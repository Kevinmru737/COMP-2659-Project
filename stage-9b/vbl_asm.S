    xref _process_vbl_isr
	xdef _vbl_isr




;----------------- SUBROUTINE: void main_gm_vbl_isr(); ----------------
; PURPOSE: VBL ISR for the main game loop( player going through the level)
;			Uses a c helper function to update model, events, level and check for collision
;------------------------------------------------------------------
_vbl_isr:
	movem.l	d0-3/a0-3,-(sp)
	jsr     _process_vbl_isr
	movem.l (sp)+,d0-3/a0-3
	rte



