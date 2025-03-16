#ifndef UTILS_H 
#define UTILS_H

#include "vehicle_model.h"
#include <string>
#include <vector>

using namespace std;

template <typename T>
T sign(T val) {
    return (T(0) < val) - (val < T(0));
}

// Function to print trajectory with all data to console
void printTrajectory(const vector<State>& trajectory, 
                    const vector<Control>& controls,
                    const vector<TrackingError>& errors,
                    const vector<double>& time_vec);

// Function to save trajectory with all data to a text file
void saveTrajectoryToFile(const vector<State>& trajectory, 
                         const vector<Control>& controls,
                         const vector<TrackingError>& errors,
                         const vector<double>& time_vec,
                         const string& filename);

#endif // UTILS_H