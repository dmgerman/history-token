multiline_comment|/*********************************************************************&n; *                &n; * Filename:      wrapper.h&n; * Version:       1.2&n; * Description:   IrDA SIR async wrapper layer&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Aug  4 20:40:53 1997&n; * Modified at:   Tue Jan 11 12:37:29 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-2000 Dag Brattli &lt;dagb@cs.uit.no&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef WRAPPER_H
DECL|macro|WRAPPER_H
mdefine_line|#define WRAPPER_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
DECL|macro|BOF
mdefine_line|#define BOF  0xc0 /* Beginning of frame */
DECL|macro|XBOF
mdefine_line|#define XBOF 0xff
DECL|macro|EOF
mdefine_line|#define EOF  0xc1 /* End of frame */
DECL|macro|CE
mdefine_line|#define CE   0x7d /* Control escape */
DECL|macro|STA
mdefine_line|#define STA BOF  /* Start flag */
DECL|macro|STO
mdefine_line|#define STO EOF  /* End flag */
DECL|macro|IRDA_TRANS
mdefine_line|#define IRDA_TRANS 0x20    /* Asynchronous transparency modifier */       
multiline_comment|/* States for receving a frame in async mode */
r_enum
(brace
DECL|enumerator|OUTSIDE_FRAME
id|OUTSIDE_FRAME
comma
DECL|enumerator|BEGIN_FRAME
id|BEGIN_FRAME
comma
DECL|enumerator|LINK_ESCAPE
id|LINK_ESCAPE
comma
DECL|enumerator|INSIDE_FRAME
id|INSIDE_FRAME
)brace
suffix:semicolon
multiline_comment|/* Proto definitions */
r_int
id|async_wrap_skb
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u8
op_star
id|tx_buff
comma
r_int
id|buffsize
)paren
suffix:semicolon
r_void
id|async_bump
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|net_device_stats
op_star
id|stats
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_void
id|async_unwrap_char
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|net_device_stats
op_star
id|stats
comma
id|iobuff_t
op_star
id|buf
comma
id|__u8
id|byte
)paren
suffix:semicolon
macro_line|#endif
eof
