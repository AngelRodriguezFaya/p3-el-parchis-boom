/**
 * @file AIPlayer.h
 * @brief Clase AIPlayer que representa un jugador inteligente.
 *
 * Clase que representa un jugador inteligente que puede jugar al parchís.
 * 
 * @see Player.h
 * @see Parchis.h
 * @see Attributes.h
 * 
 * @version 1.0
 * @date 01/04/2021
 * 
 * Modificado por Ángel Rodríguez Faya
 * 
 * Práctica 4: Busqueda con adversario en juegos. El Parchís Boom!
 * Inteligencia Artifical
 * Curso 2023/2024
 * Universidad de Granada - Grado en Ingeniería Informática
 */

#ifndef __AI_PLAYER_H__
#define __AI_PLAYER_H__

# include "Attributes.h"
# include "Player.h"

class AIPlayer: public Player{
    protected:
        //Id identificativo del jugador
        const int id;
    public:
        /**
         * @brief Constructor de un objeto AIPlayer
         * 
         * @param name Nombre del jugador
         */
        inline AIPlayer(const string & name):Player(name), id(1){};
        
        /**
         * @brief Constructor de un objeto AIPlayer 
         * 
         * @param name Nombre  del jugador
         * @param id Id del jugador
         */
        inline AIPlayer(const string & name, const int id):Player(name), id(id){};

        /**
         * @brief Función que percibe el el parchís y al jugador actual.
         * Asigna el tablero en actual y el id del jugador.
         * 
         * @param p Instancia Parchis que se quiere percibir
         */
        inline virtual void perceive(Parchis &p){Player::perceive(p);}

        /**
         * @brief Función abstracta que define el movimiento devuelto por el jugador.
         * Llama a la función movePiece con el valor asignado a los parámetros pasados 
         * por referencia.
         * 
         * @return true
         * @return false 
         */
        virtual bool move();
        
        /**
         * @brief Función que se encarga de decidir el mejor movimiento posible a 
         * partir del estado actual del tablero. Asigna a las variables pasadas por
         * referencia el valor de color de ficha, id de ficha y dado del mejor movimiento.
         * 
         * @param c_piece Color de la ficha
         * @param id_piece Id de la ficha
         * @param dice Número de dado
         */
        virtual void think(color & c_piece,  int & id_piece, int & dice) const;

        /**
         * @brief Método que determina si el player es inteligente (decide el mejor movimiento)
         * o no. True para AIPlayer.
         * 
         * @return true 
         * @return false 
         */
        inline virtual bool canThink() const{return true;}

        /**
         * @brief Heurística de prueba para validar el algoritmo de búsqueda.
         * 
         * @param estado Instancia de Parchis con el estado actual de la partida.
         * @param jugador Id del jugador actual (0 o 1)
         * @return double 
         */
        static double ValoracionTest(const Parchis &estado, int jugador);

        // Métodos del tutorial ------------------------------------------------------------------
        
        void thinkAleatorio(color & c_piece,  int & id_piece, int & dice) const;

        void thinkAleatorioMasInteligente(color & c_piece,  int & id_piece, int & dice) const;

        void thinkFichaMasAdelantada(color & c_piece,  int & id_piece, int & dice) const;

        void thinkMejorOpcion(color & c_piece, int & id_piece, int & dice) const;

        // ----------------------------------------------------------------------------------------


        /**
         * @brief Método implementa el algoritmo de la poda alpha-beta.
         * 
         * Se encarga de decidir el mejor movimiento posible  utilizando la heurística 
         * pasada como parámetro.
         * 
         * @param actual Estado actual del tablero
         * @param jugador Id del jugador actual
         * @param c_piece Color de la ficha que realizará el movimiento
         * @param id_piece Id de la ficha que realizará el movimiento
         * @param dice Dado que se ha lanzado/escogido.
         * @param profundidad Profundidad actual de la búsqueda
         * @param profundidad_maxima Profundidad máxima de la búsqueda (para este algoritmo el máximo es 6)
         * @param alpha Valor de alpha
         * @param beta Valor de beta
         * @param fun_heuristica Heurística que se utilizará para evaluar los estados del tablero.
         * 
         * @return double Valor MiniMax. Además se tendrá que tener en cuenta los valores de los parámetros
         * c_piece, id_piece y dice, donde se indicará la el color, la ficha y el dado que realizarán el movimiento.
         */
        double podaAlphaBeta(const Parchis &actual, int jugador, color &c_piece, int &id_piece, int &dice, int profundidad, 
                    int profundidad_maxima, double alpha, double beta, double (*fun_heuristica)(const Parchis &, int)) const;

        
        // ********************************************************************************//
        // ************************** MIS HEURÍSTICAS *************************************//
        // ********************************************************************************//

        /**
         * @brief Heurística 1.
         * 
         * @param estado Estado actual del tablero
         * @param jugador Id del jugador actual
         * 
         * @return double Puntuación de la heurística. 
         */
        static double miHeuristica1(const Parchis &estado, int jugador);

        /**
         * @brief Heurística 2.
         * 
         * @param estado Estado actual del tablero
         * @param jugador Id del jugador actual
         * 
         * @return double Puntuación de la heurística. 
         */
        static double miHeuristica2(const Parchis &estado, int jugador);

        /**
         * @brief Heurística 3. Necesita de una sub-heurística para su cálculo.
         * 
         * @see miSub_Heuristica3_1
         * 
         * @param estado Estado actual del tablero
         * @param jugador Id del jugador actual
         * 
         * @return double Puntuación de la heurística. 
         */
        static double miHeuristica3(const Parchis &estado, int jugador);
        
        /**
         * @brief Sub-heurística 1 de la heurística 3.
         * 
         * @param estado Estado actual del tablero
         * @param jugador Id del jugador actual
         * 
         * @return double Puntuación de la sub-heurística. 
         */
        static double miSub_Heuristica3_1(const Parchis &estado, int jugador);

        /**
         * @brief Sub-heurística 2 de la heurística 3.
         * 
         * No se utiliza en la heurística 3.
         * Utilizar la sub-heurística 3_1.
         * @param estado Estado actual del tablero
         * @param jugador Id del jugador actual
         * 
         * @return double Puntuación de la sub-heurística. 
         */
        static double miSub_Heuristica3_2(const Parchis &estado, int jugador);


        // ***************** Funciones de utilidad para las heurísticas
        
        /**
         * @brief Función que devuelve la puntuación de un dado especial.
         * 
         * @param valorPowerBar Valor de la barra de energía
         * 
         * @return int Puntuación
         */
        static int puntuacionPorDadoEspecial(const int valorPowerBar);

};
#endif