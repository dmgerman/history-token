multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                      L I N K&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra / Jeremy Rolls&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _link_h
DECL|macro|_link_h
mdefine_line|#define _link_h 1
macro_line|#ifndef lint
macro_line|#ifdef SCCS_LABELS
multiline_comment|/* static char *_rio_link_h_sccs = &quot;@(#)link.h&t;1.15&quot;; */
macro_line|#endif
macro_line|#endif
multiline_comment|/*************************************************&n; * Define the Link Status stuff&n; ************************************************/
DECL|macro|LRT_ACTIVE
mdefine_line|#define LRT_ACTIVE         ((ushort) 0x01)
DECL|macro|LRT_SPARE1
mdefine_line|#define LRT_SPARE1         ((ushort) 0x02)
DECL|macro|INTRO_RCVD
mdefine_line|#define INTRO_RCVD         ((ushort) 0x04)
DECL|macro|FORCED_DISCONNECT
mdefine_line|#define FORCED_DISCONNECT  ((ushort) 0x08)
DECL|macro|LRT_SPARE2
mdefine_line|#define LRT_SPARE2&t;   ((ushort) 0x80)
DECL|macro|TOP_OF_RTA_RAM
mdefine_line|#define TOP_OF_RTA_RAM     ((ushort) 0x7000)
DECL|macro|HOST_SERIAL_POINTER
mdefine_line|#define HOST_SERIAL_POINTER (unsigned char **) (TOP_OF_RTA_RAM - 2 * sizeof (ushort))
multiline_comment|/* Flags for ltt_status */
DECL|macro|WAITING_ACK
mdefine_line|#define  WAITING_ACK&t;&t;(ushort) 0x0001
DECL|macro|DATA_SENT
mdefine_line|#define  DATA_SENT&t;&t;(ushort) 0x0002
DECL|macro|WAITING_RUP
mdefine_line|#define  WAITING_RUP&t;&t;(ushort) 0x0004
DECL|macro|WAITING_RETRY
mdefine_line|#define  WAITING_RETRY&t;&t;(ushort) 0x0008
DECL|macro|WAITING_TOPOLOGY
mdefine_line|#define  WAITING_TOPOLOGY&t;(ushort) 0x0010
DECL|macro|SEND_SYNC
mdefine_line|#define  SEND_SYNC&t;&t;(ushort) 0x0020
DECL|macro|FOAD_THIS_LINK
mdefine_line|#define  FOAD_THIS_LINK&t;&t;(ushort) 0x0040
DECL|macro|REQUEST_SYNC
mdefine_line|#define  REQUEST_SYNC&t;&t;(ushort) 0x0080
DECL|macro|REMOTE_DYING
mdefine_line|#define  REMOTE_DYING&t;&t;(ushort) 0x0100
DECL|macro|DIE_NOW
mdefine_line|#define  DIE_NOW&t;&t;(ushort) 0x0200
multiline_comment|/* Boot request stuff */
DECL|macro|BOOT_REQUEST
mdefine_line|#define BOOT_REQUEST       ((ushort) 0)    /* Request for a boot */
DECL|macro|BOOT_ABORT
mdefine_line|#define BOOT_ABORT         ((ushort) 1)    /* Abort a boot */
DECL|macro|BOOT_SEQUENCE
mdefine_line|#define BOOT_SEQUENCE      ((ushort) 2)    /* Packet with the number of packets&n;                                              and load address */
DECL|macro|BOOT_COMPLETED
mdefine_line|#define BOOT_COMPLETED     ((ushort) 3)    /* Boot completed */
multiline_comment|/* States that a link can be in */
DECL|macro|LINK_DISCONNECTED
mdefine_line|#define&t;LINK_DISCONNECTED  ((ushort) 0)    /* Disconnected */
DECL|macro|LINK_BOOT1
mdefine_line|#define LINK_BOOT1         ((ushort) 1)    /* Trying to send 1st stage boot */
DECL|macro|LINK_BOOT2
mdefine_line|#define LINK_BOOT2         ((ushort) 2)    /* Trying to send 2nd stage boot */
DECL|macro|LINK_BOOT2WAIT
mdefine_line|#define LINK_BOOT2WAIT     ((ushort) 3)    /* Waiting for selftest results */
DECL|macro|LINK_BOOT3
mdefine_line|#define LINK_BOOT3         ((ushort) 4)    /* Trying to send 3rd stage boots */
DECL|macro|LINK_SYNC
mdefine_line|#define LINK_SYNC          ((ushort) 5)    /* Syncing */
DECL|macro|LINK_INTRO
mdefine_line|#define LINK_INTRO         ((ushort) 10)    /* Introductory packet */
DECL|macro|LINK_SUPPLYID
mdefine_line|#define LINK_SUPPLYID      ((ushort) 11)    /* Trying to supply an ID */
DECL|macro|LINK_TOPOLOGY
mdefine_line|#define LINK_TOPOLOGY      ((ushort) 12)    /* Send a topology update */
DECL|macro|LINK_REQUESTID
mdefine_line|#define LINK_REQUESTID     ((ushort) 13)    /* Waiting for an ID */
DECL|macro|LINK_CONNECTED
mdefine_line|#define LINK_CONNECTED     ((ushort) 14)    /* Connected */
DECL|macro|LINK_INTERCONNECT
mdefine_line|#define LINK_INTERCONNECT  ((ushort) 20)   /* Subnets interconnected */
DECL|macro|LINK_SPARE
mdefine_line|#define LINK_SPARE&t;   ((ushort) 40)
multiline_comment|/*&n;** Set the default timeout for link communications.&n;*/
DECL|macro|LINKTIMEOUT
mdefine_line|#define&t;LINKTIMEOUT&t;&t;(400 * MILLISECOND)
multiline_comment|/*&n;** LED stuff&n;*/
macro_line|#if defined(RTA)
DECL|macro|LED_OFF
mdefine_line|#define LED_OFF            ((ushort) 0)    /* LED off */
DECL|macro|LED_RED
mdefine_line|#define LED_RED            ((ushort) 1)    /* LED Red */
DECL|macro|LED_GREEN
mdefine_line|#define LED_GREEN          ((ushort) 2)    /* LED Green */
DECL|macro|LED_ORANGE
mdefine_line|#define LED_ORANGE         ((ushort) 4)    /* LED Orange */
DECL|macro|LED_1TO8_OPEN
mdefine_line|#define LED_1TO8_OPEN      ((ushort) 1)    /* Port 1-&gt;8 LED on */
DECL|macro|LED_9TO16_OPEN
mdefine_line|#define LED_9TO16_OPEN     ((ushort) 2)    /* Port 9-&gt;16 LED on */
DECL|macro|LED_SET_COLOUR
mdefine_line|#define LED_SET_COLOUR(colour)&t;(link-&gt;led = (colour))
DECL|macro|LED_OR_COLOUR
mdefine_line|#define LED_OR_COLOUR(colour)&t;(link-&gt;led |= (colour))
DECL|macro|LED_TIMEOUT
mdefine_line|#define LED_TIMEOUT(time)    (link-&gt;led_timeout = RioTimePlus(RioTime(),(time)))
macro_line|#else
DECL|macro|LED_SET_COLOUR
mdefine_line|#define LED_SET_COLOUR(colour)
DECL|macro|LED_OR_COLOUR
mdefine_line|#define LED_OR_COLOUR(colour)
DECL|macro|LED_TIMEOUT
mdefine_line|#define LED_TIMEOUT(time)
macro_line|#endif /* RTA */
DECL|struct|LPB
r_struct
id|LPB
(brace
DECL|member|link_number
id|WORD
id|link_number
suffix:semicolon
multiline_comment|/* Link Number */
DECL|member|in_ch
id|Channel_ptr
id|in_ch
suffix:semicolon
multiline_comment|/* Link In Channel */
DECL|member|out_ch
id|Channel_ptr
id|out_ch
suffix:semicolon
multiline_comment|/* Link Out Channel */
macro_line|#ifdef RTA
DECL|member|stat_led
id|uchar
id|stat_led
suffix:semicolon
multiline_comment|/* Port open leds */
DECL|member|led
id|uchar
id|led
suffix:semicolon
multiline_comment|/* True, light led! */
macro_line|#endif
DECL|member|attached_serial
id|BYTE
id|attached_serial
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Attached serial number */
DECL|member|attached_host_serial
id|BYTE
id|attached_host_serial
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Serial number of Host who&n;                                                    booted the other end */
DECL|member|descheduled
id|WORD
id|descheduled
suffix:semicolon
multiline_comment|/* Currently Descheduled */
DECL|member|state
id|WORD
id|state
suffix:semicolon
multiline_comment|/* Current state */
DECL|member|send_poll
id|WORD
id|send_poll
suffix:semicolon
multiline_comment|/* Send a Poll Packet */
DECL|member|ltt_p
id|Process_ptr
id|ltt_p
suffix:semicolon
multiline_comment|/* Process Descriptor */
DECL|member|lrt_p
id|Process_ptr
id|lrt_p
suffix:semicolon
multiline_comment|/* Process Descriptor */
DECL|member|lrt_status
id|WORD
id|lrt_status
suffix:semicolon
multiline_comment|/* Current lrt status */
DECL|member|ltt_status
id|WORD
id|ltt_status
suffix:semicolon
multiline_comment|/* Current ltt status */
DECL|member|timeout
id|WORD
id|timeout
suffix:semicolon
multiline_comment|/* Timeout value */
DECL|member|topology
id|WORD
id|topology
suffix:semicolon
multiline_comment|/* Topology bits */
DECL|member|mon_ltt
id|WORD
id|mon_ltt
suffix:semicolon
DECL|member|mon_lrt
id|WORD
id|mon_lrt
suffix:semicolon
DECL|member|WaitNoBoot
id|WORD
id|WaitNoBoot
suffix:semicolon
multiline_comment|/* Secs to hold off booting */
DECL|member|add_packet_list
id|PKT_ptr
id|add_packet_list
suffix:semicolon
multiline_comment|/* Add packets to here */
DECL|member|remove_packet_list
id|PKT_ptr
id|remove_packet_list
suffix:semicolon
multiline_comment|/* Send packets from here */
macro_line|#ifdef RTA
macro_line|#ifdef DCIRRUS
DECL|macro|QBUFS_PER_REDIRECT
mdefine_line|#define    QBUFS_PER_REDIRECT (4 / PKTS_PER_BUFFER + 1) 
macro_line|#else
DECL|macro|QBUFS_PER_REDIRECT
mdefine_line|#define    QBUFS_PER_REDIRECT (8 / PKTS_PER_BUFFER + 1) 
macro_line|#endif
DECL|member|rd_add
id|PKT_ptr_ptr
id|rd_add
suffix:semicolon
multiline_comment|/* Add a new Packet here */
DECL|member|rd_add_qb
id|Q_BUF_ptr
id|rd_add_qb
suffix:semicolon
multiline_comment|/* Pointer to the add Q buf */
DECL|member|rd_add_st_qbb
id|PKT_ptr_ptr
id|rd_add_st_qbb
suffix:semicolon
multiline_comment|/* Pointer to start of the Q&squot;s buf */
DECL|member|rd_add_end_qbb
id|PKT_ptr_ptr
id|rd_add_end_qbb
suffix:semicolon
multiline_comment|/* Pointer to the end of the Q&squot;s buf */
DECL|member|rd_remove
id|PKT_ptr_ptr
id|rd_remove
suffix:semicolon
multiline_comment|/* Remove a Packet here */
DECL|member|rd_remove_qb
id|Q_BUF_ptr
id|rd_remove_qb
suffix:semicolon
multiline_comment|/* Pointer to the remove Q buf */
DECL|member|rd_remove_st_qbb
id|PKT_ptr_ptr
id|rd_remove_st_qbb
suffix:semicolon
multiline_comment|/* Pointer to the start of the Q buf */
DECL|member|rd_remove_end_qbb
id|PKT_ptr_ptr
id|rd_remove_end_qbb
suffix:semicolon
multiline_comment|/* Pointer to the end of the Q buf */
DECL|member|pkts_in_q
id|ushort
id|pkts_in_q
suffix:semicolon
multiline_comment|/* Packets in queue */
macro_line|#endif
DECL|member|lrt_fail_chan
id|Channel_ptr
id|lrt_fail_chan
suffix:semicolon
multiline_comment|/* Lrt&squot;s failure channel */
DECL|member|ltt_fail_chan
id|Channel_ptr
id|ltt_fail_chan
suffix:semicolon
multiline_comment|/* Ltt&squot;s failure channel */
macro_line|#if defined (HOST) || defined (INKERNEL)
multiline_comment|/* RUP structure for HOST to driver communications */
DECL|member|rup
r_struct
id|RUP
id|rup
suffix:semicolon
macro_line|#endif
DECL|member|link_rup
r_struct
id|RUP
id|link_rup
suffix:semicolon
multiline_comment|/* RUP for the link (POLL,&n;                                                    topology etc.) */
DECL|member|attached_link
id|WORD
id|attached_link
suffix:semicolon
multiline_comment|/* Number of attached link */
DECL|member|csum_errors
id|WORD
id|csum_errors
suffix:semicolon
multiline_comment|/* csum errors */
DECL|member|num_disconnects
id|WORD
id|num_disconnects
suffix:semicolon
multiline_comment|/* number of disconnects */
DECL|member|num_sync_rcvd
id|WORD
id|num_sync_rcvd
suffix:semicolon
multiline_comment|/* # sync&squot;s received */
DECL|member|num_sync_rqst
id|WORD
id|num_sync_rqst
suffix:semicolon
multiline_comment|/* # sync requests */
DECL|member|num_tx
id|WORD
id|num_tx
suffix:semicolon
multiline_comment|/* Num pkts sent */
DECL|member|num_rx
id|WORD
id|num_rx
suffix:semicolon
multiline_comment|/* Num pkts received */
DECL|member|module_attached
id|WORD
id|module_attached
suffix:semicolon
multiline_comment|/* Module tpyes of attached */
DECL|member|led_timeout
id|WORD
id|led_timeout
suffix:semicolon
multiline_comment|/* LED timeout */
DECL|member|first_port
id|WORD
id|first_port
suffix:semicolon
multiline_comment|/* First port to service */
DECL|member|last_port
id|WORD
id|last_port
suffix:semicolon
multiline_comment|/* Last port to service */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
