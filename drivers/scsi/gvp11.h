macro_line|#ifndef GVP11_H
multiline_comment|/* $Id: gvp11.h,v 1.4 1997/01/19 23:07:12 davem Exp $&n; *&n; * Header file for the GVP Series II SCSI controller for Linux&n; *&n; * Written and (C) 1993, Ralf Baechle, see gvp11.c for more info&n; * based on a2091.h (C) 1993 by Hamish Macdonald&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
r_int
id|gvp11_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|gvp11_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|wd33c93_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|wd33c93_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|wd33c93_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|wd33c93_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN 2
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE 16
macro_line|#endif
macro_line|#ifdef HOSTS_C
DECL|macro|GVP11_SCSI
mdefine_line|#define GVP11_SCSI {  proc_name:&t;   &quot;GVP11&quot;, &bslash;&n;&t;&t;      name:                &quot;GVP Series II SCSI&quot;, &bslash;&n;&t;&t;      detect:              gvp11_detect,    &bslash;&n;&t;&t;      release:             gvp11_release,   &bslash;&n;&t;&t;      queuecommand:        wd33c93_queuecommand, &bslash;&n;&t;&t;      abort:               wd33c93_abort,   &bslash;&n;&t;&t;      reset:               wd33c93_reset,   &bslash;&n;&t;&t;      can_queue:           CAN_QUEUE,       &bslash;&n;&t;&t;      this_id:             7,               &bslash;&n;&t;&t;      sg_tablesize:        SG_ALL,          &bslash;&n;&t;&t;      cmd_per_lun:&t;   CMD_PER_LUN,     &bslash;&n;&t;&t;      use_clustering:      DISABLE_CLUSTERING }
macro_line|#else
multiline_comment|/*&n; * if the transfer address ANDed with this results in a non-zero&n; * result, then we can&squot;t use DMA.&n; */
DECL|macro|GVP11_XFER_MASK
mdefine_line|#define GVP11_XFER_MASK  (0xff000001)
r_typedef
r_struct
(brace
DECL|member|pad1
r_int
r_char
id|pad1
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|CNTR
r_volatile
r_int
r_int
id|CNTR
suffix:semicolon
DECL|member|pad2
r_int
r_char
id|pad2
(braket
l_int|31
)braket
suffix:semicolon
DECL|member|SASR
r_volatile
r_int
r_char
id|SASR
suffix:semicolon
DECL|member|pad3
r_int
r_char
id|pad3
suffix:semicolon
DECL|member|SCMD
r_volatile
r_int
r_char
id|SCMD
suffix:semicolon
DECL|member|pad4
r_int
r_char
id|pad4
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|BANK
r_volatile
r_int
r_int
id|BANK
suffix:semicolon
DECL|member|pad5
r_int
r_char
id|pad5
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|ACR
r_volatile
r_int
r_int
id|ACR
suffix:semicolon
DECL|member|secret1
r_volatile
r_int
r_int
id|secret1
suffix:semicolon
multiline_comment|/* store 0 here */
DECL|member|ST_DMA
r_volatile
r_int
r_int
id|ST_DMA
suffix:semicolon
DECL|member|SP_DMA
r_volatile
r_int
r_int
id|SP_DMA
suffix:semicolon
DECL|member|secret2
r_volatile
r_int
r_int
id|secret2
suffix:semicolon
multiline_comment|/* store 1 here */
DECL|member|secret3
r_volatile
r_int
r_int
id|secret3
suffix:semicolon
multiline_comment|/* store 15 here */
DECL|typedef|gvp11_scsiregs
)brace
id|gvp11_scsiregs
suffix:semicolon
multiline_comment|/* bits in CNTR */
DECL|macro|GVP11_DMAC_BUSY
mdefine_line|#define GVP11_DMAC_BUSY&t;&t;(1&lt;&lt;0)
DECL|macro|GVP11_DMAC_INT_PENDING
mdefine_line|#define GVP11_DMAC_INT_PENDING&t;(1&lt;&lt;1)
DECL|macro|GVP11_DMAC_INT_ENABLE
mdefine_line|#define GVP11_DMAC_INT_ENABLE&t;(1&lt;&lt;3)
DECL|macro|GVP11_DMAC_DIR_WRITE
mdefine_line|#define GVP11_DMAC_DIR_WRITE&t;(1&lt;&lt;4)
macro_line|#endif /* else def HOSTS_C */
macro_line|#endif /* GVP11_H */
eof
