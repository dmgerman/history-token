multiline_comment|/*&n; *  linux/drivers/acorn/net/ether3.h&n; *&n; *  Copyright (C) 1995-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  network driver for Acorn/ANT Ether3 cards&n; */
macro_line|#ifndef _LINUX_ether3_H
DECL|macro|_LINUX_ether3_H
mdefine_line|#define _LINUX_ether3_H
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug. debug flags: */
DECL|macro|DEBUG_TX
mdefine_line|#define DEBUG_TX&t; 2
DECL|macro|DEBUG_RX
mdefine_line|#define DEBUG_RX&t; 4
DECL|macro|DEBUG_INT
mdefine_line|#define DEBUG_INT&t; 8
DECL|macro|DEBUG_IC
mdefine_line|#define DEBUG_IC&t;16
macro_line|#ifndef NET_DEBUG
DECL|macro|NET_DEBUG
mdefine_line|#define NET_DEBUG &t;0
macro_line|#endif
multiline_comment|/* Command register definitions &amp; bits */
DECL|macro|REG_COMMAND
mdefine_line|#define REG_COMMAND&t;&t;(dev-&gt;base_addr + 0x00)
DECL|macro|CMD_ENINTDMA
mdefine_line|#define CMD_ENINTDMA&t;&t;0x0001
DECL|macro|CMD_ENINTRX
mdefine_line|#define CMD_ENINTRX&t;&t;0x0002
DECL|macro|CMD_ENINTTX
mdefine_line|#define CMD_ENINTTX&t;&t;0x0004
DECL|macro|CMD_ENINTBUFWIN
mdefine_line|#define CMD_ENINTBUFWIN&t;&t;0x0008
DECL|macro|CMD_ACKINTDMA
mdefine_line|#define CMD_ACKINTDMA&t;&t;0x0010
DECL|macro|CMD_ACKINTRX
mdefine_line|#define CMD_ACKINTRX&t;&t;0x0020
DECL|macro|CMD_ACKINTTX
mdefine_line|#define CMD_ACKINTTX&t;&t;0x0040
DECL|macro|CMD_ACKINTBUFWIN
mdefine_line|#define CMD_ACKINTBUFWIN&t;0x0080
DECL|macro|CMD_DMAON
mdefine_line|#define CMD_DMAON&t;&t;0x0100
DECL|macro|CMD_RXON
mdefine_line|#define CMD_RXON&t;&t;0x0200
DECL|macro|CMD_TXON
mdefine_line|#define CMD_TXON&t;&t;0x0400
DECL|macro|CMD_DMAOFF
mdefine_line|#define CMD_DMAOFF&t;&t;0x0800
DECL|macro|CMD_RXOFF
mdefine_line|#define CMD_RXOFF&t;&t;0x1000
DECL|macro|CMD_TXOFF
mdefine_line|#define CMD_TXOFF&t;&t;0x2000
DECL|macro|CMD_FIFOREAD
mdefine_line|#define CMD_FIFOREAD&t;&t;0x4000
DECL|macro|CMD_FIFOWRITE
mdefine_line|#define CMD_FIFOWRITE&t;&t;0x8000
multiline_comment|/* status register */
DECL|macro|REG_STATUS
mdefine_line|#define REG_STATUS&t;&t;(dev-&gt;base_addr + 0x00)
DECL|macro|STAT_ENINTSTAT
mdefine_line|#define STAT_ENINTSTAT&t;&t;0x0001
DECL|macro|STAT_ENINTRX
mdefine_line|#define STAT_ENINTRX&t;&t;0x0002
DECL|macro|STAT_ENINTTX
mdefine_line|#define STAT_ENINTTX&t;&t;0x0004
DECL|macro|STAT_ENINTBUFWIN
mdefine_line|#define STAT_ENINTBUFWIN&t;0x0008
DECL|macro|STAT_INTDMA
mdefine_line|#define STAT_INTDMA&t;&t;0x0010
DECL|macro|STAT_INTRX
mdefine_line|#define STAT_INTRX&t;&t;0x0020
DECL|macro|STAT_INTTX
mdefine_line|#define STAT_INTTX&t;&t;0x0040
DECL|macro|STAT_INTBUFWIN
mdefine_line|#define STAT_INTBUFWIN&t;&t;0x0080
DECL|macro|STAT_DMAON
mdefine_line|#define STAT_DMAON&t;&t;0x0100
DECL|macro|STAT_RXON
mdefine_line|#define STAT_RXON&t;&t;0x0200
DECL|macro|STAT_TXON
mdefine_line|#define STAT_TXON&t;&t;0x0400
DECL|macro|STAT_FIFOFULL
mdefine_line|#define STAT_FIFOFULL&t;&t;0x2000
DECL|macro|STAT_FIFOEMPTY
mdefine_line|#define STAT_FIFOEMPTY&t;&t;0x4000
DECL|macro|STAT_FIFODIR
mdefine_line|#define STAT_FIFODIR&t;&t;0x8000
multiline_comment|/* configuration register 1 */
DECL|macro|REG_CONFIG1
mdefine_line|#define REG_CONFIG1&t;&t;(dev-&gt;base_addr + 0x10)
DECL|macro|CFG1_BUFSELSTAT0
mdefine_line|#define CFG1_BUFSELSTAT0&t;0x0000
DECL|macro|CFG1_BUFSELSTAT1
mdefine_line|#define CFG1_BUFSELSTAT1&t;0x0001
DECL|macro|CFG1_BUFSELSTAT2
mdefine_line|#define CFG1_BUFSELSTAT2&t;0x0002
DECL|macro|CFG1_BUFSELSTAT3
mdefine_line|#define CFG1_BUFSELSTAT3&t;0x0003
DECL|macro|CFG1_BUFSELSTAT4
mdefine_line|#define CFG1_BUFSELSTAT4&t;0x0004
DECL|macro|CFG1_BUFSELSTAT5
mdefine_line|#define CFG1_BUFSELSTAT5&t;0x0005
DECL|macro|CFG1_ADDRPROM
mdefine_line|#define CFG1_ADDRPROM&t;&t;0x0006
DECL|macro|CFG1_TRANSEND
mdefine_line|#define CFG1_TRANSEND&t;&t;0x0007
DECL|macro|CFG1_LOCBUFMEM
mdefine_line|#define CFG1_LOCBUFMEM&t;&t;0x0008
DECL|macro|CFG1_INTVECTOR
mdefine_line|#define CFG1_INTVECTOR&t;&t;0x0009
DECL|macro|CFG1_RECVSPECONLY
mdefine_line|#define CFG1_RECVSPECONLY&t;0x0000
DECL|macro|CFG1_RECVSPECBROAD
mdefine_line|#define CFG1_RECVSPECBROAD&t;0x4000
DECL|macro|CFG1_RECVSPECBRMULTI
mdefine_line|#define CFG1_RECVSPECBRMULTI&t;0x8000
DECL|macro|CFG1_RECVPROMISC
mdefine_line|#define CFG1_RECVPROMISC&t;0xC000
multiline_comment|/* The following aren&squot;t in 8004 */
DECL|macro|CFG1_DMABURSTCONT
mdefine_line|#define CFG1_DMABURSTCONT&t;0x0000
DECL|macro|CFG1_DMABURST800NS
mdefine_line|#define CFG1_DMABURST800NS&t;0x0010
DECL|macro|CFG1_DMABURST1600NS
mdefine_line|#define CFG1_DMABURST1600NS&t;0x0020
DECL|macro|CFG1_DMABURST3200NS
mdefine_line|#define CFG1_DMABURST3200NS&t;0x0030
DECL|macro|CFG1_DMABURST1
mdefine_line|#define CFG1_DMABURST1&t;&t;0x0000
DECL|macro|CFG1_DMABURST4
mdefine_line|#define CFG1_DMABURST4&t;&t;0x0040
DECL|macro|CFG1_DMABURST8
mdefine_line|#define CFG1_DMABURST8&t;&t;0x0080
DECL|macro|CFG1_DMABURST16
mdefine_line|#define CFG1_DMABURST16&t;&t;0x00C0
DECL|macro|CFG1_RECVCOMPSTAT0
mdefine_line|#define CFG1_RECVCOMPSTAT0&t;0x0100
DECL|macro|CFG1_RECVCOMPSTAT1
mdefine_line|#define CFG1_RECVCOMPSTAT1&t;0x0200
DECL|macro|CFG1_RECVCOMPSTAT2
mdefine_line|#define CFG1_RECVCOMPSTAT2&t;0x0400
DECL|macro|CFG1_RECVCOMPSTAT3
mdefine_line|#define CFG1_RECVCOMPSTAT3&t;0x0800
DECL|macro|CFG1_RECVCOMPSTAT4
mdefine_line|#define CFG1_RECVCOMPSTAT4&t;0x1000
DECL|macro|CFG1_RECVCOMPSTAT5
mdefine_line|#define CFG1_RECVCOMPSTAT5&t;0x2000
multiline_comment|/* configuration register 2 */
DECL|macro|REG_CONFIG2
mdefine_line|#define REG_CONFIG2&t;&t;(dev-&gt;base_addr + 0x20)
DECL|macro|CFG2_BYTESWAP
mdefine_line|#define CFG2_BYTESWAP&t;&t;0x0001
DECL|macro|CFG2_ERRENCRC
mdefine_line|#define CFG2_ERRENCRC&t;&t;0x0008
DECL|macro|CFG2_ERRENDRIBBLE
mdefine_line|#define CFG2_ERRENDRIBBLE&t;0x0010
DECL|macro|CFG2_ERRSHORTFRAME
mdefine_line|#define CFG2_ERRSHORTFRAME&t;0x0020
DECL|macro|CFG2_SLOTSELECT
mdefine_line|#define CFG2_SLOTSELECT&t;&t;0x0040
DECL|macro|CFG2_PREAMSELECT
mdefine_line|#define CFG2_PREAMSELECT&t;0x0080
DECL|macro|CFG2_ADDRLENGTH
mdefine_line|#define CFG2_ADDRLENGTH&t;&t;0x0100
DECL|macro|CFG2_RECVCRC
mdefine_line|#define CFG2_RECVCRC&t;&t;0x0200
DECL|macro|CFG2_XMITNOCRC
mdefine_line|#define CFG2_XMITNOCRC&t;&t;0x0400
DECL|macro|CFG2_LOOPBACK
mdefine_line|#define CFG2_LOOPBACK&t;&t;0x0800
DECL|macro|CFG2_CTRLO
mdefine_line|#define CFG2_CTRLO&t;&t;0x1000
DECL|macro|CFG2_RESET
mdefine_line|#define CFG2_RESET&t;&t;0x8000
DECL|macro|REG_RECVEND
mdefine_line|#define REG_RECVEND&t;&t;(dev-&gt;base_addr + 0x30)
DECL|macro|REG_BUFWIN
mdefine_line|#define REG_BUFWIN&t;&t;(dev-&gt;base_addr + 0x40)
DECL|macro|REG_RECVPTR
mdefine_line|#define REG_RECVPTR&t;&t;(dev-&gt;base_addr + 0x50)
DECL|macro|REG_TRANSMITPTR
mdefine_line|#define REG_TRANSMITPTR&t;&t;(dev-&gt;base_addr + 0x60)
DECL|macro|REG_DMAADDR
mdefine_line|#define REG_DMAADDR&t;&t;(dev-&gt;base_addr + 0x70)
multiline_comment|/*&n; * Cards transmit/receive headers&n; */
DECL|macro|TX_NEXT
mdefine_line|#define TX_NEXT&t;&t;&t;(0xffff)
DECL|macro|TXHDR_ENBABBLEINT
mdefine_line|#define TXHDR_ENBABBLEINT&t;(1 &lt;&lt; 16)
DECL|macro|TXHDR_ENCOLLISIONINT
mdefine_line|#define TXHDR_ENCOLLISIONINT&t;(1 &lt;&lt; 17)
DECL|macro|TXHDR_EN16COLLISION
mdefine_line|#define TXHDR_EN16COLLISION&t;(1 &lt;&lt; 18)
DECL|macro|TXHDR_ENSUCCESS
mdefine_line|#define TXHDR_ENSUCCESS&t;&t;(1 &lt;&lt; 19)
DECL|macro|TXHDR_DATAFOLLOWS
mdefine_line|#define TXHDR_DATAFOLLOWS&t;(1 &lt;&lt; 21)
DECL|macro|TXHDR_CHAINCONTINUE
mdefine_line|#define TXHDR_CHAINCONTINUE&t;(1 &lt;&lt; 22)
DECL|macro|TXHDR_TRANSMIT
mdefine_line|#define TXHDR_TRANSMIT&t;&t;(1 &lt;&lt; 23)
DECL|macro|TXSTAT_BABBLED
mdefine_line|#define TXSTAT_BABBLED&t;&t;(1 &lt;&lt; 24)
DECL|macro|TXSTAT_COLLISION
mdefine_line|#define TXSTAT_COLLISION&t;(1 &lt;&lt; 25)
DECL|macro|TXSTAT_16COLLISIONS
mdefine_line|#define TXSTAT_16COLLISIONS&t;(1 &lt;&lt; 26)
DECL|macro|TXSTAT_DONE
mdefine_line|#define TXSTAT_DONE&t;&t;(1 &lt;&lt; 31)
DECL|macro|RX_NEXT
mdefine_line|#define RX_NEXT&t;&t;&t;(0xffff)
DECL|macro|RXHDR_CHAINCONTINUE
mdefine_line|#define RXHDR_CHAINCONTINUE&t;(1 &lt;&lt; 6)
DECL|macro|RXHDR_RECEIVE
mdefine_line|#define RXHDR_RECEIVE&t;&t;(1 &lt;&lt; 7)
DECL|macro|RXSTAT_OVERSIZE
mdefine_line|#define RXSTAT_OVERSIZE&t;&t;(1 &lt;&lt; 8)
DECL|macro|RXSTAT_CRCERROR
mdefine_line|#define RXSTAT_CRCERROR&t;&t;(1 &lt;&lt; 9)
DECL|macro|RXSTAT_DRIBBLEERROR
mdefine_line|#define RXSTAT_DRIBBLEERROR&t;(1 &lt;&lt; 10)
DECL|macro|RXSTAT_SHORTPACKET
mdefine_line|#define RXSTAT_SHORTPACKET&t;(1 &lt;&lt; 11)
DECL|macro|RXSTAT_DONE
mdefine_line|#define RXSTAT_DONE&t;&t;(1 &lt;&lt; 15)
DECL|macro|TX_START
mdefine_line|#define TX_START&t;0x0000
DECL|macro|TX_END
mdefine_line|#define TX_END&t;&t;0x6000
DECL|macro|RX_START
mdefine_line|#define RX_START&t;0x6000
DECL|macro|RX_LEN
mdefine_line|#define RX_LEN&t;&t;0xA000
DECL|macro|RX_END
mdefine_line|#define RX_END&t;&t;0x10000
multiline_comment|/* must be a power of 2 and greater than MAX_TX_BUFFERED */
DECL|macro|MAX_TXED
mdefine_line|#define MAX_TXED&t;16
DECL|macro|MAX_TX_BUFFERED
mdefine_line|#define MAX_TX_BUFFERED&t;10
DECL|struct|dev_priv
r_struct
id|dev_priv
(brace
r_struct
(brace
DECL|member|command
r_int
r_int
id|command
suffix:semicolon
DECL|member|config1
r_int
r_int
id|config1
suffix:semicolon
DECL|member|config2
r_int
r_int
id|config2
suffix:semicolon
DECL|member|regs
)brace
id|regs
suffix:semicolon
DECL|member|tx_head
r_int
r_char
id|tx_head
suffix:semicolon
multiline_comment|/* buffer nr to insert next packet&t; */
DECL|member|tx_tail
r_int
r_char
id|tx_tail
suffix:semicolon
multiline_comment|/* buffer nr of transmitting packet&t; */
DECL|member|rx_head
r_int
r_int
id|rx_head
suffix:semicolon
multiline_comment|/* address to fetch next packet from&t; */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|broken
r_int
id|broken
suffix:semicolon
multiline_comment|/* 0 = ok, 1 = something went wrong&t; */
)brace
suffix:semicolon
macro_line|#endif
eof
