multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; * linux/drivers/ide/hpt34x.c&t;&t;Version 0.31&t;June. 9, 2000&n; *&n; * Copyright (C) 1998-2000&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; * May be copied or modified under the terms of the GNU General Public License&n; *&n; *&n; * 00:12.0 Unknown mass storage controller:&n; * Triones Technologies, Inc.&n; * Unknown device 0003 (rev 01)&n; *&n; * hde: UDMA 2 (0x0000 0x0002) (0x0000 0x0010)&n; * hdf: UDMA 2 (0x0002 0x0012) (0x0010 0x0030)&n; * hde: DMA 2  (0x0000 0x0002) (0x0000 0x0010)&n; * hdf: DMA 2  (0x0002 0x0012) (0x0010 0x0030)&n; * hdg: DMA 1  (0x0012 0x0052) (0x0030 0x0070)&n; * hdh: DMA 1  (0x0052 0x0252) (0x0070 0x00f0)&n; *&n; * ide-pci.c reference&n; *&n; * Since there are two cards that report almost identically,&n; * the only discernable difference is the values reported in pcicmd.&n; * Booting-BIOS card or HPT363 :: pcicmd == 0x07&n; * Non-bootable card or HPT343 :: pcicmd == 0x05&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;ata-timing.h&quot;
macro_line|#include &quot;pcihost.h&quot;
macro_line|#ifndef SPLIT_BYTE
DECL|macro|SPLIT_BYTE
macro_line|# define SPLIT_BYTE(B,H,L)&t;((H)=(B&gt;&gt;4), (L)=(B-((B&gt;&gt;4)&lt;&lt;4)))
macro_line|#endif
DECL|macro|HPT343_DEBUG_DRIVE_INFO
mdefine_line|#define HPT343_DEBUG_DRIVE_INFO&t;&t;0
DECL|function|hpt34x_clear_chipset
r_static
r_void
id|hpt34x_clear_chipset
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_int
r_int
id|reg1
op_assign
l_int|0
comma
id|tmp1
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|reg2
op_assign
l_int|0
comma
id|tmp2
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
l_int|0x44
comma
op_amp
id|reg1
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
l_int|0x48
comma
op_amp
id|reg2
)paren
suffix:semicolon
id|tmp1
op_assign
(paren
(paren
l_int|0x00
op_lshift
(paren
l_int|3
op_star
id|drive-&gt;dn
)paren
)paren
op_or
(paren
id|reg1
op_amp
op_complement
(paren
l_int|7
op_lshift
(paren
l_int|3
op_star
id|drive-&gt;dn
)paren
)paren
)paren
)paren
suffix:semicolon
id|tmp2
op_assign
(paren
id|reg2
op_amp
op_complement
(paren
l_int|0x11
op_lshift
id|drive-&gt;dn
)paren
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
l_int|0x44
comma
id|tmp1
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
l_int|0x48
comma
id|tmp2
)paren
suffix:semicolon
)brace
DECL|function|hpt34x_tune_chipset
r_static
r_int
id|hpt34x_tune_chipset
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
id|byte
id|hi_speed
comma
id|lo_speed
suffix:semicolon
r_int
r_int
id|reg1
op_assign
l_int|0
comma
id|tmp1
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|reg2
op_assign
l_int|0
comma
id|tmp2
op_assign
l_int|0
suffix:semicolon
id|SPLIT_BYTE
c_func
(paren
id|speed
comma
id|hi_speed
comma
id|lo_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi_speed
op_amp
l_int|7
)paren
(brace
id|hi_speed
op_assign
(paren
id|hi_speed
op_amp
l_int|4
)paren
ques
c_cond
l_int|0x01
suffix:colon
l_int|0x10
suffix:semicolon
)brace
r_else
(brace
id|lo_speed
op_lshift_assign
l_int|5
suffix:semicolon
id|lo_speed
op_rshift_assign
l_int|5
suffix:semicolon
)brace
id|pci_read_config_dword
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
l_int|0x44
comma
op_amp
id|reg1
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
l_int|0x48
comma
op_amp
id|reg2
)paren
suffix:semicolon
id|tmp1
op_assign
(paren
(paren
id|lo_speed
op_lshift
(paren
l_int|3
op_star
id|drive-&gt;dn
)paren
)paren
op_or
(paren
id|reg1
op_amp
op_complement
(paren
l_int|7
op_lshift
(paren
l_int|3
op_star
id|drive-&gt;dn
)paren
)paren
)paren
)paren
suffix:semicolon
id|tmp2
op_assign
(paren
(paren
id|hi_speed
op_lshift
id|drive-&gt;dn
)paren
op_or
id|reg2
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
l_int|0x44
comma
id|tmp1
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|drive-&gt;channel-&gt;pci_dev
comma
l_int|0x48
comma
id|tmp2
)paren
suffix:semicolon
macro_line|#if HPT343_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;%s: %02x drive%d (0x%04x 0x%04x) (0x%04x 0x%04x)&quot;
"&bslash;"
l_string|&quot; (0x%02x 0x%02x) 0x%04x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|speed
comma
id|drive-&gt;dn
comma
id|reg1
comma
id|tmp1
comma
id|reg2
comma
id|tmp2
comma
id|hi_speed
comma
id|lo_speed
comma
id|err
)paren
suffix:semicolon
macro_line|#endif
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
DECL|function|config_chipset_for_pio
r_static
r_void
id|config_chipset_for_pio
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_int
r_int
id|eide_pio_timing
(braket
l_int|6
)braket
op_assign
(brace
l_int|960
comma
l_int|480
comma
l_int|240
comma
l_int|180
comma
l_int|120
comma
l_int|90
)brace
suffix:semicolon
r_int
r_int
id|xfer_pio
op_assign
id|drive-&gt;id-&gt;eide_pio_modes
suffix:semicolon
id|byte
id|timing
comma
id|speed
comma
id|pio
suffix:semicolon
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
op_minus
id|XFER_PIO_0
suffix:semicolon
r_if
c_cond
(paren
id|xfer_pio
OG
l_int|4
)paren
id|xfer_pio
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;id-&gt;eide_pio_iordy
OG
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|xfer_pio
op_assign
l_int|5
suffix:semicolon
id|xfer_pio
OG
l_int|0
op_logical_and
id|drive-&gt;id-&gt;eide_pio_iordy
OG
id|eide_pio_timing
(braket
id|xfer_pio
)braket
suffix:semicolon
id|xfer_pio
op_decrement
)paren
suffix:semicolon
)brace
r_else
(brace
id|xfer_pio
op_assign
(paren
id|drive-&gt;id-&gt;eide_pio_modes
op_amp
l_int|4
)paren
ques
c_cond
l_int|0x05
suffix:colon
(paren
id|drive-&gt;id-&gt;eide_pio_modes
op_amp
l_int|2
)paren
ques
c_cond
l_int|0x04
suffix:colon
(paren
id|drive-&gt;id-&gt;eide_pio_modes
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x03
suffix:colon
id|xfer_pio
suffix:semicolon
)brace
id|timing
op_assign
(paren
id|xfer_pio
op_ge
id|pio
)paren
ques
c_cond
id|xfer_pio
suffix:colon
id|pio
suffix:semicolon
r_switch
c_cond
(paren
id|timing
)paren
(brace
r_case
l_int|4
suffix:colon
id|speed
op_assign
id|XFER_PIO_4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|speed
op_assign
id|XFER_PIO_3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|speed
op_assign
id|XFER_PIO_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|speed
op_assign
id|XFER_PIO_1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|speed
op_assign
(paren
op_logical_neg
id|drive-&gt;id-&gt;tPIO
)paren
ques
c_cond
id|XFER_PIO_0
suffix:colon
id|XFER_PIO_SLOW
suffix:semicolon
r_break
suffix:semicolon
)brace
(paren
r_void
)paren
id|hpt34x_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
)brace
DECL|function|hpt34x_tune_drive
r_static
r_void
id|hpt34x_tune_drive
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
id|byte
id|speed
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
id|speed
op_assign
id|XFER_PIO_4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|speed
op_assign
id|XFER_PIO_3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|speed
op_assign
id|XFER_PIO_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|speed
op_assign
id|XFER_PIO_1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|speed
op_assign
id|XFER_PIO_0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hpt34x_clear_chipset
c_func
(paren
id|drive
)paren
suffix:semicolon
(paren
r_void
)paren
id|hpt34x_tune_chipset
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
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|udma
)paren
id|map
op_assign
id|XFER_UDMA
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
id|hpt34x_clear_chipset
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
op_logical_neg
id|hpt34x_tune_chipset
c_func
(paren
id|drive
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|hpt34x_udma_setup
r_static
r_int
id|hpt34x_udma_setup
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
r_if
c_cond
(paren
id|id
op_logical_and
(paren
id|id-&gt;capability
op_amp
l_int|1
)paren
op_logical_and
id|drive-&gt;channel-&gt;autodma
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
id|id-&gt;field_valid
op_amp
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0007
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
l_int|1
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
l_int|0
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
l_int|0
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
id|config_chipset_for_pio
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_HPT34X_AUTODMA
r_if
c_cond
(paren
id|on
)paren
id|on
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
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
DECL|function|hpt34x_udma_stop
r_static
r_int
id|hpt34x_udma_stop
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
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_int
r_int
id|dma_base
op_assign
id|ch-&gt;dma_base
suffix:semicolon
id|u8
id|dma_stat
suffix:semicolon
id|drive-&gt;waiting_for_dma
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|dma_base
)paren
op_amp
op_complement
l_int|1
comma
id|dma_base
)paren
suffix:semicolon
multiline_comment|/* stop DMA */
id|dma_stat
op_assign
id|inb
c_func
(paren
id|dma_base
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* get DMA status */
id|outb
c_func
(paren
id|dma_stat
op_or
l_int|6
comma
id|dma_base
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* clear the INTR &amp; ERROR bits */
id|udma_destroy_table
c_func
(paren
id|ch
)paren
suffix:semicolon
multiline_comment|/* purge DMA mappings */
r_return
(paren
id|dma_stat
op_amp
l_int|7
)paren
op_ne
l_int|4
suffix:semicolon
multiline_comment|/* verify good DMA status */
)brace
DECL|function|hpt34x_udma_init
r_static
r_int
id|hpt34x_udma_init
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
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_int
r_int
id|dma_base
op_assign
id|ch-&gt;dma_base
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
id|u8
id|cmd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|count
op_assign
id|udma_new_table
c_func
(paren
id|drive
comma
id|rq
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* try PIO instead of DMA */
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|rq
)paren
op_eq
id|READ
)paren
id|cmd
op_assign
l_int|0x09
suffix:semicolon
r_else
id|cmd
op_assign
l_int|0x01
suffix:semicolon
id|outl
c_func
(paren
id|ch-&gt;dmatable_dma
comma
id|dma_base
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* PRD table */
id|outb
c_func
(paren
id|cmd
comma
id|dma_base
)paren
suffix:semicolon
multiline_comment|/* specify r/w */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|dma_base
op_plus
l_int|2
)paren
op_or
l_int|6
comma
id|dma_base
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* clear INTR &amp; ERROR flags */
id|drive-&gt;waiting_for_dma
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
r_return
l_int|0
suffix:semicolon
id|ide_set_handler
c_func
(paren
id|drive
comma
id|ide_dma_intr
comma
id|WAIT_CMD
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* issue cmd to drive */
id|OUT_BYTE
c_func
(paren
(paren
id|cmd
op_eq
l_int|0x09
)paren
ques
c_cond
id|WIN_READDMA
suffix:colon
id|WIN_WRITEDMA
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * If the BIOS does not set the IO base addaress to XX00, 343 will fail.&n; */
DECL|macro|HPT34X_PCI_INIT_REG
mdefine_line|#define&t;HPT34X_PCI_INIT_REG&t;&t;0x80
DECL|function|pci_init_hpt34x
r_static
r_int
r_int
id|__init
id|pci_init_hpt34x
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
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|hpt34xIoBase
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
r_int
id|cmd
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|HPT34X_PCI_INIT_REG
comma
l_int|0x00
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
id|PCI_COMMAND_MEMORY
)paren
(brace
r_if
c_cond
(paren
id|pci_resource_start
c_func
(paren
id|dev
comma
id|PCI_ROM_RESOURCE
)paren
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_ROM_ADDRESS
comma
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
op_or
id|PCI_ROM_ADDRESS_ENABLE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HPT345: ROM enabled at 0x%08lx&bslash;n&quot;
comma
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
)paren
suffix:semicolon
)brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|0xF0
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
id|PCI_LATENCY_TIMER
comma
l_int|0x20
)paren
suffix:semicolon
)brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
op_amp
op_complement
id|PCI_COMMAND_IO
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_assign
(paren
id|hpt34xIoBase
op_plus
l_int|0x20
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
op_assign
(paren
id|hpt34xIoBase
op_plus
l_int|0x34
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|2
)braket
dot
id|start
op_assign
(paren
id|hpt34xIoBase
op_plus
l_int|0x28
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|3
)braket
dot
id|start
op_assign
(paren
id|hpt34xIoBase
op_plus
l_int|0x3c
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
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_or_assign
id|PCI_BASE_ADDRESS_SPACE_IO
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Since 20-23 can be assigned and are R/W, we correct them.&n;&t; */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
comma
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_1
comma
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_2
comma
id|dev-&gt;resource
(braket
l_int|2
)braket
dot
id|start
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_3
comma
id|dev-&gt;resource
(braket
l_int|3
)braket
dot
id|start
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
r_return
id|dev-&gt;irq
suffix:semicolon
)brace
DECL|function|ide_init_hpt34x
r_static
r_void
id|__init
id|ide_init_hpt34x
c_func
(paren
r_struct
id|ata_channel
op_star
id|hwif
)paren
(brace
id|hwif-&gt;tuneproc
op_assign
id|hpt34x_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
id|hpt34x_tune_chipset
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_if
c_cond
(paren
id|hwif-&gt;dma_base
)paren
(brace
r_int
r_int
id|pcicmd
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|hwif-&gt;pci_dev
comma
id|PCI_COMMAND
comma
op_amp
id|pcicmd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|noautodma
)paren
id|hwif-&gt;autodma
op_assign
(paren
id|pcicmd
op_amp
id|PCI_COMMAND_MEMORY
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_else
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;udma_stop
op_assign
id|hpt34x_udma_stop
suffix:semicolon
id|hwif-&gt;udma_init
op_assign
id|hpt34x_udma_init
suffix:semicolon
id|hwif-&gt;udma_setup
op_assign
id|hpt34x_udma_setup
suffix:semicolon
id|hwif-&gt;highmem
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
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
)brace
macro_line|#else
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
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
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
id|PCI_VENDOR_ID_TTI
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_TTI_HPT343
comma
id|init_chipset
suffix:colon
id|pci_init_hpt34x
comma
id|init_channel
suffix:colon
id|ide_init_hpt34x
comma
id|bootable
suffix:colon
id|NEVER_BOARD
comma
id|extra
suffix:colon
l_int|16
comma
id|flags
suffix:colon
id|ATA_F_NOADMA
op_or
id|ATA_F_DMA
)brace
suffix:semicolon
DECL|function|init_hpt34x
r_int
id|__init
id|init_hpt34x
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
