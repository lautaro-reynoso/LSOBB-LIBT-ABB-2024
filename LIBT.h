//
// Created by lautaro on 19/8/2023.
//
#include "Envios.h"
#include <String.h>

#ifndef UNTITLED_LSO_H
#define UNTITLED_LSO_H
#endif //UNTITLED_LSO_H

char *Mayusculas(char string[]);

typedef struct {
    Envio *envios[MAX_Envios];
    int contador;

    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, celCont, tempa, tempb, eExCant, eFrCant, aCant, bCant, costo, costoEvoE, costoEvoF, tempe, tempef;

    int exitos;
    int fracasos;
    int max_exitos;
    int max_fracasos;
    int total_exitos;
    int total_fracasos;
    int total_celdas_consultadas_exitos;
    int total_celdas_consultadas_fracasos;
    float media_exitos;
    float media_fracasos;
} libt;

void initLIBT(libt *lista) {

    lista->exitos = 0;
    lista->fracasos = 0;
    lista->max_exitos = 0;
    lista->max_fracasos = 0;
    lista->total_exitos = 0;
    lista->total_fracasos = 0;
    lista->total_celdas_consultadas_fracasos = 0;
    lista->total_celdas_consultadas_exitos = 0;
    lista->media_fracasos = 0.0;
    lista->media_exitos = 0.0;
    // Nuevas variables para el seguimiento de �xitos y fracasos


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

int LocalizarLIBT(libt *lista, char codigo[], int *pos, int p) {

    int celdas_consultadas = 0;
    int li = 0; // li inclusivo
    int ls = (*lista).contador; // ls exclusivo
    int m;

    if(lista->contador==0){
        *pos = 0;
        if (p == 0) {
            if (lista->eFrMax < celdas_consultadas) {
                lista->eFrMax = celdas_consultadas;
            }
            lista->eFrCant++;
            lista->costoEvoF += celdas_consultadas;
            lista->tempef += lista->costoEvoF;
            lista->eFrMed = lista->tempef / (lista->eExCant);
        }

        return 0;
    }

    //CONSULTAR EL COSTO

    while (li < ls) {
        m = (li + ls) / 2; //Segmento mas grande a izquierda
        celdas_consultadas+= 2;


        if (strcmp(codigo, lista->envios[m]->codigo) == 0) {


            *pos = m;
            if (p == 0) {

                lista->exitos++;
                lista->total_exitos++;
                if (celdas_consultadas > lista->max_exitos) {
                    lista->max_exitos = celdas_consultadas;
                }

                lista->total_celdas_consultadas_exitos += celdas_consultadas; // Actualizar el total de celdas consultadas para �xitos
                lista->media_exitos = (float) lista->total_celdas_consultadas_exitos /
                                      lista->total_exitos; // Calcular la media para �xitos
            }


            return 1; // Elemento encontrado
        } else if (strcmp(codigo, lista->envios[m]->codigo) < 0) {
            ls = m;
        } else {
            li = m + 1;
        }
    }

    *pos = li;

    if (p == 0) {
        lista->fracasos++;
        lista->total_fracasos++;
        if (celdas_consultadas > lista->max_fracasos) {
            lista->max_fracasos = celdas_consultadas;
        }
        lista->total_celdas_consultadas_fracasos += celdas_consultadas; // Actualizar el total de celdas consultadas para fracasos
        lista->media_fracasos = (float) lista->total_celdas_consultadas_fracasos /
                                lista->total_fracasos; // Calcular la media para fracasos
    }
    return 0; // Elemento no encontrado

}


int AltaLIBT(libt *lista, Envio envio) {
//Agregar costo de de nupla sumar 2 al contador entre celda y dato
    float costo = 0.0;

    //preguntar - No libera memoria al limpiar estructura para comparar
    int pos, i;

    if(lista->contador == MAX_Envios){
        return 0;
    }

    if (LocalizarLIBT(lista, envio.codigo, &pos, 1) == 0) {
        Envio *aux;
        aux = (Envio *) malloc(sizeof(Envio));

        if (aux == NULL) {
            return 2;
        }

        strcpy(aux->codigo, envio.codigo);
        strcpy(aux->nombre, envio.nombre);
        strcpy(aux->fecha_recepcion, envio.fecha_recepcion);
        strcpy(aux->fecha_envio, envio.fecha_envio);
        strcpy(aux->direccion, envio.direccion);
        strcpy(aux->nombre_r, envio.nombre_r);
        aux->dni_remitente = envio.dni_remitente;
        aux->dni_receptor = envio.dni_receptor;


        if ((*lista).contador != 0) {
            for (i = lista->contador - 1; i >= pos; i--) {
                costo = costo + 0.5;
                lista->envios[i + 1] = lista->envios[i];


            }
        }


        //printf("Codigo:%s ---> costo: %.2f \n",envio.codigo,costo);
        // getchar();
        lista->envios[pos] = aux;

        costo += 0.5;


        lista->contador++;

        if (costo > lista->aMax) {

            lista->aMax = costo; //maximo



        }


        lista->tempa += costo; //promedio
        lista->aCant++; //cantidad de altas
        lista->aMed = lista->tempa / (lista->aCant);


        return 1;

    }

    return 0;

}


int BajaLIBT(libt *lista, Envio envio) {

    //Liberar memoria free() y controlar antes de baja estructura vacia
    float costo = 0.0;


    int pos, i;




    int localizar_resultado = LocalizarLIBT(lista, envio.codigo, &pos, 1);


    if (localizar_resultado) {

        if ((strcmp(lista->envios[pos]->direccion, envio.direccion) == 0) &&
            (lista->envios[pos]->dni_receptor == envio.dni_receptor)
            && (lista->envios[pos]->dni_remitente == envio.dni_remitente) &&
            (strcmp(lista->envios[pos]->fecha_envio, envio.fecha_envio) == 0)
            && (strcmp(lista->envios[pos]->fecha_recepcion, envio.fecha_recepcion) == 0) &&
            (strcmp(lista->envios[pos]->nombre, envio.nombre) == 0)
            && (strcmp(lista->envios[pos]->nombre_r, envio.nombre_r) == 0)) {

            free(lista->envios[pos]);

            for (i = pos; i < lista->contador - 1; i++) {
                costo += 0.5; //corrimiento
                lista->envios[i] = lista->envios[i + 1];
            }


            lista->contador--;


            if (costo > lista->bMax) {

                lista->bMax = costo; //maximo

            }

            lista->tempb += costo; //promedio
            lista->bCant++;
            lista->bMed = lista->tempb / (lista->bCant);



            //cantidad de bajas



            return 1;

        }

    } else {
        return 0;
    }


    return 0;
}

void liberarmemorialibt(libt *lista){
    int i = 0;
    for ( i = 0;i < lista->contador; i++){
        free(lista->envios[i]);
    }


}

int evocarLIBT(libt *lista, char codigo[], Envio *envio, int *contador) {


    int pos;

    if (lista->contador == 0)
        return 0;
    int res = LocalizarLIBT(lista, codigo, &pos, 0);
    Envio aux;
    if (res == 1) {

        strcpy(aux.codigo, lista->envios[pos]->codigo);
        strcpy(aux.nombre, lista->envios[pos]->nombre);
        strcpy(aux.fecha_recepcion, lista->envios[pos]->fecha_recepcion);
        strcpy(aux.fecha_envio, lista->envios[pos]->fecha_envio);
        strcpy(aux.direccion, lista->envios[pos]->direccion);
        strcpy(aux.nombre_r, lista->envios[pos]->nombre_r);
        aux.dni_remitente = lista->envios[pos]->dni_remitente;
        aux.dni_receptor = lista->envios[pos]->dni_receptor;

        *envio = aux;
        return 1;// se
        // econtro
    } else
        return 0;
}
