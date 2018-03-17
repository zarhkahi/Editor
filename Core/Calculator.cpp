#include <iostream>          
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int CARTASPORPALO = 13;  //Constantes
//EDDDD
const int MAXCARTAS = 53;
const int CENTINELA = 52;


//56856
typedef enum { picas, treboles, diamantes, corazones } tPalo;  //Tipo enumerado para el palo.
typedef enum { A, dos, tres, cuatro, cinco, seis, siete, ocho, nueve, diez, J, Q, K } tNumero; //Tipo enumerado para nuemro carta.
typedef int tCarta;
typedef tCarta tMazo[MAXCARTAS];

int menu();                                //Declaración de todas las funciones usadas en el programa.
void crearMazoVacio(tMazo mazo);
int cuantasEnMazo(const tMazo mazo);
tPalo darPalo(tCarta carta);
tNumero darNumero(tCarta carta);
void escribirCarta(tCarta carta);
void escribirMazo(const tMazo mazo);
bool cargarMazo(tMazo mazo);
void barajarMazo(tMazo mazo);
bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo);
bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino);
void cortarMazo(tMazo mazo, int cuantas);
void guardarMazo(const tMazo mazo);
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo);
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);
void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo);
void trucoTresMontones();
void separartresMontones(tMazo mazo);
void trucoPosada();
//Funciones creadas para cada opción del menú.
bool opcionCargarMazo(tMazo mazo);    //La función cargar es bool para poder saver si el mazo esta cargado o no.
void opcionBarajarMazo(tMazo mazo, bool cargado);
void opcionAñadirMazo(tMazo mazo, bool cargado);
void opcionCortarMazo(tMazo mazo, bool cargado);
void opcionNegrasRojas(tMazo mazo);
void opcionBajaAltas(tMazo mazo);
void opcionRepartir3Montones(tMazo mazo);


int main(){                       //MAIN

	locale::global(locale("spanish")); //Con esto se muestran todos los acentos y 'ñ' por consola.
	srand(time(NULL));  //Semilla para hallar números aleatorios.
	int opcion;
	tMazo mazoPrincipal;
	bool mazoCargado = false; //con esta variable sabremos si hay un mazo cargado o no.

	crearMazoVacio(mazoPrincipal);  //Creamos un mazo vacío con el que se trabaja a lo largo de toda la ejecución.
	opcion = menu();


	while (opcion != 0){
		switch (opcion){     //switch con cada opción del menú.
		case 1:{
				   mazoCargado = opcionCargarMazo(mazoPrincipal);

		}
			break;
		case 2:{
				   opcionBarajarMazo(mazoPrincipal, mazoCargado);

		}
			break;
		case 3:{
				   opcionAñadirMazo(mazoPrincipal, mazoCargado);

		}
			break;
		case 4:{
				   opcionCortarMazo(mazoPrincipal, mazoCargado);

		}
			break;
		case 5:{
				   guardarMazo(mazoPrincipal);
		}
			break;
		case 6:{
				   opcionNegrasRojas(mazoPrincipal);

		}
			break;
		case 7:{
				   opcionBajaAltas(mazoPrincipal);

		}
			break;
		case 8:{
				   opcionRepartir3Montones(mazoPrincipal);

		}
			break;
		case 9:{
				   trucoTresMontones();
		}
			break;
		case 10:{
					trucoPosada();
		}
			break;

		}
		opcion = menu();

	}
	cout << "¡Hasta pronto!" << endl;
	system("pause");
	return 0;
}

int menu(){						//Función menú.											
	int opcion = -1;
	while (opcion < 0 || opcion > 10){
		cout << endl;
		cout << "1 - Cargar un mazo de cartas de fichero" << endl;
		cout << "2 - Barajar mazo de cartas" << endl;
		cout << "3 - Añadir mazo" << endl;
		cout << "4 - Cortar mazo" << endl;
		cout << "5 - Guardar mazo de cartas en fichero" << endl;
		cout << "6 - Separar en negras y rojas" << endl;
		cout << "7 - Separar en bajas y altas" << endl;
		cout << "8 - Repartir un mazo de manera alterna en 3 montones" << endl;
		cout << "9 - Truco de los tres montones" << endl;
		cout << "10 - Truco de la posada" << endl;
		cout << "0 - Salir" << endl;
		cout << endl;
		cout << "Selecciona una opcion: ";
		cin >> opcion;
		if (opcion < 0 || opcion > 10){
			cout << "Opcion incorrecta." << endl << "Eliga una de estas 10:" << endl;
		}
	}

	return opcion;

}

