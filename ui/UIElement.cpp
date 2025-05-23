#include "../ui/UIElement.hpp"

UIElement::UIElement(i32 x, i32 y, i32 w, i32 h)
: rect{ x, y, w, h}{}

UIElement::UIElement()
: rect{ 0, 0, 0, 0 }{}

UIElement::~UIElement(){}
