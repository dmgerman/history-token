macro_line|#ifndef _ASM_X86_64_SIGCONTEXT_H
DECL|macro|_ASM_X86_64_SIGCONTEXT_H
mdefine_line|#define _ASM_X86_64_SIGCONTEXT_H
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * The first part of &quot;struct _fpstate&quot; is just the normal i387&n; * hardware setup, the extra &quot;status&quot; word is used to save the&n; * coprocessor status word before entering the handler.&n; *&n; * Pentium III FXSR, SSE support&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; *&n; * The FPU state data structure has had to grow to accomodate the&n; * extended FPU state required by the Streaming SIMD Extensions.&n; * There is no documented standard to accomplish this at the moment.&n; */
DECL|struct|_fpreg
r_struct
id|_fpreg
(brace
DECL|member|significand
r_int
r_int
id|significand
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|exponent
r_int
r_int
id|exponent
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_fpxreg
r_struct
id|_fpxreg
(brace
DECL|member|significand
r_int
r_int
id|significand
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|exponent
r_int
r_int
id|exponent
suffix:semicolon
DECL|member|padding
r_int
r_int
id|padding
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_xmmreg
r_struct
id|_xmmreg
(brace
DECL|member|element
id|__u32
id|element
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is FXSAVE layout without 64bit prefix thus 32bit compatible. &n;   This means that the IP and DPs are only 32bit and are not useful&n;   in 64bit space.&n;   If someone used them we would need to switch to 64bit FXSAVE.   &n;*/
DECL|struct|_fpstate
r_struct
id|_fpstate
(brace
multiline_comment|/* Regular FPU environment */
DECL|member|cw
id|__u32
id|cw
suffix:semicolon
DECL|member|sw
id|__u32
id|sw
suffix:semicolon
DECL|member|tag
id|__u32
id|tag
suffix:semicolon
DECL|member|ipoff
id|__u32
id|ipoff
suffix:semicolon
DECL|member|cssel
id|__u32
id|cssel
suffix:semicolon
DECL|member|dataoff
id|__u32
id|dataoff
suffix:semicolon
DECL|member|datasel
id|__u32
id|datasel
suffix:semicolon
DECL|member|_st
r_struct
id|_fpreg
id|_st
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* 0xffff = regular FPU data only */
multiline_comment|/* FXSR FPU environment */
DECL|member|_fxsr_env
id|__u32
id|_fxsr_env
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|mxcsr
id|__u32
id|mxcsr
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
suffix:semicolon
DECL|member|_fxsr_st
r_struct
id|_fpxreg
id|_fxsr_st
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|_xmm
r_struct
id|_xmmreg
id|_xmm
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* It&squot;s actually 16 */
DECL|member|padding
id|__u32
id|padding
(braket
l_int|56
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|X86_FXSR_MAGIC
mdefine_line|#define X86_FXSR_MAGIC&t;&t;0x0000
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|gs
DECL|member|__gsh
r_int
r_int
id|gs
comma
id|__gsh
suffix:semicolon
DECL|member|fs
DECL|member|__fsh
r_int
r_int
id|fs
comma
id|__fsh
suffix:semicolon
DECL|member|es
DECL|member|__esh
r_int
r_int
id|es
comma
id|__esh
suffix:semicolon
DECL|member|ds
DECL|member|__dsh
r_int
r_int
id|ds
comma
id|__dsh
suffix:semicolon
DECL|member|r8
r_int
r_int
id|r8
suffix:semicolon
DECL|member|r9
r_int
r_int
id|r9
suffix:semicolon
DECL|member|r10
r_int
r_int
id|r10
suffix:semicolon
DECL|member|r12
r_int
r_int
id|r12
suffix:semicolon
DECL|member|r13
r_int
r_int
id|r13
suffix:semicolon
DECL|member|r14
r_int
r_int
id|r14
suffix:semicolon
DECL|member|r15
r_int
r_int
id|r15
suffix:semicolon
DECL|member|rdi
r_int
r_int
id|rdi
suffix:semicolon
DECL|member|rsi
r_int
r_int
id|rsi
suffix:semicolon
DECL|member|rbp
r_int
r_int
id|rbp
suffix:semicolon
DECL|member|rbx
r_int
r_int
id|rbx
suffix:semicolon
DECL|member|rdx
r_int
r_int
id|rdx
suffix:semicolon
DECL|member|rax
r_int
r_int
id|rax
suffix:semicolon
DECL|member|trapno
r_int
r_int
id|trapno
suffix:semicolon
DECL|member|err
r_int
r_int
id|err
suffix:semicolon
DECL|member|rip
r_int
r_int
id|rip
suffix:semicolon
DECL|member|cs
DECL|member|__csh
r_int
r_int
id|cs
comma
id|__csh
suffix:semicolon
DECL|member|__pad0
r_int
r_int
id|__pad0
suffix:semicolon
DECL|member|eflags
r_int
r_int
id|eflags
suffix:semicolon
DECL|member|rsp_at_signal
r_int
r_int
id|rsp_at_signal
suffix:semicolon
DECL|member|fpstate
r_struct
id|_fpstate
op_star
id|fpstate
suffix:semicolon
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
DECL|member|cr2
r_int
r_int
id|cr2
suffix:semicolon
DECL|member|r11
r_int
r_int
id|r11
suffix:semicolon
DECL|member|rcx
r_int
r_int
id|rcx
suffix:semicolon
DECL|member|rsp
r_int
r_int
id|rsp
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof