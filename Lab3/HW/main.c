/*
    Although bitwise operators are good for saving space, space is hardly an issue. We
    will be using bits and bitwise operators in order to model the architecture of a simple processor,
    its instruction set, and its machine language. The datapath of the Tiny Processor is shown in
    Figure 1.1. In this design, the program data are stored in the Data Memory while the program
    that is being executed is stored in the Instruction Memory. The IR is a register that is used to
    hold the instruction that is being decoded and executed. The IP points to the next instruction to
    be executed. The PC or program counter is used to index the instructions in the program that is
    being executed. For now, research the literature and understand the architecture. Explain the
    design to your partner. Explore how the architecture can be modeled using C and what are the
    available options. Document all information in your report.
*/




// First we will be using a simple processor with a single register and a single memory location (Data memory).
// The register will be used to store the instruction that is being executed. The memory location
// will be used to store the program data.

/* ----------------------- IP Chip  -------------------------*/
/*
    The PC is incremented after fetching an instruction, and holds the memory address of ("points to")
    the next instruction that would be executed. Since program execution is sequential, the PC is
    incremented by one after fetching an instruction.
    This is usually done in the end of the Fetch stage, after an instruction has been fetched.

    While the IP points to the next instruction to be executed, after the first one was fetched.

    The PC is special in that it is both a register (IP) and a counter.


*/
/* -----------------------------------------------------------*/



/* ----------------------- IR Chip  -------------------------*/
/*
    When memory is read, the data first goes to the memory buffer register. If the data is an
    instruction it gets moved to the Instruction Register. 
    The IR has two parts:
        1. IR (opcode) The most significant bits of the instruction make up the opcode. (the 4 left most bits)
            This the genuine instruction part of the instruction, that tells the cpu what to do.
                LOAD_A  = 0001 ,  Read RAM location into register A
                LOAD_B  = 0001 ,  Read RAM location into register B
                ADD     = 1000 ,  Add register A and register B, store in the second register
                STORE_A = 0100 ,  Write register A to RAM location
            The instruction in IR (opcode) gets decoded and executed by the control unit (CU).

        2. IR (address) The least significant bits of the instruction are actually data.
            They get moved to IR (address). As the name suggests they usually form
            all or part of an address for later use in the Memory adress register. (However, in immediate
            addressing they are sent to the accumulator.)
*/
/* -----------------------------------------------------------*/



/* ----------------------- ALU Chip  -------------------------*/
/*
    The Arithmetic Logic Unit is responsible for bit operations on data held
    in the accumulator and memeory buffer register and for storing the results. It contains arithmetic adders,
    logical AND-ers and OR-ers, and so on.
        It takes INPUT_A (8 bits ) and INPUT_B (8 bits ) from the registers and performs the operation specified by the opcode (4 bits).
            The opcode is used in the multiplexer to select the operation to be performed on the input.
        It output:
            Actual output (8 bits) 
            Flags (1 bit): they are for the CPU to know if the operation was successful or not, and for other status.
                Zero flag: set if the result is zero.
                Carry flag: set if the result is greater than 255.
                Overflow flag: set if the result is greater than 255.
                Negative flag: set if the result is negative.
                Positive flag: set if the result is positive.
   
*/
/* -----------------------------------------------------------*/



/* ----------------------- Register File Chip  ---------------*/
/*
    The register file is the component that contains all the general purpose registers of the microprocessor.
    It contains 16 registers, each of which can hold 8 bits of data.
    The registers are numbered from 0 to 15.
    The registers are used to store the data that is being used in the ALU.

    It is formed of set of registers (16) and a MUTLIPLEXER that selects the register to be used.
    the reigster to be used is selected by the MUX.
    The MUX is formed of a 4-bit address and a 4-bit data input.
    The address is used to select the register to be used.
    The data input is used to write the data to the register.
    The data input is also used to read the data from the register.

    It also take a Enable input to enable the register.

    Inputs:
        Address 1: 4-bit address to select the register to be used.
        Address 2: 4-bit data to write to the register.
        Destination: 4-bit third address port for the write address.
        Read/Write: 1-bit to select if the register is to be read or written.
        Data: 8-bit data to write to the register.
        Enable: 1-bit enable to enable the register.
    Outputs:
        Data 1: 32 - bit data from the register.
        Data 2: 32 --bit data from the register.


*/
/* -----------------------------------------------------------*/


/* ----------------------- Data Memory Chip  -----------------*/
/*
    It is a sequential series of 8 bits(byte) of data,
    each register output needs to be stored in 4 memory location


    naming of each adress is in hex, each location is incremented by 4,
    because each 4 slots, store a single data from the register.
*/
/* -----------------------------------------------------------*/


/* ----------------------- Mux Chips  -------------------------*/
/*
    A multiplexer is a component that selects one of two inputs based on a control signal.
    The control signal is usually a single bit, but can be more than one bit.
    The multiplexer is used to select the register to be used.
*/
/* -----------------------------------------------------------*/