#include "EApplicationImpl.h"

#include <utility>

// Class lifecycle

EApplication::Impl::Impl(
    int argc,
    char *argv[]
) noexcept : commandLineArguments(argv, argv + argc) {
}

EApplication::Impl::Impl(
    Impl&& other
) noexcept : commandLineArguments(std::move(other.commandLineArguments)) {
}

EApplication::Impl& EApplication::Impl::operator=(
    Impl&& other
) noexcept {
    commandLineArguments = std::move(other.commandLineArguments);
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
    } else if (event->type == SDL_EVENT_KEY_DOWN
        && event->key.key == SDLK_ESCAPE) {
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
