multiline_comment|/* $Id: card.h,v 1.1.10.1 2001/09/23 22:24:59 kai Exp $&n; *&n; * Driver parameters for SpellCaster ISA ISDN adapters&n; *&n; * Copyright (C) 1996  SpellCaster Telecommunications Inc.&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For more information, please contact gpl-info@spellcast.com or write:&n; *&n; *     SpellCaster Telecommunications Inc.&n; *     5621 Finch Avenue East, Unit #3&n; *     Scarborough, Ontario  Canada&n; *     M1B 2T9&n; *     +1 (416) 297-8565&n; *     +1 (416) 297-6433 Facsimile&n; */
macro_line|#ifndef CARD_H
DECL|macro|CARD_H
mdefine_line|#define CARD_H
multiline_comment|/*&n; * We need these if they&squot;re not already included&n; */
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#include &quot;message.h&quot;
multiline_comment|/*&n; * Amount of time to wait for a reset to complete&n; */
DECL|macro|CHECKRESET_TIME
mdefine_line|#define CHECKRESET_TIME&t;&t;milliseconds(4000)
multiline_comment|/*&n; * Amount of time between line status checks&n; */
DECL|macro|CHECKSTAT_TIME
mdefine_line|#define CHECKSTAT_TIME&t;&t;milliseconds(8000)
multiline_comment|/*&n; * The maximum amount of time to wait for a message response&n; * to arrive. Use exclusively by send_and_receive&n; */
DECL|macro|SAR_TIMEOUT
mdefine_line|#define SAR_TIMEOUT&t;&t;milliseconds(10000)
multiline_comment|/*&n; * Macro to determine is a card id is valid&n; */
DECL|macro|IS_VALID_CARD
mdefine_line|#define IS_VALID_CARD(x)&t;((x &gt;= 0) &amp;&amp; (x &lt;= cinst))
multiline_comment|/*&n; * Per channel status and configuration&n; */
r_typedef
r_struct
(brace
DECL|member|l2_proto
r_int
id|l2_proto
suffix:semicolon
DECL|member|l3_proto
r_int
id|l3_proto
suffix:semicolon
DECL|member|dn
r_char
id|dn
(braket
l_int|50
)braket
suffix:semicolon
DECL|member|first_sendbuf
r_int
r_int
id|first_sendbuf
suffix:semicolon
multiline_comment|/* Offset of first send buffer */
DECL|member|num_sendbufs
r_int
r_int
id|num_sendbufs
suffix:semicolon
multiline_comment|/* Number of send buffers */
DECL|member|free_sendbufs
r_int
r_int
id|free_sendbufs
suffix:semicolon
multiline_comment|/* Number of free sendbufs */
DECL|member|next_sendbuf
r_int
r_int
id|next_sendbuf
suffix:semicolon
multiline_comment|/* Next sequential buffer */
DECL|member|eazlist
r_char
id|eazlist
(braket
l_int|50
)braket
suffix:semicolon
multiline_comment|/* Set with SETEAZ */
DECL|member|sillist
r_char
id|sillist
(braket
l_int|50
)braket
suffix:semicolon
multiline_comment|/* Set with SETSIL */
DECL|member|eazclear
r_int
id|eazclear
suffix:semicolon
multiline_comment|/* Don&squot;t accept calls if TRUE */
DECL|typedef|bchan
)brace
id|bchan
suffix:semicolon
multiline_comment|/*&n; * Everything you want to know about the adapter ...&n; */
r_typedef
r_struct
(brace
DECL|member|model
r_int
id|model
suffix:semicolon
DECL|member|driverId
r_int
id|driverId
suffix:semicolon
multiline_comment|/* LL Id */
DECL|member|devicename
r_char
id|devicename
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* The device name */
DECL|member|card
id|isdn_if
op_star
id|card
suffix:semicolon
multiline_comment|/* ISDN4Linux structure */
DECL|member|channel
id|bchan
op_star
id|channel
suffix:semicolon
multiline_comment|/* status of the B channels */
DECL|member|nChannels
r_char
id|nChannels
suffix:semicolon
multiline_comment|/* Number of channels */
DECL|member|interrupt
r_int
r_int
id|interrupt
suffix:semicolon
multiline_comment|/* Interrupt number */
DECL|member|iobase
r_int
id|iobase
suffix:semicolon
multiline_comment|/* I/O Base address */
DECL|member|ioport
r_int
id|ioport
(braket
id|MAX_IO_REGS
)braket
suffix:semicolon
multiline_comment|/* Index to I/O ports */
DECL|member|shmem_pgport
r_int
id|shmem_pgport
suffix:semicolon
multiline_comment|/* port for the exp mem page reg. */
DECL|member|shmem_magic
r_int
id|shmem_magic
suffix:semicolon
multiline_comment|/* adapter magic number */
DECL|member|rambase
r_int
r_int
id|rambase
suffix:semicolon
multiline_comment|/* Shared RAM base address */
DECL|member|ramsize
r_int
r_int
id|ramsize
suffix:semicolon
multiline_comment|/* Size of shared memory */
DECL|member|async_msg
id|RspMessage
id|async_msg
suffix:semicolon
multiline_comment|/* Async response message */
DECL|member|want_async_messages
r_int
id|want_async_messages
suffix:semicolon
multiline_comment|/* Snoop the Q ? */
DECL|member|seq_no
r_int
r_char
id|seq_no
suffix:semicolon
multiline_comment|/* Next send seq. number */
DECL|member|reset_timer
r_struct
id|timer_list
id|reset_timer
suffix:semicolon
multiline_comment|/* Check reset timer */
DECL|member|stat_timer
r_struct
id|timer_list
id|stat_timer
suffix:semicolon
multiline_comment|/* Check startproc timer */
DECL|member|nphystat
r_int
r_char
id|nphystat
suffix:semicolon
multiline_comment|/* Latest PhyStat info */
DECL|member|phystat
r_int
r_char
id|phystat
suffix:semicolon
multiline_comment|/* Last PhyStat info */
DECL|member|hwconfig
id|HWConfig_pl
id|hwconfig
suffix:semicolon
multiline_comment|/* Hardware config info */
DECL|member|load_ver
r_char
id|load_ver
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* CommManage Version string */
DECL|member|proc_ver
r_char
id|proc_ver
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* CommEngine Version */
DECL|member|StartOnReset
r_int
id|StartOnReset
suffix:semicolon
multiline_comment|/* Indicates startproc after reset */
DECL|member|EngineUp
r_int
id|EngineUp
suffix:semicolon
multiline_comment|/* Indicates CommEngine Up */
DECL|member|trace_mode
r_int
id|trace_mode
suffix:semicolon
multiline_comment|/* Indicate if tracing is on */
DECL|typedef|board
)brace
id|board
suffix:semicolon
macro_line|#endif /* CARD_H */
eof
