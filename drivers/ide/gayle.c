multiline_comment|/*&n; *  linux/drivers/ide/gayle.c -- Amiga Gayle IDE Driver&n; *&n; *     Created 9 Jul 1997 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigayle.h&gt;
multiline_comment|/*&n;     *  Bases of the IDE interfaces&n;     */
DECL|macro|GAYLE_BASE_4000
mdefine_line|#define GAYLE_BASE_4000&t;0xdd2020&t;/* A4000/A4000T */
DECL|macro|GAYLE_BASE_1200
mdefine_line|#define GAYLE_BASE_1200&t;0xda0000&t;/* A1200/A600 */
multiline_comment|/*&n;     *  Offsets from one of the above bases&n;     */
DECL|macro|GAYLE_DATA
mdefine_line|#define GAYLE_DATA&t;0x00
DECL|macro|GAYLE_ERROR
mdefine_line|#define GAYLE_ERROR&t;0x06&t;&t;/* see err-bits */
DECL|macro|GAYLE_NSECTOR
mdefine_line|#define GAYLE_NSECTOR&t;0x0a&t;&t;/* nr of sectors to read/write */
DECL|macro|GAYLE_SECTOR
mdefine_line|#define GAYLE_SECTOR&t;0x0e&t;&t;/* starting sector */
DECL|macro|GAYLE_LCYL
mdefine_line|#define GAYLE_LCYL&t;0x12&t;&t;/* starting cylinder */
DECL|macro|GAYLE_HCYL
mdefine_line|#define GAYLE_HCYL&t;0x16&t;&t;/* high byte of starting cyl */
DECL|macro|GAYLE_SELECT
mdefine_line|#define GAYLE_SELECT&t;0x1a&t;&t;/* 101dhhhh , d=drive, hhhh=head */
DECL|macro|GAYLE_STATUS
mdefine_line|#define GAYLE_STATUS&t;0x1e&t;&t;/* see status-bits */
DECL|macro|GAYLE_CONTROL
mdefine_line|#define GAYLE_CONTROL&t;0x101a
DECL|variable|__initdata
r_static
r_int
id|gayle_offsets
(braket
id|IDE_NR_PORTS
)braket
id|__initdata
op_assign
(brace
id|GAYLE_DATA
comma
id|GAYLE_ERROR
comma
id|GAYLE_NSECTOR
comma
id|GAYLE_SECTOR
comma
id|GAYLE_LCYL
comma
id|GAYLE_HCYL
comma
id|GAYLE_SELECT
comma
id|GAYLE_STATUS
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/*&n;     *  These are at different offsets from the base&n;     */
DECL|macro|GAYLE_IRQ_4000
mdefine_line|#define GAYLE_IRQ_4000&t;0xdd3020&t;/* MSB = 1, Harddisk is source of */
DECL|macro|GAYLE_IRQ_1200
mdefine_line|#define GAYLE_IRQ_1200&t;0xda9000&t;/* interrupt */
multiline_comment|/*&n;     *  Offset of the secondary port for IDE doublers&n;     *  Note that GAYLE_CONTROL is NOT available then!&n;     */
DECL|macro|GAYLE_NEXT_PORT
mdefine_line|#define GAYLE_NEXT_PORT&t;0x1000
macro_line|#ifndef CONFIG_BLK_DEV_IDEDOUBLER
DECL|macro|GAYLE_NUM_HWIFS
mdefine_line|#define GAYLE_NUM_HWIFS&t;&t;1
DECL|macro|GAYLE_NUM_PROBE_HWIFS
mdefine_line|#define GAYLE_NUM_PROBE_HWIFS&t;GAYLE_NUM_HWIFS
DECL|macro|GAYLE_HAS_CONTROL_REG
mdefine_line|#define GAYLE_HAS_CONTROL_REG&t;1
DECL|macro|GAYLE_IDEREG_SIZE
mdefine_line|#define GAYLE_IDEREG_SIZE&t;0x2000
macro_line|#else /* CONFIG_BLK_DEV_IDEDOUBLER */
DECL|macro|GAYLE_NUM_HWIFS
mdefine_line|#define GAYLE_NUM_HWIFS&t;&t;2
DECL|macro|GAYLE_NUM_PROBE_HWIFS
mdefine_line|#define GAYLE_NUM_PROBE_HWIFS&t;(ide_doubler ? GAYLE_NUM_HWIFS : &bslash;&n;&t;&t;&t;&t;&t;       GAYLE_NUM_HWIFS-1)
DECL|macro|GAYLE_HAS_CONTROL_REG
mdefine_line|#define GAYLE_HAS_CONTROL_REG&t;(!ide_doubler)
DECL|macro|GAYLE_IDEREG_SIZE
mdefine_line|#define GAYLE_IDEREG_SIZE&t;(ide_doubler ? 0x1000 : 0x2000)
DECL|variable|ide_doubler
r_int
id|ide_doubler
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* support IDE doublers? */
macro_line|#endif /* CONFIG_BLK_DEV_IDEDOUBLER */
multiline_comment|/*&n;     *  Check and acknowledge the interrupt status&n;     */
DECL|function|gayle_ack_intr_a4000
r_static
r_int
id|gayle_ack_intr_a4000
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
id|ch
op_assign
id|z_readb
c_func
(paren
id|hwif-&gt;io_ports
(braket
id|IDE_IRQ_OFFSET
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ch
op_amp
id|GAYLE_IRQ_IDE
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|gayle_ack_intr_a1200
r_static
r_int
id|gayle_ack_intr_a1200
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
id|ch
op_assign
id|z_readb
c_func
(paren
id|hwif-&gt;io_ports
(braket
id|IDE_IRQ_OFFSET
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ch
op_amp
id|GAYLE_IRQ_IDE
)paren
)paren
r_return
l_int|0
suffix:semicolon
(paren
r_void
)paren
id|z_readb
c_func
(paren
id|hwif-&gt;io_ports
(braket
id|IDE_STATUS_OFFSET
)braket
)paren
suffix:semicolon
id|z_writeb
c_func
(paren
l_int|0x7c
comma
id|hwif-&gt;io_ports
(braket
id|IDE_IRQ_OFFSET
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Probe for a Gayle IDE interface (and optionally for an IDE doubler)&n;     */
DECL|function|gayle_init
r_void
id|__init
id|gayle_init
c_func
(paren
r_void
)paren
(brace
r_int
id|a4000
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_AMIGA
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|a4000
op_assign
id|AMIGAHW_PRESENT
c_func
(paren
id|A4000_IDE
)paren
)paren
op_logical_and
op_logical_neg
id|AMIGAHW_PRESENT
c_func
(paren
id|A1200_IDE
)paren
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|GAYLE_NUM_PROBE_HWIFS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ide_ioreg_t
id|base
comma
id|ctrlport
comma
id|irqport
suffix:semicolon
id|ide_ack_intr_t
op_star
id|ack_intr
suffix:semicolon
id|hw_regs_t
id|hw
suffix:semicolon
r_int
id|index
suffix:semicolon
r_int
r_int
id|phys_base
comma
id|res_start
comma
id|res_n
suffix:semicolon
r_if
c_cond
(paren
id|a4000
)paren
(brace
id|phys_base
op_assign
id|GAYLE_BASE_4000
suffix:semicolon
id|irqport
op_assign
(paren
id|ide_ioreg_t
)paren
id|ZTWO_VADDR
c_func
(paren
id|GAYLE_IRQ_4000
)paren
suffix:semicolon
id|ack_intr
op_assign
id|gayle_ack_intr_a4000
suffix:semicolon
)brace
r_else
(brace
id|phys_base
op_assign
id|GAYLE_BASE_1200
suffix:semicolon
id|irqport
op_assign
(paren
id|ide_ioreg_t
)paren
id|ZTWO_VADDR
c_func
(paren
id|GAYLE_IRQ_1200
)paren
suffix:semicolon
id|ack_intr
op_assign
id|gayle_ack_intr_a1200
suffix:semicolon
)brace
id|phys_base
op_add_assign
id|i
op_star
id|GAYLE_NEXT_PORT
suffix:semicolon
id|res_start
op_assign
(paren
(paren
r_int
r_int
)paren
id|phys_base
)paren
op_amp
op_complement
(paren
id|GAYLE_NEXT_PORT
op_minus
l_int|1
)paren
suffix:semicolon
id|res_n
op_assign
id|GAYLE_IDEREG_SIZE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|res_start
comma
id|res_n
comma
l_string|&quot;IDE&quot;
)paren
)paren
r_continue
suffix:semicolon
id|base
op_assign
(paren
id|ide_ioreg_t
)paren
id|ZTWO_VADDR
c_func
(paren
id|phys_base
)paren
suffix:semicolon
id|ctrlport
op_assign
id|GAYLE_HAS_CONTROL_REG
ques
c_cond
(paren
id|base
op_plus
id|GAYLE_CONTROL
)paren
suffix:colon
l_int|0
suffix:semicolon
id|ide_setup_ports
c_func
(paren
op_amp
id|hw
comma
id|base
comma
id|gayle_offsets
comma
id|ctrlport
comma
id|irqport
comma
id|ack_intr
comma
id|IRQ_AMIGA_PORTS
)paren
suffix:semicolon
id|index
op_assign
id|ide_register_hw
c_func
(paren
op_amp
id|hw
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
op_ne
op_minus
l_int|1
)paren
(brace
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ide%d: Gayle IDE interface (A%d style)&bslash;n&quot;
comma
id|index
comma
id|a4000
ques
c_cond
l_int|4000
suffix:colon
l_int|1200
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDOUBLER
r_case
l_int|1
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ide%d: IDE doubler&bslash;n&quot;
comma
id|index
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEDOUBLER */
)brace
)brace
r_else
id|release_mem_region
c_func
(paren
id|res_start
comma
id|res_n
)paren
suffix:semicolon
macro_line|#if 1 /* TESTING */
r_if
c_cond
(paren
id|i
op_eq
l_int|1
)paren
(brace
r_volatile
id|u_short
op_star
id|addr
op_assign
(paren
id|u_short
op_star
)paren
id|base
suffix:semicolon
id|u_short
id|data
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;+++ Probing for IDE doubler... &quot;
)paren
suffix:semicolon
op_star
id|addr
op_assign
l_int|0xffff
suffix:semicolon
id|data
op_assign
op_star
id|addr
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;probe returned 0x%02x (PLEASE REPORT THIS!!)&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
)brace
macro_line|#endif /* TESTING */
)brace
)brace
eof
