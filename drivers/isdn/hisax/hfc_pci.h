multiline_comment|/* $Id: hfc_pci.h,v 1.8.6.2 2001/09/23 22:24:48 kai Exp $&n; *&n; * specific defines for CCD&squot;s HFC 2BDS0 PCI chips&n; *&n; * Author       Werner Cornelius&n; * Copyright    by Werner Cornelius  &lt;werner@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
multiline_comment|/*********************************************/
multiline_comment|/* thresholds for transparent B-channel mode */
multiline_comment|/* change mask and threshold simultaneously  */
multiline_comment|/*********************************************/
DECL|macro|HFCPCI_BTRANS_THRESHOLD
mdefine_line|#define HFCPCI_BTRANS_THRESHOLD 128
DECL|macro|HFCPCI_BTRANS_THRESMASK
mdefine_line|#define HFCPCI_BTRANS_THRESMASK 0x00
multiline_comment|/* defines for PCI config */
DECL|macro|PCI_ENA_MEMIO
mdefine_line|#define PCI_ENA_MEMIO    0x02
DECL|macro|PCI_ENA_MASTER
mdefine_line|#define PCI_ENA_MASTER   0x04
multiline_comment|/* GCI/IOM bus monitor registers */
DECL|macro|HCFPCI_C_I
mdefine_line|#define HCFPCI_C_I       0x08
DECL|macro|HFCPCI_TRxR
mdefine_line|#define HFCPCI_TRxR      0x0C
DECL|macro|HFCPCI_MON1_D
mdefine_line|#define HFCPCI_MON1_D    0x28
DECL|macro|HFCPCI_MON2_D
mdefine_line|#define HFCPCI_MON2_D    0x2C
multiline_comment|/* GCI/IOM bus timeslot registers */
DECL|macro|HFCPCI_B1_SSL
mdefine_line|#define HFCPCI_B1_SSL    0x80
DECL|macro|HFCPCI_B2_SSL
mdefine_line|#define HFCPCI_B2_SSL    0x84
DECL|macro|HFCPCI_AUX1_SSL
mdefine_line|#define HFCPCI_AUX1_SSL  0x88
DECL|macro|HFCPCI_AUX2_SSL
mdefine_line|#define HFCPCI_AUX2_SSL  0x8C
DECL|macro|HFCPCI_B1_RSL
mdefine_line|#define HFCPCI_B1_RSL    0x90
DECL|macro|HFCPCI_B2_RSL
mdefine_line|#define HFCPCI_B2_RSL    0x94
DECL|macro|HFCPCI_AUX1_RSL
mdefine_line|#define HFCPCI_AUX1_RSL  0x98
DECL|macro|HFCPCI_AUX2_RSL
mdefine_line|#define HFCPCI_AUX2_RSL  0x9C
multiline_comment|/* GCI/IOM bus data registers */
DECL|macro|HFCPCI_B1_D
mdefine_line|#define HFCPCI_B1_D      0xA0
DECL|macro|HFCPCI_B2_D
mdefine_line|#define HFCPCI_B2_D      0xA4
DECL|macro|HFCPCI_AUX1_D
mdefine_line|#define HFCPCI_AUX1_D    0xA8
DECL|macro|HFCPCI_AUX2_D
mdefine_line|#define HFCPCI_AUX2_D    0xAC
multiline_comment|/* GCI/IOM bus configuration registers */
DECL|macro|HFCPCI_MST_EMOD
mdefine_line|#define HFCPCI_MST_EMOD  0xB4
DECL|macro|HFCPCI_MST_MODE
mdefine_line|#define HFCPCI_MST_MODE&t; 0xB8
DECL|macro|HFCPCI_CONNECT
mdefine_line|#define HFCPCI_CONNECT &t; 0xBC
multiline_comment|/* Interrupt and status registers */
DECL|macro|HFCPCI_FIFO_EN
mdefine_line|#define HFCPCI_FIFO_EN   0x44
DECL|macro|HFCPCI_TRM
mdefine_line|#define HFCPCI_TRM       0x48
DECL|macro|HFCPCI_B_MODE
mdefine_line|#define HFCPCI_B_MODE    0x4C
DECL|macro|HFCPCI_CHIP_ID
mdefine_line|#define HFCPCI_CHIP_ID   0x58
DECL|macro|HFCPCI_CIRM
mdefine_line|#define HFCPCI_CIRM  &t; 0x60
DECL|macro|HFCPCI_CTMT
mdefine_line|#define HFCPCI_CTMT&t; 0x64
DECL|macro|HFCPCI_INT_M1
mdefine_line|#define HFCPCI_INT_M1  &t; 0x68
DECL|macro|HFCPCI_INT_M2
mdefine_line|#define HFCPCI_INT_M2  &t; 0x6C
DECL|macro|HFCPCI_INT_S1
mdefine_line|#define HFCPCI_INT_S1  &t; 0x78
DECL|macro|HFCPCI_INT_S2
mdefine_line|#define HFCPCI_INT_S2  &t; 0x7C
DECL|macro|HFCPCI_STATUS
mdefine_line|#define HFCPCI_STATUS  &t; 0x70
multiline_comment|/* S/T section registers */
DECL|macro|HFCPCI_STATES
mdefine_line|#define HFCPCI_STATES  &t; 0xC0
DECL|macro|HFCPCI_SCTRL
mdefine_line|#define HFCPCI_SCTRL  &t; 0xC4
DECL|macro|HFCPCI_SCTRL_E
mdefine_line|#define HFCPCI_SCTRL_E   0xC8
DECL|macro|HFCPCI_SCTRL_R
mdefine_line|#define HFCPCI_SCTRL_R   0xCC
DECL|macro|HFCPCI_SQ
mdefine_line|#define HFCPCI_SQ  &t; 0xD0
DECL|macro|HFCPCI_CLKDEL
mdefine_line|#define HFCPCI_CLKDEL  &t; 0xDC
DECL|macro|HFCPCI_B1_REC
mdefine_line|#define HFCPCI_B1_REC    0xF0
DECL|macro|HFCPCI_B1_SEND
mdefine_line|#define HFCPCI_B1_SEND   0xF0
DECL|macro|HFCPCI_B2_REC
mdefine_line|#define HFCPCI_B2_REC    0xF4
DECL|macro|HFCPCI_B2_SEND
mdefine_line|#define HFCPCI_B2_SEND   0xF4
DECL|macro|HFCPCI_D_REC
mdefine_line|#define HFCPCI_D_REC     0xF8
DECL|macro|HFCPCI_D_SEND
mdefine_line|#define HFCPCI_D_SEND    0xF8
DECL|macro|HFCPCI_E_REC
mdefine_line|#define HFCPCI_E_REC     0xFC
multiline_comment|/* bits in status register (READ) */
DECL|macro|HFCPCI_PCI_PROC
mdefine_line|#define HFCPCI_PCI_PROC   0x02
DECL|macro|HFCPCI_NBUSY
mdefine_line|#define HFCPCI_NBUSY&t;  0x04 
DECL|macro|HFCPCI_TIMER_ELAP
mdefine_line|#define HFCPCI_TIMER_ELAP 0x10
DECL|macro|HFCPCI_STATINT
mdefine_line|#define HFCPCI_STATINT&t;  0x20
DECL|macro|HFCPCI_FRAMEINT
mdefine_line|#define HFCPCI_FRAMEINT&t;  0x40
DECL|macro|HFCPCI_ANYINT
mdefine_line|#define HFCPCI_ANYINT&t;  0x80
multiline_comment|/* bits in CTMT (Write) */
DECL|macro|HFCPCI_CLTIMER
mdefine_line|#define HFCPCI_CLTIMER    0x80
DECL|macro|HFCPCI_TIM3_125
mdefine_line|#define HFCPCI_TIM3_125   0x04
DECL|macro|HFCPCI_TIM25
mdefine_line|#define HFCPCI_TIM25      0x10
DECL|macro|HFCPCI_TIM50
mdefine_line|#define HFCPCI_TIM50      0x14
DECL|macro|HFCPCI_TIM400
mdefine_line|#define HFCPCI_TIM400     0x18
DECL|macro|HFCPCI_TIM800
mdefine_line|#define HFCPCI_TIM800     0x1C
DECL|macro|HFCPCI_AUTO_TIMER
mdefine_line|#define HFCPCI_AUTO_TIMER 0x20
DECL|macro|HFCPCI_TRANSB2
mdefine_line|#define HFCPCI_TRANSB2    0x02
DECL|macro|HFCPCI_TRANSB1
mdefine_line|#define HFCPCI_TRANSB1    0x01
multiline_comment|/* bits in CIRM (Write) */
DECL|macro|HFCPCI_AUX_MSK
mdefine_line|#define HFCPCI_AUX_MSK    0x07
DECL|macro|HFCPCI_RESET
mdefine_line|#define HFCPCI_RESET  &t;  0x08
DECL|macro|HFCPCI_B1_REV
mdefine_line|#define HFCPCI_B1_REV     0x40
DECL|macro|HFCPCI_B2_REV
mdefine_line|#define HFCPCI_B2_REV     0x80
multiline_comment|/* bits in INT_M1 and INT_S1 */
DECL|macro|HFCPCI_INTS_B1TRANS
mdefine_line|#define HFCPCI_INTS_B1TRANS  0x01
DECL|macro|HFCPCI_INTS_B2TRANS
mdefine_line|#define HFCPCI_INTS_B2TRANS  0x02
DECL|macro|HFCPCI_INTS_DTRANS
mdefine_line|#define HFCPCI_INTS_DTRANS   0x04
DECL|macro|HFCPCI_INTS_B1REC
mdefine_line|#define HFCPCI_INTS_B1REC    0x08
DECL|macro|HFCPCI_INTS_B2REC
mdefine_line|#define HFCPCI_INTS_B2REC    0x10
DECL|macro|HFCPCI_INTS_DREC
mdefine_line|#define HFCPCI_INTS_DREC     0x20
DECL|macro|HFCPCI_INTS_L1STATE
mdefine_line|#define HFCPCI_INTS_L1STATE  0x40
DECL|macro|HFCPCI_INTS_TIMER
mdefine_line|#define HFCPCI_INTS_TIMER    0x80
multiline_comment|/* bits in INT_M2 */
DECL|macro|HFCPCI_PROC_TRANS
mdefine_line|#define HFCPCI_PROC_TRANS    0x01
DECL|macro|HFCPCI_GCI_I_CHG
mdefine_line|#define HFCPCI_GCI_I_CHG     0x02
DECL|macro|HFCPCI_GCI_MON_REC
mdefine_line|#define HFCPCI_GCI_MON_REC   0x04
DECL|macro|HFCPCI_IRQ_ENABLE
mdefine_line|#define HFCPCI_IRQ_ENABLE    0x08
DECL|macro|HFCPCI_PMESEL
mdefine_line|#define HFCPCI_PMESEL        0x80
multiline_comment|/* bits in STATES */
DECL|macro|HFCPCI_STATE_MSK
mdefine_line|#define HFCPCI_STATE_MSK     0x0F
DECL|macro|HFCPCI_LOAD_STATE
mdefine_line|#define HFCPCI_LOAD_STATE    0x10
DECL|macro|HFCPCI_ACTIVATE
mdefine_line|#define HFCPCI_ACTIVATE&t;     0x20
DECL|macro|HFCPCI_DO_ACTION
mdefine_line|#define HFCPCI_DO_ACTION     0x40
DECL|macro|HFCPCI_NT_G2_G3
mdefine_line|#define HFCPCI_NT_G2_G3      0x80
multiline_comment|/* bits in HFCD_MST_MODE */
DECL|macro|HFCPCI_MASTER
mdefine_line|#define HFCPCI_MASTER&t;     0x01
DECL|macro|HFCPCI_SLAVE
mdefine_line|#define HFCPCI_SLAVE         0x00
multiline_comment|/* remaining bits are for codecs control */
multiline_comment|/* bits in HFCD_SCTRL */
DECL|macro|SCTRL_B1_ENA
mdefine_line|#define SCTRL_B1_ENA&t;     0x01
DECL|macro|SCTRL_B2_ENA
mdefine_line|#define SCTRL_B2_ENA&t;     0x02
DECL|macro|SCTRL_MODE_TE
mdefine_line|#define SCTRL_MODE_TE        0x00
DECL|macro|SCTRL_MODE_NT
mdefine_line|#define SCTRL_MODE_NT        0x04
DECL|macro|SCTRL_LOW_PRIO
mdefine_line|#define SCTRL_LOW_PRIO&t;     0x08
DECL|macro|SCTRL_SQ_ENA
mdefine_line|#define SCTRL_SQ_ENA&t;     0x10
DECL|macro|SCTRL_TEST
mdefine_line|#define SCTRL_TEST&t;     0x20
DECL|macro|SCTRL_NONE_CAP
mdefine_line|#define SCTRL_NONE_CAP&t;     0x40
DECL|macro|SCTRL_PWR_DOWN
mdefine_line|#define SCTRL_PWR_DOWN&t;     0x80
multiline_comment|/* bits in SCTRL_E  */
DECL|macro|HFCPCI_AUTO_AWAKE
mdefine_line|#define HFCPCI_AUTO_AWAKE    0x01
DECL|macro|HFCPCI_DBIT_1
mdefine_line|#define HFCPCI_DBIT_1        0x04
DECL|macro|HFCPCI_IGNORE_COL
mdefine_line|#define HFCPCI_IGNORE_COL    0x08
DECL|macro|HFCPCI_CHG_B1_B2
mdefine_line|#define HFCPCI_CHG_B1_B2     0x80
multiline_comment|/****************************/
multiline_comment|/* bits in FIFO_EN register */
multiline_comment|/****************************/
DECL|macro|HFCPCI_FIFOEN_B1
mdefine_line|#define HFCPCI_FIFOEN_B1     0x03
DECL|macro|HFCPCI_FIFOEN_B2
mdefine_line|#define HFCPCI_FIFOEN_B2     0x0C
DECL|macro|HFCPCI_FIFOEN_DTX
mdefine_line|#define HFCPCI_FIFOEN_DTX    0x10
DECL|macro|HFCPCI_FIFOEN_B1TX
mdefine_line|#define HFCPCI_FIFOEN_B1TX   0x01
DECL|macro|HFCPCI_FIFOEN_B1RX
mdefine_line|#define HFCPCI_FIFOEN_B1RX   0x02
DECL|macro|HFCPCI_FIFOEN_B2TX
mdefine_line|#define HFCPCI_FIFOEN_B2TX   0x04
DECL|macro|HFCPCI_FIFOEN_B2RX
mdefine_line|#define HFCPCI_FIFOEN_B2RX   0x08
multiline_comment|/***********************************/
multiline_comment|/* definitions of fifo memory area */
multiline_comment|/***********************************/
DECL|macro|MAX_D_FRAMES
mdefine_line|#define MAX_D_FRAMES 15
DECL|macro|MAX_B_FRAMES
mdefine_line|#define MAX_B_FRAMES 31
DECL|macro|B_SUB_VAL
mdefine_line|#define B_SUB_VAL    0x200
DECL|macro|B_FIFO_SIZE
mdefine_line|#define B_FIFO_SIZE  (0x2000 - B_SUB_VAL)
DECL|macro|D_FIFO_SIZE
mdefine_line|#define D_FIFO_SIZE  512
DECL|macro|D_FREG_MASK
mdefine_line|#define D_FREG_MASK  0xF
r_typedef
r_struct
(brace
DECL|member|z1
r_int
r_int
id|z1
suffix:semicolon
multiline_comment|/* Z1 pointer 16 Bit */
DECL|member|z2
r_int
r_int
id|z2
suffix:semicolon
multiline_comment|/* Z2 pointer 16 Bit */
DECL|typedef|z_type
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|z_type
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|data
id|u_char
id|data
(braket
id|D_FIFO_SIZE
)braket
suffix:semicolon
multiline_comment|/* FIFO data space */
DECL|member|fill1
id|u_char
id|fill1
(braket
l_int|0x20A0
op_minus
id|D_FIFO_SIZE
)braket
suffix:semicolon
multiline_comment|/* reserved, do not use */
DECL|member|f1
DECL|member|f2
id|u_char
id|f1
comma
id|f2
suffix:semicolon
multiline_comment|/* f pointers */
DECL|member|fill2
id|u_char
id|fill2
(braket
l_int|0x20C0
op_minus
l_int|0x20A2
)braket
suffix:semicolon
multiline_comment|/* reserved, do not use */
DECL|member|za
id|z_type
id|za
(braket
id|MAX_D_FRAMES
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* mask index with D_FREG_MASK for access */
DECL|member|fill3
id|u_char
id|fill3
(braket
l_int|0x4000
op_minus
l_int|0x2100
)braket
suffix:semicolon
multiline_comment|/* align 16K */
DECL|typedef|dfifo_type
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|dfifo_type
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|za
id|z_type
id|za
(braket
id|MAX_B_FRAMES
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* only range 0x0..0x1F allowed */
DECL|member|f1
DECL|member|f2
id|u_char
id|f1
comma
id|f2
suffix:semicolon
multiline_comment|/* f pointers */
DECL|member|fill
id|u_char
id|fill
(braket
l_int|0x2100
op_minus
l_int|0x2082
)braket
suffix:semicolon
multiline_comment|/* alignment */
DECL|typedef|bzfifo_type
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|bzfifo_type
suffix:semicolon
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|d_tx
id|dfifo_type
id|d_tx
suffix:semicolon
multiline_comment|/* D-send channel */
DECL|member|d_rx
id|dfifo_type
id|d_rx
suffix:semicolon
multiline_comment|/* D-receive channel */
DECL|member|d_chan
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|d_chan
suffix:semicolon
r_struct
(brace
DECL|member|fill1
id|u_char
id|fill1
(braket
l_int|0x200
)braket
suffix:semicolon
DECL|member|txdat_b1
id|u_char
id|txdat_b1
(braket
id|B_FIFO_SIZE
)braket
suffix:semicolon
DECL|member|txbz_b1
id|bzfifo_type
id|txbz_b1
suffix:semicolon
DECL|member|txbz_b2
id|bzfifo_type
id|txbz_b2
suffix:semicolon
DECL|member|txdat_b2
id|u_char
id|txdat_b2
(braket
id|B_FIFO_SIZE
)braket
suffix:semicolon
DECL|member|fill2
id|u_char
id|fill2
(braket
id|D_FIFO_SIZE
)braket
suffix:semicolon
DECL|member|rxdat_b1
id|u_char
id|rxdat_b1
(braket
id|B_FIFO_SIZE
)braket
suffix:semicolon
DECL|member|rxbz_b1
id|bzfifo_type
id|rxbz_b1
suffix:semicolon
DECL|member|rxbz_b2
id|bzfifo_type
id|rxbz_b2
suffix:semicolon
DECL|member|rxdat_b2
id|u_char
id|rxdat_b2
(braket
id|B_FIFO_SIZE
)braket
suffix:semicolon
DECL|member|b_chans
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|b_chans
suffix:semicolon
DECL|member|fill
id|u_char
id|fill
(braket
l_int|32768
)braket
suffix:semicolon
DECL|typedef|fifo_area
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|fifo_area
suffix:semicolon
singleline_comment|//#define Write_hfc(a,b,c) (*(((u_char *)a-&gt;hw.hfcpci.pci_io)+b) = c) 
singleline_comment|//#define Read_hfc(a,b) (*(((u_char *)a-&gt;hw.hfcpci.pci_io)+b))
DECL|macro|Write_hfc
mdefine_line|#define Write_hfc(a,b,c)&t;writeb(c, ((u_char *)a-&gt;hw.hfcpci.pci_io)+b)
DECL|macro|Read_hfc
mdefine_line|#define Read_hfc(a,b)&t;&t;readb(((u_char *)a-&gt;hw.hfcpci.pci_io)+b)
r_extern
r_void
id|main_irq_hcpci
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
id|inithfcpci
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
id|releasehfcpci
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
eof
