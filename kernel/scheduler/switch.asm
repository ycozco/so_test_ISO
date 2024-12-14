; kernel/scheduler/switch.asm
[BITS 32]
[GLOBAL context_switch]

; context_switch:
; Funciona como: context_switch(current_process, next_process)
; Parámetros en:
;   EAX - puntero al proceso actual
;   EBX - puntero al próximo proceso

context_switch:
    ; Guardar registros del proceso actual
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ebp

    ; Asumimos que EAX contiene el puntero al proceso actual
    ; Guardar el puntero de stack del proceso actual
    mov [eax].process_t.stack_pointer, esp

    ; Rellenar los registros con los valores del próximo proceso
    mov esp, [ebx].process_t.stack_pointer

    ; Restaurar registros del próximo proceso
    pop ebp
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    ret