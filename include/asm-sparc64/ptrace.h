multiline_comment|/* $Id: ptrace.h,v 1.14 2002/02/09 19:49:32 davem Exp $ */
macro_line|#ifndef _SPARC64_PTRACE_H
DECL|macro|_SPARC64_PTRACE_H
mdefine_line|#define _SPARC64_PTRACE_H
macro_line|#include &lt;asm/pstate.h&gt;
multiline_comment|/* This struct defines the way the registers are stored on the &n; * stack during a system call and basically all traps.&n; */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|u_regs
r_int
r_int
id|u_regs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* globals and ins */
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
DECL|member|tpc
r_int
r_int
id|tpc
suffix:semicolon
DECL|member|tnpc
r_int
r_int
id|tnpc
suffix:semicolon
DECL|member|y
r_int
r_int
id|y
suffix:semicolon
DECL|member|fprs
r_int
r_int
id|fprs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pt_regs32
r_struct
id|pt_regs32
(brace
DECL|member|psr
r_int
r_int
id|psr
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|npc
r_int
r_int
id|npc
suffix:semicolon
DECL|member|y
r_int
r_int
id|y
suffix:semicolon
DECL|member|u_regs
r_int
r_int
id|u_regs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* globals and ins */
)brace
suffix:semicolon
DECL|macro|UREG_G0
mdefine_line|#define UREG_G0        0
DECL|macro|UREG_G1
mdefine_line|#define UREG_G1        1
DECL|macro|UREG_G2
mdefine_line|#define UREG_G2        2
DECL|macro|UREG_G3
mdefine_line|#define UREG_G3        3
DECL|macro|UREG_G4
mdefine_line|#define UREG_G4        4
DECL|macro|UREG_G5
mdefine_line|#define UREG_G5        5
DECL|macro|UREG_G6
mdefine_line|#define UREG_G6        6
DECL|macro|UREG_G7
mdefine_line|#define UREG_G7        7
DECL|macro|UREG_I0
mdefine_line|#define UREG_I0        8
DECL|macro|UREG_I1
mdefine_line|#define UREG_I1        9
DECL|macro|UREG_I2
mdefine_line|#define UREG_I2        10
DECL|macro|UREG_I3
mdefine_line|#define UREG_I3        11
DECL|macro|UREG_I4
mdefine_line|#define UREG_I4        12
DECL|macro|UREG_I5
mdefine_line|#define UREG_I5        13
DECL|macro|UREG_I6
mdefine_line|#define UREG_I6        14
DECL|macro|UREG_I7
mdefine_line|#define UREG_I7        15
DECL|macro|UREG_FP
mdefine_line|#define UREG_FP        UREG_I6
DECL|macro|UREG_RETPC
mdefine_line|#define UREG_RETPC     UREG_I7
multiline_comment|/* A V9 register window */
DECL|struct|reg_window
r_struct
id|reg_window
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A 32-bit register window. */
DECL|struct|reg_window32
r_struct
id|reg_window32
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A V9 Sparc stack frame */
DECL|struct|sparc_stackf
r_struct
id|sparc_stackf
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|fp
r_struct
id|sparc_stackf
op_star
id|fp
suffix:semicolon
DECL|member|callers_pc
r_int
r_int
id|callers_pc
suffix:semicolon
DECL|member|structptr
r_char
op_star
id|structptr
suffix:semicolon
DECL|member|xargs
r_int
r_int
id|xargs
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|xxargs
r_int
r_int
id|xxargs
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A 32-bit Sparc stack frame */
DECL|struct|sparc_stackf32
r_struct
id|sparc_stackf32
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|fp
r_int
r_int
id|fp
suffix:semicolon
DECL|member|callers_pc
r_int
r_int
id|callers_pc
suffix:semicolon
DECL|member|structptr
r_int
r_int
id|structptr
suffix:semicolon
DECL|member|xargs
r_int
r_int
id|xargs
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|xxargs
r_int
r_int
id|xxargs
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sparc_trapf
r_struct
id|sparc_trapf
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|_unused
r_int
r_int
id|_unused
suffix:semicolon
DECL|member|regs
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TRACEREG_SZ
mdefine_line|#define TRACEREG_SZ&t;sizeof(struct pt_regs)
DECL|macro|STACKFRAME_SZ
mdefine_line|#define STACKFRAME_SZ&t;sizeof(struct sparc_stackf)
DECL|macro|REGWIN_SZ
mdefine_line|#define REGWIN_SZ&t;sizeof(struct reg_window)
DECL|macro|TRACEREG32_SZ
mdefine_line|#define TRACEREG32_SZ&t;sizeof(struct pt_regs32)
DECL|macro|STACKFRAME32_SZ
mdefine_line|#define STACKFRAME32_SZ&t;sizeof(struct sparc_stackf32)
DECL|macro|REGWIN32_SZ
mdefine_line|#define REGWIN32_SZ&t;sizeof(struct reg_window32)
macro_line|#ifdef __KERNEL__
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (!((regs)-&gt;tstate &amp; TSTATE_PRIV))
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;tpc)
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else /* __ASSEMBLY__ */
multiline_comment|/* For assembly code. */
DECL|macro|TRACEREG_SZ
mdefine_line|#define TRACEREG_SZ&t;&t;0xa0
DECL|macro|STACKFRAME_SZ
mdefine_line|#define STACKFRAME_SZ&t;&t;0xc0
DECL|macro|REGWIN_SZ
mdefine_line|#define REGWIN_SZ&t;&t;0x80
DECL|macro|TRACEREG32_SZ
mdefine_line|#define TRACEREG32_SZ&t;&t;0x50
DECL|macro|STACKFRAME32_SZ
mdefine_line|#define STACKFRAME32_SZ&t;&t;0x60
DECL|macro|REGWIN32_SZ
mdefine_line|#define REGWIN32_SZ&t;&t;0x40
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|macro|STACK_BIAS
mdefine_line|#define STACK_BIAS&t;&t;2047
macro_line|#endif
multiline_comment|/* These are for pt_regs. */
DECL|macro|PT_V9_G0
mdefine_line|#define PT_V9_G0     0x00
DECL|macro|PT_V9_G1
mdefine_line|#define PT_V9_G1     0x08
DECL|macro|PT_V9_G2
mdefine_line|#define PT_V9_G2     0x10
DECL|macro|PT_V9_G3
mdefine_line|#define PT_V9_G3     0x18
DECL|macro|PT_V9_G4
mdefine_line|#define PT_V9_G4     0x20
DECL|macro|PT_V9_G5
mdefine_line|#define PT_V9_G5     0x28
DECL|macro|PT_V9_G6
mdefine_line|#define PT_V9_G6     0x30
DECL|macro|PT_V9_G7
mdefine_line|#define PT_V9_G7     0x38
DECL|macro|PT_V9_I0
mdefine_line|#define PT_V9_I0     0x40
DECL|macro|PT_V9_I1
mdefine_line|#define PT_V9_I1     0x48
DECL|macro|PT_V9_I2
mdefine_line|#define PT_V9_I2     0x50
DECL|macro|PT_V9_I3
mdefine_line|#define PT_V9_I3     0x58
DECL|macro|PT_V9_I4
mdefine_line|#define PT_V9_I4     0x60
DECL|macro|PT_V9_I5
mdefine_line|#define PT_V9_I5     0x68
DECL|macro|PT_V9_I6
mdefine_line|#define PT_V9_I6     0x70
DECL|macro|PT_V9_FP
mdefine_line|#define PT_V9_FP     PT_V9_I6
DECL|macro|PT_V9_I7
mdefine_line|#define PT_V9_I7     0x78
DECL|macro|PT_V9_TSTATE
mdefine_line|#define PT_V9_TSTATE 0x80
DECL|macro|PT_V9_TPC
mdefine_line|#define PT_V9_TPC    0x88
DECL|macro|PT_V9_TNPC
mdefine_line|#define PT_V9_TNPC   0x90
DECL|macro|PT_V9_Y
mdefine_line|#define PT_V9_Y      0x98
DECL|macro|PT_V9_FPRS
mdefine_line|#define PT_V9_FPRS   0x9c
DECL|macro|PT_TSTATE
mdefine_line|#define PT_TSTATE&t;PT_V9_TSTATE
DECL|macro|PT_TPC
mdefine_line|#define PT_TPC&t;&t;PT_V9_TPC
DECL|macro|PT_TNPC
mdefine_line|#define PT_TNPC&t;&t;PT_V9_TNPC
multiline_comment|/* These for pt_regs32. */
DECL|macro|PT_PSR
mdefine_line|#define PT_PSR    0x0
DECL|macro|PT_PC
mdefine_line|#define PT_PC     0x4
DECL|macro|PT_NPC
mdefine_line|#define PT_NPC    0x8
DECL|macro|PT_Y
mdefine_line|#define PT_Y      0xc
DECL|macro|PT_G0
mdefine_line|#define PT_G0     0x10
DECL|macro|PT_WIM
mdefine_line|#define PT_WIM    PT_G0
DECL|macro|PT_G1
mdefine_line|#define PT_G1     0x14
DECL|macro|PT_G2
mdefine_line|#define PT_G2     0x18
DECL|macro|PT_G3
mdefine_line|#define PT_G3     0x1c
DECL|macro|PT_G4
mdefine_line|#define PT_G4     0x20
DECL|macro|PT_G5
mdefine_line|#define PT_G5     0x24
DECL|macro|PT_G6
mdefine_line|#define PT_G6     0x28
DECL|macro|PT_G7
mdefine_line|#define PT_G7     0x2c
DECL|macro|PT_I0
mdefine_line|#define PT_I0     0x30
DECL|macro|PT_I1
mdefine_line|#define PT_I1     0x34
DECL|macro|PT_I2
mdefine_line|#define PT_I2     0x38
DECL|macro|PT_I3
mdefine_line|#define PT_I3     0x3c
DECL|macro|PT_I4
mdefine_line|#define PT_I4     0x40
DECL|macro|PT_I5
mdefine_line|#define PT_I5     0x44
DECL|macro|PT_I6
mdefine_line|#define PT_I6     0x48
DECL|macro|PT_FP
mdefine_line|#define PT_FP     PT_I6
DECL|macro|PT_I7
mdefine_line|#define PT_I7     0x4c
multiline_comment|/* Reg_window offsets */
DECL|macro|RW_V9_L0
mdefine_line|#define RW_V9_L0     0x00
DECL|macro|RW_V9_L1
mdefine_line|#define RW_V9_L1     0x08
DECL|macro|RW_V9_L2
mdefine_line|#define RW_V9_L2     0x10
DECL|macro|RW_V9_L3
mdefine_line|#define RW_V9_L3     0x18
DECL|macro|RW_V9_L4
mdefine_line|#define RW_V9_L4     0x20
DECL|macro|RW_V9_L5
mdefine_line|#define RW_V9_L5     0x28
DECL|macro|RW_V9_L6
mdefine_line|#define RW_V9_L6     0x30
DECL|macro|RW_V9_L7
mdefine_line|#define RW_V9_L7     0x38
DECL|macro|RW_V9_I0
mdefine_line|#define RW_V9_I0     0x40
DECL|macro|RW_V9_I1
mdefine_line|#define RW_V9_I1     0x48
DECL|macro|RW_V9_I2
mdefine_line|#define RW_V9_I2     0x50
DECL|macro|RW_V9_I3
mdefine_line|#define RW_V9_I3     0x58
DECL|macro|RW_V9_I4
mdefine_line|#define RW_V9_I4     0x60
DECL|macro|RW_V9_I5
mdefine_line|#define RW_V9_I5     0x68
DECL|macro|RW_V9_I6
mdefine_line|#define RW_V9_I6     0x70
DECL|macro|RW_V9_I7
mdefine_line|#define RW_V9_I7     0x78
DECL|macro|RW_L0
mdefine_line|#define RW_L0     0x00
DECL|macro|RW_L1
mdefine_line|#define RW_L1     0x04
DECL|macro|RW_L2
mdefine_line|#define RW_L2     0x08
DECL|macro|RW_L3
mdefine_line|#define RW_L3     0x0c
DECL|macro|RW_L4
mdefine_line|#define RW_L4     0x10
DECL|macro|RW_L5
mdefine_line|#define RW_L5     0x14
DECL|macro|RW_L6
mdefine_line|#define RW_L6     0x18
DECL|macro|RW_L7
mdefine_line|#define RW_L7     0x1c
DECL|macro|RW_I0
mdefine_line|#define RW_I0     0x20
DECL|macro|RW_I1
mdefine_line|#define RW_I1     0x24
DECL|macro|RW_I2
mdefine_line|#define RW_I2     0x28
DECL|macro|RW_I3
mdefine_line|#define RW_I3     0x2c
DECL|macro|RW_I4
mdefine_line|#define RW_I4     0x30
DECL|macro|RW_I5
mdefine_line|#define RW_I5     0x34
DECL|macro|RW_I6
mdefine_line|#define RW_I6     0x38
DECL|macro|RW_I7
mdefine_line|#define RW_I7     0x3c
multiline_comment|/* Stack_frame offsets */
DECL|macro|SF_V9_L0
mdefine_line|#define SF_V9_L0     0x00
DECL|macro|SF_V9_L1
mdefine_line|#define SF_V9_L1     0x08
DECL|macro|SF_V9_L2
mdefine_line|#define SF_V9_L2     0x10
DECL|macro|SF_V9_L3
mdefine_line|#define SF_V9_L3     0x18
DECL|macro|SF_V9_L4
mdefine_line|#define SF_V9_L4     0x20
DECL|macro|SF_V9_L5
mdefine_line|#define SF_V9_L5     0x28
DECL|macro|SF_V9_L6
mdefine_line|#define SF_V9_L6     0x30
DECL|macro|SF_V9_L7
mdefine_line|#define SF_V9_L7     0x38
DECL|macro|SF_V9_I0
mdefine_line|#define SF_V9_I0     0x40
DECL|macro|SF_V9_I1
mdefine_line|#define SF_V9_I1     0x48
DECL|macro|SF_V9_I2
mdefine_line|#define SF_V9_I2     0x50
DECL|macro|SF_V9_I3
mdefine_line|#define SF_V9_I3     0x58
DECL|macro|SF_V9_I4
mdefine_line|#define SF_V9_I4     0x60
DECL|macro|SF_V9_I5
mdefine_line|#define SF_V9_I5     0x68
DECL|macro|SF_V9_FP
mdefine_line|#define SF_V9_FP     0x70
DECL|macro|SF_V9_PC
mdefine_line|#define SF_V9_PC     0x78
DECL|macro|SF_V9_RETP
mdefine_line|#define SF_V9_RETP   0x80
DECL|macro|SF_V9_XARG0
mdefine_line|#define SF_V9_XARG0  0x88
DECL|macro|SF_V9_XARG1
mdefine_line|#define SF_V9_XARG1  0x90
DECL|macro|SF_V9_XARG2
mdefine_line|#define SF_V9_XARG2  0x98
DECL|macro|SF_V9_XARG3
mdefine_line|#define SF_V9_XARG3  0xa0
DECL|macro|SF_V9_XARG4
mdefine_line|#define SF_V9_XARG4  0xa8
DECL|macro|SF_V9_XARG5
mdefine_line|#define SF_V9_XARG5  0xb0
DECL|macro|SF_V9_XXARG
mdefine_line|#define SF_V9_XXARG  0xb8
DECL|macro|SF_L0
mdefine_line|#define SF_L0     0x00
DECL|macro|SF_L1
mdefine_line|#define SF_L1     0x04
DECL|macro|SF_L2
mdefine_line|#define SF_L2     0x08
DECL|macro|SF_L3
mdefine_line|#define SF_L3     0x0c
DECL|macro|SF_L4
mdefine_line|#define SF_L4     0x10
DECL|macro|SF_L5
mdefine_line|#define SF_L5     0x14
DECL|macro|SF_L6
mdefine_line|#define SF_L6     0x18
DECL|macro|SF_L7
mdefine_line|#define SF_L7     0x1c
DECL|macro|SF_I0
mdefine_line|#define SF_I0     0x20
DECL|macro|SF_I1
mdefine_line|#define SF_I1     0x24
DECL|macro|SF_I2
mdefine_line|#define SF_I2     0x28
DECL|macro|SF_I3
mdefine_line|#define SF_I3     0x2c
DECL|macro|SF_I4
mdefine_line|#define SF_I4     0x30
DECL|macro|SF_I5
mdefine_line|#define SF_I5     0x34
DECL|macro|SF_FP
mdefine_line|#define SF_FP     0x38
DECL|macro|SF_PC
mdefine_line|#define SF_PC     0x3c
DECL|macro|SF_RETP
mdefine_line|#define SF_RETP   0x40
DECL|macro|SF_XARG0
mdefine_line|#define SF_XARG0  0x44
DECL|macro|SF_XARG1
mdefine_line|#define SF_XARG1  0x48
DECL|macro|SF_XARG2
mdefine_line|#define SF_XARG2  0x4c
DECL|macro|SF_XARG3
mdefine_line|#define SF_XARG3  0x50
DECL|macro|SF_XARG4
mdefine_line|#define SF_XARG4  0x54
DECL|macro|SF_XARG5
mdefine_line|#define SF_XARG5  0x58
DECL|macro|SF_XXARG
mdefine_line|#define SF_XXARG  0x5c
multiline_comment|/* Stuff for the ptrace system call */
DECL|macro|PTRACE_SUNATTACH
mdefine_line|#define PTRACE_SUNATTACH          10
DECL|macro|PTRACE_SUNDETACH
mdefine_line|#define PTRACE_SUNDETACH          11
DECL|macro|PTRACE_GETREGS
mdefine_line|#define PTRACE_GETREGS            12
DECL|macro|PTRACE_SETREGS
mdefine_line|#define PTRACE_SETREGS            13
DECL|macro|PTRACE_GETFPREGS
mdefine_line|#define PTRACE_GETFPREGS          14
DECL|macro|PTRACE_SETFPREGS
mdefine_line|#define PTRACE_SETFPREGS          15
DECL|macro|PTRACE_READDATA
mdefine_line|#define PTRACE_READDATA           16
DECL|macro|PTRACE_WRITEDATA
mdefine_line|#define PTRACE_WRITEDATA          17
DECL|macro|PTRACE_READTEXT
mdefine_line|#define PTRACE_READTEXT           18
DECL|macro|PTRACE_WRITETEXT
mdefine_line|#define PTRACE_WRITETEXT          19
DECL|macro|PTRACE_GETFPAREGS
mdefine_line|#define PTRACE_GETFPAREGS         20
DECL|macro|PTRACE_SETFPAREGS
mdefine_line|#define PTRACE_SETFPAREGS         21
multiline_comment|/* There are for debugging 64-bit processes, either from a 32 or 64 bit&n; * parent.  Thus their compliments are for debugging 32-bit processes only.&n; */
DECL|macro|PTRACE_GETREGS64
mdefine_line|#define PTRACE_GETREGS64&t;  22
DECL|macro|PTRACE_SETREGS64
mdefine_line|#define PTRACE_SETREGS64&t;  23
multiline_comment|/* PTRACE_SYSCALL is 24 */
DECL|macro|PTRACE_GETFPREGS64
mdefine_line|#define PTRACE_GETFPREGS64&t;  25
DECL|macro|PTRACE_SETFPREGS64
mdefine_line|#define PTRACE_SETFPREGS64&t;  26
DECL|macro|PTRACE_GETUCODE
mdefine_line|#define PTRACE_GETUCODE           29  /* stupid bsd-ism */
multiline_comment|/* These are for 32-bit processes debugging 64-bit ones.&n; * Here addr and addr2 are passed in %g2 and %g3 respectively.&n; */
DECL|macro|PTRACE_PEEKTEXT64
mdefine_line|#define PTRACE_PEEKTEXT64         (30 + PTRACE_PEEKTEXT)
DECL|macro|PTRACE_POKETEXT64
mdefine_line|#define PTRACE_POKETEXT64         (30 + PTRACE_POKETEXT)
DECL|macro|PTRACE_PEEKDATA64
mdefine_line|#define PTRACE_PEEKDATA64         (30 + PTRACE_PEEKDATA)
DECL|macro|PTRACE_POKEDATA64
mdefine_line|#define PTRACE_POKEDATA64         (30 + PTRACE_POKEDATA)
DECL|macro|PTRACE_READDATA64
mdefine_line|#define PTRACE_READDATA64         (30 + PTRACE_READDATA)
DECL|macro|PTRACE_WRITEDATA64
mdefine_line|#define PTRACE_WRITEDATA64        (30 + PTRACE_WRITEDATA)
DECL|macro|PTRACE_READTEXT64
mdefine_line|#define PTRACE_READTEXT64         (30 + PTRACE_READTEXT)
DECL|macro|PTRACE_WRITETEXT64
mdefine_line|#define PTRACE_WRITETEXT64        (30 + PTRACE_WRITETEXT)
macro_line|#endif /* !(_SPARC64_PTRACE_H) */
eof
