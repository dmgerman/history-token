multiline_comment|/*&n; *  include/asm-s390/ptrace.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; */
macro_line|#ifndef _S390_PTRACE_H
DECL|macro|_S390_PTRACE_H
mdefine_line|#define _S390_PTRACE_H
multiline_comment|/*&n; * Offsets in the user_regs_struct. They are used for the ptrace&n; * system call and in entry.S&n; */
DECL|macro|PT_PSWMASK
mdefine_line|#define PT_PSWMASK  0x00
DECL|macro|PT_PSWADDR
mdefine_line|#define PT_PSWADDR  0x04
DECL|macro|PT_GPR0
mdefine_line|#define PT_GPR0     0x08
DECL|macro|PT_GPR1
mdefine_line|#define PT_GPR1     0x0C
DECL|macro|PT_GPR2
mdefine_line|#define PT_GPR2     0x10
DECL|macro|PT_GPR3
mdefine_line|#define PT_GPR3     0x14
DECL|macro|PT_GPR4
mdefine_line|#define PT_GPR4     0x18
DECL|macro|PT_GPR5
mdefine_line|#define PT_GPR5     0x1C
DECL|macro|PT_GPR6
mdefine_line|#define PT_GPR6     0x20
DECL|macro|PT_GPR7
mdefine_line|#define PT_GPR7     0x24
DECL|macro|PT_GPR8
mdefine_line|#define PT_GPR8     0x28
DECL|macro|PT_GPR9
mdefine_line|#define PT_GPR9     0x2C
DECL|macro|PT_GPR10
mdefine_line|#define PT_GPR10    0x30
DECL|macro|PT_GPR11
mdefine_line|#define PT_GPR11    0x34
DECL|macro|PT_GPR12
mdefine_line|#define PT_GPR12    0x38
DECL|macro|PT_GPR13
mdefine_line|#define PT_GPR13    0x3C
DECL|macro|PT_GPR14
mdefine_line|#define PT_GPR14    0x40
DECL|macro|PT_GPR15
mdefine_line|#define PT_GPR15    0x44
DECL|macro|PT_ACR0
mdefine_line|#define PT_ACR0     0x48
DECL|macro|PT_ACR1
mdefine_line|#define PT_ACR1     0x4C
DECL|macro|PT_ACR2
mdefine_line|#define PT_ACR2     0x50
DECL|macro|PT_ACR3
mdefine_line|#define PT_ACR3     0x54
DECL|macro|PT_ACR4
mdefine_line|#define PT_ACR4&t;    0x58
DECL|macro|PT_ACR5
mdefine_line|#define PT_ACR5&t;    0x5C
DECL|macro|PT_ACR6
mdefine_line|#define PT_ACR6&t;    0x60
DECL|macro|PT_ACR7
mdefine_line|#define PT_ACR7&t;    0x64
DECL|macro|PT_ACR8
mdefine_line|#define PT_ACR8&t;    0x68
DECL|macro|PT_ACR9
mdefine_line|#define PT_ACR9&t;    0x6C
DECL|macro|PT_ACR10
mdefine_line|#define PT_ACR10    0x70
DECL|macro|PT_ACR11
mdefine_line|#define PT_ACR11    0x74
DECL|macro|PT_ACR12
mdefine_line|#define PT_ACR12    0x78
DECL|macro|PT_ACR13
mdefine_line|#define PT_ACR13    0x7C
DECL|macro|PT_ACR14
mdefine_line|#define PT_ACR14    0x80
DECL|macro|PT_ACR15
mdefine_line|#define PT_ACR15    0x84
DECL|macro|PT_ORIGGPR2
mdefine_line|#define PT_ORIGGPR2 0x88
DECL|macro|PT_FPC
mdefine_line|#define PT_FPC&t;    0x90
multiline_comment|/*&n; * A nasty fact of life that the ptrace api&n; * only supports passing of longs.&n; */
DECL|macro|PT_FPR0_HI
mdefine_line|#define PT_FPR0_HI  0x98
DECL|macro|PT_FPR0_LO
mdefine_line|#define PT_FPR0_LO  0x9C
DECL|macro|PT_FPR1_HI
mdefine_line|#define PT_FPR1_HI  0xA0
DECL|macro|PT_FPR1_LO
mdefine_line|#define PT_FPR1_LO  0xA4
DECL|macro|PT_FPR2_HI
mdefine_line|#define PT_FPR2_HI  0xA8
DECL|macro|PT_FPR2_LO
mdefine_line|#define PT_FPR2_LO  0xAC
DECL|macro|PT_FPR3_HI
mdefine_line|#define PT_FPR3_HI  0xB0
DECL|macro|PT_FPR3_LO
mdefine_line|#define PT_FPR3_LO  0xB4
DECL|macro|PT_FPR4_HI
mdefine_line|#define PT_FPR4_HI  0xB8
DECL|macro|PT_FPR4_LO
mdefine_line|#define PT_FPR4_LO  0xBC
DECL|macro|PT_FPR5_HI
mdefine_line|#define PT_FPR5_HI  0xC0
DECL|macro|PT_FPR5_LO
mdefine_line|#define PT_FPR5_LO  0xC4
DECL|macro|PT_FPR6_HI
mdefine_line|#define PT_FPR6_HI  0xC8
DECL|macro|PT_FPR6_LO
mdefine_line|#define PT_FPR6_LO  0xCC
DECL|macro|PT_FPR7_HI
mdefine_line|#define PT_FPR7_HI  0xD0
DECL|macro|PT_FPR7_LO
mdefine_line|#define PT_FPR7_LO  0xD4
DECL|macro|PT_FPR8_HI
mdefine_line|#define PT_FPR8_HI  0xD8
DECL|macro|PT_FPR8_LO
mdefine_line|#define PT_FPR8_LO  0XDC
DECL|macro|PT_FPR9_HI
mdefine_line|#define PT_FPR9_HI  0xE0
DECL|macro|PT_FPR9_LO
mdefine_line|#define PT_FPR9_LO  0xE4
DECL|macro|PT_FPR10_HI
mdefine_line|#define PT_FPR10_HI 0xE8
DECL|macro|PT_FPR10_LO
mdefine_line|#define PT_FPR10_LO 0xEC
DECL|macro|PT_FPR11_HI
mdefine_line|#define PT_FPR11_HI 0xF0
DECL|macro|PT_FPR11_LO
mdefine_line|#define PT_FPR11_LO 0xF4
DECL|macro|PT_FPR12_HI
mdefine_line|#define PT_FPR12_HI 0xF8
DECL|macro|PT_FPR12_LO
mdefine_line|#define PT_FPR12_LO 0xFC
DECL|macro|PT_FPR13_HI
mdefine_line|#define PT_FPR13_HI 0x100
DECL|macro|PT_FPR13_LO
mdefine_line|#define PT_FPR13_LO 0x104
DECL|macro|PT_FPR14_HI
mdefine_line|#define PT_FPR14_HI 0x108
DECL|macro|PT_FPR14_LO
mdefine_line|#define PT_FPR14_LO 0x10C
DECL|macro|PT_FPR15_HI
mdefine_line|#define PT_FPR15_HI 0x110
DECL|macro|PT_FPR15_LO
mdefine_line|#define PT_FPR15_LO 0x114
DECL|macro|PT_CR_9
mdefine_line|#define PT_CR_9&t;    0x118
DECL|macro|PT_CR_10
mdefine_line|#define PT_CR_10    0x11C
DECL|macro|PT_CR_11
mdefine_line|#define PT_CR_11    0x120
DECL|macro|PT_IEEE_IP
mdefine_line|#define PT_IEEE_IP  0x13C
DECL|macro|PT_LASTOFF
mdefine_line|#define PT_LASTOFF  PT_IEEE_IP
DECL|macro|PT_ENDREGS
mdefine_line|#define PT_ENDREGS  0x140-1
DECL|macro|NUM_GPRS
mdefine_line|#define NUM_GPRS&t;16
DECL|macro|NUM_FPRS
mdefine_line|#define NUM_FPRS&t;16
DECL|macro|NUM_CRS
mdefine_line|#define NUM_CRS&t;&t;16
DECL|macro|NUM_ACRS
mdefine_line|#define NUM_ACRS&t;16
DECL|macro|GPR_SIZE
mdefine_line|#define GPR_SIZE&t;4
DECL|macro|FPR_SIZE
mdefine_line|#define FPR_SIZE&t;8
DECL|macro|FPC_SIZE
mdefine_line|#define FPC_SIZE&t;4
DECL|macro|FPC_PAD_SIZE
mdefine_line|#define FPC_PAD_SIZE&t;4 /* gcc insists on aligning the fpregs */
DECL|macro|CR_SIZE
mdefine_line|#define CR_SIZE&t;&t;4
DECL|macro|ACR_SIZE
mdefine_line|#define ACR_SIZE&t;4
DECL|macro|STACK_FRAME_OVERHEAD
mdefine_line|#define STACK_FRAME_OVERHEAD&t;96&t;/* size of minimum stack frame */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
multiline_comment|/* this typedef defines how a Program Status Word looks like */
r_typedef
r_struct
(brace
DECL|member|mask
id|__u32
id|mask
suffix:semicolon
DECL|member|addr
id|__u32
id|addr
suffix:semicolon
DECL|typedef|psw_t
)brace
id|psw_t
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|FIX_PSW
mdefine_line|#define FIX_PSW(addr) ((unsigned long)(addr)|0x80000000UL)
DECL|macro|ADDR_BITS_REMOVE
mdefine_line|#define ADDR_BITS_REMOVE(addr) ((addr)&amp;0x7fffffff)
macro_line|#endif
r_typedef
r_union
(brace
DECL|member|f
r_float
id|f
suffix:semicolon
DECL|member|d
r_float
id|d
suffix:semicolon
DECL|member|ui
id|__u64
id|ui
suffix:semicolon
r_struct
(brace
DECL|member|hi
id|__u32
id|hi
suffix:semicolon
DECL|member|lo
id|__u32
id|lo
suffix:semicolon
DECL|member|fp
)brace
id|fp
suffix:semicolon
DECL|typedef|freg_t
)brace
id|freg_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|fpc
id|__u32
id|fpc
suffix:semicolon
DECL|member|fprs
id|freg_t
id|fprs
(braket
id|NUM_FPRS
)braket
suffix:semicolon
DECL|typedef|s390_fp_regs
)brace
id|s390_fp_regs
suffix:semicolon
DECL|macro|FPC_EXCEPTION_MASK
mdefine_line|#define FPC_EXCEPTION_MASK      0xF8000000
DECL|macro|FPC_FLAGS_MASK
mdefine_line|#define FPC_FLAGS_MASK          0x00F80000
DECL|macro|FPC_DXC_MASK
mdefine_line|#define FPC_DXC_MASK            0x0000FF00
DECL|macro|FPC_RM_MASK
mdefine_line|#define FPC_RM_MASK             0x00000003
DECL|macro|FPC_VALID_MASK
mdefine_line|#define FPC_VALID_MASK          0xF8F8FF03
multiline_comment|/*&n; * The first entries in pt_regs, gdb_pt_regs and user_regs_struct&n; * are common for all three structures. The s390_regs structure&n; * covers the common parts. It simplifies copying the common part&n; * between the three structures.&n; */
r_typedef
r_struct
(brace
DECL|member|psw
id|psw_t
id|psw
suffix:semicolon
DECL|member|gprs
id|__u32
id|gprs
(braket
id|NUM_GPRS
)braket
suffix:semicolon
DECL|member|acrs
id|__u32
id|acrs
(braket
id|NUM_ACRS
)braket
suffix:semicolon
DECL|member|orig_gpr2
id|__u32
id|orig_gpr2
suffix:semicolon
DECL|typedef|s390_regs
)brace
id|s390_regs
suffix:semicolon
multiline_comment|/*&n; * The pt_regs struct defines the way the registers are stored on&n; * the stack during a system call.&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|psw
id|psw_t
id|psw
suffix:semicolon
DECL|member|gprs
id|__u32
id|gprs
(braket
id|NUM_GPRS
)braket
suffix:semicolon
DECL|member|acrs
id|__u32
id|acrs
(braket
id|NUM_ACRS
)braket
suffix:semicolon
DECL|member|orig_gpr2
id|__u32
id|orig_gpr2
suffix:semicolon
DECL|member|trap
id|__u32
id|trap
suffix:semicolon
DECL|member|old_ilc
id|__u32
id|old_ilc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The gdb_pt_regs struct is used instead of the pt_regs structure&n; * if kernel remote debugging is used.&n; */
macro_line|#if CONFIG_REMOTE_DEBUG
DECL|struct|gdb_pt_regs
r_struct
id|gdb_pt_regs
(brace
DECL|member|psw
id|psw_t
id|psw
suffix:semicolon
DECL|member|gprs
id|__u32
id|gprs
(braket
id|NUM_GPRS
)braket
suffix:semicolon
DECL|member|acrs
id|__u32
id|acrs
(braket
id|NUM_ACRS
)braket
suffix:semicolon
DECL|member|orig_gpr2
id|__u32
id|orig_gpr2
suffix:semicolon
DECL|member|trap
id|__u32
id|trap
suffix:semicolon
DECL|member|crs
id|__u32
id|crs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|fp_regs
id|s390_fp_regs
id|fp_regs
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Now for the program event recording (trace) definitions.&n; */
r_typedef
r_struct
(brace
DECL|member|cr
id|__u32
id|cr
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|per_cr_words
)brace
id|per_cr_words
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|PER_EM_MASK
mdefine_line|#define PER_EM_MASK 0xE8000000
r_typedef
r_struct
(brace
DECL|member|em_branching
r_int
id|em_branching
suffix:colon
l_int|1
suffix:semicolon
DECL|member|em_instruction_fetch
r_int
id|em_instruction_fetch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Switching on storage alteration automatically fixes&n;&t; * the storage alteration event bit in the users std.&n;&t; */
DECL|member|em_storage_alteration
r_int
id|em_storage_alteration
suffix:colon
l_int|1
suffix:semicolon
DECL|member|em_gpr_alt_unused
r_int
id|em_gpr_alt_unused
suffix:colon
l_int|1
suffix:semicolon
DECL|member|em_store_real_address
r_int
id|em_store_real_address
suffix:colon
l_int|1
suffix:semicolon
r_int
suffix:colon
l_int|3
suffix:semicolon
DECL|member|branch_addr_ctl
r_int
id|branch_addr_ctl
suffix:colon
l_int|1
suffix:semicolon
r_int
suffix:colon
l_int|1
suffix:semicolon
DECL|member|storage_alt_space_ctl
r_int
id|storage_alt_space_ctl
suffix:colon
l_int|1
suffix:semicolon
r_int
suffix:colon
l_int|21
suffix:semicolon
DECL|member|starting_addr
id|addr_t
id|starting_addr
suffix:semicolon
DECL|member|ending_addr
id|addr_t
id|ending_addr
suffix:semicolon
DECL|typedef|per_cr_bits
)brace
id|per_cr_bits
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|perc_atmid
id|__u16
id|perc_atmid
suffix:semicolon
multiline_comment|/* 0x096 */
DECL|member|address
id|__u32
id|address
suffix:semicolon
multiline_comment|/* 0x098 */
DECL|member|access_id
id|__u8
id|access_id
suffix:semicolon
multiline_comment|/* 0x0a1 */
DECL|typedef|per_lowcore_words
)brace
id|per_lowcore_words
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|perc_branching
r_int
id|perc_branching
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0x096 */
DECL|member|perc_instruction_fetch
r_int
id|perc_instruction_fetch
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perc_storage_alteration
r_int
id|perc_storage_alteration
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perc_gpr_alt_unused
r_int
id|perc_gpr_alt_unused
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perc_store_real_address
r_int
id|perc_store_real_address
suffix:colon
l_int|1
suffix:semicolon
r_int
suffix:colon
l_int|4
suffix:semicolon
DECL|member|atmid_validity_bit
r_int
id|atmid_validity_bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|atmid_psw_bit_32
r_int
id|atmid_psw_bit_32
suffix:colon
l_int|1
suffix:semicolon
DECL|member|atmid_psw_bit_5
r_int
id|atmid_psw_bit_5
suffix:colon
l_int|1
suffix:semicolon
DECL|member|atmid_psw_bit_16
r_int
id|atmid_psw_bit_16
suffix:colon
l_int|1
suffix:semicolon
DECL|member|atmid_psw_bit_17
r_int
id|atmid_psw_bit_17
suffix:colon
l_int|1
suffix:semicolon
DECL|member|si
r_int
id|si
suffix:colon
l_int|2
suffix:semicolon
DECL|member|address
id|addr_t
id|address
suffix:semicolon
multiline_comment|/* 0x098 */
r_int
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 0x0a1 */
DECL|member|access_id
r_int
id|access_id
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|per_lowcore_bits
)brace
id|per_lowcore_bits
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|words
id|per_cr_words
id|words
suffix:semicolon
DECL|member|bits
id|per_cr_bits
id|bits
suffix:semicolon
DECL|member|control_regs
)brace
id|control_regs
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Use these flags instead of setting em_instruction_fetch&n;&t; * directly they are used so that single stepping can be&n;&t; * switched on &amp; off while not affecting other tracing&n;&t; */
DECL|member|single_step
r_int
id|single_step
suffix:colon
l_int|1
suffix:semicolon
DECL|member|instruction_fetch
r_int
id|instruction_fetch
suffix:colon
l_int|1
suffix:semicolon
r_int
suffix:colon
l_int|30
suffix:semicolon
multiline_comment|/*&n;&t; * These addresses are copied into cr10 &amp; cr11 if single&n;&t; * stepping is switched off&n;&t; */
DECL|member|starting_addr
id|__u32
id|starting_addr
suffix:semicolon
DECL|member|ending_addr
id|__u32
id|ending_addr
suffix:semicolon
r_union
(brace
DECL|member|words
id|per_lowcore_words
id|words
suffix:semicolon
DECL|member|bits
id|per_lowcore_bits
id|bits
suffix:semicolon
DECL|member|lowcore
)brace
id|lowcore
suffix:semicolon
DECL|typedef|per_struct
)brace
id|per_struct
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|len
id|__u32
id|len
suffix:semicolon
DECL|member|kernel_addr
id|addr_t
id|kernel_addr
suffix:semicolon
DECL|member|process_addr
id|addr_t
id|process_addr
suffix:semicolon
DECL|typedef|ptrace_area
)brace
id|ptrace_area
suffix:semicolon
multiline_comment|/*&n; * S/390 specific non posix ptrace requests. I chose unusual values so&n; * they are unlikely to clash with future ptrace definitions.&n; */
DECL|macro|PTRACE_PEEKUSR_AREA
mdefine_line|#define PTRACE_PEEKUSR_AREA           0x5000
DECL|macro|PTRACE_POKEUSR_AREA
mdefine_line|#define PTRACE_POKEUSR_AREA           0x5001
DECL|macro|PTRACE_PEEKTEXT_AREA
mdefine_line|#define PTRACE_PEEKTEXT_AREA&t;      0x5002
DECL|macro|PTRACE_PEEKDATA_AREA
mdefine_line|#define PTRACE_PEEKDATA_AREA&t;      0x5003
DECL|macro|PTRACE_POKETEXT_AREA
mdefine_line|#define PTRACE_POKETEXT_AREA&t;      0x5004
DECL|macro|PTRACE_POKEDATA_AREA
mdefine_line|#define PTRACE_POKEDATA_AREA &t;      0x5005
multiline_comment|/*&n; * PT_PROT definition is loosely based on hppa bsd definition in&n; * gdb/hppab-nat.c&n; */
DECL|macro|PTRACE_PROT
mdefine_line|#define PTRACE_PROT                       21
r_typedef
r_enum
(brace
DECL|enumerator|ptprot_set_access_watchpoint
id|ptprot_set_access_watchpoint
comma
DECL|enumerator|ptprot_set_write_watchpoint
id|ptprot_set_write_watchpoint
comma
DECL|enumerator|ptprot_disable_watchpoint
id|ptprot_disable_watchpoint
DECL|typedef|ptprot_flags
)brace
id|ptprot_flags
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|lowaddr
id|addr_t
id|lowaddr
suffix:semicolon
DECL|member|hiaddr
id|addr_t
id|hiaddr
suffix:semicolon
DECL|member|prot
id|ptprot_flags
id|prot
suffix:semicolon
DECL|typedef|ptprot_area
)brace
id|ptprot_area
suffix:semicolon
multiline_comment|/* Sequence of bytes for breakpoint illegal instruction.  */
DECL|macro|S390_BREAKPOINT
mdefine_line|#define S390_BREAKPOINT     {0x0,0x1}
DECL|macro|S390_BREAKPOINT_U16
mdefine_line|#define S390_BREAKPOINT_U16 ((__u16)0x0001)
DECL|macro|S390_SYSCALL_OPCODE
mdefine_line|#define S390_SYSCALL_OPCODE ((__u16)0x0a00)
DECL|macro|S390_SYSCALL_SIZE
mdefine_line|#define S390_SYSCALL_SIZE   2
multiline_comment|/*&n; * The user_regs_struct defines the way the user registers are&n; * store on the stack for signal handling.&n; */
DECL|struct|user_regs_struct
r_struct
id|user_regs_struct
(brace
DECL|member|psw
id|psw_t
id|psw
suffix:semicolon
DECL|member|gprs
id|__u32
id|gprs
(braket
id|NUM_GPRS
)braket
suffix:semicolon
DECL|member|acrs
id|__u32
id|acrs
(braket
id|NUM_ACRS
)braket
suffix:semicolon
DECL|member|orig_gpr2
id|__u32
id|orig_gpr2
suffix:semicolon
DECL|member|fp_regs
id|s390_fp_regs
id|fp_regs
suffix:semicolon
multiline_comment|/*&n;&t; * These per registers are in here so that gdb can modify them&n;&t; * itself as there is no &quot;official&quot; ptrace interface for hardware&n;&t; * watchpoints. This is the way intel does it.&n;&t; */
DECL|member|per_info
id|per_struct
id|per_info
suffix:semicolon
DECL|member|ieee_instruction_pointer
id|addr_t
id|ieee_instruction_pointer
suffix:semicolon
multiline_comment|/* Used to give failing instruction back to user for ieee exceptions */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) (((regs)-&gt;psw.mask &amp; PSW_PROBLEM_STATE) != 0)
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;psw.addr)
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_char
op_star
id|task_show_regs
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _S390_PTRACE_H */
eof
