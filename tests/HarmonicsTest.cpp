#include "Harmonics.h"
#include <cassert>

void testZeroAmountKeepsSignal()
{
    float input = 0.5f;
    float output = applyHarmonics(input, 0.0f, 0.0f);
    assert(output == input);
}

void testOutputDoesNotClip()
{
    float output = applyHarmonics(0.9f, 100.0f, 0.0f);
    assert(output <= 1.0f && output >= -1.0f);
}

int main()
{
    testZeroAmountKeepsSignal();
    testOutputDoesNotClip();
    return 0;
}
