#include "vehicle_model.h"
#include <cmath>
#include <vector>

using namespace std;

State nextState(const State& current_state, const Control& control, const EgoConfig& config) {
    State next_state = current_state;

    next_state.vel = current_state.vel + control.acc * config.dt;
    next_state.vel = max(next_state.vel, config.velocity_min);
    next_state.vel = min(next_state.vel, config.velocity_max);
    
    next_state.hdg = current_state.hdg + current_state.vel * tan(control.steer) * config.dt / config.wheelbsae;
    next_state.hdg = fmod(next_state.hdg + M_PI, 2 * M_PI) - M_PI;
    
    next_state.x = current_state.x + current_state.vel * cos(current_state.hdg) * config.dt;
    next_state.y = current_state.y + current_state.vel * sin(current_state.hdg) * config.dt;
    
    return next_state;
}

vector<State> trajectoryRollout(const State& initial_state, const vector<Control>& control_vec, const EgoConfig& config) {
    int n = control_vec.size();
    vector<State> trajectory(n+1);
    trajectory[0] = initial_state;
    for (int i = 0; i < n; i++) {
        trajectory[i+1] = nextState(trajectory[i], control_vec[i], config);
    }
    return trajectory;
}