void crearMazoVacio(tMazo mazo){
	mazo[0] = CENTINELA;
}

int cuantasEnMazo(const tMazo mazo){
	int cuantasCartas = 0;
	while (mazo[cuantasCartas] != CENTINELA){  //Va sumando 1 a cuantasCartas hasta llegar al centinela (Se consigue cuantas cartas contiene el mazo)
		cuantasCartas++;
	}
	return cuantasCartas;
}

tPalo darPalo(tCarta carta){      //Devuelve el palo correspondiente a la carta.
	return tPalo(carta / CARTASPORPALO);
}

tNumero darNumero(tCarta carta){    //Devuelve el número de la carta.
	return tNumero(carta % CARTASPORPALO);
}

void escribirCarta(tCarta carta){
	tNumero numero;
	tPalo palo;
	numero = darNumero(carta); //Se obtiene el palo y el número de funciones anteriores.
	palo = darPalo(carta);
	switch (numero){ //switch que asigna a cada carta su nombre.
	case A:
		cout << "As";
		break;
	case dos:
		cout << "Dos";
		break;
	case tres:
		cout << "Tres";
		break;
	case cuatro:
		cout << "Cuatro";
		break;
	case cinco:
		cout << "Cinco";
		break;
	case seis:
		cout << "Seis";
		break;
	case siete:
		cout << "Siete";
		break;
	case ocho:
		cout << "Ocho";
		break;
	case nueve:
		cout << "Nueve";
		break;
	case diez:
		cout << "Diez";
		break;
	case J:
		cout << "J";
		break;
	case Q:
		cout << "Q";
		break;
	case K:
		cout << "K";
		break;
		cout << endl;
	}
	cout << " de ";
	switch (palo){ //switch que asigna a cada carta su palo
	case picas:
		cout << char(6) << endl;  //♠ picas
		break;
	case treboles:
		cout << char(5) << endl;  //♣ treboles
		break;
	case diamantes:
		cout << char(4) << endl;  //♦ diamantes
		break;
	case corazones:
		cout << char(3) << endl;  //♥ corazones
		break;
	}
}

void escribirMazo(const tMazo mazo){    //Muestra por pantalla el mazo de carta, utiliza la función anterior.
	for (int i = 0; mazo[i] != CENTINELA; i++){
		cout << "Carta " << i + 1 << ": ";
		escribirCarta(mazo[i]);
	}
}

bool cargarMazo(tMazo mazo){   //Carga un mazo contenido en un .txt
	bool a = false; //bool que servira para saber si el archivo esta abierto correctamente.
	string mazoElegido;
	int num = 0, i = 0;
	char palo;
	cout << "Elige el mazo a cargar (acabado en .txt): ";
	cin >> mazoElegido;
	ifstream archivo; //Para leer el archivo.
	tCarta carta = 0;
	archivo.open(mazoElegido); //Abre el archivo con el nombre que hemos escrito anteriormente acabado en .txt
	if (!archivo.is_open())
		a = false;
	else{
		archivo >> palo;    //Lee el palo y el numero de la carta del archivo.
		archivo >> num;
		while (palo != 'x' && i < CENTINELA){ //while que va detectando el palo y el numero de la carta hasta que encuentra el centinela.
			if (palo == 'p'){
				carta = (num - 1);
			}
			if (palo == 't'){
				carta = (CARTASPORPALO + num - 1);
			}
			if (palo == 'd'){
				carta = (2 * CARTASPORPALO + num - 1);
			}
			if (palo == 'c'){
				carta = (3 * CARTASPORPALO + num - 1);
			}
			mazo[i] = carta; //Con el sumatorio se va consiguendo pasar de posición en el mazo donde guarda la carta
			i++;
			archivo >> palo;
			archivo >> num;
		}
		mazo[i] = CENTINELA;
		a = true;
	}
	archivo.close();
	return a;
}

