multiline_comment|/*&n; *  acpi_drivers.h  ($Revision: 23 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#ifndef __ACPI_DRIVERS_H__
DECL|macro|__ACPI_DRIVERS_H__
mdefine_line|#define __ACPI_DRIVERS_H__
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &quot;acpi_bus.h&quot;
DECL|macro|ACPI_DRIVER_VERSION
mdefine_line|#define ACPI_DRIVER_VERSION&t;&t;0x20020404
DECL|macro|ACPI_MAX_STRING
mdefine_line|#define ACPI_MAX_STRING&t;&t;&t;80
multiline_comment|/* --------------------------------------------------------------------------&n;                                    ACPI Bus&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_BUS_COMPONENT
mdefine_line|#define ACPI_BUS_COMPONENT&t;&t;0x00010000
DECL|macro|ACPI_BUS_CLASS
mdefine_line|#define ACPI_BUS_CLASS&t;&t;&t;&quot;system_bus&quot;
DECL|macro|ACPI_BUS_HID
mdefine_line|#define ACPI_BUS_HID&t;&t;&t;&quot;ACPI_BUS&quot;
DECL|macro|ACPI_BUS_DRIVER_NAME
mdefine_line|#define ACPI_BUS_DRIVER_NAME&t;&t;&quot;ACPI Bus Driver&quot;
DECL|macro|ACPI_BUS_DEVICE_NAME
mdefine_line|#define ACPI_BUS_DEVICE_NAME&t;&t;&quot;System Bus&quot;
multiline_comment|/* --------------------------------------------------------------------------&n;                                  AC Adapter&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_AC_COMPONENT
mdefine_line|#define ACPI_AC_COMPONENT&t;&t;0x00020000
DECL|macro|ACPI_AC_CLASS
mdefine_line|#define ACPI_AC_CLASS&t;&t;&t;&quot;ac_adapter&quot;
DECL|macro|ACPI_AC_HID
mdefine_line|#define ACPI_AC_HID &t;&t;&t;&quot;ACPI0003&quot;
DECL|macro|ACPI_AC_DRIVER_NAME
mdefine_line|#define ACPI_AC_DRIVER_NAME&t;&t;&quot;ACPI AC Adapter Driver&quot;
DECL|macro|ACPI_AC_DEVICE_NAME
mdefine_line|#define ACPI_AC_DEVICE_NAME&t;&t;&quot;AC Adapter&quot;
DECL|macro|ACPI_AC_FILE_STATE
mdefine_line|#define ACPI_AC_FILE_STATE&t;&t;&quot;state&quot;
DECL|macro|ACPI_AC_NOTIFY_STATUS
mdefine_line|#define ACPI_AC_NOTIFY_STATUS&t;&t;0x80
DECL|macro|ACPI_AC_STATUS_OFFLINE
mdefine_line|#define ACPI_AC_STATUS_OFFLINE&t;&t;0x00
DECL|macro|ACPI_AC_STATUS_ONLINE
mdefine_line|#define ACPI_AC_STATUS_ONLINE&t;&t;0x01
DECL|macro|ACPI_AC_STATUS_UNKNOWN
mdefine_line|#define ACPI_AC_STATUS_UNKNOWN&t;&t;0xFF
multiline_comment|/* --------------------------------------------------------------------------&n;                                     Battery&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_BATTERY_COMPONENT
mdefine_line|#define ACPI_BATTERY_COMPONENT&t;&t;0x00040000
DECL|macro|ACPI_BATTERY_CLASS
mdefine_line|#define ACPI_BATTERY_CLASS&t;&t;&quot;battery&quot;
DECL|macro|ACPI_BATTERY_HID
mdefine_line|#define ACPI_BATTERY_HID&t;&t;&quot;PNP0C0A&quot;
DECL|macro|ACPI_BATTERY_DRIVER_NAME
mdefine_line|#define ACPI_BATTERY_DRIVER_NAME&t;&quot;ACPI Battery Driver&quot;
DECL|macro|ACPI_BATTERY_DEVICE_NAME
mdefine_line|#define ACPI_BATTERY_DEVICE_NAME&t;&quot;Battery&quot;
DECL|macro|ACPI_BATTERY_FILE_INFO
mdefine_line|#define ACPI_BATTERY_FILE_INFO&t;&t;&quot;info&quot;
DECL|macro|ACPI_BATTERY_FILE_STATUS
mdefine_line|#define ACPI_BATTERY_FILE_STATUS&t;&quot;state&quot;
DECL|macro|ACPI_BATTERY_FILE_ALARM
mdefine_line|#define ACPI_BATTERY_FILE_ALARM&t;&t;&quot;alarm&quot;
DECL|macro|ACPI_BATTERY_NOTIFY_STATUS
mdefine_line|#define ACPI_BATTERY_NOTIFY_STATUS&t;0x80
DECL|macro|ACPI_BATTERY_NOTIFY_INFO
mdefine_line|#define ACPI_BATTERY_NOTIFY_INFO&t;0x81
DECL|macro|ACPI_BATTERY_UNITS_WATTS
mdefine_line|#define ACPI_BATTERY_UNITS_WATTS&t;&quot;mW&quot;
DECL|macro|ACPI_BATTERY_UNITS_AMPS
mdefine_line|#define ACPI_BATTERY_UNITS_AMPS&t;&t;&quot;mA&quot;
multiline_comment|/* --------------------------------------------------------------------------&n;                                      Button&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_BUTTON_COMPONENT
mdefine_line|#define ACPI_BUTTON_COMPONENT&t;&t;0x00080000
DECL|macro|ACPI_BUTTON_DRIVER_NAME
mdefine_line|#define ACPI_BUTTON_DRIVER_NAME&t;&t;&quot;ACPI Button Driver&quot;
DECL|macro|ACPI_BUTTON_CLASS
mdefine_line|#define ACPI_BUTTON_CLASS&t;&t;&quot;button&quot;
DECL|macro|ACPI_BUTTON_FILE_INFO
mdefine_line|#define ACPI_BUTTON_FILE_INFO&t;&t;&quot;info&quot;
DECL|macro|ACPI_BUTTON_TYPE_UNKNOWN
mdefine_line|#define ACPI_BUTTON_TYPE_UNKNOWN&t;0x00
DECL|macro|ACPI_BUTTON_NOTIFY_STATUS
mdefine_line|#define ACPI_BUTTON_NOTIFY_STATUS&t;0x80
DECL|macro|ACPI_BUTTON_SUBCLASS_POWER
mdefine_line|#define ACPI_BUTTON_SUBCLASS_POWER&t;&quot;power&quot;
DECL|macro|ACPI_BUTTON_HID_POWER
mdefine_line|#define ACPI_BUTTON_HID_POWER&t;&t;&quot;PNP0C0C&quot;&t;
DECL|macro|ACPI_BUTTON_HID_POWERF
mdefine_line|#define ACPI_BUTTON_HID_POWERF&t;&t;&quot;ACPI_FPB&quot;
DECL|macro|ACPI_BUTTON_DEVICE_NAME_POWER
mdefine_line|#define ACPI_BUTTON_DEVICE_NAME_POWER&t;&quot;Power Button (CM)&quot;
DECL|macro|ACPI_BUTTON_DEVICE_NAME_POWERF
mdefine_line|#define ACPI_BUTTON_DEVICE_NAME_POWERF&t;&quot;Power Button (FF)&quot;
DECL|macro|ACPI_BUTTON_TYPE_POWER
mdefine_line|#define ACPI_BUTTON_TYPE_POWER&t;&t;0x01
DECL|macro|ACPI_BUTTON_TYPE_POWERF
mdefine_line|#define ACPI_BUTTON_TYPE_POWERF&t;&t;0x02
DECL|macro|ACPI_BUTTON_SUBCLASS_SLEEP
mdefine_line|#define ACPI_BUTTON_SUBCLASS_SLEEP&t;&quot;sleep&quot;
DECL|macro|ACPI_BUTTON_HID_SLEEP
mdefine_line|#define ACPI_BUTTON_HID_SLEEP&t;&t;&quot;PNP0C0E&quot;
DECL|macro|ACPI_BUTTON_HID_SLEEPF
mdefine_line|#define ACPI_BUTTON_HID_SLEEPF&t;&t;&quot;ACPI_FSB&quot;
DECL|macro|ACPI_BUTTON_DEVICE_NAME_SLEEP
mdefine_line|#define ACPI_BUTTON_DEVICE_NAME_SLEEP&t;&quot;Sleep Button (CM)&quot;
DECL|macro|ACPI_BUTTON_DEVICE_NAME_SLEEPF
mdefine_line|#define ACPI_BUTTON_DEVICE_NAME_SLEEPF&t;&quot;Sleep Button (FF)&quot;
DECL|macro|ACPI_BUTTON_TYPE_SLEEP
mdefine_line|#define ACPI_BUTTON_TYPE_SLEEP&t;&t;0x03
DECL|macro|ACPI_BUTTON_TYPE_SLEEPF
mdefine_line|#define ACPI_BUTTON_TYPE_SLEEPF&t;&t;0x04
DECL|macro|ACPI_BUTTON_SUBCLASS_LID
mdefine_line|#define ACPI_BUTTON_SUBCLASS_LID&t;&quot;lid&quot;
DECL|macro|ACPI_BUTTON_HID_LID
mdefine_line|#define ACPI_BUTTON_HID_LID&t;&t;&quot;PNP0C0D&quot;
DECL|macro|ACPI_BUTTON_DEVICE_NAME_LID
mdefine_line|#define ACPI_BUTTON_DEVICE_NAME_LID&t;&quot;Lid Switch&quot;
DECL|macro|ACPI_BUTTON_TYPE_LID
mdefine_line|#define ACPI_BUTTON_TYPE_LID&t;&t;0x05
multiline_comment|/* --------------------------------------------------------------------------&n;                                Embedded Controller&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_EC_COMPONENT
mdefine_line|#define ACPI_EC_COMPONENT&t;&t;0x00100000
DECL|macro|ACPI_EC_CLASS
mdefine_line|#define ACPI_EC_CLASS&t;&t;&t;&quot;embedded_controller&quot;
DECL|macro|ACPI_EC_HID
mdefine_line|#define ACPI_EC_HID&t;&t;&t;&quot;PNP0C09&quot;
DECL|macro|ACPI_EC_DRIVER_NAME
mdefine_line|#define ACPI_EC_DRIVER_NAME&t;&t;&quot;ACPI Embedded Controller Driver&quot;
DECL|macro|ACPI_EC_DEVICE_NAME
mdefine_line|#define ACPI_EC_DEVICE_NAME&t;&t;&quot;Embedded Controller&quot;
DECL|macro|ACPI_EC_FILE_INFO
mdefine_line|#define ACPI_EC_FILE_INFO&t;&t;&quot;info&quot;
macro_line|#ifdef CONFIG_ACPI_EC
r_int
id|acpi_ec_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ec_exit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------------&n;                                       Fan&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_FAN_COMPONENT
mdefine_line|#define ACPI_FAN_COMPONENT&t;&t;0x00200000
DECL|macro|ACPI_FAN_CLASS
mdefine_line|#define ACPI_FAN_CLASS&t;&t;&t;&quot;fan&quot;
DECL|macro|ACPI_FAN_HID
mdefine_line|#define ACPI_FAN_HID&t;&t;&t;&quot;PNP0C0B&quot;
DECL|macro|ACPI_FAN_DRIVER_NAME
mdefine_line|#define ACPI_FAN_DRIVER_NAME&t;&t;&quot;ACPI Fan Driver&quot;
DECL|macro|ACPI_FAN_DEVICE_NAME
mdefine_line|#define ACPI_FAN_DEVICE_NAME&t;&t;&quot;Fan&quot;
DECL|macro|ACPI_FAN_FILE_STATE
mdefine_line|#define ACPI_FAN_FILE_STATE&t;&t;&quot;state&quot;
DECL|macro|ACPI_FAN_NOTIFY_STATUS
mdefine_line|#define ACPI_FAN_NOTIFY_STATUS&t;&t;0x80
multiline_comment|/* --------------------------------------------------------------------------&n;                                       PCI&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_PCI_LINK_COMPONENT
mdefine_line|#define ACPI_PCI_LINK_COMPONENT&t;&t;0x00400000
DECL|macro|ACPI_PCI_LINK_CLASS
mdefine_line|#define ACPI_PCI_LINK_CLASS&t;&t;&quot;irq_routing&quot;
DECL|macro|ACPI_PCI_LINK_HID
mdefine_line|#define ACPI_PCI_LINK_HID&t;&t;&quot;PNP0C0F&quot;
DECL|macro|ACPI_PCI_LINK_DRIVER_NAME
mdefine_line|#define ACPI_PCI_LINK_DRIVER_NAME&t;&quot;ACPI PCI Interrupt Link Driver&quot;
DECL|macro|ACPI_PCI_LINK_DEVICE_NAME
mdefine_line|#define ACPI_PCI_LINK_DEVICE_NAME&t;&quot;PCI Interrupt Link&quot;
DECL|macro|ACPI_PCI_LINK_FILE_INFO
mdefine_line|#define ACPI_PCI_LINK_FILE_INFO&t;&t;&quot;info&quot;
DECL|macro|ACPI_PCI_LINK_FILE_STATUS
mdefine_line|#define ACPI_PCI_LINK_FILE_STATUS&t;&quot;state&quot;
DECL|macro|ACPI_PCI_ROOT_COMPONENT
mdefine_line|#define ACPI_PCI_ROOT_COMPONENT&t;&t;0x00800000
DECL|macro|ACPI_PCI_ROOT_CLASS
mdefine_line|#define ACPI_PCI_ROOT_CLASS&t;&t;&quot;bridge&quot;
DECL|macro|ACPI_PCI_ROOT_HID
mdefine_line|#define ACPI_PCI_ROOT_HID&t;&t;&quot;PNP0A03&quot;
DECL|macro|ACPI_PCI_ROOT_DRIVER_NAME
mdefine_line|#define ACPI_PCI_ROOT_DRIVER_NAME&t;&quot;ACPI PCI Root Bridge Driver&quot;
DECL|macro|ACPI_PCI_ROOT_DEVICE_NAME
mdefine_line|#define ACPI_PCI_ROOT_DEVICE_NAME&t;&quot;PCI Root Bridge&quot;
DECL|macro|ACPI_PCI_PRT_DEVICE_NAME
mdefine_line|#define ACPI_PCI_PRT_DEVICE_NAME&t;&quot;PCI Interrupt Routing Table&quot;
macro_line|#ifdef CONFIG_ACPI_PCI
r_int
id|acpi_pci_link_get_irq
(paren
r_struct
id|acpi_prt_entry
op_star
id|entry
comma
r_int
op_star
id|irq
)paren
suffix:semicolon
r_int
id|acpi_pci_link_set_irq
(paren
r_struct
id|acpi_prt_entry
op_star
id|entry
comma
r_int
id|irq
)paren
suffix:semicolon
r_int
id|acpi_pci_link_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_pci_link_exit
(paren
r_void
)paren
suffix:semicolon
r_int
id|acpi_pci_root_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_pci_root_exit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------------&n;                                  Power Resource&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_POWER_COMPONENT
mdefine_line|#define ACPI_POWER_COMPONENT&t;&t;0x01000000
DECL|macro|ACPI_POWER_CLASS
mdefine_line|#define ACPI_POWER_CLASS&t;&t;&quot;power_resource&quot;
DECL|macro|ACPI_POWER_HID
mdefine_line|#define ACPI_POWER_HID&t;&t;&t;&quot;ACPI_PWR&quot;
DECL|macro|ACPI_POWER_DRIVER_NAME
mdefine_line|#define ACPI_POWER_DRIVER_NAME&t;&t;&quot;ACPI Power Resource Driver&quot;
DECL|macro|ACPI_POWER_DEVICE_NAME
mdefine_line|#define ACPI_POWER_DEVICE_NAME&t;&t;&quot;Power Resource&quot;
DECL|macro|ACPI_POWER_FILE_INFO
mdefine_line|#define ACPI_POWER_FILE_INFO&t;&t;&quot;info&quot;
DECL|macro|ACPI_POWER_FILE_STATUS
mdefine_line|#define ACPI_POWER_FILE_STATUS&t;&t;&quot;state&quot;
DECL|macro|ACPI_POWER_RESOURCE_STATE_OFF
mdefine_line|#define ACPI_POWER_RESOURCE_STATE_OFF&t;0x00
DECL|macro|ACPI_POWER_RESOURCE_STATE_ON
mdefine_line|#define ACPI_POWER_RESOURCE_STATE_ON&t;0x01
DECL|macro|ACPI_POWER_RESOURCE_STATE_UNKNOWN
mdefine_line|#define ACPI_POWER_RESOURCE_STATE_UNKNOWN 0xFF
macro_line|#ifdef CONFIG_ACPI_POWER
r_int
id|acpi_power_get_inferred_state
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_int
id|acpi_power_transition
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|state
)paren
suffix:semicolon
r_int
id|acpi_power_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_power_exit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------------&n;                                    Processor&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_PROCESSOR_COMPONENT
mdefine_line|#define ACPI_PROCESSOR_COMPONENT&t;0x02000000
DECL|macro|ACPI_PROCESSOR_CLASS
mdefine_line|#define ACPI_PROCESSOR_CLASS&t;&t;&quot;processor&quot;
DECL|macro|ACPI_PROCESSOR_HID
mdefine_line|#define ACPI_PROCESSOR_HID&t;&t;&quot;ACPI_CPU&quot;
DECL|macro|ACPI_PROCESSOR_DRIVER_NAME
mdefine_line|#define ACPI_PROCESSOR_DRIVER_NAME&t;&quot;ACPI Processor Driver&quot;
DECL|macro|ACPI_PROCESSOR_DEVICE_NAME
mdefine_line|#define ACPI_PROCESSOR_DEVICE_NAME&t;&quot;Processor&quot;
DECL|macro|ACPI_PROCESSOR_FILE_INFO
mdefine_line|#define ACPI_PROCESSOR_FILE_INFO&t;&quot;info&quot;
DECL|macro|ACPI_PROCESSOR_FILE_POWER
mdefine_line|#define ACPI_PROCESSOR_FILE_POWER&t;&quot;power&quot;
DECL|macro|ACPI_PROCESSOR_FILE_PERFORMANCE
mdefine_line|#define ACPI_PROCESSOR_FILE_PERFORMANCE&t;&quot;performance&quot;
DECL|macro|ACPI_PROCESSOR_FILE_THROTTLING
mdefine_line|#define ACPI_PROCESSOR_FILE_THROTTLING&t;&quot;throttling&quot;
DECL|macro|ACPI_PROCESSOR_FILE_LIMIT
mdefine_line|#define ACPI_PROCESSOR_FILE_LIMIT&t;&quot;limit&quot;
DECL|macro|ACPI_PROCESSOR_NOTIFY_PERFORMANCE
mdefine_line|#define ACPI_PROCESSOR_NOTIFY_PERFORMANCE 0x80
DECL|macro|ACPI_PROCESSOR_NOTIFY_POWER
mdefine_line|#define ACPI_PROCESSOR_NOTIFY_POWER&t;0x81
DECL|macro|ACPI_PROCESSOR_LIMIT_NONE
mdefine_line|#define ACPI_PROCESSOR_LIMIT_NONE&t;0x00
DECL|macro|ACPI_PROCESSOR_LIMIT_INCREMENT
mdefine_line|#define ACPI_PROCESSOR_LIMIT_INCREMENT&t;0x01
DECL|macro|ACPI_PROCESSOR_LIMIT_DECREMENT
mdefine_line|#define ACPI_PROCESSOR_LIMIT_DECREMENT&t;0x02
r_int
id|acpi_processor_set_thermal_limit
c_func
(paren
id|acpi_handle
id|handle
comma
r_int
id|type
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                                     System&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_SYSTEM_COMPONENT
mdefine_line|#define ACPI_SYSTEM_COMPONENT&t;&t;0x04000000
DECL|macro|ACPI_SYSTEM_CLASS
mdefine_line|#define ACPI_SYSTEM_CLASS&t;&t;&quot;system&quot;
DECL|macro|ACPI_SYSTEM_HID
mdefine_line|#define ACPI_SYSTEM_HID&t;&t;&t;&quot;ACPI_SYS&quot;
DECL|macro|ACPI_SYSTEM_DRIVER_NAME
mdefine_line|#define ACPI_SYSTEM_DRIVER_NAME&t;&t;&quot;ACPI System Driver&quot;
DECL|macro|ACPI_SYSTEM_DEVICE_NAME
mdefine_line|#define ACPI_SYSTEM_DEVICE_NAME&t;&t;&quot;System&quot;
DECL|macro|ACPI_SYSTEM_FILE_INFO
mdefine_line|#define ACPI_SYSTEM_FILE_INFO&t;&t;&quot;info&quot;
DECL|macro|ACPI_SYSTEM_FILE_EVENT
mdefine_line|#define ACPI_SYSTEM_FILE_EVENT&t;&t;&quot;event&quot;
DECL|macro|ACPI_SYSTEM_FILE_ALARM
mdefine_line|#define ACPI_SYSTEM_FILE_ALARM&t;&t;&quot;alarm&quot;
DECL|macro|ACPI_SYSTEM_FILE_DSDT
mdefine_line|#define ACPI_SYSTEM_FILE_DSDT&t;&t;&quot;dsdt&quot;
DECL|macro|ACPI_SYSTEM_FILE_FADT
mdefine_line|#define ACPI_SYSTEM_FILE_FADT&t;&t;&quot;fadt&quot;
DECL|macro|ACPI_SYSTEM_FILE_SLEEP
mdefine_line|#define ACPI_SYSTEM_FILE_SLEEP&t;&t;&quot;sleep&quot;
DECL|macro|ACPI_SYSTEM_FILE_DEBUG_LAYER
mdefine_line|#define ACPI_SYSTEM_FILE_DEBUG_LAYER&t;&quot;debug_layer&quot;
DECL|macro|ACPI_SYSTEM_FILE_DEBUG_LEVEL
mdefine_line|#define ACPI_SYSTEM_FILE_DEBUG_LEVEL&t;&quot;debug_level&quot;
macro_line|#ifdef CONFIG_ACPI_SYSTEM
r_int
id|acpi_system_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_system_exit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------------&n;                                 Thermal Zone&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_THERMAL_COMPONENT
mdefine_line|#define ACPI_THERMAL_COMPONENT&t;&t;0x08000000
DECL|macro|ACPI_THERMAL_CLASS
mdefine_line|#define ACPI_THERMAL_CLASS&t;&t;&quot;thermal_zone&quot;
DECL|macro|ACPI_THERMAL_HID
mdefine_line|#define ACPI_THERMAL_HID&t;&t;&quot;ACPI_THM&quot;
DECL|macro|ACPI_THERMAL_DRIVER_NAME
mdefine_line|#define ACPI_THERMAL_DRIVER_NAME&t;&quot;ACPI Thermal Zone Driver&quot;
DECL|macro|ACPI_THERMAL_DEVICE_NAME
mdefine_line|#define ACPI_THERMAL_DEVICE_NAME&t;&quot;Thermal Zone&quot;
DECL|macro|ACPI_THERMAL_FILE_STATE
mdefine_line|#define ACPI_THERMAL_FILE_STATE&t;&t;&quot;state&quot;
DECL|macro|ACPI_THERMAL_FILE_TEMPERATURE
mdefine_line|#define ACPI_THERMAL_FILE_TEMPERATURE&t;&quot;temperature&quot;
DECL|macro|ACPI_THERMAL_FILE_TRIP_POINTS
mdefine_line|#define ACPI_THERMAL_FILE_TRIP_POINTS&t;&quot;trip_points&quot;
DECL|macro|ACPI_THERMAL_FILE_COOLING_MODE
mdefine_line|#define ACPI_THERMAL_FILE_COOLING_MODE&t;&quot;cooling_mode&quot;
DECL|macro|ACPI_THERMAL_FILE_POLLING_FREQ
mdefine_line|#define ACPI_THERMAL_FILE_POLLING_FREQ&t;&quot;polling_frequency&quot;
DECL|macro|ACPI_THERMAL_NOTIFY_TEMPERATURE
mdefine_line|#define ACPI_THERMAL_NOTIFY_TEMPERATURE&t;0x80
DECL|macro|ACPI_THERMAL_NOTIFY_THRESHOLDS
mdefine_line|#define ACPI_THERMAL_NOTIFY_THRESHOLDS&t;0x81
DECL|macro|ACPI_THERMAL_NOTIFY_DEVICES
mdefine_line|#define ACPI_THERMAL_NOTIFY_DEVICES&t;0x82
DECL|macro|ACPI_THERMAL_NOTIFY_CRITICAL
mdefine_line|#define ACPI_THERMAL_NOTIFY_CRITICAL&t;0xF0
DECL|macro|ACPI_THERMAL_NOTIFY_HOT
mdefine_line|#define ACPI_THERMAL_NOTIFY_HOT&t;&t;0xF1
DECL|macro|ACPI_THERMAL_MODE_ACTIVE
mdefine_line|#define ACPI_THERMAL_MODE_ACTIVE&t;0x00
DECL|macro|ACPI_THERMAL_MODE_PASSIVE
mdefine_line|#define ACPI_THERMAL_MODE_PASSIVE&t;0x01
DECL|macro|ACPI_THERMAL_PATH_POWEROFF
mdefine_line|#define ACPI_THERMAL_PATH_POWEROFF&t;&quot;/sbin/poweroff&quot;
multiline_comment|/* --------------------------------------------------------------------------&n;                                Debug Support&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_DEBUG_RESTORE
mdefine_line|#define ACPI_DEBUG_RESTORE&t;0
DECL|macro|ACPI_DEBUG_LOW
mdefine_line|#define ACPI_DEBUG_LOW&t;&t;1
DECL|macro|ACPI_DEBUG_MEDIUM
mdefine_line|#define ACPI_DEBUG_MEDIUM&t;2
DECL|macro|ACPI_DEBUG_HIGH
mdefine_line|#define ACPI_DEBUG_HIGH&t;&t;3
DECL|macro|ACPI_DEBUG_DRIVERS
mdefine_line|#define ACPI_DEBUG_DRIVERS&t;4
r_extern
id|u32
id|acpi_dbg_level
suffix:semicolon
r_extern
id|u32
id|acpi_dbg_layer
suffix:semicolon
r_static
r_inline
r_void
DECL|function|acpi_set_debug
id|acpi_set_debug
(paren
id|u32
id|flag
)paren
(brace
r_static
id|u32
id|layer_save
suffix:semicolon
r_static
id|u32
id|level_save
suffix:semicolon
r_switch
c_cond
(paren
id|flag
)paren
(brace
r_case
id|ACPI_DEBUG_RESTORE
suffix:colon
id|acpi_dbg_layer
op_assign
id|layer_save
suffix:semicolon
id|acpi_dbg_level
op_assign
id|level_save
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DEBUG_LOW
suffix:colon
r_case
id|ACPI_DEBUG_MEDIUM
suffix:colon
r_case
id|ACPI_DEBUG_HIGH
suffix:colon
r_case
id|ACPI_DEBUG_DRIVERS
suffix:colon
id|layer_save
op_assign
id|acpi_dbg_layer
suffix:semicolon
id|level_save
op_assign
id|acpi_dbg_level
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|flag
)paren
(brace
r_case
id|ACPI_DEBUG_LOW
suffix:colon
id|acpi_dbg_layer
op_assign
id|ACPI_COMPONENT_DEFAULT
op_or
id|ACPI_ALL_DRIVERS
suffix:semicolon
id|acpi_dbg_level
op_assign
id|DEBUG_DEFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DEBUG_MEDIUM
suffix:colon
id|acpi_dbg_layer
op_assign
id|ACPI_COMPONENT_DEFAULT
op_or
id|ACPI_ALL_DRIVERS
suffix:semicolon
id|acpi_dbg_level
op_assign
id|ACPI_LV_FUNCTIONS
op_or
id|ACPI_LV_ALL_EXCEPTIONS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DEBUG_HIGH
suffix:colon
id|acpi_dbg_layer
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
id|acpi_dbg_level
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DEBUG_DRIVERS
suffix:colon
id|acpi_dbg_layer
op_assign
id|ACPI_ALL_DRIVERS
suffix:semicolon
id|acpi_dbg_level
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif /*__ACPI_DRIVERS_H__*/
eof
