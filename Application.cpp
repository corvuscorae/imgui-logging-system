#include "Application.h"
#include "imgui/imgui.h"
#include <iostream>
#include <vector>
#include <cstring>

namespace ClassGame {
        //
        // our global variables
        //
        struct LogItem{
            const char* level;
            const char* dat;
            const char* type = NULL;

            LogItem(const char* _level, const char* _dat) {
                level = _level;
                dat = _dat;
            }

            LogItem(const char* _level, const char* _dat, const char* _type) {
                level = _level;
                dat = _dat;
                type = _type;
            }

            std::string print(){
                std::string message = "[" + std::string(level) + "] ";
                
                if(type){
                    message += "[" + std::string(type) + "] ";
                }

                message += dat;
                
                return message;
            }
        };

        // singleton pattern class for logging
        class Logger{
            private:
                Logger() = default;
                std::vector<LogItem> log;
                
            public:
                int log_size = 0;

                const char* levels [3] = {
                    "INFO", 
                    "WARN",
                    "ERROR"
                };

                static Logger& GetInstance(){
                    static Logger instance;
                    
                    return instance;
                }

                void LogInfo(const char* message, int level = 0){
                    // TEMP: test code
                    LogItem new_item(levels[level], message);
                    log.push_back(new_item);

                    std::cout << new_item.print() << std::endl;
                    log_size++;
                }

                void LogGameEvent(const char* message, int level = 0){
                    // TEMP: test code
                    LogItem new_item(levels[level], message, "GAME");
                    log.push_back(new_item);
                 
                    std::cout << new_item.print() << std::endl;
                    log_size++;
                }

                void clear(){
                    log.clear();
                    log_size = 0;
                }

                std::string print_last(){
                    return log.back().print();
                }

                std::string print(int i){
                    return log.at(i).print();
                }
        };

        // Initialize logging system
        Logger& logger = Logger::GetInstance();

        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //

        void GameStartUp() 
        {
           logger.LogInfo("Game started successfully");
           logger.LogGameEvent("Application initialized");
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

            ImGui::Begin("ImGui Log Demo");
            ImGui::LogButtons();

            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }
            ImGui::End();

            // TESTING
            static float f = 0.0f;
            static int counter = 0;
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            ImGuiIO& io = ImGui::GetIO(); (void)io;


            //--- GAME LOG ---//
            ImGui::Begin("Game Log");

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

            if(ImGui::Button("Clear")){
                logger.clear(); // ???
            }
            ImGui::SameLine();
            if(ImGui::Button("Test Info")){
               logger.LogInfo("This is test info.", 0);
            } 
            ImGui::SameLine();
            if(ImGui::Button("Test Warn")){
               logger.LogInfo("This is a test warning.", 1);
            } 
            ImGui::SameLine();
            if(ImGui::Button("Test Error")){
               logger.LogInfo("This is a test error.", 2);
            } 


            for(int i = 0; i < logger.log_size; i++){
                ImGui::Text(logger.print(i).c_str());
            }

            ImGui::End();
        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
        }
}
