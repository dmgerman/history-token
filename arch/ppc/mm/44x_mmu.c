multiline_comment|/*&n; * Modifications by Matt Porter (mporter@mvista.com) to support&n; * PPC44x Book E processors.&n; *&n; * This file contains the routines for initializing the MMU&n; * on the 4xx series of chips.&n; *  -- paulus&n; *&n; *  Derived from arch/ppc/mm/init.c:&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)&n; *  and Cort Dougan (PReP) (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Paul Mackerras&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/bootx.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &quot;mmu_decl.h&quot;
r_extern
r_char
id|etext
(braket
)braket
comma
id|_stext
(braket
)braket
suffix:semicolon
multiline_comment|/* Used by the 44x TLB replacement exception handler.&n; * Just needed it declared someplace.&n; */
DECL|variable|tlb_44x_index
r_int
r_int
id|tlb_44x_index
op_assign
l_int|0
suffix:semicolon
DECL|variable|tlb_44x_hwater
r_int
r_int
id|tlb_44x_hwater
op_assign
l_int|62
suffix:semicolon
multiline_comment|/*&n; * &quot;Pins&quot; a 256MB TLB entry in AS0 for kernel lowmem&n; */
r_static
r_void
id|__init
DECL|function|ppc44x_pin_tlb
id|ppc44x_pin_tlb
c_func
(paren
r_int
id|slot
comma
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
)paren
(brace
r_int
r_int
id|attrib
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;&n;&t;clrrwi&t;%2,%2,10&bslash;n&bslash;&n;&t;ori&t;%2,%2,%4&bslash;n&bslash;&n;&t;clrrwi&t;%1,%1,10&bslash;n&bslash;&n;&t;li&t;%0,0&bslash;n&bslash;&n;&t;ori&t;%0,%0,%5&bslash;n&bslash;&n;&t;tlbwe&t;%2,%3,%6&bslash;n&bslash;&n;&t;tlbwe&t;%1,%3,%7&bslash;n&bslash;&n;&t;tlbwe&t;%0,%3,%8&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|attrib
)paren
comma
l_string|&quot;r&quot;
(paren
id|phys
)paren
comma
l_string|&quot;r&quot;
(paren
id|virt
)paren
comma
l_string|&quot;r&quot;
(paren
id|slot
)paren
comma
l_string|&quot;i&quot;
(paren
id|PPC44x_TLB_VALID
op_or
id|PPC44x_TLB_256M
)paren
comma
l_string|&quot;i&quot;
(paren
id|PPC44x_TLB_SW
op_or
id|PPC44x_TLB_SR
op_or
id|PPC44x_TLB_SX
op_or
id|PPC44x_TLB_G
)paren
comma
l_string|&quot;i&quot;
(paren
id|PPC44x_TLB_PAGEID
)paren
comma
l_string|&quot;i&quot;
(paren
id|PPC44x_TLB_XLAT
)paren
comma
l_string|&quot;i&quot;
(paren
id|PPC44x_TLB_ATTRIB
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * MMU_init_hw does the chip-specific initialization of the MMU hardware.&n; */
DECL|function|MMU_init_hw
r_void
id|__init
id|MMU_init_hw
c_func
(paren
r_void
)paren
(brace
id|flush_instruction_cache
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|mmu_mapin_ram
r_int
r_int
id|__init
id|mmu_mapin_ram
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|pinned_tlbs
op_assign
l_int|1
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Determine number of entries necessary to cover lowmem */
id|pinned_tlbs
op_assign
(paren
r_int
r_int
)paren
(paren
id|_ALIGN
c_func
(paren
id|total_lowmem
comma
id|PPC44x_PIN_SIZE
)paren
op_rshift
id|PPC44x_PIN_SHIFT
)paren
suffix:semicolon
multiline_comment|/* Write upper watermark to save location */
id|tlb_44x_hwater
op_assign
id|PPC44x_LOW_SLOT
op_minus
id|pinned_tlbs
suffix:semicolon
multiline_comment|/* If necessary, set additional pinned TLBs */
r_if
c_cond
(paren
id|pinned_tlbs
OG
l_int|1
)paren
r_for
c_loop
(paren
id|i
op_assign
(paren
id|PPC44x_LOW_SLOT
op_minus
(paren
id|pinned_tlbs
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|i
OL
id|PPC44x_LOW_SLOT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|phys_addr
op_assign
(paren
id|PPC44x_LOW_SLOT
op_minus
id|i
)paren
op_star
id|PPC44x_PIN_SIZE
suffix:semicolon
id|ppc44x_pin_tlb
c_func
(paren
id|i
comma
id|phys_addr
op_plus
id|PAGE_OFFSET
comma
id|phys_addr
)paren
suffix:semicolon
)brace
r_return
id|total_lowmem
suffix:semicolon
)brace
eof
