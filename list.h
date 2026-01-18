#pragma once
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>

typedef struct{
    char* type; //es la lista real, List de por si es solo un
    //struct de datos, la que lleva los datos realmente es un puntero
    //a char, en list.c esta la explicacion logica
    uint8_t size; //tamano del tipo de dato, es decir cuanto pesa el tipo
    //int = 4 bytes, char = 1 byte, etc
    uint16_t count; //cantidad de valores en la lista
    uint16_t last; // ultimo indice de la lista
}List;

//Devuelve un puntero a una lista creada en el stack)
void StackCreateList(List* l, uint8_t size, int count);
//Devuelve un puntero a una lista creada en el heap
List* createList(List* l, uint8_t size, int count);
//Inserta un valor a lo ultimo de la lista
void PushLast(List* list, void* value);
//Obtiene el valor de la lista segun un indice
void* GetValueIn(List* l, int index);
//Cambia un valor de la lista en un indice
void ChangeValueIn(List* l, void* value, int index);