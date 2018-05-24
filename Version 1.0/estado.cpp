#include "estado.hpp"
const int MAXVIDA=1000;

//ESTADO
bool operator ==(const estado& est1, const estado& est2) {
    if(est1.cols()!=est2.cols() || est1.filas()!=est2.filas()) {
        return false;
    }
    for(int i=0; i<est1.filas(); i++) {
        for(int j=0; j<est1.cols(); j++) {
            if(est1.bloque(i,j)!=est2.bloque(i,j)) {
                return false;
            }
        }
    }
    return true;
}

bool operator !=(const estado& est1, const estado& est2) {
    return !(est1==est2);
}

estado& estado::operator=(const estado& est) {
    delete[] matriz_;
    matriz_=new int*[est.nfilas_];
    fila_=est.fila_;
    col_=est.col_;
    filaant_=est.filaant_;
    colaant_=est.colaant_;
    nfilas_=est.nfilas_;
    ncol_=est.ncol_;
    objfila_=est.objfila_;
    objcol_=est.objcol_;
    vida_=est.vida_;
    llaves_=est.llaves_;
    bloque_=est.bloque_;
    filaagujero_=est.filaagujero_;
    colagujero_=est.colagujero_;
    rellenaragujero_=est.rellenaragujero_;
    inmortal_=est.inmortal_;
    tiempo_=est.tiempo_;
    cont_invencibilidad_=est.cont_invencibilidad_;
    arma_=est.arma_;
    esqueletos=est.esqueletos;
    placas=est.placas;
    rocas=est.rocas;
    estamina_=est.estamina_;
    cambiar_=est.cambiar_;
    recargar_estamina_=est.recargar_estamina_;
    estamina_aux_=est.estamina_aux_;
    pasar_=est.pasar_;
    poder1_=est.poder1_;
    filapoder1_=est.filapoder1_;
    colpoder1_=est.colpoder1_;
    mana_=est.mana_;
    objeto_=est.objeto_;
    regen_=est.regen_;
    veneno_=est.veneno_;
    turnos_regen_=est.turnos_regen_;
    turnos_veneno_=est.turnos_veneno_;
    gpulsada_=est.gpulsada_;
    g_contador_=est.g_contador_;
    manamax_=est.manamax_;
    recogermana_=est.recogermana_;
    vidagris_=est.vidagris_;
    powerupon_=est.powerupon_;
    for(int i=0; i<nfilas_; i++) {
        matriz_[i]=new int[ncol_];
    }
    for(int i=0; i<nfilas_; i++) {
        for(int j=0; j<ncol_; j++) {
            matriz_[i][j]=est.matriz_[i][j];
        }
    }
    return *this;
}

int estado::anillo() const {
    //Diseñado para niveles cuadrados
    int extra=1;
    if(fila_==0 || col_==0 || fila_==(nfilas_-1) || col_==(ncol_-1)) {
        return 0;
    }
    for(int i=0; i<(nfilas_/2)+1; i++) {
        if((fila_==extra && col_<(ncol_-extra) && col_>(extra-1)) || (fila_==(nfilas_-(extra+1)) && col_<(ncol_-extra) && col_>(extra-1)) || (col_==extra && fila_<(nfilas_-extra) && fila_>(extra-1)) || (col_==(ncol_-(extra+1)) && fila_<(nfilas_-extra) && fila_>(extra-1))) {
            return extra;
        }
        extra++;
    }
    return 0;
}

//Otras funciones
bool estado::puedoColocarPunto() const {        //Puedo colocar punto si no hay rejas
    bool puedo=true;
    if(!placas.empty()) {
        for(Placas::iterator it=placas.begin(); it!=placas.end(); it++) {
            if((*it)->tipo()==2) {
                if((*it)->barr()->fila()==fila_ && (*it)->barr()->col()==col_) {
                    puedo=false;
                }
            }
        }
    }
    return puedo;
}

bool estado::puedoTeletransportarme() const {   //Puedo teletransportarme si no hay esqueletos ni bolas etc
    bool puedo=true;
    if(!esqueletos.empty()) {
        for(Esqueletos::iterator it=esqueletos.begin(); it!=esqueletos.end(); it++) {
            if((*it)->fila()==filapoder1_ && (*it)->col()==colpoder1_) {
                puedo=false;
            }
        }
    }
    switch(matriz_[filapoder1_][colpoder1_]) {
        case 10:
        case 7:
        case 18:
        case 19:
        case 20:
        case 21:
        case 11: puedo=false;
    }
    return puedo;
}

bool estado::puedoGenerarRoca(int fila, int col) const {
    bool puedo=false;
    //Controlar bordes del mapa
    if(fila<0 || fila>=nfilas_ || col<0 || col>=ncol_) {return false;}
    //Controlar objetos que puedo aplastar
    switch(matriz_[fila][col]) {
        case 2:
        case 3:
        case 4:
        case 7:
        case 8: //Para la llave, la cogerá y luego la soltará
        case 9: //Para la curación, lo mismo
        case 10:
        case 11:
        case 12:
        case 13:
        case 15:
        case 23:
        case 22:
        case 24:
        case 25:
        case 26:
        case 53:
        //Colocar encima de cualquier esqueleto
        case 50:
        case 51:
        case 52:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 1: puedo=true;
    }
    return puedo;
}

