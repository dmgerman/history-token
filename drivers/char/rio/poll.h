multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                      P O L L&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra / Jeremy Rolls&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _poll_h
DECL|macro|_poll_h
mdefine_line|#define _poll_h
macro_line|#ifndef lint
macro_line|#ifdef SCCS_LABELS
DECL|variable|_rio_poll_h_sccs
r_static
r_char
op_star
id|_rio_poll_h_sccs
op_assign
l_string|&quot;@(#)poll.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef HOST
DECL|macro|POLL_STACK
mdefine_line|#define POLL_STACK            100
macro_line|#endif
macro_line|#ifdef RTA
DECL|macro|POLL_STACK
mdefine_line|#define POLL_STACK            200
macro_line|#endif
DECL|macro|POLL_PERIOD
mdefine_line|#define POLL_PERIOD           (int) SECOND
multiline_comment|/* The various poll commands */
DECL|macro|POLL_POLL
mdefine_line|#define POLL_POLL             0            /* We are connected and happy.. */
DECL|macro|POLL_INTRO
mdefine_line|#define POLL_INTRO            1            /* Introduction packet */
DECL|macro|POLL_TOPOLOGY
mdefine_line|#define POLL_TOPOLOGY         2            /* Topology update */
DECL|macro|POLL_ASSIGN
mdefine_line|#define POLL_ASSIGN           3            /* ID assign */
DECL|macro|POLL_FOAD
mdefine_line|#define POLL_FOAD             4            /* F*** Off And Die */
DECL|macro|POLL_LMD
mdefine_line|#define POLL_LMD&t;      5&t;&t;   /* Let Me Die */
DECL|macro|POLL_DYB
mdefine_line|#define POLL_DYB&t;      6&t;&t;   /* Die You Ba***** */
multiline_comment|/* The way data fields are split up for POLL packets */
DECL|macro|POLL_HOST_SERIAL
mdefine_line|#define POLL_HOST_SERIAL      2            /* Host who booted me */
DECL|macro|POLL_MY_SERIAL
mdefine_line|#define POLL_MY_SERIAL        6            /* My serial number */
DECL|macro|POLL_YOUR_ID
mdefine_line|#define POLL_YOUR_ID          1            /* Your ID number */
DECL|macro|POLL_TOPOLOGY_FIELDS
mdefine_line|#define POLL_TOPOLOGY_FIELDS  2            /* Topology maps */
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
