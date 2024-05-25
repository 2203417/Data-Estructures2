//avance de practica 7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




typedef struct  nodo // estructura del arbol
{
    char operando; // el arbol almacena pilas de libros como valores
    int indice;
    struct nodo *left; // el arbol tiene nodos que guardan lo mismo 
    struct nodo *right;   // elemento de liros
}Nodo;









int evaluate_expresion(char expresion[]);

void print_tree_char(Nodo* nodo, int nivel);

Nodo* Delete_tree(Nodo** nodo);

int element_counter(Nodo *nodo);

Nodo* branch_creator(char expresion);

int is_operator(char expresion);

int is_operand(char expresion);

int  mult_2(int var);

void fill_expresionTree(Nodo** rooth_a,char expresion);

void fill_operandTree(Nodo** rooth_a,char expresion);


void fill_operandTree(Nodo** rooth_a,char expresion)
{
    if (is_operand(expresion)) // si es un operando
    {
        if ((*rooth_a) != NULL) // si es dif a nulo
        {
            if  ((*rooth_a)->operando == '+' ||(*rooth_a)->operando == '-') // si es un menos o mas
            {
               // printf("paso por mas o menos %c con la expresion %c\n",(*rooth_a)->operando,expresion);
                if ((*rooth_a)->left == NULL)
                {
                    printf("encontro un nodo bien %c\n",(*rooth_a)->operando);
                    printf("Operando nuevo creado %c\n",expresion);
                    (*rooth_a)->left = branch_creator(expresion); // creamos el nodo
                    // por que esos operados su derecha es uno de mayor jerarquia
                    return;
                }
                else if (((*rooth_a)->left != NULL &&  is_operand((*rooth_a)->left->operando)))
                {
                    fill_operandTree(&(*rooth_a)->right,expresion);
                }
                else 
                {
                    fill_operandTree(&(*rooth_a)->left,expresion);
                }
            }
                printf("paso por operando mayor  %c con la expresion %c\n",(*rooth_a)->operando,expresion);
             if ((*rooth_a)->operando == '*' || (*rooth_a)->operando == '/' || (*rooth_a)->operando == '^') // si es un multiplicacion o division
            {
                if ((*rooth_a)->left == NULL)
                {
                    (*rooth_a)->left = branch_creator(expresion); // creamos el nodo
                    return;
                }
                else if ((*rooth_a)->right == NULL)
                {
                    (*rooth_a)->right = branch_creator(expresion); // creamos el nodo
                    return;
                }
                //printf("valores de");
            }
                fill_expresionTree(&(*rooth_a)->right,expresion);  
        } 
    }
}
void fill_expresionTree(Nodo** rooth_a,char expresion)
{
   if (is_operator(expresion)) // si es un operador
    {
        if (*rooth_a == NULL) // si es nulo
        {
            //printf("--- Nodo a ingresar --- %c\n",expresion);
            (*rooth_a) = branch_creator(expresion); // creamos el nodo
            //printf("Nodo raiz creado %c\n",(*rooth_a)->operando);
            //printf("Nodo raiz creado %c\n",(*rooth_a)->operando);
            return;
        }
            if (expresion == '*' || expresion== '/' ||expresion == '^') // si el nodo es un operador de mayor jerarquia
            {
                    fill_expresionTree(&((*rooth_a)->right), expresion); // vamos hacia la derecha
                
            }
                if (expresion == '+' || expresion == '-') // si el nodo es un operador de menor jerarquia
                {
                    if ((*rooth_a)->operando == '+' || (*rooth_a)->operando == '-') 
                    {
                        //printf("Se acomoda la jerarquia --- %c\n",(*rooth_a)->operando);
                        Nodo *temp = branch_creator(expresion); // creamos un nodo
                        //printf("Operador nuevo creado %c",temp->operando);
                        temp->left = (*rooth_a); // asignamos el nodo actual al nodo izquierdo
                        (*rooth_a) = temp; // asignamos el nodo creado al nodo actual
                        //printf("%c\n",(*rooth_a)->operando);
                    }
                }
                
    }
    return;  
}


int evaluate_expresion(char expresion[])
{
    int i = 0;
    float aux_expresion = 0;
    int aux_operand = 0;
    for (i = 0; i <strlen(expresion); i++)
    {
        if (is_operator(expresion[i]))
        {
            aux_expresion++; // suma cada uno de los operadores
        }
        if (is_operand(expresion[i]))
        {
            aux_operand++; // suma cada uno de los operando
        }
    
    } 
    return (aux_expresion == (aux_operand - 1)); // si la cantidad de operadores es igual a la cantidad de operandos -1
} // menos 1 por que el primer operando no tiene operador

