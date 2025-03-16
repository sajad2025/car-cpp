#include "wpts.h"
#include <iostream>

Trajectory genWpts(const EgoConfig& cfg){
    // Debug output for configuration
    // std::cout << "Configuration values:" << std::endl;
    // std::cout << "duration = " << cfg.duration << std::endl;
    // std::cout << "dt = " << cfg.dt << std::endl;
    // std::cout << "acc_max = " << cfg.acc_max << std::endl;
    // std::cout << "steer_rate_max = " << cfg.steer_rate_max << std::endl;

    vector<State> state_t;
    vector<Control> control_t;
    vector<TrackingError> err_t;
    vector<double> time_vec;

    // Initial state
    State state_current{0, 0, 0, 0, 0};        // x, y, hdg, steer, vel
    Control ctrl_current{0, 0};                 // acc, steering_rate
    TrackingError err_current{0, 0, 0, 0};     // lat, long, hdg, steer
    double time_current = 0.0; 

    // Generate a trajectory with varying control inputs
    while (time_current < cfg.duration){
        time_current += cfg.dt;

        // Update control inputs based on time to create a meaningful trajectory
        if (time_current < 5.0) {
            // Accelerate
            ctrl_current.acc = cfg.acc_max;
            ctrl_current.steer_rate = 0;
        } else if (time_current < 10.0) {
            // Turn left
            ctrl_current.acc = 0;
            ctrl_current.steer_rate = cfg.steer_rate_max;
        } else if (time_current < 15.0) {
            // Turn right
            ctrl_current.acc = 0;
            ctrl_current.steer_rate = cfg.steer_rate_min;
        } else {
            // Decelerate
            ctrl_current.acc = cfg.acc_min;
            ctrl_current.steer_rate = 0;
        }

        state_current = nextState(state_current, ctrl_current, cfg);
        state_t.push_back(state_current);
        control_t.push_back(ctrl_current);
        err_t.push_back(err_current);
        time_vec.push_back(time_current);
    }

    // Debug output
    // std::cout << "Generated waypoints:" << std::endl;
    // std::cout << "Number of states: " << state_t.size() << std::endl;
    // std::cout << "Number of controls: " << control_t.size() << std::endl;
    // std::cout << "Number of errors: " << err_t.size() << std::endl;
    // std::cout << "Number of time points: " << time_vec.size() << std::endl;

    // if (!state_t.empty()) {
    //     std::cout << "First state: x=" << state_t[0].x << ", y=" << state_t[0].y << std::endl;
    //     std::cout << "Last state: x=" << state_t.back().x << ", y=" << state_t.back().y << std::endl;
    // }

    return Trajectory{state_t, control_t, err_t, time_vec};
}
