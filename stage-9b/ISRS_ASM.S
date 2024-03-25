    xref _process_vbl_isr
    xref _process_keyboard_driver_isr
	xdef _vbl_isr
	xdef _keyboard_driver_isr
;----------------- SUBROUTINE: void vbl_isr(); ----------------
; PURPOSE:  IS the Vertical Blank ISR. Calls a helper function in C do process
;           all the synchronous events
;-------------------------------------------------------------------------------
_vbl_isr:
	movem.l	d0-d2/a0-a2,-(sp)
	jsr     _process_vbl_isr
	movem.l (sp)+,d0-d2/a0-a2
	rte

_keyboard_driver_isr:
	movem.l	d0-d2/a0-a2,-(sp)
	jsr     _process_keyboard_driver_isr
	movem.l (sp)+,d0-d2/a0-a2
	rte
