multiline_comment|/*&n; * ipmi.h&n; *&n; * MontaVista IPMI interface&n; *&n; * Author: MontaVista Software, Inc.&n; *         Corey Minyard &lt;minyard@mvista.com&gt;&n; *         source@mvista.com&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __LINUX_IPMI_H
DECL|macro|__LINUX_IPMI_H
mdefine_line|#define __LINUX_IPMI_H
macro_line|#include &lt;linux/ipmi_msgdefs.h&gt;
multiline_comment|/*&n; * This file describes an interface to an IPMI driver.  You have to&n; * have a fairly good understanding of IPMI to use this, so go read&n; * the specs first before actually trying to do anything.&n; *&n; * With that said, this driver provides a multi-user interface to the&n; * IPMI driver, and it allows multiple IPMI physical interfaces below&n; * the driver.  The physical interfaces bind as a lower layer on the&n; * driver.  They appear as interfaces to the application using this&n; * interface.&n; *&n; * Multi-user means that multiple applications may use the driver,&n; * send commands, receive responses, etc.  The driver keeps track of&n; * commands the user sends and tracks the responses.  The responses&n; * will go back to the application that send the command.  If the&n; * response doesn&squot;t come back in time, the driver will return a&n; * timeout error response to the application.  Asynchronous events&n; * from the BMC event queue will go to all users bound to the driver.&n; * The incoming event queue in the BMC will automatically be flushed&n; * if it becomes full and it is queried once a second to see if&n; * anything is in it.  Incoming commands to the driver will get&n; * delivered as commands.&n; *&n; * This driver provides two main interfaces: one for in-kernel&n; * applications and another for userland applications.  The&n; * capabilities are basically the same for both interface, although&n; * the interfaces are somewhat different.  The stuff in the&n; * #ifdef KERNEL below is the in-kernel interface.  The userland&n; * interface is defined later in the file.  */
multiline_comment|/*&n; * This is an overlay for all the address types, so it&squot;s easy to&n; * determine the actual address type.  This is kind of like addresses&n; * work for sockets.&n; */
DECL|macro|IPMI_MAX_ADDR_SIZE
mdefine_line|#define IPMI_MAX_ADDR_SIZE 32
DECL|struct|ipmi_addr
r_struct
id|ipmi_addr
(brace
multiline_comment|/* Try to take these from the &quot;Channel Medium Type&quot; table&n;&t;    in section 6.5 of the IPMI 1.5 manual. */
DECL|member|addr_type
r_int
id|addr_type
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
id|IPMI_MAX_ADDR_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * When the address is not used, the type will be set to this value.&n; * The channel is the BMC&squot;s channel number for the channel (usually&n; * 0), or IPMC_BMC_CHANNEL if communicating directly with the BMC.&n; */
DECL|macro|IPMI_SYSTEM_INTERFACE_ADDR_TYPE
mdefine_line|#define IPMI_SYSTEM_INTERFACE_ADDR_TYPE&t;0x0c
DECL|struct|ipmi_system_interface_addr
r_struct
id|ipmi_system_interface_addr
(brace
DECL|member|addr_type
r_int
id|addr_type
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|lun
r_int
r_char
id|lun
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* An IPMB Address. */
DECL|macro|IPMI_IPMB_ADDR_TYPE
mdefine_line|#define IPMI_IPMB_ADDR_TYPE&t;&t;0x01
multiline_comment|/* Used for broadcast get device id as described in section 17.9 of the&n;   IPMI 1.5 manual. */
DECL|macro|IPMI_IPMB_BROADCAST_ADDR_TYPE
mdefine_line|#define IPMI_IPMB_BROADCAST_ADDR_TYPE&t;0x41
DECL|struct|ipmi_ipmb_addr
r_struct
id|ipmi_ipmb_addr
(brace
DECL|member|addr_type
r_int
id|addr_type
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|slave_addr
r_int
r_char
id|slave_addr
suffix:semicolon
DECL|member|lun
r_int
r_char
id|lun
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * A LAN Address.  This is an address to/from a LAN interface bridged&n; * by the BMC, not an address actually out on the LAN.&n; *&n; * A concious decision was made here to deviate slightly from the IPMI&n; * spec.  We do not use rqSWID and rsSWID like it shows in the&n; * message.  Instead, we use remote_SWID and local_SWID.  This means&n; * that any message (a request or response) from another device will&n; * always have exactly the same address.  If you didn&squot;t do this,&n; * requests and responses from the same device would have different&n; * addresses, and that&squot;s not too cool.&n; *&n; * In this address, the remote_SWID is always the SWID the remote&n; * message came from, or the SWID we are sending the message to.&n; * local_SWID is always our SWID.  Note that having our SWID in the&n; * message is a little weird, but this is required.&n; */
DECL|macro|IPMI_LAN_ADDR_TYPE
mdefine_line|#define IPMI_LAN_ADDR_TYPE&t;&t;0x04
DECL|struct|ipmi_lan_addr
r_struct
id|ipmi_lan_addr
(brace
DECL|member|addr_type
r_int
id|addr_type
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|privilege
r_int
r_char
id|privilege
suffix:semicolon
DECL|member|session_handle
r_int
r_char
id|session_handle
suffix:semicolon
DECL|member|remote_SWID
r_int
r_char
id|remote_SWID
suffix:semicolon
DECL|member|local_SWID
r_int
r_char
id|local_SWID
suffix:semicolon
DECL|member|lun
r_int
r_char
id|lun
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Channel for talking directly with the BMC.  When using this&n; * channel, This is for the system interface address type only.  FIXME&n; * - is this right, or should we use -1?&n; */
DECL|macro|IPMI_BMC_CHANNEL
mdefine_line|#define IPMI_BMC_CHANNEL  0xf
DECL|macro|IPMI_NUM_CHANNELS
mdefine_line|#define IPMI_NUM_CHANNELS 0x10
multiline_comment|/*&n; * A raw IPMI message without any addressing.  This covers both&n; * commands and responses.  The completion code is always the first&n; * byte of data in the response (as the spec shows the messages laid&n; * out).&n; */
DECL|struct|ipmi_msg
r_struct
id|ipmi_msg
(brace
DECL|member|netfn
r_int
r_char
id|netfn
suffix:semicolon
DECL|member|cmd
r_int
r_char
id|cmd
suffix:semicolon
DECL|member|data_len
r_int
r_int
id|data_len
suffix:semicolon
DECL|member|data
r_int
r_char
id|__user
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kernel_ipmi_msg
r_struct
id|kernel_ipmi_msg
(brace
DECL|member|netfn
r_int
r_char
id|netfn
suffix:semicolon
DECL|member|cmd
r_int
r_char
id|cmd
suffix:semicolon
DECL|member|data_len
r_int
r_int
id|data_len
suffix:semicolon
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Various defines that are useful for IPMI applications.&n; */
DECL|macro|IPMI_INVALID_CMD_COMPLETION_CODE
mdefine_line|#define IPMI_INVALID_CMD_COMPLETION_CODE&t;0xC1
DECL|macro|IPMI_TIMEOUT_COMPLETION_CODE
mdefine_line|#define IPMI_TIMEOUT_COMPLETION_CODE&t;&t;0xC3
DECL|macro|IPMI_UNKNOWN_ERR_COMPLETION_CODE
mdefine_line|#define IPMI_UNKNOWN_ERR_COMPLETION_CODE&t;0xff
multiline_comment|/*&n; * Receive types for messages coming from the receive interface.  This&n; * is used for the receive in-kernel interface and in the receive&n; * IOCTL.&n; *&n; * The &quot;IPMI_RESPONSE_RESPNOSE_TYPE&quot; is a little strange sounding, but&n; * it allows you to get the message results when you send a response&n; * message.&n; */
DECL|macro|IPMI_RESPONSE_RECV_TYPE
mdefine_line|#define IPMI_RESPONSE_RECV_TYPE&t;&t;1 /* A response to a command */
DECL|macro|IPMI_ASYNC_EVENT_RECV_TYPE
mdefine_line|#define IPMI_ASYNC_EVENT_RECV_TYPE&t;2 /* Something from the event queue */
DECL|macro|IPMI_CMD_RECV_TYPE
mdefine_line|#define IPMI_CMD_RECV_TYPE&t;&t;3 /* A command from somewhere else */
DECL|macro|IPMI_RESPONSE_RESPONSE_TYPE
mdefine_line|#define IPMI_RESPONSE_RESPONSE_TYPE&t;4 /* The response for&n;&t;&t;&t;&t;&t;      a sent response, giving any&n;&t;&t;&t;&t;&t;      error status for sending the&n;&t;&t;&t;&t;&t;      response.  When you send a&n;&t;&t;&t;&t;&t;      response message, this will&n;&t;&t;&t;&t;&t;      be returned. */
multiline_comment|/* Note that async events and received commands do not have a completion&n;   code as the first byte of the incoming data, unlike a response. */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * The in-kernel interface.&n; */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/* Opaque type for a IPMI message user.  One of these is needed to&n;   send and receive messages. */
DECL|typedef|ipmi_user_t
r_typedef
r_struct
id|ipmi_user
op_star
id|ipmi_user_t
suffix:semicolon
multiline_comment|/*&n; * Stuff coming from the receive interface comes as one of these.&n; * They are allocated, the receiver must free them with&n; * ipmi_free_recv_msg() when done with the message.  The link is not&n; * used after the message is delivered, so the upper layer may use the&n; * link to build a linked list, if it likes.&n; */
DECL|struct|ipmi_recv_msg
r_struct
id|ipmi_recv_msg
(brace
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* The type of message as defined in the &quot;Receive Types&quot;&n;           defines above. */
DECL|member|recv_type
r_int
id|recv_type
suffix:semicolon
DECL|member|user
id|ipmi_user_t
id|user
suffix:semicolon
DECL|member|addr
r_struct
id|ipmi_addr
id|addr
suffix:semicolon
DECL|member|msgid
r_int
id|msgid
suffix:semicolon
DECL|member|msg
r_struct
id|kernel_ipmi_msg
id|msg
suffix:semicolon
multiline_comment|/* The user_msg_data is the data supplied when a message was&n;&t;   sent, if this is a response to a sent message.  If this is&n;&t;   not a response to a sent message, then user_msg_data will&n;&t;   be NULL. */
DECL|member|user_msg_data
r_void
op_star
id|user_msg_data
suffix:semicolon
multiline_comment|/* Call this when done with the message.  It will presumably free&n;&t;   the message and do any other necessary cleanup. */
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|ipmi_recv_msg
op_star
id|msg
)paren
suffix:semicolon
multiline_comment|/* Place-holder for the data, don&squot;t make any assumptions about&n;&t;   the size or existance of this, since it may change. */
DECL|member|msg_data
r_int
r_char
id|msg_data
(braket
id|IPMI_MAX_MSG_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Allocate and free the receive message. */
DECL|function|ipmi_free_recv_msg
r_static
r_inline
r_void
id|ipmi_free_recv_msg
c_func
(paren
r_struct
id|ipmi_recv_msg
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
DECL|struct|ipmi_user_hndl
r_struct
id|ipmi_user_hndl
(brace
multiline_comment|/* Routine type to call when a message needs to be routed to&n;&t;   the upper layer.  This will be called with some locks held,&n;&t;   the only IPMI routines that can be called are ipmi_request&n;&t;   and the alloc/free operations.  The handler_data is the&n;&t;   variable supplied when the receive handler was registered. */
DECL|member|ipmi_recv_hndl
r_void
(paren
op_star
id|ipmi_recv_hndl
)paren
(paren
r_struct
id|ipmi_recv_msg
op_star
id|msg
comma
r_void
op_star
id|user_msg_data
)paren
suffix:semicolon
multiline_comment|/* Called when the interface detects a watchdog pre-timeout.  If&n;&t;   this is NULL, it will be ignored for the user. */
DECL|member|ipmi_watchdog_pretimeout
r_void
(paren
op_star
id|ipmi_watchdog_pretimeout
)paren
(paren
r_void
op_star
id|handler_data
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Create a new user of the IPMI layer on the given interface number. */
r_int
id|ipmi_create_user
c_func
(paren
r_int
r_int
id|if_num
comma
r_struct
id|ipmi_user_hndl
op_star
id|handler
comma
r_void
op_star
id|handler_data
comma
id|ipmi_user_t
op_star
id|user
)paren
suffix:semicolon
multiline_comment|/* Destroy the given user of the IPMI layer.  Note that after this&n;   function returns, the system is guaranteed to not call any&n;   callbacks for the user.  Thus as long as you destroy all the users&n;   before you unload a module, you will be safe.  And if you destroy&n;   the users before you destroy the callback structures, it should be&n;   safe, too. */
r_int
id|ipmi_destroy_user
c_func
(paren
id|ipmi_user_t
id|user
)paren
suffix:semicolon
multiline_comment|/* Get the IPMI version of the BMC we are talking to. */
r_void
id|ipmi_get_version
c_func
(paren
id|ipmi_user_t
id|user
comma
r_int
r_char
op_star
id|major
comma
r_int
r_char
op_star
id|minor
)paren
suffix:semicolon
multiline_comment|/* Set and get the slave address and LUN that we will use for our&n;   source messages.  Note that this affects the interface, not just&n;   this user, so it will affect all users of this interface.  This is&n;   so some initialization code can come in and do the OEM-specific&n;   things it takes to determine your address (if not the BMC) and set&n;   it for everyone else. */
r_void
id|ipmi_set_my_address
c_func
(paren
id|ipmi_user_t
id|user
comma
r_int
r_char
id|address
)paren
suffix:semicolon
r_int
r_char
id|ipmi_get_my_address
c_func
(paren
id|ipmi_user_t
id|user
)paren
suffix:semicolon
r_void
id|ipmi_set_my_LUN
c_func
(paren
id|ipmi_user_t
id|user
comma
r_int
r_char
id|LUN
)paren
suffix:semicolon
r_int
r_char
id|ipmi_get_my_LUN
c_func
(paren
id|ipmi_user_t
id|user
)paren
suffix:semicolon
multiline_comment|/*&n; * Like ipmi_request, but lets you specify the number of retries and&n; * the retry time.  The retries is the number of times the message&n; * will be resent if no reply is received.  If set to -1, the default&n; * value will be used.  The retry time is the time in milliseconds&n; * between retries.  If set to zero, the default value will be&n; * used.&n; *&n; * Don&squot;t use this unless you *really* have to.  It&squot;s primarily for the&n; * IPMI over LAN converter; since the LAN stuff does its own retries,&n; * it makes no sense to do it here.  However, this can be used if you&n; * have unusual requirements.&n; */
r_int
id|ipmi_request_settime
c_func
(paren
id|ipmi_user_t
id|user
comma
r_struct
id|ipmi_addr
op_star
id|addr
comma
r_int
id|msgid
comma
r_struct
id|kernel_ipmi_msg
op_star
id|msg
comma
r_void
op_star
id|user_msg_data
comma
r_int
id|priority
comma
r_int
id|max_retries
comma
r_int
r_int
id|retry_time_ms
)paren
suffix:semicolon
multiline_comment|/*&n; * Like ipmi_request, but with messages supplied.  This will not&n; * allocate any memory, and the messages may be statically allocated&n; * (just make sure to do the &quot;done&quot; handling on them).  Note that this&n; * is primarily for the watchdog timer, since it should be able to&n; * send messages even if no memory is available.  This is subject to&n; * change as the system changes, so don&squot;t use it unless you REALLY&n; * have to.&n; */
r_int
id|ipmi_request_supply_msgs
c_func
(paren
id|ipmi_user_t
id|user
comma
r_struct
id|ipmi_addr
op_star
id|addr
comma
r_int
id|msgid
comma
r_struct
id|kernel_ipmi_msg
op_star
id|msg
comma
r_void
op_star
id|user_msg_data
comma
r_void
op_star
id|supplied_smi
comma
r_struct
id|ipmi_recv_msg
op_star
id|supplied_recv
comma
r_int
id|priority
)paren
suffix:semicolon
multiline_comment|/*&n; * When commands come in to the SMS, the user can register to receive&n; * them.  Only one user can be listening on a specific netfn/cmd pair&n; * at a time, you will get an EBUSY error if the command is already&n; * registered.  If a command is received that does not have a user&n; * registered, the driver will automatically return the proper&n; * error.&n; */
r_int
id|ipmi_register_for_cmd
c_func
(paren
id|ipmi_user_t
id|user
comma
r_int
r_char
id|netfn
comma
r_int
r_char
id|cmd
)paren
suffix:semicolon
r_int
id|ipmi_unregister_for_cmd
c_func
(paren
id|ipmi_user_t
id|user
comma
r_int
r_char
id|netfn
comma
r_int
r_char
id|cmd
)paren
suffix:semicolon
multiline_comment|/*&n; * Allow run-to-completion mode to be set for the interface of&n; * a specific user.&n; */
r_void
id|ipmi_user_set_run_to_completion
c_func
(paren
id|ipmi_user_t
id|user
comma
r_int
id|val
)paren
suffix:semicolon
multiline_comment|/*&n; * When the user is created, it will not receive IPMI events by&n; * default.  The user must set this to TRUE to get incoming events.&n; * The first user that sets this to TRUE will receive all events that&n; * have been queued while no one was waiting for events.&n; */
r_int
id|ipmi_set_gets_events
c_func
(paren
id|ipmi_user_t
id|user
comma
r_int
id|val
)paren
suffix:semicolon
multiline_comment|/*&n; * Called when a new SMI is registered.  This will also be called on&n; * every existing interface when a new watcher is registered with&n; * ipmi_smi_watcher_register().&n; */
DECL|struct|ipmi_smi_watcher
r_struct
id|ipmi_smi_watcher
(brace
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* You must set the owner to the current module, if you are in&n;&t;   a module (generally just set it to &quot;THIS_MODULE&quot;). */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* These two are called with read locks held for the interface&n;&t;   the watcher list.  So you can add and remove users from the&n;&t;   IPMI interface, send messages, etc., but you cannot add&n;&t;   or remove SMI watchers or SMI interfaces. */
DECL|member|new_smi
r_void
(paren
op_star
id|new_smi
)paren
(paren
r_int
id|if_num
)paren
suffix:semicolon
DECL|member|smi_gone
r_void
(paren
op_star
id|smi_gone
)paren
(paren
r_int
id|if_num
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|ipmi_smi_watcher_register
c_func
(paren
r_struct
id|ipmi_smi_watcher
op_star
id|watcher
)paren
suffix:semicolon
r_int
id|ipmi_smi_watcher_unregister
c_func
(paren
r_struct
id|ipmi_smi_watcher
op_star
id|watcher
)paren
suffix:semicolon
multiline_comment|/* The following are various helper functions for dealing with IPMI&n;   addresses. */
multiline_comment|/* Return the maximum length of an IPMI address given it&squot;s type. */
r_int
r_int
id|ipmi_addr_length
c_func
(paren
r_int
id|addr_type
)paren
suffix:semicolon
multiline_comment|/* Validate that the given IPMI address is valid. */
r_int
id|ipmi_validate_addr
c_func
(paren
r_struct
id|ipmi_addr
op_star
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * The userland interface&n; */
multiline_comment|/*&n; * The userland interface for the IPMI driver is a standard character&n; * device, with each instance of an interface registered as a minor&n; * number under the major character device.&n; *&n; * The read and write calls do not work, to get messages in and out&n; * requires ioctl calls because of the complexity of the data.  select&n; * and poll do work, so you can wait for input using the file&n; * descriptor, you just can use read to get it.&n; *&n; * In general, you send a command down to the interface and receive&n; * responses back.  You can use the msgid value to correlate commands&n; * and responses, the driver will take care of figuring out which&n; * incoming messages are for which command and find the proper msgid&n; * value to report.  You will only receive reponses for commands you&n; * send.  Asynchronous events, however, go to all open users, so you&n; * must be ready to handle these (or ignore them if you don&squot;t care).&n; *&n; * The address type depends upon the channel type.  When talking&n; * directly to the BMC (IPMC_BMC_CHANNEL), the address is ignored&n; * (IPMI_UNUSED_ADDR_TYPE).  When talking to an IPMB channel, you must&n; * supply a valid IPMB address with the addr_type set properly.&n; *&n; * When talking to normal channels, the driver takes care of the&n; * details of formatting and sending messages on that channel.  You do&n; * not, for instance, have to format a send command, you just send&n; * whatever command you want to the channel, the driver will create&n; * the send command, automatically issue receive command and get even&n; * commands, and pass those up to the proper user.&n; */
multiline_comment|/* The magic IOCTL value for this interface. */
DECL|macro|IPMI_IOC_MAGIC
mdefine_line|#define IPMI_IOC_MAGIC &squot;i&squot;
multiline_comment|/* Messages sent to the interface are this format. */
DECL|struct|ipmi_req
r_struct
id|ipmi_req
(brace
DECL|member|addr
r_int
r_char
id|__user
op_star
id|addr
suffix:semicolon
multiline_comment|/* Address to send the message to. */
DECL|member|addr_len
r_int
r_int
id|addr_len
suffix:semicolon
DECL|member|msgid
r_int
id|msgid
suffix:semicolon
multiline_comment|/* The sequence number for the message.  This&n;&t;&t;&t;  exact value will be reported back in the&n;&t;&t;&t;  response to this request if it is a command.&n;&t;&t;&t;  If it is a response, this will be used as&n;&t;&t;&t;  the sequence value for the response.  */
DECL|member|msg
r_struct
id|ipmi_msg
id|msg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Send a message to the interfaces.  error values are:&n; *   - EFAULT - an address supplied was invalid.&n; *   - EINVAL - The address supplied was not valid, or the command&n; *              was not allowed.&n; *   - EMSGSIZE - The message to was too large.&n; *   - ENOMEM - Buffers could not be allocated for the command.&n; */
DECL|macro|IPMICTL_SEND_COMMAND
mdefine_line|#define IPMICTL_SEND_COMMAND&t;&t;_IOR(IPMI_IOC_MAGIC, 13,&t;&bslash;&n;&t;&t;&t;&t;&t;     struct ipmi_req)
multiline_comment|/* Messages sent to the interface with timing parameters are this&n;   format. */
DECL|struct|ipmi_req_settime
r_struct
id|ipmi_req_settime
(brace
DECL|member|req
r_struct
id|ipmi_req
id|req
suffix:semicolon
multiline_comment|/* See ipmi_request_settime() above for details on these&n;           values. */
DECL|member|retries
r_int
id|retries
suffix:semicolon
DECL|member|retry_time_ms
r_int
r_int
id|retry_time_ms
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Send a message to the interfaces with timing parameters.  error values&n; * are:&n; *   - EFAULT - an address supplied was invalid.&n; *   - EINVAL - The address supplied was not valid, or the command&n; *              was not allowed.&n; *   - EMSGSIZE - The message to was too large.&n; *   - ENOMEM - Buffers could not be allocated for the command.&n; */
DECL|macro|IPMICTL_SEND_COMMAND_SETTIME
mdefine_line|#define IPMICTL_SEND_COMMAND_SETTIME&t;_IOR(IPMI_IOC_MAGIC, 21,&t;&bslash;&n;&t;&t;&t;&t;&t;     struct ipmi_req_settime)
multiline_comment|/* Messages received from the interface are this format. */
DECL|struct|ipmi_recv
r_struct
id|ipmi_recv
(brace
DECL|member|recv_type
r_int
id|recv_type
suffix:semicolon
multiline_comment|/* Is this a command, response or an&n;&t;&t;&t;      asyncronous event. */
DECL|member|addr
r_int
r_char
id|__user
op_star
id|addr
suffix:semicolon
multiline_comment|/* Address the message was from is put&n;&t;&t;&t;&t;   here.  The caller must supply the&n;&t;&t;&t;&t;   memory. */
DECL|member|addr_len
r_int
r_int
id|addr_len
suffix:semicolon
multiline_comment|/* The size of the address buffer.&n;&t;&t;&t;&t;   The caller supplies the full buffer&n;&t;&t;&t;&t;   length, this value is updated to&n;&t;&t;&t;&t;   the actual message length when the&n;&t;&t;&t;&t;   message is received. */
DECL|member|msgid
r_int
id|msgid
suffix:semicolon
multiline_comment|/* The sequence number specified in the request&n;&t;&t;&t;  if this is a response.  If this is a command,&n;&t;&t;&t;  this will be the sequence number from the&n;&t;&t;&t;  command. */
DECL|member|msg
r_struct
id|ipmi_msg
id|msg
suffix:semicolon
multiline_comment|/* The data field must point to a buffer.&n;&t;&t;&t;&t;The data_size field must be set to the&n;&t;&t;&t;&t;size of the message buffer.  The&n;&t;&t;&t;&t;caller supplies the full buffer&n;&t;&t;&t;&t;length, this value is updated to the&n;&t;&t;&t;&t;actual message length when the message&n;&t;&t;&t;&t;is received. */
)brace
suffix:semicolon
multiline_comment|/*&n; * Receive a message.  error values:&n; *  - EAGAIN - no messages in the queue.&n; *  - EFAULT - an address supplied was invalid.&n; *  - EINVAL - The address supplied was not valid.&n; *  - EMSGSIZE - The message to was too large to fit into the message buffer,&n; *               the message will be left in the buffer. */
DECL|macro|IPMICTL_RECEIVE_MSG
mdefine_line|#define IPMICTL_RECEIVE_MSG&t;&t;_IOWR(IPMI_IOC_MAGIC, 12,&t;&bslash;&n;&t;&t;&t;&t;&t;      struct ipmi_recv)
multiline_comment|/*&n; * Like RECEIVE_MSG, but if the message won&squot;t fit in the buffer, it&n; * will truncate the contents instead of leaving the data in the&n; * buffer.&n; */
DECL|macro|IPMICTL_RECEIVE_MSG_TRUNC
mdefine_line|#define IPMICTL_RECEIVE_MSG_TRUNC&t;_IOWR(IPMI_IOC_MAGIC, 11,&t;&bslash;&n;&t;&t;&t;&t;&t;      struct ipmi_recv)
multiline_comment|/* Register to get commands from other entities on this interface. */
DECL|struct|ipmi_cmdspec
r_struct
id|ipmi_cmdspec
(brace
DECL|member|netfn
r_int
r_char
id|netfn
suffix:semicolon
DECL|member|cmd
r_int
r_char
id|cmd
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Register to receive a specific command.  error values:&n; *   - EFAULT - an address supplied was invalid.&n; *   - EBUSY - The netfn/cmd supplied was already in use.&n; *   - ENOMEM - could not allocate memory for the entry.&n; */
DECL|macro|IPMICTL_REGISTER_FOR_CMD
mdefine_line|#define IPMICTL_REGISTER_FOR_CMD&t;_IOR(IPMI_IOC_MAGIC, 14,&t;&bslash;&n;&t;&t;&t;&t;&t;     struct ipmi_cmdspec)
multiline_comment|/*&n; * Unregister a regsitered command.  error values:&n; *  - EFAULT - an address supplied was invalid.&n; *  - ENOENT - The netfn/cmd was not found registered for this user.&n; */
DECL|macro|IPMICTL_UNREGISTER_FOR_CMD
mdefine_line|#define IPMICTL_UNREGISTER_FOR_CMD&t;_IOR(IPMI_IOC_MAGIC, 15,&t;&bslash;&n;&t;&t;&t;&t;&t;     struct ipmi_cmdspec)
multiline_comment|/* &n; * Set whether this interface receives events.  Note that the first&n; * user registered for events will get all pending events for the&n; * interface.  error values:&n; *  - EFAULT - an address supplied was invalid.&n; */
DECL|macro|IPMICTL_SET_GETS_EVENTS_CMD
mdefine_line|#define IPMICTL_SET_GETS_EVENTS_CMD&t;_IOR(IPMI_IOC_MAGIC, 16, int)
multiline_comment|/*&n; * Set and get the slave address and LUN that we will use for our&n; * source messages.  Note that this affects the interface, not just&n; * this user, so it will affect all users of this interface.  This is&n; * so some initialization code can come in and do the OEM-specific&n; * things it takes to determine your address (if not the BMC) and set&n; * it for everyone else.  You should probably leave the LUN alone.&n; */
DECL|macro|IPMICTL_SET_MY_ADDRESS_CMD
mdefine_line|#define IPMICTL_SET_MY_ADDRESS_CMD&t;_IOR(IPMI_IOC_MAGIC, 17, unsigned int)
DECL|macro|IPMICTL_GET_MY_ADDRESS_CMD
mdefine_line|#define IPMICTL_GET_MY_ADDRESS_CMD&t;_IOR(IPMI_IOC_MAGIC, 18, unsigned int)
DECL|macro|IPMICTL_SET_MY_LUN_CMD
mdefine_line|#define IPMICTL_SET_MY_LUN_CMD&t;&t;_IOR(IPMI_IOC_MAGIC, 19, unsigned int)
DECL|macro|IPMICTL_GET_MY_LUN_CMD
mdefine_line|#define IPMICTL_GET_MY_LUN_CMD&t;&t;_IOR(IPMI_IOC_MAGIC, 20, unsigned int)
multiline_comment|/*&n; * Get/set the default timing values for an interface.  You shouldn&squot;t&n; * generally mess with these.&n; */
DECL|struct|ipmi_timing_parms
r_struct
id|ipmi_timing_parms
(brace
DECL|member|retries
r_int
id|retries
suffix:semicolon
DECL|member|retry_time_ms
r_int
r_int
id|retry_time_ms
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IPMICTL_SET_TIMING_PARMS_CMD
mdefine_line|#define IPMICTL_SET_TIMING_PARMS_CMD&t;_IOR(IPMI_IOC_MAGIC, 22, &bslash;&n;&t;&t;&t;&t;&t;     struct ipmi_timing_parms)
DECL|macro|IPMICTL_GET_TIMING_PARMS_CMD
mdefine_line|#define IPMICTL_GET_TIMING_PARMS_CMD&t;_IOR(IPMI_IOC_MAGIC, 23, &bslash;&n;&t;&t;&t;&t;&t;     struct ipmi_timing_parms)
macro_line|#endif /* __LINUX_IPMI_H */
eof
