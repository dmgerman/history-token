multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999,2000&n; *&n; * History of changes (starts July 2000)&n; */
macro_line|#ifndef DASD_H
DECL|macro|DASD_H
mdefine_line|#define DASD_H
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|IOCTL_LETTER
mdefine_line|#define IOCTL_LETTER &squot;D&squot;
multiline_comment|/* Disable the volume (for Linux) */
DECL|macro|BIODASDDISABLE
mdefine_line|#define BIODASDDISABLE _IO(IOCTL_LETTER,0) 
multiline_comment|/* Enable the volume (for Linux) */
DECL|macro|BIODASDENABLE
mdefine_line|#define BIODASDENABLE  _IO(IOCTL_LETTER,1) 
multiline_comment|/* Issue a reserve/release command, rsp. */
DECL|macro|BIODASDRSRV
mdefine_line|#define BIODASDRSRV    _IO(IOCTL_LETTER,2) /* reserve */
DECL|macro|BIODASDRLSE
mdefine_line|#define BIODASDRLSE    _IO(IOCTL_LETTER,3) /* release */
DECL|macro|BIODASDSLCK
mdefine_line|#define BIODASDSLCK    _IO(IOCTL_LETTER,4) /* steal lock */
multiline_comment|/* Read sense ID infpormation */
DECL|macro|BIODASDRSID
mdefine_line|#define BIODASDRSID    _IOR(IOCTL_LETTER,0,senseid_t)
multiline_comment|/* Format the volume or an extent */
DECL|macro|BIODASDFORMAT
mdefine_line|#define BIODASDFORMAT  _IOW(IOCTL_LETTER,0,format_data_t) 
multiline_comment|/* translate blocknumber of partition to absolute */
DECL|macro|BIODASDRWTB
mdefine_line|#define BIODASDRWTB    _IOWR(IOCTL_LETTER,0,int)
DECL|macro|DASD_NAME
mdefine_line|#define DASD_NAME &quot;dasd&quot;
DECL|macro|DASD_PARTN_BITS
mdefine_line|#define DASD_PARTN_BITS 2
DECL|macro|DASD_PER_MAJOR
mdefine_line|#define DASD_PER_MAJOR ( 1U&lt;&lt;(MINORBITS-DASD_PARTN_BITS))
multiline_comment|/* &n; * struct format_data_t&n; * represents all data necessary to format a dasd&n; */
DECL|struct|format_data_t
r_typedef
r_struct
id|format_data_t
(brace
DECL|member|start_unit
r_int
id|start_unit
suffix:semicolon
multiline_comment|/* from track */
DECL|member|stop_unit
r_int
id|stop_unit
suffix:semicolon
multiline_comment|/* to track */
DECL|member|blksize
r_int
id|blksize
suffix:semicolon
multiline_comment|/* sectorsize */
DECL|member|intensity
r_int
id|intensity
suffix:semicolon
multiline_comment|/* 0: normal, 1:record zero, 3:home address, 4 invalidate tracks */
DECL|typedef|format_data_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|format_data_t
suffix:semicolon
DECL|macro|DASD_FORMAT_DEFAULT_START_UNIT
mdefine_line|#define DASD_FORMAT_DEFAULT_START_UNIT 0
DECL|macro|DASD_FORMAT_DEFAULT_STOP_UNIT
mdefine_line|#define DASD_FORMAT_DEFAULT_STOP_UNIT -1
DECL|macro|DASD_FORMAT_DEFAULT_BLOCKSIZE
mdefine_line|#define DASD_FORMAT_DEFAULT_BLOCKSIZE -1
DECL|macro|DASD_FORMAT_DEFAULT_INTENSITY
mdefine_line|#define DASD_FORMAT_DEFAULT_INTENSITY -1
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/ccwcache.h&gt;
macro_line|#include &lt;linux/blk.h&gt; 
macro_line|#if (LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,3,98))
macro_line|#include &lt;linux/blkdev.h&gt; 
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/compatmac.h&gt;
macro_line|#include &lt;asm/s390dyn.h&gt;
macro_line|#include &lt;asm/todclk.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
multiline_comment|/* Kernel Version Compatibility section */
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,98))
DECL|typedef|request_queue_t
r_typedef
r_struct
id|request
op_star
id|request_queue_t
suffix:semicolon
DECL|macro|block_device_operations
mdefine_line|#define block_device_operations file_operations
DECL|macro|__setup
mdefine_line|#define __setup(x,y) struct dasd_device_t
DECL|macro|devfs_register_blkdev
mdefine_line|#define devfs_register_blkdev(major,name,ops) register_blkdev(major,name,ops)
DECL|macro|register_disk
mdefine_line|#define register_disk(dd,dev,partn,ops,size) &bslash;&n;do { &bslash;&n;&t;dd-&gt;sizes[MINOR(dev)] = size &gt;&gt; 1; &bslash;&n;&t;resetup_one_dev(dd,MINOR(dev)&gt;&gt;DASD_PARTN_BITS); &bslash;&n;} while(0)
DECL|macro|init_waitqueue_head
mdefine_line|#define init_waitqueue_head(x) do { *x = NULL; } while(0)
DECL|macro|blk_cleanup_queue
mdefine_line|#define blk_cleanup_queue(x) do {} while(0)
DECL|macro|blk_init_queue
mdefine_line|#define blk_init_queue(x...) do {} while(0)
DECL|macro|blk_queue_headactive
mdefine_line|#define blk_queue_headactive(x...) do {} while(0)
DECL|macro|blk_queue_make_request
mdefine_line|#define blk_queue_make_request(x) do {} while(0)
DECL|macro|list_empty
mdefine_line|#define list_empty(x) (0)
DECL|macro|INIT_BLK_DEV
mdefine_line|#define INIT_BLK_DEV(d_major,d_request_fn,d_queue_fn,d_current) &bslash;&n;do { &bslash;&n;        blk_dev[d_major].request_fn = d_request_fn; &bslash;&n;        blk_dev[d_major].queue = d_queue_fn; &bslash;&n;        blk_dev[d_major].current_request = d_current; &bslash;&n;} while(0)
DECL|macro|INIT_GENDISK
mdefine_line|#define INIT_GENDISK(D_MAJOR,D_NAME,D_PARTN_BITS,D_PER_MAJOR) &bslash;&n;&t;major:D_MAJOR, &bslash;&n;&t;major_name:D_NAME, &bslash;&n;&t;minor_shift:D_PARTN_BITS, &bslash;&n;&t;max_p:1 &lt;&lt; D_PARTN_BITS, &bslash;&n;&t;max_nr:D_PER_MAJOR, &bslash;&n;&t;nr_real:D_PER_MAJOR,
r_static
r_inline
r_struct
id|request
op_star
DECL|function|dasd_next_request
id|dasd_next_request
c_func
(paren
id|request_queue_t
op_star
id|queue
)paren
(brace
r_return
op_star
id|queue
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dasd_dequeue_request
id|dasd_dequeue_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|request
op_star
id|req
)paren
(brace
op_star
id|q
op_assign
id|req-&gt;next
suffix:semicolon
id|req-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#else
DECL|macro|INIT_BLK_DEV
mdefine_line|#define INIT_BLK_DEV(d_major,d_request_fn,d_queue_fn,d_current) &bslash;&n;do { &bslash;&n;        blk_dev[d_major].queue = d_queue_fn; &bslash;&n;} while(0)
DECL|macro|INIT_GENDISK
mdefine_line|#define INIT_GENDISK(D_MAJOR,D_NAME,D_PARTN_BITS,D_PER_MAJOR) &bslash;&n;&t;major:D_MAJOR, &bslash;&n;&t;major_name:D_NAME, &bslash;&n;&t;minor_shift:D_PARTN_BITS, &bslash;&n;&t;max_p:1 &lt;&lt; D_PARTN_BITS, &bslash;&n;&t;nr_real:D_PER_MAJOR,
r_static
r_inline
r_struct
id|request
op_star
DECL|function|dasd_next_request
id|dasd_next_request
c_func
(paren
id|request_queue_t
op_star
id|queue
)paren
(brace
r_return
id|blkdev_entry_next_request
c_func
(paren
op_amp
id|queue-&gt;queue_head
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dasd_dequeue_request
id|dasd_dequeue_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|request
op_star
id|req
)paren
(brace
id|blkdev_dequeue_request
(paren
id|req
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* dasd_range_t are used for dynamic device att-/detachment */
DECL|struct|dasd_devreg_t
r_typedef
r_struct
id|dasd_devreg_t
(brace
DECL|member|devreg
id|devreg_t
id|devreg
suffix:semicolon
multiline_comment|/* the devreg itself */
multiline_comment|/* build a linked list of devregs, needed for cleanup */
DECL|member|next
r_struct
id|dasd_devreg_t
op_star
id|next
suffix:semicolon
DECL|typedef|dasd_devreg_t
)brace
id|dasd_devreg_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|dasd_era_fatal
id|dasd_era_fatal
op_assign
op_minus
l_int|1
comma
multiline_comment|/* no chance to recover              */
DECL|enumerator|dasd_era_none
id|dasd_era_none
op_assign
l_int|0
comma
multiline_comment|/* don&squot;t recover, everything alright */
DECL|enumerator|dasd_era_msg
id|dasd_era_msg
op_assign
l_int|1
comma
multiline_comment|/* don&squot;t recover, just report...     */
DECL|enumerator|dasd_era_recover
id|dasd_era_recover
op_assign
l_int|2
multiline_comment|/* recovery action recommended       */
DECL|typedef|dasd_era_t
)brace
id|dasd_era_t
suffix:semicolon
multiline_comment|/* BIT DEFINITIONS FOR SENSE DATA */
DECL|macro|DASD_SENSE_BIT_0
mdefine_line|#define DASD_SENSE_BIT_0 0x80
DECL|macro|DASD_SENSE_BIT_1
mdefine_line|#define DASD_SENSE_BIT_1 0x40
DECL|macro|DASD_SENSE_BIT_2
mdefine_line|#define DASD_SENSE_BIT_2 0x20
DECL|macro|DASD_SENSE_BIT_3
mdefine_line|#define DASD_SENSE_BIT_3 0x10
DECL|macro|check_then_set
mdefine_line|#define check_then_set(where,from,to) &bslash;&n;do { &bslash;&n;        if ((*(where)) != (from) ) { &bslash;&n;                printk (KERN_ERR PRINTK_HEADER &quot;was %d&bslash;n&quot;, *(where)); &bslash;&n;                BUG(); &bslash;&n;        } &bslash;&n;        (*(where)) = (to); &bslash;&n;} while (0)
DECL|macro|DASD_MESSAGE
mdefine_line|#define DASD_MESSAGE(d_loglevel,d_device,d_string,d_args...)&bslash;&n;do { &bslash;&n;        int d_devno = d_device-&gt;devinfo.devno; &bslash;&n;        int d_irq = d_device-&gt;devinfo.irq; &bslash;&n;        char *d_name = d_device-&gt;name; &bslash;&n;        int d_major = MAJOR(d_device-&gt;kdev); &bslash;&n;        int d_minor = MINOR(d_device-&gt;kdev); &bslash;&n;        printk(d_loglevel PRINTK_HEADER &bslash;&n;               &quot;/dev/%s(%d:%d), 0x%04X on SCH 0x%x:&quot; &bslash;&n;               d_string &quot;&bslash;n&quot;,d_name,d_major,d_minor,d_devno,d_irq,d_args ); &bslash;&n;} while(0)
multiline_comment|/* &n; * struct dasd_sizes_t&n; * represents all data needed to access dasd with properly set up sectors&n; */
r_typedef
DECL|struct|dasd_sizes_t
r_struct
id|dasd_sizes_t
(brace
DECL|member|blocks
r_int
r_int
id|blocks
suffix:semicolon
multiline_comment|/* size of volume in blocks */
DECL|member|bp_block
r_int
r_int
id|bp_block
suffix:semicolon
multiline_comment|/* bytes per block */
DECL|member|s2b_shift
r_int
r_int
id|s2b_shift
suffix:semicolon
multiline_comment|/* log2 (bp_block/512) */
DECL|typedef|dasd_sizes_t
)brace
id|dasd_sizes_t
suffix:semicolon
multiline_comment|/* &n; * struct dasd_chanq_t &n; * represents a queue of channel programs related to a single device&n; */
r_typedef
DECL|struct|dasd_chanq_t
r_struct
id|dasd_chanq_t
(brace
DECL|member|head
id|ccw_req_t
op_star
id|head
suffix:semicolon
DECL|member|tail
id|ccw_req_t
op_star
id|tail
suffix:semicolon
DECL|typedef|dasd_chanq_t
)brace
id|dasd_chanq_t
suffix:semicolon
r_struct
id|dasd_device_t
suffix:semicolon
r_struct
id|request
suffix:semicolon
multiline_comment|/* &n; * signatures for the functions of dasd_discipline_t &n; * make typecasts much easier&n; */
DECL|typedef|dasd_erp_action_fn_t
r_typedef
id|ccw_req_t
op_star
(paren
op_star
id|dasd_erp_action_fn_t
)paren
(paren
id|ccw_req_t
op_star
id|cqr
)paren
suffix:semicolon
DECL|typedef|dasd_erp_postaction_fn_t
r_typedef
id|ccw_req_t
op_star
(paren
op_star
id|dasd_erp_postaction_fn_t
)paren
(paren
id|ccw_req_t
op_star
id|cqr
)paren
suffix:semicolon
DECL|typedef|dasd_ck_id_fn_t
r_typedef
r_int
(paren
op_star
id|dasd_ck_id_fn_t
)paren
(paren
id|dev_info_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_ck_characteristics_fn_t
r_typedef
r_int
(paren
op_star
id|dasd_ck_characteristics_fn_t
)paren
(paren
r_struct
id|dasd_device_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_fill_geometry_fn_t
r_typedef
r_int
(paren
op_star
id|dasd_fill_geometry_fn_t
)paren
(paren
r_struct
id|dasd_device_t
op_star
comma
r_struct
id|hd_geometry
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_format_fn_t
r_typedef
id|ccw_req_t
op_star
(paren
op_star
id|dasd_format_fn_t
)paren
(paren
r_struct
id|dasd_device_t
op_star
comma
r_struct
id|format_data_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_init_analysis_fn_t
r_typedef
id|ccw_req_t
op_star
(paren
op_star
id|dasd_init_analysis_fn_t
)paren
(paren
r_struct
id|dasd_device_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_do_analysis_fn_t
r_typedef
r_int
(paren
op_star
id|dasd_do_analysis_fn_t
)paren
(paren
r_struct
id|dasd_device_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_io_starter_fn_t
r_typedef
r_int
(paren
op_star
id|dasd_io_starter_fn_t
)paren
(paren
id|ccw_req_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_int_handler_fn_t
r_typedef
r_void
(paren
op_star
id|dasd_int_handler_fn_t
)paren
(paren
r_int
id|irq
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_error_examine_fn_t
r_typedef
id|dasd_era_t
(paren
op_star
id|dasd_error_examine_fn_t
)paren
(paren
id|ccw_req_t
op_star
comma
id|devstat_t
op_star
id|stat
)paren
suffix:semicolon
DECL|typedef|dasd_error_analyse_fn_t
r_typedef
id|dasd_erp_action_fn_t
(paren
op_star
id|dasd_error_analyse_fn_t
)paren
(paren
id|ccw_req_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_erp_analyse_fn_t
r_typedef
id|dasd_erp_postaction_fn_t
(paren
op_star
id|dasd_erp_analyse_fn_t
)paren
(paren
id|ccw_req_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_cp_builder_fn_t
r_typedef
id|ccw_req_t
op_star
(paren
op_star
id|dasd_cp_builder_fn_t
)paren
(paren
r_struct
id|dasd_device_t
op_star
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_dump_sense_fn_t
r_typedef
r_char
op_star
(paren
op_star
id|dasd_dump_sense_fn_t
)paren
(paren
r_struct
id|dasd_device_t
op_star
comma
id|ccw_req_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_reserve_fn_t
r_typedef
id|ccw_req_t
op_star
(paren
op_star
id|dasd_reserve_fn_t
)paren
(paren
r_struct
id|dasd_device_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_release_fn_t
r_typedef
id|ccw_req_t
op_star
(paren
op_star
id|dasd_release_fn_t
)paren
(paren
r_struct
id|dasd_device_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_merge_cp_fn_t
r_typedef
id|ccw_req_t
op_star
(paren
op_star
id|dasd_merge_cp_fn_t
)paren
(paren
r_struct
id|dasd_device_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * the dasd_discipline_t is&n; * sth like a table of virtual functions, if you think of dasd_eckd&n; * inheriting dasd...&n; * no, currently we are not planning to reimplement the driver in C++&n; */
DECL|struct|dasd_discipline_t
r_typedef
r_struct
id|dasd_discipline_t
(brace
DECL|member|ebcname
r_char
id|ebcname
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* a name used for tagging and printks */
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* a name used for tagging and printks */
DECL|member|id_check
id|dasd_ck_id_fn_t
id|id_check
suffix:semicolon
multiline_comment|/* to check sense data */
DECL|member|check_characteristics
id|dasd_ck_characteristics_fn_t
id|check_characteristics
suffix:semicolon
multiline_comment|/* to check the characteristics */
DECL|member|init_analysis
id|dasd_init_analysis_fn_t
id|init_analysis
suffix:semicolon
multiline_comment|/* to start the analysis of the volume */
DECL|member|do_analysis
id|dasd_do_analysis_fn_t
id|do_analysis
suffix:semicolon
multiline_comment|/* to complete the analysis of the volume */
DECL|member|fill_geometry
id|dasd_fill_geometry_fn_t
id|fill_geometry
suffix:semicolon
multiline_comment|/* to set up hd_geometry */
DECL|member|start_IO
id|dasd_io_starter_fn_t
id|start_IO
suffix:semicolon
DECL|member|format_device
id|dasd_format_fn_t
id|format_device
suffix:semicolon
multiline_comment|/* to format the device */
DECL|member|examine_error
id|dasd_error_examine_fn_t
id|examine_error
suffix:semicolon
DECL|member|erp_action
id|dasd_error_analyse_fn_t
id|erp_action
suffix:semicolon
DECL|member|erp_postaction
id|dasd_erp_analyse_fn_t
id|erp_postaction
suffix:semicolon
DECL|member|build_cp_from_req
id|dasd_cp_builder_fn_t
id|build_cp_from_req
suffix:semicolon
DECL|member|dump_sense
id|dasd_dump_sense_fn_t
id|dump_sense
suffix:semicolon
DECL|member|int_handler
id|dasd_int_handler_fn_t
id|int_handler
suffix:semicolon
DECL|member|reserve
id|dasd_reserve_fn_t
id|reserve
suffix:semicolon
DECL|member|release
id|dasd_release_fn_t
id|release
suffix:semicolon
DECL|member|merge_cp
id|dasd_merge_cp_fn_t
id|merge_cp
suffix:semicolon
DECL|member|next
r_struct
id|dasd_discipline_t
op_star
id|next
suffix:semicolon
multiline_comment|/* used for list of disciplines */
DECL|typedef|dasd_discipline_t
)brace
id|dasd_discipline_t
suffix:semicolon
DECL|struct|major_info_t
r_typedef
r_struct
id|major_info_t
(brace
DECL|member|next
r_struct
id|major_info_t
op_star
id|next
suffix:semicolon
DECL|member|dasd_device
r_struct
id|dasd_device_t
op_star
op_star
id|dasd_device
suffix:semicolon
DECL|member|gendisk
r_struct
id|gendisk
id|gendisk
suffix:semicolon
multiline_comment|/* actually contains the major number */
DECL|typedef|major_info_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|major_info_t
suffix:semicolon
DECL|struct|dasd_profile_info_t
r_typedef
r_struct
id|dasd_profile_info_t
(brace
DECL|member|dasd_io_reqs
r_int
r_int
id|dasd_io_reqs
suffix:semicolon
multiline_comment|/* number of requests processed at all */
DECL|member|dasd_io_secs
r_int
r_int
id|dasd_io_secs
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of request&squot;s sizes */
DECL|member|dasd_io_times
r_int
r_int
id|dasd_io_times
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of requests&squot;s times */
DECL|member|dasd_io_timps
r_int
r_int
id|dasd_io_timps
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of requests&squot;s times per sector */
DECL|member|dasd_io_time1
r_int
r_int
id|dasd_io_time1
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of time from build to start */
DECL|member|dasd_io_time2
r_int
r_int
id|dasd_io_time2
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of time from start to irq */
DECL|member|dasd_io_time2ps
r_int
r_int
id|dasd_io_time2ps
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of time from start to irq */
DECL|member|dasd_io_time3
r_int
r_int
id|dasd_io_time3
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* histogram of time from irq to end */
DECL|typedef|dasd_profile_info_t
)brace
id|dasd_profile_info_t
suffix:semicolon
DECL|struct|dasd_device_t
r_typedef
r_struct
id|dasd_device_t
(brace
DECL|member|devinfo
id|dev_info_t
id|devinfo
suffix:semicolon
DECL|member|discipline
id|dasd_discipline_t
op_star
id|discipline
suffix:semicolon
DECL|member|level
r_int
id|level
suffix:semicolon
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
DECL|member|kdev
id|kdev_t
id|kdev
suffix:semicolon
DECL|member|major_info
id|major_info_t
op_star
id|major_info
suffix:semicolon
DECL|member|queue
r_struct
id|dasd_chanq_t
id|queue
suffix:semicolon
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
DECL|member|request_queue
id|request_queue_t
id|request_queue
suffix:semicolon
DECL|member|dev_status
id|devstat_t
id|dev_status
suffix:semicolon
multiline_comment|/* needed ONLY!! for request_irq */
DECL|member|sizes
id|dasd_sizes_t
id|sizes
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* The name of the device in /dev */
DECL|member|private
r_char
op_star
r_private
suffix:semicolon
multiline_comment|/* to be used by the discipline internally */
macro_line|#if (LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,3,98))
DECL|member|devfs_entry
id|devfs_handle_t
id|devfs_entry
suffix:semicolon
macro_line|#endif /* LINUX_IS_24 */
DECL|member|bh_tq
r_struct
id|tq_struct
id|bh_tq
suffix:semicolon
DECL|member|bh_scheduled
id|atomic_t
id|bh_scheduled
suffix:semicolon
DECL|member|debug_area
id|debug_info_t
op_star
id|debug_area
suffix:semicolon
DECL|member|profile
id|dasd_profile_info_t
id|profile
suffix:semicolon
DECL|member|proc_dir
r_struct
id|proc_dir_entry
op_star
id|proc_dir
suffix:semicolon
multiline_comment|/* directory node */
DECL|member|proc_info
r_struct
id|proc_dir_entry
op_star
id|proc_info
suffix:semicolon
multiline_comment|/* information from dasd_device_t */
DECL|member|proc_stats
r_struct
id|proc_dir_entry
op_star
id|proc_stats
suffix:semicolon
multiline_comment|/* statictics information */
DECL|typedef|dasd_device_t
)brace
id|dasd_device_t
suffix:semicolon
multiline_comment|/* dasd_device_t.level can be: */
DECL|macro|DASD_DEVICE_LEVEL_UNKNOWN
mdefine_line|#define DASD_DEVICE_LEVEL_UNKNOWN 0x00
DECL|macro|DASD_DEVICE_LEVEL_RECOGNIZED
mdefine_line|#define DASD_DEVICE_LEVEL_RECOGNIZED 0x01
DECL|macro|DASD_DEVICE_LEVEL_ANALYSIS_PENDING
mdefine_line|#define DASD_DEVICE_LEVEL_ANALYSIS_PENDING 0x02
DECL|macro|DASD_DEVICE_LEVEL_ANALYSIS_PREPARED
mdefine_line|#define DASD_DEVICE_LEVEL_ANALYSIS_PREPARED 0x04
DECL|macro|DASD_DEVICE_LEVEL_ANALYSED
mdefine_line|#define DASD_DEVICE_LEVEL_ANALYSED 0x08
DECL|macro|DASD_DEVICE_LEVEL_PARTITIONED
mdefine_line|#define DASD_DEVICE_LEVEL_PARTITIONED 0x10
r_int
id|dasd_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|dasd_discipline_enq
(paren
id|dasd_discipline_t
op_star
)paren
suffix:semicolon
r_int
id|dasd_discipline_deq
c_func
(paren
id|dasd_discipline_t
op_star
)paren
suffix:semicolon
r_int
id|dasd_start_IO
(paren
id|ccw_req_t
op_star
)paren
suffix:semicolon
r_void
id|dasd_int_handler
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
id|ccw_req_t
op_star
id|default_erp_action
(paren
id|ccw_req_t
op_star
)paren
suffix:semicolon
id|ccw_req_t
op_star
id|default_erp_postaction
(paren
id|ccw_req_t
op_star
)paren
suffix:semicolon
r_int
id|dasd_chanq_deq
(paren
id|dasd_chanq_t
op_star
comma
id|ccw_req_t
op_star
)paren
suffix:semicolon
id|ccw_req_t
op_star
id|dasd_alloc_request
(paren
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|dasd_free_request
(paren
id|ccw_req_t
op_star
)paren
suffix:semicolon
DECL|variable|genhd_dasd_name
r_int
(paren
op_star
id|genhd_dasd_name
)paren
(paren
r_char
op_star
comma
r_int
comma
r_int
comma
r_struct
id|gendisk
op_star
)paren
suffix:semicolon
r_int
id|dasd_oper_handler
(paren
r_int
id|irq
comma
id|devreg_t
op_star
id|devreg
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* DASD_H */
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
