#include "effecthost.h"
#include "rocket/mgdl-rocket.h"
#include <stdio.h>
#include <cmath>
#include <mgdl/mgdl-opengl.h>
#include <mgdl/mgdl-main.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "palette.h"
#include "assetmanager.h"
#include "rocketdebug.h"

//static RocketDebug rocketDebug;
// TESTING AREA
size_t facesToDraw = 0;
float meshZ = -8.0f;
float meshScale = 1.0f;
void DrawModel();
void DrawTitle();

#ifndef SYNC_PLAYER
    const struct sync_track *scene_number;  // This is just to help with direction and not used

    const struct sync_track *effect_active;  // Which effect is active.
    const struct sync_track *item_visible;  // Which item is shown
    const struct sync_track *image_visible;  // Which image is shown

    const struct sync_track *camera_rotX;  // Camera Rotation around X
    const struct sync_track *camera_rotY;  // around Y
    const struct sync_track *camera_rotZ;  // around Z
    const struct sync_track *camera_X;  // Camera Offset to Origo X
    const struct sync_track *camera_Y;  // Offset to Origo Y
    const struct sync_track *camera_Z;  // Offset to Origo Z

    const struct sync_track *item_X;  // Camera Offset to Origo X
    const struct sync_track *item_Y;  // Offset to Origo Y
    const struct sync_track *item_Z;  // Offset to Origo Z
    const struct sync_track *item_rotX;  // Camera Rotation around X
    const struct sync_track *item_rotY;  // around Y
    const struct sync_track *item_rotZ;  // around Z
    const struct sync_track *item_scale;  //
    const struct sync_track *item_texture;  //

    const struct sync_track *image_X;  // Camera Offset to Origo X
    const struct sync_track *image_Y;  // Offset to Origo Y
    const struct sync_track *image_Z;  // Offset to Origo Z
    const struct sync_track *image_scale;  // Offset to Origo Z

    const struct sync_track *fade_A;	// Fade alpha. 0 clear 1 black screen
    const struct sync_track *fade_color;	// Fade alpha. 0 clear 1 black screen

#else
    // This is for the wii version.
    // Read track data from a header

    // NOTE
    // I spent over an hour trying to figure this one out
    // If the .cpp file is not included, the linker does not find the tracks.
	#include MGDL_ROCKET_FILE_H
	#include MGDL_ROCKET_FILE_CPP
#endif

void Init3D()
{
	// Set up state

	// Depth testing. This caused problems on NUMBERS
	// Does not render anyhing with depth test enabled and func as LESS
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE); //  is this needed?

	// This is the other way around on Wii, but
	// hopefully OpenGX handles it
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glShadeModel(GL_FLAT);

	//glClearColor((float)0xfb/255.0f, (float)0xbb/255.0f, (float)0xad/255.0f, 0.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

}

void EffectHost::StartDraw3D()
{
	// Do operations
	ColorName fadeName = (ColorName)gdl::RocketSync::GetInt(fade_color);
	PaletteClearColor3f(fadeName);

    glViewport(0, 0, gdl::GetScreenWidth(), gdl::GetScreenHeight());

	// NOTE
	// if GL_DEPTH_BUFFER_BIT is set, nothing is visible on Wii
#ifdef GEKKO
	glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
#else
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, gdl::GetAspectRatio(), 0.1, 100.0);

    // NOTE!!!!
    // Without this setup the Dolphin is
    // all messed up with the
    // rendering

	// Must have gluLookAt for anything to be visible
	// on Wii when using OpenGX
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	float cam_x = gdl::RocketSync::GetFloat(camera_X);
	float cam_y  = gdl::RocketSync::GetFloat(camera_Y);
	float cam_z = gdl::RocketSync::GetFloat(camera_Z);
	float cam_rx = gdl::RocketSync::GetFloat(camera_rotX);
	float cam_ry = gdl::RocketSync::GetFloat(camera_rotY);
	// Camera position and direction
	glm::vec4 cameraPos = glm::vec4(cam_x, cam_y, cam_z, 1.0f);
	glm::mat4 rotationMatrixY(1);
	rotationMatrixY = glm::rotate(rotationMatrixY, glm::radians(cam_ry), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotationMatrixX(1);
	rotationMatrixX = glm::rotate(rotationMatrixX, glm::radians(cam_rx), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::vec4 cameraDir = rotationMatrixY * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	cameraDir = rotationMatrixX * cameraDir;
	glm::vec4 cameraTarget = cameraPos + cameraDir;
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
				 cameraTarget.x, cameraTarget.y, cameraTarget.z,
				 0.0f, 1.0f, 0.0f);

    // End of setup
}


