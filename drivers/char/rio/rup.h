multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******               R U P   S T R U C T U R E&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _rup_h
DECL|macro|_rup_h
mdefine_line|#define _rup_h 1
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
multiline_comment|/* static char *_rio_rup_h_sccs = &quot;@(#)rup.h&t;1.5&quot;; */
macro_line|#endif
macro_line|#endif
macro_line|#if defined( HOST ) || defined( INKERNEL )
DECL|macro|MAX_RUP
mdefine_line|#define MAX_RUP          ((short) 16) 
macro_line|#endif
macro_line|#ifdef RTA
DECL|macro|MAX_RUP
mdefine_line|#define MAX_RUP          ((short) 1)
macro_line|#endif
DECL|macro|PKTS_PER_RUP
mdefine_line|#define PKTS_PER_RUP     ((short) 2)     /* They are always used in pairs */
multiline_comment|/*************************************************&n; * Define all the  packet request stuff&n; ************************************************/
DECL|macro|TX_RUP_INACTIVE
mdefine_line|#define TX_RUP_INACTIVE          0        /* Nothing to transmit */
DECL|macro|TX_PACKET_READY
mdefine_line|#define TX_PACKET_READY          1        /* Transmit packet ready */
DECL|macro|TX_LOCK_RUP
mdefine_line|#define TX_LOCK_RUP              2        /* Transmit side locked */
DECL|macro|RX_RUP_INACTIVE
mdefine_line|#define RX_RUP_INACTIVE          0        /* Nothing received */
DECL|macro|RX_PACKET_READY
mdefine_line|#define RX_PACKET_READY          1        /* Packet received */
DECL|macro|RUP_NO_OWNER
mdefine_line|#define RUP_NO_OWNER             0xff     /* RUP not owned by any process */
DECL|struct|RUP
r_struct
id|RUP
(brace
DECL|member|txpkt
id|PKT_ptr
id|txpkt
suffix:semicolon
multiline_comment|/* Outgoing packet */
DECL|member|rxpkt
id|PKT_ptr
id|rxpkt
suffix:semicolon
multiline_comment|/* Incoming packet */
DECL|member|link
id|WORD
id|link
suffix:semicolon
multiline_comment|/* Which link to send down? */
DECL|member|rup_dest_unit
id|BYTE
id|rup_dest_unit
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Destination unit */
DECL|member|handshake
id|WORD
id|handshake
suffix:semicolon
multiline_comment|/* For handshaking */
DECL|member|timeout
id|WORD
id|timeout
suffix:semicolon
multiline_comment|/* Timeout */
DECL|member|status
id|WORD
id|status
suffix:semicolon
multiline_comment|/* Status */
DECL|member|txcontrol
id|WORD
id|txcontrol
suffix:semicolon
multiline_comment|/* Transmit control */
DECL|member|rxcontrol
id|WORD
id|rxcontrol
suffix:semicolon
multiline_comment|/* Receive control */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
