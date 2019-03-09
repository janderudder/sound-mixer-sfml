```cpp
// Sound data (SFML code)
sf::SoundBuffer buffer0, buffer1;

// A sound resource
SoundResource sound0 {buffer0, SoundPriority::HIGH};

// Initialize the mixer: the template parameter is the number of channels
Mixer<16> mixer;

// Play the resource
mixer.play(sound0);

// Play the sound buffer at low priority
mixer.play(buffer1, SoundPriority::LOW)

// Once per frame (bookkeeping)
mixer.update();
```
