multiline_comment|/*****************************************************************************  &n; *&n; *&t;Copyright (C) 1997-2002 Inside Out Networks, Inc.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&n; *&t;Feb-16-2001&t;DMI&t;Added I2C structure definitions&n; *&t;May-29-2002&t;gkh&t;Ported to Linux&n; *&n; *&n; ******************************************************************************/
macro_line|#ifndef _IO_TI_H_
DECL|macro|_IO_TI_H_
mdefine_line|#define _IO_TI_H_
multiline_comment|/* Address Space */
DECL|macro|DTK_ADDR_SPACE_XDATA
mdefine_line|#define DTK_ADDR_SPACE_XDATA&t;&t;0x03&t;/* Addr is placed in XDATA space */
DECL|macro|DTK_ADDR_SPACE_I2C_TYPE_II
mdefine_line|#define DTK_ADDR_SPACE_I2C_TYPE_II&t;0x82&t;/* Addr is placed in I2C area */
DECL|macro|DTK_ADDR_SPACE_I2C_TYPE_III
mdefine_line|#define DTK_ADDR_SPACE_I2C_TYPE_III&t;0x83&t;/* Addr is placed in I2C area */
singleline_comment|// UART Defines
DECL|macro|UMPMEM_BASE_UART1
mdefine_line|#define UMPMEM_BASE_UART1&t;&t;0xFFA0  /* UMP UART1 base address          */
DECL|macro|UMPMEM_BASE_UART2
mdefine_line|#define UMPMEM_BASE_UART2&t;&t;0xFFB0  /* UMP UART2 base address          */
DECL|macro|UMPMEM_OFFS_UART_LSR
mdefine_line|#define UMPMEM_OFFS_UART_LSR&t;&t;0x05    /* UMP UART LSR register offset    */
multiline_comment|/* Bits per character */
DECL|macro|UMP_UART_CHAR5BITS
mdefine_line|#define UMP_UART_CHAR5BITS&t;&t;0x00
DECL|macro|UMP_UART_CHAR6BITS
mdefine_line|#define UMP_UART_CHAR6BITS&t;&t;0x01
DECL|macro|UMP_UART_CHAR7BITS
mdefine_line|#define UMP_UART_CHAR7BITS&t;&t;0x02
DECL|macro|UMP_UART_CHAR8BITS
mdefine_line|#define UMP_UART_CHAR8BITS&t;&t;0x03
multiline_comment|/* Parity */
DECL|macro|UMP_UART_NOPARITY
mdefine_line|#define UMP_UART_NOPARITY&t;&t;0x00
DECL|macro|UMP_UART_ODDPARITY
mdefine_line|#define UMP_UART_ODDPARITY&t;&t;0x01
DECL|macro|UMP_UART_EVENPARITY
mdefine_line|#define UMP_UART_EVENPARITY&t;&t;0x02
DECL|macro|UMP_UART_MARKPARITY
mdefine_line|#define UMP_UART_MARKPARITY&t;&t;0x03
DECL|macro|UMP_UART_SPACEPARITY
mdefine_line|#define UMP_UART_SPACEPARITY&t;&t;0x04
multiline_comment|/* Stop bits */
DECL|macro|UMP_UART_STOPBIT1
mdefine_line|#define UMP_UART_STOPBIT1&t;&t;0x00
DECL|macro|UMP_UART_STOPBIT15
mdefine_line|#define UMP_UART_STOPBIT15&t;&t;0x01
DECL|macro|UMP_UART_STOPBIT2
mdefine_line|#define UMP_UART_STOPBIT2&t;&t;0x02
multiline_comment|/* Line status register masks */
DECL|macro|UMP_UART_LSR_OV_MASK
mdefine_line|#define UMP_UART_LSR_OV_MASK&t;&t;0x01
DECL|macro|UMP_UART_LSR_PE_MASK
mdefine_line|#define UMP_UART_LSR_PE_MASK&t;&t;0x02
DECL|macro|UMP_UART_LSR_FE_MASK
mdefine_line|#define UMP_UART_LSR_FE_MASK&t;&t;0x04
DECL|macro|UMP_UART_LSR_BR_MASK
mdefine_line|#define UMP_UART_LSR_BR_MASK&t;&t;0x08
DECL|macro|UMP_UART_LSR_ER_MASK
mdefine_line|#define UMP_UART_LSR_ER_MASK&t;&t;0x0F
DECL|macro|UMP_UART_LSR_RX_MASK
mdefine_line|#define UMP_UART_LSR_RX_MASK&t;&t;0x10
DECL|macro|UMP_UART_LSR_TX_MASK
mdefine_line|#define UMP_UART_LSR_TX_MASK&t;&t;0x20
DECL|macro|UMP_UART_LSR_DATA_MASK
mdefine_line|#define UMP_UART_LSR_DATA_MASK&t;&t;( LSR_PAR_ERR | LSR_FRM_ERR | LSR_BREAK )
multiline_comment|/* Port Settings Constants) */
DECL|macro|UMP_MASK_UART_FLAGS_RTS_FLOW
mdefine_line|#define UMP_MASK_UART_FLAGS_RTS_FLOW&t;&t;0x0001
DECL|macro|UMP_MASK_UART_FLAGS_RTS_DISABLE
mdefine_line|#define UMP_MASK_UART_FLAGS_RTS_DISABLE&t;&t;0x0002
DECL|macro|UMP_MASK_UART_FLAGS_PARITY
mdefine_line|#define UMP_MASK_UART_FLAGS_PARITY&t;&t;0x0008
DECL|macro|UMP_MASK_UART_FLAGS_OUT_X_DSR_FLOW
mdefine_line|#define UMP_MASK_UART_FLAGS_OUT_X_DSR_FLOW&t;0x0010
DECL|macro|UMP_MASK_UART_FLAGS_OUT_X_CTS_FLOW
mdefine_line|#define UMP_MASK_UART_FLAGS_OUT_X_CTS_FLOW&t;0x0020
DECL|macro|UMP_MASK_UART_FLAGS_OUT_X
mdefine_line|#define UMP_MASK_UART_FLAGS_OUT_X&t;&t;0x0040
DECL|macro|UMP_MASK_UART_FLAGS_OUT_XA
mdefine_line|#define UMP_MASK_UART_FLAGS_OUT_XA&t;&t;0x0080
DECL|macro|UMP_MASK_UART_FLAGS_IN_X
mdefine_line|#define UMP_MASK_UART_FLAGS_IN_X&t;&t;0x0100
DECL|macro|UMP_MASK_UART_FLAGS_DTR_FLOW
mdefine_line|#define UMP_MASK_UART_FLAGS_DTR_FLOW&t;&t;0x0800
DECL|macro|UMP_MASK_UART_FLAGS_DTR_DISABLE
mdefine_line|#define UMP_MASK_UART_FLAGS_DTR_DISABLE&t;&t;0x1000
DECL|macro|UMP_MASK_UART_FLAGS_RECEIVE_MS_INT
mdefine_line|#define UMP_MASK_UART_FLAGS_RECEIVE_MS_INT&t;0x2000
DECL|macro|UMP_MASK_UART_FLAGS_AUTO_START_ON_ERR
mdefine_line|#define UMP_MASK_UART_FLAGS_AUTO_START_ON_ERR&t;0x4000
DECL|macro|UMP_DMA_MODE_CONTINOUS
mdefine_line|#define UMP_DMA_MODE_CONTINOUS&t;&t;&t;0x01
DECL|macro|UMP_PIPE_TRANS_TIMEOUT_ENA
mdefine_line|#define UMP_PIPE_TRANS_TIMEOUT_ENA&t;&t;0x80
DECL|macro|UMP_PIPE_TRANSFER_MODE_MASK
mdefine_line|#define UMP_PIPE_TRANSFER_MODE_MASK&t;&t;0x03
DECL|macro|UMP_PIPE_TRANS_TIMEOUT_MASK
mdefine_line|#define UMP_PIPE_TRANS_TIMEOUT_MASK&t;&t;0x7C
multiline_comment|/* Purge port Direction Mask Bits */
DECL|macro|UMP_PORT_DIR_OUT
mdefine_line|#define UMP_PORT_DIR_OUT&t;&t;&t;0x01
DECL|macro|UMP_PORT_DIR_IN
mdefine_line|#define UMP_PORT_DIR_IN&t;&t;&t;&t;0x02
singleline_comment|// Address of Port 0
DECL|macro|UMPM_UART1_PORT
mdefine_line|#define UMPM_UART1_PORT  &t;&t;&t;0x03
singleline_comment|// Commands
DECL|macro|UMPC_SET_CONFIG
mdefine_line|#define&t;UMPC_SET_CONFIG &t;&t;0x05
DECL|macro|UMPC_OPEN_PORT
mdefine_line|#define&t;UMPC_OPEN_PORT  &t;&t;0x06
DECL|macro|UMPC_CLOSE_PORT
mdefine_line|#define&t;UMPC_CLOSE_PORT &t;&t;0x07
DECL|macro|UMPC_START_PORT
mdefine_line|#define&t;UMPC_START_PORT &t;&t;0x08
DECL|macro|UMPC_STOP_PORT
mdefine_line|#define&t;UMPC_STOP_PORT  &t;&t;0x09
DECL|macro|UMPC_TEST_PORT
mdefine_line|#define&t;UMPC_TEST_PORT  &t;&t;0x0A
DECL|macro|UMPC_PURGE_PORT
mdefine_line|#define&t;UMPC_PURGE_PORT &t;&t;0x0B
DECL|macro|UMPC_COMPLETE_READ
mdefine_line|#define&t;UMPC_COMPLETE_READ&t;&t;0x80&t;
singleline_comment|// Force the Firmware to complete the current Read
DECL|macro|UMPC_HARDWARE_RESET
mdefine_line|#define&t;UMPC_HARDWARE_RESET&t;&t;0x81&t;
singleline_comment|// Force UMP back into BOOT Mode
DECL|macro|UMPC_COPY_DNLD_TO_I2C
mdefine_line|#define&t;UMPC_COPY_DNLD_TO_I2C&t;&t;0x82&t;
singleline_comment|// Copy current download image to type 0xf2 record in 16k I2C
singleline_comment|// firmware will change 0xff record to type 2 record when complete
singleline_comment|// Special function register commands
singleline_comment|// wIndex is register address
singleline_comment|// wValue is MSB/LSB mask/data
DECL|macro|UMPC_WRITE_SFR
mdefine_line|#define&t;UMPC_WRITE_SFR&t;  &t;&t;0x83&t;
singleline_comment|// Write SFR Register
singleline_comment|// wIndex is register address
DECL|macro|UMPC_READ_SFR
mdefine_line|#define&t;UMPC_READ_SFR&t;  &t;&t;0x84&t;
singleline_comment|// Read SRF Register
singleline_comment|// Set or Clear DTR (wValue bit 0 Set/Clear)&t;&t;wIndex ModuleID (port)
DECL|macro|UMPC_SET_CLR_DTR
mdefine_line|#define&t;UMPC_SET_CLR_DTR&t;&t;0x85
singleline_comment|// Set or Clear RTS (wValue bit 0 Set/Clear)&t;&t;wIndex ModuleID (port)
DECL|macro|UMPC_SET_CLR_RTS
mdefine_line|#define&t;UMPC_SET_CLR_RTS&t;&t;0x86
singleline_comment|// Set or Clear LOOPBACK (wValue bit 0 Set/Clear)&t;wIndex ModuleID (port)
DECL|macro|UMPC_SET_CLR_LOOPBACK
mdefine_line|#define&t;UMPC_SET_CLR_LOOPBACK&t;&t;0x87
singleline_comment|// Set or Clear BREAK (wValue bit 0 Set/Clear)&t;&t;wIndex ModuleID (port)
DECL|macro|UMPC_SET_CLR_BREAK
mdefine_line|#define&t;UMPC_SET_CLR_BREAK&t;&t;0x88
singleline_comment|// Read MSR wIndex ModuleID (port)
DECL|macro|UMPC_READ_MSR
mdefine_line|#define&t;UMPC_READ_MSR&t;&t;&t;0x89
multiline_comment|/* Toolkit commands */
multiline_comment|/* Read-write group */
DECL|macro|UMPC_MEMORY_READ
mdefine_line|#define&t;UMPC_MEMORY_READ   &t;&t;0x92
DECL|macro|UMPC_MEMORY_WRITE
mdefine_line|#define&t;UMPC_MEMORY_WRITE  &t;&t;0x93
multiline_comment|/*&n; *&t;UMP DMA Definitions&n; */
DECL|macro|UMPD_OEDB1_ADDRESS
mdefine_line|#define UMPD_OEDB1_ADDRESS&t;&t;0xFF08
DECL|macro|UMPD_OEDB2_ADDRESS
mdefine_line|#define UMPD_OEDB2_ADDRESS&t;&t;0xFF10
DECL|struct|out_endpoint_desc_block
r_struct
id|out_endpoint_desc_block
(brace
DECL|member|Configuration
id|__u8
id|Configuration
suffix:semicolon
DECL|member|XBufAddr
id|__u8
id|XBufAddr
suffix:semicolon
DECL|member|XByteCount
id|__u8
id|XByteCount
suffix:semicolon
DECL|member|Unused1
id|__u8
id|Unused1
suffix:semicolon
DECL|member|Unused2
id|__u8
id|Unused2
suffix:semicolon
DECL|member|YBufAddr
id|__u8
id|YBufAddr
suffix:semicolon
DECL|member|YByteCount
id|__u8
id|YByteCount
suffix:semicolon
DECL|member|BufferSize
id|__u8
id|BufferSize
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
multiline_comment|/*&n; * TYPE DEFINITIONS&n; * Structures for Firmware commands&n; */
DECL|struct|ump_uart_config
r_struct
id|ump_uart_config
multiline_comment|/* UART settings                    */
(brace
DECL|member|wBaudRate
id|__u16
id|wBaudRate
suffix:semicolon
multiline_comment|/* Baud rate                        */
DECL|member|wFlags
id|__u16
id|wFlags
suffix:semicolon
multiline_comment|/* Bitmap mask of flags             */
DECL|member|bDataBits
id|__u8
id|bDataBits
suffix:semicolon
multiline_comment|/* 5..8 - data bits per character   */
DECL|member|bParity
id|__u8
id|bParity
suffix:semicolon
multiline_comment|/* Parity settings                  */
DECL|member|bStopBits
id|__u8
id|bStopBits
suffix:semicolon
multiline_comment|/* Stop bits settings               */
DECL|member|cXon
r_char
id|cXon
suffix:semicolon
multiline_comment|/* XON character                    */
DECL|member|cXoff
r_char
id|cXoff
suffix:semicolon
multiline_comment|/* XOFF character                   */
DECL|member|bUartMode
id|__u8
id|bUartMode
suffix:semicolon
multiline_comment|/* Will be updated when a user      */
multiline_comment|/* interface is defined             */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * TYPE DEFINITIONS&n; * Structures for USB interrupts&n; */
DECL|struct|ump_interrupt
r_struct
id|ump_interrupt
multiline_comment|/* Interrupt packet structure       */
(brace
DECL|member|bICode
id|__u8
id|bICode
suffix:semicolon
multiline_comment|/* Interrupt code (interrupt num)   */
DECL|member|bIInfo
id|__u8
id|bIInfo
suffix:semicolon
multiline_comment|/* Interrupt information            */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|TIUMP_GET_PORT_FROM_CODE
mdefine_line|#define TIUMP_GET_PORT_FROM_CODE(c)&t;(((c) &gt;&gt; 4) - 3)
DECL|macro|TIUMP_GET_FUNC_FROM_CODE
mdefine_line|#define TIUMP_GET_FUNC_FROM_CODE(c)&t;((c) &amp; 0x0f)
DECL|macro|TIUMP_INTERRUPT_CODE_LSR
mdefine_line|#define TIUMP_INTERRUPT_CODE_LSR&t;0x03
DECL|macro|TIUMP_INTERRUPT_CODE_MSR
mdefine_line|#define TIUMP_INTERRUPT_CODE_MSR&t;0x04
macro_line|#endif
eof
