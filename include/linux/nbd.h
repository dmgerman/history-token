multiline_comment|/*&n; * 1999 Copyright (C) Pavel Machek, pavel@ucw.cz. This code is GPL.&n; * 1999/11/04 Copyright (C) 1999 VMware, Inc. (Regis &quot;HPReg&quot; Duchesne)&n; *            Made nbd_end_request() use the io_request_lock&n; */
macro_line|#ifndef LINUX_NBD_H
DECL|macro|LINUX_NBD_H
mdefine_line|#define LINUX_NBD_H
DECL|macro|NBD_SET_SOCK
mdefine_line|#define NBD_SET_SOCK&t;_IO( 0xab, 0 )
DECL|macro|NBD_SET_BLKSIZE
mdefine_line|#define NBD_SET_BLKSIZE&t;_IO( 0xab, 1 )
DECL|macro|NBD_SET_SIZE
mdefine_line|#define NBD_SET_SIZE&t;_IO( 0xab, 2 )
DECL|macro|NBD_DO_IT
mdefine_line|#define NBD_DO_IT&t;_IO( 0xab, 3 )
DECL|macro|NBD_CLEAR_SOCK
mdefine_line|#define NBD_CLEAR_SOCK&t;_IO( 0xab, 4 )
DECL|macro|NBD_CLEAR_QUE
mdefine_line|#define NBD_CLEAR_QUE&t;_IO( 0xab, 5 )
DECL|macro|NBD_PRINT_DEBUG
mdefine_line|#define NBD_PRINT_DEBUG&t;_IO( 0xab, 6 )
DECL|macro|NBD_SET_SIZE_BLOCKS
mdefine_line|#define NBD_SET_SIZE_BLOCKS&t;_IO( 0xab, 7 )
DECL|macro|NBD_DISCONNECT
mdefine_line|#define NBD_DISCONNECT  _IO( 0xab, 8 )
macro_line|#ifdef MAJOR_NR
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|macro|LOCAL_END_REQUEST
mdefine_line|#define LOCAL_END_REQUEST
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#ifdef PARANOIA
r_extern
r_int
id|requests_in
suffix:semicolon
r_extern
r_int
id|requests_out
suffix:semicolon
macro_line|#endif
r_static
r_int
DECL|function|nbd_end_request
id|nbd_end_request
c_func
(paren
r_struct
id|request
op_star
id|req
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef PARANOIA
id|requests_out
op_increment
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * This is a very dirty hack that we have to do to handle&n;&t; * merged requests because end_request stuff is a bit&n;&t; * broken. The fact we have to do this only if there&n;&t; * aren&squot;t errors looks even more silly.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|req-&gt;errors
)paren
(brace
id|req-&gt;sector
op_add_assign
id|req-&gt;current_nr_sectors
suffix:semicolon
id|req-&gt;nr_sectors
op_sub_assign
id|req-&gt;current_nr_sectors
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|io_request_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end_that_request_first
c_func
(paren
id|req
comma
op_logical_neg
id|req-&gt;errors
comma
l_string|&quot;nbd&quot;
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
id|end_that_request_last
c_func
(paren
id|req
)paren
suffix:semicolon
id|out
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|io_request_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|MAX_NBD
mdefine_line|#define MAX_NBD 128
DECL|struct|nbd_device
r_struct
id|nbd_device
(brace
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|harderror
r_int
id|harderror
suffix:semicolon
multiline_comment|/* Code of hard error&t;&t;&t;*/
DECL|macro|NBD_READ_ONLY
mdefine_line|#define NBD_READ_ONLY 0x0001
DECL|macro|NBD_WRITE_NOCHK
mdefine_line|#define NBD_WRITE_NOCHK 0x0002
DECL|member|sock
r_struct
id|socket
op_star
id|sock
suffix:semicolon
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
multiline_comment|/* If == NULL, device is not ready, yet&t;*/
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* FIXME: not if debugging is off&t;*/
DECL|member|queue_head
r_struct
id|list_head
id|queue_head
suffix:semicolon
multiline_comment|/* Requests are added here...&t;&t;&t;*/
DECL|member|queue_lock
r_struct
id|semaphore
id|queue_lock
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* This now IS in some kind of include file...&t;*/
multiline_comment|/* These are send over network in request/reply magic field */
DECL|macro|NBD_REQUEST_MAGIC
mdefine_line|#define NBD_REQUEST_MAGIC 0x25609513
DECL|macro|NBD_REPLY_MAGIC
mdefine_line|#define NBD_REPLY_MAGIC 0x67446698
multiline_comment|/* Do *not* use magics: 0x12560953 0x96744668. */
multiline_comment|/*&n; * This is packet used for communication between client and&n; * server. All data are in network byte order.&n; */
DECL|struct|nbd_request
r_struct
id|nbd_request
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* == READ || == WRITE &t;*/
DECL|member|handle
r_char
id|handle
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|from
id|u64
id|from
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
)brace
macro_line|#ifdef __GNUC__
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
macro_line|#endif
suffix:semicolon
DECL|struct|nbd_reply
r_struct
id|nbd_reply
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|error
id|u32
id|error
suffix:semicolon
multiline_comment|/* 0 = ok, else error&t;*/
DECL|member|handle
r_char
id|handle
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* handle you got from request&t;*/
)brace
suffix:semicolon
macro_line|#endif
eof
