macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/*&n; *&t;MMX 3DNow! library helper functions&n; *&n; *&t;To do:&n; *&t;We can use MMX just for prefetch in IRQ&squot;s. This may be a win. &n; *&t;&t;(reported so on K6-III)&n; *&t;We should use a better code neutral filler for the short jump&n; *&t;&t;leal ebx. [ebx] is apparently best for K6-2, but Cyrix ??&n; *&t;We also want to clobber the filler register so we dont get any&n; *&t;&t;register forwarding stalls on the filler. &n; *&n; *&t;Add *user handling. Checksums are not a win with MMX on any CPU&n; *&t;tested so far for any MMX solution figured.&n; *&n; *&t;22/09/2000 - Arjan van de Ven &n; *&t;&t;Improved for non-egineering-sample Athlons &n; *&n; */
DECL|function|_mmx_memcpy
r_void
op_star
id|_mmx_memcpy
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
id|len
)paren
(brace
r_void
op_star
id|p
op_assign
id|to
suffix:semicolon
r_int
id|i
op_assign
id|len
op_rshift
l_int|6
suffix:semicolon
multiline_comment|/* len/64 */
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;flags
op_amp
id|PF_USEDFPU
)paren
)paren
id|clts
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot; fnsave %0; fwait&bslash;n&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|current-&gt;thread.i387
)paren
)paren
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
)brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: prefetch (%0)&bslash;n&quot;
multiline_comment|/* This set is 28 bytes */
l_string|&quot;   prefetch 64(%0)&bslash;n&quot;
l_string|&quot;   prefetch 128(%0)&bslash;n&quot;
l_string|&quot;   prefetch 192(%0)&bslash;n&quot;
l_string|&quot;   prefetch 256(%0)&bslash;n&quot;
l_string|&quot;2:  &bslash;n&quot;
l_string|&quot;.section .fixup, &bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3: movw $0x1AEB, 1b&bslash;n&quot;
multiline_comment|/* jmp on 26 bytes */
l_string|&quot;   jmp 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 1b, 3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|from
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:  prefetch 320(%0)&bslash;n&quot;
l_string|&quot;2:  movq (%0), %%mm0&bslash;n&quot;
l_string|&quot;  movq 8(%0), %%mm1&bslash;n&quot;
l_string|&quot;  movq 16(%0), %%mm2&bslash;n&quot;
l_string|&quot;  movq 24(%0), %%mm3&bslash;n&quot;
l_string|&quot;  movq %%mm0, (%1)&bslash;n&quot;
l_string|&quot;  movq %%mm1, 8(%1)&bslash;n&quot;
l_string|&quot;  movq %%mm2, 16(%1)&bslash;n&quot;
l_string|&quot;  movq %%mm3, 24(%1)&bslash;n&quot;
l_string|&quot;  movq 32(%0), %%mm0&bslash;n&quot;
l_string|&quot;  movq 40(%0), %%mm1&bslash;n&quot;
l_string|&quot;  movq 48(%0), %%mm2&bslash;n&quot;
l_string|&quot;  movq 56(%0), %%mm3&bslash;n&quot;
l_string|&quot;  movq %%mm0, 32(%1)&bslash;n&quot;
l_string|&quot;  movq %%mm1, 40(%1)&bslash;n&quot;
l_string|&quot;  movq %%mm2, 48(%1)&bslash;n&quot;
l_string|&quot;  movq %%mm3, 56(%1)&bslash;n&quot;
l_string|&quot;.section .fixup, &bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3: movw $0x05EB, 1b&bslash;n&quot;
multiline_comment|/* jmp on 5 bytes */
l_string|&quot;   jmp 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 1b, 3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|from
)paren
comma
l_string|&quot;r&quot;
(paren
id|to
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|from
op_add_assign
l_int|64
suffix:semicolon
id|to
op_add_assign
l_int|64
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Now do the tail of the block&n;&t; */
id|__memcpy
c_func
(paren
id|to
comma
id|from
comma
id|len
op_amp
l_int|63
)paren
suffix:semicolon
id|stts
c_func
(paren
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|fast_clear_page
r_static
r_void
id|fast_clear_page
c_func
(paren
r_void
op_star
id|page
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;flags
op_amp
id|PF_USEDFPU
)paren
)paren
id|clts
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot; fnsave %0; fwait&bslash;n&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|current-&gt;thread.i387
)paren
)paren
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
)brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;  pxor %%mm0, %%mm0&bslash;n&quot;
suffix:colon
suffix:colon
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4096
op_div
l_int|64
suffix:semicolon
id|i
op_increment
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;  movntq %%mm0, (%0)&bslash;n&quot;
l_string|&quot;  movntq %%mm0, 8(%0)&bslash;n&quot;
l_string|&quot;  movntq %%mm0, 16(%0)&bslash;n&quot;
l_string|&quot;  movntq %%mm0, 24(%0)&bslash;n&quot;
l_string|&quot;  movntq %%mm0, 32(%0)&bslash;n&quot;
l_string|&quot;  movntq %%mm0, 40(%0)&bslash;n&quot;
l_string|&quot;  movntq %%mm0, 48(%0)&bslash;n&quot;
l_string|&quot;  movntq %%mm0, 56(%0)&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|page
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|page
op_add_assign
l_int|64
suffix:semicolon
)brace
multiline_comment|/* since movntq is weakly-ordered, a &quot;sfence&quot; is needed to become&n;&t; * ordered again.&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;  sfence &bslash;n&quot;
suffix:colon
suffix:colon
)paren
suffix:semicolon
id|stts
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fast_copy_page
r_static
r_void
id|fast_copy_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;flags
op_amp
id|PF_USEDFPU
)paren
)paren
id|clts
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot; fnsave %0; fwait&bslash;n&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|current-&gt;thread.i387
)paren
)paren
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
)brace
multiline_comment|/* maybe the prefetch stuff can go before the expensive fnsave...&n;&t; * but that is for later. -AV&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: prefetch (%0)&bslash;n&quot;
l_string|&quot;   prefetch 64(%0)&bslash;n&quot;
l_string|&quot;   prefetch 128(%0)&bslash;n&quot;
l_string|&quot;   prefetch 192(%0)&bslash;n&quot;
l_string|&quot;   prefetch 256(%0)&bslash;n&quot;
l_string|&quot;2:  &bslash;n&quot;
l_string|&quot;.section .fixup, &bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3: movw $0x1AEB, 1b&bslash;n&quot;
multiline_comment|/* jmp on 26 bytes */
l_string|&quot;   jmp 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 1b, 3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|from
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4096
op_div
l_int|64
suffix:semicolon
id|i
op_increment
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;1: prefetch 320(%0)&bslash;n&quot;
l_string|&quot;2: movq (%0), %%mm0&bslash;n&quot;
l_string|&quot;   movntq %%mm0, (%1)&bslash;n&quot;
l_string|&quot;   movq 8(%0), %%mm1&bslash;n&quot;
l_string|&quot;   movntq %%mm1, 8(%1)&bslash;n&quot;
l_string|&quot;   movq 16(%0), %%mm2&bslash;n&quot;
l_string|&quot;   movntq %%mm2, 16(%1)&bslash;n&quot;
l_string|&quot;   movq 24(%0), %%mm3&bslash;n&quot;
l_string|&quot;   movntq %%mm3, 24(%1)&bslash;n&quot;
l_string|&quot;   movq 32(%0), %%mm4&bslash;n&quot;
l_string|&quot;   movntq %%mm4, 32(%1)&bslash;n&quot;
l_string|&quot;   movq 40(%0), %%mm5&bslash;n&quot;
l_string|&quot;   movntq %%mm5, 40(%1)&bslash;n&quot;
l_string|&quot;   movq 48(%0), %%mm6&bslash;n&quot;
l_string|&quot;   movntq %%mm6, 48(%1)&bslash;n&quot;
l_string|&quot;   movq 56(%0), %%mm7&bslash;n&quot;
l_string|&quot;   movntq %%mm7, 56(%1)&bslash;n&quot;
l_string|&quot;.section .fixup, &bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3: movw $0x05EB, 1b&bslash;n&quot;
multiline_comment|/* jmp on 5 bytes */
l_string|&quot;   jmp 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 1b, 3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|from
)paren
comma
l_string|&quot;r&quot;
(paren
id|to
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|from
op_add_assign
l_int|64
suffix:semicolon
id|to
op_add_assign
l_int|64
suffix:semicolon
)brace
multiline_comment|/* since movntq is weakly-ordered, a &quot;sfence&quot; is needed to become&n;&t; * ordered again.&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;  sfence &bslash;n&quot;
suffix:colon
suffix:colon
)paren
suffix:semicolon
id|stts
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Favour MMX for page clear and copy. &n; */
DECL|function|slow_zero_page
r_static
r_void
id|slow_zero_page
c_func
(paren
r_void
op_star
id|page
)paren
(brace
r_int
id|d0
comma
id|d1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&bslash;"
l_string|&quot;cld&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;rep ; stosl&quot;
"&bslash;"
suffix:colon
l_string|&quot;=&amp;c&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d1
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;1&quot;
(paren
id|page
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|1024
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|mmx_clear_page
r_void
id|mmx_clear_page
c_func
(paren
r_void
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
id|slow_zero_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
id|fast_clear_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|slow_copy_page
r_static
r_void
id|slow_copy_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
(brace
r_int
id|d0
comma
id|d1
comma
id|d2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&bslash;"
l_string|&quot;cld&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;rep ; movsl&quot;
"&bslash;"
suffix:colon
l_string|&quot;=&amp;c&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d1
)paren
comma
l_string|&quot;=&amp;S&quot;
(paren
id|d2
)paren
"&bslash;"
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|1024
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
r_int
)paren
id|to
)paren
comma
l_string|&quot;2&quot;
(paren
(paren
r_int
)paren
id|from
)paren
"&bslash;"
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|mmx_copy_page
r_void
id|mmx_copy_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
(brace
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
id|slow_copy_page
c_func
(paren
id|to
comma
id|from
)paren
suffix:semicolon
)brace
r_else
id|fast_copy_page
c_func
(paren
id|to
comma
id|from
)paren
suffix:semicolon
)brace
eof
