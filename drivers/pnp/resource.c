multiline_comment|/*&n; * resource.c - Contains functions for registering and analyzing resource information&n; *&n; * based on isapnp.c resource management (c) Jaroslav Kysela &lt;perex@suse.cz&gt;&n; * Copyright 2003 Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|variable|pnp_reserve_irq
r_static
r_int
id|pnp_reserve_irq
(braket
l_int|16
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
l_int|15
)braket
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* reserve (don&squot;t use) some IRQ */
DECL|variable|pnp_reserve_dma
r_static
r_int
id|pnp_reserve_dma
(braket
l_int|8
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
l_int|7
)braket
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* reserve (don&squot;t use) some DMA */
DECL|variable|pnp_reserve_io
r_static
r_int
id|pnp_reserve_io
(braket
l_int|16
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
l_int|15
)braket
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* reserve (don&squot;t use) some I/O region */
DECL|variable|pnp_reserve_mem
r_static
r_int
id|pnp_reserve_mem
(braket
l_int|16
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
l_int|15
)braket
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* reserve (don&squot;t use) some memory region */
multiline_comment|/*&n; * option registration&n; */
DECL|function|pnp_build_option
r_static
r_struct
id|pnp_option
op_star
id|pnp_build_option
c_func
(paren
r_int
id|priority
)paren
(brace
r_struct
id|pnp_option
op_star
id|option
op_assign
id|pnp_alloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pnp_option
)paren
)paren
suffix:semicolon
multiline_comment|/* check if pnp_alloc ran out of memory */
r_if
c_cond
(paren
op_logical_neg
id|option
)paren
r_return
l_int|NULL
suffix:semicolon
id|option-&gt;priority
op_assign
id|priority
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* make sure the priority is valid */
r_if
c_cond
(paren
id|option-&gt;priority
OG
id|PNP_RES_PRIORITY_FUNCTIONAL
)paren
id|option-&gt;priority
op_assign
id|PNP_RES_PRIORITY_INVALID
suffix:semicolon
r_return
id|option
suffix:semicolon
)brace
DECL|function|pnp_register_independent_option
r_struct
id|pnp_option
op_star
id|pnp_register_independent_option
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
id|option
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
id|option
op_assign
id|pnp_build_option
c_func
(paren
id|PNP_RES_PRIORITY_PREFERRED
)paren
suffix:semicolon
multiline_comment|/* this should never happen but if it does we&squot;ll try to continue */
r_if
c_cond
(paren
id|dev-&gt;independent
)paren
id|pnp_err
c_func
(paren
l_string|&quot;independent resource already registered&quot;
)paren
suffix:semicolon
id|dev-&gt;independent
op_assign
id|option
suffix:semicolon
r_return
id|option
suffix:semicolon
)brace
DECL|function|pnp_register_dependent_option
r_struct
id|pnp_option
op_star
id|pnp_register_dependent_option
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|priority
)paren
(brace
r_struct
id|pnp_option
op_star
id|option
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
id|option
op_assign
id|pnp_build_option
c_func
(paren
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;dependent
)paren
(brace
r_struct
id|pnp_option
op_star
id|parent
op_assign
id|dev-&gt;dependent
suffix:semicolon
r_while
c_loop
(paren
id|parent-&gt;next
)paren
id|parent
op_assign
id|parent-&gt;next
suffix:semicolon
id|parent-&gt;next
op_assign
id|option
suffix:semicolon
)brace
r_else
id|dev-&gt;dependent
op_assign
id|option
suffix:semicolon
r_return
id|option
suffix:semicolon
)brace
DECL|function|pnp_register_irq_resource
r_int
id|pnp_register_irq_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_irq
op_star
id|data
)paren
(brace
r_struct
id|pnp_irq
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|option
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ptr
op_assign
id|option-&gt;irq
suffix:semicolon
r_while
c_loop
(paren
id|ptr
op_logical_and
id|ptr-&gt;next
)paren
id|ptr
op_assign
id|ptr-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
id|ptr-&gt;next
op_assign
id|data
suffix:semicolon
r_else
id|option-&gt;irq
op_assign
id|data
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|data-&gt;map
)paren
)paren
id|pcibios_penalize_isa_irq
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnp_register_dma_resource
r_int
id|pnp_register_dma_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_dma
op_star
id|data
)paren
(brace
r_struct
id|pnp_dma
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|option
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ptr
op_assign
id|option-&gt;dma
suffix:semicolon
r_while
c_loop
(paren
id|ptr
op_logical_and
id|ptr-&gt;next
)paren
id|ptr
op_assign
id|ptr-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
id|ptr-&gt;next
op_assign
id|data
suffix:semicolon
r_else
id|option-&gt;dma
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnp_register_port_resource
r_int
id|pnp_register_port_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_port
op_star
id|data
)paren
(brace
r_struct
id|pnp_port
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|option
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ptr
op_assign
id|option-&gt;port
suffix:semicolon
r_while
c_loop
(paren
id|ptr
op_logical_and
id|ptr-&gt;next
)paren
id|ptr
op_assign
id|ptr-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
id|ptr-&gt;next
op_assign
id|data
suffix:semicolon
r_else
id|option-&gt;port
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnp_register_mem_resource
r_int
id|pnp_register_mem_resource
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
comma
r_struct
id|pnp_mem
op_star
id|data
)paren
(brace
r_struct
id|pnp_mem
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|option
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ptr
op_assign
id|option-&gt;mem
suffix:semicolon
r_while
c_loop
(paren
id|ptr
op_logical_and
id|ptr-&gt;next
)paren
id|ptr
op_assign
id|ptr-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
id|ptr-&gt;next
op_assign
id|data
suffix:semicolon
r_else
id|option-&gt;mem
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pnp_free_port
r_static
r_void
id|pnp_free_port
c_func
(paren
r_struct
id|pnp_port
op_star
id|port
)paren
(brace
r_struct
id|pnp_port
op_star
id|next
suffix:semicolon
r_while
c_loop
(paren
id|port
)paren
(brace
id|next
op_assign
id|port-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|port
)paren
suffix:semicolon
id|port
op_assign
id|next
suffix:semicolon
)brace
)brace
DECL|function|pnp_free_irq
r_static
r_void
id|pnp_free_irq
c_func
(paren
r_struct
id|pnp_irq
op_star
id|irq
)paren
(brace
r_struct
id|pnp_irq
op_star
id|next
suffix:semicolon
r_while
c_loop
(paren
id|irq
)paren
(brace
id|next
op_assign
id|irq-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|irq
)paren
suffix:semicolon
id|irq
op_assign
id|next
suffix:semicolon
)brace
)brace
DECL|function|pnp_free_dma
r_static
r_void
id|pnp_free_dma
c_func
(paren
r_struct
id|pnp_dma
op_star
id|dma
)paren
(brace
r_struct
id|pnp_dma
op_star
id|next
suffix:semicolon
r_while
c_loop
(paren
id|dma
)paren
(brace
id|next
op_assign
id|dma-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|dma
)paren
suffix:semicolon
id|dma
op_assign
id|next
suffix:semicolon
)brace
)brace
DECL|function|pnp_free_mem
r_static
r_void
id|pnp_free_mem
c_func
(paren
r_struct
id|pnp_mem
op_star
id|mem
)paren
(brace
r_struct
id|pnp_mem
op_star
id|next
suffix:semicolon
r_while
c_loop
(paren
id|mem
)paren
(brace
id|next
op_assign
id|mem-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|mem
)paren
suffix:semicolon
id|mem
op_assign
id|next
suffix:semicolon
)brace
)brace
DECL|function|pnp_free_option
r_void
id|pnp_free_option
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
)paren
(brace
r_struct
id|pnp_option
op_star
id|next
suffix:semicolon
r_while
c_loop
(paren
id|option
)paren
(brace
id|next
op_assign
id|option-&gt;next
suffix:semicolon
id|pnp_free_port
c_func
(paren
id|option-&gt;port
)paren
suffix:semicolon
id|pnp_free_irq
c_func
(paren
id|option-&gt;irq
)paren
suffix:semicolon
id|pnp_free_dma
c_func
(paren
id|option-&gt;dma
)paren
suffix:semicolon
id|pnp_free_mem
c_func
(paren
id|option-&gt;mem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|option
)paren
suffix:semicolon
id|option
op_assign
id|next
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * resource validity checking&n; */
DECL|macro|length
mdefine_line|#define length(start, end) (*(end) - *(start) + 1)
multiline_comment|/* Two ranges conflict if one doesn&squot;t end before the other starts */
DECL|macro|ranged_conflict
mdefine_line|#define ranged_conflict(starta, enda, startb, endb) &bslash;&n;&t;!((*(enda) &lt; *(startb)) || (*(endb) &lt; *(starta)))
DECL|macro|cannot_compare
mdefine_line|#define cannot_compare(flags) &bslash;&n;((flags) &amp; (IORESOURCE_UNSET | IORESOURCE_DISABLED))
DECL|function|pnp_check_port
r_int
id|pnp_check_port
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|idx
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|tdev
suffix:semicolon
r_int
r_int
op_star
id|port
comma
op_star
id|end
comma
op_star
id|tport
comma
op_star
id|tend
suffix:semicolon
id|port
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
multiline_comment|/* if the resource doesn&squot;t exist, don&squot;t complain about it */
r_if
c_cond
(paren
id|cannot_compare
c_func
(paren
id|dev-&gt;res.port_resource
(braket
id|idx
)braket
dot
id|flags
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* check if the resource is already in use, skip if the&n;&t; * device is active because it itself may be in use */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;active
)paren
(brace
r_if
c_cond
(paren
id|__check_region
c_func
(paren
op_amp
id|ioport_resource
comma
op_star
id|port
comma
id|length
c_func
(paren
id|port
comma
id|end
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* check if the resource is reserved */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
l_int|8
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_int
id|rport
op_assign
id|pnp_reserve_io
(braket
id|tmp
op_lshift
l_int|1
)braket
suffix:semicolon
r_int
id|rend
op_assign
id|pnp_reserve_io
(braket
(paren
id|tmp
op_lshift
l_int|1
)paren
op_plus
l_int|1
)braket
op_plus
id|rport
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ranged_conflict
c_func
(paren
id|port
comma
id|end
comma
op_amp
id|rport
comma
op_amp
id|rend
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* check for internal conflicts */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|PNP_MAX_PORT
op_logical_and
id|tmp
op_ne
id|idx
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;res.port_resource
(braket
id|tmp
)braket
dot
id|flags
op_amp
id|IORESOURCE_IO
)paren
(brace
id|tport
op_assign
op_amp
id|dev-&gt;res.port_resource
(braket
id|tmp
)braket
dot
id|start
suffix:semicolon
id|tend
op_assign
op_amp
id|dev-&gt;res.port_resource
(braket
id|tmp
)braket
dot
id|end
suffix:semicolon
r_if
c_cond
(paren
id|ranged_conflict
c_func
(paren
id|port
comma
id|end
comma
id|tport
comma
id|tend
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* check for conflicts with other pnp devices */
id|pnp_for_each_dev
c_func
(paren
id|tdev
)paren
(brace
r_if
c_cond
(paren
id|tdev
op_eq
id|dev
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|PNP_MAX_PORT
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|tdev-&gt;res.port_resource
(braket
id|tmp
)braket
dot
id|flags
op_amp
id|IORESOURCE_IO
)paren
(brace
r_if
c_cond
(paren
id|cannot_compare
c_func
(paren
id|tdev-&gt;res.port_resource
(braket
id|tmp
)braket
dot
id|flags
)paren
)paren
r_continue
suffix:semicolon
id|tport
op_assign
op_amp
id|tdev-&gt;res.port_resource
(braket
id|tmp
)braket
dot
id|start
suffix:semicolon
id|tend
op_assign
op_amp
id|tdev-&gt;res.port_resource
(braket
id|tmp
)braket
dot
id|end
suffix:semicolon
r_if
c_cond
(paren
id|ranged_conflict
c_func
(paren
id|port
comma
id|end
comma
id|tport
comma
id|tend
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pnp_check_mem
r_int
id|pnp_check_mem
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|idx
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|tdev
suffix:semicolon
r_int
r_int
op_star
id|addr
comma
op_star
id|end
comma
op_star
id|taddr
comma
op_star
id|tend
suffix:semicolon
id|addr
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
multiline_comment|/* if the resource doesn&squot;t exist, don&squot;t complain about it */
r_if
c_cond
(paren
id|cannot_compare
c_func
(paren
id|dev-&gt;res.mem_resource
(braket
id|idx
)braket
dot
id|flags
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* check if the resource is already in use, skip if the&n;&t; * device is active because it itself may be in use */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;active
)paren
(brace
r_if
c_cond
(paren
id|check_mem_region
c_func
(paren
op_star
id|addr
comma
id|length
c_func
(paren
id|addr
comma
id|end
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* check if the resource is reserved */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
l_int|8
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_int
id|raddr
op_assign
id|pnp_reserve_mem
(braket
id|tmp
op_lshift
l_int|1
)braket
suffix:semicolon
r_int
id|rend
op_assign
id|pnp_reserve_mem
(braket
(paren
id|tmp
op_lshift
l_int|1
)paren
op_plus
l_int|1
)braket
op_plus
id|raddr
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ranged_conflict
c_func
(paren
id|addr
comma
id|end
comma
op_amp
id|raddr
comma
op_amp
id|rend
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* check for internal conflicts */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|PNP_MAX_MEM
op_logical_and
id|tmp
op_ne
id|idx
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;res.mem_resource
(braket
id|tmp
)braket
dot
id|flags
op_amp
id|IORESOURCE_MEM
)paren
(brace
id|taddr
op_assign
op_amp
id|dev-&gt;res.mem_resource
(braket
id|tmp
)braket
dot
id|start
suffix:semicolon
id|tend
op_assign
op_amp
id|dev-&gt;res.mem_resource
(braket
id|tmp
)braket
dot
id|end
suffix:semicolon
r_if
c_cond
(paren
id|ranged_conflict
c_func
(paren
id|addr
comma
id|end
comma
id|taddr
comma
id|tend
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* check for conflicts with other pnp devices */
id|pnp_for_each_dev
c_func
(paren
id|tdev
)paren
(brace
r_if
c_cond
(paren
id|tdev
op_eq
id|dev
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|PNP_MAX_MEM
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|tdev-&gt;res.mem_resource
(braket
id|tmp
)braket
dot
id|flags
op_amp
id|IORESOURCE_MEM
)paren
(brace
r_if
c_cond
(paren
id|cannot_compare
c_func
(paren
id|tdev-&gt;res.mem_resource
(braket
id|tmp
)braket
dot
id|flags
)paren
)paren
r_continue
suffix:semicolon
id|taddr
op_assign
op_amp
id|tdev-&gt;res.mem_resource
(braket
id|tmp
)braket
dot
id|start
suffix:semicolon
id|tend
op_assign
op_amp
id|tdev-&gt;res.mem_resource
(braket
id|tmp
)braket
dot
id|end
suffix:semicolon
r_if
c_cond
(paren
id|ranged_conflict
c_func
(paren
id|addr
comma
id|end
comma
id|taddr
comma
id|tend
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pnp_test_handler
r_static
id|irqreturn_t
id|pnp_test_handler
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
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|pnp_check_irq
r_int
id|pnp_check_irq
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|idx
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|tdev
suffix:semicolon
r_int
r_int
op_star
id|irq
op_assign
op_amp
id|dev-&gt;res.irq_resource
(braket
id|idx
)braket
dot
id|start
suffix:semicolon
multiline_comment|/* if the resource doesn&squot;t exist, don&squot;t complain about it */
r_if
c_cond
(paren
id|cannot_compare
c_func
(paren
id|dev-&gt;res.irq_resource
(braket
id|idx
)braket
dot
id|flags
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* check if the resource is valid */
r_if
c_cond
(paren
op_star
id|irq
template_param
l_int|15
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* check if the resource is reserved */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
l_int|16
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pnp_reserve_irq
(braket
id|tmp
)braket
op_eq
op_star
id|irq
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* check for internal conflicts */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|PNP_MAX_IRQ
op_logical_and
id|tmp
op_ne
id|idx
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;res.irq_resource
(braket
id|tmp
)braket
dot
id|flags
op_amp
id|IORESOURCE_IRQ
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;res.irq_resource
(braket
id|tmp
)braket
dot
id|start
op_eq
op_star
id|irq
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* check if the resource is being used by a pci device */
(brace
r_struct
id|pci_dev
op_star
id|pci
op_assign
l_int|NULL
suffix:semicolon
id|for_each_pci_dev
c_func
(paren
id|pci
)paren
(brace
r_if
c_cond
(paren
id|pci-&gt;irq
op_eq
op_star
id|irq
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* check if the resource is already in use, skip if the&n;&t; * device is active because it itself may be in use */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;active
)paren
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
op_star
id|irq
comma
id|pnp_test_handler
comma
id|SA_INTERRUPT
comma
l_string|&quot;pnp&quot;
comma
l_int|NULL
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|free_irq
c_func
(paren
op_star
id|irq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* check for conflicts with other pnp devices */
id|pnp_for_each_dev
c_func
(paren
id|tdev
)paren
(brace
r_if
c_cond
(paren
id|tdev
op_eq
id|dev
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|PNP_MAX_IRQ
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|tdev-&gt;res.irq_resource
(braket
id|tmp
)braket
dot
id|flags
op_amp
id|IORESOURCE_IRQ
)paren
(brace
r_if
c_cond
(paren
id|cannot_compare
c_func
(paren
id|tdev-&gt;res.irq_resource
(braket
id|tmp
)braket
dot
id|flags
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tdev-&gt;res.irq_resource
(braket
id|tmp
)braket
dot
id|start
op_eq
op_star
id|irq
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pnp_check_dma
r_int
id|pnp_check_dma
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
id|idx
)paren
(brace
macro_line|#ifndef CONFIG_IA64
r_int
id|tmp
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|tdev
suffix:semicolon
r_int
r_int
op_star
id|dma
op_assign
op_amp
id|dev-&gt;res.dma_resource
(braket
id|idx
)braket
dot
id|start
suffix:semicolon
multiline_comment|/* if the resource doesn&squot;t exist, don&squot;t complain about it */
r_if
c_cond
(paren
id|cannot_compare
c_func
(paren
id|dev-&gt;res.dma_resource
(braket
id|idx
)braket
dot
id|flags
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* check if the resource is valid */
r_if
c_cond
(paren
op_star
id|dma
template_param
l_int|7
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* check if the resource is reserved */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
l_int|8
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pnp_reserve_dma
(braket
id|tmp
)braket
op_eq
op_star
id|dma
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* check for internal conflicts */
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|PNP_MAX_DMA
op_logical_and
id|tmp
op_ne
id|idx
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;res.dma_resource
(braket
id|tmp
)braket
dot
id|flags
op_amp
id|IORESOURCE_DMA
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;res.dma_resource
(braket
id|tmp
)braket
dot
id|start
op_eq
op_star
id|dma
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* check if the resource is already in use, skip if the&n;&t; * device is active because it itself may be in use */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;active
)paren
(brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
op_star
id|dma
comma
l_string|&quot;pnp&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|free_dma
c_func
(paren
op_star
id|dma
)paren
suffix:semicolon
)brace
multiline_comment|/* check for conflicts with other pnp devices */
id|pnp_for_each_dev
c_func
(paren
id|tdev
)paren
(brace
r_if
c_cond
(paren
id|tdev
op_eq
id|dev
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
l_int|0
suffix:semicolon
id|tmp
OL
id|PNP_MAX_DMA
suffix:semicolon
id|tmp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|tdev-&gt;res.dma_resource
(braket
id|tmp
)braket
dot
id|flags
op_amp
id|IORESOURCE_DMA
)paren
(brace
r_if
c_cond
(paren
id|cannot_compare
c_func
(paren
id|tdev-&gt;res.dma_resource
(braket
id|tmp
)braket
dot
id|flags
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tdev-&gt;res.dma_resource
(braket
id|tmp
)braket
dot
id|start
op_eq
op_star
id|dma
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|1
suffix:semicolon
macro_line|#else
multiline_comment|/* IA64 hasn&squot;t legacy DMA */
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|pnp_register_dependent_option
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_register_dependent_option
)paren
suffix:semicolon
DECL|variable|pnp_register_independent_option
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_register_independent_option
)paren
suffix:semicolon
DECL|variable|pnp_register_irq_resource
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_register_irq_resource
)paren
suffix:semicolon
DECL|variable|pnp_register_dma_resource
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_register_dma_resource
)paren
suffix:semicolon
DECL|variable|pnp_register_port_resource
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_register_port_resource
)paren
suffix:semicolon
DECL|variable|pnp_register_mem_resource
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_register_mem_resource
)paren
suffix:semicolon
multiline_comment|/* format is: pnp_reserve_irq=irq1[,irq2] .... */
DECL|function|pnp_setup_reserve_irq
r_static
r_int
id|__init
id|pnp_setup_reserve_irq
c_func
(paren
r_char
op_star
id|str
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|pnp_reserve_irq
(braket
id|i
)braket
)paren
op_ne
l_int|2
)paren
r_break
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pnp_reserve_irq=&quot;
comma
id|pnp_setup_reserve_irq
)paren
suffix:semicolon
multiline_comment|/* format is: pnp_reserve_dma=dma1[,dma2] .... */
DECL|function|pnp_setup_reserve_dma
r_static
r_int
id|__init
id|pnp_setup_reserve_dma
c_func
(paren
r_char
op_star
id|str
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|pnp_reserve_dma
(braket
id|i
)braket
)paren
op_ne
l_int|2
)paren
r_break
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pnp_reserve_dma=&quot;
comma
id|pnp_setup_reserve_dma
)paren
suffix:semicolon
multiline_comment|/* format is: pnp_reserve_io=io1,size1[,io2,size2] .... */
DECL|function|pnp_setup_reserve_io
r_static
r_int
id|__init
id|pnp_setup_reserve_io
c_func
(paren
r_char
op_star
id|str
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|pnp_reserve_io
(braket
id|i
)braket
)paren
op_ne
l_int|2
)paren
r_break
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pnp_reserve_io=&quot;
comma
id|pnp_setup_reserve_io
)paren
suffix:semicolon
multiline_comment|/* format is: pnp_reserve_mem=mem1,size1[,mem2,size2] .... */
DECL|function|pnp_setup_reserve_mem
r_static
r_int
id|__init
id|pnp_setup_reserve_mem
c_func
(paren
r_char
op_star
id|str
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|pnp_reserve_mem
(braket
id|i
)braket
)paren
op_ne
l_int|2
)paren
r_break
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pnp_reserve_mem=&quot;
comma
id|pnp_setup_reserve_mem
)paren
suffix:semicolon
eof