void estado::generarRoca(int direccion, int fila, int col, bool primera_roca) {
    roca *rock;
    switch(direccion) {
        case 1: --fila;
                rock=new roca(fila, col, direccion, primera_roca);
                switch(matriz_[fila][col]) {
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 24:
                    case 26: rock->objeto()=matriz_[fila][col]; break;
                }
                matriz_[fila][col]=18;
                break;
        case 2: ++fila;
                rock=new roca(fila, col, direccion, primera_roca);
                switch(matriz_[fila][col]) {
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 24:
                    case 26: rock->objeto()=matriz_[fila][col]; break;
                }
                matriz_[fila][col]=19;
                break;
        case 3: --col;
                rock=new roca(fila, col, direccion, primera_roca);
                switch(matriz_[fila][col]) {
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 24:
                    case 26: rock->objeto()=matriz_[fila][col]; break;
                }
                matriz_[fila][col]=20;
                break;
        case 4: ++col;
                rock=new roca(fila, col, direccion, primera_roca);
                switch(matriz_[fila][col]) {
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 24:
                    case 26: rock->objeto()=matriz_[fila][col]; break;
                }
                matriz_[fila][col]=21;
                break;
    }
    //Se ha generado una roca en las coordenadas; fila, col. Comprobar si golpearía a algún esqueleto o a alguna placa de presión
    if(!esqueletos.empty()) {
        Esqueletos::iterator sol;
        bool encontrado=false;
        for(Esqueletos::iterator it=esqueletos.begin(); it!=esqueletos.end(); it++) {
            if((*it)->fila()==fila && (*it)->col()==col) {
                sol=it;
                encontrado=true;
            }
        }
        if(encontrado) {
            (*sol)->atrapado()=true;
        }
    }
    if(!placas.empty()) {
        Placas::iterator sol;
        bool encontrado=false;
        for(Placas::iterator it=placas.begin(); it!=placas.end(); it++) {
            if((*it)->fila()==fila && (*it)->col()==col) {
                sol=it;
                encontrado=true;
            }
        }
        if(encontrado) {
            (*sol)->averiada()=true;
        }
    }
    rocas.insert(rock);
}

void estado::actualizarRocas() {
    int direccion=-1;
    int fila=-1;
    int col=-1;
    stack<int> direcciones;
    stack<int> filas;
    stack<int> cols;
    stack<int> filas_eliminar;
    stack<int> cols_eliminar;
    roca* roca_eliminar=new roca(-1, -1, -1);
    if(!rocas.empty()) {
        for(Rocas::iterator it=rocas.begin(); it!=rocas.end(); it++) {
            (*it)->actualizar(*this, direccion, fila, col, *roca_eliminar);
            if(roca_eliminar->fila()!=-1 && roca_eliminar->col()!=-1 && roca_eliminar->direccion()!=-1) {
                //Añadir estos datos a una pila para eliminar con posterioridad
                filas_eliminar.push(roca_eliminar->fila());
                cols_eliminar.push(roca_eliminar->col());
            }
            if(direccion!=-1 && fila!=-1 && col!=-1) {
                //Añadir estos datos a una pila para actualizar con posterioridad
                direcciones.push(direccion);
                filas.push(fila);
                cols.push(col);
            }
        }
    }
    if(!filas_eliminar.empty() && !cols_eliminar.empty()) {
        while(!filas_eliminar.empty()) {
            int fila=filas_eliminar.top();
            int col=cols_eliminar.top();
            for(Rocas::iterator it=rocas.begin(); it!=rocas.end(); it++) {
                if((*it)->fila()==fila && (*it)->col()==col) {
                    rocas.erase(it);
                }
            }
            filas_eliminar.pop();
            cols_eliminar.pop();
        }
    }
    if(!direcciones.empty() && !filas.empty() && !cols.empty()) {
        while(!direcciones.empty()) {
            direccion=direcciones.top();
            fila=filas.top();
            col=cols.top();
            int fila2=fila;
            int col2=col;
            switch(direccion) {
                case 1: --fila2; break;
                case 2: ++fila2; break;
                case 3: --col2; break;
                case 4: ++col2; break;
            }
            if(puedoGenerarRoca(fila2, col2)) {
                generarRoca(direccion, fila, col);
            }
            direcciones.pop();
            filas.pop();
            cols.pop();
        }
    }
}

void roca::actualizar(estado& est, int& direccion, int& fila, int& col, roca& roca_eliminar) {
    if(primera_roca_) {
        //No hacer nada
        primera_roca_=false;
        return;
    }
    ++tiempo_;
    roca_eliminar.fila()=-1;
    roca_eliminar.col()=-1;
    roca_eliminar.direccion()=-1;
    if(tiempo_==tiempo_limite_) {
        //Soltar objetos (en caso de tenerlos) y autodestruirse
        if(objeto_!=-1) {
            est.bloque(fila_, col_)=objeto_; //Dejar objeto
        }
        else {
            if(est.bloque(fila_, col_)!=0) {
                est.bloque(fila_, col_)=22; //Dejar polvo
            }
        }
        roca_eliminar=*this;
    } else {
        if(pivote_) {   //Dejaré de ser pivote y generaré otra roca
            pivote_=false;
            direccion=direccion_;
            fila=fila_;
            col=col_;   //Mandar desde dentro a generar rocas extra
        }
    }
}

