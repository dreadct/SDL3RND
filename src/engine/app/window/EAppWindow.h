#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <tuple>

#include <SDL3/SDL.h>

class EAppWindow;
typedef std::unique_ptr<EAppWindow> EAppWindowUPtr;

class EAppWindow {
private:
    // Private properties
    SDL_Window* window;

public:
    // Class lifecycle
    EAppWindow() = delete;
    EAppWindow(
        const std::string& title,
        const uint32_t width,
        const uint32_t height,
        const bool isFullscreen = false
    );
    ~EAppWindow();

    EAppWindow(const EAppWindow&) = delete;
    EAppWindow(EAppWindow&& other) noexcept;

    EAppWindow& operator=(const EAppWindow&) = delete;
    EAppWindow& operator=(EAppWindow&& other) noexcept;

    // Modifying window

    std::string getTitle() const;
    void setTitle(const std::string& title);

    std::tuple<uint32_t, uint32_t> getSize() const;
    void setSize(
        const uint32_t width,
        const uint32_t height
    );

    bool hide();
    bool isHidden() const;
    bool show();

    bool isFullscreen() const;
};
