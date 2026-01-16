#pragma once

#include "imgui/imgui.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <cstring>
#include <string>


struct LogItem
{
    const char *level;
    const char *dat;
    const char *type = NULL;
    ImVec4 color;

    LogItem(const char *_level, const char *_dat, ImVec4 _col)
    {
        level = _level;
        dat = _dat;
        color = _col;
    }

    LogItem(const char *_level, const char *_dat, const char *_type, ImVec4 _col)
    {
        level = _level;
        dat = _dat;
        type = _type;
        color = _col;
    }

    std::string print()
    {
        std::string message = "[" + std::string(level) + "] ";

        if (type)
        {
            message += "[" + std::string(type) + "] ";
        }

        message += dat;

        return message;
    }
};

// singleton pattern class for logging
class Logger
{
private:
    Logger() = default;
    std::vector<LogItem> log;
    std::ofstream file;
    std::string filename;

public:
    int log_size = 0;
    bool to_console_enabled = true;

    const char *level[3] = {
        "INFO",
        "WARN",
        "ERROR"};

    const ImVec4 color[3] = {
        ImVec4(1, 1, 1, 1),
        ImVec4(1, 1, 0, 1),
        ImVec4(1, 0, 0, 1)};

    static Logger &GetInstance()
    {
        static Logger instance;
        return instance;
    }

    void ToggleConsoleLog(bool b);
    void WriteLogToFile(const std::string &_filename = "game_log.txt");
    void LogInfo(const char *message, int lvl = 0);
    void LogGameEvent(const char *message, int lvl = 0);
    void clear();
    LogItem get(int i);
    std::string print_last();
    std::string print(int i);
};