void estado::eliminarRoca(const roca& rock) {
    Rocas::iterator sol;
    for(Rocas::iterator it=rocas.begin(); it!=rocas.end(); it++) {
        if((*it)->fila()==rock.fila() && (*it)->col()==rock.col()) {
            sol=it;
        }
    }
    rocas.erase(sol);  //Borrar SOLO ese elemento
}

void estado::aplicarVidaGris() {
    double cantidad=50;
    if(vida_>50) {
        cantidad=vida_/2;
    }
    modificar_vida(vida_-cantidad);
    vidagris_=cantidad;
    estamina_=6;
    recargar_estamina_=false;
    cambiar_=true;
    estamina_aux_=0;
}

void estado::powerUp(int poder, bool& consumir_turno, int direccion) {
    int fila;
    int col;
    switch(poder) {
        case 1:
            //Comprobar si puedo colocar punto
            if(poder1_) {
                if(puedoTeletransportarme()) {
                    //Si estoy en la misma posición, me devuelve el maná y no avanzo turnos
                    if(fila_==filapoder1_ && col_==colpoder1_) {
                        poder1_=false;
                        consumir_turno=false;
                        ++mana_;
                        break;
                    }
                    //Actualizar Vida
                    double penalizacion=50*(abs(fila_-filapoder1_)+abs(col_-colpoder1_));
                    switch(matriz_[filapoder1_][colpoder1_]) {  //La penalización aumenta si hay un bloque de daño
                        case 2: penalizacion+=100; break;
                        case 3: penalizacion+=200; break;
                        case 4: penalizacion+=300; break;
                    }
                    modificar_vida(vida_-penalizacion);
                    //Recoger objetos(llave, mana,..)
                    if(matriz_[filapoder1_][colpoder1_]==8) {
                        ++llaves_;
                    }
                    if(matriz_[filapoder1_][colpoder1_]==26) {
                        if(mana_<manamax_) {
                            recogermana_=true;
                        }
                        else {
                            recogermana_=false;
                        }
                        if(recogermana_) {++mana_;}
                    }
                    //Teletransporte
                    if(bloque_!=7 && bloque_!=8 && bloque_!=9 && bloque_!=10 && bloque_!=11 && bloque_!=14) {
                        matriz_[fila_][col_]=bloque_;
                    } else {
                        matriz_[fila_][col_]=1;
                    }
                    bloque_=matriz_[filapoder1_][colpoder1_];
                    matriz_[filapoder1_][colpoder1_]=0;
                    fila_=filapoder1_;
                    col_=colpoder1_;
                    filapoder1_=-1;
                    colpoder1_=-1;
                    poder1_=false;
                    powerupon_=false;
                }
                else {
                    consumir_turno=false;
                }
            }
            else{
                if(puedoColocarPunto()) {
                    //Colocar punto
                    filapoder1_=fila_;
                    colpoder1_=col_;
                    consumir_turno=false;
                    poder1_=true;
                    --mana_;
                }
                else {
                    consumir_turno=false;
                }
            } break;
        case 2: //Generar rocas en una dirección
            fila=fila_;
            col=col_;
            switch(direccion) {
                case 1: --fila; break;
                case 2: ++fila; break;
                case 3: --col; break;
                case 4: ++col; break;
            }
            if(puedoGenerarRoca(fila, col)) {
                generarRoca(direccion, fila_, col_, true);
                //--mana_;
            }
            else {
                consumir_turno=false;
            }
            break;
        case 3: //Regenerar mucha vida
            regen_=2;
            turnos_regen_=2;
            consumir_turno=false;
            mana_-=2;
            break;
    }
}

void estado::anadir(const esqueleto& skeleton, int fila, int col) {
    esqueleto* copia=new esqueleto(skeleton);
    esqueletos.insert(copia);
    switch((int)copia->vida()) {
        case 0: matriz_[fila][col]=53; break;
        case 100: matriz_[fila][col]=52; break;
        case 200: matriz_[fila][col]=51; break;
        case 300: matriz_[fila][col]=50; break;
    }
    copia->fila()=fila;
    copia->col()=col;
    copia->objfila()=fila_;
    copia->objcol()=col_;
    copia->existe()=true;
}

void estado::anadir(placa& presion, esqueleto& skeleton, int fila, int col, bool inf) {
    placas.insert(&presion);
    presion.anadir_esqueleto(skeleton);
    matriz_[fila][col]=15;
    presion.fila()=fila;
    presion.col()=col;
    presion.infinito()=inf;
}

