multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xbow.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/module.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xswitch.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
multiline_comment|/* #define LDEBUG&t;1  */
macro_line|#ifdef LDEBUG
DECL|macro|DPRINTF
mdefine_line|#define DPRINTF&t;&t;printk
DECL|macro|printf
mdefine_line|#define printf&t;&t;printk
macro_line|#else
DECL|macro|DPRINTF
mdefine_line|#define DPRINTF(x...)
macro_line|#endif
DECL|variable|modules
id|module_t
op_star
id|modules
(braket
id|MODULE_MAX
)braket
suffix:semicolon
DECL|variable|nummodules
r_int
id|nummodules
suffix:semicolon
DECL|macro|SN00_SERIAL_FUDGE
mdefine_line|#define SN00_SERIAL_FUDGE&t;0x3b1af409d513c2
DECL|macro|SN0_SERIAL_FUDGE
mdefine_line|#define SN0_SERIAL_FUDGE&t;0x6e
r_void
DECL|function|encode_int_serial
id|encode_int_serial
c_func
(paren
r_uint64
id|src
comma
r_uint64
op_star
id|dest
)paren
(brace
r_uint64
id|val
suffix:semicolon
r_int
id|i
suffix:semicolon
id|val
op_assign
id|src
op_plus
id|SN00_SERIAL_FUDGE
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
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
(paren
r_char
op_star
)paren
id|dest
)paren
(braket
id|i
)braket
op_assign
(paren
(paren
r_char
op_star
)paren
op_amp
id|val
)paren
(braket
r_sizeof
(paren
r_int
r_int
)paren
op_div
l_int|2
op_plus
(paren
(paren
id|i
op_mod
l_int|2
)paren
ques
c_cond
(paren
(paren
id|i
op_div
l_int|2
op_star
op_minus
l_int|1
)paren
op_minus
l_int|1
)paren
suffix:colon
(paren
id|i
op_div
l_int|2
)paren
)paren
)braket
suffix:semicolon
)brace
)brace
r_void
DECL|function|decode_int_serial
id|decode_int_serial
c_func
(paren
r_uint64
id|src
comma
r_uint64
op_star
id|dest
)paren
(brace
r_uint64
id|val
suffix:semicolon
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
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
(paren
r_char
op_star
)paren
op_amp
id|val
)paren
(braket
r_sizeof
(paren
r_int
r_int
)paren
op_div
l_int|2
op_plus
(paren
(paren
id|i
op_mod
l_int|2
)paren
ques
c_cond
(paren
(paren
id|i
op_div
l_int|2
op_star
op_minus
l_int|1
)paren
op_minus
l_int|1
)paren
suffix:colon
(paren
id|i
op_div
l_int|2
)paren
)paren
)braket
op_assign
(paren
(paren
r_char
op_star
)paren
op_amp
id|src
)paren
(braket
id|i
)braket
suffix:semicolon
)brace
op_star
id|dest
op_assign
id|val
op_minus
id|SN00_SERIAL_FUDGE
suffix:semicolon
)brace
r_void
DECL|function|encode_str_serial
id|encode_str_serial
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dest
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
id|MAX_SERIAL_NUM_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dest
(braket
id|i
)braket
op_assign
id|src
(braket
id|MAX_SERIAL_NUM_SIZE
op_div
l_int|2
op_plus
(paren
(paren
id|i
op_mod
l_int|2
)paren
ques
c_cond
(paren
(paren
id|i
op_div
l_int|2
op_star
op_minus
l_int|1
)paren
op_minus
l_int|1
)paren
suffix:colon
(paren
id|i
op_div
l_int|2
)paren
)paren
)braket
op_plus
id|SN0_SERIAL_FUDGE
suffix:semicolon
)brace
)brace
r_void
DECL|function|decode_str_serial
id|decode_str_serial
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dest
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
id|MAX_SERIAL_NUM_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dest
(braket
id|MAX_SERIAL_NUM_SIZE
op_div
l_int|2
op_plus
(paren
(paren
id|i
op_mod
l_int|2
)paren
ques
c_cond
(paren
(paren
id|i
op_div
l_int|2
op_star
op_minus
l_int|1
)paren
op_minus
l_int|1
)paren
suffix:colon
(paren
id|i
op_div
l_int|2
)paren
)paren
)braket
op_assign
id|src
(braket
id|i
)braket
op_minus
id|SN0_SERIAL_FUDGE
suffix:semicolon
)brace
)brace
DECL|function|module_lookup
id|module_t
op_star
id|module_lookup
c_func
(paren
id|moduleid_t
id|id
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
id|nummodules
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|modules
(braket
id|i
)braket
op_member_access_from_pointer
id|id
op_eq
id|id
)paren
(brace
id|DPRINTF
c_func
(paren
l_string|&quot;module_lookup: found m=0x%p&bslash;n&quot;
comma
id|modules
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|modules
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * module_add_node&n; *&n; *   The first time a new module number is seen, a module structure is&n; *   inserted into the module list in order sorted by module number&n; *   and the structure is initialized.&n; *&n; *   The node number is added to the list of nodes in the module.&n; */
r_static
id|module_t
op_star
id|__init
DECL|function|module_add_node
id|module_add_node
c_func
(paren
id|geoid_t
id|geoid
comma
id|cnodeid_t
id|cnodeid
)paren
(brace
id|module_t
op_star
id|m
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
id|buffer
(braket
l_int|16
)braket
suffix:semicolon
id|moduleid_t
id|moduleid
suffix:semicolon
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
l_int|16
)paren
suffix:semicolon
id|moduleid
op_assign
id|geo_module
c_func
(paren
id|geoid
)paren
suffix:semicolon
id|format_module_id
c_func
(paren
id|buffer
comma
id|moduleid
comma
id|MODULE_FORMAT_BRIEF
)paren
suffix:semicolon
id|DPRINTF
c_func
(paren
l_string|&quot;module_add_node: moduleid=%s node=%d&bslash;n&quot;
comma
id|buffer
comma
id|cnodeid
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|m
op_assign
id|module_lookup
c_func
(paren
id|moduleid
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|m
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|module_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|m
comma
l_int|0
comma
r_sizeof
(paren
id|module_t
)paren
)paren
suffix:semicolon
id|ASSERT_ALWAYS
c_func
(paren
id|m
)paren
suffix:semicolon
id|m-&gt;id
op_assign
id|moduleid
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|m-&gt;lock
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|m-&gt;thdcnt
)paren
suffix:semicolon
multiline_comment|/* Insert in sorted order by module number */
r_for
c_loop
(paren
id|i
op_assign
id|nummodules
suffix:semicolon
id|i
OG
l_int|0
op_logical_and
id|modules
(braket
id|i
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|id
OG
id|moduleid
suffix:semicolon
id|i
op_decrement
)paren
id|modules
(braket
id|i
)braket
op_assign
id|modules
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|modules
(braket
id|i
)braket
op_assign
id|m
suffix:semicolon
id|nummodules
op_increment
suffix:semicolon
)brace
id|m-&gt;nodes
(braket
id|m-&gt;nodecnt
)braket
op_assign
id|cnodeid
suffix:semicolon
id|m-&gt;geoid
(braket
id|m-&gt;nodecnt
)braket
op_assign
id|geoid
suffix:semicolon
id|m-&gt;nodecnt
op_increment
suffix:semicolon
id|DPRINTF
c_func
(paren
l_string|&quot;module_add_node: module %s now has %d nodes&bslash;n&quot;
comma
id|buffer
comma
id|m-&gt;nodecnt
)paren
suffix:semicolon
r_return
id|m
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|module_probe_snum
id|module_probe_snum
c_func
(paren
id|module_t
op_star
id|m
comma
id|nasid_t
id|nasid
)paren
(brace
id|lboard_t
op_star
id|board
suffix:semicolon
id|klmod_serial_num_t
op_star
id|comp
suffix:semicolon
r_char
id|serial_number
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/*&n;     * record brick serial number&n;     */
id|board
op_assign
id|find_lboard
c_func
(paren
(paren
id|lboard_t
op_star
)paren
id|KL_CONFIG_INFO
c_func
(paren
id|nasid
)paren
comma
id|KLTYPE_SNIA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|board
op_logical_or
id|KL_CONFIG_DUPLICATE_BOARD
c_func
(paren
id|board
)paren
)paren
(brace
macro_line|#if&t;LDEBUG
id|printf
(paren
l_string|&quot;module_probe_snum: no IP35 board found!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|board_serial_number_get
c_func
(paren
id|board
comma
id|serial_number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serial_number
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|encode_str_serial
c_func
(paren
id|serial_number
comma
id|m-&gt;snum.snum_str
)paren
suffix:semicolon
id|m-&gt;snum_valid
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#if&t;LDEBUG
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;module_probe_snum: brick serial number is null!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;module_probe_snum: brick serial number == %s&bslash;n&quot;
comma
id|serial_number
)paren
suffix:semicolon
macro_line|#endif /* DEBUG */
id|board
op_assign
id|find_lboard
c_func
(paren
(paren
id|lboard_t
op_star
)paren
id|KL_CONFIG_INFO
c_func
(paren
id|nasid
)paren
comma
id|KLTYPE_IOBRICK_XBOW
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|board
op_logical_or
id|KL_CONFIG_DUPLICATE_BOARD
c_func
(paren
id|board
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|comp
op_assign
id|GET_SNUM_COMP
c_func
(paren
id|board
)paren
suffix:semicolon
r_if
c_cond
(paren
id|comp
)paren
(brace
macro_line|#if LDEBUG
r_int
id|i
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;********found module with id %x and string&quot;
comma
id|m-&gt;id
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
id|MAX_SERIAL_NUM_SIZE
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot; %x &quot;
comma
id|comp-&gt;snum.snum_str
(braket
id|i
)braket
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Fudged string is not ASCII */
macro_line|#endif
r_if
c_cond
(paren
id|comp-&gt;snum.snum_str
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|memcpy
c_func
(paren
id|m-&gt;sys_snum
comma
id|comp-&gt;snum.snum_str
comma
id|MAX_SERIAL_NUM_SIZE
)paren
suffix:semicolon
id|m-&gt;sys_snum_valid
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|m-&gt;sys_snum_valid
)paren
r_return
l_int|1
suffix:semicolon
r_else
(brace
id|DPRINTF
c_func
(paren
l_string|&quot;Invalid serial number for module %d, &quot;
l_string|&quot;possible missing or invalid NIC.&quot;
comma
id|m-&gt;id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|io_module_init
id|io_module_init
c_func
(paren
r_void
)paren
(brace
id|cnodeid_t
id|node
suffix:semicolon
id|lboard_t
op_star
id|board
suffix:semicolon
id|nasid_t
id|nasid
suffix:semicolon
r_int
id|nserial
suffix:semicolon
id|module_t
op_star
id|m
suffix:semicolon
id|DPRINTF
c_func
(paren
l_string|&quot;*******module_init&bslash;n&quot;
)paren
suffix:semicolon
id|nserial
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
l_int|0
suffix:semicolon
id|node
OL
id|numnodes
suffix:semicolon
id|node
op_increment
)paren
(brace
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|node
)paren
suffix:semicolon
id|board
op_assign
id|find_lboard
c_func
(paren
(paren
id|lboard_t
op_star
)paren
id|KL_CONFIG_INFO
c_func
(paren
id|nasid
)paren
comma
id|KLTYPE_SNIA
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|board
)paren
suffix:semicolon
id|m
op_assign
id|module_add_node
c_func
(paren
id|board-&gt;brd_geoid
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m-&gt;snum_valid
op_logical_and
id|module_probe_snum
c_func
(paren
id|m
comma
id|nasid
)paren
)paren
id|nserial
op_increment
suffix:semicolon
)brace
id|DPRINTF
c_func
(paren
l_string|&quot;********found total of %d serial numbers in the system&bslash;n&quot;
comma
id|nserial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nserial
op_eq
l_int|0
)paren
id|DPRINTF
c_func
(paren
id|KERN_WARNING
l_string|&quot;io_module_init: No serial number found.&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
