#include "EApplicationImpl.h"

#include <utility>

// Class lifecycle

EApplication::Impl::Impl(
    int argc,
    char *argv[]
) noexcept : commandLineArguments(argv, argv + argc),
    displayService(std::make_shared<EDisplayService>()) {
}

EApplication::Impl::Impl(
    Impl&& other
) noexcept : commandLineArguments(std::move(other.commandLineArguments)),
    displayService(std::move(other.displayService)) {
}

EApplication::Impl& EApplication::Impl::operator=(
    Impl&& other
) noexcept {
    commandLineArguments = std::move(other.commandLineArguments);
    displayService = std::move(other.displayService);
    return *this;
}

// Accessors

const std::vector<std::string>& EApplication::Impl::getCommandLineArguments() const {
    return commandLineArguments;
}

// App lifecycle

SDL_AppResult EApplication::Impl::init(
) noexcept {
    try {
        // init video system
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("Failed to init SDL video system: %s", SDL_GetError());
        }

        // get a primary display
        auto primaryDisplay = displayService->getPrimaryDisplay();
        if (primaryDisplay == nullptr) {
            SDL_Log("App can't run without a display, terminating...");
            return SDL_APP_FAILURE;
        }
        
        // get desktop display mode
        EDisplayModeSPtr desktopDisplayMode = primaryDisplay->getDesktopMode();
        if (!desktopDisplayMode) {
            SDL_Log("App can't fullscreen without obtaining a primary display mode, terminating...");
            return SDL_APP_FAILURE;
        }

        auto [width, height] = desktopDisplayMode->getResolution();
        if (width == 0 || height == 0) {
            SDL_Log("App can't fullscreen without obtaining a primary display resolution, terminating...");
            return SDL_APP_FAILURE;
        }

        appWindow = std::make_unique<EAppWindow>("", width, height, true);
        return SDL_APP_CONTINUE;
    } catch (const std::exception& e) {
        SDL_Log("Failed to init EApplication: %s", e.what());
        return SDL_APP_FAILURE;
    }
}

SDL_AppResult EApplication::Impl::handleEvent(
    SDL_Event *event
) noexcept {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult EApplication::Impl::iterate(
) noexcept {
    return SDL_APP_CONTINUE;
}

void EApplication::Impl::quit(
    SDL_AppResult result
) noexcept {
}
