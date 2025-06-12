#include <motion-calibration/motion_planner.h>

#include <gtest/gtest.h>

TEST(ForwardMotorCommandsTest, StopToForward) {
    double acceleration = 1.0;
    double steering = 0.0;

    MotionPlaner planner(State::STOP, Direction::NONE);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, DEFAULT_PWM + 10);
    ASSERT_EQ(mc.engine_right_pwm, DEFAULT_PWM + 10);
}

TEST(ForwardMotorCommandsTest, StopToForwardIncrease) {
    double acceleration = 1.0;
    double steering = 0.0;

    MotionPlaner planner(State::STOP, Direction::NONE);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, DEFAULT_PWM + 10);
    ASSERT_EQ(mc.engine_right_pwm, DEFAULT_PWM + 10);

    mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, DEFAULT_PWM + 20);
    ASSERT_EQ(mc.engine_right_pwm, DEFAULT_PWM + 20);
}

TEST(ForwardMotorCommandsTest, ForwardToForward) {
    double acceleration = 1.0;
    double steering = 0.0;

    MotionPlaner planner(State::MAINTAIN_SPEED, Direction::FORWARD);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, DEFAULT_PWM);
    ASSERT_EQ(mc.engine_right_pwm, DEFAULT_PWM);
}

TEST(ForwardMotorCommandsTest, ForwardToBackward) {
    double acceleration = -1.0;
    double steering = 0.0;

    MotionPlaner planner(State::MAINTAIN_SPEED, Direction::FORWARD);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, DEFAULT_PWM - 10);
    ASSERT_EQ(mc.engine_right_pwm, DEFAULT_PWM - 10);
}

TEST(ForwardMotorCommandsTest, ForwardToLeft) {
    double acceleration = 1.0;
    double steering = -1.0;

    MotionPlaner planner(State::MAINTAIN_SPEED, Direction::FORWARD);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, DEFAULT_PWM - 10);
    ASSERT_EQ(mc.engine_right_pwm, DEFAULT_PWM - 10);
}

TEST(ForwardMotorCommandsTest, ForwardToRight) {
    double acceleration = 1.0;
    double steering = 1.0;

    MotionPlaner planner(State::MAINTAIN_SPEED, Direction::FORWARD);

    auto mc = planner.do_plan(acceleration, steering);

    ASSERT_EQ(mc.engine_left_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_left_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_right_forward, LOW_SIGNAL);
    ASSERT_EQ(mc.engine_right_reverse, HIGH_SIGNAL);
    ASSERT_EQ(mc.engine_left_pwm, DEFAULT_PWM - 10);
    ASSERT_EQ(mc.engine_right_pwm, DEFAULT_PWM - 10);
}
