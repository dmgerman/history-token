multiline_comment|/*&n; * logfile.h - Defines for NTFS kernel journal ($LogFile) handling.  Part of&n; *&t;       the Linux-NTFS project.&n; *&n; * Copyright (c) 2000-2004 Anton Altaparmakov&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_LOGFILE_H
DECL|macro|_LINUX_NTFS_LOGFILE_H
mdefine_line|#define _LINUX_NTFS_LOGFILE_H
macro_line|#ifdef NTFS_RW
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;types.h&quot;
macro_line|#include &quot;endian.h&quot;
macro_line|#include &quot;layout.h&quot;
multiline_comment|/*&n; * Journal ($LogFile) organization:&n; *&n; * Two restart areas present in the first two pages (restart pages, one restart&n; * area in each page).  When the volume is dismounted they should be identical,&n; * except for the update sequence array which usually has a different update&n; * sequence number.&n; *&n; * These are followed by log records organized in pages headed by a log record&n; * header going up to log file size.  Not all pages contain log records when a&n; * volume is first formatted, but as the volume ages, all records will be used.&n; * When the log file fills up, the records at the beginning are purged (by&n; * modifying the oldest_lsn to a higher value presumably) and writing begins&n; * at the beginning of the file.  Effectively, the log file is viewed as a&n; * circular entity.&n; *&n; * NOTE: Windows NT, 2000, and XP all use log file version 1.1 but they accept&n; * versions &lt;= 1.x, including 0.-1.  (Yes, that is a minus one in there!)  We&n; * probably only want to support 1.1 as this seems to be the current version&n; * and we don&squot;t know how that differs from the older versions.  The only&n; * exception is if the journal is clean as marked by the two restart pages&n; * then it doesn&squot;t matter whether we are on an earlier version.  We can just&n; * reinitialize the logfile and start again with version 1.1.&n; */
multiline_comment|/* Some $LogFile related constants. */
DECL|macro|MaxLogFileSize
mdefine_line|#define MaxLogFileSize&t;&t;0x100000000ULL
DECL|macro|DefaultLogPageSize
mdefine_line|#define DefaultLogPageSize&t;4096
DECL|macro|MinLogRecordPages
mdefine_line|#define MinLogRecordPages&t;48
multiline_comment|/*&n; * Log file restart page header (begins the restart area).&n; */
r_typedef
r_struct
(brace
multiline_comment|/*Ofs*/
multiline_comment|/*  0&t;NTFS_RECORD; -- Unfolded here as gcc doesn&squot;t like unnamed structs. */
DECL|member|magic
multiline_comment|/*  0*/
id|NTFS_RECORD_TYPE
id|magic
suffix:semicolon
multiline_comment|/* The magic is &quot;RSTR&quot;. */
DECL|member|usa_ofs
multiline_comment|/*  4*/
id|le16
id|usa_ofs
suffix:semicolon
multiline_comment|/* See NTFS_RECORD definition in layout.h.&n;&t;&t;&t;&t;   When creating, set this to be immediately&n;&t;&t;&t;&t;   after this header structure (without any&n;&t;&t;&t;&t;   alignment). */
DECL|member|usa_count
multiline_comment|/*  6*/
id|le16
id|usa_count
suffix:semicolon
multiline_comment|/* See NTFS_RECORD definition in layout.h. */
DECL|member|chkdsk_lsn
multiline_comment|/*  8*/
id|leLSN
id|chkdsk_lsn
suffix:semicolon
multiline_comment|/* The last log file sequence number found by&n;&t;&t;&t;&t;   chkdsk.  Only used when the magic is changed&n;&t;&t;&t;&t;   to &quot;CHKD&quot;.  Otherwise this is zero. */
DECL|member|system_page_size
multiline_comment|/* 16*/
id|le32
id|system_page_size
suffix:semicolon
multiline_comment|/* Byte size of system pages when the log file&n;&t;&t;&t;&t;   was created, has to be &gt;= 512 and a power of&n;&t;&t;&t;&t;   2.  Use this to calculate the required size&n;&t;&t;&t;&t;   of the usa (usa_count) and add it to usa_ofs.&n;&t;&t;&t;&t;   Then verify that the result is less than the&n;&t;&t;&t;&t;   value of the restart_area_offset. */
DECL|member|log_page_size
multiline_comment|/* 20*/
id|le32
id|log_page_size
suffix:semicolon
multiline_comment|/* Byte size of log file pages, has to be &gt;=&n;&t;&t;&t;&t;   512 and a power of 2.  The default is 4096&n;&t;&t;&t;&t;   and is used when the system page size is&n;&t;&t;&t;&t;   between 4096 and 8192.  Otherwise this is&n;&t;&t;&t;&t;   set to the system page size instead. */
DECL|member|restart_area_offset
multiline_comment|/* 24*/
id|le16
id|restart_area_offset
suffix:semicolon
multiline_comment|/* Byte offset from the start of this header to&n;&t;&t;&t;&t;   the RESTART_AREA.  Value has to be aligned&n;&t;&t;&t;&t;   to 8-byte boundary.  When creating, set this&n;&t;&t;&t;&t;   to be after the usa. */
DECL|member|minor_ver
multiline_comment|/* 26*/
id|sle16
id|minor_ver
suffix:semicolon
multiline_comment|/* Log file minor version.  Only check if major&n;&t;&t;&t;&t;   version is 1. */
DECL|member|major_ver
multiline_comment|/* 28*/
id|sle16
id|major_ver
suffix:semicolon
multiline_comment|/* Log file major version.  We only support&n;&t;&t;&t;&t;   version 1.1. */
multiline_comment|/* sizeof() = 30 (0x1e) bytes */
DECL|typedef|RESTART_PAGE_HEADER
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|RESTART_PAGE_HEADER
suffix:semicolon
multiline_comment|/*&n; * Constant for the log client indices meaning that there are no client records&n; * in this particular client array.  Also inside the client records themselves,&n; * this means that there are no client records preceding or following this one.&n; */
DECL|macro|LOGFILE_NO_CLIENT
mdefine_line|#define LOGFILE_NO_CLIENT&t;const_cpu_to_le16(0xffff)
DECL|macro|LOGFILE_NO_CLIENT_CPU
mdefine_line|#define LOGFILE_NO_CLIENT_CPU&t;0xffff
multiline_comment|/*&n; * These are the so far known RESTART_AREA_* flags (16-bit) which contain&n; * information about the log file in which they are present.&n; */
DECL|macro|RESTART_VOLUME_IS_CLEAN
mdefine_line|#define RESTART_VOLUME_IS_CLEAN&t;const_cpu_to_le16(0x0002)
DECL|typedef|RESTART_AREA_FLAGS
r_typedef
id|le16
id|RESTART_AREA_FLAGS
suffix:semicolon
multiline_comment|/*&n; * Log file restart area record.  The offset of this record is found by adding&n; * the offset of the RESTART_PAGE_HEADER to the restart_area_offset value found&n; * in it.  See notes at restart_area_offset above.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*Ofs*/
DECL|member|current_lsn
multiline_comment|/*  0*/
id|leLSN
id|current_lsn
suffix:semicolon
multiline_comment|/* The current, i.e. last LSN inside the log&n;&t;&t;&t;&t;   when the restart area was last written.&n;&t;&t;&t;&t;   This happens often but what is the interval?&n;&t;&t;&t;&t;   Is it just fixed time or is it every time a&n;&t;&t;&t;&t;   check point is written or somethine else?&n;&t;&t;&t;&t;   On create set to 0. */
DECL|member|log_clients
multiline_comment|/*  8*/
id|le16
id|log_clients
suffix:semicolon
multiline_comment|/* Number of log client records in the array of&n;&t;&t;&t;&t;   log client records which follows this&n;&t;&t;&t;&t;   restart area.  Must be 1.  */
DECL|member|client_free_list
multiline_comment|/* 10*/
id|le16
id|client_free_list
suffix:semicolon
multiline_comment|/* The index of the first free log client record&n;&t;&t;&t;&t;   in the array of log client records.&n;&t;&t;&t;&t;   LOGFILE_NO_CLIENT means that there are no&n;&t;&t;&t;&t;   free log client records in the array.&n;&t;&t;&t;&t;   If != LOGFILE_NO_CLIENT, check that&n;&t;&t;&t;&t;   log_clients &gt; client_free_list.  On Win2k&n;&t;&t;&t;&t;   and presumably earlier, on a clean volume&n;&t;&t;&t;&t;   this is != LOGFILE_NO_CLIENT, and it should&n;&t;&t;&t;&t;   be 0, i.e. the first (and only) client&n;&t;&t;&t;&t;   record is free and thus the logfile is&n;&t;&t;&t;&t;   closed and hence clean.  A dirty volume&n;&t;&t;&t;&t;   would have left the logfile open and hence&n;&t;&t;&t;&t;   this would be LOGFILE_NO_CLIENT.  On WinXP&n;&t;&t;&t;&t;   and presumably later, the logfile is always&n;&t;&t;&t;&t;   open, even on clean shutdown so this should&n;&t;&t;&t;&t;   always be LOGFILE_NO_CLIENT. */
DECL|member|client_in_use_list
multiline_comment|/* 12*/
id|le16
id|client_in_use_list
suffix:semicolon
multiline_comment|/* The index of the first in-use log client&n;&t;&t;&t;&t;   record in the array of log client records.&n;&t;&t;&t;&t;   LOGFILE_NO_CLIENT means that there are no&n;&t;&t;&t;&t;   in-use log client records in the array.  If&n;&t;&t;&t;&t;   != LOGFILE_NO_CLIENT check that log_clients&n;&t;&t;&t;&t;   &gt; client_in_use_list.  On Win2k and&n;&t;&t;&t;&t;   presumably earlier, on a clean volume this&n;&t;&t;&t;&t;   is LOGFILE_NO_CLIENT, i.e. there are no&n;&t;&t;&t;&t;   client records in use and thus the logfile&n;&t;&t;&t;&t;   is closed and hence clean.  A dirty volume&n;&t;&t;&t;&t;   would have left the logfile open and hence&n;&t;&t;&t;&t;   this would be != LOGFILE_NO_CLIENT, and it&n;&t;&t;&t;&t;   should be 0, i.e. the first (and only)&n;&t;&t;&t;&t;   client record is in use.  On WinXP and&n;&t;&t;&t;&t;   presumably later, the logfile is always&n;&t;&t;&t;&t;   open, even on clean shutdown so this should&n;&t;&t;&t;&t;   always be 0. */
DECL|member|flags
multiline_comment|/* 14*/
id|RESTART_AREA_FLAGS
id|flags
suffix:semicolon
multiline_comment|/* Flags modifying LFS behaviour.  On Win2k&n;&t;&t;&t;&t;   and presumably earlier this is always 0.  On&n;&t;&t;&t;&t;   WinXP and presumably later, if the logfile&n;&t;&t;&t;&t;   was shutdown cleanly, the second bit,&n;&t;&t;&t;&t;   RESTART_VOLUME_IS_CLEAN, is set.  This bit&n;&t;&t;&t;&t;   is cleared when the volume is mounted by&n;&t;&t;&t;&t;   WinXP and set when the volume is dismounted,&n;&t;&t;&t;&t;   thus if the logfile is dirty, this bit is&n;&t;&t;&t;&t;   clear.  Thus we don&squot;t need to check the&n;&t;&t;&t;&t;   Windows version to determine if the logfile&n;&t;&t;&t;&t;   is clean.  Instead if the logfile is closed,&n;&t;&t;&t;&t;   we know it must be clean.  If it is open and&n;&t;&t;&t;&t;   this bit is set, we also know it must be&n;&t;&t;&t;&t;   clean.  If on the other hand the logfile is&n;&t;&t;&t;&t;   open and this bit is clear, we can be almost&n;&t;&t;&t;&t;   certain that the logfile is dirty. */
DECL|member|seq_number_bits
multiline_comment|/* 16*/
id|le32
id|seq_number_bits
suffix:semicolon
multiline_comment|/* How many bits to use for the sequence&n;&t;&t;&t;&t;   number.  This is calculated as 67 - the&n;&t;&t;&t;&t;   number of bits required to store the logfile&n;&t;&t;&t;&t;   size in bytes and this can be used in with&n;&t;&t;&t;&t;   the specified file_size as a consistency&n;&t;&t;&t;&t;   check. */
DECL|member|restart_area_length
multiline_comment|/* 20*/
id|le16
id|restart_area_length
suffix:semicolon
multiline_comment|/* Length of the restart area including the&n;&t;&t;&t;&t;   client array.  Following checks required if&n;&t;&t;&t;&t;   version matches.  Otherwise, skip them.&n;&t;&t;&t;&t;   restart_area_offset + restart_area_length&n;&t;&t;&t;&t;   has to be &lt;= system_page_size.  Also,&n;&t;&t;&t;&t;   restart_area_length has to be &gt;=&n;&t;&t;&t;&t;   client_array_offset + (log_clients *&n;&t;&t;&t;&t;   sizeof(log client record)). */
DECL|member|client_array_offset
multiline_comment|/* 22*/
id|le16
id|client_array_offset
suffix:semicolon
multiline_comment|/* Offset from the start of this record to&n;&t;&t;&t;&t;   the first log client record if versions are&n;&t;&t;&t;&t;   matched.  When creating, set this to be&n;&t;&t;&t;&t;   after this restart area structure, aligned&n;&t;&t;&t;&t;   to 8-bytes boundary.  If the versions do not&n;&t;&t;&t;&t;   match, this is ignored and the offset is&n;&t;&t;&t;&t;   assumed to be (sizeof(RESTART_AREA) + 7) &amp;&n;&t;&t;&t;&t;   ~7, i.e. rounded up to first 8-byte&n;&t;&t;&t;&t;   boundary.  Either way, client_array_offset&n;&t;&t;&t;&t;   has to be aligned to an 8-byte boundary.&n;&t;&t;&t;&t;   Also, restart_area_offset +&n;&t;&t;&t;&t;   client_array_offset has to be &lt;= 510.&n;&t;&t;&t;&t;   Finally, client_array_offset + (log_clients&n;&t;&t;&t;&t;   * sizeof(log client record)) has to be &lt;=&n;&t;&t;&t;&t;   system_page_size.  On Win2k and presumably&n;&t;&t;&t;&t;   earlier, this is 0x30, i.e. immediately&n;&t;&t;&t;&t;   following this record.  On WinXP and&n;&t;&t;&t;&t;   presumably later, this is 0x40, i.e. there&n;&t;&t;&t;&t;   are 16 extra bytes between this record and&n;&t;&t;&t;&t;   the client array.  This probably means that&n;&t;&t;&t;&t;   the RESTART_AREA record is actually bigger&n;&t;&t;&t;&t;   in WinXP and later. */
DECL|member|file_size
multiline_comment|/* 24*/
id|sle64
id|file_size
suffix:semicolon
multiline_comment|/* Usable byte size of the log file.  If the&n;&t;&t;&t;&t;   restart_area_offset + the offset of the&n;&t;&t;&t;&t;   file_size are &gt; 510 then corruption has&n;&t;&t;&t;&t;   occured.  This is the very first check when&n;&t;&t;&t;&t;   starting with the restart_area as if it&n;&t;&t;&t;&t;   fails it means that some of the above values&n;&t;&t;&t;&t;   will be corrupted by the multi sector&n;&t;&t;&t;&t;   transfer protection.  The file_size has to&n;&t;&t;&t;&t;   be rounded down to be a multiple of the&n;&t;&t;&t;&t;   log_page_size in the RESTART_PAGE_HEADER and&n;&t;&t;&t;&t;   then it has to be at least big enough to&n;&t;&t;&t;&t;   store the two restart pages and 48 (0x30)&n;&t;&t;&t;&t;   log record pages. */
DECL|member|last_lsn_data_length
multiline_comment|/* 32*/
id|le32
id|last_lsn_data_length
suffix:semicolon
multiline_comment|/* Length of data of last LSN, not including&n;&t;&t;&t;&t;   the log record header.  On create set to&n;&t;&t;&t;&t;   0. */
DECL|member|log_record_header_length
multiline_comment|/* 36*/
id|le16
id|log_record_header_length
suffix:semicolon
multiline_comment|/* Byte size of the log record header.&n;&t;&t;&t;&t;   If the version matches then check that the&n;&t;&t;&t;&t;   value of log_record_header_length is a&n;&t;&t;&t;&t;   multiple of 8, i.e.&n;&t;&t;&t;&t;   (log_record_header_length + 7) &amp; ~7 ==&n;&t;&t;&t;&t;   log_record_header_length.  When creating set&n;&t;&t;&t;&t;   it to sizeof(LOG_RECORD_HEADER), aligned to&n;&t;&t;&t;&t;   8 bytes. */
DECL|member|log_page_data_offset
multiline_comment|/* 38*/
id|le16
id|log_page_data_offset
suffix:semicolon
multiline_comment|/* Offset to the start of data in a log record&n;&t;&t;&t;&t;   page.  Must be a multiple of 8.  On create&n;&t;&t;&t;&t;   set it to immediately after the update&n;&t;&t;&t;&t;   sequence array of the log record page. */
DECL|member|restart_log_open_count
multiline_comment|/* 40*/
id|le32
id|restart_log_open_count
suffix:semicolon
multiline_comment|/* A counter that gets incremented every&n;&t;&t;&t;&t;   time the logfile is restarted which happens&n;&t;&t;&t;&t;   at mount time when the logfile is opened.&n;&t;&t;&t;&t;   When creating set to a random value.  Win2k&n;&t;&t;&t;&t;   sets it to the low 32 bits of the current&n;&t;&t;&t;&t;   system time in NTFS format (see time.h). */
DECL|member|reserved
multiline_comment|/* 44*/
id|le32
id|reserved
suffix:semicolon
multiline_comment|/* Reserved/alignment to 8-byte boundary. */
multiline_comment|/* sizeof() = 48 (0x30) bytes */
DECL|typedef|RESTART_AREA
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|RESTART_AREA
suffix:semicolon
multiline_comment|/*&n; * Log client record.  The offset of this record is found by adding the offset&n; * of the RESTART_AREA to the client_array_offset value found in it.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*Ofs*/
DECL|member|oldest_lsn
multiline_comment|/*  0*/
id|leLSN
id|oldest_lsn
suffix:semicolon
multiline_comment|/* Oldest LSN needed by this client.  On create&n;&t;&t;&t;&t;   set to 0. */
DECL|member|client_restart_lsn
multiline_comment|/*  8*/
id|leLSN
id|client_restart_lsn
suffix:semicolon
multiline_comment|/* LSN at which this client needs to restart&n;&t;&t;&t;&t;   the volume, i.e. the current position within&n;&t;&t;&t;&t;   the log file.  At present, if clean this&n;&t;&t;&t;&t;   should = current_lsn in restart area but it&n;&t;&t;&t;&t;   probably also = current_lsn when dirty most&n;&t;&t;&t;&t;   of the time.  At create set to 0. */
DECL|member|prev_client
multiline_comment|/* 16*/
id|le16
id|prev_client
suffix:semicolon
multiline_comment|/* The offset to the previous log client record&n;&t;&t;&t;&t;   in the array of log client records.&n;&t;&t;&t;&t;   LOGFILE_NO_CLIENT means there is no previous&n;&t;&t;&t;&t;   client record, i.e. this is the first one.&n;&t;&t;&t;&t;   This is always LOGFILE_NO_CLIENT. */
DECL|member|next_client
multiline_comment|/* 18*/
id|le16
id|next_client
suffix:semicolon
multiline_comment|/* The offset to the next log client record in&n;&t;&t;&t;&t;   the array of log client records.&n;&t;&t;&t;&t;   LOGFILE_NO_CLIENT means there are no next&n;&t;&t;&t;&t;   client records, i.e. this is the last one.&n;&t;&t;&t;&t;   This is always LOGFILE_NO_CLIENT. */
DECL|member|seq_number
multiline_comment|/* 20*/
id|le16
id|seq_number
suffix:semicolon
multiline_comment|/* On Win2k and presumably earlier, this is set&n;&t;&t;&t;&t;   to zero every time the logfile is restarted&n;&t;&t;&t;&t;   and it is incremented when the logfile is&n;&t;&t;&t;&t;   closed at dismount time.  Thus it is 0 when&n;&t;&t;&t;&t;   dirty and 1 when clean.  On WinXP and&n;&t;&t;&t;&t;   presumably later, this is always 0. */
DECL|member|reserved
multiline_comment|/* 22*/
id|u8
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Reserved/alignment. */
DECL|member|client_name_length
multiline_comment|/* 28*/
id|le32
id|client_name_length
suffix:semicolon
multiline_comment|/* Length of client name in bytes.  Should&n;&t;&t;&t;&t;   always be 8. */
DECL|member|client_name
multiline_comment|/* 32*/
id|ntfschar
id|client_name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Name of the client in Unicode.  Should&n;&t;&t;&t;&t;   always be &quot;NTFS&quot; with the remaining bytes&n;&t;&t;&t;&t;   set to 0. */
multiline_comment|/* sizeof() = 160 (0xa0) bytes */
DECL|typedef|LOG_CLIENT_RECORD
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|LOG_CLIENT_RECORD
suffix:semicolon
r_extern
id|BOOL
id|ntfs_check_logfile
c_func
(paren
r_struct
id|inode
op_star
id|log_vi
)paren
suffix:semicolon
r_extern
id|BOOL
id|ntfs_is_logfile_clean
c_func
(paren
r_struct
id|inode
op_star
id|log_vi
)paren
suffix:semicolon
r_extern
id|BOOL
id|ntfs_empty_logfile
c_func
(paren
r_struct
id|inode
op_star
id|log_vi
)paren
suffix:semicolon
macro_line|#endif /* NTFS_RW */
macro_line|#endif /* _LINUX_NTFS_LOGFILE_H */
eof
