#include <motion-calibration/motion_planner.h>

namespace {

MotorCommands foward_command()
{
    MotorCommands mc;

    mc.engine_left_forward  = LOW_SIGNAL;
    mc.engine_left_reverse  = HIGH_SIGNAL;
    mc.engine_right_forward = LOW_SIGNAL;
    mc.engine_right_reverse = HIGH_SIGNAL;

    mc.engine_left_pwm = DEFAULT_PWM;
    mc.engine_right_pwm = DEFAULT_PWM;

    return mc;
}

MotorCommands backward_command()
{
    MotorCommands mc;

    mc.engine_left_forward  = HIGH_SIGNAL;
    mc.engine_left_reverse  = LOW_SIGNAL;
    mc.engine_right_forward = HIGH_SIGNAL;
    mc.engine_right_reverse = LOW_SIGNAL;

    mc.engine_left_pwm = DEFAULT_PWM;
    mc.engine_right_pwm = DEFAULT_PWM;

    return mc;
}

MotorCommands left_command()
{
    MotorCommands mc;

    mc.engine_left_forward  = HIGH_SIGNAL; // backward
    mc.engine_left_reverse  = LOW_SIGNAL;  // backward
    mc.engine_right_forward = LOW_SIGNAL;  // forward
    mc.engine_right_reverse = HIGH_SIGNAL; // forward

    mc.engine_left_pwm = DEFAULT_PWM;
    mc.engine_right_pwm = DEFAULT_PWM;

    return mc;
}

MotorCommands right_command()
{
    MotorCommands mc;

    mc.engine_left_forward  = LOW_SIGNAL;  // forward
    mc.engine_left_reverse  = HIGH_SIGNAL; // forward
    mc.engine_right_forward = HIGH_SIGNAL; // backward
    mc.engine_right_reverse = LOW_SIGNAL;  // backward

    mc.engine_left_pwm = DEFAULT_PWM;
    mc.engine_right_pwm = DEFAULT_PWM;

    return mc;
}

Direction acceleration2direction(double acceleration)
{
    if (acceleration > 0.0)
        return Direction::FORWARD;
    if (acceleration < 0.0)
        return Direction::BACKWARD;
    return Direction::NONE;
}

Direction steering2direction(double steering)
{
    if (steering > 0.0)
        return Direction::RIGHT;
    if (steering < 0.0)
        return Direction::LEFT;
    return Direction::NONE;
}

/*
NONE -> NONE -> STOP
FORWARD -> FORWARD -> MAINTAIN_SPEED
BACKWARD -> BACKWARD -> MAINTAIN_SPEED
LEFT -> LEFT -> MAINTAIN_SPEED
RIGHT -> RIGHT -> MAINTAIN_SPEED

NONE -> FORWARD -> INCREASE_SPEED
NONE -> BACKWARD -> INCREASE_SPEED
NONE -> LEFT -> INCREASE_SPEED
NONE -> RIGHT -> INCREASE_SPEED

FORWARD -> BACKWARD -> DECREASE_SPEED
FORWARD -> LEFT -> DECREASE_SPEED
FORWARD -> RIGHT -> DECREASE_SPEED

BACKWARD -> FORWARD -> DECREASE_SPEED
BACKWARD -> LEFT -> DECREASE_SPEED
BACKWARD -> RIGHT -> DECREASE_SPEED

LEFT -> FORWARD -> DECREASE_SPEED
LEFT -> BACKWARD -> DECREASE_SPEED
LEFT -> RIGHT -> DECREASE_SPEED

RIGHT -> FORWARD -> DECREASE_SPEED
RIGHT -> BACKWARD -> DECREASE_SPEED
RIGHT -> LEFT -> DECREASE_SPEED


DECREASE_SPEED ? -> STOP
INCREASE_SPEED ? -> MAINTAIN_SPEED

*/

State transit_state(Direction prev_dir, Direction new_dir, State prev_state, uint8_t& counter) {
    if (prev_dir != new_dir) {
        if (prev_dir == Direction::NONE) {
            return State::INCREASE_SPEED;
        }
        return State::DECREASE_SPEED;
    }

    if (prev_dir == Direction::NONE) {
        counter = 0;
        return State::STOP;
    }

    if (counter == 10) {
        counter = 0;
        if (prev_state == State::INCREASE_SPEED)
            return State::MAINTAIN_SPEED;
        return State::STOP;
    }

    return prev_state;
}

} // namespace

MotionPlaner::MotionPlaner(State initial_state, Direction initial_direction)
    : state_(initial_state)
    , direction_(initial_direction)
{}

MotorCommands MotionPlaner::do_plan(double acceleration, double steering)
{
    // TODO: what about forward+left, forward+right complex command?
    auto new_direction = acceleration2direction(acceleration);
    if (steering != 0.0)
        new_direction = steering2direction(steering);

    state_ = transit_state(direction_, new_direction, state_, counter);
    if (direction_ == Direction::NONE)
        direction_ = new_direction;

    if (state_ == State::STOP) {
        direction_ = Direction::NONE;
        return {};
    }

    MotorCommands mc;
    if (direction_ == Direction::FORWARD)
        mc = foward_command();
    if (direction_ == Direction::BACKWARD)
        mc = backward_command();
    if (direction_ == Direction::LEFT)
        mc = left_command();
    if (direction_ == Direction::RIGHT)
        mc = right_command();

    if (state_ == State::INCREASE_SPEED) {
        counter += 1;
        mc.engine_left_pwm += (10 * counter);
        mc.engine_right_pwm += (10 * counter);
    }

    if (state_ == State::DECREASE_SPEED) {
        counter += 1;
        mc.engine_left_pwm -= (10 * counter);
        mc.engine_right_pwm -= (10 * counter);
    }

    return mc;
}
