macro_line|#ifndef _PPP_CHANNEL_H_
DECL|macro|_PPP_CHANNEL_H_
mdefine_line|#define _PPP_CHANNEL_H_
multiline_comment|/*&n; * Definitions for the interface between the generic PPP code&n; * and a PPP channel.&n; *&n; * A PPP channel provides a way for the generic PPP code to send&n; * and receive packets over some sort of communications medium.&n; * Packets are stored in sk_buffs and have the 2-byte PPP protocol&n; * number at the start, but not the address and control bytes.&n; *&n; * Copyright 1999 Paul Mackerras.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; * ==FILEVERSION 20000322==&n; */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
r_struct
id|ppp_channel
suffix:semicolon
DECL|struct|ppp_channel_ops
r_struct
id|ppp_channel_ops
(brace
multiline_comment|/* Send a packet (or multilink fragment) on this channel.&n;&t;   Returns 1 if it was accepted, 0 if not. */
DECL|member|start_xmit
r_int
(paren
op_star
id|start_xmit
)paren
(paren
r_struct
id|ppp_channel
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* Handle an ioctl call that has come in via /dev/ppp. */
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|ppp_channel
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ppp_channel
r_struct
id|ppp_channel
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
multiline_comment|/* channel private data */
DECL|member|ops
r_struct
id|ppp_channel_ops
op_star
id|ops
suffix:semicolon
multiline_comment|/* operations for this channel */
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* max transmit packet size */
DECL|member|hdrlen
r_int
id|hdrlen
suffix:semicolon
multiline_comment|/* amount of headroom channel needs */
DECL|member|ppp
r_void
op_star
id|ppp
suffix:semicolon
multiline_comment|/* opaque to channel */
multiline_comment|/* the following are not used at present */
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* transfer rate (bytes/second) */
DECL|member|latency
r_int
id|latency
suffix:semicolon
multiline_comment|/* overhead time in milliseconds */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Called by the channel when it can send some more data. */
r_extern
r_void
id|ppp_output_wakeup
c_func
(paren
r_struct
id|ppp_channel
op_star
)paren
suffix:semicolon
multiline_comment|/* Called by the channel to process a received PPP packet.&n;   The packet should have just the 2-byte PPP protocol header. */
r_extern
r_void
id|ppp_input
c_func
(paren
r_struct
id|ppp_channel
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* Called by the channel when an input error occurs, indicating&n;   that we may have missed a packet. */
r_extern
r_void
id|ppp_input_error
c_func
(paren
r_struct
id|ppp_channel
op_star
comma
r_int
id|code
)paren
suffix:semicolon
multiline_comment|/* Attach a channel to a given PPP unit. */
r_extern
r_int
id|ppp_register_channel
c_func
(paren
r_struct
id|ppp_channel
op_star
)paren
suffix:semicolon
multiline_comment|/* Detach a channel from its PPP unit (e.g. on hangup). */
r_extern
r_void
id|ppp_unregister_channel
c_func
(paren
r_struct
id|ppp_channel
op_star
)paren
suffix:semicolon
multiline_comment|/* Get the channel number for a channel */
r_extern
r_int
id|ppp_channel_index
c_func
(paren
r_struct
id|ppp_channel
op_star
)paren
suffix:semicolon
multiline_comment|/* Get the unit number associated with a channel, or -1 if none */
r_extern
r_int
id|ppp_unit_number
c_func
(paren
r_struct
id|ppp_channel
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * SMP locking notes:&n; * The channel code must ensure that when it calls ppp_unregister_channel,&n; * nothing is executing in any of the procedures above, for that&n; * channel.  The generic layer will ensure that nothing is executing&n; * in the start_xmit and ioctl routines for the channel by the time&n; * that ppp_unregister_channel returns.&n; */
multiline_comment|/* The following are temporary compatibility stuff */
id|ssize_t
id|ppp_channel_read
c_func
(paren
r_struct
id|ppp_channel
op_star
id|chan
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
id|ssize_t
id|ppp_channel_write
c_func
(paren
r_struct
id|ppp_channel
op_star
id|chan
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
r_int
id|ppp_channel_poll
c_func
(paren
r_struct
id|ppp_channel
op_star
id|chan
comma
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
suffix:semicolon
r_int
id|ppp_channel_ioctl
c_func
(paren
r_struct
id|ppp_channel
op_star
id|chan
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
