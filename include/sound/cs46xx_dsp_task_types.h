multiline_comment|/*&n; *  The driver for the Cirrus Logic&squot;s Sound Fusion CS46XX based soundcards&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; *&n; * NOTE: comments are copy/paste from cwcemb80.lst &n; * provided by Tom Woller at Cirrus (my only&n; * documentation about the SP OS running inside&n; * the DSP) &n; */
macro_line|#ifndef __CS46XX_DSP_TASK_TYPES_H__
DECL|macro|__CS46XX_DSP_TASK_TYPES_H__
mdefine_line|#define __CS46XX_DSP_TASK_TYPES_H__
macro_line|#include &quot;cs46xx_dsp_scb_types.h&quot;
multiline_comment|/*********************************************************************************************&n;Example hierarchy of stream control blocks in the SP&n;&n;hfgTree&n;Ptr____Call (c)&n;       &bslash;&n; -------+------         -------------      -------------      -------------      -----&n;| SBlaster IF  |______&bslash;| Foreground  |___&bslash;| Middlegr&squot;nd |___&bslash;| Background  |___&bslash;| Nul |&n;|              |Goto  /| tree header |g  /| tree header |g  /| tree header |g  /| SCB |r&n; -------------- (g)     -------------      -------------      -------------      -----&n;       |c                     |c                 |c                 |c&n;       |                      |                  |                  |&n;      &bslash;/                  -------------      -------------      -------------   &n;                       | Foreground  |_&bslash;  | Middlegr&squot;nd |_&bslash;  | Background  |_&bslash;&n;                       |     tree    |g/  |    tree     |g/  |     tree    |g/&n;                        -------------      -------------      -------------   &n;                              |c                 |c                 |c&n;                              |                  |                  | &n;                             &bslash;/                 &bslash;/                 &bslash;/ &n;&n;*********************************************************************************************/
DECL|macro|HFG_FIRST_EXECUTE_MODE
mdefine_line|#define&t;&t;HFG_FIRST_EXECUTE_MODE&t;&t;&t;0x0001
DECL|macro|HFG_FIRST_EXECUTE_MODE_BIT
mdefine_line|#define&t;&t;HFG_FIRST_EXECUTE_MODE_BIT&t;&t;0
DECL|macro|HFG_CONTEXT_SWITCH_MODE
mdefine_line|#define&t;&t;HFG_CONTEXT_SWITCH_MODE&t;&t;&t;0x0002
DECL|macro|HFG_CONTEXT_SWITCH_MODE_BIT
mdefine_line|#define&t;&t;HFG_CONTEXT_SWITCH_MODE_BIT&t;&t;1
DECL|macro|MAX_FG_STACK_SIZE
mdefine_line|#define MAX_FG_STACK_SIZE &t;32&t;&t;&t;/* THESE NEED TO BE COMPUTED PROPERLY */
DECL|macro|MAX_MG_STACK_SIZE
mdefine_line|#define MAX_MG_STACK_SIZE &t;16
DECL|macro|MAX_BG_STACK_SIZE
mdefine_line|#define MAX_BG_STACK_SIZE &t;9
DECL|macro|MAX_HFG_STACK_SIZE
mdefine_line|#define MAX_HFG_STACK_SIZE&t;4
DECL|macro|SLEEP_ACTIVE_INCREMENT
mdefine_line|#define SLEEP_ACTIVE_INCREMENT&t;&t;0&t;&t;/* Enable task tree thread to go to sleep&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;   This should only ever be used on the Background thread */
DECL|macro|STANDARD_ACTIVE_INCREMENT
mdefine_line|#define STANDARD_ACTIVE_INCREMENT&t;1&t;&t;/* Task tree thread normal operation */
DECL|macro|SUSPEND_ACTIVE_INCREMENT
mdefine_line|#define SUSPEND_ACTIVE_INCREMENT&t;2&t;&t;/* Cause execution to suspend in the task tree thread&n;                                               This should only ever be used on the Background thread */
DECL|macro|HOSTFLAGS_DISABLE_BG_SLEEP
mdefine_line|#define HOSTFLAGS_DISABLE_BG_SLEEP  0       /* Host-controlled flag that determines whether we go to sleep&n;                                               at the end of BG */
multiline_comment|/* Minimal context save area for Hyper Forground */
DECL|struct|_hf_save_area_t
r_typedef
r_struct
id|_hf_save_area_t
(brace
DECL|member|r10_save
id|u32
id|r10_save
suffix:semicolon
DECL|member|r54_save
id|u32
id|r54_save
suffix:semicolon
DECL|member|r98_save
id|u32
id|r98_save
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|status_save
comma
id|ind_save
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|rci1_save
comma
id|rci0_save
)paren
id|u32
id|r32_save
suffix:semicolon
id|u32
id|r76_save
suffix:semicolon
DECL|member|rsd2_save
id|u32
id|rsd2_save
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|rsi2_save
comma
multiline_comment|/* See TaskTreeParameterBlock for &n;&t;&t;&t;&t;     remainder of registers  */
id|rsa2Save
)paren
multiline_comment|/* saved as part of HFG context  */
DECL|typedef|hf_save_area_t
)brace
id|hf_save_area_t
suffix:semicolon
multiline_comment|/* Task link data structure */
DECL|struct|_tree_link_t
r_typedef
r_struct
id|_tree_link_t
(brace
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
multiline_comment|/* Pointer to sibling task control block */
id|next_scb
comma
multiline_comment|/* Pointer to child task control block */
id|sub_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
multiline_comment|/* Pointer to code entry point */
id|entry_point
comma
multiline_comment|/* Pointer to local data */
id|this_spb
)paren
DECL|typedef|tree_link_t
)brace
id|tree_link_t
suffix:semicolon
DECL|struct|_task_tree_data_t
r_typedef
r_struct
id|_task_tree_data_t
(brace
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
multiline_comment|/* Initial tock count; controls task tree execution rate */
id|tock_count_limit
comma
multiline_comment|/* Tock down counter */
id|tock_count
)paren
multiline_comment|/* Add to ActiveCount when TockCountLimit reached: &n;&t;   Subtract on task tree termination */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|active_tncrement
comma
multiline_comment|/* Number of pending activations for task tree */
id|active_count
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
multiline_comment|/* BitNumber to enable modification of correct bit in ActiveTaskFlags */
id|active_bit
comma
multiline_comment|/* Pointer to OS location for indicating current activity on task level */
id|active_task_flags_ptr
)paren
multiline_comment|/* Data structure for controlling movement of memory blocks:- &n;&t;   currently unused */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|mem_upd_ptr
comma
multiline_comment|/* Data structure for controlling synchronous link update */
id|link_upd_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
multiline_comment|/* Save area for remainder of full context. */
id|save_area
comma
multiline_comment|/* Address of start of local stack for data storage */
id|data_stack_base_ptr
)paren
DECL|typedef|task_tree_data_t
)brace
id|task_tree_data_t
suffix:semicolon
DECL|struct|_interval_timer_data_t
r_typedef
r_struct
id|_interval_timer_data_t
(brace
multiline_comment|/* These data items have the same relative locations to those */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|interval_timer_period
comma
id|itd_unused
)paren
multiline_comment|/* used for this data in the SPOS control block for SPOS 1.0 */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|num_FG_ticks_this_interval
comma
id|num_intervals
)paren
DECL|typedef|interval_timer_data_t
)brace
id|interval_timer_data_t
suffix:semicolon
multiline_comment|/* This structure contains extra storage for the task tree&n;   Currently, this additional data is related only to a full context save */
DECL|struct|_task_tree_context_block_t
r_typedef
r_struct
id|_task_tree_context_block_t
(brace
multiline_comment|/* Up to 10 values are saved onto the stack.  8 for the task tree, 1 for&n;&t;   The access to the context switch (call or interrupt), and 1 spare that&n;&t;   users should never use.  This last may be required by the system */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|stack1
comma
id|stack0
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|stack3
comma
id|stack2
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|stack5
comma
id|stack4
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|stack7
comma
id|stack6
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|stack9
comma
id|stack8
)paren
id|u32
id|saverfe
suffix:semicolon
multiline_comment|/* Value may be overwriten by stack save algorithm.&n;&t;   Retain the size of the stack data saved here if used */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|reserved1
comma
id|stack_size
)paren
id|u32
id|saverba
suffix:semicolon
multiline_comment|/* (HFG) */
DECL|member|saverdc
id|u32
id|saverdc
suffix:semicolon
DECL|member|savers_config_23
id|u32
id|savers_config_23
suffix:semicolon
multiline_comment|/* (HFG) */
DECL|member|savers_DMA23
id|u32
id|savers_DMA23
suffix:semicolon
multiline_comment|/* (HFG) */
DECL|member|saversa0
id|u32
id|saversa0
suffix:semicolon
DECL|member|saversi0
id|u32
id|saversi0
suffix:semicolon
DECL|member|saversa1
id|u32
id|saversa1
suffix:semicolon
DECL|member|saversi1
id|u32
id|saversi1
suffix:semicolon
DECL|member|saversa3
id|u32
id|saversa3
suffix:semicolon
DECL|member|saversd0
id|u32
id|saversd0
suffix:semicolon
DECL|member|saversd1
id|u32
id|saversd1
suffix:semicolon
DECL|member|saversd3
id|u32
id|saversd3
suffix:semicolon
DECL|member|savers_config01
id|u32
id|savers_config01
suffix:semicolon
DECL|member|savers_DMA01
id|u32
id|savers_DMA01
suffix:semicolon
DECL|member|saveacc0hl
id|u32
id|saveacc0hl
suffix:semicolon
DECL|member|saveacc1hl
id|u32
id|saveacc1hl
suffix:semicolon
DECL|member|saveacc0xacc1x
id|u32
id|saveacc0xacc1x
suffix:semicolon
DECL|member|saveacc2hl
id|u32
id|saveacc2hl
suffix:semicolon
DECL|member|saveacc3hl
id|u32
id|saveacc3hl
suffix:semicolon
DECL|member|saveacc2xacc3x
id|u32
id|saveacc2xacc3x
suffix:semicolon
DECL|member|saveaux0hl
id|u32
id|saveaux0hl
suffix:semicolon
DECL|member|saveaux1hl
id|u32
id|saveaux1hl
suffix:semicolon
DECL|member|saveaux0xaux1x
id|u32
id|saveaux0xaux1x
suffix:semicolon
DECL|member|saveaux2hl
id|u32
id|saveaux2hl
suffix:semicolon
DECL|member|saveaux3hl
id|u32
id|saveaux3hl
suffix:semicolon
DECL|member|saveaux2xaux3x
id|u32
id|saveaux2xaux3x
suffix:semicolon
DECL|member|savershouthl
id|u32
id|savershouthl
suffix:semicolon
DECL|member|savershoutxmacmode
id|u32
id|savershoutxmacmode
suffix:semicolon
DECL|typedef|task_tree_context_block_t
)brace
id|task_tree_context_block_t
suffix:semicolon
DECL|struct|_task_tree_control_block_t
r_typedef
r_struct
id|_task_tree_control_block_t
(brace
DECL|member|context
id|hf_save_area_t
id|context
suffix:semicolon
DECL|member|links
id|tree_link_t
id|links
suffix:semicolon
DECL|member|data
id|task_tree_data_t
id|data
suffix:semicolon
DECL|member|context_blk
id|task_tree_context_block_t
id|context_blk
suffix:semicolon
DECL|member|int_timer
id|interval_timer_data_t
id|int_timer
suffix:semicolon
DECL|typedef|task_tree_control_block_t
)brace
id|task_tree_control_block_t
suffix:semicolon
macro_line|#endif /* __DSP_TASK_TYPES_H__ */
eof
