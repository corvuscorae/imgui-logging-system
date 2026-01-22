#include "Application.h"
#include "imgui/imgui.h"
#include "Logger.h"

namespace ClassGame
{
    //
    // our global variables
    //
    bool show_imgui_demo = false;
    bool show_log_demo = false;

    // Initialize logging system
    Logger* logger = Logger::GetInstance();

    //
    // game starting point
    // this is called by the main render loop in main.cpp
    //
    void GameStartUp()
    {
        logger->Log("Game started successfully");
        logger->Log("Application initialized", logger->INFO, logger->GAME);
    }

    //
    // game render loop
    // this is called by the main render loop in main.cpp
    //
    void RenderGame()
    {
        ImGui::DockSpaceOverViewport();

        PutImguiLogDemo();      // imgui log demo
        logger->initUI();

        if(show_imgui_demo){    // imgui demo
            ImGui::ShowDemoWindow(&show_imgui_demo);
        }
    }

    //-- LOG DEMO WINDOW --//
    void PutImguiLogDemo(){
        if(show_log_demo){
            ImGui::Begin("ImGui Log Demo", &show_log_demo);

            // BUTTONS
            ImGui::LogButtons();

            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }

            if (ImGui::Button("Close Me")){
                show_log_demo = false;
            }
            
            ImGui::End();
        }
    }

    //
    // end turn is called by the game code at the end of each turn
    // this is where we check for a winner
    //
    void EndOfTurn()
    {
    }
}
