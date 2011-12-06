; Reference http://www.osdever.net/bkerndev/Docs/irqs.htm

DATA_SELECTOR equ 0x10

global ___irq0
global ___irq1
global ___irq2
global ___irq3
global ___irq4
global ___irq5
global ___irq6
global ___irq7
global ___irq8
global ___irq9
global ___irq10
global ___irq11
global ___irq12
global ___irq13
global ___irq14
global ___irq15



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
___irq2:
	cli
	push byte 0
	push byte 34
	jmp irq_common_stub
___irq3:
	cli
	push byte 0
	push byte 35
	jmp irq_common_stub
___irq4:
	cli
	push byte 0
	push byte 36
	jmp irq_common_stub
___irq5:
	cli
	push byte 0
	push byte 37
	jmp irq_common_stub
___irq6:
	cli
	push byte 0
	push byte 38
	jmp irq_common_stub

___irq7:
	cli
	push byte 0
	push byte 39
	jmp irq_common_stub

___irq8:
	cli
	push byte 0
	push byte 40
	jmp irq_common_stub


___irq9:
	cli
	push byte 0
	push byte 41
	jmp irq_common_stub

___irq10:
	cli
	push byte 0
	push byte 42
	jmp irq_common_stub

___irq11:
	cli
	push byte 0
	push byte 43
	jmp irq_common_stub

___irq12:
	cli	
	push byte 0
	push byte 44
	jmp irq_common_stub

___irq13:
	cli
	push byte 0
	push byte 45
	jmp irq_common_stub

___irq14:
	cli
	push byte 0
	push byte 46
	jmp irq_common_stub

___irq15:
	cli
	push byte 0
	push byte 47
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
	;sti
	iret
