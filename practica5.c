

#include <stdio.h>
#include <stdlib.h>

typedef struct s_nodo
{
    int valor;
    struct s_nodo* izquierda;
    struct s_nodo* derecha;
}Nodo;



Nodo* crearNodo(int valor)
{
    Nodo* nodo = ( Nodo*)malloc(sizeof( Nodo));
    nodo->valor = valor;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    return nodo;
}



void InsertarElemento(Nodo** raiz_a,int numero_insertar) { // doble puntero por que si no 
    if (*raiz_a == NULL) { // al memento de que entre por asid decirlo el lado izquierdo y este sea nudo
    // si no es doble puntero no se asignara correctamente y solo se generara una copia borrando y creando un ciclo donde nomas se modifique la raiz
    // asi que don doble puntero, este si se puede modificar 
        *raiz_a = crearNodo(numero_insertar); // Insertar el nuevo nodo en la posicion correcta
    } else {
        if (numero_insertar <= (*raiz_a)->valor) { // nomas validamos un elemto por que 
            // se evalua el nodo actual, si no entra a la izquierda y asi se va ir yendo hasta que evalue toda los nodos a la izquierda
            // despues si ninguno cumplio con la coindicion de ser <=  entonces pasa a los nodos de la derecha
            // siendo que si no es menor igual obviamente este sera mayor o igual 


            // Si el valor a insertar es menor o igual insertar en el subarbol izquierdo
            InsertarElemento(&((*raiz_a)->izquierda),numero_insertar);
            // asi cuando entra, como usamos doble puntero, si se va modificar al original ->izquierda 
        } else {
            // Si el valor a insertar es mayor insertar en el subarbol derecho
            InsertarElemento(&((*raiz_a)->derecha),numero_insertar);
        }
    }
}
// a 

int calcular_nivel(Nodo *Raiz,int nivel,int numero_buscar,int retornar)
{\

    if (Raiz != NULL)
    {
        printf("Numero de la raiz %d",Raiz->valor);
        if (Raiz->valor == numero_buscar)
        {
            return retornar = nivel;
        }
        if (Raiz->izquierda != NULL)
        {
            retornar = calcular_nivel(Raiz->izquierda,nivel + 1,numero_buscar,retornar);
        }
        if (Raiz->derecha != NULL)
        {
            retornar = calcular_nivel(Raiz->derecha,nivel + 1,numero_buscar,retornar);
        }
    }
    return retornar;
}





int Level_Counter(Nodo* nodo, int nivel,int max_level)
{
     
        //printf(" \nNodo arbol - %d  nivel: %d  max_level: %d\n",nodo->valor,nivel,max_level);
    if (nodo != NULL)
    {
        if(nodo->derecha!=NULL)
        {   
            //printf(" Nodo derecha arbol - %d  nivel: %d  max_level: %d\n",nodo->derecha->valor,nivel,max_level);
            max_level = Level_Counter(nodo->derecha, nivel + 1,max_level);

        }
        if(nodo->izquierda!=NULL)
        {
           // printf(" Nodo izquierda arbol - %d  nivel: %d  max_level: %d\n",nodo->derecha->valor,nivel,max_level);
            max_level = Level_Counter(nodo->izquierda, nivel + 1,max_level);

        }
    }
   // printf("Regresara\n");
    return max_level < nivel ? nivel : max_level; // si el maximo es el nivel mas alto se regresa de lo contrario se regresa el otro---
}


int tree_comparator(Nodo* nodo_a,Nodo* nodo_b, int nivel,int igual)
{
        if ( nodo_a == NULL || nodo_b == NULL)
        {
            return igual = 0;
        }
    if (nodo_a != NULL && nodo_b != NULL)
    {
        if (nodo_a->valor != nodo_b->valor)
        {
                
         return igual = 0;
        }
        else 
        if (nodo_a->derecha != NULL)
        {
            igual = tree_comparator(nodo_a->derecha,nodo_b->derecha,nivel + 1,igual);
        }
            if (nodo_a->izquierda != NULL)
        {
            igual = tree_comparator(nodo_a->izquierda,nodo_b->izquierda,nivel + 1,igual);
        }
    }
    return igual;
}


