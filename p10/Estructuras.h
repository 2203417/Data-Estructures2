
// #include "funciones.h"

// ESTRUCTURAS

typedef struct
{
    int id;
    char *name;
    short int release_date;
    short int rating;
} Movie;

typedef int (*FunctionFolding)(Movie *);

typedef struct hashtable
{
    int size;                // DATOS QUE PUEDE CONTENER
    int amount_data;         // DATOS CONTENIDOS
    Movie **table;           // ALMACENAMIENTO
    FunctionFolding folding; // POINTER A FUNCION FOLDING
} HashTable;
