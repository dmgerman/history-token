macro_line|#ifndef&t;_CYCX_X25_H
DECL|macro|_CYCX_X25_H
mdefine_line|#define&t;_CYCX_X25_H
multiline_comment|/*&n;* cycx_x25.h&t;Cyclom X.25 firmware API definitions.&n;*&n;* Author:&t;Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n;*&n;* Copyright:&t;(c) 1998-2003 Arnaldo Carvalho de Melo&n;*&n;* Based on sdla_x25.h by Gene Kozin &lt;74604.152@compuserve.com&gt;&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* 2000/04/02&t;acme&t;&t;dprintk and cycx_debug&n;* 1999/01/03&t;acme&t;&t;judicious use of data types&n;* 1999/01/02&t;acme&t;&t;#define X25_ACK_N3&t;0x4411&n;* 1998/12/28&t;acme&t;&t;cleanup: lot&squot;o&squot;things removed&n;*&t;&t;&t;&t;&t; commands listed,&n;*&t;&t;&t;&t;&t; TX25Cmd &amp; TX25Config structs&n;*&t;&t;&t;&t;&t; typedef&squot;ed&n;*/
macro_line|#ifndef PACKED
DECL|macro|PACKED
mdefine_line|#define PACKED __attribute__((packed))
macro_line|#endif 
multiline_comment|/* X.25 shared memory layout. */
DECL|macro|X25_MBOX_OFFS
mdefine_line|#define&t;X25_MBOX_OFFS&t;0x300&t;/* general mailbox block */
DECL|macro|X25_RXMBOX_OFFS
mdefine_line|#define&t;X25_RXMBOX_OFFS&t;0x340&t;/* receive mailbox */
multiline_comment|/* Debug */
DECL|macro|dprintk
mdefine_line|#define dprintk(level, format, a...) if (cycx_debug &gt;= level) printk(format, ##a)
r_extern
r_int
r_int
id|cycx_debug
suffix:semicolon
multiline_comment|/* Data Structures */
multiline_comment|/* X.25 Command Block. */
DECL|struct|cycx_x25_cmd
r_struct
id|cycx_x25_cmd
(brace
DECL|member|PACKED
id|u16
id|command
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|link
id|PACKED
suffix:semicolon
multiline_comment|/* values: 0 or 1 */
DECL|member|PACKED
id|u16
id|len
id|PACKED
suffix:semicolon
multiline_comment|/* values: 0 thru 0x205 (517) */
DECL|member|PACKED
id|u32
id|buf
id|PACKED
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Defines for the &squot;command&squot; field. */
DECL|macro|X25_CONNECT_REQUEST
mdefine_line|#define X25_CONNECT_REQUEST             0x4401
DECL|macro|X25_CONNECT_RESPONSE
mdefine_line|#define X25_CONNECT_RESPONSE            0x4402
DECL|macro|X25_DISCONNECT_REQUEST
mdefine_line|#define X25_DISCONNECT_REQUEST          0x4403
DECL|macro|X25_DISCONNECT_RESPONSE
mdefine_line|#define X25_DISCONNECT_RESPONSE         0x4404
DECL|macro|X25_DATA_REQUEST
mdefine_line|#define X25_DATA_REQUEST                0x4405
DECL|macro|X25_ACK_TO_VC
mdefine_line|#define X25_ACK_TO_VC&t;&t;&t;0x4406
DECL|macro|X25_INTERRUPT_RESPONSE
mdefine_line|#define X25_INTERRUPT_RESPONSE          0x4407
DECL|macro|X25_CONFIG
mdefine_line|#define X25_CONFIG                      0x4408
DECL|macro|X25_CONNECT_INDICATION
mdefine_line|#define X25_CONNECT_INDICATION          0x4409
DECL|macro|X25_CONNECT_CONFIRM
mdefine_line|#define X25_CONNECT_CONFIRM             0x440A
DECL|macro|X25_DISCONNECT_INDICATION
mdefine_line|#define X25_DISCONNECT_INDICATION       0x440B
DECL|macro|X25_DISCONNECT_CONFIRM
mdefine_line|#define X25_DISCONNECT_CONFIRM          0x440C
DECL|macro|X25_DATA_INDICATION
mdefine_line|#define X25_DATA_INDICATION             0x440E
DECL|macro|X25_INTERRUPT_INDICATION
mdefine_line|#define X25_INTERRUPT_INDICATION        0x440F
DECL|macro|X25_ACK_FROM_VC
mdefine_line|#define X25_ACK_FROM_VC&t;&t;&t;0x4410
DECL|macro|X25_ACK_N3
mdefine_line|#define X25_ACK_N3&t;&t;&t;0x4411
DECL|macro|X25_CONNECT_COLLISION
mdefine_line|#define X25_CONNECT_COLLISION           0x4413
DECL|macro|X25_N3WIN
mdefine_line|#define X25_N3WIN                       0x4414
DECL|macro|X25_LINE_ON
mdefine_line|#define X25_LINE_ON                     0x4415
DECL|macro|X25_LINE_OFF
mdefine_line|#define X25_LINE_OFF                    0x4416
DECL|macro|X25_RESET_REQUEST
mdefine_line|#define X25_RESET_REQUEST               0x4417
DECL|macro|X25_LOG
mdefine_line|#define X25_LOG                         0x4500
DECL|macro|X25_STATISTIC
mdefine_line|#define X25_STATISTIC                   0x4600
DECL|macro|X25_TRACE
mdefine_line|#define X25_TRACE                       0x4700
DECL|macro|X25_N2TRACEXC
mdefine_line|#define X25_N2TRACEXC                   0x4702
DECL|macro|X25_N3TRACEXC
mdefine_line|#define X25_N3TRACEXC                   0x4703
multiline_comment|/**&n; *&t;struct cycx_x25_config - cyclom2x x25 firmware configuration&n; *&t;@link - link number&n; *&t;@speed - line speed&n; *&t;@clock - internal/external&n; *&t;@n2 - # of level 2 retransm.(values: 1 thru FF)&n; *&t;@n2win - level 2 window (values: 1 thru 7)&n; *&t;@n3win - level 3 window (values: 1 thru 7)&n; *&t;@nvc - # of logical channels (values: 1 thru 64)&n; *&t;@pktlen - level 3 packet lenght - log base 2 of size&n; *&t;@locaddr - my address&n; *&t;@remaddr - remote address&n; *&t;@t1 - time, in seconds&n; *&t;@t2 - time, in seconds&n; *&t;@t21 - time, in seconds&n; *&t;@npvc - # of permanent virt. circuits (1 thru nvc)&n; *&t;@t23 - time, in seconds&n; *&t;@flags - see dosx25.doc, in portuguese, for details&n; */
DECL|struct|cycx_x25_config
r_struct
id|cycx_x25_config
(brace
DECL|member|PACKED
id|u8
id|link
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|speed
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|clock
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|n2
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|n2win
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|n3win
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|nvc
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|pktlen
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|locaddr
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|remaddr
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|t1
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|t2
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|t21
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|npvc
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|t23
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u8
id|flags
id|PACKED
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cycx_x25_stats
r_struct
id|cycx_x25_stats
(brace
DECL|member|PACKED
id|u16
id|rx_crc_errors
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|rx_over_errors
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|n2_tx_frames
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|n2_rx_frames
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|tx_timeouts
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|rx_timeouts
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|n3_tx_packets
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|n3_rx_packets
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|tx_aborts
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|u16
id|rx_aborts
id|PACKED
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* _CYCX_X25_H */
eof
