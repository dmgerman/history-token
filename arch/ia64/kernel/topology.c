multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * This file contains NUMA specific variables and functions which can&n; * be split away from DISCONTIGMEM and are used on NUMA machines with&n; * contiguous memory.&n; * &t;&t;2002/08/07 Erich Focht &lt;efocht@ess.nec.de&gt;&n; * Populate cpu entries in sysfs for non-numa systems as well&n; *  &t;Intel Corporation - Ashok Raj&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/node.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/mmzone.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#ifdef CONFIG_NUMA
DECL|variable|sysfs_nodes
r_static
r_struct
id|node
op_star
id|sysfs_nodes
suffix:semicolon
macro_line|#endif
DECL|variable|sysfs_cpus
r_static
r_struct
id|ia64_cpu
op_star
id|sysfs_cpus
suffix:semicolon
DECL|function|arch_register_cpu
r_int
id|arch_register_cpu
c_func
(paren
r_int
id|num
)paren
(brace
r_struct
id|node
op_star
id|parent
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_NUMA
id|parent
op_assign
op_amp
id|sysfs_nodes
(braket
id|cpu_to_node
c_func
(paren
id|num
)paren
)braket
suffix:semicolon
macro_line|#endif /* CONFIG_NUMA */
r_return
id|register_cpu
c_func
(paren
op_amp
id|sysfs_cpus
(braket
id|num
)braket
dot
id|cpu
comma
id|num
comma
id|parent
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HOTPLUG_CPU
DECL|function|arch_unregister_cpu
r_void
id|arch_unregister_cpu
c_func
(paren
r_int
id|num
)paren
(brace
r_struct
id|node
op_star
id|parent
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_NUMA
r_int
id|node
op_assign
id|cpu_to_node
c_func
(paren
id|num
)paren
suffix:semicolon
id|parent
op_assign
op_amp
id|sysfs_nodes
(braket
id|node
)braket
suffix:semicolon
macro_line|#endif /* CONFIG_NUMA */
r_return
id|unregister_cpu
c_func
(paren
op_amp
id|sysfs_cpus
(braket
id|num
)braket
dot
id|cpu
comma
id|parent
)paren
suffix:semicolon
)brace
DECL|variable|arch_register_cpu
id|EXPORT_SYMBOL
c_func
(paren
id|arch_register_cpu
)paren
suffix:semicolon
DECL|variable|arch_unregister_cpu
id|EXPORT_SYMBOL
c_func
(paren
id|arch_unregister_cpu
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_HOTPLUG_CPU*/
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
macro_line|#ifdef CONFIG_NUMA
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
id|MAX_NUMNODES
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
id|MAX_NUMNODES
)paren
suffix:semicolon
multiline_comment|/* MCD - Do we want to register all ONLINE nodes, or all POSSIBLE nodes? */
id|for_each_online_node
c_func
(paren
id|i
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
macro_line|#endif
id|sysfs_cpus
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ia64_cpu
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
id|ia64_cpu
)paren
op_star
id|NR_CPUS
)paren
suffix:semicolon
id|for_each_present_cpu
c_func
(paren
id|i
)paren
r_if
c_cond
(paren
(paren
id|err
op_assign
id|arch_register_cpu
c_func
(paren
id|i
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
