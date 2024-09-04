#include <mgdl.h>
#include "mgdl-rocket.h"
#include "mgdl-mesh.h"
#include "assetmanager.h"
#include "effecthost.h"


static EffectHost host;

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

//---------------------------------------------------------------------

void init()
{
    bool loadOk = AssetManager::LoadAssets();
    if (loadOk == false)
    {
        gdl::DoProgramExit();
    }

    bool rocketInit = gdl::RocketSync::InitRocket(AssetManager::GetMusic(), 120, 4);
    if (rocketInit == false)
    {
        gdl::DoProgramExit();
    }

    host.Init();

    gdl::RocketSync::StartSync();
}

// Rendering callback. glFlush etc.. is done automatically after it
void render()
{
    host.Draw();
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
        host.Save();
    }
#endif

    gdl::RocketSync::UpdateRow();
    host.Update();

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
