multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/module.h&gt;
macro_line|#include &lt;asm/sn/router.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xbow.h&gt;
DECL|macro|DEBUG_KLGRAPH
macro_line|#undef DEBUG_KLGRAPH
macro_line|#ifdef DEBUG_KLGRAPH
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif /* DEBUG_KLGRAPH */
DECL|variable|root_lboard
id|lboard_t
op_star
id|root_lboard
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|variable|klgraph_addr
id|u64
id|klgraph_addr
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|variable|hasmetarouter
r_static
r_int
id|hasmetarouter
suffix:semicolon
DECL|variable|brick_types
r_char
id|brick_types
(braket
id|MAX_BRICK_TYPES
op_plus
l_int|1
)braket
op_assign
l_string|&quot;crikxdpn%#=vo^34567890123456789...&quot;
suffix:semicolon
id|lboard_t
op_star
DECL|function|find_lboard
id|find_lboard
c_func
(paren
id|lboard_t
op_star
id|start
comma
r_int
r_char
id|brd_type
)paren
(brace
multiline_comment|/* Search all boards stored on this node. */
r_while
c_loop
(paren
id|start
)paren
(brace
r_if
c_cond
(paren
id|start-&gt;brd_type
op_eq
id|brd_type
)paren
r_return
id|start
suffix:semicolon
id|start
op_assign
id|KLCF_NEXT
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/* Didn&squot;t find it. */
r_return
(paren
id|lboard_t
op_star
)paren
l_int|NULL
suffix:semicolon
)brace
id|lboard_t
op_star
DECL|function|find_lboard_class
id|find_lboard_class
c_func
(paren
id|lboard_t
op_star
id|start
comma
r_int
r_char
id|brd_type
)paren
(brace
multiline_comment|/* Search all boards stored on this node. */
r_while
c_loop
(paren
id|start
)paren
(brace
r_if
c_cond
(paren
id|KLCLASS
c_func
(paren
id|start-&gt;brd_type
)paren
op_eq
id|KLCLASS
c_func
(paren
id|brd_type
)paren
)paren
r_return
id|start
suffix:semicolon
id|start
op_assign
id|KLCF_NEXT
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/* Didn&squot;t find it. */
r_return
(paren
id|lboard_t
op_star
)paren
l_int|NULL
suffix:semicolon
)brace
id|klinfo_t
op_star
DECL|function|find_component
id|find_component
c_func
(paren
id|lboard_t
op_star
id|brd
comma
id|klinfo_t
op_star
id|kli
comma
r_int
r_char
id|struct_type
)paren
(brace
r_int
id|index
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|kli
op_eq
(paren
id|klinfo_t
op_star
)paren
l_int|NULL
)paren
(brace
id|index
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|KLCF_NUM_COMPS
c_func
(paren
id|brd
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|kli
op_eq
id|KLCF_COMP
c_func
(paren
id|brd
comma
id|j
)paren
)paren
r_break
suffix:semicolon
)brace
id|index
op_assign
id|j
suffix:semicolon
r_if
c_cond
(paren
id|index
op_eq
id|KLCF_NUM_COMPS
c_func
(paren
id|brd
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;find_component: Bad pointer: 0x%p&bslash;n&quot;
comma
id|kli
)paren
suffix:semicolon
r_return
(paren
id|klinfo_t
op_star
)paren
l_int|NULL
suffix:semicolon
)brace
id|index
op_increment
suffix:semicolon
multiline_comment|/* next component */
)brace
r_for
c_loop
(paren
suffix:semicolon
id|index
OL
id|KLCF_NUM_COMPS
c_func
(paren
id|brd
)paren
suffix:semicolon
id|index
op_increment
)paren
(brace
id|kli
op_assign
id|KLCF_COMP
c_func
(paren
id|brd
comma
id|index
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;find_component: brd %p kli %p  request type = 0x%x kli type 0x%x&bslash;n&quot;
comma
id|brd
comma
id|kli
comma
id|kli-&gt;struct_type
comma
id|KLCF_COMP_TYPE
c_func
(paren
id|kli
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|KLCF_COMP_TYPE
c_func
(paren
id|kli
)paren
op_eq
id|struct_type
)paren
r_return
id|kli
suffix:semicolon
)brace
multiline_comment|/* Didn&squot;t find it. */
r_return
(paren
id|klinfo_t
op_star
)paren
l_int|NULL
suffix:semicolon
)brace
id|klinfo_t
op_star
DECL|function|find_first_component
id|find_first_component
c_func
(paren
id|lboard_t
op_star
id|brd
comma
r_int
r_char
id|struct_type
)paren
(brace
r_return
id|find_component
c_func
(paren
id|brd
comma
(paren
id|klinfo_t
op_star
)paren
l_int|NULL
comma
id|struct_type
)paren
suffix:semicolon
)brace
id|lboard_t
op_star
DECL|function|find_lboard_modslot
id|find_lboard_modslot
c_func
(paren
id|lboard_t
op_star
id|start
comma
id|geoid_t
id|geoid
)paren
(brace
multiline_comment|/* Search all boards stored on this node. */
r_while
c_loop
(paren
id|start
)paren
(brace
r_if
c_cond
(paren
id|geo_cmp
c_func
(paren
id|start-&gt;brd_geoid
comma
id|geoid
)paren
)paren
r_return
id|start
suffix:semicolon
id|start
op_assign
id|KLCF_NEXT
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/* Didn&squot;t find it. */
r_return
(paren
id|lboard_t
op_star
)paren
l_int|NULL
suffix:semicolon
)brace
id|lboard_t
op_star
DECL|function|find_lboard_module
id|find_lboard_module
c_func
(paren
id|lboard_t
op_star
id|start
comma
id|geoid_t
id|geoid
)paren
(brace
multiline_comment|/* Search all boards stored on this node. */
r_while
c_loop
(paren
id|start
)paren
(brace
r_if
c_cond
(paren
id|geo_cmp
c_func
(paren
id|start-&gt;brd_geoid
comma
id|geoid
)paren
)paren
r_return
id|start
suffix:semicolon
id|start
op_assign
id|KLCF_NEXT
c_func
(paren
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/* Didn&squot;t find it. */
r_return
(paren
id|lboard_t
op_star
)paren
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert a NIC name to a name for use in the hardware graph.&n; */
r_void
DECL|function|nic_name_convert
id|nic_name_convert
c_func
(paren
r_char
op_star
id|old_name
comma
r_char
op_star
id|new_name
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
id|c
suffix:semicolon
r_char
op_star
id|compare_ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|old_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
op_logical_or
(paren
id|old_name
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|new_name
comma
id|EDGE_LBL_XWIDGET
)paren
suffix:semicolon
)brace
r_else
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
id|strlen
c_func
(paren
id|old_name
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|c
op_assign
id|old_name
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|isalpha
c_func
(paren
id|c
)paren
)paren
id|new_name
(braket
id|i
)braket
op_assign
id|tolower
c_func
(paren
id|c
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|c
)paren
)paren
id|new_name
(braket
id|i
)braket
op_assign
id|c
suffix:semicolon
r_else
id|new_name
(braket
id|i
)braket
op_assign
l_char|&squot;_&squot;
suffix:semicolon
)brace
id|new_name
(braket
id|i
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
multiline_comment|/* XXX -&n;         * Since a bunch of boards made it out with weird names like&n;         * IO6-fibbbed and IO6P2, we need to look for IO6 in a name and&n;         * replace it with &quot;baseio&quot; to avoid confusion in the field.&n;&t; * We also have to make sure we don&squot;t report media_io instead of&n;&t; * baseio.&n;         */
multiline_comment|/* Skip underscores at the beginning of the name */
r_for
c_loop
(paren
id|compare_ptr
op_assign
id|new_name
suffix:semicolon
(paren
op_star
id|compare_ptr
)paren
op_eq
l_char|&squot;_&squot;
suffix:semicolon
id|compare_ptr
op_increment
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check for some names we need to replace.  Early boards&n;&t; * had junk following the name so check only the first&n;&t; * characters.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|new_name
comma
l_string|&quot;io6&quot;
comma
l_int|3
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|new_name
comma
l_string|&quot;mio&quot;
comma
l_int|3
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|new_name
comma
l_string|&quot;media_io&quot;
comma
l_int|8
)paren
)paren
id|strcpy
c_func
(paren
id|new_name
comma
l_string|&quot;baseio&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|new_name
comma
l_string|&quot;divo&quot;
comma
l_int|4
)paren
)paren
id|strcpy
c_func
(paren
id|new_name
comma
l_string|&quot;divo&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * get_actual_nasid&n; *&n; *&t;Completely disabled brds have their klconfig on &n; *&t;some other nasid as they have no memory. But their&n; *&t;actual nasid is hidden in the klconfig. Use this&n; *&t;routine to get it. Works for normal boards too.&n; */
id|nasid_t
DECL|function|get_actual_nasid
id|get_actual_nasid
c_func
(paren
id|lboard_t
op_star
id|brd
)paren
(brace
id|klhub_t
op_star
id|hub
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|brd
)paren
r_return
id|INVALID_NASID
suffix:semicolon
multiline_comment|/* find out if we are a completely disabled brd. */
id|hub
op_assign
(paren
id|klhub_t
op_star
)paren
id|find_first_component
c_func
(paren
id|brd
comma
id|KLSTRUCT_HUB
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hub
)paren
r_return
id|INVALID_NASID
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hub-&gt;hub_info.flags
op_amp
id|KLINFO_ENABLE
)paren
)paren
multiline_comment|/* disabled node brd */
r_return
id|hub-&gt;hub_info.physid
suffix:semicolon
r_else
r_return
id|brd-&gt;brd_nasid
suffix:semicolon
)brace
r_int
DECL|function|xbow_port_io_enabled
id|xbow_port_io_enabled
c_func
(paren
id|nasid_t
id|nasid
comma
r_int
id|link
)paren
(brace
id|lboard_t
op_star
id|brd
suffix:semicolon
id|klxbow_t
op_star
id|xbow_p
suffix:semicolon
multiline_comment|/*&n;&t; * look for boards that might contain an xbow or xbridge&n;&t; */
id|brd
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
id|brd
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|xbow_p
op_assign
(paren
id|klxbow_t
op_star
)paren
id|find_component
c_func
(paren
id|brd
comma
l_int|NULL
comma
id|KLSTRUCT_XBOW
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|XBOW_PORT_TYPE_IO
c_func
(paren
id|xbow_p
comma
id|link
)paren
op_logical_or
op_logical_neg
id|XBOW_PORT_IS_ENABLED
c_func
(paren
id|xbow_p
comma
id|link
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_void
DECL|function|board_to_path
id|board_to_path
c_func
(paren
id|lboard_t
op_star
id|brd
comma
r_char
op_star
id|path
)paren
(brace
id|moduleid_t
id|modnum
suffix:semicolon
r_char
op_star
id|board_name
suffix:semicolon
r_char
id|buffer
(braket
l_int|16
)braket
suffix:semicolon
id|ASSERT
c_func
(paren
id|brd
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|KLCLASS
c_func
(paren
id|brd-&gt;brd_type
)paren
)paren
(brace
r_case
id|KLCLASS_NODE
suffix:colon
id|board_name
op_assign
id|EDGE_LBL_NODE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KLCLASS_ROUTER
suffix:colon
r_if
c_cond
(paren
id|brd-&gt;brd_type
op_eq
id|KLTYPE_META_ROUTER
)paren
(brace
id|board_name
op_assign
id|EDGE_LBL_META_ROUTER
suffix:semicolon
id|hasmetarouter
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|brd-&gt;brd_type
op_eq
id|KLTYPE_REPEATER_ROUTER
)paren
(brace
id|board_name
op_assign
id|EDGE_LBL_REPEATER_ROUTER
suffix:semicolon
id|hasmetarouter
op_increment
suffix:semicolon
)brace
r_else
id|board_name
op_assign
id|EDGE_LBL_ROUTER
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KLCLASS_MIDPLANE
suffix:colon
id|board_name
op_assign
id|EDGE_LBL_MIDPLANE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KLCLASS_IO
suffix:colon
id|board_name
op_assign
id|EDGE_LBL_IO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KLCLASS_IOBRICK
suffix:colon
r_if
c_cond
(paren
id|brd-&gt;brd_type
op_eq
id|KLTYPE_PXBRICK
)paren
id|board_name
op_assign
id|EDGE_LBL_PXBRICK
suffix:semicolon
r_else
r_if
c_cond
(paren
id|brd-&gt;brd_type
op_eq
id|KLTYPE_IXBRICK
)paren
id|board_name
op_assign
id|EDGE_LBL_IXBRICK
suffix:semicolon
r_else
r_if
c_cond
(paren
id|brd-&gt;brd_type
op_eq
id|KLTYPE_OPUSBRICK
)paren
id|board_name
op_assign
id|EDGE_LBL_OPUSBRICK
suffix:semicolon
r_else
r_if
c_cond
(paren
id|brd-&gt;brd_type
op_eq
id|KLTYPE_CGBRICK
)paren
id|board_name
op_assign
id|EDGE_LBL_CGBRICK
suffix:semicolon
r_else
id|board_name
op_assign
id|EDGE_LBL_IOBRICK
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|board_name
op_assign
id|EDGE_LBL_UNKNOWN
suffix:semicolon
)brace
id|modnum
op_assign
id|geo_module
c_func
(paren
id|brd-&gt;brd_geoid
)paren
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
id|format_module_id
c_func
(paren
id|buffer
comma
id|modnum
comma
id|MODULE_FORMAT_BRIEF
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|path
comma
id|EDGE_LBL_MODULE
l_string|&quot;/%s/&quot;
id|EDGE_LBL_SLAB
l_string|&quot;/%d/%s&quot;
comma
id|buffer
comma
id|geo_slab
c_func
(paren
id|brd-&gt;brd_geoid
)paren
comma
id|board_name
)paren
suffix:semicolon
)brace
DECL|macro|MHZ
mdefine_line|#define MHZ&t;1000000
multiline_comment|/* Get the canonical hardware graph name for the given pci component&n; * on the given io board.&n; */
r_void
DECL|function|device_component_canonical_name_get
id|device_component_canonical_name_get
c_func
(paren
id|lboard_t
op_star
id|brd
comma
id|klinfo_t
op_star
id|component
comma
r_char
op_star
id|name
)paren
(brace
id|slotid_t
id|slot
suffix:semicolon
r_char
id|board_name
(braket
l_int|20
)braket
suffix:semicolon
id|ASSERT
c_func
(paren
id|brd
)paren
suffix:semicolon
multiline_comment|/* Convert the [ CLASS | TYPE ] kind of slotid&n;&t; * into a string&n;&t; */
id|slot
op_assign
id|brd-&gt;brd_slot
suffix:semicolon
multiline_comment|/* Get the io board name  */
r_if
c_cond
(paren
op_logical_neg
id|brd
op_logical_or
(paren
id|brd-&gt;brd_sversion
OL
l_int|2
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|name
comma
id|EDGE_LBL_XWIDGET
)paren
suffix:semicolon
)brace
r_else
(brace
id|nic_name_convert
c_func
(paren
id|brd-&gt;brd_name
comma
id|board_name
)paren
suffix:semicolon
)brace
multiline_comment|/* Give out the canonical  name of the pci device*/
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;/dev/hw/&quot;
id|EDGE_LBL_MODULE
l_string|&quot;/%x/&quot;
id|EDGE_LBL_SLAB
l_string|&quot;/%d/&quot;
id|EDGE_LBL_SLOT
l_string|&quot;/%s/&quot;
id|EDGE_LBL_PCI
l_string|&quot;/%d&quot;
comma
id|geo_module
c_func
(paren
id|brd-&gt;brd_geoid
)paren
comma
id|geo_slab
c_func
(paren
id|brd-&gt;brd_geoid
)paren
comma
id|board_name
comma
id|KLCF_BRIDGE_W_ID
c_func
(paren
id|component
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the serial number of the main  component of a board&n; * Returns 0 if a valid serial number is found&n; * 1 otherwise.&n; * Assumptions: Nic manufacturing string  has the following format&n; *&t;&t;&t;*Serial:&lt;serial_number&gt;;*&n; */
r_static
r_int
DECL|function|component_serial_number_get
id|component_serial_number_get
c_func
(paren
id|lboard_t
op_star
id|board
comma
id|klconf_off_t
id|mfg_nic_offset
comma
r_char
op_star
id|serial_number
comma
r_char
op_star
id|key_pattern
)paren
(brace
r_char
op_star
id|mfg_nic_string
suffix:semicolon
r_char
op_star
id|serial_string
comma
op_star
id|str
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
op_star
id|serial_pattern
op_assign
l_string|&quot;Serial:&quot;
suffix:semicolon
multiline_comment|/* We have an error on a null mfg nic offset */
r_if
c_cond
(paren
op_logical_neg
id|mfg_nic_offset
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Get the hub&squot;s manufacturing nic information&n;&t; * which is in the form of a pre-formatted string&n;&t; */
id|mfg_nic_string
op_assign
(paren
r_char
op_star
)paren
id|NODE_OFFSET_TO_K0
c_func
(paren
id|NASID_GET
c_func
(paren
id|board
)paren
comma
id|mfg_nic_offset
)paren
suffix:semicolon
multiline_comment|/* There is no manufacturing nic info */
r_if
c_cond
(paren
op_logical_neg
id|mfg_nic_string
)paren
r_return
l_int|1
suffix:semicolon
id|str
op_assign
id|mfg_nic_string
suffix:semicolon
multiline_comment|/* Look for the key pattern first (if it is  specified)&n;&t; * and then print the serial number corresponding to that.&n;&t; */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|key_pattern
comma
l_string|&quot;&quot;
)paren
op_logical_and
op_logical_neg
(paren
id|str
op_assign
id|strstr
c_func
(paren
id|mfg_nic_string
comma
id|key_pattern
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* There is no serial number info in the manufacturing&n;&t; * nic info&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|serial_string
op_assign
id|strstr
c_func
(paren
id|str
comma
id|serial_pattern
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|serial_string
op_assign
id|serial_string
op_plus
id|strlen
c_func
(paren
id|serial_pattern
)paren
suffix:semicolon
multiline_comment|/*  Copy the serial number information from the klconfig */
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|serial_string
(braket
id|i
)braket
op_ne
l_char|&squot;;&squot;
)paren
(brace
id|serial_number
(braket
id|i
)braket
op_assign
id|serial_string
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|serial_number
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the serial number of a board&n; * Returns 0 if a valid serial number is found&n; * 1 otherwise.&n; */
r_int
DECL|function|board_serial_number_get
id|board_serial_number_get
c_func
(paren
id|lboard_t
op_star
id|board
comma
r_char
op_star
id|serial_number
)paren
(brace
id|ASSERT
c_func
(paren
id|board
op_logical_and
id|serial_number
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|board
op_logical_or
op_logical_neg
id|serial_number
)paren
r_return
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|serial_number
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|KLCLASS
c_func
(paren
id|board-&gt;brd_type
)paren
)paren
(brace
r_case
id|KLCLASS_CPU
suffix:colon
(brace
multiline_comment|/* Node board */
id|klhub_t
op_star
id|hub
suffix:semicolon
multiline_comment|/* Get the hub component information */
id|hub
op_assign
(paren
id|klhub_t
op_star
)paren
id|find_first_component
c_func
(paren
id|board
comma
id|KLSTRUCT_HUB
)paren
suffix:semicolon
multiline_comment|/* If we don&squot;t have a hub component on an IP27&n;&t;&t; * then we have a weird klconfig.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|hub
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Get the serial number information from&n;&t;&t; * the hub&squot;s manufacturing nic info&n;&t;&t; */
r_if
c_cond
(paren
id|component_serial_number_get
c_func
(paren
id|board
comma
id|hub-&gt;hub_mfg_nic
comma
id|serial_number
comma
l_string|&quot;IP37&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|KLCLASS_IO
suffix:colon
(brace
multiline_comment|/* IO board */
id|klbri_t
op_star
id|bridge
suffix:semicolon
multiline_comment|/* Get the bridge component information */
id|bridge
op_assign
(paren
id|klbri_t
op_star
)paren
id|find_first_component
c_func
(paren
id|board
comma
id|KLSTRUCT_BRI
)paren
suffix:semicolon
multiline_comment|/* If we don&squot;t have a bridge component on an IO board&n;&t;&t; * then we have a weird klconfig.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|bridge
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Get the serial number information from&n;&t; &t; * the bridge&squot;s manufacturing nic info&n;&t;&t; */
r_if
c_cond
(paren
id|component_serial_number_get
c_func
(paren
id|board
comma
id|bridge-&gt;bri_mfg_nic
comma
id|serial_number
comma
l_string|&quot;&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|KLCLASS_ROUTER
suffix:colon
(brace
multiline_comment|/* Router board */
id|klrou_t
op_star
id|router
suffix:semicolon
multiline_comment|/* Get the router component information */
id|router
op_assign
(paren
id|klrou_t
op_star
)paren
id|find_first_component
c_func
(paren
id|board
comma
id|KLSTRUCT_ROU
)paren
suffix:semicolon
multiline_comment|/* If we don&squot;t have a router component on a router board&n;&t;&t; * then we have a weird klconfig.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|router
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Get the serial number information from&n;&t;&t; * the router&squot;s manufacturing nic info&n;&t;&t; */
r_if
c_cond
(paren
id|component_serial_number_get
c_func
(paren
id|board
comma
id|router-&gt;rou_mfg_nic
comma
id|serial_number
comma
l_string|&quot;&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|KLCLASS_GFX
suffix:colon
(brace
multiline_comment|/* Gfx board */
id|klgfx_t
op_star
id|graphics
suffix:semicolon
multiline_comment|/* Get the graphics component information */
id|graphics
op_assign
(paren
id|klgfx_t
op_star
)paren
id|find_first_component
c_func
(paren
id|board
comma
id|KLSTRUCT_GFX
)paren
suffix:semicolon
multiline_comment|/* If we don&squot;t have a gfx component on a gfx board&n;&t;&t; * then we have a weird klconfig.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|graphics
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Get the serial number information from&n;&t;&t; * the graphics&squot;s manufacturing nic info&n;&t;&t; */
r_if
c_cond
(paren
id|component_serial_number_get
c_func
(paren
id|board
comma
id|graphics-&gt;gfx_mfg_nic
comma
id|serial_number
comma
l_string|&quot;&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|strcpy
c_func
(paren
id|serial_number
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#include &quot;asm/sn/sn_private.h&quot;
multiline_comment|/*&n; * Format a module id for printing.&n; *&n; * There are three possible formats:&n; *&n; *   MODULE_FORMAT_BRIEF&t;is the brief 6-character format, including&n; *&t;&t;&t;&t;the actual brick-type as recorded in the &n; *&t;&t;&t;&t;moduleid_t, eg. 002c15 for a C-brick, or&n; *&t;&t;&t;&t;101#17 for a PX-brick.&n; *&n; *   MODULE_FORMAT_LONG&t;&t;is the hwgraph format, eg. rack/002/bay/15&n; *&t;&t;&t;&t;of rack/101/bay/17 (note that the brick&n; *&t;&t;&t;&t;type does not appear in this format).&n; *&n; *   MODULE_FORMAT_LCD&t;&t;is like MODULE_FORMAT_BRIEF, except that it&n; *&t;&t;&t;&t;ensures that the module id provided appears&n; *&t;&t;&t;&t;exactly as it would on the LCD display of&n; *&t;&t;&t;&t;the corresponding brick, eg. still 002c15&n; *&t;&t;&t;&t;for a C-brick, but 101p17 for a PX-brick.&n; */
r_void
DECL|function|format_module_id
id|format_module_id
c_func
(paren
r_char
op_star
id|buffer
comma
id|moduleid_t
id|m
comma
r_int
id|fmt
)paren
(brace
r_int
id|rack
comma
id|position
suffix:semicolon
r_char
id|brickchar
suffix:semicolon
id|rack
op_assign
id|MODULE_GET_RACK
c_func
(paren
id|m
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|MODULE_GET_BTYPE
c_func
(paren
id|m
)paren
OL
id|MAX_BRICK_TYPES
)paren
suffix:semicolon
id|brickchar
op_assign
id|MODULE_GET_BTCHAR
c_func
(paren
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fmt
op_eq
id|MODULE_FORMAT_LCD
)paren
(brace
multiline_comment|/* Be sure we use the same brick type character as displayed&n;&t;     * on the brick&squot;s LCD&n;&t;     */
r_switch
c_cond
(paren
id|brickchar
)paren
(brace
r_case
id|L1_BRICKTYPE_PX
suffix:colon
id|brickchar
op_assign
id|L1_BRICKTYPE_P
suffix:semicolon
r_break
suffix:semicolon
r_case
id|L1_BRICKTYPE_IX
suffix:colon
id|brickchar
op_assign
id|L1_BRICKTYPE_I
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|position
op_assign
id|MODULE_GET_BPOS
c_func
(paren
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fmt
op_eq
id|MODULE_FORMAT_BRIEF
)paren
op_logical_or
(paren
id|fmt
op_eq
id|MODULE_FORMAT_LCD
)paren
)paren
(brace
multiline_comment|/* Brief module number format, eg. 002c15 */
multiline_comment|/* Decompress the rack number */
op_star
id|buffer
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
id|RACK_GET_CLASS
c_func
(paren
id|rack
)paren
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
id|RACK_GET_GROUP
c_func
(paren
id|rack
)paren
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
id|RACK_GET_NUM
c_func
(paren
id|rack
)paren
suffix:semicolon
multiline_comment|/* Add the brick type */
op_star
id|buffer
op_increment
op_assign
id|brickchar
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fmt
op_eq
id|MODULE_FORMAT_LONG
)paren
(brace
multiline_comment|/* Fuller hwgraph format, eg. rack/002/bay/15 */
id|strcpy
c_func
(paren
id|buffer
comma
id|EDGE_LBL_RACK
l_string|&quot;/&quot;
)paren
suffix:semicolon
id|buffer
op_add_assign
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
id|RACK_GET_CLASS
c_func
(paren
id|rack
)paren
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
id|RACK_GET_GROUP
c_func
(paren
id|rack
)paren
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
id|RACK_GET_NUM
c_func
(paren
id|rack
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|buffer
comma
l_string|&quot;/&quot;
id|EDGE_LBL_RPOS
l_string|&quot;/&quot;
)paren
suffix:semicolon
id|buffer
op_add_assign
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
multiline_comment|/* Add the bay position, using at least two digits */
r_if
c_cond
(paren
id|position
OL
l_int|10
)paren
op_star
id|buffer
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d&quot;
comma
id|position
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a module id, in either brief or long form.&n; * Returns &lt; 0 on error.&n; * The long form does not include a brick type, so it defaults to 0 (CBrick)&n; */
r_int
DECL|function|parse_module_id
id|parse_module_id
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
r_int
id|v
comma
id|rack
comma
id|bay
comma
id|type
comma
id|form
suffix:semicolon
id|moduleid_t
id|m
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|buffer
comma
id|EDGE_LBL_RACK
l_string|&quot;/&quot;
)paren
op_eq
id|buffer
)paren
(brace
id|form
op_assign
id|MODULE_FORMAT_LONG
suffix:semicolon
id|buffer
op_add_assign
id|strlen
c_func
(paren
id|EDGE_LBL_RACK
l_string|&quot;/&quot;
)paren
suffix:semicolon
multiline_comment|/* A long module ID must be exactly 5 non-template chars. */
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|buffer
)paren
op_ne
id|strlen
c_func
(paren
l_string|&quot;/&quot;
id|EDGE_LBL_RPOS
l_string|&quot;/&quot;
)paren
op_plus
l_int|5
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|form
op_assign
id|MODULE_FORMAT_BRIEF
suffix:semicolon
multiline_comment|/* A brief module id must be exactly 6 characters */
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|buffer
)paren
op_ne
l_int|6
)paren
r_return
op_minus
l_int|2
suffix:semicolon
)brace
multiline_comment|/* The rack number must be exactly 3 digits */
r_if
c_cond
(paren
op_logical_neg
(paren
id|isdigit
c_func
(paren
id|buffer
(braket
l_int|0
)braket
)paren
op_logical_and
id|isdigit
c_func
(paren
id|buffer
(braket
l_int|1
)braket
)paren
op_logical_and
id|isdigit
c_func
(paren
id|buffer
(braket
l_int|2
)braket
)paren
)paren
)paren
r_return
op_minus
l_int|3
suffix:semicolon
id|rack
op_assign
l_int|0
suffix:semicolon
id|v
op_assign
op_star
id|buffer
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|v
OG
id|RACK_CLASS_MASK
c_func
(paren
id|rack
)paren
op_rshift
id|RACK_CLASS_SHFT
c_func
(paren
id|rack
)paren
)paren
r_return
op_minus
l_int|4
suffix:semicolon
id|RACK_ADD_CLASS
c_func
(paren
id|rack
comma
id|v
)paren
suffix:semicolon
id|v
op_assign
op_star
id|buffer
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|v
OG
id|RACK_GROUP_MASK
c_func
(paren
id|rack
)paren
op_rshift
id|RACK_GROUP_SHFT
c_func
(paren
id|rack
)paren
)paren
r_return
op_minus
l_int|5
suffix:semicolon
id|RACK_ADD_GROUP
c_func
(paren
id|rack
comma
id|v
)paren
suffix:semicolon
id|v
op_assign
op_star
id|buffer
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
multiline_comment|/* rack numbers are 1-based */
r_if
c_cond
(paren
id|v
op_minus
l_int|1
OG
id|RACK_NUM_MASK
c_func
(paren
id|rack
)paren
op_rshift
id|RACK_NUM_SHFT
c_func
(paren
id|rack
)paren
)paren
r_return
op_minus
l_int|6
suffix:semicolon
id|RACK_ADD_NUM
c_func
(paren
id|rack
comma
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|form
op_eq
id|MODULE_FORMAT_BRIEF
)paren
(brace
multiline_comment|/* Next should be a module type character.  Accept ucase or lcase. */
id|c
op_assign
op_star
id|buffer
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isalpha
c_func
(paren
id|c
)paren
)paren
r_return
op_minus
l_int|7
suffix:semicolon
multiline_comment|/* strchr() returns a pointer into brick_types[], or NULL */
id|type
op_assign
(paren
r_int
r_int
)paren
(paren
id|strchr
c_func
(paren
id|brick_types
comma
id|tolower
c_func
(paren
id|c
)paren
)paren
op_minus
id|brick_types
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OG
id|MODULE_BTYPE_MASK
op_rshift
id|MODULE_BTYPE_SHFT
)paren
r_return
op_minus
l_int|8
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Hardcode the module type, and skip over the boilerplate */
id|type
op_assign
id|MODULE_CBRICK
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|buffer
comma
l_string|&quot;/&quot;
id|EDGE_LBL_RPOS
l_string|&quot;/&quot;
)paren
op_ne
id|buffer
)paren
r_return
op_minus
l_int|9
suffix:semicolon
id|buffer
op_add_assign
id|strlen
c_func
(paren
l_string|&quot;/&quot;
id|EDGE_LBL_RPOS
l_string|&quot;/&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* The bay number is last.  Make sure it&squot;s exactly two digits */
r_if
c_cond
(paren
op_logical_neg
(paren
id|isdigit
c_func
(paren
id|buffer
(braket
l_int|0
)braket
)paren
op_logical_and
id|isdigit
c_func
(paren
id|buffer
(braket
l_int|1
)braket
)paren
op_logical_and
op_logical_neg
id|buffer
(braket
l_int|2
)braket
)paren
)paren
r_return
op_minus
l_int|10
suffix:semicolon
id|bay
op_assign
l_int|10
op_star
(paren
id|buffer
(braket
l_int|0
)braket
op_minus
l_char|&squot;0&squot;
)paren
op_plus
(paren
id|buffer
(braket
l_int|1
)braket
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bay
OG
id|MODULE_BPOS_MASK
op_rshift
id|MODULE_BPOS_SHFT
)paren
r_return
op_minus
l_int|11
suffix:semicolon
id|m
op_assign
id|RBT_TO_MODULE
c_func
(paren
id|rack
comma
id|bay
comma
id|type
)paren
suffix:semicolon
multiline_comment|/* avoid sign extending the moduleid_t */
r_return
(paren
r_int
)paren
(paren
r_int
r_int
)paren
id|m
suffix:semicolon
)brace
eof
