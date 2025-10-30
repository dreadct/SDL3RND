#pragma once

#include <cstdint>
#include <memory>

#include <SDL3/SDL.h>

class EDisplay;
typedef std::shared_ptr<EDisplay> EDisplaySPtr;
typedef std::weak_ptr<EDisplay> EDisplayWPtr;

class EDisplayMode {
private:
    // Private properties

    EDisplayWPtr display;
    SDL_DisplayMode *sdlDisplayMode;

public:
    // Class lifecycle

    EDisplayMode() = delete;
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
    uint32_t getWidth() const;
    uint32_t getHeight() const;
    SDL_DisplayMode* getSDLDisplayMode() const;
};
