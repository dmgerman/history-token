multiline_comment|/*&n; * arch/ppc/syslib/pplus_common.c&n; * &n; * Common Motorola PowerPlus Platform--really Falcon/Raven or HAWK.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/pplus.h&gt;
multiline_comment|/*&n; * The Falcon/Raven and HAWK has 4 sets of registers:&n; *   1) PPC Registers which define the mappings from PPC bus to PCI bus,&n; *      etc.&n; *   2) PCI Registers which define the mappings from PCI bus to PPC bus and the&n; *      MPIC base address.&n; *   3) MPIC registers.&n; *   4) System Memory Controller (SMC) registers.&n; */
multiline_comment|/*&n; * Initialize the Motorola MCG Raven or HAWK host bridge.&n; *&n; * This means setting up the PPC bus to PCI memory and I/O space mappings,&n; * setting the PCI memory space address of the MPIC (mapped straight&n; * through), and ioremap&squot;ing the mpic registers.&n; * This routine will set the PCI_CONFIG_ADDR or PCI_CONFIG_DATA&n; * addresses based on the PCI I/O address that is passed in.&n; * &squot;OpenPIC_Addr&squot; will be set correctly by this routine.&n; */
r_int
id|__init
DECL|function|pplus_init
id|pplus_init
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|uint
id|ppc_reg_base
comma
id|ulong
id|processor_pci_mem_start
comma
id|ulong
id|processor_pci_mem_end
comma
id|ulong
id|processor_pci_io_start
comma
id|ulong
id|processor_pci_io_end
comma
id|ulong
id|processor_mpic_base
)paren
(brace
id|uint
id|addr
comma
id|offset
suffix:semicolon
multiline_comment|/*&n;&t; * Some sanity checks...&n;&t; */
r_if
c_cond
(paren
(paren
(paren
id|processor_pci_mem_start
op_amp
l_int|0xffff0000
)paren
op_ne
id|processor_pci_mem_start
)paren
op_logical_or
(paren
(paren
id|processor_pci_io_start
op_amp
l_int|0xffff0000
)paren
op_ne
id|processor_pci_io_start
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pplus_init: %s&bslash;n&quot;
comma
l_string|&quot;PPC to PCI mappings must start on 64 KB boundaries&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|processor_pci_mem_end
op_amp
l_int|0x0000ffff
)paren
op_ne
l_int|0x0000ffff
)paren
op_logical_or
(paren
(paren
id|processor_pci_io_end
op_amp
l_int|0x0000ffff
)paren
op_ne
l_int|0x0000ffff
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pplus_init: PPC to PCI mappings %s&bslash;n&quot;
comma
l_string|&quot;must end just before a 64 KB boundaries&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|processor_pci_mem_end
op_minus
id|processor_pci_mem_start
)paren
op_ne
(paren
id|hose-&gt;mem_space.end
op_minus
id|hose-&gt;mem_space.start
)paren
)paren
op_logical_or
(paren
(paren
id|processor_pci_io_end
op_minus
id|processor_pci_io_start
)paren
op_ne
(paren
id|hose-&gt;io_space.end
op_minus
id|hose-&gt;io_space.start
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pplus_init: %s&bslash;n&quot;
comma
l_string|&quot;PPC and PCI memory or I/O space sizes don&squot;t match&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|processor_mpic_base
op_amp
l_int|0xfffc0000
)paren
op_ne
id|processor_mpic_base
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pplus_init: %s&bslash;n&quot;
comma
l_string|&quot;MPIC address must start on 256 MB boundary&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pci_dram_offset
op_amp
l_int|0xffff0000
)paren
op_ne
id|pci_dram_offset
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pplus_init: %s&bslash;n&quot;
comma
l_string|&quot;pci_dram_offset must be multiple of 64 KB&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Disable previous PPC-&gt;PCI mappings.&n;&t; */
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|PPLUS_PPC_XSOFF0_OFF
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|PPLUS_PPC_XSOFF1_OFF
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|PPLUS_PPC_XSOFF2_OFF
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|PPLUS_PPC_XSOFF3_OFF
)paren
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Program the XSADD/XSOFF registers to set up the PCI Mem &amp; I/O&n;&t; * space mappings.  These are the mappings going from the processor to&n;&t; * the PCI bus.&n;&t; *&n;&t; * Note: Don&squot;t need to &squot;AND&squot; start/end addresses with 0xffff0000&n;&t; *&t; because sanity check above ensures that they are properly&n;&t; *&t; aligned.&n;&t; */
multiline_comment|/* Set up PPC-&gt;PCI Mem mapping */
id|addr
op_assign
id|processor_pci_mem_start
op_or
(paren
id|processor_pci_mem_end
op_rshift
l_int|16
)paren
suffix:semicolon
id|offset
op_assign
(paren
id|hose-&gt;mem_space.start
op_minus
id|processor_pci_mem_start
)paren
op_or
l_int|0xd2
suffix:semicolon
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|PPLUS_PPC_XSADD0_OFF
)paren
comma
id|addr
)paren
suffix:semicolon
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|PPLUS_PPC_XSOFF0_OFF
)paren
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* Set up PPC-&gt;MPIC mapping on the bridge */
id|addr
op_assign
id|processor_mpic_base
op_or
(paren
(paren
(paren
id|processor_mpic_base
op_plus
id|PPLUS_MPIC_SIZE
)paren
op_rshift
l_int|16
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|offset
op_assign
l_int|0xc2
suffix:semicolon
multiline_comment|/* No write posting for this PCI Mem space */
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|PPLUS_PPC_XSADD1_OFF
)paren
comma
id|addr
)paren
suffix:semicolon
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|PPLUS_PPC_XSOFF1_OFF
)paren
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* Set up PPC-&gt;PCI I/O mapping -- Contiguous I/O space */
id|addr
op_assign
id|processor_pci_io_start
op_or
(paren
id|processor_pci_io_end
op_rshift
l_int|16
)paren
suffix:semicolon
id|offset
op_assign
(paren
id|hose-&gt;io_space.start
op_minus
id|processor_pci_io_start
)paren
op_or
l_int|0xc0
suffix:semicolon
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|PPLUS_PPC_XSADD3_OFF
)paren
comma
id|addr
)paren
suffix:semicolon
id|out_be32
c_func
(paren
(paren
id|uint
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|PPLUS_PPC_XSOFF3_OFF
)paren
comma
id|offset
)paren
suffix:semicolon
id|hose-&gt;io_base_virt
op_assign
(paren
r_void
op_star
)paren
id|ioremap
c_func
(paren
id|processor_pci_io_start
comma
(paren
id|processor_pci_io_end
op_minus
id|processor_pci_io_start
op_plus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the indirect method of accessing PCI config space.&n;&t; * The PCI config addr/data pair based on start addr of PCI I/O space.&n;&t; */
id|setup_indirect_pci
c_func
(paren
id|hose
comma
id|processor_pci_io_start
op_plus
id|PPLUS_PCI_CONFIG_ADDR_OFF
comma
id|processor_pci_io_start
op_plus
id|PPLUS_PCI_CONFIG_DATA_OFF
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable previous PCI-&gt;PPC mappings.&n;&t; */
multiline_comment|/* XXXX Put in mappings from PCI bus to processor bus XXXX */
multiline_comment|/*&n;&t; * Disable MPIC response to PCI I/O space (BAR 0).&n;&t; * Make MPIC respond to PCI Mem space at specified address.&n;&t; * (BAR 1).&n;&t; */
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
id|PCI_BASE_ADDRESS_0
comma
l_int|0x00000000
op_or
l_int|0x1
)paren
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
id|PCI_BASE_ADDRESS_1
comma
id|processor_mpic_base
op_or
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* Map MPIC into vitual memory */
id|OpenPIC_Addr
op_assign
id|ioremap
c_func
(paren
id|processor_mpic_base
comma
id|PPLUS_MPIC_SIZE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Find the amount of RAM present.&n; * This assumes that PPCBug has initialized the memory controller (SMC)&n; * on the Falcon/HAWK correctly (i.e., it does no sanity checking).&n; * It also assumes that the memory base registers are set to configure the&n; * memory as contigous starting with &quot;RAM A BASE&quot;, &quot;RAM B BASE&quot;, etc.&n; * however, RAM base registers can be skipped (e.g. A, B, C are set,&n; * D is skipped but E is set is okay).&n; */
DECL|macro|MB
mdefine_line|#define&t;MB&t;(1024*1024)
DECL|variable|__initdata
r_static
id|uint
id|reg_offset_table
(braket
)braket
id|__initdata
op_assign
(brace
id|PPLUS_SMC_RAM_A_SIZE_REG_OFF
comma
id|PPLUS_SMC_RAM_B_SIZE_REG_OFF
comma
id|PPLUS_SMC_RAM_C_SIZE_REG_OFF
comma
id|PPLUS_SMC_RAM_D_SIZE_REG_OFF
comma
id|PPLUS_SMC_RAM_E_SIZE_REG_OFF
comma
id|PPLUS_SMC_RAM_F_SIZE_REG_OFF
comma
id|PPLUS_SMC_RAM_G_SIZE_REG_OFF
comma
id|PPLUS_SMC_RAM_H_SIZE_REG_OFF
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|uint
id|falcon_size_table
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0
op_star
id|MB
comma
multiline_comment|/* 0 ==&gt;    0 MB */
l_int|16
op_star
id|MB
comma
multiline_comment|/* 1 ==&gt;   16 MB */
l_int|32
op_star
id|MB
comma
multiline_comment|/* 2 ==&gt;   32 MB */
l_int|64
op_star
id|MB
comma
multiline_comment|/* 3 ==&gt;   64 MB */
l_int|128
op_star
id|MB
comma
multiline_comment|/* 4 ==&gt;  128 MB */
l_int|256
op_star
id|MB
comma
multiline_comment|/* 5 ==&gt;  256 MB */
l_int|1024
op_star
id|MB
comma
multiline_comment|/* 6 ==&gt; 1024 MB (1 GB) */
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|uint
id|hawk_size_table
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0
op_star
id|MB
comma
multiline_comment|/* 0 ==&gt;    0 MB */
l_int|32
op_star
id|MB
comma
multiline_comment|/* 1 ==&gt;   32 MB */
l_int|64
op_star
id|MB
comma
multiline_comment|/* 2 ==&gt;   64 MB */
l_int|64
op_star
id|MB
comma
multiline_comment|/* 3 ==&gt;   64 MB */
l_int|128
op_star
id|MB
comma
multiline_comment|/* 4 ==&gt;  128 MB */
l_int|128
op_star
id|MB
comma
multiline_comment|/* 5 ==&gt;  128 MB */
l_int|128
op_star
id|MB
comma
multiline_comment|/* 6 ==&gt;  128 MB */
l_int|256
op_star
id|MB
comma
multiline_comment|/* 7 ==&gt;  256 MB */
l_int|256
op_star
id|MB
comma
multiline_comment|/* 8 ==&gt;  256 MB */
l_int|512
op_star
id|MB
comma
multiline_comment|/* 9 ==&gt;  512 MB */
)brace
suffix:semicolon
multiline_comment|/*&n; * *** WARNING: You MUST have a BAT set up to map in the SMC regs ***&n; *&n; * Read the memory controller&squot;s registers to determine the amount of system&n; * memory.  Assumes that the memory controller registers are already mapped&n; * into virtual memory--too early to use ioremap().&n; */
r_int
r_int
id|__init
DECL|function|pplus_get_mem_size
id|pplus_get_mem_size
c_func
(paren
id|uint
id|smc_base
)paren
(brace
r_int
r_int
id|total
suffix:semicolon
r_int
id|i
comma
id|size_table_entries
comma
id|reg_limit
suffix:semicolon
id|uint
id|vend_dev_id
suffix:semicolon
id|uint
op_star
id|size_table
suffix:semicolon
id|u_char
id|val
suffix:semicolon
id|vend_dev_id
op_assign
id|in_be32
c_func
(paren
(paren
id|uint
op_star
)paren
id|smc_base
op_plus
id|PCI_VENDOR_ID
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|vend_dev_id
op_amp
l_int|0xffff0000
)paren
op_rshift
l_int|16
)paren
op_ne
id|PCI_VENDOR_ID_MOTOROLA
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pplus_get_mem_size: %s (0x%x)&bslash;n&quot;
comma
l_string|&quot;Not a Motorola Memory Controller&quot;
comma
id|vend_dev_id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|vend_dev_id
op_and_assign
l_int|0x0000ffff
suffix:semicolon
r_if
c_cond
(paren
id|vend_dev_id
op_eq
id|PCI_DEVICE_ID_MOTOROLA_FALCON
)paren
(brace
id|size_table
op_assign
id|falcon_size_table
suffix:semicolon
id|size_table_entries
op_assign
r_sizeof
(paren
id|falcon_size_table
)paren
op_div
r_sizeof
(paren
id|falcon_size_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|reg_limit
op_assign
id|PPLUS_FALCON_SMC_REG_COUNT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|vend_dev_id
op_eq
id|PCI_DEVICE_ID_MOTOROLA_HAWK
)paren
(brace
id|size_table
op_assign
id|hawk_size_table
suffix:semicolon
id|size_table_entries
op_assign
r_sizeof
(paren
id|hawk_size_table
)paren
op_div
r_sizeof
(paren
id|hawk_size_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|reg_limit
op_assign
id|PPLUS_HAWK_SMC_REG_COUNT
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;pplus_get_mem_size: %s (0x%x)&bslash;n&quot;
comma
l_string|&quot;Not a Falcon or HAWK&quot;
comma
id|vend_dev_id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|total
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Check every reg because PPCBug may skip some */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|reg_limit
suffix:semicolon
id|i
op_increment
)paren
(brace
id|val
op_assign
id|in_8
c_func
(paren
(paren
id|u_char
op_star
)paren
(paren
id|smc_base
op_plus
id|reg_offset_table
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|0x80
)paren
(brace
multiline_comment|/* If enabled */
id|val
op_and_assign
l_int|0x0f
suffix:semicolon
multiline_comment|/* Don&squot;t go past end of size_table */
r_if
c_cond
(paren
id|val
OL
id|size_table_entries
)paren
(brace
id|total
op_add_assign
id|size_table
(braket
id|val
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Register not set correctly */
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
id|total
suffix:semicolon
)brace
r_int
id|__init
DECL|function|pplus_mpic_init
id|pplus_mpic_init
c_func
(paren
r_int
r_int
id|pci_mem_offset
)paren
(brace
r_int
r_int
id|devid
suffix:semicolon
r_int
r_int
id|pci_membase
suffix:semicolon
multiline_comment|/* Check the first PCI device to see if it is a Raven or Hawk. */
id|early_read_config_word
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|PCI_DEVICE_ID
comma
op_amp
id|devid
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|devid
)paren
(brace
r_case
id|PCI_DEVICE_ID_MOTOROLA_RAVEN
suffix:colon
r_case
id|PCI_DEVICE_ID_MOTOROLA_HAWK
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|OpenPIC_Addr
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Read the memory base register. */
id|early_read_config_dword
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|PCI_BASE_ADDRESS_1
comma
op_amp
id|pci_membase
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_membase
op_eq
l_int|0
)paren
(brace
id|OpenPIC_Addr
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Map the MPIC registers to virtual memory. */
id|OpenPIC_Addr
op_assign
id|ioremap
c_func
(paren
id|pci_membase
op_plus
id|pci_mem_offset
comma
l_int|0x22000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
