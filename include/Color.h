/**
 * @file Color.h
 * @brief RGBA color.
 */
#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

namespace LOOM::Utilities
{
    /** @brief 8-bit RGBA color with named opaque presets. */
    struct Color
    {
        /**
         * @var uint8_t g
         * Green channel (0-255).
         */
        /**
         * @var uint8_t b
         * Blue channel (0-255).
         */
        /**
         * @var uint8_t a
         * Alpha channel (0-255); 255 is opaque.
         */
        /** @brief Red channel (0-255). */
        uint8_t r, g, b, a;

        /** @brief Opaque black (0, 0, 0). */
        static constexpr Color black()   noexcept { return { 0, 0, 0, 255 }; }
        /** @brief Opaque gray (128, 128, 128). */
        static constexpr Color gray()    noexcept { return { 128, 128, 128, 255 }; }
        /** @brief Opaque silver (192, 192, 192). */
        static constexpr Color silver()  noexcept { return { 192, 192, 192, 255 }; }
        /** @brief Opaque white (255, 255, 255). */
        static constexpr Color white()   noexcept { return { 255, 255, 255, 255 }; }
        /** @brief Opaque navy (0, 0, 128). */
        static constexpr Color navy()    noexcept { return { 0, 0, 128, 255 }; }
        /** @brief Opaque blue (0, 0, 255). */
        static constexpr Color blue()    noexcept { return { 0, 0, 255, 255 }; }
        /** @brief Opaque teal (0, 128, 128). */
        static constexpr Color teal()    noexcept { return { 0, 128, 128, 255 }; }
        /** @brief Opaque aqua (0, 255, 255). */
        static constexpr Color aqua()    noexcept { return { 0, 255, 255, 255 }; }
        /** @brief Opaque green (0, 128, 0). */
        static constexpr Color green()   noexcept { return { 0, 128, 0, 255 }; }
        /** @brief Opaque lime (0, 255, 0). */
        static constexpr Color lime()    noexcept { return { 0, 255, 0, 255 }; }
        /** @brief Opaque olive (128, 128, 0). */
        static constexpr Color olive()   noexcept { return { 128, 128, 0, 255 }; }
        /** @brief Opaque yellow (255, 255, 0). */
        static constexpr Color yellow()  noexcept { return { 255, 255, 0, 255 }; }
        /** @brief Opaque maroon (128, 0, 0). */
        static constexpr Color maroon()  noexcept { return { 128, 0, 0, 255 }; }
        /** @brief Opaque red (255, 0, 0). */
        static constexpr Color red()     noexcept { return { 255, 0, 0, 255 }; }
        /** @brief Opaque purple (128, 0, 128). */
        static constexpr Color purple()  noexcept { return { 128, 0, 128, 255 }; }
        /** @brief Opaque fuchsia (255, 0, 255). */
        static constexpr Color fuchsia() noexcept { return { 255, 0, 255, 255 }; }
    };
}

#endif