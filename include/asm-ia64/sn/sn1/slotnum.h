multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_SN1_SLOTNUM_H
DECL|macro|_ASM_SN_SN1_SLOTNUM_H
mdefine_line|#define _ASM_SN_SN1_SLOTNUM_H
DECL|macro|SLOTNUM_MAXLENGTH
mdefine_line|#define SLOTNUM_MAXLENGTH&t;16
multiline_comment|/*&n; * This file attempts to define a slot number space across all slots.&n; *&n; *&t;Node slots&n; *&t;Router slots&n; *&t;Crosstalk slots&n; *&n; *&t;Other slots are children of their parent crosstalk slot:&n; *&t;&t;PCI slots&n; *&t;&t;VME slots&n; *&n; *&t;The PCI class has been added since the XBridge ASIC on SN-MIPS&n; *&t;has built-in PCI bridges (2). On IBricks, widget E &amp; F serve&n; *&t;PCI busses, and on PBricks all widgets serve as PCI busses&n; *&t;with the use of the super-bridge mode of the XBridge ASIC.&n; */
DECL|macro|SLOTNUM_NODE_CLASS
mdefine_line|#define SLOTNUM_NODE_CLASS&t;0x00&t;/* Node   */
DECL|macro|SLOTNUM_ROUTER_CLASS
mdefine_line|#define SLOTNUM_ROUTER_CLASS&t;0x10&t;/* Router */
DECL|macro|SLOTNUM_XTALK_CLASS
mdefine_line|#define SLOTNUM_XTALK_CLASS&t;0x20&t;/* Xtalk  */
DECL|macro|SLOTNUM_MIDPLANE_CLASS
mdefine_line|#define SLOTNUM_MIDPLANE_CLASS&t;0x30&t;/* Midplane */
DECL|macro|SLOTNUM_XBOW_CLASS
mdefine_line|#define SLOTNUM_XBOW_CLASS&t;0x40&t;/* Xbow  */
DECL|macro|SLOTNUM_KNODE_CLASS
mdefine_line|#define SLOTNUM_KNODE_CLASS&t;0x50&t;/* Kego node */
DECL|macro|SLOTNUM_PCI_CLASS
mdefine_line|#define SLOTNUM_PCI_CLASS&t;0x60&t;/* PCI widgets on XBridge */
DECL|macro|SLOTNUM_INVALID_CLASS
mdefine_line|#define SLOTNUM_INVALID_CLASS&t;0xf0&t;/* Invalid */
DECL|macro|SLOTNUM_CLASS_MASK
mdefine_line|#define SLOTNUM_CLASS_MASK&t;0xf0
DECL|macro|SLOTNUM_SLOT_MASK
mdefine_line|#define SLOTNUM_SLOT_MASK&t;0x0f
DECL|macro|SLOTNUM_GETCLASS
mdefine_line|#define SLOTNUM_GETCLASS(_sn)&t;((_sn) &amp; SLOTNUM_CLASS_MASK)
DECL|macro|SLOTNUM_GETSLOT
mdefine_line|#define SLOTNUM_GETSLOT(_sn)&t;((_sn) &amp; SLOTNUM_SLOT_MASK)
multiline_comment|/* This determines module to pnode mapping. */
multiline_comment|/* NODESLOTS_PER_MODULE has changed from 4 to 6&n; * to support the 12P 4IO configuration. This change&n; * helps in minimum  number of changes to code which&n; * depend on the number of node boards within a module.&n; */
DECL|macro|NODESLOTS_PER_MODULE
mdefine_line|#define NODESLOTS_PER_MODULE&t;&t;6
DECL|macro|NODESLOTS_PER_MODULE_SHFT
mdefine_line|#define NODESLOTS_PER_MODULE_SHFT&t;2
DECL|macro|HIGHEST_I2C_VISIBLE_NODESLOT
mdefine_line|#define HIGHEST_I2C_VISIBLE_NODESLOT&t;4
DECL|macro|RTRSLOTS_PER_MODULE
mdefine_line|#define&t;RTRSLOTS_PER_MODULE&t;&t;2
macro_line|#if __KERNEL__
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
r_extern
id|slotid_t
id|xbwidget_to_xtslot
c_func
(paren
r_int
id|crossbow
comma
r_int
id|widget
)paren
suffix:semicolon
r_extern
id|slotid_t
id|hub_slotbits_to_slot
c_func
(paren
id|slotid_t
id|slotbits
)paren
suffix:semicolon
r_extern
id|slotid_t
id|hub_slot_to_crossbow
c_func
(paren
id|slotid_t
id|hub_slot
)paren
suffix:semicolon
r_extern
id|slotid_t
id|router_slotbits_to_slot
c_func
(paren
id|slotid_t
id|slotbits
)paren
suffix:semicolon
r_extern
id|slotid_t
id|get_node_slotid
c_func
(paren
id|nasid_t
id|nasid
)paren
suffix:semicolon
r_extern
id|slotid_t
id|get_my_slotid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|slotid_t
id|get_node_crossbow
c_func
(paren
id|nasid_t
)paren
suffix:semicolon
r_extern
id|xwidgetnum_t
id|hub_slot_to_widget
c_func
(paren
id|slotid_t
)paren
suffix:semicolon
r_extern
r_void
id|get_slotname
c_func
(paren
id|slotid_t
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|get_my_slotname
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
id|slotid_t
id|get_widget_slotnum
c_func
(paren
r_int
id|xbow
comma
r_int
id|widget
)paren
suffix:semicolon
r_extern
r_void
id|get_widget_slotname
c_func
(paren
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|router_slotbits_to_slotname
c_func
(paren
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
id|slotid_t
id|meta_router_slotbits_to_slot
c_func
(paren
id|slotid_t
)paren
suffix:semicolon
r_extern
id|slotid_t
id|hub_slot_get
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|node_can_talk_to_elsc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|slot_to_widget
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|macro|MAX_IO_SLOT_NUM
mdefine_line|#define MAX_IO_SLOT_NUM&t;&t;12
DECL|macro|MAX_NODE_SLOT_NUM
mdefine_line|#define MAX_NODE_SLOT_NUM&t;4
DECL|macro|MAX_ROUTER_SLOTNUM
mdefine_line|#define MAX_ROUTER_SLOTNUM&t;2
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_SN_SN1_SLOTNUM_H */
eof
