multiline_comment|/* $Id: ranges.c,v 1.15 2001/12/19 00:29:51 davem Exp $&n; * ranges.c: Handle ranges in newer proms for obio/sbus.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|variable|promlib_obio_ranges
r_struct
id|linux_prom_ranges
id|promlib_obio_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|variable|num_obio_ranges
r_int
id|num_obio_ranges
suffix:semicolon
multiline_comment|/* Adjust register values based upon the ranges parameters. */
r_static
r_void
DECL|function|prom_adjust_regs
id|prom_adjust_regs
c_func
(paren
r_struct
id|linux_prom_registers
op_star
id|regp
comma
r_int
id|nregs
comma
r_struct
id|linux_prom_ranges
op_star
id|rangep
comma
r_int
id|nranges
)paren
(brace
r_int
id|regc
comma
id|rngc
suffix:semicolon
r_for
c_loop
(paren
id|regc
op_assign
l_int|0
suffix:semicolon
id|regc
OL
id|nregs
suffix:semicolon
id|regc
op_increment
)paren
(brace
r_for
c_loop
(paren
id|rngc
op_assign
l_int|0
suffix:semicolon
id|rngc
OL
id|nranges
suffix:semicolon
id|rngc
op_increment
)paren
r_if
c_cond
(paren
id|regp
(braket
id|regc
)braket
dot
id|which_io
op_eq
id|rangep
(braket
id|rngc
)braket
dot
id|ot_child_space
)paren
r_break
suffix:semicolon
multiline_comment|/* Fount it */
r_if
c_cond
(paren
id|rngc
op_eq
id|nranges
)paren
multiline_comment|/* oops */
id|prom_printf
c_func
(paren
l_string|&quot;adjust_regs: Could not find range with matching bus type...&bslash;n&quot;
)paren
suffix:semicolon
id|regp
(braket
id|regc
)braket
dot
id|which_io
op_assign
id|rangep
(braket
id|rngc
)braket
dot
id|ot_parent_space
suffix:semicolon
id|regp
(braket
id|regc
)braket
dot
id|phys_addr
op_sub_assign
id|rangep
(braket
id|rngc
)braket
dot
id|ot_child_base
suffix:semicolon
id|regp
(braket
id|regc
)braket
dot
id|phys_addr
op_add_assign
id|rangep
(braket
id|rngc
)braket
dot
id|ot_parent_base
suffix:semicolon
)brace
)brace
r_void
DECL|function|prom_adjust_ranges
id|prom_adjust_ranges
c_func
(paren
r_struct
id|linux_prom_ranges
op_star
id|ranges1
comma
r_int
id|nranges1
comma
r_struct
id|linux_prom_ranges
op_star
id|ranges2
comma
r_int
id|nranges2
)paren
(brace
r_int
id|rng1c
comma
id|rng2c
suffix:semicolon
r_for
c_loop
(paren
id|rng1c
op_assign
l_int|0
suffix:semicolon
id|rng1c
OL
id|nranges1
suffix:semicolon
id|rng1c
op_increment
)paren
(brace
r_for
c_loop
(paren
id|rng2c
op_assign
l_int|0
suffix:semicolon
id|rng2c
OL
id|nranges2
suffix:semicolon
id|rng2c
op_increment
)paren
r_if
c_cond
(paren
id|ranges1
(braket
id|rng1c
)braket
dot
id|ot_parent_space
op_eq
id|ranges2
(braket
id|rng2c
)braket
dot
id|ot_child_space
op_logical_and
id|ranges1
(braket
id|rng1c
)braket
dot
id|ot_parent_base
op_ge
id|ranges2
(braket
id|rng2c
)braket
dot
id|ot_child_base
op_logical_and
id|ranges2
(braket
id|rng2c
)braket
dot
id|ot_child_base
op_plus
id|ranges2
(braket
id|rng2c
)braket
dot
id|or_size
op_minus
id|ranges1
(braket
id|rng1c
)braket
dot
id|ot_parent_base
OG
l_int|0U
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rng2c
op_eq
id|nranges2
)paren
(brace
multiline_comment|/* oops */
id|prom_printf
c_func
(paren
l_string|&quot;adjust_ranges: Could not find matching bus type...&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ranges1
(braket
id|rng1c
)braket
dot
id|ot_parent_base
op_plus
id|ranges1
(braket
id|rng1c
)braket
dot
id|or_size
OG
id|ranges2
(braket
id|rng2c
)braket
dot
id|ot_child_base
op_plus
id|ranges2
(braket
id|rng2c
)braket
dot
id|or_size
)paren
id|ranges1
(braket
id|rng1c
)braket
dot
id|or_size
op_assign
id|ranges2
(braket
id|rng2c
)braket
dot
id|ot_child_base
op_plus
id|ranges2
(braket
id|rng2c
)braket
dot
id|or_size
op_minus
id|ranges1
(braket
id|rng1c
)braket
dot
id|ot_parent_base
suffix:semicolon
id|ranges1
(braket
id|rng1c
)braket
dot
id|ot_parent_space
op_assign
id|ranges2
(braket
id|rng2c
)braket
dot
id|ot_parent_space
suffix:semicolon
id|ranges1
(braket
id|rng1c
)braket
dot
id|ot_parent_base
op_add_assign
id|ranges2
(braket
id|rng2c
)braket
dot
id|ot_parent_base
suffix:semicolon
)brace
)brace
multiline_comment|/* Apply probed obio ranges to registers passed, if no ranges return. */
r_void
DECL|function|prom_apply_obio_ranges
id|prom_apply_obio_ranges
c_func
(paren
r_struct
id|linux_prom_registers
op_star
id|regs
comma
r_int
id|nregs
)paren
(brace
r_if
c_cond
(paren
id|num_obio_ranges
)paren
(brace
id|prom_adjust_regs
c_func
(paren
id|regs
comma
id|nregs
comma
id|promlib_obio_ranges
comma
id|num_obio_ranges
)paren
suffix:semicolon
)brace
)brace
DECL|function|prom_ranges_init
r_void
id|__init
id|prom_ranges_init
c_func
(paren
r_void
)paren
(brace
r_int
id|node
comma
id|obio_node
suffix:semicolon
r_int
id|success
suffix:semicolon
id|num_obio_ranges
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Check for obio and sbus ranges. */
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|obio_node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;obio&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obio_node
)paren
(brace
id|success
op_assign
id|prom_getproperty
c_func
(paren
id|obio_node
comma
l_string|&quot;ranges&quot;
comma
(paren
r_char
op_star
)paren
id|promlib_obio_ranges
comma
r_sizeof
(paren
id|promlib_obio_ranges
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|success
op_ne
op_minus
l_int|1
)paren
(brace
id|num_obio_ranges
op_assign
(paren
id|success
op_div
r_sizeof
(paren
r_struct
id|linux_prom_ranges
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|num_obio_ranges
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;PROMLIB: obio_ranges %d&bslash;n&quot;
comma
id|num_obio_ranges
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_void
DECL|function|prom_apply_generic_ranges
id|prom_apply_generic_ranges
(paren
r_int
id|node
comma
r_int
id|parent
comma
r_struct
id|linux_prom_registers
op_star
id|regs
comma
r_int
id|nregs
)paren
(brace
r_int
id|success
suffix:semicolon
r_int
id|num_ranges
suffix:semicolon
r_struct
id|linux_prom_ranges
id|ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
id|success
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;ranges&quot;
comma
(paren
r_char
op_star
)paren
id|ranges
comma
r_sizeof
(paren
id|ranges
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|success
op_ne
op_minus
l_int|1
)paren
(brace
id|num_ranges
op_assign
(paren
id|success
op_div
r_sizeof
(paren
r_struct
id|linux_prom_ranges
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
(brace
r_struct
id|linux_prom_ranges
id|parent_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
r_int
id|num_parent_ranges
suffix:semicolon
id|success
op_assign
id|prom_getproperty
c_func
(paren
id|parent
comma
l_string|&quot;ranges&quot;
comma
(paren
r_char
op_star
)paren
id|parent_ranges
comma
r_sizeof
(paren
id|parent_ranges
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|success
op_ne
op_minus
l_int|1
)paren
(brace
id|num_parent_ranges
op_assign
(paren
id|success
op_div
r_sizeof
(paren
r_struct
id|linux_prom_ranges
)paren
)paren
suffix:semicolon
id|prom_adjust_ranges
(paren
id|ranges
comma
id|num_ranges
comma
id|parent_ranges
comma
id|num_parent_ranges
)paren
suffix:semicolon
)brace
)brace
id|prom_adjust_regs
c_func
(paren
id|regs
comma
id|nregs
comma
id|ranges
comma
id|num_ranges
)paren
suffix:semicolon
)brace
)brace
eof
