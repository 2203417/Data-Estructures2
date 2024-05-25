//avance de practica 6
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



 struct libro 
{
    char *nombre;
    char *genero;
    int release_date;
};

 struct elemento 
{
    struct libro *eLibro;
    struct elemento *sig;
};

 struct pila 
{
    struct elemento *cima;
    int longitud;
    int longitud_actual;
    int num_elementos;
};

 struct arreglo_pilas 
{
    struct pila *libros;
    int num_pilas;
} ;
 struct Nodo // estructura del arbol
{
    struct pila *elibro; // el arbol almacena pilas de libros como valores
    struct Nodo *izquierda; // el arbol tiene nodos que guardan lo mismo 
    struct Nodo *derecha;   // elemento de liros
};




int llena(struct pila *caja)
{
    return (caja->longitud_actual >= caja->longitud);
}

int vacia(struct pila *caja)
{
    // si regresa  1 : La pila esta vacia
    // si regresa  0 : la pila tiene datos es decir no esta llena
    return caja->cima == NULL; // si la cima es igual a -1 no tiene datos
}


void inicializar_pila(struct pila *pLibro,int longitud) // inicializamos la pila (siendo cualquiera)
{
    pLibro->cima=NULL;  // Cima null por que es nueva
    pLibro->longitud=longitud; // longitud x
    pLibro->num_elementos=0; // igual x
    pLibro->longitud_actual = 0;
}

void push(struct pila *caja,struct libro *Libro) // hacemos push de cada elemento o sea de cada libro dentro de la caja
{
    if (llena(caja)) // validacion de que si no se hace un overflow 
    {
        printf("La pila esta llena, overflow\n\r");
        return;
    }
    struct elemento *nuevo_nodo = (struct elemento*)malloc(sizeof(struct elemento)); // elemento 
    nuevo_nodo->eLibro = Libro; // elemento apunta a una estructura de libros asi que esa estructura sera el libro del for
    nuevo_nodo->sig = caja->cima;
    caja->cima = nuevo_nodo;
    caja->longitud_actual++; // incrementamos en long actual y asi llevamos conteo 
    
}
struct libro* pop(struct pila *plibro) // funcion para sacar un libro
{ // nota improtante p libro hace referencia a pila de libros o sea puede ser la de genero o otras
    if (vacia(plibro))
    {
        printf("La pila esta vacia,underflow\n");
        return NULL;
    }
    struct elemento *sacar_libro = plibro->cima; // la cima de nuestra pila; siendo elemento pq es libro
    struct libro *libro_seleccionado = sacar_libro->eLibro; // para acceder a lo que esta en esa direccion de memoria y copiarlo
    plibro->cima = sacar_libro->sig;// recorremos la pila pq vamos a sacar el libro
    free(sacar_libro); // se borra ese libro
    plibro->longitud_actual--; // sacamos 1 valor
    return libro_seleccionado; // sacamos dicho libro de la cima y lo regresamos
}

void mostrar_caja(struct pila *plibro)
{
    int i = 0; // Corregir el valor inicial de i
    if (vacia(plibro))
    {
        printf("La pila esta vacia,underflow\n");
        return;
    }
    struct elemento *libro_a_imprimir = plibro->cima;
    while (libro_a_imprimir != NULL) // Modificar la condición del bucle
    {
        printf("Lista: \n\r");
        printf("%d  | %s ,%s ID-%d\n\r", libro_a_imprimir->eLibro->release_date, libro_a_imprimir->eLibro->nombre, libro_a_imprimir->eLibro->genero, i);
        libro_a_imprimir = libro_a_imprimir->sig;
        i++; // Incrementar el contador dentro del bucle
    }
}

void vaciar_pila(struct pila *pila)
{
    struct elemento *actual = pila->cima;
    struct elemento *siguiente = pila->cima;
    while (siguiente != NULL)
    {   
        actual = siguiente;
        siguiente = siguiente->sig;
        free(actual);
    }
    pila->cima = NULL; // Establecer el puntero cima como NULL
    free(pila);
}




void devolver_libros(struct arreglo_pilas *pila_libros,struct pila *caja)
{
    //printf("entro");
    //printf("Va sacar libros de #%d num de pilas",pila_libros->num_pilas);
    for (int i = 0; i < pila_libros->num_pilas;i++) // recorremos el numero de pilas desde 0 hasta 11
    {

        while (!vacia(&pila_libros->libros[i])) // mientras esa pila de libros no este vacia de ese arreglo las va recorrer todas
        { // cuando la encuentre vacia  parara y seguira con la siguiente pila

            struct libro *libro = pop(&pila_libros->libros[i]); // sacamos un libro de la cima de ese arreglo
            push(caja, libro); // hacemos push del libro en la caja principal
        }   

    }
    pila_libros->num_pilas = 0; // restablecemos el numero para borrar totalmente el arreglo de pikas
    free(pila_libros->libros); // liberamos esa memoria del arreglo de pilas
    pila_libros->libros = NULL; // y por seguridad Declaramos nullo
}







