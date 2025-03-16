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
    vel = data[:, 4]
    acc = data[:, 5]
    steer = data[:, 6]
    lat_err = data[:, 7]
    lng_err = data[:, 8]
    hdg_err = data[:, 9]
    
    return {
        'time': time, 'x': x, 'y': y, 'hdg': hdg, 'vel': vel, 
        'acc': acc, 'steer': steer, 
        'lat_err': lat_err, 'lng_err': lng_err, 'hdg_err': hdg_err
    }

def plot_trajectory(data, output_dir=None):
    """
    Plot the trajectory and related data in a 3x2 subplot layout.
    
    Args:
        data: Dictionary containing trajectory data
        output_dir: Directory to save the plot
    """
    # Create a figure with 3x2 subplots
    # Original height was 10, reducing by 30% gives 7
    fig = plt.figure(figsize=(12, 7))
    
    # Plot 1: Trajectory (x, y) - 1st row, 1st column
    ax1 = fig.add_subplot(3, 2, 1)
    ax1.plot(data['x'], data['y'], 'b-', linewidth=2)
    ax1.set_title('Vehicle Trajectory')
    ax1.set_xlabel('X Position (m)')
    ax1.set_ylabel('Y Position (m)')
    ax1.grid(True)
    ax1.set_aspect('equal')
    
    # Plot 2: Velocity vs Time - 2nd row, 1st column
    ax2 = fig.add_subplot(3, 2, 3)
    ax2.plot(data['time'], data['vel'], 'g-', linewidth=2)
    ax2.set_title('Velocity vs Time')
    ax2.set_xlabel('Time (s)')
    ax2.set_ylabel('Velocity (m/s)')
    ax2.grid(True)
    
    # Plot 3: Steering vs Time - 3rd row, 1st column
    ax3 = fig.add_subplot(3, 2, 5)
    ax3.plot(data['time'], data['steer'], 'm-', linewidth=2)
    ax3.set_title('Steering Angle vs Time')
    ax3.set_xlabel('Time (s)')
    ax3.set_ylabel('Steering Angle (rad)')
    ax3.grid(True)
    
    # Plot 4: Heading Error vs Time - 1st row, 2nd column
    ax4 = fig.add_subplot(3, 2, 2)
    ax4.plot(data['time'], data['hdg_err'], 'r-', linewidth=2)
    ax4.set_title('Heading Error vs Time')
    ax4.set_xlabel('Time (s)')
    ax4.set_ylabel('Heading Error (rad)')
    ax4.grid(True)
    
    # Plot 5: Lateral Error vs Time - 2nd row, 2nd column
    ax5 = fig.add_subplot(3, 2, 4)
    ax5.plot(data['time'], data['lat_err'], 'b-', linewidth=2)
    ax5.set_title('Lateral Error vs Time')
    ax5.set_xlabel('Time (s)')
    ax5.set_ylabel('Lateral Error (m)')
    ax5.grid(True)
    
    # Plot 6: Longitudinal Error vs Time - 3rd row, 2nd column
    ax6 = fig.add_subplot(3, 2, 6)
    ax6.plot(data['time'], data['lng_err'], 'g-', linewidth=2)
    ax6.set_title('Longitudinal Error vs Time')
    ax6.set_xlabel('Time (s)')
    ax6.set_ylabel('Longitudinal Error (m)')
    ax6.grid(True)
    
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