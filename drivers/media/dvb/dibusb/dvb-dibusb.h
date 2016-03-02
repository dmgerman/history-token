multiline_comment|/*&n; * dvb-dibusb.h&n; *&n; * Copyright (C) 2004 Patrick Boettcher (patrick.boettcher@desy.de)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; *&n; * for more information see dvb-dibusb.c .&n; */
macro_line|#ifndef __DVB_DIBUSB_H__
DECL|macro|__DVB_DIBUSB_H__
mdefine_line|#define __DVB_DIBUSB_H__
multiline_comment|/* Vendor IDs */
DECL|macro|USB_TWINHAN_VENDOR_ID
mdefine_line|#define USB_TWINHAN_VENDOR_ID&t;&t;&t;0x1822
DECL|macro|USB_IMC_NETWORKS_VENDOR_ID
mdefine_line|#define USB_IMC_NETWORKS_VENDOR_ID&t;&t;0x13d3
DECL|macro|USB_KWORLD_VENDOR_ID
mdefine_line|#define USB_KWORLD_VENDOR_ID&t;&t;&t;0xeb1a
DECL|macro|USB_DIBCOM_VENDOR_ID
mdefine_line|#define USB_DIBCOM_VENDOR_ID&t;&t;&t;0x10b8
DECL|macro|USB_ULTIMA_ELECTRONIC_ID
mdefine_line|#define USB_ULTIMA_ELECTRONIC_ID&t;&t;0x05d8
multiline_comment|/* Product IDs before loading the firmware */
DECL|macro|USB_VP7041_PRODUCT_PREFW_ID
mdefine_line|#define USB_VP7041_PRODUCT_PREFW_ID&t;&t;0x3201
DECL|macro|USB_VSTREAM_PRODUCT_PREFW_ID
mdefine_line|#define USB_VSTREAM_PRODUCT_PREFW_ID&t;0x17de
DECL|macro|USB_DIBCOM_PRODUCT_PREFW_ID
mdefine_line|#define USB_DIBCOM_PRODUCT_PREFW_ID&t;&t;0x0bb8
DECL|macro|USB_ULTIMA_ELEC_PROD_PREFW_ID
mdefine_line|#define USB_ULTIMA_ELEC_PROD_PREFW_ID&t;0x8105
multiline_comment|/* product ID afterwards */
DECL|macro|USB_VP7041_PRODUCT_ID
mdefine_line|#define USB_VP7041_PRODUCT_ID&t;&t;&t;0x3202
DECL|macro|USB_VSTREAM_PRODUCT_ID
mdefine_line|#define USB_VSTREAM_PRODUCT_ID&t;&t;&t;0x17df
DECL|macro|USB_DIBCOM_PRODUCT_ID
mdefine_line|#define USB_DIBCOM_PRODUCT_ID&t;&t;&t;0x0bb9
DECL|macro|USB_ULTIMA_ELEC_PROD_ID
mdefine_line|#define USB_ULTIMA_ELEC_PROD_ID&t;&t;&t;0x8106
multiline_comment|/* CS register start/stop the usb controller cpu */
DECL|macro|DIBUSB_CPU_CSREG
mdefine_line|#define DIBUSB_CPU_CSREG&t;&t;&t;&t;0x7F92
singleline_comment|// 0x10 is the I2C address of the first demodulator on the board
DECL|macro|DIBUSB_DEMOD_I2C_ADDR_DEFAULT
mdefine_line|#define DIBUSB_DEMOD_I2C_ADDR_DEFAULT&t;0x10
DECL|macro|DIBUSB_I2C_TIMEOUT
mdefine_line|#define DIBUSB_I2C_TIMEOUT &t;&t;&t;&t;HZ*5
DECL|macro|DIBUSB_MAX_PIDS
mdefine_line|#define DIBUSB_MAX_PIDS&t;&t;&t;&t;&t;16
DECL|macro|DIB3000MB_REG_FIRST_PID
mdefine_line|#define DIB3000MB_REG_FIRST_PID&t;&t;&t;(   153)
r_struct
id|usb_dibusb
suffix:semicolon
DECL|struct|dibusb_pid
r_struct
id|dibusb_pid
(brace
DECL|member|reg
id|u16
id|reg
suffix:semicolon
DECL|member|pid
id|u16
id|pid
suffix:semicolon
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|dib
r_struct
id|usb_dibusb
op_star
id|dib
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usb_dibusb
r_struct
id|usb_dibusb
(brace
multiline_comment|/* usb */
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|dibdev
r_struct
id|dibusb_device
op_star
id|dibdev
suffix:semicolon
DECL|member|streaming
r_int
id|streaming
suffix:semicolon
DECL|member|feed_count
r_int
id|feed_count
suffix:semicolon
DECL|member|buf_urb
r_struct
id|urb
op_star
id|buf_urb
suffix:semicolon
DECL|member|buffer
id|u8
op_star
id|buffer
suffix:semicolon
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
DECL|member|pid_list_lock
id|spinlock_t
id|pid_list_lock
suffix:semicolon
DECL|member|pid_list
r_struct
id|dibusb_pid
id|pid_list
(braket
id|DIBUSB_MAX_PIDS
)braket
suffix:semicolon
multiline_comment|/* I2C */
DECL|member|i2c_adap
r_struct
id|i2c_adapter
id|i2c_adap
suffix:semicolon
DECL|member|i2c_client
r_struct
id|i2c_client
id|i2c_client
suffix:semicolon
multiline_comment|/* locking */
DECL|member|usb_sem
r_struct
id|semaphore
id|usb_sem
suffix:semicolon
DECL|member|i2c_sem
r_struct
id|semaphore
id|i2c_sem
suffix:semicolon
multiline_comment|/* dvb */
DECL|member|adapter
r_struct
id|dvb_adapter
op_star
id|adapter
suffix:semicolon
DECL|member|dmxdev
r_struct
id|dmxdev
id|dmxdev
suffix:semicolon
DECL|member|demux
r_struct
id|dvb_demux
id|demux
suffix:semicolon
DECL|member|dvb_net
r_struct
id|dvb_net
id|dvb_net
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dibusb_device
r_struct
id|dibusb_device
(brace
DECL|member|cold_product_id
id|u16
id|cold_product_id
suffix:semicolon
DECL|member|warm_product_id
id|u16
id|warm_product_id
suffix:semicolon
DECL|member|demod_addr
id|u8
id|demod_addr
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* static array of valid firmware names, the best one first */
DECL|variable|valid_firmware_filenames
r_static
r_const
r_char
op_star
id|valid_firmware_filenames
(braket
)braket
op_assign
(brace
l_string|&quot;dvb-dibusb-5.0.0.11.fw&quot;
comma
)brace
suffix:semicolon
DECL|macro|DIBUSB_SUPPORTED_DEVICES
mdefine_line|#define DIBUSB_SUPPORTED_DEVICES&t;4
multiline_comment|/* USB Driver stuff */
DECL|variable|dibusb_devices
r_static
r_struct
id|dibusb_device
id|dibusb_devices
(braket
id|DIBUSB_SUPPORTED_DEVICES
)braket
op_assign
(brace
(brace
dot
id|cold_product_id
op_assign
id|USB_VP7041_PRODUCT_PREFW_ID
comma
dot
id|warm_product_id
op_assign
id|USB_VP7041_PRODUCT_ID
comma
dot
id|name
op_assign
l_string|&quot;Twinhan VisionDTV USB-Ter/HAMA USB DVB-T device&quot;
comma
dot
id|demod_addr
op_assign
id|DIBUSB_DEMOD_I2C_ADDR_DEFAULT
comma
)brace
comma
(brace
dot
id|cold_product_id
op_assign
id|USB_VSTREAM_PRODUCT_PREFW_ID
comma
dot
id|warm_product_id
op_assign
id|USB_VSTREAM_PRODUCT_ID
comma
dot
id|name
op_assign
l_string|&quot;KWorld V-Stream XPERT DTV - DVB-T USB&quot;
comma
dot
id|demod_addr
op_assign
id|DIBUSB_DEMOD_I2C_ADDR_DEFAULT
comma
)brace
comma
(brace
dot
id|cold_product_id
op_assign
id|USB_DIBCOM_PRODUCT_PREFW_ID
comma
dot
id|warm_product_id
op_assign
id|USB_DIBCOM_PRODUCT_ID
comma
dot
id|name
op_assign
l_string|&quot;DiBcom USB reference design&quot;
comma
dot
id|demod_addr
op_assign
id|DIBUSB_DEMOD_I2C_ADDR_DEFAULT
comma
)brace
comma
(brace
dot
id|cold_product_id
op_assign
id|USB_ULTIMA_ELEC_PROD_PREFW_ID
comma
dot
id|warm_product_id
op_assign
id|USB_ULTIMA_ELEC_PROD_ID
comma
dot
id|name
op_assign
l_string|&quot;Ultima Electronic/Artec T1 USB TVBOX&quot;
comma
dot
id|demod_addr
op_assign
id|DIBUSB_DEMOD_I2C_ADDR_DEFAULT
comma
)brace
comma
)brace
suffix:semicolon
DECL|macro|COMMAND_PIPE
mdefine_line|#define COMMAND_PIPE&t;usb_sndbulkpipe(dib-&gt;udev, 0x01)
DECL|macro|RESULT_PIPE
mdefine_line|#define RESULT_PIPE&t;&t;usb_rcvbulkpipe(dib-&gt;udev, 0x81)
DECL|macro|DATA_PIPE
mdefine_line|#define DATA_PIPE&t;&t;usb_rcvbulkpipe(dib-&gt;udev, 0x82)
multiline_comment|/*&n; * last endpoint 0x83 only used for chaining the buffers&n; * of the endpoints in the cypress&n; */
DECL|macro|CHAIN_PIPE_DO_NOT_USE
mdefine_line|#define CHAIN_PIPE_DO_NOT_USE&t;usb_rcvbulkpipe(dib-&gt;udev, 0x83)
multiline_comment|/* types of first byte of each buffer */
DECL|macro|DIBUSB_REQ_START_READ
mdefine_line|#define DIBUSB_REQ_START_READ&t;&t;&t;0x00
DECL|macro|DIBUSB_REQ_START_DEMOD
mdefine_line|#define DIBUSB_REQ_START_DEMOD&t;&t;&t;0x01
DECL|macro|DIBUSB_REQ_I2C_READ
mdefine_line|#define DIBUSB_REQ_I2C_READ  &t;&t;&t;0x02
DECL|macro|DIBUSB_REQ_I2C_WRITE
mdefine_line|#define DIBUSB_REQ_I2C_WRITE &t;&t;&t;0x03
multiline_comment|/* prefix for reading the current RC key */
DECL|macro|DIBUSB_REQ_POLL_REMOTE
mdefine_line|#define DIBUSB_REQ_POLL_REMOTE&t;&t;&t;0x04
multiline_comment|/* 0x05 0xXX */
DECL|macro|DIBUSB_REQ_SET_STREAMING_MODE
mdefine_line|#define DIBUSB_REQ_SET_STREAMING_MODE&t;0x05
multiline_comment|/* interrupt the internal read loop, when blocking */
DECL|macro|DIBUSB_REQ_INTR_READ
mdefine_line|#define DIBUSB_REQ_INTR_READ&t;&t;   &t;0x06
multiline_comment|/* IO control&n; * 0x07 &lt;cmd 1 byte&gt; &lt;param 32 bytes&gt;&n; */
DECL|macro|DIBUSB_REQ_SET_IOCTL
mdefine_line|#define DIBUSB_REQ_SET_IOCTL&t;&t;&t;0x07
multiline_comment|/* IOCTL commands */
multiline_comment|/* change the power mode in firmware */
DECL|macro|DIBUSB_IOCTL_CMD_POWER_MODE
mdefine_line|#define DIBUSB_IOCTL_CMD_POWER_MODE&t;&t;0x00
DECL|macro|DIBUSB_IOCTL_POWER_SLEEP
mdefine_line|#define DIBUSB_IOCTL_POWER_SLEEP&t;&t;&t;0x00
DECL|macro|DIBUSB_IOCTL_POWER_WAKEUP
mdefine_line|#define DIBUSB_IOCTL_POWER_WAKEUP&t;&t;&t;0x01
multiline_comment|/*&n; * values from the demodulator which are needed in&n; * the usb driver as well&n; */
DECL|macro|DIB3000MB_REG_FIFO
mdefine_line|#define DIB3000MB_REG_FIFO              (   145)
DECL|macro|DIB3000MB_FIFO_INHIBIT
mdefine_line|#define DIB3000MB_FIFO_INHIBIT              (     1)
DECL|macro|DIB3000MB_FIFO_ACTIVATE
mdefine_line|#define DIB3000MB_FIFO_ACTIVATE             (     0)
DECL|macro|DIB3000MB_ACTIVATE_FILTERING
mdefine_line|#define DIB3000MB_ACTIVATE_FILTERING            (0x2000)
macro_line|#endif
eof
