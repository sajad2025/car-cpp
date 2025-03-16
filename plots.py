#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import argparse
import os

def load_trajectory_data(filename):
    """Load trajectory data from the specified file."""
    data = np.loadtxt(filename, skiprows=1)
    
    # Extract columns based on the file format
    time = data[:, 0]
    x = data[:, 1]
    y = data[:, 2]
    hdg = data[:, 3]
    str = data[:, 4]  # steering angle
    vel = data[:, 5]
    str_dot = data[:, 6]  # steering rate
    acc = data[:, 7]
    lat_err = data[:, 8]
    lng_err = data[:, 9]
    hdg_err = data[:, 10]
    str_err = data[:, 11]  # steering error
    
    # Convert radians to degrees for angular measurements
    hdg_err_deg = np.degrees(hdg_err)
    str_deg = np.degrees(str)
    str_dot_deg = np.degrees(str_dot)
    str_err_deg = np.degrees(str_err)
    
    return {
        'time': time, 'x': x, 'y': y, 'hdg': hdg, 'str': str_deg, 'vel': vel,
        'str_dot': str_dot_deg, 'acc': acc,
        'lat_err': lat_err, 'lng_err': lng_err, 'hdg_err': hdg_err_deg, 'str_err': str_err_deg
    }

def plot_trajectory(data, output_dir=None):
    """
    Plot the trajectory and related data in a 4x2 subplot layout.
    
    Args:
        data: Dictionary containing trajectory data
        output_dir: Directory to save the plot
    """
    # Create a figure with 4x2 subplots
    fig = plt.figure(figsize=(12, 7.5))  # Reduced height by 25% from 10 to 7.5
    
    # Plot 1: Trajectory (x, y) - 1st row, 1st column
    ax1 = fig.add_subplot(4, 2, 1)
    ax1.plot(data['x'], data['y'], 'b-', linewidth=2)
    ax1.set_title('Vehicle Trajectory (m)')
    ax1.grid(True)
    
    # Plot 2: Heading Error vs Time - 1st row, 2nd column
    ax2 = fig.add_subplot(4, 2, 2)
    ax2.plot(data['time'], data['hdg_err'], 'r-', linewidth=2)
    ax2.set_title('Heading Error (deg)')
    ax2.grid(True)
    
    # Plot 3: Velocity vs Time - 2nd row, 1st column
    ax3 = fig.add_subplot(4, 2, 3)
    ax3.plot(data['time'], data['vel'], 'g-', linewidth=2)
    ax3.set_title('Velocity (m/s)')
    ax3.grid(True)
    
    # Plot 4: Lateral Error vs Time - 2nd row, 2nd column
    ax4 = fig.add_subplot(4, 2, 4)
    ax4.plot(data['time'], data['lat_err'], 'b-', linewidth=2)
    ax4.set_title('Lateral Error (m)')
    ax4.grid(True)
    
    # Plot 5: Acceleration vs Time - 3rd row, 1st column
    ax5 = fig.add_subplot(4, 2, 5)
    ax5.plot(data['time'], data['acc'], 'y-', linewidth=2)
    ax5.set_title('Acceleration (m/s²)')
    ax5.grid(True)
    
    # Plot 6: Longitudinal Error vs Time - 3rd row, 2nd column
    ax6 = fig.add_subplot(4, 2, 6)
    ax6.plot(data['time'], data['lng_err'], 'g-', linewidth=2)
    ax6.set_title('Longitudinal Error (m)')
    ax6.grid(True)
    
    # Plot 7: Steering Angle vs Time - 4th row, 1st column
    ax7 = fig.add_subplot(4, 2, 7)
    ax7.plot(data['time'], data['str'], 'm-', linewidth=2)
    ax7.set_title('Steering Angle (deg)')
    ax7.grid(True)
    
    # Plot 8: Steering Rate vs Time - 4th row, 2nd column
    ax8 = fig.add_subplot(4, 2, 8)
    ax8.plot(data['time'], data['str_dot'], 'c-', linewidth=2)
    ax8.set_title('Steering Rate (deg/s)')
    ax8.grid(True)
    
    # Adjust layout
    fig.tight_layout()
    
    # Save the figure if output directory is specified
    if output_dir:
        os.makedirs(output_dir, exist_ok=True)
        output_path = os.path.join(output_dir, 'trajectory.png')
        fig.savefig(output_path, dpi=300)
        print(f"Trajectory plot saved to {output_path}")
    
    # Show the plot
    plt.show()

def main():
    parser = argparse.ArgumentParser(description='Plot vehicle trajectory data')
    parser.add_argument('--file', type=str, default='docs/trajectory.txt',
                        help='Path to the trajectory data file')
    parser.add_argument('--output', type=str, default='docs',
                        help='Directory to save the plot')
    args = parser.parse_args()
    
    # Check if file exists
    if not os.path.exists(args.file):
        print(f"Error: File {args.file} not found.")
        return
    
    # Load and plot data
    data = load_trajectory_data(args.file)
    plot_trajectory(data, args.output)

if __name__ == "__main__":
    main() 