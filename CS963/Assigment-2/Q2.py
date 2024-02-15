import csv
import math
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from tabulate import tabulate

# Path to the CSV file
csv_file = "HW2_part2.csv"

# Lists to store values from the CSV file
x_values = []  # For values from the first column after conversion to log scale
y_values = [[] for _ in range(15)]  # For values from the rest of the columns
n=5.750 #Calculated from previous Question -1 
# Open the CSV file in read mode
with open(csv_file, mode='r', newline='') as file:
    # Create a CSV reader object
    csv_reader = csv.reader(file)
    
    # Iterate over each row in the CSV file
    for row in csv_reader:
        # Check if row is not empty and the first column value is numeric
        if row and row[0].replace('.', '', 1).isdigit():  # Check if the value is numeric
            # Get the X -axis values which is distance
            x_values.append(row[0])            
            # Append values from the rest of the columns to the corresponding lists
            for i in range(1, 16):
                y_values[i-1].append(float(row[i]))
# Print the y_values
print("Distance:",x_values)
# Calculate the average of each row across all columns
average_y_values = np.mean(y_values, axis=0)
y = average_y_values # store average of data as Y-axis
#Print Average Sample data
table_y_axis_avg_values=[]
for i,yaxisavg in enumerate(average_y_values):
    table_y_axis_avg_values.append([f"Row {i+1} \n (B{i+1}- P{i+1})", yaxisavg])

print(tabulate(table_y_axis_avg_values, headers=[ "Averg. measurements\n (In dBm)"], tablefmt="grid"))

#Calculate actual distance 
pd0= average_y_values[0]

actual_distance = []
table_actual_distance=[]
for i in range(1,6):
    exponent=(pd0-average_y_values[i])/(10*n)
    actual_distance.append(float('{:.3f}'.format(pow(10, exponent))))
    table_actual_distance.append([f"Row {i+1} \n (B{i+1}- P{i+1})", float('{:.3f}'.format(pow(10, exponent)))])


print(tabulate(table_actual_distance, headers=[ "Actual Distance \n (In meter)"], tablefmt="grid"))

#print("Actual Distance:",actual_distance)

error_distance = []
averg_error_distance = []
table_error_distance=[]
table_error_average=[]
for i in range(1, 6):
    # Convert x_values[i] to a float
    x_value_float = float(x_values[i])
    actual_distance_float=actual_distance[i-1]
    error=float('{:.3f}'.format(actual_distance_float - x_value_float))
    error_distance.append(error)
    table_error_distance.append([f"Row {i+1}", x_value_float,actual_distance_float,error])
   
average_error=np.mean(error_distance)
table_error_distance.append(["Average Error", "", "", average_error])
# Print the distance in tabular format with logscale
print(tabulate(table_error_distance, headers=[ "Recorded Distance","Actual Distance", "Error"], tablefmt="grid"))

print(tabulate(table_error_average, tablefmt="grid"))

