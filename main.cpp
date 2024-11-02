#include <bits/stdc++.h>

#include <stack>

#include <vector>

#include <cstdlib>

#define cnl "\n"
#define nl cout << "\n"
using namespace std;

/* ---| Lista de clases |--- 
- Jugador
- Propiedad{
    - Lugar
    - Ferrocarril
    - Servicios
}
- Tarjetas (Cartas azules de cofre y naranjas de suerte)
- Casillas{
    Metodos para:
    - Ir a la carcel
    - Go
    - Impuestos
    - Free parking (se acumulan los impuestos y quien caiga ahi se lo lleva)
    - Obtener tarjetas
}

*/

void limpiarPantalla(){
    system("cls||clear");
}

class PropiedadGeneral {
    /*Variables generales*/
    string nombre;
    int idPropiedad;
    int precio;
    int idDueno = 0; //Guarda el índice del dueño
    bool hipotecada = false; //False no hipotecada, True hipotecada
    int precioHipoteca;
    int color; //0=No existe, 1=Café... 8=Azul Rey... 9=Trenes, 10=Servicios

    /*Variables de propiedades normales*/
    int costoCasa;
    int noCasas=0;
    int rentas[7];
    int indiceColor; //Guarda el indice donde inician los colores en el vector

    public:
        PropiedadGeneral() {} //Constructor vacío
    PropiedadGeneral(int id, string nomb, int prec, int col, int incol, int costoCasa, int pbase, int unaCasa, int dosCasa, int tresCasa, int cuatroCasa, int hotel) { //Constructor lleno //Id, Nombre, Precio compra, color, indice color, costo casa/hotel, precio base, precio 1 casa, precio 2 casa, precio 3 casa, precio 4 casa, precio hotel
        idPropiedad = id;
        nombre = nomb;
        precio = prec;
        precioHipoteca = prec / 2;
        color = col;
        indiceColor = incol;
        noCasas = 0;
        if (color <= 8) { //Significa que es una propiedad normal, y, por ende, tiene varios precios de renta
            rentas[0] = pbase;
            rentas[1] = pbase * 2;
            rentas[2] = unaCasa;
            rentas[3] = dosCasa;
            rentas[4] = tresCasa;
            rentas[5] = cuatroCasa;
            rentas[6] = hotel;

        }
    }

    void comprar(int idJugador); //Compra la casilla
    int cobrar(int idJugador); //Regresa el dinero que se tiene que cobrar
    void hipotecar(int idJugador); //Se le añade el precio de hipoteca al dinero del jugador
    void deshipotecar(int idJugador); //Se le añade tarjet
    int tieneSetColor(int idJugador); //Checa si el jugador tiene todo un set de colores

    string tipoColor() { //Dependiendo del "color" de la propiedad, dice en forma de string lo que es
        switch (color) {
        case 0:
            return "de la zona cafe";
        case 1:
            return "de la zona azul cielo";
        case 2:
            return "de la zona rosa";
        case 3:
            return "de la zona naranja";
        case 4:
            return "de la zona roja";
        case 5:
            return "de la zona amarilla";
        case 6:
            return "de la zona verde";
        case 7:
            return "de la zona azul marino";
        case 8:
            return "un tren";
        case 9:
            return "un servicio";
        default:
            return "";
        }
    }

    void imprimirDatos() {
        cout << "Precio de compra: $" << precio << cnl;

        if (color < 8) {
            cout << "Renta base: $" << rentas[0] << cnl;
            cout << "Renta con el set de color: $" << rentas[0] << cnl;
            for (int i = 2; i < 6; i++) {
                cout << "Renta con " << i - 1 << " casas: $" << rentas[i] << cnl;
            }
            cout << "Renta con hotel: $" << rentas[6] << cnl;

            cout << "Actualmente cuenta con " << noCasas << " casas" << cnl;
        } else if (color == 8) {
            cout << "1 tren: $25" << cnl;
            cout << "2 trenes: $50" << cnl;
            cout << "3 trenes: $100" << cnl;
            cout << "4 trenes: $200" << cnl;
        } else {
            cout << "Si tiene 1 servicio, x4 del dado" << cnl;
            cout << "Si tiene 2 servicios x10 del dado" << cnl;
        }
        if(hipotecada==true) cout<<"Está hipotecada";
    }

    void caer(int idJugador);

    //Setter & Getter nombre
    void setNombre(string nomb) {
        nombre = nomb;
    }
    string getNombre() {
        return nombre;
    }

    //Setter & Getter precio
    void setPrecio(int prec) {
        precio = prec;
    }
    int getPrecio() {
        return precio;
    }

    //Setter & Getter idDueno
    void setIdDueno(int id) {
        idDueno = id;
    }
    int getIdDueno() {
        return idDueno;
    }

    //Setter & Getter hipotecada
    void setHipotecada(bool hip) {
        hipotecada = hip;
    }
    bool getHipotecada() {
        return idDueno;
    }

    //Setter & Getter precioHipoteca
    void setPrecioHipoteca(int precHipot) {
        precioHipoteca = precHipot;
    }
    int getPrecioHipoteca() {
        return precioHipoteca;
    }

    //Setter & Getter color
    void setColor(int col) {
        color = col;
    }
    int getColor() {
        return color;
    }

    //Setter & Getter costoCasa
    void setCostoCasa(int cos) {
        costoCasa = cos;
    }
    int getCostoCasa() {
        return costoCasa;
    }

    //Setter & Getter noCasas
    void setNoCasas(int no) {
        noCasas = no;
    }
    int getNoCasas() {
        return noCasas;
    }

