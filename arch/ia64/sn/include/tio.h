multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_TIO_H
DECL|macro|_ASM_IA64_SN_TIO_H
mdefine_line|#define _ASM_IA64_SN_TIO_H
DECL|macro|TIO_MMR_ADDR_MOD
mdefine_line|#define&t;TIO_MMR_ADDR_MOD
DECL|macro|TIO_NODE_ID
mdefine_line|#define TIO_NODE_ID     TIO_MMR_ADDR_MOD(0x0000000090060e80)
DECL|macro|TIO_ITTE_BASE
mdefine_line|#define TIO_ITTE_BASE   0xb0008800        /* base of translation table entries */
DECL|macro|TIO_ITTE
mdefine_line|#define TIO_ITTE(bigwin)        (TIO_ITTE_BASE + 8*(bigwin))
DECL|macro|TIO_ITTE_OFFSET_BITS
mdefine_line|#define TIO_ITTE_OFFSET_BITS    8       /* size of offset field */
DECL|macro|TIO_ITTE_OFFSET_MASK
mdefine_line|#define TIO_ITTE_OFFSET_MASK    ((1&lt;&lt;TIO_ITTE_OFFSET_BITS)-1)
DECL|macro|TIO_ITTE_OFFSET_SHIFT
mdefine_line|#define TIO_ITTE_OFFSET_SHIFT   0
DECL|macro|TIO_ITTE_WIDGET_BITS
mdefine_line|#define TIO_ITTE_WIDGET_BITS    2       /* size of widget field */
DECL|macro|TIO_ITTE_WIDGET_MASK
mdefine_line|#define TIO_ITTE_WIDGET_MASK    ((1&lt;&lt;TIO_ITTE_WIDGET_BITS)-1)
DECL|macro|TIO_ITTE_WIDGET_SHIFT
mdefine_line|#define TIO_ITTE_WIDGET_SHIFT   12
DECL|macro|TIO_ITTE_VALID_MASK
mdefine_line|#define TIO_ITTE_VALID_MASK&t;0x1
DECL|macro|TIO_ITTE_VALID_SHIFT
mdefine_line|#define TIO_ITTE_VALID_SHIFT&t;16
DECL|macro|TIO_ITTE_PUT
mdefine_line|#define TIO_ITTE_PUT(nasid, bigwin, widget, addr, valid) &bslash;&n;        REMOTE_HUB_S((nasid), TIO_ITTE(bigwin), &bslash;&n;                (((((addr) &gt;&gt; TIO_BWIN_SIZE_BITS) &amp; &bslash;&n;                   TIO_ITTE_OFFSET_MASK) &lt;&lt; TIO_ITTE_OFFSET_SHIFT) | &bslash;&n;                (((widget) &amp; TIO_ITTE_WIDGET_MASK) &lt;&lt; TIO_ITTE_WIDGET_SHIFT)) | &bslash;&n;&t;&t;(( (valid) &amp; TIO_ITTE_VALID_MASK) &lt;&lt; TIO_ITTE_VALID_SHIFT))
macro_line|#endif /*  _ASM_IA64_SN_TIO_H */
eof
