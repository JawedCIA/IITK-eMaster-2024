import numpy as np
from sklearn.svm import LinearSVC
from sklearn.linear_model import LogisticRegression
# You are allowed to import any submodules of sklearn as well e.g. sklearn.svm etc
# You are not allowed to use other libraries such as scipy, keras, tensorflow etc

# SUBMIT YOUR CODE AS A SINGLE PYTHON (.PY) FILE INSIDE A ZIP ARCHIVE
# THE NAME OF THE PYTHON FILE MUST BE submit.py
# DO NOT INCLUDE OTHER PACKAGES LIKE SCIPY, KERAS ETC IN YOUR CODE
# THE USE OF ANY MACHINE LEARNING LIBRARIES OTHER THAN SKLEARN WILL RESULT IN A STRAIGHT ZERO

# DO NOT CHANGE THE NAME OF THE METHODS my_fit, my_predict etc BELOW
# THESE WILL BE INVOKED BY THE EVALUATION SCRIPT. CHANGING THESE NAMES WILL CAUSE EVALUATION FAILURE

# You may define any new functions, variables, classes here
# For example, functions to calculate next coordinate or step length
################################
# Non Editable Region Starting #
################################
def my_fit( Z_train ):
################################
#  Non Editable Region Ending  #
################################

	# Use this method to train your model using training CRPs
	# The first 64 columns contain the config bits
	# The next 4 columns contain the select bits for the first mux
	# The next 4 columns contain the select bits for the second mux
	# The first 64 + 4 + 4 = 72 columns constitute the challenge
	# The last column contains the response

    # Determine the number of selection bits (S)
    S = 4  # As given in the assignment
    # Calculate M = 2^(S-1) * (2^S - 1)
    M = 2**(S - 1) * (2 ** S - 1)  # This will give M = 120 for S = 4


    xor_data_map = {}
    
    # Transforming training data based on selection bits
    for i in range(Z_train.shape[0]):
        x = int(Z_train[i][-6] + 2 * Z_train[i][-7] + 4 * Z_train[i][-8] + 8 * Z_train[i][-9])
        y = int(Z_train[i][-2] + 2 * Z_train[i][-3] + 4 * Z_train[i][-4] + 8 * Z_train[i][-5])
        model_key = 16 * min(x, y) + max(x, y)  # Ensure x <= y for consistent keys

        # Initialize the entry in the map if it doesn't exist
        if model_key not in xor_data_map:
            xor_data_map[model_key] = []

        row_copy = Z_train[i].copy()
        if x > y:
            row_copy[-1] = 1 - row_copy[-1]  # Flip response if needed

        xor_data_map[model_key].append(row_copy)

    # Convert lists to numpy arrays for model training
    for key in xor_data_map:
        xor_data_map[key] = np.array(xor_data_map[key])

    trained_models = {}

    # Train LinearSVC models for each XORRO configuration
    for i in range(15):
        for j in range(i + 1, 16):
            model_key = 16 * i + j
            if model_key in xor_data_map:
             
                #clf = LinearSVC(max_iter=10000, loss='squared_hinge',penalty='l2',tol=1e-4,C=11,dual='auto') 
                # 0.9914572810000208 7.048575445200004 88156.0 0.9487500000000001               
                #clf=LogisticRegression(max_iter=10000, solver='liblinear', C=11, tol=1e-4,penalty='l2')
                # 1.3102126592000787 7.1384906877998215 88156.0 0.9484999999999999
                clf=LogisticRegression(max_iter=10000, solver='liblinear', C=10, tol=1e-4,penalty='l2')
                #For Best Performance with Speed:
                #3.20083408240007 6.624912874600023 88156.0 0.949975
                #clf=LogisticRegression(max_iter=10000, solver='newton-cg', C=40,tol=1e-4,penalty='l2')
                clf.fit(xor_data_map[model_key][:, :64], xor_data_map[model_key][:, -1])
                trained_models[model_key] = clf
    # Validate the number of trained models against M
    # print(f"Total models trained: {len(trained_models)} out of {M} expected.")
    return trained_models                   # Return the trained model   

################################
# Non Editable Region Starting #
################################
def my_predict( X_tst, model ):
################################
#  Non Editable Region Ending  #
################################
    # Use this method to make predictions on test challenges
    X_pred = np.zeros(X_tst.shape[0])
    
    for i in range(X_tst.shape[0]):
        x = int(X_tst[i][-5] + 2 * X_tst[i][-6] + 4 * X_tst[i][-7] + 8 * X_tst[i][-8])
        y = int(X_tst[i][-1] + 2 * X_tst[i][-2] + 4 * X_tst[i][-3] + 8 * X_tst[i][-4])
        model_key = 16 * min(x, y) + max(x, y)  # Ensure x <= y for consistent keys

        # Check if model_key exists before prediction
        if model_key not in model:
            #print(f"Warning: Model for key {model_key} not found. Available keys: {list(models.keys())}")
            continue  # Skip this iteration if the model is missing

        feature_array = X_tst[i, :64].reshape(1, 64)  # Reshape for prediction
        pred = model[model_key].predict(feature_array)

        # Flip the prediction if needed
        if x > y:
            pred = 1 - pred
            
        X_pred[i] = pred
    
    return X_pred

