#pragma once

class IRenderer;

class IDrawable {
public:
    virtual ~IDrawable() = default;

    virtual void onDraw(const IRenderer& renderer) const = 0;
};