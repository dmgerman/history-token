multiline_comment|/*&n; * drivers/s390/char/monreader.c&n; *&n; * Character device driver for reading z/VM *MONITOR service records.&n; *&n; * Copyright (C) 2004 IBM Corporation, IBM Deutschland Entwicklung GmbH.&n; *&n; * Author: Gerald Schaefer &lt;geraldsc@de.ibm.com&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;asm/extmem.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &quot;../net/iucv.h&quot;
singleline_comment|//#define MON_DEBUG&t;&t;&t;/* Debug messages on/off */
DECL|macro|MON_NAME
mdefine_line|#define MON_NAME &quot;monreader&quot;
DECL|macro|P_INFO
mdefine_line|#define P_INFO(x...)&t;printk(KERN_INFO MON_NAME &quot; info: &quot; x)
DECL|macro|P_ERROR
mdefine_line|#define P_ERROR(x...)&t;printk(KERN_ERR MON_NAME &quot; error: &quot; x)
DECL|macro|P_WARNING
mdefine_line|#define P_WARNING(x...)&t;printk(KERN_WARNING MON_NAME &quot; warning: &quot; x)
macro_line|#ifdef MON_DEBUG
DECL|macro|P_DEBUG
mdefine_line|#define P_DEBUG(x...)   printk(KERN_DEBUG MON_NAME &quot; debug: &quot; x)
macro_line|#else
DECL|macro|P_DEBUG
mdefine_line|#define P_DEBUG(x...)   do {} while (0)
macro_line|#endif
DECL|macro|MON_COLLECT_SAMPLE
mdefine_line|#define MON_COLLECT_SAMPLE 0x80
DECL|macro|MON_COLLECT_EVENT
mdefine_line|#define MON_COLLECT_EVENT  0x40
DECL|macro|MON_SERVICE
mdefine_line|#define MON_SERVICE&t;   &quot;*MONITOR&quot;
DECL|macro|MON_IN_USE
mdefine_line|#define MON_IN_USE&t;   0x01
DECL|macro|MON_MSGLIM
mdefine_line|#define MON_MSGLIM&t;   255
DECL|variable|mon_dcss_name
r_static
r_char
id|mon_dcss_name
(braket
l_int|9
)braket
op_assign
l_string|&quot;MONDCSS&bslash;0&quot;
suffix:semicolon
DECL|struct|mon_msg
r_struct
id|mon_msg
(brace
DECL|member|pos
id|u32
id|pos
suffix:semicolon
DECL|member|mca_offset
id|u32
id|mca_offset
suffix:semicolon
DECL|member|local_eib
id|iucv_MessagePending
id|local_eib
suffix:semicolon
DECL|member|msglim_reached
r_char
id|msglim_reached
suffix:semicolon
DECL|member|replied_msglim
r_char
id|replied_msglim
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mon_private
r_struct
id|mon_private
(brace
DECL|member|pathid
id|u16
id|pathid
suffix:semicolon
DECL|member|iucv_handle
id|iucv_handle_t
id|iucv_handle
suffix:semicolon
DECL|member|msg_array
r_struct
id|mon_msg
op_star
id|msg_array
(braket
id|MON_MSGLIM
)braket
suffix:semicolon
DECL|member|write_index
r_int
r_int
id|write_index
suffix:semicolon
DECL|member|read_index
r_int
r_int
id|read_index
suffix:semicolon
DECL|member|msglim_count
id|atomic_t
id|msglim_count
suffix:semicolon
DECL|member|read_ready
id|atomic_t
id|read_ready
suffix:semicolon
DECL|member|iucv_connected
id|atomic_t
id|iucv_connected
suffix:semicolon
DECL|member|iucv_severed
id|atomic_t
id|iucv_severed
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|mon_in_use
r_static
r_int
r_int
id|mon_in_use
op_assign
l_int|0
suffix:semicolon
DECL|variable|mon_dcss_start
r_static
r_int
r_int
id|mon_dcss_start
suffix:semicolon
DECL|variable|mon_dcss_end
r_static
r_int
r_int
id|mon_dcss_end
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|mon_read_wait_queue
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|mon_conn_wait_queue
)paren
suffix:semicolon
DECL|variable|iucv_host
r_static
id|u8
id|iucv_host
(braket
l_int|8
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
DECL|variable|user_data_connect
r_static
id|u8
id|user_data_connect
(braket
l_int|16
)braket
op_assign
(brace
multiline_comment|/* Version code, must be 0x01 for shared mode */
l_int|0x01
comma
multiline_comment|/* what to collect */
id|MON_COLLECT_SAMPLE
op_or
id|MON_COLLECT_EVENT
comma
multiline_comment|/* DCSS name in EBCDIC, 8 bytes padded with blanks */
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
)brace
suffix:semicolon
DECL|variable|user_data_sever
r_static
id|u8
id|user_data_sever
(braket
l_int|16
)braket
op_assign
(brace
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
)brace
suffix:semicolon
multiline_comment|/******************************************************************************&n; *                             helper functions                               *&n; *****************************************************************************/
multiline_comment|/*&n; * Create the 8 bytes EBCDIC DCSS segment name from&n; * an ASCII name, incl. padding&n; */
r_static
r_inline
r_void
DECL|function|dcss_mkname
id|dcss_mkname
c_func
(paren
r_char
op_star
id|ascii_name
comma
r_char
op_star
id|ebcdic_name
)paren
(brace
r_int
id|i
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ascii_name
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_break
suffix:semicolon
id|ebcdic_name
(braket
id|i
)braket
op_assign
id|toupper
c_func
(paren
id|ascii_name
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|ebcdic_name
(braket
id|i
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|ASCEBC
c_func
(paren
id|ebcdic_name
comma
l_int|8
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * print appropriate error message for segment_load()/segment_type()&n; * return code&n; */
r_static
r_void
DECL|function|mon_segment_warn
id|mon_segment_warn
c_func
(paren
r_int
id|rc
comma
r_char
op_star
id|seg_name
)paren
(brace
r_switch
c_cond
(paren
id|rc
)paren
(brace
r_case
op_minus
id|ENOENT
suffix:colon
id|P_WARNING
c_func
(paren
l_string|&quot;cannot load/query segment %s, does not exist&bslash;n&quot;
comma
id|seg_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ENOSYS
suffix:colon
id|P_WARNING
c_func
(paren
l_string|&quot;cannot load/query segment %s, not running on VM&bslash;n&quot;
comma
id|seg_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EIO
suffix:colon
id|P_WARNING
c_func
(paren
l_string|&quot;cannot load/query segment %s, hardware error&bslash;n&quot;
comma
id|seg_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ENOTSUPP
suffix:colon
id|P_WARNING
c_func
(paren
l_string|&quot;cannot load/query segment %s, is a multi-part &quot;
l_string|&quot;segment&bslash;n&quot;
comma
id|seg_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ENOSPC
suffix:colon
id|P_WARNING
c_func
(paren
l_string|&quot;cannot load/query segment %s, overlaps with &quot;
l_string|&quot;storage&bslash;n&quot;
comma
id|seg_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EBUSY
suffix:colon
id|P_WARNING
c_func
(paren
l_string|&quot;cannot load/query segment %s, overlaps with &quot;
l_string|&quot;already loaded dcss&bslash;n&quot;
comma
id|seg_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EPERM
suffix:colon
id|P_WARNING
c_func
(paren
l_string|&quot;cannot load/query segment %s, already loaded in &quot;
l_string|&quot;incompatible mode&bslash;n&quot;
comma
id|seg_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ENOMEM
suffix:colon
id|P_WARNING
c_func
(paren
l_string|&quot;cannot load/query segment %s, out of memory&bslash;n&quot;
comma
id|seg_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ERANGE
suffix:colon
id|P_WARNING
c_func
(paren
l_string|&quot;cannot load/query segment %s, exceeds kernel &quot;
l_string|&quot;mapping range&bslash;n&quot;
comma
id|seg_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|P_WARNING
c_func
(paren
l_string|&quot;cannot load/query segment %s, return value %i&bslash;n&quot;
comma
id|seg_name
comma
id|rc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_inline
r_int
r_int
DECL|function|mon_mca_start
id|mon_mca_start
c_func
(paren
r_struct
id|mon_msg
op_star
id|monmsg
)paren
(brace
r_return
id|monmsg-&gt;local_eib.ln1msg1.iprmmsg1_u32
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|mon_mca_end
id|mon_mca_end
c_func
(paren
r_struct
id|mon_msg
op_star
id|monmsg
)paren
(brace
r_return
id|monmsg-&gt;local_eib.ln1msg2.ipbfln1f
suffix:semicolon
)brace
r_static
r_inline
id|u8
DECL|function|mon_mca_type
id|mon_mca_type
c_func
(paren
r_struct
id|mon_msg
op_star
id|monmsg
comma
id|u8
id|index
)paren
(brace
r_return
op_star
(paren
(paren
id|u8
op_star
)paren
id|mon_mca_start
c_func
(paren
id|monmsg
)paren
op_plus
id|monmsg-&gt;mca_offset
op_plus
id|index
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
DECL|function|mon_mca_size
id|mon_mca_size
c_func
(paren
r_struct
id|mon_msg
op_star
id|monmsg
)paren
(brace
r_return
id|mon_mca_end
c_func
(paren
id|monmsg
)paren
op_minus
id|mon_mca_start
c_func
(paren
id|monmsg
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_static
r_inline
id|u32
DECL|function|mon_rec_start
id|mon_rec_start
c_func
(paren
r_struct
id|mon_msg
op_star
id|monmsg
)paren
(brace
r_return
op_star
(paren
(paren
id|u32
op_star
)paren
(paren
id|mon_mca_start
c_func
(paren
id|monmsg
)paren
op_plus
id|monmsg-&gt;mca_offset
op_plus
l_int|4
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
DECL|function|mon_rec_end
id|mon_rec_end
c_func
(paren
r_struct
id|mon_msg
op_star
id|monmsg
)paren
(brace
r_return
op_star
(paren
(paren
id|u32
op_star
)paren
(paren
id|mon_mca_start
c_func
(paren
id|monmsg
)paren
op_plus
id|monmsg-&gt;mca_offset
op_plus
l_int|8
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|mon_check_mca
id|mon_check_mca
c_func
(paren
r_struct
id|mon_msg
op_star
id|monmsg
)paren
(brace
r_if
c_cond
(paren
(paren
id|mon_rec_end
c_func
(paren
id|monmsg
)paren
op_le
id|mon_rec_start
c_func
(paren
id|monmsg
)paren
)paren
op_logical_or
(paren
id|mon_rec_start
c_func
(paren
id|monmsg
)paren
OL
id|mon_dcss_start
)paren
op_logical_or
(paren
id|mon_rec_end
c_func
(paren
id|monmsg
)paren
OG
id|mon_dcss_end
)paren
op_logical_or
(paren
id|mon_mca_type
c_func
(paren
id|monmsg
comma
l_int|0
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
id|mon_mca_size
c_func
(paren
id|monmsg
)paren
op_mod
l_int|12
op_ne
l_int|0
)paren
op_logical_or
(paren
id|mon_mca_end
c_func
(paren
id|monmsg
)paren
op_le
id|mon_mca_start
c_func
(paren
id|monmsg
)paren
)paren
op_logical_or
(paren
id|mon_mca_end
c_func
(paren
id|monmsg
)paren
OG
id|mon_dcss_end
)paren
op_logical_or
(paren
id|mon_mca_start
c_func
(paren
id|monmsg
)paren
OL
id|mon_dcss_start
)paren
op_logical_or
(paren
(paren
id|mon_mca_type
c_func
(paren
id|monmsg
comma
l_int|1
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|mon_mca_type
c_func
(paren
id|monmsg
comma
l_int|2
)paren
op_eq
l_int|0
)paren
)paren
)paren
(brace
id|P_DEBUG
c_func
(paren
l_string|&quot;READ, IGNORED INVALID MCA&bslash;n&bslash;n&quot;
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
r_inline
r_int
DECL|function|mon_send_reply
id|mon_send_reply
c_func
(paren
r_struct
id|mon_msg
op_star
id|monmsg
comma
r_struct
id|mon_private
op_star
id|monpriv
)paren
(brace
id|u8
id|prmmsg
(braket
l_int|8
)braket
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;read, REPLY: pathid = 0x%04X, msgid = 0x%08X, trgcls = &quot;
l_string|&quot;0x%08X&bslash;n&bslash;n&quot;
comma
id|monmsg-&gt;local_eib.ippathid
comma
id|monmsg-&gt;local_eib.ipmsgid
comma
id|monmsg-&gt;local_eib.iptrgcls
)paren
suffix:semicolon
id|rc
op_assign
id|iucv_reply_prmmsg
c_func
(paren
id|monmsg-&gt;local_eib.ippathid
comma
id|monmsg-&gt;local_eib.ipmsgid
comma
id|monmsg-&gt;local_eib.iptrgcls
comma
l_int|0
comma
id|prmmsg
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|monpriv-&gt;msglim_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|monmsg-&gt;msglim_reached
)paren
)paren
(brace
id|monmsg-&gt;pos
op_assign
l_int|0
suffix:semicolon
id|monpriv-&gt;read_index
op_assign
(paren
id|monpriv-&gt;read_index
op_plus
l_int|1
)paren
op_mod
id|MON_MSGLIM
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|monpriv-&gt;read_ready
)paren
suffix:semicolon
)brace
r_else
id|monmsg-&gt;replied_msglim
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|P_ERROR
c_func
(paren
l_string|&quot;read, IUCV reply failed with rc = %i&bslash;n&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|mon_private
op_star
DECL|function|mon_alloc_mem
id|mon_alloc_mem
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_struct
id|mon_private
op_star
id|monpriv
suffix:semicolon
id|monpriv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mon_private
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|monpriv
)paren
(brace
id|P_ERROR
c_func
(paren
l_string|&quot;no memory for monpriv&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|monpriv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mon_private
)paren
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
id|MON_MSGLIM
suffix:semicolon
id|i
op_increment
)paren
(brace
id|monpriv-&gt;msg_array
(braket
id|i
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mon_msg
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|monpriv-&gt;msg_array
(braket
id|i
)braket
)paren
(brace
id|P_ERROR
c_func
(paren
l_string|&quot;open, no memory for msg_array&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
id|kfree
c_func
(paren
id|monpriv-&gt;msg_array
(braket
id|j
)braket
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|monpriv-&gt;msg_array
(braket
id|i
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mon_msg
)paren
)paren
suffix:semicolon
)brace
r_return
id|monpriv
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|mon_read_debug
id|mon_read_debug
c_func
(paren
r_struct
id|mon_msg
op_star
id|monmsg
comma
r_struct
id|mon_private
op_star
id|monpriv
)paren
(brace
macro_line|#ifdef MON_DEBUG
id|u8
id|msg_type
(braket
l_int|2
)braket
comma
id|mca_type
suffix:semicolon
r_int
r_int
id|records_len
suffix:semicolon
id|records_len
op_assign
id|mon_rec_end
c_func
(paren
id|monmsg
)paren
op_minus
id|mon_rec_start
c_func
(paren
id|monmsg
)paren
op_plus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|msg_type
comma
op_amp
id|monmsg-&gt;local_eib.iptrgcls
comma
l_int|2
)paren
suffix:semicolon
id|EBCASC
c_func
(paren
id|msg_type
comma
l_int|2
)paren
suffix:semicolon
id|mca_type
op_assign
id|mon_mca_type
c_func
(paren
id|monmsg
comma
l_int|0
)paren
suffix:semicolon
id|EBCASC
c_func
(paren
op_amp
id|mca_type
comma
l_int|1
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;read, mon_read_index = %i, mon_write_index = %i&bslash;n&quot;
comma
id|monpriv-&gt;read_index
comma
id|monpriv-&gt;write_index
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;read, pathid = 0x%04X, msgid = 0x%08X, trgcls = 0x%08X&bslash;n&quot;
comma
id|monmsg-&gt;local_eib.ippathid
comma
id|monmsg-&gt;local_eib.ipmsgid
comma
id|monmsg-&gt;local_eib.iptrgcls
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;read, msg_type = &squot;%c%c&squot;, mca_type = &squot;%c&squot; / 0x%X / 0x%X&bslash;n&quot;
comma
id|msg_type
(braket
l_int|0
)braket
comma
id|msg_type
(braket
l_int|1
)braket
comma
id|mca_type
ques
c_cond
id|mca_type
suffix:colon
l_char|&squot;X&squot;
comma
id|mon_mca_type
c_func
(paren
id|monmsg
comma
l_int|1
)paren
comma
id|mon_mca_type
c_func
(paren
id|monmsg
comma
l_int|2
)paren
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;read, MCA: start = 0x%lX, end = 0x%lX&bslash;n&quot;
comma
id|mon_mca_start
c_func
(paren
id|monmsg
)paren
comma
id|mon_mca_end
c_func
(paren
id|monmsg
)paren
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;read, REC: start = 0x%X, end = 0x%X, len = %lu&bslash;n&bslash;n&quot;
comma
id|mon_rec_start
c_func
(paren
id|monmsg
)paren
comma
id|mon_rec_end
c_func
(paren
id|monmsg
)paren
comma
id|records_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mon_mca_size
c_func
(paren
id|monmsg
)paren
OG
l_int|12
)paren
id|P_DEBUG
c_func
(paren
l_string|&quot;READ, MORE THAN ONE MCA&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_inline
r_void
DECL|function|mon_next_mca
id|mon_next_mca
c_func
(paren
r_struct
id|mon_msg
op_star
id|monmsg
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
(paren
id|mon_mca_size
c_func
(paren
id|monmsg
)paren
op_minus
id|monmsg-&gt;mca_offset
)paren
op_eq
l_int|12
)paren
)paren
r_return
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;READ, NEXT MCA&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|monmsg-&gt;mca_offset
op_add_assign
l_int|12
suffix:semicolon
id|monmsg-&gt;pos
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|mon_msg
op_star
DECL|function|mon_next_message
id|mon_next_message
c_func
(paren
r_struct
id|mon_private
op_star
id|monpriv
)paren
(brace
r_struct
id|mon_msg
op_star
id|monmsg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|monpriv-&gt;read_ready
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|monmsg
op_assign
id|monpriv-&gt;msg_array
(braket
id|monpriv-&gt;read_index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|monmsg-&gt;replied_msglim
)paren
)paren
(brace
id|monmsg-&gt;replied_msglim
op_assign
l_int|0
suffix:semicolon
id|monmsg-&gt;msglim_reached
op_assign
l_int|0
suffix:semicolon
id|monmsg-&gt;pos
op_assign
l_int|0
suffix:semicolon
id|P_WARNING
c_func
(paren
l_string|&quot;read, message limit reached&bslash;n&quot;
)paren
suffix:semicolon
id|monpriv-&gt;read_index
op_assign
(paren
id|monpriv-&gt;read_index
op_plus
l_int|1
)paren
op_mod
id|MON_MSGLIM
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|monpriv-&gt;read_ready
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EOVERFLOW
)paren
suffix:semicolon
)brace
r_return
id|monmsg
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *                               IUCV handler                                 *&n; *****************************************************************************/
r_static
r_void
DECL|function|mon_iucv_ConnectionComplete
id|mon_iucv_ConnectionComplete
c_func
(paren
id|iucv_ConnectionComplete
op_star
id|eib
comma
r_void
op_star
id|pgm_data
)paren
(brace
r_struct
id|mon_private
op_star
id|monpriv
op_assign
(paren
r_struct
id|mon_private
op_star
)paren
id|pgm_data
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;IUCV connection completed&bslash;n&quot;
)paren
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;IUCV ACCEPT (from *MONITOR): Version = 0x%02X, Event = &quot;
l_string|&quot;0x%02X, Sample = 0x%02X&bslash;n&quot;
comma
id|eib-&gt;ipuser
(braket
l_int|0
)braket
comma
id|eib-&gt;ipuser
(braket
l_int|1
)braket
comma
id|eib-&gt;ipuser
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|monpriv-&gt;iucv_connected
comma
l_int|1
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|mon_conn_wait_queue
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|mon_iucv_ConnectionSevered
id|mon_iucv_ConnectionSevered
c_func
(paren
id|iucv_ConnectionSevered
op_star
id|eib
comma
r_void
op_star
id|pgm_data
)paren
(brace
r_struct
id|mon_private
op_star
id|monpriv
op_assign
(paren
r_struct
id|mon_private
op_star
)paren
id|pgm_data
suffix:semicolon
id|P_ERROR
c_func
(paren
l_string|&quot;IUCV connection severed with rc = 0x%X&bslash;n&quot;
comma
(paren
id|u8
)paren
id|eib-&gt;ipuser
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|monpriv-&gt;iucv_severed
comma
l_int|1
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|mon_conn_wait_queue
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|mon_read_wait_queue
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|mon_iucv_MessagePending
id|mon_iucv_MessagePending
c_func
(paren
id|iucv_MessagePending
op_star
id|eib
comma
r_void
op_star
id|pgm_data
)paren
(brace
r_struct
id|mon_private
op_star
id|monpriv
op_assign
(paren
r_struct
id|mon_private
op_star
)paren
id|pgm_data
suffix:semicolon
id|P_DEBUG
c_func
(paren
l_string|&quot;IUCV message pending&bslash;n&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|monpriv-&gt;msg_array
(braket
id|monpriv-&gt;write_index
)braket
op_member_access_from_pointer
id|local_eib
comma
id|eib
comma
r_sizeof
(paren
id|iucv_MessagePending
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_inc_return
c_func
(paren
op_amp
id|monpriv-&gt;msglim_count
)paren
op_eq
id|MON_MSGLIM
)paren
(brace
id|P_WARNING
c_func
(paren
l_string|&quot;IUCV message pending, message limit (%i) reached&bslash;n&quot;
comma
id|MON_MSGLIM
)paren
suffix:semicolon
id|monpriv-&gt;msg_array
(braket
id|monpriv-&gt;write_index
)braket
op_member_access_from_pointer
id|msglim_reached
op_assign
l_int|1
suffix:semicolon
)brace
id|monpriv-&gt;write_index
op_assign
(paren
id|monpriv-&gt;write_index
op_plus
l_int|1
)paren
op_mod
id|MON_MSGLIM
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|monpriv-&gt;read_ready
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|mon_read_wait_queue
)paren
suffix:semicolon
)brace
DECL|variable|mon_iucvops
r_static
id|iucv_interrupt_ops_t
id|mon_iucvops
op_assign
(brace
dot
id|ConnectionComplete
op_assign
id|mon_iucv_ConnectionComplete
comma
dot
id|ConnectionSevered
op_assign
id|mon_iucv_ConnectionSevered
comma
dot
id|MessagePending
op_assign
id|mon_iucv_MessagePending
comma
)brace
suffix:semicolon
multiline_comment|/******************************************************************************&n; *                               file operations                              *&n; *****************************************************************************/
r_static
r_int
DECL|function|mon_open
id|mon_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|rc
comma
id|i
suffix:semicolon
r_struct
id|mon_private
op_star
id|monpriv
suffix:semicolon
multiline_comment|/*&n;&t; * only one user allowed&n;&t; */
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|MON_IN_USE
comma
op_amp
id|mon_in_use
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|monpriv
op_assign
id|mon_alloc_mem
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|monpriv
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/*&n;&t; * Register with IUCV and connect to *MONITOR service&n;&t; */
id|monpriv-&gt;iucv_handle
op_assign
id|iucv_register_program
c_func
(paren
l_string|&quot;my_monreader    &quot;
comma
id|MON_SERVICE
comma
l_int|NULL
comma
op_amp
id|mon_iucvops
comma
id|monpriv
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|monpriv-&gt;iucv_handle
)paren
(brace
id|P_ERROR
c_func
(paren
l_string|&quot;failed to register with iucv driver&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_error
suffix:semicolon
)brace
id|P_INFO
c_func
(paren
l_string|&quot;open, registered with IUCV&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
id|iucv_connect
c_func
(paren
op_amp
id|monpriv-&gt;pathid
comma
id|MON_MSGLIM
comma
id|user_data_connect
comma
id|MON_SERVICE
comma
id|iucv_host
comma
id|IPRMDATA
comma
l_int|NULL
comma
l_int|NULL
comma
id|monpriv-&gt;iucv_handle
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|P_ERROR
c_func
(paren
l_string|&quot;iucv connection to *MONITOR failed with &quot;
l_string|&quot;IPUSER SEVER code = %i&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_unregister
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Wait for connection confirmation&n;&t; */
id|wait_event
c_func
(paren
id|mon_conn_wait_queue
comma
id|atomic_read
c_func
(paren
op_amp
id|monpriv-&gt;iucv_connected
)paren
op_logical_or
id|atomic_read
c_func
(paren
op_amp
id|monpriv-&gt;iucv_severed
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|monpriv-&gt;iucv_severed
)paren
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|monpriv-&gt;iucv_severed
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|monpriv-&gt;iucv_connected
comma
l_int|0
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_unregister
suffix:semicolon
)brace
id|P_INFO
c_func
(paren
l_string|&quot;open, established connection to *MONITOR service&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|monpriv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_unregister
suffix:colon
id|iucv_unregister_program
c_func
(paren
id|monpriv-&gt;iucv_handle
)paren
suffix:semicolon
id|out_error
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
id|MON_MSGLIM
suffix:semicolon
id|i
op_increment
)paren
id|kfree
c_func
(paren
id|monpriv-&gt;msg_array
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|monpriv
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|MON_IN_USE
comma
op_amp
id|mon_in_use
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_int
DECL|function|mon_close
id|mon_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|rc
comma
id|i
suffix:semicolon
r_struct
id|mon_private
op_star
id|monpriv
op_assign
id|filp-&gt;private_data
suffix:semicolon
multiline_comment|/*&n;&t; * Close IUCV connection and unregister&n;&t; */
id|rc
op_assign
id|iucv_sever
c_func
(paren
id|monpriv-&gt;pathid
comma
id|user_data_sever
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|P_ERROR
c_func
(paren
l_string|&quot;close, iucv_sever failed with rc = %i&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_else
id|P_INFO
c_func
(paren
l_string|&quot;close, terminated connection to *MONITOR service&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
id|iucv_unregister_program
c_func
(paren
id|monpriv-&gt;iucv_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|P_ERROR
c_func
(paren
l_string|&quot;close, iucv_unregister failed with rc = %i&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_else
id|P_INFO
c_func
(paren
l_string|&quot;close, unregistered with IUCV&bslash;n&quot;
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|monpriv-&gt;iucv_severed
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|monpriv-&gt;iucv_connected
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|monpriv-&gt;read_ready
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|monpriv-&gt;msglim_count
comma
l_int|0
)paren
suffix:semicolon
id|monpriv-&gt;write_index
op_assign
l_int|0
suffix:semicolon
id|monpriv-&gt;read_index
op_assign
l_int|0
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
id|MON_MSGLIM
suffix:semicolon
id|i
op_increment
)paren
id|kfree
c_func
(paren
id|monpriv-&gt;msg_array
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|monpriv
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|MON_IN_USE
comma
op_amp
id|mon_in_use
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|mon_read
id|mon_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
id|__user
op_star
id|data
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|mon_private
op_star
id|monpriv
op_assign
id|filp-&gt;private_data
suffix:semicolon
r_struct
id|mon_msg
op_star
id|monmsg
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|monmsg
op_assign
id|mon_next_message
c_func
(paren
id|monpriv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|monmsg
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|monmsg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|monmsg
)paren
(brace
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|ret
op_assign
id|wait_event_interruptible
c_func
(paren
id|mon_read_wait_queue
comma
id|atomic_read
c_func
(paren
op_amp
id|monpriv-&gt;read_ready
)paren
op_logical_or
id|atomic_read
c_func
(paren
op_amp
id|monpriv-&gt;iucv_severed
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|monpriv-&gt;iucv_severed
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|monmsg
op_assign
id|monpriv-&gt;msg_array
(braket
id|monpriv-&gt;read_index
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|monmsg-&gt;pos
)paren
(brace
id|monmsg-&gt;pos
op_assign
id|mon_rec_start
c_func
(paren
id|monmsg
)paren
suffix:semicolon
id|mon_read_debug
c_func
(paren
id|monmsg
comma
id|monpriv
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mon_check_mca
c_func
(paren
id|monmsg
)paren
)paren
r_goto
id|reply
suffix:semicolon
r_if
c_cond
(paren
id|mon_rec_end
c_func
(paren
id|monmsg
)paren
OG
id|monmsg-&gt;pos
)paren
(brace
id|count
op_assign
id|min
c_func
(paren
id|count
comma
(paren
r_int
)paren
id|mon_rec_end
c_func
(paren
id|monmsg
)paren
op_minus
id|monmsg-&gt;pos
op_plus
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
id|copy_to_user
c_func
(paren
id|data
comma
(paren
r_void
op_star
)paren
(paren
r_int
r_int
)paren
id|monmsg-&gt;pos
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|monmsg-&gt;pos
op_add_assign
id|count
suffix:semicolon
op_star
id|ppos
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|mon_rec_end
c_func
(paren
id|monmsg
)paren
op_eq
id|monmsg-&gt;pos
)paren
id|mon_next_mca
c_func
(paren
id|monmsg
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
id|reply
suffix:colon
id|ret
op_assign
id|mon_send_reply
c_func
(paren
id|monmsg
comma
id|monpriv
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|mon_poll
id|mon_poll
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|poll_table_struct
op_star
id|p
)paren
(brace
r_struct
id|mon_private
op_star
id|monpriv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|poll_wait
c_func
(paren
id|filp
comma
op_amp
id|mon_read_wait_queue
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|monpriv-&gt;iucv_severed
)paren
)paren
)paren
r_return
id|POLLERR
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|monpriv-&gt;read_ready
)paren
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mon_fops
r_static
r_struct
id|file_operations
id|mon_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
op_amp
id|mon_open
comma
dot
id|release
op_assign
op_amp
id|mon_close
comma
dot
id|read
op_assign
op_amp
id|mon_read
comma
dot
id|poll
op_assign
op_amp
id|mon_poll
comma
)brace
suffix:semicolon
DECL|variable|mon_dev
r_static
r_struct
id|miscdevice
id|mon_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;monreader&quot;
comma
dot
id|devfs_name
op_assign
l_string|&quot;monreader&quot;
comma
dot
id|fops
op_assign
op_amp
id|mon_fops
comma
dot
id|minor
op_assign
id|MISC_DYNAMIC_MINOR
comma
)brace
suffix:semicolon
multiline_comment|/******************************************************************************&n; *                              module init/exit                              *&n; *****************************************************************************/
r_static
r_int
id|__init
DECL|function|mon_init
id|mon_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_IS_VM
)paren
(brace
id|P_ERROR
c_func
(paren
l_string|&quot;not running under z/VM, driver not loaded&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|rc
op_assign
id|segment_type
c_func
(paren
id|mon_dcss_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|mon_segment_warn
c_func
(paren
id|rc
comma
id|mon_dcss_name
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rc
op_ne
id|SEG_TYPE_SC
)paren
(brace
id|P_ERROR
c_func
(paren
l_string|&quot;segment %s has unsupported type, should be SC&bslash;n&quot;
comma
id|mon_dcss_name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|rc
op_assign
id|segment_load
c_func
(paren
id|mon_dcss_name
comma
id|SEGMENT_SHARED
comma
op_amp
id|mon_dcss_start
comma
op_amp
id|mon_dcss_end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|mon_segment_warn
c_func
(paren
id|rc
comma
id|mon_dcss_name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dcss_mkname
c_func
(paren
id|mon_dcss_name
comma
op_amp
id|user_data_connect
(braket
l_int|8
)braket
)paren
suffix:semicolon
id|rc
op_assign
id|misc_register
c_func
(paren
op_amp
id|mon_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|P_ERROR
c_func
(paren
l_string|&quot;misc_register failed, rc = %i&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|P_INFO
c_func
(paren
l_string|&quot;Loaded segment %s from %p to %p, size = %lu Byte&bslash;n&quot;
comma
id|mon_dcss_name
comma
(paren
r_void
op_star
)paren
id|mon_dcss_start
comma
(paren
r_void
op_star
)paren
id|mon_dcss_end
comma
id|mon_dcss_end
op_minus
id|mon_dcss_start
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|segment_unload
c_func
(paren
id|mon_dcss_name
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|mon_exit
id|mon_exit
c_func
(paren
r_void
)paren
(brace
id|segment_unload
c_func
(paren
id|mon_dcss_name
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
id|misc_deregister
c_func
(paren
op_amp
id|mon_dev
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|mon_init
id|module_init
c_func
(paren
id|mon_init
)paren
suffix:semicolon
DECL|variable|mon_exit
id|module_exit
c_func
(paren
id|mon_exit
)paren
suffix:semicolon
id|module_param_string
c_func
(paren
id|mondcss
comma
id|mon_dcss_name
comma
l_int|9
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mondcss
comma
l_string|&quot;Name of DCSS segment to be used for *MONITOR &quot;
l_string|&quot;service, max. 8 chars. Default is MONDCSS&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Gerald Schaefer &lt;geraldsc@de.ibm.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Character device driver for reading z/VM &quot;
l_string|&quot;monitor service records.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
