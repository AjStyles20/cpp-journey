# 03_Simple Machine Learning: K-Means Clustering

## Description

This project demonstrates the K-Means clustering algorithm on synthetic 2D data. The program generates sample data with three clusters, applies K-Means to group the data, and evaluates the clustering performance. It also predicts the cluster assignment for new, unseen points.

---

## Features

- Generates synthetic 2D data with three distinct clusters
- Implements the K-Means clustering algorithm from scratch
- Random centroid initialization and iterative refinement
- Calculates Within-Cluster Sum of Squares (WCSS) for evaluation
- Prints cluster centroids, sample assignments, and performance metrics
- Predicts cluster membership for new data points

---

## How to Run

1. **Compile the code:**
   ```bash
   g++ main.cpp -o kmeans_demo -std=c++11
   ```

2. **Run the program:**
   ```bash
   ./kmeans_demo
   ```
   or on Windows:
   ```powershell
   .\kmeans_demo.exe
   ```

---

## Example Output

```
Converged after 7 iterations
Centroids:
Cluster 0: (1.98, 2.01)
Cluster 1: (7.05, 6.98)
Cluster 2: (5.01, 2.02)

Within-Cluster Sum of Squares: 98.7

Sample points and their clusters:
Point (2.12, 1.85) -> Cluster 0
Point (1.95, 2.23) -> Cluster 0
...

Clustering completed in 3.2 ms

Predicting clusters for new points:
Point (2.5, 2.5) -> Cluster 0
Point (6.0, 6.0) -> Cluster 1
Point (5.0, 1.8) -> Cluster 2
```

---

## Learning Objectives

- Understand and implement the K-Means clustering algorithm
- Practice random initialization and iterative optimization
- Learn how to evaluate clustering quality with WCSS
- Gain experience with synthetic data generation and prediction in C++

---

This project provides a hands-on introduction to unsupervised machine learning and clustering in C++.