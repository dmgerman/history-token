multiline_comment|/*&n; * Helpfile for sonic.c&n; *&n; * (C) Waldorf Electronics, Germany&n; * Written by Andreas Busse&n; *&n; * NOTE: most of the structure definitions here are endian dependent.&n; * If you want to use this driver on big endian machines, the data&n; * and pad structure members must be exchanged. Also, the structures&n; * need to be changed accordingly to the bus size. &n; *&n; * 981229 MSch:&t;did just that for the 68k Mac port (32 bit, big endian),&n; *&t;&t;see CONFIG_MACSONIC branch below.&n; *&n; */
macro_line|#ifndef SONIC_H
DECL|macro|SONIC_H
mdefine_line|#define SONIC_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * SONIC register offsets&n; */
DECL|macro|SONIC_CMD
mdefine_line|#define SONIC_CMD              0x00
DECL|macro|SONIC_DCR
mdefine_line|#define SONIC_DCR              0x01
DECL|macro|SONIC_RCR
mdefine_line|#define SONIC_RCR              0x02
DECL|macro|SONIC_TCR
mdefine_line|#define SONIC_TCR              0x03
DECL|macro|SONIC_IMR
mdefine_line|#define SONIC_IMR              0x04
DECL|macro|SONIC_ISR
mdefine_line|#define SONIC_ISR              0x05
DECL|macro|SONIC_UTDA
mdefine_line|#define SONIC_UTDA             0x06
DECL|macro|SONIC_CTDA
mdefine_line|#define SONIC_CTDA             0x07
DECL|macro|SONIC_URDA
mdefine_line|#define SONIC_URDA             0x0d
DECL|macro|SONIC_CRDA
mdefine_line|#define SONIC_CRDA             0x0e
DECL|macro|SONIC_EOBC
mdefine_line|#define SONIC_EOBC             0x13
DECL|macro|SONIC_URRA
mdefine_line|#define SONIC_URRA             0x14
DECL|macro|SONIC_RSA
mdefine_line|#define SONIC_RSA              0x15
DECL|macro|SONIC_REA
mdefine_line|#define SONIC_REA              0x16
DECL|macro|SONIC_RRP
mdefine_line|#define SONIC_RRP              0x17
DECL|macro|SONIC_RWP
mdefine_line|#define SONIC_RWP              0x18
DECL|macro|SONIC_RSC
mdefine_line|#define SONIC_RSC              0x2b
DECL|macro|SONIC_CEP
mdefine_line|#define SONIC_CEP              0x21
DECL|macro|SONIC_CAP2
mdefine_line|#define SONIC_CAP2             0x22
DECL|macro|SONIC_CAP1
mdefine_line|#define SONIC_CAP1             0x23
DECL|macro|SONIC_CAP0
mdefine_line|#define SONIC_CAP0             0x24
DECL|macro|SONIC_CE
mdefine_line|#define SONIC_CE               0x25
DECL|macro|SONIC_CDP
mdefine_line|#define SONIC_CDP              0x26
DECL|macro|SONIC_CDC
mdefine_line|#define SONIC_CDC              0x27
DECL|macro|SONIC_WT0
mdefine_line|#define SONIC_WT0              0x29
DECL|macro|SONIC_WT1
mdefine_line|#define SONIC_WT1              0x2a
DECL|macro|SONIC_SR
mdefine_line|#define SONIC_SR               0x28
multiline_comment|/* test-only registers */
DECL|macro|SONIC_TPS
mdefine_line|#define SONIC_TPS&t;&t;0x08
DECL|macro|SONIC_TFC
mdefine_line|#define SONIC_TFC&t;&t;0x09
DECL|macro|SONIC_TSA0
mdefine_line|#define SONIC_TSA0&t;&t;0x0a
DECL|macro|SONIC_TSA1
mdefine_line|#define SONIC_TSA1&t;&t;0x0b
DECL|macro|SONIC_TFS
mdefine_line|#define SONIC_TFS&t;&t;0x0c
DECL|macro|SONIC_CRBA0
mdefine_line|#define SONIC_CRBA0&t;&t;0x0f
DECL|macro|SONIC_CRBA1
mdefine_line|#define SONIC_CRBA1&t;&t;0x10
DECL|macro|SONIC_RBWC0
mdefine_line|#define SONIC_RBWC0&t;&t;0x11
DECL|macro|SONIC_RBWC1
mdefine_line|#define SONIC_RBWC1&t;&t;0x12
DECL|macro|SONIC_TTDA
mdefine_line|#define SONIC_TTDA&t;&t;0x20
DECL|macro|SONIC_MDT
mdefine_line|#define SONIC_MDT&t;&t;0x2f
DECL|macro|SONIC_TRBA0
mdefine_line|#define SONIC_TRBA0&t;&t;0x19
DECL|macro|SONIC_TRBA1
mdefine_line|#define SONIC_TRBA1&t;&t;0x1a
DECL|macro|SONIC_TBWC0
mdefine_line|#define SONIC_TBWC0&t;&t;0x1b
DECL|macro|SONIC_TBWC1
mdefine_line|#define SONIC_TBWC1&t;&t;0x1c
DECL|macro|SONIC_LLFA
mdefine_line|#define SONIC_LLFA&t;&t;0x1f
DECL|macro|SONIC_ADDR0
mdefine_line|#define SONIC_ADDR0&t;&t;0x1d
DECL|macro|SONIC_ADDR1
mdefine_line|#define SONIC_ADDR1&t;&t;0x1e
multiline_comment|/*&n; * Error counters&n; */
DECL|macro|SONIC_CRCT
mdefine_line|#define SONIC_CRCT              0x2c
DECL|macro|SONIC_FAET
mdefine_line|#define SONIC_FAET              0x2d
DECL|macro|SONIC_MPT
mdefine_line|#define SONIC_MPT               0x2e
multiline_comment|/*&n; * SONIC command bits&n; */
DECL|macro|SONIC_CR_LCAM
mdefine_line|#define SONIC_CR_LCAM           0x0200
DECL|macro|SONIC_CR_RRRA
mdefine_line|#define SONIC_CR_RRRA           0x0100
DECL|macro|SONIC_CR_RST
mdefine_line|#define SONIC_CR_RST            0x0080
DECL|macro|SONIC_CR_ST
mdefine_line|#define SONIC_CR_ST             0x0020
DECL|macro|SONIC_CR_STP
mdefine_line|#define SONIC_CR_STP            0x0010
DECL|macro|SONIC_CR_RXEN
mdefine_line|#define SONIC_CR_RXEN           0x0008
DECL|macro|SONIC_CR_RXDIS
mdefine_line|#define SONIC_CR_RXDIS          0x0004
DECL|macro|SONIC_CR_TXP
mdefine_line|#define SONIC_CR_TXP            0x0002
DECL|macro|SONIC_CR_HTX
mdefine_line|#define SONIC_CR_HTX            0x0001
multiline_comment|/*&n; * SONIC data configuration bits&n; */
DECL|macro|SONIC_DCR_EXBUS
mdefine_line|#define SONIC_DCR_EXBUS         0x8000
DECL|macro|SONIC_DCR_LBR
mdefine_line|#define SONIC_DCR_LBR           0x2000
DECL|macro|SONIC_DCR_PO1
mdefine_line|#define SONIC_DCR_PO1           0x1000
DECL|macro|SONIC_DCR_PO0
mdefine_line|#define SONIC_DCR_PO0           0x0800
DECL|macro|SONIC_DCR_SBUS
mdefine_line|#define SONIC_DCR_SBUS          0x0400
DECL|macro|SONIC_DCR_USR1
mdefine_line|#define SONIC_DCR_USR1          0x0200
DECL|macro|SONIC_DCR_USR0
mdefine_line|#define SONIC_DCR_USR0          0x0100
DECL|macro|SONIC_DCR_WC1
mdefine_line|#define SONIC_DCR_WC1           0x0080
DECL|macro|SONIC_DCR_WC0
mdefine_line|#define SONIC_DCR_WC0           0x0040
DECL|macro|SONIC_DCR_DW
mdefine_line|#define SONIC_DCR_DW            0x0020
DECL|macro|SONIC_DCR_BMS
mdefine_line|#define SONIC_DCR_BMS           0x0010
DECL|macro|SONIC_DCR_RFT1
mdefine_line|#define SONIC_DCR_RFT1          0x0008
DECL|macro|SONIC_DCR_RFT0
mdefine_line|#define SONIC_DCR_RFT0          0x0004
DECL|macro|SONIC_DCR_TFT1
mdefine_line|#define SONIC_DCR_TFT1          0x0002
DECL|macro|SONIC_DCR_TFT0
mdefine_line|#define SONIC_DCR_TFT0          0x0001
multiline_comment|/*&n; * Constants for the SONIC receive control register.&n; */
DECL|macro|SONIC_RCR_ERR
mdefine_line|#define SONIC_RCR_ERR           0x8000
DECL|macro|SONIC_RCR_RNT
mdefine_line|#define SONIC_RCR_RNT           0x4000
DECL|macro|SONIC_RCR_BRD
mdefine_line|#define SONIC_RCR_BRD           0x2000
DECL|macro|SONIC_RCR_PRO
mdefine_line|#define SONIC_RCR_PRO           0x1000
DECL|macro|SONIC_RCR_AMC
mdefine_line|#define SONIC_RCR_AMC           0x0800
DECL|macro|SONIC_RCR_LB1
mdefine_line|#define SONIC_RCR_LB1           0x0400
DECL|macro|SONIC_RCR_LB0
mdefine_line|#define SONIC_RCR_LB0           0x0200
DECL|macro|SONIC_RCR_MC
mdefine_line|#define SONIC_RCR_MC            0x0100
DECL|macro|SONIC_RCR_BC
mdefine_line|#define SONIC_RCR_BC            0x0080
DECL|macro|SONIC_RCR_LPKT
mdefine_line|#define SONIC_RCR_LPKT          0x0040
DECL|macro|SONIC_RCR_CRS
mdefine_line|#define SONIC_RCR_CRS           0x0020
DECL|macro|SONIC_RCR_COL
mdefine_line|#define SONIC_RCR_COL           0x0010
DECL|macro|SONIC_RCR_CRCR
mdefine_line|#define SONIC_RCR_CRCR          0x0008
DECL|macro|SONIC_RCR_FAER
mdefine_line|#define SONIC_RCR_FAER          0x0004
DECL|macro|SONIC_RCR_LBK
mdefine_line|#define SONIC_RCR_LBK           0x0002
DECL|macro|SONIC_RCR_PRX
mdefine_line|#define SONIC_RCR_PRX           0x0001
DECL|macro|SONIC_RCR_LB_OFF
mdefine_line|#define SONIC_RCR_LB_OFF        0
DECL|macro|SONIC_RCR_LB_MAC
mdefine_line|#define SONIC_RCR_LB_MAC        SONIC_RCR_LB0
DECL|macro|SONIC_RCR_LB_ENDEC
mdefine_line|#define SONIC_RCR_LB_ENDEC      SONIC_RCR_LB1
DECL|macro|SONIC_RCR_LB_TRANS
mdefine_line|#define SONIC_RCR_LB_TRANS      (SONIC_RCR_LB0 | SONIC_RCR_LB1)
multiline_comment|/* default RCR setup */
DECL|macro|SONIC_RCR_DEFAULT
mdefine_line|#define SONIC_RCR_DEFAULT       (SONIC_RCR_BRD)
multiline_comment|/*&n; * SONIC Transmit Control register bits&n; */
DECL|macro|SONIC_TCR_PINTR
mdefine_line|#define SONIC_TCR_PINTR         0x8000
DECL|macro|SONIC_TCR_POWC
mdefine_line|#define SONIC_TCR_POWC          0x4000
DECL|macro|SONIC_TCR_CRCI
mdefine_line|#define SONIC_TCR_CRCI          0x2000
DECL|macro|SONIC_TCR_EXDIS
mdefine_line|#define SONIC_TCR_EXDIS         0x1000
DECL|macro|SONIC_TCR_EXD
mdefine_line|#define SONIC_TCR_EXD           0x0400
DECL|macro|SONIC_TCR_DEF
mdefine_line|#define SONIC_TCR_DEF           0x0200
DECL|macro|SONIC_TCR_NCRS
mdefine_line|#define SONIC_TCR_NCRS          0x0100
DECL|macro|SONIC_TCR_CRLS
mdefine_line|#define SONIC_TCR_CRLS          0x0080
DECL|macro|SONIC_TCR_EXC
mdefine_line|#define SONIC_TCR_EXC           0x0040
DECL|macro|SONIC_TCR_PMB
mdefine_line|#define SONIC_TCR_PMB           0x0008
DECL|macro|SONIC_TCR_FU
mdefine_line|#define SONIC_TCR_FU            0x0004
DECL|macro|SONIC_TCR_BCM
mdefine_line|#define SONIC_TCR_BCM           0x0002
DECL|macro|SONIC_TCR_PTX
mdefine_line|#define SONIC_TCR_PTX           0x0001
DECL|macro|SONIC_TCR_DEFAULT
mdefine_line|#define SONIC_TCR_DEFAULT       0x0000
multiline_comment|/* &n; * Constants for the SONIC_INTERRUPT_MASK and&n; * SONIC_INTERRUPT_STATUS registers.&n; */
DECL|macro|SONIC_INT_BR
mdefine_line|#define SONIC_INT_BR&t;&t;0x4000
DECL|macro|SONIC_INT_HBL
mdefine_line|#define SONIC_INT_HBL&t;&t;0x2000
DECL|macro|SONIC_INT_LCD
mdefine_line|#define SONIC_INT_LCD           0x1000
DECL|macro|SONIC_INT_PINT
mdefine_line|#define SONIC_INT_PINT          0x0800
DECL|macro|SONIC_INT_PKTRX
mdefine_line|#define SONIC_INT_PKTRX         0x0400
DECL|macro|SONIC_INT_TXDN
mdefine_line|#define SONIC_INT_TXDN          0x0200
DECL|macro|SONIC_INT_TXER
mdefine_line|#define SONIC_INT_TXER          0x0100
DECL|macro|SONIC_INT_TC
mdefine_line|#define SONIC_INT_TC            0x0080
DECL|macro|SONIC_INT_RDE
mdefine_line|#define SONIC_INT_RDE           0x0040
DECL|macro|SONIC_INT_RBE
mdefine_line|#define SONIC_INT_RBE           0x0020
DECL|macro|SONIC_INT_RBAE
mdefine_line|#define SONIC_INT_RBAE&t;&t;0x0010
DECL|macro|SONIC_INT_CRC
mdefine_line|#define SONIC_INT_CRC&t;&t;0x0008
DECL|macro|SONIC_INT_FAE
mdefine_line|#define SONIC_INT_FAE&t;&t;0x0004
DECL|macro|SONIC_INT_MP
mdefine_line|#define SONIC_INT_MP&t;&t;0x0002
DECL|macro|SONIC_INT_RFO
mdefine_line|#define SONIC_INT_RFO&t;&t;0x0001
multiline_comment|/*&n; * The interrupts we allow.&n; */
DECL|macro|SONIC_IMR_DEFAULT
mdefine_line|#define SONIC_IMR_DEFAULT&t;(SONIC_INT_BR | &bslash;&n;&t;&t;&t;&t;SONIC_INT_LCD | &bslash;&n;                                SONIC_INT_PINT | &bslash;&n;                                SONIC_INT_PKTRX | &bslash;&n;                                SONIC_INT_TXDN | &bslash;&n;                                SONIC_INT_TXER | &bslash;&n;                                SONIC_INT_RDE | &bslash;&n;                                SONIC_INT_RBE | &bslash;&n;                                SONIC_INT_RBAE | &bslash;&n;                                SONIC_INT_CRC | &bslash;&n;                                SONIC_INT_FAE | &bslash;&n;                                SONIC_INT_MP)
DECL|macro|SONIC_END_OF_LINKS
mdefine_line|#define&t;SONIC_END_OF_LINKS&t;0x0001
macro_line|#ifdef CONFIG_MACSONIC
multiline_comment|/* Big endian like structures on Mac&n; * (680x0)&n; */
r_typedef
r_struct
(brace
DECL|member|rx_bufadr_l
id|u32
id|rx_bufadr_l
suffix:semicolon
multiline_comment|/* receive buffer ptr */
DECL|member|rx_bufadr_h
id|u32
id|rx_bufadr_h
suffix:semicolon
DECL|member|rx_bufsize_l
id|u32
id|rx_bufsize_l
suffix:semicolon
multiline_comment|/* no. of words in the receive buffer */
DECL|member|rx_bufsize_h
id|u32
id|rx_bufsize_h
suffix:semicolon
DECL|typedef|sonic_rr_t
)brace
id|sonic_rr_t
suffix:semicolon
multiline_comment|/*&n; * Sonic receive descriptor. Receive descriptors are&n; * kept in a linked list of these structures.&n; */
r_typedef
r_struct
(brace
id|SREGS_PAD
c_func
(paren
id|pad0
)paren
suffix:semicolon
DECL|member|rx_status
id|u16
id|rx_status
suffix:semicolon
multiline_comment|/* status after reception of a packet */
id|SREGS_PAD
c_func
(paren
id|pad1
)paren
suffix:semicolon
DECL|member|rx_pktlen
id|u16
id|rx_pktlen
suffix:semicolon
multiline_comment|/* length of the packet incl. CRC */
multiline_comment|/*&n;   * Pointers to the location in the receive buffer area (RBA)&n;   * where the packet resides. A packet is always received into&n;   * a contiguous piece of memory.&n;   */
id|SREGS_PAD
c_func
(paren
id|pad2
)paren
suffix:semicolon
DECL|member|rx_pktptr_l
id|u16
id|rx_pktptr_l
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad3
)paren
suffix:semicolon
DECL|member|rx_pktptr_h
id|u16
id|rx_pktptr_h
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad4
)paren
suffix:semicolon
DECL|member|rx_seqno
id|u16
id|rx_seqno
suffix:semicolon
multiline_comment|/* sequence no. */
id|SREGS_PAD
c_func
(paren
id|pad5
)paren
suffix:semicolon
DECL|member|link
id|u16
id|link
suffix:semicolon
multiline_comment|/* link to next RDD (end if EOL bit set) */
multiline_comment|/*&n;   * Owner of this descriptor, 0= driver, 1=sonic&n;   */
id|SREGS_PAD
c_func
(paren
id|pad6
)paren
suffix:semicolon
DECL|member|in_use
id|u16
id|in_use
suffix:semicolon
DECL|member|rda_next
id|caddr_t
id|rda_next
suffix:semicolon
multiline_comment|/* pointer to next RD */
DECL|typedef|sonic_rd_t
)brace
id|sonic_rd_t
suffix:semicolon
multiline_comment|/*&n; * Describes a Transmit Descriptor&n; */
r_typedef
r_struct
(brace
id|SREGS_PAD
c_func
(paren
id|pad0
)paren
suffix:semicolon
DECL|member|tx_status
id|u16
id|tx_status
suffix:semicolon
multiline_comment|/* status after transmission of a packet */
id|SREGS_PAD
c_func
(paren
id|pad1
)paren
suffix:semicolon
DECL|member|tx_config
id|u16
id|tx_config
suffix:semicolon
multiline_comment|/* transmit configuration for this packet */
id|SREGS_PAD
c_func
(paren
id|pad2
)paren
suffix:semicolon
DECL|member|tx_pktsize
id|u16
id|tx_pktsize
suffix:semicolon
multiline_comment|/* size of the packet to be transmitted */
id|SREGS_PAD
c_func
(paren
id|pad3
)paren
suffix:semicolon
DECL|member|tx_frag_count
id|u16
id|tx_frag_count
suffix:semicolon
multiline_comment|/* no. of fragments */
id|SREGS_PAD
c_func
(paren
id|pad4
)paren
suffix:semicolon
DECL|member|tx_frag_ptr_l
id|u16
id|tx_frag_ptr_l
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad5
)paren
suffix:semicolon
DECL|member|tx_frag_ptr_h
id|u16
id|tx_frag_ptr_h
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad6
)paren
suffix:semicolon
DECL|member|tx_frag_size
id|u16
id|tx_frag_size
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad7
)paren
suffix:semicolon
DECL|member|link
id|u16
id|link
suffix:semicolon
multiline_comment|/* ptr to next descriptor */
DECL|typedef|sonic_td_t
)brace
id|sonic_td_t
suffix:semicolon
multiline_comment|/*&n; * Describes an entry in the CAM Descriptor Area.&n; */
r_typedef
r_struct
(brace
id|SREGS_PAD
c_func
(paren
id|pad0
)paren
suffix:semicolon
DECL|member|cam_entry_pointer
id|u16
id|cam_entry_pointer
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad1
)paren
suffix:semicolon
DECL|member|cam_cap0
id|u16
id|cam_cap0
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad2
)paren
suffix:semicolon
DECL|member|cam_cap1
id|u16
id|cam_cap1
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad3
)paren
suffix:semicolon
DECL|member|cam_cap2
id|u16
id|cam_cap2
suffix:semicolon
DECL|typedef|sonic_cd_t
)brace
id|sonic_cd_t
suffix:semicolon
DECL|macro|CAM_DESCRIPTORS
mdefine_line|#define CAM_DESCRIPTORS 16
r_typedef
r_struct
(brace
DECL|member|cam_desc
id|sonic_cd_t
id|cam_desc
(braket
id|CAM_DESCRIPTORS
)braket
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad
)paren
suffix:semicolon
DECL|member|cam_enable
id|u16
id|cam_enable
suffix:semicolon
DECL|typedef|sonic_cda_t
)brace
id|sonic_cda_t
suffix:semicolon
macro_line|#else /* original declarations, little endian 32 bit */
multiline_comment|/*&n; * structure definitions&n; */
r_typedef
r_struct
(brace
DECL|member|rx_bufadr_l
id|u32
id|rx_bufadr_l
suffix:semicolon
multiline_comment|/* receive buffer ptr */
DECL|member|rx_bufadr_h
id|u32
id|rx_bufadr_h
suffix:semicolon
DECL|member|rx_bufsize_l
id|u32
id|rx_bufsize_l
suffix:semicolon
multiline_comment|/* no. of words in the receive buffer */
DECL|member|rx_bufsize_h
id|u32
id|rx_bufsize_h
suffix:semicolon
DECL|typedef|sonic_rr_t
)brace
id|sonic_rr_t
suffix:semicolon
multiline_comment|/*&n; * Sonic receive descriptor. Receive descriptors are&n; * kept in a linked list of these structures.&n; */
r_typedef
r_struct
(brace
DECL|member|rx_status
id|u16
id|rx_status
suffix:semicolon
multiline_comment|/* status after reception of a packet */
id|SREGS_PAD
c_func
(paren
id|pad0
)paren
suffix:semicolon
DECL|member|rx_pktlen
id|u16
id|rx_pktlen
suffix:semicolon
multiline_comment|/* length of the packet incl. CRC */
id|SREGS_PAD
c_func
(paren
id|pad1
)paren
suffix:semicolon
multiline_comment|/*&n;   * Pointers to the location in the receive buffer area (RBA)&n;   * where the packet resides. A packet is always received into&n;   * a contiguous piece of memory.&n;   */
DECL|member|rx_pktptr_l
id|u16
id|rx_pktptr_l
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad2
)paren
suffix:semicolon
DECL|member|rx_pktptr_h
id|u16
id|rx_pktptr_h
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad3
)paren
suffix:semicolon
DECL|member|rx_seqno
id|u16
id|rx_seqno
suffix:semicolon
multiline_comment|/* sequence no. */
id|SREGS_PAD
c_func
(paren
id|pad4
)paren
suffix:semicolon
DECL|member|link
id|u16
id|link
suffix:semicolon
multiline_comment|/* link to next RDD (end if EOL bit set) */
id|SREGS_PAD
c_func
(paren
id|pad5
)paren
suffix:semicolon
multiline_comment|/*&n;   * Owner of this descriptor, 0= driver, 1=sonic&n;   */
DECL|member|in_use
id|u16
id|in_use
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad6
)paren
suffix:semicolon
DECL|member|rda_next
id|caddr_t
id|rda_next
suffix:semicolon
multiline_comment|/* pointer to next RD */
DECL|typedef|sonic_rd_t
)brace
id|sonic_rd_t
suffix:semicolon
multiline_comment|/*&n; * Describes a Transmit Descriptor&n; */
r_typedef
r_struct
(brace
DECL|member|tx_status
id|u16
id|tx_status
suffix:semicolon
multiline_comment|/* status after transmission of a packet */
id|SREGS_PAD
c_func
(paren
id|pad0
)paren
suffix:semicolon
DECL|member|tx_config
id|u16
id|tx_config
suffix:semicolon
multiline_comment|/* transmit configuration for this packet */
id|SREGS_PAD
c_func
(paren
id|pad1
)paren
suffix:semicolon
DECL|member|tx_pktsize
id|u16
id|tx_pktsize
suffix:semicolon
multiline_comment|/* size of the packet to be transmitted */
id|SREGS_PAD
c_func
(paren
id|pad2
)paren
suffix:semicolon
DECL|member|tx_frag_count
id|u16
id|tx_frag_count
suffix:semicolon
multiline_comment|/* no. of fragments */
id|SREGS_PAD
c_func
(paren
id|pad3
)paren
suffix:semicolon
DECL|member|tx_frag_ptr_l
id|u16
id|tx_frag_ptr_l
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad4
)paren
suffix:semicolon
DECL|member|tx_frag_ptr_h
id|u16
id|tx_frag_ptr_h
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad5
)paren
suffix:semicolon
DECL|member|tx_frag_size
id|u16
id|tx_frag_size
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad6
)paren
suffix:semicolon
DECL|member|link
id|u16
id|link
suffix:semicolon
multiline_comment|/* ptr to next descriptor */
id|SREGS_PAD
c_func
(paren
id|pad7
)paren
suffix:semicolon
DECL|typedef|sonic_td_t
)brace
id|sonic_td_t
suffix:semicolon
multiline_comment|/*&n; * Describes an entry in the CAM Descriptor Area.&n; */
r_typedef
r_struct
(brace
DECL|member|cam_entry_pointer
id|u16
id|cam_entry_pointer
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad0
)paren
suffix:semicolon
DECL|member|cam_cap0
id|u16
id|cam_cap0
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad1
)paren
suffix:semicolon
DECL|member|cam_cap1
id|u16
id|cam_cap1
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad2
)paren
suffix:semicolon
DECL|member|cam_cap2
id|u16
id|cam_cap2
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad3
)paren
suffix:semicolon
DECL|typedef|sonic_cd_t
)brace
id|sonic_cd_t
suffix:semicolon
DECL|macro|CAM_DESCRIPTORS
mdefine_line|#define CAM_DESCRIPTORS 16
r_typedef
r_struct
(brace
DECL|member|cam_desc
id|sonic_cd_t
id|cam_desc
(braket
id|CAM_DESCRIPTORS
)braket
suffix:semicolon
DECL|member|cam_enable
id|u16
id|cam_enable
suffix:semicolon
id|SREGS_PAD
c_func
(paren
id|pad
)paren
suffix:semicolon
DECL|typedef|sonic_cda_t
)brace
id|sonic_cda_t
suffix:semicolon
macro_line|#endif&t;/* endianness */ 
multiline_comment|/*&n; * Some tunables for the buffer areas. Power of 2 is required&n; * the current driver uses one receive buffer for each descriptor.&n; *&n; * MSch: use more buffer space for the slow m68k Macs!&n; */
macro_line|#ifdef CONFIG_MACSONIC
DECL|macro|SONIC_NUM_RRS
mdefine_line|#define SONIC_NUM_RRS    32             /* number of receive resources */
DECL|macro|SONIC_NUM_RDS
mdefine_line|#define SONIC_NUM_RDS    SONIC_NUM_RRS  /* number of receive descriptors */
DECL|macro|SONIC_NUM_TDS
mdefine_line|#define SONIC_NUM_TDS    32      /* number of transmit descriptors */
macro_line|#else
DECL|macro|SONIC_NUM_RRS
mdefine_line|#define SONIC_NUM_RRS    16             /* number of receive resources */
DECL|macro|SONIC_NUM_RDS
mdefine_line|#define SONIC_NUM_RDS    SONIC_NUM_RRS  /* number of receive descriptors */
DECL|macro|SONIC_NUM_TDS
mdefine_line|#define SONIC_NUM_TDS    16      /* number of transmit descriptors */
macro_line|#endif
DECL|macro|SONIC_RBSIZE
mdefine_line|#define SONIC_RBSIZE   1520      /* size of one resource buffer */
DECL|macro|SONIC_RDS_MASK
mdefine_line|#define SONIC_RDS_MASK   (SONIC_NUM_RDS-1)
DECL|macro|SONIC_TDS_MASK
mdefine_line|#define SONIC_TDS_MASK   (SONIC_NUM_TDS-1)
multiline_comment|/* Information that need to be kept for each board. */
DECL|struct|sonic_local
r_struct
id|sonic_local
(brace
DECL|member|cda
id|sonic_cda_t
id|cda
suffix:semicolon
multiline_comment|/* virtual CPU address of CDA */
DECL|member|tda
id|sonic_td_t
id|tda
(braket
id|SONIC_NUM_TDS
)braket
suffix:semicolon
multiline_comment|/* transmit descriptor area */
DECL|member|rra
id|sonic_rr_t
id|rra
(braket
id|SONIC_NUM_RRS
)braket
suffix:semicolon
multiline_comment|/* receive resource arrea */
DECL|member|rda
id|sonic_rd_t
id|rda
(braket
id|SONIC_NUM_RDS
)braket
suffix:semicolon
multiline_comment|/* receive descriptor area */
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
(braket
id|SONIC_NUM_TDS
)braket
suffix:semicolon
multiline_comment|/* skbuffs for packets to transmit */
DECL|member|tx_laddr
r_int
r_int
id|tx_laddr
(braket
id|SONIC_NUM_TDS
)braket
suffix:semicolon
multiline_comment|/* logical DMA address fro skbuffs */
DECL|member|rba
r_int
r_char
op_star
id|rba
suffix:semicolon
multiline_comment|/* start of receive buffer areas */
DECL|member|cda_laddr
r_int
r_int
id|cda_laddr
suffix:semicolon
multiline_comment|/* logical DMA address of CDA */
DECL|member|tda_laddr
r_int
r_int
id|tda_laddr
suffix:semicolon
multiline_comment|/* logical DMA address of TDA */
DECL|member|rra_laddr
r_int
r_int
id|rra_laddr
suffix:semicolon
multiline_comment|/* logical DMA address of RRA */
DECL|member|rda_laddr
r_int
r_int
id|rda_laddr
suffix:semicolon
multiline_comment|/* logical DMA address of RDA */
DECL|member|rba_laddr
r_int
r_int
id|rba_laddr
suffix:semicolon
multiline_comment|/* logical DMA address of RBA */
DECL|member|cur_rra
r_int
r_int
id|cur_rra
suffix:semicolon
multiline_comment|/* current indexes to resource areas */
DECL|member|cur_rx
r_int
r_int
id|cur_rx
suffix:semicolon
DECL|member|cur_tx
r_int
r_int
id|cur_tx
suffix:semicolon
DECL|member|dirty_tx
r_int
r_int
id|dirty_tx
suffix:semicolon
multiline_comment|/* last unacked transmit packet */
DECL|member|tx_full
r_char
id|tx_full
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Index to functions, as function prototypes. */
r_static
r_int
id|sonic_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|sonic_send_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|sonic_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_void
id|sonic_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|sonic_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device_stats
op_star
id|sonic_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|sonic_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|sonic_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;sonic.c:v0.92 20.9.98 tsbogend@alpha.franken.de&bslash;n&quot;
suffix:semicolon
macro_line|#endif /* SONIC_H */
eof
