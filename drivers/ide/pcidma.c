multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; *  Copyright (C) 2002&t;     Marcin Dalecki &lt;martin@dalecki.de&gt;&n; *&n; *  Based on previous work by:&n; *&n; *  Copyright (c) 1999-2000  Andre Hedrick &lt;andre@linux-ide.org&gt;&n; *  Copyright (c) 1995-1998  Mark Lord&n; *&n; *  May be copied or modified under the terms of the GNU General Public License&n; */
multiline_comment|/*&n; * Those are the generic BM DMA support functions for PCI bus based systems.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|DEFAULT_BMIBA
mdefine_line|#define DEFAULT_BMIBA&t;0xe800&t;/* in case BIOS did not init it */
DECL|macro|DEFAULT_BMCRBA
mdefine_line|#define DEFAULT_BMCRBA&t;0xcc00&t;/* VIA&squot;s default value */
DECL|macro|DEFAULT_BMALIBA
mdefine_line|#define DEFAULT_BMALIBA&t;0xd400&t;/* ALI&squot;s default value */
multiline_comment|/*&n; * This is the handler for disk read/write DMA interrupts.&n; */
DECL|function|ide_dma_intr
id|ide_startstop_t
id|ide_dma_intr
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
id|u8
id|dma_stat
suffix:semicolon
id|dma_stat
op_assign
id|udma_stop
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ata_status
c_func
(paren
id|drive
comma
id|DRIVE_READY
comma
id|drive-&gt;bad_wstat
op_or
id|DRQ_STAT
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dma_stat
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
multiline_comment|/* FIXME: this locking should encompass the above register&n;&t;&t;&t; * file access too.&n;&t;&t;&t; */
id|spin_lock_irqsave
c_func
(paren
id|ch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|__ata_end_request
c_func
(paren
id|drive
comma
id|rq
comma
l_int|1
comma
id|rq-&gt;nr_sectors
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|ch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: dma_intr: bad DMA status (dma_stat=%x)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|dma_stat
)paren
suffix:semicolon
)brace
r_return
id|ata_error
c_func
(paren
id|drive
comma
id|rq
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME: taskfiles should be a map of pages, not a long virt address... /jens&n; * FIXME: I agree with Jens --mdcki!&n; */
DECL|function|build_sglist
r_static
r_int
id|build_sglist
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
r_struct
id|scatterlist
op_star
id|sg
op_assign
id|ch-&gt;sg_table
suffix:semicolon
r_int
id|nents
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rq-&gt;flags
op_amp
id|REQ_SPECIAL
)paren
op_logical_and
(paren
id|drive-&gt;type
op_eq
id|ATA_DISK
)paren
)paren
(brace
r_struct
id|ata_taskfile
op_star
id|args
op_assign
id|rq-&gt;special
suffix:semicolon
macro_line|#if 1
r_int
r_char
op_star
id|virt_addr
op_assign
id|rq-&gt;buffer
suffix:semicolon
r_int
id|sector_count
op_assign
id|rq-&gt;nr_sectors
suffix:semicolon
macro_line|#else
id|nents
op_assign
id|blk_rq_map_sg
c_func
(paren
op_amp
id|drive-&gt;queue
comma
id|rq
comma
id|ch-&gt;sg_table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nents
OG
id|rq-&gt;nr_segments
)paren
id|printk
c_func
(paren
l_string|&quot;ide-dma: received %d segments, build %d&bslash;n&quot;
comma
id|rq-&gt;nr_segments
comma
id|nents
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|args-&gt;command_type
op_eq
id|IDE_DRIVE_TASK_RAW_WRITE
)paren
id|ch-&gt;sg_dma_direction
op_assign
id|PCI_DMA_TODEVICE
suffix:semicolon
r_else
id|ch-&gt;sg_dma_direction
op_assign
id|PCI_DMA_FROMDEVICE
suffix:semicolon
multiline_comment|/*&n;&t;&t; * FIXME: This depends upon a hard coded page size!&n;&t;&t; */
r_if
c_cond
(paren
id|sector_count
OG
l_int|128
)paren
(brace
id|memset
c_func
(paren
op_amp
id|sg
(braket
id|nents
)braket
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sg
)paren
)paren
suffix:semicolon
id|sg
(braket
id|nents
)braket
dot
id|page
op_assign
id|virt_to_page
c_func
(paren
id|virt_addr
)paren
suffix:semicolon
id|sg
(braket
id|nents
)braket
dot
id|offset
op_assign
(paren
r_int
r_int
)paren
id|virt_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|sg
(braket
id|nents
)braket
dot
id|length
op_assign
l_int|128
op_star
id|SECTOR_SIZE
suffix:semicolon
op_increment
id|nents
suffix:semicolon
id|virt_addr
op_assign
id|virt_addr
op_plus
(paren
l_int|128
op_star
id|SECTOR_SIZE
)paren
suffix:semicolon
id|sector_count
op_sub_assign
l_int|128
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|sg
(braket
id|nents
)braket
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sg
)paren
)paren
suffix:semicolon
id|sg
(braket
id|nents
)braket
dot
id|page
op_assign
id|virt_to_page
c_func
(paren
id|virt_addr
)paren
suffix:semicolon
id|sg
(braket
id|nents
)braket
dot
id|offset
op_assign
(paren
r_int
r_int
)paren
id|virt_addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|sg
(braket
id|nents
)braket
dot
id|length
op_assign
id|sector_count
op_star
id|SECTOR_SIZE
suffix:semicolon
op_increment
id|nents
suffix:semicolon
)brace
r_else
(brace
id|nents
op_assign
id|blk_rq_map_sg
c_func
(paren
op_amp
id|drive-&gt;queue
comma
id|rq
comma
id|ch-&gt;sg_table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;q
op_logical_and
id|nents
OG
id|rq-&gt;nr_phys_segments
)paren
id|printk
c_func
(paren
l_string|&quot;ide-dma: received %d phys segments, build %d&bslash;n&quot;
comma
id|rq-&gt;nr_phys_segments
comma
id|nents
)paren
suffix:semicolon
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
id|ch-&gt;sg_dma_direction
op_assign
id|PCI_DMA_FROMDEVICE
suffix:semicolon
r_else
id|ch-&gt;sg_dma_direction
op_assign
id|PCI_DMA_TODEVICE
suffix:semicolon
)brace
r_return
id|pci_map_sg
c_func
(paren
id|ch-&gt;pci_dev
comma
id|sg
comma
id|nents
comma
id|ch-&gt;sg_dma_direction
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * 1 dma-ing, 2 error, 4 intr&n; */
DECL|function|dma_timer_expiry
r_static
r_int
id|dma_timer_expiry
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
multiline_comment|/* FIXME: What&squot;s that? */
id|u8
id|dma_stat
op_assign
id|inb
c_func
(paren
id|drive-&gt;channel-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: dma_timer_expiry: dma status == 0x%02x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|dma_stat
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if 0
id|drive-&gt;expiry
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* one free ride for now */
macro_line|#endif
r_if
c_cond
(paren
id|dma_stat
op_amp
l_int|2
)paren
(brace
multiline_comment|/* ERROR */
id|ata_status
c_func
(paren
id|drive
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ata_error
c_func
(paren
id|drive
comma
id|rq
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dma_stat
op_amp
l_int|1
)paren
multiline_comment|/* DMAing */
r_return
id|WAIT_CMD
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ata_start_dma
r_int
id|ata_start_dma
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
id|reading
op_assign
l_int|0
suffix:semicolon
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
id|reading
op_assign
l_int|1
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* try PIO instead of DMA */
r_if
c_cond
(paren
op_logical_neg
id|udma_new_table
c_func
(paren
id|drive
comma
id|rq
)paren
)paren
r_return
l_int|1
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
id|reading
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Configure a device for DMA operation.&n; */
DECL|function|udma_pci_setup
r_int
id|udma_pci_setup
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_int
id|config_allows_dma
op_assign
l_int|1
suffix:semicolon
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
macro_line|#ifdef CONFIG_IDEDMA_ONLYDISK
r_if
c_cond
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
id|config_allows_dma
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
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
id|ch-&gt;autodma
op_logical_and
id|config_allows_dma
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
id|udma_enable
c_func
(paren
id|drive
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Enable DMA on any drive that has UltraDMA (mode 6/7/?) enabled */
r_if
c_cond
(paren
(paren
id|id-&gt;field_valid
op_amp
l_int|4
)paren
op_logical_and
(paren
id|eighty_ninty_three
c_func
(paren
id|drive
)paren
)paren
)paren
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
(paren
id|id-&gt;dma_ultra
op_rshift
l_int|14
)paren
op_amp
l_int|2
)paren
)paren
(brace
id|udma_enable
c_func
(paren
id|drive
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Enable DMA on any drive that has UltraDMA (mode 3/4/5) enabled */
r_if
c_cond
(paren
(paren
id|id-&gt;field_valid
op_amp
l_int|4
)paren
op_logical_and
(paren
id|eighty_ninty_three
c_func
(paren
id|drive
)paren
)paren
)paren
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
(paren
id|id-&gt;dma_ultra
op_rshift
l_int|11
)paren
op_amp
l_int|7
)paren
)paren
(brace
id|udma_enable
c_func
(paren
id|drive
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Enable DMA on any drive that has UltraDMA (mode 0/1/2) enabled */
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|4
)paren
multiline_comment|/* UltraDMA */
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
(paren
id|id-&gt;dma_ultra
op_rshift
l_int|8
)paren
op_amp
l_int|7
)paren
)paren
(brace
id|udma_enable
c_func
(paren
id|drive
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Enable DMA on any drive that has mode2 DMA (multi or single) enabled */
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
multiline_comment|/* regular DMA */
r_if
c_cond
(paren
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x404
)paren
op_eq
l_int|0x404
op_logical_or
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x404
)paren
op_eq
l_int|0x404
)paren
(brace
id|udma_enable
c_func
(paren
id|drive
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Consult the list of known &quot;good&quot; drives */
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
id|udma_enable
c_func
(paren
id|drive
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|udma_enable
c_func
(paren
id|drive
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Needed for allowing full modular support of ide-driver&n; */
DECL|function|ide_release_dma
r_void
id|ide_release_dma
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;dma_base
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;dmatable_cpu
)paren
(brace
id|pci_free_consistent
c_func
(paren
id|ch-&gt;pci_dev
comma
id|PRD_ENTRIES
op_star
id|PRD_BYTES
comma
id|ch-&gt;dmatable_cpu
comma
id|ch-&gt;dmatable_dma
)paren
suffix:semicolon
id|ch-&gt;dmatable_cpu
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ch-&gt;sg_table
)paren
(brace
id|kfree
c_func
(paren
id|ch-&gt;sg_table
)paren
suffix:semicolon
id|ch-&gt;sg_table
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ch-&gt;dma_extra
)paren
op_logical_and
(paren
id|ch-&gt;unit
op_eq
l_int|0
)paren
)paren
id|release_region
c_func
(paren
(paren
id|ch-&gt;dma_base
op_plus
l_int|16
)paren
comma
id|ch-&gt;dma_extra
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ch-&gt;dma_base
comma
l_int|8
)paren
suffix:semicolon
id|ch-&gt;dma_base
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; * PCI specific UDMA channel method implementations.&n; */
multiline_comment|/*&n; * This is the generic part of the DMA setup used by the host chipset drivers&n; * in the corresponding DMA setup method.&n; *&n; * FIXME: there are some places where this gets used driectly for &quot;error&n; * recovery&quot; in the ATAPI drivers. This was just plain wrong before, in esp.&n; * not portable, and just got uncovered now.&n; */
DECL|function|udma_pci_enable
r_void
id|udma_pci_enable
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
id|on
comma
r_int
id|verbose
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
id|set_high
op_assign
l_int|1
suffix:semicolon
id|u8
id|unit
suffix:semicolon
id|u64
id|addr
suffix:semicolon
multiline_comment|/* Fall back to the default implementation. */
id|unit
op_assign
(paren
id|drive-&gt;select.b.unit
op_amp
l_int|0x01
)paren
suffix:semicolon
id|addr
op_assign
id|BLK_BOUNCE_HIGH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|on
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
id|printk
c_func
(paren
l_string|&quot;%s: DMA disabled&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
id|set_high
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ch-&gt;dma_base
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
id|ch-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDE_TCQ
id|udma_tcq_enable
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* toggle bounce buffers */
r_if
c_cond
(paren
id|on
op_logical_and
id|drive-&gt;type
op_eq
id|ATA_DISK
op_logical_and
id|drive-&gt;channel-&gt;highmem
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PCI_DMA_BUS_IS_PHYS
)paren
id|addr
op_assign
id|BLK_BOUNCE_ANY
suffix:semicolon
r_else
id|addr
op_assign
id|drive-&gt;channel-&gt;pci_dev-&gt;dma_mask
suffix:semicolon
)brace
id|blk_queue_bounce_limit
c_func
(paren
op_amp
id|drive-&gt;queue
comma
id|addr
)paren
suffix:semicolon
id|drive-&gt;using_dma
op_assign
id|on
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ch-&gt;dma_base
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
id|ch-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDE_TCQ_DEFAULT
id|udma_tcq_enable
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/*&n; * This prepares a dma request.  Returns 0 if all went okay, returns 1&n; * otherwise.  May also be invoked from trm290.c&n; */
DECL|function|udma_new_table
r_int
id|udma_new_table
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
op_star
id|table
op_assign
id|ch-&gt;dmatable_cpu
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_TRM290
r_int
r_int
id|is_trm290_chipset
op_assign
(paren
id|ch-&gt;chipset
op_eq
id|ide_trm290
)paren
suffix:semicolon
macro_line|#else
r_const
r_int
id|is_trm290_chipset
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_int
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
id|ch-&gt;sg_nents
op_assign
id|i
op_assign
id|build_sglist
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_return
l_int|0
suffix:semicolon
id|sg
op_assign
id|ch-&gt;sg_table
suffix:semicolon
r_while
c_loop
(paren
id|i
)paren
(brace
id|u32
id|cur_addr
suffix:semicolon
id|u32
id|cur_len
suffix:semicolon
id|cur_addr
op_assign
id|sg_dma_address
c_func
(paren
id|sg
)paren
suffix:semicolon
id|cur_len
op_assign
id|sg_dma_len
c_func
(paren
id|sg
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Fill in the dma table, without crossing any 64kB boundaries.&n;&t;&t; * Most hardware requires 16-bit alignment of all blocks,&n;&t;&t; * but the trm290 requires 32-bit alignment.&n;&t;&t; */
r_while
c_loop
(paren
id|cur_len
)paren
(brace
id|u32
id|xcount
comma
id|bcount
op_assign
l_int|0x10000
op_minus
(paren
id|cur_addr
op_amp
l_int|0xffff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_increment
op_ge
id|PRD_ENTRIES
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide-dma: count %d, sg_nents %d, cur_len %d, cur_addr %u&bslash;n&quot;
comma
id|count
comma
id|ch-&gt;sg_nents
comma
id|cur_len
comma
id|cur_addr
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bcount
OG
id|cur_len
)paren
id|bcount
op_assign
id|cur_len
suffix:semicolon
op_star
id|table
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|cur_addr
)paren
suffix:semicolon
id|xcount
op_assign
id|bcount
op_amp
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
id|is_trm290_chipset
)paren
id|xcount
op_assign
(paren
(paren
id|xcount
op_rshift
l_int|2
)paren
op_minus
l_int|1
)paren
op_lshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|xcount
op_eq
l_int|0x0000
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Most chipsets correctly interpret a length of&n;&t;&t;&t; * 0x0000 as 64KB, but at least one (e.g. CS5530)&n;&t;&t;&t; * misinterprets it as zero (!). So here we break&n;&t;&t;&t; * the 64KB entry into two 32KB entries instead.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|count
op_increment
op_ge
id|PRD_ENTRIES
)paren
(brace
id|pci_unmap_sg
c_func
(paren
id|ch-&gt;pci_dev
comma
id|sg
comma
id|ch-&gt;sg_nents
comma
id|ch-&gt;sg_dma_direction
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|table
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
l_int|0x8000
)paren
suffix:semicolon
op_star
id|table
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|cur_addr
op_plus
l_int|0x8000
)paren
suffix:semicolon
id|xcount
op_assign
l_int|0x8000
suffix:semicolon
)brace
op_star
id|table
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|xcount
)paren
suffix:semicolon
id|cur_addr
op_add_assign
id|bcount
suffix:semicolon
id|cur_len
op_sub_assign
id|bcount
suffix:semicolon
)brace
id|sg
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: empty DMA table?&bslash;n&quot;
comma
id|ch-&gt;name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|is_trm290_chipset
)paren
op_star
op_decrement
id|table
op_or_assign
id|cpu_to_le32
c_func
(paren
l_int|0x80000000
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Teardown mappings after DMA has completed.&n; *&n; * Channel lock should be held.&n; */
DECL|function|udma_destroy_table
r_void
id|udma_destroy_table
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
)paren
(brace
id|pci_unmap_sg
c_func
(paren
id|ch-&gt;pci_dev
comma
id|ch-&gt;sg_table
comma
id|ch-&gt;sg_nents
comma
id|ch-&gt;sg_dma_direction
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Prepare the channel for a DMA startfer. Please note that only the broken&n; * Pacific Digital host chip needs the reques to be passed there to decide&n; * about addressing modes.&n; *&n; * Channel lock should be held.&n; */
DECL|function|udma_pci_start
r_void
id|udma_pci_start
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
multiline_comment|/* Note that this is done *after* the cmd has been issued to the drive,&n;&t; * as per the BM-IDE spec.  The Promise Ultra33 doesn&squot;t work correctly&n;&t; * when we do this part before issuing the drive cmd.&n;&t; */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|dma_base
)paren
op_or
l_int|1
comma
id|dma_base
)paren
suffix:semicolon
multiline_comment|/* start DMA */
)brace
multiline_comment|/*&n; * Channel lock should be held.&n; */
DECL|function|udma_pci_stop
r_int
id|udma_pci_stop
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
ques
c_cond
(paren
l_int|0x10
op_or
id|dma_stat
)paren
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* verify good DMA status */
)brace
multiline_comment|/*&n; * FIXME: This should be attached to a channel as we can see now!&n; *&n; * Channel lock should be held.&n; */
DECL|function|udma_pci_irq_status
r_int
id|udma_pci_irq_status
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
id|u8
id|dma_stat
suffix:semicolon
multiline_comment|/* default action */
id|dma_stat
op_assign
id|inb
c_func
(paren
id|ch-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
r_return
(paren
id|dma_stat
op_amp
l_int|4
)paren
op_eq
l_int|4
suffix:semicolon
multiline_comment|/* return 1 if INTR asserted */
)brace
DECL|function|udma_pci_timeout
r_void
id|udma_pci_timeout
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ATA: UDMA timeout occured %s!&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|udma_pci_irq_lost
r_void
id|udma_pci_irq_lost
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
)brace
multiline_comment|/*&n; * This can be called for a dynamically installed interface. Don&squot;t __init it&n; */
DECL|function|ata_init_dma
r_void
id|ata_init_dma
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
comma
r_int
r_int
id|dma_base
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|dma_base
comma
l_int|8
comma
id|ch-&gt;name
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ATA: ERROR: BM DMA portst already in use!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;    %s: BM-DMA at 0x%04lx-0x%04lx&quot;
comma
id|ch-&gt;name
comma
id|dma_base
comma
id|dma_base
op_plus
l_int|7
)paren
suffix:semicolon
id|ch-&gt;dma_base
op_assign
id|dma_base
suffix:semicolon
id|ch-&gt;dmatable_cpu
op_assign
id|pci_alloc_consistent
c_func
(paren
id|ch-&gt;pci_dev
comma
id|PRD_ENTRIES
op_star
id|PRD_BYTES
comma
op_amp
id|ch-&gt;dmatable_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;dmatable_cpu
op_eq
l_int|NULL
)paren
r_goto
id|dma_alloc_failure
suffix:semicolon
id|ch-&gt;sg_table
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|scatterlist
)paren
op_star
id|PRD_ENTRIES
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;sg_table
op_eq
l_int|NULL
)paren
(brace
id|pci_free_consistent
c_func
(paren
id|ch-&gt;pci_dev
comma
id|PRD_ENTRIES
op_star
id|PRD_BYTES
comma
id|ch-&gt;dmatable_cpu
comma
id|ch-&gt;dmatable_dma
)paren
suffix:semicolon
r_goto
id|dma_alloc_failure
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We could just assign them, and then leave it up to the chipset&n;&t; * specific code to override these after they&squot;ve called this function.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;udma_setup
)paren
id|ch-&gt;udma_setup
op_assign
id|udma_pci_setup
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;udma_enable
)paren
id|ch-&gt;udma_enable
op_assign
id|udma_pci_enable
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;udma_start
)paren
id|ch-&gt;udma_start
op_assign
id|udma_pci_start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;udma_stop
)paren
id|ch-&gt;udma_stop
op_assign
id|udma_pci_stop
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;udma_init
)paren
id|ch-&gt;udma_init
op_assign
id|udma_pci_init
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;udma_irq_status
)paren
id|ch-&gt;udma_irq_status
op_assign
id|udma_pci_irq_status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;udma_timeout
)paren
id|ch-&gt;udma_timeout
op_assign
id|udma_pci_timeout
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;udma_irq_lost
)paren
id|ch-&gt;udma_irq_lost
op_assign
id|udma_pci_irq_lost
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;chipset
op_ne
id|ide_trm290
)paren
(brace
id|u8
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
id|printk
c_func
(paren
l_string|&quot;, BIOS settings: %s:%s, %s:%s&quot;
comma
id|ch-&gt;drives
(braket
l_int|0
)braket
dot
id|name
comma
(paren
id|dma_stat
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;DMA&quot;
suffix:colon
l_string|&quot;pio&quot;
comma
id|ch-&gt;drives
(braket
l_int|1
)braket
dot
id|name
comma
(paren
id|dma_stat
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;DMA&quot;
suffix:colon
l_string|&quot;pio&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
id|dma_alloc_failure
suffix:colon
id|printk
c_func
(paren
l_string|&quot; -- ERROR, UNABLE TO ALLOCATE DMA TABLES&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the default read write function.&n; *&n; * It&squot;s exported only for host chips which use it for fallback or (too) late&n; * capability checking.&n; *&n; * Channel lock should be held.&n; */
DECL|function|udma_pci_init
r_int
id|udma_pci_init
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
id|u8
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|ata_start_dma
c_func
(paren
id|drive
comma
id|rq
)paren
)paren
r_return
id|ide_stopped
suffix:semicolon
multiline_comment|/* No DMA transfers on ATAPI devices. */
r_if
c_cond
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
)paren
r_return
id|ide_started
suffix:semicolon
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
l_int|0x08
suffix:semicolon
r_else
id|cmd
op_assign
l_int|0x00
suffix:semicolon
id|ata_set_handler
c_func
(paren
id|drive
comma
id|ide_dma_intr
comma
id|WAIT_CMD
comma
id|dma_timer_expiry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;addressing
)paren
id|outb
c_func
(paren
id|cmd
ques
c_cond
id|WIN_READDMA_EXT
suffix:colon
id|WIN_WRITEDMA_EXT
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|cmd
ques
c_cond
id|WIN_READDMA
suffix:colon
id|WIN_WRITEDMA
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
id|udma_start
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
r_return
id|ide_started
suffix:semicolon
)brace
DECL|variable|ide_dma_intr
id|EXPORT_SYMBOL
c_func
(paren
id|ide_dma_intr
)paren
suffix:semicolon
DECL|variable|udma_pci_enable
id|EXPORT_SYMBOL
c_func
(paren
id|udma_pci_enable
)paren
suffix:semicolon
DECL|variable|udma_pci_start
id|EXPORT_SYMBOL
c_func
(paren
id|udma_pci_start
)paren
suffix:semicolon
DECL|variable|udma_pci_stop
id|EXPORT_SYMBOL
c_func
(paren
id|udma_pci_stop
)paren
suffix:semicolon
DECL|variable|udma_pci_init
id|EXPORT_SYMBOL
c_func
(paren
id|udma_pci_init
)paren
suffix:semicolon
DECL|variable|udma_pci_irq_status
id|EXPORT_SYMBOL
c_func
(paren
id|udma_pci_irq_status
)paren
suffix:semicolon
DECL|variable|udma_pci_timeout
id|EXPORT_SYMBOL
c_func
(paren
id|udma_pci_timeout
)paren
suffix:semicolon
DECL|variable|udma_pci_irq_lost
id|EXPORT_SYMBOL
c_func
(paren
id|udma_pci_irq_lost
)paren
suffix:semicolon
eof
