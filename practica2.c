#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// declaracion de la estructura de datos
struct datos 
{
    int numero;
    struct datos *siguiente;
    struct datos *atras;
};
// funciones
void creator(struct datos **lista,int dato)
{
    struct datos *nuevo = (struct datos*)malloc(sizeof(struct datos));
    if (nuevo == NULL)
    {
        printf("Error de asignacion de la memoria \n");
        exit(EXIT_FAILURE);
    }
    else 
    nuevo->numero = dato;
    if (*lista == NULL)
    {

        *lista = nuevo;

    }
    else 
    {
        struct datos *p = *lista; // nos ayudamos de la struct p
            while(p->siguiente != NULL)
            {
                p = p->siguiente;
            }
            p->siguiente = nuevo; // nuevo = p->siguiente || o sea nuevo sera la head
            nuevo->atras = p; //  nuevo->atras = p  siendo p el penultimo valor y como nuevo es la (nueva head) su cola es
            // el penumiltimo dato
    }
}
void imprimir(struct datos *lista)
{
    struct datos *imprimir = lista;
    //printf("\nEntró a imprimir\n");

    while (imprimir != NULL)
    {
        if (imprimir->atras == NULL)
        {
        printf("\nNULL-->");
        }
        else
        printf(" <-%d ",imprimir->atras->numero);
        printf(" <-[%d] ",imprimir->numero);
        imprimir = imprimir->siguiente;

    }
            if (imprimir == NULL)
        {
            printf("<- Null\n");
        }    
}
void liberador_memory(struct datos *lista)
{
    struct datos *liberador_sig = lista;
    struct datos *liberador_anterior = lista;
    while (liberador_sig != NULL)
    {
        liberador_anterior = liberador_sig;
        liberador_sig = liberador_sig->siguiente;
        free(liberador_anterior);
    }


}

void bubblesort(struct datos *lista) // un clasico bubblesort pero de listas .-.
{
    struct datos *actual = lista;
    //printf("\nNumero actua--- %d",actual->numero);
    struct datos *siguiente = lista;
    struct datos *inicio = lista;
    siguiente = siguiente->siguiente;
    int temp =0; //nesceistaremos ayuda de una variable temp
    //printf("\nNumero actua--- %d",siguiente->numero);
    //printf("entro a bubble \n");
    while (actual != NULL)
    {
        while (siguiente != NULL)
        {
           // printf("\nNumero guardado en sig [%d] #1\n",siguiente->numero);   
            if (actual->numero > siguiente->numero)
            { 
            temp=actual->numero; // temp  = actual
            actual->numero = siguiente->numero; // actual = siguiente (el mayor encontrado)
            siguiente->numero = temp; 
            //printf("algo entro a ordenar\n"); // siguiente igual a actual (menor) intercambian lugar
            }
            siguiente = siguiente->siguiente;
        }
        siguiente = inicio;
        actual = actual->siguiente;
    }
}
int tamano_lista(struct datos *lista)
{
    printf("entro");
    struct datos *lista_temp = lista;
    int tam = 0;
    if (lista_temp == NULL) // Si la lista esta vacia su tam sera 0
    {
        return 0;
    }
    else 
    while (lista_temp!= NULL)
    {
        tam++;
        lista_temp = lista_temp->siguiente;
    }
    printf("TAM = [%d]\n",tam);
    return tam;
}

