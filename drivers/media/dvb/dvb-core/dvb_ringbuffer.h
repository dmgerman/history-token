multiline_comment|/*&n; *&n; * dvb_ringbuffer.h: ring buffer implementation for the dvb driver&n; *&n; * Copyright (C) 2003 Oliver Endriss &n; * Copyright (C) 2004 Andrew de Quincey&n; * &n; * based on code originally found in av7110.c &amp; dvb_ci.c:&n; * Copyright (C) 1999-2003 Ralph Metzler &amp; Marcus Metzler&n; *                         for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU Lesser General Public License for more details.&n; * &n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
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
DECL|macro|DVB_RINGBUFFER_PKTHDRSIZE
mdefine_line|#define DVB_RINGBUFFER_PKTHDRSIZE 3
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
multiline_comment|/**&n; * Write a packet into the ringbuffer.&n; *&n; * &lt;rbuf&gt; Ringbuffer to write to.&n; * &lt;buf&gt; Buffer to write.&n; * &lt;len&gt; Length of buffer (currently limited to 65535 bytes max).&n; * &lt;usermem&gt; Set to 1 if &lt;buf&gt; is in userspace.&n; * returns Number of bytes written, or -EFAULT, -ENOMEM, -EVINAL.&n; */
r_extern
id|ssize_t
id|dvb_ringbuffer_pkt_write
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
multiline_comment|/**&n; * Read from a packet in the ringbuffer. Note: unlike dvb_ringbuffer_read(), this&n; * does NOT update the read pointer in the ringbuffer. You must use&n; * dvb_ringbuffer_pkt_dispose() to mark a packet as no longer required.&n; *&n; * &lt;rbuf&gt; Ringbuffer concerned.&n; * &lt;idx&gt; Packet index as returned by dvb_ringbuffer_pkt_next().&n; * &lt;offset&gt; Offset into packet to read from.&n; * &lt;buf&gt; Destination buffer for data.&n; * &lt;len&gt; Size of destination buffer.&n; * &lt;usermem&gt; Set to 1 if &lt;buf&gt; is in userspace.&n; * returns Number of bytes read, or -EFAULT.&n; */
r_extern
id|ssize_t
id|dvb_ringbuffer_pkt_read
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
comma
r_int
id|idx
comma
r_int
id|offset
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
multiline_comment|/**&n; * Dispose of a packet in the ring buffer.&n; *&n; * &lt;rbuf&gt; Ring buffer concerned.&n; * &lt;idx&gt; Packet index as returned by dvb_ringbuffer_pkt_next().&n; */
r_extern
r_void
id|dvb_ringbuffer_pkt_dispose
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
comma
r_int
id|idx
)paren
suffix:semicolon
multiline_comment|/**&n; * Get the index of the next packet in a ringbuffer.&n; *&n; * &lt;rbuf&gt; Ringbuffer concerned.&n; * &lt;idx&gt; Previous packet index, or -1 to return the first packet index.&n; * &lt;pktlen&gt; On success, will be updated to contain the length of the packet in bytes.&n; * returns Packet index (if &gt;=0), or -1 if no packets available.&n; */
r_extern
id|ssize_t
id|dvb_ringbuffer_pkt_next
c_func
(paren
r_struct
id|dvb_ringbuffer
op_star
id|rbuf
comma
r_int
id|idx
comma
r_int
op_star
id|pktlen
)paren
suffix:semicolon
macro_line|#endif /* _DVB_RINGBUFFER_H_ */
eof
