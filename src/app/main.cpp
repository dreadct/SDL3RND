#include <stdexcept>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <engine/app/EApplication.h>

SDL_AppResult SDL_AppInit(
    void **appstate,
    int argc,
    char *argv[]
) {
    SDL_SetAppMetadata("SDL3 RnD", "1.0", "com.example.sld3rnd");

    auto app = new EApplication(argc, argv);
    *appstate = app;
    return app->init();
}

SDL_AppResult SDL_AppEvent(
    void *appstate,
    SDL_Event *event
) {
    EApplication *app;
    if (appstate && (app = static_cast<EApplication*>(appstate))) {
        return app->handleEvent(event);
    } else {
        return SDL_APP_CONTINUE;
    }
}

SDL_AppResult SDL_AppIterate(
    void *appstate
) {
    EApplication *app;
    if (appstate && (app = static_cast<EApplication*>(appstate))) {
        return app->iterate();
    } else {
        return SDL_APP_CONTINUE;
    }
}

void SDL_AppQuit(
    void *appstate,
    SDL_AppResult result
) {
    EApplication *app;
    if (appstate && (app = static_cast<EApplication*>(appstate))) {
        app->quit(result);
        delete app;
    }
}
