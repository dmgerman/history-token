multiline_comment|/*&n; * linux/drivers/ide/alim15x3.c&t;&t;Version 0.10&t;Jun. 9, 2000&n; *&n; *  Copyright (C) 1998-2000 Michel Aubry, Maintainer&n; *  Copyright (C) 1998-2000 Andrzej Krzysztofowicz, Maintainer&n; *  Copyright (C) 1999-2000 CJ, cjtsai@ali.com.tw, Maintainer&n; *&n; *  Copyright (C) 1998-2000 Andre Hedrick (andre@linux-ide.org)&n; *  May be copied or modified under the terms of the GNU General Public License&n; *&n; *  (U)DMA capable version of ali 1533/1543(C), 1535(D)&n; *&n; **********************************************************************&n; *  9/7/99 --Parts from the above author are included and need to be&n; *  converted into standard interface, once I finish the thought.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ata-timing.h&quot;
macro_line|#include &quot;pcihost.h&quot;
DECL|variable|m5229_revision
r_static
id|byte
id|m5229_revision
suffix:semicolon
DECL|variable|chip_is_1543c_e
r_static
id|byte
id|chip_is_1543c_e
suffix:semicolon
DECL|variable|isa_dev
r_static
r_struct
id|pci_dev
op_star
id|isa_dev
suffix:semicolon
DECL|function|ali15x3_tune_drive
r_static
r_void
id|ali15x3_tune_drive
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
r_struct
id|ata_timing
op_star
id|t
suffix:semicolon
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
r_int
id|s_time
comma
id|a_time
comma
id|c_time
suffix:semicolon
id|byte
id|s_clc
comma
id|a_clc
comma
id|r_clc
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|port
op_assign
id|hwif-&gt;unit
ques
c_cond
l_int|0x5c
suffix:colon
l_int|0x58
suffix:semicolon
r_int
id|portFIFO
op_assign
id|hwif-&gt;unit
ques
c_cond
l_int|0x55
suffix:colon
l_int|0x54
suffix:semicolon
id|byte
id|cd_dma_fifo
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pio
op_eq
l_int|255
)paren
id|pio
op_assign
id|ata_timing_mode
c_func
(paren
id|drive
comma
id|XFER_PIO
op_or
id|XFER_EPIO
)paren
suffix:semicolon
r_else
id|pio
op_assign
id|XFER_PIO_0
op_plus
id|min_t
c_func
(paren
id|byte
comma
id|pio
comma
l_int|4
)paren
suffix:semicolon
id|t
op_assign
id|ata_timing_data
c_func
(paren
id|pio
)paren
suffix:semicolon
id|s_time
op_assign
id|t-&gt;setup
suffix:semicolon
id|a_time
op_assign
id|t-&gt;active
suffix:semicolon
r_if
c_cond
(paren
(paren
id|s_clc
op_assign
(paren
id|s_time
op_star
id|system_bus_speed
op_plus
l_int|999999
)paren
op_div
l_int|1000000
)paren
op_ge
l_int|8
)paren
id|s_clc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|a_clc
op_assign
(paren
id|a_time
op_star
id|system_bus_speed
op_plus
l_int|999999
)paren
op_div
l_int|1000000
)paren
op_ge
l_int|8
)paren
id|a_clc
op_assign
l_int|0
suffix:semicolon
id|c_time
op_assign
id|t-&gt;cycle
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
(paren
id|r_clc
op_assign
(paren
(paren
id|c_time
op_minus
id|s_time
op_minus
id|a_time
)paren
op_star
id|system_bus_speed
op_plus
l_int|999999
)paren
op_div
l_int|1000000
)paren
op_ge
l_int|16
)paren
id|r_clc
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|r_clc
op_assign
(paren
id|c_time
op_star
id|system_bus_speed
op_plus
l_int|999999
)paren
op_div
l_int|1000000
op_minus
id|a_clc
op_minus
id|s_clc
)paren
)paren
(brace
id|r_clc
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|r_clc
op_ge
l_int|16
)paren
id|r_clc
op_assign
l_int|0
suffix:semicolon
)brace
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * PIO mode =&gt; ATA FIFO on, ATAPI FIFO off&n;&t; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|portFIFO
comma
op_amp
id|cd_dma_fifo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;type
op_eq
id|ATA_DISK
)paren
(brace
r_if
c_cond
(paren
id|hwif-&gt;index
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|portFIFO
comma
(paren
id|cd_dma_fifo
op_amp
l_int|0x0F
)paren
op_or
l_int|0x50
)paren
suffix:semicolon
)brace
r_else
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|portFIFO
comma
(paren
id|cd_dma_fifo
op_amp
l_int|0xF0
)paren
op_or
l_int|0x05
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|hwif-&gt;index
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|portFIFO
comma
id|cd_dma_fifo
op_amp
l_int|0x0F
)paren
suffix:semicolon
)brace
r_else
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|portFIFO
comma
id|cd_dma_fifo
op_amp
l_int|0xF0
)paren
suffix:semicolon
)brace
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|port
comma
id|s_clc
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|port
op_plus
id|drive-&gt;select.b.unit
op_plus
l_int|2
comma
(paren
id|a_clc
op_lshift
l_int|4
)paren
op_or
id|r_clc
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|ali15x3_can_ultra
r_static
id|byte
id|ali15x3_can_ultra
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
id|m5229_revision
op_le
l_int|0x20
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|m5229_revision
OL
l_int|0xC2
)paren
op_logical_and
macro_line|#ifndef CONFIG_WDC_ALI15X3
(paren
(paren
id|chip_is_1543c_e
op_logical_and
id|strstr
c_func
(paren
id|drive-&gt;id-&gt;model
comma
l_string|&quot;WDC &quot;
)paren
)paren
op_logical_or
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
)paren
)paren
(brace
macro_line|#else
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
)paren
(brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|ali15x3_ratemask
r_static
r_int
id|ali15x3_ratemask
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_int
id|map
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ali15x3_can_ultra
c_func
(paren
id|drive
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|map
op_or_assign
id|XFER_UDMA
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eighty_ninty_three
c_func
(paren
id|drive
)paren
)paren
r_return
id|map
suffix:semicolon
r_if
c_cond
(paren
id|m5229_revision
op_ge
l_int|0xC4
)paren
id|map
op_or_assign
id|XFER_UDMA_100
suffix:semicolon
r_if
c_cond
(paren
id|m5229_revision
op_ge
l_int|0xC2
)paren
id|map
op_or_assign
id|XFER_UDMA_66
suffix:semicolon
r_return
id|map
suffix:semicolon
)brace
DECL|function|ali15x3_tune_chipset
r_static
r_int
id|ali15x3_tune_chipset
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|byte
id|speed
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|drive-&gt;channel-&gt;pci_dev
suffix:semicolon
id|byte
id|unit
op_assign
(paren
id|drive-&gt;select.b.unit
op_amp
l_int|0x01
)paren
suffix:semicolon
id|byte
id|tmpbyte
op_assign
l_int|0x00
suffix:semicolon
r_int
id|m5229_udma
op_assign
id|drive-&gt;channel-&gt;unit
ques
c_cond
l_int|0x57
suffix:colon
l_int|0x56
suffix:semicolon
r_if
c_cond
(paren
id|speed
OL
id|XFER_UDMA_0
)paren
(brace
id|byte
id|ultra_enable
op_assign
(paren
id|unit
)paren
ques
c_cond
l_int|0x7f
suffix:colon
l_int|0xf7
suffix:semicolon
multiline_comment|/*&n;&t;&t; * clear &quot;ultra enable&quot; bit&n;&t;&t; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|m5229_udma
comma
op_amp
id|tmpbyte
)paren
suffix:semicolon
id|tmpbyte
op_and_assign
id|ultra_enable
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|m5229_udma
comma
id|tmpbyte
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|speed
OL
id|XFER_SW_DMA_0
)paren
id|ali15x3_tune_drive
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_else
r_if
c_cond
(paren
id|speed
op_ge
id|XFER_UDMA_0
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|m5229_udma
comma
op_amp
id|tmpbyte
)paren
suffix:semicolon
id|tmpbyte
op_and_assign
(paren
l_int|0x0f
op_lshift
(paren
(paren
l_int|1
op_minus
id|unit
)paren
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * enable ultra dma and set timing&n;&t;&t; */
id|tmpbyte
op_or_assign
(paren
(paren
l_int|0x08
op_or
(paren
(paren
l_int|4
op_minus
id|speed
)paren
op_amp
l_int|0x07
)paren
)paren
op_lshift
(paren
id|unit
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|m5229_udma
comma
id|tmpbyte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_ge
id|XFER_UDMA_3
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x4b
comma
op_amp
id|tmpbyte
)paren
suffix:semicolon
id|tmpbyte
op_or_assign
l_int|1
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4b
comma
id|tmpbyte
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
id|drive-&gt;current_speed
op_assign
id|speed
suffix:semicolon
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
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
DECL|function|config_chipset_for_dma
r_static
r_int
id|config_chipset_for_dma
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|u8
id|udma
)paren
(brace
r_int
id|map
suffix:semicolon
id|u8
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|udma
)paren
id|map
op_assign
id|ali15x3_ratemask
c_func
(paren
id|drive
)paren
suffix:semicolon
r_else
id|map
op_assign
id|XFER_SWDMA
op_or
id|XFER_MWDMA
suffix:semicolon
id|mode
op_assign
id|ata_timing_mode
c_func
(paren
id|drive
comma
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
OL
id|XFER_SW_DMA_0
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_logical_neg
id|ali15x3_tune_chipset
c_func
(paren
id|drive
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|ali15x3_udma_setup
r_static
r_int
id|ali15x3_udma_setup
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_struct
id|ata_channel
op_star
id|hwif
op_assign
id|drive-&gt;channel
suffix:semicolon
r_int
id|on
op_assign
l_int|1
suffix:semicolon
r_int
id|verbose
op_assign
l_int|1
suffix:semicolon
id|byte
id|can_ultra_dma
op_assign
id|ali15x3_can_ultra
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|m5229_revision
op_le
l_int|0x20
)paren
op_logical_and
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
)paren
(brace
id|udma_enable
c_func
(paren
id|drive
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id
op_ne
l_int|NULL
)paren
op_logical_and
(paren
(paren
id|id-&gt;capability
op_amp
l_int|1
)paren
op_ne
l_int|0
)paren
op_logical_and
id|hwif-&gt;autodma
)paren
(brace
multiline_comment|/* Consult the list of known &quot;bad&quot; drives */
r_if
c_cond
(paren
id|udma_black_list
c_func
(paren
id|drive
)paren
)paren
(brace
id|on
op_assign
l_int|0
suffix:semicolon
r_goto
id|fast_ata_pio
suffix:semicolon
)brace
id|on
op_assign
l_int|0
suffix:semicolon
id|verbose
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id-&gt;field_valid
op_amp
l_int|4
)paren
op_logical_and
(paren
id|m5229_revision
op_ge
l_int|0xC2
)paren
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x003F
)paren
(brace
multiline_comment|/* Force if Capable UltraDMA */
id|on
op_assign
id|config_chipset_for_dma
c_func
(paren
id|drive
comma
id|can_ultra_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
op_logical_and
(paren
op_logical_neg
id|on
)paren
)paren
r_goto
id|try_dma_modes
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
id|try_dma_modes
suffix:colon
r_if
c_cond
(paren
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0007
)paren
op_logical_or
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0007
)paren
)paren
(brace
multiline_comment|/* Force if Capable regular DMA modes */
id|on
op_assign
id|config_chipset_for_dma
c_func
(paren
id|drive
comma
id|can_ultra_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|on
)paren
r_goto
id|no_dma_set
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|udma_white_list
c_func
(paren
id|drive
)paren
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;eide_dma_time
OG
l_int|150
)paren
(brace
r_goto
id|no_dma_set
suffix:semicolon
)brace
multiline_comment|/* Consult the list of known &quot;good&quot; drives */
id|on
op_assign
id|config_chipset_for_dma
c_func
(paren
id|drive
comma
id|can_ultra_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|on
)paren
r_goto
id|no_dma_set
suffix:semicolon
)brace
r_else
(brace
r_goto
id|fast_ata_pio
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|id-&gt;capability
op_amp
l_int|8
)paren
op_logical_or
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
)paren
(brace
id|fast_ata_pio
suffix:colon
id|on
op_assign
l_int|0
suffix:semicolon
id|verbose
op_assign
l_int|0
suffix:semicolon
id|no_dma_set
suffix:colon
id|ali15x3_tune_drive
c_func
(paren
id|drive
comma
l_int|255
)paren
suffix:semicolon
)brace
id|udma_enable
c_func
(paren
id|drive
comma
id|on
comma
id|verbose
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ali15x3_udma_init
r_static
r_int
id|ali15x3_udma_init
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
r_if
c_cond
(paren
(paren
id|m5229_revision
OL
l_int|0xC2
)paren
op_logical_and
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
)paren
r_return
id|ide_stopped
suffix:semicolon
multiline_comment|/* try PIO instead of DMA */
r_return
id|udma_pci_init
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|ali15x3_init_chipset
r_static
r_int
r_int
id|__init
id|ali15x3_init_chipset
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|fixdma_base
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|4
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_REVISION_ID
comma
op_amp
id|m5229_revision
)paren
suffix:semicolon
id|isa_dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_AL
comma
id|PCI_DEVICE_ID_AL_M1533
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fixdma_base
)paren
(brace
multiline_comment|/*&n;&t;&t; *&n;&t;&t; */
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * enable DMA capable bit, and &quot;not&quot; simplex only&n;&t;&t; */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|fixdma_base
op_plus
l_int|2
)paren
op_amp
l_int|0x60
comma
id|fixdma_base
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|fixdma_base
op_plus
l_int|2
)paren
op_amp
l_int|0x80
)paren
id|printk
c_func
(paren
l_string|&quot;%s: simplex device: DMA will fail!!&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This checks if the controller and the cable are capable&n; * of UDMA66 transfers. It doesn&squot;t check the drives.&n; * But see note 2 below!&n; */
DECL|function|ali15x3_ata66_check
r_static
r_int
r_int
id|__init
id|ali15x3_ata66_check
c_func
(paren
r_struct
id|ata_channel
op_star
id|hwif
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|ata66
op_assign
l_int|0
suffix:semicolon
id|byte
id|cable_80_pin
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|byte
id|tmpbyte
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m5229_revision
op_ge
l_int|0xC2
)paren
(brace
multiline_comment|/*&n;&t;&t; * 1543C-B?, 1535, 1535D, 1553&n;&t;&t; * Note 1: not all &quot;motherboard&quot; support this detection&n;&t;&t; * Note 2: if no udma 66 device, the detection may &quot;error&quot;.&n;&t;&t; *         but in this case, we will not set the device to&n;&t;&t; *         ultra 66, the detection result is not important&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * enable &quot;Cable Detection&quot;, m5229, 0x4b, bit3&n;&t;&t; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x4b
comma
op_amp
id|tmpbyte
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4b
comma
id|tmpbyte
op_or
l_int|0x08
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * set south-bridge&squot;s enable bit, m1533, 0x79&n;&t;&t; */
id|pci_read_config_byte
c_func
(paren
id|isa_dev
comma
l_int|0x79
comma
op_amp
id|tmpbyte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m5229_revision
op_eq
l_int|0xC2
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * 1543C-B0 (m1533, 0x79, bit 2)&n;&t;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|isa_dev
comma
l_int|0x79
comma
id|tmpbyte
op_or
l_int|0x04
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|m5229_revision
op_ge
l_int|0xC3
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * 1553/1535 (m1533, 0x79, bit 1)&n;&t;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|isa_dev
comma
l_int|0x79
comma
id|tmpbyte
op_or
l_int|0x02
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Ultra66 cable detection (from Host View)&n;&t;&t; * m5229, 0x4a, bit0: primary, bit1: secondary 80 pin&n;&t;&t; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x4a
comma
op_amp
id|tmpbyte
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * 0x4a, bit0 is 0 =&gt; primary channel&n;&t;&t; * has 80-pin (from host view)&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmpbyte
op_amp
l_int|0x01
)paren
)paren
id|cable_80_pin
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * 0x4a, bit1 is 0 =&gt; secondary channel&n;&t;&t; * has 80-pin (from host view)&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmpbyte
op_amp
l_int|0x02
)paren
)paren
id|cable_80_pin
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Allow ata66 if cable of current channel has 80 pins&n;&t;&t; */
id|ata66
op_assign
(paren
id|hwif-&gt;unit
)paren
ques
c_cond
id|cable_80_pin
(braket
l_int|1
)braket
suffix:colon
id|cable_80_pin
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * revision 0x20 (1543-E, 1543-F)&n;&t;&t; * revision 0xC0, 0xC1 (1543C-C, 1543C-D, 1543C-E)&n;&t;&t; * clear CD-ROM DMA write bit, m5229, 0x4b, bit 7&n;&t;&t; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x4b
comma
op_amp
id|tmpbyte
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * clear bit 7&n;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4b
comma
id|tmpbyte
op_amp
l_int|0x7F
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * check m1533, 0x5e, bit 1~4 == 1001 =&gt; &amp; 00011110 = 00010010&n;&t;&t; */
id|pci_read_config_byte
c_func
(paren
id|isa_dev
comma
l_int|0x5e
comma
op_amp
id|tmpbyte
)paren
suffix:semicolon
id|chip_is_1543c_e
op_assign
(paren
(paren
id|tmpbyte
op_amp
l_int|0x1e
)paren
op_eq
l_int|0x12
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * CD_ROM DMA on (m5229, 0x53, bit0)&n;&t; *      Enable this bit even if we want to use PIO&n;&t; * PIO FIFO off (m5229, 0x53, bit1)&n;&t; *      The hardware will use 0x54h and 0x55h to control PIO FIFO&n;&t; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x53
comma
op_amp
id|tmpbyte
)paren
suffix:semicolon
id|tmpbyte
op_assign
(paren
id|tmpbyte
op_amp
(paren
op_complement
l_int|0x02
)paren
)paren
op_or
l_int|0x01
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x53
comma
id|tmpbyte
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ata66
suffix:semicolon
)brace
DECL|function|ali15x3_init_channel
r_static
r_void
id|__init
id|ali15x3_init_channel
c_func
(paren
r_struct
id|ata_channel
op_star
id|hwif
)paren
(brace
macro_line|#ifndef CONFIG_SPARC64
id|byte
id|ideic
comma
id|inmir
suffix:semicolon
id|byte
id|irq_routing_table
(braket
)braket
op_assign
(brace
op_minus
l_int|1
comma
l_int|9
comma
l_int|3
comma
l_int|10
comma
l_int|4
comma
l_int|5
comma
l_int|7
comma
l_int|6
comma
l_int|1
comma
l_int|11
comma
l_int|0
comma
l_int|12
comma
l_int|0
comma
l_int|14
comma
l_int|0
comma
l_int|15
)brace
suffix:semicolon
id|hwif-&gt;irq
op_assign
id|hwif-&gt;unit
ques
c_cond
l_int|15
suffix:colon
l_int|14
suffix:semicolon
r_if
c_cond
(paren
id|isa_dev
)paren
(brace
multiline_comment|/*&n;&t;&t; * read IDE interface control&n;&t;&t; */
id|pci_read_config_byte
c_func
(paren
id|isa_dev
comma
l_int|0x58
comma
op_amp
id|ideic
)paren
suffix:semicolon
multiline_comment|/* bit0, bit1 */
id|ideic
op_assign
id|ideic
op_amp
l_int|0x03
suffix:semicolon
multiline_comment|/* get IRQ for IDE Controller */
r_if
c_cond
(paren
(paren
id|hwif-&gt;unit
op_logical_and
id|ideic
op_eq
l_int|0x03
)paren
op_logical_or
(paren
op_logical_neg
id|hwif-&gt;unit
op_logical_and
op_logical_neg
id|ideic
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * get SIRQ1 routing table&n;&t;&t;&t; */
id|pci_read_config_byte
c_func
(paren
id|isa_dev
comma
l_int|0x44
comma
op_amp
id|inmir
)paren
suffix:semicolon
id|inmir
op_assign
id|inmir
op_amp
l_int|0x0f
suffix:semicolon
id|hwif-&gt;irq
op_assign
id|irq_routing_table
(braket
id|inmir
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hwif-&gt;unit
op_logical_and
op_logical_neg
(paren
id|ideic
op_amp
l_int|0x01
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * get SIRQ2 routing table&n;&t;&t;&t; */
id|pci_read_config_byte
c_func
(paren
id|isa_dev
comma
l_int|0x75
comma
op_amp
id|inmir
)paren
suffix:semicolon
id|inmir
op_assign
id|inmir
op_amp
l_int|0x0f
suffix:semicolon
id|hwif-&gt;irq
op_assign
id|irq_routing_table
(braket
id|inmir
)braket
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_SPARC64 */
id|hwif-&gt;tuneproc
op_assign
op_amp
id|ali15x3_tune_drive
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
id|ali15x3_tune_chipset
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_if
c_cond
(paren
(paren
id|hwif-&gt;dma_base
)paren
op_logical_and
(paren
id|m5229_revision
op_ge
l_int|0x20
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * M1543C or newer for DMAing&n;&t;&t; */
id|hwif-&gt;udma_init
op_assign
id|ali15x3_udma_init
suffix:semicolon
id|hwif-&gt;udma_setup
op_assign
id|ali15x3_udma_setup
suffix:semicolon
id|hwif-&gt;autodma
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|noautodma
)paren
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
macro_line|#else
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|ali15x3_init_dma
r_static
r_void
id|__init
id|ali15x3_init_dma
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
comma
r_int
r_int
id|dmabase
)paren
(brace
r_if
c_cond
(paren
(paren
id|dmabase
)paren
op_logical_and
(paren
id|m5229_revision
OL
l_int|0x20
)paren
)paren
r_return
suffix:semicolon
id|ata_init_dma
c_func
(paren
id|ch
comma
id|dmabase
)paren
suffix:semicolon
)brace
multiline_comment|/* module data table */
DECL|variable|__initdata
r_static
r_struct
id|ata_pci_device
id|chipsets
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_AL
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_AL_M5219
comma
multiline_comment|/* FIXME: Perhaps we should use the same init routines&n;&t;&t; * as below here. */
id|enablebits
suffix:colon
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
comma
id|flags
suffix:colon
id|ATA_F_SIMPLEX
)brace
comma
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_AL
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_AL_M5229
comma
id|init_chipset
suffix:colon
id|ali15x3_init_chipset
comma
id|ata66_check
suffix:colon
id|ali15x3_ata66_check
comma
id|init_channel
suffix:colon
id|ali15x3_init_channel
comma
id|init_dma
suffix:colon
id|ali15x3_init_dma
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
)brace
)brace
suffix:semicolon
DECL|function|init_ali15x3
r_int
id|__init
id|init_ali15x3
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|ARRAY_SIZE
c_func
(paren
id|chipsets
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
id|ata_register_chipset
c_func
(paren
op_amp
id|chipsets
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
