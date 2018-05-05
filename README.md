# face-recognition

TP2 Métodos Numéricos DC-UBA

## Problemas con dejar vector como Matrix

* Es feo iterar algo que sabes que es un vector, en vez de hacer V[i] tenés que hacer V[0][i].
* Para calcular score(X) me gustaria iterar los vectores de X y llamar a predict(X) pero predict toma Matrix.  

## Cosas knn

* Así como está hecho en caso de empate elige la clase de menor valor.
* En caso de que haya elementos equidistantes elimina el de mayor clase.
