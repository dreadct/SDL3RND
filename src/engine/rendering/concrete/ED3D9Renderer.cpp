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
) : ERenderer(window),
    isDeviceLost(false) {
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
    device(std::exchange(other.device, nullptr)),
    isDeviceLost(std::exchange(other.isDeviceLost, false)) {
    memcpy_s(
        &d3dpp, sizeof(D3DPRESENT_PARAMETERS),
        &other.d3dpp, sizeof(D3DPRESENT_PARAMETERS)
    );
    ZeroMemory(&other.d3dpp, sizeof(D3DPRESENT_PARAMETERS));
}

ED3D9Renderer& ED3D9Renderer::operator=(
    ED3D9Renderer&& other
) {
    ERenderer::operator=(std::move(other));
    direct3D = std::exchange(other.direct3D, nullptr);
    device = std::exchange(other.device, nullptr);
    isDeviceLost = std::exchange(other.isDeviceLost, false);
    memcpy_s(
        &d3dpp, sizeof(D3DPRESENT_PARAMETERS),
        &other.d3dpp, sizeof(D3DPRESENT_PARAMETERS)
    );
    ZeroMemory(&other.d3dpp, sizeof(D3DPRESENT_PARAMETERS));
    return *this;
}

// Rendering

void ED3D9Renderer::render(
    const ESClock::duration timeSinceInit
) {
    // ensure device is capable to work
    HRESULT hResult = device->TestCooperativeLevel();
    switch (hResult) {
    case D3DERR_DEVICELOST:
        // skip rendering on lost device
        return;
    case D3DERR_DEVICENOTRESET:
        recoverLostDevice();
        break;
    default:
        if (FAILED(hResult)) {
            std::string errorFormat = "D3D9 renderer has a failed device state (0x%08X)";
            std::string errorDesc;
            if (getHResultErrorDescription(hResult, &errorDesc)) {
                errorFormat += ": " + errorDesc;
            }
            SDL_LogError(
                SDL_LOG_CATEGORY_RENDER,
                errorFormat.c_str(),
                hResult
            );
        }
    }

    const auto secondSinceInit = (float)std::chrono::duration_cast<
        std::chrono::milliseconds
    >(timeSinceInit).count() / 1000.0f;

    const uint8_t red = (uint8_t)((float) (0.5 + 0.5 * SDL_sin(secondSinceInit)) * 255.0f);
    const uint8_t green = (uint8_t)((float) (0.5 + 0.5 * SDL_sin(secondSinceInit + SDL_PI_D * 2 / 3)) * 255.0f);
    const uint8_t blue = (uint8_t)((float) (0.5 + 0.5 * SDL_sin(secondSinceInit + SDL_PI_D * 4 / 3)) * 255.0f);

    if (FAILED(hResult = device->Clear(
        0,
        nullptr,
        D3DCLEAR_TARGET,
        D3DCOLOR_XRGB(red, green, blue),
        1.0f,
        0
    ))) {
        std::string errorFormat = "D3D9 renderer failed to clear screen (0x%08X)";
        std::string errorDesc;
        if (getHResultErrorDescription(hResult, &errorDesc)) {
            errorFormat += ": " + errorDesc;
        }
        SDL_LogError(
            SDL_LOG_CATEGORY_RENDER,
            errorFormat.c_str(),
            hResult
        );
    }

    if (FAILED(hResult = device->BeginScene())) {
        std::string errorFormat = "D3D9 renderer failed to begin scene (0x%08X)";
        std::string errorDesc;
        if (getHResultErrorDescription(hResult, &errorDesc)) {
            errorFormat += ": " + errorDesc;
        }
        SDL_LogError(
            SDL_LOG_CATEGORY_RENDER,
            errorFormat.c_str(),
            hResult
        );
    }

    if (FAILED(hResult = device->EndScene())) {
        std::string errorFormat = "D3D9 renderer failed to end scene (0x%08X)";
        std::string errorDesc;
        if (getHResultErrorDescription(hResult, &errorDesc)) {
            errorFormat += ": " + errorDesc;
        }
        SDL_LogError(
            SDL_LOG_CATEGORY_RENDER,
            errorFormat.c_str(),
            hResult
        );
    }

    if (FAILED(hResult = device->Present(
        nullptr,
        nullptr,
        NULL,
        nullptr
    ))) {
        std::string errorFormat = "D3D9 renderer failed to present scene (0x%08X)";
        std::string errorDesc;
        if (getHResultErrorDescription(hResult, &errorDesc)) {
            errorFormat += ": " + errorDesc;
        }
        SDL_LogError(
            SDL_LOG_CATEGORY_RENDER,
            errorFormat.c_str(),
            hResult
        );
    }
}

// State management methods

void ED3D9Renderer::recoverLostDevice() {
    freeManagedResources();

    HRESULT hResult = D3D_OK;
    if (FAILED(hResult = device->Reset(&d3dpp))) {
        std::string error = "D3D9 renderer failed to reset device";
        std::string errorDesc;
        if (getHResultErrorDescription(hResult, &errorDesc)) {
            error += ": " + errorDesc;
        }
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, error.c_str());
    }

    acquireManagedResources();
}

// Resources management methods

void ED3D9Renderer::acquireManagedResources() {
}

void ED3D9Renderer::freeManagedResources() {
}
