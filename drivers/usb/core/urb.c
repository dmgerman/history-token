macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;hcd.h&quot;
multiline_comment|/**&n; * usb_alloc_urb - creates a new urb for a USB driver to use&n; * @iso_packets: number of iso packets for this urb&n; * @mem_flags: the type of memory to allocate, see kmalloc() for a list of&n; *&t;valid options for this.&n; *&n; * Creates an urb for the USB driver to use, initializes a few internal&n; * structures, incrementes the usage counter, and returns a pointer to it.&n; *&n; * If no memory is available, NULL is returned.&n; *&n; * If the driver want to use this urb for interrupt, control, or bulk&n; * endpoints, pass &squot;0&squot; as the number of iso packets.&n; *&n; * The driver must call usb_free_urb() when it is finished with the urb.&n; */
DECL|function|usb_alloc_urb
r_struct
id|urb
op_star
id|usb_alloc_urb
c_func
(paren
r_int
id|iso_packets
comma
r_int
id|mem_flags
)paren
(brace
r_struct
id|urb
op_star
id|urb
suffix:semicolon
id|urb
op_assign
(paren
r_struct
id|urb
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|urb
)paren
op_plus
id|iso_packets
op_star
r_sizeof
(paren
r_struct
id|usb_iso_packet_descriptor
)paren
comma
id|mem_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
)paren
(brace
id|err
c_func
(paren
l_string|&quot;alloc_urb: kmalloc failed&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|urb
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|urb
)paren
)paren
suffix:semicolon
id|urb-&gt;count
op_assign
(paren
id|atomic_t
)paren
id|ATOMIC_INIT
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|urb-&gt;lock
)paren
suffix:semicolon
r_return
id|urb
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_free_urb - frees the memory used by a urb when all users of it are finished&n; * @urb: pointer to the urb to free&n; *&n; * Must be called when a user of a urb is finished with it.  When the last user&n; * of the urb calls this function, the memory of the urb is freed.&n; *&n; * Note: The transfer buffer associated with the urb is not freed, that must be&n; * done elsewhere.&n; */
DECL|function|usb_free_urb
r_void
id|usb_free_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_if
c_cond
(paren
id|urb
)paren
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|urb-&gt;count
)paren
)paren
id|kfree
c_func
(paren
id|urb
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_get_urb - increments the reference count of the urb&n; * @urb: pointer to the urb to modify&n; *&n; * This must be  called whenever a urb is transfered from a device driver to a&n; * host controller driver.  This allows proper reference counting to happen&n; * for urbs.&n; *&n; * A pointer to the urb with the incremented reference counter is returned.&n; */
DECL|function|usb_get_urb
r_struct
id|urb
op_star
id|usb_get_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_if
c_cond
(paren
id|urb
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|urb-&gt;count
)paren
suffix:semicolon
r_return
id|urb
suffix:semicolon
)brace
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------*/
multiline_comment|/**&n; * usb_submit_urb - issue an asynchronous transfer request for an endpoint&n; * @urb: pointer to the urb describing the request&n; * @mem_flags: the type of memory to allocate, see kmalloc() for a list&n; *&t;of valid options for this.&n; *&n; * This submits a transfer request, and transfers control of the URB&n; * describing that request to the USB subsystem.  Request completion will&n; * be indicated later, asynchronously, by calling the completion handler.&n; * The three types of completion are success, error, and unlink&n; * (also called &quot;request cancellation&quot;).&n; * URBs may be submitted in interrupt context.&n; *&n; * The caller must have correctly initialized the URB before submitting&n; * it.  Functions such as usb_fill_bulk_urb() and usb_fill_control_urb() are&n; * available to ensure that most fields are correctly initialized, for&n; * the particular kind of transfer, although they will not initialize&n; * any transfer flags.&n; *&n; * Successful submissions return 0; otherwise this routine returns a&n; * negative error number.  If the submission is successful, the complete()&n; * fuction of the urb will be called when the USB host driver is&n; * finished with the urb (either a successful transmission, or some&n; * error case.)&n; *&n; * Unreserved Bandwidth Transfers:&n; *&n; * Bulk or control requests complete only once.  When the completion&n; * function is called, control of the URB is returned to the device&n; * driver which issued the request.  The completion handler may then&n; * immediately free or reuse that URB.&n; *&n; * Bulk URBs may be queued by submitting an URB to an endpoint before&n; * previous ones complete.  This can maximize bandwidth utilization by&n; * letting the USB controller start work on the next URB without any&n; * delay to report completion (scheduling and processing an interrupt)&n; * and then submit that next request.&n; *&n; * For control endpoints, the synchronous usb_control_msg() call is&n; * often used (in non-interrupt context) instead of this call.&n; *&n; * Reserved Bandwidth Transfers:&n; *&n; * Periodic URBs (interrupt or isochronous) are performed repeatedly.&n; *&n; * For interrupt requests this is (currently) automagically done&n; * until the original request is aborted.  When the completion callback&n; * indicates the URB has been unlinked (with a special status code),&n; * control of that URB returns to the device driver.  Otherwise, the&n; * completion handler does not control the URB, and should not change&n; * any of its fields.&n; *&n; * For isochronous requests, the completion handler is expected to&n; * submit an urb, typically resubmitting its parameter, until drivers&n; * stop wanting data transfers.  (For example, audio playback might have&n; * finished, or a webcam turned off.)&n; *&n; * If the USB subsystem can&squot;t reserve sufficient bandwidth to perform&n; * the periodic request, and bandwidth reservation is being done for&n; * this controller, submitting such a periodic request will fail.&n; *&n; * Memory Flags:&n; *&n; * The general rules for how to decide which mem_flags to use&n; * are the same as for kmalloc.  There are four&n; * different possible values; GFP_KERNEL, GFP_NOFS, GFP_NOIO and&n; * GFP_ATOMIC.&n; *&n; * GFP_NOFS is not ever used, as it has not been implemented yet.&n; *&n; * GFP_ATOMIC is used when&n; *   (a) you are inside a completion handler, an interrupt, bottom half,&n; *       tasklet or timer, or&n; *   (b) you are holding a spinlock or rwlock (does not apply to&n; *       semaphores), or&n; *   (c) current-&gt;state != TASK_RUNNING, this is the case only after&n; *       you&squot;ve changed it.&n; * &n; * GFP_NOIO is used in the block io path and error handling of storage&n; * devices.&n; *&n; * All other situations use GFP_KERNEL.&n; *&n; * Some more specific rules for mem_flags can be inferred, such as&n; *  (1) start_xmit, timeout, and receive methods of network drivers must&n; *      use GFP_ATOMIC (they are called with a spinlock held);&n; *  (2) queuecommand methods of scsi drivers must use GFP_ATOMIC (also&n; *      called with a spinlock held);&n; *  (3) If you use a kernel thread with a network driver you must use&n; *      GFP_NOIO, unless (b) or (c) apply;&n; *  (4) after you have done a down() you can use GFP_KERNEL, unless (b) or (c)&n; *      apply or your are in a storage driver&squot;s block io path;&n; *  (5) USB probe and disconnect can use GFP_KERNEL unless (b) or (c) apply; and&n; *  (6) changing firmware on a running storage or net device uses&n; *      GFP_NOIO, unless b) or c) apply&n; *&n; */
DECL|function|usb_submit_urb
r_int
id|usb_submit_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_int
id|mem_flags
)paren
(brace
r_int
id|pipe
comma
id|temp
comma
id|max
suffix:semicolon
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
r_struct
id|usb_operations
op_star
id|op
suffix:semicolon
r_int
id|is_out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
op_logical_or
id|urb-&gt;hcpriv
op_logical_or
op_logical_neg
id|urb-&gt;complete
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev
op_assign
id|urb-&gt;dev
)paren
op_logical_or
op_logical_neg
id|dev-&gt;bus
op_logical_or
id|dev-&gt;devnum
op_le
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|op
op_assign
id|dev-&gt;bus-&gt;op
)paren
op_logical_or
op_logical_neg
id|op-&gt;submit_urb
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|urb-&gt;status
op_assign
op_minus
id|EINPROGRESS
suffix:semicolon
id|urb-&gt;actual_length
op_assign
l_int|0
suffix:semicolon
id|urb-&gt;bandwidth
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Lots of sanity checks, so HCDs can rely on clean data&n;&t; * and don&squot;t need to duplicate tests&n;&t; */
id|pipe
op_assign
id|urb-&gt;pipe
suffix:semicolon
id|temp
op_assign
id|usb_pipetype
(paren
id|pipe
)paren
suffix:semicolon
id|is_out
op_assign
id|usb_pipeout
(paren
id|pipe
)paren
suffix:semicolon
multiline_comment|/* (actually HCDs may need to duplicate this, endpoint might yet&n;&t; * stall due to queued bulk/intr transactions that complete after&n;&t; * we check)&n;&t; */
r_if
c_cond
(paren
id|usb_endpoint_halted
(paren
id|dev
comma
id|usb_pipeendpoint
(paren
id|pipe
)paren
comma
id|is_out
)paren
)paren
r_return
op_minus
id|EPIPE
suffix:semicolon
multiline_comment|/* FIXME there should be a sharable lock protecting us against&n;&t; * config/altsetting changes and disconnects, kicking in here.&n;&t; * (here == before maxpacket, and eventually endpoint type,&n;&t; * checks get made.)&n;&t; */
id|max
op_assign
id|usb_maxpacket
(paren
id|dev
comma
id|pipe
comma
id|is_out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max
op_le
l_int|0
)paren
(brace
id|dbg
(paren
l_string|&quot;%s: bogus endpoint %d-%s on usb-%s-%s (bad maxpacket %d)&quot;
comma
id|__FUNCTION__
comma
id|usb_pipeendpoint
(paren
id|pipe
)paren
comma
id|is_out
ques
c_cond
l_string|&quot;OUT&quot;
suffix:colon
l_string|&quot;IN&quot;
comma
id|dev-&gt;bus-&gt;bus_name
comma
id|dev-&gt;devpath
comma
id|max
)paren
suffix:semicolon
r_return
op_minus
id|EMSGSIZE
suffix:semicolon
)brace
multiline_comment|/* periodic transfers limit size per frame/uframe,&n;&t; * but drivers only control those sizes for ISO.&n;&t; * while we&squot;re checking, initialize return status.&n;&t; */
r_if
c_cond
(paren
id|temp
op_eq
id|PIPE_ISOCHRONOUS
)paren
(brace
r_int
id|n
comma
id|len
suffix:semicolon
multiline_comment|/* &quot;high bandwidth&quot; mode, 1-3 packets/uframe? */
r_if
c_cond
(paren
id|dev-&gt;speed
op_eq
id|USB_SPEED_HIGH
)paren
(brace
r_int
id|mult
op_assign
l_int|1
op_plus
(paren
(paren
id|max
op_rshift
l_int|11
)paren
op_amp
l_int|0x03
)paren
suffix:semicolon
id|max
op_and_assign
l_int|0x03ff
suffix:semicolon
id|max
op_mul_assign
id|mult
suffix:semicolon
)brace
r_if
c_cond
(paren
id|urb-&gt;number_of_packets
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|urb-&gt;number_of_packets
suffix:semicolon
id|n
op_increment
)paren
(brace
id|len
op_assign
id|urb-&gt;iso_frame_desc
(braket
id|n
)braket
dot
id|length
suffix:semicolon
r_if
c_cond
(paren
id|len
template_param
id|max
)paren
r_return
op_minus
id|EMSGSIZE
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
id|n
)braket
dot
id|status
op_assign
op_minus
id|EXDEV
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
id|n
)braket
dot
id|actual_length
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* the I/O buffer must be mapped/unmapped, except when length=0 */
r_if
c_cond
(paren
id|urb-&gt;transfer_buffer_length
OL
l_int|0
)paren
r_return
op_minus
id|EMSGSIZE
suffix:semicolon
macro_line|#ifdef DEBUG
multiline_comment|/* stuff that drivers shouldn&squot;t do, but which shouldn&squot;t&n;&t; * cause problems in HCDs if they get it wrong.&n;&t; */
(brace
r_int
r_int
id|orig_flags
op_assign
id|urb-&gt;transfer_flags
suffix:semicolon
r_int
r_int
id|allowed
suffix:semicolon
multiline_comment|/* enforce simple/standard policy */
id|allowed
op_assign
id|USB_ASYNC_UNLINK
suffix:semicolon
singleline_comment|// affects later unlinks
id|allowed
op_or_assign
id|URB_NO_DMA_MAP
suffix:semicolon
id|allowed
op_or_assign
id|URB_NO_INTERRUPT
suffix:semicolon
r_switch
c_cond
(paren
id|temp
)paren
(brace
r_case
id|PIPE_BULK
suffix:colon
r_if
c_cond
(paren
id|is_out
)paren
id|allowed
op_or_assign
id|USB_ZERO_PACKET
suffix:semicolon
multiline_comment|/* FALLTHROUGH */
r_case
id|PIPE_CONTROL
suffix:colon
id|allowed
op_or_assign
id|USB_NO_FSBR
suffix:semicolon
multiline_comment|/* only affects UHCI */
multiline_comment|/* FALLTHROUGH */
r_default
suffix:colon
(brace
)brace
multiline_comment|/* all non-iso endpoints */
r_if
c_cond
(paren
op_logical_neg
id|is_out
)paren
id|allowed
op_or_assign
id|URB_SHORT_NOT_OK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PIPE_ISOCHRONOUS
suffix:colon
id|allowed
op_or_assign
id|USB_ISO_ASAP
suffix:semicolon
r_break
suffix:semicolon
)brace
id|urb-&gt;transfer_flags
op_and_assign
id|allowed
suffix:semicolon
multiline_comment|/* fail if submitter gave bogus flags */
r_if
c_cond
(paren
id|urb-&gt;transfer_flags
op_ne
id|orig_flags
)paren
(brace
id|err
(paren
l_string|&quot;BOGUS urb flags, %x --&gt; %x&quot;
comma
id|orig_flags
comma
id|urb-&gt;transfer_flags
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Force periodic transfer intervals to be legal values that are&n;&t; * a power of two (so HCDs don&squot;t need to).&n;&t; *&n;&t; * FIXME want bus-&gt;{intr,iso}_sched_horizon values here.  Each HC&n;&t; * supports different values... this uses EHCI/UHCI defaults (and&n;&t; * EHCI can use smaller non-default values).&n;&t; */
r_switch
c_cond
(paren
id|temp
)paren
(brace
r_case
id|PIPE_ISOCHRONOUS
suffix:colon
r_case
id|PIPE_INTERRUPT
suffix:colon
multiline_comment|/* too small? */
r_if
c_cond
(paren
id|urb-&gt;interval
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* too big? */
r_switch
c_cond
(paren
id|dev-&gt;speed
)paren
(brace
r_case
id|USB_SPEED_HIGH
suffix:colon
multiline_comment|/* units are microframes */
singleline_comment|// NOTE usb handles 2^15
r_if
c_cond
(paren
id|urb-&gt;interval
OG
(paren
l_int|1024
op_star
l_int|8
)paren
)paren
id|urb-&gt;interval
op_assign
l_int|1024
op_star
l_int|8
suffix:semicolon
id|temp
op_assign
l_int|1024
op_star
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_SPEED_FULL
suffix:colon
multiline_comment|/* units are frames/msec */
r_case
id|USB_SPEED_LOW
suffix:colon
r_if
c_cond
(paren
id|temp
op_eq
id|PIPE_INTERRUPT
)paren
(brace
r_if
c_cond
(paren
id|urb-&gt;interval
OG
l_int|255
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
singleline_comment|// NOTE ohci only handles up to 32
id|temp
op_assign
l_int|128
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|urb-&gt;interval
OG
l_int|1024
)paren
id|urb-&gt;interval
op_assign
l_int|1024
suffix:semicolon
singleline_comment|// NOTE usb and ohci handle up to 2^15
id|temp
op_assign
l_int|1024
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* power of two? */
r_while
c_loop
(paren
id|temp
OG
id|urb-&gt;interval
)paren
id|temp
op_rshift_assign
l_int|1
suffix:semicolon
id|urb-&gt;interval
op_assign
id|temp
suffix:semicolon
)brace
r_return
id|op-&gt;submit_urb
(paren
id|urb
comma
id|mem_flags
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------*/
multiline_comment|/**&n; * usb_unlink_urb - abort/cancel a transfer request for an endpoint&n; * @urb: pointer to urb describing a previously submitted request&n; *&n; * This routine cancels an in-progress request.  The requests&squot;s&n; * completion handler will be called with a status code indicating&n; * that the request has been canceled, and that control of the URB&n; * has been returned to that device driver.  This is the only way&n; * to stop an interrupt transfer, so long as the device is connected.&n; *&n; * When the USB_ASYNC_UNLINK transfer flag for the URB is clear, this&n; * request is synchronous.  Success is indicated by returning zero,&n; * at which time the urb will have been unlinked,&n; * and the completion function will see status -ENOENT.  Failure is&n; * indicated by any other return value.  This mode may not be used&n; * when unlinking an urb from an interrupt context, such as a bottom&n; * half or a completion handler,&n; *&n; * When the USB_ASYNC_UNLINK transfer flag for the URB is set, this&n; * request is asynchronous.  Success is indicated by returning -EINPROGRESS,&n; * at which time the urb will normally not have been unlinked,&n; * and the completion function will see status -ECONNRESET.  Failure is&n; * indicated by any other return value.&n; */
DECL|function|usb_unlink_urb
r_int
id|usb_unlink_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_if
c_cond
(paren
id|urb
op_logical_and
id|urb-&gt;dev
op_logical_and
id|urb-&gt;dev-&gt;bus
op_logical_and
id|urb-&gt;dev-&gt;bus-&gt;op
)paren
r_return
id|urb-&gt;dev-&gt;bus-&gt;op
op_member_access_from_pointer
id|unlink_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
r_else
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
singleline_comment|// asynchronous request completion model
DECL|variable|usb_alloc_urb
id|EXPORT_SYMBOL
c_func
(paren
id|usb_alloc_urb
)paren
suffix:semicolon
DECL|variable|usb_free_urb
id|EXPORT_SYMBOL
c_func
(paren
id|usb_free_urb
)paren
suffix:semicolon
DECL|variable|usb_get_urb
id|EXPORT_SYMBOL
c_func
(paren
id|usb_get_urb
)paren
suffix:semicolon
DECL|variable|usb_submit_urb
id|EXPORT_SYMBOL
c_func
(paren
id|usb_submit_urb
)paren
suffix:semicolon
DECL|variable|usb_unlink_urb
id|EXPORT_SYMBOL
c_func
(paren
id|usb_unlink_urb
)paren
suffix:semicolon
eof
