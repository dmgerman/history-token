multiline_comment|/*&n; * Common routines for a handful of drivers.&n; * Unrelated to CF/SM - just USB stuff.&n; *&n; * This is mostly a thin layer on top of transport.c.&n; * It converts routines that return values like -EPIPE&n; * into routines that return USB_STOR_TRANSPORT_ABORTED etc.&n; *&n; * There is also some debug printing here.&n; */
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;raw_bulk.h&quot;
macro_line|#ifdef CONFIG_USB_STORAGE_DEBUG
DECL|macro|DEBUG_PRCT
mdefine_line|#define DEBUG_PRCT 12
macro_line|#else
DECL|macro|DEBUG_PRCT
mdefine_line|#define DEBUG_PRCT 0
macro_line|#endif
multiline_comment|/*&n; * Send a control message and wait for the response.&n; *&n; * us - the pointer to the us_data structure for the device to use&n; *&n; * request - the URB Setup Packet&squot;s first 6 bytes. The first byte always&n; *  corresponds to the request type, and the second byte always corresponds&n; *  to the request.  The other 4 bytes do not correspond to value and index,&n; *  since they are used in a custom way by the SCM protocol.&n; *&n; * xfer_data - a buffer from which to get, or to which to store, any data&n; *  that gets send or received, respectively, with the URB. Even though&n; *  it looks like we allocate a buffer in this code for the data, xfer_data&n; *  must contain enough allocated space.&n; *&n; * xfer_len - the number of bytes to send or receive with the URB.&n; *&n; */
r_int
DECL|function|usb_storage_send_control
id|usb_storage_send_control
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
id|pipe
comma
r_int
r_char
id|request
comma
r_int
r_char
id|requesttype
comma
r_int
r_int
id|value
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|xfer_data
comma
r_int
r_int
id|xfer_len
)paren
(brace
r_int
id|result
suffix:semicolon
singleline_comment|// Send the URB to the device and wait for a response.
multiline_comment|/* Why are request and request type reversed in this call? */
id|result
op_assign
id|usb_stor_control_msg
c_func
(paren
id|us
comma
id|pipe
comma
id|request
comma
id|requesttype
comma
id|value
comma
id|index
comma
id|xfer_data
comma
id|xfer_len
)paren
suffix:semicolon
multiline_comment|/* did we abort this command? */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|us-&gt;sm_state
)paren
op_eq
id|US_STATE_ABORTING
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;usb_stor_send_control(): transfer aborted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_ABORTED
suffix:semicolon
)brace
singleline_comment|// Check the return code for the command.
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
multiline_comment|/* a stall indicates a protocol error */
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EPIPE
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;-- Stall on control pipe&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
multiline_comment|/* Uh oh... serious problem here */
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
r_int
DECL|function|usb_storage_raw_bulk
id|usb_storage_raw_bulk
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
id|direction
comma
r_int
r_char
op_star
id|data
comma
r_int
r_int
id|len
comma
r_int
r_int
op_star
id|act_len
)paren
(brace
r_int
id|result
suffix:semicolon
r_int
id|pipe
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|SCSI_DATA_READ
)paren
id|pipe
op_assign
id|usb_rcvbulkpipe
c_func
(paren
id|us-&gt;pusb_dev
comma
id|us-&gt;ep_in
)paren
suffix:semicolon
r_else
id|pipe
op_assign
id|usb_sndbulkpipe
c_func
(paren
id|us-&gt;pusb_dev
comma
id|us-&gt;ep_out
)paren
suffix:semicolon
id|result
op_assign
id|usb_stor_bulk_msg
c_func
(paren
id|us
comma
id|data
comma
id|pipe
comma
id|len
comma
id|act_len
)paren
suffix:semicolon
multiline_comment|/* if we stall, we need to clear it before we go on */
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EPIPE
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;EPIPE: clearing endpoint halt for&quot;
l_string|&quot; pipe 0x%x, stalled at %d bytes&bslash;n&quot;
comma
id|pipe
comma
op_star
id|act_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_stor_clear_halt
c_func
(paren
id|us
comma
id|pipe
)paren
OL
l_int|0
)paren
r_return
id|USB_STOR_XFER_ERROR
suffix:semicolon
r_return
id|USB_STOR_XFER_STALLED
suffix:semicolon
)brace
multiline_comment|/* did we abort this command? */
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|us-&gt;sm_state
)paren
op_eq
id|US_STATE_ABORTING
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;usb_storage_raw_bulk(): transfer aborted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_XFER_ABORTED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
)paren
(brace
multiline_comment|/* NAK - that means we&squot;ve retried a few times already */
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ETIMEDOUT
)paren
id|US_DEBUGP
c_func
(paren
l_string|&quot;raw_bulk(): device NAKed&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EOVERFLOW
)paren
id|US_DEBUGP
c_func
(paren
l_string|&quot;raw_bulk(): babble/overflow&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ECONNRESET
)paren
id|US_DEBUGP
c_func
(paren
l_string|&quot;raw_bulk(): asynchronous reset&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|result
op_ne
op_minus
id|EPIPE
)paren
id|US_DEBUGP
c_func
(paren
l_string|&quot;raw_bulk(): unknown error %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_return
id|USB_STOR_XFER_ERROR
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|act_len
op_ne
id|len
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;Warning: Transferred only %d of %d bytes&bslash;n&quot;
comma
op_star
id|act_len
comma
id|len
)paren
suffix:semicolon
r_return
id|USB_STOR_XFER_SHORT
suffix:semicolon
)brace
macro_line|#if 0
id|US_DEBUGP
c_func
(paren
l_string|&quot;raw_bulk(): Transferred %s %d of %d bytes&bslash;n&quot;
comma
(paren
id|direction
op_eq
id|SCSI_DATA_READ
)paren
ques
c_cond
l_string|&quot;in&quot;
suffix:colon
l_string|&quot;out&quot;
comma
op_star
id|act_len
comma
id|len
)paren
suffix:semicolon
macro_line|#endif
r_return
id|USB_STOR_XFER_GOOD
suffix:semicolon
)brace
r_int
DECL|function|usb_storage_bulk_transport
id|usb_storage_bulk_transport
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
id|direction
comma
r_int
r_char
op_star
id|data
comma
r_int
r_int
id|len
comma
r_int
id|use_sg
)paren
(brace
r_int
id|result
op_assign
id|USB_STOR_XFER_ERROR
suffix:semicolon
r_int
id|transferred
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
r_int
r_int
id|act_len
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_return
id|USB_STOR_XFER_GOOD
suffix:semicolon
macro_line|#if DEBUG_PRCT
r_if
c_cond
(paren
id|direction
op_eq
id|SCSI_DATA_WRITE
op_logical_and
op_logical_neg
id|use_sg
)paren
(brace
r_char
id|string
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Debug-print the first N bytes of the write transfer */
id|strcpy
c_func
(paren
id|string
comma
l_string|&quot;wr: &quot;
)paren
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
id|len
op_logical_and
id|i
OL
id|DEBUG_PRCT
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|string
op_plus
id|strlen
c_func
(paren
id|string
)paren
comma
l_string|&quot;%02X &quot;
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|16
)paren
op_eq
l_int|15
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|string
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|string
comma
l_string|&quot;wr: &quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|16
)paren
op_ne
l_int|0
)paren
id|US_DEBUGP
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|string
)paren
suffix:semicolon
)brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;SCM data %s transfer %d sg buffers %d&bslash;n&quot;
comma
(paren
id|direction
op_eq
id|SCSI_DATA_READ
)paren
ques
c_cond
l_string|&quot;in&quot;
suffix:colon
l_string|&quot;out&quot;
comma
id|len
comma
id|use_sg
)paren
suffix:semicolon
macro_line|#endif /* DEBUG_PRCT */
r_if
c_cond
(paren
op_logical_neg
id|use_sg
)paren
id|result
op_assign
id|usb_storage_raw_bulk
c_func
(paren
id|us
comma
id|direction
comma
id|data
comma
id|len
comma
op_amp
id|act_len
)paren
suffix:semicolon
r_else
(brace
id|sg
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|data
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
id|use_sg
op_logical_and
id|transferred
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
op_star
id|buf
suffix:semicolon
r_int
r_int
id|length
suffix:semicolon
id|buf
op_assign
id|sg_address
c_func
(paren
id|sg
(braket
id|i
)braket
)paren
suffix:semicolon
id|length
op_assign
id|len
op_minus
id|transferred
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|sg
(braket
id|i
)braket
dot
id|length
)paren
id|length
op_assign
id|sg
(braket
id|i
)braket
dot
id|length
suffix:semicolon
id|result
op_assign
id|usb_storage_raw_bulk
c_func
(paren
id|us
comma
id|direction
comma
id|buf
comma
id|length
comma
op_amp
id|act_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|USB_STOR_XFER_GOOD
)paren
r_break
suffix:semicolon
id|transferred
op_add_assign
id|length
suffix:semicolon
)brace
)brace
macro_line|#if DEBUG_PRCT
r_if
c_cond
(paren
id|direction
op_eq
id|SCSI_DATA_READ
op_logical_and
op_logical_neg
id|use_sg
)paren
(brace
r_char
id|string
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Debug-print the first N bytes of the read transfer */
id|strcpy
c_func
(paren
id|string
comma
l_string|&quot;rd: &quot;
)paren
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
id|len
op_logical_and
id|i
OL
id|act_len
op_logical_and
id|i
OL
id|DEBUG_PRCT
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|string
op_plus
id|strlen
c_func
(paren
id|string
)paren
comma
l_string|&quot;%02X &quot;
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|16
)paren
op_eq
l_int|15
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|string
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|string
comma
l_string|&quot;rd: &quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|16
)paren
op_ne
l_int|0
)paren
id|US_DEBUGP
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|string
)paren
suffix:semicolon
)brace
macro_line|#endif /* DEBUG_PRCT */
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * The routines below convert scatter-gather to single buffer.&n; * Some drivers claim this is necessary.&n; * Nothing is done when use_sg is zero.&n; */
multiline_comment|/*&n; * Copy from scatter-gather buffer into a newly allocated single buffer,&n; * starting at a given index and offset.&n; * When done, update index and offset.&n; * Return a pointer to the single buffer.&n; */
r_int
r_char
op_star
DECL|function|us_copy_from_sgbuf
id|us_copy_from_sgbuf
c_func
(paren
r_int
r_char
op_star
id|content
comma
r_int
id|len
comma
r_int
op_star
id|index
comma
r_int
op_star
id|offset
comma
r_int
id|use_sg
)paren
(brace
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
r_int
id|transferred
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|use_sg
)paren
r_return
id|content
suffix:semicolon
id|sg
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|content
suffix:semicolon
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|transferred
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
op_star
id|index
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|use_sg
op_logical_and
id|transferred
OL
id|len
)paren
(brace
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_int
r_int
id|length
comma
id|room
suffix:semicolon
id|ptr
op_assign
id|sg_address
c_func
(paren
id|sg
(braket
id|i
)braket
)paren
op_plus
op_star
id|offset
suffix:semicolon
id|room
op_assign
id|sg
(braket
id|i
)braket
dot
id|length
op_minus
op_star
id|offset
suffix:semicolon
id|length
op_assign
id|len
op_minus
id|transferred
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|room
)paren
id|length
op_assign
id|room
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
op_plus
id|transferred
comma
id|ptr
comma
id|length
)paren
suffix:semicolon
id|transferred
op_add_assign
id|length
suffix:semicolon
op_star
id|offset
op_add_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|length
op_eq
id|room
)paren
(brace
id|i
op_increment
suffix:semicolon
op_star
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
)brace
op_star
id|index
op_assign
id|i
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
r_int
r_char
op_star
DECL|function|us_copy_from_sgbuf_all
id|us_copy_from_sgbuf_all
c_func
(paren
r_int
r_char
op_star
id|content
comma
r_int
id|len
comma
r_int
id|use_sg
)paren
(brace
r_int
id|index
comma
id|offset
suffix:semicolon
id|index
op_assign
id|offset
op_assign
l_int|0
suffix:semicolon
r_return
id|us_copy_from_sgbuf
c_func
(paren
id|content
comma
id|len
comma
op_amp
id|index
comma
op_amp
id|offset
comma
id|use_sg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy from a single buffer into a scatter-gather buffer,&n; * starting at a given index and offset.&n; * When done, update index and offset.&n; */
r_void
DECL|function|us_copy_to_sgbuf
id|us_copy_to_sgbuf
c_func
(paren
r_int
r_char
op_star
id|buffer
comma
r_int
id|buflen
comma
r_void
op_star
id|content
comma
r_int
op_star
id|index
comma
r_int
op_star
id|offset
comma
r_int
id|use_sg
)paren
(brace
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
r_int
id|i
comma
id|transferred
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|use_sg
)paren
r_return
suffix:semicolon
id|transferred
op_assign
l_int|0
suffix:semicolon
id|sg
op_assign
id|content
suffix:semicolon
id|i
op_assign
op_star
id|index
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|use_sg
op_logical_and
id|transferred
OL
id|buflen
)paren
(brace
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_int
r_int
id|length
comma
id|room
suffix:semicolon
id|ptr
op_assign
id|sg_address
c_func
(paren
id|sg
(braket
id|i
)braket
)paren
op_plus
op_star
id|offset
suffix:semicolon
id|room
op_assign
id|sg
(braket
id|i
)braket
dot
id|length
op_minus
op_star
id|offset
suffix:semicolon
id|length
op_assign
id|buflen
op_minus
id|transferred
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|room
)paren
id|length
op_assign
id|room
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
id|buffer
op_plus
id|transferred
comma
id|length
)paren
suffix:semicolon
id|transferred
op_add_assign
id|sg
(braket
id|i
)braket
dot
id|length
suffix:semicolon
op_star
id|offset
op_add_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|length
op_eq
id|room
)paren
(brace
id|i
op_increment
suffix:semicolon
op_star
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
)brace
op_star
id|index
op_assign
id|i
suffix:semicolon
)brace
r_void
DECL|function|us_copy_to_sgbuf_all
id|us_copy_to_sgbuf_all
c_func
(paren
r_int
r_char
op_star
id|buffer
comma
r_int
id|buflen
comma
r_void
op_star
id|content
comma
r_int
id|use_sg
)paren
(brace
r_int
id|index
comma
id|offset
suffix:semicolon
id|index
op_assign
id|offset
op_assign
l_int|0
suffix:semicolon
id|us_copy_to_sgbuf
c_func
(paren
id|buffer
comma
id|buflen
comma
id|content
comma
op_amp
id|index
comma
op_amp
id|offset
comma
id|use_sg
)paren
suffix:semicolon
)brace
eof
