multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SNI specific PCI support for RM200/RM300.&n; *&n; * Copyright (C) 1997 - 2000 Ralf Baechle&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/pci_channel.h&gt;
macro_line|#include &lt;asm/hp-lj/asic.h&gt;
DECL|variable|pci_config_address_reg
r_volatile
id|u32
op_star
id|pci_config_address_reg
op_assign
(paren
r_volatile
id|u32
op_star
)paren
l_int|0xfdead000
suffix:semicolon
DECL|variable|pci_config_data_reg
r_volatile
id|u32
op_star
id|pci_config_data_reg
op_assign
(paren
r_volatile
id|u32
op_star
)paren
l_int|0xfdead000
suffix:semicolon
DECL|macro|cfgaddr
mdefine_line|#define cfgaddr(dev, where) (((dev-&gt;bus-&gt;number &amp; 0xff) &lt;&lt; 0x10) |  &bslash;&n;                             ((dev-&gt;devfn &amp; 0xff) &lt;&lt; 0x08) |        &bslash;&n;                             (where &amp; 0xfc))
multiline_comment|/*&n; * We can&squot;t address 8 and 16 bit words directly.  Instead we have to&n; * read/write a 32bit word and mask/modify the data we actually want.&n; */
DECL|function|pcimt_read_config_byte
r_static
r_int
id|pcimt_read_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
r_int
r_char
op_star
id|val
)paren
(brace
op_star
id|pci_config_address_reg
op_assign
id|cfgaddr
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
op_star
id|val
op_assign
(paren
id|le32_to_cpu
c_func
(paren
op_star
id|pci_config_data_reg
)paren
op_rshift
(paren
(paren
id|where
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
singleline_comment|//printk(&quot;pci_read_byte 0x%x == 0x%x&bslash;n&quot;, where, *val);
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pcimt_read_config_word
r_static
r_int
id|pcimt_read_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
op_star
id|pci_config_address_reg
op_assign
id|cfgaddr
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
op_star
id|val
op_assign
(paren
id|le32_to_cpu
c_func
(paren
op_star
id|pci_config_data_reg
)paren
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
singleline_comment|//printk(&quot;pci_read_word 0x%x == 0x%x&bslash;n&quot;, where, *val);
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pcimt_read_config_dword
r_int
id|pcimt_read_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_if
c_cond
(paren
id|where
op_amp
l_int|3
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
op_star
id|pci_config_address_reg
op_assign
id|cfgaddr
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
op_star
id|val
op_assign
id|le32_to_cpu
c_func
(paren
op_star
id|pci_config_data_reg
)paren
suffix:semicolon
singleline_comment|//printk(&quot;pci_read_dword 0x%x == 0x%x&bslash;n&quot;, where, *val);
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pcimt_write_config_byte
r_static
r_int
id|pcimt_write_config_byte
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
r_int
r_char
id|val
)paren
(brace
op_star
id|pci_config_address_reg
op_assign
id|cfgaddr
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
(paren
(paren
r_int
)paren
id|pci_config_data_reg
)paren
op_plus
(paren
id|where
op_amp
l_int|3
)paren
)paren
op_assign
id|val
suffix:semicolon
singleline_comment|//printk(&quot;pci_write_byte 0x%x = 0x%x&bslash;n&quot;, where, val);
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pcimt_write_config_word
r_static
r_int
id|pcimt_write_config_word
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
op_star
id|pci_config_address_reg
op_assign
id|cfgaddr
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u16
op_star
)paren
(paren
(paren
(paren
r_int
)paren
id|pci_config_data_reg
)paren
op_plus
(paren
id|where
op_amp
l_int|2
)paren
)paren
op_assign
id|le16_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
singleline_comment|//printk(&quot;pci_write_word 0x%x = 0x%x&bslash;n&quot;, where, val);
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pcimt_write_config_dword
r_int
id|pcimt_write_config_dword
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|where
comma
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|where
op_amp
l_int|3
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
op_star
id|pci_config_address_reg
op_assign
id|cfgaddr
c_func
(paren
id|dev
comma
id|where
)paren
suffix:semicolon
op_star
id|pci_config_data_reg
op_assign
id|le32_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
singleline_comment|//printk(&quot;pci_write_dword 0x%x = 0x%x&bslash;n&quot;, where, val);
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|hp_pci_ops
r_struct
id|pci_ops
id|hp_pci_ops
op_assign
(brace
id|pcimt_read_config_byte
comma
id|pcimt_read_config_word
comma
id|pcimt_read_config_dword
comma
id|pcimt_write_config_byte
comma
id|pcimt_write_config_word
comma
id|pcimt_write_config_dword
)brace
suffix:semicolon
DECL|variable|mips_pci_channels
r_struct
id|pci_channel
id|mips_pci_channels
(braket
)braket
op_assign
(brace
(brace
op_amp
id|hp_pci_ops
comma
op_amp
id|ioport_resource
comma
op_amp
id|iomem_resource
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|pcibios_assign_all_busses
r_int
id|__init
r_int
id|pcibios_assign_all_busses
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pcibios_fixup
r_void
id|__init
id|pcibios_fixup
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|pcibios_fixup_irqs
r_void
id|__init
id|pcibios_fixup_irqs
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|slot_num
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|slot_num
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|slot_num
)paren
(brace
r_case
l_int|2
suffix:colon
id|dev-&gt;irq
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|dev-&gt;irq
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|dev-&gt;irq
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|macro|IO_MEM_LOGICAL_START
mdefine_line|#define IO_MEM_LOGICAL_START   0x3e000000
DECL|macro|IO_MEM_LOGICAL_END
mdefine_line|#define IO_MEM_LOGICAL_END     0x3fefffff
DECL|macro|IO_PORT_LOGICAL_START
mdefine_line|#define IO_PORT_LOGICAL_START  0x3ff00000
DECL|macro|IO_PORT_LOGICAL_END
mdefine_line|#define IO_PORT_LOGICAL_END    0x3fffffff
DECL|macro|IO_MEM_VIRTUAL_OFFSET
mdefine_line|#define IO_MEM_VIRTUAL_OFFSET  0xb0000000
DECL|macro|IO_PORT_VIRTUAL_OFFSET
mdefine_line|#define IO_PORT_VIRTUAL_OFFSET 0xb0000000
DECL|macro|ONE_MEG
mdefine_line|#define ONE_MEG   (1024 * 1024)
DECL|function|pci_setup
r_void
id|__init
id|pci_setup
c_func
(paren
r_void
)paren
(brace
id|u32
id|pci_regs_base_offset
op_assign
l_int|0xfdead000
suffix:semicolon
r_switch
c_cond
(paren
id|GetAsicId
c_func
(paren
)paren
)paren
(brace
r_case
id|AndrosAsic
suffix:colon
id|pci_regs_base_offset
op_assign
l_int|0xbff80000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HarmonyAsic
suffix:colon
id|pci_regs_base_offset
op_assign
l_int|0xbff70000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ERROR: PCI does not support %s Asic&bslash;n&quot;
comma
id|GetAsicName
c_func
(paren
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
singleline_comment|// set bus stat/command reg
singleline_comment|// REVIST this setting may need vary depending on the hardware
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|pci_regs_base_offset
op_or
l_int|0x0004
)paren
)paren
op_assign
l_int|0x38000007
suffix:semicolon
id|iomem_resource.start
op_assign
id|IO_MEM_LOGICAL_START
op_plus
id|IO_MEM_VIRTUAL_OFFSET
suffix:semicolon
id|iomem_resource.end
op_assign
id|IO_MEM_LOGICAL_END
op_plus
id|IO_MEM_VIRTUAL_OFFSET
suffix:semicolon
id|ioport_resource.start
op_assign
id|IO_PORT_LOGICAL_START
op_plus
id|IO_PORT_VIRTUAL_OFFSET
suffix:semicolon
id|ioport_resource.end
op_assign
id|IO_PORT_LOGICAL_END
op_plus
id|IO_PORT_VIRTUAL_OFFSET
suffix:semicolon
singleline_comment|// KLUDGE (mips_io_port_base is screwed up, we&squot;ve got to work around it here)
singleline_comment|// by letting both low (illegal) and high (legal) addresses appear in pci io space
id|ioport_resource.start
op_assign
l_int|0x0
suffix:semicolon
id|set_io_port_base
c_func
(paren
id|IO_PORT_LOGICAL_START
op_plus
id|IO_PORT_VIRTUAL_OFFSET
)paren
suffix:semicolon
singleline_comment|// map the PCI address space
singleline_comment|// global map - all levels &amp; processes can access
singleline_comment|// except that the range is outside user space
singleline_comment|// parameters: lo0, lo1, hi, pagemask
singleline_comment|// lo indicates physical page, hi indicates virtual address
id|add_wired_entry
c_func
(paren
(paren
id|IO_MEM_LOGICAL_START
op_rshift
l_int|6
)paren
op_or
l_int|0x17
comma
(paren
(paren
id|IO_MEM_LOGICAL_START
op_plus
(paren
l_int|16
op_star
id|ONE_MEG
)paren
)paren
op_rshift
l_int|6
)paren
op_or
l_int|0x17
comma
l_int|0xee000000
comma
id|PM_16M
)paren
suffix:semicolon
singleline_comment|// These are used in pci r/w routines so need to preceed bus scan
id|pci_config_data_reg
op_assign
(paren
id|u32
op_star
)paren
(paren
(paren
(paren
id|u32
)paren
id|mips_io_port_base
)paren
op_or
l_int|0xcfc
)paren
suffix:semicolon
id|pci_config_address_reg
op_assign
(paren
id|u32
op_star
)paren
(paren
(paren
(paren
id|u32
)paren
id|pci_regs_base_offset
)paren
op_or
l_int|0xcf8
)paren
suffix:semicolon
)brace
DECL|function|pcibios_fixup_resources
r_void
id|__init
id|pcibios_fixup_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|pos
suffix:semicolon
r_int
id|bases
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;adjusting pci device: %s&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;hdr_type
)paren
(brace
r_case
id|PCI_HEADER_TYPE_NORMAL
suffix:colon
id|bases
op_assign
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_HEADER_TYPE_BRIDGE
suffix:colon
id|bases
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_HEADER_TYPE_CARDBUS
suffix:colon
id|bases
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|bases
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|pos
op_assign
l_int|0
suffix:semicolon
id|pos
OL
id|bases
suffix:semicolon
id|pos
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
op_amp
id|dev-&gt;resource
(braket
id|pos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;start
op_ge
id|IO_MEM_LOGICAL_START
op_logical_and
id|res-&gt;end
op_le
id|IO_MEM_LOGICAL_END
)paren
(brace
id|res-&gt;start
op_add_assign
id|IO_MEM_VIRTUAL_OFFSET
suffix:semicolon
id|res-&gt;end
op_add_assign
id|IO_MEM_VIRTUAL_OFFSET
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res-&gt;start
op_ge
id|IO_PORT_LOGICAL_START
op_logical_and
id|res-&gt;end
op_le
id|IO_PORT_LOGICAL_END
)paren
(brace
id|res-&gt;start
op_add_assign
id|IO_PORT_VIRTUAL_OFFSET
suffix:semicolon
id|res-&gt;end
op_add_assign
id|IO_PORT_VIRTUAL_OFFSET
suffix:semicolon
)brace
)brace
)brace
eof
