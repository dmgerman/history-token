multiline_comment|/******************************************************************************&n; *&n; * Name: acutils.h -- prototypes for the common (subsystem-wide) procedures&n; *       $Revision: 146 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _ACUTILS_H
DECL|macro|_ACUTILS_H
mdefine_line|#define _ACUTILS_H
r_typedef
DECL|typedef|ACPI_PKG_CALLBACK
id|acpi_status
(paren
op_star
id|ACPI_PKG_CALLBACK
)paren
(paren
id|u8
id|object_type
comma
id|acpi_operand_object
op_star
id|source_object
comma
id|acpi_generic_state
op_star
id|state
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_walk_package_tree
(paren
id|acpi_operand_object
op_star
id|source_object
comma
r_void
op_star
id|target_object
comma
id|ACPI_PKG_CALLBACK
id|walk_callback
comma
r_void
op_star
id|context
)paren
suffix:semicolon
DECL|struct|acpi_pkg_info
r_typedef
r_struct
id|acpi_pkg_info
(brace
DECL|member|free_space
id|u8
op_star
id|free_space
suffix:semicolon
DECL|member|length
id|ACPI_SIZE
id|length
suffix:semicolon
DECL|member|object_space
id|u32
id|object_space
suffix:semicolon
DECL|member|num_packages
id|u32
id|num_packages
suffix:semicolon
DECL|typedef|acpi_pkg_info
)brace
id|acpi_pkg_info
suffix:semicolon
DECL|macro|REF_INCREMENT
mdefine_line|#define REF_INCREMENT       (u16) 0
DECL|macro|REF_DECREMENT
mdefine_line|#define REF_DECREMENT       (u16) 1
DECL|macro|REF_FORCE_DELETE
mdefine_line|#define REF_FORCE_DELETE    (u16) 2
multiline_comment|/* Acpi_ut_dump_buffer */
DECL|macro|DB_BYTE_DISPLAY
mdefine_line|#define DB_BYTE_DISPLAY     1
DECL|macro|DB_WORD_DISPLAY
mdefine_line|#define DB_WORD_DISPLAY     2
DECL|macro|DB_DWORD_DISPLAY
mdefine_line|#define DB_DWORD_DISPLAY    4
DECL|macro|DB_QWORD_DISPLAY
mdefine_line|#define DB_QWORD_DISPLAY    8
multiline_comment|/* Global initialization interfaces */
r_void
id|acpi_ut_init_globals
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ut_terminate
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_init - miscellaneous initialization and shutdown&n; */
id|acpi_status
id|acpi_ut_hardware_initialize
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ut_subsystem_shutdown
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_validate_fadt
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_global - Global data structures and procedures&n; */
macro_line|#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)
id|NATIVE_CHAR
op_star
id|acpi_ut_get_mutex_name
(paren
id|u32
id|mutex_id
)paren
suffix:semicolon
macro_line|#endif
id|NATIVE_CHAR
op_star
id|acpi_ut_get_type_name
(paren
id|acpi_object_type
id|type
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ut_get_object_type_name
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ut_get_region_name
(paren
id|u8
id|space_id
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ut_get_event_name
(paren
id|u32
id|event_id
)paren
suffix:semicolon
r_char
id|acpi_ut_hex_to_ascii_char
(paren
id|acpi_integer
id|integer
comma
id|u32
id|position
)paren
suffix:semicolon
id|u8
id|acpi_ut_valid_object_type
(paren
id|acpi_object_type
id|type
)paren
suffix:semicolon
id|acpi_owner_id
id|acpi_ut_allocate_owner_id
(paren
id|u32
id|id_type
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_clib - Local implementations of C library functions&n; */
macro_line|#ifndef ACPI_USE_SYSTEM_CLIBRARY
id|ACPI_SIZE
id|acpi_ut_strlen
(paren
r_const
id|NATIVE_CHAR
op_star
id|string
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ut_strcpy
(paren
id|NATIVE_CHAR
op_star
id|dst_string
comma
r_const
id|NATIVE_CHAR
op_star
id|src_string
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ut_strncpy
(paren
id|NATIVE_CHAR
op_star
id|dst_string
comma
r_const
id|NATIVE_CHAR
op_star
id|src_string
comma
id|ACPI_SIZE
id|count
)paren
suffix:semicolon
r_int
id|acpi_ut_strncmp
(paren
r_const
id|NATIVE_CHAR
op_star
id|string1
comma
r_const
id|NATIVE_CHAR
op_star
id|string2
comma
id|ACPI_SIZE
id|count
)paren
suffix:semicolon
r_int
id|acpi_ut_strcmp
(paren
r_const
id|NATIVE_CHAR
op_star
id|string1
comma
r_const
id|NATIVE_CHAR
op_star
id|string2
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ut_strcat
(paren
id|NATIVE_CHAR
op_star
id|dst_string
comma
r_const
id|NATIVE_CHAR
op_star
id|src_string
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ut_strncat
(paren
id|NATIVE_CHAR
op_star
id|dst_string
comma
r_const
id|NATIVE_CHAR
op_star
id|src_string
comma
id|ACPI_SIZE
id|count
)paren
suffix:semicolon
id|u32
id|acpi_ut_strtoul
(paren
r_const
id|NATIVE_CHAR
op_star
id|string
comma
id|NATIVE_CHAR
op_star
op_star
id|terminator
comma
id|u32
id|base
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ut_strstr
(paren
id|NATIVE_CHAR
op_star
id|string1
comma
id|NATIVE_CHAR
op_star
id|string2
)paren
suffix:semicolon
r_void
op_star
id|acpi_ut_memcpy
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
id|ACPI_SIZE
id|count
)paren
suffix:semicolon
r_void
op_star
id|acpi_ut_memset
(paren
r_void
op_star
id|dest
comma
id|NATIVE_UINT
id|value
comma
id|ACPI_SIZE
id|count
)paren
suffix:semicolon
r_int
id|acpi_ut_to_upper
(paren
r_int
id|c
)paren
suffix:semicolon
r_int
id|acpi_ut_to_lower
(paren
r_int
id|c
)paren
suffix:semicolon
r_extern
r_const
id|u8
id|_acpi_ctype
(braket
)braket
suffix:semicolon
DECL|macro|_ACPI_XA
mdefine_line|#define _ACPI_XA     0x00    /* extra alphabetic - not supported */
DECL|macro|_ACPI_XS
mdefine_line|#define _ACPI_XS     0x40    /* extra space */
DECL|macro|_ACPI_BB
mdefine_line|#define _ACPI_BB     0x00    /* BEL, BS, etc. - not supported */
DECL|macro|_ACPI_CN
mdefine_line|#define _ACPI_CN     0x20    /* CR, FF, HT, NL, VT */
DECL|macro|_ACPI_DI
mdefine_line|#define _ACPI_DI     0x04    /* &squot;0&squot;-&squot;9&squot; */
DECL|macro|_ACPI_LO
mdefine_line|#define _ACPI_LO     0x02    /* &squot;a&squot;-&squot;z&squot; */
DECL|macro|_ACPI_PU
mdefine_line|#define _ACPI_PU     0x10    /* punctuation */
DECL|macro|_ACPI_SP
mdefine_line|#define _ACPI_SP     0x08    /* space */
DECL|macro|_ACPI_UP
mdefine_line|#define _ACPI_UP     0x01    /* &squot;A&squot;-&squot;Z&squot; */
DECL|macro|_ACPI_XD
mdefine_line|#define _ACPI_XD     0x80    /* &squot;0&squot;-&squot;9&squot;, &squot;A&squot;-&squot;F&squot;, &squot;a&squot;-&squot;f&squot; */
DECL|macro|ACPI_IS_DIGIT
mdefine_line|#define ACPI_IS_DIGIT(c)  (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_DI))
DECL|macro|ACPI_IS_SPACE
mdefine_line|#define ACPI_IS_SPACE(c)  (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_SP))
DECL|macro|ACPI_IS_XDIGIT
mdefine_line|#define ACPI_IS_XDIGIT(c) (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_XD))
DECL|macro|ACPI_IS_UPPER
mdefine_line|#define ACPI_IS_UPPER(c)  (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_UP))
DECL|macro|ACPI_IS_LOWER
mdefine_line|#define ACPI_IS_LOWER(c)  (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_LO))
DECL|macro|ACPI_IS_PRINT
mdefine_line|#define ACPI_IS_PRINT(c)  (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_LO | _ACPI_UP | _ACPI_DI | _ACPI_SP | _ACPI_PU))
DECL|macro|ACPI_IS_ALPHA
mdefine_line|#define ACPI_IS_ALPHA(c)  (_acpi_ctype[(unsigned char)(c)] &amp; (_ACPI_LO | _ACPI_UP))
DECL|macro|ACPI_IS_ASCII
mdefine_line|#define ACPI_IS_ASCII(c)  ((c) &lt; 0x80)
macro_line|#endif /* ACPI_USE_SYSTEM_CLIBRARY */
multiline_comment|/*&n; * Ut_copy - Object construction and conversion interfaces&n; */
id|acpi_status
id|acpi_ut_build_simple_object
c_func
(paren
id|acpi_operand_object
op_star
id|obj
comma
id|acpi_object
op_star
id|user_obj
comma
id|u8
op_star
id|data_space
comma
id|u32
op_star
id|buffer_space_used
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_build_package_object
(paren
id|acpi_operand_object
op_star
id|obj
comma
id|u8
op_star
id|buffer
comma
id|u32
op_star
id|space_used
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_copy_ielement_to_eelement
(paren
id|u8
id|object_type
comma
id|acpi_operand_object
op_star
id|source_object
comma
id|acpi_generic_state
op_star
id|state
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_copy_ielement_to_ielement
(paren
id|u8
id|object_type
comma
id|acpi_operand_object
op_star
id|source_object
comma
id|acpi_generic_state
op_star
id|state
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_copy_iobject_to_eobject
(paren
id|acpi_operand_object
op_star
id|obj
comma
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_copy_esimple_to_isimple
c_func
(paren
id|acpi_object
op_star
id|user_obj
comma
id|acpi_operand_object
op_star
op_star
id|return_obj
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_copy_eobject_to_iobject
(paren
id|acpi_object
op_star
id|obj
comma
id|acpi_operand_object
op_star
op_star
id|internal_obj
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_copy_isimple_to_isimple
(paren
id|acpi_operand_object
op_star
id|source_obj
comma
id|acpi_operand_object
op_star
id|dest_obj
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_copy_ipackage_to_ipackage
(paren
id|acpi_operand_object
op_star
id|source_obj
comma
id|acpi_operand_object
op_star
id|dest_obj
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_copy_simple_object
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
id|dest_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_copy_iobject_to_iobject
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
op_star
id|dest_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_create - Object creation&n; */
id|acpi_status
id|acpi_ut_update_object_reference
(paren
id|acpi_operand_object
op_star
id|object
comma
id|u16
id|action
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_debug - Debug interfaces&n; */
r_void
id|acpi_ut_init_stack_ptr_trace
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ut_track_stack_ptr
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ut_trace
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
)paren
suffix:semicolon
r_void
id|acpi_ut_trace_ptr
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
r_void
op_star
id|pointer
)paren
suffix:semicolon
r_void
id|acpi_ut_trace_u32
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
id|u32
id|integer
)paren
suffix:semicolon
r_void
id|acpi_ut_trace_str
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
id|NATIVE_CHAR
op_star
id|string
)paren
suffix:semicolon
r_void
id|acpi_ut_exit
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
)paren
suffix:semicolon
r_void
id|acpi_ut_status_exit
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
id|acpi_status
id|status
)paren
suffix:semicolon
r_void
id|acpi_ut_value_exit
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
id|acpi_integer
id|value
)paren
suffix:semicolon
r_void
id|acpi_ut_ptr_exit
(paren
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
id|u8
op_star
id|ptr
)paren
suffix:semicolon
r_void
id|acpi_ut_report_info
(paren
id|NATIVE_CHAR
op_star
id|module_name
comma
id|u32
id|line_number
comma
id|u32
id|component_id
)paren
suffix:semicolon
r_void
id|acpi_ut_report_error
(paren
id|NATIVE_CHAR
op_star
id|module_name
comma
id|u32
id|line_number
comma
id|u32
id|component_id
)paren
suffix:semicolon
r_void
id|acpi_ut_report_warning
(paren
id|NATIVE_CHAR
op_star
id|module_name
comma
id|u32
id|line_number
comma
id|u32
id|component_id
)paren
suffix:semicolon
r_void
id|acpi_ut_dump_buffer
(paren
id|u8
op_star
id|buffer
comma
id|u32
id|count
comma
id|u32
id|display
comma
id|u32
id|component_id
)paren
suffix:semicolon
r_void
id|ACPI_INTERNAL_VAR_XFACE
id|acpi_ut_debug_print
(paren
id|u32
id|requested_debug_level
comma
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
r_char
op_star
id|format
comma
dot
dot
dot
)paren
id|ACPI_PRINTF_LIKE_FUNC
suffix:semicolon
r_void
id|ACPI_INTERNAL_VAR_XFACE
id|acpi_ut_debug_print_raw
(paren
id|u32
id|requested_debug_level
comma
id|u32
id|line_number
comma
id|acpi_debug_print_info
op_star
id|dbg_info
comma
r_char
op_star
id|format
comma
dot
dot
dot
)paren
id|ACPI_PRINTF_LIKE_FUNC
suffix:semicolon
multiline_comment|/*&n; * Ut_delete - Object deletion&n; */
r_void
id|acpi_ut_delete_internal_obj
(paren
id|acpi_operand_object
op_star
id|object
)paren
suffix:semicolon
r_void
id|acpi_ut_delete_internal_package_object
(paren
id|acpi_operand_object
op_star
id|object
)paren
suffix:semicolon
r_void
id|acpi_ut_delete_internal_simple_object
(paren
id|acpi_operand_object
op_star
id|object
)paren
suffix:semicolon
r_void
id|acpi_ut_delete_internal_object_list
(paren
id|acpi_operand_object
op_star
op_star
id|obj_list
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_eval - object evaluation&n; */
multiline_comment|/* Method name strings */
DECL|macro|METHOD_NAME__HID
mdefine_line|#define METHOD_NAME__HID        &quot;_HID&quot;
DECL|macro|METHOD_NAME__CID
mdefine_line|#define METHOD_NAME__CID        &quot;_CID&quot;
DECL|macro|METHOD_NAME__UID
mdefine_line|#define METHOD_NAME__UID        &quot;_UID&quot;
DECL|macro|METHOD_NAME__ADR
mdefine_line|#define METHOD_NAME__ADR        &quot;_ADR&quot;
DECL|macro|METHOD_NAME__STA
mdefine_line|#define METHOD_NAME__STA        &quot;_STA&quot;
DECL|macro|METHOD_NAME__REG
mdefine_line|#define METHOD_NAME__REG        &quot;_REG&quot;
DECL|macro|METHOD_NAME__SEG
mdefine_line|#define METHOD_NAME__SEG        &quot;_SEG&quot;
DECL|macro|METHOD_NAME__BBN
mdefine_line|#define METHOD_NAME__BBN        &quot;_BBN&quot;
DECL|macro|METHOD_NAME__PRT
mdefine_line|#define METHOD_NAME__PRT        &quot;_PRT&quot;
id|acpi_status
id|acpi_ut_evaluate_numeric_object
(paren
id|NATIVE_CHAR
op_star
id|object_name
comma
id|acpi_namespace_node
op_star
id|device_node
comma
id|acpi_integer
op_star
id|address
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_execute_HID
(paren
id|acpi_namespace_node
op_star
id|device_node
comma
id|acpi_device_id
op_star
id|hid
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_execute_CID
(paren
id|acpi_namespace_node
op_star
id|device_node
comma
id|acpi_device_id
op_star
id|cid
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_execute_STA
(paren
id|acpi_namespace_node
op_star
id|device_node
comma
id|u32
op_star
id|status_flags
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_execute_UID
(paren
id|acpi_namespace_node
op_star
id|device_node
comma
id|acpi_device_id
op_star
id|uid
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_mutex - mutual exclusion interfaces&n; */
id|acpi_status
id|acpi_ut_mutex_initialize
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ut_mutex_terminate
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_create_mutex
(paren
id|ACPI_MUTEX_HANDLE
id|mutex_id
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_delete_mutex
(paren
id|ACPI_MUTEX_HANDLE
id|mutex_id
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MUTEX_HANDLE
id|mutex_id
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_release_mutex
(paren
id|ACPI_MUTEX_HANDLE
id|mutex_id
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_object - internal object create/delete/cache routines&n; */
id|acpi_operand_object
op_star
id|acpi_ut_create_internal_object_dbg
(paren
id|NATIVE_CHAR
op_star
id|module_name
comma
id|u32
id|line_number
comma
id|u32
id|component_id
comma
id|acpi_object_type
id|type
)paren
suffix:semicolon
r_void
op_star
id|acpi_ut_allocate_object_desc_dbg
(paren
id|NATIVE_CHAR
op_star
id|module_name
comma
id|u32
id|line_number
comma
id|u32
id|component_id
)paren
suffix:semicolon
DECL|macro|acpi_ut_create_internal_object
mdefine_line|#define acpi_ut_create_internal_object(t) acpi_ut_create_internal_object_dbg (_THIS_MODULE,__LINE__,_COMPONENT,t)
DECL|macro|acpi_ut_allocate_object_desc
mdefine_line|#define acpi_ut_allocate_object_desc()  acpi_ut_allocate_object_desc_dbg (_THIS_MODULE,__LINE__,_COMPONENT)
r_void
id|acpi_ut_delete_object_desc
(paren
id|acpi_operand_object
op_star
id|object
)paren
suffix:semicolon
id|u8
id|acpi_ut_valid_internal_object
(paren
r_void
op_star
id|object
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_ref_cnt - Object reference count management&n; */
r_void
id|acpi_ut_add_reference
(paren
id|acpi_operand_object
op_star
id|object
)paren
suffix:semicolon
r_void
id|acpi_ut_remove_reference
(paren
id|acpi_operand_object
op_star
id|object
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_size - Object size routines&n; */
id|acpi_status
id|acpi_ut_get_simple_object_size
(paren
id|acpi_operand_object
op_star
id|obj
comma
id|ACPI_SIZE
op_star
id|obj_length
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_get_package_object_size
(paren
id|acpi_operand_object
op_star
id|obj
comma
id|ACPI_SIZE
op_star
id|obj_length
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_get_object_size
c_func
(paren
id|acpi_operand_object
op_star
id|obj
comma
id|ACPI_SIZE
op_star
id|obj_length
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_get_element_length
(paren
id|u8
id|object_type
comma
id|acpi_operand_object
op_star
id|source_object
comma
id|acpi_generic_state
op_star
id|state
comma
r_void
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/*&n; * Ut_state - Generic state creation/cache routines&n; */
r_void
id|acpi_ut_push_generic_state
(paren
id|acpi_generic_state
op_star
op_star
id|list_head
comma
id|acpi_generic_state
op_star
id|state
)paren
suffix:semicolon
id|acpi_generic_state
op_star
id|acpi_ut_pop_generic_state
(paren
id|acpi_generic_state
op_star
op_star
id|list_head
)paren
suffix:semicolon
id|acpi_generic_state
op_star
id|acpi_ut_create_generic_state
(paren
r_void
)paren
suffix:semicolon
id|ACPI_THREAD_STATE
op_star
id|acpi_ut_create_thread_state
(paren
r_void
)paren
suffix:semicolon
id|acpi_generic_state
op_star
id|acpi_ut_create_update_state
(paren
id|acpi_operand_object
op_star
id|object
comma
id|u16
id|action
)paren
suffix:semicolon
id|acpi_generic_state
op_star
id|acpi_ut_create_pkg_state
(paren
r_void
op_star
id|internal_object
comma
r_void
op_star
id|external_object
comma
id|u16
id|index
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_create_update_state_and_push
(paren
id|acpi_operand_object
op_star
id|object
comma
id|u16
id|action
comma
id|acpi_generic_state
op_star
op_star
id|state_list
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_create_pkg_state_and_push
(paren
r_void
op_star
id|internal_object
comma
r_void
op_star
id|external_object
comma
id|u16
id|index
comma
id|acpi_generic_state
op_star
op_star
id|state_list
)paren
suffix:semicolon
id|acpi_generic_state
op_star
id|acpi_ut_create_control_state
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ut_delete_generic_state
(paren
id|acpi_generic_state
op_star
id|state
)paren
suffix:semicolon
r_void
id|acpi_ut_delete_generic_state_cache
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ut_delete_object_cache
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * utmisc&n; */
id|acpi_status
id|acpi_ut_divide
(paren
id|acpi_integer
op_star
id|in_dividend
comma
id|acpi_integer
op_star
id|in_divisor
comma
id|acpi_integer
op_star
id|out_quotient
comma
id|acpi_integer
op_star
id|out_remainder
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_short_divide
(paren
id|acpi_integer
op_star
id|in_dividend
comma
id|u32
id|divisor
comma
id|acpi_integer
op_star
id|out_quotient
comma
id|u32
op_star
id|out_remainder
)paren
suffix:semicolon
id|u8
id|acpi_ut_valid_acpi_name
(paren
id|u32
id|name
)paren
suffix:semicolon
id|u8
id|acpi_ut_valid_acpi_character
(paren
id|NATIVE_CHAR
id|character
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_strtoul64
(paren
id|NATIVE_CHAR
op_star
id|string
comma
id|u32
id|base
comma
id|acpi_integer
op_star
id|ret_integer
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ut_strupr
(paren
id|NATIVE_CHAR
op_star
id|src_string
)paren
suffix:semicolon
id|u8
op_star
id|acpi_ut_get_resource_end_tag
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
id|u8
id|acpi_ut_generate_checksum
(paren
id|u8
op_star
id|buffer
comma
id|u32
id|length
)paren
suffix:semicolon
id|u32
id|acpi_ut_dword_byte_swap
(paren
id|u32
id|value
)paren
suffix:semicolon
r_void
id|acpi_ut_set_integer_width
(paren
id|u8
id|revision
)paren
suffix:semicolon
macro_line|#ifdef ACPI_DEBUG_OUTPUT
r_void
id|acpi_ut_display_init_pathname
(paren
id|acpi_handle
id|obj_handle
comma
r_char
op_star
id|path
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Utalloc - memory allocation and object caching&n; */
r_void
op_star
id|acpi_ut_acquire_from_cache
(paren
id|u32
id|list_id
)paren
suffix:semicolon
r_void
id|acpi_ut_release_to_cache
(paren
id|u32
id|list_id
comma
r_void
op_star
id|object
)paren
suffix:semicolon
r_void
id|acpi_ut_delete_generic_cache
(paren
id|u32
id|list_id
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_validate_buffer
(paren
id|acpi_buffer
op_star
id|buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_initialize_buffer
(paren
id|acpi_buffer
op_star
id|buffer
comma
id|ACPI_SIZE
id|required_length
)paren
suffix:semicolon
multiline_comment|/* Memory allocation functions */
r_void
op_star
id|acpi_ut_allocate
(paren
id|ACPI_SIZE
id|size
comma
id|u32
id|component
comma
id|NATIVE_CHAR
op_star
id|module
comma
id|u32
id|line
)paren
suffix:semicolon
r_void
op_star
id|acpi_ut_callocate
(paren
id|ACPI_SIZE
id|size
comma
id|u32
id|component
comma
id|NATIVE_CHAR
op_star
id|module
comma
id|u32
id|line
)paren
suffix:semicolon
macro_line|#ifdef ACPI_DBG_TRACK_ALLOCATIONS
r_void
op_star
id|acpi_ut_allocate_and_track
(paren
id|ACPI_SIZE
id|size
comma
id|u32
id|component
comma
id|NATIVE_CHAR
op_star
id|module
comma
id|u32
id|line
)paren
suffix:semicolon
r_void
op_star
id|acpi_ut_callocate_and_track
(paren
id|ACPI_SIZE
id|size
comma
id|u32
id|component
comma
id|NATIVE_CHAR
op_star
id|module
comma
id|u32
id|line
)paren
suffix:semicolon
r_void
id|acpi_ut_free_and_track
(paren
r_void
op_star
id|address
comma
id|u32
id|component
comma
id|NATIVE_CHAR
op_star
id|module
comma
id|u32
id|line
)paren
suffix:semicolon
id|acpi_debug_mem_block
op_star
id|acpi_ut_find_allocation
(paren
id|u32
id|list_id
comma
r_void
op_star
id|allocation
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_track_allocation
(paren
id|u32
id|list_id
comma
id|acpi_debug_mem_block
op_star
id|address
comma
id|ACPI_SIZE
id|size
comma
id|u8
id|alloc_type
comma
id|u32
id|component
comma
id|NATIVE_CHAR
op_star
id|module
comma
id|u32
id|line
)paren
suffix:semicolon
id|acpi_status
id|acpi_ut_remove_allocation
(paren
id|u32
id|list_id
comma
id|acpi_debug_mem_block
op_star
id|address
comma
id|u32
id|component
comma
id|NATIVE_CHAR
op_star
id|module
comma
id|u32
id|line
)paren
suffix:semicolon
r_void
id|acpi_ut_dump_allocation_info
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ut_dump_allocations
(paren
id|u32
id|component
comma
id|NATIVE_CHAR
op_star
id|module
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _ACUTILS_H */
eof
