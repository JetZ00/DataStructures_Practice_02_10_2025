//
// Luis Llopis, Data Structures, UMA.
//

#include "Task.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Task* Task_new(unsigned int id, const char* name, int quantum) {

if (name == NULL) return NULL;  // Nombre NULL: evitamos crash devolviendo NULL

size_t len = strlen(name);      // Longitud del nombre

if (len > MAX_NAME_LEN) {       // Nombre demasiado largo: evitamos overflow devolviendo NULL
return NULL;
}

struct Task* t = (struct Task*)malloc(sizeof(struct Task));  // Reserva de memoria para la estructura Task
if (t == NULL) return NULL; // malloc ha fallado

t->id = id;                    // Inicializacion de los campos
t->quantum = quantum;

memcpy(t->name, name, len);   // Copia del nombre
t->name[len] = '\0';          // Aseguramos el terminador nulo

return t;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void Task_free(struct Task** p_p_task) {
  
if (p_p_task == NULL || *p_p_task == NULL) return;

free(*p_p_task);            // Liberacion de la memoria reservada para la estructura Task (Valor)

*p_p_task = NULL;           // Liberacion de la memoria reservada para la estructura Task (Dirección)
//¿Y se podria poner directamente el p_task = NULL?
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Task* Task_copyOf(const struct Task* p_task) {

if (p_task == NULL) return NULL;

return Task_new(p_task->id,p_task->name,p_task->quantum); // Reutilizamos la funcion de creacion
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void Task_print(const struct Task* p_task) {

if (p_task == NULL) {
printf("(Task NULL)\n");
return;
}

printf("Task{id=%u, name=\"%s\", quantum=%d}\n",
p_task->id, p_task->name, p_task->quantum);           // Imprime los campos de la estructura Task
}

////////////////////////////////////////////////////////////////////////////////////////////////////////