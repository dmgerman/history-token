multiline_comment|/*&n; * Platform dependent support for SGI SN&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio_private.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub_mmr.h&gt;
r_static
r_void
id|force_interrupt
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|pcibr_force_interrupt
c_func
(paren
id|pcibr_intr_t
id|intr
)paren
suffix:semicolon
r_extern
r_int
id|sn_force_interrupt_flag
suffix:semicolon
DECL|struct|sn_intr_list_t
r_struct
id|sn_intr_list_t
(brace
DECL|member|next
r_struct
id|sn_intr_list_t
op_star
id|next
suffix:semicolon
DECL|member|intr
id|pcibr_intr_t
id|intr
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|sn_intr_list
r_static
r_struct
id|sn_intr_list_t
op_star
id|sn_intr_list
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_static
r_int
r_int
DECL|function|sn_startup_irq
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
r_static
r_void
DECL|function|sn_shutdown_irq
id|sn_shutdown_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
r_static
r_void
DECL|function|sn_disable_irq
id|sn_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
r_static
r_void
DECL|function|sn_enable_irq
id|sn_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
r_static
r_void
DECL|function|sn_ack_irq
id|sn_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
)brace
r_static
r_void
DECL|function|sn_end_irq
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
r_int
r_int
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
r_int
r_int
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
singleline_comment|// If the UART bit is set here, we may have received an interrupt from the
singleline_comment|// UART that the driver missed.  To make sure, we IPI ourselves to force us
singleline_comment|// to look again.
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
r_static
r_void
DECL|function|sn_set_affinity_irq
id|sn_set_affinity_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|cpu
)paren
(brace
macro_line|#if CONFIG_SMP
r_int
id|redir
op_assign
l_int|0
suffix:semicolon
r_struct
id|sn_intr_list_t
op_star
id|p
op_assign
id|sn_intr_list
(braket
id|irq
)braket
suffix:semicolon
id|pcibr_intr_t
id|intr
suffix:semicolon
r_extern
r_void
id|sn_shub_redirect_intr
c_func
(paren
id|pcibr_intr_t
id|intr
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_void
id|sn_tio_redirect_intr
c_func
(paren
id|pcibr_intr_t
id|intr
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|intr
op_assign
id|p-&gt;intr
suffix:semicolon
r_if
c_cond
(paren
id|intr
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|sn_shub_redirect_intr
c_func
(paren
id|intr
comma
id|cpu
)paren
suffix:semicolon
(paren
r_void
)paren
id|set_irq_affinity_info
c_func
(paren
id|irq
comma
id|cpu_physical_id
c_func
(paren
id|intr-&gt;bi_cpu
)paren
comma
id|redir
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
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
r_struct
id|irq_desc
op_star
DECL|function|sn_irq_desc
id|sn_irq_desc
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_assign
id|SN_IVEC_FROM_IRQ
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
id|_irq_desc
op_plus
id|irq
suffix:semicolon
)brace
id|u8
DECL|function|sn_irq_to_vector
id|sn_irq_to_vector
c_func
(paren
id|u8
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
r_int
r_int
DECL|function|sn_local_vector_to_irq
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
r_void
DECL|function|sn_irq_init
id|sn_irq_init
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
r_void
DECL|function|register_pcibr_intr
id|register_pcibr_intr
c_func
(paren
r_int
id|irq
comma
id|pcibr_intr_t
id|intr
)paren
(brace
r_struct
id|sn_intr_list_t
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sn_intr_list_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_struct
id|sn_intr_list_t
op_star
id|list
suffix:semicolon
r_int
id|cpu
op_assign
id|intr-&gt;bi_cpu
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
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|panic
c_func
(paren
l_string|&quot;Could not allocate memory for sn_intr_list_t&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|list
op_assign
id|sn_intr_list
(braket
id|irq
)braket
)paren
)paren
(brace
r_while
c_loop
(paren
id|list-&gt;next
)paren
id|list
op_assign
id|list-&gt;next
suffix:semicolon
id|list-&gt;next
op_assign
id|p
suffix:semicolon
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;intr
op_assign
id|intr
suffix:semicolon
)brace
r_else
(brace
id|sn_intr_list
(braket
id|irq
)braket
op_assign
id|p
suffix:semicolon
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;intr
op_assign
id|intr
suffix:semicolon
)brace
)brace
r_void
DECL|function|force_polled_int
id|force_polled_int
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|sn_intr_list_t
op_star
id|p
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
id|p
op_assign
id|sn_intr_list
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;intr
)paren
(brace
id|pcibr_force_interrupt
c_func
(paren
id|p-&gt;intr
)paren
suffix:semicolon
)brace
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
)brace
r_static
r_void
DECL|function|force_interrupt
id|force_interrupt
c_func
(paren
r_int
id|irq
)paren
(brace
r_struct
id|sn_intr_list_t
op_star
id|p
op_assign
id|sn_intr_list
(braket
id|irq
)braket
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;intr
)paren
(brace
id|pcibr_force_interrupt
c_func
(paren
id|p-&gt;intr
)paren
suffix:semicolon
)brace
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;Check for lost interrupts.  If the PIC int_status reg. says that&n;an interrupt has been sent, but not handled, and the interrupt&n;is not pending in either the cpu irr regs or in the soft irr regs,&n;and the interrupt is not in service, then the interrupt may have&n;been lost.  Force an interrupt on that pin.  It is possible that&n;the interrupt is in flight, so we may generate a spurious interrupt,&n;but we should never miss a real lost interrupt.&n;*/
r_static
r_void
DECL|function|sn_check_intr
id|sn_check_intr
c_func
(paren
r_int
id|irq
comma
id|pcibr_intr_t
id|intr
)paren
(brace
r_int
r_int
id|regval
suffix:semicolon
r_int
id|irr_reg_num
suffix:semicolon
r_int
id|irr_bit
suffix:semicolon
r_int
r_int
id|irr_reg
suffix:semicolon
id|regval
op_assign
id|pcireg_intr_status_get
c_func
(paren
id|intr-&gt;bi_soft
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
id|intr-&gt;bi_ibits
op_amp
id|regval
op_amp
id|intr-&gt;bi_last_intr
)paren
(brace
id|regval
op_and_assign
op_complement
(paren
id|intr-&gt;bi_ibits
op_amp
id|regval
)paren
suffix:semicolon
id|pcibr_force_interrupt
c_func
(paren
id|intr
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
id|intr-&gt;bi_last_intr
op_assign
id|regval
suffix:semicolon
)brace
r_void
DECL|function|sn_lb_int_war_check
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
id|sn_intr_list_t
op_star
id|p
op_assign
id|sn_intr_list
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
)paren
(brace
id|sn_check_intr
c_func
(paren
id|i
comma
id|p-&gt;intr
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
)brace
eof