void imprimirArbol(Nodo* nodo, int nivel)
{
    int i;
    if (nodo != NULL)
        {
        printf(" %d", nodo->valor);
        if(nodo->derecha!=NULL)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimirArbol(nodo->derecha, nivel + 1);
        }
        if(nodo->izquierda!=NULL)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimirArbol(nodo->izquierda, nivel + 1);
        }
    }
}



Nodo* borraArbol(Nodo** nodo)
{
    if ((*nodo) != NULL)
    {
        if((*nodo)->derecha!=NULL)
        {
            (*nodo)->derecha = borraArbol(&(*nodo)->derecha);
        }
        if((*nodo)->izquierda!=NULL)
        {
            (*nodo)->izquierda = borraArbol(&(*nodo)->izquierda);
        }
        free((*nodo));
        return NULL;
    }
    return NULL;
}


int contarElementos(Nodo* nodo)
{
    //int i;
    int n=0;
    if (nodo != NULL)
    {
        if(nodo->derecha!=NULL)
        {
            n+=  contarElementos(nodo->derecha);
        }
        if(nodo->izquierda!=NULL)
        {
            n+= contarElementos(nodo->izquierda);
        }
        n++;
        return n;
    }
    return n;
}
Nodo* crearNodo(int valor);
void imprimirArbol(Nodo* nodo, int nivel);
Nodo* borraArbol(Nodo** nodo);
int contarElementos(Nodo* nodo);
//IMPLEMENTAR
//int calcularAltura(Nodo *arbol);
//int compararArboles(Nodo *arbol_a,Nodo *arbol_b);

int main(void)
{
    Nodo* raiz_a = crearNodo(0);
    int opccion = 0,sub = 0,numero_buscar = 0,variable_aux = 0,numero_insertar =0,resultado =0;
    while (!sub)
    {
    
    printf("\n----------------------MENU----------------------\n");
    printf("Ingrese la accion de quiere realizar\n");
    printf("[0]-Insertar nodo\n");
    printf("[1]-calcular nivel de la posicion de un elemento en la raiz\n");
    printf("[2]-Calcular el numero de elementos de una raiz\n");
    printf("[3]-calcular profundidad de una raiz\n");
    printf("[4]-imprimir arbol\n");
    printf("[5]-Terminar progama\n");
    printf("\n------>");
    scanf("%d",&opccion);
    printf("\n");
    switch (opccion)
    {
    case 0:
        printf("Ingrese el numero a insertar: ");
        scanf("%d",&numero_insertar);
        printf("\n");
        if (variable_aux == 0)
        {
            raiz_a->valor = numero_insertar;
            variable_aux++;
            
        }
        else if (variable_aux != 0) 
        {
            //Nodo* nodo_aux_insertar = crearNodo(numero_insertar);
            InsertarElemento(&raiz_a,numero_insertar);
            //free (nodo_aux_insertar);
            imprimirArbol(raiz_a,0);
        }
        break;
    case 1:
        printf("Ingrese el numero a buscar\n");
        scanf("%d",&numero_buscar);
        resultado = calcular_nivel(raiz_a,0,numero_buscar,-1);
        if (resultado == -1)
        {
            printf("Numero no encontrado, %d\n",resultado);
        }
        else 
        {
            printf("El numero %d se encuentra en el nivel %d\n",numero_buscar,resultado);
        }
        break;
    case 2:
        printf("[2]-Calcular el numero de elementos de una raiz\n");
         resultado = contarElementos(raiz_a);
         printf("El numero de elementos del arbol es de %d\n",resultado);
        break;
    case 3:
        printf("[3]-calcular profundidad de una raiz\n");
        resultado = Level_Counter(raiz_a,0,0);
        printf("La profundidad de la raiz es de %d\n",resultado+1);
        break;
    case 4:
        imprimirArbol(raiz_a,0);
        printf("\n");
        break;
    case 5:
        sub = 1;
        borraArbol(&raiz_a);
        printf(":p");
        break;
    
    default:

        break;
    }
    }


    printf("\n\n");
    return 0;
}