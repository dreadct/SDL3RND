#include "EDisplayMode.h"

#include <cassert>
#include <utility>

// Class lifecycle

EDisplayMode::EDisplayMode(
    const EDisplaySPtr display,
    const SDL_PixelFormat pixelFormat,
    const uint32_t width,
    const uint32_t height
) noexcept : display(display),
    pixelFormat(pixelFormat),
    width(width),
    height(height) {
    assert(display != nullptr);
}

EDisplayMode::EDisplayMode(
    const EDisplaySPtr display,
    const SDL_DisplayMode *sdlDisplayMode
) noexcept : display(display) {
    assert(display != nullptr);
    assert(sdlDisplayMode != nullptr);

    pixelFormat = sdlDisplayMode->format;
    width = sdlDisplayMode->w;
    height = sdlDisplayMode->h;
}

EDisplayMode::EDisplayMode(
    EDisplayMode&& other
) noexcept : display(std::move(other.display)),
    pixelFormat(std::exchange(other.pixelFormat, SDL_PIXELFORMAT_UNKNOWN)),
    width(std::exchange(other.width, 0)),
    height(std::exchange(other.height, 0)) {
}

EDisplayMode& EDisplayMode::operator=(
    EDisplayMode&& other
) noexcept {
    display = std::move(other.display);
    pixelFormat = std::exchange(other.pixelFormat, SDL_PIXELFORMAT_UNKNOWN);
    width = std::exchange(other.width, 0);
    height = std::exchange(other.height, 0);
    return *this;
}

// Accessors

EDisplayWPtr EDisplayMode::getDisplay(
) const {
    return display;
}

SDL_PixelFormat EDisplayMode::getPixelFormat(
) const {
    return pixelFormat;
}

std::tuple<uint32_t, uint32_t> EDisplayMode::getResolution(
) const {
    return { width, height };
}