macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/au1000.h&gt;
macro_line|#ifdef CONFIG_REMOTE_DEBUG
multiline_comment|/*&n; * FIXME the user should be able to select the&n; * uart to be used for debugging.&n; */
DECL|macro|DEBUG_BASE
mdefine_line|#define&t;DEBUG_BASE  UART2_ADDR
multiline_comment|/**/
multiline_comment|/* we need uint32 uint8 */
multiline_comment|/* #include &quot;types.h&quot; */
DECL|typedef|uint8
r_typedef
r_int
r_char
id|uint8
suffix:semicolon
DECL|typedef|uint32
r_typedef
r_int
r_int
id|uint32
suffix:semicolon
DECL|macro|UART16550_BAUD_2400
mdefine_line|#define         UART16550_BAUD_2400             2400
DECL|macro|UART16550_BAUD_4800
mdefine_line|#define         UART16550_BAUD_4800             4800
DECL|macro|UART16550_BAUD_9600
mdefine_line|#define         UART16550_BAUD_9600             9600
DECL|macro|UART16550_BAUD_19200
mdefine_line|#define         UART16550_BAUD_19200            19200
DECL|macro|UART16550_BAUD_38400
mdefine_line|#define         UART16550_BAUD_38400            38400
DECL|macro|UART16550_BAUD_57600
mdefine_line|#define         UART16550_BAUD_57600            57600
DECL|macro|UART16550_BAUD_115200
mdefine_line|#define         UART16550_BAUD_115200           115200
DECL|macro|UART16550_PARITY_NONE
mdefine_line|#define         UART16550_PARITY_NONE           0
DECL|macro|UART16550_PARITY_ODD
mdefine_line|#define         UART16550_PARITY_ODD            0x08
DECL|macro|UART16550_PARITY_EVEN
mdefine_line|#define         UART16550_PARITY_EVEN           0x18
DECL|macro|UART16550_PARITY_MARK
mdefine_line|#define         UART16550_PARITY_MARK           0x28
DECL|macro|UART16550_PARITY_SPACE
mdefine_line|#define         UART16550_PARITY_SPACE          0x38
DECL|macro|UART16550_DATA_5BIT
mdefine_line|#define         UART16550_DATA_5BIT             0x0
DECL|macro|UART16550_DATA_6BIT
mdefine_line|#define         UART16550_DATA_6BIT             0x1
DECL|macro|UART16550_DATA_7BIT
mdefine_line|#define         UART16550_DATA_7BIT             0x2
DECL|macro|UART16550_DATA_8BIT
mdefine_line|#define         UART16550_DATA_8BIT             0x3
DECL|macro|UART16550_STOP_1BIT
mdefine_line|#define         UART16550_STOP_1BIT             0x0
DECL|macro|UART16550_STOP_2BIT
mdefine_line|#define         UART16550_STOP_2BIT             0x4
DECL|macro|UART_RX
mdefine_line|#define UART_RX&t;&t;0&t;/* Receive buffer */
DECL|macro|UART_TX
mdefine_line|#define UART_TX&t;&t;4&t;/* Transmit buffer */
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;8&t;/* Interrupt Enable Register */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;0xC&t;/* Interrupt ID Register */
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;0x10&t;/* FIFO Control Register */
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;0x14&t;/* Line Control Register */
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;0x18&t;/* Modem Control Register */
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;0x1C&t;/* Line Status Register */
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;0x20&t;/* Modem Status Register */
DECL|macro|UART_CLK
mdefine_line|#define UART_CLK&t;0x28&t;/* Baud Rat4e Clock Divider */
DECL|macro|UART_MOD_CNTRL
mdefine_line|#define UART_MOD_CNTRL&t;0x100&t;/* Module Control */
multiline_comment|/* memory-mapped read/write of the port */
DECL|macro|UART16550_READ
mdefine_line|#define UART16550_READ(y)    (inl(DEBUG_BASE + y) &amp; 0xff)
DECL|macro|UART16550_WRITE
mdefine_line|#define UART16550_WRITE(y,z) (outl(z&amp;0xff, DEBUG_BASE + y))
DECL|function|debugInit
r_void
id|debugInit
c_func
(paren
id|uint32
id|baud
comma
id|uint8
id|data
comma
id|uint8
id|parity
comma
id|uint8
id|stop
)paren
(brace
r_if
c_cond
(paren
id|UART16550_READ
c_func
(paren
id|UART_MOD_CNTRL
)paren
op_ne
l_int|0x3
)paren
(brace
id|UART16550_WRITE
c_func
(paren
id|UART_MOD_CNTRL
comma
l_int|3
)paren
suffix:semicolon
)brace
id|cal_r4koff
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* disable interrupts */
id|UART16550_WRITE
c_func
(paren
id|UART_IER
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* set up baud rate */
(brace
id|uint32
id|divisor
suffix:semicolon
multiline_comment|/* set divisor */
id|divisor
op_assign
id|get_au1000_uart_baud
c_func
(paren
)paren
op_div
id|baud
suffix:semicolon
id|UART16550_WRITE
c_func
(paren
id|UART_CLK
comma
id|divisor
op_amp
l_int|0xffff
)paren
suffix:semicolon
)brace
multiline_comment|/* set data format */
id|UART16550_WRITE
c_func
(paren
id|UART_LCR
comma
id|data
op_or
id|parity
op_or
id|stop
)paren
suffix:semicolon
)brace
DECL|variable|remoteDebugInitialized
r_static
r_int
id|remoteDebugInitialized
op_assign
l_int|0
suffix:semicolon
DECL|function|getDebugChar
id|uint8
id|getDebugChar
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|remoteDebugInitialized
)paren
(brace
id|remoteDebugInitialized
op_assign
l_int|1
suffix:semicolon
id|debugInit
c_func
(paren
id|UART16550_BAUD_115200
comma
id|UART16550_DATA_8BIT
comma
id|UART16550_PARITY_NONE
comma
id|UART16550_STOP_1BIT
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|UART16550_READ
c_func
(paren
id|UART_LSR
)paren
op_amp
l_int|0x1
)paren
op_eq
l_int|0
)paren
(brace
suffix:semicolon
)brace
r_return
id|UART16550_READ
c_func
(paren
id|UART_RX
)paren
suffix:semicolon
)brace
DECL|function|putDebugChar
r_int
id|putDebugChar
c_func
(paren
id|uint8
id|byte
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remoteDebugInitialized
)paren
(brace
id|remoteDebugInitialized
op_assign
l_int|1
suffix:semicolon
id|debugInit
c_func
(paren
id|UART16550_BAUD_115200
comma
id|UART16550_DATA_8BIT
comma
id|UART16550_PARITY_NONE
comma
id|UART16550_STOP_1BIT
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|UART16550_READ
c_func
(paren
id|UART_LSR
)paren
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|UART16550_WRITE
c_func
(paren
id|UART_TX
comma
id|byte
)paren
suffix:semicolon
singleline_comment|//for (i=0;i&lt;0xfff;i++);
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
eof
