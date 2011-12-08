
global CPUID_IsSupported

CPUID_IsSupported:
	push ecx
	pushfd
	pop eax
	mov ecx,eax
	xor eax,0x200000
	push eax
	popfd
	pushfd
	pop eax
	xor eax,ecx
	shr eax,21
	and eax,1
	push ecx
	popfd
	pop ecx
	ret


