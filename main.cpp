#include <mgdl.h>
#include "mgdl-rocket.h"
#include "mgdl-mesh.h"
#include "assetmanager.h"
#include "effecthost.h"


static EffectHost host;


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

    bool rocketInit = gdl::RocketSync::InitRocket(AssetManager::GetMusic(), 50, 8);
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
    bool qr = host.quitRequested;
#ifndef SYNC_PLAYER
    if (qr)
    {
        qr = false;
    }
#endif
    if (gdl::GetController(0).ButtonPress(gdl::WiiButtons::ButtonHome) || qr)
    {
        gdl::Sound* music = AssetManager::GetMusic();
        music->Stop();
        host.Free();
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
        //,gdl::PlatformInitFlag::FlagPauseUntilA
    );
}
