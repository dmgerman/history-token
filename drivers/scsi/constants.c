multiline_comment|/* &n; * ASCII values for a number of symbolic constants, printing functions,&n; * etc.&n; * Additions for SCSI 2 and Linux 2.2.x by D. Gilbert (990422)&n; * Additions for SCSI 3+ (SPC-3 T10/1416-D Rev 07 3 May 2002)&n; *   by D. Gilbert and aeb (20020609)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
DECL|macro|CONST_COMMAND
mdefine_line|#define CONST_COMMAND   0x01
DECL|macro|CONST_STATUS
mdefine_line|#define CONST_STATUS    0x02
DECL|macro|CONST_SENSE
mdefine_line|#define CONST_SENSE     0x04
DECL|macro|CONST_XSENSE
mdefine_line|#define CONST_XSENSE    0x08
DECL|macro|CONST_CMND
mdefine_line|#define CONST_CMND      0x10
DECL|macro|CONST_MSG
mdefine_line|#define CONST_MSG       0x20
DECL|macro|CONST_HOST
mdefine_line|#define CONST_HOST&t;0x40
DECL|macro|CONST_DRIVER
mdefine_line|#define CONST_DRIVER&t;0x80
DECL|variable|unknown
r_static
r_const
r_char
id|unknown
(braket
)braket
op_assign
l_string|&quot;UNKNOWN&quot;
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI_CONSTANTS
macro_line|#ifdef CONSTANTS
DECL|macro|CONSTANTS
macro_line|#undef CONSTANTS
macro_line|#endif
DECL|macro|CONSTANTS
mdefine_line|#define CONSTANTS (CONST_COMMAND | CONST_STATUS | CONST_SENSE | CONST_XSENSE &bslash;&n;&t;&t;   | CONST_CMND | CONST_MSG | CONST_HOST | CONST_DRIVER)
macro_line|#endif
macro_line|#if (CONSTANTS &amp; CONST_COMMAND)
DECL|variable|group_0_commands
r_static
r_const
r_char
op_star
id|group_0_commands
(braket
)braket
op_assign
(brace
multiline_comment|/* 00-03 */
l_string|&quot;Test Unit Ready&quot;
comma
l_string|&quot;Rezero Unit&quot;
comma
id|unknown
comma
l_string|&quot;Request Sense&quot;
comma
multiline_comment|/* 04-07 */
l_string|&quot;Format Unit&quot;
comma
l_string|&quot;Read Block Limits&quot;
comma
id|unknown
comma
l_string|&quot;Reasssign Blocks&quot;
comma
multiline_comment|/* 08-0d */
l_string|&quot;Read (6)&quot;
comma
id|unknown
comma
l_string|&quot;Write (6)&quot;
comma
l_string|&quot;Seek (6)&quot;
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 0e-12 */
id|unknown
comma
l_string|&quot;Read Reverse&quot;
comma
l_string|&quot;Write Filemarks&quot;
comma
l_string|&quot;Space&quot;
comma
l_string|&quot;Inquiry&quot;
comma
multiline_comment|/* 13-16 */
l_string|&quot;Verify&quot;
comma
l_string|&quot;Recover Buffered Data&quot;
comma
l_string|&quot;Mode Select&quot;
comma
l_string|&quot;Reserve&quot;
comma
multiline_comment|/* 17-1b */
l_string|&quot;Release&quot;
comma
l_string|&quot;Copy&quot;
comma
l_string|&quot;Erase&quot;
comma
l_string|&quot;Mode Sense&quot;
comma
l_string|&quot;Start/Stop Unit&quot;
comma
multiline_comment|/* 1c-1d */
l_string|&quot;Receive Diagnostic&quot;
comma
l_string|&quot;Send Diagnostic&quot;
comma
multiline_comment|/* 1e-1f */
l_string|&quot;Prevent/Allow Medium Removal&quot;
comma
id|unknown
comma
)brace
suffix:semicolon
DECL|variable|group_1_commands
r_static
r_const
r_char
op_star
id|group_1_commands
(braket
)braket
op_assign
(brace
multiline_comment|/* 20-22 */
id|unknown
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 23-28 */
id|unknown
comma
l_string|&quot;Define window parameters&quot;
comma
l_string|&quot;Read Capacity&quot;
comma
id|unknown
comma
id|unknown
comma
l_string|&quot;Read (10)&quot;
comma
multiline_comment|/* 29-2d */
l_string|&quot;Read Generation&quot;
comma
l_string|&quot;Write (10)&quot;
comma
l_string|&quot;Seek (10)&quot;
comma
l_string|&quot;Erase&quot;
comma
l_string|&quot;Read updated block&quot;
comma
multiline_comment|/* 2e-31 */
l_string|&quot;Write Verify&quot;
comma
l_string|&quot;Verify&quot;
comma
l_string|&quot;Search High&quot;
comma
l_string|&quot;Search Equal&quot;
comma
multiline_comment|/* 32-34 */
l_string|&quot;Search Low&quot;
comma
l_string|&quot;Set Limits&quot;
comma
l_string|&quot;Prefetch or Read Position&quot;
comma
multiline_comment|/* 35-37 */
l_string|&quot;Synchronize Cache&quot;
comma
l_string|&quot;Lock/Unlock Cache&quot;
comma
l_string|&quot;Read Defect Data&quot;
comma
multiline_comment|/* 38-3c */
l_string|&quot;Medium Scan&quot;
comma
l_string|&quot;Compare&quot;
comma
l_string|&quot;Copy Verify&quot;
comma
l_string|&quot;Write Buffer&quot;
comma
l_string|&quot;Read Buffer&quot;
comma
multiline_comment|/* 3d-3f */
l_string|&quot;Update Block&quot;
comma
l_string|&quot;Read Long&quot;
comma
l_string|&quot;Write Long&quot;
comma
)brace
suffix:semicolon
DECL|variable|group_2_commands
r_static
r_const
r_char
op_star
id|group_2_commands
(braket
)braket
op_assign
(brace
multiline_comment|/* 40-41 */
l_string|&quot;Change Definition&quot;
comma
l_string|&quot;Write Same&quot;
comma
multiline_comment|/* 42-48 */
l_string|&quot;Read sub-channel&quot;
comma
l_string|&quot;Read TOC&quot;
comma
l_string|&quot;Read header&quot;
comma
l_string|&quot;Play audio (10)&quot;
comma
id|unknown
comma
l_string|&quot;Play audio msf&quot;
comma
l_string|&quot;Play audio track/index&quot;
comma
multiline_comment|/* 49-4f */
l_string|&quot;Play track relative (10)&quot;
comma
id|unknown
comma
l_string|&quot;Pause/resume&quot;
comma
l_string|&quot;Log Select&quot;
comma
l_string|&quot;Log Sense&quot;
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 50-55 */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
l_string|&quot;Mode Select (10)&quot;
comma
multiline_comment|/* 56-5b */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
l_string|&quot;Mode Sense (10)&quot;
comma
id|unknown
comma
multiline_comment|/* 5c-5f */
id|unknown
comma
id|unknown
comma
id|unknown
comma
)brace
suffix:semicolon
multiline_comment|/* The following are 16 byte commands in group 4 */
DECL|variable|group_4_commands
r_static
r_const
r_char
op_star
id|group_4_commands
(braket
)braket
op_assign
(brace
multiline_comment|/* 80-84 */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 85-89 */
l_string|&quot;Memory Export In (16)&quot;
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
l_string|&quot;Memory Export Out (16)&quot;
comma
multiline_comment|/* 8a-8f */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 90-94 */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 95-99 */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
multiline_comment|/* 9a-9f */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
)brace
suffix:semicolon
multiline_comment|/* The following are 12 byte commands in group 5 */
DECL|variable|group_5_commands
r_static
r_const
r_char
op_star
id|group_5_commands
(braket
)braket
op_assign
(brace
multiline_comment|/* a0-a5 */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
l_string|&quot;Move medium/play audio(12)&quot;
comma
multiline_comment|/* a6-a9 */
l_string|&quot;Exchange medium&quot;
comma
id|unknown
comma
l_string|&quot;Read(12)&quot;
comma
l_string|&quot;Play track relative(12)&quot;
comma
multiline_comment|/* aa-ae */
l_string|&quot;Write(12)&quot;
comma
id|unknown
comma
l_string|&quot;Erase(12)&quot;
comma
id|unknown
comma
l_string|&quot;Write and verify(12)&quot;
comma
multiline_comment|/* af-b1 */
l_string|&quot;Verify(12)&quot;
comma
l_string|&quot;Search data high(12)&quot;
comma
l_string|&quot;Search data equal(12)&quot;
comma
multiline_comment|/* b2-b4 */
l_string|&quot;Search data low(12)&quot;
comma
l_string|&quot;Set limits(12)&quot;
comma
id|unknown
comma
multiline_comment|/* b5-b6 */
l_string|&quot;Request volume element address&quot;
comma
l_string|&quot;Send volume tag&quot;
comma
multiline_comment|/* b7-b9 */
l_string|&quot;Read defect data(12)&quot;
comma
l_string|&quot;Read element status&quot;
comma
id|unknown
comma
multiline_comment|/* ba-bf */
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
id|unknown
comma
)brace
suffix:semicolon
DECL|macro|group
mdefine_line|#define group(opcode) (((opcode) &gt;&gt; 5) &amp; 7)
DECL|macro|RESERVED_GROUP
mdefine_line|#define RESERVED_GROUP  0
DECL|macro|VENDOR_GROUP
mdefine_line|#define VENDOR_GROUP    1
DECL|variable|commands
r_static
r_const
r_char
op_star
op_star
id|commands
(braket
)braket
op_assign
(brace
id|group_0_commands
comma
id|group_1_commands
comma
id|group_2_commands
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|RESERVED_GROUP
comma
id|group_4_commands
comma
id|group_5_commands
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|VENDOR_GROUP
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|VENDOR_GROUP
)brace
suffix:semicolon
DECL|variable|reserved
r_static
r_const
r_char
id|reserved
(braket
)braket
op_assign
l_string|&quot;RESERVED&quot;
suffix:semicolon
DECL|variable|vendor
r_static
r_const
r_char
id|vendor
(braket
)braket
op_assign
l_string|&quot;VENDOR SPECIFIC&quot;
suffix:semicolon
DECL|function|print_opcode
r_static
r_void
id|print_opcode
c_func
(paren
r_int
id|opcode
)paren
(brace
r_const
r_char
op_star
op_star
id|table
op_assign
id|commands
(braket
id|group
c_func
(paren
id|opcode
)paren
)braket
suffix:semicolon
r_switch
c_cond
(paren
(paren
r_int
r_int
)paren
id|table
)paren
(brace
r_case
id|RESERVED_GROUP
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s(0x%02x) &quot;
comma
id|reserved
comma
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VENDOR_GROUP
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s(0x%02x) &quot;
comma
id|vendor
comma
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|table
(braket
id|opcode
op_amp
l_int|0x1f
)braket
op_ne
id|unknown
)paren
id|printk
c_func
(paren
l_string|&quot;%s &quot;
comma
id|table
(braket
id|opcode
op_amp
l_int|0x1f
)braket
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;%s(0x%02x) &quot;
comma
id|unknown
comma
id|opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#else /* CONST &amp; CONST_COMMAND */
DECL|function|print_opcode
r_static
r_void
id|print_opcode
c_func
(paren
r_int
id|opcode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;0x%02x &quot;
comma
id|opcode
)paren
suffix:semicolon
)brace
macro_line|#endif  
DECL|function|print_command
r_void
id|print_command
(paren
r_int
r_char
op_star
id|command
)paren
(brace
r_int
id|i
comma
id|s
suffix:semicolon
id|print_opcode
c_func
(paren
id|command
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
comma
id|s
op_assign
id|COMMAND_SIZE
c_func
(paren
id|command
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
OL
id|s
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|command
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&n; *&t;print_status - print scsi status description&n; *&t;@scsi_status: scsi status value&n; *&n; *&t;If the status is recognized, the description is printed.&n; *&t;Otherwise &quot;Unknown status&quot; is output. No trailing space.&n; *&t;If CONFIG_SCSI_CONSTANTS is not set, then print status in hex&n; *&t;(e.g. &quot;0x2&quot; for Check Condition).&n; **/
r_void
DECL|function|print_status
id|print_status
c_func
(paren
r_int
r_char
id|scsi_status
)paren
(brace
macro_line|#if (CONSTANTS &amp; CONST_STATUS)
r_const
r_char
op_star
id|ccp
suffix:semicolon
r_switch
c_cond
(paren
id|scsi_status
)paren
(brace
r_case
l_int|0
suffix:colon
id|ccp
op_assign
l_string|&quot;Good&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x2
suffix:colon
id|ccp
op_assign
l_string|&quot;Check Condition&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4
suffix:colon
id|ccp
op_assign
l_string|&quot;Condition Met&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8
suffix:colon
id|ccp
op_assign
l_string|&quot;Busy&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x10
suffix:colon
id|ccp
op_assign
l_string|&quot;Intermediate&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x14
suffix:colon
id|ccp
op_assign
l_string|&quot;Intermediate-Condition Met&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x18
suffix:colon
id|ccp
op_assign
l_string|&quot;Reservation Conflict&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x22
suffix:colon
id|ccp
op_assign
l_string|&quot;Command Terminated&quot;
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* obsolete */
r_case
l_int|0x28
suffix:colon
id|ccp
op_assign
l_string|&quot;Task set Full&quot;
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* was: Queue Full */
r_case
l_int|0x30
suffix:colon
id|ccp
op_assign
l_string|&quot;ACA Active&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x40
suffix:colon
id|ccp
op_assign
l_string|&quot;Task Aborted&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ccp
op_assign
l_string|&quot;Unknown status&quot;
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|ccp
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;0x%0x&quot;
comma
id|scsi_status
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if (CONSTANTS &amp; CONST_XSENSE)
DECL|struct|error_info
r_struct
id|error_info
(brace
DECL|member|code12
r_int
r_int
id|code12
suffix:semicolon
multiline_comment|/* 0x0302 looks better than 0x03,0x02 */
DECL|member|text
r_const
r_char
op_star
id|text
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|additional
r_static
r_struct
id|error_info
id|additional
(braket
)braket
op_assign
(brace
(brace
l_int|0x0000
comma
l_string|&quot;No additional sense information&quot;
)brace
comma
(brace
l_int|0x0001
comma
l_string|&quot;Filemark detected&quot;
)brace
comma
(brace
l_int|0x0002
comma
l_string|&quot;End-of-partition/medium detected&quot;
)brace
comma
(brace
l_int|0x0003
comma
l_string|&quot;Setmark detected&quot;
)brace
comma
(brace
l_int|0x0004
comma
l_string|&quot;Beginning-of-partition/medium detected&quot;
)brace
comma
(brace
l_int|0x0005
comma
l_string|&quot;End-of-data detected&quot;
)brace
comma
(brace
l_int|0x0006
comma
l_string|&quot;I/O process terminated&quot;
)brace
comma
(brace
l_int|0x0011
comma
l_string|&quot;Audio play operation in progress&quot;
)brace
comma
(brace
l_int|0x0012
comma
l_string|&quot;Audio play operation paused&quot;
)brace
comma
(brace
l_int|0x0013
comma
l_string|&quot;Audio play operation successfully completed&quot;
)brace
comma
(brace
l_int|0x0014
comma
l_string|&quot;Audio play operation stopped due to error&quot;
)brace
comma
(brace
l_int|0x0015
comma
l_string|&quot;No current audio status to return&quot;
)brace
comma
(brace
l_int|0x0016
comma
l_string|&quot;Operation in progress&quot;
)brace
comma
(brace
l_int|0x0017
comma
l_string|&quot;Cleaning requested&quot;
)brace
comma
(brace
l_int|0x0018
comma
l_string|&quot;Erase operation in progress&quot;
)brace
comma
(brace
l_int|0x0019
comma
l_string|&quot;Locate operation in progress&quot;
)brace
comma
(brace
l_int|0x001A
comma
l_string|&quot;Rewind operation in progress&quot;
)brace
comma
(brace
l_int|0x001B
comma
l_string|&quot;Set capacity operation in progress&quot;
)brace
comma
(brace
l_int|0x001C
comma
l_string|&quot;Verify operation in progress&quot;
)brace
comma
(brace
l_int|0x0100
comma
l_string|&quot;No index/sector signal&quot;
)brace
comma
(brace
l_int|0x0200
comma
l_string|&quot;No seek complete&quot;
)brace
comma
(brace
l_int|0x0300
comma
l_string|&quot;Peripheral device write fault&quot;
)brace
comma
(brace
l_int|0x0301
comma
l_string|&quot;No write current&quot;
)brace
comma
(brace
l_int|0x0302
comma
l_string|&quot;Excessive write errors&quot;
)brace
comma
(brace
l_int|0x0400
comma
l_string|&quot;Logical unit not ready, cause not reportable&quot;
)brace
comma
(brace
l_int|0x0401
comma
l_string|&quot;Logical unit is in process of becoming ready&quot;
)brace
comma
(brace
l_int|0x0402
comma
l_string|&quot;Logical unit not ready, initializing cmd. required&quot;
)brace
comma
(brace
l_int|0x0403
comma
l_string|&quot;Logical unit not ready, manual intervention required&quot;
)brace
comma
(brace
l_int|0x0404
comma
l_string|&quot;Logical unit not ready, format in progress&quot;
)brace
comma
(brace
l_int|0x0405
comma
l_string|&quot;Logical unit not ready, rebuild in progress&quot;
)brace
comma
(brace
l_int|0x0406
comma
l_string|&quot;Logical unit not ready, recalculation in progress&quot;
)brace
comma
(brace
l_int|0x0407
comma
l_string|&quot;Logical unit not ready, operation in progress&quot;
)brace
comma
(brace
l_int|0x0408
comma
l_string|&quot;Logical unit not ready, long write in progress&quot;
)brace
comma
(brace
l_int|0x0409
comma
l_string|&quot;Logical unit not ready, self-test in progress&quot;
)brace
comma
(brace
l_int|0x040A
comma
l_string|&quot;Logical unit not accessible, asymmetric access state &quot;
l_string|&quot;transition&quot;
)brace
comma
(brace
l_int|0x040B
comma
l_string|&quot;Logical unit not accessible, target port in standby state&quot;
)brace
comma
(brace
l_int|0x040C
comma
l_string|&quot;Logical unit not accessible, target port in unavailable &quot;
l_string|&quot;state&quot;
)brace
comma
(brace
l_int|0x0410
comma
l_string|&quot;Logical unit not ready, auxiliary memory not accessible&quot;
)brace
comma
(brace
l_int|0x0500
comma
l_string|&quot;Logical unit does not respond to selection&quot;
)brace
comma
(brace
l_int|0x0600
comma
l_string|&quot;No reference position found&quot;
)brace
comma
(brace
l_int|0x0700
comma
l_string|&quot;Multiple peripheral devices selected&quot;
)brace
comma
(brace
l_int|0x0800
comma
l_string|&quot;Logical unit communication failure&quot;
)brace
comma
(brace
l_int|0x0801
comma
l_string|&quot;Logical unit communication time-out&quot;
)brace
comma
(brace
l_int|0x0802
comma
l_string|&quot;Logical unit communication parity error&quot;
)brace
comma
(brace
l_int|0x0803
comma
l_string|&quot;Logical unit communication CRC error (Ultra-DMA/32)&quot;
)brace
comma
(brace
l_int|0x0804
comma
l_string|&quot;Unreachable copy target&quot;
)brace
comma
(brace
l_int|0x0900
comma
l_string|&quot;Track following error&quot;
)brace
comma
(brace
l_int|0x0901
comma
l_string|&quot;Tracking servo failure&quot;
)brace
comma
(brace
l_int|0x0902
comma
l_string|&quot;Focus servo failure&quot;
)brace
comma
(brace
l_int|0x0903
comma
l_string|&quot;Spindle servo failure&quot;
)brace
comma
(brace
l_int|0x0904
comma
l_string|&quot;Head select fault&quot;
)brace
comma
(brace
l_int|0x0A00
comma
l_string|&quot;Error log overflow&quot;
)brace
comma
(brace
l_int|0x0B00
comma
l_string|&quot;Warning&quot;
)brace
comma
(brace
l_int|0x0B01
comma
l_string|&quot;Warning - specified temperature exceeded&quot;
)brace
comma
(brace
l_int|0x0B02
comma
l_string|&quot;Warning - enclosure degraded&quot;
)brace
comma
(brace
l_int|0x0C00
comma
l_string|&quot;Write error&quot;
)brace
comma
(brace
l_int|0x0C01
comma
l_string|&quot;Write error - recovered with auto reallocation&quot;
)brace
comma
(brace
l_int|0x0C02
comma
l_string|&quot;Write error - auto reallocation failed&quot;
)brace
comma
(brace
l_int|0x0C03
comma
l_string|&quot;Write error - recommend reassignment&quot;
)brace
comma
(brace
l_int|0x0C04
comma
l_string|&quot;Compression check miscompare error&quot;
)brace
comma
(brace
l_int|0x0C05
comma
l_string|&quot;Data expansion occurred during compression&quot;
)brace
comma
(brace
l_int|0x0C06
comma
l_string|&quot;Block not compressible&quot;
)brace
comma
(brace
l_int|0x0C07
comma
l_string|&quot;Write error - recovery needed&quot;
)brace
comma
(brace
l_int|0x0C08
comma
l_string|&quot;Write error - recovery failed&quot;
)brace
comma
(brace
l_int|0x0C09
comma
l_string|&quot;Write error - loss of streaming&quot;
)brace
comma
(brace
l_int|0x0C0A
comma
l_string|&quot;Write error - padding blocks added&quot;
)brace
comma
(brace
l_int|0x0C0B
comma
l_string|&quot;Auxiliary memory write error&quot;
)brace
comma
(brace
l_int|0x0C0C
comma
l_string|&quot;Write error - unexpected unsolicited data&quot;
)brace
comma
(brace
l_int|0x0C0D
comma
l_string|&quot;Write error - not enough unsolicited data&quot;
)brace
comma
(brace
l_int|0x0D00
comma
l_string|&quot;Error detected by third party temporary initiator&quot;
)brace
comma
(brace
l_int|0x0D01
comma
l_string|&quot;Third party device failure&quot;
)brace
comma
(brace
l_int|0x0D02
comma
l_string|&quot;Copy target device not reachable&quot;
)brace
comma
(brace
l_int|0x0D03
comma
l_string|&quot;Incorrect copy target device type&quot;
)brace
comma
(brace
l_int|0x0D04
comma
l_string|&quot;Copy target device data underrun&quot;
)brace
comma
(brace
l_int|0x0D05
comma
l_string|&quot;Copy target device data overrun&quot;
)brace
comma
(brace
l_int|0x1000
comma
l_string|&quot;Id CRC or ECC error&quot;
)brace
comma
(brace
l_int|0x1100
comma
l_string|&quot;Unrecovered read error&quot;
)brace
comma
(brace
l_int|0x1101
comma
l_string|&quot;Read retries exhausted&quot;
)brace
comma
(brace
l_int|0x1102
comma
l_string|&quot;Error too long to correct&quot;
)brace
comma
(brace
l_int|0x1103
comma
l_string|&quot;Multiple read errors&quot;
)brace
comma
(brace
l_int|0x1104
comma
l_string|&quot;Unrecovered read error - auto reallocate failed&quot;
)brace
comma
(brace
l_int|0x1105
comma
l_string|&quot;L-EC uncorrectable error&quot;
)brace
comma
(brace
l_int|0x1106
comma
l_string|&quot;CIRC unrecovered error&quot;
)brace
comma
(brace
l_int|0x1107
comma
l_string|&quot;Data re-synchronization error&quot;
)brace
comma
(brace
l_int|0x1108
comma
l_string|&quot;Incomplete block read&quot;
)brace
comma
(brace
l_int|0x1109
comma
l_string|&quot;No gap found&quot;
)brace
comma
(brace
l_int|0x110A
comma
l_string|&quot;Miscorrected error&quot;
)brace
comma
(brace
l_int|0x110B
comma
l_string|&quot;Unrecovered read error - recommend reassignment&quot;
)brace
comma
(brace
l_int|0x110C
comma
l_string|&quot;Unrecovered read error - recommend rewrite the data&quot;
)brace
comma
(brace
l_int|0x110D
comma
l_string|&quot;De-compression CRC error&quot;
)brace
comma
(brace
l_int|0x110E
comma
l_string|&quot;Cannot decompress using declared algorithm&quot;
)brace
comma
(brace
l_int|0x110F
comma
l_string|&quot;Error reading UPC/EAN number&quot;
)brace
comma
(brace
l_int|0x1110
comma
l_string|&quot;Error reading ISRC number&quot;
)brace
comma
(brace
l_int|0x1111
comma
l_string|&quot;Read error - loss of streaming&quot;
)brace
comma
(brace
l_int|0x1112
comma
l_string|&quot;Auxiliary memory read error&quot;
)brace
comma
(brace
l_int|0x1113
comma
l_string|&quot;Read error - failed retransmission request&quot;
)brace
comma
(brace
l_int|0x1200
comma
l_string|&quot;Address mark not found for id field&quot;
)brace
comma
(brace
l_int|0x1300
comma
l_string|&quot;Address mark not found for data field&quot;
)brace
comma
(brace
l_int|0x1400
comma
l_string|&quot;Recorded entity not found&quot;
)brace
comma
(brace
l_int|0x1401
comma
l_string|&quot;Record not found&quot;
)brace
comma
(brace
l_int|0x1402
comma
l_string|&quot;Filemark or setmark not found&quot;
)brace
comma
(brace
l_int|0x1403
comma
l_string|&quot;End-of-data not found&quot;
)brace
comma
(brace
l_int|0x1404
comma
l_string|&quot;Block sequence error&quot;
)brace
comma
(brace
l_int|0x1405
comma
l_string|&quot;Record not found - recommend reassignment&quot;
)brace
comma
(brace
l_int|0x1406
comma
l_string|&quot;Record not found - data auto-reallocated&quot;
)brace
comma
(brace
l_int|0x1407
comma
l_string|&quot;Locate operation failure&quot;
)brace
comma
(brace
l_int|0x1500
comma
l_string|&quot;Random positioning error&quot;
)brace
comma
(brace
l_int|0x1501
comma
l_string|&quot;Mechanical positioning error&quot;
)brace
comma
(brace
l_int|0x1502
comma
l_string|&quot;Positioning error detected by read of medium&quot;
)brace
comma
(brace
l_int|0x1600
comma
l_string|&quot;Data synchronization mark error&quot;
)brace
comma
(brace
l_int|0x1601
comma
l_string|&quot;Data sync error - data rewritten&quot;
)brace
comma
(brace
l_int|0x1602
comma
l_string|&quot;Data sync error - recommend rewrite&quot;
)brace
comma
(brace
l_int|0x1603
comma
l_string|&quot;Data sync error - data auto-reallocated&quot;
)brace
comma
(brace
l_int|0x1604
comma
l_string|&quot;Data sync error - recommend reassignment&quot;
)brace
comma
(brace
l_int|0x1700
comma
l_string|&quot;Recovered data with no error correction applied&quot;
)brace
comma
(brace
l_int|0x1701
comma
l_string|&quot;Recovered data with retries&quot;
)brace
comma
(brace
l_int|0x1702
comma
l_string|&quot;Recovered data with positive head offset&quot;
)brace
comma
(brace
l_int|0x1703
comma
l_string|&quot;Recovered data with negative head offset&quot;
)brace
comma
(brace
l_int|0x1704
comma
l_string|&quot;Recovered data with retries and/or circ applied&quot;
)brace
comma
(brace
l_int|0x1705
comma
l_string|&quot;Recovered data using previous sector id&quot;
)brace
comma
(brace
l_int|0x1706
comma
l_string|&quot;Recovered data without ECC - data auto-reallocated&quot;
)brace
comma
(brace
l_int|0x1707
comma
l_string|&quot;Recovered data without ECC - recommend reassignment&quot;
)brace
comma
(brace
l_int|0x1708
comma
l_string|&quot;Recovered data without ECC - recommend rewrite&quot;
)brace
comma
(brace
l_int|0x1709
comma
l_string|&quot;Recovered data without ECC - data rewritten&quot;
)brace
comma
(brace
l_int|0x1800
comma
l_string|&quot;Recovered data with error correction applied&quot;
)brace
comma
(brace
l_int|0x1801
comma
l_string|&quot;Recovered data with error corr. &amp; retries applied&quot;
)brace
comma
(brace
l_int|0x1802
comma
l_string|&quot;Recovered data - data auto-reallocated&quot;
)brace
comma
(brace
l_int|0x1803
comma
l_string|&quot;Recovered data with CIRC&quot;
)brace
comma
(brace
l_int|0x1804
comma
l_string|&quot;Recovered data with L-EC&quot;
)brace
comma
(brace
l_int|0x1805
comma
l_string|&quot;Recovered data - recommend reassignment&quot;
)brace
comma
(brace
l_int|0x1806
comma
l_string|&quot;Recovered data - recommend rewrite&quot;
)brace
comma
(brace
l_int|0x1807
comma
l_string|&quot;Recovered data with ECC - data rewritten&quot;
)brace
comma
(brace
l_int|0x1808
comma
l_string|&quot;Recovered data with linking&quot;
)brace
comma
(brace
l_int|0x1900
comma
l_string|&quot;Defect list error&quot;
)brace
comma
(brace
l_int|0x1901
comma
l_string|&quot;Defect list not available&quot;
)brace
comma
(brace
l_int|0x1902
comma
l_string|&quot;Defect list error in primary list&quot;
)brace
comma
(brace
l_int|0x1903
comma
l_string|&quot;Defect list error in grown list&quot;
)brace
comma
(brace
l_int|0x1A00
comma
l_string|&quot;Parameter list length error&quot;
)brace
comma
(brace
l_int|0x1B00
comma
l_string|&quot;Synchronous data transfer error&quot;
)brace
comma
(brace
l_int|0x1C00
comma
l_string|&quot;Defect list not found&quot;
)brace
comma
(brace
l_int|0x1C01
comma
l_string|&quot;Primary defect list not found&quot;
)brace
comma
(brace
l_int|0x1C02
comma
l_string|&quot;Grown defect list not found&quot;
)brace
comma
(brace
l_int|0x1D00
comma
l_string|&quot;Miscompare during verify operation&quot;
)brace
comma
(brace
l_int|0x1E00
comma
l_string|&quot;Recovered id with ECC correction&quot;
)brace
comma
(brace
l_int|0x1F00
comma
l_string|&quot;Partial defect list transfer&quot;
)brace
comma
(brace
l_int|0x2000
comma
l_string|&quot;Invalid command operation code&quot;
)brace
comma
(brace
l_int|0x2001
comma
l_string|&quot;Access denied - initiator pending-enrolled&quot;
)brace
comma
(brace
l_int|0x2002
comma
l_string|&quot;Access denied - no access rights&quot;
)brace
comma
(brace
l_int|0x2003
comma
l_string|&quot;Access denied - invalid mgmt id key&quot;
)brace
comma
(brace
l_int|0x2004
comma
l_string|&quot;Illegal command while in write capable state&quot;
)brace
comma
(brace
l_int|0x2005
comma
l_string|&quot;Obsolete&quot;
)brace
comma
(brace
l_int|0x2006
comma
l_string|&quot;Illegal command while in explicit address mode&quot;
)brace
comma
(brace
l_int|0x2007
comma
l_string|&quot;Illegal command while in implicit address mode&quot;
)brace
comma
(brace
l_int|0x2008
comma
l_string|&quot;Access denied - enrollment conflict&quot;
)brace
comma
(brace
l_int|0x2009
comma
l_string|&quot;Access denied - invalid LU identifier&quot;
)brace
comma
(brace
l_int|0x200A
comma
l_string|&quot;Access denied - invalid proxy token&quot;
)brace
comma
(brace
l_int|0x200B
comma
l_string|&quot;Access denied - ACL LUN conflict&quot;
)brace
comma
(brace
l_int|0x2100
comma
l_string|&quot;Logical block address out of range&quot;
)brace
comma
(brace
l_int|0x2101
comma
l_string|&quot;Invalid element address&quot;
)brace
comma
(brace
l_int|0x2102
comma
l_string|&quot;Invalid address for write&quot;
)brace
comma
(brace
l_int|0x2200
comma
l_string|&quot;Illegal function (use 20 00, 24 00, or 26 00)&quot;
)brace
comma
(brace
l_int|0x2400
comma
l_string|&quot;Invalid field in cdb&quot;
)brace
comma
(brace
l_int|0x2401
comma
l_string|&quot;CDB decryption error&quot;
)brace
comma
(brace
l_int|0x2402
comma
l_string|&quot;Obsolete&quot;
)brace
comma
(brace
l_int|0x2403
comma
l_string|&quot;Obsolete&quot;
)brace
comma
(brace
l_int|0x2500
comma
l_string|&quot;Logical unit not supported&quot;
)brace
comma
(brace
l_int|0x2600
comma
l_string|&quot;Invalid field in parameter list&quot;
)brace
comma
(brace
l_int|0x2601
comma
l_string|&quot;Parameter not supported&quot;
)brace
comma
(brace
l_int|0x2602
comma
l_string|&quot;Parameter value invalid&quot;
)brace
comma
(brace
l_int|0x2603
comma
l_string|&quot;Threshold parameters not supported&quot;
)brace
comma
(brace
l_int|0x2604
comma
l_string|&quot;Invalid release of persistent reservation&quot;
)brace
comma
(brace
l_int|0x2605
comma
l_string|&quot;Data decryption error&quot;
)brace
comma
(brace
l_int|0x2606
comma
l_string|&quot;Too many target descriptors&quot;
)brace
comma
(brace
l_int|0x2607
comma
l_string|&quot;Unsupported target descriptor type code&quot;
)brace
comma
(brace
l_int|0x2608
comma
l_string|&quot;Too many segment descriptors&quot;
)brace
comma
(brace
l_int|0x2609
comma
l_string|&quot;Unsupported segment descriptor type code&quot;
)brace
comma
(brace
l_int|0x260A
comma
l_string|&quot;Unexpected inexact segment&quot;
)brace
comma
(brace
l_int|0x260B
comma
l_string|&quot;Inline data length exceeded&quot;
)brace
comma
(brace
l_int|0x260C
comma
l_string|&quot;Invalid operation for copy source or destination&quot;
)brace
comma
(brace
l_int|0x260D
comma
l_string|&quot;Copy segment granularity violation&quot;
)brace
comma
(brace
l_int|0x2700
comma
l_string|&quot;Write protected&quot;
)brace
comma
(brace
l_int|0x2701
comma
l_string|&quot;Hardware write protected&quot;
)brace
comma
(brace
l_int|0x2702
comma
l_string|&quot;Logical unit software write protected&quot;
)brace
comma
(brace
l_int|0x2703
comma
l_string|&quot;Associated write protect&quot;
)brace
comma
(brace
l_int|0x2704
comma
l_string|&quot;Persistent write protect&quot;
)brace
comma
(brace
l_int|0x2705
comma
l_string|&quot;Permanent write protect&quot;
)brace
comma
(brace
l_int|0x2706
comma
l_string|&quot;Conditional write protect&quot;
)brace
comma
(brace
l_int|0x2800
comma
l_string|&quot;Not ready to ready change, medium may have changed&quot;
)brace
comma
(brace
l_int|0x2801
comma
l_string|&quot;Import or export element accessed&quot;
)brace
comma
(brace
l_int|0x2900
comma
l_string|&quot;Power on, reset, or bus device reset occurred&quot;
)brace
comma
(brace
l_int|0x2901
comma
l_string|&quot;Power on occurred&quot;
)brace
comma
(brace
l_int|0x2902
comma
l_string|&quot;Scsi bus reset occurred&quot;
)brace
comma
(brace
l_int|0x2903
comma
l_string|&quot;Bus device reset function occurred&quot;
)brace
comma
(brace
l_int|0x2904
comma
l_string|&quot;Device internal reset&quot;
)brace
comma
(brace
l_int|0x2905
comma
l_string|&quot;Transceiver mode changed to single-ended&quot;
)brace
comma
(brace
l_int|0x2906
comma
l_string|&quot;Transceiver mode changed to lvd&quot;
)brace
comma
(brace
l_int|0x2907
comma
l_string|&quot;I_T nexus loss occurred&quot;
)brace
comma
(brace
l_int|0x2A00
comma
l_string|&quot;Parameters changed&quot;
)brace
comma
(brace
l_int|0x2A01
comma
l_string|&quot;Mode parameters changed&quot;
)brace
comma
(brace
l_int|0x2A02
comma
l_string|&quot;Log parameters changed&quot;
)brace
comma
(brace
l_int|0x2A03
comma
l_string|&quot;Reservations preempted&quot;
)brace
comma
(brace
l_int|0x2A04
comma
l_string|&quot;Reservations released&quot;
)brace
comma
(brace
l_int|0x2A05
comma
l_string|&quot;Registrations preempted&quot;
)brace
comma
(brace
l_int|0x2A06
comma
l_string|&quot;Asymmetric access state changed&quot;
)brace
comma
(brace
l_int|0x2A07
comma
l_string|&quot;Implicit asymmetric access state transition failed&quot;
)brace
comma
(brace
l_int|0x2B00
comma
l_string|&quot;Copy cannot execute since host cannot disconnect&quot;
)brace
comma
(brace
l_int|0x2C00
comma
l_string|&quot;Command sequence error&quot;
)brace
comma
(brace
l_int|0x2C01
comma
l_string|&quot;Too many windows specified&quot;
)brace
comma
(brace
l_int|0x2C02
comma
l_string|&quot;Invalid combination of windows specified&quot;
)brace
comma
(brace
l_int|0x2C03
comma
l_string|&quot;Current program area is not empty&quot;
)brace
comma
(brace
l_int|0x2C04
comma
l_string|&quot;Current program area is empty&quot;
)brace
comma
(brace
l_int|0x2C05
comma
l_string|&quot;Illegal power condition request&quot;
)brace
comma
(brace
l_int|0x2C06
comma
l_string|&quot;Persistent prevent conflict&quot;
)brace
comma
(brace
l_int|0x2C07
comma
l_string|&quot;Previous busy status&quot;
)brace
comma
(brace
l_int|0x2C08
comma
l_string|&quot;Previous task set full status&quot;
)brace
comma
(brace
l_int|0x2C09
comma
l_string|&quot;Previous reservation conflict status&quot;
)brace
comma
(brace
l_int|0x2D00
comma
l_string|&quot;Overwrite error on update in place&quot;
)brace
comma
(brace
l_int|0x2E00
comma
l_string|&quot;Insufficient time for operation&quot;
)brace
comma
(brace
l_int|0x2F00
comma
l_string|&quot;Commands cleared by another initiator&quot;
)brace
comma
(brace
l_int|0x3000
comma
l_string|&quot;Incompatible medium installed&quot;
)brace
comma
(brace
l_int|0x3001
comma
l_string|&quot;Cannot read medium - unknown format&quot;
)brace
comma
(brace
l_int|0x3002
comma
l_string|&quot;Cannot read medium - incompatible format&quot;
)brace
comma
(brace
l_int|0x3003
comma
l_string|&quot;Cleaning cartridge installed&quot;
)brace
comma
(brace
l_int|0x3004
comma
l_string|&quot;Cannot write medium - unknown format&quot;
)brace
comma
(brace
l_int|0x3005
comma
l_string|&quot;Cannot write medium - incompatible format&quot;
)brace
comma
(brace
l_int|0x3006
comma
l_string|&quot;Cannot format medium - incompatible medium&quot;
)brace
comma
(brace
l_int|0x3007
comma
l_string|&quot;Cleaning failure&quot;
)brace
comma
(brace
l_int|0x3008
comma
l_string|&quot;Cannot write - application code mismatch&quot;
)brace
comma
(brace
l_int|0x3009
comma
l_string|&quot;Current session not fixated for append&quot;
)brace
comma
(brace
l_int|0x3010
comma
l_string|&quot;Medium not formatted&quot;
)brace
comma
(brace
l_int|0x3100
comma
l_string|&quot;Medium format corrupted&quot;
)brace
comma
(brace
l_int|0x3101
comma
l_string|&quot;Format command failed&quot;
)brace
comma
(brace
l_int|0x3102
comma
l_string|&quot;Zoned formatting failed due to spare linking&quot;
)brace
comma
(brace
l_int|0x3200
comma
l_string|&quot;No defect spare location available&quot;
)brace
comma
(brace
l_int|0x3201
comma
l_string|&quot;Defect list update failure&quot;
)brace
comma
(brace
l_int|0x3300
comma
l_string|&quot;Tape length error&quot;
)brace
comma
(brace
l_int|0x3400
comma
l_string|&quot;Enclosure failure&quot;
)brace
comma
(brace
l_int|0x3500
comma
l_string|&quot;Enclosure services failure&quot;
)brace
comma
(brace
l_int|0x3501
comma
l_string|&quot;Unsupported enclosure function&quot;
)brace
comma
(brace
l_int|0x3502
comma
l_string|&quot;Enclosure services unavailable&quot;
)brace
comma
(brace
l_int|0x3503
comma
l_string|&quot;Enclosure services transfer failure&quot;
)brace
comma
(brace
l_int|0x3504
comma
l_string|&quot;Enclosure services transfer refused&quot;
)brace
comma
(brace
l_int|0x3600
comma
l_string|&quot;Ribbon, ink, or toner failure&quot;
)brace
comma
(brace
l_int|0x3700
comma
l_string|&quot;Rounded parameter&quot;
)brace
comma
(brace
l_int|0x3800
comma
l_string|&quot;Event status notification&quot;
)brace
comma
(brace
l_int|0x3802
comma
l_string|&quot;Esn - power management class event&quot;
)brace
comma
(brace
l_int|0x3804
comma
l_string|&quot;Esn - media class event&quot;
)brace
comma
(brace
l_int|0x3806
comma
l_string|&quot;Esn - device busy class event&quot;
)brace
comma
(brace
l_int|0x3900
comma
l_string|&quot;Saving parameters not supported&quot;
)brace
comma
(brace
l_int|0x3A00
comma
l_string|&quot;Medium not present&quot;
)brace
comma
(brace
l_int|0x3A01
comma
l_string|&quot;Medium not present - tray closed&quot;
)brace
comma
(brace
l_int|0x3A02
comma
l_string|&quot;Medium not present - tray open&quot;
)brace
comma
(brace
l_int|0x3A03
comma
l_string|&quot;Medium not present - loadable&quot;
)brace
comma
(brace
l_int|0x3A04
comma
l_string|&quot;Medium not present - medium auxiliary memory accessible&quot;
)brace
comma
(brace
l_int|0x3B00
comma
l_string|&quot;Sequential positioning error&quot;
)brace
comma
(brace
l_int|0x3B01
comma
l_string|&quot;Tape position error at beginning-of-medium&quot;
)brace
comma
(brace
l_int|0x3B02
comma
l_string|&quot;Tape position error at end-of-medium&quot;
)brace
comma
(brace
l_int|0x3B03
comma
l_string|&quot;Tape or electronic vertical forms unit not ready&quot;
)brace
comma
(brace
l_int|0x3B04
comma
l_string|&quot;Slew failure&quot;
)brace
comma
(brace
l_int|0x3B05
comma
l_string|&quot;Paper jam&quot;
)brace
comma
(brace
l_int|0x3B06
comma
l_string|&quot;Failed to sense top-of-form&quot;
)brace
comma
(brace
l_int|0x3B07
comma
l_string|&quot;Failed to sense bottom-of-form&quot;
)brace
comma
(brace
l_int|0x3B08
comma
l_string|&quot;Reposition error&quot;
)brace
comma
(brace
l_int|0x3B09
comma
l_string|&quot;Read past end of medium&quot;
)brace
comma
(brace
l_int|0x3B0A
comma
l_string|&quot;Read past beginning of medium&quot;
)brace
comma
(brace
l_int|0x3B0B
comma
l_string|&quot;Position past end of medium&quot;
)brace
comma
(brace
l_int|0x3B0C
comma
l_string|&quot;Position past beginning of medium&quot;
)brace
comma
(brace
l_int|0x3B0D
comma
l_string|&quot;Medium destination element full&quot;
)brace
comma
(brace
l_int|0x3B0E
comma
l_string|&quot;Medium source element empty&quot;
)brace
comma
(brace
l_int|0x3B0F
comma
l_string|&quot;End of medium reached&quot;
)brace
comma
(brace
l_int|0x3B11
comma
l_string|&quot;Medium magazine not accessible&quot;
)brace
comma
(brace
l_int|0x3B12
comma
l_string|&quot;Medium magazine removed&quot;
)brace
comma
(brace
l_int|0x3B13
comma
l_string|&quot;Medium magazine inserted&quot;
)brace
comma
(brace
l_int|0x3B14
comma
l_string|&quot;Medium magazine locked&quot;
)brace
comma
(brace
l_int|0x3B15
comma
l_string|&quot;Medium magazine unlocked&quot;
)brace
comma
(brace
l_int|0x3B16
comma
l_string|&quot;Mechanical positioning or changer error&quot;
)brace
comma
(brace
l_int|0x3D00
comma
l_string|&quot;Invalid bits in identify message&quot;
)brace
comma
(brace
l_int|0x3E00
comma
l_string|&quot;Logical unit has not self-configured yet&quot;
)brace
comma
(brace
l_int|0x3E01
comma
l_string|&quot;Logical unit failure&quot;
)brace
comma
(brace
l_int|0x3E02
comma
l_string|&quot;Timeout on logical unit&quot;
)brace
comma
(brace
l_int|0x3E03
comma
l_string|&quot;Logical unit failed self-test&quot;
)brace
comma
(brace
l_int|0x3E04
comma
l_string|&quot;Logical unit unable to update self-test log&quot;
)brace
comma
(brace
l_int|0x3F00
comma
l_string|&quot;Target operating conditions have changed&quot;
)brace
comma
(brace
l_int|0x3F01
comma
l_string|&quot;Microcode has been changed&quot;
)brace
comma
(brace
l_int|0x3F02
comma
l_string|&quot;Changed operating definition&quot;
)brace
comma
(brace
l_int|0x3F03
comma
l_string|&quot;Inquiry data has changed&quot;
)brace
comma
(brace
l_int|0x3F04
comma
l_string|&quot;Component device attached&quot;
)brace
comma
(brace
l_int|0x3F05
comma
l_string|&quot;Device identifier changed&quot;
)brace
comma
(brace
l_int|0x3F06
comma
l_string|&quot;Redundancy group created or modified&quot;
)brace
comma
(brace
l_int|0x3F07
comma
l_string|&quot;Redundancy group deleted&quot;
)brace
comma
(brace
l_int|0x3F08
comma
l_string|&quot;Spare created or modified&quot;
)brace
comma
(brace
l_int|0x3F09
comma
l_string|&quot;Spare deleted&quot;
)brace
comma
(brace
l_int|0x3F0A
comma
l_string|&quot;Volume set created or modified&quot;
)brace
comma
(brace
l_int|0x3F0B
comma
l_string|&quot;Volume set deleted&quot;
)brace
comma
(brace
l_int|0x3F0C
comma
l_string|&quot;Volume set deassigned&quot;
)brace
comma
(brace
l_int|0x3F0D
comma
l_string|&quot;Volume set reassigned&quot;
)brace
comma
(brace
l_int|0x3F0E
comma
l_string|&quot;Reported luns data has changed&quot;
)brace
comma
(brace
l_int|0x3F0F
comma
l_string|&quot;Echo buffer overwritten&quot;
)brace
comma
(brace
l_int|0x3F10
comma
l_string|&quot;Medium loadable&quot;
)brace
comma
(brace
l_int|0x3F11
comma
l_string|&quot;Medium auxiliary memory accessible&quot;
)brace
comma
macro_line|#if 0
(brace
l_int|0x40
id|NN
comma
l_string|&quot;Ram failure&quot;
)brace
comma
(brace
l_int|0x40
id|NN
comma
l_string|&quot;Diagnostic failure on component nn&quot;
)brace
comma
(brace
l_int|0x41
id|NN
comma
l_string|&quot;Data path failure&quot;
)brace
comma
(brace
l_int|0x42
id|NN
comma
l_string|&quot;Power-on or self-test failure&quot;
)brace
comma
macro_line|#endif
(brace
l_int|0x4300
comma
l_string|&quot;Message error&quot;
)brace
comma
(brace
l_int|0x4400
comma
l_string|&quot;Internal target failure&quot;
)brace
comma
(brace
l_int|0x4500
comma
l_string|&quot;Select or reselect failure&quot;
)brace
comma
(brace
l_int|0x4600
comma
l_string|&quot;Unsuccessful soft reset&quot;
)brace
comma
(brace
l_int|0x4700
comma
l_string|&quot;Scsi parity error&quot;
)brace
comma
(brace
l_int|0x4701
comma
l_string|&quot;Data phase CRC error detected&quot;
)brace
comma
(brace
l_int|0x4702
comma
l_string|&quot;Scsi parity error detected during st data phase&quot;
)brace
comma
(brace
l_int|0x4703
comma
l_string|&quot;Information unit CRC error detected&quot;
)brace
comma
(brace
l_int|0x4704
comma
l_string|&quot;Asynchronous information protection error detected&quot;
)brace
comma
(brace
l_int|0x4705
comma
l_string|&quot;Protocol service CRC error&quot;
)brace
comma
(brace
l_int|0x4800
comma
l_string|&quot;Initiator detected error message received&quot;
)brace
comma
(brace
l_int|0x4900
comma
l_string|&quot;Invalid message error&quot;
)brace
comma
(brace
l_int|0x4A00
comma
l_string|&quot;Command phase error&quot;
)brace
comma
(brace
l_int|0x4B00
comma
l_string|&quot;Data phase error&quot;
)brace
comma
(brace
l_int|0x4C00
comma
l_string|&quot;Logical unit failed self-configuration&quot;
)brace
comma
macro_line|#if 0
(brace
l_int|0x4D
id|NN
comma
l_string|&quot;Tagged overlapped commands (nn = queue tag)&quot;
)brace
comma
macro_line|#endif
(brace
l_int|0x4E00
comma
l_string|&quot;Overlapped commands attempted&quot;
)brace
comma
(brace
l_int|0x5000
comma
l_string|&quot;Write append error&quot;
)brace
comma
(brace
l_int|0x5001
comma
l_string|&quot;Write append position error&quot;
)brace
comma
(brace
l_int|0x5002
comma
l_string|&quot;Position error related to timing&quot;
)brace
comma
(brace
l_int|0x5100
comma
l_string|&quot;Erase failure&quot;
)brace
comma
(brace
l_int|0x5101
comma
l_string|&quot;Erase failure - incomplete erase operation detected&quot;
)brace
comma
(brace
l_int|0x5200
comma
l_string|&quot;Cartridge fault&quot;
)brace
comma
(brace
l_int|0x5300
comma
l_string|&quot;Media load or eject failed&quot;
)brace
comma
(brace
l_int|0x5301
comma
l_string|&quot;Unload tape failure&quot;
)brace
comma
(brace
l_int|0x5302
comma
l_string|&quot;Medium removal prevented&quot;
)brace
comma
(brace
l_int|0x5400
comma
l_string|&quot;Scsi to host system interface failure&quot;
)brace
comma
(brace
l_int|0x5500
comma
l_string|&quot;System resource failure&quot;
)brace
comma
(brace
l_int|0x5501
comma
l_string|&quot;System buffer full&quot;
)brace
comma
(brace
l_int|0x5502
comma
l_string|&quot;Insufficient reservation resources&quot;
)brace
comma
(brace
l_int|0x5503
comma
l_string|&quot;Insufficient resources&quot;
)brace
comma
(brace
l_int|0x5504
comma
l_string|&quot;Insufficient registration resources&quot;
)brace
comma
(brace
l_int|0x5505
comma
l_string|&quot;Insufficient access control resources&quot;
)brace
comma
(brace
l_int|0x5506
comma
l_string|&quot;Auxiliary memory out of space&quot;
)brace
comma
(brace
l_int|0x5700
comma
l_string|&quot;Unable to recover table-of-contents&quot;
)brace
comma
(brace
l_int|0x5800
comma
l_string|&quot;Generation does not exist&quot;
)brace
comma
(brace
l_int|0x5900
comma
l_string|&quot;Updated block read&quot;
)brace
comma
(brace
l_int|0x5A00
comma
l_string|&quot;Operator request or state change input&quot;
)brace
comma
(brace
l_int|0x5A01
comma
l_string|&quot;Operator medium removal request&quot;
)brace
comma
(brace
l_int|0x5A02
comma
l_string|&quot;Operator selected write protect&quot;
)brace
comma
(brace
l_int|0x5A03
comma
l_string|&quot;Operator selected write permit&quot;
)brace
comma
(brace
l_int|0x5B00
comma
l_string|&quot;Log exception&quot;
)brace
comma
(brace
l_int|0x5B01
comma
l_string|&quot;Threshold condition met&quot;
)brace
comma
(brace
l_int|0x5B02
comma
l_string|&quot;Log counter at maximum&quot;
)brace
comma
(brace
l_int|0x5B03
comma
l_string|&quot;Log list codes exhausted&quot;
)brace
comma
(brace
l_int|0x5C00
comma
l_string|&quot;Rpl status change&quot;
)brace
comma
(brace
l_int|0x5C01
comma
l_string|&quot;Spindles synchronized&quot;
)brace
comma
(brace
l_int|0x5C02
comma
l_string|&quot;Spindles not synchronized&quot;
)brace
comma
(brace
l_int|0x5D00
comma
l_string|&quot;Failure prediction threshold exceeded&quot;
)brace
comma
(brace
l_int|0x5D01
comma
l_string|&quot;Media failure prediction threshold exceeded&quot;
)brace
comma
(brace
l_int|0x5D02
comma
l_string|&quot;Logical unit failure prediction threshold exceeded&quot;
)brace
comma
(brace
l_int|0x5D03
comma
l_string|&quot;Spare area exhaustion prediction threshold exceeded&quot;
)brace
comma
(brace
l_int|0x5D10
comma
l_string|&quot;Hardware impending failure general hard drive failure&quot;
)brace
comma
(brace
l_int|0x5D11
comma
l_string|&quot;Hardware impending failure drive error rate too high&quot;
)brace
comma
(brace
l_int|0x5D12
comma
l_string|&quot;Hardware impending failure data error rate too high&quot;
)brace
comma
(brace
l_int|0x5D13
comma
l_string|&quot;Hardware impending failure seek error rate too high&quot;
)brace
comma
(brace
l_int|0x5D14
comma
l_string|&quot;Hardware impending failure too many block reassigns&quot;
)brace
comma
(brace
l_int|0x5D15
comma
l_string|&quot;Hardware impending failure access times too high&quot;
)brace
comma
(brace
l_int|0x5D16
comma
l_string|&quot;Hardware impending failure start unit times too high&quot;
)brace
comma
(brace
l_int|0x5D17
comma
l_string|&quot;Hardware impending failure channel parametrics&quot;
)brace
comma
(brace
l_int|0x5D18
comma
l_string|&quot;Hardware impending failure controller detected&quot;
)brace
comma
(brace
l_int|0x5D19
comma
l_string|&quot;Hardware impending failure throughput performance&quot;
)brace
comma
(brace
l_int|0x5D1A
comma
l_string|&quot;Hardware impending failure seek time performance&quot;
)brace
comma
(brace
l_int|0x5D1B
comma
l_string|&quot;Hardware impending failure spin-up retry count&quot;
)brace
comma
(brace
l_int|0x5D1C
comma
l_string|&quot;Hardware impending failure drive calibration retry count&quot;
)brace
comma
(brace
l_int|0x5D20
comma
l_string|&quot;Controller impending failure general hard drive failure&quot;
)brace
comma
(brace
l_int|0x5D21
comma
l_string|&quot;Controller impending failure drive error rate too high&quot;
)brace
comma
(brace
l_int|0x5D22
comma
l_string|&quot;Controller impending failure data error rate too high&quot;
)brace
comma
(brace
l_int|0x5D23
comma
l_string|&quot;Controller impending failure seek error rate too high&quot;
)brace
comma
(brace
l_int|0x5D24
comma
l_string|&quot;Controller impending failure too many block reassigns&quot;
)brace
comma
(brace
l_int|0x5D25
comma
l_string|&quot;Controller impending failure access times too high&quot;
)brace
comma
(brace
l_int|0x5D26
comma
l_string|&quot;Controller impending failure start unit times too high&quot;
)brace
comma
(brace
l_int|0x5D27
comma
l_string|&quot;Controller impending failure channel parametrics&quot;
)brace
comma
(brace
l_int|0x5D28
comma
l_string|&quot;Controller impending failure controller detected&quot;
)brace
comma
(brace
l_int|0x5D29
comma
l_string|&quot;Controller impending failure throughput performance&quot;
)brace
comma
(brace
l_int|0x5D2A
comma
l_string|&quot;Controller impending failure seek time performance&quot;
)brace
comma
(brace
l_int|0x5D2B
comma
l_string|&quot;Controller impending failure spin-up retry count&quot;
)brace
comma
(brace
l_int|0x5D2C
comma
l_string|&quot;Controller impending failure drive calibration retry count&quot;
)brace
comma
(brace
l_int|0x5D30
comma
l_string|&quot;Data channel impending failure general hard drive failure&quot;
)brace
comma
(brace
l_int|0x5D31
comma
l_string|&quot;Data channel impending failure drive error rate too high&quot;
)brace
comma
(brace
l_int|0x5D32
comma
l_string|&quot;Data channel impending failure data error rate too high&quot;
)brace
comma
(brace
l_int|0x5D33
comma
l_string|&quot;Data channel impending failure seek error rate too high&quot;
)brace
comma
(brace
l_int|0x5D34
comma
l_string|&quot;Data channel impending failure too many block reassigns&quot;
)brace
comma
(brace
l_int|0x5D35
comma
l_string|&quot;Data channel impending failure access times too high&quot;
)brace
comma
(brace
l_int|0x5D36
comma
l_string|&quot;Data channel impending failure start unit times too high&quot;
)brace
comma
(brace
l_int|0x5D37
comma
l_string|&quot;Data channel impending failure channel parametrics&quot;
)brace
comma
(brace
l_int|0x5D38
comma
l_string|&quot;Data channel impending failure controller detected&quot;
)brace
comma
(brace
l_int|0x5D39
comma
l_string|&quot;Data channel impending failure throughput performance&quot;
)brace
comma
(brace
l_int|0x5D3A
comma
l_string|&quot;Data channel impending failure seek time performance&quot;
)brace
comma
(brace
l_int|0x5D3B
comma
l_string|&quot;Data channel impending failure spin-up retry count&quot;
)brace
comma
(brace
l_int|0x5D3C
comma
l_string|&quot;Data channel impending failure drive calibration retry &quot;
l_string|&quot;count&quot;
)brace
comma
(brace
l_int|0x5D40
comma
l_string|&quot;Servo impending failure general hard drive failure&quot;
)brace
comma
(brace
l_int|0x5D41
comma
l_string|&quot;Servo impending failure drive error rate too high&quot;
)brace
comma
(brace
l_int|0x5D42
comma
l_string|&quot;Servo impending failure data error rate too high&quot;
)brace
comma
(brace
l_int|0x5D43
comma
l_string|&quot;Servo impending failure seek error rate too high&quot;
)brace
comma
(brace
l_int|0x5D44
comma
l_string|&quot;Servo impending failure too many block reassigns&quot;
)brace
comma
(brace
l_int|0x5D45
comma
l_string|&quot;Servo impending failure access times too high&quot;
)brace
comma
(brace
l_int|0x5D46
comma
l_string|&quot;Servo impending failure start unit times too high&quot;
)brace
comma
(brace
l_int|0x5D47
comma
l_string|&quot;Servo impending failure channel parametrics&quot;
)brace
comma
(brace
l_int|0x5D48
comma
l_string|&quot;Servo impending failure controller detected&quot;
)brace
comma
(brace
l_int|0x5D49
comma
l_string|&quot;Servo impending failure throughput performance&quot;
)brace
comma
(brace
l_int|0x5D4A
comma
l_string|&quot;Servo impending failure seek time performance&quot;
)brace
comma
(brace
l_int|0x5D4B
comma
l_string|&quot;Servo impending failure spin-up retry count&quot;
)brace
comma
(brace
l_int|0x5D4C
comma
l_string|&quot;Servo impending failure drive calibration retry count&quot;
)brace
comma
(brace
l_int|0x5D50
comma
l_string|&quot;Spindle impending failure general hard drive failure&quot;
)brace
comma
(brace
l_int|0x5D51
comma
l_string|&quot;Spindle impending failure drive error rate too high&quot;
)brace
comma
(brace
l_int|0x5D52
comma
l_string|&quot;Spindle impending failure data error rate too high&quot;
)brace
comma
(brace
l_int|0x5D53
comma
l_string|&quot;Spindle impending failure seek error rate too high&quot;
)brace
comma
(brace
l_int|0x5D54
comma
l_string|&quot;Spindle impending failure too many block reassigns&quot;
)brace
comma
(brace
l_int|0x5D55
comma
l_string|&quot;Spindle impending failure access times too high&quot;
)brace
comma
(brace
l_int|0x5D56
comma
l_string|&quot;Spindle impending failure start unit times too high&quot;
)brace
comma
(brace
l_int|0x5D57
comma
l_string|&quot;Spindle impending failure channel parametrics&quot;
)brace
comma
(brace
l_int|0x5D58
comma
l_string|&quot;Spindle impending failure controller detected&quot;
)brace
comma
(brace
l_int|0x5D59
comma
l_string|&quot;Spindle impending failure throughput performance&quot;
)brace
comma
(brace
l_int|0x5D5A
comma
l_string|&quot;Spindle impending failure seek time performance&quot;
)brace
comma
(brace
l_int|0x5D5B
comma
l_string|&quot;Spindle impending failure spin-up retry count&quot;
)brace
comma
(brace
l_int|0x5D5C
comma
l_string|&quot;Spindle impending failure drive calibration retry count&quot;
)brace
comma
(brace
l_int|0x5D60
comma
l_string|&quot;Firmware impending failure general hard drive failure&quot;
)brace
comma
(brace
l_int|0x5D61
comma
l_string|&quot;Firmware impending failure drive error rate too high&quot;
)brace
comma
(brace
l_int|0x5D62
comma
l_string|&quot;Firmware impending failure data error rate too high&quot;
)brace
comma
(brace
l_int|0x5D63
comma
l_string|&quot;Firmware impending failure seek error rate too high&quot;
)brace
comma
(brace
l_int|0x5D64
comma
l_string|&quot;Firmware impending failure too many block reassigns&quot;
)brace
comma
(brace
l_int|0x5D65
comma
l_string|&quot;Firmware impending failure access times too high&quot;
)brace
comma
(brace
l_int|0x5D66
comma
l_string|&quot;Firmware impending failure start unit times too high&quot;
)brace
comma
(brace
l_int|0x5D67
comma
l_string|&quot;Firmware impending failure channel parametrics&quot;
)brace
comma
(brace
l_int|0x5D68
comma
l_string|&quot;Firmware impending failure controller detected&quot;
)brace
comma
(brace
l_int|0x5D69
comma
l_string|&quot;Firmware impending failure throughput performance&quot;
)brace
comma
(brace
l_int|0x5D6A
comma
l_string|&quot;Firmware impending failure seek time performance&quot;
)brace
comma
(brace
l_int|0x5D6B
comma
l_string|&quot;Firmware impending failure spin-up retry count&quot;
)brace
comma
(brace
l_int|0x5D6C
comma
l_string|&quot;Firmware impending failure drive calibration retry count&quot;
)brace
comma
(brace
l_int|0x5DFF
comma
l_string|&quot;Failure prediction threshold exceeded (false)&quot;
)brace
comma
(brace
l_int|0x5E00
comma
l_string|&quot;Low power condition on&quot;
)brace
comma
(brace
l_int|0x5E01
comma
l_string|&quot;Idle condition activated by timer&quot;
)brace
comma
(brace
l_int|0x5E02
comma
l_string|&quot;Standby condition activated by timer&quot;
)brace
comma
(brace
l_int|0x5E03
comma
l_string|&quot;Idle condition activated by command&quot;
)brace
comma
(brace
l_int|0x5E04
comma
l_string|&quot;Standby condition activated by command&quot;
)brace
comma
(brace
l_int|0x5E41
comma
l_string|&quot;Power state change to active&quot;
)brace
comma
(brace
l_int|0x5E42
comma
l_string|&quot;Power state change to idle&quot;
)brace
comma
(brace
l_int|0x5E43
comma
l_string|&quot;Power state change to standby&quot;
)brace
comma
(brace
l_int|0x5E45
comma
l_string|&quot;Power state change to sleep&quot;
)brace
comma
(brace
l_int|0x5E47
comma
l_string|&quot;Power state change to device control&quot;
)brace
comma
(brace
l_int|0x6000
comma
l_string|&quot;Lamp failure&quot;
)brace
comma
(brace
l_int|0x6100
comma
l_string|&quot;Video acquisition error&quot;
)brace
comma
(brace
l_int|0x6101
comma
l_string|&quot;Unable to acquire video&quot;
)brace
comma
(brace
l_int|0x6102
comma
l_string|&quot;Out of focus&quot;
)brace
comma
(brace
l_int|0x6200
comma
l_string|&quot;Scan head positioning error&quot;
)brace
comma
(brace
l_int|0x6300
comma
l_string|&quot;End of user area encountered on this track&quot;
)brace
comma
(brace
l_int|0x6301
comma
l_string|&quot;Packet does not fit in available space&quot;
)brace
comma
(brace
l_int|0x6400
comma
l_string|&quot;Illegal mode for this track&quot;
)brace
comma
(brace
l_int|0x6401
comma
l_string|&quot;Invalid packet size&quot;
)brace
comma
(brace
l_int|0x6500
comma
l_string|&quot;Voltage fault&quot;
)brace
comma
(brace
l_int|0x6600
comma
l_string|&quot;Automatic document feeder cover up&quot;
)brace
comma
(brace
l_int|0x6601
comma
l_string|&quot;Automatic document feeder lift up&quot;
)brace
comma
(brace
l_int|0x6602
comma
l_string|&quot;Document jam in automatic document feeder&quot;
)brace
comma
(brace
l_int|0x6603
comma
l_string|&quot;Document miss feed automatic in document feeder&quot;
)brace
comma
(brace
l_int|0x6700
comma
l_string|&quot;Configuration failure&quot;
)brace
comma
(brace
l_int|0x6701
comma
l_string|&quot;Configuration of incapable logical units failed&quot;
)brace
comma
(brace
l_int|0x6702
comma
l_string|&quot;Add logical unit failed&quot;
)brace
comma
(brace
l_int|0x6703
comma
l_string|&quot;Modification of logical unit failed&quot;
)brace
comma
(brace
l_int|0x6704
comma
l_string|&quot;Exchange of logical unit failed&quot;
)brace
comma
(brace
l_int|0x6705
comma
l_string|&quot;Remove of logical unit failed&quot;
)brace
comma
(brace
l_int|0x6706
comma
l_string|&quot;Attachment of logical unit failed&quot;
)brace
comma
(brace
l_int|0x6707
comma
l_string|&quot;Creation of logical unit failed&quot;
)brace
comma
(brace
l_int|0x6708
comma
l_string|&quot;Assign failure occurred&quot;
)brace
comma
(brace
l_int|0x6709
comma
l_string|&quot;Multiply assigned logical unit&quot;
)brace
comma
(brace
l_int|0x670A
comma
l_string|&quot;Set target port groups command failed&quot;
)brace
comma
(brace
l_int|0x6800
comma
l_string|&quot;Logical unit not configured&quot;
)brace
comma
(brace
l_int|0x6900
comma
l_string|&quot;Data loss on logical unit&quot;
)brace
comma
(brace
l_int|0x6901
comma
l_string|&quot;Multiple logical unit failures&quot;
)brace
comma
(brace
l_int|0x6902
comma
l_string|&quot;Parity/data mismatch&quot;
)brace
comma
(brace
l_int|0x6A00
comma
l_string|&quot;Informational, refer to log&quot;
)brace
comma
(brace
l_int|0x6B00
comma
l_string|&quot;State change has occurred&quot;
)brace
comma
(brace
l_int|0x6B01
comma
l_string|&quot;Redundancy level got better&quot;
)brace
comma
(brace
l_int|0x6B02
comma
l_string|&quot;Redundancy level got worse&quot;
)brace
comma
(brace
l_int|0x6C00
comma
l_string|&quot;Rebuild failure occurred&quot;
)brace
comma
(brace
l_int|0x6D00
comma
l_string|&quot;Recalculate failure occurred&quot;
)brace
comma
(brace
l_int|0x6E00
comma
l_string|&quot;Command to logical unit failed&quot;
)brace
comma
(brace
l_int|0x6F00
comma
l_string|&quot;Copy protection key exchange failure - authentication &quot;
l_string|&quot;failure&quot;
)brace
comma
(brace
l_int|0x6F01
comma
l_string|&quot;Copy protection key exchange failure - key not present&quot;
)brace
comma
(brace
l_int|0x6F02
comma
l_string|&quot;Copy protection key exchange failure - key not established&quot;
)brace
comma
(brace
l_int|0x6F03
comma
l_string|&quot;Read of scrambled sector without authentication&quot;
)brace
comma
(brace
l_int|0x6F04
comma
l_string|&quot;Media region code is mismatched to logical unit region&quot;
)brace
comma
(brace
l_int|0x6F05
comma
l_string|&quot;Drive region must be permanent/region reset count error&quot;
)brace
comma
macro_line|#if 0
(brace
l_int|0x70
id|NN
comma
l_string|&quot;Decompression exception short algorithm id of nn&quot;
)brace
comma
macro_line|#endif
(brace
l_int|0x7100
comma
l_string|&quot;Decompression exception long algorithm id&quot;
)brace
comma
(brace
l_int|0x7200
comma
l_string|&quot;Session fixation error&quot;
)brace
comma
(brace
l_int|0x7201
comma
l_string|&quot;Session fixation error writing lead-in&quot;
)brace
comma
(brace
l_int|0x7202
comma
l_string|&quot;Session fixation error writing lead-out&quot;
)brace
comma
(brace
l_int|0x7203
comma
l_string|&quot;Session fixation error - incomplete track in session&quot;
)brace
comma
(brace
l_int|0x7204
comma
l_string|&quot;Empty or partially written reserved track&quot;
)brace
comma
(brace
l_int|0x7205
comma
l_string|&quot;No more track reservations allowed&quot;
)brace
comma
(brace
l_int|0x7300
comma
l_string|&quot;Cd control error&quot;
)brace
comma
(brace
l_int|0x7301
comma
l_string|&quot;Power calibration area almost full&quot;
)brace
comma
(brace
l_int|0x7302
comma
l_string|&quot;Power calibration area is full&quot;
)brace
comma
(brace
l_int|0x7303
comma
l_string|&quot;Power calibration area error&quot;
)brace
comma
(brace
l_int|0x7304
comma
l_string|&quot;Program memory area update failure&quot;
)brace
comma
(brace
l_int|0x7305
comma
l_string|&quot;Program memory area is full&quot;
)brace
comma
(brace
l_int|0x7306
comma
l_string|&quot;RMA/PMA is almost full&quot;
)brace
comma
(brace
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|struct|error_info2
r_struct
id|error_info2
(brace
DECL|member|code1
DECL|member|code2_min
DECL|member|code2_max
r_int
r_char
id|code1
comma
id|code2_min
comma
id|code2_max
suffix:semicolon
DECL|member|fmt
r_const
r_char
op_star
id|fmt
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|additional2
r_static
r_struct
id|error_info2
id|additional2
(braket
)braket
op_assign
(brace
(brace
l_int|0x40
comma
l_int|0x00
comma
l_int|0x7f
comma
l_string|&quot;Ram failure (%x)&quot;
)brace
comma
(brace
l_int|0x40
comma
l_int|0x80
comma
l_int|0xff
comma
l_string|&quot;Diagnostic failure on component (%x)&quot;
)brace
comma
(brace
l_int|0x41
comma
l_int|0x00
comma
l_int|0xff
comma
l_string|&quot;Data path failure (%x)&quot;
)brace
comma
(brace
l_int|0x42
comma
l_int|0x00
comma
l_int|0xff
comma
l_string|&quot;Power-on or self-test failure (%x)&quot;
)brace
comma
(brace
l_int|0x4D
comma
l_int|0x00
comma
l_int|0xff
comma
l_string|&quot;Tagged overlapped commands (queue tag %x)&quot;
)brace
comma
(brace
l_int|0x70
comma
l_int|0x00
comma
l_int|0xff
comma
l_string|&quot;Decompression exception short algorithm id of %x&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
macro_line|#endif
macro_line|#if (CONSTANTS &amp; CONST_SENSE)
multiline_comment|/* description of the sense key values */
DECL|variable|snstext
r_static
r_const
r_char
op_star
id|snstext
(braket
)braket
op_assign
(brace
l_string|&quot;No Sense&quot;
comma
multiline_comment|/* 0: There is no sense information */
l_string|&quot;Recovered Error&quot;
comma
multiline_comment|/* 1: The last command completed successfully&n;&t;&t;&t;&t;  but used error correction */
l_string|&quot;Not Ready&quot;
comma
multiline_comment|/* 2: The addressed target is not ready */
l_string|&quot;Medium Error&quot;
comma
multiline_comment|/* 3: Data error detected on the medium */
l_string|&quot;Hardware Error&quot;
comma
multiline_comment|/* 4: Controller or device failure */
l_string|&quot;Illegal Request&quot;
comma
multiline_comment|/* 5: Error in request */
l_string|&quot;Unit Attention&quot;
comma
multiline_comment|/* 6: Removable medium was changed, or&n;&t;&t;&t;&t;  the target has been reset */
l_string|&quot;Data Protect&quot;
comma
multiline_comment|/* 7: Access to the data is blocked */
l_string|&quot;Blank Check&quot;
comma
multiline_comment|/* 8: Reached unexpected written or unwritten&n;&t;&t;&t;&t;  region of the medium */
l_string|&quot;Vendor Specific&quot;
comma
multiline_comment|/* 9: Vendor specific */
l_string|&quot;Copy Aborted&quot;
comma
multiline_comment|/* A: COPY or COMPARE was aborted */
l_string|&quot;Aborted Command&quot;
comma
multiline_comment|/* B: The target aborted the command */
l_string|&quot;Equal&quot;
comma
multiline_comment|/* C: A SEARCH DATA command found data equal */
l_string|&quot;Volume Overflow&quot;
comma
multiline_comment|/* D: Medium full with still data to be written */
l_string|&quot;Miscompare&quot;
comma
multiline_comment|/* E: Source data and data on the medium&n;&t;&t;&t;&t;  do not agree */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Get sense key string or NULL if not available */
r_const
r_char
op_star
DECL|function|scsi_sense_key_string
id|scsi_sense_key_string
c_func
(paren
r_int
r_char
id|key
)paren
(brace
macro_line|#if (CONSTANTS &amp; CONST_SENSE)
r_if
c_cond
(paren
id|key
op_le
l_int|0xE
)paren
r_return
id|snstext
(braket
id|key
)braket
suffix:semicolon
macro_line|#endif
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Get extended sense key string or NULL if not available.&n; * This string may contain a %x and must be printed with ascq as arg.&n; */
r_const
r_char
op_star
DECL|function|scsi_extd_sense_format
id|scsi_extd_sense_format
c_func
(paren
r_int
r_char
id|asc
comma
r_int
r_char
id|ascq
)paren
(brace
macro_line|#if (CONSTANTS &amp; CONST_XSENSE)
r_int
id|i
suffix:semicolon
r_int
r_int
id|code
op_assign
(paren
(paren
id|asc
op_lshift
l_int|8
)paren
op_or
id|ascq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|additional
(braket
id|i
)braket
dot
id|text
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|additional
(braket
id|i
)braket
dot
id|code12
op_eq
id|code
)paren
r_return
id|additional
(braket
id|i
)braket
dot
id|text
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|additional2
(braket
id|i
)braket
dot
id|fmt
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|additional2
(braket
id|i
)braket
dot
id|code1
op_eq
id|asc
op_logical_and
id|additional2
(braket
id|i
)braket
dot
id|code2_min
op_ge
id|ascq
op_logical_and
id|additional2
(braket
id|i
)braket
dot
id|code2_max
op_le
id|ascq
)paren
r_return
id|additional2
(braket
id|i
)braket
dot
id|fmt
suffix:semicolon
macro_line|#endif
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Print extended sense information */
r_static
r_void
DECL|function|scsi_show_extd_sense
id|scsi_show_extd_sense
c_func
(paren
r_int
r_char
id|asc
comma
r_int
r_char
id|ascq
)paren
(brace
r_const
r_char
op_star
id|extd_sense_fmt
op_assign
id|scsi_extd_sense_format
c_func
(paren
id|asc
comma
id|ascq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|extd_sense_fmt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Additional sense: &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|extd_sense_fmt
comma
id|ascq
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;ASC=%2x ASCQ=%2x&bslash;n&quot;
comma
id|asc
comma
id|ascq
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Print sense information */
r_static
r_void
DECL|function|print_sense_internal
id|print_sense_internal
c_func
(paren
r_const
r_char
op_star
id|devclass
comma
r_const
r_int
r_char
op_star
id|sense_buffer
comma
id|kdev_t
id|dev
)paren
(brace
r_int
id|s
comma
id|sense_class
comma
id|valid
comma
id|code
comma
id|info
suffix:semicolon
r_const
r_char
op_star
id|error
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|asc
comma
id|ascq
suffix:semicolon
r_const
r_char
op_star
id|sense_txt
suffix:semicolon
id|sense_class
op_assign
(paren
id|sense_buffer
(braket
l_int|0
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0x07
suffix:semicolon
id|code
op_assign
id|sense_buffer
(braket
l_int|0
)braket
op_amp
l_int|0xf
suffix:semicolon
id|valid
op_assign
id|sense_buffer
(braket
l_int|0
)braket
op_amp
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
id|sense_class
op_eq
l_int|7
)paren
(brace
multiline_comment|/* extended sense data */
id|s
op_assign
id|sense_buffer
(braket
l_int|7
)braket
op_plus
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|s
OG
id|SCSI_SENSE_BUFFERSIZE
)paren
id|s
op_assign
id|SCSI_SENSE_BUFFERSIZE
suffix:semicolon
id|info
op_assign
(paren
(paren
id|sense_buffer
(braket
l_int|3
)braket
op_lshift
l_int|24
)paren
op_or
(paren
id|sense_buffer
(braket
l_int|4
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|sense_buffer
(braket
l_int|5
)braket
op_lshift
l_int|8
)paren
op_or
id|sense_buffer
(braket
l_int|6
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_logical_or
id|valid
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Info fld=0x%x&quot;
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|valid
)paren
multiline_comment|/* info data not according to standard */
id|printk
c_func
(paren
l_string|&quot; (nonstd)&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, &quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0x80
)paren
id|printk
c_func
(paren
l_string|&quot;FMK &quot;
)paren
suffix:semicolon
multiline_comment|/* current command has read a filemark */
r_if
c_cond
(paren
id|sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0x40
)paren
id|printk
c_func
(paren
l_string|&quot;EOM &quot;
)paren
suffix:semicolon
multiline_comment|/* end-of-medium condition exists */
r_if
c_cond
(paren
id|sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0x20
)paren
id|printk
c_func
(paren
l_string|&quot;ILI &quot;
)paren
suffix:semicolon
multiline_comment|/* incorrect block length requested */
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
l_int|0x0
suffix:colon
id|error
op_assign
l_string|&quot;Current&quot;
suffix:semicolon
multiline_comment|/* error concerns current command */
r_break
suffix:semicolon
r_case
l_int|0x1
suffix:colon
id|error
op_assign
l_string|&quot;Deferred&quot;
suffix:semicolon
multiline_comment|/* error concerns some earlier command */
multiline_comment|/* e.g., an earlier write to disk cache succeeded, but&n;&t;&t;&t;   now the disk discovers that it cannot write the data */
r_break
suffix:semicolon
r_default
suffix:colon
id|error
op_assign
l_string|&quot;Invalid&quot;
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s &quot;
comma
id|error
)paren
suffix:semicolon
id|sense_txt
op_assign
id|scsi_sense_key_string
c_func
(paren
id|sense_buffer
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sense_txt
)paren
id|printk
c_func
(paren
l_string|&quot;%s%s: sense key %s&bslash;n&quot;
comma
id|devclass
comma
id|kdevname
c_func
(paren
id|dev
)paren
comma
id|sense_txt
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;%s%s: sense = %2x %2x&bslash;n&quot;
comma
id|devclass
comma
id|kdevname
c_func
(paren
id|dev
)paren
comma
id|sense_buffer
(braket
l_int|0
)braket
comma
id|sense_buffer
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|asc
op_assign
id|ascq
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sense_buffer
(braket
l_int|7
)braket
op_plus
l_int|7
op_ge
l_int|13
)paren
(brace
id|asc
op_assign
id|sense_buffer
(braket
l_int|12
)braket
suffix:semicolon
id|ascq
op_assign
id|sense_buffer
(braket
l_int|13
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|asc
op_logical_or
id|ascq
)paren
id|scsi_show_extd_sense
c_func
(paren
id|asc
comma
id|ascq
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* non-extended sense data */
multiline_comment|/*&n;&t;&t; * Standard says:&n;&t;&t; *    sense_buffer[0] &amp; 0200 : address valid&n;&t;&t; *    sense_buffer[0] &amp; 0177 : vendor-specific error code&n;&t;&t; *    sense_buffer[1] &amp; 0340 : vendor-specific&n;&t;&t; *    sense_buffer[1..3] : 21-bit logical block address&n;&t;&t; */
id|sense_txt
op_assign
id|scsi_sense_key_string
c_func
(paren
id|sense_buffer
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sense_txt
)paren
id|printk
c_func
(paren
l_string|&quot;%s%s: old sense key %s&bslash;n&quot;
comma
id|devclass
comma
id|kdevname
c_func
(paren
id|dev
)paren
comma
id|sense_txt
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;%s%s: sense = %2x %2x&bslash;n&quot;
comma
id|devclass
comma
id|kdevname
c_func
(paren
id|dev
)paren
comma
id|sense_buffer
(braket
l_int|0
)braket
comma
id|sense_buffer
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Non-extended sense class %d code 0x%0x&bslash;n&quot;
comma
id|sense_class
comma
id|code
)paren
suffix:semicolon
id|s
op_assign
l_int|4
suffix:semicolon
)brace
macro_line|#if !(CONSTANTS &amp; CONST_SENSE)
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Raw sense data:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|s
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot;0x%02x &quot;
comma
id|sense_buffer
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|print_sense
r_void
id|print_sense
c_func
(paren
r_const
r_char
op_star
id|devclass
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|print_sense_internal
c_func
(paren
id|devclass
comma
id|SCpnt-&gt;sense_buffer
comma
id|SCpnt-&gt;request.rq_dev
)paren
suffix:semicolon
)brace
DECL|function|print_req_sense
r_void
id|print_req_sense
c_func
(paren
r_const
r_char
op_star
id|devclass
comma
id|Scsi_Request
op_star
id|SRpnt
)paren
(brace
id|print_sense_internal
c_func
(paren
id|devclass
comma
id|SRpnt-&gt;sr_sense_buffer
comma
id|SRpnt-&gt;sr_request.rq_dev
)paren
suffix:semicolon
)brace
macro_line|#if (CONSTANTS &amp; CONST_MSG) 
DECL|variable|one_byte_msgs
r_static
r_const
r_char
op_star
id|one_byte_msgs
(braket
)braket
op_assign
(brace
multiline_comment|/* 0x00 */
l_string|&quot;Command Complete&quot;
comma
l_int|NULL
comma
l_string|&quot;Save Pointers&quot;
comma
multiline_comment|/* 0x03 */
l_string|&quot;Restore Pointers&quot;
comma
l_string|&quot;Disconnect&quot;
comma
l_string|&quot;Initiator Error&quot;
comma
multiline_comment|/* 0x06 */
l_string|&quot;Abort&quot;
comma
l_string|&quot;Message Reject&quot;
comma
l_string|&quot;Nop&quot;
comma
l_string|&quot;Message Parity Error&quot;
comma
multiline_comment|/* 0x0a */
l_string|&quot;Linked Command Complete&quot;
comma
l_string|&quot;Linked Command Complete w/flag&quot;
comma
multiline_comment|/* 0x0c */
l_string|&quot;Bus device reset&quot;
comma
l_string|&quot;Abort Tag&quot;
comma
l_string|&quot;Clear Queue&quot;
comma
multiline_comment|/* 0x0f */
l_string|&quot;Initiate Recovery&quot;
comma
l_string|&quot;Release Recovery&quot;
)brace
suffix:semicolon
DECL|macro|NO_ONE_BYTE_MSGS
mdefine_line|#define NO_ONE_BYTE_MSGS (sizeof(one_byte_msgs)  / sizeof (const char *))
DECL|variable|two_byte_msgs
r_static
r_const
r_char
op_star
id|two_byte_msgs
(braket
)braket
op_assign
(brace
multiline_comment|/* 0x20 */
l_string|&quot;Simple Queue Tag&quot;
comma
l_string|&quot;Head of Queue Tag&quot;
comma
l_string|&quot;Ordered Queue Tag&quot;
multiline_comment|/* 0x23 */
l_string|&quot;Ignore Wide Residue&quot;
)brace
suffix:semicolon
DECL|macro|NO_TWO_BYTE_MSGS
mdefine_line|#define NO_TWO_BYTE_MSGS (sizeof(two_byte_msgs)  / sizeof (const char *))
DECL|variable|extended_msgs
r_static
r_const
r_char
op_star
id|extended_msgs
(braket
)braket
op_assign
(brace
multiline_comment|/* 0x00 */
l_string|&quot;Modify Data Pointer&quot;
comma
l_string|&quot;Synchronous Data Transfer Request&quot;
comma
multiline_comment|/* 0x02 */
l_string|&quot;SCSI-I Extended Identify&quot;
comma
l_string|&quot;Wide Data Transfer Request&quot;
)brace
suffix:semicolon
DECL|macro|NO_EXTENDED_MSGS
mdefine_line|#define NO_EXTENDED_MSGS (sizeof(two_byte_msgs)  / sizeof (const char *))
macro_line|#endif /* (CONSTANTS &amp; CONST_MSG) */
DECL|function|print_msg
r_int
id|print_msg
(paren
r_const
r_int
r_char
op_star
id|msg
)paren
(brace
r_int
id|len
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|msg
(braket
l_int|0
)braket
op_eq
id|EXTENDED_MESSAGE
)paren
(brace
id|len
op_assign
l_int|3
op_plus
id|msg
(braket
l_int|1
)braket
suffix:semicolon
macro_line|#if (CONSTANTS &amp; CONST_MSG)
r_if
c_cond
(paren
id|msg
(braket
l_int|2
)braket
OL
id|NO_EXTENDED_MSGS
)paren
id|printk
(paren
l_string|&quot;%s &quot;
comma
id|extended_msgs
(braket
id|msg
(braket
l_int|2
)braket
)braket
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot;Extended Message, reserved code (0x%02x) &quot;
comma
(paren
r_int
)paren
id|msg
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|msg
(braket
l_int|2
)braket
)paren
(brace
r_case
id|EXTENDED_MODIFY_DATA_POINTER
suffix:colon
id|printk
c_func
(paren
l_string|&quot;pointer = %d&quot;
comma
(paren
r_int
)paren
(paren
id|msg
(braket
l_int|3
)braket
op_lshift
l_int|24
)paren
op_or
(paren
id|msg
(braket
l_int|4
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|msg
(braket
l_int|5
)braket
op_lshift
l_int|8
)paren
op_or
id|msg
(braket
l_int|6
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EXTENDED_SDTR
suffix:colon
id|printk
c_func
(paren
l_string|&quot;period = %d ns, offset = %d&quot;
comma
(paren
r_int
)paren
id|msg
(braket
l_int|3
)braket
op_star
l_int|4
comma
(paren
r_int
)paren
id|msg
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EXTENDED_WDTR
suffix:colon
id|printk
c_func
(paren
l_string|&quot;width = 2^%d bytes&quot;
comma
id|msg
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|msg
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|msg
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Identify */
)brace
r_else
r_if
c_cond
(paren
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x80
)paren
(brace
macro_line|#if (CONSTANTS &amp; CONST_MSG)
id|printk
c_func
(paren
l_string|&quot;Identify disconnect %sallowed %s %d &quot;
comma
(paren
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;not &quot;
comma
(paren
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;target routine&quot;
suffix:colon
l_string|&quot;lun&quot;
comma
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x7
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|msg
(braket
l_int|0
)braket
)paren
suffix:semicolon
macro_line|#endif
id|len
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Normal One byte */
)brace
r_else
r_if
c_cond
(paren
id|msg
(braket
l_int|0
)braket
OL
l_int|0x1f
)paren
(brace
macro_line|#if (CONSTANTS &amp; CONST_MSG)
r_if
c_cond
(paren
id|msg
(braket
l_int|0
)braket
OL
id|NO_ONE_BYTE_MSGS
)paren
id|printk
c_func
(paren
id|one_byte_msgs
(braket
id|msg
(braket
l_int|0
)braket
)braket
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;reserved (%02x) &quot;
comma
id|msg
(braket
l_int|0
)braket
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|msg
(braket
l_int|0
)braket
)paren
suffix:semicolon
macro_line|#endif
id|len
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Two byte */
)brace
r_else
r_if
c_cond
(paren
id|msg
(braket
l_int|0
)braket
op_le
l_int|0x2f
)paren
(brace
macro_line|#if (CONSTANTS &amp; CONST_MSG)
r_if
c_cond
(paren
(paren
id|msg
(braket
l_int|0
)braket
op_minus
l_int|0x20
)paren
OL
id|NO_TWO_BYTE_MSGS
)paren
id|printk
c_func
(paren
l_string|&quot;%s %02x &quot;
comma
id|two_byte_msgs
(braket
id|msg
(braket
l_int|0
)braket
op_minus
l_int|0x20
)braket
comma
id|msg
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;reserved two byte (%02x %02x) &quot;
comma
id|msg
(braket
l_int|0
)braket
comma
id|msg
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;%02x %02x&quot;
comma
id|msg
(braket
l_int|0
)braket
comma
id|msg
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
id|len
op_assign
l_int|2
suffix:semicolon
)brace
r_else
macro_line|#if (CONSTANTS &amp; CONST_MSG)
id|printk
c_func
(paren
id|reserved
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|msg
(braket
l_int|0
)braket
)paren
suffix:semicolon
macro_line|#endif
r_return
id|len
suffix:semicolon
)brace
DECL|function|print_Scsi_Cmnd
r_void
id|print_Scsi_Cmnd
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d : destination target %d, lun %d&bslash;n&quot;
comma
id|cmd-&gt;host-&gt;host_no
comma
id|cmd-&gt;target
comma
id|cmd-&gt;lun
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;        command = &quot;
)paren
suffix:semicolon
id|print_command
(paren
id|cmd-&gt;cmnd
)paren
suffix:semicolon
)brace
macro_line|#if (CONSTANTS &amp; CONST_HOST)
DECL|variable|hostbyte_table
r_static
r_const
r_char
op_star
id|hostbyte_table
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|print_hostbyte
r_void
id|print_hostbyte
c_func
(paren
r_int
id|scsiresult
)paren
(brace
r_static
r_int
id|maxcode
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|maxcode
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|hostbyte_table
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
suffix:semicolon
)brace
id|maxcode
op_assign
id|i
op_minus
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Hostbyte=0x%02x&quot;
comma
id|host_byte
c_func
(paren
id|scsiresult
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host_byte
c_func
(paren
id|scsiresult
)paren
OG
id|maxcode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;is invalid &quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;(%s) &quot;
comma
id|hostbyte_table
(braket
id|host_byte
c_func
(paren
id|scsiresult
)paren
)braket
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|print_hostbyte
r_void
id|print_hostbyte
c_func
(paren
r_int
id|scsiresult
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Hostbyte=0x%02x &quot;
comma
id|host_byte
c_func
(paren
id|scsiresult
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if (CONSTANTS &amp; CONST_DRIVER)
DECL|variable|driverbyte_table
r_static
r_const
r_char
op_star
id|driverbyte_table
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|driversuggest_table
r_static
r_const
r_char
op_star
id|driversuggest_table
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|print_driverbyte
r_void
id|print_driverbyte
c_func
(paren
r_int
id|scsiresult
)paren
(brace
r_static
r_int
id|driver_max
op_assign
l_int|0
comma
id|suggest_max
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|dr
op_assign
id|driver_byte
c_func
(paren
id|scsiresult
)paren
op_amp
id|DRIVER_MASK
comma
id|su
op_assign
(paren
id|driver_byte
c_func
(paren
id|scsiresult
)paren
op_amp
id|SUGGEST_MASK
)paren
op_rshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|driver_max
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|driverbyte_table
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
suffix:semicolon
)brace
id|driver_max
op_assign
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|driversuggest_table
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
suffix:semicolon
)brace
id|suggest_max
op_assign
id|i
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Driverbyte=0x%02x&quot;
comma
id|driver_byte
c_func
(paren
id|scsiresult
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(%s,%s) &quot;
comma
id|dr
OL
id|driver_max
ques
c_cond
id|driverbyte_table
(braket
id|dr
)braket
suffix:colon
l_string|&quot;invalid&quot;
comma
id|su
OL
id|suggest_max
ques
c_cond
id|driversuggest_table
(braket
id|su
)braket
suffix:colon
l_string|&quot;invalid&quot;
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|print_driverbyte
r_void
id|print_driverbyte
c_func
(paren
r_int
id|scsiresult
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Driverbyte=0x%02x &quot;
comma
id|driver_byte
c_func
(paren
id|scsiresult
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
