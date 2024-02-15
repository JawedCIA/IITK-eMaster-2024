import csv
import math
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from tabulate import tabulate

# Path to the CSV file
csv_file = "HW2_part1.csv"

# Lists to store values from the CSV file
x_values = []  # For values from the first column after conversion to log scale
y_values = [[] for _ in range(13)]  # For values from the rest of the columns
x_values_original=[]
# Open the CSV file in read mode
with open(csv_file, mode='r', newline='') as file:
    # Create a CSV reader object
    csv_reader = csv.reader(file)
    
    # Iterate over each row in the CSV file
    for row in csv_reader:
        # Check if row is not empty and the first column value is numeric
        if row and row[0].replace('.', '', 1).isdigit():  # Check if the value is numeric
            # Convert the value from the first column to log scale and append it to the list
            x_values.append(math.log(float(row[0]),10))
            x_values_original.append(row[0])
            # Append values from the rest of the columns to the corresponding lists
            for i in range(1, 14):
                y_values[i-1].append(float(row[i]))

table_x_axis_values=[]
for i,xaxis in enumerate(x_values):
    table_x_axis_values.append([f"Row {i+1}", x_values_original[i] , x_values[i]])

# Print the distance in tabular format with logscale
print(tabulate(table_x_axis_values, headers=[ "Distance(In meter)","Distance(In logscale)"], tablefmt="grid"))


# Calculate the average of each row across all columns
average_y_values = np.mean(y_values, axis=0)
# Convert lists to numpy arrays for linear regression
X = np.array(x_values).reshape(-1, 1)
y = average_y_values # store average of data as Y-axis

#Print Average Sample data
table_y_axis_avg_values=[]
for i,yaxisavg in enumerate(average_y_values):
    table_y_axis_avg_values.append([f"Row {i+1}", yaxisavg])

print(tabulate(table_y_axis_avg_values, headers=[ "Average of RSSI Sample Data(In dBm)"], tablefmt="grid"))
#print("Values of the first column in y_values:")
#print(y_values[0])

# Perform linear regression
reg = LinearRegression().fit(X, y)

# Calculate the slope of the line
slope = reg.coef_[0]

# Plotting the line graph
plt.figure(figsize=(12, 7))

# Plotting each column of y_values against x_values
for i, column_values in enumerate(y_values):
     #print(f"Column {i+2} values:", column_values)
     plt.scatter(x_values, column_values)

plt.plot(x_values, reg.predict(X), color='red', label='Best fit line')
    
# Adding labels and title
plt.xlabel('Distance (log scale)')
plt.ylabel('Signal strength(in dBm)')
plt.title('Name: Mohammed, Jawed\nCourse:CS963\nStep1: Finding the Path Loss Exponent',color='green')

# Adding legend
plt.legend()

# Calculate margins for x-axis and y-axis
x_margin = (max(x_values) - min(x_values)) * 0.05  # 5% margin
y_margin = (max([max(column_values) for column_values in y_values]) - min([min(column_values) for column_values in y_values])) * 0.05  # 5% margin


# Adjusting x-axis and y-axis limits with margins
plt.xlim(min(x_values) - x_margin, max(x_values) + x_margin)
plt.ylim(min([min(column_values) for column_values in y_values]) - y_margin, max([max(column_values) for column_values in y_values]) + y_margin)

# Calculate the absolute value of the slope divided by 10
slope_divided_by_10 = abs(slope) / 10
# Print values on the graph with three decimal places
plt.text(0.25, 0.95, f"=> Slope of the best fit line: [ {slope:.3f} ]", transform=plt.gca().transAxes, color='red')
plt.text(0.25, 0.90, f"=> Absolute value of the Slope: [ {abs(slope):.3f} ]", transform=plt.gca().transAxes, color='red')
plt.text(0.25, 0.85, f"=> Path loss exponent(n): [ {slope_divided_by_10:.3f} ]", transform=plt.gca().transAxes, color='red')
# Display the plot

# Calculate the residuals for each column of RSSI samples
residuals = average_y_values - reg.predict(X)
# Calculate the variance of the residuals for each column
variance = np.var(residuals, axis=0)
print(f"{variance:.3f}")

# Plotting each column of y_values against x_values
for i, avg_values in enumerate(average_y_values):
    print(f"Column {i+2} values:", avg_values)
    
# Show the Graph
plt.show()

