multiline_comment|/*&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * Eicon File Revision :    1.12  &n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
DECL|macro|N_DATA
macro_line|#undef N_DATA
macro_line|#include &quot;adapter.h&quot;
macro_line|#include &quot;divas.h&quot;
macro_line|#include &quot;divalog.h&quot;
r_extern
r_int
id|DivasCardNext
suffix:semicolon
r_void
id|UxPause
c_func
(paren
r_int
id|ms
)paren
suffix:semicolon
r_int
id|DivasGetMem
c_func
(paren
id|mem_block_t
op_star
)paren
suffix:semicolon
DECL|macro|DIA_IOCTL_UNLOCK
mdefine_line|#define DIA_IOCTL_UNLOCK 12
r_void
id|UnlockDivas
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|do_ioctl
r_int
id|do_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|pDivasInode
comma
r_struct
id|file
op_star
id|pDivasFile
comma
r_int
r_int
id|command
comma
r_int
r_int
id|arg
)paren
(brace
id|byte
op_star
id|pUserCards
comma
id|card_i
suffix:semicolon
id|word
id|wCardNum
suffix:semicolon
r_switch
c_cond
(paren
id|command
)paren
(brace
r_case
id|DIA_IOCTL_CONFIG
suffix:colon
(brace
id|dia_config_t
id|DivaConfig
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|DivaConfig
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|dia_config_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DivasCardConfig
c_func
(paren
op_amp
id|DivaConfig
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|DIA_IOCTL_DETECT
suffix:colon
id|pUserCards
op_assign
(paren
id|byte
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|pUserCards
comma
l_int|20
)paren
)paren
(brace
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|DivasCardNext
comma
id|pUserCards
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_for
c_loop
(paren
id|card_i
op_assign
l_int|1
suffix:semicolon
id|card_i
OL
l_int|20
suffix:semicolon
id|card_i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|__put_user
c_func
(paren
(paren
id|byte
)paren
id|DivasCards
(braket
id|card_i
op_minus
l_int|1
)braket
dot
id|cfg.card_type
comma
id|pUserCards
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
)brace
r_else
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|DIA_IOCTL_START
suffix:colon
(brace
id|dia_start_t
id|DivaStart
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|DivaStart
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|dia_start_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|DivasCardStart
c_func
(paren
id|DivaStart.card_id
)paren
suffix:semicolon
)brace
r_case
id|DIA_IOCTL_FLAVOUR
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|DIA_IOCTL_LOAD
suffix:colon
(brace
id|dia_load_t
id|DivaLoad
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|DivaLoad
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|dia_load_t
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|DivaLoad.code
comma
id|DivaLoad.length
)paren
)paren
(brace
r_if
c_cond
(paren
id|DivasCardLoad
c_func
(paren
op_amp
id|DivaLoad
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Divas: Error loading DIVA Server adapter&bslash;n&quot;
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
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_case
id|DIA_IOCTL_LOG
suffix:colon
(brace
id|dia_log_t
id|DivaLog
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|DivaLog
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|dia_log_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DivasLog
c_func
(paren
op_amp
id|DivaLog
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|DIA_IOCTL_XLOG_REQ
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|wCardNum
comma
(paren
id|word
op_star
)paren
id|arg
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|DivasXlogReq
c_func
(paren
id|wCardNum
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|DIA_IOCTL_GET_NUM
suffix:colon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|DivasCardNext
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|DIA_IOCTL_GET_LIST
suffix:colon
(brace
id|dia_card_list_t
id|cards
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: DIA_IOCTL_GET_LIST&quot;
)paren
)paren
suffix:semicolon
id|DivasGetList
c_func
(paren
op_amp
id|cards
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|cards
comma
r_sizeof
(paren
id|cards
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|DIA_IOCTL_GET_MEM
suffix:colon
(brace
id|mem_block_t
id|mem_block
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|mem_block
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|mem_block_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DivasGetMem
c_func
(paren
op_amp
id|mem_block
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|DIA_IOCTL_UNLOCK
suffix:colon
id|UnlockDivas
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|do_poll
r_int
r_int
id|do_poll
c_func
(paren
r_struct
id|file
op_star
id|pFile
comma
r_struct
id|poll_table_struct
op_star
id|pPollTable
)paren
(brace
id|word
id|wMask
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DivasLogFifoEmpty
c_func
(paren
)paren
)paren
id|wMask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
id|wMask
suffix:semicolon
)brace
DECL|function|do_read
id|ssize_t
id|do_read
c_func
(paren
r_struct
id|file
op_star
id|pFile
comma
r_char
op_star
id|pUserBuffer
comma
r_int
id|BufferSize
comma
id|loff_t
op_star
id|pOffset
)paren
(brace
id|klog_t
op_star
id|pClientLogBuffer
op_assign
(paren
id|klog_t
op_star
)paren
id|pUserBuffer
suffix:semicolon
id|klog_t
op_star
id|pHeadItem
suffix:semicolon
r_if
c_cond
(paren
id|BufferSize
OL
r_sizeof
(paren
id|klog_t
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Divas: Divalog buffer specifed a size that is too small (%d - %d required)&bslash;n&quot;
comma
id|BufferSize
comma
r_sizeof
(paren
id|klog_t
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|pHeadItem
op_assign
(paren
id|klog_t
op_star
)paren
id|DivasLogFifoRead
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pHeadItem
)paren
(brace
id|memcpy
c_func
(paren
id|pClientLogBuffer
comma
id|pHeadItem
comma
r_sizeof
(paren
id|klog_t
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pHeadItem
)paren
suffix:semicolon
r_return
r_sizeof
(paren
id|klog_t
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|private_usage_count
r_static
r_int
id|private_usage_count
suffix:semicolon
DECL|function|do_open
r_int
id|do_open
c_func
(paren
r_struct
id|inode
op_star
id|pInode
comma
r_struct
id|file
op_star
id|pFile
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#ifdef MODULE
id|private_usage_count
op_increment
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_release
r_int
id|do_release
c_func
(paren
r_struct
id|inode
op_star
id|pInode
comma
r_struct
id|file
op_star
id|pFile
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#ifdef MODULE
id|private_usage_count
op_decrement
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|UnlockDivas
r_void
id|UnlockDivas
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|private_usage_count
OG
l_int|0
)paren
(brace
id|private_usage_count
op_decrement
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
)brace
eof
