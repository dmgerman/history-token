multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******      P R O T O C O L    S T A T U S   S T R U C T U R E      *******&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra / Jeremy Rolls&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _protsts_h
DECL|macro|_protsts_h
mdefine_line|#define _protsts_h 1
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
multiline_comment|/* static char *_rio_protsts_h_sccs = &quot;@(#)protsts.h&t;1.4&quot;; */
macro_line|#endif
macro_line|#endif
multiline_comment|/*************************************************&n; * ACK bit. Last Packet received OK. Set by&n; * rxpkt to indicate that the Packet has been&n; * received OK and that the LTT must set the ACK&n; * bit in the next outward bound Packet&n; * and re-set by LTT&squot;s after xmit.&n; *&n; * Gets shoved into rx_status&n; ************************************************/
DECL|macro|PHB_RX_LAST_PKT_ACKED
mdefine_line|#define PHB_RX_LAST_PKT_ACKED    ((ushort) 0x080)
multiline_comment|/*******************************************************&n; * The Rx TOGGLE bit.&n; * Stuffed into rx_status by RXPKT&n; ******************************************************/
DECL|macro|PHB_RX_DATA_WNDW
mdefine_line|#define PHB_RX_DATA_WNDW         ((ushort) 0x040)
multiline_comment|/*******************************************************&n; * The Rx TOGGLE bit. Matches the setting in PKT.H&n; * Stuffed into rx_status&n; ******************************************************/
DECL|macro|PHB_RX_TGL
mdefine_line|#define PHB_RX_TGL               ((ushort) 0x2000)
multiline_comment|/*************************************************&n; * This bit is set by the LRT to indicate that&n; * an ACK (packet) must be returned.&n; *&n; * Gets shoved into tx_status&n; ************************************************/
DECL|macro|PHB_TX_SEND_PKT_ACK
mdefine_line|#define PHB_TX_SEND_PKT_ACK      ((ushort) 0x08)
multiline_comment|/*************************************************&n; * Set by LTT to indicate that an ACK is required&n; *************************************************/
DECL|macro|PHB_TX_ACK_RQRD
mdefine_line|#define PHB_TX_ACK_RQRD         ((ushort) 0x01)
multiline_comment|/*******************************************************&n; * The Tx TOGGLE bit.&n; * Stuffed into tx_status by RXPKT from the PKT WndW&n; * field. Looked by the LTT when the NEXT Packet&n; * is going to be sent.&n; ******************************************************/
DECL|macro|PHB_TX_DATA_WNDW
mdefine_line|#define PHB_TX_DATA_WNDW         ((ushort) 0x04)
multiline_comment|/*******************************************************&n; * The Tx TOGGLE bit. Matches the setting in PKT.H&n; * Stuffed into tx_status&n; ******************************************************/
DECL|macro|PHB_TX_TGL
mdefine_line|#define PHB_TX_TGL               ((ushort) 0x02)
multiline_comment|/*******************************************************&n; * Request intr bit. Set when the queue has gone quiet&n; * and the PHB has requested an interrupt.&n; ******************************************************/
DECL|macro|PHB_TX_INTR
mdefine_line|#define PHB_TX_INTR             ((ushort) 0x100)
multiline_comment|/*******************************************************&n; * SET if the PHB cannot send any more data down the&n; * Link&n; ******************************************************/
DECL|macro|PHB_TX_HANDSHAKE
mdefine_line|#define PHB_TX_HANDSHAKE         ((ushort) 0x010)
DECL|macro|RUP_SEND_WNDW
mdefine_line|#define RUP_SEND_WNDW&t;&t; ((ushort) 0x08) ;
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