int is_operator(char expresion)
{
    return (expresion == '+' || expresion == '-' || expresion == '*' || expresion == '/' || expresion == '^');
}

int is_operand(char expresion)
{
    return (expresion >= 'a' && expresion <= 'z');
}
Nodo* branch_creator(char expresion)
{
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo*));
    nodo->operando = expresion;
    nodo->indice = 0;
    nodo->left = NULL;
    nodo->right = NULL;
    return nodo;
}

int  mult_2(int var)
{
    return (var % 2);
}


void print_tree_char(Nodo* root, int nivel)
{
    int i;
    if (root != NULL)
        {
        printf("%c",root->operando);
        if(root->right !=NULL)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            print_tree_char(root->right, nivel + 1);
        }
        if(root->left !=NULL)
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
            print_tree_char(root->left, nivel + 1);
        }
    }
}



Nodo* Delete_tree(Nodo** nodo)
{
    if ((*nodo) != NULL)
    {
        if((*nodo)->right!=NULL)
        {
            (*nodo)->right = Delete_tree(&(*nodo)->right);
        }
        if((*nodo)->left!=NULL)
        {
            (*nodo)->left = Delete_tree(&(*nodo)->left);
        }
        free((*nodo));
        return NULL;
    }
    return NULL;
}






int main ()
{

    Nodo* raiz_a = NULL;
   // struct Nodo* raiz_b = NULL;
        

    bool verdadero = true;
    int  op = 0;
    //char expresion[15];
    char expresion_prueba[15] = "x+y/a+b*c^d"; // Ejemplo de expresión  //b*c^d
    //int ex = 0;
    printf("\n------------MENU----------\n");

    while (verdadero)
    {
        printf("Seleccione la opccion\n\r");
        printf("[0]-CAPTURAR EXPRESION\n\r");
        printf("[1]-EVALUAR EXPRESION\n\r");
        printf("[2]-TERMINAR PROGAMA\n\r");
        scanf("%d",&op);
        
        switch (op)
        {
        case 0:
        /*
            printf("Introduzca la expresion\n\r");
            scanf("%s",expresion); // capturamos la expresion
            fflush(stdin);
        */
        if (evaluate_expresion(expresion_prueba))
        {
            for (int i = 0; i <strlen(expresion_prueba); i++)
            {
                    //printf("Nodo a ingresar --- %c",expresion_prueba[i]);
                fill_expresionTree(&raiz_a,expresion_prueba[i]); // caputaramos cada una de las expresiones                
            }
                for (int i = 0; i <strlen(expresion_prueba); i++)
            {
               // printf("---------[%c]---------",expresion_prueba[i]);
                    //printf("Nodo a ingresar --- %c",expresion_prueba[i]);
                fill_operandTree(&raiz_a,expresion_prueba[i]); // caputaramos cada una de las expresiones                
            }
            printf("\n");
            print_tree_char(raiz_a,0);
            printf("\n");
        }
        else
        {
            printf("La expresion es incorrecta\n\r");
            break;
        }
            break;
        case 1:
                
            break;

        case 2: 
            verdadero = false;
            break;

        default:
        printf("Introduzca una Opccion valida\n\r");
            break;
        }
    }

    printf("Progama finalizado");
    return 0;
}


 // _____________________________________________________________________________________________FUNCIONES DE PRUEBA _____________________________________________________________
/*
void fill_expresionTree(Nodo** rooth_a,char expresion)
{
    if (is_operator(expresion)) // si es un operador
    {

    if (*rooth_a == NULL) // si es nulo
    {
        (*rooth_a) = branch_creator(expresion); // creamos el nodo
        printf("Nodo raiz creado %c\n",(*rooth_a)->operando);
        return;
    }
    else
    {
        if (expresion == '+' || expresion == '-' || expresion == '*' || expresion == '/' || expresion == '^')
        {
            if (expresion == '*' || expresion== '/' ||expresion == '^') // si el nodo es un operador de mayor jerarquia
            {
                printf("Detecto un operador de mayor jerarquia --- %c\n",(*rooth_a)->operando);
                //printf("%c\n",(*rooth_a)->operando);
                Nodo *temp = branch_creator(expresion); // creamos un nodo
                printf("Operador nuevo creado %c",temp->operando);
                temp->left = (*rooth_a); // asignamos el nodo actual al nodo izquierdo
                (*rooth_a) = temp; // asignamos el nodo creado al nodo actual
                //printf("%c\n",(*rooth_a)->operando);
                return;
            }
            else
            {
                //printf("%c\n",(*rooth_a)->operando);
                fill_expresionTree(&((*rooth_a)->right), expresion); // vamos hacia la derecha
            }
        }   
    }
    }
    return;
}*/
 // _____________________________________________________________________________________________FUNCIONES DE PRUEBA _____________________________________________________________
