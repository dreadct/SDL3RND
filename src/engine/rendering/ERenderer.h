#pragma once

#include <memory>

#include "../clock/EClock.h"

class EAppWindow;
typedef std::shared_ptr<EAppWindow> EAppWindowSPtr;
typedef std::weak_ptr<EAppWindow> EAppWindowWPtr;

class ERenderer;
typedef std::shared_ptr<ERenderer> EBaseRendererSPtr;

class ERenderer {
private:
    // Private properties

    EAppWindowWPtr window;

protected:
    // Protected methods

    EAppWindowWPtr getWindow() const;

public:
    // Class lifecycle

    ERenderer() = delete;
    ERenderer(
        EAppWindowSPtr window
    );
    virtual ~ERenderer() = default;

    ERenderer(const ERenderer&) = delete;
    ERenderer(ERenderer&& other);

    ERenderer& operator=(const ERenderer&) = delete;
    ERenderer& operator=(ERenderer&& other);

    // Rendering

    virtual void render(
        const ESClock::duration timeSinceInit
    ) = 0;
};
