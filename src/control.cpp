#include "control.h"
#include "utils.h"
#include <cmath>

// vector<Control> openLoopControl() {
//     int n = 100;
//     vector<Control> control_vec(n);

//     for (int i = 0; i < n; i++) {
//         control_vec[i].acc = 0;
//         control_vec[i].steer = 0;
//     }
//     return control_vec;
// }

Position updateReference(double x, double y, double shift_lat, double shift_lon, double h_r) {
    // Cramer's rule
    // note: det = 1 = cos(h_r) * cos(h_r) + sin(h_r) * sin(h_r)
    double x_bar = (-shift_lat * sin(h_r) - shift_lon * cos(h_r)) / 1;
    double y_bar = (shift_lat * cos(h_r) - shift_lon * sin(h_r)) / 1;
    
    // Solve for x_r and y_r using:
    double x_r = x - x_bar;
    double y_r = y - y_bar;
    
    return {x_r, y_r};
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
    double k1 = 0.1000;
    double k2 = 3.2896;
    double k3 = 1.6016;

    // Reference steering angle, assume zero curvature
    double steer_ref = 0;

    // local desired state to be modified
    State desired_state_local = desired_state;

    // Initial tracking error, needed for loop termination
    double y_err = state_current.y - desired_state_local.y;
    double x_err = state_current.x - desired_state_local.x;
    err_current.lng = -y_err * sin(desired_state_local.hdg) - x_err * cos(desired_state_local.hdg);

    bool ref_mod = false;

    while (abs(err_current.lng) > 1.0 && time_current < config.duration) {

        // test update reference, modify desired state
        if (time_current > 5 && !ref_mod) {
            ref_mod = true; // only modify reference once

            double shift_lat = 4;               // shift in lateral direction by 4m
            double shift_lon = err_current.lng; // keep shift in longitudinal direction same as tracking error
            double h_r = desired_state.hdg;     // keep ref heading fixed

            Position ref = updateReference(state_current.x, state_current.y, shift_lat, shift_lon, h_r);
            desired_state_local.x = ref.x;
            desired_state_local.y = ref.y;
        }

        // Update tracking error
        y_err = state_current.y - desired_state_local.y;
        x_err = state_current.x - desired_state_local.x;
        err_current.hdg = state_current.hdg - desired_state_local.hdg;
        err_current.lat = y_err * cos(desired_state_local.hdg) - x_err * sin(desired_state_local.hdg);
        err_current.lng = -y_err * sin(desired_state_local.hdg) - x_err * cos(desired_state_local.hdg);
        err_current.steer = state_current.steer - steer_ref;
        err_t.push_back(err_current);

        // Compute control, assume steer_rate_ref is zero, u = -Kx = steer_rate - steer_rate_ref
        ctrl_current.steer_rate = -(k1 * err_current.lat + k2 * err_current.hdg + k3 * err_current.steer);
        ctrl_current.steer_rate = max(min(ctrl_current.steer_rate, config.steer_rate_max), config.steer_rate_min);

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