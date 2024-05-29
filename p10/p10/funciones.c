#include "funciones.h"

#include <stdio.h>
#include <stdlib.h>
#define SIZE_DATA 105
#include <string.h>

HashTable *create_id_hash_table(Movie **movies)
{
    HashTable *hash = (HashTable *)calloc(1, sizeof(HashTable));    // RESERVA DE MEMORIA 1 VEZ
    hash->size = SIZE_DATA;                                         // ASIGNACION DE VALORES
    hash->amount_data = 0;                                          // ASIGNACION DE VALORES
    hash->table = (Movie **)calloc(SIZE_DATA * 2, sizeof(Movie *)); // RESERVA DE MEMORIA por la cantidad de datos que puede contener

    for (int i = 0; i < hash->size; i++)
    {
        // printMovie(movies[i]);
        hash->table[i] = (Movie *)calloc(1, sizeof(Movie)); // RESERVA DE MEMORIA
        *(hash->table[i]) = *movies[i];                     // ASIGNACION DE VALORES
        // printMovie(hash->table[i]);
        hash->amount_data++;
    }

    return hash;
}

HashTable *create_second_hash_table(Movie **movies)
{
    HashTable *hash = (HashTable *)calloc(1, sizeof(HashTable));    // RESERVA DE MEMORIA 1 VEZ
    hash->size = 0;                                                 // ASIGNACION DE VALORES
    hash->amount_data = 0;                                          // ASIGNACION DE VALORES
    hash->table = (Movie **)calloc(SIZE_DATA * 4, sizeof(Movie *)); // reserva por la cantidad de datos que puede contener
    hash->table[0] = (Movie *)calloc(1, sizeof(Movie));             // RESERVA DE MEMORIA
    hash->size++;                                                   // AUMENTO DE ESPACIO

    Movie *movie = NULL;
    for (int i = 0; i < SIZE_DATA; i++)
    {
        // duplicate_hash_table(hash);
        // printMovi
        movie = create_movie_by_movie(movies[i]); // RESERVA DE MEMORIA
        movie->id = i;

        add_movie_second_hash_table(hash, movie);
        // printf("TAM DE HASH %d\n", hash->size);
    }

    return hash;
}

Movie *create_movie_by_movie(Movie *movie)
{
    Movie *new_movie = (Movie *)malloc(sizeof(Movie));
    new_movie->name = strdup(movie->name);
    new_movie->release_date = movie->release_date;
    new_movie->rating = movie->rating;
    return new_movie;
}
Movie *create_movie(char *name, int year, int rating)
{
    Movie *movie = (Movie *)malloc(sizeof(Movie));
    movie->name = strdup(name);
    movie->release_date = year;
    movie->rating = rating;
    return movie;
}

void add_movie_first_hash_table(HashTable *hash, Movie *movie)
{ // ASIGNACION DE VALORES

    int index = first_hash_space(hash); // ASIGNACION DE VALORES
    // printf("%d\n", index);
    if (index == -1)
    {
        printf("No hay espacio\n");
        // printf("%d", hash->amount_data);
        hash->table[hash->amount_data] = (Movie *)calloc(1, sizeof(Movie)); // RESERVA DE MEMORIA
        movie->id = hash->amount_data;                                      // ASIGNACION DE VALORES
        hash->table[hash->amount_data] = movie;                             // ASIGNACION DE VALORES
        // printf("%s\n", hash->table[index]->name);
        hash->amount_data++; // AUMENTO DE DATOS
        hash->size++;
        return;
    }
    else if (hash->table[index]->name == NULL)
    {
        hash->table[index] = movie; // ASIGNACION DE VALORES
        movie->id = index;          // ASIGNACION DE VALORES
        // printf("Se agrego la pelicula\n");
        // printf("%s\n", hash->table[index]->name);
        hash->amount_data++; // AUMENTO DE DATOS
        // hash->siz
        hash->size++;

        return;
    }
    return;
}
double get_load_factor(HashTable *hash)
{
    //  printf("AMOUNT -- %d\n", hash->amount_data);
    // printf("SIZEEE %d\n", hash->size);

    // Utilizamos el tipo de dato double para mayor precisión en la división
    double factor_carga = (double)hash->amount_data / hash->size;
    // printf("Factor de carga: %.2f\n", factor_carga);
    return factor_carga;
}

