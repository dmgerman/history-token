multiline_comment|/*&n; *  scsi_merge.c Copyright (C) 1999 Eric Youngdale&n; *&n; *  SCSI queueing library.&n; *      Initial versions: Eric Youngdale (eric@andante.org).&n; *                        Based upon conversations with large numbers&n; *                        of people at Linux Expo.&n; *&t;Support for dynamic DMA mapping: Jakub Jelinek (jakub@redhat.com).&n; *&t;Support for highmem I/O: Jens Axboe &lt;axboe@suse.de&gt;&n; */
multiline_comment|/*&n; * This file contains queue management functions that are used by SCSI.&n; * We need to ensure that commands do not grow so large that they cannot&n; * be handled all at once by a host adapter.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
multiline_comment|/*&n; * Function:    scsi_init_io()&n; *&n; * Purpose:     SCSI I/O initialize function.&n; *&n; * Arguments:   SCpnt   - Command descriptor we wish to initialize&n; *&n; * Returns:     1 on success.&n; *&n; * Lock status: &n; */
DECL|function|scsi_init_io
r_int
id|scsi_init_io
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
r_struct
id|request
op_star
id|req
op_assign
id|SCpnt-&gt;request
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sgpnt
suffix:semicolon
r_int
id|count
comma
id|gfp_mask
suffix:semicolon
multiline_comment|/*&n;&t; * First we need to know how many scatter gather segments are needed.&n;&t; */
id|count
op_assign
id|req-&gt;nr_phys_segments
suffix:semicolon
multiline_comment|/*&n;&t; * we used to not use scatter-gather for single segment request,&n;&t; * but now we do (it makes highmem I/O easier to support without&n;&t; * kmapping pages)&n;&t; */
id|SCpnt-&gt;use_sg
op_assign
id|count
suffix:semicolon
id|gfp_mask
op_assign
id|GFP_NOIO
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
id|gfp_mask
op_and_assign
op_complement
id|__GFP_WAIT
suffix:semicolon
id|gfp_mask
op_or_assign
id|__GFP_HIGH
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * if sg table allocation fails, requeue request later.&n;&t; */
id|sgpnt
op_assign
id|scsi_alloc_sgtable
c_func
(paren
id|SCpnt
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgpnt
)paren
r_return
l_int|0
suffix:semicolon
id|SCpnt-&gt;request_buffer
op_assign
(paren
r_char
op_star
)paren
id|sgpnt
suffix:semicolon
id|SCpnt-&gt;request_bufflen
op_assign
id|req-&gt;nr_sectors
op_lshift
l_int|9
suffix:semicolon
id|req-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* &n;&t; * Next, walk the list, and fill in the addresses and sizes of&n;&t; * each segment.&n;&t; */
id|count
op_assign
id|blk_rq_map_sg
c_func
(paren
id|req-&gt;q
comma
id|req
comma
id|SCpnt-&gt;request_buffer
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * mapped well, send it off&n;&t; */
r_if
c_cond
(paren
id|count
op_le
id|SCpnt-&gt;use_sg
)paren
(brace
id|SCpnt-&gt;use_sg
op_assign
id|count
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Incorrect number of segments after building list&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;counted %d, received %d&bslash;n&quot;
comma
id|count
comma
id|SCpnt-&gt;use_sg
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;req nr_sec %lu, cur_nr_sec %u&bslash;n&quot;
comma
id|req-&gt;nr_sectors
comma
id|req-&gt;current_nr_sectors
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * kill it. there should be no leftover blocks in this request&n;&t; */
id|SCpnt
op_assign
id|scsi_end_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|req-&gt;nr_sectors
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function:    scsi_initialize_merge_fn()&n; *&n; * Purpose:     Initialize merge function for a host&n; *&n; * Arguments:   SHpnt   - Host descriptor.&n; *&n; * Returns:     Nothing.&n; *&n; * Lock status: &n; *&n; * Notes:&n; */
DECL|function|scsi_initialize_merge_fn
r_void
id|scsi_initialize_merge_fn
c_func
(paren
id|Scsi_Device
op_star
id|SDpnt
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|SHpnt
op_assign
id|SDpnt-&gt;host
suffix:semicolon
id|request_queue_t
op_star
id|q
op_assign
op_amp
id|SDpnt-&gt;request_queue
suffix:semicolon
id|u64
id|bounce_limit
suffix:semicolon
multiline_comment|/*&n;&t; * The generic merging functions work just fine for us.&n;&t; * Enable highmem I/O, if appropriate.&n;&t; */
id|bounce_limit
op_assign
id|BLK_BOUNCE_HIGH
suffix:semicolon
r_if
c_cond
(paren
id|SHpnt-&gt;highmem_io
op_logical_and
(paren
id|SDpnt-&gt;type
op_eq
id|TYPE_DISK
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PCI_DMA_BUS_IS_PHYS
)paren
multiline_comment|/* Platforms with virtual-DMA translation&n; &t;&t;&t; * hardware have no practical limit.&n;&t;&t;&t; */
id|bounce_limit
op_assign
id|BLK_BOUNCE_ANY
suffix:semicolon
r_else
r_if
c_cond
(paren
id|SHpnt-&gt;pci_dev
)paren
id|bounce_limit
op_assign
id|SHpnt-&gt;pci_dev-&gt;dma_mask
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|SHpnt-&gt;unchecked_isa_dma
)paren
id|bounce_limit
op_assign
id|BLK_BOUNCE_ISA
suffix:semicolon
id|blk_queue_bounce_limit
c_func
(paren
id|q
comma
id|bounce_limit
)paren
suffix:semicolon
)brace
eof
