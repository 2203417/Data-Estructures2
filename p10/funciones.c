#include "funciones.h"

#include <stdio.h>
#include <stdlib.h>
#define SIZE_DATA 105
#include <string.h>

HashTable *create_id_hash_table(Movie **movies)
{
    HashTable *hash = (HashTable *)calloc(1, sizeof(HashTable)); // RESERVA DE MEMORIA 1 VEZ
    hash->size = SIZE_DATA;                                      // ASIGNACION DE VALORES
    hash->amount_data = 0;                                       // ASIGNACION DE VALORES
    hash->table = (Movie **)calloc(SIZE_DATA, sizeof(Movie *));  // RESERVA DE MEMORIA por la cantidad de datos que puede contener
    for (int i = 0; i < hash->size; i++)
    {
        hash->table[i] = (Movie *)calloc(1, sizeof(Movie)); // RESERVA DE MEMORIA
        *(hash->table[i]) = *movies[i];                     // ASIGNACION DE VALORES
        printMovie(hash->table[i]);
        hash->amount_data++;
    }

    return hash;
}

HashTable *create_second_hash_table()
{
    HashTable *hash = (HashTable *)calloc(1, sizeof(HashTable)); // RESERVA DE MEMORIA 1 VEZ
    hash->size = 0;                                              // ASIGNACION DE VALORES
    hash->amount_data = 0;                                       // ASIGNACION DE VALORES
    hash->table = (Movie **)calloc(SIZE_DATA, sizeof(Movie *));  // RESERVA DE MEMORIA por la cantidad de datos que puede contener
    hash->table[0] = (Movie *)calloc(1, sizeof(Movie));          // RESERVA DE MEMORIA
    hash->size++;                                                // AUMENTO DE ESPACIO
    // *(hash->table[i]) = *movies[i];                     // ASIGNACION DE VALORES
    // printMovie(hash->table[i]);

    return hash;
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
    // printf("%s\n", movie->name);         // ASIGNACION DE VALORES
    // printf("%d\n", movie->release_date); // ASIGNACION DE VALORES
    // printf("%d\n", movie->rating);       // ASIGNACION DE VALORES
    int index = first_hash_space(hash); // ASIGNACION DE VALORES
    // printf("%d\n", index);
    if (index == -1)
    {
        // printf("No hay espacio\n");
        // printf("%d", hash->amount_data);
        hash->table[hash->amount_data] = (Movie *)calloc(1, sizeof(Movie)); // RESERVA DE MEMORIA
        movie->id = hash->amount_data;                                      // ASIGNACION DE VALORES
        hash->table[hash->amount_data] = movie;                             // ASIGNACION DE VALORES
        // printf("%s\n", hash->table[index]->name);
        hash->amount_data++; // AUMENTO DE DATOS
        hash->size++;        // AUMENTO DE ESPACIO
        return;
    }
    else if (hash->table[index]->name == NULL)
    {
        hash->table[index] = movie; // ASIGNACION DE VALORES
        movie->id = index;          // ASIGNACION DE VALORES
        // printf("Se agrego la pelicula\n");
        // printf("%s\n", hash->table[index]->name);
        hash->amount_data++; // AUMENTO DE DATOS

        return;
    }
    return;
}
double get_load_factor(HashTable *hash)
{
    printf("AMOUNT -- %d\n", hash->amount_data);
    printf("SIZEEE %d\n", hash->size);

    // Utilizamos el tipo de dato double para mayor precisión en la división
    double factor_carga = (double)hash->amount_data / hash->size;
    // printf("Factor de carga: %.2f\n", factor_carga);
    return factor_carga;
}

void add_movie_second_hash_table(HashTable *hash, Movie *movie)
{
    duplicate_hash_table(hash);                 // duplicamos la tabla
    double load_factor = get_load_factor(hash); // obtenemos el factor de carga
    printf("Factor de carga por el momento: %.2f\n", load_factor);
    // printf("Tam de la tabla: %d\n", hash->size);
    int index = folding(movie, hash->size); // obtenemos el index donde se ingresara
    printf("[%d]\n", index);
    if (hash->table[index]->name == NULL)
    {
        printf("Se agrego la pelicula en NULL\n");
        movie->id = index;          // se asigna el id
        hash->table[index] = movie; // se agrega la pelicula
        hash->amount_data++;        // se aumenta la cantidad de datos
        return;
    }
    else
    {
        int i = 1;
        while (hash->table[index]->name != NULL) // esta ocupado el lugar asi que se reacomoda
        {

            index = rehash(index, hash->size, i); // se reacomoda
            i++;
            printf("Index rehash: %d\n", index);
        }
        hash->table[index] = movie;
        hash->amount_data++;
        return;
    }
}

