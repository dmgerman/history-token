multiline_comment|/*&n; *  include/asm-s390/sigcontext.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; */
macro_line|#ifndef _ASM_S390_SIGCONTEXT_H
DECL|macro|_ASM_S390_SIGCONTEXT_H
mdefine_line|#define _ASM_S390_SIGCONTEXT_H
macro_line|#include &lt;asm/s390-regs-common.h&gt;
multiline_comment|/*&n;  Has to be at least _NSIG_WORDS from asm/signal.h&n; */
DECL|macro|_SIGCONTEXT_NSIG
mdefine_line|#define _SIGCONTEXT_NSIG      64
DECL|macro|_SIGCONTEXT_NSIG_BPW
mdefine_line|#define _SIGCONTEXT_NSIG_BPW  32
multiline_comment|/* Size of stack frame allocated when calling signal handler. */
DECL|macro|__SIGNAL_FRAMESIZE
mdefine_line|#define __SIGNAL_FRAMESIZE      STACK_FRAME_OVERHEAD
DECL|macro|_SIGCONTEXT_NSIG_WORDS
mdefine_line|#define _SIGCONTEXT_NSIG_WORDS  (_SIGCONTEXT_NSIG / _SIGCONTEXT_NSIG_BPW)
DECL|macro|SIGMASK_COPY_SIZE
mdefine_line|#define SIGMASK_COPY_SIZE       (sizeof(unsigned long)*_SIGCONTEXT_NSIG_WORDS)
r_typedef
r_struct
(brace
DECL|member|regs
id|s390_regs_common
id|regs
suffix:semicolon
DECL|member|fpregs
id|s390_fp_regs
id|fpregs
suffix:semicolon
DECL|typedef|sigregs
)brace
id|sigregs
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
id|sigregs
op_star
id|sregs
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
