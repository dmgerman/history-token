multiline_comment|/* linux/aio_abi.h&n; *&n; * Copyright 2000,2001,2002 Red Hat.&n; *&n; * Written by Benjamin LaHaise &lt;bcrl@redhat.com&gt;&n; *&n; * Distribute under the terms of the GPLv2 (see ../../COPYING) or under &n; * the following terms.&n; *&n; * Permission to use, copy, modify, and distribute this software and its&n; * documentation is hereby granted, provided that the above copyright&n; * notice appears in all copies.  This software is provided without any&n; * warranty, express or implied.  Red Hat makes no representations about&n; * the suitability of this software for any purpose.&n; *&n; * IN NO EVENT SHALL RED HAT BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,&n; * SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF&n; * THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF RED HAT HAS BEEN ADVISED&n; * OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * RED HAT DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR&n; * PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN &quot;AS IS&quot; BASIS, AND&n; * RED HAT HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,&n; * ENHANCEMENTS, OR MODIFICATIONS.&n; */
macro_line|#ifndef __LINUX__AIO_ABI_H
DECL|macro|__LINUX__AIO_ABI_H
mdefine_line|#define __LINUX__AIO_ABI_H
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|typedef|aio_context_t
r_typedef
r_int
r_int
id|aio_context_t
suffix:semicolon
r_enum
(brace
DECL|enumerator|IOCB_CMD_PREAD
id|IOCB_CMD_PREAD
op_assign
l_int|0
comma
DECL|enumerator|IOCB_CMD_PWRITE
id|IOCB_CMD_PWRITE
op_assign
l_int|1
comma
DECL|enumerator|IOCB_CMD_FSYNC
id|IOCB_CMD_FSYNC
op_assign
l_int|2
comma
DECL|enumerator|IOCB_CMD_FDSYNC
id|IOCB_CMD_FDSYNC
op_assign
l_int|3
comma
multiline_comment|/* These two are experimental.&n;&t; * IOCB_CMD_PREADX = 4,&n;&t; * IOCB_CMD_POLL = 5,&n;&t; */
DECL|enumerator|IOCB_CMD_NOOP
id|IOCB_CMD_NOOP
op_assign
l_int|6
comma
)brace
suffix:semicolon
multiline_comment|/* read() from /dev/aio returns these structures. */
DECL|struct|io_event
r_struct
id|io_event
(brace
DECL|member|data
id|__u64
id|data
suffix:semicolon
multiline_comment|/* the data field from the iocb */
DECL|member|obj
id|__u64
id|obj
suffix:semicolon
multiline_comment|/* what iocb this event came from */
DECL|member|res
id|__s64
id|res
suffix:semicolon
multiline_comment|/* result code for this event */
DECL|member|res2
id|__s64
id|res2
suffix:semicolon
multiline_comment|/* secondary result */
)brace
suffix:semicolon
macro_line|#if defined(__LITTLE_ENDIAN)
DECL|macro|PADDED
mdefine_line|#define PADDED(x,y)&t;x, y
macro_line|#elif defined(__BIG_ENDIAN)
DECL|macro|PADDED
mdefine_line|#define PADDED(x,y)&t;y, x
macro_line|#else
macro_line|#error edit for your odd byteorder.
macro_line|#endif
multiline_comment|/*&n; * we always use a 64bit off_t when communicating&n; * with userland.  its up to libraries to do the&n; * proper padding and aio_error abstraction&n; */
DECL|struct|iocb
r_struct
id|iocb
(brace
multiline_comment|/* these are internal to the kernel/libc. */
DECL|member|aio_data
id|__u64
id|aio_data
suffix:semicolon
multiline_comment|/* data to be returned in event&squot;s data */
id|__u32
id|PADDED
c_func
(paren
id|aio_key
comma
id|aio_reserved1
)paren
suffix:semicolon
multiline_comment|/* the kernel sets aio_key to the req # */
multiline_comment|/* common fields */
DECL|member|aio_lio_opcode
id|__u16
id|aio_lio_opcode
suffix:semicolon
multiline_comment|/* see IOCB_CMD_ above */
DECL|member|aio_reqprio
id|__s16
id|aio_reqprio
suffix:semicolon
DECL|member|aio_fildes
id|__u32
id|aio_fildes
suffix:semicolon
DECL|member|aio_buf
id|__u64
id|aio_buf
suffix:semicolon
DECL|member|aio_nbytes
id|__u64
id|aio_nbytes
suffix:semicolon
DECL|member|aio_offset
id|__s64
id|aio_offset
suffix:semicolon
multiline_comment|/* extra parameters */
DECL|member|aio_reserved2
id|__u64
id|aio_reserved2
suffix:semicolon
multiline_comment|/* TODO: use this for a (struct sigevent *) */
DECL|member|aio_reserved3
id|__u64
id|aio_reserved3
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* 64 bytes */
DECL|macro|IFBIG
macro_line|#undef IFBIG
DECL|macro|IFLITTLE
macro_line|#undef IFLITTLE
macro_line|#endif /* __LINUX__AIO_ABI_H */
eof
