#include <motion-calibration/motion_planner.h>

#include <gtest/gtest.h>

TEST(MotorCommandsTest, ComplexCurveMotion) {
    double acceleration = 0.0;
    double steering = 0.0;

    MotionPlaner planner(State::STOP, Direction::NONE);
    
    // stop
    // forward
    // stop
    // left
    // stop
    // backward
    // stop
    // right
    // stop

    auto motor_commands = planner.do_plan(acceleration, steering);
}

