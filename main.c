#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Envios.h"
#include "LIBT.h"
#include "ABB.h"
#include "LSOBB.h"

/*
 * Analisis de resultados:
//CAMBIAR ANALISIS ENTRE LSOBB Y  LIBT
Altas:
Alta Máxima:
LIBT: 29.00
LSOBB: 58.00
ABB: 0.50
Para las altas, el ABB es claramente superior en términos de eficiencia,
con un costo mucho menor que las otras dos estructuras.

Bajas:
Baja Máxima:
LIBT: 23.50
LSOBB: 47.00
ABB: 0.50
En el caso de las bajas máximas, tanto LIBT como LSOBB tienen el mismo costo,
mientras que ABB sigue siendo la opción más eficiente.

Evocaciones de Éxito:
Máxima Evocación Exitosa:
LIBT: 6.00
LSOBB: 6.00
ABB: 12.00
Media Evocación Exitosa:
LIBT: 4.70
LSOBB: 5.55
ABB: 5.72
Para las evocaciones de éxito, LIBT parece ser la mejor opción en términos de costos,
seguida de cerca por ABB. LSOBB tiene un costo más alto en ambos casos.

Evocaciones de Fracaso:
Máxima Evocación Fracaso:
LIBT: 6.00
LSOBB: 6.00
ABB: 11.00
Media Evocación Fracaso:
LIBT: 5.09
LSOBB: 4.83
ABB: 6.48
Para las evocaciones de fracaso, LSOBB parece ser la mejor opción en términos de costos,
seguida por LIBT. ABB tiene un costo más alto en ambos casos.


Altas: El árbol binario de búsqueda (ABB) es la opción más eficiente, con un costo significativamente menor que las otras estructuras.
Bajas: ABB sigue siendo la opción más eficiente, con un costo mínimo, mientras que la lista invertida por búsqueda por trisección (LIBT) y la lista secuencial ordenada por búsqueda binaria (LSOBB) tienen costos diferentes.
Evocaciones de Éxito: La lista invertida por búsqueda por trisección (LIBT) tiene el costo más bajo, seguida de cerca por ABB. La lista secuencial ordenada por búsqueda binaria (LSOBB) tiene costos más altos en este caso.
Evocaciones de Fracaso: La lista secuencial ordenada por búsqueda binaria (LSOBB) muestra la eficiencia más alta en términos de costos, seguida por LIBT. ABB tiene un costo más alto para evocaciones de fracaso.


En general, ABB parece ser la opción más eficiente en términos de costos para altas y bajas,
mientras que LIBT y LSOBB son más competitivas para evocaciones de éxito y de fracaso,
respectivamente. La elección final dependerá de las prioridades y necesidades específicas
del sistema en el que se implementen estas estructuras de datos.
 *
 *
 *
 */
int LecturaOperaciones();

char *Mayusculas();

void mostrarestructura();

void mostrarSubmenu() {

    printf("--Submenu--\n");
    printf("1. Mostrar Lista Invertida con busqueda por Triseccion (LIBT).\n");
    printf("2. Mostrar Lista Secuencial con Busqueda Binaria (LSOBB)\n");
    printf("3. Mostrar Arbol Binario de Busqueda (ABB)\n");
    printf("4. Volver al Menu Principal\n");
}

char *Mayusculas(char string[]) {
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        string[i] = toupper(string[i]);
    }
    return string;
}

void mostrarestructuraLIBT(libt lista) {
    int i;

    for (i = 0; i < lista.contador; i++) {
        mostrarenvio(*lista.envios[i]);
        getchar();
    }
    printf("Total de %d envios\n", lista.contador);

}

void mostrarestructuraLSOBB(lsobb *lista) {
    int i;

    for (i = 0; i < lista->contador; i++) {
        mostrarenvio(lista->envios[i]);
        getchar();
    }
    printf("Total de %d envios\n", lista->contador);

}


