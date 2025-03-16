#include "vehicle_model.h"
#include "control.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

int main() {
    EgoConfig ego_config;
    ego_config.duration = 15.0;
    
    State start_state;
    start_state.x = 0;
    start_state.y = 5;
    start_state.hdg = 0;
    start_state.vel = 0;
    
    State end_state;
    end_state.x = 100;
    end_state.y = 0;
    end_state.hdg = 0;
    end_state.vel = 0;

    //vector<Control> control_vec = openLoopControl();
    //vector<State> trajectory = trajectoryRollout(start_state, control_vec, ego_config);

    // Get trajectory and tracking errors from closed loop control
    Trajectory result = closedLoopControl(start_state, end_state, ego_config);
    vector<State> state_t = result.states;
    vector<Control> control_t = result.controls;
    vector<TrackingError> err_t = result.tracking_errors;
    vector<double> time_vec = result.time_vec;

    // Print trajectory and errors to console
    printTrajectory(state_t, control_t, err_t, time_vec);
    
    // Save trajectory to a file in the docs folder
    string outputFilename = "docs/trajectory.txt";
    saveTrajectoryToFile(state_t, control_t, err_t, time_vec, outputFilename);

    // generate waypoints
    Trajectory wpts = genWpts(ego_config);
    vector<State> wpts_state = wpts.states;
    vector<Control> wpts_ctrl = wpts.controls;
    vector<TrackingError> wpts_err = wpts.tracking_errors;
    vector<double> wpts_time = wpts.time_vec;
    
    string wptsFilename = "docs/wpts.txt";
    saveTrajectoryToFile(wpts_state, wpts_ctrl, wpts_err, wpts_time, wptsFilename);
    
    return 0;
}
