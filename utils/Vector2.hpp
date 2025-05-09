#ifndef VECTOR2
#define VECTOR2

#include "types.hpp"
#include <cmath>
#include <utility>

class Vector2{
private:
    f32 x = 0.f;
    f32 y = 0.f;

public:
    Vector2() = default;
    Vector2(const Vector2& vector) = default;
    Vector2(f32 x, f32 y) : x(x), y(y){};
    ~Vector2() = default;

    inline f32 magnitude() const{ return sqrtf32(x * x + y * y); }

    inline Vector2 vecTo(const Vector2& point) const{
        return {point.x - x, point.y - y};
    }

    inline Vector2 orthogonalVector() const {
        return { y, -x };
    }

    inline Vector2 WeightedMidPointTo(const Vector2& point, f32 weight) const{
        return {
            (1 - weight) * x + weight * point.x,
            (1 - weight) * y + weight * point.y
        };
    }

    inline Vector2 Unit() const{
        return { x / magnitude(), y / magnitude() };
    }

    inline Vector2 operator + (const Vector2& vector) const{
        return { x + vector.x, y + vector.y };
    }

    inline Vector2 operator * (f32 lambda) const{
        return { x * lambda, y * lambda };
    }

    inline void setX(f32 x_) { x = x_; };
    inline void setY(f32 y_) { y = y_; };

    inline f32 getX() const { return x; };
    inline f32 getY() const { return y; };
};

#endif
