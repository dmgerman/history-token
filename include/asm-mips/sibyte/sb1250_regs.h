multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  Register Definitions                     File: sb1250_regs.h&n;    *  &n;    *  This module contains the addresses of the on-chip peripherals&n;    *  on the SB1250.&n;    *  &n;    *  SB1250 specification level:  01/02/2002&n;    *  &n;    *  Author:  Mitch Lichtenberg (mpl@broadcom.com)&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_REGS_H
DECL|macro|_SB1250_REGS_H
mdefine_line|#define _SB1250_REGS_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/*  *********************************************************************&n;    *  Some general notes:&n;    *  &n;    *  For the most part, when there is more than one peripheral&n;    *  of the same type on the SOC, the constants below will be&n;    *  offsets from the base of each peripheral.  For example,&n;    *  the MAC registers are described as offsets from the first&n;    *  MAC register, and there will be a MAC_REGISTER() macro&n;    *  to calculate the base address of a given MAC.  &n;    *  &n;    *  The information in this file is based on the SB1250 SOC&n;    *  manual version 0.2, July 2000.&n;    ********************************************************************* */
multiline_comment|/*  ********************************************************************* &n;    * Memory Controller Registers&n;    ********************************************************************* */
multiline_comment|/*&n; * XXX: can&squot;t remove MC base 0 if 112x, since it&squot;s used by other macros,&n; * since there is one reg there (but it could get its addr/offset constant).&n; */
DECL|macro|A_MC_BASE_0
mdefine_line|#define A_MC_BASE_0                 0x0010051000
DECL|macro|A_MC_BASE_1
mdefine_line|#define A_MC_BASE_1                 0x0010052000
DECL|macro|MC_REGISTER_SPACING
mdefine_line|#define MC_REGISTER_SPACING         0x1000
DECL|macro|A_MC_BASE
mdefine_line|#define A_MC_BASE(ctlid)            ((ctlid)*MC_REGISTER_SPACING+A_MC_BASE_0)
DECL|macro|A_MC_REGISTER
mdefine_line|#define A_MC_REGISTER(ctlid,reg)    (A_MC_BASE(ctlid)+(reg))
DECL|macro|R_MC_CONFIG
mdefine_line|#define R_MC_CONFIG                 0x0000000100
DECL|macro|R_MC_DRAMCMD
mdefine_line|#define R_MC_DRAMCMD                0x0000000120
DECL|macro|R_MC_DRAMMODE
mdefine_line|#define R_MC_DRAMMODE               0x0000000140
DECL|macro|R_MC_TIMING1
mdefine_line|#define R_MC_TIMING1                0x0000000160
DECL|macro|R_MC_TIMING2
mdefine_line|#define R_MC_TIMING2                0x0000000180
DECL|macro|R_MC_CS_START
mdefine_line|#define R_MC_CS_START               0x00000001A0
DECL|macro|R_MC_CS_END
mdefine_line|#define R_MC_CS_END                 0x00000001C0
DECL|macro|R_MC_CS_INTERLEAVE
mdefine_line|#define R_MC_CS_INTERLEAVE          0x00000001E0
DECL|macro|S_MC_CS_STARTEND
mdefine_line|#define S_MC_CS_STARTEND            16
DECL|macro|R_MC_CSX_BASE
mdefine_line|#define R_MC_CSX_BASE               0x0000000200
DECL|macro|R_MC_CSX_ROW
mdefine_line|#define R_MC_CSX_ROW                0x0000000000&t;/* relative to CSX_BASE, above */
DECL|macro|R_MC_CSX_COL
mdefine_line|#define R_MC_CSX_COL                0x0000000020&t;/* relative to CSX_BASE, above */
DECL|macro|R_MC_CSX_BA
mdefine_line|#define R_MC_CSX_BA                 0x0000000040&t;/* relative to CSX_BASE, above */
DECL|macro|MC_CSX_SPACING
mdefine_line|#define MC_CSX_SPACING              0x0000000060&t;/* relative to CSX_BASE, above */
DECL|macro|R_MC_CS0_ROW
mdefine_line|#define R_MC_CS0_ROW                0x0000000200
DECL|macro|R_MC_CS0_COL
mdefine_line|#define R_MC_CS0_COL                0x0000000220
DECL|macro|R_MC_CS0_BA
mdefine_line|#define R_MC_CS0_BA                 0x0000000240
DECL|macro|R_MC_CS1_ROW
mdefine_line|#define R_MC_CS1_ROW                0x0000000260
DECL|macro|R_MC_CS1_COL
mdefine_line|#define R_MC_CS1_COL                0x0000000280
DECL|macro|R_MC_CS1_BA
mdefine_line|#define R_MC_CS1_BA                 0x00000002A0
DECL|macro|R_MC_CS2_ROW
mdefine_line|#define R_MC_CS2_ROW                0x00000002C0
DECL|macro|R_MC_CS2_COL
mdefine_line|#define R_MC_CS2_COL                0x00000002E0
DECL|macro|R_MC_CS2_BA
mdefine_line|#define R_MC_CS2_BA                 0x0000000300
DECL|macro|R_MC_CS3_ROW
mdefine_line|#define R_MC_CS3_ROW                0x0000000320
DECL|macro|R_MC_CS3_COL
mdefine_line|#define R_MC_CS3_COL                0x0000000340
DECL|macro|R_MC_CS3_BA
mdefine_line|#define R_MC_CS3_BA                 0x0000000360
DECL|macro|R_MC_CS_ATTR
mdefine_line|#define R_MC_CS_ATTR                0x0000000380
DECL|macro|R_MC_TEST_DATA
mdefine_line|#define R_MC_TEST_DATA              0x0000000400
DECL|macro|R_MC_TEST_ECC
mdefine_line|#define R_MC_TEST_ECC               0x0000000420
DECL|macro|R_MC_MCLK_CFG
mdefine_line|#define R_MC_MCLK_CFG               0x0000000500
multiline_comment|/*  ********************************************************************* &n;    * L2 Cache Control Registers&n;    ********************************************************************* */
DECL|macro|A_L2_READ_TAG
mdefine_line|#define A_L2_READ_TAG               0x0010040018
DECL|macro|A_L2_ECC_TAG
mdefine_line|#define A_L2_ECC_TAG                0x0010040038
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|A_L2_READ_MISC
mdefine_line|#define A_L2_READ_MISC              0x0010040058
macro_line|#endif /* 112x PASS1 */
DECL|macro|A_L2_WAY_DISABLE
mdefine_line|#define A_L2_WAY_DISABLE            0x0010041000
DECL|macro|A_L2_MAKEDISABLE
mdefine_line|#define A_L2_MAKEDISABLE(x)         (A_L2_WAY_DISABLE | (((~(x))&amp;0x0F) &lt;&lt; 8))
DECL|macro|A_L2_MGMT_TAG_BASE
mdefine_line|#define A_L2_MGMT_TAG_BASE          0x00D0000000
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|A_L2_CACHE_DISABLE
mdefine_line|#define A_L2_CACHE_DISABLE&t;   0x0010042000
DECL|macro|A_L2_MAKECACHEDISABLE
mdefine_line|#define A_L2_MAKECACHEDISABLE(x)   (A_L2_CACHE_DISABLE | (((x)&amp;0x0F) &lt;&lt; 8))
DECL|macro|A_L2_MISC_CONFIG
mdefine_line|#define A_L2_MISC_CONFIG&t;   0x0010043000
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/* Backward-compatibility definitions.  */
multiline_comment|/* XXX: discourage people from using these constants.  */
DECL|macro|A_L2_READ_ADDRESS
mdefine_line|#define A_L2_READ_ADDRESS           A_L2_READ_TAG
DECL|macro|A_L2_EEC_ADDRESS
mdefine_line|#define A_L2_EEC_ADDRESS            A_L2_ECC_TAG
multiline_comment|/*  ********************************************************************* &n;    * PCI Interface Registers&n;    ********************************************************************* */
DECL|macro|A_PCI_TYPE00_HEADER
mdefine_line|#define A_PCI_TYPE00_HEADER         0x00DE000000
DECL|macro|A_PCI_TYPE01_HEADER
mdefine_line|#define A_PCI_TYPE01_HEADER         0x00DE000800
multiline_comment|/*  ********************************************************************* &n;    * Ethernet DMA and MACs&n;    ********************************************************************* */
DECL|macro|A_MAC_BASE_0
mdefine_line|#define A_MAC_BASE_0                0x0010064000
DECL|macro|A_MAC_BASE_1
mdefine_line|#define A_MAC_BASE_1                0x0010065000
macro_line|#if SIBYTE_HDR_FEATURE_CHIP(1250)
DECL|macro|A_MAC_BASE_2
mdefine_line|#define A_MAC_BASE_2                0x0010066000
macro_line|#endif /* 1250 */
DECL|macro|MAC_SPACING
mdefine_line|#define MAC_SPACING                 0x1000
DECL|macro|MAC_DMA_TXRX_SPACING
mdefine_line|#define MAC_DMA_TXRX_SPACING        0x0400
DECL|macro|MAC_DMA_CHANNEL_SPACING
mdefine_line|#define MAC_DMA_CHANNEL_SPACING     0x0100
DECL|macro|DMA_RX
mdefine_line|#define DMA_RX                      0
DECL|macro|DMA_TX
mdefine_line|#define DMA_TX                      1
DECL|macro|MAC_NUM_DMACHAN
mdefine_line|#define MAC_NUM_DMACHAN&t;&t;    2&t;&t;    /* channels per direction */
multiline_comment|/* XXX: not correct; depends on SOC type.  */
DECL|macro|MAC_NUM_PORTS
mdefine_line|#define MAC_NUM_PORTS               3
DECL|macro|A_MAC_CHANNEL_BASE
mdefine_line|#define A_MAC_CHANNEL_BASE(macnum)                  &bslash;&n;            (A_MAC_BASE_0 +                         &bslash;&n;             MAC_SPACING*(macnum))
DECL|macro|A_MAC_REGISTER
mdefine_line|#define A_MAC_REGISTER(macnum,reg)                  &bslash;&n;            (A_MAC_BASE_0 +                         &bslash;&n;             MAC_SPACING*(macnum) + (reg))
DECL|macro|R_MAC_DMA_CHANNELS
mdefine_line|#define R_MAC_DMA_CHANNELS&t;&t;0x800 /* Relative to A_MAC_CHANNEL_BASE */
DECL|macro|A_MAC_DMA_CHANNEL_BASE
mdefine_line|#define A_MAC_DMA_CHANNEL_BASE(macnum,txrx,chan)    &bslash;&n;             ((A_MAC_CHANNEL_BASE(macnum)) +        &bslash;&n;             R_MAC_DMA_CHANNELS +                   &bslash;&n;             (MAC_DMA_TXRX_SPACING*(txrx)) +        &bslash;&n;             (MAC_DMA_CHANNEL_SPACING*(chan)))
DECL|macro|R_MAC_DMA_CHANNEL_BASE
mdefine_line|#define R_MAC_DMA_CHANNEL_BASE(txrx,chan)    &bslash;&n;             (R_MAC_DMA_CHANNELS +                   &bslash;&n;             (MAC_DMA_TXRX_SPACING*(txrx)) +        &bslash;&n;             (MAC_DMA_CHANNEL_SPACING*(chan)))
DECL|macro|A_MAC_DMA_REGISTER
mdefine_line|#define A_MAC_DMA_REGISTER(macnum,txrx,chan,reg)           &bslash;&n;            (A_MAC_DMA_CHANNEL_BASE(macnum,txrx,chan) +    &bslash;&n;            (reg))
DECL|macro|R_MAC_DMA_REGISTER
mdefine_line|#define R_MAC_DMA_REGISTER(txrx,chan,reg)           &bslash;&n;            (R_MAC_DMA_CHANNEL_BASE(txrx,chan) +    &bslash;&n;            (reg))
multiline_comment|/* &n; * DMA channel registers, relative to A_MAC_DMA_CHANNEL_BASE&n; */
DECL|macro|R_MAC_DMA_CONFIG0
mdefine_line|#define R_MAC_DMA_CONFIG0               0x00000000
DECL|macro|R_MAC_DMA_CONFIG1
mdefine_line|#define R_MAC_DMA_CONFIG1               0x00000008
DECL|macro|R_MAC_DMA_DSCR_BASE
mdefine_line|#define R_MAC_DMA_DSCR_BASE             0x00000010
DECL|macro|R_MAC_DMA_DSCR_CNT
mdefine_line|#define R_MAC_DMA_DSCR_CNT              0x00000018
DECL|macro|R_MAC_DMA_CUR_DSCRA
mdefine_line|#define R_MAC_DMA_CUR_DSCRA             0x00000020
DECL|macro|R_MAC_DMA_CUR_DSCRB
mdefine_line|#define R_MAC_DMA_CUR_DSCRB             0x00000028
DECL|macro|R_MAC_DMA_CUR_DSCRADDR
mdefine_line|#define R_MAC_DMA_CUR_DSCRADDR          0x00000030
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|R_MAC_DMA_OODPKTLOST_RX
mdefine_line|#define R_MAC_DMA_OODPKTLOST_RX         0x00000038&t;/* rx only */
macro_line|#endif /* 112x PASS1 */
multiline_comment|/*&n; * RMON Counters&n; */
DECL|macro|R_MAC_RMON_TX_BYTES
mdefine_line|#define R_MAC_RMON_TX_BYTES             0x00000000
DECL|macro|R_MAC_RMON_COLLISIONS
mdefine_line|#define R_MAC_RMON_COLLISIONS           0x00000008
DECL|macro|R_MAC_RMON_LATE_COL
mdefine_line|#define R_MAC_RMON_LATE_COL             0x00000010
DECL|macro|R_MAC_RMON_EX_COL
mdefine_line|#define R_MAC_RMON_EX_COL               0x00000018
DECL|macro|R_MAC_RMON_FCS_ERROR
mdefine_line|#define R_MAC_RMON_FCS_ERROR            0x00000020
DECL|macro|R_MAC_RMON_TX_ABORT
mdefine_line|#define R_MAC_RMON_TX_ABORT             0x00000028
multiline_comment|/* Counter #6 (0x30) now reserved */
DECL|macro|R_MAC_RMON_TX_BAD
mdefine_line|#define R_MAC_RMON_TX_BAD               0x00000038
DECL|macro|R_MAC_RMON_TX_GOOD
mdefine_line|#define R_MAC_RMON_TX_GOOD              0x00000040
DECL|macro|R_MAC_RMON_TX_RUNT
mdefine_line|#define R_MAC_RMON_TX_RUNT              0x00000048
DECL|macro|R_MAC_RMON_TX_OVERSIZE
mdefine_line|#define R_MAC_RMON_TX_OVERSIZE          0x00000050
DECL|macro|R_MAC_RMON_RX_BYTES
mdefine_line|#define R_MAC_RMON_RX_BYTES             0x00000080
DECL|macro|R_MAC_RMON_RX_MCAST
mdefine_line|#define R_MAC_RMON_RX_MCAST             0x00000088
DECL|macro|R_MAC_RMON_RX_BCAST
mdefine_line|#define R_MAC_RMON_RX_BCAST             0x00000090
DECL|macro|R_MAC_RMON_RX_BAD
mdefine_line|#define R_MAC_RMON_RX_BAD               0x00000098
DECL|macro|R_MAC_RMON_RX_GOOD
mdefine_line|#define R_MAC_RMON_RX_GOOD              0x000000A0
DECL|macro|R_MAC_RMON_RX_RUNT
mdefine_line|#define R_MAC_RMON_RX_RUNT              0x000000A8
DECL|macro|R_MAC_RMON_RX_OVERSIZE
mdefine_line|#define R_MAC_RMON_RX_OVERSIZE          0x000000B0
DECL|macro|R_MAC_RMON_RX_FCS_ERROR
mdefine_line|#define R_MAC_RMON_RX_FCS_ERROR         0x000000B8
DECL|macro|R_MAC_RMON_RX_LENGTH_ERROR
mdefine_line|#define R_MAC_RMON_RX_LENGTH_ERROR      0x000000C0
DECL|macro|R_MAC_RMON_RX_CODE_ERROR
mdefine_line|#define R_MAC_RMON_RX_CODE_ERROR        0x000000C8
DECL|macro|R_MAC_RMON_RX_ALIGN_ERROR
mdefine_line|#define R_MAC_RMON_RX_ALIGN_ERROR       0x000000D0
multiline_comment|/* Updated to spec 0.2 */
DECL|macro|R_MAC_CFG
mdefine_line|#define R_MAC_CFG                       0x00000100
DECL|macro|R_MAC_THRSH_CFG
mdefine_line|#define R_MAC_THRSH_CFG                 0x00000108
DECL|macro|R_MAC_VLANTAG
mdefine_line|#define R_MAC_VLANTAG                   0x00000110
DECL|macro|R_MAC_FRAMECFG
mdefine_line|#define R_MAC_FRAMECFG                  0x00000118
DECL|macro|R_MAC_EOPCNT
mdefine_line|#define R_MAC_EOPCNT                    0x00000120
DECL|macro|R_MAC_FIFO_PTRS
mdefine_line|#define R_MAC_FIFO_PTRS                 0x00000130
DECL|macro|R_MAC_ADFILTER_CFG
mdefine_line|#define R_MAC_ADFILTER_CFG              0x00000200
DECL|macro|R_MAC_ETHERNET_ADDR
mdefine_line|#define R_MAC_ETHERNET_ADDR             0x00000208
DECL|macro|R_MAC_PKT_TYPE
mdefine_line|#define R_MAC_PKT_TYPE                  0x00000210
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|R_MAC_ADMASK0
mdefine_line|#define R_MAC_ADMASK0&t;&t;&t;0x00000218
DECL|macro|R_MAC_ADMASK1
mdefine_line|#define R_MAC_ADMASK1&t;&t;&t;0x00000220
macro_line|#endif /* 112x PASS1 */
DECL|macro|R_MAC_HASH_BASE
mdefine_line|#define R_MAC_HASH_BASE                 0x00000240
DECL|macro|R_MAC_ADDR_BASE
mdefine_line|#define R_MAC_ADDR_BASE                 0x00000280
DECL|macro|R_MAC_CHLO0_BASE
mdefine_line|#define R_MAC_CHLO0_BASE                0x00000300
DECL|macro|R_MAC_CHUP0_BASE
mdefine_line|#define R_MAC_CHUP0_BASE                0x00000320
DECL|macro|R_MAC_ENABLE
mdefine_line|#define R_MAC_ENABLE                    0x00000400
DECL|macro|R_MAC_STATUS
mdefine_line|#define R_MAC_STATUS                    0x00000408
DECL|macro|R_MAC_INT_MASK
mdefine_line|#define R_MAC_INT_MASK                  0x00000410
DECL|macro|R_MAC_TXD_CTL
mdefine_line|#define R_MAC_TXD_CTL                   0x00000420
DECL|macro|R_MAC_MDIO
mdefine_line|#define R_MAC_MDIO                      0x00000428
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|R_MAC_STATUS1
mdefine_line|#define R_MAC_STATUS1&t;&t;        0x00000430
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|R_MAC_DEBUG_STATUS
mdefine_line|#define R_MAC_DEBUG_STATUS              0x00000448
DECL|macro|MAC_HASH_COUNT
mdefine_line|#define MAC_HASH_COUNT&t;&t;&t;8
DECL|macro|MAC_ADDR_COUNT
mdefine_line|#define MAC_ADDR_COUNT&t;&t;&t;8
DECL|macro|MAC_CHMAP_COUNT
mdefine_line|#define MAC_CHMAP_COUNT&t;&t;&t;4
multiline_comment|/*  ********************************************************************* &n;    * DUART Registers&n;    ********************************************************************* */
DECL|macro|R_DUART_NUM_PORTS
mdefine_line|#define R_DUART_NUM_PORTS           2
DECL|macro|A_DUART
mdefine_line|#define A_DUART                     0x0010060000
DECL|macro|A_DUART_REG
mdefine_line|#define A_DUART_REG(r)
DECL|macro|DUART_CHANREG_SPACING
mdefine_line|#define DUART_CHANREG_SPACING       0x100
DECL|macro|A_DUART_CHANREG
mdefine_line|#define A_DUART_CHANREG(chan,reg)   (A_DUART + DUART_CHANREG_SPACING*(chan) + (reg))
DECL|macro|R_DUART_CHANREG
mdefine_line|#define R_DUART_CHANREG(chan,reg)   (DUART_CHANREG_SPACING*(chan) + (reg))
DECL|macro|R_DUART_MODE_REG_1
mdefine_line|#define R_DUART_MODE_REG_1&t;    0x100
DECL|macro|R_DUART_MODE_REG_2
mdefine_line|#define R_DUART_MODE_REG_2&t;    0x110
DECL|macro|R_DUART_STATUS
mdefine_line|#define R_DUART_STATUS              0x120
DECL|macro|R_DUART_CLK_SEL
mdefine_line|#define R_DUART_CLK_SEL             0x130
DECL|macro|R_DUART_CMD
mdefine_line|#define R_DUART_CMD                 0x150
DECL|macro|R_DUART_RX_HOLD
mdefine_line|#define R_DUART_RX_HOLD             0x160
DECL|macro|R_DUART_TX_HOLD
mdefine_line|#define R_DUART_TX_HOLD             0x170
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|R_DUART_FULL_CTL
mdefine_line|#define R_DUART_FULL_CTL&t;    0x140
DECL|macro|R_DUART_OPCR_X
mdefine_line|#define R_DUART_OPCR_X&t;&t;    0x180
DECL|macro|R_DUART_AUXCTL_X
mdefine_line|#define R_DUART_AUXCTL_X&t;    0x190
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/*&n; * The IMR and ISR can&squot;t be addressed with A_DUART_CHANREG,&n; * so use this macro instead.&n; */
DECL|macro|R_DUART_AUX_CTRL
mdefine_line|#define R_DUART_AUX_CTRL            0x310
DECL|macro|R_DUART_ISR_A
mdefine_line|#define R_DUART_ISR_A               0x320
DECL|macro|R_DUART_IMR_A
mdefine_line|#define R_DUART_IMR_A               0x330
DECL|macro|R_DUART_ISR_B
mdefine_line|#define R_DUART_ISR_B               0x340
DECL|macro|R_DUART_IMR_B
mdefine_line|#define R_DUART_IMR_B               0x350
DECL|macro|R_DUART_OUT_PORT
mdefine_line|#define R_DUART_OUT_PORT            0x360
DECL|macro|R_DUART_OPCR
mdefine_line|#define R_DUART_OPCR                0x370
DECL|macro|R_DUART_SET_OPR
mdefine_line|#define R_DUART_SET_OPR&t;&t;    0x3B0
DECL|macro|R_DUART_CLEAR_OPR
mdefine_line|#define R_DUART_CLEAR_OPR&t;    0x3C0
DECL|macro|DUART_IMRISR_SPACING
mdefine_line|#define DUART_IMRISR_SPACING        0x20
DECL|macro|R_DUART_IMRREG
mdefine_line|#define R_DUART_IMRREG(chan)&t;    (R_DUART_IMR_A + (chan)*DUART_IMRISR_SPACING)
DECL|macro|R_DUART_ISRREG
mdefine_line|#define R_DUART_ISRREG(chan)&t;    (R_DUART_ISR_A + (chan)*DUART_IMRISR_SPACING)
DECL|macro|A_DUART_IMRREG
mdefine_line|#define A_DUART_IMRREG(chan)&t;    (A_DUART + R_DUART_IMRREG(chan))
DECL|macro|A_DUART_ISRREG
mdefine_line|#define A_DUART_ISRREG(chan)&t;    (A_DUART + R_DUART_ISRREG(chan))
multiline_comment|/*&n; * These constants are the absolute addresses.&n; */
DECL|macro|A_DUART_MODE_REG_1_A
mdefine_line|#define A_DUART_MODE_REG_1_A        0x0010060100
DECL|macro|A_DUART_MODE_REG_2_A
mdefine_line|#define A_DUART_MODE_REG_2_A        0x0010060110
DECL|macro|A_DUART_STATUS_A
mdefine_line|#define A_DUART_STATUS_A            0x0010060120
DECL|macro|A_DUART_CLK_SEL_A
mdefine_line|#define A_DUART_CLK_SEL_A           0x0010060130
DECL|macro|A_DUART_CMD_A
mdefine_line|#define A_DUART_CMD_A               0x0010060150
DECL|macro|A_DUART_RX_HOLD_A
mdefine_line|#define A_DUART_RX_HOLD_A           0x0010060160
DECL|macro|A_DUART_TX_HOLD_A
mdefine_line|#define A_DUART_TX_HOLD_A           0x0010060170
DECL|macro|A_DUART_MODE_REG_1_B
mdefine_line|#define A_DUART_MODE_REG_1_B        0x0010060200
DECL|macro|A_DUART_MODE_REG_2_B
mdefine_line|#define A_DUART_MODE_REG_2_B        0x0010060210
DECL|macro|A_DUART_STATUS_B
mdefine_line|#define A_DUART_STATUS_B            0x0010060220
DECL|macro|A_DUART_CLK_SEL_B
mdefine_line|#define A_DUART_CLK_SEL_B           0x0010060230
DECL|macro|A_DUART_CMD_B
mdefine_line|#define A_DUART_CMD_B               0x0010060250
DECL|macro|A_DUART_RX_HOLD_B
mdefine_line|#define A_DUART_RX_HOLD_B           0x0010060260
DECL|macro|A_DUART_TX_HOLD_B
mdefine_line|#define A_DUART_TX_HOLD_B           0x0010060270
DECL|macro|A_DUART_INPORT_CHNG
mdefine_line|#define A_DUART_INPORT_CHNG         0x0010060300
DECL|macro|A_DUART_AUX_CTRL
mdefine_line|#define A_DUART_AUX_CTRL            0x0010060310
DECL|macro|A_DUART_ISR_A
mdefine_line|#define A_DUART_ISR_A               0x0010060320
DECL|macro|A_DUART_IMR_A
mdefine_line|#define A_DUART_IMR_A               0x0010060330
DECL|macro|A_DUART_ISR_B
mdefine_line|#define A_DUART_ISR_B               0x0010060340
DECL|macro|A_DUART_IMR_B
mdefine_line|#define A_DUART_IMR_B               0x0010060350
DECL|macro|A_DUART_OUT_PORT
mdefine_line|#define A_DUART_OUT_PORT            0x0010060360
DECL|macro|A_DUART_OPCR
mdefine_line|#define A_DUART_OPCR                0x0010060370
DECL|macro|A_DUART_IN_PORT
mdefine_line|#define A_DUART_IN_PORT             0x0010060380
DECL|macro|A_DUART_ISR
mdefine_line|#define A_DUART_ISR                 0x0010060390
DECL|macro|A_DUART_IMR
mdefine_line|#define A_DUART_IMR                 0x00100603A0
DECL|macro|A_DUART_SET_OPR
mdefine_line|#define A_DUART_SET_OPR             0x00100603B0
DECL|macro|A_DUART_CLEAR_OPR
mdefine_line|#define A_DUART_CLEAR_OPR           0x00100603C0
DECL|macro|A_DUART_INPORT_CHNG_A
mdefine_line|#define A_DUART_INPORT_CHNG_A       0x00100603D0
DECL|macro|A_DUART_INPORT_CHNG_B
mdefine_line|#define A_DUART_INPORT_CHNG_B       0x00100603E0
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|A_DUART_FULL_CTL_A
mdefine_line|#define A_DUART_FULL_CTL_A&t;    0x0010060140
DECL|macro|A_DUART_FULL_CTL_B
mdefine_line|#define A_DUART_FULL_CTL_B&t;    0x0010060240
DECL|macro|A_DUART_OPCR_A
mdefine_line|#define A_DUART_OPCR_A&t;  &t;    0x0010060180
DECL|macro|A_DUART_OPCR_B
mdefine_line|#define A_DUART_OPCR_B&t;  &t;    0x0010060280
DECL|macro|A_DUART_INPORT_CHNG_DEBUG
mdefine_line|#define A_DUART_INPORT_CHNG_DEBUG   0x00100603F0
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/*  ********************************************************************* &n;    * Synchronous Serial Registers&n;    ********************************************************************* */
DECL|macro|A_SER_BASE_0
mdefine_line|#define A_SER_BASE_0                0x0010060400
DECL|macro|A_SER_BASE_1
mdefine_line|#define A_SER_BASE_1                0x0010060800
DECL|macro|SER_SPACING
mdefine_line|#define SER_SPACING                 0x400
DECL|macro|SER_DMA_TXRX_SPACING
mdefine_line|#define SER_DMA_TXRX_SPACING        0x80
DECL|macro|SER_NUM_PORTS
mdefine_line|#define SER_NUM_PORTS               2
DECL|macro|A_SER_CHANNEL_BASE
mdefine_line|#define A_SER_CHANNEL_BASE(sernum)                  &bslash;&n;            (A_SER_BASE_0 +                         &bslash;&n;             SER_SPACING*(sernum))
DECL|macro|A_SER_REGISTER
mdefine_line|#define A_SER_REGISTER(sernum,reg)                  &bslash;&n;            (A_SER_BASE_0 +                         &bslash;&n;             SER_SPACING*(sernum) + (reg))
DECL|macro|R_SER_DMA_CHANNELS
mdefine_line|#define R_SER_DMA_CHANNELS&t;&t;0   /* Relative to A_SER_BASE_x */
DECL|macro|A_SER_DMA_CHANNEL_BASE
mdefine_line|#define A_SER_DMA_CHANNEL_BASE(sernum,txrx)    &bslash;&n;             ((A_SER_CHANNEL_BASE(sernum)) +        &bslash;&n;             R_SER_DMA_CHANNELS +                   &bslash;&n;             (SER_DMA_TXRX_SPACING*(txrx)))
DECL|macro|A_SER_DMA_REGISTER
mdefine_line|#define A_SER_DMA_REGISTER(sernum,txrx,reg)           &bslash;&n;            (A_SER_DMA_CHANNEL_BASE(sernum,txrx) +    &bslash;&n;            (reg))
multiline_comment|/* &n; * DMA channel registers, relative to A_SER_DMA_CHANNEL_BASE&n; */
DECL|macro|R_SER_DMA_CONFIG0
mdefine_line|#define R_SER_DMA_CONFIG0           0x00000000
DECL|macro|R_SER_DMA_CONFIG1
mdefine_line|#define R_SER_DMA_CONFIG1           0x00000008
DECL|macro|R_SER_DMA_DSCR_BASE
mdefine_line|#define R_SER_DMA_DSCR_BASE         0x00000010
DECL|macro|R_SER_DMA_DSCR_CNT
mdefine_line|#define R_SER_DMA_DSCR_CNT          0x00000018
DECL|macro|R_SER_DMA_CUR_DSCRA
mdefine_line|#define R_SER_DMA_CUR_DSCRA         0x00000020
DECL|macro|R_SER_DMA_CUR_DSCRB
mdefine_line|#define R_SER_DMA_CUR_DSCRB         0x00000028
DECL|macro|R_SER_DMA_CUR_DSCRADDR
mdefine_line|#define R_SER_DMA_CUR_DSCRADDR      0x00000030
DECL|macro|R_SER_DMA_CONFIG0_RX
mdefine_line|#define R_SER_DMA_CONFIG0_RX        0x00000000
DECL|macro|R_SER_DMA_CONFIG1_RX
mdefine_line|#define R_SER_DMA_CONFIG1_RX        0x00000008
DECL|macro|R_SER_DMA_DSCR_BASE_RX
mdefine_line|#define R_SER_DMA_DSCR_BASE_RX      0x00000010
DECL|macro|R_SER_DMA_DSCR_COUNT_RX
mdefine_line|#define R_SER_DMA_DSCR_COUNT_RX     0x00000018
DECL|macro|R_SER_DMA_CUR_DSCR_A_RX
mdefine_line|#define R_SER_DMA_CUR_DSCR_A_RX     0x00000020
DECL|macro|R_SER_DMA_CUR_DSCR_B_RX
mdefine_line|#define R_SER_DMA_CUR_DSCR_B_RX     0x00000028
DECL|macro|R_SER_DMA_CUR_DSCR_ADDR_RX
mdefine_line|#define R_SER_DMA_CUR_DSCR_ADDR_RX  0x00000030
DECL|macro|R_SER_DMA_CONFIG0_TX
mdefine_line|#define R_SER_DMA_CONFIG0_TX        0x00000080
DECL|macro|R_SER_DMA_CONFIG1_TX
mdefine_line|#define R_SER_DMA_CONFIG1_TX        0x00000088
DECL|macro|R_SER_DMA_DSCR_BASE_TX
mdefine_line|#define R_SER_DMA_DSCR_BASE_TX      0x00000090
DECL|macro|R_SER_DMA_DSCR_COUNT_TX
mdefine_line|#define R_SER_DMA_DSCR_COUNT_TX     0x00000098
DECL|macro|R_SER_DMA_CUR_DSCR_A_TX
mdefine_line|#define R_SER_DMA_CUR_DSCR_A_TX     0x000000A0
DECL|macro|R_SER_DMA_CUR_DSCR_B_TX
mdefine_line|#define R_SER_DMA_CUR_DSCR_B_TX     0x000000A8
DECL|macro|R_SER_DMA_CUR_DSCR_ADDR_TX
mdefine_line|#define R_SER_DMA_CUR_DSCR_ADDR_TX  0x000000B0
DECL|macro|R_SER_MODE
mdefine_line|#define R_SER_MODE                  0x00000100
DECL|macro|R_SER_MINFRM_SZ
mdefine_line|#define R_SER_MINFRM_SZ             0x00000108
DECL|macro|R_SER_MAXFRM_SZ
mdefine_line|#define R_SER_MAXFRM_SZ             0x00000110
DECL|macro|R_SER_ADDR
mdefine_line|#define R_SER_ADDR                  0x00000118
DECL|macro|R_SER_USR0_ADDR
mdefine_line|#define R_SER_USR0_ADDR             0x00000120
DECL|macro|R_SER_USR1_ADDR
mdefine_line|#define R_SER_USR1_ADDR             0x00000128
DECL|macro|R_SER_USR2_ADDR
mdefine_line|#define R_SER_USR2_ADDR             0x00000130
DECL|macro|R_SER_USR3_ADDR
mdefine_line|#define R_SER_USR3_ADDR             0x00000138
DECL|macro|R_SER_CMD
mdefine_line|#define R_SER_CMD                   0x00000140
DECL|macro|R_SER_TX_RD_THRSH
mdefine_line|#define R_SER_TX_RD_THRSH           0x00000160
DECL|macro|R_SER_TX_WR_THRSH
mdefine_line|#define R_SER_TX_WR_THRSH           0x00000168
DECL|macro|R_SER_RX_RD_THRSH
mdefine_line|#define R_SER_RX_RD_THRSH           0x00000170
DECL|macro|R_SER_LINE_MODE
mdefine_line|#define R_SER_LINE_MODE&t;&t;    0x00000178
DECL|macro|R_SER_DMA_ENABLE
mdefine_line|#define R_SER_DMA_ENABLE            0x00000180
DECL|macro|R_SER_INT_MASK
mdefine_line|#define R_SER_INT_MASK              0x00000190
DECL|macro|R_SER_STATUS
mdefine_line|#define R_SER_STATUS                0x00000188
DECL|macro|R_SER_STATUS_DEBUG
mdefine_line|#define R_SER_STATUS_DEBUG          0x000001A8
DECL|macro|R_SER_RX_TABLE_BASE
mdefine_line|#define R_SER_RX_TABLE_BASE         0x00000200
DECL|macro|SER_RX_TABLE_COUNT
mdefine_line|#define SER_RX_TABLE_COUNT          16
DECL|macro|R_SER_TX_TABLE_BASE
mdefine_line|#define R_SER_TX_TABLE_BASE         0x00000300
DECL|macro|SER_TX_TABLE_COUNT
mdefine_line|#define SER_TX_TABLE_COUNT          16
multiline_comment|/* RMON Counters */
DECL|macro|R_SER_RMON_TX_BYTE_LO
mdefine_line|#define R_SER_RMON_TX_BYTE_LO       0x000001C0
DECL|macro|R_SER_RMON_TX_BYTE_HI
mdefine_line|#define R_SER_RMON_TX_BYTE_HI       0x000001C8
DECL|macro|R_SER_RMON_RX_BYTE_LO
mdefine_line|#define R_SER_RMON_RX_BYTE_LO       0x000001D0
DECL|macro|R_SER_RMON_RX_BYTE_HI
mdefine_line|#define R_SER_RMON_RX_BYTE_HI       0x000001D8
DECL|macro|R_SER_RMON_TX_UNDERRUN
mdefine_line|#define R_SER_RMON_TX_UNDERRUN      0x000001E0
DECL|macro|R_SER_RMON_RX_OVERFLOW
mdefine_line|#define R_SER_RMON_RX_OVERFLOW      0x000001E8
DECL|macro|R_SER_RMON_RX_ERRORS
mdefine_line|#define R_SER_RMON_RX_ERRORS        0x000001F0
DECL|macro|R_SER_RMON_RX_BADADDR
mdefine_line|#define R_SER_RMON_RX_BADADDR       0x000001F8
multiline_comment|/*  ********************************************************************* &n;    * Generic Bus Registers&n;    ********************************************************************* */
DECL|macro|IO_EXT_CFG_COUNT
mdefine_line|#define IO_EXT_CFG_COUNT            8
DECL|macro|A_IO_EXT_BASE
mdefine_line|#define A_IO_EXT_BASE&t;&t;    0x0010061000
DECL|macro|A_IO_EXT_REG
mdefine_line|#define A_IO_EXT_REG(r)&t;&t;    (A_IO_EXT_BASE + (r))
DECL|macro|A_IO_EXT_CFG_BASE
mdefine_line|#define A_IO_EXT_CFG_BASE           0x0010061000
DECL|macro|A_IO_EXT_MULT_SIZE_BASE
mdefine_line|#define A_IO_EXT_MULT_SIZE_BASE     0x0010061100
DECL|macro|A_IO_EXT_START_ADDR_BASE
mdefine_line|#define A_IO_EXT_START_ADDR_BASE    0x0010061200
DECL|macro|A_IO_EXT_TIME_CFG0_BASE
mdefine_line|#define A_IO_EXT_TIME_CFG0_BASE     0x0010061600
DECL|macro|A_IO_EXT_TIME_CFG1_BASE
mdefine_line|#define A_IO_EXT_TIME_CFG1_BASE     0x0010061700
DECL|macro|IO_EXT_REGISTER_SPACING
mdefine_line|#define IO_EXT_REGISTER_SPACING&t;    8
DECL|macro|A_IO_EXT_CS_BASE
mdefine_line|#define A_IO_EXT_CS_BASE(cs)&t;    (A_IO_EXT_CFG_BASE+IO_EXT_REGISTER_SPACING*(cs))
DECL|macro|R_IO_EXT_REG
mdefine_line|#define R_IO_EXT_REG(reg,cs)&t;    ((cs)*IO_EXT_REGISTER_SPACING + (reg))
DECL|macro|R_IO_EXT_CFG
mdefine_line|#define R_IO_EXT_CFG&t;&t;    0x0000
DECL|macro|R_IO_EXT_MULT_SIZE
mdefine_line|#define R_IO_EXT_MULT_SIZE          0x0100
DECL|macro|R_IO_EXT_START_ADDR
mdefine_line|#define R_IO_EXT_START_ADDR&t;    0x0200
DECL|macro|R_IO_EXT_TIME_CFG0
mdefine_line|#define R_IO_EXT_TIME_CFG0          0x0600
DECL|macro|R_IO_EXT_TIME_CFG1
mdefine_line|#define R_IO_EXT_TIME_CFG1          0x0700
DECL|macro|A_IO_INTERRUPT_STATUS
mdefine_line|#define A_IO_INTERRUPT_STATUS       0x0010061A00
DECL|macro|A_IO_INTERRUPT_DATA0
mdefine_line|#define A_IO_INTERRUPT_DATA0        0x0010061A10
DECL|macro|A_IO_INTERRUPT_DATA1
mdefine_line|#define A_IO_INTERRUPT_DATA1        0x0010061A18
DECL|macro|A_IO_INTERRUPT_DATA2
mdefine_line|#define A_IO_INTERRUPT_DATA2        0x0010061A20
DECL|macro|A_IO_INTERRUPT_DATA3
mdefine_line|#define A_IO_INTERRUPT_DATA3        0x0010061A28
DECL|macro|A_IO_INTERRUPT_ADDR0
mdefine_line|#define A_IO_INTERRUPT_ADDR0        0x0010061A30
DECL|macro|A_IO_INTERRUPT_ADDR1
mdefine_line|#define A_IO_INTERRUPT_ADDR1        0x0010061A40
DECL|macro|A_IO_INTERRUPT_PARITY
mdefine_line|#define A_IO_INTERRUPT_PARITY       0x0010061A50
DECL|macro|A_IO_PCMCIA_CFG
mdefine_line|#define A_IO_PCMCIA_CFG             0x0010061A60
DECL|macro|A_IO_PCMCIA_STATUS
mdefine_line|#define A_IO_PCMCIA_STATUS          0x0010061A70
DECL|macro|A_IO_DRIVE_0
mdefine_line|#define A_IO_DRIVE_0&t;&t;    0x0010061300
DECL|macro|A_IO_DRIVE_1
mdefine_line|#define A_IO_DRIVE_1&t;&t;    0x0010061308
DECL|macro|A_IO_DRIVE_2
mdefine_line|#define A_IO_DRIVE_2&t;&t;    0x0010061310
DECL|macro|A_IO_DRIVE_3
mdefine_line|#define A_IO_DRIVE_3&t;&t;    0x0010061318
DECL|macro|A_IO_DRIVE_BASE
mdefine_line|#define A_IO_DRIVE_BASE&t;&t;    A_IO_DRIVE_0
DECL|macro|IO_DRIVE_REGISTER_SPACING
mdefine_line|#define IO_DRIVE_REGISTER_SPACING   8
DECL|macro|R_IO_DRIVE
mdefine_line|#define R_IO_DRIVE(x)&t;&t;    ((x)*IO_DRIVE_REGISTER_SPACING)
DECL|macro|A_IO_DRIVE
mdefine_line|#define A_IO_DRIVE(x)&t;&t;    (A_IO_DRIVE_BASE + R_IO_DRIVE(x))
DECL|macro|R_IO_INTERRUPT_STATUS
mdefine_line|#define R_IO_INTERRUPT_STATUS       0x0A00
DECL|macro|R_IO_INTERRUPT_DATA0
mdefine_line|#define R_IO_INTERRUPT_DATA0        0x0A10
DECL|macro|R_IO_INTERRUPT_DATA1
mdefine_line|#define R_IO_INTERRUPT_DATA1        0x0A18
DECL|macro|R_IO_INTERRUPT_DATA2
mdefine_line|#define R_IO_INTERRUPT_DATA2        0x0A20
DECL|macro|R_IO_INTERRUPT_DATA3
mdefine_line|#define R_IO_INTERRUPT_DATA3        0x0A28
DECL|macro|R_IO_INTERRUPT_ADDR0
mdefine_line|#define R_IO_INTERRUPT_ADDR0        0x0A30
DECL|macro|R_IO_INTERRUPT_ADDR1
mdefine_line|#define R_IO_INTERRUPT_ADDR1        0x0A40
DECL|macro|R_IO_INTERRUPT_PARITY
mdefine_line|#define R_IO_INTERRUPT_PARITY       0x0A50
DECL|macro|R_IO_PCMCIA_CFG
mdefine_line|#define R_IO_PCMCIA_CFG             0x0A60
DECL|macro|R_IO_PCMCIA_STATUS
mdefine_line|#define R_IO_PCMCIA_STATUS          0x0A70
multiline_comment|/*  ********************************************************************* &n;    * GPIO Registers&n;    ********************************************************************* */
DECL|macro|A_GPIO_CLR_EDGE
mdefine_line|#define A_GPIO_CLR_EDGE             0x0010061A80
DECL|macro|A_GPIO_INT_TYPE
mdefine_line|#define A_GPIO_INT_TYPE             0x0010061A88
DECL|macro|A_GPIO_INPUT_INVERT
mdefine_line|#define A_GPIO_INPUT_INVERT         0x0010061A90
DECL|macro|A_GPIO_GLITCH
mdefine_line|#define A_GPIO_GLITCH               0x0010061A98
DECL|macro|A_GPIO_READ
mdefine_line|#define A_GPIO_READ                 0x0010061AA0
DECL|macro|A_GPIO_DIRECTION
mdefine_line|#define A_GPIO_DIRECTION            0x0010061AA8
DECL|macro|A_GPIO_PIN_CLR
mdefine_line|#define A_GPIO_PIN_CLR              0x0010061AB0
DECL|macro|A_GPIO_PIN_SET
mdefine_line|#define A_GPIO_PIN_SET              0x0010061AB8
DECL|macro|A_GPIO_BASE
mdefine_line|#define A_GPIO_BASE&t;&t;    0x0010061A80
DECL|macro|R_GPIO_CLR_EDGE
mdefine_line|#define R_GPIO_CLR_EDGE             0x00
DECL|macro|R_GPIO_INT_TYPE
mdefine_line|#define R_GPIO_INT_TYPE             0x08
DECL|macro|R_GPIO_INPUT_INVERT
mdefine_line|#define R_GPIO_INPUT_INVERT         0x10
DECL|macro|R_GPIO_GLITCH
mdefine_line|#define R_GPIO_GLITCH               0x18
DECL|macro|R_GPIO_READ
mdefine_line|#define R_GPIO_READ                 0x20
DECL|macro|R_GPIO_DIRECTION
mdefine_line|#define R_GPIO_DIRECTION            0x28
DECL|macro|R_GPIO_PIN_CLR
mdefine_line|#define R_GPIO_PIN_CLR              0x30
DECL|macro|R_GPIO_PIN_SET
mdefine_line|#define R_GPIO_PIN_SET              0x38
multiline_comment|/*  ********************************************************************* &n;    * SMBus Registers&n;    ********************************************************************* */
DECL|macro|A_SMB_XTRA_0
mdefine_line|#define A_SMB_XTRA_0                0x0010060000
DECL|macro|A_SMB_XTRA_1
mdefine_line|#define A_SMB_XTRA_1                0x0010060008
DECL|macro|A_SMB_FREQ_0
mdefine_line|#define A_SMB_FREQ_0                0x0010060010
DECL|macro|A_SMB_FREQ_1
mdefine_line|#define A_SMB_FREQ_1                0x0010060018
DECL|macro|A_SMB_STATUS_0
mdefine_line|#define A_SMB_STATUS_0              0x0010060020
DECL|macro|A_SMB_STATUS_1
mdefine_line|#define A_SMB_STATUS_1              0x0010060028
DECL|macro|A_SMB_CMD_0
mdefine_line|#define A_SMB_CMD_0                 0x0010060030
DECL|macro|A_SMB_CMD_1
mdefine_line|#define A_SMB_CMD_1                 0x0010060038
DECL|macro|A_SMB_START_0
mdefine_line|#define A_SMB_START_0               0x0010060040
DECL|macro|A_SMB_START_1
mdefine_line|#define A_SMB_START_1               0x0010060048
DECL|macro|A_SMB_DATA_0
mdefine_line|#define A_SMB_DATA_0                0x0010060050
DECL|macro|A_SMB_DATA_1
mdefine_line|#define A_SMB_DATA_1                0x0010060058
DECL|macro|A_SMB_CONTROL_0
mdefine_line|#define A_SMB_CONTROL_0             0x0010060060
DECL|macro|A_SMB_CONTROL_1
mdefine_line|#define A_SMB_CONTROL_1             0x0010060068
DECL|macro|A_SMB_PEC_0
mdefine_line|#define A_SMB_PEC_0                 0x0010060070
DECL|macro|A_SMB_PEC_1
mdefine_line|#define A_SMB_PEC_1                 0x0010060078
DECL|macro|A_SMB_0
mdefine_line|#define A_SMB_0                     0x0010060000
DECL|macro|A_SMB_1
mdefine_line|#define A_SMB_1                     0x0010060008
DECL|macro|SMB_REGISTER_SPACING
mdefine_line|#define SMB_REGISTER_SPACING        0x8
DECL|macro|A_SMB_BASE
mdefine_line|#define A_SMB_BASE(idx)             (A_SMB_0+(idx)*SMB_REGISTER_SPACING)
DECL|macro|A_SMB_REGISTER
mdefine_line|#define A_SMB_REGISTER(idx,reg)     (A_SMB_BASE(idx)+(reg))
DECL|macro|R_SMB_XTRA
mdefine_line|#define R_SMB_XTRA                  0x0000000000
DECL|macro|R_SMB_FREQ
mdefine_line|#define R_SMB_FREQ                  0x0000000010
DECL|macro|R_SMB_STATUS
mdefine_line|#define R_SMB_STATUS                0x0000000020
DECL|macro|R_SMB_CMD
mdefine_line|#define R_SMB_CMD                   0x0000000030
DECL|macro|R_SMB_START
mdefine_line|#define R_SMB_START                 0x0000000040
DECL|macro|R_SMB_DATA
mdefine_line|#define R_SMB_DATA                  0x0000000050
DECL|macro|R_SMB_CONTROL
mdefine_line|#define R_SMB_CONTROL               0x0000000060
DECL|macro|R_SMB_PEC
mdefine_line|#define R_SMB_PEC                   0x0000000070
multiline_comment|/*  ********************************************************************* &n;    * Timer Registers&n;    ********************************************************************* */
multiline_comment|/*&n; * Watchdog timers&n; */
DECL|macro|A_SCD_WDOG_0
mdefine_line|#define A_SCD_WDOG_0&t;&t;    0x0010020050
DECL|macro|A_SCD_WDOG_1
mdefine_line|#define A_SCD_WDOG_1                0x0010020150
DECL|macro|SCD_WDOG_SPACING
mdefine_line|#define SCD_WDOG_SPACING            0x100
DECL|macro|SCD_NUM_WDOGS
mdefine_line|#define SCD_NUM_WDOGS&t;&t;    2
DECL|macro|A_SCD_WDOG_BASE
mdefine_line|#define A_SCD_WDOG_BASE(w)          (A_SCD_WDOG_0+SCD_WDOG_SPACING*(w))
DECL|macro|A_SCD_WDOG_REGISTER
mdefine_line|#define A_SCD_WDOG_REGISTER(w,r)    (A_SCD_WDOG_BASE(w) + (r))
DECL|macro|R_SCD_WDOG_INIT
mdefine_line|#define R_SCD_WDOG_INIT&t;&t;    0x0000000000
DECL|macro|R_SCD_WDOG_CNT
mdefine_line|#define R_SCD_WDOG_CNT&t;&t;    0x0000000008
DECL|macro|R_SCD_WDOG_CFG
mdefine_line|#define R_SCD_WDOG_CFG&t;&t;    0x0000000010
DECL|macro|A_SCD_WDOG_INIT_0
mdefine_line|#define A_SCD_WDOG_INIT_0           0x0010020050
DECL|macro|A_SCD_WDOG_CNT_0
mdefine_line|#define A_SCD_WDOG_CNT_0            0x0010020058
DECL|macro|A_SCD_WDOG_CFG_0
mdefine_line|#define A_SCD_WDOG_CFG_0            0x0010020060
DECL|macro|A_SCD_WDOG_INIT_1
mdefine_line|#define A_SCD_WDOG_INIT_1           0x0010020150
DECL|macro|A_SCD_WDOG_CNT_1
mdefine_line|#define A_SCD_WDOG_CNT_1            0x0010020158
DECL|macro|A_SCD_WDOG_CFG_1
mdefine_line|#define A_SCD_WDOG_CFG_1            0x0010020160
multiline_comment|/*&n; * Generic timers&n; */
DECL|macro|A_SCD_TIMER_0
mdefine_line|#define A_SCD_TIMER_0&t;&t;    0x0010020070
DECL|macro|A_SCD_TIMER_1
mdefine_line|#define A_SCD_TIMER_1               0x0010020078
DECL|macro|A_SCD_TIMER_2
mdefine_line|#define A_SCD_TIMER_2&t;&t;    0x0010020170
DECL|macro|A_SCD_TIMER_3
mdefine_line|#define A_SCD_TIMER_3               0x0010020178
DECL|macro|SCD_NUM_TIMERS
mdefine_line|#define SCD_NUM_TIMERS&t;&t;    4
DECL|macro|A_SCD_TIMER_BASE
mdefine_line|#define A_SCD_TIMER_BASE(w)         (A_SCD_TIMER_0+0x08*((w)&amp;1)+0x100*(((w)&amp;2)&gt;&gt;1))
DECL|macro|A_SCD_TIMER_REGISTER
mdefine_line|#define A_SCD_TIMER_REGISTER(w,r)   (A_SCD_TIMER_BASE(w) + (r))
DECL|macro|R_SCD_TIMER_INIT
mdefine_line|#define R_SCD_TIMER_INIT&t;    0x0000000000
DECL|macro|R_SCD_TIMER_CNT
mdefine_line|#define R_SCD_TIMER_CNT&t;&t;    0x0000000010
DECL|macro|R_SCD_TIMER_CFG
mdefine_line|#define R_SCD_TIMER_CFG&t;&t;    0x0000000020
DECL|macro|A_SCD_TIMER_INIT_0
mdefine_line|#define A_SCD_TIMER_INIT_0          0x0010020070
DECL|macro|A_SCD_TIMER_CNT_0
mdefine_line|#define A_SCD_TIMER_CNT_0           0x0010020080
DECL|macro|A_SCD_TIMER_CFG_0
mdefine_line|#define A_SCD_TIMER_CFG_0           0x0010020090
DECL|macro|A_SCD_TIMER_INIT_1
mdefine_line|#define A_SCD_TIMER_INIT_1          0x0010020078
DECL|macro|A_SCD_TIMER_CNT_1
mdefine_line|#define A_SCD_TIMER_CNT_1           0x0010020088
DECL|macro|A_SCD_TIMER_CFG_1
mdefine_line|#define A_SCD_TIMER_CFG_1           0x0010020098
DECL|macro|A_SCD_TIMER_INIT_2
mdefine_line|#define A_SCD_TIMER_INIT_2          0x0010020170
DECL|macro|A_SCD_TIMER_CNT_2
mdefine_line|#define A_SCD_TIMER_CNT_2           0x0010020180
DECL|macro|A_SCD_TIMER_CFG_2
mdefine_line|#define A_SCD_TIMER_CFG_2           0x0010020190
DECL|macro|A_SCD_TIMER_INIT_3
mdefine_line|#define A_SCD_TIMER_INIT_3          0x0010020178
DECL|macro|A_SCD_TIMER_CNT_3
mdefine_line|#define A_SCD_TIMER_CNT_3           0x0010020188
DECL|macro|A_SCD_TIMER_CFG_3
mdefine_line|#define A_SCD_TIMER_CFG_3           0x0010020198
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|A_SCD_SCRATCH
mdefine_line|#define A_SCD_SCRATCH&t;&t;   0x0010020C10
DECL|macro|A_SCD_ZBBUS_CYCLE_COUNT
mdefine_line|#define A_SCD_ZBBUS_CYCLE_COUNT&t;   0x0010030000
DECL|macro|A_SCD_ZBBUS_CYCLE_CP0
mdefine_line|#define A_SCD_ZBBUS_CYCLE_CP0&t;   0x0010020C00
DECL|macro|A_SCD_ZBBUS_CYCLE_CP1
mdefine_line|#define A_SCD_ZBBUS_CYCLE_CP1&t;   0x0010020C08
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/*  ********************************************************************* &n;    * System Control Registers&n;    ********************************************************************* */
DECL|macro|A_SCD_SYSTEM_REVISION
mdefine_line|#define A_SCD_SYSTEM_REVISION       0x0010020000
DECL|macro|A_SCD_SYSTEM_CFG
mdefine_line|#define A_SCD_SYSTEM_CFG            0x0010020008
multiline_comment|/*  ********************************************************************* &n;    * System Address Trap Registers&n;    ********************************************************************* */
DECL|macro|A_ADDR_TRAP_INDEX
mdefine_line|#define A_ADDR_TRAP_INDEX           0x00100200B0
DECL|macro|A_ADDR_TRAP_REG
mdefine_line|#define A_ADDR_TRAP_REG             0x00100200B8
DECL|macro|A_ADDR_TRAP_UP_0
mdefine_line|#define A_ADDR_TRAP_UP_0            0x0010020400
DECL|macro|A_ADDR_TRAP_UP_1
mdefine_line|#define A_ADDR_TRAP_UP_1            0x0010020408
DECL|macro|A_ADDR_TRAP_UP_2
mdefine_line|#define A_ADDR_TRAP_UP_2            0x0010020410
DECL|macro|A_ADDR_TRAP_UP_3
mdefine_line|#define A_ADDR_TRAP_UP_3            0x0010020418
DECL|macro|A_ADDR_TRAP_DOWN_0
mdefine_line|#define A_ADDR_TRAP_DOWN_0          0x0010020420
DECL|macro|A_ADDR_TRAP_DOWN_1
mdefine_line|#define A_ADDR_TRAP_DOWN_1          0x0010020428
DECL|macro|A_ADDR_TRAP_DOWN_2
mdefine_line|#define A_ADDR_TRAP_DOWN_2          0x0010020430
DECL|macro|A_ADDR_TRAP_DOWN_3
mdefine_line|#define A_ADDR_TRAP_DOWN_3          0x0010020438
DECL|macro|A_ADDR_TRAP_CFG_0
mdefine_line|#define A_ADDR_TRAP_CFG_0           0x0010020440
DECL|macro|A_ADDR_TRAP_CFG_1
mdefine_line|#define A_ADDR_TRAP_CFG_1           0x0010020448
DECL|macro|A_ADDR_TRAP_CFG_2
mdefine_line|#define A_ADDR_TRAP_CFG_2           0x0010020450
DECL|macro|A_ADDR_TRAP_CFG_3
mdefine_line|#define A_ADDR_TRAP_CFG_3           0x0010020458
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|A_ADDR_TRAP_REG_DEBUG
mdefine_line|#define A_ADDR_TRAP_REG_DEBUG&t;    0x0010020460
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/*  ********************************************************************* &n;    * System Interrupt Mapper Registers&n;    ********************************************************************* */
DECL|macro|A_IMR_CPU0_BASE
mdefine_line|#define A_IMR_CPU0_BASE                 0x0010020000
DECL|macro|A_IMR_CPU1_BASE
mdefine_line|#define A_IMR_CPU1_BASE                 0x0010022000
DECL|macro|IMR_REGISTER_SPACING
mdefine_line|#define IMR_REGISTER_SPACING            0x2000
DECL|macro|IMR_REGISTER_SPACING_SHIFT
mdefine_line|#define IMR_REGISTER_SPACING_SHIFT      13
DECL|macro|A_IMR_MAPPER
mdefine_line|#define A_IMR_MAPPER(cpu) (A_IMR_CPU0_BASE+(cpu)*IMR_REGISTER_SPACING)
DECL|macro|A_IMR_REGISTER
mdefine_line|#define A_IMR_REGISTER(cpu,reg) (A_IMR_MAPPER(cpu)+(reg))
DECL|macro|R_IMR_INTERRUPT_DIAG
mdefine_line|#define R_IMR_INTERRUPT_DIAG            0x0010
DECL|macro|R_IMR_INTERRUPT_MASK
mdefine_line|#define R_IMR_INTERRUPT_MASK            0x0028
DECL|macro|R_IMR_INTERRUPT_TRACE
mdefine_line|#define R_IMR_INTERRUPT_TRACE           0x0038
DECL|macro|R_IMR_INTERRUPT_SOURCE_STATUS
mdefine_line|#define R_IMR_INTERRUPT_SOURCE_STATUS   0x0040
DECL|macro|R_IMR_LDT_INTERRUPT_SET
mdefine_line|#define R_IMR_LDT_INTERRUPT_SET         0x0048
DECL|macro|R_IMR_LDT_INTERRUPT
mdefine_line|#define R_IMR_LDT_INTERRUPT             0x0018
DECL|macro|R_IMR_LDT_INTERRUPT_CLR
mdefine_line|#define R_IMR_LDT_INTERRUPT_CLR         0x0020
DECL|macro|R_IMR_MAILBOX_CPU
mdefine_line|#define R_IMR_MAILBOX_CPU               0x00c0
DECL|macro|R_IMR_ALIAS_MAILBOX_CPU
mdefine_line|#define R_IMR_ALIAS_MAILBOX_CPU         0x1000
DECL|macro|R_IMR_MAILBOX_SET_CPU
mdefine_line|#define R_IMR_MAILBOX_SET_CPU           0x00C8
DECL|macro|R_IMR_ALIAS_MAILBOX_SET_CPU
mdefine_line|#define R_IMR_ALIAS_MAILBOX_SET_CPU     0x1008
DECL|macro|R_IMR_MAILBOX_CLR_CPU
mdefine_line|#define R_IMR_MAILBOX_CLR_CPU           0x00D0
DECL|macro|R_IMR_INTERRUPT_STATUS_BASE
mdefine_line|#define R_IMR_INTERRUPT_STATUS_BASE     0x0100
DECL|macro|R_IMR_INTERRUPT_STATUS_COUNT
mdefine_line|#define R_IMR_INTERRUPT_STATUS_COUNT    7
DECL|macro|R_IMR_INTERRUPT_MAP_BASE
mdefine_line|#define R_IMR_INTERRUPT_MAP_BASE        0x0200
DECL|macro|R_IMR_INTERRUPT_MAP_COUNT
mdefine_line|#define R_IMR_INTERRUPT_MAP_COUNT       64
multiline_comment|/*  ********************************************************************* &n;    * System Performance Counter Registers&n;    ********************************************************************* */
DECL|macro|A_SCD_PERF_CNT_CFG
mdefine_line|#define A_SCD_PERF_CNT_CFG          0x00100204C0
DECL|macro|A_SCD_PERF_CNT_0
mdefine_line|#define A_SCD_PERF_CNT_0            0x00100204D0
DECL|macro|A_SCD_PERF_CNT_1
mdefine_line|#define A_SCD_PERF_CNT_1            0x00100204D8
DECL|macro|A_SCD_PERF_CNT_2
mdefine_line|#define A_SCD_PERF_CNT_2            0x00100204E0
DECL|macro|A_SCD_PERF_CNT_3
mdefine_line|#define A_SCD_PERF_CNT_3            0x00100204E8
multiline_comment|/*  ********************************************************************* &n;    * System Bus Watcher Registers&n;    ********************************************************************* */
DECL|macro|A_SCD_BUS_ERR_STATUS
mdefine_line|#define A_SCD_BUS_ERR_STATUS        0x0010020880
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|A_SCD_BUS_ERR_STATUS_DEBUG
mdefine_line|#define A_SCD_BUS_ERR_STATUS_DEBUG  0x00100208D0
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|A_BUS_ERR_DATA_0
mdefine_line|#define A_BUS_ERR_DATA_0            0x00100208A0
DECL|macro|A_BUS_ERR_DATA_1
mdefine_line|#define A_BUS_ERR_DATA_1            0x00100208A8
DECL|macro|A_BUS_ERR_DATA_2
mdefine_line|#define A_BUS_ERR_DATA_2            0x00100208B0
DECL|macro|A_BUS_ERR_DATA_3
mdefine_line|#define A_BUS_ERR_DATA_3            0x00100208B8
DECL|macro|A_BUS_L2_ERRORS
mdefine_line|#define A_BUS_L2_ERRORS             0x00100208C0
DECL|macro|A_BUS_MEM_IO_ERRORS
mdefine_line|#define A_BUS_MEM_IO_ERRORS         0x00100208C8
multiline_comment|/*  ********************************************************************* &n;    * System Debug Controller Registers&n;    ********************************************************************* */
DECL|macro|A_SCD_JTAG_BASE
mdefine_line|#define A_SCD_JTAG_BASE             0x0010000000
multiline_comment|/*  ********************************************************************* &n;    * System Trace Buffer Registers&n;    ********************************************************************* */
DECL|macro|A_SCD_TRACE_CFG
mdefine_line|#define A_SCD_TRACE_CFG             0x0010020A00
DECL|macro|A_SCD_TRACE_READ
mdefine_line|#define A_SCD_TRACE_READ            0x0010020A08
DECL|macro|A_SCD_TRACE_EVENT_0
mdefine_line|#define A_SCD_TRACE_EVENT_0         0x0010020A20
DECL|macro|A_SCD_TRACE_EVENT_1
mdefine_line|#define A_SCD_TRACE_EVENT_1         0x0010020A28
DECL|macro|A_SCD_TRACE_EVENT_2
mdefine_line|#define A_SCD_TRACE_EVENT_2         0x0010020A30
DECL|macro|A_SCD_TRACE_EVENT_3
mdefine_line|#define A_SCD_TRACE_EVENT_3         0x0010020A38
DECL|macro|A_SCD_TRACE_SEQUENCE_0
mdefine_line|#define A_SCD_TRACE_SEQUENCE_0      0x0010020A40
DECL|macro|A_SCD_TRACE_SEQUENCE_1
mdefine_line|#define A_SCD_TRACE_SEQUENCE_1      0x0010020A48
DECL|macro|A_SCD_TRACE_SEQUENCE_2
mdefine_line|#define A_SCD_TRACE_SEQUENCE_2      0x0010020A50
DECL|macro|A_SCD_TRACE_SEQUENCE_3
mdefine_line|#define A_SCD_TRACE_SEQUENCE_3      0x0010020A58
DECL|macro|A_SCD_TRACE_EVENT_4
mdefine_line|#define A_SCD_TRACE_EVENT_4         0x0010020A60
DECL|macro|A_SCD_TRACE_EVENT_5
mdefine_line|#define A_SCD_TRACE_EVENT_5         0x0010020A68
DECL|macro|A_SCD_TRACE_EVENT_6
mdefine_line|#define A_SCD_TRACE_EVENT_6         0x0010020A70
DECL|macro|A_SCD_TRACE_EVENT_7
mdefine_line|#define A_SCD_TRACE_EVENT_7         0x0010020A78
DECL|macro|A_SCD_TRACE_SEQUENCE_4
mdefine_line|#define A_SCD_TRACE_SEQUENCE_4      0x0010020A80
DECL|macro|A_SCD_TRACE_SEQUENCE_5
mdefine_line|#define A_SCD_TRACE_SEQUENCE_5      0x0010020A88
DECL|macro|A_SCD_TRACE_SEQUENCE_6
mdefine_line|#define A_SCD_TRACE_SEQUENCE_6      0x0010020A90
DECL|macro|A_SCD_TRACE_SEQUENCE_7
mdefine_line|#define A_SCD_TRACE_SEQUENCE_7      0x0010020A98
multiline_comment|/*  ********************************************************************* &n;    * System Generic DMA Registers&n;    ********************************************************************* */
DECL|macro|A_DM_0
mdefine_line|#define A_DM_0&t;&t;  &t;    0x0010020B00
DECL|macro|A_DM_1
mdefine_line|#define A_DM_1&t;&t;  &t;    0x0010020B20
DECL|macro|A_DM_2
mdefine_line|#define A_DM_2&t;&t;&t;    0x0010020B40
DECL|macro|A_DM_3
mdefine_line|#define A_DM_3&t;&t;&t;    0x0010020B60
DECL|macro|DM_REGISTER_SPACING
mdefine_line|#define DM_REGISTER_SPACING&t;    0x20
DECL|macro|DM_NUM_CHANNELS
mdefine_line|#define DM_NUM_CHANNELS&t;&t;    4
DECL|macro|A_DM_BASE
mdefine_line|#define A_DM_BASE(idx) (A_DM_0 + ((idx) * DM_REGISTER_SPACING))
DECL|macro|A_DM_REGISTER
mdefine_line|#define A_DM_REGISTER(idx,reg) (A_DM_BASE(idx) + (reg))
DECL|macro|R_DM_DSCR_BASE
mdefine_line|#define R_DM_DSCR_BASE&t;&t;    0x0000000000
DECL|macro|R_DM_DSCR_COUNT
mdefine_line|#define R_DM_DSCR_COUNT&t;&t;    0x0000000008
DECL|macro|R_DM_CUR_DSCR_ADDR
mdefine_line|#define R_DM_CUR_DSCR_ADDR&t;    0x0000000010
DECL|macro|R_DM_DSCR_BASE_DEBUG
mdefine_line|#define R_DM_DSCR_BASE_DEBUG&t;    0x0000000018
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|A_DM_PARTIAL_0
mdefine_line|#define A_DM_PARTIAL_0&t;&t;    0x0010020ba0
DECL|macro|A_DM_PARTIAL_1
mdefine_line|#define A_DM_PARTIAL_1&t;&t;    0x0010020ba8
DECL|macro|A_DM_PARTIAL_2
mdefine_line|#define A_DM_PARTIAL_2&t;&t;    0x0010020bb0
DECL|macro|A_DM_PARTIAL_3
mdefine_line|#define A_DM_PARTIAL_3&t;&t;    0x0010020bb8
DECL|macro|DM_PARTIAL_REGISTER_SPACING
mdefine_line|#define DM_PARTIAL_REGISTER_SPACING 0x8
DECL|macro|A_DM_PARTIAL
mdefine_line|#define A_DM_PARTIAL(idx)&t;    (A_DM_PARTIAL_0 + ((idx) * DM_PARTIAL_REGISTER_SPACING))
macro_line|#endif /* 112x PASS1 */
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|A_DM_CRC_0
mdefine_line|#define A_DM_CRC_0&t;&t;    0x0010020b80
DECL|macro|A_DM_CRC_1
mdefine_line|#define A_DM_CRC_1&t;&t;    0x0010020b90
DECL|macro|DM_CRC_REGISTER_SPACING
mdefine_line|#define DM_CRC_REGISTER_SPACING&t;    0x10
DECL|macro|DM_CRC_NUM_CHANNELS
mdefine_line|#define DM_CRC_NUM_CHANNELS&t;    2
DECL|macro|A_DM_CRC_BASE
mdefine_line|#define A_DM_CRC_BASE(idx)&t;    (A_DM_CRC_0 + ((idx) * DM_CRC_REGISTER_SPACING))
DECL|macro|A_DM_CRC_REGISTER
mdefine_line|#define A_DM_CRC_REGISTER(idx,reg)  (A_DM_CRC_BASE(idx) + (reg))
DECL|macro|R_CRC_DEF_0
mdefine_line|#define R_CRC_DEF_0&t;&t;    0x00
DECL|macro|R_CTCP_DEF_0
mdefine_line|#define R_CTCP_DEF_0&t;&t;    0x08
macro_line|#endif /* 112x PASS1 */
multiline_comment|/*  *********************************************************************&n;    *  Physical Address Map&n;    ********************************************************************* */
DECL|macro|A_PHYS_MEMORY_0
mdefine_line|#define A_PHYS_MEMORY_0                 _SB_MAKE64(0x0000000000)
DECL|macro|A_PHYS_MEMORY_SIZE
mdefine_line|#define A_PHYS_MEMORY_SIZE              _SB_MAKE64((256*1024*1024))
DECL|macro|A_PHYS_SYSTEM_CTL
mdefine_line|#define A_PHYS_SYSTEM_CTL               _SB_MAKE64(0x0010000000)
DECL|macro|A_PHYS_IO_SYSTEM
mdefine_line|#define A_PHYS_IO_SYSTEM                _SB_MAKE64(0x0010060000)
DECL|macro|A_PHYS_GENBUS
mdefine_line|#define A_PHYS_GENBUS&t;&t;&t;_SB_MAKE64(0x0010090000)
DECL|macro|A_PHYS_GENBUS_END
mdefine_line|#define A_PHYS_GENBUS_END&t;&t;_SB_MAKE64(0x0040000000)
DECL|macro|A_PHYS_LDTPCI_IO_MATCH_BYTES_32
mdefine_line|#define A_PHYS_LDTPCI_IO_MATCH_BYTES_32 _SB_MAKE64(0x0040000000)
DECL|macro|A_PHYS_LDTPCI_IO_MATCH_BITS_32
mdefine_line|#define A_PHYS_LDTPCI_IO_MATCH_BITS_32  _SB_MAKE64(0x0060000000)
DECL|macro|A_PHYS_MEMORY_1
mdefine_line|#define A_PHYS_MEMORY_1                 _SB_MAKE64(0x0080000000)
DECL|macro|A_PHYS_MEMORY_2
mdefine_line|#define A_PHYS_MEMORY_2                 _SB_MAKE64(0x0090000000)
DECL|macro|A_PHYS_MEMORY_3
mdefine_line|#define A_PHYS_MEMORY_3                 _SB_MAKE64(0x00C0000000)
DECL|macro|A_PHYS_L2_CACHE_TEST
mdefine_line|#define A_PHYS_L2_CACHE_TEST            _SB_MAKE64(0x00D0000000)
DECL|macro|A_PHYS_LDT_SPECIAL_MATCH_BYTES
mdefine_line|#define A_PHYS_LDT_SPECIAL_MATCH_BYTES  _SB_MAKE64(0x00D8000000)
DECL|macro|A_PHYS_LDTPCI_IO_MATCH_BYTES
mdefine_line|#define A_PHYS_LDTPCI_IO_MATCH_BYTES    _SB_MAKE64(0x00DC000000)
DECL|macro|A_PHYS_LDTPCI_CFG_MATCH_BYTES
mdefine_line|#define A_PHYS_LDTPCI_CFG_MATCH_BYTES   _SB_MAKE64(0x00DE000000)
DECL|macro|A_PHYS_LDT_SPECIAL_MATCH_BITS
mdefine_line|#define A_PHYS_LDT_SPECIAL_MATCH_BITS   _SB_MAKE64(0x00F8000000)
DECL|macro|A_PHYS_LDTPCI_IO_MATCH_BITS
mdefine_line|#define A_PHYS_LDTPCI_IO_MATCH_BITS     _SB_MAKE64(0x00FC000000)
DECL|macro|A_PHYS_LDTPCI_CFG_MATCH_BITS
mdefine_line|#define A_PHYS_LDTPCI_CFG_MATCH_BITS    _SB_MAKE64(0x00FE000000)
DECL|macro|A_PHYS_MEMORY_EXP
mdefine_line|#define A_PHYS_MEMORY_EXP               _SB_MAKE64(0x0100000000)
DECL|macro|A_PHYS_MEMORY_EXP_SIZE
mdefine_line|#define A_PHYS_MEMORY_EXP_SIZE          _SB_MAKE64((508*1024*1024*1024))
DECL|macro|A_PHYS_LDT_EXP
mdefine_line|#define A_PHYS_LDT_EXP                  _SB_MAKE64(0x8000000000)
DECL|macro|A_PHYS_PCI_FULLACCESS_BYTES
mdefine_line|#define A_PHYS_PCI_FULLACCESS_BYTES     _SB_MAKE64(0xF000000000)
DECL|macro|A_PHYS_PCI_FULLACCESS_BITS
mdefine_line|#define A_PHYS_PCI_FULLACCESS_BITS      _SB_MAKE64(0xF100000000)
DECL|macro|A_PHYS_RESERVED
mdefine_line|#define A_PHYS_RESERVED                 _SB_MAKE64(0xF200000000)
DECL|macro|A_PHYS_RESERVED_SPECIAL_LDT
mdefine_line|#define A_PHYS_RESERVED_SPECIAL_LDT     _SB_MAKE64(0xFD00000000)
DECL|macro|A_PHYS_L2CACHE_WAY_SIZE
mdefine_line|#define A_PHYS_L2CACHE_WAY_SIZE         _SB_MAKE64(0x0000020000)
DECL|macro|PHYS_L2CACHE_NUM_WAYS
mdefine_line|#define PHYS_L2CACHE_NUM_WAYS           4
DECL|macro|A_PHYS_L2CACHE_TOTAL_SIZE
mdefine_line|#define A_PHYS_L2CACHE_TOTAL_SIZE       _SB_MAKE64(0x0000080000)
DECL|macro|A_PHYS_L2CACHE_WAY0
mdefine_line|#define A_PHYS_L2CACHE_WAY0             _SB_MAKE64(0x00D0180000)
DECL|macro|A_PHYS_L2CACHE_WAY1
mdefine_line|#define A_PHYS_L2CACHE_WAY1             _SB_MAKE64(0x00D01A0000)
DECL|macro|A_PHYS_L2CACHE_WAY2
mdefine_line|#define A_PHYS_L2CACHE_WAY2             _SB_MAKE64(0x00D01C0000)
DECL|macro|A_PHYS_L2CACHE_WAY3
mdefine_line|#define A_PHYS_L2CACHE_WAY3             _SB_MAKE64(0x00D01E0000)
macro_line|#endif
eof
