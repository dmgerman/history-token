multiline_comment|/*&n; * &lt;linux/usb_gadget.h&gt;&n; *&n; * We call the USB code inside a Linux-based peripheral device a &quot;gadget&quot;&n; * driver, except for the hardware-specific bus glue.  One USB host can&n; * master many USB gadgets, but the gadgets are only slaved to one host.&n; *&n; *&n; * (c) Copyright 2002-2003 by David Brownell&n; * All Rights Reserved.&n; *&n; * This software is licensed under the GNU GPL version 2.&n; */
macro_line|#ifndef __LINUX_USB_GADGET_H
DECL|macro|__LINUX_USB_GADGET_H
mdefine_line|#define __LINUX_USB_GADGET_H
macro_line|#ifdef __KERNEL__
r_struct
id|usb_ep
suffix:semicolon
multiline_comment|/**&n; * struct usb_request - describes one i/o request&n; * @buf: Buffer used for data.  Always provide this; some controllers&n; * &t;only use PIO, or don&squot;t use DMA for some endpoints.&n; * @dma: DMA address corresponding to &squot;buf&squot;.  If you don&squot;t set this&n; * &t;field, and the usb controller needs one, it is responsible&n; * &t;for mapping and unmapping the buffer.&n; * @length: Length of that data&n; * @no_interrupt: If true, hints that no completion irq is needed.&n; *&t;Helpful sometimes with deep request queues.&n; * @zero: If true, when writing data, makes the last packet be &quot;short&quot;&n; *     by adding a zero length packet as needed;&n; * @short_not_ok: When reading data, makes short packets be&n; *     treated as errors (queue stops advancing till cleanup).&n; * @complete: Function called when request completes&n; * @context: For use by the completion callback&n; * @list: For use by the gadget driver.&n; * @status: Reports completion code, zero or a negative errno.&n; * &t;Normally, faults block the transfer queue from advancing until&n; * &t;the completion callback returns.&n; * &t;Code &quot;-ESHUTDOWN&quot; indicates completion caused by device disconnect,&n; * &t;or when the driver disabled the endpoint.&n; * @actual: Reports actual bytes transferred.  For reads (OUT&n; * &t;transfers) this may be less than the requested length.  If the&n; * &t;short_not_ok flag is set, short reads are treated as errors&n; * &t;even when status otherwise indicates successful completion.&n; * &t;Note that for writes (IN transfers) the data bytes may still&n; * &t;reside in a device-side FIFO.&n; *&n; * These are allocated/freed through the endpoint they&squot;re used with.  The&n; * hardware&squot;s driver can add extra per-request data to the memory it returns,&n; * which often avoids separate memory allocations (potential failures),&n; * later when the request is queued.&n; *&n; * Request flags affect request handling, such as whether a zero length&n; * packet is written (the &quot;zero&quot; flag), whether a short read should be&n; * treated as an error (blocking request queue advance, the &quot;short_not_ok&quot;&n; * flag), or hinting that an interrupt is not required (the &quot;no_interrupt&quot;&n; * flag, for use with deep request queues).&n; *&n; * Bulk endpoints can use any size buffers, and can also be used for interrupt&n; * transfers. interrupt-only endpoints can be much less functional.&n; */
singleline_comment|// NOTE this is analagous to &squot;struct urb&squot; on the host side,
singleline_comment|// except that it&squot;s thinner and promotes more pre-allocation.
singleline_comment|//
singleline_comment|// ISSUE should this be allocated through the device?
DECL|struct|usb_request
r_struct
id|usb_request
(brace
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|dma
id|dma_addr_t
id|dma
suffix:semicolon
DECL|member|no_interrupt
r_int
id|no_interrupt
suffix:colon
l_int|1
comma
DECL|member|zero
id|zero
suffix:colon
l_int|1
comma
DECL|member|short_not_ok
id|short_not_ok
suffix:colon
l_int|1
suffix:semicolon
DECL|member|complete
r_void
(paren
op_star
id|complete
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_struct
id|usb_request
op_star
id|req
)paren
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|actual
r_int
id|actual
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* endpoint-specific parts of the api to the usb controller hardware.&n; * unlike the urb model, (de)multiplexing layers are not required.&n; * (so this api could slash overhead if used on the host side...)&n; *&n; * note that device side usb controllers commonly differ in how many&n; * endpoints they support, as well as their capabilities.&n; */
DECL|struct|usb_ep_ops
r_struct
id|usb_ep_ops
(brace
DECL|member|enable
r_int
(paren
op_star
id|enable
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_const
r_struct
id|usb_endpoint_descriptor
op_star
id|desc
)paren
suffix:semicolon
DECL|member|disable
r_int
(paren
op_star
id|disable
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
)paren
suffix:semicolon
DECL|member|alloc_request
r_struct
id|usb_request
op_star
(paren
op_star
id|alloc_request
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_int
id|gfp_flags
)paren
suffix:semicolon
DECL|member|free_request
r_void
(paren
op_star
id|free_request
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_struct
id|usb_request
op_star
id|req
)paren
suffix:semicolon
DECL|member|alloc_buffer
r_void
op_star
(paren
op_star
id|alloc_buffer
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_int
id|bytes
comma
id|dma_addr_t
op_star
id|dma
comma
r_int
id|gfp_flags
)paren
suffix:semicolon
DECL|member|free_buffer
r_void
(paren
op_star
id|free_buffer
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_void
op_star
id|buf
comma
id|dma_addr_t
id|dma
comma
r_int
id|bytes
)paren
suffix:semicolon
singleline_comment|// NOTE:  on 2.5, drivers may also use dma_map() and
singleline_comment|// dma_sync_single() to manage dma overhead. 
DECL|member|queue
r_int
(paren
op_star
id|queue
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_struct
id|usb_request
op_star
id|req
comma
r_int
id|gfp_flags
)paren
suffix:semicolon
DECL|member|dequeue
r_int
(paren
op_star
id|dequeue
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_struct
id|usb_request
op_star
id|req
)paren
suffix:semicolon
DECL|member|set_halt
r_int
(paren
op_star
id|set_halt
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_int
id|value
)paren
suffix:semicolon
DECL|member|fifo_status
r_int
(paren
op_star
id|fifo_status
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
)paren
suffix:semicolon
DECL|member|fifo_flush
r_void
(paren
op_star
id|fifo_flush
)paren
(paren
r_struct
id|usb_ep
op_star
id|ep
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct usb_ep - device side representation of USB endpoint&n; * @name:identifier for the endpoint, such as &quot;ep-a&quot; or &quot;ep9in-bulk&quot;&n; * @ep_list:the gadget&squot;s ep_list holds all of its endpoints&n; * @maxpacket:the maximum packet size used on this endpoint, as&n; * &t;configured when the endpoint was enabled.&n; * @driver_data:for use by the gadget driver.  all other fields are&n; * &t;read-only to gadget drivers.&n; *&n; * the bus controller driver lists all the general purpose endpoints in&n; * gadget-&gt;ep_list.  the control endpoint (gadget-&gt;ep0) is not in that list,&n; * and is accessed only in response to a driver setup() callback.&n; */
DECL|struct|usb_ep
r_struct
id|usb_ep
(brace
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|ops
r_const
r_struct
id|usb_ep_ops
op_star
id|ops
suffix:semicolon
DECL|member|ep_list
r_struct
id|list_head
id|ep_list
suffix:semicolon
DECL|member|maxpacket
r_int
id|maxpacket
suffix:colon
l_int|16
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/**&n; * usb_ep_enable - configure endpoint, making it usable&n; * @ep:the endpoint being configured.  may not be the endpoint named &quot;ep0&quot;.&n; * &t;drivers discover endpoints through the ep_list of a usb_gadget.&n; * @desc:descriptor for desired behavior.  caller guarantees this pointer&n; * &t;remains valid until the endpoint is disabled; the data byte order&n; * &t;is little-endian (usb-standard).&n; *&n; * when configurations are set, or when interface settings change, the driver&n; * will enable or disable the relevant endpoints.  while it is enabled, an&n; * endpoint may be used for i/o until the driver receives a disconnect() from&n; * the host or until the endpoint is disabled.&n; *&n; * the ep0 implementation (which calls this routine) must ensure that the&n; * hardware capabilities of each endpoint match the descriptor provided&n; * for it.  for example, an endpoint named &quot;ep2in-bulk&quot; would be usable&n; * for interrupt transfers as well as bulk, but it likely couldn&squot;t be used&n; * for iso transfers or for endpoint 14.  some endpoints are fully&n; * configurable, with more generic names like &quot;ep-a&quot;.  (remember that for&n; * USB, &quot;in&quot; means &quot;towards the USB master&quot;.)&n; *&n; * returns zero, or a negative error code.&n; */
r_static
r_inline
r_int
DECL|function|usb_ep_enable
id|usb_ep_enable
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_const
r_struct
id|usb_endpoint_descriptor
op_star
id|desc
)paren
(brace
r_return
id|ep-&gt;ops-&gt;enable
(paren
id|ep
comma
id|desc
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_disable - endpoint is no longer usable&n; * @ep:the endpoint being unconfigured.  may not be the endpoint named &quot;ep0&quot;.&n; *&n; * no other task may be using this endpoint when this is called.&n; * any pending and uncompleted requests will complete with status&n; * indicating disconnect (-ESHUTDOWN) before this call returns.&n; * gadget drivers must call usb_ep_enable() again before queueing&n; * requests to the endpoint.&n; *&n; * returns zero, or a negative error code.&n; */
r_static
r_inline
r_int
DECL|function|usb_ep_disable
id|usb_ep_disable
(paren
r_struct
id|usb_ep
op_star
id|ep
)paren
(brace
r_return
id|ep-&gt;ops-&gt;disable
(paren
id|ep
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_alloc_request - allocate a request object to use with this endpoint&n; * @ep:the endpoint to be used with with the request&n; * @gfp_flags:GFP_* flags to use&n; *&n; * Request objects must be allocated with this call, since they normally&n; * need controller-specific setup and may even need endpoint-specific&n; * resources such as allocation of DMA descriptors.&n; * Requests may be submitted with usb_ep_queue(), and receive a single&n; * completion callback.  Free requests with usb_ep_free_request(), when&n; * they are no longer needed.&n; *&n; * Returns the request, or null if one could not be allocated.&n; */
r_static
r_inline
r_struct
id|usb_request
op_star
DECL|function|usb_ep_alloc_request
id|usb_ep_alloc_request
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_int
id|gfp_flags
)paren
(brace
r_return
id|ep-&gt;ops-&gt;alloc_request
(paren
id|ep
comma
id|gfp_flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_free_request - frees a request object&n; * @ep:the endpoint associated with the request&n; * @req:the request being freed&n; *&n; * Reverses the effect of usb_ep_alloc_request().&n; * Caller guarantees the request is not queued, and that it will&n; * no longer be requeued (or otherwise used).&n; */
r_static
r_inline
r_void
DECL|function|usb_ep_free_request
id|usb_ep_free_request
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_struct
id|usb_request
op_star
id|req
)paren
(brace
id|ep-&gt;ops-&gt;free_request
(paren
id|ep
comma
id|req
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_alloc_buffer - allocate an I/O buffer&n; * @ep:the endpoint associated with the buffer&n; * @len:length of the desired buffer&n; * @dma:pointer to the buffer&squot;s DMA address; must be valid&n; * @gfp_flags:GFP_* flags to use&n; *&n; * Returns a new buffer, or null if one could not be allocated.&n; * The buffer is suitably aligned for dma, if that endpoint uses DMA,&n; * and the caller won&squot;t have to care about dma-inconsistency&n; * or any hidden &quot;bounce buffer&quot; mechanism.  No additional per-request&n; * DMA mapping will be required for such buffers.&n; * Free it later with usb_ep_free_buffer().&n; *&n; * You don&squot;t need to use this call to allocate I/O buffers unless you&n; * want to make sure drivers don&squot;t incur costs for such &quot;bounce buffer&quot;&n; * copies or per-request DMA mappings.&n; */
r_static
r_inline
r_void
op_star
DECL|function|usb_ep_alloc_buffer
id|usb_ep_alloc_buffer
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_int
id|len
comma
id|dma_addr_t
op_star
id|dma
comma
r_int
id|gfp_flags
)paren
(brace
r_return
id|ep-&gt;ops-&gt;alloc_buffer
(paren
id|ep
comma
id|len
comma
id|dma
comma
id|gfp_flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_free_buffer - frees an i/o buffer&n; * @ep:the endpoint associated with the buffer&n; * @buf:CPU view address of the buffer&n; * @dma:the buffer&squot;s DMA address&n; * @len:length of the buffer&n; *&n; * reverses the effect of usb_ep_alloc_buffer().&n; * caller guarantees the buffer will no longer be accessed&n; */
r_static
r_inline
r_void
DECL|function|usb_ep_free_buffer
id|usb_ep_free_buffer
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_void
op_star
id|buf
comma
id|dma_addr_t
id|dma
comma
r_int
id|len
)paren
(brace
id|ep-&gt;ops-&gt;free_buffer
(paren
id|ep
comma
id|buf
comma
id|dma
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_queue - queues (submits) an I/O request to an endpoint.&n; * @ep:the endpoint associated with the request&n; * @req:the request being submitted&n; * @gfp_flags: GFP_* flags to use in case the lower level driver couldn&squot;t&n; * &t;pre-allocate all necessary memory with the request.&n; *&n; * This tells the device controller to perform the specified request through&n; * that endpoint (reading or writing a buffer).  When the request completes,&n; * including being canceled by usb_ep_dequeue(), the request&squot;s completion&n; * routine is called to return the request to the driver.  Any endpoint&n; * (except control endpoints like ep0) may have more than one transfer&n; * request queued; they complete in FIFO order.  Once a gadget driver&n; * submits a request, that request may not be examined or modified until it&n; * is given back to that driver through the completion callback.&n; *&n; * Each request is turned into one or more packets.  The controller driver&n; * never merges adjacent requests into the same packet.  OUT transfers&n; * will sometimes use data that&squot;s already buffered in the hardware.&n; *&n; * Bulk endpoints can queue any amount of data; the transfer is packetized&n; * automatically.  The last packet will be short if the request doesn&squot;t fill it&n; * out completely.  Zero length packets (ZLPs) should be avoided in portable&n; * protocols since not all usb hardware can successfully handle zero length&n; * packets.  (ZLPs may be explicitly written, and may be implicitly written if&n; * the request &squot;zero&squot; flag is set.)  Bulk endpoints may also be used&n; * for interrupt transfers; but the reverse is not true, and some endpoints&n; * won&squot;t support every interrupt transfer.  (Such as 768 byte packets.)&n; *&n; * Interrupt-only endpoints are less functional than bulk endpoints, for&n; * example by not supporting queueing or not handling buffers that are&n; * larger than the endpoint&squot;s maxpacket size.  They may also treat data&n; * toggle differently.&n; *&n; * Control endpoints ... after getting a setup() callback, the driver queues&n; * one response (optional if it would be zero length).  That enables the&n; * status ack, after transfering data as specified in the response.  Setup&n; * functions may return negative error codes to generate protocol stalls.&n; *&n; * For periodic endpoints, like interrupt or isochronous ones, the usb host&n; * arranges to poll once per interval, and the gadget driver usually will&n; * have queued some data to transfer at that time.&n; *&n; * Returns zero, or a negative error code.  Endpoints that are not enabled,&n; * or which are enabled but halted, report errors; errors will also be&n; * reported when the usb peripheral is disconnected.&n; */
r_static
r_inline
r_int
DECL|function|usb_ep_queue
id|usb_ep_queue
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_struct
id|usb_request
op_star
id|req
comma
r_int
id|gfp_flags
)paren
(brace
r_return
id|ep-&gt;ops-&gt;queue
(paren
id|ep
comma
id|req
comma
id|gfp_flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_dequeue - dequeues (cancels, unlinks) an I/O request from an endpoint&n; * @ep:the endpoint associated with the request&n; * @req:the request being canceled&n; *&n; * if the request is still active on the endpoint, it is dequeued and its&n; * completion routine is called (with status -ECONNRESET); else a negative&n; * error code is returned.&n; *&n; * note that some hardware can&squot;t clear out write fifos (to unlink the request&n; * at the head of the queue) except as part of disconnecting from usb.  such&n; * restrictions prevent drivers from supporting configuration changes,&n; * even to configuration zero (a &quot;chapter 9&quot; requirement).&n; */
DECL|function|usb_ep_dequeue
r_static
r_inline
r_int
id|usb_ep_dequeue
(paren
r_struct
id|usb_ep
op_star
id|ep
comma
r_struct
id|usb_request
op_star
id|req
)paren
(brace
r_return
id|ep-&gt;ops-&gt;dequeue
(paren
id|ep
comma
id|req
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_set_halt - sets the endpoint halt feature.&n; * @ep: the non-isochronous endpoint being stalled&n; *&n; * Use this to stall an endpoint, perhaps as an error report.&n; * Except for control endpoints,&n; * the endpoint stays halted (will not stream any data) until the host&n; * clears this feature; drivers may need to empty the endpoint&squot;s request&n; * queue first, to make sure no inappropriate transfers happen.&n; *&n; * Returns zero, or a negative error code.  On success, this call sets&n; * underlying hardware state that blocks data transfers.&n; */
r_static
r_inline
r_int
DECL|function|usb_ep_set_halt
id|usb_ep_set_halt
(paren
r_struct
id|usb_ep
op_star
id|ep
)paren
(brace
r_return
id|ep-&gt;ops-&gt;set_halt
(paren
id|ep
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_clear_halt - clears endpoint halt, and resets toggle&n; * @ep:the bulk or interrupt endpoint being reset&n; *&n; * use this when responding to the standard usb &quot;set interface&quot; request,&n; * for endpoints that aren&squot;t reconfigured, after clearing any other state&n; * in the endpoint&squot;s i/o queue.&n; *&n; * returns zero, or a negative error code.  on success, this call clears&n; * the underlying hardware state reflecting endpoint halt and data toggle.&n; */
r_static
r_inline
r_int
DECL|function|usb_ep_clear_halt
id|usb_ep_clear_halt
(paren
r_struct
id|usb_ep
op_star
id|ep
)paren
(brace
r_return
id|ep-&gt;ops-&gt;set_halt
(paren
id|ep
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_fifo_status - returns number of bytes in fifo, or error&n; * @ep: the endpoint whose fifo status is being checked.&n; *&n; * FIFO endpoints may have &quot;unclaimed data&quot; in them in certain cases,&n; * such as after aborted transfers.  Hosts may not have collected all&n; * the IN data written by the gadget driver, as reported by a request&n; * completion.  The gadget driver may not have collected all the data&n; * written OUT to it by the host.  Drivers that need precise handling for&n; * fault reporting or recovery may need to use this call.&n; *&n; * This returns the number of such bytes in the fifo, or a negative&n; * errno if the endpoint doesn&squot;t use a FIFO or doesn&squot;t support such&n; * precise handling.&n; */
r_static
r_inline
r_int
DECL|function|usb_ep_fifo_status
id|usb_ep_fifo_status
(paren
r_struct
id|usb_ep
op_star
id|ep
)paren
(brace
r_if
c_cond
(paren
id|ep-&gt;ops-&gt;fifo_status
)paren
r_return
id|ep-&gt;ops-&gt;fifo_status
(paren
id|ep
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_ep_fifo_flush - flushes contents of a fifo&n; * @ep: the endpoint whose fifo is being flushed.&n; *&n; * This call may be used to flush the &quot;unclaimed data&quot; that may exist in&n; * an endpoint fifo after abnormal transaction terminations.  The call&n; * must never be used except when endpoint is not being used for any&n; * protocol translation.&n; */
r_static
r_inline
r_void
DECL|function|usb_ep_fifo_flush
id|usb_ep_fifo_flush
(paren
r_struct
id|usb_ep
op_star
id|ep
)paren
(brace
r_if
c_cond
(paren
id|ep-&gt;ops-&gt;fifo_flush
)paren
id|ep-&gt;ops-&gt;fifo_flush
(paren
id|ep
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
r_struct
id|usb_gadget
suffix:semicolon
multiline_comment|/* the rest of the api to the controller hardware: device operations,&n; * which don&squot;t involve endpoints (or i/o).&n; */
DECL|struct|usb_gadget_ops
r_struct
id|usb_gadget_ops
(brace
DECL|member|get_frame
r_int
(paren
op_star
id|get_frame
)paren
(paren
r_struct
id|usb_gadget
op_star
)paren
suffix:semicolon
DECL|member|wakeup
r_int
(paren
op_star
id|wakeup
)paren
(paren
r_struct
id|usb_gadget
op_star
)paren
suffix:semicolon
DECL|member|set_selfpowered
r_int
(paren
op_star
id|set_selfpowered
)paren
(paren
r_struct
id|usb_gadget
op_star
comma
r_int
id|value
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|usb_gadget
op_star
comma
r_int
id|code
comma
r_int
r_int
id|param
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct usb_gadget - represents a usb slave device&n; * @ep0: Endpoint zero, used when reading or writing responses to&n; * &t;driver setup() requests&n; * @ep_list: List of other endpoints supported by the device.&n; * @speed: Speed of current connection to USB host.&n; * @name: Identifies the controller hardware type.  Used in diagnostics&n; * &t;and sometimes configuration.&n; *&n; * Gadgets have a mostly-portable &quot;gadget driver&quot; implementing device&n; * functions, handling all usb configurations and interfaces.  They&n; * also have a hardware-specific driver (accessed through ops vectors),&n; * which insulates the gadget driver from hardware details and packages&n; * the hardware endpoints through generic i/o queues.&n; *&n; * Except for the driver data, all fields in this structure are&n; * read-only to the gadget driver.  That driver data is part of the&n; * &quot;driver model&quot; infrastructure in 2.5 (and later) kernels, and for&n; * earlier systems is grouped in a similar structure that&squot;s not known&n; * to the rest of the kernel.&n; */
DECL|struct|usb_gadget
r_struct
id|usb_gadget
(brace
multiline_comment|/* readonly to gadget driver */
DECL|member|ops
r_const
r_struct
id|usb_gadget_ops
op_star
id|ops
suffix:semicolon
DECL|member|ep0
r_struct
id|usb_ep
op_star
id|ep0
suffix:semicolon
DECL|member|ep_list
r_struct
id|list_head
id|ep_list
suffix:semicolon
multiline_comment|/* of usb_ep */
DECL|member|speed
r_enum
id|usb_device_speed
id|speed
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* use this to allocate dma-coherent buffers or set up&n;&t; * dma mappings.  or print diagnostics, etc.&n;&t; */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|function|set_gadget_data
r_static
r_inline
r_void
id|set_gadget_data
(paren
r_struct
id|usb_gadget
op_star
id|gadget
comma
r_void
op_star
id|data
)paren
(brace
id|dev_set_drvdata
(paren
op_amp
id|gadget-&gt;dev
comma
id|data
)paren
suffix:semicolon
)brace
DECL|function|get_gadget_data
r_static
r_inline
r_void
op_star
id|get_gadget_data
(paren
r_struct
id|usb_gadget
op_star
id|gadget
)paren
(brace
r_return
id|dev_get_drvdata
(paren
op_amp
id|gadget-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/* iterates the non-control endpoints; &squot;tmp&squot; is a struct usb_ep pointer */
DECL|macro|gadget_for_each_ep
mdefine_line|#define gadget_for_each_ep(tmp,gadget) &bslash;&n;&t;list_for_each_entry(tmp, &amp;(gadget)-&gt;ep_list, ep_list)
multiline_comment|/**&n; * usb_gadget_frame_number - returns the current frame number&n; * @gadget: controller that reports the frame number&n; *&n; * Returns the usb frame number, normally eleven bits from a SOF packet,&n; * or negative errno if this device doesn&squot;t support this capability.&n; */
DECL|function|usb_gadget_frame_number
r_static
r_inline
r_int
id|usb_gadget_frame_number
(paren
r_struct
id|usb_gadget
op_star
id|gadget
)paren
(brace
r_return
id|gadget-&gt;ops-&gt;get_frame
(paren
id|gadget
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_gadget_wakeup - tries to wake up the host connected to this gadget&n; * @gadget: controller used to wake up the host&n; *&n; * Returns zero on success, else negative error code if the hardware&n; * doesn&squot;t support such attempts, or its support has not been enabled&n; * by the usb host.  Drivers must return device descriptors that report&n; * their ability to support this, or hosts won&squot;t enable it.&n; */
DECL|function|usb_gadget_wakeup
r_static
r_inline
r_int
id|usb_gadget_wakeup
(paren
r_struct
id|usb_gadget
op_star
id|gadget
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|gadget-&gt;ops-&gt;wakeup
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_return
id|gadget-&gt;ops-&gt;wakeup
(paren
id|gadget
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_gadget_set_selfpowered - sets the device selfpowered feature.&n; * @gadget:the device being declared as self-powered&n; *&n; * this affects the device status reported by the hardware driver&n; * to reflect that it now has a local power supply.&n; *&n; * returns zero on success, else negative errno.&n; */
r_static
r_inline
r_int
DECL|function|usb_gadget_set_selfpowered
id|usb_gadget_set_selfpowered
(paren
r_struct
id|usb_gadget
op_star
id|gadget
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|gadget-&gt;ops-&gt;set_selfpowered
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_return
id|gadget-&gt;ops-&gt;set_selfpowered
(paren
id|gadget
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_gadget_clear_selfpowered - clear the device selfpowered feature.&n; * @gadget:the device being declared as bus-powered&n; *&n; * this affects the device status reported by the hardware driver.&n; * some hardware may not support bus-powered operation, in which&n; * case this feature&squot;s value can never change.&n; *&n; * returns zero on success, else negative errno.&n; */
r_static
r_inline
r_int
DECL|function|usb_gadget_clear_selfpowered
id|usb_gadget_clear_selfpowered
(paren
r_struct
id|usb_gadget
op_star
id|gadget
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|gadget-&gt;ops-&gt;set_selfpowered
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_return
id|gadget-&gt;ops-&gt;set_selfpowered
(paren
id|gadget
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/**&n; * struct usb_gadget_driver - driver for usb &squot;slave&squot; devices&n; * @function: String describing the gadget&squot;s function&n; * @speed: Highest speed the driver handles.&n; * @bind: Invoked when the driver is bound to a gadget, usually&n; * &t;after registering the driver.&n; * &t;At that point, ep0 is fully initialized, and ep_list holds&n; * &t;the currently-available endpoints.&n; * &t;Called in a context that permits sleeping.&n; * @setup: Invoked for ep0 control requests that aren&squot;t handled by&n; * &t;the hardware level driver. Most calls must be handled by&n; * &t;the gadget driver, including descriptor and configuration&n; * &t;management.  The 16 bit members of the setup data are in&n; * &t;cpu order. Called in_interrupt; this may not sleep.  Driver&n; *&t;queues a response to ep0, or returns negative to stall.&n; * @disconnect: Invoked after all transfers have been stopped,&n; * &t;when the host is disconnected.  May be called in_interrupt; this&n; * &t;may not sleep.&n; * @unbind: Invoked when the driver is unbound from a gadget,&n; * &t;usually from rmmod (after a disconnect is reported).&n; * &t;Called in a context that permits sleeping.&n; * @suspend: Invoked on USB suspend.  May be called in_interrupt.&n; * @resume: Invoked on USB resume.  May be called in_interrupt.&n; *&n; * Devices are disabled till a gadget driver successfully bind()s, which&n; * means the driver will handle setup() requests needed to enumerate (and&n; * meet &quot;chapter 9&quot; requirements) then do some useful work.&n; *&n; * Drivers use hardware-specific knowledge to configure the usb hardware.&n; * endpoint addressing is only one of several hardware characteristics that&n; * are in descriptors the ep0 implementation returns from setup() calls.&n; *&n; * Except for ep0 implementation, most driver code shouldn&squot;t need change to&n; * run on top of different usb controllers.  It&squot;ll use endpoints set up by&n; * that ep0 implementation.&n; *&n; * The usb controller driver handles a few standard usb requests.  Those&n; * include set_address, and feature flags for devices, interfaces, and&n; * endpoints (the get_status, set_feature, and clear_feature requests).&n; *&n; * Accordingly, the driver&squot;s setup() callback must always implement all&n; * get_descriptor requests, returning at least a device descriptor and&n; * a configuration descriptor.  Drivers must make sure the endpoint&n; * descriptors match any hardware constraints. Some hardware also constrains&n; * other descriptors. (The pxa250 allows only configurations 1, 2, or 3).&n; *&n; * The driver&squot;s setup() callback must also implement set_configuration,&n; * and should also implement set_interface, get_configuration, and&n; * get_interface.  Setting a configuration (or interface) is where&n; * endpoints should be activated or (config 0) shut down.&n; *&n; * (Note that only the default control endpoint is supported.  Neither&n; * hosts nor devices generally support control traffic except to ep0.)&n; *&n; * Most devices will ignore USB suspend/resume operations, and so will&n; * not provide those callbacks.  However, some may need to change modes&n; * when the host is not longer directing those activities.  For example,&n; * local controls (buttons, dials, etc) may need to be re-enabled since&n; * the (remote) host can&squot;t do that any longer. &n; */
DECL|struct|usb_gadget_driver
r_struct
id|usb_gadget_driver
(brace
DECL|member|function
r_char
op_star
id|function
suffix:semicolon
DECL|member|speed
r_enum
id|usb_device_speed
id|speed
suffix:semicolon
DECL|member|bind
r_int
(paren
op_star
id|bind
)paren
(paren
r_struct
id|usb_gadget
op_star
)paren
suffix:semicolon
DECL|member|unbind
r_void
(paren
op_star
id|unbind
)paren
(paren
r_struct
id|usb_gadget
op_star
)paren
suffix:semicolon
DECL|member|setup
r_int
(paren
op_star
id|setup
)paren
(paren
r_struct
id|usb_gadget
op_star
comma
r_const
r_struct
id|usb_ctrlrequest
op_star
)paren
suffix:semicolon
DECL|member|disconnect
r_void
(paren
op_star
id|disconnect
)paren
(paren
r_struct
id|usb_gadget
op_star
)paren
suffix:semicolon
DECL|member|suspend
r_void
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|usb_gadget
op_star
)paren
suffix:semicolon
DECL|member|resume
r_void
(paren
op_star
id|resume
)paren
(paren
r_struct
id|usb_gadget
op_star
)paren
suffix:semicolon
singleline_comment|// FIXME support safe rmmod
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* driver modules register and unregister, as usual.&n; * these calls must be made in a context that can sleep.&n; *&n; * these will usually be implemented directly by the hardware-dependent&n; * usb bus interface driver, which will only support a single driver.&n; */
multiline_comment|/**&n; * usb_gadget_register_driver - register a gadget driver&n; * @driver:the driver being registered&n; *&n; * Call this in your gadget driver&squot;s module initialization function,&n; * to tell the underlying usb controller driver about your driver.&n; * The driver&squot;s bind() function will be called to bind it to a&n; * gadget.  This function must be called in a context that can sleep.&n; */
r_int
id|usb_gadget_register_driver
(paren
r_struct
id|usb_gadget_driver
op_star
id|driver
)paren
suffix:semicolon
multiline_comment|/**&n; * usb_gadget_unregister_driver - unregister a gadget driver&n; * @driver:the driver being unregistered&n; *&n; * Call this in your gadget driver&squot;s module cleanup function,&n; * to tell the underlying usb controller that your driver is&n; * going away.  If the controller is connected to a USB host,&n; * it will first disconnect().  The driver is also requested&n; * to unbind() and clean up any device state, before this procedure&n; * finally returns.&n; * This function must be called in a context that can sleep.&n; */
r_int
id|usb_gadget_unregister_driver
(paren
r_struct
id|usb_gadget_driver
op_star
id|driver
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* utility to simplify dealing with string descriptors */
multiline_comment|/**&n; * struct usb_string - wraps a C string and its USB id&n; * @id:the (nonzero) ID for this string&n; * @s:the string, in ISO-8859/1 characters&n; *&n; * If you&squot;re using usb_gadget_get_string(), use this to wrap a string&n; * together with its ID.&n; */
DECL|struct|usb_string
r_struct
id|usb_string
(brace
DECL|member|id
id|u8
id|id
suffix:semicolon
DECL|member|s
r_const
r_char
op_star
id|s
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct usb_gadget_strings - a set of USB strings in a given language&n; * @language:identifies the strings&squot; language (0x0409 for en-us)&n; * @strings:array of strings with their ids&n; *&n; * If you&squot;re using usb_gadget_get_string(), use this to wrap all the&n; * strings for a given language.&n; */
DECL|struct|usb_gadget_strings
r_struct
id|usb_gadget_strings
(brace
DECL|member|language
id|u16
id|language
suffix:semicolon
multiline_comment|/* 0x0409 for en-us */
DECL|member|strings
r_struct
id|usb_string
op_star
id|strings
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* put descriptor for string with that id into buf (buflen &gt;= 256) */
r_int
id|usb_gadget_get_string
(paren
r_struct
id|usb_gadget_strings
op_star
id|table
comma
r_int
id|id
comma
id|u8
op_star
id|buf
)paren
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif&t;/* __LINUX_USB_GADGET_H */
eof