void Init2D()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, (double)gdl::GetScreenWidth(), 0.0, (double)gdl::GetScreenHeight());
}

EffectHost::EffectHost()
{

}

void EffectHost::Init()
{
#ifndef SYNC_PLAYER
	scene_number = gdl::RocketSync::GetTrack("scene_number", false);

	effect_active = gdl::RocketSync::GetTrack("effect_active");
	item_visible = gdl::RocketSync::GetTrack( "item_visible");
	image_visible = gdl::RocketSync::GetTrack( "image_visible");

	camera_X = gdl::RocketSync::GetTrack( "camera:X");
	camera_Y = gdl::RocketSync::GetTrack( "camera:Y");
	camera_Z = gdl::RocketSync::GetTrack( "camera:Z");
	camera_rotX = gdl::RocketSync::GetTrack( "camera:rotX");
	camera_rotY = gdl::RocketSync::GetTrack( "camera:rotY");
	camera_rotZ = gdl::RocketSync::GetTrack( "camera:rotZ");

	item_X = gdl::RocketSync::GetTrack( "item:X");
	item_Y = gdl::RocketSync::GetTrack( "item:Y");
	item_Z = gdl::RocketSync::GetTrack( "item:Z");
	item_rotX = gdl::RocketSync::GetTrack( "item:rotX");
	item_rotY = gdl::RocketSync::GetTrack( "item:rotY");
	item_rotZ = gdl::RocketSync::GetTrack( "item:rotZ");
	item_scale = gdl::RocketSync::GetTrack( "item:scale");
	item_texture = gdl::RocketSync::GetTrack( "item:texture");

	image_X = gdl::RocketSync::GetTrack("image:X");
	image_Y = gdl::RocketSync::GetTrack("image:Y");
	image_Z = gdl::RocketSync::GetTrack("image:Z");
	image_scale = gdl::RocketSync::GetTrack("image:scale");

	fade_A = gdl::RocketSync::GetTrack( "fade_A");
	fade_color = gdl::RocketSync::GetTrack( "fade_color");

#endif

	activeEffect = fxTitle;
	quitRequested = false;
	Init3D();
	printf("host init done\n");
}

void EffectHost::Save()
{
#ifndef SYNC_PLAYER
	gdl::RocketSync::SaveAllTracks();
#endif
}

void EffectHost::Free()
{

}

void EffectHost::Update ()
{
	activeEffect = static_cast<EffectName>(gdl::RocketSync::GetInt(effect_active));
}

void EffectHost::DrawText()
{
}

void EffectHost::DrawBackground()
{
	int imageIndex = gdl::RocketSync::GetInt(image_visible);
	if (imageIndex < 0)
	{
		return;
	}
	gdl::Image* bg = AssetManager::GetImage(imageIndex);
	if (bg == nullptr)
	{
		return;
	}
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.3f);

	glPushMatrix();
	glTranslatef(
		gdl::RocketSync::GetFloat(image_X),
		gdl::RocketSync::GetFloat(image_Y),
		gdl::RocketSync::GetFloat(image_Z));
	float s = gdl::RocketSync::GetFloat(image_scale);
	glScalef(s, s, 1.0f);
	bg->Draw3D(1.0f, gdl::LJustify, gdl::LJustify);
	glPopMatrix();

	glDisable(GL_ALPHA_TEST);
}

