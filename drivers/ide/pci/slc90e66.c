multiline_comment|/*&n; *  linux/drivers/ide/pci/slc90e66.c&t;Version 0.11&t;September 11, 2002&n; *&n; *  Copyright (C) 2000-2002 Andre Hedrick &lt;andre@linux-ide.org&gt;&n; *&n; * This a look-a-like variation of the ICH0 PIIX4 Ultra-66,&n; * but this keeps the ISA-Bridge and slots alive.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|slc90e66_ratemask
r_static
id|u8
id|slc90e66_ratemask
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|u8
id|mode
op_assign
l_int|2
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
id|mode
op_assign
id|min
c_func
(paren
id|mode
comma
(paren
id|u8
)paren
l_int|1
)paren
suffix:semicolon
r_return
id|mode
suffix:semicolon
)brace
DECL|function|slc90e66_dma_2_pio
r_static
id|u8
id|slc90e66_dma_2_pio
(paren
id|u8
id|xfer_rate
)paren
(brace
r_switch
c_cond
(paren
id|xfer_rate
)paren
(brace
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
r_case
id|XFER_MW_DMA_2
suffix:colon
r_case
id|XFER_PIO_4
suffix:colon
r_return
l_int|4
suffix:semicolon
r_case
id|XFER_MW_DMA_1
suffix:colon
r_case
id|XFER_PIO_3
suffix:colon
r_return
l_int|3
suffix:semicolon
r_case
id|XFER_SW_DMA_2
suffix:colon
r_case
id|XFER_PIO_2
suffix:colon
r_return
l_int|2
suffix:semicolon
r_case
id|XFER_MW_DMA_0
suffix:colon
r_case
id|XFER_SW_DMA_1
suffix:colon
r_case
id|XFER_SW_DMA_0
suffix:colon
r_case
id|XFER_PIO_1
suffix:colon
r_case
id|XFER_PIO_0
suffix:colon
r_case
id|XFER_PIO_SLOW
suffix:colon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Based on settings done by AMI BIOS&n; *  (might be useful if drive is not registered in CMOS for any reason).&n; */
DECL|function|slc90e66_tune_drive
r_static
r_void
id|slc90e66_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_int
id|is_slave
op_assign
(paren
op_amp
id|hwif-&gt;drives
(braket
l_int|1
)braket
op_eq
id|drive
)paren
suffix:semicolon
r_int
id|master_port
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x42
suffix:colon
l_int|0x40
suffix:semicolon
r_int
id|slave_port
op_assign
l_int|0x44
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u16
id|master_data
suffix:semicolon
id|u8
id|slave_data
suffix:semicolon
multiline_comment|/* ISP  RTC */
id|u8
id|timings
(braket
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|2
comma
l_int|1
)brace
comma
(brace
l_int|2
comma
l_int|3
)brace
comma
)brace
suffix:semicolon
id|pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
l_int|5
comma
l_int|NULL
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|master_port
comma
op_amp
id|master_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_slave
)paren
(brace
id|master_data
op_assign
id|master_data
op_or
l_int|0x4000
suffix:semicolon
r_if
c_cond
(paren
id|pio
OG
l_int|1
)paren
multiline_comment|/* enable PPE, IE and TIME */
id|master_data
op_assign
id|master_data
op_or
l_int|0x0070
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|slave_port
comma
op_amp
id|slave_data
)paren
suffix:semicolon
id|slave_data
op_assign
id|slave_data
op_amp
(paren
id|hwif-&gt;channel
ques
c_cond
l_int|0x0f
suffix:colon
l_int|0xf0
)paren
suffix:semicolon
id|slave_data
op_assign
id|slave_data
op_or
(paren
(paren
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|0
)braket
op_lshift
l_int|2
)paren
op_or
id|timings
(braket
id|pio
)braket
(braket
l_int|1
)braket
)paren
op_lshift
(paren
id|hwif-&gt;channel
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|master_data
op_assign
id|master_data
op_amp
l_int|0xccf8
suffix:semicolon
r_if
c_cond
(paren
id|pio
OG
l_int|1
)paren
multiline_comment|/* enable PPE, IE and TIME */
id|master_data
op_assign
id|master_data
op_or
l_int|0x0007
suffix:semicolon
id|master_data
op_assign
id|master_data
op_or
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|0
)braket
op_lshift
l_int|12
)paren
op_or
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|master_port
comma
id|master_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_slave
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|slave_port
comma
id|slave_data
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|slc90e66_tune_chipset
r_static
r_int
id|slc90e66_tune_chipset
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|xferspeed
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|u8
id|maslave
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x42
suffix:colon
l_int|0x40
suffix:semicolon
id|u8
id|speed
op_assign
id|ide_rate_filter
c_func
(paren
id|slc90e66_ratemask
c_func
(paren
id|drive
)paren
comma
id|xferspeed
)paren
suffix:semicolon
r_int
id|sitre
op_assign
l_int|0
comma
id|a_speed
op_assign
l_int|7
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
suffix:semicolon
r_int
id|u_speed
op_assign
l_int|0
comma
id|u_flag
op_assign
l_int|1
op_lshift
id|drive-&gt;dn
suffix:semicolon
id|u16
id|reg4042
comma
id|reg44
comma
id|reg48
comma
id|reg4a
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|maslave
comma
op_amp
id|reg4042
)paren
suffix:semicolon
id|sitre
op_assign
(paren
id|reg4042
op_amp
l_int|0x4000
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x44
comma
op_amp
id|reg44
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x48
comma
op_amp
id|reg48
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
op_amp
id|reg4a
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|speed
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_case
id|XFER_UDMA_4
suffix:colon
id|u_speed
op_assign
l_int|4
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_3
suffix:colon
id|u_speed
op_assign
l_int|3
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_2
suffix:colon
id|u_speed
op_assign
l_int|2
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_1
suffix:colon
id|u_speed
op_assign
l_int|1
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_0
suffix:colon
id|u_speed
op_assign
l_int|0
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
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
id|XFER_SW_DMA_2
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
id|XFER_PIO_0
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|speed
op_ge
id|XFER_UDMA_0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg48
op_amp
id|u_flag
)paren
)paren
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x48
comma
id|reg48
op_or
id|u_flag
)paren
suffix:semicolon
multiline_comment|/* FIXME: (reg4a &amp; a_speed) ? */
r_if
c_cond
(paren
(paren
id|reg4a
op_amp
id|u_speed
)paren
op_ne
id|u_speed
)paren
(brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
id|reg4a
op_amp
op_complement
id|a_speed
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
op_amp
id|reg4a
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
id|reg4a
op_or
id|u_speed
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|reg48
op_amp
id|u_flag
)paren
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x48
comma
id|reg48
op_amp
op_complement
id|u_flag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg4a
op_amp
id|a_speed
)paren
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
id|reg4a
op_amp
op_complement
id|a_speed
)paren
suffix:semicolon
)brace
id|slc90e66_tune_drive
c_func
(paren
id|drive
comma
id|slc90e66_dma_2_pio
c_func
(paren
id|speed
)paren
)paren
suffix:semicolon
r_return
(paren
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|speed
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
DECL|function|slc90e66_config_drive_for_dma
r_static
r_int
id|slc90e66_config_drive_for_dma
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|u8
id|speed
op_assign
id|ide_dma_speed
c_func
(paren
id|drive
comma
id|slc90e66_ratemask
c_func
(paren
id|drive
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|speed
)paren
)paren
(brace
id|u8
id|tspeed
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
l_int|255
comma
l_int|5
comma
l_int|NULL
)paren
suffix:semicolon
id|speed
op_assign
id|slc90e66_dma_2_pio
c_func
(paren
id|XFER_PIO_0
op_plus
id|tspeed
)paren
suffix:semicolon
)brace
(paren
r_void
)paren
id|slc90e66_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
r_return
id|ide_dma_enable
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|slc90e66_config_drive_xfer_rate
r_static
r_int
id|slc90e66_config_drive_xfer_rate
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
id|drive-&gt;init_speed
op_assign
l_int|0
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
id|drive-&gt;autodma
)paren
(brace
r_if
c_cond
(paren
id|ide_use_dma
c_func
(paren
id|drive
)paren
)paren
(brace
r_if
c_cond
(paren
id|slc90e66_config_drive_for_dma
c_func
(paren
id|drive
)paren
)paren
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_on
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
r_goto
id|fast_ata_pio
suffix:semicolon
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
id|hwif
op_member_access_from_pointer
id|tuneproc
c_func
(paren
id|drive
comma
l_int|5
)paren
suffix:semicolon
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_off_quietly
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
multiline_comment|/* IORDY not supported */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
DECL|function|init_hwif_slc90e66
r_static
r_void
id|__init
id|init_hwif_slc90e66
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|u8
id|reg47
op_assign
l_int|0
suffix:semicolon
id|u8
id|mask
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x01
suffix:colon
l_int|0x02
suffix:semicolon
multiline_comment|/* bit0:Primary */
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;irq
)paren
id|hwif-&gt;irq
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|15
suffix:colon
l_int|14
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|slc90e66_tune_chipset
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
op_amp
id|slc90e66_tune_drive
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|hwif-&gt;pci_dev
comma
l_int|0x47
comma
op_amp
id|reg47
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;dma_base
)paren
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
r_return
suffix:semicolon
)brace
id|hwif-&gt;atapi_dma
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;ultra_mask
op_assign
l_int|0x1f
suffix:semicolon
id|hwif-&gt;mwdma_mask
op_assign
l_int|0x07
suffix:semicolon
id|hwif-&gt;swdma_mask
op_assign
l_int|0x07
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA 
r_if
c_cond
(paren
op_logical_neg
(paren
id|hwif-&gt;udma_four
)paren
)paren
multiline_comment|/* bit[0(1)]: 0:80, 1:40 */
id|hwif-&gt;udma_four
op_assign
(paren
id|reg47
op_amp
id|mask
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|slc90e66_config_drive_xfer_rate
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|noautodma
)paren
id|hwif-&gt;autodma
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autodma
op_assign
id|hwif-&gt;autodma
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autodma
op_assign
id|hwif-&gt;autodma
suffix:semicolon
macro_line|#endif /* !CONFIG_BLK_DEV_IDEDMA */
)brace
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|slc90e66_chipset
id|__devinitdata
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SLC90E66&quot;
comma
dot
id|init_hwif
op_assign
id|init_hwif_slc90e66
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x41
comma
l_int|0x80
comma
l_int|0x80
)brace
comma
(brace
l_int|0x43
comma
l_int|0x80
comma
l_int|0x80
)brace
)brace
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
)brace
suffix:semicolon
DECL|function|slc90e66_init_one
r_static
r_int
id|__devinit
id|slc90e66_init_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
op_amp
id|slc90e66_chipset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|slc90e66_pci_tbl
r_static
r_struct
id|pci_device_id
id|slc90e66_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_EFAR
comma
id|PCI_DEVICE_ID_EFAR_SLC90E66_1
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|slc90e66_pci_tbl
)paren
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|pci_driver
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SLC90e66_IDE&quot;
comma
dot
id|id_table
op_assign
id|slc90e66_pci_tbl
comma
dot
id|probe
op_assign
id|slc90e66_init_one
comma
)brace
suffix:semicolon
DECL|function|slc90e66_ide_init
r_static
r_int
id|slc90e66_ide_init
c_func
(paren
r_void
)paren
(brace
r_return
id|ide_pci_register_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|slc90e66_ide_init
id|module_init
c_func
(paren
id|slc90e66_ide_init
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andre Hedrick&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for SLC90E66 IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
