#include "EAppWindow.h"

#include <stdexcept>
#include <utility>

// Class lifecycle

EAppWindow::EAppWindow(
    const std::string& title,
    const uint32_t width,
    const uint32_t height,
    const bool isFullscreen
) {
    SDL_WindowFlags flags = 0;
    if (isFullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

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
