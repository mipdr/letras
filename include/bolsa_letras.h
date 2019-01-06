#ifndef BOLSA_LETRAS
#define BOLSA_LETRAS

#include <map>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm> //sort

using namespace std;
/**
  *  @brief T.D.A. Bolsa_Letras
  * Este T.D.A está diseñado específicamente para ser utilizado en el contexto 
  * del juego de las letras.
  * Una instancia de esta clase servirá para almacenar la información referente 
  * al conjunto de letras que se proporciona para obtener soluciones a partir de
  * él.
  * @author Miguel Pedregosa Pérez
  * @date Diciembre 2018
  */
class Bolsa_Letras{
	private:
		/**
		* @brief map caracter-frecuencia de las letras que se le dan al jugador
		*/
		map<char, int> letras;
		
		/**
		* @brief Método auxiliar para obtener un objeto coherente para el dato miembro letras
		* a partir del objeto mapa en juego.cpp
		* @param mm multimap frecuencia-caracter
		* @return map caracter-frecuencia
		*/
		map<char, int> convertir(const multimap<int, char>& mm);
		/**
		* @brief Función auxiliar generadora de números aleatorios
		* @param min Mínimo del rango
		* @param max Máximo del rango
		* @return Entero aleatorio entre min y max
		*/
		int aleatorio(int min, int max){
			static default_random_engine generador( (random_device())() );
			static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
			return distribucion_uniforme( generador );
		}
	public:
		/**
		* @brief Constructor sin parámetros
		*/
		Bolsa_Letras();
		/**
		* @brief Constructor con parámetros
		* @param mm Multimap con las frecuencias absolutas de las apariciones de
		* las letras
		* @param nl Número de letras a generar
		* @param tl Total de letras en el diccionario
		*/
		Bolsa_Letras(multimap<int, char>& mm, unsigned int nl, unsigned int tl);
		/**
		* @brief Método para renovar la bolsa
		* @param mm Multimap con las frecuencias absolutas de las apariciones de
		* las letras
		* @param nl Número de letras a generar
		* @param tl Total de letras en el diccionario
		*/
		void renovar(multimap<int, char>& mm, unsigned int nl, unsigned int tl);
		/**
		* @brief Método para añadir una letra a la bolsa
		* @param c Letra a añadir
		*/
		void anadir(char c);
		/**
		* @brief Método para eliminar una letra de la bolsa
		* @param c Caracter a eliminar
		*/
		void quitar(char c);
		/**
		* @brief Método de comprobación de la validez de una palabra
		* @param palabra Cadena tipo C a comprobar
		* @return true si palabra se puede construir a partir de la bolsa
		* @pre palabra debe ser una cadena tipo Cs
		*/
		bool palabr_ok(const char* palabra);
		/**
		* @brief Operador de igualacion
		* @param b Bolsa_Letras a copiar
		* @return *this
		*/
		Bolsa_Letras operator=(const Bolsa_Letras& b);
		/**
		* @brief Operador de impresión a un flujo
		* @param os Flujo de salida
		* @param bolsa Bolsa a imprimir
		* @return Mismo flujo para encadenar salidas
		*/
		friend ostream& operator<<(ostream& os, Bolsa_Letras& bolsa); 
		/**
		*@brief Clase iteradora para Bolsa_Letras
		*/
		class iterator{
			private:
				map<char, int>::iterator it;
				
			public:
				void set_it(map<char, int>::iterator i){
					it=i;
				}
				map<char, int>::iterator get_it(){
					return it;
				}
				iterator(){}
				pair<char, int> operator*(){
					return *it;
				}
				bool operator==(iterator otro){
					return otro.it==this->it;
				}
				bool operator!=(iterator otro){
					return otro.it!=this->it;
				}
				iterator operator++(){
					++it;
					return *this;
				}
				iterator operator--(){
					--it;
					return *this;
				}
		};
		/**
		* @brief Función begin de la clase
		* @return Iterator apuntando al principio del objeto
		*/
		iterator begin(){
			iterator retorno;
			retorno.set_it(letras.begin());
			return retorno;
		}
		/**
		* @brief Función end de la clase
		* @return Iterator apuntando al final del objeto
		*/
		iterator end(){
			iterator retorno;
			retorno.set_it(letras.end());
			return retorno;
		}
		/**
		* @brief Función erase
		* @param Iterator apuntando a lo que queremos borrar
		* @return Iterator apuntando al final del objeto
		*/
		iterator erase(iterator it);
};

#endif