void estado::anadirBarra(placa& presion, bool subida, int fila, int col) {
    placas.insert(&presion);
    barra *bar=new barra(presion.filaobj(), presion.colobj(), subida);
    presion.anadir_barra(*bar);
    matriz_[fila][col]=15;
    if(subida) {
        matriz_[presion.filaobj()][presion.colobj()]=16;  //Barra subida
    } else {
        matriz_[presion.filaobj()][presion.colobj()]=17;  //Barra bajada
    }
    presion.fila()=fila;
    presion.col()=col;
}

void estado::modificar_vida(double valor, bool veneno) {
    if(!inmortal_) {
        if(valor<vida_ && vidagris_>0 && !veneno) {
            vidagris_=0;
        }
        vida_=valor;
        if(valor>MAXVIDA) {
            vida_=MAXVIDA;
        }
    }
    else {
        if(valor>vida_) {
            vida_=valor;
            if(valor>MAXVIDA) {
                vida_=MAXVIDA;
            }
        }
    }
}

void estado::actualizarEsqueletos() {
    if(!esqueletos.empty()) {
        for(Esqueletos::iterator it=esqueletos.begin(); it!=esqueletos.end(); it++) {
            (*it)->actualizar(*this);
        }
    }
}

void estado::actualizarPlacas() {
    if(!placas.empty()) {
        for(Placas::iterator it=placas.begin(); it!=placas.end(); it++) {
            (*it)->actualizar(*this);
            //Comprobar si hay barra y no hay nada encima, para actualizar su visualización
            if((*it)->barr()!=nullptr) {
                if(matriz_[(*it)->barr()->fila()][(*it)->barr()->col()]==1 && (*it)->barr()->subida()==false) {
                    matriz_[(*it)->barr()->fila()][(*it)->barr()->col()]=17;
                }
            }
        }
    }
}

bool estado::puedoatacarEsqueleto(int fila, int col) const {
    bool puedo=false;
    if(esqueletos.empty()) {
        return false;
    }
    Esqueletos::iterator sol;
    for(Esqueletos::iterator it=esqueletos.begin(); it!=esqueletos.end(); it++) {
        if((*it)->fila()==fila && (*it)->col()==col) {
            sol=it;
            puedo=true;
        }
    }
    if(puedo) {
        if((*sol)->vida()==0) {
            puedo=false;
        }
    }
    return puedo;
}

bool estado::puedoaturdirEsqueleto(int fila, int col) const {
    bool puedo=false;
    if(esqueletos.empty()) {
        return false;
    }
    Esqueletos::iterator sol;
    for(Esqueletos::iterator it=esqueletos.begin(); it!=esqueletos.end(); it++) {
        if((*it)->fila()==fila && (*it)->col()==col) {
            sol=it;
            puedo=true;
        }
    }
    if(puedo) {
        if((*sol)->aturdido() || !(*sol)->atacando() || (*sol)->vida()==0) {
            puedo=false;
        }
    }
    return puedo;
}

void estado::aturdirEsqueleto(int fila, int col) {
    //Se supone que existe un esqueleto en la posicion fila, col
    Esqueletos::iterator sol;
    for(Esqueletos::iterator it=esqueletos.begin(); it!=esqueletos.end(); it++) {
        if((*it)->fila()==fila && (*it)->col()==col) {
            sol=it;
        }
    }
    //sol es el iterador que controla a nuestro esqueleto víctima
    (*sol)->aturdir();
    //Modificar estamina
    estamina_-=2;
    if(estamina_<0) estamina_=0;
}

void estado::atacarEsqueleto(int fila, int col) {
    //Se supone que existe un esqueleto en la posicion fila, col
    Esqueletos::iterator sol;
    for(Esqueletos::iterator it=esqueletos.begin(); it!=esqueletos.end(); it++) {
        if((*it)->fila()==fila && (*it)->col()==col) {
            sol=it;
        }
    }
    //sol es el iterador que controla a nuestro esqueleto víctima
    (*sol)->modificar_vida((*sol)->vida()-100);
    //Modificar estamina
    estamina_-=2;
    if(estamina_<0) estamina_=0;
}

void estado::eliminarEsqueleto(const esqueleto& skeleton) { //Programar acción al matar esqueleto aqui
    Esqueletos::iterator sol;
    for(Esqueletos::iterator it=esqueletos.begin(); it!=esqueletos.end(); it++) {
        if((*it)->fila()==skeleton.fila() && (*it)->col()==skeleton.col()) {
            sol=it;
        }
    }
    esqueletos.erase(sol);
}
//Fin otras funciones


//ESQUELETO
//Constructores
esqueleto::esqueleto(double vida, int inteligencia): vida_(vida), fila_(-1), col_(-1), objfila_(-1), objcol_(-1), bloque_(1), existe_(false), inteligencia_(inteligencia), atacando_(false), dir_ataque_(-1), turnos_sin_atacar_(0), turnos_aturdido_(0), exito_(false), mov_anterior_(0), atrapado_(false) {}
//Fin constructores

