multiline_comment|/*&n; * Copyright (C) 2001 Jens Axboe &lt;axboe@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public Licens&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/times.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
multiline_comment|/* Command group 3 is reserved and should never be used.  */
DECL|variable|scsi_command_size
r_const
r_int
r_char
id|scsi_command_size
(braket
l_int|8
)braket
op_assign
(brace
l_int|6
comma
l_int|10
comma
l_int|10
comma
l_int|12
comma
l_int|16
comma
l_int|12
comma
l_int|10
comma
l_int|10
)brace
suffix:semicolon
DECL|macro|BLK_DEFAULT_TIMEOUT
mdefine_line|#define BLK_DEFAULT_TIMEOUT&t;(60 * HZ)
multiline_comment|/* defined in ../scsi/scsi.h  ... should it be included? */
macro_line|#ifndef SCSI_SENSE_BUFFERSIZE
DECL|macro|SCSI_SENSE_BUFFERSIZE
mdefine_line|#define SCSI_SENSE_BUFFERSIZE 64
macro_line|#endif
DECL|function|blk_do_rq
r_static
r_int
id|blk_do_rq
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|block_device
op_star
id|bdev
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
r_char
id|sense
(braket
id|SCSI_SENSE_BUFFERSIZE
)braket
suffix:semicolon
id|DECLARE_COMPLETION
c_func
(paren
id|wait
)paren
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|rq-&gt;rq_disk
op_assign
id|bdev-&gt;bd_disk
suffix:semicolon
multiline_comment|/*&n;&t; * we need an extra reference to the request, so we can look at&n;&t; * it after io completion&n;&t; */
id|rq-&gt;ref_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rq-&gt;sense
)paren
(brace
id|memset
c_func
(paren
id|sense
comma
l_int|0
comma
r_sizeof
(paren
id|sense
)paren
)paren
suffix:semicolon
id|rq-&gt;sense
op_assign
id|sense
suffix:semicolon
id|rq-&gt;sense_len
op_assign
l_int|0
suffix:semicolon
)brace
id|rq-&gt;flags
op_or_assign
id|REQ_NOMERGE
suffix:semicolon
id|rq-&gt;waiting
op_assign
op_amp
id|wait
suffix:semicolon
id|elv_add_request
c_func
(paren
id|q
comma
id|rq
comma
id|ELEVATOR_INSERT_BACK
comma
l_int|1
)paren
suffix:semicolon
id|generic_unplug_device
c_func
(paren
id|q
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;errors
)paren
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#include &lt;scsi/sg.h&gt;
DECL|function|sg_get_version
r_static
r_int
id|sg_get_version
c_func
(paren
r_int
op_star
id|p
)paren
(brace
r_static
r_int
id|sg_version_num
op_assign
l_int|30527
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|sg_version_num
comma
id|p
)paren
suffix:semicolon
)brace
DECL|function|scsi_get_idlun
r_static
r_int
id|scsi_get_idlun
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_int
op_star
id|p
)paren
(brace
r_return
id|put_user
c_func
(paren
l_int|0
comma
id|p
)paren
suffix:semicolon
)brace
DECL|function|scsi_get_bus
r_static
r_int
id|scsi_get_bus
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_int
op_star
id|p
)paren
(brace
r_return
id|put_user
c_func
(paren
l_int|0
comma
id|p
)paren
suffix:semicolon
)brace
DECL|function|sg_get_timeout
r_static
r_int
id|sg_get_timeout
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_return
id|q-&gt;sg_timeout
op_div
(paren
id|HZ
op_div
id|USER_HZ
)paren
suffix:semicolon
)brace
DECL|function|sg_set_timeout
r_static
r_int
id|sg_set_timeout
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_int
op_star
id|p
)paren
(brace
r_int
id|timeout
comma
id|err
op_assign
id|get_user
c_func
(paren
id|timeout
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|q-&gt;sg_timeout
op_assign
id|timeout
op_star
(paren
id|HZ
op_div
id|USER_HZ
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|sg_get_reserved_size
r_static
r_int
id|sg_get_reserved_size
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_int
op_star
id|p
)paren
(brace
r_return
id|put_user
c_func
(paren
id|q-&gt;sg_reserved_size
comma
id|p
)paren
suffix:semicolon
)brace
DECL|function|sg_set_reserved_size
r_static
r_int
id|sg_set_reserved_size
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_int
op_star
id|p
)paren
(brace
r_int
id|size
comma
id|err
op_assign
id|get_user
c_func
(paren
id|size
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
(paren
id|q-&gt;max_sectors
op_lshift
l_int|9
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|q-&gt;sg_reserved_size
op_assign
id|size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * will always return that we are ATAPI even for a real SCSI drive, I&squot;m not&n; * so sure this is worth doing anything about (why would you care??)&n; */
DECL|function|sg_emulated_host
r_static
r_int
id|sg_emulated_host
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_int
op_star
id|p
)paren
(brace
r_return
id|put_user
c_func
(paren
l_int|1
comma
id|p
)paren
suffix:semicolon
)brace
DECL|function|sg_io
r_static
r_int
id|sg_io
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|block_device
op_star
id|bdev
comma
r_struct
id|sg_io_hdr
op_star
id|hdr
)paren
(brace
r_int
r_int
id|start_time
suffix:semicolon
r_int
id|reading
comma
id|writing
suffix:semicolon
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_struct
id|bio
op_star
id|bio
suffix:semicolon
r_char
id|sense
(braket
id|SCSI_SENSE_BUFFERSIZE
)braket
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;interface_id
op_ne
l_char|&squot;S&squot;
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;cmd_len
OG
r_sizeof
(paren
id|rq-&gt;cmd
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * we&squot;ll do that later&n;&t; */
r_if
c_cond
(paren
id|hdr-&gt;iovec_count
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;dxfer_len
OG
(paren
id|q-&gt;max_sectors
op_lshift
l_int|9
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|reading
op_assign
id|writing
op_assign
l_int|0
suffix:semicolon
id|buffer
op_assign
l_int|NULL
suffix:semicolon
id|bio
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;dxfer_len
)paren
(brace
r_int
r_int
id|bytes
op_assign
(paren
id|hdr-&gt;dxfer_len
op_plus
l_int|511
)paren
op_amp
op_complement
l_int|511
suffix:semicolon
r_switch
c_cond
(paren
id|hdr-&gt;dxfer_direction
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|SG_DXFER_TO_FROM_DEV
suffix:colon
id|reading
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|SG_DXFER_TO_DEV
suffix:colon
id|writing
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SG_DXFER_FROM_DEV
suffix:colon
id|reading
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * first try to map it into a bio. reading from device will&n;&t;&t; * be a write to vm.&n;&t;&t; */
id|bio
op_assign
id|bio_map_user
c_func
(paren
id|bdev
comma
(paren
r_int
r_int
)paren
id|hdr-&gt;dxferp
comma
id|hdr-&gt;dxfer_len
comma
id|reading
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * if bio setup failed, fall back to slow approach&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|bio
)paren
(brace
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|bytes
comma
id|q-&gt;bounce_gfp
op_or
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|writing
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buffer
comma
id|hdr-&gt;dxferp
comma
id|hdr-&gt;dxfer_len
)paren
)paren
r_goto
id|out_buffer
suffix:semicolon
)brace
r_else
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
id|hdr-&gt;dxfer_len
)paren
suffix:semicolon
)brace
)brace
id|rq
op_assign
id|blk_get_request
c_func
(paren
id|q
comma
id|writing
ques
c_cond
id|WRITE
suffix:colon
id|READ
comma
id|__GFP_WAIT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * fill in request structure&n;&t; */
id|rq-&gt;cmd_len
op_assign
id|hdr-&gt;cmd_len
suffix:semicolon
id|memcpy
c_func
(paren
id|rq-&gt;cmd
comma
id|hdr-&gt;cmdp
comma
id|hdr-&gt;cmd_len
)paren
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|rq-&gt;cmd
)paren
op_ne
id|hdr-&gt;cmd_len
)paren
id|memset
c_func
(paren
id|rq-&gt;cmd
op_plus
id|hdr-&gt;cmd_len
comma
l_int|0
comma
r_sizeof
(paren
id|rq-&gt;cmd
)paren
op_minus
id|hdr-&gt;cmd_len
)paren
suffix:semicolon
id|memset
c_func
(paren
id|sense
comma
l_int|0
comma
r_sizeof
(paren
id|sense
)paren
)paren
suffix:semicolon
id|rq-&gt;sense
op_assign
id|sense
suffix:semicolon
id|rq-&gt;sense_len
op_assign
l_int|0
suffix:semicolon
id|rq-&gt;flags
op_or_assign
id|REQ_BLOCK_PC
suffix:semicolon
id|rq-&gt;bio
op_assign
id|rq-&gt;biotail
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|bio
)paren
id|blk_rq_bio_prep
c_func
(paren
id|q
comma
id|rq
comma
id|bio
)paren
suffix:semicolon
id|rq-&gt;data
op_assign
id|buffer
suffix:semicolon
id|rq-&gt;data_len
op_assign
id|hdr-&gt;dxfer_len
suffix:semicolon
id|rq-&gt;timeout
op_assign
(paren
id|hdr-&gt;timeout
op_star
id|HZ
)paren
op_div
l_int|1000
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rq-&gt;timeout
)paren
id|rq-&gt;timeout
op_assign
id|q-&gt;sg_timeout
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rq-&gt;timeout
)paren
id|rq-&gt;timeout
op_assign
id|BLK_DEFAULT_TIMEOUT
suffix:semicolon
id|start_time
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* ignore return value. All information is passed back to caller&n;&t; * (if he doesn&squot;t check that is his problem).&n;&t; * N.B. a non-zero SCSI status is _not_ necessarily an error.&n;&t; */
id|blk_do_rq
c_func
(paren
id|q
comma
id|bdev
comma
id|rq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bio
)paren
id|bio_unmap_user
c_func
(paren
id|bio
comma
id|reading
)paren
suffix:semicolon
multiline_comment|/* write to all output members */
id|hdr-&gt;status
op_assign
id|rq-&gt;errors
suffix:semicolon
id|hdr-&gt;masked_status
op_assign
(paren
id|hdr-&gt;status
op_rshift
l_int|1
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|hdr-&gt;msg_status
op_assign
l_int|0
suffix:semicolon
id|hdr-&gt;host_status
op_assign
l_int|0
suffix:semicolon
id|hdr-&gt;driver_status
op_assign
l_int|0
suffix:semicolon
id|hdr-&gt;info
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;masked_status
op_logical_or
id|hdr-&gt;host_status
op_logical_or
id|hdr-&gt;driver_status
)paren
id|hdr-&gt;info
op_or_assign
id|SG_INFO_CHECK
suffix:semicolon
id|hdr-&gt;resid
op_assign
id|rq-&gt;data_len
suffix:semicolon
id|hdr-&gt;duration
op_assign
(paren
(paren
id|jiffies
op_minus
id|start_time
)paren
op_star
l_int|1000
)paren
op_div
id|HZ
suffix:semicolon
id|hdr-&gt;sb_len_wr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;sense_len
op_logical_and
id|hdr-&gt;sbp
)paren
(brace
r_int
id|len
op_assign
id|min
c_func
(paren
(paren
r_int
r_int
)paren
id|hdr-&gt;mx_sb_len
comma
id|rq-&gt;sense_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|copy_to_user
c_func
(paren
id|hdr-&gt;sbp
comma
id|rq-&gt;sense
comma
id|len
)paren
)paren
id|hdr-&gt;sb_len_wr
op_assign
id|len
suffix:semicolon
)brace
id|blk_put_request
c_func
(paren
id|rq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|reading
)paren
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|hdr-&gt;dxferp
comma
id|buffer
comma
id|hdr-&gt;dxfer_len
)paren
)paren
r_goto
id|out_buffer
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
multiline_comment|/* may not have succeeded, but output values written to control&n;&t; * structure (struct sg_io_hdr).  */
r_return
l_int|0
suffix:semicolon
id|out_buffer
suffix:colon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
DECL|macro|FORMAT_UNIT_TIMEOUT
mdefine_line|#define FORMAT_UNIT_TIMEOUT&t;&t;(2 * 60 * 60 * HZ)
DECL|macro|START_STOP_TIMEOUT
mdefine_line|#define START_STOP_TIMEOUT&t;&t;(60 * HZ)
DECL|macro|MOVE_MEDIUM_TIMEOUT
mdefine_line|#define MOVE_MEDIUM_TIMEOUT&t;&t;(5 * 60 * HZ)
DECL|macro|READ_ELEMENT_STATUS_TIMEOUT
mdefine_line|#define READ_ELEMENT_STATUS_TIMEOUT&t;(5 * 60 * HZ)
DECL|macro|READ_DEFECT_DATA_TIMEOUT
mdefine_line|#define READ_DEFECT_DATA_TIMEOUT&t;(60 * HZ )
DECL|macro|OMAX_SB_LEN
mdefine_line|#define OMAX_SB_LEN 16          /* For backward compatibility */
DECL|function|sg_scsi_ioctl
r_static
r_int
id|sg_scsi_ioctl
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|Scsi_Ioctl_Command
op_star
id|sic
)paren
(brace
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_int
id|err
comma
id|in_len
comma
id|out_len
comma
id|bytes
comma
id|opcode
comma
id|cmdlen
suffix:semicolon
r_char
op_star
id|buffer
op_assign
l_int|NULL
comma
id|sense
(braket
id|SCSI_SENSE_BUFFERSIZE
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * get in an out lengths, verify they don&squot;t exceed a page worth of data&n;&t; */
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|in_len
comma
op_amp
id|sic-&gt;inlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|out_len
comma
op_amp
id|sic-&gt;outlen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|in_len
OG
id|PAGE_SIZE
op_logical_or
id|out_len
OG
id|PAGE_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|opcode
comma
id|sic-&gt;data
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|bytes
op_assign
id|max
c_func
(paren
id|in_len
comma
id|out_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bytes
)paren
(brace
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|bytes
comma
id|q-&gt;bounce_gfp
op_or
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
id|bytes
)paren
suffix:semicolon
)brace
id|rq
op_assign
id|blk_get_request
c_func
(paren
id|q
comma
id|in_len
ques
c_cond
id|WRITE
suffix:colon
id|READ
comma
id|__GFP_WAIT
)paren
suffix:semicolon
id|cmdlen
op_assign
id|COMMAND_SIZE
c_func
(paren
id|opcode
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * get command and data to send to device, if any&n;&t; */
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|rq-&gt;cmd_len
op_assign
id|cmdlen
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|rq-&gt;cmd
comma
id|sic-&gt;data
comma
id|cmdlen
)paren
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buffer
comma
id|sic-&gt;data
op_plus
id|cmdlen
comma
id|in_len
)paren
)paren
r_goto
id|error
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|SEND_DIAGNOSTIC
suffix:colon
r_case
id|FORMAT_UNIT
suffix:colon
id|rq-&gt;timeout
op_assign
id|FORMAT_UNIT_TIMEOUT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|START_STOP
suffix:colon
id|rq-&gt;timeout
op_assign
id|START_STOP_TIMEOUT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MOVE_MEDIUM
suffix:colon
id|rq-&gt;timeout
op_assign
id|MOVE_MEDIUM_TIMEOUT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_ELEMENT_STATUS
suffix:colon
id|rq-&gt;timeout
op_assign
id|READ_ELEMENT_STATUS_TIMEOUT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_DEFECT_DATA
suffix:colon
id|rq-&gt;timeout
op_assign
id|READ_DEFECT_DATA_TIMEOUT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|rq-&gt;timeout
op_assign
id|BLK_DEFAULT_TIMEOUT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sense
comma
l_int|0
comma
r_sizeof
(paren
id|sense
)paren
)paren
suffix:semicolon
id|rq-&gt;sense
op_assign
id|sense
suffix:semicolon
id|rq-&gt;sense_len
op_assign
l_int|0
suffix:semicolon
id|rq-&gt;data
op_assign
id|buffer
suffix:semicolon
id|rq-&gt;data_len
op_assign
id|bytes
suffix:semicolon
id|rq-&gt;flags
op_or_assign
id|REQ_BLOCK_PC
suffix:semicolon
id|blk_do_rq
c_func
(paren
id|q
comma
id|bdev
comma
id|rq
)paren
suffix:semicolon
id|err
op_assign
id|rq-&gt;errors
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* only 8 bit SCSI status */
r_if
c_cond
(paren
id|err
)paren
(brace
r_if
c_cond
(paren
id|rq-&gt;sense_len
op_logical_and
id|rq-&gt;sense
)paren
(brace
id|bytes
op_assign
(paren
id|OMAX_SB_LEN
OG
id|rq-&gt;sense_len
)paren
ques
c_cond
id|rq-&gt;sense_len
suffix:colon
id|OMAX_SB_LEN
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|sic-&gt;data
comma
id|rq-&gt;sense
comma
id|bytes
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|sic-&gt;data
comma
id|buffer
comma
id|out_len
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
id|error
suffix:colon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|blk_put_request
c_func
(paren
id|rq
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|scsi_cmd_ioctl
r_int
id|scsi_cmd_ioctl
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|request_queue_t
op_star
id|q
suffix:semicolon
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_int
id|close
op_assign
l_int|0
comma
id|err
suffix:semicolon
id|q
op_assign
id|bdev_get_queue
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|blk_get_queue
c_func
(paren
id|q
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/*&n;&t;&t; * new sgv3 interface&n;&t;&t; */
r_case
id|SG_GET_VERSION_NUM
suffix:colon
id|err
op_assign
id|sg_get_version
c_func
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSI_IOCTL_GET_IDLUN
suffix:colon
id|err
op_assign
id|scsi_get_idlun
c_func
(paren
id|q
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSI_IOCTL_GET_BUS_NUMBER
suffix:colon
id|err
op_assign
id|scsi_get_bus
c_func
(paren
id|q
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SG_SET_TIMEOUT
suffix:colon
id|err
op_assign
id|sg_set_timeout
c_func
(paren
id|q
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SG_GET_TIMEOUT
suffix:colon
id|err
op_assign
id|sg_get_timeout
c_func
(paren
id|q
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SG_GET_RESERVED_SIZE
suffix:colon
id|err
op_assign
id|sg_get_reserved_size
c_func
(paren
id|q
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SG_SET_RESERVED_SIZE
suffix:colon
id|err
op_assign
id|sg_set_reserved_size
c_func
(paren
id|q
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SG_EMULATED_HOST
suffix:colon
id|err
op_assign
id|sg_emulated_host
c_func
(paren
id|q
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SG_IO
suffix:colon
(brace
r_struct
id|sg_io_hdr
id|hdr
suffix:semicolon
r_int
r_char
id|cdb
(braket
id|BLK_MAX_CDB
)braket
comma
op_star
id|old_cdb
suffix:semicolon
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|hdr
comma
(paren
r_struct
id|sg_io_hdr
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|hdr
)paren
)paren
)paren
r_break
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|hdr.cmd_len
OG
r_sizeof
(paren
id|rq-&gt;cmd
)paren
)paren
r_break
suffix:semicolon
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|cdb
comma
id|hdr.cmdp
comma
id|hdr.cmd_len
)paren
)paren
r_break
suffix:semicolon
id|old_cdb
op_assign
id|hdr.cmdp
suffix:semicolon
id|hdr.cmdp
op_assign
id|cdb
suffix:semicolon
id|err
op_assign
id|sg_io
c_func
(paren
id|q
comma
id|bdev
comma
op_amp
id|hdr
)paren
suffix:semicolon
id|hdr.cmdp
op_assign
id|old_cdb
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|sg_io_hdr
op_star
)paren
id|arg
comma
op_amp
id|hdr
comma
r_sizeof
(paren
id|hdr
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|CDROM_SEND_PACKET
suffix:colon
(brace
r_struct
id|cdrom_generic_command
id|cgc
suffix:semicolon
r_struct
id|sg_io_hdr
id|hdr
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|cgc
comma
(paren
r_struct
id|cdrom_generic_command
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|cgc
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cgc.timeout
op_assign
id|clock_t_to_jiffies
c_func
(paren
id|cgc.timeout
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hdr
comma
l_int|0
comma
r_sizeof
(paren
id|hdr
)paren
)paren
suffix:semicolon
id|hdr.interface_id
op_assign
l_char|&squot;S&squot;
suffix:semicolon
id|hdr.cmd_len
op_assign
r_sizeof
(paren
id|cgc.cmd
)paren
suffix:semicolon
id|hdr.dxfer_len
op_assign
id|cgc.buflen
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cgc.data_direction
)paren
(brace
r_case
id|CGC_DATA_UNKNOWN
suffix:colon
id|hdr.dxfer_direction
op_assign
id|SG_DXFER_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CGC_DATA_WRITE
suffix:colon
id|hdr.dxfer_direction
op_assign
id|SG_DXFER_TO_DEV
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CGC_DATA_READ
suffix:colon
id|hdr.dxfer_direction
op_assign
id|SG_DXFER_FROM_DEV
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CGC_DATA_NONE
suffix:colon
id|hdr.dxfer_direction
op_assign
id|SG_DXFER_NONE
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
r_break
suffix:semicolon
id|hdr.dxferp
op_assign
id|cgc.buffer
suffix:semicolon
id|hdr.sbp
op_assign
(paren
r_char
op_star
)paren
id|cgc.sense
suffix:semicolon
r_if
c_cond
(paren
id|hdr.sbp
)paren
id|hdr.mx_sb_len
op_assign
r_sizeof
(paren
r_struct
id|request_sense
)paren
suffix:semicolon
id|hdr.timeout
op_assign
id|cgc.timeout
suffix:semicolon
id|hdr.cmdp
op_assign
id|cgc.cmd
suffix:semicolon
id|hdr.cmd_len
op_assign
r_sizeof
(paren
id|cgc.cmd
)paren
suffix:semicolon
id|err
op_assign
id|sg_io
c_func
(paren
id|q
comma
id|bdev
comma
op_amp
id|hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr.status
)paren
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
id|cgc.stat
op_assign
id|err
suffix:semicolon
id|cgc.buflen
op_assign
id|hdr.resid
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|cdrom_generic_command
op_star
)paren
id|arg
comma
op_amp
id|cgc
comma
r_sizeof
(paren
id|cgc
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * old junk scsi send command ioctl&n;&t;&t; */
r_case
id|SCSI_IOCTL_SEND_COMMAND
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_break
suffix:semicolon
id|err
op_assign
id|sg_scsi_ioctl
c_func
(paren
id|q
comma
id|bdev
comma
(paren
id|Scsi_Ioctl_Command
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CDROMCLOSETRAY
suffix:colon
id|close
op_assign
l_int|1
suffix:semicolon
r_case
id|CDROMEJECT
suffix:colon
id|rq
op_assign
id|blk_get_request
c_func
(paren
id|q
comma
id|WRITE
comma
id|__GFP_WAIT
)paren
suffix:semicolon
id|rq-&gt;flags
op_or_assign
id|REQ_BLOCK_PC
suffix:semicolon
id|rq-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|rq-&gt;data_len
op_assign
l_int|0
suffix:semicolon
id|rq-&gt;timeout
op_assign
id|BLK_DEFAULT_TIMEOUT
suffix:semicolon
id|memset
c_func
(paren
id|rq-&gt;cmd
comma
l_int|0
comma
r_sizeof
(paren
id|rq-&gt;cmd
)paren
)paren
suffix:semicolon
id|rq-&gt;cmd
(braket
l_int|0
)braket
op_assign
id|GPCMD_START_STOP_UNIT
suffix:semicolon
id|rq-&gt;cmd
(braket
l_int|4
)braket
op_assign
l_int|0x02
op_plus
(paren
id|close
op_ne
l_int|0
)paren
suffix:semicolon
id|rq-&gt;cmd_len
op_assign
l_int|6
suffix:semicolon
id|err
op_assign
id|blk_do_rq
c_func
(paren
id|q
comma
id|bdev
comma
id|rq
)paren
suffix:semicolon
id|blk_put_request
c_func
(paren
id|rq
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|ENOTTY
suffix:semicolon
)brace
id|blk_put_queue
c_func
(paren
id|q
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|scsi_cmd_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_cmd_ioctl
)paren
suffix:semicolon
DECL|variable|scsi_command_size
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_command_size
)paren
suffix:semicolon
eof
