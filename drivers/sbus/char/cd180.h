multiline_comment|/* Definitions for Cirrus Logic CL-CD180 8-port async mux chip */
DECL|macro|CD180_NCH
mdefine_line|#define CD180_NCH       8       /* Total number of channels                */
DECL|macro|CD180_TPC
mdefine_line|#define CD180_TPC       16      /* Ticks per character                     */
DECL|macro|CD180_NFIFO
mdefine_line|#define CD180_NFIFO&t;8&t;/* TX FIFO size                            */
multiline_comment|/* Global registers */
DECL|macro|CD180_GFRCR
mdefine_line|#define CD180_GFRCR&t;0x6b&t;/* Global Firmware Revision Code Register  */
DECL|macro|CD180_SRCR
mdefine_line|#define CD180_SRCR&t;0x66&t;/* Service Request Configuration Register  */
DECL|macro|CD180_PPRH
mdefine_line|#define CD180_PPRH&t;0x70&t;/* Prescaler Period Register High&t;   */
DECL|macro|CD180_PPRL
mdefine_line|#define CD180_PPRL&t;0x71&t;/* Prescaler Period Register Low&t;   */
DECL|macro|CD180_MSMR
mdefine_line|#define CD180_MSMR&t;0x61&t;/* Modem Service Match Register&t;&t;   */
DECL|macro|CD180_TSMR
mdefine_line|#define CD180_TSMR&t;0x62&t;/* Transmit Service Match Register&t;   */
DECL|macro|CD180_RSMR
mdefine_line|#define CD180_RSMR&t;0x63&t;/* Receive Service Match Register&t;   */
DECL|macro|CD180_GSVR
mdefine_line|#define CD180_GSVR&t;0x40&t;/* Global Service Vector Register&t;   */
DECL|macro|CD180_SRSR
mdefine_line|#define CD180_SRSR&t;0x65&t;/* Service Request Status Register&t;   */
DECL|macro|CD180_GSCR
mdefine_line|#define CD180_GSCR&t;0x41&t;/* Global Service Channel Register&t;   */
DECL|macro|CD180_CAR
mdefine_line|#define CD180_CAR&t;0x64&t;/* Channel Access Register&t;&t;   */
multiline_comment|/* Indexed registers */
DECL|macro|CD180_RDCR
mdefine_line|#define CD180_RDCR&t;0x07&t;/* Receive Data Count Register&t;&t;   */
DECL|macro|CD180_RDR
mdefine_line|#define CD180_RDR&t;0x78&t;/* Receiver Data Register&t;&t;   */
DECL|macro|CD180_RCSR
mdefine_line|#define CD180_RCSR&t;0x7a&t;/* Receiver Character Status Register&t;   */
DECL|macro|CD180_TDR
mdefine_line|#define CD180_TDR&t;0x7b&t;/* Transmit Data Register&t;&t;   */
DECL|macro|CD180_EOSRR
mdefine_line|#define CD180_EOSRR&t;0x7f&t;/* End of Service Request Register&t;   */
multiline_comment|/* Channel Registers */
DECL|macro|CD180_SRER
mdefine_line|#define CD180_SRER      0x02    /* Service Request Enable Register         */
DECL|macro|CD180_CCR
mdefine_line|#define CD180_CCR       0x01    /* Channel Command Register                */
DECL|macro|CD180_COR1
mdefine_line|#define CD180_COR1      0x03    /* Channel Option Register 1               */
DECL|macro|CD180_COR2
mdefine_line|#define CD180_COR2      0x04    /* Channel Option Register 2               */
DECL|macro|CD180_COR3
mdefine_line|#define CD180_COR3      0x05    /* Channel Option Register 3               */
DECL|macro|CD180_CCSR
mdefine_line|#define CD180_CCSR      0x06    /* Channel Control Status Register         */
DECL|macro|CD180_RTPR
mdefine_line|#define CD180_RTPR      0x18    /* Receive Timeout Period Register         */
DECL|macro|CD180_RBPRH
mdefine_line|#define CD180_RBPRH     0x31    /* Receive Bit Rate Period Register High  */
DECL|macro|CD180_RBPRL
mdefine_line|#define CD180_RBPRL     0x32    /* Receive Bit Rate Period Register Low   */
DECL|macro|CD180_TBPRH
mdefine_line|#define CD180_TBPRH     0x39    /* Transmit Bit Rate Period Register High */
DECL|macro|CD180_TBPRL
mdefine_line|#define CD180_TBPRL     0x3a    /* Transmit Bit Rate Period Register Low  */
DECL|macro|CD180_SCHR1
mdefine_line|#define CD180_SCHR1     0x09    /* Special Character Register 1            */
DECL|macro|CD180_SCHR2
mdefine_line|#define CD180_SCHR2     0x0a    /* Special Character Register 2            */
DECL|macro|CD180_SCHR3
mdefine_line|#define CD180_SCHR3     0x0b    /* Special Character Register 3            */
DECL|macro|CD180_SCHR4
mdefine_line|#define CD180_SCHR4     0x0c    /* Special Character Register 4            */
DECL|macro|CD180_MCR
mdefine_line|#define CD180_MCR       0x12    /* Modem Change Register                   */
DECL|macro|CD180_MCOR1
mdefine_line|#define CD180_MCOR1     0x10    /* Modem Change Option 1 Register          */
DECL|macro|CD180_MCOR2
mdefine_line|#define CD180_MCOR2     0x11    /* Modem Change Option 2 Register          */
DECL|macro|CD180_MSVR
mdefine_line|#define CD180_MSVR      0x28    /* Modem Signal Value Register             */
DECL|macro|CD180_MSVRTS
mdefine_line|#define CD180_MSVRTS    0x29    /* Modem Signal Value RTS                  */
DECL|macro|CD180_MSVDTR
mdefine_line|#define CD180_MSVDTR    0x2a    /* Modem Signal Value DTR                  */
multiline_comment|/* Global Interrupt Vector Register (R/W) */
DECL|macro|GSVR_ITMASK
mdefine_line|#define GSVR_ITMASK     0x07     /* Interrupt type mask                     */
DECL|macro|GSVR_IT_MDM
mdefine_line|#define  GSVR_IT_MDM     0x01    /* Modem Signal Change Interrupt           */
DECL|macro|GSVR_IT_TX
mdefine_line|#define  GSVR_IT_TX      0x02    /* Transmit Data Interrupt                 */
DECL|macro|GSVR_IT_RGD
mdefine_line|#define  GSVR_IT_RGD     0x03    /* Receive Good Data Interrupt             */
DECL|macro|GSVR_IT_REXC
mdefine_line|#define  GSVR_IT_REXC    0x07    /* Receive Exception Interrupt             */
multiline_comment|/* Global Interrupt Channel Register (R/W) */
DECL|macro|GSCR_CHAN
mdefine_line|#define GSCR_CHAN       0x1c    /* Channel Number Mask                     */
DECL|macro|GSCR_CHAN_OFF
mdefine_line|#define GSCR_CHAN_OFF   2       /* Channel Number Offset                   */
multiline_comment|/* Channel Address Register (R/W) */
DECL|macro|CAR_CHAN
mdefine_line|#define CAR_CHAN        0x07    /* Channel Number Mask                     */
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
multiline_comment|/* Service Request Enable Register (R/W) */
DECL|macro|SRER_DSR
mdefine_line|#define SRER_DSR         0x80    /* Enable interrupt on DSR change          */
DECL|macro|SRER_CD
mdefine_line|#define SRER_CD          0x40    /* Enable interrupt on CD change           */
DECL|macro|SRER_CTS
mdefine_line|#define SRER_CTS         0x20    /* Enable interrupt on CTS change          */
DECL|macro|SRER_RXD
mdefine_line|#define SRER_RXD         0x10    /* Enable interrupt on Receive Data        */
DECL|macro|SRER_RXSC
mdefine_line|#define SRER_RXSC        0x08    /* Enable interrupt on Receive Spec. Char  */
DECL|macro|SRER_TXRDY
mdefine_line|#define SRER_TXRDY       0x04    /* Enable interrupt on TX FIFO empty       */
DECL|macro|SRER_TXEMPTY
mdefine_line|#define SRER_TXEMPTY     0x02    /* Enable interrupt on TX completely empty */
DECL|macro|SRER_RET
mdefine_line|#define SRER_RET         0x01    /* Enable interrupt on RX Exc. Timeout     */
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
multiline_comment|/* Service Request Status Register */
DECL|macro|SRSR_CMASK
mdefine_line|#define SRSR_CMASK&t;0xC0&t;/* Current Service Context Mask            */
DECL|macro|SRSR_CNONE
mdefine_line|#define  SRSR_CNONE&t;0x00&t;/* Not in a service context&t;&t;   */
DECL|macro|SRSR_CRX
mdefine_line|#define  SRSR_CRX&t;0x40&t;/* Rx Context&t;&t;&t;&t;   */
DECL|macro|SRSR_CTX
mdefine_line|#define  SRSR_CTX&t;0x80&t;/* Tx Context&t;&t;&t;&t;   */
DECL|macro|SRSR_CMDM
mdefine_line|#define  SRSR_CMDM&t;0xC0&t;/* Modem Context&t;&t;&t;   */
DECL|macro|SRSR_ANYINT
mdefine_line|#define SRSR_ANYINT&t;0x6F&t;/* Any interrupt flag&t;&t;&t;   */
DECL|macro|SRSR_RINT
mdefine_line|#define SRSR_RINT&t;0x10&t;/* Receive Interrupt&t;&t;&t;   */
DECL|macro|SRSR_TINT
mdefine_line|#define SRSR_TINT&t;0x04&t;/* Transmit Interrupt&t;&t;&t;   */
DECL|macro|SRSR_MINT
mdefine_line|#define SRSR_MINT&t;0x01&t;/* Modem Interrupt&t;&t;&t;   */
DECL|macro|SRSR_REXT
mdefine_line|#define SRSR_REXT&t;0x20&t;/* Receive External Interrupt&t;&t;   */
DECL|macro|SRSR_TEXT
mdefine_line|#define SRSR_TEXT&t;0x08&t;/* Transmit External Interrupt&t;&t;   */
DECL|macro|SRSR_MEXT
mdefine_line|#define SRSR_MEXT&t;0x02&t;/* Modem External Interrupt&t;&t;   */
multiline_comment|/* Service Request Configuration Register */
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
multiline_comment|/* Values for register-based Interrupt ACKs */
DECL|macro|CD180_ACK_MINT
mdefine_line|#define CD180_ACK_MINT&t;0x75&t;/* goes to MSMR&t;&t;&t;&t;   */
DECL|macro|CD180_ACK_TINT
mdefine_line|#define CD180_ACK_TINT&t;0x76&t;/* goes to TSMR&t;&t;&t;&t;   */
DECL|macro|CD180_ACK_RINT
mdefine_line|#define CD180_ACK_RINT&t;0x77&t;/* goes to RSMR&t;&t;&t;&t;   */
multiline_comment|/* Escape characters */
DECL|macro|CD180_C_ESC
mdefine_line|#define CD180_C_ESC     0x00    /* Escape character                        */
DECL|macro|CD180_C_SBRK
mdefine_line|#define CD180_C_SBRK    0x81    /* Start sending BREAK                     */
DECL|macro|CD180_C_DELAY
mdefine_line|#define CD180_C_DELAY   0x82    /* Delay output                            */
DECL|macro|CD180_C_EBRK
mdefine_line|#define CD180_C_EBRK    0x83    /* Stop sending BREAK                      */
eof
