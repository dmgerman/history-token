multiline_comment|/*&n; * Implementation of Utility functions for all SCSI device types.&n; *&n; * Copyright (c) 1997, 1998, 1999 Justin T. Gibbs.&n; * Copyright (c) 1997, 1998 Kenneth D. Merry.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification, immediately at the beginning of the file.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; * $FreeBSD: src/sys/cam/scsi/scsi_all.c,v 1.38 2002/09/23 04:56:35 mjacob Exp $&n; * $Id$&n; */
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/version.h&gt;
multiline_comment|/* Core SCSI definitions */
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;aiclib.h&quot;
macro_line|#include &quot;cam.h&quot;
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE   0
macro_line|#endif /* FALSE */
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE    1
macro_line|#endif /* TRUE */
macro_line|#ifndef ERESTART
DECL|macro|ERESTART
mdefine_line|#define ERESTART        -1              /* restart syscall */
macro_line|#endif
macro_line|#ifndef EJUSTRETURN
DECL|macro|EJUSTRETURN
mdefine_line|#define EJUSTRETURN     -2              /* don&squot;t modify regs, just return */
macro_line|#endif
r_static
r_int
id|ascentrycomp
c_func
(paren
r_const
r_void
op_star
id|key
comma
r_const
r_void
op_star
id|member
)paren
suffix:semicolon
r_static
r_int
id|senseentrycomp
c_func
(paren
r_const
r_void
op_star
id|key
comma
r_const
r_void
op_star
id|member
)paren
suffix:semicolon
r_static
r_void
id|fetchtableentries
c_func
(paren
r_int
id|sense_key
comma
r_int
id|asc
comma
r_int
id|ascq
comma
r_struct
id|scsi_inquiry_data
op_star
comma
r_const
r_struct
id|sense_key_table_entry
op_star
op_star
comma
r_const
r_struct
id|asc_table_entry
op_star
op_star
)paren
suffix:semicolon
r_static
r_void
op_star
id|scsibsearch
c_func
(paren
r_const
r_void
op_star
id|key
comma
r_const
r_void
op_star
id|base
comma
r_int
id|nmemb
comma
r_int
id|size
comma
r_int
(paren
op_star
id|compar
)paren
(paren
r_const
r_void
op_star
comma
r_const
r_void
op_star
)paren
)paren
suffix:semicolon
DECL|typedef|cam_quirkmatch_t
r_typedef
r_int
(paren
id|cam_quirkmatch_t
)paren
(paren
id|caddr_t
comma
id|caddr_t
)paren
suffix:semicolon
r_static
r_int
id|cam_strmatch
c_func
(paren
r_const
id|u_int8_t
op_star
id|str
comma
r_const
id|u_int8_t
op_star
id|pattern
comma
r_int
id|str_len
)paren
suffix:semicolon
r_static
id|caddr_t
id|cam_quirkmatch
c_func
(paren
id|caddr_t
id|target
comma
id|caddr_t
id|quirk_table
comma
r_int
id|num_entries
comma
r_int
id|entry_size
comma
id|cam_quirkmatch_t
op_star
id|comp_func
)paren
suffix:semicolon
DECL|macro|SCSI_NO_SENSE_STRINGS
mdefine_line|#define SCSI_NO_SENSE_STRINGS 1
macro_line|#if !defined(SCSI_NO_SENSE_STRINGS)
DECL|macro|SST
mdefine_line|#define SST(asc, ascq, action, desc) &bslash;&n;&t;asc, ascq, action, desc
macro_line|#else 
DECL|variable|empty_string
r_static
r_const
r_char
id|empty_string
(braket
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|macro|SST
mdefine_line|#define SST(asc, ascq, action, desc) &bslash;&n;&t;asc, ascq, action, empty_string
macro_line|#endif 
DECL|variable|sense_key_table
r_static
r_const
r_struct
id|sense_key_table_entry
id|sense_key_table
(braket
)braket
op_assign
(brace
(brace
id|SSD_KEY_NO_SENSE
comma
id|SS_NOP
comma
l_string|&quot;NO SENSE&quot;
)brace
comma
(brace
id|SSD_KEY_RECOVERED_ERROR
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;RECOVERED ERROR&quot;
)brace
comma
(brace
id|SSD_KEY_NOT_READY
comma
id|SS_TUR
op_or
id|SSQ_MANY
op_or
id|SSQ_DECREMENT_COUNT
op_or
id|EBUSY
comma
l_string|&quot;NOT READY&quot;
)brace
comma
(brace
id|SSD_KEY_MEDIUM_ERROR
comma
id|SS_RDEF
comma
l_string|&quot;MEDIUM ERROR&quot;
)brace
comma
(brace
id|SSD_KEY_HARDWARE_ERROR
comma
id|SS_RDEF
comma
l_string|&quot;HARDWARE FAILURE&quot;
)brace
comma
(brace
id|SSD_KEY_ILLEGAL_REQUEST
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;ILLEGAL REQUEST&quot;
)brace
comma
(brace
id|SSD_KEY_UNIT_ATTENTION
comma
id|SS_FATAL
op_or
id|ENXIO
comma
l_string|&quot;UNIT ATTENTION&quot;
)brace
comma
(brace
id|SSD_KEY_DATA_PROTECT
comma
id|SS_FATAL
op_or
id|EACCES
comma
l_string|&quot;DATA PROTECT&quot;
)brace
comma
(brace
id|SSD_KEY_BLANK_CHECK
comma
id|SS_FATAL
op_or
id|ENOSPC
comma
l_string|&quot;BLANK CHECK&quot;
)brace
comma
(brace
id|SSD_KEY_Vendor_Specific
comma
id|SS_FATAL
op_or
id|EIO
comma
l_string|&quot;Vendor Specific&quot;
)brace
comma
(brace
id|SSD_KEY_COPY_ABORTED
comma
id|SS_FATAL
op_or
id|EIO
comma
l_string|&quot;COPY ABORTED&quot;
)brace
comma
(brace
id|SSD_KEY_ABORTED_COMMAND
comma
id|SS_RDEF
comma
l_string|&quot;ABORTED COMMAND&quot;
)brace
comma
(brace
id|SSD_KEY_EQUAL
comma
id|SS_NOP
comma
l_string|&quot;EQUAL&quot;
)brace
comma
(brace
id|SSD_KEY_VOLUME_OVERFLOW
comma
id|SS_FATAL
op_or
id|EIO
comma
l_string|&quot;VOLUME OVERFLOW&quot;
)brace
comma
(brace
id|SSD_KEY_MISCOMPARE
comma
id|SS_NOP
comma
l_string|&quot;MISCOMPARE&quot;
)brace
comma
(brace
id|SSD_KEY_RESERVED
comma
id|SS_FATAL
op_or
id|EIO
comma
l_string|&quot;RESERVED&quot;
)brace
)brace
suffix:semicolon
DECL|variable|sense_key_table_size
r_static
r_const
r_int
id|sense_key_table_size
op_assign
r_sizeof
(paren
id|sense_key_table
)paren
op_div
r_sizeof
(paren
id|sense_key_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
DECL|variable|quantum_fireball_entries
r_static
r_struct
id|asc_table_entry
id|quantum_fireball_entries
(braket
)braket
op_assign
(brace
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x0b
comma
id|SS_START
op_or
id|SSQ_DECREMENT_COUNT
op_or
id|ENXIO
comma
l_string|&quot;Logical unit not ready, initializing cmd. required&quot;
)paren
)brace
)brace
suffix:semicolon
DECL|variable|sony_mo_entries
r_static
r_struct
id|asc_table_entry
id|sony_mo_entries
(braket
)braket
op_assign
(brace
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x00
comma
id|SS_START
op_or
id|SSQ_DECREMENT_COUNT
op_or
id|ENXIO
comma
l_string|&quot;Logical unit not ready, cause not reportable&quot;
)paren
)brace
)brace
suffix:semicolon
DECL|variable|sense_quirk_table
r_static
r_struct
id|scsi_sense_quirk_entry
id|sense_quirk_table
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/*&n;&t;&t; * The Quantum Fireball ST and SE like to return 0x04 0x0b when&n;&t;&t; * they really should return 0x04 0x02.  0x04,0x0b isn&squot;t&n;&t;&t; * defined in any SCSI spec, and it isn&squot;t mentioned in the&n;&t;&t; * hardware manual for these drives.&n;&t;&t; */
(brace
id|T_DIRECT
comma
id|SIP_MEDIA_FIXED
comma
l_string|&quot;QUANTUM&quot;
comma
l_string|&quot;FIREBALL S*&quot;
comma
l_string|&quot;*&quot;
)brace
comma
multiline_comment|/*num_sense_keys*/
l_int|0
comma
r_sizeof
(paren
id|quantum_fireball_entries
)paren
op_div
r_sizeof
(paren
r_struct
id|asc_table_entry
)paren
comma
multiline_comment|/*sense key entries*/
l_int|NULL
comma
id|quantum_fireball_entries
)brace
comma
(brace
multiline_comment|/*&n;&t;&t; * This Sony MO drive likes to return 0x04, 0x00 when it&n;&t;&t; * isn&squot;t spun up.&n;&t;&t; */
(brace
id|T_DIRECT
comma
id|SIP_MEDIA_REMOVABLE
comma
l_string|&quot;SONY&quot;
comma
l_string|&quot;SMO-*&quot;
comma
l_string|&quot;*&quot;
)brace
comma
multiline_comment|/*num_sense_keys*/
l_int|0
comma
r_sizeof
(paren
id|sony_mo_entries
)paren
op_div
r_sizeof
(paren
r_struct
id|asc_table_entry
)paren
comma
multiline_comment|/*sense key entries*/
l_int|NULL
comma
id|sony_mo_entries
)brace
)brace
suffix:semicolon
DECL|variable|sense_quirk_table_size
r_static
r_const
r_int
id|sense_quirk_table_size
op_assign
r_sizeof
(paren
id|sense_quirk_table
)paren
op_div
r_sizeof
(paren
id|sense_quirk_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
DECL|variable|asc_table
r_static
r_struct
id|asc_table_entry
id|asc_table
(braket
)braket
op_assign
(brace
multiline_comment|/*&n; * From File: ASC-NUM.TXT&n; * SCSI ASC/ASCQ Assignments&n; * Numeric Sorted Listing&n; * as of  5/12/97&n; *&n; * D - DIRECT ACCESS DEVICE (SBC)                     device column key&n; * .T - SEQUENTIAL ACCESS DEVICE (SSC)               -------------------&n; * . L - PRINTER DEVICE (SSC)                           blank = reserved&n; * .  P - PROCESSOR DEVICE (SPC)                     not blank = allowed&n; * .  .W - WRITE ONCE READ MULTIPLE DEVICE (SBC)&n; * .  . R - CD DEVICE (MMC)&n; * .  .  S - SCANNER DEVICE (SGC)&n; * .  .  .O - OPTICAL MEMORY DEVICE (SBC)&n; * .  .  . M - MEDIA CHANGER DEVICE (SMC)&n; * .  .  .  C - COMMUNICATION DEVICE (SSC)&n; * .  .  .  .A - STORAGE ARRAY DEVICE (SCC)&n; * .  .  .  . E - ENCLOSURE SERVICES DEVICE (SES)&n; * DTLPWRSOMCAE        ASC   ASCQ  Action  Description&n; * ------------        ----  ----  ------  -----------------------------------*/
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x00
comma
id|SS_NOP
comma
l_string|&quot;No additional sense information&quot;
)paren
)brace
comma
multiline_comment|/*  T    S      */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Filemark detected&quot;
)paren
)brace
comma
multiline_comment|/*  T    S      */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;End-of-partition/medium detected&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Setmark detected&quot;
)paren
)brace
comma
multiline_comment|/*  T    S      */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Beginning-of-partition/medium detected&quot;
)paren
)brace
comma
multiline_comment|/*  T    S      */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x05
comma
id|SS_RDEF
comma
l_string|&quot;End-of-data detected&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x06
comma
id|SS_RDEF
comma
l_string|&quot;I/O process terminated&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x11
comma
id|SS_FATAL
op_or
id|EBUSY
comma
l_string|&quot;Audio play operation in progress&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x12
comma
id|SS_NOP
comma
l_string|&quot;Audio play operation paused&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x13
comma
id|SS_NOP
comma
l_string|&quot;Audio play operation successfully completed&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x14
comma
id|SS_RDEF
comma
l_string|&quot;Audio play operation stopped due to error&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x15
comma
id|SS_NOP
comma
l_string|&quot;No current audio status to return&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x16
comma
id|SS_FATAL
op_or
id|EBUSY
comma
l_string|&quot;Operation in progress&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOM AE */
(brace
id|SST
c_func
(paren
l_int|0x00
comma
l_int|0x17
comma
id|SS_RDEF
comma
l_string|&quot;Cleaning requested&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x01
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;No index/sector signal&quot;
)paren
)brace
comma
multiline_comment|/* D   WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x02
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;No seek complete&quot;
)paren
)brace
comma
multiline_comment|/* DTL W SO     */
(brace
id|SST
c_func
(paren
l_int|0x03
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Peripheral device write fault&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x03
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;No write current&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x03
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Excessive write errors&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x00
comma
id|SS_TUR
op_or
id|SSQ_DELAY
op_or
id|SSQ_MANY
op_or
id|SSQ_DECREMENT_COUNT
op_or
id|EIO
comma
l_string|&quot;Logical unit not ready, cause not reportable&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x01
comma
id|SS_TUR
op_or
id|SSQ_DELAY
op_or
id|SSQ_MANY
op_or
id|SSQ_DECREMENT_COUNT
op_or
id|EBUSY
comma
l_string|&quot;Logical unit is in process of becoming ready&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x02
comma
id|SS_START
op_or
id|SSQ_DECREMENT_COUNT
op_or
id|ENXIO
comma
l_string|&quot;Logical unit not ready, initializing cmd. required&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x03
comma
id|SS_FATAL
op_or
id|ENXIO
comma
l_string|&quot;Logical unit not ready, manual intervention required&quot;
)paren
)brace
comma
multiline_comment|/* DTL    O     */
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x04
comma
id|SS_FATAL
op_or
id|EBUSY
comma
l_string|&quot;Logical unit not ready, format in progress&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  OMCA  */
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x05
comma
id|SS_FATAL
op_or
id|EBUSY
comma
l_string|&quot;Logical unit not ready, rebuild in progress&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  OMCA  */
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x06
comma
id|SS_FATAL
op_or
id|EBUSY
comma
l_string|&quot;Logical unit not ready, recalculation in progress&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x07
comma
id|SS_FATAL
op_or
id|EBUSY
comma
l_string|&quot;Logical unit not ready, operation in progress&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x04
comma
l_int|0x08
comma
id|SS_FATAL
op_or
id|EBUSY
comma
l_string|&quot;Logical unit not ready, long write in progress&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x05
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Logical unit does not respond to selection&quot;
)paren
)brace
comma
multiline_comment|/* D   WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x06
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;No reference position found&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOM    */
(brace
id|SST
c_func
(paren
l_int|0x07
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Multiple peripheral devices selected&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x08
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Logical unit communication failure&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x08
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Logical unit communication time-out&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x08
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Logical unit communication parity error&quot;
)paren
)brace
comma
multiline_comment|/* DT   R OM    */
(brace
id|SST
c_func
(paren
l_int|0x08
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Logical unit communication crc error (ultra-dma/32)&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x09
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Track following error&quot;
)paren
)brace
comma
multiline_comment|/*     WR O     */
(brace
id|SST
c_func
(paren
l_int|0x09
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Tracking servo failure&quot;
)paren
)brace
comma
multiline_comment|/*     WR O     */
(brace
id|SST
c_func
(paren
l_int|0x09
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Focus servo failure&quot;
)paren
)brace
comma
multiline_comment|/*     WR O     */
(brace
id|SST
c_func
(paren
l_int|0x09
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Spindle servo failure&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x09
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Head select fault&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x0A
comma
l_int|0x00
comma
id|SS_FATAL
op_or
id|ENOSPC
comma
l_string|&quot;Error log overflow&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x0B
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Warning&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x0B
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Specified temperature exceeded&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x0B
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Enclosure degraded&quot;
)paren
)brace
comma
multiline_comment|/*  T   RS      */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Write error&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x01
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Write error - recovered with auto reallocation&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Write error - auto reallocation failed&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Write error - recommend reassignment&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Compression check miscompare error&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x05
comma
id|SS_RDEF
comma
l_string|&quot;Data expansion occurred during compression&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x06
comma
id|SS_RDEF
comma
l_string|&quot;Block not compressible&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x07
comma
id|SS_RDEF
comma
l_string|&quot;Write error - recovery needed&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x08
comma
id|SS_RDEF
comma
l_string|&quot;Write error - recovery failed&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x09
comma
id|SS_RDEF
comma
l_string|&quot;Write error - loss of streaming&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x0C
comma
l_int|0x0A
comma
id|SS_RDEF
comma
l_string|&quot;Write error - padding blocks added&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x10
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;ID CRC or ECC error&quot;
)paren
)brace
comma
multiline_comment|/* DT  WRSO     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Unrecovered read error&quot;
)paren
)brace
comma
multiline_comment|/* DT  W SO     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Read retries exhausted&quot;
)paren
)brace
comma
multiline_comment|/* DT  W SO     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Error too long to correct&quot;
)paren
)brace
comma
multiline_comment|/* DT  W SO     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Multiple read errors&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Unrecovered read error - auto reallocate failed&quot;
)paren
)brace
comma
multiline_comment|/*     WR O     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x05
comma
id|SS_RDEF
comma
l_string|&quot;L-EC uncorrectable error&quot;
)paren
)brace
comma
multiline_comment|/*     WR O     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x06
comma
id|SS_RDEF
comma
l_string|&quot;CIRC unrecovered error&quot;
)paren
)brace
comma
multiline_comment|/*     W  O     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x07
comma
id|SS_RDEF
comma
l_string|&quot;Data re-synchronization error&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x08
comma
id|SS_RDEF
comma
l_string|&quot;Incomplete block read&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x09
comma
id|SS_RDEF
comma
l_string|&quot;No gap found&quot;
)paren
)brace
comma
multiline_comment|/* DT     O     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x0A
comma
id|SS_RDEF
comma
l_string|&quot;Miscorrected error&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x0B
comma
id|SS_RDEF
comma
l_string|&quot;Unrecovered read error - recommend reassignment&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x0C
comma
id|SS_RDEF
comma
l_string|&quot;Unrecovered read error - recommend rewrite the data&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x0D
comma
id|SS_RDEF
comma
l_string|&quot;De-compression CRC error&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x0E
comma
id|SS_RDEF
comma
l_string|&quot;Cannot decompress using declared algorithm&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x0F
comma
id|SS_RDEF
comma
l_string|&quot;Error reading UPC/EAN number&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x10
comma
id|SS_RDEF
comma
l_string|&quot;Error reading ISRC number&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x11
comma
l_int|0x11
comma
id|SS_RDEF
comma
l_string|&quot;Read error - loss of streaming&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x12
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Address mark not found for id field&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x13
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Address mark not found for data field&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSO     */
(brace
id|SST
c_func
(paren
l_int|0x14
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Recorded entity not found&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x14
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Record not found&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x14
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Filemark or setmark not found&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x14
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;End-of-data not found&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x14
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Block sequence error&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x14
comma
l_int|0x05
comma
id|SS_RDEF
comma
l_string|&quot;Record not found - recommend reassignment&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x14
comma
l_int|0x06
comma
id|SS_RDEF
comma
l_string|&quot;Record not found - data auto-reallocated&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOM    */
(brace
id|SST
c_func
(paren
l_int|0x15
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Random positioning error&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOM    */
(brace
id|SST
c_func
(paren
l_int|0x15
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Mechanical positioning error&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x15
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Positioning error detected by read of medium&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x16
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Data synchronization mark error&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x16
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Data sync error - data rewritten&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x16
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Data sync error - recommend rewrite&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x16
comma
l_int|0x03
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Data sync error - data auto-reallocated&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x16
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Data sync error - recommend reassignment&quot;
)paren
)brace
comma
multiline_comment|/* DT  WRSO     */
(brace
id|SST
c_func
(paren
l_int|0x17
comma
l_int|0x00
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data with no error correction applied&quot;
)paren
)brace
comma
multiline_comment|/* DT  WRSO     */
(brace
id|SST
c_func
(paren
l_int|0x17
comma
l_int|0x01
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data with retries&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x17
comma
l_int|0x02
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data with positive head offset&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x17
comma
l_int|0x03
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data with negative head offset&quot;
)paren
)brace
comma
multiline_comment|/*     WR O     */
(brace
id|SST
c_func
(paren
l_int|0x17
comma
l_int|0x04
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data with retries and/or CIRC applied&quot;
)paren
)brace
comma
multiline_comment|/* D   WR O     */
(brace
id|SST
c_func
(paren
l_int|0x17
comma
l_int|0x05
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data using previous sector id&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x17
comma
l_int|0x06
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data without ECC - data auto-reallocated&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x17
comma
l_int|0x07
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data without ECC - recommend reassignment&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x17
comma
l_int|0x08
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data without ECC - recommend rewrite&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x17
comma
l_int|0x09
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data without ECC - data rewritten&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x18
comma
l_int|0x00
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data with error correction applied&quot;
)paren
)brace
comma
multiline_comment|/* D   WR O     */
(brace
id|SST
c_func
(paren
l_int|0x18
comma
l_int|0x01
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data with error corr. &amp; retries applied&quot;
)paren
)brace
comma
multiline_comment|/* D   WR O     */
(brace
id|SST
c_func
(paren
l_int|0x18
comma
l_int|0x02
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data - data auto-reallocated&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x18
comma
l_int|0x03
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data with CIRC&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x18
comma
l_int|0x04
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data with L-EC&quot;
)paren
)brace
comma
multiline_comment|/* D   WR O     */
(brace
id|SST
c_func
(paren
l_int|0x18
comma
l_int|0x05
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data - recommend reassignment&quot;
)paren
)brace
comma
multiline_comment|/* D   WR O     */
(brace
id|SST
c_func
(paren
l_int|0x18
comma
l_int|0x06
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data - recommend rewrite&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x18
comma
l_int|0x07
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered data with ECC - data rewritten&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x19
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Defect list error&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x19
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Defect list not available&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x19
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Defect list error in primary list&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x19
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Defect list error in grown list&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x1A
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Parameter list length error&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x1B
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Synchronous data transfer error&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x1C
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Defect list not found&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x1C
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Primary defect list not found&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x1C
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Grown defect list not found&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x1D
comma
l_int|0x00
comma
id|SS_FATAL
comma
l_string|&quot;Miscompare during verify operation&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x1E
comma
l_int|0x00
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Recovered id with ecc correction&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x1F
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Partial defect list transfer&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x20
comma
l_int|0x00
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;Invalid command operation code&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x21
comma
l_int|0x00
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;Logical block address out of range&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x21
comma
l_int|0x01
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;Invalid element address&quot;
)paren
)brace
comma
multiline_comment|/* D            */
(brace
id|SST
c_func
(paren
l_int|0x22
comma
l_int|0x00
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;Illegal function&quot;
)paren
)brace
comma
multiline_comment|/* Deprecated. Use 20 00, 24 00, or 26 00 instead */
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x24
comma
l_int|0x00
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;Invalid field in CDB&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x25
comma
l_int|0x00
comma
id|SS_FATAL
op_or
id|ENXIO
comma
l_string|&quot;Logical unit not supported&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x26
comma
l_int|0x00
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;Invalid field in parameter list&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x26
comma
l_int|0x01
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;Parameter not supported&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x26
comma
l_int|0x02
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;Parameter value invalid&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x26
comma
l_int|0x03
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;Threshold parameters not supported&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x26
comma
l_int|0x04
comma
id|SS_FATAL
op_or
id|EINVAL
comma
l_string|&quot;Invalid release of active persistent reservation&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x27
comma
l_int|0x00
comma
id|SS_FATAL
op_or
id|EACCES
comma
l_string|&quot;Write protected&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x27
comma
l_int|0x01
comma
id|SS_FATAL
op_or
id|EACCES
comma
l_string|&quot;Hardware write protected&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x27
comma
l_int|0x02
comma
id|SS_FATAL
op_or
id|EACCES
comma
l_string|&quot;Logical unit software write protected&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x27
comma
l_int|0x03
comma
id|SS_FATAL
op_or
id|EACCES
comma
l_string|&quot;Associated write protect&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x27
comma
l_int|0x04
comma
id|SS_FATAL
op_or
id|EACCES
comma
l_string|&quot;Persistent write protect&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x27
comma
l_int|0x05
comma
id|SS_FATAL
op_or
id|EACCES
comma
l_string|&quot;Permanent write protect&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x28
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Not ready to ready change, medium may have changed&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x28
comma
l_int|0x01
comma
id|SS_FATAL
op_or
id|ENXIO
comma
l_string|&quot;Import or export element accessed&quot;
)paren
)brace
comma
multiline_comment|/*&n; * XXX JGibbs - All of these should use the same errno, but I don&squot;t think&n; * ENXIO is the correct choice.  Should we borrow from the networking&n; * errnos?  ECONNRESET anyone?&n; */
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x29
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Power on, reset, or bus device reset occurred&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x29
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Power on occurred&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x29
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Scsi bus reset occurred&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x29
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Bus device reset function occurred&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x29
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Device internal reset&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x29
comma
l_int|0x05
comma
id|SS_RDEF
comma
l_string|&quot;Transceiver mode changed to single-ended&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x29
comma
l_int|0x06
comma
id|SS_RDEF
comma
l_string|&quot;Transceiver mode changed to LVD&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x2A
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Parameters changed&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x2A
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Mode parameters changed&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x2A
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Log parameters changed&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x2A
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Reservations preempted&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSO C   */
(brace
id|SST
c_func
(paren
l_int|0x2B
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Copy cannot execute since host cannot disconnect&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x2C
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Command sequence error&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x2C
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Too many windows specified&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x2C
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Invalid combination of windows specified&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x2C
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Current program area is not empty&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x2C
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Current program area is empty&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x2D
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Overwrite error on update in place&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x2F
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Commands cleared by another initiator&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x30
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Incompatible medium installed&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x30
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Cannot read medium - unknown format&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x30
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Cannot read medium - incompatible format&quot;
)paren
)brace
comma
multiline_comment|/* DT           */
(brace
id|SST
c_func
(paren
l_int|0x30
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Cleaning cartridge installed&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x30
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Cannot write medium - unknown format&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x30
comma
l_int|0x05
comma
id|SS_RDEF
comma
l_string|&quot;Cannot write medium - incompatible format&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x30
comma
l_int|0x06
comma
id|SS_RDEF
comma
l_string|&quot;Cannot format medium - incompatible medium&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOM AE */
(brace
id|SST
c_func
(paren
l_int|0x30
comma
l_int|0x07
comma
id|SS_RDEF
comma
l_string|&quot;Cleaning failure&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x30
comma
l_int|0x08
comma
id|SS_RDEF
comma
l_string|&quot;Cannot write - application code mismatch&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x30
comma
l_int|0x09
comma
id|SS_RDEF
comma
l_string|&quot;Current session not fixated for append&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR O     */
(brace
id|SST
c_func
(paren
l_int|0x31
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Medium format corrupted&quot;
)paren
)brace
comma
multiline_comment|/* D L  R O     */
(brace
id|SST
c_func
(paren
l_int|0x31
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Format command failed&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x32
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;No defect spare location available&quot;
)paren
)brace
comma
multiline_comment|/* D   W  O     */
(brace
id|SST
c_func
(paren
l_int|0x32
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Defect list update failure&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x33
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Tape length error&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x34
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Enclosure failure&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x35
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Enclosure services failure&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x35
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Unsupported enclosure function&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x35
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Enclosure services unavailable&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x35
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Enclosure services transfer failure&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x35
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Enclosure services transfer refused&quot;
)paren
)brace
comma
multiline_comment|/*   L          */
(brace
id|SST
c_func
(paren
l_int|0x36
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Ribbon, ink, or toner failure&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x37
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Rounded parameter&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x39
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Saving parameters not supported&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOM    */
(brace
id|SST
c_func
(paren
l_int|0x3A
comma
l_int|0x00
comma
id|SS_NOP
comma
l_string|&quot;Medium not present&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3A
comma
l_int|0x01
comma
id|SS_NOP
comma
l_string|&quot;Medium not present - tray closed&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3A
comma
l_int|0x01
comma
id|SS_NOP
comma
l_string|&quot;Medium not present - tray open&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3A
comma
l_int|0x03
comma
id|SS_NOP
comma
l_string|&quot;Medium not present - Loadable&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3A
comma
l_int|0x04
comma
id|SS_NOP
comma
l_string|&quot;Medium not present - medium auxiliary &quot;
l_string|&quot;memory accessible&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3A
comma
l_int|0xFF
comma
id|SS_NOP
comma
l_int|NULL
)paren
)brace
comma
multiline_comment|/* Range 0x05-&gt;0xFF */
multiline_comment|/*  TL          */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Sequential positioning error&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Tape position error at beginning-of-medium&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Tape position error at end-of-medium&quot;
)paren
)brace
comma
multiline_comment|/*   L          */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Tape or electronic vertical forms unit not ready&quot;
)paren
)brace
comma
multiline_comment|/*   L          */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Slew failure&quot;
)paren
)brace
comma
multiline_comment|/*   L          */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x05
comma
id|SS_RDEF
comma
l_string|&quot;Paper jam&quot;
)paren
)brace
comma
multiline_comment|/*   L          */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x06
comma
id|SS_RDEF
comma
l_string|&quot;Failed to sense top-of-form&quot;
)paren
)brace
comma
multiline_comment|/*   L          */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x07
comma
id|SS_RDEF
comma
l_string|&quot;Failed to sense bottom-of-form&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x08
comma
id|SS_RDEF
comma
l_string|&quot;Reposition error&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x09
comma
id|SS_RDEF
comma
l_string|&quot;Read past end of medium&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x0A
comma
id|SS_RDEF
comma
l_string|&quot;Read past beginning of medium&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x0B
comma
id|SS_RDEF
comma
l_string|&quot;Position past end of medium&quot;
)paren
)brace
comma
multiline_comment|/*  T    S      */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x0C
comma
id|SS_RDEF
comma
l_string|&quot;Position past beginning of medium&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x0D
comma
id|SS_FATAL
op_or
id|ENOSPC
comma
l_string|&quot;Medium destination element full&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x0E
comma
id|SS_RDEF
comma
l_string|&quot;Medium source element empty&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x0F
comma
id|SS_RDEF
comma
l_string|&quot;End of medium reached&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x11
comma
id|SS_RDEF
comma
l_string|&quot;Medium magazine not accessible&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x12
comma
id|SS_RDEF
comma
l_string|&quot;Medium magazine removed&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x13
comma
id|SS_RDEF
comma
l_string|&quot;Medium magazine inserted&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x14
comma
id|SS_RDEF
comma
l_string|&quot;Medium magazine locked&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x3B
comma
l_int|0x15
comma
id|SS_RDEF
comma
l_string|&quot;Medium magazine unlocked&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3D
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Invalid bits in identify message&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3E
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Logical unit has not self-configured yet&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3E
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Logical unit failure&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3E
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Timeout on logical unit&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Target operating conditions have changed&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Microcode has been changed&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMC   */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Changed operating definition&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x03
comma
id|SS_INQ_REFRESH
op_or
id|SSQ_DECREMENT_COUNT
comma
l_string|&quot;Inquiry data has changed&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Component device attached&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x05
comma
id|SS_RDEF
comma
l_string|&quot;Device identifier changed&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x06
comma
id|SS_RDEF
comma
l_string|&quot;Redundancy group created or modified&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x07
comma
id|SS_RDEF
comma
l_string|&quot;Redundancy group deleted&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x08
comma
id|SS_RDEF
comma
l_string|&quot;Spare created or modified&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x09
comma
id|SS_RDEF
comma
l_string|&quot;Spare deleted&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x0A
comma
id|SS_RDEF
comma
l_string|&quot;Volume set created or modified&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x0B
comma
id|SS_RDEF
comma
l_string|&quot;Volume set deleted&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x0C
comma
id|SS_RDEF
comma
l_string|&quot;Volume set deassigned&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x0D
comma
id|SS_RDEF
comma
l_string|&quot;Volume set reassigned&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x0E
comma
id|SS_RDEF
comma
l_string|&quot;Reported luns data has changed&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x0F
comma
id|SS_RETRY
op_or
id|SSQ_DECREMENT_COUNT
op_or
id|SSQ_DELAY_RANDOM
op_or
id|EBUSY
comma
l_string|&quot;Echo buffer overwritten&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM   B*/
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x0F
comma
id|SS_RDEF
comma
l_string|&quot;Medium Loadable&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM   B*/
(brace
id|SST
c_func
(paren
l_int|0x3F
comma
l_int|0x0F
comma
id|SS_RDEF
comma
l_string|&quot;Medium auxiliary memory accessible&quot;
)paren
)brace
comma
multiline_comment|/* D            */
(brace
id|SST
c_func
(paren
l_int|0x40
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Ram failure&quot;
)paren
)brace
comma
multiline_comment|/* deprecated - use 40 NN instead */
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x40
comma
l_int|0x80
comma
id|SS_RDEF
comma
l_string|&quot;Diagnostic failure: ASCQ = Component ID&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x40
comma
l_int|0xFF
comma
id|SS_RDEF
op_or
id|SSQ_RANGE
comma
l_int|NULL
)paren
)brace
comma
multiline_comment|/* Range 0x80-&gt;0xFF */
multiline_comment|/* D            */
(brace
id|SST
c_func
(paren
l_int|0x41
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Data path failure&quot;
)paren
)brace
comma
multiline_comment|/* deprecated - use 40 NN instead */
multiline_comment|/* D            */
(brace
id|SST
c_func
(paren
l_int|0x42
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Power-on or self-test failure&quot;
)paren
)brace
comma
multiline_comment|/* deprecated - use 40 NN instead */
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x43
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Message error&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x44
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Internal target failure&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x45
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Select or reselect failure&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMC   */
(brace
id|SST
c_func
(paren
l_int|0x46
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Unsuccessful soft reset&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x47
comma
l_int|0x00
comma
id|SS_RDEF
op_or
id|SSQ_FALLBACK
comma
l_string|&quot;SCSI parity error&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x47
comma
l_int|0x01
comma
id|SS_RDEF
op_or
id|SSQ_FALLBACK
comma
l_string|&quot;Data Phase CRC error detected&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x47
comma
l_int|0x02
comma
id|SS_RDEF
op_or
id|SSQ_FALLBACK
comma
l_string|&quot;SCSI parity error detected during ST data phase&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x47
comma
l_int|0x03
comma
id|SS_RDEF
op_or
id|SSQ_FALLBACK
comma
l_string|&quot;Information Unit iuCRC error&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x47
comma
l_int|0x04
comma
id|SS_RDEF
op_or
id|SSQ_FALLBACK
comma
l_string|&quot;Asynchronous information protection error detected&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x47
comma
l_int|0x05
comma
id|SS_RDEF
op_or
id|SSQ_FALLBACK
comma
l_string|&quot;Protocol server CRC error&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x48
comma
l_int|0x00
comma
id|SS_RDEF
op_or
id|SSQ_FALLBACK
comma
l_string|&quot;Initiator detected error message received&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x49
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Invalid message error&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x4A
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Command phase error&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x4B
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Data phase error&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x4C
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Logical unit failed self-configuration&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x4D
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Tagged overlapped commands: ASCQ = Queue tag ID&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x4D
comma
l_int|0xFF
comma
id|SS_RDEF
op_or
id|SSQ_RANGE
comma
l_int|NULL
)paren
)brace
comma
multiline_comment|/* Range 0x00-&gt;0xFF */
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x4E
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Overlapped commands attempted&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x50
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Write append error&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x50
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Write append position error&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x50
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Position error related to timing&quot;
)paren
)brace
comma
multiline_comment|/*  T     O     */
(brace
id|SST
c_func
(paren
l_int|0x51
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Erase failure&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x52
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Cartridge fault&quot;
)paren
)brace
comma
multiline_comment|/* DTL WRSOM    */
(brace
id|SST
c_func
(paren
l_int|0x53
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Media load or eject failed&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x53
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Unload tape failure&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x53
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Medium removal prevented&quot;
)paren
)brace
comma
multiline_comment|/*    P         */
(brace
id|SST
c_func
(paren
l_int|0x54
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Scsi to host system interface failure&quot;
)paren
)brace
comma
multiline_comment|/*    P         */
(brace
id|SST
c_func
(paren
l_int|0x55
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;System resource failure&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x55
comma
l_int|0x01
comma
id|SS_FATAL
op_or
id|ENOSPC
comma
l_string|&quot;System buffer full&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x57
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Unable to recover table-of-contents&quot;
)paren
)brace
comma
multiline_comment|/*        O     */
(brace
id|SST
c_func
(paren
l_int|0x58
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Generation does not exist&quot;
)paren
)brace
comma
multiline_comment|/*        O     */
(brace
id|SST
c_func
(paren
l_int|0x59
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Updated block read&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOM    */
(brace
id|SST
c_func
(paren
l_int|0x5A
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Operator request or state change input&quot;
)paren
)brace
comma
multiline_comment|/* DT  WR OM    */
(brace
id|SST
c_func
(paren
l_int|0x5A
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Operator medium removal request&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x5A
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Operator selected write protect&quot;
)paren
)brace
comma
multiline_comment|/* DT  W  O     */
(brace
id|SST
c_func
(paren
l_int|0x5A
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Operator selected write permit&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOM    */
(brace
id|SST
c_func
(paren
l_int|0x5B
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Log exception&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOM    */
(brace
id|SST
c_func
(paren
l_int|0x5B
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Threshold condition met&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOM    */
(brace
id|SST
c_func
(paren
l_int|0x5B
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Log counter at maximum&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOM    */
(brace
id|SST
c_func
(paren
l_int|0x5B
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Log list codes exhausted&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x5C
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;RPL status change&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x5C
comma
l_int|0x01
comma
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
comma
l_string|&quot;Spindles synchronized&quot;
)paren
)brace
comma
multiline_comment|/* D      O     */
(brace
id|SST
c_func
(paren
l_int|0x5C
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Spindles not synchronized&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x5D
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Failure prediction threshold exceeded&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x5D
comma
l_int|0xFF
comma
id|SS_RDEF
comma
l_string|&quot;Failure prediction threshold exceeded (false)&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSO CA  */
(brace
id|SST
c_func
(paren
l_int|0x5E
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Low power condition on&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSO CA  */
(brace
id|SST
c_func
(paren
l_int|0x5E
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Idle condition activated by timer&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSO CA  */
(brace
id|SST
c_func
(paren
l_int|0x5E
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Standby condition activated by timer&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSO CA  */
(brace
id|SST
c_func
(paren
l_int|0x5E
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Idle condition activated by command&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSO CA  */
(brace
id|SST
c_func
(paren
l_int|0x5E
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Standby condition activated by command&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x60
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Lamp failure&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x61
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Video acquisition error&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x61
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Unable to acquire video&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x61
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Out of focus&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x62
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Scan head positioning error&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x63
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;End of user area encountered on this track&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x63
comma
l_int|0x01
comma
id|SS_FATAL
op_or
id|ENOSPC
comma
l_string|&quot;Packet does not fit in available space&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x64
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Illegal mode for this track&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x64
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Invalid packet size&quot;
)paren
)brace
comma
multiline_comment|/* DTLPWRSOMCAE */
(brace
id|SST
c_func
(paren
l_int|0x65
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Voltage fault&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x66
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Automatic document feeder cover up&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x66
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Automatic document feeder lift up&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x66
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Document jam in automatic document feeder&quot;
)paren
)brace
comma
multiline_comment|/*       S      */
(brace
id|SST
c_func
(paren
l_int|0x66
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Document miss feed automatic in document feeder&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x67
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Configuration failure&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x67
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Configuration of incapable logical units failed&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x67
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Add logical unit failed&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x67
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Modification of logical unit failed&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x67
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Exchange of logical unit failed&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x67
comma
l_int|0x05
comma
id|SS_RDEF
comma
l_string|&quot;Remove of logical unit failed&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x67
comma
l_int|0x06
comma
id|SS_RDEF
comma
l_string|&quot;Attachment of logical unit failed&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x67
comma
l_int|0x07
comma
id|SS_RDEF
comma
l_string|&quot;Creation of logical unit failed&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x68
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Logical unit not configured&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x69
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Data loss on logical unit&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x69
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Multiple logical unit failures&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x69
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Parity/data mismatch&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x6A
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Informational, refer to log&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x6B
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;State change has occurred&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x6B
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Redundancy level got better&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x6B
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Redundancy level got worse&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x6C
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Rebuild failure occurred&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x6D
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Recalculate failure occurred&quot;
)paren
)brace
comma
multiline_comment|/*           A  */
(brace
id|SST
c_func
(paren
l_int|0x6E
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Command to logical unit failed&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x70
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Decompression exception short: ASCQ = Algorithm ID&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x70
comma
l_int|0xFF
comma
id|SS_RDEF
op_or
id|SSQ_RANGE
comma
l_int|NULL
)paren
)brace
comma
multiline_comment|/* Range 0x00 -&gt; 0xFF */
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x71
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Decompression exception long: ASCQ = Algorithm ID&quot;
)paren
)brace
comma
multiline_comment|/*  T           */
(brace
id|SST
c_func
(paren
l_int|0x71
comma
l_int|0xFF
comma
id|SS_RDEF
op_or
id|SSQ_RANGE
comma
l_int|NULL
)paren
)brace
comma
multiline_comment|/* Range 0x00 -&gt; 0xFF */
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x72
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;Session fixation error&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x72
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Session fixation error writing lead-in&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x72
comma
l_int|0x02
comma
id|SS_RDEF
comma
l_string|&quot;Session fixation error writing lead-out&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x72
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Session fixation error - incomplete track in session&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x72
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Empty or partially written reserved track&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x73
comma
l_int|0x00
comma
id|SS_RDEF
comma
l_string|&quot;CD control error&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x73
comma
l_int|0x01
comma
id|SS_RDEF
comma
l_string|&quot;Power calibration area almost full&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x73
comma
l_int|0x02
comma
id|SS_FATAL
op_or
id|ENOSPC
comma
l_string|&quot;Power calibration area is full&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x73
comma
l_int|0x03
comma
id|SS_RDEF
comma
l_string|&quot;Power calibration area error&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x73
comma
l_int|0x04
comma
id|SS_RDEF
comma
l_string|&quot;Program memory area update failure&quot;
)paren
)brace
comma
multiline_comment|/*      R       */
(brace
id|SST
c_func
(paren
l_int|0x73
comma
l_int|0x05
comma
id|SS_RDEF
comma
l_string|&quot;program memory area is full&quot;
)paren
)brace
)brace
suffix:semicolon
DECL|variable|asc_table_size
r_static
r_const
r_int
id|asc_table_size
op_assign
r_sizeof
(paren
id|asc_table
)paren
op_div
r_sizeof
(paren
id|asc_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
DECL|struct|asc_key
r_struct
id|asc_key
(brace
DECL|member|asc
r_int
id|asc
suffix:semicolon
DECL|member|ascq
r_int
id|ascq
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|ascentrycomp
id|ascentrycomp
c_func
(paren
r_const
r_void
op_star
id|key
comma
r_const
r_void
op_star
id|member
)paren
(brace
r_int
id|asc
suffix:semicolon
r_int
id|ascq
suffix:semicolon
r_const
r_struct
id|asc_table_entry
op_star
id|table_entry
suffix:semicolon
id|asc
op_assign
(paren
(paren
r_const
r_struct
id|asc_key
op_star
)paren
id|key
)paren
op_member_access_from_pointer
id|asc
suffix:semicolon
id|ascq
op_assign
(paren
(paren
r_const
r_struct
id|asc_key
op_star
)paren
id|key
)paren
op_member_access_from_pointer
id|ascq
suffix:semicolon
id|table_entry
op_assign
(paren
r_const
r_struct
id|asc_table_entry
op_star
)paren
id|member
suffix:semicolon
r_if
c_cond
(paren
id|asc
op_ge
id|table_entry-&gt;asc
)paren
(brace
r_if
c_cond
(paren
id|asc
OG
id|table_entry-&gt;asc
)paren
r_return
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ascq
op_le
id|table_entry-&gt;ascq
)paren
(brace
multiline_comment|/* Check for ranges */
r_if
c_cond
(paren
id|ascq
op_eq
id|table_entry-&gt;ascq
op_logical_or
(paren
(paren
id|table_entry-&gt;action
op_amp
id|SSQ_RANGE
)paren
op_ne
l_int|0
op_logical_and
id|ascq
op_ge
(paren
id|table_entry
op_minus
l_int|1
)paren
op_member_access_from_pointer
id|ascq
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|senseentrycomp
id|senseentrycomp
c_func
(paren
r_const
r_void
op_star
id|key
comma
r_const
r_void
op_star
id|member
)paren
(brace
r_int
id|sense_key
suffix:semicolon
r_const
r_struct
id|sense_key_table_entry
op_star
id|table_entry
suffix:semicolon
id|sense_key
op_assign
op_star
(paren
(paren
r_const
r_int
op_star
)paren
id|key
)paren
suffix:semicolon
id|table_entry
op_assign
(paren
r_const
r_struct
id|sense_key_table_entry
op_star
)paren
id|member
suffix:semicolon
r_if
c_cond
(paren
id|sense_key
op_ge
id|table_entry-&gt;sense_key
)paren
(brace
r_if
c_cond
(paren
id|sense_key
op_eq
id|table_entry-&gt;sense_key
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|fetchtableentries
id|fetchtableentries
c_func
(paren
r_int
id|sense_key
comma
r_int
id|asc
comma
r_int
id|ascq
comma
r_struct
id|scsi_inquiry_data
op_star
id|inq_data
comma
r_const
r_struct
id|sense_key_table_entry
op_star
op_star
id|sense_entry
comma
r_const
r_struct
id|asc_table_entry
op_star
op_star
id|asc_entry
)paren
(brace
r_void
op_star
id|match
suffix:semicolon
r_const
r_struct
id|asc_table_entry
op_star
id|asc_tables
(braket
l_int|2
)braket
suffix:semicolon
r_const
r_struct
id|sense_key_table_entry
op_star
id|sense_tables
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|asc_key
id|asc_ascq
suffix:semicolon
r_int
id|asc_tables_size
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|sense_tables_size
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|num_asc_tables
suffix:semicolon
r_int
id|num_sense_tables
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Default to failure */
op_star
id|sense_entry
op_assign
l_int|NULL
suffix:semicolon
op_star
id|asc_entry
op_assign
l_int|NULL
suffix:semicolon
id|match
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|inq_data
op_ne
l_int|NULL
)paren
id|match
op_assign
id|cam_quirkmatch
c_func
(paren
(paren
r_void
op_star
)paren
id|inq_data
comma
(paren
r_void
op_star
)paren
id|sense_quirk_table
comma
id|sense_quirk_table_size
comma
r_sizeof
(paren
op_star
id|sense_quirk_table
)paren
comma
id|aic_inquiry_match
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
op_ne
l_int|NULL
)paren
(brace
r_struct
id|scsi_sense_quirk_entry
op_star
id|quirk
suffix:semicolon
id|quirk
op_assign
(paren
r_struct
id|scsi_sense_quirk_entry
op_star
)paren
id|match
suffix:semicolon
id|asc_tables
(braket
l_int|0
)braket
op_assign
id|quirk-&gt;asc_info
suffix:semicolon
id|asc_tables_size
(braket
l_int|0
)braket
op_assign
id|quirk-&gt;num_ascs
suffix:semicolon
id|asc_tables
(braket
l_int|1
)braket
op_assign
id|asc_table
suffix:semicolon
id|asc_tables_size
(braket
l_int|1
)braket
op_assign
id|asc_table_size
suffix:semicolon
id|num_asc_tables
op_assign
l_int|2
suffix:semicolon
id|sense_tables
(braket
l_int|0
)braket
op_assign
id|quirk-&gt;sense_key_info
suffix:semicolon
id|sense_tables_size
(braket
l_int|0
)braket
op_assign
id|quirk-&gt;num_sense_keys
suffix:semicolon
id|sense_tables
(braket
l_int|1
)braket
op_assign
id|sense_key_table
suffix:semicolon
id|sense_tables_size
(braket
l_int|1
)braket
op_assign
id|sense_key_table_size
suffix:semicolon
id|num_sense_tables
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|asc_tables
(braket
l_int|0
)braket
op_assign
id|asc_table
suffix:semicolon
id|asc_tables_size
(braket
l_int|0
)braket
op_assign
id|asc_table_size
suffix:semicolon
id|num_asc_tables
op_assign
l_int|1
suffix:semicolon
id|sense_tables
(braket
l_int|0
)braket
op_assign
id|sense_key_table
suffix:semicolon
id|sense_tables_size
(braket
l_int|0
)braket
op_assign
id|sense_key_table_size
suffix:semicolon
id|num_sense_tables
op_assign
l_int|1
suffix:semicolon
)brace
id|asc_ascq.asc
op_assign
id|asc
suffix:semicolon
id|asc_ascq.ascq
op_assign
id|ascq
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
id|num_asc_tables
suffix:semicolon
id|i
op_increment
)paren
(brace
r_void
op_star
id|found_entry
suffix:semicolon
id|found_entry
op_assign
id|scsibsearch
c_func
(paren
op_amp
id|asc_ascq
comma
id|asc_tables
(braket
id|i
)braket
comma
id|asc_tables_size
(braket
id|i
)braket
comma
r_sizeof
(paren
op_star
op_star
id|asc_tables
)paren
comma
id|ascentrycomp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found_entry
)paren
(brace
op_star
id|asc_entry
op_assign
(paren
r_struct
id|asc_table_entry
op_star
)paren
id|found_entry
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_sense_tables
suffix:semicolon
id|i
op_increment
)paren
(brace
r_void
op_star
id|found_entry
suffix:semicolon
id|found_entry
op_assign
id|scsibsearch
c_func
(paren
op_amp
id|sense_key
comma
id|sense_tables
(braket
id|i
)braket
comma
id|sense_tables_size
(braket
id|i
)braket
comma
r_sizeof
(paren
op_star
op_star
id|sense_tables
)paren
comma
id|senseentrycomp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found_entry
)paren
(brace
op_star
id|sense_entry
op_assign
(paren
r_struct
id|sense_key_table_entry
op_star
)paren
id|found_entry
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_static
r_void
op_star
DECL|function|scsibsearch
id|scsibsearch
c_func
(paren
r_const
r_void
op_star
id|key
comma
r_const
r_void
op_star
id|base
comma
r_int
id|nmemb
comma
r_int
id|size
comma
r_int
(paren
op_star
id|compar
)paren
(paren
r_const
r_void
op_star
comma
r_const
r_void
op_star
)paren
)paren
(brace
r_const
r_void
op_star
id|entry
suffix:semicolon
id|u_int
id|l
suffix:semicolon
id|u_int
id|u
suffix:semicolon
id|u_int
id|m
suffix:semicolon
id|l
op_assign
op_minus
l_int|1
suffix:semicolon
id|u
op_assign
id|nmemb
suffix:semicolon
r_while
c_loop
(paren
id|l
op_plus
l_int|1
op_ne
id|u
)paren
(brace
id|m
op_assign
(paren
id|l
op_plus
id|u
)paren
op_div
l_int|2
suffix:semicolon
id|entry
op_assign
id|base
op_plus
id|m
op_star
id|size
suffix:semicolon
r_if
c_cond
(paren
id|compar
c_func
(paren
id|key
comma
id|entry
)paren
OG
l_int|0
)paren
id|l
op_assign
id|m
suffix:semicolon
r_else
id|u
op_assign
id|m
suffix:semicolon
)brace
id|entry
op_assign
id|base
op_plus
id|u
op_star
id|size
suffix:semicolon
r_if
c_cond
(paren
id|u
op_eq
id|nmemb
op_logical_or
id|compar
c_func
(paren
id|key
comma
id|entry
)paren
op_ne
l_int|0
)paren
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
(paren
(paren
r_void
op_star
)paren
id|entry
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Compare string with pattern, returning 0 on match.&n; * Short pattern matches trailing blanks in name,&n; * wildcard &squot;*&squot; in pattern matches rest of name,&n; * wildcard &squot;?&squot; matches a single non-space character.&n; */
r_static
r_int
DECL|function|cam_strmatch
id|cam_strmatch
c_func
(paren
r_const
r_uint8
op_star
id|str
comma
r_const
r_uint8
op_star
id|pattern
comma
r_int
id|str_len
)paren
(brace
r_while
c_loop
(paren
op_star
id|pattern
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
id|str_len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_star
id|pattern
op_eq
l_char|&squot;*&squot;
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|pattern
op_ne
op_star
id|str
)paren
op_logical_and
(paren
op_star
id|pattern
op_ne
l_char|&squot;?&squot;
op_logical_or
op_star
id|str
op_eq
l_char|&squot; &squot;
)paren
)paren
(brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|pattern
op_increment
suffix:semicolon
id|str
op_increment
suffix:semicolon
id|str_len
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|str_len
OG
l_int|0
op_logical_and
op_star
id|str
op_increment
op_eq
l_char|&squot; &squot;
)paren
id|str_len
op_decrement
suffix:semicolon
r_return
(paren
id|str_len
)paren
suffix:semicolon
)brace
r_static
id|caddr_t
DECL|function|cam_quirkmatch
id|cam_quirkmatch
c_func
(paren
id|caddr_t
id|target
comma
id|caddr_t
id|quirk_table
comma
r_int
id|num_entries
comma
r_int
id|entry_size
comma
id|cam_quirkmatch_t
op_star
id|comp_func
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|num_entries
OG
l_int|0
suffix:semicolon
id|num_entries
op_decrement
comma
id|quirk_table
op_add_assign
id|entry_size
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|comp_func
)paren
(paren
id|target
comma
id|quirk_table
)paren
op_eq
l_int|0
)paren
r_return
(paren
id|quirk_table
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_void
DECL|function|aic_sense_desc
id|aic_sense_desc
c_func
(paren
r_int
id|sense_key
comma
r_int
id|asc
comma
r_int
id|ascq
comma
r_struct
id|scsi_inquiry_data
op_star
id|inq_data
comma
r_const
r_char
op_star
op_star
id|sense_key_desc
comma
r_const
r_char
op_star
op_star
id|asc_desc
)paren
(brace
r_const
r_struct
id|asc_table_entry
op_star
id|asc_entry
suffix:semicolon
r_const
r_struct
id|sense_key_table_entry
op_star
id|sense_entry
suffix:semicolon
id|fetchtableentries
c_func
(paren
id|sense_key
comma
id|asc
comma
id|ascq
comma
id|inq_data
comma
op_amp
id|sense_entry
comma
op_amp
id|asc_entry
)paren
suffix:semicolon
op_star
id|sense_key_desc
op_assign
id|sense_entry-&gt;desc
suffix:semicolon
r_if
c_cond
(paren
id|asc_entry
op_ne
l_int|NULL
)paren
op_star
id|asc_desc
op_assign
id|asc_entry-&gt;desc
suffix:semicolon
r_else
r_if
c_cond
(paren
id|asc
op_ge
l_int|0x80
op_logical_and
id|asc
op_le
l_int|0xff
)paren
op_star
id|asc_desc
op_assign
l_string|&quot;Vendor Specific ASC&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ascq
op_ge
l_int|0x80
op_logical_and
id|ascq
op_le
l_int|0xff
)paren
op_star
id|asc_desc
op_assign
l_string|&quot;Vendor Specific ASCQ&quot;
suffix:semicolon
r_else
op_star
id|asc_desc
op_assign
l_string|&quot;Reserved ASC/ASCQ pair&quot;
suffix:semicolon
)brace
multiline_comment|/*&n; * Given sense and device type information, return the appropriate action.&n; * If we do not understand the specific error as identified by the ASC/ASCQ&n; * pair, fall back on the more generic actions derived from the sense key.&n; */
id|aic_sense_action
DECL|function|aic_sense_error_action
id|aic_sense_error_action
c_func
(paren
r_struct
id|scsi_sense_data
op_star
id|sense_data
comma
r_struct
id|scsi_inquiry_data
op_star
id|inq_data
comma
r_uint32
id|sense_flags
)paren
(brace
r_const
r_struct
id|asc_table_entry
op_star
id|asc_entry
suffix:semicolon
r_const
r_struct
id|sense_key_table_entry
op_star
id|sense_entry
suffix:semicolon
r_int
id|error_code
comma
id|sense_key
comma
id|asc
comma
id|ascq
suffix:semicolon
id|aic_sense_action
id|action
suffix:semicolon
id|scsi_extract_sense
c_func
(paren
id|sense_data
comma
op_amp
id|error_code
comma
op_amp
id|sense_key
comma
op_amp
id|asc
comma
op_amp
id|ascq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error_code
op_eq
id|SSD_DEFERRED_ERROR
)paren
(brace
multiline_comment|/*&n;&t;&t; * XXX dufault@FreeBSD.org&n;&t;&t; * This error doesn&squot;t relate to the command associated&n;&t;&t; * with this request sense.  A deferred error is an error&n;&t;&t; * for a command that has already returned GOOD status&n;&t;&t; * (see SCSI2 8.2.14.2).&n;&t;&t; *&n;&t;&t; * By my reading of that section, it looks like the current&n;&t;&t; * command has been cancelled, we should now clean things up&n;&t;&t; * (hopefully recovering any lost data) and then retry the&n;&t;&t; * current command.  There are two easy choices, both wrong:&n;&t;&t; *&n;&t;&t; * 1. Drop through (like we had been doing), thus treating&n;&t;&t; *    this as if the error were for the current command and&n;&t;&t; *    return and stop the current command.&n;&t;&t; * &n;&t;&t; * 2. Issue a retry (like I made it do) thus hopefully&n;&t;&t; *    recovering the current transfer, and ignoring the&n;&t;&t; *    fact that we&squot;ve dropped a command.&n;&t;&t; *&n;&t;&t; * These should probably be handled in a device specific&n;&t;&t; * sense handler or punted back up to a user mode daemon&n;&t;&t; */
id|action
op_assign
id|SS_RETRY
op_or
id|SSQ_DECREMENT_COUNT
op_or
id|SSQ_PRINT_SENSE
suffix:semicolon
)brace
r_else
(brace
id|fetchtableentries
c_func
(paren
id|sense_key
comma
id|asc
comma
id|ascq
comma
id|inq_data
comma
op_amp
id|sense_entry
comma
op_amp
id|asc_entry
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Override the &squot;No additional Sense&squot; entry (0,0)&n;&t;&t; * with the error action of the sense key.&n;&t;&t; */
r_if
c_cond
(paren
id|asc_entry
op_ne
l_int|NULL
op_logical_and
(paren
id|asc
op_ne
l_int|0
op_logical_or
id|ascq
op_ne
l_int|0
)paren
)paren
id|action
op_assign
id|asc_entry-&gt;action
suffix:semicolon
r_else
id|action
op_assign
id|sense_entry-&gt;action
suffix:semicolon
r_if
c_cond
(paren
id|sense_key
op_eq
id|SSD_KEY_RECOVERED_ERROR
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The action succeeded but the device wants&n;&t;&t;&t; * the user to know that some recovery action&n;&t;&t;&t; * was required.&n;&t;&t;&t; */
id|action
op_and_assign
op_complement
(paren
id|SS_MASK
op_or
id|SSQ_MASK
op_or
id|SS_ERRMASK
)paren
suffix:semicolon
id|action
op_or_assign
id|SS_NOP
op_or
id|SSQ_PRINT_SENSE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sense_key
op_eq
id|SSD_KEY_ILLEGAL_REQUEST
)paren
(brace
r_if
c_cond
(paren
(paren
id|sense_flags
op_amp
id|SF_QUIET_IR
)paren
op_ne
l_int|0
)paren
id|action
op_and_assign
op_complement
id|SSQ_PRINT_SENSE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sense_key
op_eq
id|SSD_KEY_UNIT_ATTENTION
)paren
(brace
r_if
c_cond
(paren
(paren
id|sense_flags
op_amp
id|SF_RETRY_UA
)paren
op_ne
l_int|0
op_logical_and
(paren
id|action
op_amp
id|SS_MASK
)paren
op_eq
id|SS_FAIL
)paren
(brace
id|action
op_and_assign
op_complement
(paren
id|SS_MASK
op_or
id|SSQ_MASK
)paren
suffix:semicolon
id|action
op_or_assign
id|SS_RETRY
op_or
id|SSQ_DECREMENT_COUNT
op_or
id|SSQ_PRINT_SENSE
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
(paren
id|sense_flags
op_amp
id|SF_PRINT_ALWAYS
)paren
op_ne
l_int|0
)paren
id|action
op_or_assign
id|SSQ_PRINT_SENSE
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|sense_flags
op_amp
id|SF_NO_PRINT
)paren
op_ne
l_int|0
)paren
id|action
op_and_assign
op_complement
id|SSQ_PRINT_SENSE
suffix:semicolon
r_return
(paren
id|action
)paren
suffix:semicolon
)brace
multiline_comment|/*      &n; * Try make as good a match as possible with&n; * available sub drivers&n; */
r_int
DECL|function|aic_inquiry_match
id|aic_inquiry_match
c_func
(paren
id|caddr_t
id|inqbuffer
comma
id|caddr_t
id|table_entry
)paren
(brace
r_struct
id|scsi_inquiry_pattern
op_star
id|entry
suffix:semicolon
r_struct
id|scsi_inquiry_data
op_star
id|inq
suffix:semicolon
id|entry
op_assign
(paren
r_struct
id|scsi_inquiry_pattern
op_star
)paren
id|table_entry
suffix:semicolon
id|inq
op_assign
(paren
r_struct
id|scsi_inquiry_data
op_star
)paren
id|inqbuffer
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|SID_TYPE
c_func
(paren
id|inq
)paren
op_eq
id|entry-&gt;type
)paren
op_logical_or
(paren
id|entry-&gt;type
op_eq
id|T_ANY
)paren
)paren
op_logical_and
(paren
id|SID_IS_REMOVABLE
c_func
(paren
id|inq
)paren
ques
c_cond
id|entry-&gt;media_type
op_amp
id|SIP_MEDIA_REMOVABLE
suffix:colon
id|entry-&gt;media_type
op_amp
id|SIP_MEDIA_FIXED
)paren
op_logical_and
(paren
id|cam_strmatch
c_func
(paren
id|inq-&gt;vendor
comma
id|entry-&gt;vendor
comma
r_sizeof
(paren
id|inq-&gt;vendor
)paren
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|cam_strmatch
c_func
(paren
id|inq-&gt;product
comma
id|entry-&gt;product
comma
r_sizeof
(paren
id|inq-&gt;product
)paren
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|cam_strmatch
c_func
(paren
id|inq-&gt;revision
comma
id|entry-&gt;revision
comma
r_sizeof
(paren
id|inq-&gt;revision
)paren
)paren
op_eq
l_int|0
)paren
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Table of syncrates that don&squot;t follow the &quot;divisible by 4&quot;&n; * rule. This table will be expanded in future SCSI specs.&n; */
r_static
r_struct
(brace
DECL|member|period_factor
id|u_int
id|period_factor
suffix:semicolon
DECL|member|period
id|u_int
id|period
suffix:semicolon
multiline_comment|/* in 100ths of ns */
DECL|variable|scsi_syncrates
)brace
id|scsi_syncrates
(braket
)braket
op_assign
(brace
(brace
l_int|0x08
comma
l_int|625
)brace
comma
multiline_comment|/* FAST-160 */
(brace
l_int|0x09
comma
l_int|1250
)brace
comma
multiline_comment|/* FAST-80 */
(brace
l_int|0x0a
comma
l_int|2500
)brace
comma
multiline_comment|/* FAST-40 40MHz */
(brace
l_int|0x0b
comma
l_int|3030
)brace
comma
multiline_comment|/* FAST-40 33MHz */
(brace
l_int|0x0c
comma
l_int|5000
)brace
multiline_comment|/* FAST-20 */
)brace
suffix:semicolon
multiline_comment|/*&n; * Return the frequency in kHz corresponding to the given&n; * sync period factor.&n; */
id|u_int
DECL|function|aic_calc_syncsrate
id|aic_calc_syncsrate
c_func
(paren
id|u_int
id|period_factor
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|num_syncrates
suffix:semicolon
id|num_syncrates
op_assign
r_sizeof
(paren
id|scsi_syncrates
)paren
op_div
r_sizeof
(paren
id|scsi_syncrates
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* See if the period is in the &quot;exception&quot; table */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_syncrates
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|period_factor
op_eq
id|scsi_syncrates
(braket
id|i
)braket
dot
id|period_factor
)paren
(brace
multiline_comment|/* Period in kHz */
r_return
(paren
l_int|100000000
op_div
id|scsi_syncrates
(braket
id|i
)braket
dot
id|period
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Wasn&squot;t in the table, so use the standard&n;&t; * 4 times conversion.&n;&t; */
r_return
(paren
l_int|10000000
op_div
(paren
id|period_factor
op_star
l_int|4
op_star
l_int|10
)paren
)paren
suffix:semicolon
)brace
eof
