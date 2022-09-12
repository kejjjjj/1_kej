#include "pch.h"

std::string fs::Log_LevelToText(log_level level)
{
    switch (level) {
    case log_level::LOG_NONE:
        return "";
    case log_level::LOG_WARNING:
        return "[WARNING] ";
    case log_level::LOG_ERROR:
        return "[ERROR] ";
    case log_level::LOG_FATAL:
        return "[FATAL] ";
    default:
        return "";
    }
    return "";
}
bool fs::Log_Create(std::string path)
{
    _log.initialized = F_CreateFile(path);
    return _log.initialized;
}

bool fs::Log_Write(log_level type, const char* msg, ...)
{
    if (!_log.initialized)
        return false;

    char v2[4096];
    va_list va;

    va_start(va, msg);
    _vsnprintf_s(v2, 0x1000u, msg, va);
    v2[4095] = 0;

    return Log_WriteWithModule(type, "", v2);


}
bool fs::Log_WriteWithModule(log_level type, const char* moduleName, const char* msg)
{
    if (!_log.initialized)
        return false;

    std::fstream f;
    const static std::string _path = GetExePath() + "\\1_kej_log.txt";

    if (!F_OpenFile(f, _path, fs::fileopen::FILE_APP))
        return false;

    f << Log_LevelToText(type) << moduleName << ": " << msg;

    F_CloseFile(f);

    if (type == LOG_FATAL) {
        char buffer[1024];
        sprintf_s(buffer, "A fatal error has occurred!\nSee the log file in %s\\log.txt for more information.", fs::GetExePath().c_str());
        exit(-1);
        
    }
}