void delete_by_id_first_hash(HashTable *hash, int id)
{
    for (int i = 0; i < hash->size; i++)
    {
        if (hash->table[i]->id == id)
        {
            printf("Pelicula encontrada, se eliminara la pelicula con el id: %d\n", id);
            printMovie(hash->table[i]); // imprime la pelicula
            hash->table[i]->name = NULL;
            hash->table[i]->release_date = 0;
            hash->table[i]->rating = 0;
            hash->amount_data--;
            return;
        }
    }
    printf("Pelicula no encontrada\n");
}
void delete_by_name_second_hash(HashTable *hash, char *name)
{
    HashTable *temp_array = create_second_hash_table(); // array temporal de hash para almacenar las opcciones que tengan el mismo nombre
    for (int i = 0; i < hash->amount_data; i++)
    {
        if (hash->table[i]->name == NULL)
        {
            continue;
        }
        if (strcmp(hash->table[i]->name, name) == 0)
        {
            printf("Tam de temp, %d\n", temp_array->amount_data);
            temp_array->table[temp_array->amount_data] = hash->table[i];
            temp_array->amount_data++;
            duplicate_hash_table(temp_array); // reservamos la memoria
                                              // hash->table[i]->name = NULL;
            printMovie(hash->table[i]);       // imprime la pelicula
                                              // hash->table[i]->name = NULL;
                                              // hash->table[i]->release_date = 0;
                                              // hash->table[i]->rating = 0;
                                              // hash->amount_data--;
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
        temp_array->table[0]->name = NULL;
        temp_array->table[0]->release_date = 0;
        temp_array->table[0]->rating = 0;
        temp_array->amount_data--;
        return;
    }
    printf("Tam de temp, %d\n", temp_array->size);
    int index = 0;
    printf("Cual de las peliculas desea eliminar\n");
    for (int i = 0; i < temp_array->amount_data; i++)
    {
        printf("ID-[%d]", i);
        printMovie(temp_array->table[i]); // imprime la pelicula
    }
    scanf("%d", &index);
    printf("Tam de temp, %d\n", temp_array->size);
    if (index > temp_array->size)
    {
        printf("Opcion no valida\n, Intentelo de");
        return;
    }
    for (int i = 0; i < hash->size; i++)
    {
        if (strcmp(hash->table[i]->name, name) == 0 && temp_array->table[index]->id == hash->table[i]->id)
        {
            printf("Pelicula encontrada, se eliminara la pelicula con el nombre: %s\n", name);
            printMovie(hash->table[i]); // imprime la pelicula
            hash->table[i]->name = NULL;
            hash->table[i]->release_date = 0;
            hash->table[i]->rating = 0;
            hash->amount_data--;
            return;
        }
    }
}

void duplicate_hash_table(HashTable *hash)
{
    int i = 0;
    int op = hash->amount_data * 4;

    // printf("--%d--\n", op);           // se duplica el tamaño de la tabla
    for (i = hash->size; i < op; i++) // creamos por 4 por que se debe llevar el .25 de carga o sea que si metemos 1 llevamos el 25% de carga
    {
        printf("%d\n", i);
        hash->table[i] = (Movie *)calloc(1, sizeof(Movie)); // RESERVA DE MEMORIA
        hash->table[i]->name = NULL;
        hash->table[i]->release_date = 0;
        hash->table[i]->rating = 0;
        hash->table[i]->id = 0;
        hash->size++;
        // *(hash->table[i]) = *movies[i];                     // ASIGNACION DE VALORES
        // printMovie(hash->table[i]);
    }
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
    for (int i = 0; i < SIZE_DATA; i++) // se recorre por el numeor de elementos que puede tener
    {
        // printf("%d\n", i);
        if (second_hash->table[i]->name != NULL) // si no es nulo , utilizamos nombre por que si utilizamos el index como tal ese ya tiene su espacio de memoria
        {
            if (strcmp(second_hash->table[i]->name, name_search) == 0) // si el nombre es igual
            {
                printMovie(second_hash->table[i]); // se imprime
                return;
            }
        }
    }
    printf("La pelicula no existe\n"); // de lo contrario la pelicula no existe
    return;
}
void print_hastable(HashTable *hash)
{
    printf("ID | NOMBRE                                          | FECHA | CALIFICACION\n");
    for (int i = 0; i < hash->size; i++)
    {
        printf("-------------------------------------------------------------------------\n");
        // printf("[%d]", i);
        printMovie(hash->table[i]);
    }
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
    int op = index % data_size; // se obtiene el modulo de la division
    printf("%d\n", op);
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
    printf("%-3d | %-50s | %d | %d \n", movie->id, movie->name, movie->release_date, movie->rating); // IMPRESION DE PELICULA
    // printf("%-2d | %-48s | %d | %d",pelicula->id,pelicula->nombre,pelicula->fecha,pelicula->calificacion);
}