//Operadores
esqueleto& esqueleto::operator=(const esqueleto& s) {
    vida_=s.vida_;
    fila_=s.fila_;
    col_=s.col_;
    objfila_=s.objfila_;
    objcol_=s.objcol_;
    bloque_=s.bloque_;
    existe_=s.existe_;
    inteligencia_=s.inteligencia_;
    atacando_=s.atacando_;
    dir_ataque_=s.dir_ataque_;
    turnos_sin_atacar_=s.turnos_sin_atacar_;
    turnos_aturdido_=s.turnos_aturdido_;
    exito_=s.exito_;
    mov_anterior_=s.mov_anterior_;
    atrapado_=s.atrapado_;
    return *this;
}
//Fin operadores

int esqueleto::feval(const estado& est, int mov) {
    //Devuelve la distancia desde el esqueleto hasta el personaje
    int fila=fila_;
    int col=col_;
    switch(mov) {
        case 1: fila--; break;
        case 2: fila++; break;
        case 3: col--; break;
        case 4: col++; break;
    }
    return abs(est.fila()-fila)+abs(est.col()-col);
}

bool esqueleto::repetido(int movimiento, int movimientos[]) {
    bool sol=false;
    switch(movimiento) {
        case 0: sol=false; break;
        case 1: sol=(mov_anterior_==2); break;
        case 2: sol=(mov_anterior_==1); break;
        case 3: sol=(mov_anterior_==4); break;
        case 4: sol=(mov_anterior_==3); break;
    }
    //Comprobar si este movimiento es el único que puede hacer. Si es así, devuelve false
    int cont=0;
    for(int i=0; i<4; i++) {
        if(movimientos[i]!=0) {
            cont++;
        }
    }
    if(cont==1) {sol=false;}
    return sol;
}

void esqueleto::hill_climbing(estado& est) {
    //Si la distancia es de 1, no hacer nada
    if((abs(est.fila()-fila_)+abs(est.col()-col_))==1 || atrapado_) {
        //Quedarse en el mismo sitio
        switch((int)vida_) {
            case 0: est.bloque(fila_, col_)=53; break;
            case 100: est.bloque(fila_, col_)=52; break;
            case 200: est.bloque(fila_, col_)=51; break;
            case 300: est.bloque(fila_, col_)=50; break;
        }
        return;
    }
	//Escoger movimientos válidos y almacenarlos en un vector
	int cont=0;
	int movimientos[]={0,0,0,0};
	int empate[]={0,0,0,0};
	int contempate=0;
	for(int mov=1; mov<5; mov++) {
		int fila=fila_;
		int col=col_;
		switch(mov) {
			case 1:	fila--; break; //Arriba
			case 2:	fila++; break; //Abajo
			case 3: col--; break; //Izquierda
			case 4:	col++; break; //Derecha
		}
		if(esValido(est, fila, col)) {
			movimientos[cont]=mov;
		}
		cont++;
	}
	//De los movimientos válidos, escoger el mejor
	int cont2=0;
	int mejor=0;
	int movimiento=0;
	//Mejor será inicialmente el primer movimiento válido
	for(int i=0; i<4; i++) {
        if(movimientos[i]!=0 && !repetido(movimientos[i], movimientos)) {
            mejor=feval(est, movimientos[i]);
            movimiento=movimientos[i];
            break;
        }
        else {
            cont2++;
        }
	}
	if(cont2==4) {
        //Quedarse en el mismo sitio
        switch((int)vida_) {
            case 0: est.bloque(fila_, col_)=53; break;
            case 100: est.bloque(fila_, col_)=52; break;
            case 200: est.bloque(fila_, col_)=51; break;
            case 300: est.bloque(fila_, col_)=50; break;
        }
        return;
	}  //No puede realizar ningún movimiento
	//Actualizar mejor
    for(int i=0; i<4; i++) {
        if(movimientos[i]!=0 && !repetido(movimientos[i], movimientos)) {
            if(feval(est, movimientos[i])==mejor) {
                //Añadir al vector de empate
                empate[contempate]=movimientos[i];
                contempate++;
            }
            if(feval(est, movimientos[i])<mejor) {
                mejor=feval(est, movimientos[i]);
                movimiento=movimientos[i];
                //Romper vector de empate
                empate[0]=movimientos[i]; empate[1]=0; empate[2]=0; empate[3]=0;
                contempate=1;
            }
        }
    }
    //Si hay más de un elemento en el vector de empate, "movimiento" se sortea entre los posibles en el vector
    if(contempate>1) {
        int num=rand()%contempate;
        movimiento=empate[num];
    }
	mov_anterior_=movimiento;
	//Realizar el movimiento
	int filaantesq=fila_;
    int colantesq=col_;
	switch(movimiento) {
        case 1: fila_--; break;
        case 2: fila_++; break;
        case 3: col_--; break;
        case 4: col_++; break;
	}
    //Guardar bloque al que va a mover el esqueleto
    int antbloque=bloque_;
    bloque_=est.bloque(fila_, col_);
    //Actualizar esqueleto en la matriz
    switch((int)vida_) {
        case 0: est.bloque(fila_, col_)=53; break;
        case 100: est.bloque(fila_, col_)=52; break;
        case 200: est.bloque(fila_, col_)=51; break;
        case 300: est.bloque(fila_, col_)=50; break;
    }
    switch(antbloque) { //En caso de que los esqueletos puedan eliminar algún bloque, añadir case bloque
        default: est.bloque(filaantesq, colantesq)=antbloque; break;
    }
}

