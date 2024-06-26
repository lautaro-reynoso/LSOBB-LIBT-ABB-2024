#define ABB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include "Envios.h"
#include <malloc.h>



typedef struct Nodo
{
    Envio envio;
    struct Nodo *der;
    struct Nodo *izq;
} nodo;
typedef struct
{
    nodo *raiz;
    nodo *pos;
    nodo *padre;
    float eExMax, eExMed, eFrMax, eFrMed, aMax, aMed, bMax, bMed, celCont,costoAcum, costobajatemp, costobajaacum;
    float eExCant,eFrCant,aCant,bCant;
    float costoacumEF,costoacumEE;

} arbol;
void initABB(arbol *a)
{
    (*a).pos=NULL;
    (*a).padre=NULL;
    (*a).raiz=NULL;
    a->eExMax = 0;
    a->aMax = 0;
    a->bMax = 0;
    a->eFrMax = 0;
    a->bMed = 0;
    a->bCant = 0;
    a->eFrMed = 0;
    a->eExCant = 0;
    a->eFrCant = 0;
    a->aCant = 0;
    a->aMed = 0;
    a->eExMed=0;
    a->costoAcum = 0.0;
    a->costoacumEF = 0;
    a->costoacumEE = 0;
    a->costobajatemp = 0;
    a->costobajaacum = 0;
}
int localizarABB(arbol *a,char codigo[], int f)
{
    a->celCont = 0;
    //a->eFrMax = 0;
    a->pos = a->raiz;
    a->padre = a->raiz;
    while((*a).pos != NULL && strcmp((*a).pos->envio.codigo, codigo)!=0){
        a->celCont++;
        if (strcmp((*a).pos->envio.codigo, codigo) > 0)
        {
            (*a).padre = (*a).pos;
            (*a).pos = (*a).pos->izq;
        }
        else
        {
            (*a).padre = (*a).pos;
            (*a).pos = (*a).pos->der;
        }

    }

    if ((*a).pos == NULL){
        if(f == 2){
            if(a->celCont > a->eFrMax){
                a->eFrMax = a->celCont;
            }
            a->eFrCant++;
            a->costoacumEF += a->celCont;
            a->eFrMed = a->costoacumEF/(a->eFrCant);
        }

        return 0;
    }else{
        a->celCont++;
        if(f == 2){

            if(a->celCont > a->eExMax){
                a->eExMax =a->celCont;
            }
            a->eExCant++;
            a->costoacumEE += a->celCont;
            a->eExMed = a->costoacumEE/(a->eExCant);
        }

        return 1;
    }
}
int bajaABB(arbol *a,Envio envio)
{

    a->costobajatemp = 0;

    if (localizarABB(a,envio.codigo,0)== 0)
    {
        return 2;
    }
    else
    {
        if( (strcmp(a->pos->envio.direccion, envio.direccion)==0) && (a->pos->envio.dni_receptor == envio.dni_receptor)
            && (a->pos->envio.dni_remitente == envio.dni_remitente) && (strcmp(a->pos->envio.fecha_envio,envio.fecha_envio)==0)
            && (strcmp(a->pos->envio.fecha_recepcion,envio.fecha_recepcion)==0) && (strcmp(a->pos->envio.nombre,envio.nombre)==0)
            && (strcmp(a->pos->envio.nombre_r,envio.nombre_r)==0))
        {
            int s=0;
            nodo *aux,*padre;
            padre = (*a).pos;
            aux = a->pos;

            (*a).bCant++;


            if ((*a).pos->izq != NULL)
            {

                if((*a).pos->der != NULL) //caso tiene los dos hijos
                {
                    aux = (*a).pos->izq;
                    while(aux->der != NULL)
                    {
                        s++;
                        padre = aux;
                        aux = aux->der;
                    }
                    if(s == 0 )
                    {
                        padre->izq = aux->izq;

                    }
                    else
                    {
                        padre->der = aux->izq;

                    }
                    a->costobajatemp= 1.5;
                    a->costobajaacum += 1.5;

                    if((*a).bMax < a->costobajatemp){
                        (*a).bMax = a->costobajatemp;
                    }
                    (*a).pos->envio = aux->envio;
                    free(aux);

                    (*a).bMed = a->costobajaacum/((*a).bCant);
                    return 1;
                }
                else //caso tiene hijo izq
                {
                    aux = (*a).pos->izq;
                    if((*a).padre->izq == (*a).pos)
                        (*a).padre->izq = aux;

                    else if((*a).padre->der == (*a).pos)
                        (*a).padre->der = aux;

                    else
                        (*a).raiz = aux;
                    a->costobajatemp= 0.5;
                    a->costobajaacum +=0.5;
                    if((*a).bMax < a->costobajatemp){
                        (*a).bMax = a->costobajatemp;
                    }
                    free(((*a).pos));

                    (*a).bMed = a->costobajaacum/((*a).bCant);
                    return 1;
                }
            }
            else if((*a).pos->der != NULL) //caso tiene hijo derecho
            {
                aux = (*a).pos->der;

                if((*a).padre->izq == (*a).pos)
                    (*a).padre->izq = aux;

                else if((*a).padre->der == (*a).pos)
                    (*a).padre->der = aux;

                else
                    (*a).raiz = aux;
                a->costobajatemp= 0.5;
                a->costobajaacum +=0.5;

                if((*a).bMax < a->costobajatemp){
                    (*a).bMax = a->costobajatemp;
                }
                free(((*a).pos));

                (*a).bMed = a->costobajaacum/((*a).bCant);
                return 1;
            }
            else if((*a).padre == (*a).pos)//caso raiz
            {
                (*a).raiz = NULL;
                a->costobajatemp= 0.5;
                a->costobajaacum +=0.5;
                if((*a).bMax < a->costobajatemp){
                    (*a).bMax = a->costobajatemp;
                }
                free(aux);

                (*a).bMed = a->costobajaacum/((*a).bCant);
                return 1;
            }
            else if((*a).padre->izq == (*a).pos) //no tiene hijos
            {
                (*a).padre->izq = NULL;
                a->costobajatemp+= 0.5;
                a->costobajaacum +=0.5;
                if((*a).bMax < a->costobajatemp){
                    (*a).bMax = a->costobajatemp;
                }
                free(aux);

                (*a).bMed = a->costobajaacum/((*a).bCant);
                return 1;
            }
            else
            {
                (*a).padre->der = NULL;
                a->costobajatemp+= 0.5;
                a->costobajaacum +=0.5;
                if((*a).bMax < a->costobajatemp){
                    (*a).bMax = a->costobajatemp;
                }
                free(aux);

                (*a).bMed = a->costobajaacum/((*a).bCant);
                return 1;
            }



        }
        return 0;


    }

}

