multiline_comment|/* r3964 linediscipline for linux&n; *&n; * -----------------------------------------------------------&n; * Copyright by&n; * Philips Automation Projects&n; * Kassel (Germany)&n; * http://www.pap-philips.de&n; * -----------------------------------------------------------&n; * This software may be used and distributed according to the terms of&n; * the GNU General Public License, incorporated herein by reference.&n; *&n; * Author:&n; * L. Haag&n; *&n; * $Log: r3964.h,v $&n; * Revision 1.1.1.1  1998/10/13 16:43:14  dwmw2&n; * This&squot;ll screw the version control&n; *&n; * Revision 1.6  1998/09/30 00:40:38  dwmw2&n; * Updated to use kernel&squot;s N_R3964 if available&n; *&n; * Revision 1.4  1998/04/02 20:29:44  lhaag&n; * select, blocking, ...&n; *&n; * Revision 1.3  1998/02/12 18:58:43  root&n; * fixed some memory leaks&n; * calculation of checksum characters&n; *&n; * Revision 1.2  1998/02/07 13:03:17  root&n; * ioctl read_telegram&n; *&n; * Revision 1.1  1998/02/06 19:19:43  root&n; * Initial revision&n; *&n; *&n; */
macro_line|#ifndef __LINUX_N_R3964_H__
DECL|macro|__LINUX_N_R3964_H__
mdefine_line|#define __LINUX_N_R3964_H__
multiline_comment|/* line disciplines for r3964 protocol */
macro_line|#include &lt;asm/termios.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Common ascii handshake characters:&n; */
DECL|macro|STX
mdefine_line|#define STX 0x02
DECL|macro|ETX
mdefine_line|#define ETX 0x03
DECL|macro|DLE
mdefine_line|#define DLE 0x10
DECL|macro|NAK
mdefine_line|#define NAK 0x15
multiline_comment|/*&n; * Timeouts (msecs/10 msecs per timer interrupt):&n; */
DECL|macro|R3964_TO_QVZ
mdefine_line|#define R3964_TO_QVZ 550/10
DECL|macro|R3964_TO_ZVZ
mdefine_line|#define R3964_TO_ZVZ 220/10
DECL|macro|R3964_TO_NO_BUF
mdefine_line|#define R3964_TO_NO_BUF 400/10
DECL|macro|R3964_NO_TX_ROOM
mdefine_line|#define R3964_NO_TX_ROOM 100/10
DECL|macro|R3964_TO_RX_PANIC
mdefine_line|#define R3964_TO_RX_PANIC 4000/10
DECL|macro|R3964_MAX_RETRIES
mdefine_line|#define R3964_MAX_RETRIES 5
macro_line|#endif
multiline_comment|/*&n; * Ioctl-commands&n; */
DECL|macro|R3964_ENABLE_SIGNALS
mdefine_line|#define R3964_ENABLE_SIGNALS      0x5301
DECL|macro|R3964_SETPRIORITY
mdefine_line|#define R3964_SETPRIORITY         0x5302
DECL|macro|R3964_USE_BCC
mdefine_line|#define R3964_USE_BCC             0x5303
DECL|macro|R3964_READ_TELEGRAM
mdefine_line|#define R3964_READ_TELEGRAM       0x5304
multiline_comment|/* Options for R3964_SETPRIORITY */
DECL|macro|R3964_MASTER
mdefine_line|#define R3964_MASTER   0
DECL|macro|R3964_SLAVE
mdefine_line|#define R3964_SLAVE    1
multiline_comment|/* Options for R3964_ENABLE_SIGNALS */
DECL|macro|R3964_SIG_ACK
mdefine_line|#define R3964_SIG_ACK   0x0001
DECL|macro|R3964_SIG_DATA
mdefine_line|#define R3964_SIG_DATA  0x0002
DECL|macro|R3964_SIG_ALL
mdefine_line|#define R3964_SIG_ALL   0x000f
DECL|macro|R3964_SIG_NONE
mdefine_line|#define R3964_SIG_NONE  0x0000
DECL|macro|R3964_USE_SIGIO
mdefine_line|#define R3964_USE_SIGIO 0x1000
multiline_comment|/*&n; * r3964 operation states:&n; */
macro_line|#ifdef __KERNEL__
DECL|enumerator|R3964_IDLE
r_enum
(brace
id|R3964_IDLE
comma
DECL|enumerator|R3964_TX_REQUEST
DECL|enumerator|R3964_TRANSMITTING
id|R3964_TX_REQUEST
comma
id|R3964_TRANSMITTING
comma
DECL|enumerator|R3964_WAIT_ZVZ_BEFORE_TX_RETRY
DECL|enumerator|R3964_WAIT_FOR_TX_ACK
id|R3964_WAIT_ZVZ_BEFORE_TX_RETRY
comma
id|R3964_WAIT_FOR_TX_ACK
comma
DECL|enumerator|R3964_WAIT_FOR_RX_BUF
id|R3964_WAIT_FOR_RX_BUF
comma
DECL|enumerator|R3964_RECEIVING
DECL|enumerator|R3964_WAIT_FOR_BCC
DECL|enumerator|R3964_WAIT_FOR_RX_REPEAT
id|R3964_RECEIVING
comma
id|R3964_WAIT_FOR_BCC
comma
id|R3964_WAIT_FOR_RX_REPEAT
)brace
suffix:semicolon
multiline_comment|/*&n; * All open file-handles are &squot;clients&squot; and are stored in a linked list:&n; */
r_struct
id|r3964_message
suffix:semicolon
DECL|struct|r3964_client_info
r_struct
id|r3964_client_info
(brace
DECL|member|pid
id|pid_t
id|pid
suffix:semicolon
DECL|member|sig_flags
r_int
r_int
id|sig_flags
suffix:semicolon
DECL|member|next
r_struct
id|r3964_client_info
op_star
id|next
suffix:semicolon
DECL|member|first_msg
r_struct
id|r3964_message
op_star
id|first_msg
suffix:semicolon
DECL|member|last_msg
r_struct
id|r3964_message
op_star
id|last_msg
suffix:semicolon
DECL|member|next_block_to_read
r_struct
id|r3964_block_header
op_star
id|next_block_to_read
suffix:semicolon
DECL|member|msg_count
r_int
id|msg_count
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* types for msg_id: */
DECL|enumerator|R3964_MSG_ACK
DECL|enumerator|R3964_MSG_DATA
r_enum
(brace
id|R3964_MSG_ACK
op_assign
l_int|1
comma
id|R3964_MSG_DATA
)brace
suffix:semicolon
DECL|macro|R3964_MAX_MSG_COUNT
mdefine_line|#define R3964_MAX_MSG_COUNT 32
multiline_comment|/* error codes for client messages */
DECL|macro|R3964_OK
mdefine_line|#define R3964_OK 0        /* no error. */
DECL|macro|R3964_TX_FAIL
mdefine_line|#define R3964_TX_FAIL -1  /* transmission error, block NOT sent */
DECL|macro|R3964_OVERFLOW
mdefine_line|#define R3964_OVERFLOW -2 /* msg queue overflow */
multiline_comment|/* the client gets this struct when calling read(fd,...): */
DECL|struct|r3964_client_message
r_struct
id|r3964_client_message
(brace
DECL|member|msg_id
r_int
id|msg_id
suffix:semicolon
DECL|member|arg
r_int
id|arg
suffix:semicolon
DECL|member|error_code
r_int
id|error_code
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|R3964_MTU
mdefine_line|#define R3964_MTU      256
macro_line|#ifdef __KERNEL__
r_struct
id|r3964_block_header
suffix:semicolon
multiline_comment|/* internal version of client_message: */
DECL|struct|r3964_message
r_struct
id|r3964_message
(brace
DECL|member|msg_id
r_int
id|msg_id
suffix:semicolon
DECL|member|arg
r_int
id|arg
suffix:semicolon
DECL|member|error_code
r_int
id|error_code
suffix:semicolon
DECL|member|block
r_struct
id|r3964_block_header
op_star
id|block
suffix:semicolon
DECL|member|next
r_struct
id|r3964_message
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Header of received block in rx_buf/tx_buf:&n; */
DECL|struct|r3964_block_header
r_struct
id|r3964_block_header
(brace
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* length in chars without header */
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* usually data is located &n;                                        immediatly behind this struct */
DECL|member|locks
r_int
r_int
id|locks
suffix:semicolon
multiline_comment|/* only used in rx_buffer */
DECL|member|next
r_struct
id|r3964_block_header
op_star
id|next
suffix:semicolon
DECL|member|owner
r_struct
id|r3964_client_info
op_star
id|owner
suffix:semicolon
multiline_comment|/* =NULL in rx_buffer */
)brace
suffix:semicolon
multiline_comment|/*&n; * If rx_buf hasn&squot;t enough space to store R3964_MTU chars,&n; * we will reject all incoming STX-requests by sending NAK.&n; */
DECL|macro|RX_BUF_SIZE
mdefine_line|#define RX_BUF_SIZE    4000
DECL|macro|TX_BUF_SIZE
mdefine_line|#define TX_BUF_SIZE    4000
DECL|macro|R3964_MAX_BLOCKS_IN_RX_QUEUE
mdefine_line|#define R3964_MAX_BLOCKS_IN_RX_QUEUE 100
DECL|macro|R3964_PARITY
mdefine_line|#define R3964_PARITY 0x0001
DECL|macro|R3964_FRAME
mdefine_line|#define R3964_FRAME  0x0002
DECL|macro|R3964_OVERRUN
mdefine_line|#define R3964_OVERRUN 0x0004
DECL|macro|R3964_UNKNOWN
mdefine_line|#define R3964_UNKNOWN 0x0008
DECL|macro|R3964_BREAK
mdefine_line|#define R3964_BREAK   0x0010
DECL|macro|R3964_CHECKSUM
mdefine_line|#define R3964_CHECKSUM 0x0020
DECL|macro|R3964_ERROR
mdefine_line|#define R3964_ERROR  0x003f
DECL|macro|R3964_BCC
mdefine_line|#define R3964_BCC   0x4000
DECL|macro|R3964_DEBUG
mdefine_line|#define R3964_DEBUG 0x8000
DECL|struct|r3964_info
r_struct
id|r3964_info
(brace
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|priority
r_int
r_char
id|priority
suffix:semicolon
DECL|member|rx_buf
r_int
r_char
op_star
id|rx_buf
suffix:semicolon
multiline_comment|/* ring buffer */
DECL|member|tx_buf
r_int
r_char
op_star
id|tx_buf
suffix:semicolon
DECL|member|read_wait
id|wait_queue_head_t
id|read_wait
suffix:semicolon
singleline_comment|//struct wait_queue *read_wait;
DECL|member|rx_first
r_struct
id|r3964_block_header
op_star
id|rx_first
suffix:semicolon
DECL|member|rx_last
r_struct
id|r3964_block_header
op_star
id|rx_last
suffix:semicolon
DECL|member|tx_first
r_struct
id|r3964_block_header
op_star
id|tx_first
suffix:semicolon
DECL|member|tx_last
r_struct
id|r3964_block_header
op_star
id|tx_last
suffix:semicolon
DECL|member|tx_position
r_int
r_int
id|tx_position
suffix:semicolon
DECL|member|rx_position
r_int
r_int
id|rx_position
suffix:semicolon
DECL|member|last_rx
r_int
r_char
id|last_rx
suffix:semicolon
DECL|member|bcc
r_int
r_char
id|bcc
suffix:semicolon
DECL|member|blocks_in_rx_queue
r_int
r_int
id|blocks_in_rx_queue
suffix:semicolon
DECL|member|firstClient
r_struct
id|r3964_client_info
op_star
id|firstClient
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|count_down
r_int
id|count_down
suffix:semicolon
DECL|member|nRetry
r_int
id|nRetry
suffix:semicolon
DECL|member|bh_1
r_struct
id|tq_struct
id|bh_1
suffix:semicolon
DECL|member|bh_2
r_struct
id|tq_struct
id|bh_2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;
macro_line|#endif
eof
