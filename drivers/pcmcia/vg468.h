multiline_comment|/*&n; * vg468.h 1.11 1999/10/25 20:03:34&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_VG468_H
DECL|macro|_LINUX_VG468_H
mdefine_line|#define _LINUX_VG468_H
multiline_comment|/* Special bit in I365_IDENT used for Vadem chip detection */
DECL|macro|I365_IDENT_VADEM
mdefine_line|#define I365_IDENT_VADEM&t;0x08
multiline_comment|/* Special definitions in I365_POWER */
DECL|macro|VG468_VPP2_MASK
mdefine_line|#define VG468_VPP2_MASK&t;&t;0x0c
DECL|macro|VG468_VPP2_5V
mdefine_line|#define VG468_VPP2_5V&t;&t;0x04
DECL|macro|VG468_VPP2_12V
mdefine_line|#define VG468_VPP2_12V&t;&t;0x08
multiline_comment|/* Unique Vadem registers */
DECL|macro|VG469_VSENSE
mdefine_line|#define VG469_VSENSE&t;&t;0x1f&t;/* Card voltage sense */
DECL|macro|VG469_VSELECT
mdefine_line|#define VG469_VSELECT&t;&t;0x2f&t;/* Card voltage select */
DECL|macro|VG468_CTL
mdefine_line|#define VG468_CTL&t;&t;0x38&t;/* Control register */
DECL|macro|VG468_TIMER
mdefine_line|#define VG468_TIMER&t;&t;0x39&t;/* Timer control */
DECL|macro|VG468_MISC
mdefine_line|#define VG468_MISC&t;&t;0x3a&t;/* Miscellaneous */
DECL|macro|VG468_GPIO_CFG
mdefine_line|#define VG468_GPIO_CFG&t;&t;0x3b&t;/* GPIO configuration */
DECL|macro|VG469_EXT_MODE
mdefine_line|#define VG469_EXT_MODE&t;&t;0x3c&t;/* Extended mode register */
DECL|macro|VG468_SELECT
mdefine_line|#define VG468_SELECT&t;&t;0x3d&t;/* Programmable chip select */
DECL|macro|VG468_SELECT_CFG
mdefine_line|#define VG468_SELECT_CFG&t;0x3e&t;/* Chip select configuration */
DECL|macro|VG468_ATA
mdefine_line|#define VG468_ATA&t;&t;0x3f&t;/* ATA control */
multiline_comment|/* Flags for VG469_VSENSE */
DECL|macro|VG469_VSENSE_A_VS1
mdefine_line|#define VG469_VSENSE_A_VS1&t;0x01
DECL|macro|VG469_VSENSE_A_VS2
mdefine_line|#define VG469_VSENSE_A_VS2&t;0x02
DECL|macro|VG469_VSENSE_B_VS1
mdefine_line|#define VG469_VSENSE_B_VS1&t;0x04
DECL|macro|VG469_VSENSE_B_VS2
mdefine_line|#define VG469_VSENSE_B_VS2&t;0x08
multiline_comment|/* Flags for VG469_VSELECT */
DECL|macro|VG469_VSEL_VCC
mdefine_line|#define VG469_VSEL_VCC&t;&t;0x03
DECL|macro|VG469_VSEL_5V
mdefine_line|#define VG469_VSEL_5V&t;&t;0x00
DECL|macro|VG469_VSEL_3V
mdefine_line|#define VG469_VSEL_3V&t;&t;0x03
DECL|macro|VG469_VSEL_MAX
mdefine_line|#define VG469_VSEL_MAX&t;&t;0x0c
DECL|macro|VG469_VSEL_EXT_STAT
mdefine_line|#define VG469_VSEL_EXT_STAT&t;0x10
DECL|macro|VG469_VSEL_EXT_BUS
mdefine_line|#define VG469_VSEL_EXT_BUS&t;0x20
DECL|macro|VG469_VSEL_MIXED
mdefine_line|#define VG469_VSEL_MIXED&t;0x40
DECL|macro|VG469_VSEL_ISA
mdefine_line|#define VG469_VSEL_ISA&t;&t;0x80
multiline_comment|/* Flags for VG468_CTL */
DECL|macro|VG468_CTL_SLOW
mdefine_line|#define VG468_CTL_SLOW&t;&t;0x01&t;/* 600ns memory timing */
DECL|macro|VG468_CTL_ASYNC
mdefine_line|#define VG468_CTL_ASYNC&t;&t;0x02&t;/* Asynchronous bus clocking */
DECL|macro|VG468_CTL_TSSI
mdefine_line|#define VG468_CTL_TSSI&t;&t;0x08&t;/* Tri-state some outputs */
DECL|macro|VG468_CTL_DELAY
mdefine_line|#define VG468_CTL_DELAY&t;&t;0x10&t;/* Card detect debounce */
DECL|macro|VG468_CTL_INPACK
mdefine_line|#define VG468_CTL_INPACK&t;0x20&t;/* Obey INPACK signal? */
DECL|macro|VG468_CTL_POLARITY
mdefine_line|#define VG468_CTL_POLARITY&t;0x40&t;/* VCCEN polarity */
DECL|macro|VG468_CTL_COMPAT
mdefine_line|#define VG468_CTL_COMPAT&t;0x80&t;/* Compatibility stuff */
DECL|macro|VG469_CTL_WS_COMPAT
mdefine_line|#define VG469_CTL_WS_COMPAT&t;0x04&t;/* Wait state compatibility */
DECL|macro|VG469_CTL_STRETCH
mdefine_line|#define VG469_CTL_STRETCH&t;0x10&t;/* LED stretch */
multiline_comment|/* Flags for VG468_TIMER */
DECL|macro|VG468_TIMER_ZEROPWR
mdefine_line|#define VG468_TIMER_ZEROPWR&t;0x10&t;/* Zero power control */
DECL|macro|VG468_TIMER_SIGEN
mdefine_line|#define VG468_TIMER_SIGEN&t;0x20&t;/* Power up */
DECL|macro|VG468_TIMER_STATUS
mdefine_line|#define VG468_TIMER_STATUS&t;0x40&t;/* Activity timer status */
DECL|macro|VG468_TIMER_RES
mdefine_line|#define VG468_TIMER_RES&t;&t;0x80&t;/* Timer resolution */
DECL|macro|VG468_TIMER_MASK
mdefine_line|#define VG468_TIMER_MASK&t;0x0f&t;/* Activity timer timeout */
multiline_comment|/* Flags for VG468_MISC */
DECL|macro|VG468_MISC_GPIO
mdefine_line|#define VG468_MISC_GPIO&t;&t;0x04&t;/* General-purpose IO */
DECL|macro|VG468_MISC_DMAWSB
mdefine_line|#define VG468_MISC_DMAWSB&t;0x08&t;/* DMA wait state control */
DECL|macro|VG469_MISC_LEDENA
mdefine_line|#define VG469_MISC_LEDENA&t;0x10&t;/* LED enable */
DECL|macro|VG468_MISC_VADEMREV
mdefine_line|#define VG468_MISC_VADEMREV&t;0x40&t;/* Vadem revision control */
DECL|macro|VG468_MISC_UNLOCK
mdefine_line|#define VG468_MISC_UNLOCK&t;0x80&t;/* Unique register lock */
multiline_comment|/* Flags for VG469_EXT_MODE_A */
DECL|macro|VG469_MODE_VPPST
mdefine_line|#define VG469_MODE_VPPST&t;0x03&t;/* Vpp steering control */
DECL|macro|VG469_MODE_INT_SENSE
mdefine_line|#define VG469_MODE_INT_SENSE&t;0x04&t;/* Internal voltage sense */
DECL|macro|VG469_MODE_CABLE
mdefine_line|#define VG469_MODE_CABLE&t;0x08
DECL|macro|VG469_MODE_COMPAT
mdefine_line|#define VG469_MODE_COMPAT&t;0x10&t;/* i82365sl B or DF step */
DECL|macro|VG469_MODE_TEST
mdefine_line|#define VG469_MODE_TEST&t;&t;0x20
DECL|macro|VG469_MODE_RIO
mdefine_line|#define VG469_MODE_RIO&t;&t;0x40&t;/* Steer RIO to INTR? */
multiline_comment|/* Flags for VG469_EXT_MODE_B */
DECL|macro|VG469_MODE_B_3V
mdefine_line|#define VG469_MODE_B_3V&t;&t;0x01&t;/* 3.3v for socket B */
macro_line|#endif /* _LINUX_VG468_H */
eof
