# CS973
## ASSIGMENT 1
## Password: SinglePython973

# Summary for Q3
## Language and Libraries
Q3 of Asisgment 1 of CS973 is written in **Python(submit.py)** and utilizes the **scikit-learn** library for machine learning and validated using provided Google Colab script. The specific implementation employs **Logistic Regression** with the configuration:
```python
clf = LogisticRegression(max_iter=10000, solver='liblinear', C=10, tol=1e-4, penalty='l2')
```
### Hyperparameters
The hyperparameters used include:

- **max_iter=10000:** Allows the optimization algorithm to run for a maximum of 10,000 iterations, ensuring adequate time for convergence.
- **solver='liblinear':** Suitable for small datasets and efficient for logistic regression tasks.
- **C=10:** Provides moderate regularization, balancing model complexity and fitting the training data.
- **tol=1e-4:** Tolerance level for convergence that helps determine when to stop the optimization process.
- **penalty='l2':** Indicates the use of L2 regularization to discourage overly complex models.

### Method Summaries
#### my_fit()
**The my_fit()** method processes the Challenge-Response Pairs (CRPs) for the Advanced XORRO PUF, extracting relevant selection bits to generate unique model keys. It groups the training data by these keys and trains a Logistic Regression model for each configuration of selected XORROs, ensuring a total of 𝑀 = 120 models are learned based on the number of selection bits.
##### my_fit Method Flowchart Description

