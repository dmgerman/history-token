multiline_comment|/*&n; * arch/ppc/syslib/mpc10x_common.c&n; *&n; * Common routines for the Motorola SPS MPC106, MPC107 and MPC8240 Host bridge,&n; * Mem ctlr, EPIC, etc.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * *** WARNING - A BAT MUST be set to access the PCI config addr/data regs ***&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/mpc10x.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
multiline_comment|/* The OCP structure is fixed by code below, before OCP initialises.&n;   paddr depends on where the board places the EUMB.&n;    - fixed in mpc10x_bridge_init().&n;   irq depends on two things:&n;    &gt; does the board use the EPIC at all? (PCORE does not).&n;    &gt; is the EPIC in serial or parallel mode?&n;    - fixed in mpc10x_set_openpic().&n;*/
macro_line|#ifdef CONFIG_MPC10X_OPENPIC
macro_line|#ifdef CONFIG_EPIC_SERIAL_MODE
DECL|macro|EPIC_IRQ_BASE
mdefine_line|#define EPIC_IRQ_BASE (epic_serial_mode ? 16 : 5)
macro_line|#else
DECL|macro|EPIC_IRQ_BASE
mdefine_line|#define EPIC_IRQ_BASE 5
macro_line|#endif
DECL|macro|MPC10X_I2C_IRQ
mdefine_line|#define MPC10X_I2C_IRQ (EPIC_IRQ_BASE + NUM_8259_INTERRUPTS)
DECL|macro|MPC10X_DMA0_IRQ
mdefine_line|#define MPC10X_DMA0_IRQ (EPIC_IRQ_BASE + 1 + NUM_8259_INTERRUPTS)
DECL|macro|MPC10X_DMA1_IRQ
mdefine_line|#define MPC10X_DMA1_IRQ (EPIC_IRQ_BASE + 2 + NUM_8259_INTERRUPTS)
macro_line|#else
DECL|macro|MPC10X_I2C_IRQ
mdefine_line|#define MPC10X_I2C_IRQ OCP_IRQ_NA
DECL|macro|MPC10X_DMA0_IRQ
mdefine_line|#define MPC10X_DMA0_IRQ OCP_IRQ_NA
DECL|macro|MPC10X_DMA1_IRQ
mdefine_line|#define MPC10X_DMA1_IRQ OCP_IRQ_NA
macro_line|#endif
DECL|variable|core_ocp
r_struct
id|ocp_def
id|core_ocp
(braket
)braket
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_INVALID
)brace
)brace
suffix:semicolon
DECL|variable|mpc10x_i2c_data
r_static
r_struct
id|ocp_fs_i2c_data
id|mpc10x_i2c_data
op_assign
(brace
dot
id|flags
op_assign
l_int|0
)brace
suffix:semicolon
DECL|variable|mpc10x_i2c_ocp
r_static
r_struct
id|ocp_def
id|mpc10x_i2c_ocp
op_assign
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_MOTOROLA
comma
dot
id|function
op_assign
id|OCP_FUNC_IIC
comma
dot
id|index
op_assign
l_int|0
comma
dot
id|additions
op_assign
op_amp
id|mpc10x_i2c_data
)brace
suffix:semicolon
DECL|variable|mpc10x_dma_ocp
r_static
r_struct
id|ocp_def
id|mpc10x_dma_ocp
(braket
l_int|2
)braket
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_MOTOROLA
comma
dot
id|function
op_assign
id|OCP_FUNC_DMA
comma
dot
id|index
op_assign
l_int|0
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_MOTOROLA
comma
dot
id|function
op_assign
id|OCP_FUNC_DMA
comma
dot
id|index
op_assign
l_int|1
)brace
)brace
suffix:semicolon
multiline_comment|/* Set resources to match bridge memory map */
r_void
id|__init
DECL|function|mpc10x_bridge_set_resources
id|mpc10x_bridge_set_resources
c_func
(paren
r_int
id|map
comma
r_struct
id|pci_controller
op_star
id|hose
)paren
(brace
r_switch
c_cond
(paren
id|map
)paren
(brace
r_case
id|MPC10X_MEM_MAP_A
suffix:colon
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;io_resource
comma
l_int|0x00000000
comma
l_int|0x3f7fffff
comma
id|IORESOURCE_IO
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
id|pci_init_resource
(paren
op_amp
id|hose-&gt;mem_resources
(braket
l_int|0
)braket
comma
l_int|0xc0000000
comma
l_int|0xfeffffff
comma
id|IORESOURCE_MEM
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MPC10X_MEM_MAP_B
suffix:colon
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;io_resource
comma
l_int|0x00000000
comma
l_int|0x00bfffff
comma
id|IORESOURCE_IO
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
id|pci_init_resource
(paren
op_amp
id|hose-&gt;mem_resources
(braket
l_int|0
)braket
comma
l_int|0x80000000
comma
l_int|0xfcffffff
comma
id|IORESOURCE_MEM
comma
l_string|&quot;PCI host bridge&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;mpc10x_bridge_set_resources: &quot;
l_string|&quot;Invalid map specified&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mpc10x:exit1&quot;
comma
l_int|0x100
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Do some initialization and put the EUMB registers at the specified address&n; * (also map the EPIC registers into virtual space--OpenPIC_Addr will be set).&n; *&n; * The EPIC is not on the 106, only the 8240 and 107.&n; */
r_int
id|__init
DECL|function|mpc10x_bridge_init
id|mpc10x_bridge_init
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|uint
id|current_map
comma
id|uint
id|new_map
comma
id|uint
id|phys_eumb_base
)paren
(brace
r_int
id|host_bridge
comma
id|picr1
comma
id|picr1_bit
suffix:semicolon
id|ulong
id|pci_config_addr
comma
id|pci_config_data
suffix:semicolon
id|u_char
id|pir
comma
id|byte
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mpc10x:enter&quot;
comma
l_int|0x100
)paren
suffix:semicolon
multiline_comment|/* Set up for current map so we can get at config regs */
r_switch
c_cond
(paren
id|current_map
)paren
(brace
r_case
id|MPC10X_MEM_MAP_A
suffix:colon
id|setup_indirect_pci
c_func
(paren
id|hose
comma
id|MPC10X_MAPA_CNFG_ADDR
comma
id|MPC10X_MAPA_CNFG_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MPC10X_MEM_MAP_B
suffix:colon
id|setup_indirect_pci
c_func
(paren
id|hose
comma
id|MPC10X_MAPB_CNFG_ADDR
comma
id|MPC10X_MAPB_CNFG_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;mpc10x_bridge_init: %s&bslash;n&quot;
comma
l_string|&quot;Invalid current map specified&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mpc10x:exit1&quot;
comma
l_int|0x100
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Make sure it&squot;s a supported bridge */
id|early_read_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|PCI_VENDOR_ID
comma
op_amp
id|host_bridge
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|host_bridge
)paren
(brace
r_case
id|MPC10X_BRIDGE_106
suffix:colon
r_case
id|MPC10X_BRIDGE_8240
suffix:colon
r_case
id|MPC10X_BRIDGE_107
suffix:colon
r_case
id|MPC10X_BRIDGE_8245
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mpc10x:exit2&quot;
comma
l_int|0x100
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|new_map
)paren
(brace
r_case
id|MPC10X_MEM_MAP_A
suffix:colon
id|MPC10X_SETUP_HOSE
c_func
(paren
id|hose
comma
id|A
)paren
suffix:semicolon
id|pci_config_addr
op_assign
id|MPC10X_MAPA_CNFG_ADDR
suffix:semicolon
id|pci_config_data
op_assign
id|MPC10X_MAPA_CNFG_DATA
suffix:semicolon
id|picr1_bit
op_assign
id|MPC10X_CFG_PICR1_ADDR_MAP_A
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MPC10X_MEM_MAP_B
suffix:colon
id|MPC10X_SETUP_HOSE
c_func
(paren
id|hose
comma
id|B
)paren
suffix:semicolon
id|pci_config_addr
op_assign
id|MPC10X_MAPB_CNFG_ADDR
suffix:semicolon
id|pci_config_data
op_assign
id|MPC10X_MAPB_CNFG_DATA
suffix:semicolon
id|picr1_bit
op_assign
id|MPC10X_CFG_PICR1_ADDR_MAP_B
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;mpc10x_bridge_init: %s&bslash;n&quot;
comma
l_string|&quot;Invalid new map specified&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mpc10x:exit3&quot;
comma
l_int|0x100
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Make bridge use the &squot;new_map&squot;, if not already usng it */
r_if
c_cond
(paren
id|current_map
op_ne
id|new_map
)paren
(brace
id|early_read_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PICR1_REG
comma
op_amp
id|picr1
)paren
suffix:semicolon
id|picr1
op_assign
(paren
id|picr1
op_amp
op_complement
id|MPC10X_CFG_PICR1_ADDR_MAP_MASK
)paren
op_or
id|picr1_bit
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PICR1_REG
comma
id|picr1
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
multiline_comment|/* Undo old mappings &amp; map in new cfg data/addr regs */
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|hose-&gt;cfg_addr
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|hose-&gt;cfg_data
)paren
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose
comma
id|pci_config_addr
comma
id|pci_config_data
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup resources to match map */
id|mpc10x_bridge_set_resources
c_func
(paren
id|new_map
comma
id|hose
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Want processor accesses of 0xFDxxxxxx to be mapped&n;&t; * to PCI memory space at 0x00000000.  Do not want&n;&t; * host bridge to respond to PCI memory accesses of&n;&t; * 0xFDxxxxxx.  Do not want host bridge to respond&n;&t; * to PCI memory addresses 0xFD000000-0xFDFFFFFF;&n;&t; * want processor accesses from 0x000A0000-0x000BFFFF&n;&t; * to be forwarded to system memory.&n;&t; *&n;&t; * Only valid if not in agent mode and using MAP B.&n;&t; */
r_if
c_cond
(paren
id|new_map
op_eq
id|MPC10X_MEM_MAP_B
)paren
(brace
id|early_read_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_MAPB_OPTIONS_REG
comma
op_amp
id|byte
)paren
suffix:semicolon
id|byte
op_and_assign
op_complement
(paren
id|MPC10X_CFG_MAPB_OPTIONS_PFAE
op_or
id|MPC10X_CFG_MAPB_OPTIONS_PCICH
op_or
id|MPC10X_CFG_MAPB_OPTIONS_PROCCH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host_bridge
op_ne
id|MPC10X_BRIDGE_106
)paren
(brace
id|byte
op_or_assign
id|MPC10X_CFG_MAPB_OPTIONS_CFAE
suffix:semicolon
)brace
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_MAPB_OPTIONS_REG
comma
id|byte
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|host_bridge
op_ne
id|MPC10X_BRIDGE_106
)paren
(brace
id|early_read_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PIR_REG
comma
op_amp
id|pir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pir
op_ne
id|MPC10X_CFG_PIR_HOST_BRIDGE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Host bridge in Agent mode&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Read or Set LMBAR &amp; PCSRBAR? */
)brace
multiline_comment|/* Set base addr of the 8240/107 EUMB.  */
id|early_write_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_EUMBBAR
comma
id|phys_eumb_base
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MPC10X_OPENPIC
multiline_comment|/* Map EPIC register part of EUMB into vitual memory  - PCORE&n;&t;&t;   uses an i8259 instead of EPIC. */
id|OpenPIC_Addr
op_assign
id|ioremap
c_func
(paren
id|phys_eumb_base
op_plus
id|MPC10X_EUMB_EPIC_OFFSET
comma
id|MPC10X_EUMB_EPIC_SIZE
)paren
suffix:semicolon
macro_line|#endif
id|mpc10x_i2c_ocp.paddr
op_assign
id|phys_eumb_base
op_plus
id|MPC10X_EUMB_I2C_OFFSET
suffix:semicolon
id|mpc10x_i2c_ocp.irq
op_assign
id|MPC10X_I2C_IRQ
suffix:semicolon
id|ocp_add_one_device
c_func
(paren
op_amp
id|mpc10x_i2c_ocp
)paren
suffix:semicolon
id|mpc10x_dma_ocp
(braket
l_int|0
)braket
dot
id|paddr
op_assign
id|phys_eumb_base
op_plus
id|MPC10X_EUMB_DMA_OFFSET
op_plus
l_int|0x100
suffix:semicolon
id|mpc10x_dma_ocp
(braket
l_int|0
)braket
dot
id|irq
op_assign
id|MPC10X_DMA0_IRQ
suffix:semicolon
id|ocp_add_one_device
c_func
(paren
op_amp
id|mpc10x_dma_ocp
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|mpc10x_dma_ocp
(braket
l_int|1
)braket
dot
id|paddr
op_assign
id|phys_eumb_base
op_plus
id|MPC10X_EUMB_DMA_OFFSET
op_plus
l_int|0x200
suffix:semicolon
id|mpc10x_dma_ocp
(braket
l_int|1
)braket
dot
id|irq
op_assign
id|MPC10X_DMA1_IRQ
suffix:semicolon
id|ocp_add_one_device
c_func
(paren
op_amp
id|mpc10x_dma_ocp
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MPC10X_STORE_GATHERING
id|mpc10x_enable_store_gathering
c_func
(paren
id|hose
)paren
suffix:semicolon
macro_line|#else
id|mpc10x_disable_store_gathering
c_func
(paren
id|hose
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * 8240 erratum 26, 8241/8245 erratum 29, 107 erratum 23: speculative&n;&t; * PCI reads may return stale data so turn off.&n;&t; */
r_if
c_cond
(paren
(paren
id|host_bridge
op_eq
id|MPC10X_BRIDGE_8240
)paren
op_logical_or
(paren
id|host_bridge
op_eq
id|MPC10X_BRIDGE_8245
)paren
op_logical_or
(paren
id|host_bridge
op_eq
id|MPC10X_BRIDGE_107
)paren
)paren
(brace
id|early_read_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PICR1_REG
comma
op_amp
id|picr1
)paren
suffix:semicolon
id|picr1
op_and_assign
op_complement
id|MPC10X_CFG_PICR1_SPEC_PCI_RD
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PICR1_REG
comma
id|picr1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * 8241/8245 erratum 28: PCI reads from local memory may return&n;&t; * stale data.  Workaround by setting PICR2[0] to disable copyback&n;&t; * optimization.  Oddly, the latest available user manual for the&n;&t; * 8245 (Rev 2., dated 10/2003) says PICR2[0] is reserverd.&n;&t; */
r_if
c_cond
(paren
id|host_bridge
op_eq
id|MPC10X_BRIDGE_8245
)paren
(brace
id|ulong
id|picr2
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PICR2_REG
comma
op_amp
id|picr2
)paren
suffix:semicolon
id|picr2
op_or_assign
id|MPC10X_CFG_PICR2_COPYBACK_OPT
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PICR2_REG
comma
id|picr2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;mpc10x:exit&quot;
comma
l_int|0x100
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Need to make our own PCI config space access macros because&n; * mpc10x_get_mem_size() is called before the data structures are set up for&n; * the &squot;early_xxx&squot; and &squot;indirect_xxx&squot; routines to work.&n; * Assumes bus 0.&n; */
DECL|macro|MPC10X_CFG_read
mdefine_line|#define MPC10X_CFG_read(val, addr, type, op)&t;*val = op((type)(addr))
DECL|macro|MPC10X_CFG_write
mdefine_line|#define MPC10X_CFG_write(val, addr, type, op)&t;op((type *)(addr), (val))
DECL|macro|MPC10X_PCI_OP
mdefine_line|#define MPC10X_PCI_OP(rw, size, type, op, mask)&t;&t;&t; &t;&bslash;&n;static void&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;mpc10x_##rw##_config_##size(uint *cfg_addr, uint *cfg_data, int devfn, int offset, type val) &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;out_be32(cfg_addr, &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t; ((offset &amp; 0xfc) &lt;&lt; 24) | (devfn &lt;&lt; 16)&t;&t;&bslash;&n;&t;&t; | (0 &lt;&lt; 8) | 0x80);&t;&t;&t;&t;&t;&bslash;&n;&t;MPC10X_CFG_##rw(val, cfg_data + (offset &amp; mask), type, op);&t;&bslash;&n;&t;return;    &t;&t;&t;&t;&t; &t;&t;&bslash;&n;}
id|MPC10X_PCI_OP
c_func
(paren
id|read
comma
id|byte
comma
id|u8
op_star
comma
id|in_8
comma
l_int|3
)paren
id|MPC10X_PCI_OP
c_func
(paren
id|read
comma
id|dword
comma
id|u32
op_star
comma
id|in_le32
comma
l_int|0
)paren
macro_line|#if 0&t;/* Not used */
id|MPC10X_PCI_OP
c_func
(paren
id|write
comma
id|byte
comma
id|u8
comma
id|out_8
comma
l_int|3
)paren
id|MPC10X_PCI_OP
c_func
(paren
id|read
comma
id|word
comma
id|u16
op_star
comma
id|in_le16
comma
l_int|2
)paren
id|MPC10X_PCI_OP
c_func
(paren
id|write
comma
id|word
comma
id|u16
comma
id|out_le16
comma
l_int|2
)paren
id|MPC10X_PCI_OP
c_func
(paren
id|write
comma
id|dword
comma
id|u32
comma
id|out_le32
comma
l_int|0
)paren
macro_line|#endif
multiline_comment|/*&n; * Read the memory controller registers to determine the amount of memory in&n; * the system.  This assumes that the firmware has correctly set up the memory&n; * controller registers.&n; */
r_int
r_int
id|__init
DECL|function|mpc10x_get_mem_size
id|mpc10x_get_mem_size
c_func
(paren
id|uint
id|mem_map
)paren
(brace
id|uint
op_star
id|config_addr
comma
op_star
id|config_data
comma
id|val
suffix:semicolon
id|ulong
id|start
comma
id|end
comma
id|total
comma
id|offset
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u_char
id|bank_enables
suffix:semicolon
r_switch
c_cond
(paren
id|mem_map
)paren
(brace
r_case
id|MPC10X_MEM_MAP_A
suffix:colon
id|config_addr
op_assign
(paren
id|uint
op_star
)paren
id|MPC10X_MAPA_CNFG_ADDR
suffix:semicolon
id|config_data
op_assign
(paren
id|uint
op_star
)paren
id|MPC10X_MAPA_CNFG_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MPC10X_MEM_MAP_B
suffix:colon
id|config_addr
op_assign
(paren
id|uint
op_star
)paren
id|MPC10X_MAPB_CNFG_ADDR
suffix:semicolon
id|config_data
op_assign
(paren
id|uint
op_star
)paren
id|MPC10X_MAPB_CNFG_DATA
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
id|mpc10x_read_config_byte
c_func
(paren
id|config_addr
comma
id|config_data
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_MCTLR_MEM_BANK_ENABLES
comma
op_amp
id|bank_enables
)paren
suffix:semicolon
id|total
op_assign
l_int|0
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bank_enables
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|offset
op_assign
id|MPC10X_MCTLR_MEM_START_1
op_plus
(paren
(paren
id|i
OG
l_int|3
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
id|mpc10x_read_config_dword
c_func
(paren
id|config_addr
comma
id|config_data
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|offset
comma
op_amp
id|val
)paren
suffix:semicolon
id|start
op_assign
(paren
id|val
op_rshift
(paren
(paren
id|i
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
id|offset
op_assign
id|MPC10X_MCTLR_EXT_MEM_START_1
op_plus
(paren
(paren
id|i
OG
l_int|3
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
id|mpc10x_read_config_dword
c_func
(paren
id|config_addr
comma
id|config_data
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|offset
comma
op_amp
id|val
)paren
suffix:semicolon
id|val
op_assign
(paren
id|val
op_rshift
(paren
(paren
id|i
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0x03
suffix:semicolon
id|start
op_assign
(paren
id|val
op_lshift
l_int|28
)paren
op_or
(paren
id|start
op_lshift
l_int|20
)paren
suffix:semicolon
id|offset
op_assign
id|MPC10X_MCTLR_MEM_END_1
op_plus
(paren
(paren
id|i
OG
l_int|3
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
id|mpc10x_read_config_dword
c_func
(paren
id|config_addr
comma
id|config_data
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|offset
comma
op_amp
id|val
)paren
suffix:semicolon
id|end
op_assign
(paren
id|val
op_rshift
(paren
(paren
id|i
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
id|offset
op_assign
id|MPC10X_MCTLR_EXT_MEM_END_1
op_plus
(paren
(paren
id|i
OG
l_int|3
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
id|mpc10x_read_config_dword
c_func
(paren
id|config_addr
comma
id|config_data
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|offset
comma
op_amp
id|val
)paren
suffix:semicolon
id|val
op_assign
(paren
id|val
op_rshift
(paren
(paren
id|i
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0x03
suffix:semicolon
id|end
op_assign
(paren
id|val
op_lshift
l_int|28
)paren
op_or
(paren
id|end
op_lshift
l_int|20
)paren
op_or
l_int|0xfffff
suffix:semicolon
id|total
op_add_assign
(paren
id|end
op_minus
id|start
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_return
id|total
suffix:semicolon
)brace
r_int
id|__init
DECL|function|mpc10x_enable_store_gathering
id|mpc10x_enable_store_gathering
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
)paren
(brace
id|uint
id|picr1
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PICR1_REG
comma
op_amp
id|picr1
)paren
suffix:semicolon
id|picr1
op_or_assign
id|MPC10X_CFG_PICR1_ST_GATH_EN
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PICR1_REG
comma
id|picr1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
id|__init
DECL|function|mpc10x_disable_store_gathering
id|mpc10x_disable_store_gathering
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
)paren
(brace
id|uint
id|picr1
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PICR1_REG
comma
op_amp
id|picr1
)paren
suffix:semicolon
id|picr1
op_and_assign
op_complement
id|MPC10X_CFG_PICR1_ST_GATH_EN
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|MPC10X_CFG_PICR1_REG
comma
id|picr1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MPC10X_OPENPIC
DECL|function|mpc10x_set_openpic
r_void
id|__init
id|mpc10x_set_openpic
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Map external IRQs */
id|openpic_set_sources
c_func
(paren
l_int|0
comma
id|EPIC_IRQ_BASE
comma
id|OpenPIC_Addr
op_plus
l_int|0x10200
)paren
suffix:semicolon
multiline_comment|/* Skip reserved space and map i2c and DMA Ch[01] */
id|openpic_set_sources
c_func
(paren
id|EPIC_IRQ_BASE
comma
l_int|3
comma
id|OpenPIC_Addr
op_plus
l_int|0x11020
)paren
suffix:semicolon
multiline_comment|/* Skip reserved space and map Message Unit Interrupt (I2O) */
id|openpic_set_sources
c_func
(paren
id|EPIC_IRQ_BASE
op_plus
l_int|3
comma
l_int|1
comma
id|OpenPIC_Addr
op_plus
l_int|0x110C0
)paren
suffix:semicolon
id|openpic_init
c_func
(paren
id|NUM_8259_INTERRUPTS
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
