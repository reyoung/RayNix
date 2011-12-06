DATA_SELECTOR equ 0x10

; The Real ISR Handler. To get ISR types, and regs to C function
global ___isr0
global ___isr1
global ___isr2
global ___isr3
global ___isr4
global ___isr5

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
	



