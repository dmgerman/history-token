macro_line|#ifndef _NET_H_SYMBA
DECL|macro|_NET_H_SYMBA
mdefine_line|#define _NET_H_SYMBA
multiline_comment|/* transmit status bit definitions */
DECL|macro|TX_STATUS_TXOK
mdefine_line|#define TX_STATUS_TXOK         (1&lt;&lt;13)     /* success */
DECL|macro|TX_STATUS_TDLC
mdefine_line|#define TX_STATUS_TDLC         (1&lt;&lt;12)     /* dropped for late colls */
DECL|macro|TX_STATUS_TCXSDFR
mdefine_line|#define TX_STATUS_TCXSDFR      (1&lt;&lt;11)     /* excessive deferral */
DECL|macro|TX_STATUS_TDEC
mdefine_line|#define TX_STATUS_TDEC         (1&lt;&lt;10)     /* excessive collisions */
DECL|macro|TX_STATUS_TAUR
mdefine_line|#define TX_STATUS_TAUR         (1&lt;&lt;9)      /* abort on underrun/&quot;jumbo&quot; */
DECL|macro|TX_STATUS_PDFRD
mdefine_line|#define TX_STATUS_PDFRD        (1&lt;&lt;8)      /* packet deferred */
DECL|macro|TX_STATUS_BCAST
mdefine_line|#define TX_STATUS_BCAST        (1&lt;&lt;7)      /* broadcast ok */
DECL|macro|TX_STATUS_MCAST
mdefine_line|#define TX_STATUS_MCAST        (1&lt;&lt;6)      /* multicast ok */
DECL|macro|TX_STATUS_CRCERR
mdefine_line|#define TX_STATUS_CRCERR       (1&lt;&lt;5)      /* CRC error */
DECL|macro|TX_STATUS_LC
mdefine_line|#define TX_STATUS_LC           (1&lt;&lt;4)      /* late collision */
DECL|macro|TX_STATUS_CCNT_MASK
mdefine_line|#define TX_STATUS_CCNT_MASK    0xf         /* collision count */
DECL|macro|T_TXOK
mdefine_line|#define T_TXOK      (1&lt;&lt;13)
DECL|macro|T_TDLC
mdefine_line|#define T_TDLC      (1&lt;&lt;12)
DECL|macro|T_TCXSDFR
mdefine_line|#define T_TCXSDFR   (1&lt;&lt;11)
DECL|macro|T_TDEC
mdefine_line|#define T_TDEC      (1&lt;&lt;10)
DECL|macro|T_TAUR
mdefine_line|#define T_TAUR      (1&lt;&lt;9)
DECL|macro|T_PDFRD
mdefine_line|#define T_PDFRD     (1&lt;&lt;8)
DECL|macro|T_BCAST
mdefine_line|#define T_BCAST     (1&lt;&lt;7)
DECL|macro|T_MCAST
mdefine_line|#define T_MCAST     (1&lt;&lt;6)
DECL|macro|T_LC
mdefine_line|#define T_LC        (1&lt;&lt;4)
DECL|macro|T_CCNT_MASK
mdefine_line|#define T_CCNT_MASK 0xf
multiline_comment|/* receive status bit definitions */
DECL|macro|RX_STATUS_RXOVRN
mdefine_line|#define RX_STATUS_RXOVRN       (1&lt;&lt;23)     /* overrun */
DECL|macro|RX_STATUS_CEPS
mdefine_line|#define RX_STATUS_CEPS         (1&lt;&lt;22)     /* carrier event already seen */
DECL|macro|RX_STATUS_RXOK
mdefine_line|#define RX_STATUS_RXOK         (1&lt;&lt;21)     /* success */
DECL|macro|RX_STATUS_BCAST
mdefine_line|#define RX_STATUS_BCAST        (1&lt;&lt;20)     /* broadcast ok */
DECL|macro|RX_STATUS_MCAST
mdefine_line|#define RX_STATUS_MCAST        (1&lt;&lt;19)     /* multicast ok */
DECL|macro|RX_STATUS_CRCERR
mdefine_line|#define RX_STATUS_CRCERR       (1&lt;&lt;18)     /* CRC error */
DECL|macro|RX_STATUS_DR
mdefine_line|#define RX_STATUS_DR           (1&lt;&lt;17)     /* dribble nibble */
DECL|macro|RX_STATUS_RCV
mdefine_line|#define RX_STATUS_RCV          (1&lt;&lt;16)     /* rx code violation */
DECL|macro|RX_STATUS_PTL
mdefine_line|#define RX_STATUS_PTL          (1&lt;&lt;15)     /* pkt &gt; 1518 bytes */
DECL|macro|RX_STATUS_PTS
mdefine_line|#define RX_STATUS_PTS          (1&lt;&lt;14)     /* pkt &lt; 64 bytes */
DECL|macro|RX_STATUS_LEN_MASK
mdefine_line|#define RX_STATUS_LEN_MASK     0x1fff      /* length mask */
DECL|macro|EEPROM_LENGTH
mdefine_line|#define EEPROM_LENGTH          100
multiline_comment|/*  Serial EEPROM interface  */
DECL|macro|EE_STATUS
mdefine_line|#define EE_STATUS              0xf0
DECL|macro|EE_CONTROL
mdefine_line|#define EE_CONTROL             0xf1
DECL|macro|EE_WORD_ADDR
mdefine_line|#define EE_WORD_ADDR           0xf2
DECL|macro|EE_READ_DATA
mdefine_line|#define EE_READ_DATA           0xf3
DECL|macro|EE_WRITE_DATA
mdefine_line|#define EE_WRITE_DATA          0xf4
DECL|macro|EE_FEATURE_ENB
mdefine_line|#define EE_FEATURE_ENB         0xf5
multiline_comment|/*  Use on EE_STATUS  */
DECL|macro|EE_SEB
mdefine_line|#define EE_SEB                 (1&lt;&lt;8)
DECL|macro|EE_SEE
mdefine_line|#define EE_SEE                     1
multiline_comment|/*  Serial EEPROM commands */
DECL|macro|EE_CONTROL_SEQ_READB
mdefine_line|#define EE_CONTROL_SEQ_READB   (1&lt;&lt;4)
DECL|macro|EE_CONTROL_RND_WRITEB
mdefine_line|#define EE_CONTROL_RND_WRITEB  (1&lt;&lt;5)
DECL|macro|EE_CONTROL_RND_READB
mdefine_line|#define EE_CONTROL_RND_READB   ((1&lt;&lt;4)|(1&lt;&lt;5))
multiline_comment|/*  Enable writing to serial EEPROM */
DECL|macro|EE_WRITE_ENB
mdefine_line|#define EE_WRITE_ENB                1
multiline_comment|/*  The 885 configuration register */
DECL|macro|MAC_CONFIG
mdefine_line|#define MAC_CONFIG             0xa0
DECL|macro|MAC_CONFIG_SRST
mdefine_line|#define  MAC_CONFIG_SRST       1&lt;&lt;15
DECL|macro|MAC_CONFIG_ITXA
mdefine_line|#define  MAC_CONFIG_ITXA       1&lt;&lt;13
DECL|macro|MAC_CONFIG_RXEN
mdefine_line|#define  MAC_CONFIG_RXEN       1&lt;&lt;12
DECL|macro|MAC_CONFIG_INTLB
mdefine_line|#define  MAC_CONFIG_INTLB      1&lt;&lt;10
DECL|macro|MAC_CONFIG_MODE_MASK
mdefine_line|#define  MAC_CONFIG_MODE_MASK  (1&lt;&lt;8|1&lt;&lt;9)
DECL|macro|MAC_CONFIG_MODE_TP
mdefine_line|#define  MAC_CONFIG_MODE_TP    1&lt;&lt;8
DECL|macro|MAC_CONFIG_HUGEN
mdefine_line|#define  MAC_CONFIG_HUGEN      1&lt;&lt;5
DECL|macro|MAC_CONFIG_RETRYL
mdefine_line|#define  MAC_CONFIG_RETRYL     1&lt;&lt;4
DECL|macro|MAC_CONFIG_CRCEN
mdefine_line|#define  MAC_CONFIG_CRCEN      1&lt;&lt;3
DECL|macro|MAC_CONFIG_PADEN
mdefine_line|#define  MAC_CONFIG_PADEN      1&lt;&lt;2
DECL|macro|MAC_CONFIG_FULLD
mdefine_line|#define  MAC_CONFIG_FULLD      1&lt;&lt;1
DECL|macro|MAC_CONFIG_NOCFR
mdefine_line|#define  MAC_CONFIG_NOCFR      1&lt;&lt;0
DECL|macro|TX_WAIT_SELECT
mdefine_line|#define TX_WAIT_SELECT         0x18
DECL|macro|RX_CHANNEL_CONTROL
mdefine_line|#define RX_CHANNEL_CONTROL     0x40
multiline_comment|/* Tx channel status */
DECL|macro|TX_DBDMA_REG
mdefine_line|#define TX_DBDMA_REG           0x00
DECL|macro|TX_CHANNEL_CONTROL
mdefine_line|#define TX_CHANNEL_CONTROL     0x00
DECL|macro|TX_CHANNEL_STATUS
mdefine_line|#define TX_CHANNEL_STATUS      0x04
DECL|macro|TX_STATUS_RUN
mdefine_line|#define  TX_STATUS_RUN         1&lt;&lt;15
DECL|macro|TX_STATUS_PAUSE
mdefine_line|#define  TX_STATUS_PAUSE       1&lt;&lt;14
DECL|macro|TX_STATUS_WAKE
mdefine_line|#define  TX_STATUS_WAKE        1&lt;&lt;12
DECL|macro|TX_STATUS_DEAD
mdefine_line|#define  TX_STATUS_DEAD        1&lt;&lt;11
DECL|macro|TX_STATUS_ACTIVE
mdefine_line|#define  TX_STATUS_ACTIVE      1&lt;&lt;10
DECL|macro|TX_STATUS_BT
mdefine_line|#define  TX_STATUS_BT          1&lt;&lt;8
DECL|macro|TX_STATUS_TXABORT
mdefine_line|#define  TX_STATUS_TXABORT     1&lt;&lt;7
DECL|macro|TX_STATUS_TXSR
mdefine_line|#define  TX_STATUS_TXSR        1&lt;&lt;6
DECL|macro|TX_CHANNEL_RUN
mdefine_line|#define  TX_CHANNEL_RUN        TX_STATUS_RUN
DECL|macro|TX_CHANNEL_PAUSE
mdefine_line|#define  TX_CHANNEL_PAUSE      TX_STATUS_PAUSE
DECL|macro|TX_CHANNEL_WAKE
mdefine_line|#define  TX_CHANNEL_WAKE       TX_STATUS_WAKE
DECL|macro|TX_CHANNEL_DEAD
mdefine_line|#define  TX_CHANNEL_DEAD       TX_STATUS_DEAD
DECL|macro|TX_CHANNEL_ACTIVE
mdefine_line|#define  TX_CHANNEL_ACTIVE     TX_STATUS_ACTIVE
DECL|macro|TX_CHANNEL_BT
mdefine_line|#define  TX_CHANNEL_BT         TX_STATUS_BT
DECL|macro|TX_CHANNEL_TXABORT
mdefine_line|#define  TX_CHANNEL_TXABORT    TX_STATUS_TXABORT
DECL|macro|TX_CHANNEL_TXSR
mdefine_line|#define  TX_CHANNEL_TXSR       TX_STATUS_TXSR
DECL|macro|TX_DBDMA_ENABLE
mdefine_line|#define  TX_DBDMA_ENABLE       (TX_CHANNEL_WAKE | TX_CHANNEL_PAUSE | &bslash;&n;                                TX_CHANNEL_RUN )
multiline_comment|/* Transmit command ptr lo register */
DECL|macro|TX_CMD_PTR_LO
mdefine_line|#define TX_CMD_PTR_LO          0x0c
multiline_comment|/* Transmit interrupt select register */
DECL|macro|TX_INT_SELECT
mdefine_line|#define TX_INT_SELECT          0x10
multiline_comment|/* Transmit branch select register */
DECL|macro|TX_BRANCH_SELECT
mdefine_line|#define TX_BRANCH_SELECT       0x14
multiline_comment|/* Transmit wait select register */
DECL|macro|TX_WAIT_SELECT
mdefine_line|#define TX_WAIT_SELECT         0x18
DECL|macro|TX_WAIT_STAT_RECV
mdefine_line|#define  TX_WAIT_STAT_RECV     0x40
multiline_comment|/* Rx channel status */
DECL|macro|RX_DBDMA_REG
mdefine_line|#define RX_DBDMA_REG           0x40
DECL|macro|RX_CHANNEL_CONTROL
mdefine_line|#define RX_CHANNEL_CONTROL     0x40
DECL|macro|RX_CHANNEL_STATUS
mdefine_line|#define RX_CHANNEL_STATUS      0x44
DECL|macro|RX_STATUS_RUN
mdefine_line|#define  RX_STATUS_RUN         1&lt;&lt;15
DECL|macro|RX_STATUS_PAUSE
mdefine_line|#define  RX_STATUS_PAUSE       1&lt;&lt;14
DECL|macro|RX_STATUS_WAKE
mdefine_line|#define  RX_STATUS_WAKE        1&lt;&lt;12
DECL|macro|RX_STATUS_DEAD
mdefine_line|#define  RX_STATUS_DEAD        1&lt;&lt;11
DECL|macro|RX_STATUS_ACTIVE
mdefine_line|#define  RX_STATUS_ACTIVE      1&lt;&lt;10
DECL|macro|RX_STATUS_BT
mdefine_line|#define  RX_STATUS_BT          1&lt;&lt;8
DECL|macro|RX_STATUS_EOP
mdefine_line|#define  RX_STATUS_EOP         1&lt;&lt;6
DECL|macro|RX_CHANNEL_RUN
mdefine_line|#define  RX_CHANNEL_RUN        RX_STATUS_RUN
DECL|macro|RX_CHANNEL_PAUSE
mdefine_line|#define  RX_CHANNEL_PAUSE      RX_STATUS_PAUSE
DECL|macro|RX_CHANNEL_WAKE
mdefine_line|#define  RX_CHANNEL_WAKE       RX_STATUS_WAKE
DECL|macro|RX_CHANNEL_DEAD
mdefine_line|#define  RX_CHANNEL_DEAD       RX_STATUS_DEAD
DECL|macro|RX_CHANNEL_ACTIVE
mdefine_line|#define  RX_CHANNEL_ACTIVE     RX_STATUS_ACTIVE
DECL|macro|RX_CHANNEL_BT
mdefine_line|#define  RX_CHANNEL_BT         RX_STATUS_BT
DECL|macro|RX_CHANNEL_EOP
mdefine_line|#define  RX_CHANNEL_EOP        RX_STATUS_EOP
DECL|macro|RX_DBDMA_ENABLE
mdefine_line|#define  RX_DBDMA_ENABLE       (RX_CHANNEL_WAKE | RX_CHANNEL_PAUSE | &bslash;&n;                                RX_CHANNEL_RUN)
multiline_comment|/*  Receive command ptr lo  */
DECL|macro|RX_CMD_PTR_LO
mdefine_line|#define RX_CMD_PTR_LO          0x4c
multiline_comment|/*  Receive interrupt select register */
DECL|macro|RX_INT_SELECT
mdefine_line|#define RX_INT_SELECT          0x50
DECL|macro|RX_INT_SELECT_EOP
mdefine_line|#define  RX_INT_SELECT_EOP     0x40
multiline_comment|/*  Receive branch select  */
DECL|macro|RX_BRANCH_SELECT
mdefine_line|#define RX_BRANCH_SELECT       0x54
DECL|macro|RX_BRANCH_SELECT_EOP
mdefine_line|#define  RX_BRANCH_SELECT_EOP  0x40
multiline_comment|/*  Receive wait select  */
DECL|macro|RX_WAIT_SELECT
mdefine_line|#define RX_WAIT_SELECT         0x58
DECL|macro|RX_WAIT_SELECT_EOP
mdefine_line|#define  RX_WAIT_SELECT_EOP    0x40
multiline_comment|/*  Event status register  */
DECL|macro|EVENT_STATUS
mdefine_line|#define EVENT_STATUS           0x80
DECL|macro|EVENT_TXSR
mdefine_line|#define  EVENT_TXSR            1&lt;&lt;2
DECL|macro|EVENT_EOP
mdefine_line|#define  EVENT_EOP             1&lt;&lt;1
DECL|macro|EVENT_TXABORT
mdefine_line|#define  EVENT_TXABORT         1&lt;&lt;0
multiline_comment|/*  Interrupt enable register  */
DECL|macro|INTERRUPT_ENABLE
mdefine_line|#define INTERRUPT_ENABLE       0x82
multiline_comment|/*  Interrupt clear register  */
DECL|macro|INTERRUPT_CLEAR
mdefine_line|#define INTERRUPT_CLEAR        0x84
multiline_comment|/*  Interrupt status register  */
DECL|macro|INTERRUPT_STATUS_REG
mdefine_line|#define INTERRUPT_STATUS_REG   0x86
multiline_comment|/*  bits for the above three interrupt registers */
DECL|macro|INTERRUPT_INTE
mdefine_line|#define  INTERRUPT_INTE        1&lt;&lt;15   /* interrupt enable */
DECL|macro|INTERRUPT_WI
mdefine_line|#define  INTERRUPT_WI          1&lt;&lt;9    /* wakeup interrupt */
DECL|macro|INTERRUPT_ERI
mdefine_line|#define  INTERRUPT_ERI         1&lt;&lt;8    /* early receive interrupt */
DECL|macro|INTERRUPT_PPET
mdefine_line|#define  INTERRUPT_PPET        1&lt;&lt;7    /* PCI Tx parity error */
DECL|macro|INTERRUPT_PBFT
mdefine_line|#define  INTERRUPT_PBFT        1&lt;&lt;6    /* PCI Tx bus fault */
DECL|macro|INTERRUPT_IIDT
mdefine_line|#define  INTERRUPT_IIDT        1&lt;&lt;5    /* illegal instruction Tx */
DECL|macro|INTERRUPT_DIT
mdefine_line|#define  INTERRUPT_DIT         1&lt;&lt;4    /* DBDMA Tx interrupt */
DECL|macro|INTERRUPT_PPER
mdefine_line|#define  INTERRUPT_PPER        1&lt;&lt;3    /* PCI Rx parity error */
DECL|macro|INTERRUPT_PBFR
mdefine_line|#define  INTERRUPT_PBFR        1&lt;&lt;2    /* PCI Rx bus fault */
DECL|macro|INTERRUPT_IIDR
mdefine_line|#define  INTERRUPT_IIDR        1&lt;&lt;1    /* illegal instruction Rx */
DECL|macro|INTERRUPT_DIR
mdefine_line|#define  INTERRUPT_DIR         1&lt;&lt;0    /* DBDMA Rx interrupt */
DECL|macro|INTERRUPT_TX_MASK
mdefine_line|#define  INTERRUPT_TX_MASK     (INTERRUPT_PBFT|INTERRUPT_IIDT| &bslash;&n;                                INTERRUPT_PPET|INTERRUPT_DIT)
DECL|macro|INTERRUPT_RX_MASK
mdefine_line|#define  INTERRUPT_RX_MASK     (INTERRUPT_PBFR|INTERRUPT_IIDR| &bslash;&n;                                INTERRUPT_PPER|INTERRUPT_DIR)
multiline_comment|/*  chip revision register */
DECL|macro|CHIP_REVISION_REG
mdefine_line|#define CHIP_REVISION_REG      0x8c
DECL|macro|CHIP_PCIREV_MASK
mdefine_line|#define  CHIP_PCIREV_MASK      (0xf&lt;&lt;16)
DECL|macro|CHIP_PCIDEV_MASK
mdefine_line|#define  CHIP_PCIDEV_MASK      0xff
multiline_comment|/*  Tx threshold register */
DECL|macro|TX_THRESHOLD
mdefine_line|#define TX_THRESHOLD           0x94
multiline_comment|/*  General purpose register */
DECL|macro|GEN_PURPOSE_REG
mdefine_line|#define GEN_PURPOSE_REG        0x9e
multiline_comment|/*  General purpose pin control reg */
DECL|macro|GEN_PIN_CONTROL_REG
mdefine_line|#define GEN_PIN_CONTROL_REG    0x9f
multiline_comment|/*  DBDMA control register  */
DECL|macro|DBDMA_CONTROL
mdefine_line|#define DBDMA_CONTROL          0x90
DECL|macro|DBDMA_SRST
mdefine_line|#define  DBDMA_SRST            1&lt;&lt;31
DECL|macro|DBDMA_TDPCE
mdefine_line|#define  DBDMA_TDPCE           1&lt;&lt;23
DECL|macro|DBDMA_BE
mdefine_line|#define  DBDMA_BE              1&lt;&lt;22
DECL|macro|DBDMA_TAP_MASK
mdefine_line|#define  DBDMA_TAP_MASK        (1&lt;&lt;19|1&lt;&lt;20|1&lt;&lt;21)
DECL|macro|DBDMA_RAP_MASK
mdefine_line|#define  DBDMA_RAP_MASK        (1&lt;&lt;16|1&lt;&lt;17|1&lt;&lt;18)
DECL|macro|DBDMA_DPMRLE
mdefine_line|#define  DBDMA_DPMRLE          1&lt;&lt;15
DECL|macro|DBDMA_WIE
mdefine_line|#define  DBDMA_WIE             1&lt;&lt;14
DECL|macro|DBDMA_MP
mdefine_line|#define  DBDMA_MP              1&lt;&lt;13
DECL|macro|DBDMA_SME
mdefine_line|#define  DBDMA_SME             1&lt;&lt;12
DECL|macro|DBDMA_CME
mdefine_line|#define  DBDMA_CME             1&lt;&lt;11
DECL|macro|DBDMA_DDPE
mdefine_line|#define  DBDMA_DDPE            1&lt;&lt;10
DECL|macro|DBDMA_TDPE
mdefine_line|#define  DBDMA_TDPE            1&lt;&lt;9
DECL|macro|DBDMA_EXTE
mdefine_line|#define  DBDMA_EXTE            1&lt;&lt;8
DECL|macro|DBDMA_BST_MASK
mdefine_line|#define  DBDMA_BST_MASK        (1&lt;&lt;4|1&lt;&lt;5|1&lt;&lt;6)
DECL|macro|DBDMA_BSR_MASK
mdefine_line|#define  DBDMA_BSR_MASK        (1&lt;&lt;0|1&lt;&lt;1|1&lt;&lt;2)
DECL|macro|DBDMA_BURST_1
mdefine_line|#define  DBDMA_BURST_1         (0x00)
DECL|macro|DBDMA_BURST_2
mdefine_line|#define  DBDMA_BURST_2         (0x01)
DECL|macro|DBDMA_BURST_4
mdefine_line|#define  DBDMA_BURST_4         (0x02)
DECL|macro|DBDMA_BURST_8
mdefine_line|#define  DBDMA_BURST_8         (0x03)
DECL|macro|DBDMA_BURST_16
mdefine_line|#define  DBDMA_BURST_16        (0x04)
DECL|macro|DBDMA_BURST_32
mdefine_line|#define  DBDMA_BURST_32        (0x05)
DECL|macro|DBDMA_BURST_64
mdefine_line|#define  DBDMA_BURST_64        (0x06)
DECL|macro|DBDMA_BURST_128
mdefine_line|#define  DBDMA_BURST_128       (0x07)
DECL|macro|DBDMA_TX_BST_SHIFT
mdefine_line|#define  DBDMA_TX_BST_SHIFT    (4)
DECL|macro|DBDMA_RX_BST_SHIFT
mdefine_line|#define  DBDMA_RX_BST_SHIFT    (0)
DECL|macro|DBDMA_TX_ARBITRATION_DEFAULT
mdefine_line|#define  DBDMA_TX_ARBITRATION_DEFAULT ( 1 &lt;&lt; 19 )
DECL|macro|DBDMA_RX_ARBITRATION_DEFAULT
mdefine_line|#define  DBDMA_RX_ARBITRATION_DEFAULT ( 2 &lt;&lt; 16 )
multiline_comment|/*  Back-to-back interpacket gap register */
DECL|macro|BTOB_INTP_GAP
mdefine_line|#define BTOB_INTP_GAP          0xa2
DECL|macro|BTOB_INTP_DEFAULT
mdefine_line|#define  BTOB_INTP_DEFAULT     0x18
multiline_comment|/*  Non-back-to-back interpacket gap register */
DECL|macro|NBTOB_INTP_GAP
mdefine_line|#define NBTOB_INTP_GAP         0xa4
multiline_comment|/*  MIIM command register */
DECL|macro|MIIM_COMMAND
mdefine_line|#define MIIM_COMMAND           0xa6
DECL|macro|MIIM_SCAN
mdefine_line|#define  MIIM_SCAN             1&lt;&lt;1
DECL|macro|MIIM_RSTAT
mdefine_line|#define  MIIM_RSTAT            1&lt;&lt;0
multiline_comment|/*  MII address register */
DECL|macro|MII_ADDRESS
mdefine_line|#define MII_ADDRESS            0xa8
DECL|macro|MII_FIAD_MASK
mdefine_line|#define  MII_FIAD_MASK         (1&lt;&lt;8|1&lt;&lt;9|1&lt;&lt;10|1&lt;&lt;11|1&lt;&lt;12)
DECL|macro|MII_RGAD_MASK
mdefine_line|#define  MII_RGAD_MASK         (1&lt;&lt;0|1&lt;&lt;1|1&lt;&lt;2|1&lt;&lt;3|1&lt;&lt;4)
DECL|macro|TPPMD_CONTROL_REG
mdefine_line|#define TPPMD_CONTROL_REG      0xa8
DECL|macro|TPPMD_FO
mdefine_line|#define  TPPMD_FO              1&lt;&lt;1
DECL|macro|TPPMD_LB
mdefine_line|#define  TPPMD_LB              1&lt;&lt;0
multiline_comment|/*  MII read and write registers */
DECL|macro|MII_WRITE_DATA
mdefine_line|#define MII_WRITE_DATA         0xaa
DECL|macro|MII_READ_DATA
mdefine_line|#define MII_READ_DATA          0xac
multiline_comment|/*  MII indicators */
DECL|macro|MII_INDICATOR
mdefine_line|#define MII_INDICATOR          0xae
DECL|macro|MII_NVALID
mdefine_line|#define  MII_NVALID            1&lt;&lt;2
DECL|macro|MII_SCAN
mdefine_line|#define  MII_SCAN              1&lt;&lt;1
DECL|macro|MII_BUSY
mdefine_line|#define  MII_BUSY              1&lt;&lt;0
multiline_comment|/*  Address filter  */
DECL|macro|ADDRESS_FILTER
mdefine_line|#define ADDRESS_FILTER         0xd0
DECL|macro|ADDRESS_RPPRM
mdefine_line|#define  ADDRESS_RPPRM         1&lt;&lt;3       /* multicast promis. mode */
DECL|macro|ADDRESS_RPPRO
mdefine_line|#define  ADDRESS_RPPRO         1&lt;&lt;2       /* promiscuous mode */
DECL|macro|ADDRESS_RPAMC
mdefine_line|#define  ADDRESS_RPAMC         1&lt;&lt;1       /* accept multicasts */
DECL|macro|ADDRESS_RPABC
mdefine_line|#define  ADDRESS_RPABC         1&lt;&lt;0       /* accept broadcasts */
multiline_comment|/*  Station addresses&n;&n;    Note that if the serial EEPROM is disabled, these values are all&n;    zero.  If, like us, you get the chips when they&squot;re fresh, they&squot;re&n;    also zero and you have to initialize the address */
DECL|macro|STATION_ADDRESS_0
mdefine_line|#define STATION_ADDRESS_0      0xd2
DECL|macro|STATION_ADDRESS_1
mdefine_line|#define STATION_ADDRESS_1      0xd4
DECL|macro|STATION_ADDRESS_2
mdefine_line|#define STATION_ADDRESS_2      0xd6
multiline_comment|/*  Hash tables  */
DECL|macro|HASH_TABLE_0
mdefine_line|#define HASH_TABLE_0           0xd8
DECL|macro|HASH_TABLE_1
mdefine_line|#define HASH_TABLE_1           0xda
DECL|macro|HASH_TABLE_2
mdefine_line|#define HASH_TABLE_2           0xdc
DECL|macro|HASH_TABLE_3
mdefine_line|#define HASH_TABLE_3           0xde
multiline_comment|/* PHY indentifiers */
DECL|macro|PHY_IDENTIFIER_0
mdefine_line|#define PHY_IDENTIFIER_0       0xe4
DECL|macro|PHY_IDENTIFIER_1
mdefine_line|#define PHY_IDENTIFIER_1       0xe6
multiline_comment|/*  MII Auto-negotiation register definitions  */
DECL|macro|MII_AUTO_NEGOTIATION_CONTROL
mdefine_line|#define MII_AUTO_NEGOTIATION_CONTROL        (0x0000)
DECL|macro|MANC_PHY_RESET
mdefine_line|#define   MANC_PHY_RESET                      (0x8000)
DECL|macro|MANC_PHY_LOOPBACK_ENABLE
mdefine_line|#define   MANC_PHY_LOOPBACK_ENABLE            (0x4000)
DECL|macro|MANC_PHY_LOOPBACK_DISABLE
mdefine_line|#define   MANC_PHY_LOOPBACK_DISABLE           (0x0000)
DECL|macro|MANC_PHY_SPEED_100
mdefine_line|#define   MANC_PHY_SPEED_100                  (0x2000)
DECL|macro|MANC_PHY_SPEED_10
mdefine_line|#define   MANC_PHY_SPEED_10                   (0x0000)
DECL|macro|MANC_AUTO_NEGOTIATION_ENABLE
mdefine_line|#define   MANC_AUTO_NEGOTIATION_ENABLE        (0x1000)
DECL|macro|MANC_AUTO_NEGOTIATION_DISABLE
mdefine_line|#define   MANC_AUTO_NEGOTIATION_DISABLE       (0x0000)
DECL|macro|MANC_PHY_POWER_DOWN
mdefine_line|#define   MANC_PHY_POWER_DOWN                 (0x0800)
DECL|macro|MANC_PHY_POWER_UP
mdefine_line|#define   MANC_PHY_POWER_UP                   (0x0000)
DECL|macro|MANC_ISOLATE_ENABLE
mdefine_line|#define   MANC_ISOLATE_ENABLE                 (0x0400)
DECL|macro|MANC_ISOLATE_DISABLE
mdefine_line|#define   MANC_ISOLATE_DISABLE                (0x0000)
DECL|macro|MANC_RESTART_AUTO_NEGOTIATION
mdefine_line|#define   MANC_RESTART_AUTO_NEGOTIATION       (0x0200)
DECL|macro|MANC_FULL_DUPLEX
mdefine_line|#define   MANC_FULL_DUPLEX                    (0x0100)
DECL|macro|MANC_HALF_DUPLEX
mdefine_line|#define   MANC_HALF_DUPLEX                    (0x0000)
DECL|macro|MII_AUTO_NEGOTIATION_STATUS
mdefine_line|#define MII_AUTO_NEGOTIATION_STATUS         (0x0001)
DECL|macro|MANS_100BASE_T4_HALF_DUPLEX
mdefine_line|#define   MANS_100BASE_T4_HALF_DUPLEX         (0x8000)
DECL|macro|MANS_100BASE_X_FULL_DUPLEX
mdefine_line|#define   MANS_100BASE_X_FULL_DUPLEX          (0x4000)
DECL|macro|MANS_100BASE_X_HALF_DUPLEX
mdefine_line|#define   MANS_100BASE_X_HALF_DUPLEX          (0x2000)
DECL|macro|MANS_10MBS_FULL_DUPLEX
mdefine_line|#define   MANS_10MBS_FULL_DUPLEX              (0x1000)
DECL|macro|MANS_10MBS_HALF_DUPLEX
mdefine_line|#define   MANS_10MBS_HALF_DUPLEX              (0x0800)
DECL|macro|MANS_AUTO_NEGOTIATION_COMPLETE
mdefine_line|#define   MANS_AUTO_NEGOTIATION_COMPLETE      (0x0020)
DECL|macro|MANS_REMOTE_FAULT
mdefine_line|#define   MANS_REMOTE_FAULT                   (0x0010)
DECL|macro|MANS_AUTO_NEGOTIATION_ABILITY
mdefine_line|#define   MANS_AUTO_NEGOTIATION_ABILITY       (0x0008)
DECL|macro|MANS_LINK_STATUS
mdefine_line|#define   MANS_LINK_STATUS                    (0x0004)
DECL|macro|MANS_JABBER_DETECT
mdefine_line|#define   MANS_JABBER_DETECT                  (0x0002)
DECL|macro|MANS_EXTENDED_CAPABILITY
mdefine_line|#define   MANS_EXTENDED_CAPABILITY            (0x0001)
DECL|macro|MII_PHY_IDENTIFIER_1
mdefine_line|#define MII_PHY_IDENTIFIER_1                (0x0002)
DECL|macro|MII_PHY_IDENTIFIER_2
mdefine_line|#define MII_PHY_IDENTIFIER_2                (0x0003)
DECL|macro|MII_AUTO_NEGOTIATION_ADVERTISEMENT
mdefine_line|#define MII_AUTO_NEGOTIATION_ADVERTISEMENT  (0x0004)
DECL|macro|MANA_NEXT_PAGE
mdefine_line|#define   MANA_NEXT_PAGE                      (0x8000)
DECL|macro|MANA_REMOTE_FAULT
mdefine_line|#define   MANA_REMOTE_FAULT                   (0x2000)
DECL|macro|MANA_TECHNOLOGY_ABILITY_MASK
mdefine_line|#define   MANA_TECHNOLOGY_ABILITY_MASK        (0x1FE0)
DECL|macro|MANATECH_10BASET_HALF_DUPLEX
mdefine_line|#define     MANATECH_10BASET_HALF_DUPLEX        (0x0020)
DECL|macro|MANATECH_10BASET_FULL_DUPLEX
mdefine_line|#define     MANATECH_10BASET_FULL_DUPLEX        (0x0040)
DECL|macro|MANATECH_100BASETX_HALF_DUPLEX
mdefine_line|#define     MANATECH_100BASETX_HALF_DUPLEX      (0x0080)
DECL|macro|MANATECH_100BASETX_FULL_DUPLEX
mdefine_line|#define     MANATECH_100BASETX_FULL_DUPLEX      (0x0100)
DECL|macro|MANATECH_100BASET4
mdefine_line|#define     MANATECH_100BASET4                  (0x0200)
DECL|macro|MANA_SELECTOR_MASK
mdefine_line|#define   MANA_SELECTOR_MASK                  (0x001F)
DECL|macro|MANASELECTOR_802_3
mdefine_line|#define     MANASELECTOR_802_3                  (0x0001)
DECL|macro|MII_AUTO_NEGOTIATION_LINK_PARTNER
mdefine_line|#define MII_AUTO_NEGOTIATION_LINK_PARTNER   (0x0005)
DECL|macro|MANLP_NEXT_PAGE
mdefine_line|#define   MANLP_NEXT_PAGE                     (0x8000)
DECL|macro|MANLP_ACKNOWLEDGE
mdefine_line|#define   MANLP_ACKNOWLEDGE                   (0x4000)
DECL|macro|MANLP_REMOTE_FAULT
mdefine_line|#define   MANLP_REMOTE_FAULT                  (0x2000)
DECL|macro|MANLP_TECHNOLOGY_ABILITY_MASK
mdefine_line|#define   MANLP_TECHNOLOGY_ABILITY_MASK       (0x1FE0)
DECL|macro|MANLP_SELECTOR_MASK
mdefine_line|#define   MANLP_SELECTOR_MASK                 (0x001F)
DECL|macro|MII_AUTO_NEGOTIATION_EXPANSION
mdefine_line|#define MII_AUTO_NEGOTIATION_EXPANSION      (0x0006)
DECL|macro|MANE_PARALLEL_DETECTION_FAULT
mdefine_line|#define   MANE_PARALLEL_DETECTION_FAULT       (0x0010)
DECL|macro|MANE_LINK_PARTNER_NEXT_PAGE_ABLE
mdefine_line|#define   MANE_LINK_PARTNER_NEXT_PAGE_ABLE    (0x0008)
DECL|macro|MANE_NEXT_PAGE_ABLE
mdefine_line|#define   MANE_NEXT_PAGE_ABLE                 (0x0004)
DECL|macro|MANE_PAGE_RECEIVED
mdefine_line|#define   MANE_PAGE_RECEIVED                  (0x0002)
DECL|macro|MANE_LINK_PARTNER_AUTO_ABLE
mdefine_line|#define   MANE_LINK_PARTNER_AUTO_ABLE         (0x0001)
DECL|macro|MII_AUTO_NEGOTIATION_NEXT_PAGE_TRANSMIT
mdefine_line|#define MII_AUTO_NEGOTIATION_NEXT_PAGE_TRANSMIT (0x0007)
DECL|macro|MANNPT_NEXT_PAGE
mdefine_line|#define   MANNPT_NEXT_PAGE                    (0x8000)
DECL|macro|MANNPT_MESSAGE_PAGE
mdefine_line|#define   MANNPT_MESSAGE_PAGE                 (0x2000)
DECL|macro|MANNPT_ACKNOWLEDGE_2
mdefine_line|#define   MANNPT_ACKNOWLEDGE_2                (0x1000)
DECL|macro|MANNPT_TOGGLE
mdefine_line|#define   MANNPT_TOGGLE                       (0x0800)
DECL|macro|MANNPT_MESSAGE_FIELD_MASK
mdefine_line|#define   MANNPT_MESSAGE_FIELD_MASK           (0x07FF)
macro_line|#endif
eof
