multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * xtalk.h -- platform-independent crosstalk interface, derived from&n; * IRIX &lt;sys/PCI/bridge.h&gt;, revision 1.38.&n; *&n; * Copyright (C) 1995 - 1997, 1999 Silcon Graphics, Inc.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_XTALK_XTALK_H
DECL|macro|_ASM_XTALK_XTALK_H
mdefine_line|#define _ASM_XTALK_XTALK_H
macro_line|#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
multiline_comment|/*&n; * User-level device driver visible types&n; */
DECL|typedef|xwidgetnum_t
r_typedef
r_char
id|xwidgetnum_t
suffix:semicolon
multiline_comment|/* xtalk widget number  (0..15) */
DECL|macro|XWIDGET_NONE
mdefine_line|#define XWIDGET_NONE&t;&t;-1
DECL|typedef|xwidget_part_num_t
r_typedef
r_int
id|xwidget_part_num_t
suffix:semicolon
multiline_comment|/* xtalk widget part number */
DECL|macro|XWIDGET_PART_NUM_NONE
mdefine_line|#define XWIDGET_PART_NUM_NONE&t;-1
DECL|typedef|xwidget_rev_num_t
r_typedef
r_int
id|xwidget_rev_num_t
suffix:semicolon
multiline_comment|/* xtalk widget revision number */
DECL|macro|XWIDGET_REV_NUM_NONE
mdefine_line|#define XWIDGET_REV_NUM_NONE&t;-1
DECL|typedef|xwidget_mfg_num_t
r_typedef
r_int
id|xwidget_mfg_num_t
suffix:semicolon
multiline_comment|/* xtalk widget manufacturing ID */
DECL|macro|XWIDGET_MFG_NUM_NONE
mdefine_line|#define XWIDGET_MFG_NUM_NONE&t;-1
DECL|typedef|xtalk_piomap_t
r_typedef
r_struct
id|xtalk_piomap_s
op_star
id|xtalk_piomap_t
suffix:semicolon
multiline_comment|/* It is often convenient to fold the XIO target port&n; * number into the XIO address.&n; */
DECL|macro|XIO_NOWHERE
mdefine_line|#define&t;XIO_NOWHERE&t;(0xFFFFFFFFFFFFFFFFull)
DECL|macro|XIO_ADDR_BITS
mdefine_line|#define&t;XIO_ADDR_BITS&t;(0x0000FFFFFFFFFFFFull)
DECL|macro|XIO_PORT_BITS
mdefine_line|#define&t;XIO_PORT_BITS&t;(0xF000000000000000ull)
DECL|macro|XIO_PORT_SHIFT
mdefine_line|#define&t;XIO_PORT_SHIFT&t;(60)
DECL|macro|XIO_PACKED
mdefine_line|#define&t;XIO_PACKED(x)&t;(((x)&amp;XIO_PORT_BITS) != 0)
DECL|macro|XIO_ADDR
mdefine_line|#define&t;XIO_ADDR(x)&t;((x)&amp;XIO_ADDR_BITS)
DECL|macro|XIO_PORT
mdefine_line|#define&t;XIO_PORT(x)&t;((xwidgetnum_t)(((x)&amp;XIO_PORT_BITS) &gt;&gt; XIO_PORT_SHIFT))
DECL|macro|XIO_PACK
mdefine_line|#define&t;XIO_PACK(p,o)&t;((((uint64_t)(p))&lt;&lt;XIO_PORT_SHIFT) | ((o)&amp;XIO_ADDR_BITS))
macro_line|#endif /* _LANGUAGE_C */
macro_line|#endif /* _ASM_XTALK_XTALK_H */
eof
