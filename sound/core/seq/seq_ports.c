multiline_comment|/*&n; *   ALSA sequencer Ports&n; *   Copyright (c) 1998 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *                         Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;seq_system.h&quot;
macro_line|#include &quot;seq_ports.h&quot;
macro_line|#include &quot;seq_clientmgr.h&quot;
multiline_comment|/*&n;&n;   registration of client ports&n;&n; */
multiline_comment|/* &n;&n;NOTE: the current implementation of the port structure as a linked list is&n;not optimal for clients that have many ports. For sending messages to all&n;subscribers of a port we first need to find the address of the port&n;structure, which means we have to traverse the list. A direct access table&n;(array) would be better, but big preallocated arrays waste memory.&n;&n;Possible actions:&n;&n;1) leave it this way, a client does normaly does not have more than a few&n;ports&n;&n;2) replace the linked list of ports by a array of pointers which is&n;dynamicly kmalloced. When a port is added or deleted we can simply allocate&n;a new array, copy the corresponding pointers, and delete the old one. We&n;then only need a pointer to this array, and an integer that tells us how&n;much elements are in array.&n;&n;*/
multiline_comment|/* return pointer to port structure - port is locked if found */
DECL|function|snd_seq_port_use_ptr
id|client_port_t
op_star
id|snd_seq_port_use_ptr
c_func
(paren
id|client_t
op_star
id|client
comma
r_int
id|num
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|client_port_t
op_star
id|port
suffix:semicolon
r_if
c_cond
(paren
id|client
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|client-&gt;ports_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|client-&gt;ports_list_head
)paren
(brace
id|port
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|client_port_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;addr.port
op_eq
id|num
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;closing
)paren
r_break
suffix:semicolon
multiline_comment|/* deleting now */
id|snd_use_lock_use
c_func
(paren
op_amp
id|port-&gt;use_lock
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|client-&gt;ports_lock
)paren
suffix:semicolon
r_return
id|port
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|client-&gt;ports_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* not found */
)brace
multiline_comment|/* search for the next port - port is locked if found */
DECL|function|snd_seq_port_query_nearest
id|client_port_t
op_star
id|snd_seq_port_query_nearest
c_func
(paren
id|client_t
op_star
id|client
comma
id|snd_seq_port_info_t
op_star
id|pinfo
)paren
(brace
r_int
id|num
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|client_port_t
op_star
id|port
comma
op_star
id|found
suffix:semicolon
id|num
op_assign
id|pinfo-&gt;addr.port
suffix:semicolon
id|found
op_assign
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|client-&gt;ports_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|client-&gt;ports_list_head
)paren
(brace
id|port
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|client_port_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;addr.port
OL
id|num
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;addr.port
op_eq
id|num
)paren
(brace
id|found
op_assign
id|port
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
op_eq
l_int|NULL
op_logical_or
id|port-&gt;addr.port
OL
id|found-&gt;addr.port
)paren
id|found
op_assign
id|port
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
)paren
(brace
r_if
c_cond
(paren
id|found-&gt;closing
)paren
id|found
op_assign
l_int|NULL
suffix:semicolon
r_else
id|snd_use_lock_use
c_func
(paren
op_amp
id|found-&gt;use_lock
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|client-&gt;ports_lock
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
multiline_comment|/* initialize port_subs_info_t */
DECL|function|port_subs_info_init
r_static
r_void
id|port_subs_info_init
c_func
(paren
id|port_subs_info_t
op_star
id|grp
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|grp-&gt;list_head
)paren
suffix:semicolon
id|grp-&gt;count
op_assign
l_int|0
suffix:semicolon
id|grp-&gt;exclusive
op_assign
l_int|0
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|grp-&gt;list_lock
)paren
suffix:semicolon
id|init_rwsem
c_func
(paren
op_amp
id|grp-&gt;list_mutex
)paren
suffix:semicolon
id|grp-&gt;open
op_assign
l_int|NULL
suffix:semicolon
id|grp-&gt;close
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* create a port, port number is returned (-1 on failure) */
DECL|function|snd_seq_create_port
id|client_port_t
op_star
id|snd_seq_create_port
c_func
(paren
id|client_t
op_star
id|client
comma
r_int
id|port
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|client_port_t
op_star
id|new_port
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_int
id|num
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* sanity check */
id|snd_assert
c_func
(paren
id|client
comma
r_return
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|client-&gt;num_ports
op_ge
id|SNDRV_SEQ_MAX_PORTS
op_minus
l_int|1
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;too many ports for client %d&bslash;n&quot;
comma
id|client-&gt;number
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* create a new port */
id|new_port
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|client_port_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_port
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;malloc failed for registering client port&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* failure, out of memory */
)brace
multiline_comment|/* init port data */
id|new_port-&gt;addr.client
op_assign
id|client-&gt;number
suffix:semicolon
id|new_port-&gt;addr.port
op_assign
op_minus
l_int|1
suffix:semicolon
id|new_port-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|sprintf
c_func
(paren
id|new_port-&gt;name
comma
l_string|&quot;port-%d&quot;
comma
id|num
)paren
suffix:semicolon
id|snd_use_lock_init
c_func
(paren
op_amp
id|new_port-&gt;use_lock
)paren
suffix:semicolon
id|port_subs_info_init
c_func
(paren
op_amp
id|new_port-&gt;c_src
)paren
suffix:semicolon
id|port_subs_info_init
c_func
(paren
op_amp
id|new_port-&gt;c_dest
)paren
suffix:semicolon
id|num
op_assign
id|port
op_ge
l_int|0
ques
c_cond
id|port
suffix:colon
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|client-&gt;ports_mutex
)paren
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|client-&gt;ports_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|client-&gt;ports_list_head
)paren
(brace
id|client_port_t
op_star
id|p
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|client_port_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;addr.port
OG
id|num
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|port
OL
l_int|0
)paren
multiline_comment|/* auto-probe mode */
id|num
op_assign
id|p-&gt;addr.port
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* insert the new port */
id|list_add_tail
c_func
(paren
op_amp
id|new_port-&gt;list
comma
id|l
)paren
suffix:semicolon
id|client-&gt;num_ports
op_increment
suffix:semicolon
id|new_port-&gt;addr.port
op_assign
id|num
suffix:semicolon
multiline_comment|/* store the port number in the port */
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|client-&gt;ports_lock
comma
id|flags
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|client-&gt;ports_mutex
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|new_port-&gt;name
comma
l_string|&quot;port-%d&quot;
comma
id|num
)paren
suffix:semicolon
r_return
id|new_port
suffix:semicolon
)brace
multiline_comment|/* */
DECL|enum|group_type_t
r_enum
id|group_type_t
(brace
DECL|enumerator|SRC_LIST
DECL|enumerator|DEST_LIST
id|SRC_LIST
comma
id|DEST_LIST
)brace
suffix:semicolon
r_static
r_int
id|subscribe_port
c_func
(paren
id|client_t
op_star
id|client
comma
id|client_port_t
op_star
id|port
comma
id|port_subs_info_t
op_star
id|grp
comma
id|snd_seq_port_subscribe_t
op_star
id|info
comma
r_int
id|send_ack
)paren
suffix:semicolon
r_static
r_int
id|unsubscribe_port
c_func
(paren
id|client_t
op_star
id|client
comma
id|client_port_t
op_star
id|port
comma
id|port_subs_info_t
op_star
id|grp
comma
id|snd_seq_port_subscribe_t
op_star
id|info
comma
r_int
id|send_ack
)paren
suffix:semicolon
DECL|function|get_client_port
r_static
id|client_port_t
op_star
id|get_client_port
c_func
(paren
id|snd_seq_addr_t
op_star
id|addr
comma
id|client_t
op_star
op_star
id|cp
)paren
(brace
id|client_port_t
op_star
id|p
suffix:semicolon
op_star
id|cp
op_assign
id|snd_seq_client_use_ptr
c_func
(paren
id|addr-&gt;client
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
)paren
(brace
id|p
op_assign
id|snd_seq_port_use_ptr
c_func
(paren
op_star
id|cp
comma
id|addr-&gt;port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|snd_seq_client_unlock
c_func
(paren
op_star
id|cp
)paren
suffix:semicolon
op_star
id|cp
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * remove all subscribers on the list&n; * this is called from port_delete, for each src and dest list.&n; */
DECL|function|clear_subscriber_list
r_static
r_void
id|clear_subscriber_list
c_func
(paren
id|client_t
op_star
id|client
comma
id|client_port_t
op_star
id|port
comma
id|port_subs_info_t
op_star
id|grp
comma
r_int
id|grptype
)paren
(brace
r_struct
id|list_head
op_star
id|p
comma
op_star
id|n
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|grp-&gt;list_mutex
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|p
comma
id|n
comma
op_amp
id|grp-&gt;list_head
)paren
(brace
id|subscribers_t
op_star
id|subs
suffix:semicolon
id|client_t
op_star
id|c
suffix:semicolon
id|client_port_t
op_star
id|aport
suffix:semicolon
r_if
c_cond
(paren
id|grptype
op_eq
id|SRC_LIST
)paren
(brace
id|subs
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|subscribers_t
comma
id|src_list
)paren
suffix:semicolon
id|aport
op_assign
id|get_client_port
c_func
(paren
op_amp
id|subs-&gt;info.dest
comma
op_amp
id|c
)paren
suffix:semicolon
)brace
r_else
(brace
id|subs
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|subscribers_t
comma
id|dest_list
)paren
suffix:semicolon
id|aport
op_assign
id|get_client_port
c_func
(paren
op_amp
id|subs-&gt;info.sender
comma
op_amp
id|c
)paren
suffix:semicolon
)brace
id|list_del
c_func
(paren
id|p
)paren
suffix:semicolon
id|unsubscribe_port
c_func
(paren
id|client
comma
id|port
comma
id|grp
comma
op_amp
id|subs-&gt;info
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|aport
)paren
(brace
multiline_comment|/* looks like the connected port is being deleted.&n;&t;&t;&t; * we decrease the counter, and when both ports are deleted&n;&t;&t;&t; * remove the subscriber info&n;&t;&t;&t; */
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|subs-&gt;ref_count
)paren
)paren
id|kfree
c_func
(paren
id|subs
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* ok we got the connected port */
id|port_subs_info_t
op_star
id|agrp
suffix:semicolon
id|agrp
op_assign
(paren
id|grptype
op_eq
id|SRC_LIST
)paren
ques
c_cond
op_amp
id|aport-&gt;c_dest
suffix:colon
op_amp
id|aport-&gt;c_src
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|agrp-&gt;list_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|grptype
op_eq
id|SRC_LIST
)paren
id|list_del
c_func
(paren
op_amp
id|subs-&gt;dest_list
)paren
suffix:semicolon
r_else
id|list_del
c_func
(paren
op_amp
id|subs-&gt;src_list
)paren
suffix:semicolon
id|unsubscribe_port
c_func
(paren
id|c
comma
id|aport
comma
id|agrp
comma
op_amp
id|subs-&gt;info
comma
l_int|1
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|subs
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|agrp-&gt;list_mutex
)paren
suffix:semicolon
id|snd_seq_port_unlock
c_func
(paren
id|aport
)paren
suffix:semicolon
id|snd_seq_client_unlock
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
id|up_write
c_func
(paren
op_amp
id|grp-&gt;list_mutex
)paren
suffix:semicolon
)brace
multiline_comment|/* delete port data */
DECL|function|port_delete
r_static
r_int
id|port_delete
c_func
(paren
id|client_t
op_star
id|client
comma
id|client_port_t
op_star
id|port
)paren
(brace
multiline_comment|/* set closing flag and wait for all port access are gone */
id|port-&gt;closing
op_assign
l_int|1
suffix:semicolon
id|snd_use_lock_sync
c_func
(paren
op_amp
id|port-&gt;use_lock
)paren
suffix:semicolon
multiline_comment|/* clear subscribers info */
id|clear_subscriber_list
c_func
(paren
id|client
comma
id|port
comma
op_amp
id|port-&gt;c_src
comma
id|SRC_LIST
)paren
suffix:semicolon
id|clear_subscriber_list
c_func
(paren
id|client
comma
id|port
comma
op_amp
id|port-&gt;c_dest
comma
id|DEST_LIST
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;private_free
)paren
id|port
op_member_access_from_pointer
id|private_free
c_func
(paren
id|port-&gt;private_data
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|port-&gt;c_src.count
op_eq
l_int|0
comma
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|port-&gt;c_dest.count
op_eq
l_int|0
comma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* delete a port with the given port id */
DECL|function|snd_seq_delete_port
r_int
id|snd_seq_delete_port
c_func
(paren
id|client_t
op_star
id|client
comma
r_int
id|port
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|client_port_t
op_star
id|found
op_assign
l_int|NULL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|client-&gt;ports_mutex
)paren
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|client-&gt;ports_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|client-&gt;ports_list_head
)paren
(brace
id|client_port_t
op_star
id|p
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|client_port_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;addr.port
op_eq
id|port
)paren
(brace
multiline_comment|/* ok found.  delete from the list at first */
id|list_del
c_func
(paren
id|l
)paren
suffix:semicolon
id|client-&gt;num_ports
op_decrement
suffix:semicolon
id|found
op_assign
id|p
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|client-&gt;ports_lock
comma
id|flags
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|client-&gt;ports_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found
)paren
r_return
id|port_delete
c_func
(paren
id|client
comma
id|found
)paren
suffix:semicolon
r_else
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
multiline_comment|/* delete the all ports belonging to the given client */
DECL|function|snd_seq_delete_all_ports
r_int
id|snd_seq_delete_all_ports
c_func
(paren
id|client_t
op_star
id|client
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
id|deleted_list
comma
op_star
id|p
comma
op_star
id|n
suffix:semicolon
multiline_comment|/* move the port list to deleted_list, and&n;&t; * clear the port list in the client data.&n;&t; */
id|down
c_func
(paren
op_amp
id|client-&gt;ports_mutex
)paren
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|client-&gt;ports_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|client-&gt;ports_list_head
)paren
)paren
(brace
id|__list_add
c_func
(paren
op_amp
id|deleted_list
comma
id|client-&gt;ports_list_head.prev
comma
id|client-&gt;ports_list_head.next
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|client-&gt;ports_list_head
)paren
suffix:semicolon
)brace
r_else
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|deleted_list
)paren
suffix:semicolon
)brace
id|client-&gt;num_ports
op_assign
l_int|0
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|client-&gt;ports_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* remove each port in deleted_list */
id|list_for_each_safe
c_func
(paren
id|p
comma
id|n
comma
op_amp
id|deleted_list
)paren
(brace
id|client_port_t
op_star
id|port
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|client_port_t
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
id|p
)paren
suffix:semicolon
id|snd_seq_system_client_ev_port_exit
c_func
(paren
id|port-&gt;addr.client
comma
id|port-&gt;addr.port
)paren
suffix:semicolon
id|port_delete
c_func
(paren
id|client
comma
id|port
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|client-&gt;ports_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* set port info fields */
DECL|function|snd_seq_set_port_info
r_int
id|snd_seq_set_port_info
c_func
(paren
id|client_port_t
op_star
id|port
comma
id|snd_seq_port_info_t
op_star
id|info
)paren
(brace
id|snd_assert
c_func
(paren
id|port
op_logical_and
id|info
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* set port name */
r_if
c_cond
(paren
id|info-&gt;name
(braket
l_int|0
)braket
)paren
(brace
id|strncpy
c_func
(paren
id|port-&gt;name
comma
id|info-&gt;name
comma
r_sizeof
(paren
id|port-&gt;name
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|port-&gt;name
(braket
r_sizeof
(paren
id|port-&gt;name
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
multiline_comment|/* set capabilities */
id|port-&gt;capability
op_assign
id|info-&gt;capability
suffix:semicolon
multiline_comment|/* get port type */
id|port-&gt;type
op_assign
id|info-&gt;type
suffix:semicolon
multiline_comment|/* information about supported channels/voices */
id|port-&gt;midi_channels
op_assign
id|info-&gt;midi_channels
suffix:semicolon
id|port-&gt;midi_voices
op_assign
id|info-&gt;midi_voices
suffix:semicolon
id|port-&gt;synth_voices
op_assign
id|info-&gt;synth_voices
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* get port info fields */
DECL|function|snd_seq_get_port_info
r_int
id|snd_seq_get_port_info
c_func
(paren
id|client_port_t
op_star
id|port
comma
id|snd_seq_port_info_t
op_star
id|info
)paren
(brace
id|snd_assert
c_func
(paren
id|port
op_logical_and
id|info
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* get port name */
id|strncpy
c_func
(paren
id|info-&gt;name
comma
id|port-&gt;name
comma
r_sizeof
(paren
id|info-&gt;name
)paren
)paren
suffix:semicolon
multiline_comment|/* get capabilities */
id|info-&gt;capability
op_assign
id|port-&gt;capability
suffix:semicolon
multiline_comment|/* get port type */
id|info-&gt;type
op_assign
id|port-&gt;type
suffix:semicolon
multiline_comment|/* information about supported channels/voices */
id|info-&gt;midi_channels
op_assign
id|port-&gt;midi_channels
suffix:semicolon
id|info-&gt;midi_voices
op_assign
id|port-&gt;midi_voices
suffix:semicolon
id|info-&gt;synth_voices
op_assign
id|port-&gt;synth_voices
suffix:semicolon
multiline_comment|/* get subscriber counts */
id|info-&gt;read_use
op_assign
id|port-&gt;c_src.count
suffix:semicolon
id|info-&gt;write_use
op_assign
id|port-&gt;c_dest.count
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * call callback functions (if any):&n; * the callbacks are invoked only when the first (for connection) or&n; * the last subscription (for disconnection) is done.  Second or later&n; * subscription results in increment of counter, but no callback is&n; * invoked.&n; * This feature is useful if these callbacks are associated with&n; * initialization or termination of devices (see seq_midi.c).&n; *&n; * If callback_all option is set, the callback function is invoked&n; * at each connnection/disconnection. &n; */
DECL|function|subscribe_port
r_static
r_int
id|subscribe_port
c_func
(paren
id|client_t
op_star
id|client
comma
id|client_port_t
op_star
id|port
comma
id|port_subs_info_t
op_star
id|grp
comma
id|snd_seq_port_subscribe_t
op_star
id|info
comma
r_int
id|send_ack
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|port-&gt;owner
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|grp-&gt;count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|grp-&gt;open
op_logical_and
(paren
id|port-&gt;callback_all
op_logical_or
id|grp-&gt;count
op_eq
l_int|1
)paren
)paren
(brace
id|err
op_assign
id|grp
op_member_access_from_pointer
id|open
c_func
(paren
id|port-&gt;private_data
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|module_put
c_func
(paren
id|port-&gt;owner
)paren
suffix:semicolon
id|grp-&gt;count
op_decrement
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|err
op_ge
l_int|0
op_logical_and
id|send_ack
op_logical_and
id|client-&gt;type
op_eq
id|USER_CLIENT
)paren
id|snd_seq_client_notify_subscription
c_func
(paren
id|port-&gt;addr.client
comma
id|port-&gt;addr.port
comma
id|info
comma
id|SNDRV_SEQ_EVENT_PORT_SUBSCRIBED
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|unsubscribe_port
r_static
r_int
id|unsubscribe_port
c_func
(paren
id|client_t
op_star
id|client
comma
id|client_port_t
op_star
id|port
comma
id|port_subs_info_t
op_star
id|grp
comma
id|snd_seq_port_subscribe_t
op_star
id|info
comma
r_int
id|send_ack
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|grp-&gt;count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|grp-&gt;count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|grp-&gt;close
op_logical_and
(paren
id|port-&gt;callback_all
op_logical_or
id|grp-&gt;count
op_eq
l_int|0
)paren
)paren
id|err
op_assign
id|grp
op_member_access_from_pointer
id|close
c_func
(paren
id|port-&gt;private_data
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|send_ack
op_logical_and
id|client-&gt;type
op_eq
id|USER_CLIENT
)paren
id|snd_seq_client_notify_subscription
c_func
(paren
id|port-&gt;addr.client
comma
id|port-&gt;addr.port
comma
id|info
comma
id|SNDRV_SEQ_EVENT_PORT_UNSUBSCRIBED
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|port-&gt;owner
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* check if both addresses are identical */
DECL|function|addr_match
r_static
r_inline
r_int
id|addr_match
c_func
(paren
id|snd_seq_addr_t
op_star
id|r
comma
id|snd_seq_addr_t
op_star
id|s
)paren
(brace
r_return
(paren
id|r-&gt;client
op_eq
id|s-&gt;client
)paren
op_logical_and
(paren
id|r-&gt;port
op_eq
id|s-&gt;port
)paren
suffix:semicolon
)brace
multiline_comment|/* check the two subscribe info match */
multiline_comment|/* if flags is zero, checks only sender and destination addresses */
DECL|function|match_subs_info
r_static
r_int
id|match_subs_info
c_func
(paren
id|snd_seq_port_subscribe_t
op_star
id|r
comma
id|snd_seq_port_subscribe_t
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|addr_match
c_func
(paren
op_amp
id|r-&gt;sender
comma
op_amp
id|s-&gt;sender
)paren
op_logical_and
id|addr_match
c_func
(paren
op_amp
id|r-&gt;dest
comma
op_amp
id|s-&gt;dest
)paren
)paren
(brace
r_if
c_cond
(paren
id|r-&gt;flags
op_logical_and
id|r-&gt;flags
op_eq
id|s-&gt;flags
)paren
r_return
id|r-&gt;queue
op_eq
id|s-&gt;queue
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;flags
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* connect two ports */
DECL|function|snd_seq_port_connect
r_int
id|snd_seq_port_connect
c_func
(paren
id|client_t
op_star
id|connector
comma
id|client_t
op_star
id|src_client
comma
id|client_port_t
op_star
id|src_port
comma
id|client_t
op_star
id|dest_client
comma
id|client_port_t
op_star
id|dest_port
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
(brace
id|port_subs_info_t
op_star
id|src
op_assign
op_amp
id|src_port-&gt;c_src
suffix:semicolon
id|port_subs_info_t
op_star
id|dest
op_assign
op_amp
id|dest_port-&gt;c_dest
suffix:semicolon
id|subscribers_t
op_star
id|subs
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_int
id|err
comma
id|src_called
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|exclusive
suffix:semicolon
id|subs
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|subs
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|subs
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|subs-&gt;info
op_assign
op_star
id|info
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|subs-&gt;ref_count
comma
l_int|2
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|src-&gt;list_mutex
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|dest-&gt;list_mutex
)paren
suffix:semicolon
id|exclusive
op_assign
id|info-&gt;flags
op_amp
id|SNDRV_SEQ_PORT_SUBS_EXCLUSIVE
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|exclusive
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|src-&gt;list_head
)paren
op_logical_or
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dest-&gt;list_head
)paren
)paren
r_goto
id|__error
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|src-&gt;exclusive
op_logical_or
id|dest-&gt;exclusive
)paren
r_goto
id|__error
suffix:semicolon
multiline_comment|/* check whether already exists */
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|src-&gt;list_head
)paren
(brace
id|subscribers_t
op_star
id|s
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|subscribers_t
comma
id|src_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_subs_info
c_func
(paren
id|info
comma
op_amp
id|s-&gt;info
)paren
)paren
r_goto
id|__error
suffix:semicolon
)brace
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|dest-&gt;list_head
)paren
(brace
id|subscribers_t
op_star
id|s
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|subscribers_t
comma
id|dest_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_subs_info
c_func
(paren
id|info
comma
op_amp
id|s-&gt;info
)paren
)paren
r_goto
id|__error
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|subscribe_port
c_func
(paren
id|src_client
comma
id|src_port
comma
id|src
comma
id|info
comma
id|connector-&gt;number
op_ne
id|src_client-&gt;number
)paren
)paren
OL
l_int|0
)paren
r_goto
id|__error
suffix:semicolon
id|src_called
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|subscribe_port
c_func
(paren
id|dest_client
comma
id|dest_port
comma
id|dest
comma
id|info
comma
id|connector-&gt;number
op_ne
id|dest_client-&gt;number
)paren
)paren
OL
l_int|0
)paren
r_goto
id|__error
suffix:semicolon
multiline_comment|/* add to list */
id|write_lock_irqsave
c_func
(paren
op_amp
id|src-&gt;list_lock
comma
id|flags
)paren
suffix:semicolon
singleline_comment|// write_lock(&amp;dest-&gt;list_lock); // no other lock yet
id|list_add_tail
c_func
(paren
op_amp
id|subs-&gt;src_list
comma
op_amp
id|src-&gt;list_head
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|subs-&gt;dest_list
comma
op_amp
id|dest-&gt;list_head
)paren
suffix:semicolon
singleline_comment|// write_unlock(&amp;dest-&gt;list_lock); // no other lock yet
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|src-&gt;list_lock
comma
id|flags
)paren
suffix:semicolon
id|src-&gt;exclusive
op_assign
id|dest-&gt;exclusive
op_assign
id|exclusive
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|dest-&gt;list_mutex
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|src-&gt;list_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|__error
suffix:colon
r_if
c_cond
(paren
id|src_called
)paren
id|unsubscribe_port
c_func
(paren
id|src_client
comma
id|src_port
comma
id|src
comma
id|info
comma
id|connector-&gt;number
op_ne
id|src_client-&gt;number
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|subs
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|dest-&gt;list_mutex
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|src-&gt;list_mutex
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* remove the connection */
DECL|function|snd_seq_port_disconnect
r_int
id|snd_seq_port_disconnect
c_func
(paren
id|client_t
op_star
id|connector
comma
id|client_t
op_star
id|src_client
comma
id|client_port_t
op_star
id|src_port
comma
id|client_t
op_star
id|dest_client
comma
id|client_port_t
op_star
id|dest_port
comma
id|snd_seq_port_subscribe_t
op_star
id|info
)paren
(brace
id|port_subs_info_t
op_star
id|src
op_assign
op_amp
id|src_port-&gt;c_src
suffix:semicolon
id|port_subs_info_t
op_star
id|dest
op_assign
op_amp
id|dest_port-&gt;c_dest
suffix:semicolon
id|subscribers_t
op_star
id|subs
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|src-&gt;list_mutex
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|dest-&gt;list_mutex
)paren
suffix:semicolon
multiline_comment|/* look for the connection */
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|src-&gt;list_head
)paren
(brace
id|subs
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|subscribers_t
comma
id|src_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_subs_info
c_func
(paren
id|info
comma
op_amp
id|subs-&gt;info
)paren
)paren
(brace
id|write_lock_irqsave
c_func
(paren
op_amp
id|src-&gt;list_lock
comma
id|flags
)paren
suffix:semicolon
singleline_comment|// write_lock(&amp;dest-&gt;list_lock);  // no lock yet
id|list_del
c_func
(paren
op_amp
id|subs-&gt;src_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|subs-&gt;dest_list
)paren
suffix:semicolon
singleline_comment|// write_unlock(&amp;dest-&gt;list_lock);
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|src-&gt;list_lock
comma
id|flags
)paren
suffix:semicolon
id|src-&gt;exclusive
op_assign
id|dest-&gt;exclusive
op_assign
l_int|0
suffix:semicolon
id|unsubscribe_port
c_func
(paren
id|src_client
comma
id|src_port
comma
id|src
comma
id|info
comma
id|connector-&gt;number
op_ne
id|src_client-&gt;number
)paren
suffix:semicolon
id|unsubscribe_port
c_func
(paren
id|dest_client
comma
id|dest_port
comma
id|dest
comma
id|info
comma
id|connector-&gt;number
op_ne
id|dest_client-&gt;number
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|subs
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|up_write
c_func
(paren
op_amp
id|dest-&gt;list_mutex
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|src-&gt;list_mutex
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* get matched subscriber */
DECL|function|snd_seq_port_get_subscription
id|subscribers_t
op_star
id|snd_seq_port_get_subscription
c_func
(paren
id|port_subs_info_t
op_star
id|src_grp
comma
id|snd_seq_addr_t
op_star
id|dest_addr
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|subscribers_t
op_star
id|s
comma
op_star
id|found
op_assign
l_int|NULL
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|src_grp-&gt;list_mutex
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|src_grp-&gt;list_head
)paren
(brace
id|s
op_assign
id|list_entry
c_func
(paren
id|p
comma
id|subscribers_t
comma
id|src_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr_match
c_func
(paren
id|dest_addr
comma
op_amp
id|s-&gt;info.dest
)paren
)paren
(brace
id|found
op_assign
id|s
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|up_read
c_func
(paren
op_amp
id|src_grp-&gt;list_mutex
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
multiline_comment|/*&n; * Attach a device driver that wants to receive events from the&n; * sequencer.  Returns the new port number on success.&n; * A driver that wants to receive the events converted to midi, will&n; * use snd_seq_midisynth_register_port().&n; */
multiline_comment|/* exported */
DECL|function|snd_seq_event_port_attach
r_int
id|snd_seq_event_port_attach
c_func
(paren
r_int
id|client
comma
id|snd_seq_port_callback_t
op_star
id|pcbp
comma
r_int
id|cap
comma
r_int
id|type
comma
r_int
id|midi_channels
comma
r_int
id|midi_voices
comma
r_char
op_star
id|portname
)paren
(brace
id|snd_seq_port_info_t
id|portinfo
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* Set up the port */
id|memset
c_func
(paren
op_amp
id|portinfo
comma
l_int|0
comma
r_sizeof
(paren
id|portinfo
)paren
)paren
suffix:semicolon
id|portinfo.addr.client
op_assign
id|client
suffix:semicolon
r_if
c_cond
(paren
id|portname
)paren
id|strncpy
c_func
(paren
id|portinfo.name
comma
id|portname
comma
r_sizeof
(paren
id|portinfo.name
)paren
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|portinfo.name
comma
l_string|&quot;Unamed port&quot;
)paren
suffix:semicolon
id|portinfo.capability
op_assign
id|cap
suffix:semicolon
id|portinfo.type
op_assign
id|type
suffix:semicolon
id|portinfo.kernel
op_assign
id|pcbp
suffix:semicolon
id|portinfo.midi_channels
op_assign
id|midi_channels
suffix:semicolon
id|portinfo.midi_voices
op_assign
id|midi_voices
suffix:semicolon
multiline_comment|/* Create it */
id|ret
op_assign
id|snd_seq_kernel_client_ctl
c_func
(paren
id|client
comma
id|SNDRV_SEQ_IOCTL_CREATE_PORT
comma
op_amp
id|portinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
)paren
id|ret
op_assign
id|portinfo.addr.port
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Detach the driver from a port.&n; */
multiline_comment|/* exported */
DECL|function|snd_seq_event_port_detach
r_int
id|snd_seq_event_port_detach
c_func
(paren
r_int
id|client
comma
r_int
id|port
)paren
(brace
id|snd_seq_port_info_t
id|portinfo
suffix:semicolon
r_int
id|err
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|portinfo
comma
l_int|0
comma
r_sizeof
(paren
id|portinfo
)paren
)paren
suffix:semicolon
id|portinfo.addr.client
op_assign
id|client
suffix:semicolon
id|portinfo.addr.port
op_assign
id|port
suffix:semicolon
id|err
op_assign
id|snd_seq_kernel_client_ctl
c_func
(paren
id|client
comma
id|SNDRV_SEQ_IOCTL_DELETE_PORT
comma
op_amp
id|portinfo
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