void esqueleto::actualizar(estado& est) {
    if(vida_==0) {
        existe_=false;
        if(bloque_==1) {
            est.bloque(fila_, col_)=53; //Colocar cadáver solo si el esqueleto no tiene ningún objeto
        }
        else {
            est.bloque(fila_, col_)=bloque_;
        }
        //Spawnear maná con cierta probabilidad(60%)
        srand(time(NULL));
        int aleatorio=rand()%3;
        if(aleatorio<2) {
            est.bloque(fila_, col_)=26;
        }
        //
        est.eliminarEsqueleto(*this);
        return;
    }
    if(turnos_aturdido_>0) {
        switch((int)vida_) {
            case 100: est.bloque(fila_, col_)=63; break;
            case 200: est.bloque(fila_, col_)=62; break;
            case 300: est.bloque(fila_, col_)=61; break;
        }
        turnos_aturdido_--;
        atacando_=false;
        return;
    }
    if(atacando_) {
        switch((int)vida_) {
            case 100: est.bloque(fila_, col_)=59; break;
            case 200: est.bloque(fila_, col_)=57; break;
            case 300: est.bloque(fila_, col_)=54; break;
        }
        //Atacar en la direccion de ataque
        atacar(est, dir_ataque_);
        atacando_=false;
        turnos_sin_atacar_=2;
        return;
    }
    int num = rand()%2; //Numero que decidira si mueve en el eje x o y (número entre 0 y (2-1))
    if(inteligencia_==1) {
        objfila_=est.filaant();
        objcol_=est.colaant();
    }
    if(inteligencia_==2 || inteligencia_==4) {
        objfila_=est.fila();
        objcol_=est.col();
    }
    if(inteligencia_==3 && exito_) {
        //Quedarse en el sitio
        switch((int)vida_) {
            case 0: est.bloque(fila_, col_)=53; break;
            case 100: est.bloque(fila_, col_)=52; break;
            case 200: est.bloque(fila_, col_)=51; break;
            case 300: est.bloque(fila_, col_)=50; break;
        }
    }
    if(inteligencia_==3 && !exito_) {
        //objfila_, objcol_ serán las coordenadas de la placa más cercana
        //Analizar primero si encuentran alguna placa, empezando desde su posición
        set<placa*> placas=est.placas_obs();
        if(placas.empty()) {
            //Atacar al jugador
            objfila_=est.fila();
            objcol_=est.col();
            inteligencia_=2;
        }
        else {
            set<placa*>::iterator it=placas.begin();
            int mindist=abs((*it)->fila()-fila_)+abs((*it)->col()-col_);
            int dist=1;
            int actualizadas=0;
            int cont=0;
            for(set<placa*>::iterator it=placas.begin(); it!=placas.end(); it++) {
                if((est.fila()!=(*it)->fila() || est.col()!=(*it)->col()) && est.bloque((*it)->fila(), (*it)->col())!=50 && est.bloque((*it)->fila(), (*it)->col())!=51 && est.bloque((*it)->fila(), (*it)->col())!=52 && est.bloque((*it)->fila(), (*it)->col())!=54 && est.bloque((*it)->fila(), (*it)->col())!=56 && est.bloque((*it)->fila(), (*it)->col())!=57 && est.bloque((*it)->fila(), (*it)->col())!=58 && est.bloque((*it)->fila(), (*it)->col())!=59 && est.bloque((*it)->fila(), (*it)->col())!=60 && est.bloque((*it)->fila(), (*it)->col())!=61 && est.bloque((*it)->fila(), (*it)->col())!=62 && est.bloque((*it)->fila(), (*it)->col())!=63 && est.bloque((*it)->fila(), (*it)->col())!=10) { //La placa no se actualiza hasta después, luego habrá que cambiar la comprobación (!(*it)->actualizada())
                    cout << "Placa con coordenadas " << (*it)->fila() << " " << (*it)->col() << endl;
                    //Medir distancia del esqueleto a esa placa
                    dist=abs((*it)->fila()-fila_)+abs((*it)->col()-col_);
                    cout << "Distancia con esta placa: " << dist << endl;
                    if(dist<=mindist) {
                        mindist=dist;
                        objfila_=(*it)->fila();
                        objcol_=(*it)->col();
                    }
                } else {actualizadas++;}
                cont++;
            }
            if(actualizadas==cont) {    //Se vuelve agresivo si no tiene placa a la que acceder (todas están ocupadas)
                //Atacar al jugador
                objfila_=est.fila();
                objcol_=est.col();
                inteligencia_=2;
            }
        }
    }
    if(inteligencia_==4) {
        hill_climbing(est);
    }
    if(inteligencia_!=4) {
        int filaantesq=fila_;
        int colantesq=col_;
        int fila2=fila_;
        int col2=col_;
        //Moverse
        if(fila_<objfila_ && col_<objcol_) {
            if(num==1) {
                fila2++;
                if(!esValido(est, fila2, col2)) {fila2--; col2++;}
            }
            else {
                col2++;
                if(!esValido(est, fila2, col2)) {col2--; fila2++;}
            }
        }
        if(fila_>objfila_ && col_>objcol_) {
            if(num==1) {
                fila2--;
                if(!esValido(est, fila2, col2)) {fila2++; col2--;}
            }
            else {
                col2--;
                if(!esValido(est, fila2, col2)) {col2++; fila2--;}
            }
        }
        if(fila_<objfila_ && col_>objcol_) {
            if(num==1) {
                fila2++;
                if(!esValido(est, fila2, col2)) {fila2--; col2--;}
            }
            else {
                col2--;
                if(!esValido(est, fila2, col2)) {col2++; fila2++;}
            }
        }
        if(fila_>objfila_ && col_<objcol_) {
            if(num==1) {
                fila2--;
                if(!esValido(est, fila2, col2)) {fila2++; col2++;}
            }
            else {
                col2++;
                if(!esValido(est, fila2, col2)) {col2--; fila2--;}
            }
        }
        if(fila_>objfila_ && col_==objcol_) {
            fila2--;
        }
        if(fila_<objfila_ && col_==objcol_) {
            fila2++;
        }
        if(fila_==objfila_ && col_>objcol_) {
            col2--;
        }
        if(fila_==objfila_ && col_<objcol_) {
            col2++;
        }
        //Comprobar que puede moverse
        if(esValido(est, fila2, col2) && !atrapado_) {
            fila_=fila2; col_=col2;
            //Guardar bloque al que va a mover el esqueleto
            int antbloque=bloque_;
            bloque_=est.bloque(fila_, col_);
            //Actualizar esqueleto en la matriz
            switch((int)vida_) {
                case 0: est.bloque(fila_, col_)=53; break;
                case 100: est.bloque(fila_, col_)=52; break;
                case 200: est.bloque(fila_, col_)=51; break;
                case 300: est.bloque(fila_, col_)=50; break;
            }
            switch(antbloque) { //En caso de que los esqueletos puedan eliminar algún bloque, añadir case bloque
                default: est.bloque(filaantesq, colantesq)=antbloque; break;
            }
        }
        else {
            //Quedarse en el mismo sitio
            switch((int)vida_) {
                case 0: est.bloque(fila_, col_)=53; break;
                case 100: est.bloque(fila_, col_)=52; break;
                case 200: est.bloque(fila_, col_)=51; break;
                case 300: est.bloque(fila_, col_)=50; break;
            }
        }
    }
    //Intentar atacar
    if(inteligencia_!=3 && turnos_sin_atacar_==0) {
        //Va a intentar atacar a la fila est.fila() y a la columna est.col()
        if((fila_==est.fila()+1 && col_==est.col()) || (fila_==est.fila()-1 && col_==est.col()) || (col_==est.col()-1 && fila_==est.fila()) || (col_==est.col()+1 && fila_==est.fila())) {
            switch((int)vida_) {
                case 100: est.bloque(fila_, col_)=60; break;
                case 200: est.bloque(fila_, col_)=58; break;
                case 300: est.bloque(fila_, col_)=56; break;
            }
            atacando_=true;
        }
        if(fila_==est.fila()+1 && col_==est.col()) {
            //Ataca arriba
            dir_ataque_=0;
        }
        if(fila_==est.fila()-1 && col_==est.col()) {
            //Ataca abajo
            dir_ataque_=1;
        }
        if(col_==est.col()-1 && fila_==est.fila()) {
            //Ataca derecha
            dir_ataque_=3;
        }
        if(col_==est.col()+1 && fila_==est.fila()) {
            //Ataca izquierda
            dir_ataque_=2;
        }
    }
    if(turnos_sin_atacar_>0) turnos_sin_atacar_--;
}

