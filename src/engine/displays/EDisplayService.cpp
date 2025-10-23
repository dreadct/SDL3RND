#include "EDisplayService.h"

#include <algorithm>
#include <iostream>

#include "EDisplay.h"

// Class lifecycle

EDisplayService::EDisplayService(
) noexcept {
}

EDisplayService::EDisplayService(
    EDisplayService&& other
) noexcept {
}

EDisplayService& EDisplayService::operator=(
    EDisplayService&& other
) noexcept {
    return *this;
}

// Operating displays

EDisplaySPtrVec EDisplayService::getDisplays(
) const {
    int count = 0;
    auto pDisplayIDs = SDL_GetDisplays(&count);
    if (pDisplayIDs == nullptr) {
        auto errorDesc = SDL_GetError();
        if (errorDesc != nullptr) {
            SDL_Log("Failed to get displays list: %s", errorDesc);
        }
        return {};
    }

    std::vector<SDL_DisplayID> displayIDs(pDisplayIDs, pDisplayIDs + count);
    SDL_free(pDisplayIDs);

    EDisplaySPtrVec displays(displayIDs.size(), nullptr);
    std::transform(
        displayIDs.begin(),
        displayIDs.end(),
        displays.begin(),
        [](SDL_DisplayID displayID) {
            return std::make_shared<EDisplay>(displayID);
        }
    );

    return displays;
}

EDisplaySPtr EDisplayService::getPrimaryDisplay(
) const {
    auto displayId = SDL_GetPrimaryDisplay();
    if (displayId == 0) {
        auto errorDesc = SDL_GetError();
        if (errorDesc != nullptr) {
            SDL_Log("Failed to get a primary display: %s", errorDesc);
        }
        return nullptr;
    }

    return std::make_shared<EDisplay>(displayId);
}
