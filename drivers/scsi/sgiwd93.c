multiline_comment|/*&n; * sgiwd93.c: SGI WD93 scsi driver.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; *&t;&t; 1999 Andrew R. Baker (andrewb@uab.edu)&n; *&t;&t;      - Support for 2nd SCSI controller on Indigo2&n; *&t;&t; 2001 Florian Lohoff (flo@rfc822.org)&n; *&t;&t;      - Delete HPC scatter gather (Read corruption on &n; *&t;&t;        multiple disks)&n; *&t;&t;      - Cleanup wback cache handling&n; * &n; * (In all truth, Jed Schimmel wrote all this code.)&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/sgi/sgi.h&gt;
macro_line|#include &lt;asm/sgi/sgimc.h&gt;
macro_line|#include &lt;asm/sgi/sgihpc.h&gt;
macro_line|#include &lt;asm/sgi/sgint23.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;wd33c93.h&quot;
macro_line|#include &quot;sgiwd93.h&quot;
macro_line|#include &lt;linux/stat.h&gt;
DECL|struct|hpc_chunk
r_struct
id|hpc_chunk
(brace
DECL|member|desc
r_struct
id|hpc_dma_desc
id|desc
suffix:semicolon
DECL|member|_padding
id|u32
id|_padding
suffix:semicolon
multiline_comment|/* align to quadword boundary */
)brace
suffix:semicolon
DECL|variable|sgiwd93_host
r_struct
id|Scsi_Host
op_star
id|sgiwd93_host
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|sgiwd93_host1
r_struct
id|Scsi_Host
op_star
id|sgiwd93_host1
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Wuff wuff, wuff, wd33c93.c, wuff wuff, object oriented, bow wow. */
multiline_comment|/* XXX woof! */
DECL|function|sgiwd93_intr
r_static
r_void
id|sgiwd93_intr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|dev
op_assign
id|dev_id
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|dev-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|wd33c93_intr
c_func
(paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
id|dev_id
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|dev-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|DEBUG_DMA
macro_line|#undef DEBUG_DMA
r_static
r_inline
DECL|function|fill_hpc_entries
r_void
id|fill_hpc_entries
(paren
r_struct
id|hpc_chunk
op_star
op_star
id|hcp
comma
r_char
op_star
id|addr
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|physaddr
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
id|physaddr
op_assign
id|PHYSADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
multiline_comment|/*&n;&t;&t; * even cntinfo could be up to 16383, without&n;&t;&t; * magic only 8192 works correctly&n;&t;&t; */
id|count
op_assign
id|len
OG
l_int|8192
ques
c_cond
l_int|8192
suffix:colon
id|len
suffix:semicolon
(paren
op_star
id|hcp
)paren
op_member_access_from_pointer
id|desc.pbuf
op_assign
id|physaddr
suffix:semicolon
(paren
op_star
id|hcp
)paren
op_member_access_from_pointer
id|desc.cntinfo
op_assign
id|count
suffix:semicolon
(paren
op_star
id|hcp
)paren
op_increment
suffix:semicolon
id|len
op_sub_assign
id|count
suffix:semicolon
id|physaddr
op_add_assign
id|count
suffix:semicolon
)brace
)brace
DECL|function|dma_setup
r_static
r_int
id|dma_setup
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
id|datainp
)paren
(brace
r_struct
id|WD33C93_hostdata
op_star
id|hdata
op_assign
(paren
r_struct
id|WD33C93_hostdata
op_star
)paren
id|cmd-&gt;host-&gt;hostdata
suffix:semicolon
r_struct
id|hpc3_scsiregs
op_star
id|hregs
op_assign
(paren
r_struct
id|hpc3_scsiregs
op_star
)paren
id|cmd-&gt;host-&gt;base
suffix:semicolon
r_struct
id|hpc_chunk
op_star
id|hcp
op_assign
(paren
r_struct
id|hpc_chunk
op_star
)paren
id|hdata-&gt;dma_bounce_buffer
suffix:semicolon
macro_line|#ifdef DEBUG_DMA
id|printk
c_func
(paren
l_string|&quot;dma_setup: datainp&lt;%d&gt; hcp&lt;%p&gt; &quot;
comma
id|datainp
comma
id|hcp
)paren
suffix:semicolon
macro_line|#endif
id|hdata-&gt;dma_dir
op_assign
id|datainp
suffix:semicolon
multiline_comment|/*&n;&t; * wd33c93 shouldn&squot;t pass us bogus dma_setups, but&n;&t; * it does:-( The other wd33c93 drivers deal with&n;&t; * it the same way (which isn&squot;t that obvious).&n;&t; * IMHO a better fix would be, not to do these&n;&t; * dma setups in the first place&n;&t; */
r_if
c_cond
(paren
id|cmd-&gt;SCp.ptr
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
id|fill_hpc_entries
(paren
op_amp
id|hcp
comma
id|cmd-&gt;SCp.ptr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
multiline_comment|/* To make sure, if we trip an HPC bug, that we transfer&n;&t; * every single byte, we tag on an extra zero length dma&n;&t; * descriptor at the end of the chain.&n;&t; */
id|hcp-&gt;desc.pbuf
op_assign
l_int|0
suffix:semicolon
id|hcp-&gt;desc.cntinfo
op_assign
(paren
id|HPCDMA_EOX
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_DMA
id|printk
c_func
(paren
l_string|&quot; HPCGO&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Start up the HPC. */
id|hregs-&gt;ndptr
op_assign
id|PHYSADDR
c_func
(paren
id|hdata-&gt;dma_bounce_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|datainp
)paren
(brace
id|dma_cache_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|cmd-&gt;SCp.ptr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
id|hregs-&gt;ctrl
op_assign
(paren
id|HPC3_SCTRL_ACTIVE
)paren
suffix:semicolon
)brace
r_else
(brace
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|cmd-&gt;SCp.ptr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
id|hregs-&gt;ctrl
op_assign
(paren
id|HPC3_SCTRL_ACTIVE
op_or
id|HPC3_SCTRL_DIR
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dma_stop
r_static
r_void
id|dma_stop
c_func
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
r_struct
id|WD33C93_hostdata
op_star
id|hdata
op_assign
(paren
r_struct
id|WD33C93_hostdata
op_star
)paren
id|instance-&gt;hostdata
suffix:semicolon
r_struct
id|hpc3_scsiregs
op_star
id|hregs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SCpnt
)paren
r_return
suffix:semicolon
id|hregs
op_assign
(paren
r_struct
id|hpc3_scsiregs
op_star
)paren
id|SCpnt-&gt;host-&gt;base
suffix:semicolon
macro_line|#ifdef DEBUG_DMA
id|printk
c_func
(paren
l_string|&quot;dma_stop: status&lt;%d&gt; &quot;
comma
id|status
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* First stop the HPC and flush it&squot;s FIFO. */
r_if
c_cond
(paren
id|hdata-&gt;dma_dir
)paren
(brace
id|hregs-&gt;ctrl
op_or_assign
id|HPC3_SCTRL_FLUSH
suffix:semicolon
r_while
c_loop
(paren
id|hregs-&gt;ctrl
op_amp
id|HPC3_SCTRL_ACTIVE
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|hregs-&gt;ctrl
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG_DMA
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|sgiwd93_reset
r_void
id|sgiwd93_reset
c_func
(paren
r_int
r_int
id|base
)paren
(brace
r_struct
id|hpc3_scsiregs
op_star
id|hregs
op_assign
(paren
r_struct
id|hpc3_scsiregs
op_star
)paren
id|base
suffix:semicolon
id|hregs-&gt;ctrl
op_assign
id|HPC3_SCTRL_CRESET
suffix:semicolon
id|udelay
(paren
l_int|50
)paren
suffix:semicolon
id|hregs-&gt;ctrl
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|init_hpc_chain
r_static
r_inline
r_void
id|init_hpc_chain
c_func
(paren
id|uchar
op_star
id|buf
)paren
(brace
r_struct
id|hpc_chunk
op_star
id|hcp
op_assign
(paren
r_struct
id|hpc_chunk
op_star
)paren
id|buf
suffix:semicolon
r_int
r_int
id|start
comma
id|end
suffix:semicolon
id|start
op_assign
(paren
r_int
r_int
)paren
id|buf
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|hcp-&gt;desc.pnext
op_assign
id|PHYSADDR
c_func
(paren
(paren
id|hcp
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|hcp-&gt;desc.cntinfo
op_assign
id|HPCDMA_EOX
suffix:semicolon
id|hcp
op_increment
suffix:semicolon
id|start
op_add_assign
r_sizeof
(paren
r_struct
id|hpc_chunk
)paren
suffix:semicolon
)brace
suffix:semicolon
id|hcp
op_decrement
suffix:semicolon
id|hcp-&gt;desc.pnext
op_assign
id|PHYSADDR
c_func
(paren
id|buf
)paren
suffix:semicolon
multiline_comment|/* Force flush to memory */
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|buf
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
DECL|function|sgiwd93_detect
r_int
id|__init
id|sgiwd93_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|SGIblows
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
id|hpc3_scsiregs
op_star
id|hregs
op_assign
op_amp
id|hpc3c0-&gt;scsi_chan0
suffix:semicolon
r_struct
id|hpc3_scsiregs
op_star
id|hregs1
op_assign
op_amp
id|hpc3c0-&gt;scsi_chan1
suffix:semicolon
r_struct
id|WD33C93_hostdata
op_star
id|hdata
suffix:semicolon
r_struct
id|WD33C93_hostdata
op_star
id|hdata1
suffix:semicolon
id|wd33c93_regs
id|regs
suffix:semicolon
id|uchar
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|called
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Should bitch on the console about this... */
id|SGIblows-&gt;proc_name
op_assign
l_string|&quot;SGIWD93&quot;
suffix:semicolon
id|sgiwd93_host
op_assign
id|scsi_register
c_func
(paren
id|SGIblows
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
id|sgiwd93_host
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|sgiwd93_host-&gt;base
op_assign
(paren
r_int
r_int
)paren
id|hregs
suffix:semicolon
id|sgiwd93_host-&gt;irq
op_assign
id|SGI_WD93_0_IRQ
suffix:semicolon
id|buf
op_assign
(paren
id|uchar
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sgiwd93: Could not allocate memory for host0 buffer.&bslash;n&quot;
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|sgiwd93_host
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|init_hpc_chain
c_func
(paren
id|buf
)paren
suffix:semicolon
multiline_comment|/* HPC_SCSI_REG0 | 0x03 | KSEG1 */
id|regs.SASR
op_assign
(paren
r_int
r_char
op_star
)paren
id|KSEG1ADDR
(paren
l_int|0x1fbc0003
)paren
suffix:semicolon
id|regs.SCMD
op_assign
(paren
r_int
r_char
op_star
)paren
id|KSEG1ADDR
(paren
l_int|0x1fbc0007
)paren
suffix:semicolon
id|wd33c93_init
c_func
(paren
id|sgiwd93_host
comma
id|regs
comma
id|dma_setup
comma
id|dma_stop
comma
id|WD33C93_FS_16_20
)paren
suffix:semicolon
id|hdata
op_assign
(paren
r_struct
id|WD33C93_hostdata
op_star
)paren
id|sgiwd93_host-&gt;hostdata
suffix:semicolon
id|hdata-&gt;no_sync
op_assign
l_int|0
suffix:semicolon
id|hdata-&gt;dma_bounce_buffer
op_assign
(paren
id|uchar
op_star
)paren
(paren
id|KSEG1ADDR
c_func
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|SGI_WD93_0_IRQ
comma
id|sgiwd93_intr
comma
l_int|0
comma
l_string|&quot;SGI WD93&quot;
comma
(paren
r_void
op_star
)paren
id|sgiwd93_host
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sgiwd93: Could not register IRQ %d (for host 0).&bslash;n&quot;
comma
id|SGI_WD93_0_IRQ
)paren
suffix:semicolon
id|wd33c93_release
c_func
(paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buf
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|sgiwd93_host
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* set up second controller on the Indigo2 */
r_if
c_cond
(paren
op_logical_neg
id|sgi_guiness
)paren
(brace
id|sgiwd93_host1
op_assign
id|scsi_register
c_func
(paren
id|SGIblows
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
id|sgiwd93_host1
op_ne
l_int|NULL
)paren
(brace
id|sgiwd93_host1-&gt;base
op_assign
(paren
r_int
r_int
)paren
id|hregs1
suffix:semicolon
id|sgiwd93_host1-&gt;irq
op_assign
id|SGI_WD93_1_IRQ
suffix:semicolon
id|buf
op_assign
(paren
id|uchar
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sgiwd93: Could not allocate memory for host1 buffer.&bslash;n&quot;
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|sgiwd93_host1
)paren
suffix:semicolon
id|called
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* We registered host0 so return success*/
)brace
id|init_hpc_chain
c_func
(paren
id|buf
)paren
suffix:semicolon
multiline_comment|/* HPC_SCSI_REG1 | 0x03 | KSEG1 */
id|regs.SASR
op_assign
(paren
r_int
r_char
op_star
)paren
id|KSEG1ADDR
c_func
(paren
l_int|0x1fbc8003
)paren
suffix:semicolon
id|regs.SCMD
op_assign
(paren
r_int
r_char
op_star
)paren
id|KSEG1ADDR
c_func
(paren
l_int|0x1fbc8007
)paren
suffix:semicolon
id|wd33c93_init
c_func
(paren
id|sgiwd93_host1
comma
id|regs
comma
id|dma_setup
comma
id|dma_stop
comma
id|WD33C93_FS_16_20
)paren
suffix:semicolon
id|hdata1
op_assign
(paren
r_struct
id|WD33C93_hostdata
op_star
)paren
id|sgiwd93_host1-&gt;hostdata
suffix:semicolon
id|hdata1-&gt;no_sync
op_assign
l_int|0
suffix:semicolon
id|hdata1-&gt;dma_bounce_buffer
op_assign
(paren
id|uchar
op_star
)paren
(paren
id|KSEG1ADDR
c_func
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|SGI_WD93_1_IRQ
comma
id|sgiwd93_intr
comma
l_int|0
comma
l_string|&quot;SGI WD93&quot;
comma
(paren
r_void
op_star
)paren
id|sgiwd93_host1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sgiwd93: Could not allocate irq %d (for host1).&bslash;n&quot;
comma
id|SGI_WD93_1_IRQ
)paren
suffix:semicolon
id|wd33c93_release
c_func
(paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buf
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|sgiwd93_host1
)paren
suffix:semicolon
multiline_comment|/* Fall through since host0 registered OK */
)brace
)brace
)brace
id|called
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Found one. */
)brace
DECL|function|sgiwd93_release
r_int
id|sgiwd93_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
id|free_irq
c_func
(paren
id|SGI_WD93_0_IRQ
comma
id|sgiwd93_intr
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|KSEG0ADDR
c_func
(paren
id|hdata-&gt;dma_bounce_buffer
)paren
)paren
suffix:semicolon
id|wd33c93_release
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgi_guiness
)paren
(brace
id|free_irq
c_func
(paren
id|SGI_WD93_1_IRQ
comma
id|sgiwd93_intr
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|KSEG0ADDR
c_func
(paren
id|hdata1-&gt;dma_bounce_buffer
)paren
)paren
suffix:semicolon
id|wd33c93_release
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
(brace
dot
id|proc_name
op_assign
l_string|&quot;SGIWD93&quot;
comma
dot
id|name
op_assign
l_string|&quot;SGI WD93&quot;
comma
dot
id|detect
op_assign
id|sgiwd93_detect
comma
dot
id|release
op_assign
id|sgiwd93_release
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
comma
)brace
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
