multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1992 - 1997,2001 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN2_SLOTNUM_H
DECL|macro|_ASM_IA64_SN_SN2_SLOTNUM_H
mdefine_line|#define _ASM_IA64_SN_SN2_SLOTNUM_H
DECL|macro|SLOTNUM_MAXLENGTH
mdefine_line|#define SLOTNUM_MAXLENGTH&t;16
multiline_comment|/*&n; * This file defines IO widget to slot/device assignments.&n; */
multiline_comment|/* This determines module to pnode mapping. */
DECL|macro|NODESLOTS_PER_MODULE
mdefine_line|#define NODESLOTS_PER_MODULE&t;&t;1
DECL|macro|NODESLOTS_PER_MODULE_SHFT
mdefine_line|#define NODESLOTS_PER_MODULE_SHFT&t;1
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
macro_line|#endif /* _ASM_IA64_SN_SN2_SLOTNUM_H */
eof
