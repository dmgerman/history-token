multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
multiline_comment|/*&n; * This is a temporary file that statically initializes the expected &n; * initial klgraph information that is normally provided by prom.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
DECL|variable|real_port
r_void
op_star
id|real_port
suffix:semicolon
DECL|variable|real_io_base
r_void
op_star
id|real_io_base
suffix:semicolon
DECL|variable|real_addr
r_void
op_star
id|real_addr
suffix:semicolon
DECL|variable|BW0
r_char
op_star
id|BW0
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|linux_klcfg
id|kl_config_hdr_t
op_star
id|linux_klcfg
suffix:semicolon
macro_line|#ifdef DEFINE_DUMP_RTNS
multiline_comment|/* forward declarations */
r_static
r_void
id|dump_ii
c_func
(paren
r_void
)paren
comma
id|dump_crossbow
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|clear_ii_error
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* DEFINE_DUMP_RTNS */
DECL|macro|SYNERGY_WIDGET
mdefine_line|#define SYNERGY_WIDGET          ((char *)0xc0000e0000000000)
DECL|macro|SYNERGY_SWIZZLE
mdefine_line|#define SYNERGY_SWIZZLE         ((char *)0xc0000e0000000400)
DECL|macro|HUBREG
mdefine_line|#define HUBREG                  ((char *)0xc0000a0001e00000)
DECL|macro|WIDGET0
mdefine_line|#define WIDGET0                 ((char *)0xc0000a0000000000)
DECL|macro|WIDGET4
mdefine_line|#define WIDGET4                 ((char *)0xc0000a0000000004)
DECL|macro|SYNERGY_WIDGET
mdefine_line|#define SYNERGY_WIDGET          ((char *)0xc0000e0000000000)
DECL|macro|SYNERGY_SWIZZLE
mdefine_line|#define SYNERGY_SWIZZLE         ((char *)0xc0000e0000000400)
DECL|macro|HUBREG
mdefine_line|#define HUBREG                  ((char *)0xc0000a0001e00000)
DECL|macro|WIDGET0
mdefine_line|#define WIDGET0                 ((char *)0xc0000a0000000000)
r_void
DECL|function|klgraph_hack_init
id|klgraph_hack_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * We need to know whether we are booting from PROM or &n;&t; * boot from disk.&n;&t; */
id|linux_klcfg
op_assign
(paren
id|kl_config_hdr_t
op_star
)paren
l_int|0xe000000000030000
suffix:semicolon
r_if
c_cond
(paren
id|linux_klcfg-&gt;ch_magic
op_eq
l_int|0xbeedbabe
)paren
(brace
r_return
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;klgraph_hack_init: Unable to locate KLCONFIG TABLE&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEFINE_DUMP_RTNS
multiline_comment|/* &n; * these were useful for printing out registers etc&n; * during bringup  &n; */
r_static
r_void
DECL|function|xdump
id|xdump
c_func
(paren
r_int
r_int
op_star
id|addr
comma
r_int
id|count
)paren
(brace
r_int
id|ii
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|xx
op_assign
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ii
op_assign
l_int|0
suffix:semicolon
id|ii
OL
id|count
suffix:semicolon
id|ii
op_increment
comma
id|xx
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;0x%p : 0x%p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|xx
comma
(paren
r_void
op_star
)paren
op_star
id|xx
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|xdump32
id|xdump32
c_func
(paren
r_int
r_int
op_star
id|addr
comma
r_int
id|count
)paren
(brace
r_int
id|ii
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|xx
op_assign
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ii
op_assign
l_int|0
suffix:semicolon
id|ii
OL
id|count
suffix:semicolon
id|ii
op_increment
comma
id|xx
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;0x%p : 0x%0x&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|xx
comma
(paren
r_int
)paren
op_star
id|xx
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|clear_ii_error
id|clear_ii_error
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
op_star
id|tmp
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;... WSTAT &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c00008
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;... WCTRL &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c00020
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;... WLCSR &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c00128
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;... IIDSR &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c00138
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;... IOPRBs &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c00198
comma
l_int|9
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;... IXSS &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c00210
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;... IBLS0 &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c10000
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;... IBLS1 &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c20000
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Write IOERR clear to clear the CRAZY bit in the status */
id|tmp
op_assign
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c001f8
suffix:semicolon
op_star
id|tmp
op_assign
(paren
r_int
r_int
)paren
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* dump out local block error registers */
id|printk
c_func
(paren
l_string|&quot;... &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001e04040
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* LB_ERROR_BITS */
id|printk
c_func
(paren
l_string|&quot;... &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001e04050
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* LB_ERROR_HDR1 */
id|printk
c_func
(paren
l_string|&quot;... &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001e04058
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* LB_ERROR_HDR2 */
multiline_comment|/* and clear the LB_ERROR_BITS */
id|tmp
op_assign
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001e04040
suffix:semicolon
op_star
id|tmp
op_assign
l_int|0x0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;clr: &quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001e04040
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* LB_ERROR_BITS */
id|tmp
op_assign
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001e04050
suffix:semicolon
op_star
id|tmp
op_assign
l_int|0x0
suffix:semicolon
id|tmp
op_assign
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001e04058
suffix:semicolon
op_star
id|tmp
op_assign
l_int|0x0
suffix:semicolon
)brace
r_static
r_void
DECL|function|dump_ii
id|dump_ii
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;===== Dump the II regs =====&bslash;n&quot;
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c00000
comma
l_int|2
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c00020
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c00100
comma
l_int|37
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c00300
comma
l_int|98
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c10000
comma
l_int|6
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c20000
comma
l_int|6
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001c30000
comma
l_int|2
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0000000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0001000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0002000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0003000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0004000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0005000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0006000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0007000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0008000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0009000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a000a000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a000b000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a000c000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a000d000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a000e000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a000f000000
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|dump_crossbow
id|dump_crossbow
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;===== Dump the Crossbow regs =====&bslash;n&quot;
)paren
suffix:semicolon
id|clear_ii_error
c_func
(paren
)paren
suffix:semicolon
id|xdump32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0000000004
comma
l_int|1
)paren
suffix:semicolon
id|clear_ii_error
c_func
(paren
)paren
suffix:semicolon
id|xdump32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0000000000
comma
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;and again..&bslash;n&quot;
)paren
suffix:semicolon
id|xdump32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0000000000
comma
l_int|1
)paren
suffix:semicolon
id|xdump32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0000000000
comma
l_int|1
)paren
suffix:semicolon
id|clear_ii_error
c_func
(paren
)paren
suffix:semicolon
id|xdump32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc000020000000004
comma
l_int|1
)paren
suffix:semicolon
id|clear_ii_error
c_func
(paren
)paren
suffix:semicolon
id|xdump32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc000020000000000
comma
l_int|1
)paren
suffix:semicolon
id|clear_ii_error
c_func
(paren
)paren
suffix:semicolon
id|xdump32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0000800004
comma
l_int|1
)paren
suffix:semicolon
id|clear_ii_error
c_func
(paren
)paren
suffix:semicolon
id|xdump32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc0000a0000800000
comma
l_int|1
)paren
suffix:semicolon
id|clear_ii_error
c_func
(paren
)paren
suffix:semicolon
id|xdump32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc000020000800004
comma
l_int|1
)paren
suffix:semicolon
id|clear_ii_error
c_func
(paren
)paren
suffix:semicolon
id|xdump32
c_func
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0xc000020000800000
comma
l_int|1
)paren
suffix:semicolon
id|clear_ii_error
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* DEFINE_DUMP_RTNS */
eof