void barajarMazo(tMazo mazo){
	int numCartas = cuantasEnMazo(mazo);
	tCarta aux, cartaUno, cartaDos;
	for (int i = 0; i < 3 * numCartas; i++){ //Se realiza tres veces.
		cartaUno = rand() % (numCartas); //Va creando posiciones aleatorias
		cartaDos = rand() % (numCartas);
		aux = mazo[cartaUno];  //Se copia la cartas del mazo1 en uno auxiliar, en esa posición se copia la carta del mazo dos y en la posición copiada del mazo dos se pone la carta que se había guardado en mazo auxiliar.
		mazo[cartaUno] = mazo[cartaDos];
		mazo[cartaDos] = aux;
	}
	mazo[CENTINELA] = CENTINELA;
}

bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo){ //Une un mazo con el cargado en la opción 1.
	bool posible = false;
	int numCartas1, numCartas2, suma, i = 0;
	numCartas1 = cuantasEnMazo(mazoOriginal); //cuenta las cartas del mazo original y el nuevo
	numCartas2 = cuantasEnMazo(nuevoMazo);
	suma = numCartas1 + numCartas2;
	if (suma > CENTINELA){ //Si el total de cartas entre ambos mazos no excede 52 (el limite de una baraja) entonces se pueden unir.
		posible = false;
	}
	else{
		posible = true;
		for (numCartas1; numCartas1 < suma; numCartas1++){ //Coge la posición final del mazo original y le va añadiendo a partir de ahí las cartas del mazo nuevo, para cuendo se llega al límite de capazidad entre ambos mazos unidos.
			mazoOriginal[numCartas1] = nuevoMazo[i];
			i++; //va pasando de posición en el mazo nuevo
		}
		mazoOriginal[numCartas1] = CENTINELA; //Pone el centinela en la última posición
	}
	return posible;
}

bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino){    //Se parte el mazo en dos.
	bool posible = false;
	int i = 0, j = 0; //variables creadas para moverse por las posiciones de los mazos.
	int cuantas = cuantasEnMazo(mazoOrigen);
	if (cuantas < cuantasCoger){ //Si el lugar elegido es mayor que las cartas que hay, no se puede cortar, en caso contrario se realiza el corte.
		posible = false;
	}
	else{
		posible = true;
		for (i; i < cuantasCoger; i++) //Va copiando en el mazo destino las cartas del mazo hasta llegar hasta la que usuario había pedido.
			mazoDestino[i] = mazoOrigen[i];
		for (cuantasCoger; cuantasCoger < cuantas; cuantasCoger++){ //Pasamos las cartas del mazo que quedaban al primeras posiciones del mazo
			mazoOrigen[j] = mazoOrigen[cuantasCoger];
			j++;
		}
		mazoOrigen[j] = CENTINELA;
		mazoDestino[i] = CENTINELA;
	}
	return posible;
}

void cortarMazo(tMazo mazo, int cuantas) {     //Se pedirá el lugar pordonde cortar el mazo (en su correspondiente función del menú) y se corta.
	tMazo mazoAuxiliar;
	bool partir = false;

	partir = partirMazo(mazo, cuantas, mazoAuxiliar);
	if (partir == true){
		unirMazos(mazo, mazoAuxiliar); //Una vez comprobado que se han podido partir se unen los mazos.
	}
}

