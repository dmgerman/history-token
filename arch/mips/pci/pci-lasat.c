multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000, 2001, 04 Keith M Wesolowski&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
r_extern
r_struct
id|pci_ops
id|nile4_pci_ops
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|gt64120_pci_ops
suffix:semicolon
DECL|variable|lasat_pci_mem_resource
r_static
r_struct
id|resource
id|lasat_pci_mem_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;LASAT PCI MEM&quot;
comma
dot
id|start
op_assign
l_int|0x18000000
comma
dot
id|end
op_assign
l_int|0x19FFFFFF
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|lasat_pci_io_resource
r_static
r_struct
id|resource
id|lasat_pci_io_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;LASAT PCI IO&quot;
comma
dot
id|start
op_assign
l_int|0x1a000000
comma
dot
id|end
op_assign
l_int|0x1bFFFFFF
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
comma
)brace
suffix:semicolon
DECL|variable|lasat_pci_controller
r_static
r_struct
id|pci_controller
id|lasat_pci_controller
op_assign
(brace
dot
id|mem_resource
op_assign
op_amp
id|lasat_pci_mem_resource
comma
dot
id|io_resource
op_assign
op_amp
id|lasat_pci_io_resource
comma
)brace
suffix:semicolon
DECL|function|lasat_pci_setup
r_static
r_int
id|__init
id|lasat_pci_setup
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: starting&bslash;n&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mips_machtype
)paren
(brace
r_case
id|MACH_LASAT_100
suffix:colon
id|lasat_pci_controller.pci_ops
op_assign
op_amp
id|gt64120_pci_ops
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MACH_LASAT_200
suffix:colon
id|lasat_pci_controller.pci_ops
op_assign
op_amp
id|nile4_pci_ops
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;pcibios_init: mips_machtype incorrect&quot;
)paren
suffix:semicolon
)brace
id|register_pci_controller
c_func
(paren
op_amp
id|lasat_pci_controller
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|lasat_pci_setup
id|early_initcall
c_func
(paren
id|lasat_pci_setup
)paren
suffix:semicolon
DECL|macro|LASATINT_ETH1
mdefine_line|#define LASATINT_ETH1   0
DECL|macro|LASATINT_ETH0
mdefine_line|#define LASATINT_ETH0   1
DECL|macro|LASATINT_HDC
mdefine_line|#define LASATINT_HDC    2
DECL|macro|LASATINT_COMP
mdefine_line|#define LASATINT_COMP   3
DECL|macro|LASATINT_HDLC
mdefine_line|#define LASATINT_HDLC   4
DECL|macro|LASATINT_PCIA
mdefine_line|#define LASATINT_PCIA   5
DECL|macro|LASATINT_PCIB
mdefine_line|#define LASATINT_PCIB   6
DECL|macro|LASATINT_PCIC
mdefine_line|#define LASATINT_PCIC   7
DECL|macro|LASATINT_PCID
mdefine_line|#define LASATINT_PCID   8
DECL|function|pcibios_map_irq
r_int
id|__init
id|pcibios_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_switch
c_cond
(paren
id|slot
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|LASATINT_PCIA
suffix:semicolon
multiline_comment|/* Expansion Module 0 */
r_case
l_int|2
suffix:colon
r_return
id|LASATINT_PCIB
suffix:semicolon
multiline_comment|/* Expansion Module 1 */
r_case
l_int|3
suffix:colon
r_return
id|LASATINT_PCIC
suffix:semicolon
multiline_comment|/* Expansion Module 2 */
r_case
l_int|4
suffix:colon
r_return
id|LASATINT_ETH1
suffix:semicolon
multiline_comment|/* Ethernet 1 (LAN 2) */
r_case
l_int|5
suffix:colon
r_return
id|LASATINT_ETH0
suffix:semicolon
multiline_comment|/* Ethernet 0 (LAN 1) */
r_case
l_int|6
suffix:colon
r_return
id|LASATINT_HDC
suffix:semicolon
multiline_comment|/* IDE controller */
r_default
suffix:colon
r_return
l_int|0xff
suffix:semicolon
multiline_comment|/* Illegal */
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Do platform specific device initialization at pci_enable_device() time */
DECL|function|pcibios_plat_dev_init
r_int
id|pcibios_plat_dev_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
