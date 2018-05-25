import pandas as pd
from sklearn.metrics import accuracy_score, confusion_matrix
import utils
import numpy as np
from subprocess import call, check_output
import pickle

time_mesurements = []
k = 3
carpetas = ['ImagenesCaras', 'ImagenesX2', 'ImagenesX3', 'ImagenesX4', 'ImagenesX5', 'ImagenesX6']
for carpeta in carpetas:
    print(carpeta)
    result = check_output(['../src/experimentotiempos', '-m', str(0), '-i', '../tests/nuestros/{}80.train'.format(carpeta),'-q','../tests/nuestros/{}80.test'.format(carpeta), '-o', '/dev/null', '-knn-k', str(k)])
    print(result)
    time_mesurements.append(float(result))

with open('tiemposknntamanios.pkl', 'wb') as f:
    pickle.dump(time_mesurements, f)
