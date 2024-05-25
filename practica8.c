#ifndef QUEUES_H
#define QUEUES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct dato
{
    char *nombre;
    short int paginas;
} Dato;

typedef struct nodo
{
    Dato *archivo;
    struct nodo *sig;
} Nodo;

typedef struct cola
{
    Nodo *inicio;
    Nodo *fin;
    short int cantidad_nodos;
    struct cola *sig;
} Cola;

typedef struct cola_2 // SIENDO ESTE EL ARREGLO DE COLAS
{
    Cola *inicio;
    Cola *fin;
    short int cantidad_colas;
} Cola_2;

typedef struct stack
{
    Cola *cima;
    int lenght;
    int actual_lenght;
} Stack;

#endif
// FUNCIONES DE INICIALIZAR
Cola_2 *initialize_array_queques(void);
Cola *initialize_queques(void);

// FUNCIONES DE ACCIONES
Dato *make_data(void);

void print_queque(Cola_2 *bigQueque);
void add_new_file(Cola_2 *Big_queque, Dato *file);
void all_file_deleter(Cola_2 *Big_queque);
void file_procesator(Cola_2 *Big_queque);
int number_comparation(int a, int b);
void changue_priority(Cola_2 *Big_queque);
void delect_selected_queque(Cola_2 *Big_queque, int position);
void print_insert(Cola_2 *Big_queque);
void pint_obtain_subqueque(Cola_2 *Big_queque, int positicion);
// FUNCIONES BASICAS DE COLA
void push(Cola *queque, Dato *elemento);
int vacia(Cola *queque);
Dato *pop(Cola *queque);
Cola *big_pop(Cola_2 *big_queque);
void big_push(Cola_2 *queque, Cola *elemento);
int obtain_max_value(Cola_2 *Bigqueque);
int obtain_min_value(Cola_2 *Bigqueque, int max_value);
// int obtain_perfect_position(Cola_2 *Bigqueque, int valor_nuevo);
int match_values(Cola_2 *Bigqueque, int page_number);
// FUNCIONES BASICAS PARA PILA;
void push_stack(Stack *stack, Cola *queque);
Cola *pop_stack(Stack *stack);

int main()
{
    // Iniciamos el arreglo de colas
    // Cola_2 *arreglo_de_colas = NULL; //
    int op = 0;
    Dato *temp = NULL;
    int correr_progama = 0;
    int priority = 0;
    int ciclo_while = 0;
    // Cola *queque = initialize_queques(); // inicializamos la cola
    Cola_2 *bigQueque = initialize_array_queques();
    int file_selector = 0;
    int file_selector_2 = 0;
    while (correr_progama == 0)
    {

        printf("[0]-CAMBIAR PRIORIDAD\n");
        printf("[1]-MOSTRAR COLA DE IMPRESION\n");
        printf("[2]-AGREGAR ARCHIVO\n");
        printf("[3]-ELIMINAR ARCHIVO\n");
        printf("[4]-ELIMINAR TODO LOS ARCHIVOS\n");
        printf("[5]-PROCESAR/IMPRIMIR ARCHIVO\n");
        printf("[6]-TERMINAR PROGAMA\n");
        scanf("%d", &op);
        switch (op)
        {
        case 0:                //----------------------------------------PENDIENTE----------------------------------------
            if (priority == 0) // si la prioridad esta en normal (menor a mayor)
            {
                printf("Cambiando prioridad\n");
                printf("Cola antes del cambio de prioridad\n");
                print_queque(bigQueque);
                printf("\n\n\n");
                printf("Cola despues del cambio de prioridad\n");
                changue_priority(bigQueque);
                print_queque(bigQueque);
                priority++;
                break;
            }
            else // si la priority es dif a 0 o sea que esta invertidaa
            {
                printf("Cambiando prioridad\n");
                printf("Cola antes del cambio de prioridad\n");
                print_queque(bigQueque);
                printf("\n\n\n");
                printf("Cola despues del cambio de prioridad\n");
                changue_priority(bigQueque);
                print_queque(bigQueque);
                priority--; // para llevar registrod e si esta o no esta en este estado

                break;
            }

            break;
        case 1: //----------------------------------------COMPLETADA----------------------------------------
            if (bigQueque->cantidad_colas == 0)
            {
                printf("No hay archivos en la cola\n");
                break;
            }
            print_queque(bigQueque);
            break;
        case 2: //----------------------------------------COMPLETADA----------------------------------------
            temp = make_data();
            if (priority == 1) // o sea esta invertido
            {
                changue_priority(bigQueque);
                add_new_file(bigQueque, temp);
                changue_priority(bigQueque);
                print_queque(bigQueque);
                break;
            }
            // push(queque,temp);
            add_new_file(bigQueque, temp);
            // push(queque,make_data());
            // push(queque,make_data());

            print_queque(bigQueque);
            break;
        case 3: //----------------------------------------PENDIENTE----------------------------------------
            while (ciclo_while == 0)
            {

                print_insert(bigQueque);
                printf("SELECCIONE QUE ARCHIVO QUIERE ELIMINAR\n");
                scanf("%d", &file_selector);
                if (file_selector > bigQueque->cantidad_colas || file_selector < 0)
                {
                    printf("Ingrese un valor valido\n");
                    break;
                }
                printf("Desea eliminar toda la lista o solo un archivo dentro de la lista");

                delect_selected_queque(bigQueque, file_selector);
                print_queque(bigQueque);
            }
            break; // pint_obtain_subqueque(bigQueque,file_selector_2);
        case 4:    //----------------------------------------COMPLETADA----------------------------------------
            if (bigQueque->cantidad_colas == 0)
            {
                printf("No hay archivos en la cola\n");
                break;
            }
            all_file_deleter(bigQueque);
            break;
        case 5: //----------------------------------------COMPLETADA----------------------------------------
            file_procesator(bigQueque);
            print_queque(bigQueque);
            break;
        case 6: //----------------------------------------COMPLETADA----------------------------------------
            correr_progama = 1;
            break;

        default:
            printf("Ingrese una opccion valida\n");
            break;
        }
    }

    return 0;
}

