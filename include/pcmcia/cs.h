multiline_comment|/*&n; * cs.h 1.71 2000/08/29 00:54:20&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_CS_H
DECL|macro|_LINUX_CS_H
mdefine_line|#define _LINUX_CS_H
multiline_comment|/* For AccessConfigurationRegister */
DECL|struct|conf_reg_t
r_typedef
r_struct
id|conf_reg_t
(brace
DECL|member|Function
id|u_char
id|Function
suffix:semicolon
DECL|member|Action
id|u_int
id|Action
suffix:semicolon
DECL|member|Offset
id|off_t
id|Offset
suffix:semicolon
DECL|member|Value
id|u_int
id|Value
suffix:semicolon
DECL|typedef|conf_reg_t
)brace
id|conf_reg_t
suffix:semicolon
multiline_comment|/* Actions */
DECL|macro|CS_READ
mdefine_line|#define CS_READ&t;&t;1
DECL|macro|CS_WRITE
mdefine_line|#define CS_WRITE&t;2
multiline_comment|/* for AdjustResourceInfo */
DECL|struct|adjust_t
r_typedef
r_struct
id|adjust_t
(brace
DECL|member|Action
id|u_int
id|Action
suffix:semicolon
DECL|member|Resource
id|u_int
id|Resource
suffix:semicolon
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
r_union
(brace
DECL|struct|memory
r_struct
id|memory
(brace
DECL|member|Base
id|u_long
id|Base
suffix:semicolon
DECL|member|Size
id|u_long
id|Size
suffix:semicolon
DECL|member|memory
)brace
id|memory
suffix:semicolon
DECL|struct|io
r_struct
id|io
(brace
DECL|member|BasePort
id|ioaddr_t
id|BasePort
suffix:semicolon
DECL|member|NumPorts
id|ioaddr_t
id|NumPorts
suffix:semicolon
DECL|member|IOAddrLines
id|u_int
id|IOAddrLines
suffix:semicolon
DECL|member|io
)brace
id|io
suffix:semicolon
DECL|struct|irq
r_struct
id|irq
(brace
DECL|member|IRQ
id|u_int
id|IRQ
suffix:semicolon
DECL|member|irq
)brace
id|irq
suffix:semicolon
DECL|member|resource
)brace
id|resource
suffix:semicolon
DECL|typedef|adjust_t
)brace
id|adjust_t
suffix:semicolon
multiline_comment|/* Action field */
DECL|macro|REMOVE_MANAGED_RESOURCE
mdefine_line|#define REMOVE_MANAGED_RESOURCE&t;&t;1
DECL|macro|ADD_MANAGED_RESOURCE
mdefine_line|#define ADD_MANAGED_RESOURCE&t;&t;2
DECL|macro|GET_FIRST_MANAGED_RESOURCE
mdefine_line|#define GET_FIRST_MANAGED_RESOURCE&t;3
DECL|macro|GET_NEXT_MANAGED_RESOURCE
mdefine_line|#define GET_NEXT_MANAGED_RESOURCE&t;4
multiline_comment|/* Resource field */
DECL|macro|RES_MEMORY_RANGE
mdefine_line|#define RES_MEMORY_RANGE&t;&t;1
DECL|macro|RES_IO_RANGE
mdefine_line|#define RES_IO_RANGE&t;&t;&t;2
DECL|macro|RES_IRQ
mdefine_line|#define RES_IRQ&t;&t;&t;&t;3
multiline_comment|/* Attribute field */
DECL|macro|RES_IRQ_TYPE
mdefine_line|#define RES_IRQ_TYPE&t;&t;&t;0x03
DECL|macro|RES_IRQ_TYPE_EXCLUSIVE
mdefine_line|#define RES_IRQ_TYPE_EXCLUSIVE&t;&t;0
DECL|macro|RES_IRQ_TYPE_TIME
mdefine_line|#define RES_IRQ_TYPE_TIME&t;&t;1
DECL|macro|RES_IRQ_TYPE_DYNAMIC
mdefine_line|#define RES_IRQ_TYPE_DYNAMIC&t;&t;2
DECL|macro|RES_IRQ_CSC
mdefine_line|#define RES_IRQ_CSC&t;&t;&t;0x04
DECL|macro|RES_SHARED
mdefine_line|#define RES_SHARED&t;&t;&t;0x08
DECL|macro|RES_RESERVED
mdefine_line|#define RES_RESERVED&t;&t;&t;0x10
DECL|macro|RES_ALLOCATED
mdefine_line|#define RES_ALLOCATED&t;&t;&t;0x20
DECL|macro|RES_REMOVED
mdefine_line|#define RES_REMOVED&t;&t;&t;0x40
DECL|struct|servinfo_t
r_typedef
r_struct
id|servinfo_t
(brace
DECL|member|Signature
r_char
id|Signature
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|Count
id|u_int
id|Count
suffix:semicolon
DECL|member|Revision
id|u_int
id|Revision
suffix:semicolon
DECL|member|CSLevel
id|u_int
id|CSLevel
suffix:semicolon
DECL|member|VendorString
r_char
op_star
id|VendorString
suffix:semicolon
DECL|typedef|servinfo_t
)brace
id|servinfo_t
suffix:semicolon
DECL|struct|event_callback_args_t
r_typedef
r_struct
id|event_callback_args_t
(brace
DECL|member|client_handle
id|client_handle_t
id|client_handle
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|mtdrequest
r_void
op_star
id|mtdrequest
suffix:semicolon
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
DECL|member|misc
r_void
op_star
id|misc
suffix:semicolon
DECL|member|client_data
r_void
op_star
id|client_data
suffix:semicolon
DECL|member|bus
r_struct
id|bus_operations
op_star
id|bus
suffix:semicolon
DECL|typedef|event_callback_args_t
)brace
id|event_callback_args_t
suffix:semicolon
multiline_comment|/* for GetConfigurationInfo */
DECL|struct|config_info_t
r_typedef
r_struct
id|config_info_t
(brace
DECL|member|Function
id|u_char
id|Function
suffix:semicolon
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|Vcc
DECL|member|Vpp1
DECL|member|Vpp2
id|u_int
id|Vcc
comma
id|Vpp1
comma
id|Vpp2
suffix:semicolon
DECL|member|IntType
id|u_int
id|IntType
suffix:semicolon
DECL|member|ConfigBase
id|u_int
id|ConfigBase
suffix:semicolon
DECL|member|Status
DECL|member|Pin
DECL|member|Copy
DECL|member|Option
DECL|member|ExtStatus
id|u_char
id|Status
comma
id|Pin
comma
id|Copy
comma
id|Option
comma
id|ExtStatus
suffix:semicolon
DECL|member|Present
id|u_int
id|Present
suffix:semicolon
DECL|member|CardValues
id|u_int
id|CardValues
suffix:semicolon
DECL|member|AssignedIRQ
id|u_int
id|AssignedIRQ
suffix:semicolon
DECL|member|IRQAttributes
id|u_int
id|IRQAttributes
suffix:semicolon
DECL|member|BasePort1
id|ioaddr_t
id|BasePort1
suffix:semicolon
DECL|member|NumPorts1
id|ioaddr_t
id|NumPorts1
suffix:semicolon
DECL|member|Attributes1
id|u_int
id|Attributes1
suffix:semicolon
DECL|member|BasePort2
id|ioaddr_t
id|BasePort2
suffix:semicolon
DECL|member|NumPorts2
id|ioaddr_t
id|NumPorts2
suffix:semicolon
DECL|member|Attributes2
id|u_int
id|Attributes2
suffix:semicolon
DECL|member|IOAddrLines
id|u_int
id|IOAddrLines
suffix:semicolon
DECL|typedef|config_info_t
)brace
id|config_info_t
suffix:semicolon
multiline_comment|/* For CardValues field */
DECL|macro|CV_OPTION_VALUE
mdefine_line|#define CV_OPTION_VALUE&t;&t;0x01
DECL|macro|CV_STATUS_VALUE
mdefine_line|#define CV_STATUS_VALUE&t;&t;0x02
DECL|macro|CV_PIN_REPLACEMENT
mdefine_line|#define CV_PIN_REPLACEMENT&t;0x04
DECL|macro|CV_COPY_VALUE
mdefine_line|#define CV_COPY_VALUE&t;&t;0x08
DECL|macro|CV_EXT_STATUS
mdefine_line|#define CV_EXT_STATUS&t;&t;0x10
multiline_comment|/* For GetFirst/NextClient */
DECL|struct|client_req_t
r_typedef
r_struct
id|client_req_t
(brace
DECL|member|Socket
id|socket_t
id|Socket
suffix:semicolon
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|typedef|client_req_t
)brace
id|client_req_t
suffix:semicolon
DECL|macro|CLIENT_THIS_SOCKET
mdefine_line|#define CLIENT_THIS_SOCKET&t;0x01
multiline_comment|/* For RegisterClient */
DECL|struct|client_reg_t
r_typedef
r_struct
id|client_reg_t
(brace
DECL|member|dev_info
id|dev_info_t
op_star
id|dev_info
suffix:semicolon
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|EventMask
id|u_int
id|EventMask
suffix:semicolon
DECL|member|event_handler
r_int
(paren
op_star
id|event_handler
)paren
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
)paren
suffix:semicolon
DECL|member|event_callback_args
id|event_callback_args_t
id|event_callback_args
suffix:semicolon
DECL|member|Version
id|u_int
id|Version
suffix:semicolon
DECL|typedef|client_reg_t
)brace
id|client_reg_t
suffix:semicolon
multiline_comment|/* ModifyConfiguration */
DECL|struct|modconf_t
r_typedef
r_struct
id|modconf_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|Vcc
DECL|member|Vpp1
DECL|member|Vpp2
id|u_int
id|Vcc
comma
id|Vpp1
comma
id|Vpp2
suffix:semicolon
DECL|typedef|modconf_t
)brace
id|modconf_t
suffix:semicolon
multiline_comment|/* Attributes for ModifyConfiguration */
DECL|macro|CONF_IRQ_CHANGE_VALID
mdefine_line|#define CONF_IRQ_CHANGE_VALID&t;0x100
DECL|macro|CONF_VCC_CHANGE_VALID
mdefine_line|#define CONF_VCC_CHANGE_VALID&t;0x200
DECL|macro|CONF_VPP1_CHANGE_VALID
mdefine_line|#define CONF_VPP1_CHANGE_VALID&t;0x400
DECL|macro|CONF_VPP2_CHANGE_VALID
mdefine_line|#define CONF_VPP2_CHANGE_VALID&t;0x800
multiline_comment|/* For RequestConfiguration */
DECL|struct|config_req_t
r_typedef
r_struct
id|config_req_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|Vcc
DECL|member|Vpp1
DECL|member|Vpp2
id|u_int
id|Vcc
comma
id|Vpp1
comma
id|Vpp2
suffix:semicolon
DECL|member|IntType
id|u_int
id|IntType
suffix:semicolon
DECL|member|ConfigBase
id|u_int
id|ConfigBase
suffix:semicolon
DECL|member|Status
DECL|member|Pin
DECL|member|Copy
DECL|member|ExtStatus
id|u_char
id|Status
comma
id|Pin
comma
id|Copy
comma
id|ExtStatus
suffix:semicolon
DECL|member|ConfigIndex
id|u_char
id|ConfigIndex
suffix:semicolon
DECL|member|Present
id|u_int
id|Present
suffix:semicolon
DECL|typedef|config_req_t
)brace
id|config_req_t
suffix:semicolon
multiline_comment|/* Attributes for RequestConfiguration */
DECL|macro|CONF_ENABLE_IRQ
mdefine_line|#define CONF_ENABLE_IRQ&t;&t;0x01
DECL|macro|CONF_ENABLE_DMA
mdefine_line|#define CONF_ENABLE_DMA&t;&t;0x02
DECL|macro|CONF_ENABLE_SPKR
mdefine_line|#define CONF_ENABLE_SPKR&t;0x04
DECL|macro|CONF_VALID_CLIENT
mdefine_line|#define CONF_VALID_CLIENT&t;0x100
multiline_comment|/* IntType field */
DECL|macro|INT_MEMORY
mdefine_line|#define INT_MEMORY&t;&t;0x01
DECL|macro|INT_MEMORY_AND_IO
mdefine_line|#define INT_MEMORY_AND_IO&t;0x02
DECL|macro|INT_CARDBUS
mdefine_line|#define INT_CARDBUS&t;&t;0x04
multiline_comment|/* For RequestIO and ReleaseIO */
DECL|struct|io_req_t
r_typedef
r_struct
id|io_req_t
(brace
DECL|member|BasePort1
id|ioaddr_t
id|BasePort1
suffix:semicolon
DECL|member|NumPorts1
id|ioaddr_t
id|NumPorts1
suffix:semicolon
DECL|member|Attributes1
id|u_int
id|Attributes1
suffix:semicolon
DECL|member|BasePort2
id|ioaddr_t
id|BasePort2
suffix:semicolon
DECL|member|NumPorts2
id|ioaddr_t
id|NumPorts2
suffix:semicolon
DECL|member|Attributes2
id|u_int
id|Attributes2
suffix:semicolon
DECL|member|IOAddrLines
id|u_int
id|IOAddrLines
suffix:semicolon
DECL|typedef|io_req_t
)brace
id|io_req_t
suffix:semicolon
multiline_comment|/* Attributes for RequestIO and ReleaseIO */
DECL|macro|IO_SHARED
mdefine_line|#define IO_SHARED&t;&t;0x01
DECL|macro|IO_FIRST_SHARED
mdefine_line|#define IO_FIRST_SHARED&t;&t;0x02
DECL|macro|IO_FORCE_ALIAS_ACCESS
mdefine_line|#define IO_FORCE_ALIAS_ACCESS&t;0x04
DECL|macro|IO_DATA_PATH_WIDTH
mdefine_line|#define IO_DATA_PATH_WIDTH&t;0x18
DECL|macro|IO_DATA_PATH_WIDTH_8
mdefine_line|#define IO_DATA_PATH_WIDTH_8&t;0x00
DECL|macro|IO_DATA_PATH_WIDTH_16
mdefine_line|#define IO_DATA_PATH_WIDTH_16&t;0x08
DECL|macro|IO_DATA_PATH_WIDTH_AUTO
mdefine_line|#define IO_DATA_PATH_WIDTH_AUTO&t;0x10
multiline_comment|/* For RequestIRQ and ReleaseIRQ */
DECL|struct|irq_req_t
r_typedef
r_struct
id|irq_req_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|AssignedIRQ
id|u_int
id|AssignedIRQ
suffix:semicolon
DECL|member|IRQInfo1
DECL|member|IRQInfo2
id|u_int
id|IRQInfo1
comma
id|IRQInfo2
suffix:semicolon
DECL|member|Handler
r_void
op_star
id|Handler
suffix:semicolon
DECL|member|Instance
r_void
op_star
id|Instance
suffix:semicolon
DECL|typedef|irq_req_t
)brace
id|irq_req_t
suffix:semicolon
multiline_comment|/* Attributes for RequestIRQ and ReleaseIRQ */
DECL|macro|IRQ_TYPE
mdefine_line|#define IRQ_TYPE&t;&t;&t;0x03
DECL|macro|IRQ_TYPE_EXCLUSIVE
mdefine_line|#define IRQ_TYPE_EXCLUSIVE&t;&t;0x00
DECL|macro|IRQ_TYPE_TIME
mdefine_line|#define IRQ_TYPE_TIME&t;&t;&t;0x01
DECL|macro|IRQ_TYPE_DYNAMIC_SHARING
mdefine_line|#define IRQ_TYPE_DYNAMIC_SHARING&t;0x02
DECL|macro|IRQ_FORCED_PULSE
mdefine_line|#define IRQ_FORCED_PULSE&t;&t;0x04
DECL|macro|IRQ_FIRST_SHARED
mdefine_line|#define IRQ_FIRST_SHARED&t;&t;0x08
DECL|macro|IRQ_HANDLE_PRESENT
mdefine_line|#define IRQ_HANDLE_PRESENT&t;&t;0x10
DECL|macro|IRQ_PULSE_ALLOCATED
mdefine_line|#define IRQ_PULSE_ALLOCATED&t;&t;0x100
multiline_comment|/* Bits in IRQInfo1 field */
DECL|macro|IRQ_MASK
mdefine_line|#define IRQ_MASK&t;&t;0x0f
DECL|macro|IRQ_NMI_ID
mdefine_line|#define IRQ_NMI_ID&t;&t;0x01
DECL|macro|IRQ_IOCK_ID
mdefine_line|#define IRQ_IOCK_ID&t;&t;0x02
DECL|macro|IRQ_BERR_ID
mdefine_line|#define IRQ_BERR_ID&t;&t;0x04
DECL|macro|IRQ_VEND_ID
mdefine_line|#define IRQ_VEND_ID&t;&t;0x08
DECL|macro|IRQ_INFO2_VALID
mdefine_line|#define IRQ_INFO2_VALID&t;&t;0x10
DECL|macro|IRQ_LEVEL_ID
mdefine_line|#define IRQ_LEVEL_ID&t;&t;0x20
DECL|macro|IRQ_PULSE_ID
mdefine_line|#define IRQ_PULSE_ID&t;&t;0x40
DECL|macro|IRQ_SHARE_ID
mdefine_line|#define IRQ_SHARE_ID&t;&t;0x80
DECL|struct|eventmask_t
r_typedef
r_struct
id|eventmask_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|EventMask
id|u_int
id|EventMask
suffix:semicolon
DECL|typedef|eventmask_t
)brace
id|eventmask_t
suffix:semicolon
DECL|macro|CONF_EVENT_MASK_VALID
mdefine_line|#define CONF_EVENT_MASK_VALID&t;0x01
multiline_comment|/* Configuration registers present */
DECL|macro|PRESENT_OPTION
mdefine_line|#define PRESENT_OPTION&t;&t;0x001
DECL|macro|PRESENT_STATUS
mdefine_line|#define PRESENT_STATUS&t;&t;0x002
DECL|macro|PRESENT_PIN_REPLACE
mdefine_line|#define PRESENT_PIN_REPLACE&t;0x004
DECL|macro|PRESENT_COPY
mdefine_line|#define PRESENT_COPY&t;&t;0x008
DECL|macro|PRESENT_EXT_STATUS
mdefine_line|#define PRESENT_EXT_STATUS&t;0x010
DECL|macro|PRESENT_IOBASE_0
mdefine_line|#define PRESENT_IOBASE_0&t;0x020
DECL|macro|PRESENT_IOBASE_1
mdefine_line|#define PRESENT_IOBASE_1&t;0x040
DECL|macro|PRESENT_IOBASE_2
mdefine_line|#define PRESENT_IOBASE_2&t;0x080
DECL|macro|PRESENT_IOBASE_3
mdefine_line|#define PRESENT_IOBASE_3&t;0x100
DECL|macro|PRESENT_IOSIZE
mdefine_line|#define PRESENT_IOSIZE&t;&t;0x200
multiline_comment|/* For GetMemPage, MapMemPage */
DECL|struct|memreq_t
r_typedef
r_struct
id|memreq_t
(brace
DECL|member|CardOffset
id|u_int
id|CardOffset
suffix:semicolon
DECL|member|Page
id|page_t
id|Page
suffix:semicolon
DECL|typedef|memreq_t
)brace
id|memreq_t
suffix:semicolon
multiline_comment|/* For ModifyWindow */
DECL|struct|modwin_t
r_typedef
r_struct
id|modwin_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|AccessSpeed
id|u_int
id|AccessSpeed
suffix:semicolon
DECL|typedef|modwin_t
)brace
id|modwin_t
suffix:semicolon
multiline_comment|/* For RequestWindow */
DECL|struct|win_req_t
r_typedef
r_struct
id|win_req_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|Base
id|u_long
id|Base
suffix:semicolon
DECL|member|Size
id|u_int
id|Size
suffix:semicolon
DECL|member|AccessSpeed
id|u_int
id|AccessSpeed
suffix:semicolon
DECL|typedef|win_req_t
)brace
id|win_req_t
suffix:semicolon
multiline_comment|/* Attributes for RequestWindow */
DECL|macro|WIN_ADDR_SPACE
mdefine_line|#define WIN_ADDR_SPACE&t;&t;0x0001
DECL|macro|WIN_ADDR_SPACE_MEM
mdefine_line|#define WIN_ADDR_SPACE_MEM&t;0x0000
DECL|macro|WIN_ADDR_SPACE_IO
mdefine_line|#define WIN_ADDR_SPACE_IO&t;0x0001
DECL|macro|WIN_MEMORY_TYPE
mdefine_line|#define WIN_MEMORY_TYPE&t;&t;0x0002
DECL|macro|WIN_MEMORY_TYPE_CM
mdefine_line|#define WIN_MEMORY_TYPE_CM&t;0x0000
DECL|macro|WIN_MEMORY_TYPE_AM
mdefine_line|#define WIN_MEMORY_TYPE_AM&t;0x0002
DECL|macro|WIN_ENABLE
mdefine_line|#define WIN_ENABLE&t;&t;0x0004
DECL|macro|WIN_DATA_WIDTH
mdefine_line|#define WIN_DATA_WIDTH&t;&t;0x0018
DECL|macro|WIN_DATA_WIDTH_8
mdefine_line|#define WIN_DATA_WIDTH_8&t;0x0000
DECL|macro|WIN_DATA_WIDTH_16
mdefine_line|#define WIN_DATA_WIDTH_16&t;0x0008
DECL|macro|WIN_DATA_WIDTH_32
mdefine_line|#define WIN_DATA_WIDTH_32&t;0x0010
DECL|macro|WIN_PAGED
mdefine_line|#define WIN_PAGED&t;&t;0x0020
DECL|macro|WIN_SHARED
mdefine_line|#define WIN_SHARED&t;&t;0x0040
DECL|macro|WIN_FIRST_SHARED
mdefine_line|#define WIN_FIRST_SHARED&t;0x0080
DECL|macro|WIN_USE_WAIT
mdefine_line|#define WIN_USE_WAIT&t;&t;0x0100
DECL|macro|WIN_STRICT_ALIGN
mdefine_line|#define WIN_STRICT_ALIGN&t;0x0200
DECL|macro|WIN_MAP_BELOW_1MB
mdefine_line|#define WIN_MAP_BELOW_1MB&t;0x0400
DECL|macro|WIN_PREFETCH
mdefine_line|#define WIN_PREFETCH&t;&t;0x0800
DECL|macro|WIN_CACHEABLE
mdefine_line|#define WIN_CACHEABLE&t;&t;0x1000
DECL|macro|WIN_BAR_MASK
mdefine_line|#define WIN_BAR_MASK&t;&t;0xe000
DECL|macro|WIN_BAR_SHIFT
mdefine_line|#define WIN_BAR_SHIFT&t;&t;13
multiline_comment|/* Attributes for RegisterClient */
DECL|macro|INFO_MASTER_CLIENT
mdefine_line|#define INFO_MASTER_CLIENT&t;0x01
DECL|macro|INFO_IO_CLIENT
mdefine_line|#define INFO_IO_CLIENT&t;&t;0x02
DECL|macro|INFO_MTD_CLIENT
mdefine_line|#define INFO_MTD_CLIENT&t;&t;0x04
DECL|macro|INFO_MEM_CLIENT
mdefine_line|#define INFO_MEM_CLIENT&t;&t;0x08
DECL|macro|MAX_NUM_CLIENTS
mdefine_line|#define MAX_NUM_CLIENTS&t;&t;3
DECL|macro|INFO_CARD_SHARE
mdefine_line|#define INFO_CARD_SHARE&t;&t;0x10
DECL|macro|INFO_CARD_EXCL
mdefine_line|#define INFO_CARD_EXCL&t;&t;0x20
DECL|struct|cs_status_t
r_typedef
r_struct
id|cs_status_t
(brace
DECL|member|Function
id|u_char
id|Function
suffix:semicolon
DECL|member|CardState
id|event_t
id|CardState
suffix:semicolon
DECL|member|SocketState
id|event_t
id|SocketState
suffix:semicolon
DECL|typedef|cs_status_t
)brace
id|cs_status_t
suffix:semicolon
DECL|struct|error_info_t
r_typedef
r_struct
id|error_info_t
(brace
DECL|member|func
r_int
id|func
suffix:semicolon
DECL|member|retcode
r_int
id|retcode
suffix:semicolon
DECL|typedef|error_info_t
)brace
id|error_info_t
suffix:semicolon
multiline_comment|/* Special stuff for binding drivers to sockets */
DECL|struct|bind_req_t
r_typedef
r_struct
id|bind_req_t
(brace
DECL|member|Socket
id|socket_t
id|Socket
suffix:semicolon
DECL|member|Function
id|u_char
id|Function
suffix:semicolon
DECL|member|dev_info
id|dev_info_t
op_star
id|dev_info
suffix:semicolon
DECL|typedef|bind_req_t
)brace
id|bind_req_t
suffix:semicolon
multiline_comment|/* Flag to bind to all functions */
DECL|macro|BIND_FN_ALL
mdefine_line|#define BIND_FN_ALL&t;0xff
DECL|struct|mtd_bind_t
r_typedef
r_struct
id|mtd_bind_t
(brace
DECL|member|Socket
id|socket_t
id|Socket
suffix:semicolon
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|CardOffset
id|u_int
id|CardOffset
suffix:semicolon
DECL|member|dev_info
id|dev_info_t
op_star
id|dev_info
suffix:semicolon
DECL|typedef|mtd_bind_t
)brace
id|mtd_bind_t
suffix:semicolon
multiline_comment|/* Events */
DECL|macro|CS_EVENT_PRI_LOW
mdefine_line|#define CS_EVENT_PRI_LOW&t;&t;0
DECL|macro|CS_EVENT_PRI_HIGH
mdefine_line|#define CS_EVENT_PRI_HIGH&t;&t;1
DECL|macro|CS_EVENT_WRITE_PROTECT
mdefine_line|#define CS_EVENT_WRITE_PROTECT&t;&t;0x000001
DECL|macro|CS_EVENT_CARD_LOCK
mdefine_line|#define CS_EVENT_CARD_LOCK&t;&t;0x000002
DECL|macro|CS_EVENT_CARD_INSERTION
mdefine_line|#define CS_EVENT_CARD_INSERTION&t;&t;0x000004
DECL|macro|CS_EVENT_CARD_REMOVAL
mdefine_line|#define CS_EVENT_CARD_REMOVAL&t;&t;0x000008
DECL|macro|CS_EVENT_BATTERY_DEAD
mdefine_line|#define CS_EVENT_BATTERY_DEAD&t;&t;0x000010
DECL|macro|CS_EVENT_BATTERY_LOW
mdefine_line|#define CS_EVENT_BATTERY_LOW&t;&t;0x000020
DECL|macro|CS_EVENT_READY_CHANGE
mdefine_line|#define CS_EVENT_READY_CHANGE&t;&t;0x000040
DECL|macro|CS_EVENT_CARD_DETECT
mdefine_line|#define CS_EVENT_CARD_DETECT&t;&t;0x000080
DECL|macro|CS_EVENT_RESET_REQUEST
mdefine_line|#define CS_EVENT_RESET_REQUEST&t;&t;0x000100
DECL|macro|CS_EVENT_RESET_PHYSICAL
mdefine_line|#define CS_EVENT_RESET_PHYSICAL&t;&t;0x000200
DECL|macro|CS_EVENT_CARD_RESET
mdefine_line|#define CS_EVENT_CARD_RESET&t;&t;0x000400
DECL|macro|CS_EVENT_REGISTRATION_COMPLETE
mdefine_line|#define CS_EVENT_REGISTRATION_COMPLETE&t;0x000800
DECL|macro|CS_EVENT_RESET_COMPLETE
mdefine_line|#define CS_EVENT_RESET_COMPLETE&t;&t;0x001000
DECL|macro|CS_EVENT_PM_SUSPEND
mdefine_line|#define CS_EVENT_PM_SUSPEND&t;&t;0x002000
DECL|macro|CS_EVENT_PM_RESUME
mdefine_line|#define CS_EVENT_PM_RESUME&t;&t;0x004000
DECL|macro|CS_EVENT_INSERTION_REQUEST
mdefine_line|#define CS_EVENT_INSERTION_REQUEST&t;0x008000
DECL|macro|CS_EVENT_EJECTION_REQUEST
mdefine_line|#define CS_EVENT_EJECTION_REQUEST&t;0x010000
DECL|macro|CS_EVENT_MTD_REQUEST
mdefine_line|#define CS_EVENT_MTD_REQUEST&t;&t;0x020000
DECL|macro|CS_EVENT_ERASE_COMPLETE
mdefine_line|#define CS_EVENT_ERASE_COMPLETE&t;&t;0x040000
DECL|macro|CS_EVENT_REQUEST_ATTENTION
mdefine_line|#define CS_EVENT_REQUEST_ATTENTION&t;0x080000
DECL|macro|CS_EVENT_CB_DETECT
mdefine_line|#define CS_EVENT_CB_DETECT&t;&t;0x100000
DECL|macro|CS_EVENT_3VCARD
mdefine_line|#define CS_EVENT_3VCARD&t;&t;&t;0x200000
DECL|macro|CS_EVENT_XVCARD
mdefine_line|#define CS_EVENT_XVCARD&t;&t;&t;0x400000
multiline_comment|/* Return codes */
DECL|macro|CS_SUCCESS
mdefine_line|#define CS_SUCCESS&t;&t;0x00
DECL|macro|CS_BAD_ADAPTER
mdefine_line|#define CS_BAD_ADAPTER&t;&t;0x01
DECL|macro|CS_BAD_ATTRIBUTE
mdefine_line|#define CS_BAD_ATTRIBUTE&t;0x02
DECL|macro|CS_BAD_BASE
mdefine_line|#define CS_BAD_BASE&t;&t;0x03
DECL|macro|CS_BAD_EDC
mdefine_line|#define CS_BAD_EDC&t;&t;0x04
DECL|macro|CS_BAD_IRQ
mdefine_line|#define CS_BAD_IRQ&t;&t;0x06
DECL|macro|CS_BAD_OFFSET
mdefine_line|#define CS_BAD_OFFSET&t;&t;0x07
DECL|macro|CS_BAD_PAGE
mdefine_line|#define CS_BAD_PAGE&t;&t;0x08
DECL|macro|CS_READ_FAILURE
mdefine_line|#define CS_READ_FAILURE&t;&t;0x09
DECL|macro|CS_BAD_SIZE
mdefine_line|#define CS_BAD_SIZE&t;&t;0x0a
DECL|macro|CS_BAD_SOCKET
mdefine_line|#define CS_BAD_SOCKET&t;&t;0x0b
DECL|macro|CS_BAD_TYPE
mdefine_line|#define CS_BAD_TYPE&t;&t;0x0d
DECL|macro|CS_BAD_VCC
mdefine_line|#define CS_BAD_VCC&t;&t;0x0e
DECL|macro|CS_BAD_VPP
mdefine_line|#define CS_BAD_VPP&t;&t;0x0f
DECL|macro|CS_BAD_WINDOW
mdefine_line|#define CS_BAD_WINDOW&t;&t;0x11
DECL|macro|CS_WRITE_FAILURE
mdefine_line|#define CS_WRITE_FAILURE&t;0x12
DECL|macro|CS_NO_CARD
mdefine_line|#define CS_NO_CARD&t;&t;0x14
DECL|macro|CS_UNSUPPORTED_FUNCTION
mdefine_line|#define CS_UNSUPPORTED_FUNCTION&t;0x15
DECL|macro|CS_UNSUPPORTED_MODE
mdefine_line|#define CS_UNSUPPORTED_MODE&t;0x16
DECL|macro|CS_BAD_SPEED
mdefine_line|#define CS_BAD_SPEED&t;&t;0x17
DECL|macro|CS_BUSY
mdefine_line|#define CS_BUSY&t;&t;&t;0x18
DECL|macro|CS_GENERAL_FAILURE
mdefine_line|#define CS_GENERAL_FAILURE&t;0x19
DECL|macro|CS_WRITE_PROTECTED
mdefine_line|#define CS_WRITE_PROTECTED&t;0x1a
DECL|macro|CS_BAD_ARG_LENGTH
mdefine_line|#define CS_BAD_ARG_LENGTH&t;0x1b
DECL|macro|CS_BAD_ARGS
mdefine_line|#define CS_BAD_ARGS&t;&t;0x1c
DECL|macro|CS_CONFIGURATION_LOCKED
mdefine_line|#define CS_CONFIGURATION_LOCKED&t;0x1d
DECL|macro|CS_IN_USE
mdefine_line|#define CS_IN_USE&t;&t;0x1e
DECL|macro|CS_NO_MORE_ITEMS
mdefine_line|#define CS_NO_MORE_ITEMS&t;0x1f
DECL|macro|CS_OUT_OF_RESOURCE
mdefine_line|#define CS_OUT_OF_RESOURCE&t;0x20
DECL|macro|CS_BAD_HANDLE
mdefine_line|#define CS_BAD_HANDLE&t;&t;0x21
DECL|macro|CS_BAD_TUPLE
mdefine_line|#define CS_BAD_TUPLE&t;&t;0x40
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; *  The main Card Services entry point&n; */
DECL|enum|service
r_enum
id|service
(brace
DECL|enumerator|AccessConfigurationRegister
DECL|enumerator|AddSocketServices
id|AccessConfigurationRegister
comma
id|AddSocketServices
comma
DECL|enumerator|AdjustResourceInfo
DECL|enumerator|CheckEraseQueue
DECL|enumerator|CloseMemory
DECL|enumerator|CopyMemory
id|AdjustResourceInfo
comma
id|CheckEraseQueue
comma
id|CloseMemory
comma
id|CopyMemory
comma
DECL|enumerator|DeregisterClient
DECL|enumerator|DeregisterEraseQueue
DECL|enumerator|GetCardServicesInfo
id|DeregisterClient
comma
id|DeregisterEraseQueue
comma
id|GetCardServicesInfo
comma
DECL|enumerator|GetClientInfo
DECL|enumerator|GetConfigurationInfo
DECL|enumerator|GetEventMask
id|GetClientInfo
comma
id|GetConfigurationInfo
comma
id|GetEventMask
comma
DECL|enumerator|GetFirstClient
DECL|enumerator|GetFirstPartion
DECL|enumerator|GetFirstRegion
DECL|enumerator|GetFirstTuple
id|GetFirstClient
comma
id|GetFirstPartion
comma
id|GetFirstRegion
comma
id|GetFirstTuple
comma
DECL|enumerator|GetNextClient
DECL|enumerator|GetNextPartition
DECL|enumerator|GetNextRegion
DECL|enumerator|GetNextTuple
id|GetNextClient
comma
id|GetNextPartition
comma
id|GetNextRegion
comma
id|GetNextTuple
comma
DECL|enumerator|GetStatus
DECL|enumerator|GetTupleData
DECL|enumerator|MapLogSocket
DECL|enumerator|MapLogWindow
DECL|enumerator|MapMemPage
id|GetStatus
comma
id|GetTupleData
comma
id|MapLogSocket
comma
id|MapLogWindow
comma
id|MapMemPage
comma
DECL|enumerator|MapPhySocket
DECL|enumerator|MapPhyWindow
DECL|enumerator|ModifyConfiguration
DECL|enumerator|ModifyWindow
id|MapPhySocket
comma
id|MapPhyWindow
comma
id|ModifyConfiguration
comma
id|ModifyWindow
comma
DECL|enumerator|OpenMemory
DECL|enumerator|ParseTuple
DECL|enumerator|ReadMemory
DECL|enumerator|RegisterClient
id|OpenMemory
comma
id|ParseTuple
comma
id|ReadMemory
comma
id|RegisterClient
comma
DECL|enumerator|RegisterEraseQueue
DECL|enumerator|RegisterMTD
DECL|enumerator|RegisterTimer
id|RegisterEraseQueue
comma
id|RegisterMTD
comma
id|RegisterTimer
comma
DECL|enumerator|ReleaseConfiguration
DECL|enumerator|ReleaseExclusive
DECL|enumerator|ReleaseIO
DECL|enumerator|ReleaseIRQ
id|ReleaseConfiguration
comma
id|ReleaseExclusive
comma
id|ReleaseIO
comma
id|ReleaseIRQ
comma
DECL|enumerator|ReleaseSocketMask
DECL|enumerator|ReleaseWindow
DECL|enumerator|ReplaceSocketServices
id|ReleaseSocketMask
comma
id|ReleaseWindow
comma
id|ReplaceSocketServices
comma
DECL|enumerator|RequestConfiguration
DECL|enumerator|RequestExclusive
DECL|enumerator|RequestIO
DECL|enumerator|RequestIRQ
id|RequestConfiguration
comma
id|RequestExclusive
comma
id|RequestIO
comma
id|RequestIRQ
comma
DECL|enumerator|RequestSocketMask
DECL|enumerator|RequestWindow
DECL|enumerator|ResetCard
DECL|enumerator|ReturnSSEntry
id|RequestSocketMask
comma
id|RequestWindow
comma
id|ResetCard
comma
id|ReturnSSEntry
comma
DECL|enumerator|SetEventMask
DECL|enumerator|SetRegion
DECL|enumerator|ValidateCIS
DECL|enumerator|VendorSpecific
id|SetEventMask
comma
id|SetRegion
comma
id|ValidateCIS
comma
id|VendorSpecific
comma
DECL|enumerator|WriteMemory
DECL|enumerator|BindDevice
DECL|enumerator|BindMTD
DECL|enumerator|ReportError
id|WriteMemory
comma
id|BindDevice
comma
id|BindMTD
comma
id|ReportError
comma
DECL|enumerator|SuspendCard
DECL|enumerator|ResumeCard
DECL|enumerator|EjectCard
DECL|enumerator|InsertCard
DECL|enumerator|ReplaceCIS
id|SuspendCard
comma
id|ResumeCard
comma
id|EjectCard
comma
id|InsertCard
comma
id|ReplaceCIS
comma
DECL|enumerator|GetFirstWindow
DECL|enumerator|GetNextWindow
DECL|enumerator|GetMemPage
id|GetFirstWindow
comma
id|GetNextWindow
comma
id|GetMemPage
)brace
suffix:semicolon
macro_line|#ifdef IN_CARD_SERVICES
r_extern
r_int
id|CardServices
c_func
(paren
r_int
id|func
comma
r_void
op_star
id|a1
comma
r_void
op_star
id|a2
comma
r_void
op_star
id|a3
)paren
suffix:semicolon
macro_line|#else
r_extern
r_int
id|CardServices
c_func
(paren
r_int
id|func
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#endif
r_int
id|pcmcia_access_configuration_register
c_func
(paren
id|client_handle_t
id|handle
comma
id|conf_reg_t
op_star
id|reg
)paren
suffix:semicolon
r_int
id|pcmcia_bind_device
c_func
(paren
id|bind_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_bind_mtd
c_func
(paren
id|mtd_bind_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_deregister_client
c_func
(paren
id|client_handle_t
id|handle
)paren
suffix:semicolon
r_int
id|pcmcia_get_configuration_info
c_func
(paren
id|client_handle_t
id|handle
comma
id|config_info_t
op_star
id|config
)paren
suffix:semicolon
r_int
id|pcmcia_get_card_services_info
c_func
(paren
id|servinfo_t
op_star
id|info
)paren
suffix:semicolon
r_int
id|pcmcia_get_first_client
c_func
(paren
id|client_handle_t
op_star
id|handle
comma
id|client_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_get_next_client
c_func
(paren
id|client_handle_t
op_star
id|handle
comma
id|client_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_get_window
c_func
(paren
id|window_handle_t
op_star
id|handle
comma
r_int
id|idx
comma
id|win_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_get_first_window
c_func
(paren
id|window_handle_t
op_star
id|win
comma
id|win_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_get_next_window
c_func
(paren
id|window_handle_t
op_star
id|win
comma
id|win_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_get_status
c_func
(paren
id|client_handle_t
id|handle
comma
id|cs_status_t
op_star
id|status
)paren
suffix:semicolon
r_int
id|pcmcia_get_mem_page
c_func
(paren
id|window_handle_t
id|win
comma
id|memreq_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_map_mem_page
c_func
(paren
id|window_handle_t
id|win
comma
id|memreq_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_modify_configuration
c_func
(paren
id|client_handle_t
id|handle
comma
id|modconf_t
op_star
id|mod
)paren
suffix:semicolon
r_int
id|pcmcia_modify_window
c_func
(paren
id|window_handle_t
id|win
comma
id|modwin_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_register_client
c_func
(paren
id|client_handle_t
op_star
id|handle
comma
id|client_reg_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_release_configuration
c_func
(paren
id|client_handle_t
id|handle
)paren
suffix:semicolon
r_int
id|pcmcia_release_io
c_func
(paren
id|client_handle_t
id|handle
comma
id|io_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_release_irq
c_func
(paren
id|client_handle_t
id|handle
comma
id|irq_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_release_window
c_func
(paren
id|window_handle_t
id|win
)paren
suffix:semicolon
r_int
id|pcmcia_request_configuration
c_func
(paren
id|client_handle_t
id|handle
comma
id|config_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_request_io
c_func
(paren
id|client_handle_t
id|handle
comma
id|io_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_request_irq
c_func
(paren
id|client_handle_t
id|handle
comma
id|irq_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_request_window
c_func
(paren
id|client_handle_t
op_star
id|handle
comma
id|win_req_t
op_star
id|req
comma
id|window_handle_t
op_star
id|wh
)paren
suffix:semicolon
r_int
id|pcmcia_reset_card
c_func
(paren
id|client_handle_t
id|handle
comma
id|client_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_suspend_card
c_func
(paren
id|client_handle_t
id|handle
comma
id|client_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_resume_card
c_func
(paren
id|client_handle_t
id|handle
comma
id|client_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_eject_card
c_func
(paren
id|client_handle_t
id|handle
comma
id|client_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_insert_card
c_func
(paren
id|client_handle_t
id|handle
comma
id|client_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pcmcia_set_event_mask
c_func
(paren
id|client_handle_t
id|handle
comma
id|eventmask_t
op_star
id|mask
)paren
suffix:semicolon
r_int
id|pcmcia_report_error
c_func
(paren
id|client_handle_t
id|handle
comma
id|error_info_t
op_star
id|err
)paren
suffix:semicolon
r_struct
id|pci_bus
op_star
id|pcmcia_lookup_bus
c_func
(paren
id|client_handle_t
id|handle
)paren
suffix:semicolon
multiline_comment|/* rsrc_mgr.c */
r_int
id|pcmcia_adjust_resource_info
c_func
(paren
id|client_handle_t
id|handle
comma
id|adjust_t
op_star
id|adj
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_CS_H */
eof