struct pila* inicializar_caja(void) // inicializar la caja 1 sola vez
{
    int i;
    struct pila *caja;
    static struct libro libros[44] =  {
                            {"Cell","Horror",2006},
                            {"The Street Lawyer","Thriller",1998},
                            {"Nineteen Minutes","Thriller",2007},
                            {"Harry Potter y la piedra filosofal","Fantasy",1997},
                            {"Armageddon","Post-apocalyptic fiction",2003},
                            {"The Jester","Historical fiction",2003},
                            {"Harry Potter y el prisionero de Azkaban","Fantasy",1999},
                            {"Star Wars: Episode I The Phantom Menace","Science fiction",1999},
                            {"Dreamcatcher","Fantasy",2001},
                            {"Rainbow Six","Thriller",1998},
                            {"Hannibal","Horror",1999},
                            {"Twelve Sharp","Crime",2006},
                            {"The Bear and the Dragon","Thriller",2000},
                            {"The Testament","Adventure Story",1999},
                            {"Red Rabbit","Historical fiction",2002},
                            {"Anansi Boys","Fantasy",2005},
                            {"Airframe","Thriller",1997},
                            {"Harry Potter y la camara secreta","Fantasy",1998},
                            {"The King of Torts","Thriller",2003},
                            {"The Da Vinci Code","Mystery",2003},
                            {"Harry Potter y la Orden del Fenix","Fantasy",2003},
                            {"Mary, Mary","Crime",2005},
                            {"The Summons","Thriller",2002},
                            {"Bag of Bones","Horror",1998},
                            {"The 5th Horseman","Thriller",2006},
                            {"Step on a Crack","Thriller",2007},
                            {"Winter's Heart","Fantasy",2000},
                            {"Plum Island","Fiction",1997},
                            {"Eleven on Top","Crime",2005},
                            {"Harry Potter y el misterio del principe","Fantasy",2005},
                            {"The Closers","Crime",2005},
                            {"Glorious Appearing","Post-apocalyptic fiction",2004},
                            {"Prey ","Science fiction",2002},
                            {"The Last Juror","Thriller",2004},
                            {"'S' Is for Silence","Mystery",2005},
                            {"4th of July","Mystery",2005},
                            {"Harry Potter y las reliquias de la Muerte","Fantasy",2007},
                            {"The Shelters of Stone","Historical fiction",2002},
                            {"Harry Potter y el caliz de fuego","Fantasy",2000},
                            {"The Dark Tower VII: The Dark Tower","Fantasy",2004},
                            {"Book of the Dead ","Crime",2007},
                            {"The Dark Tower VI: Song of Susannah","Fantasy",2004},
                            {"Cold Mountain","Historical novel",1997},
                            {"A Feast for Crows","Fantasy",2005},
                            
                        };

        
    caja = (struct pila*)malloc(sizeof(struct pila)); // se aloca la memoria a la estructura pila pq al final la caja 
    // es una pila nomas pero sera nuestra pila principal
        if (caja == NULL)
        {
            printf("Erro en alocacion de la memoria");
            exit(EXIT_FAILURE);
        }
    inicializar_pila(caja,44); /// inicializamos la caja que es nuestra pila donde estara todos nuestros libros sin importar el orden
    for(i=0;i<44;i++)
    {        
        push(caja,&libros[i]); // hacemos push cada uno de los libros dentro de la caja 
    }
    return caja; // regresa la caja ya creada
}

void iniciar_arreglo(struct arreglo_pilas *pila_libros) // para iniciar el arreglo de estructuras
{
            for(int i=0;i<2;i++)
            {
                pila_libros[i].libros= (struct pila*)malloc(sizeof(struct pila));
                pila_libros[i].num_pilas=0;
                inicializar_pila(pila_libros[i].libros,40);
            }
}

void imprimir_pilar_apilada_genero(struct arreglo_pilas *pila_libros,int cant_nodos) 
{
    for (int i = 0; i < cant_nodos; i++)
    {
        //printf("[%d]\n",i);
        printf("[%d]-%s\n\r",i,pila_libros->libros[i].cima->eLibro->genero); // nuestro menu de cajas apiladas
    }
}


void imprimir_pilar_apilada_fecha(struct arreglo_pilas *pila_libros,int num)
{
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < num; i++)
    {
    printf("[%d]-%d\n\r",i,pila_libros->libros[i].cima->eLibro->release_date); // lo mismo pero con fecha
    }
    printf("----------------------------------------------------------------\n");
}




