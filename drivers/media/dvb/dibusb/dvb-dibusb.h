multiline_comment|/*&n; * dvb-dibusb.h&n; *&n; * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@desy.de)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; * for more information see dvb-dibusb-core.c .&n; */
macro_line|#ifndef __DVB_DIBUSB_H__
DECL|macro|__DVB_DIBUSB_H__
mdefine_line|#define __DVB_DIBUSB_H__
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;dvb_demux.h&quot;
macro_line|#include &quot;dvb_net.h&quot;
macro_line|#include &quot;dmxdev.h&quot;
macro_line|#include &quot;dib3000.h&quot;
macro_line|#include &quot;mt352.h&quot;
multiline_comment|/* debug */
macro_line|#ifdef CONFIG_DVB_DIBCOM_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(level,args...) &bslash;&n;&t;    do { if ((debug &amp; level)) { printk(args); } } while (0)
DECL|macro|debug_dump
mdefine_line|#define debug_dump(b,l) if (debug) {&bslash;&n;&t;int i; deb_xfer(&quot;%s: %d &gt; &quot;,__FUNCTION__,l); &bslash;&n;&t;for (i = 0; i &lt; l; i++) deb_xfer(&quot;%02x &quot;, b[i]); &bslash;&n;&t;deb_xfer(&quot;&bslash;n&quot;);&bslash;&n;}
multiline_comment|/* module parameters - declared in -core.c */
r_extern
r_int
id|debug
suffix:semicolon
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(args...)
DECL|macro|debug_dump
mdefine_line|#define debug_dump(b,l)
macro_line|#endif
multiline_comment|/* Version information */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;0.3&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;Driver for DiBcom based USB Budget DVB-T device&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Patrick Boettcher, patrick.boettcher@desy.de&quot;
multiline_comment|/* module parameters - declared in -core.c */
r_extern
r_int
id|pid_parse
suffix:semicolon
r_extern
r_int
id|rc_query_interval
suffix:semicolon
DECL|macro|deb_info
mdefine_line|#define deb_info(args...) dprintk(0x01,args)
DECL|macro|deb_xfer
mdefine_line|#define deb_xfer(args...) dprintk(0x02,args)
DECL|macro|deb_alot
mdefine_line|#define deb_alot(args...) dprintk(0x04,args)
DECL|macro|deb_ts
mdefine_line|#define deb_ts(args...)   dprintk(0x08,args)
DECL|macro|deb_err
mdefine_line|#define deb_err(args...)  dprintk(0x10,args)
DECL|macro|deb_rc
mdefine_line|#define deb_rc(args...)   dprintk(0x20,args)
multiline_comment|/* generic log methods - taken from usb.h */
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
DECL|struct|dibusb_usb_controller
r_struct
id|dibusb_usb_controller
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of the usb controller */
DECL|member|cpu_cs_register
id|u16
id|cpu_cs_register
suffix:semicolon
multiline_comment|/* needs to be restarted, when the firmware has been downloaded. */
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|DIBUSB1_1
id|DIBUSB1_1
op_assign
l_int|0
comma
DECL|enumerator|DIBUSB1_1_AN2235
id|DIBUSB1_1_AN2235
comma
DECL|enumerator|DIBUSB2_0
id|DIBUSB2_0
comma
DECL|enumerator|UMT2_0
id|UMT2_0
comma
DECL|typedef|dibusb_class_t
)brace
id|dibusb_class_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|DIBUSB_TUNER_CABLE_THOMSON
id|DIBUSB_TUNER_CABLE_THOMSON
op_assign
l_int|0
comma
DECL|enumerator|DIBUSB_TUNER_COFDM_PANASONIC_ENV57H1XD5
id|DIBUSB_TUNER_COFDM_PANASONIC_ENV57H1XD5
comma
DECL|enumerator|DIBUSB_TUNER_CABLE_LG_TDTP_E102P
id|DIBUSB_TUNER_CABLE_LG_TDTP_E102P
comma
DECL|enumerator|DIBUSB_TUNER_COFDM_PANASONIC_ENV77H11D5
id|DIBUSB_TUNER_COFDM_PANASONIC_ENV77H11D5
comma
DECL|typedef|dibusb_tuner_t
)brace
id|dibusb_tuner_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|DIBUSB_DIB3000MB
id|DIBUSB_DIB3000MB
op_assign
l_int|0
comma
DECL|enumerator|DIBUSB_DIB3000MC
id|DIBUSB_DIB3000MC
comma
DECL|enumerator|DIBUSB_MT352
id|DIBUSB_MT352
comma
DECL|typedef|dibusb_demodulator_t
)brace
id|dibusb_demodulator_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|DIBUSB_RC_NO
id|DIBUSB_RC_NO
op_assign
l_int|0
comma
DECL|enumerator|DIBUSB_RC_NEC_PROTOCOL
id|DIBUSB_RC_NEC_PROTOCOL
op_assign
l_int|1
comma
DECL|typedef|dibusb_remote_t
)brace
id|dibusb_remote_t
suffix:semicolon
DECL|struct|dibusb_tuner
r_struct
id|dibusb_tuner
(brace
DECL|member|id
id|dibusb_tuner_t
id|id
suffix:semicolon
DECL|member|pll_addr
id|u8
id|pll_addr
suffix:semicolon
multiline_comment|/* tuner i2c address */
)brace
suffix:semicolon
r_extern
r_struct
id|dibusb_tuner
id|dibusb_tuner
(braket
)braket
suffix:semicolon
DECL|macro|DIBUSB_POSSIBLE_I2C_ADDR_NUM
mdefine_line|#define DIBUSB_POSSIBLE_I2C_ADDR_NUM 4
DECL|struct|dibusb_demod
r_struct
id|dibusb_demod
(brace
DECL|member|id
id|dibusb_demodulator_t
id|id
suffix:semicolon
DECL|member|pid_filter_count
r_int
id|pid_filter_count
suffix:semicolon
multiline_comment|/* counter of the internal pid_filter */
DECL|member|i2c_addrs
id|u8
id|i2c_addrs
(braket
id|DIBUSB_POSSIBLE_I2C_ADDR_NUM
)braket
suffix:semicolon
multiline_comment|/* list of possible i2c addresses of the demod */
)brace
suffix:semicolon
DECL|macro|DIBUSB_MAX_TUNER_NUM
mdefine_line|#define DIBUSB_MAX_TUNER_NUM 2
DECL|struct|dibusb_device_class
r_struct
id|dibusb_device_class
(brace
DECL|member|id
id|dibusb_class_t
id|id
suffix:semicolon
DECL|member|usb_ctrl
r_const
r_struct
id|dibusb_usb_controller
op_star
id|usb_ctrl
suffix:semicolon
multiline_comment|/* usb controller */
DECL|member|firmware
r_const
r_char
op_star
id|firmware
suffix:semicolon
multiline_comment|/* valid firmware filenames */
DECL|member|pipe_cmd
r_int
id|pipe_cmd
suffix:semicolon
multiline_comment|/* command pipe (read/write) */
DECL|member|pipe_data
r_int
id|pipe_data
suffix:semicolon
multiline_comment|/* data pipe */
DECL|member|urb_count
r_int
id|urb_count
suffix:semicolon
multiline_comment|/* number of data URBs to be submitted */
DECL|member|urb_buffer_size
r_int
id|urb_buffer_size
suffix:semicolon
multiline_comment|/* the size of the buffer for each URB */
DECL|member|remote_type
id|dibusb_remote_t
id|remote_type
suffix:semicolon
multiline_comment|/* does this device have a ir-receiver */
DECL|member|demod
r_struct
id|dibusb_demod
op_star
id|demod
suffix:semicolon
multiline_comment|/* which demodulator is mount */
DECL|member|tuner
r_struct
id|dibusb_tuner
op_star
id|tuner
suffix:semicolon
multiline_comment|/* which tuner can be found here */
)brace
suffix:semicolon
DECL|macro|DIBUSB_ID_MAX_NUM
mdefine_line|#define DIBUSB_ID_MAX_NUM 15
DECL|struct|dibusb_usb_device
r_struct
id|dibusb_usb_device
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* real name of the box */
DECL|member|dev_cl
r_struct
id|dibusb_device_class
op_star
id|dev_cl
suffix:semicolon
multiline_comment|/* which dibusb_device_class is this device part of */
DECL|member|cold_ids
r_struct
id|usb_device_id
op_star
id|cold_ids
(braket
id|DIBUSB_ID_MAX_NUM
)braket
suffix:semicolon
multiline_comment|/* list of USB ids when this device is at pre firmware state */
DECL|member|warm_ids
r_struct
id|usb_device_id
op_star
id|warm_ids
(braket
id|DIBUSB_ID_MAX_NUM
)braket
suffix:semicolon
multiline_comment|/* list of USB ids when this device is at post firmware state */
)brace
suffix:semicolon
multiline_comment|/* a PID for the pid_filter list, when in use */
DECL|struct|dibusb_pid
r_struct
id|dibusb_pid
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|pid
id|u16
id|pid
suffix:semicolon
DECL|member|active
r_int
id|active
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
id|dibusb_usb_device
op_star
id|dibdev
suffix:semicolon
DECL|macro|DIBUSB_STATE_INIT
mdefine_line|#define DIBUSB_STATE_INIT       0x000
DECL|macro|DIBUSB_STATE_URB_LIST
mdefine_line|#define DIBUSB_STATE_URB_LIST   0x001
DECL|macro|DIBUSB_STATE_URB_BUF
mdefine_line|#define DIBUSB_STATE_URB_BUF    0x002
DECL|macro|DIBUSB_STATE_URB_SUBMIT
mdefine_line|#define DIBUSB_STATE_URB_SUBMIT 0x004 
DECL|macro|DIBUSB_STATE_DVB
mdefine_line|#define DIBUSB_STATE_DVB        0x008
DECL|macro|DIBUSB_STATE_I2C
mdefine_line|#define DIBUSB_STATE_I2C        0x010
DECL|macro|DIBUSB_STATE_REMOTE
mdefine_line|#define DIBUSB_STATE_REMOTE&t;&t;0x020
DECL|macro|DIBUSB_STATE_PIDLIST
mdefine_line|#define DIBUSB_STATE_PIDLIST    0x040
DECL|member|init_state
r_int
id|init_state
suffix:semicolon
DECL|member|feedcount
r_int
id|feedcount
suffix:semicolon
DECL|member|pid_parse
r_int
id|pid_parse
suffix:semicolon
DECL|member|xfer_ops
r_struct
id|dib_fe_xfer_ops
id|xfer_ops
suffix:semicolon
DECL|member|tuner
r_struct
id|dibusb_tuner
op_star
id|tuner
suffix:semicolon
DECL|member|urb_list
r_struct
id|urb
op_star
op_star
id|urb_list
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
multiline_comment|/* I2C */
DECL|member|i2c_adap
r_struct
id|i2c_adapter
id|i2c_adap
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
multiline_comment|/* pid filtering */
DECL|member|pid_list_lock
id|spinlock_t
id|pid_list_lock
suffix:semicolon
DECL|member|pid_list
r_struct
id|dibusb_pid
op_star
id|pid_list
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
DECL|member|fe
r_struct
id|dvb_frontend
op_star
id|fe
suffix:semicolon
DECL|member|fe_sleep
r_int
(paren
op_star
id|fe_sleep
)paren
(paren
r_struct
id|dvb_frontend
op_star
)paren
suffix:semicolon
DECL|member|fe_init
r_int
(paren
op_star
id|fe_init
)paren
(paren
r_struct
id|dvb_frontend
op_star
)paren
suffix:semicolon
multiline_comment|/* remote control */
DECL|member|rc_input_dev
r_struct
id|input_dev
id|rc_input_dev
suffix:semicolon
DECL|member|rc_query_work
r_struct
id|work_struct
id|rc_query_work
suffix:semicolon
DECL|member|rc_input_event
r_int
id|rc_input_event
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* commonly used functions in the separated files */
multiline_comment|/* dvb-dibusb-firmware.c */
r_int
id|dibusb_loadfirmware
c_func
(paren
r_struct
id|usb_device
op_star
id|udev
comma
r_struct
id|dibusb_usb_device
op_star
id|dibdev
)paren
suffix:semicolon
multiline_comment|/* dvb-dibusb-remote.c */
r_int
id|dibusb_remote_exit
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
suffix:semicolon
r_int
id|dibusb_remote_init
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
suffix:semicolon
multiline_comment|/* dvb-dibusb-fe-i2c.c */
r_int
id|dibusb_i2c_msg
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
comma
id|u8
id|addr
comma
id|u8
op_star
id|wbuf
comma
id|u16
id|wlen
comma
id|u8
op_star
id|rbuf
comma
id|u16
id|rlen
)paren
suffix:semicolon
r_int
id|dibusb_fe_init
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
suffix:semicolon
r_int
id|dibusb_fe_exit
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
suffix:semicolon
r_int
id|dibusb_i2c_init
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
suffix:semicolon
r_int
id|dibusb_i2c_exit
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
suffix:semicolon
multiline_comment|/* dvb-dibusb-dvb.c */
r_void
id|dibusb_urb_complete
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
suffix:semicolon
r_int
id|dibusb_dvb_init
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
suffix:semicolon
r_int
id|dibusb_dvb_exit
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
suffix:semicolon
multiline_comment|/* dvb-dibusb-usb.c */
r_int
id|dibusb_readwrite_usb
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
comma
id|u8
op_star
id|wbuf
comma
id|u16
id|wlen
comma
id|u8
op_star
id|rbuf
comma
id|u16
id|rlen
)paren
suffix:semicolon
r_int
id|dibusb_hw_wakeup
c_func
(paren
r_struct
id|dvb_frontend
op_star
)paren
suffix:semicolon
r_int
id|dibusb_hw_sleep
c_func
(paren
r_struct
id|dvb_frontend
op_star
)paren
suffix:semicolon
r_int
id|dibusb_set_streaming_mode
c_func
(paren
r_struct
id|usb_dibusb
op_star
comma
id|u8
)paren
suffix:semicolon
r_int
id|dibusb_streaming
c_func
(paren
r_struct
id|usb_dibusb
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|dibusb_urb_init
c_func
(paren
r_struct
id|usb_dibusb
op_star
)paren
suffix:semicolon
r_int
id|dibusb_urb_exit
c_func
(paren
r_struct
id|usb_dibusb
op_star
)paren
suffix:semicolon
multiline_comment|/* dvb-dibusb-pid.c */
r_int
id|dibusb_pid_list_init
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
suffix:semicolon
r_void
id|dibusb_pid_list_exit
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
suffix:semicolon
r_int
id|dibusb_ctrl_pid
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
comma
r_struct
id|dvb_demux_feed
op_star
id|dvbdmxfeed
comma
r_int
id|onoff
)paren
suffix:semicolon
multiline_comment|/* i2c and transfer stuff */
DECL|macro|DIBUSB_I2C_TIMEOUT
mdefine_line|#define DIBUSB_I2C_TIMEOUT&t;&t;&t;&t;HZ*5
multiline_comment|/* &n; * protocol of all dibusb related devices&n; */
multiline_comment|/* &n; * bulk msg to/from endpoint 0x01&n; *&n; * general structure:&n; * request_byte parameter_bytes&n; */
DECL|macro|DIBUSB_REQ_START_READ
mdefine_line|#define DIBUSB_REQ_START_READ&t;&t;&t;0x00
DECL|macro|DIBUSB_REQ_START_DEMOD
mdefine_line|#define DIBUSB_REQ_START_DEMOD&t;&t;&t;0x01
multiline_comment|/* &n; * i2c read &n; * bulk write: 0x02 ((7bit i2c_addr &lt;&lt; 1) &amp; 0x01) register_bytes length_word&n; * bulk read:  byte_buffer (length_word bytes)&n; */
DECL|macro|DIBUSB_REQ_I2C_READ
mdefine_line|#define DIBUSB_REQ_I2C_READ  &t;&t;&t;0x02
multiline_comment|/*&n; * i2c write&n; * bulk write: 0x03 (7bit i2c_addr &lt;&lt; 1) register_bytes value_bytes&n; */
DECL|macro|DIBUSB_REQ_I2C_WRITE
mdefine_line|#define DIBUSB_REQ_I2C_WRITE &t;&t;&t;0x03
multiline_comment|/* &n; * polling the value of the remote control &n; * bulk write: 0x04&n; * bulk read:  byte_buffer (5 bytes) &n; *&n; * first byte of byte_buffer shows the status (0x00, 0x01, 0x02)&n; */
DECL|macro|DIBUSB_REQ_POLL_REMOTE
mdefine_line|#define DIBUSB_REQ_POLL_REMOTE&t;&t;&t;0x04
DECL|macro|DIBUSB_RC_NEC_EMPTY
mdefine_line|#define DIBUSB_RC_NEC_EMPTY&t;&t;&t;&t;0x00
DECL|macro|DIBUSB_RC_NEC_KEY_PRESSED
mdefine_line|#define DIBUSB_RC_NEC_KEY_PRESSED&t;&t;0x01
DECL|macro|DIBUSB_RC_NEC_KEY_REPEATED
mdefine_line|#define DIBUSB_RC_NEC_KEY_REPEATED&t;&t;0x02
multiline_comment|/* streaming mode:&n; * bulk write: 0x05 mode_byte &n; *&n; * mode_byte is mostly 0x00&n; */
DECL|macro|DIBUSB_REQ_SET_STREAMING_MODE
mdefine_line|#define DIBUSB_REQ_SET_STREAMING_MODE&t;0x05
multiline_comment|/* interrupt the internal read loop, when blocking */
DECL|macro|DIBUSB_REQ_INTR_READ
mdefine_line|#define DIBUSB_REQ_INTR_READ&t;&t;   &t;0x06
multiline_comment|/* io control&n; * 0x07 cmd_byte param_bytes&n; *&n; * param_bytes can be up to 32 bytes&n; *&n; * cmd_byte function    parameter name &n; * 0x00     power mode&n; *                      0x00      sleep&n; *                      0x01      wakeup&n; *&n; * 0x01     enable streaming &n; * 0x02     disable streaming&n; *&n; *&n; */
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
multiline_comment|/* modify streaming of the FX2 */
DECL|macro|DIBUSB_IOCTL_CMD_ENABLE_STREAM
mdefine_line|#define DIBUSB_IOCTL_CMD_ENABLE_STREAM&t;0x01
DECL|macro|DIBUSB_IOCTL_CMD_DISABLE_STREAM
mdefine_line|#define DIBUSB_IOCTL_CMD_DISABLE_STREAM&t;0x02
macro_line|#endif
eof
