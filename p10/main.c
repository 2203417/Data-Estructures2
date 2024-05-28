#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// banderas de compilacion y como compilar el progama
// gcc -Wall -Werror -pedantic -std=c99 main.c funciones.c -o practica10

int main()
{
    //  -------------------------------------------------------------------variables-------------------------------------------------------------------
    int ciclo = 0;
    int op = 0;
    int id_search = 0;
    int year = 0;
    int rating = 0;
    int sub_op = 0;
    char name_search[50]; // del tamaño de la cadena

    Movie **movies = create_movies();                     // creamos el arreglo de punteros a estructuras
    Movie *temp_movie = NULL;                             // puntero temporal
    HashTable *first_hash = create_id_hash_table(movies); // creamos la tabla hash
    HashTable *second_hash = create_second_hash_table();
    // second_hash->table[3] = movies[5];
    while (ciclo == 0)
    {
        // system("clear");
        printf("[0] MOSTRAR HASH ID\n");
        printf("[1] MOSTRAR HASH NOMBRE\n");
        printf("[2] BUSCAR PELÍCULA ID\n");
        printf("[3] BUSCAR PELÍCULA NOMBRE\n");
        printf("[4] AGREGAR PELÍCULA\n");
        printf("[5] ELIMINAR PELÍCULA\n");
        printf("[6] TERMINAR PROGAMA\n");
        scanf("%d", &op);
        getchar(); // Consumir el caracter de nueva línea
        switch (op)
        {
        case 0: // -------------------------------------------------------------------COMPLETA-------------------------------------------------------------------
            print_hastable(first_hash);

            break;
        case 1: // -------------------------------------------------------------------COMPLETA-------------------------------------------------------------------
            print_hastable(second_hash);

            break;
        case 2:
            // -------------------------------------------------------------------INCOMPLETA-------------------------------------------------------------------
            printf("Ingrese el numero de la pelicula que desea buscar:\n");
            scanf("%d", &id_search);
            search_movie_id(first_hash, id_search - 1); // mas uno por que empieza del 0 entonces -1 se ingresara el numero de la pelicula
            printf("\n");
            break;
        case 3:
            // -------------------------------------------------------------------COMPLETA-------------------------------------------------------------------
            printf("Ingrese el nombre de la pelicula:\n");
            fflush(stdin);
            fgets(name_search, sizeof(name_search), stdin);
            name_search[strcspn(name_search, "\n")] = 0; // quitamos el salto de linea
            search_movie_name(second_hash, name_search);
            break;
        case 4:
            printf("Ingrese el nombre de la pelicula:\n");
            fflush(stdin);
            fgets(name_search, sizeof(name_search), stdin);
            name_search[strcspn(name_search, "\n")] = 0; // quitamos el salto de linea
            printf("Cadena ingresada: %s\n", name_search);
            printf("Ingrese el año de la pelicula:\n");
            scanf("%d", &year);
            printf("Ingrese la calificacion de la pelicula:\n");
            scanf("%d", &rating);
            temp_movie = create_movie(name_search, year, rating); //  creamos la pelicula
            // agregamos a la priemra hash
            add_movie_first_hash_table(first_hash, temp_movie);
            // agregamos a la segunda
            add_movie_second_hash_table(second_hash, temp_movie);

            break;
        case 5:
            // -------------------------------------------------------------------NULL-------------------------------------------------------------------
            printf("Eliminacion de pelicula\n");
            printf("[0]- Eliminar por ID\n");
            printf("[1]- Eliminar por Nombre\n");
            printf("[2]- Regresar\n");
            scanf("%d", &sub_op);
            switch (sub_op)
            {
            case 0:
                printf("Ingrese el numero de la pelicula que desea eliminar:\n");
                scanf("%d", &id_search);
                delete_by_id_first_hash(first_hash, id_search);  // se elikmina el id
                delete_by_id_first_hash(second_hash, id_search); // se elikmina el id
                break;
            case 1:
                getchar(); // Consumir el caracter de nueva línea
                printf("Ingrese el nombre de la pelicula:\n");
                fflush(stdin);
                fgets(name_search, sizeof(name_search), stdin);
                name_search[strcspn(name_search, "\n")] = 0; // quitamos el salto de linea
                // printf("Primera hash\n");
                delete_by_name_second_hash(first_hash, name_search); // se elimina por nombre en la primera tabla tmb
                // delete_by_name_second_hash(second_hash, name_search); // se elimina por nombre
                // printf("Segunda hash\n");

                print_hastable(first_hash);
                print_hastable(second_hash);
                break;
            case 2:
                printf("Saliendo\n");
                break;
            default:
                printf("Saliendo\n");
                break;
            }

            break;
        case 6:
            // -------------------------------------------------------------------NULL-------------------------------------------------------------------
            printf("Saliendo\n");
            ciclo = 1;
            break;
        default:
            printf("OPCION NO VALIDA\n");
            break;
        }
    }
}