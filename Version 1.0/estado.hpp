#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <stack>
using namespace std;

class estado;
class barra;
class esqueleto;

class roca {
    public:
        roca(int fila, int col, int direccion, bool primera_roca=false): fila_(fila), col_(col), pivote_(true), objeto_(-1), tiempo_(0), tiempo_limite_(7), direccion_(direccion), primera_roca_(primera_roca) {}
        roca(const roca& rock): fila_(rock.fila_), col_(rock.col_), pivote_(rock.pivote_), objeto_(rock.objeto_), tiempo_(rock.tiempo_), tiempo_limite_(rock.tiempo_limite_), direccion_(rock.direccion_), primera_roca_(rock.primera_roca_) {}
        //Observadores
        int fila() const {return fila_;}
        int col() const {return col_;}
        bool pivote() const {return pivote_;}
        int objeto() const {return objeto_;}
        int tiempo() const {return tiempo_;}
        int tiempo_limite() const {return tiempo_limite_;}
        int direccion() const {return direccion_;}
        bool primera_roca() const {return primera_roca_;}
        //Fin observadores
        //Modificadores
        int& fila() {return fila_;}
        int& col() {return col_;}
        bool& pivote() {return pivote_;}
        int& objeto() {return objeto_;}
        int& tiempo() {return tiempo_;}
        int& tiempo_limite() {return tiempo_limite_;}
        int& direccion() {return direccion_;}
        bool& primera_roca() {return primera_roca_;}
        //Fin modificadores
        //Operador de asignacion
        roca& operator=(const roca& rock) {
            fila_=rock.fila_;
            col_=rock.col_;
            pivote_=rock.pivote_;
            objeto_=rock.objeto_;
            tiempo_=rock.tiempo_;
            tiempo_limite_=rock.tiempo_limite_;
            direccion_=rock.direccion_;
            primera_roca_=rock.primera_roca_;
            return *this;
        }
        //Fin operador de asignacion
        //Funciones complejas
        void actualizar(estado& est, int& direccion, int& fila, int& col, roca& roca_eliminar);  //Actualizar estado por referencia
        //Fin funciones complejas
    private:
        int fila_;
        int col_;
        bool pivote_;
        int objeto_;    //Objeto como llaves que suelta al autodestruirse
        int tiempo_;
        int tiempo_limite_;
        int direccion_;
        bool primera_roca_;
};

class placa {
    public:
        placa(int tipo, int filaobj, int colobj): tipo_(tipo), fila_(-1), col_(-1), filaobj_(filaobj), colobj_(colobj), anadido_(false), actualizada_(false), esqueleto_(nullptr), barra_(nullptr), averiada_(false) {}
        placa(const placa& p): tipo_(p.tipo_), infinito_(p.infinito_), fila_(p.fila_), col_(p.col_), filaobj_(p.filaobj_), colobj_(p.colobj_), anadido_(p.anadido_), actualizada_(p.actualizada_), esqueleto_(p.esqueleto_), barra_(p.barra_), averiada_(p.averiada_) {}
        //Observadores
        int fila() const {return fila_;}
        int col() const {return col_;}
        int filaobj() const {return filaobj_;}
        int colobj() const {return colobj_;}
        bool infinito() const {return infinito_;}
        bool actualizada() const {return actualizada_;}
        const barra* barr() const {return barra_;}
        bool averiada() const {return averiada_;}
        int tipo() const {return tipo_;}
        //Fin observadores
        //Modificadores
        int& fila() {return fila_;}
        int& col() {return col_;}
        int& filaobj() {return filaobj_;}
        int& colobj() {return colobj_;}
        bool& infinito() {return infinito_;}
        bool& actualizada() {return actualizada_;}
        bool& averiada() {return averiada_;}
        int& tipo() {return tipo_;}
        //Fin modificadores
        //Otras funciones
        void actualizar(estado& est);
        void spawn(estado& est, esqueleto& skeleton);
        void actualizarBarra(estado& est, barra& bar);
        void anadir_esqueleto(esqueleto& e) {esqueleto_=&e;}
        void anadir_barra(barra& bar) {barra_=&bar;}
        //Fin otras funciones
        //Operador de asignacion
        placa& operator=(const placa& c) {
            tipo_=c.tipo_;
            infinito_=c.infinito_;
            fila_=c.fila_;
            col_=c.col_;
            filaobj_=c.filaobj_;
            colobj_=c.colobj_;
            anadido_=c.anadido_;
            actualizada_=c.actualizada_;
            esqueleto_=c.esqueleto_;
            barra_=c.barra_;
            averiada_=c.averiada_;
            return *this;
        }
        //Fin operador de asignacion
    private:
        int tipo_;  //1 -> spawn; 2 -> barras
        bool infinito_;
        int fila_;
        int col_;
        int filaobj_;
        int colobj_;
        bool anadido_;
        bool actualizada_;
        esqueleto* esqueleto_;
        barra* barra_;
        bool averiada_;
};

