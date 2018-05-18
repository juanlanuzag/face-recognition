rm nuestros/exp1-tiempos
touch nuestros/exp1-tiempos
for i in $(seq 1 80); do
    echo Corriendo para k=$i;
    ./main -m 0 -i ../tests/nuestros/ImagenesCaras80.train -q ../tests/nuestros/ImagenesCaras80.test -o /dev/null -knn-k $i >> ../tests/nuestros/exp1-tiempos;
done
