/**
 * @file Text.h
 * @brief Text fiber.
 */
#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "Color.h"
#include "InternalFunctions.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
#include "FiberTraits.h"

namespace LOOM::Fibers
{
    /**
     * @brief Text drawn at the tow's Transform. Requires Transform.
     *
     * Rendered to a cached texture, rebuilt when text, font or color change.
     */
    struct Text
    {
        /** @brief Horizontal anchoring relative to the Transform position. */
        enum class Alignment {Left, Right, Center};

        /** @brief Displayed string (UTF-8). */
        std::string text;
        /** @brief TrueType font file path. */
        std::string fontPath;
        /** @brief Font size in points. */
        int fontSize;
        /** @brief Text color. */
        Utilities::Color color;
        /** @brief Horizontal alignment. */
        Alignment alignment;
        /** @brief When true the texture is never regenerated; see MarkStatic(). */
        bool isStatic;
        /** @brief (Internal) Key of the cached texture. */
        size_t cacheKey;

        /**
         * @brief Constructs a text fiber.
         * @param text String to display.
         * @param fontPath Font file path.
         * @param fontSize Size in points.
         * @param color Text color.
         * @param alignment Horizontal alignment.
         */
        Text(
            std::string text = "New Text",
            std::string fontPath = "",
            int fontSize = 24,
            Utilities::Color color = Utilities::Color::white(),
            Alignment alignment = Alignment::Center)
            : text{ text }, fontPath{ fontPath }, fontSize{ fontSize }, color{ color }, alignment{ alignment } 
        {
            isStatic = false;
            cacheKey = 0;
        }

        /**
         * @brief Replaces the displayed string.
         * @param newText New string.
         */
        void SetText(const std::string& newText)
        {
            text = newText;
        }

        /** @brief Freezes the rendered texture to save re-rendering; use for text that never changes. */
        void MarkStatic()
        {
            isStatic = true;
        }
    };

    /** @brief Serialization traits for Text. */
    template<>
    struct FiberTraits<Text>
    {
        /** @brief True if the type can be stored in prefabs. */
        static constexpr bool Serializable = true;
        /** @brief True if the type is a payload-free marker. */
        static constexpr bool IsTag = false;

        /** @brief Writes the fiber to a BinaryWriter. */
        static void Save(InternalUtilities::BinaryWriter& writer, const Text& t)
        {
            writer.Write(t.text);
            writer.Write(t.fontPath);
            writer.Write(t.fontSize);
            writer.Write(t.color.r);
            writer.Write(t.color.g);
            writer.Write(t.color.b);
            writer.Write(t.color.a);
            writer.Write(t.alignment);
        }

        /** @brief Reads the fiber from a BinaryReader. */
        static Text Load(InternalUtilities::BinaryReader& reader)
        {
            Text t;
            reader.Read(t.text);
            reader.Read(t.fontPath);
            reader.Read(t.fontSize);
            reader.Read(t.color.r);
            reader.Read(t.color.g);
            reader.Read(t.color.b);
            reader.Read(t.color.a);
            reader.Read(t.alignment);
            return t;
        }
    };
}

#endif