void ordenar_arbol_genero(struct Nodo** raiz_a,struct libro *libro)
 { // doble puntero por que si no  se borra, oocupamos acceder a la direccion de memoria 
    if (*raiz_a == NULL) { // si es nullo creamos la nueva pila
        (*raiz_a) =(struct Nodo*)malloc(sizeof(struct Nodo*)); // creamos el espacio del nod o
        (*raiz_a)->elibro = (struct pila*)malloc(sizeof(struct pila)); // creamos el espacio de la pila que almacenara los libros ( cada nodo es una pila de libros)
        inicializar_pila((*raiz_a)->elibro,45); // inicializamos la pila
        push((*raiz_a)->elibro,libro); // hacemos push del susodicho libro 
        //printf("Pila creada de %s",libro->genero);
        return;
        //inicializar_pila(libro,40);
    } 
    else 
    {   
        int r = strcmp(libro->genero,(*raiz_a)->elibro->cima->eLibro->genero); // para obtener el valor -1 si es menor, 0 es igual y 1 es mayor
        if (r == 0)  // si es igual
        { // si son iguales, se hace push a esa pila
            push((*raiz_a)->elibro,libro);//almacenamos dicho valor en el libro, si es que son iguales
        } 
            else if (r > 0)  // si es mayor  
            {
                ordenar_arbol_genero(&((*raiz_a)->derecha),libro); // se va para la derecha 
            }
                else
                {
                    ordenar_arbol_genero(&((*raiz_a)->izquierda),libro); // de lo contrario se va para la izquierda 
                } 
    }
}
// a 
void ordenar_arbol_fecha(struct Nodo** raiz_a,struct libro *libro)
 { // doble puntero por que si no  se borra, oocupamos acceder a la direccion de memoria 
    if (*raiz_a == NULL) { // si es nullo creamos la nueva pila
        (*raiz_a) =(struct Nodo*)malloc(sizeof(struct Nodo*)); // creamos el espacio del nod o
        (*raiz_a)->elibro = (struct pila*)malloc(sizeof(struct pila)); // creamos el espacio de la pila que almacenara los libros ( cada nodo es una pila de libros)
        inicializar_pila((*raiz_a)->elibro,45); // inicializamos la pila
        push((*raiz_a)->elibro,libro); // hacemos push del susodicho libro 
        printf("-%d-\n",libro->release_date);
        return;
        //inicializar_pila(libro,40);
    } 
    else 
    {   
        //printf("Libro-%d,cima-%d--\n",libro->release_date,(*raiz_a)->elibro->cima->eLibro->release_date);
        if ( (*raiz_a)->elibro->cima->eLibro->release_date == libro->release_date) 
        { // si son iguales, se hace push a esa pila
            //printf("-------------entro a igual");
            //printf("-%d-",libro->release_date);
            //printf("-%d--------\n",(*raiz_a)->elibro->cima->eLibro->release_date);
            push((*raiz_a)->elibro,libro);//almacenamos dicho valor en el libro, si es que son iguales
        } 
            else if ((*raiz_a)->elibro->cima->eLibro->release_date > libro->release_date)  // si es mayor  
            {
                ordenar_arbol_fecha(&((*raiz_a)->izquierda),libro); // se va para la derecha 
            }
                else
                {
                    ordenar_arbol_fecha(&((*raiz_a)->derecha),libro); // de lo contrario se va para la izquierda 
                } 
    }
}





void imprimirArbol_genero(struct Nodo* nodo, int nivel)
{
    int i;
    if (nodo != NULL)
        {
        printf("%s",nodo->elibro->cima->eLibro->genero);
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
            imprimirArbol_genero(nodo->derecha, nivel + 1);
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
            imprimirArbol_genero(nodo->izquierda, nivel + 1);
        }
    }
}
void imprimirArbol_fecha(struct Nodo* nodo, int nivel)
{
    int i;
    if (nodo != NULL)
        {
        printf("%d",nodo->elibro->cima->eLibro->release_date);
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
            imprimirArbol_fecha(nodo->derecha, nivel + 1);
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
            imprimirArbol_fecha(nodo->izquierda, nivel + 1);
        }
    }
}



struct Nodo* borraArbol(struct Nodo** nodo)
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
int arbol_a_arreglo(struct Nodo **raiz_a,struct arreglo_pilas *arreglo_pilas,int nivel,int indice) // para insertarlo lo vamos hacer por orden
{
    if (raiz_a != NULL)
    {
        if((*raiz_a)->izquierda  != NULL)
        {
            indice = arbol_a_arreglo(&(*raiz_a)->izquierda,arreglo_pilas,nivel + 1,indice);
        }
        arreglo_pilas->num_pilas++;
        //printf("indice-%d",indice);
        //printf("-%s\n",(*raiz_a)->elibro->cima->eLibro->genero);
        arreglo_pilas->libros[indice] = *((*raiz_a)->elibro);
        indice++;
        if((*raiz_a)->derecha  != NULL)
        {
            indice =  arbol_a_arreglo(&(*raiz_a)->derecha,arreglo_pilas,nivel + 1,indice);
        }
    }
    return indice;
}

