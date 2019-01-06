#include "conjunto_letras.h"

Conjunto_Letras::Conjunto_Letras(){}

void Conjunto_Letras::inicializar(const multimap<int, char> & mapa_freq){
	multimap<int, char>::const_iterator it;
	int i=0;
	for(it=mapa_freq.begin(); it!=mapa_freq.end(); ++it){
		if (it->first == 0)
			array_trad[it->second-'a']=0;
		else
			array_trad[it->second-'a']=array_pts[i];
		++i;
	}
}

unsigned int Conjunto_Letras::traducir(const char* palabra, const char modalidad){
	unsigned int i=0, resultado=0, index;
	char caracter=palabra[i];
	if(modalidad=='P'){
		while (caracter!=0){
			index=caracter-'a';
			resultado+=array_trad[index];
			++i;
			caracter=palabra[i];
		}
	}else{
		while(caracter!=0){
			++i;
			caracter=palabra[i];
		}
		resultado=i-1;
	}
	return resultado;
}
