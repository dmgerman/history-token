multiline_comment|/*&n; *&t;IDE tuning and bus mastering support for the CS5510/CS5520&n; *&t;chipsets&n; *&n; *&t;The CS5510/CS5520 are slightly unusual devices. Unlike the &n; *&t;typical IDE controllers they do bus mastering with the drive in&n; *&t;PIO mode and smarter silicon.&n; *&n; *&t;The practical upshot of this is that we must always tune the&n; *&t;drive for the right PIO mode. We must also ignore all the blacklists&n; *&t;and the drive bus mastering DMA information.&n; *&n; *&t;*** This driver is strictly experimental ***&n; *&n; *&t;(c) Copyright Red Hat Inc 2002&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * For the avoidance of doubt the &quot;preferred form&quot; of this code is one which&n; * is in an open non patent encumbered format. Where cryptographic key signing&n; * forms part of the process of creating an executable the information&n; * including keys needed to generate an equivalently functional executable&n; * are deemed to be part of the source code.&n; *&n; */
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
DECL|macro|DISPLAY_CS5520_TIMINGS
mdefine_line|#define DISPLAY_CS5520_TIMINGS
macro_line|#if defined(DISPLAY_CS5520_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|cs5520_proc
r_static
id|u8
id|cs5520_proc
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
DECL|function|cs5520_get_info
r_static
r_int
id|cs5520_get_info
c_func
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
r_int
r_int
id|bmiba
op_assign
id|pci_resource_start
c_func
(paren
id|bmide_dev
comma
l_int|2
)paren
suffix:semicolon
r_int
id|len
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
id|u16
id|reg16
suffix:semicolon
id|u32
id|reg32
suffix:semicolon
multiline_comment|/*&n;&t; * at that point bibma+0x2 et bibma+0xa are byte registers&n;&t; * to investigate:&n;&t; */
id|c0
op_assign
id|inb
c_func
(paren
id|bmiba
op_plus
l_int|0x02
)paren
suffix:semicolon
id|c1
op_assign
id|inb
c_func
(paren
id|bmiba
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
l_string|&quot;&bslash;nCyrix CS55x0 IDE&bslash;n&quot;
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
l_string|&quot;&bslash;n&bslash;nTimings: &bslash;n&quot;
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|bmide_dev
comma
l_int|0x62
comma
op_amp
id|reg16
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;8bit CAT/CRT   : %04x&bslash;n&quot;
comma
id|reg16
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|bmide_dev
comma
l_int|0x64
comma
op_amp
id|reg32
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;16bit Primary  : %08x&bslash;n&quot;
comma
id|reg32
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|bmide_dev
comma
l_int|0x68
comma
op_amp
id|reg32
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;16bit Secondary: %08x&bslash;n&quot;
comma
id|reg32
)paren
suffix:semicolon
id|len
op_assign
(paren
id|p
op_minus
id|buffer
)paren
op_minus
id|offset
suffix:semicolon
op_star
id|addr
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
r_return
id|len
OG
id|count
ques
c_cond
id|count
suffix:colon
id|len
suffix:semicolon
)brace
macro_line|#endif
DECL|struct|pio_clocks
r_struct
id|pio_clocks
(brace
DECL|member|address
r_int
id|address
suffix:semicolon
DECL|member|assert
r_int
m_assert
suffix:semicolon
DECL|member|recovery
r_int
id|recovery
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|cs5520_pio_clocks
r_struct
id|pio_clocks
id|cs5520_pio_clocks
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|cs5520_tune_chipset
r_static
r_int
id|cs5520_tune_chipset
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
id|pdev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|u8
id|speed
op_assign
id|min
c_func
(paren
(paren
id|u8
)paren
id|XFER_PIO_4
comma
id|xferspeed
)paren
suffix:semicolon
r_int
id|pio
op_assign
id|speed
suffix:semicolon
id|u8
id|reg
suffix:semicolon
r_int
id|controller
op_assign
id|drive-&gt;dn
OG
l_int|1
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
r_switch
c_cond
(paren
id|speed
)paren
(brace
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
id|pio
op_sub_assign
id|XFER_PIO_0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|pio
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cs55x0: bad ide timing.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PIO clocking = %d&bslash;n&quot;
comma
id|pio
)paren
suffix:semicolon
multiline_comment|/* FIXME: if DMA = 1 do we need to set the DMA bit here ? */
multiline_comment|/* 8bit command timing for channel */
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
l_int|0x62
op_plus
id|controller
comma
(paren
id|cs5520_pio_clocks
(braket
id|pio
)braket
dot
id|recovery
op_lshift
l_int|4
)paren
op_or
(paren
id|cs5520_pio_clocks
(braket
id|pio
)braket
dot
m_assert
)paren
)paren
suffix:semicolon
multiline_comment|/* FIXME: should these use address ? */
multiline_comment|/* Data read timing */
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
l_int|0x64
op_plus
l_int|4
op_star
id|controller
op_plus
(paren
id|drive-&gt;dn
op_amp
l_int|1
)paren
comma
(paren
id|cs5520_pio_clocks
(braket
id|pio
)braket
dot
id|recovery
op_lshift
l_int|4
)paren
op_or
(paren
id|cs5520_pio_clocks
(braket
id|pio
)braket
dot
m_assert
)paren
)paren
suffix:semicolon
multiline_comment|/* Write command timing */
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
l_int|0x66
op_plus
l_int|4
op_star
id|controller
op_plus
(paren
id|drive-&gt;dn
op_amp
l_int|1
)paren
comma
(paren
id|cs5520_pio_clocks
(braket
id|pio
)braket
dot
id|recovery
op_lshift
l_int|4
)paren
op_or
(paren
id|cs5520_pio_clocks
(braket
id|pio
)braket
dot
m_assert
)paren
)paren
suffix:semicolon
multiline_comment|/* Set the DMA enable/disable flag */
id|reg
op_assign
id|inb
c_func
(paren
id|hwif-&gt;dma_base
op_plus
l_int|0x02
op_plus
l_int|8
op_star
id|controller
)paren
suffix:semicolon
id|reg
op_or_assign
l_int|1
op_lshift
(paren
(paren
id|drive-&gt;dn
op_amp
l_int|1
)paren
op_plus
l_int|5
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|hwif-&gt;dma_base
op_plus
l_int|0x02
op_plus
l_int|8
op_star
id|controller
)paren
suffix:semicolon
id|error
op_assign
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
multiline_comment|/* ATAPI is harder so leave it for now */
r_if
c_cond
(paren
op_logical_neg
id|error
op_logical_and
id|drive-&gt;media
op_eq
id|ide_disk
)paren
(brace
id|error
op_assign
id|hwif
op_member_access_from_pointer
id|ide_dma_on
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|cs5520_tune_drive
r_static
r_void
id|cs5520_tune_drive
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
id|pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
l_int|4
comma
l_int|NULL
)paren
suffix:semicolon
id|cs5520_tune_chipset
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
DECL|function|cs5520_config_drive_xfer_rate
r_static
r_int
id|cs5520_config_drive_xfer_rate
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
multiline_comment|/* Tune the drive for PIO modes up to PIO 4 */
id|cs5520_tune_drive
c_func
(paren
id|drive
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Then tell the core to use DMA operations */
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
DECL|function|init_chipset_cs5520
r_static
r_int
r_int
id|__devinit
id|init_chipset_cs5520
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
macro_line|#if defined(DISPLAY_CS5520_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
r_if
c_cond
(paren
op_logical_neg
id|cs5520_proc
)paren
(brace
id|cs5520_proc
op_assign
l_int|1
suffix:semicolon
id|bmide_dev
op_assign
id|dev
suffix:semicolon
id|ide_pci_create_host_proc
c_func
(paren
l_string|&quot;cs5520&quot;
comma
id|cs5520_get_info
)paren
suffix:semicolon
)brace
macro_line|#endif /* DISPLAY_CS5520_TIMINGS &amp;&amp; CONFIG_PROC_FS */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;We provide a callback for our nonstandard DMA location&n; */
DECL|function|cs5520_init_setup_dma
r_static
r_void
id|__devinit
id|cs5520_init_setup_dma
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
comma
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_int
r_int
id|bmide
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Not the usual 4 */
r_if
c_cond
(paren
id|hwif-&gt;mate
op_logical_and
id|hwif-&gt;mate-&gt;dma_base
)paren
(brace
multiline_comment|/* Second channel at primary + 8 */
id|bmide
op_add_assign
l_int|8
suffix:semicolon
)brace
id|ide_setup_dma
c_func
(paren
id|hwif
comma
id|bmide
comma
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;We wrap the DMA activate to set the vdma flag. This is needed&n; *&t;so that the IDE DMA layer issues PIO not DMA commands over the&n; *&t;DMA channel&n; */
DECL|function|cs5520_dma_on
r_static
r_int
id|cs5520_dma_on
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|drive-&gt;vdma
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_hwif_cs5520
r_static
r_void
id|__devinit
id|init_hwif_cs5520
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|hwif-&gt;tuneproc
op_assign
op_amp
id|cs5520_tune_drive
suffix:semicolon
id|hwif-&gt;speedproc
op_assign
op_amp
id|cs5520_tune_chipset
suffix:semicolon
id|hwif-&gt;ide_dma_check
op_assign
op_amp
id|cs5520_config_drive_xfer_rate
suffix:semicolon
id|hwif-&gt;ide_dma_on
op_assign
op_amp
id|cs5520_dma_on
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|noautodma
)paren
(brace
id|hwif-&gt;autodma
op_assign
l_int|1
suffix:semicolon
)brace
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
l_int|0
suffix:semicolon
id|hwif-&gt;ultra_mask
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;swdma_mask
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;mwdma_mask
op_assign
l_int|0
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
DECL|macro|DECLARE_CS_DEV
mdefine_line|#define DECLARE_CS_DEV(name_str)&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.name&t;&t;= name_str,&t;&t;&t;&bslash;&n;&t;&t;.init_chipset&t;= init_chipset_cs5520,&t;&t;&bslash;&n;&t;&t;.init_setup_dma = cs5520_init_setup_dma,&t;&bslash;&n;&t;&t;.init_hwif&t;= init_hwif_cs5520,&t;&t;&bslash;&n;&t;&t;.channels&t;= 2,&t;&t;&t;&t;&bslash;&n;&t;&t;.autodma&t;= AUTODMA,&t;&t;&t;&bslash;&n;&t;&t;.bootable&t;= ON_BOARD,&t;&t;&t;&bslash;&n;&t;&t;.flags&t;&t;= IDEPCI_FLAG_ISA_PORTS,&t;&bslash;&n;&t;}
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|cyrix_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
multiline_comment|/* 0 */
id|DECLARE_CS_DEV
c_func
(paren
l_string|&quot;Cyrix 5510&quot;
)paren
comma
multiline_comment|/* 1 */
id|DECLARE_CS_DEV
c_func
(paren
l_string|&quot;Cyrix 5520&quot;
)paren
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;The 5510/5520 are a bit weird. They don&squot;t quite set up the way&n; *&t;the PCI helper layer expects so we must do much of the set up &n; *&t;work longhand.&n; */
DECL|function|cs5520_init_one
r_static
r_int
id|__devinit
id|cs5520_init_one
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
id|ata_index_t
id|index
suffix:semicolon
id|ide_pci_device_t
op_star
id|d
op_assign
op_amp
id|cyrix_chipsets
(braket
id|id-&gt;driver_data
)braket
suffix:semicolon
id|ide_setup_pci_noise
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
multiline_comment|/* We must not grab the entire device, it has &squot;ISA&squot; space in its&n;&t;   BARS too and we will freak out other bits of the kernel */
r_if
c_cond
(paren
id|pci_enable_device_bars
c_func
(paren
id|dev
comma
l_int|1
op_lshift
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Unable to enable 55x0.&bslash;n&quot;
comma
id|d-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|pci_set_master
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_set_dma_mask
c_func
(paren
id|dev
comma
l_int|0xFFFFFFFF
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cs5520: No suitable DMA available.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|init_chipset_cs5520
c_func
(paren
id|dev
comma
id|d-&gt;name
)paren
suffix:semicolon
id|index.all
op_assign
l_int|0xf0f0
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Now the chipset is configured we can let the core&n;&t; *&t;do all the device setup for us&n;&t; */
id|ide_pci_setup_ports
c_func
(paren
id|dev
comma
id|d
comma
l_int|1
comma
l_int|14
comma
op_amp
id|index
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Index.b %d %d&bslash;n&quot;
comma
id|index.b.low
comma
id|index.b.high
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|index.b.low
op_amp
l_int|0xf0
)paren
op_ne
l_int|0xf0
)paren
(brace
id|probe_hwif_init
c_func
(paren
op_amp
id|ide_hwifs
(braket
id|index.b.low
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|index.b.high
op_amp
l_int|0xf0
)paren
op_ne
l_int|0xf0
)paren
(brace
id|probe_hwif_init
c_func
(paren
op_amp
id|ide_hwifs
(braket
id|index.b.high
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cs5520_pci_tbl
r_static
r_struct
id|pci_device_id
id|cs5520_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_CYRIX
comma
id|PCI_DEVICE_ID_CYRIX_5510
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
id|PCI_VENDOR_ID_CYRIX
comma
id|PCI_DEVICE_ID_CYRIX_5520
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
id|cs5520_pci_tbl
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
l_string|&quot;Cyrix_IDE&quot;
comma
dot
id|id_table
op_assign
id|cs5520_pci_tbl
comma
dot
id|probe
op_assign
id|cs5520_init_one
comma
)brace
suffix:semicolon
DECL|function|cs5520_ide_init
r_static
r_int
id|cs5520_ide_init
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
DECL|variable|cs5520_ide_init
id|module_init
c_func
(paren
id|cs5520_ide_init
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Alan Cox&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for Cyrix 5510/5520 IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
