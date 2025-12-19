Feature: VST Harmonic EQ Plugin - Smoke E2E

  Background:
    Given the DAW project is opened
    And the plugin "VST Harmonic EQ Plugin" is inserted on an audio track
    And the sample rate is 48000 Hz
    And the buffer size is 512 samples

  Scenario: Audio is processed when bypass is OFF (R1.1)
    Given bypass is set to OFF
    When I play a 1 kHz sine test signal for 5 seconds
    Then the output signal should be different from the input signal

  Scenario: Mix controls dry/wet blend (R1.3)
    Given bypass is set to OFF
    When mix is set to 0 percent
    And I play a 1 kHz sine test signal for 5 seconds
    Then the output signal should be approximately equal to the input signal
    When mix is set to 100 percent
    And I play a 1 kHz sine test signal for 5 seconds
    Then the output signal should be different from the input signal

  Scenario: Mid Gain affects the signal (R1.2)
    Given bypass is set to OFF
    When mid gain is set to 0 dB
    And I play a 1 kHz sine test signal for 5 seconds
    Then I save the output as "out_mid_0db.wav"
    When mid gain is set to +6 dB
    And I play a 1 kHz sine test signal for 5 seconds
    Then I save the output as "out_mid_plus6db.wav"
    And the RMS of "out_mid_plus6db.wav" should be greater than the RMS of "out_mid_0db.wav"
