#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include <SDL3/SDL.h>

#include "EDisplayMode.h"

class EDisplay;
typedef std::shared_ptr<EDisplay> EDisplaySPtr;
typedef std::weak_ptr<EDisplay> EDisplayWPtr;

class EDisplayMode;
typedef std::shared_ptr<EDisplayMode> EDisplayModeSPtr;
typedef std::vector<EDisplayModeSPtr> EDisplayModeSPtrVec;

class EDisplay: public std::enable_shared_from_this<EDisplay> {
private:
    // Private properties
    
    SDL_DisplayID displayID;

public:
    // Class lifecycle

    EDisplay() = delete;
    EDisplay(const SDL_DisplayID displayID) noexcept;
    ~EDisplay() = default;

	EDisplay(EDisplay const&) = delete;
	EDisplay(EDisplay&& other) noexcept;

	EDisplay& operator=(EDisplay const&) = delete;
	EDisplay& operator=(EDisplay&& other) noexcept;

    // Display information

    EDisplayModeSPtr getCurrentMode() const;

    EDisplayModeSPtr getDesktopMode() const;

    EDisplayModeSPtrVec getFullscreenModes() const;

    std::string getName() const;
};
