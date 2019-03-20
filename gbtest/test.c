#include <gb/console.h>
#include <gb/gb.h>
#include <gb/drawing.h>

int main() { 
	gprint("Alaric's sound tests");

	NR52_REG = 0x80u;
	NR50_REG = 0x77u;
	NR51_REG = 0xffu;

	//NR41_REG = 0x00u;
	//NR42_REG = 0x29u;
	//NR43_REG = 0x68u;
	//NR44_REG = 0x80u;

	//delay(6);

	//NR50_REG = 0x77u;

	//delay(7);

	//NR41_REG = 0x3cu;
	//NR42_REG = 0xc0u;
	//NR43_REG = 0x50u;
	//NR44_REG = 0xc0u;

//	delay(9);
//
//	NR50_REG = 0x77u;
//
//	delay(7);
//
	NR41_REG = 0x00u;
	NR42_REG = 0xc0u;
	NR43_REG = 0x18u;
	NR44_REG = 0x80u;

	NR50_REG = 0x77u;
	return 0; 
}

/*
APU write: ff24 -> 77 | delay: 11
APU write: ff11 -> 80 | delay: 8
APU write: ff12 -> 27 | delay: 0
APU write: ff13 -> 11 | delay: 0
APU write: ff14 -> 85 | delay: 0
APU write: ff24 -> 77 | delay: 7
APU write: ff24 -> 77 | delay: 11
APU write: ff24 -> 77 | delay: 12

APU write: ff20 -> 0 | delay: 9
APU write: ff21 -> 29 | delay: 0
APU write: ff22 -> 68 | delay: 0
APU write: ff23 -> 80 | delay: 0
NoiseChan dump:
ff
ff
29
68
ff
length: 0
APU write: ff16 -> 80 | delay: 0
APU write: ff17 -> 27 | delay: 0
APU write: ff18 -> 4e | delay: 0
APU write: ff19 -> 84 | delay: 0

APU write: ff24 -> 77 | delay: 6

APU write: ff20 -> 3c | delay: 7
APU write: ff21 -> c0 | delay: 0
APU write: ff22 -> 50 | delay: 0
APU write: ff23 -> c0 | delay: 0
NoiseChan dump:
ff
ff
c0
50
bf
length: 3c

APU write: ff24 -> 77 | delay: 9
APU write: ff20 -> 3c | delay: 7
APU write: ff21 -> c1 | delay: 0
APU write: ff22 -> 18 | delay: 0
APU write: ff23 -> c0 | delay: 0
NoiseChan dump:
ff
ff
c1
18
ff
length: 3c
APU write: ff24 -> 77 | delay: 8
APU write: ff24 -> 77 | delay: 11
APU write: ff24 -> 77 | delay: 11
APU write: ff24 -> 77 | delay: e
APU write: ff24 -> 77 | delay: 12
APU write: ff24 -> 77 | delay: f
APU write: ff24 -> 77 | delay: 12
APU write: ff11 -> 80 | delay: 8
APU write: ff12 -> 27 | delay: 0
APU write: ff13 -> 4e | delay: 0
APU write: ff14 -> 84 | delay: 0
APU write: ff24 -> 77 | delay: 6
APU write: ff24 -> 77 | delay: 12
APU write: ff24 -> 77 | delay: 11
APU write: ff16 -> 80 | delay: 9
APU write: ff17 -> 27 | delay: 0
APU write: ff18 -> 3b | delay: 0
APU write: ff19 -> 85 | delay: 0
*/
