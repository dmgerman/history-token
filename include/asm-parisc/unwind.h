macro_line|#ifndef _UNWIND_H_
DECL|macro|_UNWIND_H_
mdefine_line|#define _UNWIND_H_
multiline_comment|/* From ABI specifications */
DECL|struct|unwind_table_entry
r_struct
id|unwind_table_entry
(brace
DECL|member|region_start
r_int
r_int
id|region_start
suffix:semicolon
DECL|member|region_end
r_int
r_int
id|region_end
suffix:semicolon
DECL|member|Cannot_unwind
r_int
r_int
id|Cannot_unwind
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|Millicode
r_int
r_int
id|Millicode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|Millicode_save_sr0
r_int
r_int
id|Millicode_save_sr0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|Region_description
r_int
r_int
id|Region_description
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 3..4 */
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 5 */
DECL|member|Entry_SR
r_int
r_int
id|Entry_SR
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 6 */
DECL|member|Entry_FR
r_int
r_int
id|Entry_FR
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* number saved */
multiline_comment|/* 7..10 */
DECL|member|Entry_GR
r_int
r_int
id|Entry_GR
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* number saved */
multiline_comment|/* 11..15 */
DECL|member|Args_stored
r_int
r_int
id|Args_stored
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16 */
DECL|member|Variable_Frame
r_int
r_int
id|Variable_Frame
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 17 */
DECL|member|Separate_Package_Body
r_int
r_int
id|Separate_Package_Body
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 18 */
DECL|member|Frame_Extension_Millicode
r_int
r_int
id|Frame_Extension_Millicode
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19 */
DECL|member|Stack_Overflow_Check
r_int
r_int
id|Stack_Overflow_Check
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20 */
DECL|member|Two_Instruction_SP_Increment
r_int
r_int
id|Two_Instruction_SP_Increment
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 21 */
DECL|member|Ada_Region
r_int
r_int
id|Ada_Region
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 22 */
DECL|member|cxx_info
r_int
r_int
id|cxx_info
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 23 */
DECL|member|cxx_try_catch
r_int
r_int
id|cxx_try_catch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24 */
DECL|member|sched_entry_seq
r_int
r_int
id|sched_entry_seq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 25 */
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 26 */
DECL|member|Save_SP
r_int
r_int
id|Save_SP
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 27 */
DECL|member|Save_RP
r_int
r_int
id|Save_RP
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 28 */
DECL|member|Save_MRP_in_frame
r_int
r_int
id|Save_MRP_in_frame
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29 */
DECL|member|extn_ptr_defined
r_int
r_int
id|extn_ptr_defined
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 30 */
DECL|member|Cleanup_defined
r_int
r_int
id|Cleanup_defined
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31 */
DECL|member|MPE_XL_interrupt_marker
r_int
r_int
id|MPE_XL_interrupt_marker
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|HP_UX_interrupt_marker
r_int
r_int
id|HP_UX_interrupt_marker
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|Large_frame
r_int
r_int
id|Large_frame
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|Pseudo_SP_Set
r_int
r_int
id|Pseudo_SP_Set
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|reserved4
r_int
r_int
id|reserved4
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 4 */
DECL|member|Total_frame_size
r_int
r_int
id|Total_frame_size
suffix:colon
l_int|27
suffix:semicolon
multiline_comment|/* 5..31 */
)brace
suffix:semicolon
DECL|struct|unwind_table
r_struct
id|unwind_table
(brace
DECL|member|next
r_struct
id|unwind_table
op_star
id|next
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|gp
r_int
r_int
id|gp
suffix:semicolon
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
DECL|member|table
r_const
r_struct
id|unwind_table_entry
op_star
id|table
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|unwind_frame_info
r_struct
id|unwind_frame_info
(brace
DECL|member|t
r_struct
id|task_struct
op_star
id|t
suffix:semicolon
multiline_comment|/* Eventually we would like to be able to get at any of the registers&n;&t;   available; but for now we only try to get the sp and ip for each&n;&t;   frame */
multiline_comment|/* struct pt_regs regs; */
DECL|member|sp
DECL|member|ip
DECL|member|rp
r_int
r_int
id|sp
comma
id|ip
comma
id|rp
suffix:semicolon
DECL|member|prev_sp
DECL|member|prev_ip
r_int
r_int
id|prev_sp
comma
id|prev_ip
suffix:semicolon
)brace
suffix:semicolon
r_void
op_star
id|unwind_table_add
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|base_addr
comma
r_int
r_int
id|gp
comma
r_void
op_star
id|start
comma
r_void
op_star
id|end
)paren
suffix:semicolon
r_void
id|unwind_frame_init
c_func
(paren
r_struct
id|unwind_frame_info
op_star
id|info
comma
r_struct
id|task_struct
op_star
id|t
comma
r_int
r_int
id|sp
comma
r_int
r_int
id|ip
comma
r_int
r_int
id|rp
)paren
suffix:semicolon
r_void
id|unwind_frame_init_from_blocked_task
c_func
(paren
r_struct
id|unwind_frame_info
op_star
id|info
comma
r_struct
id|task_struct
op_star
id|t
)paren
suffix:semicolon
r_void
id|unwind_frame_init_running
c_func
(paren
r_struct
id|unwind_frame_info
op_star
id|info
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|unwind_once
c_func
(paren
r_struct
id|unwind_frame_info
op_star
id|info
)paren
suffix:semicolon
r_int
id|unwind_to_user
c_func
(paren
r_struct
id|unwind_frame_info
op_star
id|info
)paren
suffix:semicolon
macro_line|#endif
eof
