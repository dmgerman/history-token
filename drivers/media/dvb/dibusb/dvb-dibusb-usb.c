multiline_comment|/*&n; * dvb-dibusb-usb.c is part of the driver for mobile USB Budget DVB-T devices&n; * based on reference design made by DiBcom (http://www.dibcom.fr/)&n; *&n; * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@desy.de)&n; *&n; * see dvb-dibusb-core.c for more copyright details.&n; *&n; * This file contains functions for initializing and handling the&n; * usb specific stuff.&n; */
macro_line|#include &quot;dvb-dibusb.h&quot;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
DECL|function|dibusb_readwrite_usb
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
(brace
r_int
id|actlen
comma
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|wbuf
op_eq
l_int|NULL
op_logical_or
id|wlen
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|down_interruptible
c_func
(paren
op_amp
id|dib-&gt;usb_sem
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
id|debug_dump
c_func
(paren
id|wbuf
comma
id|wlen
)paren
suffix:semicolon
id|ret
op_assign
id|usb_bulk_msg
c_func
(paren
id|dib-&gt;udev
comma
id|usb_sndbulkpipe
c_func
(paren
id|dib-&gt;udev
comma
id|dib-&gt;dibdev-&gt;dev_cl-&gt;pipe_cmd
)paren
comma
id|wbuf
comma
id|wlen
comma
op_amp
id|actlen
comma
id|DIBUSB_I2C_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|err
c_func
(paren
l_string|&quot;bulk message failed: %d (%d/%d)&quot;
comma
id|ret
comma
id|wlen
comma
id|actlen
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|actlen
op_ne
id|wlen
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* an answer is expected, and no error before */
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|rbuf
op_logical_and
id|rlen
)paren
(brace
id|ret
op_assign
id|usb_bulk_msg
c_func
(paren
id|dib-&gt;udev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|dib-&gt;udev
comma
id|dib-&gt;dibdev-&gt;dev_cl-&gt;pipe_cmd
)paren
comma
id|rbuf
comma
id|rlen
comma
op_amp
id|actlen
comma
id|DIBUSB_I2C_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|err
c_func
(paren
l_string|&quot;recv bulk message failed: %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_else
(brace
id|deb_alot
c_func
(paren
l_string|&quot;rlen: %d&bslash;n&quot;
comma
id|rlen
)paren
suffix:semicolon
id|debug_dump
c_func
(paren
id|rbuf
comma
id|actlen
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|dib-&gt;usb_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Cypress controls&n; */
DECL|function|dibusb_write_usb
r_int
id|dibusb_write_usb
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
comma
id|u8
op_star
id|buf
comma
id|u16
id|len
)paren
(brace
r_return
id|dibusb_readwrite_usb
c_func
(paren
id|dib
comma
id|buf
comma
id|len
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/*&n; * #if 0&squot;ing the following functions as they are not in use _now_,&n; * but probably will be sometime.&n; */
multiline_comment|/*&n; * do not use this, just a workaround for a bug,&n; * which will hopefully never occur :).&n; */
r_int
id|dibusb_interrupt_read_loop
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
id|u8
id|b
(braket
l_int|1
)braket
op_assign
(brace
id|DIBUSB_REQ_INTR_READ
)brace
suffix:semicolon
r_return
id|dibusb_write_usb
c_func
(paren
id|dib
comma
id|b
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * ioctl for the firmware&n; */
DECL|function|dibusb_ioctl_cmd
r_static
r_int
id|dibusb_ioctl_cmd
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
comma
id|u8
id|cmd
comma
id|u8
op_star
id|param
comma
r_int
id|plen
)paren
(brace
id|u8
id|b
(braket
l_int|34
)braket
suffix:semicolon
r_int
id|size
op_assign
id|plen
OG
l_int|32
ques
c_cond
l_int|32
suffix:colon
id|plen
suffix:semicolon
id|memset
c_func
(paren
id|b
comma
l_int|0
comma
l_int|34
)paren
suffix:semicolon
id|b
(braket
l_int|0
)braket
op_assign
id|DIBUSB_REQ_SET_IOCTL
suffix:semicolon
id|b
(braket
l_int|1
)braket
op_assign
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
id|memcpy
c_func
(paren
op_amp
id|b
(braket
l_int|2
)braket
comma
id|param
comma
id|size
)paren
suffix:semicolon
r_return
id|dibusb_write_usb
c_func
(paren
id|dib
comma
id|b
comma
l_int|34
)paren
suffix:semicolon
singleline_comment|//2+size);
)brace
multiline_comment|/*&n; * ioctl for power control&n; */
DECL|function|dibusb_hw_wakeup
r_int
id|dibusb_hw_wakeup
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|usb_dibusb
op_star
id|dib
op_assign
(paren
r_struct
id|usb_dibusb
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|u8
id|b
(braket
l_int|1
)braket
op_assign
(brace
id|DIBUSB_IOCTL_POWER_WAKEUP
)brace
suffix:semicolon
id|deb_info
c_func
(paren
l_string|&quot;dibusb-device is getting up.&bslash;n&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dib-&gt;dibdev-&gt;dev_cl-&gt;id
)paren
(brace
r_case
id|DTT200U
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|dibusb_ioctl_cmd
c_func
(paren
id|dib
comma
id|DIBUSB_IOCTL_CMD_POWER_MODE
comma
id|b
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dib-&gt;fe_init
)paren
r_return
id|dib
op_member_access_from_pointer
id|fe_init
c_func
(paren
id|fe
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_hw_sleep
r_int
id|dibusb_hw_sleep
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|usb_dibusb
op_star
id|dib
op_assign
(paren
r_struct
id|usb_dibusb
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|u8
id|b
(braket
l_int|1
)braket
op_assign
(brace
id|DIBUSB_IOCTL_POWER_SLEEP
)brace
suffix:semicolon
id|deb_info
c_func
(paren
l_string|&quot;dibusb-device is going to bed.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* workaround, something is wrong, when dibusb 1.1 device are going to bed too late */
r_switch
c_cond
(paren
id|dib-&gt;dibdev-&gt;dev_cl-&gt;id
)paren
(brace
r_case
id|DIBUSB1_1
suffix:colon
r_case
id|NOVAT_USB2
suffix:colon
r_case
id|DTT200U
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|dibusb_ioctl_cmd
c_func
(paren
id|dib
comma
id|DIBUSB_IOCTL_CMD_POWER_MODE
comma
id|b
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dib-&gt;fe_sleep
)paren
r_return
id|dib
op_member_access_from_pointer
id|fe_sleep
c_func
(paren
id|fe
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_set_streaming_mode
r_int
id|dibusb_set_streaming_mode
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
comma
id|u8
id|mode
)paren
(brace
id|u8
id|b
(braket
l_int|2
)braket
op_assign
(brace
id|DIBUSB_REQ_SET_STREAMING_MODE
comma
id|mode
)brace
suffix:semicolon
r_return
id|dibusb_readwrite_usb
c_func
(paren
id|dib
comma
id|b
comma
l_int|2
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|dibusb_urb_kill
r_static
r_int
id|dibusb_urb_kill
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
r_int
id|i
suffix:semicolon
id|deb_info
c_func
(paren
l_string|&quot;trying to kill urbs&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dib-&gt;init_state
op_amp
id|DIBUSB_STATE_URB_SUBMIT
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|deb_info
c_func
(paren
l_string|&quot;killing URB no. %d.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* stop the URB */
id|usb_kill_urb
c_func
(paren
id|dib-&gt;urb_list
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_else
id|deb_info
c_func
(paren
l_string|&quot; URBs not killed.&bslash;n&quot;
)paren
suffix:semicolon
id|dib-&gt;init_state
op_and_assign
op_complement
id|DIBUSB_STATE_URB_SUBMIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_urb_submit
r_static
r_int
id|dibusb_urb_submit
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
r_int
id|i
comma
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|dib-&gt;init_state
op_amp
id|DIBUSB_STATE_URB_INIT
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|deb_info
c_func
(paren
l_string|&quot;submitting URB no. %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|usb_submit_urb
c_func
(paren
id|dib-&gt;urb_list
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
l_string|&quot;could not submit buffer urb no. %d - get them all back&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|dibusb_urb_kill
c_func
(paren
id|dib
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|dib-&gt;init_state
op_or_assign
id|DIBUSB_STATE_URB_SUBMIT
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_streaming
r_int
id|dibusb_streaming
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
comma
r_int
id|onoff
)paren
(brace
r_if
c_cond
(paren
id|onoff
)paren
id|dibusb_urb_submit
c_func
(paren
id|dib
)paren
suffix:semicolon
r_else
id|dibusb_urb_kill
c_func
(paren
id|dib
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dib-&gt;dibdev-&gt;dev_cl-&gt;id
)paren
(brace
r_case
id|DIBUSB2_0
suffix:colon
r_case
id|DIBUSB2_0B
suffix:colon
r_case
id|NOVAT_USB2
suffix:colon
r_case
id|UMT2_0
suffix:colon
r_if
c_cond
(paren
id|onoff
)paren
r_return
id|dibusb_ioctl_cmd
c_func
(paren
id|dib
comma
id|DIBUSB_IOCTL_CMD_ENABLE_STREAM
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_else
r_return
id|dibusb_ioctl_cmd
c_func
(paren
id|dib
comma
id|DIBUSB_IOCTL_CMD_DISABLE_STREAM
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_urb_init
r_int
id|dibusb_urb_init
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
r_int
id|i
comma
id|bufsize
comma
id|def_pid_parse
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * when reloading the driver w/o replugging the device&n;&t; * a timeout occures, this helps&n;&t; */
id|usb_clear_halt
c_func
(paren
id|dib-&gt;udev
comma
id|usb_sndbulkpipe
c_func
(paren
id|dib-&gt;udev
comma
id|dib-&gt;dibdev-&gt;dev_cl-&gt;pipe_cmd
)paren
)paren
suffix:semicolon
id|usb_clear_halt
c_func
(paren
id|dib-&gt;udev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|dib-&gt;udev
comma
id|dib-&gt;dibdev-&gt;dev_cl-&gt;pipe_cmd
)paren
)paren
suffix:semicolon
id|usb_clear_halt
c_func
(paren
id|dib-&gt;udev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|dib-&gt;udev
comma
id|dib-&gt;dibdev-&gt;dev_cl-&gt;pipe_data
)paren
)paren
suffix:semicolon
multiline_comment|/* allocate the array for the data transfer URBs */
id|dib-&gt;urb_list
op_assign
id|kmalloc
c_func
(paren
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_count
op_star
r_sizeof
(paren
r_struct
id|urb
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dib-&gt;urb_list
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
id|dib-&gt;urb_list
comma
l_int|0
comma
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_count
op_star
r_sizeof
(paren
r_struct
id|urb
op_star
)paren
)paren
suffix:semicolon
id|dib-&gt;init_state
op_or_assign
id|DIBUSB_STATE_URB_LIST
suffix:semicolon
id|bufsize
op_assign
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_count
op_star
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_buffer_size
suffix:semicolon
id|deb_info
c_func
(paren
l_string|&quot;allocate %d bytes as buffersize for all URBs&bslash;n&quot;
comma
id|bufsize
)paren
suffix:semicolon
multiline_comment|/* allocate the actual buffer for the URBs */
r_if
c_cond
(paren
(paren
id|dib-&gt;buffer
op_assign
id|pci_alloc_consistent
c_func
(paren
l_int|NULL
comma
id|bufsize
comma
op_amp
id|dib-&gt;dma_handle
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|deb_info
c_func
(paren
l_string|&quot;not enough memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|deb_info
c_func
(paren
l_string|&quot;allocation complete&bslash;n&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dib-&gt;buffer
comma
l_int|0
comma
id|bufsize
)paren
suffix:semicolon
id|dib-&gt;init_state
op_or_assign
id|DIBUSB_STATE_URB_BUF
suffix:semicolon
multiline_comment|/* allocate and submit the URBs */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|dib-&gt;urb_list
(braket
id|i
)braket
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|usb_fill_bulk_urb
c_func
(paren
id|dib-&gt;urb_list
(braket
id|i
)braket
comma
id|dib-&gt;udev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|dib-&gt;udev
comma
id|dib-&gt;dibdev-&gt;dev_cl-&gt;pipe_data
)paren
comma
op_amp
id|dib-&gt;buffer
(braket
id|i
op_star
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_buffer_size
)braket
comma
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_buffer_size
comma
id|dibusb_urb_complete
comma
id|dib
)paren
suffix:semicolon
id|dib-&gt;urb_list
(braket
id|i
)braket
op_member_access_from_pointer
id|transfer_flags
op_assign
l_int|0
suffix:semicolon
id|dib-&gt;init_state
op_or_assign
id|DIBUSB_STATE_URB_INIT
suffix:semicolon
)brace
multiline_comment|/* dib-&gt;pid_parse here contains the value of the module parameter */
multiline_comment|/* decide if pid parsing can be deactivated:&n;&t; * is possible (by device type) and wanted (by user)&n;&t; */
r_switch
c_cond
(paren
id|dib-&gt;dibdev-&gt;dev_cl-&gt;id
)paren
(brace
r_case
id|DIBUSB2_0
suffix:colon
r_case
id|DIBUSB2_0B
suffix:colon
r_if
c_cond
(paren
id|dib-&gt;udev-&gt;speed
op_eq
id|USB_SPEED_HIGH
op_logical_and
op_logical_neg
id|dib-&gt;pid_parse
)paren
(brace
id|def_pid_parse
op_assign
l_int|0
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;running at HIGH speed, will deliver the complete TS.&quot;
)paren
suffix:semicolon
)brace
r_else
id|info
c_func
(paren
l_string|&quot;will use pid_parsing.&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* from here on it contains the device and user decision */
id|dib-&gt;pid_parse
op_assign
id|def_pid_parse
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_urb_exit
r_int
id|dibusb_urb_exit
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
r_int
id|i
suffix:semicolon
id|dibusb_urb_kill
c_func
(paren
id|dib
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dib-&gt;init_state
op_amp
id|DIBUSB_STATE_URB_LIST
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dib-&gt;urb_list
(braket
id|i
)braket
op_ne
l_int|NULL
)paren
(brace
id|deb_info
c_func
(paren
l_string|&quot;freeing URB no. %d.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* free the URBs */
id|usb_free_urb
c_func
(paren
id|dib-&gt;urb_list
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* free the urb array */
id|kfree
c_func
(paren
id|dib-&gt;urb_list
)paren
suffix:semicolon
id|dib-&gt;init_state
op_and_assign
op_complement
id|DIBUSB_STATE_URB_LIST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dib-&gt;init_state
op_amp
id|DIBUSB_STATE_URB_BUF
)paren
id|pci_free_consistent
c_func
(paren
l_int|NULL
comma
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_buffer_size
op_star
id|dib-&gt;dibdev-&gt;dev_cl-&gt;urb_count
comma
id|dib-&gt;buffer
comma
id|dib-&gt;dma_handle
)paren
suffix:semicolon
id|dib-&gt;init_state
op_and_assign
op_complement
id|DIBUSB_STATE_URB_BUF
suffix:semicolon
id|dib-&gt;init_state
op_and_assign
op_complement
id|DIBUSB_STATE_URB_INIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