int contarElementos(struct Nodo *nodo)
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



int main ()
{

    
    struct pila *caja;
    caja = inicializar_caja(); // inicializamos la caja
    printf("_--------------------\n");
    //mostrar_caja(caja);
    printf("_--------------------\n");
    struct Nodo* raiz_a = NULL;
    struct Nodo* raiz_b = NULL;
    // struct arreglo_pilas **pila_libros = NULL;
    struct arreglo_pilas pila_libros[2];
    //iniciar_arreglo(&pila_libros[0]);
        
        
        for(int i=0;i<2;i++)
        {
            //pila_libros[i].libros= (struct pila*)malloc(sizeof(struct pila));
            pila_libros[i].libros= NULL;
            pila_libros[i].num_pilas=0;
           /// inicializar_pila(pila_libros[i].libros,40);
         }

        

    bool verdadero = true;
    int  op = 0;
    int cant_nodos;
    int gen;
    printf("\n------------MENU----------\n");

    while (verdadero)
    {
        printf("Seleccione la opccion\n\r");
        printf("[1]-Mostrar contenido de la caja\n\r");
        printf("[2]-Apilar por genero\n\r");
        printf("[3]-Apilar por fecha \n\r");
        printf("[4]-Terminar progama \n\r");
        scanf("%d",&op);
        
        switch (op)
        {
        case 1:
                mostrar_caja(caja);
                printf("\n");
            break;
        case 2:
                
                while(!vacia(caja))
                {
                    
                    ordenar_arbol_genero(&raiz_a,pop(caja)); // cada valor sacado se va meter a la funcion
                }
                printf("\n");

                imprimirArbol_genero(raiz_a,0);
                printf("\n");
                // --------------pasamos de arbol a arreglos a de pilos
                cant_nodos =  contarElementos(raiz_a); // primero contamos la cantidad de nodos que se generaron
                //printf("cantidad de nodos %d",cant_nodos);
                pila_libros[0].libros = (struct pila *)malloc(sizeof(struct pila) * cant_nodos); // primero asignamos memoria al arreglo 0 de pilas (siendo el 0 nuestro arreglo de pilas de genero
                printf("\n"); // espacio nomas 
                int a =arbol_a_arreglo(&raiz_a,&pila_libros[0],0,0); // la variable "a" recibe un valor ya que ocupaba que fuera int la funcion,pila_libros[0]
                imprimir_pilar_apilada_genero(&pila_libros[0],cant_nodos); // se imprime las pilas de libros
                scanf("%d",&gen); // se captura el interesado
                mostrar_caja(&pila_libros[0].libros[gen]); // se muestra la seccion interesada
                //printf("---%d--",pila_libros->num_pilas);
                raiz_a  =borraArbol(&raiz_a); // raiz_a borra el arbol para asi poder volver a usarlo
                // devolvermos los libros a la caja
                devolver_libros(&pila_libros[0],caja); // devolvemos los libros a la caja
                a++; // variables por que si no me marcaba warning por la funcion arbol_a_arreglo
                a = 0;
                printf("\n");
            break;

        case 3: //ordenar_arbol_fecha(struct Nodo** raiz_a,struct libro *libro)
                while(!vacia(caja))
                {
                    ordenar_arbol_fecha(&raiz_b,pop(caja)); // cada valor sacado se va meter a la funcion
                }
                printf("\n");

                imprimirArbol_fecha(raiz_b,0); // imprimimos el arbol para verificar que todo este bien
                printf("\n");
                // pasamos de arbol a arreglos a de pilos
                cant_nodos =  contarElementos(raiz_b); // obtenemos la cantidad de nodos para despues
                //printf("cantidad de nodos %d",cant_nodos);
                pila_libros[1].libros = (struct pila *)malloc(sizeof(struct pila) * cant_nodos); // primero asignamos memoria al arreglo 0 de pilas (siendo el 0 nuestro arreglo de pilas de genero
                printf("\n");
                int b =arbol_a_arreglo(&raiz_b,&pila_libros[1],0,0); // cambiamos de arbol a un arreglo de pilas
                imprimir_pilar_apilada_fecha(&pila_libros[1],cant_nodos); // se imprimen la cantidad de nodos que se crearon
                scanf("%d",&gen); //  se obtiene el interesado
                mostrar_caja(&pila_libros[1].libros[gen]); // se muestra el interesado
                raiz_b  =borraArbol(&raiz_b); // se borra susodicho arbol
                devolver_libros(&pila_libros[1],caja); // se devuelven los libros a la caja y listo
                b++;
                b = 0;
            break;

        case 4:
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