# DECISION TREE CLASSIFIER - IRIS DATASET

### STEP 1: Decision Tree Hyperparameter Tuning with Cross-Validation

Best Decision Tree Hyperparameters:
{'criterion': 'gini', 'max_depth': 5, 'min_samples_leaf': 1, 'min_samples_split': 2}
Best Cross-validation Score: `0.9417`

## STEP 2: Training Final Decision Tree Model

Training time: 0.0020 seconds

## STEP 3: Decision Tree Model Evaluation

Performance Metrics:

```bash
Accuracy: 0.9333
Precision: 0.9333
Recall: 0.9333
F1-Score: 0.9333
```

```bash
Detailed Classification Report:
precision recall f1-score support

      setosa       1.00      1.00      1.00        10

versicolor 0.90 0.90 0.90 10
virginica 0.90 0.90 0.90 10

    accuracy                           0.93        30

macro avg 0.93 0.93 0.93 30
weighted avg 0.93 0.93 0.93 30
```

### STEP 4: Decision Tree Confusion Matrix

Confusion Matrix:

```bash
[[10  0  0]
 [ 0  9  1]
 [ 0  1  9]]
```

STEP 6: Feature Importance Analysis

```bash
Feature Importance Scores:
petal length (cm): 0.5586
petal width (cm): 0.4060
sepal width (cm): 0.0292
sepal length (cm): 0.0062
```

STEP 7: Final Cross-validation Performance

```bash
Cross-validation scores: [0.91666667 0.95833333 0.95833333 0.95833333 0.91666667]
Mean CV accuracy: 0.9417 (+/- 0.0408)
```

STEP 8: Probability Analysis
First 5 test samples prediction probabilities:

```
Sample 1: True=setosa, Predicted=setosa, Probabilities=[1. 0. 0.]
Sample 2: True=virginica, Predicted=virginica, Probabilities=[0. 0. 1.]
Sample 3: True=versicolor, Predicted=versicolor, Probabilities=[0. 1. 0.]
Sample 4: True=versicolor, Predicted=versicolor, Probabilities=[0. 1. 0.]
Sample 5: True=setosa, Predicted=setosa, Probabilities=[1. 0. 0.]
```

DECISION TREE ANALYSIS COMPLETED SUCCESSFULLY

---
