macro_line|#ifndef _ASMi386_SIGCONTEXT_H
DECL|macro|_ASMi386_SIGCONTEXT_H
mdefine_line|#define _ASMi386_SIGCONTEXT_H
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/*&n; * As documented in the iBCS2 standard..&n; *&n; * The first part of &quot;struct _fpstate&quot; is just the normal i387&n; * hardware setup, the extra &quot;status&quot; word is used to save the&n; * coprocessor status word before entering the handler.&n; *&n; * Pentium III FXSR, SSE support&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; *&n; * The FPU state data structure has had to grow to accommodate the&n; * extended FPU state required by the Streaming SIMD Extensions.&n; * There is no documented standard to accomplish this at the moment.&n; */
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
r_int
r_int
id|element
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_fpstate
r_struct
id|_fpstate
(brace
multiline_comment|/* Regular FPU environment */
DECL|member|cw
r_int
r_int
id|cw
suffix:semicolon
DECL|member|sw
r_int
r_int
id|sw
suffix:semicolon
DECL|member|tag
r_int
r_int
id|tag
suffix:semicolon
DECL|member|ipoff
r_int
r_int
id|ipoff
suffix:semicolon
DECL|member|cssel
r_int
r_int
id|cssel
suffix:semicolon
DECL|member|dataoff
r_int
r_int
id|dataoff
suffix:semicolon
DECL|member|datasel
r_int
r_int
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
r_int
r_int
id|_fxsr_env
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* FXSR FPU env is ignored */
DECL|member|mxcsr
r_int
r_int
id|mxcsr
suffix:semicolon
DECL|member|reserved
r_int
r_int
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
multiline_comment|/* FXSR FPU reg data is ignored */
DECL|member|_xmm
r_struct
id|_xmmreg
id|_xmm
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|padding
r_int
r_int
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
DECL|member|edi
r_int
r_int
id|edi
suffix:semicolon
DECL|member|esi
r_int
r_int
id|esi
suffix:semicolon
DECL|member|ebp
r_int
r_int
id|ebp
suffix:semicolon
DECL|member|esp
r_int
r_int
id|esp
suffix:semicolon
DECL|member|ebx
r_int
r_int
id|ebx
suffix:semicolon
DECL|member|edx
r_int
r_int
id|edx
suffix:semicolon
DECL|member|ecx
r_int
r_int
id|ecx
suffix:semicolon
DECL|member|eax
r_int
r_int
id|eax
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
DECL|member|eip
r_int
r_int
id|eip
suffix:semicolon
DECL|member|cs
DECL|member|__csh
r_int
r_int
id|cs
comma
id|__csh
suffix:semicolon
DECL|member|eflags
r_int
r_int
id|eflags
suffix:semicolon
DECL|member|esp_at_signal
r_int
r_int
id|esp_at_signal
suffix:semicolon
DECL|member|ss
DECL|member|__ssh
r_int
r_int
id|ss
comma
id|__ssh
suffix:semicolon
DECL|member|fpstate
r_struct
id|_fpstate
id|__user
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
)brace
suffix:semicolon
macro_line|#endif
eof
