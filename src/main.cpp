#include "game.hpp"
#include "platform.hpp"

int game_main(int argc, char *argv[])
{
    Game game;
    if (!game.init())
        return -1;
    game.run();

    return 0;
}

#if defined(GAME_PLATFORM_LINUX)

int main(int argc, char *argv[])
{
    return game_main(argc, argv);
}

#else // Windows

#include <Windows.h>

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;

    return game_main(__argc, __argv);
}

#endif
