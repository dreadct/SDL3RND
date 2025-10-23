#pragma once

#include <memory>

#include <SDL3/SDL.h>

/// An engine application class used to initialize
/// the engine instance in a SDL application.
class EApplication {
private:
    // PIMPL

    class Impl;
    std::unique_ptr<Impl> pImpl;

public:
    // Class lifecycle

    EApplication() = delete;
    EApplication(
        int argc,
        char *argv[]
    ) noexcept;
    ~EApplication();

    EApplication(const EApplication&) = delete;
    EApplication(EApplication&& other) noexcept;

    EApplication& operator=(const EApplication&) = delete;
    EApplication& operator=(EApplication&& other) noexcept;

    // App lifecycle

    SDL_AppResult init() noexcept;
    SDL_AppResult handleEvent(SDL_Event *event) noexcept;
    SDL_AppResult iterate() noexcept;
    void quit(SDL_AppResult result) noexcept;
};
