multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                 P H B     H E A D E R                        *******&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra, Jeremy Rolls&n; Date    : &n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _phb_h
DECL|macro|_phb_h
mdefine_line|#define _phb_h 1
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
multiline_comment|/* static char *_rio_phb_h_sccs = &quot;@(#)phb.h&t;1.12&quot;; */
macro_line|#endif
macro_line|#endif
multiline_comment|/*************************************************&n;  * Set the LIMIT values.&n;  ************************************************/
macro_line|#ifdef RTA
DECL|macro|RX_LIMIT
mdefine_line|#define RX_LIMIT       (ushort) 3
macro_line|#endif
macro_line|#ifdef HOST
DECL|macro|RX_LIMIT
mdefine_line|#define RX_LIMIT       (ushort) 1
macro_line|#endif
multiline_comment|/*************************************************&n; * Handshake asserted. Deasserted by the LTT(s)&n; ************************************************/
DECL|macro|PHB_HANDSHAKE_SET
mdefine_line|#define PHB_HANDSHAKE_SET      ((ushort) 0x001) /* Set by LRT */
DECL|macro|PHB_HANDSHAKE_RESET
mdefine_line|#define PHB_HANDSHAKE_RESET     ((ushort) 0x002) /* Set by ISR / driver */
DECL|macro|PHB_HANDSHAKE_FLAGS
mdefine_line|#define PHB_HANDSHAKE_FLAGS     (PHB_HANDSHAKE_RESET | PHB_HANDSHAKE_SET)
multiline_comment|/* Reset by ltt */
multiline_comment|/*************************************************&n; * Maximum number of PHB&squot;s&n; ************************************************/
macro_line|#if defined (HOST) || defined (INKERNEL)
DECL|macro|MAX_PHB
mdefine_line|#define MAX_PHB               ((ushort) 128)  /* range 0-127 */
macro_line|#else
DECL|macro|MAX_PHB
mdefine_line|#define MAX_PHB               ((ushort) 8)    /* range 0-7 */
macro_line|#endif
multiline_comment|/*************************************************&n; * Defines for the mode fields&n; ************************************************/
DECL|macro|TXPKT_INCOMPLETE
mdefine_line|#define TXPKT_INCOMPLETE        0x0001  /* Previous tx packet not completed */
DECL|macro|TXINTR_ENABLED
mdefine_line|#define TXINTR_ENABLED          0x0002  /* Tx interrupt is enabled */
DECL|macro|TX_TAB3
mdefine_line|#define TX_TAB3                 0x0004  /* TAB3 mode */
DECL|macro|TX_OCRNL
mdefine_line|#define TX_OCRNL                0x0008  /* OCRNL mode */
DECL|macro|TX_ONLCR
mdefine_line|#define TX_ONLCR                0x0010  /* ONLCR mode */
DECL|macro|TX_SENDSPACES
mdefine_line|#define TX_SENDSPACES           0x0020  /* Send n spaces command needs &n;                                           completing */
DECL|macro|TX_SENDNULL
mdefine_line|#define TX_SENDNULL             0x0040  /* Escaping NULL needs completing */
DECL|macro|TX_SENDLF
mdefine_line|#define TX_SENDLF               0x0080  /* LF -&gt; CR LF needs completing */
DECL|macro|TX_PARALLELBUG
mdefine_line|#define TX_PARALLELBUG          0x0100  /* CD1400 LF -&gt; CR LF bug on parallel&n;                                           port */
DECL|macro|TX_HANGOVER
mdefine_line|#define TX_HANGOVER             (TX_SENDSPACES | TX_SENDLF | TX_SENDNULL)
DECL|macro|TX_DTRFLOW
mdefine_line|#define TX_DTRFLOW&t;&t;0x0200&t;/* DTR tx flow control */
DECL|macro|TX_DTRFLOWED
mdefine_line|#define&t;TX_DTRFLOWED&t;&t;0x0400&t;/* DTR is low - don&squot;t allow more data&n;&t;&t;&t;&t;&t;   into the FIFO */
DECL|macro|TX_DATAINFIFO
mdefine_line|#define&t;TX_DATAINFIFO&t;&t;0x0800&t;/* There is data in the FIFO */
DECL|macro|TX_BUSY
mdefine_line|#define&t;TX_BUSY&t;&t;&t;0x1000&t;/* Data in FIFO, shift or holding regs */
DECL|macro|RX_SPARE
mdefine_line|#define RX_SPARE&t;        0x0001   /* SPARE */
DECL|macro|RXINTR_ENABLED
mdefine_line|#define RXINTR_ENABLED          0x0002   /* Rx interrupt enabled */
DECL|macro|RX_ICRNL
mdefine_line|#define RX_ICRNL                0x0008   /* ICRNL mode */
DECL|macro|RX_INLCR
mdefine_line|#define RX_INLCR                0x0010   /* INLCR mode */
DECL|macro|RX_IGNCR
mdefine_line|#define RX_IGNCR                0x0020   /* IGNCR mode */
DECL|macro|RX_CTSFLOW
mdefine_line|#define RX_CTSFLOW              0x0040   /* CTSFLOW enabled */
DECL|macro|RX_IXOFF
mdefine_line|#define RX_IXOFF                0x0080   /* IXOFF enabled */
DECL|macro|RX_CTSFLOWED
mdefine_line|#define RX_CTSFLOWED            0x0100   /* CTSFLOW and CTS dropped */
DECL|macro|RX_IXOFFED
mdefine_line|#define RX_IXOFFED              0x0200   /* IXOFF and xoff sent */
DECL|macro|RX_BUFFERED
mdefine_line|#define RX_BUFFERED&t;&t;0x0400&t; /* Try and pass on complete packets */
DECL|macro|PORT_ISOPEN
mdefine_line|#define PORT_ISOPEN             0x0001  /* Port open? */
DECL|macro|PORT_HUPCL
mdefine_line|#define PORT_HUPCL              0x0002  /* Hangup on close? */
DECL|macro|PORT_MOPENPEND
mdefine_line|#define PORT_MOPENPEND          0x0004  /* Modem open pending */
DECL|macro|PORT_ISPARALLEL
mdefine_line|#define PORT_ISPARALLEL         0x0008  /* Parallel port */
DECL|macro|PORT_BREAK
mdefine_line|#define PORT_BREAK              0x0010  /* Port on break */
DECL|macro|PORT_STATUSPEND
mdefine_line|#define PORT_STATUSPEND&t;&t;0x0020  /* Status packet pending */
DECL|macro|PORT_BREAKPEND
mdefine_line|#define PORT_BREAKPEND          0x0040  /* Break packet pending */
DECL|macro|PORT_MODEMPEND
mdefine_line|#define PORT_MODEMPEND          0x0080  /* Modem status packet pending */
DECL|macro|PORT_PARALLELBUG
mdefine_line|#define PORT_PARALLELBUG        0x0100  /* CD1400 LF -&gt; CR LF bug on parallel&n;                                           port */
DECL|macro|PORT_FULLMODEM
mdefine_line|#define PORT_FULLMODEM          0x0200  /* Full modem signals */
DECL|macro|PORT_RJ45
mdefine_line|#define PORT_RJ45               0x0400  /* RJ45 connector - no RI signal */
DECL|macro|PORT_RESTRICTED
mdefine_line|#define PORT_RESTRICTED         0x0600  /* Restricted connector - no RI / DTR */
DECL|macro|PORT_MODEMBITS
mdefine_line|#define PORT_MODEMBITS          0x0600  /* Mask for modem fields */
DECL|macro|PORT_WCLOSE
mdefine_line|#define PORT_WCLOSE             0x0800  /* Waiting for close */
DECL|macro|PORT_HANDSHAKEFIX
mdefine_line|#define&t;PORT_HANDSHAKEFIX&t;0x1000&t;/* Port has H/W flow control fix */
DECL|macro|PORT_WASPCLOSED
mdefine_line|#define&t;PORT_WASPCLOSED&t;&t;0x2000&t;/* Port closed with PCLOSE */
DECL|macro|DUMPMODE
mdefine_line|#define&t;DUMPMODE&t;&t;0x4000&t;/* Dump RTA mem */
DECL|macro|READ_REG
mdefine_line|#define&t;READ_REG&t;&t;0x8000&t;/* Read CD1400 register */
multiline_comment|/**************************************************************************&n; * PHB Structure&n; * A  few words.&n; *&n; * Normally Packets are added to the end of the list and removed from&n; * the start. The pointer tx_add points to a SPACE to put a Packet.&n; * The pointer tx_remove points to the next Packet to remove&n; *************************************************************************/
macro_line|#ifndef INKERNEL
DECL|macro|src_unit
mdefine_line|#define src_unit     u2.s2.unit
DECL|macro|src_port
mdefine_line|#define src_port     u2.s2.port
DECL|macro|dest_unit
mdefine_line|#define dest_unit    u1.s1.unit
DECL|macro|dest_port
mdefine_line|#define dest_port    u1.s1.port
macro_line|#endif
macro_line|#ifdef HOST
DECL|macro|tx_start
mdefine_line|#define tx_start     u3.s1.tx_start_ptr_ptr
DECL|macro|tx_add
mdefine_line|#define tx_add       u3.s1.tx_add_ptr_ptr
DECL|macro|tx_end
mdefine_line|#define tx_end       u3.s1.tx_end_ptr_ptr
DECL|macro|tx_remove
mdefine_line|#define tx_remove    u3.s1.tx_remove_ptr_ptr
DECL|macro|rx_start
mdefine_line|#define rx_start     u4.s1.rx_start_ptr_ptr
DECL|macro|rx_add
mdefine_line|#define rx_add       u4.s1.rx_add_ptr_ptr
DECL|macro|rx_end
mdefine_line|#define rx_end       u4.s1.rx_end_ptr_ptr
DECL|macro|rx_remove
mdefine_line|#define rx_remove    u4.s1.rx_remove_ptr_ptr
macro_line|#endif
DECL|typedef|PHB
r_typedef
r_struct
id|PHB
id|PHB
suffix:semicolon
DECL|struct|PHB
r_struct
id|PHB
(brace
macro_line|#ifdef RTA
DECL|member|port
id|ushort
id|port
suffix:semicolon
macro_line|#endif
macro_line|#ifdef INKERNEL
DECL|member|source
id|WORD
id|source
suffix:semicolon
macro_line|#else
r_union
(brace
DECL|member|source
id|ushort
id|source
suffix:semicolon
multiline_comment|/* Complete source */
r_struct
(brace
DECL|member|unit
r_int
r_char
id|unit
suffix:semicolon
multiline_comment|/* Source unit */
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
multiline_comment|/* Source port */
DECL|member|s2
)brace
id|s2
suffix:semicolon
DECL|member|u2
)brace
id|u2
suffix:semicolon
macro_line|#endif
DECL|member|handshake
id|WORD
id|handshake
suffix:semicolon
DECL|member|status
id|WORD
id|status
suffix:semicolon
DECL|member|timeout
id|NUMBER
id|timeout
suffix:semicolon
multiline_comment|/* Maximum of 1.9 seconds */
DECL|member|link
id|WORD
id|link
suffix:semicolon
multiline_comment|/* Send down this link */
macro_line|#ifdef INKERNEL
DECL|member|destination
id|WORD
id|destination
suffix:semicolon
macro_line|#else
r_union
(brace
DECL|member|destination
id|ushort
id|destination
suffix:semicolon
multiline_comment|/* Complete destination */
r_struct
(brace
DECL|member|unit
r_int
r_char
id|unit
suffix:semicolon
multiline_comment|/* Destination unit */
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
multiline_comment|/* Destination port */
DECL|member|s1
)brace
id|s1
suffix:semicolon
DECL|member|u1
)brace
id|u1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef RTA
DECL|member|tx_pkts_added
id|ushort
id|tx_pkts_added
suffix:semicolon
DECL|member|tx_pkts_removed
id|ushort
id|tx_pkts_removed
suffix:semicolon
DECL|member|tx_q_start
id|Q_BUF_ptr
id|tx_q_start
suffix:semicolon
multiline_comment|/* Start of the Q list chain */
DECL|member|num_tx_q_bufs
r_int
id|num_tx_q_bufs
suffix:semicolon
multiline_comment|/* Number of Q buffers in the chain */
DECL|member|tx_add
id|PKT_ptr_ptr
id|tx_add
suffix:semicolon
multiline_comment|/* Add a new Packet here */
DECL|member|tx_add_qb
id|Q_BUF_ptr
id|tx_add_qb
suffix:semicolon
multiline_comment|/* Pointer to the add Q buf */
DECL|member|tx_add_st_qbb
id|PKT_ptr_ptr
id|tx_add_st_qbb
suffix:semicolon
multiline_comment|/* Pointer to start of the Q&squot;s buf */
DECL|member|tx_add_end_qbb
id|PKT_ptr_ptr
id|tx_add_end_qbb
suffix:semicolon
multiline_comment|/* Pointer to the end of the Q&squot;s buf */
DECL|member|tx_remove
id|PKT_ptr_ptr
id|tx_remove
suffix:semicolon
multiline_comment|/* Remove a Packet here */
DECL|member|tx_remove_qb
id|Q_BUF_ptr
id|tx_remove_qb
suffix:semicolon
multiline_comment|/* Pointer to the remove Q buf */
DECL|member|tx_remove_st_qbb
id|PKT_ptr_ptr
id|tx_remove_st_qbb
suffix:semicolon
multiline_comment|/* Pointer to the start of the Q buf */
DECL|member|tx_remove_end_qbb
id|PKT_ptr_ptr
id|tx_remove_end_qbb
suffix:semicolon
multiline_comment|/* Pointer to the end of the Q buf */
macro_line|#endif
macro_line|#ifdef INKERNEL
DECL|member|tx_start
id|PKT_ptr_ptr
id|tx_start
suffix:semicolon
DECL|member|tx_end
id|PKT_ptr_ptr
id|tx_end
suffix:semicolon
DECL|member|tx_add
id|PKT_ptr_ptr
id|tx_add
suffix:semicolon
DECL|member|tx_remove
id|PKT_ptr_ptr
id|tx_remove
suffix:semicolon
macro_line|#endif
macro_line|#ifdef HOST
r_union
(brace
r_struct
(brace
DECL|member|tx_start_ptr_ptr
id|PKT_ptr_ptr
id|tx_start_ptr_ptr
suffix:semicolon
DECL|member|tx_end_ptr_ptr
id|PKT_ptr_ptr
id|tx_end_ptr_ptr
suffix:semicolon
DECL|member|tx_add_ptr_ptr
id|PKT_ptr_ptr
id|tx_add_ptr_ptr
suffix:semicolon
DECL|member|tx_remove_ptr_ptr
id|PKT_ptr_ptr
id|tx_remove_ptr_ptr
suffix:semicolon
DECL|member|s1
)brace
id|s1
suffix:semicolon
r_struct
(brace
DECL|member|tx_start_ptr
id|ushort
op_star
id|tx_start_ptr
suffix:semicolon
DECL|member|tx_end_ptr
id|ushort
op_star
id|tx_end_ptr
suffix:semicolon
DECL|member|tx_add_ptr
id|ushort
op_star
id|tx_add_ptr
suffix:semicolon
DECL|member|tx_remove_ptr
id|ushort
op_star
id|tx_remove_ptr
suffix:semicolon
DECL|member|s2
)brace
id|s2
suffix:semicolon
DECL|member|u3
)brace
id|u3
suffix:semicolon
macro_line|#endif
macro_line|#ifdef  RTA
DECL|member|rx_pkts_added
id|ushort
id|rx_pkts_added
suffix:semicolon
DECL|member|rx_pkts_removed
id|ushort
id|rx_pkts_removed
suffix:semicolon
DECL|member|rx_q_start
id|Q_BUF_ptr
id|rx_q_start
suffix:semicolon
multiline_comment|/* Start of the Q list chain */
DECL|member|num_rx_q_bufs
r_int
id|num_rx_q_bufs
suffix:semicolon
multiline_comment|/* Number of Q buffers in the chain */
DECL|member|rx_add
id|PKT_ptr_ptr
id|rx_add
suffix:semicolon
multiline_comment|/* Add a new Packet here */
DECL|member|rx_add_qb
id|Q_BUF_ptr
id|rx_add_qb
suffix:semicolon
multiline_comment|/* Pointer to the add Q buf */
DECL|member|rx_add_st_qbb
id|PKT_ptr_ptr
id|rx_add_st_qbb
suffix:semicolon
multiline_comment|/* Pointer to start of the Q&squot;s buf */
DECL|member|rx_add_end_qbb
id|PKT_ptr_ptr
id|rx_add_end_qbb
suffix:semicolon
multiline_comment|/* Pointer to the end of the Q&squot;s buf */
DECL|member|rx_remove
id|PKT_ptr_ptr
id|rx_remove
suffix:semicolon
multiline_comment|/* Remove a Packet here */
DECL|member|rx_remove_qb
id|Q_BUF_ptr
id|rx_remove_qb
suffix:semicolon
multiline_comment|/* Pointer to the remove Q buf */
DECL|member|rx_remove_st_qbb
id|PKT_ptr_ptr
id|rx_remove_st_qbb
suffix:semicolon
multiline_comment|/* Pointer to the start of the Q buf */
DECL|member|rx_remove_end_qbb
id|PKT_ptr_ptr
id|rx_remove_end_qbb
suffix:semicolon
multiline_comment|/* Pointer to the end of the Q buf */
macro_line|#endif
macro_line|#ifdef INKERNEL
DECL|member|rx_start
id|PKT_ptr_ptr
id|rx_start
suffix:semicolon
DECL|member|rx_end
id|PKT_ptr_ptr
id|rx_end
suffix:semicolon
DECL|member|rx_add
id|PKT_ptr_ptr
id|rx_add
suffix:semicolon
DECL|member|rx_remove
id|PKT_ptr_ptr
id|rx_remove
suffix:semicolon
macro_line|#endif
macro_line|#ifdef HOST
r_union
(brace
r_struct
(brace
DECL|member|rx_start_ptr_ptr
id|PKT_ptr_ptr
id|rx_start_ptr_ptr
suffix:semicolon
DECL|member|rx_end_ptr_ptr
id|PKT_ptr_ptr
id|rx_end_ptr_ptr
suffix:semicolon
DECL|member|rx_add_ptr_ptr
id|PKT_ptr_ptr
id|rx_add_ptr_ptr
suffix:semicolon
DECL|member|rx_remove_ptr_ptr
id|PKT_ptr_ptr
id|rx_remove_ptr_ptr
suffix:semicolon
DECL|member|s1
)brace
id|s1
suffix:semicolon
r_struct
(brace
DECL|member|rx_start_ptr
id|ushort
op_star
id|rx_start_ptr
suffix:semicolon
DECL|member|rx_end_ptr
id|ushort
op_star
id|rx_end_ptr
suffix:semicolon
DECL|member|rx_add_ptr
id|ushort
op_star
id|rx_add_ptr
suffix:semicolon
DECL|member|rx_remove_ptr
id|ushort
op_star
id|rx_remove_ptr
suffix:semicolon
DECL|member|s2
)brace
id|s2
suffix:semicolon
DECL|member|u4
)brace
id|u4
suffix:semicolon
macro_line|#endif
macro_line|#ifdef RTA                              /* some fields for the remotes */
DECL|member|flush_count
id|ushort
id|flush_count
suffix:semicolon
multiline_comment|/* Count of write flushes */
DECL|member|txmode
id|ushort
id|txmode
suffix:semicolon
multiline_comment|/* Modes for tx */
DECL|member|rxmode
id|ushort
id|rxmode
suffix:semicolon
multiline_comment|/* Modes for rx */
DECL|member|portmode
id|ushort
id|portmode
suffix:semicolon
multiline_comment|/* Generic modes */
DECL|member|column
id|ushort
id|column
suffix:semicolon
multiline_comment|/* TAB3 column count */
DECL|member|tx_subscript
id|ushort
id|tx_subscript
suffix:semicolon
multiline_comment|/* (TX) Subscript into data field */
DECL|member|rx_subscript
id|ushort
id|rx_subscript
suffix:semicolon
multiline_comment|/* (RX) Subscript into data field */
DECL|member|rx_incomplete
id|PKT_ptr
id|rx_incomplete
suffix:semicolon
multiline_comment|/* Hold an incomplete packet here */
DECL|member|modem_bits
id|ushort
id|modem_bits
suffix:semicolon
multiline_comment|/* Modem bits to mask */
DECL|member|lastModem
id|ushort
id|lastModem
suffix:semicolon
multiline_comment|/* Modem control lines. */
DECL|member|addr
id|ushort
id|addr
suffix:semicolon
multiline_comment|/* Address for sub commands */
DECL|member|MonitorTstate
id|ushort
id|MonitorTstate
suffix:semicolon
multiline_comment|/* TRUE if monitoring tstop */
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