int altaABB(arbol *a,Envio envio)
{
    float temporal = 0.0;

    if (localizarABB(a,envio.codigo,0)==0)
    {
        nodo *nuevo_nodo;
        nuevo_nodo=(nodo*)malloc(sizeof(nodo));
        if(nuevo_nodo==NULL)
        {
            return 2;//no hay espacio
        }
        else
        {


            nuevo_nodo->envio=envio;
            nuevo_nodo->der=NULL;
            nuevo_nodo->izq=NULL;

            if((*a).padre==NULL)
            {
                (*a).padre=nuevo_nodo;
                (*a).pos=(*a).padre;
                (*a).raiz=(*a).padre;

                temporal+= 0.5;
                (*a).aCant++;
                if((*a).aMax<temporal)
                {
                    (*a).aMax=temporal;

                }
                //media
                (*a).costoAcum += temporal;
                (*a).aMed = (*a).costoAcum/((*a).aCant);

                return 1;
            }
            else if (strcmp((*a).padre->envio.codigo, envio.codigo) < 0)
            {
                (*a).padre->der=nuevo_nodo;
                temporal+= 0.5;
                (*a).aCant++;
                if((*a).aMax<temporal)
                {
                    (*a).aMax=temporal;
                }
                //media
                (*a).costoAcum += temporal;
                (*a).aMed = (*a).costoAcum/((*a).aCant);
                return 1;
            }
            else
            {

                (*a).padre->izq=nuevo_nodo;
                temporal+= 0.5;
                (*a).aCant++;
                if((*a).aMax<temporal)
                {
                    (*a).aMax=temporal;
                }
                //media
                (*a).costoAcum += temporal;
                (*a).aMed = (*a).costoAcum/((*a).aCant);
                return 1;
            }


        }
    }
    else
    {
        return 0;
    }
}

int evocacionABB(arbol *a,char codigo[],int *exito)
{

    *exito=localizarABB(a,codigo,2);
    if(*exito==1)
    {
        return 1;
    }
    return 0;
}
void liberarmemoriaabb(nodo* nodo){

    if(nodo == NULL){
        return;
    }
    liberarmemoriaabb(nodo->izq);
    liberarmemoriaabb(nodo->der);
    free(nodo);
}
void inorden(nodo* nodo_actual, int *cont) {
    *cont++;
    if (nodo_actual != NULL) {

        inorden(nodo_actual->izq,cont);
        printf("\nCodigo: %s \n", nodo_actual->envio.codigo);
        printf("Dni receptor: %d\n",nodo_actual->envio.dni_receptor);
        printf("Nombre y Apellido: %s\n",nodo_actual->envio.nombre);
        printf("Direccion: %s\n",nodo_actual->envio.direccion);
        printf("Dni remitente: %d\n",nodo_actual->envio.dni_remitente);
        printf("Fecha de envio: %s\n",nodo_actual->envio.fecha_envio);
        printf("Fecha recepcion: %s\n",nodo_actual->envio.fecha_recepcion);
        printf("Nombre receptor: %s\n\n",nodo_actual->envio.nombre_r);
        if( nodo_actual->izq != NULL )
        {
            printf("El Codigo de su hijo izquierdo es: %s\n",nodo_actual->izq->envio.codigo);
        }
        else
        {
            printf("No tiene hijo izquierdo.\n");
        }
        if(nodo_actual->der != NULL)
        {
            printf("El Codigo de su hijo derecho es: %s\n",nodo_actual->der->envio.codigo);
        }
        else
            printf("No tiene hijo derecho.\n");
        getchar();
        inorden(nodo_actual->der,cont);
    }
}


