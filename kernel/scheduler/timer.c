// kernel/driver/timer.c
#include "scheduler.h"

// Agrega la declaración del manejador de interrupción del temporizador
void timer_interrupt_handler() {
    // Manejo actual del temporizador
    // ...

    // Llamar al planificador
    schedule();

    // Enviar fin de interrupción al PIC
    send_eoi();
}