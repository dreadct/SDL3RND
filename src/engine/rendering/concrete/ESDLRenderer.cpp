#include "ESDLRenderer.h"

#include <cassert>
#include <stdexcept>

#include "../../app/window/EAppWindow.h"

// Class lifecycle

ESDLRenderer::ESDLRenderer(
    EAppWindowSPtr window
) : ERenderer(window) {
    assert(window);

    // attempt to create a renderer
    if ((renderer = SDL_CreateRenderer(
        window->getSDLWindow(),
        nullptr
    )) == nullptr) {
        std::string error = "Failed to init SDL renderer: ";
        error += SDL_GetError();
        throw std::runtime_error(error);
    }
}

ESDLRenderer::~ESDLRenderer() {
    SDL_DestroyRenderer(renderer);
}

ESDLRenderer::ESDLRenderer(
    ESDLRenderer&& other
) : ERenderer(std::move(other)),
    renderer(std::move(other.renderer)) {
}

ESDLRenderer& ESDLRenderer::operator=(
    ESDLRenderer&& other
) {
    ERenderer::operator=(std::move(other));
    renderer = other.renderer;
    return *this;
}

// Rendering

void ESDLRenderer::render(
    const ESClock::duration timeSinceInit
) const {
    const auto secondSinceInit = (float)std::chrono::duration_cast<
        std::chrono::milliseconds
    >(timeSinceInit).count() / 1000.0f;

    const float red = (float) (0.5 + 0.5 * SDL_sin(secondSinceInit));
    const float green = (float) (0.5 + 0.5 * SDL_sin(secondSinceInit + SDL_PI_D * 2 / 3));
    const float blue = (float) (0.5 + 0.5 * SDL_sin(secondSinceInit + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}