void add_movie_second_hash_table(HashTable *hash, Movie *movie)
{
    duplicate_hash_table(&hash);
    printf("Hash size %d", hash->size);
    int index = folding(movie, hash->size);
    printf("----Index %d\n", index);

    if (hash->table[index]->name == NULL)
    {
        movie->id = index;
        hash->table[index] = movie;
        hash->amount_data++;
    }
    else
    {
        int i = 1;
        while (hash->table[index]->name != NULL)
        {
            index = rehash(index, hash->size, i);
            printf("Rehasheo %d\n", index);
            i++;
        }
        movie->id = index;
        hash->table[index] = movie;
        hash->amount_data++;
    }
}

void delete_by_id_first_hash(HashTable *hash, HashTable *second_hash, int id)
{
    Movie *movie_delete;
    for (int i = 0; i < hash->size; i++)
    {
        if (hash->table[i]->id == id)
        {
            printf("Pelicula encontrada, se eliminara la pelicula con el id: %d\n", id);
            printMovie(hash->table[i]); // imprime la pelicula
            delete_by_id_second_hash(second_hash, id, hash->table[i]->name);
            movie_delete = hash->table[i];
            // free(movie_delete->name);
            // free(movie_delete);
            movie_delete->id = 0;
            movie_delete->name = NULL;
            movie_delete->release_date = 0;
            movie_delete->rating = 0;
            // hash->table[i]->name = NULL;
            // hash->table[i]->release_date = 0;
            // hash->table[i]->rating = 0;
            // hash->amount_data--;
            return;
        }
    }
    printf("Pelicula no encontrada\n");
}

HashTable *inicializate_second_hash()
{
    HashTable *hash = (HashTable *)calloc(1, sizeof(HashTable)); // RESERVA DE MEMORIA 1 VEZ
    hash->size = 0;                                              // ASIGNACION DE VALORES
    hash->amount_data = 0;                                       // ASIGNACION DE VALORES
    hash->table = (Movie **)calloc(SIZE_DATA, sizeof(Movie *));  // se multiplica por siza data por que es el tamaño de la tabla,
    hash->table[0] = (Movie *)calloc(1, sizeof(Movie));          // RESERVA DE MEMORIA
    hash->size++;                                                // AUMENTO DE ESPACIO
    // *(hash->table[i]) = *movies[i];                     // ASIGNACION DE VALORES
    // printMovie(hash->table[i]);
    return hash;
}

void delete_by_id_second_hash(HashTable *hash, int id, char *name)
{
    int index = 0;
    int ide = id;
    ide--;
    if (ide == 0)
    {
        printf("Entro a  0");
        index = second_folding(name, 1);
        // cuando es 0 el id es mas 1 nomas
        // procedimiento para id 1
    }
    else if (ide == 1)
    {
        printf("Entro a  1");
        index = second_folding(name, 2);
        // procedimiento para id 2
    }
    else if (ide > 2)
    {
        printf("Entro a  > 2");
        index = second_folding(name, ide * 2);
    }

    // int index = second_folding(name, id);
    printf("Folding %d \n", index);
    // int ciclo = 0;
    while (1)
    {
        if (comparar(hash->table[index]->name, name) == 0)
        {
            printf("Pelicula encontrada, se eliminara la pelicula con el id: %d\n", id);
            printMovie(hash->table[index]); // imprime la pelicula
            hash->table[index]->name = NULL;
            hash->table[index]->release_date = 0;
            hash->table[index]->rating = 0;
            hash->amount_data--;
            break;
        }

        index = rehash(index, hash->size, 1);
        printf("Rehash %d\n", index);
    }
    return;
    /*
    while (1)
    {
        if (hash->table[index] == NULL)
        {
            printf("espaciko nulo \n");
            continue; // si es nulo continua
        }
        if (hash->table[index] != NULL && strcmp(hash->table[index]->name, name) == 0)
        {
            printf("Pelicula encontrada, se eliminara la pelicula con el id: %d\n", id);
            printMovie(hash->table[index]); // imprime la pelicula
            hash->table[index]->name = NULL;
            hash->table[index]->release_date = 0;
            hash->table[index]->rating = 0;
            hash->amount_data--;
            break; // Salir del bucle
        }
        index = rehash(index, hash->size, 1);
        printf("Rehash %d\n", index);
    }
    return;
    */
    /*
        while (hash->table[index] != NULl && (hash->table[index]->name, name) != 0)
        {
            index = rehash(index, hash->size, 1);
            printf("Rehash %d\n", index);
        }
        // int encontro = 0;
        // rehash(index, hash->size, 1);

        if (strcmp(hash->table[index]->name, name) == 0)
        {
            printf("Es igual\n");
            printMovie(hash->table[index]);
            hash->table[index]->name = NULL;
            hash->table[index]->release_date = 0;
            hash->amount_data--;
            hash->table[index]->rating = 0;
            return;c
        }
        * /
    */
}

