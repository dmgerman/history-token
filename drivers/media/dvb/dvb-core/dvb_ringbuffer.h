multiline_comment|/*&n; *&n; * dvb_ringbuffer.h: ring buffer implementation for the dvb driver&n; *&n; * Copyright (C) 2003 Oliver Endriss &n; * &n; * based on code originally found in av7110.c:&n; * Copyright (C) 1999-2002 Ralph  Metzler &n; *                       &amp; Marcus Metzler for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; * &n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; * Or, point your browser to http://www.gnu.org/copyleft/gpl.html&n; * &n; *&n; * the project&squot;s page is at http://www.linuxtv.org/dvb/&n; */
macro_line|#ifndef _DVB_RINGBUFFER_H_
DECL|macro|_DVB_RINGBUFFER_H_
mdefine_line|#define _DVB_RINGBUFFER_H_
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
DECL|struct|dvb_ringbuffer
r_struct
id|dvb_ringbuffer
(brace
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
DECL|member|size
id|ssize_t
id|size
suffix:semicolon
DECL|member|pread
id|ssize_t
id|pread
suffix:semicolon
DECL|member|pwrite
id|ssize_t
id|pwrite
suffix:semicolon
DECL|member|queue
id|wait_queue_head_t
id|queue
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;** Notes:&n;** ------&n;** (1) For performance reasons read and write routines don&squot;t check buffer sizes&n;**     and/or number of bytes free/available. This has to be done before these&n;**     routines are called. For example:&n;**&n;**     *** write &lt;buflen&gt; bytes ***&n;**     free = dvb_ringbuffer_free(rbuf);&n;**     if (free &gt;= buflen) &n;**         count = dvb_ringbuffer_write(rbuf, buffer, buflen, 0);&n;**     else&n;**         ...&n;**&n;**     *** read min. 1000, max. &lt;bufsize&gt; bytes ***&n;**     avail = dvb_ringbuffer_avail(rbuf);&n;**     if (avail &gt;= 1000)&n;**         count = dvb_ringbuffer_read(rbuf, buffer, min(avail, bufsize), 0);&n;**     else&n;**         ...&n;**&n;** (2) If there is exactly one reader and one writer, there is no need &n;**     to lock read or write operations.&n;**     Two or more readers must be locked against each other.&n;**     Flushing the buffer counts as a read operation.&n;**     Two or more writers must be locked against each other.&n;*/
multiline_comment|/* initialize ring buffer, lock and queue */
r_extern
r_void
id|dvb_ringbuffer_init
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
comma
r_void
op_star
id|data
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* test whether buffer is empty */
r_extern
r_int
id|dvb_ringbuffer_empty
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
)paren
suffix:semicolon
multiline_comment|/* return the number of free bytes in the buffer */
r_extern
id|ssize_t
id|dvb_ringbuffer_free
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
)paren
suffix:semicolon
multiline_comment|/* return the number of bytes waiting in the buffer */
r_extern
id|ssize_t
id|dvb_ringbuffer_avail
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
)paren
suffix:semicolon
multiline_comment|/* read routines &amp; macros */
multiline_comment|/* ---------------------- */
multiline_comment|/* flush buffer */
r_extern
r_void
id|dvb_ringbuffer_flush
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
)paren
suffix:semicolon
multiline_comment|/* flush buffer protected by spinlock and wake-up waiting task(s) */
r_extern
r_void
id|dvb_ringbuffer_flush_spinlock_wakeup
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
)paren
suffix:semicolon
multiline_comment|/* peek at byte &lt;offs&gt; in the buffer */
DECL|macro|DVB_RINGBUFFER_PEEK
mdefine_line|#define DVB_RINGBUFFER_PEEK(rbuf,offs)&t;&bslash;&n;&t;&t;&t;(rbuf)-&gt;data[((rbuf)-&gt;pread+(offs))%(rbuf)-&gt;size]
multiline_comment|/* advance read ptr by &lt;num&gt; bytes */
DECL|macro|DVB_RINGBUFFER_SKIP
mdefine_line|#define DVB_RINGBUFFER_SKIP(rbuf,num)&t;&bslash;&n;&t;&t;&t;(rbuf)-&gt;pread=((rbuf)-&gt;pread+(num))%(rbuf)-&gt;size
multiline_comment|/*&n;** read &lt;len&gt; bytes from ring buffer into &lt;buf&gt; &n;** &lt;usermem&gt; specifies whether &lt;buf&gt; resides in user space&n;** returns number of bytes transferred or -EFAULT&n;*/
r_extern
id|ssize_t
id|dvb_ringbuffer_read
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
comma
id|u8
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|usermem
)paren
suffix:semicolon
multiline_comment|/* write routines &amp; macros */
multiline_comment|/* ----------------------- */
multiline_comment|/* write single byte to ring buffer */
DECL|macro|DVB_RINGBUFFER_WRITE_BYTE
mdefine_line|#define DVB_RINGBUFFER_WRITE_BYTE(rbuf,byte)&t;&bslash;&n;&t;&t;&t;{ (rbuf)-&gt;data[(rbuf)-&gt;pwrite]=(byte); &bslash;&n;&t;&t;&t;(rbuf)-&gt;pwrite=((rbuf)-&gt;pwrite+1)%(rbuf)-&gt;size; }
multiline_comment|/*&n;** write &lt;len&gt; bytes to ring buffer&n;** &lt;usermem&gt; specifies whether &lt;buf&gt; resides in user space&n;** returns number of bytes transferred or -EFAULT&n;*/
r_extern
id|ssize_t
id|dvb_ringbuffer_write
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
comma
r_const
id|u8
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|usermem
)paren
suffix:semicolon
macro_line|#endif /* _DVB_RINGBUFFER_H_ */
eof
