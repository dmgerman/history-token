multiline_comment|/*&n; * arch/sh64/lib/iomap.c&n; *&n; * Generic sh64 iomap interface&n; *&n; * Copyright (C) 2004  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_void
id|__iomem
op_star
id|__attribute__
(paren
(paren
id|weak
)paren
)paren
DECL|function|ioport_map
id|ioport_map
c_func
(paren
r_int
r_int
id|port
comma
r_int
r_int
id|len
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
id|port
suffix:semicolon
)brace
DECL|function|ioport_unmap
r_void
id|ioport_unmap
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
multiline_comment|/* Nothing .. */
)brace
DECL|function|pci_iomap
r_void
id|__iomem
op_star
id|pci_iomap
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|bar
comma
r_int
r_int
id|max
)paren
(brace
r_int
r_int
id|start
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
id|bar
)paren
suffix:semicolon
r_int
r_int
id|len
op_assign
id|pci_resource_len
c_func
(paren
id|dev
comma
id|bar
)paren
suffix:semicolon
r_int
r_int
id|flags
op_assign
id|pci_resource_flags
c_func
(paren
id|dev
comma
id|bar
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|max
op_logical_and
id|len
OG
id|max
)paren
id|len
op_assign
id|max
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IORESOURCE_IO
)paren
r_return
id|ioport_map
c_func
(paren
id|start
op_plus
id|pciio_virt
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IORESOURCE_MEM
)paren
r_return
(paren
r_void
id|__iomem
op_star
)paren
id|start
suffix:semicolon
multiline_comment|/* What? */
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pci_iounmap
r_void
id|pci_iounmap
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_void
id|__iomem
op_star
id|addr
)paren
(brace
multiline_comment|/* Nothing .. */
)brace
DECL|variable|ioport_map
id|EXPORT_SYMBOL
c_func
(paren
id|ioport_map
)paren
suffix:semicolon
DECL|variable|ioport_unmap
id|EXPORT_SYMBOL
c_func
(paren
id|ioport_unmap
)paren
suffix:semicolon
DECL|variable|pci_iomap
id|EXPORT_SYMBOL
c_func
(paren
id|pci_iomap
)paren
suffix:semicolon
DECL|variable|pci_iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|pci_iounmap
)paren
suffix:semicolon
eof
