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
    int longitud_actual ;
    int num_elementos;
};

 struct arreglo_pilas 
{
    struct pila *libros;
    int num_pilas;
} ;


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


void apilar_genero(struct arreglo_pilas *pila_libros,struct libro *elibro) // estructura de pila de libros,
{// el arreglo es donde meteras los libros, el parametros es el libro sacado y aqui se mete dependiendo su genero
    //bool encontrado = false;
    //int contador = 0;
    //printf("Entro a aplicar genero [%d]\n",contador);
    //contador++;
    if (pila_libros->num_pilas == 0 && pila_libros->libros == NULL)// si es la primera pila o es null los libros
    {
        //printf("Entro a nullo");
        pila_libros->num_pilas++; // incrementa el num de pilas
        pila_libros->libros = (struct pila *)malloc (sizeof(struct pila));// primer malloc para la primera
        inicializar_pila(pila_libros->libros,40); // inicializamos la pila
        push(pila_libros->libros,elibro); // hacemos push del primer libro
        return;

    }
    for (int i = 0; i <pila_libros->num_pilas; i++)
    {
        //printf("Entro en la busqueda de comparar\n");
        //printf("Generos actual [%s]  / Genero a buscar [%s]        Iteracion[%d]\n",pila_libros[i].libros->cima->eLibro->genero,elibro->genero,i);
        if (strcmp(pila_libros->libros[i].cima->eLibro->genero, elibro->genero) ==0) // busca si hay una pila con el genero que ya esta
        {
            //printf("Genero encontrado------\n");
            push(&pila_libros->libros[i], elibro); // se agrega el libro a la cima que es la pila (una caja por ej)
            //encontrado = true;
            return;
        }
    }
        pila_libros->num_pilas++;
        struct pila *aux;
        aux= NULL;
        while (aux == NULL)
        {
            aux = realloc(pila_libros->libros,sizeof(struct pila)*pila_libros->num_pilas); // realloc aveces falla entonces 
            //se metre dentro de un ciclo while para que salga cuando termine este proceso
        }
        pila_libros->libros =aux; // pila_libros sera igual 
        inicializar_pila(&pila_libros->libros[pila_libros->num_pilas-1],40);
        push(&pila_libros->libros[pila_libros->num_pilas-1],elibro);

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


void apilar_fecha(struct arreglo_pilas *pila_libros,struct libro *elibro) // estructura de pila de libros,
{// el arreglo es donde meteras los libros, el parametros es el libro sacado y aqui se mete dependiendo su genero
   if (pila_libros->num_pilas == 0 && pila_libros->libros == NULL)// si es la primera pila o es null los libros
    {
        //printf("Entro a nullo");
        pila_libros->num_pilas++; // incrementa el num de pilas
        pila_libros->libros = (struct pila *)malloc (sizeof(struct pila));// primer malloc para la primera
        inicializar_pila(pila_libros->libros,40); // inicializamos la pila
        push(pila_libros->libros,elibro); // hacemos push del primer libro
        return;

    }
    for (int i = 0; i <pila_libros->num_pilas; i++)
    {
        //printf("Entro en la busqueda de comparar\n");
        //printf("Generos actual [%s]  / Genero a buscar [%s]        Iteracion[%d]\n",pila_libros[i].libros->cima->eLibro->genero,elibro->genero,i);
        if (pila_libros->libros[i].cima->eLibro->release_date == elibro->release_date) // busca si hay una pila con el genero que ya esta
        {
            //printf("Genero encontrado------\n");
            push(&pila_libros->libros[i], elibro); // se agrega el libro a la cima que es la pila (una caja por ej)
            //encontrado = true;
            return;
        }
    }
        pila_libros->num_pilas++;
        struct pila *aux;
        aux= NULL;
        while (aux == NULL)
        {
            aux = realloc(pila_libros->libros,sizeof(struct pila)*pila_libros->num_pilas); // realloc aveces falla entonces 
            //se metre dentro de un ciclo while para que salga cuando termine este proceso
        }
        pila_libros->libros =aux; // pila_libros sera igual 
        inicializar_pila(&pila_libros->libros[pila_libros->num_pilas-1],40); // & amperson por que accedemos a la direccion del dato
        // el [i] del num de pila va alfrente por que accedemos al arreglo de pilas  siendo una pila la esctructura *libros*
        push(&pila_libros->libros[pila_libros->num_pilas-1],elibro);
}






struct pila* inicializar_caja(void) // inicializar la caja 1 sola vez
{
    int i;
    struct pila *caja;
    static struct libro libros[45] =  {
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
                            {"Nueva de orueva","Nueva_Prueva",111},
                        };

        
    caja = (struct pila*)malloc(sizeof(struct pila)); // se aloca la memoria a la estructura pila pq al final la caja 
    // es una pila nomas pero sera nuestra pila principal
        if (caja == NULL)
        {
            printf("Erro en alocacion de la memoria");
            exit(EXIT_FAILURE);
        }
    inicializar_pila(caja,45); /// inicializamos la caja que es nuestra pila donde estara todos nuestros libros sin importar el orden
    for(i=0;i<45;i++)
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

void imprimir_pilar_apilada_genero(struct arreglo_pilas *pila_libros) 
{
    for (int i = 0; i < pila_libros->num_pilas;i++)
    {
        //printf("[%d]\n",i);
        printf("[%d]-%s\n\r",i,pila_libros->libros[i].cima->eLibro->genero); // nuestro menu de cajas apiladas
    }
}


void imprimir_pilar_apilada_fecha(struct arreglo_pilas *pila_libros)
{
    for (int i = 0; i < pila_libros->num_pilas;i++)
    {
    printf("[%d]-%d\n\r",i,pila_libros->libros[i].cima->eLibro->release_date); // lo mismo pero con fecha
    }
}


int main ()
{

    
    struct pila *caja;
    caja = inicializar_caja(); // inicializamos la caja
    printf("_--------------------\n");
    //mostrar_caja(caja);
    printf("_--------------------\n");

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
    int gen= 0;
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
            break;
        case 2:
                while(!vacia(caja))
                {

                    apilar_genero(&pila_libros[0],pop(caja)); // mete los libros a la pila 0 
                }
                //printf("Salio");
                imprimir_pilar_apilada_genero(&pila_libros[0]);
                scanf("%d",&gen);
                mostrar_caja(&pila_libros->libros[gen]);
                devolver_libros(&pila_libros[0],caja); // en devolver libros al hacer pop de cada libro, se borra la memoria asi que
                //iniciar_arreglo(&pila_libros[0]); // con esta funcion arreglo la volvemos alocar 
    

            break;

        case 3:
                while(!vacia(caja))
                {

                    apilar_fecha(&pila_libros[0],pop(caja)); // mete los libros a la pila 0 
                }
                //printf("Salio");
                imprimir_pilar_apilada_fecha(&pila_libros[0]);
                scanf("%d",&gen);
                mostrar_caja(&pila_libros->libros[gen]);
                devolver_libros(&pila_libros[0],caja); // en devolver libros al hacer pop de cada libro, se borra la memoria asi que
                //iniciar_arreglo(&pila_libros[0]); // con esta funcion arreglo la volvemos alocar 
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