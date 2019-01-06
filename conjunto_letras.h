#ifndef CONJUNTO_LETRAS
#define CONJUNTO_LETRAS

#define N_LETRAS 26
#include <map>
using namespace std;
/**
  *  @brief T.D.A. Conjunto_Letras
  * Este T.D.A está diseñado específicamente para ser utilizado en el contexto 
  * del juego de las letras.
  * Una instancia de esta clase servirá para almacenar la información referente 
  * al conjunto de letras válidas, las puntuaciones a atribuir a las letras y 
  * como se reparten.
  * @author Miguel Pedregosa Pérez
  * @date Diciembre 2018
  */
class Conjunto_Letras{
	private:
		/**
		* @brief Array de traduccion, el valor de un caracter c está en la posición c-'a'
		*/
		unsigned int array_trad[N_LETRAS];
		/**
		* @brief Array de puntos, contiene las puntuaciones de las letras de mayor a menor
		*/
		unsigned int array_pts[N_LETRAS]={10,8,8,5,4,4,4,4,3,3,3,3,2,2,2,2,1,1,1,1,1,1,1,1,1,1};
	public:
		/**
		* @brief Constructor sin parámetros
		*/
		Conjunto_Letras();
		/**
		* @brief Método de inicialización
		* @param mapa_freq Multimap que almacena la frecuencia absoluta de 
		* aparicion de cada letra en el diccionario
		* @pre Las letras en mapa_freq deben de coincidir con las esperadas en 
		* el Conjunto_Letras
		*/
		void inicializar(const multimap<int, char> & mapa_freq);
		/**
		* @brief Método para obtener la puntuación de una palabra
		* @param palabra Cadena tipo C a traducir
		* @return Puntuación correspondiente a la palabra
		* @pre palabra debe ser una cadena tipo C
		*/
		unsigned int traducir(const char* palabra, const char modalidad);
};

#endif