    //Setter & Getter rentas
    void setRentas(int ren, int in ) {
        rentas[in] = ren;
    }
    int getRentas(int in ) {
        return rentas[in];
    }

    //Setter & Getter indiceColor
    void setIndiceColor(int in ) {
        indiceColor = in;
    }
    int getIndiceColor() {
        return indiceColor;
    }

    void construirCasa();
    void venderCasa();

    //Métodos
    //-Revisar si tiene dueño
    //En caso de que no permitir comprar
    //Si si tiene cobrar lo mandamos al método en específico
    //-Comprar
    //-Cobrar General
    //Hipotecar
};
vector < PropiedadGeneral > propiedades;

class Jugador {
    int id = 0; //ID=0 es banco
    string nombre = "Banco";
    vector < int > numPropiedad; //Guarda el índice de la posición de las propiedades del usuario
    int numCasilla = 0;
    int dinero = 1500;
    bool salirCarcel = 0;
    bool bancarrota = 0;
    bool enCarcel = 0;

    public:

        Jugador() {} //Constructor vacío, termina generando el banco
    Jugador(string n, int i) { //Se le mete el índice y el nombre del jugador
        id = 0;
        nombre = n;
    }

    int dado() { //Genera 2 números aleatorios de 1 a 6, los suma y regresa el número
        srand(time(NULL)); //Inicializa la semilla para la generación de números aleatorios
        int d = rand() % 12 + 1; //Crea números aleatorios
        return d;
    }

    int unDado() { //Genera 1 número aleatorio de 1 a 6
        srand(time(NULL)); //Inicializa la semilla para la generación de números aleatorios
        int d = rand() % 6 + 1; //Crea números aleatorios
        return d;
    }

    bool hipotecar() { //Muestra las propiedades que se tienen y que se pueden hipotecar
        cout << "Propiedades:" << cnl;
        bool checador=true;
        for (int i = 0; i < numPropiedad.size(); i++) { //Recorre el vector de propiedades
            if(propiedades[numPropiedad[i]].getHipotecada()==false) checador=false;
        }
        if(checador==true){
            return true;
        }
        for (int i = 0; i < numPropiedad.size(); i++) { //Recorre el vector de propiedades
            cout << "\t" << i << ".- " << propiedades[numPropiedad[i]].getNombre() << " -  $" << propiedades[numPropiedad[i]].getPrecioHipoteca() << endl; //Imprime el nombre de la propiedad y el precio que te regresará
        }
        cout << "Ingrese el indice de la propiedad que desea hipotecar: ";
        int aux;
        cin >> aux;
        aux--;
        propiedades[numPropiedad[aux]].hipotecar(id); //Se hipoteca la propiedad que escoja el usuario
        
        return 1;
    }

    void modificarDinero(int n) { //Se le mete una variable, ya se positiva o negativa y se modifica el dinero
        dinero += n;
        while (dinero < 0) { //En caso de que se tenga un dinero negativo manda a llamar una función para obligar al usuario a cancelar la deuda
            cout << "Se tiene dinero negativo, se deben $" << -dinero << " al banco" << cnl;
            if (hipotecar() == 1) {
                cout << "Ya no se tiene dinero ni propiedades para hipotecar, queda en bancarrota" << cnl;
                bancarrota = 1;
                break;
            }
        }
    }

    void anadirPropiedad(int idPropiedad) {
        numPropiedad.push_back(idPropiedad);
    }

    void mover(int x) { //Se le mete el índice de la casilla a donde se moverá el usuario
        numCasilla = x;
    }

    /*Contunto de getters*/
    int getId() {
        return id;
    }
    string getNombre() {
        return nombre;
    }
    int getCasilla() {
        return numCasilla;
    }
    int getDinero() {
        return dinero;
    }
    bool getStatusSalirCarcel() {
        return salirCarcel;
    }
    bool getStatusBancarrota() {
        return bancarrota;
    }
    bool getStatusCarcel() {
        return enCarcel;
    }
    vector < int > getListaPropiedades() {
        return numPropiedad;
    }

    /*Conjunto de setters*/
    //No tiene setId ya que no se modifica
    //No tiene setNombre ya que no se modifica
    //La función setCasilla() es enrealidad mover()
    //La función setDinero() es enrealidad modificarDinero()
    void setStatusSalirCarcel(bool a) {
        salirCarcel = a;
    }
    void setStatusBancarrota(bool a) {
        bancarrota = a;
    }
    void setStatusCarcel(bool a) {
        enCarcel = a;
    }

    //Métodos
    //-Tirar dado
    //-Mover jugador a ID casilla
    //-Getters
    //Setters		
    //-Modificar dinero
};
vector < Jugador > jugadores; //Crea el vector de jugadores donde se van a hacer operaciones varias

class Casilla {
    int tipo = 0; //GO=0, Propiedad=1, CAzul=2, Impuesto(200)=3, Ferrocarril=4, CNaranja=5, Carcel=6, Servicio=7, FreeParking=8, GoToJail=9 Impuesto(100)=10
    int idPropiedad;

    public:

        Casilla(int t, int id) {
            tipo = t;
            idPropiedad = id;
        }
    Casilla(int t) {
        tipo = t;
    }
    Casilla() {}

    string getNombre() {
        switch (tipo) {
        case 0:
            return "Casilla de salida";
        case 1:
            return propiedades[idPropiedad].getNombre();
        case 2:
            return "Casilla de correo";
        case 3:
            return "El pago de mitec";
        case 4: //Es ferrocaril
            return propiedades[idPropiedad].getNombre();
        case 5:
            return "Casilla de sorteo";
        case 6:
            return "Centro de dignidad humana";
        case 7:
            return propiedades[idPropiedad].getNombre();
        case 8:
            return "La nada";
        case 9:
            return "La casa de Linda Revo";
        case 10:
            return "Impuestos";
        }
        return "";
    }

