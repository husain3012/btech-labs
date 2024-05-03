
# import pandas
import pandas as pd
# import numpy
import numpy as np
from itertools import combinations
# read the data from data.txt


class Apriori:
    def __init__(self, min_support, threshold) -> None:
        self.min_support = min_support
        self.threshold = threshold
        self.items = []
        self.frequent_items_sets = []
        self.support = {}
    def load(self, df):
        self.df = df
        items=pd.unique(df.values.ravel('K'))
        self.items=sorted(items[~pd.isna(items)])
    def fit(self, debug=False):
        print('\nAlgo Started...\n')
        self.__fit_helper([(item,) for item in self.items], debug=debug)

    def info(self):
        print('Min Support: ', self.min_support)
        print('Threshold: ', self.threshold)
        print('No. of transactions:', len(self.df))
        print(f'Items ({len(self.items)}): ')
        for  idx, item in enumerate(self.items):
            print(f"{idx+1}. {item}")


    def __fit_helper(self, current_item_set, iter_no=1, debug=False):
        print(f'Iteration: {iter_no} ...', end='\r')
        
        # create a dictionary of counts
        count = {}
     
        for items in current_item_set:
            ctr = 0
            for index, row in self.df.iterrows():
                # print(list(row))
                if all(item in list(row) for item in items):
                    ctr += 1
            count[tuple(items)] = ctr
        # calculate support and confidence
     
        for item in count:
            self.support[item] = count[item]/len(self.df)
            if self.support[item] >= self.threshold:
                self.frequent_items_sets.append(item)

        # create new items list with items
        frequent_items = []
        for item in current_item_set:
            if self.support[tuple(item)] >= self.min_support:
                frequent_items.append(item)
        frequent_items = np.unique(np.array(frequent_items).flatten())


        new_item_set = list(combinations(frequent_items, iter_no+1))

        if debug:
            print('Item\t\tSupport')
            for item in count:
                print(f'{item}\t\t{self.support[item]}')
            print('Frequent Items: ', frequent_items)
        # if new item set is empty, return
        if len(new_item_set) == 0:
            return
        # if new item set is not empty, call fit helper with new item set
        self.__fit_helper(new_item_set, iter_no+1)
    

    def generate_rules(self):
        
        rules = []
        for item_set in self.frequent_items_sets:
            if len(item_set) > 1:
                for item in item_set:
                    rule = ((tuple(set(item_set)-set([item])), (item,)))
                    confidence = self.support[item_set]/self.support[tuple(set(item_set)-set([item]))]
                    if confidence >= self.threshold:
                        rules.append((rule, confidence))
        rules.sort(key=lambda x: x[1], reverse=True)
        return rules


if __name__ == "__main__":
    ap = Apriori(0.01, 0.1)
    df = pd.read_csv("apriori/Market_Basket_Optimisation.csv",header=None, index_col=False)
  
    ap.load(df)
    ap.info()
    ap.fit(debug=True)
    print('Frequent Items:', ap.frequent_items_sets)

    rules = ap.generate_rules()
    print('Rules:')
    for rule in rules:
        asc_rule, confidence = rule
        print(f'{asc_rule[0]} -> {asc_rule[1]} : {confidence}')

    