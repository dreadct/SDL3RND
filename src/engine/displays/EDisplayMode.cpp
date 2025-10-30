#include "EDisplayMode.h"

#include <cassert>
#include <utility>

// Class lifecycle

EDisplayMode::EDisplayMode(
    const EDisplaySPtr display,
    const SDL_DisplayMode *sdlDisplayMode
) noexcept : display(display),
    sdlDisplayMode(const_cast<SDL_DisplayMode *>(sdlDisplayMode)) {
    assert(display != nullptr);
    assert(sdlDisplayMode != nullptr);
}

EDisplayMode::EDisplayMode(
    EDisplayMode&& other
) noexcept : display(std::move(other.display)),
    sdlDisplayMode(std::exchange(other.sdlDisplayMode, nullptr)) {
}

EDisplayMode& EDisplayMode::operator=(
    EDisplayMode&& other
) noexcept {
    display = std::move(other.display);
    sdlDisplayMode = std::exchange(other.sdlDisplayMode, nullptr);
    return *this;
}

// Accessors

EDisplayWPtr EDisplayMode::getDisplay(
) const {
    return display;
}

SDL_PixelFormat EDisplayMode::getPixelFormat(
) const {
    return sdlDisplayMode->format;
}

uint32_t EDisplayMode::getWidth() const {
    return (uint32_t)sdlDisplayMode->w;
}

uint32_t EDisplayMode::getHeight() const {
    return (uint32_t)sdlDisplayMode->h;
}

SDL_DisplayMode* EDisplayMode::getSDLDisplayMode() const {
    return sdlDisplayMode;
}
