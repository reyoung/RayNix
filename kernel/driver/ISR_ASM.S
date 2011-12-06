DATA_SELECTOR equ 0x10

; The Real ISR Handler. To get ISR types, and regs to C function
global ___isr0
global ___isr1
global ___isr2
global ___isr3
global ___isr4
global ___isr5
global ___isr6
global ___isr7
global ___isr8
global ___isr9
global ___isr10
global ___isr11
global ___isr12
global ___isr13
global ___isr14
global ___isr15
global ___isr16
global ___isr17
global ___isr18
global ___isr19
global ___isr20
global ___isr21
global ___isr22
global ___isr23
global ___isr24
global ___isr25
global ___isr26
global ___isr27


___isr0:
	cli	; Close the interrupt
	push byte 0 ;	Exception Error Code, Fake
	push byte 0 ;	ISR Type
	jmp	isr_common_stub
___isr1:
	cli
	push byte 0
	push byte 1
	jmp isr_common_stub

___isr2:
	cli
	push byte 0
	push byte 2
	jmp isr_common_stub
___isr3:
	cli
	push byte 0
	push byte 3
	jmp isr_common_stub
___isr4:
	cli 
	push byte 0
	push byte 4
	jmp isr_common_stub
___isr5:
	cli
	push byte 0
	push byte 5
	jmp isr_common_stub
___isr6:
	cli
	push byte 0
	push byte 6
	jmp isr_common_stub
___isr7:
	cli
	push byte 0
	push byte 7
	jmp isr_common_stub

___isr8:
	cli
	push byte 8
	jmp isr_common_stub

___isr9:
	cli
	push byte 0
	push byte 9
	jmp isr_common_stub

___isr10:
	cli
	push byte 10
	jmp isr_common_stub

___isr11:
	cli
	push byte 11
	jmp isr_common_stub

___isr12:
	cli
	push byte 12
	jmp isr_common_stub

___isr13:
	cli
	push byte 13
	jmp isr_common_stub

___isr14:
	cli
	push byte 14
	jmp isr_common_stub

___isr15:
	cli
	push byte 0
	push byte 15
	jmp isr_common_stub
___isr16:
	cli
	push byte 0
	push byte 16
	jmp isr_common_stub
___isr17:
	cli
	push byte 0
	push byte 17
	jmp isr_common_stub
___isr18:
	cli
	push byte 0
	push byte 18
	jmp isr_common_stub
___isr19:
	cli
	push byte 0
	push byte 19
	jmp isr_common_stub
___isr20:
	cli
	push byte 0
	push byte 20
	jmp isr_common_stub
___isr21:
	cli
	push byte 0
	push byte 21
	jmp isr_common_stub
___isr22:
	cli
	push byte 0
	push byte 22
	jmp isr_common_stub
___isr23:
	cli
	push byte 0
	push byte 23
	jmp isr_common_stub
___isr24:
	cli
	push byte 0
	push byte 24
	jmp isr_common_stub
___isr25:
	cli
	push byte 0
	push byte 25
	jmp isr_common_stub
___isr26:
	cli
	push byte 0
	push byte 26
	jmp isr_common_stub
___isr27:
	cli
	push byte 0
	push byte 27
	jmp isr_common_stub





extern ___ISR_Handler

isr_common_stub:
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
	mov eax,___ISR_Handler
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
	



