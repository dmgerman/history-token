multiline_comment|/*&n; * Detection routine for the NCR53c710 based MVME16x SCSI Controllers for Linux.&n; *&n; * Based on work by Alan Hourihane&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/bvme6000hw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;53c7xx.h&quot;
macro_line|#include &quot;bvme6000.h&quot;
macro_line|#include&lt;linux/stat.h&gt;
r_extern
id|ncr53c7xx_init
(paren
id|Scsi_Host_Template
op_star
id|tpnt
comma
r_int
id|board
comma
r_int
id|chip
comma
id|u32
id|base
comma
r_int
id|io_port
comma
r_int
id|irq
comma
r_int
id|dma
comma
r_int
r_int
id|options
comma
r_int
id|clock
)paren
suffix:semicolon
DECL|function|bvme6000_scsi_detect
r_int
id|bvme6000_scsi_detect
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
id|called
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_BVME6000
)paren
r_return
l_int|0
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;BVME6000&quot;
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
l_int|40000000
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
id|u32
)paren
id|BVME_NCR53C710_BASE
comma
l_int|0
comma
id|BVME_IRQ_SCSI
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
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|BVME6000_SCSI
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
