multiline_comment|/*&n; * linux/arch/sh/kernel/pci-7751se.c&n; *&n; * Author:  Ian DaSilva (idasilva@mvista.com)&n; *&n; * Highly leveraged from pci-bigsur.c, written by Dustin McIntire.&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * PCI initialization for the Hitachi SH7751 Solution Engine board (MS7751SE01)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pci-sh7751.h&gt;
DECL|macro|PCIMCR_MRSET_OFF
mdefine_line|#define PCIMCR_MRSET_OFF&t;0xBFFFFFFF
DECL|macro|PCIMCR_RFSH_OFF
mdefine_line|#define PCIMCR_RFSH_OFF&t;&t;0xFFFFFFFB
multiline_comment|/*&n; * Only long word accesses of the PCIC&squot;s internal local registers and the&n; * configuration registers from the CPU is supported.&n; */
DECL|macro|PCIC_WRITE
mdefine_line|#define PCIC_WRITE(x,v) writel((v), PCI_REG(x))
DECL|macro|PCIC_READ
mdefine_line|#define PCIC_READ(x) readl(PCI_REG(x))
multiline_comment|/*&n; * Description:  This function sets up and initializes the pcic, sets&n; * up the BARS, maps the DRAM into the address space etc, etc.&n; */
DECL|function|pcibios_init_platform
r_int
id|__init
id|pcibios_init_platform
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|data
suffix:semicolon
r_int
r_int
id|bcr1
comma
id|wcr1
comma
id|wcr2
comma
id|wcr3
comma
id|mcr
suffix:semicolon
r_int
r_int
id|bcr2
suffix:semicolon
multiline_comment|/*&n;    * Initialize the slave bus controller on the pcic.  The values used&n;    * here should not be hardcoded, but they should be taken from the bsc&n;    * on the processor, to make this function as generic as possible.&n;    * (i.e. Another sbc may usr different SDRAM timing settings -- in order&n;    * for the pcic to work, its settings need to be exactly the same.)&n;    */
id|bcr1
op_assign
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|SH7751_BCR1
)paren
)paren
suffix:semicolon
id|bcr2
op_assign
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|SH7751_BCR2
)paren
)paren
suffix:semicolon
id|wcr1
op_assign
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|SH7751_WCR1
)paren
)paren
suffix:semicolon
id|wcr2
op_assign
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|SH7751_WCR2
)paren
)paren
suffix:semicolon
id|wcr3
op_assign
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|SH7751_WCR3
)paren
)paren
suffix:semicolon
id|mcr
op_assign
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|SH7751_MCR
)paren
)paren
suffix:semicolon
id|bcr1
op_assign
id|bcr1
op_or
l_int|0x00080000
suffix:semicolon
multiline_comment|/* Enable Bit 19, BREQEN */
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|SH7751_BCR1
)paren
)paren
op_assign
id|bcr1
suffix:semicolon
id|bcr1
op_assign
id|bcr1
op_or
l_int|0x40080000
suffix:semicolon
multiline_comment|/* Enable Bit 19 BREQEN, set PCIC to slave */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCIBCR1
comma
id|bcr1
)paren
suffix:semicolon
multiline_comment|/* PCIC BCR1 */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCIBCR2
comma
id|bcr2
)paren
suffix:semicolon
multiline_comment|/* PCIC BCR2 */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCIWCR1
comma
id|wcr1
)paren
suffix:semicolon
multiline_comment|/* PCIC WCR1 */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCIWCR2
comma
id|wcr2
)paren
suffix:semicolon
multiline_comment|/* PCIC WCR2 */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCIWCR3
comma
id|wcr3
)paren
suffix:semicolon
multiline_comment|/* PCIC WCR3 */
id|mcr
op_assign
(paren
id|mcr
op_amp
id|PCIMCR_MRSET_OFF
)paren
op_amp
id|PCIMCR_RFSH_OFF
suffix:semicolon
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCIMCR
comma
id|mcr
)paren
suffix:semicolon
multiline_comment|/* PCIC MCR */
multiline_comment|/* Enable all interrupts, so we know what to fix */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCIINTM
comma
l_int|0x0000c3ff
)paren
suffix:semicolon
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCIAINTM
comma
l_int|0x0000380f
)paren
suffix:semicolon
multiline_comment|/* Set up standard PCI config registers */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCICONF1
comma
l_int|0xF39000C7
)paren
suffix:semicolon
multiline_comment|/* Bus Master, Mem &amp; I/O access */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCICONF2
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* PCI Class code &amp; Revision ID */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCICONF4
comma
l_int|0xab000001
)paren
suffix:semicolon
multiline_comment|/* PCI I/O address (local regs) */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCICONF5
comma
l_int|0x0c000000
)paren
suffix:semicolon
multiline_comment|/* PCI MEM address (local RAM)  */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCICONF6
comma
l_int|0xd0000000
)paren
suffix:semicolon
multiline_comment|/* PCI MEM address (unused)     */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCICONF11
comma
l_int|0x35051054
)paren
suffix:semicolon
multiline_comment|/* PCI Subsystem ID &amp; Vendor ID */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCILSR0
comma
l_int|0x03f00000
)paren
suffix:semicolon
multiline_comment|/* MEM (full 64M exposed)       */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCILSR1
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* MEM (unused)                 */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCILAR0
comma
l_int|0x0c000000
)paren
suffix:semicolon
multiline_comment|/* MEM (direct map from PCI)    */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCILAR1
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* MEM (unused)                 */
multiline_comment|/* Now turn it on... */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCICR
comma
l_int|0xa5000001
)paren
suffix:semicolon
multiline_comment|/*&n;    * Set PCIMBR and PCIIOBR here, assuming a single window&n;    * (16M MEM, 256K IO) is enough.  If a larger space is&n;    * needed, the readx/writex and inx/outx functions will&n;    * have to do more (e.g. setting registers for each call).&n;    */
multiline_comment|/*&n;    * Set the MBR so PCI address is one-to-one with window,&n;    * meaning all calls go straight through... use ifdef to&n;    * catch erroneous assumption.&n;    */
macro_line|#if PCIBIOS_MIN_MEM != SH7751_PCI_MEMORY_BASE
macro_line|#error One-to-one assumption for PCI memory mapping is wrong!?!?!?
macro_line|#endif   
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCIMBR
comma
id|PCIBIOS_MIN_MEM
)paren
suffix:semicolon
multiline_comment|/* Set IOBR for window containing area specified in pci.h */
id|PCIC_WRITE
c_func
(paren
id|SH7751_PCIIOBR
comma
(paren
id|PCIBIOS_MIN_IO
op_amp
id|SH7751_PCIIOBR_MASK
)paren
)paren
suffix:semicolon
multiline_comment|/* All done, may as well say so... */
id|printk
c_func
(paren
l_string|&quot;SH7751 PCI: Finished initialization of the PCI controller&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pcibios_map_platform_irq
r_int
id|__init
id|pcibios_map_platform_irq
c_func
(paren
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_switch
c_cond
(paren
id|slot
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|13
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
l_int|13
suffix:semicolon
multiline_comment|/* AMD Ethernet controller */
r_case
l_int|2
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
r_case
l_int|4
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;PCI: Bad IRQ mapping request for slot %d&bslash;n&quot;
comma
id|slot
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
eof
