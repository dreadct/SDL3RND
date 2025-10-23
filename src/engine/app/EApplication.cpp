#include <engine/app/EApplication.h>
#include "EApplicationImpl.h"

#include <utility>

// Class lifecycle

EApplication::EApplication(
    int argc,
    char *argv[]
) noexcept : pImpl(std::make_unique<Impl>(argc, argv)) {
}

EApplication::~EApplication() {
}

EApplication::EApplication(
    EApplication&& other
) noexcept : pImpl(std::move(other.pImpl)) {
}

EApplication& EApplication::operator=(
    EApplication&& other
) noexcept {
    pImpl = std::move(other.pImpl);
    return *this;
}

// App lifecycle

SDL_AppResult EApplication::init(
) noexcept {
    return pImpl->init();
}

SDL_AppResult EApplication::handleEvent(
    SDL_Event *event
) noexcept {
    return pImpl->handleEvent(event);
}

SDL_AppResult EApplication::iterate(
) noexcept {
    return pImpl->iterate();
}

void EApplication::quit(
    SDL_AppResult result
) noexcept {
    pImpl->quit(result);
}
