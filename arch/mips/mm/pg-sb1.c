multiline_comment|/*&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997, 2001 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 2000 Sibyte&n; *&n; * Written by Justin Carlson (carlson@sibyte.com)&n; *&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifdef CONFIG_SB1_PASS_1_WORKAROUNDS
DECL|macro|SB1_PREF_LOAD_STREAMED_HINT
mdefine_line|#define SB1_PREF_LOAD_STREAMED_HINT &quot;0&quot;
DECL|macro|SB1_PREF_STORE_STREAMED_HINT
mdefine_line|#define SB1_PREF_STORE_STREAMED_HINT &quot;1&quot;
macro_line|#else
DECL|macro|SB1_PREF_LOAD_STREAMED_HINT
mdefine_line|#define SB1_PREF_LOAD_STREAMED_HINT &quot;4&quot;
DECL|macro|SB1_PREF_STORE_STREAMED_HINT
mdefine_line|#define SB1_PREF_STORE_STREAMED_HINT &quot;5&quot;
macro_line|#endif
multiline_comment|/* These are the functions hooked by the memory management function pointers */
DECL|function|sb1_clear_page
r_void
id|sb1_clear_page
c_func
(paren
r_void
op_star
id|page
)paren
(brace
multiline_comment|/*&n;&t; * JDCXXX - This should be bottlenecked by the write buffer, but these&n;&t; * things tend to be mildly unpredictable...should check this on the&n;&t; * performance model&n;&t; *&n;&t; * We prefetch 4 lines ahead.  We&squot;re also &quot;cheating&quot; slightly here...&n;&t; * since we know we&squot;re on an SB1, we force the assembler to take&n;&t; * 64-bit operands to speed things up&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push                  &bslash;n&quot;
l_string|&quot;.set noreorder             &bslash;n&quot;
l_string|&quot;.set noat                  &bslash;n&quot;
l_string|&quot;.set mips4                 &bslash;n&quot;
l_string|&quot;     addiu     $1, %0, %2  &bslash;n&quot;
multiline_comment|/* Calculate the end of the page to clear */
macro_line|#ifdef CONFIG_CPU_HAS_PREFETCH
l_string|&quot;     pref       &quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  0(%0)  &bslash;n&quot;
multiline_comment|/* Prefetch the first 4 lines */
l_string|&quot;     pref       &quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;, 32(%0)  &bslash;n&quot;
l_string|&quot;     pref       &quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;, 64(%0)  &bslash;n&quot;
l_string|&quot;     pref       &quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;, 96(%0)  &bslash;n&quot;
macro_line|#endif
l_string|&quot;1:   sd        $0,  0(%0)  &bslash;n&quot;
multiline_comment|/* Throw out a cacheline of 0&squot;s */
l_string|&quot;     sd        $0,  8(%0)  &bslash;n&quot;
l_string|&quot;     sd        $0, 16(%0)  &bslash;n&quot;
l_string|&quot;     sd        $0, 24(%0)  &bslash;n&quot;
macro_line|#ifdef CONFIG_CPU_HAS_PREFETCH
l_string|&quot;     pref       &quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,128(%0)  &bslash;n&quot;
multiline_comment|/* Prefetch 4 lines ahead     */
macro_line|#endif
l_string|&quot;     bne       $1, %0, 1b  &bslash;n&quot;
l_string|&quot;     addiu     %0, %0, 32  &bslash;n&quot;
multiline_comment|/* Next cacheline (This instruction better be short piped!) */
l_string|&quot;.set pop                   &bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|page
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|page
)paren
comma
l_string|&quot;I&quot;
(paren
id|PAGE_SIZE
op_minus
l_int|32
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|sb1_copy_page
r_void
id|sb1_copy_page
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
multiline_comment|/*&n;&t; * This should be optimized in assembly...can&squot;t use ld/sd, though,&n;&t; * because the top 32 bits could be nuked if we took an interrupt&n;&t; * during the routine.&t;And this is not a good place to be cli()&squot;ing&n;&t; *&n;&t; * The pref&squot;s used here are using &quot;streaming&quot; hints, which cause the&n;&t; * copied data to be kicked out of the cache sooner.  A page copy often&n;&t; * ends up copying a lot more data than is commonly used, so this seems&n;&t; * to make sense in terms of reducing cache pollution, but I&squot;ve no real&n;&t; * performance data to back this up&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push                  &bslash;n&quot;
l_string|&quot;.set noreorder             &bslash;n&quot;
l_string|&quot;.set noat                  &bslash;n&quot;
l_string|&quot;.set mips4                 &bslash;n&quot;
l_string|&quot;     addiu     $1, %0, %4  &bslash;n&quot;
multiline_comment|/* Calculate the end of the page to copy */
macro_line|#ifdef CONFIG_CPU_HAS_PREFETCH
l_string|&quot;     pref       &quot;
id|SB1_PREF_LOAD_STREAMED_HINT
l_string|&quot;,  0(%0)  &bslash;n&quot;
multiline_comment|/* Prefetch the first 3 lines */
l_string|&quot;     pref       &quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  0(%1)  &bslash;n&quot;
l_string|&quot;     pref       &quot;
id|SB1_PREF_LOAD_STREAMED_HINT
l_string|&quot;,  32(%0) &bslash;n&quot;
l_string|&quot;     pref       &quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  32(%1) &bslash;n&quot;
l_string|&quot;     pref       &quot;
id|SB1_PREF_LOAD_STREAMED_HINT
l_string|&quot;,  64(%0) &bslash;n&quot;
l_string|&quot;     pref       &quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  64(%1) &bslash;n&quot;
macro_line|#endif
l_string|&quot;1:   lw        $2,  0(%0)  &bslash;n&quot;
multiline_comment|/* Block copy a cacheline */
l_string|&quot;     lw        $3,  4(%0)  &bslash;n&quot;
l_string|&quot;     lw        $4,  8(%0)  &bslash;n&quot;
l_string|&quot;     lw        $5, 12(%0)  &bslash;n&quot;
l_string|&quot;     lw        $6, 16(%0)  &bslash;n&quot;
l_string|&quot;     lw        $7, 20(%0)  &bslash;n&quot;
l_string|&quot;     lw        $8, 24(%0)  &bslash;n&quot;
l_string|&quot;     lw        $9, 28(%0)  &bslash;n&quot;
macro_line|#ifdef CONFIG_CPU_HAS_PREFETCH
l_string|&quot;     pref       &quot;
id|SB1_PREF_LOAD_STREAMED_HINT
l_string|&quot;, 96(%0)  &bslash;n&quot;
multiline_comment|/* Prefetch ahead         */
l_string|&quot;     pref       &quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;, 96(%1)  &bslash;n&quot;
macro_line|#endif
l_string|&quot;     sw        $2,  0(%1)  &bslash;n&quot;
l_string|&quot;     sw        $3,  4(%1)  &bslash;n&quot;
l_string|&quot;     sw        $4,  8(%1)  &bslash;n&quot;
l_string|&quot;     sw        $5, 12(%1)  &bslash;n&quot;
l_string|&quot;     sw        $6, 16(%1)  &bslash;n&quot;
l_string|&quot;     sw        $7, 20(%1)  &bslash;n&quot;
l_string|&quot;     sw        $8, 24(%1)  &bslash;n&quot;
l_string|&quot;     sw        $9, 28(%1)  &bslash;n&quot;
l_string|&quot;     addiu     %1, %1, 32  &bslash;n&quot;
multiline_comment|/* Next cacheline */
l_string|&quot;     nop                   &bslash;n&quot;
multiline_comment|/* Force next add to short pipe */
l_string|&quot;     nop                   &bslash;n&quot;
multiline_comment|/* Force next add to short pipe */
l_string|&quot;     bne       $1, %0, 1b  &bslash;n&quot;
l_string|&quot;     addiu     %0, %0, 32  &bslash;n&quot;
multiline_comment|/* Next cacheline */
l_string|&quot;.set pop                   &bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|to
)paren
comma
l_string|&quot;=r&quot;
(paren
id|from
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|from
)paren
comma
l_string|&quot;1&quot;
(paren
id|to
)paren
comma
l_string|&quot;I&quot;
(paren
id|PAGE_SIZE
op_minus
l_int|32
)paren
suffix:colon
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$6&quot;
comma
l_string|&quot;$7&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$9&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
eof