void insetar(struct datos **lista, int dato,int posicion)
{
    printf("entro");
    struct datos *nuevo =  ((struct datos*)malloc(sizeof(struct datos)));
    struct datos *p = *lista;
    if (nuevo == NULL)
    {
        printf("Error de alocacion de memoria dentro de #insertar\n");
        exit(EXIT_FAILURE);
    }
    else 
    {
        nuevo->numero = dato; 
        int tam =tamano_lista(*lista);
        if (posicion > tam)
        {
            printf("Posicion no valida, debe ser menor al num de nodos   #%d\n",tam);
            return;
        }
        else 
        if (*lista == NULL) // si es el primer dato se agrega directamente
        {
            *lista = nuevo;
            return;
        }
         if ( posicion == tam)
        {
            while(p->siguiente != NULL)
            {
                p = p->siguiente;
            }
            p->siguiente = nuevo; // nuevo = p->siguiente || o sea nuevo sera la head
            nuevo->atras = p; //  nuevo->atras = p  siendo p el penultimo valor y como nuevo es la (nueva head) su cola es
            // el penumiltimo dato
            return;
        }
        else 
        {
            //struct datos *p = *lista;
            struct datos *temporal = *lista;
            struct datos *inicio = *lista;
            if (posicion == 0)
            {
              p = nuevo; // siendo inicio el nuevo dato 
              inicio->atras = p;
              p->siguiente = inicio;
              p->atras = NULL;
              *lista = p; // insertando en el 0 cambiando el primer punto de lista al nuevo
              return;
            }
            for (int i = 0; i < posicion; i++)
            {
                p = p->siguiente;
                //printf(" valor = %d ",p->numero);
            }
            //printf(" salio ---Valor atras = %d ",p->atras->numero);
            //printf("valor final = %d",p->numero);
            
            temporal=p; //temporal p se hace una copia literal de p, teniendo sus mismos sig y anterior
            //printf("\nNumero en temporal %d\n",temporal->numero);

            p = nuevo;  // recuerda, nuevo no tiene sig ni sucedor asi que se tiene que conectar || ej teniendo 4 y agregar 3
            p->atras = temporal->atras; //  p->atras es el sucedor de 3 conectandose con el antiguto decesor de 4 [num ant]->[3]
            p->atras->siguiente = p; //   p->atras->siguiente es conectar que el sigueinte de atras sea el 3 que agrega [num ant]<-[3]
            p->siguiente = temporal; //  el sigueinte de p sera la direccion de 4 siendo 4 el nuevo siguiente [3]->[4]
            temporal->atras = p; //  el decesor de 4 sera el 3 conetandolo de reversa    [3]<-[4]

            //printf("\nnumero en p ahora %d",p->numero);
            //printf("\nnumero en p atras ahora %d",temporal->atras->numero);


            
            //printf("\nnumero en p adelante ahora %d",p->siguiente->numero);
           // printf("\nnumero en p atras ahora %d",p->atras->numero);
            
            
            
            printf("\ntermino\n");
        }
    }
}

