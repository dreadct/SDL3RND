#include "ED3D9Renderer.h"

#include <cassert>
#include <stdexcept>
#include <utility>

#include "../../app/window/EAppWindow.h"
#include "../../displays/EDisplay.h"
#include "../../platform/windows/HResultUtils.h"

// Class lifecycle

ED3D9Renderer::ED3D9Renderer(
    EAppWindowSPtr window
) : ERenderer(window) {
    assert(window);

    // get window HWND
    HWND hWnd = 0;
    auto properties = window->getProperties();
    if ((hWnd = (HWND)SDL_GetPointerProperty(
        properties,
        SDL_PROP_WINDOW_WIN32_HWND_POINTER,
        nullptr
    )) == nullptr) {
        throw std::runtime_error("Failed to get a given window handle (HWND)");
    }

    // get window size
    auto [width, height] = window->getSize();

    // attempt to create a D3D9
    if ((direct3D = Direct3DCreate9(
        D3D_SDK_VERSION
    )) == nullptr) {
        throw std::runtime_error("Failed to init D3D9");
    }

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = (UINT)width;
	d3dpp.BackBufferHeight = (UINT)height;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.Windowed = !window->isFullscreen();

    // get window adapter
    auto d3dAdapter = D3DADAPTER_DEFAULT;
    EDisplaySPtr display;
    if ((display = window->getDisplay())) {
        d3dAdapter = display->getDisplayID() - 1;
    }

    // attempt to create device
    HRESULT hResult = D3D_OK;
    if (FAILED((hResult = direct3D->CreateDevice(
        d3dAdapter,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &device
    )))) {
        std::string error = "Failed to init D3D9 device";
        std::string description;
        if (getHResultErrorDescription(hResult, &description)) {
            error += ": " + description;
        }
        throw std::runtime_error(error);
    }
}

ED3D9Renderer::~ED3D9Renderer() {
    if (device) {
        device->Release();
        device = nullptr;
    }
    if (direct3D) {
        direct3D->Release();
        direct3D = nullptr;
    }
}

ED3D9Renderer::ED3D9Renderer(
    ED3D9Renderer&& other
) : ERenderer(std::move(other)),
    direct3D(std::exchange(other.direct3D, nullptr)),
    device(std::exchange(other.device, nullptr)) {
}

ED3D9Renderer& ED3D9Renderer::operator=(
    ED3D9Renderer&& other
) {
    ERenderer::operator=(std::move(other));
    direct3D = std::exchange(other.direct3D, nullptr);
    device = std::exchange(other.device, nullptr);
    return *this;
}

// Rendering

void ED3D9Renderer::render(
    const ESClock::duration timeSinceInit
) {
    const auto secondSinceInit = (float)std::chrono::duration_cast<
        std::chrono::milliseconds
    >(timeSinceInit).count() / 1000.0f;

    const uint8_t red = (uint8_t)((float) (0.5 + 0.5 * SDL_sin(secondSinceInit)) * 255.0f);
    const uint8_t green = (uint8_t)((float) (0.5 + 0.5 * SDL_sin(secondSinceInit + SDL_PI_D * 2 / 3)) * 255.0f);
    const uint8_t blue = (uint8_t)((float) (0.5 + 0.5 * SDL_sin(secondSinceInit + SDL_PI_D * 4 / 3)) * 255.0f);

    device->Clear();
        0,
        nullptr,
        D3DCLEAR_TARGET,
        D3DCOLOR_XRGB(red, green, blue),
        1.0f,
        0
    );

    device->BeginScene();

    device->EndScene();

    device->Present(
        nullptr,
        nullptr,
        NULL,
        nullptr
    );
}
