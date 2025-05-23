import pandas as pd
import matplotlib.pyplot as plt
import numpy as np



#Load the input points and convex hull points from CSV files
input_points = pd.read_csv('inputpoints.csv')
hull_points = pd.read_csv('hullPoints.csv')

#Function to sort points in counter-clockwise order
def sort_points(points):
    #Calculate the centroid of the points
    centroid = np.mean(points, axis=0)
    
    #Calculate the angle of each point relative to the centroid
    angles = np.arctan2(points[:, 1] - centroid[1], points[:, 0] - centroid[0])
    
    #Sort points based on the angles
    sorted_indices = np.argsort(angles)
    return points[sorted_indices]

#Convert hull points to a NumPy array for sorting
hull_points_array = hull_points[['X', 'Y']].to_numpy()
sorted_hull_points = sort_points(hull_points_array)

#Create a scatter plot for the input points
plt.figure(figsize=(10, 6))
plt.scatter(input_points['X'], input_points['Y'], color='blue', label='Input Points', s=10)

#Create a scatter plot for the convex hull points
plt.scatter(hull_points['X'], hull_points['Y'], color='red', label='Convex Hull Points', s=10)

#Draw lines between the sorted convex hull points
if len(sorted_hull_points) > 1:
    plt.plot(sorted_hull_points[:, 0].tolist() + [sorted_hull_points[0, 0]], 
             sorted_hull_points[:, 1].tolist() + [sorted_hull_points[0, 1]], 
             color='red', linestyle='-', linewidth=2)

#Set plot title and labels
plt.title('Convex Hull Visualization')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.axhline(0, color='black', linewidth=0.5, ls='--')
plt.axvline(0, color='black', linewidth=0.5, ls='--')
plt.grid(color='gray', linestyle='--', linewidth=0.5)
plt.legend()
plt.axis('equal')  # Equal scaling for both axes
plt.show()
