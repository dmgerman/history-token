macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &quot;mtrr.h&quot;
multiline_comment|/*  Put the processor into a state where MTRRs can be safely set  */
DECL|function|set_mtrr_prepare_save
r_void
id|set_mtrr_prepare_save
c_func
(paren
r_struct
id|set_mtrr_context
op_star
id|ctxt
)paren
(brace
r_int
r_int
id|cr0
suffix:semicolon
multiline_comment|/*  Disable interrupts locally  */
id|local_irq_save
c_func
(paren
id|ctxt-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_intel
c_func
(paren
)paren
op_logical_or
id|is_cpu
c_func
(paren
id|CYRIX
)paren
)paren
(brace
multiline_comment|/*  Save value of CR4 and clear Page Global Enable (bit 7)  */
r_if
c_cond
(paren
id|cpu_has_pge
)paren
(brace
id|ctxt-&gt;cr4val
op_assign
id|read_cr4
c_func
(paren
)paren
suffix:semicolon
id|write_cr4
c_func
(paren
id|ctxt-&gt;cr4val
op_amp
(paren
r_int
r_char
)paren
op_complement
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*  Disable and flush caches. Note that wbinvd flushes the TLBs as&n;&t;&t;    a side-effect  */
id|cr0
op_assign
id|read_cr0
c_func
(paren
)paren
op_or
l_int|0x40000000
suffix:semicolon
id|wbinvd
c_func
(paren
)paren
suffix:semicolon
id|write_cr0
c_func
(paren
id|cr0
)paren
suffix:semicolon
id|wbinvd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_intel
c_func
(paren
)paren
)paren
multiline_comment|/*  Save MTRR state */
id|rdmsr
c_func
(paren
id|MTRRdefType_MSR
comma
id|ctxt-&gt;deftype_lo
comma
id|ctxt-&gt;deftype_hi
)paren
suffix:semicolon
r_else
multiline_comment|/* Cyrix ARRs - everything else were excluded at the top */
id|ctxt-&gt;ccr3
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
suffix:semicolon
)brace
)brace
DECL|function|set_mtrr_cache_disable
r_void
id|set_mtrr_cache_disable
c_func
(paren
r_struct
id|set_mtrr_context
op_star
id|ctxt
)paren
(brace
r_if
c_cond
(paren
id|use_intel
c_func
(paren
)paren
)paren
multiline_comment|/*  Disable MTRRs, and set the default type to uncached  */
id|mtrr_wrmsr
c_func
(paren
id|MTRRdefType_MSR
comma
id|ctxt-&gt;deftype_lo
op_amp
l_int|0xf300UL
comma
id|ctxt-&gt;deftype_hi
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|is_cpu
c_func
(paren
id|CYRIX
)paren
)paren
multiline_comment|/* Cyrix ARRs - everything else were excluded at the top */
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
(paren
id|ctxt-&gt;ccr3
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
)brace
multiline_comment|/*  Restore the processor after a set_mtrr_prepare  */
DECL|function|set_mtrr_done
r_void
id|set_mtrr_done
c_func
(paren
r_struct
id|set_mtrr_context
op_star
id|ctxt
)paren
(brace
r_if
c_cond
(paren
id|use_intel
c_func
(paren
)paren
op_logical_or
id|is_cpu
c_func
(paren
id|CYRIX
)paren
)paren
(brace
multiline_comment|/*  Flush caches and TLBs  */
id|wbinvd
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*  Restore MTRRdefType  */
r_if
c_cond
(paren
id|use_intel
c_func
(paren
)paren
)paren
multiline_comment|/* Intel (P6) standard MTRRs */
id|mtrr_wrmsr
c_func
(paren
id|MTRRdefType_MSR
comma
id|ctxt-&gt;deftype_lo
comma
id|ctxt-&gt;deftype_hi
)paren
suffix:semicolon
r_else
multiline_comment|/* Cyrix ARRs - everything else was excluded at the top */
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ctxt-&gt;ccr3
)paren
suffix:semicolon
multiline_comment|/*  Enable caches  */
id|write_cr0
c_func
(paren
id|read_cr0
c_func
(paren
)paren
op_amp
l_int|0xbfffffff
)paren
suffix:semicolon
multiline_comment|/*  Restore value of CR4  */
r_if
c_cond
(paren
id|cpu_has_pge
)paren
id|write_cr4
c_func
(paren
id|ctxt-&gt;cr4val
)paren
suffix:semicolon
)brace
multiline_comment|/*  Re-enable interrupts locally (if enabled previously)  */
id|local_irq_restore
c_func
(paren
id|ctxt-&gt;flags
)paren
suffix:semicolon
)brace
eof
