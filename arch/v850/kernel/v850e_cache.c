multiline_comment|/*&n; * arch/v850/kernel/v850e_cache.c -- Cache control for V850E cache memories&n; *&n; *  Copyright (C) 2003  NEC Electronics Corporation&n; *  Copyright (C) 2003  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
multiline_comment|/* This file implements cache control for the rather simple cache used on&n;   some V850E CPUs, specifically the NB85E/TEG CPU-core and the V850E/ME2&n;   CPU.  V850E2 processors have their own (better) cache&n;   implementation.  */
macro_line|#include &lt;asm/entry.h&gt;
macro_line|#include &lt;asm/v850e_cache.h&gt;
DECL|macro|WAIT_UNTIL_CLEAR
mdefine_line|#define WAIT_UNTIL_CLEAR(value) while (value) {}
multiline_comment|/* Set caching params via the BHC and DCC registers.  */
DECL|function|v850e_cache_enable
r_void
id|v850e_cache_enable
(paren
id|u16
id|bhc
comma
id|u16
id|icc
comma
id|u16
id|dcc
)paren
(brace
r_int
r_int
op_star
id|r0_ram
op_assign
(paren
r_int
r_int
op_star
)paren
id|R0_RAM_ADDR
suffix:semicolon
r_register
id|u16
id|bhc_val
id|asm
(paren
l_string|&quot;r6&quot;
)paren
op_assign
id|bhc
suffix:semicolon
multiline_comment|/* Read the instruction cache control register (ICC) and confirm&n;&t;   that bits 0 and 1 (TCLR0, TCLR1) are all cleared.  */
id|WAIT_UNTIL_CLEAR
(paren
id|V850E_CACHE_ICC
op_amp
l_int|0x3
)paren
suffix:semicolon
id|V850E_CACHE_ICC
op_assign
id|icc
suffix:semicolon
macro_line|#ifdef V850E_CACHE_DCC
multiline_comment|/* Configure data-cache.  */
id|V850E_CACHE_DCC
op_assign
id|dcc
suffix:semicolon
macro_line|#endif /* V850E_CACHE_DCC */
multiline_comment|/* Configure caching for various memory regions by writing the BHC&n;&t;   register.  The documentation says that an instruction _cannot_&n;&t;   enable/disable caching for the memory region in which the&n;&t;   instruction itself exists; to work around this, we store&n;&t;   appropriate instructions into the on-chip RAM area (which is never&n;&t;   cached), and briefly jump there to do the work.  */
macro_line|#ifdef V850E_CACHE_WRITE_IBS
op_star
id|r0_ram
op_increment
op_assign
l_int|0xf0720760
suffix:semicolon
multiline_comment|/* st.h r0, 0xfffff072[r0] */
macro_line|#endif
op_star
id|r0_ram
op_increment
op_assign
l_int|0xf06a3760
suffix:semicolon
multiline_comment|/* st.h r6, 0xfffff06a[r0] */
op_star
id|r0_ram
op_assign
l_int|0x5640006b
suffix:semicolon
multiline_comment|/* jmp [r11] */
id|asm
(paren
l_string|&quot;mov hilo(1f), r11; jmp [%1]; 1:;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|bhc_val
)paren
comma
l_string|&quot;r&quot;
(paren
id|R0_RAM_ADDR
)paren
suffix:colon
l_string|&quot;r11&quot;
)paren
suffix:semicolon
)brace
DECL|function|clear_icache
r_static
r_void
id|clear_icache
(paren
r_void
)paren
(brace
multiline_comment|/* 1. Read the instruction cache control register (ICC) and confirm&n;&t;      that bits 0 and 1 (TCLR0, TCLR1) are all cleared.  */
id|WAIT_UNTIL_CLEAR
(paren
id|V850E_CACHE_ICC
op_amp
l_int|0x3
)paren
suffix:semicolon
multiline_comment|/* 2. Read the ICC register and confirm that bit 12 (LOCK0) is&n;  &t;      cleared.  Bit 13 of the ICC register is always cleared.  */
id|WAIT_UNTIL_CLEAR
(paren
id|V850E_CACHE_ICC
op_amp
l_int|0x1000
)paren
suffix:semicolon
multiline_comment|/* 3. Set the TCLR0 and TCLR1 bits of the ICC register as follows,&n;&t;      when clearing way 0 and way 1 at the same time:&n;&t;        (a) Set the TCLR0 and TCLR1 bits.&n;&t;&t;(b) Read the TCLR0 and TCLR1 bits to confirm that these bits&n;&t;&t;    are cleared.&n;&t;&t;(c) Perform (a) and (b) above again.  */
id|V850E_CACHE_ICC
op_or_assign
l_int|0x3
suffix:semicolon
id|WAIT_UNTIL_CLEAR
(paren
id|V850E_CACHE_ICC
op_amp
l_int|0x3
)paren
suffix:semicolon
macro_line|#ifdef V850E_CACHE_REPEAT_ICC_WRITE
multiline_comment|/* Do it again.  */
id|V850E_CACHE_ICC
op_or_assign
l_int|0x3
suffix:semicolon
id|WAIT_UNTIL_CLEAR
(paren
id|V850E_CACHE_ICC
op_amp
l_int|0x3
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef V850E_CACHE_DCC
multiline_comment|/* Flush or clear (or both) the data cache, depending on the value of FLAGS;&n;   the procedure is the same for both, just the control bits used differ (and&n;   both may be performed simultaneously).  */
DECL|function|dcache_op
r_static
r_void
id|dcache_op
(paren
r_int
r_int
id|flags
)paren
(brace
multiline_comment|/* 1. Read the data cache control register (DCC) and confirm that bits&n;&t;      0, 1, 4, and 5 (DC00, DC01, DC04, DC05) are all cleared.  */
id|WAIT_UNTIL_CLEAR
(paren
id|V850E_CACHE_DCC
op_amp
l_int|0x33
)paren
suffix:semicolon
multiline_comment|/* 2. Clear DCC register bit 12 (DC12), bit 13 (DC13), or both&n;&t;      depending on the way for which tags are to be cleared.  */
id|V850E_CACHE_DCC
op_and_assign
op_complement
l_int|0xC000
suffix:semicolon
multiline_comment|/* 3. Set DCC register bit 0 (DC00), bit 1 (DC01) or both depending on&n;&t;      the way for which tags are to be cleared.&n;&t;      ...&n;&t;      Set DCC register bit 4 (DC04), bit 5 (DC05), or both depending&n;&t;      on the way to be data flushed.  */
id|V850E_CACHE_DCC
op_or_assign
id|flags
suffix:semicolon
multiline_comment|/* 4. Read DCC register bit DC00, DC01 [DC04, DC05], or both depending&n;&t;      on the way for which tags were cleared [flushed] and confirm&n;&t;      that that bit is cleared.  */
id|WAIT_UNTIL_CLEAR
(paren
id|V850E_CACHE_DCC
op_amp
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* V850E_CACHE_DCC */
multiline_comment|/* Flushes the contents of the dcache to memory.  */
DECL|function|flush_dcache
r_static
r_inline
r_void
id|flush_dcache
(paren
r_void
)paren
(brace
macro_line|#ifdef V850E_CACHE_DCC
multiline_comment|/* We only need to do something if in write-back mode.  */
r_if
c_cond
(paren
id|V850E_CACHE_DCC
op_amp
l_int|0x0400
)paren
id|dcache_op
(paren
l_int|0x30
)paren
suffix:semicolon
macro_line|#endif /* V850E_CACHE_DCC */
)brace
multiline_comment|/* Flushes the contents of the dcache to memory, and then clears it.  */
DECL|function|clear_dcache
r_static
r_inline
r_void
id|clear_dcache
(paren
r_void
)paren
(brace
macro_line|#ifdef V850E_CACHE_DCC
multiline_comment|/* We only need to do something if the dcache is enabled.  */
r_if
c_cond
(paren
id|V850E_CACHE_DCC
op_amp
l_int|0x0C00
)paren
id|dcache_op
(paren
l_int|0x33
)paren
suffix:semicolon
macro_line|#endif /* V850E_CACHE_DCC */
)brace
multiline_comment|/* Clears the dcache without flushing to memory first.  */
DECL|function|clear_dcache_no_flush
r_static
r_inline
r_void
id|clear_dcache_no_flush
(paren
r_void
)paren
(brace
macro_line|#ifdef V850E_CACHE_DCC
multiline_comment|/* We only need to do something if the dcache is enabled.  */
r_if
c_cond
(paren
id|V850E_CACHE_DCC
op_amp
l_int|0x0C00
)paren
id|dcache_op
(paren
l_int|0x3
)paren
suffix:semicolon
macro_line|#endif /* V850E_CACHE_DCC */
)brace
DECL|function|cache_exec_after_store
r_static
r_inline
r_void
id|cache_exec_after_store
(paren
r_void
)paren
(brace
id|flush_dcache
(paren
)paren
suffix:semicolon
id|clear_icache
(paren
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/* Exported functions.  */
DECL|function|flush_icache
r_void
id|flush_icache
(paren
r_void
)paren
(brace
id|cache_exec_after_store
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_icache_range
r_void
id|flush_icache_range
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|cache_exec_after_store
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_icache_page
r_void
id|flush_icache_page
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|cache_exec_after_store
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_icache_user_range
r_void
id|flush_icache_user_range
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|adr
comma
r_int
id|len
)paren
(brace
id|cache_exec_after_store
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_cache_sigtramp
r_void
id|flush_cache_sigtramp
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_exec_after_store
(paren
)paren
suffix:semicolon
)brace
eof
