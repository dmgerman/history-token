multiline_comment|/*&n; *&n;  Copyright (c) Eicon Technology Corporation, 2000.&n; *&n;  This source file is supplied for the use with Eicon&n;  Technology Corporation&squot;s range of DIVA Server Adapters.&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_DEBUG_IF_H__
DECL|macro|__DIVA_DEBUG_IF_H__
mdefine_line|#define __DIVA_DEBUG_IF_H__
DECL|macro|MSG_TYPE_DRV_ID
mdefine_line|#define MSG_TYPE_DRV_ID&t;&t;0x0001
DECL|macro|MSG_TYPE_FLAGS
mdefine_line|#define MSG_TYPE_FLAGS&t;&t;0x0002
DECL|macro|MSG_TYPE_STRING
mdefine_line|#define MSG_TYPE_STRING&t;&t;0x0003
DECL|macro|MSG_TYPE_BINARY
mdefine_line|#define MSG_TYPE_BINARY&t;&t;0x0004
DECL|macro|MSG_TYPE_MLOG
mdefine_line|#define MSG_TYPE_MLOG     0x0005
DECL|macro|MSG_FRAME_MAX_SIZE
mdefine_line|#define MSG_FRAME_MAX_SIZE 2150
DECL|struct|_diva_dbg_entry_head
r_typedef
r_struct
id|_diva_dbg_entry_head
(brace
DECL|member|sequence
id|dword
id|sequence
suffix:semicolon
DECL|member|time_sec
id|dword
id|time_sec
suffix:semicolon
DECL|member|time_usec
id|dword
id|time_usec
suffix:semicolon
DECL|member|facility
id|dword
id|facility
suffix:semicolon
DECL|member|dli
id|dword
id|dli
suffix:semicolon
DECL|member|drv_id
id|dword
id|drv_id
suffix:semicolon
DECL|member|di_cpu
id|dword
id|di_cpu
suffix:semicolon
DECL|member|data_length
id|dword
id|data_length
suffix:semicolon
DECL|typedef|diva_dbg_entry_head_t
)brace
id|diva_dbg_entry_head_t
suffix:semicolon
r_int
id|diva_maint_init
(paren
id|byte
op_star
id|base
comma
r_int
r_int
id|length
comma
r_int
id|do_init
)paren
suffix:semicolon
r_void
op_star
id|diva_maint_finit
(paren
r_void
)paren
suffix:semicolon
id|dword
id|diva_dbg_q_length
(paren
r_void
)paren
suffix:semicolon
id|diva_dbg_entry_head_t
op_star
id|diva_maint_get_message
(paren
id|word
op_star
id|size
comma
id|diva_os_spin_lock_magic_t
op_star
id|old_irql
)paren
suffix:semicolon
r_void
id|diva_maint_ack_message
(paren
r_int
id|do_release
comma
id|diva_os_spin_lock_magic_t
op_star
id|old_irql
)paren
suffix:semicolon
r_void
id|diva_maint_prtComp
(paren
r_char
op_star
id|format
comma
dot
dot
dot
)paren
suffix:semicolon
r_void
id|diva_maint_wakeup_read
(paren
r_void
)paren
suffix:semicolon
r_int
id|diva_get_driver_info
(paren
id|dword
id|id
comma
id|byte
op_star
id|data
comma
r_int
id|data_length
)paren
suffix:semicolon
r_int
id|diva_get_driver_dbg_mask
(paren
id|dword
id|id
comma
id|byte
op_star
id|data
)paren
suffix:semicolon
r_int
id|diva_set_driver_dbg_mask
(paren
id|dword
id|id
comma
id|dword
id|mask
)paren
suffix:semicolon
r_void
id|diva_mnt_remove_xdi_adapter
(paren
r_const
id|DESCRIPTOR
op_star
id|d
)paren
suffix:semicolon
r_void
id|diva_mnt_add_xdi_adapter
(paren
r_const
id|DESCRIPTOR
op_star
id|d
)paren
suffix:semicolon
r_int
id|diva_mnt_shutdown_xdi_adapters
(paren
r_void
)paren
suffix:semicolon
DECL|macro|DITRACE_CMD_GET_DRIVER_INFO
mdefine_line|#define DITRACE_CMD_GET_DRIVER_INFO   1
DECL|macro|DITRACE_READ_DRIVER_DBG_MASK
mdefine_line|#define DITRACE_READ_DRIVER_DBG_MASK  2
DECL|macro|DITRACE_WRITE_DRIVER_DBG_MASK
mdefine_line|#define DITRACE_WRITE_DRIVER_DBG_MASK 3
DECL|macro|DITRACE_READ_TRACE_ENTRY
mdefine_line|#define DITRACE_READ_TRACE_ENTRY      4
DECL|macro|DITRACE_READ_TRACE_ENTRYS
mdefine_line|#define DITRACE_READ_TRACE_ENTRYS     5
multiline_comment|/*&n;  Trace lavels for debug via management interface&n;  */
DECL|macro|DIVA_MGT_DBG_TRACE
mdefine_line|#define DIVA_MGT_DBG_TRACE          0x00000001 /* All trace messages from the card */
DECL|macro|DIVA_MGT_DBG_DCHAN
mdefine_line|#define DIVA_MGT_DBG_DCHAN          0x00000002 /* All D-channel relater trace messages */
DECL|macro|DIVA_MGT_DBG_MDM_PROGRESS
mdefine_line|#define DIVA_MGT_DBG_MDM_PROGRESS   0x00000004 /* Modem progress events */
DECL|macro|DIVA_MGT_DBG_FAX_PROGRESS
mdefine_line|#define DIVA_MGT_DBG_FAX_PROGRESS   0x00000008 /* Fax progress events */
DECL|macro|DIVA_MGT_DBG_IFC_STATISTICS
mdefine_line|#define DIVA_MGT_DBG_IFC_STATISTICS 0x00000010 /* Interface call statistics */
DECL|macro|DIVA_MGT_DBG_MDM_STATISTICS
mdefine_line|#define DIVA_MGT_DBG_MDM_STATISTICS 0x00000020 /* Global modem statistics   */
DECL|macro|DIVA_MGT_DBG_FAX_STATISTICS
mdefine_line|#define DIVA_MGT_DBG_FAX_STATISTICS 0x00000040 /* Global call statistics    */
DECL|macro|DIVA_MGT_DBG_LINE_EVENTS
mdefine_line|#define DIVA_MGT_DBG_LINE_EVENTS    0x00000080 /* Line state events */
DECL|macro|DIVA_MGT_DBG_IFC_EVENTS
mdefine_line|#define DIVA_MGT_DBG_IFC_EVENTS     0x00000100 /* Interface/L1/L2 state events */
DECL|macro|DIVA_MGT_DBG_IFC_BCHANNEL
mdefine_line|#define DIVA_MGT_DBG_IFC_BCHANNEL   0x00000200 /* B-Channel trace for all channels */
DECL|macro|DIVA_MGT_DBG_IFC_AUDIO
mdefine_line|#define DIVA_MGT_DBG_IFC_AUDIO      0x00000400 /* Audio Tap trace for all channels */
macro_line|# endif /* DEBUG_IF___H */
eof
