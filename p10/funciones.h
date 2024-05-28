#include "Estructuras.h"

#define SIZE_DATA 105

Movie **create_movies(void);
void printMovie(Movie *movie);
Movie *getMovie(Movie **movies, int index);

// typedef int (*FunctionFolding)(Movie *);

HashTable *create_id_hash_table(Movie **movies);

HashTable *create_second_hash_table();

int folding(Movie *movie, int data_size);

int rehash(int index, int data_size, int k);

void print_hastable(HashTable *hash);

void search_movie_id(HashTable *hash, int id);

void search_movie_name(HashTable *second_hash, char *name_search);

void add_movie_first_hash_table(HashTable *hash, Movie *movie);

void add_movie_second_hash_table(HashTable *hash, Movie *movie);

void delete_by_id_first_hash(HashTable *hash, int id);

void delete_by_name_second_hash(HashTable *hash, char *name);

void delete_by_id_first_hash2(HashTable *hash, int id);

void duplicate_hash_table(HashTable *hash);

int first_hash_space(HashTable *hash); // funcion para buscar si hay un espacio

Movie *create_movie(char *name, int year, int rating);

char *strdup(const char *s);

double get_load_factor(HashTable *hash);