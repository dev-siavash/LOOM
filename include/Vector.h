#ifndef VECTOR_H
#define VECTOR_H

#include <cmath> 

namespace LOOM::Math {
    /**
     * Represents a 2D vector or point.
    */
    struct Vector 
    { 
        float x, y;

        constexpr Vector() noexcept : x{0}, y{0} {} 
        constexpr Vector(float x, float y) noexcept : x{x}, y{y} {}; 

        /**
         * Returns this vector's magnitude.
        */
        float magnitude() const noexcept 
        { 
            return std::sqrt(x * x + y * y); 
        }
        /**
         * Returns normalized version of this vector, keeping the direction but changing its magnitude to one.
         * Note that this does not change this vector but returns a new one.
         * If you want to normalize this vector call Normalize().
        */
        Vector normalized() const noexcept
        { 
            auto mag = magnitude();
            return (mag == 0.0f) ? Vector::zero() : Vector(x / mag, y / mag);
        }
        
        constexpr Vector operator-(const Vector& other) const noexcept
        {
            return Vector(this->x - other.x, this->y - other.y);
        }

        constexpr Vector operator+(const Vector& other) const noexcept
        {
            return Vector(this->x + other.x, this->y + other.y);
        }

        constexpr Vector operator*(float value) const noexcept
        {
            return Vector(this->x * value, this->y * value);
        }

        constexpr Vector operator/(float value) const noexcept
        {
            return Vector(this->x / value, this->y / value);
        }

        constexpr Vector& operator-=(const Vector& other) noexcept
        {
            *this = *this - other;
            return *this;
        }

        constexpr Vector& operator+=(const Vector& other) noexcept
        {
            *this = *this + other;
            return *this;
        }

        constexpr Vector& operator*=(float value) noexcept
        {
            *this = *this * value;
            return *this;
        }

        constexpr Vector& operator/=(float value) noexcept
        {
            *this = *this / value;
            return *this;
        }

        constexpr bool operator==(const Vector& other) const noexcept
        {
            return (this->x == other.x) && (this->y == other.y);
        }
        
        static constexpr Vector up()               noexcept { return {  0.0,  1.0 }; }
        static constexpr Vector down()             noexcept { return {  0.0, -1.0 }; }
        static constexpr Vector left()             noexcept { return { -1.0,  0.0 }; }
        static constexpr Vector right()            noexcept { return {  1.0,  0.0 }; }
        static constexpr Vector one()              noexcept { return {  1.0,  1.0 }; }
        static constexpr Vector zero()             noexcept { return {  0.0,  0.0 }; }
        static constexpr Vector pivotTopLeft()     noexcept { return {  0.0,  0.0 }; }
        static constexpr Vector pivotTopCenter()   noexcept { return {  0.5,  0.0 }; }
        static constexpr Vector pivotTopRight()    noexcept { return {  1.0,  0.0 }; }
        static constexpr Vector pivotCenterLeft()  noexcept { return {  0.0,  0.5 }; }
        static constexpr Vector pivotCenter()      noexcept { return {  0.5,  0.5 }; }
        static constexpr Vector pivotCenterRight() noexcept { return {  1.0,  0.5 }; }
        static constexpr Vector pivotBottomLeft()  noexcept { return {  0.0,  1.0 }; }
        static constexpr Vector pivotDownCenter()  noexcept { return {  0.5,  1.0 }; }
        static constexpr Vector pivotDownRight()   noexcept { return {  1.0,  1.0 }; }
    }; 
}

#endif