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

    const struct sync_track *image_X;  // Camera Offset to Origo X
    const struct sync_track *image_Y;  // Offset to Origo Y
    const struct sync_track *image_Z;  // Offset to Origo Z
    const struct sync_track *image_scale;  // Offset to Origo Z

    const struct sync_track *fade_A;	// Fade alpha. 0 clear 1 black screen

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
    glViewport(0, 0, gdl::GetScreenWidth(), gdl::GetScreenHeight());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, gdl::GetAspectRatio(), 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 0.0f,
			  0.0, 0.0f, -1.0f,
			  0.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_FLAT);

	glClearColor((float)0xfb/255.0f, (float)0xbb/255.0f, (float)0xad/255.0f, 0.0f);
    //glClearColor(247.0f/255.0f, 1.0f, 174.0f/255.0f, 0.0f);
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

	image_X = gdl::RocketSync::GetTrack("image:X");
	image_Y = gdl::RocketSync::GetTrack("image:Y");
	image_Z = gdl::RocketSync::GetTrack("image:Z");
	image_scale = gdl::RocketSync::GetTrack("image:scale");

	fade_A = gdl::RocketSync::GetTrack( "fade_A");

#endif

	activeEffect = fxTitle;
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
	gdl::Font* f = AssetManager::GetDebugFont();
	glTranslatef(0.0f, 0.0f, -1.0f);
	f->Printf(0x333f58FF, 0.2f, gdl::LJustify, gdl::LJustify, "Objects of\nSentimental Value\nSpinning to\nChillstep");
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
	glPushMatrix();
	glTranslatef(
		gdl::RocketSync::GetFloat(image_X),
		gdl::RocketSync::GetFloat(image_Y),
		gdl::RocketSync::GetFloat(image_Z));
	float s = gdl::RocketSync::GetFloat(image_scale);
	glScalef(s, s, 1.0f);
	bg->Draw3D(1.0f, gdl::LJustify, gdl::LJustify);
	glPopMatrix();
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

		model->Draw();
    glPopMatrix();

    // TODO: Change font and image default
    // rendering to CCW
	/*
    glPushMatrix();
        glTranslatef(00.0f, -00.0f, -1.0f);
        AssetManager::GetDebugFont()->Printf(gdl::Colors::Black, 0.2f, gdl::LJustify, gdl::LJustify, "scale:%.1f", is);
    glPopMatrix();
    */
}


void EffectHost::Draw()
{
    // NOTE!!!!
    // Without this setup the Dolphin is
    // all messed up with the
    // rendering
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    Init3D();
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
		case fxQUIT_DEMO:
			// TODO quit demo
		default:
			// nop
			break;
	};


	float fade = gdl::RocketSync::GetFloat(fade_A);
	if (fade > 0.0f)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		float W = gdl::GetScreenWidth();
		float H = gdl::GetScreenHeight();
		glOrtho(0, W, H, 0.0f, 1.0f, -1.0f);

		// Set the modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glBegin(GL_QUADS);
			PaletteColor4f(BLACK, fade);
			glVertex3f(0.0f, 0.0f, 0.9999f);
			glVertex3f(W, 0.0f, 0.9999f);
			glVertex3f(W, H, 0.9999f);
			glVertex3f(0.0f, H, 0.9999f);
		glEnd();
		glDisable(GL_BLEND);
	}

#ifdef PROFILING
	rocketDebug.Draw(AssetManager::GetDebugFont());
#endif
}