//----------------------------------- ----------------------------------- FUNCIONES DE INICIALIZAR----------------------------------- -----------------------------------
Cola_2 *initialize_array_queques(void)
{
    Cola_2 *initialize_array_queques = (Cola_2 *)malloc(sizeof(Cola_2));
    initialize_array_queques->inicio = initialize_queques();
    initialize_array_queques->cantidad_colas = 0;
    return initialize_array_queques;
}

Cola *initialize_queques(void) // funcion que inicializa la cola para usarse
{
    Cola *queque_initialize = (Cola *)malloc(sizeof(Cola));
    if (queque_initialize == NULL)
    {
        printf("Error alocando la memoria\n");
        return NULL;
    }
    queque_initialize->cantidad_nodos = 0;
    queque_initialize->fin = NULL;
    queque_initialize->inicio = NULL;
    queque_initialize->sig = NULL;
    return queque_initialize;
}

//----------------------------------- ----------------------------------- // FUNCIONES DE ACCIONES ----------------------------------- -----------------------------------

Dato *make_data(void)
{
    char nombre[30];
    int num;
    printf("Ingrese el nombre del archivo\n");
    scanf("%s", nombre);
    fflush(stdin);
    printf("Ingrese el numero de paginas\n");
    scanf("%d", &num);
    Dato *new_data = (Dato *)malloc(sizeof(Dato));
    new_data->nombre = (char *)malloc(strlen(nombre) + 1); // creamos memoria dinamica del tam de nombre
    // la memoria dinamica es nescesaria ya que el nombre puede tener muchos caracteres y es una memoria que no sabemos hasta que ejecutamos el progama
    strcpy(new_data->nombre, nombre);
    new_data->paginas = num;
    return (new_data);
}

