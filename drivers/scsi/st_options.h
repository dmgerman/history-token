multiline_comment|/*&n;   The compile-time configurable defaults for the Linux SCSI tape driver.&n;&n;   Copyright 1995-2000 Kai Makisara.&n;&n;   Last modified: Sat Apr 22 14:47:02 2000 by makisara@kai.makisara.local&n;*/
macro_line|#ifndef _ST_OPTIONS_H
DECL|macro|_ST_OPTIONS_H
mdefine_line|#define _ST_OPTIONS_H
multiline_comment|/* The driver does not wait for some operations to finish before returning&n;   to the user program if ST_NOWAIT is non-zero. This helps if the SCSI&n;   adapter does not support multiple outstanding commands. However, the user&n;   should not give a new tape command before the previous one has finished. */
DECL|macro|ST_NOWAIT
mdefine_line|#define ST_NOWAIT 0
multiline_comment|/* If ST_IN_FILE_POS is nonzero, the driver positions the tape after the&n;   record been read by the user program even if the tape has moved further&n;   because of buffered reads. Should be set to zero to support also drives&n;   that can&squot;t space backwards over records. NOTE: The tape will be&n;   spaced backwards over an &quot;accidentally&quot; crossed filemark in any case. */
DECL|macro|ST_IN_FILE_POS
mdefine_line|#define ST_IN_FILE_POS 0
multiline_comment|/* If ST_RECOVERED_WRITE_FATAL is non-zero, recovered errors while writing&n;   are considered &quot;hard errors&quot;. */
DECL|macro|ST_RECOVERED_WRITE_FATAL
mdefine_line|#define ST_RECOVERED_WRITE_FATAL 0
multiline_comment|/* The &quot;guess&quot; for the block size for devices that don&squot;t support MODE&n;   SENSE. */
DECL|macro|ST_DEFAULT_BLOCK
mdefine_line|#define ST_DEFAULT_BLOCK 0
multiline_comment|/* The tape driver buffer size in kilobytes. Must be non-zero. */
DECL|macro|ST_BUFFER_BLOCKS
mdefine_line|#define ST_BUFFER_BLOCKS 32
multiline_comment|/* The number of kilobytes of data in the buffer that triggers an&n;   asynchronous write in fixed block mode. See also ST_ASYNC_WRITES&n;   below. */
DECL|macro|ST_WRITE_THRESHOLD_BLOCKS
mdefine_line|#define ST_WRITE_THRESHOLD_BLOCKS 30
multiline_comment|/* The maximum number of tape buffers the driver tries to allocate at &n;   driver initialisation. The number is also constrained by the number&n;   of drives detected. If more buffers are needed, they are allocated&n;   at run time and freed after use. */
DECL|macro|ST_MAX_BUFFERS
mdefine_line|#define ST_MAX_BUFFERS 4
multiline_comment|/* Maximum number of scatter/gather segments */
DECL|macro|ST_MAX_SG
mdefine_line|#define ST_MAX_SG      16
multiline_comment|/* The number of scatter/gather segments to allocate at first try (must be&n;   smaller or equal to the maximum). */
DECL|macro|ST_FIRST_SG
mdefine_line|#define ST_FIRST_SG    8
multiline_comment|/* The size of the first scatter/gather segments (determines the maximum block&n;   size for SCSI adapters not supporting scatter/gather). The default is set&n;   to try to allocate the buffer as one chunk. */
DECL|macro|ST_FIRST_ORDER
mdefine_line|#define ST_FIRST_ORDER  5
multiline_comment|/* The following lines define defaults for properties that can be set&n;   separately for each drive using the MTSTOPTIONS ioctl. */
multiline_comment|/* If ST_TWO_FM is non-zero, the driver writes two filemarks after a&n;   file being written. Some drives can&squot;t handle two filemarks at the&n;   end of data. */
DECL|macro|ST_TWO_FM
mdefine_line|#define ST_TWO_FM 0
multiline_comment|/* If ST_BUFFER_WRITES is non-zero, writes in fixed block mode are&n;   buffered until the driver buffer is full or asynchronous write is&n;   triggered. May make detection of End-Of-Medium early enough fail. */
DECL|macro|ST_BUFFER_WRITES
mdefine_line|#define ST_BUFFER_WRITES 1
multiline_comment|/* If ST_ASYNC_WRITES is non-zero, the SCSI write command may be started&n;   without waiting for it to finish. May cause problems in multiple&n;   tape backups. */
DECL|macro|ST_ASYNC_WRITES
mdefine_line|#define ST_ASYNC_WRITES 1
multiline_comment|/* If ST_READ_AHEAD is non-zero, blocks are read ahead in fixed block&n;   mode. */
DECL|macro|ST_READ_AHEAD
mdefine_line|#define ST_READ_AHEAD 1
multiline_comment|/* If ST_AUTO_LOCK is non-zero, the drive door is locked at the first&n;   read or write command after the device is opened. The door is opened&n;   when the device is closed. */
DECL|macro|ST_AUTO_LOCK
mdefine_line|#define ST_AUTO_LOCK 0
multiline_comment|/* If ST_FAST_MTEOM is non-zero, the MTEOM ioctl is done using the&n;   direct SCSI command. The file number status is lost but this method&n;   is fast with some drives. Otherwise MTEOM is done by spacing over&n;   files and the file number status is retained. */
DECL|macro|ST_FAST_MTEOM
mdefine_line|#define ST_FAST_MTEOM 0
multiline_comment|/* If ST_SCSI2LOGICAL is nonzero, the logical block addresses are used for&n;   MTIOCPOS and MTSEEK by default. Vendor addresses are used if ST_SCSI2LOGICAL&n;   is zero. */
DECL|macro|ST_SCSI2LOGICAL
mdefine_line|#define ST_SCSI2LOGICAL 0
multiline_comment|/* If ST_SYSV is non-zero, the tape behaves according to the SYS V semantics.&n;   The default is BSD semantics. */
DECL|macro|ST_SYSV
mdefine_line|#define ST_SYSV 0
macro_line|#endif
eof
