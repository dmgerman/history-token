multiline_comment|/*&n; * kgdb io functions for osprey.  We use the serial port on debug board.&n; *&n; * Copyright (C) 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
multiline_comment|/* ======================= CONFIG ======================== */
multiline_comment|/* [jsun] we use the second serial port for kdb */
DECL|macro|BASE
mdefine_line|#define         BASE                    0xb7fffff0
DECL|macro|MAX_BAUD
mdefine_line|#define         MAX_BAUD                115200
multiline_comment|/* distance in bytes between two serial registers */
DECL|macro|REG_OFFSET
mdefine_line|#define         REG_OFFSET              1
multiline_comment|/*&n; * 0 - kgdb does serial init&n; * 1 - kgdb skip serial init&n; */
DECL|variable|remoteDebugInitialized
r_static
r_int
id|remoteDebugInitialized
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n; * the default baud rate *if* kgdb does serial init&n; */
DECL|macro|BAUD_DEFAULT
mdefine_line|#define&t;&t;BAUD_DEFAULT&t;&t;UART16550_BAUD_38400
multiline_comment|/* ======================= END OF CONFIG ======================== */
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
multiline_comment|/* register offset */
DECL|macro|OFS_RCV_BUFFER
mdefine_line|#define         OFS_RCV_BUFFER          0
DECL|macro|OFS_TRANS_HOLD
mdefine_line|#define         OFS_TRANS_HOLD          0
DECL|macro|OFS_SEND_BUFFER
mdefine_line|#define         OFS_SEND_BUFFER         0
DECL|macro|OFS_INTR_ENABLE
mdefine_line|#define         OFS_INTR_ENABLE         (1*REG_OFFSET)
DECL|macro|OFS_INTR_ID
mdefine_line|#define         OFS_INTR_ID             (2*REG_OFFSET)
DECL|macro|OFS_DATA_FORMAT
mdefine_line|#define         OFS_DATA_FORMAT         (3*REG_OFFSET)
DECL|macro|OFS_LINE_CONTROL
mdefine_line|#define         OFS_LINE_CONTROL        (3*REG_OFFSET)
DECL|macro|OFS_MODEM_CONTROL
mdefine_line|#define         OFS_MODEM_CONTROL       (4*REG_OFFSET)
DECL|macro|OFS_RS232_OUTPUT
mdefine_line|#define         OFS_RS232_OUTPUT        (4*REG_OFFSET)
DECL|macro|OFS_LINE_STATUS
mdefine_line|#define         OFS_LINE_STATUS         (5*REG_OFFSET)
DECL|macro|OFS_MODEM_STATUS
mdefine_line|#define         OFS_MODEM_STATUS        (6*REG_OFFSET)
DECL|macro|OFS_RS232_INPUT
mdefine_line|#define         OFS_RS232_INPUT         (6*REG_OFFSET)
DECL|macro|OFS_SCRATCH_PAD
mdefine_line|#define         OFS_SCRATCH_PAD         (7*REG_OFFSET)
DECL|macro|OFS_DIVISOR_LSB
mdefine_line|#define         OFS_DIVISOR_LSB         (0*REG_OFFSET)
DECL|macro|OFS_DIVISOR_MSB
mdefine_line|#define         OFS_DIVISOR_MSB         (1*REG_OFFSET)
multiline_comment|/* memory-mapped read/write of the port */
DECL|macro|UART16550_READ
mdefine_line|#define         UART16550_READ(y)    (*((volatile uint8*)(BASE + y)))
DECL|macro|UART16550_WRITE
mdefine_line|#define         UART16550_WRITE(y, z)  ((*((volatile uint8*)(BASE + y))) = z)
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
multiline_comment|/* disable interrupts */
id|UART16550_WRITE
c_func
(paren
id|OFS_INTR_ENABLE
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* set up buad rate */
(brace
id|uint32
id|divisor
suffix:semicolon
multiline_comment|/* set DIAB bit */
id|UART16550_WRITE
c_func
(paren
id|OFS_LINE_CONTROL
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* set divisor */
id|divisor
op_assign
id|MAX_BAUD
op_div
id|baud
suffix:semicolon
id|UART16550_WRITE
c_func
(paren
id|OFS_DIVISOR_LSB
comma
id|divisor
op_amp
l_int|0xff
)paren
suffix:semicolon
id|UART16550_WRITE
c_func
(paren
id|OFS_DIVISOR_MSB
comma
(paren
id|divisor
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* clear DIAB bit */
id|UART16550_WRITE
c_func
(paren
id|OFS_LINE_CONTROL
comma
l_int|0x0
)paren
suffix:semicolon
)brace
multiline_comment|/* set data format */
id|UART16550_WRITE
c_func
(paren
id|OFS_DATA_FORMAT
comma
id|data
op_or
id|parity
op_or
id|stop
)paren
suffix:semicolon
)brace
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
id|BAUD_DEFAULT
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
id|OFS_LINE_STATUS
)paren
op_amp
l_int|0x1
)paren
op_eq
l_int|0
)paren
suffix:semicolon
r_return
id|UART16550_READ
c_func
(paren
id|OFS_RCV_BUFFER
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
id|BAUD_DEFAULT
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
id|OFS_LINE_STATUS
)paren
op_amp
l_int|0x20
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|UART16550_WRITE
c_func
(paren
id|OFS_SEND_BUFFER
comma
id|byte
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
