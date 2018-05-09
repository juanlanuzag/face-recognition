#include <iostream>
#include "ppmloader.h"

using namespace std;

typedef unsigned char uchar;

void test_load(){
  PGMImage imagen;
  imagen.load("square.pgm");

  vector<double> datos = imagen.data_to_vec();

  cout << imagen.width << " " << imagen.height << endl;
  for (auto it = datos.begin(); it!=datos.end(); it++){
      cout << *it << endl;
  }
}

void test_save(){

  string comments = "";

  PGMImage img;
  img.width = 3;
  img.height = 3;
  uchar* data = new uchar[img.width * img.height];
  data[0] = 100;
  data[1] = 110;
  data[2] = 120;
  data[3] = 100;
  data[4] = 110;
  data[5] = 120;
  data[6] = 100;
  data[7] = 110;
  data[8] = 120;

  img.data = data;

  img.save("square.pgm", comments);
}

void test_face_line_n_save() {
    PGMImage imagen;
    imagen.load("../../assets/ImagenesCarasRed/s1/4.pgm");

    for(int j=0; j<imagen.width; j++) {
        imagen.data[imagen.width*3 + j] = 255; //Pinto toda la fila 3 de blanco
    }
    imagen.save("cara_con_raya.pgm", "Soy un comentario");
}

void test_flatten_face() {
    PGMImage imagen1;
    imagen1.load("../../assets/ImagenesCarasRed/s1/4.pgm");

    PGMImage imagen2;
    imagen2.width = imagen1.width * imagen1.height;
    imagen2.height = 1;
    uchar* data = new uchar[imagen2.width * imagen2.height];

    for (int i =0; i< imagen2.width * imagen2.height; i++){
        data[i] = imagen1.data[i];
    }
    imagen2.data = data;
    imagen2.save("cara_width1.pgm", "Soy un comentario");
}

int main() {

  test_load();
  test_save();
  test_face_line_n_save();
  test_flatten_face();


  return 0;
}
