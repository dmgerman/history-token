multiline_comment|/******************************************************************************&n; *&n; * Name: acoutput.h -- debug output&n; *       $Revision: 68 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACOUTPUT_H__
DECL|macro|__ACOUTPUT_H__
mdefine_line|#define __ACOUTPUT_H__
multiline_comment|/*&n; * Debug levels and component IDs.  These are used to control the&n; * granularity of the output of the DEBUG_PRINT macro -- on a per-&n; * component basis and a per-exception-type basis.&n; */
multiline_comment|/* Component IDs -- used in the global &quot;Debug_layer&quot; */
DECL|macro|GLOBAL
mdefine_line|#define GLOBAL                      0x00000001
DECL|macro|COMMON
mdefine_line|#define COMMON                      0x00000002
DECL|macro|PARSER
mdefine_line|#define PARSER                      0x00000004
DECL|macro|DISPATCHER
mdefine_line|#define DISPATCHER                  0x00000008
DECL|macro|INTERPRETER
mdefine_line|#define INTERPRETER                 0x00000010
DECL|macro|NAMESPACE
mdefine_line|#define NAMESPACE                   0x00000020
DECL|macro|RESOURCE_MANAGER
mdefine_line|#define RESOURCE_MANAGER            0x00000040
DECL|macro|TABLE_MANAGER
mdefine_line|#define TABLE_MANAGER               0x00000080
DECL|macro|EVENT_HANDLING
mdefine_line|#define EVENT_HANDLING              0x00000100
DECL|macro|HARDWARE
mdefine_line|#define HARDWARE                    0x00000200
DECL|macro|MISCELLANEOUS
mdefine_line|#define MISCELLANEOUS               0x00000400
DECL|macro|OS_DEPENDENT
mdefine_line|#define OS_DEPENDENT                0x00000800
DECL|macro|BUS_MANAGER
mdefine_line|#define BUS_MANAGER                 0x00001000
DECL|macro|PROCESSOR_CONTROL
mdefine_line|#define PROCESSOR_CONTROL           0x00002000
DECL|macro|SYSTEM_CONTROL
mdefine_line|#define SYSTEM_CONTROL              0x00004000
DECL|macro|THERMAL_CONTROL
mdefine_line|#define THERMAL_CONTROL             0x00008000
DECL|macro|POWER_CONTROL
mdefine_line|#define POWER_CONTROL               0x00010000
DECL|macro|EMBEDDED_CONTROLLER
mdefine_line|#define EMBEDDED_CONTROLLER         0x00020000
DECL|macro|BATTERY
mdefine_line|#define BATTERY                     0x00040000
DECL|macro|DEBUGGER
mdefine_line|#define DEBUGGER                    0x00100000
DECL|macro|ALL_COMPONENTS
mdefine_line|#define ALL_COMPONENTS              0x001FFFFF
DECL|macro|COMPONENT_DEFAULT
mdefine_line|#define COMPONENT_DEFAULT           (ALL_COMPONENTS)
multiline_comment|/* Exception level -- used in the global &quot;Debug_level&quot; */
DECL|macro|ACPI_OK
mdefine_line|#define ACPI_OK                     0x00000001
DECL|macro|ACPI_INFO
mdefine_line|#define ACPI_INFO                   0x00000002
DECL|macro|ACPI_WARN
mdefine_line|#define ACPI_WARN                   0x00000004
DECL|macro|ACPI_ERROR
mdefine_line|#define ACPI_ERROR                  0x00000008
DECL|macro|ACPI_FATAL
mdefine_line|#define ACPI_FATAL                  0x00000010
DECL|macro|ACPI_DEBUG_OBJECT
mdefine_line|#define ACPI_DEBUG_OBJECT           0x00000020
DECL|macro|ACPI_ALL
mdefine_line|#define ACPI_ALL                    0x0000003F
multiline_comment|/* Trace level -- also used in the global &quot;Debug_level&quot; */
DECL|macro|TRACE_PARSE
mdefine_line|#define TRACE_PARSE                 0x00000100
DECL|macro|TRACE_DISPATCH
mdefine_line|#define TRACE_DISPATCH              0x00000200
DECL|macro|TRACE_LOAD
mdefine_line|#define TRACE_LOAD                  0x00000400
DECL|macro|TRACE_EXEC
mdefine_line|#define TRACE_EXEC                  0x00000800
DECL|macro|TRACE_NAMES
mdefine_line|#define TRACE_NAMES                 0x00001000
DECL|macro|TRACE_OPREGION
mdefine_line|#define TRACE_OPREGION              0x00002000
DECL|macro|TRACE_BFIELD
mdefine_line|#define TRACE_BFIELD                0x00004000
DECL|macro|TRACE_TRASH
mdefine_line|#define TRACE_TRASH                 0x00008000
DECL|macro|TRACE_TABLES
mdefine_line|#define TRACE_TABLES                0x00010000
DECL|macro|TRACE_FUNCTIONS
mdefine_line|#define TRACE_FUNCTIONS             0x00020000
DECL|macro|TRACE_VALUES
mdefine_line|#define TRACE_VALUES                0x00040000
DECL|macro|TRACE_OBJECTS
mdefine_line|#define TRACE_OBJECTS               0x00080000
DECL|macro|TRACE_ALLOCATIONS
mdefine_line|#define TRACE_ALLOCATIONS           0x00100000
DECL|macro|TRACE_RESOURCES
mdefine_line|#define TRACE_RESOURCES             0x00200000
DECL|macro|TRACE_IO
mdefine_line|#define TRACE_IO                    0x00400000
DECL|macro|TRACE_INTERRUPTS
mdefine_line|#define TRACE_INTERRUPTS            0x00800000
DECL|macro|TRACE_USER_REQUESTS
mdefine_line|#define TRACE_USER_REQUESTS         0x01000000
DECL|macro|TRACE_PACKAGE
mdefine_line|#define TRACE_PACKAGE               0x02000000
DECL|macro|TRACE_MUTEX
mdefine_line|#define TRACE_MUTEX                 0x04000000
DECL|macro|TRACE_ALL
mdefine_line|#define TRACE_ALL                   0x0FFFFF00
multiline_comment|/* Exceptionally verbose output -- also used in the global &quot;Debug_level&quot; */
DECL|macro|VERBOSE_AML_DISASSEMBLE
mdefine_line|#define VERBOSE_AML_DISASSEMBLE     0x10000000
DECL|macro|VERBOSE_INFO
mdefine_line|#define VERBOSE_INFO                0x20000000
DECL|macro|VERBOSE_TABLES
mdefine_line|#define VERBOSE_TABLES              0x40000000
DECL|macro|VERBOSE_EVENTS
mdefine_line|#define VERBOSE_EVENTS              0x80000000
DECL|macro|VERBOSE_ALL
mdefine_line|#define VERBOSE_ALL                 0xF0000000
multiline_comment|/* Defaults for Debug_level, debug and normal */
DECL|macro|DEBUG_DEFAULT
mdefine_line|#define DEBUG_DEFAULT               (ACPI_OK | ACPI_WARN | ACPI_ERROR | ACPI_DEBUG_OBJECT)
DECL|macro|NORMAL_DEFAULT
mdefine_line|#define NORMAL_DEFAULT              (ACPI_OK | ACPI_WARN | ACPI_ERROR | ACPI_DEBUG_OBJECT)
DECL|macro|DEBUG_ALL
mdefine_line|#define DEBUG_ALL                   (VERBOSE_AML_DISASSEMBLE | TRACE_ALL | ACPI_ALL)
multiline_comment|/* Misc defines */
DECL|macro|HEX
mdefine_line|#define HEX                         0x01
DECL|macro|ASCII
mdefine_line|#define ASCII                       0x02
DECL|macro|FULL_ADDRESS
mdefine_line|#define FULL_ADDRESS                0x04
DECL|macro|CHARS_PER_LINE
mdefine_line|#define CHARS_PER_LINE              16          /* used in Dump_buf function */
macro_line|#endif /* __ACOUTPUT_H__ */
eof
