multiline_comment|/*&n; * linux/arch/sh/drivers/pci/ops-sh03.c&n; *&n; * PCI initialization for the Interface CTP/PCI-SH03 board&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;pci-sh7751.h&quot;
multiline_comment|/*&n; * Description:  This function sets up and initializes the pcic, sets&n; * up the BARS, maps the DRAM into the address space etc, etc.&n; */
DECL|function|pcibios_init_platform
r_int
id|__init
id|pcibios_init_platform
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|sh7751_io_resource
r_static
r_struct
id|resource
id|sh7751_io_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SH03 IO&quot;
comma
dot
id|start
op_assign
id|SH7751_PCI_IO_BASE
comma
dot
id|end
op_assign
id|SH7751_PCI_IO_BASE
op_plus
id|SH7751_PCI_IO_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
)brace
suffix:semicolon
DECL|variable|sh7751_mem_resource
r_static
r_struct
id|resource
id|sh7751_mem_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SH03 mem&quot;
comma
dot
id|start
op_assign
id|SH7751_PCI_MEMORY_BASE
comma
dot
id|end
op_assign
id|SH7751_PCI_MEMORY_BASE
op_plus
id|SH7751_PCI_MEM_SIZE
op_minus
l_int|1
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
)brace
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|sh7751_pci_ops
suffix:semicolon
DECL|variable|board_pci_channels
r_struct
id|pci_channel
id|board_pci_channels
(braket
)braket
op_assign
(brace
(brace
op_amp
id|sh7751_pci_ops
comma
op_amp
id|sh7751_io_resource
comma
op_amp
id|sh7751_mem_resource
comma
l_int|0
comma
l_int|0xff
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
eof
