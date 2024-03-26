    xref _kbd_driver
    xdef _kbd_isr

_kbd_isr: 	movem.l	d0-3/a0-3,-(sp)
	jsr     _kbd_driver
	movem.l (sp)+,d0-3/a0-3
	rte