class esqueleto {
    public:
        //Constructores
        esqueleto(double vida, int inteligencia=1);
        esqueleto(const esqueleto& s): vida_(s.vida_), fila_(s.fila_), col_(s.col_), objfila_(s.objfila_), objcol_(s.objcol_), bloque_(s.bloque_), existe_(s.existe_), inteligencia_(s.inteligencia_), atacando_(s.atacando_), dir_ataque_(s.dir_ataque_), turnos_sin_atacar_(s.turnos_sin_atacar_), turnos_aturdido_(s.turnos_aturdido_), exito_(s.exito_), mov_anterior_(s.mov_anterior_), atrapado_(s.atrapado_) {}
        //Fin constructores
        //Operador
        esqueleto& operator=(const esqueleto& s);
        //Fin operador
        //Observadores
        double vida() const {return vida_;}
        int fila() const {return fila_;}
        int col() const {return col_;}
        int objfila() const {return objfila_;}
        int objcol() const {return objcol_;}
        bool existe() const {return existe_;}
        bool atacando() const {return atacando_;}
        bool aturdido() const {return turnos_aturdido_>0;}
        bool exito() const {return exito_;}
        bool atrapado() const {return atrapado_;}
        //Fin observadores
        //Modificadores
        double& vida() {return vida_;}
        int& fila() {return fila_;}
        int& col() {return col_;}
        int& objfila() {return objfila_;}
        int& objcol() {return objcol_;}
        bool& existe() {return existe_;}
        bool& exito() {return exito_;}
        bool& atrapado() {return atrapado_;}
        //Fin modificadores
        //Otras funciones
        void actualizar(estado& est);  //Actualizar estado por referencia
        bool esValido(const estado& est, int fila, int col);
        void atacar(estado& est, int direccion);
        void aturdir() {turnos_aturdido_=4;}    //4 equivale a 3 turnos
        void modificar_vida(double valor);
        void hill_climbing(estado& est);
        int feval(const estado& est, int mov);
        bool repetido(int movimiento, int movimientos[]);
        //Fin otras funciones
    private:
        double vida_;  //50 con vida 300, 51 con vida 200, 52 con vida 100 y 53 con vida 0
        int fila_;
        int col_;
        int objfila_;
        int objcol_;
        int bloque_;
        bool existe_;
        int inteligencia_;
        bool atacando_;
        int dir_ataque_;    //{0,1,2,3} -> {arriba, abajo, izquierda, derecha}
        int turnos_sin_atacar_;
        int turnos_aturdido_;
        bool exito_;
        int mov_anterior_;
        bool atrapado_; //No puede moverse pero puede atacar
};

