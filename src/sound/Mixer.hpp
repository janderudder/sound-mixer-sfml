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
class Mixer final
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

    // Sorts the handle array. Supposed to be called each frame.
    void update();

    // Play a sf::SoundBuffer, which doesn't know about priority
    void play(const sf::SoundBuffer&, SoundPriority = SoundPriority::NORMAL);

    // Play a SoundResource with a custom priority
    void play(const SoundResource&, SoundPriority);

    // Play a SoundResource with its built-in priority
    void play(const SoundResource&);


private:
    // Called only from other methods (this is the core method that plays a sound)
    inline void _playBuffer(const sf::SoundBuffer&, const SoundPriority&) noexcept;


};

// Implementation file:
#include "./Mixer.impl.hpp"
