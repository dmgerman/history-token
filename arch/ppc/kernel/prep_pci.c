multiline_comment|/*&n; * BK Id: SCCS/s.prep_pci.c 1.18 05/17/01 18:14:22 cort&n; */
multiline_comment|/*&n; * PReP pci functions.&n; * Originally by Gary Thomas&n; * rewritten and updated by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * The motherboard routes/maps will disappear shortly. -- Cort&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
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
macro_line|#include &quot;open_pic.h&quot;
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
DECL|variable|Motherboard_non0
r_void
(paren
op_star
id|Motherboard_non0
)paren
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_void
id|Powerplus_Map_Non0
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
multiline_comment|/* Used for Motorola to store system config register */
DECL|variable|ProcInfo
r_static
r_int
r_int
op_star
id|ProcInfo
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
l_int|15
comma
multiline_comment|/* Line 1 */
l_int|15
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
multiline_comment|/* Motorola PowerPlus architecture PCI IRQ tables */
multiline_comment|/* Interrupt line values for INTA-D on primary/secondary MPIC inputs */
DECL|struct|powerplus_irq_list
r_struct
id|powerplus_irq_list
(brace
DECL|member|primary
r_int
r_char
id|primary
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* INT A-D */
DECL|member|secondary
r_int
r_char
id|secondary
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* INT A-D */
)brace
suffix:semicolon
multiline_comment|/*&n; * For standard PowerPlus boards, bus 0 PCI INTs A-D are routed to&n; * OpenPIC inputs 9-12.  PCI INTs A-D from the on board P2P bridge&n; * are routed to OpenPIC inputs 5-8.  These values are offset by&n; * 16 in the table to reflect the Linux kernel interrupt value.&n; */
DECL|variable|Powerplus_pci_IRQ_list
r_struct
id|powerplus_irq_list
id|Powerplus_pci_IRQ_list
op_assign
(brace
(brace
l_int|25
comma
l_int|26
comma
l_int|27
comma
l_int|28
)brace
comma
(brace
l_int|21
comma
l_int|22
comma
l_int|23
comma
l_int|24
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * For the MCP750 (system slot board), cPCI INTs A-D are routed to&n; * OpenPIC inputs 8-11 and the PMC INTs A-D are routed to OpenPIC&n; * input 3.  On a hot swap MCP750, the companion card PCI INTs A-D&n; * are routed to OpenPIC inputs 12-15. These values are offset by&n; * 16 in the table to reflect the Linux kernel interrupt value.&n; */
DECL|variable|Mesquite_pci_IRQ_list
r_struct
id|powerplus_irq_list
id|Mesquite_pci_IRQ_list
op_assign
(brace
(brace
l_int|24
comma
l_int|25
comma
l_int|26
comma
l_int|27
)brace
comma
(brace
l_int|28
comma
l_int|29
comma
l_int|30
comma
l_int|31
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * This table represents the standard PCI swizzle defined in the&n; * PCI bus specification.&n; */
DECL|variable|prep_pci_intpins
r_static
r_int
r_char
id|prep_pci_intpins
(braket
l_int|4
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
)brace
comma
multiline_comment|/* Buses 0, 4, 8, ... */
(brace
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|1
)brace
comma
multiline_comment|/* Buses 1, 5, 9, ... */
(brace
l_int|3
comma
l_int|4
comma
l_int|1
comma
l_int|2
)brace
comma
multiline_comment|/* Buses 2, 6, 10 ... */
(brace
l_int|4
comma
l_int|1
comma
l_int|2
comma
l_int|3
)brace
comma
multiline_comment|/* Buses 3, 7, 11 ... */
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
DECL|macro|cfg_read
mdefine_line|#define cfg_read(val, addr, type, op)&t;*val = op((type)(addr))
DECL|macro|cfg_write
mdefine_line|#define cfg_write(val, addr, type, op)&t;op((type *)(addr), (val))
DECL|macro|cfg_read_bad
mdefine_line|#define cfg_read_bad(val, size)&t;&t;*val = bad_##size;
DECL|macro|cfg_write_bad
mdefine_line|#define cfg_write_bad(val, size)
DECL|macro|bad_byte
mdefine_line|#define bad_byte&t;0xff
DECL|macro|bad_word
mdefine_line|#define bad_word&t;0xffff
DECL|macro|bad_dword
mdefine_line|#define bad_dword&t;0xffffffffU
DECL|macro|PREP_PCI_OP
mdefine_line|#define PREP_PCI_OP(rw, size, type, op)&t;&t;&t;&t;&t;&bslash;&n;static int __prep&t;&t;&t;&t;&t;&t;&t;&bslash;&n;prep_##rw##_config_##size(struct pci_dev *dev, int offset, type val)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((dev-&gt;bus-&gt;number != 0) || (DEVNO(dev-&gt;devfn) &gt; MAX_DEVNR))&t;&bslash;&n;&t;{                   &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cfg_##rw##_bad(val, size)&t;&t;&t;&t;&bslash;&n;&t;&t;return PCIBIOS_DEVICE_NOT_FOUND;    &t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cfg_##rw(val, CFGPTR(dev-&gt;devfn), type, op);&t;&t;&t;&bslash;&n;&t;return PCIBIOS_SUCCESSFUL;&t;&t;&t;&t;&t;&bslash;&n;}
id|PREP_PCI_OP
c_func
(paren
id|read
comma
id|byte
comma
id|u8
op_star
comma
id|in_8
)paren
id|PREP_PCI_OP
c_func
(paren
id|read
comma
id|word
comma
id|u16
op_star
comma
id|in_le16
)paren
id|PREP_PCI_OP
c_func
(paren
id|read
comma
id|dword
comma
id|u32
op_star
comma
id|in_le32
)paren
id|PREP_PCI_OP
c_func
(paren
id|write
comma
id|byte
comma
id|u8
comma
id|out_8
)paren
id|PREP_PCI_OP
c_func
(paren
id|write
comma
id|word
comma
id|u16
comma
id|out_le16
)paren
id|PREP_PCI_OP
c_func
(paren
id|write
comma
id|dword
comma
id|u32
comma
id|out_le32
)paren
DECL|variable|prep_pci_ops
r_static
r_struct
id|pci_ops
id|prep_pci_ops
op_assign
(brace
id|prep_read_config_byte
comma
id|prep_read_config_word
comma
id|prep_read_config_dword
comma
id|prep_write_config_byte
comma
id|prep_write_config_word
comma
id|prep_write_config_dword
)brace
suffix:semicolon
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
DECL|variable|mot_entry
r_int
id|mot_entry
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|prep_keybd_present
r_int
id|prep_keybd_present
op_assign
l_int|1
suffix:semicolon
DECL|variable|MotMPIC
r_int
id|MotMPIC
suffix:semicolon
DECL|variable|mot_multi
r_int
id|mot_multi
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
id|OpenPIC_Addr
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
id|OpenPIC_Addr
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Check the first PCI device to see if it is a Raven. */
id|early_read_config_dword
c_func
(paren
l_int|0
comma
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
id|OpenPIC_Addr
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Read the memory base register. */
id|early_read_config_dword
c_func
(paren
l_int|0
comma
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
id|OpenPIC_Addr
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Map the Raven MPIC registers to virtual memory. */
id|OpenPIC_Addr
op_assign
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
id|openpic_get_irq
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
multiline_comment|/* Indicate to system if this is a multiprocessor board */
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
)paren
(brace
id|mot_multi
op_assign
l_int|1
suffix:semicolon
)brace
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
DECL|member|map_non0_bus
r_void
(paren
op_star
id|map_non0_bus
)paren
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
multiline_comment|/* For boards with more than bus 0 devices. */
DECL|member|pci_irq_list
r_struct
id|powerplus_irq_list
op_star
id|pci_irq_list
suffix:semicolon
multiline_comment|/* List of PCI MPIC inputs */
DECL|member|secondary_bridge_devfn
r_int
r_char
id|secondary_bridge_devfn
suffix:semicolon
multiline_comment|/* devfn of secondary bus transparent bridge */
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xFF
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0x00
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
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0x00
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
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0x00
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
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0x00
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
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0x00
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
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0x00
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Mesquite_pci_IRQ_list
comma
l_int|0xFF
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xFF
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Mesquite_pci_IRQ_list
comma
l_int|0xC0
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xA0
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xA0
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0x00
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0x00
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0x00
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0x00
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xFF
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xFF
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xFF
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xFF
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0x00
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xFF
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xFF
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xFF
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
comma
id|Powerplus_Map_Non0
comma
op_amp
id|Powerplus_pci_IRQ_list
comma
l_int|0xFF
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
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0x00
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
id|Motherboard_non0
op_assign
id|mot_info
(braket
id|mot_entry
)braket
dot
id|map_non0_bus
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
DECL|function|prep_pib_init
id|prep_pib_init
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|reg
suffix:semicolon
r_int
r_int
id|short_reg
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|_prep_type
op_eq
id|_PREP_Motorola
)paren
op_logical_and
(paren
id|OpenPIC_Addr
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Perform specific configuration for the Via Tech or&n;&t;&t; * or Winbond PCI-ISA-Bridge part.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C586_1
comma
id|dev
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * PPCBUG does not set the enable bits&n;&t;&t;&t; * for the IDE device. Force them on here.&n;&t;&t;&t; */
id|pcibios_read_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
l_int|0x40
comma
op_amp
id|reg
)paren
suffix:semicolon
id|reg
op_or_assign
l_int|0x03
suffix:semicolon
multiline_comment|/* IDE: Chip Enable Bits */
id|pcibios_write_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
l_int|0x40
comma
id|reg
)paren
suffix:semicolon
multiline_comment|/* Force correct IDE function interrupt */
id|dev-&gt;irq
op_assign
l_int|14
suffix:semicolon
id|pcibios_write_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_83C553
comma
id|dev
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Clear the PCI Interrupt Routing Control Register.&n;&t;&t;&t; */
id|short_reg
op_assign
l_int|0x0000
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x44
comma
id|short_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|OpenPIC_Addr
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Route both IDE interrupts to IRQ 14&n;&t;&t;&t;&t; */
id|reg
op_assign
l_int|0xEE
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x44
comma
id|reg
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C586_2
comma
id|dev
)paren
)paren
)paren
(brace
multiline_comment|/* Force correct USB function interrupt */
id|dev-&gt;irq
op_assign
l_int|11
suffix:semicolon
id|pcibios_write_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_82C105
comma
id|dev
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|OpenPIC_Addr
)paren
(brace
multiline_comment|/* Disable LEGIRQ mode so PCI INTs are routed to&n;&t;&t;&t;   the 8259 */
id|printk
c_func
(paren
l_string|&quot;Set winbond IDE to native mode&bslash;n&quot;
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
l_int|0x10ff00a1
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Enable LEGIRQ for PCI INT -&gt; 8259 IRQ routing */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
l_int|0x10ff08a1
)paren
suffix:semicolon
)brace
)brace
)brace
r_void
DECL|function|Powerplus_Map_Non0
id|Powerplus_Map_Non0
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pci_bus
op_star
id|pbus
suffix:semicolon
multiline_comment|/* Parent bus structure pointer */
r_struct
id|pci_dev
op_star
id|tdev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* Temporary device structure */
r_int
r_int
id|devnum
suffix:semicolon
multiline_comment|/* Accumulated device number */
r_int
r_char
id|intline
suffix:semicolon
multiline_comment|/* Linux interrupt value */
r_int
r_char
id|intpin
suffix:semicolon
multiline_comment|/* PCI interrupt pin */
multiline_comment|/* Check for valid PCI dev pointer */
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* Initialize bridge IDSEL variable */
id|devnum
op_assign
id|PCI_SLOT
c_func
(paren
id|tdev-&gt;devfn
)paren
suffix:semicolon
multiline_comment|/* Read the interrupt pin of the device and adjust for indexing */
id|pcibios_read_config_byte
c_func
(paren
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|intpin
)paren
suffix:semicolon
multiline_comment|/* If device doesn&squot;t request an interrupt, return */
r_if
c_cond
(paren
(paren
id|intpin
OL
l_int|1
)paren
op_logical_or
(paren
id|intpin
OG
l_int|4
)paren
)paren
r_return
suffix:semicolon
id|intpin
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t; * Walk up to bus 0, adjusting the interrupt pin for the standard&n;&t; * PCI bus swizzle.&n;&t; */
r_do
(brace
id|intpin
op_assign
(paren
id|prep_pci_intpins
(braket
id|devnum
op_mod
l_int|4
)braket
(braket
id|intpin
)braket
)paren
op_minus
l_int|1
suffix:semicolon
id|pbus
op_assign
id|tdev-&gt;bus
suffix:semicolon
multiline_comment|/* up one level */
id|tdev
op_assign
id|pbus-&gt;self
suffix:semicolon
id|devnum
op_assign
id|PCI_SLOT
c_func
(paren
id|tdev-&gt;devfn
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tdev-&gt;bus-&gt;number
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Use the primary interrupt inputs by default */
id|intline
op_assign
id|mot_info
(braket
id|mot_entry
)braket
dot
id|pci_irq_list-&gt;primary
(braket
id|intpin
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * If the board has secondary interrupt inputs, walk the bus and&n;&t; * note the devfn of the bridge from bus 0.  If it is the same as&n;&t; * the devfn of the bus bridge with secondary inputs, use those.&n;&t; * Otherwise, assume it&squot;s a PMC site and get the interrupt line&n;&t; * value from the interrupt routing table.&n;&t; */
r_if
c_cond
(paren
id|mot_info
(braket
id|mot_entry
)braket
dot
id|secondary_bridge_devfn
)paren
(brace
id|pbus
op_assign
id|dev-&gt;bus
suffix:semicolon
r_while
c_loop
(paren
id|pbus-&gt;primary
op_ne
l_int|0
)paren
id|pbus
op_assign
id|pbus-&gt;parent
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pbus-&gt;self
)paren
op_member_access_from_pointer
id|devfn
op_ne
l_int|0xA0
)paren
(brace
r_if
c_cond
(paren
(paren
id|pbus-&gt;self
)paren
op_member_access_from_pointer
id|devfn
op_eq
id|mot_info
(braket
id|mot_entry
)braket
dot
id|secondary_bridge_devfn
)paren
id|intline
op_assign
id|mot_info
(braket
id|mot_entry
)braket
dot
id|pci_irq_list-&gt;secondary
(braket
id|intpin
)braket
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
(paren
id|mot_info
(braket
id|mot_entry
)braket
dot
id|map
)paren
op_eq
(paren
r_char
op_star
)paren
id|Mesquite_pci_IRQ_map
)paren
id|intline
op_assign
id|mot_info
(braket
id|mot_entry
)braket
dot
id|map
(braket
(paren
(paren
id|pbus-&gt;self
)paren
op_member_access_from_pointer
id|devfn
)paren
op_div
l_int|8
)braket
op_plus
l_int|16
suffix:semicolon
r_else
(brace
r_int
id|i
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
id|intpin
op_assign
(paren
id|prep_pci_intpins
(braket
id|devnum
op_mod
l_int|4
)braket
(braket
id|intpin
)braket
)paren
op_minus
l_int|1
suffix:semicolon
id|intline
op_assign
id|mot_info
(braket
id|mot_entry
)braket
dot
id|pci_irq_list-&gt;primary
(braket
id|intpin
)braket
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/* Write calculated interrupt value to header and device list */
id|dev-&gt;irq
op_assign
id|intline
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
(paren
id|u8
)paren
id|dev-&gt;irq
)paren
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
id|OpenPIC_Addr
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
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|Motherboard_non0
op_ne
l_int|NULL
)paren
id|Motherboard_non0
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Setup the Winbond or Via PIB */
id|prep_pib_init
c_func
(paren
)paren
suffix:semicolon
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
multiline_comment|/*&n;&t;&t;&t; * Relocate PCI I/O resources if necessary so the&n;&t;&t;&t; * standard 256MB BAT covers them.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|pci_resource_flags
c_func
(paren
id|dev
comma
id|i
)paren
op_amp
id|IORESOURCE_IO
)paren
op_logical_and
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
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_assign
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_amp
l_int|0x00FFFFFF
)paren
op_or
l_int|0x01000000
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
r_void
id|__init
DECL|function|prep_find_bridges
id|prep_find_bridges
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
id|hose
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose
)paren
r_return
suffix:semicolon
id|hose-&gt;first_busno
op_assign
l_int|0
suffix:semicolon
id|hose-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|hose-&gt;pci_mem_offset
op_assign
id|PREP_ISA_MEM_BASE
suffix:semicolon
id|hose-&gt;io_base_virt
op_assign
(paren
r_void
op_star
)paren
id|PREP_ISA_IO_BASE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PReP architecture&bslash;n&quot;
)paren
suffix:semicolon
(brace
macro_line|#ifdef CONFIG_PREP_RESIDUAL&t;  
id|PPC_DEVICE
op_star
id|hostbridge
suffix:semicolon
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
id|setup_indirect_pci
c_func
(paren
id|hose
comma
id|ld_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|p.PPCData
)paren
)paren
comma
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
)paren
suffix:semicolon
)brace
r_else
(brace
id|setup_indirect_pci
c_func
(paren
id|hose
comma
l_int|0x80000cf8
comma
l_int|0x80000cfc
)paren
suffix:semicolon
)brace
)brace
r_else
macro_line|#endif /* CONFIG_PREP_RESIDUAL */
(brace
id|hose-&gt;ops
op_assign
op_amp
id|prep_pci_ops
suffix:semicolon
)brace
)brace
id|ppc_md.pcibios_fixup
op_assign
id|prep_pcibios_fixup
suffix:semicolon
)brace
eof
