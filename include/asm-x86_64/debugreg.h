macro_line|#ifndef _X86_64_DEBUGREG_H
DECL|macro|_X86_64_DEBUGREG_H
mdefine_line|#define _X86_64_DEBUGREG_H
multiline_comment|/* Indicate the register numbers for a number of the specific&n;   debug registers.  Registers 0-3 contain the addresses we wish to trap on */
DECL|macro|DR_FIRSTADDR
mdefine_line|#define DR_FIRSTADDR 0        /* u_debugreg[DR_FIRSTADDR] */
DECL|macro|DR_LASTADDR
mdefine_line|#define DR_LASTADDR 3         /* u_debugreg[DR_LASTADDR]  */
DECL|macro|DR_STATUS
mdefine_line|#define DR_STATUS 6           /* u_debugreg[DR_STATUS]     */
DECL|macro|DR_CONTROL
mdefine_line|#define DR_CONTROL 7          /* u_debugreg[DR_CONTROL] */
multiline_comment|/* Define a few things for the status register.  We can use this to determine&n;   which debugging register was responsible for the trap.  The other bits&n;   are either reserved or not of interest to us. */
DECL|macro|DR_TRAP0
mdefine_line|#define DR_TRAP0&t;(0x1)&t;&t;/* db0 */
DECL|macro|DR_TRAP1
mdefine_line|#define DR_TRAP1&t;(0x2)&t;&t;/* db1 */
DECL|macro|DR_TRAP2
mdefine_line|#define DR_TRAP2&t;(0x4)&t;&t;/* db2 */
DECL|macro|DR_TRAP3
mdefine_line|#define DR_TRAP3&t;(0x8)&t;&t;/* db3 */
DECL|macro|DR_STEP
mdefine_line|#define DR_STEP&t;&t;(0x4000)&t;/* single-step */
DECL|macro|DR_SWITCH
mdefine_line|#define DR_SWITCH&t;(0x8000)&t;/* task switch */
multiline_comment|/* Now define a bunch of things for manipulating the control register.&n;   The top two bytes of the control register consist of 4 fields of 4&n;   bits - each field corresponds to one of the four debug registers,&n;   and indicates what types of access we trap on, and how large the data&n;   field is that we are looking at */
DECL|macro|DR_CONTROL_SHIFT
mdefine_line|#define DR_CONTROL_SHIFT 16 /* Skip this many bits in ctl register */
DECL|macro|DR_CONTROL_SIZE
mdefine_line|#define DR_CONTROL_SIZE 4   /* 4 control bits per register */
DECL|macro|DR_RW_EXECUTE
mdefine_line|#define DR_RW_EXECUTE (0x0)   /* Settings for the access types to trap on */
DECL|macro|DR_RW_WRITE
mdefine_line|#define DR_RW_WRITE (0x1)
DECL|macro|DR_RW_READ
mdefine_line|#define DR_RW_READ (0x3)
DECL|macro|DR_LEN_1
mdefine_line|#define DR_LEN_1 (0x0) /* Settings for data length to trap on */
DECL|macro|DR_LEN_2
mdefine_line|#define DR_LEN_2 (0x4)
DECL|macro|DR_LEN_4
mdefine_line|#define DR_LEN_4 (0xC)
DECL|macro|DR_LEN_8
mdefine_line|#define DR_LEN_8 (0x8)
multiline_comment|/* The low byte to the control register determine which registers are&n;   enabled.  There are 4 fields of two bits.  One bit is &quot;local&quot;, meaning&n;   that the processor will reset the bit after a task switch and the other&n;   is global meaning that we have to explicitly reset the bit.  With linux,&n;   you can use either one, since we explicitly zero the register when we enter&n;   kernel mode. */
DECL|macro|DR_LOCAL_ENABLE_SHIFT
mdefine_line|#define DR_LOCAL_ENABLE_SHIFT 0    /* Extra shift to the local enable bit */
DECL|macro|DR_GLOBAL_ENABLE_SHIFT
mdefine_line|#define DR_GLOBAL_ENABLE_SHIFT 1   /* Extra shift to the global enable bit */
DECL|macro|DR_ENABLE_SIZE
mdefine_line|#define DR_ENABLE_SIZE 2           /* 2 enable bits per register */
DECL|macro|DR_LOCAL_ENABLE_MASK
mdefine_line|#define DR_LOCAL_ENABLE_MASK (0x55)  /* Set  local bits for all 4 regs */
DECL|macro|DR_GLOBAL_ENABLE_MASK
mdefine_line|#define DR_GLOBAL_ENABLE_MASK (0xAA) /* Set global bits for all 4 regs */
multiline_comment|/* The second byte to the control register has a few special things.&n;   We can slow the instruction pipeline for instructions coming via the&n;   gdt or the ldt if we want to.  I am not sure why this is an advantage */
DECL|macro|DR_CONTROL_RESERVED
mdefine_line|#define DR_CONTROL_RESERVED (0xFC00) /* Reserved by Intel */
DECL|macro|DR_LOCAL_SLOWDOWN
mdefine_line|#define DR_LOCAL_SLOWDOWN (0x100)   /* Local slow the pipeline */
DECL|macro|DR_GLOBAL_SLOWDOWN
mdefine_line|#define DR_GLOBAL_SLOWDOWN (0x200)  /* Global slow the pipeline */
macro_line|#endif
eof
