import numpy as np
from scipy import linalg

def lqr(A, B, Q, R):
    """
    Solve the continuous time LQR controller.
    
    Args:
        A: System dynamics matrix
        B: Control input matrix
        Q: State cost matrix
        R: Control cost matrix
    
    Returns:
        K: Optimal gain matrix
    """
    # Solve the continuous time algebraic Riccati equation
    P = linalg.solve_continuous_are(A, B, Q, R)
    
    # Compute the LQR gain matrix K
    K = np.linalg.inv(R) @ B.T @ P
    
    return K

if __name__ == "__main__":
    # Define the system matrices as given in the example
    A = np.array([[0., 1., 0.],
                  [0., 0., 1./(2.7*0.95)],
                  [0., 0., 0.]])
    
    B = np.array([[0],
                  [0],
                  [1]])
    # state cost matrix [latError, headingError, steeringError]
    Q = np.array([[.1,  0.,   0.],
                  [0.,  100.,  0.],
                  [0.,  0.,   0.00]])
    
    # control cost matrix [steer_rate]
    R = np.array([[10.]])
    
    # Compute the LQR gain matrix
    K = lqr(A, B, Q, R)
    
    # Print the results
    print(f"K = lqr(A, B, Q, R) = {K.flatten()}")
    print(f"k1 = {K[0, 0]:.4f}")
    print(f"k2 = {K[0, 1]:.4f}") 
    print(f"k3 = {K[0, 2]:.4f}") 