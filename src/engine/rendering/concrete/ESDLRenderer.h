#pragma once

#include <SDL3/SDL.h>

#include "../ERenderer.h"

class ESDLRenderer: public ERenderer {
private:
    // Private properties

    SDL_Renderer *renderer;

public:
    // Class lifecycle

    ESDLRenderer() = delete;
    ESDLRenderer(
        EAppWindowSPtr window
    );
    virtual ~ESDLRenderer();

    ESDLRenderer(const ESDLRenderer&) = delete;
    ESDLRenderer(ESDLRenderer&& other);

    ESDLRenderer& operator=(const ESDLRenderer&) = delete;
    ESDLRenderer& operator=(ESDLRenderer&& other);

    // Rendering

    void render(
        const ESClock::duration timeSinceInit
    ) override;
};
