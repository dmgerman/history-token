multiline_comment|/*&n; *  linux/drivers/ide/pci/atiixp.c&t;Version 0.01-bart2&t;Feb. 26, 2004&n; *&n; *  Copyright (C) 2003 ATI Inc. &lt;hyu@ati.com&gt;&n; *  Copyright (C) 2004 Bartlomiej Zolnierkiewicz&n; *&n; */
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
DECL|macro|ATIIXP_IDE_PIO_TIMING
mdefine_line|#define ATIIXP_IDE_PIO_TIMING&t;&t;0x40
DECL|macro|ATIIXP_IDE_MDMA_TIMING
mdefine_line|#define ATIIXP_IDE_MDMA_TIMING&t;&t;0x44
DECL|macro|ATIIXP_IDE_PIO_CONTROL
mdefine_line|#define ATIIXP_IDE_PIO_CONTROL&t;&t;0x48
DECL|macro|ATIIXP_IDE_PIO_MODE
mdefine_line|#define ATIIXP_IDE_PIO_MODE&t;&t;0x4a
DECL|macro|ATIIXP_IDE_UDMA_CONTROL
mdefine_line|#define ATIIXP_IDE_UDMA_CONTROL&t;&t;0x54
DECL|macro|ATIIXP_IDE_UDMA_MODE
mdefine_line|#define ATIIXP_IDE_UDMA_MODE&t;&t;0x56
r_typedef
r_struct
(brace
DECL|member|command_width
id|u8
id|command_width
suffix:semicolon
DECL|member|recover_width
id|u8
id|recover_width
suffix:semicolon
DECL|typedef|atiixp_ide_timing
)brace
id|atiixp_ide_timing
suffix:semicolon
DECL|variable|pio_timing
r_static
id|atiixp_ide_timing
id|pio_timing
(braket
)braket
op_assign
(brace
(brace
l_int|0x05
comma
l_int|0x0d
)brace
comma
(brace
l_int|0x04
comma
l_int|0x07
)brace
comma
(brace
l_int|0x03
comma
l_int|0x04
)brace
comma
(brace
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x02
comma
l_int|0x00
)brace
comma
)brace
suffix:semicolon
DECL|variable|mdma_timing
r_static
id|atiixp_ide_timing
id|mdma_timing
(braket
)braket
op_assign
(brace
(brace
l_int|0x07
comma
l_int|0x07
)brace
comma
(brace
l_int|0x02
comma
l_int|0x01
)brace
comma
(brace
l_int|0x02
comma
l_int|0x00
)brace
comma
)brace
suffix:semicolon
DECL|variable|save_mdma_mode
r_static
r_int
id|save_mdma_mode
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/**&n; *&t;atiixp_ratemask&t;&t;-&t;compute rate mask for ATIIXP IDE&n; *&t;@drive: IDE drive to compute for&n; *&n; *&t;Returns the available modes for the ATIIXP IDE controller.&n; */
DECL|function|atiixp_ratemask
r_static
id|u8
id|atiixp_ratemask
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|u8
id|mode
op_assign
l_int|3
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
multiline_comment|/**&n; *&t;atiixp_dma_2_pio&t;&t;-&t;return the PIO mode matching DMA&n; *&t;@xfer_rate: transfer speed&n; *&n; *&t;Returns the nearest equivalent PIO timing for the PIO or DMA&n; *&t;mode requested by the controller.&n; */
DECL|function|atiixp_dma_2_pio
r_static
id|u8
id|atiixp_dma_2_pio
c_func
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
id|XFER_UDMA_6
suffix:colon
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
DECL|function|atiixp_ide_dma_host_on
r_static
r_int
id|atiixp_ide_dma_host_on
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|drive-&gt;hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u16
id|tmp16
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
id|ATIIXP_IDE_UDMA_CONTROL
comma
op_amp
id|tmp16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|save_mdma_mode
(braket
id|drive-&gt;dn
)braket
)paren
id|tmp16
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|drive-&gt;dn
)paren
suffix:semicolon
r_else
id|tmp16
op_or_assign
(paren
l_int|1
op_lshift
id|drive-&gt;dn
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|ATIIXP_IDE_UDMA_CONTROL
comma
id|tmp16
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
r_return
id|__ide_dma_host_on
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|atiixp_ide_dma_host_off
r_static
r_int
id|atiixp_ide_dma_host_off
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|drive-&gt;hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u16
id|tmp16
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
id|ATIIXP_IDE_UDMA_CONTROL
comma
op_amp
id|tmp16
)paren
suffix:semicolon
id|tmp16
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|drive-&gt;dn
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|ATIIXP_IDE_UDMA_CONTROL
comma
id|tmp16
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
r_return
id|__ide_dma_host_off
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;atiixp_tune_drive&t;&t;-&t;tune a drive attached to a ATIIXP&n; *&t;@drive: drive to tune&n; *&t;@pio: desired PIO mode&n; *&n; *&t;Set the interface PIO mode.&n; */
DECL|function|atiixp_tuneproc
r_static
r_void
id|atiixp_tuneproc
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|drive-&gt;hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|timing_shift
op_assign
(paren
id|drive-&gt;dn
op_amp
l_int|2
)paren
ques
c_cond
l_int|16
suffix:colon
l_int|0
op_plus
(paren
id|drive-&gt;dn
op_amp
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|8
suffix:semicolon
id|u32
id|pio_timing_data
suffix:semicolon
id|u16
id|pio_mode_data
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
id|ATIIXP_IDE_PIO_MODE
comma
op_amp
id|pio_mode_data
)paren
suffix:semicolon
id|pio_mode_data
op_and_assign
op_complement
(paren
l_int|0x07
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|pio_mode_data
op_or_assign
(paren
id|pio
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|ATIIXP_IDE_PIO_MODE
comma
id|pio_mode_data
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|ATIIXP_IDE_PIO_TIMING
comma
op_amp
id|pio_timing_data
)paren
suffix:semicolon
id|pio_timing_data
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
id|timing_shift
)paren
suffix:semicolon
id|pio_timing_data
op_or_assign
(paren
id|pio_timing
(braket
id|pio
)braket
dot
id|recover_width
op_lshift
id|timing_shift
)paren
op_or
(paren
id|pio_timing
(braket
id|pio
)braket
dot
id|command_width
op_lshift
(paren
id|timing_shift
op_plus
l_int|4
)paren
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|ATIIXP_IDE_PIO_TIMING
comma
id|pio_timing_data
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
multiline_comment|/**&n; *&t;atiixp_tune_chipset&t;-&t;tune a ATIIXP interface&n; *&t;@drive: IDE drive to tune&n; *&t;@xferspeed: speed to configure&n; *&n; *&t;Set a ATIIXP interface channel to the desired speeds. This involves&n; *&t;requires the right timing data into the ATIIXP configuration space&n; *&t;then setting the drive parameters appropriately&n; */
DECL|function|atiixp_speedproc
r_static
r_int
id|atiixp_speedproc
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|xferspeed
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|drive-&gt;hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|timing_shift
op_assign
(paren
id|drive-&gt;dn
op_amp
l_int|2
)paren
ques
c_cond
l_int|16
suffix:colon
l_int|0
op_plus
(paren
id|drive-&gt;dn
op_amp
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|8
suffix:semicolon
id|u32
id|tmp32
suffix:semicolon
id|u16
id|tmp16
suffix:semicolon
id|u8
id|speed
comma
id|pio
suffix:semicolon
id|speed
op_assign
id|ide_rate_filter
c_func
(paren
id|atiixp_ratemask
c_func
(paren
id|drive
)paren
comma
id|xferspeed
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
id|save_mdma_mode
(braket
id|drive-&gt;dn
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_ge
id|XFER_UDMA_0
)paren
(brace
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|ATIIXP_IDE_UDMA_MODE
comma
op_amp
id|tmp16
)paren
suffix:semicolon
id|tmp16
op_and_assign
op_complement
(paren
l_int|0x07
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|tmp16
op_or_assign
(paren
(paren
id|speed
op_amp
l_int|0x07
)paren
op_lshift
(paren
id|drive-&gt;dn
op_star
l_int|4
)paren
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|ATIIXP_IDE_UDMA_MODE
comma
id|tmp16
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|speed
op_ge
id|XFER_MW_DMA_0
)paren
op_logical_and
(paren
id|speed
op_le
id|XFER_MW_DMA_2
)paren
)paren
(brace
id|save_mdma_mode
(braket
id|drive-&gt;dn
)braket
op_assign
id|speed
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|ATIIXP_IDE_MDMA_TIMING
comma
op_amp
id|tmp32
)paren
suffix:semicolon
id|tmp32
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
id|timing_shift
)paren
suffix:semicolon
id|tmp32
op_or_assign
(paren
id|mdma_timing
(braket
id|speed
op_amp
l_int|0x03
)braket
dot
id|recover_width
op_lshift
id|timing_shift
)paren
op_or
(paren
id|mdma_timing
(braket
id|speed
op_amp
l_int|0x03
)braket
dot
id|command_width
op_lshift
(paren
id|timing_shift
op_plus
l_int|4
)paren
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|ATIIXP_IDE_MDMA_TIMING
comma
id|tmp32
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_ge
id|XFER_SW_DMA_0
)paren
id|pio
op_assign
id|atiixp_dma_2_pio
c_func
(paren
id|speed
)paren
suffix:semicolon
r_else
id|pio
op_assign
id|speed
op_minus
id|XFER_PIO_0
suffix:semicolon
id|atiixp_tuneproc
c_func
(paren
id|drive
comma
id|pio
)paren
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
multiline_comment|/**&n; *&t;atiixp_config_drive_for_dma&t;-&t;configure drive for DMA&n; *&t;@drive: IDE drive to configure&n; *&n; *&t;Set up a ATIIXP interface channel for the best available speed.&n; *&t;We prefer UDMA if it is available and then MWDMA. If DMA is&n; *&t;not available we switch to PIO and return 0.&n; */
DECL|function|atiixp_config_drive_for_dma
r_static
r_int
id|atiixp_config_drive_for_dma
c_func
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
id|atiixp_ratemask
c_func
(paren
id|drive
)paren
)paren
suffix:semicolon
multiline_comment|/* If no DMA speed was available then disable DMA and use PIO. */
r_if
c_cond
(paren
op_logical_neg
id|speed
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
id|atiixp_dma_2_pio
c_func
(paren
id|XFER_PIO_0
op_plus
id|tspeed
)paren
op_plus
id|XFER_PIO_0
suffix:semicolon
)brace
(paren
r_void
)paren
id|atiixp_speedproc
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
multiline_comment|/**&n; *&t;atiixp_dma_check&t;-&t;set up an IDE device&n; *&t;@drive: IDE drive to configure&n; *&n; *&t;Set up the ATIIXP interface for the best available speed on this&n; *&t;interface, preferring DMA to PIO.&n; */
DECL|function|atiixp_dma_check
r_static
r_int
id|atiixp_dma_check
c_func
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
id|u8
id|tspeed
comma
id|speed
suffix:semicolon
id|drive-&gt;init_speed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id-&gt;capability
op_amp
l_int|1
)paren
op_logical_and
id|drive-&gt;autodma
)paren
(brace
multiline_comment|/* Consult the list of known &quot;bad&quot; drives */
r_if
c_cond
(paren
id|__ide_dma_bad_drive
c_func
(paren
id|drive
)paren
)paren
r_goto
id|fast_ata_pio
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
id|hwif-&gt;ultra_mask
)paren
(brace
multiline_comment|/* Force if Capable UltraDMA */
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
id|atiixp_config_drive_for_dma
c_func
(paren
id|drive
)paren
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
id|hwif-&gt;mwdma_mask
)paren
op_logical_or
(paren
id|id-&gt;dma_1word
op_amp
id|hwif-&gt;swdma_mask
)paren
)paren
(brace
multiline_comment|/* Force if Capable regular DMA modes */
r_if
c_cond
(paren
op_logical_neg
id|atiixp_config_drive_for_dma
c_func
(paren
id|drive
)paren
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
id|__ide_dma_good_drive
c_func
(paren
id|drive
)paren
op_logical_and
(paren
id|id-&gt;eide_dma_time
OL
l_int|150
)paren
)paren
(brace
multiline_comment|/* Consult the list of known &quot;good&quot; drives */
r_if
c_cond
(paren
op_logical_neg
id|atiixp_config_drive_for_dma
c_func
(paren
id|drive
)paren
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
id|no_dma_set
suffix:colon
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
id|atiixp_dma_2_pio
c_func
(paren
id|XFER_PIO_0
op_plus
id|tspeed
)paren
op_plus
id|XFER_PIO_0
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|speedproc
c_func
(paren
id|drive
comma
id|speed
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
multiline_comment|/**&n; *&t;init_hwif_atiixp&t;&t;-&t;fill in the hwif for the ATIIXP&n; *&t;@hwif: IDE interface&n; *&n; *&t;Set up the ide_hwif_t for the ATIIXP interface according to the&n; *&t;capabilities of the hardware.&n; */
DECL|function|init_hwif_atiixp
r_static
r_void
id|__devinit
id|init_hwif_atiixp
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
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
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
op_amp
id|atiixp_tuneproc
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|atiixp_speedproc
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
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;dma_base
)paren
r_return
suffix:semicolon
id|hwif-&gt;atapi_dma
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;ultra_mask
op_assign
l_int|0x3f
suffix:semicolon
id|hwif-&gt;mwdma_mask
op_assign
l_int|0x06
suffix:semicolon
id|hwif-&gt;swdma_mask
op_assign
l_int|0x04
suffix:semicolon
multiline_comment|/* FIXME: proper cable detection needed */
id|hwif-&gt;udma_four
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;ide_dma_host_on
op_assign
op_amp
id|atiixp_ide_dma_host_on
suffix:semicolon
id|hwif-&gt;ide_dma_host_off
op_assign
op_amp
id|atiixp_ide_dma_host_off
suffix:semicolon
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|atiixp_dma_check
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
l_int|1
)braket
dot
id|autodma
op_assign
id|hwif-&gt;autodma
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
)brace
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|atiixp_pci_info
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
dot
id|name
op_assign
l_string|&quot;ATIIXP&quot;
comma
dot
id|init_hwif
op_assign
id|init_hwif_atiixp
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
l_int|0x48
comma
l_int|0x01
comma
l_int|0x00
)brace
comma
(brace
l_int|0x48
comma
l_int|0x08
comma
l_int|0x00
)brace
)brace
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
)brace
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;atiixp_init_one&t;-&t;called when a ATIIXP is found&n; *&t;@dev: the atiixp device&n; *&t;@id: the matching pci id&n; *&n; *&t;Called when the PCI registration layer (or the IDE initialization)&n; *&t;finds a device matching our IDE device tables.&n; */
DECL|function|atiixp_init_one
r_static
r_int
id|__devinit
id|atiixp_init_one
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
id|atiixp_pci_info
(braket
id|id-&gt;driver_data
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|atiixp_pci_tbl
r_static
r_struct
id|pci_device_id
id|atiixp_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_ATI
comma
id|PCI_DEVICE_ID_ATI_IXP_IDE
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
id|atiixp_pci_tbl
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
l_string|&quot;ATIIXP_IDE&quot;
comma
dot
id|id_table
op_assign
id|atiixp_pci_tbl
comma
dot
id|probe
op_assign
id|atiixp_init_one
comma
)brace
suffix:semicolon
DECL|function|atiixp_ide_init
r_static
r_int
id|atiixp_ide_init
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
DECL|variable|atiixp_ide_init
id|module_init
c_func
(paren
id|atiixp_ide_init
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;HUI YU&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for ATI IXP IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
