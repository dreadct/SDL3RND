#pragma once

#include <d3d9.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../ERenderer.h"

class ED3D9Renderer: public ERenderer {
private:
    // Private properties
    LPDIRECT3D9 direct3D;
    LPDIRECT3DDEVICE9 device;

public:
    // Class lifecycle

    ED3D9Renderer() = delete;
    ED3D9Renderer(
        EAppWindowSPtr window
    );
    virtual ~ED3D9Renderer();

    ED3D9Renderer(const ED3D9Renderer&) = delete;
    ED3D9Renderer(ED3D9Renderer&& other);

    ED3D9Renderer& operator=(const ED3D9Renderer&) = delete;
    ED3D9Renderer& operator=(ED3D9Renderer&& other);

    // Rendering

    void render(
        const ESClock::duration timeSinceInit
    ) override;
};
