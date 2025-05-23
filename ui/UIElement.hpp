#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include <SDL2/SDL.h>
#include "../utils/types.hpp"

class UIElement{
protected:
    SDL_Rect rect;

public:
    UIElement();
    UIElement(i32 x, i32 y, i32 w, i32 h);
    ~UIElement();

    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* ren) const = 0;
};

#endif
