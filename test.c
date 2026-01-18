#include<stdio.h>
#include<stdlib.h>
#include"list.h" 
//Guia pa juandi:
//MACROS
#define GetValueRaw(T, b, y) *(T*)GetValueIn(b, y) 
//GetValueRaw se usa para acceder a uno de los valores de la lista, 
//esta retorna el valor del indice al que apunta, a diferencia de
//GetValueP, la cual retorna la direccion de memoria del valor
//en esencia retorna un puntero, este es necesario si la lista es de strings
//ya que aqui los strings son un puntero tipo char, por lo que si usai
//GetValueRaw para un char* (string), dara un error de memoria
//(se desreferencia el propio char*, lo que solamente da el primer caracter)
#define GetValueP(T, b, y) (T*)GetValueIn(b,y)

//pon aqui papi
#define Push(T, list, v) PushLast(list, &(T){v})
#define ChangeValueRaw(T, list, v, i) ChangeValueIn(list, &(T){v}, i)
//macro para crear una variable temporal en el stack, en esencia, ningun literal (es decir, 
//constante que se pasa como argumento a una funcion sin variable, osea digamos Push(34)),
//tiene una direccion de memoria valida, por lo que es necesario primero asignarle una direccion de memoria
//para evitar tener que declarar la variable a mano, se crea una variable temporal en el stack con una direccion de memoria
//esta es la sintaxis &(tipodedato){dato}, en esencia el compilador esta haciendo esto
//tipodedato a = dato;
//es nada mas por comodidad, para evitar tener que declarar una variable cada vez que se quiera pasar un argumento


int main(int argc, char* argv)
{
    //en list.h esta la explicacion de que hace cada funcion
    List slist;
    StackCreateList(&slist, sizeof(int), 3);
    Push(int, &slist, 322);
    printf("list in stack, values in heap: %i\n", GetValueRaw(int, &slist, slist.last));
    List* charList = createList(charList, sizeof(char*), 3 );
    PushLast(charList, "holaa");
    printf("char*: %s \n", GetValueP(char, charList, charList->last));
    List* list;
    list = createList(list, sizeof(int), 3);
    Push(int, list, 577);
    ChangeValueIn(list, &(int){4777}, 2);
    printf("%i\n", GetValueRaw(int, list, list->count - 1));
    
    printf("\n\n\n\n\n ORGANIZED IMPLEMENTATIONS");
    printf("\n STACK LISTS\n");
    List stringList;
    List flist;
    StackCreateList(&flist, sizeof(float), 4);
    for(int i = 0; i < 4; i++)
    {
        Push(float, &flist, i * 3.1459 / 2.01);
        printf("value: %f \n", GetValueRaw(float, &flist, flist.last));
    }
 
    StackCreateList(&stringList, sizeof(char*), 30);
    for(int i = 0; i < 10; i++)
    {
        Push(char*, &stringList, "omlaa");
        printf("value: %s \n", GetValueRaw(char*, &stringList, stringList.last));
    }
    ChangeValueRaw(float, &flist, 7.7777, 0);
    printf("changed first: %f\n", GetValueRaw(float, &flist,0 ));

    ChangeValueIn(&stringList, "ayyy", 0); 
    printf("changed first: %s\n", GetValueP(char , &stringList,0 ));
    printf("HEAP LISTS\n");

    List* stlist = createList(stlist, sizeof(float), 5);
    List* chlist = createList(chlist, sizeof(char*), 15);
    for(int i = 0; i < 10; i++)
    {
        Push(char*, chlist, "omlaa");
        printf("value: %s \n", GetValueRaw(char*, chlist, chlist->last));
    }
 
    for(int i = 0; i < 4; i++)
    {
        Push(float, stlist, i * 3.14522229 / 7.01);
        printf("value: %f \n", GetValueRaw(float, stlist, stlist->last));
    }
    ChangeValueRaw(float, stlist, 7.7777, 0);
    printf("changed first: %f\n", GetValueRaw(float, stlist,0 ));

    ChangeValueIn(chlist, "ayyy", 0); 
    printf("changed first: %s\n", GetValueP(char , chlist,0 ));
    //al final tendriamos que liberar cada puntero con free(), pero ya estoy cansado y pues no es necesario para esto XDD
    //el por que de esto es por que si ya no vamos a utilizar un puntero, dejamos una direccion de memoria
    //colgando sin usar, lo que es un desperdicio de recursos 
    return 0;
}