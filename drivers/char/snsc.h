multiline_comment|/*&n; * SN Platform system controller communication support&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2004 Silicon Graphics, Inc. All rights reserved.&n; */
multiline_comment|/*&n; * This file contains macros and data types for communication with the&n; * system controllers in SGI SN systems.&n; */
macro_line|#ifndef _SN_SYSCTL_H_
DECL|macro|_SN_SYSCTL_H_
mdefine_line|#define _SN_SYSCTL_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/cdev.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|macro|CHUNKSIZE
mdefine_line|#define CHUNKSIZE 127
multiline_comment|/* This structure is used to track an open subchannel. */
DECL|struct|subch_data_s
r_struct
id|subch_data_s
(brace
DECL|member|sd_nasid
id|nasid_t
id|sd_nasid
suffix:semicolon
multiline_comment|/* node on which the subchannel was opened */
DECL|member|sd_subch
r_int
id|sd_subch
suffix:semicolon
multiline_comment|/* subchannel number */
DECL|member|sd_rlock
id|spinlock_t
id|sd_rlock
suffix:semicolon
multiline_comment|/* monitor lock for rsv */
DECL|member|sd_wlock
id|spinlock_t
id|sd_wlock
suffix:semicolon
multiline_comment|/* monitor lock for wsv */
DECL|member|sd_rq
id|wait_queue_head_t
id|sd_rq
suffix:semicolon
multiline_comment|/* wait queue for readers */
DECL|member|sd_wq
id|wait_queue_head_t
id|sd_wq
suffix:semicolon
multiline_comment|/* wait queue for writers */
DECL|member|sd_rbs
r_struct
id|semaphore
id|sd_rbs
suffix:semicolon
multiline_comment|/* semaphore for read buffer */
DECL|member|sd_wbs
r_struct
id|semaphore
id|sd_wbs
suffix:semicolon
multiline_comment|/* semaphore for write buffer */
DECL|member|sd_rb
r_char
id|sd_rb
(braket
id|CHUNKSIZE
)braket
suffix:semicolon
multiline_comment|/* read buffer */
DECL|member|sd_wb
r_char
id|sd_wb
(braket
id|CHUNKSIZE
)braket
suffix:semicolon
multiline_comment|/* write buffer */
)brace
suffix:semicolon
DECL|struct|sysctl_data_s
r_struct
id|sysctl_data_s
(brace
DECL|member|scd_cdev
r_struct
id|cdev
id|scd_cdev
suffix:semicolon
multiline_comment|/* Character device info */
DECL|member|scd_nasid
id|nasid_t
id|scd_nasid
suffix:semicolon
multiline_comment|/* Node on which subchannels are opened. */
)brace
suffix:semicolon
macro_line|#endif /* _SN_SYSCTL_H_ */
eof
