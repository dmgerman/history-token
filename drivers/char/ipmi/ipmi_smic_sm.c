multiline_comment|/*&n; * ipmi_smic_sm.c&n; *&n; * The state-machine driver for an IPMI SMIC driver&n; *&n; * It started as a copy of Corey Minyard&squot;s driver for the KSC interface&n; * and the kernel patch &quot;mmcdev-patch-245&quot; by HP&n; *&n; * modified by:&t;Hannes Schulz &lt;schulz@schwaar.com&gt;&n; *&t;&t;ipmi@schwaar.com&n; *&n; *&n; * Corey Minyard&squot;s driver for the KSC interface has the following&n; * copyright notice:&n; *   Copyright 2002 MontaVista Software Inc.&n; *&n; * the kernel patch &quot;mmcdev-patch-245&quot; by HP has the following&n; * copyright notice:&n; * (c) Copyright 2001 Grant Grundler (c) Copyright&n; * 2001 Hewlett-Packard Company&n; *&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.  */
macro_line|#include &lt;linux/kernel.h&gt; /* For printk. */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ipmi_msgdefs.h&gt;&t;&t;/* for completion codes */
macro_line|#include &quot;ipmi_si_sm.h&quot;
DECL|macro|IPMI_SMIC_VERSION
mdefine_line|#define IPMI_SMIC_VERSION &quot;v32&quot;
multiline_comment|/* smic_debug is a bit-field&n; *&t;SMIC_DEBUG_ENABLE -&t;turned on for now&n; *&t;SMIC_DEBUG_MSG -&t;commands and their responses&n; *&t;SMIC_DEBUG_STATES -&t;state machine&n;*/
DECL|macro|SMIC_DEBUG_STATES
mdefine_line|#define SMIC_DEBUG_STATES&t;4
DECL|macro|SMIC_DEBUG_MSG
mdefine_line|#define SMIC_DEBUG_MSG&t;&t;2
DECL|macro|SMIC_DEBUG_ENABLE
mdefine_line|#define&t;SMIC_DEBUG_ENABLE&t;1
DECL|variable|smic_debug
r_static
r_int
id|smic_debug
op_assign
l_int|1
suffix:semicolon
DECL|enum|smic_states
r_enum
id|smic_states
(brace
DECL|enumerator|SMIC_IDLE
id|SMIC_IDLE
comma
DECL|enumerator|SMIC_START_OP
id|SMIC_START_OP
comma
DECL|enumerator|SMIC_OP_OK
id|SMIC_OP_OK
comma
DECL|enumerator|SMIC_WRITE_START
id|SMIC_WRITE_START
comma
DECL|enumerator|SMIC_WRITE_NEXT
id|SMIC_WRITE_NEXT
comma
DECL|enumerator|SMIC_WRITE_END
id|SMIC_WRITE_END
comma
DECL|enumerator|SMIC_WRITE2READ
id|SMIC_WRITE2READ
comma
DECL|enumerator|SMIC_READ_START
id|SMIC_READ_START
comma
DECL|enumerator|SMIC_READ_NEXT
id|SMIC_READ_NEXT
comma
DECL|enumerator|SMIC_READ_END
id|SMIC_READ_END
comma
DECL|enumerator|SMIC_HOSED
id|SMIC_HOSED
)brace
suffix:semicolon
DECL|macro|MAX_SMIC_READ_SIZE
mdefine_line|#define MAX_SMIC_READ_SIZE 80
DECL|macro|MAX_SMIC_WRITE_SIZE
mdefine_line|#define MAX_SMIC_WRITE_SIZE 80
DECL|macro|SMIC_MAX_ERROR_RETRIES
mdefine_line|#define SMIC_MAX_ERROR_RETRIES 3
multiline_comment|/* Timeouts in microseconds. */
DECL|macro|SMIC_RETRY_TIMEOUT
mdefine_line|#define SMIC_RETRY_TIMEOUT 100000
multiline_comment|/* SMIC Flags Register Bits */
DECL|macro|SMIC_RX_DATA_READY
mdefine_line|#define SMIC_RX_DATA_READY&t;0x80
DECL|macro|SMIC_TX_DATA_READY
mdefine_line|#define SMIC_TX_DATA_READY&t;0x40
DECL|macro|SMIC_SMI
mdefine_line|#define SMIC_SMI&t;&t;0x10
DECL|macro|SMIC_EVM_DATA_AVAIL
mdefine_line|#define SMIC_EVM_DATA_AVAIL&t;0x08
DECL|macro|SMIC_SMS_DATA_AVAIL
mdefine_line|#define SMIC_SMS_DATA_AVAIL&t;0x04
DECL|macro|SMIC_FLAG_BSY
mdefine_line|#define SMIC_FLAG_BSY&t;&t;0x01
multiline_comment|/* SMIC Error Codes */
DECL|macro|EC_NO_ERROR
mdefine_line|#define&t;EC_NO_ERROR&t;&t;0x00
DECL|macro|EC_ABORTED
mdefine_line|#define&t;EC_ABORTED&t;&t;0x01
DECL|macro|EC_ILLEGAL_CONTROL
mdefine_line|#define&t;EC_ILLEGAL_CONTROL&t;0x02
DECL|macro|EC_NO_RESPONSE
mdefine_line|#define&t;EC_NO_RESPONSE&t;&t;0x03
DECL|macro|EC_ILLEGAL_COMMAND
mdefine_line|#define&t;EC_ILLEGAL_COMMAND&t;0x04
DECL|macro|EC_BUFFER_FULL
mdefine_line|#define&t;EC_BUFFER_FULL&t;&t;0x05
DECL|struct|si_sm_data
r_struct
id|si_sm_data
(brace
DECL|member|state
r_enum
id|smic_states
id|state
suffix:semicolon
DECL|member|io
r_struct
id|si_sm_io
op_star
id|io
suffix:semicolon
DECL|member|write_data
r_int
r_char
id|write_data
(braket
id|MAX_SMIC_WRITE_SIZE
)braket
suffix:semicolon
DECL|member|write_pos
r_int
id|write_pos
suffix:semicolon
DECL|member|write_count
r_int
id|write_count
suffix:semicolon
DECL|member|orig_write_count
r_int
id|orig_write_count
suffix:semicolon
DECL|member|read_data
r_int
r_char
id|read_data
(braket
id|MAX_SMIC_READ_SIZE
)braket
suffix:semicolon
DECL|member|read_pos
r_int
id|read_pos
suffix:semicolon
DECL|member|truncated
r_int
id|truncated
suffix:semicolon
DECL|member|error_retries
r_int
r_int
id|error_retries
suffix:semicolon
DECL|member|smic_timeout
r_int
id|smic_timeout
suffix:semicolon
)brace
suffix:semicolon
DECL|function|init_smic_data
r_static
r_int
r_int
id|init_smic_data
(paren
r_struct
id|si_sm_data
op_star
id|smic
comma
r_struct
id|si_sm_io
op_star
id|io
)paren
(brace
id|smic-&gt;state
op_assign
id|SMIC_IDLE
suffix:semicolon
id|smic-&gt;io
op_assign
id|io
suffix:semicolon
id|smic-&gt;write_pos
op_assign
l_int|0
suffix:semicolon
id|smic-&gt;write_count
op_assign
l_int|0
suffix:semicolon
id|smic-&gt;orig_write_count
op_assign
l_int|0
suffix:semicolon
id|smic-&gt;read_pos
op_assign
l_int|0
suffix:semicolon
id|smic-&gt;error_retries
op_assign
l_int|0
suffix:semicolon
id|smic-&gt;truncated
op_assign
l_int|0
suffix:semicolon
id|smic-&gt;smic_timeout
op_assign
id|SMIC_RETRY_TIMEOUT
suffix:semicolon
multiline_comment|/* We use 3 bytes of I/O. */
r_return
l_int|3
suffix:semicolon
)brace
DECL|function|start_smic_transaction
r_static
r_int
id|start_smic_transaction
c_func
(paren
r_struct
id|si_sm_data
op_star
id|smic
comma
r_int
r_char
op_star
id|data
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
OL
l_int|2
)paren
op_logical_or
(paren
id|size
OG
id|MAX_SMIC_WRITE_SIZE
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|smic-&gt;state
op_ne
id|SMIC_IDLE
)paren
op_logical_and
(paren
id|smic-&gt;state
op_ne
id|SMIC_HOSED
)paren
)paren
(brace
r_return
op_minus
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|smic_debug
op_amp
id|SMIC_DEBUG_MSG
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;start_smic_transaction -&quot;
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
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
(paren
l_string|&quot; %02x&quot;
comma
(paren
r_int
r_char
)paren
(paren
id|data
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|smic-&gt;error_retries
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|smic-&gt;write_data
comma
id|data
comma
id|size
)paren
suffix:semicolon
id|smic-&gt;write_count
op_assign
id|size
suffix:semicolon
id|smic-&gt;orig_write_count
op_assign
id|size
suffix:semicolon
id|smic-&gt;write_pos
op_assign
l_int|0
suffix:semicolon
id|smic-&gt;read_pos
op_assign
l_int|0
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_START_OP
suffix:semicolon
id|smic-&gt;smic_timeout
op_assign
id|SMIC_RETRY_TIMEOUT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smic_get_result
r_static
r_int
id|smic_get_result
c_func
(paren
r_struct
id|si_sm_data
op_star
id|smic
comma
r_int
r_char
op_star
id|data
comma
r_int
r_int
id|length
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|smic_debug
op_amp
id|SMIC_DEBUG_MSG
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;smic_get result -&quot;
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
id|smic-&gt;read_pos
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
(paren
l_string|&quot; %02x&quot;
comma
(paren
id|smic-&gt;read_data
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
OL
id|smic-&gt;read_pos
)paren
(brace
id|smic-&gt;read_pos
op_assign
id|length
suffix:semicolon
id|smic-&gt;truncated
op_assign
l_int|1
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|data
comma
id|smic-&gt;read_data
comma
id|smic-&gt;read_pos
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|length
op_ge
l_int|3
)paren
op_logical_and
(paren
id|smic-&gt;read_pos
OL
l_int|3
)paren
)paren
(brace
id|data
(braket
l_int|2
)braket
op_assign
id|IPMI_ERR_UNSPECIFIED
suffix:semicolon
id|smic-&gt;read_pos
op_assign
l_int|3
suffix:semicolon
)brace
r_if
c_cond
(paren
id|smic-&gt;truncated
)paren
(brace
id|data
(braket
l_int|2
)braket
op_assign
id|IPMI_ERR_MSG_TRUNCATED
suffix:semicolon
id|smic-&gt;truncated
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|smic-&gt;read_pos
suffix:semicolon
)brace
DECL|function|read_smic_flags
r_static
r_inline
r_int
r_char
id|read_smic_flags
c_func
(paren
r_struct
id|si_sm_data
op_star
id|smic
)paren
(brace
r_return
id|smic-&gt;io
op_member_access_from_pointer
id|inputb
c_func
(paren
id|smic-&gt;io
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|read_smic_status
r_static
r_inline
r_int
r_char
id|read_smic_status
c_func
(paren
r_struct
id|si_sm_data
op_star
id|smic
)paren
(brace
r_return
id|smic-&gt;io
op_member_access_from_pointer
id|inputb
c_func
(paren
id|smic-&gt;io
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|read_smic_data
r_static
r_inline
r_int
r_char
id|read_smic_data
c_func
(paren
r_struct
id|si_sm_data
op_star
id|smic
)paren
(brace
r_return
id|smic-&gt;io
op_member_access_from_pointer
id|inputb
c_func
(paren
id|smic-&gt;io
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|write_smic_flags
r_static
r_inline
r_void
id|write_smic_flags
c_func
(paren
r_struct
id|si_sm_data
op_star
id|smic
comma
r_int
r_char
id|flags
)paren
(brace
id|smic-&gt;io
op_member_access_from_pointer
id|outputb
c_func
(paren
id|smic-&gt;io
comma
l_int|2
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|write_smic_control
r_static
r_inline
r_void
id|write_smic_control
c_func
(paren
r_struct
id|si_sm_data
op_star
id|smic
comma
r_int
r_char
id|control
)paren
(brace
id|smic-&gt;io
op_member_access_from_pointer
id|outputb
c_func
(paren
id|smic-&gt;io
comma
l_int|1
comma
id|control
)paren
suffix:semicolon
)brace
DECL|function|write_si_sm_data
r_static
r_inline
r_void
id|write_si_sm_data
(paren
r_struct
id|si_sm_data
op_star
id|smic
comma
r_int
r_char
id|data
)paren
(brace
id|smic-&gt;io
op_member_access_from_pointer
id|outputb
c_func
(paren
id|smic-&gt;io
comma
l_int|0
comma
id|data
)paren
suffix:semicolon
)brace
DECL|function|start_error_recovery
r_static
r_inline
r_void
id|start_error_recovery
c_func
(paren
r_struct
id|si_sm_data
op_star
id|smic
comma
r_char
op_star
id|reason
)paren
(brace
(paren
id|smic-&gt;error_retries
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|smic-&gt;error_retries
OG
id|SMIC_MAX_ERROR_RETRIES
)paren
(brace
r_if
c_cond
(paren
id|smic_debug
op_amp
id|SMIC_DEBUG_ENABLE
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ipmi_smic_drv: smic hosed: %s&bslash;n&quot;
comma
id|reason
)paren
suffix:semicolon
)brace
id|smic-&gt;state
op_assign
id|SMIC_HOSED
suffix:semicolon
)brace
r_else
(brace
id|smic-&gt;write_count
op_assign
id|smic-&gt;orig_write_count
suffix:semicolon
id|smic-&gt;write_pos
op_assign
l_int|0
suffix:semicolon
id|smic-&gt;read_pos
op_assign
l_int|0
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_START_OP
suffix:semicolon
id|smic-&gt;smic_timeout
op_assign
id|SMIC_RETRY_TIMEOUT
suffix:semicolon
)brace
)brace
DECL|function|write_next_byte
r_static
r_inline
r_void
id|write_next_byte
c_func
(paren
r_struct
id|si_sm_data
op_star
id|smic
)paren
(brace
id|write_si_sm_data
c_func
(paren
id|smic
comma
id|smic-&gt;write_data
(braket
id|smic-&gt;write_pos
)braket
)paren
suffix:semicolon
(paren
id|smic-&gt;write_pos
)paren
op_increment
suffix:semicolon
(paren
id|smic-&gt;write_count
)paren
op_decrement
suffix:semicolon
)brace
DECL|function|read_next_byte
r_static
r_inline
r_void
id|read_next_byte
(paren
r_struct
id|si_sm_data
op_star
id|smic
)paren
(brace
r_if
c_cond
(paren
id|smic-&gt;read_pos
op_ge
id|MAX_SMIC_READ_SIZE
)paren
(brace
id|read_smic_data
(paren
id|smic
)paren
suffix:semicolon
id|smic-&gt;truncated
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|smic-&gt;read_data
(braket
id|smic-&gt;read_pos
)braket
op_assign
id|read_smic_data
c_func
(paren
id|smic
)paren
suffix:semicolon
(paren
id|smic-&gt;read_pos
)paren
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*  SMIC Control/Status Code Components */
DECL|macro|SMIC_GET_STATUS
mdefine_line|#define&t;SMIC_GET_STATUS&t;&t;0x00&t;/* Control form&squot;s name */
DECL|macro|SMIC_READY
mdefine_line|#define&t;SMIC_READY&t;&t;0x00&t;/* Status  form&squot;s name */
DECL|macro|SMIC_WR_START
mdefine_line|#define&t;SMIC_WR_START&t;&t;0x01&t;/* Unified Control/Status names... */
DECL|macro|SMIC_WR_NEXT
mdefine_line|#define&t;SMIC_WR_NEXT&t;&t;0x02
DECL|macro|SMIC_WR_END
mdefine_line|#define&t;SMIC_WR_END&t;&t;0x03
DECL|macro|SMIC_RD_START
mdefine_line|#define&t;SMIC_RD_START&t;&t;0x04
DECL|macro|SMIC_RD_NEXT
mdefine_line|#define&t;SMIC_RD_NEXT&t;&t;0x05
DECL|macro|SMIC_RD_END
mdefine_line|#define&t;SMIC_RD_END&t;&t;0x06
DECL|macro|SMIC_CODE_MASK
mdefine_line|#define&t;SMIC_CODE_MASK&t;&t;0x0f
DECL|macro|SMIC_CONTROL
mdefine_line|#define&t;SMIC_CONTROL&t;&t;0x00
DECL|macro|SMIC_STATUS
mdefine_line|#define&t;SMIC_STATUS&t;&t;0x80
DECL|macro|SMIC_CS_MASK
mdefine_line|#define&t;SMIC_CS_MASK&t;&t;0x80
DECL|macro|SMIC_SMS
mdefine_line|#define&t;SMIC_SMS&t;&t;0x40
DECL|macro|SMIC_SMM
mdefine_line|#define&t;SMIC_SMM&t;&t;0x60
DECL|macro|SMIC_STREAM_MASK
mdefine_line|#define&t;SMIC_STREAM_MASK&t;0x60
multiline_comment|/*  SMIC Control Codes */
DECL|macro|SMIC_CC_SMS_GET_STATUS
mdefine_line|#define&t;SMIC_CC_SMS_GET_STATUS&t;(SMIC_CONTROL|SMIC_SMS|SMIC_GET_STATUS)
DECL|macro|SMIC_CC_SMS_WR_START
mdefine_line|#define&t;SMIC_CC_SMS_WR_START&t;(SMIC_CONTROL|SMIC_SMS|SMIC_WR_START)
DECL|macro|SMIC_CC_SMS_WR_NEXT
mdefine_line|#define&t;SMIC_CC_SMS_WR_NEXT&t;(SMIC_CONTROL|SMIC_SMS|SMIC_WR_NEXT)
DECL|macro|SMIC_CC_SMS_WR_END
mdefine_line|#define&t;SMIC_CC_SMS_WR_END&t;(SMIC_CONTROL|SMIC_SMS|SMIC_WR_END)
DECL|macro|SMIC_CC_SMS_RD_START
mdefine_line|#define&t;SMIC_CC_SMS_RD_START&t;(SMIC_CONTROL|SMIC_SMS|SMIC_RD_START)
DECL|macro|SMIC_CC_SMS_RD_NEXT
mdefine_line|#define&t;SMIC_CC_SMS_RD_NEXT&t;(SMIC_CONTROL|SMIC_SMS|SMIC_RD_NEXT)
DECL|macro|SMIC_CC_SMS_RD_END
mdefine_line|#define&t;SMIC_CC_SMS_RD_END&t;(SMIC_CONTROL|SMIC_SMS|SMIC_RD_END)
DECL|macro|SMIC_CC_SMM_GET_STATUS
mdefine_line|#define&t;SMIC_CC_SMM_GET_STATUS&t;(SMIC_CONTROL|SMIC_SMM|SMIC_GET_STATUS)
DECL|macro|SMIC_CC_SMM_WR_START
mdefine_line|#define&t;SMIC_CC_SMM_WR_START&t;(SMIC_CONTROL|SMIC_SMM|SMIC_WR_START)
DECL|macro|SMIC_CC_SMM_WR_NEXT
mdefine_line|#define&t;SMIC_CC_SMM_WR_NEXT&t;(SMIC_CONTROL|SMIC_SMM|SMIC_WR_NEXT)
DECL|macro|SMIC_CC_SMM_WR_END
mdefine_line|#define&t;SMIC_CC_SMM_WR_END&t;(SMIC_CONTROL|SMIC_SMM|SMIC_WR_END)
DECL|macro|SMIC_CC_SMM_RD_START
mdefine_line|#define&t;SMIC_CC_SMM_RD_START&t;(SMIC_CONTROL|SMIC_SMM|SMIC_RD_START)
DECL|macro|SMIC_CC_SMM_RD_NEXT
mdefine_line|#define&t;SMIC_CC_SMM_RD_NEXT&t;(SMIC_CONTROL|SMIC_SMM|SMIC_RD_NEXT)
DECL|macro|SMIC_CC_SMM_RD_END
mdefine_line|#define&t;SMIC_CC_SMM_RD_END&t;(SMIC_CONTROL|SMIC_SMM|SMIC_RD_END)
multiline_comment|/*  SMIC Status Codes */
DECL|macro|SMIC_SC_SMS_READY
mdefine_line|#define&t;SMIC_SC_SMS_READY&t;(SMIC_STATUS|SMIC_SMS|SMIC_READY)
DECL|macro|SMIC_SC_SMS_WR_START
mdefine_line|#define&t;SMIC_SC_SMS_WR_START&t;(SMIC_STATUS|SMIC_SMS|SMIC_WR_START)
DECL|macro|SMIC_SC_SMS_WR_NEXT
mdefine_line|#define&t;SMIC_SC_SMS_WR_NEXT&t;(SMIC_STATUS|SMIC_SMS|SMIC_WR_NEXT)
DECL|macro|SMIC_SC_SMS_WR_END
mdefine_line|#define&t;SMIC_SC_SMS_WR_END&t;(SMIC_STATUS|SMIC_SMS|SMIC_WR_END)
DECL|macro|SMIC_SC_SMS_RD_START
mdefine_line|#define&t;SMIC_SC_SMS_RD_START&t;(SMIC_STATUS|SMIC_SMS|SMIC_RD_START)
DECL|macro|SMIC_SC_SMS_RD_NEXT
mdefine_line|#define&t;SMIC_SC_SMS_RD_NEXT&t;(SMIC_STATUS|SMIC_SMS|SMIC_RD_NEXT)
DECL|macro|SMIC_SC_SMS_RD_END
mdefine_line|#define&t;SMIC_SC_SMS_RD_END&t;(SMIC_STATUS|SMIC_SMS|SMIC_RD_END)
DECL|macro|SMIC_SC_SMM_READY
mdefine_line|#define&t;SMIC_SC_SMM_READY&t;(SMIC_STATUS|SMIC_SMM|SMIC_READY)
DECL|macro|SMIC_SC_SMM_WR_START
mdefine_line|#define&t;SMIC_SC_SMM_WR_START&t;(SMIC_STATUS|SMIC_SMM|SMIC_WR_START)
DECL|macro|SMIC_SC_SMM_WR_NEXT
mdefine_line|#define&t;SMIC_SC_SMM_WR_NEXT&t;(SMIC_STATUS|SMIC_SMM|SMIC_WR_NEXT)
DECL|macro|SMIC_SC_SMM_WR_END
mdefine_line|#define&t;SMIC_SC_SMM_WR_END&t;(SMIC_STATUS|SMIC_SMM|SMIC_WR_END)
DECL|macro|SMIC_SC_SMM_RD_START
mdefine_line|#define&t;SMIC_SC_SMM_RD_START&t;(SMIC_STATUS|SMIC_SMM|SMIC_RD_START)
DECL|macro|SMIC_SC_SMM_RD_NEXT
mdefine_line|#define&t;SMIC_SC_SMM_RD_NEXT&t;(SMIC_STATUS|SMIC_SMM|SMIC_RD_NEXT)
DECL|macro|SMIC_SC_SMM_RD_END
mdefine_line|#define&t;SMIC_SC_SMM_RD_END&t;(SMIC_STATUS|SMIC_SMM|SMIC_RD_END)
multiline_comment|/* these are the control/status codes we actually use&n;&t;SMIC_CC_SMS_GET_STATUS&t;0x40&n;&t;SMIC_CC_SMS_WR_START&t;0x41&n;&t;SMIC_CC_SMS_WR_NEXT&t;0x42&n;&t;SMIC_CC_SMS_WR_END&t;0x43&n;&t;SMIC_CC_SMS_RD_START&t;0x44&n;&t;SMIC_CC_SMS_RD_NEXT&t;0x45&n;&t;SMIC_CC_SMS_RD_END&t;0x46&n;&n;&t;SMIC_SC_SMS_READY&t;0xC0&n;&t;SMIC_SC_SMS_WR_START&t;0xC1&n;&t;SMIC_SC_SMS_WR_NEXT&t;0xC2&n;&t;SMIC_SC_SMS_WR_END&t;0xC3&n;&t;SMIC_SC_SMS_RD_START&t;0xC4&n;&t;SMIC_SC_SMS_RD_NEXT&t;0xC5&n;&t;SMIC_SC_SMS_RD_END&t;0xC6&n;*/
DECL|function|smic_event
r_static
r_enum
id|si_sm_result
id|smic_event
(paren
r_struct
id|si_sm_data
op_star
id|smic
comma
r_int
id|time
)paren
(brace
r_int
r_char
id|status
suffix:semicolon
r_int
r_char
id|flags
suffix:semicolon
r_int
r_char
id|data
suffix:semicolon
r_if
c_cond
(paren
id|smic-&gt;state
op_eq
id|SMIC_HOSED
)paren
(brace
id|init_smic_data
c_func
(paren
id|smic
comma
id|smic-&gt;io
)paren
suffix:semicolon
r_return
id|SI_SM_HOSED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|smic-&gt;state
op_ne
id|SMIC_IDLE
)paren
(brace
r_if
c_cond
(paren
id|smic_debug
op_amp
id|SMIC_DEBUG_STATES
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;smic_event - smic-&gt;smic_timeout = %ld,&quot;
l_string|&quot; time = %ld&bslash;n&quot;
comma
id|smic-&gt;smic_timeout
comma
id|time
)paren
suffix:semicolon
)brace
multiline_comment|/* FIXME: smic_event is sometimes called with time &gt; SMIC_RETRY_TIMEOUT */
r_if
c_cond
(paren
id|time
OL
id|SMIC_RETRY_TIMEOUT
)paren
(brace
id|smic-&gt;smic_timeout
op_sub_assign
id|time
suffix:semicolon
r_if
c_cond
(paren
id|smic-&gt;smic_timeout
OL
l_int|0
)paren
(brace
id|start_error_recovery
c_func
(paren
id|smic
comma
l_string|&quot;smic timed out.&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
)brace
)brace
id|flags
op_assign
id|read_smic_flags
c_func
(paren
id|smic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|SMIC_FLAG_BSY
)paren
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
id|status
op_assign
id|read_smic_status
(paren
id|smic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smic_debug
op_amp
id|SMIC_DEBUG_STATES
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;smic_event - state = %d, flags = 0x%02x,&quot;
l_string|&quot; status = 0x%02x&bslash;n&quot;
comma
id|smic-&gt;state
comma
id|flags
comma
id|status
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|smic-&gt;state
)paren
(brace
r_case
id|SMIC_IDLE
suffix:colon
multiline_comment|/* in IDLE we check for available messages */
r_if
c_cond
(paren
id|flags
op_amp
(paren
id|SMIC_SMI
op_or
id|SMIC_EVM_DATA_AVAIL
op_or
id|SMIC_SMS_DATA_AVAIL
)paren
)paren
(brace
r_return
id|SI_SM_ATTN
suffix:semicolon
)brace
r_return
id|SI_SM_IDLE
suffix:semicolon
r_case
id|SMIC_START_OP
suffix:colon
multiline_comment|/* sanity check whether smic is really idle */
id|write_smic_control
c_func
(paren
id|smic
comma
id|SMIC_CC_SMS_GET_STATUS
)paren
suffix:semicolon
id|write_smic_flags
c_func
(paren
id|smic
comma
id|flags
op_or
id|SMIC_FLAG_BSY
)paren
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_OP_OK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SMIC_OP_OK
suffix:colon
r_if
c_cond
(paren
id|status
op_ne
id|SMIC_SC_SMS_READY
)paren
(brace
multiline_comment|/* this should not happen */
id|start_error_recovery
c_func
(paren
id|smic
comma
l_string|&quot;state = SMIC_OP_OK,&quot;
l_string|&quot; status != SMIC_SC_SMS_READY&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
multiline_comment|/* OK so far; smic is idle let us start ... */
id|write_smic_control
c_func
(paren
id|smic
comma
id|SMIC_CC_SMS_WR_START
)paren
suffix:semicolon
id|write_next_byte
c_func
(paren
id|smic
)paren
suffix:semicolon
id|write_smic_flags
c_func
(paren
id|smic
comma
id|flags
op_or
id|SMIC_FLAG_BSY
)paren
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_WRITE_START
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SMIC_WRITE_START
suffix:colon
r_if
c_cond
(paren
id|status
op_ne
id|SMIC_SC_SMS_WR_START
)paren
(brace
id|start_error_recovery
c_func
(paren
id|smic
comma
l_string|&quot;state = SMIC_WRITE_START, &quot;
l_string|&quot;status != SMIC_SC_SMS_WR_START&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
multiline_comment|/* we must not issue WR_(NEXT|END) unless&n;                   TX_DATA_READY is set */
r_if
c_cond
(paren
id|flags
op_amp
id|SMIC_TX_DATA_READY
)paren
(brace
r_if
c_cond
(paren
id|smic-&gt;write_count
op_eq
l_int|1
)paren
(brace
multiline_comment|/* last byte */
id|write_smic_control
c_func
(paren
id|smic
comma
id|SMIC_CC_SMS_WR_END
)paren
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_WRITE_END
suffix:semicolon
)brace
r_else
(brace
id|write_smic_control
c_func
(paren
id|smic
comma
id|SMIC_CC_SMS_WR_NEXT
)paren
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_WRITE_NEXT
suffix:semicolon
)brace
id|write_next_byte
c_func
(paren
id|smic
)paren
suffix:semicolon
id|write_smic_flags
c_func
(paren
id|smic
comma
id|flags
op_or
id|SMIC_FLAG_BSY
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SMIC_WRITE_NEXT
suffix:colon
r_if
c_cond
(paren
id|status
op_ne
id|SMIC_SC_SMS_WR_NEXT
)paren
(brace
id|start_error_recovery
c_func
(paren
id|smic
comma
l_string|&quot;state = SMIC_WRITE_NEXT, &quot;
l_string|&quot;status != SMIC_SC_SMS_WR_NEXT&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
multiline_comment|/* this is the same code as in SMIC_WRITE_START */
r_if
c_cond
(paren
id|flags
op_amp
id|SMIC_TX_DATA_READY
)paren
(brace
r_if
c_cond
(paren
id|smic-&gt;write_count
op_eq
l_int|1
)paren
(brace
id|write_smic_control
c_func
(paren
id|smic
comma
id|SMIC_CC_SMS_WR_END
)paren
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_WRITE_END
suffix:semicolon
)brace
r_else
(brace
id|write_smic_control
c_func
(paren
id|smic
comma
id|SMIC_CC_SMS_WR_NEXT
)paren
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_WRITE_NEXT
suffix:semicolon
)brace
id|write_next_byte
c_func
(paren
id|smic
)paren
suffix:semicolon
id|write_smic_flags
c_func
(paren
id|smic
comma
id|flags
op_or
id|SMIC_FLAG_BSY
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SMIC_WRITE_END
suffix:colon
r_if
c_cond
(paren
id|status
op_ne
id|SMIC_SC_SMS_WR_END
)paren
(brace
id|start_error_recovery
(paren
id|smic
comma
l_string|&quot;state = SMIC_WRITE_END, &quot;
l_string|&quot;status != SMIC_SC_SMS_WR_END&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
multiline_comment|/* data register holds an error code */
id|data
op_assign
id|read_smic_data
c_func
(paren
id|smic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|smic_debug
op_amp
id|SMIC_DEBUG_ENABLE
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SMIC_WRITE_END: data = %02x&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
)brace
id|start_error_recovery
c_func
(paren
id|smic
comma
l_string|&quot;state = SMIC_WRITE_END, &quot;
l_string|&quot;data != SUCCESS&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
r_else
(brace
id|smic-&gt;state
op_assign
id|SMIC_WRITE2READ
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SMIC_WRITE2READ
suffix:colon
multiline_comment|/* we must wait for RX_DATA_READY to be set before we&n;                   can continue */
r_if
c_cond
(paren
id|flags
op_amp
id|SMIC_RX_DATA_READY
)paren
(brace
id|write_smic_control
c_func
(paren
id|smic
comma
id|SMIC_CC_SMS_RD_START
)paren
suffix:semicolon
id|write_smic_flags
c_func
(paren
id|smic
comma
id|flags
op_or
id|SMIC_FLAG_BSY
)paren
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_READ_START
suffix:semicolon
)brace
r_else
(brace
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SMIC_READ_START
suffix:colon
r_if
c_cond
(paren
id|status
op_ne
id|SMIC_SC_SMS_RD_START
)paren
(brace
id|start_error_recovery
c_func
(paren
id|smic
comma
l_string|&quot;state = SMIC_READ_START, &quot;
l_string|&quot;status != SMIC_SC_SMS_RD_START&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|SMIC_RX_DATA_READY
)paren
(brace
id|read_next_byte
c_func
(paren
id|smic
)paren
suffix:semicolon
id|write_smic_control
c_func
(paren
id|smic
comma
id|SMIC_CC_SMS_RD_NEXT
)paren
suffix:semicolon
id|write_smic_flags
c_func
(paren
id|smic
comma
id|flags
op_or
id|SMIC_FLAG_BSY
)paren
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_READ_NEXT
suffix:semicolon
)brace
r_else
(brace
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SMIC_READ_NEXT
suffix:colon
r_switch
c_cond
(paren
id|status
)paren
(brace
multiline_comment|/* smic tells us that this is the last byte to be read&n;                   --&gt; clean up */
r_case
id|SMIC_SC_SMS_RD_END
suffix:colon
id|read_next_byte
c_func
(paren
id|smic
)paren
suffix:semicolon
id|write_smic_control
c_func
(paren
id|smic
comma
id|SMIC_CC_SMS_RD_END
)paren
suffix:semicolon
id|write_smic_flags
c_func
(paren
id|smic
comma
id|flags
op_or
id|SMIC_FLAG_BSY
)paren
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_READ_END
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SMIC_SC_SMS_RD_NEXT
suffix:colon
r_if
c_cond
(paren
id|flags
op_amp
id|SMIC_RX_DATA_READY
)paren
(brace
id|read_next_byte
c_func
(paren
id|smic
)paren
suffix:semicolon
id|write_smic_control
c_func
(paren
id|smic
comma
id|SMIC_CC_SMS_RD_NEXT
)paren
suffix:semicolon
id|write_smic_flags
c_func
(paren
id|smic
comma
id|flags
op_or
id|SMIC_FLAG_BSY
)paren
suffix:semicolon
id|smic-&gt;state
op_assign
id|SMIC_READ_NEXT
suffix:semicolon
)brace
r_else
(brace
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|start_error_recovery
c_func
(paren
id|smic
comma
l_string|&quot;state = SMIC_READ_NEXT, &quot;
l_string|&quot;status != SMIC_SC_SMS_RD_(NEXT|END)&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SMIC_READ_END
suffix:colon
r_if
c_cond
(paren
id|status
op_ne
id|SMIC_SC_SMS_READY
)paren
(brace
id|start_error_recovery
c_func
(paren
id|smic
comma
l_string|&quot;state = SMIC_READ_END, &quot;
l_string|&quot;status != SMIC_SC_SMS_READY&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
id|data
op_assign
id|read_smic_data
c_func
(paren
id|smic
)paren
suffix:semicolon
multiline_comment|/* data register holds an error code */
r_if
c_cond
(paren
id|data
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|smic_debug
op_amp
id|SMIC_DEBUG_ENABLE
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SMIC_READ_END: data = %02x&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
)brace
id|start_error_recovery
c_func
(paren
id|smic
comma
l_string|&quot;state = SMIC_READ_END, &quot;
l_string|&quot;data != SUCCESS&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
r_else
(brace
id|smic-&gt;state
op_assign
id|SMIC_IDLE
suffix:semicolon
r_return
id|SI_SM_TRANSACTION_COMPLETE
suffix:semicolon
)brace
r_case
id|SMIC_HOSED
suffix:colon
id|init_smic_data
c_func
(paren
id|smic
comma
id|smic-&gt;io
)paren
suffix:semicolon
r_return
id|SI_SM_HOSED
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|smic_debug
op_amp
id|SMIC_DEBUG_ENABLE
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;smic-&gt;state = %d&bslash;n&quot;
comma
id|smic-&gt;state
)paren
suffix:semicolon
id|start_error_recovery
c_func
(paren
id|smic
comma
l_string|&quot;state = UNKNOWN&quot;
)paren
suffix:semicolon
r_return
id|SI_SM_CALL_WITH_DELAY
suffix:semicolon
)brace
)brace
id|smic-&gt;smic_timeout
op_assign
id|SMIC_RETRY_TIMEOUT
suffix:semicolon
r_return
id|SI_SM_CALL_WITHOUT_DELAY
suffix:semicolon
)brace
DECL|function|smic_detect
r_static
r_int
id|smic_detect
c_func
(paren
r_struct
id|si_sm_data
op_star
id|smic
)paren
(brace
multiline_comment|/* It&squot;s impossible for the SMIC fnags register to be all 1&squot;s,&n;&t;   (assuming a properly functioning, self-initialized BMC)&n;&t;   but that&squot;s what you get from reading a bogus address, so we&n;&t;   test that first. */
r_if
c_cond
(paren
id|read_smic_flags
c_func
(paren
id|smic
)paren
op_eq
l_int|0xff
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smic_cleanup
r_static
r_void
id|smic_cleanup
c_func
(paren
r_struct
id|si_sm_data
op_star
id|kcs
)paren
(brace
)brace
DECL|function|smic_size
r_static
r_int
id|smic_size
c_func
(paren
r_void
)paren
(brace
r_return
r_sizeof
(paren
r_struct
id|si_sm_data
)paren
suffix:semicolon
)brace
DECL|variable|smic_smi_handlers
r_struct
id|si_sm_handlers
id|smic_smi_handlers
op_assign
(brace
dot
id|version
op_assign
id|IPMI_SMIC_VERSION
comma
dot
id|init_data
op_assign
id|init_smic_data
comma
dot
id|start_transaction
op_assign
id|start_smic_transaction
comma
dot
id|get_result
op_assign
id|smic_get_result
comma
dot
id|event
op_assign
id|smic_event
comma
dot
id|detect
op_assign
id|smic_detect
comma
dot
id|cleanup
op_assign
id|smic_cleanup
comma
dot
id|size
op_assign
id|smic_size
comma
)brace
suffix:semicolon
eof