1. Start
2. Initialize `xor_data_map` as an empty dictionary.
3. For each row in `Z_train`:
   - Calculate `x` and `y` from selection bits.
   - Compute `model_key = 16 * min(x, y) + max(x, y)`. [Each pair of XORRO selections (identified by x and y) needs a unique identifier for indexing into a collection of trained models. This allows the program to correctly access the model corresponding to any given selection of XORROs.
		Given that both x and y can take values from 0 to 15, the keys generated will range from 0 to 255 (i.e., 16×15+15), allowing for efficient mapping of configurations to model indices.
   - If `model_key` is not in `xor_data_map`:
     - Initialize `xor_data_map[model_key]` as an empty list.
   - Create a copy of the current row.
   - If `x > y`, flip the response (last element of the row).[a data preprocessing step aimed at maintaining consistent labeling of the output responses based on the selected XORROs. This helps prevent confusion during model training by ensuring that the model learns from consistently defined input-output mappings.]
   - Append the modified row to `xor_data_map[model_key]`.
4. Convert lists in `xor_data_map` to NumPy arrays.
5. Initialize `trained_models` as an empty dictionary.
6. For each combination of `i` and `j` (where `i < j` from 0 to 15):
   - Compute `model_key = 16 * i + j`.
   - If `model_key` is in `xor_data_map`:
     - Initialize a `LinearSVC` model.
     - Fit the model on the data associated with `model_key`.
     - Store the trained model in `trained_models` using `model_key`.
7. Return `trained_models`.
8. End

#### my_predict() 
The **my_predict()** method takes the test data and utilizes the trained models from my_fit() to predict responses based on the provided challenges. It generates the corresponding model keys for the test inputs, retrieves the appropriate trained model, and returns the predicted outputs, ensuring accurate classification based on the learned configurations.

##### my_predict Method Flowchart Description

1. Start
2. Initialize `X_pred` as a zero array of length equal to the number of rows in `X_tst`.
3. For each row in `X_tst`:
   - Calculate `x` and `y` from selection bits.
   - Compute `model_key = 16 * min(x, y) + max(x, y)`.
   - If `model_key` is not in `models`:
     - Continue to the next iteration.
   - Reshape the first 64 features of the current row for prediction.
   - Use the corresponding model to predict the response based on the reshaped features.
   - If `x > y`, flip the prediction.
   - Store the prediction in `X_pred`.
4. Return `X_pred`.
5. End
### Results

The following are the results we obtained after using the optimized Logistic Regression classifier model with the best-chosen hyperparameters on the provided Google Colab script.

![image](https://github.com/user-attachments/assets/7039f7e8-c99c-4dfc-b769-603c09b10c66)

# Q4: Reporting the Outcome of Various Hyperparameters
In this section, we report the outcomes of the effect of various hyperparameters by comparing the performance of LinearSVC and Logistic Regression. Below, we include a data table of hyperparameters along with corresponding charts for clear visualization.

During the experiments with various hyperparameters, we chose to vary only the specific hyperparameter value under test while keeping all other hyperparameters at their default values (not explicitly mentioned in this report).

We also experimented with RidgeClassifier using various hyperparameters to compare its performance with LinearSVC and Logistic Regression. However, we chose not to include those results in the report, as it would be too cumbersome for the data table and chart. Also, we observed the training time was longer and the model had less accuracy for this method. 

So, for clarity, we focused solely on the results from LinearSVC and Logistic Regression.

Notably, for Logistic Regression with the hyperparameter penalty=’l1’, we specified solver=’liblinear’
as the default since the default solver solver=’lbfgs’ does not support the l1 penalty.

a) Changing the loss hyperparameter in LinearSVC (hinge vs squared hinge)

![image](https://github.com/user-attachments/assets/bbcf7199-3822-4331-af57-225a8c7e15ad)

![image](https://github.com/user-attachments/assets/67367292-d507-4fb7-894b-cb5abf9c9f14)


b) setting C hyperparameter in LinearSVC and LogisticRegression to high/low/medium
values



![image](https://github.com/user-attachments/assets/77a5e9da-fd16-4fac-b59a-cd30cfe53378)

![image](https://github.com/user-attachments/assets/9054f9b5-7ceb-461b-9f62-eac39baa7eca)

c) changing the tol hyperparameter in LinearSVC and LogisticRegression to high/low/medium
values

![image](https://github.com/user-attachments/assets/e525bad1-d6f5-4a24-9cf3-e935188049a7)

![image](https://github.com/user-attachments/assets/5025989a-957b-421a-97a3-1ffa4f35114d)


d) changing the penalty (regularization) hyperparameter in LinearSVC and LogisticRegression
(l2 vs l1)



![image](https://github.com/user-attachments/assets/aa1d31e2-9e37-4132-a0a3-58ad822be738)

![image](https://github.com/user-attachments/assets/123dea75-f713-4f9f-84fb-322fa6adc0a6)




# Appendix

## Response Flipping Explanation

In the context of the XORRO PUF implementation, the indices `x` and `y` are derived from specific bits in the input data, representing the selected XORROs for processing. The response, located in the last element of the row, indicates the output of the PUF for the given challenge.

### Meaning of `x` and `y`
- **`x`**: Represents the index of the first selected XORRO.
- **`y`**: Represents the index of the second selected XORRO.

### Reason for Flipping
- The configuration and the corresponding response of the XORRO can be sensitive to the order of the XORRO indices.
- Flipping the response ensures consistent labeling. Specifically, when the index of the first selected XORRO (`x`) is greater than the second (`y`), it indicates an inversion of the intended configuration.

### Flipping Mechanism
- When the condition `x > y` is met, the last element of the row (the response) is modified as follows:
    ```python
    row_copy[-1] = 1 - row_copy[-1]
    ```
- This effectively changes a response of `0` to `1` and vice versa, ensuring that the model is trained on correctly labeled data.

## Explanation of `model_key = 16 * min(x, y) + max(x, y)`
### Short explanation
The use of the formula `model_key = 16 * min(x, y) + max(x, y)` ensures that each combination of XORRO selections is uniquely and consistently identified, facilitating the efficient storage and retrieval of trained models in the implementation.
The expression `model_key = 16 * min(x, y) + max(x, y)` is used to compute a unique identifier for each combination of selected XORROs in the XORRO PUF implementation. This calculation serves several important purposes:

### Unique Identification
- The `model_key` allows for the indexing of trained models based on the specific configuration of XORRO selections, ensuring that each configuration can be easily retrieved later.

### Consistent Ordering
- By using `min(x, y)` and `max(x, y)`, the order of the selected XORRO indices does not affect the resulting key. This ensures that the same pair of selections yields the same `model_key`, regardless of their order:
  - For instance, if `x = 3` and `y = 12`, both configurations `(3, 12)` and `(12, 3)` will result in the same key:
    ```plaintext
    model_key = 16 * min(3, 12) + max(3, 12) = 16 * 3 + 12 = 60
    ```

### Efficient Mapping
- The multiplication by `16` effectively groups keys based on the value of `x` (the first XORRO), while `y` (the second XORRO) extends the key within that grouping.
- Given that both `x` and `y` can take values from `0` to `15`, the keys generated will range from `0` to `255` (i.e., \(16 * 15 + 15\)), allowing for efficient mapping of configurations to model indices.



