macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;mtrr.h&quot;
DECL|variable|arr3_protected
r_int
id|arr3_protected
suffix:semicolon
r_static
r_void
DECL|function|cyrix_get_arr
id|cyrix_get_arr
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
op_star
id|base
comma
r_int
r_int
op_star
id|size
comma
id|mtrr_type
op_star
id|type
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|arr
comma
id|ccr3
comma
id|rcr
comma
id|shift
suffix:semicolon
id|arr
op_assign
id|CX86_ARR_BASE
op_plus
(paren
id|reg
op_lshift
l_int|1
)paren
op_plus
id|reg
suffix:semicolon
multiline_comment|/* avoid multiplication by 3 */
multiline_comment|/* Save flags and disable interrupts */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ccr3
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
(paren
id|ccr3
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* enable MAPEN */
(paren
(paren
r_int
r_char
op_star
)paren
id|base
)paren
(braket
l_int|3
)braket
op_assign
id|getCx86
c_func
(paren
id|arr
)paren
suffix:semicolon
(paren
(paren
r_int
r_char
op_star
)paren
id|base
)paren
(braket
l_int|2
)braket
op_assign
id|getCx86
c_func
(paren
id|arr
op_plus
l_int|1
)paren
suffix:semicolon
(paren
(paren
r_int
r_char
op_star
)paren
id|base
)paren
(braket
l_int|1
)braket
op_assign
id|getCx86
c_func
(paren
id|arr
op_plus
l_int|2
)paren
suffix:semicolon
id|rcr
op_assign
id|getCx86
c_func
(paren
id|CX86_RCR_BASE
op_plus
id|reg
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ccr3
)paren
suffix:semicolon
multiline_comment|/* disable MAPEN */
multiline_comment|/* Enable interrupts if it was enabled previously */
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|shift
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|base
)paren
(braket
l_int|1
)braket
op_amp
l_int|0x0f
suffix:semicolon
op_star
id|base
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* Power of two, at least 4K on ARR0-ARR6, 256K on ARR7&n;&t; * Note: shift==0xf means 4G, this is unsupported.&n;&t; */
r_if
c_cond
(paren
id|shift
)paren
op_star
id|size
op_assign
(paren
id|reg
OL
l_int|7
ques
c_cond
l_int|0x1UL
suffix:colon
l_int|0x40UL
)paren
op_lshift
(paren
id|shift
op_minus
l_int|1
)paren
suffix:semicolon
r_else
op_star
id|size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Bit 0 is Cache Enable on ARR7, Cache Disable on ARR0-ARR6 */
r_if
c_cond
(paren
id|reg
OL
l_int|7
)paren
(brace
r_switch
c_cond
(paren
id|rcr
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|type
op_assign
id|MTRR_TYPE_UNCACHABLE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
op_star
id|type
op_assign
id|MTRR_TYPE_WRBACK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
op_star
id|type
op_assign
id|MTRR_TYPE_WRCOMB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
r_default
suffix:colon
op_star
id|type
op_assign
id|MTRR_TYPE_WRTHROUGH
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|rcr
)paren
(brace
r_case
l_int|0
suffix:colon
op_star
id|type
op_assign
id|MTRR_TYPE_UNCACHABLE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
op_star
id|type
op_assign
id|MTRR_TYPE_WRCOMB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
op_star
id|type
op_assign
id|MTRR_TYPE_WRBACK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|25
suffix:colon
r_default
suffix:colon
op_star
id|type
op_assign
id|MTRR_TYPE_WRTHROUGH
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_static
r_int
DECL|function|cyrix_get_free_region
id|cyrix_get_free_region
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
multiline_comment|/*  [SUMMARY] Get a free ARR.&n;    &lt;base&gt; The starting (base) address of the region.&n;    &lt;size&gt; The size (in bytes) of the region.&n;    [RETURNS] The index of the region on success, else -1 on error.&n;*/
(brace
r_int
id|i
suffix:semicolon
id|mtrr_type
id|ltype
suffix:semicolon
r_int
r_int
id|lbase
comma
id|lsize
suffix:semicolon
multiline_comment|/* If we are to set up a region &gt;32M then look at ARR7 immediately */
r_if
c_cond
(paren
id|size
OG
l_int|0x2000
)paren
(brace
id|cyrix_get_arr
c_func
(paren
l_int|7
comma
op_amp
id|lbase
comma
op_amp
id|lsize
comma
op_amp
id|ltype
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lsize
op_eq
l_int|0
)paren
r_return
l_int|7
suffix:semicolon
multiline_comment|/*  Else try ARR0-ARR6 first  */
)brace
r_else
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
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cyrix_get_arr
c_func
(paren
id|i
comma
op_amp
id|lbase
comma
op_amp
id|lsize
comma
op_amp
id|ltype
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_eq
l_int|3
)paren
op_logical_and
id|arr3_protected
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|lsize
op_eq
l_int|0
)paren
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/* ARR0-ARR6 isn&squot;t free, try ARR7 but its size must be at least 256K */
id|cyrix_get_arr
c_func
(paren
id|i
comma
op_amp
id|lbase
comma
op_amp
id|lsize
comma
op_amp
id|ltype
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lsize
op_eq
l_int|0
)paren
op_logical_and
(paren
id|size
op_ge
l_int|0x40
)paren
)paren
r_return
id|i
suffix:semicolon
)brace
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
DECL|function|cyrix_set_arr
r_static
r_void
id|cyrix_set_arr
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
id|mtrr_type
id|type
)paren
(brace
r_int
r_char
id|arr
comma
id|arr_type
comma
id|arr_size
suffix:semicolon
id|u32
id|cr0
comma
id|ccr3
suffix:semicolon
id|u32
id|cr4
op_assign
l_int|0
suffix:semicolon
id|arr
op_assign
id|CX86_ARR_BASE
op_plus
(paren
id|reg
op_lshift
l_int|1
)paren
op_plus
id|reg
suffix:semicolon
multiline_comment|/* avoid multiplication by 3 */
multiline_comment|/* count down from 32M (ARR0-ARR6) or from 2G (ARR7) */
r_if
c_cond
(paren
id|reg
op_ge
l_int|7
)paren
id|size
op_rshift_assign
l_int|6
suffix:semicolon
id|size
op_and_assign
l_int|0x7fff
suffix:semicolon
multiline_comment|/* make sure arr_size &lt;= 14 */
r_for
c_loop
(paren
id|arr_size
op_assign
l_int|0
suffix:semicolon
id|size
suffix:semicolon
id|arr_size
op_increment
comma
id|size
op_rshift_assign
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
OL
l_int|7
)paren
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|MTRR_TYPE_UNCACHABLE
suffix:colon
id|arr_type
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRR_TYPE_WRCOMB
suffix:colon
id|arr_type
op_assign
l_int|9
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRR_TYPE_WRTHROUGH
suffix:colon
id|arr_type
op_assign
l_int|24
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|arr_type
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|MTRR_TYPE_UNCACHABLE
suffix:colon
id|arr_type
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRR_TYPE_WRCOMB
suffix:colon
id|arr_type
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTRR_TYPE_WRTHROUGH
suffix:colon
id|arr_type
op_assign
l_int|25
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|arr_type
op_assign
l_int|9
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*  Save value of CR4 and clear Page Global Enable (bit 7)  */
r_if
c_cond
(paren
id|cpu_has_pge
)paren
(brace
id|cr4
op_assign
id|read_cr4
c_func
(paren
)paren
suffix:semicolon
id|write_cr4
c_func
(paren
id|cr4
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
multiline_comment|/*  Disable and flush caches. Note that wbinvd flushes the TLBs as&n;&t;    a side-effect  */
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
multiline_comment|/* Cyrix ARRs - everything else were excluded at the top */
id|ccr3
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
suffix:semicolon
multiline_comment|/* Cyrix ARRs - everything else were excluded at the top */
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
(paren
id|ccr3
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
id|base
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|setCx86
c_func
(paren
id|arr
comma
(paren
(paren
r_int
r_char
op_star
)paren
op_amp
id|base
)paren
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|arr
op_plus
l_int|1
comma
(paren
(paren
r_int
r_char
op_star
)paren
op_amp
id|base
)paren
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|arr
op_plus
l_int|2
comma
(paren
(paren
(paren
r_int
r_char
op_star
)paren
op_amp
id|base
)paren
(braket
l_int|1
)braket
)paren
op_or
id|arr_size
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_RCR_BASE
op_plus
id|reg
comma
id|arr_type
)paren
suffix:semicolon
multiline_comment|/*  Flush caches and TLBs  */
id|wbinvd
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Cyrix ARRs - everything else was excluded at the top */
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ccr3
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
id|cr4
)paren
suffix:semicolon
)brace
r_typedef
r_struct
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|type
id|mtrr_type
id|type
suffix:semicolon
DECL|typedef|arr_state_t
)brace
id|arr_state_t
suffix:semicolon
DECL|variable|__initdata
id|arr_state_t
id|arr_state
(braket
l_int|8
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0UL
comma
l_int|0UL
comma
l_int|0UL
)brace
comma
(brace
l_int|0UL
comma
l_int|0UL
comma
l_int|0UL
)brace
comma
(brace
l_int|0UL
comma
l_int|0UL
comma
l_int|0UL
)brace
comma
(brace
l_int|0UL
comma
l_int|0UL
comma
l_int|0UL
)brace
comma
(brace
l_int|0UL
comma
l_int|0UL
comma
l_int|0UL
)brace
comma
(brace
l_int|0UL
comma
l_int|0UL
comma
l_int|0UL
)brace
comma
(brace
l_int|0UL
comma
l_int|0UL
comma
l_int|0UL
)brace
comma
(brace
l_int|0UL
comma
l_int|0UL
comma
l_int|0UL
)brace
)brace
suffix:semicolon
DECL|variable|__initdata
r_int
r_char
id|ccr_state
(braket
l_int|7
)braket
id|__initdata
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_static
r_void
id|__init
DECL|function|cyrix_arr_init_secondary
id|cyrix_arr_init_secondary
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
id|cr0
comma
id|ccr3
comma
id|cr4
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* flush cache and enable MAPEN */
multiline_comment|/*  Save value of CR4 and clear Page Global Enable (bit 7)  */
r_if
c_cond
(paren
id|cpu_has_pge
)paren
(brace
id|cr4
op_assign
id|read_cr4
c_func
(paren
)paren
suffix:semicolon
id|write_cr4
c_func
(paren
id|cr4
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
multiline_comment|/*  Disable and flush caches. Note that wbinvd flushes the TLBs as&n;&t;    a side-effect  */
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
multiline_comment|/* Cyrix ARRs - everything else were excluded at the top */
id|ccr3
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
suffix:semicolon
multiline_comment|/* Cyrix ARRs - everything else were excluded at the top */
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
(paren
id|ccr3
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* the CCRs are not contiguous */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|setCx86
c_func
(paren
id|CX86_CCR0
op_plus
id|i
comma
id|ccr_state
(braket
id|i
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
id|setCx86
c_func
(paren
id|CX86_CCR4
op_plus
id|i
comma
id|ccr_state
(braket
id|i
)braket
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|cyrix_set_arr
c_func
(paren
id|i
comma
id|arr_state
(braket
id|i
)braket
dot
id|base
comma
id|arr_state
(braket
id|i
)braket
dot
id|size
comma
id|arr_state
(braket
id|i
)braket
dot
id|type
)paren
suffix:semicolon
multiline_comment|/*  Flush caches and TLBs  */
id|wbinvd
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Cyrix ARRs - everything else was excluded at the top */
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ccr3
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
id|cr4
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * On Cyrix 6x86(MX) and M II the ARR3 is special: it has connection&n; * with the SMM (System Management Mode) mode. So we need the following:&n; * Check whether SMI_LOCK (CCR3 bit 0) is set&n; *   if it is set, write a warning message: ARR3 cannot be changed!&n; *     (it cannot be changed until the next processor reset)&n; *   if it is reset, then we can change it, set all the needed bits:&n; *   - disable access to SMM memory through ARR3 range (CCR1 bit 7 reset)&n; *   - disable access to SMM memory (CCR1 bit 2 reset)&n; *   - disable SMM mode (CCR1 bit 1 reset)&n; *   - disable write protection of ARR3 (CCR6 bit 1 reset)&n; *   - (maybe) disable ARR3&n; * Just to be sure, we enable ARR usage by the processor (CCR5 bit 5 set)&n; */
r_static
r_void
id|__init
DECL|function|cyrix_arr_init
id|cyrix_arr_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|set_mtrr_context
id|ctxt
suffix:semicolon
r_int
r_char
id|ccr
(braket
l_int|7
)braket
suffix:semicolon
r_int
id|ccrc
(braket
l_int|7
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_int
id|i
suffix:semicolon
macro_line|#endif
multiline_comment|/* flush cache and enable MAPEN */
id|set_mtrr_prepare_save
c_func
(paren
op_amp
id|ctxt
)paren
suffix:semicolon
id|set_mtrr_cache_disable
c_func
(paren
op_amp
id|ctxt
)paren
suffix:semicolon
multiline_comment|/* Save all CCRs locally */
id|ccr
(braket
l_int|0
)braket
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR0
)paren
suffix:semicolon
id|ccr
(braket
l_int|1
)braket
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR1
)paren
suffix:semicolon
id|ccr
(braket
l_int|2
)braket
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR2
)paren
suffix:semicolon
id|ccr
(braket
l_int|3
)braket
op_assign
id|ctxt.ccr3
suffix:semicolon
id|ccr
(braket
l_int|4
)braket
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR4
)paren
suffix:semicolon
id|ccr
(braket
l_int|5
)braket
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR5
)paren
suffix:semicolon
id|ccr
(braket
l_int|6
)braket
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR6
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccr
(braket
l_int|3
)braket
op_amp
l_int|1
)paren
(brace
id|ccrc
(braket
l_int|3
)braket
op_assign
l_int|1
suffix:semicolon
id|arr3_protected
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Disable SMM mode (bit 1), access to SMM memory (bit 2) and&n;&t;&t; * access to SMM memory through ARR3 (bit 7).&n;&t;&t; */
r_if
c_cond
(paren
id|ccr
(braket
l_int|1
)braket
op_amp
l_int|0x80
)paren
(brace
id|ccr
(braket
l_int|1
)braket
op_and_assign
l_int|0x7f
suffix:semicolon
id|ccrc
(braket
l_int|1
)braket
op_or_assign
l_int|0x80
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ccr
(braket
l_int|1
)braket
op_amp
l_int|0x04
)paren
(brace
id|ccr
(braket
l_int|1
)braket
op_and_assign
l_int|0xfb
suffix:semicolon
id|ccrc
(braket
l_int|1
)braket
op_or_assign
l_int|0x04
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ccr
(braket
l_int|1
)braket
op_amp
l_int|0x02
)paren
(brace
id|ccr
(braket
l_int|1
)braket
op_and_assign
l_int|0xfd
suffix:semicolon
id|ccrc
(braket
l_int|1
)braket
op_or_assign
l_int|0x02
suffix:semicolon
)brace
id|arr3_protected
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ccr
(braket
l_int|6
)braket
op_amp
l_int|0x02
)paren
(brace
id|ccr
(braket
l_int|6
)braket
op_and_assign
l_int|0xfd
suffix:semicolon
id|ccrc
(braket
l_int|6
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Disable write protection of ARR3 */
id|setCx86
c_func
(paren
id|CX86_CCR6
comma
id|ccr
(braket
l_int|6
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Disable ARR3. This is safe now that we disabled SMM. */
multiline_comment|/* cyrix_set_arr_up (3, 0, 0, 0, FALSE); */
)brace
multiline_comment|/* If we changed CCR1 in memory, change it in the processor, too. */
r_if
c_cond
(paren
id|ccrc
(braket
l_int|1
)braket
)paren
id|setCx86
c_func
(paren
id|CX86_CCR1
comma
id|ccr
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* Enable ARR usage by the processor */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ccr
(braket
l_int|5
)braket
op_amp
l_int|0x20
)paren
)paren
(brace
id|ccr
(braket
l_int|5
)braket
op_or_assign
l_int|0x20
suffix:semicolon
id|ccrc
(braket
l_int|5
)braket
op_assign
l_int|1
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR5
comma
id|ccr
(braket
l_int|5
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
id|ccr_state
(braket
id|i
)braket
op_assign
id|ccr
(braket
id|i
)braket
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|cyrix_get_arr
c_func
(paren
id|i
comma
op_amp
id|arr_state
(braket
id|i
)braket
dot
id|base
comma
op_amp
id|arr_state
(braket
id|i
)braket
dot
id|size
comma
op_amp
id|arr_state
(braket
id|i
)braket
dot
id|type
)paren
suffix:semicolon
macro_line|#endif
id|set_mtrr_done
c_func
(paren
op_amp
id|ctxt
)paren
suffix:semicolon
multiline_comment|/* flush cache and disable MAPEN */
r_if
c_cond
(paren
id|ccrc
(braket
l_int|5
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;mtrr: ARR usage was not enabled, enabled manually&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccrc
(braket
l_int|3
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;mtrr: ARR3 cannot be changed&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;    if ( ccrc[1] &amp; 0x80) printk (&quot;mtrr: SMM memory access through ARR3 disabled&bslash;n&quot;);&n;    if ( ccrc[1] &amp; 0x04) printk (&quot;mtrr: SMM memory access disabled&bslash;n&quot;);&n;    if ( ccrc[1] &amp; 0x02) printk (&quot;mtrr: SMM mode disabled&bslash;n&quot;);&n;*/
r_if
c_cond
(paren
id|ccrc
(braket
l_int|6
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;mtrr: ARR3 was write protected, unprotected&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|cyrix_mtrr_ops
r_static
r_struct
id|mtrr_ops
id|cyrix_mtrr_ops
op_assign
(brace
dot
id|vendor
op_assign
id|X86_VENDOR_CYRIX
comma
dot
id|init
op_assign
id|cyrix_arr_init
comma
dot
id|init_secondary
op_assign
id|cyrix_arr_init_secondary
comma
dot
id|set
op_assign
id|cyrix_set_arr
comma
dot
id|get
op_assign
id|cyrix_get_arr
comma
dot
id|get_free_region
op_assign
id|cyrix_get_free_region
comma
dot
id|validate_add_page
op_assign
id|generic_validate_add_page
comma
dot
id|have_wrcomb
op_assign
id|positive_have_wrcomb
comma
)brace
suffix:semicolon
DECL|function|cyrix_init_mtrr
r_int
id|__init
id|cyrix_init_mtrr
c_func
(paren
r_void
)paren
(brace
id|set_mtrr_ops
c_func
(paren
op_amp
id|cyrix_mtrr_ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//arch_initcall(cyrix_init_mtrr);
eof
