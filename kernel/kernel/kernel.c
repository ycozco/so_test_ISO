// kernel/kernel/kernel.c
#include <stdint.h>
#include "dadio.h"
#include "phymem.h"
#include "virtmem.h"
#include "timer.h"
#include "keyboard.h"
#include "hal.h"
#include "inthandling.h"
#include "ATA.h"
#include "FAT12.h"
#include "scheduler.h"
#include "process.h"

extern void refresh_stack();
extern void kshell();

uint8_t array[512];

void initialize_all(uint32_t mmapsize);

// Funciones de los procesos
void some_function() {
    // Código del proceso interactivo
    while (1) {
        // Realiza alguna tarea interactiva
    }
}

void another_function() {
    // Código del proceso batch
    while (1) {
        // Realiza tareas en segundo plano
    }
}

void kmain(uint32_t mmapsize, uint32_t data_sect, uint32_t root_sect, uint32_t fat_sect) {
    gdt_init();
    pmmngr_init(mmapsize); // Inicializa el gestor de memoria física
    vmmngr_init();  // Inicializa el gestor de memoria virtual
    clear();

    refresh_stack(); // Remapea la pila
    remove_identity_map();

    interrupt_init();
    kbc_init();
    set_timer(0xFFFF);

    // Inicializar el planificador
    scheduler_init();

    // Crear y agregar procesos
    process_t *proc1 = process_create(&some_function, PROCESS_TYPE_INTERACTIVE);
    add_process(proc1);

    process_t *proc2 = process_create(&another_function, PROCESS_TYPE_BATCH);
    add_process(proc2);

    // Crear y agregar el proceso del shell del kernel
    process_t *shell_proc = process_create(&kshell, PROCESS_TYPE_INTERACTIVE);
    add_process(shell_proc);

    // Iniciar la planificación de procesos
    schedule();

    // Bucle infinito del kernel
    while (1) {
        // Puedes agregar aquí tareas del kernel si es necesario
        // Por ejemplo, manejo de interrupciones o tareas de mantenimiento
    }
}