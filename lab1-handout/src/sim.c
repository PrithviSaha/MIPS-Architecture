#include <stdio.h>
#include "shell.h"


// R - TYPE
// OP-Code
#define SPLOP 0x00
//FUNCT
#define SLL 0x00
#define SRL 0x02
#define SRA 0x03
#define SLLV 0x04
#define SRLV 0x06
#define SRAV 0x07
#define JR 0x08
#define JALR 0x09
#define ADD 0x20
#define ADDU 0x21
#define SUB 0x22
#define SUBU 0x23
#define AND 0x024
#define OR 0x25
#define XOR 0x26
#define NOR 0x27
#define SLT 0x2A
#define SLTU 0x2B
#define MULT 0x18
#define MFHI 0x10
#define MFLO 0x12
#define MTHI 0x11
#define MTLO 0x13
#define MULTU 0x19
#define DIV 0x1A
#define DIVU 0x1B
#define SYSCALL 0x0C

// I - TYPE
#define BEQ 0x04
#define BNE 0x05
#define BLEZ 0x06
#define BGTZ 0x07
#define ADDI 0x08
#define ADDIU 0x09
#define SLTI 0x0A
#define SLTIU 0x0B
#define ANDI 0x0C
#define ORI 0x0D
#define XORI 0x0E
#define LUI 0x0F
#define LB 0x20
#define LH 0x21
#define LW 0x23
#define LBU 0x24
#define LHU 0x25
#define SB 0x28
#define SH 0x29
#define SW 0x2B
//OP-Code
#define REGIMM 0x01
//RT
#define BLTZ 0x00
#define BGEZ 0x01
#define BLTZAL 0x10
#define BGEZAL 0x11

//J - TYPE
#define J 0x02
#define JAL 0x03