    int getIdPropiedad() {
        return idPropiedad;
    }

    int idSeleccion() {
        int id = rand() % 16;

        return id;
    }

    void donacion(int idJugador, int donationm) { // Devuelve el número de jugadores vivos.
        for (int i = 0; i < jugadores.size(); i++) {
            if (jugadores[i].getStatusBancarrota() == 0) {
                jugadores[i].modificarDinero(donationm);
                jugadores[idJugador].modificarDinero(-donationm);
            }
        }
    }

    void accion(int idJugador) {
        int id;
        switch (tipo) {
        case 0:
            cout << "Has pasado por GO!\nRecolecta tus $200 :3" << endl;
            jugadores[idJugador].modificarDinero(200);
            break;
        case 1:
            propiedades[idPropiedad].caer(idJugador);
            break;
        case 2:
            /* | | | | | --- FALTA PONER LO QUE SE HACE EN CASO DE QUE SEA UNA TARJETA AZUL --- | | | | |*/
            id = idSeleccion(); //id se refiere al número de tarjeta tomada
            switch (id) {
            case 1:
                cout << "Avanza a Hábitad.";
                jugadores[idJugador].mover(39);
                break;
            case 2:
                cout << "Avanza al inicio (Recoge tus $200).";
                jugadores[idJugador].mover(10);
                jugadores[idJugador].modificarDinero(+200);
                break;
            case 3:
                cout << "Avanza al edificio de medicina.";
                jugadores[idJugador].mover(24);
                break;
            case 4:
                cout << "Avanza a Aulas IV.";
                jugadores[idJugador].mover(11);
                break;
            case 5:
                cout << "Avanza al restaurante más cercano, si no tiene propietario, cómprala, si ya tiene uno, pagale el doble de la renta al usuario.";
                propiedades[idPropiedad].caer(idJugador);
                break;
            case 6:
                cout << "Avanza al restaurante más cercano, si no tiene propietario, cómprala, si ya tiene uno, pagale el doble de la renta al usuario.";
                propiedades[idPropiedad].caer(idJugador);
                break;
            case 7:
                cout << "Avanza al servicio más cercano, si no tiene propietario, cómprala, si ya tiene uno, pagale el doble de la renta al usuario.";
                propiedades[idPropiedad].caer(idJugador);
                break;
            case 8:
                cout << "El banco te paga $50 por transacción equivocada, toma $50.";
                jugadores[idJugador].modificarDinero(+50);
                break;
            case 9:
                cout << "Tienes buena reputación, tienes un pase para salir del Centro de Dignidad Humana gratis.";
                jugadores[idJugador].setStatusSalirCarcel(1);
                break;
            case 10:
                cout << "Están remodelando aquí de momento, retrocede 3 casillas.";
                jugadores[idJugador].mover((40 + jugadores[idJugador].getCasilla() - 3) % 40);
                break;
            case 11:
                cout << "Te burlaste de un colimense, vas directo al centro de dignidad humana, y no recojas tus $200 si le das la vuelta al campus.";
                jugadores[idJugador].setStatusCarcel(true);
                jugadores[idJugador].mover(10);
                break;
            case 12:
                cout << "Has sido patrocinador de un club del tec, dona a cada jugador $25.";
                donacion(idJugador, 25);
                break;
            case 13:
                cout << "Te detuvieron por exceso de velocidad dentro del Tec, da $15.";
                jugadores[idJugador].modificarDinero(-15);
                break;
            case 14:
                cout << "Avanza al Starbucks, si le das la vuelta al campus recibe tus $200.";
                jugadores[idJugador].mover(5);
                break;
            case 15:
                cout << "Has sido patrocinador de un club del tec, dona a cada jugador $50.";
                donacion(idJugador, 50);
                break;
            case 16:
                cout << "Ganaste una rifa que te compraron, recibe $150 por parte del Banco Tec.";
                jugadores[idJugador].modificarDinero(+150);
                break;
            }
            break;
        case 3:
            cout << "Se te fue la mano en el oxxo, gastaste $200, paga AHORA!\n";
            jugadores[idJugador].modificarDinero(-200);
            break;
        case 4:
            cout << "Te volviste homie de los restaurantes\n";
            propiedades[idPropiedad].caer(idJugador);
            break;
        case 5:
            /* | | | | | --- FALTA PONER LO QUE SE HACE EN CASO DE QUE SEA UNA TARJETA NARANJA --- | | | | |*/
            id = idSeleccion(); //id se refiere al número de tarjeta tomada
            switch (id) {
            case 1:
                cout << "Avance a caseta. Recibe $200." << endl;
                jugadores[idJugador].modificarDinero(200);
                break;

            case 2:
                cout << "Eres foráneo y tus papás te acaban de depositar. Recibe $200." << endl;
                jugadores[idJugador].modificarDinero(200);
                break;
            case 3:
                cout << "Te caíste de una bicicleta, te salió un morete y TecMed te cobró el hielo. Paga $50." << endl;
                jugadores[idJugador].modificarDinero(-50);
                break;

            case 4:
                cout << "Decidiste emprender y vendiste brownies. Fueron un éxito. Recibe $50." << endl;
                jugadores[idJugador].modificarDinero(50);

                break;

            case 5:
                cout << "Ahórrate un ETHOS. Sal del Centro de Dignidad Humana gratis." << endl;
                jugadores[idJugador].setStatusSalirCarcel(1);

                break;

            case 6:
                cout << "Dirígete al Centro de Dignidad Humana. Ve directamente, no pases a Caseta, no cobres $200." << endl;
                jugadores[idJugador].setStatusCarcel(true);
                jugadores[idJugador].mover(10);

                break;

            case 7:
                cout << "La salud mental es primero. Diste de baja una materia. Recibe $100." << endl;
                jugadores[idJugador].modificarDinero(100);

                break;

            case 8:
                cout << "Decidiste llevar lonche en vez de comprar en campus. Recibe $20." << endl;
                jugadores[idJugador].modificarDinero(20);

                break;

            case 9:
                cout << "Salvaste al equipo de reprobar. Recibe $10 de cada jugador." << endl; //no estoy muy seguro de este caso
                jugadores[idJugador].modificarDinero(jugadores.size() * 10);
                for (int i = 1; jugadores.size(); i++) {
                    if (i == idJugador) continue;
                    jugadores[i].modificarDinero(-10);
                }

                break;

            case 10:
                cout << "Después de semana 5 requieres ayuda psiquiátrica. Tu seguro de gastos médicos mayores lo cubre. Recibe $100." << endl;
                jugadores[idJugador].modificarDinero(100);

                break;

            case 11:
                cout << "La maquina expendedora se tragó tu billete. Paga $50" << endl;
                jugadores[idJugador].modificarDinero(-50);

                break;

            case 12:
                cout << "Hora de cubrir tu seguro de gastos médicos mayores. Paga $100." << endl;
                jugadores[idJugador].modificarDinero(-100);

                break;

            case 13:
                cout << "Ganaste un termo de Linda REVO. Recibe $25." << endl;
                jugadores[idJugador].modificarDinero(25);

                break;

            case 14:
                cout << "Ser foráneo sale caro. Paga $40 por cada piso, $150 por cada edificio." << endl;

                break;

            case 15:
                cout << "Es Jueves de 2x1 en Dolphy y te ahorraste dinero. Recibe $10." << endl;
                jugadores[idJugador].modificarDinero(10);

                break;

            case 16:
                cout << "Te graduaste de administración de empresas. Heredas el negocio de tu papá. Recibe $100." << endl;
                jugadores[idJugador].modificarDinero(100);

                break;

            }
            break;
        case 6:
            cout << "Al tope de la funa, pero solo pasando al lado del Centro de Dignidad Humana\n";
            break;
        case 7:
            cout << "La familia TEC esta para ti\n";
            propiedades[idPropiedad].caer(idJugador);
            break;
        case 8:
            cout << "Estás viendo la nada\n";
            break;
        case 9:
            cout << "Te cacharon siendo funaaadoo, nimodo, para el Centro de Dignidad Humana, ora, que se aplaste\n";
            jugadores[idJugador].setStatusCarcel(true);
            jugadores[idJugador].mover(10);
            break;
        case 10:
            cout << "Nombre carnal, te toca pagar intensivos, ora dame 100\n";
            jugadores[idJugador].modificarDinero(-100);
            break;
        }
    }
    //Métodos
    //Hacer algo si es GO
    //Dar 200 al jugador
    //Hacer algo si es Propiedad
    //Hacer algo si es Cartas
    //Mandar al ID de Cárcel
    //Pass si es Free parking
    //Pagar 200 si es Impuesto(200)
    //Pagar 100 si es Impuesto(100)
};

