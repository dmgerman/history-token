macro_line|#ifndef _AHA1740_H
multiline_comment|/* $Id$&n; *&n; * Header file for the adaptec 1740 driver for Linux&n; *&n; * With minor revisions 3/31/93&n; * Written and (C) 1992,1993 Brad McLean.  See aha1740.c&n; * for more info&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
multiline_comment|/* Eisa Enhanced mode operation - slot locating and addressing */
DECL|macro|MINEISA
mdefine_line|#define MINEISA 1   /* I don&squot;t have an EISA Spec to know these ranges, so I */
DECL|macro|MAXEISA
mdefine_line|#define MAXEISA 8   /* Just took my machine&squot;s specifications.  Adjust to fit.*/
multiline_comment|/* I just saw an ad, and bumped this from 6 to 8 */
DECL|macro|SLOTBASE
mdefine_line|#define&t;SLOTBASE(x)&t;((x &lt;&lt; 12) + 0xc80)
DECL|macro|SLOTSIZE
mdefine_line|#define SLOTSIZE&t;0x5c
multiline_comment|/* EISA configuration registers &amp; values */
DECL|macro|HID0
mdefine_line|#define&t;HID0(base)&t;(base + 0x0)
DECL|macro|HID1
mdefine_line|#define&t;HID1(base)&t;(base + 0x1)
DECL|macro|HID2
mdefine_line|#define HID2(base)&t;(base + 0x2)
DECL|macro|HID3
mdefine_line|#define&t;HID3(base)&t;(base + 0x3)
DECL|macro|EBCNTRL
mdefine_line|#define&t;EBCNTRL(base)&t;(base + 0x4)
DECL|macro|PORTADR
mdefine_line|#define&t;PORTADR(base)&t;(base + 0x40)
DECL|macro|BIOSADR
mdefine_line|#define BIOSADR(base)&t;(base + 0x41)
DECL|macro|INTDEF
mdefine_line|#define INTDEF(base)&t;(base + 0x42)
DECL|macro|SCSIDEF
mdefine_line|#define SCSIDEF(base)&t;(base + 0x43)
DECL|macro|BUSDEF
mdefine_line|#define BUSDEF(base)&t;(base + 0x44)
DECL|macro|RESV0
mdefine_line|#define&t;RESV0(base)&t;(base + 0x45)
DECL|macro|RESV1
mdefine_line|#define RESV1(base)&t;(base + 0x46)
DECL|macro|RESV2
mdefine_line|#define&t;RESV2(base)&t;(base + 0x47)
DECL|macro|HID_MFG
mdefine_line|#define&t;HID_MFG&t;&quot;ADP&quot;
DECL|macro|HID_PRD
mdefine_line|#define&t;HID_PRD 0
DECL|macro|HID_REV
mdefine_line|#define HID_REV 2
DECL|macro|EBCNTRL_VALUE
mdefine_line|#define EBCNTRL_VALUE 1
DECL|macro|PORTADDR_ENH
mdefine_line|#define PORTADDR_ENH 0x80
multiline_comment|/* READ */
DECL|macro|G2INTST
mdefine_line|#define&t;G2INTST(base)&t;(base + 0x56)
DECL|macro|G2STAT
mdefine_line|#define G2STAT(base)&t;(base + 0x57)
DECL|macro|MBOXIN0
mdefine_line|#define&t;MBOXIN0(base)&t;(base + 0x58)
DECL|macro|MBOXIN1
mdefine_line|#define&t;MBOXIN1(base)&t;(base + 0x59)
DECL|macro|MBOXIN2
mdefine_line|#define&t;MBOXIN2(base)&t;(base + 0x5a)
DECL|macro|MBOXIN3
mdefine_line|#define&t;MBOXIN3(base)&t;(base + 0x5b)
DECL|macro|G2STAT2
mdefine_line|#define G2STAT2(base)&t;(base + 0x5c)
DECL|macro|G2INTST_MASK
mdefine_line|#define G2INTST_MASK&t;&t;0xf0&t;/* isolate the status */
DECL|macro|G2INTST_CCBGOOD
mdefine_line|#define&t;G2INTST_CCBGOOD&t;&t;0x10&t;/* CCB Completed */
DECL|macro|G2INTST_CCBRETRY
mdefine_line|#define&t;G2INTST_CCBRETRY&t;0x50&t;/* CCB Completed with a retry */
DECL|macro|G2INTST_HARDFAIL
mdefine_line|#define&t;G2INTST_HARDFAIL&t;0x70&t;/* Adapter Hardware Failure */
DECL|macro|G2INTST_CMDGOOD
mdefine_line|#define&t;G2INTST_CMDGOOD&t;&t;0xa0&t;/* Immediate command success */
DECL|macro|G2INTST_CCBERROR
mdefine_line|#define G2INTST_CCBERROR&t;0xc0&t;/* CCB Completed with error */
DECL|macro|G2INTST_ASNEVENT
mdefine_line|#define&t;G2INTST_ASNEVENT&t;0xd0&t;/* Asynchronous Event Notification */
DECL|macro|G2INTST_CMDERROR
mdefine_line|#define&t;G2INTST_CMDERROR&t;0xe0&t;/* Immediate command error */
DECL|macro|G2STAT_MBXOUT
mdefine_line|#define G2STAT_MBXOUT&t;4&t;/* Mailbox Out Empty Bit */
DECL|macro|G2STAT_INTPEND
mdefine_line|#define&t;G2STAT_INTPEND&t;2&t;/* Interrupt Pending Bit */
DECL|macro|G2STAT_BUSY
mdefine_line|#define&t;G2STAT_BUSY&t;1&t;/* Busy Bit (attention pending) */
DECL|macro|G2STAT2_READY
mdefine_line|#define G2STAT2_READY&t;0&t;/* Host Ready Bit */
multiline_comment|/* WRITE (and ReadBack) */
DECL|macro|MBOXOUT0
mdefine_line|#define&t;MBOXOUT0(base)&t;(base + 0x50)
DECL|macro|MBOXOUT1
mdefine_line|#define&t;MBOXOUT1(base)&t;(base + 0x51)
DECL|macro|MBOXOUT2
mdefine_line|#define&t;MBOXOUT2(base)&t;(base + 0x52)
DECL|macro|MBOXOUT3
mdefine_line|#define&t;MBOXOUT3(base)&t;(base + 0x53)
DECL|macro|ATTN
mdefine_line|#define&t;ATTN(base)&t;(base + 0x54)
DECL|macro|G2CNTRL
mdefine_line|#define G2CNTRL(base)&t;(base + 0x55)
DECL|macro|ATTN_IMMED
mdefine_line|#define&t;ATTN_IMMED&t;0x10&t;/* Immediate Command */
DECL|macro|ATTN_START
mdefine_line|#define&t;ATTN_START&t;0x40&t;/* Start CCB */
DECL|macro|ATTN_ABORT
mdefine_line|#define&t;ATTN_ABORT&t;0x50&t;/* Abort CCB */
DECL|macro|G2CNTRL_HRST
mdefine_line|#define G2CNTRL_HRST&t;0x80&t;&t;/* Hard Reset */
DECL|macro|G2CNTRL_IRST
mdefine_line|#define G2CNTRL_IRST&t;0x40&t;&t;/* Clear EISA Interrupt */
DECL|macro|G2CNTRL_HRDY
mdefine_line|#define G2CNTRL_HRDY&t;0x20&t;&t;/* Sets HOST ready */
multiline_comment|/* This is used with scatter-gather */
DECL|struct|aha1740_chain
r_struct
id|aha1740_chain
(brace
DECL|member|dataptr
id|u32
id|dataptr
suffix:semicolon
multiline_comment|/* Location of data */
DECL|member|datalen
id|u32
id|datalen
suffix:semicolon
multiline_comment|/* Size of this part of chain */
)brace
suffix:semicolon
multiline_comment|/* These belong in scsi.h */
DECL|macro|any2scsi
mdefine_line|#define any2scsi(up, p)&t;&t;&t;&t;&bslash;&n;(up)[0] = (((unsigned long)(p)) &gt;&gt; 16)  ;&t;&bslash;&n;(up)[1] = (((unsigned long)(p)) &gt;&gt; 8);&t;&t;&bslash;&n;(up)[2] = ((unsigned long)(p));
DECL|macro|scsi2int
mdefine_line|#define scsi2int(up) ( (((long)*(up)) &lt;&lt; 16) + (((long)(up)[1]) &lt;&lt; 8) + ((long)(up)[2]) )
DECL|macro|xany2scsi
mdefine_line|#define xany2scsi(up, p)&t;&bslash;&n;(up)[0] = ((long)(p)) &gt;&gt; 24;&t;&bslash;&n;(up)[1] = ((long)(p)) &gt;&gt; 16;&t;&bslash;&n;(up)[2] = ((long)(p)) &gt;&gt; 8;&t;&bslash;&n;(up)[3] = ((long)(p));
DECL|macro|xscsi2int
mdefine_line|#define xscsi2int(up) ( (((long)(up)[0]) &lt;&lt; 24) + (((long)(up)[1]) &lt;&lt; 16) &bslash;&n;&t;&t;      + (((long)(up)[2]) &lt;&lt;  8) +  ((long)(up)[3]) )
DECL|macro|MAX_CDB
mdefine_line|#define MAX_CDB 12
DECL|macro|MAX_SENSE
mdefine_line|#define MAX_SENSE 14
DECL|macro|MAX_STATUS
mdefine_line|#define MAX_STATUS 32
DECL|struct|ecb
r_struct
id|ecb
(brace
multiline_comment|/* Enhanced Control Block 6.1 */
DECL|member|cmdw
id|u16
id|cmdw
suffix:semicolon
multiline_comment|/* Command Word */
multiline_comment|/* Flag Word 1 */
DECL|member|cne
id|u16
id|cne
suffix:colon
l_int|1
comma
multiline_comment|/* Control Block Chaining */
DECL|member|di
suffix:colon
l_int|6
comma
id|di
suffix:colon
l_int|1
comma
multiline_comment|/* Disable Interrupt */
DECL|member|ses
suffix:colon
l_int|2
comma
id|ses
suffix:colon
l_int|1
comma
multiline_comment|/* Suppress Underrun error */
DECL|member|sg
suffix:colon
l_int|1
comma
id|sg
suffix:colon
l_int|1
comma
multiline_comment|/* Scatter/Gather */
DECL|member|dsb
suffix:colon
l_int|1
comma
id|dsb
suffix:colon
l_int|1
comma
multiline_comment|/* Disable Status Block */
DECL|member|ars
id|ars
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Automatic Request Sense */
multiline_comment|/* Flag Word 2 */
DECL|member|lun
id|u16
id|lun
suffix:colon
l_int|3
comma
multiline_comment|/* Logical Unit */
DECL|member|tag
id|tag
suffix:colon
l_int|1
comma
multiline_comment|/* Tagged Queuing */
DECL|member|tt
id|tt
suffix:colon
l_int|2
comma
multiline_comment|/* Tag Type */
DECL|member|nd
id|nd
suffix:colon
l_int|1
comma
multiline_comment|/* No Disconnect */
DECL|member|dat
suffix:colon
l_int|1
comma
id|dat
suffix:colon
l_int|1
comma
multiline_comment|/* Data transfer - check direction */
DECL|member|dir
id|dir
suffix:colon
l_int|1
comma
multiline_comment|/* Direction of transfer 1 = datain */
DECL|member|st
id|st
suffix:colon
l_int|1
comma
multiline_comment|/* Suppress Transfer */
DECL|member|chk
id|chk
suffix:colon
l_int|1
comma
multiline_comment|/* Calculate Checksum */
DECL|member|rec
suffix:colon
l_int|2
comma
id|rec
suffix:colon
l_int|1
comma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Error Recovery */
DECL|member|nil0
id|u16
id|nil0
suffix:semicolon
multiline_comment|/* nothing */
DECL|member|dataptr
id|u32
id|dataptr
suffix:semicolon
multiline_comment|/* Data or Scatter List ptr */
DECL|member|datalen
id|u32
id|datalen
suffix:semicolon
multiline_comment|/* Data or Scatter List len */
DECL|member|statusptr
id|u32
id|statusptr
suffix:semicolon
multiline_comment|/* Status Block ptr */
DECL|member|linkptr
id|u32
id|linkptr
suffix:semicolon
multiline_comment|/* Chain Address */
DECL|member|nil1
id|u32
id|nil1
suffix:semicolon
multiline_comment|/* nothing */
DECL|member|senseptr
id|u32
id|senseptr
suffix:semicolon
multiline_comment|/* Sense Info Pointer */
DECL|member|senselen
id|u8
id|senselen
suffix:semicolon
multiline_comment|/* Sense Length */
DECL|member|cdblen
id|u8
id|cdblen
suffix:semicolon
multiline_comment|/* CDB Length */
DECL|member|datacheck
id|u16
id|datacheck
suffix:semicolon
multiline_comment|/* Data checksum */
DECL|member|cdb
id|u8
id|cdb
(braket
id|MAX_CDB
)braket
suffix:semicolon
multiline_comment|/* CDB area */
multiline_comment|/* Hardware defined portion ends here, rest is driver defined */
DECL|member|sense
id|u8
id|sense
(braket
id|MAX_SENSE
)braket
suffix:semicolon
multiline_comment|/* Sense area */
DECL|member|status
id|u8
id|status
(braket
id|MAX_STATUS
)braket
suffix:semicolon
multiline_comment|/* Status area */
DECL|member|SCpnt
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
multiline_comment|/* Link to the SCSI Command Block */
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Completion Function */
)brace
suffix:semicolon
DECL|macro|AHA1740CMD_NOP
mdefine_line|#define&t;AHA1740CMD_NOP&t; 0x00&t;/* No OP */
DECL|macro|AHA1740CMD_INIT
mdefine_line|#define AHA1740CMD_INIT&t; 0x01&t;/* Initiator SCSI Command */
DECL|macro|AHA1740CMD_DIAG
mdefine_line|#define AHA1740CMD_DIAG&t; 0x05&t;/* Run Diagnostic Command */
DECL|macro|AHA1740CMD_SCSI
mdefine_line|#define AHA1740CMD_SCSI&t; 0x06&t;/* Initialize SCSI */
DECL|macro|AHA1740CMD_SENSE
mdefine_line|#define AHA1740CMD_SENSE 0x08&t;/* Read Sense Information */
DECL|macro|AHA1740CMD_DOWN
mdefine_line|#define AHA1740CMD_DOWN  0x09&t;/* Download Firmware (yeah, I bet!) */
DECL|macro|AHA1740CMD_RINQ
mdefine_line|#define AHA1740CMD_RINQ  0x0a&t;/* Read Host Adapter Inquiry Data */
DECL|macro|AHA1740CMD_TARG
mdefine_line|#define AHA1740CMD_TARG  0x10&t;/* Target SCSI Command */
r_int
id|aha1740_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|aha1740_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|aha1740_queuecommand
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
id|aha1740_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|aha1740_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|aha1740_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|aha1740_proc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
DECL|macro|AHA1740_ECBS
mdefine_line|#define AHA1740_ECBS 32
DECL|macro|AHA1740_SCATTER
mdefine_line|#define AHA1740_SCATTER 16
DECL|macro|AHA1740_CMDLUN
mdefine_line|#define AHA1740_CMDLUN 1
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
DECL|macro|AHA1740
mdefine_line|#define AHA1740 {  proc_name:      &quot;aha1740&quot;,&t;&t;&t;&t;&bslash;&n;&t;&t;   proc_info:      aha1740_proc_info,&t;                &bslash;&n;&t;&t;   name:           &quot;Adaptec 174x (EISA)&quot;,&t;&t;&bslash;&n;&t;&t;   detect:         aha1740_detect,&t;&t;&t;&bslash;&n;&t;&t;   command:        aha1740_command,&t;&t;&t;&bslash;&n;&t;&t;   queuecommand:   aha1740_queuecommand,&t;&t;&bslash;&n;&t;&t;   abort:          aha1740_abort,&t;&t;&t;&bslash;&n;&t;&t;   reset:          aha1740_reset,&t;&t;&t;&bslash;&n;&t;&t;   bios_param:     aha1740_biosparam,                   &bslash;&n;&t;&t;   can_queue:      AHA1740_ECBS, &t;&t;&t;&bslash;&n;&t;&t;   this_id:        7, &t;&t;&t;&t;&t;&bslash;&n;&t;&t;   sg_tablesize:   AHA1740_SCATTER, &t;&t;&t;&bslash;&n;&t;&t;   cmd_per_lun:    AHA1740_CMDLUN, &t;&t;&t;&bslash;&n;&t;&t;   use_clustering: ENABLE_CLUSTERING}
macro_line|#endif
eof
