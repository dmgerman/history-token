multiline_comment|/*&n; * arch/ia64/kernel/domain.c&n; * Architecture specific sched-domains builder.&n; *&n; * Copyright (C) 2004 Jesse Barnes&n; * Copyright (C) 2004 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/topology.h&gt;
DECL|macro|SD_NODES_PER_DOMAIN
mdefine_line|#define SD_NODES_PER_DOMAIN 6
macro_line|#ifdef CONFIG_NUMA
multiline_comment|/**&n; * find_next_best_node - find the next node to include in a sched_domain&n; * @node: node whose sched_domain we&squot;re building&n; * @used_nodes: nodes already in the sched_domain&n; *&n; * Find the next node to include in a given scheduling domain.  Simply&n; * finds the closest node not already in the @used_nodes map.&n; *&n; * Should use nodemask_t.&n; */
DECL|function|find_next_best_node
r_static
r_int
id|__devinit
id|find_next_best_node
c_func
(paren
r_int
id|node
comma
r_int
r_int
op_star
id|used_nodes
)paren
(brace
r_int
id|i
comma
id|n
comma
id|val
comma
id|min_val
comma
id|best_node
op_assign
l_int|0
suffix:semicolon
id|min_val
op_assign
id|INT_MAX
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
id|MAX_NUMNODES
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Start at @node */
id|n
op_assign
(paren
id|node
op_plus
id|i
)paren
op_mod
id|MAX_NUMNODES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_cpus_node
c_func
(paren
id|n
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Skip already used nodes */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|n
comma
id|used_nodes
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Simple min distance search */
id|val
op_assign
id|node_distance
c_func
(paren
id|node
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
OL
id|min_val
)paren
(brace
id|min_val
op_assign
id|val
suffix:semicolon
id|best_node
op_assign
id|n
suffix:semicolon
)brace
)brace
id|set_bit
c_func
(paren
id|best_node
comma
id|used_nodes
)paren
suffix:semicolon
r_return
id|best_node
suffix:semicolon
)brace
multiline_comment|/**&n; * sched_domain_node_span - get a cpumask for a node&squot;s sched_domain&n; * @node: node whose cpumask we&squot;re constructing&n; * @size: number of nodes to include in this span&n; *&n; * Given a node, construct a good cpumask for its sched_domain to span.  It&n; * should be one that prevents unnecessary balancing, but also spreads tasks&n; * out optimally.&n; */
DECL|function|sched_domain_node_span
r_static
id|cpumask_t
id|__devinit
id|sched_domain_node_span
c_func
(paren
r_int
id|node
)paren
(brace
r_int
id|i
suffix:semicolon
id|cpumask_t
id|span
comma
id|nodemask
suffix:semicolon
id|DECLARE_BITMAP
c_func
(paren
id|used_nodes
comma
id|MAX_NUMNODES
)paren
suffix:semicolon
id|cpus_clear
c_func
(paren
id|span
)paren
suffix:semicolon
id|bitmap_zero
c_func
(paren
id|used_nodes
comma
id|MAX_NUMNODES
)paren
suffix:semicolon
id|nodemask
op_assign
id|node_to_cpumask
c_func
(paren
id|node
)paren
suffix:semicolon
id|cpus_or
c_func
(paren
id|span
comma
id|span
comma
id|nodemask
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|node
comma
id|used_nodes
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|SD_NODES_PER_DOMAIN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|next_node
op_assign
id|find_next_best_node
c_func
(paren
id|node
comma
id|used_nodes
)paren
suffix:semicolon
id|nodemask
op_assign
id|node_to_cpumask
c_func
(paren
id|next_node
)paren
suffix:semicolon
id|cpus_or
c_func
(paren
id|span
comma
id|span
comma
id|nodemask
)paren
suffix:semicolon
)brace
r_return
id|span
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * At the moment, CONFIG_SCHED_SMT is never defined, but leave it in so we&n; * can switch it on easily if needed.&n; */
macro_line|#ifdef CONFIG_SCHED_SMT
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|sched_domain
comma
id|cpu_domains
)paren
suffix:semicolon
DECL|variable|sched_group_cpus
r_static
r_struct
id|sched_group
id|sched_group_cpus
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|cpu_to_cpu_group
r_static
r_int
id|__devinit
id|cpu_to_cpu_group
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|cpu
suffix:semicolon
)brace
macro_line|#endif
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|sched_domain
comma
id|phys_domains
)paren
suffix:semicolon
DECL|variable|sched_group_phys
r_static
r_struct
id|sched_group
id|sched_group_phys
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|cpu_to_phys_group
r_static
r_int
id|__devinit
id|cpu_to_phys_group
c_func
(paren
r_int
id|cpu
)paren
(brace
macro_line|#ifdef CONFIG_SCHED_SMT
r_return
id|first_cpu
c_func
(paren
id|cpu_sibling_map
(braket
id|cpu
)braket
)paren
suffix:semicolon
macro_line|#else
r_return
id|cpu
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_NUMA
multiline_comment|/*&n; * The init_sched_build_groups can&squot;t handle what we want to do with node&n; * groups, so roll our own. Now each node has its own list of groups which&n; * gets dynamically allocated.&n; */
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|sched_domain
comma
id|node_domains
)paren
suffix:semicolon
DECL|variable|sched_group_nodes
r_static
r_struct
id|sched_group
op_star
id|sched_group_nodes
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|sched_domain
comma
id|allnodes_domains
)paren
suffix:semicolon
DECL|variable|sched_group_allnodes
r_static
r_struct
id|sched_group
id|sched_group_allnodes
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|function|cpu_to_allnodes_group
r_static
r_int
id|__devinit
id|cpu_to_allnodes_group
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|cpu_to_node
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Set up scheduler domains and groups.  Callers must hold the hotplug lock.&n; */
DECL|function|arch_init_sched_domains
r_void
id|__devinit
id|arch_init_sched_domains
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|cpumask_t
id|cpu_default_map
suffix:semicolon
multiline_comment|/*&n;&t; * Setup mask for cpus without special case scheduling requirements.&n;&t; * For now this just excludes isolated cpus, but could be used to&n;&t; * exclude other special cases in the future.&n;&t; */
id|cpus_complement
c_func
(paren
id|cpu_default_map
comma
id|cpu_isolated_map
)paren
suffix:semicolon
id|cpus_and
c_func
(paren
id|cpu_default_map
comma
id|cpu_default_map
comma
id|cpu_online_map
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up domains. Isolated domains just stay on the dummy domain.&n;&t; */
id|for_each_cpu_mask
c_func
(paren
id|i
comma
id|cpu_default_map
)paren
(brace
r_int
id|node
op_assign
id|cpu_to_node
c_func
(paren
id|i
)paren
suffix:semicolon
r_int
id|group
suffix:semicolon
r_struct
id|sched_domain
op_star
id|sd
op_assign
l_int|NULL
comma
op_star
id|p
suffix:semicolon
id|cpumask_t
id|nodemask
op_assign
id|node_to_cpumask
c_func
(paren
id|node
)paren
suffix:semicolon
id|cpus_and
c_func
(paren
id|nodemask
comma
id|nodemask
comma
id|cpu_default_map
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NUMA
r_if
c_cond
(paren
id|num_online_cpus
c_func
(paren
)paren
OG
id|SD_NODES_PER_DOMAIN
op_star
id|cpus_weight
c_func
(paren
id|nodemask
)paren
)paren
(brace
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|allnodes_domains
comma
id|i
)paren
suffix:semicolon
op_star
id|sd
op_assign
id|SD_ALLNODES_INIT
suffix:semicolon
id|sd-&gt;span
op_assign
id|cpu_default_map
suffix:semicolon
id|group
op_assign
id|cpu_to_allnodes_group
c_func
(paren
id|i
)paren
suffix:semicolon
id|sd-&gt;groups
op_assign
op_amp
id|sched_group_allnodes
(braket
id|group
)braket
suffix:semicolon
id|p
op_assign
id|sd
suffix:semicolon
)brace
r_else
id|p
op_assign
l_int|NULL
suffix:semicolon
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|node_domains
comma
id|i
)paren
suffix:semicolon
op_star
id|sd
op_assign
id|SD_NODE_INIT
suffix:semicolon
id|sd-&gt;span
op_assign
id|sched_domain_node_span
c_func
(paren
id|node
)paren
suffix:semicolon
id|sd-&gt;parent
op_assign
id|p
suffix:semicolon
id|cpus_and
c_func
(paren
id|sd-&gt;span
comma
id|sd-&gt;span
comma
id|cpu_default_map
)paren
suffix:semicolon
macro_line|#endif
id|p
op_assign
id|sd
suffix:semicolon
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|phys_domains
comma
id|i
)paren
suffix:semicolon
id|group
op_assign
id|cpu_to_phys_group
c_func
(paren
id|i
)paren
suffix:semicolon
op_star
id|sd
op_assign
id|SD_CPU_INIT
suffix:semicolon
id|sd-&gt;span
op_assign
id|nodemask
suffix:semicolon
id|sd-&gt;parent
op_assign
id|p
suffix:semicolon
id|sd-&gt;groups
op_assign
op_amp
id|sched_group_phys
(braket
id|group
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SCHED_SMT
id|p
op_assign
id|sd
suffix:semicolon
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|cpu_domains
comma
id|i
)paren
suffix:semicolon
id|group
op_assign
id|cpu_to_cpu_group
c_func
(paren
id|i
)paren
suffix:semicolon
op_star
id|sd
op_assign
id|SD_SIBLING_INIT
suffix:semicolon
id|sd-&gt;span
op_assign
id|cpu_sibling_map
(braket
id|i
)braket
suffix:semicolon
id|cpus_and
c_func
(paren
id|sd-&gt;span
comma
id|sd-&gt;span
comma
id|cpu_default_map
)paren
suffix:semicolon
id|sd-&gt;parent
op_assign
id|p
suffix:semicolon
id|sd-&gt;groups
op_assign
op_amp
id|sched_group_cpus
(braket
id|group
)braket
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_SCHED_SMT
multiline_comment|/* Set up CPU (sibling) groups */
id|for_each_cpu_mask
c_func
(paren
id|i
comma
id|cpu_default_map
)paren
(brace
id|cpumask_t
id|this_sibling_map
op_assign
id|cpu_sibling_map
(braket
id|i
)braket
suffix:semicolon
id|cpus_and
c_func
(paren
id|this_sibling_map
comma
id|this_sibling_map
comma
id|cpu_default_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|first_cpu
c_func
(paren
id|this_sibling_map
)paren
)paren
r_continue
suffix:semicolon
id|init_sched_build_groups
c_func
(paren
id|sched_group_cpus
comma
id|this_sibling_map
comma
op_amp
id|cpu_to_cpu_group
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Set up physical groups */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_NUMNODES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cpumask_t
id|nodemask
op_assign
id|node_to_cpumask
c_func
(paren
id|i
)paren
suffix:semicolon
id|cpus_and
c_func
(paren
id|nodemask
comma
id|nodemask
comma
id|cpu_default_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|nodemask
)paren
)paren
r_continue
suffix:semicolon
id|init_sched_build_groups
c_func
(paren
id|sched_group_phys
comma
id|nodemask
comma
op_amp
id|cpu_to_phys_group
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NUMA
id|init_sched_build_groups
c_func
(paren
id|sched_group_allnodes
comma
id|cpu_default_map
comma
op_amp
id|cpu_to_allnodes_group
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
id|MAX_NUMNODES
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Set up node groups */
r_struct
id|sched_group
op_star
id|sg
comma
op_star
id|prev
suffix:semicolon
id|cpumask_t
id|nodemask
op_assign
id|node_to_cpumask
c_func
(paren
id|i
)paren
suffix:semicolon
id|cpumask_t
id|domainspan
suffix:semicolon
id|cpumask_t
id|covered
op_assign
id|CPU_MASK_NONE
suffix:semicolon
r_int
id|j
suffix:semicolon
id|cpus_and
c_func
(paren
id|nodemask
comma
id|nodemask
comma
id|cpu_default_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|nodemask
)paren
)paren
r_continue
suffix:semicolon
id|domainspan
op_assign
id|sched_domain_node_span
c_func
(paren
id|i
)paren
suffix:semicolon
id|cpus_and
c_func
(paren
id|domainspan
comma
id|domainspan
comma
id|cpu_default_map
)paren
suffix:semicolon
id|sg
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sched_group
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|sched_group_nodes
(braket
id|i
)braket
op_assign
id|sg
suffix:semicolon
id|for_each_cpu_mask
c_func
(paren
id|j
comma
id|nodemask
)paren
(brace
r_struct
id|sched_domain
op_star
id|sd
suffix:semicolon
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|node_domains
comma
id|j
)paren
suffix:semicolon
id|sd-&gt;groups
op_assign
id|sg
suffix:semicolon
r_if
c_cond
(paren
id|sd-&gt;groups
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* Turn off balancing if we have no groups */
id|sd-&gt;flags
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|sg
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can not alloc domain group for node %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|sg-&gt;cpu_power
op_assign
l_int|0
suffix:semicolon
id|sg-&gt;cpumask
op_assign
id|nodemask
suffix:semicolon
id|cpus_or
c_func
(paren
id|covered
comma
id|covered
comma
id|nodemask
)paren
suffix:semicolon
id|prev
op_assign
id|sg
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|MAX_NUMNODES
suffix:semicolon
id|j
op_increment
)paren
(brace
id|cpumask_t
id|tmp
comma
id|notcovered
suffix:semicolon
r_int
id|n
op_assign
(paren
id|i
op_plus
id|j
)paren
op_mod
id|MAX_NUMNODES
suffix:semicolon
id|cpus_complement
c_func
(paren
id|notcovered
comma
id|covered
)paren
suffix:semicolon
id|cpus_and
c_func
(paren
id|tmp
comma
id|notcovered
comma
id|cpu_default_map
)paren
suffix:semicolon
id|cpus_and
c_func
(paren
id|tmp
comma
id|tmp
comma
id|domainspan
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
r_break
suffix:semicolon
id|nodemask
op_assign
id|node_to_cpumask
c_func
(paren
id|n
)paren
suffix:semicolon
id|cpus_and
c_func
(paren
id|tmp
comma
id|tmp
comma
id|nodemask
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
r_continue
suffix:semicolon
id|sg
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sched_group
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sg
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can not alloc domain group for node %d&bslash;n&quot;
comma
id|j
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sg-&gt;cpu_power
op_assign
l_int|0
suffix:semicolon
id|sg-&gt;cpumask
op_assign
id|tmp
suffix:semicolon
id|cpus_or
c_func
(paren
id|covered
comma
id|covered
comma
id|tmp
)paren
suffix:semicolon
id|prev-&gt;next
op_assign
id|sg
suffix:semicolon
id|prev
op_assign
id|sg
suffix:semicolon
)brace
id|prev-&gt;next
op_assign
id|sched_group_nodes
(braket
id|i
)braket
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Calculate CPU power for physical packages and nodes */
id|for_each_cpu_mask
c_func
(paren
id|i
comma
id|cpu_default_map
)paren
(brace
r_int
id|power
suffix:semicolon
r_struct
id|sched_domain
op_star
id|sd
suffix:semicolon
macro_line|#ifdef CONFIG_SCHED_SMT
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|cpu_domains
comma
id|i
)paren
suffix:semicolon
id|power
op_assign
id|SCHED_LOAD_SCALE
suffix:semicolon
id|sd-&gt;groups-&gt;cpu_power
op_assign
id|power
suffix:semicolon
macro_line|#endif
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|phys_domains
comma
id|i
)paren
suffix:semicolon
id|power
op_assign
id|SCHED_LOAD_SCALE
op_plus
id|SCHED_LOAD_SCALE
op_star
(paren
id|cpus_weight
c_func
(paren
id|sd-&gt;groups-&gt;cpumask
)paren
op_minus
l_int|1
)paren
op_div
l_int|10
suffix:semicolon
id|sd-&gt;groups-&gt;cpu_power
op_assign
id|power
suffix:semicolon
macro_line|#ifdef CONFIG_NUMA
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|allnodes_domains
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sd-&gt;groups
)paren
(brace
id|power
op_assign
id|SCHED_LOAD_SCALE
op_plus
id|SCHED_LOAD_SCALE
op_star
(paren
id|cpus_weight
c_func
(paren
id|sd-&gt;groups-&gt;cpumask
)paren
op_minus
l_int|1
)paren
op_div
l_int|10
suffix:semicolon
id|sd-&gt;groups-&gt;cpu_power
op_assign
id|power
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_NUMA
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_NUMNODES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|sched_group
op_star
id|sg
op_assign
id|sched_group_nodes
(braket
id|i
)braket
suffix:semicolon
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
id|sg
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|next_sg
suffix:colon
id|for_each_cpu_mask
c_func
(paren
id|j
comma
id|sg-&gt;cpumask
)paren
(brace
r_struct
id|sched_domain
op_star
id|sd
suffix:semicolon
r_int
id|power
suffix:semicolon
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|phys_domains
comma
id|j
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
op_ne
id|first_cpu
c_func
(paren
id|sd-&gt;groups-&gt;cpumask
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Only add &quot;power&quot; once for each&n;&t;&t;&t;&t; * physical package.&n;&t;&t;&t;&t; */
r_continue
suffix:semicolon
)brace
id|power
op_assign
id|SCHED_LOAD_SCALE
op_plus
id|SCHED_LOAD_SCALE
op_star
(paren
id|cpus_weight
c_func
(paren
id|sd-&gt;groups-&gt;cpumask
)paren
op_minus
l_int|1
)paren
op_div
l_int|10
suffix:semicolon
id|sg-&gt;cpu_power
op_add_assign
id|power
suffix:semicolon
)brace
id|sg
op_assign
id|sg-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|sg
op_ne
id|sched_group_nodes
(braket
id|i
)braket
)paren
r_goto
id|next_sg
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Attach the domains */
id|for_each_online_cpu
c_func
(paren
id|i
)paren
(brace
r_struct
id|sched_domain
op_star
id|sd
suffix:semicolon
macro_line|#ifdef CONFIG_SCHED_SMT
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|cpu_domains
comma
id|i
)paren
suffix:semicolon
macro_line|#else
id|sd
op_assign
op_amp
id|per_cpu
c_func
(paren
id|phys_domains
comma
id|i
)paren
suffix:semicolon
macro_line|#endif
id|cpu_attach_domain
c_func
(paren
id|sd
comma
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|function|arch_destroy_sched_domains
r_void
id|__devinit
id|arch_destroy_sched_domains
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_NUMA
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
id|MAX_NUMNODES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|sched_group
op_star
id|oldsg
comma
op_star
id|sg
op_assign
id|sched_group_nodes
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sg
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|sg
op_assign
id|sg-&gt;next
suffix:semicolon
id|next_sg
suffix:colon
id|oldsg
op_assign
id|sg
suffix:semicolon
id|sg
op_assign
id|sg-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|oldsg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldsg
op_ne
id|sched_group_nodes
(braket
id|i
)braket
)paren
r_goto
id|next_sg
suffix:semicolon
id|sched_group_nodes
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
