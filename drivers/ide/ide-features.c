multiline_comment|/*&n; * linux/drivers/block/ide-features.c&t;Version 0.04&t;June 9, 2000&n; *&n; *  Copyright (C) 1999-2000&t;Linus Torvalds &amp; authors (see below)&n; *&n; *  Copyright (C) 1999-2000&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; *&n; *  Extracts if ide.c to address the evolving transfer rate code for&n; *  the SETFEATURES_XFER callouts.  Various parts of any given function&n; *  are credited to previous ATA-IDE maintainers.&n; *&n; *  Auto-CRC downgrade for Ultra DMA(ing)&n; *&n; *  May be copied or modified under the terms of the GNU General Public License&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
multiline_comment|/*&n; * A Verbose noise maker for debugging on the attempted transfer rates.&n; */
DECL|function|ide_xfer_verbose
r_char
op_star
id|ide_xfer_verbose
(paren
id|byte
id|xfer_rate
)paren
(brace
r_static
r_struct
id|ide_xfer_par
(brace
id|byte
id|rate
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
)brace
id|xfer_verbose
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_7
comma
l_string|&quot;UDMA 7&quot;
)brace
comma
(brace
id|XFER_UDMA_6
comma
l_string|&quot;UDMA 6&quot;
)brace
comma
(brace
id|XFER_UDMA_5
comma
l_string|&quot;UDMA 5&quot;
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_string|&quot;UDMA 4&quot;
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_string|&quot;UDMA 3&quot;
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_string|&quot;UDMA 2&quot;
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_string|&quot;UDMA 1&quot;
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_string|&quot;UDMA 0&quot;
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_string|&quot;MW DMA 2&quot;
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_string|&quot;MW DMA 1&quot;
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_string|&quot;MW DMA 0&quot;
)brace
comma
(brace
id|XFER_SW_DMA_2
comma
l_string|&quot;SW DMA 2&quot;
)brace
comma
(brace
id|XFER_SW_DMA_1
comma
l_string|&quot;SW DMA 1&quot;
)brace
comma
(brace
id|XFER_SW_DMA_0
comma
l_string|&quot;SW DMA 0&quot;
)brace
comma
(brace
id|XFER_PIO_4
comma
l_string|&quot;PIO 4&quot;
)brace
comma
(brace
id|XFER_PIO_3
comma
l_string|&quot;PIO 3&quot;
)brace
comma
(brace
id|XFER_PIO_2
comma
l_string|&quot;PIO 2&quot;
)brace
comma
(brace
id|XFER_PIO_1
comma
l_string|&quot;PIO 1&quot;
)brace
comma
(brace
id|XFER_PIO_0
comma
l_string|&quot;PIO 0&quot;
)brace
comma
(brace
id|XFER_PIO_SLOW
comma
l_string|&quot;PIO SLOW&quot;
)brace
comma
)brace
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|xfer_verbose
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|xfer_verbose
(braket
id|i
)braket
dot
id|rate
op_eq
id|xfer_rate
)paren
r_return
id|xfer_verbose
(braket
id|i
)braket
dot
id|name
suffix:semicolon
r_return
l_string|&quot;XFER ERROR&quot;
suffix:semicolon
)brace
DECL|function|ide_auto_reduce_xfer
id|byte
id|ide_auto_reduce_xfer
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;crc_count
)paren
r_return
id|drive-&gt;current_speed
suffix:semicolon
id|drive-&gt;crc_count
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|drive-&gt;current_speed
)paren
(brace
r_case
id|XFER_UDMA_7
suffix:colon
r_return
id|XFER_UDMA_6
suffix:semicolon
r_case
id|XFER_UDMA_6
suffix:colon
r_return
id|XFER_UDMA_5
suffix:semicolon
r_case
id|XFER_UDMA_5
suffix:colon
r_return
id|XFER_UDMA_4
suffix:semicolon
r_case
id|XFER_UDMA_4
suffix:colon
r_return
id|XFER_UDMA_3
suffix:semicolon
r_case
id|XFER_UDMA_3
suffix:colon
r_return
id|XFER_UDMA_2
suffix:semicolon
r_case
id|XFER_UDMA_2
suffix:colon
r_return
id|XFER_UDMA_1
suffix:semicolon
r_case
id|XFER_UDMA_1
suffix:colon
r_return
id|XFER_UDMA_0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * OOPS we do not goto non Ultra DMA modes&n;&t;&t;&t; * without iCRC&squot;s available we force&n;&t;&t;&t; * the system to PIO and make the user&n;&t;&t;&t; * invoke the ATA-1 ATA-2 DMA modes.&n;&t;&t;&t; */
r_case
id|XFER_UDMA_0
suffix:colon
r_default
suffix:colon
r_return
id|XFER_PIO_4
suffix:semicolon
)brace
)brace
DECL|function|ide_driveid_update
r_int
id|ide_driveid_update
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
multiline_comment|/*&n;&t; * Re-read drive-&gt;id for possible DMA mode&n;&t; * change (copied from ide-probe.c)&n;&t; */
r_struct
id|hd_driveid
op_star
id|id
suffix:semicolon
r_int
r_int
id|timeout
comma
id|flags
suffix:semicolon
id|SELECT_MASK
c_func
(paren
id|drive-&gt;channel
comma
id|drive
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IDE_CONTROL_REG
)paren
id|OUT_BYTE
c_func
(paren
id|drive-&gt;ctl
comma
id|IDE_CONTROL_REG
)paren
suffix:semicolon
id|ide_delay_50ms
c_func
(paren
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|WIN_IDENTIFY
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
id|timeout
op_assign
id|jiffies
op_plus
id|WAIT_WORSTCASE
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
l_int|0
OL
(paren
r_int
r_int
)paren
(paren
id|jiffies
op_minus
id|timeout
)paren
)paren
(brace
id|SELECT_MASK
c_func
(paren
id|drive-&gt;channel
comma
id|drive
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* drive timed-out */
)brace
id|ide_delay_50ms
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* give drive a breather */
)brace
r_while
c_loop
(paren
id|IN_BYTE
c_func
(paren
id|IDE_ALTSTATUS_REG
)paren
op_amp
id|BUSY_STAT
)paren
suffix:semicolon
id|ide_delay_50ms
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* wait for IRQ and DRQ_STAT */
r_if
c_cond
(paren
op_logical_neg
id|OK_STAT
c_func
(paren
id|GET_STAT
c_func
(paren
)paren
comma
id|DRQ_STAT
comma
id|BAD_R_STAT
)paren
)paren
(brace
id|SELECT_MASK
c_func
(paren
id|drive-&gt;channel
comma
id|drive
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CHECK for good STATUS&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
multiline_comment|/* local CPU only; some systems need this */
id|SELECT_MASK
c_func
(paren
id|drive-&gt;channel
comma
id|drive
comma
l_int|0
)paren
suffix:semicolon
id|id
op_assign
id|kmalloc
c_func
(paren
id|SECTOR_WORDS
op_star
l_int|4
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|id
)paren
(brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
r_return
l_int|0
suffix:semicolon
)brace
id|ata_read
c_func
(paren
id|drive
comma
id|id
comma
id|SECTOR_WORDS
)paren
suffix:semicolon
id|GET_STAT
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* clear drive IRQ */
id|ide__sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|ide_fix_driveid
c_func
(paren
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
)paren
(brace
id|drive-&gt;id-&gt;dma_ultra
op_assign
id|id-&gt;dma_ultra
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_assign
id|id-&gt;dma_mword
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_assign
id|id-&gt;dma_1word
suffix:semicolon
multiline_comment|/* anything more ? */
id|kfree
c_func
(paren
id|id
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Verify that we are doing an approved SETFEATURES_XFER with respect&n; * to the hardware being able to support request.  Since some hardware&n; * can improperly report capabilties, we check to see if the host adapter&n; * in combination with the device (usually a disk) properly detect&n; * and acknowledge each end of the ribbon.&n; */
DECL|function|ide_ata66_check
r_int
id|ide_ata66_check
(paren
id|ide_drive_t
op_star
id|drive
comma
r_struct
id|ata_taskfile
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
(paren
id|args-&gt;taskfile.command
op_eq
id|WIN_SETFEATURES
)paren
op_logical_and
(paren
id|args-&gt;taskfile.sector_number
OG
id|XFER_UDMA_2
)paren
op_logical_and
(paren
id|args-&gt;taskfile.feature
op_eq
id|SETFEATURES_XFER
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;channel-&gt;udma_four
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Speed warnings UDMA 3/4/5 is not functional.&bslash;n&quot;
comma
id|drive-&gt;channel-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_IDEDMA_IVB
r_if
c_cond
(paren
(paren
id|drive-&gt;id-&gt;hw_config
op_amp
l_int|0x6000
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#else
r_if
c_cond
(paren
(paren
(paren
id|drive-&gt;id-&gt;hw_config
op_amp
l_int|0x2000
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
(paren
id|drive-&gt;id-&gt;hw_config
op_amp
l_int|0x4000
)paren
op_eq
l_int|0
)paren
)paren
(brace
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;%s: Speed warnings UDMA 3/4/5 is not functional.&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Backside of HDIO_DRIVE_CMD call of SETFEATURES_XFER.&n; * 1 : Safe to update drive-&gt;id DMA registers.&n; * 0 : OOPs not allowed.&n; */
DECL|function|set_transfer
r_int
id|set_transfer
(paren
id|ide_drive_t
op_star
id|drive
comma
r_struct
id|ata_taskfile
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
(paren
id|args-&gt;taskfile.command
op_eq
id|WIN_SETFEATURES
)paren
op_logical_and
(paren
id|args-&gt;taskfile.sector_number
op_ge
id|XFER_SW_DMA_0
)paren
op_logical_and
(paren
id|args-&gt;taskfile.feature
op_eq
id|SETFEATURES_XFER
)paren
op_logical_and
(paren
id|drive-&gt;id-&gt;dma_ultra
op_logical_or
id|drive-&gt;id-&gt;dma_mword
op_logical_or
id|drive-&gt;id-&gt;dma_1word
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  All hosts that use the 80c ribbon mus use!&n; */
DECL|function|eighty_ninty_three
id|byte
id|eighty_ninty_three
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_return
(paren
(paren
id|byte
)paren
(paren
(paren
id|drive-&gt;channel-&gt;udma_four
)paren
op_logical_and
macro_line|#ifndef CONFIG_IDEDMA_IVB
(paren
id|drive-&gt;id-&gt;hw_config
op_amp
l_int|0x4000
)paren
op_logical_and
macro_line|#endif
(paren
id|drive-&gt;id-&gt;hw_config
op_amp
l_int|0x6000
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Similar to ide_wait_stat(), except it never calls ide_error internally.&n; * This is a kludge to handle the new ide_config_drive_speed() function,&n; * and should not otherwise be used anywhere.  Eventually, the tuneproc&squot;s&n; * should be updated to return ide_startstop_t, in which case we can get&n; * rid of this abomination again.  :)   -ml&n; *&n; * It is gone..........&n; *&n; * const char *msg == consider adding for verbose errors.&n; */
DECL|function|ide_config_drive_speed
r_int
id|ide_config_drive_speed
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|speed
)paren
(brace
r_struct
id|ata_channel
op_star
id|hwif
op_assign
id|drive-&gt;channel
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|error
op_assign
l_int|1
suffix:semicolon
id|byte
id|stat
suffix:semicolon
macro_line|#if defined(CONFIG_BLK_DEV_IDEDMA) &amp;&amp; !defined(CONFIG_DMA_NONPCI)
id|byte
id|unit
op_assign
(paren
id|drive-&gt;select.b.unit
op_amp
l_int|0x01
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
(paren
l_int|5
op_plus
id|unit
)paren
)paren
comma
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
macro_line|#endif /* (CONFIG_BLK_DEV_IDEDMA) &amp;&amp; !(CONFIG_DMA_NONPCI) */
multiline_comment|/*&n;&t; * Don&squot;t use ide_wait_cmd here - it will&n;&t; * attempt to set_geometry and recalibrate,&n;&t; * but for some reason these don&squot;t work at&n;&t; * this point (lost interrupt).&n;&t; */
multiline_comment|/*&n;         * Select the drive, and issue the SETFEATURES command&n;         */
id|disable_irq
c_func
(paren
id|hwif-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* disable_irq_nosync ?? */
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|SELECT_DRIVE
c_func
(paren
id|drive-&gt;channel
comma
id|drive
)paren
suffix:semicolon
id|SELECT_MASK
c_func
(paren
id|drive-&gt;channel
comma
id|drive
comma
l_int|0
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IDE_CONTROL_REG
)paren
id|OUT_BYTE
c_func
(paren
id|drive-&gt;ctl
op_or
l_int|2
comma
id|IDE_CONTROL_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|speed
comma
id|IDE_NSECTOR_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|SETFEATURES_XFER
comma
id|IDE_FEATURE_REG
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|WIN_SETFEATURES
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|IDE_CONTROL_REG
)paren
op_logical_and
(paren
id|drive-&gt;quirk_list
op_eq
l_int|2
)paren
)paren
id|OUT_BYTE
c_func
(paren
id|drive-&gt;ctl
comma
id|IDE_CONTROL_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wait for drive to become non-BUSY&n;&t; */
r_if
c_cond
(paren
(paren
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
)paren
op_amp
id|BUSY_STAT
)paren
(brace
r_int
r_int
id|flags
comma
id|timeout
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|ide__sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* local CPU only -- for jiffies */
id|timeout
op_assign
id|jiffies
op_plus
id|WAIT_CMD
suffix:semicolon
r_while
c_loop
(paren
(paren
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
)paren
op_amp
id|BUSY_STAT
)paren
(brace
r_if
c_cond
(paren
l_int|0
OL
(paren
r_int
r_int
)paren
(paren
id|jiffies
op_minus
id|timeout
)paren
)paren
r_break
suffix:semicolon
)brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
)brace
multiline_comment|/*&n;&t; * Allow status to settle, then read it again.&n;&t; * A few rare drives vastly violate the 400ns spec here,&n;&t; * so we&squot;ll wait up to 10usec for a &quot;good&quot; status&n;&t; * rather than expensively fail things immediately.&n;&t; * This fix courtesy of Matthew Faupel &amp; Niccolo Rigacci.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|OK_STAT
c_func
(paren
(paren
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
)paren
comma
id|DRIVE_READY
comma
id|BUSY_STAT
op_or
id|DRQ_STAT
op_or
id|ERR_STAT
)paren
)paren
(brace
id|error
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|SELECT_MASK
c_func
(paren
id|drive-&gt;channel
comma
id|drive
comma
l_int|0
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|hwif-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|ide_dump_status
c_func
(paren
id|drive
comma
l_string|&quot;set_drive_speed_status&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|drive-&gt;id-&gt;dma_ultra
op_and_assign
op_complement
l_int|0xFF00
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
macro_line|#if defined(CONFIG_BLK_DEV_IDEDMA) &amp;&amp; !defined(CONFIG_DMA_NONPCI)
r_if
c_cond
(paren
id|speed
OG
id|XFER_PIO_4
)paren
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
op_or
(paren
l_int|1
op_lshift
(paren
l_int|5
op_plus
id|unit
)paren
)paren
comma
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
(paren
l_int|5
op_plus
id|unit
)paren
)paren
comma
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
)brace
macro_line|#endif /* (CONFIG_BLK_DEV_IDEDMA) &amp;&amp; !(CONFIG_DMA_NONPCI) */
r_switch
c_cond
(paren
id|speed
)paren
(brace
r_case
id|XFER_UDMA_7
suffix:colon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x8080
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_6
suffix:colon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x4040
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_5
suffix:colon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x2020
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_4
suffix:colon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x1010
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_3
suffix:colon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x0808
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_2
suffix:colon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x0404
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_1
suffix:colon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x0202
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_UDMA_0
suffix:colon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x0101
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_2
suffix:colon
id|drive-&gt;id-&gt;dma_mword
op_or_assign
l_int|0x0404
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_1
suffix:colon
id|drive-&gt;id-&gt;dma_mword
op_or_assign
l_int|0x0202
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MW_DMA_0
suffix:colon
id|drive-&gt;id-&gt;dma_mword
op_or_assign
l_int|0x0101
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_SW_DMA_2
suffix:colon
id|drive-&gt;id-&gt;dma_1word
op_or_assign
l_int|0x0404
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_SW_DMA_1
suffix:colon
id|drive-&gt;id-&gt;dma_1word
op_or_assign
l_int|0x0202
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_SW_DMA_0
suffix:colon
id|drive-&gt;id-&gt;dma_1word
op_or_assign
l_int|0x0101
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|variable|ide_auto_reduce_xfer
id|EXPORT_SYMBOL
c_func
(paren
id|ide_auto_reduce_xfer
)paren
suffix:semicolon
DECL|variable|ide_driveid_update
id|EXPORT_SYMBOL
c_func
(paren
id|ide_driveid_update
)paren
suffix:semicolon
DECL|variable|ide_ata66_check
id|EXPORT_SYMBOL
c_func
(paren
id|ide_ata66_check
)paren
suffix:semicolon
DECL|variable|set_transfer
id|EXPORT_SYMBOL
c_func
(paren
id|set_transfer
)paren
suffix:semicolon
DECL|variable|eighty_ninty_three
id|EXPORT_SYMBOL
c_func
(paren
id|eighty_ninty_three
)paren
suffix:semicolon
DECL|variable|ide_config_drive_speed
id|EXPORT_SYMBOL
c_func
(paren
id|ide_config_drive_speed
)paren
suffix:semicolon
eof
