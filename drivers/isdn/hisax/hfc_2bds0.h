multiline_comment|/* $Id: hfc_2bds0.h,v 1.4.6.2 2001/09/23 22:24:47 kai Exp $&n; *&n; * specific defines for CCD&squot;s HFC 2BDS0&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
DECL|macro|HFCD_CIRM
mdefine_line|#define HFCD_CIRM  &t;0x18
DECL|macro|HFCD_CTMT
mdefine_line|#define HFCD_CTMT&t;0x19
DECL|macro|HFCD_INT_M1
mdefine_line|#define HFCD_INT_M1  &t;0x1A
DECL|macro|HFCD_INT_M2
mdefine_line|#define HFCD_INT_M2  &t;0x1B
DECL|macro|HFCD_INT_S1
mdefine_line|#define HFCD_INT_S1  &t;0x1E
DECL|macro|HFCD_STAT
mdefine_line|#define HFCD_STAT  &t;0x1C
DECL|macro|HFCD_STAT_DISB
mdefine_line|#define HFCD_STAT_DISB  0x1D
DECL|macro|HFCD_STATES
mdefine_line|#define HFCD_STATES  &t;0x30
DECL|macro|HFCD_SCTRL
mdefine_line|#define HFCD_SCTRL  &t;0x31
DECL|macro|HFCD_TEST
mdefine_line|#define HFCD_TEST  &t;0x32
DECL|macro|HFCD_SQ
mdefine_line|#define HFCD_SQ  &t;0x34
DECL|macro|HFCD_CLKDEL
mdefine_line|#define HFCD_CLKDEL  &t;0x37
DECL|macro|HFCD_MST_MODE
mdefine_line|#define HFCD_MST_MODE&t;0x2E
DECL|macro|HFCD_CONN
mdefine_line|#define HFCD_CONN  &t;0x2F
DECL|macro|HFCD_FIFO
mdefine_line|#define HFCD_FIFO&t;0x80
DECL|macro|HFCD_Z1
mdefine_line|#define HFCD_Z1&t;&t;0x10
DECL|macro|HFCD_Z2
mdefine_line|#define HFCD_Z2&t;&t;0x18
DECL|macro|HFCD_Z_LOW
mdefine_line|#define HFCD_Z_LOW&t;0x00
DECL|macro|HFCD_Z_HIGH
mdefine_line|#define HFCD_Z_HIGH&t;0x04
DECL|macro|HFCD_F1_INC
mdefine_line|#define HFCD_F1_INC&t;0x12
DECL|macro|HFCD_FIFO_IN
mdefine_line|#define HFCD_FIFO_IN&t;0x16
DECL|macro|HFCD_F1
mdefine_line|#define HFCD_F1&t;&t;0x1a
DECL|macro|HFCD_F2
mdefine_line|#define HFCD_F2&t;&t;0x1e
DECL|macro|HFCD_F2_INC
mdefine_line|#define HFCD_F2_INC&t;0x22
DECL|macro|HFCD_FIFO_OUT
mdefine_line|#define HFCD_FIFO_OUT&t;0x26
DECL|macro|HFCD_REC
mdefine_line|#define HFCD_REC&t;0x01
DECL|macro|HFCD_SEND
mdefine_line|#define HFCD_SEND&t;0x00
DECL|macro|HFCB_FIFO
mdefine_line|#define HFCB_FIFO&t;0x80
DECL|macro|HFCB_Z1
mdefine_line|#define HFCB_Z1&t;&t;0x00
DECL|macro|HFCB_Z2
mdefine_line|#define HFCB_Z2&t;&t;0x08
DECL|macro|HFCB_Z_LOW
mdefine_line|#define HFCB_Z_LOW&t;0x00
DECL|macro|HFCB_Z_HIGH
mdefine_line|#define HFCB_Z_HIGH&t;0x04
DECL|macro|HFCB_F1_INC
mdefine_line|#define HFCB_F1_INC&t;0x28
DECL|macro|HFCB_FIFO_IN
mdefine_line|#define HFCB_FIFO_IN&t;0x2c
DECL|macro|HFCB_F1
mdefine_line|#define HFCB_F1&t;&t;0x30
DECL|macro|HFCB_F2
mdefine_line|#define HFCB_F2&t;&t;0x34
DECL|macro|HFCB_F2_INC
mdefine_line|#define HFCB_F2_INC&t;0x38
DECL|macro|HFCB_FIFO_OUT
mdefine_line|#define HFCB_FIFO_OUT&t;0x3c
DECL|macro|HFCB_REC
mdefine_line|#define HFCB_REC&t;0x01
DECL|macro|HFCB_SEND
mdefine_line|#define HFCB_SEND&t;0x00
DECL|macro|HFCB_B1
mdefine_line|#define HFCB_B1&t;&t;0x00
DECL|macro|HFCB_B2
mdefine_line|#define HFCB_B2&t;&t;0x02
DECL|macro|HFCB_CHANNEL
mdefine_line|#define HFCB_CHANNEL(ch) (ch ? HFCB_B2 : HFCB_B1)
DECL|macro|HFCD_STATUS
mdefine_line|#define HFCD_STATUS&t;0
DECL|macro|HFCD_DATA
mdefine_line|#define HFCD_DATA&t;1
DECL|macro|HFCD_DATA_NODEB
mdefine_line|#define HFCD_DATA_NODEB&t;2
multiline_comment|/* Status (READ) */
DECL|macro|HFCD_BUSY
mdefine_line|#define HFCD_BUSY&t;0x01
DECL|macro|HFCD_BUSY_NBUSY
mdefine_line|#define HFCD_BUSY_NBUSY&t;0x04
DECL|macro|HFCD_TIMER_ELAP
mdefine_line|#define HFCD_TIMER_ELAP&t;0x10
DECL|macro|HFCD_STATINT
mdefine_line|#define HFCD_STATINT&t;0x20
DECL|macro|HFCD_FRAMEINT
mdefine_line|#define HFCD_FRAMEINT&t;0x40
DECL|macro|HFCD_ANYINT
mdefine_line|#define HFCD_ANYINT&t;0x80
multiline_comment|/* CTMT (Write) */
DECL|macro|HFCD_CLTIMER
mdefine_line|#define HFCD_CLTIMER 0x80
DECL|macro|HFCD_TIM25
mdefine_line|#define HFCD_TIM25  0x00
DECL|macro|HFCD_TIM50
mdefine_line|#define HFCD_TIM50  0x08
DECL|macro|HFCD_TIM400
mdefine_line|#define HFCD_TIM400 0x10
DECL|macro|HFCD_TIM800
mdefine_line|#define HFCD_TIM800 0x18
DECL|macro|HFCD_AUTO_TIMER
mdefine_line|#define HFCD_AUTO_TIMER 0x20
DECL|macro|HFCD_TRANSB2
mdefine_line|#define HFCD_TRANSB2 0x02
DECL|macro|HFCD_TRANSB1
mdefine_line|#define HFCD_TRANSB1 0x01
multiline_comment|/* CIRM (Write) */
DECL|macro|HFCD_RESET
mdefine_line|#define HFCD_RESET  &t;0x08
DECL|macro|HFCD_MEM8K
mdefine_line|#define HFCD_MEM8K&t;0x10
DECL|macro|HFCD_INTA
mdefine_line|#define HFCD_INTA&t;0x01
DECL|macro|HFCD_INTB
mdefine_line|#define HFCD_INTB&t;0x02
DECL|macro|HFCD_INTC
mdefine_line|#define HFCD_INTC&t;0x03
DECL|macro|HFCD_INTD
mdefine_line|#define HFCD_INTD&t;0x04
DECL|macro|HFCD_INTE
mdefine_line|#define HFCD_INTE&t;0x05
DECL|macro|HFCD_INTF
mdefine_line|#define HFCD_INTF&t;0x06
multiline_comment|/* INT_M1;INT_S1 */
DECL|macro|HFCD_INTS_B1TRANS
mdefine_line|#define HFCD_INTS_B1TRANS&t;0x01
DECL|macro|HFCD_INTS_B2TRANS
mdefine_line|#define HFCD_INTS_B2TRANS&t;0x02
DECL|macro|HFCD_INTS_DTRANS
mdefine_line|#define HFCD_INTS_DTRANS&t;0x04
DECL|macro|HFCD_INTS_B1REC
mdefine_line|#define HFCD_INTS_B1REC&t;&t;0x08
DECL|macro|HFCD_INTS_B2REC
mdefine_line|#define HFCD_INTS_B2REC&t;&t;0x10
DECL|macro|HFCD_INTS_DREC
mdefine_line|#define HFCD_INTS_DREC&t;&t;0x20
DECL|macro|HFCD_INTS_L1STATE
mdefine_line|#define HFCD_INTS_L1STATE&t;0x40
DECL|macro|HFCD_INTS_TIMER
mdefine_line|#define HFCD_INTS_TIMER&t;&t;0x80
multiline_comment|/* INT_M2 */
DECL|macro|HFCD_IRQ_ENABLE
mdefine_line|#define HFCD_IRQ_ENABLE&t;&t;0x08
multiline_comment|/* STATES */
DECL|macro|HFCD_LOAD_STATE
mdefine_line|#define HFCD_LOAD_STATE&t;&t;0x10
DECL|macro|HFCD_ACTIVATE
mdefine_line|#define HFCD_ACTIVATE&t;&t;0x20
DECL|macro|HFCD_DO_ACTION
mdefine_line|#define HFCD_DO_ACTION&t;&t;0x40
multiline_comment|/* HFCD_MST_MODE */
DECL|macro|HFCD_MASTER
mdefine_line|#define HFCD_MASTER&t;&t;0x01
multiline_comment|/* HFCD_SCTRL */
DECL|macro|SCTRL_B1_ENA
mdefine_line|#define SCTRL_B1_ENA&t;&t;0x01
DECL|macro|SCTRL_B2_ENA
mdefine_line|#define SCTRL_B2_ENA&t;&t;0x02
DECL|macro|SCTRL_LOW_PRIO
mdefine_line|#define SCTRL_LOW_PRIO&t;&t;0x08
DECL|macro|SCTRL_SQ_ENA
mdefine_line|#define SCTRL_SQ_ENA&t;&t;0x10
DECL|macro|SCTRL_TEST
mdefine_line|#define SCTRL_TEST&t;&t;0x20
DECL|macro|SCTRL_NONE_CAP
mdefine_line|#define SCTRL_NONE_CAP&t;&t;0x40
DECL|macro|SCTRL_PWR_DOWN
mdefine_line|#define SCTRL_PWR_DOWN&t;&t;0x80
multiline_comment|/* HFCD_TEST */
DECL|macro|HFCD_AUTO_AWAKE
mdefine_line|#define HFCD_AUTO_AWAKE&t;&t;0x01
r_extern
r_void
id|main_irq_2bds0
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
id|init2bds0
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
id|release2bds0
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
id|hfc2bds0_interrupt
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_char
id|val
)paren
suffix:semicolon
r_extern
r_void
id|set_cs_func
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