void esqueleto::atacar(estado& est, int direccion) {
    //Comprobar que el personaje se encuentra en trayectoria
    switch(direccion) {
        case 0: if(est.col()==col_ && est.fila()<fila_ && est.fila()>(fila_-3)) {
                    est.modificar_vida(est.vida()-200);
                } break;
        case 1: if(est.col()==col_ && est.fila()>fila_ && est.fila()<(fila_+3)) {
                    est.modificar_vida(est.vida()-200);
                } break;
        case 2: if(est.fila()==fila_ && est.col()<col_ && est.col()>(col_-3)) {
                    est.modificar_vida(est.vida()-200);
                } break;
        case 3: if(est.fila()==fila_ && est.col()>col_ && est.col()<(col_+3)) {
                    est.modificar_vida(est.vida()-200);
                } break;
    }
}

bool esqueleto::esValido(const estado& est, int fila, int col) {
    bool valido=true;
    if(fila<0 || col<0 || fila>(est.filas()-1) || col>(est.cols()-1)) {return false;}
    switch(est.bloque(fila, col)) {
        case 0:
        case 6:
        case 7:
        case 10:
        case 11:
        case 12:
        case 16:
        case 18:
        case 19:
        case 20:
        case 21:
        case 50:
        case 51:
        case 52:
        case 54:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63: valido=false; break;
    }
    return valido;
}

