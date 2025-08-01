# MIPS Architecture Instruction Flow Simulation

This project demonstrates the implementation and simulation of various **MIPS assembly control flow instructions** including unconditional jumps, conditional branches, and subroutine calls/returns. The project was executed using a custom-built MIPS instruction simulator written in C.

---

## 🛠️ Features

- Implementation and testing of jump and branch instructions:
  - `j`, `jal`, `jr`, `jalr`, `beq`, `bne`, `blez`, `bgtz`, `bltz`, `bgez`, `bltzal`, `bgezal`
- Correct handling of return addresses using `$ra` in subroutine instructions.
- Validation of register values, program counter (PC), and memory states after each control transfer.
- Designed for educational use to understand **R-type**, **I-type**, and **J-type** instruction formats and branching logic.

---


## 🔧 Converting Assembly File to Hex File

1. Navigate to the `inputs/` directory:
   
   ```bash
   $ cd inputs/

2. Use asm2hex to convert a test input (.s file) into a hexdump (.x file):
      
   ```bash
   $ ./asm2hex addiu.s
   
You should now have a hexdump of the assembled machine code "addiu.x". Repeat
this step for the rest of the test inputs.


4. Run the hexdump in the simulator.

## 🧪 How to Run

3. Run the hexdump in the simulator:

   ```bash
    $ src/sim inputs/addiu.x

5. Simulator commands:

   ```bash
    >> MIPS Simulator
    >> 
    >> Read 7 words from program into memory.
    >> 
    >> MIPS-SIM> go
    >> 
    >> Simulating...
    >>
    >> MIPS-SIM> rdump

- use `rdump` to view the registers

- Press `Ctrl+C` to exit the simulator.

---

Feel free to fork or contribute to this repository to add more MIPS instructions or enhance simulator functionality.
