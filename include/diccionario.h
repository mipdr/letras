#ifndef DICCIONARIO
#define DICCIONARIO

#include <iostream>
#include <fstream>
#include <math.h>
#include <map>

#define N_LETRAS 26
#define AQUI_PALABRA 0xF0
#define SEGUIR_BUSCANDO 0x0F
#define LETRAS_TXT "data/letras.txt"

using namespace std;

/**
  *  @brief T.D.A. Diccionario
  * Este T.D.A está diseñado específicamente para ser utilizado en el contexto 
  * del juego de las letras.
  * Una instancia de esta clase servirá para almacenar la información esencial 
  * de un conjunto de palabras, expresadas como cadenas tipo c. 
  * La finalidad de la forma de almacenamiento de la información es la alta eficiencia de los métodos que más regularmente se utilizarán en una implementación normal del juego, así como la minimización del espacio de almacenamiento.
  *
  *
  * @author Miguel Pedregosa Pérez
  * @date Diciembre 2018
  */
class Diccionario{
	typedef char aqui_seguir;
	
	/**
	* @brief Estructura de puntero a diccionario hijo y datos de búsqueda
	*/
	struct Nodo{
		Diccionario* hijo;
		aqui_seguir dat_busqd;
	};
	
	private:
		/**
		* @brief Indica la profundidad del diccionario actual
		*/
		unsigned int profundidad;
		/**
		* @brief Array de hijos y datos de búsqueda
		*/
		Nodo* nodo;
	
	public:
		/**
		* @brief Constructor por defecto de la clase
		*/
		Diccionario(unsigned int p);
		/**
		* @brief Destructor de la clase
		*/
		~Diccionario();
		/**
		* @brief Operador de acceso a Diccionarios hijo
		* @param index Índice del vector nodo a acceder
		* @return Diccionario del índice indicado
		* @pre index ha de estar entre 0 y N_LETRAS-1
		*/
		Diccionario operator[](unsigned int index) const;
		/**
		* @brief Operador de igualación
		* @param dic Diccionario al que igualar
		* @return Diccionario que recibe la igualación
		*/
		Diccionario operator=(const Diccionario &dic);
		/**
		* @brief Método de registro de palabras
		* @param cadena Cadena tipo C a registrar
		* @param recuento Array de frecuencias absolutas de aparicion de caracteres,
		* la frecuencia de un caracter c está en la posicion (c-'a')-ésima del array
		* @return Informa del éxito de la operación
		* @pre cadena debe ser una cadena tipo C
		*/
		bool registrar(const char* cadena, int* recuento);
		/**
		* @brief Método de consulta, informa si una palabra está registrada o no
		* @param cadena Cadena tipo C a consultar
		* @return true si está registrada, false si no lo está
		* @pre cadena debe ser una cadena tipo C
		*/
		bool contiene(const char* cadena) const;
		/**
		* @brief Operador de entrada a partir de un flujo
		* @param is Flujo de entrada
		* @param dic Diccionario que recibe la entrada
		* @return Mismo flujo para encadenar entradas
		* @pre Los parámetros deben ser objetos inicializados
		*/
		friend istream& operator>>(istream& is, Diccionario & dic);
		friend class Juego;
};



#endif






