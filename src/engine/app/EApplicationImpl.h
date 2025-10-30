#include <engine/app/EApplication.h>

#include <string>
#include <vector>

#include "window/EAppWindow.h"
#include "../displays/EDisplayService.h"

class EApplication::Impl {
private:
    // Private properties

    EAppWindowUPtr appWindow;
    std::vector<std::string> commandLineArguments;
    EDisplayServiceSPtr displayService;

public:
    // Class lifecycle

    Impl() = delete;
    Impl(
        int argc,
        char *argv[]
    ) noexcept;
    ~Impl() = default;

    Impl(const Impl&) = delete;
    Impl(Impl&& other) noexcept;

    Impl& operator=(const Impl&) = delete;
    Impl& operator=(Impl&& other) noexcept;

    // Accessors

    const std::vector<std::string>& getCommandLineArguments() const;

    // App lifecycle

    SDL_AppResult init() noexcept;
    SDL_AppResult handleEvent(SDL_Event *event) noexcept;
    SDL_AppResult iterate() noexcept;
    void quit(SDL_AppResult result) noexcept;
};
