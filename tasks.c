#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 100
#define LMAX 100

typedef struct Date {
    int day;
    int month;
    int year;
} TDate;

typedef struct Task {
    char description[LMAX];
    char dutyManager[LMAX];
    int priority; // 1 for high, 0 for low
    TDate creationDate;
    TDate dueDate;
} TTask;

typedef struct Data {
    TTask tasks[NMAX];
    int elements;
} TData;

bool isEmpty(TData* data);
bool isFull(TData* data);
void newTask(TData* data, TDate* date);
void modifyTask(TData* data, int index);
void deleteTask(TData* data, int index);
void showTasks(TData* data);
void urgentTasks(TData* data);
void managerTasks(TData* data);

int main() {
    TData data = { .elements = 0 };
    TDate date;
    int option, index;

    printf("\nIngresa el día de hoy: ");
    scanf("%d", &date.day);
    printf("Ingresa el mes de hoy: ");
    scanf("%d", &date.month);
    printf("Ingresa el año de hoy: ");
    scanf("%d", &date.year);

    do {
        // Menú que se mostrará cada vez que se ejecute el programa
        printf("\n-----------------------------------\n");
        printf("Nueva tarea (1)\n");
        printf("Modificar una tarea (2)\n");
        printf("Borrar una tarea (3)\n");
        printf("Mostrar tareas (4)\n");
        printf("Tareas urgentes (5)\n");
        printf("Tareas del manager (6)\n");
        printf("Salir (7)\n");
        printf("-----------------------------------\n");
        printf("Ingresa una opción: ");
        fflush(stdout); fflush(stdin);
        scanf("%d", &option);
        fflush(stdin);

        switch (option) {
            case 1:
                newTask(&data, &date);    
                break;
            case 2:
                printf("\nIngrese el índice de la tarea a modificar: ");
                scanf("%d", &index);
                modifyTask(&data, index);
                break;
            case 3:
                printf("\nIngrese el índice de la tarea a eliminar: ");
                scanf("%d", &index);
                deleteTask(&data, index);
                break;
            case 4: 
                showTasks(&data);
                break;
            case 5: 
                urgentTasks(&data);
                break;
            case 6:
                managerTasks(&data);
                break;
            case 7:
                return 0;
            default:
                printf("\nOpción no válida\n");
                break;
        }
    } while (1);
}

bool isFull(TData* data) {
    return data->elements == NMAX;
}

bool isEmpty(TData* data) {
    return data->elements == 0;
}

void newTask(TData* data, TDate* date) {
    if (isFull(data)) {
        printf("\nLa lista está llena.\n");
        return;
    }

    TTask new_task;
    printf("\nDescripción de la nueva tarea: ");
    scanf(" %99[^\n]", new_task.description);
    printf("Manager a cargo de la nueva tarea: ");
    scanf(" %99[^\n]", new_task.dutyManager);
    printf("Prioridad (1 es alta, 0 es baja): ");
    scanf("%d", &new_task.priority);
    printf("Fecha de vencimiento (día): ");
    scanf("%d", &new_task.dueDate.day);
    printf("Fecha de vencimiento (mes): ");
    scanf("%d", &new_task.dueDate.month);
    printf("Fecha de vencimiento (año): ");
    scanf("%d", &new_task.dueDate.year);

    new_task.creationDate = *date;

    int pos = 0;
    if (new_task.priority == 1) {
        for (pos = data->elements; pos > 0; pos--) {
            data->tasks[pos] = data->tasks[pos - 1];
        }
        data->tasks[0] = new_task;
    } else {
        for (pos = 0; pos < data->elements; pos++) {
            if (data->tasks[pos].priority != 1) {
                break;
            }
        }
        for (int j = data->elements; j > pos; j--) {
            data->tasks[j] = data->tasks[j - 1];
        }
        data->tasks[pos] = new_task;
    }

    data->elements++;
    printf("\n¡Nueva tarea añadida con éxito!\n");
}

void modifyTask(TData* data, int index) {
    char description[LMAX];
    char dutyManager[LMAX];
    TDate dueDate;

    if (isEmpty(data)) {
        printf("\nThe list is empty.");
    } else {
        index--;
        printf("\nNew tasks' description: ");
        scanf("%s", description);
        printf("New tasks' duty manager: ");
        scanf("%s", dutyManager);
        printf("New tasks' due date day: ");
        scanf("%d", &dueDate.day);
        printf("New tasks' due date month: ");
        scanf("%d", &dueDate.month);
        printf("New tasks' due date year: ");
        scanf("%d", &dueDate.year);

        strcpy((*data).tasks[index].description, description);
        strcpy((*data).tasks[index].dutyManager, dutyManager);
        (*data).tasks[index].dueDate.day = dueDate.day;
        (*data).tasks[index].dueDate.month = dueDate.month;
        (*data).tasks[index].dueDate.year = dueDate.year;
        printf("\nThe task at index %d was modified successfully!\n", ++index);
    }
}

void deleteTask(TData* data, int index) {

    if (isEmpty(data)) {
        printf("\nThe list is empty.");
    } else {
        index--;
        int i = index;
    
        for (; i < (*data).elements; i++) {
            (*data).tasks[i] = (*data).tasks[i + 1];
        }
        
        (*data).elements--;
        printf("\nTask at index %d was deleted successfully!\n", ++index);
    }
}

void showTasks(TData* data) {

    if (isEmpty(data)) {
        printf("\nThe list is empty.");
    } else {
        printf("\nTasks: \n");
        for (int i = 0; i < (*data).elements; i++) {
            printf("\n-----------------------------------\n");
            printf("Description: %s\n", (*data).tasks[i].description);
            printf("Duty manager: %s\n", (*data).tasks[i].dutyManager);
            printf("Priority (1 is high, 0 is low): %d\n", (int) (*data).tasks[i].priority);
            printf("Creation date: %d/%d/%d \n", (*data).tasks[i].creationDate.day, (*data).tasks[i].creationDate.month, (*data).tasks[i].creationDate.year);
            printf("Due date: %d/%d/%d", (*data).tasks[i].dueDate.day, (*data).tasks[i].dueDate.month, (*data).tasks[i].dueDate.year);
            printf("\n-----------------------------------\n");
        }
    }
}

void urgentTasks(TData* data){}

void managerTasks(TData* data){}