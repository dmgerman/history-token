multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******               H O S T   M E M O R Y  M A P&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra / Jeremy Rolls&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;6/4/1991   jonb&t;&t;     Made changes to accomodate Mips R3230 bus&n; ***************************************************************************/
macro_line|#ifndef _parmap_h
DECL|macro|_parmap_h
mdefine_line|#define _parmap_h
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
multiline_comment|/* static char *_rio_parmmap_h_sccs = &quot;@(#)parmmap.h&t;1.4&quot;; */
macro_line|#endif
macro_line|#endif
DECL|typedef|PARM_MAP
r_typedef
r_struct
id|PARM_MAP
id|PARM_MAP
suffix:semicolon
DECL|struct|PARM_MAP
r_struct
id|PARM_MAP
(brace
DECL|member|phb_ptr
id|PHB_ptr
id|phb_ptr
suffix:semicolon
multiline_comment|/* Pointer to the PHB array */
DECL|member|phb_num_ptr
id|WORD_ptr
id|phb_num_ptr
suffix:semicolon
multiline_comment|/* Ptr to Number of PHB&squot;s */
DECL|member|free_list
id|FREE_LIST_ptr
id|free_list
suffix:semicolon
multiline_comment|/* Free List pointer */
DECL|member|free_list_end
id|FREE_LIST_ptr
id|free_list_end
suffix:semicolon
multiline_comment|/* Free List End pointer */
DECL|member|q_free_list_ptr
id|Q_BUF_ptr_ptr
id|q_free_list_ptr
suffix:semicolon
multiline_comment|/* Ptr to Q_BUF variable */
DECL|member|unit_id_ptr
id|BYTE_ptr
id|unit_id_ptr
suffix:semicolon
multiline_comment|/* Unit Id */
DECL|member|link_str_ptr
id|LPB_ptr
id|link_str_ptr
suffix:semicolon
multiline_comment|/* Link Structure Array */
DECL|member|bootloader_1
id|BYTE_ptr
id|bootloader_1
suffix:semicolon
multiline_comment|/* 1st Stage Boot Loader */
DECL|member|bootloader_2
id|BYTE_ptr
id|bootloader_2
suffix:semicolon
multiline_comment|/* 2nd Stage Boot Loader */
DECL|member|port_route_map_ptr
id|WORD_ptr
id|port_route_map_ptr
suffix:semicolon
multiline_comment|/* Port Route Map */
DECL|member|route_ptr
id|ROUTE_STR_ptr
id|route_ptr
suffix:semicolon
multiline_comment|/* Unit Route Map */
DECL|member|map_present
id|NUMBER_ptr
id|map_present
suffix:semicolon
multiline_comment|/* Route Map present */
DECL|member|pkt_num
id|NUMBER
id|pkt_num
suffix:semicolon
multiline_comment|/* Total number of packets */
DECL|member|q_num
id|NUMBER
id|q_num
suffix:semicolon
multiline_comment|/* Total number of Q packets */
DECL|member|buffers_per_port
id|WORD
id|buffers_per_port
suffix:semicolon
multiline_comment|/* Number of buffers per port */
DECL|member|heap_size
id|WORD
id|heap_size
suffix:semicolon
multiline_comment|/* Initial size of heap */
DECL|member|heap_left
id|WORD
id|heap_left
suffix:semicolon
multiline_comment|/* Current Heap left */
DECL|member|error
id|WORD
id|error
suffix:semicolon
multiline_comment|/* Error code */
DECL|member|tx_max
id|WORD
id|tx_max
suffix:semicolon
multiline_comment|/* Max number of tx pkts per phb */
DECL|member|rx_max
id|WORD
id|rx_max
suffix:semicolon
multiline_comment|/* Max number of rx pkts per phb */
DECL|member|rx_limit
id|WORD
id|rx_limit
suffix:semicolon
multiline_comment|/* For high / low watermarks */
DECL|member|links
id|NUMBER
id|links
suffix:semicolon
multiline_comment|/* Links to use */
DECL|member|timer
id|NUMBER
id|timer
suffix:semicolon
multiline_comment|/* Interrupts per second */
DECL|member|rups
id|RUP_ptr
id|rups
suffix:semicolon
multiline_comment|/* Pointer to the RUPs */
DECL|member|max_phb
id|WORD
id|max_phb
suffix:semicolon
multiline_comment|/* Mostly for debugging */
DECL|member|living
id|WORD
id|living
suffix:semicolon
multiline_comment|/* Just increments!! */
DECL|member|init_done
id|WORD
id|init_done
suffix:semicolon
multiline_comment|/* Initialisation over */
DECL|member|booting_link
id|WORD
id|booting_link
suffix:semicolon
DECL|member|idle_count
id|WORD
id|idle_count
suffix:semicolon
multiline_comment|/* Idle time counter */
DECL|member|busy_count
id|WORD
id|busy_count
suffix:semicolon
multiline_comment|/* Busy counter */
DECL|member|idle_control
id|WORD
id|idle_control
suffix:semicolon
multiline_comment|/* Control Idle Process */
macro_line|#if defined(HOST) || defined(INKERNEL)
DECL|member|tx_intr
id|WORD
id|tx_intr
suffix:semicolon
multiline_comment|/* TX interrupt pending */
DECL|member|rx_intr
id|WORD
id|rx_intr
suffix:semicolon
multiline_comment|/* RX interrupt pending */
DECL|member|rup_intr
id|WORD
id|rup_intr
suffix:semicolon
multiline_comment|/* RUP interrupt pending */
macro_line|#endif
macro_line|#if defined(RTA)
DECL|member|dying_count
id|WORD
id|dying_count
suffix:semicolon
multiline_comment|/* Count of processes dead */
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
