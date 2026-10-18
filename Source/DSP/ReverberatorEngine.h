#pragma once
#include <cmath>

using namespace std;

class ReverberatorEngine {
private:
    void updatePreDelaySamples() noexcept {
        preDelaySamples = static_cast<int>((currentPreDelayMs * 0.001f) * static_cast<float>(currentSampleRate));
    }

    double currentSampleRate = 44100.0;

    float dryGain = 1.0f;
    float wetGain = 0.5f;
    float currentPreDelayMs = 20.0f;
    int preDelaySamples = 0;
    float feedback = 0.84f;

    float x1[2] = {0.0f, 0.0f};
    float y1[2] = {0.0f, 0.0f};

public:
    ReverberatorEngine() = default;

    void prepare(double sampleRate) noexcept {
        currentSampleRate = sampleRate;
    }

    void reset() noexcept {
        fill(begin(x1), end(x1), 0.0f);
        fill(begin(y1), end(y1), 0.0f);
    }

    inline float processSample(float input, int channel) noexcept {
        return 0.0f;
    }

    void processBlock(float *left, float *right, int numSamples) noexcept {
        for (int i = 0; i < numSamples; ++i) {
            left[i] = processSample(left[i], 0);
            right[i] = processSample(right[i], 0);
        }
    }

    void setSampleRate(double newSampleRate) noexcept {
        currentSampleRate = (newSampleRate > 0.0) ? newSampleRate : 44100.0;
        updatePreDelaySamples();
    }

    void setDry(float dryPercent) noexcept {
        dryGain = std::clamp(dryPercent * 0.01f, 0.0f, 1.0f);
    }

    void setWet(float wetPercent) noexcept {
        wetGain = std::clamp(wetPercent * 0.01f, 0.0f, 1.0f);
    }

    void setPreDelay(float preDelayMs) noexcept {
        currentPreDelayMs = std::max(0.0f, preDelayMs);
        updatePreDelaySamples();
    }

    void setRoomSize(float roomPercent) noexcept {
        const float norm = std::clamp(roomPercent * 0.01f, 0.0f, 1.0f);
        feedback = 0.7f + (norm * 0.28f);
    }
};