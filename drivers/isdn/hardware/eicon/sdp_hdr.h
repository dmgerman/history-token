multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_SOFT_DSP_TASK_ENTRY_H__
DECL|macro|__DIVA_SOFT_DSP_TASK_ENTRY_H__
mdefine_line|#define __DIVA_SOFT_DSP_TASK_ENTRY_H__
multiline_comment|/*&n; The soft DSP image is described by binary header contained on begin of this&n; image:&n;OFFSET FROM IMAGE START |  VARIABLE&n;------------------------------------------------------------------------&n; DIVA_MIPS_TASK_IMAGE_LINK_OFFS   |  link to the next image&n;  ----------------------------------------------------------------------&n; DIVA_MIPS_TASK_IMAGE_GP_OFFS    |  image gp register value, void*&n;  ----------------------------------------------------------------------&n; DIVA_MIPS_TASK_IMAGE_ENTRY_OFFS   |  diva_mips_sdp_task_entry_t*&n;  ----------------------------------------------------------------------&n; DIVA_MIPS_TASK_IMAGE_LOAD_ADDR_OFFS |  image image start address (void*)&n;  ----------------------------------------------------------------------&n; DIVA_MIPS_TASK_IMAGE_END_ADDR_OFFS |  image image end address   (void*)&n;  ----------------------------------------------------------------------&n; DIVA_MIPS_TASK_IMAGE_ID_STRING_OFFS |  image id string char[...];&n;  ----------------------------------------------------------------------&n; */
DECL|macro|DIVA_MIPS_TASK_IMAGE_LINK_OFFS
mdefine_line|#define DIVA_MIPS_TASK_IMAGE_LINK_OFFS   0x6C
DECL|macro|DIVA_MIPS_TASK_IMAGE_GP_OFFS
mdefine_line|#define DIVA_MIPS_TASK_IMAGE_GP_OFFS    0x70
DECL|macro|DIVA_MIPS_TASK_IMAGE_ENTRY_OFFS
mdefine_line|#define DIVA_MIPS_TASK_IMAGE_ENTRY_OFFS   0x74
DECL|macro|DIVA_MIPS_TASK_IMAGE_LOAD_ADDR_OFFS
mdefine_line|#define DIVA_MIPS_TASK_IMAGE_LOAD_ADDR_OFFS 0x78
DECL|macro|DIVA_MIPS_TASK_IMAGE_END_ADDR_OFFS
mdefine_line|#define DIVA_MIPS_TASK_IMAGE_END_ADDR_OFFS 0x7c
DECL|macro|DIVA_MIPS_TASK_IMAGE_ID_STRING_OFFS
mdefine_line|#define DIVA_MIPS_TASK_IMAGE_ID_STRING_OFFS 0x80
multiline_comment|/*&n; This function is called in order to set GP register of this task&n; This function should be always called before any function of the&n; task is called&n; */
DECL|typedef|diva_task_set_prog_gp_proc_t
r_typedef
r_void
(paren
op_star
id|diva_task_set_prog_gp_proc_t
)paren
(paren
r_void
op_star
id|new_gp
)paren
suffix:semicolon
multiline_comment|/*&n; This function is called to clear .bss at task initialization step&n; */
DECL|typedef|diva_task_sys_reset_proc_t
r_typedef
r_void
(paren
op_star
id|diva_task_sys_reset_proc_t
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; This function is called in order to provide GP of master call to&n; task, that will be used by calls from the task to the master&n; */
DECL|typedef|diva_task_set_main_gp_proc_t
r_typedef
r_void
(paren
op_star
id|diva_task_set_main_gp_proc_t
)paren
(paren
r_void
op_star
id|main_gp
)paren
suffix:semicolon
multiline_comment|/*&n; This function is called to provide address of &squot;dprintf&squot; function&n; to the task&n; */
DECL|typedef|diva_prt_proc_t
r_typedef
id|word
(paren
op_star
id|diva_prt_proc_t
)paren
(paren
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|typedef|diva_task_set_prt_proc_t
r_typedef
r_void
(paren
op_star
id|diva_task_set_prt_proc_t
)paren
(paren
id|diva_prt_proc_t
id|fn
)paren
suffix:semicolon
multiline_comment|/*&n; This function is called to set task PID&n; */
DECL|typedef|diva_task_set_pid_proc_t
r_typedef
r_void
(paren
op_star
id|diva_task_set_pid_proc_t
)paren
(paren
id|dword
id|id
)paren
suffix:semicolon
multiline_comment|/*&n; This function is called for run-time task init&n; */
DECL|typedef|diva_task_run_time_init_proc_t
r_typedef
r_int
(paren
op_star
id|diva_task_run_time_init_proc_t
)paren
(paren
r_void
op_star
comma
id|dword
)paren
suffix:semicolon
multiline_comment|/*&n; This function is called from system scheduler or from timer&n; */
DECL|typedef|diva_task_callback_proc_t
r_typedef
r_void
(paren
op_star
id|diva_task_callback_proc_t
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; This callback is used by task to get current time im mS&n;  */
DECL|typedef|diva_task_get_tick_count_proc_t
r_typedef
id|dword
(paren
op_star
id|diva_task_get_tick_count_proc_t
)paren
(paren
r_void
)paren
suffix:semicolon
r_typedef
r_void
(paren
op_star
id|diva_task_set_get_time_proc_t
)paren
(paren
"&bslash;"
id|diva_task_get_tick_count_proc_t
id|fn
)paren
suffix:semicolon
DECL|struct|_diva_mips_sdp_task_entry
r_typedef
r_struct
id|_diva_mips_sdp_task_entry
(brace
DECL|member|set_gp_proc
id|diva_task_set_prog_gp_proc_t
id|set_gp_proc
suffix:semicolon
DECL|member|sys_reset_proc
id|diva_task_sys_reset_proc_t
id|sys_reset_proc
suffix:semicolon
DECL|member|set_main_gp_proc
id|diva_task_set_main_gp_proc_t
id|set_main_gp_proc
suffix:semicolon
DECL|member|set_dprintf_proc
id|diva_task_set_prt_proc_t
id|set_dprintf_proc
suffix:semicolon
DECL|member|set_pid_proc
id|diva_task_set_pid_proc_t
id|set_pid_proc
suffix:semicolon
DECL|member|run_time_init_proc
id|diva_task_run_time_init_proc_t
id|run_time_init_proc
suffix:semicolon
DECL|member|task_callback_proc
id|diva_task_callback_proc_t
id|task_callback_proc
suffix:semicolon
DECL|member|timer_callback_proc
id|diva_task_callback_proc_t
id|timer_callback_proc
suffix:semicolon
DECL|member|set_get_time_proc
id|diva_task_set_get_time_proc_t
id|set_get_time_proc
suffix:semicolon
DECL|member|last_entry_proc
r_void
op_star
id|last_entry_proc
suffix:semicolon
DECL|typedef|diva_mips_sdp_task_entry_t
)brace
id|diva_mips_sdp_task_entry_t
suffix:semicolon
multiline_comment|/*&n; &squot;last_entry_proc&squot; should be set to zero and is used for future extensuios&n; */
DECL|struct|_diva_mips_sw_task
r_typedef
r_struct
id|_diva_mips_sw_task
(brace
DECL|member|sdp_entry
id|diva_mips_sdp_task_entry_t
id|sdp_entry
suffix:semicolon
DECL|member|sdp_gp_reg
r_void
op_star
id|sdp_gp_reg
suffix:semicolon
DECL|member|own_gp_reg
r_void
op_star
id|own_gp_reg
suffix:semicolon
DECL|typedef|diva_mips_sw_task_t
)brace
id|diva_mips_sw_task_t
suffix:semicolon
macro_line|#if !defined(DIVA_BRI2F_SDP_1_NAME)
DECL|macro|DIVA_BRI2F_SDP_1_NAME
mdefine_line|#define DIVA_BRI2F_SDP_1_NAME &quot;sdp0.2q0&quot;
macro_line|#endif
macro_line|#if !defined(DIVA_BRI2F_SDP_2_NAME)
DECL|macro|DIVA_BRI2F_SDP_2_NAME
mdefine_line|#define DIVA_BRI2F_SDP_2_NAME &quot;sdp1.2q0&quot;
macro_line|#endif
macro_line|#endif
eof
