#pragma once

#pragma once

struct Vector2 {
    int x, y;
    Vector2() : x(0), y(0) {}
    Vector2(int x, int y) : x(x), y(y) {}
    inline Vector2 operator+(const Vector2& v) const { 
        return Vector2(x + v.x, y + v.y); 
    }
    inline Vector2 operator+=(const Vector2& v) const { 
        return Vector2(x + v.x, y + v.y); 
    }
    Vector2 operator-(const Vector2& v) const { 
        return Vector2(x - v.x, y - v.y); 
    }
    Vector2 operator*(const Vector2& v) const { 
        return Vector2(x * v.x, y * v.y); 
}
};