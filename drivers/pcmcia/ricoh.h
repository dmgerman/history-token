multiline_comment|/*&n; * ricoh.h 1.9 1999/10/25 20:03:34&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_RICOH_H
DECL|macro|_LINUX_RICOH_H
mdefine_line|#define _LINUX_RICOH_H
DECL|macro|RF5C_MODE_CTL
mdefine_line|#define RF5C_MODE_CTL&t;&t;0x1f&t;/* Mode control */
DECL|macro|RF5C_PWR_CTL
mdefine_line|#define RF5C_PWR_CTL&t;&t;0x2f&t;/* Mixed voltage control */
DECL|macro|RF5C_CHIP_ID
mdefine_line|#define RF5C_CHIP_ID&t;&t;0x3a&t;/* Chip identification */
DECL|macro|RF5C_MODE_CTL_3
mdefine_line|#define RF5C_MODE_CTL_3&t;&t;0x3b&t;/* Mode control 3 */
multiline_comment|/* I/O window address offset */
DECL|macro|RF5C_IO_OFF
mdefine_line|#define RF5C_IO_OFF(w)&t;&t;(0x36+((w)&lt;&lt;1))
multiline_comment|/* Flags for RF5C_MODE_CTL */
DECL|macro|RF5C_MODE_ATA
mdefine_line|#define RF5C_MODE_ATA&t;&t;0x01&t;/* ATA mode */
DECL|macro|RF5C_MODE_LED_ENA
mdefine_line|#define RF5C_MODE_LED_ENA&t;0x02&t;/* IRQ 12 is LED */
DECL|macro|RF5C_MODE_CA21
mdefine_line|#define RF5C_MODE_CA21&t;&t;0x04
DECL|macro|RF5C_MODE_CA22
mdefine_line|#define RF5C_MODE_CA22&t;&t;0x08
DECL|macro|RF5C_MODE_CA23
mdefine_line|#define RF5C_MODE_CA23&t;&t;0x10
DECL|macro|RF5C_MODE_CA24
mdefine_line|#define RF5C_MODE_CA24&t;&t;0x20
DECL|macro|RF5C_MODE_CA25
mdefine_line|#define RF5C_MODE_CA25&t;&t;0x40
DECL|macro|RF5C_MODE_3STATE_BIT7
mdefine_line|#define RF5C_MODE_3STATE_BIT7&t;0x80
multiline_comment|/* Flags for RF5C_PWR_CTL */
DECL|macro|RF5C_PWR_VCC_3V
mdefine_line|#define RF5C_PWR_VCC_3V&t;&t;0x01
DECL|macro|RF5C_PWR_IREQ_HIGH
mdefine_line|#define RF5C_PWR_IREQ_HIGH&t;0x02
DECL|macro|RF5C_PWR_INPACK_ENA
mdefine_line|#define RF5C_PWR_INPACK_ENA&t;0x04
DECL|macro|RF5C_PWR_5V_DET
mdefine_line|#define RF5C_PWR_5V_DET&t;&t;0x08
DECL|macro|RF5C_PWR_TC_SEL
mdefine_line|#define RF5C_PWR_TC_SEL&t;&t;0x10&t;/* Terminal Count: irq 11 or 15 */
DECL|macro|RF5C_PWR_DREQ_LOW
mdefine_line|#define RF5C_PWR_DREQ_LOW&t;0x20
DECL|macro|RF5C_PWR_DREQ_OFF
mdefine_line|#define RF5C_PWR_DREQ_OFF&t;0x00&t;/* DREQ steering control */
DECL|macro|RF5C_PWR_DREQ_INPACK
mdefine_line|#define RF5C_PWR_DREQ_INPACK&t;0x40
DECL|macro|RF5C_PWR_DREQ_SPKR
mdefine_line|#define RF5C_PWR_DREQ_SPKR&t;0x80
DECL|macro|RF5C_PWR_DREQ_IOIS16
mdefine_line|#define RF5C_PWR_DREQ_IOIS16&t;0xc0
multiline_comment|/* Values for RF5C_CHIP_ID */
DECL|macro|RF5C_CHIP_RF5C296
mdefine_line|#define RF5C_CHIP_RF5C296&t;0x32
DECL|macro|RF5C_CHIP_RF5C396
mdefine_line|#define RF5C_CHIP_RF5C396&t;0xb2
multiline_comment|/* Flags for RF5C_MODE_CTL_3 */
DECL|macro|RF5C_MCTL3_DISABLE
mdefine_line|#define RF5C_MCTL3_DISABLE&t;0x01&t;/* Disable PCMCIA interface */
DECL|macro|RF5C_MCTL3_DMA_ENA
mdefine_line|#define RF5C_MCTL3_DMA_ENA&t;0x02
multiline_comment|/* Register definitions for Ricoh PCI-to-CardBus bridges */
multiline_comment|/* Extra bits in CB_BRIDGE_CONTROL */
DECL|macro|RL5C46X_BCR_3E0_ENA
mdefine_line|#define RL5C46X_BCR_3E0_ENA&t;&t;0x0800
DECL|macro|RL5C46X_BCR_3E2_ENA
mdefine_line|#define RL5C46X_BCR_3E2_ENA&t;&t;0x1000
multiline_comment|/* Misc Control Register */
DECL|macro|RL5C4XX_MISC
mdefine_line|#define RL5C4XX_MISC&t;&t;&t;0x0082&t;/* 16 bit */
DECL|macro|RL5C4XX_MISC_HW_SUSPEND_ENA
mdefine_line|#define  RL5C4XX_MISC_HW_SUSPEND_ENA&t;0x0002
DECL|macro|RL5C4XX_MISC_VCCEN_POL
mdefine_line|#define  RL5C4XX_MISC_VCCEN_POL&t;&t;0x0100
DECL|macro|RL5C4XX_MISC_VPPEN_POL
mdefine_line|#define  RL5C4XX_MISC_VPPEN_POL&t;&t;0x0200
DECL|macro|RL5C46X_MISC_SUSPEND
mdefine_line|#define  RL5C46X_MISC_SUSPEND&t;&t;0x0001
DECL|macro|RL5C46X_MISC_PWR_SAVE_2
mdefine_line|#define  RL5C46X_MISC_PWR_SAVE_2&t;0x0004
DECL|macro|RL5C46X_MISC_IFACE_BUSY
mdefine_line|#define  RL5C46X_MISC_IFACE_BUSY&t;0x0008
DECL|macro|RL5C46X_MISC_B_LOCK
mdefine_line|#define  RL5C46X_MISC_B_LOCK&t;&t;0x0010
DECL|macro|RL5C46X_MISC_A_LOCK
mdefine_line|#define  RL5C46X_MISC_A_LOCK&t;&t;0x0020
DECL|macro|RL5C46X_MISC_PCI_LOCK
mdefine_line|#define  RL5C46X_MISC_PCI_LOCK&t;&t;0x0040
DECL|macro|RL5C47X_MISC_IFACE_BUSY
mdefine_line|#define  RL5C47X_MISC_IFACE_BUSY&t;0x0004
DECL|macro|RL5C47X_MISC_PCI_INT_MASK
mdefine_line|#define  RL5C47X_MISC_PCI_INT_MASK&t;0x0018
DECL|macro|RL5C47X_MISC_PCI_INT_DIS
mdefine_line|#define  RL5C47X_MISC_PCI_INT_DIS&t;0x0020
DECL|macro|RL5C47X_MISC_SUBSYS_WR
mdefine_line|#define  RL5C47X_MISC_SUBSYS_WR&t;&t;0x0040
DECL|macro|RL5C47X_MISC_SRIRQ_ENA
mdefine_line|#define  RL5C47X_MISC_SRIRQ_ENA&t;&t;0x0080
DECL|macro|RL5C47X_MISC_5V_DISABLE
mdefine_line|#define  RL5C47X_MISC_5V_DISABLE&t;0x0400
DECL|macro|RL5C47X_MISC_LED_POL
mdefine_line|#define  RL5C47X_MISC_LED_POL&t;&t;0x0800
multiline_comment|/* 16-bit Interface Control Register */
DECL|macro|RL5C4XX_16BIT_CTL
mdefine_line|#define RL5C4XX_16BIT_CTL&t;&t;0x0084&t;/* 16 bit */
DECL|macro|RL5C4XX_16CTL_IO_TIMING
mdefine_line|#define  RL5C4XX_16CTL_IO_TIMING&t;0x0100
DECL|macro|RL5C4XX_16CTL_MEM_TIMING
mdefine_line|#define  RL5C4XX_16CTL_MEM_TIMING&t;0x0200
DECL|macro|RL5C46X_16CTL_LEVEL_1
mdefine_line|#define  RL5C46X_16CTL_LEVEL_1&t;&t;0x0010
DECL|macro|RL5C46X_16CTL_LEVEL_2
mdefine_line|#define  RL5C46X_16CTL_LEVEL_2&t;&t;0x0020
multiline_comment|/* 16-bit IO and memory timing registers */
DECL|macro|RL5C4XX_16BIT_IO_0
mdefine_line|#define RL5C4XX_16BIT_IO_0&t;&t;0x0088&t;/* 16 bit */
DECL|macro|RL5C4XX_16BIT_MEM_0
mdefine_line|#define RL5C4XX_16BIT_MEM_0&t;&t;0x0088&t;/* 16 bit */
DECL|macro|RL5C4XX_SETUP_MASK
mdefine_line|#define  RL5C4XX_SETUP_MASK&t;&t;0x0007
DECL|macro|RL5C4XX_SETUP_SHIFT
mdefine_line|#define  RL5C4XX_SETUP_SHIFT&t;&t;0
DECL|macro|RL5C4XX_CMD_MASK
mdefine_line|#define  RL5C4XX_CMD_MASK&t;&t;0x01f0
DECL|macro|RL5C4XX_CMD_SHIFT
mdefine_line|#define  RL5C4XX_CMD_SHIFT&t;&t;4
DECL|macro|RL5C4XX_HOLD_MASK
mdefine_line|#define  RL5C4XX_HOLD_MASK&t;&t;0x1c00
DECL|macro|RL5C4XX_HOLD_SHIFT
mdefine_line|#define  RL5C4XX_HOLD_SHIFT&t;&t;10
macro_line|#ifdef __YENTA_H
DECL|macro|rl_misc
mdefine_line|#define rl_misc(socket)&t;&t;((socket)-&gt;private[0])
DECL|macro|rl_ctl
mdefine_line|#define rl_ctl(socket)&t;&t;((socket)-&gt;private[1])
DECL|macro|rl_io
mdefine_line|#define rl_io(socket)&t;&t;((socket)-&gt;private[2])
DECL|macro|rl_mem
mdefine_line|#define rl_mem(socket)&t;&t;((socket)-&gt;private[3])
multiline_comment|/*&n; * Magic Ricoh initialization code.. Save state at&n; * beginning, re-initialize it after suspend.&n; */
DECL|function|ricoh_open
r_static
r_int
id|ricoh_open
c_func
(paren
id|pci_socket_t
op_star
id|socket
)paren
(brace
id|rl_misc
c_func
(paren
id|socket
)paren
op_assign
id|config_readw
c_func
(paren
id|socket
comma
id|RL5C4XX_MISC
)paren
suffix:semicolon
id|rl_ctl
c_func
(paren
id|socket
)paren
op_assign
id|config_readw
c_func
(paren
id|socket
comma
id|RL5C4XX_16BIT_CTL
)paren
suffix:semicolon
id|rl_io
c_func
(paren
id|socket
)paren
op_assign
id|config_readw
c_func
(paren
id|socket
comma
id|RL5C4XX_16BIT_IO_0
)paren
suffix:semicolon
id|rl_mem
c_func
(paren
id|socket
)paren
op_assign
id|config_readw
c_func
(paren
id|socket
comma
id|RL5C4XX_16BIT_MEM_0
)paren
suffix:semicolon
multiline_comment|/* Set the default timings, don&squot;t trust the original values */
id|rl_ctl
c_func
(paren
id|socket
)paren
op_assign
id|RL5C4XX_16CTL_IO_TIMING
op_or
id|RL5C4XX_16CTL_MEM_TIMING
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ricoh_init
r_static
r_int
id|ricoh_init
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
id|config_writew
c_func
(paren
id|socket
comma
id|RL5C4XX_MISC
comma
id|rl_misc
c_func
(paren
id|socket
)paren
)paren
suffix:semicolon
id|config_writew
c_func
(paren
id|socket
comma
id|RL5C4XX_16BIT_CTL
comma
id|rl_ctl
c_func
(paren
id|socket
)paren
)paren
suffix:semicolon
id|config_writew
c_func
(paren
id|socket
comma
id|RL5C4XX_16BIT_IO_0
comma
id|rl_io
c_func
(paren
id|socket
)paren
)paren
suffix:semicolon
id|config_writew
c_func
(paren
id|socket
comma
id|RL5C4XX_16BIT_MEM_0
comma
id|rl_mem
c_func
(paren
id|socket
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ricoh_ops
r_static
r_struct
id|pci_socket_ops
id|ricoh_ops
op_assign
(brace
id|ricoh_open
comma
id|yenta_close
comma
id|ricoh_init
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
macro_line|#endif /* _LINUX_RICOH_H */
eof
