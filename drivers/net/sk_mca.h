macro_line|#ifndef _SK_MCA_INCLUDE_
DECL|macro|_SK_MCA_INCLUDE_
mdefine_line|#define _SK_MCA_INCLUDE_
macro_line|#ifdef _SK_MCA_DRIVER_
multiline_comment|/* version-dependent functions/structures */
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020318
DECL|macro|SKMCA_READB
mdefine_line|#define SKMCA_READB(addr) isa_readb(addr)
DECL|macro|SKMCA_READW
mdefine_line|#define SKMCA_READW(addr) isa_readw(addr)
DECL|macro|SKMCA_WRITEB
mdefine_line|#define SKMCA_WRITEB(data, addr) isa_writeb(data, addr)
DECL|macro|SKMCA_WRITEW
mdefine_line|#define SKMCA_WRITEW(data, addr) isa_writew(data, addr)
DECL|macro|SKMCA_TOIO
mdefine_line|#define SKMCA_TOIO(dest, src, len) isa_memcpy_toio(dest, src, len)
DECL|macro|SKMCA_FROMIO
mdefine_line|#define SKMCA_FROMIO(dest, src, len) isa_memcpy_fromio(dest, src, len)
DECL|macro|SKMCA_SETIO
mdefine_line|#define SKMCA_SETIO(dest, val, len) isa_memset_io(dest, val, len)
DECL|macro|SKMCA_NETDEV
mdefine_line|#define SKMCA_NETDEV net_device
macro_line|#else
DECL|macro|SKMCA_READB
mdefine_line|#define SKMCA_READB(addr) readb(addr)
DECL|macro|SKMCA_READW
mdefine_line|#define SKMCA_READW(addr) readw(addr)
DECL|macro|SKMCA_WRITEB
mdefine_line|#define SKMCA_WRITEB(data, addr) writeb(data, addr)
DECL|macro|SKMCA_WRITEW
mdefine_line|#define SKMCA_WRITEW(data, addr) writew(data, addr)
DECL|macro|SKMCA_TOIO
mdefine_line|#define SKMCA_TOIO(dest, src, len) memcpy_toio(dest, src, len)
DECL|macro|SKMCA_FROMIO
mdefine_line|#define SKMCA_FROMIO(dest, src, len) memcpy_fromio(dest, src, len)
DECL|macro|SKMCA_SETIO
mdefine_line|#define SKMCA_SETIO(dest, val, len) memset_io(dest, val, len)
DECL|macro|SKMCA_NETDEV
mdefine_line|#define SKMCA_NETDEV device
macro_line|#endif
multiline_comment|/* Adapter ID&squot;s */
DECL|macro|SKNET_MCA_ID
mdefine_line|#define SKNET_MCA_ID 0x6afd
DECL|macro|SKNET_JUNIOR_MCA_ID
mdefine_line|#define SKNET_JUNIOR_MCA_ID 0x6be9
multiline_comment|/* media enumeration - defined in a way that it fits onto the MC2+&squot;s&n;   POS registers... */
DECL|enumerator|Media_10Base2
DECL|enumerator|Media_10BaseT
r_typedef
r_enum
(brace
id|Media_10Base2
comma
id|Media_10BaseT
comma
DECL|enumerator|Media_10Base5
DECL|enumerator|Media_Unknown
DECL|enumerator|Media_Count
id|Media_10Base5
comma
id|Media_Unknown
comma
id|Media_Count
DECL|typedef|skmca_medium
)brace
id|skmca_medium
suffix:semicolon
multiline_comment|/* private structure */
r_typedef
r_struct
(brace
DECL|member|slot
r_int
r_int
id|slot
suffix:semicolon
multiline_comment|/* MCA-Slot-#                       */
DECL|member|macbase
r_int
r_int
id|macbase
suffix:semicolon
multiline_comment|/* base address of MAC address PROM */
DECL|member|ioregaddr
r_int
r_int
id|ioregaddr
suffix:semicolon
multiline_comment|/* address of I/O-register (Lo)     */
DECL|member|ctrladdr
r_int
r_int
id|ctrladdr
suffix:semicolon
multiline_comment|/* address of control/stat register */
DECL|member|cmdaddr
r_int
r_int
id|cmdaddr
suffix:semicolon
multiline_comment|/* address of I/O-command register  */
DECL|member|nextrx
r_int
id|nextrx
suffix:semicolon
multiline_comment|/* index of next RX descriptor to&n;&t;&t;&t;&t;   be read                          */
DECL|member|nexttxput
r_int
id|nexttxput
suffix:semicolon
multiline_comment|/* index of next free TX descriptor */
DECL|member|nexttxdone
r_int
id|nexttxdone
suffix:semicolon
multiline_comment|/* index of next TX descriptor to &n;&t;&t;&t;&t;   be finished                      */
DECL|member|txbusy
r_int
id|txbusy
suffix:semicolon
multiline_comment|/* # of busy TX descriptors         */
DECL|member|stat
r_struct
id|net_device_stats
id|stat
suffix:semicolon
multiline_comment|/* packet statistics            */
DECL|member|realirq
r_int
id|realirq
suffix:semicolon
multiline_comment|/* memorizes actual IRQ, even when &n;&t;&t;&t;&t;   currently not allocated          */
DECL|member|medium
id|skmca_medium
id|medium
suffix:semicolon
multiline_comment|/* physical cannector               */
DECL|typedef|skmca_priv
)brace
id|skmca_priv
suffix:semicolon
multiline_comment|/* card registers: control/status register bits */
DECL|macro|CTRL_ADR_DATA
mdefine_line|#define CTRL_ADR_DATA      0&t;/* Bit 0 = 0 -&gt;access data register  */
DECL|macro|CTRL_ADR_RAP
mdefine_line|#define CTRL_ADR_RAP       1&t;/* Bit 0 = 1 -&gt;access RAP register   */
DECL|macro|CTRL_RW_WRITE
mdefine_line|#define CTRL_RW_WRITE      0&t;/* Bit 1 = 0 -&gt;write register        */
DECL|macro|CTRL_RW_READ
mdefine_line|#define CTRL_RW_READ       2&t;/* Bit 1 = 1 -&gt;read register         */
DECL|macro|CTRL_RESET_ON
mdefine_line|#define CTRL_RESET_ON      0&t;/* Bit 3 = 0 -&gt;reset board           */
DECL|macro|CTRL_RESET_OFF
mdefine_line|#define CTRL_RESET_OFF     8&t;/* Bit 3 = 1 -&gt;no reset of board     */
DECL|macro|STAT_ADR_DATA
mdefine_line|#define STAT_ADR_DATA      0&t;/* Bit 0 of ctrl register read back  */
DECL|macro|STAT_ADR_RAP
mdefine_line|#define STAT_ADR_RAP       1
DECL|macro|STAT_RW_WRITE
mdefine_line|#define STAT_RW_WRITE      0&t;/* Bit 1 of ctrl register read back  */
DECL|macro|STAT_RW_READ
mdefine_line|#define STAT_RW_READ       2
DECL|macro|STAT_RESET_ON
mdefine_line|#define STAT_RESET_ON      0&t;/* Bit 3 of ctrl register read back  */
DECL|macro|STAT_RESET_OFF
mdefine_line|#define STAT_RESET_OFF     8
DECL|macro|STAT_IRQ_ACT
mdefine_line|#define STAT_IRQ_ACT       0&t;/* interrupt pending                 */
DECL|macro|STAT_IRQ_NOACT
mdefine_line|#define STAT_IRQ_NOACT     16&t;/* no interrupt pending              */
DECL|macro|STAT_IO_NOBUSY
mdefine_line|#define STAT_IO_NOBUSY     0&t;/* no transfer busy                  */
DECL|macro|STAT_IO_BUSY
mdefine_line|#define STAT_IO_BUSY       32&t;/* transfer busy                     */
multiline_comment|/* I/O command register bits */
DECL|macro|IOCMD_GO
mdefine_line|#define IOCMD_GO           128&t;/* Bit 7 = 1 -&gt; start register xfer  */
multiline_comment|/* LANCE registers */
DECL|macro|LANCE_CSR0
mdefine_line|#define LANCE_CSR0         0&t;/* Status/Control                    */
DECL|macro|CSR0_ERR
mdefine_line|#define CSR0_ERR           0x8000&t;/* general error flag                */
DECL|macro|CSR0_BABL
mdefine_line|#define CSR0_BABL          0x4000&t;/* transmitter timeout               */
DECL|macro|CSR0_CERR
mdefine_line|#define CSR0_CERR          0x2000&t;/* collision error                   */
DECL|macro|CSR0_MISS
mdefine_line|#define CSR0_MISS          0x1000&t;/* lost Rx block                     */
DECL|macro|CSR0_MERR
mdefine_line|#define CSR0_MERR          0x0800&t;/* memory access error               */
DECL|macro|CSR0_RINT
mdefine_line|#define CSR0_RINT          0x0400&t;/* receiver interrupt                */
DECL|macro|CSR0_TINT
mdefine_line|#define CSR0_TINT          0x0200&t;/* transmitter interrupt             */
DECL|macro|CSR0_IDON
mdefine_line|#define CSR0_IDON          0x0100&t;/* initialization done               */
DECL|macro|CSR0_INTR
mdefine_line|#define CSR0_INTR          0x0080&t;/* general interrupt flag            */
DECL|macro|CSR0_INEA
mdefine_line|#define CSR0_INEA          0x0040&t;/* interrupt enable                  */
DECL|macro|CSR0_RXON
mdefine_line|#define CSR0_RXON          0x0020&t;/* receiver enabled                  */
DECL|macro|CSR0_TXON
mdefine_line|#define CSR0_TXON          0x0010&t;/* transmitter enabled               */
DECL|macro|CSR0_TDMD
mdefine_line|#define CSR0_TDMD          0x0008&t;/* force transmission now            */
DECL|macro|CSR0_STOP
mdefine_line|#define CSR0_STOP          0x0004&t;/* stop LANCE                        */
DECL|macro|CSR0_STRT
mdefine_line|#define CSR0_STRT          0x0002&t;/* start LANCE                       */
DECL|macro|CSR0_INIT
mdefine_line|#define CSR0_INIT          0x0001&t;/* read initialization block         */
DECL|macro|LANCE_CSR1
mdefine_line|#define LANCE_CSR1         1&t;/* addr bit 0..15 of initialization  */
DECL|macro|LANCE_CSR2
mdefine_line|#define LANCE_CSR2         2&t;/*          16..23 block             */
DECL|macro|LANCE_CSR3
mdefine_line|#define LANCE_CSR3         3&t;/* Bus control                       */
DECL|macro|CSR3_BCON_HOLD
mdefine_line|#define CSR3_BCON_HOLD     0&t;/* Bit 0 = 0 -&gt; BM1,BM0,HOLD         */
DECL|macro|CSR3_BCON_BUSRQ
mdefine_line|#define CSR3_BCON_BUSRQ    1&t;/* Bit 0 = 1 -&gt; BUSAK0,BYTE,BUSRQ    */
DECL|macro|CSR3_ALE_HIGH
mdefine_line|#define CSR3_ALE_HIGH      0&t;/* Bit 1 = 0 -&gt; ALE asserted high    */
DECL|macro|CSR3_ALE_LOW
mdefine_line|#define CSR3_ALE_LOW       2&t;/* Bit 1 = 1 -&gt; ALE asserted low     */
DECL|macro|CSR3_BSWAP_OFF
mdefine_line|#define CSR3_BSWAP_OFF     0&t;/* Bit 2 = 0 -&gt; no byte swap         */
DECL|macro|CSR3_BSWAP_ON
mdefine_line|#define CSR3_BSWAP_ON      0&t;/* Bit 2 = 1 -&gt; byte swap            */
multiline_comment|/* LANCE structures */
r_typedef
r_struct
(brace
multiline_comment|/* LANCE initialization block        */
DECL|member|Mode
id|u16
id|Mode
suffix:semicolon
multiline_comment|/* mode flags                        */
DECL|member|PAdr
id|u8
id|PAdr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* MAC address                       */
DECL|member|LAdrF
id|u8
id|LAdrF
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Multicast filter                  */
DECL|member|RdrP
id|u32
id|RdrP
suffix:semicolon
multiline_comment|/* Receive descriptor                */
DECL|member|TdrP
id|u32
id|TdrP
suffix:semicolon
multiline_comment|/* Transmit descriptor               */
DECL|typedef|LANCE_InitBlock
)brace
id|LANCE_InitBlock
suffix:semicolon
multiline_comment|/* Mode flags init block */
DECL|macro|LANCE_INIT_PROM
mdefine_line|#define LANCE_INIT_PROM    0x8000&t;/* enable promiscous mode            */
DECL|macro|LANCE_INIT_INTL
mdefine_line|#define LANCE_INIT_INTL    0x0040&t;/* internal loopback                 */
DECL|macro|LANCE_INIT_DRTY
mdefine_line|#define LANCE_INIT_DRTY    0x0020&t;/* disable retry                     */
DECL|macro|LANCE_INIT_COLL
mdefine_line|#define LANCE_INIT_COLL    0x0010&t;/* force collision                   */
DECL|macro|LANCE_INIT_DTCR
mdefine_line|#define LANCE_INIT_DTCR    0x0008&t;/* disable transmit CRC              */
DECL|macro|LANCE_INIT_LOOP
mdefine_line|#define LANCE_INIT_LOOP    0x0004&t;/* loopback                          */
DECL|macro|LANCE_INIT_DTX
mdefine_line|#define LANCE_INIT_DTX     0x0002&t;/* disable transmitter               */
DECL|macro|LANCE_INIT_DRX
mdefine_line|#define LANCE_INIT_DRX     0x0001&t;/* disable receiver                  */
r_typedef
r_struct
(brace
multiline_comment|/* LANCE Tx descriptor               */
DECL|member|LowAddr
id|u16
id|LowAddr
suffix:semicolon
multiline_comment|/* bit 0..15 of address              */
DECL|member|Flags
id|u16
id|Flags
suffix:semicolon
multiline_comment|/* bit 16..23 of address + Flags     */
DECL|member|Len
id|u16
id|Len
suffix:semicolon
multiline_comment|/* 2s complement of packet length    */
DECL|member|Status
id|u16
id|Status
suffix:semicolon
multiline_comment|/* Result of transmission            */
DECL|typedef|LANCE_TxDescr
)brace
id|LANCE_TxDescr
suffix:semicolon
DECL|macro|TXDSCR_FLAGS_OWN
mdefine_line|#define TXDSCR_FLAGS_OWN   0x8000&t;/* LANCE owns descriptor             */
DECL|macro|TXDSCR_FLAGS_ERR
mdefine_line|#define TXDSCR_FLAGS_ERR   0x4000&t;/* summary error flag                */
DECL|macro|TXDSCR_FLAGS_MORE
mdefine_line|#define TXDSCR_FLAGS_MORE  0x1000&t;/* more than one retry needed?       */
DECL|macro|TXDSCR_FLAGS_ONE
mdefine_line|#define TXDSCR_FLAGS_ONE   0x0800&t;/* one retry?                        */
DECL|macro|TXDSCR_FLAGS_DEF
mdefine_line|#define TXDSCR_FLAGS_DEF   0x0400&t;/* transmission deferred?            */
DECL|macro|TXDSCR_FLAGS_STP
mdefine_line|#define TXDSCR_FLAGS_STP   0x0200&t;/* first packet in chain?            */
DECL|macro|TXDSCR_FLAGS_ENP
mdefine_line|#define TXDSCR_FLAGS_ENP   0x0100&t;/* last packet in chain?             */
DECL|macro|TXDSCR_STATUS_BUFF
mdefine_line|#define TXDSCR_STATUS_BUFF 0x8000&t;/* buffer error?                     */
DECL|macro|TXDSCR_STATUS_UFLO
mdefine_line|#define TXDSCR_STATUS_UFLO 0x4000&t;/* silo underflow during transmit?   */
DECL|macro|TXDSCR_STATUS_LCOL
mdefine_line|#define TXDSCR_STATUS_LCOL 0x1000&t;/* late collision?                   */
DECL|macro|TXDSCR_STATUS_LCAR
mdefine_line|#define TXDSCR_STATUS_LCAR 0x0800&t;/* loss of carrier?                  */
DECL|macro|TXDSCR_STATUS_RTRY
mdefine_line|#define TXDSCR_STATUS_RTRY 0x0400&t;/* retry error?                      */
r_typedef
r_struct
(brace
multiline_comment|/* LANCE Rx descriptor               */
DECL|member|LowAddr
id|u16
id|LowAddr
suffix:semicolon
multiline_comment|/* bit 0..15 of address              */
DECL|member|Flags
id|u16
id|Flags
suffix:semicolon
multiline_comment|/* bit 16..23 of address + Flags     */
DECL|member|MaxLen
id|u16
id|MaxLen
suffix:semicolon
multiline_comment|/* 2s complement of buffer length    */
DECL|member|Len
id|u16
id|Len
suffix:semicolon
multiline_comment|/* packet length                     */
DECL|typedef|LANCE_RxDescr
)brace
id|LANCE_RxDescr
suffix:semicolon
DECL|macro|RXDSCR_FLAGS_OWN
mdefine_line|#define RXDSCR_FLAGS_OWN   0x8000&t;/* LANCE owns descriptor             */
DECL|macro|RXDSCR_FLAGS_ERR
mdefine_line|#define RXDSCR_FLAGS_ERR   0x4000&t;/* summary error flag                */
DECL|macro|RXDSCR_FLAGS_FRAM
mdefine_line|#define RXDSCR_FLAGS_FRAM  0x2000&t;/* framing error flag                */
DECL|macro|RXDSCR_FLAGS_OFLO
mdefine_line|#define RXDSCR_FLAGS_OFLO  0x1000&t;/* FIFO overflow?                    */
DECL|macro|RXDSCR_FLAGS_CRC
mdefine_line|#define RXDSCR_FLAGS_CRC   0x0800&t;/* CRC error?                        */
DECL|macro|RXDSCR_FLAGS_BUFF
mdefine_line|#define RXDSCR_FLAGS_BUFF  0x0400&t;/* buffer error?                     */
DECL|macro|RXDSCR_FLAGS_STP
mdefine_line|#define RXDSCR_FLAGS_STP   0x0200&t;/* first packet in chain?            */
DECL|macro|RXDCSR_FLAGS_ENP
mdefine_line|#define RXDCSR_FLAGS_ENP   0x0100&t;/* last packet in chain?             */
multiline_comment|/* RAM layout */
DECL|macro|TXCOUNT
mdefine_line|#define TXCOUNT            4&t;/* length of TX descriptor queue     */
DECL|macro|LTXCOUNT
mdefine_line|#define LTXCOUNT           2&t;/* log2 of it                        */
DECL|macro|RXCOUNT
mdefine_line|#define RXCOUNT            4&t;/* length of RX descriptor queue     */
DECL|macro|LRXCOUNT
mdefine_line|#define LRXCOUNT           2&t;/* log2 of it                        */
DECL|macro|RAM_INITBASE
mdefine_line|#define RAM_INITBASE       0&t;/* LANCE init block                  */
DECL|macro|RAM_TXBASE
mdefine_line|#define RAM_TXBASE         24&t;/* Start of TX descriptor queue      */
DECL|macro|RAM_RXBASE
mdefine_line|#define RAM_RXBASE         &bslash;&n;(RAM_TXBASE + (TXCOUNT * 8))&t;/* Start of RX descriptor queue      */
DECL|macro|RAM_DATABASE
mdefine_line|#define RAM_DATABASE       &bslash;&n;(RAM_RXBASE + (RXCOUNT * 8))&t;/* Start of data area for frames     */
DECL|macro|RAM_BUFSIZE
mdefine_line|#define RAM_BUFSIZE        1580&t;/* max. frame size - should never be&n;&t;&t;&t;&t;   reached                           */
macro_line|#endif&t;&t;&t;&t;/* _SK_MCA_DRIVER_ */
r_extern
r_int
id|skmca_probe
c_func
(paren
r_struct
id|SKMCA_NETDEV
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* _SK_MCA_INCLUDE_ */
eof
