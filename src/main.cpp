#include "vehicle_model.h"
#include "control.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

int main() {
    EgoConfig ego_config;
    
    State start_state;
    start_state.x = 0;
    start_state.y = 0;
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
    auto result = closedLoopControl(start_state, end_state, ego_config);
    vector<State> trajectory = get<0>(result);
    vector<Control> control_vec = get<1>(result);
    vector<TrackingError> tracking_errors = get<2>(result);

    // Print trajectory and errors to console
    printTrajectoryError(trajectory, control_vec, tracking_errors);
    
    // Save trajectory with errors to a file in the docs folder
    string outputFilenameWithErrors = "docs/trajectory_with_errors.txt";
    saveTrajectoryWithErrorToFile(trajectory, control_vec, tracking_errors, outputFilenameWithErrors);
    
    return 0;
}