class estado {
    public:
        typedef set<esqueleto*> Esqueletos;
        typedef set<placa*> Placas;
        typedef set<roca*> Rocas;
        //Constructores
        estado(int** matriz, int nfilas, int ncol, double vida=600, int llaves=0, int mana=0): matriz_(new int*[nfilas]), nfilas_(nfilas), ncol_(ncol), vida_(vida), llaves_(llaves), bloque_(1), filaagujero_(-1), colagujero_(-1), rellenaragujero_(false), inmortal_(false), tiempo_(0), cont_invencibilidad_(0), arma_(0), estamina_(6), cambiar_(true), recargar_estamina_(false), estamina_aux_(0), pasar_(false), poder1_(false), filapoder1_(-1), colpoder1_(-1), mana_(mana), objeto_(-1), regen_(0), veneno_(0), turnos_regen_(0), turnos_veneno_(0), gpulsada_(false), g_contador_(0), manamax_(2), recogermana_(true), vidagris_(0), powerupon_(true) {
            for(int i=0; i<nfilas; i++) {
                matriz_[i]=new int[ncol];
            }
            for(int i=0; i<nfilas_; i++) {
                for(int j=0; j<ncol_; j++) {
                    matriz_[i][j]=matriz[i][j];
                    if(matriz_[i][j]==0) {
                        fila_=i;
                        col_=j;
                        filaant_=fila_;
                        colaant_=col_;
                    }
                    if(matriz_[i][j]==5) {
                        objfila_=i;
                        objcol_=j;
                    }
                }
            }
        }
        estado(const estado& nuevo): matriz_(new int*[nuevo.nfilas_]), fila_(nuevo.fila_), col_(nuevo.col_), filaant_(nuevo.filaant_), colaant_(nuevo.colaant_), nfilas_(nuevo.nfilas_), ncol_(nuevo.ncol_), objfila_(nuevo.objfila_), objcol_(nuevo.objcol_), vida_(nuevo.vida_), llaves_(nuevo.llaves_), bloque_(nuevo.bloque_), filaagujero_(nuevo.filaagujero_), colagujero_(nuevo.colagujero_), rellenaragujero_(nuevo.rellenaragujero_), inmortal_(nuevo.inmortal_), tiempo_(nuevo.tiempo_), cont_invencibilidad_(nuevo.cont_invencibilidad_), arma_(nuevo.arma_), esqueletos(nuevo.esqueletos), placas(nuevo.placas), rocas(nuevo.rocas), estamina_(nuevo.estamina_), cambiar_(nuevo.cambiar_), recargar_estamina_(nuevo.recargar_estamina_), estamina_aux_(nuevo.estamina_aux_), pasar_(nuevo.pasar_), poder1_(nuevo.poder1_), filapoder1_(nuevo.filapoder1_), colpoder1_(nuevo.colpoder1_), mana_(nuevo.mana_), objeto_(nuevo.objeto_), regen_(nuevo.regen_), veneno_(nuevo.veneno_), turnos_regen_(nuevo.turnos_regen_), turnos_veneno_(nuevo.turnos_veneno_), gpulsada_(nuevo.gpulsada_), g_contador_(nuevo.g_contador_), manamax_(nuevo.manamax_), recogermana_(nuevo.recogermana_), vidagris_(nuevo.vidagris_), powerupon_(nuevo.powerupon_) {
            for(int i=0; i<nfilas_; i++) {
                matriz_[i]=new int[ncol_];
            }
            for(int i=0; i<nfilas_; i++) {
                for(int j=0; j<ncol_; j++) {
                    matriz_[i][j]=nuevo.matriz_[i][j];
                }
            }
        }
        //Fin constructores
        //Operador
        estado& operator=(const estado& est);
        //Fin operador
        //Observadores
        int filas() const {return nfilas_;}
        int cols() const {return ncol_;}
        int fila() const {return fila_;}
        int col() const {return col_;}
        int filaant() const {return filaant_;}
        int colaant() const {return colaant_;}
        int objfila() const {return objfila_;}
        int objcol() const {return objcol_;}
        int bloque(int fila, int col) const {return matriz_[fila][col];}
        double vida() const {return vida_;}
        int llaves() const {return llaves_;}
        int anillo() const;
        int bloque() const {return bloque_;}
        int filaagujero() const {return filaagujero_;}
        int colagujero() const {return colagujero_;}
        bool rellenaragujero() const {return rellenaragujero_;}
        bool inmortal() const {return inmortal_;}
        int tiempo() const {return tiempo_;}
        int cont_invencibilidad() const {return cont_invencibilidad_;}
        int arma() const {return arma_;}
        int estamina() const {return estamina_;}
        bool cambiar() const {return cambiar_;}
        bool recargar_estamina() const {return recargar_estamina_;}
        int estamina_aux() const {return estamina_aux_;}
        const Placas& placas_obs() const {return placas;}
        const Esqueletos& esqueletos_obs() const {return esqueletos;}
        const Rocas& rocas_obs() const {return rocas;}
        bool pasar() const {return pasar_;}
        bool poder1() const {return poder1_;}
        int filapoder1() const {return filapoder1_;}
        int colpoder1() const {return colpoder1_;}
        int mana() const {return mana_;}
        int objeto() const {return objeto_;}
        int regen() const {return regen_;}
        int veneno() const {return veneno_;}
        int turnos_regen() const {return turnos_regen_;}
        int turnos_veneno() const {return turnos_veneno_;}
        bool gpulsada() const {return gpulsada_;}
        int g_contador() const {return g_contador_;}
        int manamax() const {return manamax_;}
        bool recogermana() const {return recogermana_;}
        double vidagris() const {return vidagris_;}
        bool powerupon() const {return powerupon_;}
        //Fin observadores
        //Modificadores
        int& fila() {return fila_;}
        int& col() {return col_;}
        int& filaant() {return filaant_;}
        int& colaant() {return colaant_;}
        int& bloque(int fila, int col) {return matriz_[fila][col];}
        double& vida() {return vida_;}
        int& llaves() {return llaves_;}
        int& bloque() {return bloque_;}
        int& filaagujero() {return filaagujero_;}
        int& colagujero() {return colagujero_;}
        bool& rellenaragujero() {return rellenaragujero_;}
        bool& inmortal() {return inmortal_;}
        int& tiempo() {return tiempo_;}
        int& cont_invencibilidad() {return cont_invencibilidad_;}
        int& arma() {return arma_;}
        int& estamina() {return estamina_;}
        bool& cambiar() {return cambiar_;}
        bool& recargar_estamina() {return recargar_estamina_;}
        int& estamina_aux() {return estamina_aux_;}
        bool& pasar() {return pasar_;}
        bool& poder1() {return poder1_;}
        int& filapoder1() {return filapoder1_;}
        int& colpoder1() {return colpoder1_;}
        int& mana() {return mana_;}
        int& objeto() {return objeto_;}
        int& regen() {return regen_;}
        int& veneno() {return veneno_;}
        int& turnos_regen() {return turnos_regen_;}
        int& turnos_veneno() {return turnos_veneno_;}
        bool& gpulsada() {return gpulsada_;}
        int& g_contador() {return g_contador_;}
        int& manamax() {return manamax_;}
        bool& recogermana() {return recogermana_;}
        double& vidagris() {return vidagris_;}
        bool& powerupon() {return powerupon_;}
        //Fin modificadores
        //Otras funciones
        bool puedoGenerarRoca(int fila, int col) const;
        void generarRoca(int direccion, int fila, int col, bool primera_roca=false); //Generar roca a partir de unas coordenadas
        void powerUp(int poder, bool& consumir_turno, int direccion=0);    //1: punto
        bool puedoColocarPunto() const;
        bool puedoTeletransportarme() const;
        void anadir(const esqueleto& skeleton, int fila, int col);
        void anadir(placa& presion, esqueleto& skeleton, int fila, int col, bool infinito=false);
        void anadirBarra(placa& presion, bool subida, int fila, int col);
        void modificar_vida(double valor, bool veneno=false);
        void actualizarEsqueletos();
        void actualizarPlacas();
        void actualizarRocas();
        bool puedoatacarEsqueleto(int fila, int col) const;
        bool puedoaturdirEsqueleto(int fila, int col) const;
        void aturdirEsqueleto(int fila, int col);
        void atacarEsqueleto(int fila, int col);
        void eliminarEsqueleto(const esqueleto& skeleton);
        void eliminarRoca(const roca& rock);
        void aplicarVidaGris();
        void mostrarEsqueletos() const {
            if(esqueletos.empty()) {
                std::cout << "No hay ningun esqueleto" << std::endl;
            }
            else {
                for(Esqueletos::iterator it=esqueletos.begin(); it!=esqueletos.end(); it++) {
                    cout << "Esqueleto con coordenadas " << (*it)->fila() << " " << (*it)->col() << endl;
                }
            }
        }
        void mostrarRocas() const {
            if(rocas.empty()) {
                std::cout << "No hay ninguna roca" << std::endl;
            }
            else {
                for(Rocas::iterator it=rocas.begin(); it!=rocas.end(); it++) {
                    cout << "Roca con coordenadas " << (*it)->fila() << " " << (*it)->col() << " y objeto " << (*it)->objeto() << endl;
                }
            }
        }
        //Fin otras funciones
    private:
        int** matriz_;
        int fila_;
        int col_;
        int filaant_;
        int colaant_;
        int nfilas_;
        int ncol_;
        int objfila_;
        int objcol_;
        double vida_;
        int llaves_;
        int bloque_;
        int filaagujero_;
        int colagujero_;
        bool rellenaragujero_;
        bool inmortal_;
        int tiempo_;
        int cont_invencibilidad_;  //Este sirve para la invencibilidad
        int arma_;                 //{0,1,2} -> {nada, espada, escudo}
        Esqueletos esqueletos;
        Placas placas;
        Rocas rocas;
        int estamina_;  //Número del 1 al 6
        bool cambiar_;
        bool recargar_estamina_;
        int estamina_aux_;
        bool pasar_;
        bool poder1_;
        int filapoder1_;
        int colpoder1_;
        int mana_;
        int objeto_;    //Objeto que guarda una bola cuando lo pisa
        int regen_;     //1, 2
        int veneno_;    //1, 2
        int turnos_regen_;
        int turnos_veneno_;
        bool gpulsada_;
        int g_contador_;
        int manamax_;
        bool recogermana_;
        double vidagris_;
        bool powerupon_;
};

class barra {
    public:
        barra(int fila, int col, bool subida): fila_(fila), col_(col), subida_(subida) {}
        barra(const barra& bar): fila_(bar.fila_), col_(bar.col_), subida_(bar.subida_) {}
        //Observadores
        int fila() const {return fila_;}
        int col() const {return col_;}
        bool subida() const {return subida_;}
        //Fin observadores
        //Modificadores
        int& fila() {return fila_;}
        int& col() {return col_;}
        bool& subida() {return subida_;}
        //Fin modificadores
        //Operador de asignacion
        barra& operator=(const barra& bar) {
            fila_=bar.fila_;
            col_=bar.col_;
            subida_=bar.subida_;
            return *this;
        }
        //Fin operador de asignacion
    private:
        int fila_;
        int col_;
        bool subida_;
};

/*class proyectil {
    public:
        proyectil(int maxticks, int direccion): fila_(0), col_(0), ticks_(0), maxticks_(maxticks), dir_(direccion) {}
        void avanzar(estado& est);
        int dir() const {return dir_;}
    private:
        int fila_;
        int col_;
        int ticks_;
        int maxticks_;
        int dir_;
};*/












