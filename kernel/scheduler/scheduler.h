// kernel/scheduler/scheduler.h
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

void scheduler_init();
void schedule();
void add_process(process_t *process);
process_t *get_current_process();

#endif // SCHEDULER_H