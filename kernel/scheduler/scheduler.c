// kernel/scheduler/scheduler.c
#include "scheduler.h"
#include "process.h"
#include "dadio.h"

#define MAX_PROCESSES 256

static process_t *process_table[MAX_PROCESSES];
static process_t *current_process = NULL;
static uint32_t process_count = 0;

void scheduler_init() {
    // Inicializa la tabla de procesos
    for (uint32_t i = 0; i < MAX_PROCESSES; i++) {
        process_table[i] = NULL;
    }
    process_count = 0;
}

void add_process(process_t *process) {
    if (process_count < MAX_PROCESSES) {
        process_table[process_count++] = process;
        process->state = PROCESS_STATE_READY;
    } else {
        // Manejar error: máximo de procesos alcanzado
    }
}

process_t *get_current_process() {
    return current_process;
}

extern void context_switch(process_t *current, process_t *next);

void schedule() {
    if (process_count == 0) {
        // No hay procesos para ejecutar
        return;
    }

    static uint32_t last_process = 0;
    uint32_t next_process = (last_process + 1) % process_count;

    process_t *prev_process = current_process;
    current_process = process_table[next_process];

    if (prev_process != current_process) {
        // Cambiar de contexto entre prev_process y current_process
        context_switch(prev_process, current_process);
    }

    last_process = next_process;
}