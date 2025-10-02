//
// Luis Llopis, Data Structures, UMA.
//

#include "Scheduler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node* Scheduler_new() {

  return NULL; // Lista vacía representada como puntero NULL
}

size_t Scheduler_size(const struct Node* p_last) {
if (p_last == NULL) return 0;

size_t count = 0;
const struct Node* it = p_last->p_next; // primero (head)
do {
++count;
it = it->p_next;
} while (it != p_last->p_next);
return count;
}

void Scheduler_clear(struct Node** p_p_last) {
if (p_p_last == NULL || *p_p_last == NULL) return;

struct Node* last = *p_p_last;
struct Node* it = last->p_next; // primero
// Recorremos y liberamos todos los nodos
while (it != last) {
struct Node* next = it->p_next;
free(it);
it = next;
}
// Falta liberar 'last' en sí
free(last);
*p_p_last = NULL;
}

struct Task* Scheduler_first(const struct Node* p_last) {
if (p_last == NULL) return NULL;
const struct Task* first = &p_last->p_next->task;
// Devolver una copia asignada en el heap
return Task_copyOf(first);
}

// Variante que escribe la primera tarea en una estructura proporcionada
void Scheduler_first_v2(const struct Node* p_last, struct Task* p_task) {
if (p_last == NULL || p_task == NULL) return;
*p_task = p_last->p_next->task; // copia por valor (incluye el array name)
}

void Scheduler_enqueue(struct Node** p_p_last, const struct Task* p_task) {
if (p_p_last == NULL || p_task == NULL) return;

struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
if (new_node == NULL) return; // sin memoria, no encolamos

// Guardamos una COPIA de la tarea (asignación por valor)
new_node->task = *p_task;

if (*p_p_last == NULL) {
// Cola vacía: el nuevo nodo se apunta a sí mismo
new_node->p_next = new_node;
*p_p_last = new_node;
} else {
// Insertar después de last y antes de first (al final lógico)
new_node->p_next = (*p_p_last)->p_next; // old first
(*p_p_last)->p_next = new_node;
*p_p_last = new_node; // ahora este es el último
}
}

void Scheduler_dequeue(struct Node** p_p_last) {
if (p_p_last == NULL || *p_p_last == NULL) return;

struct Node* last = *p_p_last;
struct Node* first = last->p_next;

if (first == last) {
// Solo un nodo
free(first);
*p_p_last = NULL;
} else {
// Más de un nodo: saltamos el primero
last->p_next = first->p_next;
free(first);
}
}

void Scheduler_print(const struct Node* p_last) {
if (p_last == NULL) {
printf("(Scheduler vacío)\n");
return;
}

const struct Node* it = p_last->p_next; // primero
do {
Task_print(&it->task);
it = it->p_next;
} while (it != p_last->p_next);
}