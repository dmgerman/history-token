multiline_comment|/*&n; *  linux/drivers/ide/adma100.c -- basic support for Pacific Digital ADMA-100 boards&n; *&n; *     Created 09 Apr 2002 by Mark Lord&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|ide_init_adma100
r_void
id|__init
id|ide_init_adma100
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_int
r_int
id|phy_admctl
op_assign
id|pci_resource_start
c_func
(paren
id|hwif-&gt;pci_dev
comma
l_int|4
)paren
op_plus
l_int|0x80
op_plus
(paren
id|hwif-&gt;channel
op_star
l_int|0x20
)paren
suffix:semicolon
r_void
op_star
id|v_admctl
suffix:semicolon
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
singleline_comment|// not compatible with normal IDE DMA transfers
id|hwif-&gt;dma_base
op_assign
l_int|0
suffix:semicolon
singleline_comment|// disable DMA completely
id|hwif-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_add_assign
l_int|4
suffix:semicolon
singleline_comment|// chip needs offset of 6 instead of 2
id|v_admctl
op_assign
id|ioremap_nocache
c_func
(paren
id|phy_admctl
comma
l_int|1024
)paren
suffix:semicolon
singleline_comment|// map config regs, so we can turn on drive IRQs
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|v_admctl
)paren
op_and_assign
l_int|3
suffix:semicolon
singleline_comment|// enable aIEN; preserve PIO mode
id|iounmap
c_func
(paren
id|v_admctl
)paren
suffix:semicolon
singleline_comment|// all done; unmap config regs
)brace
eof
