multiline_comment|/*&n; *  3c359.h (c) 2000 Mike Phillips (mikep@linuxtr.net) All Rights Reserved&n; *&n; *  Linux driver for 3Com 3C359 Token Link PCI XL cards.&n; *&n; *  This software may be used and distributed according to the terms&n; *  of the GNU General Public License Version 2 or (at your option) &n; *  any later verion, incorporated herein by reference.&n; */
multiline_comment|/* Memory Access Commands */
DECL|macro|IO_BYTE_READ
mdefine_line|#define IO_BYTE_READ 0x28 &lt;&lt; 24
DECL|macro|IO_BYTE_WRITE
mdefine_line|#define IO_BYTE_WRITE 0x18 &lt;&lt; 24 
DECL|macro|IO_WORD_READ
mdefine_line|#define IO_WORD_READ 0x20 &lt;&lt; 24
DECL|macro|IO_WORD_WRITE
mdefine_line|#define IO_WORD_WRITE 0x10 &lt;&lt; 24
DECL|macro|MMIO_BYTE_READ
mdefine_line|#define MMIO_BYTE_READ 0x88 &lt;&lt; 24
DECL|macro|MMIO_BYTE_WRITE
mdefine_line|#define MMIO_BYTE_WRITE 0x48 &lt;&lt; 24
DECL|macro|MMIO_WORD_READ
mdefine_line|#define MMIO_WORD_READ 0x80 &lt;&lt; 24
DECL|macro|MMIO_WORD_WRITE
mdefine_line|#define MMIO_WORD_WRITE 0x40 &lt;&lt; 24
DECL|macro|MEM_BYTE_READ
mdefine_line|#define MEM_BYTE_READ 0x8C &lt;&lt; 24
DECL|macro|MEM_BYTE_WRITE
mdefine_line|#define MEM_BYTE_WRITE 0x4C &lt;&lt; 24
DECL|macro|MEM_WORD_READ
mdefine_line|#define MEM_WORD_READ 0x84 &lt;&lt; 24
DECL|macro|MEM_WORD_WRITE
mdefine_line|#define MEM_WORD_WRITE 0x44 &lt;&lt; 24
DECL|macro|PMBAR
mdefine_line|#define PMBAR 0x1C80
DECL|macro|PMB_CPHOLD
mdefine_line|#define PMB_CPHOLD (1&lt;&lt;10)
DECL|macro|CPATTENTION
mdefine_line|#define CPATTENTION 0x180D
DECL|macro|CPA_PMBARVIS
mdefine_line|#define CPA_PMBARVIS (1&lt;&lt;7)
DECL|macro|CPA_MEMWREN
mdefine_line|#define CPA_MEMWREN (1&lt;&lt;6)
DECL|macro|SWITCHSETTINGS
mdefine_line|#define SWITCHSETTINGS 0x1C88
DECL|macro|EECONTROL
mdefine_line|#define EECONTROL 0x1C8A
DECL|macro|EEDATA
mdefine_line|#define EEDATA 0x1C8C
DECL|macro|EEREAD
mdefine_line|#define EEREAD 0x0080 
DECL|macro|EEWRITE
mdefine_line|#define EEWRITE 0x0040
DECL|macro|EEERASE
mdefine_line|#define EEERASE 0x0060
DECL|macro|EE_ENABLE_WRITE
mdefine_line|#define EE_ENABLE_WRITE 0x0030
DECL|macro|EEBUSY
mdefine_line|#define EEBUSY (1&lt;&lt;15)
DECL|macro|WRBR
mdefine_line|#define WRBR 0xCDE02
DECL|macro|WWOR
mdefine_line|#define WWOR 0xCDE04
DECL|macro|WWCR
mdefine_line|#define WWCR 0xCDE06
DECL|macro|MACSTATUS
mdefine_line|#define MACSTATUS 0xCDE08 
DECL|macro|MISR_RW
mdefine_line|#define MISR_RW 0xCDE0B
DECL|macro|MISR_AND
mdefine_line|#define MISR_AND 0xCDE2B
DECL|macro|MISR_SET
mdefine_line|#define MISR_SET 0xCDE4B
DECL|macro|RXBUFAREA
mdefine_line|#define RXBUFAREA 0xCDE10
DECL|macro|RXEARLYTHRESH
mdefine_line|#define RXEARLYTHRESH 0xCDE12
DECL|macro|TXSTARTTHRESH
mdefine_line|#define TXSTARTTHRESH 0x58
DECL|macro|DNPRIREQTHRESH
mdefine_line|#define DNPRIREQTHRESH 0x2C
DECL|macro|MISR_CSRB
mdefine_line|#define MISR_CSRB (1&lt;&lt;5)
DECL|macro|MISR_RASB
mdefine_line|#define MISR_RASB (1&lt;&lt;4)
DECL|macro|MISR_SRBFR
mdefine_line|#define MISR_SRBFR (1&lt;&lt;3)
DECL|macro|MISR_ASBFR
mdefine_line|#define MISR_ASBFR (1&lt;&lt;2)
DECL|macro|MISR_ARBF
mdefine_line|#define MISR_ARBF (1&lt;&lt;1) 
multiline_comment|/* MISR Flags memory locations */
DECL|macro|MF_SSBF
mdefine_line|#define MF_SSBF 0xDFFE0 
DECL|macro|MF_ARBF
mdefine_line|#define MF_ARBF 0xDFFE1
DECL|macro|MF_ASBFR
mdefine_line|#define MF_ASBFR 0xDFFE2
DECL|macro|MF_SRBFR
mdefine_line|#define MF_SRBFR 0xDFFE3
DECL|macro|MF_RASB
mdefine_line|#define MF_RASB 0xDFFE4
DECL|macro|MF_CSRB
mdefine_line|#define MF_CSRB 0xDFFE5
DECL|macro|MMIO_MACDATA
mdefine_line|#define MMIO_MACDATA 0x10 
DECL|macro|MMIO_MAC_ACCESS_CMD
mdefine_line|#define MMIO_MAC_ACCESS_CMD 0x14
DECL|macro|MMIO_TIMER
mdefine_line|#define MMIO_TIMER 0x1A
DECL|macro|MMIO_DMA_CTRL
mdefine_line|#define MMIO_DMA_CTRL 0x20
DECL|macro|MMIO_DNLISTPTR
mdefine_line|#define MMIO_DNLISTPTR 0x24
DECL|macro|MMIO_HASHFILTER
mdefine_line|#define MMIO_HASHFILTER 0x28
DECL|macro|MMIO_CONFIG
mdefine_line|#define MMIO_CONFIG 0x29
DECL|macro|MMIO_DNPRIREQTHRESH
mdefine_line|#define MMIO_DNPRIREQTHRESH 0x2C
DECL|macro|MMIO_DNPOLL
mdefine_line|#define MMIO_DNPOLL 0x2D
DECL|macro|MMIO_UPPKTSTATUS
mdefine_line|#define MMIO_UPPKTSTATUS 0x30
DECL|macro|MMIO_FREETIMER
mdefine_line|#define MMIO_FREETIMER 0x34
DECL|macro|MMIO_COUNTDOWN
mdefine_line|#define MMIO_COUNTDOWN 0x36
DECL|macro|MMIO_UPLISTPTR
mdefine_line|#define MMIO_UPLISTPTR 0x38
DECL|macro|MMIO_UPPOLL
mdefine_line|#define MMIO_UPPOLL 0x3C
DECL|macro|MMIO_UPBURSTTHRESH
mdefine_line|#define MMIO_UPBURSTTHRESH 0x40
DECL|macro|MMIO_DNBURSTTHRESH
mdefine_line|#define MMIO_DNBURSTTHRESH 0x41
DECL|macro|MMIO_INTSTATUS_AUTO
mdefine_line|#define MMIO_INTSTATUS_AUTO 0x56
DECL|macro|MMIO_TXSTARTTHRESH
mdefine_line|#define MMIO_TXSTARTTHRESH 0x58
DECL|macro|MMIO_INTERRUPTENABLE
mdefine_line|#define MMIO_INTERRUPTENABLE 0x5A
DECL|macro|MMIO_INDICATIONENABLE
mdefine_line|#define MMIO_INDICATIONENABLE 0x5C
DECL|macro|MMIO_COMMAND
mdefine_line|#define MMIO_COMMAND 0x5E  /* These two are meant to be the same */
DECL|macro|MMIO_INTSTATUS
mdefine_line|#define MMIO_INTSTATUS 0x5E /* Makes the code more readable this way */
DECL|macro|INTSTAT_CMD_IN_PROGRESS
mdefine_line|#define INTSTAT_CMD_IN_PROGRESS (1&lt;&lt;12) 
DECL|macro|INTSTAT_SRB
mdefine_line|#define INTSTAT_SRB (1&lt;&lt;14)
DECL|macro|INTSTAT_INTLATCH
mdefine_line|#define INTSTAT_INTLATCH (1&lt;&lt;0)
multiline_comment|/* Indication / Interrupt Mask &n; * Annoyingly the bits to be set in the indication and interrupt enable&n; * do not match with the actual bits received in the interrupt, although&n; * they are in the same order. &n; * The mapping for the indication / interrupt are:&n; * Bit&t;Indication / Interrupt&n; *   0&t;HostError&n; *   1&t;txcomplete&n; *   2&t;updneeded&n; *   3&t;rxcomplete&n; *   4&t;intrequested&n; *   5&t;macerror&n; *   6  dncomplete&n; *   7&t;upcomplete&n; *   8&t;txunderrun&n; *   9&t;asbf&n; *  10&t;srbr&n; *  11&t;arbc&n; *&n; *  The only ones we don&squot;t want to receive are txcomplete and rxcomplete&n; *  we use dncomplete and upcomplete instead.&n; */
DECL|macro|INT_MASK
mdefine_line|#define INT_MASK 0xFF5
multiline_comment|/* Note the subtle difference here, IND and INT */
DECL|macro|SETINDENABLE
mdefine_line|#define SETINDENABLE (8&lt;&lt;12)
DECL|macro|SETINTENABLE
mdefine_line|#define SETINTENABLE (7&lt;&lt;12)
DECL|macro|SRBBIT
mdefine_line|#define SRBBIT (1&lt;&lt;10)
DECL|macro|ASBBIT
mdefine_line|#define ASBBIT (1&lt;&lt;9)
DECL|macro|ARBBIT
mdefine_line|#define ARBBIT (1&lt;&lt;11)
DECL|macro|SRB
mdefine_line|#define SRB 0xDFE90
DECL|macro|ASB
mdefine_line|#define ASB 0xDFED0
DECL|macro|ARB
mdefine_line|#define ARB 0xD0000
DECL|macro|SCRATCH
mdefine_line|#define SCRATCH 0xDFEF0
DECL|macro|INT_REQUEST
mdefine_line|#define INT_REQUEST 0x6000 /* (6 &lt;&lt; 12) */
DECL|macro|ACK_INTERRUPT
mdefine_line|#define ACK_INTERRUPT 0x6800 /* (13 &lt;&lt;11) */
DECL|macro|GLOBAL_RESET
mdefine_line|#define GLOBAL_RESET 0x00 
DECL|macro|DNDISABLE
mdefine_line|#define DNDISABLE 0x5000 
DECL|macro|DNENABLE
mdefine_line|#define DNENABLE 0x4800 
DECL|macro|DNSTALL
mdefine_line|#define DNSTALL 0x3002
DECL|macro|DNRESET
mdefine_line|#define DNRESET 0x5800
DECL|macro|DNUNSTALL
mdefine_line|#define DNUNSTALL 0x3003
DECL|macro|UPRESET
mdefine_line|#define UPRESET 0x2800
DECL|macro|UPSTALL
mdefine_line|#define UPSTALL 0x3000
DECL|macro|UPUNSTALL
mdefine_line|#define UPUNSTALL 0x3001
DECL|macro|SETCONFIG
mdefine_line|#define SETCONFIG 0x4000
DECL|macro|SETTXSTARTTHRESH
mdefine_line|#define SETTXSTARTTHRESH 0x9800 
multiline_comment|/* Received Interrupts */
DECL|macro|ASBFINT
mdefine_line|#define ASBFINT (1&lt;&lt;13)
DECL|macro|SRBRINT
mdefine_line|#define SRBRINT (1&lt;&lt;14)
DECL|macro|ARBCINT
mdefine_line|#define ARBCINT (1&lt;&lt;15)
DECL|macro|TXUNDERRUN
mdefine_line|#define TXUNDERRUN (1&lt;&lt;11)
DECL|macro|UPCOMPINT
mdefine_line|#define UPCOMPINT (1&lt;&lt;10)
DECL|macro|DNCOMPINT
mdefine_line|#define DNCOMPINT (1&lt;&lt;9)
DECL|macro|HARDERRINT
mdefine_line|#define HARDERRINT (1&lt;&lt;7)
DECL|macro|RXCOMPLETE
mdefine_line|#define RXCOMPLETE (1&lt;&lt;4)
DECL|macro|TXCOMPINT
mdefine_line|#define TXCOMPINT (1&lt;&lt;2)
DECL|macro|HOSTERRINT
mdefine_line|#define HOSTERRINT (1&lt;&lt;1)
multiline_comment|/* Receive descriptor bits */
DECL|macro|RXOVERRUN
mdefine_line|#define RXOVERRUN (1&lt;&lt;19)
DECL|macro|RXFC
mdefine_line|#define RXFC (1&lt;&lt;21)
DECL|macro|RXAR
mdefine_line|#define RXAR (1&lt;&lt;22)
DECL|macro|RXUPDCOMPLETE
mdefine_line|#define RXUPDCOMPLETE (1&lt;&lt;23)
DECL|macro|RXUPDFULL
mdefine_line|#define RXUPDFULL (1&lt;&lt;24)
DECL|macro|RXUPLASTFRAG
mdefine_line|#define RXUPLASTFRAG (1&lt;&lt;31)
multiline_comment|/* Transmit descriptor bits */
DECL|macro|TXDNCOMPLETE
mdefine_line|#define TXDNCOMPLETE (1&lt;&lt;16)
DECL|macro|TXTXINDICATE
mdefine_line|#define TXTXINDICATE (1&lt;&lt;27)
DECL|macro|TXDPDEMPTY
mdefine_line|#define TXDPDEMPTY (1&lt;&lt;29)
DECL|macro|TXDNINDICATE
mdefine_line|#define TXDNINDICATE (1&lt;&lt;31)
DECL|macro|TXDNFRAGLAST
mdefine_line|#define TXDNFRAGLAST (1&lt;&lt;31)
multiline_comment|/* Interrupts to Acknowledge */
DECL|macro|LATCH_ACK
mdefine_line|#define LATCH_ACK 1 
DECL|macro|TXCOMPACK
mdefine_line|#define TXCOMPACK (1&lt;&lt;1)
DECL|macro|INTREQACK
mdefine_line|#define INTREQACK (1&lt;&lt;2)
DECL|macro|DNCOMPACK
mdefine_line|#define DNCOMPACK (1&lt;&lt;3)
DECL|macro|UPCOMPACK
mdefine_line|#define UPCOMPACK (1&lt;&lt;4)
DECL|macro|ASBFACK
mdefine_line|#define ASBFACK (1&lt;&lt;5)
DECL|macro|SRBRACK
mdefine_line|#define SRBRACK (1&lt;&lt;6)
DECL|macro|ARBCACK
mdefine_line|#define ARBCACK (1&lt;&lt;7)
DECL|macro|XL_IO_SPACE
mdefine_line|#define XL_IO_SPACE 128
DECL|macro|SRB_COMMAND_SIZE
mdefine_line|#define SRB_COMMAND_SIZE 50
multiline_comment|/* Adapter Commands */
DECL|macro|REQUEST_INT
mdefine_line|#define REQUEST_INT 0x00
DECL|macro|MODIFY_OPEN_PARMS
mdefine_line|#define MODIFY_OPEN_PARMS 0x01
DECL|macro|RESTORE_OPEN_PARMS
mdefine_line|#define RESTORE_OPEN_PARMS 0x02
DECL|macro|OPEN_NIC
mdefine_line|#define OPEN_NIC 0x03
DECL|macro|CLOSE_NIC
mdefine_line|#define CLOSE_NIC 0x04
DECL|macro|SET_SLEEP_MODE
mdefine_line|#define SET_SLEEP_MODE 0x05
DECL|macro|SET_GROUP_ADDRESS
mdefine_line|#define SET_GROUP_ADDRESS 0x06
DECL|macro|SET_FUNC_ADDRESS
mdefine_line|#define SET_FUNC_ADDRESS 0x07
DECL|macro|READ_LOG
mdefine_line|#define READ_LOG 0x08
DECL|macro|SET_MULTICAST_MODE
mdefine_line|#define SET_MULTICAST_MODE 0x0C
DECL|macro|CHANGE_WAKEUP_PATTERN
mdefine_line|#define CHANGE_WAKEUP_PATTERN 0x0D
DECL|macro|GET_STATISTICS
mdefine_line|#define GET_STATISTICS 0x13
DECL|macro|SET_RECEIVE_MODE
mdefine_line|#define SET_RECEIVE_MODE 0x1F
multiline_comment|/* ARB Commands */
DECL|macro|RECEIVE_DATA
mdefine_line|#define RECEIVE_DATA 0x81
DECL|macro|RING_STATUS_CHANGE
mdefine_line|#define RING_STATUS_CHANGE 0x84
multiline_comment|/* ASB Commands */
DECL|macro|ASB_RECEIVE_DATE
mdefine_line|#define ASB_RECEIVE_DATE 0x81 
multiline_comment|/* Defines for LAN STATUS CHANGE reports */
DECL|macro|LSC_SIG_LOSS
mdefine_line|#define LSC_SIG_LOSS 0x8000
DECL|macro|LSC_HARD_ERR
mdefine_line|#define LSC_HARD_ERR 0x4000
DECL|macro|LSC_SOFT_ERR
mdefine_line|#define LSC_SOFT_ERR 0x2000
DECL|macro|LSC_TRAN_BCN
mdefine_line|#define LSC_TRAN_BCN 0x1000
DECL|macro|LSC_LWF
mdefine_line|#define LSC_LWF      0x0800
DECL|macro|LSC_ARW
mdefine_line|#define LSC_ARW      0x0400
DECL|macro|LSC_FPE
mdefine_line|#define LSC_FPE      0x0200
DECL|macro|LSC_RR
mdefine_line|#define LSC_RR       0x0100
DECL|macro|LSC_CO
mdefine_line|#define LSC_CO       0x0080
DECL|macro|LSC_SS
mdefine_line|#define LSC_SS       0x0040
DECL|macro|LSC_RING_REC
mdefine_line|#define LSC_RING_REC 0x0020
DECL|macro|LSC_SR_CO
mdefine_line|#define LSC_SR_CO    0x0010
DECL|macro|LSC_FDX_MODE
mdefine_line|#define LSC_FDX_MODE 0x0004
DECL|macro|XL_MAX_ADAPTERS
mdefine_line|#define XL_MAX_ADAPTERS 8 /* 0x08 __MODULE_STRING can&squot;t hand 0xnn */
multiline_comment|/* 3c359 defaults for buffers */
DECL|macro|XL_RX_RING_SIZE
mdefine_line|#define XL_RX_RING_SIZE 16 /* must be a power of 2 */
DECL|macro|XL_TX_RING_SIZE
mdefine_line|#define XL_TX_RING_SIZE 16 /* must be a power of 2 */
DECL|macro|PKT_BUF_SZ
mdefine_line|#define PKT_BUF_SZ 4096 /* Default packet size */
multiline_comment|/* 3c359 data structures */
DECL|struct|xl_tx_desc
r_struct
id|xl_tx_desc
(brace
DECL|member|dnnextptr
id|u32
id|dnnextptr
suffix:semicolon
DECL|member|framestartheader
id|u32
id|framestartheader
suffix:semicolon
DECL|member|buffer
id|u32
id|buffer
suffix:semicolon
DECL|member|buffer_length
id|u32
id|buffer_length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xl_rx_desc
r_struct
id|xl_rx_desc
(brace
DECL|member|upnextptr
id|u32
id|upnextptr
suffix:semicolon
DECL|member|framestatus
id|u32
id|framestatus
suffix:semicolon
DECL|member|upfragaddr
id|u32
id|upfragaddr
suffix:semicolon
DECL|member|upfraglen
id|u32
id|upfraglen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xl_private
r_struct
id|xl_private
(brace
multiline_comment|/* These two structures must be aligned on 8 byte boundaries */
multiline_comment|/* struct xl_rx_desc xl_rx_ring[XL_RX_RING_SIZE]; */
multiline_comment|/* struct xl_tx_desc xl_tx_ring[XL_TX_RING_SIZE]; */
DECL|member|xl_rx_ring
r_struct
id|xl_rx_desc
op_star
id|xl_rx_ring
suffix:semicolon
DECL|member|xl_tx_ring
r_struct
id|xl_tx_desc
op_star
id|xl_tx_ring
suffix:semicolon
DECL|member|tx_ring_skb
DECL|member|rx_ring_skb
r_struct
id|sk_buff
op_star
id|tx_ring_skb
(braket
id|XL_TX_RING_SIZE
)braket
comma
op_star
id|rx_ring_skb
(braket
id|XL_RX_RING_SIZE
)braket
suffix:semicolon
DECL|member|tx_ring_head
DECL|member|tx_ring_tail
r_int
id|tx_ring_head
comma
id|tx_ring_tail
suffix:semicolon
DECL|member|rx_ring_tail
DECL|member|rx_ring_no
r_int
id|rx_ring_tail
comma
id|rx_ring_no
suffix:semicolon
DECL|member|free_ring_entries
r_int
id|free_ring_entries
suffix:semicolon
DECL|member|srb
id|u16
id|srb
suffix:semicolon
DECL|member|arb
id|u16
id|arb
suffix:semicolon
DECL|member|asb
id|u16
id|asb
suffix:semicolon
DECL|member|xl_mmio
id|u8
op_star
id|xl_mmio
suffix:semicolon
DECL|member|xl_card_name
r_char
op_star
id|xl_card_name
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|xl_lock
id|spinlock_t
id|xl_lock
suffix:semicolon
DECL|member|srb_queued
r_volatile
r_int
id|srb_queued
suffix:semicolon
DECL|member|srb_wait
r_struct
id|wait_queue
op_star
id|srb_wait
suffix:semicolon
DECL|member|asb_queued
r_volatile
r_int
id|asb_queued
suffix:semicolon
DECL|member|xl_stats
r_struct
id|net_device_stats
id|xl_stats
suffix:semicolon
DECL|member|mac_buffer
id|u16
id|mac_buffer
suffix:semicolon
DECL|member|xl_lan_status
id|u16
id|xl_lan_status
suffix:semicolon
DECL|member|xl_ring_speed
id|u8
id|xl_ring_speed
suffix:semicolon
DECL|member|pkt_buf_sz
id|u16
id|pkt_buf_sz
suffix:semicolon
DECL|member|xl_message_level
id|u8
id|xl_message_level
suffix:semicolon
DECL|member|xl_copy_all_options
id|u16
id|xl_copy_all_options
suffix:semicolon
DECL|member|xl_functional_addr
r_int
r_char
id|xl_functional_addr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|xl_addr_table_addr
DECL|member|xl_parms_addr
id|u16
id|xl_addr_table_addr
comma
id|xl_parms_addr
suffix:semicolon
DECL|member|xl_laa
id|u8
id|xl_laa
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|rx_ring_dma_addr
id|u32
id|rx_ring_dma_addr
suffix:semicolon
DECL|member|tx_ring_dma_addr
id|u32
id|tx_ring_dma_addr
suffix:semicolon
)brace
suffix:semicolon
eof
