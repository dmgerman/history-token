multiline_comment|/******************************************************************************&n; *&n; * Name: acoutput.h -- debug output&n; *       $Revision: 78 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACOUTPUT_H__
DECL|macro|__ACOUTPUT_H__
mdefine_line|#define __ACOUTPUT_H__
multiline_comment|/*&n; * Debug levels and component IDs.  These are used to control the&n; * granularity of the output of the DEBUG_PRINT macro -- on a per-&n; * component basis and a per-exception-type basis.&n; */
multiline_comment|/* Component IDs -- used in the global &quot;Debug_layer&quot; */
DECL|macro|ACPI_UTILITIES
mdefine_line|#define ACPI_UTILITIES              0x00000001
DECL|macro|ACPI_HARDWARE
mdefine_line|#define ACPI_HARDWARE               0x00000002
DECL|macro|ACPI_EVENTS
mdefine_line|#define ACPI_EVENTS                 0x00000004
DECL|macro|ACPI_TABLES
mdefine_line|#define ACPI_TABLES                 0x00000008
DECL|macro|ACPI_NAMESPACE
mdefine_line|#define ACPI_NAMESPACE              0x00000010
DECL|macro|ACPI_PARSER
mdefine_line|#define ACPI_PARSER                 0x00000020
DECL|macro|ACPI_DISPATCHER
mdefine_line|#define ACPI_DISPATCHER             0x00000040
DECL|macro|ACPI_EXECUTER
mdefine_line|#define ACPI_EXECUTER               0x00000080
DECL|macro|ACPI_RESOURCES
mdefine_line|#define ACPI_RESOURCES              0x00000100
DECL|macro|ACPI_DEBUGGER
mdefine_line|#define ACPI_DEBUGGER               0x00000200
DECL|macro|ACPI_OS_SERVICES
mdefine_line|#define ACPI_OS_SERVICES            0x00000400
DECL|macro|ACPI_BUS
mdefine_line|#define ACPI_BUS                    0x00001000
DECL|macro|ACPI_SYSTEM
mdefine_line|#define ACPI_SYSTEM                 0x00002000
DECL|macro|ACPI_POWER
mdefine_line|#define ACPI_POWER                  0x00004000
DECL|macro|ACPI_EC
mdefine_line|#define ACPI_EC                     0x00008000
DECL|macro|ACPI_AC_ADAPTER
mdefine_line|#define ACPI_AC_ADAPTER             0x00010000
DECL|macro|ACPI_BATTERY
mdefine_line|#define ACPI_BATTERY                0x00020000
DECL|macro|ACPI_BUTTON
mdefine_line|#define ACPI_BUTTON                 0x00040000
DECL|macro|ACPI_PROCESSOR
mdefine_line|#define ACPI_PROCESSOR              0x00080000
DECL|macro|ACPI_THERMAL
mdefine_line|#define ACPI_THERMAL                0x00100000
DECL|macro|ACPI_ALL_COMPONENTS
mdefine_line|#define ACPI_ALL_COMPONENTS         0x00FFFFFF
DECL|macro|ACPI_COMPONENT_DEFAULT
mdefine_line|#define ACPI_COMPONENT_DEFAULT      (ACPI_ALL_COMPONENTS)
DECL|macro|ACPI_COMPILER
mdefine_line|#define ACPI_COMPILER               0x10000000
DECL|macro|ACPI_TOOLS
mdefine_line|#define ACPI_TOOLS                  0x20000000
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
DECL|macro|TRACE_THREADS
mdefine_line|#define TRACE_THREADS               0x00000080
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
DECL|macro|TRACE_INIT
mdefine_line|#define TRACE_INIT                  0x08000000
DECL|macro|TRACE_ALL
mdefine_line|#define TRACE_ALL                   0x0FFFFF80
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
