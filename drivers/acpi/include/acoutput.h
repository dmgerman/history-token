multiline_comment|/******************************************************************************&n; *&n; * Name: acoutput.h -- debug output&n; *       $Revision: 87 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACOUTPUT_H__
DECL|macro|__ACOUTPUT_H__
mdefine_line|#define __ACOUTPUT_H__
multiline_comment|/*&n; * Debug levels and component IDs.  These are used to control the&n; * granularity of the output of the DEBUG_PRINT macro -- on a per-&n; * component basis and a per-exception-type basis.&n; */
multiline_comment|/* Component IDs are used in the global &quot;Debug_layer&quot; */
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
DECL|macro|ACPI_ALL_COMPONENTS
mdefine_line|#define ACPI_ALL_COMPONENTS         0x00000FFF
DECL|macro|ACPI_COMPONENT_DEFAULT
mdefine_line|#define ACPI_COMPONENT_DEFAULT      (ACPI_ALL_COMPONENTS)
multiline_comment|/* Component IDs for ACPI tools and utilities */
DECL|macro|ACPI_COMPILER
mdefine_line|#define ACPI_COMPILER               0x00001000
DECL|macro|ACPI_TOOLS
mdefine_line|#define ACPI_TOOLS                  0x00002000
multiline_comment|/* Component IDs reserved for ACPI drivers */
DECL|macro|ACPI_ALL_DRIVERS
mdefine_line|#define ACPI_ALL_DRIVERS            0xFFFF0000
multiline_comment|/*&n; * Raw debug output levels, do not use these in the DEBUG_PRINT macros&n; */
DECL|macro|ACPI_LV_OK
mdefine_line|#define ACPI_LV_OK                  0x00000001
DECL|macro|ACPI_LV_INFO
mdefine_line|#define ACPI_LV_INFO                0x00000002
DECL|macro|ACPI_LV_WARN
mdefine_line|#define ACPI_LV_WARN                0x00000004
DECL|macro|ACPI_LV_ERROR
mdefine_line|#define ACPI_LV_ERROR               0x00000008
DECL|macro|ACPI_LV_FATAL
mdefine_line|#define ACPI_LV_FATAL               0x00000010
DECL|macro|ACPI_LV_DEBUG_OBJECT
mdefine_line|#define ACPI_LV_DEBUG_OBJECT        0x00000020
DECL|macro|ACPI_LV_ALL_EXCEPTIONS
mdefine_line|#define ACPI_LV_ALL_EXCEPTIONS      0x0000003F
multiline_comment|/* Trace verbosity level 1 [Standard Trace Level] */
DECL|macro|ACPI_LV_PARSE
mdefine_line|#define ACPI_LV_PARSE               0x00000040
DECL|macro|ACPI_LV_LOAD
mdefine_line|#define ACPI_LV_LOAD                0x00000080
DECL|macro|ACPI_LV_DISPATCH
mdefine_line|#define ACPI_LV_DISPATCH            0x00000100
DECL|macro|ACPI_LV_EXEC
mdefine_line|#define ACPI_LV_EXEC                0x00000200
DECL|macro|ACPI_LV_NAMES
mdefine_line|#define ACPI_LV_NAMES               0x00000400
DECL|macro|ACPI_LV_OPREGION
mdefine_line|#define ACPI_LV_OPREGION            0x00000800
DECL|macro|ACPI_LV_BFIELD
mdefine_line|#define ACPI_LV_BFIELD              0x00001000
DECL|macro|ACPI_LV_TABLES
mdefine_line|#define ACPI_LV_TABLES              0x00002000
DECL|macro|ACPI_LV_VALUES
mdefine_line|#define ACPI_LV_VALUES              0x00004000
DECL|macro|ACPI_LV_OBJECTS
mdefine_line|#define ACPI_LV_OBJECTS             0x00008000
DECL|macro|ACPI_LV_RESOURCES
mdefine_line|#define ACPI_LV_RESOURCES           0x00010000
DECL|macro|ACPI_LV_USER_REQUESTS
mdefine_line|#define ACPI_LV_USER_REQUESTS       0x00020000
DECL|macro|ACPI_LV_PACKAGE
mdefine_line|#define ACPI_LV_PACKAGE             0x00040000
DECL|macro|ACPI_LV_INIT
mdefine_line|#define ACPI_LV_INIT                0x00080000
DECL|macro|ACPI_LV_VERBOSITY1
mdefine_line|#define ACPI_LV_VERBOSITY1          0x000FFF40 | ACPI_LV_ALL_EXCEPTIONS
multiline_comment|/* Trace verbosity level 2 [Function tracing and memory allocation] */
DECL|macro|ACPI_LV_ALLOCATIONS
mdefine_line|#define ACPI_LV_ALLOCATIONS         0x00100000
DECL|macro|ACPI_LV_FUNCTIONS
mdefine_line|#define ACPI_LV_FUNCTIONS           0x00200000
DECL|macro|ACPI_LV_VERBOSITY2
mdefine_line|#define ACPI_LV_VERBOSITY2          0x00300000 | ACPI_LV_VERBOSITY1
DECL|macro|ACPI_LV_ALL
mdefine_line|#define ACPI_LV_ALL                 ACPI_LV_VERBOSITY2
multiline_comment|/* Trace verbosity level 3 [Threading, I/O, and Interrupts] */
DECL|macro|ACPI_LV_MUTEX
mdefine_line|#define ACPI_LV_MUTEX               0x01000000
DECL|macro|ACPI_LV_THREADS
mdefine_line|#define ACPI_LV_THREADS             0x02000000
DECL|macro|ACPI_LV_IO
mdefine_line|#define ACPI_LV_IO                  0x04000000
DECL|macro|ACPI_LV_INTERRUPTS
mdefine_line|#define ACPI_LV_INTERRUPTS          0x08000000
DECL|macro|ACPI_LV_VERBOSITY3
mdefine_line|#define ACPI_LV_VERBOSITY3          0x0F000000 | ACPI_LV_VERBOSITY2
multiline_comment|/* Exceptionally verbose output -- also used in the global &quot;Debug_level&quot; */
DECL|macro|ACPI_LV_AML_DISASSEMBLE
mdefine_line|#define ACPI_LV_AML_DISASSEMBLE     0x10000000
DECL|macro|ACPI_LV_VERBOSE_INFO
mdefine_line|#define ACPI_LV_VERBOSE_INFO        0x20000000
DECL|macro|ACPI_LV_FULL_TABLES
mdefine_line|#define ACPI_LV_FULL_TABLES         0x40000000
DECL|macro|ACPI_LV_EVENTS
mdefine_line|#define ACPI_LV_EVENTS              0x80000000
DECL|macro|ACPI_LV_VERBOSE
mdefine_line|#define ACPI_LV_VERBOSE             0xF0000000
multiline_comment|/*&n; * Debug level macros that are used in the DEBUG_PRINT macros&n; */
DECL|macro|ACPI_DEBUG_LEVEL
mdefine_line|#define ACPI_DEBUG_LEVEL(dl)       dl,__LINE__,&amp;_dbg
multiline_comment|/* Exception level -- used in the global &quot;Debug_level&quot; */
DECL|macro|ACPI_DB_OK
mdefine_line|#define ACPI_DB_OK                  ACPI_DEBUG_LEVEL (ACPI_LV_OK)
DECL|macro|ACPI_DB_INFO
mdefine_line|#define ACPI_DB_INFO                ACPI_DEBUG_LEVEL (ACPI_LV_INFO)
DECL|macro|ACPI_DB_WARN
mdefine_line|#define ACPI_DB_WARN                ACPI_DEBUG_LEVEL (ACPI_LV_WARN)
DECL|macro|ACPI_DB_ERROR
mdefine_line|#define ACPI_DB_ERROR               ACPI_DEBUG_LEVEL (ACPI_LV_ERROR)
DECL|macro|ACPI_DB_FATAL
mdefine_line|#define ACPI_DB_FATAL               ACPI_DEBUG_LEVEL (ACPI_LV_FATAL)
DECL|macro|ACPI_DB_DEBUG_OBJECT
mdefine_line|#define ACPI_DB_DEBUG_OBJECT        ACPI_DEBUG_LEVEL (ACPI_LV_DEBUG_OBJECT)
DECL|macro|ACPI_DB_ALL_EXCEPTIONS
mdefine_line|#define ACPI_DB_ALL_EXCEPTIONS      ACPI_DEBUG_LEVEL (ACPI_LV_ALL_EXCEPTIONS)
multiline_comment|/* Trace level -- also used in the global &quot;Debug_level&quot; */
DECL|macro|ACPI_DB_THREADS
mdefine_line|#define ACPI_DB_THREADS             ACPI_DEBUG_LEVEL (ACPI_LV_THREADS)
DECL|macro|ACPI_DB_PARSE
mdefine_line|#define ACPI_DB_PARSE               ACPI_DEBUG_LEVEL (ACPI_LV_PARSE)
DECL|macro|ACPI_DB_DISPATCH
mdefine_line|#define ACPI_DB_DISPATCH            ACPI_DEBUG_LEVEL (ACPI_LV_DISPATCH)
DECL|macro|ACPI_DB_LOAD
mdefine_line|#define ACPI_DB_LOAD                ACPI_DEBUG_LEVEL (ACPI_LV_LOAD)
DECL|macro|ACPI_DB_EXEC
mdefine_line|#define ACPI_DB_EXEC                ACPI_DEBUG_LEVEL (ACPI_LV_EXEC)
DECL|macro|ACPI_DB_NAMES
mdefine_line|#define ACPI_DB_NAMES               ACPI_DEBUG_LEVEL (ACPI_LV_NAMES)
DECL|macro|ACPI_DB_OPREGION
mdefine_line|#define ACPI_DB_OPREGION            ACPI_DEBUG_LEVEL (ACPI_LV_OPREGION)
DECL|macro|ACPI_DB_BFIELD
mdefine_line|#define ACPI_DB_BFIELD              ACPI_DEBUG_LEVEL (ACPI_LV_BFIELD)
DECL|macro|ACPI_DB_TABLES
mdefine_line|#define ACPI_DB_TABLES              ACPI_DEBUG_LEVEL (ACPI_LV_TABLES)
DECL|macro|ACPI_DB_FUNCTIONS
mdefine_line|#define ACPI_DB_FUNCTIONS           ACPI_DEBUG_LEVEL (ACPI_LV_FUNCTIONS)
DECL|macro|ACPI_DB_VALUES
mdefine_line|#define ACPI_DB_VALUES              ACPI_DEBUG_LEVEL (ACPI_LV_VALUES)
DECL|macro|ACPI_DB_OBJECTS
mdefine_line|#define ACPI_DB_OBJECTS             ACPI_DEBUG_LEVEL (ACPI_LV_OBJECTS)
DECL|macro|ACPI_DB_ALLOCATIONS
mdefine_line|#define ACPI_DB_ALLOCATIONS         ACPI_DEBUG_LEVEL (ACPI_LV_ALLOCATIONS)
DECL|macro|ACPI_DB_RESOURCES
mdefine_line|#define ACPI_DB_RESOURCES           ACPI_DEBUG_LEVEL (ACPI_LV_RESOURCES)
DECL|macro|ACPI_DB_IO
mdefine_line|#define ACPI_DB_IO                  ACPI_DEBUG_LEVEL (ACPI_LV_IO)
DECL|macro|ACPI_DB_INTERRUPTS
mdefine_line|#define ACPI_DB_INTERRUPTS          ACPI_DEBUG_LEVEL (ACPI_LV_INTERRUPTS)
DECL|macro|ACPI_DB_USER_REQUESTS
mdefine_line|#define ACPI_DB_USER_REQUESTS       ACPI_DEBUG_LEVEL (ACPI_LV_USER_REQUESTS)
DECL|macro|ACPI_DB_PACKAGE
mdefine_line|#define ACPI_DB_PACKAGE             ACPI_DEBUG_LEVEL (ACPI_LV_PACKAGE)
DECL|macro|ACPI_DB_MUTEX
mdefine_line|#define ACPI_DB_MUTEX               ACPI_DEBUG_LEVEL (ACPI_LV_MUTEX)
DECL|macro|ACPI_DB_INIT
mdefine_line|#define ACPI_DB_INIT                ACPI_DEBUG_LEVEL (ACPI_LV_INIT)
DECL|macro|ACPI_DB_ALL
mdefine_line|#define ACPI_DB_ALL                 ACPI_DEBUG_LEVEL (ACPI_LV_ALL)
multiline_comment|/* Defaults for Debug_level, debug and normal */
DECL|macro|DEBUG_DEFAULT
mdefine_line|#define DEBUG_DEFAULT               (ACPI_LV_OK | ACPI_LV_WARN | ACPI_LV_ERROR | ACPI_LV_DEBUG_OBJECT)
DECL|macro|NORMAL_DEFAULT
mdefine_line|#define NORMAL_DEFAULT              (ACPI_LV_OK | ACPI_LV_WARN | ACPI_LV_ERROR | ACPI_LV_DEBUG_OBJECT)
DECL|macro|DEBUG_ALL
mdefine_line|#define DEBUG_ALL                   (ACPI_LV_AML_DISASSEMBLE | ACPI_LV_ALL_EXCEPTIONS | ACPI_LV_ALL)
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
