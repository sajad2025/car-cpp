#ifndef VEHICLE_MODEL_H
#define VEHICLE_MODEL_H

#include <vector>

struct Position{
    double x;
    double y;
};

struct State {
    double x;
    double y;
    double hdg;
    double steer;
    double vel;
    State(double x=0, double y=0, double hdg=0, double steer=0, double vel=0) : x(x), y(y), hdg(hdg), steer(steer), vel(vel) {}
};

struct Control {
    double acc;
    double steer_rate;
    Control(double acc=0, double steer_rate=0) : acc(acc), steer_rate(steer_rate) {}
};

struct EgoConfig {
    double wheelbsae = 2.7;
    double velocity_max = 30; // m/s
    double velocity_min = -3; // m/s
    double acc_max = 4; // m/s^2
    double acc_min = -4; // m/s^2
    double steer_max = 0.5; // rad
    double steer_min = -0.5; // rad
    double steer_rate_max = 0.5; // rad/s
    double steer_rate_min = -0.5; // rad/s
    double dt = 0.01; // s
    double duration = 20.0; // sim
};

struct TrackingError {
    double lat;
    double lng;
    double hdg;
    double steer;
    TrackingError(double lat=0, double lng=0, double hdg=0, double steer=0) : lat(lat), lng(lng), hdg(hdg), steer(steer) {}
};

struct Trajectory {
    std::vector<State> states;
    std::vector<Control> controls;
    std::vector<TrackingError> tracking_errors;
    std::vector<double> time_vec;
};

State nextState(const State& current_state, const Control& control, const EgoConfig& config);
std::vector<State> trajectoryRollout(const State& initial_state, const std::vector<Control>& control_vec, const EgoConfig& config);

#endif // VEHICLE_MODEL_H 