void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
    uint32_t inst = mem_read_32(CURRENT_STATE.PC);
    uint32_t opcode = (inst >> 26) & 0x3F;
    uint32_t funct = inst & 0x0000003F;
    uint32_t rs = (inst >> 21) & 0x1F;
    uint32_t rt = (inst >> 16) & 0x1F;
    uint32_t rd = (inst >> 11) & 0x1F;
    uint32_t shamt = (inst >> 6) & 0x1F;
    uint16_t immediate = inst & 0x0000FFFF;
    int32_t sign_extend = (int16_t)immediate;
    uint32_t target = inst & 0x03FFFFFF;

    NEXT_STATE = CURRENT_STATE;
    //NEXT_STATE.PC += 4;

    switch(opcode) {
	//R-type
	case SPLOP:
	    switch(funct) {
		case SLL:
                    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shamt;
                    break;
                case SRL:
                    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt;
                    break;
                case SRA:
                    NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rt] >> shamt;
                    break;
		case SLLV:
		    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << (CURRENT_STATE.REGS[rs] & 0x1F);
		    break;
		case SRLV:
                    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> (CURRENT_STATE.REGS[rs] & 0x1F);
                    break;
		case SRAV:
                    NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rt] >> (CURRENT_STATE.REGS[rs] & 0x1F);
                    break;
                case ADD:
                    NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rs] + (int32_t)CURRENT_STATE.REGS[rt];
                    break;
                case ADDU:
                    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
                    break;
                case SUB:
                    NEXT_STATE.REGS[rd] = (int32_t)CURRENT_STATE.REGS[rs] - (int32_t)CURRENT_STATE.REGS[rt];
                    break;
                case SUBU:
                    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
                    break;
                case AND:
                    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
                    break;
                case OR:
                    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];
                    break;
                case XOR:
                    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] ^ CURRENT_STATE.REGS[rt];
                    break;
                case NOR:
                    NEXT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);
                    break;
                case SLT:
                    NEXT_STATE.REGS[rd] = ((int32_t)CURRENT_STATE.REGS[rs] < (int32_t)CURRENT_STATE.REGS[rt]) ? 1 : 0;
                    break;
                case SLTU:
                    NEXT_STATE.REGS[rd] = (CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt]) ? 1 : 0;
                    break;
                case JR:
                    NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
                    break;
                case JALR:
                    NEXT_STATE.REGS[rd] = CURRENT_STATE.PC + 4;
                    NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
                    break;
                case MULT: {
                    int64_t prod = (int64_t)(int32_t)CURRENT_STATE.REGS[rs] * (int64_t)(int32_t)CURRENT_STATE.REGS[rt];

		    //int64_t prod = (int64_t)(CURRENT_STATE.REGS[rs] * CURRENT_STATE.REGS[rt]);
                    NEXT_STATE.HI = (uint32_t)((prod >> 32) & 0xFFFFFFFF);
                    NEXT_STATE.LO = (uint32_t)(prod & 0xFFFFFFFF);
		    printf("prod = %lld (0x%llx)\n", prod, prod);
                    break;
                }
                case MULTU: {
                    uint64_t prod = (uint64_t)CURRENT_STATE.REGS[rs] * (uint64_t)CURRENT_STATE.REGS[rt];
                    NEXT_STATE.HI = (uint32_t)((prod >> 32) & 0xFFFFFFFF);
                    NEXT_STATE.LO = (uint32_t)(prod & 0xFFFFFFFF);
		    printf("prod = %lld (0x%llx)\n", prod, prod);
                    break;
                }
                case DIV:
		    if(CURRENT_STATE.REGS[rt] != 0) {
			NEXT_STATE.LO = (int32_t)CURRENT_STATE.REGS[rs] / (int32_t)CURRENT_STATE.REGS[rt];
			NEXT_STATE.HI = (int32_t)CURRENT_STATE.REGS[rs] % (int32_t)CURRENT_STATE.REGS[rt];
		    }
		    break;
		case DIVU:
		    if(CURRENT_STATE.REGS[rt] != 0) {
                        NEXT_STATE.LO = CURRENT_STATE.REGS[rs] / CURRENT_STATE.REGS[rt];
                        NEXT_STATE.HI = CURRENT_STATE.REGS[rs] % CURRENT_STATE.REGS[rt];
                    }
		    break;
		case MFLO:
		    NEXT_STATE.REGS[rd] = CURRENT_STATE.LO;
		    break;
		case MFHI:
		    NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;
                    break;
		case MTLO:
		    NEXT_STATE.LO = CURRENT_STATE.REGS[rs];
                    break;
		case MTHI:
		    NEXT_STATE.HI = CURRENT_STATE.REGS[rs];
                    break;
		case SYSCALL:
		    if(CURRENT_STATE.REGS[2] == 0x0A) {
			RUN_BIT = 0;
		    }
                    break;
		default:
		    printf("Error in R Type instruction\n");   
	    	    break;
	    }
	    break;
	//I - TYPE
	case ADDI:
	    NEXT_STATE.REGS[rt] = (int32_t)CURRENT_STATE.REGS[rs] + sign_extend;
	    break;
	case ADDIU:
	    NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + sign_extend;
	    break;
	case SLTI:
	    NEXT_STATE.REGS[rt] = ((int32_t)CURRENT_STATE.REGS[rs] < sign_extend) ? 1 : 0;
	    break;
	case SLTIU:
	    NEXT_STATE.REGS[rt] = (CURRENT_STATE.REGS[rs] < (uint32_t)sign_extend) ? 1 : 0;
            break;
	case ANDI:
	    NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] & (uint32_t)immediate;		//zero extended immediate
	    break;
	case ORI:
	    NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | (uint32_t)immediate;		//zero extended immediate
            break;
	case XORI:
	    NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | (uint32_t)immediate;         //zero extended immediate
            break;
	case LUI:
	    NEXT_STATE.REGS[rt] = immediate << 16;
	    break;
	case LB: {
    	    int32_t addr = CURRENT_STATE.REGS[rs] + sign_extend;
    	    int32_t word = mem_read_32(addr & 0xFFFFFFFC);
    	    int8_t byte_offset = addr & 0x3;
    	    NEXT_STATE.REGS[rt] = (int8_t)(word >> (8 * byte_offset));
    	    break;
	}
	case LBU: {
            int32_t addr = CURRENT_STATE.REGS[rs] + sign_extend;
            uint32_t word = mem_read_32(addr & 0xFFFFFFFC);
            uint8_t byte_offset = addr & 0x3;
            NEXT_STATE.REGS[rt] = (uint8_t)(word >> (8 * byte_offset));
            break;
        }
	case LH: {
    	    int32_t addr = CURRENT_STATE.REGS[rs] + sign_extend;
    	    int32_t word = mem_read_32(addr & 0xFFFFFFFC);
    	    int8_t halfword_offset = (addr & 0x2) >> 1;
    	    int16_t halfword = (word >> (16 * halfword_offset)) & 0xFFFF;
    	    NEXT_STATE.REGS[rt] = (int16_t)halfword;
    	    break;
	}
	case LHU: {
            int32_t addr = CURRENT_STATE.REGS[rs] + sign_extend;
            uint32_t word = mem_read_32(addr & 0xFFFFFFFC);
            uint8_t halfword_offset = (addr & 0x2) >> 1;
            uint16_t halfword = (word >> (16 * halfword_offset)) & 0xFFFF;
            NEXT_STATE.REGS[rt] = (uint16_t)halfword;
            break;
        }
	case LW:
             NEXT_STATE.REGS[rt] = mem_read_32(CURRENT_STATE.REGS[rs] + sign_extend);
             break;
	case SW: {
	     int32_t addr = CURRENT_STATE.REGS[rs] + sign_extend;
	     mem_write_32(addr, CURRENT_STATE.REGS[rt]);
	     break;
	}
	case SH: {
            int32_t addr = CURRENT_STATE.REGS[rs] + sign_extend;
            int32_t word = mem_read_32(addr & 0xFFFFFFC);
	    int8_t half_offset = (addr & 0x2) >> 1;
	    word &= ~(0xFFFF << (8 * half_offset));
	    word |= (CURRENT_STATE.REGS[rt] & 0xFFFF) << (16 * half_offset);
            mem_write_32(addr & 0xFFFFFFFC, word);
            break;
        }
	case SB: {
            int32_t addr = CURRENT_STATE.REGS[rs] + sign_extend;
            int32_t word = mem_read_32(addr & 0xFFFFFFC);
            int8_t half_offset = (addr & 0x3);
            word &= ~(0xFF << (8 * half_offset));
            word |= (CURRENT_STATE.REGS[rt] & 0xFF) << (8 * half_offset);
            mem_write_32(addr & 0xFFFFFFFC, word);
            break;
     	}
	case BNE:
	    if(CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) {
                NEXT_STATE.PC = CURRENT_STATE.PC + (sign_extend << 2);
            }
            break;
	case BLEZ:
	    if(CURRENT_STATE.REGS[rs] <= 0) {
		NEXT_STATE.PC = CURRENT_STATE.PC + (sign_extend << 2);
	    }
	    break;
	case BEQ:
	    if(CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]) {
		NEXT_STATE.PC = CURRENT_STATE.PC + (sign_extend << 2);
	    }
	    break;
	case BGTZ:
	    if(CURRENT_STATE.REGS[rs] > 0) {
		 NEXT_STATE.PC = CURRENT_STATE.PC + (sign_extend << 2);
	    }
	    break;
	
	case REGIMM:
	    switch(rt) {
		case BLTZ:
		    if(CURRENT_STATE.REGS[rs] < 0) {
			NEXT_STATE.PC = CURRENT_STATE.PC + (sign_extend << 2);
		    }
		    break;
		case BGEZ:
		    if(CURRENT_STATE.REGS[rs] >= 0) {
			NEXT_STATE.PC = CURRENT_STATE.PC + (sign_extend << 2);
		    }
		    break;
		case BGEZAL:
		    NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
		    if(CURRENT_STATE.REGS[rs] >= 0) {
			NEXT_STATE.PC = CURRENT_STATE.PC + (sign_extend << 2);
		    }
		    break;
		case BLTZAL:
                    NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
                    if(CURRENT_STATE.REGS[rs] < 0) {
                        NEXT_STATE.PC = CURRENT_STATE.PC + (sign_extend << 2);
                    }
                    break;
	    }
	    break;
	//J - TYPE
	case J:
	    NEXT_STATE.PC = (CURRENT_STATE.PC & 0xF0000000) | (target << 2);
	    break;
	case JAL:
	    NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
	    NEXT_STATE.PC = (CURRENT_STATE.PC & 0xF0000000) | (target << 2);
	    break;
	default:
	    printf("Error in OPCODE\n");
	    break;
    }
    
    if (NEXT_STATE.PC == CURRENT_STATE.PC) {
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    }
}
