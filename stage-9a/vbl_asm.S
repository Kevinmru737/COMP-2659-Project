    xref _process_main_game_vbl_isr
    xref _process_explosion_vbl_isr
	xdef _main_gm_vbl_isr
    xdef _expl_vbl_isr

;----------------- SUBROUTINE: void vbl_isr(); ----------------
; PURPOSE:  IS the Vertical Blank ISR. Calls a helper function in C do process
;           all the synchronous events
;-------------------------------------------------------------------------------
_main_gm_vbl_isr:
	movem.l	d0-4/a0-4,-(sp)
	jsr     _process_main_game_vbl_isr
	movem.l (sp)+,d0-4/a0-4
	rte

;----------------- SUBROUTINE: void expl_vbl_isr(); ----------------
; PURPOSE:  IS the Vertical Blank ISR for when the player is in the explosion animation
;-------------------------------------------------------------------------------
_expl_vbl_isr:
	movem.l	d0-4/a0-4,-(sp)
	jsr     _process_explosion_vbl_isr
	movem.l (sp)+,d0-4/a0-4
	rte
