#include "Estructuras.h"

#define SIZE_DATA 105

Movie **create_movies(void);
void printMovie(Movie *movie);
Movie *getMovie(Movie **movies, int index);

// typedef int (*FunctionFolding)(Movie *);
// funciones de crear
HashTable *create_id_hash_table(Movie **movies);

HashTable *create_second_hash_table();

// funciones para imprimir

void print_hastable(HashTable *hash);

// funciones de busqueda
void search_movie_id(HashTable *hash, int id);

void search_movie_name(HashTable *second_hash, char *name_search);

Movie *create_movie_by_movie(Movie *movie);
// funciones de agregar
void add_movie_first_hash_table(HashTable *hash, Movie *movie);

void add_movie_second_hash_table(HashTable *hash, Movie *movie);

// funciones de eliminar
void delete_by_id_first_hash(HashTable *hash, HashTable *second_hash, int id);

void delete_by_id_second_hash(HashTable *hash, int id, char *name);

int second_folding(char *name, int data_size);

int comparar(char *name_1, char *name_2);

void delete_by_name_second_hash(HashTable *hash, char *name);

void delete_alternative(HashTable *hash, HashTable *temp_array, int index);

void delete_by_id_first_hash2(HashTable *hash, int id);

// funcion locota
void duplicate_hash_table(HashTable **hash);

Movie *create_movie(char *name, int year, int rating);
// ---------------------------------------------FUNCIONES DE HASH---------------------------------------------
int first_hash_space(HashTable *hash); // funcion para buscar si hay un espacio

char *strdup(const char *s);

double get_load_factor(HashTable *hash);

int folding(Movie *movie, int data_size);

int rehash(int index, int data_size, int k);

void delete_hash(HashTable *hash);