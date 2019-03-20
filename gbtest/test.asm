;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.8.0 #10562 (Mac OS X x86_64)
;--------------------------------------------------------
	.module test
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _gprint
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;test.c:5: int main() { 
;	---------------------------------
; Function main
; ---------------------------------
_main::
;test.c:6: gprint("Alaric's sound tests");
	ld	hl, #___str_0
	push	hl
	call	_gprint
	add	sp, #2
;test.c:8: NR52_REG = 0x80u;
	ld	hl, #0xff26
	ld	(hl), #0x80
;test.c:9: NR50_REG = 0x77u;
	ld	l, #0x24
	ld	(hl), #0x77
;test.c:10: NR51_REG = 0xffu;
	ld	l, #0x25
	ld	(hl), #0xff
;test.c:34: NR41_REG = 0x00u;
	ld	l, #0x20
	ld	(hl), #0x00
;test.c:35: NR42_REG = 0xc0u;
	ld	l, #0x21
	ld	(hl), #0xc0
;test.c:36: NR43_REG = 0x18u;
	ld	l, #0x22
	ld	(hl), #0x18
;test.c:37: NR44_REG = 0x80u;
	ld	l, #0x23
	ld	(hl), #0x80
;test.c:39: NR50_REG = 0x77u;
	ld	l, #0x24
	ld	(hl), #0x77
;test.c:40: return 0; 
	ld	de, #0x0000
;test.c:41: }
	ret
___str_0:
	.ascii "Alaric's sound tests"
	.db 0x00
	.area _CODE
	.area _CABS (ABS)
