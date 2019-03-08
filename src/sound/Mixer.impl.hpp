#include "./Mixer.hpp"
#include <algorithm>


template <std::size_t Channels_N>
Mixer<Channels_N>::Mixer() noexcept
{
    // Initialize handles
    for (std::size_t i=0; i < mHandles.size(); ++i) {
        mHandles[i].sound = &mSounds[i];
        mHandles[i].priority = SoundPriority::FREE;
    }
}



template <std::size_t Channels_N>
void Mixer<Channels_N>::update()
{
    // Stopped sounds become free.
    for (auto& handle : mHandles) {
        if (handle.sound->getStatus() != sf::Sound::Playing)
            handle.priority = SoundPriority::FREE;
    }

    // Sort by [priority, count] to put usable handles at the begining of the array.
    std::sort(mHandles.begin(), mHandles.end(),
        [](const Handle& lhs, const Handle& rhs) {
            if (lhs.priority == rhs.priority)
                return lhs.counter < rhs.counter;
            return lhs.priority < rhs.priority;
    });
}



template <std::size_t Channels_N>
void Mixer<Channels_N>::play(const sf::SoundBuffer& buffer, SoundPriority priority)
{
    ++mCounter;

    // Find a handle with less priority than the sound we want to play,
    // set the buffer to it and play.
    for (auto& handle : mHandles) {
        if (handle.priority <= priority) {
            // play
            handle.sound->setBuffer(buffer);
            handle.sound->play();
            // update
            handle.priority = priority;
            handle.counter = mCounter;
            break;
        }
    }

}



template <std::size_t Channels_N>
void Mixer<Channels_N>::play(const SoundResource& resource, SoundPriority priority)
{
    ++mCounter;

    // Find a handle with less priority than the sound we want to play,
    // set the buffer to it and play.
    for (auto& handle : mHandles) {
        if (handle.priority <= priority) {
            handle.sound->setBuffer(resource.buffer);
            handle.sound->play();
            handle.priority = priority;
            handle.counter = mCounter;
            break;
        }
    }

}



template <std::size_t Channels_N>
void Mixer<Channels_N>::play(const SoundResource& resource)
{
    ++mCounter;

    // Find a handle with less priority than the sound we want to play,
    // set the buffer to it and play.
    for (auto& handle : mHandles) {
        if (handle.priority <= resource.priority) {
            handle.sound->setBuffer(resource.buffer);
            handle.sound->play();
            handle.priority = resource.priority;
            handle.counter = mCounter;
            break;
        }
    }

}