void guardarMazo(const tMazo mazo){ //Se guarda el mazo cargado.
	int cuantas;
	string nombre;
	tNumero numero;
	tPalo palo;
	cout << "Introduce el nombre del archivo (acabado en .txt):";
	cin >> nombre;
	cout << endl;
	cuantas = cuantasEnMazo(mazo); //Contamos las cartas para poder recorrer solo las posiciones del mazo con cartas.
	ofstream archivo; //Para escribir el archivo.
	archivo.open(nombre);

	if (archivo.is_open()){
		for (int i = 0; i < cuantas; i++){  //Se recorren todas la posiciones del mazo ocupadas.
			numero = darNumero(mazo[i]);
			palo = darPalo(mazo[i]);
			switch (palo){  //switch para escribir el palo en el archivo.
			case picas:
				archivo << 'p';
				break;
			case treboles:
				archivo << 't';
				break;
			case diamantes:
				archivo << 'd';
				break;
			case corazones:
				archivo << 'c';
				break;
			}
			archivo << ' ';
			switch (numero){  //switch para escribir el numero de la carta en el archivo.
			case A:
				archivo << '1';
				break;
			case dos:
				archivo << '2';
				break;
			case tres:
				archivo << '3';
				break;
			case cuatro:
				archivo << '4';
				break;
			case cinco:
				archivo << '5';
				break;
			case seis:
				archivo << '6';
				break;
			case siete:
				archivo << '7';
				break;
			case ocho:
				archivo << '8';
				break;
			case nueve:
				archivo << '9';
				break;
			case diez:
				archivo << '1' << '0';
				break;
			case J:
				archivo << '1' << '1';
				break;
			case Q:
				archivo << '1' << '2';
				break;
			case K:
				archivo << '1' << '3';
				break;
			}
			archivo << endl;
		}
		archivo << 'x'; //Se pone el centinela al final y se cierra el archivo.
		archivo.close();
		cout << "El mazo ha sido guardado con éxito!" << endl;
	}
	else {
		cout << "ERROR al guardar el archivo" << endl;
	}
}

void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo){
	tPalo palo;
	int i = 0, k = 0, j = 0; //Tres variables que nos van a permitir movernos a traves de los mazos.
	palo = darPalo(mazo[i]); //Se obtiene el palo por función correspondiente.

	while (mazo[i] != CENTINELA){
		if (palo == picas || palo == treboles){ //mientras el palo sea ♠ o ♣ se guarda en el mazo negro, de lo contrario en el mazo rojo.
			mazoNegro[k] = mazo[i];
			k++;
		}
		else{
			mazoRojo[j] = mazo[i];
			j++;
		}
		i++;
	}
	mazoNegro[k] = CENTINELA; //Centinela en la ultima posición sin usar de los mazos
	mazoRojo[j] = CENTINELA;
}

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas){
	tNumero numero;
	int i = 0, k = 0, j = 0; //Tres variables que nos van a permitir movernos a traves de los mazos.
	numero = darNumero(mazo[i]); //Se obtiene el número por la función correspondiente.

	while (mazo[i] != CENTINELA){
		if (numero <= 7){    //mientras el palo sea menor que 7 se guarda en el mazo bajas, de lo contrario en el mazo negro.
			mazoBajas[k] = mazo[i];
			k++;
		}
		else{
			mazoAltas[j] = mazo[i];
			j++;
		}
		i++;
	}
	mazoBajas[k] = CENTINELA; //Centinela en la ultima posición sin usar de los mazos
	mazoAltas[j] = CENTINELA;
}

void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo){
	int i = queMazoPido - 1, j = 0, numCartas = cuantasEnMazo(mazo);
	if (queMazoPido > enCuantosMazos || enCuantosMazos > numCartas){
		cout << "ERROR. El mazo contiene un número de cartas no válido." << endl;
	}
	else{
		while (i < numCartas){                   //Consiste en ir repartiendo una carta a cada montón (mazo) de los elegido hasta llenarlos y coger uno de ellos.
			mazoNuevo[j] = mazo[i];
			j++;
			i = i + enCuantosMazos;
		}
		mazoNuevo[j] = CENTINELA;
	}
}

void trucoTresMontones(){
	tMazo mazo;
	bool a = cargarMazo(mazo);
	if (!a){
		cout << "No se ha podido cargar el mazo";  //Se carga un mazo, si no existe da ERROR, de lo contrario se ejecuta el truco.
	}
	else{
		cout << "La baraja ha sido dividida en 3 montones, elige una carta." << endl;

		barajarMazo(mazo);   //Se llama a las función barajar y a separar en tres montones que se ejecuta tres veces.
		separartresMontones(mazo);
		separartresMontones(mazo);
		separartresMontones(mazo);
		cout << "La carta que habías pensado es: ";
		escribirCarta(mazo[10]); //Se escribe la carta 11 que corresponde a la posición 10 del mazo. Es la carta elegida.
	}
}

