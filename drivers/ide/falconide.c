multiline_comment|/*&n; *  linux/drivers/ide/falconide.c -- Atari Falcon IDE Driver&n; *&n; *     Created 12 Jul 1997 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
macro_line|#include &lt;asm/atari_stdma.h&gt;
multiline_comment|/*&n;     *  Base of the IDE interface&n;     */
DECL|macro|ATA_HD_BASE
mdefine_line|#define ATA_HD_BASE&t;0xfff00000
multiline_comment|/*&n;     *  Offsets from the above base&n;     */
DECL|macro|ATA_HD_DATA
mdefine_line|#define ATA_HD_DATA&t;0x00
DECL|macro|ATA_HD_ERROR
mdefine_line|#define ATA_HD_ERROR&t;0x05&t;&t;/* see err-bits */
DECL|macro|ATA_HD_NSECTOR
mdefine_line|#define ATA_HD_NSECTOR&t;0x09&t;&t;/* nr of sectors to read/write */
DECL|macro|ATA_HD_SECTOR
mdefine_line|#define ATA_HD_SECTOR&t;0x0d&t;&t;/* starting sector */
DECL|macro|ATA_HD_LCYL
mdefine_line|#define ATA_HD_LCYL&t;0x11&t;&t;/* starting cylinder */
DECL|macro|ATA_HD_HCYL
mdefine_line|#define ATA_HD_HCYL&t;0x15&t;&t;/* high byte of starting cyl */
DECL|macro|ATA_HD_SELECT
mdefine_line|#define ATA_HD_SELECT&t;0x19&t;&t;/* 101dhhhh , d=drive, hhhh=head */
DECL|macro|ATA_HD_STATUS
mdefine_line|#define ATA_HD_STATUS&t;0x1d&t;&t;/* see status-bits */
DECL|macro|ATA_HD_CONTROL
mdefine_line|#define ATA_HD_CONTROL&t;0x39
DECL|variable|__initdata
r_static
r_int
id|falconide_offsets
(braket
id|IDE_NR_PORTS
)braket
id|__initdata
op_assign
(brace
id|ATA_HD_DATA
comma
id|ATA_HD_ERROR
comma
id|ATA_HD_NSECTOR
comma
id|ATA_HD_SECTOR
comma
id|ATA_HD_LCYL
comma
id|ATA_HD_HCYL
comma
id|ATA_HD_SELECT
comma
id|ATA_HD_STATUS
comma
id|ATA_HD_CONTROL
comma
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Probe for a Falcon IDE interface&n;     */
DECL|function|falconide_init
r_void
id|__init
id|falconide_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MACH_IS_ATARI
op_logical_and
id|ATARIHW_PRESENT
c_func
(paren
id|IDE
)paren
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
r_int
id|index
suffix:semicolon
id|ide_setup_ports
c_func
(paren
op_amp
id|hw
comma
(paren
id|ide_ioreg_t
)paren
id|ATA_HD_BASE
comma
id|falconide_offsets
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|IRQ_MFP_IDE
)paren
suffix:semicolon
id|index
op_assign
id|ide_register_hw
c_func
(paren
op_amp
id|hw
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
id|printk
c_func
(paren
l_string|&quot;ide%d: Falcon IDE interface&bslash;n&quot;
comma
id|index
)paren
suffix:semicolon
)brace
)brace
eof
