macro_line|#ifndef _BLK_H
DECL|macro|_BLK_H
mdefine_line|#define _BLK_H
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/elevator.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
r_extern
r_void
id|set_device_ro
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_void
id|add_blkdev_randomness
c_func
(paren
r_int
id|major
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|macro|INITRD_MINOR
mdefine_line|#define INITRD_MINOR 250 /* shouldn&squot;t collide with /dev/ram* too soon ... */
r_extern
r_int
r_int
id|initrd_start
comma
id|initrd_end
suffix:semicolon
r_extern
r_int
id|initrd_below_start_ok
suffix:semicolon
multiline_comment|/* 1 if it is not an error if initrd_start &lt; memory_start */
r_extern
r_int
id|rd_doload
suffix:semicolon
multiline_comment|/* 1 = load ramdisk, 0 = don&squot;t load */
r_extern
r_int
id|rd_prompt
suffix:semicolon
multiline_comment|/* 1 = prompt for ramdisk, 0 = don&squot;t prompt */
r_extern
r_int
id|rd_image_start
suffix:semicolon
multiline_comment|/* starting block # of image */
r_void
id|initrd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * end_request() and friends. Must be called with the request queue spinlock&n; * acquired. All functions called within end_request() _must_be_ atomic.&n; *&n; * Several drivers define their own end_request and call&n; * end_that_request_first() and end_that_request_last()&n; * for parts of the original function. This prevents&n; * code duplication in drivers.&n; */
r_extern
r_int
id|end_that_request_first
c_func
(paren
r_struct
id|request
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|end_that_request_last
c_func
(paren
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|function|blkdev_dequeue_request
r_static
r_inline
r_void
id|blkdev_dequeue_request
c_func
(paren
r_struct
id|request
op_star
id|req
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|req-&gt;queuelist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;q
)paren
id|elv_remove_request
c_func
(paren
id|req-&gt;q
comma
id|req
)paren
suffix:semicolon
)brace
DECL|function|elv_next_request
r_extern
r_inline
r_struct
id|request
op_star
id|elv_next_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_while
c_loop
(paren
(paren
id|rq
op_assign
id|__elv_next_request
c_func
(paren
id|q
)paren
)paren
)paren
(brace
id|rq-&gt;flags
op_or_assign
id|REQ_STARTED
suffix:semicolon
r_if
c_cond
(paren
op_amp
id|rq-&gt;queuelist
op_eq
id|q-&gt;last_merge
)paren
id|q-&gt;last_merge
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rq-&gt;flags
op_amp
id|REQ_DONTPREP
)paren
op_logical_or
op_logical_neg
id|q-&gt;prep_rq_fn
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * all ok, break and return it&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|q
op_member_access_from_pointer
id|prep_rq_fn
c_func
(paren
id|q
comma
id|rq
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * prep said no-go, kill it&n;&t;&t; */
id|blkdev_dequeue_request
c_func
(paren
id|rq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end_that_request_first
c_func
(paren
id|rq
comma
l_int|0
comma
id|rq-&gt;nr_sectors
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|end_that_request_last
c_func
(paren
id|rq
)paren
suffix:semicolon
)brace
r_return
id|rq
suffix:semicolon
)brace
DECL|macro|_elv_add_request_core
mdefine_line|#define _elv_add_request_core(q, rq, where, plug)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((plug))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;blk_plug_device((q));&t;&t;&t;&t;&bslash;&n;&t;&t;(q)-&gt;elevator.elevator_add_req_fn((q), (rq), (where));&t;&bslash;&n;&t;} while (0)
DECL|macro|_elv_add_request
mdefine_line|#define _elv_add_request(q, rq, back, p) do {&t;&t;&t;&t;      &bslash;&n;&t;if ((back))&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;_elv_add_request_core((q), (rq), (q)-&gt;queue_head.prev, (p));  &bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;&t;_elv_add_request_core((q), (rq), &amp;(q)-&gt;queue_head, (p));      &bslash;&n;} while (0)
DECL|macro|elv_add_request
mdefine_line|#define elv_add_request(q, rq, back) _elv_add_request((q), (rq), (back), 1)
macro_line|#if defined(MAJOR_NR) || defined(IDE_DRIVER)
DECL|macro|DEVICE_ON
macro_line|#undef DEVICE_ON
DECL|macro|DEVICE_OFF
macro_line|#undef DEVICE_OFF
multiline_comment|/*&n; * Add entries as needed.&n; */
macro_line|#ifdef IDE_DRIVER
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device)&t;(minor(device) &gt;&gt; PARTN_BITS)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;ide&quot;
macro_line|#elif (MAJOR_NR == RAMDISK_MAJOR)
multiline_comment|/* ram disk */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;ramdisk&quot;
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
DECL|macro|DEVICE_NO_RANDOM
mdefine_line|#define DEVICE_NO_RANDOM
macro_line|#elif (MAJOR_NR == Z2RAM_MAJOR)
multiline_comment|/* Zorro II Ram */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Z2RAM&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_z2_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == FLOPPY_MAJOR)
r_static
r_void
id|floppy_off
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;floppy&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_floppy
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_fd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) ( (minor(device) &amp; 3) | ((minor(device) &amp; 0x80 ) &gt;&gt; 5 ))
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device) floppy_off(DEVICE_NR(device))
macro_line|#elif (MAJOR_NR == HD_MAJOR)
multiline_comment|/* Hard disk:  timeout is 6 seconds. */
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;hard disk&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_hd
DECL|macro|TIMEOUT_VALUE
mdefine_line|#define TIMEOUT_VALUE (6*HZ)
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_hd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device)&gt;&gt;6)
macro_line|#elif (SCSI_DISK_MAJOR(MAJOR_NR))
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;scsidisk&quot;
DECL|macro|TIMEOUT_VALUE
mdefine_line|#define TIMEOUT_VALUE (2*HZ)
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (((major(device) &amp; SD_MAJOR_MASK) &lt;&lt; (8 - 4)) + (minor(device) &gt;&gt; 4))
multiline_comment|/* Kludge to use the same number for both char and block major numbers */
macro_line|#elif  (MAJOR_NR == MD_MAJOR) &amp;&amp; defined(MD_DRIVER)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Multiple devices driver&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_md_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == SCSI_TAPE_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;scsitape&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_st  
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device) &amp; 0x7f)
macro_line|#elif (MAJOR_NR == OSST_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;onstream&quot; 
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_osst
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device) &amp; 0x7f) 
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device) 
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device) 
macro_line|#elif (MAJOR_NR == SCSI_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;CD-ROM&quot;
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == XT_DISK_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;xt disk&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_xd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device) &gt;&gt; 6)
macro_line|#elif (MAJOR_NR == PS2ESDI_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;PS/2 ESDI&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_ps2esdi_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device) &gt;&gt; 6)
macro_line|#elif (MAJOR_NR == CDU31A_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;CDU31A&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_cdu31a_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == ACSI_MAJOR) &amp;&amp; (defined(CONFIG_ATARI_ACSI) || defined(CONFIG_ATARI_ACSI_MODULE))
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;ACSI&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_acsi
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_acsi_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device) &gt;&gt; 4)
macro_line|#elif (MAJOR_NR == MITSUMI_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Mitsumi CD-ROM&quot;
multiline_comment|/* #define DEVICE_INTR do_mcd */
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_mcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == MITSUMI_X_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Mitsumi CD-ROM&quot;
multiline_comment|/* #define DEVICE_INTR do_mcdx */
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_mcdx_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == MATSUSHITA_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Matsushita CD-ROM controller #1&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sbpcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == MATSUSHITA_CDROM2_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Matsushita CD-ROM controller #2&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sbpcd2_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == MATSUSHITA_CDROM3_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Matsushita CD-ROM controller #3&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sbpcd3_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == MATSUSHITA_CDROM4_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Matsushita CD-ROM controller #4&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sbpcd4_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == AZTECH_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Aztech CD-ROM&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_aztcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == CDU535_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;SONY-CDU535&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_cdu535
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_cdu535_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == GOLDSTAR_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Goldstar R420&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_gscd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == CM206_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Philips/LMS CD-ROM cm206&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_cm206_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == OPTICS_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;DOLPHIN 8000AT CD-ROM&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_optcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == SANYO_CDROM_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;Sanyo H94A CD-ROM&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_sjcd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == APBLOCK_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;apblock&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST ap_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == DDV_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;ddv&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST ddv_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device)&gt;&gt;PARTN_BITS)
macro_line|#elif (MAJOR_NR == MFM_ACORN_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;mfm disk&quot;
DECL|macro|DEVICE_INTR
mdefine_line|#define DEVICE_INTR do_mfm
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_mfm_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device) &gt;&gt; 6)
macro_line|#elif (MAJOR_NR == NBD_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;nbd&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_nbd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == MDISK_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;mdisk&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST mdisk_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device))
macro_line|#elif (MAJOR_NR == DASD_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;dasd&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_dasd_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device) &gt;&gt; PARTN_BITS)
macro_line|#elif (MAJOR_NR == I2O_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;I2O block&quot;
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST i2ob_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device)&gt;&gt;4)
macro_line|#elif (MAJOR_NR == COMPAQ_SMART2_MAJOR)
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;ida&quot;
DECL|macro|TIMEOUT_VALUE
mdefine_line|#define TIMEOUT_VALUE (25*HZ)
DECL|macro|DEVICE_REQUEST
mdefine_line|#define DEVICE_REQUEST do_ida_request
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(device) (minor(device) &gt;&gt; 4)
macro_line|#endif /* MAJOR_NR == whatever */
multiline_comment|/* provide DEVICE_xxx defaults, if not explicitly defined&n; * above in the MAJOR_NR==xxx if-elif tree */
macro_line|#ifndef DEVICE_ON
DECL|macro|DEVICE_ON
mdefine_line|#define DEVICE_ON(device) do {} while (0)
macro_line|#endif
macro_line|#ifndef DEVICE_OFF
DECL|macro|DEVICE_OFF
mdefine_line|#define DEVICE_OFF(device) do {} while (0)
macro_line|#endif
macro_line|#if (MAJOR_NR != SCSI_TAPE_MAJOR) &amp;&amp; (MAJOR_NR != OSST_MAJOR)
macro_line|#if !defined(IDE_DRIVER)
macro_line|#ifndef CURRENT
DECL|macro|CURRENT
mdefine_line|#define CURRENT elv_next_request(&amp;blk_dev[MAJOR_NR].request_queue)
macro_line|#endif
macro_line|#ifndef QUEUE
DECL|macro|QUEUE
mdefine_line|#define QUEUE (&amp;blk_dev[MAJOR_NR].request_queue)
macro_line|#endif
macro_line|#ifndef QUEUE_EMPTY
DECL|macro|QUEUE_EMPTY
mdefine_line|#define QUEUE_EMPTY blk_queue_empty(QUEUE)
macro_line|#endif
macro_line|#ifndef DEVICE_NAME
DECL|macro|DEVICE_NAME
mdefine_line|#define DEVICE_NAME &quot;unknown&quot;
macro_line|#endif
DECL|macro|CURRENT_DEV
mdefine_line|#define CURRENT_DEV DEVICE_NR(CURRENT-&gt;rq_dev)
macro_line|#ifdef DEVICE_INTR
DECL|variable|DEVICE_INTR
r_static
r_void
(paren
op_star
id|DEVICE_INTR
)paren
(paren
r_void
)paren
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
DECL|macro|SET_INTR
mdefine_line|#define SET_INTR(x) (DEVICE_INTR = (x))
macro_line|#ifdef DEVICE_REQUEST
r_static
r_void
(paren
id|DEVICE_REQUEST
)paren
(paren
id|request_queue_t
op_star
)paren
suffix:semicolon
macro_line|#endif 
macro_line|#ifdef DEVICE_INTR
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR SET_INTR(NULL)
macro_line|#else
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR
macro_line|#endif
DECL|macro|INIT_REQUEST
mdefine_line|#define INIT_REQUEST&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (QUEUE_EMPTY) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;CLEAR_INTR;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (major(CURRENT-&gt;rq_dev) != MAJOR_NR) &t;&t;&t;&bslash;&n;&t;&t;panic(DEVICE_NAME &quot;: request list destroyed&quot;);&t;&bslash;&n;&t;if (!CURRENT-&gt;bio)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;panic(DEVICE_NAME &quot;: no bio&quot;);&t;&t;&t;&bslash;&n;
macro_line|#endif /* !defined(IDE_DRIVER) */
macro_line|#ifndef LOCAL_END_REQUEST&t;/* If we have our own end_request, we do not want to include this mess */
macro_line|#if ! SCSI_BLK_MAJOR(MAJOR_NR) &amp;&amp; (MAJOR_NR != COMPAQ_SMART2_MAJOR)
DECL|function|end_request
r_static
r_inline
r_void
id|end_request
c_func
(paren
r_int
id|uptodate
)paren
(brace
r_struct
id|request
op_star
id|req
op_assign
id|CURRENT
suffix:semicolon
r_if
c_cond
(paren
id|end_that_request_first
c_func
(paren
id|req
comma
id|uptodate
comma
id|CURRENT-&gt;hard_cur_sectors
)paren
)paren
r_return
suffix:semicolon
macro_line|#ifndef DEVICE_NO_RANDOM
id|add_blkdev_randomness
c_func
(paren
id|major
c_func
(paren
id|req-&gt;rq_dev
)paren
)paren
suffix:semicolon
macro_line|#endif
id|DEVICE_OFF
c_func
(paren
id|req-&gt;rq_dev
)paren
suffix:semicolon
id|blkdev_dequeue_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|end_that_request_last
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
macro_line|#endif /* ! SCSI_BLK_MAJOR(MAJOR_NR) */
macro_line|#endif /* LOCAL_END_REQUEST */
macro_line|#endif /* (MAJOR_NR != SCSI_TAPE_MAJOR) */
macro_line|#endif /* defined(MAJOR_NR) || defined(IDE_DRIVER) */
macro_line|#endif /* _BLK_H */
eof
