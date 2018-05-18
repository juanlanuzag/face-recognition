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
## Problemas con dejar vector como Matrix

* Es feo iterar algo que sabes que es un vector, en vez de hacer V[i] tenés que hacer V[0][i].
* Para calcular score(X) me gustaria iterar los vectores de X y llamar a predict(X) pero predict toma Matrix.  

## Cosas knn

* Así como está hecho en caso de empate elige la clase de menor valor. <-- Cambio: a la hora de calcular la clase me guardo como "representante" de cada clase al elemento más cercano, desempato por ese. Otra opción sería tener la posición promedio de la clase y usar eso, evitaría el caso en que el representante es un outlier.

* En caso de que haya elementos equidistantes elimina el de mayor clase.
