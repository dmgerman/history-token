multiline_comment|/*&n; * o2micro.h 1.13 1999/10/25 20:03:34&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_O2MICRO_H
DECL|macro|_LINUX_O2MICRO_H
mdefine_line|#define _LINUX_O2MICRO_H
macro_line|#ifndef PCI_VENDOR_ID_O2
DECL|macro|PCI_VENDOR_ID_O2
mdefine_line|#define PCI_VENDOR_ID_O2&t;&t;0x1217
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_O2_6729
DECL|macro|PCI_DEVICE_ID_O2_6729
mdefine_line|#define PCI_DEVICE_ID_O2_6729&t;&t;0x6729
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_O2_6730
DECL|macro|PCI_DEVICE_ID_O2_6730
mdefine_line|#define PCI_DEVICE_ID_O2_6730&t;&t;0x673a
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_O2_6832
DECL|macro|PCI_DEVICE_ID_O2_6832
mdefine_line|#define PCI_DEVICE_ID_O2_6832&t;&t;0x6832
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_O2_6836
DECL|macro|PCI_DEVICE_ID_O2_6836
mdefine_line|#define PCI_DEVICE_ID_O2_6836&t;&t;0x6836
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_O2_6812
DECL|macro|PCI_DEVICE_ID_O2_6812
mdefine_line|#define PCI_DEVICE_ID_O2_6812&t;&t;0x6872
macro_line|#endif
multiline_comment|/* Additional PCI configuration registers */
DECL|macro|O2_MUX_CONTROL
mdefine_line|#define O2_MUX_CONTROL&t;&t;0x90&t;/* 32 bit */
DECL|macro|O2_MUX_RING_OUT
mdefine_line|#define  O2_MUX_RING_OUT&t;0x0000000f
DECL|macro|O2_MUX_SKTB_ACTV
mdefine_line|#define  O2_MUX_SKTB_ACTV&t;0x000000f0
DECL|macro|O2_MUX_SCTA_ACTV_ENA
mdefine_line|#define  O2_MUX_SCTA_ACTV_ENA&t;0x00000100
DECL|macro|O2_MUX_SCTB_ACTV_ENA
mdefine_line|#define  O2_MUX_SCTB_ACTV_ENA&t;0x00000200
DECL|macro|O2_MUX_SER_IRQ_ROUTE
mdefine_line|#define  O2_MUX_SER_IRQ_ROUTE&t;0x0000e000
DECL|macro|O2_MUX_SER_PCI
mdefine_line|#define  O2_MUX_SER_PCI&t;&t;0x00010000
DECL|macro|O2_MUX_SKTA_TURBO
mdefine_line|#define  O2_MUX_SKTA_TURBO&t;0x000c0000&t;/* for 6833, 6860 */
DECL|macro|O2_MUX_SKTB_TURBO
mdefine_line|#define  O2_MUX_SKTB_TURBO&t;0x00300000
DECL|macro|O2_MUX_AUX_VCC_3V
mdefine_line|#define  O2_MUX_AUX_VCC_3V&t;0x00400000
DECL|macro|O2_MUX_PCI_VCC_5V
mdefine_line|#define  O2_MUX_PCI_VCC_5V&t;0x00800000
DECL|macro|O2_MUX_PME_MUX
mdefine_line|#define  O2_MUX_PME_MUX&t;&t;0x0f000000
multiline_comment|/* Additional ExCA registers */
DECL|macro|O2_MODE_A
mdefine_line|#define O2_MODE_A&t;&t;0x38
DECL|macro|O2_MODE_A_2
mdefine_line|#define O2_MODE_A_2&t;&t;0x26&t;/* for 6833B, 6860C */
DECL|macro|O2_MODE_A_CD_PULSE
mdefine_line|#define  O2_MODE_A_CD_PULSE&t;0x04
DECL|macro|O2_MODE_A_SUSP_EDGE
mdefine_line|#define  O2_MODE_A_SUSP_EDGE&t;0x08
DECL|macro|O2_MODE_A_HOST_SUSP
mdefine_line|#define  O2_MODE_A_HOST_SUSP&t;0x10
DECL|macro|O2_MODE_A_PWR_MASK
mdefine_line|#define  O2_MODE_A_PWR_MASK&t;0x60
DECL|macro|O2_MODE_A_QUIET
mdefine_line|#define  O2_MODE_A_QUIET&t;0x80
DECL|macro|O2_MODE_B
mdefine_line|#define O2_MODE_B&t;&t;0x39
DECL|macro|O2_MODE_B_2
mdefine_line|#define O2_MODE_B_2&t;&t;0x2e&t;/* for 6833B, 6860C */
DECL|macro|O2_MODE_B_IDENT
mdefine_line|#define  O2_MODE_B_IDENT&t;0x03
DECL|macro|O2_MODE_B_ID_BSTEP
mdefine_line|#define  O2_MODE_B_ID_BSTEP&t;0x00
DECL|macro|O2_MODE_B_ID_CSTEP
mdefine_line|#define  O2_MODE_B_ID_CSTEP&t;0x01
DECL|macro|O2_MODE_B_ID_O2
mdefine_line|#define  O2_MODE_B_ID_O2&t;0x02
DECL|macro|O2_MODE_B_VS1
mdefine_line|#define  O2_MODE_B_VS1&t;&t;0x04
DECL|macro|O2_MODE_B_VS2
mdefine_line|#define  O2_MODE_B_VS2&t;&t;0x08
DECL|macro|O2_MODE_B_IRQ15_RI
mdefine_line|#define  O2_MODE_B_IRQ15_RI&t;0x80
DECL|macro|O2_MODE_C
mdefine_line|#define O2_MODE_C&t;&t;0x3a
DECL|macro|O2_MODE_C_DREQ_MASK
mdefine_line|#define  O2_MODE_C_DREQ_MASK&t;0x03
DECL|macro|O2_MODE_C_DREQ_INPACK
mdefine_line|#define  O2_MODE_C_DREQ_INPACK&t;0x01
DECL|macro|O2_MODE_C_DREQ_WP
mdefine_line|#define  O2_MODE_C_DREQ_WP&t;0x02
DECL|macro|O2_MODE_C_DREQ_BVD2
mdefine_line|#define  O2_MODE_C_DREQ_BVD2&t;0x03
DECL|macro|O2_MODE_C_ZVIDEO
mdefine_line|#define  O2_MODE_C_ZVIDEO&t;0x08
DECL|macro|O2_MODE_C_IREQ_SEL
mdefine_line|#define  O2_MODE_C_IREQ_SEL&t;0x30
DECL|macro|O2_MODE_C_MGMT_SEL
mdefine_line|#define  O2_MODE_C_MGMT_SEL&t;0xc0
DECL|macro|O2_MODE_D
mdefine_line|#define O2_MODE_D&t;&t;0x3b
DECL|macro|O2_MODE_D_IRQ_MODE
mdefine_line|#define  O2_MODE_D_IRQ_MODE&t;0x03
DECL|macro|O2_MODE_D_PCI_CLKRUN
mdefine_line|#define  O2_MODE_D_PCI_CLKRUN&t;0x04
DECL|macro|O2_MODE_D_CB_CLKRUN
mdefine_line|#define  O2_MODE_D_CB_CLKRUN&t;0x08
DECL|macro|O2_MODE_D_SKT_ACTV
mdefine_line|#define  O2_MODE_D_SKT_ACTV&t;0x20
DECL|macro|O2_MODE_D_PCI_FIFO
mdefine_line|#define  O2_MODE_D_PCI_FIFO&t;0x40&t;/* for OZ6729, OZ6730 */
DECL|macro|O2_MODE_D_W97_IRQ
mdefine_line|#define  O2_MODE_D_W97_IRQ&t;0x40
DECL|macro|O2_MODE_D_ISA_IRQ
mdefine_line|#define  O2_MODE_D_ISA_IRQ&t;0x80
DECL|macro|O2_MHPG_DMA
mdefine_line|#define O2_MHPG_DMA&t;&t;0x3c
DECL|macro|O2_MHPG_CHANNEL
mdefine_line|#define  O2_MHPG_CHANNEL&t;0x07
DECL|macro|O2_MHPG_CINT_ENA
mdefine_line|#define  O2_MHPG_CINT_ENA&t;0x08
DECL|macro|O2_MHPG_CSC_ENA
mdefine_line|#define  O2_MHPG_CSC_ENA&t;0x10
DECL|macro|O2_FIFO_ENA
mdefine_line|#define O2_FIFO_ENA&t;&t;0x3d
DECL|macro|O2_FIFO_ZVIDEO_3
mdefine_line|#define  O2_FIFO_ZVIDEO_3&t;0x08
DECL|macro|O2_FIFO_PCI_FIFO
mdefine_line|#define  O2_FIFO_PCI_FIFO&t;0x10
DECL|macro|O2_FIFO_POSTWR
mdefine_line|#define  O2_FIFO_POSTWR&t;&t;0x40
DECL|macro|O2_FIFO_BUFFER
mdefine_line|#define  O2_FIFO_BUFFER&t;&t;0x80
DECL|macro|O2_MODE_E
mdefine_line|#define O2_MODE_E&t;&t;0x3e
DECL|macro|O2_MODE_E_MHPG_DMA
mdefine_line|#define  O2_MODE_E_MHPG_DMA&t;0x01
DECL|macro|O2_MODE_E_SPKR_OUT
mdefine_line|#define  O2_MODE_E_SPKR_OUT&t;0x02
DECL|macro|O2_MODE_E_LED_OUT
mdefine_line|#define  O2_MODE_E_LED_OUT&t;0x08
DECL|macro|O2_MODE_E_SKTA_ACTV
mdefine_line|#define  O2_MODE_E_SKTA_ACTV&t;0x10
macro_line|#endif /* _LINUX_O2MICRO_H */
eof
