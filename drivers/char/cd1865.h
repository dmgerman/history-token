multiline_comment|/*&n; *      linux/drivers/char/cd1865.h -- Definitions relating to the CD1865&n; *                          for the Specialix IO8+ multiport serial driver.&n; *&n; *      Copyright (C) 1997 Roger Wolff (R.E.Wolff@BitWizard.nl)&n; *      Copyright (C) 1994-1996  Dmitry Gorodchanin (pgmdsg@ibi.com)&n; *&n; *      Specialix pays for the development and support of this driver.&n; *      Please DO contact io8-linux@specialix.co.uk if you require&n; *      support.&n; *&n; *      This driver was developped in the BitWizard linux device&n; *      driver service. If you require a linux device driver for your&n; *      product, please contact devices@BitWizard.nl for a quote.&n; *&n; */
multiline_comment|/*&n; * Definitions for Driving CD180/CD1864/CD1865 based eightport serial cards.&n; */
multiline_comment|/* Values of choice for Interrupt ACKs */
multiline_comment|/* These values are &quot;obligatory&quot; if you use the register based&n; * interrupt acknowledgements. See page 99-101 of V2.0 of the CD1865&n; * databook */
DECL|macro|SX_ACK_MINT
mdefine_line|#define SX_ACK_MINT     0x75    /* goes to PILR1                           */
DECL|macro|SX_ACK_TINT
mdefine_line|#define SX_ACK_TINT     0x76    /* goes to PILR2                           */
DECL|macro|SX_ACK_RINT
mdefine_line|#define SX_ACK_RINT     0x77    /* goes to PILR3                           */
multiline_comment|/* Chip ID (is used when chips ar daisy chained.) */
DECL|macro|SX_ID
mdefine_line|#define SX_ID           0x10
multiline_comment|/* Definitions for Cirrus Logic CL-CD186x 8-port async mux chip */
DECL|macro|CD186x_NCH
mdefine_line|#define CD186x_NCH       8       /* Total number of channels                */
DECL|macro|CD186x_TPC
mdefine_line|#define CD186x_TPC       16      /* Ticks per character                     */
DECL|macro|CD186x_NFIFO
mdefine_line|#define CD186x_NFIFO&t; 8&t; /* TX FIFO size                            */
multiline_comment|/* Global registers */
DECL|macro|CD186x_GIVR
mdefine_line|#define CD186x_GIVR      0x40    /* Global Interrupt Vector Register        */
DECL|macro|CD186x_GICR
mdefine_line|#define CD186x_GICR      0x41    /* Global Interrupting Channel Register    */
DECL|macro|CD186x_PILR1
mdefine_line|#define CD186x_PILR1     0x61    /* Priority Interrupt Level Register 1     */
DECL|macro|CD186x_PILR2
mdefine_line|#define CD186x_PILR2     0x62    /* Priority Interrupt Level Register 2     */
DECL|macro|CD186x_PILR3
mdefine_line|#define CD186x_PILR3     0x63    /* Priority Interrupt Level Register 3     */
DECL|macro|CD186x_CAR
mdefine_line|#define CD186x_CAR       0x64    /* Channel Access Register                 */
DECL|macro|CD186x_SRSR
mdefine_line|#define CD186x_SRSR      0x65    /* Channel Access Register                 */
DECL|macro|CD186x_GFRCR
mdefine_line|#define CD186x_GFRCR     0x6b    /* Global Firmware Revision Code Register  */
DECL|macro|CD186x_PPRH
mdefine_line|#define CD186x_PPRH      0x70    /* Prescaler Period Register High          */
DECL|macro|CD186x_PPRL
mdefine_line|#define CD186x_PPRL      0x71    /* Prescaler Period Register Low           */
DECL|macro|CD186x_RDR
mdefine_line|#define CD186x_RDR       0x78    /* Receiver Data Register                  */
DECL|macro|CD186x_RCSR
mdefine_line|#define CD186x_RCSR      0x7a    /* Receiver Character Status Register      */
DECL|macro|CD186x_TDR
mdefine_line|#define CD186x_TDR       0x7b    /* Transmit Data Register                  */
DECL|macro|CD186x_EOIR
mdefine_line|#define CD186x_EOIR      0x7f    /* End of Interrupt Register               */
DECL|macro|CD186x_MRAR
mdefine_line|#define CD186x_MRAR      0x75    /* Modem Request Acknowlege register       */
DECL|macro|CD186x_TRAR
mdefine_line|#define CD186x_TRAR      0x76    /* Transmit Request Acknowlege register    */
DECL|macro|CD186x_RRAR
mdefine_line|#define CD186x_RRAR      0x77    /* Receive Request Acknowlege register     */
DECL|macro|CD186x_SRCR
mdefine_line|#define CD186x_SRCR      0x66    /* Service Request Configuration register  */
multiline_comment|/* Channel Registers */
DECL|macro|CD186x_CCR
mdefine_line|#define CD186x_CCR       0x01    /* Channel Command Register                */
DECL|macro|CD186x_IER
mdefine_line|#define CD186x_IER       0x02    /* Interrupt Enable Register               */
DECL|macro|CD186x_COR1
mdefine_line|#define CD186x_COR1      0x03    /* Channel Option Register 1               */
DECL|macro|CD186x_COR2
mdefine_line|#define CD186x_COR2      0x04    /* Channel Option Register 2               */
DECL|macro|CD186x_COR3
mdefine_line|#define CD186x_COR3      0x05    /* Channel Option Register 3               */
DECL|macro|CD186x_CCSR
mdefine_line|#define CD186x_CCSR      0x06    /* Channel Control Status Register         */
DECL|macro|CD186x_RDCR
mdefine_line|#define CD186x_RDCR      0x07    /* Receive Data Count Register             */
DECL|macro|CD186x_SCHR1
mdefine_line|#define CD186x_SCHR1     0x09    /* Special Character Register 1            */
DECL|macro|CD186x_SCHR2
mdefine_line|#define CD186x_SCHR2     0x0a    /* Special Character Register 2            */
DECL|macro|CD186x_SCHR3
mdefine_line|#define CD186x_SCHR3     0x0b    /* Special Character Register 3            */
DECL|macro|CD186x_SCHR4
mdefine_line|#define CD186x_SCHR4     0x0c    /* Special Character Register 4            */
DECL|macro|CD186x_MCOR1
mdefine_line|#define CD186x_MCOR1     0x10    /* Modem Change Option 1 Register          */
DECL|macro|CD186x_MCOR2
mdefine_line|#define CD186x_MCOR2     0x11    /* Modem Change Option 2 Register          */
DECL|macro|CD186x_MCR
mdefine_line|#define CD186x_MCR       0x12    /* Modem Change Register                   */
DECL|macro|CD186x_RTPR
mdefine_line|#define CD186x_RTPR      0x18    /* Receive Timeout Period Register         */
DECL|macro|CD186x_MSVR
mdefine_line|#define CD186x_MSVR      0x28    /* Modem Signal Value Register             */
DECL|macro|CD186x_MSVRTS
mdefine_line|#define CD186x_MSVRTS    0x29    /* Modem Signal Value Register             */
DECL|macro|CD186x_MSVDTR
mdefine_line|#define CD186x_MSVDTR    0x2a    /* Modem Signal Value Register             */
DECL|macro|CD186x_RBPRH
mdefine_line|#define CD186x_RBPRH     0x31    /* Receive Baud Rate Period Register High  */
DECL|macro|CD186x_RBPRL
mdefine_line|#define CD186x_RBPRL     0x32    /* Receive Baud Rate Period Register Low   */
DECL|macro|CD186x_TBPRH
mdefine_line|#define CD186x_TBPRH     0x39    /* Transmit Baud Rate Period Register High */
DECL|macro|CD186x_TBPRL
mdefine_line|#define CD186x_TBPRL     0x3a    /* Transmit Baud Rate Period Register Low  */
multiline_comment|/* Global Interrupt Vector Register (R/W) */
DECL|macro|GIVR_ITMASK
mdefine_line|#define GIVR_ITMASK     0x07     /* Interrupt type mask                     */
DECL|macro|GIVR_IT_MODEM
mdefine_line|#define  GIVR_IT_MODEM   0x01    /* Modem Signal Change Interrupt           */
DECL|macro|GIVR_IT_TX
mdefine_line|#define  GIVR_IT_TX      0x02    /* Transmit Data Interrupt                 */
DECL|macro|GIVR_IT_RCV
mdefine_line|#define  GIVR_IT_RCV     0x03    /* Receive Good Data Interrupt             */
DECL|macro|GIVR_IT_REXC
mdefine_line|#define  GIVR_IT_REXC    0x07    /* Receive Exception Interrupt             */
multiline_comment|/* Global Interrupt Channel Register (R/W) */
DECL|macro|GICR_CHAN
mdefine_line|#define GICR_CHAN       0x1c    /* Channel Number Mask                     */
DECL|macro|GICR_CHAN_OFF
mdefine_line|#define GICR_CHAN_OFF   2       /* Channel Number shift                    */
multiline_comment|/* Channel Address Register (R/W) */
DECL|macro|CAR_CHAN
mdefine_line|#define CAR_CHAN        0x07    /* Channel Number Mask                     */
DECL|macro|CAR_A7
mdefine_line|#define CAR_A7          0x08    /* A7 Address Extension (unused)           */
multiline_comment|/* Receive Character Status Register (R/O) */
DECL|macro|RCSR_TOUT
mdefine_line|#define RCSR_TOUT       0x80    /* Rx Timeout                              */
DECL|macro|RCSR_SCDET
mdefine_line|#define RCSR_SCDET      0x70    /* Special Character Detected Mask         */
DECL|macro|RCSR_NO_SC
mdefine_line|#define  RCSR_NO_SC      0x00   /* No Special Characters Detected          */
DECL|macro|RCSR_SC_1
mdefine_line|#define  RCSR_SC_1       0x10   /* Special Char 1 (or 1 &amp; 3) Detected      */
DECL|macro|RCSR_SC_2
mdefine_line|#define  RCSR_SC_2       0x20   /* Special Char 2 (or 2 &amp; 4) Detected      */
DECL|macro|RCSR_SC_3
mdefine_line|#define  RCSR_SC_3       0x30   /* Special Char 3 Detected                 */
DECL|macro|RCSR_SC_4
mdefine_line|#define  RCSR_SC_4       0x40   /* Special Char 4 Detected                 */
DECL|macro|RCSR_BREAK
mdefine_line|#define RCSR_BREAK      0x08    /* Break has been detected                 */
DECL|macro|RCSR_PE
mdefine_line|#define RCSR_PE         0x04    /* Parity Error                            */
DECL|macro|RCSR_FE
mdefine_line|#define RCSR_FE         0x02    /* Frame Error                             */
DECL|macro|RCSR_OE
mdefine_line|#define RCSR_OE         0x01    /* Overrun Error                           */
multiline_comment|/* Channel Command Register (R/W) (commands in groups can be OR-ed) */
DECL|macro|CCR_HARDRESET
mdefine_line|#define CCR_HARDRESET   0x81    /* Reset the chip                          */
DECL|macro|CCR_SOFTRESET
mdefine_line|#define CCR_SOFTRESET   0x80    /* Soft Channel Reset                      */
DECL|macro|CCR_CORCHG1
mdefine_line|#define CCR_CORCHG1     0x42    /* Channel Option Register 1 Changed       */
DECL|macro|CCR_CORCHG2
mdefine_line|#define CCR_CORCHG2     0x44    /* Channel Option Register 2 Changed       */
DECL|macro|CCR_CORCHG3
mdefine_line|#define CCR_CORCHG3     0x48    /* Channel Option Register 3 Changed       */
DECL|macro|CCR_SSCH1
mdefine_line|#define CCR_SSCH1       0x21    /* Send Special Character 1                */
DECL|macro|CCR_SSCH2
mdefine_line|#define CCR_SSCH2       0x22    /* Send Special Character 2                */
DECL|macro|CCR_SSCH3
mdefine_line|#define CCR_SSCH3       0x23    /* Send Special Character 3                */
DECL|macro|CCR_SSCH4
mdefine_line|#define CCR_SSCH4       0x24    /* Send Special Character 4                */
DECL|macro|CCR_TXEN
mdefine_line|#define CCR_TXEN        0x18    /* Enable Transmitter                      */
DECL|macro|CCR_RXEN
mdefine_line|#define CCR_RXEN        0x12    /* Enable Receiver                         */
DECL|macro|CCR_TXDIS
mdefine_line|#define CCR_TXDIS       0x14    /* Disable Transmitter                     */
DECL|macro|CCR_RXDIS
mdefine_line|#define CCR_RXDIS       0x11    /* Disable Receiver                        */
multiline_comment|/* Interrupt Enable Register (R/W) */
DECL|macro|IER_DSR
mdefine_line|#define IER_DSR         0x80    /* Enable interrupt on DSR change          */
DECL|macro|IER_CD
mdefine_line|#define IER_CD          0x40    /* Enable interrupt on CD change           */
DECL|macro|IER_CTS
mdefine_line|#define IER_CTS         0x20    /* Enable interrupt on CTS change          */
DECL|macro|IER_RXD
mdefine_line|#define IER_RXD         0x10    /* Enable interrupt on Receive Data        */
DECL|macro|IER_RXSC
mdefine_line|#define IER_RXSC        0x08    /* Enable interrupt on Receive Spec. Char  */
DECL|macro|IER_TXRDY
mdefine_line|#define IER_TXRDY       0x04    /* Enable interrupt on TX FIFO empty       */
DECL|macro|IER_TXEMPTY
mdefine_line|#define IER_TXEMPTY     0x02    /* Enable interrupt on TX completely empty */
DECL|macro|IER_RET
mdefine_line|#define IER_RET         0x01    /* Enable interrupt on RX Exc. Timeout     */
multiline_comment|/* Channel Option Register 1 (R/W) */
DECL|macro|COR1_ODDP
mdefine_line|#define COR1_ODDP       0x80    /* Odd Parity                              */
DECL|macro|COR1_PARMODE
mdefine_line|#define COR1_PARMODE    0x60    /* Parity Mode mask                        */
DECL|macro|COR1_NOPAR
mdefine_line|#define  COR1_NOPAR      0x00   /* No Parity                               */
DECL|macro|COR1_FORCEPAR
mdefine_line|#define  COR1_FORCEPAR   0x20   /* Force Parity                            */
DECL|macro|COR1_NORMPAR
mdefine_line|#define  COR1_NORMPAR    0x40   /* Normal Parity                           */
DECL|macro|COR1_IGNORE
mdefine_line|#define COR1_IGNORE     0x10    /* Ignore Parity on RX                     */
DECL|macro|COR1_STOPBITS
mdefine_line|#define COR1_STOPBITS   0x0c    /* Number of Stop Bits                     */
DECL|macro|COR1_1SB
mdefine_line|#define  COR1_1SB        0x00   /* 1 Stop Bit                              */
DECL|macro|COR1_15SB
mdefine_line|#define  COR1_15SB       0x04   /* 1.5 Stop Bits                           */
DECL|macro|COR1_2SB
mdefine_line|#define  COR1_2SB        0x08   /* 2 Stop Bits                             */
DECL|macro|COR1_CHARLEN
mdefine_line|#define COR1_CHARLEN    0x03    /* Character Length                        */
DECL|macro|COR1_5BITS
mdefine_line|#define  COR1_5BITS      0x00   /* 5 bits                                  */
DECL|macro|COR1_6BITS
mdefine_line|#define  COR1_6BITS      0x01   /* 6 bits                                  */
DECL|macro|COR1_7BITS
mdefine_line|#define  COR1_7BITS      0x02   /* 7 bits                                  */
DECL|macro|COR1_8BITS
mdefine_line|#define  COR1_8BITS      0x03   /* 8 bits                                  */
multiline_comment|/* Channel Option Register 2 (R/W) */
DECL|macro|COR2_IXM
mdefine_line|#define COR2_IXM        0x80    /* Implied XON mode                        */
DECL|macro|COR2_TXIBE
mdefine_line|#define COR2_TXIBE      0x40    /* Enable In-Band (XON/XOFF) Flow Control  */
DECL|macro|COR2_ETC
mdefine_line|#define COR2_ETC        0x20    /* Embedded Tx Commands Enable             */
DECL|macro|COR2_LLM
mdefine_line|#define COR2_LLM        0x10    /* Local Loopback Mode                     */
DECL|macro|COR2_RLM
mdefine_line|#define COR2_RLM        0x08    /* Remote Loopback Mode                    */
DECL|macro|COR2_RTSAO
mdefine_line|#define COR2_RTSAO      0x04    /* RTS Automatic Output Enable             */
DECL|macro|COR2_CTSAE
mdefine_line|#define COR2_CTSAE      0x02    /* CTS Automatic Enable                    */
DECL|macro|COR2_DSRAE
mdefine_line|#define COR2_DSRAE      0x01    /* DSR Automatic Enable                    */
multiline_comment|/* Channel Option Register 3 (R/W) */
DECL|macro|COR3_XONCH
mdefine_line|#define COR3_XONCH      0x80    /* XON is a pair of characters (1 &amp; 3)     */
DECL|macro|COR3_XOFFCH
mdefine_line|#define COR3_XOFFCH     0x40    /* XOFF is a pair of characters (2 &amp; 4)    */
DECL|macro|COR3_FCT
mdefine_line|#define COR3_FCT        0x20    /* Flow-Control Transparency Mode          */
DECL|macro|COR3_SCDE
mdefine_line|#define COR3_SCDE       0x10    /* Special Character Detection Enable      */
DECL|macro|COR3_RXTH
mdefine_line|#define COR3_RXTH       0x0f    /* RX FIFO Threshold value (1-8)           */
multiline_comment|/* Channel Control Status Register (R/O) */
DECL|macro|CCSR_RXEN
mdefine_line|#define CCSR_RXEN       0x80    /* Receiver Enabled                        */
DECL|macro|CCSR_RXFLOFF
mdefine_line|#define CCSR_RXFLOFF    0x40    /* Receive Flow Off (XOFF was sent)        */
DECL|macro|CCSR_RXFLON
mdefine_line|#define CCSR_RXFLON     0x20    /* Receive Flow On (XON was sent)          */
DECL|macro|CCSR_TXEN
mdefine_line|#define CCSR_TXEN       0x08    /* Transmitter Enabled                     */
DECL|macro|CCSR_TXFLOFF
mdefine_line|#define CCSR_TXFLOFF    0x04    /* Transmit Flow Off (got XOFF)            */
DECL|macro|CCSR_TXFLON
mdefine_line|#define CCSR_TXFLON     0x02    /* Transmit Flow On (got XON)              */
multiline_comment|/* Modem Change Option Register 1 (R/W) */
DECL|macro|MCOR1_DSRZD
mdefine_line|#define MCOR1_DSRZD     0x80    /* Detect 0-&gt;1 transition of DSR           */
DECL|macro|MCOR1_CDZD
mdefine_line|#define MCOR1_CDZD      0x40    /* Detect 0-&gt;1 transition of CD            */
DECL|macro|MCOR1_CTSZD
mdefine_line|#define MCOR1_CTSZD     0x20    /* Detect 0-&gt;1 transition of CTS           */
DECL|macro|MCOR1_DTRTH
mdefine_line|#define MCOR1_DTRTH     0x0f    /* Auto DTR flow control Threshold (1-8)   */
DECL|macro|MCOR1_NODTRFC
mdefine_line|#define  MCOR1_NODTRFC   0x0     /* Automatic DTR flow control disabled     */
multiline_comment|/* Modem Change Option Register 2 (R/W) */
DECL|macro|MCOR2_DSROD
mdefine_line|#define MCOR2_DSROD     0x80    /* Detect 1-&gt;0 transition of DSR           */
DECL|macro|MCOR2_CDOD
mdefine_line|#define MCOR2_CDOD      0x40    /* Detect 1-&gt;0 transition of CD            */
DECL|macro|MCOR2_CTSOD
mdefine_line|#define MCOR2_CTSOD     0x20    /* Detect 1-&gt;0 transition of CTS           */
multiline_comment|/* Modem Change Register (R/W) */
DECL|macro|MCR_DSRCHG
mdefine_line|#define MCR_DSRCHG      0x80    /* DSR Changed                             */
DECL|macro|MCR_CDCHG
mdefine_line|#define MCR_CDCHG       0x40    /* CD Changed                              */
DECL|macro|MCR_CTSCHG
mdefine_line|#define MCR_CTSCHG      0x20    /* CTS Changed                             */
multiline_comment|/* Modem Signal Value Register (R/W) */
DECL|macro|MSVR_DSR
mdefine_line|#define MSVR_DSR        0x80    /* Current state of DSR input              */
DECL|macro|MSVR_CD
mdefine_line|#define MSVR_CD         0x40    /* Current state of CD input               */
DECL|macro|MSVR_CTS
mdefine_line|#define MSVR_CTS        0x20    /* Current state of CTS input              */
DECL|macro|MSVR_DTR
mdefine_line|#define MSVR_DTR        0x02    /* Current state of DTR output             */
DECL|macro|MSVR_RTS
mdefine_line|#define MSVR_RTS        0x01    /* Current state of RTS output             */
multiline_comment|/* Escape characters */
DECL|macro|CD186x_C_ESC
mdefine_line|#define CD186x_C_ESC     0x00    /* Escape character                        */
DECL|macro|CD186x_C_SBRK
mdefine_line|#define CD186x_C_SBRK    0x81    /* Start sending BREAK                     */
DECL|macro|CD186x_C_DELAY
mdefine_line|#define CD186x_C_DELAY   0x82    /* Delay output                            */
DECL|macro|CD186x_C_EBRK
mdefine_line|#define CD186x_C_EBRK    0x83    /* Stop sending BREAK                      */
DECL|macro|SRSR_RREQint
mdefine_line|#define SRSR_RREQint     0x10    /* This chip wants &quot;rec&quot; serviced          */
DECL|macro|SRSR_TREQint
mdefine_line|#define SRSR_TREQint     0x04    /* This chip wants &quot;transmit&quot; serviced     */
DECL|macro|SRSR_MREQint
mdefine_line|#define SRSR_MREQint     0x01    /* This chip wants &quot;mdm change&quot; serviced   */
DECL|macro|SRCR_PKGTYPE
mdefine_line|#define SRCR_PKGTYPE    0x80
DECL|macro|SRCR_REGACKEN
mdefine_line|#define SRCR_REGACKEN   0x40
DECL|macro|SRCR_DAISYEN
mdefine_line|#define SRCR_DAISYEN    0x20
DECL|macro|SRCR_GLOBPRI
mdefine_line|#define SRCR_GLOBPRI    0x10
DECL|macro|SRCR_UNFAIR
mdefine_line|#define SRCR_UNFAIR     0x08
DECL|macro|SRCR_AUTOPRI
mdefine_line|#define SRCR_AUTOPRI    0x02
DECL|macro|SRCR_PRISEL
mdefine_line|#define SRCR_PRISEL     0x01
eof
