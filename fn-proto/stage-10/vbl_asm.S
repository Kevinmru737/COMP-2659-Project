    xref _process_vbl_isr
	xdef _vbl_isr


;----------------- SUBROUTINE: void vbl_isr(); ----------------
; PURPOSE: VBL ISR for the game
;------------------------------------------------------------------
_vbl_isr:
	movem.l	d0-3/a0-3,-(sp)
	jsr     _process_vbl_isr
	movem.l (sp)+,d0-3/a0-3
	rte



