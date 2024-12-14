// kernel/scheduler/resource.c
#include "resource.h"

#define MAX_RESOURCES 32

static resource_t resources[MAX_RESOURCES];

void resource_init() {
    for (uint32_t i = 0; i < MAX_RESOURCES; i++) {
        resources[i].id = i;
        resources[i].in_use = false;
        resources[i].owner = NULL;
    }
}

resource_t *resource_request(process_t *process) {
    for (uint32_t i = 0; i < MAX_RESOURCES; i++) {
        if (!resources[i].in_use) {
            resources[i].in_use = true;
            resources[i].owner = process;
            return &resources[i];
        }
    }
    // Si no hay recursos disponibles, devuelve NULL o implementa espera
    return NULL;
}

void resource_release(process_t *process, resource_t *resource) {
    if (resource->owner == process) {
        resource->in_use = false;
        resource->owner = NULL;
    }
}