multiline_comment|/*&n; * scsicam.c - SCSI CAM support functions, use for HDIO_GETGEO, etc.&n; *&n; * Copyright 1993, 1994 Drew Eckhardt&n; *      Visionary Computing &n; *      (Unix and Linux consulting and custom programming)&n; *      drew@Colorado.EDU&n; *      +1 (303) 786-7975&n; *&n; * For more information, please consult the SCSI-CAM draft.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;sd.h&quot;
macro_line|#include &lt;scsi/scsicam.h&gt;
r_static
r_int
id|setsize
c_func
(paren
r_int
r_int
id|capacity
comma
r_int
r_int
op_star
id|cyls
comma
r_int
r_int
op_star
id|hds
comma
r_int
r_int
op_star
id|secs
)paren
suffix:semicolon
DECL|function|scsi_bios_ptable
r_int
r_char
op_star
id|scsi_bios_ptable
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
r_int
r_char
op_star
id|res
op_assign
id|kmalloc
c_func
(paren
l_int|66
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|kdev_t
id|rdev
op_assign
id|mk_kdev
c_func
(paren
id|major
c_func
(paren
id|dev
)paren
comma
id|minor
c_func
(paren
id|dev
)paren
op_amp
op_complement
l_int|0x0f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|err
suffix:semicolon
id|bdev
op_assign
id|bdget
c_func
(paren
id|kdev_t_to_nr
c_func
(paren
id|rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev
)paren
r_goto
id|fail
suffix:semicolon
id|err
op_assign
id|blkdev_get
c_func
(paren
id|bdev
comma
id|FMODE_READ
comma
l_int|0
comma
id|BDEV_FILE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
id|bh
op_assign
id|__bread
c_func
(paren
id|bdev
comma
l_int|0
comma
id|block_size
c_func
(paren
id|rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|fail2
suffix:semicolon
id|memcpy
c_func
(paren
id|res
comma
id|bh-&gt;b_data
op_plus
l_int|0x1be
comma
l_int|66
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_FILE
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
id|fail2
suffix:colon
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_FILE
)paren
suffix:semicolon
id|fail
suffix:colon
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function : int scsicam_bios_param (Disk *disk, int dev, int *ip)&n; *&n; * Purpose : to determine the BIOS mapping used for a drive in a &n; *      SCSI-CAM system, storing the results in ip as required&n; *      by the HDIO_GETGEO ioctl().&n; *&n; * Returns : -1 on failure, 0 on success.&n; *&n; */
DECL|function|scsicam_bios_param
r_int
id|scsicam_bios_param
c_func
(paren
id|Disk
op_star
id|disk
comma
multiline_comment|/* SCSI disk */
id|kdev_t
id|dev
comma
multiline_comment|/* Device major, minor */
r_int
op_star
id|ip
multiline_comment|/* Heads, sectors, cylinders in that order */
)paren
(brace
r_int
id|ret_code
suffix:semicolon
r_int
id|size
op_assign
id|disk-&gt;capacity
suffix:semicolon
r_int
r_int
id|temp_cyl
suffix:semicolon
r_int
r_char
op_star
id|p
op_assign
id|scsi_bios_ptable
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* try to infer mapping from partition table */
id|ret_code
op_assign
id|scsi_partsize
c_func
(paren
id|p
comma
(paren
r_int
r_int
)paren
id|size
comma
(paren
r_int
r_int
op_star
)paren
id|ip
op_plus
l_int|2
comma
(paren
r_int
r_int
op_star
)paren
id|ip
op_plus
l_int|0
comma
(paren
r_int
r_int
op_star
)paren
id|ip
op_plus
l_int|1
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_code
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* pick some standard mapping with at most 1024 cylinders,&n;&t;&t;   and at most 62 sectors per track - this works up to&n;&t;&t;   7905 MB */
id|ret_code
op_assign
id|setsize
c_func
(paren
(paren
r_int
r_int
)paren
id|size
comma
(paren
r_int
r_int
op_star
)paren
id|ip
op_plus
l_int|2
comma
(paren
r_int
r_int
op_star
)paren
id|ip
op_plus
l_int|0
comma
(paren
r_int
r_int
op_star
)paren
id|ip
op_plus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* if something went wrong, then apparently we have to return&n;&t;   a geometry with more than 1024 cylinders */
r_if
c_cond
(paren
id|ret_code
op_logical_or
id|ip
(braket
l_int|0
)braket
OG
l_int|255
op_logical_or
id|ip
(braket
l_int|1
)braket
OG
l_int|63
)paren
(brace
id|ip
(braket
l_int|0
)braket
op_assign
l_int|64
suffix:semicolon
id|ip
(braket
l_int|1
)braket
op_assign
l_int|32
suffix:semicolon
id|temp_cyl
op_assign
id|size
op_div
(paren
id|ip
(braket
l_int|0
)braket
op_star
id|ip
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp_cyl
OG
l_int|65534
)paren
(brace
id|ip
(braket
l_int|0
)braket
op_assign
l_int|255
suffix:semicolon
id|ip
(braket
l_int|1
)braket
op_assign
l_int|63
suffix:semicolon
)brace
id|ip
(braket
l_int|2
)braket
op_assign
id|size
op_div
(paren
id|ip
(braket
l_int|0
)braket
op_star
id|ip
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function : static int scsi_partsize(unsigned char *buf, unsigned long &n; *     capacity,unsigned int *cyls, unsigned int *hds, unsigned int *secs);&n; *&n; * Purpose : to determine the BIOS mapping used to create the partition&n; *      table, storing the results in *cyls, *hds, and *secs &n; *&n; * Returns : -1 on failure, 0 on success.&n; *&n; */
DECL|function|scsi_partsize
r_int
id|scsi_partsize
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|capacity
comma
r_int
r_int
op_star
id|cyls
comma
r_int
r_int
op_star
id|hds
comma
r_int
r_int
op_star
id|secs
)paren
(brace
r_struct
id|partition
op_star
id|p
op_assign
(paren
r_struct
id|partition
op_star
)paren
id|buf
comma
op_star
id|largest
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
comma
id|largest_cyl
suffix:semicolon
r_int
id|cyl
comma
id|ext_cyl
comma
id|end_head
comma
id|end_cyl
comma
id|end_sector
suffix:semicolon
r_int
r_int
id|logical_end
comma
id|physical_end
comma
id|ext_physical_end
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|buf
op_plus
l_int|64
)paren
op_eq
l_int|0xAA55
)paren
(brace
r_for
c_loop
(paren
id|largest_cyl
op_assign
op_minus
l_int|1
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
op_increment
id|i
comma
op_increment
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;sys_ind
)paren
r_continue
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;scsicam_bios_param : partition %d has system &bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
macro_line|#endif
id|cyl
op_assign
id|p-&gt;cyl
op_plus
(paren
(paren
id|p-&gt;sector
op_amp
l_int|0xc0
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cyl
OG
id|largest_cyl
)paren
(brace
id|largest_cyl
op_assign
id|cyl
suffix:semicolon
id|largest
op_assign
id|p
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|largest
)paren
(brace
id|end_cyl
op_assign
id|largest-&gt;end_cyl
op_plus
(paren
(paren
id|largest-&gt;end_sector
op_amp
l_int|0xc0
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
id|end_head
op_assign
id|largest-&gt;end_head
suffix:semicolon
id|end_sector
op_assign
id|largest-&gt;end_sector
op_amp
l_int|0x3f
suffix:semicolon
r_if
c_cond
(paren
id|end_head
op_plus
l_int|1
op_eq
l_int|0
op_logical_or
id|end_sector
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;scsicam_bios_param : end at h = %d, c = %d, s = %d&bslash;n&quot;
comma
id|end_head
comma
id|end_cyl
comma
id|end_sector
)paren
suffix:semicolon
macro_line|#endif
id|physical_end
op_assign
id|end_cyl
op_star
(paren
id|end_head
op_plus
l_int|1
)paren
op_star
id|end_sector
op_plus
id|end_head
op_star
id|end_sector
op_plus
id|end_sector
suffix:semicolon
multiline_comment|/* This is the actual _sector_ number at the end */
id|logical_end
op_assign
id|get_unaligned
c_func
(paren
op_amp
id|largest-&gt;start_sect
)paren
op_plus
id|get_unaligned
c_func
(paren
op_amp
id|largest-&gt;nr_sects
)paren
suffix:semicolon
multiline_comment|/* This is for &gt;1023 cylinders */
id|ext_cyl
op_assign
(paren
id|logical_end
op_minus
(paren
id|end_head
op_star
id|end_sector
op_plus
id|end_sector
)paren
)paren
op_div
(paren
id|end_head
op_plus
l_int|1
)paren
op_div
id|end_sector
suffix:semicolon
id|ext_physical_end
op_assign
id|ext_cyl
op_star
(paren
id|end_head
op_plus
l_int|1
)paren
op_star
id|end_sector
op_plus
id|end_head
op_star
id|end_sector
op_plus
id|end_sector
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;scsicam_bios_param : logical_end=%d physical_end=%d ext_physical_end=%d ext_cyl=%d&bslash;n&quot;
comma
id|logical_end
comma
id|physical_end
comma
id|ext_physical_end
comma
id|ext_cyl
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|logical_end
op_eq
id|physical_end
)paren
op_logical_or
(paren
id|end_cyl
op_eq
l_int|1023
op_logical_and
id|ext_physical_end
op_eq
id|logical_end
)paren
)paren
(brace
op_star
id|secs
op_assign
id|end_sector
suffix:semicolon
op_star
id|hds
op_assign
id|end_head
op_plus
l_int|1
suffix:semicolon
op_star
id|cyls
op_assign
id|capacity
op_div
(paren
(paren
id|end_head
op_plus
l_int|1
)paren
op_star
id|end_sector
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;scsicam_bios_param : logical (%u) != physical (%u)&bslash;n&quot;
comma
id|logical_end
comma
id|physical_end
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Function : static int setsize(unsigned long capacity,unsigned int *cyls,&n; *      unsigned int *hds, unsigned int *secs);&n; *&n; * Purpose : to determine a near-optimal int 0x13 mapping for a&n; *      SCSI disk in terms of lost space of size capacity, storing&n; *      the results in *cyls, *hds, and *secs.&n; *&n; * Returns : -1 on failure, 0 on success.&n; *&n; * Extracted from&n; *&n; * WORKING                                                    X3T9.2&n; * DRAFT                                                        792D&n; *&n; *&n; *                                                        Revision 6&n; *                                                         10-MAR-94&n; * Information technology -&n; * SCSI-2 Common access method&n; * transport and SCSI interface module&n; * &n; * ANNEX A :&n; *&n; * setsize() converts a read capacity value to int 13h&n; * head-cylinder-sector requirements. It minimizes the value for&n; * number of heads and maximizes the number of cylinders. This&n; * will support rather large disks before the number of heads&n; * will not fit in 4 bits (or 6 bits). This algorithm also&n; * minimizes the number of sectors that will be unused at the end&n; * of the disk while allowing for very large disks to be&n; * accommodated. This algorithm does not use physical geometry. &n; */
DECL|function|setsize
r_static
r_int
id|setsize
c_func
(paren
r_int
r_int
id|capacity
comma
r_int
r_int
op_star
id|cyls
comma
r_int
r_int
op_star
id|hds
comma
r_int
r_int
op_star
id|secs
)paren
(brace
r_int
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|heads
comma
id|sectors
comma
id|cylinders
comma
id|temp
suffix:semicolon
id|cylinders
op_assign
l_int|1024L
suffix:semicolon
multiline_comment|/* Set number of cylinders to max */
id|sectors
op_assign
l_int|62L
suffix:semicolon
multiline_comment|/* Maximize sectors per track */
id|temp
op_assign
id|cylinders
op_star
id|sectors
suffix:semicolon
multiline_comment|/* Compute divisor for heads */
id|heads
op_assign
id|capacity
op_div
id|temp
suffix:semicolon
multiline_comment|/* Compute value for number of heads */
r_if
c_cond
(paren
id|capacity
op_mod
id|temp
)paren
(brace
multiline_comment|/* If no remainder, done! */
id|heads
op_increment
suffix:semicolon
multiline_comment|/* Else, increment number of heads */
id|temp
op_assign
id|cylinders
op_star
id|heads
suffix:semicolon
multiline_comment|/* Compute divisor for sectors */
id|sectors
op_assign
id|capacity
op_div
id|temp
suffix:semicolon
multiline_comment|/* Compute value for sectors per&n;&t;&t;&t;&t;&t;&t;   track */
r_if
c_cond
(paren
id|capacity
op_mod
id|temp
)paren
(brace
multiline_comment|/* If no remainder, done! */
id|sectors
op_increment
suffix:semicolon
multiline_comment|/* Else, increment number of sectors */
id|temp
op_assign
id|heads
op_star
id|sectors
suffix:semicolon
multiline_comment|/* Compute divisor for cylinders */
id|cylinders
op_assign
id|capacity
op_div
id|temp
suffix:semicolon
multiline_comment|/* Compute number of cylinders */
)brace
)brace
r_if
c_cond
(paren
id|cylinders
op_eq
l_int|0
)paren
id|rv
op_assign
(paren
r_int
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Give error if 0 cylinders */
op_star
id|cyls
op_assign
(paren
r_int
r_int
)paren
id|cylinders
suffix:semicolon
multiline_comment|/* Stuff return values */
op_star
id|secs
op_assign
(paren
r_int
r_int
)paren
id|sectors
suffix:semicolon
op_star
id|hds
op_assign
(paren
r_int
r_int
)paren
id|heads
suffix:semicolon
r_return
(paren
id|rv
)paren
suffix:semicolon
)brace
eof
