multiline_comment|/*&n; * Copyright (C) 2004 Patrick Boettcher &lt;patrick.boettcher@desy.de&gt;,&n; *                    Luca Bertagnolio &lt;&gt;,&n; *&n; * based on information provided by John Jurrius from BBTI, Inc.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &quot;dmxdev.h&quot;
macro_line|#include &quot;dvb_demux.h&quot;
macro_line|#include &quot;dvb_filter.h&quot;
macro_line|#include &quot;dvb_net.h&quot;
macro_line|#include &quot;dvb_frontend.h&quot;
multiline_comment|/* debug */
DECL|macro|dprintk
mdefine_line|#define dprintk(level,args...) &bslash;&n;&t;    do { if ((debug &amp; level)) { printk(args); } } while (0)
DECL|macro|debug_dump
mdefine_line|#define debug_dump(b,l) if (debug) {&bslash;&n;&t;int i; deb_xfer(&quot;%s: %d &gt; &quot;,__FUNCTION__,l); &bslash;&n;&t;for (i = 0; i &lt; l; i++) deb_xfer(&quot;%02x &quot;, b[i]); &bslash;&n;&t;deb_xfer(&quot;&bslash;n&quot;);&bslash;&n;}
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_int
comma
l_int|0x644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;set debugging level (1=info,ts=2,ctrl=4 (or-able)).&quot;
)paren
suffix:semicolon
DECL|macro|deb_info
mdefine_line|#define deb_info(args...) dprintk(0x01,args)
DECL|macro|deb_ts
mdefine_line|#define deb_ts(args...)   dprintk(0x02,args)
DECL|macro|deb_ctrl
mdefine_line|#define deb_ctrl(args...) dprintk(0x04,args)
multiline_comment|/* Version information */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;0.0&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;Driver for B2C2/Technisat Air/Cable/Sky-2-PC USB devices&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Patrick Boettcher, patrick.boettcher@desy.de&quot;
multiline_comment|/* transfer parameters */
DECL|macro|B2C2_USB_FRAMES_PER_ISO
mdefine_line|#define B2C2_USB_FRAMES_PER_ISO&t;&t;4
DECL|macro|B2C2_USB_NUM_ISO_URB
mdefine_line|#define B2C2_USB_NUM_ISO_URB&t;&t;4    /* TODO check out a good value */
DECL|macro|B2C2_USB_CTRL_PIPE_IN
mdefine_line|#define B2C2_USB_CTRL_PIPE_IN&t;&t;usb_rcvctrlpipe(b2c2-&gt;udev,0)
DECL|macro|B2C2_USB_CTRL_PIPE_OUT
mdefine_line|#define B2C2_USB_CTRL_PIPE_OUT&t;&t;usb_sndctrlpipe(b2c2-&gt;udev,0)
DECL|macro|B2C2_USB_DATA_PIPE
mdefine_line|#define B2C2_USB_DATA_PIPE&t;&t;&t;usb_rcvisocpipe(b2c2-&gt;udev,0x81)
DECL|struct|usb_b2c2_usb
r_struct
id|usb_b2c2_usb
(brace
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|uintf
r_struct
id|usb_interface
op_star
id|uintf
suffix:semicolon
DECL|member|iso_buffer
id|u8
op_star
id|iso_buffer
suffix:semicolon
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
DECL|member|iso_dma_handle
id|dma_addr_t
id|iso_dma_handle
suffix:semicolon
DECL|member|iso_urb
r_struct
id|urb
op_star
id|iso_urb
(braket
id|B2C2_USB_NUM_ISO_URB
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * USB&n; * 10 90 34 12 78 56 04 00&n; * usb_control_msg(udev, usb_sndctrlpipe(udev,0),&n; * 0x90,&n; * 0x10,&n; * 0x1234,&n; * 0x5678,&n; * buf,&n; * 4,&n; * 5*HZ);&n; *&n; * extern int usb_control_msg(struct usb_device *dev, unsigned int pipe,&n; * __u8 request,&n; * __u8 requesttype,&n; * __u16 value,&n; * __u16 index,&n; * void *data,&n; * __u16 size,&n; * int timeout);&n; *&n; */
multiline_comment|/* request types */
r_typedef
r_enum
(brace
DECL|enumerator|RTYPE_READ_DW
id|RTYPE_READ_DW
op_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
DECL|enumerator|RTYPE_WRITE_DW_1
id|RTYPE_WRITE_DW_1
op_assign
(paren
l_int|3
op_lshift
l_int|6
)paren
comma
DECL|enumerator|RTYPE_READ_V8_MEMORY
id|RTYPE_READ_V8_MEMORY
op_assign
(paren
l_int|6
op_lshift
l_int|6
)paren
comma
DECL|enumerator|RTYPE_WRITE_V8_MEMORY
id|RTYPE_WRITE_V8_MEMORY
op_assign
(paren
l_int|7
op_lshift
l_int|6
)paren
comma
DECL|enumerator|RTYPE_WRITE_V8_FLASH
id|RTYPE_WRITE_V8_FLASH
op_assign
(paren
l_int|8
op_lshift
l_int|6
)paren
comma
DECL|enumerator|RTYPE_GENERIC
id|RTYPE_GENERIC
op_assign
(paren
l_int|9
op_lshift
l_int|6
)paren
comma
DECL|typedef|b2c2_usb_request_type_t
)brace
id|b2c2_usb_request_type_t
suffix:semicolon
multiline_comment|/* request */
r_typedef
r_enum
(brace
DECL|enumerator|B2C2_USB_WRITE_V8_MEM
id|B2C2_USB_WRITE_V8_MEM
op_assign
l_int|0x04
comma
DECL|enumerator|B2C2_USB_READ_V8_MEM
id|B2C2_USB_READ_V8_MEM
op_assign
l_int|0x05
comma
DECL|enumerator|B2C2_USB_READ_REG
id|B2C2_USB_READ_REG
op_assign
l_int|0x08
comma
DECL|enumerator|B2C2_USB_WRITE_REG
id|B2C2_USB_WRITE_REG
op_assign
l_int|0x0A
comma
multiline_comment|/*&t;B2C2_USB_WRITEREGLO   = 0x0A, */
DECL|enumerator|B2C2_USB_WRITEREGHI
id|B2C2_USB_WRITEREGHI
op_assign
l_int|0x0B
comma
DECL|enumerator|B2C2_USB_FLASH_BLOCK
id|B2C2_USB_FLASH_BLOCK
op_assign
l_int|0x10
comma
DECL|enumerator|B2C2_USB_I2C_REQUEST
id|B2C2_USB_I2C_REQUEST
op_assign
l_int|0x11
comma
DECL|enumerator|B2C2_USB_UTILITY
id|B2C2_USB_UTILITY
op_assign
l_int|0x12
comma
DECL|typedef|b2c2_usb_request_t
)brace
id|b2c2_usb_request_t
suffix:semicolon
multiline_comment|/* function definition for I2C_REQUEST */
r_typedef
r_enum
(brace
DECL|enumerator|USB_FUNC_I2C_WRITE
id|USB_FUNC_I2C_WRITE
op_assign
l_int|0x01
comma
DECL|enumerator|USB_FUNC_I2C_MULTIWRITE
id|USB_FUNC_I2C_MULTIWRITE
op_assign
l_int|0x02
comma
DECL|enumerator|USB_FUNC_I2C_READ
id|USB_FUNC_I2C_READ
op_assign
l_int|0x03
comma
DECL|enumerator|USB_FUNC_I2C_REPEATWRITE
id|USB_FUNC_I2C_REPEATWRITE
op_assign
l_int|0x04
comma
DECL|enumerator|USB_FUNC_GET_DESCRIPTOR
id|USB_FUNC_GET_DESCRIPTOR
op_assign
l_int|0x05
comma
DECL|enumerator|USB_FUNC_I2C_REPEATREAD
id|USB_FUNC_I2C_REPEATREAD
op_assign
l_int|0x06
comma
multiline_comment|/* DKT 020208 - add this to support special case of DiSEqC */
DECL|enumerator|USB_FUNC_I2C_CHECKWRITE
id|USB_FUNC_I2C_CHECKWRITE
op_assign
l_int|0x07
comma
DECL|enumerator|USB_FUNC_I2C_CHECKRESULT
id|USB_FUNC_I2C_CHECKRESULT
op_assign
l_int|0x08
comma
DECL|typedef|b2c2_usb_i2c_function_t
)brace
id|b2c2_usb_i2c_function_t
suffix:semicolon
multiline_comment|/*&n; * function definition for UTILITY request 0x12&n; * DKT 020304 - new utility function&n; */
r_typedef
r_enum
(brace
DECL|enumerator|UTILITY_SET_FILTER
id|UTILITY_SET_FILTER
op_assign
l_int|0x01
comma
DECL|enumerator|UTILITY_DATA_ENABLE
id|UTILITY_DATA_ENABLE
op_assign
l_int|0x02
comma
DECL|enumerator|UTILITY_FLEX_MULTIWRITE
id|UTILITY_FLEX_MULTIWRITE
op_assign
l_int|0x03
comma
DECL|enumerator|UTILITY_SET_BUFFER_SIZE
id|UTILITY_SET_BUFFER_SIZE
op_assign
l_int|0x04
comma
DECL|enumerator|UTILITY_FLEX_OPERATOR
id|UTILITY_FLEX_OPERATOR
op_assign
l_int|0x05
comma
DECL|enumerator|UTILITY_FLEX_RESET300_START
id|UTILITY_FLEX_RESET300_START
op_assign
l_int|0x06
comma
DECL|enumerator|UTILITY_FLEX_RESET300_STOP
id|UTILITY_FLEX_RESET300_STOP
op_assign
l_int|0x07
comma
DECL|enumerator|UTILITY_FLEX_RESET300
id|UTILITY_FLEX_RESET300
op_assign
l_int|0x08
comma
DECL|enumerator|UTILITY_SET_ISO_SIZE
id|UTILITY_SET_ISO_SIZE
op_assign
l_int|0x09
comma
DECL|enumerator|UTILITY_DATA_RESET
id|UTILITY_DATA_RESET
op_assign
l_int|0x0A
comma
DECL|enumerator|UTILITY_GET_DATA_STATUS
id|UTILITY_GET_DATA_STATUS
op_assign
l_int|0x10
comma
DECL|enumerator|UTILITY_GET_V8_REG
id|UTILITY_GET_V8_REG
op_assign
l_int|0x11
comma
multiline_comment|/* DKT 020326 - add function for v1.14 */
DECL|enumerator|UTILITY_SRAM_WRITE
id|UTILITY_SRAM_WRITE
op_assign
l_int|0x12
comma
DECL|enumerator|UTILITY_SRAM_READ
id|UTILITY_SRAM_READ
op_assign
l_int|0x13
comma
DECL|enumerator|UTILITY_SRAM_TESTFILL
id|UTILITY_SRAM_TESTFILL
op_assign
l_int|0x14
comma
DECL|enumerator|UTILITY_SRAM_TESTSET
id|UTILITY_SRAM_TESTSET
op_assign
l_int|0x15
comma
DECL|enumerator|UTILITY_SRAM_TESTVERIFY
id|UTILITY_SRAM_TESTVERIFY
op_assign
l_int|0x16
comma
DECL|typedef|b2c2_usb_utility_function_t
)brace
id|b2c2_usb_utility_function_t
suffix:semicolon
DECL|macro|B2C2_WAIT_FOR_OPERATION_RW
mdefine_line|#define B2C2_WAIT_FOR_OPERATION_RW  1  
singleline_comment|// 1 s
DECL|macro|B2C2_WAIT_FOR_OPERATION_RDW
mdefine_line|#define B2C2_WAIT_FOR_OPERATION_RDW 3  
singleline_comment|// 3 s
DECL|macro|B2C2_WAIT_FOR_OPERATION_WDW
mdefine_line|#define B2C2_WAIT_FOR_OPERATION_WDW 1  
singleline_comment|// 1 s
DECL|macro|B2C2_WAIT_FOR_OPERATION_V8READ
mdefine_line|#define B2C2_WAIT_FOR_OPERATION_V8READ   3  
singleline_comment|// 3 s
DECL|macro|B2C2_WAIT_FOR_OPERATION_V8WRITE
mdefine_line|#define B2C2_WAIT_FOR_OPERATION_V8WRITE  3  
singleline_comment|// 3 s
DECL|macro|B2C2_WAIT_FOR_OPERATION_V8FLASH
mdefine_line|#define B2C2_WAIT_FOR_OPERATION_V8FLASH  3  
singleline_comment|// 3 s
multiline_comment|/* JLP 111700: we will include the 1 bit gap between the upper and lower 3 bits&n; * in the IBI address, to make the V8 code simpler.&n; * PCI ADDRESS FORMAT: 0x71C -&gt; 0000 0111 0001 1100 (these are the six bits used)&n; *                  in general: 0000 0HHH 000L LL00&n; * IBI ADDRESS FORMAT:                    RHHH BLLL&n; *&n; * where R is the read(1)/write(0) bit, B is the busy bit&n; * and HHH and LLL are the two sets of three bits from the PCI address.&n; */
DECL|macro|B2C2_FLEX_PCIOFFSET_TO_INTERNALADDR
mdefine_line|#define B2C2_FLEX_PCIOFFSET_TO_INTERNALADDR(usPCI) (u8) (((usPCI &gt;&gt; 2) &amp; 0x07) + ((usPCI &gt;&gt; 4) &amp; 0x70))
DECL|macro|B2C2_FLEX_INTERNALADDR_TO_PCIOFFSET
mdefine_line|#define B2C2_FLEX_INTERNALADDR_TO_PCIOFFSET(ucAddr) (u16) (((ucAddr &amp; 0x07) &lt;&lt; 2) + ((ucAddr &amp; 0x70) &lt;&lt; 4))
multiline_comment|/*&n; * DKT 020228 - forget about this VENDOR_BUFFER_SIZE, read and write register&n; * deal with DWORD or 4 bytes, that should be should from now on&n; */
DECL|function|b2c2_usb_read_dw
r_static
id|u32
id|b2c2_usb_read_dw
c_func
(paren
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
comma
id|u16
id|wRegOffsPCI
)paren
(brace
id|u32
id|val
suffix:semicolon
id|u16
id|wAddress
op_assign
id|B2C2_FLEX_PCIOFFSET_TO_INTERNALADDR
c_func
(paren
id|wRegOffsPCI
)paren
op_or
l_int|0x0080
suffix:semicolon
r_int
id|len
op_assign
id|usb_control_msg
c_func
(paren
id|b2c2-&gt;udev
comma
id|B2C2_USB_CTRL_PIPE_IN
comma
id|B2C2_USB_READ_REG
comma
id|RTYPE_READ_DW
comma
id|wAddress
comma
l_int|0
comma
op_amp
id|val
comma
r_sizeof
(paren
id|u32
)paren
comma
id|B2C2_WAIT_FOR_OPERATION_RDW
op_star
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
r_sizeof
(paren
id|u32
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;error while reading dword from %d (%d).&quot;
comma
id|wAddress
comma
id|wRegOffsPCI
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * DKT 020228 - from now on, we don&squot;t support anything older than firm 1.00&n; * I eliminated the write register as a 2 trip of writing hi word and lo word&n; * and force this to write only 4 bytes at a time.&n; * NOTE: this should work with all the firmware from 1.00 and newer&n; */
DECL|function|b2c2_usb_write_dw
r_static
r_int
id|b2c2_usb_write_dw
c_func
(paren
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
comma
id|u16
id|wRegOffsPCI
comma
id|u32
id|val
)paren
(brace
id|u16
id|wAddress
op_assign
id|B2C2_FLEX_PCIOFFSET_TO_INTERNALADDR
c_func
(paren
id|wRegOffsPCI
)paren
suffix:semicolon
r_int
id|len
op_assign
id|usb_control_msg
c_func
(paren
id|b2c2-&gt;udev
comma
id|B2C2_USB_CTRL_PIPE_OUT
comma
id|B2C2_USB_WRITE_REG
comma
id|RTYPE_WRITE_DW_1
comma
id|wAddress
comma
l_int|0
comma
op_amp
id|val
comma
r_sizeof
(paren
id|u32
)paren
comma
id|B2C2_WAIT_FOR_OPERATION_RDW
op_star
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
r_sizeof
(paren
id|u32
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;error while reading dword from %d (%d).&quot;
comma
id|wAddress
comma
id|wRegOffsPCI
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * DKT 010817 - add support for V8 memory read/write and flash update&n; */
DECL|function|b2c2_usb_v8_memory_req
r_static
r_int
id|b2c2_usb_v8_memory_req
c_func
(paren
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
comma
id|b2c2_usb_request_t
id|req
comma
id|u8
id|page
comma
id|u16
id|wAddress
comma
id|u16
id|buflen
comma
id|u8
op_star
id|pbBuffer
)paren
(brace
id|u8
id|dwRequestType
suffix:semicolon
id|u16
id|wIndex
suffix:semicolon
r_int
id|nWaitTime
comma
id|pipe
comma
id|len
suffix:semicolon
id|wIndex
op_assign
id|page
op_lshift
l_int|8
suffix:semicolon
r_switch
c_cond
(paren
id|req
)paren
(brace
r_case
id|B2C2_USB_READ_V8_MEM
suffix:colon
id|nWaitTime
op_assign
id|B2C2_WAIT_FOR_OPERATION_V8READ
suffix:semicolon
id|dwRequestType
op_assign
(paren
id|u8
)paren
id|RTYPE_READ_V8_MEMORY
suffix:semicolon
id|pipe
op_assign
id|B2C2_USB_CTRL_PIPE_IN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B2C2_USB_WRITE_V8_MEM
suffix:colon
id|wIndex
op_or_assign
id|pbBuffer
(braket
l_int|0
)braket
suffix:semicolon
id|nWaitTime
op_assign
id|B2C2_WAIT_FOR_OPERATION_V8WRITE
suffix:semicolon
id|dwRequestType
op_assign
(paren
id|u8
)paren
id|RTYPE_WRITE_V8_MEMORY
suffix:semicolon
id|pipe
op_assign
id|B2C2_USB_CTRL_PIPE_OUT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|B2C2_USB_FLASH_BLOCK
suffix:colon
id|nWaitTime
op_assign
id|B2C2_WAIT_FOR_OPERATION_V8FLASH
suffix:semicolon
id|dwRequestType
op_assign
(paren
id|u8
)paren
id|RTYPE_WRITE_V8_FLASH
suffix:semicolon
id|pipe
op_assign
id|B2C2_USB_CTRL_PIPE_OUT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|deb_info
c_func
(paren
l_string|&quot;unsupported request for v8_mem_req %x.&bslash;n&quot;
comma
id|req
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|len
op_assign
id|usb_control_msg
c_func
(paren
id|b2c2-&gt;udev
comma
id|pipe
comma
id|req
comma
id|dwRequestType
comma
id|wAddress
comma
id|wIndex
comma
id|pbBuffer
comma
id|buflen
comma
id|nWaitTime
op_star
id|HZ
)paren
suffix:semicolon
r_return
id|len
op_eq
id|buflen
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|b2c2_usb_i2c_req
r_static
r_int
id|b2c2_usb_i2c_req
c_func
(paren
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
comma
id|b2c2_usb_request_t
id|req
comma
id|b2c2_usb_i2c_function_t
id|func
comma
id|u8
id|port
comma
id|u8
id|chipaddr
comma
id|u8
id|addr
comma
id|u8
id|buflen
comma
id|u8
op_star
id|buf
)paren
(brace
id|u16
id|wValue
comma
id|wIndex
suffix:semicolon
r_int
id|nWaitTime
comma
id|pipe
comma
id|len
suffix:semicolon
id|u8
id|dwRequestType
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|USB_FUNC_I2C_WRITE
suffix:colon
r_case
id|USB_FUNC_I2C_MULTIWRITE
suffix:colon
r_case
id|USB_FUNC_I2C_REPEATWRITE
suffix:colon
multiline_comment|/* DKT 020208 - add this to support special case of DiSEqC */
r_case
id|USB_FUNC_I2C_CHECKWRITE
suffix:colon
id|pipe
op_assign
id|B2C2_USB_CTRL_PIPE_OUT
suffix:semicolon
id|nWaitTime
op_assign
l_int|2
suffix:semicolon
id|dwRequestType
op_assign
(paren
id|u8
)paren
id|RTYPE_GENERIC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_FUNC_I2C_READ
suffix:colon
r_case
id|USB_FUNC_I2C_REPEATREAD
suffix:colon
id|pipe
op_assign
id|B2C2_USB_CTRL_PIPE_IN
suffix:semicolon
id|nWaitTime
op_assign
l_int|2
suffix:semicolon
id|dwRequestType
op_assign
(paren
id|u8
)paren
id|RTYPE_GENERIC
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|deb_info
c_func
(paren
l_string|&quot;unsupported function for i2c_req %x&bslash;n&quot;
comma
id|func
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|wValue
op_assign
(paren
id|func
op_lshift
l_int|8
)paren
op_or
id|port
suffix:semicolon
id|wIndex
op_assign
(paren
id|chipaddr
op_lshift
l_int|8
)paren
op_or
id|addr
suffix:semicolon
id|len
op_assign
id|usb_control_msg
c_func
(paren
id|b2c2-&gt;udev
comma
id|pipe
comma
id|req
comma
id|dwRequestType
comma
id|addr
comma
id|wIndex
comma
id|buf
comma
id|buflen
comma
id|nWaitTime
op_star
id|HZ
)paren
suffix:semicolon
r_return
id|len
op_eq
id|buflen
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|b2c2_usb_utility_req
r_int
r_static
id|b2c2_usb_utility_req
c_func
(paren
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
comma
r_int
id|set
comma
id|b2c2_usb_utility_function_t
id|func
comma
id|u8
id|extra
comma
id|u16
id|wIndex
comma
id|u16
id|buflen
comma
id|u8
op_star
id|pvBuffer
)paren
(brace
id|u16
id|wValue
suffix:semicolon
r_int
id|nWaitTime
op_assign
l_int|2
comma
id|pipe
op_assign
id|set
ques
c_cond
id|B2C2_USB_CTRL_PIPE_OUT
suffix:colon
id|B2C2_USB_CTRL_PIPE_IN
comma
id|len
suffix:semicolon
id|wValue
op_assign
(paren
id|func
op_lshift
l_int|8
)paren
op_or
id|extra
suffix:semicolon
id|len
op_assign
id|usb_control_msg
c_func
(paren
id|b2c2-&gt;udev
comma
id|pipe
comma
id|B2C2_USB_UTILITY
comma
(paren
id|u8
)paren
id|RTYPE_GENERIC
comma
id|wValue
comma
id|wIndex
comma
id|pvBuffer
comma
id|buflen
comma
id|nWaitTime
op_star
id|HZ
)paren
suffix:semicolon
r_return
id|len
op_eq
id|buflen
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|b2c2_dumpfourreg
r_static
r_void
id|b2c2_dumpfourreg
c_func
(paren
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
comma
id|u16
id|offs
)paren
(brace
id|u32
id|r0
comma
id|r1
comma
id|r2
comma
id|r3
suffix:semicolon
id|r0
op_assign
id|r1
op_assign
id|r2
op_assign
id|r3
op_assign
l_int|0
suffix:semicolon
id|r0
op_assign
id|b2c2_usb_read_dw
c_func
(paren
id|b2c2
comma
id|offs
)paren
suffix:semicolon
id|r1
op_assign
id|b2c2_usb_read_dw
c_func
(paren
id|b2c2
comma
id|offs
op_plus
l_int|0x04
)paren
suffix:semicolon
id|r2
op_assign
id|b2c2_usb_read_dw
c_func
(paren
id|b2c2
comma
id|offs
op_plus
l_int|0x08
)paren
suffix:semicolon
id|r3
op_assign
id|b2c2_usb_read_dw
c_func
(paren
id|b2c2
comma
id|offs
op_plus
l_int|0x0c
)paren
suffix:semicolon
id|deb_ctrl
c_func
(paren
l_string|&quot;dump: offset: %03x, %08x, %08x, %08x, %08x&bslash;n&quot;
comma
id|offs
comma
id|r0
comma
id|r1
comma
id|r2
comma
id|r3
)paren
suffix:semicolon
)brace
DECL|function|b2c2_urb_complete
r_static
r_void
id|b2c2_urb_complete
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|pt_regs
op_star
id|ptregs
)paren
(brace
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
op_assign
id|urb-&gt;context
suffix:semicolon
id|deb_ts
c_func
(paren
l_string|&quot;urb completed, bufsize: %d&bslash;n&quot;
comma
id|urb-&gt;transfer_buffer_length
)paren
suffix:semicolon
singleline_comment|//&t;urb_submit_urb(urb,GFP_ATOMIC); enable for real action
)brace
DECL|function|b2c2_exit_usb
r_static
r_void
id|b2c2_exit_usb
c_func
(paren
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|B2C2_USB_NUM_ISO_URB
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|b2c2-&gt;iso_urb
(braket
id|i
)braket
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* not sure about unlink_urb and iso-urbs TODO */
id|deb_info
c_func
(paren
l_string|&quot;unlinking/killing urb no. %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt;= KERNEL_VERSION(2,6,7)
id|usb_unlink_urb
c_func
(paren
id|b2c2-&gt;iso_urb
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#else
id|usb_kill_urb
c_func
(paren
id|b2c2-&gt;iso_urb
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
id|usb_free_urb
c_func
(paren
id|b2c2-&gt;iso_urb
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|b2c2-&gt;iso_buffer
op_ne
l_int|NULL
)paren
id|pci_free_consistent
c_func
(paren
l_int|NULL
comma
id|b2c2-&gt;buffer_size
comma
id|b2c2-&gt;iso_buffer
comma
id|b2c2-&gt;iso_dma_handle
)paren
suffix:semicolon
)brace
DECL|function|b2c2_init_usb
r_static
r_int
id|b2c2_init_usb
c_func
(paren
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
)paren
(brace
id|u16
id|frame_size
op_assign
id|le16_to_cpu
c_func
(paren
id|b2c2-&gt;uintf-&gt;cur_altsetting-&gt;endpoint
(braket
l_int|0
)braket
dot
id|desc.wMaxPacketSize
)paren
suffix:semicolon
r_int
id|bufsize
op_assign
id|B2C2_USB_NUM_ISO_URB
op_star
id|B2C2_USB_FRAMES_PER_ISO
op_star
id|frame_size
comma
id|i
comma
id|j
comma
id|ret
suffix:semicolon
r_int
id|buffer_offset
op_assign
l_int|0
suffix:semicolon
id|deb_info
c_func
(paren
l_string|&quot;creating %d iso-urbs with %d frames each of %d bytes size = %d.&bslash;n&quot;
comma
id|B2C2_USB_NUM_ISO_URB
comma
id|B2C2_USB_FRAMES_PER_ISO
comma
id|frame_size
comma
id|bufsize
)paren
suffix:semicolon
id|b2c2-&gt;iso_buffer
op_assign
id|pci_alloc_consistent
c_func
(paren
l_int|NULL
comma
id|bufsize
comma
op_amp
id|b2c2-&gt;iso_dma_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b2c2-&gt;iso_buffer
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|b2c2-&gt;iso_buffer
comma
l_int|0
comma
id|bufsize
)paren
suffix:semicolon
id|b2c2-&gt;buffer_size
op_assign
id|bufsize
suffix:semicolon
multiline_comment|/* creating iso urbs */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|B2C2_USB_NUM_ISO_URB
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|b2c2-&gt;iso_urb
(braket
id|i
)braket
op_assign
id|usb_alloc_urb
c_func
(paren
id|B2C2_USB_FRAMES_PER_ISO
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|urb_error
suffix:semicolon
)brace
multiline_comment|/* initialising and submitting iso urbs */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|B2C2_USB_NUM_ISO_URB
suffix:semicolon
id|i
op_increment
)paren
(brace
id|deb_info
c_func
(paren
l_string|&quot;initializing and submitting urb no. %d (buf_offset: %d).&bslash;n&quot;
comma
id|i
comma
id|buffer_offset
)paren
suffix:semicolon
r_int
id|frame_offset
op_assign
l_int|0
suffix:semicolon
r_struct
id|urb
op_star
id|urb
op_assign
id|b2c2-&gt;iso_urb
(braket
id|i
)braket
suffix:semicolon
id|urb-&gt;dev
op_assign
id|b2c2-&gt;udev
suffix:semicolon
id|urb-&gt;context
op_assign
id|b2c2
suffix:semicolon
id|urb-&gt;complete
op_assign
id|b2c2_urb_complete
suffix:semicolon
id|urb-&gt;pipe
op_assign
id|B2C2_USB_DATA_PIPE
suffix:semicolon
id|urb-&gt;transfer_flags
op_assign
id|URB_ISO_ASAP
suffix:semicolon
id|urb-&gt;interval
op_assign
l_int|1
suffix:semicolon
id|urb-&gt;number_of_packets
op_assign
id|B2C2_USB_FRAMES_PER_ISO
suffix:semicolon
id|urb-&gt;transfer_buffer_length
op_assign
id|frame_size
op_star
id|B2C2_USB_FRAMES_PER_ISO
suffix:semicolon
id|urb-&gt;transfer_buffer
op_assign
id|b2c2-&gt;iso_buffer
op_plus
id|buffer_offset
suffix:semicolon
id|buffer_offset
op_add_assign
id|frame_size
op_star
id|B2C2_USB_FRAMES_PER_ISO
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|B2C2_USB_FRAMES_PER_ISO
suffix:semicolon
id|j
op_increment
)paren
(brace
id|deb_info
c_func
(paren
l_string|&quot;urb no: %d, frame: %d, frame_offset: %d&bslash;n&quot;
comma
id|i
comma
id|j
comma
id|frame_offset
)paren
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
id|j
)braket
dot
id|offset
op_assign
id|frame_offset
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
id|j
)braket
dot
id|length
op_assign
id|frame_size
suffix:semicolon
id|frame_offset
op_add_assign
id|frame_size
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|usb_submit_urb
c_func
(paren
id|b2c2-&gt;iso_urb
(braket
id|i
)braket
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;submitting urb %d failed with %d.&quot;
comma
id|i
comma
id|ret
)paren
suffix:semicolon
r_goto
id|urb_error
suffix:semicolon
)brace
id|deb_info
c_func
(paren
l_string|&quot;submitted urb no. %d.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|success
suffix:semicolon
id|urb_error
suffix:colon
id|b2c2_exit_usb
c_func
(paren
id|b2c2
)paren
suffix:semicolon
id|success
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|b2c2_usb_probe
r_static
r_int
id|b2c2_usb_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|b2c2
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|usb_b2c2_usb
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b2c2
op_eq
l_int|NULL
)paren
(brace
id|err
c_func
(paren
l_string|&quot;no memory&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|b2c2-&gt;udev
op_assign
id|udev
suffix:semicolon
id|b2c2-&gt;uintf
op_assign
id|intf
suffix:semicolon
multiline_comment|/* use the alternate setting with the larges buffer */
id|usb_set_interface
c_func
(paren
id|udev
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|b2c2_init_usb
c_func
(paren
id|b2c2
)paren
)paren
)paren
r_goto
id|usb_init_error
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
id|b2c2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|udev-&gt;speed
)paren
(brace
r_case
id|USB_SPEED_LOW
suffix:colon
id|err
c_func
(paren
l_string|&quot;cannot handle USB speed because it is to sLOW.&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_SPEED_FULL
suffix:colon
id|info
c_func
(paren
l_string|&quot;running at FULL speed.&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_SPEED_HIGH
suffix:colon
id|info
c_func
(paren
l_string|&quot;running at HIGH speed.&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_SPEED_UNKNOWN
suffix:colon
multiline_comment|/* fall through */
r_default
suffix:colon
id|err
c_func
(paren
l_string|&quot;cannot handle USB speed because it is unkown.&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|b2c2_dumpfourreg
c_func
(paren
id|b2c2
comma
l_int|0x200
)paren
suffix:semicolon
id|b2c2_dumpfourreg
c_func
(paren
id|b2c2
comma
l_int|0x300
)paren
suffix:semicolon
id|b2c2_dumpfourreg
c_func
(paren
id|b2c2
comma
l_int|0x400
)paren
suffix:semicolon
id|b2c2_dumpfourreg
c_func
(paren
id|b2c2
comma
l_int|0x700
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|info
c_func
(paren
l_string|&quot;%s successfully initialized and connected.&quot;
comma
id|DRIVER_DESC
)paren
suffix:semicolon
r_else
id|info
c_func
(paren
l_string|&quot;%s error while loading driver (%d)&quot;
comma
id|DRIVER_DESC
comma
id|ret
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|success
suffix:semicolon
id|usb_init_error
suffix:colon
id|kfree
c_func
(paren
id|b2c2
)paren
suffix:semicolon
id|success
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|b2c2_usb_disconnect
r_static
r_void
id|b2c2_usb_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|usb_b2c2_usb
op_star
id|b2c2
op_assign
id|usb_get_intfdata
c_func
(paren
id|intf
)paren
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b2c2
op_ne
l_int|NULL
)paren
(brace
id|b2c2_exit_usb
c_func
(paren
id|b2c2
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|b2c2
)paren
suffix:semicolon
)brace
id|info
c_func
(paren
l_string|&quot;%s successfully deinitialized and disconnected.&quot;
comma
id|DRIVER_DESC
)paren
suffix:semicolon
)brace
DECL|variable|b2c2_usb_table
r_static
r_struct
id|usb_device_id
id|b2c2_usb_table
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0af7
comma
l_int|0x0101
)paren
)brace
)brace
suffix:semicolon
multiline_comment|/* usb specific object needed to register this driver with the usb subsystem */
DECL|variable|b2c2_usb_driver
r_static
r_struct
id|usb_driver
id|b2c2_usb_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;dvb_b2c2_usb&quot;
comma
dot
id|probe
op_assign
id|b2c2_usb_probe
comma
dot
id|disconnect
op_assign
id|b2c2_usb_disconnect
comma
dot
id|id_table
op_assign
id|b2c2_usb_table
comma
)brace
suffix:semicolon
multiline_comment|/* module stuff */
DECL|function|b2c2_usb_init
r_static
r_int
id|__init
id|b2c2_usb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|usb_register
c_func
(paren
op_amp
id|b2c2_usb_driver
)paren
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;usb_register failed. Error number %d&quot;
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|b2c2_usb_exit
r_static
r_void
id|__exit
id|b2c2_usb_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* deregister this driver from the USB subsystem */
id|usb_deregister
c_func
(paren
op_amp
id|b2c2_usb_driver
)paren
suffix:semicolon
)brace
DECL|variable|b2c2_usb_init
id|module_init
(paren
id|b2c2_usb_init
)paren
suffix:semicolon
DECL|variable|b2c2_usb_exit
id|module_exit
(paren
id|b2c2_usb_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