void esqueleto::modificar_vida(double valor) {
    if(valor<0) {
        vida_=0;
    }
    else {
        vida_=valor;
    }
}

//PLACA

void placa::actualizar(estado& est) {
    if((est.fila()!=fila_ || est.col()!=col_) && est.bloque(fila_, col_)!=50 && est.bloque(fila_, col_)!=51 && est.bloque(fila_, col_)!=52 && est.bloque(fila_, col_)!=54 && est.bloque(fila_, col_)!=56 && est.bloque(fila_, col_)!=57 && est.bloque(fila_, col_)!=58 && est.bloque(fila_, col_)!=59 && est.bloque(fila_, col_)!=60 && est.bloque(fila_, col_)!=61 && est.bloque(fila_, col_)!=62 && est.bloque(fila_, col_)!=63 && est.bloque(fila_, col_)!=10 && est.bloque(fila_, col_)!=26) {    //Se libera la placa
        actualizada_=false;
        if(averiada_) {
            est.bloque(fila_, col_)=23;
        }
        else {
            est.bloque(fila_, col_)=15;
        }
    }
    //Actualizar
    if(!actualizada_ && !averiada_) {
        if((est.fila()==fila_ && est.col()==col_) || est.bloque(fila_, col_)==50 || est.bloque(fila_, col_)==51 || est.bloque(fila_, col_)==52 || est.bloque(fila_, col_)==54 || est.bloque(fila_, col_)==56 || est.bloque(fila_, col_)==57 || est.bloque(fila_, col_)==58 || est.bloque(fila_, col_)==59 || est.bloque(fila_, col_)==60 || est.bloque(fila_, col_)==61 || est.bloque(fila_, col_)==62 || est.bloque(fila_, col_)==63 || est.bloque(fila_, col_)==10) {
            switch(tipo_) {
                case 1: spawn(est, *esqueleto_); break;
                case 2: actualizarBarra(est, *barra_); break;
            }
            actualizada_=true;
        }
    }
    //Comprobar si tiene un esqueleto encima para activar el booleano EXITO
    set<esqueleto*> esqueletos=est.esqueletos_obs();
    if(!esqueletos.empty()) {
        for(set<esqueleto*>::iterator it=esqueletos.begin(); it!=esqueletos.end(); it++) {
            if((*it)->fila()==fila_ && (*it)->col()==col_) {
                (*it)->exito()=true;
            }
        }
    }
}

void placa::spawn(estado& est, esqueleto& skeleton) {
    if(!anadido_){
        est.anadir(skeleton, filaobj_, colobj_);
        if(!infinito_) {
            anadido_=true;
        }
    }
}

void placa::actualizarBarra(estado& est, barra& bar) {
    //La barra de las coordenadas filaobj_, colobj_ va a ser actualizada
    if(bar.subida()) {
        bar.subida()=false;
        est.bloque(bar.fila(), bar.col())=17;
    }
    else {
        if(est.bloque(bar.fila(), bar.col())!=10 && est.bloque(bar.fila(), bar.col())!=50 && est.bloque(bar.fila(), bar.col())!=51 && est.bloque(bar.fila(), bar.col())!=52 && est.bloque(bar.fila(), bar.col())!=54 && est.bloque(bar.fila(), bar.col())!=56 && est.bloque(bar.fila(), bar.col())!=57 && est.bloque(bar.fila(), bar.col())!=58 && est.bloque(bar.fila(), bar.col())!=59 && est.bloque(bar.fila(), bar.col())!=60 && est.bloque(bar.fila(), bar.col())!=61 && est.bloque(bar.fila(), bar.col())!=62 && est.bloque(bar.fila(), bar.col())!=63) { //Si hay un objeto encima encima no hacer nada
            bar.subida()=true;
            est.bloque(bar.fila(), bar.col())=16;
        }
    }
}

/*void esqueleto::disparar(estado& est, proyectil& hueso) {
    switch(hueso.dir()) {
        case 1: est.bloque(fila_-1, col_)=55; break;    //ARRIBA
        case 2: est.bloque(fila_+1, col_)=55; break;    //ABAJO
        case 3: est.bloque(fila_, col_-1)=55; break;    //IZQUIERDA
        case 4: est.bloque(fila_, col_+1)=55; break;  //DERECHA
    }
    //hueso.avanzar(est);

    std::cout << fila_ << " " << col_ << std::endl;
    nuevo.bloque(fila_, col_)=1;//est.bloque(fila_, col_);
    est=nuevo;
}*/

//PROYECTIL
/*void proyectil::avanzar(estado& est) {
    estado nuevo(est);
    if(ticks_>=maxticks_) {return;}
    ++ticks_;
    //Actualizar disparo en la matriz
    switch(dir_) {
        case 1: nuevo.bloque(fila_-ticks_, col_)=55; break;    //ARRIBA
        case 2: nuevo.bloque(fila_+ticks_, col_)=55; break;    //ABAJO
        case 3: nuevo.bloque(fila_, col_-ticks_)=55; break;    //IZQUIERDA
        case 4: nuevo.bloque(fila_, col_+ticks_)=55; break;  //DERECHA
        }
}*/

