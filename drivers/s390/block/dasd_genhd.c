multiline_comment|/*&n; * File...........: linux/drivers/s390/block/dasd_genhd.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; *&t;&t;    Horst Hummel &lt;Horst.Hummel@de.ibm.com&gt;&n; *&t;&t;    Carsten Otte &lt;Cotte@de.ibm.com&gt;&n; *&t;&t;    Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999-2001&n; *&n; * gendisk related functions for the dasd driver.&n; *&n; * $Revision: 1.44 $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* This is ugly... */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;dasd_gendisk:&quot;
macro_line|#include &quot;dasd_int.h&quot;
multiline_comment|/*&n; * Allocate and register gendisk structure for device.&n; */
r_int
DECL|function|dasd_gendisk_alloc
id|dasd_gendisk_alloc
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
)paren
(brace
r_struct
id|gendisk
op_star
id|gdp
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* Make sure the minor for this device exists. */
r_if
c_cond
(paren
id|device-&gt;devindex
op_ge
id|DASD_PER_MAJOR
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|gdp
op_assign
id|alloc_disk
c_func
(paren
l_int|1
op_lshift
id|DASD_PARTN_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gdp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Initialize gendisk structure. */
id|gdp-&gt;major
op_assign
id|DASD_MAJOR
suffix:semicolon
id|gdp-&gt;first_minor
op_assign
id|device-&gt;devindex
op_lshift
id|DASD_PARTN_BITS
suffix:semicolon
id|gdp-&gt;fops
op_assign
op_amp
id|dasd_device_operations
suffix:semicolon
id|gdp-&gt;driverfs_dev
op_assign
op_amp
id|device-&gt;cdev-&gt;dev
suffix:semicolon
multiline_comment|/*&n;&t; * Set device name.&n;&t; *   dasda - dasdz : 26 devices&n;&t; *   dasdaa - dasdzz : 676 devices, added up = 702&n;&t; *   dasdaaa - dasdzzz : 17576 devices, added up = 18278&n;&t; *   dasdaaaa - dasdzzzz : 456976 devices, added up = 475252&n;&t; */
id|len
op_assign
id|sprintf
c_func
(paren
id|gdp-&gt;disk_name
comma
l_string|&quot;dasd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;devindex
OG
l_int|25
)paren
(brace
r_if
c_cond
(paren
id|device-&gt;devindex
OG
l_int|701
)paren
(brace
r_if
c_cond
(paren
id|device-&gt;devindex
OG
l_int|18277
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|gdp-&gt;disk_name
op_plus
id|len
comma
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
(paren
(paren
id|device-&gt;devindex
op_minus
l_int|18278
)paren
op_div
l_int|17576
)paren
op_mod
l_int|26
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|gdp-&gt;disk_name
op_plus
id|len
comma
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
(paren
(paren
id|device-&gt;devindex
op_minus
l_int|702
)paren
op_div
l_int|676
)paren
op_mod
l_int|26
)paren
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|gdp-&gt;disk_name
op_plus
id|len
comma
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
(paren
(paren
id|device-&gt;devindex
op_minus
l_int|26
)paren
op_div
l_int|26
)paren
op_mod
l_int|26
)paren
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|gdp-&gt;disk_name
op_plus
id|len
comma
l_string|&quot;%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
id|device-&gt;devindex
op_mod
l_int|26
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|gdp-&gt;devfs_name
comma
l_string|&quot;dasd/%s&quot;
comma
id|device-&gt;cdev-&gt;dev.bus_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;ro_flag
)paren
id|set_disk_ro
c_func
(paren
id|gdp
comma
l_int|1
)paren
suffix:semicolon
id|gdp-&gt;private_data
op_assign
id|device
suffix:semicolon
id|gdp-&gt;queue
op_assign
id|device-&gt;request_queue
suffix:semicolon
id|device-&gt;gdp
op_assign
id|gdp
suffix:semicolon
id|set_capacity
c_func
(paren
id|device-&gt;gdp
comma
l_int|0
)paren
suffix:semicolon
id|add_disk
c_func
(paren
id|device-&gt;gdp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Unregister and free gendisk structure for device.&n; */
r_void
DECL|function|dasd_gendisk_free
id|dasd_gendisk_free
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
)paren
(brace
id|del_gendisk
c_func
(paren
id|device-&gt;gdp
)paren
suffix:semicolon
id|device-&gt;gdp-&gt;queue
op_assign
l_int|0
suffix:semicolon
id|put_disk
c_func
(paren
id|device-&gt;gdp
)paren
suffix:semicolon
id|device-&gt;gdp
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Trigger a partition detection.&n; */
r_void
DECL|function|dasd_scan_partitions
id|dasd_scan_partitions
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
multiline_comment|/* Make the disk known. */
id|set_capacity
c_func
(paren
id|device-&gt;gdp
comma
id|device-&gt;blocks
op_lshift
id|device-&gt;s2b_shift
)paren
suffix:semicolon
multiline_comment|/* See fs/partition/check.c:register_disk,rescan_partitions */
id|bdev
op_assign
id|bdget_disk
c_func
(paren
id|device-&gt;gdp
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdev
)paren
(brace
r_if
c_cond
(paren
id|blkdev_get
c_func
(paren
id|bdev
comma
id|FMODE_READ
comma
l_int|1
)paren
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Can&squot;t call rescan_partitions directly. Use ioctl. */
id|ioctl_by_bdev
c_func
(paren
id|bdev
comma
id|BLKRRPART
comma
l_int|0
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|bdev
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Remove all inodes in the system for a device, delete the&n; * partitions and make device unusable by setting its size to zero.&n; */
r_void
DECL|function|dasd_destroy_partitions
id|dasd_destroy_partitions
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
)paren
(brace
r_int
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|device-&gt;gdp-&gt;minors
op_minus
l_int|1
suffix:semicolon
id|p
OG
l_int|0
suffix:semicolon
id|p
op_decrement
)paren
(brace
id|invalidate_partition
c_func
(paren
id|device-&gt;gdp
comma
id|p
)paren
suffix:semicolon
id|delete_partition
c_func
(paren
id|device-&gt;gdp
comma
id|p
)paren
suffix:semicolon
)brace
id|invalidate_partition
c_func
(paren
id|device-&gt;gdp
comma
l_int|0
)paren
suffix:semicolon
id|set_capacity
c_func
(paren
id|device-&gt;gdp
comma
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|dasd_gendisk_init
id|dasd_gendisk_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
multiline_comment|/* Register to static dasd major 94 */
id|rc
op_assign
id|register_blkdev
c_func
(paren
id|DASD_MAJOR
comma
l_string|&quot;dasd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;Couldn&squot;t register successfully to &quot;
l_string|&quot;major no %d&quot;
comma
id|DASD_MAJOR
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|dasd_gendisk_exit
id|dasd_gendisk_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_blkdev
c_func
(paren
id|DASD_MAJOR
comma
l_string|&quot;dasd&quot;
)paren
suffix:semicolon
)brace
eof
