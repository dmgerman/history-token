multiline_comment|/*&n; * topic.h 1.8 1999/08/28 04:01:47&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@hyper.stanford.edu&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; * topic.h $Release$ 1999/08/28 04:01:47&n; */
macro_line|#ifndef _LINUX_TOPIC_H
DECL|macro|_LINUX_TOPIC_H
mdefine_line|#define _LINUX_TOPIC_H
macro_line|#ifndef PCI_VENDOR_ID_TOSHIBA
DECL|macro|PCI_VENDOR_ID_TOSHIBA
mdefine_line|#define PCI_VENDOR_ID_TOSHIBA&t;&t;0x1179
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TOSHIBA_TOPIC95_A
DECL|macro|PCI_DEVICE_ID_TOSHIBA_TOPIC95_A
mdefine_line|#define PCI_DEVICE_ID_TOSHIBA_TOPIC95_A&t;0x0603
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TOSHIBA_TOPIC95_B
DECL|macro|PCI_DEVICE_ID_TOSHIBA_TOPIC95_B
mdefine_line|#define PCI_DEVICE_ID_TOSHIBA_TOPIC95_B&t;0x060a
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TOSHIBA_TOPIC97
DECL|macro|PCI_DEVICE_ID_TOSHIBA_TOPIC97
mdefine_line|#define PCI_DEVICE_ID_TOSHIBA_TOPIC97&t;0x060f
macro_line|#endif
multiline_comment|/* Register definitions for Toshiba ToPIC95 controllers */
DECL|macro|TOPIC_SOCKET_CONTROL
mdefine_line|#define TOPIC_SOCKET_CONTROL&t;&t;0x0090&t;/* 32 bit */
DECL|macro|TOPIC_SCR_IRQSEL
mdefine_line|#define  TOPIC_SCR_IRQSEL&t;&t;0x00000001
DECL|macro|TOPIC_SLOT_CONTROL
mdefine_line|#define TOPIC_SLOT_CONTROL&t;&t;0x00a0&t;/* 8 bit */
DECL|macro|TOPIC_SLOT_SLOTON
mdefine_line|#define  TOPIC_SLOT_SLOTON&t;&t;0x80
DECL|macro|TOPIC_SLOT_SLOTEN
mdefine_line|#define  TOPIC_SLOT_SLOTEN&t;&t;0x40
DECL|macro|TOPIC_SLOT_ID_LOCK
mdefine_line|#define  TOPIC_SLOT_ID_LOCK&t;&t;0x20
DECL|macro|TOPIC_SLOT_ID_WP
mdefine_line|#define  TOPIC_SLOT_ID_WP&t;&t;0x10
DECL|macro|TOPIC_SLOT_PORT_MASK
mdefine_line|#define  TOPIC_SLOT_PORT_MASK&t;&t;0x0c
DECL|macro|TOPIC_SLOT_PORT_SHIFT
mdefine_line|#define  TOPIC_SLOT_PORT_SHIFT&t;&t;2
DECL|macro|TOPIC_SLOT_OFS_MASK
mdefine_line|#define  TOPIC_SLOT_OFS_MASK&t;&t;0x03
DECL|macro|TOPIC_CARD_CONTROL
mdefine_line|#define TOPIC_CARD_CONTROL&t;&t;0x00a1&t;/* 8 bit */
DECL|macro|TOPIC_CCR_INTB
mdefine_line|#define  TOPIC_CCR_INTB&t;&t;&t;0x20
DECL|macro|TOPIC_CCR_INTA
mdefine_line|#define  TOPIC_CCR_INTA&t;&t;&t;0x10
DECL|macro|TOPIC_CCR_CLOCK
mdefine_line|#define  TOPIC_CCR_CLOCK&t;&t;0x0c
DECL|macro|TOPIC_CCR_PCICLK
mdefine_line|#define  TOPIC_CCR_PCICLK&t;&t;0x0c
DECL|macro|TOPIC_CCR_PCICLK_2
mdefine_line|#define  TOPIC_CCR_PCICLK_2&t;&t;0x08
DECL|macro|TOPIC_CCR_CCLK
mdefine_line|#define  TOPIC_CCR_CCLK&t;&t;&t;0x04
DECL|macro|TOPIC97_INT_CONTROL
mdefine_line|#define TOPIC97_INT_CONTROL&t;&t;0x00a1&t;/* 8 bit */
DECL|macro|TOPIC97_ICR_INTB
mdefine_line|#define  TOPIC97_ICR_INTB&t;&t;0x20
DECL|macro|TOPIC97_ICR_INTA
mdefine_line|#define  TOPIC97_ICR_INTA&t;&t;0x10
DECL|macro|TOPIC97_ICR_STSIRQNP
mdefine_line|#define  TOPIC97_ICR_STSIRQNP&t;&t;0x04
DECL|macro|TOPIC97_ICR_IRQNP
mdefine_line|#define  TOPIC97_ICR_IRQNP&t;&t;0x02
DECL|macro|TOPIC97_ICR_IRQSEL
mdefine_line|#define  TOPIC97_ICR_IRQSEL&t;&t;0x01
DECL|macro|TOPIC_CARD_DETECT
mdefine_line|#define TOPIC_CARD_DETECT&t;&t;0x00a3&t;/* 8 bit */
DECL|macro|TOPIC_CDR_MODE_PC32
mdefine_line|#define  TOPIC_CDR_MODE_PC32&t;&t;0x80
DECL|macro|TOPIC_CDR_VS1
mdefine_line|#define  TOPIC_CDR_VS1&t;&t;&t;0x04
DECL|macro|TOPIC_CDR_VS2
mdefine_line|#define  TOPIC_CDR_VS2&t;&t;&t;0x02
DECL|macro|TOPIC_CDR_SW_DETECT
mdefine_line|#define  TOPIC_CDR_SW_DETECT&t;&t;0x01
DECL|macro|TOPIC_REGISTER_CONTROL
mdefine_line|#define TOPIC_REGISTER_CONTROL&t;&t;0x00a4&t;/* 32 bit */
DECL|macro|TOPIC_RCR_RESUME_RESET
mdefine_line|#define  TOPIC_RCR_RESUME_RESET&t;&t;0x80000000
DECL|macro|TOPIC_RCR_REMOVE_RESET
mdefine_line|#define  TOPIC_RCR_REMOVE_RESET&t;&t;0x40000000
DECL|macro|TOPIC97_RCR_CLKRUN_ENA
mdefine_line|#define  TOPIC97_RCR_CLKRUN_ENA&t;&t;0x20000000
DECL|macro|TOPIC97_RCR_TESTMODE
mdefine_line|#define  TOPIC97_RCR_TESTMODE&t;&t;0x10000000
DECL|macro|TOPIC97_RCR_IOPLUP
mdefine_line|#define  TOPIC97_RCR_IOPLUP&t;&t;0x08000000
DECL|macro|TOPIC_RCR_BUFOFF_PWROFF
mdefine_line|#define  TOPIC_RCR_BUFOFF_PWROFF&t;0x02000000
DECL|macro|TOPIC_RCR_BUFOFF_SIGOFF
mdefine_line|#define  TOPIC_RCR_BUFOFF_SIGOFF&t;0x01000000
DECL|macro|TOPIC97_RCR_CB_DEV_MASK
mdefine_line|#define  TOPIC97_RCR_CB_DEV_MASK&t;0x0000f800
DECL|macro|TOPIC97_RCR_CB_DEV_SHIFT
mdefine_line|#define  TOPIC97_RCR_CB_DEV_SHIFT&t;11
DECL|macro|TOPIC97_RCR_RI_DISABLE
mdefine_line|#define  TOPIC97_RCR_RI_DISABLE&t;&t;0x00000004
DECL|macro|TOPIC97_RCR_CAUDIO_OFF
mdefine_line|#define  TOPIC97_RCR_CAUDIO_OFF&t;&t;0x00000002
DECL|macro|TOPIC_RCR_CAUDIO_INVERT
mdefine_line|#define  TOPIC_RCR_CAUDIO_INVERT&t;0x00000001
macro_line|#endif /* _LINUX_TOPIC_H */
eof
