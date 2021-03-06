multiline_comment|/*&n; * Implement the sparc64 iomap interfaces&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Create a virtual mapping cookie for an IO port range */
DECL|function|ioport_map
r_void
id|__iomem
op_star
id|ioport_map
c_func
(paren
r_int
r_int
id|port
comma
r_int
r_int
id|nr
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
r_int
r_int
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
multiline_comment|/* Nothing to do */
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
multiline_comment|/* Create a virtual mapping cookie for a PCI BAR (memory or IO) */
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
id|maxlen
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
op_logical_or
op_logical_neg
id|start
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|maxlen
op_logical_and
id|len
OG
id|maxlen
)paren
id|len
op_assign
id|maxlen
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
(brace
r_if
c_cond
(paren
id|flags
op_amp
id|IORESOURCE_CACHEABLE
)paren
r_return
id|ioremap
c_func
(paren
id|start
comma
id|len
)paren
suffix:semicolon
r_return
id|ioremap_nocache
c_func
(paren
id|start
comma
id|len
)paren
suffix:semicolon
)brace
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
multiline_comment|/* nothing to do */
)brace
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
