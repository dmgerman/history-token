multiline_comment|/*&n; * FILE NAME: ppc405_pci.c&n; *&n; * BRIEF MODULE DESCRIPTION: &n; * Based on arch/ppc/kernel/indirect.c, Copyright (C) 1998 Gabriel Paubert.&n; *&n; * Author: MontaVista Software, Inc.  &lt;source@mvista.com&gt;&n; *         Frank Rowand &lt;frank_rowand@mvista.com&gt;&n; *         Debbie Chu   &lt;debbie_chu@mvista.com&gt;&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ibm4xx.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;platforms/ibm_ocp.h&gt;
macro_line|#ifdef  CONFIG_DEBUG_BRINGUP
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
r_extern
r_void
id|bios_fixup
c_func
(paren
r_struct
id|pci_controller
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ppc405_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
suffix:semicolon
r_extern
r_struct
id|pcil0_regs
op_star
id|PCIL_ADDR
(braket
)braket
suffix:semicolon
r_void
DECL|function|ppc405_pcibios_fixup_resources
id|ppc405_pcibios_fixup_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|max_host_addr
suffix:semicolon
r_int
r_int
id|min_host_addr
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
multiline_comment|/*&n;&t; * openbios puts some graphics cards in the same range as the host&n;&t; * controller uses to map to SDRAM.  Fix it.&n;&t; */
id|min_host_addr
op_assign
l_int|0
suffix:semicolon
id|max_host_addr
op_assign
id|PPC405_PCI_MEM_BASE
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DEVICE_COUNT_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|res
op_assign
id|dev-&gt;resource
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res-&gt;start
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
op_logical_and
(paren
(paren
(paren
id|res-&gt;start
op_ge
id|min_host_addr
)paren
op_logical_and
(paren
id|res-&gt;start
op_le
id|max_host_addr
)paren
)paren
op_logical_or
(paren
(paren
id|res-&gt;end
op_ge
id|min_host_addr
)paren
op_logical_and
(paren
id|res-&gt;end
op_le
id|max_host_addr
)paren
)paren
op_logical_or
(paren
(paren
id|res-&gt;start
OL
id|min_host_addr
)paren
op_logical_and
(paren
id|res-&gt;end
OG
id|max_host_addr
)paren
)paren
)paren
)paren
(brace
id|DBG
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: 0x%lx &lt;= resource[%d] &lt;= 0x%lx&quot;
l_string|&quot;, bus 0x%x dev 0x%2.2x.%1.1x,&bslash;n&quot;
id|KERN_ERR
l_string|&quot;  %s&bslash;n&quot;
id|KERN_ERR
l_string|&quot;  fixup will be attempted later&bslash;n&quot;
comma
id|min_host_addr
comma
id|i
comma
id|max_host_addr
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* force pcibios_assign_resources() to assign a new address */
id|res-&gt;end
op_sub_assign
id|res-&gt;start
suffix:semicolon
id|res-&gt;start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_static
r_int
DECL|function|ppc4xx_exclude_device
id|ppc4xx_exclude_device
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|devfn
)paren
(brace
multiline_comment|/* We prevent us from seeing ourselves to avoid having&n;&t; * the kernel try to remap our BAR #1 and fuck up bus&n;&t; * master from external PCI devices&n;&t; */
r_return
(paren
id|bus
op_eq
l_int|0
op_logical_and
id|devfn
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|ppc4xx_find_bridges
id|ppc4xx_find_bridges
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose_a
suffix:semicolon
r_struct
id|pcil0_regs
op_star
id|pcip
suffix:semicolon
r_int
r_int
id|tmp_addr
suffix:semicolon
r_int
r_int
id|tmp_size
suffix:semicolon
r_int
r_int
id|reg_index
suffix:semicolon
r_int
r_int
id|new_pmm_max
suffix:semicolon
r_int
r_int
id|new_pmm_min
suffix:semicolon
id|isa_io_base
op_assign
l_int|0
suffix:semicolon
id|isa_mem_base
op_assign
l_int|0
suffix:semicolon
id|pci_dram_offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Check if running in slave mode */
r_if
c_cond
(paren
(paren
id|mfdcr
c_func
(paren
id|DCRN_CHPSR
)paren
op_amp
id|PSR_PCI_ARBIT_EN
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Running as PCI slave, kernel PCI disabled !&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Setup PCI32 hose */
id|hose_a
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose_a
)paren
r_return
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose_a
comma
id|PPC405_PCI_CONFIG_ADDR
comma
id|PPC405_PCI_CONFIG_DATA
)paren
suffix:semicolon
id|pcip
op_assign
id|ioremap
c_func
(paren
(paren
r_int
r_int
)paren
id|PCIL_ADDR
(braket
l_int|0
)braket
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcip
op_ne
l_int|NULL
)paren
(brace
macro_line|#if defined(CONFIG_BIOS_FIXUP)
id|bios_fixup
c_func
(paren
id|hose_a
comma
id|pcip
)paren
suffix:semicolon
macro_line|#endif
id|new_pmm_min
op_assign
l_int|0xffffffff
suffix:semicolon
r_for
c_loop
(paren
id|reg_index
op_assign
l_int|0
suffix:semicolon
id|reg_index
OL
l_int|3
suffix:semicolon
id|reg_index
op_increment
)paren
(brace
id|tmp_size
op_assign
id|in_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|reg_index
)braket
dot
id|ma
)paren
)paren
suffix:semicolon
singleline_comment|// *_PMM0MA
r_if
c_cond
(paren
id|tmp_size
op_amp
l_int|0x1
)paren
(brace
id|tmp_addr
op_assign
id|in_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|reg_index
)braket
dot
id|pcila
)paren
)paren
suffix:semicolon
singleline_comment|// *_PMM0PCILA
r_if
c_cond
(paren
id|tmp_addr
OL
id|PPC405_PCI_PHY_MEM_BASE
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Disabling mapping to PCI mem addr 0x%8.8x&bslash;n&quot;
comma
id|tmp_addr
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|reg_index
)braket
dot
id|ma
)paren
comma
id|tmp_size
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
singleline_comment|// *_PMMOMA
)brace
r_else
(brace
id|tmp_addr
op_assign
id|in_le32
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
(paren
id|pcip-&gt;pmm
(braket
id|reg_index
)braket
dot
id|la
)paren
)paren
suffix:semicolon
singleline_comment|// *_PMMOLA
r_if
c_cond
(paren
id|tmp_addr
OL
id|new_pmm_min
)paren
id|new_pmm_min
op_assign
id|tmp_addr
suffix:semicolon
id|tmp_addr
op_assign
id|tmp_addr
op_plus
(paren
l_int|0xffffffff
op_minus
(paren
id|tmp_size
op_amp
l_int|0xffffc000
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp_addr
OG
id|PPC405_PCI_UPPER_MEM
)paren
(brace
id|new_pmm_max
op_assign
id|tmp_addr
suffix:semicolon
singleline_comment|// PPC405_PCI_UPPER_MEM 
)brace
r_else
(brace
id|new_pmm_max
op_assign
id|PPC405_PCI_UPPER_MEM
suffix:semicolon
)brace
)brace
)brace
)brace
singleline_comment|// for
id|iounmap
c_func
(paren
id|pcip
)paren
suffix:semicolon
)brace
id|hose_a-&gt;first_busno
op_assign
l_int|0
suffix:semicolon
id|hose_a-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|hose_a-&gt;pci_mem_offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Setup bridge memory/IO ranges &amp; resources&n;&t; * TODO: Handle firmwares setting up a legacy ISA mem base&n;&t; */
id|hose_a-&gt;io_space.start
op_assign
id|PPC405_PCI_LOWER_IO
suffix:semicolon
id|hose_a-&gt;io_space.end
op_assign
id|PPC405_PCI_UPPER_IO
suffix:semicolon
id|hose_a-&gt;mem_space.start
op_assign
id|new_pmm_min
suffix:semicolon
id|hose_a-&gt;mem_space.end
op_assign
id|new_pmm_max
suffix:semicolon
id|hose_a-&gt;io_base_phys
op_assign
id|PPC405_PCI_PHY_IO_BASE
suffix:semicolon
id|hose_a-&gt;io_base_virt
op_assign
id|ioremap
c_func
(paren
id|hose_a-&gt;io_base_phys
comma
l_int|0x10000
)paren
suffix:semicolon
id|hose_a-&gt;io_resource.start
op_assign
l_int|0
suffix:semicolon
id|hose_a-&gt;io_resource.end
op_assign
id|PPC405_PCI_UPPER_IO
op_minus
id|PPC405_PCI_LOWER_IO
suffix:semicolon
id|hose_a-&gt;io_resource.flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|hose_a-&gt;io_resource.name
op_assign
l_string|&quot;PCI I/O&quot;
suffix:semicolon
id|hose_a-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|start
op_assign
id|new_pmm_min
suffix:semicolon
id|hose_a-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|end
op_assign
id|new_pmm_max
suffix:semicolon
id|hose_a-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|hose_a-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|name
op_assign
l_string|&quot;PCI Memory&quot;
suffix:semicolon
id|isa_io_base
op_assign
(paren
r_int
)paren
id|hose_a-&gt;io_base_virt
suffix:semicolon
id|isa_mem_base
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*     ISA not implemented */
id|ISA_DMA_THRESHOLD
op_assign
l_int|0x00ffffff
suffix:semicolon
multiline_comment|/* ??? ISA not implemented */
multiline_comment|/* Scan busses &amp; initial setup by pci_auto */
id|hose_a-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose_a
comma
id|hose_a-&gt;first_busno
)paren
suffix:semicolon
id|hose_a-&gt;last_busno
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Setup ppc_md */
id|ppc_md.pcibios_fixup
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.pci_exclude_device
op_assign
id|ppc4xx_exclude_device
suffix:semicolon
id|ppc_md.pcibios_fixup_resources
op_assign
id|ppc405_pcibios_fixup_resources
suffix:semicolon
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
id|ppc_md.pci_map_irq
op_assign
id|ppc405_map_irq
suffix:semicolon
)brace
eof