
import pandas as pd
import numpy as np
from itertools import combinations


class Node():
    def __init__(self, feature_index=None, threshold=None, left=None, right=None, info_gain=None, value=None):
        
        self.feature_index = feature_index
        self.threshold = threshold
        self.left = left
        self.right = right
        self.info_gain = info_gain
        
        # for leaf node
        self.value = value

    def __repr__(self) -> str:
        return f"Node({self.feature_index}, {self.threshold}, {self.info_gain}, {self.value})"

class DecisionTree:
    def __init__(self, max_depth, min_samples_split) -> None:
        self.root = None
        self.max_depth = max_depth
        self.min_samples_split = min_samples_split
    def fit(self, X, Y):

        
        dataset = np.concatenate((X, Y), axis=1)
        self.root = self.__build_tree(dataset)

    def predict(self, X):
        ''' function to predict new dataset '''
        
        predations = [self.__make_prediction(x, self.root) for x in X]
        return predations
    
    def __make_prediction(self, x, tree):
        ''' function to predict a single data point '''
        
        if tree.value!=None: return tree.value
        feature_val = x[tree.feature_index]
        if feature_val<=tree.threshold:
            return self.__make_prediction(x, tree.left)
        else:
            return self.__make_prediction(x, tree.right)


    def __build_tree(self, dataset, curr_depth=0):
        X, y = dataset[:, :-1], dataset[:, -1]
        num_samples, num_features = np.shape(X)
        if num_samples >= self.min_samples_split and curr_depth <= self.max_depth:
            best_split = self.__get_best_split(dataset, num_samples, num_features)
            if best_split["info_gain"] > 0:
                left_subtree = self.__build_tree(best_split["dataset_left"], curr_depth + 1)
                right_subtree = self.__build_tree(best_split["dataset_right"], curr_depth + 1)
                return Node(best_split["feature_index"], best_split["threshold"], left_subtree, right_subtree, best_split["info_gain"])
        leaf_value = self.__calculate_leaf_value(y)
        return Node(value=leaf_value)


    def __get_best_split(self, dataset, num_samples, num_features):
        best_split = {}
        max_info_gain = -float("inf")
        for feature_idx in range(num_features):
            feature_values = dataset[:, feature_idx]
            possible_thresholds = np.unique(feature_values)

            for threshold in possible_thresholds:

                left = dataset[feature_values <= threshold]
                right = dataset[feature_values > threshold]

                if len(left) > 0 and len(right) > 0:
                    y, left_y, right_y = dataset[:, -1], left[:, -1], right[:, -1]
                    curr_info_gain = self.__information_gain(y, left_y, right_y, "gini")
                    if curr_info_gain > max_info_gain:
                        best_split["feature_index"] = feature_idx
                        best_split["threshold"] = threshold
                        best_split["dataset_left"] = left
                        best_split["dataset_right"] = right
                        best_split["info_gain"] = curr_info_gain
                        max_info_gain = curr_info_gain
        return best_split
    
    def __calculate_leaf_value(self, y):
        y = list(y)
        return max(y, key=y.count)
    
    def print_tree(self, tree=None, indent=" "):
        ''' function to print the tree '''
        
        if not tree:
            tree = self.root

        if tree.value is not None:
            print(tree.value)

        else:
            print("X_"+str(tree.feature_index), "<=", tree.threshold, "?", tree.info_gain)
            print("%sleft:" % (indent), end="")
            self.print_tree(tree.left, indent + indent)
            print("%sright:" % (indent), end="")
            self.print_tree(tree.right, indent + indent)

    
    
    def __information_gain(self, parent, l_child, r_child, mode="entropy"):
        weight_l = len(l_child) / len(parent)
        weight_r = len(r_child) / len(parent)
        if mode == "entropy":
            gain = self.__entropy(parent) - (weight_l * self.__entropy(l_child) + weight_r * self.__entropy(r_child))
        elif mode == "gini":
            gain = self.__gini(parent) - (weight_l * self.__gini(l_child) + weight_r * self.__gini(r_child))
        else:
            raise Exception("Unknown mode")
        return gain
    def __entropy(self, y):
        unique_labels = np.unique(y)
        entropy = 0
        for label in unique_labels:
            p = len(y[y == label]) / len(y)
            entropy += -p * np.log2(p)
        return entropy
    def __gini(self, y):
        unique_labels = np.unique(y)
        gini = 1
        for label in unique_labels:
            p = len(y[y == label]) / len(y)
            gini -= p ** 2
        return gini
    
    
    




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
    df = pd.read_csv('decision-tree/breast-cancer.csv')
    print(df.head())
    X = df.iloc[:, 1:-1].values
    Y = df.iloc[:, -1].values.reshape(-1,1)
    X_train, X_test, Y_train, Y_test = train_test_split(X, Y, 0.3)
    print(f'Train Size: {len(X_train)}')
    print(f'Test Size: {len(X_test)}')
    classifier = DecisionTree(max_depth=5,  min_samples_split=2)
    classifier.fit(X_train,Y_train)
    classifier.print_tree()



    # Test the model
    Y_pred = classifier.predict(X_test) 
    acc = accuracy_score(Y_test, Y_pred)
    print(f'Accuracy Score: {acc}')