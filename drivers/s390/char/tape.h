multiline_comment|/***************************************************************************&n; *&n; *  drivers/s390/char/tape.h&n; *    tape device driver for 3480/3490E/3590 tapes.&n; *&n; *  S390 and zSeries version&n; *    Copyright (C) 2001 IBM Corporation&n; *    Author(s): Carsten Otte &lt;cotte@de.ibm.com&gt;&n; *               Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&n; ****************************************************************************&n; */
macro_line|#ifndef _TAPE_H
DECL|macro|_TAPE_H
mdefine_line|#define _TAPE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mtio.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#ifdef CONFIG_DEVFS_FS
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#endif
macro_line|#include &quot;tape_idalbuf.h&quot;
DECL|macro|TAPE_VERSION_MAJOR
mdefine_line|#define TAPE_VERSION_MAJOR 1
DECL|macro|TAPE_VERSION_MINOR
mdefine_line|#define TAPE_VERSION_MINOR 10
DECL|macro|TAPE_MAGIC
mdefine_line|#define TAPE_MAGIC &quot;tape&quot;
DECL|macro|TAPE_BUSY
mdefine_line|#define TAPE_BUSY(td) (td-&gt;treq != NULL)
DECL|macro|TAPE_MINORS_PER_DEV
mdefine_line|#define TAPE_MINORS_PER_DEV 2       /* two minors per device */
DECL|macro|TAPE_MERGE_RC
mdefine_line|#define TAPE_MERGE_RC(treq,rc) &bslash;&n;&t;if( ((rc) == 0) &amp;&amp; ((treq)-&gt;rc != 0) ) &bslash;&n;&t;&t;rc = (treq)-&gt;rc;
r_typedef
DECL|typedef|tape_wait_t
id|tape_wait_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|MS_UNKNOWN
id|MS_UNKNOWN
comma
DECL|enumerator|MS_LOADED
id|MS_LOADED
comma
DECL|enumerator|MS_UNLOADED
id|MS_UNLOADED
comma
DECL|enumerator|MS_SIZE
id|MS_SIZE
DECL|typedef|tape_medium_state_t
)brace
id|tape_medium_state_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|TS_UNUSED
id|TS_UNUSED
op_assign
l_int|0
comma
DECL|enumerator|TS_IN_USE
id|TS_IN_USE
comma
DECL|enumerator|TS_INIT
id|TS_INIT
comma
DECL|enumerator|TS_NOT_OPER
id|TS_NOT_OPER
comma
DECL|enumerator|TS_SIZE
id|TS_SIZE
DECL|typedef|tape_state_t
)brace
id|tape_state_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|TO_BLOCK
id|TO_BLOCK
comma
DECL|enumerator|TO_BSB
id|TO_BSB
comma
DECL|enumerator|TO_BSF
id|TO_BSF
comma
DECL|enumerator|TO_DSE
id|TO_DSE
comma
DECL|enumerator|TO_EGA
id|TO_EGA
comma
DECL|enumerator|TO_FSB
id|TO_FSB
comma
DECL|enumerator|TO_FSF
id|TO_FSF
comma
DECL|enumerator|TO_LDI
id|TO_LDI
comma
DECL|enumerator|TO_LBL
id|TO_LBL
comma
DECL|enumerator|TO_MSE
id|TO_MSE
comma
DECL|enumerator|TO_NOP
id|TO_NOP
comma
DECL|enumerator|TO_RBA
id|TO_RBA
comma
DECL|enumerator|TO_RBI
id|TO_RBI
comma
DECL|enumerator|TO_RBU
id|TO_RBU
comma
DECL|enumerator|TO_RBL
id|TO_RBL
comma
DECL|enumerator|TO_RDC
id|TO_RDC
comma
DECL|enumerator|TO_RFO
id|TO_RFO
comma
DECL|enumerator|TO_RSD
id|TO_RSD
comma
DECL|enumerator|TO_REW
id|TO_REW
comma
DECL|enumerator|TO_RUN
id|TO_RUN
comma
DECL|enumerator|TO_SEN
id|TO_SEN
comma
DECL|enumerator|TO_SID
id|TO_SID
comma
DECL|enumerator|TO_SNP
id|TO_SNP
comma
DECL|enumerator|TO_SPG
id|TO_SPG
comma
DECL|enumerator|TO_SWI
id|TO_SWI
comma
DECL|enumerator|TO_SMR
id|TO_SMR
comma
DECL|enumerator|TO_SYN
id|TO_SYN
comma
DECL|enumerator|TO_TIO
id|TO_TIO
comma
DECL|enumerator|TO_UNA
id|TO_UNA
comma
DECL|enumerator|TO_WRI
id|TO_WRI
comma
DECL|enumerator|TO_WTM
id|TO_WTM
comma
DECL|enumerator|TO_MSEN
id|TO_MSEN
comma
DECL|enumerator|TO_LOAD
id|TO_LOAD
comma
DECL|enumerator|TO_READ_CONFIG
id|TO_READ_CONFIG
comma
multiline_comment|/* 3590 */
DECL|enumerator|TO_READ_ATTMSG
id|TO_READ_ATTMSG
comma
multiline_comment|/* 3590 */
DECL|enumerator|TO_NOTHING
id|TO_NOTHING
comma
DECL|enumerator|TO_DIS
id|TO_DIS
comma
DECL|enumerator|TO_SIZE
id|TO_SIZE
DECL|typedef|tape_op_t
)brace
id|tape_op_t
suffix:semicolon
DECL|macro|TAPE_INTERRUPTIBLE_OP
mdefine_line|#define TAPE_INTERRUPTIBLE_OP(op) &bslash;&n;&t;(op == MTEOM) || &bslash;&n;&t;(op == MTRETEN)
r_struct
id|_tape_dev_t
suffix:semicolon
singleline_comment|//Forward declaration
multiline_comment|/* The tape device list lock */
r_extern
id|rwlock_t
id|tape_dev_lock
suffix:semicolon
multiline_comment|/* Tape CCW request */
DECL|struct|_tape_ccw_req_t
r_typedef
r_struct
id|_tape_ccw_req_t
(brace
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
DECL|member|cpaddr
id|ccw1_t
op_star
id|cpaddr
suffix:semicolon
DECL|member|cplength
r_int
id|cplength
suffix:semicolon
DECL|member|options
r_int
id|options
suffix:semicolon
DECL|member|kernbuf
r_void
op_star
id|kernbuf
suffix:semicolon
DECL|member|kernbuf_size
r_int
id|kernbuf_size
suffix:semicolon
DECL|member|idal_buf
id|idalbuf_t
op_star
id|idal_buf
suffix:semicolon
DECL|member|userbuf
r_void
op_star
id|userbuf
suffix:semicolon
DECL|member|userbuf_size
r_int
id|userbuf_size
suffix:semicolon
DECL|member|op
id|tape_op_t
id|op
suffix:semicolon
DECL|member|wakeup
r_void
(paren
op_star
id|wakeup
)paren
(paren
r_struct
id|_tape_ccw_req_t
op_star
id|treq
)paren
suffix:semicolon
DECL|member|wait
r_void
(paren
op_star
id|wait
)paren
(paren
r_struct
id|_tape_ccw_req_t
op_star
id|treq
)paren
suffix:semicolon
DECL|member|tape_dev
r_struct
id|_tape_dev_t
op_star
id|tape_dev
suffix:semicolon
singleline_comment|// Pointer for back reference
DECL|member|rc
r_int
id|rc
suffix:semicolon
DECL|member|recover
r_struct
id|_tape_ccw_req_t
op_star
id|recover
suffix:semicolon
DECL|typedef|tape_ccw_req_t
)brace
id|tape_ccw_req_t
suffix:semicolon
multiline_comment|/* Callback typedefs */
DECL|typedef|tape_disc_shutdown_t
r_typedef
r_void
(paren
op_star
id|tape_disc_shutdown_t
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|tape_event_handler_t
r_typedef
r_void
(paren
op_star
id|tape_event_handler_t
)paren
(paren
r_struct
id|_tape_dev_t
op_star
)paren
suffix:semicolon
DECL|typedef|tape_reqgen_ioctl_t
r_typedef
id|tape_ccw_req_t
op_star
(paren
op_star
id|tape_reqgen_ioctl_t
)paren
(paren
r_struct
id|_tape_dev_t
op_star
id|td
comma
r_int
id|op
comma
r_int
id|count
comma
r_int
op_star
id|rc
)paren
suffix:semicolon
DECL|typedef|tape_reqgen_bread_t
r_typedef
id|tape_ccw_req_t
op_star
(paren
op_star
id|tape_reqgen_bread_t
)paren
(paren
r_struct
id|request
op_star
id|req
comma
r_struct
id|_tape_dev_t
op_star
id|td
comma
r_int
id|tapeblock_major
)paren
suffix:semicolon
DECL|typedef|tape_reqgen_enable_loc_t
r_typedef
r_void
(paren
op_star
id|tape_reqgen_enable_loc_t
)paren
(paren
id|tape_ccw_req_t
op_star
)paren
suffix:semicolon
DECL|typedef|tape_free_bread_t
r_typedef
r_void
(paren
op_star
id|tape_free_bread_t
)paren
(paren
id|tape_ccw_req_t
op_star
)paren
suffix:semicolon
DECL|typedef|tape_reqgen_rw_t
r_typedef
id|tape_ccw_req_t
op_star
(paren
op_star
id|tape_reqgen_rw_t
)paren
(paren
r_const
r_char
op_star
id|data
comma
r_int
id|count
comma
r_struct
id|_tape_dev_t
op_star
id|td
)paren
suffix:semicolon
DECL|typedef|tape_setup_device_t
r_typedef
r_int
(paren
op_star
id|tape_setup_device_t
)paren
(paren
r_struct
id|_tape_dev_t
op_star
)paren
suffix:semicolon
DECL|typedef|tape_cleanup_device_t
r_typedef
r_void
(paren
op_star
id|tape_cleanup_device_t
)paren
(paren
r_struct
id|_tape_dev_t
op_star
)paren
suffix:semicolon
DECL|typedef|tape_disc_ioctl_overl_t
r_typedef
r_int
(paren
op_star
id|tape_disc_ioctl_overl_t
)paren
(paren
r_struct
id|_tape_dev_t
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
DECL|typedef|tape_devfs_constructor_t
r_typedef
id|devfs_handle_t
(paren
op_star
id|tape_devfs_constructor_t
)paren
(paren
r_struct
id|_tape_dev_t
op_star
)paren
suffix:semicolon
DECL|typedef|tape_devfs_destructor_t
r_typedef
r_void
(paren
op_star
id|tape_devfs_destructor_t
)paren
(paren
r_struct
id|_tape_dev_t
op_star
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Tape Discipline */
DECL|struct|_tape_discipline_t
r_typedef
r_struct
id|_tape_discipline_t
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|cu_type
r_int
r_int
id|cu_type
suffix:semicolon
DECL|member|setup_device
id|tape_setup_device_t
id|setup_device
suffix:semicolon
DECL|member|cleanup_device
id|tape_cleanup_device_t
id|cleanup_device
suffix:semicolon
DECL|member|init_device
id|tape_event_handler_t
id|init_device
suffix:semicolon
DECL|member|process_eov
id|tape_event_handler_t
id|process_eov
suffix:semicolon
DECL|member|irq
id|tape_event_handler_t
id|irq
suffix:semicolon
DECL|member|bread
id|tape_reqgen_bread_t
id|bread
suffix:semicolon
DECL|member|free_bread
id|tape_free_bread_t
id|free_bread
suffix:semicolon
DECL|member|bread_enable_locate
id|tape_reqgen_enable_loc_t
id|bread_enable_locate
suffix:semicolon
DECL|member|write_block
id|tape_reqgen_rw_t
id|write_block
suffix:semicolon
DECL|member|read_block
id|tape_reqgen_rw_t
id|read_block
suffix:semicolon
DECL|member|ioctl
id|tape_reqgen_ioctl_t
id|ioctl
suffix:semicolon
DECL|member|shutdown
id|tape_disc_shutdown_t
id|shutdown
suffix:semicolon
DECL|member|discipline_ioctl_overload
id|tape_disc_ioctl_overl_t
id|discipline_ioctl_overload
suffix:semicolon
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
DECL|typedef|tape_discipline_t
)brace
id|tape_discipline_t
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Frontend */
DECL|struct|_tape_frontend_t
r_typedef
r_struct
id|_tape_frontend_t
(brace
DECL|member|device_setup
id|tape_setup_device_t
id|device_setup
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
DECL|member|mkdevfstree
id|tape_devfs_constructor_t
id|mkdevfstree
suffix:semicolon
DECL|member|rmdevfstree
id|tape_devfs_destructor_t
id|rmdevfstree
suffix:semicolon
macro_line|#endif
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
DECL|typedef|tape_frontend_t
)brace
id|tape_frontend_t
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Char Frontend Data */
DECL|struct|_tape_char_front_data_t
r_typedef
r_struct
id|_tape_char_front_data_t
(brace
DECL|member|block_size
r_int
id|block_size
suffix:semicolon
multiline_comment|/* block size of tape */
DECL|typedef|tape_char_data_t
)brace
id|tape_char_data_t
suffix:semicolon
multiline_comment|/* Block Frontend Data */
DECL|struct|_tape_blk_front_data_t
r_typedef
r_struct
id|_tape_blk_front_data_t
(brace
DECL|member|request_queue
id|request_queue_t
id|request_queue
suffix:semicolon
DECL|member|current_request
r_struct
id|request
op_star
id|current_request
suffix:semicolon
DECL|member|blk_retries
r_int
id|blk_retries
suffix:semicolon
DECL|member|position
r_int
id|position
suffix:semicolon
DECL|member|bh_scheduled
id|atomic_t
id|bh_scheduled
suffix:semicolon
DECL|member|bh_tq
r_struct
id|tq_struct
id|bh_tq
suffix:semicolon
DECL|typedef|tape_blk_data_t
)brace
id|tape_blk_data_t
suffix:semicolon
multiline_comment|/* Tape Info */
DECL|struct|_tape_dev_t
r_typedef
r_struct
id|_tape_dev_t
(brace
DECL|member|use_count
id|atomic_t
id|use_count
suffix:semicolon
multiline_comment|/* Reference count, when == 0 delete */
DECL|member|first_minor
r_int
id|first_minor
suffix:semicolon
multiline_comment|/* each tape device has two minors */
DECL|member|devinfo
id|s390_dev_info_t
id|devinfo
suffix:semicolon
multiline_comment|/* device info from Common I/O */
DECL|member|devstat
id|devstat_t
id|devstat
suffix:semicolon
multiline_comment|/* contains irq, devno, status */
DECL|member|filp
r_struct
id|file
op_star
id|filp
suffix:semicolon
multiline_comment|/* backpointer to file structure */
DECL|member|tape_state
r_int
id|tape_state
suffix:semicolon
multiline_comment|/* State of the device. See tape_stat */
DECL|member|medium_state
r_int
id|medium_state
suffix:semicolon
multiline_comment|/* loaded, unloaded, unkown etc. */
DECL|member|discipline
id|tape_discipline_t
op_star
id|discipline
suffix:semicolon
multiline_comment|/* The used discipline */
DECL|member|discdata
r_void
op_star
id|discdata
suffix:semicolon
multiline_comment|/* discipline specific data */
DECL|member|treq
id|tape_ccw_req_t
op_star
id|treq
suffix:semicolon
multiline_comment|/* Active Tape request */
DECL|member|last_op
id|tape_op_t
id|last_op
suffix:semicolon
multiline_comment|/* Last Tape operation */
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
multiline_comment|/* ptr to next tape_dev */
DECL|member|char_data
id|tape_char_data_t
id|char_data
suffix:semicolon
multiline_comment|/* Character dev frontend data */
DECL|member|blk_data
id|tape_blk_data_t
id|blk_data
suffix:semicolon
multiline_comment|/* Block dev frontend data */
DECL|typedef|tape_dev_t
)brace
id|tape_dev_t
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* tape functions */
DECL|macro|TAPE_MEMB_IRQ
mdefine_line|#define TAPE_MEMB_IRQ       0
DECL|macro|TAPE_MEMB_MINOR
mdefine_line|#define TAPE_MEMB_MINOR     1
DECL|macro|TAPE_MEMB_QUEUE
mdefine_line|#define TAPE_MEMB_QUEUE     2
id|tape_dev_t
op_star
id|__tape_get_device_by_member
c_func
(paren
r_int
r_int
id|value
comma
r_int
id|member
)paren
suffix:semicolon
multiline_comment|/*&n; * Search for tape structure with specific minor number&n; */
r_static
r_inline
id|tape_dev_t
op_star
DECL|function|tape_get_device_by_minor
id|tape_get_device_by_minor
c_func
(paren
r_int
id|minor
)paren
(brace
r_return
id|__tape_get_device_by_member
c_func
(paren
id|minor
comma
id|TAPE_MEMB_MINOR
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Search for tape structure with specific IRQ&n; */
r_static
r_inline
id|tape_dev_t
op_star
DECL|function|tape_get_device_by_irq
id|tape_get_device_by_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|__tape_get_device_by_member
c_func
(paren
id|irq
comma
id|TAPE_MEMB_IRQ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Search for tape structure with specific queue&n; */
r_static
r_inline
id|tape_dev_t
op_star
DECL|function|tape_get_device_by_queue
id|tape_get_device_by_queue
c_func
(paren
r_void
op_star
id|queue
)paren
(brace
r_return
id|__tape_get_device_by_member
c_func
(paren
(paren
r_int
r_int
)paren
id|queue
comma
id|TAPE_MEMB_QUEUE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Increment use count of tape structure&n; */
r_static
r_inline
r_void
DECL|function|tape_get_device
id|tape_get_device
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
(brace
r_if
c_cond
(paren
id|td
op_ne
l_int|NULL
)paren
id|atomic_inc
c_func
(paren
op_amp
(paren
id|td-&gt;use_count
)paren
)paren
suffix:semicolon
)brace
r_void
id|tape_put_device
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
multiline_comment|/* Discipline functions */
r_int
id|tape_register_discipline
c_func
(paren
id|tape_discipline_t
op_star
id|disc
)paren
suffix:semicolon
r_void
id|tape_unregister_discipline
c_func
(paren
id|tape_discipline_t
op_star
id|disc
)paren
suffix:semicolon
multiline_comment|/* tape initialisation functions */
r_int
id|tape_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* a function for dumping device sense info */
r_void
id|tape_dump_sense
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_void
id|tape_dump_sense_dbf
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
multiline_comment|/* functions for handling the status of a device */
r_inline
r_void
id|tape_state_set
(paren
id|tape_dev_t
op_star
id|td
comma
id|tape_state_t
id|newstate
)paren
suffix:semicolon
r_inline
id|tape_state_t
id|tape_state_get
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
r_inline
r_void
id|tape_med_state_set
c_func
(paren
id|tape_dev_t
op_star
id|td
comma
id|tape_medium_state_t
id|newstate
)paren
suffix:semicolon
multiline_comment|/* functions for alloc&squot;ing ccw and IO stuff */
r_inline
id|tape_ccw_req_t
op_star
id|tape_alloc_ccw_req
c_func
(paren
r_int
id|cplength
comma
r_int
id|datasize
comma
r_int
id|idal_buf_size
comma
id|tape_op_t
id|op
)paren
suffix:semicolon
r_void
id|tape_free_ccw_req
(paren
id|tape_ccw_req_t
op_star
id|request
)paren
suffix:semicolon
r_int
id|tape_do_io
c_func
(paren
id|tape_dev_t
op_star
id|td
comma
id|tape_ccw_req_t
op_star
id|treq
comma
id|tape_wait_t
id|type
)paren
suffix:semicolon
r_int
id|tape_do_io_irq
c_func
(paren
id|tape_dev_t
op_star
id|td
comma
id|tape_ccw_req_t
op_star
id|treq
comma
id|tape_wait_t
id|type
)paren
suffix:semicolon
r_int
id|tape_do_io_and_wait
c_func
(paren
id|tape_dev_t
op_star
id|td
comma
id|tape_ccw_req_t
op_star
id|treq
comma
id|tape_wait_t
id|type
)paren
suffix:semicolon
r_int
id|tape_do_wait_req
c_func
(paren
id|tape_dev_t
op_star
id|td
comma
id|tape_ccw_req_t
op_star
id|treq
comma
id|tape_wait_t
id|type
)paren
suffix:semicolon
r_int
id|tape_remove_ccw_req
c_func
(paren
id|tape_dev_t
op_star
id|td
comma
id|tape_ccw_req_t
op_star
id|treq
)paren
suffix:semicolon
id|tape_ccw_req_t
op_star
id|tape_get_active_ccw_req
c_func
(paren
id|tape_dev_t
op_star
id|td
)paren
suffix:semicolon
multiline_comment|/* The debug area */
macro_line|#ifdef TAPE_DEBUG
r_extern
id|debug_info_t
op_star
id|tape_dbf_area
suffix:semicolon
DECL|macro|tape_sprintf_event
mdefine_line|#define tape_sprintf_event debug_sprintf_event
DECL|macro|tape_sprintf_exception
mdefine_line|#define tape_sprintf_exception debug_sprintf_exception
macro_line|#else
DECL|macro|tape_sprintf_event
mdefine_line|#define tape_sprintf_event
DECL|macro|tape_sprintf_exception
mdefine_line|#define tape_sprintf_exception
macro_line|#endif
multiline_comment|/* functions for building ccws */
r_static
r_inline
id|ccw1_t
op_star
DECL|function|__ccwprep
id|__ccwprep
c_func
(paren
id|ccw1_t
op_star
id|ccw
comma
id|__u8
id|cmd_code
comma
id|__u8
id|flags
comma
id|__u16
id|memsize
comma
r_void
op_star
id|cda
comma
r_int
id|ccw_count
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_S390X
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|cda
op_ge
(paren
l_int|1UL
op_lshift
l_int|31
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cda: %p&bslash;n&quot;
comma
id|cda
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ARCH_S390X */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ccw_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ccw
(braket
id|i
)braket
dot
id|cmd_code
op_assign
id|cmd_code
suffix:semicolon
id|ccw
(braket
id|i
)braket
dot
id|flags
op_or_assign
id|CCW_FLAG_CC
suffix:semicolon
id|ccw
(braket
id|i
)braket
dot
id|count
op_assign
id|memsize
suffix:semicolon
r_if
c_cond
(paren
id|cda
op_eq
l_int|0
)paren
(brace
id|ccw
(braket
id|i
)braket
dot
id|cda
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
id|ccw
(braket
id|i
)braket
dot
id|cmd_code
)paren
suffix:semicolon
)brace
r_else
id|ccw
(braket
id|i
)braket
dot
id|cda
op_assign
(paren
r_int
r_int
)paren
id|cda
suffix:semicolon
)brace
id|ccw
(braket
id|ccw_count
op_minus
l_int|1
)braket
dot
id|flags
op_assign
id|flags
suffix:semicolon
r_return
op_amp
id|ccw
(braket
id|ccw_count
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_inline
id|ccw1_t
op_star
DECL|function|tape_ccw_cc
id|tape_ccw_cc
c_func
(paren
id|ccw1_t
op_star
id|ccw
comma
id|__u8
id|cmd_code
comma
id|__u16
id|memsize
comma
r_void
op_star
id|cda
comma
r_int
id|ccw_count
)paren
(brace
r_return
id|__ccwprep
c_func
(paren
id|ccw
comma
id|cmd_code
comma
id|CCW_FLAG_CC
comma
id|memsize
comma
id|cda
comma
id|ccw_count
)paren
suffix:semicolon
)brace
r_extern
r_inline
id|ccw1_t
op_star
DECL|function|tape_ccw_end
id|tape_ccw_end
c_func
(paren
id|ccw1_t
op_star
id|ccw
comma
id|__u8
id|cmd_code
comma
id|__u16
id|memsize
comma
r_void
op_star
id|cda
comma
r_int
id|ccw_count
)paren
(brace
r_return
id|__ccwprep
c_func
(paren
id|ccw
comma
id|cmd_code
comma
l_int|0
comma
id|memsize
comma
id|cda
comma
id|ccw_count
)paren
suffix:semicolon
)brace
r_extern
r_inline
id|ccw1_t
op_star
DECL|function|tape_ccw_cc_idal
id|tape_ccw_cc_idal
c_func
(paren
id|ccw1_t
op_star
id|ccw
comma
id|__u8
id|cmd_code
comma
id|idalbuf_t
op_star
id|idal
)paren
(brace
id|ccw-&gt;cmd_code
op_assign
id|cmd_code
suffix:semicolon
id|ccw-&gt;flags
op_assign
id|CCW_FLAG_CC
suffix:semicolon
id|idalbuf_set_normalized_cda
c_func
(paren
id|ccw
comma
id|idal
)paren
suffix:semicolon
r_return
id|ccw
op_increment
suffix:semicolon
)brace
r_extern
r_inline
id|ccw1_t
op_star
DECL|function|tape_ccw_end_idal
id|tape_ccw_end_idal
c_func
(paren
id|ccw1_t
op_star
id|ccw
comma
id|__u8
id|cmd_code
comma
id|idalbuf_t
op_star
id|idal
)paren
(brace
id|ccw-&gt;cmd_code
op_assign
id|cmd_code
suffix:semicolon
id|ccw-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|idalbuf_set_normalized_cda
c_func
(paren
id|ccw
comma
id|idal
)paren
suffix:semicolon
r_return
id|ccw
op_increment
suffix:semicolon
)brace
multiline_comment|/* Global vars */
r_extern
r_const
r_char
op_star
id|tape_state_verbose
(braket
id|TS_SIZE
)braket
suffix:semicolon
r_extern
r_const
r_char
op_star
id|tape_op_verbose
(braket
id|TO_SIZE
)braket
suffix:semicolon
multiline_comment|/* Some linked lists for storing plugins and devices */
r_extern
id|tape_dev_t
op_star
id|tape_first_dev
suffix:semicolon
r_extern
id|tape_frontend_t
op_star
id|tape_first_front
suffix:semicolon
macro_line|#endif /* for ifdef tape.h */
eof
