multiline_comment|/*  &n; *  (C) 2004 Margit Schubert-While &lt;margitsw@t-online.de&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
multiline_comment|/*  &n; *&t;Compatibility header file to aid support of different kernel versions&n; */
macro_line|#ifdef PRISM54_COMPAT24
macro_line|#include &quot;prismcompat24.h&quot;
macro_line|#else&t;/* PRISM54_COMPAT24 */
macro_line|#ifndef _PRISM_COMPAT_H
DECL|macro|_PRISM_COMPAT_H
mdefine_line|#define _PRISM_COMPAT_H
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/firmware.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#if !defined(CONFIG_FW_LOADER) &amp;&amp; !defined(CONFIG_FW_LOADER_MODULE)
macro_line|#error Firmware Loading is not configured in the kernel !
macro_line|#endif
macro_line|#ifndef __iomem
DECL|macro|__iomem
mdefine_line|#define __iomem
macro_line|#endif
DECL|macro|prism54_synchronize_irq
mdefine_line|#define prism54_synchronize_irq(irq) synchronize_irq(irq)
DECL|macro|PRISM_FW_PDEV
mdefine_line|#define PRISM_FW_PDEV&t;&t;&amp;priv-&gt;pdev-&gt;dev
macro_line|#endif&t;&t;&t;&t;/* _PRISM_COMPAT_H */
macro_line|#endif&t;&t;&t;&t;/* PRISM54_COMPAT24 */
eof