void eliminar(struct datos **lista,int posicion)
{
    struct datos *anterior = *lista;
    struct datos *actual = *lista;
    struct datos *temporal = *lista;
    if (posicion == 0) // eliminar si es la primera posicion
    {
        if (actual->siguiente == NULL   )
        {
            actual->siguiente = NULL; // desconectamos
            actual->atras = NULL; // desconectamos
            *lista = NULL; // la lista que apuntaba al unico valor ahora es nula
            free(actual);
            return;
        }
        temporal = actual->siguiente;  // actual siendo el que vamos a liberar

        temporal->atras = NULL; //

        actual->siguiente = NULL; //

        *lista = temporal; // lista apunta al valor siguiente

        free(actual);
        return;
    }
    else 
    {

    for (int i =0; i < posicion; i++)
    {
        actual = actual->siguiente; // posicionamos en la que vamos a borrar
    }
        printf("\nposicion seleccionada %d\n",actual->numero);

    if (actual->siguiente != NULL)
    {

    printf("anterior = %d  es igual a  %d\n",anterior->numero,actual->atras->numero);
    anterior = actual->atras;

    printf("anterior siguiente %d, es igual a actual->sig %d\n",anterior->siguiente->numero,actual->siguiente->numero);
    anterior->siguiente = actual->siguiente;

    printf("[%d]",actual->siguiente->atras->numero);
    actual->siguiente->atras = anterior;
    printf("[%d]",actual->siguiente->atras->numero);
    actual->atras = NULL; // desconectamos el nodo a eliminar
    actual->siguiente = NULL; // desconectamos el nodo que eliminamos
    free(actual);
    return;
    }
    else // siendo que si eliminamos la head el proceso es diferente
    {
        anterior = actual->atras;
        anterior->siguiente = NULL;

        actual->atras = NULL; // desconectamos el nodo a eliminar
        actual->siguiente = NULL; // desconectamos el nodo que eliminamos
        free(actual);
        return;
    }
    }
}
void unir_listas(struct datos **lista_insetar,struct datos **lista_3_origen,int posicion)
{
    struct datos *inicio_insetar = *lista_insetar;
    struct datos *inicio_origen = *lista_3_origen;
    struct datos *recorrer_insertar = *lista_insetar;
    struct datos *recorrer_lista_3 = *lista_3_origen;
    struct datos *anterior_lista_3 = *lista_3_origen;
    //struct datos *temporal = inicio_insetar;
    //printf("\n[%d]\n",temporal->numero);
    //printf("entro chavales");
    if (posicion == 0)
    {
        //printf("detecto el 0\n");
        while (recorrer_insertar->siguiente != NULL) // RECORREMOS A LA HEAD
        {
            recorrer_insertar = recorrer_insertar->siguiente;
            //printf("salio del while");
        }
        recorrer_insertar->siguiente = inicio_origen;
        inicio_origen->atras = recorrer_insertar;
        *lista_3_origen = inicio_insetar;
        *lista_insetar = NULL;
        return;
    }
    else
    {
        while (recorrer_insertar->siguiente != NULL) // RECORREMOS A LA HEAD
        {
            recorrer_insertar = recorrer_insertar->siguiente; // head de la lista a insertar
            //printf("salio del while");
        }
        for (int i = 0; i < posicion; i++)
        {
            recorrer_lista_3 = recorrer_lista_3->siguiente; // la posicion de la lista 3 donde se va insertar el codigo  
        }
        anterior_lista_3 = recorrer_lista_3->atras;
        recorrer_insertar->siguiente = recorrer_lista_3; // head sera igual a la posicion insertar
        recorrer_lista_3->atras = recorrer_insertar; // el anterior de la posicion a insertar sera ahora la head de la lista a insertar
        anterior_lista_3->siguiente = inicio_insetar; //siendo que el anterior next sera igual al inicio de la lista
        inicio_insetar->atras = anterior_lista_3; // siendo que anterior sera ahora el nodo antes de la posicion
        *lista_insetar = NULL;
        return;

        

    }
}

