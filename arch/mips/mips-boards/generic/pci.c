multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999, 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * MIPS boards specific PCI support.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mips-boards/generic.h&gt;
macro_line|#include &lt;asm/gt64120.h&gt;
macro_line|#include &lt;asm/mips-boards/bonito64.h&gt;
macro_line|#include &lt;asm/mips-boards/msc01_pci.h&gt;
macro_line|#ifdef CONFIG_MIPS_MALTA
macro_line|#include &lt;asm/mips-boards/malta.h&gt;
macro_line|#endif
DECL|variable|bonito64_mem_resource
r_static
r_struct
id|resource
id|bonito64_mem_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Bonito PCI MEM&quot;
comma
dot
id|start
op_assign
l_int|0x10000000UL
comma
dot
id|end
op_assign
l_int|0x1bffffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|bonito64_io_resource
r_static
r_struct
id|resource
id|bonito64_io_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Bonito IO MEM&quot;
comma
dot
id|start
op_assign
l_int|0x00002000UL
comma
multiline_comment|/* avoid conflicts with YAMON allocated I/O addresses */
dot
id|end
op_assign
l_int|0x000fffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
comma
)brace
suffix:semicolon
DECL|variable|gt64120_mem_resource
r_static
r_struct
id|resource
id|gt64120_mem_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;GT64120 PCI MEM&quot;
comma
dot
id|start
op_assign
l_int|0x10000000UL
comma
dot
id|end
op_assign
l_int|0x1bdfffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|gt64120_io_resource
r_static
r_struct
id|resource
id|gt64120_io_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;GT64120 IO MEM&quot;
comma
macro_line|#ifdef CONFIG_MIPS_ATLAS
dot
id|start
op_assign
l_int|0x18000000UL
comma
dot
id|end
op_assign
l_int|0x181fffffUL
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_MALTA
dot
id|start
op_assign
l_int|0x00002000UL
comma
dot
id|end
op_assign
l_int|0x001fffffUL
comma
macro_line|#endif
dot
id|flags
op_assign
id|IORESOURCE_IO
comma
)brace
suffix:semicolon
DECL|variable|msc_mem_resource
r_static
r_struct
id|resource
id|msc_mem_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MSC PCI MEM&quot;
comma
dot
id|start
op_assign
l_int|0x10000000UL
comma
dot
id|end
op_assign
l_int|0x1fffffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|msc_io_resource
r_static
r_struct
id|resource
id|msc_io_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MSC IO MEM&quot;
comma
dot
id|start
op_assign
l_int|0x00002000UL
comma
dot
id|end
op_assign
l_int|0x007fffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
comma
)brace
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|bonito64_pci_ops
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|gt64120_pci_ops
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|msc_pci_ops
suffix:semicolon
DECL|variable|bonito64_controller
r_static
r_struct
id|pci_controller
id|bonito64_controller
op_assign
(brace
dot
id|pci_ops
op_assign
op_amp
id|bonito64_pci_ops
comma
dot
id|io_resource
op_assign
op_amp
id|bonito64_io_resource
comma
dot
id|mem_resource
op_assign
op_amp
id|bonito64_mem_resource
comma
dot
id|mem_offset
op_assign
l_int|0x10000000UL
comma
dot
id|io_offset
op_assign
l_int|0x00000000UL
comma
)brace
suffix:semicolon
DECL|variable|gt64120_controller
r_static
r_struct
id|pci_controller
id|gt64120_controller
op_assign
(brace
dot
id|pci_ops
op_assign
op_amp
id|gt64120_pci_ops
comma
dot
id|io_resource
op_assign
op_amp
id|gt64120_io_resource
comma
dot
id|mem_resource
op_assign
op_amp
id|gt64120_mem_resource
comma
dot
id|mem_offset
op_assign
l_int|0x00000000UL
comma
dot
id|io_offset
op_assign
l_int|0x00000000UL
comma
)brace
suffix:semicolon
DECL|variable|msc_controller
r_static
r_struct
id|pci_controller
id|msc_controller
op_assign
(brace
dot
id|pci_ops
op_assign
op_amp
id|msc_pci_ops
comma
dot
id|io_resource
op_assign
op_amp
id|msc_io_resource
comma
dot
id|mem_resource
op_assign
op_amp
id|msc_mem_resource
comma
dot
id|mem_offset
op_assign
l_int|0x10000000UL
comma
dot
id|io_offset
op_assign
l_int|0x00000000UL
comma
)brace
suffix:semicolon
DECL|function|pcibios_init
r_static
r_int
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|controller
suffix:semicolon
r_switch
c_cond
(paren
id|mips_revision_corid
)paren
(brace
r_case
id|MIPS_REVISION_CORID_QED_RM5261
suffix:colon
r_case
id|MIPS_REVISION_CORID_CORE_LV
suffix:colon
r_case
id|MIPS_REVISION_CORID_CORE_FPGA
suffix:colon
r_case
id|MIPS_REVISION_CORID_CORE_FPGAR2
suffix:colon
multiline_comment|/*&n;&t;&t; * Due to a bug in the Galileo system controller, we need&n;&t;&t; * to setup the PCI BAR for the Galileo internal registers.&n;&t;&t; * This should be done in the bios/bootprom and will be&n;&t;&t; * fixed in a later revision of YAMON (the MIPS boards&n;&t;&t; * boot prom).&n;&t;&t; */
id|GT_WRITE
c_func
(paren
id|GT_PCI0_CFGADDR_OFS
comma
(paren
l_int|0
op_lshift
id|GT_PCI0_CFGADDR_BUSNUM_SHF
)paren
op_or
multiline_comment|/* Local bus */
(paren
l_int|0
op_lshift
id|GT_PCI0_CFGADDR_DEVNUM_SHF
)paren
op_or
multiline_comment|/* GT64120 dev */
(paren
l_int|0
op_lshift
id|GT_PCI0_CFGADDR_FUNCTNUM_SHF
)paren
op_or
multiline_comment|/* Function 0*/
(paren
(paren
l_int|0x20
op_div
l_int|4
)paren
op_lshift
id|GT_PCI0_CFGADDR_REGNUM_SHF
)paren
op_or
multiline_comment|/* BAR 4*/
id|GT_PCI0_CFGADDR_CONFIGEN_BIT
)paren
suffix:semicolon
multiline_comment|/* Perform the write */
id|GT_WRITE
c_func
(paren
id|GT_PCI0_CFGDATA_OFS
comma
id|CPHYSADDR
c_func
(paren
id|MIPS_GT_BASE
)paren
)paren
suffix:semicolon
id|controller
op_assign
op_amp
id|gt64120_controller
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MIPS_REVISION_CORID_BONITO64
suffix:colon
r_case
id|MIPS_REVISION_CORID_CORE_20K
suffix:colon
r_case
id|MIPS_REVISION_CORID_CORE_EMUL_BON
suffix:colon
id|controller
op_assign
op_amp
id|bonito64_controller
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MIPS_REVISION_CORID_CORE_MSC
suffix:colon
r_case
id|MIPS_REVISION_CORID_CORE_FPGA2
suffix:colon
r_case
id|MIPS_REVISION_CORID_CORE_EMUL_MSC
suffix:colon
id|controller
op_assign
op_amp
id|msc_controller
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
id|ioport_resource.end
op_assign
id|controller-&gt;io_resource-&gt;end
suffix:semicolon
id|register_pci_controller
(paren
id|controller
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pcibios_init
id|early_initcall
c_func
(paren
id|pcibios_init
)paren
suffix:semicolon
eof
