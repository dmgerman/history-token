multiline_comment|/*&n; * Platform dependent support for SGI SN&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &quot;xtalk/xwidgetdev.h&quot;
macro_line|#include &quot;pci/pcibus_provider_defs.h&quot;
macro_line|#include &quot;pci/pcidev.h&quot;
macro_line|#include &quot;pci/pcibr_provider.h&quot;
macro_line|#include &lt;asm/sn/shub_mmr.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
r_static
r_void
id|force_interrupt
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|register_intr_pda
c_func
(paren
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
)paren
suffix:semicolon
r_static
r_void
id|unregister_intr_pda
c_func
(paren
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
)paren
suffix:semicolon
r_extern
r_int
id|sn_force_interrupt_flag
suffix:semicolon
r_extern
r_int
id|sn_ioif_inited
suffix:semicolon
DECL|variable|sn_irq
r_struct
id|sn_irq_info
op_star
op_star
id|sn_irq
suffix:semicolon
DECL|function|sn_intr_alloc
r_static
r_inline
r_uint64
id|sn_intr_alloc
c_func
(paren
id|nasid_t
id|local_nasid
comma
r_int
id|local_widget
comma
id|u64
id|sn_irq_info
comma
r_int
id|req_irq
comma
id|nasid_t
id|req_nasid
comma
r_int
id|req_slice
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
(paren
id|u64
)paren
id|SN_SAL_IOIF_INTERRUPT
comma
(paren
id|u64
)paren
id|SAL_INTR_ALLOC
comma
(paren
id|u64
)paren
id|local_nasid
comma
(paren
id|u64
)paren
id|local_widget
comma
(paren
id|u64
)paren
id|sn_irq_info
comma
(paren
id|u64
)paren
id|req_irq
comma
(paren
id|u64
)paren
id|req_nasid
comma
(paren
id|u64
)paren
id|req_slice
)paren
suffix:semicolon
r_return
id|ret_stuff.status
suffix:semicolon
)brace
DECL|function|sn_intr_free
r_static
r_inline
r_void
id|sn_intr_free
c_func
(paren
id|nasid_t
id|local_nasid
comma
r_int
id|local_widget
comma
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
(paren
id|u64
)paren
id|SN_SAL_IOIF_INTERRUPT
comma
(paren
id|u64
)paren
id|SAL_INTR_FREE
comma
(paren
id|u64
)paren
id|local_nasid
comma
(paren
id|u64
)paren
id|local_widget
comma
(paren
id|u64
)paren
id|sn_irq_info-&gt;irq_irq
comma
(paren
id|u64
)paren
id|sn_irq_info-&gt;irq_cookie
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|sn_startup_irq
r_static
r_int
r_int
id|sn_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sn_shutdown_irq
r_static
r_void
id|sn_shutdown_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|sn_disable_irq
r_static
r_void
id|sn_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|sn_enable_irq
r_static
r_void
id|sn_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|sn_ack_irq
r_static
r_void
id|sn_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_uint64
id|event_occurred
comma
id|mask
op_assign
l_int|0
suffix:semicolon
r_int
id|nasid
suffix:semicolon
id|irq
op_assign
id|irq
op_amp
l_int|0xff
suffix:semicolon
id|nasid
op_assign
id|smp_physical_node_id
c_func
(paren
)paren
suffix:semicolon
id|event_occurred
op_assign
id|HUB_L
c_func
(paren
(paren
r_uint64
op_star
)paren
id|GLOBAL_MMR_ADDR
c_func
(paren
id|nasid
comma
id|SH_EVENT_OCCURRED
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|event_occurred
op_amp
id|SH_EVENT_OCCURRED_UART_INT_MASK
)paren
(brace
id|mask
op_or_assign
(paren
l_int|1
op_lshift
id|SH_EVENT_OCCURRED_UART_INT_SHFT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|event_occurred
op_amp
id|SH_EVENT_OCCURRED_IPI_INT_MASK
)paren
(brace
id|mask
op_or_assign
(paren
l_int|1
op_lshift
id|SH_EVENT_OCCURRED_IPI_INT_SHFT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|event_occurred
op_amp
id|SH_EVENT_OCCURRED_II_INT0_MASK
)paren
(brace
id|mask
op_or_assign
(paren
l_int|1
op_lshift
id|SH_EVENT_OCCURRED_II_INT0_SHFT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|event_occurred
op_amp
id|SH_EVENT_OCCURRED_II_INT1_MASK
)paren
(brace
id|mask
op_or_assign
(paren
l_int|1
op_lshift
id|SH_EVENT_OCCURRED_II_INT1_SHFT
)paren
suffix:semicolon
)brace
id|HUB_S
c_func
(paren
(paren
r_uint64
op_star
)paren
id|GLOBAL_MMR_ADDR
c_func
(paren
id|nasid
comma
id|SH_EVENT_OCCURRED_ALIAS
)paren
comma
id|mask
)paren
suffix:semicolon
id|__set_bit
c_func
(paren
id|irq
comma
(paren
r_volatile
r_void
op_star
)paren
id|pda-&gt;sn_in_service_ivecs
)paren
suffix:semicolon
id|move_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sn_end_irq
r_static
r_void
id|sn_end_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|nasid
suffix:semicolon
r_int
id|ivec
suffix:semicolon
r_uint64
id|event_occurred
suffix:semicolon
id|ivec
op_assign
id|irq
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|ivec
op_eq
id|SGI_UART_VECTOR
)paren
(brace
id|nasid
op_assign
id|smp_physical_node_id
c_func
(paren
)paren
suffix:semicolon
id|event_occurred
op_assign
id|HUB_L
c_func
(paren
(paren
r_uint64
op_star
)paren
id|GLOBAL_MMR_ADDR
(paren
id|nasid
comma
id|SH_EVENT_OCCURRED
)paren
)paren
suffix:semicolon
multiline_comment|/* If the UART bit is set here, we may have received an &n;&t;&t; * interrupt from the UART that the driver missed.  To&n;&t;&t; * make sure, we IPI ourselves to force us to look again.&n;&t;&t; */
r_if
c_cond
(paren
id|event_occurred
op_amp
id|SH_EVENT_OCCURRED_UART_INT_MASK
)paren
(brace
id|platform_send_ipi
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|SGI_UART_VECTOR
comma
id|IA64_IPI_DM_INT
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|__clear_bit
c_func
(paren
id|ivec
comma
(paren
r_volatile
r_void
op_star
)paren
id|pda-&gt;sn_in_service_ivecs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sn_force_interrupt_flag
)paren
id|force_interrupt
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sn_set_affinity_irq
r_static
r_void
id|sn_set_affinity_irq
c_func
(paren
r_int
r_int
id|irq
comma
id|cpumask_t
id|mask
)paren
(brace
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
op_assign
id|sn_irq
(braket
id|irq
)braket
suffix:semicolon
r_struct
id|sn_irq_info
op_star
id|tmp_sn_irq_info
suffix:semicolon
r_int
id|cpuid
comma
id|cpuphys
suffix:semicolon
id|nasid_t
id|t_nasid
suffix:semicolon
multiline_comment|/* nasid to target */
r_int
id|t_slice
suffix:semicolon
multiline_comment|/* slice to target */
multiline_comment|/* allocate a temp sn_irq_info struct to get new target info */
id|tmp_sn_irq_info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|tmp_sn_irq_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp_sn_irq_info
)paren
r_return
suffix:semicolon
id|cpuid
op_assign
id|first_cpu
c_func
(paren
id|mask
)paren
suffix:semicolon
id|cpuphys
op_assign
id|cpu_physical_id
c_func
(paren
id|cpuid
)paren
suffix:semicolon
id|t_nasid
op_assign
id|cpu_physical_id_to_nasid
c_func
(paren
id|cpuphys
)paren
suffix:semicolon
id|t_slice
op_assign
id|cpu_physical_id_to_slice
c_func
(paren
id|cpuphys
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sn_irq_info
)paren
(brace
r_int
id|status
suffix:semicolon
r_int
id|local_widget
suffix:semicolon
r_uint64
id|bridge
op_assign
(paren
r_uint64
)paren
id|sn_irq_info-&gt;irq_bridge
suffix:semicolon
id|nasid_t
id|local_nasid
op_assign
id|NASID_GET
c_func
(paren
id|bridge
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bridge
)paren
r_break
suffix:semicolon
multiline_comment|/* irq is not a device interrupt */
r_if
c_cond
(paren
id|local_nasid
op_amp
l_int|1
)paren
id|local_widget
op_assign
id|TIO_SWIN_WIDGETNUM
c_func
(paren
id|bridge
)paren
suffix:semicolon
r_else
id|local_widget
op_assign
id|SWIN_WIDGETNUM
c_func
(paren
id|bridge
)paren
suffix:semicolon
multiline_comment|/* Free the old PROM sn_irq_info structure */
id|sn_intr_free
c_func
(paren
id|local_nasid
comma
id|local_widget
comma
id|sn_irq_info
)paren
suffix:semicolon
multiline_comment|/* allocate a new PROM sn_irq_info struct */
id|status
op_assign
id|sn_intr_alloc
c_func
(paren
id|local_nasid
comma
id|local_widget
comma
id|__pa
c_func
(paren
id|tmp_sn_irq_info
)paren
comma
id|irq
comma
id|t_nasid
comma
id|t_slice
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Update kernels sn_irq_info with new target info */
id|unregister_intr_pda
c_func
(paren
id|sn_irq_info
)paren
suffix:semicolon
id|sn_irq_info-&gt;irq_cpuid
op_assign
id|cpuid
suffix:semicolon
id|sn_irq_info-&gt;irq_nasid
op_assign
id|t_nasid
suffix:semicolon
id|sn_irq_info-&gt;irq_slice
op_assign
id|t_slice
suffix:semicolon
id|sn_irq_info-&gt;irq_xtalkaddr
op_assign
id|tmp_sn_irq_info-&gt;irq_xtalkaddr
suffix:semicolon
id|sn_irq_info-&gt;irq_cookie
op_assign
id|tmp_sn_irq_info-&gt;irq_cookie
suffix:semicolon
id|register_intr_pda
c_func
(paren
id|sn_irq_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_PCI_BRIDGE_ASIC
c_func
(paren
id|sn_irq_info-&gt;irq_bridge_type
)paren
)paren
(brace
id|pcibr_change_devices_irq
c_func
(paren
id|sn_irq_info
)paren
suffix:semicolon
)brace
id|sn_irq_info
op_assign
id|sn_irq_info-&gt;irq_next
suffix:semicolon
id|set_irq_affinity_info
c_func
(paren
(paren
id|irq
op_amp
l_int|0xff
)paren
comma
id|cpuphys
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_break
suffix:semicolon
multiline_comment|/* snp_affinity failed the intr_alloc */
)brace
)brace
id|kfree
c_func
(paren
id|tmp_sn_irq_info
)paren
suffix:semicolon
)brace
DECL|variable|irq_type_sn
r_struct
id|hw_interrupt_type
id|irq_type_sn
op_assign
(brace
l_string|&quot;SN hub&quot;
comma
id|sn_startup_irq
comma
id|sn_shutdown_irq
comma
id|sn_enable_irq
comma
id|sn_disable_irq
comma
id|sn_ack_irq
comma
id|sn_end_irq
comma
id|sn_set_affinity_irq
)brace
suffix:semicolon
DECL|function|sn_irq_desc
r_struct
id|irq_desc
op_star
id|sn_irq_desc
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
(paren
id|_irq_desc
op_plus
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sn_irq_to_vector
id|u8
id|sn_irq_to_vector
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
DECL|function|sn_local_vector_to_irq
r_int
r_int
id|sn_local_vector_to_irq
c_func
(paren
id|u8
id|vector
)paren
(brace
r_return
(paren
id|CPU_VECTOR_TO_IRQ
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|vector
)paren
)paren
suffix:semicolon
)brace
DECL|function|sn_irq_init
r_void
id|sn_irq_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|irq_desc_t
op_star
id|base_desc
op_assign
id|_irq_desc
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
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|base_desc
(braket
id|i
)braket
dot
id|handler
op_eq
op_amp
id|no_irq_type
)paren
(brace
id|base_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|irq_type_sn
suffix:semicolon
)brace
)brace
)brace
DECL|function|register_intr_pda
r_static
r_void
id|register_intr_pda
c_func
(paren
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
)paren
(brace
r_int
id|irq
op_assign
id|sn_irq_info-&gt;irq_irq
suffix:semicolon
r_int
id|cpu
op_assign
id|sn_irq_info-&gt;irq_cpuid
suffix:semicolon
r_if
c_cond
(paren
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_last_irq
OL
id|irq
)paren
(brace
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_last_irq
op_assign
id|irq
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_first_irq
op_eq
l_int|0
op_logical_or
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_first_irq
OG
id|irq
)paren
(brace
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_first_irq
op_assign
id|irq
suffix:semicolon
)brace
)brace
DECL|function|unregister_intr_pda
r_static
r_void
id|unregister_intr_pda
c_func
(paren
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
)paren
(brace
r_int
id|irq
op_assign
id|sn_irq_info-&gt;irq_irq
suffix:semicolon
r_int
id|cpu
op_assign
id|sn_irq_info-&gt;irq_cpuid
suffix:semicolon
r_struct
id|sn_irq_info
op_star
id|tmp_irq_info
suffix:semicolon
r_int
id|i
comma
id|foundmatch
suffix:semicolon
r_if
c_cond
(paren
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_last_irq
op_eq
id|irq
)paren
(brace
id|foundmatch
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_last_irq
op_minus
l_int|1
suffix:semicolon
id|i
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|tmp_irq_info
op_assign
id|sn_irq
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|tmp_irq_info
)paren
(brace
r_if
c_cond
(paren
id|tmp_irq_info-&gt;irq_cpuid
op_eq
id|cpu
)paren
(brace
id|foundmatch
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tmp_irq_info
op_assign
id|tmp_irq_info-&gt;irq_next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|foundmatch
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_last_irq
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_first_irq
op_eq
id|irq
)paren
(brace
id|foundmatch
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_first_irq
op_plus
l_int|1
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp_irq_info
op_assign
id|sn_irq
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|tmp_irq_info
)paren
(brace
r_if
c_cond
(paren
id|tmp_irq_info-&gt;irq_cpuid
op_eq
id|cpu
)paren
(brace
id|foundmatch
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tmp_irq_info
op_assign
id|tmp_irq_info-&gt;irq_next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|foundmatch
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|pdacpu
c_func
(paren
id|cpu
)paren
op_member_access_from_pointer
id|sn_first_irq
op_assign
(paren
(paren
id|i
op_eq
id|NR_IRQS
)paren
ques
c_cond
l_int|0
suffix:colon
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|function|sn_irq_alloc
r_struct
id|sn_irq_info
op_star
id|sn_irq_alloc
c_func
(paren
id|nasid_t
id|local_nasid
comma
r_int
id|local_widget
comma
r_int
id|irq
comma
id|nasid_t
id|nasid
comma
r_int
id|slice
)paren
(brace
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
suffix:semicolon
r_int
id|status
suffix:semicolon
id|sn_irq_info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|sn_irq_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sn_irq_info
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|sn_irq_info
comma
l_int|0x0
comma
r_sizeof
(paren
op_star
id|sn_irq_info
)paren
)paren
suffix:semicolon
id|status
op_assign
id|sn_intr_alloc
c_func
(paren
id|local_nasid
comma
id|local_widget
comma
id|__pa
c_func
(paren
id|sn_irq_info
)paren
comma
id|irq
comma
id|nasid
comma
id|slice
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|kfree
c_func
(paren
id|sn_irq_info
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_return
id|sn_irq_info
suffix:semicolon
)brace
)brace
DECL|function|sn_irq_free
r_void
id|sn_irq_free
c_func
(paren
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
)paren
(brace
r_uint64
id|bridge
op_assign
(paren
r_uint64
)paren
id|sn_irq_info-&gt;irq_bridge
suffix:semicolon
id|nasid_t
id|local_nasid
op_assign
id|NASID_GET
c_func
(paren
id|bridge
)paren
suffix:semicolon
r_int
id|local_widget
suffix:semicolon
r_if
c_cond
(paren
id|local_nasid
op_amp
l_int|1
)paren
multiline_comment|/* tio check */
id|local_widget
op_assign
id|TIO_SWIN_WIDGETNUM
c_func
(paren
id|bridge
)paren
suffix:semicolon
r_else
id|local_widget
op_assign
id|SWIN_WIDGETNUM
c_func
(paren
id|bridge
)paren
suffix:semicolon
id|sn_intr_free
c_func
(paren
id|local_nasid
comma
id|local_widget
comma
id|sn_irq_info
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sn_irq_info
)paren
suffix:semicolon
)brace
DECL|function|sn_irq_fixup
r_void
id|sn_irq_fixup
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci_dev
comma
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
)paren
(brace
id|nasid_t
id|nasid
op_assign
id|sn_irq_info-&gt;irq_nasid
suffix:semicolon
r_int
id|slice
op_assign
id|sn_irq_info-&gt;irq_slice
suffix:semicolon
r_int
id|cpu
op_assign
id|nasid_slice_to_cpuid
c_func
(paren
id|nasid
comma
id|slice
)paren
suffix:semicolon
id|sn_irq_info-&gt;irq_cpuid
op_assign
id|cpu
suffix:semicolon
id|sn_irq_info-&gt;irq_pciioinfo
op_assign
id|SN_PCIDEV_INFO
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
multiline_comment|/* link it into the sn_irq[irq] list */
id|sn_irq_info-&gt;irq_next
op_assign
id|sn_irq
(braket
id|sn_irq_info-&gt;irq_irq
)braket
suffix:semicolon
id|sn_irq
(braket
id|sn_irq_info-&gt;irq_irq
)braket
op_assign
id|sn_irq_info
suffix:semicolon
(paren
r_void
)paren
id|register_intr_pda
c_func
(paren
id|sn_irq_info
)paren
suffix:semicolon
)brace
DECL|function|force_interrupt
r_static
r_void
id|force_interrupt
c_func
(paren
r_int
id|irq
)paren
(brace
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sn_ioif_inited
)paren
r_return
suffix:semicolon
id|sn_irq_info
op_assign
id|sn_irq
(braket
id|irq
)braket
suffix:semicolon
r_while
c_loop
(paren
id|sn_irq_info
)paren
(brace
r_if
c_cond
(paren
id|IS_PCI_BRIDGE_ASIC
c_func
(paren
id|sn_irq_info-&gt;irq_bridge_type
)paren
op_logical_and
(paren
id|sn_irq_info-&gt;irq_bridge
op_ne
l_int|NULL
)paren
)paren
(brace
id|pcibr_force_interrupt
c_func
(paren
id|sn_irq_info
)paren
suffix:semicolon
)brace
id|sn_irq_info
op_assign
id|sn_irq_info-&gt;irq_next
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Check for lost interrupts.  If the PIC int_status reg. says that&n; * an interrupt has been sent, but not handled, and the interrupt&n; * is not pending in either the cpu irr regs or in the soft irr regs,&n; * and the interrupt is not in service, then the interrupt may have&n; * been lost.  Force an interrupt on that pin.  It is possible that&n; * the interrupt is in flight, so we may generate a spurious interrupt,&n; * but we should never miss a real lost interrupt.&n; */
DECL|function|sn_check_intr
r_static
r_void
id|sn_check_intr
c_func
(paren
r_int
id|irq
comma
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
)paren
(brace
r_uint64
id|regval
suffix:semicolon
r_int
id|irr_reg_num
suffix:semicolon
r_int
id|irr_bit
suffix:semicolon
r_uint64
id|irr_reg
suffix:semicolon
r_struct
id|pcidev_info
op_star
id|pcidev_info
suffix:semicolon
r_struct
id|pcibus_info
op_star
id|pcibus_info
suffix:semicolon
id|pcidev_info
op_assign
(paren
r_struct
id|pcidev_info
op_star
)paren
id|sn_irq_info-&gt;irq_pciioinfo
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pcidev_info
)paren
r_return
suffix:semicolon
id|pcibus_info
op_assign
(paren
r_struct
id|pcibus_info
op_star
)paren
id|pcidev_info-&gt;pdi_host_pcidev_info
op_member_access_from_pointer
id|pdi_pcibus_info
suffix:semicolon
id|regval
op_assign
id|pcireg_intr_status_get
c_func
(paren
id|pcibus_info
)paren
suffix:semicolon
id|irr_reg_num
op_assign
id|irq_to_vector
c_func
(paren
id|irq
)paren
op_div
l_int|64
suffix:semicolon
id|irr_bit
op_assign
id|irq_to_vector
c_func
(paren
id|irq
)paren
op_mod
l_int|64
suffix:semicolon
r_switch
c_cond
(paren
id|irr_reg_num
)paren
(brace
r_case
l_int|0
suffix:colon
id|irr_reg
op_assign
id|ia64_getreg
c_func
(paren
id|_IA64_REG_CR_IRR0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|irr_reg
op_assign
id|ia64_getreg
c_func
(paren
id|_IA64_REG_CR_IRR1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|irr_reg
op_assign
id|ia64_getreg
c_func
(paren
id|_IA64_REG_CR_IRR2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|irr_reg
op_assign
id|ia64_getreg
c_func
(paren
id|_IA64_REG_CR_IRR3
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|irr_bit
comma
op_amp
id|irr_reg
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|irq
comma
id|pda-&gt;sn_soft_irr
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|irq
comma
id|pda-&gt;sn_in_service_ivecs
)paren
)paren
(brace
id|regval
op_and_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|sn_irq_info-&gt;irq_int_bit
op_amp
id|regval
op_amp
id|sn_irq_info-&gt;irq_last_intr
)paren
(brace
id|regval
op_and_assign
op_complement
(paren
id|sn_irq_info
op_member_access_from_pointer
id|irq_int_bit
op_amp
id|regval
)paren
suffix:semicolon
id|pcibr_force_interrupt
c_func
(paren
id|sn_irq_info
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
id|sn_irq_info-&gt;irq_last_intr
op_assign
id|regval
suffix:semicolon
)brace
DECL|function|sn_lb_int_war_check
r_void
id|sn_lb_int_war_check
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sn_ioif_inited
op_logical_or
id|pda-&gt;sn_first_irq
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pda-&gt;sn_first_irq
suffix:semicolon
id|i
op_le
id|pda-&gt;sn_last_irq
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|sn_irq_info
op_star
id|sn_irq_info
op_assign
id|sn_irq
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|sn_irq_info
)paren
(brace
multiline_comment|/* Only call for PCI bridges that are fully initialized. */
r_if
c_cond
(paren
id|IS_PCI_BRIDGE_ASIC
c_func
(paren
id|sn_irq_info-&gt;irq_bridge_type
)paren
op_logical_and
(paren
id|sn_irq_info-&gt;irq_bridge
op_ne
l_int|NULL
)paren
)paren
(brace
id|sn_check_intr
c_func
(paren
id|i
comma
id|sn_irq_info
)paren
suffix:semicolon
)brace
id|sn_irq_info
op_assign
id|sn_irq_info-&gt;irq_next
suffix:semicolon
)brace
)brace
)brace
eof
