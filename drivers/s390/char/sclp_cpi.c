multiline_comment|/*&n; * Author: Martin Peschke &lt;mpeschke@de.ibm.com&gt;&n; * Copyright (C) 2001 IBM Entwicklung GmbH, IBM Corporation&n; *&n; * SCLP Control-Program Identification.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;sclp.h&quot;
macro_line|#include &quot;sclp_rw.h&quot;
DECL|macro|CPI_LENGTH_SYSTEM_TYPE
mdefine_line|#define CPI_LENGTH_SYSTEM_TYPE&t;8
DECL|macro|CPI_LENGTH_SYSTEM_NAME
mdefine_line|#define CPI_LENGTH_SYSTEM_NAME&t;8
DECL|macro|CPI_LENGTH_SYSPLEX_NAME
mdefine_line|#define CPI_LENGTH_SYSPLEX_NAME&t;8
DECL|struct|cpi_evbuf
r_struct
id|cpi_evbuf
(brace
DECL|member|header
r_struct
id|evbuf_header
id|header
suffix:semicolon
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
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|cpi_sccb
r_struct
id|cpi_sccb
(brace
DECL|member|header
r_struct
id|sccb_header
id|header
suffix:semicolon
DECL|member|cpi_evbuf
r_struct
id|cpi_evbuf
id|cpi_evbuf
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Event type structure for write message and write priority message */
DECL|variable|sclp_cpi_event
r_static
r_struct
id|sclp_register
id|sclp_cpi_event
op_assign
(brace
dot
id|send_mask
op_assign
id|EvTyp_CtlProgIdent_Mask
)brace
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Martin Peschke, IBM Deutschland Entwicklung GmbH &quot;
l_string|&quot;&lt;mpeschke@de.ibm.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;identify this operating system instance to the S/390 &quot;
l_string|&quot;or zSeries hardware&quot;
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
c_func
(paren
id|system_name
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
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
c_func
(paren
id|sysplex_name
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|sysplex_name
comma
l_string|&quot;if applicable - max. 8 characters&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* use default value for this field (as well as for system level) */
DECL|variable|system_type
r_static
r_char
op_star
id|system_type
op_assign
l_string|&quot;LINUX&quot;
suffix:semicolon
r_static
r_int
DECL|function|cpi_check_parms
id|cpi_check_parms
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* reject if no system type specified */
r_if
c_cond
(paren
op_logical_neg
id|system_type
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpi: bug: no system type specified&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* reject if system type larger than 8 characters */
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|system_type
)paren
OG
id|CPI_LENGTH_SYSTEM_NAME
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpi: bug: system type has length of %li characters - &quot;
l_string|&quot;only %i characters supported&bslash;n&quot;
comma
id|strlen
c_func
(paren
id|system_type
)paren
comma
id|CPI_LENGTH_SYSTEM_TYPE
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* reject if no system name specified */
r_if
c_cond
(paren
op_logical_neg
id|system_name
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpi: no system name specified&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* reject if system name larger than 8 characters */
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|system_name
)paren
OG
id|CPI_LENGTH_SYSTEM_NAME
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpi: system name has length of %li characters - &quot;
l_string|&quot;only %i characters supported&bslash;n&quot;
comma
id|strlen
c_func
(paren
id|system_name
)paren
comma
id|CPI_LENGTH_SYSTEM_NAME
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* reject if specified sysplex name larger than 8 characters */
r_if
c_cond
(paren
id|sysplex_name
op_logical_and
id|strlen
c_func
(paren
id|sysplex_name
)paren
OG
id|CPI_LENGTH_SYSPLEX_NAME
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpi: sysplex name has length of %li characters&quot;
l_string|&quot; - only %i characters supported&bslash;n&quot;
comma
id|strlen
c_func
(paren
id|sysplex_name
)paren
comma
id|CPI_LENGTH_SYSPLEX_NAME
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|cpi_callback
id|cpi_callback
c_func
(paren
r_struct
id|sclp_req
op_star
id|req
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|semaphore
op_star
id|sem
suffix:semicolon
id|sem
op_assign
(paren
r_struct
id|semaphore
op_star
)paren
id|data
suffix:semicolon
id|up
c_func
(paren
id|sem
)paren
suffix:semicolon
)brace
r_static
r_struct
id|sclp_req
op_star
DECL|function|cpi_prepare_req
id|cpi_prepare_req
c_func
(paren
r_void
)paren
(brace
r_struct
id|sclp_req
op_star
id|req
suffix:semicolon
r_struct
id|cpi_sccb
op_star
id|sccb
suffix:semicolon
r_struct
id|cpi_evbuf
op_star
id|evb
suffix:semicolon
id|req
op_assign
(paren
r_struct
id|sclp_req
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sclp_req
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
op_eq
l_int|NULL
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|sccb
op_assign
(paren
r_struct
id|cpi_sccb
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sccb
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|req
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sccb
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cpi_sccb
)paren
)paren
suffix:semicolon
multiline_comment|/* setup SCCB for Control-Program Identification */
id|sccb-&gt;header.length
op_assign
r_sizeof
(paren
r_struct
id|cpi_sccb
)paren
suffix:semicolon
id|sccb-&gt;cpi_evbuf.header.length
op_assign
r_sizeof
(paren
r_struct
id|cpi_evbuf
)paren
suffix:semicolon
id|sccb-&gt;cpi_evbuf.header.type
op_assign
l_int|0x0B
suffix:semicolon
id|evb
op_assign
op_amp
id|sccb-&gt;cpi_evbuf
suffix:semicolon
multiline_comment|/* set system type */
id|memset
c_func
(paren
id|evb-&gt;system_type
comma
l_char|&squot; &squot;
comma
id|CPI_LENGTH_SYSTEM_TYPE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|evb-&gt;system_type
comma
id|system_type
comma
id|strlen
c_func
(paren
id|system_type
)paren
)paren
suffix:semicolon
id|sclp_ascebc_str
c_func
(paren
id|evb-&gt;system_type
comma
id|CPI_LENGTH_SYSTEM_TYPE
)paren
suffix:semicolon
id|EBC_TOUPPER
c_func
(paren
id|evb-&gt;system_type
comma
id|CPI_LENGTH_SYSTEM_TYPE
)paren
suffix:semicolon
multiline_comment|/* set system name */
id|memset
c_func
(paren
id|evb-&gt;system_name
comma
l_char|&squot; &squot;
comma
id|CPI_LENGTH_SYSTEM_NAME
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|evb-&gt;system_name
comma
id|system_name
comma
id|strlen
c_func
(paren
id|system_name
)paren
)paren
suffix:semicolon
id|sclp_ascebc_str
c_func
(paren
id|evb-&gt;system_name
comma
id|CPI_LENGTH_SYSTEM_NAME
)paren
suffix:semicolon
id|EBC_TOUPPER
c_func
(paren
id|evb-&gt;system_name
comma
id|CPI_LENGTH_SYSTEM_NAME
)paren
suffix:semicolon
multiline_comment|/* set sytem level */
id|evb-&gt;system_level
op_assign
id|LINUX_VERSION_CODE
suffix:semicolon
multiline_comment|/* set sysplex name */
r_if
c_cond
(paren
id|sysplex_name
)paren
(brace
id|memset
c_func
(paren
id|evb-&gt;sysplex_name
comma
l_char|&squot; &squot;
comma
id|CPI_LENGTH_SYSPLEX_NAME
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|evb-&gt;sysplex_name
comma
id|sysplex_name
comma
id|strlen
c_func
(paren
id|sysplex_name
)paren
)paren
suffix:semicolon
id|sclp_ascebc_str
c_func
(paren
id|evb-&gt;sysplex_name
comma
id|CPI_LENGTH_SYSPLEX_NAME
)paren
suffix:semicolon
id|EBC_TOUPPER
c_func
(paren
id|evb-&gt;sysplex_name
comma
id|CPI_LENGTH_SYSPLEX_NAME
)paren
suffix:semicolon
)brace
multiline_comment|/* prepare request data structure presented to SCLP driver */
id|req-&gt;command
op_assign
id|SCLP_CMDW_WRITEDATA
suffix:semicolon
id|req-&gt;sccb
op_assign
id|sccb
suffix:semicolon
id|req-&gt;status
op_assign
id|SCLP_REQ_FILLED
suffix:semicolon
id|req-&gt;callback
op_assign
id|cpi_callback
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
r_static
r_void
DECL|function|cpi_free_req
id|cpi_free_req
c_func
(paren
r_struct
id|sclp_req
op_star
id|req
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|req-&gt;sccb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|cpi_module_init
id|cpi_module_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|semaphore
id|sem
suffix:semicolon
r_struct
id|sclp_req
op_star
id|req
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|cpi_check_parms
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|rc
op_assign
id|sclp_register
c_func
(paren
op_amp
id|sclp_cpi_event
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
multiline_comment|/* could not register sclp event. Die. */
id|printk
c_func
(paren
l_string|&quot;cpi: could not register to hardware console.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sclp_cpi_event.sclp_send_mask
op_amp
id|EvTyp_CtlProgIdent_Mask
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpi: no control program identification support&bslash;n&quot;
)paren
suffix:semicolon
id|sclp_unregister
c_func
(paren
op_amp
id|sclp_cpi_event
)paren
suffix:semicolon
r_return
op_minus
id|ENOTSUPP
suffix:semicolon
)brace
id|req
op_assign
id|cpi_prepare_req
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|req
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpi: couldn&squot;t allocate request&bslash;n&quot;
)paren
suffix:semicolon
id|sclp_unregister
c_func
(paren
op_amp
id|sclp_cpi_event
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
multiline_comment|/* Prepare semaphore */
id|sema_init
c_func
(paren
op_amp
id|sem
comma
l_int|0
)paren
suffix:semicolon
id|req-&gt;callback_data
op_assign
op_amp
id|sem
suffix:semicolon
multiline_comment|/* Add request to sclp queue */
id|sclp_add_request
c_func
(paren
id|req
)paren
suffix:semicolon
multiline_comment|/* make &quot;insmod&quot; sleep until callback arrives */
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
id|rc
op_assign
(paren
(paren
r_struct
id|cpi_sccb
op_star
)paren
id|req-&gt;sccb
)paren
op_member_access_from_pointer
id|header.response_code
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0x0020
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpi: failed with response code 0x%x&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ECOMM
suffix:semicolon
)brace
r_else
id|rc
op_assign
l_int|0
suffix:semicolon
id|cpi_free_req
c_func
(paren
id|req
)paren
suffix:semicolon
id|sclp_unregister
c_func
(paren
op_amp
id|sclp_cpi_event
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|cpi_module_exit
r_static
r_void
id|__exit
id|cpi_module_exit
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* declare driver module init/cleanup functions */
DECL|variable|cpi_module_init
id|module_init
c_func
(paren
id|cpi_module_init
)paren
suffix:semicolon
DECL|variable|cpi_module_exit
id|module_exit
c_func
(paren
id|cpi_module_exit
)paren
suffix:semicolon
eof
