multiline_comment|/* &n; *  Parallel SCSI (SPI) transport specific attributes exported to sysfs.&n; *&n; *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;scsi/scsi_request.h&gt;
macro_line|#include &lt;scsi/scsi_transport.h&gt;
macro_line|#include &lt;scsi/scsi_transport_spi.h&gt;
DECL|macro|SPI_PRINTK
mdefine_line|#define SPI_PRINTK(x, l, f, a...)&t;printk(l &quot;scsi(%d:%d:%d:%d): &quot; f, (x)-&gt;host-&gt;host_no, (x)-&gt;channel, (x)-&gt;id, (x)-&gt;lun , ##a)
r_static
r_void
id|transport_class_release
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
suffix:semicolon
DECL|macro|SPI_NUM_ATTRS
mdefine_line|#define SPI_NUM_ATTRS 10&t;/* increase this if you add attributes */
DECL|macro|SPI_OTHER_ATTRS
mdefine_line|#define SPI_OTHER_ATTRS 1&t;/* Increase this if you add &quot;always&n;&t;&t;&t;&t; * on&quot; attributes */
DECL|macro|SPI_MAX_ECHO_BUFFER_SIZE
mdefine_line|#define SPI_MAX_ECHO_BUFFER_SIZE&t;4096
multiline_comment|/* Private data accessors (keep these out of the header file) */
DECL|macro|spi_dv_pending
mdefine_line|#define spi_dv_pending(x) (((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;dv_pending)
DECL|macro|spi_dv_sem
mdefine_line|#define spi_dv_sem(x) (((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;dv_sem)
DECL|struct|spi_internal
r_struct
id|spi_internal
(brace
DECL|member|t
r_struct
id|scsi_transport_template
id|t
suffix:semicolon
DECL|member|f
r_struct
id|spi_function_template
op_star
id|f
suffix:semicolon
multiline_comment|/* The actual attributes */
DECL|member|private_attrs
r_struct
id|class_device_attribute
id|private_attrs
(braket
id|SPI_NUM_ATTRS
)braket
suffix:semicolon
multiline_comment|/* The array of null terminated pointers to attributes &n;&t; * needed by scsi_sysfs.c */
DECL|member|attrs
r_struct
id|class_device_attribute
op_star
id|attrs
(braket
id|SPI_NUM_ATTRS
op_plus
id|SPI_OTHER_ATTRS
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_spi_internal
mdefine_line|#define to_spi_internal(tmpl)&t;container_of(tmpl, struct spi_internal, t)
DECL|variable|ppr_to_ns
r_static
r_const
r_char
op_star
r_const
id|ppr_to_ns
(braket
)braket
op_assign
(brace
multiline_comment|/* The PPR values 0-6 are reserved, fill them in when&n;&t; * the committee defines them */
l_int|NULL
comma
multiline_comment|/* 0x00 */
l_int|NULL
comma
multiline_comment|/* 0x01 */
l_int|NULL
comma
multiline_comment|/* 0x02 */
l_int|NULL
comma
multiline_comment|/* 0x03 */
l_int|NULL
comma
multiline_comment|/* 0x04 */
l_int|NULL
comma
multiline_comment|/* 0x05 */
l_int|NULL
comma
multiline_comment|/* 0x06 */
l_string|&quot;3.125&quot;
comma
multiline_comment|/* 0x07 */
l_string|&quot;6.25&quot;
comma
multiline_comment|/* 0x08 */
l_string|&quot;12.5&quot;
comma
multiline_comment|/* 0x09 */
l_string|&quot;25&quot;
comma
multiline_comment|/* 0x0a */
l_string|&quot;30.3&quot;
comma
multiline_comment|/* 0x0b */
l_string|&quot;50&quot;
comma
multiline_comment|/* 0x0c */
)brace
suffix:semicolon
multiline_comment|/* The PPR values at which you calculate the period in ns by multiplying&n; * by 4 */
DECL|macro|SPI_STATIC_PPR
mdefine_line|#define SPI_STATIC_PPR&t;0x0c
DECL|variable|spi_transport_class
r_struct
r_class
id|spi_transport_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;spi_transport&quot;
comma
dot
id|release
op_assign
id|transport_class_release
comma
)brace
suffix:semicolon
DECL|function|spi_transport_init
r_static
id|__init
r_int
id|spi_transport_init
c_func
(paren
r_void
)paren
(brace
r_return
id|class_register
c_func
(paren
op_amp
id|spi_transport_class
)paren
suffix:semicolon
)brace
DECL|function|spi_transport_exit
r_static
r_void
id|__exit
id|spi_transport_exit
c_func
(paren
r_void
)paren
(brace
id|class_unregister
c_func
(paren
op_amp
id|spi_transport_class
)paren
suffix:semicolon
)brace
DECL|function|spi_setup_transport_attrs
r_static
r_int
id|spi_setup_transport_attrs
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
id|spi_period
c_func
(paren
id|sdev
)paren
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* illegal value */
id|spi_offset
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* async */
id|spi_width
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* narrow */
id|spi_iu
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no IU */
id|spi_dt
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ST */
id|spi_qas
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
id|spi_wr_flow
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
id|spi_rd_strm
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
id|spi_rti
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
id|spi_pcomp_en
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
id|spi_dv_pending
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|spi_dv_sem
c_func
(paren
id|sdev
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|transport_class_release
r_static
r_void
id|transport_class_release
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|transport_class_to_sdev
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|put_device
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
)paren
suffix:semicolon
)brace
DECL|macro|spi_transport_show_function
mdefine_line|#define spi_transport_show_function(field, format_string)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_spi_transport_##field(struct class_device *cdev, char *buf)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_device *sdev = transport_class_to_sdev(cdev);&t;&bslash;&n;&t;struct spi_transport_attrs *tp;&t;&t;&t;&t;&t;&bslash;&n;&t;struct spi_internal *i = to_spi_internal(sdev-&gt;host-&gt;transportt); &bslash;&n;&t;tp = (struct spi_transport_attrs *)&amp;sdev-&gt;transport_data;&t;&bslash;&n;&t;if (i-&gt;f-&gt;get_##field)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;i-&gt;f-&gt;get_##field(sdev);&t;&t;&t;&t;&bslash;&n;&t;return snprintf(buf, 20, format_string, tp-&gt;field);&t;&t;&bslash;&n;}
DECL|macro|spi_transport_store_function
mdefine_line|#define spi_transport_store_function(field, format_string)&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;store_spi_transport_##field(struct class_device *cdev, const char *buf, &bslash;&n;&t;&t;&t;    size_t count)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_device *sdev = transport_class_to_sdev(cdev);&t;&bslash;&n;&t;struct spi_internal *i = to_spi_internal(sdev-&gt;host-&gt;transportt); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;val = simple_strtoul(buf, NULL, 0);&t;&t;&t;&t;&bslash;&n;&t;i-&gt;f-&gt;set_##field(sdev, val);&t;&t;&t;&t;&t;&bslash;&n;&t;return count;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|spi_transport_rd_attr
mdefine_line|#define spi_transport_rd_attr(field, format_string)&t;&t;&t;&bslash;&n;&t;spi_transport_show_function(field, format_string)&t;&t;&bslash;&n;&t;spi_transport_store_function(field, format_string)&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(field, S_IRUGO | S_IWUSR,&t;&t;&t;&bslash;&n;&t;&t;&t; show_spi_transport_##field,&t;&t;&t;&bslash;&n;&t;&t;&t; store_spi_transport_##field);
multiline_comment|/* The Parallel SCSI Tranport Attributes: */
id|spi_transport_rd_attr
c_func
(paren
id|offset
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|spi_transport_rd_attr
c_func
(paren
id|width
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|spi_transport_rd_attr
c_func
(paren
id|iu
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|spi_transport_rd_attr
c_func
(paren
id|dt
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|spi_transport_rd_attr
c_func
(paren
id|qas
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|spi_transport_rd_attr
c_func
(paren
id|wr_flow
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|spi_transport_rd_attr
c_func
(paren
id|rd_strm
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|spi_transport_rd_attr
c_func
(paren
id|rti
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|spi_transport_rd_attr
c_func
(paren
id|pcomp_en
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|store_spi_revalidate
id|store_spi_revalidate
c_func
(paren
r_struct
id|class_device
op_star
id|cdev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|transport_class_to_sdev
c_func
(paren
id|cdev
)paren
suffix:semicolon
id|spi_dv_device
c_func
(paren
id|sdev
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|revalidate
comma
id|S_IWUSR
comma
l_int|NULL
comma
id|store_spi_revalidate
)paren
suffix:semicolon
multiline_comment|/* Translate the period into ns according to the current spec&n; * for SDTR/PPR messages */
DECL|function|show_spi_transport_period
r_static
id|ssize_t
id|show_spi_transport_period
c_func
(paren
r_struct
id|class_device
op_star
id|cdev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|transport_class_to_sdev
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_struct
id|spi_transport_attrs
op_star
id|tp
suffix:semicolon
r_const
r_char
op_star
id|str
suffix:semicolon
r_struct
id|spi_internal
op_star
id|i
op_assign
id|to_spi_internal
c_func
(paren
id|sdev-&gt;host-&gt;transportt
)paren
suffix:semicolon
id|tp
op_assign
(paren
r_struct
id|spi_transport_attrs
op_star
)paren
op_amp
id|sdev-&gt;transport_data
suffix:semicolon
r_if
c_cond
(paren
id|i-&gt;f-&gt;get_period
)paren
id|i-&gt;f
op_member_access_from_pointer
id|get_period
c_func
(paren
id|sdev
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|tp-&gt;period
)paren
(brace
r_case
l_int|0x07
dot
dot
dot
id|SPI_STATIC_PPR
suffix:colon
id|str
op_assign
id|ppr_to_ns
(braket
id|tp-&gt;period
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|str
)paren
(brace
id|str
op_assign
l_string|&quot;reserved&quot;
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
(paren
id|SPI_STATIC_PPR
op_plus
l_int|1
)paren
dot
dot
dot
l_int|0xff
suffix:colon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|tp-&gt;period
op_star
l_int|4
)paren
suffix:semicolon
r_default
suffix:colon
id|str
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
)brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|store_spi_transport_period
id|store_spi_transport_period
c_func
(paren
r_struct
id|class_device
op_star
id|cdev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|transport_class_to_sdev
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_struct
id|spi_internal
op_star
id|i
op_assign
id|to_spi_internal
c_func
(paren
id|sdev-&gt;host-&gt;transportt
)paren
suffix:semicolon
r_int
id|j
comma
id|period
op_assign
op_minus
l_int|1
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
id|SPI_STATIC_PPR
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|ppr_to_ns
(braket
id|j
)braket
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
id|len
op_assign
id|strlen
c_func
(paren
id|ppr_to_ns
(braket
id|j
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ppr_to_ns
(braket
id|j
)braket
comma
id|buf
comma
id|len
)paren
op_ne
l_int|0
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buf
(braket
id|len
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_continue
suffix:semicolon
)brace
id|period
op_assign
id|j
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|period
op_eq
op_minus
l_int|1
)paren
(brace
r_int
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Should probably check limits here, but this&n;&t;&t; * gets reasonably close to OK for most things */
id|period
op_assign
id|val
op_div
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|period
OG
l_int|0xff
)paren
id|period
op_assign
l_int|0xff
suffix:semicolon
id|i-&gt;f
op_member_access_from_pointer
id|set_period
c_func
(paren
id|sdev
comma
id|period
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|period
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_spi_transport_period
comma
id|store_spi_transport_period
)paren
suffix:semicolon
DECL|macro|DV_SET
mdefine_line|#define DV_SET(x, y)&t;&t;&t;&bslash;&n;&t;if(i-&gt;f-&gt;set_##x)&t;&t;&bslash;&n;&t;&t;i-&gt;f-&gt;set_##x(sdev, y)
DECL|macro|DV_LOOPS
mdefine_line|#define DV_LOOPS&t;3
DECL|macro|DV_TIMEOUT
mdefine_line|#define DV_TIMEOUT&t;(10*HZ)
DECL|macro|DV_RETRIES
mdefine_line|#define DV_RETRIES&t;3&t;/* should only need at most &n;&t;&t;&t;&t; * two cc/ua clears */
multiline_comment|/* This is for read/write Domain Validation:  If the device supports&n; * an echo buffer, we do read/write tests to it */
r_static
r_int
DECL|function|spi_dv_device_echo_buffer
id|spi_dv_device_echo_buffer
c_func
(paren
r_struct
id|scsi_request
op_star
id|sreq
comma
id|u8
op_star
id|buffer
comma
id|u8
op_star
id|ptr
comma
r_const
r_int
id|retries
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|sreq-&gt;sr_device
suffix:semicolon
r_int
id|len
op_assign
id|ptr
op_minus
id|buffer
suffix:semicolon
r_int
id|j
comma
id|k
comma
id|r
suffix:semicolon
r_int
r_int
id|pattern
op_assign
l_int|0x0000ffff
suffix:semicolon
r_const
r_char
id|spi_write_buffer
(braket
)braket
op_assign
(brace
id|WRITE_BUFFER
comma
l_int|0x0a
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|len
op_rshift
l_int|8
comma
id|len
op_amp
l_int|0xff
comma
l_int|0
)brace
suffix:semicolon
r_const
r_char
id|spi_read_buffer
(braket
)braket
op_assign
(brace
id|READ_BUFFER
comma
l_int|0x0a
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|len
op_rshift
l_int|8
comma
id|len
op_amp
l_int|0xff
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* set up the pattern buffer.  Doesn&squot;t matter if we spill&n;&t; * slightly beyond since that&squot;s where the read buffer is */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|len
suffix:semicolon
)paren
(brace
multiline_comment|/* fill the buffer with counting (test a) */
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
id|min
c_func
(paren
id|len
comma
l_int|32
)paren
suffix:semicolon
id|j
op_increment
)paren
id|buffer
(braket
id|j
)braket
op_assign
id|j
suffix:semicolon
id|k
op_assign
id|j
suffix:semicolon
multiline_comment|/* fill the buffer with alternating words of 0x0 and&n;&t;&t; * 0xffff (test b) */
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
id|min
c_func
(paren
id|len
comma
id|k
op_plus
l_int|32
)paren
suffix:semicolon
id|j
op_add_assign
l_int|2
)paren
(brace
id|u16
op_star
id|word
op_assign
(paren
id|u16
op_star
)paren
op_amp
id|buffer
(braket
id|j
)braket
suffix:semicolon
op_star
id|word
op_assign
(paren
id|j
op_amp
l_int|0x02
)paren
ques
c_cond
l_int|0x0000
suffix:colon
l_int|0xffff
suffix:semicolon
)brace
id|k
op_assign
id|j
suffix:semicolon
multiline_comment|/* fill with crosstalk (alternating 0x5555 0xaaa)&n;                 * (test c) */
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
id|min
c_func
(paren
id|len
comma
id|k
op_plus
l_int|32
)paren
suffix:semicolon
id|j
op_add_assign
l_int|2
)paren
(brace
id|u16
op_star
id|word
op_assign
(paren
id|u16
op_star
)paren
op_amp
id|buffer
(braket
id|j
)braket
suffix:semicolon
op_star
id|word
op_assign
(paren
id|j
op_amp
l_int|0x02
)paren
ques
c_cond
l_int|0x5555
suffix:colon
l_int|0xaaaa
suffix:semicolon
)brace
id|k
op_assign
id|j
suffix:semicolon
multiline_comment|/* fill with shifting bits (test d) */
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
id|min
c_func
(paren
id|len
comma
id|k
op_plus
l_int|32
)paren
suffix:semicolon
id|j
op_add_assign
l_int|4
)paren
(brace
id|u32
op_star
id|word
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|buffer
(braket
id|j
)braket
suffix:semicolon
id|u32
id|roll
op_assign
(paren
id|pattern
op_amp
l_int|0x80000000
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|word
op_assign
id|pattern
suffix:semicolon
id|pattern
op_assign
(paren
id|pattern
op_lshift
l_int|1
)paren
op_or
id|roll
suffix:semicolon
)brace
multiline_comment|/* don&squot;t bother with random data (test e) */
)brace
r_for
c_loop
(paren
id|r
op_assign
l_int|0
suffix:semicolon
id|r
OL
id|retries
suffix:semicolon
id|r
op_increment
)paren
(brace
id|sreq-&gt;sr_cmd_len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* wait_req to fill in */
id|sreq-&gt;sr_data_direction
op_assign
id|DMA_TO_DEVICE
suffix:semicolon
id|scsi_wait_req
c_func
(paren
id|sreq
comma
id|spi_write_buffer
comma
id|buffer
comma
id|len
comma
id|DV_TIMEOUT
comma
id|DV_RETRIES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sreq-&gt;sr_result
op_logical_or
op_logical_neg
id|scsi_device_online
c_func
(paren
id|sdev
)paren
)paren
(brace
id|scsi_device_set_state
c_func
(paren
id|sdev
comma
id|SDEV_QUIESCE
)paren
suffix:semicolon
id|SPI_PRINTK
c_func
(paren
id|sdev
comma
id|KERN_ERR
comma
l_string|&quot;Write Buffer failure %x&bslash;n&quot;
comma
id|sreq-&gt;sr_result
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
id|sreq-&gt;sr_cmd_len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* wait_req to fill in */
id|sreq-&gt;sr_data_direction
op_assign
id|DMA_FROM_DEVICE
suffix:semicolon
id|scsi_wait_req
c_func
(paren
id|sreq
comma
id|spi_read_buffer
comma
id|ptr
comma
id|len
comma
id|DV_TIMEOUT
comma
id|DV_RETRIES
)paren
suffix:semicolon
id|scsi_device_set_state
c_func
(paren
id|sdev
comma
id|SDEV_QUIESCE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buffer
comma
id|ptr
comma
id|len
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This is for the simplest form of Domain Validation: a read test&n; * on the inquiry data from the device */
r_static
r_int
DECL|function|spi_dv_device_compare_inquiry
id|spi_dv_device_compare_inquiry
c_func
(paren
r_struct
id|scsi_request
op_star
id|sreq
comma
id|u8
op_star
id|buffer
comma
id|u8
op_star
id|ptr
comma
r_const
r_int
id|retries
)paren
(brace
r_int
id|r
suffix:semicolon
r_const
r_int
id|len
op_assign
id|sreq-&gt;sr_device-&gt;inquiry_len
suffix:semicolon
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|sreq-&gt;sr_device
suffix:semicolon
r_const
r_char
id|spi_inquiry
(braket
)braket
op_assign
(brace
id|INQUIRY
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|len
comma
l_int|0
)brace
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
l_int|0
suffix:semicolon
id|r
OL
id|retries
suffix:semicolon
id|r
op_increment
)paren
(brace
id|sreq-&gt;sr_cmd_len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* wait_req to fill in */
id|sreq-&gt;sr_data_direction
op_assign
id|DMA_FROM_DEVICE
suffix:semicolon
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
id|scsi_wait_req
c_func
(paren
id|sreq
comma
id|spi_inquiry
comma
id|ptr
comma
id|len
comma
id|DV_TIMEOUT
comma
id|DV_RETRIES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sreq-&gt;sr_result
op_logical_or
op_logical_neg
id|scsi_device_online
c_func
(paren
id|sdev
)paren
)paren
(brace
id|scsi_device_set_state
c_func
(paren
id|sdev
comma
id|SDEV_QUIESCE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If we don&squot;t have the inquiry data already, the&n;&t;&t; * first read gets it */
r_if
c_cond
(paren
id|ptr
op_eq
id|buffer
)paren
(brace
id|ptr
op_add_assign
id|len
suffix:semicolon
op_decrement
id|r
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buffer
comma
id|ptr
comma
id|len
)paren
op_ne
l_int|0
)paren
multiline_comment|/* failure */
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|spi_dv_retrain
id|spi_dv_retrain
c_func
(paren
r_struct
id|scsi_request
op_star
id|sreq
comma
id|u8
op_star
id|buffer
comma
id|u8
op_star
id|ptr
comma
r_int
(paren
op_star
id|compare_fn
)paren
(paren
r_struct
id|scsi_request
op_star
comma
id|u8
op_star
comma
id|u8
op_star
comma
r_int
)paren
)paren
(brace
r_struct
id|spi_internal
op_star
id|i
op_assign
id|to_spi_internal
c_func
(paren
id|sreq-&gt;sr_host-&gt;transportt
)paren
suffix:semicolon
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|sreq-&gt;sr_device
suffix:semicolon
r_int
id|period
comma
id|prevperiod
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|compare_fn
c_func
(paren
id|sreq
comma
id|buffer
comma
id|ptr
comma
id|DV_LOOPS
)paren
)paren
multiline_comment|/* Successful DV */
r_break
suffix:semicolon
multiline_comment|/* OK, retrain, fallback */
r_if
c_cond
(paren
id|i-&gt;f-&gt;get_period
)paren
id|i-&gt;f
op_member_access_from_pointer
id|get_period
c_func
(paren
id|sdev
)paren
suffix:semicolon
id|period
op_assign
id|spi_period
c_func
(paren
id|sdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|period
OL
l_int|0x0d
)paren
id|period
op_increment
suffix:semicolon
r_else
id|period
op_add_assign
id|period
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|period
OG
l_int|0xff
op_logical_or
id|period
op_eq
id|prevperiod
)paren
)paren
(brace
multiline_comment|/* Total failure; set to async and return */
id|SPI_PRINTK
c_func
(paren
id|sdev
comma
id|KERN_ERR
comma
l_string|&quot;Domain Validation Failure, dropping back to Asynchronous&bslash;n&quot;
)paren
suffix:semicolon
id|DV_SET
c_func
(paren
id|offset
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|SPI_PRINTK
c_func
(paren
id|sdev
comma
id|KERN_ERR
comma
l_string|&quot;Domain Validation detected failure, dropping back&bslash;n&quot;
)paren
suffix:semicolon
id|DV_SET
c_func
(paren
id|period
comma
id|period
)paren
suffix:semicolon
id|prevperiod
op_assign
id|period
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|spi_dv_device_get_echo_buffer
id|spi_dv_device_get_echo_buffer
c_func
(paren
r_struct
id|scsi_request
op_star
id|sreq
comma
id|u8
op_star
id|buffer
)paren
(brace
r_int
id|l
suffix:semicolon
multiline_comment|/* first off do a test unit ready.  This can error out &n;&t; * because of reservations or some other reason.  If it&n;&t; * fails, the device won&squot;t let us write to the echo buffer&n;&t; * so just return failure */
r_const
r_char
id|spi_test_unit_ready
(braket
)braket
op_assign
(brace
id|TEST_UNIT_READY
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_const
r_char
id|spi_read_buffer_descriptor
(braket
)braket
op_assign
(brace
id|READ_BUFFER
comma
l_int|0x0b
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|0
)brace
suffix:semicolon
id|sreq-&gt;sr_cmd_len
op_assign
l_int|0
suffix:semicolon
id|sreq-&gt;sr_data_direction
op_assign
id|DMA_NONE
suffix:semicolon
multiline_comment|/* We send a set of three TURs to clear any outstanding &n;&t; * unit attention conditions if they exist (Otherwise the&n;&t; * buffer tests won&squot;t be happy).  If the TUR still fails&n;&t; * (reservation conflict, device not ready, etc) just&n;&t; * skip the write tests */
r_for
c_loop
(paren
id|l
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|l
op_increment
)paren
(brace
id|scsi_wait_req
c_func
(paren
id|sreq
comma
id|spi_test_unit_ready
comma
l_int|NULL
comma
l_int|0
comma
id|DV_TIMEOUT
comma
id|DV_RETRIES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sreq-&gt;sr_result
)paren
(brace
r_if
c_cond
(paren
id|l
op_ge
l_int|3
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* TUR succeeded */
r_break
suffix:semicolon
)brace
)brace
id|sreq-&gt;sr_cmd_len
op_assign
l_int|0
suffix:semicolon
id|sreq-&gt;sr_data_direction
op_assign
id|DMA_FROM_DEVICE
suffix:semicolon
id|scsi_wait_req
c_func
(paren
id|sreq
comma
id|spi_read_buffer_descriptor
comma
id|buffer
comma
l_int|4
comma
id|DV_TIMEOUT
comma
id|DV_RETRIES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sreq-&gt;sr_result
)paren
multiline_comment|/* Device has no echo buffer */
r_return
l_int|0
suffix:semicolon
r_return
id|buffer
(braket
l_int|3
)braket
op_plus
(paren
(paren
id|buffer
(braket
l_int|2
)braket
op_amp
l_int|0x1f
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|spi_dv_device_internal
id|spi_dv_device_internal
c_func
(paren
r_struct
id|scsi_request
op_star
id|sreq
comma
id|u8
op_star
id|buffer
)paren
(brace
r_struct
id|spi_internal
op_star
id|i
op_assign
id|to_spi_internal
c_func
(paren
id|sreq-&gt;sr_host-&gt;transportt
)paren
suffix:semicolon
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|sreq-&gt;sr_device
suffix:semicolon
r_int
id|len
op_assign
id|sdev-&gt;inquiry_len
suffix:semicolon
multiline_comment|/* first set us up for narrow async */
id|DV_SET
c_func
(paren
id|offset
comma
l_int|0
)paren
suffix:semicolon
id|DV_SET
c_func
(paren
id|width
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spi_dv_device_compare_inquiry
c_func
(paren
id|sreq
comma
id|buffer
comma
id|buffer
comma
id|DV_LOOPS
)paren
)paren
(brace
id|SPI_PRINTK
c_func
(paren
id|sdev
comma
id|KERN_ERR
comma
l_string|&quot;Domain Validation Initial Inquiry Failed&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* FIXME: should probably offline the device here? */
r_return
suffix:semicolon
)brace
multiline_comment|/* test width */
r_if
c_cond
(paren
id|i-&gt;f-&gt;set_width
op_logical_and
id|sdev-&gt;wdtr
)paren
(brace
id|i-&gt;f
op_member_access_from_pointer
id|set_width
c_func
(paren
id|sdev
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spi_dv_device_compare_inquiry
c_func
(paren
id|sreq
comma
id|buffer
comma
id|buffer
op_plus
id|len
comma
id|DV_LOOPS
)paren
)paren
(brace
id|SPI_PRINTK
c_func
(paren
id|sdev
comma
id|KERN_ERR
comma
l_string|&quot;Wide Transfers Fail&bslash;n&quot;
)paren
suffix:semicolon
id|i-&gt;f
op_member_access_from_pointer
id|set_width
c_func
(paren
id|sdev
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|i-&gt;f-&gt;set_period
)paren
r_return
suffix:semicolon
multiline_comment|/* device can&squot;t handle synchronous */
r_if
c_cond
(paren
op_logical_neg
id|sdev-&gt;ppr
op_logical_and
op_logical_neg
id|sdev-&gt;sdtr
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* now set up to the maximum */
id|DV_SET
c_func
(paren
id|offset
comma
l_int|255
)paren
suffix:semicolon
id|DV_SET
c_func
(paren
id|period
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spi_dv_retrain
c_func
(paren
id|sreq
comma
id|buffer
comma
id|buffer
op_plus
id|len
comma
id|spi_dv_device_compare_inquiry
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* OK, now we have our initial speed set by the read only inquiry&n;&t; * test, now try an echo buffer test (if the device allows it) */
r_if
c_cond
(paren
(paren
id|len
op_assign
id|spi_dv_device_get_echo_buffer
c_func
(paren
id|sreq
comma
id|buffer
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|SPI_PRINTK
c_func
(paren
id|sdev
comma
id|KERN_INFO
comma
l_string|&quot;Domain Validation skipping write tests&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
id|SPI_MAX_ECHO_BUFFER_SIZE
)paren
(brace
id|SPI_PRINTK
c_func
(paren
id|sdev
comma
id|KERN_WARNING
comma
l_string|&quot;Echo buffer size %d is too big, trimming to %d&bslash;n&quot;
comma
id|len
comma
id|SPI_MAX_ECHO_BUFFER_SIZE
)paren
suffix:semicolon
id|len
op_assign
id|SPI_MAX_ECHO_BUFFER_SIZE
suffix:semicolon
)brace
id|spi_dv_retrain
c_func
(paren
id|sreq
comma
id|buffer
comma
id|buffer
op_plus
id|len
comma
id|spi_dv_device_echo_buffer
)paren
suffix:semicolon
)brace
multiline_comment|/**&t;spi_dv_device - Do Domain Validation on the device&n; *&t;@sdev:&t;&t;scsi device to validate&n; *&n; *&t;Performs the domain validation on the given device in the&n; *&t;current execution thread.  Since DV operations may sleep,&n; *&t;the current thread must have user context.  Also no SCSI&n; *&t;related locks that would deadlock I/O issued by the DV may&n; *&t;be held.&n; */
r_void
DECL|function|spi_dv_device
id|spi_dv_device
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_struct
id|scsi_request
op_star
id|sreq
op_assign
id|scsi_allocate_request
c_func
(paren
id|sdev
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|u8
op_star
id|buffer
suffix:semicolon
r_const
r_int
id|len
op_assign
id|SPI_MAX_ECHO_BUFFER_SIZE
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|sreq
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|scsi_device_get
c_func
(paren
id|sdev
)paren
)paren
)paren
r_goto
id|out_free_req
suffix:semicolon
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|buffer
)paren
)paren
r_goto
id|out_put
suffix:semicolon
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|scsi_device_quiesce
c_func
(paren
id|sdev
)paren
)paren
)paren
r_goto
id|out_free
suffix:semicolon
id|spi_dv_pending
c_func
(paren
id|sdev
)paren
op_assign
l_int|1
suffix:semicolon
id|down
c_func
(paren
op_amp
id|spi_dv_sem
c_func
(paren
id|sdev
)paren
)paren
suffix:semicolon
id|SPI_PRINTK
c_func
(paren
id|sdev
comma
id|KERN_INFO
comma
l_string|&quot;Beginning Domain Validation&bslash;n&quot;
)paren
suffix:semicolon
id|spi_dv_device_internal
c_func
(paren
id|sreq
comma
id|buffer
)paren
suffix:semicolon
id|SPI_PRINTK
c_func
(paren
id|sdev
comma
id|KERN_INFO
comma
l_string|&quot;Ending Domain Validation&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|spi_dv_sem
c_func
(paren
id|sdev
)paren
)paren
suffix:semicolon
id|spi_dv_pending
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
id|scsi_device_resume
c_func
(paren
id|sdev
)paren
suffix:semicolon
id|out_free
suffix:colon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|out_put
suffix:colon
id|scsi_device_put
c_func
(paren
id|sdev
)paren
suffix:semicolon
id|out_free_req
suffix:colon
id|scsi_release_request
c_func
(paren
id|sreq
)paren
suffix:semicolon
)brace
DECL|variable|spi_dv_device
id|EXPORT_SYMBOL
c_func
(paren
id|spi_dv_device
)paren
suffix:semicolon
DECL|struct|work_queue_wrapper
r_struct
id|work_queue_wrapper
(brace
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
DECL|member|sdev
r_struct
id|scsi_device
op_star
id|sdev
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
DECL|function|spi_dv_device_work_wrapper
id|spi_dv_device_work_wrapper
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|work_queue_wrapper
op_star
id|wqw
op_assign
(paren
r_struct
id|work_queue_wrapper
op_star
)paren
id|data
suffix:semicolon
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|wqw-&gt;sdev
suffix:semicolon
id|kfree
c_func
(paren
id|wqw
)paren
suffix:semicolon
id|spi_dv_device
c_func
(paren
id|sdev
)paren
suffix:semicolon
id|spi_dv_pending
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
id|scsi_device_put
c_func
(paren
id|sdev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;spi_schedule_dv_device - schedule domain validation to occur on the device&n; *&t;@sdev:&t;The device to validate&n; *&n; *&t;Identical to spi_dv_device() above, except that the DV will be&n; *&t;scheduled to occur in a workqueue later.  All memory allocations&n; *&t;are atomic, so may be called from any context including those holding&n; *&t;SCSI locks.&n; */
r_void
DECL|function|spi_schedule_dv_device
id|spi_schedule_dv_device
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_struct
id|work_queue_wrapper
op_star
id|wqw
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|work_queue_wrapper
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|wqw
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|spi_dv_pending
c_func
(paren
id|sdev
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|wqw
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Set pending early (dv_device doesn&squot;t check it, only sets it) */
id|spi_dv_pending
c_func
(paren
id|sdev
)paren
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|scsi_device_get
c_func
(paren
id|sdev
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|wqw
)paren
suffix:semicolon
id|spi_dv_pending
c_func
(paren
id|sdev
)paren
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|INIT_WORK
c_func
(paren
op_amp
id|wqw-&gt;work
comma
id|spi_dv_device_work_wrapper
comma
id|wqw
)paren
suffix:semicolon
id|wqw-&gt;sdev
op_assign
id|sdev
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|wqw-&gt;work
)paren
suffix:semicolon
)brace
DECL|variable|spi_schedule_dv_device
id|EXPORT_SYMBOL
c_func
(paren
id|spi_schedule_dv_device
)paren
suffix:semicolon
DECL|macro|SETUP_ATTRIBUTE
mdefine_line|#define SETUP_ATTRIBUTE(field)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;i-&gt;private_attrs[count] = class_device_attr_##field;&t;&t;&bslash;&n;&t;if (!i-&gt;f-&gt;set_##field) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;i-&gt;private_attrs[count].attr.mode = S_IRUGO;&t;&t;&bslash;&n;&t;&t;i-&gt;private_attrs[count].store = NULL;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;i-&gt;attrs[count] = &amp;i-&gt;private_attrs[count];&t;&t;&t;&bslash;&n;&t;if (i-&gt;f-&gt;show_##field)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;count++
r_struct
id|scsi_transport_template
op_star
DECL|function|spi_attach_transport
id|spi_attach_transport
c_func
(paren
r_struct
id|spi_function_template
op_star
id|ft
)paren
(brace
r_struct
id|spi_internal
op_star
id|i
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|spi_internal
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|i
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|i
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|spi_internal
)paren
)paren
suffix:semicolon
id|i-&gt;t.attrs
op_assign
op_amp
id|i-&gt;attrs
(braket
l_int|0
)braket
suffix:semicolon
id|i-&gt;t
dot
r_class
op_assign
op_amp
id|spi_transport_class
suffix:semicolon
id|i-&gt;t.setup
op_assign
op_amp
id|spi_setup_transport_attrs
suffix:semicolon
id|i-&gt;t.size
op_assign
r_sizeof
(paren
r_struct
id|spi_transport_attrs
)paren
suffix:semicolon
id|i-&gt;f
op_assign
id|ft
suffix:semicolon
id|SETUP_ATTRIBUTE
c_func
(paren
id|period
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE
c_func
(paren
id|offset
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE
c_func
(paren
id|width
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE
c_func
(paren
id|iu
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE
c_func
(paren
id|dt
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE
c_func
(paren
id|qas
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE
c_func
(paren
id|wr_flow
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE
c_func
(paren
id|rd_strm
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE
c_func
(paren
id|rti
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE
c_func
(paren
id|pcomp_en
)paren
suffix:semicolon
multiline_comment|/* if you add an attribute but forget to increase SPI_NUM_ATTRS&n;&t; * this bug will trigger */
id|BUG_ON
c_func
(paren
id|count
OG
id|SPI_NUM_ATTRS
)paren
suffix:semicolon
id|i-&gt;attrs
(braket
id|count
op_increment
)braket
op_assign
op_amp
id|class_device_attr_revalidate
suffix:semicolon
id|i-&gt;attrs
(braket
id|count
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
op_amp
id|i-&gt;t
suffix:semicolon
)brace
DECL|variable|spi_attach_transport
id|EXPORT_SYMBOL
c_func
(paren
id|spi_attach_transport
)paren
suffix:semicolon
DECL|function|spi_release_transport
r_void
id|spi_release_transport
c_func
(paren
r_struct
id|scsi_transport_template
op_star
id|t
)paren
(brace
r_struct
id|spi_internal
op_star
id|i
op_assign
id|to_spi_internal
c_func
(paren
id|t
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
DECL|variable|spi_release_transport
id|EXPORT_SYMBOL
c_func
(paren
id|spi_release_transport
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Martin Hicks&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SPI Transport Attributes&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|spi_transport_init
id|module_init
c_func
(paren
id|spi_transport_init
)paren
suffix:semicolon
DECL|variable|spi_transport_exit
id|module_exit
c_func
(paren
id|spi_transport_exit
)paren
suffix:semicolon
eof
