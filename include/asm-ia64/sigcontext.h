macro_line|#ifndef _ASM_IA64_SIGCONTEXT_H
DECL|macro|_ASM_IA64_SIGCONTEXT_H
mdefine_line|#define _ASM_IA64_SIGCONTEXT_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999, 2001 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999, 2001 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/fpu.h&gt;
DECL|macro|IA64_SC_FLAG_ONSTACK_BIT
mdefine_line|#define IA64_SC_FLAG_ONSTACK_BIT&t;&t;0&t;/* is handler running on signal stack? */
DECL|macro|IA64_SC_FLAG_IN_SYSCALL_BIT
mdefine_line|#define IA64_SC_FLAG_IN_SYSCALL_BIT&t;&t;1&t;/* did signal interrupt a syscall? */
DECL|macro|IA64_SC_FLAG_FPH_VALID_BIT
mdefine_line|#define IA64_SC_FLAG_FPH_VALID_BIT&t;&t;2&t;/* is state in f[32]-f[127] valid? */
DECL|macro|IA64_SC_FLAG_ONSTACK
mdefine_line|#define IA64_SC_FLAG_ONSTACK&t;&t;(1 &lt;&lt; IA64_SC_FLAG_ONSTACK_BIT)
DECL|macro|IA64_SC_FLAG_IN_SYSCALL
mdefine_line|#define IA64_SC_FLAG_IN_SYSCALL&t;&t;(1 &lt;&lt; IA64_SC_FLAG_IN_SYSCALL_BIT)
DECL|macro|IA64_SC_FLAG_FPH_VALID
mdefine_line|#define IA64_SC_FLAG_FPH_VALID&t;&t;(1 &lt;&lt; IA64_SC_FLAG_FPH_VALID_BIT)
macro_line|# ifndef __ASSEMBLY__
multiline_comment|/*&n; * Note on handling of register backing store: sc_ar_bsp contains the address that would&n; * be found in ar.bsp after executing a &quot;cover&quot; instruction the context in which the&n; * signal was raised.  If signal delivery required switching to an alternate signal stack&n; * (sc_rbs_base is not NULL), the &quot;dirty&quot; partition (as it would exist after executing the&n; * imaginary &quot;cover&quot; instruction) is backed by the *alternate* signal stack, not the&n; * original one.  In this case, sc_rbs_base contains the base address of the new register&n; * backing store.  The number of registers in the dirty partition can be calculated as:&n; *&n; *   ndirty = ia64_rse_num_regs(sc_rbs_base, sc_rbs_base + (sc_loadrs &gt;&gt; 16))&n; *&n; */
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|sc_flags
r_int
r_int
id|sc_flags
suffix:semicolon
multiline_comment|/* see manifest constants above */
DECL|member|sc_nat
r_int
r_int
id|sc_nat
suffix:semicolon
multiline_comment|/* bit i == 1 iff scratch reg gr[i] is a NaT */
DECL|member|sc_stack
id|stack_t
id|sc_stack
suffix:semicolon
multiline_comment|/* previously active stack */
DECL|member|sc_ip
r_int
r_int
id|sc_ip
suffix:semicolon
multiline_comment|/* instruction pointer */
DECL|member|sc_cfm
r_int
r_int
id|sc_cfm
suffix:semicolon
multiline_comment|/* current frame marker */
DECL|member|sc_um
r_int
r_int
id|sc_um
suffix:semicolon
multiline_comment|/* user mask bits */
DECL|member|sc_ar_rsc
r_int
r_int
id|sc_ar_rsc
suffix:semicolon
multiline_comment|/* register stack configuration register */
DECL|member|sc_ar_bsp
r_int
r_int
id|sc_ar_bsp
suffix:semicolon
multiline_comment|/* backing store pointer */
DECL|member|sc_ar_rnat
r_int
r_int
id|sc_ar_rnat
suffix:semicolon
multiline_comment|/* RSE NaT collection register */
DECL|member|sc_ar_ccv
r_int
r_int
id|sc_ar_ccv
suffix:semicolon
multiline_comment|/* compare and exchange compare value register */
DECL|member|sc_ar_unat
r_int
r_int
id|sc_ar_unat
suffix:semicolon
multiline_comment|/* ar.unat of interrupted context */
DECL|member|sc_ar_fpsr
r_int
r_int
id|sc_ar_fpsr
suffix:semicolon
multiline_comment|/* floating-point status register */
DECL|member|sc_ar_pfs
r_int
r_int
id|sc_ar_pfs
suffix:semicolon
multiline_comment|/* previous function state */
DECL|member|sc_ar_lc
r_int
r_int
id|sc_ar_lc
suffix:semicolon
multiline_comment|/* loop count register */
DECL|member|sc_pr
r_int
r_int
id|sc_pr
suffix:semicolon
multiline_comment|/* predicate registers */
DECL|member|sc_br
r_int
r_int
id|sc_br
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* branch registers */
multiline_comment|/* Note: sc_gr[0] is used as the &quot;uc_link&quot; member of ucontext_t */
DECL|member|sc_gr
r_int
r_int
id|sc_gr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* general registers (static partition) */
DECL|member|sc_fr
r_struct
id|ia64_fpreg
id|sc_fr
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* floating-point registers */
DECL|member|sc_rbs_base
r_int
r_int
id|sc_rbs_base
suffix:semicolon
multiline_comment|/* NULL or new base of sighandler&squot;s rbs */
DECL|member|sc_loadrs
r_int
r_int
id|sc_loadrs
suffix:semicolon
multiline_comment|/* see description above */
DECL|member|sc_ar25
r_int
r_int
id|sc_ar25
suffix:semicolon
multiline_comment|/* rsvd for scratch use */
DECL|member|sc_ar26
r_int
r_int
id|sc_ar26
suffix:semicolon
multiline_comment|/* rsvd for scratch use */
DECL|member|sc_rsvd
r_int
r_int
id|sc_rsvd
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
multiline_comment|/*&n;&t; * The mask must come last so we can increase _NSIG_WORDS&n;&t; * without breaking binary compatibility.&n;&t; */
DECL|member|sc_mask
id|sigset_t
id|sc_mask
suffix:semicolon
multiline_comment|/* signal mask to restore after handler returns */
)brace
suffix:semicolon
macro_line|# endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_SIGCONTEXT_H */
eof
