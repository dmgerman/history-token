multiline_comment|/*&n; * $Id: quirks.c,v 1.5 1998/05/02 19:24:14 mj Exp $&n; *&n; *  This file contains work-arounds for many known PCI hardware&n; *  bugs.  Devices present only on certain architectures (host&n; *  bridges et cetera) should be handled in arch-specific code.&n; *&n; *  Copyright (c) 1999 Martin Mares &lt;mj@ucw.cz&gt;&n; *&n; *  The bridge optimization stuff has been removed. If you really&n; *  have a silly BIOS which is unable to set your host bridge right,&n; *  use the PowerTweak utility (see http://powertweak.sourceforge.net).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
multiline_comment|/* Deal with broken BIOS&squot;es that neglect to enable passive release,&n;   which can cause problems in combination with the 82441FX/PPro MTRRs */
DECL|function|quirk_passive_release
r_static
r_void
id|__devinit
id|quirk_passive_release
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pci_dev
op_star
id|d
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|dlc
suffix:semicolon
multiline_comment|/* We have to make sure a particular bit is set in the PIIX3&n;&t;   ISA bridge, so we have to go out and find it. */
r_while
c_loop
(paren
(paren
id|d
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371SB_0
comma
id|d
)paren
)paren
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|d
comma
l_int|0x82
comma
op_amp
id|dlc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dlc
op_amp
l_int|1
op_lshift
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: PIIX3: Enabling Passive Release on %s&bslash;n&quot;
comma
id|d-&gt;slot_name
)paren
suffix:semicolon
id|dlc
op_or_assign
l_int|1
op_lshift
l_int|1
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|d
comma
l_int|0x82
comma
id|dlc
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*  The VIA VP2/VP3/MVP3 seem to have some &squot;features&squot;. There may be a workaround&n;    but VIA don&squot;t answer queries. If you happen to have good contacts at VIA&n;    ask them for me please -- Alan &n;    &n;    This appears to be BIOS not version dependent. So presumably there is a &n;    chipset level fix */
DECL|variable|isa_dma_bridge_buggy
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
multiline_comment|/* Exported */
DECL|function|quirk_isa_dma_hangs
r_static
r_void
id|__devinit
id|quirk_isa_dma_hangs
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|isa_dma_bridge_buggy
)paren
(brace
id|isa_dma_bridge_buggy
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Activating ISA DMA hang workarounds.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|variable|pci_pci_problems
r_int
id|pci_pci_problems
suffix:semicolon
multiline_comment|/*&n; *&t;Chipsets where PCI-&gt;PCI transfers vanish or hang&n; */
DECL|function|quirk_nopcipci
r_static
r_void
id|__devinit
id|quirk_nopcipci
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|pci_pci_problems
op_amp
id|PCIPCI_FAIL
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Disabling direct PCI/PCI transfers.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_pci_problems
op_or_assign
id|PCIPCI_FAIL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Triton requires workarounds to be used by the drivers&n; */
DECL|function|quirk_triton
r_static
r_void
id|__devinit
id|quirk_triton
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|pci_pci_problems
op_amp
id|PCIPCI_TRITON
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Limiting direct PCI/PCI transfers.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_pci_problems
op_or_assign
id|PCIPCI_TRITON
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;VIA Apollo KT133 needs PCI latency patch&n; *&t;Made according to a windows driver based patch by George E. Breese&n; *&t;see PCI Latency Adjust on http://www.viahardware.com/download/viatweak.shtm&n; *      Also see http://www.au-ja.org/review-kt133a-1-en.phtml for&n; *      the info on which Mr Breese based his work.&n; *&n; *&t;Updated based on further information from the site and also on&n; *&t;information provided by VIA &n; */
DECL|function|quirk_vialatency
r_static
r_void
id|__devinit
id|quirk_vialatency
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pci_dev
op_star
id|p
suffix:semicolon
id|u8
id|rev
suffix:semicolon
id|u8
id|busarb
suffix:semicolon
multiline_comment|/* Ok we have a potential problem chipset here. Now see if we have&n;&t;   a buggy southbridge */
id|p
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C686
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|p
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|rev
)paren
suffix:semicolon
multiline_comment|/* 0x40 - 0x4f == 686B, 0x10 - 0x2f == 686A; thanks Dan Hollis */
multiline_comment|/* Check for buggy part revisions */
r_if
c_cond
(paren
id|rev
template_param
l_int|0x42
)paren
r_return
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8231
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* No problem parts */
r_return
suffix:semicolon
)brace
id|pci_read_config_byte
c_func
(paren
id|p
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|rev
)paren
suffix:semicolon
multiline_comment|/* Check for buggy part revisions */
r_if
c_cond
(paren
id|rev
template_param
l_int|0x12
)paren
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Ok we have the problem. Now set the PCI master grant to &n;&t; *&t;occur every master grant. The apparent bug is that under high&n;&t; *&t;PCI load (quite common in Linux of course) you can get data&n;&t; *&t;loss when the CPU is held off the bus for 3 bus master requests&n;&t; *&t;This happens to include the IDE controllers....&n;&t; *&n;&t; *&t;VIA only apply this fix when an SB Live! is present but under&n;&t; *&t;both Linux and Windows this isnt enough, and we have seen&n;&t; *&t;corruption without SB Live! but with things like 3 UDMA IDE&n;&t; *&t;controllers. So we ignore that bit of the VIA recommendation..&n;&t; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x76
comma
op_amp
id|busarb
)paren
suffix:semicolon
multiline_comment|/* Set bit 4 and bi 5 of byte 76 to 0x01 &n;&t;   &quot;Master priority rotation on every PCI master grant */
id|busarb
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|5
)paren
suffix:semicolon
id|busarb
op_or_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x76
comma
id|busarb
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Applying VIA southbridge workaround.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;VIA Apollo VP3 needs ETBF on BT848/878&n; */
DECL|function|quirk_viaetbf
r_static
r_void
id|__devinit
id|quirk_viaetbf
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|pci_pci_problems
op_amp
id|PCIPCI_VIAETBF
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Limiting direct PCI/PCI transfers.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_pci_problems
op_or_assign
id|PCIPCI_VIAETBF
suffix:semicolon
)brace
)brace
DECL|function|quirk_vsfx
r_static
r_void
id|__devinit
id|quirk_vsfx
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|pci_pci_problems
op_amp
id|PCIPCI_VSFX
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Limiting direct PCI/PCI transfers.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_pci_problems
op_or_assign
id|PCIPCI_VSFX
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Natoma has some interesting boundary conditions with Zoran stuff&n; *&t;at least&n; */
DECL|function|quirk_natoma
r_static
r_void
id|__devinit
id|quirk_natoma
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|pci_pci_problems
op_amp
id|PCIPCI_NATOMA
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Limiting direct PCI/PCI transfers.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_pci_problems
op_or_assign
id|PCIPCI_NATOMA
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  S3 868 and 968 chips report region size equal to 32M, but they decode 64M.&n; *  If it&squot;s needed, re-allocate the region.&n; */
DECL|function|quirk_s3_64M
r_static
r_void
id|__devinit
id|quirk_s3_64M
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r-&gt;start
op_amp
l_int|0x3ffffff
)paren
op_logical_or
id|r-&gt;end
op_ne
id|r-&gt;start
op_plus
l_int|0x3ffffff
)paren
(brace
id|r-&gt;start
op_assign
l_int|0
suffix:semicolon
id|r-&gt;end
op_assign
l_int|0x3ffffff
suffix:semicolon
)brace
)brace
DECL|function|quirk_io_region
r_static
r_void
id|__devinit
id|quirk_io_region
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|region
comma
r_int
id|size
comma
r_int
id|nr
)paren
(brace
id|region
op_and_assign
op_complement
(paren
id|size
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|region
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
id|dev-&gt;resource
op_plus
id|nr
suffix:semicolon
id|res-&gt;name
op_assign
id|dev-&gt;name
suffix:semicolon
id|res-&gt;start
op_assign
id|region
suffix:semicolon
id|res-&gt;end
op_assign
id|region
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
id|res-&gt;flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|pci_claim_resource
c_func
(paren
id|dev
comma
id|nr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Let&squot;s make the southbridge information explicit instead&n; * of having to worry about people probing the ACPI areas,&n; * for example.. (Yes, it happens, and if you read the wrong&n; * ACPI register it will put the machine to sleep with no&n; * way of waking it up again. Bummer).&n; *&n; * ALI M7101: Two IO regions pointed to by words at&n; *&t;0xE0 (64 bytes of ACPI registers)&n; *&t;0xE2 (32 bytes of SMB registers)&n; */
DECL|function|quirk_ali7101_acpi
r_static
r_void
id|__devinit
id|quirk_ali7101_acpi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u16
id|region
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0xE0
comma
op_amp
id|region
)paren
suffix:semicolon
id|quirk_io_region
c_func
(paren
id|dev
comma
id|region
comma
l_int|64
comma
id|PCI_BRIDGE_RESOURCES
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0xE2
comma
op_amp
id|region
)paren
suffix:semicolon
id|quirk_io_region
c_func
(paren
id|dev
comma
id|region
comma
l_int|32
comma
id|PCI_BRIDGE_RESOURCES
op_plus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PIIX4 ACPI: Two IO regions pointed to by longwords at&n; *&t;0x40 (64 bytes of ACPI registers)&n; *&t;0x90 (32 bytes of SMB registers)&n; */
DECL|function|quirk_piix4_acpi
r_static
r_void
id|__devinit
id|quirk_piix4_acpi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u32
id|region
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|region
)paren
suffix:semicolon
id|quirk_io_region
c_func
(paren
id|dev
comma
id|region
comma
l_int|64
comma
id|PCI_BRIDGE_RESOURCES
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x90
comma
op_amp
id|region
)paren
suffix:semicolon
id|quirk_io_region
c_func
(paren
id|dev
comma
id|region
comma
l_int|32
comma
id|PCI_BRIDGE_RESOURCES
op_plus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * VIA ACPI: One IO region pointed to by longword at&n; *&t;0x48 or 0x20 (256 bytes of ACPI registers)&n; */
DECL|function|quirk_vt82c586_acpi
r_static
r_void
id|__devinit
id|quirk_vt82c586_acpi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|rev
suffix:semicolon
id|u32
id|region
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|rev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev
op_amp
l_int|0x10
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x48
comma
op_amp
id|region
)paren
suffix:semicolon
id|region
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|quirk_io_region
c_func
(paren
id|dev
comma
id|region
comma
l_int|256
comma
id|PCI_BRIDGE_RESOURCES
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * VIA VT82C686 ACPI: Three IO region pointed to by (long)words at&n; *&t;0x48 (256 bytes of ACPI registers)&n; *&t;0x70 (128 bytes of hardware monitoring register)&n; *&t;0x90 (16 bytes of SMB registers)&n; */
DECL|function|quirk_vt82c686_acpi
r_static
r_void
id|__devinit
id|quirk_vt82c686_acpi
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u16
id|hm
suffix:semicolon
id|u32
id|smb
suffix:semicolon
id|quirk_vt82c586_acpi
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x70
comma
op_amp
id|hm
)paren
suffix:semicolon
id|hm
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|quirk_io_region
c_func
(paren
id|dev
comma
id|hm
comma
l_int|128
comma
id|PCI_BRIDGE_RESOURCES
op_plus
l_int|1
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x90
comma
op_amp
id|smb
)paren
suffix:semicolon
id|smb
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|quirk_io_region
c_func
(paren
id|dev
comma
id|smb
comma
l_int|16
comma
id|PCI_BRIDGE_RESOURCES
op_plus
l_int|2
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86_IO_APIC 
r_extern
r_int
id|nr_ioapics
suffix:semicolon
multiline_comment|/*&n; * VIA 686A/B: If an IO-APIC is active, we need to route all on-chip&n; * devices to the external APIC.&n; *&n; * TODO: When we have device-specific interrupt routers,&n; * this code will go away from quirks.&n; */
DECL|function|quirk_via_ioapic
r_static
r_void
id|__devinit
id|quirk_via_ioapic
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|nr_ioapics
OL
l_int|1
)paren
id|tmp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* nothing routed to external APIC */
r_else
id|tmp
op_assign
l_int|0x1f
suffix:semicolon
multiline_comment|/* all known bits (4-0) routed to external APIC */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: %sbling Via external APIC routing&bslash;n&quot;
comma
id|tmp
op_eq
l_int|0
ques
c_cond
l_string|&quot;Disa&quot;
suffix:colon
l_string|&quot;Ena&quot;
)paren
suffix:semicolon
multiline_comment|/* Offset 0x58: External APIC IRQ output control */
id|pci_write_config_byte
(paren
id|dev
comma
l_int|0x58
comma
id|tmp
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_X86_IO_APIC */
multiline_comment|/*&n; * Via 686A/B:  The PCI_INTERRUPT_LINE register for the on-chip&n; * devices, USB0/1, AC97, MC97, and ACPI, has an unusual feature:&n; * when written, it makes an internal connection to the PIC.&n; * For these devices, this register is defined to be 4 bits wide.&n; * Normally this is fine.  However for IO-APIC motherboards, or&n; * non-x86 architectures (yes Via exists on PPC among other places),&n; * we must mask the PCI_INTERRUPT_LINE value versus 0xf to get&n; * interrupts delivered properly.&n; *&n; * TODO: When we have device-specific interrupt routers,&n; * quirk_via_irqpic will go away from quirks.&n; */
multiline_comment|/*&n; * FIXME: it is questionable that quirk_via_acpi&n; * is needed.  It shows up as an ISA bridge, and does not&n; * support the PCI_INTERRUPT_LINE register at all.  Therefore&n; * it seems like setting the pci_dev&squot;s &squot;irq&squot; to the&n; * value of the ACPI SCI interrupt is only done for convenience.&n; *&t;-jgarzik&n; */
DECL|function|quirk_via_acpi
r_static
r_void
id|__devinit
id|quirk_via_acpi
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
multiline_comment|/*&n;&t; * VIA ACPI device: SCI IRQ line in PCI config byte 0x42&n;&t; */
id|u8
id|irq
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|d
comma
l_int|0x42
comma
op_amp
id|irq
)paren
suffix:semicolon
id|irq
op_and_assign
l_int|0xf
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_logical_and
(paren
id|irq
op_ne
l_int|2
)paren
)paren
id|d-&gt;irq
op_assign
id|irq
suffix:semicolon
)brace
DECL|function|quirk_via_irqpic
r_static
r_void
id|__devinit
id|quirk_via_irqpic
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|irq
comma
id|new_irq
op_assign
id|dev-&gt;irq
op_amp
l_int|0xf
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_irq
op_ne
id|irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Via IRQ fixup for %s, from %d to %d&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|irq
comma
id|new_irq
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|15
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|new_irq
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * PIIX3 USB: We have to disable USB interrupts that are&n; * hardwired to PIRQD# and may be shared with an&n; * external device.&n; *&n; * Legacy Support Register (LEGSUP):&n; *     bit13:  USB PIRQ Enable (USBPIRQDEN),&n; *     bit4:   Trap/SMI On IRQ Enable (USBSMIEN).&n; *&n; * We mask out all r/wc bits, too.&n; */
DECL|function|quirk_piix3_usb
r_static
r_void
id|__devinit
id|quirk_piix3_usb
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u16
id|legsup
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0xc0
comma
op_amp
id|legsup
)paren
suffix:semicolon
id|legsup
op_and_assign
l_int|0x50ef
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0xc0
comma
id|legsup
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * VIA VT82C598 has its device ID settable and many BIOSes&n; * set it to the ID of VT82C597 for backward compatibility.&n; * We need to switch it off to be able to recognize the real&n; * type of the chip.&n; */
DECL|function|quirk_vt82c598_id
r_static
r_void
id|__devinit
id|quirk_vt82c598_id
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0xfc
comma
l_int|0
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
)brace
multiline_comment|/*&n; * CardBus controllers have a legacy base address that enables them&n; * to respond as i82365 pcmcia controllers.  We don&squot;t want them to&n; * do this even if the Linux CardBus driver is not loaded, because&n; * the Linux i82365 driver does not (and should not) handle CardBus.&n; */
DECL|function|quirk_cardbus_legacy
r_static
r_void
id|__devinit
id|quirk_cardbus_legacy
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|PCI_CLASS_BRIDGE_CARDBUS
op_lshift
l_int|8
)paren
op_xor
id|dev
op_member_access_from_pointer
r_class
)paren
r_return
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_CB_LEGACY_MODE_BASE
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The AMD io apic can hang the box when an apic irq is masked.&n; * We check all revs &gt;= B0 (yet not in the pre production!) as the bug&n; * is currently marked NoFix&n; *&n; * We have multiple reports of hangs with this chipset that went away with&n; * noapic specified. For the moment we assume its the errata. We may be wrong&n; * of course. However the advice is demonstrably good even if so..&n; */
DECL|function|quirk_amd_ioapic
r_static
r_void
id|__devinit
id|quirk_amd_ioapic
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|rev
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_REVISION_ID
comma
op_amp
id|rev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev
op_ge
l_int|0x02
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;I/O APIC: AMD Errata #22 may be present. In the event of instability try&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;        : booting with the &bslash;&quot;noapic&bslash;&quot; option.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Following the PCI ordering rules is optional on the AMD762. I&squot;m not&n; * sure what the designers were smoking but let&squot;s not inhale...&n; *&n; * To be fair to AMD, it follows the spec by default, its BIOS people&n; * who turn it off!&n; */
DECL|function|quirk_amd_ordering
r_static
r_void
id|__devinit
id|quirk_amd_ordering
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u32
id|pcic
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x4C
comma
op_amp
id|pcic
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pcic
op_amp
l_int|6
)paren
op_ne
l_int|6
)paren
(brace
id|pcic
op_or_assign
l_int|6
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;BIOS failed to enable PCI standards compliance, fixing this error.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x4C
comma
id|pcic
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x84
comma
op_amp
id|pcic
)paren
suffix:semicolon
id|pcic
op_or_assign
(paren
l_int|1
op_lshift
l_int|23
)paren
suffix:semicolon
multiline_comment|/* Required in this mode */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x84
comma
id|pcic
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;DreamWorks provided workaround for Dunord I-3000 problem&n; *&n; *&t;This card decodes and responds to addresses not apparently&n; *&t;assigned to it. We force a larger allocation to ensure that&n; *&t;nothing gets put too close to it.&n; */
DECL|function|quirk_dunord
r_static
r_void
id|__devinit
id|quirk_dunord
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|dev
op_member_access_from_pointer
id|resource
(braket
l_int|1
)braket
suffix:semicolon
id|r
op_member_access_from_pointer
id|start
op_assign
l_int|0
suffix:semicolon
id|r
op_member_access_from_pointer
id|end
op_assign
l_int|0xffffff
suffix:semicolon
)brace
DECL|function|quirk_transparent_bridge
r_static
r_void
id|__devinit
id|quirk_transparent_bridge
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;transparent
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *  The main table of quirks.&n; */
DECL|variable|__devinitdata
r_static
r_struct
id|pci_fixup
id|pci_fixups
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_DUNORD
comma
id|PCI_DEVICE_ID_DUNORD_I3000
comma
id|quirk_dunord
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82441
comma
id|quirk_passive_release
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82441
comma
id|quirk_passive_release
)brace
comma
multiline_comment|/*&n;&t; * Its not totally clear which chipsets are the problematic ones&n;&t; * We know 82C586 and 82C596 variants are affected.&n;&t; */
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C586_0
comma
id|quirk_isa_dma_hangs
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C596
comma
id|quirk_isa_dma_hangs
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371SB_0
comma
id|quirk_isa_dma_hangs
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_S3
comma
id|PCI_DEVICE_ID_S3_868
comma
id|quirk_s3_64M
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_S3
comma
id|PCI_DEVICE_ID_S3_968
comma
id|quirk_s3_64M
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82437
comma
id|quirk_triton
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82437VX
comma
id|quirk_triton
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82439
comma
id|quirk_triton
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82439TX
comma
id|quirk_triton
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82441
comma
id|quirk_natoma
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82443LX_0
comma
id|quirk_natoma
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82443LX_1
comma
id|quirk_natoma
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82443BX_0
comma
id|quirk_natoma
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82443BX_1
comma
id|quirk_natoma
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82443BX_2
comma
id|quirk_natoma
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_SI
comma
id|PCI_DEVICE_ID_SI_5597
comma
id|quirk_nopcipci
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_SI
comma
id|PCI_DEVICE_ID_SI_496
comma
id|quirk_nopcipci
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8363_0
comma
id|quirk_vialatency
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8371_1
comma
id|quirk_vialatency
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8361
comma
id|quirk_vialatency
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C576
comma
id|quirk_vsfx
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C597_0
comma
id|quirk_viaetbf
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C597_0
comma
id|quirk_vt82c598_id
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C586_3
comma
id|quirk_vt82c586_acpi
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C686_4
comma
id|quirk_vt82c686_acpi
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371AB_3
comma
id|quirk_piix4_acpi
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_AL
comma
id|PCI_DEVICE_ID_AL_M7101
comma
id|quirk_ali7101_acpi
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371SB_2
comma
id|quirk_piix3_usb
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82371AB_2
comma
id|quirk_piix3_usb
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|quirk_cardbus_legacy
)brace
comma
macro_line|#ifdef CONFIG_X86_IO_APIC 
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C686
comma
id|quirk_via_ioapic
)brace
comma
macro_line|#endif
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C586_3
comma
id|quirk_via_acpi
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C686_4
comma
id|quirk_via_acpi
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C586_2
comma
id|quirk_via_irqpic
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C686_5
comma
id|quirk_via_irqpic
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C686_6
comma
id|quirk_via_irqpic
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_VIPER_7410
comma
id|quirk_amd_ioapic
)brace
comma
(brace
id|PCI_FIXUP_FINAL
comma
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_FE_GATE_700C
comma
id|quirk_amd_ordering
)brace
comma
multiline_comment|/*&n;&t; * i82380FB mobile docking controller: its PCI-to-PCI bridge&n;&t; * is subtractive decoding (transparent), and does indicate this&n;&t; * in the ProgIf. Unfortunately, the ProgIf value is wrong - 0x80&n;&t; * instead of 0x01.&n;&t; */
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82380FB
comma
id|quirk_transparent_bridge
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|pci_do_fixups
r_static
r_void
id|pci_do_fixups
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pass
comma
r_struct
id|pci_fixup
op_star
id|f
)paren
(brace
r_while
c_loop
(paren
id|f-&gt;pass
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;pass
op_eq
id|pass
op_logical_and
(paren
id|f-&gt;vendor
op_eq
id|dev-&gt;vendor
op_logical_or
id|f-&gt;vendor
op_eq
(paren
id|u16
)paren
id|PCI_ANY_ID
)paren
op_logical_and
(paren
id|f-&gt;device
op_eq
id|dev-&gt;device
op_logical_or
id|f-&gt;device
op_eq
(paren
id|u16
)paren
id|PCI_ANY_ID
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Calling quirk %p for %s&bslash;n&quot;
comma
id|f-&gt;hook
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
macro_line|#endif
id|f
op_member_access_from_pointer
id|hook
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|f
op_increment
suffix:semicolon
)brace
)brace
DECL|function|pci_fixup_device
r_void
id|pci_fixup_device
c_func
(paren
r_int
id|pass
comma
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|pci_do_fixups
c_func
(paren
id|dev
comma
id|pass
comma
id|pcibios_fixups
)paren
suffix:semicolon
id|pci_do_fixups
c_func
(paren
id|dev
comma
id|pass
comma
id|pci_fixups
)paren
suffix:semicolon
)brace
eof
