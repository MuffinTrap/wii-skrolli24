#include "effecthost.h"
#include "rocket/mgdl-rocket.h"
#include <stdio.h>
#include <cmath>
#include <mgdl/mgdl-opengl.h>
#include <mgdl/mgdl-main.h>
#include <glm/glm.hpp>
#include "palette.h"
#include "assetmanager.h"
#include "rocketdebug.h"

//static RocketDebug rocketDebug;
// TESTING AREA
static float angle = 0.0f;
size_t facesToDraw = 0;
float meshZ = -8.0f;
float meshScale = 1.0f;
void DrawModel();
void DrawTitle();

#ifndef SYNC_PLAYER
    const struct sync_track *effect_active;  // Which effect is active.
    const struct sync_track *item_visible;  // Which item is shown
    const struct sync_track *camera_rotX;  // Camera Rotation around X
    const struct sync_track *camera_rotY;  // around Y
    const struct sync_track *camera_rotZ;  // around Z
    const struct sync_track *camera_X;  // Camera Offset to Origo X
    const struct sync_track *camera_Y;  // Offset to Origo Y
    const struct sync_track *camera_Z;  // Offset to Origo Z

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

    glClearColor(247.0f/255.0f, 1.0f, 174.0f/255.0f, 0.0f);
}

EffectHost::EffectHost()
{

}

void EffectHost::Init()
{
#ifndef SYNC_PLAYER
	effect_active = gdl::RocketSync::GetTrack("effect_active");
	item_visible = gdl::RocketSync::GetTrack( "item_visible");
	camera_rotX = gdl::RocketSync::GetTrack( "camera:rotX");
	camera_rotY = gdl::RocketSync::GetTrack( "camera:rotY");
	camera_rotZ = gdl::RocketSync::GetTrack( "camera:rotZ");
	camera_X = gdl::RocketSync::GetTrack( "camera:X");
	camera_Y = gdl::RocketSync::GetTrack( "camera:Y");
	camera_Z = gdl::RocketSync::GetTrack( "camera:Z");
	fade_A = gdl::RocketSync::GetTrack( "fade_A");

	gdl::RocketSync::SetToBeSaved(effect_active);
	gdl::RocketSync::SetToBeSaved(item_visible);
	gdl::RocketSync::SetToBeSaved(camera_rotX);
	gdl::RocketSync::SetToBeSaved(camera_rotY);
	gdl::RocketSync::SetToBeSaved(camera_rotZ);
	gdl::RocketSync::SetToBeSaved(camera_X);
	gdl::RocketSync::SetToBeSaved(camera_Y);
	gdl::RocketSync::SetToBeSaved(camera_Z);
	gdl::RocketSync::SetToBeSaved(fade_A);
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

    if (gdl::GetController(0).ButtonPress(gdl::WiiButtons::ButtonUp))
    {
        meshZ += 0.5f;
    }
    else if (gdl::GetController(0).ButtonPress(gdl::WiiButtons::ButtonDown))
    {
        meshZ -= 0.5f;
    }
    if (gdl::GetController(0).ButtonPress(gdl::WiiButtons::ButtonLeft))
    {
       angle += 15.0f;
    }
    else if (gdl::GetController(0).ButtonPress(gdl::WiiButtons::ButtonRight))
    {
        angle -= 15.0f;
    }
}

void DrawTitle()
{
	gdl::Font* f = AssetManager::GetDebugFont();
	glTranslatef(0.0f, 0.0f, -1.0f);
    glDisable(GL_CULL_FACE);
	f->Printf(gdl::Colors::Black, 0.2f, gdl::LJustify, gdl::LJustify, "Objects of\nSentimental Value\nSpinning to\nChillstep");
}


void DrawModel()
{
	Mesh* train = AssetManager::GetMesh();
	gdl::Image* texture = AssetManager::GetImage("train");
    glEnable(GL_CULL_FACE);

    float r = 247.0f/255.0f;
    float g = 1.0f;
    float b = 174.0f/255.0f;

    glClearColor(r,g ,b , 0.0f);

    glPushMatrix();
        glTranslatef(-0.0f, -0.5f, meshZ);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture->GetTextureId());
        train->DrawImmediate(Textured);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // TODO: Change font and image default
    // rendering to CCW
    glDisable(GL_CULL_FACE);
    glPushMatrix();
        glTranslatef(-0.9f, -0.1f, -1.0f);
        AssetManager::GetDebugFont()->Printf(gdl::Colors::Black, 0.10f, gdl::LJustify, gdl::LJustify, "Z: %.1f, Scl: %.1f Ang %.1f", meshZ, meshScale, angle);
    glPopMatrix();

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

	// Camera position and direction

	gluLookAt(gdl::RocketSync::GetFloat(camera_X),
				gdl::RocketSync::GetFloat(camera_Y),
				 gdl::RocketSync::GetFloat(camera_Z),
				 0.0f, 0.0f, -1.0f,
				 0.0f, 1.0f, 0.0f);

    // End of setup

	switch(activeEffect)
	{
		// nop
		case fxTitle:
			DrawTitle();

			break;
		case fxRoom:
			DrawModel();

			break;
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

