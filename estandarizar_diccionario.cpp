#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

bool delimitador(char c){
	bool retorno;
	//retorno= (c<'a' || c>'z') && c!=130 && (c<160 || c>164);
	retorno= (c<'a' || c>'z') && c!='\303';
	return retorno;
}

void transformar(char & c){
	/*
	á - '\303' '\241'
	é - '\303' '\251'
	í - '\303' '\255'
	ó - '\303' '\263'
	ú - '\303' '\272'
	ü - '\303' '\274'
	ñ - '\303' '\261'
	*/
	//Se proporciona a la función únicamente el segundo char
	if (c=='\241') //á
		c='a';
	else if(c=='\251') //é
		c='e';
	else if(c=='\255') //í
		c='i';
	else if(c=='\263') //ó
		c='o';
	else if(c=='\272') //ú
		c='u';
	else if(c=='\261') //ñ
		c='n';
	else if(c=='\274') //ü
		c='u';
	else
		c='\n';
}

int main(int argc, char** argv){
	
	if(argc!= 2){
		cout << "Error de Sintaxis.\nUsar: " << *argv << " <arch_diccionario>" << endl;
		return 1;
	}
	
	ifstream entrada(argv[1]);
	ofstream salida("data/rae_std.txt");
	
	char linea[1024];
	char palabra[1024];
	char c;
	int i_lin=0;
	int i_pal=0;
	
	if(!entrada){
		cout << "Error en apertura" << endl;
		return 1;
	}
	
	
	entrada.getline(linea, 1024, '\n');
	while(entrada){
		i_lin=i_pal=0;
		c=linea[i_lin];
		while(!delimitador(c)){
			palabra[i_pal]=linea[i_lin];
			if(c == '\303'){
				++i_lin;
				c=linea[i_lin];
				transformar(c);
				palabra[i_pal]=c;
			}
			++i_lin;
			++i_pal;
			c=linea[i_lin];
		}
		palabra[i_pal]=0;
		//insertar palabra nueva
		salida.write(palabra, strlen(palabra));
		salida.write("\n", 1);
		entrada.getline(linea, 1024, '\n');
	}
	return 0;
}
