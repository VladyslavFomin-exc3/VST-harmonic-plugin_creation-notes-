#include "Harmonics.h"
#include <algorithm>

float applyHarmonics(float sample, float amount, float randomness)
{
    if (amount <= 0.0f)
        return sample;

    float harmonic = sample * (amount / 100.0f);

    if (randomness > 0.0f)
        harmonic += randomness * 0.01f;

    float output = sample + harmonic;

    return std::clamp(output, -1.0f, 1.0f);
}
