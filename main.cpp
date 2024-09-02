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
    texture.LoadFile("assets/train_small.png", gdl::TextureFilterModes::Linear);

    gdl::RocketSync::StartSync();
}
// Rendering callback. glFlush etc.. is done automatically after it
void render()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    Cross3D();
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -1.0f);
        texture.Draw3D(2.0f, gdl::LJustify, gdl::LJustify);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.0f, -0.5f, -8.0f);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture.GetTextureId());
        trainMesh.DrawImmediate(Textured);
        //trainMesh.DrawImmediate(Lines);
        glDisable(GL_TEXTURE_2D);
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

    angle = r;
    glClearColor(r,g ,b , 0.0f);
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
