# include "AIPlayer.h"
# include "Parchis.h"

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 3;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move(){
    cout << "Realizo un movimiento automatico" << endl;

    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const{
    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente
    //como lo que se muestran al final de la función.

    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores,
    //respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // // El id de mi jugador actual.
    // int player = actual->getCurrentPlayerId();

    // // Vector que almacenará los dados que se pueden usar para el movimiento
    // vector<int> current_dices;
    // // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    // vector<tuple<color, int>> current_pieces;

    // // Se obtiene el vector de dados que se pueden usar para el movimiento
    // current_dices = actual->getAvailableNormalDices(player);
    // // Elijo un dado de forma aleatoria.
    // dice = current_dices[rand() % current_dices.size()];

    // // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    // current_pieces = actual->getAvailablePieces(player, dice);

    // // Si tengo fichas para el dado elegido muevo una al azar.
    // if (current_pieces.size() > 0)
    // {
    //     int random_id = rand() % current_pieces.size();
    //     id_piece = get<1>(current_pieces[random_id]); // get<i>(tuple<...>) me devuelve el i-ésimo
    //     c_piece = get<0>(current_pieces[random_id]);  // elemento de la tupla
    // }
    // else
    // {
    //     // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
    //     id_piece = SKIP_TURN;
    //     c_piece = actual->getCurrentColor(); // Le tengo que indicar mi color actual al pasar turno.
    // }

    /*
    // El siguiente código se proporciona como sugerencia para iniciar la implementación del agente.

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = menosinf, beta = masinf; // Cotas iniciales de la poda AlfaBeta
    // Llamada a la función para la poda (los parámetros son solo una sugerencia, se pueden modificar).
    valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    // ----------------------------------------------------------------- //

    // Si quiero poder manejar varias heurísticas, puedo usar la variable id del agente para usar una u otra.
    switch(id){
        case 0:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
            break;
        case 1:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, MiValoracion1);
            break;
        case 2:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, MiValoracion2);
            break;
    }
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    */
   double valor;
   double alpha = menosinf, beta = masinf;

   switch (id){
        case 0:
              thinkAleatorio(c_piece, id_piece, dice); 
              break;
        case 1:
              thinkAleatorioMasInteligente(c_piece, id_piece, dice);
              break;
        case 2:
              thinkFichaMasAdelantada(c_piece, id_piece, dice);
              break;
        case 3:
              thinkMejorOpcion(c_piece, id_piece, dice);
              break;
        case 4:
              valor = podaAlphaBeta(*actual, jugador, c_piece, id_piece, dice, 0, PROFUNDIDAD_ALFABETA, alpha, beta, ValoracionTest);
              break;
        case 5:
            valor = podaAlphaBeta(*actual, jugador, c_piece, id_piece, dice, 0, PROFUNDIDAD_ALFABETA, alpha, beta, heuristica2);
            break;

   }
   cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

}

double AIPlayer::ValoracionTest(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador+1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).get_box().type == goal)
                {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).get_box().type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}

void AIPlayer::thinkAleatorio(color & c_piece, int & id_piece, int & dice) const{
        // El id de mi jugador actual.
    int player = actual->getCurrentPlayerId();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<tuple<color, int>> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableNormalDices(player);
    // Elijo un dado de forma aleatoria.
    dice = current_dices[rand() % current_dices.size()];

    // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    current_pieces = actual->getAvailablePieces(player, dice);

    // Si tengo fichas para el dado elegido muevo una al azar.
    if (current_pieces.size() > 0)
    {
        int random_id = rand() % current_pieces.size();
        id_piece = get<1>(current_pieces[random_id]); // get<i>(tuple<...>) me devuelve el i-ésimo
        c_piece = get<0>(current_pieces[random_id]);  // elemento de la tupla
    }
    else
    {
        // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
        id_piece = SKIP_TURN;
        c_piece = actual->getCurrentColor(); // Le tengo que indicar mi color actual al pasar turno.
    }
}

