multiline_comment|/* vi: ts=8 sw=8&n; *&n; * TI 3410/5052 USB Serial Driver Header&n; *&n; * Copyright (C) 2004 Texas Instruments&n; *&n; * This driver is based on the Linux io_ti driver, which is&n; *   Copyright (C) 2000-2002 Inside Out Networks&n; *   Copyright (C) 2001-2002 Greg Kroah-Hartman&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * For questions or problems with this driver, contact Texas Instruments&n; * technical support, or Al Borchers &lt;alborchers@steinerpoint.com&gt;, or&n; * Peter Berger &lt;pberger@brimson.com&gt;.&n; */
macro_line|#ifndef _TI_3410_5052_H_
DECL|macro|_TI_3410_5052_H_
mdefine_line|#define _TI_3410_5052_H_
multiline_comment|/* Configuration ids */
DECL|macro|TI_BOOT_CONFIG
mdefine_line|#define TI_BOOT_CONFIG&t;&t;&t;1
DECL|macro|TI_ACTIVE_CONFIG
mdefine_line|#define TI_ACTIVE_CONFIG&t;&t;2
multiline_comment|/* Vendor and product ids */
DECL|macro|TI_VENDOR_ID
mdefine_line|#define TI_VENDOR_ID&t;&t;&t;0x0451
DECL|macro|TI_3410_PRODUCT_ID
mdefine_line|#define TI_3410_PRODUCT_ID&t;&t;0x3410
DECL|macro|TI_5052_BOOT_PRODUCT_ID
mdefine_line|#define TI_5052_BOOT_PRODUCT_ID&t;&t;0x5052&t;/* no EEPROM, no firmware */
DECL|macro|TI_5152_BOOT_PRODUCT_ID
mdefine_line|#define TI_5152_BOOT_PRODUCT_ID&t;&t;0x5152&t;/* no EEPROM, no firmware */
DECL|macro|TI_5052_EEPROM_PRODUCT_ID
mdefine_line|#define TI_5052_EEPROM_PRODUCT_ID&t;0x505A&t;/* EEPROM, no firmware */
DECL|macro|TI_5052_FIRMWARE_PRODUCT_ID
mdefine_line|#define TI_5052_FIRMWARE_PRODUCT_ID&t;0x505F&t;/* firmware is running */
multiline_comment|/* Commands */
DECL|macro|TI_GET_VERSION
mdefine_line|#define TI_GET_VERSION&t;&t;&t;0x01
DECL|macro|TI_GET_PORT_STATUS
mdefine_line|#define TI_GET_PORT_STATUS&t;&t;0x02
DECL|macro|TI_GET_PORT_DEV_INFO
mdefine_line|#define TI_GET_PORT_DEV_INFO&t;&t;0x03
DECL|macro|TI_GET_CONFIG
mdefine_line|#define TI_GET_CONFIG&t;&t;&t;0x04
DECL|macro|TI_SET_CONFIG
mdefine_line|#define TI_SET_CONFIG&t;&t;&t;0x05
DECL|macro|TI_OPEN_PORT
mdefine_line|#define TI_OPEN_PORT&t;&t;&t;0x06
DECL|macro|TI_CLOSE_PORT
mdefine_line|#define TI_CLOSE_PORT&t;&t;&t;0x07
DECL|macro|TI_START_PORT
mdefine_line|#define TI_START_PORT&t;&t;&t;0x08
DECL|macro|TI_STOP_PORT
mdefine_line|#define TI_STOP_PORT&t;&t;&t;0x09
DECL|macro|TI_TEST_PORT
mdefine_line|#define TI_TEST_PORT&t;&t;&t;0x0A
DECL|macro|TI_PURGE_PORT
mdefine_line|#define TI_PURGE_PORT&t;&t;&t;0x0B
DECL|macro|TI_RESET_EXT_DEVICE
mdefine_line|#define TI_RESET_EXT_DEVICE&t;&t;0x0C
DECL|macro|TI_WRITE_DATA
mdefine_line|#define TI_WRITE_DATA&t;&t;&t;0x80
DECL|macro|TI_READ_DATA
mdefine_line|#define TI_READ_DATA&t;&t;&t;0x81
DECL|macro|TI_REQ_TYPE_CLASS
mdefine_line|#define TI_REQ_TYPE_CLASS&t;&t;0x82
multiline_comment|/* Module identifiers */
DECL|macro|TI_I2C_PORT
mdefine_line|#define TI_I2C_PORT&t;&t;&t;0x01
DECL|macro|TI_IEEE1284_PORT
mdefine_line|#define TI_IEEE1284_PORT&t;&t;0x02
DECL|macro|TI_UART1_PORT
mdefine_line|#define TI_UART1_PORT&t;&t;&t;0x03
DECL|macro|TI_UART2_PORT
mdefine_line|#define TI_UART2_PORT&t;&t;&t;0x04
DECL|macro|TI_RAM_PORT
mdefine_line|#define TI_RAM_PORT&t;&t;&t;0x05
multiline_comment|/* Modem status */
DECL|macro|TI_MSR_DELTA_CTS
mdefine_line|#define TI_MSR_DELTA_CTS&t;&t;0x01
DECL|macro|TI_MSR_DELTA_DSR
mdefine_line|#define TI_MSR_DELTA_DSR&t;&t;0x02
DECL|macro|TI_MSR_DELTA_RI
mdefine_line|#define TI_MSR_DELTA_RI&t;&t;&t;0x04
DECL|macro|TI_MSR_DELTA_CD
mdefine_line|#define TI_MSR_DELTA_CD&t;&t;&t;0x08
DECL|macro|TI_MSR_CTS
mdefine_line|#define TI_MSR_CTS&t;&t;&t;0x10
DECL|macro|TI_MSR_DSR
mdefine_line|#define TI_MSR_DSR&t;&t;&t;0x20
DECL|macro|TI_MSR_RI
mdefine_line|#define TI_MSR_RI&t;&t;&t;0x40
DECL|macro|TI_MSR_CD
mdefine_line|#define TI_MSR_CD&t;&t;&t;0x80
DECL|macro|TI_MSR_DELTA_MASK
mdefine_line|#define TI_MSR_DELTA_MASK&t;&t;0x0F
DECL|macro|TI_MSR_MASK
mdefine_line|#define TI_MSR_MASK&t;&t;&t;0xF0
multiline_comment|/* Line status */
DECL|macro|TI_LSR_OVERRUN_ERROR
mdefine_line|#define TI_LSR_OVERRUN_ERROR&t;&t;0x01
DECL|macro|TI_LSR_PARITY_ERROR
mdefine_line|#define TI_LSR_PARITY_ERROR&t;&t;0x02
DECL|macro|TI_LSR_FRAMING_ERROR
mdefine_line|#define TI_LSR_FRAMING_ERROR&t;&t;0x04
DECL|macro|TI_LSR_BREAK
mdefine_line|#define TI_LSR_BREAK&t;&t;&t;0x08
DECL|macro|TI_LSR_ERROR
mdefine_line|#define TI_LSR_ERROR&t;&t;&t;0x0F
DECL|macro|TI_LSR_RX_FULL
mdefine_line|#define TI_LSR_RX_FULL&t;&t;&t;0x10
DECL|macro|TI_LSR_TX_EMPTY
mdefine_line|#define TI_LSR_TX_EMPTY&t;&t;&t;0x20
multiline_comment|/* Line control */
DECL|macro|TI_LCR_BREAK
mdefine_line|#define TI_LCR_BREAK&t;&t;&t;0x40
multiline_comment|/* Modem control */
DECL|macro|TI_MCR_LOOP
mdefine_line|#define TI_MCR_LOOP&t;&t;&t;0x04
DECL|macro|TI_MCR_DTR
mdefine_line|#define TI_MCR_DTR&t;&t;&t;0x10
DECL|macro|TI_MCR_RTS
mdefine_line|#define TI_MCR_RTS&t;&t;&t;0x20
multiline_comment|/* Mask settings */
DECL|macro|TI_UART_ENABLE_RTS_IN
mdefine_line|#define TI_UART_ENABLE_RTS_IN&t;&t;0x0001
DECL|macro|TI_UART_DISABLE_RTS
mdefine_line|#define TI_UART_DISABLE_RTS&t;&t;0x0002
DECL|macro|TI_UART_ENABLE_PARITY_CHECKING
mdefine_line|#define TI_UART_ENABLE_PARITY_CHECKING&t;0x0008
DECL|macro|TI_UART_ENABLE_DSR_OUT
mdefine_line|#define TI_UART_ENABLE_DSR_OUT&t;&t;0x0010
DECL|macro|TI_UART_ENABLE_CTS_OUT
mdefine_line|#define TI_UART_ENABLE_CTS_OUT&t;&t;0x0020
DECL|macro|TI_UART_ENABLE_X_OUT
mdefine_line|#define TI_UART_ENABLE_X_OUT&t;&t;0x0040
DECL|macro|TI_UART_ENABLE_XA_OUT
mdefine_line|#define TI_UART_ENABLE_XA_OUT&t;&t;0x0080
DECL|macro|TI_UART_ENABLE_X_IN
mdefine_line|#define TI_UART_ENABLE_X_IN&t;&t;0x0100
DECL|macro|TI_UART_ENABLE_DTR_IN
mdefine_line|#define TI_UART_ENABLE_DTR_IN&t;&t;0x0800
DECL|macro|TI_UART_DISABLE_DTR
mdefine_line|#define TI_UART_DISABLE_DTR&t;&t;0x1000
DECL|macro|TI_UART_ENABLE_MS_INTS
mdefine_line|#define TI_UART_ENABLE_MS_INTS&t;&t;0x2000
DECL|macro|TI_UART_ENABLE_AUTO_START_DMA
mdefine_line|#define TI_UART_ENABLE_AUTO_START_DMA&t;0x4000
multiline_comment|/* Parity */
DECL|macro|TI_UART_NO_PARITY
mdefine_line|#define TI_UART_NO_PARITY&t;&t;0x00
DECL|macro|TI_UART_ODD_PARITY
mdefine_line|#define TI_UART_ODD_PARITY&t;&t;0x01
DECL|macro|TI_UART_EVEN_PARITY
mdefine_line|#define TI_UART_EVEN_PARITY&t;&t;0x02
DECL|macro|TI_UART_MARK_PARITY
mdefine_line|#define TI_UART_MARK_PARITY&t;&t;0x03
DECL|macro|TI_UART_SPACE_PARITY
mdefine_line|#define TI_UART_SPACE_PARITY&t;&t;0x04
multiline_comment|/* Stop bits */
DECL|macro|TI_UART_1_STOP_BITS
mdefine_line|#define TI_UART_1_STOP_BITS&t;&t;0x00
DECL|macro|TI_UART_1_5_STOP_BITS
mdefine_line|#define TI_UART_1_5_STOP_BITS&t;&t;0x01
DECL|macro|TI_UART_2_STOP_BITS
mdefine_line|#define TI_UART_2_STOP_BITS&t;&t;0x02
multiline_comment|/* Bits per character */
DECL|macro|TI_UART_5_DATA_BITS
mdefine_line|#define TI_UART_5_DATA_BITS&t;&t;0x00
DECL|macro|TI_UART_6_DATA_BITS
mdefine_line|#define TI_UART_6_DATA_BITS&t;&t;0x01
DECL|macro|TI_UART_7_DATA_BITS
mdefine_line|#define TI_UART_7_DATA_BITS&t;&t;0x02
DECL|macro|TI_UART_8_DATA_BITS
mdefine_line|#define TI_UART_8_DATA_BITS&t;&t;0x03
multiline_comment|/* 232/485 modes */
DECL|macro|TI_UART_232
mdefine_line|#define TI_UART_232&t;&t;&t;0x00
DECL|macro|TI_UART_485_RECEIVER_DISABLED
mdefine_line|#define TI_UART_485_RECEIVER_DISABLED&t;0x01
DECL|macro|TI_UART_485_RECEIVER_ENABLED
mdefine_line|#define TI_UART_485_RECEIVER_ENABLED&t;0x02
multiline_comment|/* Pipe transfer mode and timeout */
DECL|macro|TI_PIPE_MODE_CONTINOUS
mdefine_line|#define TI_PIPE_MODE_CONTINOUS&t;&t;0x01
DECL|macro|TI_PIPE_MODE_MASK
mdefine_line|#define TI_PIPE_MODE_MASK&t;&t;0x03
DECL|macro|TI_PIPE_TIMEOUT_MASK
mdefine_line|#define TI_PIPE_TIMEOUT_MASK&t;&t;0x7C
DECL|macro|TI_PIPE_TIMEOUT_ENABLE
mdefine_line|#define TI_PIPE_TIMEOUT_ENABLE&t;&t;0x80
multiline_comment|/* Config struct */
DECL|struct|ti_uart_config
r_struct
id|ti_uart_config
(brace
DECL|member|wBaudRate
id|__u16
id|wBaudRate
suffix:semicolon
DECL|member|wFlags
id|__u16
id|wFlags
suffix:semicolon
DECL|member|bDataBits
id|__u8
id|bDataBits
suffix:semicolon
DECL|member|bParity
id|__u8
id|bParity
suffix:semicolon
DECL|member|bStopBits
id|__u8
id|bStopBits
suffix:semicolon
DECL|member|cXon
r_char
id|cXon
suffix:semicolon
DECL|member|cXoff
r_char
id|cXoff
suffix:semicolon
DECL|member|bUartMode
id|__u8
id|bUartMode
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Get port status */
DECL|struct|ti_port_status
r_struct
id|ti_port_status
(brace
DECL|member|bCmdCode
id|__u8
id|bCmdCode
suffix:semicolon
DECL|member|bModuleId
id|__u8
id|bModuleId
suffix:semicolon
DECL|member|bErrorCode
id|__u8
id|bErrorCode
suffix:semicolon
DECL|member|bMSR
id|__u8
id|bMSR
suffix:semicolon
DECL|member|bLSR
id|__u8
id|bLSR
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Purge modes */
DECL|macro|TI_PURGE_OUTPUT
mdefine_line|#define TI_PURGE_OUTPUT&t;&t;&t;0x00
DECL|macro|TI_PURGE_INPUT
mdefine_line|#define TI_PURGE_INPUT&t;&t;&t;0x80
multiline_comment|/* Read/Write data */
DECL|macro|TI_RW_DATA_ADDR_SFR
mdefine_line|#define TI_RW_DATA_ADDR_SFR&t;&t;0x10
DECL|macro|TI_RW_DATA_ADDR_IDATA
mdefine_line|#define TI_RW_DATA_ADDR_IDATA&t;&t;0x20
DECL|macro|TI_RW_DATA_ADDR_XDATA
mdefine_line|#define TI_RW_DATA_ADDR_XDATA&t;&t;0x30
DECL|macro|TI_RW_DATA_ADDR_CODE
mdefine_line|#define TI_RW_DATA_ADDR_CODE&t;&t;0x40
DECL|macro|TI_RW_DATA_ADDR_GPIO
mdefine_line|#define TI_RW_DATA_ADDR_GPIO&t;&t;0x50
DECL|macro|TI_RW_DATA_ADDR_I2C
mdefine_line|#define TI_RW_DATA_ADDR_I2C&t;&t;0x60
DECL|macro|TI_RW_DATA_ADDR_FLASH
mdefine_line|#define TI_RW_DATA_ADDR_FLASH&t;&t;0x70
DECL|macro|TI_RW_DATA_ADDR_DSP
mdefine_line|#define TI_RW_DATA_ADDR_DSP&t;&t;0x80
DECL|macro|TI_RW_DATA_UNSPECIFIED
mdefine_line|#define TI_RW_DATA_UNSPECIFIED&t;&t;0x00
DECL|macro|TI_RW_DATA_BYTE
mdefine_line|#define TI_RW_DATA_BYTE&t;&t;&t;0x01
DECL|macro|TI_RW_DATA_WORD
mdefine_line|#define TI_RW_DATA_WORD&t;&t;&t;0x02
DECL|macro|TI_RW_DATA_DOUBLE_WORD
mdefine_line|#define TI_RW_DATA_DOUBLE_WORD&t;&t;0x04
DECL|struct|ti_write_data_bytes
r_struct
id|ti_write_data_bytes
(brace
DECL|member|bAddrType
id|__u8
id|bAddrType
suffix:semicolon
DECL|member|bDataType
id|__u8
id|bDataType
suffix:semicolon
DECL|member|bDataCounter
id|__u8
id|bDataCounter
suffix:semicolon
DECL|member|wBaseAddrHi
id|__be16
id|wBaseAddrHi
suffix:semicolon
DECL|member|wBaseAddrLo
id|__be16
id|wBaseAddrLo
suffix:semicolon
DECL|member|bData
id|__u8
id|bData
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|ti_read_data_request
r_struct
id|ti_read_data_request
(brace
DECL|member|bAddrType
id|__u8
id|bAddrType
suffix:semicolon
DECL|member|bDataType
id|__u8
id|bDataType
suffix:semicolon
DECL|member|bDataCounter
id|__u8
id|bDataCounter
suffix:semicolon
DECL|member|wBaseAddrHi
id|__be16
id|wBaseAddrHi
suffix:semicolon
DECL|member|wBaseAddrLo
id|__be16
id|wBaseAddrLo
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|ti_read_data_bytes
r_struct
id|ti_read_data_bytes
(brace
DECL|member|bCmdCode
id|__u8
id|bCmdCode
suffix:semicolon
DECL|member|bModuleId
id|__u8
id|bModuleId
suffix:semicolon
DECL|member|bErrorCode
id|__u8
id|bErrorCode
suffix:semicolon
DECL|member|bData
id|__u8
id|bData
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Interrupt struct */
DECL|struct|ti_interrupt
r_struct
id|ti_interrupt
(brace
DECL|member|bICode
id|__u8
id|bICode
suffix:semicolon
DECL|member|bIInfo
id|__u8
id|bIInfo
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Interrupt codes */
DECL|macro|TI_GET_PORT_FROM_CODE
mdefine_line|#define TI_GET_PORT_FROM_CODE(c)&t;(((c) &gt;&gt; 4) - 3)
DECL|macro|TI_GET_FUNC_FROM_CODE
mdefine_line|#define TI_GET_FUNC_FROM_CODE(c)&t;((c) &amp; 0x0f)
DECL|macro|TI_CODE_HARDWARE_ERROR
mdefine_line|#define TI_CODE_HARDWARE_ERROR&t;&t;0xFF
DECL|macro|TI_CODE_DATA_ERROR
mdefine_line|#define TI_CODE_DATA_ERROR&t;&t;0x03
DECL|macro|TI_CODE_MODEM_STATUS
mdefine_line|#define TI_CODE_MODEM_STATUS&t;&t;0x04
multiline_comment|/* Download firmware max packet size */
DECL|macro|TI_DOWNLOAD_MAX_PACKET_SIZE
mdefine_line|#define TI_DOWNLOAD_MAX_PACKET_SIZE&t;64
multiline_comment|/* Firmware image header */
DECL|struct|ti_firmware_header
r_struct
id|ti_firmware_header
(brace
DECL|member|wLength
id|__le16
id|wLength
suffix:semicolon
DECL|member|bCheckSum
id|__u8
id|bCheckSum
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* UART addresses */
DECL|macro|TI_UART1_BASE_ADDR
mdefine_line|#define TI_UART1_BASE_ADDR&t;&t;0xFFA0&t;/* UART 1 base address */
DECL|macro|TI_UART2_BASE_ADDR
mdefine_line|#define TI_UART2_BASE_ADDR&t;&t;0xFFB0&t;/* UART 2 base address */
DECL|macro|TI_UART_OFFSET_LCR
mdefine_line|#define TI_UART_OFFSET_LCR&t;&t;0x0002&t;/* UART MCR register offset */
DECL|macro|TI_UART_OFFSET_MCR
mdefine_line|#define TI_UART_OFFSET_MCR&t;&t;0x0004&t;/* UART MCR register offset */
macro_line|#endif /* _TI_3410_5052_H_ */
eof
