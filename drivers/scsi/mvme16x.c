multiline_comment|/*&n; * Detection routine for the NCR53c710 based MVME16x SCSI Controllers for Linux.&n; *&n; * Based on work by Alan Hourihane&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mvme16xhw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;53c7xx.h&quot;
macro_line|#include &quot;mvme16x.h&quot;
macro_line|#include&lt;linux/stat.h&gt;
DECL|function|mvme16x_scsi_detect
r_int
id|mvme16x_scsi_detect
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
r_int
id|clock
suffix:semicolon
r_int
r_int
id|options
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MVME16x
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mvme16x_config
op_amp
id|MVME16x_CONFIG_NO_SCSICHIP
)paren
(brace
id|printk
(paren
l_string|&quot;SCSI detection disabled, SCSI chip not present&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|called
)paren
r_return
l_int|0
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;MVME16x&quot;
suffix:semicolon
id|options
op_assign
id|OPTION_MEMORY_MAPPED
op_or
id|OPTION_DEBUG_TEST1
op_or
id|OPTION_INTFLY
op_or
id|OPTION_SYNCHRONOUS
op_or
id|OPTION_ALWAYS_SYNCHRONOUS
op_or
id|OPTION_DISCONNECT
suffix:semicolon
id|clock
op_assign
l_int|66000000
suffix:semicolon
multiline_comment|/* 66MHz SCSI Clock */
id|ncr53c7xx_init
c_func
(paren
id|tpnt
comma
l_int|0
comma
l_int|710
comma
(paren
r_int
r_int
)paren
l_int|0xfff47000
comma
l_int|0
comma
id|MVME16x_IRQ_SCSI
comma
id|DMA_NONE
comma
id|options
comma
id|clock
)paren
suffix:semicolon
id|called
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|mvme16x_scsi_release
r_static
r_int
id|mvme16x_scsi_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_if
c_cond
(paren
id|shost-&gt;irq
)paren
id|free_irq
c_func
(paren
id|shost-&gt;irq
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;dma_channel
op_ne
l_int|0xff
)paren
id|free_dma
c_func
(paren
id|shost-&gt;dma_channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;io_port
op_logical_and
id|shost-&gt;n_io_port
)paren
id|release_region
c_func
(paren
id|shost-&gt;io_port
comma
id|shost-&gt;n_io_port
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|shost
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MVME16x NCR53c710 SCSI&quot;
comma
dot
id|detect
op_assign
id|mvme16x_scsi_detect
comma
dot
id|release
op_assign
id|mvme16x_scsi_release
comma
dot
id|queuecommand
op_assign
id|NCR53c7xx_queue_command
comma
dot
m_abort
op_assign
id|NCR53c7xx_abort
comma
dot
id|reset
op_assign
id|NCR53c7xx_reset
comma
dot
id|can_queue
op_assign
l_int|24
comma
dot
id|this_id
op_assign
l_int|7
comma
dot
id|sg_tablesize
op_assign
l_int|63
comma
dot
id|cmd_per_lun
op_assign
l_int|3
comma
dot
id|use_clustering
op_assign
id|DISABLE_CLUSTERING
)brace
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
