multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2001 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_XTALK_XTALKADDRS_H
DECL|macro|_ASM_SN_XTALK_XTALKADDRS_H
mdefine_line|#define _ASM_SN_XTALK_XTALKADDRS_H
multiline_comment|/*&n; * CrossTalk to SN0 Hub addressing support&n; *&n; * This file defines the mapping conventions used by the Hub&squot;s&n; * I/O interface when it receives a read or write request from &n; * a CrossTalk widget.  &n; *&n; * Format for non-Memory accesses:&n; *&n; *  +--------------+------------------------------------------------+&n; *  | 0  | XXXXX   |        SN0Addr                                |&n; *  +----+---------+------------------------------------------------+&n; *    47  46     40 39                                             0&n; *&t;bit 47 indicates Memory (0)&n; *&t;bits 46..40 are unused&n; *&t;bits 39..0 hold the memory address&n; *&t;&t;&t;(bits 39..31 hold the nodeID in N mode&n; *&t;&t;&t; bits 39..32 hold the nodeID in M mode&n; * By design, this looks exactly like a 0-extended SN0 Address, so&n; * we don&squot;t need to do any conversions.&n; *&n; *&n; *&n; * Format for non-Memory accesses:&n; *&n; *  +--------------+------+---------+------+--+---------------------+&n; *  | 1  | DstNode | XXXX | BigW=0  | SW=1 | 1|   Addr              |&n; *  +----+---------+------+---------+------+--+---------------------+&n; *    47  46     38 37  31 30     28 27  24 23 22                  0&n; *&n; *&t;bit 47 indicates IO (1)&n; *      bits 46..38 hold the destination node ID&n; *      bits 37..31 are unused&n; *      bits 30..28 hold the big window being addressed&n; *      bits 27..24 hold the small window being addressed&n; *                  0 always refers to the xbow&n; *                  1 always refers to the hub itself&n; *      bit 23 indicates local (0) or remote (1)&n; *             no accessing checks are done if this bit is 0&n; *      bits 22..0 hold the register address&n; *                 bits 22..21 determine which section of the hub&n; *                              00 -&gt; PI&n; *                              01 -&gt; MD&n; *                              10 -&gt; IO&n; *                              11 -&gt; NI&n; * This looks very much like a REMOTE_HUB access, except the nodeID&n; * is in a different place, and the highest xtalk bit is set.&n; */
multiline_comment|/* Hub-specific xtalk definitions */
DECL|macro|HX_MEM_BIT
mdefine_line|#define HX_MEM_BIT&t;&t;0L&t;/* Hub&squot;s idea of xtalk memory access */
DECL|macro|HX_IO_BIT
mdefine_line|#define HX_IO_BIT&t;&t;1L&t;/* Hub&squot;s idea of xtalk register access */
DECL|macro|HX_ACCTYPE_SHIFT
mdefine_line|#define HX_ACCTYPE_SHIFT&t;47
DECL|macro|HX_NODE_SHIFT
mdefine_line|#define HX_NODE_SHIFT&t;&t;39
DECL|macro|HX_BIGWIN_SHIFT
mdefine_line|#define HX_BIGWIN_SHIFT&t;&t;28
DECL|macro|HX_SWIN_SHIFT
mdefine_line|#define HX_SWIN_SHIFT&t;&t;23
DECL|macro|HX_LOCACC
mdefine_line|#define HX_LOCACC&t;&t;0L&t;/* local access */
DECL|macro|HX_REMACC
mdefine_line|#define HX_REMACC&t;&t;1L&t;/* remote access */
DECL|macro|HX_ACCESS_SHIFT
mdefine_line|#define HX_ACCESS_SHIFT&t;&t;23
multiline_comment|/*&n; * Pre-calculate the fixed portion of a crosstalk address that maps&n; * to local register space on a hub.&n; */
DECL|macro|HX_REG_BASE
mdefine_line|#define HX_REG_BASE&t;&t;((HX_IO_BIT&lt;&lt;HX_ACCTYPE_SHIFT) + &bslash;&n;&t;&t;&t;&t;(0L&lt;&lt;HX_BIGWIN_SHIFT) + &bslash;&n;&t;&t;&t;&t;(1L&lt;&lt;HX_SWIN_SHIFT) + IALIAS_SIZE + &bslash;&n;&t;&t;&t;&t;(HX_REMACC&lt;&lt;HX_ACCESS_SHIFT))
multiline_comment|/* &n; * Return a crosstalk address which a widget can use to access a&n; * designated register on a designated node.&n; */
DECL|macro|HUBREG_AS_XTALKADDR
mdefine_line|#define HUBREG_AS_XTALKADDR(nasid, regaddr) &bslash;&n;&t;((iopaddr_t)(HX_REG_BASE + (((long)nasid)&lt;&lt;HX_NODE_SHIFT) + ((long)regaddr)))
macro_line|#if TBD
macro_line|#assert sizeof(iopaddr_t) == 8
macro_line|#endif /* TBD */
multiline_comment|/*&n; * Get widget part number, given node id and widget id. &n; * Always do a 32-bit read, because some widgets, e.g., Bridge, require so.&n; * Widget ID is at offset 0 for 64-bit access.  Add 4 to get lower 32 bits&n; * in big endian mode. &n; * XXX Double check this with Hub, Xbow, Bridge and other hardware folks.&n; */
DECL|macro|XWIDGET_ID_READ
mdefine_line|#define XWIDGET_ID_READ(nasid, widget) &bslash;&n;        (widgetreg_t)(*(volatile uint32_t *)(NODE_SWIN_BASE(nasid, widget) + WIDGET_ID))
macro_line|#endif /* _ASM_SN_XTALK_XTALKADDRS_H */
eof
