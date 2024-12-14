// kernel/scheduler/process.h
#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

typedef enum {
    PROCESS_STATE_NEW,
    PROCESS_STATE_READY,
    PROCESS_STATE_RUNNING,
    PROCESS_STATE_WAITING,
    PROCESS_STATE_TERMINATED
} process_state_t;

typedef enum {
    PROCESS_TYPE_SYSTEM,
    PROCESS_TYPE_INTERACTIVE,
    PROCESS_TYPE_BATCH
} process_type_t;

typedef struct {
    uint32_t pid;
    process_state_t state;
    process_type_t type;
    uint32_t priority;
    uint32_t *stack_pointer;
    uint32_t *base_pointer;
    uint32_t *instruction_pointer;
    // Añade otros campos necesarios, como registros, manejo de memoria, recursos, etc.
} process_t;

// Funciones para manejar procesos
process_t *process_create(void (*entry_point)(), process_type_t type);
void process_destroy(process_t *process);
void process_exit();
void yield();

#endif // PROCESS_H