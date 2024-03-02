import numpy as np

# Define the matrix
A = np.array([[1,1,-1],
              [8,3,0],
              [5,4,-1]])

# Find eigenvalues and eigenvectors
eigenvalues, eigenvectors = np.linalg.eig(A)

# Print the results
print("Eigenvalues:")
print(eigenvalues)
print("\nEigenvectors:")
print(eigenvectors)