void print_insert(Cola_2 *Big_queque) // funcion para imprimir en el formato de insertar
{
    Cola *pop_queque = NULL;
    Cola_2 *auxiliar_big_queque = initialize_array_queques();
    int i = 0;
    while (Big_queque->cantidad_colas != 0)
    {
        pop_queque = big_pop(Big_queque); // sacamos el dato
        printf("[%d]-[%s]-P_NUMBER-[%d]\n", i, pop_queque->inicio->archivo->nombre, pop_queque->inicio->archivo->paginas);
        big_push(auxiliar_big_queque, pop_queque); // metemos ahi el archivo
        i++;
    }
    while (auxiliar_big_queque->cantidad_colas != 0)
    {
        big_push(Big_queque, big_pop(auxiliar_big_queque)); // lo regremos todo a big queque
    }
    printf("\n"); // regresamos
}
void pint_obtain_subqueque(Cola_2 *Big_queque, int positicion)
{
    Cola *pop_queque = NULL;
    Cola_2 *auxiliar_big_queque = initialize_array_queques();
    Dato *pop_data = NULL; // para almacenar el dato
    Cola *auxiliar_queque = NULL;
    int i = 0;
    for (int j = 0; j < positicion; j++)
    {
        pop_queque = big_pop(Big_queque);          // sacamos el dato
        big_push(auxiliar_big_queque, pop_queque); // metemos ahi el archivo
    }
    pop_queque = big_pop(Big_queque);       // sacamos el dato que el sig sera el que buscamos
    while (pop_queque->cantidad_nodos != 0) // sacamos cada nodo // vaciamos ese dato
    {
        pop_data = pop(pop_queque);                                                                     // sacamos el dato
        printf("ID- [%D]--File Name: %s || Page Number: %d\n", i, pop_data->nombre, pop_data->paginas); // mo mostramos
        push(auxiliar_queque, pop_data);                                                                // lo metemos a la cola}
    }
    while (auxiliar_queque->cantidad_nodos != 0) // regresamos los nodos a la cola
    {
        push(pop_queque, pop(auxiliar_queque)); // regresamos los nodos a la cola
    }
    while (Big_queque->cantidad_colas != 0)
    {
        pop_queque = big_pop(Big_queque);          // sacamos el dato
        big_push(auxiliar_big_queque, pop_queque); // metemos ahi el archivo
    }
    while (auxiliar_big_queque->cantidad_colas != 0)
    {
        big_push(Big_queque, big_pop(auxiliar_big_queque)); // lo regremos todo a big queque
    }
    printf("\n"); // regresamos
}
void delect_selected_queque(Cola_2 *Big_queque, int position)
{
    Cola_2 *auxiliar_big_queque = initialize_array_queques();
    Cola *pop_queque = NULL;
    if (position == 0)
    {
        pop_queque = big_pop(Big_queque); // nomas no sacamos uno nomas
        free(pop_queque);                 // liberamos la memoria
        return;                           // solo eliminamos el primero
    }
    else
    {
        for (int i = 0; i < position; i++) // esto nos pondra en la posicion 1 antes del dato a sacar
        {
            pop_queque = big_pop(Big_queque);          // sacamos el dato
            big_push(auxiliar_big_queque, pop_queque); // lo metemos
        }
        pop_queque = big_pop(Big_queque);       // sacamos el dato
        free(pop_queque);                       // liberamos la memoria
        while (Big_queque->cantidad_colas != 0) // TODO ESTE PROCESO PODRIA SER UNA FUNCION Y ASIA HORRARIA MUCHO ESPACIOD ENTRO DEL CODIGO
        {
            big_push(auxiliar_big_queque, big_pop(Big_queque)); // metemos ahi todo los archivos
        }
        while (auxiliar_big_queque->cantidad_colas != 0)
        {
            big_push(Big_queque, big_pop(auxiliar_big_queque)); // regresamos todo a la cola principal,
        }
    }
}

