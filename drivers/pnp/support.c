multiline_comment|/*&n; * support.c - provides standard pnp functions for the use of pnp protocol drivers,&n; *&n; * Copyright 2003 Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#ifdef CONFIG_PNP_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &quot;base.h&quot;
multiline_comment|/**&n; * pnp_is_active - Determines if a device is active based on its current resources&n; * @dev: pointer to the desired PnP device&n; *&n; */
DECL|function|pnp_is_active
r_int
id|pnp_is_active
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
id|pnp_port_start
c_func
(paren
id|dev
comma
l_int|0
)paren
op_logical_and
id|pnp_port_len
c_func
(paren
id|dev
comma
l_int|0
)paren
op_le
l_int|1
op_logical_and
op_logical_neg
id|pnp_mem_start
c_func
(paren
id|dev
comma
l_int|0
)paren
op_logical_and
id|pnp_mem_len
c_func
(paren
id|dev
comma
l_int|0
)paren
op_le
l_int|1
op_logical_and
id|pnp_irq
c_func
(paren
id|dev
comma
l_int|0
)paren
op_eq
op_minus
l_int|1
op_logical_and
id|pnp_dma
c_func
(paren
id|dev
comma
l_int|0
)paren
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|pnp_is_active
id|EXPORT_SYMBOL
c_func
(paren
id|pnp_is_active
)paren
suffix:semicolon
eof
