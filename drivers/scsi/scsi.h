multiline_comment|/*&n; *  scsi.h Copyright (C) 1992 Drew Eckhardt &n; *         Copyright (C) 1993, 1994, 1995, 1998, 1999 Eric Youngdale&n; *  generic SCSI package header file by&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@andante.org to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#ifndef _SCSI_H
DECL|macro|_SCSI_H
mdefine_line|#define _SCSI_H
macro_line|#include &lt;linux/config.h&gt;&t;/* for CONFIG_SCSI_LOGGING */
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
multiline_comment|/*&n; * Some of the public constants are being moved to this file.&n; * We include it here so that what came from where is transparent.&n; */
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
DECL|macro|COMMAND_SIZE
mdefine_line|#define COMMAND_SIZE(opcode) scsi_command_size[((opcode) &gt;&gt; 5) &amp; 7]
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
multiline_comment|/*&n; *  Initializes all SCSI devices.  This scans all scsi busses.&n; */
r_extern
r_int
r_int
id|scsi_logging_level
suffix:semicolon
multiline_comment|/* What do we log? */
r_extern
r_int
r_int
id|scsi_dma_free_sectors
suffix:semicolon
multiline_comment|/* How much room do we have left */
r_extern
r_int
r_int
id|scsi_need_isa_buffer
suffix:semicolon
multiline_comment|/* True if some devices need indirection&n;&t;&t;&t;&t;&t;&t;   * buffers */
r_extern
r_volatile
r_int
id|in_scan_scsis
suffix:semicolon
r_extern
r_const
r_int
r_char
id|scsi_command_size
(braket
l_int|8
)braket
suffix:semicolon
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
id|scsi_sense_valid
c_func
(paren
id|Scsi_Cmnd
op_star
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
multiline_comment|/*&n; * Prototypes for functions in scsi_dma.c&n; */
r_void
id|scsi_resize_dma_pool
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|scsi_init_minimal_dma_pool
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
op_star
id|scsi_malloc
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
id|scsi_free
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in scsi_merge.c&n; */
r_extern
r_void
id|scsi_initialize_merge_fn
c_func
(paren
id|Scsi_Device
op_star
id|SDpnt
)paren
suffix:semicolon
r_extern
r_int
id|scsi_init_io
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in scsi_queue.c&n; */
r_extern
r_int
id|scsi_mlqueue_insert
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
id|reason
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
id|Scsi_Cmnd
op_star
id|scsi_end_request
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|uptodate
comma
r_int
id|sectors
)paren
suffix:semicolon
r_extern
r_struct
id|Scsi_Device_Template
op_star
id|scsi_get_request_dev
c_func
(paren
r_struct
id|request
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_init_cmd_errh
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
multiline_comment|/*&n; * Prototypes for functions/data in hosts.c&n; */
r_extern
r_int
id|max_scsi_hosts
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in scsi_proc.c&n; */
r_extern
r_void
id|proc_print_scsidevice
c_func
(paren
id|Scsi_Device
op_star
comma
r_char
op_star
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_scsi
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in constants.c&n; */
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
(paren
r_int
id|status
)paren
suffix:semicolon
multiline_comment|/*&n; *  The scsi_device struct contains what we know about each given scsi&n; *  device.&n; *&n; * FIXME(eric) - one of the great regrets that I have is that I failed to define&n; * these structure elements as something like sdev_foo instead of foo.  This would&n; * make it so much easier to grep through sources and so forth.  I propose that&n; * all new elements that get added to these structures follow this convention.&n; * As time goes on and as people have the stomach for it, it should be possible to &n; * go back and retrofit at least some of the elements here with with the prefix.&n; */
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
DECL|member|device_queue
id|Scsi_Cmnd
op_star
id|device_queue
suffix:semicolon
multiline_comment|/* queue of SCSI Command structures */
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
DECL|member|vendor
DECL|member|model
DECL|member|rev
r_char
id|vendor
(braket
l_int|8
)braket
comma
id|model
(braket
l_int|16
)braket
comma
id|rev
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|current_tag
r_int
r_char
id|current_tag
suffix:semicolon
multiline_comment|/* current tag */
DECL|member|sync_min_period
r_int
r_char
id|sync_min_period
suffix:semicolon
multiline_comment|/* Not less than this period */
DECL|member|sync_max_offset
r_int
r_char
id|sync_max_offset
suffix:semicolon
multiline_comment|/* Not greater than this offset */
DECL|member|queue_depth
r_int
r_char
id|queue_depth
suffix:semicolon
multiline_comment|/* How deep a queue to use */
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
DECL|member|has_cmdblocks
r_int
id|has_cmdblocks
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
DECL|member|borken
r_int
id|borken
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tell the Seagate driver to be &n;&t;&t;&t;&t; * painfully slow on this device */
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
multiline_comment|/* SCSI-II tagged queuing enabled */
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
DECL|member|sync
r_int
id|sync
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Negotiate for sync transfers */
DECL|member|wide
r_int
id|wide
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Negotiate for WIDE transfers */
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
DECL|member|device_blocked
r_int
id|device_blocked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device returned QUEUE_FULL. */
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
singleline_comment|// Flag to allow revalidate to succeed in sd_open
DECL|member|allow_revalidate
r_int
id|allow_revalidate
suffix:semicolon
)brace
suffix:semicolon
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
DECL|member|eh_state
r_int
id|eh_state
suffix:semicolon
multiline_comment|/* Used for state tracking in error handlr */
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
id|request
suffix:semicolon
multiline_comment|/* A copy of the command we are&n;&t;&t;&t;&t;   working on */
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
DECL|macro|SCSI_SLEEP
mdefine_line|#define SCSI_SLEEP(QUEUE, CONDITION) {&t;&t;    &bslash;&n;    if (CONDITION) {&t;&t;&t;            &bslash;&n;&t;DECLARE_WAITQUEUE(wait, current);&t;    &bslash;&n;&t;add_wait_queue(QUEUE, &amp;wait);&t;&t;    &bslash;&n;&t;for(;;) {&t;&t;&t;            &bslash;&n;&t;set_current_state(TASK_UNINTERRUPTIBLE);    &bslash;&n;&t;if (CONDITION) {&t;&t;            &bslash;&n;            if (in_interrupt())&t;                    &bslash;&n;&t;        panic(&quot;scsi: trying to call schedule() in interrupt&quot; &bslash;&n;&t;&t;      &quot;, file %s, line %d.&bslash;n&quot;, __FILE__, __LINE__);  &bslash;&n;&t;    schedule();&t;&t;&t;&bslash;&n;        }&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;        &bslash;&n;&t;    break;      &t;&t;&bslash;&n;&t;}&t;&t;&t;        &bslash;&n;&t;remove_wait_queue(QUEUE, &amp;wait);&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&bslash;&n;    }; }
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
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
