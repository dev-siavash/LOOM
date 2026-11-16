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
    struct Text
    {
        enum class Alignment {Left, Right, Center};

        std::string text;
        std::string fontPath;
        int fontSize;
        Utilities::Color color;
        Alignment alignment;
        bool isStatic;
        size_t cacheKey;

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

        void SetText(const std::string& newText)
        {
            text = newText;
        }

        void MarkStatic()
        {
            isStatic = true;
        }
    };

    template<>
    struct FiberTraits<Text>
    {
        static constexpr bool Serializable = true;
        static constexpr bool IsTag = false;

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