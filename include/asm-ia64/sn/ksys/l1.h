multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#ifndef _ASM_SN_KSYS_L1_H
DECL|macro|_ASM_SN_KSYS_L1_H
mdefine_line|#define _ASM_SN_KSYS_L1_H
macro_line|#include &lt;asm/sn/vector.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/sn/sv.h&gt;
DECL|macro|BRL1_QSIZE
mdefine_line|#define BRL1_QSIZE&t;128&t;/* power of 2 is more efficient */
DECL|macro|BRL1_BUFSZ
mdefine_line|#define BRL1_BUFSZ&t;264&t;/* needs to be large enough&n;&t;&t;&t;&t; * to hold 2 flags, escaped&n;&t;&t;&t;&t; * CRC, type/subchannel byte,&n;&t;&t;&t;&t; * and escaped payload&n;&t;&t;&t;&t; */
DECL|macro|BRL1_IQS
mdefine_line|#define BRL1_IQS          32
DECL|macro|BRL1_OQS
mdefine_line|#define BRL1_OQS          4
DECL|struct|sc_cq_s
r_typedef
r_struct
id|sc_cq_s
(brace
DECL|member|buf
id|u_char
id|buf
(braket
id|BRL1_QSIZE
)braket
suffix:semicolon
DECL|member|ipos
DECL|member|opos
DECL|member|tent_next
r_int
id|ipos
comma
id|opos
comma
id|tent_next
suffix:semicolon
DECL|typedef|sc_cq_t
)brace
id|sc_cq_t
suffix:semicolon
multiline_comment|/* An l1sc_t struct can be associated with the local (C-brick) L1 or an L1&n; * on an R-brick.  In the R-brick case, the l1sc_t records a vector path&n; * to the R-brick&squot;s junk bus UART.  In the C-brick case, we just use the&n; * following flag to denote the local uart.&n; *&n; * This value can&squot;t be confused with a network vector because the least-&n; * significant nibble of a network vector cannot be greater than 8.&n; */
DECL|macro|BRL1_LOCALHUB_UART
mdefine_line|#define BRL1_LOCALHUB_UART&t;((net_vec_t)0xf)
multiline_comment|/* L1&lt;-&gt;Bedrock reserved subchannels */
multiline_comment|/* console channels */
DECL|macro|SC_CONS_CPU0
mdefine_line|#define SC_CONS_CPU0    0x00
DECL|macro|SC_CONS_CPU1
mdefine_line|#define SC_CONS_CPU1    0x01
DECL|macro|SC_CONS_CPU2
mdefine_line|#define SC_CONS_CPU2    0x02
DECL|macro|SC_CONS_CPU3
mdefine_line|#define SC_CONS_CPU3    0x03
DECL|macro|L1_ELSCUART_SUBCH
mdefine_line|#define L1_ELSCUART_SUBCH(p)&t;(p)
DECL|macro|L1_ELSCUART_CPU
mdefine_line|#define L1_ELSCUART_CPU(ch)&t;(ch)
DECL|macro|SC_CONS_SYSTEM
mdefine_line|#define SC_CONS_SYSTEM  CPUS_PER_NODE
multiline_comment|/* mapping subchannels to queues */
DECL|macro|MAP_IQ
mdefine_line|#define MAP_IQ(s)       (s)
DECL|macro|MAP_OQ
mdefine_line|#define MAP_OQ(s)       (s)
DECL|macro|BRL1_NUM_SUBCHANS
mdefine_line|#define BRL1_NUM_SUBCHANS 32
DECL|macro|BRL1_CMD_SUBCH
mdefine_line|#define BRL1_CMD_SUBCH&t;  16
DECL|macro|BRL1_EVENT_SUBCH
mdefine_line|#define BRL1_EVENT_SUBCH  (BRL1_NUM_SUBCHANS - 1)
DECL|macro|BRL1_SUBCH_RSVD
mdefine_line|#define BRL1_SUBCH_RSVD   0
DECL|macro|BRL1_SUBCH_FREE
mdefine_line|#define BRL1_SUBCH_FREE   (-1)
multiline_comment|/* constants for L1 hwgraph vertex info */
DECL|macro|CBRICK_L1
mdefine_line|#define CBRICK_L1&t;(__psint_t)1
DECL|macro|IOBRICK_L1
mdefine_line|#define IOBRICK_L1&t;(__psint_t)2
DECL|macro|RBRICK_L1
mdefine_line|#define RBRICK_L1&t;(__psint_t)3
r_struct
id|l1sc_s
suffix:semicolon
multiline_comment|/* Saved off interrupt frame */
DECL|struct|brl1_intr_frame
r_typedef
r_struct
id|brl1_intr_frame
(brace
DECL|member|bf_irq
r_int
id|bf_irq
suffix:semicolon
multiline_comment|/* irq received */
DECL|member|bf_dev_id
r_void
op_star
id|bf_dev_id
suffix:semicolon
multiline_comment|/* device information */
DECL|member|bf_regs
r_struct
id|pt_regs
op_star
id|bf_regs
suffix:semicolon
multiline_comment|/* register frame */
DECL|typedef|brl1_intr_frame_t
)brace
id|brl1_intr_frame_t
suffix:semicolon
DECL|typedef|brl1_notif_t
r_typedef
r_void
(paren
op_star
id|brl1_notif_t
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_struct
id|l1sc_s
op_star
comma
r_int
)paren
suffix:semicolon
DECL|typedef|brl1_uartf_t
r_typedef
r_int
(paren
op_star
id|brl1_uartf_t
)paren
(paren
r_struct
id|l1sc_s
op_star
)paren
suffix:semicolon
multiline_comment|/* structure for controlling a subchannel */
DECL|struct|brl1_sch_s
r_typedef
r_struct
id|brl1_sch_s
(brace
DECL|member|use
r_int
id|use
suffix:semicolon
multiline_comment|/* if this subchannel is free,&n;&t;&t;&t;&t; * use == BRL1_SUBCH_FREE */
DECL|member|target
id|uint
id|target
suffix:semicolon
multiline_comment|/* type, rack and slot of component to&n;&t;&t;&t;&t; * which this subchannel is directed */
DECL|member|packet_arrived
id|atomic_t
id|packet_arrived
suffix:semicolon
multiline_comment|/* true if packet arrived on&n;&t;&t;&t;&t; * this subchannel */
DECL|member|iqp
id|sc_cq_t
op_star
id|iqp
suffix:semicolon
multiline_comment|/* input queue for this subchannel */
DECL|member|arrive_sv
id|sv_t
id|arrive_sv
suffix:semicolon
multiline_comment|/* used to wait for a packet */
DECL|member|data_lock
id|spinlock_t
id|data_lock
suffix:semicolon
multiline_comment|/* synchronize access to input queues and&n;&t;&t;&t;&t; * other fields of the brl1_sch_s struct */
DECL|member|tx_notify
id|brl1_notif_t
id|tx_notify
suffix:semicolon
multiline_comment|/* notify higher layer that transmission may &n;&t;&t;&t;&t; * continue */
DECL|member|rx_notify
id|brl1_notif_t
id|rx_notify
suffix:semicolon
multiline_comment|/* notify higher layer that a packet has been&n;&t;&t;&t;&t; * received */
DECL|member|irq_frame
id|brl1_intr_frame_t
id|irq_frame
suffix:semicolon
multiline_comment|/* saved off irq information */
DECL|typedef|brl1_sch_t
)brace
id|brl1_sch_t
suffix:semicolon
multiline_comment|/* br&lt;-&gt;l1 protocol states */
DECL|macro|BRL1_IDLE
mdefine_line|#define BRL1_IDLE&t;0
DECL|macro|BRL1_FLAG
mdefine_line|#define BRL1_FLAG&t;1
DECL|macro|BRL1_HDR
mdefine_line|#define BRL1_HDR&t;2
DECL|macro|BRL1_BODY
mdefine_line|#define BRL1_BODY&t;3
DECL|macro|BRL1_ESC
mdefine_line|#define BRL1_ESC&t;4
DECL|macro|BRL1_RESET
mdefine_line|#define BRL1_RESET&t;7
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * l1sc_t structure-- tracks protocol state, open subchannels, etc.&n; */
DECL|struct|l1sc_s
r_typedef
r_struct
id|l1sc_s
(brace
DECL|member|nasid
id|nasid_t
id|nasid
suffix:semicolon
multiline_comment|/* nasid with which this instance&n;&t;&t;&t;&t; * of the structure is associated */
DECL|member|modid
id|moduleid_t
id|modid
suffix:semicolon
multiline_comment|/* module id of this brick */
DECL|member|verbose
id|u_char
id|verbose
suffix:semicolon
multiline_comment|/* non-zero if elscuart routines should&n;&t;&t;&t;&t; * prefix output */
DECL|member|uart
id|net_vec_t
id|uart
suffix:semicolon
multiline_comment|/* vector path to UART, or BRL1_LOCALUART */
DECL|member|sent
r_int
id|sent
suffix:semicolon
multiline_comment|/* number of characters sent */
DECL|member|send_len
r_int
id|send_len
suffix:semicolon
multiline_comment|/* number of characters in send buf */
DECL|member|putc_f
id|brl1_uartf_t
id|putc_f
suffix:semicolon
multiline_comment|/* pointer to UART putc function */
DECL|member|getc_f
id|brl1_uartf_t
id|getc_f
suffix:semicolon
multiline_comment|/* pointer to UART getc function */
DECL|member|send_lock
id|spinlock_t
id|send_lock
suffix:semicolon
multiline_comment|/* arbitrates send synchronization */
DECL|member|recv_lock
id|spinlock_t
id|recv_lock
suffix:semicolon
multiline_comment|/* arbitrates uart receive access */
DECL|member|subch_lock
id|spinlock_t
id|subch_lock
suffix:semicolon
multiline_comment|/* arbitrates subchannel allocation */
DECL|member|intr_cpu
id|cpuid_t
id|intr_cpu
suffix:semicolon
multiline_comment|/* cpu that receives L1 interrupts */
DECL|member|send_in_use
id|u_char
id|send_in_use
suffix:semicolon
multiline_comment|/* non-zero if send buffer contains an&n;&t;&t;&t;&t; * unsent or partially-sent  packet */
DECL|member|fifo_space
id|u_char
id|fifo_space
suffix:semicolon
multiline_comment|/* current depth of UART send FIFO */
DECL|member|brl1_state
id|u_char
id|brl1_state
suffix:semicolon
multiline_comment|/* current state of the receive side */
DECL|member|brl1_last_hdr
id|u_char
id|brl1_last_hdr
suffix:semicolon
multiline_comment|/* last header byte received */
DECL|member|send
r_char
id|send
(braket
id|BRL1_BUFSZ
)braket
suffix:semicolon
multiline_comment|/* send buffer */
DECL|member|sol
r_int
id|sol
suffix:semicolon
multiline_comment|/* &quot;start of line&quot; (see elscuart routines) */
DECL|member|cons_listen
r_int
id|cons_listen
suffix:semicolon
multiline_comment|/* non-zero if the elscuart interface should&n;&t;&t;&t;&t; * also check the system console subchannel */
DECL|member|subch
id|brl1_sch_t
id|subch
(braket
id|BRL1_NUM_SUBCHANS
)braket
suffix:semicolon
multiline_comment|/* subchannels provided by link */
DECL|member|garbage_q
id|sc_cq_t
id|garbage_q
suffix:semicolon
multiline_comment|/* a place to put unsolicited packets */
DECL|member|oq
id|sc_cq_t
id|oq
(braket
id|BRL1_OQS
)braket
suffix:semicolon
multiline_comment|/* elscuart output queues */
DECL|typedef|l1sc_t
)brace
id|l1sc_t
suffix:semicolon
multiline_comment|/* error codes */
DECL|macro|BRL1_VALID
mdefine_line|#define BRL1_VALID&t;  0
DECL|macro|BRL1_FULL_Q
mdefine_line|#define BRL1_FULL_Q&t;(-1)
DECL|macro|BRL1_CRC
mdefine_line|#define BRL1_CRC&t;(-2)
DECL|macro|BRL1_PROTOCOL
mdefine_line|#define BRL1_PROTOCOL&t;(-3)
DECL|macro|BRL1_NO_MESSAGE
mdefine_line|#define BRL1_NO_MESSAGE&t;(-4)
DECL|macro|BRL1_LINK
mdefine_line|#define BRL1_LINK&t;(-5)
DECL|macro|BRL1_BUSY
mdefine_line|#define BRL1_BUSY&t;(-6)
DECL|macro|SC_SUCCESS
mdefine_line|#define SC_SUCCESS      BRL1_VALID
DECL|macro|SC_NMSG
mdefine_line|#define SC_NMSG         BRL1_NO_MESSAGE
DECL|macro|SC_BUSY
mdefine_line|#define SC_BUSY         BRL1_BUSY
DECL|macro|SC_NOPEN
mdefine_line|#define SC_NOPEN        (-7)
DECL|macro|SC_BADSUBCH
mdefine_line|#define SC_BADSUBCH     (-8)
DECL|macro|SC_TIMEDOUT
mdefine_line|#define SC_TIMEDOUT&t;(-9)
DECL|macro|SC_NSUBCH
mdefine_line|#define SC_NSUBCH&t;(-10)
multiline_comment|/* L1 Target Addresses */
multiline_comment|/*&n; * L1 commands and responses use source/target addresses that are&n; * 32 bits long.  These are broken up into multiple bitfields that&n; * specify the type of the target controller (could actually be L2&n; * L3, not just L1), the rack and bay of the target, and the task&n; * id (L1 functionality is divided into several independent &quot;tasks&quot;&n; * that can each receive command requests and transmit responses)&n; */
DECL|macro|L1_ADDR_TYPE_SHFT
mdefine_line|#define L1_ADDR_TYPE_SHFT&t;28
DECL|macro|L1_ADDR_TYPE_MASK
mdefine_line|#define L1_ADDR_TYPE_MASK&t;0xF0000000
DECL|macro|L1_ADDR_TYPE_L1
mdefine_line|#define L1_ADDR_TYPE_L1&t;&t;0x00&t;/* L1 system controller */
DECL|macro|L1_ADDR_TYPE_L2
mdefine_line|#define L1_ADDR_TYPE_L2&t;&t;0x01&t;/* L2 system controller */
DECL|macro|L1_ADDR_TYPE_L3
mdefine_line|#define L1_ADDR_TYPE_L3&t;&t;0x02&t;/* L3 system controller */
DECL|macro|L1_ADDR_TYPE_CBRICK
mdefine_line|#define L1_ADDR_TYPE_CBRICK&t;0x03&t;/* attached C brick&t;*/
DECL|macro|L1_ADDR_TYPE_IOBRICK
mdefine_line|#define L1_ADDR_TYPE_IOBRICK&t;0x04&t;/* attached I/O brick&t;*/
DECL|macro|L1_ADDR_RACK_SHFT
mdefine_line|#define L1_ADDR_RACK_SHFT&t;18
DECL|macro|L1_ADDR_RACK_MASK
mdefine_line|#define L1_ADDR_RACK_MASK&t;0x0FFC0000
DECL|macro|L1_ADDR_RACK_LOCAL
mdefine_line|#define&t;L1_ADDR_RACK_LOCAL&t;0x3ff&t;/* local brick&squot;s rack&t;*/
DECL|macro|L1_ADDR_BAY_SHFT
mdefine_line|#define L1_ADDR_BAY_SHFT&t;12
DECL|macro|L1_ADDR_BAY_MASK
mdefine_line|#define L1_ADDR_BAY_MASK&t;0x0003F000
DECL|macro|L1_ADDR_BAY_LOCAL
mdefine_line|#define&t;L1_ADDR_BAY_LOCAL&t;0x3f&t;/* local brick&squot;s bay&t;*/
DECL|macro|L1_ADDR_TASK_SHFT
mdefine_line|#define L1_ADDR_TASK_SHFT&t;0
DECL|macro|L1_ADDR_TASK_MASK
mdefine_line|#define L1_ADDR_TASK_MASK&t;0x0000001F
DECL|macro|L1_ADDR_TASK_INVALID
mdefine_line|#define L1_ADDR_TASK_INVALID&t;0x00&t;/* invalid task &t;*/
DECL|macro|L1_ADDR_TASK_IROUTER
mdefine_line|#define&t;L1_ADDR_TASK_IROUTER&t;0x01&t;/* iRouter&t;&t;*/
DECL|macro|L1_ADDR_TASK_SYS_MGMT
mdefine_line|#define L1_ADDR_TASK_SYS_MGMT&t;0x02&t;/* system management port */
DECL|macro|L1_ADDR_TASK_CMD
mdefine_line|#define L1_ADDR_TASK_CMD&t;0x03&t;/* command interpreter&t;*/
DECL|macro|L1_ADDR_TASK_ENV
mdefine_line|#define L1_ADDR_TASK_ENV&t;0x04&t;/* environmental monitor */
DECL|macro|L1_ADDR_TASK_BEDROCK
mdefine_line|#define L1_ADDR_TASK_BEDROCK&t;0x05&t;/* bedrock&t;&t;*/
DECL|macro|L1_ADDR_TASK_GENERAL
mdefine_line|#define L1_ADDR_TASK_GENERAL&t;0x06&t;/* general requests&t;*/
DECL|macro|L1_ADDR_LOCAL
mdefine_line|#define L1_ADDR_LOCAL&t;&t;&t;&t;&bslash;&n;    (L1_ADDR_TYPE_L1 &lt;&lt; L1_ADDR_TYPE_SHFT) |&t;&bslash;&n;    (L1_ADDR_RACK_LOCAL &lt;&lt; L1_ADDR_RACK_SHFT) |&t;&bslash;&n;    (L1_ADDR_BAY_LOCAL &lt;&lt; L1_ADDR_BAY_SHFT)
DECL|macro|L1_ADDR_LOCALIO
mdefine_line|#define L1_ADDR_LOCALIO&t;&t;&t;&t;&t;&bslash;&n;    (L1_ADDR_TYPE_IOBRICK &lt;&lt; L1_ADDR_TYPE_SHFT) |&t;&bslash;&n;    (L1_ADDR_RACK_LOCAL &lt;&lt; L1_ADDR_RACK_SHFT) |&t;&t;&bslash;&n;    (L1_ADDR_BAY_LOCAL &lt;&lt; L1_ADDR_BAY_SHFT)
DECL|macro|L1_ADDR_LOCAL_SHFT
mdefine_line|#define L1_ADDR_LOCAL_SHFT&t;L1_ADDR_BAY_SHFT
multiline_comment|/* response argument types */
DECL|macro|L1_ARG_INT
mdefine_line|#define L1_ARG_INT&t;&t;0x00&t;/* 4-byte integer (big-endian)&t;*/
DECL|macro|L1_ARG_ASCII
mdefine_line|#define L1_ARG_ASCII&t;&t;0x01&t;/* null-terminated ASCII string */
DECL|macro|L1_ARG_UNKNOWN
mdefine_line|#define L1_ARG_UNKNOWN&t;&t;0x80&t;/* unknown data type.  The low&n;&t;&t;&t;&t;&t; * 7 bits will contain the data&n;&t;&t;&t;&t;&t; * length.&t;&t;&t;*/
multiline_comment|/* response codes */
DECL|macro|L1_RESP_OK
mdefine_line|#define L1_RESP_OK&t;    0&t;/* no problems encountered      */
DECL|macro|L1_RESP_IROUTER
mdefine_line|#define L1_RESP_IROUTER&t;(-  1)&t;/* iRouter error&t;        */
DECL|macro|L1_RESP_ARGC
mdefine_line|#define L1_RESP_ARGC&t;(-100)&t;/* arg count mismatch&t;        */
DECL|macro|L1_RESP_REQC
mdefine_line|#define L1_RESP_REQC&t;(-101)&t;/* bad request code&t;        */
DECL|macro|L1_RESP_NAVAIL
mdefine_line|#define L1_RESP_NAVAIL&t;(-104)&t;/* requested data not available */
DECL|macro|L1_RESP_ARGVAL
mdefine_line|#define L1_RESP_ARGVAL&t;(-105)  /* arg value out of range       */
DECL|macro|L1_RESP_INVAL
mdefine_line|#define L1_RESP_INVAL   (-107)  /* requested data invalid       */
multiline_comment|/* L1 general requests */
multiline_comment|/* request codes */
DECL|macro|L1_REQ_RDBG
mdefine_line|#define&t;L1_REQ_RDBG&t;&t;0x0001&t;/* read debug switches&t;*/
DECL|macro|L1_REQ_RRACK
mdefine_line|#define L1_REQ_RRACK&t;&t;0x0002&t;/* read brick rack &amp; bay */
DECL|macro|L1_REQ_RRBT
mdefine_line|#define L1_REQ_RRBT&t;&t;0x0003  /* read brick rack, bay &amp; type */
DECL|macro|L1_REQ_SER_NUM
mdefine_line|#define L1_REQ_SER_NUM&t;&t;0x0004  /* read brick serial number */
DECL|macro|L1_REQ_FW_REV
mdefine_line|#define L1_REQ_FW_REV&t;&t;0x0005  /* read L1 firmware revision */
DECL|macro|L1_REQ_EEPROM
mdefine_line|#define L1_REQ_EEPROM&t;&t;0x0006  /* read EEPROM info */
DECL|macro|L1_REQ_EEPROM_FMT
mdefine_line|#define L1_REQ_EEPROM_FMT&t;0x0007  /* get EEPROM data format &amp; size */
DECL|macro|L1_REQ_SYS_SERIAL
mdefine_line|#define L1_REQ_SYS_SERIAL&t;0x0008&t;/* read system serial number */
DECL|macro|L1_REQ_PARTITION_GET
mdefine_line|#define L1_REQ_PARTITION_GET&t;0x0009&t;/* read partition id */
DECL|macro|L1_REQ_PORTSPEED
mdefine_line|#define L1_REQ_PORTSPEED&t;0x000a&t;/* get ioport speed */
DECL|macro|L1_REQ_CONS_SUBCH
mdefine_line|#define L1_REQ_CONS_SUBCH&t;0x1002  /* select this node&squot;s console &n;&t;&t;&t;&t;&t;   subchannel */
DECL|macro|L1_REQ_CONS_NODE
mdefine_line|#define L1_REQ_CONS_NODE&t;0x1003  /* volunteer to be the master &n;&t;&t;&t;&t;&t;   (console-hosting) node */
DECL|macro|L1_REQ_DISP1
mdefine_line|#define L1_REQ_DISP1&t;&t;0x1004  /* write line 1 of L1 display */
DECL|macro|L1_REQ_DISP2
mdefine_line|#define L1_REQ_DISP2&t;&t;0x1005  /* write line 2 of L1 display */
DECL|macro|L1_REQ_PARTITION_SET
mdefine_line|#define L1_REQ_PARTITION_SET&t;0x1006&t;/* set partition id */
DECL|macro|L1_REQ_EVENT_SUBCH
mdefine_line|#define L1_REQ_EVENT_SUBCH&t;0x1007&t;/* set the subchannel for system&n;&t;&t;&t;&t;&t;   controller event transmission */
DECL|macro|L1_REQ_RESET
mdefine_line|#define L1_REQ_RESET&t;&t;0x2000&t;/* request a full system reset */
DECL|macro|L1_REQ_PCI_UP
mdefine_line|#define L1_REQ_PCI_UP&t;&t;0x2001  /* power up pci slot or bus */
DECL|macro|L1_REQ_PCI_DOWN
mdefine_line|#define L1_REQ_PCI_DOWN&t;&t;0x2002  /* power down pci slot or bus */
DECL|macro|L1_REQ_PCI_RESET
mdefine_line|#define L1_REQ_PCI_RESET&t;0x2003  /* reset pci bus or slot */
multiline_comment|/* L1 command interpreter requests */
multiline_comment|/* request codes */
DECL|macro|L1_REQ_EXEC_CMD
mdefine_line|#define L1_REQ_EXEC_CMD&t;&t;0x0000&t;/* interpret and execute an ASCII&n;&t;&t;&t;&t;&t;   command string */
multiline_comment|/* brick type response codes */
DECL|macro|L1_BRICKTYPE_C
mdefine_line|#define L1_BRICKTYPE_C&t;0x43
DECL|macro|L1_BRICKTYPE_I
mdefine_line|#define L1_BRICKTYPE_I&t;0x49
DECL|macro|L1_BRICKTYPE_P
mdefine_line|#define L1_BRICKTYPE_P&t;0x50
DECL|macro|L1_BRICKTYPE_R
mdefine_line|#define L1_BRICKTYPE_R  0x52
DECL|macro|L1_BRICKTYPE_X
mdefine_line|#define L1_BRICKTYPE_X  0x58
multiline_comment|/* EEPROM codes (for the &quot;read EEPROM&quot; request) */
multiline_comment|/* c brick */
DECL|macro|L1_EEP_NODE
mdefine_line|#define L1_EEP_NODE&t;&t;0x00&t;/* node board */
DECL|macro|L1_EEP_PIMM0
mdefine_line|#define L1_EEP_PIMM0&t;&t;0x01
DECL|macro|L1_EEP_PIMM
mdefine_line|#define L1_EEP_PIMM(x)&t;&t;(L1_EEP_PIMM0+(x))
DECL|macro|L1_EEP_DIMM0
mdefine_line|#define L1_EEP_DIMM0&t;&t;0x03
DECL|macro|L1_EEP_DIMM
mdefine_line|#define L1_EEP_DIMM(x)&t;&t;(L1_EEP_DIMM0+(x))
multiline_comment|/* other brick types */
DECL|macro|L1_EEP_POWER
mdefine_line|#define L1_EEP_POWER&t;&t;0x00&t;/* power board */
DECL|macro|L1_EEP_LOGIC
mdefine_line|#define L1_EEP_LOGIC&t;&t;0x01&t;/* logic board */
multiline_comment|/* info area types */
DECL|macro|L1_EEP_CHASSIS
mdefine_line|#define L1_EEP_CHASSIS&t;&t;1&t;/* chassis info area */
DECL|macro|L1_EEP_BOARD
mdefine_line|#define L1_EEP_BOARD&t;&t;2&t;/* board info area */
DECL|macro|L1_EEP_IUSE
mdefine_line|#define L1_EEP_IUSE&t;&t;3&t;/* internal use area */
DECL|macro|L1_EEP_SPD
mdefine_line|#define L1_EEP_SPD&t;&t;4&t;/* serial presence detect record */
DECL|typedef|l1addr_t
r_typedef
r_uint32
id|l1addr_t
suffix:semicolon
DECL|macro|L1_BUILD_ADDR
mdefine_line|#define L1_BUILD_ADDR(addr,at,r,s,t)&t;&t;&t;&t;&t;&bslash;&n;    (*(l1addr_t *)(addr) = ((l1addr_t)(at) &lt;&lt; L1_ADDR_TYPE_SHFT) |&t;&bslash;&n;&t;&t;&t;     ((l1addr_t)(r)  &lt;&lt; L1_ADDR_RACK_SHFT) |&t;&bslash;&n;&t;&t;&t;     ((l1addr_t)(s)  &lt;&lt; L1_ADDR_BAY_SHFT) |&t;&bslash;&n;&t;&t;&t;     ((l1addr_t)(t)  &lt;&lt; L1_ADDR_TASK_SHFT))
DECL|macro|L1_ADDRESS_TO_TASK
mdefine_line|#define L1_ADDRESS_TO_TASK(addr,trb,tsk)&t;&t;&t;&t;&bslash;&n;    (*(l1addr_t *)(addr) = (l1addr_t)(trb) |&t;&t;&t;&t;&bslash;&n;    &t;&t;&t;     ((l1addr_t)(tsk) &lt;&lt; L1_ADDR_TASK_SHFT))
DECL|macro|L1_DISPLAY_LINE_LENGTH
mdefine_line|#define L1_DISPLAY_LINE_LENGTH&t;12&t;/* L1 display characters/line */
macro_line|#ifdef L1_DISP_2LINES
DECL|macro|L1_DISPLAY_LINES
mdefine_line|#define L1_DISPLAY_LINES&t;2&t;/* number of L1 display lines */
macro_line|#else
DECL|macro|L1_DISPLAY_LINES
mdefine_line|#define L1_DISPLAY_LINES&t;1&t;/* number of L1 display lines available&n;&t;&t;&t;&t;&t; * to system software */
macro_line|#endif
DECL|macro|SC_EVENT_CLASS_MASK
mdefine_line|#define SC_EVENT_CLASS_MASK ((unsigned short)0xff00)
DECL|macro|bzero
mdefine_line|#define bzero(d, n)&t;memset((d), 0, (n))
multiline_comment|/* public interfaces to L1 system controller */
r_int
id|sc_open
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
id|uint
id|target
)paren
suffix:semicolon
r_int
id|sc_close
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
r_int
id|ch
)paren
suffix:semicolon
r_int
id|sc_construct_msg
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
r_int
id|ch
comma
r_char
op_star
id|msg
comma
r_int
id|msg_len
comma
id|uint
id|addr_task
comma
r_int
id|req_code
comma
r_int
id|req_nargs
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|sc_interpret_resp
c_func
(paren
r_char
op_star
id|resp
comma
r_int
id|resp_nargs
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|sc_send
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
r_int
id|ch
comma
r_char
op_star
id|msg
comma
r_int
id|len
comma
r_int
id|wait
)paren
suffix:semicolon
r_int
id|sc_recv
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
r_int
id|ch
comma
r_char
op_star
id|msg
comma
r_int
op_star
id|len
comma
r_uint64
id|block
)paren
suffix:semicolon
r_int
id|sc_command
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
r_int
id|ch
comma
r_char
op_star
id|cmd
comma
r_char
op_star
id|resp
comma
r_int
op_star
id|len
)paren
suffix:semicolon
r_int
id|sc_command_kern
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
r_int
id|ch
comma
r_char
op_star
id|cmd
comma
r_char
op_star
id|resp
comma
r_int
op_star
id|len
)paren
suffix:semicolon
r_int
id|sc_poll
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
r_int
id|ch
)paren
suffix:semicolon
r_void
id|sc_init
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
id|nasid_t
id|nasid
comma
id|net_vec_t
id|uart
)paren
suffix:semicolon
r_void
id|sc_intr_enable
c_func
(paren
id|l1sc_t
op_star
id|sc
)paren
suffix:semicolon
r_int
id|elsc_rack_bay_get
c_func
(paren
id|l1sc_t
op_star
id|e
comma
id|uint
op_star
id|rack
comma
id|uint
op_star
id|bay
)paren
suffix:semicolon
r_int
id|elsc_rack_bay_type_get
c_func
(paren
id|l1sc_t
op_star
id|e
comma
id|uint
op_star
id|rack
comma
id|uint
op_star
id|bay
comma
id|uint
op_star
id|brick_type
)paren
suffix:semicolon
r_int
id|elsc_cons_subch
c_func
(paren
id|l1sc_t
op_star
id|e
comma
id|uint
id|ch
)paren
suffix:semicolon
r_int
id|elsc_cons_node
c_func
(paren
id|l1sc_t
op_star
id|e
)paren
suffix:semicolon
r_int
id|elsc_display_line
c_func
(paren
id|l1sc_t
op_star
id|e
comma
r_char
op_star
id|line
comma
r_int
id|lnum
)paren
suffix:semicolon
r_extern
id|l1sc_t
op_star
id|get_elsc
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|get_l1sc
mdefine_line|#define get_l1sc&t;get_elsc
DECL|macro|get_master_l1sc
mdefine_line|#define get_master_l1sc get_l1sc
r_int
id|router_module_get
c_func
(paren
id|nasid_t
id|nasid
comma
id|net_vec_t
id|path
)paren
suffix:semicolon
r_int
id|iobrick_rack_bay_type_get
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
id|uint
op_star
id|rack
comma
id|uint
op_star
id|bay
comma
id|uint
op_star
id|brick_type
)paren
suffix:semicolon
r_int
id|iobrick_module_get
c_func
(paren
id|l1sc_t
op_star
id|sc
)paren
suffix:semicolon
r_int
id|iobrick_pci_slot_pwr
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
r_int
id|bus
comma
r_int
id|slot
comma
r_int
id|up
)paren
suffix:semicolon
r_int
id|iobrick_pci_bus_pwr
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
r_int
id|bus
comma
r_int
id|up
)paren
suffix:semicolon
r_int
id|iobrick_sc_version
c_func
(paren
id|l1sc_t
op_star
id|sc
comma
r_char
op_star
id|result
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_SN_KSYS_L1_H */
eof
