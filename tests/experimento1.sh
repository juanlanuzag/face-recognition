for i in $(seq 1 20); do
    echo Corriendo para k=$i;
    ./main -m 0 -i ../tests/nuestros/ImagenesCaras80.train -q ../tests/nuestros/ImagenesCaras80.test -o ../tests/nuestros/knnsolo$i -k $i;
done
