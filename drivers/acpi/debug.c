multiline_comment|/*&n; * debug.c - ACPI debug interface to userspace.&n; */
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;acpi_drivers.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_SYSTEM_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;debug&quot;
)paren
r_static
r_int
DECL|function|acpi_system_read_debug
id|acpi_system_read_debug
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|p
op_assign
id|page
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ne
l_int|0
)paren
r_goto
id|end
suffix:semicolon
r_switch
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
)paren
(brace
r_case
l_int|0
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;0x%08x&bslash;n&quot;
comma
id|acpi_dbg_layer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;0x%08x&bslash;n&quot;
comma
id|acpi_dbg_level
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Invalid debug option&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|end
suffix:colon
id|size
op_assign
(paren
id|p
op_minus
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|off
op_plus
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|size
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|count
)paren
id|size
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
id|size
op_assign
l_int|0
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_system_write_debug
id|acpi_system_write_debug
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_char
id|debug_string
(braket
l_int|12
)braket
op_assign
(brace
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_system_write_debug&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
r_sizeof
(paren
id|debug_string
)paren
op_minus
l_int|1
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|debug_string
comma
id|buffer
comma
id|count
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
id|debug_string
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_switch
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
)paren
(brace
r_case
l_int|0
suffix:colon
id|acpi_dbg_layer
op_assign
id|simple_strtoul
c_func
(paren
id|debug_string
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|acpi_dbg_level
op_assign
id|simple_strtoul
c_func
(paren
id|debug_string
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
id|count
)paren
suffix:semicolon
)brace
DECL|function|acpi_debug_init
r_static
r_int
id|__init
id|acpi_debug_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_debug_init&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_disabled
)paren
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* &squot;debug_layer&squot; [R/W] */
id|name
op_assign
id|ACPI_SYSTEM_FILE_DEBUG_LAYER
suffix:semicolon
id|entry
op_assign
id|create_proc_read_entry
c_func
(paren
id|name
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|acpi_root_dir
comma
id|acpi_system_read_debug
comma
(paren
r_void
op_star
)paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;write_proc
op_assign
id|acpi_system_write_debug
suffix:semicolon
r_else
r_goto
id|Error
suffix:semicolon
multiline_comment|/* &squot;debug_level&squot; [R/W] */
id|name
op_assign
id|ACPI_SYSTEM_FILE_DEBUG_LEVEL
suffix:semicolon
id|entry
op_assign
id|create_proc_read_entry
c_func
(paren
id|name
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|acpi_root_dir
comma
id|acpi_system_read_debug
comma
(paren
r_void
op_star
)paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;write_proc
op_assign
id|acpi_system_write_debug
suffix:semicolon
r_else
r_goto
id|Error
suffix:semicolon
id|Done
suffix:colon
id|return_VALUE
c_func
(paren
id|error
)paren
suffix:semicolon
id|Error
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unable to create &squot;%s&squot; proc fs entry&bslash;n&quot;
comma
id|name
)paren
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|ACPI_SYSTEM_FILE_DEBUG_LEVEL
comma
id|acpi_root_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|ACPI_SYSTEM_FILE_DEBUG_LAYER
comma
id|acpi_root_dir
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
DECL|variable|acpi_debug_init
id|subsys_initcall
c_func
(paren
id|acpi_debug_init
)paren
suffix:semicolon
eof
