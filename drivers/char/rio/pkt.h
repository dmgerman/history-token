multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******            P A C K E T   H E A D E R   F I L E&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra / Jeremy Rolls&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _pkt_h
DECL|macro|_pkt_h
mdefine_line|#define _pkt_h 1
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
multiline_comment|/* static char *_rio_pkt_h_sccs = &quot;@(#)pkt.h&t;1.8&quot;; */
macro_line|#endif
macro_line|#endif
DECL|macro|MAX_TTL
mdefine_line|#define MAX_TTL         0xf
DECL|macro|PKT_CMD_BIT
mdefine_line|#define PKT_CMD_BIT     ((ushort) 0x080)
DECL|macro|PKT_CMD_DATA
mdefine_line|#define PKT_CMD_DATA    ((ushort) 0x080)
DECL|macro|PKT_ACK
mdefine_line|#define PKT_ACK         ((ushort) 0x040)
DECL|macro|PKT_TGL
mdefine_line|#define PKT_TGL         ((ushort) 0x020)
DECL|macro|PKT_LEN_MASK
mdefine_line|#define PKT_LEN_MASK    ((ushort) 0x07f)
DECL|macro|DATA_WNDW
mdefine_line|#define DATA_WNDW       ((ushort) 0x10)
DECL|macro|PKT_TTL_MASK
mdefine_line|#define PKT_TTL_MASK    ((ushort) 0x0f)
DECL|macro|PKT_MAX_DATA_LEN
mdefine_line|#define PKT_MAX_DATA_LEN   72
DECL|macro|PKT_LENGTH
mdefine_line|#define PKT_LENGTH         sizeof(struct PKT)
DECL|macro|SYNC_PKT_LENGTH
mdefine_line|#define SYNC_PKT_LENGTH    (PKT_LENGTH + 4)
DECL|macro|CONTROL_PKT_LEN_MASK
mdefine_line|#define CONTROL_PKT_LEN_MASK PKT_LEN_MASK
DECL|macro|CONTROL_PKT_CMD_BIT
mdefine_line|#define CONTROL_PKT_CMD_BIT  PKT_CMD_BIT
DECL|macro|CONTROL_PKT_ACK
mdefine_line|#define CONTROL_PKT_ACK (PKT_ACK &lt;&lt; 8)
DECL|macro|CONTROL_PKT_TGL
mdefine_line|#define CONTROL_PKT_TGL (PKT_TGL &lt;&lt; 8)
DECL|macro|CONTROL_PKT_TTL_MASK
mdefine_line|#define CONTROL_PKT_TTL_MASK (PKT_TTL_MASK &lt;&lt; 8)
DECL|macro|CONTROL_DATA_WNDW
mdefine_line|#define CONTROL_DATA_WNDW  (DATA_WNDW &lt;&lt; 8)
DECL|struct|PKT
r_struct
id|PKT
(brace
macro_line|#ifdef INKERNEL
DECL|member|dest_unit
id|BYTE
id|dest_unit
suffix:semicolon
multiline_comment|/* Destination Unit Id */
DECL|member|dest_port
id|BYTE
id|dest_port
suffix:semicolon
multiline_comment|/* Destination POrt */
DECL|member|src_unit
id|BYTE
id|src_unit
suffix:semicolon
multiline_comment|/* Source Unit Id */
DECL|member|src_port
id|BYTE
id|src_port
suffix:semicolon
multiline_comment|/* Source POrt */
macro_line|#else
r_union
(brace
id|ushort
id|destination
suffix:semicolon
multiline_comment|/* Complete destination */
r_struct
(brace
r_int
r_char
id|unit
suffix:semicolon
multiline_comment|/* Destination unit */
r_int
r_char
id|port
suffix:semicolon
multiline_comment|/* Destination port */
)brace
id|s1
suffix:semicolon
)brace
id|u1
suffix:semicolon
r_union
(brace
id|ushort
id|source
suffix:semicolon
multiline_comment|/* Complete source */
r_struct
(brace
r_int
r_char
id|unit
suffix:semicolon
multiline_comment|/* Source unit */
r_int
r_char
id|port
suffix:semicolon
multiline_comment|/* Source port */
)brace
id|s2
suffix:semicolon
)brace
id|u2
suffix:semicolon
macro_line|#endif
macro_line|#ifdef INKERNEL
DECL|member|len
id|BYTE
id|len
suffix:semicolon
DECL|member|control
id|BYTE
id|control
suffix:semicolon
macro_line|#else
r_union
(brace
DECL|member|control
id|ushort
id|control
suffix:semicolon
r_struct
(brace
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
DECL|member|control
r_int
r_char
id|control
suffix:semicolon
DECL|member|s3
)brace
id|s3
suffix:semicolon
DECL|member|u3
)brace
id|u3
suffix:semicolon
macro_line|#endif
DECL|member|data
id|BYTE
id|data
(braket
id|PKT_MAX_DATA_LEN
)braket
suffix:semicolon
multiline_comment|/* Actual data :-) */
DECL|member|csum
id|WORD
id|csum
suffix:semicolon
multiline_comment|/* C-SUM */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
