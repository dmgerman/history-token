multiline_comment|/*&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997, 2001 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 2000 SiByte, Inc.&n; * Copyright (C) 2005 Thiemo Seufer&n; *&n; * Written by Justin Carlson of SiByte, Inc.&n; *         and Kip Walker of Broadcom Corp.&n; *&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_dma.h&gt;
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
DECL|function|clear_page_cpu
r_static
r_inline
r_void
id|clear_page_cpu
c_func
(paren
r_void
op_star
id|page
)paren
(brace
r_int
r_char
op_star
id|addr
op_assign
(paren
r_int
r_char
op_star
)paren
id|page
suffix:semicolon
r_int
r_char
op_star
id|end
op_assign
id|addr
op_plus
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/*&n;&t; * JDCXXX - This should be bottlenecked by the write buffer, but these&n;&t; * things tend to be mildly unpredictable...should check this on the&n;&t; * performance model&n;&t; *&n;&t; * We prefetch 4 lines ahead.  We&squot;re also &quot;cheating&quot; slightly here...&n;&t; * since we know we&squot;re on an SB1, we force the assembler to take&n;&t; * 64-bit operands to speed things up&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;push&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;mips4&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;noreorder&t;&bslash;n&quot;
macro_line|#ifdef CONFIG_CPU_HAS_PREFETCH
l_string|&quot;&t;daddiu&t;%0, %0, 128&t;&bslash;n&quot;
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;, -128(%0)  &bslash;n&quot;
multiline_comment|/* Prefetch the first 4 lines */
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  -96(%0)  &bslash;n&quot;
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  -64(%0)  &bslash;n&quot;
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  -32(%0)  &bslash;n&quot;
l_string|&quot;1:&t;sd&t;$0, -128(%0)&t;&bslash;n&quot;
multiline_comment|/* Throw out a cacheline of 0&squot;s */
l_string|&quot;&t;sd&t;$0, -120(%0)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$0, -112(%0)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$0, -104(%0)&t;&bslash;n&quot;
l_string|&quot;&t;daddiu&t;%0, %0, 32&t;&bslash;n&quot;
l_string|&quot;&t;bnel&t;%0, %1, 1b&t;&bslash;n&quot;
l_string|&quot;&t; pref&t;&quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  -32(%0)  &bslash;n&quot;
l_string|&quot;&t;daddiu&t;%0, %0, -128&t;&bslash;n&quot;
macro_line|#endif
l_string|&quot;&t;sd&t;$0, 0(%0)&t;&bslash;n&quot;
multiline_comment|/* Throw out a cacheline of 0&squot;s */
l_string|&quot;1:&t;sd&t;$0, 8(%0)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$0, 16(%0)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$0, 24(%0)&t;&bslash;n&quot;
l_string|&quot;&t;daddiu&t;%0, %0, 32&t;&bslash;n&quot;
l_string|&quot;&t;bnel&t;%0, %1, 1b&t;&bslash;n&quot;
l_string|&quot;&t; sd&t;$0, 0(%0)&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;pop&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;+r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|end
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|copy_page_cpu
r_static
r_inline
r_void
id|copy_page_cpu
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
r_char
op_star
id|src
op_assign
(paren
r_int
r_char
op_star
)paren
id|from
suffix:semicolon
r_int
r_char
op_star
id|dst
op_assign
(paren
r_int
r_char
op_star
)paren
id|to
suffix:semicolon
r_int
r_char
op_star
id|end
op_assign
id|src
op_plus
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/*&n;&t; * The pref&squot;s used here are using &quot;streaming&quot; hints, which cause the&n;&t; * copied data to be kicked out of the cache sooner.  A page copy often&n;&t; * ends up copying a lot more data than is commonly used, so this seems&n;&t; * to make sense in terms of reducing cache pollution, but I&squot;ve no real&n;&t; * performance data to back this up&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;push&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;mips4&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;noreorder&t;&bslash;n&quot;
macro_line|#ifdef CONFIG_CPU_HAS_PREFETCH
l_string|&quot;&t;daddiu&t;%0, %0, 128&t;&bslash;n&quot;
l_string|&quot;&t;daddiu&t;%1, %1, 128&t;&bslash;n&quot;
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_LOAD_STREAMED_HINT
l_string|&quot;, -128(%0)&bslash;n&quot;
multiline_comment|/* Prefetch the first 4 lines */
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;, -128(%1)&bslash;n&quot;
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_LOAD_STREAMED_HINT
l_string|&quot;,  -96(%0)&bslash;n&quot;
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  -96(%1)&bslash;n&quot;
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_LOAD_STREAMED_HINT
l_string|&quot;,  -64(%0)&bslash;n&quot;
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  -64(%1)&bslash;n&quot;
l_string|&quot;&t;pref&t;&quot;
id|SB1_PREF_LOAD_STREAMED_HINT
l_string|&quot;,  -32(%0)&bslash;n&quot;
l_string|&quot;1:&t;pref&t;&quot;
id|SB1_PREF_STORE_STREAMED_HINT
l_string|&quot;,  -32(%1)&bslash;n&quot;
macro_line|# ifdef CONFIG_MIPS64
l_string|&quot;&t;ld&t;$8, -128(%0)&t;&bslash;n&quot;
multiline_comment|/* Block copy a cacheline */
l_string|&quot;&t;ld&t;$9, -120(%0)&t;&bslash;n&quot;
l_string|&quot;&t;ld&t;$10, -112(%0)&t;&bslash;n&quot;
l_string|&quot;&t;ld&t;$11, -104(%0)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$8, -128(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$9, -120(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$10, -112(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$11, -104(%1)&t;&bslash;n&quot;
macro_line|# else
l_string|&quot;&t;lw&t;$2, -128(%0)&t;&bslash;n&quot;
multiline_comment|/* Block copy a cacheline */
l_string|&quot;&t;lw&t;$3, -124(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$6, -120(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$7, -116(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$8, -112(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$9, -108(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$10, -104(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$11, -100(%0)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$2, -128(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$3, -124(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$6, -120(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$7, -116(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$8, -112(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$9, -108(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$10, -104(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$11, -100(%1)&t;&bslash;n&quot;
macro_line|# endif
l_string|&quot;&t;daddiu&t;%0, %0, 32&t;&bslash;n&quot;
l_string|&quot;&t;daddiu&t;%1, %1, 32&t;&bslash;n&quot;
l_string|&quot;&t;bnel&t;%0, %2, 1b&t;&bslash;n&quot;
l_string|&quot;&t; pref&t;&quot;
id|SB1_PREF_LOAD_STREAMED_HINT
l_string|&quot;,  -32(%0)&bslash;n&quot;
l_string|&quot;&t;daddiu&t;%0, %0, -128&t;&bslash;n&quot;
l_string|&quot;&t;daddiu&t;%1, %1, -128&t;&bslash;n&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
l_string|&quot;&t;ld&t;$8, 0(%0)&t;&bslash;n&quot;
multiline_comment|/* Block copy a cacheline */
l_string|&quot;1:&t;ld&t;$9, 8(%0)&t;&bslash;n&quot;
l_string|&quot;&t;ld&t;$10, 16(%0)&t;&bslash;n&quot;
l_string|&quot;&t;ld&t;$11, 24(%0)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$8, 0(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$9, 8(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$10, 16(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;$11, 24(%1)&t;&bslash;n&quot;
macro_line|#else
l_string|&quot;&t;lw&t;$2, 0(%0)&t;&bslash;n&quot;
multiline_comment|/* Block copy a cacheline */
l_string|&quot;1:&t;lw&t;$3, 4(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$6, 8(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$7, 12(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$8, 16(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$9, 20(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$10, 24(%0)&t;&bslash;n&quot;
l_string|&quot;&t;lw&t;$11, 28(%0)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$2, 0(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$3, 4(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$6, 8(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$7, 12(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$8, 16(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$9, 20(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$10, 24(%1)&t;&bslash;n&quot;
l_string|&quot;&t;sw&t;$11, 28(%1)&t;&bslash;n&quot;
macro_line|#endif
l_string|&quot;&t;daddiu&t;%0, %0, 32&t;&bslash;n&quot;
l_string|&quot;&t;daddiu&t;%1, %1, 32&t;&bslash;n&quot;
l_string|&quot;&t;bnel&t;%0, %2, 1b&t;&bslash;n&quot;
macro_line|#ifdef CONFIG_MIPS64
l_string|&quot;&t; ld&t;$8, 0(%0)&t;&bslash;n&quot;
macro_line|#else
l_string|&quot;&t; lw&t;$2, 0(%0)&t;&bslash;n&quot;
macro_line|#endif
l_string|&quot;&t;.set&t;pop&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;+r&quot;
(paren
id|src
)paren
comma
l_string|&quot;+r&quot;
(paren
id|dst
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|end
)paren
macro_line|#ifdef CONFIG_MIPS64
suffix:colon
l_string|&quot;$8&quot;
comma
l_string|&quot;$9&quot;
comma
l_string|&quot;$10&quot;
comma
l_string|&quot;$11&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#else
suffix:colon
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$6&quot;
comma
l_string|&quot;$7&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$9&quot;
comma
l_string|&quot;$10&quot;
comma
l_string|&quot;$11&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_SIBYTE_DMA_PAGEOPS
multiline_comment|/*&n; * Pad descriptors to cacheline, since each is exclusively owned by a&n; * particular CPU. &n; */
DECL|struct|dmadscr_s
r_typedef
r_struct
id|dmadscr_s
(brace
DECL|member|dscr_a
id|u64
id|dscr_a
suffix:semicolon
DECL|member|dscr_b
id|u64
id|dscr_b
suffix:semicolon
DECL|member|pad_a
id|u64
id|pad_a
suffix:semicolon
DECL|member|pad_b
id|u64
id|pad_b
suffix:semicolon
DECL|typedef|dmadscr_t
)brace
id|dmadscr_t
suffix:semicolon
DECL|variable|page_descr
r_static
id|dmadscr_t
id|page_descr
(braket
id|NR_CPUS
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
DECL|function|sb1_dma_init
r_void
id|sb1_dma_init
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|u64
id|base_val
op_assign
id|CPHYSADDR
c_func
(paren
op_amp
id|page_descr
(braket
id|cpu
)braket
)paren
op_or
id|V_DM_DSCR_BASE_RINGSZ
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|bus_writeq
c_func
(paren
id|base_val
comma
(paren
r_void
op_star
)paren
id|IOADDR
c_func
(paren
id|A_DM_REGISTER
c_func
(paren
id|cpu
comma
id|R_DM_DSCR_BASE
)paren
)paren
)paren
suffix:semicolon
id|bus_writeq
c_func
(paren
id|base_val
op_or
id|M_DM_DSCR_BASE_RESET
comma
(paren
r_void
op_star
)paren
id|IOADDR
c_func
(paren
id|A_DM_REGISTER
c_func
(paren
id|cpu
comma
id|R_DM_DSCR_BASE
)paren
)paren
)paren
suffix:semicolon
id|bus_writeq
c_func
(paren
id|base_val
op_or
id|M_DM_DSCR_BASE_ENABL
comma
(paren
r_void
op_star
)paren
id|IOADDR
c_func
(paren
id|A_DM_REGISTER
c_func
(paren
id|cpu
comma
id|R_DM_DSCR_BASE
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|clear_page
r_void
id|clear_page
c_func
(paren
r_void
op_star
id|page
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* if the page is above Kseg0, use old way */
r_if
c_cond
(paren
(paren
r_int
)paren
id|KSEGX
c_func
(paren
id|page
)paren
op_ne
(paren
r_int
)paren
id|CKSEG0
)paren
r_return
id|clear_page_cpu
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_descr
(braket
id|cpu
)braket
dot
id|dscr_a
op_assign
id|CPHYSADDR
c_func
(paren
id|page
)paren
op_or
id|M_DM_DSCRA_ZERO_MEM
op_or
id|M_DM_DSCRA_L2C_DEST
op_or
id|M_DM_DSCRA_INTERRUPT
suffix:semicolon
id|page_descr
(braket
id|cpu
)braket
dot
id|dscr_b
op_assign
id|V_DM_DSCRB_SRC_LENGTH
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|bus_writeq
c_func
(paren
l_int|1
comma
(paren
r_void
op_star
)paren
id|IOADDR
c_func
(paren
id|A_DM_REGISTER
c_func
(paren
id|cpu
comma
id|R_DM_DSCR_COUNT
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t really want to do it this way, but there&squot;s no&n;&t; * reliable way to delay completion detection.&n;&t; */
r_while
c_loop
(paren
op_logical_neg
(paren
id|bus_readq
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|IOADDR
c_func
(paren
id|A_DM_REGISTER
c_func
(paren
id|cpu
comma
id|R_DM_DSCR_BASE_DEBUG
)paren
)paren
op_amp
id|M_DM_DSCR_BASE_INTERRUPT
)paren
)paren
)paren
)paren
suffix:semicolon
id|bus_readq
c_func
(paren
(paren
r_void
op_star
)paren
id|IOADDR
c_func
(paren
id|A_DM_REGISTER
c_func
(paren
id|cpu
comma
id|R_DM_DSCR_BASE
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|copy_page
r_void
id|copy_page
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
r_int
id|from_phys
op_assign
id|CPHYSADDR
c_func
(paren
id|from
)paren
suffix:semicolon
r_int
r_int
id|to_phys
op_assign
id|CPHYSADDR
c_func
(paren
id|to
)paren
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* if either page is above Kseg0, use old way */
r_if
c_cond
(paren
(paren
r_int
)paren
id|KSEGX
c_func
(paren
id|to
)paren
op_ne
(paren
r_int
)paren
id|CKSEG0
op_logical_or
(paren
r_int
)paren
id|KSEGX
c_func
(paren
id|from
)paren
op_ne
(paren
r_int
)paren
id|CKSEG0
)paren
r_return
id|copy_page_cpu
c_func
(paren
id|to
comma
id|from
)paren
suffix:semicolon
id|page_descr
(braket
id|cpu
)braket
dot
id|dscr_a
op_assign
id|CPHYSADDR
c_func
(paren
id|to_phys
)paren
op_or
id|M_DM_DSCRA_L2C_DEST
op_or
id|M_DM_DSCRA_INTERRUPT
suffix:semicolon
id|page_descr
(braket
id|cpu
)braket
dot
id|dscr_b
op_assign
id|CPHYSADDR
c_func
(paren
id|from_phys
)paren
op_or
id|V_DM_DSCRB_SRC_LENGTH
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|bus_writeq
c_func
(paren
l_int|1
comma
(paren
r_void
op_star
)paren
id|IOADDR
c_func
(paren
id|A_DM_REGISTER
c_func
(paren
id|cpu
comma
id|R_DM_DSCR_COUNT
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t really want to do it this way, but there&squot;s no&n;&t; * reliable way to delay completion detection.&n;&t; */
r_while
c_loop
(paren
op_logical_neg
(paren
id|bus_readq
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|IOADDR
c_func
(paren
id|A_DM_REGISTER
c_func
(paren
id|cpu
comma
id|R_DM_DSCR_BASE_DEBUG
)paren
)paren
op_amp
id|M_DM_DSCR_BASE_INTERRUPT
)paren
)paren
)paren
)paren
suffix:semicolon
id|bus_readq
c_func
(paren
(paren
r_void
op_star
)paren
id|IOADDR
c_func
(paren
id|A_DM_REGISTER
c_func
(paren
id|cpu
comma
id|R_DM_DSCR_BASE
)paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#else /* !CONFIG_SIBYTE_DMA_PAGEOPS */
DECL|function|clear_page
r_void
id|clear_page
c_func
(paren
r_void
op_star
id|page
)paren
(brace
r_return
id|clear_page_cpu
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|copy_page
r_void
id|copy_page
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
r_return
id|copy_page_cpu
c_func
(paren
id|to
comma
id|from
)paren
suffix:semicolon
)brace
macro_line|#endif /* !CONFIG_SIBYTE_DMA_PAGEOPS */
DECL|variable|clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|clear_page
)paren
suffix:semicolon
DECL|variable|copy_page
id|EXPORT_SYMBOL
c_func
(paren
id|copy_page
)paren
suffix:semicolon
eof
