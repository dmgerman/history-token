multiline_comment|/* $Id: hfc_2bs0.h,v 1.3.6.1 2001/02/16 16:43:27 kai Exp $&n; *&n; *  specific defines for CCD&squot;s HFC 2BS0&n; *&n; * Author       Karsten Keil (keil@isdn4linux.de)&n; *&n; * This file is (c) under GNU General Public License&n; *&n; */
DECL|macro|HFC_CTMT
mdefine_line|#define HFC_CTMT&t;0xe0
DECL|macro|HFC_CIRM
mdefine_line|#define HFC_CIRM  &t;0xc0
DECL|macro|HFC_CIP
mdefine_line|#define HFC_CIP&t;&t;0x80
DECL|macro|HFC_Z1
mdefine_line|#define HFC_Z1&t;&t;0x00
DECL|macro|HFC_Z2
mdefine_line|#define HFC_Z2&t;&t;0x08
DECL|macro|HFC_Z_LOW
mdefine_line|#define HFC_Z_LOW&t;0x00
DECL|macro|HFC_Z_HIGH
mdefine_line|#define HFC_Z_HIGH&t;0x04
DECL|macro|HFC_F1_INC
mdefine_line|#define HFC_F1_INC&t;0x28
DECL|macro|HFC_FIFO_IN
mdefine_line|#define HFC_FIFO_IN&t;0x2c
DECL|macro|HFC_F1
mdefine_line|#define HFC_F1&t;&t;0x30
DECL|macro|HFC_F2
mdefine_line|#define HFC_F2&t;&t;0x34
DECL|macro|HFC_F2_INC
mdefine_line|#define HFC_F2_INC&t;0x38
DECL|macro|HFC_FIFO_OUT
mdefine_line|#define HFC_FIFO_OUT&t;0x3c
DECL|macro|HFC_B1
mdefine_line|#define HFC_B1          0x00
DECL|macro|HFC_B2
mdefine_line|#define HFC_B2&t;&t;0x02
DECL|macro|HFC_REC
mdefine_line|#define HFC_REC&t;&t;0x01
DECL|macro|HFC_SEND
mdefine_line|#define HFC_SEND&t;0x00
DECL|macro|HFC_CHANNEL
mdefine_line|#define HFC_CHANNEL(ch) (ch ? HFC_B2 : HFC_B1)
DECL|macro|HFC_STATUS
mdefine_line|#define HFC_STATUS&t;0
DECL|macro|HFC_DATA
mdefine_line|#define HFC_DATA&t;1
DECL|macro|HFC_DATA_NODEB
mdefine_line|#define HFC_DATA_NODEB&t;2
multiline_comment|/* Status (READ) */
DECL|macro|HFC_BUSY
mdefine_line|#define HFC_BUSY&t;0x01
DECL|macro|HFC_TIMINT
mdefine_line|#define HFC_TIMINT&t;0x02
DECL|macro|HFC_EXTINT
mdefine_line|#define HFC_EXTINT&t;0x04
multiline_comment|/* CTMT (Write) */
DECL|macro|HFC_CLTIMER
mdefine_line|#define HFC_CLTIMER 0x10
DECL|macro|HFC_TIM50MS
mdefine_line|#define HFC_TIM50MS 0x08
DECL|macro|HFC_TIMIRQE
mdefine_line|#define HFC_TIMIRQE 0x04
DECL|macro|HFC_TRANSB2
mdefine_line|#define HFC_TRANSB2 0x02
DECL|macro|HFC_TRANSB1
mdefine_line|#define HFC_TRANSB1 0x01
multiline_comment|/* CIRM (Write) */
DECL|macro|HFC_RESET
mdefine_line|#define HFC_RESET  &t;0x08
DECL|macro|HFC_MEM8K
mdefine_line|#define HFC_MEM8K&t;0x10
DECL|macro|HFC_INTA
mdefine_line|#define HFC_INTA&t;0x01
DECL|macro|HFC_INTB
mdefine_line|#define HFC_INTB&t;0x02
DECL|macro|HFC_INTC
mdefine_line|#define HFC_INTC&t;0x03
DECL|macro|HFC_INTD
mdefine_line|#define HFC_INTD&t;0x04
DECL|macro|HFC_INTE
mdefine_line|#define HFC_INTE&t;0x05
DECL|macro|HFC_INTF
mdefine_line|#define HFC_INTF&t;0x06
r_extern
r_void
id|main_irq_hfc
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
id|inithfc
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
id|releasehfc
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
