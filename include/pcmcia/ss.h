multiline_comment|/*&n; * ss.h 1.28 2000/06/12 21:55:40&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_SS_H
DECL|macro|_LINUX_SS_H
mdefine_line|#define _LINUX_SS_H
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
macro_line|#include &lt;linux/device.h&gt;
multiline_comment|/* Definitions for card status flags for GetStatus */
DECL|macro|SS_WRPROT
mdefine_line|#define SS_WRPROT&t;0x0001
DECL|macro|SS_CARDLOCK
mdefine_line|#define SS_CARDLOCK&t;0x0002
DECL|macro|SS_EJECTION
mdefine_line|#define SS_EJECTION&t;0x0004
DECL|macro|SS_INSERTION
mdefine_line|#define SS_INSERTION&t;0x0008
DECL|macro|SS_BATDEAD
mdefine_line|#define SS_BATDEAD&t;0x0010
DECL|macro|SS_BATWARN
mdefine_line|#define SS_BATWARN&t;0x0020
DECL|macro|SS_READY
mdefine_line|#define SS_READY&t;0x0040
DECL|macro|SS_DETECT
mdefine_line|#define SS_DETECT&t;0x0080
DECL|macro|SS_POWERON
mdefine_line|#define SS_POWERON&t;0x0100
DECL|macro|SS_GPI
mdefine_line|#define SS_GPI&t;&t;0x0200
DECL|macro|SS_STSCHG
mdefine_line|#define SS_STSCHG&t;0x0400
DECL|macro|SS_CARDBUS
mdefine_line|#define SS_CARDBUS&t;0x0800
DECL|macro|SS_3VCARD
mdefine_line|#define SS_3VCARD&t;0x1000
DECL|macro|SS_XVCARD
mdefine_line|#define SS_XVCARD&t;0x2000
DECL|macro|SS_PENDING
mdefine_line|#define SS_PENDING&t;0x4000
DECL|macro|SS_ZVCARD
mdefine_line|#define SS_ZVCARD&t;0x8000
multiline_comment|/* InquireSocket capabilities */
DECL|macro|SS_CAP_PAGE_REGS
mdefine_line|#define SS_CAP_PAGE_REGS&t;0x0001
DECL|macro|SS_CAP_VIRTUAL_BUS
mdefine_line|#define SS_CAP_VIRTUAL_BUS&t;0x0002
DECL|macro|SS_CAP_MEM_ALIGN
mdefine_line|#define SS_CAP_MEM_ALIGN&t;0x0004
DECL|macro|SS_CAP_STATIC_MAP
mdefine_line|#define SS_CAP_STATIC_MAP&t;0x0008
DECL|macro|SS_CAP_PCCARD
mdefine_line|#define SS_CAP_PCCARD&t;&t;0x4000
DECL|macro|SS_CAP_CARDBUS
mdefine_line|#define SS_CAP_CARDBUS&t;&t;0x8000
multiline_comment|/* for GetSocket, SetSocket */
DECL|struct|socket_state_t
r_typedef
r_struct
id|socket_state_t
(brace
DECL|member|flags
id|u_int
id|flags
suffix:semicolon
DECL|member|csc_mask
id|u_int
id|csc_mask
suffix:semicolon
DECL|member|Vcc
DECL|member|Vpp
id|u_char
id|Vcc
comma
id|Vpp
suffix:semicolon
DECL|member|io_irq
id|u_char
id|io_irq
suffix:semicolon
DECL|typedef|socket_state_t
)brace
id|socket_state_t
suffix:semicolon
r_extern
id|socket_state_t
id|dead_socket
suffix:semicolon
multiline_comment|/* Socket configuration flags */
DECL|macro|SS_PWR_AUTO
mdefine_line|#define SS_PWR_AUTO&t;0x0010
DECL|macro|SS_IOCARD
mdefine_line|#define SS_IOCARD&t;0x0020
DECL|macro|SS_RESET
mdefine_line|#define SS_RESET&t;0x0040
DECL|macro|SS_DMA_MODE
mdefine_line|#define SS_DMA_MODE&t;0x0080
DECL|macro|SS_SPKR_ENA
mdefine_line|#define SS_SPKR_ENA&t;0x0100
DECL|macro|SS_OUTPUT_ENA
mdefine_line|#define SS_OUTPUT_ENA&t;0x0200
multiline_comment|/* Flags for I/O port and memory windows */
DECL|macro|MAP_ACTIVE
mdefine_line|#define MAP_ACTIVE&t;0x01
DECL|macro|MAP_16BIT
mdefine_line|#define MAP_16BIT&t;0x02
DECL|macro|MAP_AUTOSZ
mdefine_line|#define MAP_AUTOSZ&t;0x04
DECL|macro|MAP_0WS
mdefine_line|#define MAP_0WS&t;&t;0x08
DECL|macro|MAP_WRPROT
mdefine_line|#define MAP_WRPROT&t;0x10
DECL|macro|MAP_ATTRIB
mdefine_line|#define MAP_ATTRIB&t;0x20
DECL|macro|MAP_USE_WAIT
mdefine_line|#define MAP_USE_WAIT&t;0x40
DECL|macro|MAP_PREFETCH
mdefine_line|#define MAP_PREFETCH&t;0x80
multiline_comment|/* Use this just for bridge windows */
DECL|macro|MAP_IOSPACE
mdefine_line|#define MAP_IOSPACE&t;0x20
DECL|struct|pccard_io_map
r_typedef
r_struct
id|pccard_io_map
(brace
DECL|member|map
id|u_char
id|map
suffix:semicolon
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|member|speed
id|u_short
id|speed
suffix:semicolon
DECL|member|start
DECL|member|stop
id|ioaddr_t
id|start
comma
id|stop
suffix:semicolon
DECL|typedef|pccard_io_map
)brace
id|pccard_io_map
suffix:semicolon
DECL|struct|pccard_mem_map
r_typedef
r_struct
id|pccard_mem_map
(brace
DECL|member|map
id|u_char
id|map
suffix:semicolon
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|member|speed
id|u_short
id|speed
suffix:semicolon
DECL|member|sys_start
DECL|member|sys_stop
id|u_long
id|sys_start
comma
id|sys_stop
suffix:semicolon
DECL|member|card_start
id|u_int
id|card_start
suffix:semicolon
DECL|typedef|pccard_mem_map
)brace
id|pccard_mem_map
suffix:semicolon
DECL|struct|cb_bridge_map
r_typedef
r_struct
id|cb_bridge_map
(brace
DECL|member|map
id|u_char
id|map
suffix:semicolon
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|member|start
DECL|member|stop
id|u_int
id|start
comma
id|stop
suffix:semicolon
DECL|typedef|cb_bridge_map
)brace
id|cb_bridge_map
suffix:semicolon
multiline_comment|/*&n; * Socket operations.&n; */
r_struct
id|pcmcia_socket
suffix:semicolon
DECL|struct|pccard_operations
r_struct
id|pccard_operations
(brace
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
)paren
suffix:semicolon
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
)paren
suffix:semicolon
DECL|member|register_callback
r_int
(paren
op_star
id|register_callback
)paren
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
op_star
comma
r_int
r_int
)paren
comma
r_void
op_star
id|info
)paren
suffix:semicolon
DECL|member|get_status
r_int
(paren
op_star
id|get_status
)paren
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
id|u_int
op_star
id|value
)paren
suffix:semicolon
DECL|member|get_socket
r_int
(paren
op_star
id|get_socket
)paren
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
id|socket_state_t
op_star
id|state
)paren
suffix:semicolon
DECL|member|set_socket
r_int
(paren
op_star
id|set_socket
)paren
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
id|socket_state_t
op_star
id|state
)paren
suffix:semicolon
DECL|member|set_io_map
r_int
(paren
op_star
id|set_io_map
)paren
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
r_struct
id|pccard_io_map
op_star
id|io
)paren
suffix:semicolon
DECL|member|set_mem_map
r_int
(paren
op_star
id|set_mem_map
)paren
(paren
r_struct
id|pcmcia_socket
op_star
id|sock
comma
r_struct
id|pccard_mem_map
op_star
id|mem
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Calls to set up low-level &quot;Socket Services&quot; drivers&n; */
r_struct
id|pcmcia_socket
suffix:semicolon
DECL|struct|erase_busy_t
r_typedef
r_struct
id|erase_busy_t
(brace
DECL|member|erase
id|eraseq_entry_t
op_star
id|erase
suffix:semicolon
DECL|member|client
id|client_handle_t
id|client
suffix:semicolon
DECL|member|timeout
r_struct
id|timer_list
id|timeout
suffix:semicolon
DECL|member|prev
DECL|member|next
r_struct
id|erase_busy_t
op_star
id|prev
comma
op_star
id|next
suffix:semicolon
DECL|typedef|erase_busy_t
)brace
id|erase_busy_t
suffix:semicolon
DECL|struct|io_window_t
r_typedef
r_struct
id|io_window_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|BasePort
DECL|member|NumPorts
id|ioaddr_t
id|BasePort
comma
id|NumPorts
suffix:semicolon
DECL|member|InUse
DECL|member|Config
id|ioaddr_t
id|InUse
comma
id|Config
suffix:semicolon
DECL|member|res
r_struct
id|resource
op_star
id|res
suffix:semicolon
DECL|typedef|io_window_t
)brace
id|io_window_t
suffix:semicolon
DECL|macro|WINDOW_MAGIC
mdefine_line|#define WINDOW_MAGIC&t;0xB35C
DECL|struct|window_t
r_typedef
r_struct
id|window_t
(brace
DECL|member|magic
id|u_short
id|magic
suffix:semicolon
DECL|member|index
id|u_short
id|index
suffix:semicolon
DECL|member|handle
id|client_handle_t
id|handle
suffix:semicolon
DECL|member|sock
r_struct
id|pcmcia_socket
op_star
id|sock
suffix:semicolon
DECL|member|base
id|u_long
id|base
suffix:semicolon
DECL|member|size
id|u_long
id|size
suffix:semicolon
DECL|member|ctl
id|pccard_mem_map
id|ctl
suffix:semicolon
DECL|typedef|window_t
)brace
id|window_t
suffix:semicolon
multiline_comment|/* Maximum number of IO windows per socket */
DECL|macro|MAX_IO_WIN
mdefine_line|#define MAX_IO_WIN 2
multiline_comment|/* Maximum number of memory windows per socket */
DECL|macro|MAX_WIN
mdefine_line|#define MAX_WIN 4
r_struct
id|config_t
suffix:semicolon
r_struct
id|region_t
suffix:semicolon
DECL|struct|pcmcia_socket
r_struct
id|pcmcia_socket
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|socket
id|socket_state_t
id|socket
suffix:semicolon
DECL|member|state
id|u_int
id|state
suffix:semicolon
DECL|member|functions
id|u_short
id|functions
suffix:semicolon
DECL|member|lock_count
id|u_short
id|lock_count
suffix:semicolon
DECL|member|clients
id|client_handle_t
id|clients
suffix:semicolon
DECL|member|cis_mem
id|pccard_mem_map
id|cis_mem
suffix:semicolon
DECL|member|cis_virt
id|u_char
op_star
id|cis_virt
suffix:semicolon
DECL|member|config
r_struct
id|config_t
op_star
id|config
suffix:semicolon
r_struct
(brace
DECL|member|AssignedIRQ
id|u_int
id|AssignedIRQ
suffix:semicolon
DECL|member|Config
id|u_int
id|Config
suffix:semicolon
DECL|member|irq
)brace
id|irq
suffix:semicolon
DECL|member|io
id|io_window_t
id|io
(braket
id|MAX_IO_WIN
)braket
suffix:semicolon
DECL|member|win
id|window_t
id|win
(braket
id|MAX_WIN
)braket
suffix:semicolon
DECL|member|c_region
DECL|member|a_region
r_struct
id|region_t
op_star
id|c_region
comma
op_star
id|a_region
suffix:semicolon
DECL|member|erase_busy
id|erase_busy_t
id|erase_busy
suffix:semicolon
DECL|member|cis_cache
r_struct
id|list_head
id|cis_cache
suffix:semicolon
DECL|member|fake_cis_len
id|u_int
id|fake_cis_len
suffix:semicolon
DECL|member|fake_cis
r_char
op_star
id|fake_cis
suffix:semicolon
DECL|member|socket_list
r_struct
id|list_head
id|socket_list
suffix:semicolon
DECL|member|socket_released
r_struct
id|completion
id|socket_released
suffix:semicolon
multiline_comment|/* deprecated */
DECL|member|sock
r_int
r_int
id|sock
suffix:semicolon
multiline_comment|/* socket number */
multiline_comment|/* socket capabilities */
DECL|member|features
id|u_int
id|features
suffix:semicolon
DECL|member|irq_mask
id|u_int
id|irq_mask
suffix:semicolon
DECL|member|map_size
id|u_int
id|map_size
suffix:semicolon
DECL|member|io_offset
id|ioaddr_t
id|io_offset
suffix:semicolon
DECL|member|pci_irq
id|u_char
id|pci_irq
suffix:semicolon
DECL|member|cb_dev
r_struct
id|pci_dev
op_star
id|cb_dev
suffix:semicolon
multiline_comment|/* socket operations */
DECL|member|ops
r_struct
id|pccard_operations
op_star
id|ops
suffix:semicolon
multiline_comment|/* Zoom video behaviour is so chip specific its not worth adding&n;&t;   this to _ops */
DECL|member|zoom_video
r_void
(paren
op_star
id|zoom_video
)paren
(paren
r_struct
id|pcmcia_socket
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* state thread */
DECL|member|skt_sem
r_struct
id|semaphore
id|skt_sem
suffix:semicolon
multiline_comment|/* protects socket h/w state */
DECL|member|thread
r_struct
id|task_struct
op_star
id|thread
suffix:semicolon
DECL|member|thread_done
r_struct
id|completion
id|thread_done
suffix:semicolon
DECL|member|thread_wait
id|wait_queue_head_t
id|thread_wait
suffix:semicolon
DECL|member|thread_lock
id|spinlock_t
id|thread_lock
suffix:semicolon
multiline_comment|/* protects thread_events */
DECL|member|thread_events
r_int
r_int
id|thread_events
suffix:semicolon
multiline_comment|/* pcmcia (16-bit) */
DECL|member|pcmcia
r_struct
id|pcmcia_bus_socket
op_star
id|pcmcia
suffix:semicolon
multiline_comment|/* cardbus (32-bit) */
macro_line|#ifdef CONFIG_CARDBUS
DECL|member|cb_cis_res
r_struct
id|resource
op_star
id|cb_cis_res
suffix:semicolon
DECL|member|cb_cis_virt
id|u_char
op_star
id|cb_cis_virt
suffix:semicolon
macro_line|#endif
multiline_comment|/* socket device */
DECL|member|dev
r_struct
id|class_device
id|dev
suffix:semicolon
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
multiline_comment|/* data internal to the socket driver */
)brace
suffix:semicolon
r_struct
id|pcmcia_socket
op_star
id|pcmcia_get_socket_by_nr
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
r_extern
r_void
id|pcmcia_parse_events
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|socket
comma
r_int
r_int
id|events
)paren
suffix:semicolon
r_extern
r_int
id|pcmcia_register_socket
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|socket
)paren
suffix:semicolon
r_extern
r_void
id|pcmcia_unregister_socket
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|socket
)paren
suffix:semicolon
r_extern
r_struct
r_class
id|pcmcia_socket_class
suffix:semicolon
multiline_comment|/* socket drivers are expected to use these callbacks in their .drv struct */
r_extern
r_int
id|pcmcia_socket_dev_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
)paren
suffix:semicolon
r_extern
r_int
id|pcmcia_socket_dev_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_SS_H */
eof
