#pragma once

#include <cstdint>
#include <memory>
#include <tuple>

#include <SDL3/SDL.h>

class EDisplay;
typedef std::shared_ptr<EDisplay> EDisplaySPtr;
typedef std::weak_ptr<EDisplay> EDisplayWPtr;

class EDisplayMode {
private:
    // Private properties

    EDisplayWPtr display;
    SDL_PixelFormat pixelFormat;
    uint32_t width;
    uint32_t height;

public:
    // Class lifecycle

    EDisplayMode() = delete;
    EDisplayMode(
        const EDisplaySPtr display,
        const SDL_PixelFormat pixelFormat,
        const uint32_t width,
        const uint32_t height
    ) noexcept;
    EDisplayMode(
        const EDisplaySPtr display,
        const SDL_DisplayMode *sdlDisplayMode
    ) noexcept;
    ~EDisplayMode() = default;

	EDisplayMode(EDisplayMode const&) = delete;
	EDisplayMode(EDisplayMode&& other) noexcept;

	EDisplayMode& operator=(EDisplayMode const&) = delete;
	EDisplayMode& operator=(EDisplayMode&& other) noexcept;

    // Accessors

    EDisplayWPtr getDisplay() const;
    SDL_PixelFormat getPixelFormat() const;
    std::tuple<uint32_t, uint32_t> getResolution() const;
};
