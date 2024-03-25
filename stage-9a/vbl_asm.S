    xref _process_main_game_vbl_isr
    xref _process_keyboard_driver_isr
	xdef _main_gm_vbl_isr

;----------------- SUBROUTINE: void vbl_isr(); ----------------
; PURPOSE:  IS the Vertical Blank ISR. Calls a helper function in C do process
;           all the synchronous events
;-------------------------------------------------------------------------------
_main_gm_vbl_isr:
	movem.l	d0-d2/a0-a2,-(sp)
	jsr     _process_main_game_vbl_isr
	movem.l (sp)+,d0-d2/a0-a2
	rte

