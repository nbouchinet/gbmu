#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

#include "src/Fwd.hpp"
#include "cpu/Core.hpp"
#include <vector>
#include <map>

class Debugger {
	private:

		/*
		 * 
		 *  - Debugger on a besoin de quoi getter pour avoir les valeurs des registres: [pc(); sp(); ...]
		 *  - Lire la rom (Cartridge.hpp) donc faire un getter de std::vector<Byte> rom naviguer dans la rom avec un user input;
		 *  - Afficher la memoire de la rom pointer par le program counter 
		 *  - Execute only one instruction
		 *  - Execute during one second thanks to the timer
		 *  - Execute during one frame
		 *  - Reset all, reload the cartridge
		 */

		bool	 _enabled = 1;
		bool	 _wait_next = 1;
		int	_frame_size = 10;

		struct _debug_info {
			uint16_t pc;
			uint16_t opcode;
			const char * instr;
			uint8_t size;
		};

		struct _instr_info {
			const char * instr;
			uint8_t size;
		};

		std::vector<_debug_info> _instr_pool;

		std::map<int, _instr_info> _instr_map = {
			{0x06, {"ld B,n", 2}}, {0x0E, {"ld C,n", 2}}, {0x16, {"ld D,n", 2}}, {0x1E, {"ld E,n", 2}}, 
			{0x26, {"ld H,n", 2}}, {0x2E, {"ld L,n", 2}}, {0x7F, {"ld A,A", 1}}, {0x78, {"ld A,B", 1}}, 
			{0x79, {"ld A,C", 1}}, {0x7A, {"ld A,D", 1}}, {0x7B, {"ld A,E", 1}}, {0x7C, {"ld A,H", 1}}, 
			{0x7D, {"ld A,L", 1}}, {0x7E, {"ld A,(HL)", 1}}, {0x40, {"ld B,B", 1}}, {0x41, {"ld B,C", 1}}, 
			{0x42, {"ld B,D", 1}}, {0x43, {"ld B,E", 1}}, {0x44, {"ld B,H", 1}}, {0x45, {"ld B,L", 1}}, 
			{0x46, {"ld B,(HL)", 1}}, {0x48, {"ld C,B", 1}}, {0x49, {"ld C,C", 1}}, {0x4A, {"ld C,D", 1}}, 
			{0x4B, {"ld C,E", 1}}, {0x4C, {"ld C,H", 1}}, {0x4D, {"ld C,L", 1}}, {0x4E, {"ld C,(HL)", 1}}, 
			{0x50, {"ld D,B", 1}}, {0x51, {"ld D,C", 1}}, {0x52, {"ld D,D", 1}}, {0x53, {"ld D,E", 1}}, 
			{0x54, {"ld D,H", 1}}, {0x55, {"ld D,L", 1}}, {0x56, {"ld D,(HL)", 1}}, {0x58, {"ld E,B", 1}}, 
			{0x59, {"ld E,C", 1}}, {0x5A, {"ld E,D", 1}}, {0x5B, {"ld E,E", 1}}, {0x5C, {"ld E,H", 1}}, 
			{0x5D, {"ld E,L", 1}}, {0x5E, {"ld E,(HL)", 1}}, {0x60, {"ld H,B", 1}}, {0x61, {"ld H,C", 1}}, 
			{0x62, {"ld H,D", 1}}, {0x63, {"ld H,E", 1}}, {0x64, {"ld H,H", 1}}, {0x65, {"ld H,L", 1}}, 
			{0x66, {"ld H,(HL)", 1}}, {0x68, {"ld L,B", 1}}, {0x69, {"ld L,C", 1}}, {0x6A, {"ld L,D", 1}}, 
			{0x6B, {"ld L,E", 1}}, {0x6C, {"ld L,H", 1}}, {0x6D, {"ld L,L", 1}}, {0x6E, {"ld L,(HL)", 1}}, 
			{0x70, {"ld (HL),B", 1}}, {0x71, {"ld (HL),C", 1}}, {0x72, {"ld (HL),D", 1}}, {0x73, {"ld (HL),E", 1}}, 
			{0x74, {"ld (HL),H", 1}}, {0x75, {"ld (HL),L", 1}}, {0x36, {"ld (HL),n", 2}}, {0x0A, {"ld A,(BC)", 1}}, 
			{0x1A, {"ld A,(DE)", 1}}, {0xFA, {"ld A,(nn)", 3}}, {0x3E, {"ld A,n", 2}}, {0x47, {"ld B,A", 1}}, 
			{0x4F, {"ld C,A", 1}}, {0x57, {"ld D,A", 1}}, {0x5F, {"ld E,A", 1}}, {0x67, {"ld H,A", 1}}, 
			{0x6F, {"ld L,A", 1}}, {0x02, {"ld (BC),A", 1}}, {0x12, {"ld (DE),A", 1}}, {0x77, {"ld (HL),A", 1}}, 
			{0xEA, {"ld (nn),A", 3}}, {0xF2, {"ld A,(C)", 1}}, {0xE2, {"ld ($FF00+C),A", 1}}, {0x3A, {"ldd A,(HL)", 1}}, 
			{0x32, {"ldd (HL),A", 1}}, {0x2A, {"ldi A,HL", 1}}, {0xE0, {"ld ($FF00+n),A", 2}}, {0xF0, {"ld A,($FF00+n)", 2}}, 
			{0x01, {"ld BC,nn", 3}}, {0x11, {"ld DE,nn", 3}}, {0x21, {"ld HL,nn", 3}}, {0x31, {"ld SP,nn", 3}}, 
			{0xF9, {"ld SP,HL", 1}}, {0xF8, {"ldhl n", 2}}, {0x08, {"ld (nn),SP", 3}}, {0xF5, {"push AF", 1}}, 
			{0xC5, {"push BC", 1}}, {0xD5, {"push DE", 1}}, {0xE5, {"push HL", 1}}, {0xF1, {"pop AF", 1}}, 
			{0xC1, {"pop BC", 1}}, {0xD1, {"pop DE", 1}}, {0xE1, {"pop HL", 1}}, {0x87, {"add A,A", 1}}, 
			{0x80, {"add A,B", 1}}, {0x81, {"add A,C", 1}}, {0x82, {"add A,D", 1}}, {0x83, {"add A,E", 1}}, 
			{0x84, {"add A,H", 1}}, {0x85, {"add A,L", 1}}, {0x86, {"add A,(HL)", 1}}, {0xC6, {"add A,n", 2}}, 
			{0x8F, {"adc A,A", 1}}, {0x88, {"adc A,B", 1}}, {0x89, {"adc A,C", 1}}, {0x8A, {"adc A,D", 1}}, 
			{0x8B, {"adc A,E", 1}}, {0x8C, {"adc A,H", 1}}, {0x8D, {"adc A,L", 1}}, {0x8E, {"adc A,(HL)", 1}}, 
			{0xCE, {"adc A,n", 2}}, {0x97, {"sub A,A", 1}}, {0x90, {"sub A,B", 1}}, {0x91, {"sub A,C", 1}}, 
			{0x92, {"sub A,D", 1}}, {0x93, {"sub A,E", 1}}, {0x94, {"sub A,H", 1}}, {0x95, {"sub A,L", 1}}, 
			{0x96, {"sub A,(HL)", 1}}, {0xD6, {"sub A,n", 2}}, {0x9F, {"sbc A,A", 1}}, {0x98, {"sbc A,B", 1}}, 
			{0x99, {"sbc A,C", 1}}, {0x9A, {"sbc A,D", 1}}, {0x9B, {"sbc A,E", 1}}, {0x9C, {"sbc A,H", 1}}, 
			{0x9D, {"sbc A,L", 1}}, {0x9E, {"sbc A,(HL)", 1}}, {0xA7, {"and A,A", 1}}, {0xA0, {"and A,B", 1}}, 
			{0xA1, {"and A,C", 1}}, {0xA2, {"and A,D", 1}}, {0xA3, {"and A,E", 1}}, {0xA4, {"and A,H", 1}}, 
			{0xA5, {"and A,L", 1}}, {0xA6, {"and A,(HL)", 1}}, {0xE6, {"and A,n", 2}}, {0xB7, {"or A,A", 1}}, 
			{0xB0, {"or A,B", 1}}, {0xB1, {"or A,C", 1}}, {0xB2, {"or A,D", 1}}, {0xB3, {"or A,E", 1}}, 
			{0xB4, {"or A,H", 1}}, {0xB5, {"or A,L", 1}}, {0xB6, {"or A,(HL)", 1}}, {0xF6, {"or A,n", 2}}, 
			{0xAF, {"xor A,A", 1}}, {0xA8, {"xor A,B", 1}}, {0xA9, {"xor A,C", 1}}, {0xAA, {"xor A,D", 1}}, 
			{0xAB, {"xor A,E", 1}}, {0xAC, {"xor A,H", 1}}, {0xAD, {"xor A,L", 1}}, {0xAE, {"xor A,(HL)", 1}}, 
			{0xEE, {"xor A,n", 2}}, {0xBF, {"cp A,A", 1}}, {0xB8, {"cp A,B", 1}}, {0xB9, {"cp A,C", 1}}, 
			{0xBA, {"cp A,D", 1}}, {0xBB, {"cp A,E", 1}}, {0xBC, {"cp A,H", 1}}, {0xBD, {"cp A,L", 1}}, 
			{0xBE, {"cp A,(HL)", 1}}, {0xFE, {"cp A,n", 2}}, {0x3C, {"inc A", 1}}, {0x04, {"inc B", 1}}, 
			{0x0C, {"inc C", 1}}, {0x14, {"inc D", 1}}, {0x1C, {"inc E", 1}}, {0x24, {"inc H", 1}}, 
			{0x2C, {"inc L", 1}}, {0x34, {"inc (HL)", 1}}, {0x3D, {"dec A", 1}}, {0x05, {"dec B", 1}}, 
			{0x0D, {"dec C", 1}}, {0x15, {"dec D", 1}}, {0x1D, {"dec E", 1}}, {0x25, {"dec H", 1}}, 
			{0x2D, {"dec L", 1}}, {0x35, {"dec (HL)", 1}}, {0x09, {"add HL,BC", 1}}, {0x19, {"add HL,DE", 1}}, 
			{0x29, {"add HL,HL", 1}}, {0x39, {"add HL,SP", 1}}, {0xE8, {"add SP,n", 2}}, {0x03, {"inc BC", 1}}, 
			{0x13, {"inc DE", 1}}, {0x23, {"inc HL", 1}}, {0x33, {"inc SP", 1}}, {0x0B, {"dec BC", 1}}, 
			{0x1B, {"dec DE", 1}}, {0x2B, {"dec HL", 1}}, {0x3B, {"dec SP", 1}}, {0x27, {"daa -/-", 1}}, 
			{0x2F, {"cpl -/-", 1}}, {0x3F, {"ccf -/-", 1}}, {0x37, {"scf -/-", 1}}, {0x00, {"nop -/-", 1}}, 
			{0x76, {"halt -/-", 1}}, {0x10, {"stop -/-", 1}}, {0xF3, {"di -/-", 1}}, {0xFB, {"ei -/-", 1}}, 
			{0x07, {"rlc A", 1}}, {0x17, {"rl A", 1}}, {0x0F, {"rrc A", 1}}, {0x1F, {"rr A", 1}}, 
			{0xC3, {"jp c:-,nn", 3}}, {0xC2, {"jp c:NZ,nn", 3}}, {0xCA, {"jp c:Z,nn", 3}}, {0xD2, {"jp c:NC,nn", 3}}, 
			{0xDA, {"jp c:C,nn", 3}}, {0xE9, {"jp c:-,(HL)", 1}}, {0x18, {"jr c:-,n", 2}}, {0x20, {"jr c:NZ,n", 2}}, 
			{0x28, {"jr c:Z,n", 2}}, {0x30, {"jr c:NC,n", 2}}, {0x38, {"jr c:C,n", 2}}, {0xCD, {"call c:-,nn", 3}}, 
			{0xC4, {"call c:NZ,nn", 3}}, {0xCC, {"call c:Z,nn", 3}}, {0xD4, {"call c:NC,nn", 3}}, {0xDC, {"call c:C,nn", 3}}, 
			{0xC7, {"rst 0x00", 1}}, {0xCF, {"rst 0x08", 1}}, {0xD7, {"rst 0x10", 1}}, {0xDF, {"rst 0x18", 1}}, 
			{0xE7, {"rst 0x20", 1}}, {0xEF, {"rst 0x28", 1}}, {0xF7, {"rst 0x30", 1}}, {0xFF, {"rst 0x38", 1}}, 
			{0xC9, {"ret c:-", 1}}, {0xC0, {"ret c:NZ", 1}}, {0xC8, {"ret c:Z", 1}}, {0xD0, {"ret c:NC", 1}}, 
			{0xD8, {"ret c:C", 1}}, {0xD9, {"reti -/-", 1}}, {0xCB07, {"rlc A", 1}}, {0xCB00, {"rlc B", 1}}, 
			{0xCB01, {"rlc C", 1}}, {0xCB02, {"rlc D", 1}}, {0xCB03, {"rlc E", 1}}, {0xCB04, {"rlc H", 1}}, 
			{0xCB05, {"rlc L", 1}}, {0xCB06, {"rlc (HL)", 1}}, {0xCB17, {"rl A", 1}}, {0xCB10, {"rl B", 1}}, 
			{0xCB11, {"rl C", 1}}, {0xCB12, {"rl D", 1}}, {0xCB13, {"rl E", 1}}, {0xCB14, {"rl H", 1}}, 
			{0xCB15, {"rl L", 1}}, {0xCB16, {"rl (HL)", 1}}, {0xCB0F, {"rrc A", 1}}, {0xCB08, {"rrc B", 1}}, 
			{0xCB09, {"rrc C", 1}}, {0xCB0A, {"rrc D", 1}}, {0xCB0B, {"rrc E", 1}}, {0xCB0C, {"rrc H", 1}}, 
			{0xCB0D, {"rrc L", 1}}, {0xCB0E, {"rrc (HL)", 1}}, {0xCB1F, {"rr A", 1}}, {0xCB18, {"rr B", 1}}, 
			{0xCB19, {"rr C", 1}}, {0xCB1A, {"rr D", 1}}, {0xCB1B, {"rr E", 1}}, {0xCB1C, {"rr H", 1}}, 
			{0xCB1D, {"rr L", 1}}, {0xCB1E, {"rr (HL)", 1}}, {0xCB27, {"sla A", 1}}, {0xCB20, {"sla B", 1}}, 
			{0xCB21, {"sla C", 1}}, {0xCB22, {"sla D", 1}}, {0xCB23, {"sla E", 1}}, {0xCB24, {"sla H", 1}}, 
			{0xCB25, {"sla L", 1}}, {0xCB26, {"sla (HL)", 1}}, {0xCB2F, {"sra A", 1}}, {0xCB28, {"sra B", 1}}, 
			{0xCB29, {"sra C", 1}}, {0xCB2A, {"sra D", 1}}, {0xCB2B, {"sra E", 1}}, {0xCB2C, {"sra H", 1}}, 
			{0xCB2D, {"sra L", 1}}, {0xCB2E, {"sra (HL)", 1}}, {0xCB37, {"swap A", 1}}, {0xCB30, {"swap B", 1}}, 
			{0xCB31, {"swap C", 1}}, {0xCB32, {"swap D", 1}}, {0xCB33, {"swap E", 1}}, {0xCB34, {"swap H", 1}}, 
			{0xCB35, {"swap L", 1}}, {0xCB36, {"swap (HL)", 1}}, {0xCB3F, {"srl A", 1}}, {0xCB38, {"srl B", 1}}, 
			{0xCB39, {"srl C", 1}}, {0xCB3A, {"srl D", 1}}, {0xCB3B, {"srl E", 1}}, {0xCB3C, {"srl H", 1}}, 
			{0xCB3D, {"srl L", 1}}, {0xCB3E, {"srl (HL)", 1}}, {0xCB47, {"bit b,A", 2}}, {0xCB40, {"bit b,B", 2}}, 
			{0xCB41, {"bit b,C", 2}}, {0xCB42, {"bit b,D", 2}}, {0xCB43, {"bit b,E", 2}}, {0xCB44, {"bit b,H", 2}}, 
			{0xCB45, {"bit b,L", 2}}, {0xCB46, {"bit b,(HL)", 2}}, {0xCBC7, {"set A,b", 2}}, {0xCBC0, {"set B,b", 2}}, 
			{0xCBC1, {"set C,b", 2}}, {0xCBC2, {"set D,b", 2}}, {0xCBC3, {"set E,b", 2}}, {0xCBC4, {"set H,b", 2}}, 
			{0xCBC5, {"set L,b", 2}}, {0xCBC6, {"set (HL),b", 2}}, {0xCB87, {"res A,b", 2}}, {0xCB80, {"res B,b", 2}}, 
			{0xCB81, {"res C,b", 2}}, {0xCB82, {"res D,b", 2}}, {0xCB83, {"res E,b", 2}}, {0xCB84, {"res H,b", 2}}, 
			{0xCB85, {"res L,b", 2}}, {0xCB86, {"res (HL),b", 2}}, };
	public:
		std::vector<Word> getRegisters(void);
		std::vector<Word> dumpRom(void);

		void get_instruction_set(const Core::Iterator &it, uint16_t pc);
		void wait_user_interaction();
		bool is_enabled() const { return _enabled; }
		void toggle() { _enabled = _enabled ? false : true; }
		_debug_info gen_debug_info(uint16_t pc, uint16_t opcode, _instr_info map_info);

};

#endif
