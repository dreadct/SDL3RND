#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <tuple>

#include <SDL3/SDL.h>

class EDisplay;
typedef std::shared_ptr<EDisplay> EDisplaySPtr;

class EDisplayMode;
typedef std::shared_ptr<EDisplayMode> EDisplayModeSPtr;

class EAppWindow;
typedef std::shared_ptr<EAppWindow> EAppWindowSPtr;
typedef std::weak_ptr<EAppWindow> EAppWindowWPtr;

class EAppWindow {
private:
    // Private properties
    SDL_Window* window;

    // Private class lifecycle.

    /// @brief Creates a window of a given size with a specified flags.
    /// @param title A window title.
    /// @param width A window width.
    /// @param height A window height.
    /// @param flags A flags for window.
    EAppWindow(
        const std::string& title,
        const uint32_t width,
        const uint32_t height,
        SDL_WindowFlags flags
    );

public:
    // Class lifecycle

    EAppWindow() = delete;

    /// @brief Creates a usual window of a given size.
    /// @param title A window title.
    /// @param width A window width.
    /// @param height A window height.
    EAppWindow(
        const std::string& title,
        const uint32_t width,
        const uint32_t height
    );

    /// @brief Creates a fullscreen window.
    /// @param title A window title.
    /// @param displayMode A custom display mode to use.
    EAppWindow(
        const std::string& title,
        const EDisplayModeSPtr displayMode
    );

    /// @brief Creates a fullscreen window.
    /// @param title A window title.
    /// @param display A display to appear in fullscreen
    ///                desktop mode on.
    EAppWindow(
        const std::string& title,
        const EDisplaySPtr display
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
    bool setFullscreen(
        const bool isFullscreen
    );

    bool applyWindowFulscreenMode(
        const EDisplayModeSPtr displayMode
    );

    SDL_PropertiesID getProperties() const;
};
