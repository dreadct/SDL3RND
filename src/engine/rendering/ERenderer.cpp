#include "ERenderer.h"

#include <cassert>

ERenderer::ERenderer(
    EAppWindowSPtr window
) : window(window) {
    assert(window);
}

ERenderer::ERenderer(
    ERenderer&& other
) : window(std::move(other.window)) {
}

ERenderer& ERenderer::operator=(
    ERenderer&& other
) {
    window = std::move(other.window);
    return *this;
}

// Protected methods

EAppWindowWPtr ERenderer::getWindow() const {
    return window;
}
