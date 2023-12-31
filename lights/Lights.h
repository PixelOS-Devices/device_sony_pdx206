/*
 * Copyright (C) 2020 The Android Open Source Project
 * Copyright (C) 2023 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/android/hardware/light/BnLights.h>

namespace aidl {
namespace android {
namespace hardware {
namespace light {

enum led_type {
    RED,
    GREEN,
    BLUE,
    NUM_LIGHTS,
};

class Lights : public BnLights {
  public:
    Lights();

    ndk::ScopedAStatus setLightState(int32_t id, const HwLightState& state) override;
    ndk::ScopedAStatus getLights(std::vector<HwLight>* lights) override;

  private:
    void setSpeakerLightLocked(const HwLightState& state);

    uint32_t getActualBrightness(led_type led, uint32_t value);
    bool setLedBlink(led_type led, uint32_t value, uint32_t onMs, uint32_t offMs);
    bool setLedBrightness(led_type led, uint32_t value);

    bool IsLit(uint32_t color);
    uint32_t ReadIntFromFile(const std::string& path, uint32_t defaultValue);
    bool WriteToFile(const std::string& path, uint32_t content);

    HwLightState mNotification;
    HwLightState mBattery;

    uint32_t mMaxBrightness[NUM_LIGHTS];
};

}  // namespace light
}  // namespace hardware
}  // namespace android
}  // namespace aidl
