multiline_comment|/*&n; *  include/asm-s390/s390-regs-common.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; *  this file is designed to keep as much compatibility between&n; *  gdb&squot;s representation of registers &amp; the kernels representation of registers&n; *  as possible so as to minimise translation between gdb registers &amp;&n; *  kernel registers please keep this matched with gdb &amp; strace &n; */
macro_line|#ifndef _S390_REGS_COMMON_H
DECL|macro|_S390_REGS_COMMON_H
mdefine_line|#define _S390_REGS_COMMON_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#endif
DECL|macro|REGISTER_SIZE
mdefine_line|#define REGISTER_SIZE 4
DECL|macro|NUM_GPRS
mdefine_line|#define NUM_GPRS      16
DECL|macro|GPR_SIZE
mdefine_line|#define GPR_SIZE      4
DECL|macro|PSW_MASK_SIZE
mdefine_line|#define PSW_MASK_SIZE 4
DECL|macro|PSW_ADDR_SIZE
mdefine_line|#define PSW_ADDR_SIZE 4
DECL|macro|NUM_FPRS
mdefine_line|#define NUM_FPRS      16
DECL|macro|FPR_SIZE
mdefine_line|#define FPR_SIZE      8
DECL|macro|FPC_SIZE
mdefine_line|#define FPC_SIZE      4
DECL|macro|FPC_PAD_SIZE
mdefine_line|#define FPC_PAD_SIZE  4 /* gcc insists on aligning the fpregs */
DECL|macro|NUM_CRS
mdefine_line|#define NUM_CRS       16
DECL|macro|CR_SIZE
mdefine_line|#define CR_SIZE       4
DECL|macro|NUM_ACRS
mdefine_line|#define NUM_ACRS      16
DECL|macro|ACR_SIZE
mdefine_line|#define ACR_SIZE      4
DECL|macro|STACK_FRAME_OVERHEAD
mdefine_line|#define STACK_FRAME_OVERHEAD    96      /* size of minimum stack frame */
macro_line|#ifndef __ASSEMBLY__
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
DECL|typedef|gpr_t
r_typedef
id|__u32
id|gpr_t
suffix:semicolon
multiline_comment|/* 2 __u32&squot;s are used for floats instead to compile  with a __STRICT_ANSI__ defined */
r_typedef
r_union
(brace
macro_line|#ifdef __KERNEL__ 
DECL|member|d
id|__u64
id|d
suffix:semicolon
multiline_comment|/* mathemu.h gets upset otherwise */
macro_line|#else
r_float
id|d
suffix:semicolon
multiline_comment|/* ansi c dosen&squot;t like long longs &amp; make sure that */
multiline_comment|/* alignments are identical for both compiles */
macro_line|#endif
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
DECL|member|f
id|__u32
id|f
suffix:semicolon
DECL|typedef|freg_t
)brace
id|freg_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/*&n;  The compiler appears to like aligning freg_t on an 8 byte boundary&n;  so I always access fpregs, this was causing fun when I was doing&n;  coersions.&n; */
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
multiline_comment|/*&n;  gdb structures &amp; the kernel have this much always in common&n; */
DECL|macro|S390_REGS_COMMON
mdefine_line|#define S390_REGS_COMMON       &bslash;&n;psw_t psw;                     &bslash;&n;__u32 gprs[NUM_GPRS];          &bslash;&n;__u32  acrs[NUM_ACRS];         &bslash;&n;
r_typedef
r_struct
(brace
id|S390_REGS_COMMON
DECL|typedef|s390_regs_common
)brace
id|s390_regs_common
suffix:semicolon
multiline_comment|/* Sequence of bytes for breakpoint illegal instruction.  */
DECL|macro|S390_BREAKPOINT
mdefine_line|#define S390_BREAKPOINT {0x0,0x1}
DECL|macro|S390_BREAKPOINT_U16
mdefine_line|#define S390_BREAKPOINT_U16 ((__u16)0x0001)
DECL|macro|S390_SYSCALL_OPCODE
mdefine_line|#define S390_SYSCALL_OPCODE ((__u16)0x0a00)
DECL|macro|S390_SYSCALL_SIZE
mdefine_line|#define S390_SYSCALL_SIZE   2
DECL|macro|ADDR_BITS_REMOVE
mdefine_line|#define ADDR_BITS_REMOVE(addr) ((addr)&amp;0x7fffffff)
macro_line|#endif
macro_line|#endif
eof
