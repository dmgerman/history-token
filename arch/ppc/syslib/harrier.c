multiline_comment|/*&n; * arch/ppc/syslib/harrier.c&n; * &n; * Motorola MCG Harrier northbridge/memory controller support&n; *&n; * Author: Dale Farnsworth&n; *         dale.farnsworth@mvista.com&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/harrier.h&gt;
multiline_comment|/*&n; * Initialize the Motorola MCG Harrier host bridge.&n; *&n; * This means setting up the PPC bus to PCI memory and I/O space mappings,&n; * setting the PCI memory space address of the MPIC (mapped straight&n; * through), and ioremap&squot;ing the mpic registers.&n; * &squot;OpenPIC_Addr&squot; will be set correctly by this routine.&n; * This routine will not change the PCI_CONFIG_ADDR or PCI_CONFIG_DATA&n; * addresses and assumes that the mapping of PCI memory space back to system&n; * memory is set up correctly by PPCBug.&n; */
r_int
id|__init
DECL|function|harrier_init
id|harrier_init
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
l_string|&quot;harrier_init: %s&bslash;n&quot;
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
l_string|&quot;harrier_init: PPC to PCI mappings %s&bslash;n&quot;
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
l_string|&quot;harrier_init: %s&bslash;n&quot;
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
l_string|&quot;harrier_init: %s&bslash;n&quot;
comma
l_string|&quot;MPIC address must start on 256 KB boundary&quot;
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
l_string|&quot;harrier_init: %s&bslash;n&quot;
comma
l_string|&quot;pci_dram_offset must be multiple of 64 KB&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Program the OTAD/OTOF registers to set up the PCI Mem &amp; I/O&n;&t; * space mappings.  These are the mappings going from the processor to&n;&t; * the PCI bus.&n;&t; *&n;&t; * Note: Don&squot;t need to &squot;AND&squot; start/end addresses with 0xffff0000&n;&t; *&t; because sanity check above ensures that they are properly&n;&t; *&t; aligned.&n;&t; */
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
l_int|0x92
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
id|HARRIER_OTAD0_OFF
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
id|HARRIER_OTOF0_OFF
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
l_int|0x80
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
id|HARRIER_OTAD1_OFF
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
id|HARRIER_OTOF1_OFF
)paren
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* Enable MPIC */
id|OpenPIC_Addr
op_assign
(paren
r_void
op_star
)paren
id|processor_mpic_base
suffix:semicolon
id|addr
op_assign
(paren
id|processor_mpic_base
op_rshift
l_int|16
)paren
op_or
l_int|1
suffix:semicolon
id|out_be16
c_func
(paren
(paren
id|ushort
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|HARRIER_MBAR_OFF
)paren
comma
id|addr
)paren
suffix:semicolon
id|out_8
c_func
(paren
(paren
id|u_char
op_star
)paren
(paren
id|ppc_reg_base
op_plus
id|HARRIER_MPIC_CSR_OFF
)paren
comma
id|HARRIER_MPIC_OPI_ENABLE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Find the amount of RAM present.&n; * This assumes that PPCBug has initialized the memory controller (SMC)&n; * on the Harrier correctly (i.e., it does no sanity checking).&n; * It also assumes that the memory base registers are set to configure the&n; * memory as contigous starting with &quot;RAM A BASE&quot;, &quot;RAM B BASE&quot;, etc.&n; * however, RAM base registers can be skipped (e.g. A, B, C are set,&n; * D is skipped but E is set is okay).&n; */
DECL|macro|MB
mdefine_line|#define&t;MB&t;(1024*1024UL)
DECL|variable|__initdata
r_static
id|uint
id|harrier_size_table
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
l_int|256
op_star
id|MB
comma
multiline_comment|/* 9 ==&gt;  256 MB */
l_int|512
op_star
id|MB
comma
multiline_comment|/* a ==&gt;  512 MB */
l_int|512
op_star
id|MB
comma
multiline_comment|/* b ==&gt;  512 MB */
l_int|512
op_star
id|MB
comma
multiline_comment|/* c ==&gt;  512 MB */
l_int|1024
op_star
id|MB
comma
multiline_comment|/* d ==&gt; 1024 MB */
l_int|1024
op_star
id|MB
comma
multiline_comment|/* e ==&gt; 1024 MB */
l_int|2048
op_star
id|MB
comma
multiline_comment|/* f ==&gt; 2048 MB */
)brace
suffix:semicolon
multiline_comment|/*&n; * *** WARNING: You MUST have a BAT set up to map in the XCSR regs ***&n; *&n; * Read the memory controller&squot;s registers to determine the amount of system&n; * memory.  Assumes that the memory controller registers are already mapped&n; * into virtual memory--too early to use ioremap().&n; */
r_int
r_int
id|__init
DECL|function|harrier_get_mem_size
id|harrier_get_mem_size
c_func
(paren
id|uint
id|xcsr_base
)paren
(brace
id|ulong
id|last_addr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|uint
id|vend_dev_id
suffix:semicolon
id|uint
op_star
id|size_table
suffix:semicolon
id|uint
id|val
suffix:semicolon
id|uint
op_star
id|csrp
suffix:semicolon
id|uint
id|size
suffix:semicolon
r_int
id|size_table_entries
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
id|xcsr_base
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
l_string|&quot;harrier_get_mem_size: %s (0x%x)&bslash;n&quot;
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
id|PCI_DEVICE_ID_MOTOROLA_HARRIER
)paren
(brace
id|size_table
op_assign
id|harrier_size_table
suffix:semicolon
id|size_table_entries
op_assign
r_sizeof
(paren
id|harrier_size_table
)paren
op_div
r_sizeof
(paren
id|harrier_size_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;harrier_get_mem_size: %s (0x%x)&bslash;n&quot;
comma
l_string|&quot;Not a Harrier&quot;
comma
id|vend_dev_id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|last_addr
op_assign
l_int|0
suffix:semicolon
id|csrp
op_assign
(paren
id|uint
op_star
)paren
(paren
id|xcsr_base
op_plus
id|HARRIER_SDBA_OFF
)paren
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
id|val
op_assign
id|in_be32
c_func
(paren
id|csrp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|0x100
)paren
(brace
multiline_comment|/* If enabled */
id|size
op_assign
id|val
op_rshift
id|HARRIER_SDB_SIZE_SHIFT
suffix:semicolon
id|size
op_and_assign
id|HARRIER_SDB_SIZE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ge
id|size_table_entries
)paren
(brace
r_break
suffix:semicolon
multiline_comment|/* Register not set correctly */
)brace
id|size
op_assign
id|size_table
(braket
id|size
)braket
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
id|size
op_minus
l_int|1
)paren
suffix:semicolon
id|val
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|val
OG
id|last_addr
)paren
(brace
id|last_addr
op_assign
id|val
suffix:semicolon
)brace
)brace
)brace
r_return
id|last_addr
suffix:semicolon
)brace
eof
