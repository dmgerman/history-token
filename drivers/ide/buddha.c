multiline_comment|/*&n; *  linux/drivers/ide/buddha.c -- Amiga Buddha, Catweasel and X-Surf IDE Driver&n; *&n; *&t;Copyright (C) 1997, 2001 by Geert Uytterhoeven and others&n; *&n; *  This driver was written based on the specifications in README.buddha and&n; *  the X-Surf info from Inside_XSurf.txt available at&n; *  http://www.jschoenfeld.com&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; *&n; *  TODO:&n; *    - test it :-)&n; *    - tune the timings using the speed-register&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
multiline_comment|/*&n;     *  The Buddha has 2 IDE interfaces, the Catweasel has 3, X-Surf has 2&n;     */
DECL|macro|BUDDHA_NUM_HWIFS
mdefine_line|#define BUDDHA_NUM_HWIFS&t;2
DECL|macro|CATWEASEL_NUM_HWIFS
mdefine_line|#define CATWEASEL_NUM_HWIFS&t;3
DECL|macro|XSURF_NUM_HWIFS
mdefine_line|#define XSURF_NUM_HWIFS         2
multiline_comment|/*&n;     *  Bases of the IDE interfaces (relative to the board address)&n;     */
DECL|macro|BUDDHA_BASE1
mdefine_line|#define BUDDHA_BASE1&t;0x800
DECL|macro|BUDDHA_BASE2
mdefine_line|#define BUDDHA_BASE2&t;0xa00
DECL|macro|BUDDHA_BASE3
mdefine_line|#define BUDDHA_BASE3&t;0xc00
DECL|macro|XSURF_BASE1
mdefine_line|#define XSURF_BASE1     0xb000 /* 2.5&quot; Interface */
DECL|macro|XSURF_BASE2
mdefine_line|#define XSURF_BASE2     0xd000 /* 3.5&quot; Interface */
DECL|variable|__initdata
r_static
id|u_int
id|buddha_bases
(braket
id|CATWEASEL_NUM_HWIFS
)braket
id|__initdata
op_assign
(brace
id|BUDDHA_BASE1
comma
id|BUDDHA_BASE2
comma
id|BUDDHA_BASE3
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_int
id|xsurf_bases
(braket
id|XSURF_NUM_HWIFS
)braket
id|__initdata
op_assign
(brace
id|XSURF_BASE1
comma
id|XSURF_BASE2
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Offsets from one of the above bases&n;     */
DECL|macro|BUDDHA_DATA
mdefine_line|#define BUDDHA_DATA&t;0x00
DECL|macro|BUDDHA_ERROR
mdefine_line|#define BUDDHA_ERROR&t;0x06&t;&t;/* see err-bits */
DECL|macro|BUDDHA_NSECTOR
mdefine_line|#define BUDDHA_NSECTOR&t;0x0a&t;&t;/* nr of sectors to read/write */
DECL|macro|BUDDHA_SECTOR
mdefine_line|#define BUDDHA_SECTOR&t;0x0e&t;&t;/* starting sector */
DECL|macro|BUDDHA_LCYL
mdefine_line|#define BUDDHA_LCYL&t;0x12&t;&t;/* starting cylinder */
DECL|macro|BUDDHA_HCYL
mdefine_line|#define BUDDHA_HCYL&t;0x16&t;&t;/* high byte of starting cyl */
DECL|macro|BUDDHA_SELECT
mdefine_line|#define BUDDHA_SELECT&t;0x1a&t;&t;/* 101dhhhh , d=drive, hhhh=head */
DECL|macro|BUDDHA_STATUS
mdefine_line|#define BUDDHA_STATUS&t;0x1e&t;&t;/* see status-bits */
DECL|macro|BUDDHA_CONTROL
mdefine_line|#define BUDDHA_CONTROL&t;0x11a
DECL|macro|XSURF_CONTROL
mdefine_line|#define XSURF_CONTROL   -1              /* X-Surf has no CS1* (Control/AltStat) */
DECL|variable|__initdata
r_static
r_int
id|buddha_offsets
(braket
id|IDE_NR_PORTS
)braket
id|__initdata
op_assign
(brace
id|BUDDHA_DATA
comma
id|BUDDHA_ERROR
comma
id|BUDDHA_NSECTOR
comma
id|BUDDHA_SECTOR
comma
id|BUDDHA_LCYL
comma
id|BUDDHA_HCYL
comma
id|BUDDHA_SELECT
comma
id|BUDDHA_STATUS
comma
id|BUDDHA_CONTROL
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|xsurf_offsets
(braket
id|IDE_NR_PORTS
)braket
id|__initdata
op_assign
(brace
id|BUDDHA_DATA
comma
id|BUDDHA_ERROR
comma
id|BUDDHA_NSECTOR
comma
id|BUDDHA_SECTOR
comma
id|BUDDHA_LCYL
comma
id|BUDDHA_HCYL
comma
id|BUDDHA_SELECT
comma
id|BUDDHA_STATUS
comma
id|XSURF_CONTROL
comma
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Other registers&n;     */
DECL|macro|BUDDHA_IRQ1
mdefine_line|#define BUDDHA_IRQ1&t;0xf00&t;&t;/* MSB = 1, Harddisk is source of */
DECL|macro|BUDDHA_IRQ2
mdefine_line|#define BUDDHA_IRQ2&t;0xf40&t;&t;/* interrupt */
DECL|macro|BUDDHA_IRQ3
mdefine_line|#define BUDDHA_IRQ3&t;0xf80
DECL|macro|XSURF_IRQ1
mdefine_line|#define XSURF_IRQ1      0x7e
DECL|macro|XSURF_IRQ2
mdefine_line|#define XSURF_IRQ2      0x7e
DECL|variable|__initdata
r_static
r_int
id|buddha_irqports
(braket
id|CATWEASEL_NUM_HWIFS
)braket
id|__initdata
op_assign
(brace
id|BUDDHA_IRQ1
comma
id|BUDDHA_IRQ2
comma
id|BUDDHA_IRQ3
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|xsurf_irqports
(braket
id|XSURF_NUM_HWIFS
)braket
id|__initdata
op_assign
(brace
id|XSURF_IRQ1
comma
id|XSURF_IRQ2
)brace
suffix:semicolon
DECL|macro|BUDDHA_IRQ_MR
mdefine_line|#define BUDDHA_IRQ_MR&t;0xfc0&t;&t;/* master interrupt enable */
multiline_comment|/*&n;     *  Board information&n;     */
DECL|enum|BuddhaType_Enum
r_typedef
r_enum
id|BuddhaType_Enum
(brace
DECL|enumerator|BOARD_BUDDHA
DECL|enumerator|BOARD_CATWEASEL
DECL|enumerator|BOARD_XSURF
id|BOARD_BUDDHA
comma
id|BOARD_CATWEASEL
comma
id|BOARD_XSURF
DECL|typedef|BuddhaType
)brace
id|BuddhaType
suffix:semicolon
multiline_comment|/*&n;     *  Check and acknowledge the interrupt status&n;     */
DECL|function|buddha_ack_intr
r_static
r_int
id|buddha_ack_intr
c_func
(paren
r_struct
id|ata_channel
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
l_int|0x80
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|xsurf_ack_intr
r_static
r_int
id|xsurf_ack_intr
c_func
(paren
r_struct
id|ata_channel
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
multiline_comment|/* X-Surf needs a 0 written to IRQ register to ensure ISA bit A11 stays at 0 */
id|z_writeb
c_func
(paren
l_int|0
comma
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
l_int|0x80
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Probe for a Buddha or Catweasel IDE interface&n;     */
DECL|function|buddha_init
r_void
id|__init
id|buddha_init
c_func
(paren
r_void
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
r_int
id|i
comma
id|index
suffix:semicolon
r_struct
id|zorro_dev
op_star
id|z
op_assign
l_int|NULL
suffix:semicolon
id|u_long
id|buddha_board
op_assign
l_int|0
suffix:semicolon
id|BuddhaType
id|type
suffix:semicolon
r_int
id|buddha_num_hwifs
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
r_int
r_int
id|board
suffix:semicolon
r_if
c_cond
(paren
id|z-&gt;id
op_eq
id|ZORRO_PROD_INDIVIDUAL_COMPUTERS_BUDDHA
)paren
(brace
id|buddha_num_hwifs
op_assign
id|BUDDHA_NUM_HWIFS
suffix:semicolon
id|type
op_assign
id|BOARD_BUDDHA
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|z-&gt;id
op_eq
id|ZORRO_PROD_INDIVIDUAL_COMPUTERS_CATWEASEL
)paren
(brace
id|buddha_num_hwifs
op_assign
id|CATWEASEL_NUM_HWIFS
suffix:semicolon
id|type
op_assign
id|BOARD_CATWEASEL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|z-&gt;id
op_eq
id|ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF
)paren
(brace
id|buddha_num_hwifs
op_assign
id|XSURF_NUM_HWIFS
suffix:semicolon
id|type
op_assign
id|BOARD_XSURF
suffix:semicolon
)brace
r_else
r_continue
suffix:semicolon
id|board
op_assign
id|z-&gt;resource.start
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|BOARD_XSURF
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|board
op_plus
id|BUDDHA_BASE1
comma
l_int|0x800
comma
l_string|&quot;IDE&quot;
)paren
)paren
r_continue
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|board
op_plus
id|XSURF_BASE1
comma
l_int|0x1000
comma
l_string|&quot;IDE&quot;
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|board
op_plus
id|XSURF_BASE2
comma
l_int|0x1000
comma
l_string|&quot;IDE&quot;
)paren
)paren
r_goto
id|fail_base2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|board
op_plus
id|XSURF_IRQ1
comma
l_int|0x8
comma
l_string|&quot;IDE&quot;
)paren
)paren
(brace
id|release_mem_region
c_func
(paren
id|board
op_plus
id|XSURF_BASE2
comma
l_int|0x1000
)paren
suffix:semicolon
id|fail_base2
suffix:colon
id|release_mem_region
c_func
(paren
id|board
op_plus
id|XSURF_BASE1
comma
l_int|0x1000
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|buddha_board
op_assign
id|ZTWO_VADDR
c_func
(paren
id|board
)paren
suffix:semicolon
multiline_comment|/* write to BUDDHA_IRQ_MR to enable the board IRQ */
multiline_comment|/* X-Surf doesn&squot;t have this.  IRQs are always on */
r_if
c_cond
(paren
id|type
op_ne
id|BOARD_XSURF
)paren
id|z_writeb
c_func
(paren
l_int|0
comma
id|buddha_board
op_plus
id|BUDDHA_IRQ_MR
)paren
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
id|buddha_num_hwifs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|type
op_ne
id|BOARD_XSURF
)paren
(brace
id|ide_setup_ports
c_func
(paren
op_amp
id|hw
comma
(paren
id|ide_ioreg_t
)paren
(paren
id|buddha_board
op_plus
id|buddha_bases
(braket
id|i
)braket
)paren
comma
id|buddha_offsets
comma
l_int|0
comma
(paren
id|ide_ioreg_t
)paren
(paren
id|buddha_board
op_plus
id|buddha_irqports
(braket
id|i
)braket
)paren
comma
id|buddha_ack_intr
comma
id|IRQ_AMIGA_PORTS
)paren
suffix:semicolon
)brace
r_else
(brace
id|ide_setup_ports
c_func
(paren
op_amp
id|hw
comma
(paren
id|ide_ioreg_t
)paren
(paren
id|buddha_board
op_plus
id|xsurf_bases
(braket
id|i
)braket
)paren
comma
id|xsurf_offsets
comma
l_int|0
comma
(paren
id|ide_ioreg_t
)paren
(paren
id|buddha_board
op_plus
id|xsurf_irqports
(braket
id|i
)braket
)paren
comma
id|xsurf_ack_intr
comma
id|IRQ_AMIGA_PORTS
)paren
suffix:semicolon
)brace
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
id|printk
c_func
(paren
l_string|&quot;ide%d: &quot;
comma
id|index
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|BOARD_BUDDHA
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Buddha&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BOARD_CATWEASEL
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Catweasel&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BOARD_XSURF
suffix:colon
id|printk
c_func
(paren
l_string|&quot;X-Surf&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; IDE interface&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
eof
