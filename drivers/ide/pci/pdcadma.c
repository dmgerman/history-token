multiline_comment|/*&n; * linux/drivers/ide/pdcadma.c&t;&t;Version 0.05&t;Sept 10, 2002&n; *&n; * Copyright (C) 1999-2000&t;&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; * May be copied or modified under the terms of the GNU General Public License&n; *&n; */
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
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;ide_modes.h&quot;
macro_line|#include &quot;pdcadma.h&quot;
macro_line|#if defined(DISPLAY_PDCADMA_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|pdcadma_proc
r_static
id|u8
id|pdcadma_proc
op_assign
l_int|0
suffix:semicolon
DECL|macro|PDC_MAX_DEVS
mdefine_line|#define PDC_MAX_DEVS&t;&t;5
DECL|variable|pdc_devs
r_static
r_struct
id|pci_dev
op_star
id|pdc_devs
(braket
id|PDC_MAX_DEVS
)braket
suffix:semicolon
DECL|variable|n_pdc_devs
r_static
r_int
id|n_pdc_devs
suffix:semicolon
DECL|function|pdcadma_get_info
r_static
r_int
id|pdcadma_get_info
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
id|n_pdc_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|pdc_devs
(braket
id|i
)braket
suffix:semicolon
id|u32
id|bibma
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|4
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
l_string|&quot;PDC ADMA %04X Chipset.&bslash;n&quot;
comma
id|dev-&gt;device
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
l_string|&quot;PIO&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|p
op_minus
id|buffer
suffix:semicolon
multiline_comment|/* =&gt; must be less than 4k! */
)brace
macro_line|#endif  /* defined(DISPLAY_PDCADMA_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
multiline_comment|/*&n; * pdcadma_dma functions() initiates/aborts (U)DMA read/write&n; * operations on a drive.&n; */
macro_line|#if 0
r_int
(paren
op_star
id|ide_dma_read
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_write
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_begin
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_end
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_check
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_on
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_off
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_off_quietly
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_test_irq
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_host_on
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_host_off
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_bad_drive
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_good_drive
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_count
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_verbose
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_retune
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_lostirq
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_int
(paren
op_star
id|ide_dma_timeout
)paren
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
DECL|function|init_chipset_pdcadma
r_static
r_int
r_int
id|__init
id|init_chipset_pdcadma
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
macro_line|#if defined(DISPLAY_PDCADMA_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
id|pdc_devs
(braket
id|n_pdc_devs
op_increment
)braket
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdcadma_proc
)paren
(brace
id|pdcadma_proc
op_assign
l_int|1
suffix:semicolon
id|ide_pci_register_host_proc
c_func
(paren
op_amp
id|pdcadma_procs
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif /* DISPLAY_PDCADMA_TIMINGS &amp;&amp; CONFIG_PROC_FS */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_hwif_pdcadma
r_static
r_void
id|__init
id|init_hwif_pdcadma
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
id|hwif-&gt;dma_base
op_assign
l_int|0
suffix:semicolon
singleline_comment|//&t;hwif-&gt;tuneproc = &amp;pdcadma_tune_drive;
singleline_comment|//&t;hwif-&gt;speedproc = &amp;pdcadma_tune_chipset;
singleline_comment|//&t;if (hwif-&gt;dma_base) {
singleline_comment|//&t;&t;hwif-&gt;autodma = 1;
singleline_comment|//&t;}
id|hwif-&gt;udma_four
op_assign
l_int|1
suffix:semicolon
singleline_comment|//&t;hwif-&gt;atapi_dma = 1;
singleline_comment|//&t;hwif-&gt;ultra_mask = 0x7f;
singleline_comment|//&t;hwif-&gt;mwdma_mask = 0x07;
singleline_comment|//&t;hwif-&gt;swdma_mask = 0x07;
)brace
DECL|function|init_dma_pdcadma
r_static
r_void
id|__init
id|init_dma_pdcadma
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
macro_line|#if 0
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
macro_line|#endif
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
DECL|function|pdcadma_init_one
r_static
r_int
id|__devinit
id|pdcadma_init_one
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
id|pdcadma_chipsets
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
l_int|1
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|pdcadma_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_PDC
comma
id|PCI_DEVICE_ID_PDC_1841
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
DECL|variable|driver
r_static
r_struct
id|pci_driver
id|driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;PDCADMA-IDE&quot;
comma
id|id_table
suffix:colon
id|pdcadma_pci_tbl
comma
id|probe
suffix:colon
id|pdcadma_init_one
comma
)brace
suffix:semicolon
DECL|function|pdcadma_ide_init
r_static
r_int
id|pdcadma_ide_init
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
DECL|function|pdcadma_ide_exit
r_static
r_void
id|pdcadma_ide_exit
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
DECL|variable|pdcadma_ide_init
id|module_init
c_func
(paren
id|pdcadma_ide_init
)paren
suffix:semicolon
DECL|variable|pdcadma_ide_exit
id|module_exit
c_func
(paren
id|pdcadma_ide_exit
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
l_string|&quot;PCI driver module for PDCADMA IDE&quot;
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
