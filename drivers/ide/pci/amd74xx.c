multiline_comment|/*&n; * linux/drivers/ide/amd74xx.c&t;&t;Version 0.05&t;June 9, 2000&n; *&n; * Copyright (C) 1999-2000&t;&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; * May be copied or modified under the terms of the GNU General Public License&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;ide_modes.h&quot;
macro_line|#include &quot;amd74xx.h&quot;
macro_line|#if defined(DISPLAY_VIPER_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|amd74xx_proc
r_static
id|u8
id|amd74xx_proc
op_assign
l_int|0
suffix:semicolon
DECL|variable|bmide_dev
r_static
r_struct
id|pci_dev
op_star
id|bmide_dev
suffix:semicolon
DECL|function|amd74xx_get_info
r_static
r_int
id|amd74xx_get_info
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|addr
comma
id|off_t
id|offset
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|p
op_assign
id|buffer
suffix:semicolon
id|u32
id|bibma
op_assign
id|pci_resource_start
c_func
(paren
id|bmide_dev
comma
l_int|4
)paren
suffix:semicolon
id|u8
id|c0
op_assign
l_int|0
comma
id|c1
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * at that point bibma+0x2 et bibma+0xa are byte registers&n;&t; * to investigate:&n;&t; */
id|c0
op_assign
id|inb
c_func
(paren
(paren
r_int
r_int
)paren
id|bibma
op_plus
l_int|0x02
)paren
suffix:semicolon
id|c1
op_assign
id|inb
c_func
(paren
(paren
r_int
r_int
)paren
id|bibma
op_plus
l_int|0x0a
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n                                &quot;
l_string|&quot;AMD %04X VIPER Chipset.&bslash;n&quot;
comma
id|bmide_dev-&gt;device
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;--------------- Primary Channel &quot;
l_string|&quot;---------------- Secondary Channel &quot;
l_string|&quot;-------------&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;                %sabled &quot;
l_string|&quot;                        %sabled&bslash;n&quot;
comma
(paren
id|c0
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;dis&quot;
suffix:colon
l_string|&quot; en&quot;
comma
(paren
id|c1
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;dis&quot;
suffix:colon
l_string|&quot; en&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;--------------- drive0 --------- drive1 &quot;
l_string|&quot;-------- drive0 ---------- drive1 ------&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;DMA enabled:    %s              %s &quot;
l_string|&quot;            %s               %s&bslash;n&quot;
comma
(paren
id|c0
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
comma
(paren
id|c0
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
comma
(paren
id|c1
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
comma
(paren
id|c1
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no &quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;UDMA&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;DMA&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;PIO&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|p
op_minus
id|buffer
suffix:semicolon
multiline_comment|/* =&gt; must be less than 4k! */
)brace
macro_line|#endif  /* defined(DISPLAY_VIPER_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
DECL|function|amd74xx_mode5_check
r_static
r_int
id|amd74xx_mode5_check
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_switch
c_cond
(paren
id|dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_AMD_VIPER_7411
suffix:colon
r_case
id|PCI_DEVICE_ID_AMD_VIPER_7441
suffix:colon
r_case
id|PCI_DEVICE_ID_AMD_8111_IDE
suffix:colon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|amd74xx_swdma_check
r_static
r_int
r_int
id|amd74xx_swdma_check
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|class_rev
suffix:semicolon
r_if
c_cond
(paren
id|amd74xx_mode5_check
c_func
(paren
id|dev
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|class_rev
)paren
suffix:semicolon
id|class_rev
op_and_assign
l_int|0xff
suffix:semicolon
r_return
(paren
(paren
r_int
)paren
(paren
id|class_rev
op_ge
l_int|7
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|amd74xx_ratemask
r_static
id|u8
id|amd74xx_ratemask
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|u8
id|mode
suffix:semicolon
r_switch
c_cond
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_AMD_8111_IDE
suffix:colon
r_case
id|PCI_DEVICE_ID_AMD_VIPER_7441
suffix:colon
r_case
id|PCI_DEVICE_ID_AMD_VIPER_7411
suffix:colon
id|mode
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_DEVICE_ID_AMD_VIPER_7409
suffix:colon
id|mode
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_DEVICE_ID_AMD_COBRA_7401
suffix:colon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
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
multiline_comment|/*&n; * Here is where all the hard work goes to program the chipset.&n; */
DECL|function|amd74xx_tune_chipset
r_static
r_int
id|amd74xx_tune_chipset
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|xferspeed
)paren
(brace
id|u8
id|drive_pci
(braket
)braket
op_assign
(brace
l_int|0x53
comma
l_int|0x52
comma
l_int|0x51
comma
l_int|0x50
)brace
suffix:semicolon
id|u8
id|drive_pci2
(braket
)braket
op_assign
(brace
l_int|0x4b
comma
l_int|0x4a
comma
l_int|0x49
comma
l_int|0x48
)brace
suffix:semicolon
macro_line|#if 0
id|u8
id|ultra_rate
(braket
)braket
op_assign
(brace
l_int|0x42
comma
l_int|0x41
comma
l_int|0x40
comma
l_int|0x44
comma
l_int|0x45
comma
l_int|0x46
)brace
suffix:semicolon
id|u8
id|mwdma_rate
(braket
)braket
op_assign
(brace
l_int|0x77
comma
l_int|0x21
comma
l_int|0x20
)brace
suffix:semicolon
id|u8
id|swdma_rate
(braket
)braket
op_assign
(brace
l_int|0xA8
comma
l_int|0x65
comma
l_int|0x42
)brace
suffix:semicolon
id|u8
id|pio_rate
(braket
)braket
op_assign
(brace
l_int|0xA8
comma
l_int|0x65
comma
l_int|0x42
comma
l_int|0x22
comma
l_int|0x20
)brace
suffix:semicolon
macro_line|#endif
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
id|speed
op_assign
id|ide_rate_filter
c_func
(paren
id|amd74xx_ratemask
c_func
(paren
id|drive
)paren
comma
id|xferspeed
)paren
suffix:semicolon
id|u8
id|ultra_timing
op_assign
l_int|0
comma
id|dma_pio_timing
op_assign
l_int|0
comma
id|pio_timing
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|drive_pci
(braket
id|drive-&gt;dn
)braket
comma
op_amp
id|ultra_timing
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|drive_pci2
(braket
id|drive-&gt;dn
)braket
comma
op_amp
id|dma_pio_timing
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x4c
comma
op_amp
id|pio_timing
)paren
suffix:semicolon
id|ultra_timing
op_and_assign
op_complement
l_int|0xC7
suffix:semicolon
id|dma_pio_timing
op_and_assign
op_complement
l_int|0xFF
suffix:semicolon
id|pio_timing
op_and_assign
op_complement
(paren
l_int|0x03
op_lshift
id|drive-&gt;dn
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
id|XFER_UDMA_7
suffix:colon
r_case
id|XFER_UDMA_6
suffix:colon
id|speed
op_assign
id|XFER_UDMA_5
suffix:semicolon
r_case
id|XFER_UDMA_5
suffix:colon
id|ultra_timing
op_or_assign
l_int|0x46
suffix:semicolon
id|dma_pio_timing
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_4
suffix:colon
id|ultra_timing
op_or_assign
l_int|0x45
suffix:semicolon
id|dma_pio_timing
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_3
suffix:colon
id|ultra_timing
op_or_assign
l_int|0x44
suffix:semicolon
id|dma_pio_timing
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_2
suffix:colon
id|ultra_timing
op_or_assign
l_int|0x40
suffix:semicolon
id|dma_pio_timing
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_1
suffix:colon
id|ultra_timing
op_or_assign
l_int|0x41
suffix:semicolon
id|dma_pio_timing
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_0
suffix:colon
id|ultra_timing
op_or_assign
l_int|0x42
suffix:semicolon
id|dma_pio_timing
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_2
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_1
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0x21
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_0
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0x77
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_SW_DMA_2
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0x42
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_SW_DMA_1
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0x65
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_SW_DMA_0
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0xA8
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
r_case
id|XFER_PIO_4
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_PIO_3
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0x22
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_PIO_2
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0x42
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_PIO_1
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0x65
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_PIO_0
suffix:colon
r_default
suffix:colon
id|dma_pio_timing
op_or_assign
l_int|0xA8
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pio_timing
op_or_assign
(paren
l_int|0x03
op_lshift
id|drive-&gt;dn
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|drive_pci
(braket
id|drive-&gt;dn
)braket
comma
id|ultra_timing
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|drive_pci2
(braket
id|drive-&gt;dn
)braket
comma
id|dma_pio_timing
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4c
comma
id|pio_timing
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
DECL|function|amd74xx_tune_drive
r_static
r_void
id|amd74xx_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
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
(paren
r_void
)paren
id|amd74xx_tune_chipset
c_func
(paren
id|drive
comma
(paren
id|XFER_PIO_0
op_plus
id|pio
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
multiline_comment|/*&n; * This allows the configuration of ide_pci chipset registers&n; * for cards that learn about the drive&squot;s UDMA, DMA, PIO capabilities&n; * after the drive is reported by the OS.&n; */
DECL|function|config_chipset_for_dma
r_static
r_int
id|config_chipset_for_dma
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
id|amd74xx_ratemask
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
r_return
l_int|0
suffix:semicolon
(paren
r_void
)paren
id|amd74xx_tune_chipset
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
DECL|function|amd74xx_config_drive_xfer_rate
r_static
r_int
id|amd74xx_config_drive_xfer_rate
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
multiline_comment|/* Consult the list of known &quot;bad&quot; drives */
r_if
c_cond
(paren
id|hwif
op_member_access_from_pointer
id|ide_dma_bad_drive
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
r_int
id|dma
op_assign
id|config_chipset_for_dma
c_func
(paren
id|drive
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
id|dma
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
id|config_chipset_for_dma
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
id|hwif
op_member_access_from_pointer
id|ide_dma_good_drive
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
id|config_chipset_for_dma
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
id|amd74xx_tune_drive
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
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
DECL|function|init_chipset_amd74xx
r_static
r_int
r_int
id|__init
id|init_chipset_amd74xx
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_char
op_star
id|name
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
r_if
c_cond
(paren
op_logical_neg
id|amd74xx_swdma_check
c_func
(paren
id|dev
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;%s: disabling single-word DMA support (revision &lt; C4)&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
macro_line|#if defined(DISPLAY_VIPER_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
r_if
c_cond
(paren
op_logical_neg
id|amd74xx_proc
)paren
(brace
id|amd74xx_proc
op_assign
l_int|1
suffix:semicolon
id|bmide_dev
op_assign
id|dev
suffix:semicolon
id|ide_pci_register_host_proc
c_func
(paren
op_amp
id|amd74xx_procs
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif /* DISPLAY_VIPER_TIMINGS &amp;&amp; CONFIG_PROC_FS */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ata66_amd74xx
r_static
r_int
r_int
id|__init
id|ata66_amd74xx
(paren
id|ide_hwif_t
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
id|u8
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
id|u8
id|ata66
op_assign
l_int|0
suffix:semicolon
id|u8
id|tmpbyte
suffix:semicolon
multiline_comment|/*&n;&t; * Ultra66 cable detection (from Host View)&n;&t; * 7411, 7441, 0x42, bit0: primary, bit2: secondary 80 pin&n;&t; */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x42
comma
op_amp
id|tmpbyte
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * 0x42, bit0 is 1 =&gt; primary channel&n;&t; * has 80-pin (from host view)&n;&t; */
r_if
c_cond
(paren
id|tmpbyte
op_amp
l_int|0x01
)paren
id|cable_80_pin
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * 0x42, bit2 is 1 =&gt; secondary channel&n;&t; * has 80-pin (from host view)&n;&t; */
r_if
c_cond
(paren
id|tmpbyte
op_amp
l_int|0x04
)paren
id|cable_80_pin
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_AMD_COBRA_7401
suffix:colon
id|cable_80_pin
(braket
id|hwif-&gt;channel
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PCI_DEVICE_ID_AMD_8111_IDE
suffix:colon
r_case
id|PCI_DEVICE_ID_AMD_VIPER_7441
suffix:colon
r_case
id|PCI_DEVICE_ID_AMD_VIPER_7411
suffix:colon
id|ata66
op_assign
(paren
id|hwif-&gt;channel
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
r_default
suffix:colon
r_break
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_AMD74XX_OVERRIDE
r_return
l_int|1
suffix:semicolon
macro_line|#else
r_return
(paren
r_int
r_int
)paren
id|ata66
suffix:semicolon
macro_line|#endif /* CONFIG_AMD74XX_OVERRIDE */
)brace
DECL|function|init_hwif_amd74xx
r_static
r_void
id|__init
id|init_hwif_amd74xx
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
op_amp
id|amd74xx_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|amd74xx_tune_chipset
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
l_int|0x3f
suffix:semicolon
id|hwif-&gt;mwdma_mask
op_assign
l_int|0x07
suffix:semicolon
r_if
c_cond
(paren
id|amd74xx_swdma_check
c_func
(paren
id|hwif-&gt;pci_dev
)paren
)paren
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
id|hwif-&gt;udma_four
op_assign
id|ata66_amd74xx
c_func
(paren
id|hwif
)paren
suffix:semicolon
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|amd74xx_config_drive_xfer_rate
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
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
)brace
DECL|function|init_dma_amd74xx
r_static
r_void
id|__init
id|init_dma_amd74xx
(paren
id|ide_hwif_t
op_star
id|hwif
comma
r_int
r_int
id|dmabase
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|hwif-&gt;channel
)paren
)paren
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|dmabase
op_plus
l_int|2
)paren
op_amp
l_int|0x60
comma
id|dmabase
op_plus
l_int|2
)paren
suffix:semicolon
id|ide_setup_dma
c_func
(paren
id|hwif
comma
id|dmabase
comma
l_int|8
)paren
suffix:semicolon
)brace
r_extern
r_void
id|ide_setup_pci_device
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|ide_pci_device_t
op_star
)paren
suffix:semicolon
DECL|function|amd74xx_init_one
r_static
r_int
id|__devinit
id|amd74xx_init_one
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
id|ide_pci_device_t
op_star
id|d
op_assign
op_amp
id|amd74xx_chipsets
(braket
id|id-&gt;driver_data
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device
op_ne
id|d-&gt;device
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|amd74xx_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_COBRA_7401
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
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_VIPER_7409
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
(brace
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_VIPER_7411
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|2
)brace
comma
(brace
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_OPUS_7441
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|3
)brace
comma
(brace
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_8111_IDE
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|4
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|pci_driver
id|driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;AMD IDE&quot;
comma
id|id_table
suffix:colon
id|amd74xx_pci_tbl
comma
id|probe
suffix:colon
id|amd74xx_init_one
comma
)brace
suffix:semicolon
DECL|function|amd74xx_ide_init
r_static
r_int
id|amd74xx_ide_init
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
DECL|function|amd74xx_ide_exit
r_static
r_void
id|amd74xx_ide_exit
c_func
(paren
r_void
)paren
(brace
id|ide_pci_unregister_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|amd74xx_ide_init
id|module_init
c_func
(paren
id|amd74xx_ide_init
)paren
suffix:semicolon
DECL|variable|amd74xx_ide_exit
id|module_exit
c_func
(paren
id|amd74xx_ide_exit
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
l_string|&quot;PCI driver module for AMD IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
eof
