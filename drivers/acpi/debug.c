multiline_comment|/*&n; * debug.c - ACPI debug interface to userspace.&n; */
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;acpi/acpi_drivers.h&gt;
macro_line|#include &lt;acpi/acglobal.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_SYSTEM_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;debug&quot;
)paren
DECL|macro|ACPI_SYSTEM_FILE_DEBUG_LAYER
mdefine_line|#define ACPI_SYSTEM_FILE_DEBUG_LAYER&t;&quot;debug_layer&quot;
DECL|macro|ACPI_SYSTEM_FILE_DEBUG_LEVEL
mdefine_line|#define ACPI_SYSTEM_FILE_DEBUG_LEVEL&t;&quot;debug_level&quot;
macro_line|#ifdef MODULE_PARAM_PREFIX
DECL|macro|MODULE_PARAM_PREFIX
macro_line|#undef MODULE_PARAM_PREFIX
macro_line|#endif
DECL|macro|MODULE_PARAM_PREFIX
mdefine_line|#define MODULE_PARAM_PREFIX
id|module_param
c_func
(paren
id|acpi_dbg_layer
comma
id|uint
comma
l_int|0400
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|acpi_dbg_level
comma
id|uint
comma
l_int|0400
)paren
suffix:semicolon
DECL|struct|acpi_dlayer
r_struct
id|acpi_dlayer
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_dlevel
r_struct
id|acpi_dlevel
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ACPI_DEBUG_INIT
mdefine_line|#define ACPI_DEBUG_INIT(v)&t;{ .name = #v, .value = v }
DECL|variable|acpi_debug_layers
r_static
r_const
r_struct
id|acpi_dlayer
id|acpi_debug_layers
(braket
)braket
op_assign
(brace
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_UTILITIES
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_HARDWARE
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_EVENTS
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_TABLES
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_NAMESPACE
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_PARSER
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_DISPATCHER
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_EXECUTER
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_RESOURCES
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_CA_DEBUGGER
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_OS_SERVICES
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_CA_DISASSEMBLER
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_COMPILER
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_TOOLS
)paren
comma
)brace
suffix:semicolon
DECL|variable|acpi_debug_levels
r_static
r_const
r_struct
id|acpi_dlevel
id|acpi_debug_levels
(braket
)braket
op_assign
(brace
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_ERROR
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_WARN
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_INIT
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_DEBUG_OBJECT
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_INFO
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_INIT_NAMES
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_PARSE
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_LOAD
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_DISPATCH
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_EXEC
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_NAMES
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_OPREGION
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_BFIELD
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_TABLES
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_VALUES
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_OBJECTS
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_RESOURCES
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_USER_REQUESTS
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_PACKAGE
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_ALLOCATIONS
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_FUNCTIONS
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_OPTIMIZATIONS
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_MUTEX
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_THREADS
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_IO
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_INTERRUPTS
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_AML_DISASSEMBLE
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_VERBOSE_INFO
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_FULL_TABLES
)paren
comma
id|ACPI_DEBUG_INIT
c_func
(paren
id|ACPI_LV_EVENTS
)paren
comma
)brace
suffix:semicolon
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
r_int
r_int
id|i
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
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%-25s&bslash;tHex        SET&bslash;n&quot;
comma
l_string|&quot;Description&quot;
)paren
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|acpi_debug_layers
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%-25s&bslash;t0x%08lX [%c]&bslash;n&quot;
comma
id|acpi_debug_layers
(braket
id|i
)braket
dot
id|name
comma
id|acpi_debug_layers
(braket
id|i
)braket
dot
id|value
comma
(paren
id|acpi_dbg_layer
op_amp
id|acpi_debug_layers
(braket
id|i
)braket
dot
id|value
)paren
ques
c_cond
l_char|&squot;*&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%-25s&bslash;t0x%08X [%c]&bslash;n&quot;
comma
l_string|&quot;ACPI_ALL_DRIVERS&quot;
comma
id|ACPI_ALL_DRIVERS
comma
(paren
id|acpi_dbg_layer
op_amp
id|ACPI_ALL_DRIVERS
)paren
op_eq
id|ACPI_ALL_DRIVERS
ques
c_cond
l_char|&squot;*&squot;
suffix:colon
(paren
id|acpi_dbg_layer
op_amp
id|ACPI_ALL_DRIVERS
)paren
op_eq
l_int|0
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;-&squot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;--&bslash;ndebug_layer = 0x%08X (* = enabled, - = partial)&bslash;n&quot;
comma
id|acpi_dbg_layer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|acpi_debug_levels
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%-25s&bslash;t0x%08lX [%c]&bslash;n&quot;
comma
id|acpi_debug_levels
(braket
id|i
)braket
dot
id|name
comma
id|acpi_debug_levels
(braket
id|i
)braket
dot
id|value
comma
(paren
id|acpi_dbg_level
op_amp
id|acpi_debug_levels
(braket
id|i
)braket
dot
id|value
)paren
ques
c_cond
l_char|&squot;*&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;--&bslash;ndebug_level = 0x%08X (* = enabled)&bslash;n&quot;
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
id|__user
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