void file_procesator(Cola_2 *Big_queque)
{
    Cola *pop_queque = NULL;
    Dato *aux = NULL;

    if (Big_queque->cantidad_colas == 0)
    {
        printf("No hay archivos en la cola\n");
        return;
    }
    Cola_2 *auxiliar_big_queque = initialize_array_queques(); // creamos un nodo auxiliar

    pop_queque = big_pop(Big_queque);    // sacamos 1 solo dato
    if (pop_queque->cantidad_nodos != 0) // se saca y se muestra que hay ahi
    {
        printf("---------INFORMACION DEL ARCHIVO ELIMINADO---------\n");
        aux = pop(pop_queque);
        printf("Nombre del Archivo: %s || ", aux->nombre);          // se muestra el dato a eliminar
        printf("Num de paginas del Archivo: %d  \n", aux->paginas); // se muestra el dato a eliminar
    }

    if (pop_queque->cantidad_nodos > 0) // si es mayor a 0 entonces lo devolvemos a la cola, de lo contarrion nose hace nada
    {
        big_push(auxiliar_big_queque, pop_queque); // metemos ahi el archivo
    }
    else if (pop_queque->cantidad_nodos == 0) // si es 0 entonces debemos de elminar la memoria y omitir el paso de ingresarlo
    {
        free(pop_queque); // liberamos la memoria
    }
    while (Big_queque->cantidad_colas != 0)
    {
        big_push(auxiliar_big_queque, big_pop(Big_queque)); // metemos ahi todo los archivos
    }
    while (auxiliar_big_queque->cantidad_colas != 0)
    {
        big_push(Big_queque, big_pop(auxiliar_big_queque)); // regresamos todo a la cola principal,
    }
    free(auxiliar_big_queque); // liberamos la memoria
    // free(pop_queque);          // se elimina el nodo
} // mi logica de esta funcion es que no es posible eliminar un solo elemento de una sola cola ya que al momento de volver a meterlo normal, quedaria desacomodad y no igual
void all_file_deleter(Cola_2 *Big_queque)
{
    Cola *pop_queque = NULL;
    while (Big_queque->cantidad_colas != 0)
    {
        pop_queque = big_pop(Big_queque);
        while (pop_queque->cantidad_nodos != 0)
        {

            pop(pop_queque); // Liberamos los datos de la cola
        }
        free(pop_queque); // Liberamos la cola
    }
    free(Big_queque); // Liberamos la estructura Cola_2
}

void print_queque(Cola_2 *bigQueque) // respetnado fifo
{
    printf("\n");
    Cola *queque_pop = NULL;            // Usa un puntero temporal a Cola
    if (bigQueque->cantidad_colas == 0) // si no hay colas
    {                                   // no hay nada que mostrar
        printf("No hay archivos en la cola\n");
        return;
    }
    Cola *queque_pop_auxiliar_one = initialize_queques(); // Usa un puntero temporal a Cola
    Cola_2 *auxiliar_big_queque = initialize_array_queques();
    while (bigQueque->cantidad_colas != 0)
    {
        queque_pop = big_pop(bigQueque);                                                                       // Sacamos la cola de la cola de colas
        printf("---------Cola de impresion con paginas---------[%d]\n", queque_pop->inicio->archivo->paginas); // imprimimos
        while (queque_pop->cantidad_nodos != 0)                                                                // para mostrar los archivos dentro de esta misma
        {
            Dato *temp = pop(queque_pop); // Sacamos el dato de la cola
            printf("File Name: %s || Page Number: %d\n", temp->nombre, temp->paginas);
            push(queque_pop_auxiliar_one, temp); // lo metemos a una cola temporal
        }
        while (queque_pop_auxiliar_one->cantidad_nodos != 0) // regresamos los nodos a la otra cola
        {
            push(queque_pop, pop(queque_pop_auxiliar_one));
        }
        big_push(auxiliar_big_queque, queque_pop); // Regresamos la cola a la cola de colas
    }
    while (auxiliar_big_queque->cantidad_colas != 0) // regresamos todas las colas a la cola de colas
    {
        big_push(bigQueque, big_pop(auxiliar_big_queque)); // regresamos todo a la original
    }
    free(queque_pop_auxiliar_one); // liberamos la memoria
    free(auxiliar_big_queque);     // liberamos la memoria
    printf("\n");
    return;
}

