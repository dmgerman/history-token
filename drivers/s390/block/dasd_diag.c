multiline_comment|/* &n; * File...........: linux/drivers/s390/block/dasd_diag.c&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Based on.......: linux/drivers/s390/block/mdisk.c&n; * ...............: by Hartmunt Penner &lt;hpenner@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999,2000&n; *&n; * $Revision: 1.33 $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;&t;/* HDIO_GETGEO&t;&t;&t;    */
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/dasd.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/s390_ext.h&gt;
macro_line|#include &lt;asm/todclk.h&gt;
macro_line|#include &quot;dasd_int.h&quot;
macro_line|#include &quot;dasd_diag.h&quot;
macro_line|#ifdef PRINTK_HEADER
DECL|macro|PRINTK_HEADER
macro_line|#undef PRINTK_HEADER
macro_line|#endif&t;&t;&t;&t;/* PRINTK_HEADER */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;dasd(diag):&quot;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|struct|dasd_diag_private
r_struct
id|dasd_diag_private
(brace
DECL|member|rdc_data
r_struct
id|dasd_diag_characteristics
id|rdc_data
suffix:semicolon
DECL|member|iob
r_struct
id|dasd_diag_rw_io
id|iob
suffix:semicolon
DECL|member|iib
r_struct
id|dasd_diag_init_io
id|iib
suffix:semicolon
DECL|member|pt_block
r_int
r_int
id|pt_block
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dasd_diag_req
r_struct
id|dasd_diag_req
(brace
DECL|member|block_count
r_int
id|block_count
suffix:semicolon
DECL|member|bio
r_struct
id|dasd_diag_bio
id|bio
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
r_static
id|__inline__
r_int
DECL|function|dia250
id|dia250
c_func
(paren
r_void
op_star
id|iob
comma
r_int
id|cmd
)paren
(brace
r_int
id|rc
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;    lhi   %0,3&bslash;n&quot;
l_string|&quot;&t;  lr&t;0,%2&bslash;n&quot;
l_string|&quot;&t;  diag&t;0,%1,0x250&bslash;n&quot;
l_string|&quot;0:  ipm&t;%0&bslash;n&quot;
l_string|&quot;&t;  srl&t;%0,28&bslash;n&quot;
l_string|&quot;&t;  or&t;%0,1&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
macro_line|#ifndef CONFIG_ARCH_S390X
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;  .align 4&bslash;n&quot;
l_string|&quot;&t;  .long 0b,1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
macro_line|#else
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;  .align 8&bslash;n&quot;
l_string|&quot;&t;  .quad  0b,1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
macro_line|#endif
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|rc
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|cmd
)paren
comma
l_string|&quot;d&quot;
(paren
(paren
r_void
op_star
)paren
id|__pa
c_func
(paren
id|iob
)paren
)paren
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|mdsk_init_io
id|mdsk_init_io
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
comma
r_int
id|blocksize
comma
r_int
id|offset
comma
r_int
id|size
)paren
(brace
r_struct
id|dasd_diag_private
op_star
r_private
suffix:semicolon
r_struct
id|dasd_diag_init_io
op_star
id|iib
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_private
op_assign
(paren
r_struct
id|dasd_diag_private
op_star
)paren
id|device
op_member_access_from_pointer
r_private
suffix:semicolon
id|iib
op_assign
op_amp
r_private
op_member_access_from_pointer
id|iib
suffix:semicolon
id|memset
c_func
(paren
id|iib
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dasd_diag_init_io
)paren
)paren
suffix:semicolon
id|iib-&gt;dev_nr
op_assign
id|_ccw_device_get_device_number
c_func
(paren
id|device-&gt;cdev
)paren
suffix:semicolon
id|iib-&gt;block_size
op_assign
id|blocksize
suffix:semicolon
id|iib-&gt;offset
op_assign
id|offset
suffix:semicolon
id|iib-&gt;start_block
op_assign
l_int|0
suffix:semicolon
id|iib-&gt;end_block
op_assign
id|size
suffix:semicolon
id|rc
op_assign
id|dia250
c_func
(paren
id|iib
comma
id|INIT_BIO
)paren
suffix:semicolon
r_return
id|rc
op_amp
l_int|3
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|mdsk_term_io
id|mdsk_term_io
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
)paren
(brace
r_struct
id|dasd_diag_private
op_star
r_private
suffix:semicolon
r_struct
id|dasd_diag_init_io
op_star
id|iib
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_private
op_assign
(paren
r_struct
id|dasd_diag_private
op_star
)paren
id|device
op_member_access_from_pointer
r_private
suffix:semicolon
id|iib
op_assign
op_amp
r_private
op_member_access_from_pointer
id|iib
suffix:semicolon
id|memset
c_func
(paren
id|iib
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dasd_diag_init_io
)paren
)paren
suffix:semicolon
id|iib-&gt;dev_nr
op_assign
id|_ccw_device_get_device_number
c_func
(paren
id|device-&gt;cdev
)paren
suffix:semicolon
id|rc
op_assign
id|dia250
c_func
(paren
id|iib
comma
id|TERM_BIO
)paren
suffix:semicolon
r_return
id|rc
op_amp
l_int|3
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_start_diag
id|dasd_start_diag
c_func
(paren
r_struct
id|dasd_ccw_req
op_star
id|cqr
)paren
(brace
r_struct
id|dasd_device
op_star
id|device
suffix:semicolon
r_struct
id|dasd_diag_private
op_star
r_private
suffix:semicolon
r_struct
id|dasd_diag_req
op_star
id|dreq
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|device
op_assign
id|cqr-&gt;device
suffix:semicolon
r_private
op_assign
(paren
r_struct
id|dasd_diag_private
op_star
)paren
id|device
op_member_access_from_pointer
r_private
suffix:semicolon
id|dreq
op_assign
(paren
r_struct
id|dasd_diag_req
op_star
)paren
id|cqr-&gt;data
suffix:semicolon
r_private
op_member_access_from_pointer
id|iob.dev_nr
op_assign
id|_ccw_device_get_device_number
c_func
(paren
id|device-&gt;cdev
)paren
suffix:semicolon
r_private
op_member_access_from_pointer
id|iob.key
op_assign
l_int|0
suffix:semicolon
r_private
op_member_access_from_pointer
id|iob.flags
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* do asynchronous io */
r_private
op_member_access_from_pointer
id|iob.block_count
op_assign
id|dreq-&gt;block_count
suffix:semicolon
r_private
op_member_access_from_pointer
id|iob.interrupt_params
op_assign
(paren
id|u32
)paren
(paren
id|addr_t
)paren
id|cqr
suffix:semicolon
r_private
op_member_access_from_pointer
id|iob.bio_list
op_assign
id|__pa
c_func
(paren
id|dreq-&gt;bio
)paren
suffix:semicolon
id|cqr-&gt;startclk
op_assign
id|get_clock
c_func
(paren
)paren
suffix:semicolon
id|rc
op_assign
id|dia250
c_func
(paren
op_amp
r_private
op_member_access_from_pointer
id|iob
comma
id|RW_BIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OG
l_int|8
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;dia250 returned CC %d&quot;
comma
id|rc
)paren
suffix:semicolon
id|cqr-&gt;status
op_assign
id|DASD_CQR_ERROR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|cqr-&gt;status
op_assign
id|DASD_CQR_DONE
suffix:semicolon
id|dasd_schedule_bh
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
r_else
(brace
id|cqr-&gt;status
op_assign
id|DASD_CQR_IN_IO
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
r_static
r_void
DECL|function|dasd_ext_handler
id|dasd_ext_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|__u16
id|code
)paren
(brace
r_struct
id|dasd_ccw_req
op_star
id|cqr
comma
op_star
id|next
suffix:semicolon
r_struct
id|dasd_device
op_star
id|device
suffix:semicolon
r_int
r_int
r_int
id|expires
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_char
id|status
suffix:semicolon
r_int
id|ip
comma
id|cpu
suffix:semicolon
multiline_comment|/*&n;&t; * Get the external interruption subcode. VM stores&n;&t; * this in the &squot;cpu address&squot; field associated with&n;&t; * the external interrupt. For diag 250 the subcode&n;&t; * needs to be 3.&n;&t; */
r_if
c_cond
(paren
(paren
id|S390_lowcore.cpu_addr
op_amp
l_int|0xff00
)paren
op_ne
l_int|0x0300
)paren
r_return
suffix:semicolon
id|status
op_assign
op_star
(paren
(paren
r_char
op_star
)paren
op_amp
id|S390_lowcore.ext_params
op_plus
l_int|5
)paren
suffix:semicolon
id|ip
op_assign
id|S390_lowcore.ext_params
suffix:semicolon
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ip
)paren
(brace
multiline_comment|/* no intparm: unsolicited interrupt */
id|MESSAGE
c_func
(paren
id|KERN_DEBUG
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;caught unsolicited interrupt&quot;
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cqr
op_assign
(paren
r_struct
id|dasd_ccw_req
op_star
)paren
(paren
id|addr_t
)paren
id|ip
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
id|strncmp
c_func
(paren
id|device-&gt;discipline-&gt;ebcname
comma
(paren
r_char
op_star
)paren
op_amp
id|cqr-&gt;magic
comma
l_int|4
)paren
)paren
(brace
id|DEV_MESSAGE
c_func
(paren
id|KERN_WARNING
comma
id|device
comma
l_string|&quot; magic number of dasd_ccw_req 0x%08X doesn&squot;t&quot;
l_string|&quot; match discipline 0x%08X&quot;
comma
id|cqr-&gt;magic
comma
op_star
(paren
r_int
op_star
)paren
(paren
op_amp
id|device-&gt;discipline-&gt;name
)paren
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* get irq lock to modify request queue */
id|spin_lock_irqsave
c_func
(paren
id|get_ccwdev_lock
c_func
(paren
id|device-&gt;cdev
)paren
comma
id|flags
)paren
suffix:semicolon
id|cqr-&gt;stopclk
op_assign
id|get_clock
c_func
(paren
)paren
suffix:semicolon
id|expires
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
l_int|0
)paren
(brace
id|cqr-&gt;status
op_assign
id|DASD_CQR_DONE
suffix:semicolon
multiline_comment|/* Start first request on queue if possible -&gt; fast_io. */
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|device-&gt;ccw_queue
)paren
)paren
(brace
id|next
op_assign
id|list_entry
c_func
(paren
id|device-&gt;ccw_queue.next
comma
r_struct
id|dasd_ccw_req
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next-&gt;status
op_eq
id|DASD_CQR_QUEUED
)paren
(brace
r_if
c_cond
(paren
id|dasd_start_diag
c_func
(paren
id|next
)paren
op_eq
l_int|0
)paren
id|expires
op_assign
id|next-&gt;expires
suffix:semicolon
r_else
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;Interrupt fastpath failed!&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
id|cqr-&gt;status
op_assign
id|DASD_CQR_FAILED
suffix:semicolon
r_if
c_cond
(paren
id|expires
op_ne
l_int|0
)paren
id|dasd_set_timer
c_func
(paren
id|device
comma
id|expires
)paren
suffix:semicolon
r_else
id|dasd_clear_timer
c_func
(paren
id|device
)paren
suffix:semicolon
id|dasd_schedule_bh
c_func
(paren
id|device
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|get_ccwdev_lock
c_func
(paren
id|device-&gt;cdev
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_diag_check_device
id|dasd_diag_check_device
c_func
(paren
r_struct
id|dasd_device
op_star
id|device
)paren
(brace
r_struct
id|dasd_diag_private
op_star
r_private
suffix:semicolon
r_struct
id|dasd_diag_characteristics
op_star
id|rdc_data
suffix:semicolon
r_struct
id|dasd_diag_bio
id|bio
suffix:semicolon
r_int
op_star
id|label
suffix:semicolon
r_int
id|sb
comma
id|bsize
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_private
op_assign
(paren
r_struct
id|dasd_diag_private
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
id|dasd_diag_private
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
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;memory allocation failed for private data&quot;
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
id|rdc_data-&gt;dev_nr
op_assign
id|_ccw_device_get_device_number
c_func
(paren
id|device-&gt;cdev
)paren
suffix:semicolon
id|rdc_data-&gt;rdc_len
op_assign
r_sizeof
(paren
r_struct
id|dasd_diag_characteristics
)paren
suffix:semicolon
id|rc
op_assign
id|diag210
c_func
(paren
(paren
r_struct
id|diag210
op_star
)paren
id|rdc_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
op_minus
id|ENOTSUPP
suffix:semicolon
multiline_comment|/* Figure out position of label block */
r_switch
c_cond
(paren
r_private
op_member_access_from_pointer
id|rdc_data.vdev_class
)paren
(brace
r_case
id|DEV_CLASS_FBA
suffix:colon
r_private
op_member_access_from_pointer
id|pt_block
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DEV_CLASS_ECKD
suffix:colon
r_private
op_member_access_from_pointer
id|pt_block
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOTSUPP
suffix:semicolon
)brace
id|DBF_EVENT
c_func
(paren
id|DBF_INFO
comma
l_string|&quot;%04X: %04X on real %04X/%02X&quot;
comma
id|rdc_data-&gt;dev_nr
comma
id|rdc_data-&gt;vdev_type
comma
id|rdc_data-&gt;rdev_type
comma
id|rdc_data-&gt;rdev_model
)paren
suffix:semicolon
multiline_comment|/* terminate all outstanding operations */
id|mdsk_term_io
c_func
(paren
id|device
)paren
suffix:semicolon
multiline_comment|/* figure out blocksize of device */
id|label
op_assign
(paren
r_int
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|label
op_eq
l_int|NULL
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_WARNING
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;No memory to allocate initialization request&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_for
c_loop
(paren
id|bsize
op_assign
l_int|512
suffix:semicolon
id|bsize
op_le
id|PAGE_SIZE
suffix:semicolon
id|bsize
op_lshift_assign
l_int|1
)paren
(brace
id|mdsk_init_io
c_func
(paren
id|device
comma
id|bsize
comma
l_int|0
comma
l_int|64
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|bio
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dasd_diag_bio
)paren
)paren
suffix:semicolon
id|bio.type
op_assign
id|MDSK_READ_REQ
suffix:semicolon
id|bio.block_number
op_assign
r_private
op_member_access_from_pointer
id|pt_block
op_plus
l_int|1
suffix:semicolon
id|bio.buffer
op_assign
id|__pa
c_func
(paren
id|label
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
r_private
op_member_access_from_pointer
id|iob
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dasd_diag_rw_io
)paren
)paren
suffix:semicolon
r_private
op_member_access_from_pointer
id|iob.dev_nr
op_assign
id|rdc_data-&gt;dev_nr
suffix:semicolon
r_private
op_member_access_from_pointer
id|iob.key
op_assign
l_int|0
suffix:semicolon
r_private
op_member_access_from_pointer
id|iob.flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* do synchronous io */
r_private
op_member_access_from_pointer
id|iob.block_count
op_assign
l_int|1
suffix:semicolon
r_private
op_member_access_from_pointer
id|iob.interrupt_params
op_assign
l_int|0
suffix:semicolon
r_private
op_member_access_from_pointer
id|iob.bio_list
op_assign
id|__pa
c_func
(paren
op_amp
id|bio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dia250
c_func
(paren
op_amp
r_private
op_member_access_from_pointer
id|iob
comma
id|RW_BIO
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|mdsk_term_io
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bsize
op_le
id|PAGE_SIZE
op_logical_and
id|label
(braket
l_int|3
)braket
op_eq
id|bsize
op_logical_and
id|label
(braket
l_int|0
)braket
op_eq
l_int|0xc3d4e2f1
op_logical_and
id|label
(braket
l_int|13
)braket
op_ne
l_int|0
)paren
(brace
id|device-&gt;blocks
op_assign
id|label
(braket
l_int|7
)braket
suffix:semicolon
id|device-&gt;bp_block
op_assign
id|bsize
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
id|bsize
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
id|DEV_MESSAGE
c_func
(paren
id|KERN_INFO
comma
id|device
comma
l_string|&quot;capacity (%dkB blks): %ldkB&quot;
comma
(paren
id|device-&gt;bp_block
op_rshift
l_int|10
)paren
comma
(paren
id|device-&gt;blocks
op_lshift
id|device-&gt;s2b_shift
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|rc
op_assign
op_minus
id|EMEDIUMTYPE
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|label
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_int
DECL|function|dasd_diag_fill_geometry
id|dasd_diag_fill_geometry
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
DECL|function|dasd_diag_examine_error
id|dasd_diag_examine_error
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
id|stat
)paren
(brace
r_return
id|dasd_era_fatal
suffix:semicolon
)brace
r_static
id|dasd_erp_fn_t
DECL|function|dasd_diag_erp_action
id|dasd_diag_erp_action
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
DECL|function|dasd_diag_erp_postaction
id|dasd_diag_erp_postaction
c_func
(paren
r_struct
id|dasd_ccw_req
op_star
id|cqr
)paren
(brace
r_return
id|dasd_default_erp_postaction
suffix:semicolon
)brace
r_static
r_struct
id|dasd_ccw_req
op_star
DECL|function|dasd_diag_build_cp
id|dasd_diag_build_cp
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
id|dasd_ccw_req
op_star
id|cqr
suffix:semicolon
r_struct
id|dasd_diag_req
op_star
id|dreq
suffix:semicolon
r_struct
id|dasd_diag_bio
op_star
id|dbio
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
id|blksize
comma
id|off
suffix:semicolon
r_int
r_char
id|rw_cmd
suffix:semicolon
r_int
id|i
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
id|rw_cmd
op_assign
id|MDSK_READ_REQ
suffix:semicolon
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
id|rw_cmd
op_assign
id|MDSK_WRITE_REQ
suffix:semicolon
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
multiline_comment|/* Build the request */
id|datasize
op_assign
r_sizeof
(paren
r_struct
id|dasd_diag_req
)paren
op_plus
id|count
op_star
r_sizeof
(paren
r_struct
id|dasd_diag_bio
)paren
suffix:semicolon
id|cqr
op_assign
id|dasd_smalloc_request
c_func
(paren
id|dasd_diag_discipline.name
comma
l_int|0
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
id|dreq
op_assign
(paren
r_struct
id|dasd_diag_req
op_star
)paren
id|cqr-&gt;data
suffix:semicolon
id|dreq-&gt;block_count
op_assign
id|count
suffix:semicolon
id|dbio
op_assign
id|dreq-&gt;bio
suffix:semicolon
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
id|memset
c_func
(paren
id|dbio
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dasd_diag_bio
)paren
)paren
suffix:semicolon
id|dbio-&gt;type
op_assign
id|rw_cmd
suffix:semicolon
id|dbio-&gt;block_number
op_assign
id|recid
op_plus
l_int|1
suffix:semicolon
id|dbio-&gt;buffer
op_assign
id|__pa
c_func
(paren
id|dst
)paren
suffix:semicolon
id|dbio
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
)brace
id|cqr-&gt;buildclk
op_assign
id|get_clock
c_func
(paren
)paren
suffix:semicolon
id|cqr-&gt;device
op_assign
id|device
suffix:semicolon
id|cqr-&gt;expires
op_assign
l_int|50
op_star
id|HZ
suffix:semicolon
multiline_comment|/* 50 seconds */
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
DECL|function|dasd_diag_fill_info
id|dasd_diag_fill_info
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
r_struct
id|dasd_diag_private
op_star
r_private
suffix:semicolon
r_private
op_assign
(paren
r_struct
id|dasd_diag_private
op_star
)paren
id|device
op_member_access_from_pointer
r_private
suffix:semicolon
id|info-&gt;label_block
op_assign
r_private
op_member_access_from_pointer
id|pt_block
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
id|dasd_diag_characteristics
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
id|dasd_diag_private
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
id|dasd_diag_characteristics
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
DECL|function|dasd_diag_dump_sense
id|dasd_diag_dump_sense
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
id|stat
)paren
(brace
r_char
op_star
id|page
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
id|GFP_KERNEL
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
id|MESSAGE
c_func
(paren
id|KERN_ERR
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;No memory to dump sense data&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|page
comma
id|KERN_WARNING
id|PRINTK_HEADER
l_string|&quot;device %s: I/O status report:&bslash;n&quot;
comma
id|device-&gt;cdev-&gt;dev.bus_id
)paren
suffix:semicolon
id|MESSAGE
c_func
(paren
id|KERN_ERR
comma
l_string|&quot;Sense data:&bslash;n%s&quot;
comma
id|page
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
multiline_comment|/*&n; * max_blocks is dependent on the amount of storage that is available&n; * in the static io buffer for each device. Currently each device has&n; * 8192 bytes (=2 pages). dasd diag is only relevant for 31 bit.&n; * The struct dasd_ccw_req has 96 bytes, the struct dasd_diag_req has&n; * 8 bytes and the struct dasd_diag_bio for each block has 16 bytes. &n; * That makes:&n; * (8192 - 96 - 8) / 16 = 505.5 blocks at maximum.&n; * We want to fit two into the available memory so that we can immediately&n; * start the next request if one finishes off. That makes 252.75 blocks&n; * for one request. Give a little safety and the result is 240.&n; */
DECL|variable|dasd_diag_discipline
r_struct
id|dasd_discipline
id|dasd_diag_discipline
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
l_string|&quot;DIAG&quot;
comma
dot
id|ebcname
op_assign
l_string|&quot;DIAG&quot;
comma
dot
id|max_blocks
op_assign
l_int|240
comma
dot
id|check_device
op_assign
id|dasd_diag_check_device
comma
dot
id|fill_geometry
op_assign
id|dasd_diag_fill_geometry
comma
dot
id|start_IO
op_assign
id|dasd_start_diag
comma
dot
id|examine_error
op_assign
id|dasd_diag_examine_error
comma
dot
id|erp_action
op_assign
id|dasd_diag_erp_action
comma
dot
id|erp_postaction
op_assign
id|dasd_diag_erp_postaction
comma
dot
id|build_cp
op_assign
id|dasd_diag_build_cp
comma
dot
id|dump_sense
op_assign
id|dasd_diag_dump_sense
comma
dot
id|fill_info
op_assign
id|dasd_diag_fill_info
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|dasd_diag_init
id|dasd_diag_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_IS_VM
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_INFO
comma
l_string|&quot;Machine is not VM: %s discipline not initializing&quot;
comma
id|dasd_diag_discipline.name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ASCEBC
c_func
(paren
id|dasd_diag_discipline.ebcname
comma
l_int|4
)paren
suffix:semicolon
id|ctl_set_bit
c_func
(paren
l_int|0
comma
l_int|9
)paren
suffix:semicolon
id|register_external_interrupt
c_func
(paren
l_int|0x2603
comma
id|dasd_ext_handler
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|dasd_diag_cleanup
id|dasd_diag_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_IS_VM
)paren
(brace
id|MESSAGE
c_func
(paren
id|KERN_INFO
comma
l_string|&quot;Machine is not VM: %s discipline not initializing&quot;
comma
id|dasd_diag_discipline.name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|unregister_external_interrupt
c_func
(paren
l_int|0x2603
comma
id|dasd_ext_handler
)paren
suffix:semicolon
id|ctl_clear_bit
c_func
(paren
l_int|0
comma
l_int|9
)paren
suffix:semicolon
)brace
DECL|variable|dasd_diag_init
id|module_init
c_func
(paren
id|dasd_diag_init
)paren
suffix:semicolon
DECL|variable|dasd_diag_cleanup
id|module_exit
c_func
(paren
id|dasd_diag_cleanup
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: 1&n; * tab-width: 8&n; * End:&n; */
eof
