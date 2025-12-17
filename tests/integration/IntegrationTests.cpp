#include <map>
#include <set>
#include <string>
#include <gtest/gtest.h>

using namespace std;
// Interface for parameter access
struct IParameterProvider {
    virtual ~IParameterProvider() = default;
    virtual float getParam(const string& id) = 0;
};
// Simple Spy/Mock parameter provider
struct SpyParams : IParameterProvider {
    map<string, float> values;
    set<string> requested;
    float getParam(const string& id) override {
        requested.insert(id);
        if (values.count(id))
            return values[id];
        return 0.0f;
    }
};
TEST(Integration, UsesParamsAndChangesSignal) {
    // Arrange
    SpyParams params;
    params.values["mix"]        = 1.0f;
    params.values["bypass"]     = 0.0f;
    params.values["midGainDb"]  = 6.0f;
    params.values["amount"]     = 0.0f;
    params.values["randomness"] = 0.0f;
    DspCore core(/*eqModule*/, /*harmonicsModule*/, &params);

    auto input  = MakeSineBuffer(1000.0f, 48000, 512);
    auto output = input;
    // Act
    core.processBlock(output);
    // Assert: parameters were read
    EXPECT_TRUE(params.requested.count("mix") > 0);
    EXPECT_TRUE(params.requested.count("midGainDb") > 0);
    // Assert: signal was modified by EQ
    EXPECT_GT(Rms(output), Rms(input));
}
