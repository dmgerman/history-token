multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd_fba.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999,2000&n; *          fixed partition handling and HDIO_GETGEO&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;&t;/* HDIO_GETGEO                      */
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;asm/ccwcache.h&gt;
macro_line|#include &lt;asm/idals.h&gt;
macro_line|#include &lt;asm/dasd.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/s390dyn.h&gt;
macro_line|#include &quot;dasd_fba.h&quot;
macro_line|#ifdef PRINTK_HEADER
DECL|macro|PRINTK_HEADER
macro_line|#undef PRINTK_HEADER
macro_line|#endif&t;&t;&t;&t;/* PRINTK_HEADER */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER DASD_NAME&quot;(fba):&quot;
DECL|macro|DASD_FBA_CCW_WRITE
mdefine_line|#define DASD_FBA_CCW_WRITE 0x41
DECL|macro|DASD_FBA_CCW_READ
mdefine_line|#define DASD_FBA_CCW_READ 0x42
DECL|macro|DASD_FBA_CCW_LOCATE
mdefine_line|#define DASD_FBA_CCW_LOCATE 0x43
DECL|macro|DASD_FBA_CCW_DEFINE_EXTENT
mdefine_line|#define DASD_FBA_CCW_DEFINE_EXTENT 0x63
DECL|variable|dasd_fba_discipline
id|dasd_discipline_t
id|dasd_fba_discipline
suffix:semicolon
r_typedef
r_struct
DECL|struct|dasd_fba_private_t
id|dasd_fba_private_t
(brace
DECL|member|rdc_data
id|dasd_fba_characteristics_t
id|rdc_data
suffix:semicolon
DECL|typedef|dasd_fba_private_t
)brace
id|dasd_fba_private_t
suffix:semicolon
macro_line|#ifdef CONFIG_DASD_DYNAMIC
r_static
DECL|variable|dasd_fba_known_devices
id|devreg_t
id|dasd_fba_known_devices
(braket
)braket
op_assign
(brace
(brace
id|ci
suffix:colon
(brace
id|hc
suffix:colon
(brace
id|ctype
suffix:colon
l_int|0x6310
comma
id|dtype
suffix:colon
l_int|0x9336
)brace
)brace
comma
id|flag
suffix:colon
(paren
id|DEVREG_MATCH_CU_TYPE
op_or
id|DEVREG_MATCH_DEV_TYPE
op_or
id|DEVREG_TYPE_DEVCHARS
)paren
comma
id|oper_func
suffix:colon
id|dasd_oper_handler
)brace
comma
(brace
id|ci
suffix:colon
(brace
id|hc
suffix:colon
(brace
id|ctype
suffix:colon
l_int|0x3880
comma
id|dtype
suffix:colon
l_int|0x3370
)brace
)brace
comma
id|flag
suffix:colon
(paren
id|DEVREG_MATCH_CU_TYPE
op_or
id|DEVREG_MATCH_DEV_TYPE
op_or
id|DEVREG_TYPE_DEVCHARS
)paren
comma
id|oper_func
suffix:colon
id|dasd_oper_handler
)brace
)brace
suffix:semicolon
macro_line|#endif
r_static
r_inline
r_void
DECL|function|define_extent
id|define_extent
(paren
id|ccw1_t
op_star
id|ccw
comma
id|DE_fba_data_t
op_star
id|DE_data
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
id|memset
(paren
id|DE_data
comma
l_int|0
comma
r_sizeof
(paren
id|DE_fba_data_t
)paren
)paren
suffix:semicolon
id|ccw-&gt;cmd_code
op_assign
id|DASD_FBA_CCW_DEFINE_EXTENT
suffix:semicolon
id|ccw-&gt;count
op_assign
l_int|16
suffix:semicolon
id|set_normalized_cda
(paren
id|ccw
comma
id|__pa
(paren
id|DE_data
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
id|DE_data-&gt;mask
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
id|DE_data-&gt;mask
)paren
dot
id|perm
op_assign
l_int|0x1
suffix:semicolon
r_else
id|DE_data-&gt;mask.perm
op_assign
l_int|0x2
suffix:semicolon
id|DE_data-&gt;blk_size
op_assign
id|blksize
suffix:semicolon
id|DE_data-&gt;ext_loc
op_assign
id|beg
suffix:semicolon
id|DE_data-&gt;ext_end
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
(paren
id|ccw1_t
op_star
id|ccw
comma
id|LO_fba_data_t
op_star
id|LO_data
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
id|memset
(paren
id|LO_data
comma
l_int|0
comma
r_sizeof
(paren
id|LO_fba_data_t
)paren
)paren
suffix:semicolon
id|ccw-&gt;cmd_code
op_assign
id|DASD_FBA_CCW_LOCATE
suffix:semicolon
id|ccw-&gt;count
op_assign
l_int|8
suffix:semicolon
id|set_normalized_cda
(paren
id|ccw
comma
id|__pa
(paren
id|LO_data
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
id|LO_data-&gt;operation.cmd
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
id|LO_data-&gt;operation.cmd
op_assign
l_int|0x6
suffix:semicolon
r_else
id|LO_data-&gt;operation.cmd
op_assign
l_int|0x8
suffix:semicolon
id|LO_data-&gt;blk_nr
op_assign
id|block_nr
suffix:semicolon
id|LO_data-&gt;blk_ct
op_assign
id|block_ct
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_fba_id_check
id|dasd_fba_id_check
(paren
id|s390_dev_info_t
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;sid_data.cu_type
op_eq
l_int|0x3880
)paren
r_if
c_cond
(paren
id|info-&gt;sid_data.dev_type
op_eq
l_int|0x3370
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;sid_data.cu_type
op_eq
l_int|0x6310
)paren
r_if
c_cond
(paren
id|info-&gt;sid_data.dev_type
op_eq
l_int|0x9336
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_fba_check_characteristics
id|dasd_fba_check_characteristics
(paren
r_struct
id|dasd_device_t
op_star
id|device
)paren
(brace
r_int
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_void
op_star
id|rdc_data
suffix:semicolon
id|dasd_fba_private_t
op_star
r_private
suffix:semicolon
r_if
c_cond
(paren
id|device
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
id|KERN_WARNING
id|PRINTK_HEADER
l_string|&quot;Null device pointer passed to characteristics checker&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|device
op_member_access_from_pointer
r_private
op_ne
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|device
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
)brace
id|device
op_member_access_from_pointer
r_private
op_assign
id|kmalloc
(paren
r_sizeof
(paren
id|dasd_fba_private_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device
op_member_access_from_pointer
r_private
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
id|KERN_WARNING
id|PRINTK_HEADER
l_string|&quot;memory allocation failed for private data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_private
op_assign
(paren
id|dasd_fba_private_t
op_star
)paren
id|device
op_member_access_from_pointer
r_private
suffix:semicolon
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
(paren
id|device-&gt;devinfo.irq
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
id|printk
(paren
id|KERN_WARNING
id|PRINTK_HEADER
l_string|&quot;Read device characteristics returned error %d&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|kfree
c_func
(paren
r_private
)paren
suffix:semicolon
id|device
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
id|PRINTK_HEADER
l_string|&quot;%04X on sch %d: %04X/%02X(CU:%04X/%02X) %dMB at(%d B/blk)&bslash;n&quot;
comma
id|device-&gt;devinfo.devno
comma
id|device-&gt;devinfo.irq
comma
id|device-&gt;devinfo.sid_data.dev_type
comma
id|device-&gt;devinfo.sid_data.dev_model
comma
id|device-&gt;devinfo.sid_data.cu_type
comma
id|device-&gt;devinfo.sid_data.cu_model
comma
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
(paren
r_struct
id|dasd_device_t
op_star
id|device
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
id|sb
suffix:semicolon
id|dasd_fba_private_t
op_star
r_private
op_assign
(paren
id|dasd_fba_private_t
op_star
)paren
id|device
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|bs
op_assign
r_private
op_member_access_from_pointer
id|rdc_data.blk_size
suffix:semicolon
id|memset
(paren
op_amp
(paren
id|device-&gt;sizes
)paren
comma
l_int|0
comma
r_sizeof
(paren
id|dasd_sizes_t
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|bs
)paren
(brace
r_case
l_int|512
suffix:colon
r_case
l_int|1024
suffix:colon
r_case
l_int|2048
suffix:colon
r_case
l_int|4096
suffix:colon
id|device-&gt;sizes.bp_block
op_assign
id|bs
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
id|KERN_INFO
id|PRINTK_HEADER
l_string|&quot;/dev/%s (%04X): unknown blocksize %d&bslash;n&quot;
comma
id|device-&gt;name
comma
id|device-&gt;devinfo.devno
comma
id|bs
)paren
suffix:semicolon
r_return
op_minus
id|EMEDIUMTYPE
suffix:semicolon
)brace
id|device-&gt;sizes.s2b_shift
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
id|bs
suffix:semicolon
id|sb
op_assign
id|sb
op_lshift
l_int|1
)paren
id|device-&gt;sizes.s2b_shift
op_increment
suffix:semicolon
id|device-&gt;sizes.blocks
op_assign
(paren
r_private
op_member_access_from_pointer
id|rdc_data.blk_bdsa
)paren
suffix:semicolon
id|device-&gt;sizes.pt_block
op_assign
l_int|1
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_fba_fill_geometry
id|dasd_fba_fill_geometry
(paren
r_struct
id|dasd_device_t
op_star
id|device
comma
r_struct
id|hd_geometry
op_star
id|geo
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|sectors
op_assign
id|device-&gt;sizes.blocks
op_lshift
id|device-&gt;sizes.s2b_shift
suffix:semicolon
r_int
r_int
id|tracks
op_assign
id|sectors
op_rshift
l_int|6
suffix:semicolon
r_int
r_int
id|cyls
op_assign
id|tracks
op_rshift
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|device-&gt;sizes.bp_block
)paren
(brace
r_case
l_int|512
suffix:colon
r_case
l_int|1024
suffix:colon
r_case
l_int|2048
suffix:colon
r_case
l_int|4096
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|geo-&gt;cylinders
op_assign
id|cyls
suffix:semicolon
id|geo-&gt;heads
op_assign
l_int|16
suffix:semicolon
id|geo-&gt;sectors
op_assign
l_int|128
op_rshift
id|device-&gt;sizes.s2b_shift
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
id|dasd_era_t
DECL|function|dasd_fba_examine_error
id|dasd_fba_examine_error
(paren
id|ccw_req_t
op_star
id|cqr
comma
id|devstat_t
op_star
id|stat
)paren
(brace
id|dasd_device_t
op_star
id|device
op_assign
(paren
id|dasd_device_t
op_star
)paren
id|cqr-&gt;device
suffix:semicolon
r_if
c_cond
(paren
id|stat-&gt;cstat
op_eq
l_int|0x00
op_logical_and
id|stat-&gt;dstat
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
r_switch
c_cond
(paren
id|device-&gt;devinfo.sid_data.dev_model
)paren
(brace
r_case
l_int|0x3370
suffix:colon
r_return
id|dasd_3370_erp_examine
(paren
id|cqr
comma
id|stat
)paren
suffix:semicolon
r_case
l_int|0x9336
suffix:colon
r_return
id|dasd_9336_erp_examine
(paren
id|cqr
comma
id|stat
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
id|dasd_erp_action_fn_t
DECL|function|dasd_fba_erp_action
id|dasd_fba_erp_action
(paren
id|ccw_req_t
op_star
id|cqr
)paren
(brace
r_return
id|default_erp_action
suffix:semicolon
)brace
r_static
id|dasd_erp_postaction_fn_t
DECL|function|dasd_fba_erp_postaction
id|dasd_fba_erp_postaction
(paren
id|ccw_req_t
op_star
id|cqr
)paren
(brace
r_if
c_cond
(paren
id|cqr-&gt;function
op_eq
id|default_erp_action
)paren
r_return
id|default_erp_postaction
suffix:semicolon
id|printk
(paren
id|KERN_WARNING
id|PRINTK_HEADER
l_string|&quot;unknown ERP action %p&bslash;n&quot;
comma
id|cqr-&gt;function
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
id|ccw_req_t
op_star
DECL|function|dasd_fba_build_cp_from_req
id|dasd_fba_build_cp_from_req
(paren
id|dasd_device_t
op_star
id|device
comma
r_struct
id|request
op_star
id|req
)paren
(brace
id|ccw_req_t
op_star
id|rw_cp
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rw_cmd
suffix:semicolon
r_int
id|bhct
comma
id|i
suffix:semicolon
r_int
id|size
suffix:semicolon
id|ccw1_t
op_star
id|ccw
suffix:semicolon
id|DE_fba_data_t
op_star
id|DE_data
suffix:semicolon
id|LO_fba_data_t
op_star
id|LO_data
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|dasd_fba_private_t
op_star
r_private
op_assign
(paren
id|dasd_fba_private_t
op_star
)paren
id|device
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|byt_per_blk
op_assign
id|device-&gt;sizes.bp_block
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;cmd
op_eq
id|READ
)paren
(brace
id|rw_cmd
op_assign
id|DASD_FBA_CCW_READ
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|req-&gt;cmd
op_eq
id|WRITE
)paren
(brace
id|rw_cmd
op_assign
id|DASD_FBA_CCW_WRITE
suffix:semicolon
)brace
r_else
(brace
id|PRINT_ERR
(paren
l_string|&quot;Unknown command %d&bslash;n&quot;
comma
id|req-&gt;cmd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Build the request */
multiline_comment|/* count bhs to prevent errors, when bh smaller than block */
id|bhct
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|bh
op_assign
id|req-&gt;bh
suffix:semicolon
id|bh
suffix:semicolon
id|bh
op_assign
id|bh-&gt;b_reqnext
)paren
(brace
r_if
c_cond
(paren
id|bh-&gt;b_size
OG
id|byt_per_blk
)paren
r_for
c_loop
(paren
id|size
op_assign
l_int|0
suffix:semicolon
id|size
OL
id|bh-&gt;b_size
suffix:semicolon
id|size
op_add_assign
id|byt_per_blk
)paren
id|bhct
op_increment
suffix:semicolon
r_else
id|bhct
op_increment
suffix:semicolon
)brace
id|rw_cp
op_assign
id|dasd_alloc_request
(paren
id|dasd_fba_discipline.name
comma
l_int|1
op_plus
l_int|2
op_star
id|bhct
comma
r_sizeof
(paren
id|DE_fba_data_t
)paren
op_plus
id|bhct
op_star
r_sizeof
(paren
id|LO_fba_data_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rw_cp
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|DE_data
op_assign
id|rw_cp-&gt;data
suffix:semicolon
id|LO_data
op_assign
id|rw_cp-&gt;data
op_plus
r_sizeof
(paren
id|DE_fba_data_t
)paren
suffix:semicolon
id|ccw
op_assign
id|rw_cp-&gt;cpaddr
suffix:semicolon
id|define_extent
(paren
id|ccw
comma
id|DE_data
comma
id|req-&gt;cmd
comma
id|byt_per_blk
comma
id|req-&gt;sector
comma
id|req-&gt;nr_sectors
)paren
suffix:semicolon
id|ccw-&gt;flags
op_or_assign
id|CCW_FLAG_CC
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|bh
op_assign
id|req-&gt;bh
suffix:semicolon
id|bh
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|bh-&gt;b_size
OG
id|byt_per_blk
)paren
(brace
r_for
c_loop
(paren
id|size
op_assign
l_int|0
suffix:semicolon
id|size
OL
id|bh-&gt;b_size
suffix:semicolon
id|size
op_add_assign
id|byt_per_blk
)paren
(brace
id|ccw
op_increment
suffix:semicolon
id|locate_record
(paren
id|ccw
comma
id|LO_data
comma
id|req-&gt;cmd
comma
id|i
comma
l_int|1
)paren
suffix:semicolon
id|ccw-&gt;flags
op_or_assign
id|CCW_FLAG_CC
suffix:semicolon
id|ccw
op_increment
suffix:semicolon
id|ccw-&gt;flags
op_or_assign
id|CCW_FLAG_CC
op_or
id|CCW_FLAG_SLI
suffix:semicolon
id|ccw-&gt;cmd_code
op_assign
id|rw_cmd
suffix:semicolon
id|ccw-&gt;count
op_assign
id|byt_per_blk
suffix:semicolon
id|set_normalized_cda
(paren
id|ccw
comma
id|__pa
(paren
id|bh-&gt;b_data
op_plus
id|size
)paren
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|LO_data
op_increment
suffix:semicolon
)brace
id|bh
op_assign
id|bh-&gt;b_reqnext
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* group N bhs to fit into byt_per_blk */
r_for
c_loop
(paren
id|size
op_assign
l_int|0
suffix:semicolon
id|bh
op_ne
l_int|NULL
op_logical_and
id|size
OL
id|byt_per_blk
suffix:semicolon
)paren
(brace
id|ccw
op_increment
suffix:semicolon
id|locate_record
(paren
id|ccw
comma
id|LO_data
comma
id|req-&gt;cmd
comma
id|i
comma
l_int|1
)paren
suffix:semicolon
id|ccw-&gt;flags
op_or_assign
id|CCW_FLAG_CC
suffix:semicolon
id|ccw
op_increment
suffix:semicolon
r_if
c_cond
(paren
r_private
op_member_access_from_pointer
id|rdc_data.mode.bits.data_chain
)paren
(brace
id|ccw-&gt;flags
op_or_assign
id|CCW_FLAG_DC
op_or
id|CCW_FLAG_SLI
suffix:semicolon
)brace
r_else
(brace
id|PRINT_WARN
(paren
l_string|&quot;Cannot chain chunks smaller than one block&bslash;n&quot;
)paren
suffix:semicolon
id|ccw_free_request
(paren
id|rw_cp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ccw-&gt;cmd_code
op_assign
id|rw_cmd
suffix:semicolon
id|ccw-&gt;count
op_assign
id|bh-&gt;b_size
suffix:semicolon
id|set_normalized_cda
(paren
id|ccw
comma
id|__pa
(paren
id|bh-&gt;b_data
)paren
)paren
suffix:semicolon
id|size
op_add_assign
id|bh-&gt;b_size
suffix:semicolon
id|bh
op_assign
id|bh-&gt;b_reqnext
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|LO_data
op_increment
suffix:semicolon
)brace
id|ccw-&gt;flags
op_and_assign
op_complement
id|CCW_FLAG_DC
suffix:semicolon
id|ccw-&gt;flags
op_or_assign
id|CCW_FLAG_CC
op_or
id|CCW_FLAG_SLI
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ne
id|byt_per_blk
)paren
(brace
id|PRINT_WARN
(paren
l_string|&quot;Cannot fulfill request smaller than block&bslash;n&quot;
)paren
suffix:semicolon
id|ccw_free_request
(paren
id|rw_cp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
id|ccw-&gt;flags
op_and_assign
op_complement
(paren
id|CCW_FLAG_DC
op_or
id|CCW_FLAG_CC
)paren
suffix:semicolon
id|rw_cp-&gt;device
op_assign
id|device
suffix:semicolon
id|rw_cp-&gt;expires
op_assign
l_int|5
op_star
id|TOD_MIN
suffix:semicolon
multiline_comment|/* 5 minutes */
id|rw_cp-&gt;req
op_assign
id|req
suffix:semicolon
id|check_then_set
(paren
op_amp
id|rw_cp-&gt;status
comma
id|CQR_STATUS_EMPTY
comma
id|CQR_STATUS_FILLED
)paren
suffix:semicolon
r_return
id|rw_cp
suffix:semicolon
)brace
r_static
r_char
op_star
DECL|function|dasd_fba_dump_sense
id|dasd_fba_dump_sense
(paren
r_struct
id|dasd_device_t
op_star
id|device
comma
id|ccw_req_t
op_star
id|req
)paren
(brace
r_char
op_star
id|page
op_assign
(paren
r_char
op_star
)paren
id|get_free_page
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|page
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|len
op_assign
id|sprintf
(paren
id|page
comma
id|KERN_WARNING
id|PRINTK_HEADER
l_string|&quot;device %04X on irq %d: I/O status report:&bslash;n&quot;
comma
id|device-&gt;devinfo.devno
comma
id|device-&gt;devinfo.irq
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|variable|dasd_fba_discipline
id|dasd_discipline_t
id|dasd_fba_discipline
op_assign
(brace
id|name
suffix:colon
l_string|&quot;FBA &quot;
comma
id|ebcname
suffix:colon
l_string|&quot;FBA &quot;
comma
id|max_blocks
suffix:colon
(paren
(paren
id|PAGE_SIZE
op_rshift
l_int|1
)paren
op_div
r_sizeof
(paren
id|ccw1_t
)paren
op_minus
l_int|1
)paren
comma
id|id_check
suffix:colon
id|dasd_fba_id_check
comma
id|check_characteristics
suffix:colon
id|dasd_fba_check_characteristics
comma
id|do_analysis
suffix:colon
id|dasd_fba_do_analysis
comma
id|fill_geometry
suffix:colon
id|dasd_fba_fill_geometry
comma
id|start_IO
suffix:colon
id|dasd_start_IO
comma
id|examine_error
suffix:colon
id|dasd_fba_examine_error
comma
id|erp_action
suffix:colon
id|dasd_fba_erp_action
comma
id|erp_postaction
suffix:colon
id|dasd_fba_erp_postaction
comma
id|build_cp_from_req
suffix:colon
id|dasd_fba_build_cp_from_req
comma
id|dump_sense
suffix:colon
id|dasd_fba_dump_sense
comma
id|int_handler
suffix:colon
id|dasd_int_handler
)brace
suffix:semicolon
r_int
DECL|function|dasd_fba_init
id|dasd_fba_init
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|printk
(paren
id|KERN_INFO
id|PRINTK_HEADER
l_string|&quot;%s discipline initializing&bslash;n&quot;
comma
id|dasd_fba_discipline.name
)paren
suffix:semicolon
id|ASCEBC
(paren
id|dasd_fba_discipline.ebcname
comma
l_int|4
)paren
suffix:semicolon
id|dasd_discipline_enq
(paren
op_amp
id|dasd_fba_discipline
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DASD_DYNAMIC 
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
r_sizeof
(paren
id|dasd_fba_known_devices
)paren
op_div
r_sizeof
(paren
id|devreg_t
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PRINTK_HEADER
l_string|&quot;We are interested in: CU %04X/%02x&bslash;n&quot;
comma
id|dasd_fba_known_devices
(braket
id|i
)braket
dot
id|ci.hc.ctype
comma
id|dasd_fba_known_devices
(braket
id|i
)braket
dot
id|ci.hc.cmode
)paren
suffix:semicolon
id|s390_device_register
(paren
op_amp
id|dasd_fba_known_devices
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif&t;&t;&t;&t;/* CONFIG_DASD_DYNAMIC */
r_return
id|rc
suffix:semicolon
)brace
r_void
DECL|function|dasd_fba_cleanup
id|dasd_fba_cleanup
c_func
(paren
r_void
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PRINTK_HEADER
l_string|&quot;%s discipline cleaning up&bslash;n&quot;
comma
id|dasd_fba_discipline.name
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DASD_DYNAMIC
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
r_sizeof
(paren
id|dasd_fba_known_devices
)paren
op_div
r_sizeof
(paren
id|devreg_t
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PRINTK_HEADER
l_string|&quot;We were interested in: CU %04X/%02x&bslash;n&quot;
comma
id|dasd_fba_known_devices
(braket
id|i
)braket
dot
id|ci.hc.ctype
comma
id|dasd_fba_known_devices
(braket
id|i
)braket
dot
id|ci.hc.cmode
)paren
suffix:semicolon
id|s390_device_unregister
c_func
(paren
op_amp
id|dasd_fba_known_devices
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_DASD_DYNAMIC */
id|dasd_discipline_deq
c_func
(paren
op_amp
id|dasd_fba_discipline
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