class Tablero {
    vector < Casilla > casillas;

    public:
        Tablero() {
            //Color: 0-Café, 1-Azul Bajito, 2-Rosa 3-Naranja 4-Rojo 5-Amarillo 6-Verde 7-Azul Oscuro 8-Trenes 9-Servicios
            //Indice Color: -Cafe:0 -Azul Bajito: 2 -Rosa: 5 -Naranja: 8 -Rojo: 11 -Amarillo: 14 -Verde:17 -Azul Oscuro: 20 -Trenes: 22 -Servicios: 26
            /*Inicialización de todas las casillas*/

            /*Propiedad 0*/
            propiedades.push_back(PropiedadGeneral(0, "Aulas V", 60, 0, 0, 50, 2, 10, 30, 90, 160, 250)); //Id, Nombre, Precio compra, color, indice color, costo casa/hotel, precio base, precio 1 casa, precio 2 casa, precio 3 casa, precio 4 casa, precio hotel //Café 1
            /*Propiedad 1*/
            propiedades.push_back(PropiedadGeneral(1, "Aulas VI", 60, 0, 0, 50, 4, 20, 60, 180, 320, 450)); //Café 2
            /*Propiedad 2*/
            propiedades.push_back(PropiedadGeneral(2, "Aulas I", 100, 1, 2, 50, 6, 30, 90, 270, 400, 550)); //Azul cielo 1
            /*Propiedad 3*/
            propiedades.push_back(PropiedadGeneral(3, "Aulas II", 100, 1, 2, 50, 6, 30, 90, 270, 400, 550)); //Azul cielo 2
            /*Propiedad 4*/
            propiedades.push_back(PropiedadGeneral(4, "Aulas III", 120, 1, 2, 50, 8, 40, 100, 300, 450, 600)); //Azul cielo 3
            /*Propiedad 5*/
            propiedades.push_back(PropiedadGeneral(5, "Aulas IV", 140, 2, 5, 100, 10, 50, 150, 450, 625, 750)); //Rosa 1
            /*Propiedad 6*/
            propiedades.push_back(PropiedadGeneral(6, "Edificio Administrativo", 140, 2, 5, 100, 10, 50, 150, 450, 625, 750)); //Rosa 2
            /*Propiedad 7*/
            propiedades.push_back(PropiedadGeneral(7, "Tec Med", 160, 2, 5, 100, 12, 60, 180, 500, 700, 900)); //Rosa 3
            /*Propiedad 8*/
            propiedades.push_back(PropiedadGeneral(8, "Estadio Borregos", 180, 3, 8, 100, 14, 70, 200, 550, 750, 950)); //Naranja 1
            /*Propiedad 9*/
            propiedades.push_back(PropiedadGeneral(9, "Domo Deportivo", 180, 3, 8, 100, 14, 70, 200, 550, 750, 950)); //Naranja 2
            /*Propiedad 10*/
            propiedades.push_back(PropiedadGeneral(10, "Difusión cultural", 200, 3, 8, 100, 16, 80, 220, 600, 800, 1000)); //Naranja 3
            /*Propiedad 11*/
            propiedades.push_back(PropiedadGeneral(11, "Alberca", 220, 4, 11, 150, 18, 90, 250, 700, 875, 1050)); //Rojo 1
            /*Propiedad 12*/
            propiedades.push_back(PropiedadGeneral(12, "Ciberplaza", 220, 4, 11, 150, 18, 90, 250, 700, 875, 1050)); //Rojo 2
            /*Propiedad 13*/
            propiedades.push_back(PropiedadGeneral(13, "Edificio de Medicina", 240, 4, 11, 150, 20, 100, 300, 750, 925, 1100)); //Rojo 3
            /*Propiedad 14*/
            propiedades.push_back(PropiedadGeneral(14, "Residencias TEC", 220, 5, 14, 150, 22, 110, 330, 800, 975, 1150)); //Rojo 1
            /*Propiedad 15*/
            propiedades.push_back(PropiedadGeneral(15, "E-SPORTS Arena", 220, 5, 14, 150, 22, 110, 330, 800, 975, 1150)); //Rojo 2
            /*Propiedad 16*/
            propiedades.push_back(PropiedadGeneral(16, "El GYM", 240, 5, 14, 150, 24, 120, 360, 850, 1025, 1200)); //Rojo 3
            /*Propiedad 17*/
            propiedades.push_back(PropiedadGeneral(17, "Biblio", 300, 6, 17, 200, 26, 130, 390, 900, 1100, 1275)); //Verde 1
            /*Propiedad 18*/
            propiedades.push_back(PropiedadGeneral(18, "CARD", 300, 6, 17, 200, 26, 130, 390, 900, 1100, 1275)); //Verde 2
            /*Propiedad 19*/
            propiedades.push_back(PropiedadGeneral(19, "EIAD", 320, 6, 17, 200, 28, 150, 450, 1000, 1200, 1400)); //Verde 3
            /*Propiedad 20*/
            propiedades.push_back(PropiedadGeneral(20, "Centro de congresos", 350, 7, 20, 200, 35, 175, 500, 1100, 1300, 1500)); //Azul Oscuro 1
            /*Propiedad 21*/
            propiedades.push_back(PropiedadGeneral(21, "Hábitat de negocios", 400, 7, 20, 200, 50, 200, 600, 1400, 1700, 2000)); //Azul Oscuro 2
            /*Propiedad 22*/
            propiedades.push_back(PropiedadGeneral(22, "Starbucks", 200, 8, 22, 25, 0, 0, 0, 0, 0, 0)); //Trenes 1
            /*Propiedad 23*/
            propiedades.push_back(PropiedadGeneral(23, "Flor de Córdoba", 200, 8, 22, 25, 0, 0, 0, 0, 0, 0)); //Trenes 2
            /*Propiedad 24*/
            propiedades.push_back(PropiedadGeneral(24, "Subway", 200, 8, 22, 25, 0, 0, 0, 0, 0, 0)); //Trenes 3
            /*Propiedad 25*/
            propiedades.push_back(PropiedadGeneral(25, "Juvie Jus", 200, 8, 22, 25, 0, 0, 0, 0, 0, 0)); //Trenes 4
            /*Propiedad 26*/
            propiedades.push_back(PropiedadGeneral(26, "Locatec", 200, 9, 26, 1, 0, 0, 0, 0, 0, 0)); //Servicios 1
            /*Propiedad 27*/
            propiedades.push_back(PropiedadGeneral(27, "Tec Services", 200, 9, 26, 1, 0, 0, 0, 0, 0, 0)); //Servicios 2

            //GO=0, Propiedad=1, CAzul=2, Impuesto(200)=3, Ferrocarril=4, CNaranja=5, Carcel=6, Servicio=7, FreeParking=8, GoToJail=9 Impuesto(100)=10

            /*Casilla 0*/
            casillas.push_back(Casilla(0)); //Crea el GO
            /*Casilla 1*/
            casillas.push_back(Casilla(1, 0)); //Crea la casilla de id 1, de tipo 1(propiedad) con su propiedad en índice 0
            /*Casilla 2*/
            casillas.push_back(Casilla(2));
            /*Casilla 3*/
            casillas.push_back(Casilla(1, 1));
            /*Casilla 4*/
            casillas.push_back(Casilla(3)); //Impuesto de 200
            /*Casilla 5*/
            casillas.push_back(Casilla(4, 22));
            /*Casilla 6*/
            casillas.push_back(Casilla(1, 2));
            /*Casilla 7*/
            casillas.push_back(Casilla(5));
            /*Casilla 8*/
            casillas.push_back(Casilla(1, 3));
            /*Casilla 9*/
            casillas.push_back(Casilla(1, 4));
            /*Casilla 10*/
            casillas.push_back(Casilla(6));
            /*Casilla 11*/
            casillas.push_back(Casilla(1, 5));
            /*Casilla 12*/
            casillas.push_back(Casilla(7, 26));
            /*Casilla 13*/
            casillas.push_back(Casilla(1, 6));
            /*Casilla 14*/
            casillas.push_back(Casilla(1, 7));
            /*Casilla 15*/
            casillas.push_back(Casilla(4, 23));
            /*Casilla 16*/
            casillas.push_back(Casilla(1, 8));
            /*Casilla 17*/
            casillas.push_back(Casilla(2));
            /*Casilla 18*/
            casillas.push_back(Casilla(1, 9));
            /*Casilla 19*/
            casillas.push_back(Casilla(1, 10));
            /*Casilla 20*/
            casillas.push_back(Casilla(8));
            /*Casilla 21*/
            casillas.push_back(Casilla(1, 11));
            /*Casilla 22*/
            casillas.push_back(Casilla(5));
            /*Casilla 23*/
            casillas.push_back(Casilla(1, 12));
            /*Casilla 24*/
            casillas.push_back(Casilla(1, 13));
            /*Casilla 25*/
            casillas.push_back(Casilla(4, 24));
            /*Casilla 26*/
            casillas.push_back(Casilla(1, 14));
            /*Casilla 27*/
            casillas.push_back(Casilla(1, 15));
            /*Casilla 28*/
            casillas.push_back(Casilla(7, 27));
            /*Casilla 29*/
            casillas.push_back(Casilla(1, 16));
            /*Casilla 30*/
            casillas.push_back(Casilla(9));
            /*Casilla 31*/
            casillas.push_back(Casilla(1, 17));
            /*Casilla 32*/
            casillas.push_back(Casilla(1, 18));
            /*Casilla 33*/
            casillas.push_back(Casilla(2));
            /*Casilla 34*/
            casillas.push_back(Casilla(1, 19));
            /*Casilla 35*/
            casillas.push_back(Casilla(4, 25));
            /*Casilla 36*/
            casillas.push_back(Casilla(5));
            /*Casilla 37*/
            casillas.push_back(Casilla(1, 20));
            /*Casilla 38*/
            casillas.push_back(Casilla(10));
            /*Casilla 39*/
            casillas.push_back(Casilla(1, 21));
        }

