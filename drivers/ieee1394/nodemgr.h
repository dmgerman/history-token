multiline_comment|/*&n; * Copyright (C) 2000&t;Andreas E. Bombe&n; *               2001&t;Ben Collins &lt;bcollins@debian.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ifndef _IEEE1394_NODEMGR_H
DECL|macro|_IEEE1394_NODEMGR_H
mdefine_line|#define _IEEE1394_NODEMGR_H
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;csr1212.h&quot;
macro_line|#include &quot;ieee1394_core.h&quot;
macro_line|#include &quot;ieee1394_hotplug.h&quot;
multiline_comment|/* &squot;1&squot; &squot;3&squot; &squot;9&squot; &squot;4&squot; in ASCII */
DECL|macro|IEEE1394_BUSID_MAGIC
mdefine_line|#define IEEE1394_BUSID_MAGIC&t;__constant_cpu_to_be32(0x31333934)
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
DECL|member|max_rom
id|u8
id|max_rom
suffix:semicolon
multiline_comment|/* Maximum block read supported in the CSR */
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
mdefine_line|#define UNIT_DIRECTORY_VENDOR_ID&t;&t;0x01
DECL|macro|UNIT_DIRECTORY_MODEL_ID
mdefine_line|#define UNIT_DIRECTORY_MODEL_ID&t;&t;&t;0x02
DECL|macro|UNIT_DIRECTORY_SPECIFIER_ID
mdefine_line|#define UNIT_DIRECTORY_SPECIFIER_ID&t;&t;0x04
DECL|macro|UNIT_DIRECTORY_VERSION
mdefine_line|#define UNIT_DIRECTORY_VERSION&t;&t;&t;0x08
DECL|macro|UNIT_DIRECTORY_HAS_LUN_DIRECTORY
mdefine_line|#define UNIT_DIRECTORY_HAS_LUN_DIRECTORY&t;0x10
DECL|macro|UNIT_DIRECTORY_LUN_DIRECTORY
mdefine_line|#define UNIT_DIRECTORY_LUN_DIRECTORY&t;&t;0x20
multiline_comment|/*&n; * A unit directory corresponds to a protocol supported by the&n; * node. If a node supports eg. IP/1394 and AV/C, its config rom has a&n; * unit directory for each of these protocols.&n; */
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
DECL|member|vendor_name_kv
r_struct
id|csr1212_keyval
op_star
id|vendor_name_kv
suffix:semicolon
DECL|member|vendor_oui
r_const
r_char
op_star
id|vendor_oui
suffix:semicolon
DECL|member|model_id
id|quadlet_t
id|model_id
suffix:semicolon
DECL|member|model_name_kv
r_struct
id|csr1212_keyval
op_star
id|model_name_kv
suffix:semicolon
DECL|member|specifier_id
id|quadlet_t
id|specifier_id
suffix:semicolon
DECL|member|version
id|quadlet_t
id|version
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|ignore_driver
r_int
id|ignore_driver
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* Number of quadlets */
DECL|member|device
r_struct
id|device
id|device
suffix:semicolon
DECL|member|class_dev
r_struct
id|class_device
id|class_dev
suffix:semicolon
DECL|member|ud_kv
r_struct
id|csr1212_keyval
op_star
id|ud_kv
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|node_entry
r_struct
id|node_entry
(brace
DECL|member|guid
id|u64
id|guid
suffix:semicolon
multiline_comment|/* GUID of this node */
DECL|member|guid_vendor_id
id|u32
id|guid_vendor_id
suffix:semicolon
multiline_comment|/* Top 24bits of guid */
DECL|member|guid_vendor_oui
r_const
r_char
op_star
id|guid_vendor_oui
suffix:semicolon
multiline_comment|/* OUI name of guid vendor id */
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
DECL|member|needs_probe
r_int
id|needs_probe
suffix:semicolon
DECL|member|generation
r_int
r_int
id|generation
suffix:semicolon
multiline_comment|/* Synced with hpsb generation */
multiline_comment|/* The following is read from the config rom */
DECL|member|vendor_id
id|u32
id|vendor_id
suffix:semicolon
DECL|member|vendor_name_kv
r_struct
id|csr1212_keyval
op_star
id|vendor_name_kv
suffix:semicolon
DECL|member|vendor_oui
r_const
r_char
op_star
id|vendor_oui
suffix:semicolon
DECL|member|capabilities
id|u32
id|capabilities
suffix:semicolon
DECL|member|tpool
r_struct
id|hpsb_tlabel_pool
op_star
id|tpool
suffix:semicolon
DECL|member|device
r_struct
id|device
id|device
suffix:semicolon
DECL|member|class_dev
r_struct
id|class_device
id|class_dev
suffix:semicolon
multiline_comment|/* Means this node is not attached anymore */
DECL|member|in_limbo
r_int
id|in_limbo
suffix:semicolon
DECL|member|csr
r_struct
id|csr1212_csr
op_star
id|csr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hpsb_protocol_driver
r_struct
id|hpsb_protocol_driver
(brace
multiline_comment|/* The name of the driver, e.g. SBP2 or IP1394 */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/*&n;&t; * The device id table describing the protocols and/or devices&n;&t; * supported by this driver.  This is used by the nodemgr to&n;&t; * decide if a driver could support a given node, but the&n;&t; * probe function below can implement further protocol&n;&t; * dependent or vendor dependent checking.&n;&t; */
DECL|member|id_table
r_struct
id|ieee1394_device_id
op_star
id|id_table
suffix:semicolon
multiline_comment|/*&n;&t; * The update function is called when the node has just&n;&t; * survived a bus reset, i.e. it is still present on the bus.&n;&t; * However, it may be necessary to reestablish the connection&n;&t; * or login into the node again, depending on the protocol. If the&n;&t; * probe fails (returns non-zero), we unbind the driver from this&n;&t; * device.&n;&t; */
DECL|member|update
r_int
(paren
op_star
id|update
)paren
(paren
r_struct
id|unit_directory
op_star
id|ud
)paren
suffix:semicolon
multiline_comment|/* Our LDM structure */
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
r_int
id|hpsb_register_protocol
c_func
(paren
r_struct
id|hpsb_protocol_driver
op_star
id|driver
)paren
suffix:semicolon
r_void
id|hpsb_unregister_protocol
c_func
(paren
r_struct
id|hpsb_protocol_driver
op_star
id|driver
)paren
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
id|ne-&gt;generation
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
r_struct
id|hpsb_host
op_star
id|host
comma
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
multiline_comment|/*&n; * This will fill in the given, pre-initialised hpsb_packet with the current&n; * information from the node entry (host, node ID, generation number).  It will&n; * return false if the node owning the GUID is not accessible (and not modify the&n; * hpsb_packet) and return true otherwise.&n; *&n; * Note that packet sending may still fail in hpsb_send_packet if a bus reset&n; * happens while you are trying to set up the packet (due to obsolete generation&n; * number).  It will at least reliably fail so that you don&squot;t accidentally and&n; * unknowingly send your packet to the wrong node.&n; */
r_void
id|hpsb_node_fill_packet
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
r_int
id|hpsb_node_read
c_func
(paren
r_struct
id|node_entry
op_star
id|ne
comma
id|u64
id|addr
comma
id|quadlet_t
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
r_int
id|hpsb_node_write
c_func
(paren
r_struct
id|node_entry
op_star
id|ne
comma
id|u64
id|addr
comma
id|quadlet_t
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
r_int
id|hpsb_node_lock
c_func
(paren
r_struct
id|node_entry
op_star
id|ne
comma
id|u64
id|addr
comma
r_int
id|extcode
comma
id|quadlet_t
op_star
id|data
comma
id|quadlet_t
id|arg
)paren
suffix:semicolon
multiline_comment|/* Iterate the hosts, calling a given function with supplied data for each&n; * host. */
r_int
id|nodemgr_for_each_host
c_func
(paren
r_void
op_star
id|__data
comma
r_int
(paren
op_star
id|cb
)paren
(paren
r_struct
id|hpsb_host
op_star
comma
r_void
op_star
)paren
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
multiline_comment|/* The template for a host device */
r_extern
r_struct
id|device
id|nodemgr_dev_template_host
suffix:semicolon
multiline_comment|/* Bus attributes we export */
r_extern
r_struct
id|bus_attribute
op_star
r_const
id|fw_bus_attrs
(braket
)braket
suffix:semicolon
macro_line|#endif /* _IEEE1394_NODEMGR_H */
eof