int main() {
    // Crea las estructuras de datos (LSO, ABB) aqu�

    int opcion, submenu_opcion;

    libt libt;
    initLIBT(&libt);
    libt.contador = 0;

    arbol a;
    initABB(&a);

    lsobb lsobb;
    lsobb.contador = 0;
    initLSOBB(&lsobb);


    do {
        // Men� principal

        printf("1. Comparacion de estructuras\n");
        printf("2. Mostrar Estructura\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                system("cls");
                liberarmemorialibt(&libt);
                initLIBT(&libt);
                libt.contador = 0;

                liberarmemoriaabb(a.raiz);
                initABB(&a);

                lsobb.contador = 0;
                initLSOBB(&lsobb);

                LecturaOperaciones(&libt, &a, &lsobb);

                printf("\t AltaMax | AltaMed | BajaMax | BajaMed | Max.Ev.Ex | Med.Ev.Ex | Max.Ev.Fr | Med.Ev.Fr|\n");
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("LIBT :: %.2f   |   %.2f |  %.2f  |  %.2f    |    %d    |   %.2f     |   %d     |   %.2f    | \n",
                       libt.aMax, libt.aMed, libt.bMax, libt.bMed, libt.max_exitos, libt.media_exitos,
                       libt.max_fracasos, libt.media_fracasos);
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("LSOBB :: %.2f   |   %.2f |  %.2f  |  %.2f  |    %.2f   |   %.2f    |   %.2f    |   %.2f   | \n",
                       lsobb.aMax, lsobb.aMed, lsobb.bMax, lsobb.bMed, lsobb.eExMax, lsobb.eExMed, lsobb.eFrMax,
                       lsobb.eFrMed);
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("ABB   ::  %.2f   |    %.2f |   %.2f  |   %.2f  |   %.2f   |   %.2f    |  %.2f    |   %.2f   | \n",
                       a.aMax, a.aMed, a.bMax, a.bMed, a.eExMax, a.eExMed, a.eFrMax, a.eFrMed);
                printf("-----------------------------------------------------------------------------------------------\n");


                break;
            case 2:


                system("cls");
                do {
                    mostrarSubmenu();
                    printf("Seleccione una opcion: ");
                    scanf("%d", &submenu_opcion);
                    switch (submenu_opcion) {
                        case 1:
                            system("cls");

                            printf("Lista Invertida con Busqueda Triseccion:\n");
                            mostrarestructuraLIBT(libt);
                            break;
                        case 2:
                            system("cls");
                            printf("Lista Secuencial Ordenada con Busqueda Binaria (LSOBB):\n");
                            mostrarestructuraLSOBB(&lsobb);

                            break;
                        case 3:
                            system("cls");
                            printf("Arbol Binario de Busqueda (orden ascendente):\n");
                            int contadorarbol = 0;
                            inorden(a.raiz, &contadorarbol);

                            break;
                        case 4:
                            system("cls");
                            // Volver
                            break;
                        default:
                            system("cls");
                            printf("Opcion no valida. Intente de nuevo.\n");
                    }
                } while (submenu_opcion != 4);

                break;
            case 3:
                system("cls");
                printf("Saliendo de la aplicacion.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 3);


    return 0;
}

int LecturaOperaciones(libt *libt, arbol *arbol, lsobb *lsobb) {

    // Declaraciones e inicializaciones
    int evocar = 0, contador = 0;
    Envio aux, aux2;
    FILE *fp;
    char cwd[1024];



    // Obtener el directorio actual
    if (_getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Error al obtener el directorio actual");
        return 1;
    }




    // Concatenar la ruta del archivo al directorio actual
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s\\%s", cwd, "../Operaciones-Envios.txt");

    // Intentar abrir el archivo en modo lectura
    if ((fp = fopen(filepath, "r")) == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    } else {
        printf("enbtro");
        int codigoOperador = 0, i;


        while (!(feof(fp))) {


            fscanf(fp, "%d", &codigoOperador);


            fscanf(fp, " %[^\n]", aux.codigo);
            for (i = 0; i <= 8; i++) {
                aux.codigo[i] = toupper(aux.codigo[i]);
            }
            if (codigoOperador == 1 || codigoOperador == 2) {

                // Leer y procesar los datos para Alta o Baja
                fscanf(fp, "%d", &aux.dni_receptor);

                fscanf(fp, " %[^\n]", aux.nombre);
                for (i = 0; i <= strlen(aux.nombre); i++) {
                    aux.nombre[i] = toupper(aux.nombre[i]);
                }
                fscanf(fp, " %[^\n]", aux.direccion);
                for (i = 0; i <= strlen(aux.direccion); i++) {
                    aux.direccion[i] = toupper(aux.direccion[i]);
                }
                fscanf(fp, "%d", &aux.dni_remitente);
                fscanf(fp, " %[^\n]", aux.nombre_r);
                for (i = 0; i <= strlen(aux.nombre_r); i++) {
                    aux.nombre_r[i] = toupper(aux.nombre_r[i]);
                }
                fscanf(fp, " %[^\n]", aux.fecha_envio);
                fscanf(fp, " %[^\n]", aux.fecha_recepcion);

                // Llama a la funci�n correspondiente para alta o baja en las estructuras
                if (codigoOperador == 1) {
                    //  mostrarenvio(aux);

                    AltaLIBT(libt, aux);

                    AltaLSOBB(lsobb, aux);

                    altaABB(arbol, aux);


                }
                if (codigoOperador == 2) {


                    bajaABB(arbol, aux);
                    BajaLSOBB(lsobb, aux);

                    BajaLIBT(libt, aux);


                }

            } else if (codigoOperador == 3) {

                evocar++;

                int exito = 0;
                evocarLIBT(libt, aux.codigo, &aux2, &contador);
                evocarLSOBB(lsobb, aux.codigo, &aux2);
                evocacionABB(arbol, aux.codigo, &exito);

            } else {
                // Maneja el caso de c�digo de operaci�n no reconocido
                printf("Error: Codigo de operaci�n no reconocido.\n");
                //break;
            }

        }

        fclose(fp);


        return 1;
    }

}
