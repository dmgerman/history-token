multiline_comment|/*&n; * $Id: prep_pci.c,v 1.40 1999/09/17 17:23:05 cort Exp $&n; * PReP pci functions.&n; * Originally by Gary Thomas&n; * rewritten and updated by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * The motherboard routes/maps will disappear shortly. -- Cort&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/openpic.h&gt;
macro_line|#include &lt;asm/init.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|MAX_DEVNR
mdefine_line|#define MAX_DEVNR 22
multiline_comment|/* Which PCI interrupt line does a given device [slot] use? */
multiline_comment|/* Note: This really should be two dimensional based in slot/pin used */
DECL|variable|Motherboard_map
r_int
r_char
op_star
id|Motherboard_map
suffix:semicolon
DECL|variable|Motherboard_map_name
r_int
r_char
op_star
id|Motherboard_map_name
suffix:semicolon
multiline_comment|/* How is the 82378 PIRQ mapping setup? */
DECL|variable|Motherboard_routes
r_int
r_char
op_star
id|Motherboard_routes
suffix:semicolon
multiline_comment|/* Used for Motorola to store system config register */
DECL|variable|ProcInfo
r_static
r_int
r_int
op_star
id|ProcInfo
suffix:semicolon
r_extern
r_int
id|chrp_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|chrp_post_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Tables for known hardware */
multiline_comment|/* Motorola PowerStackII - Utah */
DECL|variable|__prepdata
r_static
r_char
id|Utah_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|5
comma
multiline_comment|/* Slot 2  - SCSI - NCR825A  */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|1
comma
multiline_comment|/* Slot 4  - Ethernet - DEC2114x */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|3
comma
multiline_comment|/* Slot 6  - PCI Card slot #1 */
l_int|4
comma
multiline_comment|/* Slot 7  - PCI Card slot #2 */
l_int|5
comma
multiline_comment|/* Slot 8  - PCI Card slot #3 */
l_int|5
comma
multiline_comment|/* Slot 9  - PCI Bridge */
multiline_comment|/* added here in case we ever support PCI bridges */
multiline_comment|/* Secondary PCI bus cards are at slot-9,6 &amp; slot-9,7 */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|5
comma
multiline_comment|/* Slot 12 - SCSI - NCR825A */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|3
comma
multiline_comment|/* Slot 14 - enet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|2
comma
multiline_comment|/* Slot 16 - unused */
l_int|3
comma
multiline_comment|/* Slot 17 - unused */
l_int|5
comma
multiline_comment|/* Slot 18 - unused */
l_int|0
comma
multiline_comment|/* Slot 19 - unused */
l_int|0
comma
multiline_comment|/* Slot 20 - unused */
l_int|0
comma
multiline_comment|/* Slot 21 - unused */
l_int|0
comma
multiline_comment|/* Slot 22 - unused */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Utah_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|9
comma
multiline_comment|/* Line 1 */
l_int|10
comma
multiline_comment|/* Line 2 */
l_int|11
comma
multiline_comment|/* Line 3 */
l_int|14
comma
multiline_comment|/* Line 4 */
l_int|15
comma
multiline_comment|/* Line 5 */
)brace
suffix:semicolon
multiline_comment|/* Motorola PowerStackII - Omaha */
multiline_comment|/* no integrated SCSI or ethernet */
DECL|variable|__prepdata
r_static
r_char
id|Omaha_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|3
comma
multiline_comment|/* Slot 2  - Winbond EIDE */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|1
comma
multiline_comment|/* Slot 6  - PCI slot 1 */
l_int|2
comma
multiline_comment|/* Slot 7  - PCI slot 2  */
l_int|3
comma
multiline_comment|/* Slot 8  - PCI slot 3 */
l_int|4
comma
multiline_comment|/* Slot 9  - PCI slot 4 */
multiline_comment|/* needs indirect access */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|0
comma
multiline_comment|/* Slot 12 - unused */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|0
comma
multiline_comment|/* Slot 14 - unused */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|1
comma
multiline_comment|/* Slot 16  - PCI slot 1 */
l_int|2
comma
multiline_comment|/* Slot 17  - PCI slot 2  */
l_int|3
comma
multiline_comment|/* Slot 18  - PCI slot 3 */
l_int|4
comma
multiline_comment|/* Slot 19  - PCI slot 4 */
multiline_comment|/* needs indirect access */
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Omaha_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|9
comma
multiline_comment|/* Line 1 */
l_int|11
comma
multiline_comment|/* Line 2 */
l_int|14
comma
multiline_comment|/* Line 3 */
l_int|15
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* Motorola PowerStack */
DECL|variable|__prepdata
r_static
r_char
id|Blackhawk_pci_IRQ_map
(braket
l_int|19
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|3
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|1
comma
multiline_comment|/* Slot 14 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|1
comma
multiline_comment|/* Slot P7 */
l_int|2
comma
multiline_comment|/* Slot P6 */
l_int|3
comma
multiline_comment|/* Slot P5 */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Blackhawk_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|9
comma
multiline_comment|/* Line 1 */
l_int|11
comma
multiline_comment|/* Line 2 */
l_int|15
comma
multiline_comment|/* Line 3 */
l_int|15
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* Motorola Mesquite */
DECL|variable|__prepdata
r_static
r_char
id|Mesquite_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unxued */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|0
comma
multiline_comment|/* Slot 12 - unused */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|2
comma
multiline_comment|/* Slot 14 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|3
comma
multiline_comment|/* Slot 16 - PMC */
l_int|0
comma
multiline_comment|/* Slot 17 - unused */
l_int|0
comma
multiline_comment|/* Slot 18 - unused */
l_int|0
comma
multiline_comment|/* Slot 19 - unused */
l_int|0
comma
multiline_comment|/* Slot 20 - unused */
l_int|0
comma
multiline_comment|/* Slot 21 - unused */
l_int|0
comma
multiline_comment|/* Slot 22 - unused */
)brace
suffix:semicolon
multiline_comment|/* Motorola Sitka */
DECL|variable|__prepdata
r_static
r_char
id|Sitka_pci_IRQ_map
(braket
l_int|21
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unxued */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|0
comma
multiline_comment|/* Slot 12 - unused */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|2
comma
multiline_comment|/* Slot 14 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|9
comma
multiline_comment|/* Slot 16 - PMC 1  */
l_int|12
comma
multiline_comment|/* Slot 17 - PMC 2  */
l_int|0
comma
multiline_comment|/* Slot 18 - unused */
l_int|0
comma
multiline_comment|/* Slot 19 - unused */
l_int|4
comma
multiline_comment|/* Slot 20 - NT P2P bridge */
)brace
suffix:semicolon
multiline_comment|/* Motorola MTX */
DECL|variable|__prepdata
r_static
r_char
id|MTX_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|3
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|2
comma
multiline_comment|/* Slot 14 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|9
comma
multiline_comment|/* Slot 16 - PCI/PMC slot 1 */
l_int|10
comma
multiline_comment|/* Slot 17 - PCI/PMC slot 2 */
l_int|11
comma
multiline_comment|/* Slot 18 - PCI slot 3 */
l_int|0
comma
multiline_comment|/* Slot 19 - unused */
l_int|0
comma
multiline_comment|/* Slot 20 - unused */
l_int|0
comma
multiline_comment|/* Slot 21 - unused */
l_int|0
comma
multiline_comment|/* Slot 22 - unused */
)brace
suffix:semicolon
multiline_comment|/* Motorola MTX Plus */
multiline_comment|/* Secondary bus interrupt routing is not supported yet */
DECL|variable|__prepdata
r_static
r_char
id|MTXplus_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|3
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|2
comma
multiline_comment|/* Slot 14 - Ethernet 1 */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|9
comma
multiline_comment|/* Slot 16 - PCI slot 1P */
l_int|10
comma
multiline_comment|/* Slot 17 - PCI slot 2P */
l_int|11
comma
multiline_comment|/* Slot 18 - PCI slot 3P */
l_int|10
comma
multiline_comment|/* Slot 19 - Ethernet 2 */
l_int|0
comma
multiline_comment|/* Slot 20 - P2P Bridge */
l_int|0
comma
multiline_comment|/* Slot 21 - unused */
l_int|0
comma
multiline_comment|/* Slot 22 - unused */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Raven_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* This is a dummy structure */
)brace
suffix:semicolon
multiline_comment|/* Motorola MVME16xx */
DECL|variable|__prepdata
r_static
r_char
id|Genesis_pci_IRQ_map
(braket
l_int|16
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|3
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|1
comma
multiline_comment|/* Slot 14 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Genesis_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|10
comma
multiline_comment|/* Line 1 */
l_int|11
comma
multiline_comment|/* Line 2 */
l_int|14
comma
multiline_comment|/* Line 3 */
l_int|15
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Genesis2_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 11 - Universe PCI - VME Bridge */
l_int|3
comma
multiline_comment|/* Slot 12 - unused */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|2
comma
multiline_comment|/* Slot 14 - SCSI */
l_int|0
comma
multiline_comment|/* Slot 15 - graphics on 3600 */
l_int|9
comma
multiline_comment|/* Slot 16 - PMC */
l_int|12
comma
multiline_comment|/* Slot 17 - pci */
l_int|11
comma
multiline_comment|/* Slot 18 - pci */
l_int|10
comma
multiline_comment|/* Slot 19 - pci */
l_int|0
comma
multiline_comment|/* Slot 20 - pci */
l_int|0
comma
multiline_comment|/* Slot 21 - unused */
l_int|0
comma
multiline_comment|/* Slot 22 - unused */
)brace
suffix:semicolon
multiline_comment|/* Motorola Series-E */
DECL|variable|__prepdata
r_static
r_char
id|Comet_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|3
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|1
comma
multiline_comment|/* Slot 14 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|1
comma
multiline_comment|/* Slot 16 - PCI slot 1 */
l_int|2
comma
multiline_comment|/* Slot 17 - PCI slot 2 */
l_int|3
comma
multiline_comment|/* Slot 18 - PCI slot 3 */
l_int|4
comma
multiline_comment|/* Slot 19 - PCI bridge */
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Comet_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|10
comma
multiline_comment|/* Line 1 */
l_int|11
comma
multiline_comment|/* Line 2 */
l_int|14
comma
multiline_comment|/* Line 3 */
l_int|15
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* Motorola Series-EX */
DECL|variable|__prepdata
r_static
r_char
id|Comet2_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|3
comma
multiline_comment|/* Slot 2  - SCSI - NCR825A */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|1
comma
multiline_comment|/* Slot 4  - Ethernet - DEC2104X */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|1
comma
multiline_comment|/* Slot 6  - PCI slot 1 */
l_int|2
comma
multiline_comment|/* Slot 7  - PCI slot 2 */
l_int|3
comma
multiline_comment|/* Slot 8  - PCI slot 3 */
l_int|4
comma
multiline_comment|/* Slot 9  - PCI bridge  */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|3
comma
multiline_comment|/* Slot 12 - SCSI - NCR825A */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|1
comma
multiline_comment|/* Slot 14 - Ethernet - DEC2104X */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|1
comma
multiline_comment|/* Slot 16 - PCI slot 1 */
l_int|2
comma
multiline_comment|/* Slot 17 - PCI slot 2 */
l_int|3
comma
multiline_comment|/* Slot 18 - PCI slot 3 */
l_int|4
comma
multiline_comment|/* Slot 19 - PCI bridge */
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Comet2_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|10
comma
multiline_comment|/* Line 1 */
l_int|11
comma
multiline_comment|/* Line 2 */
l_int|14
comma
multiline_comment|/* Line 3 */
l_int|15
comma
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/*&n; * ibm 830 (and 850?).&n; * This is actually based on the Carolina motherboard&n; * -- Cort&n; */
DECL|variable|__prepdata
r_static
r_char
id|ibm8xx_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - FireCoral */
l_int|4
comma
multiline_comment|/* Slot 12 - Ethernet  PCIINTD# */
l_int|2
comma
multiline_comment|/* Slot 13 - PCI Slot #2 */
l_int|2
comma
multiline_comment|/* Slot 14 - S3 Video PCIINTD# */
l_int|0
comma
multiline_comment|/* Slot 15 - onboard SCSI (INDI) [1] */
l_int|3
comma
multiline_comment|/* Slot 16 - NCR58C810 RS6000 Only PCIINTC# */
l_int|0
comma
multiline_comment|/* Slot 17 - unused */
l_int|2
comma
multiline_comment|/* Slot 18 - PCI Slot 2 PCIINTx# (See below) */
l_int|0
comma
multiline_comment|/* Slot 19 - unused */
l_int|0
comma
multiline_comment|/* Slot 20 - unused */
l_int|0
comma
multiline_comment|/* Slot 21 - unused */
l_int|2
comma
multiline_comment|/* Slot 22 - PCI slot 1 PCIINTx# (See below) */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|ibm8xx_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - unused */
l_int|13
comma
multiline_comment|/* Line 1 */
l_int|10
comma
multiline_comment|/* Line 2 */
l_int|15
comma
multiline_comment|/* Line 3 */
l_int|15
comma
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/*&n; * a 6015 ibm board&n; * -- Cort&n; */
DECL|variable|__prepdata
r_static
r_char
id|ibm6015_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 -  */
l_int|1
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|2
comma
multiline_comment|/* Slot 13 -  */
l_int|2
comma
multiline_comment|/* Slot 14 -  */
l_int|1
comma
multiline_comment|/* Slot 15 -  */
l_int|1
comma
multiline_comment|/* Slot 16 -  */
l_int|0
comma
multiline_comment|/* Slot 17 -  */
l_int|2
comma
multiline_comment|/* Slot 18 -  */
l_int|0
comma
multiline_comment|/* Slot 19 -  */
l_int|0
comma
multiline_comment|/* Slot 20 -  */
l_int|0
comma
multiline_comment|/* Slot 21 -  */
l_int|2
comma
multiline_comment|/* Slot 22 -  */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|ibm6015_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - unused */
l_int|13
comma
multiline_comment|/* Line 1 */
l_int|10
comma
multiline_comment|/* Line 2 */
l_int|15
comma
multiline_comment|/* Line 3 */
l_int|15
comma
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* IBM Nobis and 850 */
DECL|variable|__prepdata
r_static
r_char
id|Nobis_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
initialization_block
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Nobis_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|13
comma
multiline_comment|/* Line 1 */
l_int|13
comma
multiline_comment|/* Line 2 */
l_int|13
comma
multiline_comment|/* Line 3 */
l_int|13
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* We have to turn on LEVEL mode for changed IRQ&squot;s */
multiline_comment|/* All PCI IRQ&squot;s need to be level mode, so this should be something&n; * other than hard-coded as well... IRQ&squot;s are individually mappable&n; * to either edge or level.&n; */
DECL|macro|CAROLINA_IRQ_EDGE_MASK_LO
mdefine_line|#define CAROLINA_IRQ_EDGE_MASK_LO   0x00  /* IRQ&squot;s 0-7  */
DECL|macro|CAROLINA_IRQ_EDGE_MASK_HI
mdefine_line|#define CAROLINA_IRQ_EDGE_MASK_HI   0xA4  /* IRQ&squot;s 8-15 [10,13,15] */
multiline_comment|/*&n; * 8259 edge/level control definitions&n; */
DECL|macro|ISA8259_M_ELCR
mdefine_line|#define ISA8259_M_ELCR 0x4d0
DECL|macro|ISA8259_S_ELCR
mdefine_line|#define ISA8259_S_ELCR 0x4d1
DECL|macro|ELCRS_INT15_LVL
mdefine_line|#define ELCRS_INT15_LVL         0x80
DECL|macro|ELCRS_INT14_LVL
mdefine_line|#define ELCRS_INT14_LVL         0x40
DECL|macro|ELCRS_INT12_LVL
mdefine_line|#define ELCRS_INT12_LVL         0x10
DECL|macro|ELCRS_INT11_LVL
mdefine_line|#define ELCRS_INT11_LVL         0x08
DECL|macro|ELCRS_INT10_LVL
mdefine_line|#define ELCRS_INT10_LVL         0x04
DECL|macro|ELCRS_INT9_LVL
mdefine_line|#define ELCRS_INT9_LVL          0x02
DECL|macro|ELCRS_INT8_LVL
mdefine_line|#define ELCRS_INT8_LVL          0x01
DECL|macro|ELCRM_INT7_LVL
mdefine_line|#define ELCRM_INT7_LVL          0x80
DECL|macro|ELCRM_INT5_LVL
mdefine_line|#define ELCRM_INT5_LVL          0x20
DECL|macro|CFGPTR
mdefine_line|#define CFGPTR(dev) (0x80800000 | (1&lt;&lt;(dev&gt;&gt;3)) | ((dev&amp;7)&lt;&lt;8) | offset)
DECL|macro|DEVNO
mdefine_line|#define DEVNO(dev)  (dev&gt;&gt;3)                                  
id|__prep
r_int
DECL|function|prep_pcibios_read_config_dword
id|prep_pcibios_read_config_dword
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_int
r_int
id|_val
suffix:semicolon
r_int
r_int
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
op_star
id|val
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|_val
op_assign
id|le32_to_cpu
c_func
(paren
op_star
id|ptr
)paren
suffix:semicolon
)brace
op_star
id|val
op_assign
id|_val
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|__prep
r_int
DECL|function|prep_pcibios_read_config_word
id|prep_pcibios_read_config_word
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_int
r_int
id|_val
suffix:semicolon
r_int
r_int
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
op_star
id|val
op_assign
l_int|0xFFFF
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|_val
op_assign
id|le16_to_cpu
c_func
(paren
op_star
id|ptr
)paren
suffix:semicolon
)brace
op_star
id|val
op_assign
id|_val
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|__prep
r_int
DECL|function|prep_pcibios_read_config_byte
id|prep_pcibios_read_config_byte
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_char
op_star
id|val
)paren
(brace
r_int
r_char
id|_val
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
op_star
id|val
op_assign
l_int|0xFF
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|_val
op_assign
op_star
id|ptr
suffix:semicolon
)brace
op_star
id|val
op_assign
id|_val
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|__prep
r_int
DECL|function|prep_pcibios_write_config_dword
id|prep_pcibios_write_config_dword
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|_val
suffix:semicolon
r_int
r_int
op_star
id|ptr
suffix:semicolon
id|_val
op_assign
id|le32_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
op_star
id|ptr
op_assign
id|_val
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|__prep
r_int
DECL|function|prep_pcibios_write_config_word
id|prep_pcibios_write_config_word
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|_val
suffix:semicolon
r_int
r_int
op_star
id|ptr
suffix:semicolon
id|_val
op_assign
id|le16_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
op_star
id|ptr
op_assign
id|_val
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|__prep
r_int
DECL|function|prep_pcibios_write_config_byte
id|prep_pcibios_write_config_byte
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_char
id|val
)paren
(brace
r_int
r_char
id|_val
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|_val
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
op_star
id|ptr
op_assign
id|_val
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|macro|MOTOROLA_CPUTYPE_REG
mdefine_line|#define MOTOROLA_CPUTYPE_REG&t;0x800
DECL|macro|MOTOROLA_BASETYPE_REG
mdefine_line|#define MOTOROLA_BASETYPE_REG&t;0x803
DECL|macro|MPIC_RAVEN_ID
mdefine_line|#define MPIC_RAVEN_ID&t;&t;0x48010000
DECL|macro|MPIC_HAWK_ID
mdefine_line|#define&t;MPIC_HAWK_ID&t;&t;0x48030000
DECL|macro|MOT_PROC2_BIT
mdefine_line|#define&t;MOT_PROC2_BIT&t;&t;0x800
DECL|variable|__initdata
r_static
id|u_char
id|mvme2600_openpic_initsenses
(braket
)braket
id|__initdata
op_assign
(brace
l_int|1
comma
multiline_comment|/* MVME2600_INT_SIO */
l_int|0
comma
multiline_comment|/* MVME2600_INT_FALCN_ECC_ERR */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_ETHERNET */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_SCSI */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_GRAPHICS */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_VME0 */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_VME1 */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_VME2 */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_VME3 */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_INTA */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_INTB */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_INTC */
l_int|1
comma
multiline_comment|/* MVME2600_INT_PCI_INTD */
l_int|1
comma
multiline_comment|/* MVME2600_INT_LM_SIG0 */
l_int|1
comma
multiline_comment|/* MVME2600_INT_LM_SIG1 */
)brace
suffix:semicolon
DECL|macro|MOT_RAVEN_PRESENT
mdefine_line|#define MOT_RAVEN_PRESENT&t;0x1
DECL|macro|MOT_HAWK_PRESENT
mdefine_line|#define MOT_HAWK_PRESENT&t;0x2
DECL|variable|prep_keybd_present
r_int
id|prep_keybd_present
op_assign
l_int|1
suffix:semicolon
DECL|variable|MotMPIC
r_int
id|MotMPIC
op_assign
l_int|0
suffix:semicolon
DECL|function|raven_init
r_int
id|__init
id|raven_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|devid
suffix:semicolon
r_int
r_int
id|pci_membase
suffix:semicolon
r_int
r_char
id|base_mod
suffix:semicolon
multiline_comment|/* Check to see if the Raven chip exists. */
r_if
c_cond
(paren
id|_prep_type
op_ne
id|_PREP_Motorola
)paren
(brace
id|OpenPIC
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Check to see if this board is a type that might have a Raven. */
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|MOTOROLA_CPUTYPE_REG
)paren
op_amp
l_int|0xF0
)paren
op_ne
l_int|0xE0
)paren
(brace
id|OpenPIC
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Check the first PCI device to see if it is a Raven. */
id|pcibios_read_config_dword
c_func
(paren
l_int|0
comma
l_int|0
comma
id|PCI_VENDOR_ID
comma
op_amp
id|devid
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|devid
op_amp
l_int|0xffff0000
)paren
(brace
r_case
id|MPIC_RAVEN_ID
suffix:colon
id|MotMPIC
op_assign
id|MOT_RAVEN_PRESENT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MPIC_HAWK_ID
suffix:colon
id|MotMPIC
op_assign
id|MOT_HAWK_PRESENT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|OpenPIC
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Read the memory base register. */
id|pcibios_read_config_dword
c_func
(paren
l_int|0
comma
l_int|0
comma
id|PCI_BASE_ADDRESS_1
comma
op_amp
id|pci_membase
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_membase
op_eq
l_int|0
)paren
(brace
id|OpenPIC
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Map the Raven MPIC registers to virtual memory. */
id|OpenPIC
op_assign
(paren
r_struct
id|OpenPIC
op_star
)paren
id|ioremap
c_func
(paren
id|pci_membase
op_plus
l_int|0xC0000000
comma
l_int|0x22000
)paren
suffix:semicolon
id|OpenPIC_InitSenses
op_assign
id|mvme2600_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|mvme2600_openpic_initsenses
)paren
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|chrp_get_irq
suffix:semicolon
id|ppc_md.post_irq
op_assign
id|chrp_post_irq
suffix:semicolon
multiline_comment|/* If raven is present on Motorola store the system config register&n;&t; * for later use.&n;&t; */
id|ProcInfo
op_assign
(paren
r_int
r_int
op_star
)paren
id|ioremap
c_func
(paren
l_int|0xfef80400
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* This is a hack.  If this is a 2300 or 2400 mot board then there is&n;&t; * no keyboard controller and we have to indicate that.&n;&t; */
id|base_mod
op_assign
id|inb
c_func
(paren
id|MOTOROLA_BASETYPE_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|MotMPIC
op_eq
id|MOT_HAWK_PRESENT
)paren
op_logical_or
(paren
id|base_mod
op_eq
l_int|0xF9
)paren
op_logical_or
(paren
id|base_mod
op_eq
l_int|0xFA
)paren
op_logical_or
(paren
id|base_mod
op_eq
l_int|0xE1
)paren
)paren
id|prep_keybd_present
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|struct|mot_info
r_struct
id|mot_info
(brace
DECL|member|cpu_type
r_int
id|cpu_type
suffix:semicolon
multiline_comment|/* 0x100 mask assumes for Raven and Hawk boards that the level/edge are set */
multiline_comment|/* 0x200 if this board has a Hawk chip. */
DECL|member|base_type
r_int
id|base_type
suffix:semicolon
DECL|member|max_cpu
r_int
id|max_cpu
suffix:semicolon
multiline_comment|/* ored with 0x80 if this board should be checked for multi CPU */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|map
r_int
r_char
op_star
id|map
suffix:semicolon
DECL|member|routes
r_int
r_char
op_star
id|routes
suffix:semicolon
DECL|variable|mot_info
)brace
id|mot_info
(braket
)braket
op_assign
(brace
(brace
l_int|0x300
comma
l_int|0x00
comma
l_int|0x00
comma
l_string|&quot;MVME 2400&quot;
comma
id|Genesis2_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x010
comma
l_int|0x00
comma
l_int|0x00
comma
l_string|&quot;Genesis&quot;
comma
id|Genesis_pci_IRQ_map
comma
id|Genesis_pci_IRQ_routes
)brace
comma
(brace
l_int|0x020
comma
l_int|0x00
comma
l_int|0x00
comma
l_string|&quot;Powerstack (Series E)&quot;
comma
id|Comet_pci_IRQ_map
comma
id|Comet_pci_IRQ_routes
)brace
comma
(brace
l_int|0x040
comma
l_int|0x00
comma
l_int|0x00
comma
l_string|&quot;Blackhawk (Powerstack)&quot;
comma
id|Blackhawk_pci_IRQ_map
comma
id|Blackhawk_pci_IRQ_routes
)brace
comma
(brace
l_int|0x050
comma
l_int|0x00
comma
l_int|0x00
comma
l_string|&quot;Omaha (PowerStack II Pro3000)&quot;
comma
id|Omaha_pci_IRQ_map
comma
id|Omaha_pci_IRQ_routes
)brace
comma
(brace
l_int|0x060
comma
l_int|0x00
comma
l_int|0x00
comma
l_string|&quot;Utah (Powerstack II Pro4000)&quot;
comma
id|Utah_pci_IRQ_map
comma
id|Utah_pci_IRQ_routes
)brace
comma
(brace
l_int|0x0A0
comma
l_int|0x00
comma
l_int|0x00
comma
l_string|&quot;Powerstack (Series EX)&quot;
comma
id|Comet2_pci_IRQ_map
comma
id|Comet2_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xE0
comma
l_int|0x00
comma
l_string|&quot;Mesquite cPCI (MCP750)&quot;
comma
id|Mesquite_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xE1
comma
l_int|0x00
comma
l_string|&quot;Sitka cPCI (MCPN750)&quot;
comma
id|Sitka_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xE2
comma
l_int|0x00
comma
l_string|&quot;Mesquite cPCI (MCP750) w/ HAC&quot;
comma
id|Mesquite_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xF6
comma
l_int|0x80
comma
l_string|&quot;MTX Plus&quot;
comma
id|MTXplus_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xF6
comma
l_int|0x81
comma
l_string|&quot;Dual MTX Plus&quot;
comma
id|MTXplus_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xF7
comma
l_int|0x80
comma
l_string|&quot;MTX wo/ Parallel Port&quot;
comma
id|MTX_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xF7
comma
l_int|0x81
comma
l_string|&quot;Dual MTX wo/ Parallel Port&quot;
comma
id|MTX_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xF8
comma
l_int|0x80
comma
l_string|&quot;MTX w/ Parallel Port&quot;
comma
id|MTX_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xF8
comma
l_int|0x81
comma
l_string|&quot;Dual MTX w/ Parallel Port&quot;
comma
id|MTX_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xF9
comma
l_int|0x00
comma
l_string|&quot;MVME 2300&quot;
comma
id|Genesis2_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xFA
comma
l_int|0x00
comma
l_string|&quot;MVME 2300SC/2600&quot;
comma
id|Genesis2_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xFB
comma
l_int|0x00
comma
l_string|&quot;MVME 2600 with MVME712M&quot;
comma
id|Genesis2_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xFC
comma
l_int|0x00
comma
l_string|&quot;MVME 2600/2700 with MVME761&quot;
comma
id|Genesis2_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xFD
comma
l_int|0x80
comma
l_string|&quot;MVME 3600 with MVME712M&quot;
comma
id|Genesis2_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xFD
comma
l_int|0x81
comma
l_string|&quot;MVME 4600 with MVME712M&quot;
comma
id|Genesis2_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xFE
comma
l_int|0x80
comma
l_string|&quot;MVME 3600 with MVME761&quot;
comma
id|Genesis2_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xFE
comma
l_int|0x81
comma
l_string|&quot;MVME 4600 with MVME761&quot;
comma
id|Genesis2_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x1E0
comma
l_int|0xFF
comma
l_int|0x00
comma
l_string|&quot;MVME 1600-001 or 1600-011&quot;
comma
id|Genesis2_pci_IRQ_map
comma
id|Raven_pci_IRQ_routes
)brace
comma
(brace
l_int|0x000
comma
l_int|0x00
comma
l_int|0x00
comma
l_string|&quot;&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|prep_route_pci_interrupts
r_int
r_int
id|__init
id|prep_route_pci_interrupts
c_func
(paren
r_void
)paren
(brace
r_int
r_char
op_star
id|ibc_pirq
op_assign
(paren
r_int
r_char
op_star
)paren
l_int|0x80800860
suffix:semicolon
r_int
r_char
op_star
id|ibc_pcicon
op_assign
(paren
r_int
r_char
op_star
)paren
l_int|0x80800840
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|_prep_type
op_eq
id|_PREP_Motorola
)paren
(brace
r_int
r_int
id|irq_mode
suffix:semicolon
r_int
r_char
id|cpu_type
suffix:semicolon
r_int
r_char
id|base_mod
suffix:semicolon
r_int
id|entry
suffix:semicolon
r_int
id|mot_entry
op_assign
op_minus
l_int|1
suffix:semicolon
id|cpu_type
op_assign
id|inb
c_func
(paren
id|MOTOROLA_CPUTYPE_REG
)paren
op_amp
l_int|0xF0
suffix:semicolon
id|base_mod
op_assign
id|inb
c_func
(paren
id|MOTOROLA_BASETYPE_REG
)paren
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
l_int|0
suffix:semicolon
id|mot_info
(braket
id|entry
)braket
dot
id|cpu_type
op_ne
l_int|0
suffix:semicolon
id|entry
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mot_info
(braket
id|entry
)braket
dot
id|cpu_type
op_amp
l_int|0x200
)paren
(brace
multiline_comment|/* Check for Hawk chip */
r_if
c_cond
(paren
op_logical_neg
(paren
id|MotMPIC
op_amp
id|MOT_HAWK_PRESENT
)paren
)paren
r_continue
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Check non hawk boards */
r_if
c_cond
(paren
(paren
id|mot_info
(braket
id|entry
)braket
dot
id|cpu_type
op_amp
l_int|0xff
)paren
op_ne
id|cpu_type
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|mot_info
(braket
id|entry
)braket
dot
id|base_type
op_eq
l_int|0
)paren
(brace
id|mot_entry
op_assign
id|entry
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mot_info
(braket
id|entry
)braket
dot
id|base_type
op_ne
id|base_mod
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mot_info
(braket
id|entry
)braket
dot
id|max_cpu
op_amp
l_int|0x80
)paren
)paren
(brace
id|mot_entry
op_assign
id|entry
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* processor 1 not present and max processor zero indicated */
r_if
c_cond
(paren
(paren
op_star
id|ProcInfo
op_amp
id|MOT_PROC2_BIT
)paren
op_logical_and
op_logical_neg
(paren
id|mot_info
(braket
id|entry
)braket
dot
id|max_cpu
op_amp
l_int|0x7f
)paren
)paren
(brace
id|mot_entry
op_assign
id|entry
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* processor 1 present and max processor zero indicated */
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|ProcInfo
op_amp
id|MOT_PROC2_BIT
)paren
op_logical_and
(paren
id|mot_info
(braket
id|entry
)braket
dot
id|max_cpu
op_amp
l_int|0x7f
)paren
)paren
(brace
id|mot_entry
op_assign
id|entry
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mot_entry
op_eq
op_minus
l_int|1
)paren
multiline_comment|/* No particular cpu type found - assume Blackhawk */
id|mot_entry
op_assign
l_int|3
suffix:semicolon
id|Motherboard_map_name
op_assign
(paren
r_int
r_char
op_star
)paren
id|mot_info
(braket
id|mot_entry
)braket
dot
id|name
suffix:semicolon
id|Motherboard_map
op_assign
id|mot_info
(braket
id|mot_entry
)braket
dot
id|map
suffix:semicolon
id|Motherboard_routes
op_assign
id|mot_info
(braket
id|mot_entry
)braket
dot
id|routes
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mot_info
(braket
id|entry
)braket
dot
id|cpu_type
op_amp
l_int|0x100
)paren
)paren
(brace
multiline_comment|/* AJF adjust level/edge control according to routes */
id|irq_mode
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_mode
op_or_assign
(paren
l_int|1
op_lshift
id|Motherboard_routes
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|irq_mode
op_amp
l_int|0xff
comma
l_int|0x4d0
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|irq_mode
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
l_int|0x4d1
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|_prep_type
op_eq
id|_PREP_IBM
)paren
(brace
r_int
r_char
id|pl_id
suffix:semicolon
multiline_comment|/*&n;&t;&t; * my carolina is 0xf0&n;&t;&t; * 6015 has 0xfc&n;&t;&t; * -- Cort&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;IBM ID: %08x&bslash;n&quot;
comma
id|inb
c_func
(paren
l_int|0x0852
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|inb
c_func
(paren
l_int|0x0852
)paren
)paren
(brace
r_case
l_int|0xff
suffix:colon
id|Motherboard_map_name
op_assign
l_string|&quot;IBM 850/860 Portable&bslash;n&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|Nobis_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|Nobis_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xfc
suffix:colon
id|Motherboard_map_name
op_assign
l_string|&quot;IBM 6015&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|ibm6015_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|ibm6015_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|Motherboard_map_name
op_assign
l_string|&quot;IBM 8xx (Carolina)&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|ibm8xx_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|ibm8xx_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*printk(&quot;Changing IRQ mode&bslash;n&quot;);*/
id|pl_id
op_assign
id|inb
c_func
(paren
l_int|0x04d0
)paren
suffix:semicolon
multiline_comment|/*printk(&quot;Low mask is %#0x&bslash;n&quot;, pl_id);*/
id|outb
c_func
(paren
id|pl_id
op_or
id|CAROLINA_IRQ_EDGE_MASK_LO
comma
l_int|0x04d0
)paren
suffix:semicolon
id|pl_id
op_assign
id|inb
c_func
(paren
l_int|0x04d1
)paren
suffix:semicolon
multiline_comment|/*printk(&quot;Hi mask is  %#0x&bslash;n&quot;, pl_id);*/
id|outb
c_func
(paren
id|pl_id
op_or
id|CAROLINA_IRQ_EDGE_MASK_HI
comma
l_int|0x04d1
)paren
suffix:semicolon
id|pl_id
op_assign
id|inb
c_func
(paren
l_int|0x04d1
)paren
suffix:semicolon
multiline_comment|/*printk(&quot;Hi mask now %#0x&bslash;n&quot;, pl_id);*/
)brace
r_else
r_if
c_cond
(paren
id|_prep_type
op_eq
id|_PREP_Radstone
)paren
(brace
r_int
r_char
id|ucElcrM
comma
id|ucElcrS
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set up edge/level&n;&t;&t; */
r_switch
c_cond
(paren
id|ucSystemType
)paren
(brace
r_case
id|RS_SYS_TYPE_PPC1
suffix:colon
(brace
r_if
c_cond
(paren
id|ucBoardRevMaj
OL
l_int|5
)paren
(brace
id|ucElcrS
op_assign
id|ELCRS_INT15_LVL
suffix:semicolon
)brace
r_else
(brace
id|ucElcrS
op_assign
id|ELCRS_INT9_LVL
op_or
id|ELCRS_INT11_LVL
op_or
id|ELCRS_INT14_LVL
op_or
id|ELCRS_INT15_LVL
suffix:semicolon
)brace
id|ucElcrM
op_assign
id|ELCRM_INT5_LVL
op_or
id|ELCRM_INT7_LVL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|RS_SYS_TYPE_PPC1a
suffix:colon
(brace
id|ucElcrS
op_assign
id|ELCRS_INT9_LVL
op_or
id|ELCRS_INT11_LVL
op_or
id|ELCRS_INT14_LVL
op_or
id|ELCRS_INT15_LVL
suffix:semicolon
id|ucElcrM
op_assign
id|ELCRM_INT5_LVL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|RS_SYS_TYPE_PPC2
suffix:colon
r_case
id|RS_SYS_TYPE_PPC2a
suffix:colon
r_case
id|RS_SYS_TYPE_PPC2ep
suffix:colon
r_case
id|RS_SYS_TYPE_PPC4
suffix:colon
r_case
id|RS_SYS_TYPE_PPC4a
suffix:colon
r_default
suffix:colon
(brace
)brace
(brace
id|ucElcrS
op_assign
id|ELCRS_INT9_LVL
op_or
id|ELCRS_INT10_LVL
op_or
id|ELCRS_INT11_LVL
op_or
id|ELCRS_INT14_LVL
op_or
id|ELCRS_INT15_LVL
suffix:semicolon
id|ucElcrM
op_assign
id|ELCRM_INT5_LVL
op_or
id|ELCRM_INT7_LVL
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Write edge/level selection&n;&t;&t; */
id|outb
c_func
(paren
id|ucElcrS
comma
id|ISA8259_S_ELCR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ucElcrM
comma
id|ISA8259_M_ELCR
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Radstone boards have PCI interrupts all set up&n;&t;&t; * so leave well alone&n;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;No known machine pci routing!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Set up mapping from slots */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ibc_pirq
(braket
id|i
op_minus
l_int|1
)braket
op_assign
id|Motherboard_routes
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* Enable PCI interrupts */
op_star
id|ibc_pcicon
op_or_assign
l_int|0x20
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|prep_pcibios_fixup
id|prep_pcibios_fixup
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_extern
r_int
r_char
op_star
id|Motherboard_map
suffix:semicolon
r_extern
r_int
r_char
op_star
id|Motherboard_routes
suffix:semicolon
r_int
r_char
id|i
suffix:semicolon
r_if
c_cond
(paren
id|_prep_type
op_eq
id|_PREP_Radstone
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Radstone boards require no PCI fixups&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|prep_route_pci_interrupts
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Setting PCI interrupts for a &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|Motherboard_map_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|OpenPIC
)paren
(brace
multiline_comment|/* PCI interrupts are controlled by the OpenPIC */
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
)paren
(brace
id|dev-&gt;irq
op_assign
id|openpic_to_irq
c_func
(paren
id|Motherboard_map
(braket
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)braket
)paren
suffix:semicolon
id|pcibios_write_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_INTERRUPT_PIN
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
multiline_comment|/*&n;&t;&t; * Use our old hard-coded kludge to figure out what&n;&t;&t; * irq this device uses.  This is necessary on things&n;&t;&t; * without residual data. -- Cort&n;&t;&t; */
r_int
r_char
id|d
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|Motherboard_routes
(braket
id|Motherboard_map
(braket
id|d
)braket
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
OG
l_int|0x10000000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Relocating PCI address %lx -&gt; %lx&bslash;n&quot;
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
comma
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_amp
l_int|0x00FFFFFF
)paren
op_or
l_int|0x01000000
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_amp
l_int|0x00FFFFFF
)paren
op_or
l_int|0x01000000
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|i
op_star
l_int|0x4
)paren
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
)paren
suffix:semicolon
)brace
)brace
macro_line|#if 0
multiline_comment|/*&n;&t;&t; * If we have residual data and if it knows about this&n;&t;&t; * device ask it what the irq is.&n;&t;&t; *  -- Cort&n;&t;&t; */
id|ppcd
op_assign
id|residual_find_device_id
c_func
(paren
op_complement
l_int|0L
comma
id|dev-&gt;device
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|variable|indirect
id|decl_config_access_method
c_func
(paren
id|indirect
)paren
suffix:semicolon
r_void
id|__init
DECL|function|prep_setup_pci_ptrs
id|prep_setup_pci_ptrs
c_func
(paren
r_void
)paren
(brace
id|PPC_DEVICE
op_star
id|hostbridge
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PReP architecture&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_prep_type
op_eq
id|_PREP_Radstone
)paren
(brace
id|pci_config_address
op_assign
(paren
r_int
op_star
)paren
l_int|0x80000cf8
suffix:semicolon
id|pci_config_data
op_assign
(paren
r_char
op_star
)paren
l_int|0x80000cfc
suffix:semicolon
id|set_config_access_method
c_func
(paren
id|indirect
)paren
suffix:semicolon
)brace
r_else
(brace
id|hostbridge
op_assign
id|residual_find_device
c_func
(paren
id|PROCESSORDEVICE
comma
l_int|NULL
comma
id|BridgeController
comma
id|PCIBridge
comma
op_minus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hostbridge
op_logical_and
id|hostbridge-&gt;DeviceId.Interface
op_eq
id|PCIBridgeIndirect
)paren
(brace
id|PnP_TAG_PACKET
op_star
id|pkt
suffix:semicolon
id|set_config_access_method
c_func
(paren
id|indirect
)paren
suffix:semicolon
id|pkt
op_assign
id|PnP_find_large_vendor_packet
c_func
(paren
id|res-&gt;DevicePnPHeap
op_plus
id|hostbridge-&gt;AllocatedOffset
comma
l_int|3
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pkt
)paren
(brace
DECL|macro|p
mdefine_line|#define p pkt-&gt;L4_Pack.L4_Data.L4_PPCPack
id|pci_config_address
op_assign
(paren
r_int
op_star
)paren
id|ld_le32
c_func
(paren
(paren
r_int
op_star
)paren
id|p.PPCData
)paren
suffix:semicolon
id|pci_config_data
op_assign
(paren
r_int
r_char
op_star
)paren
id|ld_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|p.PPCData
op_plus
l_int|8
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|pci_config_address
op_assign
(paren
r_int
op_star
)paren
l_int|0x80000cf8
suffix:semicolon
id|pci_config_data
op_assign
(paren
r_int
r_char
op_star
)paren
l_int|0x80000cfc
suffix:semicolon
)brace
)brace
r_else
(brace
id|set_config_access_method
c_func
(paren
id|prep
)paren
suffix:semicolon
)brace
)brace
id|ppc_md.pcibios_fixup
op_assign
id|prep_pcibios_fixup
suffix:semicolon
)brace
eof
