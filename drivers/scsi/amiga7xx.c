multiline_comment|/*&n; * Detection routine for the NCR53c710 based Amiga SCSI Controllers for Linux.&n; *  &t;&t;Amiga MacroSystemUS WarpEngine SCSI controller.&n; *&t;&t;Amiga Technologies A4000T SCSI controller.&n; *&t;&t;Amiga Technologies/DKB A4091 SCSI controller.&n; *&n; * Written 1997 by Alan Hourihane &lt;alanh@fairlite.demon.co.uk&gt;&n; * plus modifications of the 53c7xx.c driver to support the Amiga.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;53c7xx.h&quot;
macro_line|#include &quot;amiga7xx.h&quot;
macro_line|#include&lt;linux/stat.h&gt;
r_extern
r_int
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
r_int
r_int
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
DECL|function|amiga7xx_detect
r_int
id|__init
id|amiga7xx_detect
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
id|num
op_assign
l_int|0
comma
id|clock
suffix:semicolon
r_int
r_int
id|options
suffix:semicolon
r_struct
id|zorro_dev
op_star
id|z
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
r_if
c_cond
(paren
id|called
op_logical_or
op_logical_neg
id|MACH_IS_AMIGA
)paren
r_return
l_int|0
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;Amiga7xx&quot;
suffix:semicolon
macro_line|#ifdef CONFIG_A4000T_SCSI
r_if
c_cond
(paren
id|AMIGAHW_PRESENT
c_func
(paren
id|A4000_SCSI
)paren
)paren
(brace
id|address
op_assign
l_int|0xdd0040
suffix:semicolon
r_if
c_cond
(paren
id|request_mem_region
c_func
(paren
id|address
comma
l_int|0x1000
comma
l_string|&quot;ncr53c710&quot;
)paren
)paren
(brace
id|address
op_assign
id|ZTWO_VADDR
c_func
(paren
id|address
)paren
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
l_int|50000000
suffix:semicolon
multiline_comment|/* 50MHz SCSI Clock */
id|ncr53c7xx_init
c_func
(paren
id|tpnt
comma
l_int|0
comma
l_int|710
comma
id|address
comma
l_int|0
comma
id|IRQ_AMIGA_PORTS
comma
id|DMA_NONE
comma
id|options
comma
id|clock
)paren
suffix:semicolon
id|num
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif
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
r_int
r_int
id|address
op_assign
id|z-&gt;resource.start
suffix:semicolon
r_int
r_int
id|size
op_assign
id|z-&gt;resource.end
op_minus
id|z-&gt;resource.start
op_plus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|z-&gt;id
)paren
(brace
macro_line|#ifdef CONFIG_BLZ603EPLUS_SCSI
r_case
id|ZORRO_PROD_PHASE5_BLIZZARD_603E_PLUS
suffix:colon
id|address
op_assign
l_int|0xf40000
suffix:semicolon
r_if
c_cond
(paren
id|request_mem_region
c_func
(paren
id|address
comma
l_int|0x1000
comma
l_string|&quot;ncr53c710&quot;
)paren
)paren
(brace
id|address
op_assign
id|ZTWO_VADDR
c_func
(paren
id|address
)paren
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
l_int|50000000
suffix:semicolon
multiline_comment|/* 50MHz SCSI Clock */
id|ncr53c7xx_init
c_func
(paren
id|tpnt
comma
l_int|0
comma
l_int|710
comma
id|address
comma
l_int|0
comma
id|IRQ_AMIGA_PORTS
comma
id|DMA_NONE
comma
id|options
comma
id|clock
)paren
suffix:semicolon
id|num
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_WARPENGINE_SCSI
r_case
id|ZORRO_PROD_MACROSYSTEMS_WARP_ENGINE_40xx
suffix:colon
r_if
c_cond
(paren
id|request_mem_region
c_func
(paren
id|address
op_plus
l_int|0x40000
comma
l_int|0x1000
comma
l_string|&quot;ncr53c710&quot;
)paren
)paren
(brace
id|address
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|address
comma
id|size
)paren
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
l_int|50000000
suffix:semicolon
multiline_comment|/* 50MHz SCSI Clock */
id|ncr53c7xx_init
c_func
(paren
id|tpnt
comma
l_int|0
comma
l_int|710
comma
id|address
op_plus
l_int|0x40000
comma
l_int|0
comma
id|IRQ_AMIGA_PORTS
comma
id|DMA_NONE
comma
id|options
comma
id|clock
)paren
suffix:semicolon
id|num
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_A4091_SCSI
r_case
id|ZORRO_PROD_CBM_A4091_1
suffix:colon
r_case
id|ZORRO_PROD_CBM_A4091_2
suffix:colon
r_if
c_cond
(paren
id|request_mem_region
c_func
(paren
id|address
op_plus
l_int|0x800000
comma
l_int|0x1000
comma
l_string|&quot;ncr53c710&quot;
)paren
)paren
(brace
id|address
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|address
comma
id|size
)paren
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
l_int|50000000
suffix:semicolon
multiline_comment|/* 50MHz SCSI Clock */
id|ncr53c7xx_init
c_func
(paren
id|tpnt
comma
l_int|0
comma
l_int|710
comma
id|address
op_plus
l_int|0x800000
comma
l_int|0
comma
id|IRQ_AMIGA_PORTS
comma
id|DMA_NONE
comma
id|options
comma
id|clock
)paren
suffix:semicolon
id|num
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_GVP_TURBO_SCSI
r_case
id|ZORRO_PROD_GVP_GFORCE_040_060
suffix:colon
r_if
c_cond
(paren
id|request_mem_region
c_func
(paren
id|address
op_plus
l_int|0x40000
comma
l_int|0x1000
comma
l_string|&quot;ncr53c710&quot;
)paren
)paren
(brace
id|address
op_assign
id|ZTWO_VADDR
c_func
(paren
id|address
)paren
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
l_int|50000000
suffix:semicolon
multiline_comment|/* 50MHz SCSI Clock */
id|ncr53c7xx_init
c_func
(paren
id|tpnt
comma
l_int|0
comma
l_int|710
comma
id|address
op_plus
l_int|0x40000
comma
l_int|0
comma
id|IRQ_AMIGA_PORTS
comma
id|DMA_NONE
comma
id|options
comma
id|clock
)paren
suffix:semicolon
id|num
op_increment
suffix:semicolon
)brace
macro_line|#endif
)brace
)brace
id|called
op_assign
l_int|1
suffix:semicolon
r_return
id|num
suffix:semicolon
)brace
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|AMIGA7XX_SCSI
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof
