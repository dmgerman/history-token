multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * This file contains NUMA specific variables and functions which can&n; * be split away from DISCONTIGMEM and are used on NUMA machines with&n; * contiguous memory.&n; * &n; *                         2002/08/07 Erich Focht &lt;efocht@ess.nec.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/memblk.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/node.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
DECL|variable|sysfs_memblks
r_static
r_struct
id|memblk
op_star
id|sysfs_memblks
suffix:semicolon
DECL|variable|sysfs_nodes
r_static
r_struct
id|node
op_star
id|sysfs_nodes
suffix:semicolon
DECL|variable|sysfs_cpus
r_static
r_struct
id|cpu
op_star
id|sysfs_cpus
suffix:semicolon
multiline_comment|/*&n; * The following structures are usually initialized by ACPI or&n; * similar mechanisms and describe the NUMA characteristics of the machine.&n; */
DECL|variable|num_memblks
r_int
id|num_memblks
op_assign
l_int|0
suffix:semicolon
DECL|variable|node_memblk
r_struct
id|node_memblk_s
id|node_memblk
(braket
id|NR_MEMBLKS
)braket
suffix:semicolon
DECL|variable|node_cpuid
r_struct
id|node_cpuid_s
id|node_cpuid
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; * This is a matrix with &quot;distances&quot; between nodes, they should be&n; * proportional to the memory access latency ratios.&n; */
DECL|variable|numa_slit
id|u8
id|numa_slit
(braket
id|MAX_NUMNODES
op_star
id|MAX_NUMNODES
)braket
suffix:semicolon
multiline_comment|/* Identify which cnode a physical address resides on */
r_int
DECL|function|paddr_to_nid
id|paddr_to_nid
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
r_int
id|i
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
id|num_memblks
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|paddr
op_ge
id|node_memblk
(braket
id|i
)braket
dot
id|start_paddr
op_logical_and
id|paddr
OL
id|node_memblk
(braket
id|i
)braket
dot
id|start_paddr
op_plus
id|node_memblk
(braket
id|i
)braket
dot
id|size
)paren
r_break
suffix:semicolon
r_return
(paren
id|i
OL
id|num_memblks
)paren
ques
c_cond
id|node_memblk
(braket
id|i
)braket
dot
id|nid
suffix:colon
(paren
id|num_memblks
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|topology_init
r_static
r_int
id|__init
id|topology_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|sysfs_nodes
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|node
)paren
op_star
id|numnodes
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysfs_nodes
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sysfs_nodes
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|node
)paren
op_star
id|numnodes
)paren
suffix:semicolon
id|sysfs_memblks
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|memblk
)paren
op_star
id|num_memblks
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysfs_memblks
)paren
(brace
id|kfree
c_func
(paren
id|sysfs_nodes
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sysfs_memblks
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|memblk
)paren
op_star
id|num_memblks
)paren
suffix:semicolon
id|sysfs_cpus
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cpu
)paren
op_star
id|NR_CPUS
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysfs_cpus
)paren
(brace
id|kfree
c_func
(paren
id|sysfs_memblks
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sysfs_nodes
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sysfs_cpus
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cpu
)paren
op_star
id|NR_CPUS
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
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|err
op_assign
id|register_node
c_func
(paren
op_amp
id|sysfs_nodes
(braket
id|i
)braket
comma
id|i
comma
l_int|0
)paren
)paren
)paren
r_goto
id|out
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
id|num_memblks
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|err
op_assign
id|register_memblk
c_func
(paren
op_amp
id|sysfs_memblks
(braket
id|i
)braket
comma
id|i
comma
op_amp
id|sysfs_nodes
(braket
id|memblk_to_node
c_func
(paren
id|i
)paren
)braket
)paren
)paren
)paren
r_goto
id|out
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|i
)paren
)paren
r_if
c_cond
(paren
(paren
id|err
op_assign
id|register_cpu
c_func
(paren
op_amp
id|sysfs_cpus
(braket
id|i
)braket
comma
id|i
comma
op_amp
id|sysfs_nodes
(braket
id|cpu_to_node
c_func
(paren
id|i
)paren
)braket
)paren
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|topology_init
id|__initcall
c_func
(paren
id|topology_init
)paren
suffix:semicolon
eof
