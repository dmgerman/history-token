macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt; 
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; *&t;MMX 3DNow! library helper functions&n; *&n; *&t;To do:&n; *&t;We can use MMX just for prefetch in IRQ&squot;s. This may be a win. &n; *&t;&t;(reported so on K6-III)&n; *&t;We should use a better code neutral filler for the short jump&n; *&t;&t;leal ebx. [ebx] is apparently best for K6-2, but Cyrix ??&n; *&t;We also want to clobber the filler register so we dont get any&n; *&t;&t;register forwarding stalls on the filler. &n; *&n; *&t;Add *user handling. Checksums are not a win with MMX on any CPU&n; *&t;tested so far for any MMX solution figured.&n; *&n; *&t;22/09/2000 - Arjan van de Ven &n; *&t;&t;Improved for non-egineering-sample Athlons &n; *&n; *&t;2002 Andi Kleen. Some cleanups and changes for x86-64. &n; *&t;Not really tuned yet. Using the Athlon version for now.&n; *      This currenly uses MMX for 8 byte stores, but on hammer we could&n; *      use integer 8 byte stores too and avoid the FPU save overhead.&n; *&t;Disadvantage is that the integer load/stores have strong ordering&n; *&t;model and may be slower.&n; * &n; *&t;$Id$&n; */
macro_line|#ifdef MMX_MEMCPY_THRESH
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
suffix:semicolon
r_int
id|i
suffix:semicolon
id|p
op_assign
id|to
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
)paren
r_goto
id|standard
suffix:semicolon
multiline_comment|/* XXX: check if this is still memory bound with unaligned to/from.&n;&t;   if not align them here to 8bytes. */
id|i
op_assign
id|len
op_rshift
l_int|6
suffix:semicolon
multiline_comment|/* len/64 */
id|kernel_fpu_begin
c_func
(paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;   prefetch (%0)&bslash;n&quot;
multiline_comment|/* This set is 28 bytes */
l_string|&quot;   prefetch 64(%0)&bslash;n&quot;
l_string|&quot;   prefetch 128(%0)&bslash;n&quot;
l_string|&quot;   prefetch 192(%0)&bslash;n&quot;
l_string|&quot;   prefetch 256(%0)&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
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
l_int|5
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;  prefetch 320(%0)&bslash;n&quot;
l_string|&quot;  movq (%0), %%mm0&bslash;n&quot;
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
l_string|&quot;  movq (%0), %%mm0&bslash;n&quot;
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
id|len
op_and_assign
l_int|63
suffix:semicolon
id|kernel_fpu_end
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Now do the tail of the block&n;&t; */
id|standard
suffix:colon
id|__inline_memcpy
c_func
(paren
id|to
comma
id|from
comma
id|len
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
macro_line|#endif
DECL|function|fast_clear_page
r_static
r_inline
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
id|kernel_fpu_begin
c_func
(paren
)paren
suffix:semicolon
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
id|kernel_fpu_end
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fast_copy_page
r_static
r_inline
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
id|kernel_fpu_begin
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* maybe the prefetch stuff can go before the expensive fnsave...&n;&t; * but that is for later. -AV&n;&t; */
id|__asm__
id|__volatile__
(paren
l_string|&quot;   prefetch (%0)&bslash;n&quot;
l_string|&quot;   prefetch 64(%0)&bslash;n&quot;
l_string|&quot;   prefetch 128(%0)&bslash;n&quot;
l_string|&quot;   prefetch 192(%0)&bslash;n&quot;
l_string|&quot;   prefetch 256(%0)&bslash;n&quot;
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
(paren
l_int|4096
op_minus
l_int|320
)paren
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
l_string|&quot;   prefetch 320(%0)&bslash;n&quot;
l_string|&quot;   movq (%0), %%mm0&bslash;n&quot;
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
r_for
c_loop
(paren
id|i
op_assign
(paren
l_int|4096
op_minus
l_int|320
)paren
op_div
l_int|64
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
id|kernel_fpu_end
c_func
(paren
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
macro_line|#if 1 
id|__builtin_memset
c_func
(paren
id|page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* AK: these in_interrupt checks should not be needed. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
)paren
(brace
id|__builtin_memset
c_func
(paren
id|page
comma
l_int|0
comma
id|PAGE_SIZE
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
macro_line|#endif
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
macro_line|#if 1
id|__builtin_memcpy
c_func
(paren
id|to
comma
id|from
comma
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* AK: these in_interrupt checks should not be needed. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
)paren
(brace
id|__builtin_memcpy
c_func
(paren
id|to
comma
id|from
comma
id|PAGE_SIZE
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
macro_line|#endif
)brace
eof
