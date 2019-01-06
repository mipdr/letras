#include "juego.h"

Juego::Juego(ifstream& input, int nl, char mod):dic(0){
	t_letras=0;
	recuento=new int[N_LETRAS];	
	//Inicializamos dic y recuento con operator>> de Diccionario
	input >> dic;
	//Inicializamos n_letras
	n_letras=nl;
	//Inicializamos modalidad
	modalidad=mod;
	//Inicializamos t_letras
	for(int i=0; i<N_LETRAS; ++i){
		t_letras+=recuento[i];
	}
	//Inicializamos multimap frecuencia-caracter
	ini_mapa();
	//Inicializamos conjunto
	conjunto.inicializar(mapa);
}

void Juego::ini_mapa(){
	multimap<int, char>::const_iterator it;
	pair<int, char> aux_p;
	for (int i=0; i<N_LETRAS; ++i){
		aux_p.second=i+'a';
		aux_p.first=(recuento[i]);
		mapa.insert(aux_p);
	}
}

void Juego::jugar(){
	string palabra;
	const char* palabra_c;
	bool ok=true, seguir_jugando=true;
	string opcion_jugador;
	unsigned int puntos;
	Soluciones sol;
	vector<string>::iterator it;
	char char_imprimir[2]={'a', 0};
	
	cout << "REGLAS\nLas reglas son simples, te dare un conjunto de letras para que intentes formar la palabra de mayor ";
	if(modalidad=='P'){
		cout << "puntuacion." << endl;
		cout << "Las puntuaciones que aportan las letras son las siguientes: " << endl;
		for(int i=0; i<N_LETRAS; ++i){
			char_imprimir[0]=i+'a';
			palabra=char_imprimir;
			cout << "\t" << palabra << " - " << conjunto.traducir(char_imprimir, modalidad) << endl;
		}
	}else{
		cout << "longitud." << endl;
	}
	
	cout << "NOTA: No se distinguirán caracteres especiales de sus versiones estandarizadas." << endl;
	
	while(seguir_jugando){
		bolsa.renovar(mapa, n_letras, t_letras);
		cout << bolsa << endl;
		cout << "Introduce una palabra: " ;
		cin >> palabra;
		palabra_c=palabra.c_str();
		
		if(!(ok&=bolsa.palabr_ok(palabra_c)))
			cout << "Has usado mas letras de la cuenta" << endl;
		if(!(ok&=dic.contiene(palabra_c)))
			cout << "La palabra no esta en el diccionario" << endl;
		if(!ok)
			cout << "Palabra invalida, vuelva a introducir: ";
		while(!ok) {
			cin >>palabra;
			palabra_c=palabra.c_str();
			ok=true;
			if(!bolsa.palabr_ok(palabra_c)){
				cout << "Has usado mas letras de la cuenta" << endl;
				ok=false;
			}else if(!dic.contiene(palabra_c)){
				cout << "La palabra no esta en el diccionario" << endl;
				ok=false;
			}
			if(!ok)
				cout << "Vuelve a introducir: ";
		}
		
		puntos=conjunto.traducir(palabra_c, modalidad);
		cout << "Tu palabra vale: " << puntos << " puntos" << endl;
		
		sol=obtener_soluciones();
		cout << "Mis soluciones son: " << endl;
		for(it=sol.palabras.begin(); it!=sol.palabras.end(); ++it){
			cout << "\t- " << *it << endl;
		}
		cout << "\nY cada una vale " << sol.puntuacion << " puntos" << endl;
		
		if(sol.puntuacion > puntos)
			cout << "¿No sabes hacer nada mejor?\n" << endl;
		else if(sol.puntuacion == puntos)
			cout << "Al menos has conseguido empatar, enhorabuena...supongo" << endl;
		
		cout << "¿Volver a jugar? (s/n)" << endl;
		cin >> opcion_jugador;
		while( opcion_jugador!="s" && opcion_jugador!="n"){
			cout << "Introduzca opcion valida: 's' o 'n'" << endl;
			cin >> opcion_jugador;
		}
		if(opcion_jugador=="n")
			seguir_jugando=false;
	}
}

Juego::Soluciones Juego::obtener_soluciones(){
	Soluciones retorno;
	char *palabra;
	palabra=new char[n_letras+1];
	
	buscar_soluciones(palabra, dic, retorno, bolsa);
	
	return retorno;
}

void Juego::buscar_soluciones(char* comienzo_palabra, const Diccionario& dic, Soluciones& sol, Bolsa_Letras &bol)
{
	unsigned int punt, index;
	char c;
	char* auxc;
	Bolsa_Letras bolsa_aux;
	Bolsa_Letras::iterator bit;
	string palabra;
	
	//Hasta llegar a la mayor longitud de solución posible
	if(dic.profundidad<n_letras){
		//Recorremos las letras de la bolsa
		for (bit=bol.begin(); bit!=bol.end(); ++bit){
			c=(*bit).first;
			index=c-'a';
			
			bolsa_aux=bol;
			bolsa_aux.quitar(c);
			//Pasamos la letra de la bolsa a la palabra
			
			comienzo_palabra[dic.profundidad+1]=0;
			comienzo_palabra[dic.profundidad]=c;
			
			//Vemos si la palabra existe en el Diccionario o si por lo menos
			//vamos por buen camino, es decir, si existen posibles soluciones
			//que comiencen por la palabra actual
			palabra=comienzo_palabra;
			if((dic.nodo[index].dat_busqd & AQUI_PALABRA) == AQUI_PALABRA){
				punt=conjunto.traducir(comienzo_palabra, modalidad);
				if(punt > sol.puntuacion){
					//Si encontramos una solución que puntúa más que la mejor
					//encontrada, vaciamos las soluciones e insertamos esta nueva
					sol.palabras.clear();
					sol.palabras.insert(sol.palabras.end(), palabra);
					auxc=new char[n_letras+1];
					sprintf(auxc, "%s", comienzo_palabra);
					comienzo_palabra=auxc;
					sol.puntuacion=punt;
				}else if(punt == sol.puntuacion){
					//Si encontramos una solución que puntúa igual que las mejores
					//encontradas, la insertamos
					sol.palabras.insert(sol.palabras.end(), palabra);
				}
			}
			if((dic.nodo[index].dat_busqd & SEGUIR_BUSCANDO) == SEGUIR_BUSCANDO){
				//Si hay palabras por este camino de la jerarquía, añadimos las 
				//soluciones que se puedan encontrar a mayor profundidad
				buscar_soluciones(comienzo_palabra, *(dic.nodo[index].hijo), sol, bolsa_aux);
			}
		}
	}
}
istream& operator>>(istream& is, Diccionario & dic){
	string palabra_str;
	char palabra[1024];
	for (int i=0; i<N_LETRAS; ++i){
		recuento[i]=0;
	}
	while( is >> palabra_str ){
		sprintf(palabra, "%s", palabra_str.c_str());
	dic.registrar(palabra, recuento);
	}
	return is;
}

ostream& operator<<(ostream& os, Bolsa_Letras& bolsa){
	map<char, int>::const_iterator it;
	os << "TUS LETRAS SON:" << endl;
	for(it=bolsa.letras.begin(); it!=bolsa.letras.end(); ++it){
		for (int i=0; i<it->second; ++i){
			os << it->first << "  ";
		}
	}
	os << endl;
	
	return os;
}
