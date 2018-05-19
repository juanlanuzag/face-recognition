# face-recognition

TP2 Métodos Numéricos DC-UBA

[Informe](https://www.overleaf.com/16138812khstvghvmqjx)


-----

# Parametros del main
Parametros para correr el comando ./main :
-m  Method (0: knn solo)
-i  Path al archivo con el train_set
-q  Path al archivo con el test_set
-o  Path del archivo de salida con la clasificacion de los datos de test_set

Para m=0 (KNN):


Ejemplo:
    ./main -m 0 -i ../tests/nuestros/ImagenesCaras80.train -q ../tests/nuestros/ImagenesCaras80.test -o ../tests/nuestros/results


-----
# Datasets

Todo dataset tiene que estar en su propio directorio dentro de assets/, y adentro debe tener un directorio por cara a reconocer.

 NO TOCAR los datasets ImagenesCaras e ImagenesCarasRed provistos por la catedra.

-----
# Mediciones para metodos 2 y 3

Si se corre el main con -m 2 o -m 3 se generan dos archivos (ignora por completo el parámetro -q).

* El primero es el que le pasas por parámetro en -o y tiene un csv con los siguientes datos:

|method|train_set|knn-k|k-folds|alpha(solo para metodo 3)|test_fold|accuracy|
|:---: |:-------:|:---:|:-----:|:-----------------------:|:-------:|:------:|

* El segundo es el path de -o más la extensión .conf que tiene para cada fold su matriz de confusión. El formato del archivo es:

1: #filas_matriz_confusion #folds

2: Matriz de confusion para fold1

...

n: Matriz de confusion para fold2

...

etc



* En **tests/utils.py** hay 2 funciones que se usan para cada uno de los archivos:

* generateConfM(path) le pasas el path al archivo .conf y te devuelve una lista de matrices de confusion. A cada matriz de confusion le podes pedir accuracy, precision, recall o f1 (los ultimos 4 les tenes que dar la clase positiva)

* loadStats(path) toma el output -o del main y lo carga en un dataframe de pandas.

-----
## Problemas con dejar vector como Matrix

* Es feo iterar algo que sabes que es un vector, en vez de hacer V[i] tenés que hacer V[0][i].
* Para calcular score(X) me gustaria iterar los vectores de X y llamar a predict(X) pero predict toma Matrix.  

## Cosas knn

* Así como está hecho en caso de empate elige la clase de menor valor. <-- Cambio: a la hora de calcular la clase me guardo como "representante" de cada clase al elemento más cercano, desempato por ese. Otra opción sería tener la posición promedio de la clase y usar eso, evitaría el caso en que el representante es un outlier.

* En caso de que haya elementos equidistantes elimina el de mayor clase.
