multiline_comment|/* $Id: cf-enabler.c,v 1.8 2001/07/18 12:32:21 gniibe Exp $&n; *&n; *  linux/drivers/block/cf-enabler.c&n; *&n; *  Copyright (C) 1999  Niibe Yutaka&n; *  Copyright (C) 2000  Toshiharu Nozawa&n; *  Copyright (C) 2001  A&amp;D Co., Ltd.&n; *&n; *  Enable the CF configuration.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * You can connect Compact Flash directly to the bus of SuperH.&n; * This is the enabler for that.&n; *&n; * SIM: How generic is this really? It looks pretty board, or at&n; * least SH sub-type, specific to me.&n; * I know it doesn&squot;t work on the Overdrive!&n; */
multiline_comment|/*&n; * 0xB8000000 : Attribute&n; * 0xB8001000 : Common Memory&n; * 0xBA000000 : I/O&n; */
macro_line|#if defined(CONFIG_IDE) &amp;&amp; defined(__SH4__)
multiline_comment|/* SH4 can&squot;t access PCMCIA interface through P2 area.&n; * we must remap it with appropreate attribute bit of the page set.&n; * this part is based on Greg Banks&squot; hd64465_ss.c implementation - Masahiro Abe */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#if defined(CONFIG_CF_AREA6)
DECL|macro|slot_no
mdefine_line|#define slot_no 0
macro_line|#else
DECL|macro|slot_no
mdefine_line|#define slot_no 1
macro_line|#endif
multiline_comment|/* defined in mm/ioremap.c */
r_extern
r_void
op_star
id|p3_ioremap
c_func
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* use this pointer to access to directly connected compact flash io area*/
DECL|variable|cf_io_base
r_void
op_star
id|cf_io_base
suffix:semicolon
DECL|function|allocate_cf_area
r_static
r_int
id|__init
id|allocate_cf_area
c_func
(paren
r_void
)paren
(brace
id|pgprot_t
id|prot
suffix:semicolon
r_int
r_int
id|paddrbase
comma
id|psize
suffix:semicolon
multiline_comment|/* open I/O area window */
id|paddrbase
op_assign
id|virt_to_phys
c_func
(paren
(paren
r_void
op_star
)paren
id|CONFIG_CF_BASE_ADDR
)paren
suffix:semicolon
id|psize
op_assign
id|PAGE_SIZE
suffix:semicolon
id|prot
op_assign
id|PAGE_KERNEL_PCC
c_func
(paren
id|slot_no
comma
id|_PAGE_PCC_IO16
)paren
suffix:semicolon
id|cf_io_base
op_assign
id|p3_ioremap
c_func
(paren
id|paddrbase
comma
id|psize
comma
id|prot.pgprot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cf_io_base
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;allocate_cf_area : can&squot;t open CF I/O window!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/*&t;printk(&quot;p3_ioremap(paddr=0x%08lx, psize=0x%08lx, prot=0x%08lx)=0x%08lx&bslash;n&quot;,&n;&t;    &t;paddrbase, psize, prot.pgprot, cf_io_base);*/
multiline_comment|/* XXX : do we need attribute and common-memory area also? */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|cf_init_default
r_static
r_int
id|__init
id|cf_init_default
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* You must have enabled the card, and set the level interrupt&n; * before reaching this point. Possibly in boot ROM or boot loader.&n; */
macro_line|#if defined(CONFIG_IDE) &amp;&amp; defined(__SH4__)
id|allocate_cf_area
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_SH_UNKNOWN)
multiline_comment|/* This should be done in each board&squot;s init_xxx_irq. */
id|make_imask_irq
c_func
(paren
l_int|14
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
l_int|14
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_SH_GENERIC) || defined(CONFIG_SH_SOLUTION_ENGINE)
macro_line|#include &lt;asm/hitachi_se.h&gt;
multiline_comment|/*&n; * SolutionEngine&n; *&n; * 0xB8400000 : Common Memory&n; * 0xB8500000 : Attribute&n; * 0xB8600000 : I/O&n; */
DECL|function|cf_init_se
r_static
r_int
id|__init
id|cf_init_se
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|ctrl_inw
c_func
(paren
id|MRSHPC_CSR
)paren
op_amp
l_int|0x000c
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Not detected */
r_if
c_cond
(paren
(paren
id|ctrl_inw
c_func
(paren
id|MRSHPC_CSR
)paren
op_amp
l_int|0x0080
)paren
op_eq
l_int|0
)paren
(brace
id|ctrl_outw
c_func
(paren
l_int|0x0674
comma
id|MRSHPC_CPWCR
)paren
suffix:semicolon
multiline_comment|/* Card Vcc is 3.3v? */
)brace
r_else
(brace
id|ctrl_outw
c_func
(paren
l_int|0x0678
comma
id|MRSHPC_CPWCR
)paren
suffix:semicolon
multiline_comment|/* Card Vcc is 5V */
)brace
multiline_comment|/*&n;&t; *  PC-Card window open &n;&t; *  flag == COMMON/ATTRIBUTE/IO&n;&t; */
multiline_comment|/* common window open */
id|ctrl_outw
c_func
(paren
l_int|0x8a84
comma
id|MRSHPC_MW0CR1
)paren
suffix:semicolon
multiline_comment|/* window 0xb8400000 */
r_if
c_cond
(paren
(paren
id|ctrl_inw
c_func
(paren
id|MRSHPC_CSR
)paren
op_amp
l_int|0x4000
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* common mode &amp; bus width 16bit SWAP = 1*/
id|ctrl_outw
c_func
(paren
l_int|0x0b00
comma
id|MRSHPC_MW0CR2
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* common mode &amp; bus width 16bit SWAP = 0*/
id|ctrl_outw
c_func
(paren
l_int|0x0300
comma
id|MRSHPC_MW0CR2
)paren
suffix:semicolon
multiline_comment|/* attribute window open */
id|ctrl_outw
c_func
(paren
l_int|0x8a85
comma
id|MRSHPC_MW1CR1
)paren
suffix:semicolon
multiline_comment|/* window 0xb8500000 */
r_if
c_cond
(paren
(paren
id|ctrl_inw
c_func
(paren
id|MRSHPC_CSR
)paren
op_amp
l_int|0x4000
)paren
op_ne
l_int|0
)paren
multiline_comment|/* attribute mode &amp; bus width 16bit SWAP = 1*/
id|ctrl_outw
c_func
(paren
l_int|0x0a00
comma
id|MRSHPC_MW1CR2
)paren
suffix:semicolon
r_else
multiline_comment|/* attribute mode &amp; bus width 16bit SWAP = 0*/
id|ctrl_outw
c_func
(paren
l_int|0x0200
comma
id|MRSHPC_MW1CR2
)paren
suffix:semicolon
multiline_comment|/* I/O window open */
id|ctrl_outw
c_func
(paren
l_int|0x8a86
comma
id|MRSHPC_IOWCR1
)paren
suffix:semicolon
multiline_comment|/* I/O window 0xb8600000 */
id|ctrl_outw
c_func
(paren
l_int|0x0008
comma
id|MRSHPC_CDCR
)paren
suffix:semicolon
multiline_comment|/* I/O card mode */
r_if
c_cond
(paren
(paren
id|ctrl_inw
c_func
(paren
id|MRSHPC_CSR
)paren
op_amp
l_int|0x4000
)paren
op_ne
l_int|0
)paren
id|ctrl_outw
c_func
(paren
l_int|0x0a00
comma
id|MRSHPC_IOWCR2
)paren
suffix:semicolon
multiline_comment|/* bus width 16bit SWAP = 1*/
r_else
id|ctrl_outw
c_func
(paren
l_int|0x0200
comma
id|MRSHPC_IOWCR2
)paren
suffix:semicolon
multiline_comment|/* bus width 16bit SWAP = 0*/
id|ctrl_outw
c_func
(paren
l_int|0x2000
comma
id|MRSHPC_ICR
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0x00
comma
id|PA_MRSHPC_MW2
op_plus
l_int|0x206
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0x42
comma
id|PA_MRSHPC_MW2
op_plus
l_int|0x200
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|cf_init
r_int
id|__init
id|cf_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_SH_GENERIC) || defined(CONFIG_SH_SOLUTION_ENGINE)
r_if
c_cond
(paren
id|MACH_SE
)paren
r_return
id|cf_init_se
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|cf_init_default
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|cf_init
id|__initcall
(paren
id|cf_init
)paren
suffix:semicolon
eof
