#include "EAppWindow.h"

#include <cassert>
#include <stdexcept>
#include <utility>

#include "../../displays/EDisplay.h"
#include "../../displays/EDisplayMode.h"

// Class lifecycle

EAppWindow::EAppWindow(
    const std::string& title,
    const uint32_t width,
    const uint32_t height,
    SDL_WindowFlags flags
) {
    if ((window = SDL_CreateWindow(
        title.c_str(),
        (int)width,
        (int)height,
        flags
    )) == nullptr) {
        std::string error = "Failed to init SDL window: ";
        error += SDL_GetError();
        throw std::runtime_error(error);
    }
}

EAppWindow::EAppWindow(
    const std::string& title,
    const uint32_t width,
    const uint32_t height
) : EAppWindow(
    title,
    width,
    height,
    0
) {
    assert(width > 0);
    assert(height > 0);
}

EAppWindow::EAppWindow(
    const std::string& title,
    const EDisplayModeSPtr displayMode
) : EAppWindow(
    title,
    displayMode->getWidth(),
    displayMode->getHeight(),
    SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIDDEN
) {
    assert(displayMode);

    if (!displayMode) {
        throw std::runtime_error(
            "Failed to init SDL window due to a null fullscreen displayMode"
        );
    }

    if (!applyWindowFulscreenMode(displayMode)) {
        std::string error = "Failed to init SDL window in a fullscreen displayMode, cannot apply fullscreen mode: ";
        error += SDL_GetError();
        throw std::runtime_error(error);
    }

    if (!show()) {
        std::string error = "Failed to init SDL window in a fullscreen displayMode, cannot show window: ";
        error += SDL_GetError();
        throw std::runtime_error(error);
    }
}

EAppWindow::EAppWindow(
    const std::string& title,
    const EDisplaySPtr display
) {
    assert(display);

    if (!display) {
        throw std::runtime_error(
            "Failed to init SDL window due to a null fullscreen display"
        );
    }

    auto desktopMode = display->getDesktopMode();
    assert(desktopMode);

    EAppWindow(
        title,
        desktopMode
    );
}

EAppWindow::~EAppWindow() {
    if (window) {
        SDL_DestroyWindow(window);
    }
}

EAppWindow::EAppWindow(
    EAppWindow&& other
) noexcept : window(std::exchange(other.window, nullptr)) {
}

EAppWindow& EAppWindow::operator=(
    EAppWindow&& other
) noexcept {
    window = std::exchange(other.window, nullptr);
    return *this;
}

// Modifying window

std::string EAppWindow::getTitle() const {
    return SDL_GetWindowTitle(window);
}

void EAppWindow::setTitle(const std::string& title) {
    SDL_SetWindowTitle(window, title.c_str());
}

std::tuple<uint32_t, uint32_t> EAppWindow::getSize() const {
    int width = 0, height = 0;
    SDL_GetWindowSize(window, &width, &height);
    return { (uint32_t)width, (uint32_t)height };
}

void EAppWindow::setSize(
    const uint32_t width,
    const uint32_t height
) {
    SDL_SetWindowSize(window, (int)width, (int)height);
}

bool EAppWindow::hide() {
    return SDL_HideWindow(window);
}

bool EAppWindow::isHidden() const {
    auto flags = SDL_GetWindowFlags(window);
    return (flags & SDL_WINDOW_HIDDEN) != 0;
}

bool EAppWindow::show() {
    return SDL_ShowWindow(window);
}

bool EAppWindow::isFullscreen() const {
    auto flags = SDL_GetWindowFlags(window);
    return (flags & SDL_WINDOW_FULLSCREEN) != 0;
}

bool EAppWindow::setFullscreen(
    const bool isFullscreen
) {
    if (!SDL_SetWindowFullscreen(window, isFullscreen)) {
        auto errorDesc = SDL_GetError();
        if (errorDesc != nullptr) {
            SDL_LogError(
                SDL_LOG_CATEGORY_VIDEO,
                "Failed to set a fullscreen mode for window: %s",
                errorDesc
            );
        }
        return false;
    }

    if (!SDL_SyncWindow(window)) {
        auto errorDesc = SDL_GetError();
        if (errorDesc != nullptr) {
            SDL_LogError(
                SDL_LOG_CATEGORY_VIDEO,
                "Failed to set a fullscreen mode for window: %s",
                errorDesc
            );
        }
        return false;
    }

    return true;
}

bool EAppWindow::applyWindowFulscreenMode(
    const EDisplayModeSPtr displayMode
) {
    assert(displayMode);

    auto sdlDisplayMode = displayMode->getSDLDisplayMode();

    if (!SDL_SetWindowFullscreenMode(window, sdlDisplayMode)) {
        auto errorDesc = SDL_GetError();
        if (errorDesc != nullptr) {
            SDL_LogError(
                SDL_LOG_CATEGORY_VIDEO,
                "Failed to set a fullscreen display mode for window: %s",
                errorDesc
            );
        }
        return false;
    }

    if (!SDL_SyncWindow(window)) {
        auto errorDesc = SDL_GetError();
        if (errorDesc != nullptr) {
            SDL_LogError(
                SDL_LOG_CATEGORY_VIDEO,
                "Failed to set a fullscreen display mode for window: %s",
                errorDesc
            );
        }
        return false;
    }

    return true;
}

SDL_PropertiesID EAppWindow::getProperties() const {
    auto result = SDL_GetWindowProperties(window);
    if (result == 0) {
        auto errorDesc = SDL_GetError();
        if (errorDesc != nullptr) {
            SDL_LogError(
                SDL_LOG_CATEGORY_VIDEO,
                "Failed to get properties of a window: %s",
                errorDesc
            );
        }
    }
    return result;
}