    bool jugadoresVivos() { // Si hay por lo menos 3 jugadores vivos, devuelve true, sino false. False indica el fin del juego.
        int contadorVivos = 0;
        for (int i = 0; i < jugadores.size(); i++) {
            if (jugadores[i].getStatusBancarrota() == 0) {
                contadorVivos++;
            }
        }
        if (contadorVivos < 3) {
            return false;
        } else {
            return true;
        }
    }

    void menu(int idJugador) { //Muestra el menú de juego y pide al jugador que elija una opción. 
        int dado = jugadores[idJugador].dado(); //Se obtiene el valor de lo que podría ser sus dados
        bool aunTurno = 1, yaAvanzo = 0, setCompleto = 0;

        //Dice que jugador está jugando y en qué casilla:
        cout << "Turno de " << jugadores[idJugador].getNombre() << cnl;

        //Revisa si el jugador sigue vivo
        if (jugadores[idJugador].getStatusBancarrota() == 1) {
            cout << "Está en bancarrota, no puede jugar" << cnl;
            return; //Como el jugador ya perdió su turno no es necesario jugar
        }

        //Revisa si el jugador está en la cárcel
        if (jugadores[idJugador].getStatusCarcel()) { //Si el jugador está en la cárcel hace esto
            if (jugadores[idJugador].getStatusSalirCarcel() == true) { //Se mete si el jugador tiene la jail free card
                jugadores[idJugador].setStatusCarcel(false);
            } else { //En dado caso de que no tenga una jail free card, hace esto
                int d1 = jugadores[idJugador].unDado();
                int d2 = jugadores[idJugador].unDado();
                cout << "En el primer dado salió " << d1 << cnl;
                cout << "En el segundo dado salió " << d2 << cnl;
                if (d1 == d2) {
                    dado = d1 + d2; //Se actualiza el valor del dado ya que esos son los valores que se usarían
                    cout << "Los dados salieron iguales, puede salir, va a recorrer la suma de sus dados: " << dado << cnl;
                } else { //No pudo salir de la carcel, se termina su turno
                    cout << "Sus dados no son iguales, termina su turno" << cnl;
                    yaAvanzo = 1;
                }
            }
        }

        //Para este punto ya podría jugar normalmente el usuario

        while (aunTurno == 1) { //Muestra las diferentes opciones que puede hacer el usuario
            nl;
            //Muestra la información actual del jugador y de los jugadores alrededor de el
            cout << "Se encuentra en la casilla " << jugadores[idJugador].getCasilla() << " - " << casillas[jugadores[idJugador].getCasilla()].getNombre() << cnl;
            cout << "Se tienen $" << jugadores[idJugador].getDinero() << cnl;
            cout << "Tiene " << jugadores[idJugador].getListaPropiedades().size() << " propiedades" << cnl;
            for (int i = 0; i < jugadores[idJugador].getListaPropiedades().size(); i++) {
                cout << "\t" << i + 1 << " - " << propiedades[jugadores[idJugador].getListaPropiedades()[i]].getNombre() << cnl;
            }
            nl;
            cout << "Las posiciones de sus rivales:" << cnl;
            for (int i = 1; i < jugadores.size(); i++) {
                if (i == idJugador) continue;
                cout << jugadores[i].getNombre() << " se encuentra en la casilla " << jugadores[i].getCasilla() << " - " << casillas[jugadores[i].getCasilla()].getNombre() << cnl;
            }

            cout << "¿Qué desea hacer?" << cnl;
            if (yaAvanzo == 0) cout << "\tA.- Avanzar" << cnl;
            if (jugadores[idJugador].getListaPropiedades().size() >= 1) { //Se tienen propiedades
                cout << "\tL.- Ver lista de mis propiedades" << cnl;
                cout << "\tH.- Hipotecar" << cnl;
                cout << "\tD.- Deshipotecar" << cnl;
                for (auto i: jugadores[idJugador].getListaPropiedades()) { //Checa en las propiedades si hay alguna que coincida con que el usuario tenga una mismo set al menos
                    if (propiedades[i].tieneSetColor(idJugador) == 0 && propiedades[i].getColor() < 8) {
                        setCompleto = true;
                        break;
                    }
                }
                if (setCompleto == true) {
                    cout << "\tC.- Comprar casas/hoteles" << cnl;
                    cout << "\tV.- Vender casas/hoteles" << cnl;
                }
            }
            if (yaAvanzo == 1) cout << "\tT.- Terminar turno" << cnl;

            string aux;
            while (aunTurno == 1) {
                cout << "Escriba el caracter correspondiente: ";
                cin >> aux;
                if ((aux == "A" && yaAvanzo == 0) || ((aux == "H" || aux=="D" ||aux == "L") && jugadores[idJugador].getListaPropiedades().size() >= 1) || ((aux == "C" || aux == "V") && setCompleto == true) || (aux == "T" && yaAvanzo == 1)) { //Significa que dió bien la entrada
                    break;
                }
                cout << "Se escribó algo mal, vuelva a intentarlo" << cnl;
            }

            nl;

            if (aux == "A") { //Si eligió avanzar
                int nPos = jugadores[idJugador].getCasilla() + dado;
                if (nPos >= 40) { //le dió la vuelta al tablero, tiene que pasar por el Go
                    nPos = nPos - 40;
                    jugadores[idJugador].modificarDinero(200);
                    cout << "Te depositaron tus papás, ganas $200" << cnl;
                }
                jugadores[idJugador].mover(nPos);
                cout << "Viajó a la casilla " << nPos << cnl;
                casillas[nPos].accion(idJugador);
                yaAvanzo = 1;
            }

            if (aux == "L") { //Si eligió ver la lista de sus propiedades
                cout << "Con los números de las propiedades dichas anteriormente, ¿cuál desea visualizar? ";
                int x;
                cin >> x;
                propiedades[jugadores[idJugador].getListaPropiedades()[x - 1]].imprimirDatos();
            }

            if (aux == "H") { //Si eligió hipotecar
                cout << "Con los números de las propiedades dichas anteriormente, ¿cuál desea hipotecar? ";
                int x;
                cin >> x;
                propiedades[jugadores[idJugador].getListaPropiedades()[x - 1]].hipotecar(idJugador);
            }

            if (aux == "D") { //Si eligió deshipotecar
                cout << "Con los números de las propiedades dichas anteriormente, ¿cuál desea deshipotecar? ";
                int x;
                cin >> x;
                propiedades[jugadores[idJugador].getListaPropiedades()[x - 1]].deshipotecar(idJugador);
            }

            if (aux == "C") { //Si eligió comprar casas
                cout << "Con los números de las propiedades dichas anteriormente, ¿a cuál le desea comprar casas? ";
                int x;
                cin >> x;
                propiedades[jugadores[idJugador].getListaPropiedades()[x - 1]].construirCasa();
            }

            if (aux == "V") { //Si eligió vender casas
                cout << "Con los números de las propiedades dichas anteriormente, ¿a cuál le desea vender casas? ";
                int x;
                cin >> x;
                propiedades[jugadores[idJugador].getListaPropiedades()[x - 1]].venderCasa();
            }

            if (aux == "T") { //Si eligió terminar su turno
                aunTurno = 0;
            }
        }
    }
    //Métodos
    //Checar si todos los jugadores están vivos
    //Desplegar menú de que se va a hacer

};

