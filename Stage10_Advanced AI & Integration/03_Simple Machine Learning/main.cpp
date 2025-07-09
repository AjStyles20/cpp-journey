#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <limits>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 2D Point structure with cluster assignment
struct Point {
    double x, y;
    int cluster;
    
    Point(double x = 0, double y = 0) : x(x), y(y), cluster(-1) {}
    
    double distanceTo(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

// K-Means Clustering class
class KMeans {
private:
    int k; // Number of clusters
    vector<Point> centroids;
    
    // Initialize centroids randomly from data points
    void initializeCentroids(vector<Point>& data) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, data.size() - 1);
        
        centroids.clear();
        for (int i = 0; i < k; i++) {
            int idx = dist(gen);
            centroids.push_back(data[idx]);
        }
    }
    
    // Assign each point to the nearest centroid
    void assignClusters(vector<Point>& data) {
        for (auto& point : data) {
            double minDist = numeric_limits<double>::max();
            for (int i = 0; i < k; i++) {
                double dist = point.distanceTo(centroids[i]);
                if (dist < minDist) {
                    minDist = dist;
                    point.cluster = i;
                }
            }
        }
    }
    
    // Update centroids to be the mean of their assigned points
    bool updateCentroids(const vector<Point>& data) {
        vector<Point> newCentroids(k, Point());
        vector<int> counts(k, 0);
        bool changed = false;
        
        // Sum all points in each cluster
        for (const auto& point : data) {
            newCentroids[point.cluster].x += point.x;
            newCentroids[point.cluster].y += point.y;
            counts[point.cluster]++;
        }
        
        // Calculate mean for each cluster
        for (int i = 0; i < k; i++) {
            if (counts[i] > 0) {
                newCentroids[i].x /= counts[i];
                newCentroids[i].y /= counts[i];
                
                // Check if centroid has moved
                if (newCentroids[i].distanceTo(centroids[i]) > 0.001) {
                    changed = true;
                }
            }
        }
        
        centroids = newCentroids;
        return changed;
    }
    
public:
    KMeans(int k) : k(k) {}
    
    // Run the clustering algorithm
    void fit(vector<Point>& data, int maxIterations = 100) {
        if (data.empty() || k <= 0) return;
        
        initializeCentroids(data);
        
        for (int iter = 0; iter < maxIterations; iter++) {
            assignClusters(data);
            bool centroidsChanged = updateCentroids(data);
            
            if (!centroidsChanged) {
                cout << "Converged after " << iter + 1 << " iterations\n";
                break;
            }
        }
    }
    
    // Predict cluster for new points
    int predict(const Point& point) {
        double minDist = numeric_limits<double>::max();
        int bestCluster = -1;
        
        for (int i = 0; i < k; i++) {
            double dist = point.distanceTo(centroids[i]);
            if (dist < minDist) {
                minDist = dist;
                bestCluster = i;
            }
        }
        
        return bestCluster;
    }
    
    // Get the current centroids
    const vector<Point>& getCentroids() const {
        return centroids;
    }
    
    // Calculate WCSS (Within-Cluster Sum of Squares)
    double calculateWCSS(const vector<Point>& data) const {
        double wcss = 0.0;
        for (const auto& point : data) {
            wcss += pow(point.distanceTo(centroids[point.cluster]), 2);
        }
        return wcss;
    }
};

// Generate sample data with three clusters
vector<Point> generateSampleData(int pointsPerCluster) {
    vector<Point> data;
    random_device rd;
    mt19937 gen(rd());
    
    // Cluster 1: Centered at (2, 2)
    normal_distribution<double> distX1(2.0, 0.7);
    normal_distribution<double> distY1(2.0, 0.7);
    for (int i = 0; i < pointsPerCluster; i++) {
        data.emplace_back(distX1(gen), distY1(gen));
    }
    
    // Cluster 2: Centered at (7, 7)
    normal_distribution<double> distX2(7.0, 1.0);
    normal_distribution<double> distY2(7.0, 1.0);
    for (int i = 0; i < pointsPerCluster; i++) {
        data.emplace_back(distX2(gen), distY2(gen));
    }
    
    // Cluster 3: Centered at (5, 2)
    normal_distribution<double> distX3(5.0, 0.5);
    normal_distribution<double> distY3(2.0, 0.5);
    for (int i = 0; i < pointsPerCluster; i++) {
        data.emplace_back(distX3(gen), distY3(gen));
    }
    
    return data;
}

// Print clustering results
void printResults(const vector<Point>& data, const KMeans& kmeans) {
    cout << "Centroids:\n";
    for (const auto& centroid : kmeans.getCentroids()) {
        cout << "Cluster " << centroid.cluster << ": (" 
             << centroid.x << ", " << centroid.y << ")\n";
    }
    
    cout << "\nWithin-Cluster Sum of Squares: " 
         << kmeans.calculateWCSS(data) << "\n";
    
    // Print first few points with their clusters
    cout << "\nSample points and their clusters:\n";
    for (size_t i = 0; i < min(data.size(), size_t(10)); i++) {
        cout << "Point (" << data[i].x << ", " << data[i].y 
             << ") -> Cluster " << data[i].cluster << "\n";
    }
}

int main() {
    // Generate sample data
    vector<Point> data = generateSampleData(100);
    
    // Create and run K-Means clustering
    KMeans kmeans(3); // We know there are 3 clusters in our sample data
    
    auto start = high_resolution_clock::now();
    kmeans.fit(data);
    auto end = high_resolution_clock::now();
    
    // Print results
    printResults(data, kmeans);
    
    // Performance measurement
    auto duration = duration_cast<microseconds>(end - start);
    cout << "\nClustering completed in " << duration.count() / 1000.0 << " ms\n";
    
    // Test prediction on new points
    cout << "\nPredicting clusters for new points:\n";
    Point test1(2.5, 2.5);
    Point test2(6.0, 6.0);
    Point test3(5.0, 1.8);
    
    cout << "Point (" << test1.x << ", " << test1.y << ") -> Cluster " 
         << kmeans.predict(test1) << "\n";
    cout << "Point (" << test2.x << ", " << test2.y << ") -> Cluster " 
         << kmeans.predict(test2) << "\n";
    cout << "Point (" << test3.x << ", " << test3.y << ") -> Cluster " 
         << kmeans.predict(test3) << "\n";
    
    return 0;
}