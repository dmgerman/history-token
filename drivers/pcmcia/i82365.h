multiline_comment|/*&n; * i82365.h 1.15 1999/10/25 20:03:34&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_I82365_H
DECL|macro|_LINUX_I82365_H
mdefine_line|#define _LINUX_I82365_H
multiline_comment|/* register definitions for the Intel 82365SL PCMCIA controller */
multiline_comment|/* Offsets for PCIC registers */
DECL|macro|I365_IDENT
mdefine_line|#define I365_IDENT&t;0x00&t;/* Identification and revision */
DECL|macro|I365_STATUS
mdefine_line|#define I365_STATUS&t;0x01&t;/* Interface status */
DECL|macro|I365_POWER
mdefine_line|#define I365_POWER&t;0x02&t;/* Power and RESETDRV control */
DECL|macro|I365_INTCTL
mdefine_line|#define I365_INTCTL&t;0x03&t;/* Interrupt and general control */
DECL|macro|I365_CSC
mdefine_line|#define I365_CSC&t;0x04&t;/* Card status change */
DECL|macro|I365_CSCINT
mdefine_line|#define I365_CSCINT&t;0x05&t;/* Card status change interrupt control */
DECL|macro|I365_ADDRWIN
mdefine_line|#define I365_ADDRWIN&t;0x06&t;/* Address window enable */
DECL|macro|I365_IOCTL
mdefine_line|#define I365_IOCTL&t;0x07&t;/* I/O control */
DECL|macro|I365_GENCTL
mdefine_line|#define I365_GENCTL&t;0x16&t;/* Card detect and general control */
DECL|macro|I365_GBLCTL
mdefine_line|#define I365_GBLCTL&t;0x1E&t;/* Global control register */
multiline_comment|/* Offsets for I/O and memory window registers */
DECL|macro|I365_IO
mdefine_line|#define I365_IO(map)&t;(0x08+((map)&lt;&lt;2))
DECL|macro|I365_MEM
mdefine_line|#define I365_MEM(map)&t;(0x10+((map)&lt;&lt;3))
DECL|macro|I365_W_START
mdefine_line|#define I365_W_START&t;0
DECL|macro|I365_W_STOP
mdefine_line|#define I365_W_STOP&t;2
DECL|macro|I365_W_OFF
mdefine_line|#define I365_W_OFF&t;4
multiline_comment|/* Flags for I365_STATUS */
DECL|macro|I365_CS_BVD1
mdefine_line|#define I365_CS_BVD1&t;0x01
DECL|macro|I365_CS_STSCHG
mdefine_line|#define I365_CS_STSCHG&t;0x01
DECL|macro|I365_CS_BVD2
mdefine_line|#define I365_CS_BVD2&t;0x02
DECL|macro|I365_CS_SPKR
mdefine_line|#define I365_CS_SPKR&t;0x02
DECL|macro|I365_CS_DETECT
mdefine_line|#define I365_CS_DETECT&t;0x0C
DECL|macro|I365_CS_WRPROT
mdefine_line|#define I365_CS_WRPROT&t;0x10
DECL|macro|I365_CS_READY
mdefine_line|#define I365_CS_READY&t;0x20&t;/* Inverted */
DECL|macro|I365_CS_POWERON
mdefine_line|#define I365_CS_POWERON&t;0x40
DECL|macro|I365_CS_GPI
mdefine_line|#define I365_CS_GPI&t;0x80
multiline_comment|/* Flags for I365_POWER */
DECL|macro|I365_PWR_OFF
mdefine_line|#define I365_PWR_OFF&t;0x00&t;/* Turn off the socket */
DECL|macro|I365_PWR_OUT
mdefine_line|#define I365_PWR_OUT&t;0x80&t;/* Output enable */
DECL|macro|I365_PWR_NORESET
mdefine_line|#define I365_PWR_NORESET 0x40&t;/* Disable RESETDRV on resume */
DECL|macro|I365_PWR_AUTO
mdefine_line|#define I365_PWR_AUTO&t;0x20&t;/* Auto pwr switch enable */
DECL|macro|I365_VCC_MASK
mdefine_line|#define I365_VCC_MASK&t;0x18&t;/* Mask for turning off Vcc */
multiline_comment|/* There are different layouts for B-step and DF-step chips: the B&n;   step has independent Vpp1/Vpp2 control, and the DF step has only&n;   Vpp1 control, plus 3V control */
DECL|macro|I365_VCC_5V
mdefine_line|#define I365_VCC_5V&t;0x10&t;/* Vcc = 5.0v */
DECL|macro|I365_VCC_3V
mdefine_line|#define I365_VCC_3V&t;0x18&t;/* Vcc = 3.3v */
DECL|macro|I365_VPP2_MASK
mdefine_line|#define I365_VPP2_MASK&t;0x0c&t;/* Mask for turning off Vpp2 */
DECL|macro|I365_VPP2_5V
mdefine_line|#define I365_VPP2_5V&t;0x04&t;/* Vpp2 = 5.0v */
DECL|macro|I365_VPP2_12V
mdefine_line|#define I365_VPP2_12V&t;0x08&t;/* Vpp2 = 12.0v */
DECL|macro|I365_VPP1_MASK
mdefine_line|#define I365_VPP1_MASK&t;0x03&t;/* Mask for turning off Vpp1 */
DECL|macro|I365_VPP1_5V
mdefine_line|#define I365_VPP1_5V&t;0x01&t;/* Vpp2 = 5.0v */
DECL|macro|I365_VPP1_12V
mdefine_line|#define I365_VPP1_12V&t;0x02&t;/* Vpp2 = 12.0v */
multiline_comment|/* Flags for I365_INTCTL */
DECL|macro|I365_RING_ENA
mdefine_line|#define I365_RING_ENA&t;0x80
DECL|macro|I365_PC_RESET
mdefine_line|#define I365_PC_RESET&t;0x40
DECL|macro|I365_PC_IOCARD
mdefine_line|#define I365_PC_IOCARD&t;0x20
DECL|macro|I365_INTR_ENA
mdefine_line|#define I365_INTR_ENA&t;0x10
DECL|macro|I365_IRQ_MASK
mdefine_line|#define I365_IRQ_MASK&t;0x0F
multiline_comment|/* Flags for I365_CSC and I365_CSCINT*/
DECL|macro|I365_CSC_BVD1
mdefine_line|#define I365_CSC_BVD1&t;0x01
DECL|macro|I365_CSC_STSCHG
mdefine_line|#define I365_CSC_STSCHG&t;0x01
DECL|macro|I365_CSC_BVD2
mdefine_line|#define I365_CSC_BVD2&t;0x02
DECL|macro|I365_CSC_READY
mdefine_line|#define I365_CSC_READY&t;0x04
DECL|macro|I365_CSC_DETECT
mdefine_line|#define I365_CSC_DETECT&t;0x08
DECL|macro|I365_CSC_ANY
mdefine_line|#define I365_CSC_ANY&t;0x0F
DECL|macro|I365_CSC_GPI
mdefine_line|#define I365_CSC_GPI&t;0x10
multiline_comment|/* Flags for I365_ADDRWIN */
DECL|macro|I365_ENA_IO
mdefine_line|#define I365_ENA_IO(map)&t;(0x40 &lt;&lt; (map))
DECL|macro|I365_ENA_MEM
mdefine_line|#define I365_ENA_MEM(map)&t;(0x01 &lt;&lt; (map))
multiline_comment|/* Flags for I365_IOCTL */
DECL|macro|I365_IOCTL_MASK
mdefine_line|#define I365_IOCTL_MASK(map)&t;(0x0F &lt;&lt; (map&lt;&lt;2))
DECL|macro|I365_IOCTL_WAIT
mdefine_line|#define I365_IOCTL_WAIT(map)&t;(0x08 &lt;&lt; (map&lt;&lt;2))
DECL|macro|I365_IOCTL_0WS
mdefine_line|#define I365_IOCTL_0WS(map)&t;(0x04 &lt;&lt; (map&lt;&lt;2))
DECL|macro|I365_IOCTL_IOCS16
mdefine_line|#define I365_IOCTL_IOCS16(map)&t;(0x02 &lt;&lt; (map&lt;&lt;2))
DECL|macro|I365_IOCTL_16BIT
mdefine_line|#define I365_IOCTL_16BIT(map)&t;(0x01 &lt;&lt; (map&lt;&lt;2))
multiline_comment|/* Flags for I365_GENCTL */
DECL|macro|I365_CTL_16DELAY
mdefine_line|#define I365_CTL_16DELAY&t;0x01
DECL|macro|I365_CTL_RESET
mdefine_line|#define I365_CTL_RESET&t;&t;0x02
DECL|macro|I365_CTL_GPI_ENA
mdefine_line|#define I365_CTL_GPI_ENA&t;0x04
DECL|macro|I365_CTL_GPI_CTL
mdefine_line|#define I365_CTL_GPI_CTL&t;0x08
DECL|macro|I365_CTL_RESUME
mdefine_line|#define I365_CTL_RESUME&t;&t;0x10
DECL|macro|I365_CTL_SW_IRQ
mdefine_line|#define I365_CTL_SW_IRQ&t;&t;0x20
multiline_comment|/* Flags for I365_GBLCTL */
DECL|macro|I365_GBL_PWRDOWN
mdefine_line|#define I365_GBL_PWRDOWN&t;0x01
DECL|macro|I365_GBL_CSC_LEV
mdefine_line|#define I365_GBL_CSC_LEV&t;0x02
DECL|macro|I365_GBL_WRBACK
mdefine_line|#define I365_GBL_WRBACK&t;&t;0x04
DECL|macro|I365_GBL_IRQ_0_LEV
mdefine_line|#define I365_GBL_IRQ_0_LEV&t;0x08
DECL|macro|I365_GBL_IRQ_1_LEV
mdefine_line|#define I365_GBL_IRQ_1_LEV&t;0x10
multiline_comment|/* Flags for memory window registers */
DECL|macro|I365_MEM_16BIT
mdefine_line|#define I365_MEM_16BIT&t;0x8000&t;/* In memory start high byte */
DECL|macro|I365_MEM_0WS
mdefine_line|#define I365_MEM_0WS&t;0x4000
DECL|macro|I365_MEM_WS1
mdefine_line|#define I365_MEM_WS1&t;0x8000&t;/* In memory stop high byte */
DECL|macro|I365_MEM_WS0
mdefine_line|#define I365_MEM_WS0&t;0x4000
DECL|macro|I365_MEM_WRPROT
mdefine_line|#define I365_MEM_WRPROT&t;0x8000&t;/* In offset high byte */
DECL|macro|I365_MEM_REG
mdefine_line|#define I365_MEM_REG&t;0x4000
DECL|macro|I365_REG
mdefine_line|#define I365_REG(slot, reg)&t;(((slot) &lt;&lt; 6) + reg)
macro_line|#endif /* _LINUX_I82365_H */
eof
