multiline_comment|/*&n; *  Copyright (C) 2003  Osamu Tomita &lt;tomita@cinet.co.jp&gt;&n; *&n; *  PC9801 BIOS geometry handling.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;asm/pc9800.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
DECL|function|pc98_first_bios_param
r_static
r_int
id|pc98_first_bios_param
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
op_star
id|ip
)paren
(brace
r_const
id|u8
op_star
id|p
op_assign
(paren
op_amp
id|__PC9800SCA
c_func
(paren
id|u8
comma
id|PC9800SCA_SCSI_PARAMS
)paren
op_plus
id|sdev-&gt;id
op_star
l_int|4
)paren
suffix:semicolon
id|ip
(braket
l_int|0
)braket
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* # of heads */
id|ip
(braket
l_int|1
)braket
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* # of sectors/track */
id|ip
(braket
l_int|2
)braket
op_assign
op_star
(paren
id|u16
op_star
)paren
op_amp
id|p
(braket
l_int|2
)braket
op_amp
l_int|0x0fff
suffix:semicolon
multiline_comment|/* # of cylinders */
r_if
c_cond
(paren
id|p
(braket
l_int|3
)braket
op_amp
(paren
l_int|1
op_lshift
l_int|6
)paren
)paren
(brace
multiline_comment|/* #-of-cylinders is 16-bit */
id|ip
(braket
l_int|2
)braket
op_or_assign
(paren
id|ip
(braket
l_int|0
)braket
op_amp
l_int|0xf0
)paren
op_lshift
l_int|8
suffix:semicolon
id|ip
(braket
l_int|0
)braket
op_and_assign
l_int|0x0f
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pc98_bios_param
r_int
id|pc98_bios_param
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|sector_t
id|capacity
comma
r_int
op_star
id|ip
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|first_real
op_assign
id|first_real_host
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * XXX&n;&t; * XXX This needs to become a sysfs attribute that&squot;s set&n;&t; * XXX by code that knows which host is the first one.&n;&t; * XXX&n;&t; * XXX Currently we support only one host on with a&n;&t; * XXX PC98ish HBA.&n;&t; * XXX&n;&t; */
r_if
c_cond
(paren
l_int|1
op_logical_or
id|sdev-&gt;host
op_eq
id|first_real
op_logical_and
id|sdev-&gt;id
OL
l_int|7
op_logical_and
id|__PC9800SCA_TEST_BIT
c_func
(paren
id|PC9800SCA_DISK_EQUIPS
comma
id|sdev-&gt;id
)paren
)paren
r_return
id|pc98_first_bios_param
c_func
(paren
id|sdev
comma
id|ip
)paren
suffix:semicolon
multiline_comment|/* Assume PC-9801-92 compatible parameters for HAs without BIOS.  */
id|ip
(braket
l_int|0
)braket
op_assign
l_int|8
suffix:semicolon
id|ip
(braket
l_int|1
)braket
op_assign
l_int|32
suffix:semicolon
id|ip
(braket
l_int|2
)braket
op_assign
id|capacity
op_div
(paren
l_int|8
op_star
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip
(braket
l_int|2
)braket
OG
l_int|65535
)paren
(brace
multiline_comment|/* if capacity &gt;= 8GB */
multiline_comment|/* Recent on-board adapters seem to use this parameter. */
id|ip
(braket
l_int|1
)braket
op_assign
l_int|128
suffix:semicolon
id|ip
(braket
l_int|2
)braket
op_assign
id|capacity
op_div
(paren
l_int|8
op_star
l_int|128
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip
(braket
l_int|2
)braket
OG
l_int|65535
)paren
(brace
multiline_comment|/* if capacity &gt;= 32GB  */
multiline_comment|/* Clip the number of cylinders.  Currently&n;&t;&t;&t;   this is the limit that we deal with.  */
id|ip
(braket
l_int|2
)braket
op_assign
l_int|65535
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pc98_bios_param
id|EXPORT_SYMBOL
c_func
(paren
id|pc98_bios_param
)paren
suffix:semicolon
eof
