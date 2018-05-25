from os import listdir
from os.path import isfile, join, isdir
import pandas as pd
from math import floor


def listdir_paths(path):
    return [join(path, fil) for fil in listdir(path)]


def dataset_to_dict(dataset_path):
    data = {}
    for person_file in listdir(dataset_path):
        person_path = join(dataset_path, person_file)
        if isdir(person_path):
            data[person_file] = []
            for img_file in listdir(person_path):
                if isfile(join(person_path, img_file)):
                    data[person_file].append(join(person_path, img_file))
    return data


def dataset_to_df(dataset_path):
    return pd.DataFrame(dataset_to_dict(dataset_path))


def split_dataset(dataset_path, frac):
    df = dataset_to_df(dataset_path)
    total = len(df.index)
    train = floor(total * frac)
    test = total - train
    return (df[0:train], df[-test:])


def colname_to_int(col):
    return ''.join(c for c in col if c.isdigit())


def traindf_to_csv(df, path):
    with open(path, 'w') as archivo:
        for key, col in df.iteritems():
            for index, elem in col.iteritems():
                archivo.write(elem + ', ' + colname_to_int(key) + ',\n')


def testdf_to_csv(df, pathtest, pathexpected):
    with open(pathtest, 'w') as archivo:
        for key, col in df.iteritems():
            for index, elem in col.iteritems():
                archivo.write(elem + ',\n')
    with open(pathexpected, 'w') as archivo:
        for key, col in df.iteritems():
            for index, elem in col.iteritems():
                archivo.write(colname_to_int(key) + ',\n')


# Main
carpetas = ['ImagenesCaras', 'ImagenesX2', 'ImagenesX5', 'ImagenesX7', 'ImagenesX10']
for carpeta in carpetas:
    (train_df, test_df) = split_dataset('../assets/{}'.format(carpeta), 0.8)
    traindf_to_csv(train_df, 'nuestros/{}80.train'.format(carpeta))
    testdf_to_csv(test_df, 'nuestros/{}80.test'.format(carpeta),
                  'nuestros/{}80.expected'.format(carpeta))
