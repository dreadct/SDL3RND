#include "EDisplay.h"

#include <algorithm>
#include <cassert>
#include <utility>

#include "EDisplayMode.h"

// Class lifecycle

EDisplay::EDisplay(
    const SDL_DisplayID displayID
) noexcept : displayID(displayID) {
    assert(displayID != 0);
}

EDisplay::EDisplay(
    EDisplay&& other
) noexcept : displayID(std::exchange(other.displayID, 0)) {
}

EDisplay& EDisplay::operator=(
    EDisplay&& other
) noexcept {
    displayID = std::exchange(other.displayID, 0);
    return *this;
}

// Display information

EDisplayModeSPtr EDisplay::getCurrentMode() const {
    auto mode = SDL_GetCurrentDisplayMode(displayID);
    if (mode == nullptr) {
        SDL_Log(
            "Failed to get a current display mode for display %du (%s): %s",
            displayID,
            getName().c_str(),
            SDL_GetError()
        );
        return nullptr;
    }

    return std::make_shared<EDisplayMode>(
        std::const_pointer_cast<EDisplay>(shared_from_this()),
        mode
    );
}

EDisplayModeSPtr EDisplay::getDesktopMode() const {
    auto mode = SDL_GetDesktopDisplayMode(displayID);
    if (mode == nullptr) {
        SDL_Log(
            "Failed to get a desktop display mode for display %du (%s): %s",
            displayID,
            getName().c_str(),
            SDL_GetError()
        );
        return nullptr;
    }

    return std::make_shared<EDisplayMode>(
        std::const_pointer_cast<EDisplay>(shared_from_this()),
        mode
    );
}

EDisplayModeSPtrVec EDisplay::getFullscreenModes() const {
    int count = 0;
    auto pModes = SDL_GetFullscreenDisplayModes(displayID, &count);
    if (pModes == nullptr) {
        SDL_Log(
            "Failed to get fullscreen display modes for display %du (%s): %s",
            displayID,
            getName().c_str(),
            SDL_GetError()
        );
        return {};
    }

    EDisplayModeSPtrVec modes(count, nullptr);
    std::transform(
        pModes,
        pModes + count,
        modes.begin(),
        [this](SDL_DisplayMode *mode) {
            return std::make_shared<EDisplayMode>(
                std::const_pointer_cast<EDisplay>(
                    this->shared_from_this()
                ),
                mode
            );
        }
    );

    return modes;
}

std::string EDisplay::getName() const {
    auto cName = SDL_GetDisplayName(displayID);
    if (cName == nullptr) {
        SDL_Log(
            "Failed to get a display name for display %du: %s",
            displayID,
            SDL_GetError()
        );
        return "";
    }

    return cName;
}
