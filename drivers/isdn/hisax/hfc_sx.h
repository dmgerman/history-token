multiline_comment|/* $Id: hfc_sx.h,v 1.2.6.1 2001/09/23 22:24:48 kai Exp $&n; *&n; * specific defines for CCD&squot;s HFC 2BDS0 S+,SP chips&n; *&n; * Author       Werner Cornelius&n; *              based on existing driver for CCD HFC PCI cards&n; * Copyright    by Werner Cornelius  &lt;werner@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
multiline_comment|/*********************************************/
multiline_comment|/* thresholds for transparent B-channel mode */
multiline_comment|/* change mask and threshold simultaneously  */
multiline_comment|/*********************************************/
DECL|macro|HFCSX_BTRANS_THRESHOLD
mdefine_line|#define HFCSX_BTRANS_THRESHOLD 128
DECL|macro|HFCSX_BTRANS_THRESMASK
mdefine_line|#define HFCSX_BTRANS_THRESMASK 0x00
multiline_comment|/* GCI/IOM bus monitor registers */
DECL|macro|HFCSX_C_I
mdefine_line|#define HFCSX_C_I       0x02
DECL|macro|HFCSX_TRxR
mdefine_line|#define HFCSX_TRxR      0x03
DECL|macro|HFCSX_MON1_D
mdefine_line|#define HFCSX_MON1_D    0x0A
DECL|macro|HFCSX_MON2_D
mdefine_line|#define HFCSX_MON2_D    0x0B
multiline_comment|/* GCI/IOM bus timeslot registers */
DECL|macro|HFCSX_B1_SSL
mdefine_line|#define HFCSX_B1_SSL    0x20
DECL|macro|HFCSX_B2_SSL
mdefine_line|#define HFCSX_B2_SSL    0x21
DECL|macro|HFCSX_AUX1_SSL
mdefine_line|#define HFCSX_AUX1_SSL  0x22
DECL|macro|HFCSX_AUX2_SSL
mdefine_line|#define HFCSX_AUX2_SSL  0x23
DECL|macro|HFCSX_B1_RSL
mdefine_line|#define HFCSX_B1_RSL    0x24
DECL|macro|HFCSX_B2_RSL
mdefine_line|#define HFCSX_B2_RSL    0x25
DECL|macro|HFCSX_AUX1_RSL
mdefine_line|#define HFCSX_AUX1_RSL  0x26
DECL|macro|HFCSX_AUX2_RSL
mdefine_line|#define HFCSX_AUX2_RSL  0x27
multiline_comment|/* GCI/IOM bus data registers */
DECL|macro|HFCSX_B1_D
mdefine_line|#define HFCSX_B1_D      0x28
DECL|macro|HFCSX_B2_D
mdefine_line|#define HFCSX_B2_D      0x29
DECL|macro|HFCSX_AUX1_D
mdefine_line|#define HFCSX_AUX1_D    0x2A
DECL|macro|HFCSX_AUX2_D
mdefine_line|#define HFCSX_AUX2_D    0x2B
multiline_comment|/* GCI/IOM bus configuration registers */
DECL|macro|HFCSX_MST_EMOD
mdefine_line|#define HFCSX_MST_EMOD  0x2D
DECL|macro|HFCSX_MST_MODE
mdefine_line|#define HFCSX_MST_MODE&t;0x2E
DECL|macro|HFCSX_CONNECT
mdefine_line|#define HFCSX_CONNECT &t;0x2F
multiline_comment|/* Interrupt and status registers */
DECL|macro|HFCSX_TRM
mdefine_line|#define HFCSX_TRM       0x12
DECL|macro|HFCSX_B_MODE
mdefine_line|#define HFCSX_B_MODE    0x13
DECL|macro|HFCSX_CHIP_ID
mdefine_line|#define HFCSX_CHIP_ID   0x16
DECL|macro|HFCSX_CIRM
mdefine_line|#define HFCSX_CIRM  &t;0x18
DECL|macro|HFCSX_CTMT
mdefine_line|#define HFCSX_CTMT&t;0x19
DECL|macro|HFCSX_INT_M1
mdefine_line|#define HFCSX_INT_M1  &t;0x1A
DECL|macro|HFCSX_INT_M2
mdefine_line|#define HFCSX_INT_M2  &t;0x1B
DECL|macro|HFCSX_INT_S1
mdefine_line|#define HFCSX_INT_S1  &t;0x1E
DECL|macro|HFCSX_INT_S2
mdefine_line|#define HFCSX_INT_S2  &t;0x1F
DECL|macro|HFCSX_STATUS
mdefine_line|#define HFCSX_STATUS  &t;0x1C
multiline_comment|/* S/T section registers */
DECL|macro|HFCSX_STATES
mdefine_line|#define HFCSX_STATES  &t;0x30
DECL|macro|HFCSX_SCTRL
mdefine_line|#define HFCSX_SCTRL  &t;0x31
DECL|macro|HFCSX_SCTRL_E
mdefine_line|#define HFCSX_SCTRL_E   0x32
DECL|macro|HFCSX_SCTRL_R
mdefine_line|#define HFCSX_SCTRL_R   0x33
DECL|macro|HFCSX_SQ
mdefine_line|#define HFCSX_SQ  &t;0x34
DECL|macro|HFCSX_CLKDEL
mdefine_line|#define HFCSX_CLKDEL  &t;0x37
DECL|macro|HFCSX_B1_REC
mdefine_line|#define HFCSX_B1_REC    0x3C
DECL|macro|HFCSX_B1_SEND
mdefine_line|#define HFCSX_B1_SEND   0x3C
DECL|macro|HFCSX_B2_REC
mdefine_line|#define HFCSX_B2_REC    0x3D
DECL|macro|HFCSX_B2_SEND
mdefine_line|#define HFCSX_B2_SEND   0x3D
DECL|macro|HFCSX_D_REC
mdefine_line|#define HFCSX_D_REC     0x3E
DECL|macro|HFCSX_D_SEND
mdefine_line|#define HFCSX_D_SEND    0x3E
DECL|macro|HFCSX_E_REC
mdefine_line|#define HFCSX_E_REC     0x3F
multiline_comment|/****************/
multiline_comment|/* FIFO section */
multiline_comment|/****************/
DECL|macro|HFCSX_FIF_SEL
mdefine_line|#define HFCSX_FIF_SEL   0x10
DECL|macro|HFCSX_FIF_Z1L
mdefine_line|#define HFCSX_FIF_Z1L   0x80
DECL|macro|HFCSX_FIF_Z1H
mdefine_line|#define HFCSX_FIF_Z1H   0x84
DECL|macro|HFCSX_FIF_Z2L
mdefine_line|#define HFCSX_FIF_Z2L   0x88
DECL|macro|HFCSX_FIF_Z2H
mdefine_line|#define HFCSX_FIF_Z2H   0x8C
DECL|macro|HFCSX_FIF_INCF1
mdefine_line|#define HFCSX_FIF_INCF1 0xA8
DECL|macro|HFCSX_FIF_DWR
mdefine_line|#define HFCSX_FIF_DWR   0xAC
DECL|macro|HFCSX_FIF_F1
mdefine_line|#define HFCSX_FIF_F1    0xB0
DECL|macro|HFCSX_FIF_F2
mdefine_line|#define HFCSX_FIF_F2    0xB4
DECL|macro|HFCSX_FIF_INCF2
mdefine_line|#define HFCSX_FIF_INCF2 0xB8
DECL|macro|HFCSX_FIF_DRD
mdefine_line|#define HFCSX_FIF_DRD   0xBC
multiline_comment|/* bits in status register (READ) */
DECL|macro|HFCSX_SX_PROC
mdefine_line|#define HFCSX_SX_PROC    0x02
DECL|macro|HFCSX_NBUSY
mdefine_line|#define HFCSX_NBUSY&t; 0x04 
DECL|macro|HFCSX_TIMER_ELAP
mdefine_line|#define HFCSX_TIMER_ELAP 0x10
DECL|macro|HFCSX_STATINT
mdefine_line|#define HFCSX_STATINT&t; 0x20
DECL|macro|HFCSX_FRAMEINT
mdefine_line|#define HFCSX_FRAMEINT&t; 0x40
DECL|macro|HFCSX_ANYINT
mdefine_line|#define HFCSX_ANYINT&t; 0x80
multiline_comment|/* bits in CTMT (Write) */
DECL|macro|HFCSX_CLTIMER
mdefine_line|#define HFCSX_CLTIMER    0x80
DECL|macro|HFCSX_TIM3_125
mdefine_line|#define HFCSX_TIM3_125   0x04
DECL|macro|HFCSX_TIM25
mdefine_line|#define HFCSX_TIM25      0x10
DECL|macro|HFCSX_TIM50
mdefine_line|#define HFCSX_TIM50      0x14
DECL|macro|HFCSX_TIM400
mdefine_line|#define HFCSX_TIM400     0x18
DECL|macro|HFCSX_TIM800
mdefine_line|#define HFCSX_TIM800     0x1C
DECL|macro|HFCSX_AUTO_TIMER
mdefine_line|#define HFCSX_AUTO_TIMER 0x20
DECL|macro|HFCSX_TRANSB2
mdefine_line|#define HFCSX_TRANSB2    0x02
DECL|macro|HFCSX_TRANSB1
mdefine_line|#define HFCSX_TRANSB1    0x01
multiline_comment|/* bits in CIRM (Write) */
DECL|macro|HFCSX_IRQ_SELMSK
mdefine_line|#define HFCSX_IRQ_SELMSK 0x07
DECL|macro|HFCSX_IRQ_SELDIS
mdefine_line|#define HFCSX_IRQ_SELDIS 0x00
DECL|macro|HFCSX_RESET
mdefine_line|#define HFCSX_RESET  &t; 0x08
DECL|macro|HFCSX_FIFO_RESET
mdefine_line|#define HFCSX_FIFO_RESET 0x80
multiline_comment|/* bits in INT_M1 and INT_S1 */
DECL|macro|HFCSX_INTS_B1TRANS
mdefine_line|#define HFCSX_INTS_B1TRANS  0x01
DECL|macro|HFCSX_INTS_B2TRANS
mdefine_line|#define HFCSX_INTS_B2TRANS  0x02
DECL|macro|HFCSX_INTS_DTRANS
mdefine_line|#define HFCSX_INTS_DTRANS   0x04
DECL|macro|HFCSX_INTS_B1REC
mdefine_line|#define HFCSX_INTS_B1REC    0x08
DECL|macro|HFCSX_INTS_B2REC
mdefine_line|#define HFCSX_INTS_B2REC    0x10
DECL|macro|HFCSX_INTS_DREC
mdefine_line|#define HFCSX_INTS_DREC     0x20
DECL|macro|HFCSX_INTS_L1STATE
mdefine_line|#define HFCSX_INTS_L1STATE  0x40
DECL|macro|HFCSX_INTS_TIMER
mdefine_line|#define HFCSX_INTS_TIMER    0x80
multiline_comment|/* bits in INT_M2 */
DECL|macro|HFCSX_PROC_TRANS
mdefine_line|#define HFCSX_PROC_TRANS    0x01
DECL|macro|HFCSX_GCI_I_CHG
mdefine_line|#define HFCSX_GCI_I_CHG     0x02
DECL|macro|HFCSX_GCI_MON_REC
mdefine_line|#define HFCSX_GCI_MON_REC   0x04
DECL|macro|HFCSX_IRQ_ENABLE
mdefine_line|#define HFCSX_IRQ_ENABLE    0x08
multiline_comment|/* bits in STATES */
DECL|macro|HFCSX_STATE_MSK
mdefine_line|#define HFCSX_STATE_MSK     0x0F
DECL|macro|HFCSX_LOAD_STATE
mdefine_line|#define HFCSX_LOAD_STATE    0x10
DECL|macro|HFCSX_ACTIVATE
mdefine_line|#define HFCSX_ACTIVATE&t;    0x20
DECL|macro|HFCSX_DO_ACTION
mdefine_line|#define HFCSX_DO_ACTION     0x40
DECL|macro|HFCSX_NT_G2_G3
mdefine_line|#define HFCSX_NT_G2_G3      0x80
multiline_comment|/* bits in HFCD_MST_MODE */
DECL|macro|HFCSX_MASTER
mdefine_line|#define HFCSX_MASTER&t;    0x01
DECL|macro|HFCSX_SLAVE
mdefine_line|#define HFCSX_SLAVE         0x00
multiline_comment|/* remaining bits are for codecs control */
multiline_comment|/* bits in HFCD_SCTRL */
DECL|macro|SCTRL_B1_ENA
mdefine_line|#define SCTRL_B1_ENA&t;    0x01
DECL|macro|SCTRL_B2_ENA
mdefine_line|#define SCTRL_B2_ENA&t;    0x02
DECL|macro|SCTRL_MODE_TE
mdefine_line|#define SCTRL_MODE_TE       0x00
DECL|macro|SCTRL_MODE_NT
mdefine_line|#define SCTRL_MODE_NT       0x04
DECL|macro|SCTRL_LOW_PRIO
mdefine_line|#define SCTRL_LOW_PRIO&t;    0x08
DECL|macro|SCTRL_SQ_ENA
mdefine_line|#define SCTRL_SQ_ENA&t;    0x10
DECL|macro|SCTRL_TEST
mdefine_line|#define SCTRL_TEST&t;    0x20
DECL|macro|SCTRL_NONE_CAP
mdefine_line|#define SCTRL_NONE_CAP&t;    0x40
DECL|macro|SCTRL_PWR_DOWN
mdefine_line|#define SCTRL_PWR_DOWN&t;    0x80
multiline_comment|/* bits in SCTRL_E  */
DECL|macro|HFCSX_AUTO_AWAKE
mdefine_line|#define HFCSX_AUTO_AWAKE    0x01
DECL|macro|HFCSX_DBIT_1
mdefine_line|#define HFCSX_DBIT_1        0x04
DECL|macro|HFCSX_IGNORE_COL
mdefine_line|#define HFCSX_IGNORE_COL    0x08
DECL|macro|HFCSX_CHG_B1_B2
mdefine_line|#define HFCSX_CHG_B1_B2     0x80
multiline_comment|/**********************************/
multiline_comment|/* definitions for FIFO selection */
multiline_comment|/**********************************/
DECL|macro|HFCSX_SEL_D_RX
mdefine_line|#define HFCSX_SEL_D_RX      5
DECL|macro|HFCSX_SEL_D_TX
mdefine_line|#define HFCSX_SEL_D_TX      4
DECL|macro|HFCSX_SEL_B1_RX
mdefine_line|#define HFCSX_SEL_B1_RX     1
DECL|macro|HFCSX_SEL_B1_TX
mdefine_line|#define HFCSX_SEL_B1_TX     0
DECL|macro|HFCSX_SEL_B2_RX
mdefine_line|#define HFCSX_SEL_B2_RX     3
DECL|macro|HFCSX_SEL_B2_TX
mdefine_line|#define HFCSX_SEL_B2_TX     2
DECL|macro|MAX_D_FRAMES
mdefine_line|#define MAX_D_FRAMES 15
DECL|macro|MAX_B_FRAMES
mdefine_line|#define MAX_B_FRAMES 31
DECL|macro|B_SUB_VAL_32K
mdefine_line|#define B_SUB_VAL_32K       0x0200
DECL|macro|B_FIFO_SIZE_32K
mdefine_line|#define B_FIFO_SIZE_32K    (0x2000 - B_SUB_VAL_32K)
DECL|macro|B_SUB_VAL_8K
mdefine_line|#define B_SUB_VAL_8K        0x1A00
DECL|macro|B_FIFO_SIZE_8K
mdefine_line|#define B_FIFO_SIZE_8K     (0x2000 - B_SUB_VAL_8K)
DECL|macro|D_FIFO_SIZE
mdefine_line|#define D_FIFO_SIZE  512
DECL|macro|D_FREG_MASK
mdefine_line|#define D_FREG_MASK  0xF
multiline_comment|/************************************************************/
multiline_comment|/* structure holding additional dynamic data -&gt; send marker */
multiline_comment|/************************************************************/
DECL|struct|hfcsx_extra
r_struct
id|hfcsx_extra
(brace
DECL|member|marker
r_int
r_int
id|marker
(braket
l_int|2
op_star
(paren
id|MAX_B_FRAMES
op_plus
l_int|1
)paren
op_plus
(paren
id|MAX_D_FRAMES
op_plus
l_int|1
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|main_irq_hfcsx
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
suffix:semicolon
r_extern
r_void
id|inithfcsx
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_void
id|releasehfcsx
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
