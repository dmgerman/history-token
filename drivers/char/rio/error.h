multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******     E R R O R  H E A D E R   F I L E&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef lint
multiline_comment|/* static char *_rio_error_h_sccs = &quot;@(#)error.h&t;1.3&quot;; */
macro_line|#endif
DECL|macro|E_NO_ERROR
mdefine_line|#define E_NO_ERROR                       ((ushort) 0)
DECL|macro|E_PROCESS_NOT_INIT
mdefine_line|#define E_PROCESS_NOT_INIT               ((ushort) 1)
DECL|macro|E_LINK_TIMEOUT
mdefine_line|#define E_LINK_TIMEOUT                   ((ushort) 2)
DECL|macro|E_NO_ROUTE
mdefine_line|#define E_NO_ROUTE                       ((ushort) 3)
DECL|macro|E_CONFUSED
mdefine_line|#define E_CONFUSED                       ((ushort) 4)
DECL|macro|E_HOME
mdefine_line|#define E_HOME                           ((ushort) 5)
DECL|macro|E_CSUM_FAIL
mdefine_line|#define E_CSUM_FAIL                      ((ushort) 6)
DECL|macro|E_DISCONNECTED
mdefine_line|#define E_DISCONNECTED                   ((ushort) 7)
DECL|macro|E_BAD_RUP
mdefine_line|#define E_BAD_RUP                        ((ushort) 8)
DECL|macro|E_NO_VIRGIN
mdefine_line|#define E_NO_VIRGIN                      ((ushort) 9)
DECL|macro|E_BOOT_RUP_BUSY
mdefine_line|#define E_BOOT_RUP_BUSY                  ((ushort) 10)
multiline_comment|/*************************************************&n;     * Parsed to mem_halt()&n;     ************************************************/
DECL|macro|E_CHANALLOC
mdefine_line|#define E_CHANALLOC                      ((ushort) 0x80)
DECL|macro|E_POLL_ALLOC
mdefine_line|#define E_POLL_ALLOC                     ((ushort) 0x81)
DECL|macro|E_LTTWAKE
mdefine_line|#define E_LTTWAKE                        ((ushort) 0x82)
DECL|macro|E_LTT_ALLOC
mdefine_line|#define E_LTT_ALLOC                      ((ushort) 0x83)
DECL|macro|E_LRT_ALLOC
mdefine_line|#define E_LRT_ALLOC                      ((ushort) 0x84)
DECL|macro|E_CIRRUS
mdefine_line|#define E_CIRRUS                         ((ushort) 0x85)
DECL|macro|E_MONITOR
mdefine_line|#define E_MONITOR                        ((ushort) 0x86)
DECL|macro|E_PHB_ALLOC
mdefine_line|#define E_PHB_ALLOC                      ((ushort) 0x87)
DECL|macro|E_ARRAY_ALLOC
mdefine_line|#define E_ARRAY_ALLOC                    ((ushort) 0x88)
DECL|macro|E_QBUF_ALLOC
mdefine_line|#define E_QBUF_ALLOC                     ((ushort) 0x89)
DECL|macro|E_PKT_ALLOC
mdefine_line|#define E_PKT_ALLOC                      ((ushort) 0x8a)
DECL|macro|E_GET_TX_Q_BUF
mdefine_line|#define E_GET_TX_Q_BUF                   ((ushort) 0x8b)
DECL|macro|E_GET_RX_Q_BUF
mdefine_line|#define E_GET_RX_Q_BUF                   ((ushort) 0x8c)
DECL|macro|E_MEM_OUT
mdefine_line|#define E_MEM_OUT                        ((ushort) 0x8d)
DECL|macro|E_MMU_INIT
mdefine_line|#define E_MMU_INIT                       ((ushort) 0x8e)
DECL|macro|E_LTT_INIT
mdefine_line|#define E_LTT_INIT                       ((ushort) 0x8f)
DECL|macro|E_LRT_INIT
mdefine_line|#define E_LRT_INIT                       ((ushort) 0x90)
DECL|macro|E_LINK_RUN
mdefine_line|#define E_LINK_RUN                       ((ushort) 0x91)
DECL|macro|E_MONITOR_ALLOC
mdefine_line|#define E_MONITOR_ALLOC                  ((ushort) 0x92)
DECL|macro|E_MONITOR_INIT
mdefine_line|#define E_MONITOR_INIT                   ((ushort) 0x93)
DECL|macro|E_POLL_INIT
mdefine_line|#define E_POLL_INIT                      ((ushort) 0x94)
multiline_comment|/*********** end of file ***********/
eof
