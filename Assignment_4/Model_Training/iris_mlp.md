
# MLP CLASSIFIER - IRIS DATASET


## ## STEP 1: MLP Hyperparameter Tuning with Cross-Validation
Best MLP Hyperparameters:
  {'activation': 'tanh', 'alpha': 0.0001, 'hidden_layer_sizes': (50,), 'learning_rate_init': 0.01, 'max_iter': 500}
Best Cross-validation Score: `0.8833`

## ## STEP 2: Training Final MLP Model
```bash 
Training time: 0.0142 seconds
Final training loss: 0.2898
Number of iterations: 13
Number of layers: 3
Number of outputs: 3
```
## STEP 3: MLP Model Evaluation
Performance Metrics:
```bash 
Accuracy: 0.8000
Precision: 0.8056
Recall: 0.8000
F1-Score: 0.7980

Detailed Classification Report:
              precision    recall  f1-score   support

      setosa       1.00      1.00      1.00        10
  versicolor       0.75      0.60      0.67        10
   virginica       0.67      0.80      0.73        10

    accuracy                           0.80        30
   macro avg       0.81      0.80      0.80        30
weighted avg       0.81      0.80      0.80        30
```

## STEP 4: MLP Confusion Matrix
Confusion Matrix:
```bash
[[10  0  0]
 [ 0  6  4]
 [ 0  2  8]]
```
## STEP 5: MLP Training History Visualization
Final training loss: `0.289840`
Final validation score: `0.9167`

## STEP 6: MLP Architecture Analysis
MLP Architecture Details:
```bash
  Hidden layer sizes: (50,)
  Activation function: tanh
  Learning rate: 0.01
  Alpha (L2 regularization): 0.0001
  Total iterations: 13
```
Feature Importance (Permutation Importance):
  sepal length (cm): 0.1967 (+/- 0.0314)
  sepal width (cm): 0.1433 (+/- 0.0578)
  petal length (cm): -0.0200 (+/- 0.0221)
  petal width (cm): 0.4300 (+/- 0.0849)


## STEP 7: Final Cross-validation Performance
```bash
Cross-validation scores: [0.875      0.875      0.95833333 0.83333333 0.875     ]
Mean CV accuracy: 0.8833 (+/- 0.0816)
```
## STEP 8: Probability Analysis
First 5 test samples prediction probabilities:

```text
  Sample 1: True=setosa, Predicted=setosa, Probabilities=[0.56356505 0.29372302 0.14271193]
  Sample 2: True=virginica, Predicted=virginica, Probabilities=[0.1419283  0.37535561 0.48271609]
  Sample 3: True=versicolor, Predicted=versicolor, Probabilities=[0.36389506 0.43300016 0.20310478]
  Sample 4: True=versicolor, Predicted=versicolor, Probabilities=[0.34493615 0.45057068 0.20449316]
  Sample 5: True=setosa, Predicted=setosa, Probabilities=[0.58714922 0.26748837 0.14536241]
```

MLP ANALYSIS COMPLETED SUCCESSFULLY
--



# MLP CLASSIFIER - IMPROVED CONFIGURATION

## STEP 1: MLP Configuration for Training History
Best MLP Hyperparameters:
  {'activation': 'relu', 'alpha': 0.01, 'early_stopping': True, 'hidden_layer_sizes': (100,), 'learning_rate_init': 0.01, 'max_iter': 1000, 'n_iter_no_change': 50, 'solver': 'adam', 'validation_fraction': 0.2}
Best Cross-validation Score: `0.9583`

## STEP 2: Training MLP with History Tracking
```bash
Training time: 0.0533 seconds
Final training loss: 0.033078
Number of iterations: 76
Solver: adam
Converged: True
Loss curve available with 76 points

## STEP 3: MLP Model Evaluation
Performance Metrics:
Accuracy: 0.9000
Precision: 0.9024
Recall: 0.9000
F1-Score: 0.8997

Detailed Classification Report:
              precision    recall  f1-score   support

      setosa       1.00      1.00      1.00        10
  versicolor       0.89      0.80      0.84        10
   virginica       0.82      0.90      0.86        10

    accuracy                           0.90        30
   macro avg       0.90      0.90      0.90        30
weighted avg       0.90      0.90      0.90        30
```

## STEP 4: MLP Confusion Matrix
```bash
Confusion Matrix:
[[10  0  0]
 [ 0  8  2]
 [ 0  1  9]]
```
## STEP 5: MLP Training History Visualization
Final training loss: `0.033078`
Final validation score: `0.9583`
Training history visualization saved

## STEP 7: Final Cross-validation Performance
Cross-validation scores: [0.91666667 0.95833333 0.95833333 1.         0.95833333]
Mean CV accuracy: `0.9583 (+/- 0.0527)`

## STEP 8: Probability Analysis
First 5 test samples prediction probabilities:
  Sample 1: True=setosa, Predicted=setosa, Probabilities=[9.98864269e-01 1.13262767e-03 3.10330591e-06]
  Sample 2: True=virginica, Predicted=virginica, Probabilities=[0.00163488 0.2257053  0.77265982]
  Sample 3: True=versicolor, Predicted=versicolor, Probabilities=[0.06219769 0.92489506 0.01290725]
  Sample 4: True=versicolor, Predicted=versicolor, Probabilities=[0.02713645 0.96039078 0.01247277]
  Sample 5: True=setosa, Predicted=setosa, Probabilities=[9.99619292e-01 3.79305027e-04 1.40333585e-06]


MLP ANALYSIS COMPLETED SUCCESSFULLY


## STEP 6: MLP Architecture Analysis
```bash
MLP Architecture Details:
  Hidden layer sizes: (100,)
  Activation function: relu
  Learning rate: 0.01
  Alpha (L2 regularization): 0.01
  Total iterations: 76
```
Feature Importance (Permutation Importance):
  sepal length (cm): -0.0067 (+/- 0.0249)
  sepal width (cm): 0.0333 (+/- 0.0333)
  petal length (cm): 0.1533 (+/- 0.0636)
  petal width (cm): 0.2167 (+/- 0.1067)


FINAL SUMMARY - ALL THREE MODELS

### ALL MODEL ANALYSES COMPLETED 

```bash
Model Performance Summary:
        Model Test Accuracy Precision Recall F1-Score Training Time (s) Mean CV Score
  Naive Bayes        0.9667    0.9697 0.9667   0.9666            0.0022        0.9583
Decision Tree        0.9333    0.9333 0.9333   0.9333            0.0020        0.9417
          MLP        0.8000    0.8056 0.8000   0.7980            0.0142        0.8833
```
### Updated MLP model with Others
```bash
Model Performance Summary:
        Model Test Accuracy Precision Recall F1-Score Training Time (s) Mean CV Score
  Naive Bayes        0.9667    0.9697 0.9667   0.9666            0.0022        0.9583
Decision Tree        0.9333    0.9333 0.9333   0.9333            0.0020        0.9417
          MLP        0.9000    0.9024 0.9000   0.8997            0.0533        0.9583
```

ALL MODEL ANALYSES COMPLETED

--

Results saved to:
  - ../Output/output.txt (detailed results)
  - ../Output/Plots/ (visualizations)

