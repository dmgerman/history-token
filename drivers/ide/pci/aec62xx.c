multiline_comment|/*&n; * linux/drivers/ide/pci/aec62xx.c&t;&t;Version 0.11&t;March 27, 2002&n; *&n; * Copyright (C) 1999-2002&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;aec62xx.h&quot;
macro_line|#if 0
r_if
c_cond
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_ARTOP_ATP850UF
)paren
(brace
(paren
r_void
)paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x54
comma
op_amp
id|art
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;DMA Mode:       %s(%s)&quot;
comma
(paren
id|c0
op_amp
l_int|0x20
)paren
ques
c_cond
(paren
(paren
id|art
op_amp
l_int|0x03
)paren
ques
c_cond
l_string|&quot;UDMA&quot;
suffix:colon
l_string|&quot; DMA&quot;
)paren
suffix:colon
l_string|&quot; PIO&quot;
comma
(paren
id|art
op_amp
l_int|0x02
)paren
ques
c_cond
l_string|&quot;2&quot;
suffix:colon
(paren
id|art
op_amp
l_int|0x01
)paren
ques
c_cond
l_string|&quot;1&quot;
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;          %s(%s)&quot;
comma
(paren
id|c0
op_amp
l_int|0x40
)paren
ques
c_cond
(paren
(paren
id|art
op_amp
l_int|0x0c
)paren
ques
c_cond
l_string|&quot;UDMA&quot;
suffix:colon
l_string|&quot; DMA&quot;
)paren
suffix:colon
l_string|&quot; PIO&quot;
comma
(paren
id|art
op_amp
l_int|0x08
)paren
ques
c_cond
l_string|&quot;2&quot;
suffix:colon
(paren
id|art
op_amp
l_int|0x04
)paren
ques
c_cond
l_string|&quot;1&quot;
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;         %s(%s)&quot;
comma
(paren
id|c1
op_amp
l_int|0x20
)paren
ques
c_cond
(paren
(paren
id|art
op_amp
l_int|0x30
)paren
ques
c_cond
l_string|&quot;UDMA&quot;
suffix:colon
l_string|&quot; DMA&quot;
)paren
suffix:colon
l_string|&quot; PIO&quot;
comma
(paren
id|art
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;2&quot;
suffix:colon
(paren
id|art
op_amp
l_int|0x10
)paren
ques
c_cond
l_string|&quot;1&quot;
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;           %s(%s)&bslash;n&quot;
comma
(paren
id|c1
op_amp
l_int|0x40
)paren
ques
c_cond
(paren
(paren
id|art
op_amp
l_int|0xc0
)paren
ques
c_cond
l_string|&quot;UDMA&quot;
suffix:colon
l_string|&quot; DMA&quot;
)paren
suffix:colon
l_string|&quot; PIO&quot;
comma
(paren
id|art
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;2&quot;
suffix:colon
(paren
id|art
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;1&quot;
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#endif
multiline_comment|/*&n; * TO DO: active tuning and correction of cards without a bios.&n; */
DECL|function|pci_bus_clock_list
r_static
id|u8
id|pci_bus_clock_list
(paren
id|u8
id|speed
comma
r_struct
id|chipset_bus_clock_list_entry
op_star
id|chipset_table
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|chipset_table-&gt;xfer_speed
suffix:semicolon
id|chipset_table
op_increment
)paren
r_if
c_cond
(paren
id|chipset_table-&gt;xfer_speed
op_eq
id|speed
)paren
(brace
r_return
id|chipset_table-&gt;chipset_settings
suffix:semicolon
)brace
r_return
id|chipset_table-&gt;chipset_settings
suffix:semicolon
)brace
DECL|function|pci_bus_clock_list_ultra
r_static
id|u8
id|pci_bus_clock_list_ultra
(paren
id|u8
id|speed
comma
r_struct
id|chipset_bus_clock_list_entry
op_star
id|chipset_table
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|chipset_table-&gt;xfer_speed
suffix:semicolon
id|chipset_table
op_increment
)paren
r_if
c_cond
(paren
id|chipset_table-&gt;xfer_speed
op_eq
id|speed
)paren
(brace
r_return
id|chipset_table-&gt;ultra_settings
suffix:semicolon
)brace
r_return
id|chipset_table-&gt;ultra_settings
suffix:semicolon
)brace
DECL|function|aec62xx_ratemask
r_static
id|u8
id|aec62xx_ratemask
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
id|u8
id|mode
suffix:semicolon
r_switch
c_cond
(paren
id|hwif-&gt;pci_dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_ARTOP_ATP865
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP865R
suffix:colon
macro_line|#if 0
id|mode
op_assign
(paren
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|hwif-&gt;dma_master
)paren
op_amp
l_int|0x10
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|3
suffix:semicolon
macro_line|#else
id|mode
op_assign
(paren
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
(paren
(paren
id|hwif-&gt;channel
)paren
ques
c_cond
id|hwif-&gt;mate-&gt;dma_status
suffix:colon
id|hwif-&gt;dma_status
)paren
)paren
op_amp
l_int|0x10
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|3
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP860
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP860R
suffix:colon
id|mode
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP850UF
suffix:colon
r_default
suffix:colon
r_return
l_int|1
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
DECL|function|aec6210_tune_chipset
r_static
r_int
id|aec6210_tune_chipset
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
id|u16
id|d_conf
op_assign
l_int|0
suffix:semicolon
id|u8
id|speed
op_assign
id|ide_rate_filter
c_func
(paren
id|aec62xx_ratemask
c_func
(paren
id|drive
)paren
comma
id|xferspeed
)paren
suffix:semicolon
id|u8
id|ultra
op_assign
l_int|0
comma
id|ultra_conf
op_assign
l_int|0
suffix:semicolon
id|u8
id|tmp0
op_assign
l_int|0
comma
id|tmp1
op_assign
l_int|0
comma
id|tmp2
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* 0x40|(2*drive-&gt;dn): Active, 0x41|(2*drive-&gt;dn): Recovery */
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x40
op_or
(paren
l_int|2
op_star
id|drive-&gt;dn
)paren
comma
op_amp
id|d_conf
)paren
suffix:semicolon
id|tmp0
op_assign
id|pci_bus_clock_list
c_func
(paren
id|speed
comma
id|BUSCLOCK
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|SPLIT_BYTE
c_func
(paren
id|tmp0
comma
id|tmp1
comma
id|tmp2
)paren
suffix:semicolon
id|MAKE_WORD
c_func
(paren
id|d_conf
comma
id|tmp1
comma
id|tmp2
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x40
op_or
(paren
l_int|2
op_star
id|drive-&gt;dn
)paren
comma
id|d_conf
)paren
suffix:semicolon
id|tmp1
op_assign
l_int|0x00
suffix:semicolon
id|tmp2
op_assign
l_int|0x00
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x54
comma
op_amp
id|ultra
)paren
suffix:semicolon
id|tmp1
op_assign
(paren
(paren
l_int|0x00
op_lshift
(paren
l_int|2
op_star
id|drive-&gt;dn
)paren
)paren
op_or
(paren
id|ultra
op_amp
op_complement
(paren
l_int|3
op_lshift
(paren
l_int|2
op_star
id|drive-&gt;dn
)paren
)paren
)paren
)paren
suffix:semicolon
id|ultra_conf
op_assign
id|pci_bus_clock_list_ultra
c_func
(paren
id|speed
comma
id|BUSCLOCK
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|tmp2
op_assign
(paren
(paren
id|ultra_conf
op_lshift
(paren
l_int|2
op_star
id|drive-&gt;dn
)paren
)paren
op_or
(paren
id|tmp1
op_amp
op_complement
(paren
l_int|3
op_lshift
(paren
l_int|2
op_star
id|drive-&gt;dn
)paren
)paren
)paren
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x54
comma
id|tmp2
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
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
DECL|function|aec6260_tune_chipset
r_static
r_int
id|aec6260_tune_chipset
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
id|speed
op_assign
id|ide_rate_filter
c_func
(paren
id|aec62xx_ratemask
c_func
(paren
id|drive
)paren
comma
id|xferspeed
)paren
suffix:semicolon
id|u8
id|unit
op_assign
(paren
id|drive-&gt;select.b.unit
op_amp
l_int|0x01
)paren
suffix:semicolon
id|u8
id|tmp1
op_assign
l_int|0
comma
id|tmp2
op_assign
l_int|0
suffix:semicolon
id|u8
id|ultra
op_assign
l_int|0
comma
id|drive_conf
op_assign
l_int|0
comma
id|ultra_conf
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* high 4-bits: Active, low 4-bits: Recovery */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x40
op_or
id|drive-&gt;dn
comma
op_amp
id|drive_conf
)paren
suffix:semicolon
id|drive_conf
op_assign
id|pci_bus_clock_list
c_func
(paren
id|speed
comma
id|BUSCLOCK
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x40
op_or
id|drive-&gt;dn
comma
id|drive_conf
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
(paren
l_int|0x44
op_or
id|hwif-&gt;channel
)paren
comma
op_amp
id|ultra
)paren
suffix:semicolon
id|tmp1
op_assign
(paren
(paren
l_int|0x00
op_lshift
(paren
l_int|4
op_star
id|unit
)paren
)paren
op_or
(paren
id|ultra
op_amp
op_complement
(paren
l_int|7
op_lshift
(paren
l_int|4
op_star
id|unit
)paren
)paren
)paren
)paren
suffix:semicolon
id|ultra_conf
op_assign
id|pci_bus_clock_list_ultra
c_func
(paren
id|speed
comma
id|BUSCLOCK
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|tmp2
op_assign
(paren
(paren
id|ultra_conf
op_lshift
(paren
l_int|4
op_star
id|unit
)paren
)paren
op_or
(paren
id|tmp1
op_amp
op_complement
(paren
l_int|7
op_lshift
(paren
l_int|4
op_star
id|unit
)paren
)paren
)paren
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
(paren
l_int|0x44
op_or
id|hwif-&gt;channel
)paren
comma
id|tmp2
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
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
DECL|function|aec62xx_tune_chipset
r_static
r_int
id|aec62xx_tune_chipset
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|speed
)paren
(brace
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
id|PCI_DEVICE_ID_ARTOP_ATP865
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP865R
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP860
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP860R
suffix:colon
r_return
(paren
(paren
r_int
)paren
id|aec6260_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
)paren
suffix:semicolon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP850UF
suffix:colon
r_return
(paren
(paren
r_int
)paren
id|aec6210_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
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
id|aec62xx_ratemask
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
id|aec62xx_tune_chipset
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
DECL|function|aec62xx_tune_drive
r_static
r_void
id|aec62xx_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|pio
)paren
(brace
id|u8
id|speed
op_assign
l_int|0
suffix:semicolon
id|u8
id|new_pio
op_assign
id|XFER_PIO_0
op_plus
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
r_switch
c_cond
(paren
id|pio
)paren
(brace
r_case
l_int|5
suffix:colon
id|speed
op_assign
id|new_pio
suffix:semicolon
r_break
suffix:semicolon
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
(paren
r_void
)paren
id|aec62xx_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
)brace
DECL|function|aec62xx_config_drive_xfer_rate
r_static
r_int
id|aec62xx_config_drive_xfer_rate
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
id|config_chipset_for_dma
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
id|aec62xx_tune_drive
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
DECL|function|aec62xx_irq_timeout
r_static
r_int
id|aec62xx_irq_timeout
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
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;device
)paren
(brace
r_case
id|PCI_DEVICE_ID_ARTOP_ATP860
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP860R
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP865
suffix:colon
r_case
id|PCI_DEVICE_ID_ARTOP_ATP865R
suffix:colon
id|printk
c_func
(paren
l_string|&quot; AEC62XX time out &quot;
)paren
suffix:semicolon
macro_line|#if 0
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|u8
id|reg49h
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x49
comma
op_amp
id|reg49h
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
id|pci_write_config_byte
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x49
comma
id|reg49h
op_or
l_int|0x10
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x49
comma
id|reg49h
op_amp
op_complement
l_int|0x10
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_break
suffix:semicolon
)brace
macro_line|#if 0
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
id|tmp1
op_assign
l_int|0
comma
id|tmp2
op_assign
l_int|0
comma
id|mode6
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x44
comma
op_amp
id|tmp1
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x45
comma
op_amp
id|tmp2
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; AEC6280 r44=%x r45=%x &quot;
comma
id|tmp1
comma
id|tmp2
)paren
suffix:semicolon
id|mode6
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|INB
c_func
(paren
(paren
(paren
id|hwif-&gt;channel
)paren
ques
c_cond
id|hwif-&gt;mate-&gt;dma_status
suffix:colon
id|hwif-&gt;dma_status
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; AEC6280 133=%x &quot;
comma
(paren
id|mode6
op_amp
l_int|0x10
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_chipset_aec62xx
r_static
r_int
r_int
id|__devinit
id|init_chipset_aec62xx
c_func
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
r_int
id|bus_speed
op_assign
id|system_bus_clock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
)paren
(brace
id|pci_write_config_dword
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
l_string|&quot;%s: ROM enabled at 0x%08lx&bslash;n&quot;
comma
id|name
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
r_if
c_cond
(paren
id|bus_speed
op_le
l_int|33
)paren
id|pci_set_drvdata
c_func
(paren
id|dev
comma
(paren
r_void
op_star
)paren
id|aec6xxx_33_base
)paren
suffix:semicolon
r_else
id|pci_set_drvdata
c_func
(paren
id|dev
comma
(paren
r_void
op_star
)paren
id|aec6xxx_34_base
)paren
suffix:semicolon
r_return
id|dev-&gt;irq
suffix:semicolon
)brace
DECL|function|init_hwif_aec62xx
r_static
r_void
id|__devinit
id|init_hwif_aec62xx
c_func
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
id|aec62xx_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|aec62xx_tune_chipset
suffix:semicolon
r_if
c_cond
(paren
id|hwif-&gt;pci_dev-&gt;device
op_eq
id|PCI_DEVICE_ID_ARTOP_ATP850UF
)paren
(brace
id|hwif-&gt;serialized
op_assign
id|hwif-&gt;channel
suffix:semicolon
id|hwif-&gt;no_dsc
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hwif-&gt;mate
)paren
id|hwif-&gt;mate-&gt;serialized
op_assign
id|hwif-&gt;serialized
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
id|hwif-&gt;ultra_mask
op_assign
l_int|0x7f
suffix:semicolon
id|hwif-&gt;mwdma_mask
op_assign
l_int|0x07
suffix:semicolon
id|hwif-&gt;swdma_mask
op_assign
l_int|0x07
suffix:semicolon
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|aec62xx_config_drive_xfer_rate
suffix:semicolon
id|hwif-&gt;ide_dma_lostirq
op_assign
op_amp
id|aec62xx_irq_timeout
suffix:semicolon
id|hwif-&gt;ide_dma_timeout
op_assign
op_amp
id|aec62xx_irq_timeout
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
)brace
DECL|function|init_dma_aec62xx
r_static
r_void
id|__devinit
id|init_dma_aec62xx
c_func
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
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_ARTOP_ATP850UF
)paren
(brace
id|u8
id|reg54h
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
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
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x54
comma
op_amp
id|reg54h
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x54
comma
id|reg54h
op_amp
op_complement
(paren
id|hwif-&gt;channel
ques
c_cond
l_int|0xF0
suffix:colon
l_int|0x0F
)paren
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
r_else
(brace
id|u8
id|ata66
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|hwif-&gt;pci_dev
comma
l_int|0x49
comma
op_amp
id|ata66
)paren
suffix:semicolon
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
(paren
id|ata66
op_amp
(paren
id|hwif-&gt;channel
ques
c_cond
l_int|0x02
suffix:colon
l_int|0x01
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
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
DECL|function|init_setup_aec62xx
r_static
r_int
id|__devinit
id|init_setup_aec62xx
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|ide_pci_device_t
op_star
id|d
)paren
(brace
r_return
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
)brace
DECL|function|init_setup_aec6x80
r_static
r_int
id|__devinit
id|init_setup_aec6x80
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|ide_pci_device_t
op_star
id|d
)paren
(brace
r_int
r_int
id|bar4reg
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|bar4reg
op_plus
l_int|2
)paren
op_amp
l_int|0x10
)paren
(brace
id|strcpy
c_func
(paren
id|d-&gt;name
comma
l_string|&quot;AEC6880&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_ARTOP_ATP865R
)paren
id|strcpy
c_func
(paren
id|d-&gt;name
comma
l_string|&quot;AEC6880R&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|d-&gt;name
comma
l_string|&quot;AEC6280&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_ARTOP_ATP865R
)paren
id|strcpy
c_func
(paren
id|d-&gt;name
comma
l_string|&quot;AEC6280R&quot;
)paren
suffix:semicolon
)brace
r_return
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aec62xx_init_one&t;-&t;called when a AEC is found&n; *&t;@dev: the aec62xx device&n; *&t;@id: the matching pci id&n; *&n; *&t;Called when the PCI registration layer (or the IDE initialization)&n; *&t;finds a device matching our IDE device tables.&n; */
DECL|function|aec62xx_init_one
r_static
r_int
id|__devinit
id|aec62xx_init_one
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
id|aec62xx_chipsets
(braket
id|id-&gt;driver_data
)braket
suffix:semicolon
r_return
id|d
op_member_access_from_pointer
id|init_setup
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
)brace
DECL|variable|aec62xx_pci_tbl
r_static
r_struct
id|pci_device_id
id|aec62xx_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_ARTOP
comma
id|PCI_DEVICE_ID_ARTOP_ATP850UF
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
id|PCI_VENDOR_ID_ARTOP
comma
id|PCI_DEVICE_ID_ARTOP_ATP860
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
id|PCI_VENDOR_ID_ARTOP
comma
id|PCI_DEVICE_ID_ARTOP_ATP860R
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
id|PCI_VENDOR_ID_ARTOP
comma
id|PCI_DEVICE_ID_ARTOP_ATP865
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
id|PCI_VENDOR_ID_ARTOP
comma
id|PCI_DEVICE_ID_ARTOP_ATP865R
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
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|aec62xx_pci_tbl
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
l_string|&quot;AEC62xx_IDE&quot;
comma
dot
id|id_table
op_assign
id|aec62xx_pci_tbl
comma
dot
id|probe
op_assign
id|aec62xx_init_one
comma
)brace
suffix:semicolon
DECL|function|aec62xx_ide_init
r_static
r_int
id|aec62xx_ide_init
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
DECL|variable|aec62xx_ide_init
id|module_init
c_func
(paren
id|aec62xx_ide_init
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
l_string|&quot;PCI driver module for ARTOP AEC62xx IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
