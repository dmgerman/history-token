multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******           C O M M A N D   P A C K E T   H E A D E R S&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _cmd_h
DECL|macro|_cmd_h
mdefine_line|#define _cmd_h
macro_line|#ifndef lint
macro_line|#ifdef SCCS
DECL|variable|_rio_cmd_h_sccs
r_static
r_char
op_star
id|_rio_cmd_h_sccs
op_assign
l_string|&quot;@(#)cmd.h&t;1.1&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|macro|PRE_EMPTIVE_CMD
mdefine_line|#define PRE_EMPTIVE_CMD         0x80
DECL|macro|INLINE_CMD
mdefine_line|#define INLINE_CMD              ~PRE_EMPTIVE_CMD
DECL|macro|CMD_IGNORE_PKT
mdefine_line|#define CMD_IGNORE_PKT          ( (ushort) 0)
DECL|macro|CMD_STATUS_REQ
mdefine_line|#define CMD_STATUS_REQ          ( (ushort) 1)
DECL|macro|CMD_UNIT_STATUS_REQ
mdefine_line|#define CMD_UNIT_STATUS_REQ     ( (ushort) 2)     /* Is this needed ??? */
DECL|macro|CMD_CONF_PORT
mdefine_line|#define CMD_CONF_PORT           ( (ushort) 3)
DECL|macro|CMD_CONF_UNIT
mdefine_line|#define CMD_CONF_UNIT           ( (ushort) 4)
DECL|macro|CMD_ROUTE_MAP_REQ
mdefine_line|#define CMD_ROUTE_MAP_REQ       ( (ushort) 5)
DECL|macro|CMD_FLUSH_TX
mdefine_line|#define CMD_FLUSH_TX            ( (ushort) 6)
DECL|macro|CMD_FLUSH_RX
mdefine_line|#define CMD_FLUSH_RX            ( (ushort) 7)
DECL|macro|CMD_PARTION_PORT
mdefine_line|#define CMD_PARTION_PORT        ( (ushort) 8)
DECL|macro|CMD_RESET_PORT
mdefine_line|#define CMD_RESET_PORT          ( (ushort) 0x0a)
DECL|macro|CMD_BOOT_UNIT
mdefine_line|#define CMD_BOOT_UNIT           ( (ushort) 0x0b)
DECL|macro|CMD_FOUND_UNIT
mdefine_line|#define CMD_FOUND_UNIT          ( (ushort) 0x0c)
DECL|macro|CMD_ATTACHED_RTA_2
mdefine_line|#define CMD_ATTACHED_RTA_2      ( (ushort) 0x0d)
DECL|macro|CMD_PROVIDE_BOOT
mdefine_line|#define CMD_PROVIDE_BOOT        ( (ushort) 0x0e)
DECL|macro|CMD_CIRRUS
mdefine_line|#define CMD_CIRRUS              ( (ushort) 0x0f)
DECL|macro|FORM_STATUS_PKT
mdefine_line|#define FORM_STATUS_PKT         ( (ushort) 1 )
DECL|macro|FORM_POLL_PKT
mdefine_line|#define FORM_POLL_PKT           ( (ushort) 2 )
DECL|macro|FORM_LINK_STATUS_PKT
mdefine_line|#define FORM_LINK_STATUS_PKT    ( (ushort) 3 )
DECL|macro|CMD_DATA_PORT
mdefine_line|#define CMD_DATA_PORT           ( (ushort) 1 )
DECL|macro|CMD_DATA
mdefine_line|#define CMD_DATA                ( (ushort) 2 )
DECL|macro|CMD_TX_PART
mdefine_line|#define CMD_TX_PART             ( (ushort) 2 )
DECL|macro|CMD_RX_PART
mdefine_line|#define CMD_RX_PART             ( (ushort) 3 )
DECL|macro|CMD_RX_LIMIT
mdefine_line|#define CMD_RX_LIMIT            ( (ushort) 4 )
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
