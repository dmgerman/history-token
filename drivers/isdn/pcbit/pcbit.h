multiline_comment|/*&n; * PCBIT-D device driver definitions&n; *&n; * Copyright (C) 1996 Universidade de Lisboa&n; * &n; * Written by Pedro Roque Marques (roque@di.fc.ul.pt)&n; *&n; * This software may be used and distributed according to the terms of &n; * the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#ifndef PCBIT_H
DECL|macro|PCBIT_H
mdefine_line|#define PCBIT_H
macro_line|#include &lt;linux/tqueue.h&gt;
DECL|macro|MAX_PCBIT_CARDS
mdefine_line|#define MAX_PCBIT_CARDS 4
DECL|macro|BLOCK_TIMER
mdefine_line|#define BLOCK_TIMER
macro_line|#ifdef __KERNEL__
DECL|struct|pcbit_chan
r_struct
id|pcbit_chan
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|callref
r_int
r_int
id|callref
suffix:semicolon
multiline_comment|/* Call Reference */
DECL|member|proto
r_int
r_char
id|proto
suffix:semicolon
multiline_comment|/* layer2protocol  */
DECL|member|queued
r_int
r_char
id|queued
suffix:semicolon
multiline_comment|/* unacked data messages */
DECL|member|layer2link
r_int
r_char
id|layer2link
suffix:semicolon
multiline_comment|/* used in TData */
DECL|member|snum
r_int
r_char
id|snum
suffix:semicolon
multiline_comment|/* used in TData */
DECL|member|s_refnum
r_int
r_int
id|s_refnum
suffix:semicolon
DECL|member|r_refnum
r_int
r_int
id|r_refnum
suffix:semicolon
DECL|member|fsm_state
r_int
r_int
id|fsm_state
suffix:semicolon
DECL|member|fsm_timer
r_struct
id|timer_list
id|fsm_timer
suffix:semicolon
macro_line|#ifdef  BLOCK_TIMER
DECL|member|block_timer
r_struct
id|timer_list
id|block_timer
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|msn_entry
r_struct
id|msn_entry
(brace
DECL|member|msn
r_char
op_star
id|msn
suffix:semicolon
DECL|member|next
r_struct
id|msn_entry
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcbit_dev
r_struct
id|pcbit_dev
(brace
multiline_comment|/* board */
DECL|member|sh_mem
r_volatile
r_int
r_char
op_star
id|sh_mem
suffix:semicolon
multiline_comment|/* RDP address&t;*/
DECL|member|ph_mem
r_int
r_int
id|ph_mem
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|interrupt
r_int
r_int
id|interrupt
suffix:semicolon
multiline_comment|/* set during interrupt &n;&t;&t;&t;&t;&t;&t;   processing */
multiline_comment|/* isdn4linux */
DECL|member|msn_list
r_struct
id|msn_entry
op_star
id|msn_list
suffix:semicolon
multiline_comment|/* ISDN address list */
DECL|member|dev_if
id|isdn_if
op_star
id|dev_if
suffix:semicolon
DECL|member|ll_hdrlen
id|ushort
id|ll_hdrlen
suffix:semicolon
DECL|member|hl_hdrlen
id|ushort
id|hl_hdrlen
suffix:semicolon
multiline_comment|/* link layer */
DECL|member|l2_state
r_int
r_char
id|l2_state
suffix:semicolon
DECL|member|read_queue
r_struct
id|frame_buf
op_star
id|read_queue
suffix:semicolon
DECL|member|read_frame
r_struct
id|frame_buf
op_star
id|read_frame
suffix:semicolon
DECL|member|write_queue
r_struct
id|frame_buf
op_star
id|write_queue
suffix:semicolon
multiline_comment|/* Protocol start */
DECL|member|set_running_wq
id|wait_queue_head_t
id|set_running_wq
suffix:semicolon
DECL|member|set_running_timer
r_struct
id|timer_list
id|set_running_timer
suffix:semicolon
DECL|member|error_recover_timer
r_struct
id|timer_list
id|error_recover_timer
suffix:semicolon
DECL|member|qdelivery
r_struct
id|tq_struct
id|qdelivery
suffix:semicolon
DECL|member|w_busy
id|u_char
id|w_busy
suffix:semicolon
DECL|member|r_busy
id|u_char
id|r_busy
suffix:semicolon
DECL|member|readptr
r_volatile
r_int
r_char
op_star
id|readptr
suffix:semicolon
DECL|member|writeptr
r_volatile
r_int
r_char
op_star
id|writeptr
suffix:semicolon
DECL|member|loadptr
id|ushort
id|loadptr
suffix:semicolon
DECL|member|fsize
r_int
r_int
id|fsize
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* sent layer2 frames size */
DECL|member|send_seq
r_int
r_char
id|send_seq
suffix:semicolon
DECL|member|rcv_seq
r_int
r_char
id|rcv_seq
suffix:semicolon
DECL|member|unack_seq
r_int
r_char
id|unack_seq
suffix:semicolon
DECL|member|free
r_int
r_int
id|free
suffix:semicolon
multiline_comment|/* channels */
DECL|member|b1
r_struct
id|pcbit_chan
op_star
id|b1
suffix:semicolon
DECL|member|b2
r_struct
id|pcbit_chan
op_star
id|b2
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|STATS_TIMER
mdefine_line|#define STATS_TIMER (10*HZ)
DECL|macro|ERRTIME
mdefine_line|#define ERRTIME     (HZ/10)
multiline_comment|/* MRU */
DECL|macro|MAXBUFSIZE
mdefine_line|#define MAXBUFSIZE  1534
DECL|macro|MRU
mdefine_line|#define MRU   MAXBUFSIZE
DECL|macro|STATBUF_LEN
mdefine_line|#define STATBUF_LEN 2048
multiline_comment|/*&n; * &n; */
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* isdn_ctrl only allows a long sized argument */
DECL|struct|pcbit_ioctl
r_struct
id|pcbit_ioctl
(brace
r_union
(brace
DECL|struct|byte_op
r_struct
id|byte_op
(brace
DECL|member|addr
id|ushort
id|addr
suffix:semicolon
DECL|member|value
id|ushort
id|value
suffix:semicolon
DECL|member|rdp_byte
)brace
id|rdp_byte
suffix:semicolon
DECL|member|l2_status
r_int
r_int
id|l2_status
suffix:semicolon
DECL|member|info
)brace
id|info
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PCBIT_IOCTL_GETSTAT
mdefine_line|#define PCBIT_IOCTL_GETSTAT  0x01    /* layer2 status */
DECL|macro|PCBIT_IOCTL_LWMODE
mdefine_line|#define PCBIT_IOCTL_LWMODE   0x02    /* linear write mode */
DECL|macro|PCBIT_IOCTL_STRLOAD
mdefine_line|#define PCBIT_IOCTL_STRLOAD  0x03    /* start load mode */
DECL|macro|PCBIT_IOCTL_ENDLOAD
mdefine_line|#define PCBIT_IOCTL_ENDLOAD  0x04    /* end load mode */
DECL|macro|PCBIT_IOCTL_SETBYTE
mdefine_line|#define PCBIT_IOCTL_SETBYTE  0x05    /* set byte */
DECL|macro|PCBIT_IOCTL_GETBYTE
mdefine_line|#define PCBIT_IOCTL_GETBYTE  0x06    /* get byte */
DECL|macro|PCBIT_IOCTL_RUNNING
mdefine_line|#define PCBIT_IOCTL_RUNNING  0x07    /* set protocol running */
DECL|macro|PCBIT_IOCTL_WATCH188
mdefine_line|#define PCBIT_IOCTL_WATCH188 0x08    /* set watch 188 */
DECL|macro|PCBIT_IOCTL_PING188
mdefine_line|#define PCBIT_IOCTL_PING188  0x09    /* ping 188 */
DECL|macro|PCBIT_IOCTL_FWMODE
mdefine_line|#define PCBIT_IOCTL_FWMODE   0x0A    /* firmware write mode */
DECL|macro|PCBIT_IOCTL_STOP
mdefine_line|#define PCBIT_IOCTL_STOP     0x0B    /* stop protocol */
DECL|macro|PCBIT_IOCTL_APION
mdefine_line|#define PCBIT_IOCTL_APION    0x0C    /* issue API_ON  */
macro_line|#ifndef __KERNEL__
DECL|macro|PCBIT_GETSTAT
mdefine_line|#define PCBIT_GETSTAT  (PCBIT_IOCTL_GETSTAT  + IIOCDRVCTL)
DECL|macro|PCBIT_LWMODE
mdefine_line|#define PCBIT_LWMODE   (PCBIT_IOCTL_LWMODE   + IIOCDRVCTL)
DECL|macro|PCBIT_STRLOAD
mdefine_line|#define PCBIT_STRLOAD  (PCBIT_IOCTL_STRLOAD  + IIOCDRVCTL)
DECL|macro|PCBIT_ENDLOAD
mdefine_line|#define PCBIT_ENDLOAD  (PCBIT_IOCTL_ENDLOAD  + IIOCDRVCTL)
DECL|macro|PCBIT_SETBYTE
mdefine_line|#define PCBIT_SETBYTE  (PCBIT_IOCTL_SETBYTE  + IIOCDRVCTL)
DECL|macro|PCBIT_GETBYTE
mdefine_line|#define PCBIT_GETBYTE  (PCBIT_IOCTL_GETBYTE  + IIOCDRVCTL)
DECL|macro|PCBIT_RUNNING
mdefine_line|#define PCBIT_RUNNING  (PCBIT_IOCTL_RUNNING  + IIOCDRVCTL)
DECL|macro|PCBIT_WATCH188
mdefine_line|#define PCBIT_WATCH188 (PCBIT_IOCTL_WATCH188 + IIOCDRVCTL)
DECL|macro|PCBIT_PING188
mdefine_line|#define PCBIT_PING188  (PCBIT_IOCTL_PING188  + IIOCDRVCTL)
DECL|macro|PCBIT_FWMODE
mdefine_line|#define PCBIT_FWMODE   (PCBIT_IOCTL_FWMODE   + IIOCDRVCTL)
DECL|macro|PCBIT_STOP
mdefine_line|#define PCBIT_STOP     (PCBIT_IOCTL_STOP     + IIOCDRVCTL)
DECL|macro|PCBIT_APION
mdefine_line|#define PCBIT_APION    (PCBIT_IOCTL_APION    + IIOCDRVCTL)
DECL|macro|MAXSUPERLINE
mdefine_line|#define MAXSUPERLINE 3000
macro_line|#endif
DECL|macro|L2_DOWN
mdefine_line|#define L2_DOWN     0
DECL|macro|L2_LOADING
mdefine_line|#define L2_LOADING  1
DECL|macro|L2_LWMODE
mdefine_line|#define L2_LWMODE   2
DECL|macro|L2_FWMODE
mdefine_line|#define L2_FWMODE   3
DECL|macro|L2_STARTING
mdefine_line|#define L2_STARTING 4
DECL|macro|L2_RUNNING
mdefine_line|#define L2_RUNNING  5
DECL|macro|L2_ERROR
mdefine_line|#define L2_ERROR    6
macro_line|#endif
eof
