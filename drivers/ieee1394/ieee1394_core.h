macro_line|#ifndef _IEEE1394_CORE_H
DECL|macro|_IEEE1394_CORE_H
mdefine_line|#define _IEEE1394_CORE_H
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;hosts.h&quot;
DECL|struct|hpsb_packet
r_struct
id|hpsb_packet
(brace
multiline_comment|/* This struct is basically read-only for hosts with the exception of&n;         * the data buffer contents and xnext - see below. */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* This can be used for host driver internal linking. */
DECL|member|xnext
r_struct
id|hpsb_packet
op_star
id|xnext
suffix:semicolon
DECL|member|node_id
id|nodeid_t
id|node_id
suffix:semicolon
multiline_comment|/* Async and Iso types should be clear, raw means send-as-is, do not&n;         * CRC!  Byte swapping shall still be done in this case. */
DECL|enumerator|hpsb_async
DECL|enumerator|hpsb_iso
DECL|enumerator|hpsb_raw
DECL|member|type
r_enum
(brace
id|hpsb_async
comma
id|hpsb_iso
comma
id|hpsb_raw
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|type
suffix:semicolon
multiline_comment|/* Okay, this is core internal and a no care for hosts.&n;         * queued   = queued for sending&n;         * pending  = sent, waiting for response&n;         * complete = processing completed, successful or not&n;         * incoming = incoming packet&n;         */
r_enum
(brace
DECL|enumerator|hpsb_unused
DECL|enumerator|hpsb_queued
DECL|enumerator|hpsb_pending
DECL|enumerator|hpsb_complete
DECL|enumerator|hpsb_incoming
id|hpsb_unused
comma
id|hpsb_queued
comma
id|hpsb_pending
comma
id|hpsb_complete
comma
id|hpsb_incoming
DECL|member|state
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|state
suffix:semicolon
multiline_comment|/* These are core internal. */
DECL|member|tlabel
r_char
id|tlabel
suffix:semicolon
DECL|member|ack_code
r_char
id|ack_code
suffix:semicolon
DECL|member|tcode
r_char
id|tcode
suffix:semicolon
DECL|member|expect_response
r_int
id|expect_response
suffix:colon
l_int|1
suffix:semicolon
DECL|member|no_waiter
r_int
id|no_waiter
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data big endianness flag - may vary from request to request.  The&n;         * header is always in machine byte order.&n;         * Not really used currently.  */
DECL|member|data_be
r_int
id|data_be
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Speed to transmit with: 0 = 100Mbps, 1 = 200Mbps, 2 = 400Mbps */
DECL|member|speed_code
r_int
id|speed_code
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/*&n;         * *header and *data are guaranteed to be 32-bit DMAable and may be&n;         * overwritten to allow in-place byte swapping.  Neither of these is&n;         * CRCed (the sizes also don&squot;t include CRC), but contain space for at&n;         * least one additional quadlet to allow in-place CRCing.  The memory is&n;         * also guaranteed to be DMA mappable.&n;         */
DECL|member|header
id|quadlet_t
op_star
id|header
suffix:semicolon
DECL|member|data
id|quadlet_t
op_star
id|data
suffix:semicolon
DECL|member|header_size
r_int
id|header_size
suffix:semicolon
DECL|member|data_size
r_int
id|data_size
suffix:semicolon
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|generation
r_int
r_int
id|generation
suffix:semicolon
multiline_comment|/* Very core internal, don&squot;t care. */
DECL|member|state_change
r_struct
id|semaphore
id|state_change
suffix:semicolon
DECL|member|complete_tq
id|task_queue
id|complete_tq
suffix:semicolon
multiline_comment|/* Store jiffies for implementing bus timeouts. */
DECL|member|sendtime
r_int
r_int
id|sendtime
suffix:semicolon
DECL|member|embedded_header
id|quadlet_t
id|embedded_header
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
r_void
id|abort_timedouts
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
r_void
id|abort_requests
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
r_struct
id|hpsb_packet
op_star
id|alloc_hpsb_packet
c_func
(paren
r_int
id|data_size
)paren
suffix:semicolon
r_void
id|free_hpsb_packet
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
)paren
suffix:semicolon
multiline_comment|/*&n; * Generation counter for the complete 1394 subsystem.  Generation gets&n; * incremented on every change in the subsystem (e.g. bus reset).&n; *&n; * Use the functions, not the variable.&n; */
macro_line|#include &lt;asm/atomic.h&gt;
DECL|function|get_hpsb_generation
r_static
r_inline
r_int
r_int
id|get_hpsb_generation
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_return
id|atomic_read
c_func
(paren
op_amp
id|host-&gt;generation
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Queue packet for transmitting, return 0 for failure.&n; */
r_int
id|hpsb_send_packet
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
)paren
suffix:semicolon
multiline_comment|/* Initiate bus reset on the given host.  Returns 1 if bus reset already in&n; * progress, 0 otherwise. */
r_int
id|hpsb_reset_bus
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|type
)paren
suffix:semicolon
multiline_comment|/*&n; * The following functions are exported for host driver module usage.  All of&n; * them are safe to use in interrupt contexts, although some are quite&n; * complicated so you may want to run them in bottom halves instead of calling&n; * them directly.&n; */
multiline_comment|/* Notify a bus reset to the core.  Returns 1 if bus reset already in progress,&n; * 0 otherwise. */
r_int
id|hpsb_bus_reset
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
multiline_comment|/*&n; * Hand over received selfid packet to the core.  Complement check (second&n; * quadlet is complement of first) is expected to be done and succesful.&n; */
r_void
id|hpsb_selfid_received
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|quadlet_t
id|sid
)paren
suffix:semicolon
multiline_comment|/* &n; * Notify completion of SelfID stage to the core and report new physical ID&n; * and whether host is root now.&n; */
r_void
id|hpsb_selfid_complete
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|phyid
comma
r_int
id|isroot
)paren
suffix:semicolon
multiline_comment|/*&n; * Notify core of sending a packet.  Ackcode is the ack code returned for async&n; * transmits or ACKX_SEND_ERROR if the transmission failed completely; ACKX_NONE&n; * for other cases (internal errors that don&squot;t justify a panic).  Safe to call&n; * from within a transmit packet routine.&n; */
r_void
id|hpsb_packet_sent
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_struct
id|hpsb_packet
op_star
id|packet
comma
r_int
id|ackcode
)paren
suffix:semicolon
multiline_comment|/*&n; * Hand over received packet to the core.  The contents of data are expected to&n; * be the full packet but with the CRCs left out (data block follows header&n; * immediately), with the header (i.e. the first four quadlets) in machine byte&n; * order and the data block in big endian.  *data can be safely overwritten&n; * after this call.&n; *&n; * If the packet is a write request, write_acked is to be set to true if it was&n; * ack_complete&squot;d already, false otherwise.  This arg is ignored for any other&n; * packet type.&n; */
r_void
id|hpsb_packet_received
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|quadlet_t
op_star
id|data
comma
r_int
id|size
comma
r_int
id|write_acked
)paren
suffix:semicolon
multiline_comment|/*&n; * CHARACTER DEVICE DISPATCHING&n; *&n; * All ieee1394 character device drivers share the same major number&n; * (major 171).  The 256 minor numbers are allocated to the various&n; * task-specific interfaces (raw1394, video1394, dv1394, etc) in&n; * blocks of 16.&n; *&n; * The core ieee1394.o modules handles the initial open() for all&n; * character devices on major 171; it then dispatches to the&n; * appropriate task-specific driver.&n; *&n; * Minor device number block allocations:&n; *&n; * Block 0  (  0- 15)  raw1394&n; * Block 1  ( 16- 31)  video1394&n; * Block 2  ( 32- 47)  dv1394&n; *&n; * Blocks 3-14 free for future allocation&n; *&n; * Block 15 (240-255)  reserved for drivers under development, etc.&n; */
DECL|macro|IEEE1394_MAJOR
mdefine_line|#define IEEE1394_MAJOR               171
DECL|macro|IEEE1394_MINOR_BLOCK_RAW1394
mdefine_line|#define IEEE1394_MINOR_BLOCK_RAW1394       0
DECL|macro|IEEE1394_MINOR_BLOCK_VIDEO1394
mdefine_line|#define IEEE1394_MINOR_BLOCK_VIDEO1394     1
DECL|macro|IEEE1394_MINOR_BLOCK_DV1394
mdefine_line|#define IEEE1394_MINOR_BLOCK_DV1394        2
DECL|macro|IEEE1394_MINOR_BLOCK_EXPERIMENTAL
mdefine_line|#define IEEE1394_MINOR_BLOCK_EXPERIMENTAL 15
multiline_comment|/* return the index (within a minor number block) of a file */
DECL|function|ieee1394_file_to_instance
r_static
r_inline
r_int
r_char
id|ieee1394_file_to_instance
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
r_char
id|minor
op_assign
id|minor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
multiline_comment|/* return lower 4 bits */
r_return
id|minor
op_amp
l_int|0xF
suffix:semicolon
)brace
multiline_comment|/* &n; * Task-specific drivers should call ieee1394_register_chardev() to&n; * request a block of 16 minor numbers.&n; *&n; * Returns 0 if the request was successful, -EBUSY if the block was&n; * already taken.&n; */
r_int
id|ieee1394_register_chardev
c_func
(paren
r_int
id|blocknum
comma
multiline_comment|/* 0-15 */
r_struct
id|module
op_star
id|module
comma
multiline_comment|/* THIS_MODULE */
r_struct
id|file_operations
op_star
id|file_ops
)paren
suffix:semicolon
multiline_comment|/* release a block of minor numbers */
r_void
id|ieee1394_unregister_chardev
c_func
(paren
r_int
id|blocknum
)paren
suffix:semicolon
multiline_comment|/* the devfs handle for /dev/ieee1394; NULL if devfs is not in use */
r_extern
id|devfs_handle_t
id|ieee1394_devfs_handle
suffix:semicolon
multiline_comment|/* the proc_fs entry for /proc/ieee1394 */
r_extern
r_struct
id|proc_dir_entry
op_star
id|ieee1394_procfs_entry
suffix:semicolon
macro_line|#endif /* _IEEE1394_CORE_H */
eof
