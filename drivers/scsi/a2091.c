macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;wd33c93.h&quot;
macro_line|#include &quot;a2091.h&quot;
macro_line|#include&lt;linux/stat.h&gt;
DECL|macro|DMA
mdefine_line|#define DMA(ptr) ((a2091_scsiregs *)((ptr)-&gt;base))
DECL|macro|HDATA
mdefine_line|#define HDATA(ptr) ((struct WD33C93_hostdata *)((ptr)-&gt;hostdata))
DECL|variable|first_instance
r_static
r_struct
id|Scsi_Host
op_star
id|first_instance
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|a2091_template
r_static
id|Scsi_Host_Template
op_star
id|a2091_template
suffix:semicolon
DECL|function|a2091_intr
r_static
id|irqreturn_t
id|a2091_intr
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
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|instance
suffix:semicolon
r_int
id|handled
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|instance
op_assign
id|first_instance
suffix:semicolon
id|instance
op_logical_and
id|instance-&gt;hostt
op_eq
id|a2091_template
suffix:semicolon
id|instance
op_assign
id|instance-&gt;next
)paren
(brace
id|status
op_assign
id|DMA
c_func
(paren
id|instance
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
(paren
id|ISTR_INT_F
op_or
id|ISTR_INT_P
)paren
)paren
)paren
r_continue
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
id|instance-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|wd33c93_intr
(paren
id|instance
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|instance-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|handled
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|IRQ_RETVAL
c_func
(paren
id|handled
)paren
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
r_struct
id|Scsi_Host
op_star
id|instance
op_assign
id|cmd-&gt;device-&gt;host
suffix:semicolon
multiline_comment|/* don&squot;t allow DMA if the physical address is bad */
r_if
c_cond
(paren
id|addr
op_amp
id|A2091_XFER_MASK
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
id|instance
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
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
op_assign
id|kmalloc
(paren
id|HDATA
c_func
(paren
id|instance
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
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
)paren
(brace
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
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* get the physical address of the bounce buffer */
id|addr
op_assign
id|virt_to_bus
c_func
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
multiline_comment|/* the bounce buffer may not be in the first 16M of physmem */
r_if
c_cond
(paren
id|addr
op_amp
id|A2091_XFER_MASK
)paren
(brace
multiline_comment|/* we could use chipmem... maybe later */
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
macro_line|#if 0
id|panic
(paren
l_string|&quot;scsi%ddma: incomplete s/g support&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
macro_line|#else
id|memcpy
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|cmd-&gt;SCp.ptr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
macro_line|#endif
r_else
id|memcpy
(paren
id|HDATA
c_func
(paren
id|instance
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
id|cmd-&gt;device-&gt;host
)paren
op_member_access_from_pointer
id|dma_dir
op_assign
id|dir_in
suffix:semicolon
id|DMA
c_func
(paren
id|cmd-&gt;device-&gt;host
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
id|cmd-&gt;device-&gt;host
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
(brace
multiline_comment|/* invalidate any cache */
id|cache_clear
(paren
id|addr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* push any dirty cache */
id|cache_push
(paren
id|addr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
)brace
multiline_comment|/* start DMA */
id|DMA
c_func
(paren
id|cmd-&gt;device-&gt;host
)paren
op_member_access_from_pointer
id|ST_DMA
op_assign
l_int|1
suffix:semicolon
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
multiline_comment|/* disable SCSI interrupts */
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
suffix:semicolon
)brace
multiline_comment|/* clear a possible interrupt */
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
macro_line|#if 0
id|panic
(paren
l_string|&quot;scsi%d: incomplete s/g support&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
macro_line|#else
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
)brace
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
macro_line|#endif
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
DECL|variable|num_a2091
r_static
r_int
id|num_a2091
op_assign
l_int|0
suffix:semicolon
DECL|function|a2091_detect
r_int
id|__init
id|a2091_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_static
r_int
r_char
id|called
op_assign
l_int|0
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|instance
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
r_struct
id|zorro_dev
op_star
id|z
op_assign
l_int|NULL
suffix:semicolon
id|wd33c93_regs
id|regs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_AMIGA
op_logical_or
id|called
)paren
r_return
l_int|0
suffix:semicolon
id|called
op_assign
l_int|1
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;A2091&quot;
suffix:semicolon
id|tpnt-&gt;proc_info
op_assign
op_amp
id|wd33c93_proc_info
suffix:semicolon
r_while
c_loop
(paren
(paren
id|z
op_assign
id|zorro_find_device
c_func
(paren
id|ZORRO_WILDCARD
comma
id|z
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|z-&gt;id
op_ne
id|ZORRO_PROD_CBM_A590_A2091_1
op_logical_and
id|z-&gt;id
op_ne
id|ZORRO_PROD_CBM_A590_A2091_2
)paren
r_continue
suffix:semicolon
id|address
op_assign
id|z-&gt;resource.start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|address
comma
l_int|256
comma
l_string|&quot;wd33c93&quot;
)paren
)paren
r_continue
suffix:semicolon
id|instance
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
id|instance
op_eq
l_int|NULL
)paren
(brace
id|release_mem_region
c_func
(paren
id|address
comma
l_int|256
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|instance-&gt;base
op_assign
id|ZTWO_VADDR
c_func
(paren
id|address
)paren
suffix:semicolon
id|instance-&gt;irq
op_assign
id|IRQ_AMIGA_PORTS
suffix:semicolon
id|instance-&gt;unique_id
op_assign
id|z-&gt;slotaddr
suffix:semicolon
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|DAWR
op_assign
id|DAWR_A2091
suffix:semicolon
id|regs.SASR
op_assign
op_amp
(paren
id|DMA
c_func
(paren
id|instance
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
id|instance
)paren
op_member_access_from_pointer
id|SCMD
)paren
suffix:semicolon
id|wd33c93_init
c_func
(paren
id|instance
comma
id|regs
comma
id|dma_setup
comma
id|dma_stop
comma
id|WD33C93_FS_8_10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_a2091
op_increment
op_eq
l_int|0
)paren
(brace
id|first_instance
op_assign
id|instance
suffix:semicolon
id|a2091_template
op_assign
id|instance-&gt;hostt
suffix:semicolon
id|request_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|a2091_intr
comma
id|SA_SHIRQ
comma
l_string|&quot;A2091 SCSI&quot;
comma
id|a2091_intr
)paren
suffix:semicolon
)brace
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
)brace
r_return
id|num_a2091
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
l_string|&quot;A2901&quot;
comma
dot
id|name
op_assign
l_string|&quot;Commodore A2091/A590 SCSI&quot;
comma
dot
id|detect
op_assign
id|a2091_detect
comma
dot
id|release
op_assign
id|a2091_release
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
id|DISABLE_CLUSTERING
)brace
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
DECL|function|a2091_release
r_int
id|a2091_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
macro_line|#ifdef MODULE
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
id|ZTWO_PADDR
c_func
(paren
id|instance-&gt;base
)paren
comma
l_int|256
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|num_a2091
op_eq
l_int|0
)paren
id|free_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|a2091_intr
)paren
suffix:semicolon
id|wd33c93_release
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
