#pragma once

#include <memory>

class EAppWindow;
typedef std::shared_ptr<EAppWindow> EAppWindowSPtr;

class ERenderer;
typedef std::shared_ptr<ERenderer> ERendererSPtr;

class ERendererFactory;
typedef std::shared_ptr<ERendererFactory> ERendererFactorySPtr;

class ERendererFactory {
private:
    // Private properties
    EAppWindowSPtr window;

public:
    // Class lifecycle

    ERendererFactory() = delete;
    ERendererFactory(
        EAppWindowSPtr window
    );
    virtual ~ERendererFactory() = default;

    ERendererFactory(const ERendererFactory&) = delete;
    ERendererFactory(ERendererFactory&& other);

    ERendererFactory& operator=(const ERendererFactory&) = delete;
    ERendererFactory& operator=(ERendererFactory&& other);

    // Factory methods

    ERendererSPtr makeRenderer() const;
};
