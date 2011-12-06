DATA_SELECTOR equ 0x10

global ___irq0
global ___irq1

___irq0:
	cli
	push byte 0
	push byte 32
	jmp irq_common_stub
___irq1:
	cli
	push byte 0
	push byte 33
	jmp irq_common_stub


extern ___IRQ_Handler

irq_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,DATA_SELECTOR
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov eax,esp
	push eax
	mov eax,___IRQ_Handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp,8
	sti
	iret
