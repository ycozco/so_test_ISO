// kernel/scheduler/process.c
#include "process.h"
#include "scheduler.h"
#include "phymem.h"
#include "virtmem.h"
#include "dadio.h"

static uint32_t next_pid = 1;
static process_t *current_process = NULL;

process_t *process_create(void (*entry_point)(), process_type_t type) {
    process_t *process = (process_t *)pmmngr_allocate_block();
    if (!process) {
        // Manejar error de asignación
        return NULL;
    }

    process->pid = next_pid++;
    process->state = PROCESS_STATE_NEW;
    process->type = type;
    process->priority = 0; // Establece la prioridad según sea necesario
    process->instruction_pointer = (uint32_t *)entry_point;
    // Inicializa otros campos, como la pila y los registros

    return process;
}

void process_destroy(process_t *process) {
    // Libera recursos asignados al proceso
    pmmngr_free_block((uint32_t *)process);
}

void process_exit() {
    current_process->state = PROCESS_STATE_TERMINATED;
    schedule(); // Llamar al planificador para cambiar de proceso
}

void yield() {
    schedule(); // Ceder el control al planificador
}