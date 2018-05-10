# face-recognition

TP2 Métodos Numéricos DC-UBA

[Informe](https://www.overleaf.com/16138812khstvghvnqjx)

## Problemas con dejar vector como Matrix

* Es feo iterar algo que sabes que es un vector, en vez de hacer V[i] tenés que hacer V[0][i].
* Para calcular score(X) me gustaria iterar los vectores de X y llamar a predict(X) pero predict toma Matrix.  

## Cosas knn

* Así como está hecho en caso de empate elige la clase de menor valor. <-- Cambio: a la hora de calcular la clase me guardo como "representante" de cada clase al elemento más cercano, desempato por ese. Otra opción sería tener la posición promedio de la clase y usar eso, evitaría el caso en que el representante es un outlier.

* En caso de que haya elementos equidistantes elimina el de mayor clase.