void AIPlayer::thinkAleatorioMasInteligente(color & c_piece,  int & id_piece, int & dice) const{

    // El número de mi jugador actual.
    int player = actual->getCurrentPlayerId();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;

    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<tuple<color, int>> current_pieces;

    // Obtengo el vector de dados que puedo usar para el movimiento
    // - actual->getAvailableNormalDices(player) -> solo dados disponibles en ese turno.
    // Importante: "getAvailableNormalDices" me da los dados que puedo usar en el turno actual.
    // Por ejemplo, si me tengo que contar 10 o 20 solo me saldrán los dados 10 y 20.
    // Puedo saber qué más dados tengo, aunque no los pueda usar en este turno, con:
    // - actual->getNormalDices(player) -> todos los dados

    current_dices = actual->getAvailableNormalDices(player);

    // En vez de elegir un dado al azar, miro primero cuáles tienen fichas que se puedan mover.
    vector<int> current_dices_que_pueden_mover_ficha;

    for(int i = 0; i < current_dices.size(); i++){

        //Se obtiene el vector de fichas que se pueden mover para el dado elegido.
        current_pieces = actual->getAvailablePieces(player, current_dices[i]);

        // Si se pueden mover fichas para el dado actual, lo añado al vector de dados que pueden mover ficha.
        if(current_pieces.size() > 0){
            current_dices_que_pueden_mover_ficha.push_back(current_dices[i]);
        }
    }

    // Si no tengo ningún dado que pueda mover fichas, paso turno con un dado al azar (la macro SKIP_TURN
    // me permite no mover)
    if(current_dices_que_pueden_mover_ficha.size() == 0){
        dice = current_dices[rand() % current_dices.size()];

        id_piece = SKIP_TURN;
        c_piece = actual->getCurrentColor(); // Le tengo que indicar mi color actual al pasar turno.
    }
    else{   // En caso contrario, elijo un dado de forma aleatoria de entre los que pueden mover ficha.

        dice = current_dices_que_pueden_mover_ficha[rand() % current_dices_que_pueden_mover_ficha.size()];

        // Se obtiene el vector de fichas que se pueden mover para el dado elegido.
        current_pieces = actual->getAvailablePieces(player, dice);

        //Muevo una ficha al azar de entre las que se pueden mover.
        int random_id = rand() % current_pieces.size();
        id_piece = get<1>(current_pieces[random_id]);
        c_piece = get<0>(current_pieces[random_id]);
    }
}

void AIPlayer::thinkFichaMasAdelantada(color & c_piece,  int & id_piece, int & dice) const{
    
    // Elijo el dado haciendo lo mismo que el jugador anterior.
    thinkAleatorioMasInteligente(c_piece, id_piece, dice);

    // Tras llamar a esta función, ya tengo en dice el número de dado que quiero usar.
    // Ahora, en vez de mover una ficha al azar, voy a mover (o a aplicar
    // el dado especial a) la que esté más adelantada
    // equivalentemente, la más cercana a la meta).

    int player = actual->getCurrentPlayerId();
    vector<tuple<color, int>> current_pieces = actual->getAvailablePieces(player, dice);

    int id_ficha_mas_adelantada = -1;
    color col_ficha_mas_adelantada = none;
    int min_distancia_meta = 9999;
    for(int i = 0; i < current_pieces.size(); i++){
        //distanceToGoal(color, id) devuelve la distancia a la meta de la ficha [id] del color que le indique.
        color col = get<0>(current_pieces[i]);
        int id = get<1>(current_pieces[i]);
        int distancia_meta = actual->distanceToGoal(col, id);
        if(distancia_meta < min_distancia_meta){
            min_distancia_meta = distancia_meta;
            id_ficha_mas_adelantada = id;
            col_ficha_mas_adelantada = col;
        }
    }

    // Si no he encontrado ninguna ficha, paso turno.
    if(id_ficha_mas_adelantada == -1){
        id_piece = SKIP_TURN;
        c_piece = actual->getCurrentColor(); // Le tengo que indicar mi color actual al pasar turno.
    }

    // En caso contrario, moveré la ficha más adelantada.
    else{
        id_piece = id_ficha_mas_adelantada;
        c_piece = col_ficha_mas_adelantada;
    }
}

