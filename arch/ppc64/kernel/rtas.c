multiline_comment|/*&n; *&n; * Procedures for interfacing to the RTAS on CHRP machines.&n; *&n; * Peter Bergner, IBM&t;March 2001.&n; * Copyright (C) 2001 IBM.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/udbg.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|rtas_firmware_flash_list
r_struct
id|flash_block_list_header
id|rtas_firmware_flash_list
op_assign
(brace
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|rtas
r_struct
id|rtas_t
id|rtas
op_assign
(brace
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
)brace
suffix:semicolon
DECL|variable|rtas
id|EXPORT_SYMBOL
c_func
(paren
id|rtas
)paren
suffix:semicolon
DECL|variable|rtas_err_buf
r_char
id|rtas_err_buf
(braket
id|RTAS_ERROR_LOG_MAX
)braket
suffix:semicolon
DECL|variable|rtas_data_buf_lock
id|spinlock_t
id|rtas_data_buf_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|__page_aligned
r_char
id|rtas_data_buf
(braket
id|RTAS_DATA_BUF_SIZE
)braket
id|__page_aligned
suffix:semicolon
DECL|variable|rtas_rmo_buf
r_int
r_int
id|rtas_rmo_buf
suffix:semicolon
r_void
DECL|function|call_rtas_display_status
id|call_rtas_display_status
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_struct
id|rtas_args
op_star
id|args
op_assign
op_amp
id|rtas.args
suffix:semicolon
r_int
r_int
id|s
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rtas.base
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtas.lock
comma
id|s
)paren
suffix:semicolon
id|args-&gt;token
op_assign
l_int|10
suffix:semicolon
id|args-&gt;nargs
op_assign
l_int|1
suffix:semicolon
id|args-&gt;nret
op_assign
l_int|1
suffix:semicolon
id|args-&gt;rets
op_assign
(paren
id|rtas_arg_t
op_star
)paren
op_amp
(paren
id|args-&gt;args
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|args-&gt;args
(braket
l_int|0
)braket
op_assign
(paren
r_int
)paren
id|c
suffix:semicolon
id|enter_rtas
c_func
(paren
id|__pa
c_func
(paren
id|args
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtas.lock
comma
id|s
)paren
suffix:semicolon
)brace
r_void
DECL|function|call_rtas_display_status_delay
id|call_rtas_display_status_delay
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_static
r_int
id|pending_newline
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* did last write end with unprinted newline? */
r_static
r_int
id|width
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_while
c_loop
(paren
id|width
op_decrement
OG
l_int|0
)paren
id|call_rtas_display_status
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
id|width
op_assign
l_int|16
suffix:semicolon
id|udelay
c_func
(paren
l_int|500000
)paren
suffix:semicolon
id|pending_newline
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|pending_newline
)paren
(brace
id|call_rtas_display_status
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|call_rtas_display_status
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
id|pending_newline
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|width
op_decrement
)paren
(brace
id|call_rtas_display_status
c_func
(paren
id|c
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10000
)paren
suffix:semicolon
)brace
)brace
)brace
r_int
DECL|function|rtas_token
id|rtas_token
c_func
(paren
r_const
r_char
op_star
id|service
)paren
(brace
r_int
op_star
id|tokp
suffix:semicolon
r_if
c_cond
(paren
id|rtas.dev
op_eq
l_int|NULL
)paren
(brace
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;tNo rtas device in device-tree...&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|RTAS_UNKNOWN_SERVICE
suffix:semicolon
)brace
id|tokp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|rtas.dev
comma
id|service
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|tokp
ques
c_cond
op_star
id|tokp
suffix:colon
id|RTAS_UNKNOWN_SERVICE
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the firmware-specified size of the error log buffer&n; *  for all rtas calls that require an error buffer argument.&n; *  This includes &squot;check-exception&squot; and &squot;rtas-last-error&squot;.&n; */
DECL|function|rtas_get_error_log_max
r_int
id|rtas_get_error_log_max
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|rtas_error_log_max
suffix:semicolon
r_if
c_cond
(paren
id|rtas_error_log_max
)paren
r_return
id|rtas_error_log_max
suffix:semicolon
id|rtas_error_log_max
op_assign
id|rtas_token
(paren
l_string|&quot;rtas-error-log-max&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rtas_error_log_max
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
op_logical_or
(paren
id|rtas_error_log_max
OG
id|RTAS_ERROR_LOG_MAX
)paren
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;RTAS: bad log buffer size %d&bslash;n&quot;
comma
id|rtas_error_log_max
)paren
suffix:semicolon
id|rtas_error_log_max
op_assign
id|RTAS_ERROR_LOG_MAX
suffix:semicolon
)brace
r_return
id|rtas_error_log_max
suffix:semicolon
)brace
multiline_comment|/** Return a copy of the detailed error text associated with the&n; *  most recent failed call to rtas.  Because the error text&n; *  might go stale if there are any other intervening rtas calls,&n; *  this routine must be called atomically with whatever produced&n; *  the error (i.e. with rtas.lock still held from the previous call).&n; */
r_static
r_int
DECL|function|__fetch_rtas_last_error
id|__fetch_rtas_last_error
c_func
(paren
r_void
)paren
(brace
r_struct
id|rtas_args
id|err_args
comma
id|save_args
suffix:semicolon
id|u32
id|bufsz
suffix:semicolon
id|bufsz
op_assign
id|rtas_get_error_log_max
c_func
(paren
)paren
suffix:semicolon
id|err_args.token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;rtas-last-error&quot;
)paren
suffix:semicolon
id|err_args.nargs
op_assign
l_int|2
suffix:semicolon
id|err_args.nret
op_assign
l_int|1
suffix:semicolon
id|err_args.args
(braket
l_int|0
)braket
op_assign
(paren
id|rtas_arg_t
)paren
id|__pa
c_func
(paren
id|rtas_err_buf
)paren
suffix:semicolon
id|err_args.args
(braket
l_int|1
)braket
op_assign
id|bufsz
suffix:semicolon
id|err_args.args
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|save_args
op_assign
id|rtas.args
suffix:semicolon
id|rtas.args
op_assign
id|err_args
suffix:semicolon
id|enter_rtas
c_func
(paren
id|__pa
c_func
(paren
op_amp
id|rtas.args
)paren
)paren
suffix:semicolon
id|err_args
op_assign
id|rtas.args
suffix:semicolon
id|rtas.args
op_assign
id|save_args
suffix:semicolon
r_return
id|err_args.args
(braket
l_int|2
)braket
suffix:semicolon
)brace
DECL|function|rtas_call
r_int
id|rtas_call
c_func
(paren
r_int
id|token
comma
r_int
id|nargs
comma
r_int
id|nret
comma
r_int
op_star
id|outputs
comma
dot
dot
dot
)paren
(brace
id|va_list
id|list
suffix:semicolon
r_int
id|i
comma
id|logit
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|s
suffix:semicolon
r_struct
id|rtas_args
op_star
id|rtas_args
suffix:semicolon
r_char
op_star
id|buff_copy
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;Entering rtas_call&bslash;n&quot;
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;ttoken    = 0x%x&bslash;n&quot;
comma
id|token
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;tnargs    = %d&bslash;n&quot;
comma
id|nargs
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;tnret     = %d&bslash;n&quot;
comma
id|nret
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;t&amp;outputs = 0x%lx&bslash;n&quot;
comma
id|outputs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|token
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Gotta do something different here, use global lock for now... */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtas.lock
comma
id|s
)paren
suffix:semicolon
id|rtas_args
op_assign
op_amp
id|rtas.args
suffix:semicolon
id|rtas_args-&gt;token
op_assign
id|token
suffix:semicolon
id|rtas_args-&gt;nargs
op_assign
id|nargs
suffix:semicolon
id|rtas_args-&gt;nret
op_assign
id|nret
suffix:semicolon
id|rtas_args-&gt;rets
op_assign
(paren
id|rtas_arg_t
op_star
)paren
op_amp
(paren
id|rtas_args-&gt;args
(braket
id|nargs
)braket
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|outputs
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nargs
suffix:semicolon
op_increment
id|i
)paren
(brace
id|rtas_args-&gt;args
(braket
id|i
)braket
op_assign
id|va_arg
c_func
(paren
id|list
comma
id|rtas_arg_t
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;tnarg[%d] = 0x%x&bslash;n&quot;
comma
id|i
comma
id|rtas_args-&gt;args
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nret
suffix:semicolon
op_increment
id|i
)paren
id|rtas_args-&gt;rets
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;tentering rtas with 0x%lx&bslash;n&quot;
comma
id|__pa
c_func
(paren
id|rtas_args
)paren
)paren
suffix:semicolon
id|enter_rtas
c_func
(paren
id|__pa
c_func
(paren
id|rtas_args
)paren
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_RTAS
comma
l_string|&quot;&bslash;treturned from rtas ...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* A -1 return code indicates that the last command couldn&squot;t&n;&t;   be completed due to a hardware error. */
r_if
c_cond
(paren
id|rtas_args-&gt;rets
(braket
l_int|0
)braket
op_eq
op_minus
l_int|1
)paren
id|logit
op_assign
(paren
id|__fetch_rtas_last_error
c_func
(paren
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|ifppcdebug
c_func
(paren
id|PPCDBG_RTAS
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nret
suffix:semicolon
id|i
op_increment
)paren
(brace
id|udbg_printf
c_func
(paren
l_string|&quot;&bslash;tnret[%d] = 0x%lx&bslash;n&quot;
comma
id|i
comma
(paren
id|ulong
)paren
id|rtas_args-&gt;rets
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|nret
OG
l_int|1
op_logical_and
id|outputs
op_ne
l_int|NULL
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nret
op_minus
l_int|1
suffix:semicolon
op_increment
id|i
)paren
id|outputs
(braket
id|i
)braket
op_assign
id|rtas_args-&gt;rets
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|ret
op_assign
(paren
id|nret
OG
l_int|0
)paren
ques
c_cond
id|rtas_args-&gt;rets
(braket
l_int|0
)braket
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* Log the error in the unlikely case that there was one. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|logit
)paren
)paren
(brace
id|buff_copy
op_assign
id|rtas_err_buf
suffix:semicolon
r_if
c_cond
(paren
id|mem_init_done
)paren
(brace
id|buff_copy
op_assign
id|kmalloc
c_func
(paren
id|RTAS_ERROR_LOG_MAX
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buff_copy
)paren
id|memcpy
c_func
(paren
id|buff_copy
comma
id|rtas_err_buf
comma
id|RTAS_ERROR_LOG_MAX
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Gotta do something different here, use global lock for now... */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtas.lock
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buff_copy
)paren
(brace
id|log_error
c_func
(paren
id|buff_copy
comma
id|ERR_TYPE_RTAS_LOG
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem_init_done
)paren
id|kfree
c_func
(paren
id|buff_copy
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Given an RTAS status code of 990n compute the hinted delay of 10^n&n; * (last digit) milliseconds.  For now we bound at n=5 (100 sec).&n; */
r_int
r_int
DECL|function|rtas_extended_busy_delay_time
id|rtas_extended_busy_delay_time
c_func
(paren
r_int
id|status
)paren
(brace
r_int
id|order
op_assign
id|status
op_minus
l_int|9900
suffix:semicolon
r_int
r_int
id|ms
suffix:semicolon
r_if
c_cond
(paren
id|order
OL
l_int|0
)paren
id|order
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* RTC depends on this for -2 clock busy */
r_else
r_if
c_cond
(paren
id|order
OG
l_int|5
)paren
id|order
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* bound */
multiline_comment|/* Use microseconds for reasonable accuracy */
r_for
c_loop
(paren
id|ms
op_assign
l_int|1
suffix:semicolon
id|order
OG
l_int|0
suffix:semicolon
id|order
op_decrement
)paren
id|ms
op_mul_assign
l_int|10
suffix:semicolon
r_return
id|ms
suffix:semicolon
)brace
r_int
DECL|function|rtas_get_power_level
id|rtas_get_power_level
c_func
(paren
r_int
id|powerdomain
comma
r_int
op_star
id|level
)paren
(brace
r_int
id|token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;get-power-level&quot;
)paren
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|token
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
r_return
id|RTAS_UNKNOWN_OP
suffix:semicolon
r_while
c_loop
(paren
(paren
id|rc
op_assign
id|rtas_call
c_func
(paren
id|token
comma
l_int|1
comma
l_int|2
comma
id|level
comma
id|powerdomain
)paren
)paren
op_eq
id|RTAS_BUSY
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_int
DECL|function|rtas_set_power_level
id|rtas_set_power_level
c_func
(paren
r_int
id|powerdomain
comma
r_int
id|level
comma
r_int
op_star
id|setlevel
)paren
(brace
r_int
id|token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;set-power-level&quot;
)paren
suffix:semicolon
r_int
r_int
id|wait_time
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|token
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
r_return
id|RTAS_UNKNOWN_OP
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|rc
op_assign
id|rtas_call
c_func
(paren
id|token
comma
l_int|2
comma
l_int|2
comma
id|setlevel
comma
id|powerdomain
comma
id|level
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|RTAS_BUSY
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rtas_is_extended_busy
c_func
(paren
id|rc
)paren
)paren
(brace
id|wait_time
op_assign
id|rtas_extended_busy_delay_time
c_func
(paren
id|rc
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|wait_time
op_star
l_int|1000
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
r_int
DECL|function|rtas_get_sensor
id|rtas_get_sensor
c_func
(paren
r_int
id|sensor
comma
r_int
id|index
comma
r_int
op_star
id|state
)paren
(brace
r_int
id|token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;get-sensor-state&quot;
)paren
suffix:semicolon
r_int
r_int
id|wait_time
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|token
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
r_return
id|RTAS_UNKNOWN_OP
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|rc
op_assign
id|rtas_call
c_func
(paren
id|token
comma
l_int|2
comma
l_int|2
comma
id|state
comma
id|sensor
comma
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|RTAS_BUSY
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rtas_is_extended_busy
c_func
(paren
id|rc
)paren
)paren
(brace
id|wait_time
op_assign
id|rtas_extended_busy_delay_time
c_func
(paren
id|rc
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|wait_time
op_star
l_int|1000
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
r_int
DECL|function|rtas_set_indicator
id|rtas_set_indicator
c_func
(paren
r_int
id|indicator
comma
r_int
id|index
comma
r_int
id|new_value
)paren
(brace
r_int
id|token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;set-indicator&quot;
)paren
suffix:semicolon
r_int
r_int
id|wait_time
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|token
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
r_return
id|RTAS_UNKNOWN_OP
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|rc
op_assign
id|rtas_call
c_func
(paren
id|token
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
id|indicator
comma
id|index
comma
id|new_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|RTAS_BUSY
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rtas_is_extended_busy
c_func
(paren
id|rc
)paren
)paren
(brace
id|wait_time
op_assign
id|rtas_extended_busy_delay_time
c_func
(paren
id|rc
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|wait_time
op_star
l_int|1000
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|macro|FLASH_BLOCK_LIST_VERSION
mdefine_line|#define FLASH_BLOCK_LIST_VERSION (1UL)
r_static
r_void
DECL|function|rtas_flash_firmware
id|rtas_flash_firmware
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|image_size
suffix:semicolon
r_struct
id|flash_block_list
op_star
id|f
comma
op_star
id|next
comma
op_star
id|flist
suffix:semicolon
r_int
r_int
id|rtas_block_list
suffix:semicolon
r_int
id|i
comma
id|status
comma
id|update_token
suffix:semicolon
id|update_token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,update-flash-64-and-reboot&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|update_token
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: ibm,update-flash-64-and-reboot is not available -- not a service partition?&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: firmware will not be flashed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* NOTE: the &quot;first&quot; block list is a global var with no data&n;&t; * blocks in the kernel data segment.  We do this because&n;&t; * we want to ensure this block_list addr is under 4GB.&n;&t; */
id|rtas_firmware_flash_list.num_blocks
op_assign
l_int|0
suffix:semicolon
id|flist
op_assign
(paren
r_struct
id|flash_block_list
op_star
)paren
op_amp
id|rtas_firmware_flash_list
suffix:semicolon
id|rtas_block_list
op_assign
id|virt_to_abs
c_func
(paren
id|flist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtas_block_list
op_ge
l_int|4UL
op_star
l_int|1024
op_star
l_int|1024
op_star
l_int|1024
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: kernel bug...flash list header addr above 4GB&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: preparing saved firmware image for flash&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Update the block_list in place. */
id|image_size
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|flist
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|next
)paren
(brace
multiline_comment|/* Translate data addrs to absolute */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|f-&gt;num_blocks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|f-&gt;blocks
(braket
id|i
)braket
dot
id|data
op_assign
(paren
r_char
op_star
)paren
id|virt_to_abs
c_func
(paren
id|f-&gt;blocks
(braket
id|i
)braket
dot
id|data
)paren
suffix:semicolon
id|image_size
op_add_assign
id|f-&gt;blocks
(braket
id|i
)braket
dot
id|length
suffix:semicolon
)brace
id|next
op_assign
id|f-&gt;next
suffix:semicolon
multiline_comment|/* Don&squot;t translate NULL pointer for last entry */
r_if
c_cond
(paren
id|f-&gt;next
)paren
id|f-&gt;next
op_assign
(paren
r_struct
id|flash_block_list
op_star
)paren
id|virt_to_abs
c_func
(paren
id|f-&gt;next
)paren
suffix:semicolon
r_else
id|f-&gt;next
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* make num_blocks into the version/length field */
id|f-&gt;num_blocks
op_assign
(paren
id|FLASH_BLOCK_LIST_VERSION
op_lshift
l_int|56
)paren
op_or
(paren
(paren
id|f-&gt;num_blocks
op_plus
l_int|1
)paren
op_star
l_int|16
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: flash image is %ld bytes&bslash;n&quot;
comma
id|image_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: performing flash and reboot&bslash;n&quot;
)paren
suffix:semicolon
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;Flashing        &bslash;n&quot;
comma
l_int|0x0
)paren
suffix:semicolon
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;Please Wait...  &quot;
comma
l_int|0x0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: this will take several minutes.  Do not power off!&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|rtas_call
c_func
(paren
id|update_token
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
id|rtas_block_list
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
multiline_comment|/* should only get &quot;bad&quot; status */
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: success&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|1
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: hardware error.  Firmware may not be not flashed&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|3
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: image is corrupt or not correct for this platform.  Firmware not flashed&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
l_int|4
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: flash failed when partially complete.  System may not reboot&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: unknown flash return code %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|rtas_flash_bypass_warning
r_void
id|rtas_flash_bypass_warning
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: firmware flash requires a reboot&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;FLASH: the firmware image will NOT be flashed&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_void
DECL|function|rtas_restart
id|rtas_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_if
c_cond
(paren
id|rtas_firmware_flash_list.next
)paren
id|rtas_flash_firmware
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RTAS system-reboot returned %d&bslash;n&quot;
comma
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;system-reboot&quot;
)paren
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_void
DECL|function|rtas_power_off
id|rtas_power_off
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|rtas_firmware_flash_list.next
)paren
id|rtas_flash_bypass_warning
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* allow power on only with power button press */
id|printk
c_func
(paren
l_string|&quot;RTAS power-off returned %d&bslash;n&quot;
comma
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;power-off&quot;
)paren
comma
l_int|2
comma
l_int|1
comma
l_int|NULL
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_void
DECL|function|rtas_halt
id|rtas_halt
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|rtas_firmware_flash_list.next
)paren
id|rtas_flash_bypass_warning
c_func
(paren
)paren
suffix:semicolon
id|rtas_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Must be in the RMO region, so we place it here */
DECL|variable|rtas_os_term_buf
r_static
r_char
id|rtas_os_term_buf
(braket
l_int|2048
)braket
suffix:semicolon
DECL|function|rtas_os_term
r_void
id|rtas_os_term
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|status
suffix:semicolon
id|snprintf
c_func
(paren
id|rtas_os_term_buf
comma
l_int|2048
comma
l_string|&quot;OS panic: %s&quot;
comma
id|str
)paren
suffix:semicolon
r_do
(brace
id|status
op_assign
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;ibm,os-term&quot;
)paren
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
id|__pa
c_func
(paren
id|rtas_os_term_buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|RTAS_BUSY
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;ibm,os-term call failed %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
op_eq
id|RTAS_BUSY
)paren
suffix:semicolon
)brace
DECL|function|ppc_rtas
id|asmlinkage
r_int
id|ppc_rtas
c_func
(paren
r_struct
id|rtas_args
id|__user
op_star
id|uargs
)paren
(brace
r_struct
id|rtas_args
id|args
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_char
op_star
id|buff_copy
suffix:semicolon
r_int
id|nargs
suffix:semicolon
r_int
id|err_rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|args
comma
id|uargs
comma
l_int|3
op_star
r_sizeof
(paren
id|u32
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|nargs
op_assign
id|args.nargs
suffix:semicolon
r_if
c_cond
(paren
id|nargs
OG
id|ARRAY_SIZE
c_func
(paren
id|args.args
)paren
op_logical_or
id|args.nret
OG
id|ARRAY_SIZE
c_func
(paren
id|args.args
)paren
op_logical_or
id|nargs
op_plus
id|args.nret
OG
id|ARRAY_SIZE
c_func
(paren
id|args.args
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Copy in args. */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|args.args
comma
id|uargs-&gt;args
comma
id|nargs
op_star
r_sizeof
(paren
id|rtas_arg_t
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buff_copy
op_assign
id|kmalloc
c_func
(paren
id|RTAS_ERROR_LOG_MAX
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtas.lock
comma
id|flags
)paren
suffix:semicolon
id|rtas.args
op_assign
id|args
suffix:semicolon
id|enter_rtas
c_func
(paren
id|__pa
c_func
(paren
op_amp
id|rtas.args
)paren
)paren
suffix:semicolon
id|args
op_assign
id|rtas.args
suffix:semicolon
id|args.rets
op_assign
op_amp
id|args.args
(braket
id|nargs
)braket
suffix:semicolon
multiline_comment|/* A -1 return code indicates that the last command couldn&squot;t&n;&t;   be completed due to a hardware error. */
r_if
c_cond
(paren
id|args.rets
(braket
l_int|0
)braket
op_eq
op_minus
l_int|1
)paren
(brace
id|err_rc
op_assign
id|__fetch_rtas_last_error
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err_rc
op_eq
l_int|0
)paren
op_logical_and
id|buff_copy
)paren
(brace
id|memcpy
c_func
(paren
id|buff_copy
comma
id|rtas_err_buf
comma
id|RTAS_ERROR_LOG_MAX
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtas.lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buff_copy
)paren
(brace
r_if
c_cond
(paren
(paren
id|args.rets
(braket
l_int|0
)braket
op_eq
op_minus
l_int|1
)paren
op_logical_and
(paren
id|err_rc
op_eq
l_int|0
)paren
)paren
(brace
id|log_error
c_func
(paren
id|buff_copy
comma
id|ERR_TYPE_RTAS_LOG
comma
l_int|0
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|buff_copy
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy out args. */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|uargs-&gt;args
op_plus
id|nargs
comma
id|args.args
op_plus
id|nargs
comma
id|args.nret
op_star
r_sizeof
(paren
id|rtas_arg_t
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This version can&squot;t take the spinlock, because it never returns */
DECL|variable|rtas_stop_self_args
r_struct
id|rtas_args
id|rtas_stop_self_args
op_assign
(brace
multiline_comment|/* The token is initialized for real in setup_system() */
dot
id|token
op_assign
id|RTAS_UNKNOWN_SERVICE
comma
dot
id|nargs
op_assign
l_int|0
comma
dot
id|nret
op_assign
l_int|1
comma
dot
id|rets
op_assign
op_amp
id|rtas_stop_self_args.args
(braket
l_int|0
)braket
comma
)brace
suffix:semicolon
DECL|function|rtas_stop_self
r_void
id|rtas_stop_self
c_func
(paren
r_void
)paren
(brace
r_struct
id|rtas_args
op_star
id|rtas_args
op_assign
op_amp
id|rtas_stop_self_args
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|rtas_args-&gt;token
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cpu %u (hwid %u) Ready to die...&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|hard_smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|enter_rtas
c_func
(paren
id|__pa
c_func
(paren
id|rtas_args
)paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Alas, I survived.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Call early during boot, before mem init or bootmem, to retreive the RTAS&n; * informations from the device-tree and allocate the RMO buffer for userland&n; * accesses.&n; */
DECL|function|rtas_initialize
r_void
id|__init
id|rtas_initialize
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Get RTAS dev node and fill up our &quot;rtas&quot; structure with infos&n;&t; * about it.&n;&t; */
id|rtas.dev
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;rtas&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtas.dev
)paren
(brace
id|u64
op_star
id|basep
comma
op_star
id|entryp
suffix:semicolon
id|u32
op_star
id|sizep
suffix:semicolon
id|basep
op_assign
(paren
id|u64
op_star
)paren
id|get_property
c_func
(paren
id|of_chosen
comma
l_string|&quot;linux,rtas-base&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|sizep
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|of_chosen
comma
l_string|&quot;linux,rtas-size&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|basep
op_ne
l_int|NULL
op_logical_and
id|sizep
op_ne
l_int|NULL
)paren
(brace
id|rtas.base
op_assign
op_star
id|basep
suffix:semicolon
id|rtas.size
op_assign
op_star
id|sizep
suffix:semicolon
id|entryp
op_assign
(paren
id|u64
op_star
)paren
id|get_property
c_func
(paren
id|of_chosen
comma
l_string|&quot;linux,rtas-entry&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entryp
op_eq
l_int|NULL
)paren
multiline_comment|/* Ugh */
id|rtas.entry
op_assign
id|rtas.base
suffix:semicolon
r_else
id|rtas.entry
op_assign
op_star
id|entryp
suffix:semicolon
)brace
r_else
id|rtas.dev
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* If RTAS was found, allocate the RMO buffer for it and look for&n;&t; * the stop-self token if any&n;&t; */
r_if
c_cond
(paren
id|rtas.dev
)paren
(brace
r_int
r_int
id|rtas_region
op_assign
id|RTAS_INSTANTIATE_MAX
suffix:semicolon
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_eq
id|PLATFORM_PSERIES_LPAR
)paren
id|rtas_region
op_assign
id|min
c_func
(paren
id|lmb.rmo_size
comma
id|RTAS_INSTANTIATE_MAX
)paren
suffix:semicolon
id|rtas_rmo_buf
op_assign
id|lmb_alloc_base
c_func
(paren
id|RTAS_RMOBUF_MAX
comma
id|PAGE_SIZE
comma
id|rtas_region
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HOTPLUG_CPU
id|rtas_stop_self_args.token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;stop-self&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_HOTPLUG_CPU */
)brace
)brace
DECL|variable|rtas_firmware_flash_list
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_firmware_flash_list
)paren
suffix:semicolon
DECL|variable|rtas_token
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_token
)paren
suffix:semicolon
DECL|variable|rtas_call
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_call
)paren
suffix:semicolon
DECL|variable|rtas_data_buf
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_data_buf
)paren
suffix:semicolon
DECL|variable|rtas_data_buf_lock
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_data_buf_lock
)paren
suffix:semicolon
DECL|variable|rtas_extended_busy_delay_time
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_extended_busy_delay_time
)paren
suffix:semicolon
DECL|variable|rtas_get_sensor
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_get_sensor
)paren
suffix:semicolon
DECL|variable|rtas_get_power_level
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_get_power_level
)paren
suffix:semicolon
DECL|variable|rtas_set_power_level
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_set_power_level
)paren
suffix:semicolon
DECL|variable|rtas_set_indicator
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_set_indicator
)paren
suffix:semicolon
DECL|variable|rtas_get_error_log_max
id|EXPORT_SYMBOL
c_func
(paren
id|rtas_get_error_log_max
)paren
suffix:semicolon
eof
