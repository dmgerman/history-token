macro_line|#ifndef _QIC117_H
DECL|macro|_QIC117_H
mdefine_line|#define _QIC117_H
multiline_comment|/*&n; *      Copyright (C) 1993-1996 Bas Laarhoven,&n; *                (C) 1997      Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/include/linux/qic117.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:19:32 $&n; *&n; *      This file contains QIC-117 spec. related definitions for the&n; *      QIC-40/80/3010/3020 floppy-tape driver &quot;ftape&quot; for Linux.&n; *&n; *      These data were taken from the Quarter-Inch Cartridge&n; *      Drive Standards, Inc. document titled:&n; *      `Common Command Set Interface Specification for Flexible&n; *       Disk Controller Based Minicartridge Tape Drives&squot;&n; *       document QIC-117 Revision J, 28 Aug 96.&n; *      For more information, contact:&n; *       Quarter-Inch Cartridge Drive Standards, Inc.&n; *       311 East Carrillo Street&n; *       Santa Barbara, California 93101&n; *       Telephone (805) 963-3853&n; *       Fax       (805) 962-1541&n; *       WWW       http://www.qic.org&n; *&n; *      Current QIC standard revisions (of interest) are:&n; *       QIC-40-MC,   Rev. M,  2 Sep 92.&n; *       QIC-80-MC,   Rev. N, 20 Mar 96.&n; *       QIC-80-MC,   Rev. K, 15 Dec 94.&n; *       QIC-113,     Rev. G, 15 Jun 95.&n; *       QIC-117,     Rev. J, 28 Aug 96.&n; *       QIC-122,     Rev. B,  6 Mar 91.&n; *       QIC-130,     Rev. C,  2 Sep 92.&n; *       QIC-3010-MC, Rev. F, 14 Jun 95.&n; *       QIC-3020-MC, Rev. G, 31 Aug 95.&n; *       QIC-CRF3,    Rev. B, 15 Jun 95.&n; * */
multiline_comment|/*&n; *      QIC-117 common command set rev. J.&n; *      These commands are sent to the tape unit&n; *      as number of pulses over the step line.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|QIC_NO_COMMAND
id|QIC_NO_COMMAND
op_assign
l_int|0
comma
DECL|enumerator|QIC_RESET
id|QIC_RESET
op_assign
l_int|1
comma
DECL|enumerator|QIC_REPORT_NEXT_BIT
id|QIC_REPORT_NEXT_BIT
op_assign
l_int|2
comma
DECL|enumerator|QIC_PAUSE
id|QIC_PAUSE
op_assign
l_int|3
comma
DECL|enumerator|QIC_MICRO_STEP_PAUSE
id|QIC_MICRO_STEP_PAUSE
op_assign
l_int|4
comma
DECL|enumerator|QIC_ALTERNATE_TIMEOUT
id|QIC_ALTERNATE_TIMEOUT
op_assign
l_int|5
comma
DECL|enumerator|QIC_REPORT_DRIVE_STATUS
id|QIC_REPORT_DRIVE_STATUS
op_assign
l_int|6
comma
DECL|enumerator|QIC_REPORT_ERROR_CODE
id|QIC_REPORT_ERROR_CODE
op_assign
l_int|7
comma
DECL|enumerator|QIC_REPORT_DRIVE_CONFIGURATION
id|QIC_REPORT_DRIVE_CONFIGURATION
op_assign
l_int|8
comma
DECL|enumerator|QIC_REPORT_ROM_VERSION
id|QIC_REPORT_ROM_VERSION
op_assign
l_int|9
comma
DECL|enumerator|QIC_LOGICAL_FORWARD
id|QIC_LOGICAL_FORWARD
op_assign
l_int|10
comma
DECL|enumerator|QIC_PHYSICAL_REVERSE
id|QIC_PHYSICAL_REVERSE
op_assign
l_int|11
comma
DECL|enumerator|QIC_PHYSICAL_FORWARD
id|QIC_PHYSICAL_FORWARD
op_assign
l_int|12
comma
DECL|enumerator|QIC_SEEK_HEAD_TO_TRACK
id|QIC_SEEK_HEAD_TO_TRACK
op_assign
l_int|13
comma
DECL|enumerator|QIC_SEEK_LOAD_POINT
id|QIC_SEEK_LOAD_POINT
op_assign
l_int|14
comma
DECL|enumerator|QIC_ENTER_FORMAT_MODE
id|QIC_ENTER_FORMAT_MODE
op_assign
l_int|15
comma
DECL|enumerator|QIC_WRITE_REFERENCE_BURST
id|QIC_WRITE_REFERENCE_BURST
op_assign
l_int|16
comma
DECL|enumerator|QIC_ENTER_VERIFY_MODE
id|QIC_ENTER_VERIFY_MODE
op_assign
l_int|17
comma
DECL|enumerator|QIC_STOP_TAPE
id|QIC_STOP_TAPE
op_assign
l_int|18
comma
multiline_comment|/* commands 19-20: reserved */
DECL|enumerator|QIC_MICRO_STEP_HEAD_UP
id|QIC_MICRO_STEP_HEAD_UP
op_assign
l_int|21
comma
DECL|enumerator|QIC_MICRO_STEP_HEAD_DOWN
id|QIC_MICRO_STEP_HEAD_DOWN
op_assign
l_int|22
comma
DECL|enumerator|QIC_SOFT_SELECT
id|QIC_SOFT_SELECT
op_assign
l_int|23
comma
DECL|enumerator|QIC_SOFT_DESELECT
id|QIC_SOFT_DESELECT
op_assign
l_int|24
comma
DECL|enumerator|QIC_SKIP_REVERSE
id|QIC_SKIP_REVERSE
op_assign
l_int|25
comma
DECL|enumerator|QIC_SKIP_FORWARD
id|QIC_SKIP_FORWARD
op_assign
l_int|26
comma
DECL|enumerator|QIC_SELECT_RATE
id|QIC_SELECT_RATE
op_assign
l_int|27
comma
multiline_comment|/* command 27, in ccs2: Select Rate or Format */
DECL|enumerator|QIC_ENTER_DIAGNOSTIC_1
id|QIC_ENTER_DIAGNOSTIC_1
op_assign
l_int|28
comma
DECL|enumerator|QIC_ENTER_DIAGNOSTIC_2
id|QIC_ENTER_DIAGNOSTIC_2
op_assign
l_int|29
comma
DECL|enumerator|QIC_ENTER_PRIMARY_MODE
id|QIC_ENTER_PRIMARY_MODE
op_assign
l_int|30
comma
multiline_comment|/* command 31: vendor unique */
DECL|enumerator|QIC_REPORT_VENDOR_ID
id|QIC_REPORT_VENDOR_ID
op_assign
l_int|32
comma
DECL|enumerator|QIC_REPORT_TAPE_STATUS
id|QIC_REPORT_TAPE_STATUS
op_assign
l_int|33
comma
DECL|enumerator|QIC_SKIP_EXTENDED_REVERSE
id|QIC_SKIP_EXTENDED_REVERSE
op_assign
l_int|34
comma
DECL|enumerator|QIC_SKIP_EXTENDED_FORWARD
id|QIC_SKIP_EXTENDED_FORWARD
op_assign
l_int|35
comma
DECL|enumerator|QIC_CALIBRATE_TAPE_LENGTH
id|QIC_CALIBRATE_TAPE_LENGTH
op_assign
l_int|36
comma
DECL|enumerator|QIC_REPORT_FORMAT_SEGMENTS
id|QIC_REPORT_FORMAT_SEGMENTS
op_assign
l_int|37
comma
DECL|enumerator|QIC_SET_FORMAT_SEGMENTS
id|QIC_SET_FORMAT_SEGMENTS
op_assign
l_int|38
comma
multiline_comment|/* commands 39-45: reserved */
DECL|enumerator|QIC_PHANTOM_SELECT
id|QIC_PHANTOM_SELECT
op_assign
l_int|46
comma
DECL|enumerator|QIC_PHANTOM_DESELECT
id|QIC_PHANTOM_DESELECT
op_assign
l_int|47
DECL|typedef|qic117_cmd_t
)brace
id|qic117_cmd_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|discretional
DECL|enumerator|required
DECL|enumerator|ccs1
DECL|enumerator|ccs2
id|discretional
op_assign
l_int|0
comma
id|required
comma
id|ccs1
comma
id|ccs2
DECL|typedef|qic_compatibility
)brace
id|qic_compatibility
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|unused
DECL|enumerator|mode
DECL|enumerator|motion
DECL|enumerator|report
id|unused
comma
id|mode
comma
id|motion
comma
id|report
DECL|typedef|command_types
)brace
id|command_types
suffix:semicolon
DECL|struct|qic117_command_table
r_struct
id|qic117_command_table
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|mask
id|__u8
id|mask
suffix:semicolon
DECL|member|state
id|__u8
id|state
suffix:semicolon
DECL|member|cmd_type
id|__u8
id|cmd_type
suffix:semicolon
DECL|member|non_intr
id|__u8
id|non_intr
suffix:semicolon
DECL|member|level
id|__u8
id|level
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|QIC117_COMMANDS
mdefine_line|#define QIC117_COMMANDS {&bslash;&n;/* command                           mask  state cmd_type           */&bslash;&n;/* |    name                         |     |     |       non_intr   */&bslash;&n;/* |    |                            |     |     |       |  level   */&bslash;&n;/* 0*/ {NULL,                        0x00, 0x00, mode,   0, discretional},&bslash;&n;/* 1*/ {&quot;soft reset&quot;,                0x00, 0x00, motion, 1, required},&bslash;&n;/* 2*/ {&quot;report next bit&quot;,           0x00, 0x00, report, 0, required},&bslash;&n;/* 3*/ {&quot;pause&quot;,                     0x36, 0x24, motion, 1, required},&bslash;&n;/* 4*/ {&quot;micro step pause&quot;,          0x36, 0x24, motion, 1, required},&bslash;&n;/* 5*/ {&quot;alternate command timeout&quot;, 0x00, 0x00, mode,   0, required},&bslash;&n;/* 6*/ {&quot;report drive status&quot;,       0x00, 0x00, report, 0, required},&bslash;&n;/* 7*/ {&quot;report error code&quot;,         0x01, 0x01, report, 0, required},&bslash;&n;/* 8*/ {&quot;report drive configuration&quot;,0x00, 0x00, report, 0, required},&bslash;&n;/* 9*/ {&quot;report rom version&quot;,        0x00, 0x00, report, 0, required},&bslash;&n;/*10*/ {&quot;logical forward&quot;,           0x37, 0x25, motion, 0, required},&bslash;&n;/*11*/ {&quot;physical reverse&quot;,          0x17, 0x05, motion, 0, required},&bslash;&n;/*12*/ {&quot;physical forward&quot;,          0x17, 0x05, motion, 0, required},&bslash;&n;/*13*/ {&quot;seek head to track&quot;,        0x37, 0x25, motion, 0, required},&bslash;&n;/*14*/ {&quot;seek load point&quot;,           0x17, 0x05, motion, 1, required},&bslash;&n;/*15*/ {&quot;enter format mode&quot;,         0x1f, 0x05, mode,   0, required},&bslash;&n;/*16*/ {&quot;write reference burst&quot;,     0x1f, 0x05, motion, 1, required},&bslash;&n;/*17*/ {&quot;enter verify mode&quot;,         0x37, 0x25, mode,   0, required},&bslash;&n;/*18*/ {&quot;stop tape&quot;,                 0x00, 0x00, motion, 1, required},&bslash;&n;/*19*/ {&quot;reserved (19)&quot;,             0x00, 0x00, unused, 0, discretional},&bslash;&n;/*20*/ {&quot;reserved (20)&quot;,             0x00, 0x00, unused, 0, discretional},&bslash;&n;/*21*/ {&quot;micro step head up&quot;,        0x02, 0x00, motion, 0, required},&bslash;&n;/*22*/ {&quot;micro step head down&quot;,      0x02, 0x00, motion, 0, required},&bslash;&n;/*23*/ {&quot;soft select&quot;,               0x00, 0x00, mode,   0, discretional},&bslash;&n;/*24*/ {&quot;soft deselect&quot;,             0x00, 0x00, mode,   0, discretional},&bslash;&n;/*25*/ {&quot;skip segments reverse&quot;,     0x36, 0x24, motion, 1, required},&bslash;&n;/*26*/ {&quot;skip segments forward&quot;,     0x36, 0x24, motion, 1, required},&bslash;&n;/*27*/ {&quot;select rate or format&quot;,     0x03, 0x01, mode,   0, required /* [ccs2] */},&bslash;&n;/*28*/ {&quot;enter diag mode 1&quot;,         0x00, 0x00, mode,   0, discretional},&bslash;&n;/*29*/ {&quot;enter diag mode 2&quot;,         0x00, 0x00, mode,   0, discretional},&bslash;&n;/*30*/ {&quot;enter primary mode&quot;,        0x00, 0x00, mode,   0, required},&bslash;&n;/*31*/ {&quot;vendor unique (31)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*32*/ {&quot;report vendor id&quot;,          0x00, 0x00, report, 0, required},&bslash;&n;/*33*/ {&quot;report tape status&quot;,        0x04, 0x04, report, 0, ccs1},&bslash;&n;/*34*/ {&quot;skip extended reverse&quot;,     0x36, 0x24, motion, 1, ccs1},&bslash;&n;/*35*/ {&quot;skip extended forward&quot;,     0x36, 0x24, motion, 1, ccs1},&bslash;&n;/*36*/ {&quot;calibrate tape length&quot;,     0x17, 0x05, motion, 1, ccs2},&bslash;&n;/*37*/ {&quot;report format segments&quot;,    0x17, 0x05, report, 0, ccs2},&bslash;&n;/*38*/ {&quot;set format segments&quot;,       0x17, 0x05, mode,   0, ccs2},&bslash;&n;/*39*/ {&quot;reserved (39)&quot;,             0x00, 0x00, unused, 0, discretional},&bslash;&n;/*40*/ {&quot;vendor unique (40)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*41*/ {&quot;vendor unique (41)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*42*/ {&quot;vendor unique (42)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*43*/ {&quot;vendor unique (43)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*44*/ {&quot;vendor unique (44)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*45*/ {&quot;vendor unique (45)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*46*/ {&quot;phantom select&quot;,            0x00, 0x00, mode,   0, discretional},&bslash;&n;/*47*/ {&quot;phantom deselect&quot;,          0x00, 0x00, mode,   0, discretional},&bslash;&n;}
multiline_comment|/*&n; *      Status bits returned by QIC_REPORT_DRIVE_STATUS&n; */
DECL|macro|QIC_STATUS_READY
mdefine_line|#define QIC_STATUS_READY&t;0x01&t;/* Drive is ready or idle. */
DECL|macro|QIC_STATUS_ERROR
mdefine_line|#define QIC_STATUS_ERROR&t;0x02&t;/* Error detected, must read&n;&t;&t;&t;&t;&t;   error code to clear this */
DECL|macro|QIC_STATUS_CARTRIDGE_PRESENT
mdefine_line|#define QIC_STATUS_CARTRIDGE_PRESENT 0x04&t;/* Tape is present */
DECL|macro|QIC_STATUS_WRITE_PROTECT
mdefine_line|#define QIC_STATUS_WRITE_PROTECT 0x08&t;/* Tape is write protected */
DECL|macro|QIC_STATUS_NEW_CARTRIDGE
mdefine_line|#define QIC_STATUS_NEW_CARTRIDGE 0x10&t;/* New cartridge inserted, must&n;&t;&t;&t;&t;&t;   read error status to clear. */
DECL|macro|QIC_STATUS_REFERENCED
mdefine_line|#define QIC_STATUS_REFERENCED&t;0x20&t;/* Cartridge appears to have been&n;&t;&t;&t;&t;&t;   formatted. */
DECL|macro|QIC_STATUS_AT_BOT
mdefine_line|#define QIC_STATUS_AT_BOT&t;0x40&t;/* Cartridge is at physical&n;&t;&t;&t;&t;&t;   beginning of tape. */
DECL|macro|QIC_STATUS_AT_EOT
mdefine_line|#define QIC_STATUS_AT_EOT&t;0x80&t;/* Cartridge is at physical end&n;&t;&t;&t;&t;&t;   of tape. */
multiline_comment|/*&n; *      Status bits returned by QIC_REPORT_DRIVE_CONFIGURATION&n; */
DECL|macro|QIC_CONFIG_RATE_MASK
mdefine_line|#define QIC_CONFIG_RATE_MASK&t;0x18
DECL|macro|QIC_CONFIG_RATE_SHIFT
mdefine_line|#define QIC_CONFIG_RATE_SHIFT&t;3
DECL|macro|QIC_CONFIG_RATE_250
mdefine_line|#define QIC_CONFIG_RATE_250&t;0
DECL|macro|QIC_CONFIG_RATE_500
mdefine_line|#define QIC_CONFIG_RATE_500&t;2
DECL|macro|QIC_CONFIG_RATE_1000
mdefine_line|#define QIC_CONFIG_RATE_1000&t;3
DECL|macro|QIC_CONFIG_RATE_2000
mdefine_line|#define QIC_CONFIG_RATE_2000&t;1
DECL|macro|QIC_CONFIG_RATE_4000
mdefine_line|#define QIC_CONFIG_RATE_4000    0       /* since QIC-117 Rev. J */
DECL|macro|QIC_CONFIG_LONG
mdefine_line|#define QIC_CONFIG_LONG&t;&t;0x40&t;/* Extra Length Tape Detected */
DECL|macro|QIC_CONFIG_80
mdefine_line|#define QIC_CONFIG_80&t;&t;0x80&t;/* QIC-80 detected. */
multiline_comment|/*&n; *      Status bits returned by QIC_REPORT_TAPE_STATUS&n; */
DECL|macro|QIC_TAPE_STD_MASK
mdefine_line|#define QIC_TAPE_STD_MASK       0x0f
DECL|macro|QIC_TAPE_QIC40
mdefine_line|#define QIC_TAPE_QIC40  &t;0x01
DECL|macro|QIC_TAPE_QIC80
mdefine_line|#define QIC_TAPE_QIC80  &t;0x02
DECL|macro|QIC_TAPE_QIC3020
mdefine_line|#define QIC_TAPE_QIC3020  &t;0x03
DECL|macro|QIC_TAPE_QIC3010
mdefine_line|#define QIC_TAPE_QIC3010  &t;0x04
DECL|macro|QIC_TAPE_LEN_MASK
mdefine_line|#define QIC_TAPE_LEN_MASK&t;0x70
DECL|macro|QIC_TAPE_205FT
mdefine_line|#define QIC_TAPE_205FT&t;&t;0x10
DECL|macro|QIC_TAPE_307FT
mdefine_line|#define QIC_TAPE_307FT&t;&t;0x20
DECL|macro|QIC_TAPE_VARIABLE
mdefine_line|#define QIC_TAPE_VARIABLE&t;0x30
DECL|macro|QIC_TAPE_1100FT
mdefine_line|#define QIC_TAPE_1100FT&t;&t;0x40
DECL|macro|QIC_TAPE_FLEX
mdefine_line|#define QIC_TAPE_FLEX&t;&t;0x60
DECL|macro|QIC_TAPE_WIDE
mdefine_line|#define QIC_TAPE_WIDE&t;&t;0x80
multiline_comment|/* Define a value (in feet) slightly higher than &n; * the possible maximum tape length.&n; */
DECL|macro|QIC_TOP_TAPE_LEN
mdefine_line|#define QIC_TOP_TAPE_LEN&t;1500
multiline_comment|/*&n; *      Errors: List of error codes, and their severity.&n; */
r_typedef
r_struct
(brace
DECL|member|message
r_char
op_star
id|message
suffix:semicolon
multiline_comment|/* Text describing the error. */
DECL|member|fatal
r_int
r_int
id|fatal
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Non-zero if the error is fatal. */
DECL|typedef|ftape_error
)brace
id|ftape_error
suffix:semicolon
DECL|macro|QIC117_ERRORS
mdefine_line|#define QIC117_ERRORS {&bslash;&n;  /* 0*/ { &quot;No error&quot;, 0, },&bslash;&n;  /* 1*/ { &quot;Command Received while Drive Not Ready&quot;, 0, },&bslash;&n;  /* 2*/ { &quot;Cartridge Not Present or Removed&quot;, 1, },&bslash;&n;  /* 3*/ { &quot;Motor Speed Error (not within 1%)&quot;, 1, },&bslash;&n;  /* 4*/ { &quot;Motor Speed Fault (jammed, or gross speed error&quot;, 1, },&bslash;&n;  /* 5*/ { &quot;Cartridge Write Protected&quot;, 1, },&bslash;&n;  /* 6*/ { &quot;Undefined or Reserved Command Code&quot;, 1, },&bslash;&n;  /* 7*/ { &quot;Illegal Track Address Specified for Seek&quot;, 1, },&bslash;&n;  /* 8*/ { &quot;Illegal Command in Report Subcontext&quot;, 0, },&bslash;&n;  /* 9*/ { &quot;Illegal Entry into a Diagnostic Mode&quot;, 1, },&bslash;&n;  /*10*/ { &quot;Broken Tape Detected (based on hole sensor)&quot;, 1, },&bslash;&n;  /*11*/ { &quot;Warning--Read Gain Setting Error&quot;, 1, },&bslash;&n;  /*12*/ { &quot;Command Received While Error Status Pending (obs)&quot;, 1, },&bslash;&n;  /*13*/ { &quot;Command Received While New Cartridge Pending&quot;, 1, },&bslash;&n;  /*14*/ { &quot;Command Illegal or Undefined in Primary Mode&quot;, 1, },&bslash;&n;  /*15*/ { &quot;Command Illegal or Undefined in Format Mode&quot;, 1, },&bslash;&n;  /*16*/ { &quot;Command Illegal or Undefined in Verify Mode&quot;, 1, },&bslash;&n;  /*17*/ { &quot;Logical Forward Not at Logical BOT or no Format Segments in Format Mode&quot;, 1, },&bslash;&n;  /*18*/ { &quot;Logical EOT Before All Segments generated&quot;, 1, },&bslash;&n;  /*19*/ { &quot;Command Illegal When Cartridge Not Referenced&quot;, 1, },&bslash;&n;  /*20*/ { &quot;Self-Diagnostic Failed (cannot be cleared)&quot;, 1, },&bslash;&n;  /*21*/ { &quot;Warning EEPROM Not Initialized, Defaults Set&quot;, 1, },&bslash;&n;  /*22*/ { &quot;EEPROM Corrupted or Hardware Failure&quot;, 1, },&bslash;&n;  /*23*/ { &quot;Motion Time-out Error&quot;, 1, },&bslash;&n;  /*24*/ { &quot;Data Segment Too Long -- Logical Forward or Pause&quot;, 1, },&bslash;&n;  /*25*/ { &quot;Transmit Overrun (obs)&quot;, 1, },&bslash;&n;  /*26*/ { &quot;Power On Reset Occurred&quot;, 0, },&bslash;&n;  /*27*/ { &quot;Software Reset Occurred&quot;, 0, },&bslash;&n;  /*28*/ { &quot;Diagnostic Mode 1 Error&quot;, 1, },&bslash;&n;  /*29*/ { &quot;Diagnostic Mode 2 Error&quot;, 1, },&bslash;&n;  /*30*/ { &quot;Command Received During Non-Interruptible Process&quot;, 1, },&bslash;&n;  /*31*/ { &quot;Rate or Format Selection Error&quot;, 1, },&bslash;&n;  /*32*/ { &quot;Illegal Command While in High Speed Mode&quot;, 1, },&bslash;&n;  /*33*/ { &quot;Illegal Seek Segment Value&quot;, 1, },&bslash;&n;  /*34*/ { &quot;Invalid Media&quot;, 1, },&bslash;&n;  /*35*/ { &quot;Head Positioning Failure&quot;, 1, },&bslash;&n;  /*36*/ { &quot;Write Reference Burst Failure&quot;, 1, },&bslash;&n;  /*37*/ { &quot;Prom Code Missing&quot;, 1, },&bslash;&n;  /*38*/ { &quot;Invalid Format&quot;, 1, },&bslash;&n;  /*39*/ { &quot;EOT/BOT System Failure&quot;, 1, },&bslash;&n;  /*40*/ { &quot;Prom A Checksum Error&quot;, 1, },&bslash;&n;  /*41*/ { &quot;Drive Wakeup Reset Occurred&quot;, 1, },&bslash;&n;  /*42*/ { &quot;Prom B Checksum Error&quot;, 1, },&bslash;&n;  /*43*/ { &quot;Illegal Entry into Format Mode&quot;, 1, },&bslash;&n;}
macro_line|#endif&t;&t;&t;&t;/* _QIC117_H */
eof