int comparar(char *name_1, char *name_2)
{
    if (name_1 == NULL)
    {
        return 1;
    }
    else if (strcmp(name_1, name_2) == 0)
    {
        return 0;
    }
    return 1;
}
int second_folding(char *name, int data_size)
{
    int index = 0;
    int i = 0;
    while (name[i] != '\0')
    {
        index += name[i]; // se suma el valor de cada caracter
        i++;              // se aumenta el contador
    }
    // printf("Tam de la suma de letras %d\n", index);
    //  int op = index % data_size; // se obtiene el modulo de la division
    //   printf("%d\n", op);
    return index % data_size; // se retorna el modulo de la division o sea el hash
}
void delete_by_name_second_hash(HashTable *hash, char *name)
{
    HashTable *temp_array = inicializate_second_hash(); // array temporal de hash para almacenar las opcciones que tengan el mismo nombre
    for (int i = 0; i < hash->size; i++)
    {
        if (hash->table[i]->name == NULL)
        {
            continue;
        }
        if (strcmp(hash->table[i]->name, name) == 0)
        {
            // printf("Tam de temp, %d\n", temp_array->amount_data);
            temp_array->table[temp_array->amount_data] = hash->table[i];
            temp_array->amount_data++;
            duplicate_hash_table(&temp_array); // reservamos la memoria
                                               // hash->table[i]->name = NULL;
            // printMovie(hash->table[i]);        // imprime la pelicula
        }
    }
    if (temp_array->amount_data == 0)
    {
        printf("La pelicula no existe\n");
        return;
    }
    else if (temp_array->amount_data == 0)
    {
        printMovie(temp_array->table[0]); // imprime la pelicula
                                          // delete_alternative(hash, second_hash, temp_array->table[0]);
        temp_array->table[0]->name = NULL;
        temp_array->table[0]->release_date = 0;
        temp_array->table[0]->rating = 0;
        temp_array->amount_data--;
        // free(temp_array->table[0]);
        return;
    }
    // printf("Tam de temp, %d\n", temp_array->size);
    int index = 0;
    printf("Cual de las peliculas desea eliminar\n");
    for (int i = 0; i < temp_array->amount_data; i++)
    {
        printf("ID-[%d]", i);
        printMovie(temp_array->table[i]); // imprime la pelicula
    }
    scanf("%d", &index);
    // printf("Tam de temp, %d\n", temp_array->size);
    if (index > temp_array->size)
    {
        printf("Opcion no valida\n, Intentelo de");
        return;
    }
    delete_alternative(hash, temp_array, index);
    return;
    // Movie *temp_movie = NULL;
    for (int i = 0; i < hash->size; i++)
    {
        if (strcmp(hash->table[i]->name, name) == 0 && temp_array->table[index]->id == hash->table[i]->id)
        {
            printf("Pelicula encontrada, se eliminara la pelicula con el nombre: %s\n", name);
            printMovie(hash->table[i]); // imprime la pelicula
            // delete_alternative(hash, , temp_array->table[0]);
            printf("\n");
            temp_array->table[index]->name = NULL;
            temp_array->table[index]->release_date = 0;
            temp_array->table[index]->rating = 0;
            temp_array->amount_data--;
            // free(hash->table[i]->name);
            // free(te);
            // printMovie(hash->table[i]);
            return;
        }
    }
}

