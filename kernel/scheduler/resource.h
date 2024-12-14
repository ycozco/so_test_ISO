// kernel/scheduler/resource.h
#ifndef RESOURCE_H
#define RESOURCE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t id;
    bool in_use;
    process_t *owner;
    // Otros detalles del recurso
} resource_t;

void resource_init();
resource_t *resource_request(process_t *process);
void resource_release(process_t *process, resource_t *resource);

#endif // RESOURCE_H