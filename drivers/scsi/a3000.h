macro_line|#ifndef A3000_H
DECL|macro|A3000_H
mdefine_line|#define A3000_H
multiline_comment|/* $Id: a3000.h,v 1.4 1997/01/19 23:07:10 davem Exp $&n; *&n; * Header file for the Amiga 3000 built-in SCSI controller for Linux&n; *&n; * Written and (C) 1993, Hamish Macdonald, see a3000.c for more info&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
r_int
id|a3000_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|a3000_release
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
DECL|macro|_A3000_SCSI
mdefine_line|#define _A3000_SCSI { proc_name:&t;   &quot;A3000&quot;,&t;&t;&t;&bslash;&n;&t;&t;      proc_info:           NULL,&t;&t;&t;&bslash;&n;&t;&t;      name:                &quot;Amiga 3000 built-in SCSI&quot;,&t;&bslash;&n;&t;&t;      detect:              a3000_detect,&t;&t;&bslash;&n;&t;&t;      release:             a3000_release,&t;&t;&bslash;&n;&t;&t;      queuecommand:        wd33c93_queuecommand,&t;&bslash;&n;&t;&t;      abort:               wd33c93_abort,&t;&t;&bslash;&n;&t;&t;      reset:               wd33c93_reset,&t;&t;&bslash;&n;&t;&t;      can_queue:           CAN_QUEUE,&t;&t;&t;&bslash;&n;&t;&t;      this_id:             7,&t;&t;&t;&t;&bslash;&n;&t;&t;      sg_tablesize:        SG_ALL,&t;&t;&t;&bslash;&n;&t;&t;      cmd_per_lun:&t;   CMD_PER_LUN,&t;&t;&t;&bslash;&n;&t;&t;      use_clustering:      ENABLE_CLUSTERING }
multiline_comment|/*&n; * if the transfer address ANDed with this results in a non-zero&n; * result, then we can&squot;t use DMA.&n; */
DECL|macro|A3000_XFER_MASK
mdefine_line|#define A3000_XFER_MASK  (0x00000003)
r_typedef
r_struct
(brace
DECL|member|pad1
r_int
r_char
id|pad1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|DAWR
r_volatile
r_int
r_int
id|DAWR
suffix:semicolon
DECL|member|WTC
r_volatile
r_int
r_int
id|WTC
suffix:semicolon
DECL|member|pad2
r_int
r_char
id|pad2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|CNTR
r_volatile
r_int
r_int
id|CNTR
suffix:semicolon
DECL|member|ACR
r_volatile
r_int
r_int
id|ACR
suffix:semicolon
DECL|member|pad3
r_int
r_char
id|pad3
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ST_DMA
r_volatile
r_int
r_int
id|ST_DMA
suffix:semicolon
DECL|member|pad4
r_int
r_char
id|pad4
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|FLUSH
r_volatile
r_int
r_int
id|FLUSH
suffix:semicolon
DECL|member|pad5
r_int
r_char
id|pad5
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|CINT
r_volatile
r_int
r_int
id|CINT
suffix:semicolon
DECL|member|pad6
r_int
r_char
id|pad6
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ISTR
r_volatile
r_int
r_int
id|ISTR
suffix:semicolon
DECL|member|pad7
r_int
r_char
id|pad7
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|SP_DMA
r_volatile
r_int
r_int
id|SP_DMA
suffix:semicolon
DECL|member|pad8
r_int
r_char
id|pad8
suffix:semicolon
DECL|member|SASR
r_volatile
r_int
r_char
id|SASR
suffix:semicolon
DECL|member|pad9
r_int
r_char
id|pad9
suffix:semicolon
DECL|member|SCMD
r_volatile
r_int
r_char
id|SCMD
suffix:semicolon
DECL|typedef|a3000_scsiregs
)brace
id|a3000_scsiregs
suffix:semicolon
DECL|macro|DAWR_A3000
mdefine_line|#define DAWR_A3000&t;&t;(3)
multiline_comment|/* CNTR bits. */
DECL|macro|CNTR_TCEN
mdefine_line|#define CNTR_TCEN&t;&t;(1&lt;&lt;5)
DECL|macro|CNTR_PREST
mdefine_line|#define CNTR_PREST&t;&t;(1&lt;&lt;4)
DECL|macro|CNTR_PDMD
mdefine_line|#define CNTR_PDMD&t;&t;(1&lt;&lt;3)
DECL|macro|CNTR_INTEN
mdefine_line|#define CNTR_INTEN&t;&t;(1&lt;&lt;2)
DECL|macro|CNTR_DDIR
mdefine_line|#define CNTR_DDIR&t;&t;(1&lt;&lt;1)
DECL|macro|CNTR_IO_DX
mdefine_line|#define CNTR_IO_DX&t;&t;(1&lt;&lt;0)
multiline_comment|/* ISTR bits. */
DECL|macro|ISTR_INTX
mdefine_line|#define ISTR_INTX&t;&t;(1&lt;&lt;8)
DECL|macro|ISTR_INT_F
mdefine_line|#define ISTR_INT_F&t;&t;(1&lt;&lt;7)
DECL|macro|ISTR_INTS
mdefine_line|#define ISTR_INTS&t;&t;(1&lt;&lt;6)
DECL|macro|ISTR_E_INT
mdefine_line|#define ISTR_E_INT&t;&t;(1&lt;&lt;5)
DECL|macro|ISTR_INT_P
mdefine_line|#define ISTR_INT_P&t;&t;(1&lt;&lt;4)
DECL|macro|ISTR_UE_INT
mdefine_line|#define ISTR_UE_INT&t;&t;(1&lt;&lt;3)
DECL|macro|ISTR_OE_INT
mdefine_line|#define ISTR_OE_INT&t;&t;(1&lt;&lt;2)
DECL|macro|ISTR_FF_FLG
mdefine_line|#define ISTR_FF_FLG&t;&t;(1&lt;&lt;1)
DECL|macro|ISTR_FE_FLG
mdefine_line|#define ISTR_FE_FLG&t;&t;(1&lt;&lt;0)
macro_line|#endif /* A3000_H */
eof
