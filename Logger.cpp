#include "Logger.h"

void Logger::ToggleConsoleLog(bool b)
{
    to_console_enabled = b;
}

void Logger::WriteLogToFile(const std::string &_filename)
{
    // OPEN FILE
    if (file.is_open())
    {
        file.close();
    }

    filename = _filename;
    file.open(filename, std::ios::out);

    // WRITE
    if (file.is_open())
    {
        for (int i = 0; i < log.size(); i++)
        {
            file << log.at(i).print() << "\n";
        }
        file.flush();
    }
}

void Logger::LogInfo(const char *message, int lvl)
{
    LogItem new_item(level[lvl], message, color[lvl]);
    log.push_back(new_item);

    if (to_console_enabled)
    {
        std::cout << new_item.print() << std::endl;
    }

    log_size++;
}

void Logger::LogGameEvent(const char *message, int lvl)
{
    LogItem new_item(level[lvl], message, "GAME", color[lvl]);
    log.push_back(new_item);

    if (to_console_enabled)
    {
        std::cout << new_item.print() << std::endl;
    }

    log_size++;
}

void Logger::clear()
{
    log.clear();
    log_size = 0;
}

LogItem Logger::get(int i)
{
    return log.at(i);
}

std::string Logger::print_last()
{
    return log.back().print();
}

std::string Logger::print(int i)
{
    return log.at(i).print();
}
