multiline_comment|/*&n; * arch/sh/mm/tlb-sh3.c&n; *&n; * SH-3 specific TLB operations&n; *&n; * Copyright (C) 1999  Niibe Yutaka&n; * Copyright (C) 2002  Paul Mundt&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
DECL|function|update_mmu_cache
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|pteval
suffix:semicolon
r_int
r_int
id|vpn
suffix:semicolon
multiline_comment|/* Ptrace may call this routine. */
r_if
c_cond
(paren
id|vma
op_logical_and
id|current-&gt;active_mm
op_ne
id|vma-&gt;vm_mm
)paren
r_return
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Set PTEH register */
id|vpn
op_assign
(paren
id|address
op_amp
id|MMU_VPN_MASK
)paren
op_or
id|get_asid
c_func
(paren
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|vpn
comma
id|MMU_PTEH
)paren
suffix:semicolon
id|pteval
op_assign
id|pte_val
c_func
(paren
id|pte
)paren
suffix:semicolon
multiline_comment|/* Set PTEL register */
id|pteval
op_and_assign
id|_PAGE_FLAGS_HARDWARE_MASK
suffix:semicolon
multiline_comment|/* drop software flags */
multiline_comment|/* conveniently, we want all the software flags to be 0 anyway */
id|ctrl_outl
c_func
(paren
id|pteval
comma
id|MMU_PTEL
)paren
suffix:semicolon
multiline_comment|/* Load the TLB */
id|asm
r_volatile
(paren
l_string|&quot;ldtlb&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
multiline_comment|/* no input */
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|__flush_tlb_page
r_void
id|__flush_tlb_page
c_func
(paren
r_int
r_int
id|asid
comma
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|addr
comma
id|data
suffix:semicolon
multiline_comment|/*&n;&t; * NOTE: PTEH.ASID should be set to this MM&n;&t; *       _AND_ we need to write ASID to the array.&n;&t; *&n;&t; * It would be simple if we didn&squot;t need to set PTEH.ASID...&n;&t; */
id|addr
op_assign
id|MMU_TLB_ADDRESS_ARRAY
op_or
(paren
id|page
op_amp
l_int|0x1F000
)paren
op_or
id|MMU_PAGE_ASSOC_BIT
suffix:semicolon
id|data
op_assign
(paren
id|page
op_amp
l_int|0xfffe0000
)paren
op_or
id|asid
suffix:semicolon
multiline_comment|/* VALID bit is off */
id|ctrl_outl
c_func
(paren
id|data
comma
id|addr
)paren
suffix:semicolon
)brace
eof
