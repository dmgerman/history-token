multiline_comment|/*****************************************************************************&n; *&n; * Module name: bm.h&n; *   $Revision: 39 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __BM_H__
DECL|macro|__BM_H__
mdefine_line|#define __BM_H__
macro_line|#include &lt;actypes.h&gt;
macro_line|#include &lt;acexcep.h&gt;
multiline_comment|/*****************************************************************************&n; *                               Types &amp; Defines&n; *****************************************************************************/
multiline_comment|/*&n; * Output Flags (Debug):&n; * ---------------------&n; */
DECL|macro|BM_PRINT_ALL
mdefine_line|#define BM_PRINT_ALL&t;&t;(0x00000000)
DECL|macro|BM_PRINT_GROUP
mdefine_line|#define BM_PRINT_GROUP&t;&t;(0x00000001)
DECL|macro|BM_PRINT_LINKAGE
mdefine_line|#define BM_PRINT_LINKAGE&t;(0x00000002)
DECL|macro|BM_PRINT_IDENTIFICATION
mdefine_line|#define BM_PRINT_IDENTIFICATION&t;(0x00000004)
DECL|macro|BM_PRINT_POWER
mdefine_line|#define BM_PRINT_POWER&t;&t;(0x00000008)
DECL|macro|BM_PRINT_PRESENT
mdefine_line|#define BM_PRINT_PRESENT&t;(0x00000010)
multiline_comment|/*&n; * BM_COMMAND:&n; * -----------&n; */
DECL|typedef|BM_COMMAND
r_typedef
id|u32
id|BM_COMMAND
suffix:semicolon
DECL|macro|BM_COMMAND_UNKNOWN
mdefine_line|#define BM_COMMAND_UNKNOWN&t;((BM_COMMAND) 0x00)
DECL|macro|BM_COMMAND_GET_POWER_STATE
mdefine_line|#define BM_COMMAND_GET_POWER_STATE ((BM_COMMAND) 0x01)
DECL|macro|BM_COMMAND_SET_POWER_STATE
mdefine_line|#define BM_COMMAND_SET_POWER_STATE ((BM_COMMAND) 0x02)
DECL|macro|BM_COMMAND_DEVICE_SPECIFIC
mdefine_line|#define BM_COMMAND_DEVICE_SPECIFIC ((BM_COMMAND) 0x80)
multiline_comment|/*&n; * BM_NOTIFY:&n; * ----------&n; * Standard ACPI notification values, from section 5.6.3 of the ACPI 2.0&n; * specification.  Note that the Bus Manager internally handles all&n; * standard ACPI notifications -- driver modules are never sent these&n; * values (see &quot;Bus Manager Notifications&quot;, below).&n; */
DECL|typedef|BM_NOTIFY
r_typedef
id|u32
id|BM_NOTIFY
suffix:semicolon
DECL|macro|BM_NOTIFY_BUS_CHECK
mdefine_line|#define BM_NOTIFY_BUS_CHECK&t;((BM_NOTIFY) 0x00)
DECL|macro|BM_NOTIFY_DEVICE_CHECK
mdefine_line|#define BM_NOTIFY_DEVICE_CHECK&t;((BM_NOTIFY) 0x01)
DECL|macro|BM_NOTIFY_DEVICE_WAKE
mdefine_line|#define BM_NOTIFY_DEVICE_WAKE&t;((BM_NOTIFY) 0x02)
DECL|macro|BM_NOTIFY_EJECT_REQUEST
mdefine_line|#define BM_NOTIFY_EJECT_REQUEST&t;((BM_NOTIFY) 0x03)
DECL|macro|BM_NOTIFY_DEVICE_CHECK_LIGHT
mdefine_line|#define BM_NOTIFY_DEVICE_CHECK_LIGHT ((BM_NOTIFY) 0x04)
DECL|macro|BM_NOTIFY_FREQUENCY_MISMATCH
mdefine_line|#define BM_NOTIFY_FREQUENCY_MISMATCH ((BM_NOTIFY) 0x05)
DECL|macro|BM_NOTIFY_BUS_MODE_MISMATCH
mdefine_line|#define BM_NOTIFY_BUS_MODE_MISMATCH ((BM_NOTIFY) 0x06)
DECL|macro|BM_NOTIFY_POWER_FAULT
mdefine_line|#define BM_NOTIFY_POWER_FAULT&t;((BM_NOTIFY) 0x07)
multiline_comment|/*&n; * These are a higher-level abstraction of ACPI notifications, intended&n; * for consumption by driver modules to facilitate PnP.&n; */
DECL|macro|BM_NOTIFY_UNKNOWN
mdefine_line|#define BM_NOTIFY_UNKNOWN&t;((BM_NOTIFY) 0x00)
DECL|macro|BM_NOTIFY_DEVICE_ADDED
mdefine_line|#define BM_NOTIFY_DEVICE_ADDED&t;((BM_NOTIFY) 0x01)
DECL|macro|BM_NOTIFY_DEVICE_REMOVED
mdefine_line|#define BM_NOTIFY_DEVICE_REMOVED ((BM_NOTIFY) 0x02)
multiline_comment|/*&n; * BM_HANDLE:&n; * ----------&n; */
DECL|typedef|BM_HANDLE
r_typedef
id|u32
id|BM_HANDLE
suffix:semicolon
DECL|macro|BM_HANDLE_ROOT
mdefine_line|#define BM_HANDLE_ROOT&t;&t;((BM_HANDLE) 0x00000000)
DECL|macro|BM_HANDLE_UNKNOWN
mdefine_line|#define BM_HANDLE_UNKNOWN&t;((BM_HANDLE) 0xFFFFFFFF)
DECL|macro|BM_HANDLES_MAX
mdefine_line|#define BM_HANDLES_MAX&t;&t;100
multiline_comment|/*&n; * BM_HANDLE_LIST:&n; * ---------------&n; */
r_typedef
r_struct
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|handles
id|BM_HANDLE
id|handles
(braket
id|BM_HANDLES_MAX
)braket
suffix:semicolon
DECL|typedef|BM_HANDLE_LIST
)brace
id|BM_HANDLE_LIST
suffix:semicolon
multiline_comment|/*&n; * BM_DEVICE_TYPE:&n; * ---------------&n; */
DECL|typedef|BM_DEVICE_TYPE
r_typedef
id|u32
id|BM_DEVICE_TYPE
suffix:semicolon
DECL|macro|BM_TYPE_UNKNOWN
mdefine_line|#define BM_TYPE_UNKNOWN&t;&t;((BM_DEVICE_TYPE) 0x00000000)
DECL|macro|BM_TYPE_SYSTEM
mdefine_line|#define BM_TYPE_SYSTEM&t;&t;((BM_DEVICE_TYPE) 0x00000001)
DECL|macro|BM_TYPE_SCOPE
mdefine_line|#define BM_TYPE_SCOPE&t;&t;((BM_DEVICE_TYPE) 0x00000002)
DECL|macro|BM_TYPE_PROCESSOR
mdefine_line|#define BM_TYPE_PROCESSOR&t;((BM_DEVICE_TYPE) 0x00000003)
DECL|macro|BM_TYPE_THERMAL_ZONE
mdefine_line|#define BM_TYPE_THERMAL_ZONE&t;((BM_DEVICE_TYPE) 0x00000004)
DECL|macro|BM_TYPE_POWER_RESOURCE
mdefine_line|#define BM_TYPE_POWER_RESOURCE&t;((BM_DEVICE_TYPE) 0x00000005)
DECL|macro|BM_TYPE_DEVICE
mdefine_line|#define BM_TYPE_DEVICE&t;&t;((BM_DEVICE_TYPE) 0x00000006)
DECL|macro|BM_TYPE_FIXED_BUTTON
mdefine_line|#define BM_TYPE_FIXED_BUTTON&t;((BM_DEVICE_TYPE) 0x00000007)
multiline_comment|/*&n; * BM_DEVICE_UID:&n; * --------------&n; */
DECL|typedef|BM_DEVICE_UID
r_typedef
r_char
id|BM_DEVICE_UID
(braket
l_int|9
)braket
suffix:semicolon
DECL|macro|BM_UID_UNKNOWN
mdefine_line|#define BM_UID_UNKNOWN&t;&t;&squot;0&squot;
multiline_comment|/*&n; * BM_DEVICE_HID:&n; * --------------&n; */
DECL|typedef|BM_DEVICE_HID
r_typedef
r_char
id|BM_DEVICE_HID
(braket
l_int|9
)braket
suffix:semicolon
DECL|macro|BM_HID_UNKNOWN
mdefine_line|#define BM_HID_UNKNOWN&t;&t;&squot;&bslash;0&squot;
DECL|macro|BM_HID_POWER_BUTTON
mdefine_line|#define BM_HID_POWER_BUTTON&t;&quot;PNP0C0C&quot;
DECL|macro|BM_HID_SLEEP_BUTTON
mdefine_line|#define BM_HID_SLEEP_BUTTON&t;&quot;PNP0C0E&quot;
multiline_comment|/*&n; * BM_DEVICE_ADR:&n; * --------------&n; */
DECL|typedef|BM_DEVICE_ADR
r_typedef
id|u32
id|BM_DEVICE_ADR
suffix:semicolon
DECL|macro|BM_ADDRESS_UNKNOWN
mdefine_line|#define BM_ADDRESS_UNKNOWN&t;0
multiline_comment|/*&n; * BM_DEVICE_FLAGS:&n; * ----------------&n; * The encoding of BM_DEVICE_FLAGS is illustrated below.&n; * Note that a set bit (1) indicates the property is TRUE&n; * (e.g. if bit 0 is set then the device has dynamic status).&n; * +--+------------+-+-+-+-+-+-+-+&n; * |31| Bits 30:7  |6|5|4|3|2|1|0|&n; * +--+------------+-+-+-+-+-+-+-+&n; *   |       |      | | | | | | |&n; *   |       |      | | | | | | +- Dynamic status?&n; *   |       |      | | | | | +--- Identifiable?&n; *   |       |      | | | | +----- Configurable?&n; *   |       |      | | | +------- Power Control?&n; *   |       |      | | +--------- Ejectable?&n; *   |       |      | +----------- Docking Station?&n; *   |       |      +------------- Fixed-Feature?&n; *   |       +-------------------- &lt;Reserved&gt;&n; *   +---------------------------- Driver Control?&n; *&n; * Dynamic status:  Device has a _STA object.&n; * Identifiable:    Device has a _HID and/or _ADR and possibly other&n; *                  identification objects defined.&n; * Configurable:    Device has a _CRS and possibly other configuration&n; *                  objects defined.&n; * Power Control:   Device has a _PR0 and/or _PS0 and possibly other&n; *                  power management objects defined.&n; * Ejectable:       Device has an _EJD and/or _EJx and possibly other&n; *                  dynamic insertion/removal objects defined.&n; * Docking Station: Device has a _DCK object defined.&n; * Fixed-Feature:   Device does not exist in the namespace; was&n; *                  enumerated as a fixed-feature (e.g. power button).&n; * Driver Control:  A driver has been installed for this device.&n; */
DECL|typedef|BM_DEVICE_FLAGS
r_typedef
id|u32
id|BM_DEVICE_FLAGS
suffix:semicolon
DECL|macro|BM_FLAGS_UNKNOWN
mdefine_line|#define BM_FLAGS_UNKNOWN&t;((BM_DEVICE_FLAGS) 0x00000000)
DECL|macro|BM_FLAGS_DYNAMIC_STATUS
mdefine_line|#define BM_FLAGS_DYNAMIC_STATUS&t;((BM_DEVICE_FLAGS) 0x00000001)
DECL|macro|BM_FLAGS_IDENTIFIABLE
mdefine_line|#define BM_FLAGS_IDENTIFIABLE&t;((BM_DEVICE_FLAGS) 0x00000002)
DECL|macro|BM_FLAGS_CONFIGURABLE
mdefine_line|#define BM_FLAGS_CONFIGURABLE&t;((BM_DEVICE_FLAGS) 0x00000004)
DECL|macro|BM_FLAGS_POWER_CONTROL
mdefine_line|#define BM_FLAGS_POWER_CONTROL&t;((BM_DEVICE_FLAGS) 0x00000008)
DECL|macro|BM_FLAGS_EJECTABLE
mdefine_line|#define BM_FLAGS_EJECTABLE&t;((BM_DEVICE_FLAGS) 0x00000010)
DECL|macro|BM_FLAGS_DOCKING_STATION
mdefine_line|#define BM_FLAGS_DOCKING_STATION ((BM_DEVICE_FLAGS) 0x00000020)
DECL|macro|BM_FLAGS_FIXED_FEATURE
mdefine_line|#define BM_FLAGS_FIXED_FEATURE&t;((BM_DEVICE_FLAGS) 0x00000040)
DECL|macro|BM_FLAGS_DRIVER_CONTROL
mdefine_line|#define BM_FLAGS_DRIVER_CONTROL&t;((BM_DEVICE_FLAGS) 0x80000000)
multiline_comment|/*&n; * Device PM Flags:&n; * ----------------&n; * +-----------+-+-+-+-+-+-+-+&n; * | Bits 31:7 |6|5|4|3|2|1|0|&n; * +-----------+-+-+-+-+-+-+-+&n; *       |      | | | | | | |&n; *       |      | | | | | | +- D0 Support?&n; *       |      | | | | | +--- D1 Support?&n; *       |      | | | | +----- D2 Support?&n; *       |      | | | +------- D3 Support?&n; *       |      | | +--------- Power State Queriable?&n; *       |      | +----------- Inrush Current?&n; *       |      +------------- Wake Capable?&n; *       +-------------------- &lt;Reserved&gt;&n; *&n; * D0-D3 Support:   Device supports corresponding Dx state.&n; * Power State:     Device has a _PSC (current power state) object defined.&n; * Inrush Current:  Device has an _IRC (inrush current) object defined.&n; * Wake Capable:    Device has a _PRW (wake-capable) object defined.&n; */
DECL|macro|BM_FLAGS_D0_SUPPORT
mdefine_line|#define BM_FLAGS_D0_SUPPORT&t;((BM_DEVICE_FLAGS) 0x00000001)
DECL|macro|BM_FLAGS_D1_SUPPORT
mdefine_line|#define BM_FLAGS_D1_SUPPORT&t;((BM_DEVICE_FLAGS) 0x00000002)
DECL|macro|BM_FLAGS_D2_SUPPORT
mdefine_line|#define BM_FLAGS_D2_SUPPORT&t;((BM_DEVICE_FLAGS) 0x00000004)
DECL|macro|BM_FLAGS_D3_SUPPORT
mdefine_line|#define BM_FLAGS_D3_SUPPORT&t;((BM_DEVICE_FLAGS) 0x00000008)
DECL|macro|BM_FLAGS_POWER_STATE
mdefine_line|#define BM_FLAGS_POWER_STATE&t;((BM_DEVICE_FLAGS) 0x00000010)
DECL|macro|BM_FLAGS_INRUSH_CURRENT
mdefine_line|#define BM_FLAGS_INRUSH_CURRENT&t;((BM_DEVICE_FLAGS) 0x00000020)
DECL|macro|BM_FLAGS_WAKE_CAPABLE
mdefine_line|#define BM_FLAGS_WAKE_CAPABLE&t;((BM_DEVICE_FLAGS) 0x00000040)
multiline_comment|/*&n; * BM_DEVICE_STATUS:&n; * -----------------&n; * The encoding of BM_DEVICE_STATUS is illustrated below.&n; * Note that a set bit (1) indicates the property is TRUE&n; * (e.g. if bit 0 is set then the device is present).&n; * +-----------+-+-+-+-+-+&n; * | Bits 31:4 |4|3|2|1|0|&n; * +-----------+-+-+-+-+-+&n; *       |      | | | | |&n; *       |      | | | | +- Present?&n; *       |      | | | +--- Enabled?&n; *       |      | | +----- Show in UI?&n; *       |      | +------- Functioning?&n; *       |      +--------- Battery Present?&n; *       +---------------- &lt;Reserved&gt;&n; */
DECL|typedef|BM_DEVICE_STATUS
r_typedef
id|u32
id|BM_DEVICE_STATUS
suffix:semicolon
DECL|macro|BM_STATUS_UNKNOWN
mdefine_line|#define BM_STATUS_UNKNOWN&t;((BM_DEVICE_STATUS) 0x00000000)
DECL|macro|BM_STATUS_PRESENT
mdefine_line|#define BM_STATUS_PRESENT&t;((BM_DEVICE_STATUS) 0x00000001)
DECL|macro|BM_STATUS_ENABLED
mdefine_line|#define BM_STATUS_ENABLED&t;((BM_DEVICE_STATUS) 0x00000002)
DECL|macro|BM_STATUS_SHOW_UI
mdefine_line|#define BM_STATUS_SHOW_UI&t;((BM_DEVICE_STATUS) 0x00000004)
DECL|macro|BM_STATUS_FUNCTIONING
mdefine_line|#define BM_STATUS_FUNCTIONING&t;((BM_DEVICE_STATUS) 0x00000008)
DECL|macro|BM_STATUS_BATTERY_PRESENT
mdefine_line|#define BM_STATUS_BATTERY_PRESENT ((BM_DEVICE_STATUS) 0x00000010)
DECL|macro|BM_STATUS_DEFAULT
mdefine_line|#define BM_STATUS_DEFAULT&t;((BM_DEVICE_STATUS) 0x0000000F)
multiline_comment|/*&n; * BM_POWER_STATE:&n; * ---------------&n; */
DECL|typedef|BM_POWER_STATE
r_typedef
id|u32
id|BM_POWER_STATE
suffix:semicolon
multiline_comment|/*&n; * BM_DEVICE_ID:&n; * -------------&n; */
r_typedef
r_struct
(brace
DECL|member|type
id|BM_DEVICE_TYPE
id|type
suffix:semicolon
DECL|member|uid
id|BM_DEVICE_UID
id|uid
suffix:semicolon
DECL|member|hid
id|BM_DEVICE_HID
id|hid
suffix:semicolon
DECL|member|adr
id|BM_DEVICE_ADR
id|adr
suffix:semicolon
DECL|typedef|BM_DEVICE_ID
)brace
id|BM_DEVICE_ID
suffix:semicolon
multiline_comment|/*&n; * BM_DEVICE_POWER:&n; * ----------------&n; * Structure containing basic device power management information.&n; */
r_typedef
r_struct
(brace
DECL|member|flags
id|BM_DEVICE_FLAGS
id|flags
suffix:semicolon
DECL|member|state
id|BM_POWER_STATE
id|state
suffix:semicolon
DECL|member|dx_supported
id|BM_DEVICE_FLAGS
id|dx_supported
(braket
id|ACPI_S_STATE_COUNT
)braket
suffix:semicolon
DECL|typedef|BM_DEVICE_POWER
)brace
id|BM_DEVICE_POWER
suffix:semicolon
multiline_comment|/*&n; * BM_DEVICE:&n; * ----------&n; */
r_typedef
r_struct
(brace
DECL|member|handle
id|BM_HANDLE
id|handle
suffix:semicolon
DECL|member|acpi_handle
id|ACPI_HANDLE
id|acpi_handle
suffix:semicolon
DECL|member|flags
id|BM_DEVICE_FLAGS
id|flags
suffix:semicolon
DECL|member|status
id|BM_DEVICE_STATUS
id|status
suffix:semicolon
DECL|member|id
id|BM_DEVICE_ID
id|id
suffix:semicolon
DECL|member|power
id|BM_DEVICE_POWER
id|power
suffix:semicolon
DECL|typedef|BM_DEVICE
)brace
id|BM_DEVICE
suffix:semicolon
multiline_comment|/*&n; * BM_SEARCH:&n; * ----------&n; * Structure used for searching the ACPI Bus Manager&squot;s device hierarchy.&n; */
r_typedef
r_struct
(brace
DECL|member|criteria
id|BM_DEVICE_ID
id|criteria
suffix:semicolon
DECL|member|results
id|BM_HANDLE_LIST
id|results
suffix:semicolon
DECL|typedef|BM_SEARCH
)brace
id|BM_SEARCH
suffix:semicolon
multiline_comment|/*&n; * BM_REQUEST:&n; * -----------&n; * Structure used for sending requests to/through the ACPI Bus Manager.&n; */
r_typedef
r_struct
(brace
DECL|member|status
id|ACPI_STATUS
id|status
suffix:semicolon
DECL|member|command
id|BM_COMMAND
id|command
suffix:semicolon
DECL|member|handle
id|BM_HANDLE
id|handle
suffix:semicolon
DECL|member|buffer
id|ACPI_BUFFER
id|buffer
suffix:semicolon
DECL|typedef|BM_REQUEST
)brace
id|BM_REQUEST
suffix:semicolon
multiline_comment|/*&n; * Driver Registration:&n; * --------------------&n; */
multiline_comment|/* Driver Context */
DECL|typedef|BM_DRIVER_CONTEXT
r_typedef
r_void
op_star
id|BM_DRIVER_CONTEXT
suffix:semicolon
multiline_comment|/* Notification Callback Function */
r_typedef
DECL|typedef|BM_DRIVER_NOTIFY
id|ACPI_STATUS
(paren
op_star
id|BM_DRIVER_NOTIFY
)paren
(paren
id|BM_NOTIFY
id|notify_type
comma
id|BM_HANDLE
id|device_handle
comma
id|BM_DRIVER_CONTEXT
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/* Request Callback Function */
r_typedef
DECL|typedef|BM_DRIVER_REQUEST
id|ACPI_STATUS
(paren
op_star
id|BM_DRIVER_REQUEST
)paren
(paren
id|BM_REQUEST
op_star
id|request
comma
id|BM_DRIVER_CONTEXT
id|context
)paren
suffix:semicolon
multiline_comment|/* Driver Registration */
r_typedef
r_struct
(brace
DECL|member|notify
id|BM_DRIVER_NOTIFY
id|notify
suffix:semicolon
DECL|member|request
id|BM_DRIVER_REQUEST
id|request
suffix:semicolon
DECL|member|context
id|BM_DRIVER_CONTEXT
id|context
suffix:semicolon
DECL|typedef|BM_DRIVER
)brace
id|BM_DRIVER
suffix:semicolon
multiline_comment|/*&n; * BM_NODE:&n; * --------&n; * Structure used to maintain the device hierarchy.&n; */
DECL|struct|_BM_NODE
r_typedef
r_struct
id|_BM_NODE
(brace
DECL|member|device
id|BM_DEVICE
id|device
suffix:semicolon
DECL|member|driver
id|BM_DRIVER
id|driver
suffix:semicolon
DECL|member|parent
r_struct
id|_BM_NODE
op_star
id|parent
suffix:semicolon
DECL|member|next
r_struct
id|_BM_NODE
op_star
id|next
suffix:semicolon
r_struct
(brace
DECL|member|head
r_struct
id|_BM_NODE
op_star
id|head
suffix:semicolon
DECL|member|tail
r_struct
id|_BM_NODE
op_star
id|tail
suffix:semicolon
DECL|member|scope
)brace
id|scope
suffix:semicolon
DECL|typedef|BM_NODE
)brace
id|BM_NODE
suffix:semicolon
multiline_comment|/*&n; * BM_NODE_LIST:&n; * -------------&n; * Structure used to maintain an array of node pointers.&n; */
r_typedef
r_struct
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|nodes
id|BM_NODE
op_star
id|nodes
(braket
id|BM_HANDLES_MAX
)braket
suffix:semicolon
DECL|typedef|BM_NODE_LIST
)brace
id|BM_NODE_LIST
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *                                  Macros&n; *****************************************************************************/
multiline_comment|/*&n; * Device Presence:&n; * ----------------&n; * Note that status (_STA) means something different for power resources&n; * (they&squot;re assumed to always be present).&n; */
DECL|macro|BM_DEVICE_PRESENT
mdefine_line|#define BM_DEVICE_PRESENT(d)&t;((d-&gt;id.type!=BM_TYPE_POWER_RESOURCE)?(d-&gt;status &amp; BM_STATUS_PRESENT):TRUE)
DECL|macro|BM_NODE_PRESENT
mdefine_line|#define BM_NODE_PRESENT(n)&t;((n-&gt;device.id.type!=BM_TYPE_POWER_RESOURCE)?(n-&gt;device.status &amp; BM_STATUS_PRESENT):TRUE)
multiline_comment|/*&n; * Device Flags:&n; * -------------&n; */
DECL|macro|BM_IS_DRIVER_CONTROL
mdefine_line|#define BM_IS_DRIVER_CONTROL(d)&t;(d-&gt;flags &amp; BM_FLAGS_DRIVER_CONTROL)
DECL|macro|BM_IS_POWER_CONTROL
mdefine_line|#define BM_IS_POWER_CONTROL(d)&t;(d-&gt;flags &amp; BM_FLAGS_POWER_CONTROL)
multiline_comment|/*&n; * Device Power Flags:&n; * -------------------&n; */
DECL|macro|BM_IS_POWER_STATE
mdefine_line|#define BM_IS_POWER_STATE(d)&t;(d-&gt;power.flags &amp; BM_FLAGS_POWER_STATE)
multiline_comment|/*****************************************************************************&n; *                             Function Prototypes&n; *****************************************************************************/
multiline_comment|/* bm.c */
id|ACPI_STATUS
id|bm_initialize
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_terminate
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_get_status
(paren
id|BM_DEVICE
op_star
id|device
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_get_handle
(paren
id|ACPI_HANDLE
id|acpi_handle
comma
id|BM_HANDLE
op_star
id|device_handle
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_get_node
(paren
id|BM_HANDLE
id|device_handle
comma
id|ACPI_HANDLE
id|acpi_handle
comma
id|BM_NODE
op_star
op_star
id|node
)paren
suffix:semicolon
multiline_comment|/* bmsearch.c */
id|ACPI_STATUS
id|bm_search
c_func
(paren
id|BM_HANDLE
id|device_handle
comma
id|BM_DEVICE_ID
op_star
id|criteria
comma
id|BM_HANDLE_LIST
op_star
id|results
)paren
suffix:semicolon
multiline_comment|/* bmnotify.c */
r_void
id|bm_notify
(paren
id|ACPI_HANDLE
id|acpi_handle
comma
id|u32
id|notify_value
comma
r_void
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/* bm_request.c */
id|ACPI_STATUS
id|bm_request
(paren
id|BM_REQUEST
op_star
id|request_info
)paren
suffix:semicolon
multiline_comment|/* bmdriver.c */
id|ACPI_STATUS
id|bm_get_device_power_state
(paren
id|BM_HANDLE
id|device_handle
comma
id|BM_POWER_STATE
op_star
id|state
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_set_device_power_state
(paren
id|BM_HANDLE
id|device_handle
comma
id|BM_POWER_STATE
id|state
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_get_device_status
(paren
id|BM_HANDLE
id|device_handle
comma
id|BM_DEVICE_STATUS
op_star
id|device_status
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_get_device_info
(paren
id|BM_HANDLE
id|device_handle
comma
id|BM_DEVICE
op_star
op_star
id|device_info
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_get_device_context
(paren
id|BM_HANDLE
id|device_handle
comma
id|BM_DRIVER_CONTEXT
op_star
id|context
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_register_driver
(paren
id|BM_DEVICE_ID
op_star
id|criteria
comma
id|BM_DRIVER
op_star
id|driver
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_unregister_driver
(paren
id|BM_DEVICE_ID
op_star
id|criteria
comma
id|BM_DRIVER
op_star
id|driver
)paren
suffix:semicolon
multiline_comment|/* bmpm.c */
id|ACPI_STATUS
id|bm_get_pm_capabilities
(paren
id|BM_NODE
op_star
id|node
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_get_power_state
(paren
id|BM_NODE
op_star
id|node
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_set_power_state
(paren
id|BM_NODE
op_star
id|node
comma
id|BM_POWER_STATE
id|target_state
)paren
suffix:semicolon
multiline_comment|/* bmpower.c */
id|ACPI_STATUS
id|bm_pr_initialize
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_pr_terminate
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* bmutils.c */
id|ACPI_STATUS
id|bm_cast_buffer
(paren
id|ACPI_BUFFER
op_star
id|buffer
comma
r_void
op_star
op_star
id|pointer
comma
id|u32
id|length
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_copy_to_buffer
(paren
id|ACPI_BUFFER
op_star
id|buffer
comma
r_void
op_star
id|data
comma
id|u32
id|length
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_extract_package_data
(paren
id|ACPI_OBJECT
op_star
id|package
comma
id|ACPI_BUFFER
op_star
id|format
comma
id|ACPI_BUFFER
op_star
id|buffer
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_evaluate_object
(paren
id|ACPI_HANDLE
id|acpi_handle
comma
id|ACPI_STRING
id|pathname
comma
id|ACPI_OBJECT_LIST
op_star
id|arguments
comma
id|ACPI_BUFFER
op_star
id|buffer
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_evaluate_simple_integer
(paren
id|ACPI_HANDLE
id|acpi_handle
comma
id|ACPI_STRING
id|pathname
comma
id|u32
op_star
id|data
)paren
suffix:semicolon
id|ACPI_STATUS
id|bm_evaluate_reference_list
(paren
id|ACPI_HANDLE
id|acpi_handle
comma
id|ACPI_STRING
id|pathname
comma
id|BM_HANDLE_LIST
op_star
id|reference_list
)paren
suffix:semicolon
multiline_comment|/* ACPI Bus Driver OSL */
id|ACPI_STATUS
id|bm_osl_generate_event
(paren
id|BM_HANDLE
id|device_handle
comma
r_char
op_star
id|device_type
comma
r_char
op_star
id|device_instance
comma
id|u32
id|event_type
comma
id|u32
id|event_data
)paren
suffix:semicolon
macro_line|#endif  /* __BM_H__ */
eof
