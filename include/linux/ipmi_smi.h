multiline_comment|/*&n; * ipmi_smi.h&n; *&n; * MontaVista IPMI system management interface&n; *&n; * Author: MontaVista Software, Inc.&n; *         Corey Minyard &lt;minyard@mvista.com&gt;&n; *         source@mvista.com&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __LINUX_IPMI_SMI_H
DECL|macro|__LINUX_IPMI_SMI_H
mdefine_line|#define __LINUX_IPMI_SMI_H
macro_line|#include &lt;linux/ipmi_msgdefs.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/* This files describes the interface for IPMI system management interface&n;   drivers to bind into the IPMI message handler. */
multiline_comment|/* Structure for the low-level drivers. */
DECL|typedef|ipmi_smi_t
r_typedef
r_struct
id|ipmi_smi
op_star
id|ipmi_smi_t
suffix:semicolon
multiline_comment|/*&n; * Messages to/from the lower layer.  The smi interface will take one&n; * of these to send. After the send has occurred and a response has&n; * been received, it will report this same data structure back up to&n; * the upper layer.  If an error occurs, it should fill in the&n; * response with an error code in the completion code location. When&n; * asynchronous data is received, one of these is allocated, the&n; * data_size is set to zero and the response holds the data from the&n; * get message or get event command that the interface initiated.&n; * Note that it is the interfaces responsibility to detect&n; * asynchronous data and messages and request them from the&n; * interface.&n; */
DECL|struct|ipmi_smi_msg
r_struct
id|ipmi_smi_msg
(brace
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
DECL|member|msgid
r_int
id|msgid
suffix:semicolon
DECL|member|user_data
r_void
op_star
id|user_data
suffix:semicolon
DECL|member|data_size
r_int
id|data_size
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
id|IPMI_MAX_MSG_LENGTH
)braket
suffix:semicolon
DECL|member|rsp_size
r_int
id|rsp_size
suffix:semicolon
DECL|member|rsp
r_int
r_char
id|rsp
(braket
id|IPMI_MAX_MSG_LENGTH
)braket
suffix:semicolon
multiline_comment|/* Will be called when the system is done with the message&n;           (presumably to free it). */
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|ipmi_smi_msg
op_star
id|msg
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipmi_smi_handlers
r_struct
id|ipmi_smi_handlers
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* Called to enqueue an SMI message to be sent.  This&n;&t;   operation is not allowed to fail.  If an error occurs, it&n;&t;   should report back the error in a received message.  It may&n;&t;   do this in the current call context, since no write locks&n;&t;   are held when this is run.  If the priority is &gt; 0, the&n;&t;   message will go into a high-priority queue and be sent&n;&t;   first.  Otherwise, it goes into a normal-priority queue. */
DECL|member|sender
r_void
(paren
op_star
id|sender
)paren
(paren
r_void
op_star
id|send_info
comma
r_struct
id|ipmi_smi_msg
op_star
id|msg
comma
r_int
id|priority
)paren
suffix:semicolon
multiline_comment|/* Called by the upper layer to request that we try to get&n;&t;   events from the BMC we are attached to. */
DECL|member|request_events
r_void
(paren
op_star
id|request_events
)paren
(paren
r_void
op_star
id|send_info
)paren
suffix:semicolon
multiline_comment|/* Called when the interface should go into &quot;run to&n;&t;   completion&quot; mode.  If this call sets the value to true, the&n;&t;   interface should make sure that all messages are flushed&n;&t;   out and that none are pending, and any new requests are run&n;&t;   to completion immediately. */
DECL|member|set_run_to_completion
r_void
(paren
op_star
id|set_run_to_completion
)paren
(paren
r_void
op_star
id|send_info
comma
r_int
id|run_to_completion
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Add a low-level interface to the IPMI driver. */
r_int
id|ipmi_register_smi
c_func
(paren
r_struct
id|ipmi_smi_handlers
op_star
id|handlers
comma
r_void
op_star
id|send_info
comma
r_int
r_char
id|version_major
comma
r_int
r_char
id|version_minor
comma
id|ipmi_smi_t
op_star
id|intf
)paren
suffix:semicolon
multiline_comment|/*&n; * Remove a low-level interface from the IPMI driver.  This will&n; * return an error if the interface is still in use by a user.&n; */
r_int
id|ipmi_unregister_smi
c_func
(paren
id|ipmi_smi_t
id|intf
)paren
suffix:semicolon
multiline_comment|/*&n; * The lower layer reports received messages through this interface.&n; * The data_size should be zero if this is an asyncronous message.  If&n; * the lower layer gets an error sending a message, it should format&n; * an error response in the message response.&n; */
r_void
id|ipmi_smi_msg_received
c_func
(paren
id|ipmi_smi_t
id|intf
comma
r_struct
id|ipmi_smi_msg
op_star
id|msg
)paren
suffix:semicolon
multiline_comment|/* The lower layer received a watchdog pre-timeout on interface. */
r_void
id|ipmi_smi_watchdog_pretimeout
c_func
(paren
id|ipmi_smi_t
id|intf
)paren
suffix:semicolon
r_struct
id|ipmi_smi_msg
op_star
id|ipmi_alloc_smi_msg
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|ipmi_free_smi_msg
r_static
r_inline
r_void
id|ipmi_free_smi_msg
c_func
(paren
r_struct
id|ipmi_smi_msg
op_star
id|msg
)paren
(brace
id|msg
op_member_access_from_pointer
id|done
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
multiline_comment|/* Allow the lower layer to add things to the proc filesystem&n;   directory for this interface.  Note that the entry will&n;   automatically be dstroyed when the interface is destroyed. */
r_int
id|ipmi_smi_add_proc_entry
c_func
(paren
id|ipmi_smi_t
id|smi
comma
r_char
op_star
id|name
comma
id|read_proc_t
op_star
id|read_proc
comma
id|write_proc_t
op_star
id|write_proc
comma
r_void
op_star
id|data
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
macro_line|#endif /* __LINUX_IPMI_SMI_H */
eof