void add_new_file(Cola_2 *Big_queque, Dato *file) // añadir un dato dependiendo el orden                FUNCION PESADA
{
    // int max_value = 0;
    // int counter=0;
    if (Big_queque->cantidad_colas == 0)
    {
        Cola *new_queque = initialize_queques(); // inicializamos la cola
        push(new_queque, file);                  // hacemos push del nuevo archivo a la nueva cola
        Big_queque->inicio = new_queque;         // se le asigna la nueva cola como inicio
        Big_queque->fin = new_queque;            // se le asigna la nueva cola como fin

        Big_queque->cantidad_colas++;
        return;
    }

    // translate_queques = Big_queque->inicio; // toma el valor de la cola que se va ir desplzanaod
    // Cola_2 *translate_queques = NULL;
    // Cola *new_queque =NULL ; // Esta es una auxiliar
    //------ ------------------------------------verificar si no existe una igual ya------------------------------------------
    int match = match_values(Big_queque, file->paginas); // buscamos si hay un numero de paginas
    Cola_2 *auxiliar_big_queque = initialize_array_queques();
    Cola *pop_queque = initialize_queques();

    if (match == 0) // ya exiiste una pila con el mismo num de paginas
    {
        printf("Ya existe un archivo con el mismo numero de paginas\n");
        while (Big_queque->cantidad_colas != 0)
        {
            printf("entro");
            pop_queque = big_pop(Big_queque);                          // sacamos el dato
            if (file->paginas == pop_queque->inicio->archivo->paginas) // si el numero de paginas esta aqui
            {
                printf("Hace push dentro de la cola\n");
                push(pop_queque, file); // metemos ahi el archivo               // salimos
            }
            big_push(auxiliar_big_queque, pop_queque); // metemos ahi el archivo
        }
        while (auxiliar_big_queque->cantidad_colas != 0)
        {
            big_push(Big_queque, big_pop(auxiliar_big_queque)); // lo regremos todo a big queque
        }
        return;
    }
    // Como no existe ningun archivo con el mismo numero de paginas entonces se va ingresar deacuerdo el orden
    int max = obtain_max_value(Big_queque);          // obtenemos el valor maximo  antes de ingresar el nuevo
    printf("Valor maximo es de %d\n", max);          // queremos tener el valor maximo para asi poder saber  despues de cual ingresar
    int min = obtain_min_value(Big_queque, max);     // obtenemos el valor minimo antes de ingresar el nuevo
    printf("Valor minimo obtenido es %d\n", min);    // queremos tener el valor minimo para asi poder saber  despues de cual ingresar
    Cola *new_queque = initialize_queques();         // creamos una nueva cola
    push(new_queque, file);                          // metemos ahi el archivo  y ahora seguimos con el proceso
    if (number_comparation(file->paginas, max) == 1) // si el numero de paginas es mayor al maximo
    {
        printf("el dato era mayor al maximo\n");
        big_push(Big_queque, new_queque); // metemos ahi el archivo
        return;
    }
    if (number_comparation(file->paginas, min) == 0) // si el numero de paginas es menor al minimo
    {
        printf("el dato era menor al minimo\n");
        big_push(auxiliar_big_queque, new_queque); // metemos ahi el archivo
        while (Big_queque->cantidad_colas != 0)
        {
            big_push(auxiliar_big_queque, big_pop(Big_queque)); // mandamos todo a  auxiliar
        }
        while (auxiliar_big_queque->cantidad_colas != 0)
        {
            big_push(Big_queque, big_pop(auxiliar_big_queque)); // lo regremos todo a big queque
        }
        free(auxiliar_big_queque);
        return;
    }
    // el valor se quedo enmedio

    printf("el dato era enmedio\n");
    // int a = obtain_perfect_position(Big_queque, file->paginas);
    // printf("Valor perfecto para ingresar es %d", a);
    int bucle = 0;
    while (Big_queque->cantidad_colas != 0)
    {
        pop_queque = big_pop(Big_queque);                         // sacamos una cola de la cola (valgame la rebundancia)
        if (file->paginas < pop_queque->inicio->archivo->paginas) // si el numero de paginas es mayor al maximo
        {
            if (bucle == 1) // ya paso por aqui
            {
                big_push(auxiliar_big_queque, pop_queque); // metemos ahi el archivo
                continue;
            }
            big_push(auxiliar_big_queque, new_queque); // metemos ahi el archivo
            big_push(auxiliar_big_queque, pop_queque); // metemos ahi el archivo
            bucle++;
            continue; // en teoria debera de insertarlo donde debe ya que a la primera que sea mayor lo insertera, y este dato por las anteriores
            // verificaciones no puede ser, igual o mayor al maximo o menor al maximo asi que debe de estar en la priemra que encuentre
        }
        big_push(auxiliar_big_queque, pop_queque); // lo metemos al auxiliar
    }

    while (auxiliar_big_queque->cantidad_colas != 0)
    {
        big_push(Big_queque, big_pop(auxiliar_big_queque)); // regresmaos toda las colas al anterior
    }
    free(auxiliar_big_queque);
    // free(pop_queque);
    return;
}
//----------------------------------- ---------------------------FUNCIONES DE OBTENER/MANEJAR POSICIONES O VALORES----------------------------------- -----------------------------------
int number_comparation(int a, int b)
{
    if (a >= b)
    {
        return 1;
    }
    return 0;
}
/*
int obtain_perfect_position(Cola_2 *Bigqueque, int valor_nuevo)
{
    Cola *pop_cola = NULL;
    Cola_2 *auxiliar_queque = initialize_array_queques();
    int max = 0;
    int max_2 = 0;
    while (Bigqueque->cantidad_colas != 0)
    {
        pop_cola = big_pop(Bigqueque);                        // sacamos una cola de la cola (valgame la rebundancia)                                                                      // sacamos el segundo valor que es como el siguiente
        if (valor_nuevo > pop_cola->inicio->archivo->paginas) // si el nuevo valor es > que el ant sacado y < que el siguiente a sacar entonces se tiene que
        {
            max = pop_cola->inicio->archivo->paginas;
        }
        if (valor_nuevo > max && valor_nuevo < pop_cola->inicio->archivo->paginas)
        {
            max_2 = pop_cola->inicio->archivo->paginas;
        }
        big_push(auxiliar_queque, pop_cola); // lo metemos al auxiliar
    }

    while (auxiliar_queque->cantidad_colas != 0)
    {
        big_push(Bigqueque, big_pop(auxiliar_queque)); // regresmaos toda las colas al anterior
    }

    return max_2;
}
*/
int obtain_max_value(Cola_2 *Bigqueque)
{
    Cola *pop_cola = NULL;
    Cola_2 *auxiliar_queque = initialize_array_queques();
    int max = 0;
    while (Bigqueque->cantidad_colas != 0)
    {
        pop_cola = big_pop(Bigqueque); // sacamos una cola de la cola (valgame la rebundancia)
        if (max < pop_cola->inicio->archivo->paginas)
        {
            max = pop_cola->inicio->archivo->paginas;
        }
        big_push(auxiliar_queque, pop_cola); // lo metemos al auxiliar
    }

    while (auxiliar_queque->cantidad_colas != 0)
    {
        big_push(Bigqueque, big_pop(auxiliar_queque)); // regresmaos toda las colas al anterior
    }

    return max;
}
int obtain_min_value(Cola_2 *Bigqueque, int max_value)
{
    Cola *pop_cola = NULL;
    Cola_2 *auxiliar_queque = initialize_array_queques();
    int max = max_value;
    while (Bigqueque->cantidad_colas != 0)
    {
        pop_cola = big_pop(Bigqueque); // sacamos una cola de la cola (valgame la rebundancia)
        if (max > pop_cola->inicio->archivo->paginas)
        {
            max = pop_cola->inicio->archivo->paginas;
        }
        big_push(auxiliar_queque, pop_cola); // lo metemos al auxiliar
    }

    while (auxiliar_queque->cantidad_colas != 0)
    {
        big_push(Bigqueque, big_pop(auxiliar_queque)); // regresmaos toda las colas al anterior
    }

    return max;
}
int match_values(Cola_2 *Bigqueque, int page_number) // funcion para encontrar si hay un valor igual ( una cola con el mismo num de paginas)
{
    Cola *pop_cola = NULL;
    Cola_2 *auxiliar_queque = initialize_array_queques();
    int max = 1;
    while (Bigqueque->cantidad_colas != 0)
    {
        pop_cola = big_pop(Bigqueque); // sacamos una cola de la cola (valgame la rebundancia)
        if (page_number == pop_cola->inicio->archivo->paginas)
        {
            max = 0;
        }
        big_push(auxiliar_queque, pop_cola); // lo metemos al auxiliar
    }

    while (auxiliar_queque->cantidad_colas != 0)
    {
        big_push(Bigqueque, big_pop(auxiliar_queque)); // regresmaos toda las colas al anterior
    }
    free(auxiliar_queque);
    return max;
}
//----------------------------------- ----------------------------------- BASICAS DE COLA----------------------------------- -----------------------------------
void push(Cola *queque, Dato *elemento)
{
    Nodo *new_Node = (Nodo *)malloc(sizeof(Nodo)); // creamos el espacio de memoria para el nuevo nodo
    if (new_Node == NULL)
    {
        printf(" Error en alocacion de la memoria\n");
        return;
    }
    new_Node->sig = NULL;
    new_Node->archivo = elemento;
    if (queque->cantidad_nodos == 0) // si es el primer nodo
    {                                // este es el primer nodo
        queque->inicio = new_Node;   // su nuevo inicio 2
        queque->fin = new_Node;      // su nuevo fin
        queque->cantidad_nodos++;    // se suma la cantidad de nodos a uno
        return;
    }
    queque->fin->sig = new_Node;
    queque->fin = new_Node;
    queque->cantidad_nodos++;
}

