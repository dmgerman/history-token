multiline_comment|/*&n; * arch/ppc/boot/spruce/misc.c&n; *&n; * Misc. bootloader code for IBM Spruce reference platform&n; *&n; * Authors: Johnnie Peters &lt;jpeters@mvista.com&gt;&n; *&t;    Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Derived from arch/ppc/boot/prep/misc.c&n; *&n; * Copyright 2000-2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; * WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; * NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; * USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &quot;zlib.h&quot;
multiline_comment|/* Define some important locations of the Spruce. */
DECL|macro|SPRUCE_PCI_CONFIG_ADDR
mdefine_line|#define SPRUCE_PCI_CONFIG_ADDR&t;0xfec00000
DECL|macro|SPRUCE_PCI_CONFIG_DATA
mdefine_line|#define SPRUCE_PCI_CONFIG_DATA&t;0xfec00004
DECL|macro|SPRUCE_ISA_IO_BASE
mdefine_line|#define SPRUCE_ISA_IO_BASE&t;0xf8000000
DECL|variable|com_port
r_int
r_int
id|com_port
suffix:semicolon
DECL|variable|avail_ram
r_char
op_star
id|avail_ram
suffix:semicolon
DECL|variable|end_avail
r_char
op_star
id|end_avail
suffix:semicolon
multiline_comment|/* The linker tells us where the image is. */
r_extern
r_char
id|__image_begin
comma
id|__image_end
suffix:semicolon
r_extern
r_char
id|__ramdisk_begin
comma
id|__ramdisk_end
suffix:semicolon
r_extern
r_char
id|_end
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_CMDLINE
DECL|macro|CMDLINE
mdefine_line|#define CMDLINE CONFIG_CMDLINE
macro_line|#else
DECL|macro|CMDLINE
mdefine_line|#define CMDLINE &quot;&quot;
macro_line|#endif
DECL|variable|cmd_preset
r_char
id|cmd_preset
(braket
)braket
op_assign
id|CMDLINE
suffix:semicolon
DECL|variable|cmd_buf
r_char
id|cmd_buf
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|cmd_line
r_char
op_star
id|cmd_line
op_assign
id|cmd_buf
suffix:semicolon
DECL|variable|initrd_size
r_int
r_int
id|initrd_size
op_assign
l_int|0
suffix:semicolon
DECL|variable|zimage_start
r_char
op_star
id|zimage_start
suffix:semicolon
DECL|variable|zimage_size
r_int
id|zimage_size
suffix:semicolon
r_extern
r_void
id|udelay
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|putc
c_func
(paren
r_const
r_char
id|c
)paren
suffix:semicolon
r_extern
r_void
id|puthex
c_func
(paren
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|getc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|tstc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gunzip
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|serial_init
c_func
(paren
r_int
id|chan
comma
r_void
op_star
id|ignored
)paren
suffix:semicolon
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
DECL|variable|isa_io_base
r_int
r_int
id|isa_io_base
op_assign
id|SPRUCE_ISA_IO_BASE
suffix:semicolon
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
DECL|function|decompress_kernel
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
(brace
r_int
id|timer
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|cp
comma
id|ch
suffix:semicolon
r_int
id|loop
suffix:semicolon
r_int
id|csr0
suffix:semicolon
r_int
id|csr_id
suffix:semicolon
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
macro_line|#ifdef CONFIG_SERIAL_CONSOLE
multiline_comment|/* Initialize the serial console port */
id|com_port
op_assign
id|serial_init
c_func
(paren
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* assume the chunk below 8M is free */
id|end_avail
op_assign
(paren
r_char
op_star
)paren
l_int|0x00800000
suffix:semicolon
multiline_comment|/*&n;&t; * We link ourself to 0x00800000.  When we run, we relocate&n;&t; * ourselves there.  So we just need __image_begin for the&n;&t; * start. -- Tom&n;&t; */
id|zimage_start
op_assign
(paren
r_char
op_star
)paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__image_begin
)paren
suffix:semicolon
id|zimage_size
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__image_end
)paren
op_minus
(paren
r_int
r_int
)paren
(paren
op_amp
id|__image_begin
)paren
suffix:semicolon
id|initrd_size
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_end
)paren
op_minus
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The zImage and initrd will be between start and _end, so they&squot;ve&n;&t; * already been moved once.  We&squot;re good to go now. -- Tom&n;&t; */
id|avail_ram
op_assign
(paren
r_char
op_star
)paren
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|_end
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;zimage at:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|zimage_start
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|zimage_size
op_plus
id|zimage_start
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initrd_size
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;initrd at:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_end
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|avail_ram
op_assign
(paren
r_char
op_star
)paren
l_int|0x00400000
suffix:semicolon
id|end_avail
op_assign
(paren
r_char
op_star
)paren
l_int|0x00800000
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;avail ram:     &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|avail_ram
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|puthex
c_func
(paren
(paren
r_int
r_int
)paren
id|end_avail
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Display standard Linux/PPC boot prompt for kernel args */
id|puts
c_func
(paren
l_string|&quot;&bslash;nLinux/PPC load: &quot;
)paren
suffix:semicolon
id|cp
op_assign
id|cmd_line
suffix:semicolon
id|memcpy
(paren
id|cmd_line
comma
id|cmd_preset
comma
r_sizeof
(paren
id|cmd_preset
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
)paren
id|putc
c_func
(paren
op_star
id|cp
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
id|timer
op_increment
OL
l_int|5
op_star
l_int|1000
)paren
(brace
r_if
c_cond
(paren
id|tstc
c_func
(paren
)paren
)paren
(brace
r_while
c_loop
(paren
(paren
id|ch
op_assign
id|getc
c_func
(paren
)paren
)paren
op_ne
l_char|&squot;&bslash;n&squot;
op_logical_and
id|ch
op_ne
l_char|&squot;&bslash;r&squot;
)paren
(brace
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;b&squot;
)paren
(brace
r_if
c_cond
(paren
id|cp
op_ne
id|cmd_line
)paren
(brace
id|cp
op_decrement
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;b &bslash;b&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
op_star
id|cp
op_increment
op_assign
id|ch
suffix:semicolon
id|putc
c_func
(paren
id|ch
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
multiline_comment|/* Exit &squot;timer&squot; loop */
)brace
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* 1 msec */
)brace
op_star
id|cp
op_assign
l_int|0
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;Uncompressing Linux...&quot;
)paren
suffix:semicolon
id|gunzip
c_func
(paren
l_int|0
comma
l_int|0x400000
comma
id|zimage_start
comma
op_amp
id|zimage_size
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
(brace
r_struct
id|bi_record
op_star
id|rec
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
id|_ALIGN
c_func
(paren
(paren
id|ulong
)paren
id|zimage_size
op_plus
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
comma
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_FIRST
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_BOOTLOADER_ID
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|rec-&gt;data
comma
l_string|&quot;spruceboot&quot;
comma
l_int|11
)paren
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
l_int|10
op_plus
l_int|1
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_MEMSIZE
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
id|mem_size
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_CMD_LINE
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|rec-&gt;data
comma
id|cmd_line
comma
id|strlen
c_func
(paren
id|cmd_line
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
id|strlen
c_func
(paren
id|cmd_line
)paren
op_plus
l_int|1
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
id|ulong
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initrd_size
)paren
(brace
id|rec-&gt;tag
op_assign
id|BI_INITRD
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|__ramdisk_begin
)paren
suffix:semicolon
id|rec-&gt;data
(braket
l_int|1
)braket
op_assign
id|initrd_size
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
l_int|2
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
)brace
id|rec-&gt;tag
op_assign
id|BI_LAST
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
)brace
id|puts
c_func
(paren
l_string|&quot;Now booting the kernel&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof