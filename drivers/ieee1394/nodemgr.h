multiline_comment|/*&n; * Copyright (C) 2000&t;Andreas E. Bombe&n; *               2001&t;Ben Collins &lt;bcollins@debian.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ifndef _IEEE1394_NODEMGR_H
DECL|macro|_IEEE1394_NODEMGR_H
mdefine_line|#define _IEEE1394_NODEMGR_H
DECL|macro|CONFIG_ROM_BUS_INFO_LENGTH
mdefine_line|#define CONFIG_ROM_BUS_INFO_LENGTH(q)&t;&t;((q) &gt;&gt; 24)
DECL|macro|CONFIG_ROM_BUS_CRC_LENGTH
mdefine_line|#define CONFIG_ROM_BUS_CRC_LENGTH(q)&t;&t;(((q) &gt;&gt; 16) &amp; 0xff)
DECL|macro|CONFIG_ROM_BUS_CRC
mdefine_line|#define CONFIG_ROM_BUS_CRC(q)&t;&t;&t;((q) &amp; 0xffff)
DECL|macro|CONFIG_ROM_ROOT_LENGTH
mdefine_line|#define CONFIG_ROM_ROOT_LENGTH(q)&t;&t;((q) &gt;&gt; 16)
DECL|macro|CONFIG_ROM_ROOT_CRC
mdefine_line|#define CONFIG_ROM_ROOT_CRC(q)&t;&t;&t;((q) &amp; 0xffff)
DECL|macro|CONFIG_ROM_DIRECTORY_LENGTH
mdefine_line|#define CONFIG_ROM_DIRECTORY_LENGTH(q)&t;&t;((q) &gt;&gt; 16)
DECL|macro|CONFIG_ROM_DIRECTORY_CRC
mdefine_line|#define CONFIG_ROM_DIRECTORY_CRC(q)&t;&t;((q) &amp; 0xffff)
DECL|macro|CONFIG_ROM_LEAF_LENGTH
mdefine_line|#define CONFIG_ROM_LEAF_LENGTH(q)&t;&t;((q) &gt;&gt; 16)
DECL|macro|CONFIG_ROM_LEAF_CRC
mdefine_line|#define CONFIG_ROM_LEAF_CRC(q)&t;&t;&t;((q) &amp; 0xffff)
DECL|macro|CONFIG_ROM_DESCRIPTOR_TYPE
mdefine_line|#define CONFIG_ROM_DESCRIPTOR_TYPE(q)&t;&t;((q) &gt;&gt; 24)
DECL|macro|CONFIG_ROM_DESCRIPTOR_SPECIFIER_ID
mdefine_line|#define CONFIG_ROM_DESCRIPTOR_SPECIFIER_ID(q)&t;((q) &amp; 0xffffff)
DECL|macro|CONFIG_ROM_DESCRIPTOR_WIDTH
mdefine_line|#define CONFIG_ROM_DESCRIPTOR_WIDTH(q)&t;&t;((q) &gt;&gt; 28)
DECL|macro|CONFIG_ROM_DESCRIPTOR_CHAR_SET
mdefine_line|#define CONFIG_ROM_DESCRIPTOR_CHAR_SET(q)&t;(((q) &gt;&gt; 16) &amp; 0xfff)
DECL|macro|CONFIG_ROM_DESCRIPTOR_LANG
mdefine_line|#define CONFIG_ROM_DESCRIPTOR_LANG(q)&t;&t;((q) &amp; 0xffff)
DECL|macro|CONFIG_ROM_KEY_ID_MASK
mdefine_line|#define CONFIG_ROM_KEY_ID_MASK&t;&t;&t;0x3f
DECL|macro|CONFIG_ROM_KEY_TYPE_MASK
mdefine_line|#define CONFIG_ROM_KEY_TYPE_MASK&t;&t;0xc0
DECL|macro|CONFIG_ROM_KEY_TYPE_IMMEDIATE
mdefine_line|#define CONFIG_ROM_KEY_TYPE_IMMEDIATE&t;&t;0x00
DECL|macro|CONFIG_ROM_KEY_TYPE_OFFSET
mdefine_line|#define CONFIG_ROM_KEY_TYPE_OFFSET&t;&t;0x40
DECL|macro|CONFIG_ROM_KEY_TYPE_LEAF
mdefine_line|#define CONFIG_ROM_KEY_TYPE_LEAF&t;&t;0x80
DECL|macro|CONFIG_ROM_KEY_TYPE_DIRECTORY
mdefine_line|#define CONFIG_ROM_KEY_TYPE_DIRECTORY&t;&t;0xc0
DECL|macro|CONFIG_ROM_KEY
mdefine_line|#define CONFIG_ROM_KEY(q)&t;&t;&t;((q) &gt;&gt; 24)
DECL|macro|CONFIG_ROM_VALUE
mdefine_line|#define CONFIG_ROM_VALUE(q)&t;&t;&t;((q) &amp; 0xffffff)
DECL|macro|CONFIG_ROM_VENDOR_ID
mdefine_line|#define CONFIG_ROM_VENDOR_ID&t;&t;&t;0x03
DECL|macro|CONFIG_ROM_MODEL_ID
mdefine_line|#define CONFIG_ROM_MODEL_ID&t;&t;&t;0x17
DECL|macro|CONFIG_ROM_NODE_CAPABILITES
mdefine_line|#define CONFIG_ROM_NODE_CAPABILITES&t;&t;0x0C
DECL|macro|CONFIG_ROM_UNIT_DIRECTORY
mdefine_line|#define CONFIG_ROM_UNIT_DIRECTORY&t;&t;0xd1
DECL|macro|CONFIG_ROM_SPECIFIER_ID
mdefine_line|#define CONFIG_ROM_SPECIFIER_ID&t;&t;&t;0x12 
DECL|macro|CONFIG_ROM_UNIT_SW_VERSION
mdefine_line|#define CONFIG_ROM_UNIT_SW_VERSION&t;&t;0x13
DECL|macro|CONFIG_ROM_DESCRIPTOR_LEAF
mdefine_line|#define CONFIG_ROM_DESCRIPTOR_LEAF&t;&t;0x81
DECL|macro|CONFIG_ROM_DESCRIPTOR_DIRECTORY
mdefine_line|#define CONFIG_ROM_DESCRIPTOR_DIRECTORY&t;&t;0xc1
multiline_comment|/* &squot;1&squot; &squot;3&squot; &squot;9&squot; &squot;4&squot; in ASCII */
DECL|macro|IEEE1394_BUSID_MAGIC
mdefine_line|#define IEEE1394_BUSID_MAGIC&t;0x31333934
multiline_comment|/* This is the start of a Node entry structure. It should be a stable API&n; * for which to gather info from the Node Manager about devices attached&n; * to the bus.  */
DECL|struct|bus_options
r_struct
id|bus_options
(brace
DECL|member|irmc
id|u8
id|irmc
suffix:semicolon
multiline_comment|/* Iso Resource Manager Capable */
DECL|member|cmc
id|u8
id|cmc
suffix:semicolon
multiline_comment|/* Cycle Master Capable */
DECL|member|isc
id|u8
id|isc
suffix:semicolon
multiline_comment|/* Iso Capable */
DECL|member|bmc
id|u8
id|bmc
suffix:semicolon
multiline_comment|/* Bus Master Capable */
DECL|member|pmc
id|u8
id|pmc
suffix:semicolon
multiline_comment|/* Power Manager Capable (PNP spec) */
DECL|member|cyc_clk_acc
id|u8
id|cyc_clk_acc
suffix:semicolon
multiline_comment|/* Cycle clock accuracy */
DECL|member|generation
id|u8
id|generation
suffix:semicolon
multiline_comment|/* Incremented when configrom changes */
DECL|member|lnkspd
id|u8
id|lnkspd
suffix:semicolon
multiline_comment|/* Link speed */
DECL|member|max_rec
id|u16
id|max_rec
suffix:semicolon
multiline_comment|/* Maximum packet size node can receive */
)brace
suffix:semicolon
DECL|macro|UNIT_DIRECTORY_VENDOR_ID
mdefine_line|#define UNIT_DIRECTORY_VENDOR_ID&t;0x01
DECL|macro|UNIT_DIRECTORY_MODEL_ID
mdefine_line|#define UNIT_DIRECTORY_MODEL_ID&t;&t;0x02
DECL|macro|UNIT_DIRECTORY_SPECIFIER_ID
mdefine_line|#define UNIT_DIRECTORY_SPECIFIER_ID&t;0x04
DECL|macro|UNIT_DIRECTORY_VERSION
mdefine_line|#define UNIT_DIRECTORY_VERSION&t;&t;0x08
DECL|macro|UNIT_DIRECTORY_VENDOR_TEXT
mdefine_line|#define UNIT_DIRECTORY_VENDOR_TEXT&t;0x10
DECL|macro|UNIT_DIRECTORY_MODEL_TEXT
mdefine_line|#define UNIT_DIRECTORY_MODEL_TEXT&t;0x20
multiline_comment|/*&n; * A unit directory corresponds to a protocol supported by the&n; * node. If a node supports eg. IP/1394 and AV/C, its config rom has a&n; * unit directory for each of these protocols.&n; * &n; * Unit directories appear on two types of lists: for each node we&n; * maintain a list of the unit directories found in its config rom and&n; * for each driver we maintain a list of the unit directories&n; * (ie. devices) the driver manages.&n; */
DECL|struct|unit_directory
r_struct
id|unit_directory
(brace
DECL|member|ne
r_struct
id|node_entry
op_star
id|ne
suffix:semicolon
multiline_comment|/* The node which this directory belongs to */
DECL|member|address
id|octlet_t
id|address
suffix:semicolon
multiline_comment|/* Address of the unit directory on the node */
DECL|member|flags
id|u8
id|flags
suffix:semicolon
multiline_comment|/* Indicates which entries were read */
DECL|member|vendor_id
id|quadlet_t
id|vendor_id
suffix:semicolon
DECL|member|vendor_name
r_const
r_char
op_star
id|vendor_name
suffix:semicolon
DECL|member|vendor_name_size
r_int
id|vendor_name_size
suffix:semicolon
DECL|member|model_id
id|quadlet_t
id|model_id
suffix:semicolon
DECL|member|model_name
r_const
r_char
op_star
id|model_name
suffix:semicolon
DECL|member|model_name_size
r_int
id|model_name_size
suffix:semicolon
DECL|member|specifier_id
id|quadlet_t
id|specifier_id
suffix:semicolon
DECL|member|version
id|quadlet_t
id|version
suffix:semicolon
DECL|member|driver
r_struct
id|hpsb_protocol_driver
op_star
id|driver
suffix:semicolon
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
multiline_comment|/* For linking the nodes managed by the driver, or unmanaged nodes */
DECL|member|driver_list
r_struct
id|list_head
id|driver_list
suffix:semicolon
multiline_comment|/* For linking directories belonging to a node */
DECL|member|node_list
r_struct
id|list_head
id|node_list
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* Number of quadlets */
DECL|member|quadlets
id|quadlet_t
id|quadlets
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|node_entry
r_struct
id|node_entry
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|guid
id|u64
id|guid
suffix:semicolon
multiline_comment|/* GUID of this node */
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
multiline_comment|/* Host this node is attached to */
DECL|member|nodeid
id|nodeid_t
id|nodeid
suffix:semicolon
multiline_comment|/* NodeID */
DECL|member|busopt
r_struct
id|bus_options
id|busopt
suffix:semicolon
multiline_comment|/* Bus Options */
DECL|member|generation
id|atomic_t
id|generation
suffix:semicolon
multiline_comment|/* Synced with hpsb generation */
multiline_comment|/* The following is read from the config rom */
DECL|member|vendor_id
id|u32
id|vendor_id
suffix:semicolon
DECL|member|capabilities
id|u32
id|capabilities
suffix:semicolon
DECL|member|unit_directories
r_struct
id|list_head
id|unit_directories
suffix:semicolon
DECL|member|vendor_name
r_const
r_char
op_star
id|vendor_name
suffix:semicolon
DECL|member|quadlets
id|quadlet_t
id|quadlets
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|hpsb_node_entry_valid
r_static
r_inline
r_int
id|hpsb_node_entry_valid
c_func
(paren
r_struct
id|node_entry
op_star
id|ne
)paren
(brace
r_return
id|atomic_read
c_func
(paren
op_amp
id|ne-&gt;generation
)paren
op_eq
id|get_hpsb_generation
c_func
(paren
id|ne-&gt;host
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns a node entry (which has its reference count incremented) or NULL if&n; * the GUID in question is not known.  Getting a valid entry does not mean that&n; * the node with this GUID is currently accessible (might be powered down).&n; */
r_struct
id|node_entry
op_star
id|hpsb_guid_get_entry
c_func
(paren
id|u64
id|guid
)paren
suffix:semicolon
multiline_comment|/* Same as above, but use the nodeid to get an node entry. This is not&n; * fool-proof by itself, since the nodeid can change.  */
r_struct
id|node_entry
op_star
id|hpsb_nodeid_get_entry
c_func
(paren
id|nodeid_t
id|nodeid
)paren
suffix:semicolon
multiline_comment|/*&n; * If the entry refers to a local host, this function will return the pointer&n; * to the hpsb_host structure.  It will return NULL otherwise.  Once you have&n; * established it is a local host, you can use that knowledge from then on (the&n; * GUID won&squot;t wander to an external node).  */
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
suffix:semicolon
multiline_comment|/*&n; * This will fill in the given, pre-initialised hpsb_packet with the current&n; * information from the node entry (host, node ID, generation number).  It will&n; * return false if the node owning the GUID is not accessible (and not modify the &n; * hpsb_packet) and return true otherwise.&n; *&n; * Note that packet sending may still fail in hpsb_send_packet if a bus reset&n; * happens while you are trying to set up the packet (due to obsolete generation&n; * number).  It will at least reliably fail so that you don&squot;t accidentally and&n; * unknowingly send your packet to the wrong node.&n; */
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
suffix:semicolon
r_void
id|init_ieee1394_nodemgr
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cleanup_ieee1394_nodemgr
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _IEEE1394_NODEMGR_H */
eof