int main ()
{
    struct datos *lista_1= NULL;
    struct datos *lista_2 = NULL;
    struct datos *lista_3 = NULL;
    
    /*
    creator(&lista_1,1);
    creator(&lista_1,2);
    creator(&lista_1,3);
       

    creator(&lista_2,4);
    creator(&lista_2,5);
    creator(&lista_2,6);

    //eliminar(&lista_2,1);


    printf("\nLista 1\n");
    imprimir(lista_1);
    printf("\nLista 2\n");
    imprimir(lista_2);
    printf("\nLista 3\n");
    imprimir(lista_3);
    */
    creator(&lista_3,7);
    creator(&lista_3,8);
    creator(&lista_3,9);
    //insetar(&lista,21,6);
    int opccion = 0;
    bool verdadero = true;
    int dato;
    int posicion;
    int tam;
    int lista_selecionar;
    while (verdadero)
    {
        printf("\n [0] AGREGAR NODO A LA LISTA UNO ");
        printf("\n [1] ELIMINAR NODO DE LA LISTA UNO ");
        printf("\n [2] AGREGAR NODO A LA LISTA DOS");
        printf("\n [3] ELIMINAR NODO DE LA LISTA DOS");
        printf("\n [4] INSERTAR LISTA A LA LISTA TRES");
        printf("\n [5] TERMINAR PROGAMA\n");
        printf("\n SELECCIONA UNA OPCION: ");
        fflush(stdin); //limpia
        scanf("%d",&opccion);
        switch (opccion)
        {
        case 0:
            printf("\n INGRESE EL NUMERO A INSERTAR: ");
            scanf("%d",&dato);
            printf("\n INGRESE LA POSICION A INSERTAR: ");
            scanf("%d",&posicion);
            printf("Lista 1 antes del cambio\n");
            imprimir(lista_1);
            printf("\nLista 1 despues del cambio;\n");
            insetar(&lista_1,dato,posicion);
            imprimir(lista_1);

            break;

        case 1:
            printf("\n INGRESE LA POSICION DEL NODO A ELIMINAR: ");
            scanf("%d",&posicion);
            tam =tamano_lista(lista_1);
            if (posicion > tam)
            {
                printf("\nPosicion invalida, es mayor a la lista\n");
            }
            else 
            {
            printf("Lista 1 antes del cambio\n");
            imprimir(lista_1);
            printf("\nLista 1 despues del cambio;\n");
            eliminar(&lista_1,posicion-1);
            imprimir(lista_1);
            }
            break;

        case 2:
            printf("\n INGRESE EL NUMERO A INSERTAR: ");
            scanf("%d",&dato);
            printf("\n INGRESE LA POSICION A INSERTAR: ");
            scanf("%d",&posicion);
            printf("Lista 2 antes del cambio\n");
            imprimir(lista_2);
            printf("\nLista 2 despues del cambio;\n");
            insetar(&lista_2,dato,posicion);
            imprimir(lista_2);
            break;
        case 3:
            printf("\n INGRESE LA POSICION DEL NODO A ELIMINAR: ");
            scanf("%d",&posicion);
            tam =tamano_lista(lista_2);
            if (posicion > tam)
            {
                printf("\nPosicion invalida, es mayor a la lista\n");
            }
            else 
            {
            printf("Lista 1 antes del cambio\n");
            imprimir(lista_2);
            printf("\nLista 1 despues del cambio;\n");
            eliminar(&lista_2,posicion-1);
            imprimir(lista_2);
            }
            break;
        case 4:
            printf("INGRESE LA LISTA A INSERTAR [1]/[2]\n");
            scanf("%d",&lista_selecionar);
            if (lista_selecionar == 1)
            {
                printf("Seleccione la posicion a insertar: ");
                scanf("%d",&posicion);
                printf("\nContenido en la lista 1:\n");
                imprimir(lista_1);
                printf("\nContenido en la lista 3: \n");
                imprimir(lista_3);
                printf("\nListas despues de los cambios\n");
                unir_listas(&lista_1,&lista_3,posicion);
                printf("\nContenido en la lista 1:\n");
                imprimir(lista_1);
                printf("\nContenido en la lista 3: \n");
                imprimir(lista_3);
            }
            else if (lista_selecionar == 2)
            {
                printf("Seleccione la posicion a insertar: ");
                scanf("%d",&posicion);
                printf("\nContenido en la lista 2:\n");
                imprimir(lista_2);
                printf("\nContenido en la lista 3: \n");
                imprimir(lista_3);
                printf("\nListas despues de los cambios\n");
                unir_listas(&lista_2,&lista_3,posicion);
                printf("\nContenido en la lista 2:\n");
                imprimir(lista_2);
                printf("\nContenido en la lista 3: \n");
                imprimir(lista_3);
            }
            else 
            {
                printf("\n SELECCIONE UNA LISTA VALIDA [1]-[2]");
            }
            break;
        case 5:
            verdadero = false;
            printf("\n Saliendo..\n");
            break;
         
        default:
            break;
        }

    }
    

    liberador_memory(lista_1);
    liberador_memory(lista_2);
    liberador_memory(lista_3);
    printf("\n Fin del progama");
    return  0;
}