## **AI Assignment 4 – Benchmarking Machine Learning Models and LLMs**

**Course:** AI Assignment
**Student:** Gour Krishna Dey
**Roll No.:** MT24035

This assignment presents a comparative study between traditional Machine Learning (ML) models and Large Language Models (LLMs) using In-Context Learning.
Three datasets of varying complexity are used: **Iris**, **Wine**, and **Adult Income**.
The objective is to analyze the performance, consistency, and practical applicability of each learning approach across different data types.

Traditional ML models implemented:

- Gaussian Naive Bayes
- Decision Tree Classifier
- Multi-Layer Perceptron (MLP)

LLM predictions are generated using few-shot prompting and evaluated against ground-truth values.

The complete evaluation includes accuracy, precision, recall, F1-score, confusion matrices, visualizations, and dataset-specific observations.

---

## **Directory Structure**

```
ASSIGNMENT_4/
├── Data/                              # Raw and processed dataset files possessed all data that've been passed to LLM for few shot
│   ├── iris_train.csv
│   ├── iris_test.csv
│   ├── iris_test_no_target.csv
│   ├── wine_train.csv
│   ├── wine_test.csv
│   ├── wine_test_no_target.csv
│   └── wine_llm_response.csv
│
├── Output/                            # Stored evaluation results
|       ├── Plots/                     # Visualizations and analysis plots
|       │   ├── Adult_Dataset/
|       │   ├── iris_Dataset/
|       │   ├── Wine_Dataset/
|       │   ├── output_adult.txt
|       │   ├── output_iris.txt
|       │   ├── output_llm.txt
|       │   └── output_wine.txt
|       ├── output_adult.txt           # raw output of adult dataset
|       ├── output_iris.txt            # raw output of iris dataset
|       ├── output_llm.txt             # raw output of llm interaction and output
|       └── output_iris.txt            # raw output of iris dataset
|
├── src/                           # Source notebooks for all experiments
│   ├── iris_classification.ipynb
│   ├── wine_classification.ipynb
│   ├── adult_income_classification.ipynb
│   └── llm_evaluation.ipynb
│
├── Problem.pdf                    # Assignment problem statement
├── Problem.pdf                    # Assignment Report
├── PPT.pdf                        # Assignment PPT
└── README.md                      # assignment documentation
```

---

## **How to Run the assignment**

All executable code is located inside the **src/** directory.
Each notebook is self-contained and can be run independently.

### **1. Iris Dataset – `iris_classification.ipynb`**

- Loads Iris dataset.
- Trains Naive Bayes, Decision Tree, and MLP.
- Generates classification metrics.
- Produces plots stored under `Plots/iris_Dataset/`.

### **2. Wine Dataset – `wine_classification.ipynb`**

- Loads wine chemical composition data.
- Trains the three ML models.
- Evaluates model performance on test data.
- Stores results and plots under `Plots/Wine_Dataset/`.

### **3. Adult Income Dataset – `adult_income_classification.ipynb`**

- Performs preprocessing of mixed categorical and numerical features.
- Trains Naive Bayes, Decision Tree, and MLP.
- Computes evaluation metrics and visualizations.
- Outputs saved under `Plots/Adult_Dataset/`.

### **4. LLM Evaluation – `llm_evaluation.ipynb`**

- Reads LLM-generated predictions for each dataset.
- Compares LLM output with actual targets.
- Calculates all classification metrics.
- Writes evaluation summaries into the Output directory.
- Reference of LLM Interaction - https://chatgpt.com/share/691b9ff3-42e8-8007-a0a9-a342b8370ca3 

---

## **Assignment Summary**

The assignment demonstrates how ML models behave across datasets of increasing difficulty and highlights where LLMs succeed or fail in tabular classification tasks.
A detailed explanation of methodologies, architectures, evaluation metrics, and findings is provided in the accompanying **Report.pdf**.

---