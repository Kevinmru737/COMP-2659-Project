

    xref        _enter_super
    xref        _exit_super
	xdef		_clear_screen
	xdef		_clear_except_ground
	xdef		_set_video_base
	xdef		_get_video_base

video_reg_address  equ		$FFFF8201


;clears the screen	
;Author : Marc Shroeder	
base		equ		64		; offset from SP, not A6
_clear_screen:	movem.l	d0-7/a0-6,-(sp)
		lea			zeros,a0
		movem.l		(a0)+,d1-7/a1-6
		movea.l		base(sp),a0
		adda.l		#32000,a0
		move.w		#614,d0
fill_loop:	movem.l		d1-7/a1-6,-(a0)
		dbra		d0,fill_loop
		movem.l		d1-5,-(a0)
		movem.l		(sp)+,d0-7/a0-6
		rts



_clear_except_ground: 
		movem.l		d0-7/a0-6,-(sp)
		lea			zeros,a0
		movem.l		(a0)+,d1-7/a1-6
		movea.l		base(sp),a0
		adda.l		#21680,a0
		move.w		#415,d0
fill:		movem.l		d1-7/a1-6,-(a0)
		dbra			d0,fill
		movem.l		d1-7/a1-5,-(a0)
		movem.l		(sp)+,d0-7/a0-6
		rts





;----------------- SUBROUTINE: UINT32 *get_video_base(); ----------------
; PURPOSE:  Returns the address stored at the video base register
;------------------------------------------------------------------
_get_video_base:
		link	a6,#0
		movem.l	d3/a0,-(sp)

		jsr _enter_super

		clr.l 	d3
		move.l  #video_reg_address,a0
		movep.w (a0),d3
		lsl.l   #8,d3

		jsr _exit_super
		
		move.l d3,d0
		
		movem.l	(sp)+,d3/a0
		unlk	a6
		rts
;--------------------end of Subroutine------------------------------------------





;----------------- SUBROUTINE: void set_video_base(UINT32 *); ----------------
; PURPOSE:  Changes the address stored at the video base register to the address
;           passed into the function
;-------------------------------------------------------------------------------
NEW_VIDEO_BASE_OFFSET 	equ     	8

_set_video_base:
		link	a6,#0
		movem.l	d0/a0,-(sp)

		jsr		_enter_super

		clr.l 	d0
		move.l	NEW_VIDEO_BASE_OFFSET(a6),d0
		lsr.l   #8,d0
		move.l  #video_reg_address,a0
		movep.w d0,(a0)
		
		jsr		_exit_super
		
		movem.l	(sp)+,d0/a0
		unlk	a6
		rts
;--------------------end of Subroutine------------------------------------------








zeros:		ds.l		13