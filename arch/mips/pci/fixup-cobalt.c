multiline_comment|/*&n; * Cobalt Qube/Raq PCI support&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1997, 2002, 2003 by Ralf Baechle&n; * Copyright (C) 2001, 2002, 2003 by Liam Davies (ldavies@agile.tv)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/gt64120.h&gt;
macro_line|#include &lt;asm/cobalt/cobalt.h&gt;
r_extern
r_int
id|cobalt_board_id
suffix:semicolon
DECL|function|qube_raq_via_bmIDE_fixup
r_static
r_void
id|qube_raq_via_bmIDE_fixup
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|cfgword
suffix:semicolon
r_int
r_char
id|lt
suffix:semicolon
multiline_comment|/* Enable Bus Mastering and fast back to back. */
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cfgword
)paren
suffix:semicolon
id|cfgword
op_or_assign
(paren
id|PCI_COMMAND_FAST_BACK
op_or
id|PCI_COMMAND_MASTER
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cfgword
)paren
suffix:semicolon
multiline_comment|/* Enable both ide interfaces. ROM only enables primary one.  */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x40
comma
l_int|0xb
)paren
suffix:semicolon
multiline_comment|/* Set latency timer to reasonable value. */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|lt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lt
OL
l_int|64
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|64
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
l_int|7
)paren
suffix:semicolon
)brace
id|DECLARE_PCI_FIXUP_HEADER
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C586_1
comma
id|qube_raq_via_bmIDE_fixup
)paren
suffix:semicolon
DECL|function|qube_raq_galileo_fixup
r_static
r_void
id|qube_raq_galileo_fixup
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|galileo_id
suffix:semicolon
multiline_comment|/* Fix PCI latency-timer and cache-line-size values in Galileo&n;&t; * host bridge.&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|64
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * On all machines prior to Q2, we had the STOP line disconnected&n;&t; * from Galileo to VIA on PCI.  The new Galileo does not function&n;&t; * correctly unless we have it connected.&n;&t; *&n;&t; * Therefore we must set the disconnect/retry cycle values to&n;&t; * something sensible when using the new Galileo.&n;&t; */
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_REVISION_ID
comma
op_amp
id|galileo_id
)paren
suffix:semicolon
id|galileo_id
op_and_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* mask off class info */
r_if
c_cond
(paren
id|galileo_id
op_ge
l_int|0x10
)paren
(brace
multiline_comment|/* New Galileo, assumes PCI stop line to VIA is connected. */
id|GALILEO_OUTL
c_func
(paren
l_int|0x4020
comma
id|GT_PCI0_TOR_OFS
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|galileo_id
op_eq
l_int|0x1
op_logical_or
id|galileo_id
op_eq
l_int|0x2
)paren
(brace
r_int
r_int
id|timeo
suffix:semicolon
multiline_comment|/* XXX WE MUST DO THIS ELSE GALILEO LOCKS UP! -DaveM */
id|timeo
op_assign
id|GALILEO_INL
c_func
(paren
id|GT_PCI0_TOR_OFS
)paren
suffix:semicolon
multiline_comment|/* Old Galileo, assumes PCI STOP line to VIA is disconnected. */
id|GALILEO_OUTL
c_func
(paren
l_int|0xffff
comma
id|GT_PCI0_TOR_OFS
)paren
suffix:semicolon
)brace
)brace
id|DECLARE_PCI_FIXUP_HEADER
c_func
(paren
id|PCI_VENDOR_ID_GALILEO
comma
id|PCI_ANY_ID
comma
id|qube_raq_galileo_fixup
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|irq_tab_cobalt
(braket
)braket
id|__initdata
op_assign
(brace
(braket
id|COBALT_PCICONF_CPU
)braket
op_assign
l_int|0
comma
(braket
id|COBALT_PCICONF_ETH0
)braket
op_assign
id|COBALT_ETH0_IRQ
comma
(braket
id|COBALT_PCICONF_RAQSCSI
)braket
op_assign
id|COBALT_SCSI_IRQ
comma
(braket
id|COBALT_PCICONF_VIA
)braket
op_assign
l_int|0
comma
(braket
id|COBALT_PCICONF_PCISLOT
)braket
op_assign
id|COBALT_QUBE_SLOT_IRQ
comma
(braket
id|COBALT_PCICONF_ETH1
)braket
op_assign
id|COBALT_ETH1_IRQ
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|irq_tab_raq2
(braket
)braket
id|__initdata
op_assign
(brace
(braket
id|COBALT_PCICONF_CPU
)braket
op_assign
l_int|0
comma
(braket
id|COBALT_PCICONF_ETH0
)braket
op_assign
id|COBALT_ETH0_IRQ
comma
(braket
id|COBALT_PCICONF_RAQSCSI
)braket
op_assign
id|COBALT_RAQ_SCSI_IRQ
comma
(braket
id|COBALT_PCICONF_VIA
)braket
op_assign
l_int|0
comma
(braket
id|COBALT_PCICONF_PCISLOT
)braket
op_assign
id|COBALT_QUBE_SLOT_IRQ
comma
(braket
id|COBALT_PCICONF_ETH1
)braket
op_assign
id|COBALT_ETH1_IRQ
)brace
suffix:semicolon
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
id|cobalt_board_id
op_eq
id|COBALT_BRD_ID_RAQ2
)paren
r_return
id|irq_tab_raq2
(braket
id|slot
)braket
suffix:semicolon
r_return
id|irq_tab_cobalt
(braket
id|slot
)braket
suffix:semicolon
)brace
multiline_comment|/* Do platform specific device initialization at pci_enable_device() time */
DECL|function|pcibios_plat_dev_init
r_int
id|pcibios_plat_dev_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
