multiline_comment|/*&n; *&n; * aec62xx.c, v1.2 2002/05/24&n; *&n; *  Copyright (c) 2002 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;Andre Hedrick&n; */
multiline_comment|/*&n; * AEC 6210UF (ATP850UF), AEC6260 (ATP860) and AEC6280 (ATP865) IDE driver for Linux.&n; *&n; * UDMA66 and higher modes are autoenabled only in case the BIOS has detected a&n; * 80 wire cable. To ignore the BIOS data and assume the cable is present, use&n; * &squot;ide0=ata66&squot; or &squot;ide1=ata66&squot; on the kernel command line.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ata-timing.h&quot;
macro_line|#include &quot;pcihost.h&quot;
DECL|macro|AEC_DRIVE_TIMING
mdefine_line|#define AEC_DRIVE_TIMING&t;0x40
DECL|macro|AEC_UDMA_NEW
mdefine_line|#define AEC_UDMA_NEW&t;&t;0x44
DECL|macro|AEC_MISC
mdefine_line|#define AEC_MISC&t;&t;0x49
DECL|macro|AEC_IDE_ENABLE
mdefine_line|#define AEC_IDE_ENABLE&t;&t;0x4a
DECL|macro|AEC_UDMA_OLD
mdefine_line|#define AEC_UDMA_OLD&t;&t;0x54
DECL|macro|AEC_BM_STAT_PCH
mdefine_line|#define AEC_BM_STAT_PCH&t;&t;0x02
DECL|macro|AEC_BM_STAT_SCH
mdefine_line|#define AEC_BM_STAT_SCH&t;&t;0x0a
DECL|macro|AEC_PLLCLK_ATA133
mdefine_line|#define AEC_PLLCLK_ATA133&t;0x10
DECL|macro|AEC_CABLEPINS_INPUT
mdefine_line|#define AEC_CABLEPINS_INPUT&t;0x10
DECL|variable|aec_cyc2udma
r_static
r_int
r_char
id|aec_cyc2udma
(braket
l_int|9
)braket
op_assign
(brace
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|4
comma
l_int|3
comma
l_int|2
comma
l_int|2
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|aec_cyc2act
r_static
r_int
r_char
id|aec_cyc2act
(braket
l_int|16
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
)brace
suffix:semicolon
DECL|variable|aec_cyc2rec
r_static
r_int
r_char
id|aec_cyc2rec
(braket
l_int|16
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|0
comma
l_int|12
comma
l_int|13
comma
l_int|14
)brace
suffix:semicolon
multiline_comment|/*&n; * aec_set_speed_old() writes timing values to&n; * the chipset registers for ATP850UF&n; */
DECL|function|aec_set_speed_old
r_static
r_void
id|aec_set_speed_old
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|dn
comma
r_struct
id|ata_timing
op_star
id|timing
)paren
(brace
r_int
r_char
id|t
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AEC_DRIVE_TIMING
op_plus
(paren
id|dn
op_lshift
l_int|1
)paren
comma
id|aec_cyc2act
(braket
id|FIT
c_func
(paren
id|timing-&gt;active
comma
l_int|0
comma
l_int|15
)paren
)braket
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AEC_DRIVE_TIMING
op_plus
(paren
id|dn
op_lshift
l_int|1
)paren
op_plus
l_int|1
comma
id|aec_cyc2rec
(braket
id|FIT
c_func
(paren
id|timing-&gt;recover
comma
l_int|0
comma
l_int|15
)paren
)braket
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AEC_UDMA_OLD
comma
op_amp
id|t
)paren
suffix:semicolon
id|t
op_and_assign
op_complement
(paren
l_int|3
op_lshift
(paren
id|dn
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timing-&gt;udma
)paren
id|t
op_or_assign
(paren
l_int|5
op_minus
id|FIT
c_func
(paren
id|timing-&gt;udma
comma
l_int|2
comma
l_int|4
)paren
)paren
op_lshift
(paren
id|dn
op_lshift
l_int|1
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AEC_UDMA_OLD
comma
id|t
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * aec_set_speed_new() writes timing values to the chipset registers for all&n; * other Artop chips&n; */
DECL|function|aec_set_speed_new
r_static
r_void
id|aec_set_speed_new
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|dn
comma
r_struct
id|ata_timing
op_star
id|timing
)paren
(brace
r_int
r_char
id|t
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AEC_DRIVE_TIMING
op_plus
id|dn
comma
(paren
id|aec_cyc2act
(braket
id|FIT
c_func
(paren
id|timing-&gt;active
comma
l_int|0
comma
l_int|15
)paren
)braket
op_lshift
l_int|4
)paren
op_or
id|aec_cyc2rec
(braket
id|FIT
c_func
(paren
id|timing-&gt;recover
comma
l_int|0
comma
l_int|15
)paren
)braket
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AEC_UDMA_NEW
op_plus
(paren
id|dn
op_rshift
l_int|1
)paren
comma
op_amp
id|t
)paren
suffix:semicolon
id|t
op_and_assign
op_complement
(paren
l_int|0xf
op_lshift
(paren
(paren
id|dn
op_amp
l_int|1
)paren
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timing-&gt;udma
)paren
(brace
r_if
c_cond
(paren
id|timing-&gt;udma
op_ge
l_int|2
)paren
id|t
op_or_assign
id|aec_cyc2udma
(braket
id|FIT
c_func
(paren
id|timing-&gt;udma
comma
l_int|2
comma
l_int|8
)paren
)braket
op_lshift
(paren
(paren
id|dn
op_amp
l_int|1
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timing-&gt;mode
op_eq
id|XFER_UDMA_5
)paren
id|t
op_or_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|timing-&gt;mode
op_eq
id|XFER_UDMA_6
)paren
id|t
op_or_assign
l_int|7
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AEC_UDMA_NEW
op_plus
(paren
id|dn
op_rshift
l_int|1
)paren
comma
id|t
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * aec_set_drive() computes timing values configures the drive and&n; * the chipset to a desired transfer mode. It also can be called&n; * by upper layers.&n; */
DECL|function|aec_set_drive
r_static
r_int
id|aec_set_drive
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
r_char
id|speed
)paren
(brace
r_struct
id|ata_timing
id|t
suffix:semicolon
r_int
id|T
comma
id|UT
suffix:semicolon
r_int
id|aec_old
suffix:semicolon
id|aec_old
op_assign
(paren
id|drive-&gt;channel-&gt;pci_dev-&gt;device
op_eq
id|PCI_DEVICE_ID_ARTOP_ATP850UF
)paren
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_ne
id|XFER_PIO_SLOW
op_logical_and
id|speed
op_ne
id|drive-&gt;current_speed
)paren
r_if
c_cond
(paren
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|speed
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ide%d: Drive %d didn&squot;t accept speed setting. Oh, well.&bslash;n&quot;
comma
id|drive-&gt;dn
op_rshift
l_int|1
comma
id|drive-&gt;dn
op_amp
l_int|1
)paren
suffix:semicolon
id|T
op_assign
l_int|1000000000
op_div
id|system_bus_speed
suffix:semicolon
id|UT
op_assign
id|T
op_div
(paren
id|aec_old
ques
c_cond
l_int|1
suffix:colon
l_int|2
)paren
suffix:semicolon
id|ata_timing_compute
c_func
(paren
id|drive
comma
id|speed
comma
op_amp
id|t
comma
id|T
comma
id|UT
)paren
suffix:semicolon
id|ata_timing_merge_8bit
c_func
(paren
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aec_old
)paren
id|aec_set_speed_old
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
id|drive-&gt;dn
comma
op_amp
id|t
)paren
suffix:semicolon
r_else
id|aec_set_speed_new
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
id|drive-&gt;dn
comma
op_amp
id|t
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * aec62xx_tune_drive() is a callback from upper layers for&n; * PIO-only tuning.&n; */
DECL|function|aec62xx_tune_drive
r_static
r_void
id|aec62xx_tune_drive
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
r_char
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
(brace
id|aec_set_drive
c_func
(paren
id|drive
comma
id|ata_timing_mode
c_func
(paren
id|drive
comma
id|XFER_PIO
op_or
id|XFER_EPIO
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|aec_set_drive
c_func
(paren
id|drive
comma
id|XFER_PIO_0
op_plus
id|min_t
c_func
(paren
id|byte
comma
id|pio
comma
l_int|5
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
DECL|function|aec62xx_modes_map
r_static
r_int
id|__init
id|aec62xx_modes_map
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
)paren
(brace
id|u32
id|bmide
op_assign
id|pci_resource_start
c_func
(paren
id|ch-&gt;pci_dev
comma
l_int|4
)paren
suffix:semicolon
r_int
id|map
suffix:semicolon
id|map
op_assign
id|XFER_EPIO
op_or
id|XFER_SWDMA
op_or
id|XFER_MWDMA
op_or
id|XFER_UDMA
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;udma_four
)paren
r_switch
c_cond
(paren
id|ch-&gt;pci_dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_ARTOP_ATP865R
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP865
suffix:colon
multiline_comment|/* Can&squot;t use these modes simultaneously,&n;&t;&t;&t;&t;   based on which PLL clock was chosen. */
id|map
op_or_assign
id|inb
(paren
id|bmide
op_plus
id|AEC_BM_STAT_PCH
)paren
op_amp
id|AEC_PLLCLK_ATA133
ques
c_cond
id|XFER_UDMA_133
suffix:colon
id|XFER_UDMA_100
suffix:semicolon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP860R
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP860
suffix:colon
id|map
op_or_assign
id|XFER_UDMA_66
suffix:semicolon
)brace
r_return
id|map
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * The initialization callback. Here we determine the IDE chip type&n; * and initialize its drive independent registers.&n; * We return the IRQ assigned to the chip.&n; */
DECL|function|aec62xx_init_chipset
r_static
r_int
r_int
id|__init
id|aec62xx_init_chipset
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u32
id|bmide
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|4
)paren
suffix:semicolon
r_int
r_char
id|t
suffix:semicolon
multiline_comment|/*&n; * Initialize if needed.&n; */
r_switch
c_cond
(paren
id|dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_ARTOP_ATP865R
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP865
suffix:colon
multiline_comment|/* Clear reset and test bits. */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AEC_MISC
comma
op_amp
id|t
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AEC_MISC
comma
id|t
op_amp
op_complement
l_int|0x30
)paren
suffix:semicolon
multiline_comment|/* Enable chip interrupt output. */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AEC_IDE_ENABLE
comma
op_amp
id|t
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AEC_IDE_ENABLE
comma
id|t
op_amp
op_complement
l_int|0x01
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_AEC6280_BURST
multiline_comment|/* Must be greater than 0x80 for burst mode. */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|0x90
)paren
suffix:semicolon
multiline_comment|/* Enable burst mode. */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|AEC_IDE_ENABLE
comma
op_amp
id|t
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|AEC_IDE_ENABLE
comma
id|t
op_or
l_int|0x80
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* switch cable detection pins to input-only. */
id|outb
(paren
id|inb
(paren
id|bmide
op_plus
id|AEC_BM_STAT_SCH
)paren
op_or
id|AEC_CABLEPINS_INPUT
comma
id|bmide
op_plus
id|AEC_BM_STAT_SCH
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Print the boot message.&n; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_REVISION_ID
comma
op_amp
id|t
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AEC_IDE: %s (rev %02x) controller on pci%s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|t
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
r_return
id|dev-&gt;irq
suffix:semicolon
)brace
DECL|function|aec62xx_ata66_check
r_static
r_int
r_int
id|__init
id|aec62xx_ata66_check
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
)paren
(brace
r_int
r_char
id|t
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;pci_dev-&gt;device
op_eq
id|PCI_DEVICE_ID_ARTOP_ATP850UF
)paren
r_return
l_int|0
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|ch-&gt;pci_dev
comma
id|AEC_MISC
comma
op_amp
id|t
)paren
suffix:semicolon
r_return
(paren
(paren
id|t
op_amp
(paren
l_int|1
op_lshift
id|ch-&gt;unit
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|aec62xx_init_channel
r_static
r_void
id|__init
id|aec62xx_init_channel
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
)paren
(brace
r_int
id|i
suffix:semicolon
id|ch-&gt;tuneproc
op_assign
id|aec62xx_tune_drive
suffix:semicolon
id|ch-&gt;speedproc
op_assign
id|aec_set_drive
suffix:semicolon
id|ch-&gt;io_32bit
op_assign
l_int|1
suffix:semicolon
id|ch-&gt;unmask
op_assign
l_int|1
suffix:semicolon
id|ch-&gt;udma_four
op_assign
id|aec62xx_ata66_check
c_func
(paren
id|ch
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ch-&gt;drives
(braket
id|i
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
id|ch-&gt;drives
(braket
id|i
)braket
dot
id|dn
op_assign
id|ch-&gt;unit
op_star
l_int|2
op_plus
id|i
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_if
c_cond
(paren
id|ch-&gt;dma_base
)paren
(brace
id|ch-&gt;highmem
op_assign
l_int|1
suffix:semicolon
id|ch-&gt;modes_map
op_assign
id|aec62xx_modes_map
c_func
(paren
id|ch
)paren
suffix:semicolon
id|ch-&gt;udma_setup
op_assign
id|udma_generic_setup
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; * We allow the BM-DMA driver only work on enabled interfaces.&n; */
DECL|function|aec62xx_init_dma
r_static
r_void
id|__init
id|aec62xx_init_dma
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
r_int
r_char
id|t
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|ch-&gt;pci_dev
comma
id|AEC_IDE_ENABLE
comma
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
op_amp
(paren
l_int|1
op_lshift
(paren
(paren
id|ch-&gt;unit
op_lshift
l_int|1
)paren
op_plus
l_int|2
)paren
)paren
)paren
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
id|PCI_VENDOR_ID_ARTOP
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_ARTOP_ATP850UF
comma
id|init_chipset
suffix:colon
id|aec62xx_init_chipset
comma
id|init_channel
suffix:colon
id|aec62xx_init_channel
comma
id|init_dma
suffix:colon
id|aec62xx_init_dma
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
id|OFF_BOARD
comma
id|flags
suffix:colon
id|ATA_F_SER
op_or
id|ATA_F_IRQ
op_or
id|ATA_F_DMA
)brace
comma
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_ARTOP
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_ARTOP_ATP860
comma
id|init_chipset
suffix:colon
id|aec62xx_init_chipset
comma
id|init_channel
suffix:colon
id|aec62xx_init_channel
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
id|NEVER_BOARD
comma
id|flags
suffix:colon
id|ATA_F_IRQ
op_or
id|ATA_F_DMA
)brace
comma
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_ARTOP
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_ARTOP_ATP860R
comma
id|init_chipset
suffix:colon
id|aec62xx_init_chipset
comma
id|init_channel
suffix:colon
id|aec62xx_init_channel
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
id|OFF_BOARD
comma
id|flags
suffix:colon
id|ATA_F_IRQ
op_or
id|ATA_F_DMA
)brace
comma
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_ARTOP
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_ARTOP_ATP865
comma
id|init_chipset
suffix:colon
id|aec62xx_init_chipset
comma
id|init_channel
suffix:colon
id|aec62xx_init_channel
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
id|NEVER_BOARD
comma
id|flags
suffix:colon
id|ATA_F_IRQ
op_or
id|ATA_F_DMA
)brace
comma
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_ARTOP
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_ARTOP_ATP865R
comma
id|init_chipset
suffix:colon
id|aec62xx_init_chipset
comma
id|init_channel
suffix:colon
id|aec62xx_init_channel
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
id|OFF_BOARD
comma
id|flags
suffix:colon
id|ATA_F_IRQ
op_or
id|ATA_F_DMA
)brace
)brace
suffix:semicolon
DECL|function|init_aec62xx
r_int
id|__init
id|init_aec62xx
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
id|i
op_increment
)paren
id|ata_register_chipset
c_func
(paren
id|chipsets
op_plus
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