void AIPlayer::thinkMejorOpcion(color & c_piece,  int & id_piece, int & dice) const{

    // Vamos a mirar todos los posibles movimientos del jugador actual accediendo a los hijos del estado actual.

    // Cuando ya he recorrido todos los hijos, la función devuelve el estado actual. De esta forma puedo saber
    // cuando paro de iterar.

    // Para ello, vamos a iterar sobre los hijos con la función de Parchís getChildren().
    // Esta función devueleve un objeto de la clase PArchisBros, que es una estructura iterable
    // sobre la que se pueden recorrer todos los hijos del estado sobre el que se llama.

    ParchisBros hijos = actual->getChildren();

    bool me_quedo_con_esta_accion = false;

    // La clase ParchisBros viene con un iterator muy útil y sencillo de usar.
    // Al hacer begin() accedemeos al primer hijo de la rama.
    // y cada vez aue hagamos ++it saltaremos al siguiente hijo.
    // Comparado con el iterador end() podemos consutar cuando hemos termiando de visitar los hijos.

    // Voy a moverme a la casilla siempre con la que gana más energía, salvo que se encuentre con
    // algún movimiento más interesante, comoo comer fichas o llegar a la meta.

    int current_power = actual->getPowerBar(this->jugador).getPower();
    int max_power = -101; // Máxima ganancia de energía.

    for(ParchisBros::Iterator it = hijos.begin();

        it != hijos.end() and !me_quedo_con_esta_accion; ++it)
    {
        Parchis siguiente_hijo = *it;

        // Si en el movimiento elegido comiera ficha, llegara a la meta o ganara, me quedo con esta acción.
        // Termino el bucle en este caso.
        if(siguiente_hijo.isEatingMove() or
            siguiente_hijo.isGoalMove() or
            (siguiente_hijo.gameOver() and siguiente_hijo.getWinner() == this->jugador))
        {
            me_quedo_con_esta_accion = true;
            c_piece = it.getMovedColor();
            id_piece = it.getMovedPieceId();
            dice = it.getMovedDiceValue();
        }

        //En caso contario, me voy quedando con el que me de más energía.
        else{
            int new_power = siguiente_hijo.getPower(this->jugador);
            if(new_power - current_power > max_power){
                c_piece = it.getMovedColor();
                id_piece = it.getMovedPieceId();
                dice = it.getMovedDiceValue();
                max_power = new_power - current_power;
            }
        }

    }

    // Si he encontrado una accioón que me interesa, la guardo en las variables pasadas por referencia.

    // (Ya lo he hecho antes, cuando les he asigando los valores del iterador).
}

double AIPlayer::podaAlphaBeta(const Parchis &actual, int jugador, color &c_piece, int &id_piece, int &dice, int profundidad, 
        int profundidad_maxima, double alpha, double beta, double (*fun_heuristica)(const Parchis &, int)) const
{
    // CONDICION DE PARADA
    // Si la profundidad es la máxima o ha terminado la partida
    if(profundidad == profundidad_maxima or actual.gameOver()){

        // Devuelve la valoración del estado actual.
        return fun_heuristica(actual, jugador); 
    }

    ParchisBros hijos = actual.getChildren();

    for(ParchisBros::Iterator it = hijos.begin(); it != hijos.end(); ++it){

        if(jugador == actual.getCurrentPlayerId()){ // Es un nodo MAX

            double valor = podaAlphaBeta(*it, jugador, c_piece, id_piece, dice, 
            profundidad + 1, profundidad_maxima, alpha, beta, fun_heuristica);

            if(valor > alpha){  
                
                alpha = valor;

                if(profundidad == 0){ // Compruebo si estamos en el nodo raíz
                    c_piece = it.getMovedColor();
                    id_piece = it.getMovedPieceId();
                    dice = it.getMovedDiceValue();
                }
            }

            // Verifico si se cumple la condición de poda.
            if(alpha >= beta){
                break;
            }

        }
        
        else{ // Es un nodo MIN

            double valor = podaAlphaBeta(*it, jugador, c_piece, id_piece, dice, 
            profundidad + 1, profundidad_maxima, alpha, beta, fun_heuristica);

            if(valor < beta){
                
                beta = valor;
            }

            // Verifico si se cumple la condición de poda.
            if(alpha >= beta){
                break;
            }
        }
    }

    // Devuelvo el valor de alpha o beta, según si soy MAX o MIN.
    if(jugador == actual.getCurrentPlayerId()){
        return alpha;
    }
    else{
        return beta;
    }
}

double AIPlayer::heuristica2(const Parchis &estado, int jugador){

    int ganador = estado.getWinner();
    int oponente = (jugador+1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).get_box().type == goal)
                {
                    puntuacion_jugador += 5;
                }

                // HASTA AQUÍ ES EL MISMO CÓDIGO QUE LA HEURÍSTICA ValoracionTest
                // Ahora voy a introducir mejoras para que si el agente se pueda comer una ficha del equipo contrario, lo haga.
                // Con el fin de conseguir el dado +20 y llegar antes a la meta.

                for(int k = 0; k < op_colors.size(); k++){
                    color c_op = op_colors[k];
                    for(int l = 0; l < num_pieces; l++){
                        int dado_necesario = estado.distanceBoxtoBox(c, j, c_op, l);
                        for(int dado_disponible : estado.getAvailableNormalDices(jugador)){
                            if(dado_necesario == dado_disponible){
                                puntuacion_jugador += 100;
                            }
                        }
                    }
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).get_box().type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}