void delete_alternative(HashTable *hash, HashTable *temp_array, int index)
{
    for (int i = 0; i < hash->size; i++)
    {
        if (temp_array->table[index]->id == hash->table[i]->id)
        {
            // printf("Pelicula encontrada, se eliminara la pelicula con el nombre: %s\n", name);
            printMovie(hash->table[i]); // imprime la pelicula
            // delete_alternative(hash, second_hash, temp_array->table[0]);
            printf("\n");
            temp_array->table[index]->name = NULL;
            temp_array->table[index]->release_date = 0;
            temp_array->table[index]->rating = 0;
            temp_array->amount_data--;
            // free(hash->table[i]->name);
            // free(te);
            // printMovie(hash->table[i]);
            return;
        }
    }
}
void duplicate_hash_table(HashTable **hash)
{
    int i = 0;
    int new_size = (*hash)->amount_data * 2;

    // hash->table = (Movie **)realloc(hash->table, new_size * sizeof(Movie *));
    // printf("--NEW SIZE---   %d--\n", new_size); // se duplica el tamaño de la tabla
    for (i = (*hash)->size; i < new_size; i++) // creamos por 2 por que se debe llevar el .25 de carga o sea que si metemos 1 llevamos el 25% de carga
    {
        // printf("%d\n", i);
        (*hash)->table[i] = (Movie *)calloc(1, sizeof(Movie)); // RESERVA DE MEMORIA
        (*hash)->table[i]->name = NULL;
        (*hash)->table[i]->release_date = 0;
        (*hash)->table[i]->rating = 0;
        (*hash)->table[i]->id = i;
        (*hash)->size++;
    }
    // printf("FIN DE ESTA IRTEACION\n");
}

int first_hash_space(HashTable *hash)
{
    int i = 0;
    for (i = 0; i < SIZE_DATA; i++)
    {
        if (hash->table[i]->name == NULL)
        {
            return i;
        }
    }
    return -1;
}

void search_movie_id(HashTable *hash, int id)
{
    if (id > hash->amount_data) // es decir la pelicula no existe
    {
        printf("La pelicula no existe\n");
        return;
    }
    printMovie(hash->table[id]);
    return;
}

void search_movie_name(HashTable *second_hash, char *name_search)
{
    // printf("%s\n", name_search);
    printf("---------------------\n");
    HashTable *temp_array = inicializate_second_hash();
    // un array emporal para el arreglo de movies igual

    for (int i = 0; i < second_hash->amount_data; i++) // se recorre por el numeor de elementos que puede tener
    {
        // printf("%d\n", i);
        if (second_hash->table[i]->name != NULL) // si no es nulo , utilizamos nombre por que si utilizamos el index como tal ese ya tiene su espacio de memoria
        {
            if (strcmp(second_hash->table[i]->name, name_search) == 0) // si el nombre es igual
            {
                temp_array->table[temp_array->amount_data] = second_hash->table[i]; // se agrega a la tabla temporal
                // printMovie(second_hash->table[i]);
                temp_array->amount_data++; // se imprime
                duplicate_hash_table(&temp_array);
            }
        }
    }
    if (temp_array->amount_data == 0)
    {
        printf("La pelicula no existe\n"); // de lo contrario la pelicula no existe
        return;
    }
    else if (temp_array->amount_data > 0)
    {
        printf("Peliculas con el mismo nombre\n");
        for (int i = 0; i < temp_array->amount_data; i++)
        {
            printMovie(temp_array->table[i]); // imprime la pelicula
        }
    }
    // free(temp_array);
    delete_hash(temp_array);
    //  return;
}
void print_hastable(HashTable *hash)
{
    // int i = 0;
    printf("ID | NOMBRE                                          | FECHA | CALIFICACION\n");
    for (int i = 0; i < hash->size; i++)
    {
        if (hash->table[i] == NULL || hash->table[i]->name == NULL || hash->table[i] == NULL)
        {
            printf("-------------------------------------------------------------------------\n");
            printf("  | Espacio vacio |\n");
            // printf("%d", i);
            continue;
        }
        printf("-------------------------------------------------------------------------\n");
        // printf("[%d]", i);
        printf("|");
        printMovie(hash->table[i]);
    }
    printf("-------------------------------------------------------------------------\n");
    // printf("%d",i);
}

int folding(Movie *movie, int data_size) // funcion de folding
{                                        // esta funcion se encarga de hacer el hash
    int index = 0;
    int i = 0;
    char *name = movie->name;
    while (name[i] != '\0')
    {
        index += name[i]; // se suma el valor de cada caracter
        i++;              // se aumenta el contador
    }
    printf("Tam de la suma de letras %d\n", index);
    // int op = index % data_size; // se obtiene el modulo de la division
    //  printf("%d\n", op);
    return index % data_size; // se retorna el modulo de la division o sea el hash
}
int rehash(int index, int data_size, int k)
{
    return (index + (k * k)) % data_size; // siendo la formula de sondeo cuadratico i + k^2 % mod tamaño de la tabla
}

