#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>

// Helper function to format a number with exactly 4 digits total
string FormatWithFixedDigits(double value) {
    stringstream ss;
    ss << fixed;
    
    // Determine how many digits are before the decimal point
    int integerPart = abs(static_cast<int>(value));
    int digitsBeforeDecimal = (integerPart == 0) ? 1 : static_cast<int>(log10(integerPart)) + 1;
    if (value < 0) digitsBeforeDecimal++; // Account for negative sign
    
    // Set precision to have exactly 4 digits total
    int precision = max(0, 4 - digitsBeforeDecimal);
    ss << setprecision(precision) << value;
    
    return ss.str();
}

void printTrajectory(const vector<State>& trajectory, 
                    const vector<Control>& controls,
                    const vector<TrackingError>& errors,
                    const vector<double>& time_vec) {
    // Check if all vectors have the same size
    if (trajectory.size() != errors.size() || trajectory.size() != controls.size() || trajectory.size() != time_vec.size()) {
        cerr << "Error: Trajectory, controls, error, and time vectors have different sizes." << endl;
        return;
    }
    
    // Set column width to match file output
    const int colWidth = 9;
    
    // Print header
    cout << left 
         << setw(colWidth) << "time:" 
         << setw(colWidth) << "x:" 
         << setw(colWidth) << "y:" 
         << setw(colWidth) << "hdg:" 
         << setw(colWidth) << "vel:" 
         << setw(colWidth) << "acc:" 
         << setw(colWidth) << "steer:" 
         << setw(colWidth) << "lat:" 
         << setw(colWidth) << "lng:" 
         << setw(colWidth) << "hdg_err:" << endl;
    
    cout << string(colWidth * 10 - 3, '-') << endl;  // Separator line adjusted for new width
    
    // Print each step in a single line
    for (size_t i = 0; i < trajectory.size(); ++i) {
        const auto& state = trajectory[i];
        const auto& control = controls[i];
        const auto& error = errors[i];
        const auto& time = time_vec[i];
        
        cout << left 
             << fixed << setprecision(2)
             << setw(colWidth) << time
             << setw(colWidth) << state.x 
             << setw(colWidth) << state.y 
             << setw(colWidth) << state.hdg 
             << setw(colWidth) << state.vel 
             << setw(colWidth) << control.acc 
             << setw(colWidth) << control.steer 
             << setw(colWidth) << error.lat 
             << setw(colWidth) << error.lng 
             << setw(colWidth) << error.hdg << endl;
    }
}

void saveTrajectoryToFile(const vector<State>& trajectory, 
                         const vector<Control>& controls,
                         const vector<TrackingError>& errors,
                         const vector<double>& time_vec,
                         const string& filename) {
    // Check if all vectors have the same size
    if (trajectory.size() != errors.size() || trajectory.size() != controls.size() || trajectory.size() != time_vec.size()) {
        cerr << "Error: Trajectory, controls, error, and time vectors have different sizes." << endl;
        return;
    }
    
    ofstream outFile(filename);
    
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }
    
    // Set column widths for better readability
    const int colWidth = 9;  // Reduced from 12 to 9 to make output more compact
    
    // Write header with proper formatting
    outFile << left
            << setw(colWidth) << "time"
            << setw(colWidth) << "x"
            << setw(colWidth) << "y"
            << setw(colWidth) << "hdg"
            << setw(colWidth) << "vel"
            << setw(colWidth) << "acc"
            << setw(colWidth) << "steer"
            << setw(colWidth) << "lat_err"
            << setw(colWidth) << "lng_err"
            << setw(colWidth) << "hdg_err" << endl;
    
    // Write data with consistent column widths and fixed 4 digits total
    for (size_t i = 0; i < trajectory.size(); ++i) {
        const auto& state = trajectory[i];
        const auto& control = controls[i];
        const auto& error = errors[i];
        const auto& time = time_vec[i];
        
        // Format each value to have exactly 4 digits total
        outFile << left << fixed;
        
        // Format time value
        outFile << setw(colWidth) << FormatWithFixedDigits(time);
        
        // Format state values
        outFile << setw(colWidth) << FormatWithFixedDigits(state.x)
                << setw(colWidth) << FormatWithFixedDigits(state.y)
                << setw(colWidth) << FormatWithFixedDigits(state.hdg)
                << setw(colWidth) << FormatWithFixedDigits(state.vel);
        
        // Format control values
        outFile << setw(colWidth) << FormatWithFixedDigits(control.acc)
                << setw(colWidth) << FormatWithFixedDigits(control.steer);
        
        // Format error values
        outFile << setw(colWidth) << FormatWithFixedDigits(error.lat)
                << setw(colWidth) << FormatWithFixedDigits(error.lng)
                << setw(colWidth) << FormatWithFixedDigits(error.hdg) << endl;
    }
    
    outFile.close();
    cout << "Trajectory saved to " << filename << endl;
}

