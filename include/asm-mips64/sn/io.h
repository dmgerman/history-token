multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Ralf Baechle&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SN_IO_H
DECL|macro|_ASM_SN_IO_H
mdefine_line|#define _ASM_SN_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if !defined(CONFIG_SGI_IO)
macro_line|#include &lt;asm/sn/sn0/addrs.h&gt;
DECL|macro|IO_SPACE_BASE
mdefine_line|#define IO_SPACE_BASE IO_BASE
multiline_comment|/* Because we only have PCI I/O ports.  */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/* No isa_* versions, the Origin doesn&squot;t have ISA / EISA bridges.  */
macro_line|#else&t;/* CONFIG_SGI_IO */
DECL|macro|IIO_ITTE_BASE
mdefine_line|#define IIO_ITTE_BASE&t;0x400160&t;/* base of translation table entries */
DECL|macro|IIO_ITTE
mdefine_line|#define IIO_ITTE(bigwin)&t;(IIO_ITTE_BASE + 8*(bigwin))
DECL|macro|IIO_ITTE_OFFSET_BITS
mdefine_line|#define IIO_ITTE_OFFSET_BITS&t;5&t;/* size of offset field */
DECL|macro|IIO_ITTE_OFFSET_MASK
mdefine_line|#define IIO_ITTE_OFFSET_MASK&t;((1&lt;&lt;IIO_ITTE_OFFSET_BITS)-1)
DECL|macro|IIO_ITTE_OFFSET_SHIFT
mdefine_line|#define IIO_ITTE_OFFSET_SHIFT&t;0
DECL|macro|IIO_ITTE_WIDGET_BITS
mdefine_line|#define IIO_ITTE_WIDGET_BITS&t;4&t;/* size of widget field */
DECL|macro|IIO_ITTE_WIDGET_MASK
mdefine_line|#define IIO_ITTE_WIDGET_MASK&t;((1&lt;&lt;IIO_ITTE_WIDGET_BITS)-1)
DECL|macro|IIO_ITTE_WIDGET_SHIFT
mdefine_line|#define IIO_ITTE_WIDGET_SHIFT&t;8
DECL|macro|IIO_ITTE_IOSP
mdefine_line|#define IIO_ITTE_IOSP&t;&t;1&t;/* I/O Space bit */
DECL|macro|IIO_ITTE_IOSP_MASK
mdefine_line|#define IIO_ITTE_IOSP_MASK&t;1
DECL|macro|IIO_ITTE_IOSP_SHIFT
mdefine_line|#define IIO_ITTE_IOSP_SHIFT&t;12
DECL|macro|HUB_PIO_MAP_TO_MEM
mdefine_line|#define HUB_PIO_MAP_TO_MEM&t;0
DECL|macro|HUB_PIO_MAP_TO_IO
mdefine_line|#define HUB_PIO_MAP_TO_IO&t;1
DECL|macro|IIO_ITTE_INVALID_WIDGET
mdefine_line|#define IIO_ITTE_INVALID_WIDGET&t;3&t;/* an invalid widget  */
DECL|macro|IIO_ITTE_PUT
mdefine_line|#define IIO_ITTE_PUT(nasid, bigwin, io_or_mem, widget, addr) &bslash;&n;&t;REMOTE_HUB_S((nasid), IIO_ITTE(bigwin), &bslash;&n;&t;&t;(((((addr) &gt;&gt; BWIN_SIZE_BITS) &amp; &bslash;&n;&t;&t;   IIO_ITTE_OFFSET_MASK) &lt;&lt; IIO_ITTE_OFFSET_SHIFT) | &bslash;&n;&t;&t;(io_or_mem &lt;&lt; IIO_ITTE_IOSP_SHIFT) | &bslash;&n;&t;&t;(((widget) &amp; IIO_ITTE_WIDGET_MASK) &lt;&lt; IIO_ITTE_WIDGET_SHIFT)))
DECL|macro|IIO_ITTE_DISABLE
mdefine_line|#define IIO_ITTE_DISABLE(nasid, bigwin) &bslash;&n;&t;IIO_ITTE_PUT((nasid), HUB_PIO_MAP_TO_MEM, &bslash;&n;&t;&t;     (bigwin), IIO_ITTE_INVALID_WIDGET, 0)
DECL|macro|IIO_ITTE_GET
mdefine_line|#define IIO_ITTE_GET(nasid, bigwin) REMOTE_HUB_ADDR((nasid), IIO_ITTE(bigwin))
multiline_comment|/*&n; * Macro which takes the widget number, and returns the &n; * IO PRB address of that widget.&n; * value _x is expected to be a widget number in the range &n; * 0, 8 - 0xF&n; */
DECL|macro|IIO_IOPRB
mdefine_line|#define&t;IIO_IOPRB(_x)&t;(IIO_IOPRB_0 + ( ( (_x) &lt; HUB_WIDGET_ID_MIN ? &bslash;&n;&t;&t;&t;(_x) : &bslash;&n;&t;&t;&t;(_x) - (HUB_WIDGET_ID_MIN-1)) &lt;&lt; 3) )
macro_line|#if defined (CONFIG_SGI_IP27)
macro_line|#include &lt;asm/sn/sn0/hubio.h&gt;
macro_line|#endif
macro_line|#endif&t;/* CONFIG_SGI_IO */
macro_line|#endif /* _ASM_SN_IO_H */
eof
