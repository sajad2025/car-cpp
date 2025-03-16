#include "wpts.h"

Trajectory genWpts(const EgoConfig& cfg){
    vector<State> state_t;
    vector<Control> control_t;
    vector<TrackingError> err_t;
    vector<double> time_vec;

    State state_current{0, 0, 0, 3};        // x, y, hdg, vel
    Control ctrl_current{0, 0.1};             // acc, steering
    TrackingError err_current{0, 0, 0};     // lat, long, hdg
    double time_current = 0.0; 

    while (time_current < cfg.duration){
        time_current += cfg.dt;

        state_current = nextState(state_current, ctrl_current, cfg);
        state_t.push_back(state_current);

        // for consistency
        control_t.push_back(ctrl_current);
        err_t.push_back(err_current);
        time_vec.push_back(time_current);
    }

    return Trajectory{state_t, control_t, err_t, time_vec};
}
