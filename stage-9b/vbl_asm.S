    xref _process_main_game_vbl_isr
	xref _animation_helper
	
	xdef _main_gm_vbl_isr
	xdef _event_animation_vbl_isr



;----------------- SUBROUTINE: void main_gm_vbl_isr(); ----------------
; PURPOSE: VBL ISR for the main game loop( player going through the level)
;			Uses a c helper function to update model, events, level and check for collision
;------------------------------------------------------------------
_main_gm_vbl_isr:
	movem.l	d0-3/a0-3,-(sp)
	jsr     _process_main_game_vbl_isr
	movem.l (sp)+,d0-3/a0-3
	rte




;----------------- SUBROUTINE: void event_animation_vbl_isr(); ----------------
; PURPOSE: VBL ISR for handling animations triggered by events in the game,
;          including fatal collisions (explosion animation) and victory celebrations.
;--------------------------------------------------------------------------------
_event_animation_vbl_isr:
    movem.l d0-3/a0-3,-(sp)
    jsr     _animation_helper
    movem.l (sp)+,d0-3/a0-3
    rte
