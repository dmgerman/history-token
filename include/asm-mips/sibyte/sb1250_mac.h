multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  MAC constants and macros&t;&t;&t;File: sb1250_mac.h&n;    *  &n;    *  This module contains constants and macros for the SB1250&squot;s&n;    *  ethernet controllers.&n;    *  &n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg (mpl@broadcom.com)&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_MAC_H
DECL|macro|_SB1250_MAC_H
mdefine_line|#define _SB1250_MAC_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/*  *********************************************************************&n;    *  Ethernet MAC Registers&n;    ********************************************************************* */
multiline_comment|/*&n; * MAC Configuration Register (Table 9-13)&n; * Register: MAC_CFG_0&n; * Register: MAC_CFG_1&n; * Register: MAC_CFG_2&n; */
DECL|macro|M_MAC_RESERVED0
mdefine_line|#define M_MAC_RESERVED0             _SB_MAKEMASK1(0)
DECL|macro|M_MAC_TX_HOLD_SOP_EN
mdefine_line|#define M_MAC_TX_HOLD_SOP_EN        _SB_MAKEMASK1(1)
DECL|macro|M_MAC_RETRY_EN
mdefine_line|#define M_MAC_RETRY_EN              _SB_MAKEMASK1(2)
DECL|macro|M_MAC_RET_DRPREQ_EN
mdefine_line|#define M_MAC_RET_DRPREQ_EN         _SB_MAKEMASK1(3)
DECL|macro|M_MAC_RET_UFL_EN
mdefine_line|#define M_MAC_RET_UFL_EN            _SB_MAKEMASK1(4)
DECL|macro|M_MAC_BURST_EN
mdefine_line|#define M_MAC_BURST_EN              _SB_MAKEMASK1(5)
DECL|macro|S_MAC_TX_PAUSE
mdefine_line|#define S_MAC_TX_PAUSE              _SB_MAKE64(6)
DECL|macro|M_MAC_TX_PAUSE_CNT
mdefine_line|#define M_MAC_TX_PAUSE_CNT          _SB_MAKEMASK(3,S_MAC_TX_PAUSE)
DECL|macro|V_MAC_TX_PAUSE_CNT
mdefine_line|#define V_MAC_TX_PAUSE_CNT(x)       _SB_MAKEVALUE(x,S_MAC_TX_PAUSE)
DECL|macro|K_MAC_TX_PAUSE_CNT_512
mdefine_line|#define K_MAC_TX_PAUSE_CNT_512      0
DECL|macro|K_MAC_TX_PAUSE_CNT_1K
mdefine_line|#define K_MAC_TX_PAUSE_CNT_1K       1
DECL|macro|K_MAC_TX_PAUSE_CNT_2K
mdefine_line|#define K_MAC_TX_PAUSE_CNT_2K       2
DECL|macro|K_MAC_TX_PAUSE_CNT_4K
mdefine_line|#define K_MAC_TX_PAUSE_CNT_4K       3
DECL|macro|K_MAC_TX_PAUSE_CNT_8K
mdefine_line|#define K_MAC_TX_PAUSE_CNT_8K       4
DECL|macro|K_MAC_TX_PAUSE_CNT_16K
mdefine_line|#define K_MAC_TX_PAUSE_CNT_16K      5
DECL|macro|K_MAC_TX_PAUSE_CNT_32K
mdefine_line|#define K_MAC_TX_PAUSE_CNT_32K      6
DECL|macro|K_MAC_TX_PAUSE_CNT_64K
mdefine_line|#define K_MAC_TX_PAUSE_CNT_64K      7
DECL|macro|V_MAC_TX_PAUSE_CNT_512
mdefine_line|#define V_MAC_TX_PAUSE_CNT_512      V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_512)
DECL|macro|V_MAC_TX_PAUSE_CNT_1K
mdefine_line|#define V_MAC_TX_PAUSE_CNT_1K       V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_1K)
DECL|macro|V_MAC_TX_PAUSE_CNT_2K
mdefine_line|#define V_MAC_TX_PAUSE_CNT_2K       V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_2K)
DECL|macro|V_MAC_TX_PAUSE_CNT_4K
mdefine_line|#define V_MAC_TX_PAUSE_CNT_4K       V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_4K)
DECL|macro|V_MAC_TX_PAUSE_CNT_8K
mdefine_line|#define V_MAC_TX_PAUSE_CNT_8K       V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_8K)
DECL|macro|V_MAC_TX_PAUSE_CNT_16K
mdefine_line|#define V_MAC_TX_PAUSE_CNT_16K      V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_16K)
DECL|macro|V_MAC_TX_PAUSE_CNT_32K
mdefine_line|#define V_MAC_TX_PAUSE_CNT_32K      V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_32K)
DECL|macro|V_MAC_TX_PAUSE_CNT_64K
mdefine_line|#define V_MAC_TX_PAUSE_CNT_64K      V_MAC_TX_PAUSE_CNT(K_MAC_TX_PAUSE_CNT_64K)
DECL|macro|M_MAC_RESERVED1
mdefine_line|#define M_MAC_RESERVED1             _SB_MAKEMASK(8,9)
DECL|macro|M_MAC_AP_STAT_EN
mdefine_line|#define M_MAC_AP_STAT_EN            _SB_MAKEMASK1(17)
DECL|macro|M_MAC_RESERVED2
mdefine_line|#define M_MAC_RESERVED2&t;&t;    _SB_MAKEMASK1(18)
DECL|macro|M_MAC_DRP_ERRPKT_EN
mdefine_line|#define M_MAC_DRP_ERRPKT_EN         _SB_MAKEMASK1(19)
DECL|macro|M_MAC_DRP_FCSERRPKT_EN
mdefine_line|#define M_MAC_DRP_FCSERRPKT_EN      _SB_MAKEMASK1(20)
DECL|macro|M_MAC_DRP_CODEERRPKT_EN
mdefine_line|#define M_MAC_DRP_CODEERRPKT_EN     _SB_MAKEMASK1(21)
DECL|macro|M_MAC_DRP_DRBLERRPKT_EN
mdefine_line|#define M_MAC_DRP_DRBLERRPKT_EN     _SB_MAKEMASK1(22)
DECL|macro|M_MAC_DRP_RNTPKT_EN
mdefine_line|#define M_MAC_DRP_RNTPKT_EN         _SB_MAKEMASK1(23)
DECL|macro|M_MAC_DRP_OSZPKT_EN
mdefine_line|#define M_MAC_DRP_OSZPKT_EN         _SB_MAKEMASK1(24)
DECL|macro|M_MAC_DRP_LENERRPKT_EN
mdefine_line|#define M_MAC_DRP_LENERRPKT_EN      _SB_MAKEMASK1(25)
DECL|macro|M_MAC_RESERVED3
mdefine_line|#define M_MAC_RESERVED3             _SB_MAKEMASK(6,26)
DECL|macro|M_MAC_BYPASS_SEL
mdefine_line|#define M_MAC_BYPASS_SEL            _SB_MAKEMASK1(32)
DECL|macro|M_MAC_HDX_EN
mdefine_line|#define M_MAC_HDX_EN                _SB_MAKEMASK1(33)
DECL|macro|S_MAC_SPEED_SEL
mdefine_line|#define S_MAC_SPEED_SEL             _SB_MAKE64(34)
DECL|macro|M_MAC_SPEED_SEL
mdefine_line|#define M_MAC_SPEED_SEL             _SB_MAKEMASK(2,S_MAC_SPEED_SEL)
DECL|macro|V_MAC_SPEED_SEL
mdefine_line|#define V_MAC_SPEED_SEL(x)&t;    _SB_MAKEVALUE(x,S_MAC_SPEED_SEL)
DECL|macro|G_MAC_SPEED_SEL
mdefine_line|#define G_MAC_SPEED_SEL(x)&t;    _SB_GETVALUE(x,S_MAC_SPEED_SEL,M_MAC_SPEED_SEL)
DECL|macro|K_MAC_SPEED_SEL_10MBPS
mdefine_line|#define K_MAC_SPEED_SEL_10MBPS      0
DECL|macro|K_MAC_SPEED_SEL_100MBPS
mdefine_line|#define K_MAC_SPEED_SEL_100MBPS     1
DECL|macro|K_MAC_SPEED_SEL_1000MBPS
mdefine_line|#define K_MAC_SPEED_SEL_1000MBPS    2
DECL|macro|K_MAC_SPEED_SEL_RESERVED
mdefine_line|#define K_MAC_SPEED_SEL_RESERVED    3
DECL|macro|V_MAC_SPEED_SEL_10MBPS
mdefine_line|#define V_MAC_SPEED_SEL_10MBPS      V_MAC_SPEED_SEL(K_MAC_SPEED_SEL_10MBPS)
DECL|macro|V_MAC_SPEED_SEL_100MBPS
mdefine_line|#define V_MAC_SPEED_SEL_100MBPS     V_MAC_SPEED_SEL(K_MAC_SPEED_SEL_100MBPS)
DECL|macro|V_MAC_SPEED_SEL_1000MBPS
mdefine_line|#define V_MAC_SPEED_SEL_1000MBPS    V_MAC_SPEED_SEL(K_MAC_SPEED_SEL_1000MBPS)
DECL|macro|V_MAC_SPEED_SEL_RESERVED
mdefine_line|#define V_MAC_SPEED_SEL_RESERVED    V_MAC_SPEED_SEL(K_MAC_SPEED_SEL_RESERVED)
DECL|macro|M_MAC_TX_CLK_EDGE_SEL
mdefine_line|#define M_MAC_TX_CLK_EDGE_SEL       _SB_MAKEMASK1(36)
DECL|macro|M_MAC_LOOPBACK_SEL
mdefine_line|#define M_MAC_LOOPBACK_SEL          _SB_MAKEMASK1(37)
DECL|macro|M_MAC_FAST_SYNC
mdefine_line|#define M_MAC_FAST_SYNC             _SB_MAKEMASK1(38)
DECL|macro|M_MAC_SS_EN
mdefine_line|#define M_MAC_SS_EN                 _SB_MAKEMASK1(39)
DECL|macro|S_MAC_BYPASS_CFG
mdefine_line|#define S_MAC_BYPASS_CFG&t;    _SB_MAKE64(40)
DECL|macro|M_MAC_BYPASS_CFG
mdefine_line|#define M_MAC_BYPASS_CFG            _SB_MAKEMASK(2,S_MAC_BYPASS_CFG)
DECL|macro|V_MAC_BYPASS_CFG
mdefine_line|#define V_MAC_BYPASS_CFG(x)         _SB_MAKEVALUE(x,S_MAC_BYPASS_CFG)
DECL|macro|G_MAC_BYPASS_CFG
mdefine_line|#define G_MAC_BYPASS_CFG(x)         _SB_GETVALUE(x,S_MAC_BYPASS_CFG,M_MAC_BYPASS_CFG)
DECL|macro|K_MAC_BYPASS_GMII
mdefine_line|#define K_MAC_BYPASS_GMII&t;    0
DECL|macro|K_MAC_BYPASS_ENCODED
mdefine_line|#define K_MAC_BYPASS_ENCODED        1
DECL|macro|K_MAC_BYPASS_SOP
mdefine_line|#define K_MAC_BYPASS_SOP            2
DECL|macro|K_MAC_BYPASS_EOP
mdefine_line|#define K_MAC_BYPASS_EOP            3
DECL|macro|M_MAC_BYPASS_16
mdefine_line|#define M_MAC_BYPASS_16             _SB_MAKEMASK1(42)
DECL|macro|M_MAC_BYPASS_FCS_CHK
mdefine_line|#define M_MAC_BYPASS_FCS_CHK&t;    _SB_MAKEMASK1(43)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_MAC_RX_CH_SEL_MSB
mdefine_line|#define M_MAC_RX_CH_SEL_MSB&t;    _SB_MAKEMASK1(44)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_MAC_SPLIT_CH_SEL
mdefine_line|#define M_MAC_SPLIT_CH_SEL&t;    _SB_MAKEMASK1(45)
macro_line|#endif /* 112x PASS1 */
DECL|macro|S_MAC_BYPASS_IFG
mdefine_line|#define S_MAC_BYPASS_IFG            _SB_MAKE64(46)
DECL|macro|M_MAC_BYPASS_IFG
mdefine_line|#define M_MAC_BYPASS_IFG            _SB_MAKEMASK(8,S_MAC_BYPASS_IFG)
DECL|macro|V_MAC_BYPASS_IFG
mdefine_line|#define V_MAC_BYPASS_IFG(x)&t;    _SB_MAKEVALUE(x,S_MAC_BYPASS_IFG)
DECL|macro|G_MAC_BYPASS_IFG
mdefine_line|#define G_MAC_BYPASS_IFG(x)&t;    _SB_GETVALUE(x,S_MAC_BYPASS_IFG,M_MAC_BYPASS_IFG)
DECL|macro|K_MAC_FC_CMD_DISABLED
mdefine_line|#define K_MAC_FC_CMD_DISABLED       0
DECL|macro|K_MAC_FC_CMD_ENABLED
mdefine_line|#define K_MAC_FC_CMD_ENABLED        1
DECL|macro|K_MAC_FC_CMD_ENAB_FALSECARR
mdefine_line|#define K_MAC_FC_CMD_ENAB_FALSECARR 2
DECL|macro|V_MAC_FC_CMD_DISABLED
mdefine_line|#define V_MAC_FC_CMD_DISABLED       V_MAC_FC_CMD(K_MAC_FC_CMD_DISABLED)
DECL|macro|V_MAC_FC_CMD_ENABLED
mdefine_line|#define V_MAC_FC_CMD_ENABLED        V_MAC_FC_CMD(K_MAC_FC_CMD_ENABLED)
DECL|macro|V_MAC_FC_CMD_ENAB_FALSECARR
mdefine_line|#define V_MAC_FC_CMD_ENAB_FALSECARR V_MAC_FC_CMD(K_MAC_FC_CMD_ENAB_FALSECARR)
DECL|macro|M_MAC_FC_SEL
mdefine_line|#define M_MAC_FC_SEL                _SB_MAKEMASK1(54)
DECL|macro|S_MAC_FC_CMD
mdefine_line|#define S_MAC_FC_CMD                _SB_MAKE64(55)
DECL|macro|M_MAC_FC_CMD
mdefine_line|#define M_MAC_FC_CMD                _SB_MAKEMASK(2,S_MAC_FC_CMD)
DECL|macro|V_MAC_FC_CMD
mdefine_line|#define V_MAC_FC_CMD(x)&t;            _SB_MAKEVALUE(x,S_MAC_FC_CMD)
DECL|macro|G_MAC_FC_CMD
mdefine_line|#define G_MAC_FC_CMD(x)&t;            _SB_GETVALUE(x,S_MAC_FC_CMD,M_MAC_FC_CMD)
DECL|macro|S_MAC_RX_CH_SEL
mdefine_line|#define S_MAC_RX_CH_SEL             _SB_MAKE64(57)
DECL|macro|M_MAC_RX_CH_SEL
mdefine_line|#define M_MAC_RX_CH_SEL             _SB_MAKEMASK(7,S_MAC_RX_CH_SEL)
DECL|macro|V_MAC_RX_CH_SEL
mdefine_line|#define V_MAC_RX_CH_SEL(x)          _SB_MAKEVALUE(x,S_MAC_RX_CH_SEL)
DECL|macro|G_MAC_RX_CH_SEL
mdefine_line|#define G_MAC_RX_CH_SEL(x)          _SB_GETVALUE(x,S_MAC_RX_CH_SEL,M_MAC_RX_CH_SEL)
multiline_comment|/*&n; * MAC Enable Registers&n; * Register: MAC_ENABLE_0&n; * Register: MAC_ENABLE_1&n; * Register: MAC_ENABLE_2&n; */
DECL|macro|M_MAC_RXDMA_EN0
mdefine_line|#define M_MAC_RXDMA_EN0&t;            _SB_MAKEMASK1(0)
DECL|macro|M_MAC_RXDMA_EN1
mdefine_line|#define M_MAC_RXDMA_EN1&t;            _SB_MAKEMASK1(1)
DECL|macro|M_MAC_TXDMA_EN0
mdefine_line|#define M_MAC_TXDMA_EN0&t;            _SB_MAKEMASK1(4)
DECL|macro|M_MAC_TXDMA_EN1
mdefine_line|#define M_MAC_TXDMA_EN1&t;            _SB_MAKEMASK1(5)
DECL|macro|M_MAC_PORT_RESET
mdefine_line|#define M_MAC_PORT_RESET            _SB_MAKEMASK1(8)
DECL|macro|M_MAC_RX_ENABLE
mdefine_line|#define M_MAC_RX_ENABLE             _SB_MAKEMASK1(10)
DECL|macro|M_MAC_TX_ENABLE
mdefine_line|#define M_MAC_TX_ENABLE             _SB_MAKEMASK1(11)
DECL|macro|M_MAC_BYP_RX_ENABLE
mdefine_line|#define M_MAC_BYP_RX_ENABLE         _SB_MAKEMASK1(12)
DECL|macro|M_MAC_BYP_TX_ENABLE
mdefine_line|#define M_MAC_BYP_TX_ENABLE         _SB_MAKEMASK1(13)
multiline_comment|/*&n; * MAC DMA Control Register&n; * Register: MAC_TXD_CTL_0&n; * Register: MAC_TXD_CTL_1&n; * Register: MAC_TXD_CTL_2&n; */
DECL|macro|S_MAC_TXD_WEIGHT0
mdefine_line|#define S_MAC_TXD_WEIGHT0&t;    _SB_MAKE64(0)
DECL|macro|M_MAC_TXD_WEIGHT0
mdefine_line|#define M_MAC_TXD_WEIGHT0&t;    _SB_MAKEMASK(4,S_MAC_TXD_WEIGHT0)
DECL|macro|V_MAC_TXD_WEIGHT0
mdefine_line|#define V_MAC_TXD_WEIGHT0(x)        _SB_MAKEVALUE(x,S_MAC_TXD_WEIGHT0)
DECL|macro|G_MAC_TXD_WEIGHT0
mdefine_line|#define G_MAC_TXD_WEIGHT0(x)        _SB_GETVALUE(x,S_MAC_TXD_WEIGHT0,M_MAC_TXD_WEIGHT0)
DECL|macro|S_MAC_TXD_WEIGHT1
mdefine_line|#define S_MAC_TXD_WEIGHT1&t;    _SB_MAKE64(4)
DECL|macro|M_MAC_TXD_WEIGHT1
mdefine_line|#define M_MAC_TXD_WEIGHT1&t;    _SB_MAKEMASK(4,S_MAC_TXD_WEIGHT1)
DECL|macro|V_MAC_TXD_WEIGHT1
mdefine_line|#define V_MAC_TXD_WEIGHT1(x)        _SB_MAKEVALUE(x,S_MAC_TXD_WEIGHT1)
DECL|macro|G_MAC_TXD_WEIGHT1
mdefine_line|#define G_MAC_TXD_WEIGHT1(x)        _SB_GETVALUE(x,S_MAC_TXD_WEIGHT1,M_MAC_TXD_WEIGHT1)
multiline_comment|/*&n; * MAC Fifo Threshhold registers (Table 9-14)&n; * Register: MAC_THRSH_CFG_0&n; * Register: MAC_THRSH_CFG_1&n; * Register: MAC_THRSH_CFG_2&n; */
DECL|macro|S_MAC_TX_WR_THRSH
mdefine_line|#define S_MAC_TX_WR_THRSH           _SB_MAKE64(0)
macro_line|#if SIBYTE_HDR_FEATURE_UP_TO(1250, PASS1)
multiline_comment|/* XXX: Can&squot;t enable, as it has the same name as a pass2+ define below.  */
multiline_comment|/* #define M_MAC_TX_WR_THRSH           _SB_MAKEMASK(6,S_MAC_TX_WR_THRSH) */
macro_line|#endif /* up to 1250 PASS1 */
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_MAC_TX_WR_THRSH
mdefine_line|#define M_MAC_TX_WR_THRSH           _SB_MAKEMASK(7,S_MAC_TX_WR_THRSH)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|V_MAC_TX_WR_THRSH
mdefine_line|#define V_MAC_TX_WR_THRSH(x)        _SB_MAKEVALUE(x,S_MAC_TX_WR_THRSH)
DECL|macro|G_MAC_TX_WR_THRSH
mdefine_line|#define G_MAC_TX_WR_THRSH(x)        _SB_GETVALUE(x,S_MAC_TX_WR_THRSH,M_MAC_TX_WR_THRSH)
DECL|macro|S_MAC_TX_RD_THRSH
mdefine_line|#define S_MAC_TX_RD_THRSH           _SB_MAKE64(8)
macro_line|#if SIBYTE_HDR_FEATURE_UP_TO(1250, PASS1)
multiline_comment|/* XXX: Can&squot;t enable, as it has the same name as a pass2+ define below.  */
multiline_comment|/* #define M_MAC_TX_RD_THRSH           _SB_MAKEMASK(6,S_MAC_TX_RD_THRSH) */
macro_line|#endif /* up to 1250 PASS1 */
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_MAC_TX_RD_THRSH
mdefine_line|#define M_MAC_TX_RD_THRSH           _SB_MAKEMASK(7,S_MAC_TX_RD_THRSH)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|V_MAC_TX_RD_THRSH
mdefine_line|#define V_MAC_TX_RD_THRSH(x)        _SB_MAKEVALUE(x,S_MAC_TX_RD_THRSH)
DECL|macro|G_MAC_TX_RD_THRSH
mdefine_line|#define G_MAC_TX_RD_THRSH(x)        _SB_GETVALUE(x,S_MAC_TX_RD_THRSH,M_MAC_TX_RD_THRSH)
DECL|macro|S_MAC_TX_RL_THRSH
mdefine_line|#define S_MAC_TX_RL_THRSH           _SB_MAKE64(16)
DECL|macro|M_MAC_TX_RL_THRSH
mdefine_line|#define M_MAC_TX_RL_THRSH           _SB_MAKEMASK(4,S_MAC_TX_RL_THRSH)
DECL|macro|V_MAC_TX_RL_THRSH
mdefine_line|#define V_MAC_TX_RL_THRSH(x)        _SB_MAKEVALUE(x,S_MAC_TX_RL_THRSH)
DECL|macro|G_MAC_TX_RL_THRSH
mdefine_line|#define G_MAC_TX_RL_THRSH(x)        _SB_GETVALUE(x,S_MAC_TX_RL_THRSH,M_MAC_TX_RL_THRSH)
DECL|macro|S_MAC_RX_PL_THRSH
mdefine_line|#define S_MAC_RX_PL_THRSH           _SB_MAKE64(24)
DECL|macro|M_MAC_RX_PL_THRSH
mdefine_line|#define M_MAC_RX_PL_THRSH           _SB_MAKEMASK(6,S_MAC_RX_PL_THRSH)
DECL|macro|V_MAC_RX_PL_THRSH
mdefine_line|#define V_MAC_RX_PL_THRSH(x)        _SB_MAKEVALUE(x,S_MAC_RX_PL_THRSH)
DECL|macro|G_MAC_RX_PL_THRSH
mdefine_line|#define G_MAC_RX_PL_THRSH(x)        _SB_GETVALUE(x,S_MAC_RX_PL_THRSH,M_MAC_RX_PL_THRSH)
DECL|macro|S_MAC_RX_RD_THRSH
mdefine_line|#define S_MAC_RX_RD_THRSH           _SB_MAKE64(32)
DECL|macro|M_MAC_RX_RD_THRSH
mdefine_line|#define M_MAC_RX_RD_THRSH           _SB_MAKEMASK(6,S_MAC_RX_RD_THRSH)
DECL|macro|V_MAC_RX_RD_THRSH
mdefine_line|#define V_MAC_RX_RD_THRSH(x)        _SB_MAKEVALUE(x,S_MAC_RX_RD_THRSH)
DECL|macro|G_MAC_RX_RD_THRSH
mdefine_line|#define G_MAC_RX_RD_THRSH(x)        _SB_GETVALUE(x,S_MAC_RX_RD_THRSH,M_MAC_RX_RD_THRSH)
DECL|macro|S_MAC_RX_RL_THRSH
mdefine_line|#define S_MAC_RX_RL_THRSH           _SB_MAKE64(40)
DECL|macro|M_MAC_RX_RL_THRSH
mdefine_line|#define M_MAC_RX_RL_THRSH           _SB_MAKEMASK(6,S_MAC_RX_RL_THRSH)
DECL|macro|V_MAC_RX_RL_THRSH
mdefine_line|#define V_MAC_RX_RL_THRSH(x)        _SB_MAKEVALUE(x,S_MAC_RX_RL_THRSH)
DECL|macro|G_MAC_RX_RL_THRSH
mdefine_line|#define G_MAC_RX_RL_THRSH(x)        _SB_GETVALUE(x,S_MAC_RX_RL_THRSH,M_MAC_RX_RL_THRSH)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_MAC_ENC_FC_THRSH
mdefine_line|#define S_MAC_ENC_FC_THRSH           _SB_MAKE64(56)
DECL|macro|M_MAC_ENC_FC_THRSH
mdefine_line|#define M_MAC_ENC_FC_THRSH           _SB_MAKEMASK(6,S_MAC_ENC_FC_THRSH)
DECL|macro|V_MAC_ENC_FC_THRSH
mdefine_line|#define V_MAC_ENC_FC_THRSH(x)        _SB_MAKEVALUE(x,S_MAC_ENC_FC_THRSH)
DECL|macro|G_MAC_ENC_FC_THRSH
mdefine_line|#define G_MAC_ENC_FC_THRSH(x)        _SB_GETVALUE(x,S_MAC_ENC_FC_THRSH,M_MAC_ENC_FC_THRSH)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/*&n; * MAC Frame Configuration Registers (Table 9-15)&n; * Register: MAC_FRAME_CFG_0&n; * Register: MAC_FRAME_CFG_1&n; * Register: MAC_FRAME_CFG_2&n; */
multiline_comment|/* XXXCGD: ??? Unused in pass2? */
DECL|macro|S_MAC_IFG_RX
mdefine_line|#define S_MAC_IFG_RX                _SB_MAKE64(0)
DECL|macro|M_MAC_IFG_RX
mdefine_line|#define M_MAC_IFG_RX                _SB_MAKEMASK(6,S_MAC_IFG_RX)
DECL|macro|V_MAC_IFG_RX
mdefine_line|#define V_MAC_IFG_RX(x)             _SB_MAKEVALUE(x,S_MAC_IFG_RX)
DECL|macro|G_MAC_IFG_RX
mdefine_line|#define G_MAC_IFG_RX(x)             _SB_GETVALUE(x,S_MAC_IFG_RX,M_MAC_IFG_RX)
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_MAC_PRE_LEN
mdefine_line|#define S_MAC_PRE_LEN               _SB_MAKE64(0)
DECL|macro|M_MAC_PRE_LEN
mdefine_line|#define M_MAC_PRE_LEN               _SB_MAKEMASK(6,S_MAC_PRE_LEN)
DECL|macro|V_MAC_PRE_LEN
mdefine_line|#define V_MAC_PRE_LEN(x)            _SB_MAKEVALUE(x,S_MAC_PRE_LEN)
DECL|macro|G_MAC_PRE_LEN
mdefine_line|#define G_MAC_PRE_LEN(x)            _SB_GETVALUE(x,S_MAC_PRE_LEN,M_MAC_PRE_LEN)
macro_line|#endif /* 112x PASS1 */
DECL|macro|S_MAC_IFG_TX
mdefine_line|#define S_MAC_IFG_TX                _SB_MAKE64(6)
DECL|macro|M_MAC_IFG_TX
mdefine_line|#define M_MAC_IFG_TX                _SB_MAKEMASK(6,S_MAC_IFG_TX)
DECL|macro|V_MAC_IFG_TX
mdefine_line|#define V_MAC_IFG_TX(x)             _SB_MAKEVALUE(x,S_MAC_IFG_TX)
DECL|macro|G_MAC_IFG_TX
mdefine_line|#define G_MAC_IFG_TX(x)             _SB_GETVALUE(x,S_MAC_IFG_TX,M_MAC_IFG_TX)
DECL|macro|S_MAC_IFG_THRSH
mdefine_line|#define S_MAC_IFG_THRSH             _SB_MAKE64(12)
DECL|macro|M_MAC_IFG_THRSH
mdefine_line|#define M_MAC_IFG_THRSH             _SB_MAKEMASK(6,S_MAC_IFG_THRSH)
DECL|macro|V_MAC_IFG_THRSH
mdefine_line|#define V_MAC_IFG_THRSH(x)          _SB_MAKEVALUE(x,S_MAC_IFG_THRSH)
DECL|macro|G_MAC_IFG_THRSH
mdefine_line|#define G_MAC_IFG_THRSH(x)          _SB_GETVALUE(x,S_MAC_IFG_THRSH,M_MAC_IFG_THRSH)
DECL|macro|S_MAC_BACKOFF_SEL
mdefine_line|#define S_MAC_BACKOFF_SEL           _SB_MAKE64(18)
DECL|macro|M_MAC_BACKOFF_SEL
mdefine_line|#define M_MAC_BACKOFF_SEL           _SB_MAKEMASK(4,S_MAC_BACKOFF_SEL)
DECL|macro|V_MAC_BACKOFF_SEL
mdefine_line|#define V_MAC_BACKOFF_SEL(x)        _SB_MAKEVALUE(x,S_MAC_BACKOFF_SEL)
DECL|macro|G_MAC_BACKOFF_SEL
mdefine_line|#define G_MAC_BACKOFF_SEL(x)        _SB_GETVALUE(x,S_MAC_BACKOFF_SEL,M_MAC_BACKOFF_SEL)
DECL|macro|S_MAC_LFSR_SEED
mdefine_line|#define S_MAC_LFSR_SEED             _SB_MAKE64(22)
DECL|macro|M_MAC_LFSR_SEED
mdefine_line|#define M_MAC_LFSR_SEED             _SB_MAKEMASK(8,S_MAC_LFSR_SEED)
DECL|macro|V_MAC_LFSR_SEED
mdefine_line|#define V_MAC_LFSR_SEED(x)          _SB_MAKEVALUE(x,S_MAC_LFSR_SEED)
DECL|macro|G_MAC_LFSR_SEED
mdefine_line|#define G_MAC_LFSR_SEED(x)          _SB_GETVALUE(x,S_MAC_LFSR_SEED,M_MAC_LFSR_SEED)
DECL|macro|S_MAC_SLOT_SIZE
mdefine_line|#define S_MAC_SLOT_SIZE             _SB_MAKE64(30)
DECL|macro|M_MAC_SLOT_SIZE
mdefine_line|#define M_MAC_SLOT_SIZE             _SB_MAKEMASK(10,S_MAC_SLOT_SIZE)
DECL|macro|V_MAC_SLOT_SIZE
mdefine_line|#define V_MAC_SLOT_SIZE(x)          _SB_MAKEVALUE(x,S_MAC_SLOT_SIZE)
DECL|macro|G_MAC_SLOT_SIZE
mdefine_line|#define G_MAC_SLOT_SIZE(x)          _SB_GETVALUE(x,S_MAC_SLOT_SIZE,M_MAC_SLOT_SIZE)
DECL|macro|S_MAC_MIN_FRAMESZ
mdefine_line|#define S_MAC_MIN_FRAMESZ           _SB_MAKE64(40)
DECL|macro|M_MAC_MIN_FRAMESZ
mdefine_line|#define M_MAC_MIN_FRAMESZ           _SB_MAKEMASK(8,S_MAC_MIN_FRAMESZ)
DECL|macro|V_MAC_MIN_FRAMESZ
mdefine_line|#define V_MAC_MIN_FRAMESZ(x)        _SB_MAKEVALUE(x,S_MAC_MIN_FRAMESZ)
DECL|macro|G_MAC_MIN_FRAMESZ
mdefine_line|#define G_MAC_MIN_FRAMESZ(x)        _SB_GETVALUE(x,S_MAC_MIN_FRAMESZ,M_MAC_MIN_FRAMESZ)
DECL|macro|S_MAC_MAX_FRAMESZ
mdefine_line|#define S_MAC_MAX_FRAMESZ           _SB_MAKE64(48)
DECL|macro|M_MAC_MAX_FRAMESZ
mdefine_line|#define M_MAC_MAX_FRAMESZ           _SB_MAKEMASK(16,S_MAC_MAX_FRAMESZ)
DECL|macro|V_MAC_MAX_FRAMESZ
mdefine_line|#define V_MAC_MAX_FRAMESZ(x)        _SB_MAKEVALUE(x,S_MAC_MAX_FRAMESZ)
DECL|macro|G_MAC_MAX_FRAMESZ
mdefine_line|#define G_MAC_MAX_FRAMESZ(x)        _SB_GETVALUE(x,S_MAC_MAX_FRAMESZ,M_MAC_MAX_FRAMESZ)
multiline_comment|/*&n; * These constants are used to configure the fields within the Frame&n; * Configuration Register.  &n; */
DECL|macro|K_MAC_IFG_RX_10
mdefine_line|#define K_MAC_IFG_RX_10             _SB_MAKE64(0)&t;/* See table 176, not used */
DECL|macro|K_MAC_IFG_RX_100
mdefine_line|#define K_MAC_IFG_RX_100            _SB_MAKE64(0)
DECL|macro|K_MAC_IFG_RX_1000
mdefine_line|#define K_MAC_IFG_RX_1000           _SB_MAKE64(0)
DECL|macro|K_MAC_IFG_TX_10
mdefine_line|#define K_MAC_IFG_TX_10             _SB_MAKE64(20)
DECL|macro|K_MAC_IFG_TX_100
mdefine_line|#define K_MAC_IFG_TX_100            _SB_MAKE64(20)
DECL|macro|K_MAC_IFG_TX_1000
mdefine_line|#define K_MAC_IFG_TX_1000           _SB_MAKE64(8)
DECL|macro|K_MAC_IFG_THRSH_10
mdefine_line|#define K_MAC_IFG_THRSH_10          _SB_MAKE64(4)
DECL|macro|K_MAC_IFG_THRSH_100
mdefine_line|#define K_MAC_IFG_THRSH_100         _SB_MAKE64(4)
DECL|macro|K_MAC_IFG_THRSH_1000
mdefine_line|#define K_MAC_IFG_THRSH_1000        _SB_MAKE64(0)
DECL|macro|K_MAC_SLOT_SIZE_10
mdefine_line|#define K_MAC_SLOT_SIZE_10          _SB_MAKE64(0)
DECL|macro|K_MAC_SLOT_SIZE_100
mdefine_line|#define K_MAC_SLOT_SIZE_100         _SB_MAKE64(0)
DECL|macro|K_MAC_SLOT_SIZE_1000
mdefine_line|#define K_MAC_SLOT_SIZE_1000        _SB_MAKE64(0)
DECL|macro|V_MAC_IFG_RX_10
mdefine_line|#define V_MAC_IFG_RX_10        V_MAC_IFG_RX(K_MAC_IFG_RX_10)
DECL|macro|V_MAC_IFG_RX_100
mdefine_line|#define V_MAC_IFG_RX_100       V_MAC_IFG_RX(K_MAC_IFG_RX_100)
DECL|macro|V_MAC_IFG_RX_1000
mdefine_line|#define V_MAC_IFG_RX_1000      V_MAC_IFG_RX(K_MAC_IFG_RX_1000)
DECL|macro|V_MAC_IFG_TX_10
mdefine_line|#define V_MAC_IFG_TX_10        V_MAC_IFG_TX(K_MAC_IFG_TX_10)
DECL|macro|V_MAC_IFG_TX_100
mdefine_line|#define V_MAC_IFG_TX_100       V_MAC_IFG_TX(K_MAC_IFG_TX_100)
DECL|macro|V_MAC_IFG_TX_1000
mdefine_line|#define V_MAC_IFG_TX_1000      V_MAC_IFG_TX(K_MAC_IFG_TX_1000)
DECL|macro|V_MAC_IFG_THRSH_10
mdefine_line|#define V_MAC_IFG_THRSH_10     V_MAC_IFG_THRSH(K_MAC_IFG_THRSH_10)
DECL|macro|V_MAC_IFG_THRSH_100
mdefine_line|#define V_MAC_IFG_THRSH_100    V_MAC_IFG_THRSH(K_MAC_IFG_THRSH_100)
DECL|macro|V_MAC_IFG_THRSH_1000
mdefine_line|#define V_MAC_IFG_THRSH_1000   V_MAC_IFG_THRSH(K_MAC_IFG_THRSH_1000)
DECL|macro|V_MAC_SLOT_SIZE_10
mdefine_line|#define V_MAC_SLOT_SIZE_10     V_MAC_SLOT_SIZE(K_MAC_SLOT_SIZE_10)
DECL|macro|V_MAC_SLOT_SIZE_100
mdefine_line|#define V_MAC_SLOT_SIZE_100    V_MAC_SLOT_SIZE(K_MAC_SLOT_SIZE_100)
DECL|macro|V_MAC_SLOT_SIZE_1000
mdefine_line|#define V_MAC_SLOT_SIZE_1000   V_MAC_SLOT_SIZE(K_MAC_SLOT_SIZE_1000)
DECL|macro|K_MAC_MIN_FRAMESZ_FIFO
mdefine_line|#define K_MAC_MIN_FRAMESZ_FIFO      _SB_MAKE64(9)
DECL|macro|K_MAC_MIN_FRAMESZ_DEFAULT
mdefine_line|#define K_MAC_MIN_FRAMESZ_DEFAULT   _SB_MAKE64(64)
DECL|macro|K_MAC_MAX_FRAMESZ_DEFAULT
mdefine_line|#define K_MAC_MAX_FRAMESZ_DEFAULT   _SB_MAKE64(1518)
DECL|macro|K_MAC_MAX_FRAMESZ_JUMBO
mdefine_line|#define K_MAC_MAX_FRAMESZ_JUMBO     _SB_MAKE64(9216)
DECL|macro|V_MAC_MIN_FRAMESZ_FIFO
mdefine_line|#define V_MAC_MIN_FRAMESZ_FIFO      V_MAC_MIN_FRAMESZ(K_MAC_MIN_FRAMESZ_FIFO)
DECL|macro|V_MAC_MIN_FRAMESZ_DEFAULT
mdefine_line|#define V_MAC_MIN_FRAMESZ_DEFAULT   V_MAC_MIN_FRAMESZ(K_MAC_MIN_FRAMESZ_DEFAULT)
DECL|macro|V_MAC_MAX_FRAMESZ_DEFAULT
mdefine_line|#define V_MAC_MAX_FRAMESZ_DEFAULT   V_MAC_MAX_FRAMESZ(K_MAC_MAX_FRAMESZ_DEFAULT)
DECL|macro|V_MAC_MAX_FRAMESZ_JUMBO
mdefine_line|#define V_MAC_MAX_FRAMESZ_JUMBO     V_MAC_MAX_FRAMESZ(K_MAC_MAX_FRAMESZ_JUMBO)
multiline_comment|/*&n; * MAC VLAN Tag Registers (Table 9-16)&n; * Register: MAC_VLANTAG_0&n; * Register: MAC_VLANTAG_1&n; * Register: MAC_VLANTAG_2&n; */
DECL|macro|S_MAC_VLAN_TAG
mdefine_line|#define S_MAC_VLAN_TAG           _SB_MAKE64(0)
DECL|macro|M_MAC_VLAN_TAG
mdefine_line|#define M_MAC_VLAN_TAG           _SB_MAKEMASK(32,S_MAC_VLAN_TAG)
DECL|macro|V_MAC_VLAN_TAG
mdefine_line|#define V_MAC_VLAN_TAG(x)        _SB_MAKEVALUE(x,S_MAC_VLAN_TAG)
DECL|macro|G_MAC_VLAN_TAG
mdefine_line|#define G_MAC_VLAN_TAG(x)        _SB_GETVALUE(x,S_MAC_VLAN_TAG,M_MAC_VLAN_TAG)
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_MAC_TX_PKT_OFFSET
mdefine_line|#define S_MAC_TX_PKT_OFFSET      _SB_MAKE64(32)
DECL|macro|M_MAC_TX_PKT_OFFSET
mdefine_line|#define M_MAC_TX_PKT_OFFSET      _SB_MAKEMASK(8,S_MAC_TX_PKT_OFFSET)
DECL|macro|V_MAC_TX_PKT_OFFSET
mdefine_line|#define V_MAC_TX_PKT_OFFSET(x)   _SB_MAKEVALUE(x,S_MAC_TX_PKT_OFFSET)
DECL|macro|G_MAC_TX_PKT_OFFSET
mdefine_line|#define G_MAC_TX_PKT_OFFSET(x)   _SB_GETVALUE(x,S_MAC_TX_PKT_OFFSET,M_MAC_TX_PKT_OFFSET)
DECL|macro|S_MAC_TX_CRC_OFFSET
mdefine_line|#define S_MAC_TX_CRC_OFFSET      _SB_MAKE64(40)
DECL|macro|M_MAC_TX_CRC_OFFSET
mdefine_line|#define M_MAC_TX_CRC_OFFSET      _SB_MAKEMASK(8,S_MAC_TX_CRC_OFFSET)
DECL|macro|V_MAC_TX_CRC_OFFSET
mdefine_line|#define V_MAC_TX_CRC_OFFSET(x)   _SB_MAKEVALUE(x,S_MAC_TX_CRC_OFFSET)
DECL|macro|G_MAC_TX_CRC_OFFSET
mdefine_line|#define G_MAC_TX_CRC_OFFSET(x)   _SB_GETVALUE(x,S_MAC_TX_CRC_OFFSET,M_MAC_TX_CRC_OFFSET)
DECL|macro|M_MAC_CH_BASE_FC_EN
mdefine_line|#define M_MAC_CH_BASE_FC_EN      _SB_MAKEMASK1(48)
macro_line|#endif /* 112x PASS1 */
multiline_comment|/*&n; * MAC Status Registers (Table 9-17)&n; * Also used for the MAC Interrupt Mask Register (Table 9-18)&n; * Register: MAC_STATUS_0&n; * Register: MAC_STATUS_1&n; * Register: MAC_STATUS_2&n; * Register: MAC_INT_MASK_0&n; * Register: MAC_INT_MASK_1&n; * Register: MAC_INT_MASK_2&n; */
multiline_comment|/* &n; * Use these constants to shift the appropriate channel&n; * into the CH0 position so the same tests can be used&n; * on each channel.&n; */
DECL|macro|S_MAC_RX_CH0
mdefine_line|#define S_MAC_RX_CH0                _SB_MAKE64(0)
DECL|macro|S_MAC_RX_CH1
mdefine_line|#define S_MAC_RX_CH1                _SB_MAKE64(8)
DECL|macro|S_MAC_TX_CH0
mdefine_line|#define S_MAC_TX_CH0                _SB_MAKE64(16)
DECL|macro|S_MAC_TX_CH1
mdefine_line|#define S_MAC_TX_CH1                _SB_MAKE64(24)
DECL|macro|S_MAC_TXCHANNELS
mdefine_line|#define S_MAC_TXCHANNELS&t;    _SB_MAKE64(16)&t;/* this is 1st TX chan */
DECL|macro|S_MAC_CHANWIDTH
mdefine_line|#define S_MAC_CHANWIDTH             _SB_MAKE64(8)&t;/* bits between channels */
multiline_comment|/*&n; *  These are the same as RX channel 0.  The idea here&n; *  is that you&squot;ll use one of the &quot;S_&quot; things above&n; *  and pass just the six bits to a DMA-channel-specific ISR&n; */
DECL|macro|M_MAC_INT_CHANNEL
mdefine_line|#define M_MAC_INT_CHANNEL           _SB_MAKEMASK(8,0)
DECL|macro|M_MAC_INT_EOP_COUNT
mdefine_line|#define M_MAC_INT_EOP_COUNT         _SB_MAKEMASK1(0)
DECL|macro|M_MAC_INT_EOP_TIMER
mdefine_line|#define M_MAC_INT_EOP_TIMER         _SB_MAKEMASK1(1)
DECL|macro|M_MAC_INT_EOP_SEEN
mdefine_line|#define M_MAC_INT_EOP_SEEN          _SB_MAKEMASK1(2)
DECL|macro|M_MAC_INT_HWM
mdefine_line|#define M_MAC_INT_HWM               _SB_MAKEMASK1(3)
DECL|macro|M_MAC_INT_LWM
mdefine_line|#define M_MAC_INT_LWM               _SB_MAKEMASK1(4)
DECL|macro|M_MAC_INT_DSCR
mdefine_line|#define M_MAC_INT_DSCR              _SB_MAKEMASK1(5)
DECL|macro|M_MAC_INT_ERR
mdefine_line|#define M_MAC_INT_ERR               _SB_MAKEMASK1(6)
DECL|macro|M_MAC_INT_DZERO
mdefine_line|#define M_MAC_INT_DZERO             _SB_MAKEMASK1(7)&t;/* only for TX channels */
DECL|macro|M_MAC_INT_DROP
mdefine_line|#define M_MAC_INT_DROP              _SB_MAKEMASK1(7)&t;/* only for RX channels */
multiline_comment|/*&n; * In the following definitions we use ch (0/1) and txrx (TX=1, RX=0, see&n; * also DMA_TX/DMA_RX in sb_regs.h).&n; */
DECL|macro|S_MAC_STATUS_CH_OFFSET
mdefine_line|#define S_MAC_STATUS_CH_OFFSET(ch,txrx) _SB_MAKE64(((ch) + 2 * (txrx)) * S_MAC_CHANWIDTH)
DECL|macro|M_MAC_STATUS_CHANNEL
mdefine_line|#define M_MAC_STATUS_CHANNEL(ch,txrx)   _SB_MAKEVALUE(_SB_MAKEMASK(8,0),S_MAC_STATUS_CH_OFFSET(ch,txrx))
DECL|macro|M_MAC_STATUS_EOP_COUNT
mdefine_line|#define M_MAC_STATUS_EOP_COUNT(ch,txrx) _SB_MAKEVALUE(M_MAC_INT_EOP_COUNT,S_MAC_STATUS_CH_OFFSET(ch,txrx))
DECL|macro|M_MAC_STATUS_EOP_TIMER
mdefine_line|#define M_MAC_STATUS_EOP_TIMER(ch,txrx) _SB_MAKEVALUE(M_MAC_INT_EOP_TIMER,S_MAC_STATUS_CH_OFFSET(ch,txrx))
DECL|macro|M_MAC_STATUS_EOP_SEEN
mdefine_line|#define M_MAC_STATUS_EOP_SEEN(ch,txrx)  _SB_MAKEVALUE(M_MAC_INT_EOP_SEEN,S_MAC_STATUS_CH_OFFSET(ch,txrx))
DECL|macro|M_MAC_STATUS_HWM
mdefine_line|#define M_MAC_STATUS_HWM(ch,txrx)       _SB_MAKEVALUE(M_MAC_INT_HWM,S_MAC_STATUS_CH_OFFSET(ch,txrx))
DECL|macro|M_MAC_STATUS_LWM
mdefine_line|#define M_MAC_STATUS_LWM(ch,txrx)       _SB_MAKEVALUE(M_MAC_INT_LWM,S_MAC_STATUS_CH_OFFSET(ch,txrx))
DECL|macro|M_MAC_STATUS_DSCR
mdefine_line|#define M_MAC_STATUS_DSCR(ch,txrx)      _SB_MAKEVALUE(M_MAC_INT_DSCR,S_MAC_STATUS_CH_OFFSET(ch,txrx))
DECL|macro|M_MAC_STATUS_ERR
mdefine_line|#define M_MAC_STATUS_ERR(ch,txrx)       _SB_MAKEVALUE(M_MAC_INT_ERR,S_MAC_STATUS_CH_OFFSET(ch,txrx))
DECL|macro|M_MAC_STATUS_DZERO
mdefine_line|#define M_MAC_STATUS_DZERO(ch,txrx)     _SB_MAKEVALUE(M_MAC_INT_DZERO,S_MAC_STATUS_CH_OFFSET(ch,txrx))
DECL|macro|M_MAC_STATUS_DROP
mdefine_line|#define M_MAC_STATUS_DROP(ch,txrx)      _SB_MAKEVALUE(M_MAC_INT_DROP,S_MAC_STATUS_CH_OFFSET(ch,txrx))
DECL|macro|M_MAC_STATUS_OTHER_ERR
mdefine_line|#define M_MAC_STATUS_OTHER_ERR          _SB_MAKEVALUE(_SB_MAKEMASK(7,0),40)
DECL|macro|M_MAC_RX_UNDRFL
mdefine_line|#define M_MAC_RX_UNDRFL             _SB_MAKEMASK1(40)
DECL|macro|M_MAC_RX_OVRFL
mdefine_line|#define M_MAC_RX_OVRFL              _SB_MAKEMASK1(41)
DECL|macro|M_MAC_TX_UNDRFL
mdefine_line|#define M_MAC_TX_UNDRFL             _SB_MAKEMASK1(42)
DECL|macro|M_MAC_TX_OVRFL
mdefine_line|#define M_MAC_TX_OVRFL              _SB_MAKEMASK1(43)
DECL|macro|M_MAC_LTCOL_ERR
mdefine_line|#define M_MAC_LTCOL_ERR             _SB_MAKEMASK1(44)
DECL|macro|M_MAC_EXCOL_ERR
mdefine_line|#define M_MAC_EXCOL_ERR             _SB_MAKEMASK1(45)
DECL|macro|M_MAC_CNTR_OVRFL_ERR
mdefine_line|#define M_MAC_CNTR_OVRFL_ERR        _SB_MAKEMASK1(46)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_MAC_SPLIT_EN
mdefine_line|#define M_MAC_SPLIT_EN&t;&t;    _SB_MAKEMASK1(47) &t;/* interrupt mask only */
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|S_MAC_COUNTER_ADDR
mdefine_line|#define S_MAC_COUNTER_ADDR          _SB_MAKE64(47)
DECL|macro|M_MAC_COUNTER_ADDR
mdefine_line|#define M_MAC_COUNTER_ADDR          _SB_MAKEMASK(5,S_MAC_COUNTER_ADDR)
DECL|macro|V_MAC_COUNTER_ADDR
mdefine_line|#define V_MAC_COUNTER_ADDR(x)       _SB_MAKEVALUE(x,S_MAC_COUNTER_ADDR)
DECL|macro|G_MAC_COUNTER_ADDR
mdefine_line|#define G_MAC_COUNTER_ADDR(x)       _SB_GETVALUE(x,S_MAC_COUNTER_ADDR,M_MAC_COUNTER_ADDR)
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_MAC_TX_PAUSE_ON
mdefine_line|#define M_MAC_TX_PAUSE_ON&t;    _SB_MAKEMASK1(52)
macro_line|#endif /* 112x PASS1 */
multiline_comment|/*&n; * MAC Fifo Pointer Registers (Table 9-19)    [Debug register]&n; * Register: MAC_FIFO_PTRS_0&n; * Register: MAC_FIFO_PTRS_1&n; * Register: MAC_FIFO_PTRS_2&n; */
DECL|macro|S_MAC_TX_WRPTR
mdefine_line|#define S_MAC_TX_WRPTR              _SB_MAKE64(0)
DECL|macro|M_MAC_TX_WRPTR
mdefine_line|#define M_MAC_TX_WRPTR              _SB_MAKEMASK(6,S_MAC_TX_WRPTR)
DECL|macro|V_MAC_TX_WRPTR
mdefine_line|#define V_MAC_TX_WRPTR(x)           _SB_MAKEVALUE(x,S_MAC_TX_WRPTR)
DECL|macro|G_MAC_TX_WRPTR
mdefine_line|#define G_MAC_TX_WRPTR(x)           _SB_GETVALUE(x,S_MAC_TX_WRPTR,M_MAC_TX_WRPTR)
DECL|macro|S_MAC_TX_RDPTR
mdefine_line|#define S_MAC_TX_RDPTR              _SB_MAKE64(8)
DECL|macro|M_MAC_TX_RDPTR
mdefine_line|#define M_MAC_TX_RDPTR              _SB_MAKEMASK(6,S_MAC_TX_RDPTR)
DECL|macro|V_MAC_TX_RDPTR
mdefine_line|#define V_MAC_TX_RDPTR(x)           _SB_MAKEVALUE(x,S_MAC_TX_RDPTR)
DECL|macro|G_MAC_TX_RDPTR
mdefine_line|#define G_MAC_TX_RDPTR(x)           _SB_GETVALUE(x,S_MAC_TX_RDPTR,M_MAC_TX_RDPTR)
DECL|macro|S_MAC_RX_WRPTR
mdefine_line|#define S_MAC_RX_WRPTR              _SB_MAKE64(16)
DECL|macro|M_MAC_RX_WRPTR
mdefine_line|#define M_MAC_RX_WRPTR              _SB_MAKEMASK(6,S_MAC_RX_WRPTR)
DECL|macro|V_MAC_RX_WRPTR
mdefine_line|#define V_MAC_RX_WRPTR(x)           _SB_MAKEVALUE(x,S_MAC_RX_WRPTR)
DECL|macro|G_MAC_RX_WRPTR
mdefine_line|#define G_MAC_RX_WRPTR(x)           _SB_GETVALUE(x,S_MAC_RX_WRPTR,M_MAC_TX_WRPTR)
DECL|macro|S_MAC_RX_RDPTR
mdefine_line|#define S_MAC_RX_RDPTR              _SB_MAKE64(24)
DECL|macro|M_MAC_RX_RDPTR
mdefine_line|#define M_MAC_RX_RDPTR              _SB_MAKEMASK(6,S_MAC_RX_RDPTR)
DECL|macro|V_MAC_RX_RDPTR
mdefine_line|#define V_MAC_RX_RDPTR(x)           _SB_MAKEVALUE(x,S_MAC_RX_RDPTR)
DECL|macro|G_MAC_RX_RDPTR
mdefine_line|#define G_MAC_RX_RDPTR(x)           _SB_GETVALUE(x,S_MAC_RX_RDPTR,M_MAC_TX_RDPTR)
multiline_comment|/*&n; * MAC Fifo End Of Packet Count Registers (Table 9-20)  [Debug register]&n; * Register: MAC_EOPCNT_0&n; * Register: MAC_EOPCNT_1&n; * Register: MAC_EOPCNT_2&n; */
DECL|macro|S_MAC_TX_EOP_COUNTER
mdefine_line|#define S_MAC_TX_EOP_COUNTER        _SB_MAKE64(0)
DECL|macro|M_MAC_TX_EOP_COUNTER
mdefine_line|#define M_MAC_TX_EOP_COUNTER        _SB_MAKEMASK(6,S_MAC_TX_EOP_COUNTER)
DECL|macro|V_MAC_TX_EOP_COUNTER
mdefine_line|#define V_MAC_TX_EOP_COUNTER(x)     _SB_MAKEVALUE(x,S_MAC_TX_EOP_COUNTER)
DECL|macro|G_MAC_TX_EOP_COUNTER
mdefine_line|#define G_MAC_TX_EOP_COUNTER(x)     _SB_GETVALUE(x,S_MAC_TX_EOP_COUNTER,M_MAC_TX_EOP_COUNTER)
DECL|macro|S_MAC_RX_EOP_COUNTER
mdefine_line|#define S_MAC_RX_EOP_COUNTER        _SB_MAKE64(8)
DECL|macro|M_MAC_RX_EOP_COUNTER
mdefine_line|#define M_MAC_RX_EOP_COUNTER        _SB_MAKEMASK(6,S_MAC_RX_EOP_COUNTER)
DECL|macro|V_MAC_RX_EOP_COUNTER
mdefine_line|#define V_MAC_RX_EOP_COUNTER(x)     _SB_MAKEVALUE(x,S_MAC_RX_EOP_COUNTER)
DECL|macro|G_MAC_RX_EOP_COUNTER
mdefine_line|#define G_MAC_RX_EOP_COUNTER(x)     _SB_GETVALUE(x,S_MAC_RX_EOP_COUNTER,M_MAC_RX_EOP_COUNTER)
multiline_comment|/*&n; * MAC Recieve Address Filter Exact Match Registers (Table 9-21)&n; * Registers: MAC_ADDR0_0 through MAC_ADDR7_0&n; * Registers: MAC_ADDR0_1 through MAC_ADDR7_1&n; * Registers: MAC_ADDR0_2 through MAC_ADDR7_2&n; */
multiline_comment|/* No bitfields */
multiline_comment|/*&n; * MAC Receive Address Filter Mask Registers&n; * Registers: MAC_ADDRMASK0_0 and MAC_ADDRMASK0_1&n; * Registers: MAC_ADDRMASK1_0 and MAC_ADDRMASK1_1&n; * Registers: MAC_ADDRMASK2_0 and MAC_ADDRMASK2_1&n; */
multiline_comment|/* No bitfields */
multiline_comment|/*&n; * MAC Recieve Address Filter Hash Match Registers (Table 9-22)&n; * Registers: MAC_HASH0_0 through MAC_HASH7_0&n; * Registers: MAC_HASH0_1 through MAC_HASH7_1&n; * Registers: MAC_HASH0_2 through MAC_HASH7_2&n; */
multiline_comment|/* No bitfields */
multiline_comment|/*&n; * MAC Transmit Source Address Registers (Table 9-23)&n; * Register: MAC_ETHERNET_ADDR_0&n; * Register: MAC_ETHERNET_ADDR_1&n; * Register: MAC_ETHERNET_ADDR_2&n; */
multiline_comment|/* No bitfields */
multiline_comment|/*&n; * MAC Packet Type Configuration Register&n; * Register: MAC_TYPE_CFG_0&n; * Register: MAC_TYPE_CFG_1&n; * Register: MAC_TYPE_CFG_2&n; */
DECL|macro|S_TYPECFG_TYPESIZE
mdefine_line|#define S_TYPECFG_TYPESIZE      _SB_MAKE64(16)
DECL|macro|S_TYPECFG_TYPE0
mdefine_line|#define S_TYPECFG_TYPE0&t;&t;_SB_MAKE64(0)
DECL|macro|M_TYPECFG_TYPE0
mdefine_line|#define M_TYPECFG_TYPE0         _SB_MAKEMASK(16,S_TYPECFG_TYPE0)
DECL|macro|V_TYPECFG_TYPE0
mdefine_line|#define V_TYPECFG_TYPE0(x)      _SB_MAKEVALUE(x,S_TYPECFG_TYPE0)
DECL|macro|G_TYPECFG_TYPE0
mdefine_line|#define G_TYPECFG_TYPE0(x)      _SB_GETVALUE(x,S_TYPECFG_TYPE0,M_TYPECFG_TYPE0)
DECL|macro|S_TYPECFG_TYPE1
mdefine_line|#define S_TYPECFG_TYPE1&t;&t;_SB_MAKE64(0)
DECL|macro|M_TYPECFG_TYPE1
mdefine_line|#define M_TYPECFG_TYPE1         _SB_MAKEMASK(16,S_TYPECFG_TYPE1)
DECL|macro|V_TYPECFG_TYPE1
mdefine_line|#define V_TYPECFG_TYPE1(x)      _SB_MAKEVALUE(x,S_TYPECFG_TYPE1)
DECL|macro|G_TYPECFG_TYPE1
mdefine_line|#define G_TYPECFG_TYPE1(x)      _SB_GETVALUE(x,S_TYPECFG_TYPE1,M_TYPECFG_TYPE1)
DECL|macro|S_TYPECFG_TYPE2
mdefine_line|#define S_TYPECFG_TYPE2&t;&t;_SB_MAKE64(0)
DECL|macro|M_TYPECFG_TYPE2
mdefine_line|#define M_TYPECFG_TYPE2         _SB_MAKEMASK(16,S_TYPECFG_TYPE2)
DECL|macro|V_TYPECFG_TYPE2
mdefine_line|#define V_TYPECFG_TYPE2(x)      _SB_MAKEVALUE(x,S_TYPECFG_TYPE2)
DECL|macro|G_TYPECFG_TYPE2
mdefine_line|#define G_TYPECFG_TYPE2(x)      _SB_GETVALUE(x,S_TYPECFG_TYPE2,M_TYPECFG_TYPE2)
DECL|macro|S_TYPECFG_TYPE3
mdefine_line|#define S_TYPECFG_TYPE3&t;&t;_SB_MAKE64(0)
DECL|macro|M_TYPECFG_TYPE3
mdefine_line|#define M_TYPECFG_TYPE3         _SB_MAKEMASK(16,S_TYPECFG_TYPE3)
DECL|macro|V_TYPECFG_TYPE3
mdefine_line|#define V_TYPECFG_TYPE3(x)      _SB_MAKEVALUE(x,S_TYPECFG_TYPE3)
DECL|macro|G_TYPECFG_TYPE3
mdefine_line|#define G_TYPECFG_TYPE3(x)      _SB_GETVALUE(x,S_TYPECFG_TYPE3,M_TYPECFG_TYPE3)
multiline_comment|/*&n; * MAC Receive Address Filter Control Registers (Table 9-24)&n; * Register: MAC_ADFILTER_CFG_0&n; * Register: MAC_ADFILTER_CFG_1&n; * Register: MAC_ADFILTER_CFG_2&n; */
DECL|macro|M_MAC_ALLPKT_EN
mdefine_line|#define M_MAC_ALLPKT_EN&t;        _SB_MAKEMASK1(0)
DECL|macro|M_MAC_UCAST_EN
mdefine_line|#define M_MAC_UCAST_EN          _SB_MAKEMASK1(1)
DECL|macro|M_MAC_UCAST_INV
mdefine_line|#define M_MAC_UCAST_INV         _SB_MAKEMASK1(2)
DECL|macro|M_MAC_MCAST_EN
mdefine_line|#define M_MAC_MCAST_EN          _SB_MAKEMASK1(3)
DECL|macro|M_MAC_MCAST_INV
mdefine_line|#define M_MAC_MCAST_INV         _SB_MAKEMASK1(4)
DECL|macro|M_MAC_BCAST_EN
mdefine_line|#define M_MAC_BCAST_EN          _SB_MAKEMASK1(5)
DECL|macro|M_MAC_DIRECT_INV
mdefine_line|#define M_MAC_DIRECT_INV        _SB_MAKEMASK1(6)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_MAC_ALLMCAST_EN
mdefine_line|#define M_MAC_ALLMCAST_EN&t;_SB_MAKEMASK1(7)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|S_MAC_IPHDR_OFFSET
mdefine_line|#define S_MAC_IPHDR_OFFSET      _SB_MAKE64(8)
DECL|macro|M_MAC_IPHDR_OFFSET
mdefine_line|#define M_MAC_IPHDR_OFFSET      _SB_MAKEMASK(8,S_MAC_IPHDR_OFFSET)
DECL|macro|V_MAC_IPHDR_OFFSET
mdefine_line|#define V_MAC_IPHDR_OFFSET(x)&t;_SB_MAKEVALUE(x,S_MAC_IPHDR_OFFSET)
DECL|macro|G_MAC_IPHDR_OFFSET
mdefine_line|#define G_MAC_IPHDR_OFFSET(x)&t;_SB_GETVALUE(x,S_MAC_IPHDR_OFFSET,M_MAC_IPHDR_OFFSET)
macro_line|#if SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_MAC_RX_CRC_OFFSET
mdefine_line|#define S_MAC_RX_CRC_OFFSET     _SB_MAKE64(16)
DECL|macro|M_MAC_RX_CRC_OFFSET
mdefine_line|#define M_MAC_RX_CRC_OFFSET     _SB_MAKEMASK(8,S_MAC_RX_CRC_OFFSET)
DECL|macro|V_MAC_RX_CRC_OFFSET
mdefine_line|#define V_MAC_RX_CRC_OFFSET(x)&t;_SB_MAKEVALUE(x,S_MAC_RX_CRC_OFFSET)
DECL|macro|G_MAC_RX_CRC_OFFSET
mdefine_line|#define G_MAC_RX_CRC_OFFSET(x)&t;_SB_GETVALUE(x,S_MAC_RX_CRC_OFFSET,M_MAC_RX_CRC_OFFSET)
DECL|macro|S_MAC_RX_PKT_OFFSET
mdefine_line|#define S_MAC_RX_PKT_OFFSET     _SB_MAKE64(24)
DECL|macro|M_MAC_RX_PKT_OFFSET
mdefine_line|#define M_MAC_RX_PKT_OFFSET     _SB_MAKEMASK(8,S_MAC_RX_PKT_OFFSET)
DECL|macro|V_MAC_RX_PKT_OFFSET
mdefine_line|#define V_MAC_RX_PKT_OFFSET(x)&t;_SB_MAKEVALUE(x,S_MAC_RX_PKT_OFFSET)
DECL|macro|G_MAC_RX_PKT_OFFSET
mdefine_line|#define G_MAC_RX_PKT_OFFSET(x)&t;_SB_GETVALUE(x,S_MAC_RX_PKT_OFFSET,M_MAC_RX_PKT_OFFSET)
DECL|macro|M_MAC_FWDPAUSE_EN
mdefine_line|#define M_MAC_FWDPAUSE_EN&t;_SB_MAKEMASK1(32)
DECL|macro|M_MAC_VLAN_DET_EN
mdefine_line|#define M_MAC_VLAN_DET_EN&t;_SB_MAKEMASK1(33)
DECL|macro|S_MAC_RX_CH_MSN_SEL
mdefine_line|#define S_MAC_RX_CH_MSN_SEL     _SB_MAKE64(34)
DECL|macro|M_MAC_RX_CH_MSN_SEL
mdefine_line|#define M_MAC_RX_CH_MSN_SEL     _SB_MAKEMASK(8,S_MAC_RX_CH_MSN_SEL)
DECL|macro|V_MAC_RX_CH_MSN_SEL
mdefine_line|#define V_MAC_RX_CH_MSN_SEL(x)&t;_SB_MAKEVALUE(x,S_MAC_RX_CH_MSN_SEL)
DECL|macro|G_MAC_RX_CH_MSN_SEL
mdefine_line|#define G_MAC_RX_CH_MSN_SEL(x)&t;_SB_GETVALUE(x,S_MAC_RX_CH_MSN_SEL,M_MAC_RX_CH_MSN_SEL)
macro_line|#endif /* 112x PASS1 */
multiline_comment|/*&n; * MAC Receive Channel Select Registers (Table 9-25)&n; */
multiline_comment|/* no bitfields */
multiline_comment|/*&n; * MAC MII Management Interface Registers (Table 9-26)&n; * Register: MAC_MDIO_0&n; * Register: MAC_MDIO_1&n; * Register: MAC_MDIO_2&n; */
DECL|macro|S_MAC_MDC
mdefine_line|#define S_MAC_MDC&t;&t;0
DECL|macro|S_MAC_MDIO_DIR
mdefine_line|#define S_MAC_MDIO_DIR&t;&t;1
DECL|macro|S_MAC_MDIO_OUT
mdefine_line|#define S_MAC_MDIO_OUT&t;&t;2
DECL|macro|S_MAC_GENC
mdefine_line|#define S_MAC_GENC&t;&t;3
DECL|macro|S_MAC_MDIO_IN
mdefine_line|#define S_MAC_MDIO_IN&t;&t;4
DECL|macro|M_MAC_MDC
mdefine_line|#define M_MAC_MDC&t;&t;_SB_MAKEMASK1(S_MAC_MDC)
DECL|macro|M_MAC_MDIO_DIR
mdefine_line|#define M_MAC_MDIO_DIR&t;&t;_SB_MAKEMASK1(S_MAC_MDIO_DIR)
DECL|macro|M_MAC_MDIO_DIR_INPUT
mdefine_line|#define M_MAC_MDIO_DIR_INPUT&t;_SB_MAKEMASK1(S_MAC_MDIO_DIR)
DECL|macro|M_MAC_MDIO_OUT
mdefine_line|#define M_MAC_MDIO_OUT&t;&t;_SB_MAKEMASK1(S_MAC_MDIO_OUT)
DECL|macro|M_MAC_GENC
mdefine_line|#define M_MAC_GENC&t;&t;_SB_MAKEMASK1(S_MAC_GENC)
DECL|macro|M_MAC_MDIO_IN
mdefine_line|#define M_MAC_MDIO_IN&t;&t;_SB_MAKEMASK1(S_MAC_MDIO_IN)
macro_line|#endif
eof
