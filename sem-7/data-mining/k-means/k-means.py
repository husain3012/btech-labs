import matplotlib.pyplot as plt
import numpy as np
from matplotlib import style
style.use('ggplot')


X = np.random.rand(10,2)*50

X = [[5,   43],
     [36,  7],
     [1, 28],
     [21, 13],
     [33, 26],
     [14, 25],
     [18, 10],
     [24,  9],
     [20,  1],
     [28, 46]]
X = np.array(X)



plt.scatter(X[:, 0], X[:, 1], s=150)
plt.savefig('k-means/' + str('data') + ".png")

colors = ['red', 'green', 'blue']


class K_Means:
    def __init__(self, k=2, tolerance=0.001, max_iter=300):
        self.k = k
        self.tol = tolerance
        self.max_iter = max_iter

    def fit(self, data):

        self.centroids = {}

        for i in range(self.k):
            self.centroids[i] = data[len(data)-i-1]

        for i in range(self.max_iter):
            self.classifications = {}

            for i in range(self.k):
                self.classifications[i] = []

            for featureset in data:
                
                distances = [np.linalg.norm(
                    featureset-self.centroids[centroid]) for centroid in self.centroids]
                
                classification = distances.index(min(distances))
                self.classifications[classification].append(featureset)

            prev_centroids = dict(self.centroids)

            # calculate new centroid
            for classification in self.classifications:
                self.centroids[classification] = np.average(
                    self.classifications[classification], axis=0)

            optimized = True

            for c in self.centroids:
                original_centroid = prev_centroids[c]
                current_centroid = self.centroids[c]
                if np.sum((current_centroid-original_centroid)/original_centroid*100.0) > self.tol:
                    print(np.sum((current_centroid-original_centroid) /
                          original_centroid*100.0))
                    print('not optimized')
                    optimized = False

            if optimized:
                break

    def predict(self, data):
        distances = [np.linalg.norm(data-self.centroids[centroid])
                     for centroid in self.centroids]
        classification = distances.index(min(distances))
        return classification


if __name__ == "__main__":
    model = K_Means(2, 0.00000001, max_iter=1000)
    model.fit(X)

    for centroid in model.centroids:
        plt.scatter(model.centroids[centroid][0], model.centroids[centroid][1],
                    marker="o", color="k", s=150, linewidths=5)

    for classification in model.classifications:
        color = colors[classification]
        for featureset in model.classifications[classification]:
            plt.scatter(featureset[0], featureset[1],
                        marker="x", color=color, s=150, linewidths=5)

    plt.savefig('k-means/' + str('clustered') + ".png")
