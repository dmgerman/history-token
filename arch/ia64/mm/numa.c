multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * This file contains NUMA specific variables and functions which can&n; * be split away from DISCONTIGMEM and are used on NUMA machines with&n; * contiguous memory.&n; * &n; *                         2002/08/07 Erich Focht &lt;efocht@ess.nec.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/node.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/mmzone.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
multiline_comment|/*&n; * The following structures are usually initialized by ACPI or&n; * similar mechanisms and describe the NUMA characteristics of the machine.&n; */
DECL|variable|num_node_memblks
r_int
id|num_node_memblks
suffix:semicolon
DECL|variable|node_memblk
r_struct
id|node_memblk_s
id|node_memblk
(braket
id|NR_NODE_MEMBLKS
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
id|num_node_memblks
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
id|num_node_memblks
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
id|num_node_memblks
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
eof
