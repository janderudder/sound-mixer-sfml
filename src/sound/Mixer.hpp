#pragma once
#include <SFML/Audio.hpp>
#include <array>
#include "./SoundPriority.hpp"
#include "./SoundResource.hpp"
/**
 * A little mixer to have a fixed number of sf::Sounds
 * allocated once.
 *
 * update() should be called each frame.
 *
 * The template parameter is the maximum number of sounds playing
 * simultaneously.
 *
 * On play, a sf::SoundBuffer is tied to a sf::Sound and played.
 * That is, if there are stopped sounds or playing sounds with lesser
 * priority.
 */
template <std::size_t Channels_N>
struct Mixer final
{
    using counter_t = unsigned short;

    //* Handle type to wrap the sounds
    struct Handle {
        sf::Sound*      sound;
        SoundPriority   priority;
        counter_t       counter         = 0;
    };


    //* Mixer data
    std::array<sf::Sound, Channels_N>   mSounds;
    std::array<Handle, Channels_N>      mHandles;
    counter_t                           mCounter    = 0;


public:
    explicit Mixer() noexcept;

    // Sorts the handle array. Good to call each frame.
    void update();

    void play(const sf::SoundBuffer&, SoundPriority = SoundPriority::NORMAL);
    void play(const SoundResource&, SoundPriority);
    void play(const SoundResource&);

};


#include "./Mixer.impl.hpp"
