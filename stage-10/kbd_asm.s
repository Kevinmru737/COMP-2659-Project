    xref _kbd_driver
    xdef _kbd_isr
	xdef _set_ipl


inservice_reg equ $FFFA11

_kbd_isr: 	movem.l	d0-3/a0-3,-(sp)
	jsr     _kbd_driver
	movem.l (sp)+,d0-3/a0-3
	and.b   #$BF,inservice_reg
	rte


_set_ipl: 
        move.w sr,d0
        move.w d0,-(sp) ; place orig. sr on stack
        
        lsr.w #8,d0 ; will return orig. ipl
        and.w #$0007,d0 ; ... in d0.w
        
        andi.w #$F8FF,(sp)
        move.w d1,-(sp)
        
        move.w 8(sp),d1 ; place new ipl in d1.w
        lsl.w #8,d1
        
        and.w #$0700,d1
        or.w d1,2(sp) ; insert it into sr on stack
        move.w (sp)+,d1
        rte 