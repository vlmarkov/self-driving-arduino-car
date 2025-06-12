#pragma once

#include "motor_commands.h"

enum class State {STOP, INCREASE_SPEED, MAINTAIN_SPEED, DECREASE_SPEED };
enum class Direction {NONE, FORWARD, BACKWARD, LEFT, RIGHT };

class MotionPlaner {
public:
    MotionPlaner(State initial_state, Direction initial_direction);

    MotorCommands do_plan(double acceleration, double steering);

private:
    uint8_t counter{0};
    State state_{State::STOP};
    Direction direction_{Direction::NONE};
};
