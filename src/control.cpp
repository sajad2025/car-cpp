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

tuple<vector<State>, vector<Control>, vector<TrackingError>> closedLoopControl(const State& start_state, const State& desired_state, const EgoConfig& config) {
    vector<State> trajectory;
    vector<Control> control_vec;
    vector<TrackingError> tracking_errors;

    State tmp_state;
    Control ctrl;
    TrackingError err;

    double k1 = 0.44;
    double k2 = 1.04;
    double steer_ref = 0;

    double y_err = start_state.y - desired_state.y;
    double x_err = start_state.x - desired_state.x;
    err.hdg = start_state.hdg - desired_state.hdg;
    err.lat = y_err * cos(desired_state.hdg) - x_err * sin(desired_state.hdg);
    err.lng = -y_err * sin(desired_state.hdg) - x_err * cos(desired_state.hdg);

    int counter = 0;
    int max_iter = (int) (60.0 / config.dt);
    while (abs(err.lng) > 1.0 && counter < max_iter) {
        counter++;

        ctrl.steer = -config.wheelbsae * (k1 * err.lat + k2 * err.hdg) * cos(steer_ref) * cos(steer_ref);
        ctrl.steer = max(min(ctrl.steer, config.steer_max), config.steer_min);
        ctrl.acc = sign(err.lng)? config.acc_max : config.acc_min;

        tmp_state = nextState(tmp_state, ctrl, config);

        trajectory.push_back(tmp_state);
        tracking_errors.push_back(err);
        control_vec.push_back(ctrl);
        y_err = tmp_state.y - desired_state.y;
        x_err = tmp_state.x - desired_state.x;
        err.hdg = tmp_state.hdg - desired_state.hdg;
        err.lat = y_err * cos(desired_state.hdg) - x_err * sin(desired_state.hdg);
        err.lng = -y_err * sin(desired_state.hdg) - x_err * cos(desired_state.hdg);
    }

    return make_tuple(trajectory, control_vec, tracking_errors);
}
