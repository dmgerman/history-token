multiline_comment|/*&n; *  scsi.h Copyright (C) 1992 Drew Eckhardt &n; *         Copyright (C) 1993, 1994, 1995, 1998, 1999 Eric Youngdale&n; *  generic SCSI package header file by&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@andante.org to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#ifndef _SCSI_H
DECL|macro|_SCSI_H
mdefine_line|#define _SCSI_H
macro_line|#include &lt;linux/config.h&gt;&t;    /* for CONFIG_SCSI_LOGGING */
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_eh.h&gt;
macro_line|#include &lt;scsi/scsi_request.h&gt;
macro_line|#include &lt;scsi/scsi_tcq.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
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
DECL|macro|IDENTIFY_BASE
mdefine_line|#define IDENTIFY_BASE       0x80
DECL|macro|IDENTIFY
mdefine_line|#define IDENTIFY(can_disconnect, lun)   (IDENTIFY_BASE |&bslash;&n;&t;&t;     ((can_disconnect) ?  0x40 : 0) |&bslash;&n;&t;&t;     ((lun) &amp; 0x07))
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
r_struct
id|Scsi_Host
suffix:semicolon
r_struct
id|scsi_cmnd
suffix:semicolon
r_struct
id|scsi_device
suffix:semicolon
r_struct
id|scsi_target
suffix:semicolon
r_struct
id|scatterlist
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in constants.c&n; * Some of these used to live in constants.h&n; */
r_extern
r_void
id|print_Scsi_Cmnd
c_func
(paren
r_struct
id|scsi_cmnd
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
r_struct
id|scsi_cmnd
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
r_struct
id|scsi_request
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
multiline_comment|/*&n; * Legacy dma direction interfaces.&n; *&n; * This assumes the pci/sbus dma mapping flags have the same numercial&n; * values as the generic dma-mapping ones.  Currently they have but there&squot;s&n; * no way to check.  Better don&squot;t use these interfaces!&n; */
DECL|macro|SCSI_DATA_UNKNOWN
mdefine_line|#define SCSI_DATA_UNKNOWN&t;(DMA_BIDIRECTIONAL)
DECL|macro|SCSI_DATA_WRITE
mdefine_line|#define SCSI_DATA_WRITE&t;&t;(DMA_TO_DEVICE)
DECL|macro|SCSI_DATA_READ
mdefine_line|#define SCSI_DATA_READ&t;&t;(DMA_FROM_DEVICE)
DECL|macro|SCSI_DATA_NONE
mdefine_line|#define SCSI_DATA_NONE&t;&t;(DMA_NONE)
DECL|macro|scsi_to_pci_dma_dir
mdefine_line|#define scsi_to_pci_dma_dir(scsi_dir)&t;((int)(scsi_dir))
DECL|macro|scsi_to_sbus_dma_dir
mdefine_line|#define scsi_to_sbus_dma_dir(scsi_dir)&t;((int)(scsi_dir))
multiline_comment|/*&n; * This is the crap from the old error handling code.  We have it in a special&n; * place so that we can more easily delete it later on.&n; */
macro_line|#include &quot;scsi_obsolete.h&quot;
multiline_comment|/* obsolete typedef junk. */
macro_line|#include &quot;scsi_typedefs.h&quot;
macro_line|#endif /* _SCSI_H */
eof
