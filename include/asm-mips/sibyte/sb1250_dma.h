multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  DMA definitions&t;&t;&t;&t;File: sb1250_dma.h&n;    *  &n;    *  This module contains constants and macros useful for&n;    *  programming the SB1250&squot;s DMA controllers, both the data mover&n;    *  and the Ethernet DMA.&n;    *  &n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_DMA_H
DECL|macro|_SB1250_DMA_H
mdefine_line|#define _SB1250_DMA_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/*  *********************************************************************&n;    *  DMA Registers&n;    ********************************************************************* */
multiline_comment|/* &n; * Ethernet and Serial DMA Configuration Register 0  (Table 7-4)&n; * Registers: DMA_CONFIG0_MAC_x_RX_CH_0 &n; * Registers: DMA_CONFIG0_MAC_x_TX_CH_0&n; * Registers: DMA_CONFIG0_SER_x_RX&n; * Registers: DMA_CONFIG0_SER_x_TX&n; */
DECL|macro|M_DMA_DROP
mdefine_line|#define M_DMA_DROP                  _SB_MAKEMASK1(0)
DECL|macro|M_DMA_CHAIN_SEL
mdefine_line|#define M_DMA_CHAIN_SEL             _SB_MAKEMASK1(1)
DECL|macro|M_DMA_RESERVED1
mdefine_line|#define M_DMA_RESERVED1             _SB_MAKEMASK1(2)
DECL|macro|S_DMA_DESC_TYPE
mdefine_line|#define S_DMA_DESC_TYPE&t;&t;    _SB_MAKE64(1)
DECL|macro|M_DMA_DESC_TYPE
mdefine_line|#define M_DMA_DESC_TYPE&t;&t;    _SB_MAKE64(2,S_DMA_DESC_TYPE)
DECL|macro|V_DMA_DESC_TYPE
mdefine_line|#define V_DMA_DESC_TYPE(x)          _SB_MAKEVALUE(x,S_DMA_DESC_TYPE)
DECL|macro|G_DMA_DESC_TYPE
mdefine_line|#define G_DMA_DESC_TYPE(x)          _SB_GETVALUE(x,S_DMA_DESC_TYPE,M_DMA_DESC_TYPE)
DECL|macro|K_DMA_DESC_TYPE_RING_AL
mdefine_line|#define K_DMA_DESC_TYPE_RING_AL&t;&t;0
DECL|macro|K_DMA_DESC_TYPE_CHAIN_AL
mdefine_line|#define K_DMA_DESC_TYPE_CHAIN_AL&t;1
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|K_DMA_DESC_TYPE_RING_UAL_WI
mdefine_line|#define K_DMA_DESC_TYPE_RING_UAL_WI&t;2
DECL|macro|K_DMA_DESC_TYPE_RING_UAL_RMW
mdefine_line|#define K_DMA_DESC_TYPE_RING_UAL_RMW&t;3
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
DECL|macro|M_DMA_EOP_INT_EN
mdefine_line|#define M_DMA_EOP_INT_EN            _SB_MAKEMASK1(3)
DECL|macro|M_DMA_HWM_INT_EN
mdefine_line|#define M_DMA_HWM_INT_EN            _SB_MAKEMASK1(4)
DECL|macro|M_DMA_LWM_INT_EN
mdefine_line|#define M_DMA_LWM_INT_EN            _SB_MAKEMASK1(5)
DECL|macro|M_DMA_TBX_EN
mdefine_line|#define M_DMA_TBX_EN                _SB_MAKEMASK1(6)
DECL|macro|M_DMA_TDX_EN
mdefine_line|#define M_DMA_TDX_EN                _SB_MAKEMASK1(7)
DECL|macro|S_DMA_INT_PKTCNT
mdefine_line|#define S_DMA_INT_PKTCNT            _SB_MAKE64(8)
DECL|macro|M_DMA_INT_PKTCNT
mdefine_line|#define M_DMA_INT_PKTCNT            _SB_MAKEMASK(8,S_DMA_INT_PKTCNT)
DECL|macro|V_DMA_INT_PKTCNT
mdefine_line|#define V_DMA_INT_PKTCNT(x)         _SB_MAKEVALUE(x,S_DMA_INT_PKTCNT)
DECL|macro|G_DMA_INT_PKTCNT
mdefine_line|#define G_DMA_INT_PKTCNT(x)         _SB_GETVALUE(x,S_DMA_INT_PKTCNT,M_DMA_INT_PKTCNT)
DECL|macro|S_DMA_RINGSZ
mdefine_line|#define S_DMA_RINGSZ                _SB_MAKE64(16)
DECL|macro|M_DMA_RINGSZ
mdefine_line|#define M_DMA_RINGSZ                _SB_MAKEMASK(16,S_DMA_RINGSZ)
DECL|macro|V_DMA_RINGSZ
mdefine_line|#define V_DMA_RINGSZ(x)             _SB_MAKEVALUE(x,S_DMA_RINGSZ)
DECL|macro|G_DMA_RINGSZ
mdefine_line|#define G_DMA_RINGSZ(x)             _SB_GETVALUE(x,S_DMA_RINGSZ,M_DMA_RINGSZ)
DECL|macro|S_DMA_HIGH_WATERMARK
mdefine_line|#define S_DMA_HIGH_WATERMARK        _SB_MAKE64(32)
DECL|macro|M_DMA_HIGH_WATERMARK
mdefine_line|#define M_DMA_HIGH_WATERMARK        _SB_MAKEMASK(16,S_DMA_HIGH_WATERMARK)
DECL|macro|V_DMA_HIGH_WATERMARK
mdefine_line|#define V_DMA_HIGH_WATERMARK(x)     _SB_MAKEVALUE(x,S_DMA_HIGH_WATERMARK)
DECL|macro|G_DMA_HIGH_WATERMARK
mdefine_line|#define G_DMA_HIGH_WATERMARK(x)     _SB_GETVALUE(x,S_DMA_HIGH_WATERMARK,M_DMA_HIGH_WATERMARK)
DECL|macro|S_DMA_LOW_WATERMARK
mdefine_line|#define S_DMA_LOW_WATERMARK         _SB_MAKE64(48)
DECL|macro|M_DMA_LOW_WATERMARK
mdefine_line|#define M_DMA_LOW_WATERMARK         _SB_MAKEMASK(16,S_DMA_LOW_WATERMARK)
DECL|macro|V_DMA_LOW_WATERMARK
mdefine_line|#define V_DMA_LOW_WATERMARK(x)      _SB_MAKEVALUE(x,S_DMA_LOW_WATERMARK)
DECL|macro|G_DMA_LOW_WATERMARK
mdefine_line|#define G_DMA_LOW_WATERMARK(x)      _SB_GETVALUE(x,S_DMA_LOW_WATERMARK,M_DMA_LOW_WATERMARK)
multiline_comment|/*&n; * Ethernet and Serial DMA Configuration Register 1 (Table 7-5)&n; * Registers: DMA_CONFIG1_MAC_x_RX_CH_0 &n; * Registers: DMA_CONFIG1_DMA_x_TX_CH_0&n; * Registers: DMA_CONFIG1_SER_x_RX&n; * Registers: DMA_CONFIG1_SER_x_TX&n; */
DECL|macro|M_DMA_HDR_CF_EN
mdefine_line|#define M_DMA_HDR_CF_EN             _SB_MAKEMASK1(0)
DECL|macro|M_DMA_ASIC_XFR_EN
mdefine_line|#define M_DMA_ASIC_XFR_EN           _SB_MAKEMASK1(1)
DECL|macro|M_DMA_PRE_ADDR_EN
mdefine_line|#define M_DMA_PRE_ADDR_EN           _SB_MAKEMASK1(2)
DECL|macro|M_DMA_FLOW_CTL_EN
mdefine_line|#define M_DMA_FLOW_CTL_EN           _SB_MAKEMASK1(3)
DECL|macro|M_DMA_NO_DSCR_UPDT
mdefine_line|#define M_DMA_NO_DSCR_UPDT          _SB_MAKEMASK1(4)
DECL|macro|M_DMA_L2CA
mdefine_line|#define M_DMA_L2CA&t;&t;    _SB_MAKEMASK1(5)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_DMA_RX_XTRA_STATUS
mdefine_line|#define M_DMA_RX_XTRA_STATUS&t;    _SB_MAKEMASK1(6)
DECL|macro|M_DMA_TX_CPU_PAUSE
mdefine_line|#define M_DMA_TX_CPU_PAUSE&t;    _SB_MAKEMASK1(6)
DECL|macro|M_DMA_TX_FC_PAUSE_EN
mdefine_line|#define M_DMA_TX_FC_PAUSE_EN&t;    _SB_MAKEMASK1(7)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
DECL|macro|M_DMA_MBZ1
mdefine_line|#define M_DMA_MBZ1                  _SB_MAKEMASK(6,15)
DECL|macro|S_DMA_HDR_SIZE
mdefine_line|#define S_DMA_HDR_SIZE              _SB_MAKE64(21)
DECL|macro|M_DMA_HDR_SIZE
mdefine_line|#define M_DMA_HDR_SIZE              _SB_MAKEMASK(9,S_DMA_HDR_SIZE)
DECL|macro|V_DMA_HDR_SIZE
mdefine_line|#define V_DMA_HDR_SIZE(x)           _SB_MAKEVALUE(x,S_DMA_HDR_SIZE)
DECL|macro|G_DMA_HDR_SIZE
mdefine_line|#define G_DMA_HDR_SIZE(x)           _SB_GETVALUE(x,S_DMA_HDR_SIZE,M_DMA_HDR_SIZE)
DECL|macro|M_DMA_MBZ2
mdefine_line|#define M_DMA_MBZ2                  _SB_MAKEMASK(5,32)
DECL|macro|S_DMA_ASICXFR_SIZE
mdefine_line|#define S_DMA_ASICXFR_SIZE          _SB_MAKE64(37)
DECL|macro|M_DMA_ASICXFR_SIZE
mdefine_line|#define M_DMA_ASICXFR_SIZE          _SB_MAKEMASK(9,S_DMA_ASICXFR_SIZE)
DECL|macro|V_DMA_ASICXFR_SIZE
mdefine_line|#define V_DMA_ASICXFR_SIZE(x)       _SB_MAKEVALUE(x,S_DMA_ASICXFR_SIZE)
DECL|macro|G_DMA_ASICXFR_SIZE
mdefine_line|#define G_DMA_ASICXFR_SIZE(x)       _SB_GETVALUE(x,S_DMA_ASICXFR_SIZE,M_DMA_ASICXFR_SIZE)
DECL|macro|S_DMA_INT_TIMEOUT
mdefine_line|#define S_DMA_INT_TIMEOUT           _SB_MAKE64(48)
DECL|macro|M_DMA_INT_TIMEOUT
mdefine_line|#define M_DMA_INT_TIMEOUT           _SB_MAKEMASK(16,S_DMA_INT_TIMEOUT)
DECL|macro|V_DMA_INT_TIMEOUT
mdefine_line|#define V_DMA_INT_TIMEOUT(x)        _SB_MAKEVALUE(x,S_DMA_INT_TIMEOUT)
DECL|macro|G_DMA_INT_TIMEOUT
mdefine_line|#define G_DMA_INT_TIMEOUT(x)        _SB_GETVALUE(x,S_DMA_INT_TIMEOUT,M_DMA_INT_TIMEOUT)
multiline_comment|/*&n; * Ethernet and Serial DMA Descriptor base address (Table 7-6)&n; */
DECL|macro|M_DMA_DSCRBASE_MBZ
mdefine_line|#define M_DMA_DSCRBASE_MBZ          _SB_MAKEMASK(4,0)
multiline_comment|/*&n; * ASIC Mode Base Address (Table 7-7)&n; */
DECL|macro|M_DMA_ASIC_BASE_MBZ
mdefine_line|#define M_DMA_ASIC_BASE_MBZ         _SB_MAKEMASK(20,0)
multiline_comment|/*&n; * DMA Descriptor Count Registers (Table 7-8)&n; */
multiline_comment|/* No bitfields */
multiline_comment|/* &n; * Current Descriptor Address Register (Table 7-11)&n; */
DECL|macro|S_DMA_CURDSCR_ADDR
mdefine_line|#define S_DMA_CURDSCR_ADDR          _SB_MAKE64(0)
DECL|macro|M_DMA_CURDSCR_ADDR
mdefine_line|#define M_DMA_CURDSCR_ADDR          _SB_MAKEMASK(40,S_DMA_CURDSCR_ADDR)
DECL|macro|S_DMA_CURDSCR_COUNT
mdefine_line|#define S_DMA_CURDSCR_COUNT         _SB_MAKE64(40)
DECL|macro|M_DMA_CURDSCR_COUNT
mdefine_line|#define M_DMA_CURDSCR_COUNT         _SB_MAKEMASK(16,S_DMA_CURDSCR_COUNT)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_DMA_TX_CH_PAUSE_ON
mdefine_line|#define M_DMA_TX_CH_PAUSE_ON&t;    _SB_MAKEMASK1(56)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
multiline_comment|/*&n; * Receive Packet Drop Registers&n; */
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_DMA_OODLOST_RX
mdefine_line|#define S_DMA_OODLOST_RX           _SB_MAKE64(0)
DECL|macro|M_DMA_OODLOST_RX
mdefine_line|#define M_DMA_OODLOST_RX           _SB_MAKEMASK(16,S_DMA_OODLOST_RX)
DECL|macro|G_DMA_OODLOST_RX
mdefine_line|#define G_DMA_OODLOST_RX(x)        _SB_GETVALUE(x,S_DMA_OODLOST_RX,M_DMA_OODLOST_RX)
DECL|macro|S_DMA_EOP_COUNT_RX
mdefine_line|#define S_DMA_EOP_COUNT_RX         _SB_MAKE64(16)
DECL|macro|M_DMA_EOP_COUNT_RX
mdefine_line|#define M_DMA_EOP_COUNT_RX         _SB_MAKEMASK(8,S_DMA_EOP_COUNT_RX)
DECL|macro|G_DMA_EOP_COUNT_RX
mdefine_line|#define G_DMA_EOP_COUNT_RX(x)      _SB_GETVALUE(x,S_DMA_EOP_COUNT_RX,M_DMA_EOP_COUNT_RX)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
multiline_comment|/*  *********************************************************************&n;    *  DMA Descriptors&n;    ********************************************************************* */
multiline_comment|/*&n; * Descriptor doubleword &quot;A&quot;  (Table 7-12)&n; */
DECL|macro|S_DMA_DSCRA_OFFSET
mdefine_line|#define S_DMA_DSCRA_OFFSET          _SB_MAKE64(0)
DECL|macro|M_DMA_DSCRA_OFFSET
mdefine_line|#define M_DMA_DSCRA_OFFSET          _SB_MAKEMASK(5,S_DMA_DSCRA_OFFSET)
DECL|macro|V_DMA_DSCRA_OFFSET
mdefine_line|#define V_DMA_DSCRA_OFFSET(x)       _SB_MAKEVALUE(x,S_DMA_DSCRA_OFFSET)
DECL|macro|G_DMA_DSCRA_OFFSET
mdefine_line|#define G_DMA_DSCRA_OFFSET(x)       _SB_GETVALUE(x,S_DMA_DSCRA_OFFSET,M_DMA_DSCRA_OFFSET)
multiline_comment|/* Note: Don&squot;t shift the address over, just mask it with the mask below */
DECL|macro|S_DMA_DSCRA_A_ADDR
mdefine_line|#define S_DMA_DSCRA_A_ADDR          _SB_MAKE64(5)
DECL|macro|M_DMA_DSCRA_A_ADDR
mdefine_line|#define M_DMA_DSCRA_A_ADDR          _SB_MAKEMASK(35,S_DMA_DSCRA_A_ADDR)
DECL|macro|M_DMA_DSCRA_A_ADDR_OFFSET
mdefine_line|#define M_DMA_DSCRA_A_ADDR_OFFSET   (M_DMA_DSCRA_OFFSET | M_DMA_DSCRA_A_ADDR)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_DMA_DSCRA_A_ADDR_UA
mdefine_line|#define S_DMA_DSCRA_A_ADDR_UA        _SB_MAKE64(0)
DECL|macro|M_DMA_DSCRA_A_ADDR_UA
mdefine_line|#define M_DMA_DSCRA_A_ADDR_UA        _SB_MAKEMASK(40,S_DMA_DSCRA_A_ADDR_UA)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
DECL|macro|S_DMA_DSCRA_A_SIZE
mdefine_line|#define S_DMA_DSCRA_A_SIZE          _SB_MAKE64(40)
DECL|macro|M_DMA_DSCRA_A_SIZE
mdefine_line|#define M_DMA_DSCRA_A_SIZE          _SB_MAKEMASK(9,S_DMA_DSCRA_A_SIZE)
DECL|macro|V_DMA_DSCRA_A_SIZE
mdefine_line|#define V_DMA_DSCRA_A_SIZE(x)       _SB_MAKEVALUE(x,S_DMA_DSCRA_A_SIZE)
DECL|macro|G_DMA_DSCRA_A_SIZE
mdefine_line|#define G_DMA_DSCRA_A_SIZE(x)       _SB_GETVALUE(x,S_DMA_DSCRA_A_SIZE,M_DMA_DSCRA_A_SIZE)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_DMA_DSCRA_DSCR_CNT
mdefine_line|#define S_DMA_DSCRA_DSCR_CNT&t;    _SB_MAKE64(40)
DECL|macro|M_DMA_DSCRA_DSCR_CNT
mdefine_line|#define M_DMA_DSCRA_DSCR_CNT&t;    _SB_MAKEMASK(8,S_DMA_DSCRA_DSCR_CNT)
DECL|macro|G_DMA_DSCRA_DSCR_CNT
mdefine_line|#define G_DMA_DSCRA_DSCR_CNT(x)&t;    _SB_GETVALUE(x,S_DMA_DSCRA_DSCR_CNT,M_DMA_DSCRA_DSCR_CNT)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
DECL|macro|M_DMA_DSCRA_INTERRUPT
mdefine_line|#define M_DMA_DSCRA_INTERRUPT       _SB_MAKEMASK1(49)
DECL|macro|M_DMA_DSCRA_OFFSETB
mdefine_line|#define M_DMA_DSCRA_OFFSETB&t;    _SB_MAKEMASK1(50)
DECL|macro|S_DMA_DSCRA_STATUS
mdefine_line|#define S_DMA_DSCRA_STATUS          _SB_MAKE64(51)
DECL|macro|M_DMA_DSCRA_STATUS
mdefine_line|#define M_DMA_DSCRA_STATUS          _SB_MAKEMASK(13,S_DMA_DSCRA_STATUS)
DECL|macro|V_DMA_DSCRA_STATUS
mdefine_line|#define V_DMA_DSCRA_STATUS(x)       _SB_MAKEVALUE(x,S_DMA_DSCRA_STATUS)
DECL|macro|G_DMA_DSCRA_STATUS
mdefine_line|#define G_DMA_DSCRA_STATUS(x)       _SB_GETVALUE(x,S_DMA_DSCRA_STATUS,M_DMA_DSCRA_STATUS)
multiline_comment|/*&n; * Descriptor doubleword &quot;B&quot;  (Table 7-13)&n; */
DECL|macro|S_DMA_DSCRB_OPTIONS
mdefine_line|#define S_DMA_DSCRB_OPTIONS         _SB_MAKE64(0)
DECL|macro|M_DMA_DSCRB_OPTIONS
mdefine_line|#define M_DMA_DSCRB_OPTIONS         _SB_MAKEMASK(4,S_DMA_DSCRB_OPTIONS)
DECL|macro|V_DMA_DSCRB_OPTIONS
mdefine_line|#define V_DMA_DSCRB_OPTIONS(x)      _SB_MAKEVALUE(x,S_DMA_DSCRB_OPTIONS)
DECL|macro|G_DMA_DSCRB_OPTIONS
mdefine_line|#define G_DMA_DSCRB_OPTIONS(x)      _SB_GETVALUE(x,S_DMA_DSCRB_OPTIONS,M_DMA_DSCRB_OPTIONS)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_DMA_DSCRB_A_SIZE
mdefine_line|#define S_DMA_DSCRB_A_SIZE        _SB_MAKE64(8)
DECL|macro|M_DMA_DSCRB_A_SIZE
mdefine_line|#define M_DMA_DSCRB_A_SIZE        _SB_MAKEMASK(14,S_DMA_DSCRB_A_SIZE)
DECL|macro|V_DMA_DSCRB_A_SIZE
mdefine_line|#define V_DMA_DSCRB_A_SIZE(x)     _SB_MAKEVALUE(x,S_DMA_DSCRB_A_SIZE)
DECL|macro|G_DMA_DSCRB_A_SIZE
mdefine_line|#define G_DMA_DSCRB_A_SIZE(x)     _SB_GETVALUE(x,S_DMA_DSCRB_A_SIZE,M_DMA_DSCRB_A_SIZE)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
DECL|macro|R_DMA_DSCRB_ADDR
mdefine_line|#define R_DMA_DSCRB_ADDR            _SB_MAKE64(0x10)
multiline_comment|/* Note: Don&squot;t shift the address over, just mask it with the mask below */
DECL|macro|S_DMA_DSCRB_B_ADDR
mdefine_line|#define S_DMA_DSCRB_B_ADDR          _SB_MAKE64(5)
DECL|macro|M_DMA_DSCRB_B_ADDR
mdefine_line|#define M_DMA_DSCRB_B_ADDR          _SB_MAKEMASK(35,S_DMA_DSCRB_B_ADDR)
DECL|macro|S_DMA_DSCRB_B_SIZE
mdefine_line|#define S_DMA_DSCRB_B_SIZE          _SB_MAKE64(40)
DECL|macro|M_DMA_DSCRB_B_SIZE
mdefine_line|#define M_DMA_DSCRB_B_SIZE          _SB_MAKEMASK(9,S_DMA_DSCRB_B_SIZE)
DECL|macro|V_DMA_DSCRB_B_SIZE
mdefine_line|#define V_DMA_DSCRB_B_SIZE(x)       _SB_MAKEVALUE(x,S_DMA_DSCRB_B_SIZE)
DECL|macro|G_DMA_DSCRB_B_SIZE
mdefine_line|#define G_DMA_DSCRB_B_SIZE(x)       _SB_GETVALUE(x,S_DMA_DSCRB_B_SIZE,M_DMA_DSCRB_B_SIZE)
DECL|macro|M_DMA_DSCRB_B_VALID
mdefine_line|#define M_DMA_DSCRB_B_VALID         _SB_MAKEMASK1(49)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_DMA_DSCRB_PKT_SIZE_MSB
mdefine_line|#define S_DMA_DSCRB_PKT_SIZE_MSB    _SB_MAKE64(48)
DECL|macro|M_DMA_DSCRB_PKT_SIZE_MSB
mdefine_line|#define M_DMA_DSCRB_PKT_SIZE_MSB    _SB_MAKEMASK(2,S_DMA_DSCRB_PKT_SIZE_MSB)
DECL|macro|V_DMA_DSCRB_PKT_SIZE_MSB
mdefine_line|#define V_DMA_DSCRB_PKT_SIZE_MSB(x) _SB_MAKEVALUE(x,S_DMA_DSCRB_PKT_SIZE_MSB)
DECL|macro|G_DMA_DSCRB_PKT_SIZE_MSB
mdefine_line|#define G_DMA_DSCRB_PKT_SIZE_MSB(x) _SB_GETVALUE(x,S_DMA_DSCRB_PKT_SIZE_MSB,M_DMA_DSCRB_PKT_SIZE_MSB)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
DECL|macro|S_DMA_DSCRB_PKT_SIZE
mdefine_line|#define S_DMA_DSCRB_PKT_SIZE        _SB_MAKE64(50)
DECL|macro|M_DMA_DSCRB_PKT_SIZE
mdefine_line|#define M_DMA_DSCRB_PKT_SIZE        _SB_MAKEMASK(14,S_DMA_DSCRB_PKT_SIZE)
DECL|macro|V_DMA_DSCRB_PKT_SIZE
mdefine_line|#define V_DMA_DSCRB_PKT_SIZE(x)     _SB_MAKEVALUE(x,S_DMA_DSCRB_PKT_SIZE)
DECL|macro|G_DMA_DSCRB_PKT_SIZE
mdefine_line|#define G_DMA_DSCRB_PKT_SIZE(x)     _SB_GETVALUE(x,S_DMA_DSCRB_PKT_SIZE,M_DMA_DSCRB_PKT_SIZE)
multiline_comment|/*&n; * from pass2 some bits in dscr_b are also used for rx status&n; */
DECL|macro|S_DMA_DSCRB_STATUS
mdefine_line|#define S_DMA_DSCRB_STATUS          _SB_MAKE64(0)
DECL|macro|M_DMA_DSCRB_STATUS
mdefine_line|#define M_DMA_DSCRB_STATUS          _SB_MAKEMASK(1,S_DMA_DSCRB_STATUS)
DECL|macro|V_DMA_DSCRB_STATUS
mdefine_line|#define V_DMA_DSCRB_STATUS(x)       _SB_MAKEVALUE(x,S_DMA_DSCRB_STATUS)
DECL|macro|G_DMA_DSCRB_STATUS
mdefine_line|#define G_DMA_DSCRB_STATUS(x)       _SB_GETVALUE(x,S_DMA_DSCRB_STATUS,M_DMA_DSCRB_STATUS)
multiline_comment|/* &n; * Ethernet Descriptor Status Bits (Table 7-15)&n; */
DECL|macro|M_DMA_ETHRX_BADIP4CS
mdefine_line|#define M_DMA_ETHRX_BADIP4CS        _SB_MAKEMASK1(51)
DECL|macro|M_DMA_ETHRX_DSCRERR
mdefine_line|#define M_DMA_ETHRX_DSCRERR&t;    _SB_MAKEMASK1(52)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) 
multiline_comment|/* Note: BADTCPCS is actually in DSCR_B options field */
DECL|macro|M_DMA_ETHRX_BADTCPCS
mdefine_line|#define M_DMA_ETHRX_BADTCPCS&t;_SB_MAKEMASK1(0)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_DMA_ETH_VLAN_FLAG
mdefine_line|#define M_DMA_ETH_VLAN_FLAG&t;_SB_MAKEMASK1(1)
DECL|macro|M_DMA_ETH_CRC_FLAG
mdefine_line|#define M_DMA_ETH_CRC_FLAG&t;_SB_MAKEMASK1(2)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
DECL|macro|S_DMA_ETHRX_RXCH
mdefine_line|#define S_DMA_ETHRX_RXCH            53
DECL|macro|M_DMA_ETHRX_RXCH
mdefine_line|#define M_DMA_ETHRX_RXCH            _SB_MAKEMASK(2,S_DMA_ETHRX_RXCH)
DECL|macro|V_DMA_ETHRX_RXCH
mdefine_line|#define V_DMA_ETHRX_RXCH(x)         _SB_MAKEVALUE(x,S_DMA_ETHRX_RXCH)
DECL|macro|G_DMA_ETHRX_RXCH
mdefine_line|#define G_DMA_ETHRX_RXCH(x)         _SB_GETVALUE(x,S_DMA_ETHRX_RXCH,M_DMA_ETHRX_RXCH)
DECL|macro|S_DMA_ETHRX_PKTTYPE
mdefine_line|#define S_DMA_ETHRX_PKTTYPE         55
DECL|macro|M_DMA_ETHRX_PKTTYPE
mdefine_line|#define M_DMA_ETHRX_PKTTYPE         _SB_MAKEMASK(3,S_DMA_ETHRX_PKTTYPE)
DECL|macro|V_DMA_ETHRX_PKTTYPE
mdefine_line|#define V_DMA_ETHRX_PKTTYPE(x)      _SB_MAKEVALUE(x,S_DMA_ETHRX_PKTTYPE)
DECL|macro|G_DMA_ETHRX_PKTTYPE
mdefine_line|#define G_DMA_ETHRX_PKTTYPE(x)      _SB_GETVALUE(x,S_DMA_ETHRX_PKTTYPE,M_DMA_ETHRX_PKTTYPE)
DECL|macro|K_DMA_ETHRX_PKTTYPE_IPV4
mdefine_line|#define K_DMA_ETHRX_PKTTYPE_IPV4    0
DECL|macro|K_DMA_ETHRX_PKTTYPE_ARPV4
mdefine_line|#define K_DMA_ETHRX_PKTTYPE_ARPV4   1
DECL|macro|K_DMA_ETHRX_PKTTYPE_802
mdefine_line|#define K_DMA_ETHRX_PKTTYPE_802     2
DECL|macro|K_DMA_ETHRX_PKTTYPE_OTHER
mdefine_line|#define K_DMA_ETHRX_PKTTYPE_OTHER   3
DECL|macro|K_DMA_ETHRX_PKTTYPE_USER0
mdefine_line|#define K_DMA_ETHRX_PKTTYPE_USER0   4
DECL|macro|K_DMA_ETHRX_PKTTYPE_USER1
mdefine_line|#define K_DMA_ETHRX_PKTTYPE_USER1   5
DECL|macro|K_DMA_ETHRX_PKTTYPE_USER2
mdefine_line|#define K_DMA_ETHRX_PKTTYPE_USER2   6
DECL|macro|K_DMA_ETHRX_PKTTYPE_USER3
mdefine_line|#define K_DMA_ETHRX_PKTTYPE_USER3   7
DECL|macro|M_DMA_ETHRX_MATCH_HASH
mdefine_line|#define M_DMA_ETHRX_MATCH_HASH      _SB_MAKEMASK1(58)
DECL|macro|M_DMA_ETHRX_MATCH_EXACT
mdefine_line|#define M_DMA_ETHRX_MATCH_EXACT     _SB_MAKEMASK1(59)
DECL|macro|M_DMA_ETHRX_BCAST
mdefine_line|#define M_DMA_ETHRX_BCAST           _SB_MAKEMASK1(60)
DECL|macro|M_DMA_ETHRX_MCAST
mdefine_line|#define M_DMA_ETHRX_MCAST           _SB_MAKEMASK1(61)
DECL|macro|M_DMA_ETHRX_BAD
mdefine_line|#define M_DMA_ETHRX_BAD&t;            _SB_MAKEMASK1(62)
DECL|macro|M_DMA_ETHRX_SOP
mdefine_line|#define M_DMA_ETHRX_SOP             _SB_MAKEMASK1(63)
multiline_comment|/*&n; * Ethernet Transmit Status Bits (Table 7-16)&n; */
DECL|macro|M_DMA_ETHTX_SOP
mdefine_line|#define M_DMA_ETHTX_SOP&t;    &t;    _SB_MAKEMASK1(63)
multiline_comment|/* &n; * Ethernet Transmit Options (Table 7-17)&n; */
DECL|macro|K_DMA_ETHTX_NOTSOP
mdefine_line|#define K_DMA_ETHTX_NOTSOP          _SB_MAKE64(0x00)
DECL|macro|K_DMA_ETHTX_APPENDCRC
mdefine_line|#define K_DMA_ETHTX_APPENDCRC       _SB_MAKE64(0x01)
DECL|macro|K_DMA_ETHTX_REPLACECRC
mdefine_line|#define K_DMA_ETHTX_REPLACECRC      _SB_MAKE64(0x02)
DECL|macro|K_DMA_ETHTX_APPENDCRC_APPENDPAD
mdefine_line|#define K_DMA_ETHTX_APPENDCRC_APPENDPAD _SB_MAKE64(0x03)
DECL|macro|K_DMA_ETHTX_APPENDVLAN_REPLACECRC
mdefine_line|#define K_DMA_ETHTX_APPENDVLAN_REPLACECRC _SB_MAKE64(0x04)
DECL|macro|K_DMA_ETHTX_REMOVEVLAN_REPLACECRC
mdefine_line|#define K_DMA_ETHTX_REMOVEVLAN_REPLACECRC _SB_MAKE64(0x05)
DECL|macro|K_DMA_ETHTX_REPLACEVLAN_REPLACECRC
mdefine_line|#define K_DMA_ETHTX_REPLACEVLAN_REPLACECRC _SB_MAKE64(0x6)
DECL|macro|K_DMA_ETHTX_NOMODS
mdefine_line|#define K_DMA_ETHTX_NOMODS          _SB_MAKE64(0x07)
DECL|macro|K_DMA_ETHTX_RESERVED1
mdefine_line|#define K_DMA_ETHTX_RESERVED1       _SB_MAKE64(0x08)
DECL|macro|K_DMA_ETHTX_REPLACESADDR_APPENDCRC
mdefine_line|#define K_DMA_ETHTX_REPLACESADDR_APPENDCRC _SB_MAKE64(0x09)
DECL|macro|K_DMA_ETHTX_REPLACESADDR_REPLACECRC
mdefine_line|#define K_DMA_ETHTX_REPLACESADDR_REPLACECRC _SB_MAKE64(0x0A)
DECL|macro|K_DMA_ETHTX_REPLACESADDR_APPENDCRC_APPENDPAD
mdefine_line|#define K_DMA_ETHTX_REPLACESADDR_APPENDCRC_APPENDPAD _SB_MAKE64(0x0B)
DECL|macro|K_DMA_ETHTX_REPLACESADDR_APPENDVLAN_REPLACECRC
mdefine_line|#define K_DMA_ETHTX_REPLACESADDR_APPENDVLAN_REPLACECRC _SB_MAKE64(0x0C)
DECL|macro|K_DMA_ETHTX_REPLACESADDR_REMOVEVLAN_REPLACECRC
mdefine_line|#define K_DMA_ETHTX_REPLACESADDR_REMOVEVLAN_REPLACECRC _SB_MAKE64(0x0D)
DECL|macro|K_DMA_ETHTX_REPLACESADDR_REPLACEVLAN_REPLACECRC
mdefine_line|#define K_DMA_ETHTX_REPLACESADDR_REPLACEVLAN_REPLACECRC _SB_MAKE64(0x0E)
DECL|macro|K_DMA_ETHTX_RESERVED2
mdefine_line|#define K_DMA_ETHTX_RESERVED2       _SB_MAKE64(0x0F)
multiline_comment|/*&n; * Serial Receive Options (Table 7-18)&n; */
DECL|macro|M_DMA_SERRX_CRC_ERROR
mdefine_line|#define M_DMA_SERRX_CRC_ERROR       _SB_MAKEMASK1(56)
DECL|macro|M_DMA_SERRX_ABORT
mdefine_line|#define M_DMA_SERRX_ABORT           _SB_MAKEMASK1(57)
DECL|macro|M_DMA_SERRX_OCTET_ERROR
mdefine_line|#define M_DMA_SERRX_OCTET_ERROR     _SB_MAKEMASK1(58)
DECL|macro|M_DMA_SERRX_LONGFRAME_ERROR
mdefine_line|#define M_DMA_SERRX_LONGFRAME_ERROR _SB_MAKEMASK1(59)
DECL|macro|M_DMA_SERRX_SHORTFRAME_ERROR
mdefine_line|#define M_DMA_SERRX_SHORTFRAME_ERROR _SB_MAKEMASK1(60)
DECL|macro|M_DMA_SERRX_OVERRUN_ERROR
mdefine_line|#define M_DMA_SERRX_OVERRUN_ERROR   _SB_MAKEMASK1(61)
DECL|macro|M_DMA_SERRX_GOOD
mdefine_line|#define M_DMA_SERRX_GOOD            _SB_MAKEMASK1(62)
DECL|macro|M_DMA_SERRX_SOP
mdefine_line|#define M_DMA_SERRX_SOP             _SB_MAKEMASK1(63)
multiline_comment|/*&n; * Serial Transmit Status Bits (Table 7-20)&n; */
DECL|macro|M_DMA_SERTX_FLAG
mdefine_line|#define M_DMA_SERTX_FLAG&t;    _SB_MAKEMASK1(63)
multiline_comment|/*&n; * Serial Transmit Options (Table 7-21)&n; */
DECL|macro|K_DMA_SERTX_RESERVED
mdefine_line|#define K_DMA_SERTX_RESERVED        _SB_MAKEMASK1(0)
DECL|macro|K_DMA_SERTX_APPENDCRC
mdefine_line|#define K_DMA_SERTX_APPENDCRC       _SB_MAKEMASK1(1)
DECL|macro|K_DMA_SERTX_APPENDPAD
mdefine_line|#define K_DMA_SERTX_APPENDPAD       _SB_MAKEMASK1(2)
DECL|macro|K_DMA_SERTX_ABORT
mdefine_line|#define K_DMA_SERTX_ABORT           _SB_MAKEMASK1(3)
multiline_comment|/*  *********************************************************************&n;    *  Data Mover Registers&n;    ********************************************************************* */
multiline_comment|/* &n; * Data Mover Descriptor Base Address Register (Table 7-22)&n; * Register: DM_DSCR_BASE_0&n; * Register: DM_DSCR_BASE_1&n; * Register: DM_DSCR_BASE_2&n; * Register: DM_DSCR_BASE_3&n; */
DECL|macro|M_DM_DSCR_BASE_MBZ
mdefine_line|#define M_DM_DSCR_BASE_MBZ          _SB_MAKEMASK(4,0)
multiline_comment|/*  Note: Just mask the base address and then OR it in. */
DECL|macro|S_DM_DSCR_BASE_ADDR
mdefine_line|#define S_DM_DSCR_BASE_ADDR         _SB_MAKE64(4)
DECL|macro|M_DM_DSCR_BASE_ADDR
mdefine_line|#define M_DM_DSCR_BASE_ADDR         _SB_MAKEMASK(36,S_DM_DSCR_BASE_ADDR)
DECL|macro|S_DM_DSCR_BASE_RINGSZ
mdefine_line|#define S_DM_DSCR_BASE_RINGSZ       _SB_MAKE64(40)
DECL|macro|M_DM_DSCR_BASE_RINGSZ
mdefine_line|#define M_DM_DSCR_BASE_RINGSZ       _SB_MAKEMASK(16,S_DM_DSCR_BASE_RINGSZ)
DECL|macro|V_DM_DSCR_BASE_RINGSZ
mdefine_line|#define V_DM_DSCR_BASE_RINGSZ(x)    _SB_MAKEVALUE(x,S_DM_DSCR_BASE_RINGSZ)
DECL|macro|G_DM_DSCR_BASE_RINGSZ
mdefine_line|#define G_DM_DSCR_BASE_RINGSZ(x)    _SB_GETVALUE(x,S_DM_DSCR_BASE_RINGSZ,M_DM_DSCR_BASE_RINGSZ)
DECL|macro|S_DM_DSCR_BASE_PRIORITY
mdefine_line|#define S_DM_DSCR_BASE_PRIORITY     _SB_MAKE64(56)
DECL|macro|M_DM_DSCR_BASE_PRIORITY
mdefine_line|#define M_DM_DSCR_BASE_PRIORITY     _SB_MAKEMASK(3,S_DM_DSCR_BASE_PRIORITY)
DECL|macro|V_DM_DSCR_BASE_PRIORITY
mdefine_line|#define V_DM_DSCR_BASE_PRIORITY(x)  _SB_MAKEVALUE(x,S_DM_DSCR_BASE_PRIORITY)
DECL|macro|G_DM_DSCR_BASE_PRIORITY
mdefine_line|#define G_DM_DSCR_BASE_PRIORITY(x)  _SB_GETVALUE(x,S_DM_DSCR_BASE_PRIORITY,M_DM_DSCR_BASE_PRIORITY)
DECL|macro|K_DM_DSCR_BASE_PRIORITY_1
mdefine_line|#define K_DM_DSCR_BASE_PRIORITY_1   0
DECL|macro|K_DM_DSCR_BASE_PRIORITY_2
mdefine_line|#define K_DM_DSCR_BASE_PRIORITY_2   1
DECL|macro|K_DM_DSCR_BASE_PRIORITY_4
mdefine_line|#define K_DM_DSCR_BASE_PRIORITY_4   2
DECL|macro|K_DM_DSCR_BASE_PRIORITY_8
mdefine_line|#define K_DM_DSCR_BASE_PRIORITY_8   3
DECL|macro|K_DM_DSCR_BASE_PRIORITY_16
mdefine_line|#define K_DM_DSCR_BASE_PRIORITY_16  4
DECL|macro|M_DM_DSCR_BASE_ACTIVE
mdefine_line|#define M_DM_DSCR_BASE_ACTIVE       _SB_MAKEMASK1(59)
DECL|macro|M_DM_DSCR_BASE_INTERRUPT
mdefine_line|#define M_DM_DSCR_BASE_INTERRUPT    _SB_MAKEMASK1(60)
DECL|macro|M_DM_DSCR_BASE_RESET
mdefine_line|#define M_DM_DSCR_BASE_RESET        _SB_MAKEMASK1(61)&t;/* write register */
DECL|macro|M_DM_DSCR_BASE_ERROR
mdefine_line|#define M_DM_DSCR_BASE_ERROR        _SB_MAKEMASK1(61)&t;/* read register */
DECL|macro|M_DM_DSCR_BASE_ABORT
mdefine_line|#define M_DM_DSCR_BASE_ABORT        _SB_MAKEMASK1(62)
DECL|macro|M_DM_DSCR_BASE_ENABL
mdefine_line|#define M_DM_DSCR_BASE_ENABL        _SB_MAKEMASK1(63)
multiline_comment|/* &n; * Data Mover Descriptor Count Register (Table 7-25)&n; */
multiline_comment|/* no bitfields */
multiline_comment|/*&n; * Data Mover Current Descriptor Address (Table 7-24)&n; * Register: DM_CUR_DSCR_ADDR_0&n; * Register: DM_CUR_DSCR_ADDR_1&n; * Register: DM_CUR_DSCR_ADDR_2&n; * Register: DM_CUR_DSCR_ADDR_3&n; */
DECL|macro|S_DM_CUR_DSCR_DSCR_ADDR
mdefine_line|#define S_DM_CUR_DSCR_DSCR_ADDR     _SB_MAKE64(0)
DECL|macro|M_DM_CUR_DSCR_DSCR_ADDR
mdefine_line|#define M_DM_CUR_DSCR_DSCR_ADDR     _SB_MAKEMASK(40,S_DM_CUR_DSCR_DSCR_ADDR)
DECL|macro|S_DM_CUR_DSCR_DSCR_COUNT
mdefine_line|#define S_DM_CUR_DSCR_DSCR_COUNT    _SB_MAKE64(48)
DECL|macro|M_DM_CUR_DSCR_DSCR_COUNT
mdefine_line|#define M_DM_CUR_DSCR_DSCR_COUNT    _SB_MAKEMASK(16,S_DM_CUR_DSCR_DSCR_COUNT)
DECL|macro|V_DM_CUR_DSCR_DSCR_COUNT
mdefine_line|#define V_DM_CUR_DSCR_DSCR_COUNT(r) _SB_MAKEVALUE(r,S_DM_CUR_DSCR_DSCR_COUNT)
DECL|macro|G_DM_CUR_DSCR_DSCR_COUNT
mdefine_line|#define G_DM_CUR_DSCR_DSCR_COUNT(r) _SB_GETVALUE(r,S_DM_CUR_DSCR_DSCR_COUNT,&bslash;&n;                                     M_DM_CUR_DSCR_DSCR_COUNT)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
multiline_comment|/*&n; * Data Mover Channel Partial Result Registers&n; * Register: DM_PARTIAL_0&n; * Register: DM_PARTIAL_1&n; * Register: DM_PARTIAL_2&n; * Register: DM_PARTIAL_3&n; */
DECL|macro|S_DM_PARTIAL_CRC_PARTIAL
mdefine_line|#define S_DM_PARTIAL_CRC_PARTIAL      _SB_MAKE64(0)
DECL|macro|M_DM_PARTIAL_CRC_PARTIAL
mdefine_line|#define M_DM_PARTIAL_CRC_PARTIAL      _SB_MAKEMASK(32,S_DM_PARTIAL_CRC_PARTIAL)
DECL|macro|V_DM_PARTIAL_CRC_PARTIAL
mdefine_line|#define V_DM_PARTIAL_CRC_PARTIAL(r)   _SB_MAKEVALUE(r,S_DM_PARTIAL_CRC_PARTIAL)
DECL|macro|G_DM_PARTIAL_CRC_PARTIAL
mdefine_line|#define G_DM_PARTIAL_CRC_PARTIAL(r)   _SB_GETVALUE(r,S_DM_PARTIAL_CRC_PARTIAL,&bslash;&n;                                       M_DM_PARTIAL_CRC_PARTIAL)
DECL|macro|S_DM_PARTIAL_TCPCS_PARTIAL
mdefine_line|#define S_DM_PARTIAL_TCPCS_PARTIAL    _SB_MAKE64(32)
DECL|macro|M_DM_PARTIAL_TCPCS_PARTIAL
mdefine_line|#define M_DM_PARTIAL_TCPCS_PARTIAL    _SB_MAKEMASK(16,S_DM_PARTIAL_TCPCS_PARTIAL)
DECL|macro|V_DM_PARTIAL_TCPCS_PARTIAL
mdefine_line|#define V_DM_PARTIAL_TCPCS_PARTIAL(r) _SB_MAKEVALUE(r,S_DM_PARTIAL_TCPCS_PARTIAL)
DECL|macro|G_DM_PARTIAL_TCPCS_PARTIAL
mdefine_line|#define G_DM_PARTIAL_TCPCS_PARTIAL(r) _SB_GETVALUE(r,S_DM_PARTIAL_TCPCS_PARTIAL,&bslash;&n;                                       M_DM_PARTIAL_TCPCS_PARTIAL)
DECL|macro|M_DM_PARTIAL_ODD_BYTE
mdefine_line|#define M_DM_PARTIAL_ODD_BYTE         _SB_MAKEMASK1(48)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
multiline_comment|/*&n; * Data Mover CRC Definition Registers&n; * Register: CRC_DEF_0&n; * Register: CRC_DEF_1&n; */
DECL|macro|S_CRC_DEF_CRC_INIT
mdefine_line|#define S_CRC_DEF_CRC_INIT            _SB_MAKE64(0)
DECL|macro|M_CRC_DEF_CRC_INIT
mdefine_line|#define M_CRC_DEF_CRC_INIT            _SB_MAKEMASK(32,S_CRC_DEF_CRC_INIT)
DECL|macro|V_CRC_DEF_CRC_INIT
mdefine_line|#define V_CRC_DEF_CRC_INIT(r)         _SB_MAKEVALUE(r,S_CRC_DEF_CRC_INIT)
DECL|macro|G_CRC_DEF_CRC_INIT
mdefine_line|#define G_CRC_DEF_CRC_INIT(r)         _SB_GETVALUE(r,S_CRC_DEF_CRC_INIT,&bslash;&n;                                       M_CRC_DEF_CRC_INIT)
DECL|macro|S_CRC_DEF_CRC_POLY
mdefine_line|#define S_CRC_DEF_CRC_POLY            _SB_MAKE64(32)
DECL|macro|M_CRC_DEF_CRC_POLY
mdefine_line|#define M_CRC_DEF_CRC_POLY            _SB_MAKEMASK(32,S_CRC_DEF_CRC_POLY)
DECL|macro|V_CRC_DEF_CRC_POLY
mdefine_line|#define V_CRC_DEF_CRC_POLY(r)         _SB_MAKEVALUE(r,S_CRC_DEF_CRC_POLY)
DECL|macro|G_CRC_DEF_CRC_POLY
mdefine_line|#define G_CRC_DEF_CRC_POLY(r)         _SB_GETVALUE(r,S_CRC_DEF_CRC_POLY,&bslash;&n;                                       M_CRC_DEF_CRC_POLY)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
multiline_comment|/*&n; * Data Mover CRC/Checksum Definition Registers&n; * Register: CTCP_DEF_0&n; * Register: CTCP_DEF_1&n; */
DECL|macro|S_CTCP_DEF_CRC_TXOR
mdefine_line|#define S_CTCP_DEF_CRC_TXOR           _SB_MAKE64(0)
DECL|macro|M_CTCP_DEF_CRC_TXOR
mdefine_line|#define M_CTCP_DEF_CRC_TXOR           _SB_MAKEMASK(32,S_CTCP_DEF_CRC_TXOR)
DECL|macro|V_CTCP_DEF_CRC_TXOR
mdefine_line|#define V_CTCP_DEF_CRC_TXOR(r)        _SB_MAKEVALUE(r,S_CTCP_DEF_CRC_TXOR)
DECL|macro|G_CTCP_DEF_CRC_TXOR
mdefine_line|#define G_CTCP_DEF_CRC_TXOR(r)        _SB_GETVALUE(r,S_CTCP_DEF_CRC_TXOR,&bslash;&n;                                       M_CTCP_DEF_CRC_TXOR)
DECL|macro|S_CTCP_DEF_TCPCS_INIT
mdefine_line|#define S_CTCP_DEF_TCPCS_INIT         _SB_MAKE64(32)
DECL|macro|M_CTCP_DEF_TCPCS_INIT
mdefine_line|#define M_CTCP_DEF_TCPCS_INIT         _SB_MAKEMASK(16,S_CTCP_DEF_TCPCS_INIT)
DECL|macro|V_CTCP_DEF_TCPCS_INIT
mdefine_line|#define V_CTCP_DEF_TCPCS_INIT(r)      _SB_MAKEVALUE(r,S_CTCP_DEF_TCPCS_INIT)
DECL|macro|G_CTCP_DEF_TCPCS_INIT
mdefine_line|#define G_CTCP_DEF_TCPCS_INIT(r)      _SB_GETVALUE(r,S_CTCP_DEF_TCPCS_INIT,&bslash;&n;                                       M_CTCP_DEF_TCPCS_INIT)
DECL|macro|S_CTCP_DEF_CRC_WIDTH
mdefine_line|#define S_CTCP_DEF_CRC_WIDTH          _SB_MAKE64(48)
DECL|macro|M_CTCP_DEF_CRC_WIDTH
mdefine_line|#define M_CTCP_DEF_CRC_WIDTH          _SB_MAKEMASK(2,S_CTCP_DEF_CRC_WIDTH)
DECL|macro|V_CTCP_DEF_CRC_WIDTH
mdefine_line|#define V_CTCP_DEF_CRC_WIDTH(r)       _SB_MAKEVALUE(r,S_CTCP_DEF_CRC_WIDTH)
DECL|macro|G_CTCP_DEF_CRC_WIDTH
mdefine_line|#define G_CTCP_DEF_CRC_WIDTH(r)       _SB_GETVALUE(r,S_CTCP_DEF_CRC_WIDTH,&bslash;&n;                                       M_CTCP_DEF_CRC_WIDTH)
DECL|macro|K_CTCP_DEF_CRC_WIDTH_4
mdefine_line|#define K_CTCP_DEF_CRC_WIDTH_4        0
DECL|macro|K_CTCP_DEF_CRC_WIDTH_2
mdefine_line|#define K_CTCP_DEF_CRC_WIDTH_2        1
DECL|macro|K_CTCP_DEF_CRC_WIDTH_1
mdefine_line|#define K_CTCP_DEF_CRC_WIDTH_1        2
DECL|macro|M_CTCP_DEF_CRC_BIT_ORDER
mdefine_line|#define M_CTCP_DEF_CRC_BIT_ORDER      _SB_MAKEMASK1(50)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
multiline_comment|/*&n; * Data Mover Descriptor Doubleword &quot;A&quot;  (Table 7-26)&n; */
DECL|macro|S_DM_DSCRA_DST_ADDR
mdefine_line|#define S_DM_DSCRA_DST_ADDR         _SB_MAKE64(0)
DECL|macro|M_DM_DSCRA_DST_ADDR
mdefine_line|#define M_DM_DSCRA_DST_ADDR         _SB_MAKEMASK(40,S_DM_DSCRA_DST_ADDR)
DECL|macro|M_DM_DSCRA_UN_DEST
mdefine_line|#define M_DM_DSCRA_UN_DEST          _SB_MAKEMASK1(40)
DECL|macro|M_DM_DSCRA_UN_SRC
mdefine_line|#define M_DM_DSCRA_UN_SRC           _SB_MAKEMASK1(41)
DECL|macro|M_DM_DSCRA_INTERRUPT
mdefine_line|#define M_DM_DSCRA_INTERRUPT        _SB_MAKEMASK1(42)
macro_line|#if SIBYTE_HDR_FEATURE_UP_TO(1250, PASS1)
DECL|macro|M_DM_DSCRA_THROTTLE
mdefine_line|#define M_DM_DSCRA_THROTTLE         _SB_MAKEMASK1(43)
macro_line|#endif /* up to 1250 PASS1 */
DECL|macro|S_DM_DSCRA_DIR_DEST
mdefine_line|#define S_DM_DSCRA_DIR_DEST         _SB_MAKE64(44)
DECL|macro|M_DM_DSCRA_DIR_DEST
mdefine_line|#define M_DM_DSCRA_DIR_DEST         _SB_MAKEMASK(2,S_DM_DSCRA_DIR_DEST)
DECL|macro|V_DM_DSCRA_DIR_DEST
mdefine_line|#define V_DM_DSCRA_DIR_DEST(x)      _SB_MAKEVALUE(x,S_DM_DSCRA_DIR_DEST)
DECL|macro|G_DM_DSCRA_DIR_DEST
mdefine_line|#define G_DM_DSCRA_DIR_DEST(x)      _SB_GETVALUE(x,S_DM_DSCRA_DIR_DEST,M_DM_DSCRA_DIR_DEST)
DECL|macro|K_DM_DSCRA_DIR_DEST_INCR
mdefine_line|#define K_DM_DSCRA_DIR_DEST_INCR    0
DECL|macro|K_DM_DSCRA_DIR_DEST_DECR
mdefine_line|#define K_DM_DSCRA_DIR_DEST_DECR    1
DECL|macro|K_DM_DSCRA_DIR_DEST_CONST
mdefine_line|#define K_DM_DSCRA_DIR_DEST_CONST   2
DECL|macro|V_DM_DSCRA_DIR_DEST_INCR
mdefine_line|#define V_DM_DSCRA_DIR_DEST_INCR    _SB_MAKEVALUE(K_DM_DSCRA_DIR_DEST_INCR,S_DM_DSCRA_DIR_DEST)
DECL|macro|V_DM_DSCRA_DIR_DEST_DECR
mdefine_line|#define V_DM_DSCRA_DIR_DEST_DECR    _SB_MAKEVALUE(K_DM_DSCRA_DIR_DEST_DECR,S_DM_DSCRA_DIR_DEST)
DECL|macro|V_DM_DSCRA_DIR_DEST_CONST
mdefine_line|#define V_DM_DSCRA_DIR_DEST_CONST   _SB_MAKEVALUE(K_DM_DSCRA_DIR_DEST_CONST,S_DM_DSCRA_DIR_DEST)
DECL|macro|S_DM_DSCRA_DIR_SRC
mdefine_line|#define S_DM_DSCRA_DIR_SRC          _SB_MAKE64(46)
DECL|macro|M_DM_DSCRA_DIR_SRC
mdefine_line|#define M_DM_DSCRA_DIR_SRC          _SB_MAKEMASK(2,S_DM_DSCRA_DIR_SRC)
DECL|macro|V_DM_DSCRA_DIR_SRC
mdefine_line|#define V_DM_DSCRA_DIR_SRC(x)       _SB_MAKEVALUE(x,S_DM_DSCRA_DIR_SRC)
DECL|macro|G_DM_DSCRA_DIR_SRC
mdefine_line|#define G_DM_DSCRA_DIR_SRC(x)       _SB_GETVALUE(x,S_DM_DSCRA_DIR_SRC,M_DM_DSCRA_DIR_SRC)
DECL|macro|K_DM_DSCRA_DIR_SRC_INCR
mdefine_line|#define K_DM_DSCRA_DIR_SRC_INCR     0
DECL|macro|K_DM_DSCRA_DIR_SRC_DECR
mdefine_line|#define K_DM_DSCRA_DIR_SRC_DECR     1
DECL|macro|K_DM_DSCRA_DIR_SRC_CONST
mdefine_line|#define K_DM_DSCRA_DIR_SRC_CONST    2
DECL|macro|V_DM_DSCRA_DIR_SRC_INCR
mdefine_line|#define V_DM_DSCRA_DIR_SRC_INCR     _SB_MAKEVALUE(K_DM_DSCRA_DIR_SRC_INCR,S_DM_DSCRA_DIR_SRC)
DECL|macro|V_DM_DSCRA_DIR_SRC_DECR
mdefine_line|#define V_DM_DSCRA_DIR_SRC_DECR     _SB_MAKEVALUE(K_DM_DSCRA_DIR_SRC_DECR,S_DM_DSCRA_DIR_SRC)
DECL|macro|V_DM_DSCRA_DIR_SRC_CONST
mdefine_line|#define V_DM_DSCRA_DIR_SRC_CONST    _SB_MAKEVALUE(K_DM_DSCRA_DIR_SRC_CONST,S_DM_DSCRA_DIR_SRC)
DECL|macro|M_DM_DSCRA_ZERO_MEM
mdefine_line|#define M_DM_DSCRA_ZERO_MEM         _SB_MAKEMASK1(48)
DECL|macro|M_DM_DSCRA_PREFETCH
mdefine_line|#define M_DM_DSCRA_PREFETCH         _SB_MAKEMASK1(49)
DECL|macro|M_DM_DSCRA_L2C_DEST
mdefine_line|#define M_DM_DSCRA_L2C_DEST         _SB_MAKEMASK1(50)
DECL|macro|M_DM_DSCRA_L2C_SRC
mdefine_line|#define M_DM_DSCRA_L2C_SRC          _SB_MAKEMASK1(51)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_DM_DSCRA_RD_BKOFF
mdefine_line|#define M_DM_DSCRA_RD_BKOFF&t;    _SB_MAKEMASK1(52)
DECL|macro|M_DM_DSCRA_WR_BKOFF
mdefine_line|#define M_DM_DSCRA_WR_BKOFF&t;    _SB_MAKEMASK1(53)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_DM_DSCRA_TCPCS_EN
mdefine_line|#define M_DM_DSCRA_TCPCS_EN         _SB_MAKEMASK1(54)
DECL|macro|M_DM_DSCRA_TCPCS_RES
mdefine_line|#define M_DM_DSCRA_TCPCS_RES        _SB_MAKEMASK1(55)
DECL|macro|M_DM_DSCRA_TCPCS_AP
mdefine_line|#define M_DM_DSCRA_TCPCS_AP         _SB_MAKEMASK1(56)
DECL|macro|M_DM_DSCRA_CRC_EN
mdefine_line|#define M_DM_DSCRA_CRC_EN           _SB_MAKEMASK1(57)
DECL|macro|M_DM_DSCRA_CRC_RES
mdefine_line|#define M_DM_DSCRA_CRC_RES          _SB_MAKEMASK1(58)
DECL|macro|M_DM_DSCRA_CRC_AP
mdefine_line|#define M_DM_DSCRA_CRC_AP           _SB_MAKEMASK1(59)
DECL|macro|M_DM_DSCRA_CRC_DFN
mdefine_line|#define M_DM_DSCRA_CRC_DFN          _SB_MAKEMASK1(60)
DECL|macro|M_DM_DSCRA_CRC_XBIT
mdefine_line|#define M_DM_DSCRA_CRC_XBIT         _SB_MAKEMASK1(61)
macro_line|#endif /* 1250 PASS3 || 112x PASS1 */
DECL|macro|M_DM_DSCRA_RESERVED2
mdefine_line|#define M_DM_DSCRA_RESERVED2        _SB_MAKEMASK(3,61)
multiline_comment|/*&n; * Data Mover Descriptor Doubleword &quot;B&quot;  (Table 7-25)&n; */
DECL|macro|S_DM_DSCRB_SRC_ADDR
mdefine_line|#define S_DM_DSCRB_SRC_ADDR         _SB_MAKE64(0)
DECL|macro|M_DM_DSCRB_SRC_ADDR
mdefine_line|#define M_DM_DSCRB_SRC_ADDR         _SB_MAKEMASK(40,S_DM_DSCRB_SRC_ADDR)
DECL|macro|S_DM_DSCRB_SRC_LENGTH
mdefine_line|#define S_DM_DSCRB_SRC_LENGTH       _SB_MAKE64(40)
DECL|macro|M_DM_DSCRB_SRC_LENGTH
mdefine_line|#define M_DM_DSCRB_SRC_LENGTH       _SB_MAKEMASK(20,S_DM_DSCRB_SRC_LENGTH)
DECL|macro|V_DM_DSCRB_SRC_LENGTH
mdefine_line|#define V_DM_DSCRB_SRC_LENGTH(x)    _SB_MAKEVALUE(x,S_DM_DSCRB_SRC_LENGTH)
DECL|macro|G_DM_DSCRB_SRC_LENGTH
mdefine_line|#define G_DM_DSCRB_SRC_LENGTH(x)    _SB_GETVALUE(x,S_DM_DSCRB_SRC_LENGTH,M_DM_DSCRB_SRC_LENGTH)
macro_line|#endif
eof
