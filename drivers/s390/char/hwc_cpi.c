multiline_comment|/*&n; * Author: Martin Peschke &lt;mpeschke@de.ibm.com&gt;&n; * Copyright (C) 2001 IBM Entwicklung GmbH, IBM Corporation&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &quot;hwc_rw.h&quot;
macro_line|#include &quot;hwc.h&quot;
DECL|macro|CPI_RETRIES
mdefine_line|#define CPI_RETRIES&t;&t;3
DECL|macro|CPI_SLEEP_TICKS
mdefine_line|#define CPI_SLEEP_TICKS&t;&t;50
DECL|macro|CPI_LENGTH_SYSTEM_TYPE
mdefine_line|#define CPI_LENGTH_SYSTEM_TYPE&t;8
DECL|macro|CPI_LENGTH_SYSTEM_NAME
mdefine_line|#define CPI_LENGTH_SYSTEM_NAME&t;8
DECL|macro|CPI_LENGTH_SYSPLEX_NAME
mdefine_line|#define CPI_LENGTH_SYSPLEX_NAME&t;8
r_typedef
r_struct
(brace
id|_EBUF_HEADER
DECL|member|id_format
id|u8
id|id_format
suffix:semicolon
DECL|member|reserved0
id|u8
id|reserved0
suffix:semicolon
DECL|member|system_type
id|u8
id|system_type
(braket
id|CPI_LENGTH_SYSTEM_TYPE
)braket
suffix:semicolon
DECL|member|reserved1
id|u64
id|reserved1
suffix:semicolon
DECL|member|system_name
id|u8
id|system_name
(braket
id|CPI_LENGTH_SYSTEM_NAME
)braket
suffix:semicolon
DECL|member|reserved2
id|u64
id|reserved2
suffix:semicolon
DECL|member|system_level
id|u64
id|system_level
suffix:semicolon
DECL|member|reserved3
id|u64
id|reserved3
suffix:semicolon
DECL|member|sysplex_name
id|u8
id|sysplex_name
(braket
id|CPI_LENGTH_SYSPLEX_NAME
)braket
suffix:semicolon
DECL|member|reserved4
id|u8
id|reserved4
(braket
l_int|16
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|cpi_evbuf_t
id|cpi_evbuf_t
suffix:semicolon
DECL|struct|_cpi_hwcb_t
r_typedef
r_struct
id|_cpi_hwcb_t
(brace
id|_HWCB_HEADER
DECL|member|cpi_evbuf
id|cpi_evbuf_t
id|cpi_evbuf
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|cpi_hwcb_t
id|cpi_hwcb_t
suffix:semicolon
DECL|variable|cpi_hwcb
id|cpi_hwcb_t
op_star
id|cpi_hwcb
suffix:semicolon
r_static
r_int
id|__init
id|cpi_module_init
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__exit
id|cpi_module_exit
(paren
r_void
)paren
suffix:semicolon
DECL|variable|cpi_module_init
id|module_init
(paren
id|cpi_module_init
)paren
suffix:semicolon
DECL|variable|cpi_module_exit
id|module_exit
(paren
id|cpi_module_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Martin Peschke, IBM Deutschland Entwicklung GmbH &quot;
l_string|&quot;&lt;mpeschke@de.ibm.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;identify this operating system instance to the S/390 or zSeries hardware&quot;
)paren
suffix:semicolon
DECL|variable|system_name
r_static
r_char
op_star
id|system_name
op_assign
l_int|NULL
suffix:semicolon
id|MODULE_PARM
(paren
id|system_name
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|system_name
comma
l_string|&quot;e.g. hostname - max. 8 characters&quot;
)paren
suffix:semicolon
DECL|variable|sysplex_name
r_static
r_char
op_star
id|sysplex_name
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef ALLOW_SYSPLEX_NAME
id|MODULE_PARM
(paren
id|sysplex_name
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
(paren
id|sysplex_name
comma
l_string|&quot;if applicable - max. 8 characters&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|system_type
r_static
r_char
op_star
id|system_type
op_assign
l_string|&quot;LINUX&quot;
suffix:semicolon
DECL|variable|cpi_request
id|hwc_request_t
id|cpi_request
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|cpi_callback
id|hwc_callback_t
id|cpi_callback
suffix:semicolon
r_static
id|DECLARE_MUTEX_LOCKED
(paren
id|sem
)paren
suffix:semicolon
r_static
r_int
id|__init
DECL|function|cpi_module_init
id|cpi_module_init
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
id|system_type_length
suffix:semicolon
r_int
id|system_name_length
suffix:semicolon
r_int
id|sysplex_name_length
op_assign
l_int|0
suffix:semicolon
r_int
id|retries
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_HAS_HWC
)paren
(brace
id|printk
(paren
l_string|&quot;cpi: bug: hardware console not present&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|system_type
)paren
(brace
id|printk
(paren
l_string|&quot;cpi: bug: no system type specified&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|system_type_length
op_assign
id|strlen
(paren
id|system_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|system_type_length
OG
id|CPI_LENGTH_SYSTEM_NAME
)paren
(brace
id|printk
(paren
l_string|&quot;cpi: bug: system type has length of %i characters - &quot;
l_string|&quot;only %i characters supported&bslash;n&quot;
comma
id|system_type_length
comma
id|CPI_LENGTH_SYSTEM_TYPE
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|system_name
)paren
(brace
id|printk
(paren
l_string|&quot;cpi: no system name specified&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|system_name_length
op_assign
id|strlen
(paren
id|system_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|system_name_length
OG
id|CPI_LENGTH_SYSTEM_NAME
)paren
(brace
id|printk
(paren
l_string|&quot;cpi: system name has length of %i characters - &quot;
l_string|&quot;only %i characters supported&bslash;n&quot;
comma
id|system_name_length
comma
id|CPI_LENGTH_SYSTEM_NAME
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sysplex_name
)paren
(brace
id|sysplex_name_length
op_assign
id|strlen
(paren
id|sysplex_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sysplex_name_length
OG
id|CPI_LENGTH_SYSPLEX_NAME
)paren
(brace
id|printk
(paren
l_string|&quot;cpi: sysplex name has length of %i characters - &quot;
l_string|&quot;only %i characters supported&bslash;n&quot;
comma
id|sysplex_name_length
comma
id|CPI_LENGTH_SYSPLEX_NAME
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|cpi_hwcb
op_assign
id|kmalloc
(paren
r_sizeof
(paren
id|cpi_hwcb_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpi_hwcb
)paren
(brace
id|printk
(paren
l_string|&quot;cpi: no storage to fulfill request&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memset
(paren
id|cpi_hwcb
comma
l_int|0
comma
r_sizeof
(paren
id|cpi_hwcb_t
)paren
)paren
suffix:semicolon
id|cpi_hwcb-&gt;length
op_assign
r_sizeof
(paren
id|cpi_hwcb_t
)paren
suffix:semicolon
id|cpi_hwcb-&gt;cpi_evbuf.length
op_assign
r_sizeof
(paren
id|cpi_evbuf_t
)paren
suffix:semicolon
id|cpi_hwcb-&gt;cpi_evbuf.type
op_assign
l_int|0x0B
suffix:semicolon
id|memset
(paren
id|cpi_hwcb-&gt;cpi_evbuf.system_type
comma
l_char|&squot; &squot;
comma
id|CPI_LENGTH_SYSTEM_TYPE
)paren
suffix:semicolon
id|memcpy
(paren
id|cpi_hwcb-&gt;cpi_evbuf.system_type
comma
id|system_type
comma
id|system_type_length
)paren
suffix:semicolon
id|HWC_ASCEBC_STR
(paren
id|cpi_hwcb-&gt;cpi_evbuf.system_type
comma
id|CPI_LENGTH_SYSTEM_TYPE
)paren
suffix:semicolon
id|EBC_TOUPPER
(paren
id|cpi_hwcb-&gt;cpi_evbuf.system_type
comma
id|CPI_LENGTH_SYSTEM_TYPE
)paren
suffix:semicolon
id|memset
(paren
id|cpi_hwcb-&gt;cpi_evbuf.system_name
comma
l_char|&squot; &squot;
comma
id|CPI_LENGTH_SYSTEM_NAME
)paren
suffix:semicolon
id|memcpy
(paren
id|cpi_hwcb-&gt;cpi_evbuf.system_name
comma
id|system_name
comma
id|system_name_length
)paren
suffix:semicolon
id|HWC_ASCEBC_STR
(paren
id|cpi_hwcb-&gt;cpi_evbuf.system_name
comma
id|CPI_LENGTH_SYSTEM_NAME
)paren
suffix:semicolon
id|EBC_TOUPPER
(paren
id|cpi_hwcb-&gt;cpi_evbuf.system_name
comma
id|CPI_LENGTH_SYSTEM_NAME
)paren
suffix:semicolon
id|cpi_hwcb-&gt;cpi_evbuf.system_level
op_assign
id|LINUX_VERSION_CODE
suffix:semicolon
r_if
c_cond
(paren
id|sysplex_name
)paren
(brace
id|memset
(paren
id|cpi_hwcb-&gt;cpi_evbuf.sysplex_name
comma
l_char|&squot; &squot;
comma
id|CPI_LENGTH_SYSPLEX_NAME
)paren
suffix:semicolon
id|memcpy
(paren
id|cpi_hwcb-&gt;cpi_evbuf.sysplex_name
comma
id|sysplex_name
comma
id|sysplex_name_length
)paren
suffix:semicolon
id|HWC_ASCEBC_STR
(paren
id|cpi_hwcb-&gt;cpi_evbuf.sysplex_name
comma
id|CPI_LENGTH_SYSPLEX_NAME
)paren
suffix:semicolon
id|EBC_TOUPPER
(paren
id|cpi_hwcb-&gt;cpi_evbuf.sysplex_name
comma
id|CPI_LENGTH_SYSPLEX_NAME
)paren
suffix:semicolon
)brace
id|cpi_request.block
op_assign
id|cpi_hwcb
suffix:semicolon
id|cpi_request.word
op_assign
id|HWC_CMDW_WRITEDATA
suffix:semicolon
id|cpi_request.callback
op_assign
id|cpi_callback
suffix:semicolon
r_for
c_loop
(paren
id|retries
op_assign
id|CPI_RETRIES
suffix:semicolon
id|retries
suffix:semicolon
id|retries
op_decrement
)paren
(brace
id|retval
op_assign
id|hwc_send
(paren
op_amp
id|cpi_request
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|set_current_state
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
(paren
id|CPI_SLEEP_TICKS
)paren
suffix:semicolon
)brace
r_else
(brace
id|down
(paren
op_amp
id|sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cpi_hwcb-&gt;response_code
)paren
(brace
r_case
l_int|0x0020
suffix:colon
id|printk
(paren
l_string|&quot;cpi: succeeded&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
l_string|&quot;cpi: failed with response code 0x%x&bslash;n&quot;
comma
id|cpi_hwcb-&gt;response_code
)paren
suffix:semicolon
)brace
r_goto
id|free
suffix:semicolon
)brace
)brace
id|printk
(paren
l_string|&quot;cpi: failed (%i)&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
id|free
suffix:colon
id|kfree
(paren
id|cpi_hwcb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|cpi_module_exit
id|cpi_module_exit
(paren
r_void
)paren
(brace
id|printk
(paren
l_string|&quot;cpi: exit&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_void
DECL|function|cpi_callback
id|cpi_callback
(paren
id|hwc_request_t
op_star
id|req
)paren
(brace
id|up
(paren
op_amp
id|sem
)paren
suffix:semicolon
)brace
eof
