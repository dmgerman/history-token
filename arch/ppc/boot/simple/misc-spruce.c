multiline_comment|/*&n; * arch/ppc/boot/spruce/misc.c&n; *&n; * Misc. bootloader code for IBM Spruce reference platform&n; *&n; * Authors: Johnnie Peters &lt;jpeters@mvista.com&gt;&n; *&t;    Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Derived from arch/ppc/boot/prep/misc.c&n; *&n; * 2000-2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
r_extern
r_int
r_int
id|decompress_kernel
c_func
(paren
r_int
r_int
id|load_addr
comma
r_int
id|num_words
comma
r_int
r_int
id|cksum
)paren
suffix:semicolon
multiline_comment|/* Define some important locations of the Spruce. */
DECL|macro|SPRUCE_PCI_CONFIG_ADDR
mdefine_line|#define SPRUCE_PCI_CONFIG_ADDR&t;0xfec00000
DECL|macro|SPRUCE_PCI_CONFIG_DATA
mdefine_line|#define SPRUCE_PCI_CONFIG_DATA&t;0xfec00004
multiline_comment|/* PCI configuration space access routines. */
DECL|variable|pci_config_address
r_int
r_int
op_star
id|pci_config_address
op_assign
(paren
r_int
r_int
op_star
)paren
id|SPRUCE_PCI_CONFIG_ADDR
suffix:semicolon
DECL|variable|pci_config_data
r_int
r_char
op_star
id|pci_config_data
op_assign
(paren
r_int
r_char
op_star
)paren
id|SPRUCE_PCI_CONFIG_DATA
suffix:semicolon
DECL|function|cpc700_pcibios_read_config_byte
r_void
id|cpc700_pcibios_read_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
op_star
id|val
)paren
(brace
id|out_le32
c_func
(paren
id|pci_config_address
comma
(paren
(paren
(paren
id|bus
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|dev_fn
op_lshift
l_int|8
)paren
op_or
(paren
id|offset
op_amp
l_int|0xfc
)paren
op_or
l_int|0x80000000
)paren
)paren
suffix:semicolon
op_star
id|val
op_assign
(paren
id|in_le32
c_func
(paren
(paren
r_int
op_star
)paren
id|pci_config_data
)paren
op_rshift
(paren
l_int|8
op_star
(paren
id|offset
op_amp
l_int|3
)paren
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
DECL|function|cpc700_pcibios_write_config_byte
r_void
id|cpc700_pcibios_write_config_byte
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_char
id|val
)paren
(brace
id|out_le32
c_func
(paren
id|pci_config_address
comma
(paren
(paren
(paren
id|bus
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|dev_fn
op_lshift
l_int|8
)paren
op_or
(paren
id|offset
op_amp
l_int|0xfc
)paren
op_or
l_int|0x80000000
)paren
)paren
suffix:semicolon
id|out_8
c_func
(paren
id|pci_config_data
op_plus
(paren
id|offset
op_amp
l_int|3
)paren
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|cpc700_pcibios_read_config_word
r_void
id|cpc700_pcibios_read_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
id|out_le32
c_func
(paren
id|pci_config_address
comma
(paren
(paren
(paren
id|bus
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|dev_fn
op_lshift
l_int|8
)paren
op_or
(paren
id|offset
op_amp
l_int|0xfc
)paren
op_or
l_int|0x80000000
)paren
)paren
suffix:semicolon
op_star
id|val
op_assign
id|in_le16
c_func
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|pci_config_data
op_plus
(paren
id|offset
op_amp
l_int|3
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|cpc700_pcibios_write_config_word
r_void
id|cpc700_pcibios_write_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
(brace
id|out_le32
c_func
(paren
id|pci_config_address
comma
(paren
(paren
(paren
id|bus
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|dev_fn
op_lshift
l_int|8
)paren
op_or
(paren
id|offset
op_amp
l_int|0xfc
)paren
op_or
l_int|0x80000000
)paren
)paren
suffix:semicolon
id|out_le16
c_func
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|pci_config_data
op_plus
(paren
id|offset
op_amp
l_int|3
)paren
)paren
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|cpc700_pcibios_read_config_dword
r_void
id|cpc700_pcibios_read_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
id|out_le32
c_func
(paren
id|pci_config_address
comma
(paren
(paren
(paren
id|bus
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|dev_fn
op_lshift
l_int|8
)paren
op_or
(paren
id|offset
op_amp
l_int|0xfc
)paren
op_or
l_int|0x80000000
)paren
)paren
suffix:semicolon
op_star
id|val
op_assign
id|in_le32
c_func
(paren
(paren
r_int
op_star
)paren
id|pci_config_data
)paren
suffix:semicolon
)brace
DECL|function|cpc700_pcibios_write_config_dword
r_void
id|cpc700_pcibios_write_config_dword
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
(brace
id|out_le32
c_func
(paren
id|pci_config_address
comma
(paren
(paren
(paren
id|bus
op_amp
l_int|0xff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|dev_fn
op_lshift
l_int|8
)paren
op_or
(paren
id|offset
op_amp
l_int|0xfc
)paren
op_or
l_int|0x80000000
)paren
)paren
suffix:semicolon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
id|pci_config_data
comma
id|val
)paren
suffix:semicolon
)brace
DECL|macro|PCNET32_WIO_RDP
mdefine_line|#define PCNET32_WIO_RDP&t;&t;0x10
DECL|macro|PCNET32_WIO_RAP
mdefine_line|#define PCNET32_WIO_RAP&t;&t;0x12
DECL|macro|PCNET32_WIO_RESET
mdefine_line|#define PCNET32_WIO_RESET&t;0x14
DECL|macro|PCNET32_DWIO_RDP
mdefine_line|#define PCNET32_DWIO_RDP&t;0x10
DECL|macro|PCNET32_DWIO_RAP
mdefine_line|#define PCNET32_DWIO_RAP&t;0x14
DECL|macro|PCNET32_DWIO_RESET
mdefine_line|#define PCNET32_DWIO_RESET&t;0x18
multiline_comment|/* Processor interface config register access */
DECL|macro|PIFCFGADDR
mdefine_line|#define PIFCFGADDR 0xff500000
DECL|macro|PIFCFGDATA
mdefine_line|#define PIFCFGDATA 0xff500004
DECL|macro|PLBMIFOPT
mdefine_line|#define PLBMIFOPT 0x18 /* PLB Master Interface Options */
DECL|macro|MEM_MBEN
mdefine_line|#define MEM_MBEN&t;0x24
DECL|macro|MEM_TYPE
mdefine_line|#define MEM_TYPE&t;0x28
DECL|macro|MEM_B1SA
mdefine_line|#define MEM_B1SA&t;0x3c
DECL|macro|MEM_B1EA
mdefine_line|#define MEM_B1EA&t;0x5c
DECL|macro|MEM_B2SA
mdefine_line|#define MEM_B2SA&t;0x40
DECL|macro|MEM_B2EA
mdefine_line|#define MEM_B2EA&t;0x60
r_int
r_int
DECL|function|get_mem_size
id|get_mem_size
c_func
(paren
r_void
)paren
(brace
r_int
id|loop
suffix:semicolon
r_int
r_int
id|mem_size
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|mem_mben
suffix:semicolon
r_int
r_int
id|mem_type
suffix:semicolon
r_int
r_int
id|mem_start
suffix:semicolon
r_int
r_int
id|mem_end
suffix:semicolon
r_volatile
r_int
op_star
id|mem_addr
op_assign
(paren
r_int
op_star
)paren
l_int|0xff500008
suffix:semicolon
r_volatile
r_int
op_star
id|mem_data
op_assign
(paren
r_int
op_star
)paren
l_int|0xff50000c
suffix:semicolon
multiline_comment|/* Get the size of memory from the memory controller. */
op_star
id|mem_addr
op_assign
id|MEM_MBEN
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|mem_mben
op_assign
op_star
id|mem_data
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|1000
suffix:semicolon
id|loop
op_increment
)paren
(brace
suffix:semicolon
)brace
op_star
id|mem_addr
op_assign
id|MEM_TYPE
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|mem_type
op_assign
op_star
id|mem_data
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|1000
suffix:semicolon
id|loop
op_increment
)paren
(brace
suffix:semicolon
)brace
op_star
id|mem_addr
op_assign
id|MEM_TYPE
suffix:semicolon
multiline_comment|/* Confirm bank 1 has DRAM memory */
r_if
c_cond
(paren
(paren
id|mem_mben
op_amp
l_int|0x40000000
)paren
op_logical_and
(paren
(paren
id|mem_type
op_amp
l_int|0x30000000
)paren
op_eq
l_int|0x10000000
)paren
)paren
(brace
op_star
id|mem_addr
op_assign
id|MEM_B1SA
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|mem_start
op_assign
op_star
id|mem_data
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|1000
suffix:semicolon
id|loop
op_increment
)paren
(brace
suffix:semicolon
)brace
op_star
id|mem_addr
op_assign
id|MEM_B1EA
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|mem_end
op_assign
op_star
id|mem_data
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|1000
suffix:semicolon
id|loop
op_increment
)paren
(brace
suffix:semicolon
)brace
id|mem_size
op_assign
id|mem_end
op_minus
id|mem_start
op_plus
l_int|0x100000
suffix:semicolon
)brace
multiline_comment|/* Confirm bank 2 has DRAM memory */
r_if
c_cond
(paren
(paren
id|mem_mben
op_amp
l_int|0x20000000
)paren
op_logical_and
(paren
(paren
id|mem_type
op_amp
l_int|0xc000000
)paren
op_eq
l_int|0x4000000
)paren
)paren
(brace
op_star
id|mem_addr
op_assign
id|MEM_B2SA
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|mem_start
op_assign
op_star
id|mem_data
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|1000
suffix:semicolon
id|loop
op_increment
)paren
(brace
suffix:semicolon
)brace
op_star
id|mem_addr
op_assign
id|MEM_B2EA
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|mem_end
op_assign
op_star
id|mem_data
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|1000
suffix:semicolon
id|loop
op_increment
)paren
(brace
suffix:semicolon
)brace
id|mem_size
op_add_assign
id|mem_end
op_minus
id|mem_start
op_plus
l_int|0x100000
suffix:semicolon
)brace
r_return
id|mem_size
suffix:semicolon
)brace
r_int
r_int
DECL|function|load_kernel
id|load_kernel
c_func
(paren
r_int
r_int
id|load_addr
comma
r_int
id|num_words
comma
r_int
r_int
id|cksum
comma
r_void
op_star
id|ign1
comma
r_void
op_star
id|ign2
)paren
(brace
r_int
id|csr0
suffix:semicolon
r_int
id|csr_id
suffix:semicolon
r_int
id|pci_devfn
suffix:semicolon
r_int
id|found_multi
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|vendor
suffix:semicolon
r_int
r_int
id|device
suffix:semicolon
r_int
r_int
id|command
suffix:semicolon
r_int
r_char
id|header_type
suffix:semicolon
r_int
r_int
id|bar0
suffix:semicolon
r_volatile
r_int
op_star
id|pif_addr
op_assign
(paren
r_int
op_star
)paren
l_int|0xff500000
suffix:semicolon
r_volatile
r_int
op_star
id|pif_data
op_assign
(paren
r_int
op_star
)paren
l_int|0xff500004
suffix:semicolon
multiline_comment|/*&n;&t; * Gah, these firmware guys need to learn that hardware&n;&t; * byte swapping is evil! Disable all hardware byte&n;&t; * swapping so it doesn&squot;t hurt anyone.&n;&t; */
op_star
id|pif_addr
op_assign
id|PLBMIFOPT
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
op_star
id|pif_data
op_assign
l_int|0x00000000
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
multiline_comment|/* Search out and turn off the PcNet ethernet boot device. */
r_for
c_loop
(paren
id|pci_devfn
op_assign
l_int|1
suffix:semicolon
id|pci_devfn
OL
l_int|0xff
suffix:semicolon
id|pci_devfn
op_increment
)paren
(brace
r_if
c_cond
(paren
id|PCI_FUNC
c_func
(paren
id|pci_devfn
)paren
op_logical_and
op_logical_neg
id|found_multi
)paren
r_continue
suffix:semicolon
id|cpc700_pcibios_read_config_byte
c_func
(paren
l_int|0
comma
id|pci_devfn
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|header_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PCI_FUNC
c_func
(paren
id|pci_devfn
)paren
)paren
id|found_multi
op_assign
id|header_type
op_amp
l_int|0x80
suffix:semicolon
id|cpc700_pcibios_read_config_word
c_func
(paren
l_int|0
comma
id|pci_devfn
comma
id|PCI_VENDOR_ID
comma
op_amp
id|vendor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vendor
op_ne
l_int|0xffff
)paren
(brace
id|cpc700_pcibios_read_config_word
c_func
(paren
l_int|0
comma
id|pci_devfn
comma
id|PCI_DEVICE_ID
comma
op_amp
id|device
)paren
suffix:semicolon
multiline_comment|/* If this PCI device is the Lance PCNet board then turn it off */
r_if
c_cond
(paren
(paren
id|vendor
op_eq
id|PCI_VENDOR_ID_AMD
)paren
op_logical_and
(paren
id|device
op_eq
id|PCI_DEVICE_ID_AMD_LANCE
)paren
)paren
(brace
multiline_comment|/* Turn on I/O Space on the board. */
id|cpc700_pcibios_read_config_word
c_func
(paren
l_int|0
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
op_amp
id|command
)paren
suffix:semicolon
id|command
op_or_assign
l_int|0x1
suffix:semicolon
id|cpc700_pcibios_write_config_word
c_func
(paren
l_int|0
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
id|command
)paren
suffix:semicolon
multiline_comment|/* Get the I/O space address */
id|cpc700_pcibios_read_config_dword
c_func
(paren
l_int|0
comma
id|pci_devfn
comma
id|PCI_BASE_ADDRESS_0
comma
op_amp
id|bar0
)paren
suffix:semicolon
id|bar0
op_and_assign
l_int|0xfffffffe
suffix:semicolon
multiline_comment|/* Reset the PCNet Board */
id|inl
(paren
id|bar0
op_plus
id|PCNET32_DWIO_RESET
)paren
suffix:semicolon
id|inw
(paren
id|bar0
op_plus
id|PCNET32_WIO_RESET
)paren
suffix:semicolon
multiline_comment|/* First do a work oriented read of csr0.  If the value is&n;&t;&t;&t;&t; * 4 then this is the correct mode to access the board.&n;&t;&t;&t;&t; * If not try a double word ortiented read.&n;&t;&t;&t;&t; */
id|outw
c_func
(paren
l_int|0
comma
id|bar0
op_plus
id|PCNET32_WIO_RAP
)paren
suffix:semicolon
id|csr0
op_assign
id|inw
c_func
(paren
id|bar0
op_plus
id|PCNET32_WIO_RDP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csr0
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Check the Chip id register */
id|outw
c_func
(paren
l_int|88
comma
id|bar0
op_plus
id|PCNET32_WIO_RAP
)paren
suffix:semicolon
id|csr_id
op_assign
id|inw
c_func
(paren
id|bar0
op_plus
id|PCNET32_WIO_RDP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csr_id
)paren
(brace
multiline_comment|/* This is the valid mode - set the stop bit */
id|outw
c_func
(paren
l_int|0
comma
id|bar0
op_plus
id|PCNET32_WIO_RAP
)paren
suffix:semicolon
id|outw
c_func
(paren
id|csr0
comma
id|bar0
op_plus
id|PCNET32_WIO_RDP
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|outl
c_func
(paren
l_int|0
comma
id|bar0
op_plus
id|PCNET32_DWIO_RAP
)paren
suffix:semicolon
id|csr0
op_assign
id|inl
c_func
(paren
id|bar0
op_plus
id|PCNET32_DWIO_RDP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csr0
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Check the Chip id register */
id|outl
c_func
(paren
l_int|88
comma
id|bar0
op_plus
id|PCNET32_WIO_RAP
)paren
suffix:semicolon
id|csr_id
op_assign
id|inl
c_func
(paren
id|bar0
op_plus
id|PCNET32_WIO_RDP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csr_id
)paren
(brace
multiline_comment|/* This is the valid mode  - set the stop bit*/
id|outl
c_func
(paren
l_int|0
comma
id|bar0
op_plus
id|PCNET32_WIO_RAP
)paren
suffix:semicolon
id|outl
c_func
(paren
id|csr0
comma
id|bar0
op_plus
id|PCNET32_WIO_RDP
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
)brace
r_return
id|decompress_kernel
c_func
(paren
id|load_addr
comma
id|num_words
comma
id|cksum
)paren
suffix:semicolon
)brace
eof
