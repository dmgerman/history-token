macro_line|#ifndef _SCSI_LOGGING_H
DECL|macro|_SCSI_LOGGING_H
mdefine_line|#define _SCSI_LOGGING_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * This defines the scsi logging feature.  It is a means by which the user&n; * can select how much information they get about various goings on, and it&n; * can be really useful for fault tracing.  The logging word is divided into&n; * 8 nibbles, each of which describes a loglevel.  The division of things is&n; * somewhat arbitrary, and the division of the word could be changed if it&n; * were really needed for any reason.  The numbers below are the only place&n; * where these are specified.  For a first go-around, 3 bits is more than&n; * enough, since this gives 8 levels of logging (really 7, since 0 is always&n; * off).  Cutting to 2 bits might be wise at some point.&n; */
DECL|macro|SCSI_LOG_ERROR_SHIFT
mdefine_line|#define SCSI_LOG_ERROR_SHIFT              0
DECL|macro|SCSI_LOG_TIMEOUT_SHIFT
mdefine_line|#define SCSI_LOG_TIMEOUT_SHIFT            3
DECL|macro|SCSI_LOG_SCAN_SHIFT
mdefine_line|#define SCSI_LOG_SCAN_SHIFT               6
DECL|macro|SCSI_LOG_MLQUEUE_SHIFT
mdefine_line|#define SCSI_LOG_MLQUEUE_SHIFT            9
DECL|macro|SCSI_LOG_MLCOMPLETE_SHIFT
mdefine_line|#define SCSI_LOG_MLCOMPLETE_SHIFT         12
DECL|macro|SCSI_LOG_LLQUEUE_SHIFT
mdefine_line|#define SCSI_LOG_LLQUEUE_SHIFT            15
DECL|macro|SCSI_LOG_LLCOMPLETE_SHIFT
mdefine_line|#define SCSI_LOG_LLCOMPLETE_SHIFT         18
DECL|macro|SCSI_LOG_HLQUEUE_SHIFT
mdefine_line|#define SCSI_LOG_HLQUEUE_SHIFT            21
DECL|macro|SCSI_LOG_HLCOMPLETE_SHIFT
mdefine_line|#define SCSI_LOG_HLCOMPLETE_SHIFT         24
DECL|macro|SCSI_LOG_IOCTL_SHIFT
mdefine_line|#define SCSI_LOG_IOCTL_SHIFT              27
DECL|macro|SCSI_LOG_ERROR_BITS
mdefine_line|#define SCSI_LOG_ERROR_BITS               3
DECL|macro|SCSI_LOG_TIMEOUT_BITS
mdefine_line|#define SCSI_LOG_TIMEOUT_BITS             3
DECL|macro|SCSI_LOG_SCAN_BITS
mdefine_line|#define SCSI_LOG_SCAN_BITS                3
DECL|macro|SCSI_LOG_MLQUEUE_BITS
mdefine_line|#define SCSI_LOG_MLQUEUE_BITS             3
DECL|macro|SCSI_LOG_MLCOMPLETE_BITS
mdefine_line|#define SCSI_LOG_MLCOMPLETE_BITS          3
DECL|macro|SCSI_LOG_LLQUEUE_BITS
mdefine_line|#define SCSI_LOG_LLQUEUE_BITS             3
DECL|macro|SCSI_LOG_LLCOMPLETE_BITS
mdefine_line|#define SCSI_LOG_LLCOMPLETE_BITS          3
DECL|macro|SCSI_LOG_HLQUEUE_BITS
mdefine_line|#define SCSI_LOG_HLQUEUE_BITS             3
DECL|macro|SCSI_LOG_HLCOMPLETE_BITS
mdefine_line|#define SCSI_LOG_HLCOMPLETE_BITS          3
DECL|macro|SCSI_LOG_IOCTL_BITS
mdefine_line|#define SCSI_LOG_IOCTL_BITS               3
r_extern
r_int
r_int
id|scsi_logging_level
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI_LOGGING
DECL|macro|SCSI_CHECK_LOGGING
mdefine_line|#define SCSI_CHECK_LOGGING(SHIFT, BITS, LEVEL, CMD)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        unsigned int mask = (1 &lt;&lt; (BITS)) - 1;&t;&t;&t;&bslash;&n;        if (((scsi_logging_level &gt;&gt; (SHIFT)) &amp; mask) &gt; (LEVEL))&t;&bslash;&n;&t;&t;(CMD);&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#else
DECL|macro|SCSI_CHECK_LOGGING
mdefine_line|#define SCSI_CHECK_LOGGING(SHIFT, BITS, LEVEL, CMD)
macro_line|#endif /* CONFIG_SCSI_LOGGING */
multiline_comment|/*&n; * These are the macros that are actually used throughout the code to&n; * log events.  If logging isn&squot;t enabled, they are no-ops and will be&n; * completely absent from the user&squot;s code.&n; */
DECL|macro|SCSI_LOG_ERROR_RECOVERY
mdefine_line|#define SCSI_LOG_ERROR_RECOVERY(LEVEL,CMD)  &bslash;&n;        SCSI_CHECK_LOGGING(SCSI_LOG_ERROR_SHIFT, SCSI_LOG_ERROR_BITS, LEVEL,CMD);
DECL|macro|SCSI_LOG_TIMEOUT
mdefine_line|#define SCSI_LOG_TIMEOUT(LEVEL,CMD)  &bslash;&n;        SCSI_CHECK_LOGGING(SCSI_LOG_TIMEOUT_SHIFT, SCSI_LOG_TIMEOUT_BITS, LEVEL,CMD);
DECL|macro|SCSI_LOG_SCAN_BUS
mdefine_line|#define SCSI_LOG_SCAN_BUS(LEVEL,CMD)  &bslash;&n;        SCSI_CHECK_LOGGING(SCSI_LOG_SCAN_SHIFT, SCSI_LOG_SCAN_BITS, LEVEL,CMD);
DECL|macro|SCSI_LOG_MLQUEUE
mdefine_line|#define SCSI_LOG_MLQUEUE(LEVEL,CMD)  &bslash;&n;        SCSI_CHECK_LOGGING(SCSI_LOG_MLQUEUE_SHIFT, SCSI_LOG_MLQUEUE_BITS, LEVEL,CMD);
DECL|macro|SCSI_LOG_MLCOMPLETE
mdefine_line|#define SCSI_LOG_MLCOMPLETE(LEVEL,CMD)  &bslash;&n;        SCSI_CHECK_LOGGING(SCSI_LOG_MLCOMPLETE_SHIFT, SCSI_LOG_MLCOMPLETE_BITS, LEVEL,CMD);
DECL|macro|SCSI_LOG_LLQUEUE
mdefine_line|#define SCSI_LOG_LLQUEUE(LEVEL,CMD)  &bslash;&n;        SCSI_CHECK_LOGGING(SCSI_LOG_LLQUEUE_SHIFT, SCSI_LOG_LLQUEUE_BITS, LEVEL,CMD);
DECL|macro|SCSI_LOG_LLCOMPLETE
mdefine_line|#define SCSI_LOG_LLCOMPLETE(LEVEL,CMD)  &bslash;&n;        SCSI_CHECK_LOGGING(SCSI_LOG_LLCOMPLETE_SHIFT, SCSI_LOG_LLCOMPLETE_BITS, LEVEL,CMD);
DECL|macro|SCSI_LOG_HLQUEUE
mdefine_line|#define SCSI_LOG_HLQUEUE(LEVEL,CMD)  &bslash;&n;        SCSI_CHECK_LOGGING(SCSI_LOG_HLQUEUE_SHIFT, SCSI_LOG_HLQUEUE_BITS, LEVEL,CMD);
DECL|macro|SCSI_LOG_HLCOMPLETE
mdefine_line|#define SCSI_LOG_HLCOMPLETE(LEVEL,CMD)  &bslash;&n;        SCSI_CHECK_LOGGING(SCSI_LOG_HLCOMPLETE_SHIFT, SCSI_LOG_HLCOMPLETE_BITS, LEVEL,CMD);
DECL|macro|SCSI_LOG_IOCTL
mdefine_line|#define SCSI_LOG_IOCTL(LEVEL,CMD)  &bslash;&n;        SCSI_CHECK_LOGGING(SCSI_LOG_IOCTL_SHIFT, SCSI_LOG_IOCTL_BITS, LEVEL,CMD);
macro_line|#endif /* _SCSI_LOGGING_H */
eof
