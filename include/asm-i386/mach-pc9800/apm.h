multiline_comment|/*&n; *  include/asm-i386/mach-pc9800/apm.h&n; *&n; *  Machine specific APM BIOS functions for NEC PC9800.&n; *  Split out from apm.c by Osamu Tomita &lt;tomita@cinet.co.jp&gt;&n; */
macro_line|#ifndef _ASM_APM_H
DECL|macro|_ASM_APM_H
mdefine_line|#define _ASM_APM_H
macro_line|#include &lt;linux/apm_bios.h&gt;
macro_line|#ifdef APM_ZERO_SEGS
DECL|macro|APM_DO_ZERO_SEGS
macro_line|#&t;define APM_DO_ZERO_SEGS &bslash;&n;&t;&t;&quot;pushl %%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;pushl %%es&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;xorl %%edx, %%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;mov %%dx, %%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;mov %%dx, %%es&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;mov %%dx, %%fs&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;mov %%dx, %%gs&bslash;n&bslash;t&quot;
DECL|macro|APM_DO_POP_SEGS
macro_line|#&t;define APM_DO_POP_SEGS &bslash;&n;&t;&t;&quot;popl %%es&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;popl %%ds&bslash;n&bslash;t&quot;
macro_line|#else
DECL|macro|APM_DO_ZERO_SEGS
macro_line|#&t;define APM_DO_ZERO_SEGS
DECL|macro|APM_DO_POP_SEGS
macro_line|#&t;define APM_DO_POP_SEGS
macro_line|#endif
DECL|function|apm_bios_call_asm
r_static
r_inline
r_void
id|apm_bios_call_asm
c_func
(paren
id|u32
id|func
comma
id|u32
id|ebx_in
comma
id|u32
id|ecx_in
comma
id|u32
op_star
id|eax
comma
id|u32
op_star
id|ebx
comma
id|u32
op_star
id|ecx
comma
id|u32
op_star
id|edx
comma
id|u32
op_star
id|esi
)paren
(brace
multiline_comment|/*&n;&t; * N.B. We do NOT need a cld after the BIOS call&n;&t; * because we always save and restore the flags.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
id|APM_DO_ZERO_SEGS
l_string|&quot;pushl %%edi&bslash;n&bslash;t&quot;
l_string|&quot;pushl %%ebp&bslash;n&bslash;t&quot;
l_string|&quot;pushfl&bslash;n&bslash;t&quot;
l_string|&quot;lcall *%%cs:apm_bios_entry&bslash;n&bslash;t&quot;
l_string|&quot;setc %%al&bslash;n&bslash;t&quot;
l_string|&quot;popl %%ebp&bslash;n&bslash;t&quot;
l_string|&quot;popl %%edi&bslash;n&bslash;t&quot;
id|APM_DO_POP_SEGS
suffix:colon
l_string|&quot;=a&quot;
(paren
op_star
id|eax
)paren
comma
l_string|&quot;=b&quot;
(paren
op_star
id|ebx
)paren
comma
l_string|&quot;=c&quot;
(paren
op_star
id|ecx
)paren
comma
l_string|&quot;=d&quot;
(paren
op_star
id|edx
)paren
comma
l_string|&quot;=S&quot;
(paren
op_star
id|esi
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|func
)paren
comma
l_string|&quot;b&quot;
(paren
id|ebx_in
)paren
comma
l_string|&quot;c&quot;
(paren
id|ecx_in
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|apm_bios_call_simple_asm
r_static
r_inline
id|u8
id|apm_bios_call_simple_asm
c_func
(paren
id|u32
id|func
comma
id|u32
id|ebx_in
comma
id|u32
id|ecx_in
comma
id|u32
op_star
id|eax
)paren
(brace
r_int
id|cx
comma
id|dx
comma
id|si
suffix:semicolon
id|u8
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * N.B. We do NOT need a cld after the BIOS call&n;&t; * because we always save and restore the flags.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
id|APM_DO_ZERO_SEGS
l_string|&quot;pushl %%edi&bslash;n&bslash;t&quot;
l_string|&quot;pushl %%ebp&bslash;n&bslash;t&quot;
l_string|&quot;pushfl&bslash;n&bslash;t&quot;
l_string|&quot;lcall *%%cs:apm_bios_entry&bslash;n&bslash;t&quot;
l_string|&quot;setc %%bl&bslash;n&bslash;t&quot;
l_string|&quot;popl %%ebp&bslash;n&bslash;t&quot;
l_string|&quot;popl %%edi&bslash;n&bslash;t&quot;
id|APM_DO_POP_SEGS
suffix:colon
l_string|&quot;=a&quot;
(paren
op_star
id|eax
)paren
comma
l_string|&quot;=b&quot;
(paren
id|error
)paren
comma
l_string|&quot;=c&quot;
(paren
id|cx
)paren
comma
l_string|&quot;=d&quot;
(paren
id|dx
)paren
comma
l_string|&quot;=S&quot;
(paren
id|si
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|func
)paren
comma
l_string|&quot;b&quot;
(paren
id|ebx_in
)paren
comma
l_string|&quot;c&quot;
(paren
id|ecx_in
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|func
op_eq
id|APM_FUNC_VERSION
)paren
op_star
id|eax
op_assign
(paren
op_star
id|eax
op_amp
l_int|0xff00
)paren
op_or
(paren
(paren
op_star
id|eax
op_amp
l_int|0x00f0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#endif /* _ASM_APM_H */
eof
