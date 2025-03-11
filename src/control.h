#ifndef CONTROL_H
#define CONTROL_H

#include "vehicle_model.h"
#include <vector>

std::vector<Control> openLoopControl();
std::tuple<std::vector<State>, std::vector<Control>, std::vector<TrackingError>> closedLoopControl(const State&, const State&, const EgoConfig&);


#endif // CONTROL_H 