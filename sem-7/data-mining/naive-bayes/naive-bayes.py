import numpy as np
import pandas as pd


class NaiveBayes:
    def __init__(self) -> None:

        self.prior_probabilities = []
        self.conditional_probabilities = []
        self.features = []
        self.x = []
        self.y = []
        pass

    def fit(self, x, y):

        self.x = x
        self.y = y

        prior_probabilities = np.unique(y, return_counts=True)
        self.prior_probabilities = {}
        for i in range(len(prior_probabilities[0])):
            self.prior_probabilities[prior_probabilities[0][i]] = (
                prior_probabilities[1][i]+1) / (len(y)+len(prior_probabilities[0]))

        print(self.prior_probabilities)
        self.conditional_probabilities = []
        self.features = len(x[0])
        # store all the conditional probabilities in a dictionary, also take count of zero probabilities
        for i in range(self.features):
            feature_probability = {}
            unique_values = np.unique(x[:, i])
            for cond in np.unique(y):
                cond_indices = np.where(y == cond)[0]
                cond_count = len(cond_indices)

                feature_probability[cond] = {}
                for val in unique_values:
                    feature_probability[cond][val] = 0

                    cond_with_feature_count =len(np.where(x[cond_indices, i] == val)[0])
                    feature_probability[cond][val] = (
                        cond_with_feature_count+1) / (cond_count+len(unique_values))
            self.conditional_probabilities.append(feature_probability)
        print(self.conditional_probabilities)

    def predict(self, x):
        results = []
        for i in range(len(x)):
            results.append(self.__predict(x[i]))
        return results

    def __predict(self, x):
        results = {}
        for cond in self.prior_probabilities:
           
            results[cond] = (self.prior_probabilities[cond])
            for j in range(self.features):
                results[cond] *= self.conditional_probabilities[j][cond][x[j]]
        return max(results, key=results.get)


def train_test_split(X, Y, frac):
    # Calculate the number of test samples
    num_test = int(len(Y) * frac)

    # Generate a random permutation of the indices
    indices = np.random.permutation(len(Y))

    # Split the indices into train and test
    test_indices = indices[:num_test]
    train_indices = indices[num_test:]

    # Use the indices to get the train and test sets
    X_train = X[train_indices]
    X_test = X[test_indices]
    Y_train = Y[train_indices]
    Y_test = Y[test_indices]

    return X_train, X_test, Y_train, Y_test


def accuracy_score(Y_test, Y_pred):
    # Check if test and prediction lengths are equal
    if len(Y_test) != len(Y_pred):
        return "Length of test data and prediction data do not match"

    # Calculate the number of correct predictions
    correct_predictions = sum(y_t == y_p for y_t, y_p in zip(Y_test, Y_pred))

    # Calculate the accuracy
    accuracy = correct_predictions / len(Y_test)

    return accuracy


if __name__ == "__main__":
    df = pd.read_csv('decision-tree/data.csv')
    print(df.head())
    X = df.iloc[:, 1:-1].values
    Y = df.iloc[:, -1].values.reshape(-1, 1)
    X_train, X_test, Y_train, Y_test = train_test_split(X, Y, 0.3)
    print(f'Train Size: {len(X_train)}')
    print(f'Test Size: {len(X_test)}')

    model = NaiveBayes()
    model.fit(X_train, Y_train)
    Y_pred = model.predict(X_test)
    print(Y_pred)
    print(accuracy_score(Y_test, Y_pred))
