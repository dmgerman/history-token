multiline_comment|/*********************************************************&n; *                                                       *&n; * Definition of D-Link DE-620 Ethernet Pocket adapter   *&n; *                                                       *&n; *********************************************************/
multiline_comment|/* DE-620&squot;s CMD port Command */
DECL|macro|CS0
mdefine_line|#define CS0&t;&t;0x08&t;/* 1-&gt;0 command strobe */
DECL|macro|ICEN
mdefine_line|#define ICEN&t;&t;0x04&t;/* 0=enable DL3520 host interface */
DECL|macro|DS0
mdefine_line|#define DS0&t;&t;0x02&t;/* 1-&gt;0 data strobe 0 */
DECL|macro|DS1
mdefine_line|#define DS1&t;&t;0x01&t;/* 1-&gt;0 data strobe 1 */
DECL|macro|WDIR
mdefine_line|#define WDIR&t;&t;0x20&t;/* general 0=read  1=write */
DECL|macro|RDIR
mdefine_line|#define RDIR&t;&t;0x00&t;/*  (not 100% confirm ) */
DECL|macro|PS2WDIR
mdefine_line|#define PS2WDIR&t;&t;0x00&t;/* ps/2 mode 1=read, 0=write */
DECL|macro|PS2RDIR
mdefine_line|#define PS2RDIR&t;&t;0x20
DECL|macro|IRQEN
mdefine_line|#define IRQEN&t;&t;0x10&t;/* 1 = enable printer IRQ line */
DECL|macro|SELECTIN
mdefine_line|#define SELECTIN&t;0x08&t;/* 1 = select printer */
DECL|macro|INITP
mdefine_line|#define INITP&t;&t;0x04&t;/* 0 = initial printer */
DECL|macro|AUTOFEED
mdefine_line|#define AUTOFEED&t;0x02&t;/* 1 = printer auto form feed */
DECL|macro|STROBE
mdefine_line|#define STROBE&t;&t;0x01&t;/* 0-&gt;1 data strobe */
DECL|macro|RESET
mdefine_line|#define RESET&t;&t;0x08
DECL|macro|NIS0
mdefine_line|#define NIS0&t;&t;0x20&t;/* 0 = BNC, 1 = UTP */
DECL|macro|NCTL0
mdefine_line|#define NCTL0&t;&t;0x10
multiline_comment|/* DE-620 DIC Command */
DECL|macro|W_DUMMY
mdefine_line|#define W_DUMMY&t;&t;0x00&t;/* DIC reserved command */
DECL|macro|W_CR
mdefine_line|#define W_CR&t;&t;0x20&t;/* DIC write command register */
DECL|macro|W_NPR
mdefine_line|#define W_NPR&t;&t;0x40&t;/* DIC write Next Page Register */
DECL|macro|W_TBR
mdefine_line|#define W_TBR&t;&t;0x60&t;/* DIC write Tx Byte Count 1 reg */
DECL|macro|W_RSA
mdefine_line|#define W_RSA&t;&t;0x80&t;/* DIC write Remote Start Addr 1 */
multiline_comment|/* DE-620&squot;s STAT port bits 7-4 */
DECL|macro|EMPTY
mdefine_line|#define EMPTY&t;&t;0x80&t;/* 1 = receive buffer empty */
DECL|macro|INTLEVEL
mdefine_line|#define INTLEVEL&t;0x40&t;/* 1 = interrupt level is high */
DECL|macro|TXBF1
mdefine_line|#define TXBF1&t;&t;0x20&t;/* 1 = transmit buffer 1 is in use */
DECL|macro|TXBF0
mdefine_line|#define TXBF0&t;&t;0x10&t;/* 1 = transmit buffer 0 is in use */
DECL|macro|READY
mdefine_line|#define READY&t;&t;0x08&t;/* 1 = h/w ready to accept cmd/data */
multiline_comment|/* IDC 1 Command */
DECL|macro|W_RSA1
mdefine_line|#define&t;W_RSA1&t;&t;0xa0&t;/* write remote start address 1 */
DECL|macro|W_RSA0
mdefine_line|#define&t;W_RSA0&t;&t;0xa1&t;/* write remote start address 0 */
DECL|macro|W_NPRF
mdefine_line|#define&t;W_NPRF&t;&t;0xa2&t;/* write next page register NPR15-NPR8 */
DECL|macro|W_DFR
mdefine_line|#define&t;W_DFR&t;&t;0xa3&t;/* write delay factor register */
DECL|macro|W_CPR
mdefine_line|#define&t;W_CPR&t;&t;0xa4&t;/* write current page register */
DECL|macro|W_SPR
mdefine_line|#define&t;W_SPR&t;&t;0xa5&t;/* write start page register */
DECL|macro|W_EPR
mdefine_line|#define&t;W_EPR&t;&t;0xa6&t;/* write end page register */
DECL|macro|W_SCR
mdefine_line|#define&t;W_SCR&t;&t;0xa7&t;/* write system configuration register */
DECL|macro|W_TCR
mdefine_line|#define&t;W_TCR&t;&t;0xa8&t;/* write Transceiver Configuration reg */
DECL|macro|W_EIP
mdefine_line|#define&t;W_EIP&t;&t;0xa9&t;/* write EEPM Interface port */
DECL|macro|W_PAR0
mdefine_line|#define&t;W_PAR0&t;&t;0xaa&t;/* write physical address register 0 */
DECL|macro|W_PAR1
mdefine_line|#define&t;W_PAR1&t;&t;0xab&t;/* write physical address register 1 */
DECL|macro|W_PAR2
mdefine_line|#define&t;W_PAR2&t;&t;0xac&t;/* write physical address register 2 */
DECL|macro|W_PAR3
mdefine_line|#define&t;W_PAR3&t;&t;0xad&t;/* write physical address register 3 */
DECL|macro|W_PAR4
mdefine_line|#define&t;W_PAR4&t;&t;0xae&t;/* write physical address register 4 */
DECL|macro|W_PAR5
mdefine_line|#define&t;W_PAR5&t;&t;0xaf&t;/* write physical address register 5 */
multiline_comment|/* IDC 2 Command */
DECL|macro|R_STS
mdefine_line|#define&t;R_STS&t;&t;0xc0&t;/* read status register */
DECL|macro|R_CPR
mdefine_line|#define&t;R_CPR&t;&t;0xc1&t;/* read current page register */
DECL|macro|R_BPR
mdefine_line|#define&t;R_BPR&t;&t;0xc2&t;/* read boundary page register */
DECL|macro|R_TDR
mdefine_line|#define&t;R_TDR&t;&t;0xc3&t;/* read time domain reflectometry reg */
multiline_comment|/* STATUS Register */
DECL|macro|EEDI
mdefine_line|#define EEDI&t;&t;0x80&t;/* EEPM DO pin */
DECL|macro|TXSUC
mdefine_line|#define TXSUC&t;&t;0x40&t;/* tx success */
DECL|macro|T16
mdefine_line|#define T16&t;&t;0x20&t;/* tx fail 16 times */
DECL|macro|TS1
mdefine_line|#define TS1&t;&t;0x40&t;/* 0=Tx success, 1=T16 */
DECL|macro|TS0
mdefine_line|#define TS0&t;&t;0x20&t;/* 0=Tx success, 1=T16 */
DECL|macro|RXGOOD
mdefine_line|#define RXGOOD&t;&t;0x10&t;/* rx a good packet */
DECL|macro|RXCRC
mdefine_line|#define RXCRC&t;&t;0x08&t;/* rx a CRC error packet */
DECL|macro|RXSHORT
mdefine_line|#define RXSHORT&t;&t;0x04&t;/* rx a short packet */
DECL|macro|COLS
mdefine_line|#define COLS&t;&t;0x02&t;/* coaxial collision status */
DECL|macro|LNKS
mdefine_line|#define LNKS&t;&t;0x01&t;/* UTP link status */
multiline_comment|/* Command Register */
DECL|macro|CLEAR
mdefine_line|#define CLEAR&t;&t;0x10&t;/* reset part of hardware */
DECL|macro|NOPER
mdefine_line|#define NOPER&t;&t;0x08&t;/* No Operation */
DECL|macro|RNOP
mdefine_line|#define RNOP&t;&t;0x08
DECL|macro|RRA
mdefine_line|#define RRA&t;&t;0x06&t;/* After RR then auto-advance NPR &amp; BPR(=NPR-1) */
DECL|macro|RRN
mdefine_line|#define RRN&t;&t;0x04&t;/* Normal Remote Read mode */
DECL|macro|RW1
mdefine_line|#define RW1&t;&t;0x02&t;/* Remote Write tx buffer 1  ( page 6 - 11 ) */
DECL|macro|RW0
mdefine_line|#define RW0&t;&t;0x00&t;/* Remote Write tx buffer 0  ( page 0 - 5 ) */
DECL|macro|TXEN
mdefine_line|#define TXEN&t;&t;0x01&t;/* 0-&gt;1 tx enable */
multiline_comment|/* System Configuration Register */
DECL|macro|TESTON
mdefine_line|#define TESTON&t;&t;0x80&t;/* test host data transfer reliability */
DECL|macro|SLEEP
mdefine_line|#define SLEEP&t;&t;0x40&t;/* sleep mode */
macro_line|#if 0
mdefine_line|#define FASTMODE&t;0x04&t;/* fast mode for intel 82360SL fast mode */
mdefine_line|#define BYTEMODE&t;0x02&t;/* byte mode */
macro_line|#else
DECL|macro|FASTMODE
mdefine_line|#define FASTMODE&t;0x20&t;/* fast mode for intel 82360SL fast mode */
DECL|macro|BYTEMODE
mdefine_line|#define BYTEMODE&t;0x10&t;/* byte mode */
macro_line|#endif
DECL|macro|NIBBLEMODE
mdefine_line|#define NIBBLEMODE&t;0x00&t;/* nibble mode */
DECL|macro|IRQINV
mdefine_line|#define IRQINV&t;&t;0x08&t;/* turn off IRQ line inverter */
DECL|macro|IRQNML
mdefine_line|#define IRQNML&t;&t;0x00&t;/* turn on IRQ line inverter */
DECL|macro|INTON
mdefine_line|#define INTON&t;&t;0x04
DECL|macro|AUTOFFSET
mdefine_line|#define AUTOFFSET&t;0x02&t;/* auto shift address to TPR+12 */
DECL|macro|AUTOTX
mdefine_line|#define AUTOTX&t;&t;0x01&t;/* auto tx when leave RW mode */
multiline_comment|/* Transceiver Configuration Register */
DECL|macro|JABBER
mdefine_line|#define JABBER&t;&t;0x80&t;/* generate jabber condition */
DECL|macro|TXSUCINT
mdefine_line|#define TXSUCINT&t;0x40&t;/* enable tx success interrupt */
DECL|macro|T16INT
mdefine_line|#define T16INT&t;&t;0x20&t;/* enable T16 interrupt */
DECL|macro|RXERRPKT
mdefine_line|#define RXERRPKT&t;0x10&t;/* accept CRC error or short packet */
DECL|macro|EXTERNALB2
mdefine_line|#define EXTERNALB2&t;0x0C&t;/* external loopback 2 */
DECL|macro|EXTERNALB1
mdefine_line|#define EXTERNALB1&t;0x08&t;/* external loopback 1 */
DECL|macro|INTERNALB
mdefine_line|#define INTERNALB&t;0x04&t;/* internal loopback */
DECL|macro|NMLOPERATE
mdefine_line|#define NMLOPERATE&t;0x00&t;/* normal operation */
DECL|macro|RXPBM
mdefine_line|#define RXPBM&t;&t;0x03&t;/* rx physical, broadcast, multicast */
DECL|macro|RXPB
mdefine_line|#define RXPB&t;&t;0x02&t;/* rx physical, broadcast */
DECL|macro|RXALL
mdefine_line|#define RXALL&t;&t;0x01&t;/* rx all packet */
DECL|macro|RXOFF
mdefine_line|#define RXOFF&t;&t;0x00&t;/* rx disable */
eof