int main() {
    Tablero tablero;
    /*inicializar y preguntar nombre y orden de jugadores*/
    jugadores.push_back(Jugador("Banco", 0)); //Se añade el jugador base llamado banco
    int n;
    cout << "¿Cuántos jugadores van a jugar? ";
    cin >> n;
    string nombre;
    for (int i = 1; i <= n; i++) { //Se hace un ciclo para leer los nombres de los jugadores
        cout << "Dame el nombre del jugador " << i << ": ";
        cin >> nombre;
        jugadores.push_back(Jugador(nombre, i));
    }
    int idJugadorActual = 0; //El id del jugador actual
    while (tablero.jugadoresVivos() == true) { //Se hace un ciclo mientras haya jugadores vivos
        limpiarPantalla();
        idJugadorActual %= n; //Se va poniendo el id del jugador actual en orden
        idJugadorActual++;
        tablero.menu(idJugadorActual); //Se le despliega al menú del usuario de lo que puede hacer
        //Añadir función para limpiar consola
    }

    return 0;
}

//Funcion hipotecar
void PropiedadGeneral::hipotecar(int idJugador) {
    if (hipotecada == true) { //Ya no se puede hipotecar
        cout << "Esta propiedad ya ha sido hipotecada" << cnl;
        return;
    }
    setHipotecada(true);
    jugadores[idJugador].modificarDinero(getPrecioHipoteca());
    cout<<"Se hipotecó"<<cnl;
}

