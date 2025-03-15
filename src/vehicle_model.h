#ifndef VEHICLE_MODEL_H
#define VEHICLE_MODEL_H

#include <vector>

struct State {
    double x = 0;
    double y = 0;
    double hdg = 0;
    double vel = 0;
};

struct Control {
    double acc = 0;
    double steer = 0;
};

struct EgoConfig {
    double wheelbsae = 2.7;
    double velocity_max = 3;
    double velocity_min = -3;
    double acc_max = 2;
    double acc_min = -2;
    double steer_max = 0.5;
    double steer_min = -0.5;
    double dt = 0.1;
    double duration = 20.0; // sim
};

struct TrackingError {
    double lat = 0;
    double lng = 0;
    double hdg = 0;
};

State nextState(const State& current_state, const Control& control, const EgoConfig& config);
std::vector<State> trajectoryRollout(const State& initial_state, const std::vector<Control>& control_vec, const EgoConfig& config);

#endif // VEHICLE_MODEL_H 