multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; *  Copyright (C) 2002&t;&t;Marcin Dalecki &lt;martin@dalecki.de&gt;&n; *  Copyright (C) 2000&t;&t;Michael Cornwell &lt;cornwell@acm.org&gt;&n; *  Copyright (C) 2000&t;&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; *&n; *  May be copied or modified under the terms of the GNU General Public License&n; */
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
macro_line|#include &lt;linux/completion.h&gt;
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
DECL|macro|DEBUG_TASKFILE
mdefine_line|#define DEBUG_TASKFILE&t;0&t;/* unset when fixed */
macro_line|#if DEBUG_TASKFILE
DECL|macro|DTF
mdefine_line|#define DTF(x...) printk(##x)
macro_line|#else
DECL|macro|DTF
mdefine_line|#define DTF(x...)
macro_line|#endif
multiline_comment|/*&n; * Data transfer functions for polled IO.&n; */
DECL|function|ata_read_32
r_static
r_void
id|ata_read_32
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
id|insl
c_func
(paren
id|IDE_DATA_REG
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
DECL|function|ata_write_32
r_static
r_void
id|ata_write_32
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
id|outsl
c_func
(paren
id|IDE_DATA_REG
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
macro_line|#if SUPPORT_SLOW_DATA_PORTS
DECL|function|ata_read_slow
r_static
r_void
id|ata_read_slow
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
r_int
r_int
op_star
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|wcount
op_decrement
)paren
(brace
op_star
id|ptr
op_increment
op_assign
id|inw_p
c_func
(paren
id|IDE_DATA_REG
)paren
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|inw_p
c_func
(paren
id|IDE_DATA_REG
)paren
suffix:semicolon
)brace
)brace
DECL|function|ata_write_slow
r_static
r_void
id|ata_write_slow
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
r_int
r_int
op_star
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|wcount
op_decrement
)paren
(brace
id|outw_p
c_func
(paren
op_star
id|ptr
op_increment
comma
id|IDE_DATA_REG
)paren
suffix:semicolon
id|outw_p
c_func
(paren
op_star
id|ptr
op_increment
comma
id|IDE_DATA_REG
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|ata_read_16
r_static
r_void
id|ata_read_16
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
id|insw
c_func
(paren
id|IDE_DATA_REG
comma
id|buffer
comma
id|wcount
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ata_write_16
r_static
r_void
id|ata_write_16
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
id|outsw
c_func
(paren
id|IDE_DATA_REG
comma
id|buffer
comma
id|wcount
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is used for most PIO data transfers *from* the device.&n; */
DECL|function|ata_read
r_void
id|ata_read
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
r_int
id|io_32bit
suffix:semicolon
multiline_comment|/*&n;&t; * First check if this controller has defined a special function&n;&t; * for handling polled ide transfers.&n;&t; */
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;ata_read
)paren
(brace
id|drive-&gt;channel
op_member_access_from_pointer
id|ata_read
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|io_32bit
op_assign
id|drive-&gt;channel-&gt;io_32bit
suffix:semicolon
r_if
c_cond
(paren
id|io_32bit
)paren
(brace
id|ata_read_32
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if SUPPORT_SLOW_DATA_PORTS
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;slow
)paren
id|ata_read_slow
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
r_else
macro_line|#endif
id|ata_read_16
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This is used for most PIO data transfers *to* the device interface.&n; */
DECL|function|ata_write
r_void
id|ata_write
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
r_int
id|io_32bit
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;ata_write
)paren
(brace
id|drive-&gt;channel
op_member_access_from_pointer
id|ata_write
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|io_32bit
op_assign
id|drive-&gt;channel-&gt;io_32bit
suffix:semicolon
r_if
c_cond
(paren
id|io_32bit
)paren
(brace
id|ata_write_32
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if SUPPORT_SLOW_DATA_PORTS
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;slow
)paren
id|ata_write_slow
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
r_else
macro_line|#endif
id|ata_write_16
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Needed for PCI irq sharing&n; */
DECL|function|drive_is_ready
r_int
id|drive_is_ready
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;waiting_for_dma
)paren
r_return
id|udma_irq_status
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Need to guarantee 400ns since last command was issued?&n;&t; */
multiline_comment|/* FIXME: promote this to the general status read method perhaps.&n;&t; */
macro_line|#ifdef CONFIG_IDEPCI_SHARE_IRQ
multiline_comment|/*&n;&t; * We do a passive status test under shared PCI interrupts on&n;&t; * cards that truly share the ATA side interrupt, but may also share&n;&t; * an interrupt with another pci card/device.  We make no assumptions&n;&t; * about possible isa-pnp and pci-pnp issues yet.&n;&t; */
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
id|drive-&gt;status
op_assign
id|GET_ALTSTAT
c_func
(paren
)paren
suffix:semicolon
r_else
macro_line|#endif
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
multiline_comment|/* Note: this may clear a pending IRQ! */
r_if
c_cond
(paren
id|drive-&gt;status
op_amp
id|BUSY_STAT
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* drive busy:  definitely not interrupting */
r_return
l_int|1
suffix:semicolon
multiline_comment|/* drive ready: *might* be interrupting */
)brace
DECL|function|ata_taskfile
id|ide_startstop_t
id|ata_taskfile
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|ata_taskfile
op_star
id|ar
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
multiline_comment|/* (ks/hs): Moved to start, do not use for multiple out commands.&n;&t; * FIXME: why not?! */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ar-&gt;cmd
op_eq
id|CFA_WRITE_MULTI_WO_ERASE
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_MULTWRITE
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_MULTWRITE_EXT
)paren
)paren
(brace
id|ata_irq_enable
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
id|ata_mask
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id-&gt;command_set_2
op_amp
l_int|0x0400
)paren
op_logical_and
(paren
id|id-&gt;cfs_enable_2
op_amp
l_int|0x0400
)paren
op_logical_and
(paren
id|drive-&gt;addressing
op_eq
l_int|1
)paren
)paren
id|ata_out_regfile
c_func
(paren
id|drive
comma
op_amp
id|ar-&gt;hobfile
)paren
suffix:semicolon
id|ata_out_regfile
c_func
(paren
id|drive
comma
op_amp
id|ar-&gt;taskfile
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
(paren
id|ar-&gt;taskfile.device_head
op_amp
(paren
id|drive-&gt;addressing
ques
c_cond
l_int|0xE0
suffix:colon
l_int|0xEF
)paren
)paren
op_or
id|drive-&gt;select.all
comma
id|IDE_SELECT_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ar-&gt;handler
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
multiline_comment|/* This is apparently supposed to reset the wait timeout for&n;&t;&t; * the interrupt to accur.&n;&t;&t; */
multiline_comment|/* FIXME: this locking should encompass the above register&n;&t;&t; * file access too.&n;&t;&t; */
id|spin_lock_irqsave
c_func
(paren
id|ch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|ata_set_handler
c_func
(paren
id|drive
comma
id|ar-&gt;handler
comma
id|WAIT_CMD
comma
l_int|NULL
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|ar-&gt;cmd
comma
id|IDE_COMMAND_REG
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
multiline_comment|/* FIXME: Warning check for race between handler and prehandler&n;&t;&t; * for writing first block of data.  however since we are well&n;&t;&t; * inside the boundaries of the seek, we should be okay.&n;&t;&t; *&n;&t;&t; * FIXME: Replace the switch by using a proper command_type.&n;&t;&t; */
r_if
c_cond
(paren
id|ar-&gt;cmd
op_eq
id|CFA_WRITE_SECT_WO_ERASE
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_WRITE
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_WRITE_EXT
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_WRITE_VERIFY
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_WRITE_BUFFER
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_DOWNLOAD_MICROCODE
op_logical_or
id|ar-&gt;cmd
op_eq
id|CFA_WRITE_MULTI_WO_ERASE
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_MULTWRITE
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_MULTWRITE_EXT
)paren
(brace
id|ide_startstop_t
id|startstop
suffix:semicolon
r_if
c_cond
(paren
id|ata_status_poll
c_func
(paren
id|drive
comma
id|DATA_READY
comma
id|drive-&gt;bad_wstat
comma
id|WAIT_DRQ
comma
id|rq
comma
op_amp
id|startstop
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: no DRQ after issuing %s&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|drive-&gt;mult_count
ques
c_cond
l_string|&quot;MULTWRITE&quot;
suffix:colon
l_string|&quot;WRITE&quot;
)paren
suffix:semicolon
r_return
id|startstop
suffix:semicolon
)brace
multiline_comment|/* FIXME: This doesn&squot;t make the slightest sense.&n;&t;&t;&t; * (ks/hs): Fixed Multi Write&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ar-&gt;cmd
op_eq
id|CFA_WRITE_MULTI_WO_ERASE
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_MULTWRITE
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_MULTWRITE_EXT
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|ide_map_rq
c_func
(paren
id|rq
comma
op_amp
id|flags
)paren
suffix:semicolon
multiline_comment|/* For Write_sectors we need to stuff the first sector */
id|ata_write
c_func
(paren
id|drive
comma
id|buf
comma
id|SECTOR_WORDS
)paren
suffix:semicolon
id|rq-&gt;current_nr_sectors
op_decrement
suffix:semicolon
id|ide_unmap_rq
c_func
(paren
id|rq
comma
id|buf
comma
op_amp
id|flags
)paren
suffix:semicolon
r_return
id|ide_started
suffix:semicolon
)brace
r_else
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Polling wait until the drive is ready.&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * Stuff the first sector(s) by calling the&n;&t;&t;&t;&t; * handler driectly therafter.&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * FIXME: Replace hard-coded 100, what about&n;&t;&t;&t;&t; * error handling?&n;&t;&t;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|100
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|drive_is_ready
c_func
(paren
id|drive
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|drive_is_ready
c_func
(paren
id|drive
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DISASTER WAITING TO HAPPEN!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|ar
op_member_access_from_pointer
id|handler
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * FIXME: This is a gross hack, need to unify tcq dma proc and&n;&t;&t; * regular dma proc. It should now be easier.&n;&t;&t; *&n;&t;&t; * FIXME: Handle the alternateives by a command type.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;using_dma
)paren
r_return
id|ide_started
suffix:semicolon
multiline_comment|/* for dma commands we don&squot;t set the handler */
r_if
c_cond
(paren
id|ar-&gt;cmd
op_eq
id|WIN_WRITEDMA
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_WRITEDMA_EXT
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_READDMA
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_READDMA_EXT
)paren
r_return
op_logical_neg
id|udma_init
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDE_TCQ
r_else
r_if
c_cond
(paren
id|ar-&gt;cmd
op_eq
id|WIN_WRITEDMA_QUEUED
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_WRITEDMA_QUEUED_EXT
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_READDMA_QUEUED
op_logical_or
id|ar-&gt;cmd
op_eq
id|WIN_READDMA_QUEUED_EXT
)paren
r_return
id|udma_tcq_taskfile
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
macro_line|#endif
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unknown command %x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ar-&gt;cmd
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
)brace
r_return
id|ide_started
suffix:semicolon
)brace
multiline_comment|/*&n; * This function issues a special IDE device request onto the request queue.&n; *&n; * If action is ide_wait, then the rq is queued at the end of the request&n; * queue, and the function sleeps until it has been processed.  This is for use&n; * when invoked from an ioctl handler.&n; *&n; * If action is ide_preempt, then the rq is queued at the head of the request&n; * queue, displacing the currently-being-processed request and this function&n; * returns immediately without waiting for the new rq to be completed.  This is&n; * VERY DANGEROUS, and is intended for careful use by the ATAPI tape/cdrom&n; * driver code.&n; *&n; * If action is ide_end, then the rq is queued at the end of the request queue,&n; * and the function returns immediately without waiting for the new rq to be&n; * completed. This is again intended for careful use by the ATAPI tape/cdrom&n; * driver code.&n; */
DECL|function|ide_do_drive_cmd
r_int
id|ide_do_drive_cmd
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
comma
id|ide_action_t
id|action
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|major
op_assign
id|drive-&gt;channel-&gt;major
suffix:semicolon
id|request_queue_t
op_star
id|q
op_assign
op_amp
id|drive-&gt;queue
suffix:semicolon
r_struct
id|list_head
op_star
id|queue_head
op_assign
op_amp
id|q-&gt;queue_head
suffix:semicolon
id|DECLARE_COMPLETION
c_func
(paren
id|wait
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_PDC4030
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;chipset
op_eq
id|ide_pdc4030
op_logical_and
id|rq-&gt;buffer
op_ne
l_int|NULL
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
multiline_comment|/* special drive cmds not supported */
macro_line|#endif
id|rq-&gt;errors
op_assign
l_int|0
suffix:semicolon
id|rq-&gt;rq_status
op_assign
id|RQ_ACTIVE
suffix:semicolon
id|rq-&gt;rq_dev
op_assign
id|mk_kdev
c_func
(paren
id|major
comma
(paren
id|drive-&gt;select.b.unit
)paren
op_lshift
id|PARTN_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|ide_wait
)paren
id|rq-&gt;waiting
op_assign
op_amp
id|wait
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|drive-&gt;channel-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blk_queue_empty
c_func
(paren
op_amp
id|drive-&gt;queue
)paren
op_logical_or
id|action
op_eq
id|ide_preempt
)paren
(brace
r_if
c_cond
(paren
id|action
op_eq
id|ide_preempt
)paren
id|drive-&gt;rq
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|action
op_eq
id|ide_wait
)paren
id|queue_head
op_assign
id|queue_head-&gt;prev
suffix:semicolon
r_else
id|queue_head
op_assign
id|queue_head-&gt;next
suffix:semicolon
)brace
id|q-&gt;elevator
dot
id|elevator_add_req_fn
c_func
(paren
id|q
comma
id|rq
comma
id|queue_head
)paren
suffix:semicolon
id|do_ide_request
c_func
(paren
id|q
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|drive-&gt;channel-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|ide_wait
)paren
(brace
id|wait_for_completion
c_func
(paren
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/* wait for it to be serviced */
r_return
id|rq-&gt;errors
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* return -EIO if errors */
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Invoked on completion of a special REQ_SPECIAL command.&n; */
DECL|function|ata_special_intr
id|ide_startstop_t
id|ata_special_intr
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
id|ata_taskfile
op_star
id|ar
op_assign
id|rq-&gt;special
suffix:semicolon
id|ide_startstop_t
id|ret
op_assign
id|ide_stopped
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|ide__sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|spin_lock_irqsave
c_func
(paren
id|drive-&gt;channel-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;buffer
op_logical_and
id|ar-&gt;taskfile.sector_number
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ata_status
c_func
(paren
id|drive
comma
l_int|0
comma
id|DRQ_STAT
)paren
op_logical_and
id|ar-&gt;taskfile.sector_number
)paren
(brace
r_int
id|retries
op_assign
l_int|10
suffix:semicolon
id|ata_read
c_func
(paren
id|drive
comma
id|rq-&gt;buffer
comma
id|ar-&gt;taskfile.sector_number
op_star
id|SECTOR_WORDS
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|ata_status
c_func
(paren
id|drive
comma
l_int|0
comma
id|BUSY_STAT
)paren
op_logical_and
id|retries
op_decrement
)paren
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|ata_status
c_func
(paren
id|drive
comma
id|READY_STAT
comma
id|BAD_STAT
)paren
)paren
(brace
multiline_comment|/* Keep quiet for NOP because it is expected to fail. */
r_if
c_cond
(paren
id|ar-&gt;cmd
op_ne
id|WIN_NOP
)paren
id|ret
op_assign
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
id|rq-&gt;errors
op_assign
l_int|1
suffix:semicolon
)brace
id|ar-&gt;taskfile.feature
op_assign
id|IN_BYTE
c_func
(paren
id|IDE_ERROR_REG
)paren
suffix:semicolon
id|ata_in_regfile
c_func
(paren
id|drive
comma
op_amp
id|ar-&gt;taskfile
)paren
suffix:semicolon
id|ar-&gt;taskfile.device_head
op_assign
id|IN_BYTE
c_func
(paren
id|IDE_SELECT_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive-&gt;id-&gt;command_set_2
op_amp
l_int|0x0400
)paren
op_logical_and
(paren
id|drive-&gt;id-&gt;cfs_enable_2
op_amp
l_int|0x0400
)paren
op_logical_and
(paren
id|drive-&gt;addressing
op_eq
l_int|1
)paren
)paren
(brace
multiline_comment|/* The following command goes to the hob file! */
id|OUT_BYTE
c_func
(paren
l_int|0x80
comma
id|drive-&gt;channel-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
suffix:semicolon
id|ar-&gt;hobfile.feature
op_assign
id|IN_BYTE
c_func
(paren
id|IDE_FEATURE_REG
)paren
suffix:semicolon
id|ata_in_regfile
c_func
(paren
id|drive
comma
op_amp
id|ar-&gt;hobfile
)paren
suffix:semicolon
)brace
id|blkdev_dequeue_request
c_func
(paren
id|rq
)paren
suffix:semicolon
id|drive-&gt;rq
op_assign
l_int|NULL
suffix:semicolon
id|end_that_request_last
c_func
(paren
id|rq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|drive-&gt;channel-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ide_raw_taskfile
r_int
id|ide_raw_taskfile
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|ata_taskfile
op_star
id|ar
)paren
(brace
r_struct
id|request
id|req
suffix:semicolon
id|ar-&gt;command_type
op_assign
id|IDE_DRIVE_TASK_NO_DATA
suffix:semicolon
id|ar-&gt;handler
op_assign
id|ata_special_intr
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|req
comma
l_int|0
comma
r_sizeof
(paren
id|req
)paren
)paren
suffix:semicolon
id|req.flags
op_assign
id|REQ_SPECIAL
suffix:semicolon
id|req.special
op_assign
id|ar
suffix:semicolon
r_return
id|ide_do_drive_cmd
c_func
(paren
id|drive
comma
op_amp
id|req
comma
id|ide_wait
)paren
suffix:semicolon
)brace
DECL|variable|drive_is_ready
id|EXPORT_SYMBOL
c_func
(paren
id|drive_is_ready
)paren
suffix:semicolon
DECL|variable|ide_do_drive_cmd
id|EXPORT_SYMBOL
c_func
(paren
id|ide_do_drive_cmd
)paren
suffix:semicolon
DECL|variable|ata_read
id|EXPORT_SYMBOL
c_func
(paren
id|ata_read
)paren
suffix:semicolon
DECL|variable|ata_write
id|EXPORT_SYMBOL
c_func
(paren
id|ata_write
)paren
suffix:semicolon
DECL|variable|ata_taskfile
id|EXPORT_SYMBOL
c_func
(paren
id|ata_taskfile
)paren
suffix:semicolon
DECL|variable|ata_special_intr
id|EXPORT_SYMBOL
c_func
(paren
id|ata_special_intr
)paren
suffix:semicolon
DECL|variable|ide_raw_taskfile
id|EXPORT_SYMBOL
c_func
(paren
id|ide_raw_taskfile
)paren
suffix:semicolon
eof
