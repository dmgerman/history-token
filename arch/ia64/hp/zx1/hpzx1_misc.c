multiline_comment|/*&n; * Misc. support for HP zx1 chipset support&n; *&n; * Copyright (C) 2002 Hewlett-Packard Co&n; * Copyright (C) 2002 Alex Williamson &lt;alex_williamson@hp.com&gt;&n; * Copyright (C) 2002 Bjorn Helgaas &lt;bjorn_helgaas@hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/iosapic.h&gt;
r_extern
id|acpi_status
id|acpi_evaluate_integer
(paren
id|acpi_handle
comma
id|acpi_string
comma
id|acpi_object_list
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
DECL|macro|PFX
mdefine_line|#define PFX &quot;hpzx1: &quot;
DECL|variable|hpzx1_devices
r_static
r_int
id|hpzx1_devices
suffix:semicolon
DECL|struct|fake_pci_dev
r_struct
id|fake_pci_dev
(brace
DECL|member|csr_base
r_int
r_int
id|csr_base
suffix:semicolon
DECL|member|csr_size
r_int
r_int
id|csr_size
suffix:semicolon
DECL|member|mapped_csrs
r_int
r_int
id|mapped_csrs
suffix:semicolon
singleline_comment|// ioremapped
DECL|member|sizing
r_int
id|sizing
suffix:semicolon
singleline_comment|// in middle of BAR sizing operation?
)brace
suffix:semicolon
DECL|variable|orig_pci_ops
r_static
r_struct
id|pci_ops
op_star
id|orig_pci_ops
suffix:semicolon
DECL|macro|HP_CFG_RD
mdefine_line|#define HP_CFG_RD(sz, bits, name)&t;&t;&t;&t;&t;&t;&bslash;&n;static int hp_cfg_read##sz (struct pci_dev *dev, int where, u##bits *value)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct fake_pci_dev *fake_dev;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(fake_dev = (struct fake_pci_dev *) dev-&gt;sysdata))&t;&t;&t;&bslash;&n;&t;&t;return orig_pci_ops-&gt;name(dev, where, value);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (where == PCI_BASE_ADDRESS_0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (fake_dev-&gt;sizing)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*value = ~(fake_dev-&gt;csr_size - 1);&t;&t;&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*value = (fake_dev-&gt;csr_base &amp;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;    PCI_BASE_ADDRESS_MEM_MASK) |&t;&t;&bslash;&n;&t;&t;&t;&t;PCI_BASE_ADDRESS_SPACE_MEMORY;&t;&t;&t;&bslash;&n;&t;&t;fake_dev-&gt;sizing = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return PCIBIOS_SUCCESSFUL;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*value = read##sz(fake_dev-&gt;mapped_csrs + where);&t;&t;&t;&bslash;&n;&t;if (where == PCI_COMMAND)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*value |= PCI_COMMAND_MEMORY; /* SBA omits this */&t;&t;&bslash;&n;&t;return PCIBIOS_SUCCESSFUL;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|HP_CFG_WR
mdefine_line|#define HP_CFG_WR(sz, bits, name)&t;&t;&t;&t;&t;&t;&bslash;&n;static int hp_cfg_write##sz (struct pci_dev *dev, int where, u##bits value)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct fake_pci_dev *fake_dev;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(fake_dev = (struct fake_pci_dev *) dev-&gt;sysdata))&t;&t;&t;&bslash;&n;&t;&t;return orig_pci_ops-&gt;name(dev, where, value);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (where == PCI_BASE_ADDRESS_0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (value == (u##bits) ~0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;fake_dev-&gt;sizing = 1;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return PCIBIOS_SUCCESSFUL;&t;&t;&t;&t;&t;&bslash;&n;&t;} else&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;write##sz(value, fake_dev-&gt;mapped_csrs + where);&t;&t;&bslash;&n;&t;return PCIBIOS_SUCCESSFUL;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|HP_CFG_RD
c_func
(paren
id|b
comma
l_int|8
comma
id|read_byte
)paren
id|HP_CFG_RD
c_func
(paren
id|w
comma
l_int|16
comma
id|read_word
)paren
id|HP_CFG_RD
c_func
(paren
id|l
comma
l_int|32
comma
id|read_dword
)paren
id|HP_CFG_WR
c_func
(paren
id|b
comma
l_int|8
comma
id|write_byte
)paren
id|HP_CFG_WR
c_func
(paren
id|w
comma
l_int|16
comma
id|write_word
)paren
id|HP_CFG_WR
c_func
(paren
id|l
comma
l_int|32
comma
id|write_dword
)paren
DECL|variable|hp_pci_conf
r_static
r_struct
id|pci_ops
id|hp_pci_conf
op_assign
(brace
id|hp_cfg_readb
comma
id|hp_cfg_readw
comma
id|hp_cfg_readl
comma
id|hp_cfg_writeb
comma
id|hp_cfg_writew
comma
id|hp_cfg_writel
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|hpzx1_fake_pci_dev
id|hpzx1_fake_pci_dev
c_func
(paren
r_char
op_star
id|name
comma
r_int
r_int
id|busnum
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|fake_pci_dev
op_star
id|fake
suffix:semicolon
r_int
id|slot
comma
id|ret
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|pci_bus
op_star
id|b
comma
op_star
id|bus
op_assign
l_int|NULL
suffix:semicolon
id|u8
id|hdr
suffix:semicolon
id|fake
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|fake
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fake
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;No memory for %s (0x%p) sysdata&bslash;n&quot;
comma
id|name
comma
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|fake
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|fake
)paren
)paren
suffix:semicolon
id|fake-&gt;csr_base
op_assign
id|addr
suffix:semicolon
id|fake-&gt;csr_size
op_assign
id|size
suffix:semicolon
id|fake-&gt;mapped_csrs
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
id|fake-&gt;sizing
op_assign
l_int|0
suffix:semicolon
id|pci_for_each_bus
c_func
(paren
id|b
)paren
r_if
c_cond
(paren
id|busnum
op_eq
id|b-&gt;number
)paren
(brace
id|bus
op_assign
id|b
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bus
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;No host bus 0x%02x for %s (0x%p)&bslash;n&quot;
comma
id|busnum
comma
id|name
comma
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fake
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|slot
op_assign
l_int|0x1e
suffix:semicolon
id|slot
suffix:semicolon
id|slot
op_decrement
)paren
r_if
c_cond
(paren
op_logical_neg
id|pci_find_slot
c_func
(paren
id|busnum
comma
id|PCI_DEVFN
c_func
(paren
id|slot
comma
l_int|0
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|slot
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;No space for %s (0x%p) on bus 0x%02x&bslash;n&quot;
comma
id|name
comma
(paren
r_void
op_star
)paren
id|addr
comma
id|busnum
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fake
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;No memory for %s (0x%p)&bslash;n&quot;
comma
id|name
comma
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fake
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bus-&gt;ops
op_assign
op_amp
id|hp_pci_conf
suffix:semicolon
singleline_comment|// replace pci ops for this bus
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dev
)paren
)paren
suffix:semicolon
id|dev-&gt;bus
op_assign
id|bus
suffix:semicolon
id|dev-&gt;sysdata
op_assign
id|fake
suffix:semicolon
id|dev-&gt;dev.parent
op_assign
id|bus-&gt;dev
suffix:semicolon
id|dev-&gt;dev.bus
op_assign
op_amp
id|pci_bus_type
suffix:semicolon
id|dev-&gt;devfn
op_assign
id|PCI_DEVFN
c_func
(paren
id|slot
comma
l_int|0
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_VENDOR_ID
comma
op_amp
id|dev-&gt;vendor
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_DEVICE_ID
comma
op_amp
id|dev-&gt;device
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|hdr
)paren
suffix:semicolon
id|dev-&gt;hdr_type
op_assign
id|hdr
op_amp
l_int|0x7f
suffix:semicolon
id|pci_setup_device
c_func
(paren
id|dev
)paren
suffix:semicolon
singleline_comment|// pci_insert_device() without running /sbin/hotplug
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;bus_list
comma
op_amp
id|bus-&gt;devices
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;global_list
comma
op_amp
id|pci_devices
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|dev-&gt;dev.name
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|dev-&gt;dev.bus_id
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|ret
op_assign
id|device_register
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;fake device registration failed (%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;%s at 0x%lx; pci dev %s&bslash;n&quot;
comma
id|name
comma
id|addr
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|hpzx1_devices
op_increment
suffix:semicolon
)brace
r_typedef
r_struct
(brace
DECL|member|guid_id
id|u8
id|guid_id
suffix:semicolon
DECL|member|guid
id|u8
id|guid
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|csr_base
id|u8
id|csr_base
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|csr_length
id|u8
id|csr_length
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|acpi_hp_vendor_long
)brace
id|acpi_hp_vendor_long
suffix:semicolon
DECL|macro|HP_CCSR_LENGTH
mdefine_line|#define HP_CCSR_LENGTH&t;0x21
DECL|macro|HP_CCSR_TYPE
mdefine_line|#define HP_CCSR_TYPE&t;0x2
DECL|macro|HP_CCSR_GUID
mdefine_line|#define HP_CCSR_GUID&t;EFI_GUID(0x69e9adf9, 0x924f, 0xab5f,&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; 0xf6, 0x4a, 0x24, 0xd2, 0x01, 0x37, 0x0e, 0xad)
r_extern
id|acpi_status
id|acpi_get_crs
c_func
(paren
id|acpi_handle
comma
id|acpi_buffer
op_star
)paren
suffix:semicolon
r_extern
id|acpi_resource
op_star
id|acpi_get_crs_next
c_func
(paren
id|acpi_buffer
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
id|acpi_resource_data
op_star
id|acpi_get_crs_type
c_func
(paren
id|acpi_buffer
op_star
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|acpi_dispose_crs
c_func
(paren
id|acpi_buffer
op_star
)paren
suffix:semicolon
r_static
id|acpi_status
DECL|function|hp_csr_space
id|hp_csr_space
c_func
(paren
id|acpi_handle
id|obj
comma
id|u64
op_star
id|csr_base
comma
id|u64
op_star
id|csr_length
)paren
(brace
r_int
id|i
comma
id|offset
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_buffer
id|buf
suffix:semicolon
id|acpi_resource_vendor
op_star
id|res
suffix:semicolon
id|acpi_hp_vendor_long
op_star
id|hp_res
suffix:semicolon
id|efi_guid_t
id|vendor_guid
suffix:semicolon
op_star
id|csr_base
op_assign
l_int|0
suffix:semicolon
op_star
id|csr_length
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|acpi_get_crs
c_func
(paren
id|obj
comma
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unable to get _CRS data on object&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
id|res
op_assign
(paren
id|acpi_resource_vendor
op_star
)paren
id|acpi_get_crs_type
c_func
(paren
op_amp
id|buf
comma
op_amp
id|offset
comma
id|ACPI_RSTYPE_VENDOR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Failed to find config space for device&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_dispose_crs
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
id|AE_NOT_FOUND
suffix:semicolon
)brace
id|hp_res
op_assign
(paren
id|acpi_hp_vendor_long
op_star
)paren
(paren
id|res-&gt;reserved
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;length
op_ne
id|HP_CCSR_LENGTH
op_logical_or
id|hp_res-&gt;guid_id
op_ne
id|HP_CCSR_TYPE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Unknown Vendor data&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_dispose_crs
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
id|AE_TYPE
suffix:semicolon
multiline_comment|/* Revisit error? */
)brace
id|memcpy
c_func
(paren
op_amp
id|vendor_guid
comma
id|hp_res-&gt;guid
comma
r_sizeof
(paren
id|efi_guid_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|efi_guidcmp
c_func
(paren
id|vendor_guid
comma
id|HP_CCSR_GUID
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Vendor GUID does not match&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_dispose_crs
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
id|AE_TYPE
suffix:semicolon
multiline_comment|/* Revisit error? */
)brace
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
op_star
id|csr_base
op_or_assign
(paren
(paren
id|u64
)paren
(paren
id|hp_res-&gt;csr_base
(braket
id|i
)braket
)paren
op_lshift
(paren
id|i
op_star
l_int|8
)paren
)paren
suffix:semicolon
op_star
id|csr_length
op_or_assign
(paren
(paren
id|u64
)paren
(paren
id|hp_res-&gt;csr_length
(braket
id|i
)braket
)paren
op_lshift
(paren
id|i
op_star
l_int|8
)paren
)paren
suffix:semicolon
)brace
id|acpi_dispose_crs
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
r_static
id|acpi_status
DECL|function|hpzx1_sba_probe
id|hpzx1_sba_probe
c_func
(paren
id|acpi_handle
id|obj
comma
id|u32
id|depth
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|ret
)paren
(brace
id|u64
id|csr_base
op_assign
l_int|0
comma
id|csr_length
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_char
op_star
id|name
op_assign
id|context
suffix:semicolon
r_char
id|fullname
(braket
l_int|16
)braket
suffix:semicolon
id|status
op_assign
id|hp_csr_space
c_func
(paren
id|obj
comma
op_amp
id|csr_base
comma
op_amp
id|csr_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
r_return
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * Only SBA shows up in ACPI namespace, so its CSR space&n;&t; * includes both SBA and IOC.  Make SBA and IOC show up&n;&t; * separately in PCI space.&n;&t; */
id|sprintf
c_func
(paren
id|fullname
comma
l_string|&quot;%s SBA&quot;
comma
id|name
)paren
suffix:semicolon
id|hpzx1_fake_pci_dev
c_func
(paren
id|fullname
comma
l_int|0
comma
id|csr_base
comma
l_int|0x1000
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|fullname
comma
l_string|&quot;%s IOC&quot;
comma
id|name
)paren
suffix:semicolon
id|hpzx1_fake_pci_dev
c_func
(paren
id|fullname
comma
l_int|0
comma
id|csr_base
op_plus
l_int|0x1000
comma
l_int|0x1000
)paren
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
r_static
id|acpi_status
DECL|function|hpzx1_lba_probe
id|hpzx1_lba_probe
c_func
(paren
id|acpi_handle
id|obj
comma
id|u32
id|depth
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|ret
)paren
(brace
id|u64
id|csr_base
op_assign
l_int|0
comma
id|csr_length
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|NATIVE_UINT
id|busnum
suffix:semicolon
r_char
op_star
id|name
op_assign
id|context
suffix:semicolon
r_char
id|fullname
(braket
l_int|32
)braket
suffix:semicolon
id|status
op_assign
id|hp_csr_space
c_func
(paren
id|obj
comma
op_amp
id|csr_base
comma
op_amp
id|csr_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
r_return
id|status
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_integer
c_func
(paren
id|obj
comma
id|METHOD_NAME__BBN
comma
l_int|NULL
comma
op_amp
id|busnum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;evaluate _BBN fail=0x%x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|busnum
op_assign
l_int|0
suffix:semicolon
singleline_comment|// no _BBN; stick it on bus 0
)brace
id|sprintf
c_func
(paren
id|fullname
comma
l_string|&quot;%s _BBN 0x%02x&quot;
comma
id|name
comma
(paren
r_int
r_int
)paren
id|busnum
)paren
suffix:semicolon
id|hpzx1_fake_pci_dev
c_func
(paren
id|fullname
comma
id|busnum
comma
id|csr_base
comma
id|csr_length
)paren
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
r_static
r_void
DECL|function|hpzx1_acpi_dev_init
id|hpzx1_acpi_dev_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_struct
id|pci_ops
op_star
id|pci_root_ops
suffix:semicolon
id|orig_pci_ops
op_assign
id|pci_root_ops
suffix:semicolon
multiline_comment|/*&n;&t; * Make fake PCI devices for the following hardware in the&n;&t; * ACPI namespace.  This makes it more convenient for drivers&n;&t; * because they can claim these devices based on PCI&n;&t; * information, rather than needing to know about ACPI.  The&n;&t; * 64-bit &quot;HPA&quot; space for this hardware is available as BAR&n;&t; * 0/1.&n;&t; *&n;&t; * HWP0001: Single IOC SBA w/o IOC in namespace&n;&t; * HWP0002: LBA device&n;&t; * HWP0003: AGP LBA device&n;&t; */
id|acpi_get_devices
c_func
(paren
l_string|&quot;HWP0001&quot;
comma
id|hpzx1_sba_probe
comma
l_string|&quot;HWP0001&quot;
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_HP_PROTO
r_if
c_cond
(paren
id|hpzx1_devices
)paren
(brace
macro_line|#endif
id|acpi_get_devices
c_func
(paren
l_string|&quot;HWP0002&quot;
comma
id|hpzx1_lba_probe
comma
l_string|&quot;HWP0002 PCI LBA&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|acpi_get_devices
c_func
(paren
l_string|&quot;HWP0003&quot;
comma
id|hpzx1_lba_probe
comma
l_string|&quot;HWP0003 AGP LBA&quot;
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_HP_PROTO
)brace
DECL|macro|ZX1_FUNC_ID_VALUE
mdefine_line|#define ZX1_FUNC_ID_VALUE    (PCI_DEVICE_ID_HP_ZX1_SBA &lt;&lt; 16) | PCI_VENDOR_ID_HP
multiline_comment|/*&n;&t; * Early protos don&squot;t have bridges in the ACPI namespace, so&n;&t; * if we didn&squot;t find anything, add the things we know are&n;&t; * there.&n;&t; */
r_if
c_cond
(paren
id|hpzx1_devices
op_eq
l_int|0
)paren
(brace
id|u64
id|hpa
comma
id|csr_base
suffix:semicolon
id|csr_base
op_assign
l_int|0xfed00000UL
suffix:semicolon
id|hpa
op_assign
(paren
id|u64
)paren
id|ioremap
c_func
(paren
id|csr_base
comma
l_int|0x2000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__raw_readl
c_func
(paren
id|hpa
)paren
op_eq
id|ZX1_FUNC_ID_VALUE
)paren
(brace
id|hpzx1_fake_pci_dev
c_func
(paren
l_string|&quot;HWP0001 SBA&quot;
comma
l_int|0
comma
id|csr_base
comma
l_int|0x1000
)paren
suffix:semicolon
id|hpzx1_fake_pci_dev
c_func
(paren
l_string|&quot;HWP0001 IOC&quot;
comma
l_int|0
comma
id|csr_base
op_plus
l_int|0x1000
comma
l_int|0x1000
)paren
suffix:semicolon
id|csr_base
op_assign
l_int|0xfed24000UL
suffix:semicolon
id|iounmap
c_func
(paren
id|hpa
)paren
suffix:semicolon
id|hpa
op_assign
(paren
id|u64
)paren
id|ioremap
c_func
(paren
id|csr_base
comma
l_int|0x1000
)paren
suffix:semicolon
id|hpzx1_fake_pci_dev
c_func
(paren
l_string|&quot;HWP0003 AGP LBA&quot;
comma
l_int|0x40
comma
id|csr_base
comma
l_int|0x1000
)paren
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|hpa
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_extern
r_void
id|sba_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
DECL|function|hpzx1_pci_fixup
id|hpzx1_pci_fixup
(paren
r_int
id|phase
)paren
(brace
id|iosapic_pci_fixup
c_func
(paren
id|phase
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|phase
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* zx1 has a hardware I/O TLB which lets us DMA from any device to any address */
id|MAX_DMA_ADDRESS
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|hpzx1_acpi_dev_init
c_func
(paren
)paren
suffix:semicolon
id|sba_init
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
eof
