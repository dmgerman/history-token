multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *&n;    *  Synchronous Serial Constants              File: sb1250_syncser.h&n;    *&n;    *  This module contains constants and macros useful for&n;    *  manipulating the SB1250&squot;s Synchronous Serial&n;    *&n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg (mpl@broadcom.com)&n;    *&n;    *********************************************************************&n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_SYNCSER_H
DECL|macro|_SB1250_SYNCSER_H
mdefine_line|#define _SB1250_SYNCSER_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/*&n; * Serial Mode Configuration Register&n; */
DECL|macro|M_SYNCSER_CRC_MODE
mdefine_line|#define M_SYNCSER_CRC_MODE                 _SB_MAKEMASK1(0)
DECL|macro|M_SYNCSER_MSB_FIRST
mdefine_line|#define M_SYNCSER_MSB_FIRST                _SB_MAKEMASK1(1)
DECL|macro|S_SYNCSER_FLAG_NUM
mdefine_line|#define S_SYNCSER_FLAG_NUM                 2
DECL|macro|M_SYNCSER_FLAG_NUM
mdefine_line|#define M_SYNCSER_FLAG_NUM                 _SB_MAKEMASK(4,S_SYNCSER_FLAG_NUM)
DECL|macro|V_SYNCSER_FLAG_NUM
mdefine_line|#define V_SYNCSER_FLAG_NUM                 _SB_MAKEVALUE(x,S_SYNCSER_FLAG_NUM)
DECL|macro|M_SYNCSER_FLAG_EN
mdefine_line|#define M_SYNCSER_FLAG_EN                  _SB_MAKEMASK1(6)
DECL|macro|M_SYNCSER_HDLC_EN
mdefine_line|#define M_SYNCSER_HDLC_EN                  _SB_MAKEMASK1(7)
DECL|macro|M_SYNCSER_LOOP_MODE
mdefine_line|#define M_SYNCSER_LOOP_MODE                _SB_MAKEMASK1(8)
DECL|macro|M_SYNCSER_LOOPBACK
mdefine_line|#define M_SYNCSER_LOOPBACK                 _SB_MAKEMASK1(9)
multiline_comment|/*&n; * Serial Clock Source and Line Interface Mode Register&n; */
DECL|macro|M_SYNCSER_RXCLK_INV
mdefine_line|#define M_SYNCSER_RXCLK_INV                _SB_MAKEMASK1(0)
DECL|macro|M_SYNCSER_RXCLK_EXT
mdefine_line|#define M_SYNCSER_RXCLK_EXT                _SB_MAKEMASK1(1)
DECL|macro|S_SYNCSER_RXSYNC_DLY
mdefine_line|#define S_SYNCSER_RXSYNC_DLY               2
DECL|macro|M_SYNCSER_RXSYNC_DLY
mdefine_line|#define M_SYNCSER_RXSYNC_DLY               _SB_MAKEMASK(2,S_SYNCSER_RXSYNC_DLY)
DECL|macro|V_SYNCSER_RXSYNC_DLY
mdefine_line|#define V_SYNCSER_RXSYNC_DLY(x)            _SB_MAKEVALUE(x,S_SYNCSER_RXSYNC_DLY)
DECL|macro|M_SYNCSER_RXSYNC_LOW
mdefine_line|#define M_SYNCSER_RXSYNC_LOW               _SB_MAKEMASK1(4)
DECL|macro|M_SYNCSER_RXSTRB_LOW
mdefine_line|#define M_SYNCSER_RXSTRB_LOW               _SB_MAKEMASK1(5)
DECL|macro|M_SYNCSER_RXSYNC_EDGE
mdefine_line|#define M_SYNCSER_RXSYNC_EDGE              _SB_MAKEMASK1(6)
DECL|macro|M_SYNCSER_RXSYNC_INT
mdefine_line|#define M_SYNCSER_RXSYNC_INT               _SB_MAKEMASK1(7)
DECL|macro|M_SYNCSER_TXCLK_INV
mdefine_line|#define M_SYNCSER_TXCLK_INV                _SB_MAKEMASK1(8)
DECL|macro|M_SYNCSER_TXCLK_EXT
mdefine_line|#define M_SYNCSER_TXCLK_EXT                _SB_MAKEMASK1(9)
DECL|macro|S_SYNCSER_TXSYNC_DLY
mdefine_line|#define S_SYNCSER_TXSYNC_DLY               10
DECL|macro|M_SYNCSER_TXSYNC_DLY
mdefine_line|#define M_SYNCSER_TXSYNC_DLY               _SB_MAKEMASK(2,S_SYNCSER_TXSYNC_DLY)
DECL|macro|V_SYNCSER_TXSYNC_DLY
mdefine_line|#define V_SYNCSER_TXSYNC_DLY(x)            _SB_MAKEVALUE(x,S_SYNCSER_TXSYNC_DLY)
DECL|macro|M_SYNCSER_TXSYNC_LOW
mdefine_line|#define M_SYNCSER_TXSYNC_LOW               _SB_MAKEMASK1(12)
DECL|macro|M_SYNCSER_TXSTRB_LOW
mdefine_line|#define M_SYNCSER_TXSTRB_LOW               _SB_MAKEMASK1(13)
DECL|macro|M_SYNCSER_TXSYNC_EDGE
mdefine_line|#define M_SYNCSER_TXSYNC_EDGE              _SB_MAKEMASK1(14)
DECL|macro|M_SYNCSER_TXSYNC_INT
mdefine_line|#define M_SYNCSER_TXSYNC_INT               _SB_MAKEMASK1(15)
multiline_comment|/*&n; * Serial Command Register&n; */
DECL|macro|M_SYNCSER_CMD_RX_EN
mdefine_line|#define M_SYNCSER_CMD_RX_EN                _SB_MAKEMASK1(0)
DECL|macro|M_SYNCSER_CMD_TX_EN
mdefine_line|#define M_SYNCSER_CMD_TX_EN                _SB_MAKEMASK1(1)
DECL|macro|M_SYNCSER_CMD_RX_RESET
mdefine_line|#define M_SYNCSER_CMD_RX_RESET             _SB_MAKEMASK1(2)
DECL|macro|M_SYNCSER_CMD_TX_RESET
mdefine_line|#define M_SYNCSER_CMD_TX_RESET             _SB_MAKEMASK1(3)
DECL|macro|M_SYNCSER_CMD_TX_PAUSE
mdefine_line|#define M_SYNCSER_CMD_TX_PAUSE             _SB_MAKEMASK1(5)
multiline_comment|/*&n; * Serial DMA Enable Register&n; */
DECL|macro|M_SYNCSER_DMA_RX_EN
mdefine_line|#define M_SYNCSER_DMA_RX_EN                _SB_MAKEMASK1(0)
DECL|macro|M_SYNCSER_DMA_TX_EN
mdefine_line|#define M_SYNCSER_DMA_TX_EN                _SB_MAKEMASK1(4)
multiline_comment|/*&n; * Serial Status Register&n; */
DECL|macro|M_SYNCSER_RX_CRCERR
mdefine_line|#define M_SYNCSER_RX_CRCERR                _SB_MAKEMASK1(0)
DECL|macro|M_SYNCSER_RX_ABORT
mdefine_line|#define M_SYNCSER_RX_ABORT                 _SB_MAKEMASK1(1)
DECL|macro|M_SYNCSER_RX_OCTET
mdefine_line|#define M_SYNCSER_RX_OCTET                 _SB_MAKEMASK1(2)
DECL|macro|M_SYNCSER_RX_LONGFRM
mdefine_line|#define M_SYNCSER_RX_LONGFRM               _SB_MAKEMASK1(3)
DECL|macro|M_SYNCSER_RX_SHORTFRM
mdefine_line|#define M_SYNCSER_RX_SHORTFRM              _SB_MAKEMASK1(4)
DECL|macro|M_SYNCSER_RX_OVERRUN
mdefine_line|#define M_SYNCSER_RX_OVERRUN               _SB_MAKEMASK1(5)
DECL|macro|M_SYNCSER_RX_SYNC_ERR
mdefine_line|#define M_SYNCSER_RX_SYNC_ERR              _SB_MAKEMASK1(6)
DECL|macro|M_SYNCSER_TX_CRCERR
mdefine_line|#define M_SYNCSER_TX_CRCERR                _SB_MAKEMASK1(8)
DECL|macro|M_SYNCSER_TX_UNDERRUN
mdefine_line|#define M_SYNCSER_TX_UNDERRUN              _SB_MAKEMASK1(9)
DECL|macro|M_SYNCSER_TX_SYNC_ERR
mdefine_line|#define M_SYNCSER_TX_SYNC_ERR              _SB_MAKEMASK1(10)
DECL|macro|M_SYNCSER_TX_PAUSE_COMPLETE
mdefine_line|#define M_SYNCSER_TX_PAUSE_COMPLETE        _SB_MAKEMASK1(11)
DECL|macro|M_SYNCSER_RX_EOP_COUNT
mdefine_line|#define M_SYNCSER_RX_EOP_COUNT             _SB_MAKEMASK1(16)
DECL|macro|M_SYNCSER_RX_EOP_TIMER
mdefine_line|#define M_SYNCSER_RX_EOP_TIMER             _SB_MAKEMASK1(17)
DECL|macro|M_SYNCSER_RX_EOP_SEEN
mdefine_line|#define M_SYNCSER_RX_EOP_SEEN              _SB_MAKEMASK1(18)
DECL|macro|M_SYNCSER_RX_HWM
mdefine_line|#define M_SYNCSER_RX_HWM                   _SB_MAKEMASK1(19)
DECL|macro|M_SYNCSER_RX_LWM
mdefine_line|#define M_SYNCSER_RX_LWM                   _SB_MAKEMASK1(20)
DECL|macro|M_SYNCSER_RX_DSCR
mdefine_line|#define M_SYNCSER_RX_DSCR                  _SB_MAKEMASK1(21)
DECL|macro|M_SYNCSER_RX_DERR
mdefine_line|#define M_SYNCSER_RX_DERR                  _SB_MAKEMASK1(22)
DECL|macro|M_SYNCSER_TX_EOP_COUNT
mdefine_line|#define M_SYNCSER_TX_EOP_COUNT             _SB_MAKEMASK1(24)
DECL|macro|M_SYNCSER_TX_EOP_TIMER
mdefine_line|#define M_SYNCSER_TX_EOP_TIMER             _SB_MAKEMASK1(25)
DECL|macro|M_SYNCSER_TX_EOP_SEEN
mdefine_line|#define M_SYNCSER_TX_EOP_SEEN              _SB_MAKEMASK1(26)
DECL|macro|M_SYNCSER_TX_HWM
mdefine_line|#define M_SYNCSER_TX_HWM                   _SB_MAKEMASK1(27)
DECL|macro|M_SYNCSER_TX_LWM
mdefine_line|#define M_SYNCSER_TX_LWM                   _SB_MAKEMASK1(28)
DECL|macro|M_SYNCSER_TX_DSCR
mdefine_line|#define M_SYNCSER_TX_DSCR                  _SB_MAKEMASK1(29)
DECL|macro|M_SYNCSER_TX_DERR
mdefine_line|#define M_SYNCSER_TX_DERR                  _SB_MAKEMASK1(30)
DECL|macro|M_SYNCSER_TX_DZERO
mdefine_line|#define M_SYNCSER_TX_DZERO                 _SB_MAKEMASK1(31)
multiline_comment|/*&n; * Sequencer Table Entry format&n; */
DECL|macro|M_SYNCSER_SEQ_LAST
mdefine_line|#define M_SYNCSER_SEQ_LAST                 _SB_MAKEMASK1(0)
DECL|macro|M_SYNCSER_SEQ_BYTE
mdefine_line|#define M_SYNCSER_SEQ_BYTE                 _SB_MAKEMASK1(1)
DECL|macro|S_SYNCSER_SEQ_COUNT
mdefine_line|#define S_SYNCSER_SEQ_COUNT                2
DECL|macro|M_SYNCSER_SEQ_COUNT
mdefine_line|#define M_SYNCSER_SEQ_COUNT                _SB_MAKEMASK(4,S_SYNCSER_SEQ_COUNT)
DECL|macro|V_SYNCSER_SEQ_COUNT
mdefine_line|#define V_SYNCSER_SEQ_COUNT(x)             _SB_MAKEVALUE(x,S_SYNCSER_SEQ_COUNT)
DECL|macro|M_SYNCSER_SEQ_ENABLE
mdefine_line|#define M_SYNCSER_SEQ_ENABLE               _SB_MAKEMASK1(6)
DECL|macro|M_SYNCSER_SEQ_STROBE
mdefine_line|#define M_SYNCSER_SEQ_STROBE               _SB_MAKEMASK1(7)
macro_line|#endif
eof
