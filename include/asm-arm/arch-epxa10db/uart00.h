multiline_comment|/* *&n; *  Copyright (C) 2001 Altera Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __UART00_H
DECL|macro|__UART00_H
mdefine_line|#define __UART00_H
multiline_comment|/*&n; * Register definitions for the UART&n; */
DECL|macro|UART_TX_FIFO_SIZE
mdefine_line|#define UART_TX_FIFO_SIZE      (15)
DECL|macro|UART_RSR
mdefine_line|#define UART_RSR(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x00 ))
DECL|macro|UART_RSR_RX_LEVEL_MSK
mdefine_line|#define UART_RSR_RX_LEVEL_MSK (0x1f)
DECL|macro|UART_RSR_RX_LEVEL_OFST
mdefine_line|#define UART_RSR_RX_LEVEL_OFST (0)
DECL|macro|UART_RSR_RE_MSK
mdefine_line|#define UART_RSR_RE_MSK (0x80)
DECL|macro|UART_RSR_RE_OFST
mdefine_line|#define UART_RSR_RE_OFST (7)
DECL|macro|UART_RDS
mdefine_line|#define UART_RDS(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x04 ))
DECL|macro|UART_RDS_BI_MSK
mdefine_line|#define UART_RDS_BI_MSK (0x8)
DECL|macro|UART_RDS_BI_OFST
mdefine_line|#define UART_RDS_BI_OFST (4)
DECL|macro|UART_RDS_FE_MSK
mdefine_line|#define UART_RDS_FE_MSK (0x4)
DECL|macro|UART_RDS_FE_OFST
mdefine_line|#define UART_RDS_FE_OFST (2)
DECL|macro|UART_RDS_PE_MSK
mdefine_line|#define UART_RDS_PE_MSK (0x2)
DECL|macro|UART_RDS_PE_OFST
mdefine_line|#define UART_RDS_PE_OFST (1)
DECL|macro|UART_RDS_OE_MSK
mdefine_line|#define UART_RDS_OE_MSK (0x1)
DECL|macro|UART_RDS_OE_OFST
mdefine_line|#define UART_RDS_OE_OFST (0)
DECL|macro|UART_RD
mdefine_line|#define UART_RD(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x08 ))
DECL|macro|UART_RD_RX_DATA_MSK
mdefine_line|#define UART_RD_RX_DATA_MSK (0xff)
DECL|macro|UART_RD_RX_DATA_OFST
mdefine_line|#define UART_RD_RX_DATA_OFST (0)
DECL|macro|UART_TSR
mdefine_line|#define UART_TSR(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x0c ))
DECL|macro|UART_TSR_TX_LEVEL_MSK
mdefine_line|#define UART_TSR_TX_LEVEL_MSK (0x1f)
DECL|macro|UART_TSR_TX_LEVEL_OFST
mdefine_line|#define UART_TSR_TX_LEVEL_OFST (0)
DECL|macro|UART_TSR_TXI_MSK
mdefine_line|#define UART_TSR_TXI_MSK (0x80)
DECL|macro|UART_TSR_TXI_OFST
mdefine_line|#define UART_TSR_TXI_OFST (7)
DECL|macro|UART_TD
mdefine_line|#define UART_TD(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x10 ))
DECL|macro|UART_TD_TX_DATA_MSK
mdefine_line|#define UART_TD_TX_DATA_MSK (0xff)
DECL|macro|UART_TD_TX_DATA_OFST
mdefine_line|#define UART_TD_TX_DATA_OFST (0)
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x14 ))
DECL|macro|UART_FCR_RX_THR_MSK
mdefine_line|#define UART_FCR_RX_THR_MSK (0xd0)
DECL|macro|UART_FCR_RX_THR_OFST
mdefine_line|#define UART_FCR_RX_THR_OFST (5)
DECL|macro|UART_FCR_RX_THR_1
mdefine_line|#define UART_FCR_RX_THR_1 (0x00)
DECL|macro|UART_FCR_RX_THR_2
mdefine_line|#define UART_FCR_RX_THR_2 (0x20)
DECL|macro|UART_FCR_RX_THR_4
mdefine_line|#define UART_FCR_RX_THR_4 (0x40)
DECL|macro|UART_FCR_RX_THR_6
mdefine_line|#define UART_FCR_RX_THR_6 (0x60)
DECL|macro|UART_FCR_RX_THR_8
mdefine_line|#define UART_FCR_RX_THR_8 (0x80)
DECL|macro|UART_FCR_RX_THR_10
mdefine_line|#define UART_FCR_RX_THR_10 (0xa0)
DECL|macro|UART_FCR_RX_THR_12
mdefine_line|#define UART_FCR_RX_THR_12 (0xc0)
DECL|macro|UART_FCR_RX_THR_14
mdefine_line|#define UART_FCR_RX_THR_14 (0xd0)
DECL|macro|UART_FCR_TX_THR_MSK
mdefine_line|#define UART_FCR_TX_THR_MSK (0x1c)
DECL|macro|UART_FCR_TX_THR_OFST
mdefine_line|#define UART_FCR_TX_THR_OFST (2)
DECL|macro|UART_FCR_TX_THR_0
mdefine_line|#define UART_FCR_TX_THR_0 (0x00)
DECL|macro|UART_FCR_TX_THR_2
mdefine_line|#define UART_FCR_TX_THR_2 (0x04)
DECL|macro|UART_FCR_TX_THR_4
mdefine_line|#define UART_FCR_TX_THR_4 (0x08)
DECL|macro|UART_FCR_TX_THR_8
mdefine_line|#define UART_FCR_TX_THR_8 (0x0c)
DECL|macro|UART_FCR_TX_THR_10
mdefine_line|#define UART_FCR_TX_THR_10 (0x10)
DECL|macro|UART_FCR_TX_THR_12
mdefine_line|#define UART_FCR_TX_THR_12 (0x14)
DECL|macro|UART_FCR_TX_THR_14
mdefine_line|#define UART_FCR_TX_THR_14 (0x18)
DECL|macro|UART_FCR_TX_THR_15
mdefine_line|#define UART_FCR_TX_THR_15 (0x1c)
DECL|macro|UART_FCR_RC_MSK
mdefine_line|#define UART_FCR_RC_MSK (0x02)
DECL|macro|UART_FCR_RC_OFST
mdefine_line|#define UART_FCR_RC_OFST (1)
DECL|macro|UART_FCR_TC_MSK
mdefine_line|#define UART_FCR_TC_MSK (0x01)
DECL|macro|UART_FCR_TC_OFST
mdefine_line|#define UART_FCR_TC_OFST (0)
DECL|macro|UART_IES
mdefine_line|#define UART_IES(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x18 ))
DECL|macro|UART_IES_ME_MSK
mdefine_line|#define UART_IES_ME_MSK (0x8)
DECL|macro|UART_IES_ME_OFST
mdefine_line|#define UART_IES_ME_OFST (3)
DECL|macro|UART_IES_TIE_MSK
mdefine_line|#define UART_IES_TIE_MSK (0x4)
DECL|macro|UART_IES_TIE_OFST
mdefine_line|#define UART_IES_TIE_OFST (2)
DECL|macro|UART_IES_TE_MSK
mdefine_line|#define UART_IES_TE_MSK (0x2)
DECL|macro|UART_IES_TE_OFST
mdefine_line|#define UART_IES_TE_OFST (1)
DECL|macro|UART_IES_RE_MSK
mdefine_line|#define UART_IES_RE_MSK (0x1)
DECL|macro|UART_IES_RE_OFST
mdefine_line|#define UART_IES_RE_OFST (0)
DECL|macro|UART_IEC
mdefine_line|#define UART_IEC(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x1c ))
DECL|macro|UART_IEC_ME_MSK
mdefine_line|#define UART_IEC_ME_MSK (0x8)
DECL|macro|UART_IEC_ME_OFST
mdefine_line|#define UART_IEC_ME_OFST (3)
DECL|macro|UART_IEC_TIE_MSK
mdefine_line|#define UART_IEC_TIE_MSK (0x4)
DECL|macro|UART_IEC_TIE_OFST
mdefine_line|#define UART_IEC_TIE_OFST (2)
DECL|macro|UART_IEC_TE_MSK
mdefine_line|#define UART_IEC_TE_MSK (0x2)
DECL|macro|UART_IEC_TE_OFST
mdefine_line|#define UART_IEC_TE_OFST (1)
DECL|macro|UART_IEC_RE_MSK
mdefine_line|#define UART_IEC_RE_MSK (0x1)
DECL|macro|UART_IEC_RE_OFST
mdefine_line|#define UART_IEC_RE_OFST (0)
DECL|macro|UART_ISR
mdefine_line|#define UART_ISR(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x20 ))
DECL|macro|UART_ISR_MI_MSK
mdefine_line|#define UART_ISR_MI_MSK (0x8)
DECL|macro|UART_ISR_MI_OFST
mdefine_line|#define UART_ISR_MI_OFST (3)
DECL|macro|UART_ISR_TII_MSK
mdefine_line|#define UART_ISR_TII_MSK (0x4)
DECL|macro|UART_ISR_TII_OFST
mdefine_line|#define UART_ISR_TII_OFST (2)
DECL|macro|UART_ISR_TI_MSK
mdefine_line|#define UART_ISR_TI_MSK (0x2)
DECL|macro|UART_ISR_TI_OFST
mdefine_line|#define UART_ISR_TI_OFST (1)
DECL|macro|UART_ISR_RI_MSK
mdefine_line|#define UART_ISR_RI_MSK (0x1)
DECL|macro|UART_ISR_RI_OFST
mdefine_line|#define UART_ISR_RI_OFST (0)
DECL|macro|UART_IID
mdefine_line|#define UART_IID(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x24 ))
DECL|macro|UART_IID_IID_MSK
mdefine_line|#define UART_IID_IID_MSK (0x7)
DECL|macro|UART_IID_IID_OFST
mdefine_line|#define UART_IID_IID_OFST (0)
DECL|macro|UART_MC
mdefine_line|#define UART_MC(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x28 ))
DECL|macro|UART_MC_OE_MSK
mdefine_line|#define UART_MC_OE_MSK (0x40)
DECL|macro|UART_MC_OE_OFST
mdefine_line|#define UART_MC_OE_OFST (6)
DECL|macro|UART_MC_SP_MSK
mdefine_line|#define UART_MC_SP_MSK (0x20)
DECL|macro|UART_MC_SP_OFST
mdefine_line|#define UART_MC_SP_OFST (5)
DECL|macro|UART_MC_EP_MSK
mdefine_line|#define UART_MC_EP_MSK (0x10)
DECL|macro|UART_MC_EP_OFST
mdefine_line|#define UART_MC_EP_OFST (4)
DECL|macro|UART_MC_PE_MSK
mdefine_line|#define UART_MC_PE_MSK (0x08)
DECL|macro|UART_MC_PE_OFST
mdefine_line|#define UART_MC_PE_OFST (3)
DECL|macro|UART_MC_ST_MSK
mdefine_line|#define UART_MC_ST_MSK (0x04)
DECL|macro|UART_MC_ST_ONE
mdefine_line|#define UART_MC_ST_ONE (0x0)
DECL|macro|UART_MC_ST_TWO
mdefine_line|#define UART_MC_ST_TWO (0x04)
DECL|macro|UART_MC_ST_OFST
mdefine_line|#define UART_MC_ST_OFST (2)
DECL|macro|UART_MC_CLS_MSK
mdefine_line|#define UART_MC_CLS_MSK (0x03)
DECL|macro|UART_MC_CLS_OFST
mdefine_line|#define UART_MC_CLS_OFST (0)
DECL|macro|UART_MC_CLS_CHARLEN_5
mdefine_line|#define UART_MC_CLS_CHARLEN_5 (0)
DECL|macro|UART_MC_CLS_CHARLEN_6
mdefine_line|#define UART_MC_CLS_CHARLEN_6 (1)
DECL|macro|UART_MC_CLS_CHARLEN_7
mdefine_line|#define UART_MC_CLS_CHARLEN_7 (2)
DECL|macro|UART_MC_CLS_CHARLEN_8
mdefine_line|#define UART_MC_CLS_CHARLEN_8 (3)
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x2c ))
DECL|macro|UART_MCR_AC_MSK
mdefine_line|#define UART_MCR_AC_MSK (0x80)
DECL|macro|UART_MCR_AC_OFST
mdefine_line|#define UART_MCR_AC_OFST (7)
DECL|macro|UART_MCR_AR_MSK
mdefine_line|#define UART_MCR_AR_MSK (0x40)
DECL|macro|UART_MCR_AR_OFST
mdefine_line|#define UART_MCR_AR_OFST (6)
DECL|macro|UART_MCR_BR_MSK
mdefine_line|#define UART_MCR_BR_MSK (0x20)
DECL|macro|UART_MCR_BR_OFST
mdefine_line|#define UART_MCR_BR_OFST (5)
DECL|macro|UART_MCR_LB_MSK
mdefine_line|#define UART_MCR_LB_MSK (0x10)
DECL|macro|UART_MCR_LB_OFST
mdefine_line|#define UART_MCR_LB_OFST (4)
DECL|macro|UART_MCR_DCD_MSK
mdefine_line|#define UART_MCR_DCD_MSK (0x08)
DECL|macro|UART_MCR_DCD_OFST
mdefine_line|#define UART_MCR_DCD_OFST (3)
DECL|macro|UART_MCR_RI_MSK
mdefine_line|#define UART_MCR_RI_MSK (0x04)
DECL|macro|UART_MCR_RI_OFST
mdefine_line|#define UART_MCR_RI_OFST (2)
DECL|macro|UART_MCR_DTR_MSK
mdefine_line|#define UART_MCR_DTR_MSK (0x02)
DECL|macro|UART_MCR_DTR_OFST
mdefine_line|#define UART_MCR_DTR_OFST (1)
DECL|macro|UART_MCR_RTS_MSK
mdefine_line|#define UART_MCR_RTS_MSK (0x01)
DECL|macro|UART_MCR_RTS_OFST
mdefine_line|#define UART_MCR_RTS_OFST (0)
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x30 ))
DECL|macro|UART_MSR_DCD_MSK
mdefine_line|#define UART_MSR_DCD_MSK (0x80)
DECL|macro|UART_MSR_DCD_OFST
mdefine_line|#define UART_MSR_DCD_OFST (7)
DECL|macro|UART_MSR_RI_MSK
mdefine_line|#define UART_MSR_RI_MSK (0x40)
DECL|macro|UART_MSR_RI_OFST
mdefine_line|#define UART_MSR_RI_OFST (6)
DECL|macro|UART_MSR_DSR_MSK
mdefine_line|#define UART_MSR_DSR_MSK (0x20)
DECL|macro|UART_MSR_DSR_OFST
mdefine_line|#define UART_MSR_DSR_OFST (5)
DECL|macro|UART_MSR_CTS_MSK
mdefine_line|#define UART_MSR_CTS_MSK (0x10)
DECL|macro|UART_MSR_CTS_OFST
mdefine_line|#define UART_MSR_CTS_OFST (4)
DECL|macro|UART_MSR_DDCD_MSK
mdefine_line|#define UART_MSR_DDCD_MSK (0x08)
DECL|macro|UART_MSR_DDCD_OFST
mdefine_line|#define UART_MSR_DDCD_OFST (3)
DECL|macro|UART_MSR_TERI_MSK
mdefine_line|#define UART_MSR_TERI_MSK (0x04)
DECL|macro|UART_MSR_TERI_OFST
mdefine_line|#define UART_MSR_TERI_OFST (2)
DECL|macro|UART_MSR_DDSR_MSK
mdefine_line|#define UART_MSR_DDSR_MSK (0x02)
DECL|macro|UART_MSR_DDSR_OFST
mdefine_line|#define UART_MSR_DDSR_OFST (1)
DECL|macro|UART_MSR_DCTS_MSK
mdefine_line|#define UART_MSR_DCTS_MSK (0x01)
DECL|macro|UART_MSR_DCTS_OFST
mdefine_line|#define UART_MSR_DCTS_OFST (0)
DECL|macro|UART_DIV_LO
mdefine_line|#define UART_DIV_LO(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x34 ))
DECL|macro|UART_DIV_LO_DIV_MSK
mdefine_line|#define UART_DIV_LO_DIV_MSK (0xff)
DECL|macro|UART_DIV_LO_DIV_OFST
mdefine_line|#define UART_DIV_LO_DIV_OFST (0)
DECL|macro|UART_DIV_HI
mdefine_line|#define UART_DIV_HI(BASE_ADDR) (UART00_TYPE (BASE_ADDR  + 0x38 ))
DECL|macro|UART_DIV_HI_DIV_MSK
mdefine_line|#define UART_DIV_HI_DIV_MSK (0xff)
DECL|macro|UART_DIV_HI_DIV_OFST
mdefine_line|#define UART_DIV_HI_DIV_OFST (0)
macro_line|#endif /* __UART00_H */
eof
