multiline_comment|/******************************************************************************&n; *&n; * Name: acoutput.h -- debug output&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACOUTPUT_H__
DECL|macro|__ACOUTPUT_H__
mdefine_line|#define __ACOUTPUT_H__
multiline_comment|/*&n; * Debug levels and component IDs.  These are used to control the&n; * granularity of the output of the DEBUG_PRINT macro -- on a per-&n; * component basis and a per-exception-type basis.&n; */
multiline_comment|/* Component IDs are used in the global &quot;debug_layer&quot; */
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
DECL|macro|ACPI_CA_DEBUGGER
mdefine_line|#define ACPI_CA_DEBUGGER            0x00000200
DECL|macro|ACPI_OS_SERVICES
mdefine_line|#define ACPI_OS_SERVICES            0x00000400
DECL|macro|ACPI_CA_DISASSEMBLER
mdefine_line|#define ACPI_CA_DISASSEMBLER        0x00000800
multiline_comment|/* Component IDs for ACPI tools and utilities */
DECL|macro|ACPI_COMPILER
mdefine_line|#define ACPI_COMPILER               0x00001000
DECL|macro|ACPI_TOOLS
mdefine_line|#define ACPI_TOOLS                  0x00002000
DECL|macro|ACPI_ALL_COMPONENTS
mdefine_line|#define ACPI_ALL_COMPONENTS         0x00003FFF
DECL|macro|ACPI_COMPONENT_DEFAULT
mdefine_line|#define ACPI_COMPONENT_DEFAULT      (ACPI_ALL_COMPONENTS)
multiline_comment|/* Component IDs reserved for ACPI drivers */
DECL|macro|ACPI_ALL_DRIVERS
mdefine_line|#define ACPI_ALL_DRIVERS            0xFFFF0000
multiline_comment|/*&n; * Raw debug output levels, do not use these in the DEBUG_PRINT macros&n; */
DECL|macro|ACPI_LV_ERROR
mdefine_line|#define ACPI_LV_ERROR               0x00000001
DECL|macro|ACPI_LV_WARN
mdefine_line|#define ACPI_LV_WARN                0x00000002
DECL|macro|ACPI_LV_INIT
mdefine_line|#define ACPI_LV_INIT                0x00000004
DECL|macro|ACPI_LV_DEBUG_OBJECT
mdefine_line|#define ACPI_LV_DEBUG_OBJECT        0x00000008
DECL|macro|ACPI_LV_INFO
mdefine_line|#define ACPI_LV_INFO                0x00000010
DECL|macro|ACPI_LV_ALL_EXCEPTIONS
mdefine_line|#define ACPI_LV_ALL_EXCEPTIONS      0x0000001F
multiline_comment|/* Trace verbosity level 1 [Standard Trace Level] */
DECL|macro|ACPI_LV_INIT_NAMES
mdefine_line|#define ACPI_LV_INIT_NAMES          0x00000020
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
DECL|macro|ACPI_LV_VERBOSITY1
mdefine_line|#define ACPI_LV_VERBOSITY1          0x0007FF40 | ACPI_LV_ALL_EXCEPTIONS
multiline_comment|/* Trace verbosity level 2 [Function tracing and memory allocation] */
DECL|macro|ACPI_LV_ALLOCATIONS
mdefine_line|#define ACPI_LV_ALLOCATIONS         0x00100000
DECL|macro|ACPI_LV_FUNCTIONS
mdefine_line|#define ACPI_LV_FUNCTIONS           0x00200000
DECL|macro|ACPI_LV_OPTIMIZATIONS
mdefine_line|#define ACPI_LV_OPTIMIZATIONS       0x00400000
DECL|macro|ACPI_LV_VERBOSITY2
mdefine_line|#define ACPI_LV_VERBOSITY2          0x00700000 | ACPI_LV_VERBOSITY1
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
multiline_comment|/* Exceptionally verbose output -- also used in the global &quot;debug_level&quot; */
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
mdefine_line|#define ACPI_DEBUG_LEVEL(dl)        (u32) dl,__LINE__,&amp;_debug_info
multiline_comment|/* Exception level -- used in the global &quot;debug_level&quot; */
DECL|macro|ACPI_DB_ERROR
mdefine_line|#define ACPI_DB_ERROR               ACPI_DEBUG_LEVEL (ACPI_LV_ERROR)
DECL|macro|ACPI_DB_WARN
mdefine_line|#define ACPI_DB_WARN                ACPI_DEBUG_LEVEL (ACPI_LV_WARN)
DECL|macro|ACPI_DB_INIT
mdefine_line|#define ACPI_DB_INIT                ACPI_DEBUG_LEVEL (ACPI_LV_INIT)
DECL|macro|ACPI_DB_DEBUG_OBJECT
mdefine_line|#define ACPI_DB_DEBUG_OBJECT        ACPI_DEBUG_LEVEL (ACPI_LV_DEBUG_OBJECT)
DECL|macro|ACPI_DB_INFO
mdefine_line|#define ACPI_DB_INFO                ACPI_DEBUG_LEVEL (ACPI_LV_INFO)
DECL|macro|ACPI_DB_ALL_EXCEPTIONS
mdefine_line|#define ACPI_DB_ALL_EXCEPTIONS      ACPI_DEBUG_LEVEL (ACPI_LV_ALL_EXCEPTIONS)
multiline_comment|/* Trace level -- also used in the global &quot;debug_level&quot; */
DECL|macro|ACPI_DB_INIT_NAMES
mdefine_line|#define ACPI_DB_INIT_NAMES          ACPI_DEBUG_LEVEL (ACPI_LV_INIT_NAMES)
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
DECL|macro|ACPI_DB_OPTIMIZATIONS
mdefine_line|#define ACPI_DB_OPTIMIZATIONS       ACPI_DEBUG_LEVEL (ACPI_LV_OPTIMIZATIONS)
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
DECL|macro|ACPI_DB_ALL
mdefine_line|#define ACPI_DB_ALL                 ACPI_DEBUG_LEVEL (ACPI_LV_ALL)
multiline_comment|/* Defaults for debug_level, debug and normal */
DECL|macro|ACPI_DEBUG_DEFAULT
mdefine_line|#define ACPI_DEBUG_DEFAULT          (ACPI_LV_INIT | ACPI_LV_WARN | ACPI_LV_ERROR | ACPI_LV_DEBUG_OBJECT)
DECL|macro|ACPI_NORMAL_DEFAULT
mdefine_line|#define ACPI_NORMAL_DEFAULT         (ACPI_LV_INIT | ACPI_LV_WARN | ACPI_LV_ERROR | ACPI_LV_DEBUG_OBJECT)
DECL|macro|ACPI_DEBUG_ALL
mdefine_line|#define ACPI_DEBUG_ALL              (ACPI_LV_AML_DISASSEMBLE | ACPI_LV_ALL_EXCEPTIONS | ACPI_LV_ALL)
macro_line|#endif /* __ACOUTPUT_H__ */
eof
