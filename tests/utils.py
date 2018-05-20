import numpy as np
import pandas as pd


def loadStats(path):
    return pd.read_csv(path, header=0, sep=',')


def generateConfM(path):
    """
    Dado un path a un archivo .conf devuelve una lista donde cargo cada una de
    las matrices de confusion respectivas a cada fold.
    """
    confMs = []
    with open(path, 'r') as file:
        n, folds = map(int, file.readline().split())
        for i in range(folds):
            confM = []
            for j in range(n):
                vector = np.array(list(map(int, file.readline().split())))
                confM.append(vector)
            cm = ConfusionM(matrix=confM)
            confMs.append(cm)
    return confMs


class ConfusionM:

    def __init__(self, n=0, matrix=[]):
        print(len(matrix), len(matrix[len(matrix)-1]))
        if matrix != []:
            self.matrix = np.array(matrix)
            self.total = sum([x for x in np.nditer(self.matrix)])
        else:
            self.matrix = np.zeros(shape=(n, n))
            self.total = 0

    def accuracy(self):
        correct = sum([self.matrix[i][i] for i in range(self.matrix.shape[0])])
        return float(correct)/self.total

    def precision(self, positive_class):
        tp = self.matrix[positive_class][positive_class]
        fp = sum([self.matrix[i][positive_class] for i in range(self.matrix.shape[0]) if i != positive_class])
        if tp == 0:
            return 0
        else:
            return float(tp) / (tp + fp)

    def recall(self, positive_class):
        tp = self.matrix[positive_class][positive_class]
        fn = sum([self.matrix[positive_class][i] for i in range(self.matrix.shape[0]) if i != positive_class])
        if tp == 0:
            return 0
        else:
            return float(tp) / (tp + fn)

    def f1Score(self, positive_class):
        p = self.precision(positive_class)
        r = self.recall(positive_class)
        return float(2 * p * r) / (p + r)
