#pragma once

#include <memory>
#include <vector>

#include <SDL3/SDL.h>

#include "EDisplay.h"

typedef std::vector<EDisplaySPtr> EDisplaySPtrVec;

class EDisplayService;
typedef std::shared_ptr<EDisplayService> EDisplayServiceSPtr;

class EDisplayService {
public:
    // Class lifecycle

    EDisplayService() noexcept;
    ~EDisplayService() = default;

	EDisplayService(EDisplayService const&) = delete;
	EDisplayService(EDisplayService&& other) noexcept;

	EDisplayService& operator=(EDisplayService const&) = delete;
	EDisplayService& operator=(EDisplayService&& other) noexcept;

    // Operating displays

    EDisplaySPtrVec getDisplays() const;
    EDisplaySPtr getPrimaryDisplay() const;
};
