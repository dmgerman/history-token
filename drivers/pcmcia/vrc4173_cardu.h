multiline_comment|/*&n; * FILE NAME&n; *&t;drivers/pcmcia/vrc4173_cardu.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for NEC VRC4173 CARDU.&n; *&n; * Copyright 2002 Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _VRC4173_CARDU_H
DECL|macro|_VRC4173_CARDU_H
mdefine_line|#define _VRC4173_CARDU_H
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
DECL|macro|CARDU_MAX_SOCKETS
mdefine_line|#define CARDU_MAX_SOCKETS&t;2
DECL|macro|CARDU1
mdefine_line|#define CARDU1&t;&t;&t;0
DECL|macro|CARDU2
mdefine_line|#define CARDU2&t;&t;&t;1
multiline_comment|/*&n; * PCI Configuration Registers&n; */
DECL|macro|BRGCNT
mdefine_line|#define BRGCNT&t;&t;&t;0x3e
DECL|macro|POST_WR_EN
mdefine_line|#define POST_WR_EN&t;&t;0x0400
DECL|macro|MEM1_PREF_EN
mdefine_line|#define MEM1_PREF_EN&t;&t;0x0200
DECL|macro|MEM0_PREF_EN
mdefine_line|#define MEM0_PREF_EN&t;&t;0x0100
DECL|macro|IREQ_INT
mdefine_line|#define IREQ_INT&t;&t;0x0080
DECL|macro|CARD_RST
mdefine_line|#define CARD_RST&t;&t;0x0040
DECL|macro|MABORT_MODE
mdefine_line|#define MABORT_MODE&t;&t;0x0020
DECL|macro|VGA_EN
mdefine_line|#define VGA_EN&t;&t;&t;0x0008
DECL|macro|ISA_EN
mdefine_line|#define ISA_EN&t;&t;&t;0x0004
DECL|macro|SERR_EN
mdefine_line|#define SERR_EN&t;&t;0x0002
DECL|macro|PERR_EN
mdefine_line|#define PERR_EN&t;&t;0x0001
DECL|macro|SYSCNT
mdefine_line|#define SYSCNT&t;&t;&t;0x80
DECL|macro|BAD_VCC_REQ_DISB
mdefine_line|#define BAD_VCC_REQ_DISB&t;0x00200000
DECL|macro|PCPCI_EN
mdefine_line|#define PCPCI_EN&t;&t;0x00080000
DECL|macro|CH_ASSIGN_MASK
mdefine_line|#define CH_ASSIGN_MASK&t;&t;0x00070000
DECL|macro|CH_ASSIGN_NODMA
mdefine_line|#define CH_ASSIGN_NODMA&t;0x00040000
DECL|macro|SUB_ID_WR_EN
mdefine_line|#define SUB_ID_WR_EN&t;&t;0x00000008
DECL|macro|ASYN_INT_MODE
mdefine_line|#define ASYN_INT_MODE&t;&t;0x00000004
DECL|macro|PCI_CLK_RIN
mdefine_line|#define PCI_CLK_RIN&t;&t;0x00000002
DECL|macro|DEVCNT
mdefine_line|#define DEVCNT&t;&t;&t;0x91
DECL|macro|ZOOM_VIDEO_EN
mdefine_line|#define ZOOM_VIDEO_EN&t;&t;0x40
DECL|macro|SR_PCI_INT_SEL_MASK
mdefine_line|#define SR_PCI_INT_SEL_MASK&t;0x18
DECL|macro|SR_PCI_INT_SEL_NONE
mdefine_line|#define SR_PCI_INT_SEL_NONE&t;0x00
DECL|macro|PCI_INT_MODE
mdefine_line|#define PCI_INT_MODE&t;&t;0x04
DECL|macro|IRQ_MODE
mdefine_line|#define IRQ_MODE&t;&t;0x02
DECL|macro|IFG
mdefine_line|#define IFG&t;&t;&t;0x01
DECL|macro|CHIPCNT
mdefine_line|#define CHIPCNT&t;&t;&t;0x9c
DECL|macro|S_PREF_DISB
mdefine_line|#define S_PREF_DISB&t;&t;0x10
DECL|macro|SERRDIS
mdefine_line|#define SERRDIS&t;&t;&t;0x9f
DECL|macro|SERR_DIS_MAB
mdefine_line|#define SERR_DIS_MAB&t;&t;0x10
DECL|macro|SERR_DIS_TAB
mdefine_line|#define SERR_DIS_TAB&t;&t;0x08
DECL|macro|SERR_DIS_DT_PERR
mdefine_line|#define SERR_DIS_DT_PERR&t;0x04
multiline_comment|/*&n; * ExCA Registers&n; */
DECL|macro|EXCA_REGS_BASE
mdefine_line|#define EXCA_REGS_BASE&t;&t;0x800
DECL|macro|EXCA_REGS_SIZE
mdefine_line|#define EXCA_REGS_SIZE&t;&t;0x800
DECL|macro|ID_REV
mdefine_line|#define ID_REV&t;&t;&t;0x000
DECL|macro|IF_TYPE_16BIT
mdefine_line|#define IF_TYPE_16BIT&t;&t;0x80
DECL|macro|IF_STATUS
mdefine_line|#define IF_STATUS&t;&t;0x001
DECL|macro|CARD_PWR
mdefine_line|#define CARD_PWR&t;&t;0x40
DECL|macro|READY
mdefine_line|#define READY&t;&t;&t;0x20
DECL|macro|CARD_WP
mdefine_line|#define CARD_WP&t;&t;0x10
DECL|macro|CARD_DETECT2
mdefine_line|#define CARD_DETECT2&t;&t;0x08
DECL|macro|CARD_DETECT1
mdefine_line|#define CARD_DETECT1&t;&t;0x04
DECL|macro|BV_DETECT_MASK
mdefine_line|#define BV_DETECT_MASK&t;&t;0x03
DECL|macro|BV_DETECT_GOOD
mdefine_line|#define BV_DETECT_GOOD&t;&t;0x03&t;/* Memory card */
DECL|macro|BV_DETECT_WARN
mdefine_line|#define BV_DETECT_WARN&t;&t;0x02
DECL|macro|BV_DETECT_BAD1
mdefine_line|#define BV_DETECT_BAD1&t;&t;0x01
DECL|macro|BV_DETECT_BAD0
mdefine_line|#define BV_DETECT_BAD0&t;&t;0x00
DECL|macro|STSCHG
mdefine_line|#define STSCHG&t;&t;&t;0x02&t;/* I/O card */
DECL|macro|SPKR
mdefine_line|#define SPKR&t;&t;&t;0x01
DECL|macro|PWR_CNT
mdefine_line|#define PWR_CNT&t;&t;&t;0x002
DECL|macro|CARD_OUT_EN
mdefine_line|#define CARD_OUT_EN&t;&t;0x80
DECL|macro|VCC_MASK
mdefine_line|#define VCC_MASK&t;&t;0x18
DECL|macro|VCC_3V
mdefine_line|#define VCC_3V&t;&t;&t;0x18
DECL|macro|VCC_5V
mdefine_line|#define VCC_5V&t;&t;&t;0x10
DECL|macro|VCC_0V
mdefine_line|#define VCC_0V&t;&t;&t;0x00
DECL|macro|VPP_MASK
mdefine_line|#define VPP_MASK&t;&t;0x03
DECL|macro|VPP_12V
mdefine_line|#define VPP_12V&t;&t;0x02
DECL|macro|VPP_VCC
mdefine_line|#define VPP_VCC&t;&t;0x01
DECL|macro|VPP_0V
mdefine_line|#define VPP_0V&t;&t;&t;0x00
DECL|macro|INT_GEN_CNT
mdefine_line|#define INT_GEN_CNT&t;&t;0x003
DECL|macro|CARD_REST0
mdefine_line|#define CARD_REST0&t;&t;0x40
DECL|macro|CARD_TYPE_MASK
mdefine_line|#define CARD_TYPE_MASK&t;&t;0x20
DECL|macro|CARD_TYPE_IO
mdefine_line|#define CARD_TYPE_IO&t;&t;0x20
DECL|macro|CARD_TYPE_MEM
mdefine_line|#define CARD_TYPE_MEM&t;&t;0x00
DECL|macro|CARD_SC
mdefine_line|#define CARD_SC&t;&t;&t;0x004
DECL|macro|CARD_DT_CHG
mdefine_line|#define CARD_DT_CHG&t;&t;0x08
DECL|macro|RDY_CHG
mdefine_line|#define RDY_CHG&t;&t;0x04
DECL|macro|BAT_WAR_CHG
mdefine_line|#define BAT_WAR_CHG&t;&t;0x02
DECL|macro|BAT_DEAD_ST_CHG
mdefine_line|#define BAT_DEAD_ST_CHG&t;0x01
DECL|macro|CARD_SCI
mdefine_line|#define CARD_SCI&t;&t;0x005
DECL|macro|CARD_DT_EN
mdefine_line|#define CARD_DT_EN&t;&t;0x08
DECL|macro|RDY_EN
mdefine_line|#define RDY_EN&t;&t;&t;0x04
DECL|macro|BAT_WAR_EN
mdefine_line|#define BAT_WAR_EN&t;&t;0x02
DECL|macro|BAT_DEAD_EN
mdefine_line|#define BAT_DEAD_EN&t;&t;0x01
DECL|macro|ADR_WIN_EN
mdefine_line|#define ADR_WIN_EN&t;&t;0x006
DECL|macro|IO_WIN_EN
mdefine_line|#define IO_WIN_EN(x)&t;&t;(0x40 &lt;&lt; (x))
DECL|macro|MEM_WIN_EN
mdefine_line|#define MEM_WIN_EN(x)&t;&t;(0x01 &lt;&lt; (x))
DECL|macro|IO_WIN_CNT
mdefine_line|#define IO_WIN_CNT&t;&t;0x007
DECL|macro|IO_WIN_CNT_MASK
mdefine_line|#define IO_WIN_CNT_MASK(x)&t;(0x03 &lt;&lt; ((x) &lt;&lt; 2))
DECL|macro|IO_WIN_DATA_AUTOSZ
mdefine_line|#define IO_WIN_DATA_AUTOSZ(x)&t;(0x02 &lt;&lt; ((x) &lt;&lt; 2))
DECL|macro|IO_WIN_DATA_16BIT
mdefine_line|#define IO_WIN_DATA_16BIT(x)&t;(0x01 &lt;&lt; ((x) &lt;&lt; 2))
DECL|macro|IO_WIN_SA
mdefine_line|#define IO_WIN_SA(x)&t;&t;(0x008 + ((x) &lt;&lt; 2))
DECL|macro|IO_WIN_EA
mdefine_line|#define IO_WIN_EA(x)&t;&t;(0x00a + ((x) &lt;&lt; 2))
DECL|macro|MEM_WIN_SA
mdefine_line|#define MEM_WIN_SA(x)&t;&t;(0x010 + ((x) &lt;&lt; 3))
DECL|macro|MEM_WIN_DSIZE
mdefine_line|#define MEM_WIN_DSIZE&t;&t;0x8000
DECL|macro|MEM_WIN_EA
mdefine_line|#define MEM_WIN_EA(x)&t;&t;(0x012 + ((x) &lt;&lt; 3))
DECL|macro|MEM_WIN_OA
mdefine_line|#define MEM_WIN_OA(x)&t;&t;(0x014 + ((x) &lt;&lt; 3))
DECL|macro|MEM_WIN_WP
mdefine_line|#define MEM_WIN_WP&t;&t;0x8000
DECL|macro|MEM_WIN_REGSET
mdefine_line|#define MEM_WIN_REGSET&t;&t;0x4000
DECL|macro|GEN_CNT
mdefine_line|#define GEN_CNT&t;&t;&t;0x016
DECL|macro|VS2_STATUS
mdefine_line|#define VS2_STATUS&t;&t;0x80
DECL|macro|VS1_STATUS
mdefine_line|#define VS1_STATUS&t;&t;0x40
DECL|macro|EXCA_REG_RST_EN
mdefine_line|#define EXCA_REG_RST_EN&t;0x02
DECL|macro|GLO_CNT
mdefine_line|#define GLO_CNT&t;&t;&t;0x01e
DECL|macro|FUN_INT_LEV
mdefine_line|#define FUN_INT_LEV&t;&t;0x08
DECL|macro|INT_WB_CLR
mdefine_line|#define INT_WB_CLR&t;&t;0x04
DECL|macro|CSC_INT_LEV
mdefine_line|#define CSC_INT_LEV&t;&t;0x02
DECL|macro|IO_WIN_OAL
mdefine_line|#define IO_WIN_OAL(x)&t;&t;(0x036 + ((x) &lt;&lt; 1))
DECL|macro|IO_WIN_OAH
mdefine_line|#define IO_WIN_OAH(x)&t;&t;(0x037 + ((x) &lt;&lt; 1))
DECL|macro|MEM_WIN_SAU
mdefine_line|#define MEM_WIN_SAU(x)&t;&t;(0x040 + (x))
DECL|macro|IO_SETUP_TIM
mdefine_line|#define IO_SETUP_TIM&t;&t;0x080
DECL|macro|IO_CMD_TIM
mdefine_line|#define IO_CMD_TIM&t;&t;0x081
DECL|macro|IO_HOLD_TIM
mdefine_line|#define IO_HOLD_TIM&t;&t;0x082
DECL|macro|MEM_SETUP_TIM
mdefine_line|#define MEM_SETUP_TIM(x)&t;(0x084 + ((x) &lt;&lt; 2))
DECL|macro|MEM_CMD_TIM
mdefine_line|#define MEM_CMD_TIM(x)&t;&t;(0x085 + ((x) &lt;&lt; 2))
DECL|macro|MEM_HOLD_TIM
mdefine_line|#define MEM_HOLD_TIM(x)&t;&t;(0x086 + ((x) &lt;&lt; 2))
DECL|macro|TIM_CLOCKS
mdefine_line|#define TIM_CLOCKS(x)&t;&t;((x) - 1)
DECL|macro|MEM_TIM_SEL1
mdefine_line|#define MEM_TIM_SEL1&t;&t;0x08c
DECL|macro|MEM_TIM_SEL2
mdefine_line|#define MEM_TIM_SEL2&t;&t;0x08d
DECL|macro|MEM_WIN_TIMSEL1
mdefine_line|#define MEM_WIN_TIMSEL1(x)&t;(0x03 &lt;&lt; (((x) &amp; 3) &lt;&lt; 1))
DECL|macro|MEM_WIN_PWEN
mdefine_line|#define MEM_WIN_PWEN&t;&t;0x091
DECL|macro|POSTWEN
mdefine_line|#define POSTWEN&t;&t;0x01
multiline_comment|/*&n; * CardBus Socket Registers&n; */
DECL|macro|CARDBUS_SOCKET_REGS_BASE
mdefine_line|#define CARDBUS_SOCKET_REGS_BASE&t;0x000
DECL|macro|CARDBUS_SOCKET_REGS_SIZE
mdefine_line|#define CARDBUS_SOCKET_REGS_SIZE&t;0x800
DECL|macro|SKT_EV
mdefine_line|#define SKT_EV&t;&t;&t;0x000
DECL|macro|POW_CYC_EV
mdefine_line|#define POW_CYC_EV&t;&t;0x00000008
DECL|macro|CCD2_EV
mdefine_line|#define CCD2_EV&t;&t;0x00000004
DECL|macro|CCD1_EV
mdefine_line|#define CCD1_EV&t;&t;0x00000002
DECL|macro|CSTSCHG_EV
mdefine_line|#define CSTSCHG_EV&t;&t;0x00000001
DECL|macro|SKT_MASK
mdefine_line|#define SKT_MASK&t;&t;0x004
DECL|macro|POW_CYC_MASK
mdefine_line|#define POW_CYC_MASK&t;&t;0x00000008
DECL|macro|CCD_MASK
mdefine_line|#define CCD_MASK&t;&t;0x00000006
DECL|macro|CSC_MASK
mdefine_line|#define CSC_MASK&t;&t;0x00000001
DECL|macro|SKT_PRE_STATE
mdefine_line|#define SKT_PRE_STATE&t;&t;0x008
DECL|macro|SKT_FORCE_EV
mdefine_line|#define SKT_FORCE_EV&t;&t;0x00c
DECL|macro|VOL_3V_SKT
mdefine_line|#define VOL_3V_SKT&t;&t;0x20000000
DECL|macro|VOL_5V_SKT
mdefine_line|#define VOL_5V_SKT&t;&t;0x10000000
DECL|macro|CVS_TEST
mdefine_line|#define CVS_TEST&t;&t;0x00004000
DECL|macro|VOL_YV_CARD_DT
mdefine_line|#define VOL_YV_CARD_DT&t;&t;0x00002000
DECL|macro|VOL_XV_CARD_DT
mdefine_line|#define VOL_XV_CARD_DT&t;&t;0x00001000
DECL|macro|VOL_3V_CARD_DT
mdefine_line|#define VOL_3V_CARD_DT&t;&t;0x00000800
DECL|macro|VOL_5V_CARD_DT
mdefine_line|#define VOL_5V_CARD_DT&t;&t;0x00000400
DECL|macro|BAD_VCC_REQ
mdefine_line|#define BAD_VCC_REQ&t;&t;0x00000200
DECL|macro|DATA_LOST
mdefine_line|#define DATA_LOST&t;&t;0x00000100
DECL|macro|NOT_A_CARD
mdefine_line|#define NOT_A_CARD&t;&t;0x00000080
DECL|macro|CREADY
mdefine_line|#define CREADY&t;&t;&t;0x00000040
DECL|macro|CB_CARD_DT
mdefine_line|#define CB_CARD_DT&t;&t;0x00000020
DECL|macro|R2_CARD_DT
mdefine_line|#define R2_CARD_DT&t;&t;0x00000010
DECL|macro|POW_UP
mdefine_line|#define POW_UP&t;&t;&t;0x00000008
DECL|macro|CCD20
mdefine_line|#define CCD20&t;&t;&t;0x00000004
DECL|macro|CCD10
mdefine_line|#define CCD10&t;&t;&t;0x00000002
DECL|macro|CSTSCHG
mdefine_line|#define CSTSCHG&t;&t;0x00000001
DECL|macro|SKT_CNT
mdefine_line|#define SKT_CNT&t;&t;&t;0x010
DECL|macro|STP_CLK_EN
mdefine_line|#define STP_CLK_EN&t;&t;0x00000080
DECL|macro|VCC_CNT_MASK
mdefine_line|#define VCC_CNT_MASK&t;&t;0x00000070
DECL|macro|VCC_CNT_3V
mdefine_line|#define VCC_CNT_3V&t;&t;0x00000030
DECL|macro|VCC_CNT_5V
mdefine_line|#define VCC_CNT_5V&t;&t;0x00000020
DECL|macro|VCC_CNT_0V
mdefine_line|#define VCC_CNT_0V&t;&t;0x00000000
DECL|macro|VPP_CNT_MASK
mdefine_line|#define VPP_CNT_MASK&t;&t;0x00000007
DECL|macro|VPP_CNT_3V
mdefine_line|#define VPP_CNT_3V&t;&t;0x00000003
DECL|macro|VPP_CNT_5V
mdefine_line|#define VPP_CNT_5V&t;&t;0x00000002
DECL|macro|VPP_CNT_12V
mdefine_line|#define VPP_CNT_12V&t;&t;0x00000001
DECL|macro|VPP_CNT_0V
mdefine_line|#define VPP_CNT_0V&t;&t;0x00000000
DECL|struct|vrc4173_socket
r_typedef
r_struct
id|vrc4173_socket
(brace
DECL|member|noprobe
r_int
id|noprobe
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|cap
id|socket_cap_t
id|cap
suffix:semicolon
DECL|member|event_lock
id|spinlock_t
id|event_lock
suffix:semicolon
DECL|member|events
r_uint16
id|events
suffix:semicolon
DECL|member|pcmcia_socket
r_struct
id|socket_info_t
op_star
id|pcmcia_socket
suffix:semicolon
DECL|member|tq_work
r_struct
id|work_struct
id|tq_work
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
DECL|typedef|vrc4173_socket_t
)brace
id|vrc4173_socket_t
suffix:semicolon
macro_line|#endif /* _VRC4173_CARDU_H */
eof
