multiline_comment|/*&n; * Exceptions for specific devices. Usually work-arounds for fatal design flaws.&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|function|pci_fixup_i450nx
r_static
r_void
id|__devinit
id|pci_fixup_i450nx
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
multiline_comment|/*&n;&t; * i450NX -- Find and scan all secondary buses on all PXB&squot;s.&n;&t; */
r_int
id|pxb
comma
id|reg
suffix:semicolon
id|u8
id|busno
comma
id|suba
comma
id|subb
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: Searching for i450NX host bridges on %s&bslash;n&quot;
comma
id|d-&gt;slot_name
)paren
suffix:semicolon
id|reg
op_assign
l_int|0xd0
suffix:semicolon
r_for
c_loop
(paren
id|pxb
op_assign
l_int|0
suffix:semicolon
id|pxb
OL
l_int|2
suffix:semicolon
id|pxb
op_increment
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|d
comma
id|reg
op_increment
comma
op_amp
id|busno
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|d
comma
id|reg
op_increment
comma
op_amp
id|suba
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|d
comma
id|reg
op_increment
comma
op_amp
id|subb
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;i450NX PXB %d: %02x/%02x/%02x&bslash;n&quot;
comma
id|pxb
comma
id|busno
comma
id|suba
comma
id|subb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busno
)paren
id|pci_scan_bus
c_func
(paren
id|busno
comma
id|pci_root_ops
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Bus A */
r_if
c_cond
(paren
id|suba
OL
id|subb
)paren
id|pci_scan_bus
c_func
(paren
id|suba
op_plus
l_int|1
comma
id|pci_root_ops
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Bus B */
)brace
id|pcibios_last_bus
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|pci_fixup_i450gx
r_static
r_void
id|__devinit
id|pci_fixup_i450gx
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
multiline_comment|/*&n;&t; * i450GX and i450KX -- Find and scan all secondary buses.&n;&t; * (called separately for each PCI bridge found)&n;&t; */
id|u8
id|busno
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|d
comma
l_int|0x4a
comma
op_amp
id|busno
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: i440KX/GX host bridge %s: secondary bus %02x&bslash;n&quot;
comma
id|d-&gt;slot_name
comma
id|busno
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
id|busno
comma
id|pci_root_ops
comma
l_int|NULL
)paren
suffix:semicolon
id|pcibios_last_bus
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|pci_fixup_umc_ide
r_static
r_void
id|__devinit
id|pci_fixup_umc_ide
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
multiline_comment|/*&n;&t; * UM8886BF IDE controller sets region type bits incorrectly,&n;&t; * therefore they look like memory despite of them being I/O.&n;&t; */
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: Fixing base address flags for device %s&bslash;n&quot;
comma
id|d-&gt;slot_name
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|d-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_or_assign
id|PCI_BASE_ADDRESS_SPACE_IO
suffix:semicolon
)brace
)brace
DECL|function|pci_fixup_ncr53c810
r_static
r_void
id|__devinit
id|pci_fixup_ncr53c810
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
multiline_comment|/*&n;&t; * NCR 53C810 returns class code 0 (at least on some systems).&n;&t; * Fix class to be PCI_CLASS_STORAGE_SCSI&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|d
op_member_access_from_pointer
r_class
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: fixing NCR 53C810 class code for %s&bslash;n&quot;
comma
id|d-&gt;slot_name
)paren
suffix:semicolon
id|d
op_member_access_from_pointer
r_class
op_assign
id|PCI_CLASS_STORAGE_SCSI
op_lshift
l_int|8
suffix:semicolon
)brace
)brace
DECL|function|pci_fixup_ide_bases
r_static
r_void
id|__devinit
id|pci_fixup_ide_bases
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * PCI IDE controllers use non-standard I/O port decoding, respect it.&n;&t; */
r_if
c_cond
(paren
(paren
id|d
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_STORAGE_IDE
)paren
r_return
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: IDE base address fixup for %s&bslash;n&quot;
comma
id|d-&gt;slot_name
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|d-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r-&gt;start
op_amp
op_complement
l_int|0x80
)paren
op_eq
l_int|0x374
)paren
(brace
id|r-&gt;start
op_or_assign
l_int|2
suffix:semicolon
id|r-&gt;end
op_assign
id|r-&gt;start
suffix:semicolon
)brace
)brace
)brace
DECL|function|pci_fixup_ide_trash
r_static
r_void
id|__devinit
id|pci_fixup_ide_trash
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * There exist PCI IDE controllers which have utter garbage&n;&t; * in first four base registers. Ignore that.&n;&t; */
id|DBG
c_func
(paren
l_string|&quot;PCI: IDE base address trash cleared for %s&bslash;n&quot;
comma
id|d-&gt;slot_name
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|d-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
id|d-&gt;resource
(braket
id|i
)braket
dot
id|end
op_assign
id|d-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|pci_fixup_latency
r_static
r_void
id|__devinit
id|pci_fixup_latency
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
multiline_comment|/*&n;&t; *  SiS 5597 and 5598 chipsets require latency timer set to&n;&t; *  at most 32 to avoid lockups.&n;&t; */
id|DBG
c_func
(paren
l_string|&quot;PCI: Setting max latency to 32&bslash;n&quot;
)paren
suffix:semicolon
id|pcibios_max_latency
op_assign
l_int|32
suffix:semicolon
)brace
DECL|function|pci_fixup_piix4_acpi
r_static
r_void
id|__devinit
id|pci_fixup_piix4_acpi
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
multiline_comment|/*&n;&t; * PIIX4 ACPI device: hardwired IRQ9&n;&t; */
id|d-&gt;irq
op_assign
l_int|9
suffix:semicolon
)brace
multiline_comment|/*&n; * Addresses issues with problems in the memory write queue timer in&n; * certain VIA Northbridges.  This bugfix is per VIA&squot;s specifications.&n; *&n; * VIA 8363,8622,8361 Northbridges:&n; *  - bits  5, 6, 7 at offset 0x55 need to be turned off&n; * VIA 8367 (KT266x) Northbridges:&n; *  - bits  5, 6, 7 at offset 0x95 need to be turned off&n; */
DECL|function|pci_fixup_via_northbridge_bug
r_static
r_void
id|__init
id|pci_fixup_via_northbridge_bug
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
id|u8
id|v
suffix:semicolon
r_int
id|where
op_assign
l_int|0x55
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;device
op_eq
id|PCI_DEVICE_ID_VIA_8367_0
)paren
(brace
id|where
op_assign
l_int|0x95
suffix:semicolon
multiline_comment|/* the memory write queue timer register is &n;                                 different for the kt266x&squot;s: 0x95 not 0x55 */
)brace
id|pci_read_config_byte
c_func
(paren
id|d
comma
id|where
comma
op_amp
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
op_amp
l_int|0xe0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Disabling broken memory write queue: [%02x] %02x-&gt;%02x&bslash;n&quot;
comma
id|where
comma
id|v
comma
id|v
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|v
op_and_assign
l_int|0x1f
suffix:semicolon
multiline_comment|/* clear bits 5, 6, 7 */
id|pci_write_config_byte
c_func
(paren
id|d
comma
id|where
comma
id|v
)paren
suffix:semicolon
)brace
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
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82451NX
comma
id|pci_fixup_i450nx
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82454GX
comma
id|pci_fixup_i450gx
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_UMC
comma
id|PCI_DEVICE_ID_UMC_UM8886BF
comma
id|pci_fixup_umc_ide
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_SI
comma
id|PCI_DEVICE_ID_SI_5513
comma
id|pci_fixup_ide_trash
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|pci_fixup_ide_bases
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_SI
comma
id|PCI_DEVICE_ID_SI_5597
comma
id|pci_fixup_latency
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_SI
comma
id|PCI_DEVICE_ID_SI_5598
comma
id|pci_fixup_latency
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371AB_3
comma
id|pci_fixup_piix4_acpi
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8363_0
comma
id|pci_fixup_via_northbridge_bug
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8622
comma
id|pci_fixup_via_northbridge_bug
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8361
comma
id|pci_fixup_via_northbridge_bug
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8367_0
comma
id|pci_fixup_via_northbridge_bug
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_NCR
comma
id|PCI_DEVICE_ID_NCR_53C810
comma
id|pci_fixup_ncr53c810
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
eof
