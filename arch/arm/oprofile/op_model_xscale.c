multiline_comment|/**&n; * @file op_model_xscale.c&n; * XScale Performance Monitor Driver&n; *&n; * @remark Copyright 2000-2004 Deepak Saxena &lt;dsaxena@mvista.com&gt;&n; * @remark Copyright 2000-2004 MontaVista Software Inc&n; * @remark Copyright 2004 Dave Jiang &lt;dave.jiang@intel.com&gt;&n; * @remark Copyright 2004 Intel Corporation&n; * @remark Copyright 2004 Zwane Mwaikambo &lt;zwane@arm.linux.org.uk&gt;&n; * @remark Copyright 2004 Oprofile Authors&n; *&n; * @remark Read the file COPYING&n; *&n; * @author Zwane Mwaikambo&n; */
multiline_comment|/* #define DEBUG */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#include &quot;op_counter.h&quot;
macro_line|#include &quot;op_arm_model.h&quot;
DECL|macro|PMU_ENABLE
mdefine_line|#define&t;PMU_ENABLE&t;0x001&t;/* Enable counters */
DECL|macro|PMN_RESET
mdefine_line|#define PMN_RESET&t;0x002&t;/* Reset event counters */
DECL|macro|CCNT_RESET
mdefine_line|#define&t;CCNT_RESET&t;0x004&t;/* Reset clock counter */
DECL|macro|PMU_RESET
mdefine_line|#define&t;PMU_RESET&t;(CCNT_RESET | PMN_RESET)
multiline_comment|/* TODO do runtime detection */
macro_line|#ifdef CONFIG_ARCH_IOP310
DECL|macro|XSCALE_PMU_IRQ
mdefine_line|#define XSCALE_PMU_IRQ  IRQ_XS80200_PMU
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_IOP321
DECL|macro|XSCALE_PMU_IRQ
mdefine_line|#define XSCALE_PMU_IRQ  IRQ_IOP321_CORE_PMU
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_IOP331
DECL|macro|XSCALE_PMU_IRQ
mdefine_line|#define XSCALE_PMU_IRQ  IRQ_IOP331_CORE_PMU
macro_line|#endif
multiline_comment|/*&n; * Different types of events that can be counted by the XScale PMU&n; * as used by Oprofile userspace. Here primarily for documentation&n; * purposes.&n; */
DECL|macro|EVT_ICACHE_MISS
mdefine_line|#define EVT_ICACHE_MISS&t;&t;&t;0x00
DECL|macro|EVT_ICACHE_NO_DELIVER
mdefine_line|#define&t;EVT_ICACHE_NO_DELIVER&t;&t;0x01
DECL|macro|EVT_DATA_STALL
mdefine_line|#define&t;EVT_DATA_STALL&t;&t;&t;0x02
DECL|macro|EVT_ITLB_MISS
mdefine_line|#define&t;EVT_ITLB_MISS&t;&t;&t;0x03
DECL|macro|EVT_DTLB_MISS
mdefine_line|#define&t;EVT_DTLB_MISS&t;&t;&t;0x04
DECL|macro|EVT_BRANCH
mdefine_line|#define&t;EVT_BRANCH&t;&t;&t;0x05
DECL|macro|EVT_BRANCH_MISS
mdefine_line|#define&t;EVT_BRANCH_MISS&t;&t;&t;0x06
DECL|macro|EVT_INSTRUCTION
mdefine_line|#define&t;EVT_INSTRUCTION&t;&t;&t;0x07
DECL|macro|EVT_DCACHE_FULL_STALL
mdefine_line|#define&t;EVT_DCACHE_FULL_STALL&t;&t;0x08
DECL|macro|EVT_DCACHE_FULL_STALL_CONTIG
mdefine_line|#define&t;EVT_DCACHE_FULL_STALL_CONTIG&t;0x09
DECL|macro|EVT_DCACHE_ACCESS
mdefine_line|#define&t;EVT_DCACHE_ACCESS&t;&t;0x0A
DECL|macro|EVT_DCACHE_MISS
mdefine_line|#define&t;EVT_DCACHE_MISS&t;&t;&t;0x0B
DECL|macro|EVT_DCACE_WRITE_BACK
mdefine_line|#define&t;EVT_DCACE_WRITE_BACK&t;&t;0x0C
DECL|macro|EVT_PC_CHANGED
mdefine_line|#define&t;EVT_PC_CHANGED&t;&t;&t;0x0D
DECL|macro|EVT_BCU_REQUEST
mdefine_line|#define&t;EVT_BCU_REQUEST&t;&t;&t;0x10
DECL|macro|EVT_BCU_FULL
mdefine_line|#define&t;EVT_BCU_FULL&t;&t;&t;0x11
DECL|macro|EVT_BCU_DRAIN
mdefine_line|#define&t;EVT_BCU_DRAIN&t;&t;&t;0x12
DECL|macro|EVT_BCU_ECC_NO_ELOG
mdefine_line|#define&t;EVT_BCU_ECC_NO_ELOG&t;&t;0x14
DECL|macro|EVT_BCU_1_BIT_ERR
mdefine_line|#define&t;EVT_BCU_1_BIT_ERR&t;&t;0x15
DECL|macro|EVT_RMW
mdefine_line|#define&t;EVT_RMW&t;&t;&t;&t;0x16
multiline_comment|/* EVT_CCNT is not hardware defined */
DECL|macro|EVT_CCNT
mdefine_line|#define EVT_CCNT&t;&t;&t;0xFE
DECL|macro|EVT_UNUSED
mdefine_line|#define EVT_UNUSED&t;&t;&t;0xFF
DECL|struct|pmu_counter
r_struct
id|pmu_counter
(brace
DECL|member|ovf
r_volatile
r_int
r_int
id|ovf
suffix:semicolon
DECL|member|reset_counter
r_int
r_int
id|reset_counter
suffix:semicolon
)brace
suffix:semicolon
DECL|enumerator|CCNT
DECL|enumerator|PMN0
DECL|enumerator|PMN1
DECL|enumerator|PMN2
DECL|enumerator|PMN3
DECL|enumerator|MAX_COUNTERS
r_enum
(brace
id|CCNT
comma
id|PMN0
comma
id|PMN1
comma
id|PMN2
comma
id|PMN3
comma
id|MAX_COUNTERS
)brace
suffix:semicolon
DECL|variable|results
r_static
r_struct
id|pmu_counter
id|results
(braket
id|MAX_COUNTERS
)braket
suffix:semicolon
multiline_comment|/*&n; * There are two versions of the PMU in current XScale processors&n; * with differing register layouts and number of performance counters.&n; * e.g. IOP321 is xsc1 whilst IOP331 is xsc2.&n; * We detect which register layout to use in xscale_detect_pmu()&n; */
DECL|enumerator|PMU_XSC1
DECL|enumerator|PMU_XSC2
r_enum
(brace
id|PMU_XSC1
comma
id|PMU_XSC2
)brace
suffix:semicolon
DECL|struct|pmu_type
r_struct
id|pmu_type
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|num_counters
r_int
id|num_counters
suffix:semicolon
DECL|member|int_enable
r_int
r_int
id|int_enable
suffix:semicolon
DECL|member|cnt_ovf
r_int
r_int
id|cnt_ovf
(braket
id|MAX_COUNTERS
)braket
suffix:semicolon
DECL|member|int_mask
r_int
r_int
id|int_mask
(braket
id|MAX_COUNTERS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|pmu_parms
r_static
r_struct
id|pmu_type
id|pmu_parms
(braket
)braket
op_assign
(brace
(brace
dot
id|id
op_assign
id|PMU_XSC1
comma
dot
id|name
op_assign
l_string|&quot;arm/xscale1&quot;
comma
dot
id|num_counters
op_assign
l_int|3
comma
dot
id|int_mask
op_assign
(brace
(braket
id|PMN0
)braket
op_assign
l_int|0x10
comma
(braket
id|PMN1
)braket
op_assign
l_int|0x20
comma
(braket
id|CCNT
)braket
op_assign
l_int|0x40
)brace
comma
dot
id|cnt_ovf
op_assign
(brace
(braket
id|CCNT
)braket
op_assign
l_int|0x400
comma
(braket
id|PMN0
)braket
op_assign
l_int|0x100
comma
(braket
id|PMN1
)braket
op_assign
l_int|0x200
)brace
comma
)brace
comma
(brace
dot
id|id
op_assign
id|PMU_XSC2
comma
dot
id|name
op_assign
l_string|&quot;arm/xscale2&quot;
comma
dot
id|num_counters
op_assign
l_int|5
comma
dot
id|int_mask
op_assign
(brace
(braket
id|CCNT
)braket
op_assign
l_int|0x01
comma
(braket
id|PMN0
)braket
op_assign
l_int|0x02
comma
(braket
id|PMN1
)braket
op_assign
l_int|0x04
comma
(braket
id|PMN2
)braket
op_assign
l_int|0x08
comma
(braket
id|PMN3
)braket
op_assign
l_int|0x10
)brace
comma
dot
id|cnt_ovf
op_assign
(brace
(braket
id|CCNT
)braket
op_assign
l_int|0x01
comma
(braket
id|PMN0
)braket
op_assign
l_int|0x02
comma
(braket
id|PMN1
)braket
op_assign
l_int|0x04
comma
(braket
id|PMN2
)braket
op_assign
l_int|0x08
comma
(braket
id|PMN3
)braket
op_assign
l_int|0x10
)brace
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|pmu
r_static
r_struct
id|pmu_type
op_star
id|pmu
suffix:semicolon
DECL|function|write_pmnc
r_static
r_void
id|write_pmnc
c_func
(paren
id|u32
id|val
)paren
(brace
multiline_comment|/* upper 4bits and 7, 11 are write-as-0 */
id|val
op_and_assign
l_int|0xffff77f
suffix:semicolon
r_if
c_cond
(paren
id|pmu-&gt;id
op_eq
id|PMU_XSC1
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c0, c0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c0, c1, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|read_pmnc
r_static
id|u32
id|read_pmnc
c_func
(paren
r_void
)paren
(brace
id|u32
id|val
suffix:semicolon
r_if
c_cond
(paren
id|pmu-&gt;id
op_eq
id|PMU_XSC1
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c0, c0, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c0, c1, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|__xsc1_read_counter
r_static
id|u32
id|__xsc1_read_counter
c_func
(paren
r_int
id|counter
)paren
(brace
id|u32
id|val
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|counter
)paren
(brace
r_case
id|CCNT
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c1, c0, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN0
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c2, c0, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c3, c0, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|function|__xsc2_read_counter
r_static
id|u32
id|__xsc2_read_counter
c_func
(paren
r_int
id|counter
)paren
(brace
id|u32
id|val
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|counter
)paren
(brace
r_case
id|CCNT
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c1, c1, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN0
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c0, c2, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c1, c2, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c2, c2, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN3
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c3, c2, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|function|read_counter
r_static
id|u32
id|read_counter
c_func
(paren
r_int
id|counter
)paren
(brace
id|u32
id|val
suffix:semicolon
r_if
c_cond
(paren
id|pmu-&gt;id
op_eq
id|PMU_XSC1
)paren
id|val
op_assign
id|__xsc1_read_counter
c_func
(paren
id|counter
)paren
suffix:semicolon
r_else
id|val
op_assign
id|__xsc2_read_counter
c_func
(paren
id|counter
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|__xsc1_write_counter
r_static
r_void
id|__xsc1_write_counter
c_func
(paren
r_int
id|counter
comma
id|u32
id|val
)paren
(brace
r_switch
c_cond
(paren
id|counter
)paren
(brace
r_case
id|CCNT
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c1, c0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN0
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c2, c0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c3, c0, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|__xsc2_write_counter
r_static
r_void
id|__xsc2_write_counter
c_func
(paren
r_int
id|counter
comma
id|u32
id|val
)paren
(brace
r_switch
c_cond
(paren
id|counter
)paren
(brace
r_case
id|CCNT
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c1, c1, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN0
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c0, c2, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c1, c2, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c2, c2, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMN3
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c3, c2, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|write_counter
r_static
r_void
id|write_counter
c_func
(paren
r_int
id|counter
comma
id|u32
id|val
)paren
(brace
r_if
c_cond
(paren
id|pmu-&gt;id
op_eq
id|PMU_XSC1
)paren
id|__xsc1_write_counter
c_func
(paren
id|counter
comma
id|val
)paren
suffix:semicolon
r_else
id|__xsc2_write_counter
c_func
(paren
id|counter
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|xscale_setup_ctrs
r_static
r_int
id|xscale_setup_ctrs
c_func
(paren
r_void
)paren
(brace
id|u32
id|evtsel
comma
id|pmnc
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|CCNT
suffix:semicolon
id|i
OL
id|MAX_COUNTERS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|counter_config
(braket
id|i
)braket
dot
id|event
)paren
r_continue
suffix:semicolon
id|counter_config
(braket
id|i
)braket
dot
id|event
op_assign
id|EVT_UNUSED
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|pmu-&gt;id
)paren
(brace
r_case
id|PMU_XSC1
suffix:colon
id|pmnc
op_assign
(paren
id|counter_config
(braket
id|PMN1
)braket
dot
id|event
op_lshift
l_int|20
)paren
op_or
(paren
id|counter_config
(braket
id|PMN0
)braket
dot
id|event
op_lshift
l_int|12
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;xscale_setup_ctrs: pmnc: %#08x&bslash;n&quot;
comma
id|pmnc
)paren
suffix:semicolon
id|write_pmnc
c_func
(paren
id|pmnc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PMU_XSC2
suffix:colon
id|evtsel
op_assign
id|counter_config
(braket
id|PMN0
)braket
dot
id|event
op_or
(paren
id|counter_config
(braket
id|PMN1
)braket
dot
id|event
op_lshift
l_int|8
)paren
op_or
(paren
id|counter_config
(braket
id|PMN2
)braket
dot
id|event
op_lshift
l_int|16
)paren
op_or
(paren
id|counter_config
(braket
id|PMN3
)braket
dot
id|event
op_lshift
l_int|24
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;xscale_setup_ctrs: evtsel %#08x&bslash;n&quot;
comma
id|evtsel
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c8, c1, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|evtsel
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|CCNT
suffix:semicolon
id|i
OL
id|MAX_COUNTERS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|counter_config
(braket
id|i
)braket
dot
id|event
op_eq
id|EVT_UNUSED
)paren
(brace
id|counter_config
(braket
id|i
)braket
dot
id|event
op_assign
l_int|0
suffix:semicolon
id|pmu-&gt;int_enable
op_and_assign
op_complement
id|pmu-&gt;int_mask
(braket
id|i
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|results
(braket
id|i
)braket
dot
id|reset_counter
op_assign
id|counter_config
(braket
id|i
)braket
dot
id|count
suffix:semicolon
id|write_counter
c_func
(paren
id|i
comma
op_minus
(paren
id|u32
)paren
id|counter_config
(braket
id|i
)braket
dot
id|count
)paren
suffix:semicolon
id|pmu-&gt;int_enable
op_or_assign
id|pmu-&gt;int_mask
(braket
id|i
)braket
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;xscale_setup_ctrs: counter%d %#08x from %#08lx&bslash;n&quot;
comma
id|i
comma
id|read_counter
c_func
(paren
id|i
)paren
comma
id|counter_config
(braket
id|i
)braket
dot
id|count
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__xsc1_check_ctrs
r_static
r_void
r_inline
id|__xsc1_check_ctrs
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
id|pmnc
op_assign
id|read_pmnc
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* NOTE: there&squot;s an A stepping errata that states if an overflow */
multiline_comment|/*       bit already exists and another occurs, the previous     */
multiline_comment|/*       Overflow bit gets cleared. There&squot;s no workaround.&t; */
multiline_comment|/*&t; Fixed in B stepping or later&t;&t;&t; &t; */
id|pmnc
op_and_assign
op_complement
(paren
id|PMU_ENABLE
op_or
id|pmu-&gt;cnt_ovf
(braket
id|PMN0
)braket
op_or
id|pmu-&gt;cnt_ovf
(braket
id|PMN1
)braket
op_or
id|pmu-&gt;cnt_ovf
(braket
id|CCNT
)braket
)paren
suffix:semicolon
id|write_pmnc
c_func
(paren
id|pmnc
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|CCNT
suffix:semicolon
id|i
op_le
id|PMN1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pmu-&gt;int_mask
(braket
id|i
)braket
op_amp
id|pmu-&gt;int_enable
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pmnc
op_amp
id|pmu-&gt;cnt_ovf
(braket
id|i
)braket
)paren
id|results
(braket
id|i
)braket
dot
id|ovf
op_increment
suffix:semicolon
)brace
)brace
DECL|function|__xsc2_check_ctrs
r_static
r_void
r_inline
id|__xsc2_check_ctrs
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
id|flag
op_assign
l_int|0
comma
id|pmnc
op_assign
id|read_pmnc
c_func
(paren
)paren
suffix:semicolon
id|pmnc
op_and_assign
op_complement
id|PMU_ENABLE
suffix:semicolon
id|write_pmnc
c_func
(paren
id|pmnc
)paren
suffix:semicolon
multiline_comment|/* read overflow flag register */
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p14, 0, %0, c5, c1, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|flag
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|CCNT
suffix:semicolon
id|i
op_le
id|PMN3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pmu-&gt;int_mask
(braket
id|i
)braket
op_amp
id|pmu-&gt;int_enable
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_amp
id|pmu-&gt;cnt_ovf
(braket
id|i
)braket
)paren
id|results
(braket
id|i
)braket
dot
id|ovf
op_increment
suffix:semicolon
)brace
multiline_comment|/* writeback clears overflow bits */
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c5, c1, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|flag
)paren
)paren
suffix:semicolon
)brace
DECL|function|xscale_pmu_interrupt
r_static
id|irqreturn_t
id|xscale_pmu_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|arg
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|eip
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_int
id|i
comma
id|is_kernel
op_assign
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
suffix:semicolon
id|u32
id|pmnc
suffix:semicolon
r_if
c_cond
(paren
id|pmu-&gt;id
op_eq
id|PMU_XSC1
)paren
id|__xsc1_check_ctrs
c_func
(paren
)paren
suffix:semicolon
r_else
id|__xsc2_check_ctrs
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|CCNT
suffix:semicolon
id|i
OL
id|MAX_COUNTERS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|results
(braket
id|i
)braket
dot
id|ovf
)paren
r_continue
suffix:semicolon
id|write_counter
c_func
(paren
id|i
comma
op_minus
(paren
id|u32
)paren
id|results
(braket
id|i
)braket
dot
id|reset_counter
)paren
suffix:semicolon
id|oprofile_add_sample
c_func
(paren
id|eip
comma
id|is_kernel
comma
id|i
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|results
(braket
id|i
)braket
dot
id|ovf
op_decrement
suffix:semicolon
)brace
id|pmnc
op_assign
id|read_pmnc
c_func
(paren
)paren
op_or
id|PMU_ENABLE
suffix:semicolon
id|write_pmnc
c_func
(paren
id|pmnc
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|xscale_pmu_stop
r_static
r_void
id|xscale_pmu_stop
c_func
(paren
r_void
)paren
(brace
id|u32
id|pmnc
op_assign
id|read_pmnc
c_func
(paren
)paren
suffix:semicolon
id|pmnc
op_and_assign
op_complement
id|PMU_ENABLE
suffix:semicolon
id|write_pmnc
c_func
(paren
id|pmnc
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|XSCALE_PMU_IRQ
comma
id|results
)paren
suffix:semicolon
)brace
DECL|function|xscale_pmu_start
r_static
r_int
id|xscale_pmu_start
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u32
id|pmnc
op_assign
id|read_pmnc
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|XSCALE_PMU_IRQ
comma
id|xscale_pmu_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;XScale PMU&quot;
comma
(paren
r_void
op_star
)paren
id|results
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;oprofile: unable to request IRQ%d for XScale PMU&bslash;n&quot;
comma
id|XSCALE_PMU_IRQ
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmu-&gt;id
op_eq
id|PMU_XSC1
)paren
id|pmnc
op_or_assign
id|pmu-&gt;int_enable
suffix:semicolon
r_else
id|__asm__
id|__volatile__
(paren
l_string|&quot;mcr p14, 0, %0, c4, c1, 0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|pmu-&gt;int_enable
)paren
)paren
suffix:semicolon
id|pmnc
op_or_assign
id|PMU_ENABLE
suffix:semicolon
id|write_pmnc
c_func
(paren
id|pmnc
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;xscale_pmu_start: pmnc: %#08x mask: %08x&bslash;n&quot;
comma
id|pmnc
comma
id|pmu-&gt;int_enable
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xscale_detect_pmu
r_static
r_int
id|xscale_detect_pmu
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|u32
id|id
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mrc p15, 0, %0, c0, c0, 0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|id
)paren
)paren
suffix:semicolon
id|id
op_assign
(paren
id|id
op_rshift
l_int|13
)paren
op_amp
l_int|0x7
suffix:semicolon
r_switch
c_cond
(paren
id|id
)paren
(brace
r_case
l_int|1
suffix:colon
id|pmu
op_assign
op_amp
id|pmu_parms
(braket
id|PMU_XSC1
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|pmu
op_assign
op_amp
id|pmu_parms
(braket
id|PMU_XSC2
)braket
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|op_xscale_spec.name
op_assign
id|pmu-&gt;name
suffix:semicolon
id|op_xscale_spec.num_counters
op_assign
id|pmu-&gt;num_counters
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;xscale_detect_pmu: detected %s PMU&bslash;n&quot;
comma
id|pmu-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|op_xscale_spec
r_struct
id|op_arm_model_spec
id|op_xscale_spec
op_assign
(brace
dot
id|init
op_assign
id|xscale_detect_pmu
comma
dot
id|setup_ctrs
op_assign
id|xscale_setup_ctrs
comma
dot
id|start
op_assign
id|xscale_pmu_start
comma
dot
id|stop
op_assign
id|xscale_pmu_stop
comma
)brace
suffix:semicolon
eof
