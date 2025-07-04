#include <motion-calibration/motion_planner.h>

#include <gtest/gtest.h>

TEST(LeftMotorCommandsTest, FromStopToLeftExpectIncrease) {
    double acceleration = 0.0;
    double steering = -1.0;

    MotionPlanner planner(State::STOP, Direction::NONE, 0, 0, 0);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, PWM_STEP);
    ASSERT_EQ(mc.engine_right_pwm, PWM_STEP);
}

TEST(LeftMotorCommandsTest, FromLeftToLeftExpectMaintain) {
    double acceleration = 0.0;
    double steering = -1.0;

    MotionPlanner planner(State::MAINTAIN_SPEED, Direction::LEFT, PWM_MAX, PWM_MAX, PWM_DEFAULT);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, PWM_MAX);
    ASSERT_EQ(mc.engine_right_pwm, PWM_MAX);
}

TEST(LeftMotorCommandsTest, FromLeftToForwardExpectDecrease) {
    double acceleration = 1.0;
    double steering = 0.0;

    MotionPlanner planner(State::MAINTAIN_SPEED, Direction::LEFT, PWM_MAX, PWM_MAX, PWM_DEFAULT);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, PWM_MAX - PWM_STEP);
    ASSERT_EQ(mc.engine_right_pwm, PWM_MAX - PWM_STEP);
}

TEST(LeftMotorCommandsTest, FromLeftToBackwardExpectDecrease) {
    double acceleration = -1.0;
    double steering = 0.0;

    MotionPlanner planner(State::MAINTAIN_SPEED, Direction::LEFT, PWM_MAX, PWM_MAX, PWM_DEFAULT);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, PWM_MAX - PWM_STEP);
    ASSERT_EQ(mc.engine_right_pwm, PWM_MAX - PWM_STEP);
}

TEST(LeftMotorCommandsTest, FromLeftToRightExpectDecrease) {
    double acceleration = 0.0;
    double steering = 1.0;

    MotionPlanner planner(State::MAINTAIN_SPEED, Direction::LEFT, PWM_MAX, PWM_MAX, PWM_DEFAULT);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, PWM_MAX - PWM_STEP);
    ASSERT_EQ(mc.engine_right_pwm, PWM_MAX - PWM_STEP);
}

TEST(LeftMotorCommandsTest, FromIncreaseLeftToForwardExpectDecrease) {
    double acceleration = 1.0;
    double steering = 0.0;

    MotionPlanner planner(State::INCREASE_SPEED, Direction::LEFT, 2 * PWM_STEP, 2 * PWM_STEP, PWM_STEP);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, PWM_STEP);
    ASSERT_EQ(mc.engine_right_pwm, PWM_STEP);
}

TEST(LeftMotorCommandsTest, FromIncreaseLeftToBackwardExpectDecrease) {
    double acceleration = -1.0;
    double steering = 0.0;

    MotionPlanner planner(State::INCREASE_SPEED, Direction::LEFT, 2 * PWM_STEP, 2 * PWM_STEP, PWM_STEP);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, PWM_STEP);
    ASSERT_EQ(mc.engine_right_pwm, PWM_STEP);
}

TEST(LeftMotorCommandsTest, FromIncreaseLeftToRightExpectDecrease) {
    double acceleration = 0.0;
    double steering = 1.0;

    MotionPlanner planner(State::INCREASE_SPEED, Direction::LEFT, 2 * PWM_STEP, 2 * PWM_STEP, PWM_STEP);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, PWM_STEP);
    ASSERT_EQ(mc.engine_right_pwm, PWM_STEP);
}
