multiline_comment|/*&n; *  setup.c, Setup for the TANBAC TB0229 (VR4131DIMM)&n; *&n; *  Copyright (C) 2002-2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  Modified for TANBAC TB0229:&n; *  Copyright (C) 2003  Megasolution Inc.  &lt;matsu@megasolution.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pci_channel.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/vr41xx/tb0229.h&gt;
macro_line|#ifdef CONFIG_PCI
DECL|variable|vr41xx_pci_io_resource
r_static
r_struct
id|resource
id|vr41xx_pci_io_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PCI I/O space&quot;
comma
dot
id|start
op_assign
id|VR41XX_PCI_IO_START
comma
dot
id|end
op_assign
id|VR41XX_PCI_IO_END
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
comma
)brace
suffix:semicolon
DECL|variable|vr41xx_pci_mem_resource
r_static
r_struct
id|resource
id|vr41xx_pci_mem_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PCI memory space&quot;
comma
dot
id|start
op_assign
id|VR41XX_PCI_MEM_START
comma
dot
id|end
op_assign
id|VR41XX_PCI_MEM_END
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|vr41xx_pci_ops
suffix:semicolon
DECL|variable|vr41xx_controller
r_struct
id|pci_controller
id|vr41xx_controller
op_assign
(brace
dot
id|pci_ops
op_assign
op_amp
id|vr41xx_pci_ops
comma
dot
id|io_resource
op_assign
op_amp
id|vr41xx_pci_io_resource
comma
dot
id|mem_resource
op_assign
op_amp
id|vr41xx_pci_mem_resource
comma
)brace
suffix:semicolon
DECL|variable|vr41xx_pci_mem1
r_struct
id|vr41xx_pci_address_space
id|vr41xx_pci_mem1
op_assign
(brace
dot
id|internal_base
op_assign
id|VR41XX_PCI_MEM1_BASE
comma
dot
id|address_mask
op_assign
id|VR41XX_PCI_MEM1_MASK
comma
dot
id|pci_base
op_assign
id|IO_MEM1_RESOURCE_START
comma
)brace
suffix:semicolon
DECL|variable|vr41xx_pci_mem2
r_struct
id|vr41xx_pci_address_space
id|vr41xx_pci_mem2
op_assign
(brace
dot
id|internal_base
op_assign
id|VR41XX_PCI_MEM2_BASE
comma
dot
id|address_mask
op_assign
id|VR41XX_PCI_MEM2_MASK
comma
dot
id|pci_base
op_assign
id|IO_MEM2_RESOURCE_START
comma
)brace
suffix:semicolon
DECL|variable|vr41xx_pci_io
r_struct
id|vr41xx_pci_address_space
id|vr41xx_pci_io
op_assign
(brace
dot
id|internal_base
op_assign
id|VR41XX_PCI_IO_BASE
comma
dot
id|address_mask
op_assign
id|VR41XX_PCI_IO_MASK
comma
dot
id|pci_base
op_assign
id|IO_PORT_RESOURCE_START
)brace
suffix:semicolon
DECL|variable|pci_address_map
r_static
r_struct
id|vr41xx_pci_address_map
id|pci_address_map
op_assign
(brace
dot
id|mem1
op_assign
op_amp
id|vr41xx_pci_mem1
comma
dot
id|mem2
op_assign
op_amp
id|vr41xx_pci_mem2
comma
dot
id|io
op_assign
op_amp
id|vr41xx_pci_io
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;TANBAC TB0229&quot;
suffix:semicolon
)brace
DECL|function|tanbac_tb0229_setup
r_static
r_int
id|tanbac_tb0229_setup
c_func
(paren
r_void
)paren
(brace
id|set_io_port_base
c_func
(paren
id|IO_PORT_BASE
)paren
suffix:semicolon
id|ioport_resource.start
op_assign
id|IO_PORT_RESOURCE_START
suffix:semicolon
id|ioport_resource.end
op_assign
id|IO_PORT_RESOURCE_END
suffix:semicolon
id|vr41xx_siu_init
c_func
(paren
id|SIU_RS232C
comma
l_int|0
)paren
suffix:semicolon
id|vr41xx_dsiu_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
id|vr41xx_pciu_init
c_func
(paren
op_amp
id|pci_address_map
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TANBAC_TB0219
id|_machine_restart
op_assign
id|tanbac_tb0229_restart
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|tanbac_tb0229_setup
id|early_initcall
c_func
(paren
id|tanbac_tb0229_setup
)paren
suffix:semicolon
eof
