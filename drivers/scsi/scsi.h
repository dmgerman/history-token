multiline_comment|/*&n; *  scsi.h Copyright (C) 1992 Drew Eckhardt &n; *         Copyright (C) 1993, 1994, 1995, 1998, 1999 Eric Youngdale&n; *  generic SCSI package header file by&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@andante.org to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#ifndef _SCSI_H
DECL|macro|_SCSI_H
mdefine_line|#define _SCSI_H
macro_line|#include &lt;linux/config.h&gt;&t;    /* for CONFIG_SCSI_LOGGING */
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;  /* some morons don&squot;t know struct pointers */
macro_line|#include &lt;scsi/scsi.h&gt;
multiline_comment|/*&n; * These are the values that the SCpnt-&gt;sc_data_direction and &n; * SRpnt-&gt;sr_data_direction can take.  These need to be set&n; * The SCSI_DATA_UNKNOWN value is essentially the default.&n; * In the event that the command creator didn&squot;t bother to&n; * set a value, you will see SCSI_DATA_UNKNOWN.&n; */
DECL|macro|SCSI_DATA_UNKNOWN
mdefine_line|#define SCSI_DATA_UNKNOWN       0
DECL|macro|SCSI_DATA_WRITE
mdefine_line|#define SCSI_DATA_WRITE         1
DECL|macro|SCSI_DATA_READ
mdefine_line|#define SCSI_DATA_READ          2
DECL|macro|SCSI_DATA_NONE
mdefine_line|#define SCSI_DATA_NONE          3
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#if ((SCSI_DATA_UNKNOWN == PCI_DMA_BIDIRECTIONAL) &amp;&amp; (SCSI_DATA_WRITE == PCI_DMA_TODEVICE) &amp;&amp; (SCSI_DATA_READ == PCI_DMA_FROMDEVICE) &amp;&amp; (SCSI_DATA_NONE == PCI_DMA_NONE))
DECL|macro|scsi_to_pci_dma_dir
mdefine_line|#define scsi_to_pci_dma_dir(scsi_dir)&t;((int)(scsi_dir))
macro_line|#else
DECL|function|scsi_to_pci_dma_dir
r_extern
id|__inline__
r_int
id|scsi_to_pci_dma_dir
c_func
(paren
r_int
r_char
id|scsi_dir
)paren
(brace
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_UNKNOWN
)paren
r_return
id|PCI_DMA_BIDIRECTIONAL
suffix:semicolon
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_WRITE
)paren
r_return
id|PCI_DMA_TODEVICE
suffix:semicolon
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_READ
)paren
r_return
id|PCI_DMA_FROMDEVICE
suffix:semicolon
r_return
id|PCI_DMA_NONE
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
macro_line|#if defined(CONFIG_SBUS) &amp;&amp; !defined(CONFIG_SUN3) &amp;&amp; !defined(CONFIG_SUN3X)
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#if ((SCSI_DATA_UNKNOWN == SBUS_DMA_BIDIRECTIONAL) &amp;&amp; (SCSI_DATA_WRITE == SBUS_DMA_TODEVICE) &amp;&amp; (SCSI_DATA_READ == SBUS_DMA_FROMDEVICE) &amp;&amp; (SCSI_DATA_NONE == SBUS_DMA_NONE))
DECL|macro|scsi_to_sbus_dma_dir
mdefine_line|#define scsi_to_sbus_dma_dir(scsi_dir)&t;((int)(scsi_dir))
macro_line|#else
DECL|function|scsi_to_sbus_dma_dir
r_extern
id|__inline__
r_int
id|scsi_to_sbus_dma_dir
c_func
(paren
r_int
r_char
id|scsi_dir
)paren
(brace
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_UNKNOWN
)paren
r_return
id|SBUS_DMA_BIDIRECTIONAL
suffix:semicolon
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_WRITE
)paren
r_return
id|SBUS_DMA_TODEVICE
suffix:semicolon
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_READ
)paren
r_return
id|SBUS_DMA_FROMDEVICE
suffix:semicolon
r_return
id|SBUS_DMA_NONE
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Some defs, in case these are not defined elsewhere.&n; */
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|macro|MAX_SCSI_DEVICE_CODE
mdefine_line|#define MAX_SCSI_DEVICE_CODE 14
r_extern
r_const
r_char
op_star
r_const
id|scsi_device_types
(braket
id|MAX_SCSI_DEVICE_CODE
)braket
suffix:semicolon
macro_line|#ifdef DEBUG
DECL|macro|SCSI_TIMEOUT
mdefine_line|#define SCSI_TIMEOUT (5*HZ)
macro_line|#else
DECL|macro|SCSI_TIMEOUT
mdefine_line|#define SCSI_TIMEOUT (2*HZ)
macro_line|#endif
multiline_comment|/*&n; * Used for debugging the new queueing code.  We want to make sure&n; * that the lock state is consistent with design.  Only do this in&n; * the user space simulator.&n; */
DECL|macro|ASSERT_LOCK
mdefine_line|#define ASSERT_LOCK(_LOCK, _COUNT)
macro_line|#if defined(CONFIG_SMP) &amp;&amp; defined(CONFIG_USER_DEBUG)
DECL|macro|ASSERT_LOCK
macro_line|#undef ASSERT_LOCK
DECL|macro|ASSERT_LOCK
mdefine_line|#define ASSERT_LOCK(_LOCK,_COUNT)       &bslash;&n;        { if( (_LOCK)-&gt;lock != _COUNT )   &bslash;&n;                panic(&quot;Lock count inconsistent %s %d&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;                                                                                       }
macro_line|#endif
multiline_comment|/*&n; *  Use these to separate status msg and our bytes&n; *&n; *  These are set by:&n; *&n; *      status byte = set from target device&n; *      msg_byte    = return status from host adapter itself.&n; *      host_byte   = set by low-level driver to indicate status.&n; *      driver_byte = set by mid-level.&n; */
DECL|macro|status_byte
mdefine_line|#define status_byte(result) (((result) &gt;&gt; 1) &amp; 0x1f)
DECL|macro|msg_byte
mdefine_line|#define msg_byte(result)    (((result) &gt;&gt; 8) &amp; 0xff)
DECL|macro|host_byte
mdefine_line|#define host_byte(result)   (((result) &gt;&gt; 16) &amp; 0xff)
DECL|macro|driver_byte
mdefine_line|#define driver_byte(result) (((result) &gt;&gt; 24) &amp; 0xff)
DECL|macro|suggestion
mdefine_line|#define suggestion(result)  (driver_byte(result) &amp; SUGGEST_MASK)
DECL|macro|sense_class
mdefine_line|#define sense_class(sense)  (((sense) &gt;&gt; 4) &amp; 0x7)
DECL|macro|sense_error
mdefine_line|#define sense_error(sense)  ((sense) &amp; 0xf)
DECL|macro|sense_valid
mdefine_line|#define sense_valid(sense)  ((sense) &amp; 0x80);
DECL|macro|NEEDS_RETRY
mdefine_line|#define NEEDS_RETRY     0x2001
DECL|macro|SUCCESS
mdefine_line|#define SUCCESS         0x2002
DECL|macro|FAILED
mdefine_line|#define FAILED          0x2003
DECL|macro|QUEUED
mdefine_line|#define QUEUED          0x2004
DECL|macro|SOFT_ERROR
mdefine_line|#define SOFT_ERROR      0x2005
DECL|macro|ADD_TO_MLQUEUE
mdefine_line|#define ADD_TO_MLQUEUE  0x2006
multiline_comment|/*&n; * These are the values that scsi_cmd-&gt;state can take.&n; */
DECL|macro|SCSI_STATE_TIMEOUT
mdefine_line|#define SCSI_STATE_TIMEOUT         0x1000
DECL|macro|SCSI_STATE_FINISHED
mdefine_line|#define SCSI_STATE_FINISHED        0x1001
DECL|macro|SCSI_STATE_FAILED
mdefine_line|#define SCSI_STATE_FAILED          0x1002
DECL|macro|SCSI_STATE_QUEUED
mdefine_line|#define SCSI_STATE_QUEUED          0x1003
DECL|macro|SCSI_STATE_UNUSED
mdefine_line|#define SCSI_STATE_UNUSED          0x1006
DECL|macro|SCSI_STATE_DISCONNECTING
mdefine_line|#define SCSI_STATE_DISCONNECTING   0x1008
DECL|macro|SCSI_STATE_INITIALIZING
mdefine_line|#define SCSI_STATE_INITIALIZING    0x1009
DECL|macro|SCSI_STATE_BHQUEUE
mdefine_line|#define SCSI_STATE_BHQUEUE         0x100a
DECL|macro|SCSI_STATE_MLQUEUE
mdefine_line|#define SCSI_STATE_MLQUEUE         0x100b
multiline_comment|/*&n; * These are the values that the owner field can take.&n; * They are used as an indication of who the command belongs to.&n; */
DECL|macro|SCSI_OWNER_HIGHLEVEL
mdefine_line|#define SCSI_OWNER_HIGHLEVEL      0x100
DECL|macro|SCSI_OWNER_MIDLEVEL
mdefine_line|#define SCSI_OWNER_MIDLEVEL       0x101
DECL|macro|SCSI_OWNER_LOWLEVEL
mdefine_line|#define SCSI_OWNER_LOWLEVEL       0x102
DECL|macro|SCSI_OWNER_ERROR_HANDLER
mdefine_line|#define SCSI_OWNER_ERROR_HANDLER  0x103
DECL|macro|SCSI_OWNER_BH_HANDLER
mdefine_line|#define SCSI_OWNER_BH_HANDLER     0x104
DECL|macro|SCSI_OWNER_NOBODY
mdefine_line|#define SCSI_OWNER_NOBODY         0x105
DECL|macro|IDENTIFY_BASE
mdefine_line|#define IDENTIFY_BASE       0x80
DECL|macro|IDENTIFY
mdefine_line|#define IDENTIFY(can_disconnect, lun)   (IDENTIFY_BASE |&bslash;&n;&t;&t;     ((can_disconnect) ?  0x40 : 0) |&bslash;&n;&t;&t;     ((lun) &amp; 0x07))
multiline_comment|/*&n; * This defines the scsi logging feature.  It is a means by which the&n; * user can select how much information they get about various goings on,&n; * and it can be really useful for fault tracing.  The logging word is divided&n; * into 8 nibbles, each of which describes a loglevel.  The division of things&n; * is somewhat arbitrary, and the division of the word could be changed if it&n; * were really needed for any reason.  The numbers below are the only place where these&n; * are specified.  For a first go-around, 3 bits is more than enough, since this&n; * gives 8 levels of logging (really 7, since 0 is always off).  Cutting to 2 bits&n; * might be wise at some point.&n; */
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
macro_line|#if CONFIG_SCSI_LOGGING
DECL|macro|SCSI_CHECK_LOGGING
mdefine_line|#define SCSI_CHECK_LOGGING(SHIFT, BITS, LEVEL, CMD)     &bslash;&n;{                                                       &bslash;&n;        unsigned int mask;                              &bslash;&n;                                                        &bslash;&n;        mask = (1 &lt;&lt; (BITS)) - 1;                       &bslash;&n;        if( ((scsi_logging_level &gt;&gt; (SHIFT)) &amp; mask) &gt; (LEVEL) ) &bslash;&n;        {                                               &bslash;&n;                (CMD);                                  &bslash;&n;        }&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SCSI_SET_LOGGING
mdefine_line|#define SCSI_SET_LOGGING(SHIFT, BITS, LEVEL)            &bslash;&n;{                                                       &bslash;&n;        unsigned int mask;                              &bslash;&n;                                                        &bslash;&n;        mask = ((1 &lt;&lt; (BITS)) - 1) &lt;&lt; SHIFT;            &bslash;&n;        scsi_logging_level = ((scsi_logging_level &amp; ~mask) &bslash;&n;                              | ((LEVEL &lt;&lt; SHIFT) &amp; mask));     &bslash;&n;}
macro_line|#else
multiline_comment|/*&n; * With no logging enabled, stub these out so they don&squot;t do anything.&n; */
DECL|macro|SCSI_SET_LOGGING
mdefine_line|#define SCSI_SET_LOGGING(SHIFT, BITS, LEVEL)
DECL|macro|SCSI_CHECK_LOGGING
mdefine_line|#define SCSI_CHECK_LOGGING(SHIFT, BITS, LEVEL, CMD)
macro_line|#endif
multiline_comment|/*&n; * These are the macros that are actually used throughout the code to&n; * log events.  If logging isn&squot;t enabled, they are no-ops and will be&n; * completely absent from the user&squot;s code.&n; *&n; * The &squot;set&squot; versions of the macros are really intended to only be called&n; * from the /proc filesystem, and in production kernels this will be about&n; * all that is ever used.  It could be useful in a debugging environment to&n; * bump the logging level when certain strange events are detected, however.&n; */
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
DECL|macro|SCSI_SET_ERROR_RECOVERY_LOGGING
mdefine_line|#define SCSI_SET_ERROR_RECOVERY_LOGGING(LEVEL)  &bslash;&n;        SCSI_SET_LOGGING(SCSI_LOG_ERROR_SHIFT, SCSI_LOG_ERROR_BITS, LEVEL);
DECL|macro|SCSI_SET_TIMEOUT_LOGGING
mdefine_line|#define SCSI_SET_TIMEOUT_LOGGING(LEVEL)  &bslash;&n;        SCSI_SET_LOGGING(SCSI_LOG_TIMEOUT_SHIFT, SCSI_LOG_TIMEOUT_BITS, LEVEL);
DECL|macro|SCSI_SET_SCAN_BUS_LOGGING
mdefine_line|#define SCSI_SET_SCAN_BUS_LOGGING(LEVEL)  &bslash;&n;        SCSI_SET_LOGGING(SCSI_LOG_SCAN_SHIFT, SCSI_LOG_SCAN_BITS, LEVEL);
DECL|macro|SCSI_SET_MLQUEUE_LOGGING
mdefine_line|#define SCSI_SET_MLQUEUE_LOGGING(LEVEL)  &bslash;&n;        SCSI_SET_LOGGING(SCSI_LOG_MLQUEUE_SHIFT, SCSI_LOG_MLQUEUE_BITS, LEVEL);
DECL|macro|SCSI_SET_MLCOMPLETE_LOGGING
mdefine_line|#define SCSI_SET_MLCOMPLETE_LOGGING(LEVEL)  &bslash;&n;        SCSI_SET_LOGGING(SCSI_LOG_MLCOMPLETE_SHIFT, SCSI_LOG_MLCOMPLETE_BITS, LEVEL);
DECL|macro|SCSI_SET_LLQUEUE_LOGGING
mdefine_line|#define SCSI_SET_LLQUEUE_LOGGING(LEVEL)  &bslash;&n;        SCSI_SET_LOGGING(SCSI_LOG_LLQUEUE_SHIFT, SCSI_LOG_LLQUEUE_BITS, LEVEL);
DECL|macro|SCSI_SET_LLCOMPLETE_LOGGING
mdefine_line|#define SCSI_SET_LLCOMPLETE_LOGGING(LEVEL)  &bslash;&n;        SCSI_SET_LOGGING(SCSI_LOG_LLCOMPLETE_SHIFT, SCSI_LOG_LLCOMPLETE_BITS, LEVEL);
DECL|macro|SCSI_SET_HLQUEUE_LOGGING
mdefine_line|#define SCSI_SET_HLQUEUE_LOGGING(LEVEL)  &bslash;&n;        SCSI_SET_LOGGING(SCSI_LOG_HLQUEUE_SHIFT, SCSI_LOG_HLQUEUE_BITS, LEVEL);
DECL|macro|SCSI_SET_HLCOMPLETE_LOGGING
mdefine_line|#define SCSI_SET_HLCOMPLETE_LOGGING(LEVEL)  &bslash;&n;        SCSI_SET_LOGGING(SCSI_LOG_HLCOMPLETE_SHIFT, SCSI_LOG_HLCOMPLETE_BITS, LEVEL);
DECL|macro|SCSI_SET_IOCTL_LOGGING
mdefine_line|#define SCSI_SET_IOCTL_LOGGING(LEVEL)  &bslash;&n;        SCSI_SET_LOGGING(SCSI_LOG_IOCTL_SHIFT, SCSI_LOG_IOCTL_BITS, LEVEL);
multiline_comment|/*&n; *  the return of the status word will be in the following format :&n; *  The low byte is the status returned by the SCSI command, &n; *  with vendor specific bits masked.&n; *  &n; *  The next byte is the message which followed the SCSI status.&n; *  This allows a stos to be used, since the Intel is a little&n; *  endian machine.&n; *  &n; *  The final byte is a host return code, which is one of the following.&n; *  &n; *  IE &n; *  lsb     msb&n; *  status  msg host code   &n; *  &n; *  Our errors returned by OUR driver, NOT SCSI message.  Or&squot;d with&n; *  SCSI message passed back to driver &lt;IF any&gt;.&n; */
DECL|macro|DID_OK
mdefine_line|#define DID_OK          0x00&t;/* NO error                                */
DECL|macro|DID_NO_CONNECT
mdefine_line|#define DID_NO_CONNECT  0x01&t;/* Couldn&squot;t connect before timeout period  */
DECL|macro|DID_BUS_BUSY
mdefine_line|#define DID_BUS_BUSY    0x02&t;/* BUS stayed busy through time out period */
DECL|macro|DID_TIME_OUT
mdefine_line|#define DID_TIME_OUT    0x03&t;/* TIMED OUT for other reason              */
DECL|macro|DID_BAD_TARGET
mdefine_line|#define DID_BAD_TARGET  0x04&t;/* BAD target.                             */
DECL|macro|DID_ABORT
mdefine_line|#define DID_ABORT       0x05&t;/* Told to abort for some other reason     */
DECL|macro|DID_PARITY
mdefine_line|#define DID_PARITY      0x06&t;/* Parity error                            */
DECL|macro|DID_ERROR
mdefine_line|#define DID_ERROR       0x07&t;/* Internal error                          */
DECL|macro|DID_RESET
mdefine_line|#define DID_RESET       0x08&t;/* Reset by somebody.                      */
DECL|macro|DID_BAD_INTR
mdefine_line|#define DID_BAD_INTR    0x09&t;/* Got an interrupt we weren&squot;t expecting.  */
DECL|macro|DID_PASSTHROUGH
mdefine_line|#define DID_PASSTHROUGH 0x0a&t;/* Force command past mid-layer            */
DECL|macro|DID_SOFT_ERROR
mdefine_line|#define DID_SOFT_ERROR  0x0b&t;/* The low level driver just wish a retry  */
DECL|macro|DRIVER_OK
mdefine_line|#define DRIVER_OK       0x00&t;/* Driver status                           */
multiline_comment|/*&n; *  These indicate the error that occurred, and what is available.&n; */
DECL|macro|DRIVER_BUSY
mdefine_line|#define DRIVER_BUSY         0x01
DECL|macro|DRIVER_SOFT
mdefine_line|#define DRIVER_SOFT         0x02
DECL|macro|DRIVER_MEDIA
mdefine_line|#define DRIVER_MEDIA        0x03
DECL|macro|DRIVER_ERROR
mdefine_line|#define DRIVER_ERROR        0x04
DECL|macro|DRIVER_INVALID
mdefine_line|#define DRIVER_INVALID      0x05
DECL|macro|DRIVER_TIMEOUT
mdefine_line|#define DRIVER_TIMEOUT      0x06
DECL|macro|DRIVER_HARD
mdefine_line|#define DRIVER_HARD         0x07
DECL|macro|DRIVER_SENSE
mdefine_line|#define DRIVER_SENSE&t;    0x08
DECL|macro|SUGGEST_RETRY
mdefine_line|#define SUGGEST_RETRY       0x10
DECL|macro|SUGGEST_ABORT
mdefine_line|#define SUGGEST_ABORT       0x20
DECL|macro|SUGGEST_REMAP
mdefine_line|#define SUGGEST_REMAP       0x30
DECL|macro|SUGGEST_DIE
mdefine_line|#define SUGGEST_DIE         0x40
DECL|macro|SUGGEST_SENSE
mdefine_line|#define SUGGEST_SENSE       0x80
DECL|macro|SUGGEST_IS_OK
mdefine_line|#define SUGGEST_IS_OK       0xff
DECL|macro|DRIVER_MASK
mdefine_line|#define DRIVER_MASK         0x0f
DECL|macro|SUGGEST_MASK
mdefine_line|#define SUGGEST_MASK        0xf0
DECL|macro|MAX_COMMAND_SIZE
mdefine_line|#define MAX_COMMAND_SIZE    16
DECL|macro|SCSI_SENSE_BUFFERSIZE
mdefine_line|#define SCSI_SENSE_BUFFERSIZE   64
multiline_comment|/*&n; *  SCSI command sets&n; */
DECL|macro|SCSI_UNKNOWN
mdefine_line|#define SCSI_UNKNOWN    0
DECL|macro|SCSI_1
mdefine_line|#define SCSI_1          1
DECL|macro|SCSI_1_CCS
mdefine_line|#define SCSI_1_CCS      2
DECL|macro|SCSI_2
mdefine_line|#define SCSI_2          3
DECL|macro|SCSI_3
mdefine_line|#define SCSI_3          4
multiline_comment|/*&n; *  Every SCSI command starts with a one byte OP-code.&n; *  The next byte&squot;s high three bits are the LUN of the&n; *  device.  Any multi-byte quantities are stored high byte&n; *  first, and may have a 5 bit MSB in the same byte&n; *  as the LUN.&n; */
multiline_comment|/*&n; *  As the scsi do command functions are intelligent, and may need to&n; *  redo a command, we need to keep track of the last command&n; *  executed on each one.&n; */
DECL|macro|WAS_RESET
mdefine_line|#define WAS_RESET       0x01
DECL|macro|WAS_TIMEDOUT
mdefine_line|#define WAS_TIMEDOUT    0x02
DECL|macro|WAS_SENSE
mdefine_line|#define WAS_SENSE       0x04
DECL|macro|IS_RESETTING
mdefine_line|#define IS_RESETTING    0x08
DECL|macro|IS_ABORTING
mdefine_line|#define IS_ABORTING     0x10
DECL|macro|ASKED_FOR_SENSE
mdefine_line|#define ASKED_FOR_SENSE 0x20
DECL|macro|SYNC_RESET
mdefine_line|#define SYNC_RESET      0x40
multiline_comment|/*&n; * This is the crap from the old error handling code.  We have it in a special&n; * place so that we can more easily delete it later on.&n; */
macro_line|#include &quot;scsi_obsolete.h&quot;
multiline_comment|/*&n; * Forward-declaration of structs for prototypes.&n; */
r_struct
id|Scsi_Host
suffix:semicolon
r_struct
id|scatterlist
suffix:semicolon
multiline_comment|/*&n; * Add some typedefs so that we can prototyope a bunch of the functions.&n; */
DECL|typedef|Scsi_Device
r_typedef
r_struct
id|scsi_device
id|Scsi_Device
suffix:semicolon
DECL|typedef|Scsi_Cmnd
r_typedef
r_struct
id|scsi_cmnd
id|Scsi_Cmnd
suffix:semicolon
DECL|typedef|Scsi_Request
r_typedef
r_struct
id|scsi_request
id|Scsi_Request
suffix:semicolon
DECL|macro|SCSI_CMND_MAGIC
mdefine_line|#define SCSI_CMND_MAGIC 0xE25C23A5
DECL|macro|SCSI_REQ_MAGIC
mdefine_line|#define SCSI_REQ_MAGIC  0x75F6D354
multiline_comment|/*&n; * Here is where we prototype most of the mid-layer.&n; */
r_extern
r_int
r_int
id|scsi_logging_level
suffix:semicolon
multiline_comment|/* What do we log? */
multiline_comment|/*&n; * These are the error handling functions defined in scsi_error.c&n; */
r_extern
r_void
id|scsi_times_out
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_extern
r_void
id|scsi_add_timer
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCset
comma
r_int
id|timeout
comma
r_void
(paren
op_star
id|complete
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|scsi_delete_timer
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCset
)paren
suffix:semicolon
r_extern
r_void
id|scsi_error_handler
c_func
(paren
r_void
op_star
id|host
)paren
suffix:semicolon
r_extern
r_int
id|scsi_decide_disposition
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_extern
r_int
id|scsi_block_when_processing_errors
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_sleep
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in scsicam.c&n; */
r_extern
r_int
id|scsi_partsize
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|capacity
comma
r_int
r_int
op_star
id|cyls
comma
r_int
r_int
op_star
id|hds
comma
r_int
r_int
op_star
id|secs
)paren
suffix:semicolon
multiline_comment|/*&n; * sg list allocations&n; */
r_struct
id|scatterlist
op_star
id|scsi_alloc_sgtable
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|gfp_mask
)paren
suffix:semicolon
r_void
id|scsi_free_sgtable
c_func
(paren
r_struct
id|scatterlist
op_star
id|sgl
comma
r_int
id|index
)paren
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in scsi_lib.c&n; */
r_extern
r_int
id|scsi_maybe_unblock_host
c_func
(paren
id|Scsi_Device
op_star
id|SDpnt
)paren
suffix:semicolon
r_extern
r_void
id|scsi_setup_cmd_retry
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_extern
r_int
id|scsi_insert_special_cmd
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|scsi_io_completion
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|good_sectors
comma
r_int
id|block_sectors
)paren
suffix:semicolon
r_extern
r_void
id|scsi_queue_next_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_extern
r_int
id|scsi_prep_fn
c_func
(paren
r_struct
id|request_queue
op_star
id|q
comma
r_struct
id|request
op_star
id|req
)paren
suffix:semicolon
r_extern
r_void
id|scsi_request_fn
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
suffix:semicolon
r_extern
r_int
id|scsi_starvation_completion
c_func
(paren
id|Scsi_Device
op_star
id|SDpnt
)paren
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in scsi.c&n; */
r_extern
r_int
id|scsi_dispatch_cmd
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_extern
r_void
id|scsi_bottom_half_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scsi_release_commandblocks
c_func
(paren
id|Scsi_Device
op_star
id|SDpnt
)paren
suffix:semicolon
r_extern
r_void
id|scsi_build_commandblocks
c_func
(paren
id|Scsi_Device
op_star
id|SDpnt
)paren
suffix:semicolon
r_extern
r_void
id|scsi_adjust_queue_depth
c_func
(paren
id|Scsi_Device
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|scsi_track_queue_full
c_func
(paren
id|Scsi_Device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|scsi_slave_attach
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_slave_detach
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_device_get
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_device_put
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_done
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_extern
r_void
id|scsi_finish_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_retry_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
id|Scsi_Cmnd
op_star
id|scsi_allocate_device
c_func
(paren
id|Scsi_Device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__scsi_release_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_release_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_do_cmd
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buffer
comma
r_int
id|bufflen
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
comma
r_int
id|timeout
comma
r_int
id|retries
)paren
suffix:semicolon
r_extern
r_int
id|scsi_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|scsi_mlqueue_insert
c_func
(paren
r_struct
id|scsi_cmnd
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|scsi_attach_device
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_detach_device
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_get_device_flags
c_func
(paren
r_int
r_char
op_star
id|vendor
comma
r_int
r_char
op_star
id|model
)paren
suffix:semicolon
multiline_comment|/*&n; * Newer request-based interfaces.&n; */
r_extern
id|Scsi_Request
op_star
id|scsi_allocate_request
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_release_request
c_func
(paren
id|Scsi_Request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_wait_req
c_func
(paren
id|Scsi_Request
op_star
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buffer
comma
r_int
id|bufflen
comma
r_int
id|timeout
comma
r_int
id|retries
)paren
suffix:semicolon
r_extern
r_void
id|scsi_do_req
c_func
(paren
id|Scsi_Request
op_star
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buffer
comma
r_int
id|bufflen
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
comma
r_int
id|timeout
comma
r_int
id|retries
)paren
suffix:semicolon
r_extern
r_int
id|scsi_insert_special_req
c_func
(paren
id|Scsi_Request
op_star
id|SRpnt
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|scsi_init_cmd_from_req
c_func
(paren
id|Scsi_Cmnd
op_star
comma
id|Scsi_Request
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in scsi_proc.c&n; */
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_int
id|scsi_init_procfs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scsi_exit_procfs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scsi_proc_host_add
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_proc_host_rm
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_scsi
suffix:semicolon
r_extern
r_void
id|proc_print_scsidevice
c_func
(paren
id|Scsi_Device
op_star
id|sdev
comma
r_char
op_star
id|buffer
comma
r_int
op_star
id|size
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#else
DECL|function|scsi_init_procfs
r_static
r_inline
r_int
id|scsi_init_procfs
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scsi_exit_procfs
r_static
r_inline
r_void
id|scsi_exit_procfs
c_func
(paren
r_void
)paren
(brace
suffix:semicolon
)brace
DECL|function|proc_print_scsidevice
r_static
r_inline
r_void
id|proc_print_scsidevice
c_func
(paren
id|Scsi_Device
op_star
id|sdev
comma
r_char
op_star
id|buffer
comma
r_int
op_star
id|size
comma
r_int
id|len
)paren
(brace
suffix:semicolon
)brace
r_static
r_inline
r_void
id|scsi_proc_host_add
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
id|scsi_proc_host_rm
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
multiline_comment|/*&n; * Prototypes for functions in scsi_scan.c&n; */
r_extern
r_int
id|scsi_add_single_device
c_func
(paren
id|uint
comma
id|uint
comma
id|uint
comma
id|uint
)paren
suffix:semicolon
r_extern
r_int
id|scsi_remove_single_device
c_func
(paren
id|uint
comma
id|uint
comma
id|uint
comma
id|uint
)paren
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in constants.c&n; * Some of these used to live in constants.h&n; */
r_extern
r_void
id|print_Scsi_Cmnd
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_command
c_func
(paren
r_int
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_sense
c_func
(paren
r_const
r_char
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_req_sense
c_func
(paren
r_const
r_char
op_star
comma
id|Scsi_Request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_driverbyte
c_func
(paren
r_int
id|scsiresult
)paren
suffix:semicolon
r_extern
r_void
id|print_hostbyte
c_func
(paren
r_int
id|scsiresult
)paren
suffix:semicolon
r_extern
r_void
id|print_status
c_func
(paren
r_int
r_char
id|status
)paren
suffix:semicolon
r_extern
r_int
id|print_msg
c_func
(paren
r_const
r_int
r_char
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|scsi_sense_key_string
c_func
(paren
r_int
r_char
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|scsi_extd_sense_format
c_func
(paren
r_int
r_char
comma
r_int
r_char
)paren
suffix:semicolon
multiline_comment|/*&n; * dev_info: for the black/white list in the old scsi_static_device_list&n; */
DECL|struct|dev_info
r_struct
id|dev_info
(brace
DECL|member|vendor
r_char
op_star
id|vendor
suffix:semicolon
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
DECL|member|revision
r_char
op_star
id|revision
suffix:semicolon
multiline_comment|/* revision known to be bad, unused */
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dev_info
id|scsi_static_device_list
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * scsi_dev_info_list: structure to hold black/white listed devices.&n; */
DECL|struct|scsi_dev_info_list
r_struct
id|scsi_dev_info_list
(brace
DECL|member|dev_info_list
r_struct
id|list_head
id|dev_info_list
suffix:semicolon
DECL|member|vendor
r_char
id|vendor
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|model
r_char
id|model
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|compatible
r_int
id|compatible
suffix:semicolon
multiline_comment|/* for use with scsi_static_device_list entries */
)brace
suffix:semicolon
r_extern
r_struct
id|list_head
id|scsi_dev_info_list
suffix:semicolon
r_extern
r_int
id|scsi_dev_info_list_add_str
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; *  The scsi_device struct contains what we know about each given scsi&n; *  device.&n; *&n; * FIXME(eric) - One of the great regrets that I have is that I failed to&n; * define these structure elements as something like sdev_foo instead of foo.&n; * This would make it so much easier to grep through sources and so forth.&n; * I propose that all new elements that get added to these structures follow&n; * this convention.  As time goes on and as people have the stomach for it,&n; * it should be possible to go back and retrofit at least some of the elements&n; * here with with the prefix.&n; */
DECL|struct|scsi_device
r_struct
id|scsi_device
(brace
multiline_comment|/*&n;&t; * This information is private to the scsi mid-layer.&n;&t; */
DECL|member|next
r_struct
id|scsi_device
op_star
id|next
suffix:semicolon
multiline_comment|/* Used for linked list */
DECL|member|prev
r_struct
id|scsi_device
op_star
id|prev
suffix:semicolon
multiline_comment|/* Used for linked list */
DECL|member|siblings
r_struct
id|list_head
id|siblings
suffix:semicolon
multiline_comment|/* list of all devices on this host */
DECL|member|same_target_siblings
r_struct
id|list_head
id|same_target_siblings
suffix:semicolon
multiline_comment|/* just the devices sharing same target id */
DECL|member|scpnt_wait
id|wait_queue_head_t
id|scpnt_wait
suffix:semicolon
multiline_comment|/* Used to wait if&n;&t;&t;&t;&t;&t;   device is busy */
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|request_queue
id|request_queue_t
id|request_queue
suffix:semicolon
DECL|member|device_active
id|atomic_t
id|device_active
suffix:semicolon
multiline_comment|/* commands checked out for device */
DECL|member|device_busy
r_volatile
r_int
r_int
id|device_busy
suffix:semicolon
multiline_comment|/* commands actually active on low-level */
DECL|member|free_cmnds
r_struct
id|list_head
id|free_cmnds
suffix:semicolon
multiline_comment|/* list of available Scsi_Cmnd structs */
DECL|member|busy_cmnds
r_struct
id|list_head
id|busy_cmnds
suffix:semicolon
multiline_comment|/* list of Scsi_Cmnd structs in use */
DECL|member|device_queue
id|Scsi_Cmnd
op_star
id|device_queue
suffix:semicolon
multiline_comment|/* queue of SCSI Command structures */
DECL|member|current_cmnd
id|Scsi_Cmnd
op_star
id|current_cmnd
suffix:semicolon
multiline_comment|/* currently active command */
DECL|member|current_queue_depth
r_int
r_int
id|current_queue_depth
suffix:semicolon
multiline_comment|/* How deep of a queue we have */
DECL|member|new_queue_depth
r_int
r_int
id|new_queue_depth
suffix:semicolon
multiline_comment|/* How deep of a queue we want */
DECL|member|last_queue_full_depth
r_int
r_int
id|last_queue_full_depth
suffix:semicolon
multiline_comment|/* These two are used by */
DECL|member|last_queue_full_count
r_int
r_int
id|last_queue_full_count
suffix:semicolon
multiline_comment|/* scsi_track_queue_full() */
DECL|member|last_queue_full_time
r_int
r_int
id|last_queue_full_time
suffix:semicolon
multiline_comment|/* don&squot;t let QUEUE_FULLs on the same&n;&t;&t;&t;&t;&t;   jiffie count on our counter, they&n;&t;&t;&t;&t;&t;   could all be from the same event. */
DECL|member|id
DECL|member|lun
DECL|member|channel
r_int
r_int
id|id
comma
id|lun
comma
id|channel
suffix:semicolon
DECL|member|manufacturer
r_int
r_int
id|manufacturer
suffix:semicolon
multiline_comment|/* Manufacturer of device, for using &n;&t;&t;&t;&t;&t; * vendor-specific cmd&squot;s */
DECL|member|sector_size
r_int
id|sector_size
suffix:semicolon
multiline_comment|/* size in bytes */
DECL|member|attached
r_int
id|attached
suffix:semicolon
multiline_comment|/* # of high level drivers attached to &n;&t;&t;&t;&t; * this */
DECL|member|access_count
r_int
id|access_count
suffix:semicolon
multiline_comment|/* Count of open channels/mounts */
DECL|member|hostdata
r_void
op_star
id|hostdata
suffix:semicolon
multiline_comment|/* available to low-level driver */
DECL|member|de
id|devfs_handle_t
id|de
suffix:semicolon
multiline_comment|/* directory for the device      */
DECL|member|type
r_char
id|type
suffix:semicolon
DECL|member|scsi_level
r_char
id|scsi_level
suffix:semicolon
DECL|member|inquiry_len
r_int
r_char
id|inquiry_len
suffix:semicolon
multiline_comment|/* valid bytes in &squot;inquiry&squot; */
DECL|member|inquiry
r_int
r_char
op_star
id|inquiry
suffix:semicolon
multiline_comment|/* INQUIRY response data */
DECL|member|vendor
r_char
op_star
id|vendor
suffix:semicolon
multiline_comment|/* [back_compat] point into &squot;inquiry&squot; ... */
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
multiline_comment|/* ... after scan; point to static string */
DECL|member|rev
r_char
op_star
id|rev
suffix:semicolon
multiline_comment|/* ... &quot;nullnullnullnull&quot; before scan */
DECL|member|current_tag
r_int
r_char
id|current_tag
suffix:semicolon
multiline_comment|/* current tag */
singleline_comment|//&t;unsigned char sync_min_period;&t;/* Not less than this period */
singleline_comment|//&t;unsigned char sync_max_offset;&t;/* Not greater than this offset */
DECL|member|online
r_int
id|online
suffix:colon
l_int|1
suffix:semicolon
DECL|member|writeable
r_int
id|writeable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|removable
r_int
id|removable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|random
r_int
id|random
suffix:colon
l_int|1
suffix:semicolon
DECL|member|changed
r_int
id|changed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data invalid due to media change */
DECL|member|busy
r_int
id|busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Used to prevent races */
DECL|member|lockable
r_int
id|lockable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Able to prevent media removal */
DECL|member|locked
r_int
id|locked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Media removal disabled */
DECL|member|borken
r_int
id|borken
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tell the Seagate driver to be &n;&t;&t;&t;&t; * painfully slow on this device */
DECL|member|disconnect
r_int
id|disconnect
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* can disconnect */
DECL|member|soft_reset
r_int
id|soft_reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Uses soft reset option */
DECL|member|sdtr
r_int
id|sdtr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device supports SDTR messages */
DECL|member|wdtr
r_int
id|wdtr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device supports WDTR messages */
DECL|member|ppr
r_int
id|ppr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device supports PPR messages */
DECL|member|tagged_supported
r_int
id|tagged_supported
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports SCSI-II tagged queuing */
DECL|member|tagged_queue
r_int
id|tagged_queue
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* This is going away!!!!  Look at simple_tags&n;&t;&t;&t;&t;   instead!!!  Please fix your driver now!! */
DECL|member|simple_tags
r_int
id|simple_tags
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* simple queue tag messages are enabled */
DECL|member|ordered_tags
r_int
id|ordered_tags
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ordered queue tag messages are enabled */
DECL|member|single_lun
r_int
id|single_lun
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Indicates we should only allow I/O to&n;&t;&t;&t;&t; * one of the luns for the device at a &n;&t;&t;&t;&t; * time. */
DECL|member|was_reset
r_int
id|was_reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* There was a bus reset on the bus for &n;&t;&t;&t;&t; * this device */
DECL|member|expecting_cc_ua
r_int
id|expecting_cc_ua
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Expecting a CHECK_CONDITION/UNIT_ATTN&n;&t;&t;&t;&t;&t; * because we did a bus reset. */
DECL|member|ten
r_int
id|ten
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* support ten byte read / write */
DECL|member|remap
r_int
id|remap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* support remapping  */
DECL|member|starved
r_int
id|starved
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* unable to process commands because&n;&t;&t;&t;&t;   host busy */
singleline_comment|//&t;unsigned sync:1;&t;/* Sync transfer state, managed by host */
singleline_comment|//&t;unsigned wide:1;&t;/* WIDE transfer state, managed by host */
DECL|member|device_blocked
r_int
r_int
id|device_blocked
suffix:semicolon
multiline_comment|/* Device returned QUEUE_FULL. */
DECL|member|max_device_blocked
r_int
r_int
id|max_device_blocked
suffix:semicolon
multiline_comment|/* what device_blocked counts down from  */
multiline_comment|/* default value if the device doesn&squot;t override */
DECL|macro|SCSI_DEFAULT_DEVICE_BLOCKED
mdefine_line|#define SCSI_DEFAULT_DEVICE_BLOCKED&t;3
singleline_comment|// Flag to allow revalidate to succeed in sd_open
DECL|member|allow_revalidate
r_int
id|allow_revalidate
suffix:semicolon
DECL|member|sdev_driverfs_dev
r_struct
id|device
id|sdev_driverfs_dev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_scsi_device
mdefine_line|#define&t;to_scsi_device(d)&t;&bslash;&n;&t;container_of(d, struct scsi_device, sdev_driverfs_dev)
multiline_comment|/*&n; * The Scsi_Cmnd structure is used by scsi.c internally, and for communication&n; * with low level drivers that support multiple outstanding commands.&n; */
DECL|struct|scsi_pointer
r_typedef
r_struct
id|scsi_pointer
(brace
DECL|member|ptr
r_char
op_star
id|ptr
suffix:semicolon
multiline_comment|/* data pointer */
DECL|member|this_residual
r_int
id|this_residual
suffix:semicolon
multiline_comment|/* left in this buffer */
DECL|member|buffer
r_struct
id|scatterlist
op_star
id|buffer
suffix:semicolon
multiline_comment|/* which buffer */
DECL|member|buffers_residual
r_int
id|buffers_residual
suffix:semicolon
multiline_comment|/* how many buffers left */
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
DECL|member|Status
r_volatile
r_int
id|Status
suffix:semicolon
DECL|member|Message
r_volatile
r_int
id|Message
suffix:semicolon
DECL|member|have_data_in
r_volatile
r_int
id|have_data_in
suffix:semicolon
DECL|member|sent_command
r_volatile
r_int
id|sent_command
suffix:semicolon
DECL|member|phase
r_volatile
r_int
id|phase
suffix:semicolon
DECL|typedef|Scsi_Pointer
)brace
id|Scsi_Pointer
suffix:semicolon
multiline_comment|/*&n; * This is essentially a slimmed down version of Scsi_Cmnd.  The point of&n; * having this is that requests that are injected into the queue as result&n; * of things like ioctls and character devices shouldn&squot;t be using a&n; * Scsi_Cmnd until such a time that the command is actually at the head&n; * of the queue and being sent to the driver.&n; */
DECL|struct|scsi_request
r_struct
id|scsi_request
(brace
DECL|member|sr_magic
r_int
id|sr_magic
suffix:semicolon
DECL|member|sr_result
r_int
id|sr_result
suffix:semicolon
multiline_comment|/* Status code from lower level driver */
DECL|member|sr_sense_buffer
r_int
r_char
id|sr_sense_buffer
(braket
id|SCSI_SENSE_BUFFERSIZE
)braket
suffix:semicolon
multiline_comment|/* obtained by REQUEST SENSE&n;&t;&t;&t;&t;&t;&t; * when CHECK CONDITION is&n;&t;&t;&t;&t;&t;&t; * received on original command &n;&t;&t;&t;&t;&t;&t; * (auto-sense) */
DECL|member|sr_host
r_struct
id|Scsi_Host
op_star
id|sr_host
suffix:semicolon
DECL|member|sr_device
id|Scsi_Device
op_star
id|sr_device
suffix:semicolon
DECL|member|sr_command
id|Scsi_Cmnd
op_star
id|sr_command
suffix:semicolon
DECL|member|sr_request
r_struct
id|request
op_star
id|sr_request
suffix:semicolon
multiline_comment|/* A copy of the command we are&n;&t;&t;&t;&t;   working on */
DECL|member|sr_bufflen
r_int
id|sr_bufflen
suffix:semicolon
multiline_comment|/* Size of data buffer */
DECL|member|sr_buffer
r_void
op_star
id|sr_buffer
suffix:semicolon
multiline_comment|/* Data buffer */
DECL|member|sr_allowed
r_int
id|sr_allowed
suffix:semicolon
DECL|member|sr_data_direction
r_int
r_char
id|sr_data_direction
suffix:semicolon
DECL|member|sr_cmd_len
r_int
r_char
id|sr_cmd_len
suffix:semicolon
DECL|member|sr_cmnd
r_int
r_char
id|sr_cmnd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
DECL|member|sr_done
r_void
(paren
op_star
id|sr_done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Mid-level done function */
DECL|member|sr_timeout_per_command
r_int
id|sr_timeout_per_command
suffix:semicolon
DECL|member|sr_use_sg
r_int
r_int
id|sr_use_sg
suffix:semicolon
multiline_comment|/* Number of pieces of scatter-gather */
DECL|member|sr_sglist_len
r_int
r_int
id|sr_sglist_len
suffix:semicolon
multiline_comment|/* size of malloc&squot;d scatter-gather list */
DECL|member|sr_underflow
r_int
id|sr_underflow
suffix:semicolon
multiline_comment|/* Return error if less than&n;&t;&t;&t;&t;   this amount is transferred */
DECL|member|upper_private_data
r_void
op_star
id|upper_private_data
suffix:semicolon
multiline_comment|/* reserved for owner (usually upper&n; &t;&t;&t;&t;&t;   level driver) of this request */
)brace
suffix:semicolon
multiline_comment|/*&n; * FIXME(eric) - one of the great regrets that I have is that I failed to define&n; * these structure elements as something like sc_foo instead of foo.  This would&n; * make it so much easier to grep through sources and so forth.  I propose that&n; * all new elements that get added to these structures follow this convention.&n; * As time goes on and as people have the stomach for it, it should be possible to &n; * go back and retrofit at least some of the elements here with with the prefix.&n; */
DECL|struct|scsi_cmnd
r_struct
id|scsi_cmnd
(brace
DECL|member|sc_magic
r_int
id|sc_magic
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|owner
r_int
r_int
id|owner
suffix:semicolon
DECL|member|device
id|Scsi_Device
op_star
id|device
suffix:semicolon
DECL|member|sc_request
id|Scsi_Request
op_star
id|sc_request
suffix:semicolon
DECL|member|next
r_struct
id|scsi_cmnd
op_star
id|next
suffix:semicolon
DECL|member|reset_chain
r_struct
id|scsi_cmnd
op_star
id|reset_chain
suffix:semicolon
DECL|member|list_entry
r_struct
id|list_head
id|list_entry
suffix:semicolon
multiline_comment|/* Used to place us on the cmd lists */
DECL|member|eh_state
r_int
id|eh_state
suffix:semicolon
multiline_comment|/* Used for state tracking in error handlr */
DECL|member|eh_eflags
r_int
id|eh_eflags
suffix:semicolon
multiline_comment|/* Used by error handlr */
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Mid-level done function */
multiline_comment|/*&n;&t;   A SCSI Command is assigned a nonzero serial_number when internal_cmnd&n;&t;   passes it to the driver&squot;s queue command function.  The serial_number&n;&t;   is cleared when scsi_done is entered indicating that the command has&n;&t;   been completed.  If a timeout occurs, the serial number at the moment&n;&t;   of timeout is copied into serial_number_at_timeout.  By subsequently&n;&t;   comparing the serial_number and serial_number_at_timeout fields&n;&t;   during abort or reset processing, we can detect whether the command&n;&t;   has already completed.  This also detects cases where the command has&n;&t;   completed and the SCSI Command structure has already being reused&n;&t;   for another command, so that we can avoid incorrectly aborting or&n;&t;   resetting the new command.&n;&t; */
DECL|member|serial_number
r_int
r_int
id|serial_number
suffix:semicolon
DECL|member|serial_number_at_timeout
r_int
r_int
id|serial_number_at_timeout
suffix:semicolon
DECL|member|retries
r_int
id|retries
suffix:semicolon
DECL|member|allowed
r_int
id|allowed
suffix:semicolon
DECL|member|timeout_per_command
r_int
id|timeout_per_command
suffix:semicolon
DECL|member|timeout_total
r_int
id|timeout_total
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/*&n;&t; * We handle the timeout differently if it happens when a reset, &n;&t; * abort, etc are in process. &n;&t; */
DECL|member|internal_timeout
r_int
r_volatile
r_char
id|internal_timeout
suffix:semicolon
DECL|member|bh_next
r_struct
id|scsi_cmnd
op_star
id|bh_next
suffix:semicolon
multiline_comment|/* To enumerate the commands waiting &n;&t;&t;&t;&t;&t;   to be processed. */
DECL|member|target
r_int
r_int
id|target
suffix:semicolon
DECL|member|lun
r_int
r_int
id|lun
suffix:semicolon
DECL|member|channel
r_int
r_int
id|channel
suffix:semicolon
DECL|member|cmd_len
r_int
r_char
id|cmd_len
suffix:semicolon
DECL|member|old_cmd_len
r_int
r_char
id|old_cmd_len
suffix:semicolon
DECL|member|sc_data_direction
r_int
r_char
id|sc_data_direction
suffix:semicolon
DECL|member|sc_old_data_direction
r_int
r_char
id|sc_old_data_direction
suffix:semicolon
multiline_comment|/* These elements define the operation we are about to perform */
DECL|member|cmnd
r_int
r_char
id|cmnd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
DECL|member|request_bufflen
r_int
id|request_bufflen
suffix:semicolon
multiline_comment|/* Actual request size */
DECL|member|eh_timeout
r_struct
id|timer_list
id|eh_timeout
suffix:semicolon
multiline_comment|/* Used to time out the command. */
DECL|member|request_buffer
r_void
op_star
id|request_buffer
suffix:semicolon
multiline_comment|/* Actual requested buffer */
multiline_comment|/* These elements define the operation we ultimately want to perform */
DECL|member|data_cmnd
r_int
r_char
id|data_cmnd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
DECL|member|old_use_sg
r_int
r_int
id|old_use_sg
suffix:semicolon
multiline_comment|/* We save  use_sg here when requesting&n;&t;&t;&t;&t;&t; * sense info */
DECL|member|use_sg
r_int
r_int
id|use_sg
suffix:semicolon
multiline_comment|/* Number of pieces of scatter-gather */
DECL|member|sglist_len
r_int
r_int
id|sglist_len
suffix:semicolon
multiline_comment|/* size of malloc&squot;d scatter-gather list */
DECL|member|abort_reason
r_int
r_int
id|abort_reason
suffix:semicolon
multiline_comment|/* If the mid-level code requests an&n;&t;&t;&t;&t;&t; * abort, this is the reason. */
DECL|member|bufflen
r_int
id|bufflen
suffix:semicolon
multiline_comment|/* Size of data buffer */
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
multiline_comment|/* Data buffer */
DECL|member|underflow
r_int
id|underflow
suffix:semicolon
multiline_comment|/* Return error if less than&n;&t;&t;&t;&t;   this amount is transferred */
DECL|member|old_underflow
r_int
id|old_underflow
suffix:semicolon
multiline_comment|/* save underflow here when reusing the&n;&t;&t;&t;&t; * command for error handling */
DECL|member|transfersize
r_int
id|transfersize
suffix:semicolon
multiline_comment|/* How much we are guaranteed to&n;&t;&t;&t;&t;   transfer with each SCSI transfer&n;&t;&t;&t;&t;   (ie, between disconnect / &n;&t;&t;&t;&t;   reconnects.   Probably == sector&n;&t;&t;&t;&t;   size */
DECL|member|resid
r_int
id|resid
suffix:semicolon
multiline_comment|/* Number of bytes requested to be&n;&t;&t;&t;&t;   transferred less actual number&n;&t;&t;&t;&t;   transferred (0 if not supported) */
DECL|member|request
r_struct
id|request
op_star
id|request
suffix:semicolon
multiline_comment|/* The command we are&n;&t;&t;&t;&t;   &t;   working on */
DECL|member|sense_buffer
r_int
r_char
id|sense_buffer
(braket
id|SCSI_SENSE_BUFFERSIZE
)braket
suffix:semicolon
multiline_comment|/* obtained by REQUEST SENSE&n;&t;&t;&t;&t;&t;&t; * when CHECK CONDITION is&n;&t;&t;&t;&t;&t;&t; * received on original command &n;&t;&t;&t;&t;&t;&t; * (auto-sense) */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * Used to indicate that a command which has timed out also&n;&t; * completed normally.  Typically the completion function will&n;&t; * do nothing but set this flag in this instance because the&n;&t; * timeout handler is already running.&n;&t; */
DECL|member|done_late
r_int
id|done_late
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Low-level done function - can be used by low-level driver to point&n;&t; *        to completion function.  Not used by mid/upper level code. */
DECL|member|scsi_done
r_void
(paren
op_star
id|scsi_done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The following fields can be written to by the host specific code. &n;&t; * Everything else should be left alone. &n;&t; */
DECL|member|SCp
id|Scsi_Pointer
id|SCp
suffix:semicolon
multiline_comment|/* Scratchpad used by some host adapters */
DECL|member|host_scribble
r_int
r_char
op_star
id|host_scribble
suffix:semicolon
multiline_comment|/* The host adapter is allowed to&n;&t;&t;&t;&t;&t;   * call scsi_malloc and get some memory&n;&t;&t;&t;&t;&t;   * and hang it here.     The host adapter&n;&t;&t;&t;&t;&t;   * is also expected to call scsi_free&n;&t;&t;&t;&t;&t;   * to release this memory.  (The memory&n;&t;&t;&t;&t;&t;   * obtained by scsi_malloc is guaranteed&n;&t;&t;&t;&t;&t;   * to be at an address &lt; 16Mb). */
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* Status code from lower level driver */
DECL|member|tag
r_int
r_char
id|tag
suffix:semicolon
multiline_comment|/* SCSI-II queued command tag */
DECL|member|pid
r_int
r_int
id|pid
suffix:semicolon
multiline_comment|/* Process ID, starts at 0 */
)brace
suffix:semicolon
multiline_comment|/*&n; *  Flag bit for the internal_timeout array&n; */
DECL|macro|NORMAL_TIMEOUT
mdefine_line|#define NORMAL_TIMEOUT 0
multiline_comment|/*&n; * Definitions and prototypes used for scsi mid-level queue.&n; */
DECL|macro|SCSI_MLQUEUE_HOST_BUSY
mdefine_line|#define SCSI_MLQUEUE_HOST_BUSY   0x1055
DECL|macro|SCSI_MLQUEUE_DEVICE_BUSY
mdefine_line|#define SCSI_MLQUEUE_DEVICE_BUSY 0x1056
multiline_comment|/*&n; * old style reset request from external source&n; * (private to sg.c and scsi_error.c, supplied by scsi_obsolete.c)&n; */
DECL|macro|SCSI_TRY_RESET_DEVICE
mdefine_line|#define SCSI_TRY_RESET_DEVICE&t;1
DECL|macro|SCSI_TRY_RESET_BUS
mdefine_line|#define SCSI_TRY_RESET_BUS&t;2
DECL|macro|SCSI_TRY_RESET_HOST
mdefine_line|#define SCSI_TRY_RESET_HOST&t;3
r_extern
r_int
id|scsi_reset_provider
c_func
(paren
id|Scsi_Device
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|MSG_SIMPLE_TAG
mdefine_line|#define MSG_SIMPLE_TAG&t;0x20
DECL|macro|MSG_HEAD_TAG
mdefine_line|#define MSG_HEAD_TAG&t;0x21
DECL|macro|MSG_ORDERED_TAG
mdefine_line|#define MSG_ORDERED_TAG&t;0x22
DECL|macro|SCSI_NO_TAG
mdefine_line|#define SCSI_NO_TAG&t;(-1)    /* identify no tag in use */
multiline_comment|/**&n; * scsi_activate_tcq - turn on tag command queueing&n; * @SDpnt:&t;device to turn on TCQ for&n; * @depth:&t;queue depth&n; *&n; * Notes:&n; *&t;Eventually, I hope depth would be the maximum depth&n; *&t;the device could cope with and the real queue depth&n; *&t;would be adjustable from 0 to depth.&n; **/
DECL|function|scsi_activate_tcq
r_static
r_inline
r_void
id|scsi_activate_tcq
c_func
(paren
id|Scsi_Device
op_star
id|SDpnt
comma
r_int
id|depth
)paren
(brace
id|request_queue_t
op_star
id|q
op_assign
op_amp
id|SDpnt-&gt;request_queue
suffix:semicolon
r_if
c_cond
(paren
id|SDpnt-&gt;tagged_supported
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|blk_queue_tagged
c_func
(paren
id|q
)paren
)paren
(brace
id|blk_queue_init_tags
c_func
(paren
id|q
comma
id|depth
)paren
suffix:semicolon
)brace
id|scsi_adjust_queue_depth
c_func
(paren
id|SDpnt
comma
id|MSG_ORDERED_TAG
comma
id|depth
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * scsi_deactivate_tcq - turn off tag command queueing&n; * @SDpnt:&t;device to turn off TCQ for&n; **/
DECL|function|scsi_deactivate_tcq
r_static
r_inline
r_void
id|scsi_deactivate_tcq
c_func
(paren
id|Scsi_Device
op_star
id|SDpnt
comma
r_int
id|depth
)paren
(brace
id|request_queue_t
op_star
id|q
op_assign
op_amp
id|SDpnt-&gt;request_queue
suffix:semicolon
r_if
c_cond
(paren
id|blk_queue_tagged
c_func
(paren
id|q
)paren
)paren
(brace
id|blk_queue_free_tags
c_func
(paren
id|q
)paren
suffix:semicolon
)brace
id|scsi_adjust_queue_depth
c_func
(paren
id|SDpnt
comma
l_int|0
comma
id|depth
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_populate_tag_msg - place a tag message in a buffer&n; * @SCpnt:&t;pointer to the Scsi_Cmnd for the tag&n; * @msg:&t;pointer to the area to place the tag&n; *&n; * Notes:&n; *&t;designed to create the correct type of tag message for the &n; *&t;particular request.  Returns the size of the tag message.&n; *&t;May return 0 if TCQ is disabled for this device.&n; **/
DECL|function|scsi_populate_tag_msg
r_static
r_inline
r_int
id|scsi_populate_tag_msg
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_char
op_star
id|msg
)paren
(brace
r_struct
id|request
op_star
id|req
op_assign
id|SCpnt-&gt;request
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blk_rq_tagged
c_func
(paren
id|req
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|req-&gt;flags
op_amp
id|REQ_HARDBARRIER
)paren
op_star
id|msg
op_increment
op_assign
id|MSG_ORDERED_TAG
suffix:semicolon
r_else
op_star
id|msg
op_increment
op_assign
id|MSG_SIMPLE_TAG
suffix:semicolon
op_star
id|msg
op_increment
op_assign
id|SCpnt-&gt;request-&gt;tag
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_find_tag - find a tagged command by device&n; * @SDpnt:&t;pointer to the ScSI device&n; * @tag:&t;the tag number&n; *&n; * Notes:&n; *&t;Only works with tags allocated by the generic blk layer.&n; **/
DECL|function|scsi_find_tag
r_static
r_inline
id|Scsi_Cmnd
op_star
id|scsi_find_tag
c_func
(paren
id|Scsi_Device
op_star
id|SDpnt
comma
r_int
id|tag
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_if
c_cond
(paren
id|tag
op_eq
id|SCSI_NO_TAG
)paren
(brace
multiline_comment|/* single command, look in space */
r_return
id|SDpnt-&gt;current_cmnd
suffix:semicolon
)brace
id|req
op_assign
id|blk_queue_find_tag
c_func
(paren
op_amp
id|SDpnt-&gt;request_queue
comma
id|tag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|Scsi_Cmnd
op_star
)paren
id|req-&gt;special
suffix:semicolon
)brace
DECL|macro|scsi_eh_eflags_chk
mdefine_line|#define scsi_eh_eflags_chk(scp, flags) (scp-&gt;eh_eflags &amp; flags)
DECL|macro|scsi_eh_eflags_set
mdefine_line|#define scsi_eh_eflags_set(scp, flags) do { &bslash;&n;&t;scp-&gt;eh_eflags |= flags; &bslash;&n;&t;} while(0)
DECL|macro|scsi_eh_eflags_clr
mdefine_line|#define scsi_eh_eflags_clr(scp, flags) do { &bslash;&n;&t;scp-&gt;eh_eflags &amp;= ~flags; &bslash;&n;&t;} while(0)
DECL|macro|scsi_eh_eflags_clr_all
mdefine_line|#define scsi_eh_eflags_clr_all(scp) (scp-&gt;eh_eflags = 0)
multiline_comment|/*&n; * Scsi Error Handler Flags&n; */
DECL|macro|SCSI_EH_CMD_ERR
mdefine_line|#define SCSI_EH_CMD_ERR&t;0x0001&t;/* Orig cmd error&squot;d */
DECL|macro|SCSI_EH_CMD_FAILED
mdefine_line|#define SCSI_EH_CMD_FAILED&t;0x0002&t;/* Orig cmd error type failed */
DECL|macro|SCSI_EH_CMD_TIMEOUT
mdefine_line|#define SCSI_EH_CMD_TIMEOUT&t;0x0004&t;/* Orig cmd error type timeout */
DECL|macro|SCSI_EH_REC_TIMEOUT
mdefine_line|#define SCSI_EH_REC_TIMEOUT&t;0x0008&t;/* Recovery cmd timeout */
DECL|macro|SCSI_SENSE_VALID
mdefine_line|#define SCSI_SENSE_VALID(scmd) ((scmd-&gt;sense_buffer[0] &amp; 0x70) == 0x70)
r_int
id|scsi_set_medium_removal
c_func
(paren
id|Scsi_Device
op_star
id|dev
comma
r_char
id|state
)paren
suffix:semicolon
r_extern
r_int
id|scsi_device_register
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_device_unregister
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_sysfs_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scsi_sysfs_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
