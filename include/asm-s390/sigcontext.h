multiline_comment|/*&n; *  include/asm-s390/sigcontext.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; */
macro_line|#ifndef _ASM_S390_SIGCONTEXT_H
DECL|macro|_ASM_S390_SIGCONTEXT_H
mdefine_line|#define _ASM_S390_SIGCONTEXT_H
DECL|macro|__NUM_GPRS
mdefine_line|#define __NUM_GPRS 16
DECL|macro|__NUM_FPRS
mdefine_line|#define __NUM_FPRS 16
DECL|macro|__NUM_ACRS
mdefine_line|#define __NUM_ACRS 16
multiline_comment|/*&n;  Has to be at least _NSIG_WORDS from asm/signal.h&n; */
DECL|macro|_SIGCONTEXT_NSIG
mdefine_line|#define _SIGCONTEXT_NSIG      64
DECL|macro|_SIGCONTEXT_NSIG_BPW
mdefine_line|#define _SIGCONTEXT_NSIG_BPW  32
multiline_comment|/* Size of stack frame allocated when calling signal handler. */
DECL|macro|__SIGNAL_FRAMESIZE
mdefine_line|#define __SIGNAL_FRAMESIZE&t;96
DECL|macro|_SIGCONTEXT_NSIG_WORDS
mdefine_line|#define _SIGCONTEXT_NSIG_WORDS&t;(_SIGCONTEXT_NSIG / _SIGCONTEXT_NSIG_BPW)
DECL|macro|_SIGMASK_COPY_SIZE
mdefine_line|#define _SIGMASK_COPY_SIZE&t;(sizeof(unsigned long)*_SIGCONTEXT_NSIG_WORDS)
r_typedef
r_struct
(brace
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|typedef|_psw_t
)brace
id|_psw_t
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
r_typedef
r_struct
(brace
DECL|member|psw
id|_psw_t
id|psw
suffix:semicolon
DECL|member|gprs
r_int
r_int
id|gprs
(braket
id|__NUM_GPRS
)braket
suffix:semicolon
DECL|member|acrs
r_int
r_int
id|acrs
(braket
id|__NUM_ACRS
)braket
suffix:semicolon
DECL|typedef|_s390_regs_common
)brace
id|_s390_regs_common
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|fpc
r_int
r_int
id|fpc
suffix:semicolon
DECL|member|fprs
r_float
id|fprs
(braket
id|__NUM_FPRS
)braket
suffix:semicolon
DECL|typedef|_s390_fp_regs
)brace
id|_s390_fp_regs
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|regs
id|_s390_regs_common
id|regs
suffix:semicolon
DECL|member|fpregs
id|_s390_fp_regs
id|fpregs
suffix:semicolon
DECL|typedef|_sigregs
)brace
id|_sigregs
suffix:semicolon
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|oldmask
r_int
r_int
id|oldmask
(braket
id|_SIGCONTEXT_NSIG_WORDS
)braket
suffix:semicolon
DECL|member|sregs
id|_sigregs
op_star
id|sregs
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
