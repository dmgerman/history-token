multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997, 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub_mmr_t.h&gt;
macro_line|#include &lt;asm/sn/sn2/shubio.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub_mmr.h&gt;
r_extern
id|irqpda_t
op_star
id|irqpdaindr
suffix:semicolon
r_extern
id|cnodeid_t
id|master_node_get
c_func
(paren
id|vertex_hdl_t
id|vhdl
)paren
suffix:semicolon
r_extern
id|nasid_t
id|master_nasid
suffix:semicolon
multiline_comment|/*  Initialize some shub registers for interrupts, both IO and error. */
DECL|function|intr_init_vecblk
r_void
id|intr_init_vecblk
c_func
(paren
id|cnodeid_t
id|node
)paren
(brace
r_int
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|node
)paren
suffix:semicolon
id|sh_ii_int0_config_u_t
id|ii_int_config
suffix:semicolon
id|cpuid_t
id|cpu
suffix:semicolon
id|cpuid_t
id|cpu0
comma
id|cpu1
suffix:semicolon
id|nodepda_t
op_star
id|lnodepda
suffix:semicolon
id|sh_ii_int0_enable_u_t
id|ii_int_enable
suffix:semicolon
id|sh_int_node_id_config_u_t
id|node_id_config
suffix:semicolon
id|sh_local_int5_config_u_t
id|local5_config
suffix:semicolon
id|sh_local_int5_enable_u_t
id|local5_enable
suffix:semicolon
r_if
c_cond
(paren
id|is_headless_node
c_func
(paren
id|node
)paren
)paren
(brace
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
r_int
id|cnode
suffix:semicolon
multiline_comment|/* retarget all interrupts on this node to the master node. */
id|node_id_config.sh_int_node_id_config_regval
op_assign
l_int|0
suffix:semicolon
id|node_id_config.sh_int_node_id_config_s.node_id
op_assign
id|master_nasid
suffix:semicolon
id|node_id_config.sh_int_node_id_config_s.id_sel
op_assign
l_int|1
suffix:semicolon
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
id|SH_INT_NODE_ID_CONFIG
)paren
comma
id|node_id_config.sh_int_node_id_config_regval
)paren
suffix:semicolon
id|cnode
op_assign
id|nasid_to_cnodeid
c_func
(paren
id|master_nasid
)paren
suffix:semicolon
id|lnodepda
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|cpu
op_assign
id|lnodepda-&gt;node_first_cpu
suffix:semicolon
id|cpu
op_assign
id|cpu_physical_id
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|SAL_CALL
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_REGISTER_CE
comma
id|nasid
comma
id|cpu
comma
id|master_nasid
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_stuff.status
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: SN_SAL_REGISTER_CE SAL_CALL failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_else
(brace
id|lnodepda
op_assign
id|NODEPDA
c_func
(paren
id|node
)paren
suffix:semicolon
id|cpu
op_assign
id|lnodepda-&gt;node_first_cpu
suffix:semicolon
id|cpu
op_assign
id|cpu_physical_id
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the physical id&squot;s of the cpu&squot;s on this node. */
id|cpu0
op_assign
id|nasid_slice_to_cpu_physical_id
c_func
(paren
id|nasid
comma
l_int|0
)paren
suffix:semicolon
id|cpu1
op_assign
id|nasid_slice_to_cpu_physical_id
c_func
(paren
id|nasid
comma
l_int|2
)paren
suffix:semicolon
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
id|SH_PI_ERROR_MASK
)paren
comma
l_int|0
)paren
suffix:semicolon
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
id|SH_PI_CRBP_ERROR_MASK
)paren
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Config and enable UART interrupt, all nodes. */
id|local5_config.sh_local_int5_config_regval
op_assign
l_int|0
suffix:semicolon
id|local5_config.sh_local_int5_config_s.idx
op_assign
id|SGI_UART_VECTOR
suffix:semicolon
id|local5_config.sh_local_int5_config_s.pid
op_assign
id|cpu
suffix:semicolon
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
id|SH_LOCAL_INT5_CONFIG
)paren
comma
id|local5_config.sh_local_int5_config_regval
)paren
suffix:semicolon
id|local5_enable.sh_local_int5_enable_regval
op_assign
l_int|0
suffix:semicolon
id|local5_enable.sh_local_int5_enable_s.uart_int
op_assign
l_int|1
suffix:semicolon
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
id|SH_LOCAL_INT5_ENABLE
)paren
comma
id|local5_enable.sh_local_int5_enable_regval
)paren
suffix:semicolon
multiline_comment|/* The II_INT_CONFIG register for cpu 0. */
id|ii_int_config.sh_ii_int0_config_regval
op_assign
l_int|0
suffix:semicolon
id|ii_int_config.sh_ii_int0_config_s.type
op_assign
l_int|0
suffix:semicolon
id|ii_int_config.sh_ii_int0_config_s.agt
op_assign
l_int|0
suffix:semicolon
id|ii_int_config.sh_ii_int0_config_s.pid
op_assign
id|cpu0
suffix:semicolon
id|ii_int_config.sh_ii_int0_config_s.base
op_assign
l_int|0
suffix:semicolon
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
id|SH_II_INT0_CONFIG
)paren
comma
id|ii_int_config.sh_ii_int0_config_regval
)paren
suffix:semicolon
multiline_comment|/* The II_INT_CONFIG register for cpu 1. */
id|ii_int_config.sh_ii_int0_config_regval
op_assign
l_int|0
suffix:semicolon
id|ii_int_config.sh_ii_int0_config_s.type
op_assign
l_int|0
suffix:semicolon
id|ii_int_config.sh_ii_int0_config_s.agt
op_assign
l_int|0
suffix:semicolon
id|ii_int_config.sh_ii_int0_config_s.pid
op_assign
id|cpu1
suffix:semicolon
id|ii_int_config.sh_ii_int0_config_s.base
op_assign
l_int|0
suffix:semicolon
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
id|SH_II_INT1_CONFIG
)paren
comma
id|ii_int_config.sh_ii_int0_config_regval
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts for II_INT0 and 1. */
id|ii_int_enable.sh_ii_int0_enable_regval
op_assign
l_int|0
suffix:semicolon
id|ii_int_enable.sh_ii_int0_enable_s.ii_enable
op_assign
l_int|1
suffix:semicolon
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
id|SH_II_INT0_ENABLE
)paren
comma
id|ii_int_enable.sh_ii_int0_enable_regval
)paren
suffix:semicolon
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
id|SH_II_INT1_ENABLE
)paren
comma
id|ii_int_enable.sh_ii_int0_enable_regval
)paren
suffix:semicolon
)brace
DECL|function|intr_reserve_level
r_static
r_int
id|intr_reserve_level
c_func
(paren
id|cpuid_t
id|cpu
comma
r_int
id|bit
)paren
(brace
id|irqpda_t
op_star
id|irqs
op_assign
id|irqpdaindr
suffix:semicolon
r_int
id|min_shared
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|bit
OL
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|IA64_SN2_FIRST_DEVICE_VECTOR
suffix:semicolon
id|i
op_le
id|IA64_SN2_LAST_DEVICE_VECTOR
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irqs-&gt;irq_flags
(braket
id|i
)braket
op_eq
l_int|0
)paren
(brace
id|bit
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|bit
OL
l_int|0
)paren
(brace
multiline_comment|/* ran out of irqs.  Have to share.  This will be rare. */
id|min_shared
op_assign
l_int|256
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IA64_SN2_FIRST_DEVICE_VECTOR
suffix:semicolon
id|i
OL
id|IA64_SN2_LAST_DEVICE_VECTOR
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Share with the same device class */
multiline_comment|/* XXX: gross layering violation.. */
r_if
c_cond
(paren
id|irqpdaindr-&gt;curr-&gt;vendor
op_eq
id|irqpdaindr-&gt;device_dev
(braket
id|i
)braket
op_member_access_from_pointer
id|vendor
op_logical_and
id|irqpdaindr-&gt;curr-&gt;device
op_eq
id|irqpdaindr-&gt;device_dev
(braket
id|i
)braket
op_member_access_from_pointer
id|device
op_logical_and
id|irqpdaindr-&gt;share_count
(braket
id|i
)braket
OL
id|min_shared
)paren
(brace
id|min_shared
op_assign
id|irqpdaindr-&gt;share_count
(braket
id|i
)braket
suffix:semicolon
id|bit
op_assign
id|i
suffix:semicolon
)brace
)brace
id|min_shared
op_assign
l_int|256
suffix:semicolon
r_if
c_cond
(paren
id|bit
OL
l_int|0
)paren
(brace
multiline_comment|/* didn&squot;t find a matching device, just pick one. This will be */
multiline_comment|/* exceptionally rare. */
r_for
c_loop
(paren
id|i
op_assign
id|IA64_SN2_FIRST_DEVICE_VECTOR
suffix:semicolon
id|i
OL
id|IA64_SN2_LAST_DEVICE_VECTOR
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irqpdaindr-&gt;share_count
(braket
id|i
)braket
OL
id|min_shared
)paren
(brace
id|min_shared
op_assign
id|irqpdaindr-&gt;share_count
(braket
id|i
)braket
suffix:semicolon
id|bit
op_assign
id|i
suffix:semicolon
)brace
)brace
)brace
id|irqpdaindr-&gt;share_count
(braket
id|bit
)braket
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irqs-&gt;irq_flags
(braket
id|bit
)braket
op_amp
id|SN2_IRQ_SHARED
)paren
)paren
(brace
r_if
c_cond
(paren
id|irqs-&gt;irq_flags
(braket
id|bit
)braket
op_amp
id|SN2_IRQ_RESERVED
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|irqs-&gt;num_irq_used
op_increment
suffix:semicolon
)brace
id|irqs-&gt;irq_flags
(braket
id|bit
)braket
op_or_assign
id|SN2_IRQ_RESERVED
suffix:semicolon
r_return
id|bit
suffix:semicolon
)brace
DECL|function|intr_unreserve_level
r_void
id|intr_unreserve_level
c_func
(paren
id|cpuid_t
id|cpu
comma
r_int
id|bit
)paren
(brace
id|irqpda_t
op_star
id|irqs
op_assign
id|irqpdaindr
suffix:semicolon
r_if
c_cond
(paren
id|irqs-&gt;irq_flags
(braket
id|bit
)braket
op_amp
id|SN2_IRQ_RESERVED
)paren
(brace
id|irqs-&gt;num_irq_used
op_decrement
suffix:semicolon
id|irqs-&gt;irq_flags
(braket
id|bit
)braket
op_and_assign
op_complement
id|SN2_IRQ_RESERVED
suffix:semicolon
)brace
)brace
DECL|function|intr_connect_level
r_int
id|intr_connect_level
c_func
(paren
id|cpuid_t
id|cpu
comma
r_int
id|bit
)paren
(brace
id|irqpda_t
op_star
id|irqs
op_assign
id|irqpdaindr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|irqs-&gt;irq_flags
(braket
id|bit
)braket
op_amp
id|SN2_IRQ_SHARED
)paren
op_logical_and
(paren
id|irqs-&gt;irq_flags
(braket
id|bit
)braket
op_amp
id|SN2_IRQ_CONNECTED
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|irqs-&gt;irq_flags
(braket
id|bit
)braket
op_or_assign
id|SN2_IRQ_CONNECTED
suffix:semicolon
r_return
id|bit
suffix:semicolon
)brace
DECL|function|intr_disconnect_level
r_int
id|intr_disconnect_level
c_func
(paren
id|cpuid_t
id|cpu
comma
r_int
id|bit
)paren
(brace
id|irqpda_t
op_star
id|irqs
op_assign
id|irqpdaindr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|irqs-&gt;irq_flags
(braket
id|bit
)braket
op_amp
id|SN2_IRQ_CONNECTED
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|irqs-&gt;irq_flags
(braket
id|bit
)braket
op_and_assign
op_complement
id|SN2_IRQ_CONNECTED
suffix:semicolon
r_return
id|bit
suffix:semicolon
)brace
multiline_comment|/*&n; * Choose a cpu on this node.&n; *&n; * We choose the one with the least number of int&squot;s assigned to it.&n; */
DECL|function|intr_cpu_choose_from_node
r_static
id|cpuid_t
id|intr_cpu_choose_from_node
c_func
(paren
id|cnodeid_t
id|cnode
)paren
(brace
id|cpuid_t
id|cpu
comma
id|best_cpu
op_assign
id|CPU_NONE
suffix:semicolon
r_int
id|slice
comma
id|min_count
op_assign
l_int|1000
suffix:semicolon
id|irqpda_t
op_star
id|irqs
suffix:semicolon
r_for
c_loop
(paren
id|slice
op_assign
id|CPUS_PER_NODE
op_minus
l_int|1
suffix:semicolon
id|slice
op_ge
l_int|0
suffix:semicolon
id|slice
op_decrement
)paren
(brace
r_int
id|intrs
suffix:semicolon
id|cpu
op_assign
id|cnode_slice_to_cpuid
c_func
(paren
id|cnode
comma
id|slice
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_eq
id|NR_CPUS
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
r_continue
suffix:semicolon
id|irqs
op_assign
id|irqpdaindr
suffix:semicolon
id|intrs
op_assign
id|irqs-&gt;num_irq_used
suffix:semicolon
r_if
c_cond
(paren
id|min_count
OG
id|intrs
)paren
(brace
id|min_count
op_assign
id|intrs
suffix:semicolon
id|best_cpu
op_assign
id|cpu
suffix:semicolon
r_if
c_cond
(paren
id|enable_shub_wars_1_1
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Rather than finding the best cpu, always&n;&t;&t;&t;&t; * return the first cpu.  This forces all&n;&t;&t;&t;&t; * interrupts to the same cpu&n;&t;&t;&t;&t; */
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
id|best_cpu
suffix:semicolon
)brace
multiline_comment|/*&n; * We couldn&squot;t put it on the closest node.  Try to find another one.&n; * Do a stupid round-robin assignment of the node.&n; */
DECL|function|intr_cpu_choose_node
r_static
id|cpuid_t
id|intr_cpu_choose_node
c_func
(paren
r_void
)paren
(brace
r_static
id|cnodeid_t
id|last_node
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* XXX: racy */
id|cnodeid_t
id|candidate_node
suffix:semicolon
id|cpuid_t
id|cpuid
suffix:semicolon
r_if
c_cond
(paren
id|last_node
op_ge
id|numnodes
)paren
id|last_node
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|candidate_node
op_assign
id|last_node
op_plus
l_int|1
suffix:semicolon
id|candidate_node
op_ne
id|last_node
suffix:semicolon
id|candidate_node
op_increment
)paren
(brace
r_if
c_cond
(paren
id|candidate_node
op_eq
id|numnodes
)paren
id|candidate_node
op_assign
l_int|0
suffix:semicolon
id|cpuid
op_assign
id|intr_cpu_choose_from_node
c_func
(paren
id|candidate_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpuid
op_ne
id|CPU_NONE
)paren
r_return
id|cpuid
suffix:semicolon
)brace
r_return
id|CPU_NONE
suffix:semicolon
)brace
multiline_comment|/*&n; * Find the node to assign for this interrupt.&n; *&n; * SN2 + pcibr addressing limitation:&n; *   Due to this limitation, all interrupts from a given bridge must&n; *   go to the name node.  The interrupt must also be targetted for&n; *   the same processor.  This limitation does not exist on PIC.&n; *   But, the processor limitation will stay.  The limitation will be&n; *   similar to the bedrock/xbridge limit regarding PI&squot;s&n; */
DECL|function|intr_heuristic
id|cpuid_t
id|intr_heuristic
c_func
(paren
id|vertex_hdl_t
id|dev
comma
r_int
id|req_bit
comma
r_int
op_star
id|resp_bit
)paren
(brace
id|cpuid_t
id|cpuid
suffix:semicolon
id|vertex_hdl_t
id|pconn_vhdl
suffix:semicolon
id|pcibr_soft_t
id|pcibr_soft
suffix:semicolon
r_int
id|bit
suffix:semicolon
multiline_comment|/* XXX: gross layering violation.. */
r_if
c_cond
(paren
id|hwgraph_edge_get
c_func
(paren
id|dev
comma
id|EDGE_LBL_PCI
comma
op_amp
id|pconn_vhdl
)paren
op_eq
id|GRAPH_SUCCESS
)paren
(brace
id|pcibr_soft
op_assign
id|pcibr_soft_get
c_func
(paren
id|pconn_vhdl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcibr_soft
op_logical_and
id|pcibr_soft-&gt;bsi_err_intr
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The cpu was chosen already when we assigned&n;&t;&t;&t; * the error interrupt.&n;&t;&t;&t; */
id|cpuid
op_assign
(paren
(paren
id|hub_intr_t
)paren
id|pcibr_soft-&gt;bsi_err_intr
)paren
op_member_access_from_pointer
id|i_cpuid
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Need to choose one.  Try the controlling c-brick first.&n;&t; */
id|cpuid
op_assign
id|intr_cpu_choose_from_node
c_func
(paren
id|master_node_get
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpuid
op_eq
id|CPU_NONE
)paren
id|cpuid
op_assign
id|intr_cpu_choose_node
c_func
(paren
)paren
suffix:semicolon
id|done
suffix:colon
r_if
c_cond
(paren
id|cpuid
op_ne
id|CPU_NONE
)paren
(brace
id|bit
op_assign
id|intr_reserve_level
c_func
(paren
id|cpuid
comma
id|req_bit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bit
op_ge
l_int|0
)paren
(brace
op_star
id|resp_bit
op_assign
id|bit
suffix:semicolon
r_return
id|cpuid
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;Cannot target interrupt to target cpu (%ld).&bslash;n&quot;
comma
id|cpuid
)paren
suffix:semicolon
r_return
id|CPU_NONE
suffix:semicolon
)brace
eof