//Funcion deshipotecar
void PropiedadGeneral::deshipotecar(int idJugador) {
    if (hipotecada == false) { //Ya no se puede hipotecar
        cout << "No está hipotecada la propiedad." << cnl;
        return;
    }
    setHipotecada(false);
    jugadores[idJugador].modificarDinero(-getPrecioHipoteca());
    cout<<"Se deshipotecó"<<cnl;
}

//Función comprar
void PropiedadGeneral::comprar(int idJugador) {
    if (jugadores[idJugador].getDinero() <= precio) { //Checa que el jugador tenga verdaderamente el dinero necesario para comprarlo
        cout << "No tienes el dinero suficiente para comprarla, en dado caso de querer comprarala tendrá que hipotecar propiedades, desea continuar?\n\t1.- Si\n\t2.- No\nEscriba el indice: " << cnl; //Le dice al jugador que terminaría hipotecando algo si compra
        string aux;
        cin >> aux;
        if (aux != "1") return; //En caso de que no escoja que quiere comprarla, se termina la función sin comprar nada
    }
    jugadores[idJugador].modificarDinero(-precio); //Se compra la propiedad
    jugadores[idJugador].anadirPropiedad(idPropiedad); //Se añade la propiedad al jugador
    idDueno = idJugador; //Se actualiza el dueño de dicha propiedad
    cout << "Se compró la propiedad" << cnl;
}

