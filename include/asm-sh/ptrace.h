macro_line|#ifndef __ASM_SH_PTRACE_H
DECL|macro|__ASM_SH_PTRACE_H
mdefine_line|#define __ASM_SH_PTRACE_H
multiline_comment|/*&n; * Copyright (C) 1999, 2000  Niibe Yutaka&n; *&n; */
multiline_comment|/*&n; * GCC defines register number like this:&n; * -----------------------------&n; *&t; 0 - 15 are integer registers&n; *&t;17 - 22 are control/special registers&n; *&t;24 - 39 fp registers&n; *&t;40 - 47 xd registers&n; *&t;48 -    fpscr register&n; * -----------------------------&n; *&n; * We follows above, except:&n; *&t;16 --- program counter (PC)&n; *&t;22 --- syscall #&n; *&t;23 --- floating point communication register&n; */
DECL|macro|REG_REG0
mdefine_line|#define REG_REG0&t; 0
DECL|macro|REG_REG15
mdefine_line|#define REG_REG15&t;15
DECL|macro|REG_PC
mdefine_line|#define REG_PC&t;&t;16
DECL|macro|REG_PR
mdefine_line|#define REG_PR&t;&t;17
DECL|macro|REG_SR
mdefine_line|#define REG_SR&t;&t;18
DECL|macro|REG_GBR
mdefine_line|#define REG_GBR      &t;19
DECL|macro|REG_MACH
mdefine_line|#define REG_MACH&t;20
DECL|macro|REG_MACL
mdefine_line|#define REG_MACL&t;21
DECL|macro|REG_SYSCALL
mdefine_line|#define REG_SYSCALL&t;22
DECL|macro|REG_FPUL
mdefine_line|#define REG_FPUL&t;23
DECL|macro|REG_FPREG0
mdefine_line|#define REG_FPREG0&t;24
DECL|macro|REG_FPREG15
mdefine_line|#define REG_FPREG15&t;39
DECL|macro|REG_XDREG0
mdefine_line|#define REG_XDREG0&t;40
DECL|macro|REG_XDREG14
mdefine_line|#define REG_XDREG14&t;47
DECL|macro|REG_FPSCR
mdefine_line|#define REG_FPSCR&t;48
DECL|macro|PTRACE_SETOPTIONS
mdefine_line|#define PTRACE_SETOPTIONS         21
multiline_comment|/* options set using PTRACE_SETOPTIONS */
DECL|macro|PTRACE_O_TRACESYSGOOD
mdefine_line|#define PTRACE_O_TRACESYSGOOD     0x00000001
multiline_comment|/*&n; * This struct defines the way the registers are stored on the&n; * kernel stack during a system call or other kernel entry.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|pr
r_int
r_int
id|pr
suffix:semicolon
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
DECL|member|gbr
r_int
r_int
id|gbr
suffix:semicolon
DECL|member|mach
r_int
r_int
id|mach
suffix:semicolon
DECL|member|macl
r_int
r_int
id|macl
suffix:semicolon
DECL|member|syscall_nr
r_int
id|syscall_nr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (((regs)-&gt;sr &amp; 0x40000000)==0)
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;pc)
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
multiline_comment|/* User Break Controller */
macro_line|#if defined(__sh3__)
DECL|macro|UBC_BARA
mdefine_line|#define UBC_BARA                0xffffffb0
DECL|macro|UBC_BAMRA
mdefine_line|#define UBC_BAMRA               0xffffffb4
DECL|macro|UBC_BBRA
mdefine_line|#define UBC_BBRA                0xffffffb8
DECL|macro|UBC_BASRA
mdefine_line|#define UBC_BASRA               0xffffffe4
DECL|macro|UBC_BARB
mdefine_line|#define UBC_BARB                0xffffffa0
DECL|macro|UBC_BAMRB
mdefine_line|#define UBC_BAMRB               0xffffffa4
DECL|macro|UBC_BBRB
mdefine_line|#define UBC_BBRB                0xffffffa8
DECL|macro|UBC_BASRB
mdefine_line|#define UBC_BASRB               0xffffffe8
DECL|macro|UBC_BDRB
mdefine_line|#define UBC_BDRB                0xffffff90
DECL|macro|UBC_BDMRB
mdefine_line|#define UBC_BDMRB               0xffffff94
DECL|macro|UBC_BRCR
mdefine_line|#define UBC_BRCR                0xffffff98
macro_line|#elif defined(__SH4__)
DECL|macro|UBC_BARA
mdefine_line|#define UBC_BARA&t;&t;0xff200000
DECL|macro|UBC_BAMRA
mdefine_line|#define UBC_BAMRA&t;&t;0xff200004
DECL|macro|UBC_BBRA
mdefine_line|#define UBC_BBRA&t;&t;0xff200008
DECL|macro|UBC_BASRA
mdefine_line|#define UBC_BASRA&t;&t;0xff000014
DECL|macro|UBC_BARB
mdefine_line|#define UBC_BARB&t;&t;0xff20000c
DECL|macro|UBC_BAMRB
mdefine_line|#define UBC_BAMRB&t;&t;0xff200010
DECL|macro|UBC_BBRB
mdefine_line|#define UBC_BBRB&t;&t;0xff200014
DECL|macro|UBC_BASRB
mdefine_line|#define UBC_BASRB&t;&t;0xff000018
DECL|macro|UBC_BDRB
mdefine_line|#define UBC_BDRB&t;&t;0xff200018
DECL|macro|UBC_BDMRB
mdefine_line|#define UBC_BDMRB&t;&t;0xff20001c
DECL|macro|UBC_BRCR
mdefine_line|#define UBC_BRCR&t;&t;0xff200020
macro_line|#endif
DECL|macro|BAMR_ASID
mdefine_line|#define BAMR_ASID&t;&t;(1 &lt;&lt; 2)
DECL|macro|BAMR_NONE
mdefine_line|#define BAMR_NONE&t;&t;0
DECL|macro|BAMR_10
mdefine_line|#define BAMR_10&t;&t;&t;0x1
DECL|macro|BAMR_12
mdefine_line|#define BAMR_12&t;&t;&t;0x2
DECL|macro|BAMR_ALL
mdefine_line|#define BAMR_ALL&t;&t;0x3
DECL|macro|BAMR_16
mdefine_line|#define BAMR_16&t;&t;&t;0x8
DECL|macro|BAMR_20
mdefine_line|#define BAMR_20&t;&t;&t;0x9
DECL|macro|BBR_INST
mdefine_line|#define BBR_INST&t;&t;(1 &lt;&lt; 4)
DECL|macro|BBR_DATA
mdefine_line|#define BBR_DATA&t;&t;(2 &lt;&lt; 4)
DECL|macro|BBR_READ
mdefine_line|#define BBR_READ&t;&t;(1 &lt;&lt; 2)
DECL|macro|BBR_WRITE
mdefine_line|#define BBR_WRITE&t;&t;(2 &lt;&lt; 4)
DECL|macro|BBR_BYTE
mdefine_line|#define BBR_BYTE&t;&t;0x1
DECL|macro|BBR_HALF
mdefine_line|#define BBR_HALF&t;&t;0x2
DECL|macro|BBR_LONG
mdefine_line|#define BBR_LONG&t;&t;0x3
DECL|macro|BBR_QUAD
mdefine_line|#define BBR_QUAD&t;&t;(1 &lt;&lt; 6)
DECL|macro|BRCR_CMFA
mdefine_line|#define BRCR_CMFA&t;&t;(1 &lt;&lt; 15)
DECL|macro|BRCR_CMFB
mdefine_line|#define BRCR_CMFB&t;&t;(1 &lt;&lt; 14)
DECL|macro|BRCR_PCBA
mdefine_line|#define BRCR_PCBA&t;&t;(1 &lt;&lt; 10)&t;/* 1: after execution */
DECL|macro|BRCR_DBEB
mdefine_line|#define BRCR_DBEB&t;&t;(1 &lt;&lt; 7)
DECL|macro|BRCR_PCBB
mdefine_line|#define BRCR_PCBB&t;&t;(1 &lt;&lt; 6)
DECL|macro|BRCR_SEQ
mdefine_line|#define BRCR_SEQ&t;&t;(1 &lt;&lt; 3)
DECL|macro|BRCR_UBDE
mdefine_line|#define BRCR_UBDE&t;&t;(1 &lt;&lt; 0)
macro_line|#endif
macro_line|#endif /* __ASM_SH_PTRACE_H */
eof
