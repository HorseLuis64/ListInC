#include "list.h"

//actualiza el ultimo valor de la lista
void UpdateLast(List* l){
    l->last = l->count -1;
}
List* createList(List* l, uint8_t size, int count)
{
    if(count <= 0)
    {
        printf("value most be greater than 0");
        return NULL;
    }
    l = calloc(1, sizeof(List));
    //malloc reserva memoria en el heap, es decir, 
    //se encarga de buscar en la ram un espacio disponible
    //y reserva memoria ahi en bytes, por ejemplo
    //si queremos guardar 4 enteros (cada uno pesa 4 bytes)
    //llamamos malloc con el tamano total (4 * 3)
    //y malloc reservara esa cantidad de memoria
    //calloc hace esencialmente lo mismo, la unica diferencia es que los bytes que
    //reserva los inicializa en 0
    l->size = size;
    l->count = count;

    l->type = malloc(size * count);
    //algo importante sobre C, es que los punteros no
    //cambian segun el tipo, es decir, son direcciones de memoria
    //y nada mas, pero, el compilador es el que trata distinto a estas direcciones
    // en el caso de malloc, el compilador decide como son los saltos entre bloques de memoria
    //por ejemplo, si hacemos un int* a = malloc(3 sizeof(int))
    //y accedemos al segundo valor (recordemos que un array simplemente es un bloque de memoria 
    //que se divide en saltos de bytes, es decir malloc almacena un array)
    //a[1] = 2;
    //internamente el compilador sabe que debe saltar entre indice e indice de a 4 bytes
    //[0] -> 4 bytes [1] -> 4 bytes -> [2], por que malloc fue inicializado con un puntero a un int
    //int*, pero si hubiera sido inicializado con un puntero a char*, los saltos serian de 1 byte
    //mas adelante se vera por que esto es importante
    //printf("addres succesful %p\n", l->type);
    UpdateLast(l);
    return l;
}
void StackCreateList(List* l, uint8_t size, int count)
{
    //lo mismo pero en stack XDDD
    char* ty = malloc(size * count);
    if(ty != NULL)
    {
    }
    *l = (List){ty, size, count};
    UpdateLast(l);
}

void PushLast(List *list, void* value)
{
    list->count++;
    //void* es un puntero desconocido, es decir, apunta a una direccion de memoria
    //pero el compilador no sabe a que tipo apunta, que quiere decir esto?
    //como vimos anteriormente el compilador es el que trata las direcciones de memoria
    //segun al tipo de puntero que son igualados, pero en el caso de void*, 
    //el compilador no sabe como tratarlo ya que no esta inicialiazo en un tipo, es por eso que no podemos 
    //anadir directamente el valor de value a nuestro list.type (la lista real), ya que este es un puntero a un
    //char, si intentaramos algo como list.type[indice] = value, solamente estariamos copiando un caracter dentro 
    //de un solo caracter, ya que recordemos, que los char solo pesan 1 byte, osea cada bloque solamente puede almacenar 
    //1 byte

    list->type = realloc(list->type, list->size * list->count);
    //realloc actualiza el espacio de memoria que previamente fue creado en malloc, es decir 
    // si previamente en malloc reservamos 10 bytes de memoria, y queremos anadir otro valor a la lista
    //de 3 bytes, realloc agarra esos 10 bytes, y le anade otros 3 bytes de memoria
    //printf("current count of values, copying in index: %i\n"
        //"realloc in size: %i\n"
        //"copying in: %i", list->count, list->count * list->size, list->count * list->size);

    memcpy(list->type + (( list->count - 1) * list->size), value, list->size);
    //memcpy copia cada uno de los bytes de un puntero, y los pone en otro, es decir, copia tal cual la informacion
    //de un dato hacia otro en bytes, por ejemplo -> 
    //0x9A  0x3B    0x4F === guardado en puntero A 
    //se copia a
    //0x9A  0x3B    0x4F === copiado directamente en puntero B
    //esto nos es util por que a diferencia de acceder a traves de un indice
    //copiamos en cada indice que necesitemos el byte de informacion, por lo que con eso solucionamos el problema 
    //de los tamanos desconocidos
    UpdateLast(list);
}





void* GetValueIn(List* l, int index)
{
    if(index >= l->count){
        printf("index greater than actual values");
        return NULL;
    }
    //esencialmente retornamos una direccion de memoria void, luego en el programajo
    //nos encargamos de hacerle un cast al tipo que necesitamos
    
    return (void*)(l->type + (l->size * index));
}

void ChangeValueIn(List* l, void* value, int index)
{
    if(index >= l->count){
        printf("index greater than actual values");
        return;
    }
    //hacemos lo mismo con push, buscamos la direccion de memoria, pero en vez de usar count
    //(cantidad de indices de la lista), usamos index para definir en que espacio queremos cambiar el valor
    if(memcpy(l->type + (index * l->size), value, l->size) != NULL)
    {
        //printf("value changed succes\n");
    }
}