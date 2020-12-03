#include "stdinc.hpp"

utils::hook::detour logprint_hook;

std::recursive_mutex redirect_lock;

std::ofstream stream;

const char* get_time_offset()
{
    const auto now = std::chrono::high_resolution_clock::now();

    const auto seconds = int(*reinterpret_cast<int*>(0x1474FDC94) / 1000);
    const auto minutes = int(seconds / 60);

    const auto s = seconds - minutes * 60;

    return utils::string::va("%3i:%s%i ", minutes, s < 10 ? "0" : "", s);
}

void logprint_stub(const char* fmt, ...)
{
    std::lock_guard<std::recursive_mutex> $(redirect_lock);

    static thread_local utils::string::va_provider<8, 256> provider;
    va_list ap;
    va_start(ap, fmt);
    const char* result = provider.get(fmt, ap);
    va_end(ap);

    stream << get_time_offset() << result;
    stream.flush();
}

std::wstring directory() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);

    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");

    return std::wstring(buffer).substr(0, pos);
}

void init()
{
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);

    std::wstring dir = directory();
    std::string logpath(dir.begin(), dir.end());

    logpath.append("\\identities\\dedicatedpc\\main\\games_mp.log");

    stream.open(logpath, std::ofstream::out | std::ofstream::app);

    logprint_hook.create(game::G_LogPrintf, logprint_stub);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        init();
        break;
    }
    return TRUE;
}