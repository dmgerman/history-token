macro_line|#include&lt;linux/compat.h&gt;
macro_line|#include&lt;linux/compat_siginfo.h&gt;
macro_line|#include&lt;asm/compat_ucontext.h&gt;
macro_line|#ifndef _ASM_PARISC_COMPAT_RT_SIGFRAME_H
DECL|macro|_ASM_PARISC_COMPAT_RT_SIGFRAME_H
mdefine_line|#define _ASM_PARISC_COMPAT_RT_SIGFRAME_H
multiline_comment|/* In a deft move of uber-hackery, we decide to carry the top half of all&n; * 64-bit registers in a non-portable, non-ABI, hidden structure.&n; * Userspace can read the hidden structure if it *wants* but is never&n; * guaranteed to be in the same place. Infact the uc_sigmask from the &n; * ucontext_t structure may push the hidden register file downards&n; */
DECL|struct|compat_regfile
r_struct
id|compat_regfile
(brace
multiline_comment|/* Upper half of all the 64-bit registers that were truncated&n;&t;   on a copy to a 32-bit userspace */
DECL|member|rf_gr
id|compat_int_t
id|rf_gr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|rf_iasq
id|compat_int_t
id|rf_iasq
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|rf_iaoq
id|compat_int_t
id|rf_iaoq
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|rf_sar
id|compat_int_t
id|rf_sar
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|COMPAT_SIGRETURN_TRAMP
mdefine_line|#define COMPAT_SIGRETURN_TRAMP 4
DECL|macro|COMPAT_SIGRESTARTBLOCK_TRAMP
mdefine_line|#define COMPAT_SIGRESTARTBLOCK_TRAMP 5 
DECL|macro|COMPAT_TRAMP_SIZE
mdefine_line|#define COMPAT_TRAMP_SIZE (COMPAT_SIGRETURN_TRAMP + COMPAT_SIGRESTARTBLOCK_TRAMP)
DECL|struct|compat_rt_sigframe
r_struct
id|compat_rt_sigframe
(brace
multiline_comment|/* XXX: Must match trampoline size in arch/parisc/kernel/signal.c &n;&t;        Secondary to that it must protect the ERESTART_RESTARTBLOCK&n;&t;&t;trampoline we left on the stack (we were bad and didn&squot;t &n;&t;&t;change sp so we could run really fast.) */
DECL|member|tramp
id|compat_uint_t
id|tramp
(braket
id|COMPAT_TRAMP_SIZE
)braket
suffix:semicolon
DECL|member|info
id|compat_siginfo_t
id|info
suffix:semicolon
DECL|member|uc
r_struct
id|compat_ucontext
id|uc
suffix:semicolon
multiline_comment|/* Hidden location of truncated registers, *must* be last. */
DECL|member|regs
r_struct
id|compat_regfile
id|regs
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The 32-bit ABI wants at least 48 bytes for a function call frame:&n; * 16 bytes for arg0-arg3, and 32 bytes for magic (the only part of&n; * which Linux/parisc uses is sp-20 for the saved return pointer...)&n; * Then, the stack pointer must be rounded to a cache line (64 bytes).&n; */
DECL|macro|SIGFRAME32
mdefine_line|#define SIGFRAME32&t;&t;64
DECL|macro|FUNCTIONCALLFRAME32
mdefine_line|#define FUNCTIONCALLFRAME32&t;48
DECL|macro|PARISC_RT_SIGFRAME_SIZE32
mdefine_line|#define PARISC_RT_SIGFRAME_SIZE32&t;&t;&t;&t;&t;&bslash;&n;&t;(((sizeof(struct compat_rt_sigframe) + FUNCTIONCALLFRAME32) + SIGFRAME32) &amp; -SIGFRAME32)
macro_line|#endif
eof
