multiline_comment|/*&n; * linux/drivers/ide/pdcadma.c&t;&t;Version 0.01&t;June 21, 2001&n; *&n; * Copyright (C) 1999-2000&t;&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; * May be copied or modified under the terms of the GNU General Public License&n; *&n; */
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
macro_line|#include &quot;ata-timing.h&quot;
DECL|macro|DISPLAY_PDCADMA_TIMINGS
macro_line|#undef DISPLAY_PDCADMA_TIMINGS
macro_line|#if defined(DISPLAY_PDCADMA_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
r_static
r_int
id|pdcadma_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|pdcadma_display_info
)paren
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ide-proc.c */
DECL|variable|bmide_dev
r_static
r_struct
id|pci_dev
op_star
id|bmide_dev
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
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n                                PDC ADMA %04X Chipset.&bslash;n&quot;
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
r_return
id|p
op_minus
id|buffer
suffix:semicolon
multiline_comment|/* =&gt; must be less than 4k! */
)brace
macro_line|#endif  /* defined(DISPLAY_PDCADMA_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
DECL|variable|pdcadma_proc
id|byte
id|pdcadma_proc
op_assign
l_int|0
suffix:semicolon
r_extern
r_char
op_star
id|ide_xfer_verbose
(paren
id|byte
id|xfer_rate
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
multiline_comment|/*&n; * pdcadma_dmaproc() initiates/aborts (U)DMA read/write operations on a drive.&n; */
DECL|function|pdcadma_dmaproc
r_int
id|pdcadma_dmaproc
(paren
id|ide_dma_action_t
id|func
comma
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|ide_dma_check
suffix:colon
id|func
op_assign
id|ide_dma_off_quietly
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|ide_dmaproc
c_func
(paren
id|func
comma
id|drive
)paren
suffix:semicolon
multiline_comment|/* use standard DMA stuff */
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
DECL|function|pci_init_pdcadma
r_int
r_int
id|__init
id|pci_init_pdcadma
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
macro_line|#if defined(DISPLAY_PDCADMA_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
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
id|bmide_dev
op_assign
id|dev
suffix:semicolon
id|pdcadma_display_info
op_assign
op_amp
id|pdcadma_get_info
suffix:semicolon
)brace
macro_line|#endif /* DISPLAY_PDCADMA_TIMINGS &amp;&amp; CONFIG_PROC_FS */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ata66_pdcadma
r_int
r_int
id|__init
id|ata66_pdcadma
c_func
(paren
r_struct
id|ata_channel
op_star
id|channel
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ide_init_pdcadma
r_void
id|__init
id|ide_init_pdcadma
c_func
(paren
r_struct
id|ata_channel
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
singleline_comment|//&t;&t;hwif-&gt;dmaproc = &amp;pdcadma_dmaproc;
singleline_comment|//&t;&t;hwif-&gt;autodma = 1;
singleline_comment|//&t;}
)brace
DECL|function|ide_dmacapable_pdcadma
r_void
id|__init
id|ide_dmacapable_pdcadma
c_func
(paren
r_struct
id|ata_channel
op_star
id|hwif
comma
r_int
r_int
id|dmabase
)paren
(brace
singleline_comment|//&t;ide_setup_dma(hwif, dmabase, 8);
)brace
eof
