multiline_comment|/*&n; *  scsi.h Copyright (C) 1992 Drew Eckhardt &n; *         Copyright (C) 1993, 1994, 1995, 1998, 1999 Eric Youngdale&n; *  generic SCSI package header file by&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@andante.org to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
multiline_comment|/*&n; * NOTE:  this file only contains compatibility glue for old drivers.  All&n; * these wrappers will be removed sooner or later.  For new code please use&n; * the interfaces declared in the headers in include/scsi/&n; */
macro_line|#ifndef _SCSI_H
DECL|macro|_SCSI_H
mdefine_line|#define _SCSI_H
macro_line|#include &lt;linux/config.h&gt;&t;    /* for CONFIG_SCSI_LOGGING */
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
macro_line|#include &lt;scsi/scsi_dbg.h&gt;
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
multiline_comment|/*&n; * Old names for debug prettyprinting functions.&n; */
DECL|function|print_Scsi_Cmnd
r_static
r_inline
r_void
id|print_Scsi_Cmnd
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
(brace
r_return
id|scsi_print_command
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
DECL|function|print_command
r_static
r_inline
r_void
id|print_command
c_func
(paren
r_int
r_char
op_star
id|cdb
)paren
(brace
r_return
id|__scsi_print_command
c_func
(paren
id|cdb
)paren
suffix:semicolon
)brace
DECL|function|print_sense
r_static
r_inline
r_void
id|print_sense
c_func
(paren
r_const
r_char
op_star
id|devclass
comma
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
(brace
r_return
id|scsi_print_sense
c_func
(paren
id|devclass
comma
id|cmd
)paren
suffix:semicolon
)brace
DECL|function|print_req_sense
r_static
r_inline
r_void
id|print_req_sense
c_func
(paren
r_const
r_char
op_star
id|devclass
comma
r_struct
id|scsi_request
op_star
id|req
)paren
(brace
r_return
id|scsi_print_req_sense
c_func
(paren
id|devclass
comma
id|req
)paren
suffix:semicolon
)brace
DECL|function|print_driverbyte
r_static
r_inline
r_void
id|print_driverbyte
c_func
(paren
r_int
id|scsiresult
)paren
(brace
r_return
id|scsi_print_driverbyte
c_func
(paren
id|scsiresult
)paren
suffix:semicolon
)brace
DECL|function|print_hostbyte
r_static
r_inline
r_void
id|print_hostbyte
c_func
(paren
r_int
id|scsiresult
)paren
(brace
r_return
id|scsi_print_hostbyte
c_func
(paren
id|scsiresult
)paren
suffix:semicolon
)brace
DECL|function|print_status
r_static
r_inline
r_void
id|print_status
c_func
(paren
r_int
r_char
id|status
)paren
(brace
r_return
id|scsi_print_status
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
DECL|function|print_msg
r_static
r_inline
r_int
id|print_msg
c_func
(paren
r_const
r_int
r_char
op_star
id|msg
)paren
(brace
r_return
id|scsi_print_msg
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the crap from the old error handling code.  We have it in a special&n; * place so that we can more easily delete it later on.&n; */
macro_line|#include &quot;scsi_obsolete.h&quot;
multiline_comment|/* obsolete typedef junk. */
macro_line|#include &quot;scsi_typedefs.h&quot;
macro_line|#endif /* _SCSI_H */
eof
