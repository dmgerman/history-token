multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SNI specific PCI support for RM200/RM300.&n; *&n; * Copyright (C) 1997 - 2000 Ralf Baechle&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/sni.h&gt;
macro_line|#ifdef CONFIG_PCI
DECL|macro|mkaddr
mdefine_line|#define mkaddr(bus, devfn, where)                                                   &bslash;&n;do {                                                                         &bslash;&n;&t;if (bus-&gt;number == 0)                                         &bslash;&n;&t;&t;return -1;                                                   &bslash;&n;&t;*(volatile u32 *)PCIMT_CONFIG_ADDRESS =                              &bslash;&n;&t;&t; ((bus-&gt;number    &amp; 0xff) &lt;&lt; 0x10) |                    &bslash;&n;&t;         ((devfn &amp; 0xff) &lt;&lt; 0x08) |                             &bslash;&n;&t;         (where  &amp; 0xfc);                                            &bslash;&n;} while(0)
macro_line|#if 0
multiline_comment|/* To do:  Bring this uptodate ...  */
r_static
r_void
id|pcimt_pcibios_fixup
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
multiline_comment|/*&n;&t;&t; * TODO: Take care of RM300 revision D boards for where the&n;&t;&t; * network slot became an ordinary PCI slot.&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;devfn
op_eq
id|PCI_DEVFN
c_func
(paren
l_int|1
comma
l_int|0
)paren
)paren
(brace
multiline_comment|/* Evil hack ...  */
id|set_cp0_config
c_func
(paren
id|CONF_CM_CMASK
comma
id|CONF_CM_CACHABLE_NO_WA
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|PCIMT_IRQ_SCSI
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;devfn
op_eq
id|PCI_DEVFN
c_func
(paren
l_int|2
comma
l_int|0
)paren
)paren
(brace
id|dev-&gt;irq
op_assign
id|PCIMT_IRQ_ETHERNET
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|dev-&gt;irq
)paren
(brace
r_case
l_int|1
dot
dot
dot
l_int|4
suffix:colon
id|dev-&gt;irq
op_add_assign
id|PCIMT_IRQ_INTA
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;PCI device on bus %d, dev %d, function %d &quot;
l_string|&quot;impossible interrupt configured.&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * We can&squot;t address 8 and 16 bit words directly.  Instead we have to&n; * read/write a 32bit word and mask/modify the data we actually want.&n; */
DECL|function|pcimt_read
r_static
r_int
id|pcimt_read
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|val
)paren
(brace
id|u32
id|res
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|mkaddr
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
id|res
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_DATA
suffix:semicolon
id|res
op_assign
(paren
id|le32_to_cpu
c_func
(paren
id|res
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
op_star
id|val
op_assign
(paren
id|u8
)paren
id|res
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
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
id|mkaddr
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
id|res
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_DATA
suffix:semicolon
id|res
op_assign
(paren
id|le32_to_cpu
c_func
(paren
id|res
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
op_star
id|val
op_assign
(paren
id|u16
)paren
id|res
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
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
id|mkaddr
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
id|res
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_DATA
suffix:semicolon
id|res
op_assign
id|le32_to_cpu
c_func
(paren
id|res
)paren
suffix:semicolon
op_star
id|val
op_assign
id|res
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|pcimt_write
r_static
r_int
id|pcimt_write
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|val
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|mkaddr
c_func
(paren
id|bus
comma
id|devfn
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
id|PCIMT_CONFIG_DATA
op_plus
(paren
id|where
op_amp
l_int|3
)paren
)paren
op_assign
(paren
id|u8
)paren
id|le32_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
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
id|mkaddr
c_func
(paren
id|bus
comma
id|devfn
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
id|PCIMT_CONFIG_DATA
op_plus
(paren
id|where
op_amp
l_int|3
)paren
)paren
op_assign
(paren
id|u16
)paren
id|le32_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
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
id|mkaddr
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|PCIMT_CONFIG_DATA
op_assign
id|le32_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|sni_pci_ops
r_struct
id|pci_ops
id|sni_pci_ops
op_assign
(brace
dot
id|read
op_assign
id|pcimt_read
comma
dot
id|write
op_assign
id|pcimt_write
comma
)brace
suffix:semicolon
r_void
id|__init
DECL|function|pcibios_fixup_bus
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
)brace
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_ops
op_star
id|ops
op_assign
op_amp
id|sni_pci_ops
suffix:semicolon
id|pci_scan_bus
c_func
(paren
l_int|0
comma
id|ops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|pcibios_enable_device
r_int
id|__init
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* Not needed, since we enable all devices at startup.  */
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_align_resource
id|pcibios_align_resource
c_func
(paren
r_void
op_star
id|data
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
(brace
)brace
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
l_int|0
suffix:semicolon
)brace
r_char
op_star
id|__init
DECL|function|pcibios_setup
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
multiline_comment|/* Nothing to do for now.  */
r_return
id|str
suffix:semicolon
)brace
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
eof
