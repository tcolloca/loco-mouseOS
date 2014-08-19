GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand,_int_09_hand,_int_74_hand,_int_80_hand
GLOBAL	_set_cursor
GLOBAL	_syscall
GLOBAL  _maskPIC1,_maskPIC2
GLOBAL	_cli,_sti
GLOBAL  _debug
GLOBAL	_inb,_outb

EXTERN  timertick_handler
EXTERN	keyboard_handler
EXTERN	mouse_handler
EXTERN	int_80

SECTION .text


_cli:
	cli	
	ret

_sti:

	sti	
	ret
	
_outb:
	push 	ebp
	mov		ebp, esp
	
	push	eax
	push	edx
	
	mov	eax, [ss:ebp+12]
	mov	edx, [ss:ebp+8]
	out	dx, al
	
	pop	edx
	pop	eax
	
	mov	esp, ebp
	pop	ebp
	ret
	
_inb:
    	push    ebp
    	mov     ebp, esp
	
    	push    edx
	
    	mov     edx, [ss:ebp+8]
    	xor     eax, eax
    	in      al, dx
	
    	pop     edx
	
    	mov     esp, ebp
    	pop     ebp
	ret

_maskPIC1:
	push    ebp
    	mov     ebp, esp
	
	mov     ax, [ss:ebp+8]
	out	0x21, al
	
	pop     ebp
	retn

_maskPIC2:
	push    ebp
	mov     ebp, esp

	mov     ax, [ss:ebp+8]
	out	0xA1, al
	
	pop     ebp
	retn

_read_msw:
	smsw    ax		; get the Machine Status Word
	retn


_lidt:				; Loads the IDTR
	push    ebp
	mov     ebp, esp
	
	push    ebx
	
	mov     ebx, [ss: ebp + 6] ; ds:bx = pointer to IDTR 
	rol	ebx, 16		    	
	lidt    [ds: ebx]          ; loads IDTR
	
	pop     ebx
	
	pop     ebp
	retn

_eoi:
	push	ebp
	mov	ebp, esp
	
	push 	eax
	mov 	al, 0x20
	out 	0x20, al
	pop 	eax
	
	leave
	ret
	
	
_int_80_hand:
	push	ebp
	mov 	ebp, esp
	
	push 	edx
	push 	ecx
	push 	ebx
	push 	eax
	
	sti
	
	call int_80
	
	pop 	ebx
	pop 	ebx
	pop 	ecx
	pop 	edx
	
	leave
	ret


_syscall:
	push 	ebp
	mov 	ebp, esp

	push 	ebx	
	push 	ecx
	push 	edx

	pushf
	
	mov 	edx, [ebp + 20]
	mov 	ecx, [ebp + 16]
	mov 	ebx, [ebp + 12]
	mov 	eax, [ebp + 8]
	
	int 	80h
	
	popf
	
	pop 	edx
	pop 	ecx
	pop 	ebx
	
	call	_eoi
	
	leave
	ret
	

_int_08_hand:				
	push    ds
	push    es                
	pusha       
	
	mov     ax, 0x10 ; TODO: Remove?
	mov     ds, ax
	mov     es, ax  ;Up to here                

	call    timertick_handler                 

	call	_eoi

	popa                            
	pop     es
	pop     ds
	iret

_int_09_hand:
	pusha

	cli

	call	keyboard_handler

	sti

	call	_eoi
	
	popa
	iret
	
_int_74_hand:
	push 	ebp
	mov 	ebp, esp
	
	pusha
	
	in 		al, 0x60
	
	push 	eax
	
	call	mouse_handler
	
	mov		al, 0x20
	out		0xA0, al
	out		0x20, al
	
	pop		eax
	
	popa
	leave
	iret

; Debug para el BOCHS, detiene la ejecució; Para continuar colocar en el BOCHSDBG: set $eax=0
;


_debug:
	push    bp
	mov     bp, sp
	push	ax
vuelve:	
	mov     ax, 1
	cmp		ax, 0
	jne		vuelve
	pop		ax
	pop     bp
	retn
