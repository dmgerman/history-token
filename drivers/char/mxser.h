macro_line|#ifndef _MXSER_H
DECL|macro|_MXSER_H
mdefine_line|#define _MXSER_H
multiline_comment|/*&n; *&t;Semi-public control interfaces&n; */
multiline_comment|/*&n; *&t;MOXA ioctls&n; */
DECL|macro|MOXA
mdefine_line|#define MOXA&t;&t;&t;0x400
DECL|macro|MOXA_GETDATACOUNT
mdefine_line|#define MOXA_GETDATACOUNT&t;(MOXA + 23)
DECL|macro|MOXA_GET_CONF
mdefine_line|#define&t;MOXA_GET_CONF&t;&t;(MOXA + 35)
DECL|macro|MOXA_DIAGNOSE
mdefine_line|#define MOXA_DIAGNOSE&t;&t;(MOXA + 50)
DECL|macro|MOXA_CHKPORTENABLE
mdefine_line|#define MOXA_CHKPORTENABLE&t;(MOXA + 60)
DECL|macro|MOXA_HighSpeedOn
mdefine_line|#define MOXA_HighSpeedOn&t;(MOXA + 61)
DECL|macro|MOXA_GET_MAJOR
mdefine_line|#define MOXA_GET_MAJOR&t;&t;(MOXA + 63)
DECL|macro|MOXA_GET_CUMAJOR
mdefine_line|#define MOXA_GET_CUMAJOR&t;(MOXA + 64)
DECL|macro|MOXA_GETMSTATUS
mdefine_line|#define MOXA_GETMSTATUS&t;&t;(MOXA + 65)
DECL|macro|MOXA_SET_OP_MODE
mdefine_line|#define MOXA_SET_OP_MODE&t;(MOXA + 66)
DECL|macro|MOXA_GET_OP_MODE
mdefine_line|#define MOXA_GET_OP_MODE&t;(MOXA + 67)
DECL|macro|RS232_MODE
mdefine_line|#define RS232_MODE&t;&t;0
DECL|macro|RS485_2WIRE_MODE
mdefine_line|#define RS485_2WIRE_MODE&t;1
DECL|macro|RS422_MODE
mdefine_line|#define RS422_MODE&t;&t;2
DECL|macro|RS485_4WIRE_MODE
mdefine_line|#define RS485_4WIRE_MODE&t;3
DECL|macro|OP_MODE_MASK
mdefine_line|#define OP_MODE_MASK&t;&t;3
singleline_comment|// above add by Victor Yu. 01-05-2004
DECL|macro|TTY_THRESHOLD_THROTTLE
mdefine_line|#define TTY_THRESHOLD_THROTTLE  128
DECL|macro|LO_WATER
mdefine_line|#define LO_WATER&t; &t;(TTY_FLIPBUF_SIZE)
DECL|macro|HI_WATER
mdefine_line|#define HI_WATER&t;&t;(TTY_FLIPBUF_SIZE*2*3/4)
singleline_comment|// added by James. 03-11-2004.
DECL|macro|MOXA_SDS_GETICOUNTER
mdefine_line|#define MOXA_SDS_GETICOUNTER  &t;(MOXA + 68)
DECL|macro|MOXA_SDS_RSTICOUNTER
mdefine_line|#define MOXA_SDS_RSTICOUNTER  &t;(MOXA + 69)
singleline_comment|// (above) added by James.
DECL|macro|MOXA_ASPP_OQUEUE
mdefine_line|#define MOXA_ASPP_OQUEUE  &t;(MOXA + 70)
DECL|macro|MOXA_ASPP_SETBAUD
mdefine_line|#define MOXA_ASPP_SETBAUD &t;(MOXA + 71)
DECL|macro|MOXA_ASPP_GETBAUD
mdefine_line|#define MOXA_ASPP_GETBAUD &t;(MOXA + 72)
DECL|macro|MOXA_ASPP_MON
mdefine_line|#define MOXA_ASPP_MON     &t;(MOXA + 73)
DECL|macro|MOXA_ASPP_LSTATUS
mdefine_line|#define MOXA_ASPP_LSTATUS &t;(MOXA + 74)
DECL|macro|MOXA_ASPP_MON_EXT
mdefine_line|#define MOXA_ASPP_MON_EXT &t;(MOXA + 75)
DECL|macro|MOXA_SET_BAUD_METHOD
mdefine_line|#define MOXA_SET_BAUD_METHOD&t;(MOXA + 76)
multiline_comment|/* --------------------------------------------------- */
DECL|macro|NPPI_NOTIFY_PARITY
mdefine_line|#define NPPI_NOTIFY_PARITY&t;0x01
DECL|macro|NPPI_NOTIFY_FRAMING
mdefine_line|#define NPPI_NOTIFY_FRAMING&t;0x02
DECL|macro|NPPI_NOTIFY_HW_OVERRUN
mdefine_line|#define NPPI_NOTIFY_HW_OVERRUN&t;0x04
DECL|macro|NPPI_NOTIFY_SW_OVERRUN
mdefine_line|#define NPPI_NOTIFY_SW_OVERRUN&t;0x08
DECL|macro|NPPI_NOTIFY_BREAK
mdefine_line|#define NPPI_NOTIFY_BREAK&t;0x10
DECL|macro|NPPI_NOTIFY_CTSHOLD
mdefine_line|#define NPPI_NOTIFY_CTSHOLD         0x01&t;
singleline_comment|// Tx hold by CTS low
DECL|macro|NPPI_NOTIFY_DSRHOLD
mdefine_line|#define NPPI_NOTIFY_DSRHOLD         0x02&t;
singleline_comment|// Tx hold by DSR low
DECL|macro|NPPI_NOTIFY_XOFFHOLD
mdefine_line|#define NPPI_NOTIFY_XOFFHOLD        0x08&t;
singleline_comment|// Tx hold by Xoff received
DECL|macro|NPPI_NOTIFY_XOFFXENT
mdefine_line|#define NPPI_NOTIFY_XOFFXENT        0x10&t;
singleline_comment|// Xoff Sent
singleline_comment|//CheckIsMoxaMust return value
DECL|macro|MOXA_OTHER_UART
mdefine_line|#define MOXA_OTHER_UART&t;&t;&t;0x00
DECL|macro|MOXA_MUST_MU150_HWID
mdefine_line|#define MOXA_MUST_MU150_HWID&t;&t;0x01
DECL|macro|MOXA_MUST_MU860_HWID
mdefine_line|#define MOXA_MUST_MU860_HWID&t;&t;0x02
singleline_comment|// follow just for Moxa Must chip define.
singleline_comment|//
singleline_comment|// when LCR register (offset 0x03) write following value,
singleline_comment|// the Must chip will enter enchance mode. And write value
singleline_comment|// on EFR (offset 0x02) bit 6,7 to change bank.
DECL|macro|MOXA_MUST_ENTER_ENCHANCE
mdefine_line|#define MOXA_MUST_ENTER_ENCHANCE&t;0xBF
singleline_comment|// when enhance mode enable, access on general bank register
DECL|macro|MOXA_MUST_GDL_REGISTER
mdefine_line|#define MOXA_MUST_GDL_REGISTER&t;&t;0x07
DECL|macro|MOXA_MUST_GDL_MASK
mdefine_line|#define MOXA_MUST_GDL_MASK&t;&t;0x7F
DECL|macro|MOXA_MUST_GDL_HAS_BAD_DATA
mdefine_line|#define MOXA_MUST_GDL_HAS_BAD_DATA&t;0x80
DECL|macro|MOXA_MUST_LSR_RERR
mdefine_line|#define MOXA_MUST_LSR_RERR&t;&t;0x80&t;
singleline_comment|// error in receive FIFO
singleline_comment|// enchance register bank select and enchance mode setting register
singleline_comment|// when LCR register equal to 0xBF
DECL|macro|MOXA_MUST_EFR_REGISTER
mdefine_line|#define MOXA_MUST_EFR_REGISTER&t;&t;0x02
singleline_comment|// enchance mode enable
DECL|macro|MOXA_MUST_EFR_EFRB_ENABLE
mdefine_line|#define MOXA_MUST_EFR_EFRB_ENABLE&t;0x10
singleline_comment|// enchance reister bank set 0, 1, 2
DECL|macro|MOXA_MUST_EFR_BANK0
mdefine_line|#define MOXA_MUST_EFR_BANK0&t;&t;0x00
DECL|macro|MOXA_MUST_EFR_BANK1
mdefine_line|#define MOXA_MUST_EFR_BANK1&t;&t;0x40
DECL|macro|MOXA_MUST_EFR_BANK2
mdefine_line|#define MOXA_MUST_EFR_BANK2&t;&t;0x80
DECL|macro|MOXA_MUST_EFR_BANK3
mdefine_line|#define MOXA_MUST_EFR_BANK3&t;&t;0xC0
DECL|macro|MOXA_MUST_EFR_BANK_MASK
mdefine_line|#define MOXA_MUST_EFR_BANK_MASK&t;&t;0xC0
singleline_comment|// set XON1 value register, when LCR=0xBF and change to bank0
DECL|macro|MOXA_MUST_XON1_REGISTER
mdefine_line|#define MOXA_MUST_XON1_REGISTER&t;&t;0x04
singleline_comment|// set XON2 value register, when LCR=0xBF and change to bank0
DECL|macro|MOXA_MUST_XON2_REGISTER
mdefine_line|#define MOXA_MUST_XON2_REGISTER&t;&t;0x05
singleline_comment|// set XOFF1 value register, when LCR=0xBF and change to bank0
DECL|macro|MOXA_MUST_XOFF1_REGISTER
mdefine_line|#define MOXA_MUST_XOFF1_REGISTER&t;0x06
singleline_comment|// set XOFF2 value register, when LCR=0xBF and change to bank0
DECL|macro|MOXA_MUST_XOFF2_REGISTER
mdefine_line|#define MOXA_MUST_XOFF2_REGISTER&t;0x07
DECL|macro|MOXA_MUST_RBRTL_REGISTER
mdefine_line|#define MOXA_MUST_RBRTL_REGISTER&t;0x04
DECL|macro|MOXA_MUST_RBRTH_REGISTER
mdefine_line|#define MOXA_MUST_RBRTH_REGISTER&t;0x05
DECL|macro|MOXA_MUST_RBRTI_REGISTER
mdefine_line|#define MOXA_MUST_RBRTI_REGISTER&t;0x06
DECL|macro|MOXA_MUST_THRTL_REGISTER
mdefine_line|#define MOXA_MUST_THRTL_REGISTER&t;0x07
DECL|macro|MOXA_MUST_ENUM_REGISTER
mdefine_line|#define MOXA_MUST_ENUM_REGISTER&t;&t;0x04
DECL|macro|MOXA_MUST_HWID_REGISTER
mdefine_line|#define MOXA_MUST_HWID_REGISTER&t;&t;0x05
DECL|macro|MOXA_MUST_ECR_REGISTER
mdefine_line|#define MOXA_MUST_ECR_REGISTER&t;&t;0x06
DECL|macro|MOXA_MUST_CSR_REGISTER
mdefine_line|#define MOXA_MUST_CSR_REGISTER&t;&t;0x07
singleline_comment|// good data mode enable
DECL|macro|MOXA_MUST_FCR_GDA_MODE_ENABLE
mdefine_line|#define MOXA_MUST_FCR_GDA_MODE_ENABLE&t;0x20
singleline_comment|// only good data put into RxFIFO
DECL|macro|MOXA_MUST_FCR_GDA_ONLY_ENABLE
mdefine_line|#define MOXA_MUST_FCR_GDA_ONLY_ENABLE&t;0x10
singleline_comment|// enable CTS interrupt
DECL|macro|MOXA_MUST_IER_ECTSI
mdefine_line|#define MOXA_MUST_IER_ECTSI&t;&t;0x80
singleline_comment|// eanble RTS interrupt
DECL|macro|MOXA_MUST_IER_ERTSI
mdefine_line|#define MOXA_MUST_IER_ERTSI&t;&t;0x40
singleline_comment|// enable Xon/Xoff interrupt
DECL|macro|MOXA_MUST_IER_XINT
mdefine_line|#define MOXA_MUST_IER_XINT&t;&t;0x20
singleline_comment|// enable GDA interrupt
DECL|macro|MOXA_MUST_IER_EGDAI
mdefine_line|#define MOXA_MUST_IER_EGDAI&t;&t;0x10
DECL|macro|MOXA_MUST_RECV_ISR
mdefine_line|#define MOXA_MUST_RECV_ISR&t;&t;(UART_IER_RDI | MOXA_MUST_IER_EGDAI)
singleline_comment|// GDA interrupt pending
DECL|macro|MOXA_MUST_IIR_GDA
mdefine_line|#define MOXA_MUST_IIR_GDA&t;&t;0x1C
DECL|macro|MOXA_MUST_IIR_RDA
mdefine_line|#define MOXA_MUST_IIR_RDA&t;&t;0x04
DECL|macro|MOXA_MUST_IIR_RTO
mdefine_line|#define MOXA_MUST_IIR_RTO&t;&t;0x0C
DECL|macro|MOXA_MUST_IIR_LSR
mdefine_line|#define MOXA_MUST_IIR_LSR&t;&t;0x06
singleline_comment|// recieved Xon/Xoff or specical interrupt pending
DECL|macro|MOXA_MUST_IIR_XSC
mdefine_line|#define MOXA_MUST_IIR_XSC&t;&t;0x10
singleline_comment|// RTS/CTS change state interrupt pending
DECL|macro|MOXA_MUST_IIR_RTSCTS
mdefine_line|#define MOXA_MUST_IIR_RTSCTS&t;&t;0x20
DECL|macro|MOXA_MUST_IIR_MASK
mdefine_line|#define MOXA_MUST_IIR_MASK&t;&t;0x3E
DECL|macro|MOXA_MUST_MCR_XON_FLAG
mdefine_line|#define MOXA_MUST_MCR_XON_FLAG&t;&t;0x40
DECL|macro|MOXA_MUST_MCR_XON_ANY
mdefine_line|#define MOXA_MUST_MCR_XON_ANY&t;&t;0x80
DECL|macro|MOXA_MUST_MCR_TX_XON
mdefine_line|#define MOXA_MUST_MCR_TX_XON&t;&t;0x08
singleline_comment|// software flow control on chip mask value
DECL|macro|MOXA_MUST_EFR_SF_MASK
mdefine_line|#define MOXA_MUST_EFR_SF_MASK&t;&t;0x0F
singleline_comment|// send Xon1/Xoff1
DECL|macro|MOXA_MUST_EFR_SF_TX1
mdefine_line|#define MOXA_MUST_EFR_SF_TX1&t;&t;0x08
singleline_comment|// send Xon2/Xoff2
DECL|macro|MOXA_MUST_EFR_SF_TX2
mdefine_line|#define MOXA_MUST_EFR_SF_TX2&t;&t;0x04
singleline_comment|// send Xon1,Xon2/Xoff1,Xoff2
DECL|macro|MOXA_MUST_EFR_SF_TX12
mdefine_line|#define MOXA_MUST_EFR_SF_TX12&t;&t;0x0C
singleline_comment|// don&squot;t send Xon/Xoff
DECL|macro|MOXA_MUST_EFR_SF_TX_NO
mdefine_line|#define MOXA_MUST_EFR_SF_TX_NO&t;&t;0x00
singleline_comment|// Tx software flow control mask
DECL|macro|MOXA_MUST_EFR_SF_TX_MASK
mdefine_line|#define MOXA_MUST_EFR_SF_TX_MASK&t;0x0C
singleline_comment|// don&squot;t receive Xon/Xoff
DECL|macro|MOXA_MUST_EFR_SF_RX_NO
mdefine_line|#define MOXA_MUST_EFR_SF_RX_NO&t;&t;0x00
singleline_comment|// receive Xon1/Xoff1
DECL|macro|MOXA_MUST_EFR_SF_RX1
mdefine_line|#define MOXA_MUST_EFR_SF_RX1&t;&t;0x02
singleline_comment|// receive Xon2/Xoff2
DECL|macro|MOXA_MUST_EFR_SF_RX2
mdefine_line|#define MOXA_MUST_EFR_SF_RX2&t;&t;0x01
singleline_comment|// receive Xon1,Xon2/Xoff1,Xoff2
DECL|macro|MOXA_MUST_EFR_SF_RX12
mdefine_line|#define MOXA_MUST_EFR_SF_RX12&t;&t;0x03
singleline_comment|// Rx software flow control mask
DECL|macro|MOXA_MUST_EFR_SF_RX_MASK
mdefine_line|#define MOXA_MUST_EFR_SF_RX_MASK&t;0x03
singleline_comment|//#define MOXA_MUST_MIN_XOFFLIMIT               66
singleline_comment|//#define MOXA_MUST_MIN_XONLIMIT                20
singleline_comment|//#define ID1_RX_TRIG                   120
DECL|macro|CHECK_MOXA_MUST_XOFFLIMIT
mdefine_line|#define CHECK_MOXA_MUST_XOFFLIMIT(info) { &t;&bslash;&n;&t;if ( (info)-&gt;IsMoxaMustChipFlag &amp;&amp; &t;&bslash;&n;&t; (info)-&gt;HandFlow.XoffLimit &lt; MOXA_MUST_MIN_XOFFLIMIT ) {&t;&bslash;&n;&t;&t;(info)-&gt;HandFlow.XoffLimit = MOXA_MUST_MIN_XOFFLIMIT;&t;&bslash;&n;&t;&t;(info)-&gt;HandFlow.XonLimit = MOXA_MUST_MIN_XONLIMIT;&t;&bslash;&n;&t;}&t;&bslash;&n;}
DECL|macro|ENABLE_MOXA_MUST_ENCHANCE_MODE
mdefine_line|#define ENABLE_MOXA_MUST_ENCHANCE_MODE(baseio) { &bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_EFRB_ENABLE;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|DISABLE_MOXA_MUST_ENCHANCE_MODE
mdefine_line|#define DISABLE_MOXA_MUST_ENCHANCE_MODE(baseio) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_EFRB_ENABLE;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_XON1_VALUE
mdefine_line|#define SET_MOXA_MUST_XON1_VALUE(baseio, Value) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK0;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb((u8)(Value), (baseio)+MOXA_MUST_XON1_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_XON2_VALUE
mdefine_line|#define SET_MOXA_MUST_XON2_VALUE(baseio, Value) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK0;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb((u8)(Value), (baseio)+MOXA_MUST_XON2_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_XOFF1_VALUE
mdefine_line|#define SET_MOXA_MUST_XOFF1_VALUE(baseio, Value) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK0;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb((u8)(Value), (baseio)+MOXA_MUST_XOFF1_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_XOFF2_VALUE
mdefine_line|#define SET_MOXA_MUST_XOFF2_VALUE(baseio, Value) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK0;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb((u8)(Value), (baseio)+MOXA_MUST_XOFF2_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_RBRTL_VALUE
mdefine_line|#define SET_MOXA_MUST_RBRTL_VALUE(baseio, Value) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK1;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb((u8)(Value), (baseio)+MOXA_MUST_RBRTL_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_RBRTH_VALUE
mdefine_line|#define SET_MOXA_MUST_RBRTH_VALUE(baseio, Value) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK1;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb((u8)(Value), (baseio)+MOXA_MUST_RBRTH_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_RBRTI_VALUE
mdefine_line|#define SET_MOXA_MUST_RBRTI_VALUE(baseio, Value) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK1;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb((u8)(Value), (baseio)+MOXA_MUST_RBRTI_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_THRTL_VALUE
mdefine_line|#define SET_MOXA_MUST_THRTL_VALUE(baseio, Value) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK1;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb((u8)(Value), (baseio)+MOXA_MUST_THRTL_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
singleline_comment|//#define MOXA_MUST_RBRL_VALUE  4
DECL|macro|SET_MOXA_MUST_FIFO_VALUE
mdefine_line|#define SET_MOXA_MUST_FIFO_VALUE(info) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((info)-&gt;base+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (info)-&gt;base+UART_LCR);&t;&bslash;&n;&t;__efr = inb((info)-&gt;base+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK1;&t;&bslash;&n;&t;outb(__efr, (info)-&gt;base+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb((u8)((info)-&gt;rx_high_water), (info)-&gt;base+MOXA_MUST_RBRTH_REGISTER);&t;&bslash;&n;&t;outb((u8)((info)-&gt;rx_trigger), (info)-&gt;base+MOXA_MUST_RBRTI_REGISTER);&t;&bslash;&n;&t;outb((u8)((info)-&gt;rx_low_water), (info)-&gt;base+MOXA_MUST_RBRTL_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (info)-&gt;base+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_ENUM_VALUE
mdefine_line|#define SET_MOXA_MUST_ENUM_VALUE(baseio, Value) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK2;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb((u8)(Value), (baseio)+MOXA_MUST_ENUM_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|GET_MOXA_MUST_HARDWARE_ID
mdefine_line|#define GET_MOXA_MUST_HARDWARE_ID(baseio, pId) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_BANK_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_BANK2;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;*pId = inb((baseio)+MOXA_MUST_HWID_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_NO_SOFTWARE_FLOW_CONTROL
mdefine_line|#define SET_MOXA_MUST_NO_SOFTWARE_FLOW_CONTROL(baseio) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_SF_MASK;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_JUST_TX_SOFTWARE_FLOW_CONTROL
mdefine_line|#define SET_MOXA_MUST_JUST_TX_SOFTWARE_FLOW_CONTROL(baseio) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_SF_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_SF_TX1;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|ENABLE_MOXA_MUST_TX_SOFTWARE_FLOW_CONTROL
mdefine_line|#define ENABLE_MOXA_MUST_TX_SOFTWARE_FLOW_CONTROL(baseio) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_SF_TX_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_SF_TX1;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|DISABLE_MOXA_MUST_TX_SOFTWARE_FLOW_CONTROL
mdefine_line|#define DISABLE_MOXA_MUST_TX_SOFTWARE_FLOW_CONTROL(baseio) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_SF_TX_MASK;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|SET_MOXA_MUST_JUST_RX_SOFTWARE_FLOW_CONTROL
mdefine_line|#define SET_MOXA_MUST_JUST_RX_SOFTWARE_FLOW_CONTROL(baseio) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_SF_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_SF_RX1;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|ENABLE_MOXA_MUST_RX_SOFTWARE_FLOW_CONTROL
mdefine_line|#define ENABLE_MOXA_MUST_RX_SOFTWARE_FLOW_CONTROL(baseio) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_SF_RX_MASK;&t;&bslash;&n;&t;__efr |= MOXA_MUST_EFR_SF_RX1;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|DISABLE_MOXA_MUST_RX_SOFTWARE_FLOW_CONTROL
mdefine_line|#define DISABLE_MOXA_MUST_RX_SOFTWARE_FLOW_CONTROL(baseio) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_SF_RX_MASK;&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|ENABLE_MOXA_MUST_TX_RX_SOFTWARE_FLOW_CONTROL
mdefine_line|#define ENABLE_MOXA_MUST_TX_RX_SOFTWARE_FLOW_CONTROL(baseio) {&t;&bslash;&n;&t;u8&t;__oldlcr, __efr;&t;&bslash;&n;&t;__oldlcr = inb((baseio)+UART_LCR);&t;&bslash;&n;&t;outb(MOXA_MUST_ENTER_ENCHANCE, (baseio)+UART_LCR);&t;&bslash;&n;&t;__efr = inb((baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;__efr &amp;= ~MOXA_MUST_EFR_SF_MASK;&t;&bslash;&n;&t;__efr |= (MOXA_MUST_EFR_SF_RX1|MOXA_MUST_EFR_SF_TX1);&t;&bslash;&n;&t;outb(__efr, (baseio)+MOXA_MUST_EFR_REGISTER);&t;&bslash;&n;&t;outb(__oldlcr, (baseio)+UART_LCR);&t;&bslash;&n;}
DECL|macro|ENABLE_MOXA_MUST_XON_ANY_FLOW_CONTROL
mdefine_line|#define ENABLE_MOXA_MUST_XON_ANY_FLOW_CONTROL(baseio) {&t;&bslash;&n;&t;u8&t;__oldmcr;&t;&bslash;&n;&t;__oldmcr = inb((baseio)+UART_MCR);&t;&bslash;&n;&t;__oldmcr |= MOXA_MUST_MCR_XON_ANY;&t;&bslash;&n;&t;outb(__oldmcr, (baseio)+UART_MCR);&t;&bslash;&n;}
DECL|macro|DISABLE_MOXA_MUST_XON_ANY_FLOW_CONTROL
mdefine_line|#define DISABLE_MOXA_MUST_XON_ANY_FLOW_CONTROL(baseio) {&t;&bslash;&n;&t;u8&t;__oldmcr;&t;&bslash;&n;&t;__oldmcr = inb((baseio)+UART_MCR);&t;&bslash;&n;&t;__oldmcr &amp;= ~MOXA_MUST_MCR_XON_ANY;&t;&bslash;&n;&t;outb(__oldmcr, (baseio)+UART_MCR);&t;&bslash;&n;}
DECL|macro|READ_MOXA_MUST_GDL
mdefine_line|#define READ_MOXA_MUST_GDL(baseio)&t;inb((baseio)+MOXA_MUST_GDL_REGISTER)
macro_line|#ifndef INIT_WORK
DECL|macro|INIT_WORK
mdefine_line|#define INIT_WORK(_work, _func, _data){&t;&bslash;&n;&t;_data-&gt;tqueue.routine = _func;&bslash;&n;&t;_data-&gt;tqueue.data = _data;&bslash;&n;&t;}
macro_line|#endif
macro_line|#endif
eof
