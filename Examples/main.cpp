// SPDX-License-Identifier: GPL-2.0-only
// Copyright © 2024 Interactive Echoes. All rights reserved.
// Author: mozahzah

#include "IECore.h"

class DemoApp
{
public:
    DemoApp() : m_Renderer(std::make_unique<IERenderer_Vulkan>()) {}
    IERenderer& GetRenderer() { return *m_Renderer; }

public:
    void OnPreFrameRender()
    {
        ImGui::ShowDemoWindow();
        //...
    }

    void OnPostFrameRender()
    {
        //...
    }

private:
    std::unique_ptr<IERenderer> m_Renderer;
};

int main()
{
    DemoApp App;

    IERenderer& Renderer = App.GetRenderer();
    if (Renderer.Initialize())
    {
        if (ImGuiContext* const CreatedImGuiContext = ImGui::CreateContext())
        {
            ImGuiIO& IO = ImGui::GetIO();
            IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_IsSRGB;
            if (Renderer.PostImGuiContextCreated())
            {
                ImGui::IEStyle::StyleIE();
                IO.IniFilename = nullptr;
                IO.LogFilename = nullptr;

                IEClock::time_point StartFrameTime = IEClock::now();
                IEDurationMs CapturedDeltaTime = IEDurationMs::zero();

                while (Renderer.IsAppRunning())
                {
                    StartFrameTime = IEClock::now();

                    Renderer.CheckAndResizeSwapChain();
                    Renderer.NewFrame();
                    ImGui::NewFrame();

                    // On Pre Frame Render
                    // Pre-Frame App Code Goes Here
                    App.OnPreFrameRender();
                    Renderer.DrawTelemetry();
                    // On Pre Frame Render
                    
                    ImGui::Render();
                    Renderer.RenderFrame(*ImGui::GetDrawData());
                    Renderer.PresentFrame();

                    // On Post Frame Render
                    // Post-Frame App Code Goes Here
                    App.OnPostFrameRender();
                    // On Post Frame Render

                    CapturedDeltaTime = std::chrono::duration_cast<IEDurationMs>(IEClock::now() - StartFrameTime);
                    if (Renderer.IsAppWindowOpen())
                    {
                        Renderer.WaitEventsTimeout(0.1f);
                    }
                    else
                    {
                        Renderer.WaitEvents();
                    }
                }
            }
        }

        Renderer.Deinitialize();
    }

    return 0;
}