multiline_comment|/*&n;   Driver for the Microtune 7202D Frontend&n;*/
multiline_comment|/*&n;   This driver needs a copy of the Avermedia firmware. The version tested&n;   is part of the Avermedia DVB-T 1.3.26.3 Application. If the software is&n;   installed in Windows the file will be in the /Program Files/AVerTV DVB-T/&n;   directory and is called sc_main.mc. Alternatively it can &quot;extracted&quot; from&n;   the install cab files. Copy this file to &squot;/usr/lib/hotplug/firmware/sc_main.mc&squot;.&n;   With this version of the file the first 10 bytes are discarded and the&n;   next 0x4000 loaded. This may change in future versions.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;dvb_functions.h&quot;
macro_line|#ifndef DVB_SP887X_FIRMWARE_FILE
DECL|macro|DVB_SP887X_FIRMWARE_FILE
mdefine_line|#define DVB_SP887X_FIRMWARE_FILE &quot;/usr/lib/hotplug/firmware/sc_main.mc&quot;
macro_line|#endif
DECL|variable|sp887x_firmware
r_static
r_char
op_star
id|sp887x_firmware
op_assign
id|DVB_SP887X_FIRMWARE_FILE
suffix:semicolon
macro_line|#if 0
mdefine_line|#define dprintk(x...) printk(x)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(x...)
macro_line|#endif
macro_line|#if 0
mdefine_line|#define LOG(dir,addr,buf,len) &t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int i;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;%s (%02x):&quot;, dir, addr &amp; 0xff);&t;&t;&bslash;&n;&t;&t;for (i=0; i&lt;len; i++)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(&quot; 0x%02x,&quot;, buf[i] &amp; 0xff);&t;&bslash;&n;&t;&t;printk(&quot;&bslash;n&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|LOG
mdefine_line|#define LOG(dir,addr,buf,len)
macro_line|#endif
r_static
DECL|variable|sp887x_info
r_struct
id|dvb_frontend_info
id|sp887x_info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Microtune MT7202DTF&quot;
comma
dot
id|type
op_assign
id|FE_OFDM
comma
dot
id|frequency_min
op_assign
l_int|50500000
comma
dot
id|frequency_max
op_assign
l_int|858000000
comma
dot
id|frequency_stepsize
op_assign
l_int|166666
comma
dot
id|caps
op_assign
id|FE_CAN_FEC_1_2
op_or
id|FE_CAN_FEC_2_3
op_or
id|FE_CAN_FEC_3_4
op_or
id|FE_CAN_FEC_5_6
op_or
id|FE_CAN_FEC_7_8
op_or
id|FE_CAN_FEC_AUTO
op_or
id|FE_CAN_QPSK
op_or
id|FE_CAN_QAM_16
op_or
id|FE_CAN_QAM_64
op_or
id|FE_CAN_RECOVER
)brace
suffix:semicolon
DECL|variable|errno
r_static
r_int
id|errno
suffix:semicolon
r_static
DECL|function|i2c_writebytes
r_int
id|i2c_writebytes
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
id|addr
comma
id|u8
op_star
id|buf
comma
id|u8
id|len
)paren
(brace
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|fe-&gt;i2c
suffix:semicolon
r_struct
id|i2c_msg
id|msg
op_assign
(brace
dot
id|addr
op_assign
id|addr
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|buf
comma
dot
id|len
op_assign
id|len
)brace
suffix:semicolon
r_int
id|err
suffix:semicolon
id|LOG
c_func
(paren
l_string|&quot;i2c_writebytes&quot;
comma
id|msg.addr
comma
id|msg.buf
comma
id|msg.len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|i2c-&gt;xfer
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
(brace
id|printk
(paren
l_string|&quot;%s: i2c write error (addr %02x, err == %i)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|addr
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|sp887x_writereg
r_int
id|sp887x_writereg
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u16
id|reg
comma
id|u16
id|data
)paren
(brace
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|fe-&gt;i2c
suffix:semicolon
id|u8
id|b0
(braket
)braket
op_assign
(brace
id|reg
op_rshift
l_int|8
comma
id|reg
op_amp
l_int|0xff
comma
id|data
op_rshift
l_int|8
comma
id|data
op_amp
l_int|0xff
)brace
suffix:semicolon
r_struct
id|i2c_msg
id|msg
op_assign
(brace
dot
id|addr
op_assign
l_int|0x70
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|b0
comma
dot
id|len
op_assign
l_int|4
)brace
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|LOG
c_func
(paren
l_string|&quot;sp887x_writereg&quot;
comma
id|msg.addr
comma
id|msg.buf
comma
id|msg.len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
(brace
multiline_comment|/**&n;&t;&t; *  in case of soft reset we ignore ACK errors...&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_eq
l_int|0xf1a
op_logical_and
id|data
op_eq
l_int|0x000
op_logical_and
(paren
id|ret
op_eq
op_minus
id|EREMOTEIO
op_logical_or
id|ret
op_eq
op_minus
id|EFAULT
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: writereg error &quot;
l_string|&quot;(reg %03x, data %03x, ret == %i)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|reg
op_amp
l_int|0xffff
comma
id|data
op_amp
l_int|0xffff
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|sp887x_readreg
id|u16
id|sp887x_readreg
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u16
id|reg
)paren
(brace
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|fe-&gt;i2c
suffix:semicolon
id|u8
id|b0
(braket
)braket
op_assign
(brace
id|reg
op_rshift
l_int|8
comma
id|reg
op_amp
l_int|0xff
)brace
suffix:semicolon
id|u8
id|b1
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|i2c_msg
id|msg
(braket
)braket
op_assign
(brace
(brace
dot
id|addr
op_assign
l_int|0x70
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|b0
comma
dot
id|len
op_assign
l_int|2
)brace
comma
(brace
dot
id|addr
op_assign
l_int|0x70
comma
dot
id|flags
op_assign
id|I2C_M_RD
comma
dot
id|buf
op_assign
id|b1
comma
dot
id|len
op_assign
l_int|2
)brace
)brace
suffix:semicolon
id|LOG
c_func
(paren
l_string|&quot;sp887x_readreg (w)&quot;
comma
id|msg
(braket
l_int|0
)braket
dot
id|addr
comma
id|msg
(braket
l_int|0
)braket
dot
id|buf
comma
id|msg
(braket
l_int|0
)braket
dot
id|len
)paren
suffix:semicolon
id|LOG
c_func
(paren
l_string|&quot;sp887x_readreg (r)&quot;
comma
id|msg
(braket
l_int|1
)braket
dot
id|addr
comma
id|msg
(braket
l_int|1
)braket
dot
id|buf
comma
id|msg
(braket
l_int|1
)braket
dot
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
id|msg
comma
l_int|2
)paren
)paren
op_ne
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;%s: readreg error (ret == %i)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ret
)paren
suffix:semicolon
r_return
(paren
(paren
(paren
id|b1
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
id|b1
(braket
l_int|1
)braket
)paren
op_amp
l_int|0xfff
)paren
suffix:semicolon
)brace
r_static
DECL|function|sp887x_microcontroller_stop
r_void
id|sp887x_microcontroller_stop
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xf08
comma
l_int|0x000
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xf09
comma
l_int|0x000
)paren
suffix:semicolon
multiline_comment|/* microcontroller STOP */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xf00
comma
l_int|0x000
)paren
suffix:semicolon
)brace
r_static
DECL|function|sp887x_microcontroller_start
r_void
id|sp887x_microcontroller_start
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xf08
comma
l_int|0x000
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xf09
comma
l_int|0x000
)paren
suffix:semicolon
multiline_comment|/* microcontroller START */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xf00
comma
l_int|0x001
)paren
suffix:semicolon
)brace
r_static
DECL|function|sp887x_setup_agc
r_void
id|sp887x_setup_agc
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
multiline_comment|/* setup AGC parameters */
id|dprintk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x33c
comma
l_int|0x054
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x33b
comma
l_int|0x04c
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x328
comma
l_int|0x000
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x327
comma
l_int|0x005
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x326
comma
l_int|0x001
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x325
comma
l_int|0x001
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x324
comma
l_int|0x001
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x318
comma
l_int|0x050
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x317
comma
l_int|0x3fe
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x316
comma
l_int|0x001
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x313
comma
l_int|0x005
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x312
comma
l_int|0x002
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x306
comma
l_int|0x000
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x303
comma
l_int|0x000
)paren
suffix:semicolon
)brace
DECL|macro|BLOCKSIZE
mdefine_line|#define BLOCKSIZE 30
multiline_comment|/**&n; *  load firmware and setup MPEG interface...&n; */
r_static
DECL|function|sp887x_initial_setup
r_int
id|sp887x_initial_setup
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
id|u8
id|buf
(braket
id|BLOCKSIZE
op_plus
l_int|2
)braket
suffix:semicolon
r_int
r_char
op_star
id|firmware
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_int
id|filesize
suffix:semicolon
r_int
id|fw_size
suffix:semicolon
id|mm_segment_t
id|fs
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* soft reset */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xf1a
comma
l_int|0x000
)paren
suffix:semicolon
id|sp887x_microcontroller_stop
(paren
id|fe
)paren
suffix:semicolon
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
singleline_comment|// Load the firmware
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|sys_open
c_func
(paren
id|sp887x_firmware
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Unable to open firmware %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|sp887x_firmware
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|filesize
op_assign
id|sys_lseek
c_func
(paren
id|fd
comma
l_int|0L
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filesize
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Firmware %s is empty&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|sp887x_firmware
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|fw_size
op_assign
l_int|0x4000
suffix:semicolon
singleline_comment|// allocate buffer for it
id|firmware
op_assign
id|vmalloc
c_func
(paren
id|fw_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|firmware
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Out of memory loading firmware&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
singleline_comment|// read it!
singleline_comment|// read the first 16384 bytes from the file
singleline_comment|// ignore the first 10 bytes
id|sys_lseek
c_func
(paren
id|fd
comma
l_int|10
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sys_read
c_func
(paren
id|fd
comma
id|firmware
comma
id|fw_size
)paren
op_ne
id|fw_size
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Failed to read firmware&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|firmware
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: firmware upload... &quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* setup write pointer to -1 (end of memory) */
multiline_comment|/* bit 0x8000 in address is set to enable 13bit mode */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x8f08
comma
l_int|0x1fff
)paren
suffix:semicolon
multiline_comment|/* dummy write (wrap around to start of memory) */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x8f0a
comma
l_int|0x0000
)paren
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
id|fw_size
suffix:semicolon
id|i
op_add_assign
id|BLOCKSIZE
)paren
(brace
r_int
id|c
op_assign
id|BLOCKSIZE
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|i
op_plus
id|c
OG
id|fw_size
)paren
id|c
op_assign
id|fw_size
op_minus
id|i
suffix:semicolon
multiline_comment|/* bit 0x8000 in address is set to enable 13bit mode */
multiline_comment|/* bit 0x4000 enables multibyte read/write transfers */
multiline_comment|/* write register is 0xf0a */
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0xcf
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x0a
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|buf
(braket
l_int|2
)braket
comma
id|firmware
op_plus
id|i
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|i2c_writebytes
(paren
id|fe
comma
l_int|0x70
comma
id|buf
comma
id|c
op_plus
l_int|2
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;failed.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: i2c error (err == %i)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|err
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|firmware
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
id|vfree
c_func
(paren
id|firmware
)paren
suffix:semicolon
multiline_comment|/* don&squot;t write RS bytes between packets */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc13
comma
l_int|0x001
)paren
suffix:semicolon
multiline_comment|/* suppress clock if (!data_valid) */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc14
comma
l_int|0x000
)paren
suffix:semicolon
multiline_comment|/* setup MPEG interface... */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc1a
comma
l_int|0x872
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc1b
comma
l_int|0x001
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc1c
comma
l_int|0x000
)paren
suffix:semicolon
multiline_comment|/* parallel mode (serial mode == 1) */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc1a
comma
l_int|0x871
)paren
suffix:semicolon
multiline_comment|/* ADC mode, 2 for MT8872, 3 for SP8870/SP8871 */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x301
comma
l_int|0x002
)paren
suffix:semicolon
id|sp887x_setup_agc
c_func
(paren
id|fe
)paren
suffix:semicolon
multiline_comment|/* bit 0x010: enable data valid signal */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xd00
comma
l_int|0x010
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x0d1
comma
l_int|0x000
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *  returns the actual tuned center frequency which can be used&n; *  to initialise the AFC registers&n; */
r_static
DECL|function|tsa5060_setup_pll
r_int
id|tsa5060_setup_pll
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
id|freq
)paren
(brace
id|u8
id|cfg
comma
id|cpump
comma
id|band_select
suffix:semicolon
id|u8
id|buf
(braket
l_int|4
)braket
suffix:semicolon
id|u32
id|div
suffix:semicolon
id|div
op_assign
(paren
l_int|36000000
op_plus
id|freq
op_plus
l_int|83333
)paren
op_div
l_int|166666
suffix:semicolon
id|cfg
op_assign
l_int|0x88
suffix:semicolon
id|cpump
op_assign
id|freq
OL
l_int|175000000
ques
c_cond
l_int|2
suffix:colon
id|freq
OL
l_int|390000000
ques
c_cond
l_int|1
suffix:colon
id|freq
OL
l_int|470000000
ques
c_cond
l_int|2
suffix:colon
id|freq
OL
l_int|750000000
ques
c_cond
l_int|2
suffix:colon
l_int|3
suffix:semicolon
id|band_select
op_assign
id|freq
OL
l_int|175000000
ques
c_cond
l_int|0x0e
suffix:colon
id|freq
OL
l_int|470000000
ques
c_cond
l_int|0x05
suffix:colon
l_int|0x03
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
(paren
id|div
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
(paren
(paren
id|div
op_rshift
l_int|10
)paren
op_amp
l_int|0x60
)paren
op_or
id|cfg
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
id|cpump
op_or
id|band_select
suffix:semicolon
multiline_comment|/* open i2c gate for PLL message transmission... */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x206
comma
l_int|0x001
)paren
suffix:semicolon
id|i2c_writebytes
c_func
(paren
id|fe
comma
l_int|0x60
comma
id|buf
comma
l_int|4
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x206
comma
l_int|0x000
)paren
suffix:semicolon
r_return
(paren
id|div
op_star
l_int|166666
op_minus
l_int|36000000
)paren
suffix:semicolon
)brace
r_static
DECL|function|configure_reg0xc05
r_int
id|configure_reg0xc05
(paren
r_struct
id|dvb_frontend_parameters
op_star
id|p
comma
id|u16
op_star
id|reg0xc05
)paren
(brace
r_int
id|known_parameters
op_assign
l_int|1
suffix:semicolon
op_star
id|reg0xc05
op_assign
l_int|0x000
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;u.ofdm.constellation
)paren
(brace
r_case
id|QPSK
suffix:colon
r_break
suffix:semicolon
r_case
id|QAM_16
suffix:colon
op_star
id|reg0xc05
op_or_assign
(paren
l_int|1
op_lshift
l_int|10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_64
suffix:colon
op_star
id|reg0xc05
op_or_assign
(paren
l_int|2
op_lshift
l_int|10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_AUTO
suffix:colon
id|known_parameters
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;u.ofdm.hierarchy_information
)paren
(brace
r_case
id|HIERARCHY_NONE
suffix:colon
r_break
suffix:semicolon
r_case
id|HIERARCHY_1
suffix:colon
op_star
id|reg0xc05
op_or_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HIERARCHY_2
suffix:colon
op_star
id|reg0xc05
op_or_assign
(paren
l_int|2
op_lshift
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HIERARCHY_4
suffix:colon
op_star
id|reg0xc05
op_or_assign
(paren
l_int|3
op_lshift
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HIERARCHY_AUTO
suffix:colon
id|known_parameters
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;u.ofdm.code_rate_HP
)paren
(brace
r_case
id|FEC_1_2
suffix:colon
r_break
suffix:semicolon
r_case
id|FEC_2_3
suffix:colon
op_star
id|reg0xc05
op_or_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_3_4
suffix:colon
op_star
id|reg0xc05
op_or_assign
(paren
l_int|2
op_lshift
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_5_6
suffix:colon
op_star
id|reg0xc05
op_or_assign
(paren
l_int|3
op_lshift
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_7_8
suffix:colon
op_star
id|reg0xc05
op_or_assign
(paren
l_int|4
op_lshift
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_AUTO
suffix:colon
id|known_parameters
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|known_parameters
)paren
op_star
id|reg0xc05
op_or_assign
(paren
l_int|2
op_lshift
l_int|1
)paren
suffix:semicolon
multiline_comment|/* use specified parameters */
r_else
op_star
id|reg0xc05
op_or_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
suffix:semicolon
multiline_comment|/* enable autoprobing */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *  estimates division of two 24bit numbers,&n; *  derived from the ves1820/stv0299 driver code&n; */
r_static
DECL|function|divide
r_void
id|divide
(paren
r_int
id|n
comma
r_int
id|d
comma
r_int
op_star
id|quotient_i
comma
r_int
op_star
id|quotient_f
)paren
(brace
r_int
r_int
id|q
comma
id|r
suffix:semicolon
id|r
op_assign
(paren
id|n
op_mod
id|d
)paren
op_lshift
l_int|8
suffix:semicolon
id|q
op_assign
(paren
id|r
op_div
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
id|quotient_i
)paren
op_star
id|quotient_i
op_assign
id|q
suffix:semicolon
r_if
c_cond
(paren
id|quotient_f
)paren
(brace
id|r
op_assign
(paren
id|r
op_mod
id|d
)paren
op_lshift
l_int|8
suffix:semicolon
id|q
op_assign
(paren
id|q
op_lshift
l_int|8
)paren
op_or
(paren
id|r
op_div
id|d
)paren
suffix:semicolon
id|r
op_assign
(paren
id|r
op_mod
id|d
)paren
op_lshift
l_int|8
suffix:semicolon
op_star
id|quotient_f
op_assign
(paren
id|q
op_lshift
l_int|8
)paren
op_or
(paren
id|r
op_div
id|d
)paren
suffix:semicolon
)brace
)brace
r_static
DECL|function|sp887x_correct_offsets
r_void
id|sp887x_correct_offsets
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_frontend_parameters
op_star
id|p
comma
r_int
id|actual_freq
)paren
(brace
r_static
r_const
id|u32
id|srate_correction
(braket
)braket
op_assign
(brace
l_int|1879617
comma
l_int|4544878
comma
l_int|8098561
)brace
suffix:semicolon
r_int
id|bw_index
op_assign
id|p-&gt;u.ofdm.bandwidth
op_minus
id|BANDWIDTH_8_MHZ
suffix:semicolon
r_int
id|freq_offset
op_assign
id|actual_freq
op_minus
id|p-&gt;frequency
suffix:semicolon
r_int
id|sysclock
op_assign
l_int|61003
suffix:semicolon
singleline_comment|//[kHz]
r_int
id|ifreq
op_assign
l_int|36000000
suffix:semicolon
r_int
id|freq
suffix:semicolon
r_int
id|frequency_shift
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;inversion
op_eq
id|INVERSION_ON
)paren
id|freq
op_assign
id|ifreq
op_minus
id|freq_offset
suffix:semicolon
r_else
id|freq
op_assign
id|ifreq
op_plus
id|freq_offset
suffix:semicolon
id|divide
c_func
(paren
id|freq
op_div
l_int|333
comma
id|sysclock
comma
l_int|NULL
comma
op_amp
id|frequency_shift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;inversion
op_eq
id|INVERSION_ON
)paren
id|frequency_shift
op_assign
op_minus
id|frequency_shift
suffix:semicolon
multiline_comment|/* sample rate correction */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x319
comma
id|srate_correction
(braket
id|bw_index
)braket
op_rshift
l_int|12
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x31a
comma
id|srate_correction
(braket
id|bw_index
)braket
op_amp
l_int|0xfff
)paren
suffix:semicolon
multiline_comment|/* carrier offset correction */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x309
comma
id|frequency_shift
op_rshift
l_int|12
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x30a
comma
id|frequency_shift
op_amp
l_int|0xfff
)paren
suffix:semicolon
)brace
r_static
DECL|function|sp887x_setup_frontend_parameters
r_int
id|sp887x_setup_frontend_parameters
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_frontend_parameters
op_star
id|p
)paren
(brace
r_int
id|actual_freq
comma
id|err
suffix:semicolon
id|u16
id|val
comma
id|reg0xc05
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;u.ofdm.bandwidth
op_ne
id|BANDWIDTH_8_MHZ
op_logical_and
id|p-&gt;u.ofdm.bandwidth
op_ne
id|BANDWIDTH_7_MHZ
op_logical_and
id|p-&gt;u.ofdm.bandwidth
op_ne
id|BANDWIDTH_6_MHZ
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|configure_reg0xc05
c_func
(paren
id|p
comma
op_amp
id|reg0xc05
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|sp887x_microcontroller_stop
c_func
(paren
id|fe
)paren
suffix:semicolon
id|actual_freq
op_assign
id|tsa5060_setup_pll
c_func
(paren
id|fe
comma
id|p-&gt;frequency
)paren
suffix:semicolon
multiline_comment|/* read status reg in order to clear pending irqs */
id|sp887x_readreg
c_func
(paren
id|fe
comma
l_int|0x200
)paren
suffix:semicolon
id|sp887x_correct_offsets
c_func
(paren
id|fe
comma
id|p
comma
id|actual_freq
)paren
suffix:semicolon
multiline_comment|/* filter for 6/7/8 Mhz channel */
r_if
c_cond
(paren
id|p-&gt;u.ofdm.bandwidth
op_eq
id|BANDWIDTH_6_MHZ
)paren
id|val
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p-&gt;u.ofdm.bandwidth
op_eq
id|BANDWIDTH_7_MHZ
)paren
id|val
op_assign
l_int|1
suffix:semicolon
r_else
id|val
op_assign
l_int|0
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x311
comma
id|val
)paren
suffix:semicolon
multiline_comment|/* scan order: 2k first = 0, 8k first = 1 */
r_if
c_cond
(paren
id|p-&gt;u.ofdm.transmission_mode
op_eq
id|TRANSMISSION_MODE_2K
)paren
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x338
comma
l_int|0x000
)paren
suffix:semicolon
r_else
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0x338
comma
l_int|0x001
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc05
comma
id|reg0xc05
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;u.ofdm.bandwidth
op_eq
id|BANDWIDTH_6_MHZ
)paren
id|val
op_assign
l_int|2
op_lshift
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p-&gt;u.ofdm.bandwidth
op_eq
id|BANDWIDTH_7_MHZ
)paren
id|val
op_assign
l_int|3
op_lshift
l_int|3
suffix:semicolon
r_else
id|val
op_assign
l_int|0
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* enable OFDM and SAW bits as lock indicators in sync register 0xf17,&n;&t; * optimize algorithm for given bandwidth...&n;&t; */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xf14
comma
l_int|0x160
op_or
id|val
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xf15
comma
l_int|0x000
)paren
suffix:semicolon
id|sp887x_microcontroller_start
c_func
(paren
id|fe
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|sp887x_ioctl
r_int
id|sp887x_ioctl
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FE_GET_INFO
suffix:colon
id|memcpy
(paren
id|arg
comma
op_amp
id|sp887x_info
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_info
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_READ_STATUS
suffix:colon
(brace
id|u16
id|snr12
op_assign
id|sp887x_readreg
c_func
(paren
id|fe
comma
l_int|0xf16
)paren
suffix:semicolon
id|u16
id|sync0x200
op_assign
id|sp887x_readreg
c_func
(paren
id|fe
comma
l_int|0x200
)paren
suffix:semicolon
id|u16
id|sync0xf17
op_assign
id|sp887x_readreg
c_func
(paren
id|fe
comma
l_int|0xf17
)paren
suffix:semicolon
id|fe_status_t
op_star
id|status
op_assign
id|arg
suffix:semicolon
op_star
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|snr12
OG
l_int|0x00f
)paren
op_star
id|status
op_or_assign
id|FE_HAS_SIGNAL
suffix:semicolon
singleline_comment|//if (sync0x200 &amp; 0x004)
singleline_comment|//&t;*status |= FE_HAS_SYNC | FE_HAS_CARRIER;
singleline_comment|//if (sync0x200 &amp; 0x008)
singleline_comment|//&t;*status |= FE_HAS_VITERBI;
r_if
c_cond
(paren
(paren
id|sync0xf17
op_amp
l_int|0x00f
)paren
op_eq
l_int|0x002
)paren
(brace
op_star
id|status
op_or_assign
id|FE_HAS_LOCK
suffix:semicolon
op_star
id|status
op_or_assign
id|FE_HAS_VITERBI
op_or
id|FE_HAS_SYNC
op_or
id|FE_HAS_CARRIER
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sync0x200
op_amp
l_int|0x001
)paren
(brace
multiline_comment|/* tuner adjustment requested...*/
r_int
id|steps
op_assign
(paren
id|sync0x200
op_rshift
l_int|4
)paren
op_amp
l_int|0x00f
suffix:semicolon
r_if
c_cond
(paren
id|steps
op_amp
l_int|0x008
)paren
id|steps
op_assign
op_minus
id|steps
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;sp887x: implement tuner adjustment (%+i steps)!!&bslash;n&quot;
comma
id|steps
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_BER
suffix:colon
(brace
id|u32
op_star
id|ber
op_assign
id|arg
suffix:semicolon
op_star
id|ber
op_assign
(paren
id|sp887x_readreg
c_func
(paren
id|fe
comma
l_int|0xc08
)paren
op_amp
l_int|0x3f
)paren
op_or
(paren
id|sp887x_readreg
c_func
(paren
id|fe
comma
l_int|0xc07
)paren
op_lshift
l_int|6
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc08
comma
l_int|0x000
)paren
suffix:semicolon
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc07
comma
l_int|0x000
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ber
op_ge
l_int|0x3fff0
)paren
op_star
id|ber
op_assign
op_complement
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SIGNAL_STRENGTH
suffix:colon
singleline_comment|// FIXME: correct registers ?
(brace
id|u16
id|snr12
op_assign
id|sp887x_readreg
c_func
(paren
id|fe
comma
l_int|0xf16
)paren
suffix:semicolon
id|u32
id|signal
op_assign
l_int|3
op_star
(paren
id|snr12
op_lshift
l_int|4
)paren
suffix:semicolon
op_star
(paren
(paren
id|u16
op_star
)paren
id|arg
)paren
op_assign
(paren
id|signal
OL
l_int|0xffff
)paren
ques
c_cond
id|signal
suffix:colon
l_int|0xffff
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SNR
suffix:colon
(brace
id|u16
id|snr12
op_assign
id|sp887x_readreg
c_func
(paren
id|fe
comma
l_int|0xf16
)paren
suffix:semicolon
op_star
(paren
id|u16
op_star
)paren
id|arg
op_assign
(paren
id|snr12
op_lshift
l_int|4
)paren
op_or
(paren
id|snr12
op_rshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_UNCORRECTED_BLOCKS
suffix:colon
(brace
id|u32
op_star
id|ublocks
op_assign
(paren
id|u32
op_star
)paren
id|arg
suffix:semicolon
op_star
id|ublocks
op_assign
id|sp887x_readreg
c_func
(paren
id|fe
comma
l_int|0xc0c
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ublocks
op_eq
l_int|0xfff
)paren
op_star
id|ublocks
op_assign
op_complement
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_SET_FRONTEND
suffix:colon
r_return
id|sp887x_setup_frontend_parameters
c_func
(paren
id|fe
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_GET_FRONTEND
suffix:colon
singleline_comment|// FIXME: read known values back from Hardware...
r_break
suffix:semicolon
r_case
id|FE_SLEEP
suffix:colon
multiline_comment|/* tristate TS output and disable interface pins */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc18
comma
l_int|0x000
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_INIT
suffix:colon
r_if
c_cond
(paren
id|fe-&gt;data
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* first time initialisation... */
id|fe-&gt;data
op_assign
(paren
r_void
op_star
)paren
op_complement
l_int|0
suffix:semicolon
id|sp887x_initial_setup
(paren
id|fe
)paren
suffix:semicolon
)brace
multiline_comment|/* enable TS output and interface pins */
id|sp887x_writereg
c_func
(paren
id|fe
comma
l_int|0xc18
comma
l_int|0x00d
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_GET_TUNE_SETTINGS
suffix:colon
(brace
r_struct
id|dvb_frontend_tune_settings
op_star
id|fesettings
op_assign
(paren
r_struct
id|dvb_frontend_tune_settings
op_star
)paren
id|arg
suffix:semicolon
id|fesettings-&gt;min_delay_ms
op_assign
l_int|50
suffix:semicolon
id|fesettings-&gt;step_size
op_assign
l_int|0
suffix:semicolon
id|fesettings-&gt;max_drift
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|sp887x_attach
r_int
id|sp887x_attach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_void
op_star
op_star
id|data
)paren
(brace
r_struct
id|i2c_msg
id|msg
op_assign
(brace
dot
id|addr
op_assign
l_int|0x70
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
l_int|NULL
comma
dot
id|len
op_assign
l_int|0
)brace
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c-&gt;xfer
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
op_ne
l_int|1
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|dvb_register_frontend
(paren
id|sp887x_ioctl
comma
id|i2c
comma
l_int|NULL
comma
op_amp
id|sp887x_info
)paren
suffix:semicolon
)brace
r_static
DECL|function|sp887x_detach
r_void
id|sp887x_detach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_void
op_star
id|data
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dvb_unregister_frontend
(paren
id|sp887x_ioctl
comma
id|i2c
)paren
suffix:semicolon
)brace
r_static
DECL|function|init_sp887x
r_int
id|__init
id|init_sp887x
(paren
r_void
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|dvb_register_i2c_device
(paren
l_int|NULL
comma
id|sp887x_attach
comma
id|sp887x_detach
)paren
suffix:semicolon
)brace
r_static
DECL|function|exit_sp887x
r_void
id|__exit
id|exit_sp887x
(paren
r_void
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dvb_unregister_i2c_device
(paren
id|sp887x_attach
)paren
suffix:semicolon
)brace
DECL|variable|init_sp887x
id|module_init
c_func
(paren
id|init_sp887x
)paren
suffix:semicolon
DECL|variable|exit_sp887x
id|module_exit
c_func
(paren
id|exit_sp887x
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;sp887x DVB-T demodulator driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
