multiline_comment|/*&n; * names.c - a very simple name database for PnP devices&n; *&n; * Some code is based on names.c from linux pci&n; * Copyright 1993--1999 Drew Eckhardt, Frederic Potter,&n; * David Mosberger-Tang, Martin Mares&n; *&n; * Copyright 2002 Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &quot;base.h&quot;
macro_line|#ifdef CONFIG_PNP_NAMES
DECL|variable|pnp_id_eisaid
r_static
r_char
op_star
id|pnp_id_eisaid
(braket
)braket
op_assign
(brace
DECL|macro|ID
mdefine_line|#define ID(x,y) x,
macro_line|#include &quot;idlist.h&quot;
)brace
suffix:semicolon
DECL|variable|pnp_id_names
r_static
r_char
op_star
id|pnp_id_names
(braket
)braket
op_assign
(brace
DECL|macro|ID
mdefine_line|#define ID(x,y) y,
macro_line|#include &quot;idlist.h&quot;
)brace
suffix:semicolon
r_void
DECL|function|pnp_name_device
id|pnp_name_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|name
op_assign
id|dev-&gt;name
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
r_sizeof
(paren
id|pnp_id_eisaid
)paren
op_div
r_sizeof
(paren
id|pnp_id_eisaid
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|compare_pnp_id
c_func
(paren
id|dev-&gt;id
comma
id|pnp_id_eisaid
(braket
id|i
)braket
)paren
)paren
(brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%s&quot;
comma
id|pnp_id_names
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
macro_line|#else
r_void
DECL|function|pnp_name_device
id|pnp_name_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PNP_NAMES */
eof
