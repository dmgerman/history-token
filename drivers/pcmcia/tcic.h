multiline_comment|/*&n; * tcic.h 1.13 1999/10/25 20:03:34&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_TCIC_H
DECL|macro|_LINUX_TCIC_H
mdefine_line|#define _LINUX_TCIC_H
DECL|macro|TCIC_BASE
mdefine_line|#define TCIC_BASE&t;&t;0x240
multiline_comment|/* offsets of registers from TCIC_BASE */
DECL|macro|TCIC_DATA
mdefine_line|#define TCIC_DATA&t;&t;0x00
DECL|macro|TCIC_ADDR
mdefine_line|#define TCIC_ADDR&t;&t;0x02
DECL|macro|TCIC_SCTRL
mdefine_line|#define TCIC_SCTRL&t;&t;0x06
DECL|macro|TCIC_SSTAT
mdefine_line|#define TCIC_SSTAT&t;&t;0x07
DECL|macro|TCIC_MODE
mdefine_line|#define TCIC_MODE&t;&t;0x08
DECL|macro|TCIC_PWR
mdefine_line|#define TCIC_PWR&t;&t;0x09
DECL|macro|TCIC_EDC
mdefine_line|#define TCIC_EDC&t;&t;0x0A
DECL|macro|TCIC_ICSR
mdefine_line|#define TCIC_ICSR&t;&t;0x0C
DECL|macro|TCIC_IENA
mdefine_line|#define TCIC_IENA&t;&t;0x0D
DECL|macro|TCIC_AUX
mdefine_line|#define TCIC_AUX&t;&t;0x0E
DECL|macro|TCIC_SS_SHFT
mdefine_line|#define TCIC_SS_SHFT&t;&t;12
DECL|macro|TCIC_SS_MASK
mdefine_line|#define TCIC_SS_MASK&t;&t;0x7000
multiline_comment|/* Flags for TCIC_ADDR */
DECL|macro|TCIC_ADR2_REG
mdefine_line|#define TCIC_ADR2_REG&t;&t;0x8000
DECL|macro|TCIC_ADR2_INDREG
mdefine_line|#define TCIC_ADR2_INDREG&t;0x0800
DECL|macro|TCIC_ADDR_REG
mdefine_line|#define TCIC_ADDR_REG&t;&t;0x80000000
DECL|macro|TCIC_ADDR_SS_SHFT
mdefine_line|#define TCIC_ADDR_SS_SHFT&t;(TCIC_SS_SHFT+16)
DECL|macro|TCIC_ADDR_SS_MASK
mdefine_line|#define TCIC_ADDR_SS_MASK&t;(TCIC_SS_MASK&lt;&lt;16)
DECL|macro|TCIC_ADDR_INDREG
mdefine_line|#define TCIC_ADDR_INDREG&t;0x08000000
DECL|macro|TCIC_ADDR_IO
mdefine_line|#define TCIC_ADDR_IO&t;&t;0x04000000
DECL|macro|TCIC_ADDR_MASK
mdefine_line|#define TCIC_ADDR_MASK&t;&t;0x03ffffff
multiline_comment|/* Flags for TCIC_SCTRL */
DECL|macro|TCIC_SCTRL_ENA
mdefine_line|#define TCIC_SCTRL_ENA&t;&t;0x01
DECL|macro|TCIC_SCTRL_INCMODE
mdefine_line|#define TCIC_SCTRL_INCMODE&t;0x18
DECL|macro|TCIC_SCTRL_INCMODE_HOLD
mdefine_line|#define TCIC_SCTRL_INCMODE_HOLD&t;0x00
DECL|macro|TCIC_SCTRL_INCMODE_WORD
mdefine_line|#define TCIC_SCTRL_INCMODE_WORD&t;0x08
DECL|macro|TCIC_SCTRL_INCMODE_REG
mdefine_line|#define TCIC_SCTRL_INCMODE_REG&t;0x10
DECL|macro|TCIC_SCTRL_INCMODE_AUTO
mdefine_line|#define TCIC_SCTRL_INCMODE_AUTO&t;0x18
DECL|macro|TCIC_SCTRL_EDCSUM
mdefine_line|#define TCIC_SCTRL_EDCSUM&t;0x20
DECL|macro|TCIC_SCTRL_RESET
mdefine_line|#define TCIC_SCTRL_RESET&t;0x80
multiline_comment|/* Flags for TCIC_SSTAT */
DECL|macro|TCIC_SSTAT_6US
mdefine_line|#define TCIC_SSTAT_6US&t;&t;0x01
DECL|macro|TCIC_SSTAT_10US
mdefine_line|#define TCIC_SSTAT_10US&t;&t;0x02
DECL|macro|TCIC_SSTAT_PROGTIME
mdefine_line|#define TCIC_SSTAT_PROGTIME&t;0x04
DECL|macro|TCIC_SSTAT_LBAT1
mdefine_line|#define TCIC_SSTAT_LBAT1&t;0x08
DECL|macro|TCIC_SSTAT_LBAT2
mdefine_line|#define TCIC_SSTAT_LBAT2&t;0x10
DECL|macro|TCIC_SSTAT_RDY
mdefine_line|#define TCIC_SSTAT_RDY&t;&t;0x20&t;/* Inverted */
DECL|macro|TCIC_SSTAT_WP
mdefine_line|#define TCIC_SSTAT_WP&t;&t;0x40
DECL|macro|TCIC_SSTAT_CD
mdefine_line|#define TCIC_SSTAT_CD&t;&t;0x80&t;/* Card detect */
multiline_comment|/* Flags for TCIC_MODE */
DECL|macro|TCIC_MODE_PGMMASK
mdefine_line|#define TCIC_MODE_PGMMASK&t;0x1f
DECL|macro|TCIC_MODE_NORMAL
mdefine_line|#define TCIC_MODE_NORMAL&t;0x00
DECL|macro|TCIC_MODE_PGMWR
mdefine_line|#define TCIC_MODE_PGMWR&t;&t;0x01
DECL|macro|TCIC_MODE_PGMRD
mdefine_line|#define TCIC_MODE_PGMRD&t;&t;0x02
DECL|macro|TCIC_MODE_PGMCE
mdefine_line|#define TCIC_MODE_PGMCE&t;&t;0x04
DECL|macro|TCIC_MODE_PGMDBW
mdefine_line|#define TCIC_MODE_PGMDBW&t;0x08
DECL|macro|TCIC_MODE_PGMWORD
mdefine_line|#define TCIC_MODE_PGMWORD&t;0x10
DECL|macro|TCIC_MODE_AUXSEL_MASK
mdefine_line|#define TCIC_MODE_AUXSEL_MASK&t;0xe0
multiline_comment|/* Registers accessed through TCIC_AUX, by setting TCIC_MODE */
DECL|macro|TCIC_AUX_TCTL
mdefine_line|#define TCIC_AUX_TCTL&t;&t;(0&lt;&lt;5)
DECL|macro|TCIC_AUX_PCTL
mdefine_line|#define TCIC_AUX_PCTL&t;&t;(1&lt;&lt;5)
DECL|macro|TCIC_AUX_WCTL
mdefine_line|#define TCIC_AUX_WCTL&t;&t;(2&lt;&lt;5)
DECL|macro|TCIC_AUX_EXTERN
mdefine_line|#define TCIC_AUX_EXTERN&t;&t;(3&lt;&lt;5)
DECL|macro|TCIC_AUX_PDATA
mdefine_line|#define TCIC_AUX_PDATA&t;&t;(4&lt;&lt;5)
DECL|macro|TCIC_AUX_SYSCFG
mdefine_line|#define TCIC_AUX_SYSCFG&t;&t;(5&lt;&lt;5)
DECL|macro|TCIC_AUX_ILOCK
mdefine_line|#define TCIC_AUX_ILOCK&t;&t;(6&lt;&lt;5)
DECL|macro|TCIC_AUX_TEST
mdefine_line|#define TCIC_AUX_TEST&t;&t;(7&lt;&lt;5)
multiline_comment|/* Flags for TCIC_PWR */
DECL|macro|TCIC_PWR_VCC
mdefine_line|#define TCIC_PWR_VCC(sock)&t;(0x01&lt;&lt;(sock))
DECL|macro|TCIC_PWR_VCC_MASK
mdefine_line|#define TCIC_PWR_VCC_MASK&t;0x03
DECL|macro|TCIC_PWR_VPP
mdefine_line|#define TCIC_PWR_VPP(sock)&t;(0x08&lt;&lt;(sock))
DECL|macro|TCIC_PWR_VPP_MASK
mdefine_line|#define TCIC_PWR_VPP_MASK&t;0x18
DECL|macro|TCIC_PWR_CLIMENA
mdefine_line|#define TCIC_PWR_CLIMENA&t;0x40
DECL|macro|TCIC_PWR_CLIMSTAT
mdefine_line|#define TCIC_PWR_CLIMSTAT&t;0x80
multiline_comment|/* Flags for TCIC_ICSR */
DECL|macro|TCIC_ICSR_CLEAR
mdefine_line|#define TCIC_ICSR_CLEAR&t;&t;0x01
DECL|macro|TCIC_ICSR_SET
mdefine_line|#define TCIC_ICSR_SET&t;&t;0x02
DECL|macro|TCIC_ICSR_JAM
mdefine_line|#define TCIC_ICSR_JAM&t;&t;(TCIC_ICSR_CLEAR|TCIC_ICSR_SET)
DECL|macro|TCIC_ICSR_STOPCPU
mdefine_line|#define TCIC_ICSR_STOPCPU&t;0x04
DECL|macro|TCIC_ICSR_ILOCK
mdefine_line|#define TCIC_ICSR_ILOCK&t;&t;0x08
DECL|macro|TCIC_ICSR_PROGTIME
mdefine_line|#define TCIC_ICSR_PROGTIME&t;0x10
DECL|macro|TCIC_ICSR_ERR
mdefine_line|#define TCIC_ICSR_ERR&t;&t;0x20
DECL|macro|TCIC_ICSR_CDCHG
mdefine_line|#define TCIC_ICSR_CDCHG&t;&t;0x40
DECL|macro|TCIC_ICSR_IOCHK
mdefine_line|#define TCIC_ICSR_IOCHK&t;&t;0x80
multiline_comment|/* Flags for TCIC_IENA */
DECL|macro|TCIC_IENA_CFG_MASK
mdefine_line|#define TCIC_IENA_CFG_MASK&t;0x03
DECL|macro|TCIC_IENA_CFG_OFF
mdefine_line|#define TCIC_IENA_CFG_OFF&t;0x00&t;/* disabled */
DECL|macro|TCIC_IENA_CFG_OD
mdefine_line|#define TCIC_IENA_CFG_OD&t;0x01&t;/* active low, open drain */
DECL|macro|TCIC_IENA_CFG_LOW
mdefine_line|#define TCIC_IENA_CFG_LOW&t;0x02&t;/* active low, totem pole */
DECL|macro|TCIC_IENA_CFG_HIGH
mdefine_line|#define TCIC_IENA_CFG_HIGH&t;0x03&t;/* active high, totem pole */
DECL|macro|TCIC_IENA_ILOCK
mdefine_line|#define TCIC_IENA_ILOCK&t;&t;0x08
DECL|macro|TCIC_IENA_PROGTIME
mdefine_line|#define TCIC_IENA_PROGTIME&t;0x10
DECL|macro|TCIC_IENA_ERR
mdefine_line|#define TCIC_IENA_ERR&t;&t;0x20&t;/* overcurrent or iochk */
DECL|macro|TCIC_IENA_CDCHG
mdefine_line|#define TCIC_IENA_CDCHG&t;&t;0x40
multiline_comment|/* Flags for TCIC_AUX_WCTL */
DECL|macro|TCIC_WAIT_COUNT_MASK
mdefine_line|#define TCIC_WAIT_COUNT_MASK&t;0x001f
DECL|macro|TCIC_WAIT_ASYNC
mdefine_line|#define TCIC_WAIT_ASYNC&t;&t;0x0020
DECL|macro|TCIC_WAIT_SENSE
mdefine_line|#define TCIC_WAIT_SENSE&t;&t;0x0040
DECL|macro|TCIC_WAIT_SRC
mdefine_line|#define TCIC_WAIT_SRC&t;&t;0x0080
DECL|macro|TCIC_WCTL_WR
mdefine_line|#define TCIC_WCTL_WR&t;&t;0x0100
DECL|macro|TCIC_WCTL_RD
mdefine_line|#define TCIC_WCTL_RD&t;&t;0x0200
DECL|macro|TCIC_WCTL_CE
mdefine_line|#define TCIC_WCTL_CE&t;&t;0x0400
DECL|macro|TCIC_WCTL_LLBAT1
mdefine_line|#define TCIC_WCTL_LLBAT1&t;0x0800
DECL|macro|TCIC_WCTL_LLBAT2
mdefine_line|#define TCIC_WCTL_LLBAT2&t;0x1000
DECL|macro|TCIC_WCTL_LRDY
mdefine_line|#define TCIC_WCTL_LRDY&t;&t;0x2000
DECL|macro|TCIC_WCTL_LWP
mdefine_line|#define TCIC_WCTL_LWP&t;&t;0x4000
DECL|macro|TCIC_WCTL_LCD
mdefine_line|#define TCIC_WCTL_LCD&t;&t;0x8000
multiline_comment|/* Flags for TCIC_AUX_SYSCFG */
DECL|macro|TCIC_SYSCFG_IRQ_MASK
mdefine_line|#define TCIC_SYSCFG_IRQ_MASK&t;0x000f
DECL|macro|TCIC_SYSCFG_MCSFULL
mdefine_line|#define TCIC_SYSCFG_MCSFULL&t;0x0010
DECL|macro|TCIC_SYSCFG_IO1723
mdefine_line|#define TCIC_SYSCFG_IO1723&t;0x0020
DECL|macro|TCIC_SYSCFG_MCSXB
mdefine_line|#define TCIC_SYSCFG_MCSXB&t;0x0040
DECL|macro|TCIC_SYSCFG_ICSXB
mdefine_line|#define TCIC_SYSCFG_ICSXB&t;0x0080
DECL|macro|TCIC_SYSCFG_NOPDN
mdefine_line|#define TCIC_SYSCFG_NOPDN&t;0x0100
DECL|macro|TCIC_SYSCFG_MPSEL_SHFT
mdefine_line|#define TCIC_SYSCFG_MPSEL_SHFT&t;9
DECL|macro|TCIC_SYSCFG_MPSEL_MASK
mdefine_line|#define TCIC_SYSCFG_MPSEL_MASK&t;0x0e00
DECL|macro|TCIC_SYSCFG_MPSENSE
mdefine_line|#define TCIC_SYSCFG_MPSENSE&t;0x2000
DECL|macro|TCIC_SYSCFG_AUTOBUSY
mdefine_line|#define TCIC_SYSCFG_AUTOBUSY&t;0x4000
DECL|macro|TCIC_SYSCFG_ACC
mdefine_line|#define TCIC_SYSCFG_ACC&t;&t;0x8000
DECL|macro|TCIC_ILOCK_OUT
mdefine_line|#define TCIC_ILOCK_OUT&t;&t;0x01
DECL|macro|TCIC_ILOCK_SENSE
mdefine_line|#define TCIC_ILOCK_SENSE&t;0x02
DECL|macro|TCIC_ILOCK_CRESET
mdefine_line|#define TCIC_ILOCK_CRESET&t;0x04
DECL|macro|TCIC_ILOCK_CRESENA
mdefine_line|#define TCIC_ILOCK_CRESENA&t;0x08
DECL|macro|TCIC_ILOCK_CWAIT
mdefine_line|#define TCIC_ILOCK_CWAIT&t;0x10
DECL|macro|TCIC_ILOCK_CWAITSNS
mdefine_line|#define TCIC_ILOCK_CWAITSNS&t;0x20
DECL|macro|TCIC_ILOCK_HOLD_MASK
mdefine_line|#define TCIC_ILOCK_HOLD_MASK&t;0xc0
DECL|macro|TCIC_ILOCK_HOLD_CCLK
mdefine_line|#define TCIC_ILOCK_HOLD_CCLK&t;0xc0
DECL|macro|TCIC_ILOCKTEST_ID_SH
mdefine_line|#define TCIC_ILOCKTEST_ID_SH&t;8
DECL|macro|TCIC_ILOCKTEST_ID_MASK
mdefine_line|#define TCIC_ILOCKTEST_ID_MASK&t;0x7f00
DECL|macro|TCIC_ILOCKTEST_MCIC_1
mdefine_line|#define TCIC_ILOCKTEST_MCIC_1&t;0x8000
DECL|macro|TCIC_ID_DB86082
mdefine_line|#define TCIC_ID_DB86082&t;&t;0x02
DECL|macro|TCIC_ID_DB86082A
mdefine_line|#define TCIC_ID_DB86082A&t;0x03
DECL|macro|TCIC_ID_DB86084
mdefine_line|#define TCIC_ID_DB86084&t;&t;0x04
DECL|macro|TCIC_ID_DB86084A
mdefine_line|#define TCIC_ID_DB86084A&t;0x08
DECL|macro|TCIC_ID_DB86072
mdefine_line|#define TCIC_ID_DB86072&t;&t;0x15
DECL|macro|TCIC_ID_DB86184
mdefine_line|#define TCIC_ID_DB86184&t;&t;0x14
DECL|macro|TCIC_ID_DB86082B
mdefine_line|#define TCIC_ID_DB86082B&t;0x17
DECL|macro|TCIC_TEST_DIAG
mdefine_line|#define TCIC_TEST_DIAG&t;&t;0x8000
multiline_comment|/*&n; * Indirectly addressed registers&n; */
DECL|macro|TCIC_SCF1
mdefine_line|#define TCIC_SCF1(sock)&t;((sock)&lt;&lt;3)
DECL|macro|TCIC_SCF2
mdefine_line|#define TCIC_SCF2(sock) (((sock)&lt;&lt;3)+2)
multiline_comment|/* Flags for SCF1 */
DECL|macro|TCIC_SCF1_IRQ_MASK
mdefine_line|#define TCIC_SCF1_IRQ_MASK&t;0x000f
DECL|macro|TCIC_SCF1_IRQ_OFF
mdefine_line|#define TCIC_SCF1_IRQ_OFF&t;0x0000
DECL|macro|TCIC_SCF1_IRQOC
mdefine_line|#define TCIC_SCF1_IRQOC&t;&t;0x0010
DECL|macro|TCIC_SCF1_PCVT
mdefine_line|#define TCIC_SCF1_PCVT&t;&t;0x0020
DECL|macro|TCIC_SCF1_IRDY
mdefine_line|#define TCIC_SCF1_IRDY&t;&t;0x0040
DECL|macro|TCIC_SCF1_ATA
mdefine_line|#define TCIC_SCF1_ATA&t;&t;0x0080
DECL|macro|TCIC_SCF1_DMA_SHIFT
mdefine_line|#define TCIC_SCF1_DMA_SHIFT&t;8
DECL|macro|TCIC_SCF1_DMA_MASK
mdefine_line|#define TCIC_SCF1_DMA_MASK&t;0x0700
DECL|macro|TCIC_SCF1_DMA_OFF
mdefine_line|#define TCIC_SCF1_DMA_OFF&t;0
DECL|macro|TCIC_SCF1_DREQ2
mdefine_line|#define TCIC_SCF1_DREQ2&t;&t;2
DECL|macro|TCIC_SCF1_IOSTS
mdefine_line|#define TCIC_SCF1_IOSTS&t;&t;0x0800
DECL|macro|TCIC_SCF1_SPKR
mdefine_line|#define TCIC_SCF1_SPKR&t;&t;0x1000
DECL|macro|TCIC_SCF1_FINPACK
mdefine_line|#define TCIC_SCF1_FINPACK&t;0x2000
DECL|macro|TCIC_SCF1_DELWR
mdefine_line|#define TCIC_SCF1_DELWR&t;&t;0x4000
DECL|macro|TCIC_SCF1_HD7IDE
mdefine_line|#define TCIC_SCF1_HD7IDE&t;0x8000
multiline_comment|/* Flags for SCF2 */
DECL|macro|TCIC_SCF2_RI
mdefine_line|#define TCIC_SCF2_RI&t;&t;0x0001
DECL|macro|TCIC_SCF2_IDBR
mdefine_line|#define TCIC_SCF2_IDBR&t;&t;0x0002
DECL|macro|TCIC_SCF2_MDBR
mdefine_line|#define TCIC_SCF2_MDBR&t;&t;0x0004
DECL|macro|TCIC_SCF2_MLBAT1
mdefine_line|#define TCIC_SCF2_MLBAT1&t;0x0008
DECL|macro|TCIC_SCF2_MLBAT2
mdefine_line|#define TCIC_SCF2_MLBAT2&t;0x0010
DECL|macro|TCIC_SCF2_MRDY
mdefine_line|#define TCIC_SCF2_MRDY&t;&t;0x0020
DECL|macro|TCIC_SCF2_MWP
mdefine_line|#define TCIC_SCF2_MWP&t;&t;0x0040
DECL|macro|TCIC_SCF2_MCD
mdefine_line|#define TCIC_SCF2_MCD&t;&t;0x0080
DECL|macro|TCIC_SCF2_MALL
mdefine_line|#define TCIC_SCF2_MALL&t;&t;0x00f8
multiline_comment|/* Indirect addresses for memory window registers */
DECL|macro|TCIC_MWIN
mdefine_line|#define TCIC_MWIN(sock,map)&t;(0x100+(((map)+((sock)&lt;&lt;2))&lt;&lt;3))
DECL|macro|TCIC_MBASE_X
mdefine_line|#define TCIC_MBASE_X&t;&t;2
DECL|macro|TCIC_MMAP_X
mdefine_line|#define TCIC_MMAP_X&t;&t;4
DECL|macro|TCIC_MCTL_X
mdefine_line|#define TCIC_MCTL_X&t;&t;6
DECL|macro|TCIC_MBASE_4K_BIT
mdefine_line|#define TCIC_MBASE_4K_BIT&t;0x4000
DECL|macro|TCIC_MBASE_HA_SHFT
mdefine_line|#define TCIC_MBASE_HA_SHFT&t;12
DECL|macro|TCIC_MBASE_HA_MASK
mdefine_line|#define TCIC_MBASE_HA_MASK&t;0x0fff
DECL|macro|TCIC_MMAP_REG
mdefine_line|#define TCIC_MMAP_REG&t;&t;0x8000
DECL|macro|TCIC_MMAP_CA_SHFT
mdefine_line|#define TCIC_MMAP_CA_SHFT&t;12
DECL|macro|TCIC_MMAP_CA_MASK
mdefine_line|#define TCIC_MMAP_CA_MASK&t;0x3fff
DECL|macro|TCIC_MCTL_WSCNT_MASK
mdefine_line|#define TCIC_MCTL_WSCNT_MASK&t;0x001f
DECL|macro|TCIC_MCTL_WCLK
mdefine_line|#define TCIC_MCTL_WCLK&t;&t;0x0020
DECL|macro|TCIC_MCTL_WCLK_CCLK
mdefine_line|#define TCIC_MCTL_WCLK_CCLK&t;0x0000
DECL|macro|TCIC_MCTL_WCLK_BCLK
mdefine_line|#define TCIC_MCTL_WCLK_BCLK&t;0x0020
DECL|macro|TCIC_MCTL_QUIET
mdefine_line|#define TCIC_MCTL_QUIET&t;&t;0x0040
DECL|macro|TCIC_MCTL_WP
mdefine_line|#define TCIC_MCTL_WP&t;&t;0x0080
DECL|macro|TCIC_MCTL_ACC
mdefine_line|#define TCIC_MCTL_ACC&t;&t;0x0100
DECL|macro|TCIC_MCTL_KE
mdefine_line|#define TCIC_MCTL_KE&t;&t;0x0200
DECL|macro|TCIC_MCTL_EDC
mdefine_line|#define TCIC_MCTL_EDC&t;&t;0x0400
DECL|macro|TCIC_MCTL_B8
mdefine_line|#define TCIC_MCTL_B8&t;&t;0x0800
DECL|macro|TCIC_MCTL_SS_SHFT
mdefine_line|#define TCIC_MCTL_SS_SHFT&t;TCIC_SS_SHFT
DECL|macro|TCIC_MCTL_SS_MASK
mdefine_line|#define TCIC_MCTL_SS_MASK&t;TCIC_SS_MASK
DECL|macro|TCIC_MCTL_ENA
mdefine_line|#define TCIC_MCTL_ENA&t;&t;0x8000
multiline_comment|/* Indirect addresses for I/O window registers */
DECL|macro|TCIC_IWIN
mdefine_line|#define TCIC_IWIN(sock,map)&t;(0x200+(((map)+((sock)&lt;&lt;1))&lt;&lt;2))
DECL|macro|TCIC_IBASE_X
mdefine_line|#define TCIC_IBASE_X&t;&t;0
DECL|macro|TCIC_ICTL_X
mdefine_line|#define TCIC_ICTL_X&t;&t;2
DECL|macro|TCIC_ICTL_WSCNT_MASK
mdefine_line|#define TCIC_ICTL_WSCNT_MASK&t;TCIC_MCTL_WSCNT_MASK
DECL|macro|TCIC_ICTL_QUIET
mdefine_line|#define TCIC_ICTL_QUIET&t;&t;TCIC_MCTL_QUIET
DECL|macro|TCIC_ICTL_1K
mdefine_line|#define TCIC_ICTL_1K&t;&t;0x0080
DECL|macro|TCIC_ICTL_PASS16
mdefine_line|#define TCIC_ICTL_PASS16&t;0x0100
DECL|macro|TCIC_ICTL_ACC
mdefine_line|#define TCIC_ICTL_ACC&t;&t;TCIC_MCTL_ACC
DECL|macro|TCIC_ICTL_TINY
mdefine_line|#define TCIC_ICTL_TINY&t;&t;0x0200
DECL|macro|TCIC_ICTL_B16
mdefine_line|#define TCIC_ICTL_B16&t;&t;0x0400
DECL|macro|TCIC_ICTL_B8
mdefine_line|#define TCIC_ICTL_B8&t;&t;TCIC_MCTL_B8
DECL|macro|TCIC_ICTL_BW_MASK
mdefine_line|#define TCIC_ICTL_BW_MASK&t;(TCIC_ICTL_B16|TCIC_ICTL_B8)
DECL|macro|TCIC_ICTL_BW_DYN
mdefine_line|#define TCIC_ICTL_BW_DYN&t;0
DECL|macro|TCIC_ICTL_BW_8
mdefine_line|#define TCIC_ICTL_BW_8&t;&t;TCIC_ICTL_B8
DECL|macro|TCIC_ICTL_BW_16
mdefine_line|#define TCIC_ICTL_BW_16&t;&t;TCIC_ICTL_B16
DECL|macro|TCIC_ICTL_BW_ATA
mdefine_line|#define TCIC_ICTL_BW_ATA&t;(TCIC_ICTL_B16|TCIC_ICTL_B8)
DECL|macro|TCIC_ICTL_SS_SHFT
mdefine_line|#define TCIC_ICTL_SS_SHFT&t;TCIC_SS_SHFT
DECL|macro|TCIC_ICTL_SS_MASK
mdefine_line|#define TCIC_ICTL_SS_MASK&t;TCIC_SS_MASK
DECL|macro|TCIC_ICTL_ENA
mdefine_line|#define TCIC_ICTL_ENA&t;&t;TCIC_MCTL_ENA
macro_line|#endif /* _LINUX_TCIC_H */
eof