//Función set de colores
int PropiedadGeneral::tieneSetColor(int idJugador) {
    if (idJugador == 0) return 1; //en caso de ser banco regresa que no es dueño de todas
    int c = 0; //Guarda la cantidad de propiedades del mismo color con diferente dueño
    for (int i = indiceColor; i < propiedades.size(); i++) { //Se hace hasta el size que es cuando acaba el vector
        if (propiedades[i].getColor() != color) { //Si es distinto el color actual al color de la casilla que estamos hablando termina la familia, por ende ya no ocupo checarlo
            break;
        }
        //Para este punto yo sé que son el mismo color, solo me falta verificar dueños
        if (propiedades[i].getIdDueno() != idJugador) { //El dueño de esa casilla es distinto al dueño de la propiedad con la que se trabaja
            c++; //Son distintos dueños, se añade al contador de distintos
        }
    }
    return c;
}

//Función cobrar
int PropiedadGeneral::cobrar(int idJugador) {
    int precioCobrar;
    if (color <= 7) { //significa que es un color normal, depende de casas y hoteles
        if (noCasas != 0) { //Se le aplica el precio correspondiente a sus casas y hoteles
            precioCobrar = rentas[noCasas + 1];
        } else if (tieneSetColor(getIdDueno()) == 0) { //son el mismo set de colores ya que son 0 dueños distintos
            precioCobrar = rentas[1];
        } else { //No tiene ni casas, ni hoteles ni un mismo set, es precio base
            precioCobrar = rentas[0];
        }
    } else if (color == 8) { //significa que es un tren
        int aux = tieneSetColor(getIdDueno());
        if (aux == 0) { //tiene los 4 trenes
            precioCobrar = 200;
        } else if (aux == 1) { //tiene 3 trenes
            precioCobrar = 100;
        } else if (aux == 2) { //tiene 2 trenes
            precioCobrar = 50;
        } else {
            precioCobrar = 25;
        }
    } else { //significa que es un servicio
        int dados = jugadores[idJugador].dado();
        if (tieneSetColor(getIdDueno()) == 0) { //el mismo dueño tiene ambos servicios
            precioCobrar = dados * 10;
        } else { //solo tiene un servicio
            precioCobrar = dados * 4;
        }
    }
    return precioCobrar;
}

//Funciones comprar y vender casas
void PropiedadGeneral::construirCasa() {
    int idJugador = getIdDueno();
    if (tieneSetColor(idJugador) == 0) {
        if (getNoCasas() >= 5) {
            cout << "Ya no puedes construir más casas" << endl;
        } else {
            setNoCasas(getNoCasas() + 1);
            jugadores[idJugador].modificarDinero(-costoCasa);
        }
    } else {
        cout << "No puedes construir casas en este color" << endl;
    }

}

void PropiedadGeneral::venderCasa() {
    int idJugador = getIdDueno();
    if (getNoCasas() <= 0) {
        cout << "No hay casas para vender" << endl;
    } else {
        setNoCasas(getNoCasas() - 1);
        jugadores[idJugador].modificarDinero(costoCasa / 2);
    }
}

void PropiedadGeneral::caer(int idJugador) { //Checa si tiene dueño o no
    cout << "Has caido en la casilla : " << nombre << ", es " << tipoColor() << cnl;

    //imprime los datos de precios

    if (idDueno == 0) { //El dueño es el banco, puede comprar
        cout << "Quieres comprarlo?\n\t1.- Si\n\t2.- No\nEscribe el digito: ";
        string aux;
        cin >> aux;
        if (aux == "1") {
            comprar(idJugador);
        }
    } else if (idDueno == idJugador) { //El dueño es quien cayó ahí mismo, no se hace nada
        cout << "Usted mismo es el dueño de esta propiedad" << cnl;
    } else { //Quien cayó ahí es otro jugador aparte, tiene que cobrar
        cout << "Esta propiedad es de alguien más, tiene que pagar" << cnl;
        int pRenta = cobrar(idJugador);
        cout << "El precio de renta es: $" << pRenta << cnl;
        jugadores[idJugador].modificarDinero(-pRenta);
    }
}
