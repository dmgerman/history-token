multiline_comment|/* myri_sbus.h: Defines for MyriCOM MyriNET SBUS card driver.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _MYRI_SBUS_H
DECL|macro|_MYRI_SBUS_H
mdefine_line|#define _MYRI_SBUS_H
multiline_comment|/* LANAI Registers */
DECL|macro|LANAI_IPF0
mdefine_line|#define LANAI_IPF0&t;0x00UL&t;&t;/* Context zero state registers.*/
DECL|macro|LANAI_CUR0
mdefine_line|#define LANAI_CUR0&t;0x04UL
DECL|macro|LANAI_PREV0
mdefine_line|#define LANAI_PREV0&t;0x08UL
DECL|macro|LANAI_DATA0
mdefine_line|#define LANAI_DATA0&t;0x0cUL
DECL|macro|LANAI_DPF0
mdefine_line|#define LANAI_DPF0&t;0x10UL
DECL|macro|LANAI_IPF1
mdefine_line|#define LANAI_IPF1&t;0x14UL&t;&t;/* Context one state registers.&t;*/
DECL|macro|LANAI_CUR1
mdefine_line|#define LANAI_CUR1&t;0x18UL
DECL|macro|LANAI_PREV1
mdefine_line|#define LANAI_PREV1&t;0x1cUL
DECL|macro|LANAI_DATA1
mdefine_line|#define LANAI_DATA1&t;0x20UL
DECL|macro|LANAI_DPF1
mdefine_line|#define LANAI_DPF1&t;0x24UL
DECL|macro|LANAI_ISTAT
mdefine_line|#define LANAI_ISTAT&t;0x28UL&t;&t;/* Interrupt status.&t;&t;*/
DECL|macro|LANAI_EIMASK
mdefine_line|#define LANAI_EIMASK&t;0x2cUL&t;&t;/* External IRQ mask.&t;&t;*/
DECL|macro|LANAI_ITIMER
mdefine_line|#define LANAI_ITIMER&t;0x30UL&t;&t;/* IRQ timer.&t;&t;&t;*/
DECL|macro|LANAI_RTC
mdefine_line|#define LANAI_RTC&t;0x34UL&t;&t;/* Real Time Clock&t;&t;*/
DECL|macro|LANAI_CSUM
mdefine_line|#define LANAI_CSUM&t;0x38UL&t;&t;/* Checksum.&t;&t;&t;*/
DECL|macro|LANAI_DMAXADDR
mdefine_line|#define LANAI_DMAXADDR&t;0x3cUL&t;&t;/* SBUS DMA external address.&t;*/
DECL|macro|LANAI_DMALADDR
mdefine_line|#define LANAI_DMALADDR&t;0x40UL&t;&t;/* SBUS DMA local address.&t;*/
DECL|macro|LANAI_DMACTR
mdefine_line|#define LANAI_DMACTR&t;0x44UL&t;&t;/* SBUS DMA counter.&t;&t;*/
DECL|macro|LANAI_RXDMAPTR
mdefine_line|#define LANAI_RXDMAPTR&t;0x48UL&t;&t;/* Receive DMA pointer.&t;&t;*/
DECL|macro|LANAI_RXDMALIM
mdefine_line|#define LANAI_RXDMALIM&t;0x4cUL&t;&t;/* Receive DMA limit.&t;&t;*/
DECL|macro|LANAI_TXDMAPTR
mdefine_line|#define LANAI_TXDMAPTR&t;0x50UL&t;&t;/* Transmit DMA pointer.&t;*/
DECL|macro|LANAI_TXDMALIM
mdefine_line|#define LANAI_TXDMALIM&t;0x54UL&t;&t;/* Transmit DMA limit.&t;&t;*/
DECL|macro|LANAI_TXDMALIMT
mdefine_line|#define LANAI_TXDMALIMT&t;0x58UL&t;&t;/* Transmit DMA limit w/tail.&t;*/
multiline_comment|/* 0x5cUL, reserved */
DECL|macro|LANAI_RBYTE
mdefine_line|#define LANAI_RBYTE&t;0x60UL&t;&t;/* Receive byte.&t;&t;*/
multiline_comment|/* 0x64--&gt;0x6c, reserved */
DECL|macro|LANAI_RHALF
mdefine_line|#define LANAI_RHALF&t;0x70UL&t;&t;/* Receive half-word.&t;&t;*/
multiline_comment|/* 0x72UL, reserved */
DECL|macro|LANAI_RWORD
mdefine_line|#define LANAI_RWORD&t;0x74UL&t;&t;/* Receive word.&t;&t;*/
DECL|macro|LANAI_SALIGN
mdefine_line|#define LANAI_SALIGN&t;0x78UL&t;&t;/* Send align.&t;&t;&t;*/
DECL|macro|LANAI_SBYTE
mdefine_line|#define LANAI_SBYTE&t;0x7cUL&t;&t;/* SingleSend send-byte.&t;*/
DECL|macro|LANAI_SHALF
mdefine_line|#define LANAI_SHALF&t;0x80UL&t;&t;/* SingleSend send-halfword.&t;*/
DECL|macro|LANAI_SWORD
mdefine_line|#define LANAI_SWORD&t;0x84UL&t;&t;/* SingleSend send-word.&t;*/
DECL|macro|LANAI_SSENDT
mdefine_line|#define LANAI_SSENDT&t;0x88UL&t;&t;/* SingleSend special.&t;&t;*/
DECL|macro|LANAI_DMADIR
mdefine_line|#define LANAI_DMADIR&t;0x8cUL&t;&t;/* DMA direction.&t;&t;*/
DECL|macro|LANAI_DMASTAT
mdefine_line|#define LANAI_DMASTAT&t;0x90UL&t;&t;/* DMA status.&t;&t;&t;*/
DECL|macro|LANAI_TIMEO
mdefine_line|#define LANAI_TIMEO&t;0x94UL&t;&t;/* Timeout register.&t;&t;*/
DECL|macro|LANAI_MYRINET
mdefine_line|#define LANAI_MYRINET&t;0x98UL&t;&t;/* XXX MAGIC myricom thing&t;*/
DECL|macro|LANAI_HWDEBUG
mdefine_line|#define LANAI_HWDEBUG&t;0x9cUL&t;&t;/* Hardware debugging reg.&t;*/
DECL|macro|LANAI_LEDS
mdefine_line|#define LANAI_LEDS&t;0xa0UL&t;&t;/* LED control.&t;&t;&t;*/
DECL|macro|LANAI_VERS
mdefine_line|#define LANAI_VERS&t;0xa4UL&t;&t;/* Version register.&t;&t;*/
DECL|macro|LANAI_LINKON
mdefine_line|#define LANAI_LINKON&t;0xa8UL&t;&t;/* Link activation reg.&t;&t;*/
multiline_comment|/* 0xac--&gt;0x104, reserved */
DECL|macro|LANAI_CVAL
mdefine_line|#define LANAI_CVAL&t;0x108UL&t;&t;/* Clock value register.&t;*/
DECL|macro|LANAI_REG_SIZE
mdefine_line|#define LANAI_REG_SIZE&t;0x10cUL
multiline_comment|/* Interrupt status bits. */
DECL|macro|ISTAT_DEBUG
mdefine_line|#define ISTAT_DEBUG&t;0x80000000
DECL|macro|ISTAT_HOST
mdefine_line|#define ISTAT_HOST&t;0x40000000
DECL|macro|ISTAT_LAN7
mdefine_line|#define ISTAT_LAN7&t;0x00800000
DECL|macro|ISTAT_LAN6
mdefine_line|#define ISTAT_LAN6&t;0x00400000
DECL|macro|ISTAT_LAN5
mdefine_line|#define ISTAT_LAN5&t;0x00200000
DECL|macro|ISTAT_LAN4
mdefine_line|#define ISTAT_LAN4&t;0x00100000
DECL|macro|ISTAT_LAN3
mdefine_line|#define ISTAT_LAN3&t;0x00080000
DECL|macro|ISTAT_LAN2
mdefine_line|#define ISTAT_LAN2&t;0x00040000
DECL|macro|ISTAT_LAN1
mdefine_line|#define ISTAT_LAN1&t;0x00020000
DECL|macro|ISTAT_LAN0
mdefine_line|#define ISTAT_LAN0&t;0x00010000
DECL|macro|ISTAT_WRDY
mdefine_line|#define ISTAT_WRDY&t;0x00008000
DECL|macro|ISTAT_HRDY
mdefine_line|#define ISTAT_HRDY&t;0x00004000
DECL|macro|ISTAT_SRDY
mdefine_line|#define ISTAT_SRDY&t;0x00002000
DECL|macro|ISTAT_LINK
mdefine_line|#define ISTAT_LINK&t;0x00001000
DECL|macro|ISTAT_FRES
mdefine_line|#define ISTAT_FRES&t;0x00000800
DECL|macro|ISTAT_NRES
mdefine_line|#define ISTAT_NRES&t;0x00000800
DECL|macro|ISTAT_WAKE
mdefine_line|#define ISTAT_WAKE&t;0x00000400
DECL|macro|ISTAT_OB2
mdefine_line|#define ISTAT_OB2&t;0x00000200
DECL|macro|ISTAT_OB1
mdefine_line|#define ISTAT_OB1&t;0x00000100
DECL|macro|ISTAT_TAIL
mdefine_line|#define ISTAT_TAIL&t;0x00000080
DECL|macro|ISTAT_WDOG
mdefine_line|#define ISTAT_WDOG&t;0x00000040
DECL|macro|ISTAT_TIME
mdefine_line|#define ISTAT_TIME&t;0x00000020
DECL|macro|ISTAT_DMA
mdefine_line|#define ISTAT_DMA&t;0x00000010
DECL|macro|ISTAT_SEND
mdefine_line|#define ISTAT_SEND&t;0x00000008
DECL|macro|ISTAT_BUF
mdefine_line|#define ISTAT_BUF&t;0x00000004
DECL|macro|ISTAT_RECV
mdefine_line|#define ISTAT_RECV&t;0x00000002
DECL|macro|ISTAT_BRDY
mdefine_line|#define ISTAT_BRDY&t;0x00000001
multiline_comment|/* MYRI Registers */
DECL|macro|MYRI_RESETOFF
mdefine_line|#define MYRI_RESETOFF&t;0x00UL
DECL|macro|MYRI_RESETON
mdefine_line|#define MYRI_RESETON&t;0x04UL
DECL|macro|MYRI_IRQOFF
mdefine_line|#define MYRI_IRQOFF&t;0x08UL
DECL|macro|MYRI_IRQON
mdefine_line|#define MYRI_IRQON&t;0x0cUL
DECL|macro|MYRI_WAKEUPOFF
mdefine_line|#define MYRI_WAKEUPOFF&t;0x10UL
DECL|macro|MYRI_WAKEUPON
mdefine_line|#define MYRI_WAKEUPON&t;0x14UL
DECL|macro|MYRI_IRQREAD
mdefine_line|#define MYRI_IRQREAD&t;0x18UL
multiline_comment|/* 0x1c--&gt;0x3ffc, reserved */
DECL|macro|MYRI_LOCALMEM
mdefine_line|#define MYRI_LOCALMEM&t;0x4000UL
DECL|macro|MYRI_REG_SIZE
mdefine_line|#define MYRI_REG_SIZE&t;0x25000UL
multiline_comment|/* Shared memory interrupt mask. */
DECL|macro|SHMEM_IMASK_RX
mdefine_line|#define SHMEM_IMASK_RX&t;&t;0x00000002
DECL|macro|SHMEM_IMASK_TX
mdefine_line|#define SHMEM_IMASK_TX&t;&t;0x00000001
multiline_comment|/* Just to make things readable. */
DECL|macro|KERNEL_CHANNEL
mdefine_line|#define KERNEL_CHANNEL&t;&t;0
multiline_comment|/* The size of this must be &gt;= 129 bytes. */
DECL|struct|myri_eeprom
r_struct
id|myri_eeprom
(brace
DECL|member|cval
r_int
r_int
id|cval
suffix:semicolon
DECL|member|cpuvers
r_int
r_int
id|cpuvers
suffix:semicolon
DECL|member|id
r_int
r_char
id|id
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|ramsz
r_int
r_int
id|ramsz
suffix:semicolon
DECL|member|fvers
r_int
r_char
id|fvers
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|mvers
r_int
r_char
id|mvers
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|dlval
r_int
r_int
id|dlval
suffix:semicolon
DECL|member|brd_type
r_int
r_int
id|brd_type
suffix:semicolon
DECL|member|bus_type
r_int
r_int
id|bus_type
suffix:semicolon
DECL|member|prod_code
r_int
r_int
id|prod_code
suffix:semicolon
DECL|member|serial_num
r_int
r_int
id|serial_num
suffix:semicolon
DECL|member|_reserved
r_int
r_int
id|_reserved
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|_unused
r_int
r_int
id|_unused
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* EEPROM bus types, only SBUS is valid in this driver. */
DECL|macro|BUS_TYPE_SBUS
mdefine_line|#define BUS_TYPE_SBUS&t;&t;1
multiline_comment|/* EEPROM CPU revisions. */
DECL|macro|CPUVERS_2_3
mdefine_line|#define CPUVERS_2_3&t;&t;0x0203
DECL|macro|CPUVERS_3_0
mdefine_line|#define CPUVERS_3_0&t;&t;0x0300
DECL|macro|CPUVERS_3_1
mdefine_line|#define CPUVERS_3_1&t;&t;0x0301
DECL|macro|CPUVERS_3_2
mdefine_line|#define CPUVERS_3_2&t;&t;0x0302
DECL|macro|CPUVERS_4_0
mdefine_line|#define CPUVERS_4_0&t;&t;0x0400
DECL|macro|CPUVERS_4_1
mdefine_line|#define CPUVERS_4_1&t;&t;0x0401
DECL|macro|CPUVERS_4_2
mdefine_line|#define CPUVERS_4_2&t;&t;0x0402
DECL|macro|CPUVERS_5_0
mdefine_line|#define CPUVERS_5_0&t;&t;0x0500
multiline_comment|/* MYRI Control Registers */
DECL|macro|MYRICTRL_CTRL
mdefine_line|#define MYRICTRL_CTRL&t;&t;0x00UL
DECL|macro|MYRICTRL_IRQLVL
mdefine_line|#define MYRICTRL_IRQLVL&t;&t;0x02UL
DECL|macro|MYRICTRL_REG_SIZE
mdefine_line|#define MYRICTRL_REG_SIZE&t;0x04UL
multiline_comment|/* Global control register defines. */
DECL|macro|CONTROL_ROFF
mdefine_line|#define CONTROL_ROFF&t;&t;0x8000&t;/* Reset OFF.&t;&t;*/
DECL|macro|CONTROL_RON
mdefine_line|#define CONTROL_RON&t;&t;0x4000&t;/* Reset ON.&t;&t;*/
DECL|macro|CONTROL_EIRQ
mdefine_line|#define CONTROL_EIRQ&t;&t;0x2000&t;/* Enable IRQ&squot;s.&t;*/
DECL|macro|CONTROL_DIRQ
mdefine_line|#define CONTROL_DIRQ&t;&t;0x1000&t;/* Disable IRQ&squot;s.&t;*/
DECL|macro|CONTROL_WON
mdefine_line|#define CONTROL_WON&t;&t;0x0800&t;/* Wake-up ON.&t;&t;*/
DECL|macro|MYRI_SCATTER_ENTRIES
mdefine_line|#define MYRI_SCATTER_ENTRIES&t;8
DECL|macro|MYRI_GATHER_ENTRIES
mdefine_line|#define MYRI_GATHER_ENTRIES&t;16
DECL|struct|myri_sglist
r_struct
id|myri_sglist
(brace
DECL|member|addr
id|u32
id|addr
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|myri_rxd
r_struct
id|myri_rxd
(brace
DECL|member|myri_scatters
r_struct
id|myri_sglist
id|myri_scatters
(braket
id|MYRI_SCATTER_ENTRIES
)braket
suffix:semicolon
multiline_comment|/* DMA scatter list.*/
DECL|member|csum
id|u32
id|csum
suffix:semicolon
multiline_comment|/* HW computed checksum.    */
DECL|member|ctx
id|u32
id|ctx
suffix:semicolon
DECL|member|num_sg
id|u32
id|num_sg
suffix:semicolon
multiline_comment|/* Total scatter entries.   */
)brace
suffix:semicolon
DECL|struct|myri_txd
r_struct
id|myri_txd
(brace
DECL|member|myri_gathers
r_struct
id|myri_sglist
id|myri_gathers
(braket
id|MYRI_GATHER_ENTRIES
)braket
suffix:semicolon
multiline_comment|/* DMA scatter list.  */
DECL|member|num_sg
id|u32
id|num_sg
suffix:semicolon
multiline_comment|/* Total scatter entries.   */
DECL|member|addr
id|u16
id|addr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* XXX address              */
DECL|member|chan
id|u32
id|chan
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
multiline_comment|/* Total length of packet.  */
DECL|member|csum_off
id|u32
id|csum_off
suffix:semicolon
multiline_comment|/* Where data to csum is.   */
DECL|member|csum_field
id|u32
id|csum_field
suffix:semicolon
multiline_comment|/* Where csum goes in pkt.  */
)brace
suffix:semicolon
DECL|macro|MYRINET_MTU
mdefine_line|#define MYRINET_MTU        8432
DECL|macro|RX_ALLOC_SIZE
mdefine_line|#define RX_ALLOC_SIZE      8448
DECL|macro|MYRI_PAD_LEN
mdefine_line|#define MYRI_PAD_LEN       2
DECL|macro|RX_COPY_THRESHOLD
mdefine_line|#define RX_COPY_THRESHOLD  256
multiline_comment|/* These numbers are cast in stone, new firmware is needed if&n; * you want to change them.&n; */
DECL|macro|TX_RING_MAXSIZE
mdefine_line|#define TX_RING_MAXSIZE    16
DECL|macro|RX_RING_MAXSIZE
mdefine_line|#define RX_RING_MAXSIZE    16
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE       16
DECL|macro|RX_RING_SIZE
mdefine_line|#define RX_RING_SIZE       16
multiline_comment|/* GRRR... */
DECL|function|NEXT_RX
r_static
id|__inline__
r_int
id|NEXT_RX
c_func
(paren
r_int
id|num
)paren
(brace
multiline_comment|/* XXX &gt;=??? */
r_if
c_cond
(paren
op_increment
id|num
OG
id|RX_RING_SIZE
)paren
(brace
id|num
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|num
suffix:semicolon
)brace
DECL|function|PREV_RX
r_static
id|__inline__
r_int
id|PREV_RX
c_func
(paren
r_int
id|num
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|num
OL
l_int|0
)paren
(brace
id|num
op_assign
id|RX_RING_SIZE
suffix:semicolon
)brace
r_return
id|num
suffix:semicolon
)brace
DECL|macro|NEXT_TX
mdefine_line|#define NEXT_TX(num)&t;(((num) + 1) &amp; (TX_RING_SIZE - 1))
DECL|macro|PREV_TX
mdefine_line|#define PREV_TX(num)&t;(((num) - 1) &amp; (TX_RING_SIZE - 1))
DECL|macro|TX_BUFFS_AVAIL
mdefine_line|#define TX_BUFFS_AVAIL(head, tail)&t;&t;&bslash;&n;&t;((head) &lt;= (tail) ?&t;&t;&t;&bslash;&n;&t; (head) + (TX_RING_SIZE - 1) - (tail) :&t;&bslash;&n;&t; (head) - (tail) - 1)
DECL|struct|sendq
r_struct
id|sendq
(brace
DECL|member|tail
id|u32
id|tail
suffix:semicolon
DECL|member|head
id|u32
id|head
suffix:semicolon
DECL|member|hdebug
id|u32
id|hdebug
suffix:semicolon
DECL|member|mdebug
id|u32
id|mdebug
suffix:semicolon
DECL|member|myri_txd
r_struct
id|myri_txd
id|myri_txd
(braket
id|TX_RING_MAXSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|recvq
r_struct
id|recvq
(brace
DECL|member|head
id|u32
id|head
suffix:semicolon
DECL|member|tail
id|u32
id|tail
suffix:semicolon
DECL|member|hdebug
id|u32
id|hdebug
suffix:semicolon
DECL|member|mdebug
id|u32
id|mdebug
suffix:semicolon
DECL|member|myri_rxd
r_struct
id|myri_rxd
id|myri_rxd
(braket
id|RX_RING_MAXSIZE
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MYRI_MLIST_SIZE
mdefine_line|#define MYRI_MLIST_SIZE 8
DECL|struct|mclist
r_struct
id|mclist
(brace
DECL|member|maxlen
id|u32
id|maxlen
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
DECL|member|cache
id|u32
id|cache
suffix:semicolon
DECL|struct|pair
r_struct
id|pair
(brace
DECL|member|addr
id|u8
id|addr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|val
id|u32
id|val
suffix:semicolon
DECL|member|mc_pairs
)brace
id|mc_pairs
(braket
id|MYRI_MLIST_SIZE
)braket
suffix:semicolon
DECL|member|bcast_addr
id|u8
id|bcast_addr
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|myri_channel
r_struct
id|myri_channel
(brace
DECL|member|state
id|u32
id|state
suffix:semicolon
multiline_comment|/* State of the channel.&t;*/
DECL|member|busy
id|u32
id|busy
suffix:semicolon
multiline_comment|/* Channel is busy.&t;&t;*/
DECL|member|sendq
r_struct
id|sendq
id|sendq
suffix:semicolon
multiline_comment|/* Device tx queue.&t;&t;*/
DECL|member|recvq
r_struct
id|recvq
id|recvq
suffix:semicolon
multiline_comment|/* Device rx queue.&t;&t;*/
DECL|member|recvqa
r_struct
id|recvq
id|recvqa
suffix:semicolon
multiline_comment|/* Device rx queue acked.&t;*/
DECL|member|rbytes
id|u32
id|rbytes
suffix:semicolon
multiline_comment|/* Receive bytes.&t;&t;*/
DECL|member|sbytes
id|u32
id|sbytes
suffix:semicolon
multiline_comment|/* Send bytes.&t;&t;&t;*/
DECL|member|rmsgs
id|u32
id|rmsgs
suffix:semicolon
multiline_comment|/* Receive messages.&t;&t;*/
DECL|member|smsgs
id|u32
id|smsgs
suffix:semicolon
multiline_comment|/* Send messages.&t;&t;*/
DECL|member|mclist
r_struct
id|mclist
id|mclist
suffix:semicolon
multiline_comment|/* Device multicast list.&t;*/
)brace
suffix:semicolon
multiline_comment|/* Values for per-channel state. */
DECL|macro|STATE_WFH
mdefine_line|#define STATE_WFH&t;0&t;&t;/* Waiting for HOST.&t;&t;*/
DECL|macro|STATE_WFN
mdefine_line|#define STATE_WFN&t;1&t;&t;/* Waiting for NET.&t;&t;*/
DECL|macro|STATE_READY
mdefine_line|#define STATE_READY&t;2&t;&t;/* Ready.&t;&t;&t;*/
DECL|struct|myri_shmem
r_struct
id|myri_shmem
(brace
DECL|member|addr
id|u8
id|addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Board&squot;s address.&t;&t;*/
DECL|member|nchan
id|u32
id|nchan
suffix:semicolon
multiline_comment|/* Number of channels.&t;&t;*/
DECL|member|burst
id|u32
id|burst
suffix:semicolon
multiline_comment|/* SBUS dma burst enable.&t;*/
DECL|member|shakedown
id|u32
id|shakedown
suffix:semicolon
multiline_comment|/* DarkkkkStarrr Crashesss...&t;*/
DECL|member|send
id|u32
id|send
suffix:semicolon
multiline_comment|/* Send wanted.&t;&t;&t;*/
DECL|member|imask
id|u32
id|imask
suffix:semicolon
multiline_comment|/* Interrupt enable mask.&t;*/
DECL|member|mlevel
id|u32
id|mlevel
suffix:semicolon
multiline_comment|/* Map level.&t;&t;&t;*/
DECL|member|debug
id|u32
id|debug
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Misc. debug areas.&t;&t;*/
DECL|member|channel
r_struct
id|myri_channel
id|channel
suffix:semicolon
multiline_comment|/* Only one channel on a host.&t;*/
)brace
suffix:semicolon
DECL|struct|myri_eth
r_struct
id|myri_eth
(brace
multiline_comment|/* These are frequently accessed, keep together&n;&t; * to obtain good cache hit rates.&n;&t; */
DECL|member|shmem
r_struct
id|myri_shmem
op_star
id|shmem
suffix:semicolon
multiline_comment|/* Shared data structures.    */
DECL|member|cregs
r_int
r_int
id|cregs
suffix:semicolon
multiline_comment|/* Control register space.    */
DECL|member|rqack
r_struct
id|recvq
op_star
id|rqack
suffix:semicolon
multiline_comment|/* Where we ack rx&squot;s.         */
DECL|member|rq
r_struct
id|recvq
op_star
id|rq
suffix:semicolon
multiline_comment|/* Where we put buffers.      */
DECL|member|sq
r_struct
id|sendq
op_star
id|sq
suffix:semicolon
multiline_comment|/* Where we stuff tx&squot;s.       */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Linux/NET dev struct.      */
DECL|member|tx_old
r_int
id|tx_old
suffix:semicolon
multiline_comment|/* To speed up tx cleaning.   */
DECL|member|lregs
r_int
r_int
id|lregs
suffix:semicolon
multiline_comment|/* Quick ptr to LANAI regs.   */
DECL|member|rx_skbs
r_struct
id|sk_buff
op_star
id|rx_skbs
(braket
id|RX_RING_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* RX skb&squot;s                   */
DECL|member|tx_skbs
r_struct
id|sk_buff
op_star
id|tx_skbs
(braket
id|TX_RING_SIZE
)braket
suffix:semicolon
multiline_comment|/* TX skb&squot;s                   */
DECL|member|enet_stats
r_struct
id|net_device_stats
id|enet_stats
suffix:semicolon
multiline_comment|/* Interface stats.           */
multiline_comment|/* These are less frequently accessed. */
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
multiline_comment|/* MyriCOM register space.    */
DECL|member|lanai
r_int
r_int
op_star
id|lanai
suffix:semicolon
multiline_comment|/* View 2 of register space.  */
DECL|member|lanai3
r_int
r_int
op_star
id|lanai3
suffix:semicolon
multiline_comment|/* View 3 of register space.  */
DECL|member|myri_bursts
r_int
r_int
id|myri_bursts
suffix:semicolon
multiline_comment|/* SBUS bursts.               */
DECL|member|eeprom
r_struct
id|myri_eeprom
id|eeprom
suffix:semicolon
multiline_comment|/* Local copy of EEPROM.      */
DECL|member|reg_size
r_int
r_int
id|reg_size
suffix:semicolon
multiline_comment|/* Size of register space.    */
DECL|member|shmem_base
r_int
r_int
id|shmem_base
suffix:semicolon
multiline_comment|/* Offset to shared ram.      */
DECL|member|myri_sdev
r_struct
id|sbus_dev
op_star
id|myri_sdev
suffix:semicolon
multiline_comment|/* Our SBUS device struct.    */
DECL|member|next_module
r_struct
id|myri_eth
op_star
id|next_module
suffix:semicolon
multiline_comment|/* Next in adapter chain.     */
)brace
suffix:semicolon
multiline_comment|/* We use this to acquire receive skb&squot;s that we can DMA directly into. */
DECL|macro|ALIGNED_RX_SKB_ADDR
mdefine_line|#define ALIGNED_RX_SKB_ADDR(addr) &bslash;&n;        ((((unsigned long)(addr) + (64 - 1)) &amp; ~(64 - 1)) - (unsigned long)(addr))
DECL|function|myri_alloc_skb
r_static
r_inline
r_struct
id|sk_buff
op_star
id|myri_alloc_skb
c_func
(paren
r_int
r_int
id|length
comma
r_int
id|gfp_flags
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|length
op_plus
l_int|64
comma
id|gfp_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
r_int
id|offset
op_assign
id|ALIGNED_RX_SKB_ADDR
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
id|offset
)paren
suffix:semicolon
)brace
)brace
r_return
id|skb
suffix:semicolon
)brace
macro_line|#endif /* !(_MYRI_SBUS_H) */
eof