void separartresMontones(tMazo mazo){  //Función que realiza el mecanismo del truco Tres Montones. 
	tMazo mazo1, mazo2, mazo3;
	int mazoElegido;
	repartirIntercalando(mazo, 3, 1, mazo1);   //Reparte el mazo en tres montones y se muestran al espectador.
	cout << "Mazo 1: " << endl;
	escribirMazo(mazo1);
	repartirIntercalando(mazo, 3, 2, mazo2);
	cout << "Mazo 2: " << endl;
	escribirMazo(mazo2);
	repartirIntercalando(mazo, 3, 3, mazo3);
	cout << "Mazo 3: " << endl;
	escribirMazo(mazo3);
	cout << "Indica en qué mazo está la carta en la que has pensado: ";
	cin >> mazoElegido;
	cout << endl;
	crearMazoVacio(mazo);  //Se cre un mazo vacío que será donde se unan mazo1, mazo2, mazo3 
	if (mazoElegido == 1){  //En función de en que mazo halla elegido siempre se pondra este en el medio de los tres al unirlos.
		unirMazos(mazo, mazo2);
		unirMazos(mazo, mazo1);
		unirMazos(mazo, mazo3);
	}
	else if (mazoElegido == 2){
		unirMazos(mazo, mazo1);
		unirMazos(mazo, mazo2);
		unirMazos(mazo, mazo3);
	}

	else{       //Si elige el 3
		unirMazos(mazo, mazo1);
		unirMazos(mazo, mazo3);
		unirMazos(mazo, mazo2);
	}
}

void trucoPosada(){
	tMazo mazo, mazo1, mazo2, mazo3, mazo4;
	int cortar;
	if (cargarMazo(mazo) == true){
		repartirIntercalando(mazo, 4, 1, mazo1);
		cout << "Mazo 1:" << endl;
		escribirMazo(mazo1);
		repartirIntercalando(mazo, 4, 2, mazo2);
		cout << "Mazo 2:" << endl;
		escribirMazo(mazo2);
		repartirIntercalando(mazo, 4, 3, mazo3);
		cout << "Mazo 3:" << endl;
		escribirMazo(mazo3);
		repartirIntercalando(mazo, 4, 4, mazo4);
		cout << "Mazo 4:" << endl;
		escribirMazo(mazo4);
		crearMazoVacio(mazo);
		unirMazos(mazo, mazo1);
		unirMazos(mazo, mazo2);
		unirMazos(mazo, mazo3);
		unirMazos(mazo, mazo4);
		cout << "Indica por donde quieres cortar el mazo:";
		cin >> cortar;
		cout << endl;
		cortarMazo(mazo, cortar);
		repartirIntercalando(mazo, 4, 1, mazo1);
		cout << "Mazo 1:" << endl;
		escribirMazo(mazo1);
		repartirIntercalando(mazo, 4, 2, mazo2);
		cout << "Mazo 2:" << endl;
		escribirMazo(mazo2);
		repartirIntercalando(mazo, 4, 3, mazo3);
		cout << "Mazo 3:" << endl;
		escribirMazo(mazo3);
		repartirIntercalando(mazo, 4, 4, mazo4);
		cout << "Mazo 4:" << endl;
		escribirMazo(mazo4);
	}
	else{
		cout << "ERROR. El mazo no ha sido cargado" << endl;
	}
}

//Funciones que corresponden a cada opción del menú:

bool opcionCargarMazo(tMazo mazo){  //Opción 1.
	bool cargado = false;

	if (cargarMazo(mazo) == true){  //Llama a cargar mazo, si el mazo no existe se muestra ERROR.
		escribirMazo(mazo);
		cargado = true;
	}
	else {
		cout << "ERROR. El mazo no ha podido ser cargado." << endl;
		cargado = false;
	}

	return cargado; //Devuelve si mazo está cargado o no, sera utilizado en otras funciones.
}

