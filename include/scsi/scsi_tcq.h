macro_line|#ifndef _SCSI_SCSI_TCQ_H
DECL|macro|_SCSI_SCSI_TCQ_H
mdefine_line|#define _SCSI_SCSI_TCQ_H
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
DECL|macro|MSG_SIMPLE_TAG
mdefine_line|#define MSG_SIMPLE_TAG&t;0x20
DECL|macro|MSG_HEAD_TAG
mdefine_line|#define MSG_HEAD_TAG&t;0x21
DECL|macro|MSG_ORDERED_TAG
mdefine_line|#define MSG_ORDERED_TAG&t;0x22
DECL|macro|SCSI_NO_TAG
mdefine_line|#define SCSI_NO_TAG&t;(-1)    /* identify no tag in use */
multiline_comment|/**&n; * scsi_activate_tcq - turn on tag command queueing&n; * @SDpnt:&t;device to turn on TCQ for&n; * @depth:&t;queue depth&n; *&n; * Notes:&n; *&t;Eventually, I hope depth would be the maximum depth&n; *&t;the device could cope with and the real queue depth&n; *&t;would be adjustable from 0 to depth.&n; **/
DECL|function|scsi_activate_tcq
r_static
r_inline
r_void
id|scsi_activate_tcq
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
id|depth
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;tagged_supported
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|blk_queue_tagged
c_func
(paren
id|sdev-&gt;request_queue
)paren
)paren
id|blk_queue_init_tags
c_func
(paren
id|sdev-&gt;request_queue
comma
id|depth
comma
l_int|NULL
)paren
suffix:semicolon
id|scsi_adjust_queue_depth
c_func
(paren
id|sdev
comma
id|MSG_ORDERED_TAG
comma
id|depth
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * scsi_deactivate_tcq - turn off tag command queueing&n; * @SDpnt:&t;device to turn off TCQ for&n; **/
DECL|function|scsi_deactivate_tcq
r_static
r_inline
r_void
id|scsi_deactivate_tcq
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
id|depth
)paren
(brace
r_if
c_cond
(paren
id|blk_queue_tagged
c_func
(paren
id|sdev-&gt;request_queue
)paren
)paren
id|blk_queue_free_tags
c_func
(paren
id|sdev-&gt;request_queue
)paren
suffix:semicolon
id|scsi_adjust_queue_depth
c_func
(paren
id|sdev
comma
l_int|0
comma
id|depth
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_populate_tag_msg - place a tag message in a buffer&n; * @SCpnt:&t;pointer to the Scsi_Cmnd for the tag&n; * @msg:&t;pointer to the area to place the tag&n; *&n; * Notes:&n; *&t;designed to create the correct type of tag message for the &n; *&t;particular request.  Returns the size of the tag message.&n; *&t;May return 0 if TCQ is disabled for this device.&n; **/
DECL|function|scsi_populate_tag_msg
r_static
r_inline
r_int
id|scsi_populate_tag_msg
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_char
op_star
id|msg
)paren
(brace
r_struct
id|request
op_star
id|req
op_assign
id|cmd-&gt;request
suffix:semicolon
r_if
c_cond
(paren
id|blk_rq_tagged
c_func
(paren
id|req
)paren
)paren
(brace
r_if
c_cond
(paren
id|req-&gt;flags
op_amp
id|REQ_HARDBARRIER
)paren
op_star
id|msg
op_increment
op_assign
id|MSG_ORDERED_TAG
suffix:semicolon
r_else
op_star
id|msg
op_increment
op_assign
id|MSG_SIMPLE_TAG
suffix:semicolon
op_star
id|msg
op_increment
op_assign
id|req-&gt;tag
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_find_tag - find a tagged command by device&n; * @SDpnt:&t;pointer to the ScSI device&n; * @tag:&t;the tag number&n; *&n; * Notes:&n; *&t;Only works with tags allocated by the generic blk layer.&n; **/
DECL|function|scsi_find_tag
r_static
r_inline
r_struct
id|scsi_cmnd
op_star
id|scsi_find_tag
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
id|tag
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_if
c_cond
(paren
id|tag
op_ne
id|SCSI_NO_TAG
)paren
(brace
id|req
op_assign
id|blk_queue_find_tag
c_func
(paren
id|sdev-&gt;request_queue
comma
id|tag
)paren
suffix:semicolon
r_return
id|req
ques
c_cond
(paren
r_struct
id|scsi_cmnd
op_star
)paren
id|req-&gt;special
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* single command, look in space */
r_return
id|sdev-&gt;current_cmnd
suffix:semicolon
)brace
macro_line|#endif /* _SCSI_SCSI_TCQ_H */
eof
