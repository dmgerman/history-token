multiline_comment|/*&n;&t;backpack.c (c) 2001 Micro Solutions Inc.&n;&t;&t;Released under the terms of the GNU General Public license&n;&n;&t;backpack.c is a low-level protocol driver for the Micro Solutions&n;&t;&t;&quot;BACKPACK&quot; parallel port IDE adapter&n;&t;&t;(Works on Series 6 drives)&n;&n;&t;Written by: Ken Hahn     (linux-dev@micro-solutions.com)&n;&t;            Clive Turvey (linux-dev@micro-solutions.com)&n;&n;*/
multiline_comment|/*&n;   This is Ken&squot;s linux wrapper for the PPC library&n;   Version 1.0.0 is the backpack driver for which source is not available&n;   Version 2.0.0 is the first to have source released &n;   Version 2.0.1 is the &quot;Cox-ified&quot; source code &n;   Version 2.0.2 - fixed version string usage, and made ppc functions static &n;*/
multiline_comment|/* PARAMETERS */
DECL|variable|verbose
r_static
r_int
id|verbose
suffix:semicolon
multiline_comment|/* set this to 1 to see debugging messages and whatnot */
DECL|macro|BACKPACK_VERSION
mdefine_line|#define BACKPACK_VERSION &quot;2.0.2&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if defined(CONFIG_PARPORT_MODULE)||defined(CONFIG_PARPORT)
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#endif
macro_line|#include &quot;ppc6lnx.c&quot;
macro_line|#include &quot;paride.h&quot;
DECL|macro|PPCSTRUCT
mdefine_line|#define PPCSTRUCT(pi) ((PPC *)(pi-&gt;private))
multiline_comment|/****************************************************************/
multiline_comment|/*&n; ATAPI CDROM DRIVE REGISTERS&n;*/
DECL|macro|ATAPI_DATA
mdefine_line|#define ATAPI_DATA       0      /* data port                  */
DECL|macro|ATAPI_ERROR
mdefine_line|#define ATAPI_ERROR      1      /* error register (read)      */
DECL|macro|ATAPI_FEATURES
mdefine_line|#define ATAPI_FEATURES   1      /* feature register (write)   */
DECL|macro|ATAPI_INT_REASON
mdefine_line|#define ATAPI_INT_REASON 2      /* interrupt reason register  */
DECL|macro|ATAPI_COUNT_LOW
mdefine_line|#define ATAPI_COUNT_LOW  4      /* byte count register (low)  */
DECL|macro|ATAPI_COUNT_HIGH
mdefine_line|#define ATAPI_COUNT_HIGH 5      /* byte count register (high) */
DECL|macro|ATAPI_DRIVE_SEL
mdefine_line|#define ATAPI_DRIVE_SEL  6      /* drive select register      */
DECL|macro|ATAPI_STATUS
mdefine_line|#define ATAPI_STATUS     7      /* status port (read)         */
DECL|macro|ATAPI_COMMAND
mdefine_line|#define ATAPI_COMMAND    7      /* command port (write)       */
DECL|macro|ATAPI_ALT_STATUS
mdefine_line|#define ATAPI_ALT_STATUS 0x0e /* alternate status reg (read) */
DECL|macro|ATAPI_DEVICE_CONTROL
mdefine_line|#define ATAPI_DEVICE_CONTROL 0x0e /* device control (write)   */
multiline_comment|/****************************************************************/
DECL|function|bpck6_read_regr
r_static
r_int
id|bpck6_read_regr
c_func
(paren
id|PIA
op_star
id|pi
comma
r_int
id|cont
comma
r_int
id|reg
)paren
(brace
r_int
r_int
id|out
suffix:semicolon
multiline_comment|/* check for bad settings */
r_if
c_cond
(paren
id|reg
l_int|7
op_logical_or
id|cont
l_int|2
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|out
op_assign
id|ppc6_rd_port
c_func
(paren
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
comma
id|cont
ques
c_cond
id|reg
op_or
l_int|8
suffix:colon
id|reg
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|bpck6_write_regr
r_static
r_void
id|bpck6_write_regr
c_func
(paren
id|PIA
op_star
id|pi
comma
r_int
id|cont
comma
r_int
id|reg
comma
r_int
id|val
)paren
(brace
multiline_comment|/* check for bad settings */
r_if
c_cond
(paren
id|reg
op_ge
l_int|0
op_logical_and
id|reg
op_le
l_int|7
op_logical_and
id|cont
op_ge
l_int|0
op_logical_and
id|cont
op_le
l_int|1
)paren
(brace
id|ppc6_wr_port
c_func
(paren
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
comma
id|cont
ques
c_cond
id|reg
op_or
l_int|8
suffix:colon
id|reg
comma
(paren
id|u8
)paren
id|val
)paren
suffix:semicolon
)brace
)brace
DECL|function|bpck6_write_block
r_static
r_void
id|bpck6_write_block
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|ppc6_wr_port16_blk
c_func
(paren
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
comma
id|ATAPI_DATA
comma
id|buf
comma
(paren
id|u32
)paren
id|len
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|bpck6_read_block
r_static
r_void
id|bpck6_read_block
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|ppc6_rd_port16_blk
c_func
(paren
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
comma
id|ATAPI_DATA
comma
id|buf
comma
(paren
id|u32
)paren
id|len
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|bpck6_connect
r_static
r_void
id|bpck6_connect
(paren
id|PIA
op_star
id|pi
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;connect&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pi-&gt;mode
op_ge
l_int|2
)paren
(brace
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
op_member_access_from_pointer
id|mode
op_assign
l_int|4
op_plus
id|pi-&gt;mode
op_minus
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pi-&gt;mode
op_eq
l_int|1
)paren
(brace
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
op_member_access_from_pointer
id|mode
op_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
op_member_access_from_pointer
id|mode
op_assign
l_int|1
suffix:semicolon
)brace
id|ppc6_open
c_func
(paren
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
)paren
suffix:semicolon
id|ppc6_wr_extout
c_func
(paren
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
comma
l_int|0x3
)paren
suffix:semicolon
)brace
DECL|function|bpck6_disconnect
r_static
r_void
id|bpck6_disconnect
(paren
id|PIA
op_star
id|pi
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;disconnect&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|ppc6_wr_extout
c_func
(paren
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
comma
l_int|0x0
)paren
suffix:semicolon
id|ppc6_close
c_func
(paren
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
)paren
suffix:semicolon
)brace
DECL|function|bpck6_test_port
r_static
r_int
id|bpck6_test_port
(paren
id|PIA
op_star
id|pi
)paren
multiline_comment|/* check for 8-bit port */
(brace
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PARPORT indicates modes=%x for lp=0x%lx&bslash;n&quot;
comma
(paren
(paren
r_struct
id|pardevice
op_star
)paren
(paren
id|pi-&gt;pardev
)paren
)paren
op_member_access_from_pointer
id|port-&gt;modes
comma
(paren
(paren
r_struct
id|pardevice
op_star
)paren
(paren
id|pi-&gt;pardev
)paren
)paren
op_member_access_from_pointer
id|port-&gt;base
)paren
suffix:semicolon
)brace
multiline_comment|/*copy over duplicate stuff.. initialize state info*/
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
op_member_access_from_pointer
id|ppc_id
op_assign
id|pi-&gt;unit
suffix:semicolon
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
op_member_access_from_pointer
id|lpt_addr
op_assign
id|pi-&gt;port
suffix:semicolon
macro_line|#ifdef CONFIG_PARPORT_PC_MODULE
DECL|macro|CONFIG_PARPORT_PC
mdefine_line|#define CONFIG_PARPORT_PC
macro_line|#endif
macro_line|#ifdef CONFIG_PARPORT_PC
multiline_comment|/* look at the parport device to see if what modes we can use */
r_if
c_cond
(paren
(paren
(paren
r_struct
id|pardevice
op_star
)paren
(paren
id|pi-&gt;pardev
)paren
)paren
op_member_access_from_pointer
id|port-&gt;modes
op_amp
(paren
id|PARPORT_MODE_EPP
)paren
)paren
(brace
r_return
l_int|5
suffix:semicolon
multiline_comment|/* Can do EPP*/
)brace
r_else
r_if
c_cond
(paren
(paren
(paren
r_struct
id|pardevice
op_star
)paren
(paren
id|pi-&gt;pardev
)paren
)paren
op_member_access_from_pointer
id|port-&gt;modes
op_amp
(paren
id|PARPORT_MODE_TRISTATE
)paren
)paren
(brace
r_return
l_int|2
suffix:semicolon
)brace
r_else
multiline_comment|/*Just flat SPP*/
(brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* there is no way of knowing what kind of port we have&n;&t;   default to the highest mode possible */
r_return
l_int|5
suffix:semicolon
macro_line|#endif
)brace
DECL|function|bpck6_probe_unit
r_static
r_int
id|bpck6_probe_unit
(paren
id|PIA
op_star
id|pi
)paren
(brace
r_int
id|out
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PROBE UNIT %x on port:%x&bslash;n&quot;
comma
id|pi-&gt;unit
comma
id|pi-&gt;port
)paren
suffix:semicolon
)brace
multiline_comment|/*SET PPC UNIT NUMBER*/
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
op_member_access_from_pointer
id|ppc_id
op_assign
id|pi-&gt;unit
suffix:semicolon
multiline_comment|/*LOWER DOWN TO UNIDIRECTIONAL*/
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
op_member_access_from_pointer
id|mode
op_assign
l_int|1
suffix:semicolon
id|out
op_assign
id|ppc6_open
c_func
(paren
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ppc_open returned %2x&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|out
)paren
(brace
id|ppc6_close
c_func
(paren
id|PPCSTRUCT
c_func
(paren
id|pi
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;leaving probe&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Failed open&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|bpck6_log_adapter
r_static
r_void
id|bpck6_log_adapter
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|scratch
comma
r_int
id|verbose
)paren
(brace
r_char
op_star
id|mode_string
(braket
l_int|5
)braket
op_assign
(brace
l_string|&quot;4-bit&quot;
comma
l_string|&quot;8-bit&quot;
comma
l_string|&quot;EPP-8&quot;
comma
l_string|&quot;EPP-16&quot;
comma
l_string|&quot;EPP-32&quot;
)brace
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: BACKPACK Protocol Driver V&quot;
id|BACKPACK_VERSION
l_string|&quot;&bslash;n&quot;
comma
id|pi-&gt;device
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Copyright 2001 by Micro Solutions, Inc., DeKalb IL.&bslash;n&quot;
comma
id|pi-&gt;device
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: BACKPACK %s, Micro Solutions BACKPACK Drive at 0x%x&bslash;n&quot;
comma
id|pi-&gt;device
comma
id|BACKPACK_VERSION
comma
id|pi-&gt;port
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Unit: %d Mode:%d (%s) Delay %d&bslash;n&quot;
comma
id|pi-&gt;device
comma
id|pi-&gt;unit
comma
id|pi-&gt;mode
comma
id|mode_string
(braket
id|pi-&gt;mode
)braket
comma
id|pi-&gt;delay
)paren
suffix:semicolon
)brace
DECL|function|bpck6_init_proto
r_static
r_int
id|bpck6_init_proto
c_func
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|PPC
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|PPC
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
id|PPC
)paren
)paren
suffix:semicolon
id|pi
op_member_access_from_pointer
r_private
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: ERROR COULDN&squot;T ALLOCATE MEMORY&bslash;n&quot;
comma
id|pi-&gt;device
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|bpck6_release_proto
r_static
r_void
id|bpck6_release_proto
c_func
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|kfree
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|pi
op_member_access_from_pointer
r_private
)paren
)paren
suffix:semicolon
)brace
DECL|variable|bpck6
r_static
r_struct
id|pi_protocol
id|bpck6
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;bpck6&quot;
comma
dot
id|max_mode
op_assign
l_int|5
comma
dot
id|epp_first
op_assign
l_int|2
comma
multiline_comment|/* 2-5 use epp (need 8 ports) */
dot
id|max_units
op_assign
l_int|255
comma
dot
id|write_regr
op_assign
id|bpck6_write_regr
comma
dot
id|read_regr
op_assign
id|bpck6_read_regr
comma
dot
id|write_block
op_assign
id|bpck6_write_block
comma
dot
id|read_block
op_assign
id|bpck6_read_block
comma
dot
id|connect
op_assign
id|bpck6_connect
comma
dot
id|disconnect
op_assign
id|bpck6_disconnect
comma
dot
id|test_port
op_assign
id|bpck6_test_port
comma
dot
id|probe_unit
op_assign
id|bpck6_probe_unit
comma
dot
id|log_adapter
op_assign
id|bpck6_log_adapter
comma
dot
id|init_proto
op_assign
id|bpck6_init_proto
comma
dot
id|release_proto
op_assign
id|bpck6_release_proto
comma
)brace
suffix:semicolon
DECL|function|bpck6_init
r_static
r_int
id|__init
id|bpck6_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;bpck6: BACKPACK Protocol Driver V&quot;
id|BACKPACK_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;bpck6: Copyright 2001 by Micro Solutions, Inc., DeKalb IL. USA&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;bpck6: verbose debug enabled.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|pi_register
c_func
(paren
op_amp
id|bpck6
)paren
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|bpck6_exit
r_static
r_void
id|__exit
id|bpck6_exit
c_func
(paren
r_void
)paren
(brace
id|pi_unregister
c_func
(paren
op_amp
id|bpck6
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Micro Solutions Inc.&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;BACKPACK Protocol module, compatible with PARIDE&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|verbose
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|bpck6_init
)paren
id|module_exit
c_func
(paren
id|bpck6_exit
)paren
eof
