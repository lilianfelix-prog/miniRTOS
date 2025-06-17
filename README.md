# miniRTOS

### notes
In the process of making this I ended up diving a bit deeper into a few topics mainly about the RISCV architecture,
so here are my notes:

- The main RISCV instruction pipeline is similar to other architecture:
1. Operand fetch
2. Decode and register
3. Pre-normalization
4. Arithmetic operation
5. Post-normalization
6. Write-back

- Instruction fetch:
Start by reading instruction from memory (generaly stored the .text area), this takes 1 clock cycle.
More specificly the PC read to memory at beginning of cycle, during that cycle PC increment of 4 bytes for next instruction (all instruction are the same length).
If there is a branch or jump the addr is computed during read register file, condition are computed next cycle, possible branch/jump prediction algo (possible branch delay).
- Decode and register/pre-normalization:
Specific to RISCV, there is no microcode (controls signals created direcly from instruction bits between hardware and ISA). So more space for register indexes. 
The registers indexes in the instructions are identified then presented to register memory as addresses, registers are read from memory.
During this read instruction logic determine if the pipeline is ready to execute, if not fetch and decode stall (flip flops do not accept new bits input [^1].
If there was a jump it would be directly assigned to target here, or resolving a branch.
- Execute:
In this stage there is multiple type of operation involving mainly the ALU:
1. register to register operations (single cycle latency), add, sub, compare, logical operation.
2. memory references operations (2 cycles), loads from memory, AC <- M[address], M[address] <- AC.
3. multi-cycle operations, mult, div, floating-point operations (the rest of the pipeline can continue while operation), the result is writton to seperate registers.
- Memory access:
In this stage the single cycle operations are forwarded to wait for 2 cycles operations to have their result written at same stage. To do this it virtually tags the data and cach it in 2 srams.
- Writeback:
Write 1 and 2 cylces instructions result while decode stage is reading for future instructions in file registers. ! This can cause some problems since it can write and read from same register [^2].

#### Vector instruction pipeline:
Riscv vector registers can be seen as a implementation of a SIMD architecture (Single instruction multiple data).
- A 32 bits vector register can store 1 4-bytes element, 2 2-bytes elements, 4 1-byte elements.
- There are 5 types of vector specific instruction: Vector load, store, atomic operation, arithmetic (scalar-vector, vector-vector, vector-matrix MMV ), configurations instructions.
- A key feature of these vector registers is their length and format change dynamically base on configurations instructions. This allows higher throughput on operations with vectors of differents lengths, running in a single loop.
- 
