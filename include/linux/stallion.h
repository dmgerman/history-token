multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;stallion.h  -- stallion multiport serial driver.&n; *&n; *&t;Copyright (C) 1996-1998  Stallion Technologies (support@stallion.oz.au).&n; *&t;Copyright (C) 1994-1996  Greg Ungerer.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*****************************************************************************/
macro_line|#ifndef&t;_STALLION_H
DECL|macro|_STALLION_H
mdefine_line|#define&t;_STALLION_H
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define important driver constants here.&n; */
DECL|macro|STL_MAXBRDS
mdefine_line|#define&t;STL_MAXBRDS&t;&t;4
DECL|macro|STL_MAXPANELS
mdefine_line|#define&t;STL_MAXPANELS&t;&t;4
DECL|macro|STL_MAXBANKS
mdefine_line|#define&t;STL_MAXBANKS&t;&t;8
DECL|macro|STL_PORTSPERPANEL
mdefine_line|#define&t;STL_PORTSPERPANEL&t;16
DECL|macro|STL_MAXPORTS
mdefine_line|#define&t;STL_MAXPORTS&t;&t;64
DECL|macro|STL_MAXDEVS
mdefine_line|#define&t;STL_MAXDEVS&t;&t;(STL_MAXBRDS * STL_MAXPORTS)
multiline_comment|/*&n; *&t;Define a set of structures to hold all the board/panel/port info&n; *&t;for our ports. These will be dynamically allocated as required.&n; */
multiline_comment|/*&n; *&t;Define a ring queue structure for each port. This will hold the&n; *&t;TX data waiting to be output. Characters are fed into this buffer&n; *&t;from the line discipline (or even direct from user space!) and&n; *&t;then fed into the UARTs during interrupts. Will use a classic ring&n; *&t;queue here for this. The good thing about this type of ring queue&n; *&t;is that the head and tail pointers can be updated without interrupt&n; *&t;protection - since &quot;write&quot; code only needs to change the head, and&n; *&t;interrupt code only needs to change the tail.&n; */
r_typedef
r_struct
(brace
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
DECL|member|head
r_char
op_star
id|head
suffix:semicolon
DECL|member|tail
r_char
op_star
id|tail
suffix:semicolon
DECL|typedef|stlrq_t
)brace
id|stlrq_t
suffix:semicolon
multiline_comment|/*&n; *&t;Port, panel and board structures to hold status info about each.&n; *&t;The board structure contains pointers to structures for each panel&n; *&t;connected to it, and in turn each panel structure contains pointers&n; *&t;for each port structure for each port on that panel. Note that&n; *&t;the port structure also contains the board and panel number that it&n; *&t;is associated with, this makes it (fairly) easy to get back to the&n; *&t;board/panel info for a port.&n; */
DECL|struct|stlport
r_typedef
r_struct
id|stlport
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|portnr
r_int
id|portnr
suffix:semicolon
DECL|member|panelnr
r_int
id|panelnr
suffix:semicolon
DECL|member|brdnr
r_int
id|brdnr
suffix:semicolon
DECL|member|ioaddr
r_int
id|ioaddr
suffix:semicolon
DECL|member|uartaddr
r_int
id|uartaddr
suffix:semicolon
DECL|member|pagenr
r_int
id|pagenr
suffix:semicolon
DECL|member|istate
r_int
id|istate
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|closing_wait
r_int
id|closing_wait
suffix:semicolon
DECL|member|refcount
r_int
id|refcount
suffix:semicolon
DECL|member|openwaitcnt
r_int
id|openwaitcnt
suffix:semicolon
DECL|member|brklen
r_int
id|brklen
suffix:semicolon
DECL|member|sigs
r_int
r_int
id|sigs
suffix:semicolon
DECL|member|rxignoremsk
r_int
r_int
id|rxignoremsk
suffix:semicolon
DECL|member|rxmarkmsk
r_int
r_int
id|rxmarkmsk
suffix:semicolon
DECL|member|imr
r_int
r_int
id|imr
suffix:semicolon
DECL|member|crenable
r_int
r_int
id|crenable
suffix:semicolon
DECL|member|clk
r_int
r_int
id|clk
suffix:semicolon
DECL|member|hwid
r_int
r_int
id|hwid
suffix:semicolon
DECL|member|uartp
r_void
op_star
id|uartp
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0))
DECL|member|open_wait
r_struct
id|wait_queue
op_star
id|open_wait
suffix:semicolon
DECL|member|close_wait
r_struct
id|wait_queue
op_star
id|close_wait
suffix:semicolon
macro_line|#else
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
macro_line|#endif
DECL|member|normaltermios
r_struct
id|termios
id|normaltermios
suffix:semicolon
DECL|member|tqueue
r_struct
id|work_struct
id|tqueue
suffix:semicolon
DECL|member|stats
id|comstats_t
id|stats
suffix:semicolon
DECL|member|tx
id|stlrq_t
id|tx
suffix:semicolon
DECL|typedef|stlport_t
)brace
id|stlport_t
suffix:semicolon
DECL|struct|stlpanel
r_typedef
r_struct
id|stlpanel
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|panelnr
r_int
id|panelnr
suffix:semicolon
DECL|member|brdnr
r_int
id|brdnr
suffix:semicolon
DECL|member|pagenr
r_int
id|pagenr
suffix:semicolon
DECL|member|nrports
r_int
id|nrports
suffix:semicolon
DECL|member|iobase
r_int
id|iobase
suffix:semicolon
DECL|member|uartp
r_void
op_star
id|uartp
suffix:semicolon
DECL|member|isr
r_void
(paren
op_star
id|isr
)paren
(paren
r_struct
id|stlpanel
op_star
id|panelp
comma
r_int
r_int
id|iobase
)paren
suffix:semicolon
DECL|member|hwid
r_int
r_int
id|hwid
suffix:semicolon
DECL|member|ackmask
r_int
r_int
id|ackmask
suffix:semicolon
DECL|member|ports
id|stlport_t
op_star
id|ports
(braket
id|STL_PORTSPERPANEL
)braket
suffix:semicolon
DECL|typedef|stlpanel_t
)brace
id|stlpanel_t
suffix:semicolon
DECL|struct|stlbrd
r_typedef
r_struct
id|stlbrd
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|brdnr
r_int
id|brdnr
suffix:semicolon
DECL|member|brdtype
r_int
id|brdtype
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|nrpanels
r_int
id|nrpanels
suffix:semicolon
DECL|member|nrports
r_int
id|nrports
suffix:semicolon
DECL|member|nrbnks
r_int
id|nrbnks
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|irqtype
r_int
id|irqtype
suffix:semicolon
DECL|member|isr
r_void
(paren
op_star
id|isr
)paren
(paren
r_struct
id|stlbrd
op_star
id|brdp
)paren
suffix:semicolon
DECL|member|ioaddr1
r_int
r_int
id|ioaddr1
suffix:semicolon
DECL|member|ioaddr2
r_int
r_int
id|ioaddr2
suffix:semicolon
DECL|member|iosize1
r_int
r_int
id|iosize1
suffix:semicolon
DECL|member|iosize2
r_int
r_int
id|iosize2
suffix:semicolon
DECL|member|iostatus
r_int
r_int
id|iostatus
suffix:semicolon
DECL|member|ioctrl
r_int
r_int
id|ioctrl
suffix:semicolon
DECL|member|ioctrlval
r_int
r_int
id|ioctrlval
suffix:semicolon
DECL|member|hwid
r_int
r_int
id|hwid
suffix:semicolon
DECL|member|clk
r_int
r_int
id|clk
suffix:semicolon
DECL|member|bnkpageaddr
r_int
r_int
id|bnkpageaddr
(braket
id|STL_MAXBANKS
)braket
suffix:semicolon
DECL|member|bnkstataddr
r_int
r_int
id|bnkstataddr
(braket
id|STL_MAXBANKS
)braket
suffix:semicolon
DECL|member|bnk2panel
id|stlpanel_t
op_star
id|bnk2panel
(braket
id|STL_MAXBANKS
)braket
suffix:semicolon
DECL|member|panels
id|stlpanel_t
op_star
id|panels
(braket
id|STL_MAXPANELS
)braket
suffix:semicolon
DECL|typedef|stlbrd_t
)brace
id|stlbrd_t
suffix:semicolon
multiline_comment|/*&n; *&t;Define MAGIC numbers used for above structures.&n; */
DECL|macro|STL_PORTMAGIC
mdefine_line|#define&t;STL_PORTMAGIC&t;0x5a7182c9
DECL|macro|STL_PANELMAGIC
mdefine_line|#define&t;STL_PANELMAGIC&t;0x7ef621a1
DECL|macro|STL_BOARDMAGIC
mdefine_line|#define&t;STL_BOARDMAGIC&t;0xa2267f52
multiline_comment|/*****************************************************************************/
macro_line|#endif
eof
