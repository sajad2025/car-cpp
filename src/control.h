#ifndef CONTROL_H
#define CONTROL_H

#include "vehicle_model.h"
#include <vector>

std::vector<Control> openLoopControl();
Trajectory closedLoopControl(const State&, const State&, const EgoConfig&);
Trajectory genWpts(const EgoConfig&);

#endif // CONTROL_H 