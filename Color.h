#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

namespace LOOM::Utilities
{
    struct Color
    {
        uint8_t r, g, b, a;

        static constexpr Color black()   noexcept { return { 0, 0, 0, 255 }; }
        static constexpr Color gray()    noexcept { return { 128, 128, 128, 255 }; }
        static constexpr Color silver()  noexcept { return { 192, 192, 192, 255 }; }
        static constexpr Color white()   noexcept { return { 255, 255, 255, 255 }; }
        static constexpr Color navy()    noexcept { return { 0, 0, 128, 255 }; }
        static constexpr Color blue()    noexcept { return { 0, 0, 255, 255 }; }
        static constexpr Color teal()    noexcept { return { 0, 128, 128, 255 }; }
        static constexpr Color aqua()    noexcept { return { 0, 255, 255, 255 }; }
        static constexpr Color green()   noexcept { return { 0, 128, 0, 255 }; }
        static constexpr Color lime()    noexcept { return { 0, 255, 0, 255 }; }
        static constexpr Color olive()   noexcept { return { 128, 128, 0, 255 }; }
        static constexpr Color yellow()  noexcept { return { 255, 255, 0, 255 }; }
        static constexpr Color maroon()  noexcept { return { 128, 0, 0, 255 }; }
        static constexpr Color red()     noexcept { return { 255, 0, 0, 255 }; }
        static constexpr Color purple()  noexcept { return { 128, 0, 128, 255 }; }
        static constexpr Color fuchsia() noexcept { return { 255, 0, 255, 255 }; }
    };
}

#endif