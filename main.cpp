#include <mgdl.h>
#include "mgdl-rocket.h"
#include "mgdl-mesh.h"

#ifdef SYNC_PLAYER
    #include MGDL_ROCKET_FILE_H
    #include MGDL_ROCKET_FILE_CPP
#else
    static ROCKET_TRACK clear_r;
#endif

static Mesh trainMesh;
static float angle = 0.0f;
static gdl::Image texture;
static gdl::Font ibmFont;
size_t facesToDraw = 0;
float meshZ = -8.0f;
float meshScale = 1.0f;

void Init3D()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, gdl::GetAspectRatio(), 0.1, 100.0);
}
void Init2D()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, (double)gdl::GetScreenWidth(), 0.0, (double)gdl::GetScreenHeight());
}

void Cross3D()
{
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);

        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);

        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();
}

void Cross2D()
{
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f((float)gdl::GetScreenWidth(), (float)gdl::GetScreenHeight());

    glVertex2f(0.0f, (float)gdl::GetScreenHeight());
    glVertex2f((float)gdl::GetScreenWidth(), 0.0f);
    glEnd();
}


//---------------------------------------------------------------------

void init()
{
    glViewport(0, 0, gdl::GetScreenWidth(), gdl::GetScreenHeight());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Init3D();
    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(247.0f/255.0f, 1.0f, 174.0f/255.0f, 0.0f);
    gdl::Sound* music = gdl::LoadSound("plink.wav");

    bool rocketInit = gdl::RocketSync::InitRocket(music, 120, 4);
    if (rocketInit == false)
    {
        gdl::DoProgramExit();
    }

#ifndef SYNC_PLAYER
    clear_r = gdl::RocketSync::GetTrack("clear_r");
#endif

    // Test fbx loading
    trainMesh.LoadFile("assets/train.fbx");
    texture.LoadFile("assets/train_small_512.png", gdl::TextureFilterModes::Linear);
    ibmFont.LoadFromImage("assets/font8x16.png", 8, 16, ' ');

    gdl::RocketSync::StartSync();
}
// Rendering callback. glFlush etc.. is done automatically after it
void render()
{

    // NOTE!!!!
    // Without this setup the Dolphin is
    // all messed up with the
    // rendering
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    Init3D();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0,
              0.0, 0.0, -1.0,  // Center
              0.0, 1.0, 0.0); // Up
    // End of setup
    glEnable(GL_CULL_FACE);
    Cross3D();

    glPushMatrix();
        glTranslatef(-0.0f, -0.5f, meshZ);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture.GetTextureId());
        trainMesh.DrawImmediate(Textured);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // TODO: Change font and image default
    // rendering to CCW
    glDisable(GL_CULL_FACE);
    glPushMatrix();
        glTranslatef(-0.9f, -0.1f, -1.0f);
        ibmFont.Printf(gdl::Colors::Black, 0.10f, gdl::LJustify, gdl::LJustify, "Z: %.1f, Scl: %.1f Ang %.1f", meshZ, meshScale, angle);
    glPopMatrix();
}


// Called before render()
void update()
{
    if (gdl::GetController(0).ButtonPress(gdl::WiiButtons::ButtonHome))
    {
        gdl::Platform& plat = gdl::Platform::GetPlatform();
        plat.DoProgramExit();
    }

#ifndef SYNC_PLAYER
    if (gdl::GetController(0).ButtonPress(gdl::WiiButtons::Button2))
    {
       gdl::RocketSync::StartSaveToHeader();
       gdl::RocketSync::SaveTrack(clear_r);
       gdl::RocketSync::EndSaveToHeader();
    }
#endif

    gdl::RocketSync::UpdateRow();

    float r = 1.0f;

    r = 247.0f/255.0f;
    r = gdl::RocketSync::GetFloat(clear_r);

    float g = 1.0f;
    float b = 174.0f/255.0f;

    glClearColor(r,g ,b , 0.0f);

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

int main()
{
    gdl::InitSystem(
        gdl::ScreenAspect::Screen4x3,
        init,
        update,  // std::function callbacks
        render
    );
}
