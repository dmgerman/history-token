multiline_comment|/*&n; * Copyright (C) 2000, 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * Kernel unwind support.&n; */
DECL|macro|UNW_VER
mdefine_line|#define UNW_VER(x)&t;&t;((x) &gt;&gt; 48)
DECL|macro|UNW_FLAG_MASK
mdefine_line|#define UNW_FLAG_MASK&t;&t;0x0000ffff00000000
DECL|macro|UNW_FLAG_OSMASK
mdefine_line|#define UNW_FLAG_OSMASK&t;&t;0x0000f00000000000
DECL|macro|UNW_FLAG_EHANDLER
mdefine_line|#define UNW_FLAG_EHANDLER(x)&t;((x) &amp; 0x0000000100000000L)
DECL|macro|UNW_FLAG_UHANDLER
mdefine_line|#define UNW_FLAG_UHANDLER(x)&t;((x) &amp; 0x0000000200000000L)
DECL|macro|UNW_LENGTH
mdefine_line|#define UNW_LENGTH(x)&t;&t;((x) &amp; 0x00000000ffffffffL)
DECL|enum|unw_register_index
r_enum
id|unw_register_index
(brace
multiline_comment|/* primary unat: */
DECL|enumerator|UNW_REG_PRI_UNAT_GR
id|UNW_REG_PRI_UNAT_GR
comma
DECL|enumerator|UNW_REG_PRI_UNAT_MEM
id|UNW_REG_PRI_UNAT_MEM
comma
multiline_comment|/* register stack */
DECL|enumerator|UNW_REG_BSP
id|UNW_REG_BSP
comma
multiline_comment|/* register stack pointer */
DECL|enumerator|UNW_REG_BSPSTORE
id|UNW_REG_BSPSTORE
comma
DECL|enumerator|UNW_REG_PFS
id|UNW_REG_PFS
comma
multiline_comment|/* previous function state */
DECL|enumerator|UNW_REG_RNAT
id|UNW_REG_RNAT
comma
multiline_comment|/* memory stack */
DECL|enumerator|UNW_REG_PSP
id|UNW_REG_PSP
comma
multiline_comment|/* previous memory stack pointer */
multiline_comment|/* return pointer: */
DECL|enumerator|UNW_REG_RP
id|UNW_REG_RP
comma
multiline_comment|/* preserved registers: */
DECL|enumerator|UNW_REG_R4
DECL|enumerator|UNW_REG_R5
DECL|enumerator|UNW_REG_R6
DECL|enumerator|UNW_REG_R7
id|UNW_REG_R4
comma
id|UNW_REG_R5
comma
id|UNW_REG_R6
comma
id|UNW_REG_R7
comma
DECL|enumerator|UNW_REG_UNAT
DECL|enumerator|UNW_REG_PR
DECL|enumerator|UNW_REG_LC
DECL|enumerator|UNW_REG_FPSR
id|UNW_REG_UNAT
comma
id|UNW_REG_PR
comma
id|UNW_REG_LC
comma
id|UNW_REG_FPSR
comma
DECL|enumerator|UNW_REG_B1
DECL|enumerator|UNW_REG_B2
DECL|enumerator|UNW_REG_B3
DECL|enumerator|UNW_REG_B4
DECL|enumerator|UNW_REG_B5
id|UNW_REG_B1
comma
id|UNW_REG_B2
comma
id|UNW_REG_B3
comma
id|UNW_REG_B4
comma
id|UNW_REG_B5
comma
DECL|enumerator|UNW_REG_F2
DECL|enumerator|UNW_REG_F3
DECL|enumerator|UNW_REG_F4
DECL|enumerator|UNW_REG_F5
id|UNW_REG_F2
comma
id|UNW_REG_F3
comma
id|UNW_REG_F4
comma
id|UNW_REG_F5
comma
DECL|enumerator|UNW_REG_F16
DECL|enumerator|UNW_REG_F17
DECL|enumerator|UNW_REG_F18
DECL|enumerator|UNW_REG_F19
id|UNW_REG_F16
comma
id|UNW_REG_F17
comma
id|UNW_REG_F18
comma
id|UNW_REG_F19
comma
DECL|enumerator|UNW_REG_F20
DECL|enumerator|UNW_REG_F21
DECL|enumerator|UNW_REG_F22
DECL|enumerator|UNW_REG_F23
id|UNW_REG_F20
comma
id|UNW_REG_F21
comma
id|UNW_REG_F22
comma
id|UNW_REG_F23
comma
DECL|enumerator|UNW_REG_F24
DECL|enumerator|UNW_REG_F25
DECL|enumerator|UNW_REG_F26
DECL|enumerator|UNW_REG_F27
id|UNW_REG_F24
comma
id|UNW_REG_F25
comma
id|UNW_REG_F26
comma
id|UNW_REG_F27
comma
DECL|enumerator|UNW_REG_F28
DECL|enumerator|UNW_REG_F29
DECL|enumerator|UNW_REG_F30
DECL|enumerator|UNW_REG_F31
id|UNW_REG_F28
comma
id|UNW_REG_F29
comma
id|UNW_REG_F30
comma
id|UNW_REG_F31
comma
DECL|enumerator|UNW_NUM_REGS
id|UNW_NUM_REGS
)brace
suffix:semicolon
DECL|struct|unw_info_block
r_struct
id|unw_info_block
(brace
DECL|member|header
id|u64
id|header
suffix:semicolon
DECL|member|desc
id|u64
id|desc
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* unwind descriptors */
multiline_comment|/* personality routine and language-specific data follow behind descriptors */
)brace
suffix:semicolon
DECL|struct|unw_table_entry
r_struct
id|unw_table_entry
(brace
DECL|member|start_offset
id|u64
id|start_offset
suffix:semicolon
DECL|member|end_offset
id|u64
id|end_offset
suffix:semicolon
DECL|member|info_offset
id|u64
id|info_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|unw_table
r_struct
id|unw_table
(brace
DECL|member|next
r_struct
id|unw_table
op_star
id|next
suffix:semicolon
multiline_comment|/* must be first member! */
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
multiline_comment|/* global pointer for this load-module */
DECL|member|segment_base
r_int
r_int
id|segment_base
suffix:semicolon
multiline_comment|/* base for offsets in the unwind table entries */
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
DECL|member|array
r_const
r_struct
id|unw_table_entry
op_star
id|array
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|unw_where
r_enum
id|unw_where
(brace
DECL|enumerator|UNW_WHERE_NONE
id|UNW_WHERE_NONE
comma
multiline_comment|/* register isn&squot;t saved at all */
DECL|enumerator|UNW_WHERE_GR
id|UNW_WHERE_GR
comma
multiline_comment|/* register is saved in a general register */
DECL|enumerator|UNW_WHERE_FR
id|UNW_WHERE_FR
comma
multiline_comment|/* register is saved in a floating-point register */
DECL|enumerator|UNW_WHERE_BR
id|UNW_WHERE_BR
comma
multiline_comment|/* register is saved in a branch register */
DECL|enumerator|UNW_WHERE_SPREL
id|UNW_WHERE_SPREL
comma
multiline_comment|/* register is saved on memstack (sp-relative) */
DECL|enumerator|UNW_WHERE_PSPREL
id|UNW_WHERE_PSPREL
comma
multiline_comment|/* register is saved on memstack (psp-relative) */
multiline_comment|/*&n;&t; * At the end of each prologue these locations get resolved to&n;&t; * UNW_WHERE_PSPREL and UNW_WHERE_GR, respectively:&n;&t; */
DECL|enumerator|UNW_WHERE_SPILL_HOME
id|UNW_WHERE_SPILL_HOME
comma
multiline_comment|/* register is saved in its spill home */
DECL|enumerator|UNW_WHERE_GR_SAVE
id|UNW_WHERE_GR_SAVE
multiline_comment|/* register is saved in next general register */
)brace
suffix:semicolon
DECL|macro|UNW_WHEN_NEVER
mdefine_line|#define UNW_WHEN_NEVER&t;0x7fffffff
DECL|struct|unw_reg_info
r_struct
id|unw_reg_info
(brace
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
multiline_comment|/* save location: register number or offset */
DECL|member|where
r_enum
id|unw_where
id|where
suffix:semicolon
multiline_comment|/* where the register gets saved */
DECL|member|when
r_int
id|when
suffix:semicolon
multiline_comment|/* when the register gets saved */
)brace
suffix:semicolon
DECL|struct|unw_reg_state
r_struct
id|unw_reg_state
(brace
DECL|member|next
r_struct
id|unw_reg_state
op_star
id|next
suffix:semicolon
multiline_comment|/* next (outer) element on state stack */
DECL|member|reg
r_struct
id|unw_reg_info
id|reg
(braket
id|UNW_NUM_REGS
)braket
suffix:semicolon
multiline_comment|/* register save locations */
)brace
suffix:semicolon
DECL|struct|unw_labeled_state
r_struct
id|unw_labeled_state
(brace
DECL|member|next
r_struct
id|unw_labeled_state
op_star
id|next
suffix:semicolon
multiline_comment|/* next labeled state (or NULL) */
DECL|member|label
r_int
r_int
id|label
suffix:semicolon
multiline_comment|/* label for this state */
DECL|member|saved_state
r_struct
id|unw_reg_state
id|saved_state
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|unw_state_record
r_struct
id|unw_state_record
(brace
DECL|member|first_region
r_int
r_int
id|first_region
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* is this the first region? */
DECL|member|done
r_int
r_int
id|done
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* are we done scanning descriptors? */
DECL|member|any_spills
r_int
r_int
id|any_spills
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* got any register spills? */
DECL|member|in_body
r_int
r_int
id|in_body
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* are we inside a body (as opposed to a prologue)? */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* see UNW_FLAG_* in unwind.h */
DECL|member|imask
id|u8
op_star
id|imask
suffix:semicolon
multiline_comment|/* imask of of spill_mask record or NULL */
DECL|member|pr_val
r_int
r_int
id|pr_val
suffix:semicolon
multiline_comment|/* predicate values */
DECL|member|pr_mask
r_int
r_int
id|pr_mask
suffix:semicolon
multiline_comment|/* predicate mask */
DECL|member|spill_offset
r_int
id|spill_offset
suffix:semicolon
multiline_comment|/* psp-relative offset for spill base */
DECL|member|region_start
r_int
id|region_start
suffix:semicolon
DECL|member|region_len
r_int
id|region_len
suffix:semicolon
DECL|member|epilogue_start
r_int
id|epilogue_start
suffix:semicolon
DECL|member|epilogue_count
r_int
id|epilogue_count
suffix:semicolon
DECL|member|when_target
r_int
id|when_target
suffix:semicolon
DECL|member|gr_save_loc
id|u8
id|gr_save_loc
suffix:semicolon
multiline_comment|/* next general register to use for saving a register */
DECL|member|return_link_reg
id|u8
id|return_link_reg
suffix:semicolon
multiline_comment|/* branch register in which the return link is passed */
DECL|member|labeled_states
r_struct
id|unw_labeled_state
op_star
id|labeled_states
suffix:semicolon
multiline_comment|/* list of all labeled states */
DECL|member|curr
r_struct
id|unw_reg_state
id|curr
suffix:semicolon
multiline_comment|/* current state */
)brace
suffix:semicolon
DECL|enum|unw_nat_type
r_enum
id|unw_nat_type
(brace
DECL|enumerator|UNW_NAT_NONE
id|UNW_NAT_NONE
comma
multiline_comment|/* NaT not represented */
DECL|enumerator|UNW_NAT_VAL
id|UNW_NAT_VAL
comma
multiline_comment|/* NaT represented by NaT value (fp reg) */
DECL|enumerator|UNW_NAT_MEMSTK
id|UNW_NAT_MEMSTK
comma
multiline_comment|/* NaT value is in unat word at offset OFF  */
DECL|enumerator|UNW_NAT_REGSTK
id|UNW_NAT_REGSTK
multiline_comment|/* NaT is in rnat */
)brace
suffix:semicolon
DECL|enum|unw_insn_opcode
r_enum
id|unw_insn_opcode
(brace
DECL|enumerator|UNW_INSN_ADD
id|UNW_INSN_ADD
comma
multiline_comment|/* s[dst] += val */
DECL|enumerator|UNW_INSN_ADD_PSP
id|UNW_INSN_ADD_PSP
comma
multiline_comment|/* s[dst] = (s.psp + val) */
DECL|enumerator|UNW_INSN_ADD_SP
id|UNW_INSN_ADD_SP
comma
multiline_comment|/* s[dst] = (s.sp + val) */
DECL|enumerator|UNW_INSN_MOVE
id|UNW_INSN_MOVE
comma
multiline_comment|/* s[dst] = s[val] */
DECL|enumerator|UNW_INSN_MOVE2
id|UNW_INSN_MOVE2
comma
multiline_comment|/* s[dst] = s[val]; s[dst+1] = s[val+1] */
DECL|enumerator|UNW_INSN_MOVE_STACKED
id|UNW_INSN_MOVE_STACKED
comma
multiline_comment|/* s[dst] = ia64_rse_skip(*s.bsp, val) */
DECL|enumerator|UNW_INSN_SETNAT_MEMSTK
id|UNW_INSN_SETNAT_MEMSTK
comma
multiline_comment|/* s[dst+1].nat.type = MEMSTK;&n;&t;&t;&t;&t;&t;   s[dst+1].nat.off = *s.pri_unat - s[dst] */
DECL|enumerator|UNW_INSN_SETNAT_TYPE
id|UNW_INSN_SETNAT_TYPE
comma
multiline_comment|/* s[dst+1].nat.type = val */
DECL|enumerator|UNW_INSN_LOAD
id|UNW_INSN_LOAD
multiline_comment|/* s[dst] = *s[val] */
)brace
suffix:semicolon
DECL|struct|unw_insn
r_struct
id|unw_insn
(brace
DECL|member|opc
r_int
r_int
id|opc
suffix:colon
l_int|4
suffix:semicolon
DECL|member|dst
r_int
r_int
id|dst
suffix:colon
l_int|9
suffix:semicolon
DECL|member|val
r_int
r_int
id|val
suffix:colon
l_int|19
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Preserved general static registers (r4-r7) give rise to two script&n; * instructions; everything else yields at most one instruction; at&n; * the end of the script, the psp gets popped, accounting for one more&n; * instruction.&n; */
DECL|macro|UNW_MAX_SCRIPT_LEN
mdefine_line|#define UNW_MAX_SCRIPT_LEN&t;(UNW_NUM_REGS + 5)
DECL|struct|unw_script
r_struct
id|unw_script
(brace
DECL|member|ip
r_int
r_int
id|ip
suffix:semicolon
multiline_comment|/* ip this script is for */
DECL|member|pr_mask
r_int
r_int
id|pr_mask
suffix:semicolon
multiline_comment|/* mask of predicates script depends on */
DECL|member|pr_val
r_int
r_int
id|pr_val
suffix:semicolon
multiline_comment|/* predicate values this script is for */
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* see UNW_FLAG_* in unwind.h */
DECL|member|lru_chain
r_int
r_int
id|lru_chain
suffix:semicolon
multiline_comment|/* used for least-recently-used chain */
DECL|member|coll_chain
r_int
r_int
id|coll_chain
suffix:semicolon
multiline_comment|/* used for hash collisions */
DECL|member|hint
r_int
r_int
id|hint
suffix:semicolon
multiline_comment|/* hint for next script to try (or -1) */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* number of instructions in script */
DECL|member|insn
r_struct
id|unw_insn
id|insn
(braket
id|UNW_MAX_SCRIPT_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
eof
