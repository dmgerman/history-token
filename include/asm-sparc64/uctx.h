multiline_comment|/* $Id: uctx.h,v 1.1 1997/06/18 16:51:58 davem Exp $&n; * uctx.h: Sparc64 {set,get}context() register state layouts.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_UCTX_H
DECL|macro|__SPARC64_UCTX_H
mdefine_line|#define __SPARC64_UCTX_H
DECL|macro|MC_TSTATE
mdefine_line|#define MC_TSTATE&t;0
DECL|macro|MC_PC
mdefine_line|#define MC_PC&t;&t;1
DECL|macro|MC_NPC
mdefine_line|#define MC_NPC&t;&t;2
DECL|macro|MC_Y
mdefine_line|#define MC_Y&t;&t;3
DECL|macro|MC_G1
mdefine_line|#define MC_G1&t;&t;4
DECL|macro|MC_G2
mdefine_line|#define MC_G2&t;&t;5
DECL|macro|MC_G3
mdefine_line|#define MC_G3&t;&t;6
DECL|macro|MC_G4
mdefine_line|#define MC_G4&t;&t;7
DECL|macro|MC_G5
mdefine_line|#define MC_G5&t;&t;8
DECL|macro|MC_G6
mdefine_line|#define MC_G6&t;&t;9
DECL|macro|MC_G7
mdefine_line|#define MC_G7&t;&t;10
DECL|macro|MC_O0
mdefine_line|#define MC_O0&t;&t;11
DECL|macro|MC_O1
mdefine_line|#define MC_O1&t;&t;12
DECL|macro|MC_O2
mdefine_line|#define MC_O2&t;&t;13
DECL|macro|MC_O3
mdefine_line|#define MC_O3&t;&t;14
DECL|macro|MC_O4
mdefine_line|#define MC_O4&t;&t;15
DECL|macro|MC_O5
mdefine_line|#define MC_O5&t;&t;16
DECL|macro|MC_O6
mdefine_line|#define MC_O6&t;&t;17
DECL|macro|MC_O7
mdefine_line|#define MC_O7&t;&t;18
DECL|macro|MC_NGREG
mdefine_line|#define MC_NGREG&t;19
DECL|typedef|mc_greg_t
r_typedef
r_int
r_int
id|mc_greg_t
suffix:semicolon
DECL|typedef|mc_gregset_t
r_typedef
id|mc_greg_t
id|mc_gregset_t
(braket
id|MC_NGREG
)braket
suffix:semicolon
DECL|macro|MC_MAXFPQ
mdefine_line|#define MC_MAXFPQ&t;16
DECL|struct|mc_fq
r_struct
id|mc_fq
(brace
DECL|member|mcfq_addr
r_int
r_int
op_star
id|mcfq_addr
suffix:semicolon
DECL|member|mcfq_insn
r_int
r_int
id|mcfq_insn
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mc_fpu
r_struct
id|mc_fpu
(brace
r_union
(brace
DECL|member|sregs
r_int
r_int
id|sregs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|dregs
r_int
r_int
id|dregs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|qregs
r_int
r_float
id|qregs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|mcfpu_fregs
)brace
id|mcfpu_fregs
suffix:semicolon
DECL|member|mcfpu_fsr
r_int
r_int
id|mcfpu_fsr
suffix:semicolon
DECL|member|mcfpu_fprs
r_int
r_int
id|mcfpu_fprs
suffix:semicolon
DECL|member|mcfpu_gsr
r_int
r_int
id|mcfpu_gsr
suffix:semicolon
DECL|member|mcfpu_fq
r_struct
id|mc_fq
op_star
id|mcfpu_fq
suffix:semicolon
DECL|member|mcfpu_qcnt
r_int
r_char
id|mcfpu_qcnt
suffix:semicolon
DECL|member|mcfpu_qentsz
r_int
r_char
id|mcfpu_qentsz
suffix:semicolon
DECL|member|mcfpu_enab
r_int
r_char
id|mcfpu_enab
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|mc_fpu_t
r_typedef
r_struct
id|mc_fpu
id|mc_fpu_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|mc_gregs
id|mc_gregset_t
id|mc_gregs
suffix:semicolon
DECL|member|mc_fp
id|mc_greg_t
id|mc_fp
suffix:semicolon
DECL|member|mc_i7
id|mc_greg_t
id|mc_i7
suffix:semicolon
DECL|member|mc_fpregs
id|mc_fpu_t
id|mc_fpregs
suffix:semicolon
DECL|typedef|mcontext_t
)brace
id|mcontext_t
suffix:semicolon
DECL|struct|ucontext
r_struct
id|ucontext
(brace
DECL|member|uc_link
r_struct
id|ucontext
op_star
id|uc_link
suffix:semicolon
DECL|member|uc_flags
r_int
r_int
id|uc_flags
suffix:semicolon
DECL|member|uc_sigmask
id|sigset_t
id|uc_sigmask
suffix:semicolon
DECL|member|uc_mcontext
id|mcontext_t
id|uc_mcontext
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|ucontext_t
r_typedef
r_struct
id|ucontext
id|ucontext_t
suffix:semicolon
macro_line|#endif /* __SPARC64_UCTX_H */
eof
