multiline_comment|/*&n; *  Generic function for frame buffer with packed pixels of any depth.&n; *&n; *      Copyright (C)  June 1999 James Simmons&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; *&n; * NOTES:&n; * &n; *  This is for cfb packed pixels. Iplan and such are incorporated in the &n; *  drivers that need them.&n; * &n; *  FIXME&n; *  The code for 24 bit is horrible. It copies byte by byte size instead of &n; *  longs like the other sizes. Needs to be optimized. &n; *&n; *  Also need to add code to deal with cards endians that are different than &n; *  the native cpu endians. I also need to deal with MSB position in the word.&n; *  &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if BITS_PER_LONG == 32
DECL|macro|FB_READ
mdefine_line|#define FB_READ&t;&t;fb_readl
DECL|macro|FB_WRITE
mdefine_line|#define FB_WRITE&t;fb_writel
macro_line|#else
DECL|macro|FB_READ
mdefine_line|#define FB_READ&t;&t;fb_readq
DECL|macro|FB_WRITE
mdefine_line|#define FB_WRITE&t;fb_writeq
macro_line|#endif
multiline_comment|/* &n; * Oh no Assembly code !!!! Expect more to come as the code gets better.&n; * Ideally the assembly code shoudl be split off into its own seperate file &n; */
multiline_comment|/* Those of a delicate disposition might like to skip the next couple of&n; * pages.&n; *&n; * These functions are drop in replacements for memmove and&n; * memset(_, 0, _). However their five instances add at least a kilobyte&n; * to the object file. You have been warned.&n; *&n; * Not a great fan of assembler for the sake of it, but I think&n; * that these routines are at least 10 times faster than their C&n; * equivalents for large blits, and that&squot;s important to the lowest level of&n; * a graphics driver. Question is whether some scheme with the blitter&n; * would be faster. I suspect not for simple text system - not much&n; * asynchrony.&n; *&n; * Code is very simple, just gruesome expansion. Basic strategy is to&n; * increase data moved/cleared at each step to 16 bytes to reduce&n; * instruction per data move overhead. movem might be faster still&n; * For more than 15 bytes, we try to align the write direction on a&n; * longword boundary to get maximum speed. This is even more gruesome.&n; * Unaligned read/write used requires 68020+ - think this is a problem?&n; *&n; * Sorry!&n; */
multiline_comment|/* ++roman: I&squot;ve optimized Robert&squot;s original versions in some minor&n; * aspects, e.g. moveq instead of movel, let gcc choose the registers,&n; * use movem in some places...&n; * For other modes than 1 plane, lots of more such assembler functions&n; * were needed (e.g. the ones using movep or expanding color values).&n; */
macro_line|#if defined(__mc68000__)
multiline_comment|/*&n; * ++andreas: more optimizations:&n; * subl #65536,d0 replaced by clrw d0; subql #1,d0 for dbcc&n; * addal is faster than addaw&n; * movep is rather expensive compared to ordinary move&squot;s&n; * some functions rewritten in C for clarity, no speed loss&n; */
DECL|function|fb_memmove
r_static
id|__inline__
r_void
op_star
id|fb_memmove
c_func
(paren
r_void
op_star
id|d
comma
r_const
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|d
OL
id|s
)paren
(brace
r_if
c_cond
(paren
id|count
OL
l_int|16
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lsrl   #1,%2 ; jcc 1f ; moveb %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movew %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movel %1@+,%0@+ ; movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|d
)paren
comma
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|d
)paren
comma
l_string|&quot;1&quot;
(paren
id|s
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movel  %0,%3&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%3 ; jcc 1f ; moveb %1@+,%0@+ ; subqw #1,%2&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%3 ; jcs 2f&bslash;n&bslash;t&quot;
multiline_comment|/* %0 increased=&gt;bit 2 switched*/
l_string|&quot;movew  %1@+,%0@+  ; subqw  #2,%2 ; jra 2f&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%3 ; jcc 2f&bslash;n&bslash;t&quot;
l_string|&quot;movew  %1@+,%0@+  ; subqw  #2,%2&bslash;n&bslash;t&quot;
l_string|&quot;2: movew  %2,%-; lsrl #2,%2 ; jeq 6f&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%2 ; jcc 3f ; movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;3: lsrl   #1,%2 ; jcc 4f ; movel %1@+,%0@+ ; movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;4: subql  #1,%2 ; jcs 6f&bslash;n&bslash;t&quot;
l_string|&quot;5: movel  %1@+,%0@+;movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;movel  %1@+,%0@+;movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;dbra   %2,5b ; clrw %2; subql #1,%2; jcc 5b&bslash;n&bslash;t&quot;
l_string|&quot;6: movew  %+,%2; btst #1,%2 ; jeq 7f ; movew %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;7:              ; btst #0,%2 ; jeq 8f ; moveb %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;8:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|d
)paren
comma
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|d
)paren
comma
l_string|&quot;1&quot;
(paren
id|s
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|count
OL
l_int|16
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lsrl   #1,%2 ; jcc 1f ; moveb %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movew %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movel %1@-,%0@- ; movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|d
)paren
comma
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
(paren
r_char
op_star
)paren
id|d
op_plus
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
r_char
op_star
)paren
id|s
op_plus
id|count
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movel %0,%3&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%3 ; jcc 1f ; moveb %1@-,%0@- ; subqw #1,%2&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%3 ; jcs 2f&bslash;n&bslash;t&quot;
multiline_comment|/* %0 increased=&gt;bit 2 switched*/
l_string|&quot;movew  %1@-,%0@-  ; subqw  #2,%2 ; jra 2f&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%3 ; jcc 2f&bslash;n&bslash;t&quot;
l_string|&quot;movew  %1@-,%0@-  ; subqw  #2,%2&bslash;n&bslash;t&quot;
l_string|&quot;2: movew %2,%-; lsrl #2,%2 ; jeq 6f&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%2 ; jcc 3f ; movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;3: lsrl   #1,%2 ; jcc 4f ; movel %1@-,%0@- ; movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;4: subql  #1,%2 ; jcs 6f&bslash;n&bslash;t&quot;
l_string|&quot;5: movel %1@-,%0@-;movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;movel %1@-,%0@-;movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;dbra %2,5b ; clrw %2; subql #1,%2; jcc 5b&bslash;n&bslash;t&quot;
l_string|&quot;6: movew %+,%2; btst #1,%2 ; jeq 7f ; movew %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;7:              ; btst #0,%2 ; jeq 8f ; moveb %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;8:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|d
)paren
comma
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
(paren
r_char
op_star
)paren
id|d
op_plus
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
r_char
op_star
)paren
id|s
op_plus
id|count
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ++andreas: Simple and fast version of memmove, assumes size is&n;   divisible by 16, suitable for moving the whole screen bitplane */
DECL|function|fast_memmove
r_static
id|__inline__
r_void
id|fast_memmove
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dst
OL
id|src
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&quot;
l_string|&quot;  moveml %0@+,%/d0/%/d1/%/a0/%/a1&bslash;n&quot;
l_string|&quot;  moveml %/d0/%/d1/%/a0/%/a1,%1@&bslash;n&quot;
l_string|&quot;  addql #8,%1; addql #8,%1&bslash;n&quot;
l_string|&quot;  dbra %2,1b&bslash;n&quot;
l_string|&quot;  clrw %2; subql #1,%2&bslash;n&quot;
l_string|&quot;  jcc 1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=a&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=d&quot;
(paren
id|size
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|src
)paren
comma
l_string|&quot;1&quot;
(paren
id|dst
)paren
comma
l_string|&quot;2&quot;
(paren
id|size
op_div
l_int|16
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;d1&quot;
comma
l_string|&quot;a0&quot;
comma
l_string|&quot;a1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&quot;
l_string|&quot;  subql #8,%0; subql #8,%0&bslash;n&quot;
l_string|&quot;  moveml %0@,%/d0/%/d1/%/a0/%/a1&bslash;n&quot;
l_string|&quot;  moveml %/d0/%/d1/%/a0/%/a1,%1@-&bslash;n&quot;
l_string|&quot;  dbra %2,1b&bslash;n&quot;
l_string|&quot;  clrw %2; subql #1,%2&bslash;n&quot;
l_string|&quot;  jcc 1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=a&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=d&quot;
(paren
id|size
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|src
op_plus
id|size
)paren
comma
l_string|&quot;1&quot;
(paren
id|dst
op_plus
id|size
)paren
comma
l_string|&quot;2&quot;
(paren
id|size
op_div
l_int|16
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;d1&quot;
comma
l_string|&quot;a0&quot;
comma
l_string|&quot;a1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_SUN4)
multiline_comment|/* You may think that I&squot;m crazy and that I should use generic&n;   routines.  No, I&squot;m not: sun4&squot;s framebuffer crashes if we std&n;   into it, so we cannot use memset.  */
DECL|function|sun4_memset
r_static
id|__inline__
r_void
op_star
id|sun4_memset
c_func
(paren
r_void
op_star
id|s
comma
r_char
id|val
comma
r_int
id|count
)paren
(brace
r_int
id|i
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
(paren
r_char
op_star
)paren
id|s
)paren
(braket
id|i
)braket
op_assign
id|val
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/* To be honest, this is slow_memmove :). But sun4 is crappy, so what we can do. */
DECL|function|fast_memmove
r_static
id|__inline__
r_void
id|fast_memmove
c_func
(paren
r_void
op_star
id|d
comma
r_const
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|d
OL
id|s
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(paren
(paren
r_char
op_star
)paren
id|d
)paren
(braket
id|i
)braket
op_assign
(paren
(paren
r_char
op_star
)paren
id|s
)paren
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(paren
(paren
r_char
op_star
)paren
id|d
)paren
(braket
id|count
op_minus
id|i
op_minus
l_int|1
)braket
op_assign
(paren
(paren
r_char
op_star
)paren
id|s
)paren
(braket
id|count
op_minus
id|i
op_minus
l_int|1
)braket
suffix:semicolon
)brace
DECL|function|fb_memmove
r_static
id|__inline__
r_void
op_star
id|fb_memmove
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|size
)paren
(brace
id|fast_memmove
c_func
(paren
id|dst
comma
id|src
comma
id|size
)paren
suffix:semicolon
r_return
id|dst
suffix:semicolon
)brace
macro_line|#endif /* __mc68000__ */
macro_line|#if defined(__i386__)
DECL|function|fast_memmove
r_static
id|__inline__
r_void
id|fast_memmove
c_func
(paren
r_void
op_star
id|d
comma
r_const
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_int
id|d0
comma
id|d1
comma
id|d2
comma
id|d3
suffix:semicolon
r_if
c_cond
(paren
id|d
OL
id|s
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;shrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;jnc 1f&bslash;n&bslash;t&quot;
l_string|&quot;movsb&bslash;n&quot;
l_string|&quot;1:&bslash;tshrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;jnc 2f&bslash;n&bslash;t&quot;
l_string|&quot;movsw&bslash;n&quot;
l_string|&quot;2:&bslash;trep&bslash;n&bslash;t&quot;
l_string|&quot;movsl&quot;
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
suffix:colon
l_string|&quot;0&quot;
(paren
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
r_int
)paren
id|d
)paren
comma
l_string|&quot;2&quot;
(paren
(paren
r_int
)paren
id|s
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;std&bslash;n&bslash;t&quot;
l_string|&quot;shrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;jnc 1f&bslash;n&bslash;t&quot;
l_string|&quot;movb 3(%%esi),%%al&bslash;n&bslash;t&quot;
l_string|&quot;movb %%al,3(%%edi)&bslash;n&bslash;t&quot;
l_string|&quot;decl %%esi&bslash;n&bslash;t&quot;
l_string|&quot;decl %%edi&bslash;n&quot;
l_string|&quot;1:&bslash;tshrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;jnc 2f&bslash;n&bslash;t&quot;
l_string|&quot;movw 2(%%esi),%%ax&bslash;n&bslash;t&quot;
l_string|&quot;movw %%ax,2(%%edi)&bslash;n&bslash;t&quot;
l_string|&quot;decl %%esi&bslash;n&bslash;t&quot;
l_string|&quot;decl %%edi&bslash;n&bslash;t&quot;
l_string|&quot;decl %%esi&bslash;n&bslash;t&quot;
l_string|&quot;decl %%edi&bslash;n&quot;
l_string|&quot;2:&bslash;trep&bslash;n&bslash;t&quot;
l_string|&quot;movsl&bslash;n&bslash;t&quot;
l_string|&quot;cld&quot;
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
comma
l_string|&quot;=&amp;a&quot;
(paren
id|d3
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
id|count
op_minus
l_int|4
op_plus
(paren
r_int
)paren
id|d
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
op_minus
l_int|4
op_plus
(paren
r_int
)paren
id|s
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|fb_memmove
r_static
id|__inline__
r_void
op_star
id|fb_memmove
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|size
)paren
(brace
id|fast_memmove
c_func
(paren
id|dst
comma
id|src
comma
id|size
)paren
suffix:semicolon
r_return
id|dst
suffix:semicolon
)brace
macro_line|#else /* !__i386__ */
multiline_comment|/*&n;     *  Anyone who&squot;d like to write asm functions for other CPUs?&n;     *   (Why are these functions better than those from include/asm/string.h?)&n;     */
DECL|function|fb_memmove
r_static
id|__inline__
r_void
op_star
id|fb_memmove
c_func
(paren
r_void
op_star
id|d
comma
r_const
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|dst
comma
id|src
suffix:semicolon
r_if
c_cond
(paren
id|d
OL
id|s
)paren
(brace
id|dst
op_assign
(paren
r_int
r_int
)paren
id|d
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
)paren
id|s
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
OL
l_int|8
)paren
op_logical_or
(paren
(paren
id|dst
op_xor
id|src
)paren
op_amp
l_int|3
)paren
)paren
r_goto
id|restup
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_amp
l_int|1
)paren
(brace
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dst
op_amp
l_int|2
)paren
(brace
id|fb_writew
c_func
(paren
id|fb_readw
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
id|src
op_add_assign
l_int|2
suffix:semicolon
id|dst
op_add_assign
l_int|2
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
OG
l_int|3
)paren
(brace
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
id|src
op_add_assign
l_int|4
suffix:semicolon
id|dst
op_add_assign
l_int|4
suffix:semicolon
id|count
op_sub_assign
l_int|4
suffix:semicolon
)brace
id|restup
suffix:colon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
)brace
r_else
(brace
id|dst
op_assign
(paren
r_int
r_int
)paren
id|d
op_plus
id|count
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
)paren
id|s
op_plus
id|count
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
OL
l_int|8
)paren
op_logical_or
(paren
(paren
id|dst
op_xor
id|src
)paren
op_amp
l_int|3
)paren
)paren
r_goto
id|restdown
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_amp
l_int|1
)paren
(brace
id|src
op_decrement
suffix:semicolon
id|dst
op_decrement
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dst
op_amp
l_int|2
)paren
(brace
id|src
op_sub_assign
l_int|2
suffix:semicolon
id|dst
op_sub_assign
l_int|2
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
id|fb_writew
c_func
(paren
id|fb_readw
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
OG
l_int|3
)paren
(brace
id|src
op_sub_assign
l_int|4
suffix:semicolon
id|dst
op_sub_assign
l_int|4
suffix:semicolon
id|count
op_sub_assign
l_int|4
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
id|restdown
suffix:colon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|src
op_decrement
suffix:semicolon
id|dst
op_decrement
suffix:semicolon
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
)brace
r_return
id|d
suffix:semicolon
)brace
DECL|function|fast_memmove
r_static
id|__inline__
r_void
id|fast_memmove
c_func
(paren
r_char
op_star
id|d
comma
r_const
r_char
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|dst
comma
id|src
suffix:semicolon
r_if
c_cond
(paren
id|d
OL
id|s
)paren
(brace
id|dst
op_assign
(paren
r_int
r_int
)paren
id|d
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
)paren
id|s
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
OL
l_int|8
)paren
op_logical_or
(paren
(paren
id|dst
op_xor
id|src
)paren
op_amp
l_int|3
)paren
)paren
r_goto
id|restup
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_amp
l_int|1
)paren
(brace
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dst
op_amp
l_int|2
)paren
(brace
id|fb_writew
c_func
(paren
id|fb_readw
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
id|src
op_add_assign
l_int|2
suffix:semicolon
id|dst
op_add_assign
l_int|2
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
OG
l_int|3
)paren
(brace
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
id|src
op_add_assign
l_int|4
suffix:semicolon
id|dst
op_add_assign
l_int|4
suffix:semicolon
id|count
op_sub_assign
l_int|4
suffix:semicolon
)brace
id|restup
suffix:colon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|src
op_increment
)paren
comma
id|dst
op_increment
)paren
suffix:semicolon
)brace
r_else
(brace
id|dst
op_assign
(paren
r_int
r_int
)paren
id|d
op_plus
id|count
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
)paren
id|s
op_plus
id|count
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
OL
l_int|8
)paren
op_logical_or
(paren
(paren
id|dst
op_xor
id|src
)paren
op_amp
l_int|3
)paren
)paren
r_goto
id|restdown
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_amp
l_int|1
)paren
(brace
id|src
op_decrement
suffix:semicolon
id|dst
op_decrement
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dst
op_amp
l_int|2
)paren
(brace
id|src
op_sub_assign
l_int|2
suffix:semicolon
id|dst
op_sub_assign
l_int|2
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
id|fb_writew
c_func
(paren
id|fb_readw
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
OG
l_int|3
)paren
(brace
id|src
op_sub_assign
l_int|4
suffix:semicolon
id|dst
op_sub_assign
l_int|4
suffix:semicolon
id|count
op_sub_assign
l_int|4
suffix:semicolon
id|fb_writel
c_func
(paren
id|fb_readl
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
id|restdown
suffix:colon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|src
op_decrement
suffix:semicolon
id|dst
op_decrement
suffix:semicolon
id|fb_writeb
c_func
(paren
id|fb_readb
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* !__i386__ */
DECL|function|cfb_copyarea
r_void
id|cfb_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_struct
id|fb_copyarea
op_star
id|area
)paren
(brace
r_int
id|x2
comma
id|y2
comma
id|lineincr
comma
id|shift
comma
id|shift_right
comma
id|shift_left
comma
id|old_dx
comma
id|old_dy
suffix:semicolon
r_int
id|j
comma
id|linesize
op_assign
id|p-&gt;fix.line_length
comma
id|bpl
op_assign
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|start_index
comma
id|end_index
comma
id|start_mask
comma
id|end_mask
comma
id|last
comma
id|tmp
suffix:semicolon
r_int
r_int
op_star
id|dst
op_assign
l_int|NULL
comma
op_star
id|src
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|src1
comma
op_star
id|dst1
suffix:semicolon
r_int
id|height
suffix:semicolon
multiline_comment|/* clip the destination */
id|old_dx
op_assign
id|area-&gt;dx
suffix:semicolon
id|old_dy
op_assign
id|area-&gt;dy
suffix:semicolon
multiline_comment|/*&n;&t; * We could use hardware clipping but on many cards you get around&n;&t; * hardware clipping by writing to framebuffer directly.&n;&t; */
id|x2
op_assign
id|area-&gt;dx
op_plus
id|area-&gt;width
suffix:semicolon
id|y2
op_assign
id|area-&gt;dy
op_plus
id|area-&gt;height
suffix:semicolon
id|area-&gt;dx
op_assign
id|area-&gt;dx
OG
l_int|0
ques
c_cond
id|area-&gt;dx
suffix:colon
l_int|0
suffix:semicolon
id|area-&gt;dy
op_assign
id|area-&gt;dy
OG
l_int|0
ques
c_cond
id|area-&gt;dy
suffix:colon
l_int|0
suffix:semicolon
id|x2
op_assign
id|x2
OL
id|p-&gt;var.xres_virtual
ques
c_cond
id|x2
suffix:colon
id|p-&gt;var.xres_virtual
suffix:semicolon
id|y2
op_assign
id|y2
OL
id|p-&gt;var.yres_virtual
ques
c_cond
id|y2
suffix:colon
id|p-&gt;var.yres_virtual
suffix:semicolon
id|area-&gt;width
op_assign
id|x2
op_minus
id|area-&gt;dx
suffix:semicolon
id|area-&gt;height
op_assign
id|y2
op_minus
id|area-&gt;dy
suffix:semicolon
multiline_comment|/* update sx1,sy1 */
id|area-&gt;sx
op_add_assign
(paren
id|area-&gt;dx
op_minus
id|old_dx
)paren
suffix:semicolon
id|area-&gt;sy
op_add_assign
(paren
id|area-&gt;dy
op_minus
id|old_dy
)paren
suffix:semicolon
id|height
op_assign
id|area-&gt;height
suffix:semicolon
multiline_comment|/* the source must be completely inside the virtual screen */
r_if
c_cond
(paren
id|area-&gt;sx
template_param
id|p-&gt;var.yres_virtual
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|area-&gt;dy
OL
id|area-&gt;sy
op_logical_or
(paren
id|area-&gt;dy
op_eq
id|area-&gt;sy
op_logical_and
id|area-&gt;dx
OL
id|area-&gt;sx
)paren
)paren
(brace
multiline_comment|/* start at the top */
id|src1
op_assign
id|p-&gt;screen_base
op_plus
id|area-&gt;sy
op_star
id|linesize
op_plus
(paren
(paren
id|area-&gt;sx
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|dst1
op_assign
id|p-&gt;screen_base
op_plus
id|area-&gt;dy
op_star
id|linesize
op_plus
(paren
(paren
id|area-&gt;dx
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|lineincr
op_assign
id|linesize
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* start at the bottom */
id|src1
op_assign
id|p-&gt;screen_base
op_plus
(paren
id|area-&gt;sy
op_plus
id|area-&gt;height
op_minus
l_int|1
)paren
op_star
id|linesize
op_plus
(paren
(paren
(paren
id|area-&gt;sx
op_plus
id|area-&gt;width
op_minus
l_int|1
)paren
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|dst1
op_assign
id|p-&gt;screen_base
op_plus
(paren
id|area-&gt;dy
op_plus
id|area-&gt;height
op_minus
l_int|1
)paren
op_star
id|linesize
op_plus
(paren
(paren
(paren
id|area-&gt;dx
op_plus
id|area-&gt;width
op_minus
l_int|1
)paren
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|lineincr
op_assign
op_minus
id|linesize
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|BITS_PER_LONG
op_mod
id|p-&gt;var.bits_per_pixel
)paren
op_eq
l_int|0
)paren
(brace
r_int
id|ppw
op_assign
id|BITS_PER_LONG
op_div
id|p-&gt;var.bits_per_pixel
suffix:semicolon
r_int
id|n
op_assign
(paren
(paren
id|area-&gt;width
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|start_index
op_assign
(paren
(paren
r_int
r_int
)paren
id|src1
op_amp
(paren
id|bpl
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|end_index
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|src1
op_plus
id|n
)paren
op_amp
(paren
id|bpl
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|shift
op_assign
(paren
(paren
r_int
r_int
)paren
id|dst1
op_amp
(paren
id|bpl
op_minus
l_int|1
)paren
)paren
op_minus
(paren
(paren
r_int
r_int
)paren
id|src1
op_amp
(paren
id|bpl
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|start_mask
op_assign
id|end_mask
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|start_index
)paren
(brace
id|start_mask
op_assign
op_minus
l_int|1
op_rshift
(paren
id|start_index
op_lshift
l_int|3
)paren
suffix:semicolon
id|n
op_sub_assign
(paren
id|bpl
op_minus
id|start_index
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end_index
)paren
(brace
id|end_mask
op_assign
op_minus
l_int|1
op_lshift
(paren
(paren
id|bpl
op_minus
id|end_index
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|n
op_sub_assign
id|end_index
suffix:semicolon
)brace
id|n
op_div_assign
id|bpl
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|start_mask
)paren
(brace
r_if
c_cond
(paren
id|end_mask
)paren
id|end_mask
op_and_assign
id|start_mask
suffix:semicolon
r_else
id|end_mask
op_assign
id|start_mask
suffix:semicolon
id|start_mask
op_assign
l_int|0
suffix:semicolon
)brace
id|n
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shift
)paren
(brace
r_if
c_cond
(paren
id|shift
OG
l_int|0
)paren
(brace
multiline_comment|/* dest is over to right more */
id|shift_right
op_assign
id|shift
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|shift_left
op_assign
(paren
id|ppw
op_minus
id|shift
)paren
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* source is to the right more */
id|shift_right
op_assign
(paren
id|ppw
op_plus
id|shift
)paren
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
id|shift_left
op_assign
op_minus
id|shift
op_star
id|p-&gt;var.bits_per_pixel
suffix:semicolon
)brace
multiline_comment|/* general case, positive increment */
r_if
c_cond
(paren
id|lineincr
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|shift
OL
l_int|0
)paren
id|n
op_increment
suffix:semicolon
r_do
(brace
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
id|dst1
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
op_star
)paren
id|src1
suffix:semicolon
id|last
op_assign
(paren
id|FB_READ
c_func
(paren
id|src
)paren
op_amp
id|start_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shift
OG
l_int|0
)paren
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|dst
)paren
op_or
(paren
id|last
op_rshift
id|shift_right
)paren
comma
id|dst
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|n
suffix:semicolon
id|j
op_increment
)paren
(brace
id|dst
op_increment
suffix:semicolon
id|tmp
op_assign
id|FB_READ
c_func
(paren
id|src
)paren
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|FB_WRITE
c_func
(paren
(paren
id|last
op_lshift
id|shift_left
)paren
op_or
(paren
id|tmp
op_rshift
id|shift_right
)paren
comma
id|dst
)paren
suffix:semicolon
id|last
op_assign
id|tmp
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|dst
)paren
op_or
(paren
id|last
op_lshift
id|shift_left
)paren
comma
id|dst
)paren
suffix:semicolon
id|src1
op_add_assign
id|lineincr
suffix:semicolon
id|dst1
op_add_assign
id|lineincr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|height
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* general case, negative increment */
r_if
c_cond
(paren
id|shift
OG
l_int|0
)paren
id|n
op_increment
suffix:semicolon
r_do
(brace
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
id|dst1
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
op_star
)paren
id|src1
suffix:semicolon
id|last
op_assign
(paren
id|FB_READ
c_func
(paren
id|src
)paren
op_amp
id|end_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shift
OL
l_int|0
)paren
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|dst
)paren
op_or
(paren
id|last
op_rshift
id|shift_right
)paren
comma
id|dst
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|n
suffix:semicolon
id|j
op_increment
)paren
(brace
id|dst
op_decrement
suffix:semicolon
id|tmp
op_assign
id|FB_READ
c_func
(paren
id|src
)paren
suffix:semicolon
id|src
op_decrement
suffix:semicolon
id|FB_WRITE
c_func
(paren
(paren
id|tmp
op_lshift
id|shift_left
)paren
op_or
(paren
id|last
op_rshift
id|shift_right
)paren
comma
id|dst
)paren
suffix:semicolon
id|last
op_assign
id|tmp
suffix:semicolon
id|src
op_decrement
suffix:semicolon
)brace
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|dst
)paren
op_or
(paren
id|last
op_rshift
id|shift_right
)paren
comma
id|dst
)paren
suffix:semicolon
id|src1
op_add_assign
id|lineincr
suffix:semicolon
id|dst1
op_add_assign
id|lineincr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|height
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* no shift needed */
r_if
c_cond
(paren
id|lineincr
OG
l_int|0
)paren
(brace
multiline_comment|/* positive increment */
r_do
(brace
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|dst1
op_minus
id|start_index
)paren
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|src1
op_minus
id|start_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start_mask
)paren
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|src
)paren
op_or
id|start_mask
comma
id|dst
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|n
suffix:semicolon
id|j
op_increment
)paren
(brace
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end_mask
)paren
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|src
)paren
op_or
id|end_mask
comma
id|dst
)paren
suffix:semicolon
id|src1
op_add_assign
id|lineincr
suffix:semicolon
id|dst1
op_add_assign
id|lineincr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|height
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* negative increment */
r_do
(brace
id|dst
op_assign
(paren
r_int
r_int
op_star
)paren
id|dst1
suffix:semicolon
id|src
op_assign
(paren
r_int
r_int
op_star
)paren
id|src1
suffix:semicolon
r_if
c_cond
(paren
id|start_mask
)paren
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|src
)paren
op_or
id|start_mask
comma
id|dst
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|n
suffix:semicolon
id|j
op_increment
)paren
(brace
id|FB_WRITE
c_func
(paren
id|FB_READ
c_func
(paren
id|src
)paren
comma
id|dst
)paren
suffix:semicolon
id|dst
op_decrement
suffix:semicolon
id|src
op_decrement
suffix:semicolon
)brace
id|src1
op_add_assign
id|lineincr
suffix:semicolon
id|dst1
op_add_assign
id|lineincr
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|height
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_int
id|n
op_assign
(paren
(paren
id|area-&gt;width
op_star
id|p-&gt;var.bits_per_pixel
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
r_int
id|n16
op_assign
(paren
id|n
op_rshift
l_int|4
)paren
op_lshift
l_int|4
suffix:semicolon
r_int
id|n_fract
op_assign
id|n
op_minus
id|n16
suffix:semicolon
r_int
id|rows
suffix:semicolon
r_if
c_cond
(paren
id|area-&gt;dy
OL
id|area-&gt;sy
op_logical_or
(paren
id|area-&gt;dy
op_eq
id|area-&gt;sy
op_logical_and
id|area-&gt;dx
OL
id|area-&gt;sx
)paren
)paren
(brace
r_for
c_loop
(paren
id|rows
op_assign
id|height
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|n16
)paren
id|fast_memmove
c_func
(paren
id|dst1
comma
id|src1
comma
id|n16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_fract
)paren
id|fb_memmove
c_func
(paren
id|dst1
op_plus
id|n16
comma
id|src1
op_plus
id|n16
comma
id|n_fract
)paren
suffix:semicolon
id|dst1
op_add_assign
id|linesize
suffix:semicolon
id|src1
op_add_assign
id|linesize
suffix:semicolon
)brace
)brace
r_else
(brace
r_for
c_loop
(paren
id|rows
op_assign
id|height
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|n16
)paren
id|fast_memmove
c_func
(paren
id|dst1
comma
id|src1
comma
id|n16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_fract
)paren
id|fb_memmove
c_func
(paren
id|dst1
op_plus
id|n16
comma
id|src1
op_plus
id|n16
comma
id|n_fract
)paren
suffix:semicolon
id|dst1
op_sub_assign
id|linesize
suffix:semicolon
id|src1
op_sub_assign
id|linesize
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|variable|cfb_copyarea
id|EXPORT_SYMBOL
c_func
(paren
id|cfb_copyarea
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;James Simmons &lt;jsimmons@users.sf.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Generic software accelerated copyarea&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
