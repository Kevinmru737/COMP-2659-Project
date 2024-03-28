    xref _kbd_driver
    xdef _kbd_isr


inservice_reg equ $FFFA11

_kbd_isr: 	movem.l	d0-3/a0-3,-(sp)
	jsr     _kbd_driver
	movem.l (sp)+,d0-3/a0-3
	and.b   #$BF,inservice_reg
	rte