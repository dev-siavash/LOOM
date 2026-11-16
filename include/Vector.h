/**
 * @file Vector.h
 * @brief 2D vector.
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <cmath> 

namespace LOOM::Math {
    /** @brief 2D vector or point. */
    struct Vector 
    { 
        /**
         * @var float y
         * Y component.
         */
        /** @brief X component. */
        float x, y;

        /** @brief Constructs the zero vector. */
        constexpr Vector() noexcept : x{0}, y{0} {} 
        /**
         * @brief Constructs a vector from components.
         * @param x X component.
         * @param y Y component.
         */
        constexpr Vector(float x, float y) noexcept : x{x}, y{y} {}; 

        /**
         * @brief Returns the vector's length.
         * @return Length.
         */
        float magnitude() const noexcept 
        { 
            return std::sqrt(x * x + y * y); 
        }
        /**
         * @brief Returns a unit-length copy, or the zero vector if the length is 0. Does not modify this vector.
         * @return Unit vector.
         */
        Vector normalized() const noexcept
        { 
            auto mag = magnitude();
            return (mag == 0.0f) ? Vector::zero() : Vector(x / mag, y / mag);
        }
        
        /** @brief Component-wise subtraction. */
        constexpr Vector operator-(const Vector& other) const noexcept
        {
            return Vector(this->x - other.x, this->y - other.y);
        }

        /** @brief Component-wise addition. */
        constexpr Vector operator+(const Vector& other) const noexcept
        {
            return Vector(this->x + other.x, this->y + other.y);
        }

        /** @brief Scales by a scalar. */
        constexpr Vector operator*(float value) const noexcept
        {
            return Vector(this->x * value, this->y * value);
        }

        /** @brief Divides by a scalar. */
        constexpr Vector operator/(float value) const noexcept
        {
            return Vector(this->x / value, this->y / value);
        }

        /** @brief Subtracts in place. */
        constexpr Vector& operator-=(const Vector& other) noexcept
        {
            *this = *this - other;
            return *this;
        }

        /** @brief Adds in place. */
        constexpr Vector& operator+=(const Vector& other) noexcept
        {
            *this = *this + other;
            return *this;
        }

        /** @brief Scales in place. */
        constexpr Vector& operator*=(float value) noexcept
        {
            *this = *this * value;
            return *this;
        }

        /** @brief Divides in place. */
        constexpr Vector& operator/=(float value) noexcept
        {
            *this = *this / value;
            return *this;
        }

        /** @brief Exact component-wise equality. */
        constexpr bool operator==(const Vector& other) const noexcept
        {
            return (this->x == other.x) && (this->y == other.y);
        }
        
        /** @brief (0, 1). */
        static constexpr Vector up()               noexcept { return {  0.0,  1.0 }; }
        /** @brief (0, -1). */
        static constexpr Vector down()             noexcept { return {  0.0, -1.0 }; }
        /** @brief (-1, 0). */
        static constexpr Vector left()             noexcept { return { -1.0,  0.0 }; }
        /** @brief (1, 0). */
        static constexpr Vector right()            noexcept { return {  1.0,  0.0 }; }
        /** @brief (1, 1). */
        static constexpr Vector one()              noexcept { return {  1.0,  1.0 }; }
        /** @brief (0, 0). */
        static constexpr Vector zero()             noexcept { return {  0.0,  0.0 }; }
        /** @brief Sprite pivot (0, 0): top-left. Pivots are in sprite space (origin top-left, y down). */
        static constexpr Vector pivotTopLeft()     noexcept { return {  0.0,  0.0 }; }
        /** @brief Sprite pivot (0.5, 0): top-center. */
        static constexpr Vector pivotTopCenter()   noexcept { return {  0.5,  0.0 }; }
        /** @brief Sprite pivot (1, 0): top-right. */
        static constexpr Vector pivotTopRight()    noexcept { return {  1.0,  0.0 }; }
        /** @brief Sprite pivot (0, 0.5): center-left. */
        static constexpr Vector pivotCenterLeft()  noexcept { return {  0.0,  0.5 }; }
        /** @brief Sprite pivot (0.5, 0.5): center. */
        static constexpr Vector pivotCenter()      noexcept { return {  0.5,  0.5 }; }
        /** @brief Sprite pivot (1, 0.5): center-right. */
        static constexpr Vector pivotCenterRight() noexcept { return {  1.0,  0.5 }; }
        /** @brief Sprite pivot (0, 1): bottom-left. */
        static constexpr Vector pivotBottomLeft()  noexcept { return {  0.0,  1.0 }; }
        /** @brief Sprite pivot (0.5, 1): bottom-center. */
        static constexpr Vector pivotDownCenter()  noexcept { return {  0.5,  1.0 }; }
        /** @brief Sprite pivot (1, 1): bottom-right. */
        static constexpr Vector pivotDownRight()   noexcept { return {  1.0,  1.0 }; }
    }; 
}

#endif