multiline_comment|/**&n; * @file op_model_p4.c&n; * P4 model-specific MSR operations&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author Graydon Hoare&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &quot;op_x86_model.h&quot;
macro_line|#include &quot;op_counter.h&quot;
DECL|macro|NUM_EVENTS
mdefine_line|#define NUM_EVENTS 39
DECL|macro|NUM_COUNTERS_NON_HT
mdefine_line|#define NUM_COUNTERS_NON_HT 8
DECL|macro|NUM_ESCRS_NON_HT
mdefine_line|#define NUM_ESCRS_NON_HT 45
DECL|macro|NUM_CCCRS_NON_HT
mdefine_line|#define NUM_CCCRS_NON_HT 18
DECL|macro|NUM_CONTROLS_NON_HT
mdefine_line|#define NUM_CONTROLS_NON_HT (NUM_ESCRS_NON_HT + NUM_CCCRS_NON_HT)
DECL|macro|NUM_COUNTERS_HT2
mdefine_line|#define NUM_COUNTERS_HT2 4
DECL|macro|NUM_ESCRS_HT2
mdefine_line|#define NUM_ESCRS_HT2 23
DECL|macro|NUM_CCCRS_HT2
mdefine_line|#define NUM_CCCRS_HT2 9
DECL|macro|NUM_CONTROLS_HT2
mdefine_line|#define NUM_CONTROLS_HT2 (NUM_ESCRS_HT2 + NUM_CCCRS_HT2)
DECL|variable|num_counters
r_static
r_int
r_int
id|num_counters
op_assign
id|NUM_COUNTERS_NON_HT
suffix:semicolon
multiline_comment|/* this has to be checked dynamically since the&n;   hyper-threadedness of a chip is discovered at&n;   kernel boot-time. */
DECL|function|setup_num_counters
r_static
r_inline
r_void
id|setup_num_counters
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|smp_num_siblings
op_eq
l_int|2
)paren
id|num_counters
op_assign
id|NUM_COUNTERS_HT2
suffix:semicolon
macro_line|#endif
)brace
DECL|function|addr_increment
r_static
r_int
r_inline
id|addr_increment
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_return
id|smp_num_siblings
op_eq
l_int|2
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
r_return
l_int|1
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* tables to simulate simplified hardware view of p4 registers */
DECL|struct|p4_counter_binding
r_struct
id|p4_counter_binding
(brace
DECL|member|virt_counter
r_int
id|virt_counter
suffix:semicolon
DECL|member|counter_address
r_int
id|counter_address
suffix:semicolon
DECL|member|cccr_address
r_int
id|cccr_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|p4_event_binding
r_struct
id|p4_event_binding
(brace
DECL|member|escr_select
r_int
id|escr_select
suffix:semicolon
multiline_comment|/* value to put in CCCR */
DECL|member|event_select
r_int
id|event_select
suffix:semicolon
multiline_comment|/* value to put in ESCR */
r_struct
(brace
DECL|member|virt_counter
r_int
id|virt_counter
suffix:semicolon
multiline_comment|/* for this counter... */
DECL|member|escr_address
r_int
id|escr_address
suffix:semicolon
multiline_comment|/* use this ESCR       */
DECL|member|bindings
)brace
id|bindings
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* nb: these CTR_* defines are a duplicate of defines in&n;   event/i386.p4*events. */
DECL|macro|CTR_BPU_0
mdefine_line|#define CTR_BPU_0      (1 &lt;&lt; 0)
DECL|macro|CTR_MS_0
mdefine_line|#define CTR_MS_0       (1 &lt;&lt; 1)
DECL|macro|CTR_FLAME_0
mdefine_line|#define CTR_FLAME_0    (1 &lt;&lt; 2)
DECL|macro|CTR_IQ_4
mdefine_line|#define CTR_IQ_4       (1 &lt;&lt; 3)
DECL|macro|CTR_BPU_2
mdefine_line|#define CTR_BPU_2      (1 &lt;&lt; 4)
DECL|macro|CTR_MS_2
mdefine_line|#define CTR_MS_2       (1 &lt;&lt; 5)
DECL|macro|CTR_FLAME_2
mdefine_line|#define CTR_FLAME_2    (1 &lt;&lt; 6)
DECL|macro|CTR_IQ_5
mdefine_line|#define CTR_IQ_5       (1 &lt;&lt; 7)
DECL|variable|p4_counters
r_static
r_struct
id|p4_counter_binding
id|p4_counters
(braket
id|NUM_COUNTERS_NON_HT
)braket
op_assign
(brace
(brace
id|CTR_BPU_0
comma
id|MSR_P4_BPU_PERFCTR0
comma
id|MSR_P4_BPU_CCCR0
)brace
comma
(brace
id|CTR_MS_0
comma
id|MSR_P4_MS_PERFCTR0
comma
id|MSR_P4_MS_CCCR0
)brace
comma
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_FLAME_PERFCTR0
comma
id|MSR_P4_FLAME_CCCR0
)brace
comma
(brace
id|CTR_IQ_4
comma
id|MSR_P4_IQ_PERFCTR4
comma
id|MSR_P4_IQ_CCCR4
)brace
comma
(brace
id|CTR_BPU_2
comma
id|MSR_P4_BPU_PERFCTR2
comma
id|MSR_P4_BPU_CCCR2
)brace
comma
(brace
id|CTR_MS_2
comma
id|MSR_P4_MS_PERFCTR2
comma
id|MSR_P4_MS_CCCR2
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_FLAME_PERFCTR2
comma
id|MSR_P4_FLAME_CCCR2
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_IQ_PERFCTR5
comma
id|MSR_P4_IQ_CCCR5
)brace
)brace
suffix:semicolon
DECL|macro|NUM_UNUSED_CCCRS
mdefine_line|#define NUM_UNUSED_CCCRS&t;NUM_CCCRS_NON_HT - NUM_COUNTERS_NON_HT
multiline_comment|/* All cccr we don&squot;t use. */
DECL|variable|p4_unused_cccr
r_static
r_int
id|p4_unused_cccr
(braket
id|NUM_UNUSED_CCCRS
)braket
op_assign
(brace
id|MSR_P4_BPU_CCCR1
comma
id|MSR_P4_BPU_CCCR3
comma
id|MSR_P4_MS_CCCR1
comma
id|MSR_P4_MS_CCCR3
comma
id|MSR_P4_FLAME_CCCR1
comma
id|MSR_P4_FLAME_CCCR3
comma
id|MSR_P4_IQ_CCCR0
comma
id|MSR_P4_IQ_CCCR1
comma
id|MSR_P4_IQ_CCCR2
comma
id|MSR_P4_IQ_CCCR3
)brace
suffix:semicolon
multiline_comment|/* p4 event codes in libop/op_event.h are indices into this table. */
DECL|variable|p4_events
r_static
r_struct
id|p4_event_binding
id|p4_events
(braket
id|NUM_EVENTS
)braket
op_assign
(brace
(brace
multiline_comment|/* BRANCH_RETIRED */
l_int|0x05
comma
l_int|0x06
comma
(brace
(brace
id|CTR_IQ_4
comma
id|MSR_P4_CRU_ESCR2
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_CRU_ESCR3
)brace
)brace
)brace
comma
(brace
multiline_comment|/* MISPRED_BRANCH_RETIRED */
l_int|0x04
comma
l_int|0x03
comma
(brace
(brace
id|CTR_IQ_4
comma
id|MSR_P4_CRU_ESCR0
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_CRU_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* TC_DELIVER_MODE */
l_int|0x01
comma
l_int|0x01
comma
(brace
(brace
id|CTR_MS_0
comma
id|MSR_P4_TC_ESCR0
)brace
comma
(brace
id|CTR_MS_2
comma
id|MSR_P4_TC_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* BPU_FETCH_REQUEST */
l_int|0x00
comma
l_int|0x03
comma
(brace
(brace
id|CTR_BPU_0
comma
id|MSR_P4_BPU_ESCR0
)brace
comma
(brace
id|CTR_BPU_2
comma
id|MSR_P4_BPU_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* ITLB_REFERENCE */
l_int|0x03
comma
l_int|0x18
comma
(brace
(brace
id|CTR_BPU_0
comma
id|MSR_P4_ITLB_ESCR0
)brace
comma
(brace
id|CTR_BPU_2
comma
id|MSR_P4_ITLB_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* MEMORY_CANCEL */
l_int|0x05
comma
l_int|0x02
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_DAC_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_DAC_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* MEMORY_COMPLETE */
l_int|0x02
comma
l_int|0x08
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_SAAT_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_SAAT_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* LOAD_PORT_REPLAY */
l_int|0x02
comma
l_int|0x04
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_SAAT_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_SAAT_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* STORE_PORT_REPLAY */
l_int|0x02
comma
l_int|0x05
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_SAAT_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_SAAT_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* MOB_LOAD_REPLAY */
l_int|0x02
comma
l_int|0x03
comma
(brace
(brace
id|CTR_BPU_0
comma
id|MSR_P4_MOB_ESCR0
)brace
comma
(brace
id|CTR_BPU_2
comma
id|MSR_P4_MOB_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* PAGE_WALK_TYPE */
l_int|0x04
comma
l_int|0x01
comma
(brace
(brace
id|CTR_BPU_0
comma
id|MSR_P4_PMH_ESCR0
)brace
comma
(brace
id|CTR_BPU_2
comma
id|MSR_P4_PMH_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* BSQ_CACHE_REFERENCE */
l_int|0x07
comma
l_int|0x0c
comma
(brace
(brace
id|CTR_BPU_0
comma
id|MSR_P4_BSU_ESCR0
)brace
comma
(brace
id|CTR_BPU_2
comma
id|MSR_P4_BSU_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* IOQ_ALLOCATION */
l_int|0x06
comma
l_int|0x03
comma
(brace
(brace
id|CTR_BPU_0
comma
id|MSR_P4_FSB_ESCR0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
)brace
comma
(brace
multiline_comment|/* IOQ_ACTIVE_ENTRIES */
l_int|0x06
comma
l_int|0x1a
comma
(brace
(brace
id|CTR_BPU_2
comma
id|MSR_P4_FSB_ESCR1
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
)brace
comma
(brace
multiline_comment|/* FSB_DATA_ACTIVITY */
l_int|0x06
comma
l_int|0x17
comma
(brace
(brace
id|CTR_BPU_0
comma
id|MSR_P4_FSB_ESCR0
)brace
comma
(brace
id|CTR_BPU_2
comma
id|MSR_P4_FSB_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* BSQ_ALLOCATION */
l_int|0x07
comma
l_int|0x05
comma
(brace
(brace
id|CTR_BPU_0
comma
id|MSR_P4_BSU_ESCR0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
)brace
comma
(brace
multiline_comment|/* BSQ_ACTIVE_ENTRIES */
l_int|0x07
comma
l_int|0x06
comma
(brace
(brace
id|CTR_BPU_2
comma
id|MSR_P4_BSU_ESCR1
multiline_comment|/* guess */
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
)brace
comma
(brace
multiline_comment|/* X87_ASSIST */
l_int|0x05
comma
l_int|0x03
comma
(brace
(brace
id|CTR_IQ_4
comma
id|MSR_P4_CRU_ESCR2
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_CRU_ESCR3
)brace
)brace
)brace
comma
(brace
multiline_comment|/* SSE_INPUT_ASSIST */
l_int|0x01
comma
l_int|0x34
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_FIRM_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_FIRM_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* PACKED_SP_UOP */
l_int|0x01
comma
l_int|0x08
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_FIRM_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_FIRM_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* PACKED_DP_UOP */
l_int|0x01
comma
l_int|0x0c
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_FIRM_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_FIRM_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* SCALAR_SP_UOP */
l_int|0x01
comma
l_int|0x0a
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_FIRM_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_FIRM_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* SCALAR_DP_UOP */
l_int|0x01
comma
l_int|0x0e
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_FIRM_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_FIRM_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* 64BIT_MMX_UOP */
l_int|0x01
comma
l_int|0x02
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_FIRM_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_FIRM_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* 128BIT_MMX_UOP */
l_int|0x01
comma
l_int|0x1a
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_FIRM_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_FIRM_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* X87_FP_UOP */
l_int|0x01
comma
l_int|0x04
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_FIRM_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_FIRM_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* X87_SIMD_MOVES_UOP */
l_int|0x01
comma
l_int|0x2e
comma
(brace
(brace
id|CTR_FLAME_0
comma
id|MSR_P4_FIRM_ESCR0
)brace
comma
(brace
id|CTR_FLAME_2
comma
id|MSR_P4_FIRM_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* MACHINE_CLEAR */
l_int|0x05
comma
l_int|0x02
comma
(brace
(brace
id|CTR_IQ_4
comma
id|MSR_P4_CRU_ESCR2
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_CRU_ESCR3
)brace
)brace
)brace
comma
(brace
multiline_comment|/* GLOBAL_POWER_EVENTS */
l_int|0x06
comma
l_int|0x13
multiline_comment|/* older manual says 0x05, newer 0x13 */
comma
(brace
(brace
id|CTR_BPU_0
comma
id|MSR_P4_FSB_ESCR0
)brace
comma
(brace
id|CTR_BPU_2
comma
id|MSR_P4_FSB_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* TC_MS_XFER */
l_int|0x00
comma
l_int|0x05
comma
(brace
(brace
id|CTR_MS_0
comma
id|MSR_P4_MS_ESCR0
)brace
comma
(brace
id|CTR_MS_2
comma
id|MSR_P4_MS_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* UOP_QUEUE_WRITES */
l_int|0x00
comma
l_int|0x09
comma
(brace
(brace
id|CTR_MS_0
comma
id|MSR_P4_MS_ESCR0
)brace
comma
(brace
id|CTR_MS_2
comma
id|MSR_P4_MS_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* FRONT_END_EVENT */
l_int|0x05
comma
l_int|0x08
comma
(brace
(brace
id|CTR_IQ_4
comma
id|MSR_P4_CRU_ESCR2
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_CRU_ESCR3
)brace
)brace
)brace
comma
(brace
multiline_comment|/* EXECUTION_EVENT */
l_int|0x05
comma
l_int|0x0c
comma
(brace
(brace
id|CTR_IQ_4
comma
id|MSR_P4_CRU_ESCR2
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_CRU_ESCR3
)brace
)brace
)brace
comma
(brace
multiline_comment|/* REPLAY_EVENT */
l_int|0x05
comma
l_int|0x09
comma
(brace
(brace
id|CTR_IQ_4
comma
id|MSR_P4_CRU_ESCR2
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_CRU_ESCR3
)brace
)brace
)brace
comma
(brace
multiline_comment|/* INSTR_RETIRED */
l_int|0x04
comma
l_int|0x02
comma
(brace
(brace
id|CTR_IQ_4
comma
id|MSR_P4_CRU_ESCR0
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_CRU_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* UOPS_RETIRED */
l_int|0x04
comma
l_int|0x01
comma
(brace
(brace
id|CTR_IQ_4
comma
id|MSR_P4_CRU_ESCR0
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_CRU_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* UOP_TYPE */
l_int|0x02
comma
l_int|0x02
comma
(brace
(brace
id|CTR_IQ_4
comma
id|MSR_P4_RAT_ESCR0
)brace
comma
(brace
id|CTR_IQ_5
comma
id|MSR_P4_RAT_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* RETIRED_MISPRED_BRANCH_TYPE */
l_int|0x02
comma
l_int|0x05
comma
(brace
(brace
id|CTR_MS_0
comma
id|MSR_P4_TBPU_ESCR0
)brace
comma
(brace
id|CTR_MS_2
comma
id|MSR_P4_TBPU_ESCR1
)brace
)brace
)brace
comma
(brace
multiline_comment|/* RETIRED_BRANCH_TYPE */
l_int|0x02
comma
l_int|0x04
comma
(brace
(brace
id|CTR_MS_0
comma
id|MSR_P4_TBPU_ESCR0
)brace
comma
(brace
id|CTR_MS_2
comma
id|MSR_P4_TBPU_ESCR1
)brace
)brace
)brace
)brace
suffix:semicolon
DECL|macro|MISC_PMC_ENABLED_P
mdefine_line|#define MISC_PMC_ENABLED_P(x) ((x) &amp; 1 &lt;&lt; 7)
DECL|macro|ESCR_RESERVED_BITS
mdefine_line|#define ESCR_RESERVED_BITS 0x80000003
DECL|macro|ESCR_CLEAR
mdefine_line|#define ESCR_CLEAR(escr) ((escr) &amp;= ESCR_RESERVED_BITS)
DECL|macro|ESCR_SET_USR_0
mdefine_line|#define ESCR_SET_USR_0(escr, usr) ((escr) |= (((usr) &amp; 1) &lt;&lt; 2))
DECL|macro|ESCR_SET_OS_0
mdefine_line|#define ESCR_SET_OS_0(escr, os) ((escr) |= (((os) &amp; 1) &lt;&lt; 3))
DECL|macro|ESCR_SET_USR_1
mdefine_line|#define ESCR_SET_USR_1(escr, usr) ((escr) |= (((usr) &amp; 1)))
DECL|macro|ESCR_SET_OS_1
mdefine_line|#define ESCR_SET_OS_1(escr, os) ((escr) |= (((os) &amp; 1) &lt;&lt; 1))
DECL|macro|ESCR_SET_EVENT_SELECT
mdefine_line|#define ESCR_SET_EVENT_SELECT(escr, sel) ((escr) |= (((sel) &amp; 0x3f) &lt;&lt; 25))
DECL|macro|ESCR_SET_EVENT_MASK
mdefine_line|#define ESCR_SET_EVENT_MASK(escr, mask) ((escr) |= (((mask) &amp; 0xffff) &lt;&lt; 9))
DECL|macro|ESCR_READ
mdefine_line|#define ESCR_READ(escr,high,ev,i) do {rdmsr(ev-&gt;bindings[(i)].escr_address, (escr), (high));} while (0)
DECL|macro|ESCR_WRITE
mdefine_line|#define ESCR_WRITE(escr,high,ev,i) do {wrmsr(ev-&gt;bindings[(i)].escr_address, (escr), (high));} while (0)
DECL|macro|CCCR_RESERVED_BITS
mdefine_line|#define CCCR_RESERVED_BITS 0x38030FFF
DECL|macro|CCCR_CLEAR
mdefine_line|#define CCCR_CLEAR(cccr) ((cccr) &amp;= CCCR_RESERVED_BITS)
DECL|macro|CCCR_SET_REQUIRED_BITS
mdefine_line|#define CCCR_SET_REQUIRED_BITS(cccr) ((cccr) |= 0x00030000)
DECL|macro|CCCR_SET_ESCR_SELECT
mdefine_line|#define CCCR_SET_ESCR_SELECT(cccr, sel) ((cccr) |= (((sel) &amp; 0x07) &lt;&lt; 13))
DECL|macro|CCCR_SET_PMI_OVF_0
mdefine_line|#define CCCR_SET_PMI_OVF_0(cccr) ((cccr) |= (1&lt;&lt;26))
DECL|macro|CCCR_SET_PMI_OVF_1
mdefine_line|#define CCCR_SET_PMI_OVF_1(cccr) ((cccr) |= (1&lt;&lt;27))
DECL|macro|CCCR_SET_ENABLE
mdefine_line|#define CCCR_SET_ENABLE(cccr) ((cccr) |= (1&lt;&lt;12))
DECL|macro|CCCR_SET_DISABLE
mdefine_line|#define CCCR_SET_DISABLE(cccr) ((cccr) &amp;= ~(1&lt;&lt;12))
DECL|macro|CCCR_READ
mdefine_line|#define CCCR_READ(low, high, i) do {rdmsr(p4_counters[(i)].cccr_address, (low), (high));} while (0)
DECL|macro|CCCR_WRITE
mdefine_line|#define CCCR_WRITE(low, high, i) do {wrmsr(p4_counters[(i)].cccr_address, (low), (high));} while (0)
DECL|macro|CCCR_OVF_P
mdefine_line|#define CCCR_OVF_P(cccr) ((cccr) &amp; (1U&lt;&lt;31))
DECL|macro|CCCR_CLEAR_OVF
mdefine_line|#define CCCR_CLEAR_OVF(cccr) ((cccr) &amp;= (~(1U&lt;&lt;31)))
DECL|macro|CTR_READ
mdefine_line|#define CTR_READ(l,h,i) do {rdmsr(p4_counters[(i)].counter_address, (l), (h));} while (0)
DECL|macro|CTR_WRITE
mdefine_line|#define CTR_WRITE(l,i) do {wrmsr(p4_counters[(i)].counter_address, -(u32)(l), -1);} while (0)
DECL|macro|CTR_OVERFLOW_P
mdefine_line|#define CTR_OVERFLOW_P(ctr) (!((ctr) &amp; 0x80000000))
multiline_comment|/* this assigns a &quot;stagger&quot; to the current CPU, which is used throughout&n;   the code in this module as an extra array offset, to select the &quot;even&quot;&n;   or &quot;odd&quot; part of all the divided resources. */
DECL|function|get_stagger
r_static
r_int
r_int
id|get_stagger
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|cpu
op_ne
id|first_cpu
c_func
(paren
id|cpu_sibling_map
(braket
id|cpu
)braket
)paren
)paren
suffix:semicolon
macro_line|#endif&t;
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* finally, mediate access to a real hardware counter&n;   by passing a &quot;virtual&quot; counter numer to this macro,&n;   along with your stagger setting. */
DECL|macro|VIRT_CTR
mdefine_line|#define VIRT_CTR(stagger, i) ((i) + ((num_counters) * (stagger)))
DECL|variable|reset_value
r_static
r_int
r_int
id|reset_value
(braket
id|NUM_COUNTERS_NON_HT
)braket
suffix:semicolon
DECL|function|p4_fill_in_addresses
r_static
r_void
id|p4_fill_in_addresses
c_func
(paren
r_struct
id|op_msrs
op_star
r_const
id|msrs
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|addr
comma
id|stag
suffix:semicolon
id|setup_num_counters
c_func
(paren
)paren
suffix:semicolon
id|stag
op_assign
id|get_stagger
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* the counter registers we pay attention to */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_counters
suffix:semicolon
op_increment
id|i
)paren
(brace
id|msrs-&gt;counters
(braket
id|i
)braket
dot
id|addr
op_assign
id|p4_counters
(braket
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|i
)paren
)braket
dot
id|counter_address
suffix:semicolon
)brace
multiline_comment|/* FIXME: bad feeling, we don&squot;t save the 10 counters we don&squot;t use. */
multiline_comment|/* 18 CCCR registers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|addr
op_assign
id|MSR_P4_BPU_CCCR0
op_plus
id|stag
suffix:semicolon
id|addr
op_le
id|MSR_P4_IQ_CCCR5
suffix:semicolon
op_increment
id|i
comma
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|msrs-&gt;controls
(braket
id|i
)braket
dot
id|addr
op_assign
id|addr
suffix:semicolon
)brace
multiline_comment|/* 43 ESCR registers in three or four discontiguous group */
r_for
c_loop
(paren
id|addr
op_assign
id|MSR_P4_BSU_ESCR0
op_plus
id|stag
suffix:semicolon
id|addr
OL
id|MSR_P4_IQ_ESCR0
suffix:semicolon
op_increment
id|i
comma
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|msrs-&gt;controls
(braket
id|i
)braket
dot
id|addr
op_assign
id|addr
suffix:semicolon
)brace
multiline_comment|/* no IQ_ESCR0/1 on some models, we save a seconde time BSU_ESCR0/1&n;&t; * to avoid special case in nmi_{save|restore}_registers() */
r_if
c_cond
(paren
id|boot_cpu_data.x86_model
op_ge
l_int|0x3
)paren
(brace
r_for
c_loop
(paren
id|addr
op_assign
id|MSR_P4_BSU_ESCR0
op_plus
id|stag
suffix:semicolon
id|addr
op_le
id|MSR_P4_BSU_ESCR1
suffix:semicolon
op_increment
id|i
comma
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|msrs-&gt;controls
(braket
id|i
)braket
dot
id|addr
op_assign
id|addr
suffix:semicolon
)brace
)brace
r_else
(brace
r_for
c_loop
(paren
id|addr
op_assign
id|MSR_P4_IQ_ESCR0
op_plus
id|stag
suffix:semicolon
id|addr
op_le
id|MSR_P4_IQ_ESCR1
suffix:semicolon
op_increment
id|i
comma
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|msrs-&gt;controls
(braket
id|i
)braket
dot
id|addr
op_assign
id|addr
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|addr
op_assign
id|MSR_P4_RAT_ESCR0
op_plus
id|stag
suffix:semicolon
id|addr
op_le
id|MSR_P4_SSU_ESCR0
suffix:semicolon
op_increment
id|i
comma
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|msrs-&gt;controls
(braket
id|i
)braket
dot
id|addr
op_assign
id|addr
suffix:semicolon
)brace
r_for
c_loop
(paren
id|addr
op_assign
id|MSR_P4_MS_ESCR0
op_plus
id|stag
suffix:semicolon
id|addr
op_le
id|MSR_P4_TC_ESCR1
suffix:semicolon
op_increment
id|i
comma
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|msrs-&gt;controls
(braket
id|i
)braket
dot
id|addr
op_assign
id|addr
suffix:semicolon
)brace
r_for
c_loop
(paren
id|addr
op_assign
id|MSR_P4_IX_ESCR0
op_plus
id|stag
suffix:semicolon
id|addr
op_le
id|MSR_P4_CRU_ESCR3
suffix:semicolon
op_increment
id|i
comma
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|msrs-&gt;controls
(braket
id|i
)braket
dot
id|addr
op_assign
id|addr
suffix:semicolon
)brace
multiline_comment|/* there are 2 remaining non-contiguously located ESCRs */
r_if
c_cond
(paren
id|num_counters
op_eq
id|NUM_COUNTERS_NON_HT
)paren
(brace
multiline_comment|/* standard non-HT CPUs handle both remaining ESCRs*/
id|msrs-&gt;controls
(braket
id|i
op_increment
)braket
dot
id|addr
op_assign
id|MSR_P4_CRU_ESCR5
suffix:semicolon
id|msrs-&gt;controls
(braket
id|i
op_increment
)braket
dot
id|addr
op_assign
id|MSR_P4_CRU_ESCR4
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|stag
op_eq
l_int|0
)paren
(brace
multiline_comment|/* HT CPUs give the first remainder to the even thread, as&n;&t;&t;   the 32nd control register */
id|msrs-&gt;controls
(braket
id|i
op_increment
)braket
dot
id|addr
op_assign
id|MSR_P4_CRU_ESCR4
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* and two copies of the second to the odd thread,&n;&t;&t;   for the 22st and 23nd control registers */
id|msrs-&gt;controls
(braket
id|i
op_increment
)braket
dot
id|addr
op_assign
id|MSR_P4_CRU_ESCR5
suffix:semicolon
id|msrs-&gt;controls
(braket
id|i
op_increment
)braket
dot
id|addr
op_assign
id|MSR_P4_CRU_ESCR5
suffix:semicolon
)brace
)brace
DECL|function|pmc_setup_one_p4_counter
r_static
r_void
id|pmc_setup_one_p4_counter
c_func
(paren
r_int
r_int
id|ctr
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_const
id|maxbind
op_assign
l_int|2
suffix:semicolon
r_int
r_int
id|cccr
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|escr
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|high
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|counter_bit
suffix:semicolon
r_struct
id|p4_event_binding
op_star
id|ev
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|stag
suffix:semicolon
id|stag
op_assign
id|get_stagger
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* convert from counter *number* to counter *bit* */
id|counter_bit
op_assign
l_int|1
op_lshift
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|ctr
)paren
suffix:semicolon
multiline_comment|/* find our event binding structure. */
r_if
c_cond
(paren
id|counter_config
(braket
id|ctr
)braket
dot
id|event
op_le
l_int|0
op_logical_or
id|counter_config
(braket
id|ctr
)braket
dot
id|event
OG
id|NUM_EVENTS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;oprofile: P4 event code 0x%lx out of range&bslash;n&quot;
comma
id|counter_config
(braket
id|ctr
)braket
dot
id|event
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ev
op_assign
op_amp
(paren
id|p4_events
(braket
id|counter_config
(braket
id|ctr
)braket
dot
id|event
op_minus
l_int|1
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
id|maxbind
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ev-&gt;bindings
(braket
id|i
)braket
dot
id|virt_counter
op_amp
id|counter_bit
)paren
(brace
multiline_comment|/* modify ESCR */
id|ESCR_READ
c_func
(paren
id|escr
comma
id|high
comma
id|ev
comma
id|i
)paren
suffix:semicolon
id|ESCR_CLEAR
c_func
(paren
id|escr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stag
op_eq
l_int|0
)paren
(brace
id|ESCR_SET_USR_0
c_func
(paren
id|escr
comma
id|counter_config
(braket
id|ctr
)braket
dot
id|user
)paren
suffix:semicolon
id|ESCR_SET_OS_0
c_func
(paren
id|escr
comma
id|counter_config
(braket
id|ctr
)braket
dot
id|kernel
)paren
suffix:semicolon
)brace
r_else
(brace
id|ESCR_SET_USR_1
c_func
(paren
id|escr
comma
id|counter_config
(braket
id|ctr
)braket
dot
id|user
)paren
suffix:semicolon
id|ESCR_SET_OS_1
c_func
(paren
id|escr
comma
id|counter_config
(braket
id|ctr
)braket
dot
id|kernel
)paren
suffix:semicolon
)brace
id|ESCR_SET_EVENT_SELECT
c_func
(paren
id|escr
comma
id|ev-&gt;event_select
)paren
suffix:semicolon
id|ESCR_SET_EVENT_MASK
c_func
(paren
id|escr
comma
id|counter_config
(braket
id|ctr
)braket
dot
id|unit_mask
)paren
suffix:semicolon
id|ESCR_WRITE
c_func
(paren
id|escr
comma
id|high
comma
id|ev
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* modify CCCR */
id|CCCR_READ
c_func
(paren
id|cccr
comma
id|high
comma
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|ctr
)paren
)paren
suffix:semicolon
id|CCCR_CLEAR
c_func
(paren
id|cccr
)paren
suffix:semicolon
id|CCCR_SET_REQUIRED_BITS
c_func
(paren
id|cccr
)paren
suffix:semicolon
id|CCCR_SET_ESCR_SELECT
c_func
(paren
id|cccr
comma
id|ev-&gt;escr_select
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stag
op_eq
l_int|0
)paren
(brace
id|CCCR_SET_PMI_OVF_0
c_func
(paren
id|cccr
)paren
suffix:semicolon
)brace
r_else
(brace
id|CCCR_SET_PMI_OVF_1
c_func
(paren
id|cccr
)paren
suffix:semicolon
)brace
id|CCCR_WRITE
c_func
(paren
id|cccr
comma
id|high
comma
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|ctr
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;oprofile: P4 event code 0x%lx no binding, stag %d ctr %d&bslash;n&quot;
comma
id|counter_config
(braket
id|ctr
)braket
dot
id|event
comma
id|stag
comma
id|ctr
)paren
suffix:semicolon
)brace
DECL|function|p4_setup_ctrs
r_static
r_void
id|p4_setup_ctrs
c_func
(paren
r_struct
id|op_msrs
r_const
op_star
r_const
id|msrs
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|low
comma
id|high
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|stag
suffix:semicolon
id|stag
op_assign
id|get_stagger
c_func
(paren
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MISC_ENABLE
comma
id|low
comma
id|high
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MISC_PMC_ENABLED_P
c_func
(paren
id|low
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;oprofile: P4 PMC not available&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* clear the cccrs we will use */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_counters
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rdmsr
c_func
(paren
id|p4_counters
(braket
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|i
)paren
)braket
dot
id|cccr_address
comma
id|low
comma
id|high
)paren
suffix:semicolon
id|CCCR_CLEAR
c_func
(paren
id|low
)paren
suffix:semicolon
id|CCCR_SET_REQUIRED_BITS
c_func
(paren
id|low
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|p4_counters
(braket
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|i
)paren
)braket
dot
id|cccr_address
comma
id|low
comma
id|high
)paren
suffix:semicolon
)brace
multiline_comment|/* clear cccrs outside our concern */
r_for
c_loop
(paren
id|i
op_assign
id|stag
suffix:semicolon
id|i
OL
id|NUM_UNUSED_CCCRS
suffix:semicolon
id|i
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|rdmsr
c_func
(paren
id|p4_unused_cccr
(braket
id|i
)braket
comma
id|low
comma
id|high
)paren
suffix:semicolon
id|CCCR_CLEAR
c_func
(paren
id|low
)paren
suffix:semicolon
id|CCCR_SET_REQUIRED_BITS
c_func
(paren
id|low
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|p4_unused_cccr
(braket
id|i
)braket
comma
id|low
comma
id|high
)paren
suffix:semicolon
)brace
multiline_comment|/* clear all escrs (including those outside our concern) */
r_for
c_loop
(paren
id|addr
op_assign
id|MSR_P4_BSU_ESCR0
op_plus
id|stag
suffix:semicolon
id|addr
OL
id|MSR_P4_IQ_ESCR0
suffix:semicolon
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|wrmsr
c_func
(paren
id|addr
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* On older models clear also MSR_P4_IQ_ESCR0/1 */
r_if
c_cond
(paren
id|boot_cpu_data.x86_model
OL
l_int|0x3
)paren
(brace
id|wrmsr
c_func
(paren
id|MSR_P4_IQ_ESCR0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P4_IQ_ESCR1
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|addr
op_assign
id|MSR_P4_RAT_ESCR0
op_plus
id|stag
suffix:semicolon
id|addr
op_le
id|MSR_P4_SSU_ESCR0
suffix:semicolon
op_increment
id|i
comma
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|wrmsr
c_func
(paren
id|addr
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|addr
op_assign
id|MSR_P4_MS_ESCR0
op_plus
id|stag
suffix:semicolon
id|addr
op_le
id|MSR_P4_TC_ESCR1
suffix:semicolon
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|wrmsr
c_func
(paren
id|addr
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|addr
op_assign
id|MSR_P4_IX_ESCR0
op_plus
id|stag
suffix:semicolon
id|addr
op_le
id|MSR_P4_CRU_ESCR3
suffix:semicolon
id|addr
op_add_assign
id|addr_increment
c_func
(paren
)paren
)paren
(brace
id|wrmsr
c_func
(paren
id|addr
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|num_counters
op_eq
id|NUM_COUNTERS_NON_HT
)paren
(brace
id|wrmsr
c_func
(paren
id|MSR_P4_CRU_ESCR4
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P4_CRU_ESCR5
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|stag
op_eq
l_int|0
)paren
(brace
id|wrmsr
c_func
(paren
id|MSR_P4_CRU_ESCR4
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|wrmsr
c_func
(paren
id|MSR_P4_CRU_ESCR5
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* setup all counters */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_counters
suffix:semicolon
op_increment
id|i
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
id|enabled
)paren
(brace
id|reset_value
(braket
id|i
)braket
op_assign
id|counter_config
(braket
id|i
)braket
dot
id|count
suffix:semicolon
id|pmc_setup_one_p4_counter
c_func
(paren
id|i
)paren
suffix:semicolon
id|CTR_WRITE
c_func
(paren
id|counter_config
(braket
id|i
)braket
dot
id|count
comma
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|i
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|reset_value
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|function|p4_check_ctrs
r_static
r_int
id|p4_check_ctrs
c_func
(paren
r_int
r_int
r_const
id|cpu
comma
r_struct
id|op_msrs
r_const
op_star
r_const
id|msrs
comma
r_struct
id|pt_regs
op_star
r_const
id|regs
)paren
(brace
r_int
r_int
id|ctr
comma
id|low
comma
id|high
comma
id|stag
comma
id|real
suffix:semicolon
r_int
id|i
suffix:semicolon
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
id|is_kernel
op_assign
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
suffix:semicolon
id|stag
op_assign
id|get_stagger
c_func
(paren
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
id|num_counters
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|reset_value
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
multiline_comment|/* &n;&t;&t; * there is some eccentricity in the hardware which&n;&t;&t; * requires that we perform 2 extra corrections:&n;&t;&t; *&n;&t;&t; * - check both the CCCR:OVF flag for overflow and the&n;&t;&t; *   counter high bit for un-flagged overflows.&n;&t;&t; *&n;&t;&t; * - write the counter back twice to ensure it gets&n;&t;&t; *   updated properly.&n;&t;&t; * &n;&t;&t; * the former seems to be related to extra NMIs happening&n;&t;&t; * during the current NMI; the latter is reported as errata&n;&t;&t; * N15 in intel doc 249199-029, pentium 4 specification&n;&t;&t; * update, though their suggested work-around does not&n;&t;&t; * appear to solve the problem.&n;&t;&t; */
id|real
op_assign
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|i
)paren
suffix:semicolon
id|CCCR_READ
c_func
(paren
id|low
comma
id|high
comma
id|real
)paren
suffix:semicolon
id|CTR_READ
c_func
(paren
id|ctr
comma
id|high
comma
id|real
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CCCR_OVF_P
c_func
(paren
id|low
)paren
op_logical_or
id|CTR_OVERFLOW_P
c_func
(paren
id|ctr
)paren
)paren
(brace
id|oprofile_add_sample
c_func
(paren
id|eip
comma
id|is_kernel
comma
id|i
comma
id|cpu
)paren
suffix:semicolon
id|CTR_WRITE
c_func
(paren
id|reset_value
(braket
id|i
)braket
comma
id|real
)paren
suffix:semicolon
id|CCCR_CLEAR_OVF
c_func
(paren
id|low
)paren
suffix:semicolon
id|CCCR_WRITE
c_func
(paren
id|low
comma
id|high
comma
id|real
)paren
suffix:semicolon
id|CTR_WRITE
c_func
(paren
id|reset_value
(braket
id|i
)braket
comma
id|real
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* P4 quirk: you have to re-unmask the apic vector */
id|apic_write
c_func
(paren
id|APIC_LVTPC
comma
id|apic_read
c_func
(paren
id|APIC_LVTPC
)paren
op_amp
op_complement
id|APIC_LVT_MASKED
)paren
suffix:semicolon
multiline_comment|/* See op_model_ppro.c */
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|p4_start
r_static
r_void
id|p4_start
c_func
(paren
r_struct
id|op_msrs
r_const
op_star
r_const
id|msrs
)paren
(brace
r_int
r_int
id|low
comma
id|high
comma
id|stag
suffix:semicolon
r_int
id|i
suffix:semicolon
id|stag
op_assign
id|get_stagger
c_func
(paren
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
id|num_counters
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|reset_value
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|CCCR_READ
c_func
(paren
id|low
comma
id|high
comma
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|i
)paren
)paren
suffix:semicolon
id|CCCR_SET_ENABLE
c_func
(paren
id|low
)paren
suffix:semicolon
id|CCCR_WRITE
c_func
(paren
id|low
comma
id|high
comma
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|p4_stop
r_static
r_void
id|p4_stop
c_func
(paren
r_struct
id|op_msrs
r_const
op_star
r_const
id|msrs
)paren
(brace
r_int
r_int
id|low
comma
id|high
comma
id|stag
suffix:semicolon
r_int
id|i
suffix:semicolon
id|stag
op_assign
id|get_stagger
c_func
(paren
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
id|num_counters
suffix:semicolon
op_increment
id|i
)paren
(brace
id|CCCR_READ
c_func
(paren
id|low
comma
id|high
comma
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|i
)paren
)paren
suffix:semicolon
id|CCCR_SET_DISABLE
c_func
(paren
id|low
)paren
suffix:semicolon
id|CCCR_WRITE
c_func
(paren
id|low
comma
id|high
comma
id|VIRT_CTR
c_func
(paren
id|stag
comma
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_SMP
DECL|variable|op_p4_ht2_spec
r_struct
id|op_x86_model_spec
r_const
id|op_p4_ht2_spec
op_assign
(brace
dot
id|num_counters
op_assign
id|NUM_COUNTERS_HT2
comma
dot
id|num_controls
op_assign
id|NUM_CONTROLS_HT2
comma
dot
id|fill_in_addresses
op_assign
op_amp
id|p4_fill_in_addresses
comma
dot
id|setup_ctrs
op_assign
op_amp
id|p4_setup_ctrs
comma
dot
id|check_ctrs
op_assign
op_amp
id|p4_check_ctrs
comma
dot
id|start
op_assign
op_amp
id|p4_start
comma
dot
id|stop
op_assign
op_amp
id|p4_stop
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|op_p4_spec
r_struct
id|op_x86_model_spec
r_const
id|op_p4_spec
op_assign
(brace
dot
id|num_counters
op_assign
id|NUM_COUNTERS_NON_HT
comma
dot
id|num_controls
op_assign
id|NUM_CONTROLS_NON_HT
comma
dot
id|fill_in_addresses
op_assign
op_amp
id|p4_fill_in_addresses
comma
dot
id|setup_ctrs
op_assign
op_amp
id|p4_setup_ctrs
comma
dot
id|check_ctrs
op_assign
op_amp
id|p4_check_ctrs
comma
dot
id|start
op_assign
op_amp
id|p4_start
comma
dot
id|stop
op_assign
op_amp
id|p4_stop
)brace
suffix:semicolon
eof
