#ifndef CONTROL_H
#define CONTROL_H

#include "vehicle_model.h"
#include <vector>
using namespace std;

// vector<Control> openLoopControl();
Position updateReference(double x, double y, double shift_lat, double shift_lon, double h_r);
Trajectory closedLoopControl(const State& start_state, const State& desired_state, const EgoConfig& config);

#endif // CONTROL_H 