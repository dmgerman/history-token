multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd_fba.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999,2000&n; *&n; * $Revision: 1.39 $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;&t;/* HDIO_GETGEO&t;&t;&t;    */
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/idals.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/todclk.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &quot;dasd_int.h&quot;
macro_line|#include &quot;dasd_fba.h&quot;
macro_line|#ifdef PRINTK_HEADER
DECL|macro|PRINTK_HEADER
macro_line|#undef PRINTK_HEADER
macro_line|#endif&t;&t;&t;&t;/* PRINTK_HEADER */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;dasd(fba):&quot;
DECL|macro|DASD_FBA_CCW_WRITE
mdefine_line|#define DASD_FBA_CCW_WRITE 0x41
DECL|macro|DASD_FBA_CCW_READ
mdefine_line|#define DASD_FBA_CCW_READ 0x42
DECL|macro|DASD_FBA_CCW_LOCATE
mdefine_line|#define DASD_FBA_CCW_LOCATE 0x43
DECL|macro|DASD_FBA_CCW_DEFINE_EXTENT
mdefine_line|#define DASD_FBA_CCW_DEFINE_EXTENT 0x63
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|dasd_fba_discipline
r_static
r_struct
id|dasd_discipline
id|dasd_fba_discipline
suffix:semicolon
DECL|struct|dasd_fba_private
r_struct
id|dasd_fba_private
(brace
DECL|member|rdc_data
r_struct
id|dasd_fba_characteristics
id|rdc_data
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|dasd_fba_ids
r_static
r_struct
id|ccw_device_id
id|dasd_fba_ids
(braket
)braket
op_assign
(brace
(brace
id|CCW_DEVICE_DEVTYPE
(paren
l_int|0x6310
comma
l_int|0
comma
l_int|0x9336
comma
l_int|0
)paren
comma
id|driver_info
suffix:colon
l_int|0x1
)brace
comma
(brace
id|CCW_DEVICE_DEVTYPE
(paren
l_int|0x3880
comma
l_int|0
comma
l_int|0x3370
comma
l_int|0
)paren
comma
id|driver_info
suffix:colon
l_int|0x2
)brace
comma
(brace
multiline_comment|/* end of list */
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|ccw
comma
id|dasd_fba_ids
)paren
suffix:semicolon
DECL|variable|dasd_fba_driver
r_static
r_struct
id|ccw_driver
id|dasd_fba_driver
suffix:semicolon
multiline_comment|/* see below */
r_static
r_int
DECL|function|dasd_fba_probe
id|dasd_fba_probe
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|dasd_generic_probe
(paren
id|cdev
comma
op_amp
id|dasd_fba_discipline
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|ccw_device_set_options
c_func
(paren
id|cdev
comma
id|CCWDEV_DO_PATHGROUP
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_fba_set_online
id|dasd_fba_set_online
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_return
id|dasd_generic_set_online
(paren
id|cdev
comma
op_amp
id|dasd_fba_discipline
)paren
suffix:semicolon
)brace
DECL|variable|dasd_fba_driver
r_static
r_struct
id|ccw_driver
id|dasd_fba_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;dasd-fba&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ids
op_assign
id|dasd_fba_ids
comma
dot
id|probe
op_assign
id|dasd_fba_probe
comma
dot
id|remove
op_assign
id|dasd_generic_remove
comma
dot
id|set_offline
op_assign
id|dasd_generic_set_offline
comma
dot
id|set_online
op_assign
id|dasd_fba_set_online
comma
dot
id|notify
op_assign
id|dasd_generic_notify
comma
)brace
suffix:semicolon
r_static
r_inline
r_void
DECL|function|define_extent
id|define_extent
c_func
(paren
r_struct
id|ccw1
op_star
id|ccw
comma
r_struct
id|DE_fba_data
op_star
id|data
comma
r_int
id|rw
comma
r_int
id|blksize
comma
r_int
id|beg
comma
r_int
id|nr
)paren
(brace
id|ccw-&gt;cmd_code
op_assign
id|DASD_FBA_CCW_DEFINE_EXTENT
suffix:semicolon
id|ccw-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|ccw-&gt;count
op_assign
l_int|16
suffix:semicolon
id|ccw-&gt;cda
op_assign
(paren
id|__u32
)paren
id|__pa
c_func
(paren
id|data
)paren
suffix:semicolon
id|memset
c_func
(paren
id|data
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|DE_fba_data
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|WRITE
)paren
(paren
id|data-&gt;mask
)paren
dot
id|perm
op_assign
l_int|0x0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rw
op_eq
id|READ
)paren
(paren
id|data-&gt;mask
)paren
dot
id|perm
op_assign
l_int|0x1
suffix:semicolon
r_else
id|data-&gt;mask.perm
op_assign
l_int|0x2
suffix:semicolon
id|data-&gt;blk_size
op_assign
id|blksize
suffix:semicolon
id|data-&gt;ext_loc
op_assign
id|beg
suffix:semicolon
id|data-&gt;ext_end
op_assign
id|nr
op_minus
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|locate_record
id|locate_record
c_func
(paren
r_struct
id|ccw1
op_star
id|ccw
comma
r_struct
id|LO_fba_data
op_star
id|data
comma
r_int
id|rw
comma
r_int
id|block_nr
comma
r_int
id|block_ct
)paren
(brace
id|ccw-&gt;cmd_code
op_assign
id|DASD_FBA_CCW_LOCATE
suffix:semicolon
id|ccw-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|ccw-&gt;count
op_assign
l_int|8
suffix:semicolon
id|ccw-&gt;cda
op_assign
(paren
id|__u32
)paren
id|__pa
c_func
(paren
id|data
)paren
suffix:semicolon
id|memset
c_func
(paren
id|data
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|LO_fba_data
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|WRITE
)paren
id|data-&gt;operation.cmd
op_assign
l_int|0x5
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rw
op_eq
id|READ
)paren
id|data-&gt;operation.cmd
op_assign
l_int|0x6
suffix:semicolon
r_else
id|data-&gt;operation.cmd
op_assign
l_int|0x8
suffix:semicolon
id|data-&gt;blk_nr
op_assign
id|block_nr
suffix:semicolon
id|data-&gt;blk_ct
op_assign
id|block_ct
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_fba_check_characteristics
id|dasd_fba_check_characteristics
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
)paren
(brace
r_struct
id|dasd_fba_private
op_star
r_private
suffix:semicolon
r_struct
id|ccw_device
op_star
id|cdev
op_assign
id|device-&gt;cdev
suffix:semicolon
r_void
op_star
id|rdc_data
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_private
op_assign
(paren
r_struct
id|dasd_fba_private
op_star
)paren
id|device
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
r_private
op_eq
l_int|NULL
)paren
(brace
r_private
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dasd_fba_private
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
r_private
op_eq
l_int|NULL
)paren
(brace
id|DEV_MESSAGE
c_func
(paren
id|KERN_WARNING
comma
id|device
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;memory allocation failed for private &quot;
l_string|&quot;data&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|device
op_member_access_from_pointer
r_private
op_assign
(paren
r_void
op_star
)paren
r_private
suffix:semicolon
)brace
multiline_comment|/* Read Device Characteristics */
id|rdc_data
op_assign
(paren
r_void
op_star
)paren
op_amp
(paren
r_private
op_member_access_from_pointer
id|rdc_data
)paren
suffix:semicolon
id|rc
op_assign
id|read_dev_chars
c_func
(paren
id|device-&gt;cdev
comma
op_amp
id|rdc_data
comma
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|DEV_MESSAGE
c_func
(paren
id|KERN_WARNING
comma
id|device
comma
l_string|&quot;Read device characteristics returned error %d&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|DEV_MESSAGE
c_func
(paren
id|KERN_INFO
comma
id|device
comma
l_string|&quot;%04X/%02X(CU:%04X/%02X) %dMB at(%d B/blk)&quot;
comma
id|cdev-&gt;id.dev_type
comma
id|cdev-&gt;id.dev_model
comma
id|cdev-&gt;id.cu_type
comma
id|cdev-&gt;id.cu_model
comma
(paren
(paren
r_private
op_member_access_from_pointer
id|rdc_data.blk_bdsa
op_star
(paren
r_private
op_member_access_from_pointer
id|rdc_data.blk_size
op_rshift
l_int|9
)paren
)paren
op_rshift
l_int|11
)paren
comma
r_private
op_member_access_from_pointer
id|rdc_data.blk_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_fba_do_analysis
id|dasd_fba_do_analysis
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
)paren
(brace
r_struct
id|dasd_fba_private
op_star
r_private
suffix:semicolon
r_int
id|sb
comma
id|rc
suffix:semicolon
r_private
op_assign
(paren
r_struct
id|dasd_fba_private
op_star
)paren
id|device
op_member_access_from_pointer
r_private
suffix:semicolon
id|rc
op_assign
id|dasd_check_blocksize
c_func
(paren
r_private
op_member_access_from_pointer
id|rdc_data.blk_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|DEV_MESSAGE
c_func
(paren
id|KERN_INFO
comma
id|device
comma
l_string|&quot;unknown blocksize %d&quot;
comma
r_private
op_member_access_from_pointer
id|rdc_data.blk_size
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|device-&gt;blocks
op_assign
r_private
op_member_access_from_pointer
id|rdc_data.blk_bdsa
suffix:semicolon
id|device-&gt;bp_block
op_assign
r_private
op_member_access_from_pointer
id|rdc_data.blk_size
suffix:semicolon
id|device-&gt;s2b_shift
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* bits to shift 512 to get a block */
r_for
c_loop
(paren
id|sb
op_assign
l_int|512
suffix:semicolon
id|sb
OL
r_private
op_member_access_from_pointer
id|rdc_data.blk_size
suffix:semicolon
id|sb
op_assign
id|sb
op_lshift
l_int|1
)paren
id|device-&gt;s2b_shift
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_fba_fill_geometry
id|dasd_fba_fill_geometry
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
comma
r_struct
id|hd_geometry
op_star
id|geo
)paren
(brace
r_if
c_cond
(paren
id|dasd_check_blocksize
c_func
(paren
id|device-&gt;bp_block
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|geo-&gt;cylinders
op_assign
(paren
id|device-&gt;blocks
op_lshift
id|device-&gt;s2b_shift
)paren
op_rshift
l_int|10
suffix:semicolon
id|geo-&gt;heads
op_assign
l_int|16
suffix:semicolon
id|geo-&gt;sectors
op_assign
l_int|128
op_rshift
id|device-&gt;s2b_shift
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|dasd_era_t
DECL|function|dasd_fba_examine_error
id|dasd_fba_examine_error
c_func
(paren
r_struct
id|dasd_ccw_req
op_star
id|cqr
comma
r_struct
id|irb
op_star
id|irb
)paren
(brace
r_struct
id|dasd_device
op_star
id|device
suffix:semicolon
r_struct
id|ccw_device
op_star
id|cdev
suffix:semicolon
id|device
op_assign
(paren
r_struct
id|dasd_device
op_star
)paren
id|cqr-&gt;device
suffix:semicolon
r_if
c_cond
(paren
id|irb-&gt;scsw.cstat
op_eq
l_int|0x00
op_logical_and
id|irb-&gt;scsw.dstat
op_eq
(paren
id|DEV_STAT_CHN_END
op_or
id|DEV_STAT_DEV_END
)paren
)paren
r_return
id|dasd_era_none
suffix:semicolon
id|cdev
op_assign
id|device-&gt;cdev
suffix:semicolon
r_switch
c_cond
(paren
id|cdev-&gt;id.dev_type
)paren
(brace
r_case
l_int|0x3370
suffix:colon
r_return
id|dasd_3370_erp_examine
c_func
(paren
id|cqr
comma
id|irb
)paren
suffix:semicolon
r_case
l_int|0x9336
suffix:colon
r_return
id|dasd_9336_erp_examine
c_func
(paren
id|cqr
comma
id|irb
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|dasd_era_recover
suffix:semicolon
)brace
)brace
r_static
id|dasd_erp_fn_t
DECL|function|dasd_fba_erp_action
id|dasd_fba_erp_action
c_func
(paren
r_struct
id|dasd_ccw_req
op_star
id|cqr
)paren
(brace
r_return
id|dasd_default_erp_action
suffix:semicolon
)brace
r_static
id|dasd_erp_fn_t
DECL|function|dasd_fba_erp_postaction
id|dasd_fba_erp_postaction
c_func
(paren
r_struct
id|dasd_ccw_req
op_star
id|cqr
)paren
(brace
r_if
c_cond
(paren
id|cqr-&gt;function
op_eq
id|dasd_default_erp_action
)paren
r_return
id|dasd_default_erp_postaction
suffix:semicolon
id|DEV_MESSAGE
c_func
(paren
id|KERN_WARNING
comma
id|cqr-&gt;device
comma
l_string|&quot;unknown ERP action %p&quot;
comma
id|cqr-&gt;function
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_struct
id|dasd_ccw_req
op_star
DECL|function|dasd_fba_build_cp
id|dasd_fba_build_cp
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
comma
r_struct
id|request
op_star
id|req
)paren
(brace
r_struct
id|dasd_fba_private
op_star
r_private
suffix:semicolon
r_int
r_int
op_star
id|idaws
suffix:semicolon
r_struct
id|LO_fba_data
op_star
id|LO_data
suffix:semicolon
r_struct
id|dasd_ccw_req
op_star
id|cqr
suffix:semicolon
r_struct
id|ccw1
op_star
id|ccw
suffix:semicolon
r_struct
id|bio
op_star
id|bio
suffix:semicolon
r_struct
id|bio_vec
op_star
id|bv
suffix:semicolon
r_char
op_star
id|dst
suffix:semicolon
r_int
id|count
comma
id|cidaw
comma
id|cplength
comma
id|datasize
suffix:semicolon
id|sector_t
id|recid
comma
id|first_rec
comma
id|last_rec
suffix:semicolon
r_int
r_int
id|blksize
comma
id|off
suffix:semicolon
r_int
r_char
id|cmd
suffix:semicolon
r_int
id|i
suffix:semicolon
r_private
op_assign
(paren
r_struct
id|dasd_fba_private
op_star
)paren
id|device
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|req
)paren
op_eq
id|READ
)paren
(brace
id|cmd
op_assign
id|DASD_FBA_CCW_READ
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|req
)paren
op_eq
id|WRITE
)paren
(brace
id|cmd
op_assign
id|DASD_FBA_CCW_WRITE
suffix:semicolon
)brace
r_else
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|blksize
op_assign
id|device-&gt;bp_block
suffix:semicolon
multiline_comment|/* Calculate record id of first and last block. */
id|first_rec
op_assign
id|req-&gt;sector
op_rshift
id|device-&gt;s2b_shift
suffix:semicolon
id|last_rec
op_assign
(paren
id|req-&gt;sector
op_plus
id|req-&gt;nr_sectors
op_minus
l_int|1
)paren
op_rshift
id|device-&gt;s2b_shift
suffix:semicolon
multiline_comment|/* Check struct bio and count the number of blocks for the request. */
id|count
op_assign
l_int|0
suffix:semicolon
id|cidaw
op_assign
l_int|0
suffix:semicolon
id|rq_for_each_bio
c_func
(paren
id|bio
comma
id|req
)paren
(brace
id|bio_for_each_segment
c_func
(paren
id|bv
comma
id|bio
comma
id|i
)paren
(brace
r_if
c_cond
(paren
id|bv-&gt;bv_len
op_amp
(paren
id|blksize
op_minus
l_int|1
)paren
)paren
multiline_comment|/* Fba can only do full blocks. */
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|count
op_add_assign
id|bv-&gt;bv_len
op_rshift
(paren
id|device-&gt;s2b_shift
op_plus
l_int|9
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ARCH_S390X)
r_if
c_cond
(paren
id|idal_is_needed
(paren
id|page_address
c_func
(paren
id|bv-&gt;bv_page
)paren
comma
id|bv-&gt;bv_len
)paren
)paren
id|cidaw
op_add_assign
id|bv-&gt;bv_len
op_div
id|blksize
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/* Paranoia. */
r_if
c_cond
(paren
id|count
op_ne
id|last_rec
op_minus
id|first_rec
op_plus
l_int|1
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* 1x define extent + 1x locate record + number of blocks */
id|cplength
op_assign
l_int|2
op_plus
id|count
suffix:semicolon
multiline_comment|/* 1x define extent + 1x locate record */
id|datasize
op_assign
r_sizeof
(paren
r_struct
id|DE_fba_data
)paren
op_plus
r_sizeof
(paren
r_struct
id|LO_fba_data
)paren
op_plus
id|cidaw
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Find out number of additional locate record ccws if the device&n;&t; * can&squot;t do data chaining.&n;&t; */
r_if
c_cond
(paren
r_private
op_member_access_from_pointer
id|rdc_data.mode.bits.data_chain
op_eq
l_int|0
)paren
(brace
id|cplength
op_add_assign
id|count
op_minus
l_int|1
suffix:semicolon
id|datasize
op_add_assign
(paren
id|count
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|LO_fba_data
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate the ccw request. */
id|cqr
op_assign
id|dasd_smalloc_request
c_func
(paren
id|dasd_fba_discipline.name
comma
id|cplength
comma
id|datasize
comma
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|cqr
)paren
)paren
r_return
id|cqr
suffix:semicolon
id|ccw
op_assign
id|cqr-&gt;cpaddr
suffix:semicolon
multiline_comment|/* First ccw is define extent. */
id|define_extent
c_func
(paren
id|ccw
op_increment
comma
id|cqr-&gt;data
comma
id|rq_data_dir
c_func
(paren
id|req
)paren
comma
id|device-&gt;bp_block
comma
id|req-&gt;sector
comma
id|req-&gt;nr_sectors
)paren
suffix:semicolon
multiline_comment|/* Build locate_record + read/write ccws. */
id|idaws
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|cqr-&gt;data
op_plus
r_sizeof
(paren
r_struct
id|DE_fba_data
)paren
)paren
suffix:semicolon
id|LO_data
op_assign
(paren
r_struct
id|LO_fba_data
op_star
)paren
(paren
id|idaws
op_plus
id|cidaw
)paren
suffix:semicolon
multiline_comment|/* Locate record for all blocks for smart devices. */
r_if
c_cond
(paren
r_private
op_member_access_from_pointer
id|rdc_data.mode.bits.data_chain
op_ne
l_int|0
)paren
(brace
id|ccw
(braket
op_minus
l_int|1
)braket
dot
id|flags
op_or_assign
id|CCW_FLAG_CC
suffix:semicolon
id|locate_record
c_func
(paren
id|ccw
op_increment
comma
id|LO_data
op_increment
comma
id|rq_data_dir
c_func
(paren
id|req
)paren
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
)brace
id|recid
op_assign
id|first_rec
suffix:semicolon
id|rq_for_each_bio
c_func
(paren
id|bio
comma
id|req
)paren
id|bio_for_each_segment
c_func
(paren
id|bv
comma
id|bio
comma
id|i
)paren
(brace
id|dst
op_assign
id|page_address
c_func
(paren
id|bv-&gt;bv_page
)paren
op_plus
id|bv-&gt;bv_offset
suffix:semicolon
r_if
c_cond
(paren
id|dasd_page_cache
)paren
(brace
r_char
op_star
id|copy
op_assign
id|kmem_cache_alloc
c_func
(paren
id|dasd_page_cache
comma
id|SLAB_DMA
op_or
id|__GFP_NOWARN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy
op_logical_and
id|rq_data_dir
c_func
(paren
id|req
)paren
op_eq
id|WRITE
)paren
id|memcpy
c_func
(paren
id|copy
op_plus
id|bv-&gt;bv_offset
comma
id|dst
comma
id|bv-&gt;bv_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy
)paren
id|dst
op_assign
id|copy
op_plus
id|bv-&gt;bv_offset
suffix:semicolon
)brace
r_for
c_loop
(paren
id|off
op_assign
l_int|0
suffix:semicolon
id|off
OL
id|bv-&gt;bv_len
suffix:semicolon
id|off
op_add_assign
id|blksize
)paren
(brace
multiline_comment|/* Locate record for stupid devices. */
r_if
c_cond
(paren
r_private
op_member_access_from_pointer
id|rdc_data.mode.bits.data_chain
op_eq
l_int|0
)paren
(brace
id|ccw
(braket
op_minus
l_int|1
)braket
dot
id|flags
op_or_assign
id|CCW_FLAG_CC
suffix:semicolon
id|locate_record
c_func
(paren
id|ccw
comma
id|LO_data
op_increment
comma
id|rq_data_dir
c_func
(paren
id|req
)paren
comma
id|recid
op_minus
id|first_rec
comma
l_int|1
)paren
suffix:semicolon
id|ccw-&gt;flags
op_assign
id|CCW_FLAG_CC
suffix:semicolon
id|ccw
op_increment
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|recid
OG
id|first_rec
)paren
id|ccw
(braket
op_minus
l_int|1
)braket
dot
id|flags
op_or_assign
id|CCW_FLAG_DC
suffix:semicolon
r_else
id|ccw
(braket
op_minus
l_int|1
)braket
dot
id|flags
op_or_assign
id|CCW_FLAG_CC
suffix:semicolon
)brace
id|ccw-&gt;cmd_code
op_assign
id|cmd
suffix:semicolon
id|ccw-&gt;count
op_assign
id|device-&gt;bp_block
suffix:semicolon
r_if
c_cond
(paren
id|idal_is_needed
c_func
(paren
id|dst
comma
id|blksize
)paren
)paren
(brace
id|ccw-&gt;cda
op_assign
(paren
id|__u32
)paren
(paren
id|addr_t
)paren
id|idaws
suffix:semicolon
id|ccw-&gt;flags
op_assign
id|CCW_FLAG_IDA
suffix:semicolon
id|idaws
op_assign
id|idal_create_words
c_func
(paren
id|idaws
comma
id|dst
comma
id|blksize
)paren
suffix:semicolon
)brace
r_else
(brace
id|ccw-&gt;cda
op_assign
(paren
id|__u32
)paren
(paren
id|addr_t
)paren
id|dst
suffix:semicolon
id|ccw-&gt;flags
op_assign
l_int|0
suffix:semicolon
)brace
id|ccw
op_increment
suffix:semicolon
id|dst
op_add_assign
id|blksize
suffix:semicolon
id|recid
op_increment
suffix:semicolon
)brace
)brace
id|cqr-&gt;device
op_assign
id|device
suffix:semicolon
id|cqr-&gt;expires
op_assign
l_int|5
op_star
l_int|60
op_star
id|HZ
suffix:semicolon
multiline_comment|/* 5 minutes */
id|cqr-&gt;status
op_assign
id|DASD_CQR_FILLED
suffix:semicolon
r_return
id|cqr
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_fba_free_cp
id|dasd_fba_free_cp
c_func
(paren
r_struct
id|dasd_ccw_req
op_star
id|cqr
comma
r_struct
id|request
op_star
id|req
)paren
(brace
r_struct
id|dasd_fba_private
op_star
r_private
suffix:semicolon
r_struct
id|ccw1
op_star
id|ccw
suffix:semicolon
r_struct
id|bio
op_star
id|bio
suffix:semicolon
r_struct
id|bio_vec
op_star
id|bv
suffix:semicolon
r_char
op_star
id|dst
comma
op_star
id|cda
suffix:semicolon
r_int
r_int
id|blksize
comma
id|off
suffix:semicolon
r_int
id|i
comma
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dasd_page_cache
)paren
r_goto
id|out
suffix:semicolon
r_private
op_assign
(paren
r_struct
id|dasd_fba_private
op_star
)paren
id|cqr-&gt;device
op_member_access_from_pointer
r_private
suffix:semicolon
id|blksize
op_assign
id|cqr-&gt;device-&gt;bp_block
suffix:semicolon
id|ccw
op_assign
id|cqr-&gt;cpaddr
suffix:semicolon
multiline_comment|/* Skip over define extent &amp; locate record. */
id|ccw
op_increment
suffix:semicolon
r_if
c_cond
(paren
r_private
op_member_access_from_pointer
id|rdc_data.mode.bits.data_chain
op_ne
l_int|0
)paren
id|ccw
op_increment
suffix:semicolon
id|rq_for_each_bio
c_func
(paren
id|bio
comma
id|req
)paren
id|bio_for_each_segment
c_func
(paren
id|bv
comma
id|bio
comma
id|i
)paren
(brace
id|dst
op_assign
id|page_address
c_func
(paren
id|bv-&gt;bv_page
)paren
op_plus
id|bv-&gt;bv_offset
suffix:semicolon
r_for
c_loop
(paren
id|off
op_assign
l_int|0
suffix:semicolon
id|off
OL
id|bv-&gt;bv_len
suffix:semicolon
id|off
op_add_assign
id|blksize
)paren
(brace
multiline_comment|/* Skip locate record. */
r_if
c_cond
(paren
r_private
op_member_access_from_pointer
id|rdc_data.mode.bits.data_chain
op_eq
l_int|0
)paren
id|ccw
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dst
)paren
(brace
r_if
c_cond
(paren
id|ccw-&gt;flags
op_amp
id|CCW_FLAG_IDA
)paren
id|cda
op_assign
op_star
(paren
(paren
r_char
op_star
op_star
)paren
(paren
(paren
id|addr_t
)paren
id|ccw-&gt;cda
)paren
)paren
suffix:semicolon
r_else
id|cda
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
id|addr_t
)paren
id|ccw-&gt;cda
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_ne
id|cda
)paren
(brace
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|req
)paren
op_eq
id|READ
)paren
id|memcpy
c_func
(paren
id|dst
comma
id|cda
comma
id|bv-&gt;bv_len
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|dasd_page_cache
comma
(paren
r_void
op_star
)paren
(paren
(paren
id|addr_t
)paren
id|cda
op_amp
id|PAGE_MASK
)paren
)paren
suffix:semicolon
)brace
id|dst
op_assign
l_int|NULL
suffix:semicolon
)brace
id|ccw
op_increment
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|status
op_assign
id|cqr-&gt;status
op_eq
id|DASD_CQR_DONE
suffix:semicolon
id|dasd_sfree_request
c_func
(paren
id|cqr
comma
id|cqr-&gt;device
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_fba_fill_info
id|dasd_fba_fill_info
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
comma
r_struct
id|dasd_information2_t
op_star
id|info
)paren
(brace
id|info-&gt;label_block
op_assign
l_int|1
suffix:semicolon
id|info-&gt;FBA_layout
op_assign
l_int|1
suffix:semicolon
id|info-&gt;format
op_assign
id|DASD_FORMAT_LDL
suffix:semicolon
id|info-&gt;characteristics_size
op_assign
r_sizeof
(paren
r_struct
id|dasd_fba_characteristics
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|info-&gt;characteristics
comma
op_amp
(paren
(paren
r_struct
id|dasd_fba_private
op_star
)paren
id|device
op_member_access_from_pointer
r_private
)paren
op_member_access_from_pointer
id|rdc_data
comma
r_sizeof
(paren
r_struct
id|dasd_fba_characteristics
)paren
)paren
suffix:semicolon
id|info-&gt;confdata_size
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|dasd_fba_dump_sense
id|dasd_fba_dump_sense
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
comma
r_struct
id|dasd_ccw_req
op_star
id|req
comma
r_struct
id|irb
op_star
id|irb
)paren
(brace
r_char
op_star
id|page
suffix:semicolon
r_struct
id|ccw1
op_star
id|act
comma
op_star
id|end
comma
op_star
id|last
suffix:semicolon
r_int
id|len
comma
id|sl
comma
id|sct
comma
id|count
suffix:semicolon
id|page
op_assign
(paren
r_char
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
op_eq
l_int|NULL
)paren
(brace
id|DEV_MESSAGE
c_func
(paren
id|KERN_ERR
comma
id|device
comma
l_string|&quot; %s&quot;
comma
l_string|&quot;No memory to dump sense data&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot; I/O status report for device %s:&bslash;n&quot;
comma
id|device-&gt;cdev-&gt;dev.bus_id
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot; in req: %p CS: 0x%02X DS: 0x%02X&bslash;n&quot;
comma
id|req
comma
id|irb-&gt;scsw.cstat
comma
id|irb-&gt;scsw.dstat
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot; device %s: Failing CCW: %p&bslash;n&quot;
comma
id|device-&gt;cdev-&gt;dev.bus_id
comma
(paren
r_void
op_star
)paren
(paren
id|addr_t
)paren
id|irb-&gt;scsw.cpa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irb-&gt;esw.esw0.erw.cons
)paren
(brace
r_for
c_loop
(paren
id|sl
op_assign
l_int|0
suffix:semicolon
id|sl
OL
l_int|4
suffix:semicolon
id|sl
op_increment
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot; Sense(hex) %2d-%2d:&quot;
comma
(paren
l_int|8
op_star
id|sl
)paren
comma
(paren
(paren
l_int|8
op_star
id|sl
)paren
op_plus
l_int|7
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sct
op_assign
l_int|0
suffix:semicolon
id|sct
OL
l_int|8
suffix:semicolon
id|sct
op_increment
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot; %02x&quot;
comma
id|irb-&gt;ecw
(braket
l_int|8
op_star
id|sl
op_plus
id|sct
)braket
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot; SORRY - NO VALID SENSE AVAILABLE&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|MESSAGE_LOG
c_func
(paren
id|KERN_ERR
comma
l_string|&quot;%s&quot;
comma
id|page
op_plus
r_sizeof
(paren
id|KERN_ERR
id|PRINTK_HEADER
)paren
)paren
suffix:semicolon
multiline_comment|/* dump the Channel Program */
multiline_comment|/* print first CCWs (maximum 8) */
id|act
op_assign
id|req-&gt;cpaddr
suffix:semicolon
r_for
c_loop
(paren
id|last
op_assign
id|act
suffix:semicolon
id|last-&gt;flags
op_amp
(paren
id|CCW_FLAG_CC
op_or
id|CCW_FLAG_DC
)paren
suffix:semicolon
id|last
op_increment
)paren
suffix:semicolon
id|end
op_assign
id|min
c_func
(paren
id|act
op_plus
l_int|8
comma
id|last
)paren
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot; Related CP in req: %p&bslash;n&quot;
comma
id|req
)paren
suffix:semicolon
r_while
c_loop
(paren
id|act
op_le
id|end
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot; CCW %p: %08X %08X DAT:&quot;
comma
id|act
comma
(paren
(paren
r_int
op_star
)paren
id|act
)paren
(braket
l_int|0
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|act
)paren
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|32
op_logical_and
id|count
OL
id|act-&gt;count
suffix:semicolon
id|count
op_add_assign
r_sizeof
(paren
r_int
)paren
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot; %08X&quot;
comma
(paren
(paren
r_int
op_star
)paren
(paren
id|addr_t
)paren
id|act-&gt;cda
)paren
(braket
(paren
id|count
op_rshift
l_int|2
)paren
)braket
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|act
op_increment
suffix:semicolon
)brace
id|MESSAGE_LOG
c_func
(paren
id|KERN_ERR
comma
l_string|&quot;%s&quot;
comma
id|page
op_plus
r_sizeof
(paren
id|KERN_ERR
id|PRINTK_HEADER
)paren
)paren
suffix:semicolon
multiline_comment|/* print failing CCW area */
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|act
OL
(paren
(paren
r_struct
id|ccw1
op_star
)paren
(paren
id|addr_t
)paren
id|irb-&gt;scsw.cpa
)paren
op_minus
l_int|2
)paren
(brace
id|act
op_assign
(paren
(paren
r_struct
id|ccw1
op_star
)paren
(paren
id|addr_t
)paren
id|irb-&gt;scsw.cpa
)paren
op_minus
l_int|2
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot;......&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|end
op_assign
id|min
c_func
(paren
(paren
r_struct
id|ccw1
op_star
)paren
(paren
id|addr_t
)paren
id|irb-&gt;scsw.cpa
op_plus
l_int|2
comma
id|last
)paren
suffix:semicolon
r_while
c_loop
(paren
id|act
op_le
id|end
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot; CCW %p: %08X %08X DAT:&quot;
comma
id|act
comma
(paren
(paren
r_int
op_star
)paren
id|act
)paren
(braket
l_int|0
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|act
)paren
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|32
op_logical_and
id|count
OL
id|act-&gt;count
suffix:semicolon
id|count
op_add_assign
r_sizeof
(paren
r_int
)paren
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot; %08X&quot;
comma
(paren
(paren
r_int
op_star
)paren
(paren
id|addr_t
)paren
id|act-&gt;cda
)paren
(braket
(paren
id|count
op_rshift
l_int|2
)paren
)braket
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|act
op_increment
suffix:semicolon
)brace
multiline_comment|/* print last CCWs */
r_if
c_cond
(paren
id|act
OL
id|last
op_minus
l_int|2
)paren
(brace
id|act
op_assign
id|last
op_minus
l_int|2
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot;......&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|act
op_le
id|last
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
id|KERN_ERR
id|PRINTK_HEADER
l_string|&quot; CCW %p: %08X %08X DAT:&quot;
comma
id|act
comma
(paren
(paren
r_int
op_star
)paren
id|act
)paren
(braket
l_int|0
)braket
comma
(paren
(paren
r_int
op_star
)paren
id|act
)paren
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|32
op_logical_and
id|count
OL
id|act-&gt;count
suffix:semicolon
id|count
op_add_assign
r_sizeof
(paren
r_int
)paren
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot; %08X&quot;
comma
(paren
(paren
r_int
op_star
)paren
(paren
id|addr_t
)paren
id|act-&gt;cda
)paren
(braket
(paren
id|count
op_rshift
l_int|2
)paren
)braket
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|act
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
id|MESSAGE_LOG
c_func
(paren
id|KERN_ERR
comma
l_string|&quot;%s&quot;
comma
id|page
op_plus
r_sizeof
(paren
id|KERN_ERR
id|PRINTK_HEADER
)paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * max_blocks is dependent on the amount of storage that is available&n; * in the static io buffer for each device. Currently each device has&n; * 8192 bytes (=2 pages). For 64 bit one dasd_mchunkt_t structure has&n; * 24 bytes, the struct dasd_ccw_req has 136 bytes and each block can use&n; * up to 16 bytes (8 for the ccw and 8 for the idal pointer). In&n; * addition we have one define extent ccw + 16 bytes of data and a &n; * locate record ccw for each block (stupid devices!) + 16 bytes of data.&n; * That makes:&n; * (8192 - 24 - 136 - 8 - 16) / 40 = 200.2 blocks at maximum.&n; * We want to fit two into the available memory so that we can immediately&n; * start the next request if one finishes off. That makes 100.1 blocks&n; * for one request. Give a little safety and the result is 96.&n; */
DECL|variable|dasd_fba_discipline
r_static
r_struct
id|dasd_discipline
id|dasd_fba_discipline
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
l_string|&quot;FBA &quot;
comma
dot
id|ebcname
op_assign
l_string|&quot;FBA &quot;
comma
dot
id|max_blocks
op_assign
l_int|96
comma
dot
id|check_device
op_assign
id|dasd_fba_check_characteristics
comma
dot
id|do_analysis
op_assign
id|dasd_fba_do_analysis
comma
dot
id|fill_geometry
op_assign
id|dasd_fba_fill_geometry
comma
dot
id|start_IO
op_assign
id|dasd_start_IO
comma
dot
id|term_IO
op_assign
id|dasd_term_IO
comma
dot
id|examine_error
op_assign
id|dasd_fba_examine_error
comma
dot
id|erp_action
op_assign
id|dasd_fba_erp_action
comma
dot
id|erp_postaction
op_assign
id|dasd_fba_erp_postaction
comma
dot
id|build_cp
op_assign
id|dasd_fba_build_cp
comma
dot
id|free_cp
op_assign
id|dasd_fba_free_cp
comma
dot
id|dump_sense
op_assign
id|dasd_fba_dump_sense
comma
dot
id|fill_info
op_assign
id|dasd_fba_fill_info
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|dasd_fba_init
id|dasd_fba_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ASCEBC
c_func
(paren
id|dasd_fba_discipline.ebcname
comma
l_int|4
)paren
suffix:semicolon
id|ret
op_assign
id|ccw_driver_register
c_func
(paren
op_amp
id|dasd_fba_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|dasd_generic_auto_online
c_func
(paren
op_amp
id|dasd_fba_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|dasd_fba_cleanup
id|dasd_fba_cleanup
c_func
(paren
r_void
)paren
(brace
id|ccw_driver_unregister
c_func
(paren
op_amp
id|dasd_fba_driver
)paren
suffix:semicolon
)brace
DECL|variable|dasd_fba_init
id|module_init
c_func
(paren
id|dasd_fba_init
)paren
suffix:semicolon
DECL|variable|dasd_fba_cleanup
id|module_exit
c_func
(paren
id|dasd_fba_cleanup
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: 1&n; * tab-width: 8&n; * End:&n; */
eof