void opcionBarajarMazo(tMazo mazo, bool cargado){  //Opción 2.

	if (!cargado){
		cout << "ERROR. No hay un archivo cargado!" << endl; //Si no hay un mazo cargado muestra ERROR.
	}
	else{
		escribirMazo(mazo); //Muestra el mazo cargado, lo baraja y lo muestra barajado
		barajarMazo(mazo);
		cout << endl;
		cout << "Mazo barajado" << endl;
		escribirMazo(mazo);
		cout << endl;
	}

}

void opcionAñadirMazo(tMazo mazo, bool cargado){ //Opción 3.

	tMazo mazoSecundario;
	cout << "Recuerde cargar un mazo en la opción 1 antes de realizar esta opción." << endl;
	if (!cargado){
		cout << "ERROR. No hay un archivo cargado!" << endl; //Si no hay un mazo cargado muestra ERROR.
	}
	else{
		if (cargarMazo(mazoSecundario) == true){  //Se carga un nuevo mazo, si no existe muestra ERROR.
			cout << "Mazo del programa:" << endl; //Muestra ambos mazos a unir.
			escribirMazo(mazo);
			cout << endl;
			cout << "Mazo a añadir:" << endl;
			escribirMazo(mazoSecundario);
			cout << endl;
			if (unirMazos(mazo, mazoSecundario) == true){ //Si se pueden unir muestra los mazos unidos si no se muestra ERROR.
				cout << "Unión de ambos mazos: " << endl;
				escribirMazo(mazo);
			}
			else{
				cout << "No se han podido unir los mazos, el numero de cartas excede el permitido." << endl;
			}
		}
		else
			cout << "No existe un mazo con ese nombre (recuerde poner .txt al final)" << endl;
	}

}

void opcionCortarMazo(tMazo mazo, bool cargado){ //Opción 4. 
	int carta;

	if (!cargado) { //Se carga un nuevo mazo, si no existe muestra ERROR.
		cout << "ERROR. No hay un archivo cargado!" << endl;
	}
	else{ //se muestra el mazo, se pide por donde cortarlo y se muestra ya cortado.
		cout << endl;
		escribirMazo(mazo);
		cout << endl;
		cout << "Escribe la carta por la que quieres cortar: ";
		cin >> carta;
		cout << endl;
		cortarMazo(mazo, carta);
		escribirMazo(mazo);
		cout << endl;
	}
}

void opcionNegrasRojas(tMazo mazo){ //Opción 6. 

	tMazo mazoNegras, mazoRojas;
	repartirNegroRojo(mazo, mazoNegras, mazoRojas); //Llama a la función correspondiente y muestra ambos mazos (Negras y Rojas).
	cout << "Cartas negras (Treboles, Picas): " << endl;
	escribirMazo(mazoNegras);
	cout << endl;
	cout << "Cartas rojas (Rombos, Corazones): " << endl;
	escribirMazo(mazoRojas);
	cout << endl;

}

void opcionBajaAltas(tMazo mazo){ //Opción 7.

	tMazo mazoBajas, mazoAltas;
	repartirBajaAlta(mazo, mazoBajas, mazoAltas); //Llama a la función correspondiente y muestra ambos mazos (Bajas y Altas).
	cout << "Cartas altas (A-7): " << endl;
	escribirMazo(mazoAltas);
	cout << endl;
	cout << "Cartas bajas (8-K): " << endl;
	escribirMazo(mazoBajas);
	cout << endl;

}

void opcionRepartir3Montones(tMazo mazo){ //Opción 8.

	int cortar, mazoPedido;
	tMazo mazoNuevo;

	cout << "Mete el numero de mazos que quieres cortar: ";
	cin >> cortar;
	cout << "Elige el mazo cortado: ";
	cin >> mazoPedido;
	repartirIntercalando(mazo, cortar, mazoPedido, mazoNuevo); //Llama a la función correspondiente y se muestra el mazo elegido de los creados.
	escribirMazo(mazoNuevo);
	cout << endl;

}






