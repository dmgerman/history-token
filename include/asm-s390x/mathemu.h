multiline_comment|/*&n; *  arch/s390/kernel/mathemu.h&n; *    IEEE floating point emulation.&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; */
macro_line|#ifndef __MATHEMU__
DECL|macro|__MATHEMU__
mdefine_line|#define __MATHEMU__
r_extern
r_int
id|math_emu_b3
c_func
(paren
id|__u8
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|math_emu_ed
c_func
(paren
id|__u8
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|math_emu_ldr
c_func
(paren
id|__u8
op_star
)paren
suffix:semicolon
r_extern
r_void
id|math_emu_ler
c_func
(paren
id|__u8
op_star
)paren
suffix:semicolon
r_extern
r_void
id|math_emu_std
c_func
(paren
id|__u8
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|math_emu_ld
c_func
(paren
id|__u8
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|math_emu_ste
c_func
(paren
id|__u8
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|math_emu_le
c_func
(paren
id|__u8
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|math_emu_lfpc
c_func
(paren
id|__u8
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|math_emu_stfpc
c_func
(paren
id|__u8
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|math_emu_srnm
c_func
(paren
id|__u8
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
id|__u64
id|__adddf3
c_func
(paren
id|__u64
comma
id|__u64
)paren
suffix:semicolon
r_extern
id|__u64
id|__subdf3
c_func
(paren
id|__u64
comma
id|__u64
)paren
suffix:semicolon
r_extern
id|__u64
id|__muldf3
c_func
(paren
id|__u64
comma
id|__u64
)paren
suffix:semicolon
r_extern
id|__u64
id|__divdf3
c_func
(paren
id|__u64
comma
id|__u64
)paren
suffix:semicolon
r_extern
r_int
id|__cmpdf2
c_func
(paren
id|__u64
comma
id|__u64
)paren
suffix:semicolon
r_extern
id|__u64
id|__negdf2
c_func
(paren
id|__u64
)paren
suffix:semicolon
r_extern
id|__u64
id|__absdf2
c_func
(paren
id|__u64
)paren
suffix:semicolon
r_extern
id|__u32
id|__addsf3
c_func
(paren
id|__u32
comma
id|__u32
)paren
suffix:semicolon
r_extern
id|__u32
id|__subsf3
c_func
(paren
id|__u32
comma
id|__u32
)paren
suffix:semicolon
r_extern
id|__u32
id|__mulsf3
c_func
(paren
id|__u32
comma
id|__u32
)paren
suffix:semicolon
r_extern
id|__u32
id|__divsf3
c_func
(paren
id|__u32
comma
id|__u32
)paren
suffix:semicolon
r_extern
id|__u32
id|__negsf2
c_func
(paren
id|__u32
)paren
suffix:semicolon
r_extern
id|__u32
id|__abssf2
c_func
(paren
id|__u32
)paren
suffix:semicolon
r_extern
r_int
id|__cmpsf2
c_func
(paren
id|__u32
comma
id|__u32
)paren
suffix:semicolon
r_extern
id|__u32
id|__truncdfsf2
c_func
(paren
id|__u64
)paren
suffix:semicolon
r_extern
id|__u32
id|__fixsfsi
c_func
(paren
id|__u32
)paren
suffix:semicolon
r_extern
id|__u32
id|__fixdfsi
c_func
(paren
id|__u64
)paren
suffix:semicolon
r_extern
id|__u64
id|__floatsidf
c_func
(paren
id|__u32
)paren
suffix:semicolon
r_extern
id|__u32
id|__floatsisf
c_func
(paren
id|__u32
)paren
suffix:semicolon
r_extern
id|__u64
id|__extendsfdf2
c_func
(paren
id|__u32
)paren
suffix:semicolon
macro_line|#endif                                 /* __MATHEMU__                      */
eof
