multiline_comment|/*&n; *  &n; *  This file contains the register definitions for the Excalibur&n; *  Timer TIMER00.&n; *&n; *  Copyright (C) 2001 Altera Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __INT_CTRL00_H
DECL|macro|__INT_CTRL00_H
mdefine_line|#define __INT_CTRL00_H
DECL|macro|INT_MS
mdefine_line|#define INT_MS(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x00 ))
DECL|macro|INT_MS_FC_MSK
mdefine_line|#define INT_MS_FC_MSK (0x10000)
DECL|macro|INT_MS_FC_OFST
mdefine_line|#define INT_MS_FC_OFST (16)
DECL|macro|INT_MS_M1_MSK
mdefine_line|#define INT_MS_M1_MSK (0x8000)
DECL|macro|INT_MS_M1_OFST
mdefine_line|#define INT_MS_M1_OFST (15)
DECL|macro|INT_MS_M0_MSK
mdefine_line|#define INT_MS_M0_MSK (0x4000)
DECL|macro|INT_MS_M0_OFST
mdefine_line|#define INT_MS_M0_OFST (14)
DECL|macro|INT_MS_AE_MSK
mdefine_line|#define INT_MS_AE_MSK (0x2000)
DECL|macro|INT_MS_AE_OFST
mdefine_line|#define INT_MS_AE_OFST (13)
DECL|macro|INT_MS_PE_MSK
mdefine_line|#define INT_MS_PE_MSK (0x1000)
DECL|macro|INT_MS_PE_OFST
mdefine_line|#define INT_MS_PE_OFST (12)
DECL|macro|INT_MS_EE_MSK
mdefine_line|#define INT_MS_EE_MSK (0x0800)
DECL|macro|INT_MS_EE_OFST
mdefine_line|#define INT_MS_EE_OFST (11)
DECL|macro|INT_MS_PS_MSK
mdefine_line|#define INT_MS_PS_MSK (0x0400)
DECL|macro|INT_MS_PS_OFST
mdefine_line|#define INT_MS_PS_OFST (10)
DECL|macro|INT_MS_T1_MSK
mdefine_line|#define INT_MS_T1_MSK (0x0200)
DECL|macro|INT_MS_T1_OFST
mdefine_line|#define INT_MS_T1_OFST (9)
DECL|macro|INT_MS_T0_MSK
mdefine_line|#define INT_MS_T0_MSK (0x0100)
DECL|macro|INT_MS_T0_OFST
mdefine_line|#define INT_MS_T0_OFST (8)
DECL|macro|INT_MS_UA_MSK
mdefine_line|#define INT_MS_UA_MSK (0x0080)
DECL|macro|INT_MS_UA_OFST
mdefine_line|#define INT_MS_UA_OFST (7)
DECL|macro|INT_MS_IP_MSK
mdefine_line|#define INT_MS_IP_MSK (0x0040)
DECL|macro|INT_MS_IP_OFST
mdefine_line|#define INT_MS_IP_OFST (6)
DECL|macro|INT_MS_P5_MSK
mdefine_line|#define INT_MS_P5_MSK (0x0020)
DECL|macro|INT_MS_P5_OFST
mdefine_line|#define INT_MS_P5_OFST (5)
DECL|macro|INT_MS_P4_MSK
mdefine_line|#define INT_MS_P4_MSK (0x0010)
DECL|macro|INT_MS_P4_OFST
mdefine_line|#define INT_MS_P4_OFST (4)
DECL|macro|INT_MS_P3_MSK
mdefine_line|#define INT_MS_P3_MSK (0x0008)
DECL|macro|INT_MS_P3_OFST
mdefine_line|#define INT_MS_P3_OFST (3)
DECL|macro|INT_MS_P2_MSK
mdefine_line|#define INT_MS_P2_MSK (0x0004)
DECL|macro|INT_MS_P2_OFST
mdefine_line|#define INT_MS_P2_OFST (2)
DECL|macro|INT_MS_P1_MSK
mdefine_line|#define INT_MS_P1_MSK (0x0002)
DECL|macro|INT_MS_P1_OFST
mdefine_line|#define INT_MS_P1_OFST (1)
DECL|macro|INT_MS_P0_MSK
mdefine_line|#define INT_MS_P0_MSK (0x0001)
DECL|macro|INT_MS_P0_OFST
mdefine_line|#define INT_MS_P0_OFST (0)
DECL|macro|INT_MC
mdefine_line|#define INT_MC(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x04 ))
DECL|macro|INT_MC_FC_MSK
mdefine_line|#define INT_MC_FC_MSK (0x10000)
DECL|macro|INT_MC_FC_OFST
mdefine_line|#define INT_MC_FC_OFST (16)
DECL|macro|INT_MC_M1_MSK
mdefine_line|#define INT_MC_M1_MSK (0x8000)
DECL|macro|INT_MC_M1_OFST
mdefine_line|#define INT_MC_M1_OFST (15)
DECL|macro|INT_MC_M0_MSK
mdefine_line|#define INT_MC_M0_MSK (0x4000)
DECL|macro|INT_MC_M0_OFST
mdefine_line|#define INT_MC_M0_OFST (14)
DECL|macro|INT_MC_AE_MSK
mdefine_line|#define INT_MC_AE_MSK (0x2000)
DECL|macro|INT_MC_AE_OFST
mdefine_line|#define INT_MC_AE_OFST (13)
DECL|macro|INT_MC_PE_MSK
mdefine_line|#define INT_MC_PE_MSK (0x1000)
DECL|macro|INT_MC_PE_OFST
mdefine_line|#define INT_MC_PE_OFST (12)
DECL|macro|INT_MC_EE_MSK
mdefine_line|#define INT_MC_EE_MSK (0x0800)
DECL|macro|INT_MC_EE_OFST
mdefine_line|#define INT_MC_EE_OFST (11)
DECL|macro|INT_MC_PS_MSK
mdefine_line|#define INT_MC_PS_MSK (0x0400)
DECL|macro|INT_MC_PS_OFST
mdefine_line|#define INT_MC_PS_OFST (10)
DECL|macro|INT_MC_T1_MSK
mdefine_line|#define INT_MC_T1_MSK (0x0200)
DECL|macro|INT_MC_T1_OFST
mdefine_line|#define INT_MC_T1_OFST (9)
DECL|macro|INT_MC_T0_MSK
mdefine_line|#define INT_MC_T0_MSK (0x0100)
DECL|macro|INT_MC_T0_OFST
mdefine_line|#define INT_MC_T0_OFST (8)
DECL|macro|INT_MC_UA_MSK
mdefine_line|#define INT_MC_UA_MSK (0x0080)
DECL|macro|INT_MC_UA_OFST
mdefine_line|#define INT_MC_UA_OFST (7)
DECL|macro|INT_MC_IP_MSK
mdefine_line|#define INT_MC_IP_MSK (0x0040)
DECL|macro|INT_MC_IP_OFST
mdefine_line|#define INT_MC_IP_OFST (6)
DECL|macro|INT_MC_P5_MSK
mdefine_line|#define INT_MC_P5_MSK (0x0020)
DECL|macro|INT_MC_P5_OFST
mdefine_line|#define INT_MC_P5_OFST (5)
DECL|macro|INT_MC_P4_MSK
mdefine_line|#define INT_MC_P4_MSK (0x0010)
DECL|macro|INT_MC_P4_OFST
mdefine_line|#define INT_MC_P4_OFST (4)
DECL|macro|INT_MC_P3_MSK
mdefine_line|#define INT_MC_P3_MSK (0x0008)
DECL|macro|INT_MC_P3_OFST
mdefine_line|#define INT_MC_P3_OFST (3)
DECL|macro|INT_MC_P2_MSK
mdefine_line|#define INT_MC_P2_MSK (0x0004)
DECL|macro|INT_MC_P2_OFST
mdefine_line|#define INT_MC_P2_OFST (2)
DECL|macro|INT_MC_P1_MSK
mdefine_line|#define INT_MC_P1_MSK (0x0002)
DECL|macro|INT_MC_P1_OFST
mdefine_line|#define INT_MC_P1_OFST (1)
DECL|macro|INT_MC_P0_MSK
mdefine_line|#define INT_MC_P0_MSK (0x0001)
DECL|macro|INT_MC_P0_OFST
mdefine_line|#define INT_MC_P0_OFST (0)
DECL|macro|INT_SS
mdefine_line|#define INT_SS(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x08 ))
DECL|macro|INT_SS_FC_SSK
mdefine_line|#define INT_SS_FC_SSK (0x8000)
DECL|macro|INT_SS_FC_OFST
mdefine_line|#define INT_SS_FC_OFST (15)
DECL|macro|INT_SS_M1_SSK
mdefine_line|#define INT_SS_M1_SSK (0x8000)
DECL|macro|INT_SS_M1_OFST
mdefine_line|#define INT_SS_M1_OFST (15)
DECL|macro|INT_SS_M0_SSK
mdefine_line|#define INT_SS_M0_SSK (0x4000)
DECL|macro|INT_SS_M0_OFST
mdefine_line|#define INT_SS_M0_OFST (14)
DECL|macro|INT_SS_AE_SSK
mdefine_line|#define INT_SS_AE_SSK (0x2000)
DECL|macro|INT_SS_AE_OFST
mdefine_line|#define INT_SS_AE_OFST (13)
DECL|macro|INT_SS_PE_SSK
mdefine_line|#define INT_SS_PE_SSK (0x1000)
DECL|macro|INT_SS_PE_OFST
mdefine_line|#define INT_SS_PE_OFST (12)
DECL|macro|INT_SS_EE_SSK
mdefine_line|#define INT_SS_EE_SSK (0x0800)
DECL|macro|INT_SS_EE_OFST
mdefine_line|#define INT_SS_EE_OFST (11)
DECL|macro|INT_SS_PS_SSK
mdefine_line|#define INT_SS_PS_SSK (0x0400)
DECL|macro|INT_SS_PS_OFST
mdefine_line|#define INT_SS_PS_OFST (10)
DECL|macro|INT_SS_T1_SSK
mdefine_line|#define INT_SS_T1_SSK (0x0200)
DECL|macro|INT_SS_T1_OFST
mdefine_line|#define INT_SS_T1_OFST (9)
DECL|macro|INT_SS_T0_SSK
mdefine_line|#define INT_SS_T0_SSK (0x0100)
DECL|macro|INT_SS_T0_OFST
mdefine_line|#define INT_SS_T0_OFST (8)
DECL|macro|INT_SS_UA_SSK
mdefine_line|#define INT_SS_UA_SSK (0x0080)
DECL|macro|INT_SS_UA_OFST
mdefine_line|#define INT_SS_UA_OFST (7)
DECL|macro|INT_SS_IP_SSK
mdefine_line|#define INT_SS_IP_SSK (0x0040)
DECL|macro|INT_SS_IP_OFST
mdefine_line|#define INT_SS_IP_OFST (6)
DECL|macro|INT_SS_P5_SSK
mdefine_line|#define INT_SS_P5_SSK (0x0020)
DECL|macro|INT_SS_P5_OFST
mdefine_line|#define INT_SS_P5_OFST (5)
DECL|macro|INT_SS_P4_SSK
mdefine_line|#define INT_SS_P4_SSK (0x0010)
DECL|macro|INT_SS_P4_OFST
mdefine_line|#define INT_SS_P4_OFST (4)
DECL|macro|INT_SS_P3_SSK
mdefine_line|#define INT_SS_P3_SSK (0x0008)
DECL|macro|INT_SS_P3_OFST
mdefine_line|#define INT_SS_P3_OFST (3)
DECL|macro|INT_SS_P2_SSK
mdefine_line|#define INT_SS_P2_SSK (0x0004)
DECL|macro|INT_SS_P2_OFST
mdefine_line|#define INT_SS_P2_OFST (2)
DECL|macro|INT_SS_P1_SSK
mdefine_line|#define INT_SS_P1_SSK (0x0002)
DECL|macro|INT_SS_P1_OFST
mdefine_line|#define INT_SS_P1_OFST (1)
DECL|macro|INT_SS_P0_SSK
mdefine_line|#define INT_SS_P0_SSK (0x0001)
DECL|macro|INT_SS_P0_OFST
mdefine_line|#define INT_SS_P0_OFST (0)
DECL|macro|INT_RS
mdefine_line|#define INT_RS(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x0C ))
DECL|macro|INT_RS_FC_RSK
mdefine_line|#define INT_RS_FC_RSK (0x10000)
DECL|macro|INT_RS_FC_OFST
mdefine_line|#define INT_RS_FC_OFST (16)
DECL|macro|INT_RS_M1_RSK
mdefine_line|#define INT_RS_M1_RSK (0x8000)
DECL|macro|INT_RS_M1_OFST
mdefine_line|#define INT_RS_M1_OFST (15)
DECL|macro|INT_RS_M0_RSK
mdefine_line|#define INT_RS_M0_RSK (0x4000)
DECL|macro|INT_RS_M0_OFST
mdefine_line|#define INT_RS_M0_OFST (14)
DECL|macro|INT_RS_AE_RSK
mdefine_line|#define INT_RS_AE_RSK (0x2000)
DECL|macro|INT_RS_AE_OFST
mdefine_line|#define INT_RS_AE_OFST (13)
DECL|macro|INT_RS_PE_RSK
mdefine_line|#define INT_RS_PE_RSK (0x1000)
DECL|macro|INT_RS_PE_OFST
mdefine_line|#define INT_RS_PE_OFST (12)
DECL|macro|INT_RS_EE_RSK
mdefine_line|#define INT_RS_EE_RSK (0x0800)
DECL|macro|INT_RS_EE_OFST
mdefine_line|#define INT_RS_EE_OFST (11)
DECL|macro|INT_RS_PS_RSK
mdefine_line|#define INT_RS_PS_RSK (0x0400)
DECL|macro|INT_RS_PS_OFST
mdefine_line|#define INT_RS_PS_OFST (10)
DECL|macro|INT_RS_T1_RSK
mdefine_line|#define INT_RS_T1_RSK (0x0200)
DECL|macro|INT_RS_T1_OFST
mdefine_line|#define INT_RS_T1_OFST (9)
DECL|macro|INT_RS_T0_RSK
mdefine_line|#define INT_RS_T0_RSK (0x0100)
DECL|macro|INT_RS_T0_OFST
mdefine_line|#define INT_RS_T0_OFST (8)
DECL|macro|INT_RS_UA_RSK
mdefine_line|#define INT_RS_UA_RSK (0x0080)
DECL|macro|INT_RS_UA_OFST
mdefine_line|#define INT_RS_UA_OFST (7)
DECL|macro|INT_RS_IP_RSK
mdefine_line|#define INT_RS_IP_RSK (0x0040)
DECL|macro|INT_RS_IP_OFST
mdefine_line|#define INT_RS_IP_OFST (6)
DECL|macro|INT_RS_P5_RSK
mdefine_line|#define INT_RS_P5_RSK (0x0020)
DECL|macro|INT_RS_P5_OFST
mdefine_line|#define INT_RS_P5_OFST (5)
DECL|macro|INT_RS_P4_RSK
mdefine_line|#define INT_RS_P4_RSK (0x0010)
DECL|macro|INT_RS_P4_OFST
mdefine_line|#define INT_RS_P4_OFST (4)
DECL|macro|INT_RS_P3_RSK
mdefine_line|#define INT_RS_P3_RSK (0x0008)
DECL|macro|INT_RS_P3_OFST
mdefine_line|#define INT_RS_P3_OFST (3)
DECL|macro|INT_RS_P2_RSK
mdefine_line|#define INT_RS_P2_RSK (0x0004)
DECL|macro|INT_RS_P2_OFST
mdefine_line|#define INT_RS_P2_OFST (2)
DECL|macro|INT_RS_P1_RSK
mdefine_line|#define INT_RS_P1_RSK (0x0002)
DECL|macro|INT_RS_P1_OFST
mdefine_line|#define INT_RS_P1_OFST (1)
DECL|macro|INT_RS_P0_RSK
mdefine_line|#define INT_RS_P0_RSK (0x0001)
DECL|macro|INT_RS_P0_OFST
mdefine_line|#define INT_RS_P0_OFST (0)
DECL|macro|INT_ID
mdefine_line|#define INT_ID(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x10 ))
DECL|macro|INT_ID_ID_MSK
mdefine_line|#define INT_ID_ID_MSK (0x3F)
DECL|macro|INT_ID_ID_OFST
mdefine_line|#define INT_ID_ID_OFST (0)
DECL|macro|INT_PLD_PRIORITY
mdefine_line|#define INT_PLD_PRIORITY(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x14 ))
DECL|macro|INT_PLD_PRIORITY_PRI_MSK
mdefine_line|#define INT_PLD_PRIORITY_PRI_MSK (0x3F)
DECL|macro|INT_PLD_PRIORITY_PRI_OFST
mdefine_line|#define INT_PLD_PRIORITY_PRI_OFST (0)
DECL|macro|INT_PLD_PRIORITY_GA_MSK
mdefine_line|#define INT_PLD_PRIORITY_GA_MSK (0x40)
DECL|macro|INT_PLD_PRIORITY_GA_OFST
mdefine_line|#define INT_PLD_PRIORITY_GA_OFST (6)
DECL|macro|INT_MODE
mdefine_line|#define INT_MODE(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x18 ))
DECL|macro|INT_MODE_MODE_MSK
mdefine_line|#define INT_MODE_MODE_MSK (0x3)
DECL|macro|INT_MODE_MODE_OFST
mdefine_line|#define INT_MODE_MODE_OFST (0)
DECL|macro|INT_PRIORITY_P0
mdefine_line|#define INT_PRIORITY_P0(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x80 ))
DECL|macro|INT_PRIORITY_P0_PRI_MSK
mdefine_line|#define INT_PRIORITY_P0_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_P0_PRI_OFST
mdefine_line|#define INT_PRIORITY_P0_PRI_OFST (0)
DECL|macro|INT_PRIORITY_P0_FQ_MSK
mdefine_line|#define INT_PRIORITY_P0_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_P0_FQ_OFST
mdefine_line|#define INT_PRIORITY_P0_FQ_OFST (6)
DECL|macro|INT_PRIORITY_P1
mdefine_line|#define INT_PRIORITY_P1(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x84 ))
DECL|macro|INT_PRIORITY_P1_PRI_MSK
mdefine_line|#define INT_PRIORITY_P1_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_P1_PRI_OFST
mdefine_line|#define INT_PRIORITY_P1_PRI_OFST (0)
DECL|macro|INT_PRIORITY_P1_FQ_MSK
mdefine_line|#define INT_PRIORITY_P1_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_P1_FQ_OFST
mdefine_line|#define INT_PRIORITY_P1_FQ_OFST (6)
DECL|macro|INT_PRIORITY_P2
mdefine_line|#define INT_PRIORITY_P2(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x88 ))
DECL|macro|INT_PRIORITY_P2_PRI_MSK
mdefine_line|#define INT_PRIORITY_P2_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_P2_PRI_OFST
mdefine_line|#define INT_PRIORITY_P2_PRI_OFST (0)
DECL|macro|INT_PRIORITY_P2_FQ_MSK
mdefine_line|#define INT_PRIORITY_P2_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_P2_FQ_OFST
mdefine_line|#define INT_PRIORITY_P2_FQ_OFST (6)
DECL|macro|INT_PRIORITY_P3
mdefine_line|#define INT_PRIORITY_P3(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x8C ))
DECL|macro|INT_PRIORITY_P3_PRI_MSK
mdefine_line|#define INT_PRIORITY_P3_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_P3_PRI_OFST
mdefine_line|#define INT_PRIORITY_P3_PRI_OFST (0)
DECL|macro|INT_PRIORITY_P3_FQ_MSK
mdefine_line|#define INT_PRIORITY_P3_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_P3_FQ_OFST
mdefine_line|#define INT_PRIORITY_P3_FQ_OFST (6)
DECL|macro|INT_PRIORITY_P4
mdefine_line|#define INT_PRIORITY_P4(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x90 ))
DECL|macro|INT_PRIORITY_P4_PRI_MSK
mdefine_line|#define INT_PRIORITY_P4_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_P4_PRI_OFST
mdefine_line|#define INT_PRIORITY_P4_PRI_OFST (0)
DECL|macro|INT_PRIORITY_P4_FQ_MSK
mdefine_line|#define INT_PRIORITY_P4_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_P4_FQ_OFST
mdefine_line|#define INT_PRIORITY_P4_FQ_OFST (6)
DECL|macro|INT_PRIORITY_P5
mdefine_line|#define INT_PRIORITY_P5(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x94 ))
DECL|macro|INT_PRIORITY_P5_PRI_MSK
mdefine_line|#define INT_PRIORITY_P5_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_P5_PRI_OFST
mdefine_line|#define INT_PRIORITY_P5_PRI_OFST (0)
DECL|macro|INT_PRIORITY_P5_FQ_MSK
mdefine_line|#define INT_PRIORITY_P5_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_P5_FQ_OFST
mdefine_line|#define INT_PRIORITY_P5_FQ_OFST (6)
DECL|macro|INT_PRIORITY_IP
mdefine_line|#define INT_PRIORITY_IP(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x94 ))
DECL|macro|INT_PRIORITY_IP_PRI_MSK
mdefine_line|#define INT_PRIORITY_IP_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_IP_PRI_OFST
mdefine_line|#define INT_PRIORITY_IP_PRI_OFST (0)
DECL|macro|INT_PRIORITY_IP_FQ_MSK
mdefine_line|#define INT_PRIORITY_IP_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_IP_FQ_OFST
mdefine_line|#define INT_PRIORITY_IP_FQ_OFST (6)
DECL|macro|INT_PRIORITY_UA
mdefine_line|#define INT_PRIORITY_UA(base_addr) (INT_CTRL00_TYPE (base_addr  + 0x9C ))
DECL|macro|INT_PRIORITY_UA_PRI_MSK
mdefine_line|#define INT_PRIORITY_UA_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_UA_PRI_OFST
mdefine_line|#define INT_PRIORITY_UA_PRI_OFST (0)
DECL|macro|INT_PRIORITY_UA_FQ_MSK
mdefine_line|#define INT_PRIORITY_UA_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_UA_FQ_OFST
mdefine_line|#define INT_PRIORITY_UA_FQ_OFST (6)
DECL|macro|INT_PRIORITY_T0
mdefine_line|#define INT_PRIORITY_T0(base_addr) (INT_CTRL00_TYPE (base_addr  + 0xA0 ))
DECL|macro|INT_PRIORITY_T0_PRI_MSK
mdefine_line|#define INT_PRIORITY_T0_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_T0_PRI_OFST
mdefine_line|#define INT_PRIORITY_T0_PRI_OFST (0)
DECL|macro|INT_PRIORITY_T0_FQ_MSK
mdefine_line|#define INT_PRIORITY_T0_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_T0_FQ_OFST
mdefine_line|#define INT_PRIORITY_T0_FQ_OFST (6)
DECL|macro|INT_PRIORITY_T1
mdefine_line|#define INT_PRIORITY_T1(base_addr) (INT_CTRL00_TYPE (base_addr  + 0xA4 ))
DECL|macro|INT_PRIORITY_T1_PRI_MSK
mdefine_line|#define INT_PRIORITY_T1_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_T1_PRI_OFST
mdefine_line|#define INT_PRIORITY_T1_PRI_OFST (0)
DECL|macro|INT_PRIORITY_T1_FQ_MSK
mdefine_line|#define INT_PRIORITY_T1_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_T1_FQ_OFST
mdefine_line|#define INT_PRIORITY_T1_FQ_OFST (6)
DECL|macro|INT_PRIORITY_PS
mdefine_line|#define INT_PRIORITY_PS(base_addr) (INT_CTRL00_TYPE (base_addr  + 0xA8 ))
DECL|macro|INT_PRIORITY_PS_PRI_MSK
mdefine_line|#define INT_PRIORITY_PS_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_PS_PRI_OFST
mdefine_line|#define INT_PRIORITY_PS_PRI_OFST (0)
DECL|macro|INT_PRIORITY_PS_FQ_MSK
mdefine_line|#define INT_PRIORITY_PS_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_PS_FQ_OFST
mdefine_line|#define INT_PRIORITY_PS_FQ_OFST (6)
DECL|macro|INT_PRIORITY_EE
mdefine_line|#define INT_PRIORITY_EE(base_addr) (INT_CTRL00_TYPE (base_addr  + 0xAC ))
DECL|macro|INT_PRIORITY_EE_PRI_MSK
mdefine_line|#define INT_PRIORITY_EE_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_EE_PRI_OFST
mdefine_line|#define INT_PRIORITY_EE_PRI_OFST (0)
DECL|macro|INT_PRIORITY_EE_FQ_MSK
mdefine_line|#define INT_PRIORITY_EE_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_EE_FQ_OFST
mdefine_line|#define INT_PRIORITY_EE_FQ_OFST (6)
DECL|macro|INT_PRIORITY_PE
mdefine_line|#define INT_PRIORITY_PE(base_addr) (INT_CTRL00_TYPE (base_addr  + 0xB0 ))
DECL|macro|INT_PRIORITY_PE_PRI_MSK
mdefine_line|#define INT_PRIORITY_PE_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_PE_PRI_OFST
mdefine_line|#define INT_PRIORITY_PE_PRI_OFST (0)
DECL|macro|INT_PRIORITY_PE_FQ_MSK
mdefine_line|#define INT_PRIORITY_PE_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_PE_FQ_OFST
mdefine_line|#define INT_PRIORITY_PE_FQ_OFST (6)
DECL|macro|INT_PRIORITY_AE
mdefine_line|#define INT_PRIORITY_AE(base_addr) (INT_CTRL00_TYPE (base_addr  + 0xB4 ))
DECL|macro|INT_PRIORITY_AE_PRI_MSK
mdefine_line|#define INT_PRIORITY_AE_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_AE_PRI_OFST
mdefine_line|#define INT_PRIORITY_AE_PRI_OFST (0)
DECL|macro|INT_PRIORITY_AE_FQ_MSK
mdefine_line|#define INT_PRIORITY_AE_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_AE_FQ_OFST
mdefine_line|#define INT_PRIORITY_AE_FQ_OFST (6)
DECL|macro|INT_PRIORITY_M0
mdefine_line|#define INT_PRIORITY_M0(base_addr) (INT_CTRL00_TYPE (base_addr  + 0xB8 ))
DECL|macro|INT_PRIORITY_M0_PRI_MSK
mdefine_line|#define INT_PRIORITY_M0_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_M0_PRI_OFST
mdefine_line|#define INT_PRIORITY_M0_PRI_OFST (0)
DECL|macro|INT_PRIORITY_M0_FQ_MSK
mdefine_line|#define INT_PRIORITY_M0_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_M0_FQ_OFST
mdefine_line|#define INT_PRIORITY_M0_FQ_OFST (6)
DECL|macro|INT_PRIORITY_M1
mdefine_line|#define INT_PRIORITY_M1(base_addr) (INT_CTRL00_TYPE (base_addr  + 0xBC ))
DECL|macro|INT_PRIORITY_M1_PRI_MSK
mdefine_line|#define INT_PRIORITY_M1_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_M1_PRI_OFST
mdefine_line|#define INT_PRIORITY_M1_PRI_OFST (0)
DECL|macro|INT_PRIORITY_M1_FQ_MSK
mdefine_line|#define INT_PRIORITY_M1_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_M1_FQ_OFST
mdefine_line|#define INT_PRIORITY_M1_FQ_OFST (6)
DECL|macro|INT_PRIORITY_FC
mdefine_line|#define INT_PRIORITY_FC(base_addr) (INT_CTRL00_TYPE (base_addr  + 0xC0 ))
DECL|macro|INT_PRIORITY_FC_PRI_MSK
mdefine_line|#define INT_PRIORITY_FC_PRI_MSK (0x3F)
DECL|macro|INT_PRIORITY_FC_PRI_OFST
mdefine_line|#define INT_PRIORITY_FC_PRI_OFST (0)
DECL|macro|INT_PRIORITY_FC_FQ_MSK
mdefine_line|#define INT_PRIORITY_FC_FQ_MSK (0x40)
DECL|macro|INT_PRIORITY_FC_FQ_OFST
mdefine_line|#define INT_PRIORITY_FC_FQ_OFST (6)
macro_line|#endif /* __INT_CTRL00_H */
eof
