#include <iostream>
#include <fstream>
#include "juego.h"

using namespace std;

//letras <diccionario> <nº letras> <modalidad>
int main(int argc, char** argv){
	
	if(argc!=4){
		cout << "Error de sintaxis.\nUsar: " << *argv << " <diccionario> <num_letras> <modalidad>\n - <diccionario> nombre de fichero de diccionario\n - <num_letras> numero de letras a obtener por partida, entre 5 y 20\n - <modalidad> 'P' = puntuacion , 'L' = longitud" << endl;
		return 1;
	}
	
	ifstream dic_input(argv[1]);
	
	if(!dic_input){
		cout << "Error abriendo \"" << *(argv+1) << "\".\nFichero erroneo." << endl;
		return 1;
	}
	
	int n_letras=strtol(argv[2], NULL, 10);
	if (n_letras<5 || n_letras>20){
		cout << "El parametro <num_letras> debe de estar entre 5 y 20" << endl;
		return 1;
	}
	
	char modalidad=*argv[3];
	if (modalidad != 'P' && modalidad != 'L'){
		cout << "El parametro <modalidad> debe de ser 'P' o 'L'" << endl;
		return 1;
	}
	
	cout << "NOTA: Asegurese de que esta utilizando un diccionario valido.\nPara generar diccionarios validos puede utilizar el programa ./bin/estandarizar_diccionario" << endl;
	
	Juego juego(dic_input, n_letras, modalidad);
	
	juego.jugar();

	return 0;
}
