multiline_comment|/*&n; * ti113x.h 1.16 1999/10/25 20:03:34&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_TI113X_H
DECL|macro|_LINUX_TI113X_H
mdefine_line|#define _LINUX_TI113X_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Register definitions for TI 113X PCI-to-CardBus bridges */
multiline_comment|/* System Control Register */
DECL|macro|TI113X_SYSTEM_CONTROL
mdefine_line|#define TI113X_SYSTEM_CONTROL&t;&t;0x0080&t;/* 32 bit */
DECL|macro|TI113X_SCR_SMIROUTE
mdefine_line|#define  TI113X_SCR_SMIROUTE&t;&t;0x04000000
DECL|macro|TI113X_SCR_SMISTATUS
mdefine_line|#define  TI113X_SCR_SMISTATUS&t;&t;0x02000000
DECL|macro|TI113X_SCR_SMIENB
mdefine_line|#define  TI113X_SCR_SMIENB&t;&t;0x01000000
DECL|macro|TI113X_SCR_VCCPROT
mdefine_line|#define  TI113X_SCR_VCCPROT&t;&t;0x00200000
DECL|macro|TI113X_SCR_REDUCEZV
mdefine_line|#define  TI113X_SCR_REDUCEZV&t;&t;0x00100000
DECL|macro|TI113X_SCR_CDREQEN
mdefine_line|#define  TI113X_SCR_CDREQEN&t;&t;0x00080000
DECL|macro|TI113X_SCR_CDMACHAN
mdefine_line|#define  TI113X_SCR_CDMACHAN&t;&t;0x00070000
DECL|macro|TI113X_SCR_SOCACTIVE
mdefine_line|#define  TI113X_SCR_SOCACTIVE&t;&t;0x00002000
DECL|macro|TI113X_SCR_PWRSTREAM
mdefine_line|#define  TI113X_SCR_PWRSTREAM&t;&t;0x00000800
DECL|macro|TI113X_SCR_DELAYUP
mdefine_line|#define  TI113X_SCR_DELAYUP&t;&t;0x00000400
DECL|macro|TI113X_SCR_DELAYDOWN
mdefine_line|#define  TI113X_SCR_DELAYDOWN&t;&t;0x00000200
DECL|macro|TI113X_SCR_INTERROGATE
mdefine_line|#define  TI113X_SCR_INTERROGATE&t;&t;0x00000100
DECL|macro|TI113X_SCR_CLKRUN_SEL
mdefine_line|#define  TI113X_SCR_CLKRUN_SEL&t;&t;0x00000080
DECL|macro|TI113X_SCR_PWRSAVINGS
mdefine_line|#define  TI113X_SCR_PWRSAVINGS&t;&t;0x00000040
DECL|macro|TI113X_SCR_SUBSYSRW
mdefine_line|#define  TI113X_SCR_SUBSYSRW&t;&t;0x00000020
DECL|macro|TI113X_SCR_CB_DPAR
mdefine_line|#define  TI113X_SCR_CB_DPAR&t;&t;0x00000010
DECL|macro|TI113X_SCR_CDMA_EN
mdefine_line|#define  TI113X_SCR_CDMA_EN&t;&t;0x00000008
DECL|macro|TI113X_SCR_ASYNC_IRQ
mdefine_line|#define  TI113X_SCR_ASYNC_IRQ&t;&t;0x00000004
DECL|macro|TI113X_SCR_KEEPCLK
mdefine_line|#define  TI113X_SCR_KEEPCLK&t;&t;0x00000002
DECL|macro|TI113X_SCR_CLKRUN_ENA
mdefine_line|#define  TI113X_SCR_CLKRUN_ENA&t;&t;0x00000001  
DECL|macro|TI122X_SCR_SER_STEP
mdefine_line|#define  TI122X_SCR_SER_STEP&t;&t;0xc0000000
DECL|macro|TI122X_SCR_INTRTIE
mdefine_line|#define  TI122X_SCR_INTRTIE&t;&t;0x20000000
DECL|macro|TI122X_SCR_CBRSVD
mdefine_line|#define  TI122X_SCR_CBRSVD&t;&t;0x00400000
DECL|macro|TI122X_SCR_MRBURSTDN
mdefine_line|#define  TI122X_SCR_MRBURSTDN&t;&t;0x00008000
DECL|macro|TI122X_SCR_MRBURSTUP
mdefine_line|#define  TI122X_SCR_MRBURSTUP&t;&t;0x00004000
DECL|macro|TI122X_SCR_RIMUX
mdefine_line|#define  TI122X_SCR_RIMUX&t;&t;0x00000001
multiline_comment|/* Multimedia Control Register */
DECL|macro|TI1250_MULTIMEDIA_CTL
mdefine_line|#define TI1250_MULTIMEDIA_CTL&t;&t;0x0084&t;/* 8 bit */
DECL|macro|TI1250_MMC_ZVOUTEN
mdefine_line|#define  TI1250_MMC_ZVOUTEN&t;&t;0x80
DECL|macro|TI1250_MMC_PORTSEL
mdefine_line|#define  TI1250_MMC_PORTSEL&t;&t;0x40
DECL|macro|TI1250_MMC_ZVEN1
mdefine_line|#define  TI1250_MMC_ZVEN1&t;&t;0x02
DECL|macro|TI1250_MMC_ZVEN0
mdefine_line|#define  TI1250_MMC_ZVEN0&t;&t;0x01
DECL|macro|TI1250_GENERAL_STATUS
mdefine_line|#define TI1250_GENERAL_STATUS&t;&t;0x0085&t;/* 8 bit */
DECL|macro|TI1250_GPIO0_CONTROL
mdefine_line|#define TI1250_GPIO0_CONTROL&t;&t;0x0088&t;/* 8 bit */
DECL|macro|TI1250_GPIO1_CONTROL
mdefine_line|#define TI1250_GPIO1_CONTROL&t;&t;0x0089&t;/* 8 bit */
DECL|macro|TI1250_GPIO2_CONTROL
mdefine_line|#define TI1250_GPIO2_CONTROL&t;&t;0x008a&t;/* 8 bit */
DECL|macro|TI1250_GPIO3_CONTROL
mdefine_line|#define TI1250_GPIO3_CONTROL&t;&t;0x008b&t;/* 8 bit */
DECL|macro|TI122X_IRQMUX
mdefine_line|#define TI122X_IRQMUX&t;&t;&t;0x008c&t;/* 32 bit */
multiline_comment|/* Retry Status Register */
DECL|macro|TI113X_RETRY_STATUS
mdefine_line|#define TI113X_RETRY_STATUS&t;&t;0x0090&t;/* 8 bit */
DECL|macro|TI113X_RSR_PCIRETRY
mdefine_line|#define  TI113X_RSR_PCIRETRY&t;&t;0x80
DECL|macro|TI113X_RSR_CBRETRY
mdefine_line|#define  TI113X_RSR_CBRETRY&t;&t;0x40
DECL|macro|TI113X_RSR_TEXP_CBB
mdefine_line|#define  TI113X_RSR_TEXP_CBB&t;&t;0x20
DECL|macro|TI113X_RSR_MEXP_CBB
mdefine_line|#define  TI113X_RSR_MEXP_CBB&t;&t;0x10
DECL|macro|TI113X_RSR_TEXP_CBA
mdefine_line|#define  TI113X_RSR_TEXP_CBA&t;&t;0x08
DECL|macro|TI113X_RSR_MEXP_CBA
mdefine_line|#define  TI113X_RSR_MEXP_CBA&t;&t;0x04
DECL|macro|TI113X_RSR_TEXP_PCI
mdefine_line|#define  TI113X_RSR_TEXP_PCI&t;&t;0x02
DECL|macro|TI113X_RSR_MEXP_PCI
mdefine_line|#define  TI113X_RSR_MEXP_PCI&t;&t;0x01
multiline_comment|/* Card Control Register */
DECL|macro|TI113X_CARD_CONTROL
mdefine_line|#define TI113X_CARD_CONTROL&t;&t;0x0091&t;/* 8 bit */
DECL|macro|TI113X_CCR_RIENB
mdefine_line|#define  TI113X_CCR_RIENB&t;&t;0x80
DECL|macro|TI113X_CCR_ZVENABLE
mdefine_line|#define  TI113X_CCR_ZVENABLE&t;&t;0x40
DECL|macro|TI113X_CCR_PCI_IRQ_ENA
mdefine_line|#define  TI113X_CCR_PCI_IRQ_ENA&t;&t;0x20
DECL|macro|TI113X_CCR_PCI_IREQ
mdefine_line|#define  TI113X_CCR_PCI_IREQ&t;&t;0x10
DECL|macro|TI113X_CCR_PCI_CSC
mdefine_line|#define  TI113X_CCR_PCI_CSC&t;&t;0x08
DECL|macro|TI113X_CCR_SPKROUTEN
mdefine_line|#define  TI113X_CCR_SPKROUTEN&t;&t;0x02
DECL|macro|TI113X_CCR_IFG
mdefine_line|#define  TI113X_CCR_IFG&t;&t;&t;0x01
DECL|macro|TI1220_CCR_PORT_SEL
mdefine_line|#define  TI1220_CCR_PORT_SEL&t;&t;0x20
DECL|macro|TI122X_CCR_AUD2MUX
mdefine_line|#define  TI122X_CCR_AUD2MUX&t;&t;0x04
multiline_comment|/* Device Control Register */
DECL|macro|TI113X_DEVICE_CONTROL
mdefine_line|#define TI113X_DEVICE_CONTROL&t;&t;0x0092&t;/* 8 bit */
DECL|macro|TI113X_DCR_5V_FORCE
mdefine_line|#define  TI113X_DCR_5V_FORCE&t;&t;0x40
DECL|macro|TI113X_DCR_3V_FORCE
mdefine_line|#define  TI113X_DCR_3V_FORCE&t;&t;0x20
DECL|macro|TI113X_DCR_IMODE_MASK
mdefine_line|#define  TI113X_DCR_IMODE_MASK&t;&t;0x06
DECL|macro|TI113X_DCR_IMODE_ISA
mdefine_line|#define  TI113X_DCR_IMODE_ISA&t;&t;0x02
DECL|macro|TI113X_DCR_IMODE_SERIAL
mdefine_line|#define  TI113X_DCR_IMODE_SERIAL&t;0x04
DECL|macro|TI12XX_DCR_IMODE_PCI_ONLY
mdefine_line|#define  TI12XX_DCR_IMODE_PCI_ONLY&t;0x00
DECL|macro|TI12XX_DCR_IMODE_ALL_SERIAL
mdefine_line|#define  TI12XX_DCR_IMODE_ALL_SERIAL&t;0x06
multiline_comment|/* Buffer Control Register */
DECL|macro|TI113X_BUFFER_CONTROL
mdefine_line|#define TI113X_BUFFER_CONTROL&t;&t;0x0093&t;/* 8 bit */
DECL|macro|TI113X_BCR_CB_READ_DEPTH
mdefine_line|#define  TI113X_BCR_CB_READ_DEPTH&t;0x08
DECL|macro|TI113X_BCR_CB_WRITE_DEPTH
mdefine_line|#define  TI113X_BCR_CB_WRITE_DEPTH&t;0x04
DECL|macro|TI113X_BCR_PCI_READ_DEPTH
mdefine_line|#define  TI113X_BCR_PCI_READ_DEPTH&t;0x02
DECL|macro|TI113X_BCR_PCI_WRITE_DEPTH
mdefine_line|#define  TI113X_BCR_PCI_WRITE_DEPTH&t;0x01
multiline_comment|/* Diagnostic Register */
DECL|macro|TI1250_DIAGNOSTIC
mdefine_line|#define TI1250_DIAGNOSTIC&t;&t;0x0093&t;/* 8 bit */
DECL|macro|TI1250_DIAG_TRUE_VALUE
mdefine_line|#define  TI1250_DIAG_TRUE_VALUE&t;&t;0x80
DECL|macro|TI1250_DIAG_PCI_IREQ
mdefine_line|#define  TI1250_DIAG_PCI_IREQ&t;&t;0x40
DECL|macro|TI1250_DIAG_PCI_CSC
mdefine_line|#define  TI1250_DIAG_PCI_CSC&t;&t;0x20
DECL|macro|TI1250_DIAG_ASYNC_CSC
mdefine_line|#define  TI1250_DIAG_ASYNC_CSC&t;&t;0x01
multiline_comment|/* DMA Registers */
DECL|macro|TI113X_DMA_0
mdefine_line|#define TI113X_DMA_0&t;&t;&t;0x0094&t;/* 32 bit */
DECL|macro|TI113X_DMA_1
mdefine_line|#define TI113X_DMA_1&t;&t;&t;0x0098&t;/* 32 bit */
multiline_comment|/* ExCA IO offset registers */
DECL|macro|TI113X_IO_OFFSET
mdefine_line|#define TI113X_IO_OFFSET(map)&t;&t;(0x36+((map)&lt;&lt;1))
macro_line|#ifdef CONFIG_CARDBUS
multiline_comment|/*&n; * Generic TI init - TI has an extension for the&n; * INTCTL register that sets the PCI CSC interrupt.&n; * Make sure we set it correctly at open and init&n; * time&n; * - open: disable the PCI CSC interrupt. This makes&n; *   it possible to use the CSC interrupt to probe the&n; *   ISA interrupts.&n; * - init: set the interrupt to match our PCI state.&n; *   This makes us correctly get PCI CSC interrupt&n; *   events.&n; */
DECL|function|ti_open
r_static
r_int
id|ti_open
c_func
(paren
id|pci_socket_t
op_star
id|socket
)paren
(brace
id|u8
r_new
comma
id|reg
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_INTCTL
)paren
suffix:semicolon
r_new
op_assign
id|reg
op_amp
op_complement
id|I365_INTR_ENA
suffix:semicolon
r_if
c_cond
(paren
r_new
op_ne
id|reg
)paren
id|exca_writeb
c_func
(paren
id|socket
comma
id|I365_INTCTL
comma
r_new
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ti_intctl
r_static
r_int
id|ti_intctl
c_func
(paren
id|pci_socket_t
op_star
id|socket
)paren
(brace
id|u8
r_new
comma
id|reg
op_assign
id|exca_readb
c_func
(paren
id|socket
comma
id|I365_INTCTL
)paren
suffix:semicolon
r_new
op_assign
id|reg
op_amp
op_complement
id|I365_INTR_ENA
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;cb_irq
)paren
r_new
op_or_assign
id|I365_INTR_ENA
suffix:semicolon
r_if
c_cond
(paren
r_new
op_ne
id|reg
)paren
id|exca_writeb
c_func
(paren
id|socket
comma
id|I365_INTCTL
comma
r_new
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ti_init
r_static
r_int
id|ti_init
c_func
(paren
id|pci_socket_t
op_star
id|socket
)paren
(brace
id|yenta_init
c_func
(paren
id|socket
)paren
suffix:semicolon
id|ti_intctl
c_func
(paren
id|socket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ti_ops
r_static
r_struct
id|pci_socket_ops
id|ti_ops
op_assign
(brace
id|ti_open
comma
id|yenta_close
comma
id|ti_init
comma
id|yenta_suspend
comma
id|yenta_get_status
comma
id|yenta_get_socket
comma
id|yenta_set_socket
comma
id|yenta_get_io_map
comma
id|yenta_set_io_map
comma
id|yenta_get_mem_map
comma
id|yenta_set_mem_map
comma
id|yenta_proc_setup
)brace
suffix:semicolon
DECL|macro|ti_sysctl
mdefine_line|#define ti_sysctl(socket)&t;((socket)-&gt;private[0])
DECL|macro|ti_cardctl
mdefine_line|#define ti_cardctl(socket)&t;((socket)-&gt;private[1])
DECL|macro|ti_devctl
mdefine_line|#define ti_devctl(socket)&t;((socket)-&gt;private[2])
DECL|function|ti113x_open
r_static
r_int
id|ti113x_open
c_func
(paren
id|pci_socket_t
op_star
id|socket
)paren
(brace
id|ti_sysctl
c_func
(paren
id|socket
)paren
op_assign
id|config_readl
c_func
(paren
id|socket
comma
id|TI113X_SYSTEM_CONTROL
)paren
suffix:semicolon
id|ti_cardctl
c_func
(paren
id|socket
)paren
op_assign
id|config_readb
c_func
(paren
id|socket
comma
id|TI113X_CARD_CONTROL
)paren
suffix:semicolon
id|ti_devctl
c_func
(paren
id|socket
)paren
op_assign
id|config_readb
c_func
(paren
id|socket
comma
id|TI113X_DEVICE_CONTROL
)paren
suffix:semicolon
id|ti_cardctl
c_func
(paren
id|socket
)paren
op_and_assign
op_complement
(paren
id|TI113X_CCR_PCI_IRQ_ENA
op_or
id|TI113X_CCR_PCI_IREQ
op_or
id|TI113X_CCR_PCI_CSC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;cb_irq
)paren
id|ti_cardctl
c_func
(paren
id|socket
)paren
op_or_assign
id|TI113X_CCR_PCI_IRQ_ENA
op_or
id|TI113X_CCR_PCI_CSC
op_or
id|TI113X_CCR_PCI_IREQ
suffix:semicolon
id|ti_open
c_func
(paren
id|socket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ti113x_init
r_static
r_int
id|ti113x_init
c_func
(paren
id|pci_socket_t
op_star
id|socket
)paren
(brace
id|yenta_init
c_func
(paren
id|socket
)paren
suffix:semicolon
id|config_writel
c_func
(paren
id|socket
comma
id|TI113X_SYSTEM_CONTROL
comma
id|ti_sysctl
c_func
(paren
id|socket
)paren
)paren
suffix:semicolon
id|config_writeb
c_func
(paren
id|socket
comma
id|TI113X_CARD_CONTROL
comma
id|ti_cardctl
c_func
(paren
id|socket
)paren
)paren
suffix:semicolon
id|config_writeb
c_func
(paren
id|socket
comma
id|TI113X_DEVICE_CONTROL
comma
id|ti_devctl
c_func
(paren
id|socket
)paren
)paren
suffix:semicolon
id|ti_intctl
c_func
(paren
id|socket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ti113x_ops
r_static
r_struct
id|pci_socket_ops
id|ti113x_ops
op_assign
(brace
id|ti113x_open
comma
id|yenta_close
comma
id|ti113x_init
comma
id|yenta_suspend
comma
id|yenta_get_status
comma
id|yenta_get_socket
comma
id|yenta_set_socket
comma
id|yenta_get_io_map
comma
id|yenta_set_io_map
comma
id|yenta_get_mem_map
comma
id|yenta_set_mem_map
comma
id|yenta_proc_setup
)brace
suffix:semicolon
DECL|macro|ti_diag
mdefine_line|#define ti_diag(socket)&t;&t;((socket)-&gt;private[0])
DECL|function|ti1250_open
r_static
r_int
id|ti1250_open
c_func
(paren
id|pci_socket_t
op_star
id|socket
)paren
(brace
id|ti_diag
c_func
(paren
id|socket
)paren
op_assign
id|config_readb
c_func
(paren
id|socket
comma
id|TI1250_DIAGNOSTIC
)paren
suffix:semicolon
id|ti_diag
c_func
(paren
id|socket
)paren
op_and_assign
op_complement
(paren
id|TI1250_DIAG_PCI_CSC
op_or
id|TI1250_DIAG_PCI_IREQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|socket-&gt;cb_irq
)paren
id|ti_diag
c_func
(paren
id|socket
)paren
op_or_assign
id|TI1250_DIAG_PCI_CSC
op_or
id|TI1250_DIAG_PCI_IREQ
suffix:semicolon
id|ti_open
c_func
(paren
id|socket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ti1250_init
r_static
r_int
id|ti1250_init
c_func
(paren
id|pci_socket_t
op_star
id|socket
)paren
(brace
id|yenta_init
c_func
(paren
id|socket
)paren
suffix:semicolon
id|config_writeb
c_func
(paren
id|socket
comma
id|TI1250_DIAGNOSTIC
comma
id|ti_diag
c_func
(paren
id|socket
)paren
)paren
suffix:semicolon
id|ti_intctl
c_func
(paren
id|socket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ti1250_ops
r_static
r_struct
id|pci_socket_ops
id|ti1250_ops
op_assign
(brace
id|ti1250_open
comma
id|yenta_close
comma
id|ti1250_init
comma
id|yenta_suspend
comma
id|yenta_get_status
comma
id|yenta_get_socket
comma
id|yenta_set_socket
comma
id|yenta_get_io_map
comma
id|yenta_set_io_map
comma
id|yenta_get_mem_map
comma
id|yenta_set_mem_map
comma
id|yenta_proc_setup
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_CARDBUS */
macro_line|#endif /* _LINUX_TI113X_H */
eof
