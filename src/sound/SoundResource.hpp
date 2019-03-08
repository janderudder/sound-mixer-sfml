/**
 * The sound data.
 * It's just a wrapper around a sf::SoundBuffer,
 * adding the priority value.
 */
#pragma once
#include <SFML/Audio.hpp>
#include "./SoundPriority.hpp"


struct SoundResource final
{
    sf::SoundBuffer     buffer;
    SoundPriority       priority;


    SoundResource(SoundPriority prio = SoundPriority::NORMAL) noexcept
        : buffer    {}
        , priority  {prio}
    {}

    SoundResource(sf::SoundBuffer&& sb, SoundPriority prio = SoundPriority::NORMAL) noexcept
        : buffer    {std::move(sb)}
        , priority  {prio}
    {}

    SoundResource(const sf::SoundBuffer& sb, SoundPriority prio = SoundPriority::NORMAL) noexcept
        : buffer    {sb}
        , priority  {prio}
    {}
};
