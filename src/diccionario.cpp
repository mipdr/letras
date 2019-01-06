#include "diccionario.h"

using namespace std;
	

Diccionario::Diccionario(unsigned int p){
	profundidad=p;
	nodo=new Nodo[N_LETRAS];
	for (int i=0; i<N_LETRAS; ++i){
		nodo[i]=(Nodo){0};
	}
}

Diccionario::~Diccionario(){
	for (int i=0; i<N_LETRAS; ++i){
		if(nodo[i].hijo != NULL){
			nodo[i].hijo->~Diccionario();
		}
	}
	delete[] nodo;
}

Diccionario Diccionario::operator[](unsigned int index) const{
	return *(nodo[index].hijo);
}

Diccionario Diccionario::operator=(const Diccionario &dic) {
	this->profundidad=dic.profundidad;
	nodo=new Nodo[N_LETRAS];
	
	for(int i=0; i<N_LETRAS; ++i){
		if(this->nodo[i].hijo != NULL)
			this->nodo[i].hijo->~Diccionario();
		
		if (dic.nodo[i].hijo != NULL){
			this->nodo[i].hijo=new Diccionario(profundidad+1);
			*(nodo[i].hijo)=*(dic.nodo[i].hijo); //Llamada recursiva
		}
		this->nodo[i].dat_busqd=dic.nodo[i].dat_busqd;
	}
	
	return *this;
}

bool Diccionario::registrar(const char* cadena, int* recuento){
	char caracter=cadena[profundidad];
	char carac_siguiente=cadena[profundidad+1];
	unsigned int index=caracter-'a';
	bool exito=false;
	
	recuento[index]++;//Para obtener frecuencias absolutas de aparicion
	if(carac_siguiente=='\0'){
		//Si llegamos al final de la palabra, indicamos la presencia de 
		//la palabra
		nodo[index].dat_busqd |= AQUI_PALABRA;
		exito=true;
	}else{
		//Si estamos en mitad de la palabra, indicamos por donde seguir
		//y seguimos registrando
		if (nodo[index].hijo==NULL)
			nodo[index].hijo=new Diccionario(profundidad+1);
		nodo[index].dat_busqd |= SEGUIR_BUSCANDO;
		nodo[index].hijo->registrar(cadena, recuento);
	}
	
	return exito;
}

bool Diccionario::contiene(const char* cadena) const{	
	char caracter=cadena[this->profundidad];
	char carac_siguiente=cadena[this->profundidad+1];
	unsigned int index=caracter - 'a';
	bool retorno;
	
	if(carac_siguiente=='\0'){
		//Si hemos llegado al final de la palabra, comprobamos si se ha
		//registrado
		retorno= (nodo[index].dat_busqd & AQUI_PALABRA) == AQUI_PALABRA;
	}else{
		//Si no hemos llegado, comprobamos si sigue habiendo palabras por
		//este camino para seguir buscando o no
		if((nodo[index].dat_busqd & SEGUIR_BUSCANDO) == SEGUIR_BUSCANDO)
			retorno= nodo[index].hijo->contiene(cadena);
		else
			retorno= false; 
	}
	return retorno;
}
