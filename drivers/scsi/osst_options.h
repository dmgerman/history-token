multiline_comment|/*&n;   The compile-time configurable defaults for the Linux SCSI tape driver.&n;&n;   Copyright 1995 Kai Makisara.&n;   &n;   Last modified: Wed Sep  2 21:24:07 1998 by root@home&n;   &n;   Changed (and renamed) for OnStream SCSI drives garloff@suse.de&n;   2000-06-21&n;&n;   $Header: /home/cvsroot/Driver/osst_options.h,v 1.5 2001/01/07 22:19:15 riede Exp $&n;*/
macro_line|#ifndef _OSST_OPTIONS_H
DECL|macro|_OSST_OPTIONS_H
mdefine_line|#define _OSST_OPTIONS_H
multiline_comment|/* The minimum limit for the number of SCSI tape devices is determined by&n;   OSST_MAX_TAPES. If the number of tape devices and the &quot;slack&quot; defined by&n;   OSST_EXTRA_DEVS exceeds OSST_MAX_TAPES, the large number is used. */
DECL|macro|OSST_MAX_TAPES
mdefine_line|#define OSST_MAX_TAPES 4
multiline_comment|/* If OSST_IN_FILE_POS is nonzero, the driver positions the tape after the&n;   record been read by the user program even if the tape has moved further&n;   because of buffered reads. Should be set to zero to support also drives&n;   that can&squot;t space backwards over records. NOTE: The tape will be&n;   spaced backwards over an &quot;accidentally&quot; crossed filemark in any case. */
DECL|macro|OSST_IN_FILE_POS
mdefine_line|#define OSST_IN_FILE_POS 1
multiline_comment|/* The tape driver buffer size in kilobytes. */
multiline_comment|/* Don&squot;t change, as this is the HW blocksize */
DECL|macro|OSST_BUFFER_BLOCKS
mdefine_line|#define OSST_BUFFER_BLOCKS 32
multiline_comment|/* The number of kilobytes of data in the buffer that triggers an&n;   asynchronous write in fixed block mode. See also OSST_ASYNC_WRITES&n;   below. */
DECL|macro|OSST_WRITE_THRESHOLD_BLOCKS
mdefine_line|#define OSST_WRITE_THRESHOLD_BLOCKS 32
multiline_comment|/* OSST_EOM_RESERVE defines the number of frames are kept in reserve for&n; *  * write error recovery when writing near end of medium. ENOSPC is returned&n; *   * when write() is called and the tape write position is within this number&n; *    * of blocks from the tape capacity. */
DECL|macro|OSST_EOM_RESERVE
mdefine_line|#define OSST_EOM_RESERVE 300
multiline_comment|/* The maximum number of tape buffers the driver allocates. The number&n;   is also constrained by the number of drives detected. Determines the&n;   maximum number of concurrently active tape drives. */
DECL|macro|OSST_MAX_BUFFERS
mdefine_line|#define OSST_MAX_BUFFERS OSST_MAX_TAPES 
multiline_comment|/* Maximum number of scatter/gather segments */
multiline_comment|/* Fit one buffer in pages and add one for the AUX header */
DECL|macro|OSST_MAX_SG
mdefine_line|#define OSST_MAX_SG      (((OSST_BUFFER_BLOCKS*1024) / PAGE_SIZE) + 1)
multiline_comment|/* The number of scatter/gather segments to allocate at first try (must be&n;   smaller or equal to the maximum). */
DECL|macro|OSST_FIRST_SG
mdefine_line|#define OSST_FIRST_SG    ((OSST_BUFFER_BLOCKS*1024) / PAGE_SIZE)
multiline_comment|/* The size of the first scatter/gather segments (determines the maximum block&n;   size for SCSI adapters not supporting scatter/gather). The default is set&n;   to try to allocate the buffer as one chunk. */
DECL|macro|OSST_FIRST_ORDER
mdefine_line|#define OSST_FIRST_ORDER  5
multiline_comment|/* The following lines define defaults for properties that can be set&n;   separately for each drive using the MTSTOPTIONS ioctl. */
multiline_comment|/* If OSST_TWO_FM is non-zero, the driver writes two filemarks after a&n;   file being written. Some drives can&squot;t handle two filemarks at the&n;   end of data. */
DECL|macro|OSST_TWO_FM
mdefine_line|#define OSST_TWO_FM 0
multiline_comment|/* If OSST_BUFFER_WRITES is non-zero, writes in fixed block mode are&n;   buffered until the driver buffer is full or asynchronous write is&n;   triggered. */
DECL|macro|OSST_BUFFER_WRITES
mdefine_line|#define OSST_BUFFER_WRITES 1
multiline_comment|/* If OSST_ASYNC_WRITES is non-zero, the SCSI write command may be started&n;   without waiting for it to finish. May cause problems in multiple&n;   tape backups. */
DECL|macro|OSST_ASYNC_WRITES
mdefine_line|#define OSST_ASYNC_WRITES 1
multiline_comment|/* If OSST_READ_AHEAD is non-zero, blocks are read ahead in fixed block&n;   mode. */
DECL|macro|OSST_READ_AHEAD
mdefine_line|#define OSST_READ_AHEAD 1
multiline_comment|/* If OSST_AUTO_LOCK is non-zero, the drive door is locked at the first&n;   read or write command after the device is opened. The door is opened&n;   when the device is closed. */
DECL|macro|OSST_AUTO_LOCK
mdefine_line|#define OSST_AUTO_LOCK 0
multiline_comment|/* If OSST_FAST_MTEOM is non-zero, the MTEOM ioctl is done using the&n;   direct SCSI command. The file number status is lost but this method&n;   is fast with some drives. Otherwise MTEOM is done by spacing over&n;   files and the file number status is retained. */
DECL|macro|OSST_FAST_MTEOM
mdefine_line|#define OSST_FAST_MTEOM 0
multiline_comment|/* If OSST_SCSI2LOGICAL is nonzero, the logical block addresses are used for&n;   MTIOCPOS and MTSEEK by default. Vendor addresses are used if OSST_SCSI2LOGICAL&n;   is zero. */
DECL|macro|OSST_SCSI2LOGICAL
mdefine_line|#define OSST_SCSI2LOGICAL 0
multiline_comment|/* If OSST_SYSV is non-zero, the tape behaves according to the SYS V semantics.&n;   The default is BSD semantics. */
DECL|macro|OSST_SYSV
mdefine_line|#define OSST_SYSV 0
macro_line|#endif
eof