char *strdup(const char *s)
{
    // Determina la longitud de la cadena original
    size_t len = strlen(s);

    // Asigna memoria para la nueva cadena, incluyendo el carácter nulo de terminación
    char *new_str = (char *)malloc((len + 1) * sizeof(char));

    // Verifica si la asignación de memoria fue exitosa
    if (new_str == NULL)
    {
        return NULL; // Si no hay suficiente memoria, devuelve NULL
    }

    // Copia la cadena original a la nueva ubicación
    strcpy(new_str, s);

    // Devuelve el puntero a la nueva cadena
    return new_str;
}

void delete_hash(HashTable *hash)
{
    for (int i = 0; i < hash->amount_data; i++)
    {
        if (hash->table[i]->name != NULL)
        {
            continue;
        }
        free(hash->table[i]); // liberamos el espacio de memoria ahi
    }
    free(hash->table);
}

Movie **create_movies(void) // FUNCION QUE CREA PELICULAS
{
    Movie movies[SIZE_DATA] =
        {
            {1, "Blade Runner 2049\0", 2017, 80},
            {2, "Interstellar\0", 2014, 87},
            {3, "Mad Max: Fury Road\0", 2015, 81},
            {4, "Children of Men\0", 2006, 79},
            {5, "Inception\0", 2010, 88},
            {6, "Tenet\0", 2020, 73},
            {7, "Once Upon a Time... In Hollywood\0", 2019, 76},
            {8, "Inglourious Basterds\0", 2009, 84},
            {9, "The Lord of the Rings: The Return of the King\0", 2003, 90},
            {10, "The Wolf of Wall Street\0", 2013, 82},
            {11, "Disturbia\0", 2007, 68},
            {12, "Dunkirk\0", 2017, 78},
            {13, "Troy\0", 2004, 73},
            {14, "The Dark Knight\0", 2008, 90},
            {15, "Forrest Gump\0", 1994, 88},
            {16, "Fight Club\0", 1999, 88},
            {17, "Star Wars: Episode V - Empire Strikes Back\0", 1980, 87},
            {18, "The Silence of the Lamps\0", 1991, 86},
            {19, "Saving Private Ryan\0", 1998, 86},
            {20, "The Departed\0", 2006, 85},
            {21, "Whiplash\0", 2014, 85},
            {22, "Spider-Man: Into the Spider-Verse\0", 2018, 85},
            {23, "Avengers: Infinity War\0", 2018, 84},
            {24, "Django Unchained\0", 2012, 85},
            {25, "The Ministry of Ungentlemanly Warfare\0", 2024, 73},
            {26, "Godzilla x Kong: The New Empire\0", 2024, 65},
            {27, "Monkey Man\0", 2024, 71},
            {28, "Road House\0", 2024, 62},
            {29, "Rebel Moon - Part Two: The Scargiver\0", 2024, 52},
            {30, "Wish\0", 2023, 56},
            {31, "Anyone But You\0", 2023, 62},
            {32, "The Fall Guy\0", 2024, 74},
            {33, "The Bricklayer\0", 2023, 51},
            {34, "Anatomy of a Fall\0", 2023, 77},
            {35, "Hit man\0", 2023, 77},
            {36, "Glass\0", 2019, 66},
            {37, "Barbie\0", 2023, 68},
            {38, "Stolen\0", 2024, 56},
            {39, "Madame Web\0", 2024, 38},
            {40, "Joker\0", 2019, 84},
            {41, "The Shawshank Redemption\0", 1994, 93},
            {42, "Pulp Fiction\0", 1994, 92},
            {43, "Titanic\0", 1997, 89},
            {44, "The Matrix\0", 1999, 87},
            {45, "The Sixth Sense\0", 1999, 85},
            {46, "Gladiator\0", 2000, 86},
            {47, "Memento\0", 2000, 85},
            {48, "The Lord of the Rings: The Fellowship of the Ring\0", 2001, 88},
            {49, "A Beautiful Mind\0", 2001, 86},
            {50, "Spirited Away\0", 2001, 89},
            {51, "The Lord of the Rings: The Two Towers\0", 2002, 89},
            {52, "Finding Nemo\0", 2003, 90},
            {53, "The Incredibles\0", 2004, 89},
            {54, "Eternal Sunshine of the Spotless Mind\0", 2004, 88},
            {55, "Million Dollar Baby\0", 2004, 87},
            {56, "Brokeback Mountain\0", 2005, 87},
            {57, "Crash\0", 2004, 78},
            {58, "Pan's Labyrinth\0", 2006, 89},
            {59, "The Prestige\0", 2006, 88},
            {60, "No Country for Old Men\0", 2007, 90},
            {61, "There Will Be Blood\0", 2007, 89},
            {62, "WALL-E\0", 2008, 89},
            {63, "Slumdog Millionaire\0", 2008, 88},
            {64, "The Dark Knight\0", 2008, 90},
            {65, "Up\0", 2009, 88},
            {66, "Avatar\0", 2009, 83},
            {67, "Inception\0", 2010, 88},
            {68, "Toy Story 3\0", 2010, 87},
            {69, "Black Swan\0", 2010, 85},
            {70, "The Social Network\0", 2010, 88},
            {71, "The King's Speech\0", 2010, 87},
            {72, "The Artist\0", 2011, 88},
            {73, "Hugo\0", 2011, 87},
            {74, "The Help\0", 2011, 81},
            {75, "The Avengers\0", 2012, 85},
            {76, "Django Unchained\0", 2012, 87},
            {77, "Life of Pi\0", 2012, 86},
            {78, "Gravity\0", 2013, 87},
            {79, "12 Years a Slave\0", 2013, 88},
            {80, "Her\0", 2013, 89},
            {81, "Boyhood\0", 2014, 87},
            {82, "Birdman or (The Unexpected Virtue of Ignorance)\0", 2014, 88},
            {83, "The Grand Budapest Hotel\0", 2014, 87},
            {84, "Spotlight\0", 2015, 88},
            {85, "Mad Max: Fury Road\0", 2015, 90},
            {86, "The Revenant\0", 2015, 88},
            {87, "La La Land\0", 2016, 89},
            {88, "Arrival\0", 2016, 88},
            {89, "Moonlight\0", 2016, 88},
            {90, "Get Out\0", 2017, 87},
            {91, "Dunkirk\0", 2017, 89},
            {92, "The Shape of Water\0", 2017, 87},
            {93, "Three Billboards Outside Ebbing, Missouri\0", 2017, 88},
            {94, "Coco\0", 2017, 89},
            {95, "Call Me by Your Name\0", 2017, 88},
            {96, "Lady Bird\0", 2017, 87},
            {97, "Bohemian Rhapsody\0", 2018, 88},
            {98, "A Star is Born\0", 2018, 87},
            {99, "Black Panther\0", 2018, 88},
            {100, "Parasite\0", 2019, 89},
            {101, "Jojo Rabbit\0", 2019, 87},
            {102, "Joker\0", 2019, 86},
            {103, "Once Upon a Time... In Hollywood\0", 2019, 88},
            {104, "1917\0", 2019, 88},
            {105, "The Irishman\0", 2019, 87}};

    Movie **Pmovies = (Movie **)calloc(SIZE_DATA, sizeof(Movie *)); // RESERVA DE MEMORIA
    int i;
    for (i = 0; i < SIZE_DATA; i++)
    {
        Pmovies[i] = (Movie *)calloc(1, sizeof(Movie)); // RESERVA DE MEMORIA
        *(Pmovies[i]) = movies[i];                      // ASIGNACION DE VALORES
    }
    return Pmovies;
}

Movie *getMovie(Movie **movies, int index)
{
    if (index >= 0 && index <= (SIZE_DATA - 1)) // VALIDACION DE INDICE
        return movies[index];                   // RETORNO DE PELICULA
    else
        return NULL; // RETORNO DE NULO
}

void printMovie(Movie *movie)
{
    if (movie == NULL || movie->name == NULL)
    {
        printf("NULL\n");
        return;
    }
    printf("%-3d | %-50s | %d | %d |\n", movie->id, movie->name, movie->release_date, movie->rating); // IMPRESION DE PELICULA
    // printf("%-2d | %-48s | %d | %d",pelicula->id,pelicula->nombre,pelicula->fecha,pelicula->calificacion);
}