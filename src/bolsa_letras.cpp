#include "bolsa_letras.h"

using namespace std;

map<char, int> Bolsa_Letras::convertir(const multimap<int, char>& mm){
	multimap<int, char>::const_iterator it;
	map<char, int> retorno;
	pair<char, int> aux;
	for (it=mm.begin(); it!=mm.end(); ++it){
		aux.first=it->second;
		aux.second=it->first;
		retorno.insert(aux);
	}
	return retorno;
}

Bolsa_Letras::Bolsa_Letras(){
	srand(0);
}

Bolsa_Letras::Bolsa_Letras(multimap<int, char>& mm, unsigned int nl, unsigned int tl){
	renovar(mm, nl, tl);
}

void Bolsa_Letras::renovar(multimap<int, char>& mm, unsigned int nl, unsigned int tl){
	unsigned int acumulada=0;
	multimap<int, char>::iterator it;
	vector<unsigned int> posiciones;
	vector<unsigned int>::iterator vit;
	int alea;
	
	letras.clear();
	
	/*Sea L el conjunto total de letras, sea M el multimap frecuencia-caracter derivado de L.
	El algoritmo de obtención de n letras aleatorias en L será:
	 1- Generamos n números aleatorios entre 0 y |N|-1
	 2- Obtenemos los caracteres en las posiciones que marcan los números aleatorios obtenidos de la manera:
	    2.1-Calculamos la frecuencia absoluta acumulada de cada caracter
	    2.2-Para cada número aleatorio, obtenemos el caracter con la f.acumulada más pequeña de las que superan al número
	*/
	for (unsigned int i=0; i<nl; ++i){
		alea=aleatorio(0, tl-1);
		posiciones.insert(posiciones.end(), alea);
	}
	
	sort(posiciones.begin(), posiciones.end());
	it=mm.begin();
	
	for(vit=posiciones.begin(); vit!=posiciones.end(); ++vit){
		while(acumulada<*vit){
			acumulada+=it->first;
			++it;
		}
		--it;
		anadir(it->second);
		++it;
	}
	
	map<char, int>::const_iterator auxit;
	cout << "RENOVAMOS" << endl;
	/*for(auxit=letras.begin(); auxit!=letras.end(); ++auxit){
		for(int i=0; i < auxit->second; ++i)
			cout << auxit->first << " - ";
	}*/
}

void Bolsa_Letras::anadir(char c){
	map<char, int>::iterator it=letras.find(c);
	if(it!=letras.end())
		it->second++;
	else
		letras[c]=1;
}

void Bolsa_Letras::quitar(char c){
	map<char, int>::iterator it=letras.find(c);
	if(it!=letras.end()){
		it->second--;
		if(it->second==0)
			letras.erase(it);
	}
}

bool Bolsa_Letras::palabr_ok(const char* palabra){
	map<char, int> letras_aux;
	map<char, int>::const_iterator it;
	map<char, int>::iterator it_aux;
	unsigned int i=0;
	char caracter=palabra[i];
	bool retorno=true;
	
	//1- Creamos un map caracter-freq con los caracteres de la palabra
	while (caracter!=0){
		it_aux=letras_aux.find(caracter);
		if(it_aux!=letras_aux.end())
			it_aux->second++;
		else
			letras_aux[caracter]=1;
		++i;
		caracter=palabra[i];
	}
	
	//2- Comprobamos si este es un sub-mapa del de la bolsa principal
	for(it_aux=letras_aux.begin(); it_aux!=letras_aux.end(); ++it_aux){
		it=letras.find(it_aux->first);
		if (it==letras.end()){
			retorno=false;
			break;
		}else if (it->second < it_aux->second){
			retorno=false;
			break;
		}
	}
	return retorno;
}

Bolsa_Letras::iterator Bolsa_Letras::erase(iterator it){
	Bolsa_Letras::iterator retorno;
	retorno.set_it(letras.erase(it.get_it()));
	return retorno;
}

Bolsa_Letras Bolsa_Letras::operator=(const Bolsa_Letras & b){
	letras=b.letras;
	return *this;
}
