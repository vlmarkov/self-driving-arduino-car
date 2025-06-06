#include <main-pipeline/ros_module.h>

#include <path-planning/path_planning.h>
#include <obstacle-avoidance/obstacle_avoidance.h>
#include <lane-detection/ros_module.h>

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto main_pipeline = std::make_shared<MainPipeline>();

    //main_pipeline->add_module(PathPlanning::kName);
    main_pipeline->add_module(LaneDetection::kName);
    //main_pipeline->add_module(ObstacleAvoidance::kName);

    rclcpp::spin(main_pipeline);
    rclcpp::shutdown();

    return 0;
}
