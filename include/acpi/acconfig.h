multiline_comment|/******************************************************************************&n; *&n; * Name: acconfig.h - Global configuration constants&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef _ACCONFIG_H
DECL|macro|_ACCONFIG_H
mdefine_line|#define _ACCONFIG_H
multiline_comment|/******************************************************************************&n; *&n; * Configuration options&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * ACPI_DEBUG_OUTPUT    - This switch enables all the debug facilities of the&n; *                        ACPI subsystem.  This includes the DEBUG_PRINT output&n; *                        statements.  When disabled, all DEBUG_PRINT&n; *                        statements are compiled out.&n; *&n; * ACPI_APPLICATION     - Use this switch if the subsystem is going to be run&n; *                        at the application level.&n; *&n; */
multiline_comment|/* Version string */
DECL|macro|ACPI_CA_VERSION
mdefine_line|#define ACPI_CA_VERSION                 0x20041203
multiline_comment|/*&n; * OS name, used for the _OS object.  The _OS object is essentially obsolete,&n; * but there is a large base of ASL/AML code in existing machines that check&n; * for the string below.  The use of this string usually guarantees that&n; * the ASL will execute down the most tested code path.  Also, there is some&n; * code that will not execute the _OSI method unless _OS matches the string&n; * below.  Therefore, change this string at your own risk.&n; */
DECL|macro|ACPI_OS_NAME
mdefine_line|#define ACPI_OS_NAME                    &quot;Microsoft Windows NT&quot;
multiline_comment|/* Maximum objects in the various object caches */
DECL|macro|ACPI_MAX_STATE_CACHE_DEPTH
mdefine_line|#define ACPI_MAX_STATE_CACHE_DEPTH      64          /* State objects */
DECL|macro|ACPI_MAX_PARSE_CACHE_DEPTH
mdefine_line|#define ACPI_MAX_PARSE_CACHE_DEPTH      96          /* Parse tree objects */
DECL|macro|ACPI_MAX_EXTPARSE_CACHE_DEPTH
mdefine_line|#define ACPI_MAX_EXTPARSE_CACHE_DEPTH   64          /* Parse tree objects */
DECL|macro|ACPI_MAX_OBJECT_CACHE_DEPTH
mdefine_line|#define ACPI_MAX_OBJECT_CACHE_DEPTH     64          /* Interpreter operand objects */
DECL|macro|ACPI_MAX_WALK_CACHE_DEPTH
mdefine_line|#define ACPI_MAX_WALK_CACHE_DEPTH       4           /* Objects for parse tree walks */
multiline_comment|/*&n; * Should the subystem abort the loading of an ACPI table if the&n; * table checksum is incorrect?&n; */
DECL|macro|ACPI_CHECKSUM_ABORT
mdefine_line|#define ACPI_CHECKSUM_ABORT             FALSE
multiline_comment|/******************************************************************************&n; *&n; * Subsystem Constants&n; *&n; *****************************************************************************/
multiline_comment|/* Version of ACPI supported */
DECL|macro|ACPI_CA_SUPPORT_LEVEL
mdefine_line|#define ACPI_CA_SUPPORT_LEVEL           2
multiline_comment|/* String size constants */
DECL|macro|ACPI_MAX_STRING_LENGTH
mdefine_line|#define ACPI_MAX_STRING_LENGTH          512
DECL|macro|ACPI_PATHNAME_MAX
mdefine_line|#define ACPI_PATHNAME_MAX               256         /* A full namespace pathname */
multiline_comment|/* Maximum count for a semaphore object */
DECL|macro|ACPI_MAX_SEMAPHORE_COUNT
mdefine_line|#define ACPI_MAX_SEMAPHORE_COUNT        256
multiline_comment|/* Max reference count (for debug only) */
DECL|macro|ACPI_MAX_REFERENCE_COUNT
mdefine_line|#define ACPI_MAX_REFERENCE_COUNT        0x400
multiline_comment|/* Size of cached memory mapping for system memory operation region */
DECL|macro|ACPI_SYSMEM_REGION_WINDOW_SIZE
mdefine_line|#define ACPI_SYSMEM_REGION_WINDOW_SIZE  4096
multiline_comment|/******************************************************************************&n; *&n; * ACPI Specification constants (Do not change unless the specification changes)&n; *&n; *****************************************************************************/
multiline_comment|/* Number of distinct GPE register blocks and register width */
DECL|macro|ACPI_MAX_GPE_BLOCKS
mdefine_line|#define ACPI_MAX_GPE_BLOCKS             2
DECL|macro|ACPI_GPE_REGISTER_WIDTH
mdefine_line|#define ACPI_GPE_REGISTER_WIDTH         8
multiline_comment|/*&n; * Method info (in WALK_STATE), containing local variables and argumetns&n; */
DECL|macro|ACPI_METHOD_NUM_LOCALS
mdefine_line|#define ACPI_METHOD_NUM_LOCALS          8
DECL|macro|ACPI_METHOD_MAX_LOCAL
mdefine_line|#define ACPI_METHOD_MAX_LOCAL           7
DECL|macro|ACPI_METHOD_NUM_ARGS
mdefine_line|#define ACPI_METHOD_NUM_ARGS            7
DECL|macro|ACPI_METHOD_MAX_ARG
mdefine_line|#define ACPI_METHOD_MAX_ARG             6
multiline_comment|/* Maximum length of resulting string when converting from a buffer */
DECL|macro|ACPI_MAX_STRING_CONVERSION
mdefine_line|#define ACPI_MAX_STRING_CONVERSION      200
multiline_comment|/* Length of _HID, _UID, and _CID values */
DECL|macro|ACPI_DEVICE_ID_LENGTH
mdefine_line|#define ACPI_DEVICE_ID_LENGTH           0x09
DECL|macro|ACPI_MAX_CID_LENGTH
mdefine_line|#define ACPI_MAX_CID_LENGTH             48
multiline_comment|/*&n; * Operand Stack (in WALK_STATE), Must be large enough to contain METHOD_MAX_ARG&n; */
DECL|macro|ACPI_OBJ_NUM_OPERANDS
mdefine_line|#define ACPI_OBJ_NUM_OPERANDS           8
DECL|macro|ACPI_OBJ_MAX_OPERAND
mdefine_line|#define ACPI_OBJ_MAX_OPERAND            7
multiline_comment|/* Names within the namespace are 4 bytes long */
DECL|macro|ACPI_NAME_SIZE
mdefine_line|#define ACPI_NAME_SIZE                  4
DECL|macro|ACPI_PATH_SEGMENT_LENGTH
mdefine_line|#define ACPI_PATH_SEGMENT_LENGTH        5           /* 4 chars for name + 1 char for separator */
DECL|macro|ACPI_PATH_SEPARATOR
mdefine_line|#define ACPI_PATH_SEPARATOR             &squot;.&squot;
multiline_comment|/* Constants used in searching for the RSDP in low memory */
DECL|macro|ACPI_EBDA_PTR_LOCATION
mdefine_line|#define ACPI_EBDA_PTR_LOCATION          0x0000040E     /* Physical Address */
DECL|macro|ACPI_EBDA_PTR_LENGTH
mdefine_line|#define ACPI_EBDA_PTR_LENGTH            2
DECL|macro|ACPI_EBDA_WINDOW_SIZE
mdefine_line|#define ACPI_EBDA_WINDOW_SIZE           1024
DECL|macro|ACPI_HI_RSDP_WINDOW_BASE
mdefine_line|#define ACPI_HI_RSDP_WINDOW_BASE        0x000E0000     /* Physical Address */
DECL|macro|ACPI_HI_RSDP_WINDOW_SIZE
mdefine_line|#define ACPI_HI_RSDP_WINDOW_SIZE        0x00020000
DECL|macro|ACPI_RSDP_SCAN_STEP
mdefine_line|#define ACPI_RSDP_SCAN_STEP             16
multiline_comment|/* Operation regions */
DECL|macro|ACPI_NUM_PREDEFINED_REGIONS
mdefine_line|#define ACPI_NUM_PREDEFINED_REGIONS     8
DECL|macro|ACPI_USER_REGION_BEGIN
mdefine_line|#define ACPI_USER_REGION_BEGIN          0x80
multiline_comment|/* Maximum space_ids for Operation Regions */
DECL|macro|ACPI_MAX_ADDRESS_SPACE
mdefine_line|#define ACPI_MAX_ADDRESS_SPACE          255
multiline_comment|/* Array sizes.  Used for range checking also */
DECL|macro|ACPI_NUM_ACCESS_TYPES
mdefine_line|#define ACPI_NUM_ACCESS_TYPES           6
DECL|macro|ACPI_NUM_UPDATE_RULES
mdefine_line|#define ACPI_NUM_UPDATE_RULES           3
DECL|macro|ACPI_NUM_LOCK_RULES
mdefine_line|#define ACPI_NUM_LOCK_RULES             2
DECL|macro|ACPI_NUM_MATCH_OPS
mdefine_line|#define ACPI_NUM_MATCH_OPS              6
DECL|macro|ACPI_NUM_OPCODES
mdefine_line|#define ACPI_NUM_OPCODES                256
DECL|macro|ACPI_NUM_FIELD_NAMES
mdefine_line|#define ACPI_NUM_FIELD_NAMES            2
multiline_comment|/* RSDP checksums */
DECL|macro|ACPI_RSDP_CHECKSUM_LENGTH
mdefine_line|#define ACPI_RSDP_CHECKSUM_LENGTH       20
DECL|macro|ACPI_RSDP_XCHECKSUM_LENGTH
mdefine_line|#define ACPI_RSDP_XCHECKSUM_LENGTH      36
multiline_comment|/* SMBus bidirectional buffer size */
DECL|macro|ACPI_SMBUS_BUFFER_SIZE
mdefine_line|#define ACPI_SMBUS_BUFFER_SIZE          34
multiline_comment|/* Number of strings associated with the _OSI reserved method */
DECL|macro|ACPI_NUM_OSI_STRINGS
mdefine_line|#define ACPI_NUM_OSI_STRINGS            9
multiline_comment|/******************************************************************************&n; *&n; * ACPI AML Debugger&n; *&n; *****************************************************************************/
DECL|macro|ACPI_DEBUGGER_MAX_ARGS
mdefine_line|#define ACPI_DEBUGGER_MAX_ARGS          8  /* Must be max method args + 1 */
DECL|macro|ACPI_DEBUGGER_COMMAND_PROMPT
mdefine_line|#define ACPI_DEBUGGER_COMMAND_PROMPT    &squot;-&squot;
DECL|macro|ACPI_DEBUGGER_EXECUTE_PROMPT
mdefine_line|#define ACPI_DEBUGGER_EXECUTE_PROMPT    &squot;%&squot;
macro_line|#endif /* _ACCONFIG_H */
eof
