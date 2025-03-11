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

// Function to print trajectory to console
void printTrajectory(const std::vector<State>& trajectory);

// Function to print trajectory with controls and tracking errors to console
void printTrajectoryError(const std::vector<State>& trajectory, 
                         const std::vector<Control>& controls,
                         const std::vector<TrackingError>& errors);

// Function to save trajectory to a text file
void saveTrajectoryToFile(const std::vector<State>& trajectory, const std::string& filename);

// Function to save trajectory with controls and tracking errors to a text file
void saveTrajectoryWithErrorToFile(const std::vector<State>& trajectory, 
                                  const std::vector<Control>& controls,
                                  const std::vector<TrackingError>& errors, 
                                  const std::string& filename);

#endif // UTILS_H