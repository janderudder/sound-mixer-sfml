#pragma once
/**
 * Priority for a SoundResource or a Mixer::Handle.
 * Used to decide if playing a sound should stop another
 * sound when the mixer is full.
 */
enum class SoundPriority {
    FREE, LOW, NORMAL, HIGH, VERY_HIGH
};
