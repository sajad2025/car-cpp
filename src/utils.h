#ifndef UTILS_H 
#define UTILS_H

#include "vehicle_model.h"
#include <string>
#include <vector>
#include <tuple>

template <typename T>
T sign(T val) {
    return (T(0) < val) - (val < T(0));
}

// Function to print trajectory with all data to console
void printTrajectory(const std::vector<State>& trajectory, 
                    const std::vector<Control>& controls,
                    const std::vector<TrackingError>& errors,
                    const std::vector<double>& time_vec);

// Function to save trajectory with all data to a text file
void saveTrajectoryToFile(const std::vector<State>& trajectory, 
                         const std::vector<Control>& controls,
                         const std::vector<TrackingError>& errors,
                         const std::vector<double>& time_vec,
                         const std::string& filename);

#endif // UTILS_H