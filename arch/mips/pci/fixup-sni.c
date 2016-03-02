multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SNI specific PCI support for RM200/RM300.&n; *&n; * Copyright (C) 1997 - 2000, 2003 Ralf Baechle&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/pci_channel.h&gt;
macro_line|#include &lt;asm/sni.h&gt;
multiline_comment|/*&n; * Shortcuts ...&n; */
DECL|macro|SCSI
mdefine_line|#define SCSI&t;PCIMT_IRQ_SCSI
DECL|macro|ETH
mdefine_line|#define ETH&t;PCIMT_IRQ_ETHERNET
DECL|macro|INTA
mdefine_line|#define INTA&t;PCIMT_IRQ_INTA
DECL|macro|INTB
mdefine_line|#define INTB&t;PCIMT_IRQ_INTB
DECL|macro|INTC
mdefine_line|#define INTC&t;PCIMT_IRQ_INTC
DECL|macro|INTD
mdefine_line|#define INTD&t;PCIMT_IRQ_INTD
multiline_comment|/*&n; * Device 0: PCI EISA Bridge&t;(directly routed)&n; * Device 1: NCR53c810 SCSI&t;(directly routed)&n; * Device 2: PCnet32 Ethernet&t;(directly routed)&n; * Device 3: VGA&t;&t;(routed to INTB)&n; * Device 4: Unused&n; * Device 5: Slot 2&n; * Device 6: Slot 3&n; * Device 7: Slot 4&t;&n; *&n; * Documentation says the VGA is device 5 and device 3 is unused but that&n; * seem to be a documentation error.  At least on my RM200C the Cirrus&n; * Logic CL-GD5434 VGA is device 3.&n; */
DECL|variable|__initdata
r_static
r_char
id|irq_tab_rm200
(braket
l_int|8
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*       INTA  INTB  INTC  INTD */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* EISA bridge */
(brace
id|SCSI
comma
id|SCSI
comma
id|SCSI
comma
id|SCSI
comma
id|SCSI
)brace
comma
multiline_comment|/* SCSI */
(brace
id|ETH
comma
id|ETH
comma
id|ETH
comma
id|ETH
comma
id|ETH
)brace
comma
multiline_comment|/* Ethernet */
(brace
id|INTB
comma
id|INTB
comma
id|INTB
comma
id|INTB
comma
id|INTB
)brace
comma
multiline_comment|/* VGA */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Unused */
(brace
l_int|0
comma
id|INTB
comma
id|INTC
comma
id|INTD
comma
id|INTA
)brace
comma
multiline_comment|/* Slot 2 */
(brace
l_int|0
comma
id|INTC
comma
id|INTD
comma
id|INTA
comma
id|INTB
)brace
comma
multiline_comment|/* Slot 3 */
(brace
l_int|0
comma
id|INTD
comma
id|INTA
comma
id|INTB
comma
id|INTC
)brace
comma
multiline_comment|/* Slot 4 */
)brace
suffix:semicolon
multiline_comment|/*&n; * In Revision D of the RM300 Device 2 has become a normal purpose Slot 1&n; *&n; * The VGA card is optional for RM300 systems.&n; */
DECL|variable|__initdata
r_static
r_char
id|irq_tab_rm300d
(braket
l_int|8
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*       INTA  INTB  INTC  INTD */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* EISA bridge */
(brace
id|SCSI
comma
id|SCSI
comma
id|SCSI
comma
id|SCSI
comma
id|SCSI
)brace
comma
multiline_comment|/* SCSI */
(brace
l_int|0
comma
id|INTC
comma
id|INTD
comma
id|INTA
comma
id|INTB
)brace
comma
multiline_comment|/* Slot 1 */
(brace
id|INTB
comma
id|INTB
comma
id|INTB
comma
id|INTB
comma
id|INTB
)brace
comma
multiline_comment|/* VGA */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Unused */
(brace
l_int|0
comma
id|INTB
comma
id|INTC
comma
id|INTD
comma
id|INTA
)brace
comma
multiline_comment|/* Slot 2 */
(brace
l_int|0
comma
id|INTC
comma
id|INTD
comma
id|INTA
comma
id|INTB
)brace
comma
multiline_comment|/* Slot 3 */
(brace
l_int|0
comma
id|INTD
comma
id|INTA
comma
id|INTB
comma
id|INTC
)brace
comma
multiline_comment|/* Slot 4 */
)brace
suffix:semicolon
DECL|function|is_rm300_revd
r_static
r_inline
r_int
id|is_rm300_revd
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|csmsr
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PCIMT_CSMSR
suffix:semicolon
r_return
(paren
id|csmsr
op_amp
l_int|0xa0
)paren
op_eq
l_int|0x20
suffix:semicolon
)brace
DECL|function|pcibios_map_irq
r_int
id|__init
id|pcibios_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_if
c_cond
(paren
id|is_rm300_revd
c_func
(paren
)paren
)paren
r_return
id|irq_tab_rm300d
(braket
id|slot
)braket
(braket
id|pin
)braket
suffix:semicolon
r_return
id|irq_tab_rm200
(braket
id|slot
)braket
(braket
id|pin
)braket
suffix:semicolon
)brace
eof
