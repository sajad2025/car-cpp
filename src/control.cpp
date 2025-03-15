#include "control.h"
#include "vehicle_model.h"
#include "utils.h"
#include <cmath>
#include <tuple>
using namespace std;

vector<Control> openLoopControl() {
    int n = 100;
    vector<Control> control_vec(n);

    for (int i = 0; i < n; i++) {
        control_vec[i].acc = 0;
        control_vec[i].steer = 0;
    }
    return control_vec;
}

Trajectory closedLoopControl(const State& start_state, const State& desired_state, const EgoConfig& config) {
    vector<State> state_t;
    vector<Control> control_t;
    vector<TrackingError> err_t;
    vector<double> time_vec;  // New vector to store time data

    State state_current = start_state;
    Control ctrl_current;
    TrackingError err_current;
    double time_current = 0.0;  // Initialize time to 0

    // LQR Controller parameters
    double k1 = 0.44;
    double k2 = 1.04;

    // Reference steering angle, assume zero curvature
    double steer_ref = 0;

    // Initial tracking error, needed for loop termination
    double y_err = state_current.y - desired_state.y;
    double x_err = state_current.x - desired_state.x;
    err_current.lng = -y_err * sin(desired_state.hdg) - x_err * cos(desired_state.hdg);

    while (abs(err_current.lng) > 1.0 && time_current < config.duration) {
        // Update tracking error
        y_err = state_current.y - desired_state.y;
        x_err = state_current.x - desired_state.x;
        err_current.hdg = state_current.hdg - desired_state.hdg;
        err_current.lat = y_err * cos(desired_state.hdg) - x_err * sin(desired_state.hdg);
        err_current.lng = -y_err * sin(desired_state.hdg) - x_err * cos(desired_state.hdg);
        err_t.push_back(err_current);

        // Compute control
        ctrl_current.steer = -config.wheelbsae * (k1 * err_current.lat + k2 * err_current.hdg) * cos(steer_ref) * cos(steer_ref);
        ctrl_current.steer = max(min(ctrl_current.steer, config.steer_max), config.steer_min);
        ctrl_current.acc = sign(err_current.lng)? config.acc_max : config.acc_min;
        control_t.push_back(ctrl_current);

        // Update state
        state_current = nextState(state_current, ctrl_current, config);
        state_t.push_back(state_current);
        
        // Update time
        time_current += config.dt;
        time_vec.push_back(time_current);
    }

    return Trajectory{state_t, control_t, err_t, time_vec};
}
