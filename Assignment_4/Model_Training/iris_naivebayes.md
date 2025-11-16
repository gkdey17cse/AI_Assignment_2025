# IRIS DATASET - NAIVE BAYES ANALYSIS

## STEP 1: Loading and Exploring Iris Dataset

Dataset Shape: (150, 4)
Features: ['sepal length (cm)', 'sepal width (cm)', 'petal length (cm)', 'petal width (cm)']
Target Classes: [np.str_('setosa'), np.str_('versicolor'), np.str_('virginica')]
Class Distribution: [50 50 50]

```bash
	sepal length (cm)	sepal width (cm)	petal length (cm)	petal width (cm)	target	species
0	5.1	3.5	1.4	0.2	0	setosa
1	4.9	3.0	1.4	0.2	0	setosa
2	4.7	3.2	1.3	0.2	0	setosa
3	4.6	3.1	1.5	0.2	0	setosa
4	5.0	3.6	1.4	0.2	0	setosa
...	...	...	...	...	...	...
145	6.7	3.0	5.2	2.3	2	virginica
146	6.3	2.5	5.0	1.9	2	virginica
147	6.5	3.0	5.2	2.0	2	virginica
148	6.2	3.4	5.4	2.3	2	virginica
149	5.9	3.0	5.1	1.8	2	virginica

```

## STEP 2: Data Preprocessing

Training set size: 120
Test set size: 30
Training set class distribution: [40 40 40]
Test set class distribution: [10 10 10]

### STEP 3: Hyperparameter Tuning with Cross-Validation
Cross-validation Results:
```bash
var_smoothing=1e-09: Mean CV Accuracy = 0.9583
var_smoothing=1e-08: Mean CV Accuracy = 0.9583
var_smoothing=1e-07: Mean CV Accuracy = 0.9583
var_smoothing=1e-06: Mean CV Accuracy = 0.9583
var_smoothing=1e-05: Mean CV Accuracy = 0.9583
var_smoothing=0.0001: Mean CV Accuracy = 0.9583
var_smoothing=0.001: Mean CV Accuracy = 0.9583
var_smoothing=0.01: Mean CV Accuracy = 0.9583
var_smoothing=0.1: Mean CV Accuracy = 0.9583
```

Best Hyperparameters: {'var_smoothing': 1e-09}
Best Cross-validation Score: `0.9583`

### STEP 4: Training Final Model
Training time: 0.0022 seconds

### STEP 5: Model Evaluation
Performance Metrics:
```bash
Accuracy: 0.9667
Precision: 0.9697
Recall: 0.9667
F1-Score: 0.9666
```

Detailed Classification Report:
precision recall f1-score support
```bash
      setosa       1.00      1.00      1.00        10

versicolor 1.00 0.90 0.95 10
virginica 0.91 1.00 0.95 10

    accuracy                           0.97        30

macro avg 0.97 0.97 0.97 30
weighted avg 0.97 0.97 0.97 30
```

### STEP 6: Confusion Matrix
Confusion Matrix:
```bash
[[10  0  0]
 [ 0  9  1]
 [ 0  0 10]]
```

### STEP 7: Feature Importance Analysis
Class-wise Feature Means:
```bash
setosa: [-1.02298939 0.8209241 -1.30171662 -1.25085752]
versicolor: [ 0.10548334 -0.6679337 0.27397089 0.15141959]
virginica: [ 0.91750605 -0.1529904 1.02774573 1.09943792]
```
Class-wise Feature Variances:
```bash
setosa: [0.13229685 0.77833164 0.00813895 0.02249447]
versicolor: [0.31600087 0.46617191 0.06174031 0.05911843]
virginica: [0.6522509 0.6120386 0.10433325 0.12205094]
```

### STEP 8: Probability Analysis
First 5 test samples prediction probabilities:
```bash
Sample 1: True=setosa, Predicted=setosa, Probabilities=[1.00000000e+00 2.10423314e-20 1.24046578e-25]
Sample 2: True=virginica, Predicted=virginica, Probabilities=[8.47863245e-143 8.77457737e-002 9.12254226e-001]
Sample 3: True=versicolor, Predicted=versicolor, Probabilities=[2.60593948e-36 9.99999490e-01 5.10180419e-07]
Sample 4: True=versicolor, Predicted=versicolor, Probabilities=[1.34649967e-36 9.99999567e-01 4.32500769e-07]
Sample 5: True=setosa, Predicted=setosa, Probabilities=[1.00000000e+00 6.60691119e-21 6.79223517e-26]
```

### STEP 9: Final Cross-validation Performance
Cross-validation scores: [0.91666667 0.95833333 1. 0.95833333 0.95833333]
Mean CV accuracy: `0.9583 (+/- 0.0527)`

STEP 10: Feature Distribution Analysis
Feature distribution plots saved to '../Output/Plots/Feature_Distribution_Iris.png'
Feature boxplots saved to '../Output/Plots/Feature_Boxplots_Iris.png'

NAIVE BAYES ANALYSIS COMPLETED SUCCESSFULLY

---

