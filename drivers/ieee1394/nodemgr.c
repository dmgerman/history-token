multiline_comment|/*&n; * Node information (ConfigROM) collection and management.&n; *&n; * Copyright (C) 2000 Andreas E. Bombe&n; *               2001 Ben Collins &lt;bcollins@debian.net&gt;&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;ieee1394_types.h&quot;
macro_line|#include &quot;ieee1394.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;ieee1394_transactions.h&quot;
macro_line|#include &quot;highlevel.h&quot;
macro_line|#include &quot;csr.h&quot;
macro_line|#include &quot;nodemgr.h&quot;
DECL|macro|NODE_BUS_FMT
mdefine_line|#define NODE_BUS_FMT&t;&quot;%d:%d&quot;
DECL|macro|NODE_BUS_ARGS
mdefine_line|#define NODE_BUS_ARGS(nodeid) &bslash;&n;&t;(nodeid &amp; NODE_MASK), ((nodeid &amp; BUS_MASK) &gt;&gt; 6)
multiline_comment|/* Basically what we do here is start off retrieving the bus_info block.&n; * From there will fill in some info about the node, verify it is of IEEE&n; * 1394 type, and that the crc checks out ok. After that we start off with&n; * the root directory, and subdirectories. To do this, we retrieve the&n; * quadlet header for a directory, find out the length, and retrieve the&n; * complete directory entry (be it a leaf or a directory). We then process&n; * it and add the info to our structure for that particular node.&n; *&n; * We verify CRC&squot;s along the way for each directory/block/leaf. The&n; * entire node structure is generic, and simply stores the information in&n; * a way that&squot;s easy to parse by the protocol interface.&n; *&n; * XXX: Most of this isn&squot;t done yet :)  */
r_static
id|LIST_HEAD
c_func
(paren
id|node_list
)paren
suffix:semicolon
DECL|variable|node_lock
r_static
id|rwlock_t
id|node_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|host_info_list
)paren
suffix:semicolon
DECL|variable|host_info_lock
r_static
id|spinlock_t
id|host_info_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|struct|host_info
r_struct
id|host_info
(brace
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|task
r_struct
id|tq_struct
id|task
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|function|create_node_entry
r_static
r_struct
id|node_entry
op_star
id|create_node_entry
c_func
(paren
r_void
)paren
(brace
r_struct
id|node_entry
op_star
id|ne
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|ne
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|node_entry
)paren
comma
id|SLAB_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ne
)paren
r_return
l_int|NULL
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ne-&gt;list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ne-&gt;unit_directories
)paren
suffix:semicolon
id|ne-&gt;guid
op_assign
(paren
id|u64
)paren
op_minus
l_int|1
suffix:semicolon
id|ne-&gt;host
op_assign
l_int|NULL
suffix:semicolon
id|ne-&gt;nodeid
op_assign
l_int|0
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|ne-&gt;generation
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|ne-&gt;list
comma
op_amp
id|node_list
)paren
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ne
suffix:semicolon
)brace
DECL|function|find_entry_by_guid
r_static
r_struct
id|node_entry
op_star
id|find_entry_by_guid
c_func
(paren
id|u64
id|guid
)paren
(brace
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|node_entry
op_star
id|ne
suffix:semicolon
id|list_for_each
c_func
(paren
id|lh
comma
op_amp
id|node_list
)paren
(brace
id|ne
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|node_entry
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ne-&gt;guid
op_eq
id|guid
)paren
r_return
id|ne
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|find_entry_by_nodeid
r_static
r_struct
id|node_entry
op_star
id|find_entry_by_nodeid
c_func
(paren
id|nodeid_t
id|nodeid
)paren
(brace
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|node_entry
op_star
id|ne
suffix:semicolon
id|list_for_each
c_func
(paren
id|lh
comma
op_amp
id|node_list
)paren
(brace
id|ne
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|node_entry
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ne-&gt;nodeid
op_eq
id|nodeid
)paren
r_return
id|ne
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|nodemgr_read_quadlet
r_int
id|nodemgr_read_quadlet
c_func
(paren
r_struct
id|node_entry
op_star
id|ne
comma
id|octlet_t
id|address
comma
id|quadlet_t
op_star
id|quad
)paren
(brace
r_if
c_cond
(paren
id|hpsb_read
c_func
(paren
id|ne-&gt;host
comma
id|ne-&gt;nodeid
comma
id|address
comma
id|quad
comma
l_int|4
)paren
)paren
(brace
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;read of address %Lx failed&quot;
comma
id|address
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
op_star
id|quad
op_assign
id|be32_to_cpu
c_func
(paren
op_star
id|quad
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|CONFIG_ROM_VENDOR_ID
mdefine_line|#define CONFIG_ROM_VENDOR_ID&t;&t;0x03
DECL|macro|CONFIG_ROM_MODEL_ID
mdefine_line|#define CONFIG_ROM_MODEL_ID&t;&t;0x17
DECL|macro|CONFIG_ROM_NODE_CAPABILITES
mdefine_line|#define CONFIG_ROM_NODE_CAPABILITES&t;0x0C
DECL|macro|CONFIG_ROM_UNIT_DIRECTORY
mdefine_line|#define CONFIG_ROM_UNIT_DIRECTORY&t;0xd1
DECL|macro|CONFIG_ROM_SPECIFIER_ID
mdefine_line|#define CONFIG_ROM_SPECIFIER_ID&t;&t;0x12 
DECL|macro|CONFIG_ROM_VERSION
mdefine_line|#define CONFIG_ROM_VERSION&t;&t;0x13
DECL|macro|CONFIG_ROM_DESCRIPTOR_LEAF
mdefine_line|#define CONFIG_ROM_DESCRIPTOR_LEAF&t;0x81
DECL|macro|CONFIG_ROM_DESCRIPTOR_DIRECTORY
mdefine_line|#define CONFIG_ROM_DESCRIPTOR_DIRECTORY&t;0xc1
multiline_comment|/* This implementation currently only scans the config rom and its&n; * immediate unit directories looking for software_id and&n; * software_version entries, in order to get driver autoloading working.&n; */
DECL|function|nodemgr_process_unit_directory
r_static
r_void
id|nodemgr_process_unit_directory
c_func
(paren
r_struct
id|node_entry
op_star
id|ne
comma
id|octlet_t
id|address
)paren
(brace
r_struct
id|unit_directory
op_star
id|ud
suffix:semicolon
id|octlet_t
id|a
suffix:semicolon
id|quadlet_t
id|quad
suffix:semicolon
r_int
id|length
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ud
op_assign
id|kmalloc
(paren
r_sizeof
op_star
id|ud
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_goto
id|unit_directory_error
suffix:semicolon
id|memset
(paren
id|ud
comma
l_int|0
comma
r_sizeof
op_star
id|ud
)paren
suffix:semicolon
id|ud-&gt;address
op_assign
id|address
suffix:semicolon
r_if
c_cond
(paren
id|nodemgr_read_quadlet
c_func
(paren
id|ne
comma
id|address
comma
op_amp
id|quad
)paren
)paren
r_goto
id|unit_directory_error
suffix:semicolon
id|length
op_assign
id|quad
op_rshift
l_int|16
suffix:semicolon
id|a
op_assign
id|address
op_plus
l_int|4
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
id|length
suffix:semicolon
id|i
op_increment
comma
id|a
op_add_assign
l_int|4
)paren
(brace
r_int
id|code
comma
id|value
suffix:semicolon
r_if
c_cond
(paren
id|nodemgr_read_quadlet
c_func
(paren
id|ne
comma
id|a
comma
op_amp
id|quad
)paren
)paren
r_goto
id|unit_directory_error
suffix:semicolon
id|code
op_assign
id|quad
op_rshift
l_int|24
suffix:semicolon
id|value
op_assign
id|quad
op_amp
l_int|0xffffff
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|CONFIG_ROM_VENDOR_ID
suffix:colon
id|ud-&gt;vendor_id
op_assign
id|value
suffix:semicolon
id|ud-&gt;flags
op_or_assign
id|UNIT_DIRECTORY_VENDOR_ID
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CONFIG_ROM_MODEL_ID
suffix:colon
id|ud-&gt;model_id
op_assign
id|value
suffix:semicolon
id|ud-&gt;flags
op_or_assign
id|UNIT_DIRECTORY_MODEL_ID
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CONFIG_ROM_SPECIFIER_ID
suffix:colon
id|ud-&gt;specifier_id
op_assign
id|value
suffix:semicolon
id|ud-&gt;flags
op_or_assign
id|UNIT_DIRECTORY_SPECIFIER_ID
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CONFIG_ROM_VERSION
suffix:colon
id|ud-&gt;version
op_assign
id|value
suffix:semicolon
id|ud-&gt;flags
op_or_assign
id|UNIT_DIRECTORY_VERSION
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CONFIG_ROM_DESCRIPTOR_LEAF
suffix:colon
r_case
id|CONFIG_ROM_DESCRIPTOR_DIRECTORY
suffix:colon
multiline_comment|/* TODO: read strings... icons? */
r_break
suffix:semicolon
)brace
)brace
id|list_add_tail
(paren
op_amp
id|ud-&gt;list
comma
op_amp
id|ne-&gt;unit_directories
)paren
suffix:semicolon
r_return
suffix:semicolon
id|unit_directory_error
suffix:colon
r_if
c_cond
(paren
id|ud
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|ud
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IEEE1394_VERBOSEDEBUG
DECL|function|dump_directories
r_static
r_void
id|dump_directories
(paren
r_struct
id|node_entry
op_star
id|ne
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;vendor_id=0x%06x, capabilities=0x%06x&quot;
comma
id|ne-&gt;vendor_id
comma
id|ne-&gt;capabilities
)paren
suffix:semicolon
id|list_for_each
(paren
id|l
comma
op_amp
id|ne-&gt;unit_directories
)paren
(brace
r_struct
id|unit_directory
op_star
id|ud
op_assign
id|list_entry
(paren
id|l
comma
r_struct
id|unit_directory
comma
id|list
)paren
suffix:semicolon
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;unit directory:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ud-&gt;flags
op_amp
id|UNIT_DIRECTORY_VENDOR_ID
)paren
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;  vendor_id=0x%06x &quot;
comma
id|ud-&gt;vendor_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ud-&gt;flags
op_amp
id|UNIT_DIRECTORY_MODEL_ID
)paren
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;  model_id=0x%06x &quot;
comma
id|ud-&gt;model_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ud-&gt;flags
op_amp
id|UNIT_DIRECTORY_SPECIFIER_ID
)paren
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;  specifier_id=0x%06x &quot;
comma
id|ud-&gt;specifier_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ud-&gt;flags
op_amp
id|UNIT_DIRECTORY_VERSION
)paren
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;  version=0x%06x &quot;
comma
id|ud-&gt;version
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|nodemgr_process_root_directory
r_static
r_void
id|nodemgr_process_root_directory
c_func
(paren
r_struct
id|node_entry
op_star
id|ne
)paren
(brace
id|octlet_t
id|address
suffix:semicolon
id|quadlet_t
id|quad
suffix:semicolon
r_int
id|length
comma
id|i
suffix:semicolon
id|address
op_assign
id|CSR_REGISTER_BASE
op_plus
id|CSR_CONFIG_ROM
suffix:semicolon
r_if
c_cond
(paren
id|nodemgr_read_quadlet
c_func
(paren
id|ne
comma
id|address
comma
op_amp
id|quad
)paren
)paren
r_return
suffix:semicolon
id|address
op_add_assign
l_int|4
op_plus
(paren
id|quad
op_rshift
l_int|24
)paren
op_star
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|nodemgr_read_quadlet
c_func
(paren
id|ne
comma
id|address
comma
op_amp
id|quad
)paren
)paren
r_return
suffix:semicolon
id|length
op_assign
id|quad
op_rshift
l_int|16
suffix:semicolon
id|address
op_add_assign
l_int|4
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
id|length
suffix:semicolon
id|i
op_increment
comma
id|address
op_add_assign
l_int|4
)paren
(brace
r_int
id|code
comma
id|value
suffix:semicolon
r_if
c_cond
(paren
id|nodemgr_read_quadlet
c_func
(paren
id|ne
comma
id|address
comma
op_amp
id|quad
)paren
)paren
r_return
suffix:semicolon
id|code
op_assign
id|quad
op_rshift
l_int|24
suffix:semicolon
id|value
op_assign
id|quad
op_amp
l_int|0xffffff
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|CONFIG_ROM_VENDOR_ID
suffix:colon
id|ne-&gt;vendor_id
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CONFIG_ROM_NODE_CAPABILITES
suffix:colon
id|ne-&gt;capabilities
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CONFIG_ROM_UNIT_DIRECTORY
suffix:colon
id|nodemgr_process_unit_directory
c_func
(paren
id|ne
comma
id|address
op_plus
id|value
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CONFIG_ROM_DESCRIPTOR_LEAF
suffix:colon
r_case
id|CONFIG_ROM_DESCRIPTOR_DIRECTORY
suffix:colon
multiline_comment|/* TODO: read strings... icons? */
r_break
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_IEEE1394_VERBOSEDEBUG
id|dump_directories
c_func
(paren
id|ne
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|register_node
r_static
r_void
id|register_node
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|nodeid_t
id|nodeid
comma
id|u64
id|guid
comma
id|quadlet_t
id|busoptions
)paren
(brace
r_struct
id|node_entry
op_star
id|ne
suffix:semicolon
r_int
r_int
id|flags
comma
r_new
op_assign
l_int|0
suffix:semicolon
id|read_lock_irqsave
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
id|ne
op_assign
id|find_entry_by_guid
c_func
(paren
id|guid
)paren
suffix:semicolon
id|read_unlock_irqrestore
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* New entry */
r_if
c_cond
(paren
op_logical_neg
id|ne
)paren
(brace
r_if
c_cond
(paren
(paren
id|ne
op_assign
id|create_node_entry
c_func
(paren
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;%s added: node &quot;
id|NODE_BUS_FMT
l_string|&quot;, GUID %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x&quot;
comma
(paren
id|host-&gt;node_id
op_eq
id|nodeid
)paren
ques
c_cond
l_string|&quot;Local host&quot;
suffix:colon
l_string|&quot;Device&quot;
comma
id|NODE_BUS_ARGS
c_func
(paren
id|nodeid
)paren
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|guid
)paren
(braket
l_int|0
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|guid
)paren
(braket
l_int|1
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|guid
)paren
(braket
l_int|2
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|guid
)paren
(braket
l_int|3
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|guid
)paren
(braket
l_int|4
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|guid
)paren
(braket
l_int|5
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|guid
)paren
(braket
l_int|6
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|guid
)paren
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|ne-&gt;guid
op_assign
id|guid
suffix:semicolon
r_new
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
r_new
op_logical_and
id|ne-&gt;nodeid
op_ne
id|nodeid
)paren
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;Node &quot;
id|NODE_BUS_FMT
l_string|&quot; changed to &quot;
id|NODE_BUS_FMT
comma
id|NODE_BUS_ARGS
c_func
(paren
id|ne-&gt;nodeid
)paren
comma
id|NODE_BUS_ARGS
c_func
(paren
id|nodeid
)paren
)paren
suffix:semicolon
id|ne-&gt;host
op_assign
id|host
suffix:semicolon
id|ne-&gt;nodeid
op_assign
id|nodeid
suffix:semicolon
multiline_comment|/* Now set the bus options. Only do all this crap if this is a new&n;&t; * node, or if the generation number has changed.  */
r_if
c_cond
(paren
r_new
op_logical_or
id|ne-&gt;busopt.generation
op_ne
(paren
(paren
id|busoptions
op_rshift
l_int|6
)paren
op_amp
l_int|0x3
)paren
)paren
(brace
id|ne-&gt;busopt.irmc
op_assign
(paren
id|busoptions
op_rshift
l_int|31
)paren
op_amp
l_int|1
suffix:semicolon
id|ne-&gt;busopt.cmc
op_assign
(paren
id|busoptions
op_rshift
l_int|30
)paren
op_amp
l_int|1
suffix:semicolon
id|ne-&gt;busopt.isc
op_assign
(paren
id|busoptions
op_rshift
l_int|29
)paren
op_amp
l_int|1
suffix:semicolon
id|ne-&gt;busopt.bmc
op_assign
(paren
id|busoptions
op_rshift
l_int|28
)paren
op_amp
l_int|1
suffix:semicolon
id|ne-&gt;busopt.pmc
op_assign
(paren
id|busoptions
op_rshift
l_int|27
)paren
op_amp
l_int|1
suffix:semicolon
id|ne-&gt;busopt.cyc_clk_acc
op_assign
(paren
id|busoptions
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|ne-&gt;busopt.max_rec
op_assign
l_int|1
op_lshift
(paren
(paren
(paren
id|busoptions
op_rshift
l_int|12
)paren
op_amp
l_int|0xf
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|ne-&gt;busopt.generation
op_assign
(paren
id|busoptions
op_rshift
l_int|6
)paren
op_amp
l_int|0x3
suffix:semicolon
id|ne-&gt;busopt.lnkspd
op_assign
id|busoptions
op_amp
l_int|0x7
suffix:semicolon
multiline_comment|/* Now, process the rest of the tree */
id|nodemgr_process_root_directory
c_func
(paren
id|ne
)paren
suffix:semicolon
)brace
multiline_comment|/* Since that&squot;s done, we can declare this record current */
id|atomic_set
c_func
(paren
op_amp
id|ne-&gt;generation
comma
id|get_hpsb_generation
c_func
(paren
id|host
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IEEE1394_VERBOSEDEBUG
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;raw=0x%08x irmc=%d cmc=%d isc=%d bmc=%d pmc=%d cyc_clk_acc=%d &quot;
l_string|&quot;max_rec=%d gen=%d lspd=%d&quot;
comma
id|busoptions
comma
id|ne-&gt;busopt.irmc
comma
id|ne-&gt;busopt.cmc
comma
id|ne-&gt;busopt.isc
comma
id|ne-&gt;busopt.bmc
comma
id|ne-&gt;busopt.pmc
comma
id|ne-&gt;busopt.cyc_clk_acc
comma
id|ne-&gt;busopt.max_rec
comma
id|ne-&gt;busopt.generation
comma
id|ne-&gt;busopt.lnkspd
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
DECL|function|nodemgr_remove_node
r_static
r_void
id|nodemgr_remove_node
c_func
(paren
r_struct
id|node_entry
op_star
id|ne
)paren
(brace
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;Device removed: node &quot;
id|NODE_BUS_FMT
l_string|&quot;, GUID &quot;
l_string|&quot;%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x&quot;
comma
id|NODE_BUS_ARGS
c_func
(paren
id|ne-&gt;nodeid
)paren
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|ne-&gt;guid
)paren
(braket
l_int|0
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|ne-&gt;guid
)paren
(braket
l_int|1
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|ne-&gt;guid
)paren
(braket
l_int|2
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|ne-&gt;guid
)paren
(braket
l_int|3
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|ne-&gt;guid
)paren
(braket
l_int|4
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|ne-&gt;guid
)paren
(braket
l_int|5
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|ne-&gt;guid
)paren
(braket
l_int|6
)braket
comma
(paren
(paren
id|u8
op_star
)paren
op_amp
id|ne-&gt;guid
)paren
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|ne-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ne
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* This is where we probe the nodes for their information and provided&n; * features.  */
DECL|function|nodemgr_node_probe
r_static
r_void
id|nodemgr_node_probe
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|hpsb_host
op_star
id|host
op_assign
(paren
r_struct
id|hpsb_host
op_star
)paren
id|data
suffix:semicolon
r_struct
id|selfid
op_star
id|sid
op_assign
(paren
r_struct
id|selfid
op_star
)paren
id|host-&gt;topology_map
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|node_entry
op_star
id|ne
suffix:semicolon
r_int
id|nodecount
op_assign
id|host-&gt;node_count
suffix:semicolon
id|nodeid_t
id|nodeid
op_assign
id|LOCAL_BUS
suffix:semicolon
id|quadlet_t
id|buffer
(braket
l_int|5
)braket
comma
id|quad
suffix:semicolon
id|octlet_t
id|base
op_assign
id|CSR_REGISTER_BASE
op_plus
id|CSR_CONFIG_ROM
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* We need to detect when the ConfigROM&squot;s generation has changed,&n;&t; * so we only update the node&squot;s info when it needs to be.  */
r_for
c_loop
(paren
suffix:semicolon
id|nodecount
suffix:semicolon
id|nodecount
op_decrement
comma
id|nodeid
op_increment
comma
id|sid
op_increment
)paren
(brace
r_int
id|retries
op_assign
l_int|3
suffix:semicolon
r_int
id|header_count
suffix:semicolon
r_int
id|header_size
suffix:semicolon
id|octlet_t
id|guid
suffix:semicolon
multiline_comment|/* Skip extended, and non-active node&squot;s */
r_while
c_loop
(paren
id|sid-&gt;extended
)paren
id|sid
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sid-&gt;link_active
)paren
r_continue
suffix:semicolon
multiline_comment|/* Just use our local ROM */
r_if
c_cond
(paren
id|nodeid
op_eq
id|host-&gt;node_id
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
id|buffer
(braket
id|i
)braket
op_assign
id|be32_to_cpu
c_func
(paren
id|host-&gt;csr.rom
(braket
id|i
)braket
)paren
suffix:semicolon
r_goto
id|set_options
suffix:semicolon
)brace
id|retry_configrom
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|retries
op_decrement
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;Giving up on node &quot;
id|NODE_BUS_FMT
l_string|&quot; for ConfigROM probe, too many errors&quot;
comma
id|NODE_BUS_ARGS
c_func
(paren
id|nodeid
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|header_count
op_assign
l_int|0
suffix:semicolon
id|header_size
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_IEEE1394_VERBOSEDEBUG
id|HPSB_INFO
c_func
(paren
l_string|&quot;Initiating ConfigROM request for node &quot;
id|NODE_BUS_FMT
comma
id|NODE_BUS_ARGS
c_func
(paren
id|nodeid
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Now, P1212 says that devices should support 64byte block&n;&t;&t; * reads, aligned on 64byte boundaries. That doesn&squot;t seem&n;&t;&t; * to work though, and we are forced to doing quadlet&n;&t;&t; * sized reads.  */
r_if
c_cond
(paren
id|hpsb_read
c_func
(paren
id|host
comma
id|nodeid
comma
id|base
comma
op_amp
id|quad
comma
l_int|4
)paren
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;ConfigROM quadlet transaction error for node &quot;
id|NODE_BUS_FMT
comma
id|NODE_BUS_ARGS
c_func
(paren
id|nodeid
)paren
)paren
suffix:semicolon
r_goto
id|retry_configrom
suffix:semicolon
)brace
id|buffer
(braket
id|header_count
op_increment
)braket
op_assign
id|be32_to_cpu
c_func
(paren
id|quad
)paren
suffix:semicolon
id|header_size
op_assign
id|buffer
(braket
l_int|0
)braket
op_rshift
l_int|24
suffix:semicolon
r_if
c_cond
(paren
id|header_size
OL
l_int|4
)paren
(brace
id|HPSB_INFO
c_func
(paren
l_string|&quot;Node &quot;
id|NODE_BUS_FMT
l_string|&quot; has non-standard ROM format (%d quads), &quot;
l_string|&quot;cannot parse&quot;
comma
id|NODE_BUS_ARGS
c_func
(paren
id|nodeid
)paren
comma
id|header_size
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_while
c_loop
(paren
id|header_count
op_le
id|header_size
op_logical_and
(paren
id|header_count
op_lshift
l_int|2
)paren
OL
r_sizeof
(paren
id|buffer
)paren
)paren
(brace
r_if
c_cond
(paren
id|hpsb_read
c_func
(paren
id|host
comma
id|nodeid
comma
id|base
op_plus
(paren
id|header_count
op_lshift
l_int|2
)paren
comma
op_amp
id|quad
comma
l_int|4
)paren
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;ConfigROM quadlet transaction error for &quot;
id|NODE_BUS_FMT
comma
id|NODE_BUS_ARGS
c_func
(paren
id|nodeid
)paren
)paren
suffix:semicolon
r_goto
id|retry_configrom
suffix:semicolon
)brace
id|buffer
(braket
id|header_count
op_increment
)braket
op_assign
id|be32_to_cpu
c_func
(paren
id|quad
)paren
suffix:semicolon
)brace
id|set_options
suffix:colon
r_if
c_cond
(paren
id|buffer
(braket
l_int|1
)braket
op_ne
id|IEEE1394_BUSID_MAGIC
)paren
(brace
multiline_comment|/* This isn&squot;t a 1394 device */
id|HPSB_ERR
c_func
(paren
l_string|&quot;Node &quot;
id|NODE_BUS_FMT
l_string|&quot; isn&squot;t an IEEE 1394 device&quot;
comma
id|NODE_BUS_ARGS
c_func
(paren
id|nodeid
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|guid
op_assign
id|be64_to_cpu
c_func
(paren
(paren
(paren
id|u64
)paren
id|buffer
(braket
l_int|3
)braket
op_lshift
l_int|32
)paren
op_or
id|buffer
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|register_node
c_func
(paren
id|host
comma
id|nodeid
comma
id|guid
comma
id|buffer
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Now check to see if we have any nodes that aren&squot;t referenced&n;&t; * any longer.  */
id|write_lock_irqsave
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|lh
comma
op_amp
id|node_list
)paren
(brace
id|ne
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|node_entry
comma
id|list
)paren
suffix:semicolon
multiline_comment|/* Only checking this host */
r_if
c_cond
(paren
id|ne-&gt;host
op_ne
id|host
)paren
r_continue
suffix:semicolon
multiline_comment|/* If the generation didn&squot;t get updated, then either the&n;&t;&t; * node was removed, or it failed the above probe. Either&n;&t;&t; * way, we remove references to it, since they are&n;&t;&t; * invalid.  */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ne-&gt;generation
)paren
op_ne
id|get_hpsb_generation
c_func
(paren
id|host
)paren
)paren
id|nodemgr_remove_node
c_func
(paren
id|ne
)paren
suffix:semicolon
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|hpsb_guid_get_entry
r_struct
id|node_entry
op_star
id|hpsb_guid_get_entry
c_func
(paren
id|u64
id|guid
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|node_entry
op_star
id|ne
suffix:semicolon
id|read_lock_irqsave
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
id|ne
op_assign
id|find_entry_by_guid
c_func
(paren
id|guid
)paren
suffix:semicolon
id|read_unlock_irqrestore
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ne
suffix:semicolon
)brace
DECL|function|hpsb_nodeid_get_entry
r_struct
id|node_entry
op_star
id|hpsb_nodeid_get_entry
c_func
(paren
id|nodeid_t
id|nodeid
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|node_entry
op_star
id|ne
suffix:semicolon
id|read_lock_irqsave
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
id|ne
op_assign
id|find_entry_by_nodeid
c_func
(paren
id|nodeid
)paren
suffix:semicolon
id|read_unlock_irqrestore
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ne
suffix:semicolon
)brace
DECL|function|hpsb_get_host_by_ne
r_struct
id|hpsb_host
op_star
id|hpsb_get_host_by_ne
c_func
(paren
r_struct
id|node_entry
op_star
id|ne
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ne-&gt;generation
)paren
op_ne
id|get_hpsb_generation
c_func
(paren
id|ne-&gt;host
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ne-&gt;nodeid
op_eq
id|ne-&gt;host-&gt;node_id
)paren
r_return
id|ne-&gt;host
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|hpsb_guid_fill_packet
r_int
id|hpsb_guid_fill_packet
c_func
(paren
r_struct
id|node_entry
op_star
id|ne
comma
r_struct
id|hpsb_packet
op_star
id|pkt
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ne-&gt;generation
)paren
op_ne
id|get_hpsb_generation
c_func
(paren
id|ne-&gt;host
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|pkt-&gt;host
op_assign
id|ne-&gt;host
suffix:semicolon
id|pkt-&gt;node_id
op_assign
id|ne-&gt;nodeid
suffix:semicolon
id|pkt-&gt;generation
op_assign
id|atomic_read
c_func
(paren
op_amp
id|ne-&gt;generation
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|nodemgr_add_host
r_static
r_void
id|nodemgr_add_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|host_info
op_star
id|hi
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|host_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hi
)paren
(brace
id|HPSB_ERR
(paren
l_string|&quot;Out of memory in Node Manager&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* We simply initialize the struct here. We don&squot;t start the thread&n;&t; * until the first bus reset.  */
id|hi-&gt;host
op_assign
id|host
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hi-&gt;list
)paren
suffix:semicolon
id|INIT_TQUEUE
c_func
(paren
op_amp
id|hi-&gt;task
comma
id|nodemgr_node_probe
comma
id|host
)paren
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|host_info_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
(paren
op_amp
id|hi-&gt;list
comma
op_amp
id|host_info_list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|host_info_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|nodemgr_host_reset
r_static
r_void
id|nodemgr_host_reset
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|host_info
op_star
id|hi
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|host_info_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|lh
comma
op_amp
id|host_info_list
)paren
(brace
r_struct
id|host_info
op_star
id|myhi
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|host_info
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|myhi-&gt;host
op_eq
id|host
)paren
(brace
id|hi
op_assign
id|myhi
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|hi
op_eq
l_int|NULL
)paren
(brace
id|HPSB_ERR
(paren
l_string|&quot;Could not process reset of non-existent host in Node Manager&quot;
)paren
suffix:semicolon
r_goto
id|done_reset_host
suffix:semicolon
)brace
id|schedule_task
c_func
(paren
op_amp
id|hi-&gt;task
)paren
suffix:semicolon
id|done_reset_host
suffix:colon
id|spin_unlock_irqrestore
(paren
op_amp
id|host_info_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|nodemgr_remove_host
r_static
r_void
id|nodemgr_remove_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|host_info
op_star
id|hi
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|node_entry
op_star
id|ne
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Make sure we have no active scans */
id|flush_scheduled_tasks
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* First remove all node entries for this host */
id|write_lock_irqsave
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|lh
comma
op_amp
id|node_list
)paren
(brace
id|ne
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|node_entry
comma
id|list
)paren
suffix:semicolon
multiline_comment|/* Only checking this host */
r_if
c_cond
(paren
id|ne-&gt;host
op_ne
id|host
)paren
r_continue
suffix:semicolon
id|nodemgr_remove_node
c_func
(paren
id|ne
)paren
suffix:semicolon
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|node_lock
comma
id|flags
)paren
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|host_info_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|lh
comma
op_amp
id|host_info_list
)paren
(brace
r_struct
id|host_info
op_star
id|myhi
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|host_info
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|myhi-&gt;host
op_eq
id|host
)paren
(brace
id|hi
op_assign
id|myhi
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|hi
op_eq
l_int|NULL
)paren
(brace
id|HPSB_ERR
(paren
l_string|&quot;Could not remove non-existent host in Node Manager&quot;
)paren
suffix:semicolon
r_goto
id|done_remove_host
suffix:semicolon
)brace
id|list_del
c_func
(paren
op_amp
id|hi-&gt;list
)paren
suffix:semicolon
id|kfree
(paren
id|hi
)paren
suffix:semicolon
id|done_remove_host
suffix:colon
id|spin_unlock_irqrestore
(paren
op_amp
id|host_info_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|nodemgr_ops
r_static
r_struct
id|hpsb_highlevel_ops
id|nodemgr_ops
op_assign
(brace
id|add_host
suffix:colon
id|nodemgr_add_host
comma
id|host_reset
suffix:colon
id|nodemgr_host_reset
comma
id|remove_host
suffix:colon
id|nodemgr_remove_host
comma
)brace
suffix:semicolon
DECL|variable|hl
r_static
r_struct
id|hpsb_highlevel
op_star
id|hl
suffix:semicolon
DECL|function|init_ieee1394_nodemgr
r_void
id|init_ieee1394_nodemgr
c_func
(paren
r_void
)paren
(brace
id|hl
op_assign
id|hpsb_register_highlevel
c_func
(paren
l_string|&quot;Node manager&quot;
comma
op_amp
id|nodemgr_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hl
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;Out of memory during ieee1394 initialization&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|cleanup_ieee1394_nodemgr
r_void
id|cleanup_ieee1394_nodemgr
c_func
(paren
r_void
)paren
(brace
id|hpsb_unregister_highlevel
c_func
(paren
id|hl
)paren
suffix:semicolon
)brace
eof
