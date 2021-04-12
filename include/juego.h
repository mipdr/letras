#ifndef JUEGO
#define JUEGO

#include "diccionario.h"
#include "conjunto_letras.h"
#include "bolsa_letras.h"
#include <fstream>

static multimap<int, char> mapa;
/**
  *  @brief T.D.A. Juego
  * Este T.D.A está diseñado específicamente para ser utilizado en el contexto 
  * del juego de las letras.
  * Una instancia de esta clase servirá para administrar una partida del juego.
  * Almacena los elementos de la partida e implementa las interacciones entre
  * ellos
  * @author Miguel Pedregosa Pérez
  * @date Diciembre 2018
  */
class Juego{
	/**
	* @brief Estructura de datos para almacenar los datos referentes a un conjunto de mejores soluciones
	*/
	struct Soluciones{
		/**
		* @brief Puntuación de las mejores soluciones
		*/
		unsigned int puntuacion=0;
		/**
		* @brief Vector con las mejores soluciones
		*/
		vector<string> palabras;
	};
	
	private:
		/**
		* @brief Diccionario a utilizar
		*/
		Diccionario dic;
		/**
		* @brief Conjunto de Letras a utilizar
		*/
		Conjunto_Letras conjunto;
		/**
		* @brief Bolsa de Letras para proporcionar al jugador y a la maquina
		*/
		Bolsa_Letras bolsa;
		/**
		* @brief Cardinal de la Bolsa de Letras
		*/
		unsigned int n_letras;
		/**
		* @brief Número total de letras en el archivo de diccionario pasado como argumento
		*/
		unsigned int t_letras;
		/**
		* @brief Modalidad de juego
		*/
		char modalidad;
		
		/**
		* @brief Método auxiliar para la exploración de la jerarquía de diccionarios en la búsqueda de soluciones.
		* @param comienzo_palabra Se buscarán palabras con una letra más que comienzo_palabra que empiecen por comienzo_palabra.
		* @param dic Diccionario en el que hacer la búsqueda, su profundidad será el número de letras de comienzo_palabra.
		* @param sol Objeto tipo Soluciones donde se almacenan las mejores soluciones.
		* @param bol Objeto tipo Bolsa_Letras que contiene las letras que sobran tras utilizar las que están en comienzo_palabra.
		* @pre comienzo_palabra debe ser un vector con al menos tanta memoria reservada como ocupan n_letras+1 caracteres.
		*/
		void buscar_soluciones(char* comienzo_palabra, const Diccionario& dic, Soluciones& sol, Bolsa_Letras &bol);
	
	public:
		/**
		* @brief Constructor con parámetros
		* @param input Flujo de entrada del diccionario
		* @param nl Número de letras a generar para el jugador
		* @param mod Modalidad de juego
		* @pre input ha de estar propiamente inicializado
		*/
		Juego(ifstream& input, int nl, char mod);
		/**
		* @brief Inicializador del mapa de frecuencias de aparición de las 
		* letras en el diccionario
		*/
		void ini_mapa();
		/**
		* @brief Función para jugar la partida
		*/
		void jugar();
		/**
		* @brief Función para obtener las mejores soluciones
		* @return Struct Soluciones con las mejores soluciones y su puntuacion
		* @pre Los datos miembro dic y bolsa deben estar propiamente inicializados
		*/
		Soluciones obtener_soluciones();
};

#endif