Dato *pop(Cola *queque)
{
    if (vacia(queque))
    {
        printf("UNDERFLOW no es posible sacar un elemeto\n");
        return NULL;
    }
    Nodo *pop_node = queque->inicio;
    Dato *data_return = pop_node->archivo;
    if (queque->cantidad_nodos == 1)
    { // es decir solo existe un nodo
        queque->cantidad_nodos--;
        queque->fin = NULL;
        queque->inicio = NULL;
        queque->sig = NULL;
        return (data_return);
    }
    queque->inicio = queque->inicio->sig; // el inicio se recorre uno
    queque->cantidad_nodos--;
    return (data_return); // se regresa el primero  que esta
}

int vacia(Cola *queque)
{
    return (queque->cantidad_nodos == 0);
}
Cola *big_pop(Cola_2 *big_queque)
{
    if (big_queque->cantidad_colas <= 0)
    {
        printf("UNDERFLOW NO ES POSIBLE SACAR UN ELEMENTO\n");
        return NULL;
    }
    Cola *pop_queque = big_queque->inicio;
    if (big_queque->cantidad_colas == 1)
    {
        big_queque->cantidad_colas--;
        big_queque->fin = NULL;
        big_queque->inicio = NULL;
        return (pop_queque);
    }
    big_queque->cantidad_colas--;
    big_queque->inicio = big_queque->inicio->sig;
    pop_queque->sig = NULL;
    return (pop_queque);
}

