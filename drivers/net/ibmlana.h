macro_line|#ifndef _IBM_LANA_INCLUDE_
DECL|macro|_IBM_LANA_INCLUDE_
mdefine_line|#define _IBM_LANA_INCLUDE_
macro_line|#ifdef _IBM_LANA_DRIVER_
multiline_comment|/* version-dependent functions/structures */
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020318
DECL|macro|IBMLANA_READB
mdefine_line|#define IBMLANA_READB(addr) isa_readb(addr)
DECL|macro|IBMLANA_TOIO
mdefine_line|#define IBMLANA_TOIO(dest, src, len) isa_memcpy_toio(dest, src, len)
DECL|macro|IBMLANA_FROMIO
mdefine_line|#define IBMLANA_FROMIO(dest, src, len) isa_memcpy_fromio(dest, src, len)
DECL|macro|IBMLANA_SETIO
mdefine_line|#define IBMLANA_SETIO(dest, val, len) isa_memset_io(dest, val, len)
DECL|macro|IBMLANA_NETDEV
mdefine_line|#define IBMLANA_NETDEV net_device
macro_line|#else
DECL|macro|IBMLANA_READB
mdefine_line|#define IBMLANA_READB(addr) readb(addr)
DECL|macro|IBMLANA_TOIO
mdefine_line|#define IBMLANA_TOIO(dest, src, len) memcpy_toio(dest, src, len)
DECL|macro|IBMLANA_FROMIO
mdefine_line|#define IBMLANA_FROMIO(dest, src, len) memcpy_fromio(dest, src, len)
DECL|macro|IBMLANA_SETIO
mdefine_line|#define IBMLANA_SETIO(dest, val, len) memset_io(dest, val, len)
DECL|macro|IBMLANA_NETDEV
mdefine_line|#define IBMLANA_NETDEV device
macro_line|#endif
multiline_comment|/* maximum packet size */
DECL|macro|PKTSIZE
mdefine_line|#define PKTSIZE 1524
multiline_comment|/* number of transmit buffers */
DECL|macro|TXBUFCNT
mdefine_line|#define TXBUFCNT 4
multiline_comment|/* Adapter ID&squot;s */
DECL|macro|IBM_LANA_ID
mdefine_line|#define IBM_LANA_ID 0xffe0
multiline_comment|/* media enumeration - defined in a way that it fits onto the LAN/A&squot;s&n;   POS registers... */
DECL|enumerator|Media_10BaseT
DECL|enumerator|Media_10Base5
r_typedef
r_enum
(brace
id|Media_10BaseT
comma
id|Media_10Base5
comma
DECL|enumerator|Media_Unknown
DECL|enumerator|Media_10Base2
DECL|enumerator|Media_Count
id|Media_Unknown
comma
id|Media_10Base2
comma
id|Media_Count
DECL|typedef|ibmlana_medium
)brace
id|ibmlana_medium
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
id|ibmlana_medium
id|medium
suffix:semicolon
multiline_comment|/* physical cannector               */
DECL|member|tdastart
DECL|member|txbufstart
id|u32
id|tdastart
comma
id|txbufstart
comma
multiline_comment|/* addresses                        */
DECL|member|rrastart
DECL|member|rxbufstart
DECL|member|rdastart
DECL|member|rxbufcnt
DECL|member|txusedcnt
id|rrastart
comma
id|rxbufstart
comma
id|rdastart
comma
id|rxbufcnt
comma
id|txusedcnt
suffix:semicolon
DECL|member|nextrxdescr
r_int
id|nextrxdescr
comma
multiline_comment|/* next rx descriptor to be used    */
DECL|member|lastrxdescr
id|lastrxdescr
comma
multiline_comment|/* last free rx descriptor          */
DECL|member|nexttxdescr
id|nexttxdescr
comma
multiline_comment|/* last tx descriptor to be used    */
DECL|member|currtxdescr
id|currtxdescr
comma
multiline_comment|/* tx descriptor currently tx&squot;ed    */
DECL|member|txused
id|txused
(braket
id|TXBUFCNT
)braket
suffix:semicolon
multiline_comment|/* busy flags                       */
DECL|typedef|ibmlana_priv
)brace
id|ibmlana_priv
suffix:semicolon
multiline_comment|/* this card uses quite a lot of I/O ports...luckily the MCA bus decodes &n;   a full 64K I/O range... */
DECL|macro|IBM_LANA_IORANGE
mdefine_line|#define IBM_LANA_IORANGE 0xa0
multiline_comment|/* Command Register: */
DECL|macro|SONIC_CMDREG
mdefine_line|#define SONIC_CMDREG     0x00
DECL|macro|CMDREG_HTX
mdefine_line|#define CMDREG_HTX       0x0001&t;/* halt transmission                */
DECL|macro|CMDREG_TXP
mdefine_line|#define CMDREG_TXP       0x0002&t;/* start transmission               */
DECL|macro|CMDREG_RXDIS
mdefine_line|#define CMDREG_RXDIS     0x0004&t;/* disable receiver                 */
DECL|macro|CMDREG_RXEN
mdefine_line|#define CMDREG_RXEN      0x0008&t;/* enable receiver                  */
DECL|macro|CMDREG_STP
mdefine_line|#define CMDREG_STP       0x0010&t;/* stop timer                       */
DECL|macro|CMDREG_ST
mdefine_line|#define CMDREG_ST        0x0020&t;/* start timer                      */
DECL|macro|CMDREG_RST
mdefine_line|#define CMDREG_RST       0x0080&t;/* software reset                   */
DECL|macro|CMDREG_RRRA
mdefine_line|#define CMDREG_RRRA      0x0100&t;/* force SONIC to read first RRA    */
DECL|macro|CMDREG_LCAM
mdefine_line|#define CMDREG_LCAM      0x0200&t;/* force SONIC to read CAM descrs   */
multiline_comment|/* Data Configuration Register */
DECL|macro|SONIC_DCREG
mdefine_line|#define SONIC_DCREG      0x02
DECL|macro|DCREG_EXBUS
mdefine_line|#define DCREG_EXBUS      0x8000&t;/* Extended Bus Mode                */
DECL|macro|DCREG_LBR
mdefine_line|#define DCREG_LBR        0x2000&t;/* Latched Bus Retry                */
DECL|macro|DCREG_PO1
mdefine_line|#define DCREG_PO1        0x1000&t;/* Programmable Outputs             */
DECL|macro|DCREG_PO0
mdefine_line|#define DCREG_PO0        0x0800
DECL|macro|DCREG_SBUS
mdefine_line|#define DCREG_SBUS       0x0400&t;/* Synchronous Bus Mode             */
DECL|macro|DCREG_USR1
mdefine_line|#define DCREG_USR1       0x0200&t;/* User Definable Pins              */
DECL|macro|DCREG_USR0
mdefine_line|#define DCREG_USR0       0x0100
DECL|macro|DCREG_WC0
mdefine_line|#define DCREG_WC0        0x0000&t;/* 0..3 Wait States                 */
DECL|macro|DCREG_WC1
mdefine_line|#define DCREG_WC1        0x0040
DECL|macro|DCREG_WC2
mdefine_line|#define DCREG_WC2        0x0080
DECL|macro|DCREG_WC3
mdefine_line|#define DCREG_WC3        0x00c0
DECL|macro|DCREG_DW16
mdefine_line|#define DCREG_DW16       0x0000&t;/* 16 bit Bus Mode                  */
DECL|macro|DCREG_DW32
mdefine_line|#define DCREG_DW32       0x0020&t;/* 32 bit Bus Mode                  */
DECL|macro|DCREG_BMS
mdefine_line|#define DCREG_BMS        0x0010&t;/* Block Mode Select                */
DECL|macro|DCREG_RFT4
mdefine_line|#define DCREG_RFT4       0x0000&t;/* 4/8/16/24 bytes RX  Threshold    */
DECL|macro|DCREG_RFT8
mdefine_line|#define DCREG_RFT8       0x0004
DECL|macro|DCREG_RFT16
mdefine_line|#define DCREG_RFT16      0x0008
DECL|macro|DCREG_RFT24
mdefine_line|#define DCREG_RFT24      0x000c
DECL|macro|DCREG_TFT8
mdefine_line|#define DCREG_TFT8       0x0000&t;/* 8/16/24/28 bytes TX Threshold    */
DECL|macro|DCREG_TFT16
mdefine_line|#define DCREG_TFT16      0x0001
DECL|macro|DCREG_TFT24
mdefine_line|#define DCREG_TFT24      0x0002
DECL|macro|DCREG_TFT28
mdefine_line|#define DCREG_TFT28      0x0003
multiline_comment|/* Receive Control Register */
DECL|macro|SONIC_RCREG
mdefine_line|#define SONIC_RCREG      0x04
DECL|macro|RCREG_ERR
mdefine_line|#define RCREG_ERR        0x8000&t;/* accept damaged and collided pkts */
DECL|macro|RCREG_RNT
mdefine_line|#define RCREG_RNT        0x4000&t;/* accept packets that are &lt; 64     */
DECL|macro|RCREG_BRD
mdefine_line|#define RCREG_BRD        0x2000&t;/* accept broadcasts                */
DECL|macro|RCREG_PRO
mdefine_line|#define RCREG_PRO        0x1000&t;/* promiscous mode                  */
DECL|macro|RCREG_AMC
mdefine_line|#define RCREG_AMC        0x0800&t;/* accept all multicasts            */
DECL|macro|RCREG_LB_NONE
mdefine_line|#define RCREG_LB_NONE    0x0000&t;/* no loopback                      */
DECL|macro|RCREG_LB_MAC
mdefine_line|#define RCREG_LB_MAC     0x0200&t;/* MAC loopback                     */
DECL|macro|RCREG_LB_ENDEC
mdefine_line|#define RCREG_LB_ENDEC   0x0400&t;/* ENDEC loopback                   */
DECL|macro|RCREG_LB_XVR
mdefine_line|#define RCREG_LB_XVR     0x0600&t;/* Transceiver loopback             */
DECL|macro|RCREG_MC
mdefine_line|#define RCREG_MC         0x0100&t;/* Multicast received               */
DECL|macro|RCREG_BC
mdefine_line|#define RCREG_BC         0x0080&t;/* Broadcast received               */
DECL|macro|RCREG_LPKT
mdefine_line|#define RCREG_LPKT       0x0040&t;/* last packet in RBA               */
DECL|macro|RCREG_CRS
mdefine_line|#define RCREG_CRS        0x0020&t;/* carrier sense present            */
DECL|macro|RCREG_COL
mdefine_line|#define RCREG_COL        0x0010&t;/* recv&squot;d packet with collision     */
DECL|macro|RCREG_CRCR
mdefine_line|#define RCREG_CRCR       0x0008&t;/* recv&squot;d packet with CRC error     */
DECL|macro|RCREG_FAER
mdefine_line|#define RCREG_FAER       0x0004&t;/* recv&squot;d packet with inv. framing  */
DECL|macro|RCREG_LBK
mdefine_line|#define RCREG_LBK        0x0002&t;/* recv&squot;d loopback packet           */
DECL|macro|RCREG_PRX
mdefine_line|#define RCREG_PRX        0x0001&t;/* recv&squot;d packet is OK              */
multiline_comment|/* Transmit Control Register */
DECL|macro|SONIC_TCREG
mdefine_line|#define SONIC_TCREG      0x06
DECL|macro|TCREG_PINT
mdefine_line|#define TCREG_PINT       0x8000&t;/* generate interrupt after TDA read */
DECL|macro|TCREG_POWC
mdefine_line|#define TCREG_POWC       0x4000&t;/* timer start out of window detect */
DECL|macro|TCREG_CRCI
mdefine_line|#define TCREG_CRCI       0x2000&t;/* inhibit CRC generation           */
DECL|macro|TCREG_EXDIS
mdefine_line|#define TCREG_EXDIS      0x1000&t;/* disable excessive deferral timer */
DECL|macro|TCREG_EXD
mdefine_line|#define TCREG_EXD        0x0400&t;/* excessive deferral occurred       */
DECL|macro|TCREG_DEF
mdefine_line|#define TCREG_DEF        0x0200&t;/* single deferral occurred          */
DECL|macro|TCREG_NCRS
mdefine_line|#define TCREG_NCRS       0x0100&t;/* no carrier detected              */
DECL|macro|TCREG_CRSL
mdefine_line|#define TCREG_CRSL       0x0080&t;/* carrier lost                     */
DECL|macro|TCREG_EXC
mdefine_line|#define TCREG_EXC        0x0040&t;/* excessive collisions occurred     */
DECL|macro|TCREG_OWC
mdefine_line|#define TCREG_OWC        0x0020&t;/* out of window collision occurred  */
DECL|macro|TCREG_PMB
mdefine_line|#define TCREG_PMB        0x0008&t;/* packet monitored bad             */
DECL|macro|TCREG_FU
mdefine_line|#define TCREG_FU         0x0004&t;/* FIFO underrun                    */
DECL|macro|TCREG_BCM
mdefine_line|#define TCREG_BCM        0x0002&t;/* byte count mismatch of fragments */
DECL|macro|TCREG_PTX
mdefine_line|#define TCREG_PTX        0x0001&t;/* packet transmitted OK            */
multiline_comment|/* Interrupt Mask Register */
DECL|macro|SONIC_IMREG
mdefine_line|#define SONIC_IMREG      0x08
DECL|macro|IMREG_BREN
mdefine_line|#define IMREG_BREN       0x4000&t;/* interrupt when bus retry occurred */
DECL|macro|IMREG_HBLEN
mdefine_line|#define IMREG_HBLEN      0x2000&t;/* interrupt when heartbeat lost    */
DECL|macro|IMREG_LCDEN
mdefine_line|#define IMREG_LCDEN      0x1000&t;/* interrupt when CAM loaded        */
DECL|macro|IMREG_PINTEN
mdefine_line|#define IMREG_PINTEN     0x0800&t;/* interrupt when PINT in TDA set   */
DECL|macro|IMREG_PRXEN
mdefine_line|#define IMREG_PRXEN      0x0400&t;/* interrupt when packet received   */
DECL|macro|IMREG_PTXEN
mdefine_line|#define IMREG_PTXEN      0x0200&t;/* interrupt when packet was sent   */
DECL|macro|IMREG_TXEREN
mdefine_line|#define IMREG_TXEREN     0x0100&t;/* interrupt when send failed       */
DECL|macro|IMREG_TCEN
mdefine_line|#define IMREG_TCEN       0x0080&t;/* interrupt when timer completed   */
DECL|macro|IMREG_RDEEN
mdefine_line|#define IMREG_RDEEN      0x0040&t;/* interrupt when RDA exhausted     */
DECL|macro|IMREG_RBEEN
mdefine_line|#define IMREG_RBEEN      0x0020&t;/* interrupt when RBA exhausted     */
DECL|macro|IMREG_RBAEEN
mdefine_line|#define IMREG_RBAEEN     0x0010&t;/* interrupt when RBA too short     */
DECL|macro|IMREG_CRCEN
mdefine_line|#define IMREG_CRCEN      0x0008&t;/* interrupt when CRC counter rolls */
DECL|macro|IMREG_FAEEN
mdefine_line|#define IMREG_FAEEN      0x0004&t;/* interrupt when FAE counter rolls */
DECL|macro|IMREG_MPEN
mdefine_line|#define IMREG_MPEN       0x0002&t;/* interrupt when MP counter rolls  */
DECL|macro|IMREG_RFOEN
mdefine_line|#define IMREG_RFOEN      0x0001&t;/* interrupt when Rx FIFO overflows */
multiline_comment|/* Interrupt Status Register */
DECL|macro|SONIC_ISREG
mdefine_line|#define SONIC_ISREG      0x0a
DECL|macro|ISREG_BR
mdefine_line|#define ISREG_BR         0x4000&t;/* bus retry occurred                */
DECL|macro|ISREG_HBL
mdefine_line|#define ISREG_HBL        0x2000&t;/* heartbeat lost                   */
DECL|macro|ISREG_LCD
mdefine_line|#define ISREG_LCD        0x1000&t;/* CAM loaded                       */
DECL|macro|ISREG_PINT
mdefine_line|#define ISREG_PINT       0x0800&t;/* PINT in TDA set                  */
DECL|macro|ISREG_PKTRX
mdefine_line|#define ISREG_PKTRX      0x0400&t;/* packet received                  */
DECL|macro|ISREG_TXDN
mdefine_line|#define ISREG_TXDN       0x0200&t;/* packet was sent                  */
DECL|macro|ISREG_TXER
mdefine_line|#define ISREG_TXER       0x0100&t;/* send failed                      */
DECL|macro|ISREG_TC
mdefine_line|#define ISREG_TC         0x0080&t;/* timer completed                  */
DECL|macro|ISREG_RDE
mdefine_line|#define ISREG_RDE        0x0040&t;/* RDA exhausted                    */
DECL|macro|ISREG_RBE
mdefine_line|#define ISREG_RBE        0x0020&t;/* RBA exhausted                    */
DECL|macro|ISREG_RBAE
mdefine_line|#define ISREG_RBAE       0x0010&t;/* RBA too short for received frame */
DECL|macro|ISREG_CRC
mdefine_line|#define ISREG_CRC        0x0008&t;/* CRC counter rolls over           */
DECL|macro|ISREG_FAE
mdefine_line|#define ISREG_FAE        0x0004&t;/* FAE counter rolls over           */
DECL|macro|ISREG_MP
mdefine_line|#define ISREG_MP         0x0002&t;/* MP counter rolls  over           */
DECL|macro|ISREG_RFO
mdefine_line|#define ISREG_RFO        0x0001&t;/* Rx FIFO overflows                */
DECL|macro|SONIC_UTDA
mdefine_line|#define SONIC_UTDA       0x0c&t;/* current transmit descr address   */
DECL|macro|SONIC_CTDA
mdefine_line|#define SONIC_CTDA       0x0e
DECL|macro|SONIC_URDA
mdefine_line|#define SONIC_URDA       0x1a&t;/* current receive descr address    */
DECL|macro|SONIC_CRDA
mdefine_line|#define SONIC_CRDA       0x1c
DECL|macro|SONIC_CRBA0
mdefine_line|#define SONIC_CRBA0      0x1e&t;/* current receive buffer address   */
DECL|macro|SONIC_CRBA1
mdefine_line|#define SONIC_CRBA1      0x20
DECL|macro|SONIC_RBWC0
mdefine_line|#define SONIC_RBWC0      0x22&t;/* word count in receive buffer     */
DECL|macro|SONIC_RBWC1
mdefine_line|#define SONIC_RBWC1      0x24
DECL|macro|SONIC_EOBC
mdefine_line|#define SONIC_EOBC       0x26&t;/* minimum space to be free in RBA  */
DECL|macro|SONIC_URRA
mdefine_line|#define SONIC_URRA       0x28&t;/* upper address of CDA &amp; Recv Area */
DECL|macro|SONIC_RSA
mdefine_line|#define SONIC_RSA        0x2a&t;/* start of receive resource area   */
DECL|macro|SONIC_REA
mdefine_line|#define SONIC_REA        0x2c&t;/* end of receive resource area     */
DECL|macro|SONIC_RRP
mdefine_line|#define SONIC_RRP        0x2e&t;/* resource read pointer            */
DECL|macro|SONIC_RWP
mdefine_line|#define SONIC_RWP        0x30&t;/* resource write pointer           */
DECL|macro|SONIC_CAMEPTR
mdefine_line|#define SONIC_CAMEPTR    0x42&t;/* CAM entry pointer                */
DECL|macro|SONIC_CAMADDR2
mdefine_line|#define SONIC_CAMADDR2   0x44&t;/* CAM address ports                */
DECL|macro|SONIC_CAMADDR1
mdefine_line|#define SONIC_CAMADDR1   0x46
DECL|macro|SONIC_CAMADDR0
mdefine_line|#define SONIC_CAMADDR0   0x48
DECL|macro|SONIC_CAMPTR
mdefine_line|#define SONIC_CAMPTR     0x4c&t;/* lower address of CDA             */
DECL|macro|SONIC_CAMCNT
mdefine_line|#define SONIC_CAMCNT     0x4e&t;/* # of CAM descriptors to load     */
multiline_comment|/* Data Configuration Register 2    */
DECL|macro|SONIC_DCREG2
mdefine_line|#define SONIC_DCREG2     0x7e
DECL|macro|DCREG2_EXPO3
mdefine_line|#define DCREG2_EXPO3     0x8000&t;/* extended programmable outputs    */
DECL|macro|DCREG2_EXPO2
mdefine_line|#define DCREG2_EXPO2     0x4000
DECL|macro|DCREG2_EXPO1
mdefine_line|#define DCREG2_EXPO1     0x2000
DECL|macro|DCREG2_EXPO0
mdefine_line|#define DCREG2_EXPO0     0x1000
DECL|macro|DCREG2_HD
mdefine_line|#define DCREG2_HD        0x0800&t;/* heartbeat disable                */
DECL|macro|DCREG2_JD
mdefine_line|#define DCREG2_JD        0x0200&t;/* jabber timer disable             */
DECL|macro|DCREG2_AUTO
mdefine_line|#define DCREG2_AUTO      0x0100&t;/* enable AUI/TP auto selection     */
DECL|macro|DCREG2_XWRAP
mdefine_line|#define DCREG2_XWRAP     0x0040&t;/* TP transceiver loopback          */
DECL|macro|DCREG2_PH
mdefine_line|#define DCREG2_PH        0x0010&t;/* HOLD request timing              */
DECL|macro|DCREG2_PCM
mdefine_line|#define DCREG2_PCM       0x0004&t;/* packet compress when matched     */
DECL|macro|DCREG2_PCNM
mdefine_line|#define DCREG2_PCNM      0x0002&t;/* packet compress when not matched */
DECL|macro|DCREG2_RJCM
mdefine_line|#define DCREG2_RJCM      0x0001&t;/* inverse packet match via CAM     */
multiline_comment|/* Board Control Register: Enable RAM, Interrupts... */
DECL|macro|BCMREG
mdefine_line|#define BCMREG           0x80
DECL|macro|BCMREG_RAMEN
mdefine_line|#define BCMREG_RAMEN     0x80&t;/* switch over to RAM               */
DECL|macro|BCMREG_IPEND
mdefine_line|#define BCMREG_IPEND     0x40&t;/* interrupt pending ?              */
DECL|macro|BCMREG_RESET
mdefine_line|#define BCMREG_RESET     0x08&t;/* reset board                      */
DECL|macro|BCMREG_16BIT
mdefine_line|#define BCMREG_16BIT     0x04&t;/* adapter in 16-bit slot           */
DECL|macro|BCMREG_RAMWIN
mdefine_line|#define BCMREG_RAMWIN    0x02&t;/* enable RAM window                */
DECL|macro|BCMREG_IEN
mdefine_line|#define BCMREG_IEN       0x01&t;/* interrupt enable                 */
multiline_comment|/* MAC Address PROM */
DECL|macro|MACADDRPROM
mdefine_line|#define MACADDRPROM      0x92
multiline_comment|/* structure of a CAM entry */
r_typedef
r_struct
(brace
DECL|member|index
id|u32
id|index
suffix:semicolon
multiline_comment|/* pointer into CAM area            */
DECL|member|addr0
id|u32
id|addr0
suffix:semicolon
multiline_comment|/* address part (bits 0..15 used)   */
DECL|member|addr1
id|u32
id|addr1
suffix:semicolon
DECL|member|addr2
id|u32
id|addr2
suffix:semicolon
DECL|typedef|camentry_t
)brace
id|camentry_t
suffix:semicolon
multiline_comment|/* structure of a receive resource */
r_typedef
r_struct
(brace
DECL|member|startlo
id|u32
id|startlo
suffix:semicolon
multiline_comment|/* start address (bits 0..15 used)  */
DECL|member|starthi
id|u32
id|starthi
suffix:semicolon
DECL|member|cntlo
id|u32
id|cntlo
suffix:semicolon
multiline_comment|/* size in 16-bit quantities        */
DECL|member|cnthi
id|u32
id|cnthi
suffix:semicolon
DECL|typedef|rra_t
)brace
id|rra_t
suffix:semicolon
multiline_comment|/* structure of a receive descriptor */
r_typedef
r_struct
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
multiline_comment|/* packet status                    */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* length in bytes                  */
DECL|member|startlo
id|u32
id|startlo
suffix:semicolon
multiline_comment|/* start address                    */
DECL|member|starthi
id|u32
id|starthi
suffix:semicolon
DECL|member|seqno
id|u32
id|seqno
suffix:semicolon
multiline_comment|/* frame sequence                   */
DECL|member|link
id|u32
id|link
suffix:semicolon
multiline_comment|/* pointer to next descriptor       */
multiline_comment|/* bit 0 = EOL                      */
DECL|member|inuse
id|u32
id|inuse
suffix:semicolon
multiline_comment|/* !=0 --&gt; free for SONIC to write  */
DECL|typedef|rda_t
)brace
id|rda_t
suffix:semicolon
multiline_comment|/* structure of a transmit descriptor */
r_typedef
r_struct
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
multiline_comment|/* transmit status                  */
DECL|member|config
id|u32
id|config
suffix:semicolon
multiline_comment|/* value for TCR                    */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* total length                     */
DECL|member|fragcount
id|u32
id|fragcount
suffix:semicolon
multiline_comment|/* number of fragments              */
DECL|member|startlo
id|u32
id|startlo
suffix:semicolon
multiline_comment|/* start address of fragment        */
DECL|member|starthi
id|u32
id|starthi
suffix:semicolon
DECL|member|fraglength
id|u32
id|fraglength
suffix:semicolon
multiline_comment|/* length of this fragment          */
multiline_comment|/* more address/length triplets may */
multiline_comment|/* follow here                      */
DECL|member|link
id|u32
id|link
suffix:semicolon
multiline_comment|/* pointer to next descriptor       */
multiline_comment|/* bit 0 = EOL                      */
DECL|typedef|tda_t
)brace
id|tda_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _IBM_LANA_DRIVER_ */
r_extern
r_int
id|ibmlana_probe
c_func
(paren
r_struct
id|IBMLANA_NETDEV
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* _IBM_LANA_INCLUDE_ */
eof
