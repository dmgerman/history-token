multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: rioioctl.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:13&n;**&t;Retrieved&t;: 11/6/98 11:34:22&n;**&n;**  ident @(#)rioioctl.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef&t;__rioioctl_h__
DECL|macro|__rioioctl_h__
mdefine_line|#define&t;__rioioctl_h__
macro_line|#ifdef SCCS_LABELS
DECL|variable|_rioioctl_h_sccs_
r_static
r_char
op_star
id|_rioioctl_h_sccs_
op_assign
l_string|&quot;@(#)rioioctl.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** RIO device driver - user ioctls and associated structures.&n;*/
DECL|struct|portStats
r_struct
id|portStats
(brace
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|gather
r_int
id|gather
suffix:semicolon
DECL|member|txchars
id|ulong
id|txchars
suffix:semicolon
DECL|member|rxchars
id|ulong
id|rxchars
suffix:semicolon
DECL|member|opens
id|ulong
id|opens
suffix:semicolon
DECL|member|closes
id|ulong
id|closes
suffix:semicolon
DECL|member|ioctls
id|ulong
id|ioctls
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|rIOC
mdefine_line|#define rIOC&t;(&squot;r&squot;&lt;&lt;8)
DECL|macro|TCRIOSTATE
mdefine_line|#define&t;TCRIOSTATE&t;(rIOC | 1)
DECL|macro|TCRIOXPON
mdefine_line|#define&t;TCRIOXPON&t;(rIOC | 2)
DECL|macro|TCRIOXPOFF
mdefine_line|#define&t;TCRIOXPOFF&t;(rIOC | 3)
DECL|macro|TCRIOXPCPS
mdefine_line|#define&t;TCRIOXPCPS&t;(rIOC | 4)
DECL|macro|TCRIOXPRINT
mdefine_line|#define&t;TCRIOXPRINT&t;(rIOC | 5)
DECL|macro|TCRIOIXANYON
mdefine_line|#define TCRIOIXANYON&t;(rIOC | 6)
DECL|macro|TCRIOIXANYOFF
mdefine_line|#define&t;TCRIOIXANYOFF&t;(rIOC | 7)
DECL|macro|TCRIOIXONON
mdefine_line|#define TCRIOIXONON&t;(rIOC | 8)
DECL|macro|TCRIOIXONOFF
mdefine_line|#define&t;TCRIOIXONOFF&t;(rIOC | 9)
DECL|macro|TCRIOMBIS
mdefine_line|#define&t;TCRIOMBIS&t;(rIOC | 10)
DECL|macro|TCRIOMBIC
mdefine_line|#define&t;TCRIOMBIC&t;(rIOC | 11)
DECL|macro|TCRIOTRIAD
mdefine_line|#define&t;TCRIOTRIAD&t;(rIOC | 12)
DECL|macro|TCRIOTSTATE
mdefine_line|#define TCRIOTSTATE&t;(rIOC | 13)
multiline_comment|/*&n;** 15.10.1998 ARG - ESIL 0761 part fix&n;** Add RIO ioctls for manipulating RTS and CTS flow control, (as LynxOS&n;** appears to not support hardware flow control).&n;*/
DECL|macro|TCRIOCTSFLOWEN
mdefine_line|#define TCRIOCTSFLOWEN&t;(rIOC | 14)&t;/* enable CTS flow control */
DECL|macro|TCRIOCTSFLOWDIS
mdefine_line|#define TCRIOCTSFLOWDIS&t;(rIOC | 15)&t;/* disable CTS flow control */
DECL|macro|TCRIORTSFLOWEN
mdefine_line|#define TCRIORTSFLOWEN&t;(rIOC | 16)&t;/* enable RTS flow control */
DECL|macro|TCRIORTSFLOWDIS
mdefine_line|#define TCRIORTSFLOWDIS&t;(rIOC | 17)&t;/* disable RTS flow control */
multiline_comment|/*&n;** 09.12.1998 ARG - ESIL 0776 part fix&n;** Definition for &squot;RIOC&squot; also appears in daemon.h, so we&squot;d better do a&n;** #ifndef here first.&n;** &squot;RIO_QUICK_CHECK&squot; also #define&squot;d here as this ioctl is now&n;** allowed to be used by customers.&n;**&n;** 05.02.1999 ARG -&n;** This is what I&squot;ve decied to do with ioctls etc., which are intended to be&n;** invoked from users applications :&n;** Anything that needs to be defined here will be removed from daemon.h, that&n;** way it won&squot;t end up having to be defined/maintained in two places. The only&n;** consequence of this is that this file should now be #include&squot;d by daemon.h&n;**&n;** &squot;stats&squot; ioctls now #define&squot;d here as they are to be used by customers.&n;*/
DECL|macro|RIOC
mdefine_line|#define&t;RIOC&t;(&squot;R&squot;&lt;&lt;8)|(&squot;i&squot;&lt;&lt;16)|(&squot;o&squot;&lt;&lt;24)
DECL|macro|RIO_QUICK_CHECK
mdefine_line|#define&t;RIO_QUICK_CHECK&t;  &t;(RIOC | 105)
DECL|macro|RIO_GATHER_PORT_STATS
mdefine_line|#define RIO_GATHER_PORT_STATS&t;(RIOC | 193)
DECL|macro|RIO_RESET_PORT_STATS
mdefine_line|#define RIO_RESET_PORT_STATS&t;(RIOC | 194)
DECL|macro|RIO_GET_PORT_STATS
mdefine_line|#define RIO_GET_PORT_STATS&t;(RIOC | 195)
macro_line|#endif&t;/* __rioioctl_h__ */
eof
