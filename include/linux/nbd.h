multiline_comment|/*&n; * 1999 Copyright (C) Pavel Machek, pavel@ucw.cz. This code is GPL.&n; * 1999/11/04 Copyright (C) 1999 VMware, Inc. (Regis &quot;HPReg&quot; Duchesne)&n; *            Made nbd_end_request() use the io_request_lock&n; * 2001 Copyright (C) Steven Whitehouse&n; *            New nbd_end_request() for compatibility with new linux block&n; *            layer code.&n; * 2003/06/24 Louis D. Langholtz &lt;ldl@aros.net&gt;&n; *            Removed unneeded blksize_bits field from nbd_device struct.&n; *            Cleanup PARANOIA usage &amp; code.&n; */
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
r_enum
(brace
DECL|enumerator|NBD_CMD_READ
id|NBD_CMD_READ
op_assign
l_int|0
comma
DECL|enumerator|NBD_CMD_WRITE
id|NBD_CMD_WRITE
op_assign
l_int|1
comma
DECL|enumerator|NBD_CMD_DISC
id|NBD_CMD_DISC
op_assign
l_int|2
)brace
suffix:semicolon
DECL|macro|nbd_cmd
mdefine_line|#define nbd_cmd(req) ((req)-&gt;cmd[0])
DECL|macro|MAX_NBD
mdefine_line|#define MAX_NBD 128
multiline_comment|/* Define PARANOIA to include extra sanity checking code in here &amp; driver */
DECL|macro|PARANOIA
mdefine_line|#define PARANOIA
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
macro_line|#ifdef PARANOIA
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* FIXME: not if debugging is off&t;*/
macro_line|#endif
DECL|member|queue_lock
id|spinlock_t
id|queue_lock
suffix:semicolon
DECL|member|queue_head
r_struct
id|list_head
id|queue_head
suffix:semicolon
multiline_comment|/* Requests are added here...&t;*/
DECL|member|tx_lock
r_struct
id|semaphore
id|tx_lock
suffix:semicolon
DECL|member|disk
r_struct
id|gendisk
op_star
id|disk
suffix:semicolon
DECL|member|blksize
r_int
id|blksize
suffix:semicolon
DECL|member|bytesize
id|u64
id|bytesize
suffix:semicolon
)brace
suffix:semicolon
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
