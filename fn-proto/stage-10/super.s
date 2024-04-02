                xdef _enter_super
                xdef _exit_super


GEMDOS				equ		1


;----------------- SUBROUTINE: void enter_super(); ----------------
; PURPOSE:  lets user enter supervisor mode. From one of the labs
;-------------------------------------------------------------------------------

_enter_super:
		movem.l	d0-2/a0-2,-(sp)

		clr.l	-(sp)		; enter supervisor mode with user stack
		move.w	#$20,-(sp)
		trap	#GEMDOS
		addq.l	#6,sp
		move.l	d0,old_ssp	; save old system stack pointer

		movem.l	(sp)+,d0-2/a0-2
		rts
;--------------------end of Subroutine------------------------------------------




;----------------- SUBROUTINE: void exit_super(); ----------------
; PURPOSE:  lets user exit supervisor mode. From one of the labs
;-------------------------------------------------------------------------------
_exit_super:
		movem.l	d0-2/a0-2,-(sp)

		move.l	old_ssp(pc),-(sp)	; return to user mode, restoring
		move.w	#$20,-(sp)			; system stack pointer
		trap	#GEMDOS
		addq.l	#6,sp

		movem.l	(sp)+,d0-2/a0-2
		rts
;--------------------end of Subroutine------------------------------------------

old_ssp:	ds.l	    1		; SSP save area