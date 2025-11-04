#include "ERendererFactory.h"

#include <cassert>

#include "../../app/window/EAppWindow.h"
#include "../ERenderer.h"
#include "../concrete/ED3D9Renderer.h"
#include "../concrete/ESDLRenderer.h"

// Class lifecycle

ERendererFactory::ERendererFactory(
    EAppWindowSPtr window
) : window(window) {
    assert(window);
}

ERendererFactory::ERendererFactory(
    ERendererFactory&& other
) : window(std::move(other.window)) {
}

ERendererFactory& ERendererFactory::operator=(
    ERendererFactory&& other
) {
    window = std::move(other.window);
    return *this;
}

// Factory methods

ERendererSPtr ERendererFactory::makeRenderer() const {
    #ifdef _WIN32
    return std::static_pointer_cast<ERenderer>(
        std::make_shared<ED3D9Renderer>(window)
    );
    #else
    return std::static_pointer_cast<ERenderer>(
        std::make_shared<ESDLRenderer>(window)
    );
    #endif
}