void big_push(Cola_2 *queque, Cola *elemento)
{
    if (queque == NULL || elemento == NULL)
    {
        printf("Error: Cola de colas o cola de entrada no válida\n");
        return;
    }

    if (queque->cantidad_colas == 0)
    {
        // Si la cola de colas está vacía, establecemos el inicio y fin como el nuevo nodo
        queque->inicio = elemento;
        queque->fin = elemento;
        queque->cantidad_colas++;
    }
    else
    {
        // Si ya hay colas en la cola de colas, simplemente agregamos la nueva cola al final
        queque->fin->sig = elemento;
        queque->fin = elemento;
        queque->cantidad_colas++;
    }
}

//----------------------------------- ----------------------------------- BASICAS DE STACK----------------------------------- -----------------------------------

void push_stack(Stack *stack, Cola *queque)
{

    queque->sig = stack->cima; // el sig es igual a la cima
    stack->cima = queque;      // la sima es este mismo
    stack->actual_lenght++;    // sumamos la longitud
}
Cola *pop_stack(Stack *stack)
{
    if (stack->actual_lenght == 0)
    {
        printf("No es posible extraer un elemento si esta vacia la pila\n");
        return NULL;
    }
    Cola *pop_queque = stack->cima; // variable para hacer pop
    stack->cima = stack->cima->sig; // la cima es igual a la cima sig o sea se recorre
    stack->actual_lenght--;         // se resta la longitud
    return pop_queque;              // se regresa el valor
}

void changue_priority(Cola_2 *Big_queque)
{
    // Cola *pop_queque = NULL;
    Stack *stack = (Stack *)malloc(sizeof(Stack)); // creamos memoria de nuestro stack
    while (Big_queque->cantidad_colas != 0)
    {
        push_stack(stack, big_pop(Big_queque)); // sacamos el dato y lo ingresamos en el stack
    }
    while (stack->actual_lenght != 0)
    {
        big_push(Big_queque, pop_stack(stack)); // sacamos el dato y lo ingresamos en la cola
    }
    // free(stack); // liberamos la memoria del stack
    return;
}
