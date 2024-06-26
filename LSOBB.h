
#include "Envios.h"
#include <String.h>
#include <math.h>

#ifndef UNTITLED_LSO_H
#define UNTITLED_LSO_H

#endif //UNTITLED_LSO_H

//  float eExMax=0.0, eExMed=0.0, eFrMax=0.0, eFrMed=0.0, aMax=0.0, aMed=0.0, bMax=0.0, bMed=0.0, celCont=0.0;
//   int eExCant=0,eFrCant=0,aCant=0,bCant=0;

char *Mayusculas(char string[]);

typedef struct {
    Envio envios[MAX_Envios];
    int contador;

    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, celCont, tempa, tempb, eExCant, eFrCant
    , aCant, bCant, costo, costoEvoE, costoEvoF, tempe, tempef;
} lsobb;


void initLSOBB(lsobb *lista) {

    lista->eExMax = 0.0;
    lista->eExMed = 0.0;
    lista->eFrMax = 0.0;
    lista->eFrMed = 0.0;
    lista->aMax = 0.0;
    lista->aMed = 0.0;
    lista->bMax = 0.0;
    lista->bMed = 0.0;
    lista->celCont = 0.0;
    lista->eExCant = 0.0;
    lista->eFrCant = 0.0;
    lista->aCant = 0.0;
    lista->bCant = 0.0;
    lista->tempa = 0.0;
    lista->tempb = 0.0;
    lista->tempe = 0.0;
    lista->tempef = 0.0;

}


int LocalizarLSOBB(lsobb *lista, char codigo[], int *pos, int p) {
    float inicio = -1, comparacion = 0;
    int medio = 0;// Limite inferior exclusivo
    float fin = lista->contador;   // Limite superior exclusivo
    //segnmento mas grande a la izq, testigo a la derecha
    lista->costoEvoE = 0.0;
    lista->costoEvoF = 0.0;
    int vector_aux[MAX_Envios + 2], i = 0;
    int bandera = 0;

    float temp = 0.0;
    if (lista->contador == 0) {
        *pos = 0;
        if (p == 0) {
            if (lista->eFrMax < temp) {
                lista->eFrMax = temp;
            }
            lista->eFrCant++;
            lista->costoEvoF += temp;
            lista->tempef += lista->costoEvoF;
            lista->eFrMed = lista->tempef / (lista->eExCant);
        }
        return 0;
    }
    for (i = 0; i < lista->contador; i++) {
        vector_aux[i] = 0;

    }
    if (lista->contador == 0) {
        *pos = 0;
        return 0;
    }
    while (inicio + 1 < fin - 1) {
        temp++;
        medio = ((inicio + fin) / 2) + 1;
        comparacion = strcmp(lista->envios[medio].codigo, codigo);
        vector_aux[i] = medio;
        i++;
        if (comparacion > 0) {
            fin = medio;
        } else {
            inicio = medio - 1;
        }
        if (p == 0) {
            if (vector_aux[medio] == 1) {//while (listatamano>1)
                temp++;
                //Hacer actualizacion de limites y calculos de tests (ok)
                vector_aux[medio] = 1;
            }
        }
    }
    if (p == 0) {
        if (vector_aux[(int) fin - 1] == 0) {//Consultar en lista de tamano 1
            temp++;
        }

    }
    // Posición de inserción si no se encontró el elemento
    if (strcmp(lista->envios[(int) fin - 1].codigo, codigo) == 0) {

        if (p == 0) {

            if (lista->eExMax < temp) {
                lista->eExMax = temp;
            }

            lista->eExCant++;
            lista->costoEvoE += temp;
            lista->tempe += lista->costoEvoE;
            lista->eExMed = lista->tempe / (lista->eExCant);


        }

        *pos = (int) fin - 1;
        return 1; // Elemento encontrado
    } else {
        if (p == 0) {
            if (lista->eFrMax < temp) {
                lista->eFrMax = temp;
            }

            lista->eFrCant++;
            lista->costoEvoF += temp;
            lista->tempef += lista->costoEvoF;
            lista->eFrMed = lista->tempef / (lista->eFrCant);

        }
        if (strcmp((*lista).envios[(int) fin - 1].codigo, codigo) < 0) {
            (*pos) = fin;
        } else {
            (*pos) = fin - 1;
        }


        return 0; // Elemento no encontrado
    }
}

int AltaLSOBB(lsobb *lista, Envio envio) {


    lista->costo = 0.0;
    int pos = 0;

    if (lista->contador == MAX_Envios) {
        return 2; // Lista llena
    }

    if (LocalizarLSOBB(lista, envio.codigo, &pos, 1) == 0) {

        for (int i = lista->contador - 1; i >= pos; i--) {
            lista->costo++; //corrimiento


            lista->envios[i + 1] = lista->envios[i];
        }
        lista->envios[pos] = envio;
        lista->contador++;


        if (lista->costo > lista->aMax) {
            lista->aMax = lista->costo; //maximo
        }
        lista->aCant++; //cantidad de altas

        lista->tempa += lista->costo; //promedio

        lista->aMed = lista->tempa / (lista->aCant);


        return 0;
    } else {

        return 1;
    }
}


int BajaLSOBB(lsobb *lista, Envio envio) {
    lista->costo = 0.0;
    int pos, i;
    int encontrado = LocalizarLSOBB(lista, envio.codigo, &pos, 1);


    if (encontrado) {

        if ((strcmp(lista->envios[pos].direccion, envio.direccion) == 0) &&
            (lista->envios[pos].dni_receptor == envio.dni_receptor)
            && (lista->envios[pos].dni_remitente == envio.dni_remitente) &&
            (strcmp(lista->envios[pos].fecha_envio, envio.fecha_envio) == 0)
            && (strcmp(lista->envios[pos].fecha_recepcion, envio.fecha_recepcion) == 0) &&
            (strcmp(lista->envios[pos].nombre, envio.nombre) == 0)
            && (strcmp(lista->envios[pos].nombre_r, envio.nombre_r) == 0)) {


            for (i = pos; i < lista->contador - 1; i++) {
                lista->costo++; //corrimiento
                lista->envios[i] = lista->envios[i + 1];
            }

            pos--;
            lista->contador--;


            if (lista->costo > lista->bMax) {

                lista->bMax = lista->costo; //maximo

            }

            lista->tempb += lista->costo; //promedio

            lista->bCant++; //cantidad de bajas
            lista->bMed = lista->tempb / (lista->bCant);


            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}


int evocarLSOBB(lsobb *lista, char codigo[], Envio *envio) {
    int pos;
    int encontrado = LocalizarLSOBB(lista, codigo, &pos, 0);

    if (encontrado) {

        *envio = lista->envios[pos];
        return 1;
    } else {
        return 0;
    }
}
