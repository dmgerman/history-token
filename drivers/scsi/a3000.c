macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;wd33c93.h&quot;
macro_line|#include &quot;a3000.h&quot;
macro_line|#include&lt;linux/stat.h&gt;
DECL|macro|DMA
mdefine_line|#define DMA(ptr) ((a3000_scsiregs *)((ptr)-&gt;base))
DECL|macro|HDATA
mdefine_line|#define HDATA(ptr) ((struct WD33C93_hostdata *)((ptr)-&gt;hostdata))
DECL|variable|a3000_host
r_static
r_struct
id|Scsi_Host
op_star
id|a3000_host
op_assign
l_int|NULL
suffix:semicolon
DECL|function|a3000_intr
r_static
id|irqreturn_t
id|a3000_intr
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|status
op_assign
id|DMA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|ISTR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|ISTR_INT_P
)paren
)paren
r_return
id|IRQ_NONE
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|ISTR_INTS
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|a3000_host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|wd33c93_intr
(paren
id|a3000_host
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|a3000_host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Non-serviced A3000 SCSI-interrupt? ISTR = %02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
DECL|function|dma_setup
r_static
r_int
id|dma_setup
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
id|dir_in
)paren
(brace
r_int
r_int
id|cntr
op_assign
id|CNTR_PDMD
op_or
id|CNTR_INTEN
suffix:semicolon
r_int
r_int
id|addr
op_assign
id|virt_to_bus
c_func
(paren
id|cmd-&gt;SCp.ptr
)paren
suffix:semicolon
multiline_comment|/*&n;     * if the physical address has the wrong alignment, or if&n;     * physical address is bad, or if it is a write and at the&n;     * end of a physical memory chunk, then allocate a bounce&n;     * buffer&n;     */
r_if
c_cond
(paren
id|addr
op_amp
id|A3000_XFER_MASK
op_logical_or
(paren
op_logical_neg
id|dir_in
op_logical_and
id|mm_end_of_chunk
(paren
id|addr
comma
id|cmd-&gt;SCp.this_residual
)paren
)paren
)paren
(brace
id|HDATA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|dma_bounce_len
op_assign
(paren
id|cmd-&gt;SCp.this_residual
op_plus
l_int|511
)paren
op_amp
op_complement
l_int|0x1ff
suffix:semicolon
id|HDATA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
op_assign
id|kmalloc
(paren
id|HDATA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|dma_bounce_len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* can&squot;t allocate memory; use PIO */
r_if
c_cond
(paren
op_logical_neg
id|HDATA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
)paren
(brace
id|HDATA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|dma_bounce_len
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir_in
)paren
(brace
multiline_comment|/* copy to bounce buffer for a write */
r_if
c_cond
(paren
id|cmd-&gt;use_sg
)paren
(brace
id|memcpy
(paren
id|HDATA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|cmd-&gt;SCp.ptr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
)brace
r_else
id|memcpy
(paren
id|HDATA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|cmd-&gt;request_buffer
comma
id|cmd-&gt;request_bufflen
)paren
suffix:semicolon
)brace
id|addr
op_assign
id|virt_to_bus
c_func
(paren
id|HDATA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
)paren
suffix:semicolon
)brace
multiline_comment|/* setup dma direction */
r_if
c_cond
(paren
op_logical_neg
id|dir_in
)paren
id|cntr
op_or_assign
id|CNTR_DDIR
suffix:semicolon
multiline_comment|/* remember direction */
id|HDATA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|dma_dir
op_assign
id|dir_in
suffix:semicolon
id|DMA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|CNTR
op_assign
id|cntr
suffix:semicolon
multiline_comment|/* setup DMA *physical* address */
id|DMA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|ACR
op_assign
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|dir_in
)paren
multiline_comment|/* invalidate any cache */
id|cache_clear
(paren
id|addr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
r_else
multiline_comment|/* push any dirty cache */
id|cache_push
(paren
id|addr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
multiline_comment|/* start DMA */
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* make sure setup is completed */
id|DMA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|ST_DMA
op_assign
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* make sure DMA has started before next IO */
multiline_comment|/* return success */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dma_stop
r_static
r_void
id|dma_stop
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|status
)paren
(brace
multiline_comment|/* disable SCSI interrupts */
r_int
r_int
id|cntr
op_assign
id|CNTR_PDMD
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_dir
)paren
id|cntr
op_or_assign
id|CNTR_DDIR
suffix:semicolon
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|CNTR
op_assign
id|cntr
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* make sure CNTR is updated before next IO */
multiline_comment|/* flush if we were reading */
r_if
c_cond
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_dir
)paren
(brace
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|FLUSH
op_assign
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* don&squot;t allow prefetch */
r_while
c_loop
(paren
op_logical_neg
(paren
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|ISTR
op_amp
id|ISTR_FE_FLG
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* no IO until FLUSH is done */
)brace
multiline_comment|/* clear a possible interrupt */
multiline_comment|/* I think that this CINT is only necessary if you are&n;     * using the terminal count features.   HM 7 Mar 1994&n;     */
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|CINT
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* stop DMA */
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|SP_DMA
op_assign
l_int|1
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* make sure DMA is stopped before next IO */
multiline_comment|/* restore the CONTROL bits (minus the direction flag) */
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|CNTR
op_assign
id|CNTR_PDMD
op_or
id|CNTR_INTEN
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* make sure CNTR is updated before next IO */
multiline_comment|/* copy from a bounce buffer, if necessary */
r_if
c_cond
(paren
id|status
op_logical_and
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
)paren
(brace
r_if
c_cond
(paren
id|SCpnt
op_logical_and
id|SCpnt-&gt;use_sg
)paren
(brace
r_if
c_cond
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_dir
op_logical_and
id|SCpnt
)paren
id|memcpy
(paren
id|SCpnt-&gt;SCp.ptr
comma
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|SCpnt-&gt;SCp.this_residual
)paren
suffix:semicolon
id|kfree
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
)paren
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
op_assign
l_int|NULL
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_dir
op_logical_and
id|SCpnt
)paren
id|memcpy
(paren
id|SCpnt-&gt;request_buffer
comma
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|SCpnt-&gt;request_bufflen
)paren
suffix:semicolon
id|kfree
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
)paren
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
op_assign
l_int|NULL
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|function|a3000_detect
r_int
id|__init
id|a3000_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
id|wd33c93_regs
id|regs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_AMIGA
op_logical_or
op_logical_neg
id|AMIGAHW_PRESENT
c_func
(paren
id|A3000_SCSI
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
l_int|0xDD0000
comma
l_int|256
comma
l_string|&quot;wd33c93&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;A3000&quot;
suffix:semicolon
id|tpnt-&gt;proc_info
op_assign
op_amp
id|wd33c93_proc_info
suffix:semicolon
id|a3000_host
op_assign
id|scsi_register
(paren
id|tpnt
comma
r_sizeof
(paren
r_struct
id|WD33C93_hostdata
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a3000_host
op_eq
l_int|NULL
)paren
r_goto
id|fail_register
suffix:semicolon
id|a3000_host-&gt;base
op_assign
id|ZTWO_VADDR
c_func
(paren
l_int|0xDD0000
)paren
suffix:semicolon
id|a3000_host-&gt;irq
op_assign
id|IRQ_AMIGA_PORTS
suffix:semicolon
id|DMA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|DAWR
op_assign
id|DAWR_A3000
suffix:semicolon
id|regs.SASR
op_assign
op_amp
(paren
id|DMA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|SASR
)paren
suffix:semicolon
id|regs.SCMD
op_assign
op_amp
(paren
id|DMA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|SCMD
)paren
suffix:semicolon
id|wd33c93_init
c_func
(paren
id|a3000_host
comma
id|regs
comma
id|dma_setup
comma
id|dma_stop
comma
id|WD33C93_FS_12_15
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|a3000_intr
comma
id|SA_SHIRQ
comma
l_string|&quot;A3000 SCSI&quot;
comma
id|a3000_intr
)paren
)paren
r_goto
id|fail_irq
suffix:semicolon
id|DMA
c_func
(paren
id|a3000_host
)paren
op_member_access_from_pointer
id|CNTR
op_assign
id|CNTR_PDMD
op_or
id|CNTR_INTEN
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|fail_irq
suffix:colon
id|wd33c93_release
c_func
(paren
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|a3000_host
)paren
suffix:semicolon
id|fail_register
suffix:colon
id|release_mem_region
c_func
(paren
l_int|0xDD0000
comma
l_int|256
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|HOSTS_C
mdefine_line|#define HOSTS_C
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
(brace
dot
id|proc_name
op_assign
l_string|&quot;A3000&quot;
comma
dot
id|name
op_assign
l_string|&quot;Amiga 3000 built-in SCSI&quot;
comma
dot
id|detect
op_assign
id|a3000_detect
comma
dot
id|release
op_assign
id|a3000_release
comma
dot
id|queuecommand
op_assign
id|wd33c93_queuecommand
comma
dot
m_abort
op_assign
id|wd33c93_abort
comma
dot
id|reset
op_assign
id|wd33c93_reset
comma
dot
id|can_queue
op_assign
id|CAN_QUEUE
comma
dot
id|this_id
op_assign
l_int|7
comma
dot
id|sg_tablesize
op_assign
id|SG_ALL
comma
dot
id|cmd_per_lun
op_assign
id|CMD_PER_LUN
comma
dot
id|use_clustering
op_assign
id|ENABLE_CLUSTERING
)brace
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
DECL|function|a3000_release
r_int
id|a3000_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
id|wd33c93_release
c_func
(paren
)paren
suffix:semicolon
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|CNTR
op_assign
l_int|0
suffix:semicolon
id|release_mem_region
c_func
(paren
l_int|0xDD0000
comma
l_int|256
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|a3000_intr
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
