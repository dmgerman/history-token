multiline_comment|/*&n; * linux/drivers/ide/sis5513.c&t;&t;Version 0.13&t;March 6, 2002&n; *&n; * Copyright (C) 1999-2000&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; * Copyright (C) 2002&t;&t;Lionel Bouton &lt;Lionel.Bouton@inet6.fr&gt;, Maintainer&n; * May be copied or modified under the terms of the GNU General Public License&n; *&n; *&n; * Thanks :&n; *&n; * SiS Taiwan&t;&t;: for direct support and hardware.&n; * Daniela Engert&t;: for initial ATA100 advices and numerous others.&n; * John Fremlin, Manfred Spraul :&n; *&t;&t;&t;  for checking code correctness, providing patches.&n; */
multiline_comment|/*&n; * Original tests and design on the SiS620/5513 chipset.&n; * ATA100 tests and design on the SiS735/5513 chipset.&n; * ATA16/33 design from specs&n; */
multiline_comment|/*&n; * TODO:&n; *&t;- Get ridden of SisHostChipInfo[] completness dependancy.&n; *&t;- Get ATA-133 datasheets, implement ATA-133 init code.&n; *&t;- Are there pre-ATA_16 SiS chips ? -&gt; tune init code for them&n; *&t;  or remove ATA_00 define&n; *&t;- More checks in the config registers (force values instead of&n; *&t;  relying on the BIOS setting them correctly).&n; *&t;- Further optimisations ?&n; *&t;  . for example ATA66+ regs 0x48 &amp; 0x4A&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;ata-timing.h&quot;
macro_line|#include &quot;pcihost.h&quot;
multiline_comment|/* When DEBUG is defined it outputs initial PCI config register&n;   values and changes made to them by the driver */
singleline_comment|// #define DEBUG
multiline_comment|/* When BROKEN_LEVEL is defined it limits the DMA mode&n;   at boot time to its value */
singleline_comment|// #define BROKEN_LEVEL XFER_SW_DMA_0
multiline_comment|/* Miscellaneaous flags */
DECL|macro|SIS5513_LATENCY
mdefine_line|#define SIS5513_LATENCY&t;&t;0x01
multiline_comment|/* registers layout and init values are chipset family dependant */
multiline_comment|/* 1/ define families */
DECL|macro|ATA_00
mdefine_line|#define ATA_00&t;&t;0x00
DECL|macro|ATA_16
mdefine_line|#define ATA_16&t;&t;0x01
DECL|macro|ATA_33
mdefine_line|#define ATA_33&t;&t;0x02
DECL|macro|ATA_66
mdefine_line|#define ATA_66&t;&t;0x03
DECL|macro|ATA_100a
mdefine_line|#define ATA_100a&t;0x04&t;
singleline_comment|// SiS730 is ATA100 with ATA66 layout
DECL|macro|ATA_100
mdefine_line|#define ATA_100&t;&t;0x05
DECL|macro|ATA_133
mdefine_line|#define ATA_133&t;&t;0x06
multiline_comment|/* 2/ variable holding the controller chipset family value */
DECL|variable|chipset_family
r_static
r_int
r_char
id|chipset_family
suffix:semicolon
multiline_comment|/*&n; * Debug code: following IDE config registers&squot; changes&n; */
macro_line|#ifdef DEBUG
multiline_comment|/* Copy of IDE Config registers 0x00 -&gt; 0x57&n;   Fewer might be used depending on the actual chipset */
DECL|variable|ide_regs_copy
r_static
r_int
r_char
id|ide_regs_copy
(braket
l_int|0x58
)braket
suffix:semicolon
DECL|function|sis5513_max_config_register
r_static
id|byte
id|sis5513_max_config_register
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|chipset_family
)paren
(brace
r_case
id|ATA_00
suffix:colon
r_case
id|ATA_16
suffix:colon
r_return
l_int|0x4f
suffix:semicolon
r_case
id|ATA_33
suffix:colon
r_return
l_int|0x52
suffix:semicolon
r_case
id|ATA_66
suffix:colon
r_case
id|ATA_100a
suffix:colon
r_case
id|ATA_100
suffix:colon
r_case
id|ATA_133
suffix:colon
r_default
suffix:colon
r_return
l_int|0x57
suffix:semicolon
)brace
)brace
multiline_comment|/* Read config registers, print differences from previous read */
DECL|function|sis5513_load_verify_registers
r_static
r_void
id|sis5513_load_verify_registers
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_char
op_star
id|info
)paren
(brace
r_int
id|i
suffix:semicolon
id|byte
id|reg_val
suffix:semicolon
id|byte
id|changed
op_assign
l_int|0
suffix:semicolon
id|byte
id|max
op_assign
id|sis5513_max_config_register
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SIS5513: %s, changed registers:&bslash;n&quot;
comma
id|info
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
op_le
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|i
comma
op_amp
id|reg_val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg_val
op_ne
id|ide_regs_copy
(braket
id|i
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%0#x: %0#x -&gt; %0#x&bslash;n&quot;
comma
id|i
comma
id|ide_regs_copy
(braket
id|i
)braket
comma
id|reg_val
)paren
suffix:semicolon
id|ide_regs_copy
(braket
id|i
)braket
op_assign
id|reg_val
suffix:semicolon
id|changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|changed
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;none&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Load config registers, no printing */
DECL|function|sis5513_load_registers
r_static
r_void
id|sis5513_load_registers
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
id|byte
id|max
op_assign
id|sis5513_max_config_register
c_func
(paren
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
op_le
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|i
comma
op_amp
(paren
id|ide_regs_copy
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Print a register */
DECL|function|sis5513_print_register
r_static
r_void
id|sis5513_print_register
c_func
(paren
r_int
id|reg
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %0#x:%0#x&quot;
comma
id|reg
comma
id|ide_regs_copy
(braket
id|reg
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Print valuable registers */
DECL|function|sis5513_print_registers
r_static
r_void
id|sis5513_print_registers
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_char
op_star
id|marker
)paren
(brace
r_int
id|i
suffix:semicolon
id|byte
id|max
op_assign
id|sis5513_max_config_register
c_func
(paren
)paren
suffix:semicolon
id|sis5513_load_registers
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SIS5513 %s&bslash;n&quot;
comma
id|marker
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SIS5513 dump:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0x00
suffix:semicolon
id|i
OL
l_int|0x40
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|0x10
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n             &quot;
)paren
suffix:semicolon
id|sis5513_print_register
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
l_int|49
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sis5513_print_register
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n             &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
op_le
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sis5513_print_register
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Devices supported&n; */
r_static
r_const
r_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|host_id
r_int
r_int
id|host_id
suffix:semicolon
DECL|member|chipset_family
r_int
r_char
id|chipset_family
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|variable|SiSHostChipInfo
)brace
id|SiSHostChipInfo
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;SiS750&quot;
comma
id|PCI_DEVICE_ID_SI_750
comma
id|ATA_100
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS745&quot;
comma
id|PCI_DEVICE_ID_SI_745
comma
id|ATA_100
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS740&quot;
comma
id|PCI_DEVICE_ID_SI_740
comma
id|ATA_100
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS735&quot;
comma
id|PCI_DEVICE_ID_SI_735
comma
id|ATA_100
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS730&quot;
comma
id|PCI_DEVICE_ID_SI_730
comma
id|ATA_100a
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS650&quot;
comma
id|PCI_DEVICE_ID_SI_650
comma
id|ATA_100
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS645&quot;
comma
id|PCI_DEVICE_ID_SI_645
comma
id|ATA_100
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS635&quot;
comma
id|PCI_DEVICE_ID_SI_635
comma
id|ATA_100
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS640&quot;
comma
id|PCI_DEVICE_ID_SI_640
comma
id|ATA_66
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS630&quot;
comma
id|PCI_DEVICE_ID_SI_630
comma
id|ATA_66
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS620&quot;
comma
id|PCI_DEVICE_ID_SI_620
comma
id|ATA_66
comma
id|SIS5513_LATENCY
)brace
comma
(brace
l_string|&quot;SiS540&quot;
comma
id|PCI_DEVICE_ID_SI_540
comma
id|ATA_66
comma
l_int|0
)brace
comma
(brace
l_string|&quot;SiS530&quot;
comma
id|PCI_DEVICE_ID_SI_530
comma
id|ATA_66
comma
l_int|0
)brace
comma
(brace
l_string|&quot;SiS5600&quot;
comma
id|PCI_DEVICE_ID_SI_5600
comma
id|ATA_33
comma
l_int|0
)brace
comma
(brace
l_string|&quot;SiS5598&quot;
comma
id|PCI_DEVICE_ID_SI_5598
comma
id|ATA_33
comma
l_int|0
)brace
comma
(brace
l_string|&quot;SiS5597&quot;
comma
id|PCI_DEVICE_ID_SI_5597
comma
id|ATA_33
comma
l_int|0
)brace
comma
(brace
l_string|&quot;SiS5591&quot;
comma
id|PCI_DEVICE_ID_SI_5591
comma
id|ATA_33
comma
l_int|0
)brace
comma
(brace
l_string|&quot;SiS5513&quot;
comma
id|PCI_DEVICE_ID_SI_5513
comma
id|ATA_16
comma
l_int|0
)brace
comma
(brace
l_string|&quot;SiS5511&quot;
comma
id|PCI_DEVICE_ID_SI_5511
comma
id|ATA_16
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* Cycle time bits and values vary accross chip dma capabilities&n;   These three arrays hold the register layout and the values to set.&n;   Indexed by chipset_family and (dma_mode - XFER_UDMA_0) */
DECL|variable|cycle_time_offset
r_static
id|byte
id|cycle_time_offset
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|5
comma
l_int|4
comma
l_int|4
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|cycle_time_range
r_static
id|byte
id|cycle_time_range
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|4
)brace
suffix:semicolon
DECL|variable|cycle_time_value
r_static
id|byte
id|cycle_time_value
(braket
)braket
(braket
id|XFER_UDMA_5
op_minus
id|XFER_UDMA_0
op_plus
l_int|1
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* no udma */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* no udma */
(brace
l_int|3
comma
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|7
comma
l_int|5
comma
l_int|3
comma
l_int|2
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|7
comma
l_int|5
comma
l_int|3
comma
l_int|2
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|11
comma
l_int|7
comma
l_int|5
comma
l_int|4
comma
l_int|2
comma
l_int|1
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
multiline_comment|/* not yet known, ask SiS */
)brace
suffix:semicolon
DECL|variable|host_dev
r_static
r_struct
id|pci_dev
op_star
id|host_dev
op_assign
l_int|NULL
suffix:semicolon
DECL|function|sis5513_modes_map
r_static
r_int
id|__init
id|sis5513_modes_map
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
)paren
(brace
r_int
id|map
op_assign
id|XFER_EPIO
op_or
id|XFER_SWDMA
op_or
id|XFER_MWDMA
suffix:semicolon
r_switch
c_cond
(paren
id|chipset_family
)paren
(brace
r_case
id|ATA_133
suffix:colon
multiline_comment|/* map |= XFER_UDMA_133; */
r_case
id|ATA_100
suffix:colon
r_case
id|ATA_100a
suffix:colon
id|map
op_or_assign
id|XFER_UDMA_100
suffix:semicolon
r_case
id|ATA_66
suffix:colon
id|map
op_or_assign
id|XFER_UDMA_66
suffix:semicolon
r_case
id|ATA_33
suffix:colon
id|map
op_or_assign
id|XFER_UDMA
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|map
suffix:semicolon
)brace
multiline_comment|/*&n; * Configuration functions&n; */
multiline_comment|/* Enables per-drive prefetch and postwrite */
DECL|function|config_drive_art_rwp
r_static
r_void
id|config_drive_art_rwp
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_struct
id|ata_channel
op_star
id|hwif
op_assign
id|drive-&gt;channel
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|u8
id|reg4bh
op_assign
l_int|0
suffix:semicolon
id|u8
id|rw_prefetch
op_assign
(paren
l_int|0x11
op_lshift
id|drive-&gt;dn
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;SIS5513: config_drive_art_rwp, drive %d&bslash;n&quot;
comma
id|drive-&gt;dn
)paren
suffix:semicolon
id|sis5513_load_verify_registers
c_func
(paren
id|dev
comma
l_string|&quot;config_drive_art_rwp start&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
r_return
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x4b
comma
op_amp
id|reg4bh
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|reg4bh
op_amp
id|rw_prefetch
)paren
op_ne
id|rw_prefetch
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4b
comma
id|reg4bh
op_or
id|rw_prefetch
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|sis5513_load_verify_registers
c_func
(paren
id|dev
comma
l_string|&quot;config_drive_art_rwp end&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Set per-drive active and recovery time */
DECL|function|config_art_rwp_pio
r_static
r_int
id|config_art_rwp_pio
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
r_struct
id|ata_channel
op_star
id|hwif
op_assign
id|drive-&gt;channel
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|u8
id|drive_pci
comma
id|test1
comma
id|test2
suffix:semicolon
macro_line|#ifdef DEBUG
id|sis5513_load_verify_registers
c_func
(paren
id|dev
comma
l_string|&quot;config_drive_art_rwp_pio start&quot;
)paren
suffix:semicolon
macro_line|#endif
id|config_drive_art_rwp
c_func
(paren
id|drive
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;SIS5513: config_drive_art_rwp_pio, drive %d, pio %d, timing %d&bslash;n&quot;
comma
id|drive-&gt;dn
comma
id|pio
comma
id|timing
)paren
suffix:semicolon
macro_line|#endif
id|drive_pci
op_assign
l_int|0x40
op_plus
(paren
id|drive-&gt;dn
op_lshift
l_int|1
)paren
suffix:semicolon
multiline_comment|/* register layout changed with newer ATA100 chips */
r_if
c_cond
(paren
id|chipset_family
OL
id|ATA_100
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|drive_pci
comma
op_amp
id|test1
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|drive_pci
op_plus
l_int|1
comma
op_amp
id|test2
)paren
suffix:semicolon
multiline_comment|/* Clear active and recovery timings */
id|test1
op_and_assign
op_complement
l_int|0x0F
suffix:semicolon
id|test2
op_and_assign
op_complement
l_int|0x07
suffix:semicolon
r_switch
c_cond
(paren
id|pio
)paren
(brace
r_case
l_int|4
suffix:colon
id|test1
op_or_assign
l_int|0x01
suffix:semicolon
id|test2
op_or_assign
l_int|0x03
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|test1
op_or_assign
l_int|0x03
suffix:semicolon
id|test2
op_or_assign
l_int|0x03
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|test1
op_or_assign
l_int|0x04
suffix:semicolon
id|test2
op_or_assign
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|test1
op_or_assign
l_int|0x07
suffix:semicolon
id|test2
op_or_assign
l_int|0x06
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|drive_pci
comma
id|test1
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|drive_pci
op_plus
l_int|1
comma
id|test2
)paren
suffix:semicolon
)brace
r_else
(brace
r_switch
c_cond
(paren
id|pio
)paren
(brace
multiline_comment|/*   active  recovery&n;&t;&t;&t;&t;&t;  v     v */
r_case
l_int|4
suffix:colon
id|test1
op_assign
l_int|0x30
op_or
l_int|0x01
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|test1
op_assign
l_int|0x30
op_or
l_int|0x03
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|test1
op_assign
l_int|0x40
op_or
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|test1
op_assign
l_int|0x60
op_or
l_int|0x07
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|drive_pci
comma
id|test1
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|sis5513_load_verify_registers
c_func
(paren
id|dev
comma
l_string|&quot;config_drive_art_rwp_pio start&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|XFER_PIO_0
op_plus
id|min_t
c_func
(paren
id|u8
comma
id|pio
comma
l_int|4
)paren
)paren
suffix:semicolon
)brace
DECL|function|sis5513_tune_chipset
r_static
r_int
id|sis5513_tune_chipset
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|u8
id|speed
)paren
(brace
r_struct
id|ata_channel
op_star
id|hwif
op_assign
id|drive-&gt;channel
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|byte
id|drive_pci
comma
id|reg
suffix:semicolon
macro_line|#ifdef DEBUG
id|sis5513_load_verify_registers
c_func
(paren
id|dev
comma
l_string|&quot;sis5513_tune_chipset start&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SIS5513: sis5513_tune_chipset, drive %d, speed %d&bslash;n&quot;
comma
id|drive-&gt;dn
comma
id|speed
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|drive-&gt;dn
OG
l_int|3
)paren
multiline_comment|/* FIXME: remove this  --bkz */
r_return
l_int|1
suffix:semicolon
id|drive_pci
op_assign
l_int|0x40
op_plus
(paren
id|drive-&gt;dn
op_lshift
l_int|1
)paren
suffix:semicolon
macro_line|#ifdef BROKEN_LEVEL
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;SIS5513: BROKEN_LEVEL activated, speed=%d -&gt; speed=%d&bslash;n&quot;
comma
id|speed
comma
id|BROKEN_LEVEL
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|speed
OG
id|BROKEN_LEVEL
)paren
id|speed
op_assign
id|BROKEN_LEVEL
suffix:semicolon
macro_line|#endif
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|drive_pci
op_plus
l_int|1
comma
op_amp
id|reg
)paren
suffix:semicolon
multiline_comment|/* Disable UDMA bit for non UDMA modes on UDMA chips */
r_if
c_cond
(paren
(paren
id|speed
OL
id|XFER_UDMA_0
)paren
op_logical_and
(paren
id|chipset_family
OG
id|ATA_16
)paren
)paren
(brace
id|reg
op_and_assign
l_int|0x7F
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|drive_pci
op_plus
l_int|1
comma
id|reg
)paren
suffix:semicolon
)brace
multiline_comment|/* Config chip for mode */
r_switch
c_cond
(paren
id|speed
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_case
id|XFER_UDMA_5
suffix:colon
r_case
id|XFER_UDMA_4
suffix:colon
r_case
id|XFER_UDMA_3
suffix:colon
r_case
id|XFER_UDMA_2
suffix:colon
r_case
id|XFER_UDMA_1
suffix:colon
r_case
id|XFER_UDMA_0
suffix:colon
multiline_comment|/* Force the UDMA bit on if we want to use UDMA */
id|reg
op_or_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* clean reg cycle time bits */
id|reg
op_and_assign
op_complement
(paren
(paren
l_int|0xFF
op_rshift
(paren
l_int|8
op_minus
id|cycle_time_range
(braket
id|chipset_family
)braket
)paren
)paren
op_lshift
id|cycle_time_offset
(braket
id|chipset_family
)braket
)paren
suffix:semicolon
multiline_comment|/* set reg cycle time bits */
id|reg
op_or_assign
id|cycle_time_value
(braket
id|chipset_family
op_minus
id|ATA_00
)braket
(braket
id|speed
op_minus
id|XFER_UDMA_0
)braket
op_lshift
id|cycle_time_offset
(braket
id|chipset_family
)braket
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|drive_pci
op_plus
l_int|1
comma
id|reg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_2
suffix:colon
r_case
id|XFER_MW_DMA_1
suffix:colon
r_case
id|XFER_MW_DMA_0
suffix:colon
r_case
id|XFER_SW_DMA_2
suffix:colon
r_case
id|XFER_SW_DMA_1
suffix:colon
r_case
id|XFER_SW_DMA_0
suffix:colon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
r_case
id|XFER_PIO_4
suffix:colon
r_case
id|XFER_PIO_3
suffix:colon
r_case
id|XFER_PIO_2
suffix:colon
r_case
id|XFER_PIO_1
suffix:colon
r_case
id|XFER_PIO_0
suffix:colon
r_return
id|config_art_rwp_pio
c_func
(paren
id|drive
comma
id|speed
op_minus
id|XFER_PIO_0
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|config_art_rwp_pio
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|sis5513_load_verify_registers
c_func
(paren
id|dev
comma
l_string|&quot;sis5513_tune_chipset end&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
)brace
DECL|function|sis5513_tune_drive
r_static
r_void
id|sis5513_tune_drive
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
r_if
c_cond
(paren
id|pio
op_eq
l_int|255
)paren
id|pio
op_assign
id|ata_best_pio_mode
c_func
(paren
id|drive
)paren
op_minus
id|XFER_PIO_0
suffix:semicolon
(paren
r_void
)paren
id|config_art_rwp_pio
c_func
(paren
id|drive
comma
id|min_t
c_func
(paren
id|u8
comma
id|pio
comma
l_int|4
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Chip detection and general config */
DECL|function|pci_init_sis5513
r_static
r_int
r_int
id|__init
id|pci_init_sis5513
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
id|host
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Find the chip */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|SiSHostChipInfo
)paren
op_logical_and
op_logical_neg
id|host_dev
suffix:semicolon
id|i
op_increment
)paren
(brace
id|host
op_assign
id|pci_find_device
(paren
id|PCI_VENDOR_ID_SI
comma
id|SiSHostChipInfo
(braket
id|i
)braket
dot
id|host_id
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
r_continue
suffix:semicolon
id|host_dev
op_assign
id|host
suffix:semicolon
id|chipset_family
op_assign
id|SiSHostChipInfo
(braket
id|i
)braket
dot
id|chipset_family
suffix:semicolon
id|printk
c_func
(paren
id|SiSHostChipInfo
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|sis5513_print_registers
c_func
(paren
id|dev
comma
l_string|&quot;pci_init_sis5513 start&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|SiSHostChipInfo
(braket
id|i
)braket
dot
id|flags
op_amp
id|SIS5513_LATENCY
)paren
(brace
id|byte
id|latency
op_assign
(paren
id|chipset_family
op_eq
id|ATA_100
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0x10
suffix:semicolon
multiline_comment|/* Lacking specs */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
id|latency
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Make general config ops here&n;&t;   1/ tell IDE channels to operate in Compabitility mode only&n;&t;   2/ tell old chips to allow per drive IDE timings */
r_if
c_cond
(paren
id|host_dev
)paren
(brace
id|byte
id|reg
suffix:semicolon
r_switch
c_cond
(paren
id|chipset_family
)paren
(brace
r_case
id|ATA_133
suffix:colon
r_case
id|ATA_100
suffix:colon
multiline_comment|/* Set compatibility bit */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x49
comma
op_amp
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_amp
l_int|0x01
)paren
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x49
comma
id|reg
op_or
l_int|0x01
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ATA_100a
suffix:colon
r_case
id|ATA_66
suffix:colon
multiline_comment|/* On ATA_66 chips the bit was elsewhere */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x52
comma
op_amp
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_amp
l_int|0x04
)paren
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x52
comma
id|reg
op_or
l_int|0x04
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ATA_33
suffix:colon
multiline_comment|/* On ATA_33 we didn&squot;t have a single bit to set */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x09
comma
op_amp
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|reg
op_amp
l_int|0x0f
)paren
op_ne
l_int|0x00
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x09
comma
id|reg
op_amp
l_int|0xf0
)paren
suffix:semicolon
)brace
r_case
id|ATA_16
suffix:colon
multiline_comment|/* force per drive recovery and active timings&n;&t;&t;&t;&t;   needed on ATA_33 and below chips */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x52
comma
op_amp
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_amp
l_int|0x08
)paren
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x52
comma
id|reg
op_or
l_int|0x08
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ATA_00
suffix:colon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG
id|sis5513_load_verify_registers
c_func
(paren
id|dev
comma
l_string|&quot;pci_init_sis5513 end&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ata66_sis5513
r_static
r_int
r_int
id|__init
id|ata66_sis5513
c_func
(paren
r_struct
id|ata_channel
op_star
id|hwif
)paren
(brace
id|u8
id|reg48h
comma
id|ata66
op_assign
l_int|0
suffix:semicolon
id|u8
id|mask
op_assign
id|hwif-&gt;unit
ques
c_cond
l_int|0x20
suffix:colon
l_int|0x10
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|hwif-&gt;pci_dev
comma
l_int|0x48
comma
op_amp
id|reg48h
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chipset_family
op_ge
id|ATA_66
)paren
(brace
id|ata66
op_assign
(paren
id|reg48h
op_amp
id|mask
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
r_return
id|ata66
suffix:semicolon
)brace
DECL|function|ide_init_sis5513
r_static
r_void
id|__init
id|ide_init_sis5513
c_func
(paren
r_struct
id|ata_channel
op_star
id|hwif
)paren
(brace
id|hwif-&gt;irq
op_assign
id|hwif-&gt;unit
ques
c_cond
l_int|15
suffix:colon
l_int|14
suffix:semicolon
id|hwif-&gt;udma_four
op_assign
id|ata66_sis5513
c_func
(paren
id|hwif
)paren
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
op_amp
id|sis5513_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|sis5513_tune_chipset
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_if
c_cond
(paren
id|hwif-&gt;dma_base
op_logical_and
id|host_dev
op_logical_and
id|chipset_family
OG
id|ATA_16
)paren
(brace
id|hwif-&gt;highmem
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;modes_map
op_assign
id|sis5513_modes_map
c_func
(paren
id|hwif
)paren
suffix:semicolon
id|hwif-&gt;udma_setup
op_assign
id|udma_generic_setup
suffix:semicolon
)brace
macro_line|#endif
r_return
suffix:semicolon
)brace
multiline_comment|/* module data table */
DECL|variable|__initdata
r_static
r_struct
id|ata_pci_device
id|chipset
id|__initdata
op_assign
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_SI
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_SI_5513
comma
id|init_chipset
suffix:colon
id|pci_init_sis5513
comma
id|init_channel
suffix:colon
id|ide_init_sis5513
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x4a
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x4a
comma
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
comma
)brace
suffix:semicolon
DECL|function|init_sis5513
r_int
id|__init
id|init_sis5513
c_func
(paren
r_void
)paren
(brace
id|ata_register_chipset
c_func
(paren
op_amp
id|chipset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
