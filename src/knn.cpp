#include "knn.h"
#include <cassert>
#include <math.h>
#include <map>
#include <set>
#include "confusionM.h"
#include <algorithm> 

double euclid_dist(vector<double>& v, vector<double>& w);


KNN::KNN(Matrix& A, vector<int>& y, int n_neigh = 10): k(n_neigh), data(A), tags(y)
{
	unsigned int n_tags = tags.size();
	unsigned int n_data = data.dimensions().first;
	assert(n_tags == n_data);
};

int KNN::predict(vector<double>& img){
	/*
	Funcion de clasificacion KNN.
	O(n*d*log(k)) con:
		n = cantidad de datos de entrenamiento
		d = tamaño de un dato de entrenamiento
		k = cantidad de vecinos con los que se clasifica
	*/
	set<pair<double, double> > k_dists;
	map<double, pair<int, double> > votes; 

	for(int i = 0; i < this->data.dimensions().first; i++){
	// Invariante: en la iteracion i, k_dists tiene los k puntos de data[0..i]
	//             más cercanos a img

		double tag = this->tags[i];
		double dist = euclid_dist(img, this->data[i]);
		if((int)k_dists.size() < this->k){
			k_dists.insert(make_pair(dist, tag));
			if(votes[tag].first == 0){
				votes[tag].second = dist;
			} else if(dist < votes[tag].second) {
				votes[tag].second = dist;
			}
			votes[tag].first++;
		} else {
			auto last_elem = k_dists.rbegin();
			if(dist < last_elem->first){
				votes[last_elem->second].first--;
				k_dists.erase(*last_elem);

				k_dists.insert(make_pair(dist, tag));

				if(votes[tag].first == 0){
					votes[tag].second = dist;
				} else if(dist < votes[tag].second) {
					votes[tag].second = dist;
				}
				votes[tag].first++;
			}
		}
	}

	int max_tag = -1;
	int max_votes = -1;

	for(auto it : votes){ //Recuento de votos
		if(it.second.first > max_votes){
			max_tag = it.first;
			max_votes = it.second.first;
		} else if(it.second.first == max_votes){
			if(it.second.second < votes[max_tag].second){
				max_tag = it.first;
				max_votes = it.second.first;
			}
		}
	}
	return max_tag;
}

double euclid_dist(vector<double>& v, vector<double>& w){
	assert(v.size() == w.size());
	double dist = 0;
	for(unsigned int i = 0; i < v.size(); i++){
		dist += pow (v[i] - w[i], 2);
	}
	return sqrt(dist);
}

double KNN::p_predict(vector<double>& v, char metric){
	/*
	Devuelve la medida de confianza con la que el clasificador elige la clase.
	IN:
		v 	= entrada a clasificar
		metric 	= metodo utilizado para calcular el resultado: (por ahora lo ignora)
				'a' -> amount, cantidad de votos de la clase ganadora sobre el total
				'd' -> distancia de la muestra a la clase que que predijo (falta hacer)
	OUT:
		out = confianza en la clase predecida segun la metrica
	*/

	set<pair<double, double> > k_dists;
	map<double, pair<int, double> > votes;

	for(int i = 0; i < this->data.dimensions().first; i++){
	// Invariante: en la iteracion i, k_dists tiene los k puntos de data[0..i]
	//             más cercanos a v.
		double tag = this->tags[i];
		double dist = euclid_dist(v, this->data[i]);
		if((int)k_dists.size() < this->k){
			k_dists.insert(make_pair(dist, tag));
			if(votes[tag].first == 0){
				votes[tag].second = dist;
			} else if(dist < votes[tag].second) {
				votes[tag].second = dist;
			}
			votes[tag].first++;
		} else {
			auto last_elem = k_dists.rbegin();
			if(dist < last_elem->first){
				votes[last_elem->second].first--;
				k_dists.erase(*last_elem);

				k_dists.insert(make_pair(dist, tag));

				if(votes[tag].first == 0){
					votes[tag].second = dist;
				} else if(dist < votes[tag].second) {
					votes[tag].second = dist;
				}
				votes[tag].first++;
			}
		}
	}

	int max_tag = -1;
	int max_votes = 0;
	int total_votes = 0;
	for(auto it : votes){
		if(it.second.first > max_votes){
			max_tag = it.first;
			max_votes = it.second.first;
		} else if(it.second.first == max_votes){
			if(it.second.second < votes[max_tag].second){
				max_tag = it.first;
				max_votes = it.second.first;
			}
		}
		total_votes += it.second.first;
	}
	return (double)max_votes / total_votes;
}

ConfusionM KNN::score(Matrix& A, vector<int>& y){
	/*
	Toma un dataset de validacion y calcula el score del modelo en funcion de metric
	IN:
		A 	= matriz donde cada fila es un elemento a clasificar
		y[i] 	= tag del elemento A[i]
	OUT:
		conf = matriz de confusion para el dataset de validacion
	*/
	int max_tag = *max_element(y.begin(), y.end());	
	ConfusionM conf = ConfusionM(max_tag);

	for(int i = 0; i < A.dimensions().first; i++){
		int prediction = this->predict(A[i]);
		conf.update(y[i], prediction);
	}

	return conf;
}
