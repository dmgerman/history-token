multiline_comment|/* &n; * arch/ppc/kernel/xics.c&n; *&n; * Copyright 2000 IBM Corporation.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &quot;i8259.h&quot;
macro_line|#include &quot;xics.h&quot;
macro_line|#include &lt;asm/ppcdebug.h&gt;
r_void
id|xics_enable_irq
c_func
(paren
id|u_int
id|irq
)paren
suffix:semicolon
r_void
id|xics_disable_irq
c_func
(paren
id|u_int
id|irq
)paren
suffix:semicolon
r_void
id|xics_mask_and_ack_irq
c_func
(paren
id|u_int
id|irq
)paren
suffix:semicolon
r_void
id|xics_end_irq
c_func
(paren
id|u_int
id|irq
)paren
suffix:semicolon
r_void
id|xics_set_affinity
c_func
(paren
r_int
r_int
id|irq_nr
comma
r_int
r_int
id|cpumask
)paren
suffix:semicolon
DECL|variable|xics_pic
r_struct
id|hw_interrupt_type
id|xics_pic
op_assign
(brace
l_string|&quot; XICS     &quot;
comma
l_int|NULL
comma
l_int|NULL
comma
id|xics_enable_irq
comma
id|xics_disable_irq
comma
id|xics_mask_and_ack_irq
comma
id|xics_end_irq
comma
id|xics_set_affinity
)brace
suffix:semicolon
DECL|variable|xics_8259_pic
r_struct
id|hw_interrupt_type
id|xics_8259_pic
op_assign
(brace
l_string|&quot; XICS/8259&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|xics_mask_and_ack_irq
comma
l_int|NULL
)brace
suffix:semicolon
DECL|macro|XICS_IPI
mdefine_line|#define XICS_IPI&t;&t;2
DECL|macro|XICS_IRQ_OFFSET
mdefine_line|#define XICS_IRQ_OFFSET&t;&t;0x10
DECL|macro|XICS_IRQ_SPURIOUS
mdefine_line|#define XICS_IRQ_SPURIOUS&t;0
multiline_comment|/* Want a priority other than 0.  Various HW issues require this. */
DECL|macro|DEFAULT_PRIORITY
mdefine_line|#define&t;DEFAULT_PRIORITY&t;5
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
DECL|struct|xics_info
r_struct
id|xics_info
(brace
DECL|member|per_cpu
r_volatile
r_struct
id|xics_ipl
op_star
id|per_cpu
(braket
id|NR_CPUS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|xics_info
r_struct
id|xics_info
id|xics_info
suffix:semicolon
DECL|variable|intr_base
r_int
r_int
r_int
id|intr_base
op_assign
l_int|0
suffix:semicolon
DECL|variable|xics_irq_8259_cascade
r_int
id|xics_irq_8259_cascade
op_assign
l_int|0
suffix:semicolon
DECL|variable|xics_irq_8259_cascade_real
r_int
id|xics_irq_8259_cascade_real
op_assign
l_int|0
suffix:semicolon
DECL|variable|default_server
r_int
r_int
id|default_server
op_assign
l_int|0xFF
suffix:semicolon
DECL|variable|default_distrib_server
r_int
r_int
id|default_distrib_server
op_assign
l_int|0
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
DECL|variable|ibm_int_off
r_int
id|ibm_int_off
suffix:semicolon
DECL|struct|xics_interrupt_node
r_struct
id|xics_interrupt_node
(brace
DECL|member|addr
r_int
r_int
r_int
id|addr
suffix:semicolon
DECL|member|size
r_int
r_int
r_int
id|size
suffix:semicolon
DECL|variable|inodes
)brace
id|inodes
(braket
id|NR_CPUS
op_star
l_int|2
)braket
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
(paren
id|xics_info.per_cpu
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
id|xics_info.per_cpu
(braket
id|n_cpu
)braket
op_member_access_from_pointer
id|xirr.word
op_assign
id|value
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
id|xics_info.per_cpu
(braket
id|n_cpu
)braket
op_member_access_from_pointer
id|xirr.bytes
(braket
l_int|0
)braket
op_assign
id|value
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
id|xics_info.per_cpu
(braket
id|n_cpu
)braket
op_member_access_from_pointer
id|qirr.bytes
(braket
l_int|0
)braket
op_assign
id|value
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
r_extern
id|xics_ops
id|pSeriesLP_ops
suffix:semicolon
r_void
DECL|function|xics_enable_irq
id|xics_enable_irq
c_func
(paren
id|u_int
id|virq
)paren
(brace
id|u_int
id|irq
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_int
id|call_status
suffix:semicolon
id|virq
op_sub_assign
id|XICS_IRQ_OFFSET
suffix:semicolon
id|irq
op_assign
id|virt_irq_to_real
c_func
(paren
id|virq
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
macro_line|#ifdef CONFIG_IRQ_ALL_CPUS
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
(paren
r_int
r_int
op_star
)paren
op_amp
id|status
comma
id|irq
comma
id|smp_threads_ready
ques
c_cond
id|default_distrib_server
suffix:colon
id|default_server
comma
id|DEFAULT_PRIORITY
)paren
suffix:semicolon
macro_line|#else
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
(paren
r_int
r_int
op_star
)paren
op_amp
id|status
comma
id|irq
comma
id|default_server
comma
id|DEFAULT_PRIORITY
)paren
suffix:semicolon
macro_line|#endif
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
l_string|&quot;xics_enable_irq: irq=%x: rtas_call failed; retn=%lx, status=%lx&bslash;n&quot;
comma
id|irq
comma
id|call_status
comma
id|status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_void
DECL|function|xics_disable_irq
id|xics_disable_irq
c_func
(paren
id|u_int
id|virq
)paren
(brace
id|u_int
id|irq
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_int
id|call_status
suffix:semicolon
id|virq
op_sub_assign
id|XICS_IRQ_OFFSET
suffix:semicolon
id|irq
op_assign
id|virt_irq_to_real
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
id|ibm_int_off
comma
l_int|1
comma
l_int|1
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|status
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
l_string|&quot;xics_disable_irq: irq=%x: rtas_call failed, retn=%lx&bslash;n&quot;
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
r_void
DECL|function|xics_end_irq
id|xics_end_irq
c_func
(paren
id|u_int
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
multiline_comment|/* actually the value overwritten by ack */
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
id|irq
op_minus
id|XICS_IRQ_OFFSET
)paren
)paren
)paren
)paren
suffix:semicolon
id|iosync
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|xics_mask_and_ack_irq
id|xics_mask_and_ack_irq
c_func
(paren
id|u_int
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
id|XICS_IRQ_OFFSET
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
r_else
(brace
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
)brace
r_int
DECL|function|xics_get_irq
id|xics_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|u_int
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
id|XICS_IRQ_OFFSET
op_plus
id|xics_irq_8259_cascade
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
op_plus
id|XICS_IRQ_OFFSET
suffix:semicolon
)brace
r_return
id|irq
suffix:semicolon
)brace
DECL|struct|xics_ipi_struct
r_struct
id|xics_ipi_struct
(brace
DECL|member|value
r_volatile
r_int
r_int
id|value
suffix:semicolon
DECL|variable|____cacheline_aligned
)brace
id|____cacheline_aligned
suffix:semicolon
r_extern
r_struct
id|xics_ipi_struct
id|xics_ipi_message
(braket
id|NR_CPUS
)braket
id|__cacheline_aligned
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|function|xics_ipi_action
r_void
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
macro_line|#ifdef CONFIG_XMON
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|PPC_MSG_XMON_BREAK
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
id|PPC_MSG_XMON_BREAK
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
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
l_int|0
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
r_void
DECL|function|xics_init_IRQ
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
id|find_type_devices
c_func
(paren
l_string|&quot;PowerPC-External-Interrupt-Presentation&quot;
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
l_string|&quot;Can&squot;t find Interrupt Presentation&bslash;n&quot;
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;Can&squot;t find Interrupt Presentation&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
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
l_int|0
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
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t find Interrupt Reg Property&bslash;n&quot;
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;Can&squot;t find Interrupt Reg Property&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ilen
)paren
(brace
id|inodes
(braket
id|indx
)braket
dot
id|addr
op_assign
(paren
r_int
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
id|inodes
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
id|inodes
(braket
id|indx
)braket
dot
id|size
op_assign
(paren
r_int
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
id|inodes
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
id|np-&gt;next
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
id|find_type_devices
c_func
(paren
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
id|np
suffix:semicolon
id|np
op_assign
id|np-&gt;next
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
id|smp_processor_id
c_func
(paren
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
id|intr_base
op_assign
id|inodes
(braket
l_int|0
)braket
dot
id|addr
suffix:semicolon
id|intr_size
op_assign
(paren
id|ulong
)paren
id|inodes
(braket
l_int|0
)braket
dot
id|size
suffix:semicolon
id|np
op_assign
id|find_type_devices
c_func
(paren
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
l_string|&quot;xics:  no ISA Interrupt Controller&bslash;n&quot;
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
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ireg
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t find ISA Interrupts Property&bslash;n&quot;
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;Can&squot;t find ISA Interrupts Property&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
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
)brace
r_if
c_cond
(paren
id|naca-&gt;platform
op_eq
id|PLATFORM_PSERIES
)paren
(brace
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
id|NR_CPUS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|xics_info.per_cpu
(braket
id|i
)braket
op_assign
id|__ioremap
c_func
(paren
(paren
id|ulong
)paren
id|inodes
(braket
id|i
)braket
dot
id|addr
comma
(paren
id|ulong
)paren
id|inodes
(braket
id|i
)braket
dot
id|size
comma
id|_PAGE_NO_CACHE
)paren
suffix:semicolon
)brace
macro_line|#else
id|xics_info.per_cpu
(braket
l_int|0
)braket
op_assign
id|__ioremap
c_func
(paren
(paren
id|ulong
)paren
id|intr_base
comma
id|intr_size
comma
id|_PAGE_NO_CACHE
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
macro_line|#ifdef CONFIG_PPC_PSERIES
multiline_comment|/* actually iSeries does not use any of xics...but it has link dependencies&n;&t; * for now, except this new one...&n;&t; */
)brace
r_else
r_if
c_cond
(paren
id|naca-&gt;platform
op_eq
id|PLATFORM_PSERIES_LPAR
)paren
(brace
id|ops
op_assign
op_amp
id|pSeriesLP_ops
suffix:semicolon
macro_line|#endif
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
id|irq_desc
(braket
id|i
)braket
dot
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
id|irq_desc
(braket
id|i
)braket
dot
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
r_if
c_cond
(paren
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
id|xics_irq_8259_cascade
op_plus
id|XICS_IRQ_OFFSET
comma
id|no_action
comma
l_int|0
comma
l_string|&quot;8259 cascade&quot;
comma
l_int|0
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xics_init_IRQ: couldn&squot;t get 8259 cascade&bslash;n&quot;
)paren
suffix:semicolon
id|i8259_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
id|real_irq_to_virt_map
(braket
id|XICS_IPI
)braket
op_assign
id|virt_irq_to_real_map
(braket
id|XICS_IPI
)braket
op_assign
id|XICS_IPI
suffix:semicolon
id|request_irq
c_func
(paren
id|XICS_IPI
op_plus
id|XICS_IRQ_OFFSET
comma
id|xics_ipi_action
comma
l_int|0
comma
l_string|&quot;IPI&quot;
comma
l_int|0
)paren
suffix:semicolon
id|irq_desc
(braket
id|XICS_IPI
op_plus
id|XICS_IRQ_OFFSET
)braket
dot
id|status
op_or_assign
id|IRQ_PER_CPU
suffix:semicolon
macro_line|#endif
id|ppc64_boot_msg
c_func
(paren
l_int|0x21
comma
l_string|&quot;XICS Done&quot;
)paren
suffix:semicolon
)brace
DECL|function|xics_isa_init
r_void
id|xics_isa_init
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|xics_irq_8259_cascade
op_plus
id|XICS_IRQ_OFFSET
comma
id|no_action
comma
l_int|0
comma
l_string|&quot;8259 cascade&quot;
comma
l_int|0
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;xics_init_IRQ: couldn&squot;t get 8259 cascade&bslash;n&quot;
)paren
suffix:semicolon
id|i8259_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|xics_set_affinity
r_void
id|xics_set_affinity
c_func
(paren
r_int
r_int
id|virq
comma
r_int
r_int
id|cpumask
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|virq
suffix:semicolon
r_int
r_int
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
r_int
id|xics_status
(braket
l_int|2
)braket
suffix:semicolon
id|u32
id|newmask
suffix:semicolon
id|virq
op_sub_assign
id|XICS_IRQ_OFFSET
suffix:semicolon
id|irq
op_assign
id|virt_irq_to_real
c_func
(paren
id|virq
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
(paren
r_void
op_star
)paren
op_amp
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
l_string|&quot;xics_set_affinity: irq=%d ibm,get-xive returns %ld&bslash;n&quot;
comma
id|irq
comma
id|status
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* For the moment only implement delivery to all cpus or one cpu */
r_if
c_cond
(paren
id|cpumask
op_eq
l_int|0xffffffff
)paren
(brace
id|newmask
op_assign
id|default_distrib_server
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|cpumask
op_amp
id|cpu_online_map
)paren
)paren
r_goto
id|out
suffix:semicolon
id|newmask
op_assign
id|find_first_bit
c_func
(paren
op_amp
id|cpumask
comma
l_int|32
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
l_string|&quot;xics_set_affinity irq=%d ibm,set-xive returns %ld&bslash;n&quot;
comma
id|irq
comma
id|status
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
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
eof
