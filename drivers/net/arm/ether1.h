multiline_comment|/*&n; *  linux/drivers/acorn/net/ether1.h&n; *&n; *  Copyright (C) 1996 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Network driver for Acorn Ether1 cards.&n; */
macro_line|#ifndef _LINUX_ether1_H
DECL|macro|_LINUX_ether1_H
mdefine_line|#define _LINUX_ether1_H
macro_line|#ifdef __ETHER1_C
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
macro_line|#ifndef NET_DEBUG
DECL|macro|NET_DEBUG
mdefine_line|#define NET_DEBUG 0
macro_line|#endif
multiline_comment|/* Page register */
DECL|macro|REG_PAGE
mdefine_line|#define REG_PAGE&t;(dev-&gt;base_addr + 0x00)
multiline_comment|/* Control register */
DECL|macro|REG_CONTROL
mdefine_line|#define REG_CONTROL&t;(dev-&gt;base_addr + 0x01)
DECL|macro|CTRL_RST
mdefine_line|#define CTRL_RST&t;0x01
DECL|macro|CTRL_LOOPBACK
mdefine_line|#define CTRL_LOOPBACK&t;0x02
DECL|macro|CTRL_CA
mdefine_line|#define CTRL_CA&t;&t;0x04
DECL|macro|CTRL_ACK
mdefine_line|#define CTRL_ACK&t;0x08
DECL|macro|ETHER1_RAM
mdefine_line|#define ETHER1_RAM&t;(dev-&gt;base_addr + 0x800)
multiline_comment|/* HW address */
DECL|macro|IDPROM_ADDRESS
mdefine_line|#define IDPROM_ADDRESS&t;(dev-&gt;base_addr + 0x09)
DECL|struct|ether1_priv
r_struct
id|ether1_priv
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|tx_link
r_int
r_int
id|tx_link
suffix:semicolon
DECL|member|tx_head
r_int
r_int
id|tx_head
suffix:semicolon
DECL|member|tx_tail
r_volatile
r_int
r_int
id|tx_tail
suffix:semicolon
DECL|member|rx_head
r_volatile
r_int
r_int
id|rx_head
suffix:semicolon
DECL|member|rx_tail
r_volatile
r_int
r_int
id|rx_tail
suffix:semicolon
DECL|member|bus_type
r_int
r_char
id|bus_type
suffix:semicolon
DECL|member|resetting
r_int
r_char
id|resetting
suffix:semicolon
DECL|member|initialising
r_int
r_char
id|initialising
suffix:colon
l_int|1
suffix:semicolon
DECL|member|restart
r_int
r_char
id|restart
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|I82586_NULL
mdefine_line|#define I82586_NULL (-1)
r_typedef
r_struct
(brace
multiline_comment|/* tdr */
DECL|member|tdr_status
r_int
r_int
id|tdr_status
suffix:semicolon
DECL|member|tdr_command
r_int
r_int
id|tdr_command
suffix:semicolon
DECL|member|tdr_link
r_int
r_int
id|tdr_link
suffix:semicolon
DECL|member|tdr_result
r_int
r_int
id|tdr_result
suffix:semicolon
DECL|macro|TDR_TIME
mdefine_line|#define TDR_TIME&t;(0x7ff)
DECL|macro|TDR_SHORT
mdefine_line|#define TDR_SHORT&t;(1 &lt;&lt; 12)
DECL|macro|TDR_OPEN
mdefine_line|#define TDR_OPEN&t;(1 &lt;&lt; 13)
DECL|macro|TDR_XCVRPROB
mdefine_line|#define TDR_XCVRPROB&t;(1 &lt;&lt; 14)
DECL|macro|TDR_LNKOK
mdefine_line|#define TDR_LNKOK&t;(1 &lt;&lt; 15)
DECL|typedef|tdr_t
)brace
id|tdr_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* transmit */
DECL|member|tx_status
r_int
r_int
id|tx_status
suffix:semicolon
DECL|member|tx_command
r_int
r_int
id|tx_command
suffix:semicolon
DECL|member|tx_link
r_int
r_int
id|tx_link
suffix:semicolon
DECL|member|tx_tbdoffset
r_int
r_int
id|tx_tbdoffset
suffix:semicolon
DECL|typedef|tx_t
)brace
id|tx_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* tbd */
DECL|member|tbd_opts
r_int
r_int
id|tbd_opts
suffix:semicolon
DECL|macro|TBD_CNT
mdefine_line|#define TBD_CNT&t;&t;(0x3fff)
DECL|macro|TBD_EOL
mdefine_line|#define TBD_EOL&t;&t;(1 &lt;&lt; 15)
DECL|member|tbd_link
r_int
r_int
id|tbd_link
suffix:semicolon
DECL|member|tbd_bufl
r_int
r_int
id|tbd_bufl
suffix:semicolon
DECL|member|tbd_bufh
r_int
r_int
id|tbd_bufh
suffix:semicolon
DECL|typedef|tbd_t
)brace
id|tbd_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* rfd */
DECL|member|rfd_status
r_int
r_int
id|rfd_status
suffix:semicolon
DECL|macro|RFD_NOEOF
mdefine_line|#define RFD_NOEOF&t;(1 &lt;&lt; 6)
DECL|macro|RFD_FRAMESHORT
mdefine_line|#define RFD_FRAMESHORT&t;(1 &lt;&lt; 7)
DECL|macro|RFD_DMAOVRN
mdefine_line|#define RFD_DMAOVRN&t;(1 &lt;&lt; 8)
DECL|macro|RFD_NORESOURCES
mdefine_line|#define RFD_NORESOURCES&t;(1 &lt;&lt; 9)
DECL|macro|RFD_ALIGNERROR
mdefine_line|#define RFD_ALIGNERROR&t;(1 &lt;&lt; 10)
DECL|macro|RFD_CRCERROR
mdefine_line|#define RFD_CRCERROR&t;(1 &lt;&lt; 11)
DECL|macro|RFD_OK
mdefine_line|#define RFD_OK&t;&t;(1 &lt;&lt; 13)
DECL|macro|RFD_FDCONSUMED
mdefine_line|#define RFD_FDCONSUMED&t;(1 &lt;&lt; 14)
DECL|macro|RFD_COMPLETE
mdefine_line|#define RFD_COMPLETE&t;(1 &lt;&lt; 15)
DECL|member|rfd_command
r_int
r_int
id|rfd_command
suffix:semicolon
DECL|macro|RFD_CMDSUSPEND
mdefine_line|#define RFD_CMDSUSPEND&t;(1 &lt;&lt; 14)
DECL|macro|RFD_CMDEL
mdefine_line|#define RFD_CMDEL&t;(1 &lt;&lt; 15)
DECL|member|rfd_link
r_int
r_int
id|rfd_link
suffix:semicolon
DECL|member|rfd_rbdoffset
r_int
r_int
id|rfd_rbdoffset
suffix:semicolon
DECL|member|rfd_dest
r_int
r_char
id|rfd_dest
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|rfd_src
r_int
r_char
id|rfd_src
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|rfd_len
r_int
r_int
id|rfd_len
suffix:semicolon
DECL|typedef|rfd_t
)brace
id|rfd_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* rbd */
DECL|member|rbd_status
r_int
r_int
id|rbd_status
suffix:semicolon
DECL|macro|RBD_ACNT
mdefine_line|#define RBD_ACNT&t;(0x3fff)
DECL|macro|RBD_ACNTVALID
mdefine_line|#define RBD_ACNTVALID&t;(1 &lt;&lt; 14)
DECL|macro|RBD_EOF
mdefine_line|#define RBD_EOF&t;&t;(1 &lt;&lt; 15)
DECL|member|rbd_link
r_int
r_int
id|rbd_link
suffix:semicolon
DECL|member|rbd_bufl
r_int
r_int
id|rbd_bufl
suffix:semicolon
DECL|member|rbd_bufh
r_int
r_int
id|rbd_bufh
suffix:semicolon
DECL|member|rbd_len
r_int
r_int
id|rbd_len
suffix:semicolon
DECL|typedef|rbd_t
)brace
id|rbd_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* nop */
DECL|member|nop_status
r_int
r_int
id|nop_status
suffix:semicolon
DECL|member|nop_command
r_int
r_int
id|nop_command
suffix:semicolon
DECL|member|nop_link
r_int
r_int
id|nop_link
suffix:semicolon
DECL|typedef|nop_t
)brace
id|nop_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* set multicast */
DECL|member|mc_status
r_int
r_int
id|mc_status
suffix:semicolon
DECL|member|mc_command
r_int
r_int
id|mc_command
suffix:semicolon
DECL|member|mc_link
r_int
r_int
id|mc_link
suffix:semicolon
DECL|member|mc_cnt
r_int
r_int
id|mc_cnt
suffix:semicolon
DECL|member|mc_addrs
r_int
r_char
id|mc_addrs
(braket
l_int|1
)braket
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|mc_t
)brace
id|mc_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* set address */
DECL|member|sa_status
r_int
r_int
id|sa_status
suffix:semicolon
DECL|member|sa_command
r_int
r_int
id|sa_command
suffix:semicolon
DECL|member|sa_link
r_int
r_int
id|sa_link
suffix:semicolon
DECL|member|sa_addr
r_int
r_char
id|sa_addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|sa_t
)brace
id|sa_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* config command */
DECL|member|cfg_status
r_int
r_int
id|cfg_status
suffix:semicolon
DECL|member|cfg_command
r_int
r_int
id|cfg_command
suffix:semicolon
DECL|member|cfg_link
r_int
r_int
id|cfg_link
suffix:semicolon
DECL|member|cfg_bytecnt
r_int
r_char
id|cfg_bytecnt
suffix:semicolon
multiline_comment|/* size foll data: 4 - 12&t;&t; */
DECL|member|cfg_fifolim
r_int
r_char
id|cfg_fifolim
suffix:semicolon
multiline_comment|/* FIFO threshold&t;&t;&t; */
DECL|member|cfg_byte8
r_int
r_char
id|cfg_byte8
suffix:semicolon
DECL|macro|CFG8_SRDY
mdefine_line|#define CFG8_SRDY&t;(1 &lt;&lt; 6)
DECL|macro|CFG8_SAVEBADF
mdefine_line|#define CFG8_SAVEBADF&t;(1 &lt;&lt; 7)
DECL|member|cfg_byte9
r_int
r_char
id|cfg_byte9
suffix:semicolon
DECL|macro|CFG9_ADDRLEN
mdefine_line|#define CFG9_ADDRLEN(x)&t;(x)
DECL|macro|CFG9_ADDRLENBUF
mdefine_line|#define CFG9_ADDRLENBUF&t;(1 &lt;&lt; 3)
DECL|macro|CFG9_PREAMB2
mdefine_line|#define CFG9_PREAMB2&t;(0 &lt;&lt; 4)
DECL|macro|CFG9_PREAMB4
mdefine_line|#define CFG9_PREAMB4&t;(1 &lt;&lt; 4)
DECL|macro|CFG9_PREAMB8
mdefine_line|#define CFG9_PREAMB8&t;(2 &lt;&lt; 4)
DECL|macro|CFG9_PREAMB16
mdefine_line|#define CFG9_PREAMB16&t;(3 &lt;&lt; 4)
DECL|macro|CFG9_ILOOPBACK
mdefine_line|#define CFG9_ILOOPBACK&t;(1 &lt;&lt; 6)
DECL|macro|CFG9_ELOOPBACK
mdefine_line|#define CFG9_ELOOPBACK&t;(1 &lt;&lt; 7)
DECL|member|cfg_byte10
r_int
r_char
id|cfg_byte10
suffix:semicolon
DECL|macro|CFG10_LINPRI
mdefine_line|#define CFG10_LINPRI(x)&t;(x)
DECL|macro|CFG10_ACR
mdefine_line|#define CFG10_ACR(x)&t;(x &lt;&lt; 4)
DECL|macro|CFG10_BOFMET
mdefine_line|#define CFG10_BOFMET&t;(1 &lt;&lt; 7)
DECL|member|cfg_ifs
r_int
r_char
id|cfg_ifs
suffix:semicolon
DECL|member|cfg_slotl
r_int
r_char
id|cfg_slotl
suffix:semicolon
DECL|member|cfg_byte13
r_int
r_char
id|cfg_byte13
suffix:semicolon
DECL|macro|CFG13_SLOTH
mdefine_line|#define CFG13_SLOTH(x)&t;(x)
DECL|macro|CFG13_RETRY
mdefine_line|#define CFG13_RETRY(x)&t;(x &lt;&lt; 4)
DECL|member|cfg_byte14
r_int
r_char
id|cfg_byte14
suffix:semicolon
DECL|macro|CFG14_PROMISC
mdefine_line|#define CFG14_PROMISC&t;(1 &lt;&lt; 0)
DECL|macro|CFG14_DISBRD
mdefine_line|#define CFG14_DISBRD&t;(1 &lt;&lt; 1)
DECL|macro|CFG14_MANCH
mdefine_line|#define CFG14_MANCH&t;(1 &lt;&lt; 2)
DECL|macro|CFG14_TNCRS
mdefine_line|#define CFG14_TNCRS&t;(1 &lt;&lt; 3)
DECL|macro|CFG14_NOCRC
mdefine_line|#define CFG14_NOCRC&t;(1 &lt;&lt; 4)
DECL|macro|CFG14_CRC16
mdefine_line|#define CFG14_CRC16&t;(1 &lt;&lt; 5)
DECL|macro|CFG14_BTSTF
mdefine_line|#define CFG14_BTSTF&t;(1 &lt;&lt; 6)
DECL|macro|CFG14_FLGPAD
mdefine_line|#define CFG14_FLGPAD&t;(1 &lt;&lt; 7)
DECL|member|cfg_byte15
r_int
r_char
id|cfg_byte15
suffix:semicolon
DECL|macro|CFG15_CSTF
mdefine_line|#define CFG15_CSTF(x)&t;(x)
DECL|macro|CFG15_ICSS
mdefine_line|#define CFG15_ICSS&t;(1 &lt;&lt; 3)
DECL|macro|CFG15_CDTF
mdefine_line|#define CFG15_CDTF(x)&t;(x &lt;&lt; 4)
DECL|macro|CFG15_ICDS
mdefine_line|#define CFG15_ICDS&t;(1 &lt;&lt; 7)
DECL|member|cfg_minfrmlen
r_int
r_int
id|cfg_minfrmlen
suffix:semicolon
DECL|typedef|cfg_t
)brace
id|cfg_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* scb */
DECL|member|scb_status
r_int
r_int
id|scb_status
suffix:semicolon
multiline_comment|/* status of 82586&t;&t;&t;*/
DECL|macro|SCB_STRXMASK
mdefine_line|#define SCB_STRXMASK&t;&t;(7 &lt;&lt; 4)&t;/* Receive unit status&t;&t;*/
DECL|macro|SCB_STRXIDLE
mdefine_line|#define SCB_STRXIDLE&t;&t;(0 &lt;&lt; 4)&t;/* Idle&t;&t;&t;&t;*/
DECL|macro|SCB_STRXSUSP
mdefine_line|#define SCB_STRXSUSP&t;&t;(1 &lt;&lt; 4)&t;/* Suspended&t;&t;&t;*/
DECL|macro|SCB_STRXNRES
mdefine_line|#define SCB_STRXNRES&t;&t;(2 &lt;&lt; 4)&t;/* No resources&t;&t;&t;*/
DECL|macro|SCB_STRXRDY
mdefine_line|#define SCB_STRXRDY&t;&t;(4 &lt;&lt; 4)&t;/* Ready&t;&t;&t;*/
DECL|macro|SCB_STCUMASK
mdefine_line|#define SCB_STCUMASK&t;&t;(7 &lt;&lt; 8)&t;/* Command unit status&t;&t;*/
DECL|macro|SCB_STCUIDLE
mdefine_line|#define SCB_STCUIDLE&t;&t;(0 &lt;&lt; 8)&t;/* Idle&t;&t;&t;&t;*/
DECL|macro|SCB_STCUSUSP
mdefine_line|#define SCB_STCUSUSP&t;&t;(1 &lt;&lt; 8)&t;/* Suspended&t;&t;&t;*/
DECL|macro|SCB_STCUACTV
mdefine_line|#define SCB_STCUACTV&t;&t;(2 &lt;&lt; 8)&t;/* Active&t;&t;&t;*/
DECL|macro|SCB_STRNR
mdefine_line|#define SCB_STRNR&t;&t;(1 &lt;&lt; 12)&t;/* Receive unit not ready&t;*/
DECL|macro|SCB_STCNA
mdefine_line|#define SCB_STCNA&t;&t;(1 &lt;&lt; 13)&t;/* Command unit not ready&t;*/
DECL|macro|SCB_STFR
mdefine_line|#define SCB_STFR&t;&t;(1 &lt;&lt; 14)&t;/* Frame received&t;&t;*/
DECL|macro|SCB_STCX
mdefine_line|#define SCB_STCX&t;&t;(1 &lt;&lt; 15)&t;/* Command completed&t;&t;*/
DECL|member|scb_command
r_int
r_int
id|scb_command
suffix:semicolon
multiline_comment|/* Next command&t;&t;&t;&t;*/
DECL|macro|SCB_CMDRXSTART
mdefine_line|#define SCB_CMDRXSTART&t;&t;(1 &lt;&lt; 4)&t;/* Start (at rfa_offset)&t;*/
DECL|macro|SCB_CMDRXRESUME
mdefine_line|#define SCB_CMDRXRESUME&t;&t;(2 &lt;&lt; 4)&t;/* Resume reception&t;&t;*/
DECL|macro|SCB_CMDRXSUSPEND
mdefine_line|#define SCB_CMDRXSUSPEND&t;(3 &lt;&lt; 4)&t;/* Suspend reception&t;&t;*/
DECL|macro|SCB_CMDRXABORT
mdefine_line|#define SCB_CMDRXABORT&t;&t;(4 &lt;&lt; 4)&t;/* Abort reception&t;&t;*/
DECL|macro|SCB_CMDCUCSTART
mdefine_line|#define SCB_CMDCUCSTART&t;&t;(1 &lt;&lt; 8)&t;/* Start (at cbl_offset)&t;*/
DECL|macro|SCB_CMDCUCRESUME
mdefine_line|#define SCB_CMDCUCRESUME&t;(2 &lt;&lt; 8)&t;/* Resume execution&t;&t;*/
DECL|macro|SCB_CMDCUCSUSPEND
mdefine_line|#define SCB_CMDCUCSUSPEND&t;(3 &lt;&lt; 8)&t;/* Suspend execution&t;&t;*/
DECL|macro|SCB_CMDCUCABORT
mdefine_line|#define SCB_CMDCUCABORT&t;&t;(4 &lt;&lt; 8)&t;/* Abort execution&t;&t;*/
DECL|macro|SCB_CMDACKRNR
mdefine_line|#define SCB_CMDACKRNR&t;&t;(1 &lt;&lt; 12)&t;/* Ack RU not ready&t;&t;*/
DECL|macro|SCB_CMDACKCNA
mdefine_line|#define SCB_CMDACKCNA&t;&t;(1 &lt;&lt; 13)&t;/* Ack CU not ready&t;&t;*/
DECL|macro|SCB_CMDACKFR
mdefine_line|#define SCB_CMDACKFR&t;&t;(1 &lt;&lt; 14)&t;/* Ack Frame received&t;&t;*/
DECL|macro|SCB_CMDACKCX
mdefine_line|#define SCB_CMDACKCX&t;&t;(1 &lt;&lt; 15)&t;/* Ack Command complete&t;&t;*/
DECL|member|scb_cbl_offset
r_int
r_int
id|scb_cbl_offset
suffix:semicolon
multiline_comment|/* Offset of first command unit&t;&t;*/
DECL|member|scb_rfa_offset
r_int
r_int
id|scb_rfa_offset
suffix:semicolon
multiline_comment|/* Offset of first receive frame area&t;*/
DECL|member|scb_crc_errors
r_int
r_int
id|scb_crc_errors
suffix:semicolon
multiline_comment|/* Properly aligned frame with CRC error*/
DECL|member|scb_aln_errors
r_int
r_int
id|scb_aln_errors
suffix:semicolon
multiline_comment|/* Misaligned frames&t;&t;&t;*/
DECL|member|scb_rsc_errors
r_int
r_int
id|scb_rsc_errors
suffix:semicolon
multiline_comment|/* Frames lost due to no space&t;&t;*/
DECL|member|scb_ovn_errors
r_int
r_int
id|scb_ovn_errors
suffix:semicolon
multiline_comment|/* Frames lost due to slow bus&t;&t;*/
DECL|typedef|scb_t
)brace
id|scb_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* iscp */
DECL|member|iscp_busy
r_int
r_int
id|iscp_busy
suffix:semicolon
multiline_comment|/* set by CPU before CA&t;&t;&t;*/
DECL|member|iscp_offset
r_int
r_int
id|iscp_offset
suffix:semicolon
multiline_comment|/* offset of SCB&t;&t;&t;*/
DECL|member|iscp_basel
r_int
r_int
id|iscp_basel
suffix:semicolon
multiline_comment|/* base of SCB&t;&t;&t;&t;*/
DECL|member|iscp_baseh
r_int
r_int
id|iscp_baseh
suffix:semicolon
DECL|typedef|iscp_t
)brace
id|iscp_t
suffix:semicolon
multiline_comment|/* this address must be 0xfff6 */
r_typedef
r_struct
(brace
multiline_comment|/* scp */
DECL|member|scp_sysbus
r_int
r_int
id|scp_sysbus
suffix:semicolon
multiline_comment|/* bus size */
DECL|macro|SCP_SY_16BBUS
mdefine_line|#define SCP_SY_16BBUS&t;0x00
DECL|macro|SCP_SY_8BBUS
mdefine_line|#define SCP_SY_8BBUS&t;0x01
DECL|member|scp_junk
r_int
r_int
id|scp_junk
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* junk */
DECL|member|scp_iscpl
r_int
r_int
id|scp_iscpl
suffix:semicolon
multiline_comment|/* lower 16 bits of iscp */
DECL|member|scp_iscph
r_int
r_int
id|scp_iscph
suffix:semicolon
multiline_comment|/* upper 16 bits of iscp */
DECL|typedef|scp_t
)brace
id|scp_t
suffix:semicolon
multiline_comment|/* commands */
DECL|macro|CMD_NOP
mdefine_line|#define CMD_NOP&t;&t;&t;0
DECL|macro|CMD_SETADDRESS
mdefine_line|#define CMD_SETADDRESS&t;&t;1
DECL|macro|CMD_CONFIG
mdefine_line|#define CMD_CONFIG&t;&t;2
DECL|macro|CMD_SETMULTICAST
mdefine_line|#define CMD_SETMULTICAST&t;3
DECL|macro|CMD_TX
mdefine_line|#define CMD_TX&t;&t;&t;4
DECL|macro|CMD_TDR
mdefine_line|#define CMD_TDR&t;&t;&t;5
DECL|macro|CMD_DUMP
mdefine_line|#define CMD_DUMP&t;&t;6
DECL|macro|CMD_DIAGNOSE
mdefine_line|#define CMD_DIAGNOSE&t;&t;7
DECL|macro|CMD_MASK
mdefine_line|#define CMD_MASK&t;&t;7
DECL|macro|CMD_INTR
mdefine_line|#define CMD_INTR&t;&t;(1 &lt;&lt; 13)
DECL|macro|CMD_SUSP
mdefine_line|#define CMD_SUSP&t;&t;(1 &lt;&lt; 14)
DECL|macro|CMD_EOL
mdefine_line|#define CMD_EOL&t;&t;&t;(1 &lt;&lt; 15)
DECL|macro|STAT_COLLISIONS
mdefine_line|#define STAT_COLLISIONS&t;&t;(15)
DECL|macro|STAT_COLLEXCESSIVE
mdefine_line|#define STAT_COLLEXCESSIVE&t;(1 &lt;&lt; 5)
DECL|macro|STAT_COLLAFTERTX
mdefine_line|#define STAT_COLLAFTERTX&t;(1 &lt;&lt; 6)
DECL|macro|STAT_TXDEFERRED
mdefine_line|#define STAT_TXDEFERRED&t;&t;(1 &lt;&lt; 7)
DECL|macro|STAT_TXSLOWDMA
mdefine_line|#define STAT_TXSLOWDMA&t;&t;(1 &lt;&lt; 8)
DECL|macro|STAT_TXLOSTCTS
mdefine_line|#define STAT_TXLOSTCTS&t;&t;(1 &lt;&lt; 9)
DECL|macro|STAT_NOCARRIER
mdefine_line|#define STAT_NOCARRIER&t;&t;(1 &lt;&lt; 10)
DECL|macro|STAT_FAIL
mdefine_line|#define STAT_FAIL&t;&t;(1 &lt;&lt; 11)
DECL|macro|STAT_ABORTED
mdefine_line|#define STAT_ABORTED&t;&t;(1 &lt;&lt; 12)
DECL|macro|STAT_OK
mdefine_line|#define STAT_OK&t;&t;&t;(1 &lt;&lt; 13)
DECL|macro|STAT_BUSY
mdefine_line|#define STAT_BUSY&t;&t;(1 &lt;&lt; 14)
DECL|macro|STAT_COMPLETE
mdefine_line|#define STAT_COMPLETE&t;&t;(1 &lt;&lt; 15)
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Ether1 card definitions:&n; *&n; * FAST accesses:&n; *&t;+0&t;Page register&n; * &t;&t;&t;16 pages&n; *&t;+4&t;Control&n; *&t;&t;&t;&squot;1&squot; = reset&n; *&t;&t;&t;&squot;2&squot; = loopback&n; *&t;&t;&t;&squot;4&squot; = CA&n; *&t;&t;&t;&squot;8&squot; = int ack&n; *&n; * RAM at address + 0x2000&n; * Pod. Prod id = 3&n; * Words after ID block [base + 8 words]&n; *&t;+0 pcb issue (0x0c and 0xf3 invalid)&n; *&t;+1 - +6 eth hw address&n; */
eof
