multiline_comment|/*---------------------------------------------------------------------------+&n; |  load_store.c                                                             |&n; |                                                                           |&n; | This file contains most of the code to interpret the FPU instructions     |&n; | which load and store from user memory.                                    |&n; |                                                                           |&n; | Copyright (C) 1992,1993,1994,1997                                         |&n; |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |&n; |                       Australia.  E-mail   billm@suburbia.net             |&n; |                                                                           |&n; |                                                                           |&n; +---------------------------------------------------------------------------*/
multiline_comment|/*---------------------------------------------------------------------------+&n; | Note:                                                                     |&n; |    The file contains code which accesses user memory.                     |&n; |    Emulator static data may change when user memory is accessed, due to   |&n; |    other processes using the emulator while swapping is in progress.      |&n; +---------------------------------------------------------------------------*/
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;fpu_system.h&quot;
macro_line|#include &quot;exception.h&quot;
macro_line|#include &quot;fpu_emu.h&quot;
macro_line|#include &quot;status_w.h&quot;
macro_line|#include &quot;control_w.h&quot;
DECL|macro|_NONE_
mdefine_line|#define _NONE_ 0   /* st0_ptr etc not needed */
DECL|macro|_REG0_
mdefine_line|#define _REG0_ 1   /* Will be storing st(0) */
DECL|macro|_PUSH_
mdefine_line|#define _PUSH_ 3   /* Need to check for space to push onto stack */
DECL|macro|_null_
mdefine_line|#define _null_ 4   /* Function illegal or not implemented */
DECL|macro|pop_0
mdefine_line|#define pop_0()&t;{ FPU_settag0(TAG_Empty); top++; }
DECL|variable|type_table
r_static
id|u_char
r_const
id|type_table
(braket
l_int|32
)braket
op_assign
(brace
id|_PUSH_
comma
id|_PUSH_
comma
id|_PUSH_
comma
id|_PUSH_
comma
id|_null_
comma
id|_null_
comma
id|_null_
comma
id|_null_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_REG0_
comma
id|_NONE_
comma
id|_null_
comma
id|_NONE_
comma
id|_PUSH_
comma
id|_NONE_
comma
id|_PUSH_
comma
id|_null_
comma
id|_PUSH_
comma
id|_NONE_
comma
id|_null_
comma
id|_NONE_
comma
id|_REG0_
comma
id|_NONE_
comma
id|_REG0_
comma
id|_NONE_
comma
id|_REG0_
)brace
suffix:semicolon
DECL|variable|data_sizes_16
id|u_char
r_const
id|data_sizes_16
(braket
l_int|32
)braket
op_assign
(brace
l_int|4
comma
l_int|4
comma
l_int|8
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|4
comma
l_int|8
comma
l_int|2
comma
l_int|4
comma
l_int|4
comma
l_int|8
comma
l_int|2
comma
l_int|14
comma
l_int|0
comma
l_int|94
comma
l_int|10
comma
l_int|2
comma
l_int|10
comma
l_int|0
comma
l_int|8
comma
l_int|14
comma
l_int|0
comma
l_int|94
comma
l_int|10
comma
l_int|2
comma
l_int|10
comma
l_int|2
comma
l_int|8
)brace
suffix:semicolon
DECL|variable|data_sizes_32
r_static
id|u_char
r_const
id|data_sizes_32
(braket
l_int|32
)braket
op_assign
(brace
l_int|4
comma
l_int|4
comma
l_int|8
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|4
comma
l_int|8
comma
l_int|2
comma
l_int|4
comma
l_int|4
comma
l_int|8
comma
l_int|2
comma
l_int|28
comma
l_int|0
comma
l_int|108
comma
l_int|10
comma
l_int|2
comma
l_int|10
comma
l_int|0
comma
l_int|8
comma
l_int|28
comma
l_int|0
comma
l_int|108
comma
l_int|10
comma
l_int|2
comma
l_int|10
comma
l_int|2
comma
l_int|8
)brace
suffix:semicolon
DECL|function|FPU_load_store
r_int
id|FPU_load_store
c_func
(paren
id|u_char
id|type
comma
id|fpu_addr_modes
id|addr_modes
comma
r_void
id|__user
op_star
id|data_address
)paren
(brace
id|FPU_REG
id|loaded_data
suffix:semicolon
id|FPU_REG
op_star
id|st0_ptr
suffix:semicolon
id|u_char
id|st0_tag
op_assign
id|TAG_Empty
suffix:semicolon
multiline_comment|/* This is just to stop a gcc warning. */
id|u_char
id|loaded_tag
suffix:semicolon
id|st0_ptr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Initialized just to stop compiler warnings. */
r_if
c_cond
(paren
id|addr_modes.default_mode
op_amp
id|PROTECTED
)paren
(brace
r_if
c_cond
(paren
id|addr_modes.default_mode
op_eq
id|SEG32
)paren
(brace
r_if
c_cond
(paren
id|access_limit
OL
id|data_sizes_32
(braket
id|type
)braket
)paren
id|math_abort
c_func
(paren
id|FPU_info
comma
id|SIGSEGV
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr_modes.default_mode
op_eq
id|PM16
)paren
(brace
r_if
c_cond
(paren
id|access_limit
OL
id|data_sizes_16
(braket
id|type
)braket
)paren
id|math_abort
c_func
(paren
id|FPU_info
comma
id|SIGSEGV
)paren
suffix:semicolon
)brace
macro_line|#ifdef PARANOID
r_else
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x140
)paren
suffix:semicolon
macro_line|#endif /* PARANOID */
)brace
r_switch
c_cond
(paren
id|type_table
(braket
id|type
)braket
)paren
(brace
r_case
id|_NONE_
suffix:colon
r_break
suffix:semicolon
r_case
id|_REG0_
suffix:colon
id|st0_ptr
op_assign
op_amp
id|st
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Some of these instructions pop after&n;&t;&t;&t;&t; storing */
id|st0_tag
op_assign
id|FPU_gettag0
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_PUSH_
suffix:colon
(brace
r_if
c_cond
(paren
id|FPU_gettagi
c_func
(paren
op_minus
l_int|1
)paren
op_ne
id|TAG_Empty
)paren
(brace
id|FPU_stack_overflow
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|top
op_decrement
suffix:semicolon
id|st0_ptr
op_assign
op_amp
id|st
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|_null_
suffix:colon
id|FPU_illegal
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#ifdef PARANOID
r_default
suffix:colon
id|EXCEPTION
c_func
(paren
id|EX_INTERNAL
op_or
l_int|0x141
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#endif /* PARANOID */
)brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_int|000
suffix:colon
multiline_comment|/* fld m32real */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|loaded_tag
op_assign
id|FPU_load_single
c_func
(paren
(paren
r_float
id|__user
op_star
)paren
id|data_address
comma
op_amp
id|loaded_data
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|loaded_tag
op_eq
id|TAG_Special
)paren
op_logical_and
id|isNaN
c_func
(paren
op_amp
id|loaded_data
)paren
op_logical_and
(paren
id|real_1op_NaN
c_func
(paren
op_amp
id|loaded_data
)paren
OL
l_int|0
)paren
)paren
(brace
id|top
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|FPU_copy_to_reg0
c_func
(paren
op_amp
id|loaded_data
comma
id|loaded_tag
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|001
suffix:colon
multiline_comment|/* fild m32int */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|loaded_tag
op_assign
id|FPU_load_int32
c_func
(paren
(paren
r_int
id|__user
op_star
)paren
id|data_address
comma
op_amp
id|loaded_data
)paren
suffix:semicolon
id|FPU_copy_to_reg0
c_func
(paren
op_amp
id|loaded_data
comma
id|loaded_tag
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|002
suffix:colon
multiline_comment|/* fld m64real */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|loaded_tag
op_assign
id|FPU_load_double
c_func
(paren
(paren
r_float
id|__user
op_star
)paren
id|data_address
comma
op_amp
id|loaded_data
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|loaded_tag
op_eq
id|TAG_Special
)paren
op_logical_and
id|isNaN
c_func
(paren
op_amp
id|loaded_data
)paren
op_logical_and
(paren
id|real_1op_NaN
c_func
(paren
op_amp
id|loaded_data
)paren
OL
l_int|0
)paren
)paren
(brace
id|top
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|FPU_copy_to_reg0
c_func
(paren
op_amp
id|loaded_data
comma
id|loaded_tag
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|003
suffix:colon
multiline_comment|/* fild m16int */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|loaded_tag
op_assign
id|FPU_load_int16
c_func
(paren
(paren
r_int
id|__user
op_star
)paren
id|data_address
comma
op_amp
id|loaded_data
)paren
suffix:semicolon
id|FPU_copy_to_reg0
c_func
(paren
op_amp
id|loaded_data
comma
id|loaded_tag
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|010
suffix:colon
multiline_comment|/* fst m32real */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|FPU_store_single
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
r_float
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|011
suffix:colon
multiline_comment|/* fist m32int */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|FPU_store_int32
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
r_int
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|012
suffix:colon
multiline_comment|/* fst m64real */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|FPU_store_double
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
r_float
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|013
suffix:colon
multiline_comment|/* fist m16int */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|FPU_store_int16
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
r_int
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|014
suffix:colon
multiline_comment|/* fstp m32real */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPU_store_single
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
r_float
id|__user
op_star
)paren
id|data_address
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t;     (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|015
suffix:colon
multiline_comment|/* fistp m32int */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPU_store_int32
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
r_int
id|__user
op_star
)paren
id|data_address
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t;     (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|016
suffix:colon
multiline_comment|/* fstp m64real */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPU_store_double
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
r_float
id|__user
op_star
)paren
id|data_address
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t;     (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|017
suffix:colon
multiline_comment|/* fistp m16int */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPU_store_int16
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
r_int
id|__user
op_star
)paren
id|data_address
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t;     (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|020
suffix:colon
multiline_comment|/* fldenv  m14/28byte */
id|fldenv
c_func
(paren
id|addr_modes
comma
(paren
id|u_char
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
multiline_comment|/* Ensure that the values just loaded are not changed by&n;&t; fix-up operations. */
r_return
l_int|1
suffix:semicolon
r_case
l_int|022
suffix:colon
multiline_comment|/* frstor m94/108byte */
id|frstor
c_func
(paren
id|addr_modes
comma
(paren
id|u_char
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
multiline_comment|/* Ensure that the values just loaded are not changed by&n;&t; fix-up operations. */
r_return
l_int|1
suffix:semicolon
r_case
l_int|023
suffix:colon
multiline_comment|/* fbld m80dec */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|loaded_tag
op_assign
id|FPU_load_bcd
c_func
(paren
(paren
id|u_char
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
id|FPU_settag0
c_func
(paren
id|loaded_tag
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|024
suffix:colon
multiline_comment|/* fldcw */
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|FPU_access_ok
c_func
(paren
id|VERIFY_READ
comma
id|data_address
comma
l_int|2
)paren
suffix:semicolon
id|FPU_get_user
c_func
(paren
id|control_word
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
r_if
c_cond
(paren
id|partial_status
op_amp
op_complement
id|control_word
op_amp
id|CW_Exceptions
)paren
id|partial_status
op_or_assign
(paren
id|SW_Summary
op_or
id|SW_Backward
)paren
suffix:semicolon
r_else
id|partial_status
op_and_assign
op_complement
(paren
id|SW_Summary
op_or
id|SW_Backward
)paren
suffix:semicolon
macro_line|#ifdef PECULIAR_486
id|control_word
op_or_assign
l_int|0x40
suffix:semicolon
multiline_comment|/* An 80486 appears to always set this bit */
macro_line|#endif /* PECULIAR_486 */
r_return
l_int|1
suffix:semicolon
r_case
l_int|025
suffix:colon
multiline_comment|/* fld m80real */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|loaded_tag
op_assign
id|FPU_load_extended
c_func
(paren
(paren
r_int
r_float
id|__user
op_star
)paren
id|data_address
comma
l_int|0
)paren
suffix:semicolon
id|FPU_settag0
c_func
(paren
id|loaded_tag
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|027
suffix:colon
multiline_comment|/* fild m64int */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
id|loaded_tag
op_assign
id|FPU_load_int64
c_func
(paren
(paren
r_int
r_int
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
id|FPU_settag0
c_func
(paren
id|loaded_tag
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|030
suffix:colon
multiline_comment|/* fstenv  m14/28byte */
id|fstenv
c_func
(paren
id|addr_modes
comma
(paren
id|u_char
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
l_int|032
suffix:colon
multiline_comment|/* fsave */
id|fsave
c_func
(paren
id|addr_modes
comma
(paren
id|u_char
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
l_int|033
suffix:colon
multiline_comment|/* fbstp m80dec */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPU_store_bcd
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
id|u_char
id|__user
op_star
)paren
id|data_address
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t;     (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|034
suffix:colon
multiline_comment|/* fstcw m16int */
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|FPU_access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|data_address
comma
l_int|2
)paren
suffix:semicolon
id|FPU_put_user
c_func
(paren
id|control_word
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
l_int|035
suffix:colon
multiline_comment|/* fstp m80real */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPU_store_extended
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
r_int
r_float
id|__user
op_star
)paren
id|data_address
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t;     (see the 80486 manual p16-28) */
r_break
suffix:semicolon
r_case
l_int|036
suffix:colon
multiline_comment|/* fstsw m2byte */
id|RE_ENTRANT_CHECK_OFF
suffix:semicolon
id|FPU_access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|data_address
comma
l_int|2
)paren
suffix:semicolon
id|FPU_put_user
c_func
(paren
id|status_word
c_func
(paren
)paren
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|data_address
)paren
suffix:semicolon
id|RE_ENTRANT_CHECK_ON
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
l_int|037
suffix:colon
multiline_comment|/* fistp m64int */
id|clear_C1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FPU_store_int64
c_func
(paren
id|st0_ptr
comma
id|st0_tag
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|data_address
)paren
)paren
id|pop_0
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* pop only if the number was actually stored&n;&t;&t;     (see the 80486 manual p16-28) */
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
