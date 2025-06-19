#pragma once

#include <cstdint>

constexpr auto HIGH_SIGNAL = true;
constexpr auto LOW_SIGNAL = false;

constexpr auto DEFAULT_PWM = 0;
constexpr auto PWM_STEP = 10;
constexpr auto MAX_PWM_STEPS = 7;

struct MotorCommands {
    bool engine_left_forward{LOW_SIGNAL};
    bool engine_left_reverse{LOW_SIGNAL};

    bool engine_right_forward{LOW_SIGNAL};
    bool engine_right_reverse{LOW_SIGNAL};

    uint8_t engine_left_pwm{0};
    uint8_t engine_right_pwm{0};
};
