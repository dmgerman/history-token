multiline_comment|/* &n; * arch/ppc64/kernel/xics.c&n; *&n; * Copyright 2000 IBM Corporation.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/radix-tree.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/xics.h&gt;
macro_line|#include &lt;asm/hvcall.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &quot;i8259.h&quot;
r_static
r_int
r_int
id|xics_startup
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|xics_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|xics_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|xics_mask_and_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|xics_end_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|xics_set_affinity
c_func
(paren
r_int
r_int
id|irq_nr
comma
id|cpumask_t
id|cpumask
)paren
suffix:semicolon
DECL|variable|xics_pic
r_struct
id|hw_interrupt_type
id|xics_pic
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot; XICS     &quot;
comma
dot
id|startup
op_assign
id|xics_startup
comma
dot
id|enable
op_assign
id|xics_enable_irq
comma
dot
id|disable
op_assign
id|xics_disable_irq
comma
dot
id|ack
op_assign
id|xics_mask_and_ack_irq
comma
dot
id|end
op_assign
id|xics_end_irq
comma
dot
id|set_affinity
op_assign
id|xics_set_affinity
)brace
suffix:semicolon
DECL|variable|xics_8259_pic
r_struct
id|hw_interrupt_type
id|xics_8259_pic
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot; XICS/8259&quot;
comma
dot
id|ack
op_assign
id|xics_mask_and_ack_irq
comma
)brace
suffix:semicolon
multiline_comment|/* This is used to map real irq numbers to virtual */
DECL|variable|irq_map
r_static
r_struct
id|radix_tree_root
id|irq_map
op_assign
id|RADIX_TREE_INIT
c_func
(paren
id|GFP_ATOMIC
)paren
suffix:semicolon
DECL|macro|XICS_IPI
mdefine_line|#define XICS_IPI&t;&t;2
DECL|macro|XICS_IRQ_SPURIOUS
mdefine_line|#define XICS_IRQ_SPURIOUS&t;0
multiline_comment|/* Want a priority other than 0.  Various HW issues require this. */
DECL|macro|DEFAULT_PRIORITY
mdefine_line|#define&t;DEFAULT_PRIORITY&t;5
multiline_comment|/* &n; * Mark IPIs as higher priority so we can take them inside interrupts that&n; * arent marked SA_INTERRUPT&n; */
DECL|macro|IPI_PRIORITY
mdefine_line|#define IPI_PRIORITY&t;&t;4
DECL|struct|xics_ipl
r_struct
id|xics_ipl
(brace
r_union
(brace
DECL|member|word
id|u32
id|word
suffix:semicolon
DECL|member|bytes
id|u8
id|bytes
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|xirr_poll
)brace
id|xirr_poll
suffix:semicolon
r_union
(brace
DECL|member|word
id|u32
id|word
suffix:semicolon
DECL|member|bytes
id|u8
id|bytes
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|xirr
)brace
id|xirr
suffix:semicolon
DECL|member|dummy
id|u32
id|dummy
suffix:semicolon
r_union
(brace
DECL|member|word
id|u32
id|word
suffix:semicolon
DECL|member|bytes
id|u8
id|bytes
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|qirr
)brace
id|qirr
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|xics_per_cpu
r_static
r_struct
id|xics_ipl
id|__iomem
op_star
id|xics_per_cpu
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|xics_irq_8259_cascade
r_static
r_int
id|xics_irq_8259_cascade
op_assign
l_int|0
suffix:semicolon
DECL|variable|xics_irq_8259_cascade_real
r_static
r_int
id|xics_irq_8259_cascade_real
op_assign
l_int|0
suffix:semicolon
DECL|variable|default_server
r_static
r_int
r_int
id|default_server
op_assign
l_int|0xFF
suffix:semicolon
multiline_comment|/* also referenced in smp.c... */
DECL|variable|default_distrib_server
r_int
r_int
id|default_distrib_server
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * XICS only has a single IPI, so encode the messages per CPU&n; */
DECL|variable|__cacheline_aligned
r_struct
id|xics_ipi_struct
id|xics_ipi_message
(braket
id|NR_CPUS
)braket
id|__cacheline_aligned
suffix:semicolon
multiline_comment|/* RTAS service tokens */
DECL|variable|ibm_get_xive
r_int
id|ibm_get_xive
suffix:semicolon
DECL|variable|ibm_set_xive
r_int
id|ibm_set_xive
suffix:semicolon
DECL|variable|ibm_int_on
r_int
id|ibm_int_on
suffix:semicolon
DECL|variable|ibm_int_off
r_int
id|ibm_int_off
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|xirr_info_get
r_int
(paren
op_star
id|xirr_info_get
)paren
(paren
r_int
id|cpu
)paren
suffix:semicolon
DECL|member|xirr_info_set
r_void
(paren
op_star
id|xirr_info_set
)paren
(paren
r_int
id|cpu
comma
r_int
id|val
)paren
suffix:semicolon
DECL|member|cppr_info
r_void
(paren
op_star
id|cppr_info
)paren
(paren
r_int
id|cpu
comma
id|u8
id|val
)paren
suffix:semicolon
DECL|member|qirr_info
r_void
(paren
op_star
id|qirr_info
)paren
(paren
r_int
id|cpu
comma
id|u8
id|val
)paren
suffix:semicolon
DECL|typedef|xics_ops
)brace
id|xics_ops
suffix:semicolon
multiline_comment|/* SMP */
DECL|function|pSeries_xirr_info_get
r_static
r_int
id|pSeries_xirr_info_get
c_func
(paren
r_int
id|n_cpu
)paren
(brace
r_return
id|in_be32
c_func
(paren
op_amp
id|xics_per_cpu
(braket
id|n_cpu
)braket
op_member_access_from_pointer
id|xirr.word
)paren
suffix:semicolon
)brace
DECL|function|pSeries_xirr_info_set
r_static
r_void
id|pSeries_xirr_info_set
c_func
(paren
r_int
id|n_cpu
comma
r_int
id|value
)paren
(brace
id|out_be32
c_func
(paren
op_amp
id|xics_per_cpu
(braket
id|n_cpu
)braket
op_member_access_from_pointer
id|xirr.word
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pSeries_cppr_info
r_static
r_void
id|pSeries_cppr_info
c_func
(paren
r_int
id|n_cpu
comma
id|u8
id|value
)paren
(brace
id|out_8
c_func
(paren
op_amp
id|xics_per_cpu
(braket
id|n_cpu
)braket
op_member_access_from_pointer
id|xirr.bytes
(braket
l_int|0
)braket
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pSeries_qirr_info
r_static
r_void
id|pSeries_qirr_info
c_func
(paren
r_int
id|n_cpu
comma
id|u8
id|value
)paren
(brace
id|out_8
c_func
(paren
op_amp
id|xics_per_cpu
(braket
id|n_cpu
)braket
op_member_access_from_pointer
id|qirr.bytes
(braket
l_int|0
)braket
comma
id|value
)paren
suffix:semicolon
)brace
DECL|variable|pSeries_ops
r_static
id|xics_ops
id|pSeries_ops
op_assign
(brace
id|pSeries_xirr_info_get
comma
id|pSeries_xirr_info_set
comma
id|pSeries_cppr_info
comma
id|pSeries_qirr_info
)brace
suffix:semicolon
DECL|variable|ops
r_static
id|xics_ops
op_star
id|ops
op_assign
op_amp
id|pSeries_ops
suffix:semicolon
multiline_comment|/* LPAR */
DECL|function|plpar_eoi
r_static
r_inline
r_int
id|plpar_eoi
c_func
(paren
r_int
r_int
id|xirr
)paren
(brace
r_return
id|plpar_hcall_norets
c_func
(paren
id|H_EOI
comma
id|xirr
)paren
suffix:semicolon
)brace
DECL|function|plpar_cppr
r_static
r_inline
r_int
id|plpar_cppr
c_func
(paren
r_int
r_int
id|cppr
)paren
(brace
r_return
id|plpar_hcall_norets
c_func
(paren
id|H_CPPR
comma
id|cppr
)paren
suffix:semicolon
)brace
DECL|function|plpar_ipi
r_static
r_inline
r_int
id|plpar_ipi
c_func
(paren
r_int
r_int
id|servernum
comma
r_int
r_int
id|mfrr
)paren
(brace
r_return
id|plpar_hcall_norets
c_func
(paren
id|H_IPI
comma
id|servernum
comma
id|mfrr
)paren
suffix:semicolon
)brace
DECL|function|plpar_xirr
r_static
r_inline
r_int
id|plpar_xirr
c_func
(paren
r_int
r_int
op_star
id|xirr_ret
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
r_return
id|plpar_hcall
c_func
(paren
id|H_XIRR
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|xirr_ret
comma
op_amp
id|dummy
comma
op_amp
id|dummy
)paren
suffix:semicolon
)brace
DECL|function|pSeriesLP_xirr_info_get
r_static
r_int
id|pSeriesLP_xirr_info_get
c_func
(paren
r_int
id|n_cpu
)paren
(brace
r_int
r_int
id|lpar_rc
suffix:semicolon
r_int
r_int
id|return_value
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_xirr
c_func
(paren
op_amp
id|return_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
id|panic
c_func
(paren
l_string|&quot; bad return code xirr - rc = %lx &bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|return_value
suffix:semicolon
)brace
DECL|function|pSeriesLP_xirr_info_set
r_static
r_void
id|pSeriesLP_xirr_info_set
c_func
(paren
r_int
id|n_cpu
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|lpar_rc
suffix:semicolon
r_int
r_int
id|val64
op_assign
id|value
op_amp
l_int|0xffffffff
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_eoi
c_func
(paren
id|val64
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
id|panic
c_func
(paren
l_string|&quot;bad return code EOI - rc = %ld, value=%lx&bslash;n&quot;
comma
id|lpar_rc
comma
id|val64
)paren
suffix:semicolon
)brace
DECL|function|pSeriesLP_cppr_info
r_void
id|pSeriesLP_cppr_info
c_func
(paren
r_int
id|n_cpu
comma
id|u8
id|value
)paren
(brace
r_int
r_int
id|lpar_rc
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_cppr
c_func
(paren
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
id|panic
c_func
(paren
l_string|&quot;bad return code cppr - rc = %lx&bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
)brace
DECL|function|pSeriesLP_qirr_info
r_static
r_void
id|pSeriesLP_qirr_info
c_func
(paren
r_int
id|n_cpu
comma
id|u8
id|value
)paren
(brace
r_int
r_int
id|lpar_rc
suffix:semicolon
id|lpar_rc
op_assign
id|plpar_ipi
c_func
(paren
id|get_hard_smp_processor_id
c_func
(paren
id|n_cpu
)paren
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpar_rc
op_ne
id|H_Success
)paren
id|panic
c_func
(paren
l_string|&quot;bad return code qirr - rc = %lx&bslash;n&quot;
comma
id|lpar_rc
)paren
suffix:semicolon
)brace
DECL|variable|pSeriesLP_ops
id|xics_ops
id|pSeriesLP_ops
op_assign
(brace
id|pSeriesLP_xirr_info_get
comma
id|pSeriesLP_xirr_info_set
comma
id|pSeriesLP_cppr_info
comma
id|pSeriesLP_qirr_info
)brace
suffix:semicolon
DECL|function|xics_startup
r_static
r_int
r_int
id|xics_startup
c_func
(paren
r_int
r_int
id|virq
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
id|irq
op_assign
id|irq_offset_down
c_func
(paren
id|virq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|radix_tree_insert
c_func
(paren
op_amp
id|irq_map
comma
id|virt_irq_to_real
c_func
(paren
id|irq
)paren
comma
op_amp
id|virt_irq_to_real_map
(braket
id|irq
)braket
)paren
op_eq
op_minus
id|ENOMEM
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Out of memory creating real -&gt; virtual&quot;
l_string|&quot; IRQ mapping for irq %u (real 0x%x)&bslash;n&quot;
comma
id|virq
comma
id|virt_irq_to_real
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
id|xics_enable_irq
c_func
(paren
id|virq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* return value is ignored */
)brace
DECL|function|real_irq_to_virt
r_static
r_int
r_int
id|real_irq_to_virt
c_func
(paren
r_int
r_int
id|real_irq
)paren
(brace
r_int
r_int
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
id|radix_tree_lookup
c_func
(paren
op_amp
id|irq_map
comma
id|real_irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
l_int|NULL
)paren
r_return
id|NO_IRQ
suffix:semicolon
r_return
id|ptr
op_minus
id|virt_irq_to_real_map
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|function|get_irq_server
r_static
r_int
id|get_irq_server
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|server
suffix:semicolon
macro_line|#ifdef CONFIG_IRQ_ALL_CPUS
multiline_comment|/* For the moment only implement delivery to all cpus or one cpu */
r_if
c_cond
(paren
id|smp_threads_ready
)paren
(brace
id|cpumask_t
id|cpumask
op_assign
id|irq_affinity
(braket
id|irq
)braket
suffix:semicolon
id|cpumask_t
id|tmp
op_assign
id|CPU_MASK_NONE
suffix:semicolon
r_if
c_cond
(paren
id|cpus_equal
c_func
(paren
id|cpumask
comma
id|CPU_MASK_ALL
)paren
)paren
(brace
id|server
op_assign
id|default_distrib_server
suffix:semicolon
)brace
r_else
(brace
id|cpus_and
c_func
(paren
id|tmp
comma
id|cpu_online_map
comma
id|cpumask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|tmp
)paren
)paren
id|server
op_assign
id|default_distrib_server
suffix:semicolon
r_else
id|server
op_assign
id|get_hard_smp_processor_id
c_func
(paren
id|first_cpu
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|server
op_assign
id|default_server
suffix:semicolon
)brace
macro_line|#else
id|server
op_assign
id|default_server
suffix:semicolon
macro_line|#endif
r_return
id|server
suffix:semicolon
)brace
macro_line|#else
DECL|function|get_irq_server
r_static
r_int
id|get_irq_server
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
id|default_server
suffix:semicolon
)brace
macro_line|#endif
DECL|function|xics_enable_irq
r_static
r_void
id|xics_enable_irq
c_func
(paren
r_int
r_int
id|virq
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
r_int
id|call_status
suffix:semicolon
r_int
r_int
id|server
suffix:semicolon
id|irq
op_assign
id|virt_irq_to_real
c_func
(paren
id|irq_offset_down
c_func
(paren
id|virq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|XICS_IPI
)paren
r_return
suffix:semicolon
id|server
op_assign
id|get_irq_server
c_func
(paren
id|virq
)paren
suffix:semicolon
id|call_status
op_assign
id|rtas_call
c_func
(paren
id|ibm_set_xive
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
id|irq
comma
id|server
comma
id|DEFAULT_PRIORITY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|call_status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xics_enable_irq: irq=%d: ibm_set_xive &quot;
l_string|&quot;returned %x&bslash;n&quot;
comma
id|irq
comma
id|call_status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Now unmask the interrupt (often a no-op) */
id|call_status
op_assign
id|rtas_call
c_func
(paren
id|ibm_int_on
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|call_status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xics_enable_irq: irq=%d: ibm_int_on &quot;
l_string|&quot;returned %x&bslash;n&quot;
comma
id|irq
comma
id|call_status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|xics_disable_real_irq
r_static
r_void
id|xics_disable_real_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|call_status
suffix:semicolon
r_int
r_int
id|server
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|XICS_IPI
)paren
r_return
suffix:semicolon
id|call_status
op_assign
id|rtas_call
c_func
(paren
id|ibm_int_off
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|call_status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xics_disable_real_irq: irq=%d: &quot;
l_string|&quot;ibm_int_off returned %x&bslash;n&quot;
comma
id|irq
comma
id|call_status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|server
op_assign
id|get_irq_server
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* Have to set XIVE to 0xff to be able to remove a slot */
id|call_status
op_assign
id|rtas_call
c_func
(paren
id|ibm_set_xive
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
id|irq
comma
id|server
comma
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|call_status
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xics_disable_irq: irq=%d: ibm_set_xive(0xff)&quot;
l_string|&quot; returned %x&bslash;n&quot;
comma
id|irq
comma
id|call_status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|xics_disable_irq
r_static
r_void
id|xics_disable_irq
c_func
(paren
r_int
r_int
id|virq
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
id|irq
op_assign
id|virt_irq_to_real
c_func
(paren
id|irq_offset_down
c_func
(paren
id|virq
)paren
)paren
suffix:semicolon
id|xics_disable_real_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|xics_end_irq
r_static
r_void
id|xics_end_irq
c_func
(paren
r_int
r_int
id|irq
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
id|iosync
c_func
(paren
)paren
suffix:semicolon
id|ops
op_member_access_from_pointer
id|xirr_info_set
c_func
(paren
id|cpu
comma
(paren
(paren
l_int|0xff
op_lshift
l_int|24
)paren
op_or
(paren
id|virt_irq_to_real
c_func
(paren
id|irq_offset_down
c_func
(paren
id|irq
)paren
)paren
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|xics_mask_and_ack_irq
r_static
r_void
id|xics_mask_and_ack_irq
c_func
(paren
r_int
r_int
id|irq
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
r_if
c_cond
(paren
id|irq
OL
id|irq_offset_value
c_func
(paren
)paren
)paren
(brace
id|i8259_pic
dot
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
id|iosync
c_func
(paren
)paren
suffix:semicolon
id|ops
op_member_access_from_pointer
id|xirr_info_set
c_func
(paren
id|cpu
comma
(paren
(paren
l_int|0xff
op_lshift
l_int|24
)paren
op_or
id|xics_irq_8259_cascade_real
)paren
)paren
suffix:semicolon
id|iosync
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|xics_get_irq
r_int
id|xics_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|vec
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|vec
op_assign
id|ops
op_member_access_from_pointer
id|xirr_info_get
c_func
(paren
id|cpu
)paren
suffix:semicolon
multiline_comment|/*  (vec &gt;&gt; 24) == old priority */
id|vec
op_and_assign
l_int|0x00ffffff
suffix:semicolon
multiline_comment|/* for sanity, this had better be &lt; NR_IRQS - 16 */
r_if
c_cond
(paren
id|vec
op_eq
id|xics_irq_8259_cascade_real
)paren
(brace
id|irq
op_assign
id|i8259_irq
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* Spurious cascaded interrupt.  Still must ack xics */
id|xics_end_irq
c_func
(paren
id|irq_offset_up
c_func
(paren
id|xics_irq_8259_cascade
)paren
)paren
suffix:semicolon
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|vec
op_eq
id|XICS_IRQ_SPURIOUS
)paren
(brace
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|irq
op_assign
id|real_irq_to_virt
c_func
(paren
id|vec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|NO_IRQ
)paren
id|irq
op_assign
id|real_irq_to_virt_slowpath
c_func
(paren
id|vec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|NO_IRQ
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Interrupt %d (real) is invalid,&quot;
l_string|&quot; disabling it.&bslash;n&quot;
comma
id|vec
)paren
suffix:semicolon
id|xics_disable_real_irq
c_func
(paren
id|vec
)paren
suffix:semicolon
)brace
r_else
id|irq
op_assign
id|irq_offset_up
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_return
id|irq
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|function|xics_ipi_action
id|irqreturn_t
id|xics_ipi_action
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
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
id|ops
op_member_access_from_pointer
id|qirr_info
c_func
(paren
id|cpu
comma
l_int|0xff
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
id|cpu_is_offline
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|xics_ipi_message
(braket
id|cpu
)braket
dot
id|value
)paren
(brace
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|PPC_MSG_CALL_FUNCTION
comma
op_amp
id|xics_ipi_message
(braket
id|cpu
)braket
dot
id|value
)paren
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|smp_message_recv
c_func
(paren
id|PPC_MSG_CALL_FUNCTION
comma
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|PPC_MSG_RESCHEDULE
comma
op_amp
id|xics_ipi_message
(braket
id|cpu
)braket
dot
id|value
)paren
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|smp_message_recv
c_func
(paren
id|PPC_MSG_RESCHEDULE
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|PPC_MSG_MIGRATE_TASK
comma
op_amp
id|xics_ipi_message
(braket
id|cpu
)braket
dot
id|value
)paren
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|smp_message_recv
c_func
(paren
id|PPC_MSG_MIGRATE_TASK
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUGGER
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|PPC_MSG_DEBUGGER_BREAK
comma
op_amp
id|xics_ipi_message
(braket
id|cpu
)braket
dot
id|value
)paren
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|smp_message_recv
c_func
(paren
id|PPC_MSG_DEBUGGER_BREAK
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|xics_cause_IPI
r_void
id|xics_cause_IPI
c_func
(paren
r_int
id|cpu
)paren
(brace
id|ops
op_member_access_from_pointer
id|qirr_info
c_func
(paren
id|cpu
comma
id|IPI_PRIORITY
)paren
suffix:semicolon
)brace
DECL|function|xics_setup_cpu
r_void
id|xics_setup_cpu
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
id|ops
op_member_access_from_pointer
id|cppr_info
c_func
(paren
id|cpu
comma
l_int|0xff
)paren
suffix:semicolon
id|iosync
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
DECL|function|xics_init_IRQ
r_void
id|xics_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|intr_size
op_assign
l_int|0
suffix:semicolon
r_struct
id|device_node
op_star
id|np
suffix:semicolon
id|uint
op_star
id|ireg
comma
id|ilen
comma
id|indx
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|intr_base
op_assign
l_int|0
suffix:semicolon
r_struct
id|xics_interrupt_node
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
)brace
id|intnodes
(braket
id|NR_CPUS
)braket
suffix:semicolon
id|ppc64_boot_msg
c_func
(paren
l_int|0x20
comma
l_string|&quot;XICS Init&quot;
)paren
suffix:semicolon
id|ibm_get_xive
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,get-xive&quot;
)paren
suffix:semicolon
id|ibm_set_xive
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,set-xive&quot;
)paren
suffix:semicolon
id|ibm_int_on
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,int-on&quot;
)paren
suffix:semicolon
id|ibm_int_off
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,int-off&quot;
)paren
suffix:semicolon
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
l_int|NULL
comma
l_string|&quot;PowerPC-External-Interrupt-Presentation&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np
)paren
id|panic
c_func
(paren
l_string|&quot;xics_init_IRQ: can&squot;t find interrupt presentation&quot;
)paren
suffix:semicolon
id|nextnode
suffix:colon
id|ireg
op_assign
(paren
id|uint
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;ibm,interrupt-server-ranges&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ireg
)paren
(brace
multiline_comment|/*&n;&t;&t; * set node starting index for this node&n;&t;&t; */
id|indx
op_assign
op_star
id|ireg
suffix:semicolon
)brace
id|ireg
op_assign
(paren
id|uint
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;reg&quot;
comma
op_amp
id|ilen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ireg
)paren
id|panic
c_func
(paren
l_string|&quot;xics_init_IRQ: can&squot;t find interrupt reg property&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ilen
)paren
(brace
id|intnodes
(braket
id|indx
)braket
dot
id|addr
op_assign
(paren
r_int
r_int
)paren
op_star
id|ireg
op_increment
op_lshift
l_int|32
suffix:semicolon
id|ilen
op_sub_assign
r_sizeof
(paren
id|uint
)paren
suffix:semicolon
id|intnodes
(braket
id|indx
)braket
dot
id|addr
op_or_assign
op_star
id|ireg
op_increment
suffix:semicolon
id|ilen
op_sub_assign
r_sizeof
(paren
id|uint
)paren
suffix:semicolon
id|intnodes
(braket
id|indx
)braket
dot
id|size
op_assign
(paren
r_int
r_int
)paren
op_star
id|ireg
op_increment
op_lshift
l_int|32
suffix:semicolon
id|ilen
op_sub_assign
r_sizeof
(paren
id|uint
)paren
suffix:semicolon
id|intnodes
(braket
id|indx
)braket
dot
id|size
op_or_assign
op_star
id|ireg
op_increment
suffix:semicolon
id|ilen
op_sub_assign
r_sizeof
(paren
id|uint
)paren
suffix:semicolon
id|indx
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|indx
op_ge
id|NR_CPUS
)paren
r_break
suffix:semicolon
)brace
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
id|np
comma
l_string|&quot;PowerPC-External-Interrupt-Presentation&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|indx
OL
id|NR_CPUS
)paren
op_logical_and
id|np
)paren
r_goto
id|nextnode
suffix:semicolon
multiline_comment|/* Find the server numbers for the boot cpu. */
r_for
c_loop
(paren
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
l_int|NULL
comma
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
id|np
suffix:semicolon
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
id|np
comma
l_string|&quot;cpu&quot;
)paren
)paren
(brace
id|ireg
op_assign
(paren
id|uint
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;reg&quot;
comma
op_amp
id|ilen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ireg
op_logical_and
id|ireg
(braket
l_int|0
)braket
op_eq
id|boot_cpuid_phys
)paren
(brace
id|ireg
op_assign
(paren
id|uint
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;ibm,ppc-interrupt-gserver#s&quot;
comma
op_amp
id|ilen
)paren
suffix:semicolon
id|i
op_assign
id|ilen
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ireg
op_logical_and
id|i
OG
l_int|0
)paren
(brace
id|default_server
op_assign
id|ireg
(braket
l_int|0
)braket
suffix:semicolon
id|default_distrib_server
op_assign
id|ireg
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* take last element */
)brace
r_break
suffix:semicolon
)brace
)brace
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
id|intr_base
op_assign
id|intnodes
(braket
l_int|0
)braket
dot
id|addr
suffix:semicolon
id|intr_size
op_assign
id|intnodes
(braket
l_int|0
)braket
dot
id|size
suffix:semicolon
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
l_int|NULL
comma
l_string|&quot;interrupt-controller&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;xics: no ISA interrupt controller&bslash;n&quot;
)paren
suffix:semicolon
id|xics_irq_8259_cascade_real
op_assign
op_minus
l_int|1
suffix:semicolon
id|xics_irq_8259_cascade
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|ireg
op_assign
(paren
id|uint
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;interrupts&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ireg
)paren
id|panic
c_func
(paren
l_string|&quot;xics_init_IRQ: can&squot;t find ISA interrupts property&quot;
)paren
suffix:semicolon
id|xics_irq_8259_cascade_real
op_assign
op_star
id|ireg
suffix:semicolon
id|xics_irq_8259_cascade
op_assign
id|virt_irq_create_mapping
c_func
(paren
id|xics_irq_8259_cascade_real
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|np
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_PSERIES
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|for_each_cpu
c_func
(paren
id|i
)paren
(brace
r_int
id|hard_id
suffix:semicolon
multiline_comment|/* FIXME: Do this dynamically! --RR */
r_if
c_cond
(paren
op_logical_neg
id|cpu_present
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|hard_id
op_assign
id|get_hard_smp_processor_id
c_func
(paren
id|i
)paren
suffix:semicolon
id|xics_per_cpu
(braket
id|i
)braket
op_assign
id|ioremap
c_func
(paren
id|intnodes
(braket
id|hard_id
)braket
dot
id|addr
comma
id|intnodes
(braket
id|hard_id
)braket
dot
id|size
)paren
suffix:semicolon
)brace
macro_line|#else
id|xics_per_cpu
(braket
l_int|0
)braket
op_assign
id|ioremap
c_func
(paren
id|intr_base
comma
id|intr_size
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
)brace
r_else
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_PSERIES_LPAR
)paren
(brace
id|ops
op_assign
op_amp
id|pSeriesLP_ops
suffix:semicolon
)brace
id|xics_8259_pic.enable
op_assign
id|i8259_pic.enable
suffix:semicolon
id|xics_8259_pic.disable
op_assign
id|i8259_pic.disable
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
l_int|16
suffix:semicolon
op_increment
id|i
)paren
id|get_irq_desc
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|handler
op_assign
op_amp
id|xics_8259_pic
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
op_increment
id|i
)paren
id|get_irq_desc
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|handler
op_assign
op_amp
id|xics_pic
suffix:semicolon
id|ops
op_member_access_from_pointer
id|cppr_info
c_func
(paren
id|boot_cpuid
comma
l_int|0xff
)paren
suffix:semicolon
id|iosync
c_func
(paren
)paren
suffix:semicolon
id|ppc64_boot_msg
c_func
(paren
l_int|0x21
comma
l_string|&quot;XICS Done&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We cant do this in init_IRQ because we need the memory subsystem up for&n; * request_irq()&n; */
DECL|function|xics_setup_i8259
r_static
r_int
id|__init
id|xics_setup_i8259
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ppc64_interrupt_controller
op_eq
id|IC_PPC_XIC
op_logical_and
id|xics_irq_8259_cascade
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq_offset_up
c_func
(paren
id|xics_irq_8259_cascade
)paren
comma
id|no_action
comma
l_int|0
comma
l_string|&quot;8259 cascade&quot;
comma
l_int|NULL
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xics_setup_i8259: couldn&squot;t get 8259 &quot;
l_string|&quot;cascade&bslash;n&quot;
)paren
suffix:semicolon
id|i8259_init
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|xics_setup_i8259
id|arch_initcall
c_func
(paren
id|xics_setup_i8259
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|function|xics_request_IPIs
r_void
id|xics_request_IPIs
c_func
(paren
r_void
)paren
(brace
id|virt_irq_to_real_map
(braket
id|XICS_IPI
)braket
op_assign
id|XICS_IPI
suffix:semicolon
multiline_comment|/* IPIs are marked SA_INTERRUPT as they must run with irqs disabled */
id|request_irq
c_func
(paren
id|irq_offset_up
c_func
(paren
id|XICS_IPI
)paren
comma
id|xics_ipi_action
comma
id|SA_INTERRUPT
comma
l_string|&quot;IPI&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|get_irq_desc
c_func
(paren
id|irq_offset_up
c_func
(paren
id|XICS_IPI
)paren
)paren
op_member_access_from_pointer
id|status
op_or_assign
id|IRQ_PER_CPU
suffix:semicolon
)brace
macro_line|#endif
DECL|function|xics_set_affinity
r_static
r_void
id|xics_set_affinity
c_func
(paren
r_int
r_int
id|virq
comma
id|cpumask_t
id|cpumask
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|xics_status
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|newmask
suffix:semicolon
id|cpumask_t
id|tmp
op_assign
id|CPU_MASK_NONE
suffix:semicolon
id|irq
op_assign
id|virt_irq_to_real
c_func
(paren
id|irq_offset_down
c_func
(paren
id|virq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|XICS_IPI
op_logical_or
id|irq
op_eq
id|NO_IRQ
)paren
r_return
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|ibm_get_xive
comma
l_int|1
comma
l_int|3
comma
id|xics_status
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xics_set_affinity: irq=%d ibm,get-xive &quot;
l_string|&quot;returns %d&bslash;n&quot;
comma
id|irq
comma
id|status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* For the moment only implement delivery to all cpus or one cpu */
r_if
c_cond
(paren
id|cpus_equal
c_func
(paren
id|cpumask
comma
id|CPU_MASK_ALL
)paren
)paren
(brace
id|newmask
op_assign
id|default_distrib_server
suffix:semicolon
)brace
r_else
(brace
id|cpus_and
c_func
(paren
id|tmp
comma
id|cpu_online_map
comma
id|cpumask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|tmp
)paren
)paren
r_return
suffix:semicolon
id|newmask
op_assign
id|get_hard_smp_processor_id
c_func
(paren
id|first_cpu
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
)brace
id|status
op_assign
id|rtas_call
c_func
(paren
id|ibm_set_xive
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
id|irq
comma
id|newmask
comma
id|xics_status
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xics_set_affinity: irq=%d ibm,set-xive &quot;
l_string|&quot;returns %d&bslash;n&quot;
comma
id|irq
comma
id|status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_HOTPLUG_CPU
multiline_comment|/* Interrupts are disabled. */
DECL|function|xics_migrate_irqs_away
r_void
id|xics_migrate_irqs_away
c_func
(paren
r_void
)paren
(brace
r_int
id|set_indicator
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;set-indicator&quot;
)paren
suffix:semicolon
r_const
r_int
r_int
id|giqs
op_assign
l_int|9005UL
suffix:semicolon
multiline_comment|/* Global Interrupt Queue Server */
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|irq
comma
id|virq
comma
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|set_indicator
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
suffix:semicolon
multiline_comment|/* Reject any interrupt that was queued to us... */
id|ops
op_member_access_from_pointer
id|cppr_info
c_func
(paren
id|cpu
comma
l_int|0
)paren
suffix:semicolon
id|iosync
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Refuse any new interrupts... */
id|rtas_call
c_func
(paren
id|set_indicator
comma
l_int|3
comma
l_int|1
comma
op_amp
id|status
comma
id|giqs
comma
id|hard_smp_processor_id
c_func
(paren
)paren
comma
l_int|0
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
id|status
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Allow IPIs again... */
id|ops
op_member_access_from_pointer
id|cppr_info
c_func
(paren
id|cpu
comma
id|DEFAULT_PRIORITY
)paren
suffix:semicolon
id|iosync
c_func
(paren
)paren
suffix:semicolon
id|for_each_irq
c_func
(paren
id|virq
)paren
(brace
id|irq_desc_t
op_star
id|desc
suffix:semicolon
r_int
id|xics_status
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* We cant set affinity on ISA interrupts */
r_if
c_cond
(paren
id|virq
OL
id|irq_offset_value
c_func
(paren
)paren
)paren
r_continue
suffix:semicolon
id|desc
op_assign
id|get_irq_desc
c_func
(paren
id|virq
)paren
suffix:semicolon
id|irq
op_assign
id|virt_irq_to_real
c_func
(paren
id|irq_offset_down
c_func
(paren
id|virq
)paren
)paren
suffix:semicolon
multiline_comment|/* We need to get IPIs still. */
r_if
c_cond
(paren
id|irq
op_eq
id|XICS_IPI
op_logical_or
id|irq
op_eq
id|NO_IRQ
)paren
r_continue
suffix:semicolon
multiline_comment|/* We only need to migrate enabled IRQS */
r_if
c_cond
(paren
id|desc
op_eq
l_int|NULL
op_logical_or
id|desc-&gt;handler
op_eq
l_int|NULL
op_logical_or
id|desc-&gt;action
op_eq
l_int|NULL
op_logical_or
id|desc-&gt;handler-&gt;set_affinity
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|ibm_get_xive
comma
l_int|1
comma
l_int|3
comma
id|xics_status
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;migrate_irqs_away: irq=%d &quot;
l_string|&quot;ibm,get-xive returns %d&bslash;n&quot;
comma
id|virq
comma
id|status
)paren
suffix:semicolon
r_goto
id|unlock
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * We only support delivery to all cpus or to one cpu.&n;&t;&t; * The irq has to be migrated only in the single cpu&n;&t;&t; * case.&n;&t;&t; */
r_if
c_cond
(paren
id|xics_status
(braket
l_int|0
)braket
op_ne
id|get_hard_smp_processor_id
c_func
(paren
id|cpu
)paren
)paren
r_goto
id|unlock
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;IRQ %d affinity broken off cpu %u&bslash;n&quot;
comma
id|virq
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/* Reset affinity to all cpus */
id|xics_status
(braket
l_int|0
)braket
op_assign
id|default_distrib_server
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|ibm_set_xive
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
id|irq
comma
id|xics_status
(braket
l_int|0
)braket
comma
id|xics_status
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;migrate_irqs_away: irq=%d &quot;
l_string|&quot;ibm,set-xive returns %d&bslash;n&quot;
comma
id|virq
comma
id|status
)paren
suffix:semicolon
id|unlock
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
