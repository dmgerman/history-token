multiline_comment|/*&n; * manager.c - Resource Management, Conflict Resolution, Activation and Disabling of Devices&n; *&n; * based on isapnp.c resource management (c) Jaroslav Kysela &lt;perex@suse.cz&gt;&n; * Copyright 2003 Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#ifdef CONFIG_PNP_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|variable|pnp_res_mutex
id|DECLARE_MUTEX
c_func
(paren
id|pnp_res_mutex
)paren
suffix:semicolon
DECL|function|pnp_assign_port
r_static
r_int
id|pnp_assign_port
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_port
op_star
id|rule
comma
r_int
id|idx
)paren
(brace
r_int
r_int
op_star
id|start
comma
op_star
id|end
comma
op_star
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|rule
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|PNP_MAX_PORT
)paren
(brace
id|pnp_err
c_func
(paren
l_string|&quot;More than 4 ports is incompatible with pnp specifications.&quot;
)paren
suffix:semicolon
multiline_comment|/* pretend we were successful so at least the manager won&squot;t try again */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* check if this resource has been manually set, if so skip */
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;res.port_resource
(braket
id|idx
)braket
dot
id|flags
op_amp
id|IORESOURCE_AUTO
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|start
op_assign
op_amp
id|dev-&gt;res.port_resource
(braket
id|idx
)braket
dot
id|start
suffix:semicolon
id|end
op_assign
op_amp
id|dev-&gt;res.port_resource
(braket
id|idx
)braket
dot
id|end
suffix:semicolon
id|flags
op_assign
op_amp
id|dev-&gt;res.port_resource
(braket
id|idx
)braket
dot
id|flags
suffix:semicolon
multiline_comment|/* set the initial values */
op_star
id|flags
op_or_assign
id|rule-&gt;flags
op_or
id|IORESOURCE_IO
suffix:semicolon
op_star
id|flags
op_and_assign
op_complement
id|IORESOURCE_UNSET
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rule-&gt;size
)paren
(brace
op_star
id|flags
op_or_assign
id|IORESOURCE_DISABLED
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* skip disabled resource requests */
)brace
op_star
id|start
op_assign
id|rule-&gt;min
suffix:semicolon
op_star
id|end
op_assign
op_star
id|start
op_plus
id|rule-&gt;size
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* run through until pnp_check_port is happy */
r_while
c_loop
(paren
op_logical_neg
id|pnp_check_port
c_func
(paren
id|dev
comma
id|idx
)paren
)paren
(brace
op_star
id|start
op_add_assign
id|rule-&gt;align
suffix:semicolon
op_star
id|end
op_assign
op_star
id|start
op_plus
id|rule-&gt;size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|start
OG
id|rule-&gt;max
op_logical_or
op_logical_neg
id|rule-&gt;align
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pnp_assign_mem
r_static
r_int
id|pnp_assign_mem
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_mem
op_star
id|rule
comma
r_int
id|idx
)paren
(brace
r_int
r_int
op_star
id|start
comma
op_star
id|end
comma
op_star
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|rule
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|PNP_MAX_MEM
)paren
(brace
id|pnp_err
c_func
(paren
l_string|&quot;More than 8 mems is incompatible with pnp specifications.&quot;
)paren
suffix:semicolon
multiline_comment|/* pretend we were successful so at least the manager won&squot;t try again */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* check if this resource has been manually set, if so skip */
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;res.mem_resource
(braket
id|idx
)braket
dot
id|flags
op_amp
id|IORESOURCE_AUTO
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|start
op_assign
op_amp
id|dev-&gt;res.mem_resource
(braket
id|idx
)braket
dot
id|start
suffix:semicolon
id|end
op_assign
op_amp
id|dev-&gt;res.mem_resource
(braket
id|idx
)braket
dot
id|end
suffix:semicolon
id|flags
op_assign
op_amp
id|dev-&gt;res.mem_resource
(braket
id|idx
)braket
dot
id|flags
suffix:semicolon
multiline_comment|/* set the initial values */
op_star
id|flags
op_or_assign
id|rule-&gt;flags
op_or
id|IORESOURCE_MEM
suffix:semicolon
op_star
id|flags
op_and_assign
op_complement
id|IORESOURCE_UNSET
suffix:semicolon
multiline_comment|/* convert pnp flags to standard Linux flags */
r_if
c_cond
(paren
op_logical_neg
(paren
id|rule-&gt;flags
op_amp
id|IORESOURCE_MEM_WRITEABLE
)paren
)paren
op_star
id|flags
op_or_assign
id|IORESOURCE_READONLY
suffix:semicolon
r_if
c_cond
(paren
id|rule-&gt;flags
op_amp
id|IORESOURCE_MEM_CACHEABLE
)paren
op_star
id|flags
op_or_assign
id|IORESOURCE_CACHEABLE
suffix:semicolon
r_if
c_cond
(paren
id|rule-&gt;flags
op_amp
id|IORESOURCE_MEM_RANGELENGTH
)paren
op_star
id|flags
op_or_assign
id|IORESOURCE_RANGELENGTH
suffix:semicolon
r_if
c_cond
(paren
id|rule-&gt;flags
op_amp
id|IORESOURCE_MEM_SHADOWABLE
)paren
op_star
id|flags
op_or_assign
id|IORESOURCE_SHADOWABLE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rule-&gt;size
)paren
(brace
op_star
id|flags
op_or_assign
id|IORESOURCE_DISABLED
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* skip disabled resource requests */
)brace
op_star
id|start
op_assign
id|rule-&gt;min
suffix:semicolon
op_star
id|end
op_assign
op_star
id|start
op_plus
id|rule-&gt;size
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* run through until pnp_check_mem is happy */
r_while
c_loop
(paren
op_logical_neg
id|pnp_check_mem
c_func
(paren
id|dev
comma
id|idx
)paren
)paren
(brace
op_star
id|start
op_add_assign
id|rule-&gt;align
suffix:semicolon
op_star
id|end
op_assign
op_star
id|start
op_plus
id|rule-&gt;size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|start
OG
id|rule-&gt;max
op_logical_or
op_logical_neg
id|rule-&gt;align
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pnp_assign_irq
r_static
r_int
id|pnp_assign_irq
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_irq
op_star
id|rule
comma
r_int
id|idx
)paren
(brace
r_int
r_int
op_star
id|start
comma
op_star
id|end
comma
op_star
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* IRQ priority: this table is good for i386 */
r_static
r_int
r_int
id|xtab
(braket
l_int|16
)braket
op_assign
(brace
l_int|5
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|9
comma
l_int|14
comma
l_int|15
comma
l_int|7
comma
l_int|3
comma
l_int|4
comma
l_int|13
comma
l_int|0
comma
l_int|1
comma
l_int|6
comma
l_int|8
comma
l_int|2
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|rule
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|PNP_MAX_IRQ
)paren
(brace
id|pnp_err
c_func
(paren
l_string|&quot;More than 2 irqs is incompatible with pnp specifications.&quot;
)paren
suffix:semicolon
multiline_comment|/* pretend we were successful so at least the manager won&squot;t try again */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* check if this resource has been manually set, if so skip */
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;res.irq_resource
(braket
id|idx
)braket
dot
id|flags
op_amp
id|IORESOURCE_AUTO
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|start
op_assign
op_amp
id|dev-&gt;res.irq_resource
(braket
id|idx
)braket
dot
id|start
suffix:semicolon
id|end
op_assign
op_amp
id|dev-&gt;res.irq_resource
(braket
id|idx
)braket
dot
id|end
suffix:semicolon
id|flags
op_assign
op_amp
id|dev-&gt;res.irq_resource
(braket
id|idx
)braket
dot
id|flags
suffix:semicolon
multiline_comment|/* set the initial values */
op_star
id|flags
op_or_assign
id|rule-&gt;flags
op_or
id|IORESOURCE_IRQ
suffix:semicolon
op_star
id|flags
op_and_assign
op_complement
id|IORESOURCE_UNSET
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rule-&gt;map
)paren
(brace
op_star
id|flags
op_or_assign
id|IORESOURCE_DISABLED
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* skip disabled resource requests */
)brace
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
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|rule-&gt;map
op_amp
(paren
l_int|1
op_lshift
id|xtab
(braket
id|i
)braket
)paren
)paren
(brace
op_star
id|start
op_assign
op_star
id|end
op_assign
id|xtab
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pnp_check_irq
c_func
(paren
id|dev
comma
id|idx
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnp_assign_dma
r_static
r_int
id|pnp_assign_dma
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_dma
op_star
id|rule
comma
r_int
id|idx
)paren
(brace
r_int
r_int
op_star
id|start
comma
op_star
id|end
comma
op_star
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* DMA priority: this table is good for i386 */
r_static
r_int
r_int
id|xtab
(braket
l_int|8
)braket
op_assign
(brace
l_int|1
comma
l_int|3
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|0
comma
l_int|2
comma
l_int|4
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|rule
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|PNP_MAX_DMA
)paren
(brace
id|pnp_err
c_func
(paren
l_string|&quot;More than 2 dmas is incompatible with pnp specifications.&quot;
)paren
suffix:semicolon
multiline_comment|/* pretend we were successful so at least the manager won&squot;t try again */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* check if this resource has been manually set, if so skip */
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;res.dma_resource
(braket
id|idx
)braket
dot
id|flags
op_amp
id|IORESOURCE_AUTO
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|start
op_assign
op_amp
id|dev-&gt;res.dma_resource
(braket
id|idx
)braket
dot
id|start
suffix:semicolon
id|end
op_assign
op_amp
id|dev-&gt;res.dma_resource
(braket
id|idx
)braket
dot
id|end
suffix:semicolon
id|flags
op_assign
op_amp
id|dev-&gt;res.dma_resource
(braket
id|idx
)braket
dot
id|flags
suffix:semicolon
multiline_comment|/* set the initial values */
op_star
id|flags
op_or_assign
id|rule-&gt;flags
op_or
id|IORESOURCE_DMA
suffix:semicolon
op_star
id|flags
op_and_assign
op_complement
id|IORESOURCE_UNSET
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rule-&gt;map
)paren
(brace
op_star
id|flags
op_or_assign
id|IORESOURCE_DISABLED
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* skip disabled resource requests */
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|rule-&gt;map
op_amp
(paren
l_int|1
op_lshift
id|xtab
(braket
id|i
)braket
)paren
)paren
(brace
op_star
id|start
op_assign
op_star
id|end
op_assign
id|xtab
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pnp_check_dma
c_func
(paren
id|dev
comma
id|idx
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_init_resources - Resets a resource table to default values.&n; * @table: pointer to the desired resource table&n; *&n; */
DECL|function|pnp_init_resource_table
r_void
id|pnp_init_resource_table
c_func
(paren
r_struct
id|pnp_resource_table
op_star
id|table
)paren
(brace
r_int
id|idx
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|PNP_MAX_IRQ
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|table-&gt;irq_resource
(braket
id|idx
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|table-&gt;irq_resource
(braket
id|idx
)braket
dot
id|start
op_assign
op_minus
l_int|1
suffix:semicolon
id|table-&gt;irq_resource
(braket
id|idx
)braket
dot
id|end
op_assign
op_minus
l_int|1
suffix:semicolon
id|table-&gt;irq_resource
(braket
id|idx
)braket
dot
id|flags
op_assign
id|IORESOURCE_IRQ
op_or
id|IORESOURCE_AUTO
op_or
id|IORESOURCE_UNSET
suffix:semicolon
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|PNP_MAX_DMA
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|table-&gt;dma_resource
(braket
id|idx
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|table-&gt;dma_resource
(braket
id|idx
)braket
dot
id|start
op_assign
op_minus
l_int|1
suffix:semicolon
id|table-&gt;dma_resource
(braket
id|idx
)braket
dot
id|end
op_assign
op_minus
l_int|1
suffix:semicolon
id|table-&gt;dma_resource
(braket
id|idx
)braket
dot
id|flags
op_assign
id|IORESOURCE_DMA
op_or
id|IORESOURCE_AUTO
op_or
id|IORESOURCE_UNSET
suffix:semicolon
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|PNP_MAX_PORT
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|table-&gt;port_resource
(braket
id|idx
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|table-&gt;port_resource
(braket
id|idx
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|table-&gt;port_resource
(braket
id|idx
)braket
dot
id|end
op_assign
l_int|0
suffix:semicolon
id|table-&gt;port_resource
(braket
id|idx
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
op_or
id|IORESOURCE_AUTO
op_or
id|IORESOURCE_UNSET
suffix:semicolon
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|PNP_MAX_MEM
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|table-&gt;mem_resource
(braket
id|idx
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|table-&gt;mem_resource
(braket
id|idx
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|table-&gt;mem_resource
(braket
id|idx
)braket
dot
id|end
op_assign
l_int|0
suffix:semicolon
id|table-&gt;mem_resource
(braket
id|idx
)braket
dot
id|flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_AUTO
op_or
id|IORESOURCE_UNSET
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * pnp_clean_resources - clears resources that were not manually set&n; * @res - the resources to clean&n; *&n; */
DECL|function|pnp_clean_resource_table
r_static
r_void
id|pnp_clean_resource_table
c_func
(paren
r_struct
id|pnp_resource_table
op_star
id|res
)paren
(brace
r_int
id|idx
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|PNP_MAX_IRQ
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|res-&gt;irq_resource
(braket
id|idx
)braket
dot
id|flags
op_amp
id|IORESOURCE_AUTO
)paren
)paren
r_continue
suffix:semicolon
id|res-&gt;irq_resource
(braket
id|idx
)braket
dot
id|start
op_assign
op_minus
l_int|1
suffix:semicolon
id|res-&gt;irq_resource
(braket
id|idx
)braket
dot
id|end
op_assign
op_minus
l_int|1
suffix:semicolon
id|res-&gt;irq_resource
(braket
id|idx
)braket
dot
id|flags
op_assign
id|IORESOURCE_IRQ
op_or
id|IORESOURCE_AUTO
op_or
id|IORESOURCE_UNSET
suffix:semicolon
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|PNP_MAX_DMA
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|res-&gt;dma_resource
(braket
id|idx
)braket
dot
id|flags
op_amp
id|IORESOURCE_AUTO
)paren
)paren
r_continue
suffix:semicolon
id|res-&gt;dma_resource
(braket
id|idx
)braket
dot
id|start
op_assign
op_minus
l_int|1
suffix:semicolon
id|res-&gt;dma_resource
(braket
id|idx
)braket
dot
id|end
op_assign
op_minus
l_int|1
suffix:semicolon
id|res-&gt;dma_resource
(braket
id|idx
)braket
dot
id|flags
op_assign
id|IORESOURCE_DMA
op_or
id|IORESOURCE_AUTO
op_or
id|IORESOURCE_UNSET
suffix:semicolon
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|PNP_MAX_PORT
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|res-&gt;port_resource
(braket
id|idx
)braket
dot
id|flags
op_amp
id|IORESOURCE_AUTO
)paren
)paren
r_continue
suffix:semicolon
id|res-&gt;port_resource
(braket
id|idx
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|res-&gt;port_resource
(braket
id|idx
)braket
dot
id|end
op_assign
l_int|0
suffix:semicolon
id|res-&gt;port_resource
(braket
id|idx
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
op_or
id|IORESOURCE_AUTO
op_or
id|IORESOURCE_UNSET
suffix:semicolon
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|PNP_MAX_MEM
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|res-&gt;mem_resource
(braket
id|idx
)braket
dot
id|flags
op_amp
id|IORESOURCE_AUTO
)paren
)paren
r_continue
suffix:semicolon
id|res-&gt;mem_resource
(braket
id|idx
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|res-&gt;mem_resource
(braket
id|idx
)braket
dot
id|end
op_assign
l_int|0
suffix:semicolon
id|res-&gt;mem_resource
(braket
id|idx
)braket
dot
id|flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_AUTO
op_or
id|IORESOURCE_UNSET
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * pnp_assign_resources - assigns resources to the device based on the specified dependent number&n; * @dev: pointer to the desired device&n; * @depnum: the dependent function number&n; *&n; * Only set depnum to 0 if the device does not have dependent options.&n; */
DECL|function|pnp_assign_resources
r_int
id|pnp_assign_resources
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|depnum
)paren
(brace
r_struct
id|pnp_port
op_star
id|port
suffix:semicolon
r_struct
id|pnp_mem
op_star
id|mem
suffix:semicolon
r_struct
id|pnp_irq
op_star
id|irq
suffix:semicolon
r_struct
id|pnp_dma
op_star
id|dma
suffix:semicolon
r_int
id|nport
op_assign
l_int|0
comma
id|nmem
op_assign
l_int|0
comma
id|nirq
op_assign
l_int|0
comma
id|ndma
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_can_configure
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|down
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
id|pnp_clean_resource_table
c_func
(paren
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
multiline_comment|/* start with a fresh slate */
r_if
c_cond
(paren
id|dev-&gt;independent
)paren
(brace
id|port
op_assign
id|dev-&gt;independent-&gt;port
suffix:semicolon
id|mem
op_assign
id|dev-&gt;independent-&gt;mem
suffix:semicolon
id|irq
op_assign
id|dev-&gt;independent-&gt;irq
suffix:semicolon
id|dma
op_assign
id|dev-&gt;independent-&gt;dma
suffix:semicolon
r_while
c_loop
(paren
id|port
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_assign_port
c_func
(paren
id|dev
comma
id|port
comma
id|nport
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|nport
op_increment
suffix:semicolon
id|port
op_assign
id|port-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mem
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_assign_mem
c_func
(paren
id|dev
comma
id|mem
comma
id|nmem
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|nmem
op_increment
suffix:semicolon
id|mem
op_assign
id|mem-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_assign_irq
c_func
(paren
id|dev
comma
id|irq
comma
id|nirq
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|nirq
op_increment
suffix:semicolon
id|irq
op_assign
id|irq-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|dma
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_assign_dma
c_func
(paren
id|dev
comma
id|dma
comma
id|ndma
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|ndma
op_increment
suffix:semicolon
id|dma
op_assign
id|dma-&gt;next
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|depnum
)paren
(brace
r_struct
id|pnp_option
op_star
id|dep
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
comma
id|dep
op_assign
id|dev-&gt;dependent
suffix:semicolon
id|i
OL
id|depnum
suffix:semicolon
id|i
op_increment
comma
id|dep
op_assign
id|dep-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|dep
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
id|port
op_assign
id|dep-&gt;port
suffix:semicolon
id|mem
op_assign
id|dep-&gt;mem
suffix:semicolon
id|irq
op_assign
id|dep-&gt;irq
suffix:semicolon
id|dma
op_assign
id|dep-&gt;dma
suffix:semicolon
r_while
c_loop
(paren
id|port
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_assign_port
c_func
(paren
id|dev
comma
id|port
comma
id|nport
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|nport
op_increment
suffix:semicolon
id|port
op_assign
id|port-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mem
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_assign_mem
c_func
(paren
id|dev
comma
id|mem
comma
id|nmem
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|nmem
op_increment
suffix:semicolon
id|mem
op_assign
id|mem-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_assign_irq
c_func
(paren
id|dev
comma
id|irq
comma
id|nirq
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|nirq
op_increment
suffix:semicolon
id|irq
op_assign
id|irq-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|dma
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_assign_dma
c_func
(paren
id|dev
comma
id|dma
comma
id|ndma
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|ndma
op_increment
suffix:semicolon
id|dma
op_assign
id|dma-&gt;next
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;dependent
)paren
r_goto
id|fail
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|fail
suffix:colon
id|pnp_clean_resource_table
c_func
(paren
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_manual_config_dev - Disables Auto Config and Manually sets the resource table&n; * @dev: pointer to the desired device&n; * @res: pointer to the new resource config&n; *&n; * This function can be used by drivers that want to manually set thier resources.&n; */
DECL|function|pnp_manual_config_dev
r_int
id|pnp_manual_config_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_struct
id|pnp_resource_table
op_star
id|res
comma
r_int
id|mode
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|pnp_resource_table
op_star
id|bak
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|res
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_can_configure
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|bak
op_assign
id|pnp_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pnp_resource_table
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bak
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_star
id|bak
op_assign
id|dev-&gt;res
suffix:semicolon
id|down
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
id|dev-&gt;res
op_assign
op_star
id|res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
id|PNP_CONFIG_FORCE
)paren
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PNP_MAX_PORT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_check_port
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PNP_MAX_MEM
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_check_mem
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PNP_MAX_IRQ
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_check_irq
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PNP_MAX_DMA
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_check_dma
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
)brace
)brace
id|up
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bak
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|dev-&gt;res
op_assign
op_star
id|bak
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bak
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_auto_config_dev - automatically assigns resources to a device&n; * @dev: pointer to the desired device&n; *&n; */
DECL|function|pnp_auto_config_dev
r_int
id|pnp_auto_config_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_struct
id|pnp_option
op_star
id|dep
suffix:semicolon
r_int
id|i
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_can_configure
c_func
(paren
id|dev
)paren
)paren
(brace
id|pnp_info
c_func
(paren
l_string|&quot;Device %s does not support resource configuration.&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;dependent
)paren
(brace
r_if
c_cond
(paren
id|pnp_assign_resources
c_func
(paren
id|dev
comma
l_int|0
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
id|dep
op_assign
id|dev-&gt;dependent
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|pnp_assign_resources
c_func
(paren
id|dev
comma
id|i
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* if this dependent resource failed, try the next one */
id|dep
op_assign
id|dep-&gt;next
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|dep
)paren
suffix:semicolon
id|pnp_err
c_func
(paren
l_string|&quot;Unable to assign resources to device %s.&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_activate_dev - activates a PnP device for use&n; * @dev: pointer to the desired device&n; *&n; * does not validate or set resources so be careful.&n; */
DECL|function|pnp_activate_dev
r_int
id|pnp_activate_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;active
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* the device is already active */
)brace
multiline_comment|/* ensure resources are allocated */
r_if
c_cond
(paren
op_logical_neg
id|pnp_auto_config_dev
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_can_write
c_func
(paren
id|dev
)paren
)paren
(brace
id|pnp_info
c_func
(paren
l_string|&quot;Device %s does not supported activation.&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;protocol
op_member_access_from_pointer
id|set
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;res
)paren
OL
l_int|0
)paren
(brace
id|pnp_err
c_func
(paren
l_string|&quot;Failed to activate device %s.&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|dev-&gt;active
op_assign
l_int|1
suffix:semicolon
id|pnp_info
c_func
(paren
l_string|&quot;Device %s activated.&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_disable_dev - disables device&n; * @dev: pointer to the desired device&n; *&n; * inform the correct pnp protocol so that resources can be used by other devices&n; */
DECL|function|pnp_disable_dev
r_int
id|pnp_disable_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;active
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* the device is already disabled */
)brace
r_if
c_cond
(paren
op_logical_neg
id|pnp_can_disable
c_func
(paren
id|dev
)paren
)paren
(brace
id|pnp_info
c_func
(paren
l_string|&quot;Device %s does not supported disabling.&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;protocol
op_member_access_from_pointer
id|disable
c_func
(paren
id|dev
)paren
OL
l_int|0
)paren
(brace
id|pnp_err
c_func
(paren
l_string|&quot;Failed to disable device %s.&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|dev-&gt;active
op_assign
l_int|0
suffix:semicolon
id|pnp_info
c_func
(paren
l_string|&quot;Device %s disabled.&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
multiline_comment|/* release the resources so that other devices can use them */
id|down
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
id|pnp_clean_resource_table
c_func
(paren
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * pnp_resource_change - change one resource&n; * @resource: pointer to resource to be changed&n; * @start: start of region&n; * @size: size of region&n; *&n; */
DECL|function|pnp_resource_change
r_void
id|pnp_resource_change
c_func
(paren
r_struct
id|resource
op_star
id|resource
comma
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|resource
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|resource-&gt;flags
op_and_assign
op_complement
(paren
id|IORESOURCE_AUTO
op_or
id|IORESOURCE_UNSET
)paren
suffix:semicolon
id|resource-&gt;start
op_assign
id|start
suffix:semicolon
id|resource-&gt;end
op_assign
id|start
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|pnp_assign_resources
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_assign_resources
)paren
suffix:semicolon
DECL|variable|pnp_manual_config_dev
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_manual_config_dev
)paren
suffix:semicolon
DECL|variable|pnp_auto_config_dev
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_auto_config_dev
)paren
suffix:semicolon
DECL|variable|pnp_activate_dev
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_activate_dev
)paren
suffix:semicolon
DECL|variable|pnp_disable_dev
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_disable_dev
)paren
suffix:semicolon
DECL|variable|pnp_resource_change
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_resource_change
)paren
suffix:semicolon
DECL|variable|pnp_init_resource_table
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_init_resource_table
)paren
suffix:semicolon
eof