void EffectHost::DrawImage()
{
	// draw the selected item
	int itemIndex = gdl::RocketSync::GetInt(item_visible);
	if (itemIndex<0)
	{
		return;
	}
	gdl::Image* model = AssetManager::GetImage(itemIndex);
	if (model == nullptr)
	{
		return;
	}

	float mx = gdl::RocketSync::GetFloat(item_X);
	float my = gdl::RocketSync::GetFloat(item_Y);
	float mz = gdl::RocketSync::GetFloat(item_Z);
	float mrx = gdl::RocketSync::GetFloat(item_rotX);
	float mry = gdl::RocketSync::GetFloat(item_rotY);
	float mrz = gdl::RocketSync::GetFloat(item_rotZ);
	float is = gdl::RocketSync::GetFloat(item_scale);


    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.3f);
    glPushMatrix();
		glTranslatef(mx, my, mz);
		glRotatef(mrx, 1.0f, 0.0f, 0.0f);
		glRotatef(mry, 0.0f, 1.0f, 0.0f);
		glRotatef(mrz, 0.0f, 0.0f, 1.0f);
		glScalef(is, is, 1.0f);

		model->Draw3D(1.0f, gdl::LJustify, gdl::LJustify);
    glPopMatrix();
    glDisable(GL_ALPHA_TEST);

}

void EffectHost::DrawItem()
{
	// draw the selected item
	int itemIndex = gdl::RocketSync::GetInt(item_visible);
	if (itemIndex<0)
	{
		return;
	}
	Model* model = AssetManager::GetModel(itemIndex);
	if (model == nullptr)
	{
		return;
	}

	float mx = gdl::RocketSync::GetFloat(item_X);
	float my = gdl::RocketSync::GetFloat(item_Y);
	float mz = gdl::RocketSync::GetFloat(item_Z);
	float mrx = gdl::RocketSync::GetFloat(item_rotX);
	float mry = gdl::RocketSync::GetFloat(item_rotY);
	float mrz = gdl::RocketSync::GetFloat(item_rotZ);
	float is = gdl::RocketSync::GetFloat(item_scale);


    glPushMatrix();
		glTranslatef(mx, my, mz);
		glRotatef(mrx, 1.0f, 0.0f, 0.0f);
		glRotatef(mry, 0.0f, 1.0f, 0.0f);
		glRotatef(mrz, 0.0f, 0.0f, 1.0f);
		glScalef(is, is, is);

		model->Draw(gdl::RocketSync::GetInt(item_texture));
    glPopMatrix();
}


void EffectHost::Draw()
{
    StartDraw3D();

	switch(activeEffect)
	{
		// nop
		case fxTitle:
			DrawText();
			break;

		case fxBgAndItem:
			DrawBackground();
			DrawItem();
			break;
		case fxBgAndImage:
			DrawBackground();
			DrawImage();
			break;
		case fxCredits:
			// nothing yet
			break;
		case fxQUIT_DEMO:
			quitRequested = true;
		default:
			// nop
			break;
	};


	DrawFade();

	// Rule of thirds guide
#ifndef SYNC_PLAYER
	rocketDebug.DrawThirds();
#endif

#ifdef PROFILING
	rocketDebug.Draw(AssetManager::GetDebugFont());
#endif
}

void EffectHost::DrawFade()
{
	float fade = gdl::RocketSync::GetFloat(fade_A);
	if (fade > 0.0f)
	{
		float W = gdl::GetScreenWidth();
		float H = gdl::GetScreenHeight();

		/*
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, W,  // left, right
				H, 0.0f,  // top bottom
		  1.0f, -1.0f);  // near far
		  */

		// Set the modelview matrix
		/*
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glAlphaFunc(GL_ALWAYS, 0.0f);


		glViewport(0, 0, gdl::GetScreenWidth(), gdl::GetScreenHeight());
		*/

		//glTranslatef(0.0f, 0.0f, -1.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



		glBegin(GL_QUADS);
		//glTranslatef(0.0f, 0.0f, -1.0f);
			ColorName fadeName = (ColorName)gdl::RocketSync::GetInt(fade_color);
			PaletteColor4f(fadeName, fade);
			glVertex3f(-W, H, -0.9999f);
			glVertex3f(-W, -H, -0.9999f);
			glVertex3f(W, -H, -0.9999f);
			glVertex3f(W, H, -0.9999f);
		glEnd();
		glDisable(GL_BLEND);

	}

}


