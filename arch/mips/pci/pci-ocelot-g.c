multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2004 by Ralf Baechle&n; *&n; * This doesn&squot;t really fly - but I don&squot;t have a GT64240 system for testing.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/gt64240.h&gt;
macro_line|#include &lt;asm/pci_channel.h&gt;
multiline_comment|/*&n; * We assume these address ranges have been programmed into the GT-64240 by&n; * the firmware.  PMON in case of the Ocelot G does that.  Note the size of&n; * the I/O range is completly stupid; I/O mappings are limited to at most&n; * 256 bytes by the PCI spec and deprecated; and just to make things worse&n; * apparently many devices don&squot;t decode more than 64k of I/O space.&n; */
DECL|macro|gt_io_size
mdefine_line|#define gt_io_size&t;0x20000000UL
DECL|macro|gt_io_base
mdefine_line|#define gt_io_base&t;0xe0000000UL
DECL|variable|gt_pci_mem0_resource
r_static
r_struct
id|resource
id|gt_pci_mem0_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MV64240 PCI0 MEM&quot;
comma
dot
id|start
op_assign
l_int|0xc0000000UL
comma
dot
id|end
op_assign
l_int|0xcfffffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
)brace
suffix:semicolon
DECL|variable|gt_pci_io_mem0_resource
r_static
r_struct
id|resource
id|gt_pci_io_mem0_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MV64240 PCI0 IO MEM&quot;
comma
dot
id|start
op_assign
l_int|0xe0000000UL
comma
dot
id|end
op_assign
l_int|0xefffffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
)brace
suffix:semicolon
DECL|variable|gt_bus0_controller
r_static
r_struct
id|pci_controller
id|gt_bus0_controller
op_assign
(brace
dot
id|pci_ops
op_assign
op_amp
id|gt_bus0_pci_ops
comma
dot
id|mem_resource
op_assign
op_amp
id|gt_pci_mem0_resource
comma
dot
id|mem_offset
op_assign
l_int|0xc0000000UL
comma
dot
id|io_resource
op_assign
op_amp
id|gt_pci_io_mem0_resource
comma
dot
id|io_offset
op_assign
l_int|0x00000000UL
)brace
suffix:semicolon
DECL|variable|gt_pci_mem1_resource
r_static
r_struct
id|resource
id|gt_pci_mem1_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MV64240 PCI1 MEM&quot;
comma
dot
id|start
op_assign
l_int|0xd0000000UL
comma
dot
id|end
op_assign
l_int|0xdfffffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
)brace
suffix:semicolon
DECL|variable|gt_pci_io_mem1_resource
r_static
r_struct
id|resource
id|gt_pci_io_mem1_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MV64240 PCI1 IO MEM&quot;
comma
dot
id|start
op_assign
l_int|0xf0000000UL
comma
dot
id|end
op_assign
l_int|0xffffffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
)brace
suffix:semicolon
DECL|variable|gt_bus1_controller
r_static
r_struct
id|pci_controller
id|gt_bus1_controller
op_assign
(brace
dot
id|pci_ops
op_assign
op_amp
id|gt_bus1_pci_ops
comma
dot
id|mem_resource
op_assign
op_amp
id|gt_pci_mem1_resource
comma
dot
id|mem_offset
op_assign
l_int|0xd0000000UL
comma
dot
id|io_resource
op_assign
op_amp
id|gt_pci_io_mem1_resource
comma
dot
id|io_offset
op_assign
l_int|0x10000000UL
)brace
suffix:semicolon
DECL|function|ocelot_g_pci_init
r_static
id|__init
r_int
id|__init
id|ocelot_g_pci_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|io_v_base
suffix:semicolon
r_if
c_cond
(paren
id|gt_io_size
)paren
(brace
id|io_v_base
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|gt_io_base
comma
id|gt_io_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io_v_base
)paren
id|panic
c_func
(paren
l_string|&quot;Could not ioremap I/O port range&quot;
)paren
suffix:semicolon
id|set_io_port_base
c_func
(paren
id|io_v_base
)paren
suffix:semicolon
)brace
id|register_pci_controller
c_func
(paren
op_amp
id|gt_bus0_controller
)paren
suffix:semicolon
id|register_pci_controller
c_func
(paren
op_amp
id|gt_bus1_controller
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ocelot_g_pci_init
id|arch_initcall
c_func
(paren
id|ocelot_g_pci_init
)paren
suffix:semicolon
eof
