macro_line|#ifndef _AHA1542_H
multiline_comment|/* $Id: aha1542.h,v 1.1 1992/07/24 06:27:38 root Exp root $&n; *&n; * Header file for the adaptec 1542 driver for Linux&n; *&n; * $Log: aha1542.h,v $&n; * Revision 1.1  1992/07/24  06:27:38  root&n; * Initial revision&n; *&n; * Revision 1.2  1992/07/04  18:41:49  root&n; * Replaced distribution with current drivers&n; *&n; * Revision 1.3  1992/06/23  23:58:20  root&n; * Fixes.&n; *&n; * Revision 1.2  1992/05/26  22:13:23  root&n; * Changed bug that prevented DMA above first 2 mbytes.&n; *&n; * Revision 1.1  1992/05/22  21:00:29  root&n; * Initial revision&n; *&n; * Revision 1.1  1992/04/24  18:01:50  root&n; * Initial revision&n; *&n; * Revision 1.1  1992/04/02  03:23:13  drew&n; * Initial revision&n; *&n; * Revision 1.3  1992/01/27  14:46:29  tthorn&n; * *** empty log message ***&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
multiline_comment|/* I/O Port interface 4.2 */
multiline_comment|/* READ */
DECL|macro|STATUS
mdefine_line|#define STATUS(base) base
DECL|macro|STST
mdefine_line|#define STST&t;0x80&t;&t;/* Self Test in Progress */
DECL|macro|DIAGF
mdefine_line|#define DIAGF&t;0x40&t;&t;/* Internal Diagnostic Failure */
DECL|macro|INIT
mdefine_line|#define INIT&t;0x20&t;&t;/* Mailbox Initialization Required */
DECL|macro|IDLE
mdefine_line|#define IDLE&t;0x10&t;&t;/* SCSI Host Adapter Idle */
DECL|macro|CDF
mdefine_line|#define CDF&t;0x08&t;&t;/* Command/Data Out Port Full */
DECL|macro|DF
mdefine_line|#define DF&t;0x04&t;&t;/* Data In Port Full */
DECL|macro|INVDCMD
mdefine_line|#define INVDCMD&t;0x01&t;&t;/* Invalid H A Command */
DECL|macro|STATMASK
mdefine_line|#define STATMASK 0xfd&t;&t;/* 0x02 is reserved */
DECL|macro|INTRFLAGS
mdefine_line|#define INTRFLAGS(base) (STATUS(base)+2)
DECL|macro|ANYINTR
mdefine_line|#define ANYINTR&t;0x80&t;&t;/* Any Interrupt */
DECL|macro|SCRD
mdefine_line|#define SCRD&t;0x08&t;&t;/* SCSI Reset Detected */
DECL|macro|HACC
mdefine_line|#define HACC&t;0x04&t;&t;/* HA Command Complete */
DECL|macro|MBOA
mdefine_line|#define MBOA&t;0x02&t;&t;/* MBO Empty */
DECL|macro|MBIF
mdefine_line|#define MBIF&t;0x01&t;&t;/* MBI Full */
DECL|macro|INTRMASK
mdefine_line|#define INTRMASK 0x8f
multiline_comment|/* WRITE */
DECL|macro|CONTROL
mdefine_line|#define CONTROL(base) STATUS(base)
DECL|macro|HRST
mdefine_line|#define HRST&t;0x80&t;&t;/* Hard Reset */
DECL|macro|SRST
mdefine_line|#define SRST&t;0x40&t;&t;/* Soft Reset */
DECL|macro|IRST
mdefine_line|#define IRST&t;0x20&t;&t;/* Interrupt Reset */
DECL|macro|SCRST
mdefine_line|#define SCRST&t;0x10&t;&t;/* SCSI Bus Reset */
multiline_comment|/* READ/WRITE */
DECL|macro|DATA
mdefine_line|#define DATA(base) (STATUS(base)+1)
DECL|macro|CMD_NOP
mdefine_line|#define CMD_NOP&t;&t;0x00&t;/* No Operation */
DECL|macro|CMD_MBINIT
mdefine_line|#define CMD_MBINIT&t;0x01&t;/* Mailbox Initialization */
DECL|macro|CMD_START_SCSI
mdefine_line|#define CMD_START_SCSI&t;0x02&t;/* Start SCSI Command */
DECL|macro|CMD_INQUIRY
mdefine_line|#define CMD_INQUIRY&t;0x04&t;/* Adapter Inquiry */
DECL|macro|CMD_EMBOI
mdefine_line|#define CMD_EMBOI&t;0x05&t;/* Enable MailBox Out Interrupt */
DECL|macro|CMD_BUSON_TIME
mdefine_line|#define CMD_BUSON_TIME&t;0x07&t;/* Set Bus-On Time */
DECL|macro|CMD_BUSOFF_TIME
mdefine_line|#define CMD_BUSOFF_TIME&t;0x08&t;/* Set Bus-Off Time */
DECL|macro|CMD_DMASPEED
mdefine_line|#define CMD_DMASPEED&t;0x09&t;/* Set AT Bus Transfer Speed */
DECL|macro|CMD_RETDEVS
mdefine_line|#define CMD_RETDEVS&t;0x0a&t;/* Return Installed Devices */
DECL|macro|CMD_RETCONF
mdefine_line|#define CMD_RETCONF&t;0x0b&t;/* Return Configuration Data */
DECL|macro|CMD_RETSETUP
mdefine_line|#define CMD_RETSETUP&t;0x0d&t;/* Return Setup Data */
DECL|macro|CMD_ECHO
mdefine_line|#define CMD_ECHO&t;0x1f&t;/* ECHO Command Data */
DECL|macro|CMD_EXTBIOS
mdefine_line|#define CMD_EXTBIOS     0x28    /* Return extend bios information only 1542C */
DECL|macro|CMD_MBENABLE
mdefine_line|#define CMD_MBENABLE    0x29    /* Set Mailbox Interface enable only 1542C */
multiline_comment|/* Mailbox Definition 5.2.1 and 5.2.2 */
DECL|struct|mailbox
r_struct
id|mailbox
(brace
DECL|member|status
id|unchar
id|status
suffix:semicolon
multiline_comment|/* Command/Status */
DECL|member|ccbptr
id|unchar
id|ccbptr
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* msb, .., lsb */
)brace
suffix:semicolon
multiline_comment|/* This is used with scatter-gather */
DECL|struct|chain
r_struct
id|chain
(brace
DECL|member|datalen
id|unchar
id|datalen
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Size of this part of chain */
DECL|member|dataptr
id|unchar
id|dataptr
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Location of data */
)brace
suffix:semicolon
multiline_comment|/* These belong in scsi.h also */
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
DECL|struct|ccb
r_struct
id|ccb
(brace
multiline_comment|/* Command Control Block 5.3 */
DECL|member|op
id|unchar
id|op
suffix:semicolon
multiline_comment|/* Command Control Block Operation Code */
DECL|member|idlun
id|unchar
id|idlun
suffix:semicolon
multiline_comment|/* op=0,2:Target Id, op=1:Initiator Id */
multiline_comment|/* Outbound data transfer, length is checked*/
multiline_comment|/* Inbound data transfer, length is checked */
multiline_comment|/* Logical Unit Number */
DECL|member|cdblen
id|unchar
id|cdblen
suffix:semicolon
multiline_comment|/* SCSI Command Length */
DECL|member|rsalen
id|unchar
id|rsalen
suffix:semicolon
multiline_comment|/* Request Sense Allocation Length/Disable */
DECL|member|datalen
id|unchar
id|datalen
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Data Length (msb, .., lsb) */
DECL|member|dataptr
id|unchar
id|dataptr
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Data Pointer */
DECL|member|linkptr
id|unchar
id|linkptr
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Link Pointer */
DECL|member|commlinkid
id|unchar
id|commlinkid
suffix:semicolon
multiline_comment|/* Command Linking Identifier */
DECL|member|hastat
id|unchar
id|hastat
suffix:semicolon
multiline_comment|/* Host Adapter Status (HASTAT) */
DECL|member|tarstat
id|unchar
id|tarstat
suffix:semicolon
multiline_comment|/* Target Device Status */
DECL|member|reserved
id|unchar
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|cdb
id|unchar
id|cdb
(braket
id|MAX_CDB
op_plus
id|MAX_SENSE
)braket
suffix:semicolon
multiline_comment|/* SCSI Command Descriptor Block */
multiline_comment|/* REQUEST SENSE */
)brace
suffix:semicolon
r_static
r_int
id|aha1542_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_static
r_int
id|aha1542_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|aha1542_queuecommand
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
r_static
r_int
id|aha1542_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|aha1542_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|aha1542_dev_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|aha1542_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|aha1542_old_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|aha1542_old_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|aha1542_biosparam
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
DECL|macro|AHA1542_MAILBOXES
mdefine_line|#define AHA1542_MAILBOXES 8
DECL|macro|AHA1542_SCATTER
mdefine_line|#define AHA1542_SCATTER 16
DECL|macro|AHA1542_CMDLUN
mdefine_line|#define AHA1542_CMDLUN 1
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
DECL|macro|AHA1542
mdefine_line|#define AHA1542 {    proc_name:&t;&t;&t;&quot;aha1542&quot;,&t;&t;&bslash;&n;&t;&t;     name:&t;&t;&t;&quot;Adaptec 1542&quot;, &t;&bslash;&n;&t;&t;     detect:&t;&t;&t;aha1542_detect,&t;&t;&bslash;&n;&t;&t;     command:&t;&t;&t;aha1542_command,&t;&bslash;&n;&t;&t;     queuecommand:&t;&t;aha1542_queuecommand,&t;&bslash;&n;                     abort:&t;&t;        aha1542_old_abort,&t;&bslash;&n;                     reset:&t;&t;&t;aha1542_old_reset,&t;&bslash;&n;&t;&t;     eh_abort_handler:&t;&t;aha1542_abort,&t;&t;&bslash;&n;&t;&t;     eh_device_reset_handler:&t;aha1542_dev_reset,&t;&bslash;&n;&t;&t;     eh_bus_reset_handler:&t;aha1542_bus_reset,&t;&bslash;&n;&t;&t;     eh_host_reset_handler:&t;aha1542_host_reset,&t;&bslash;&n;&t;&t;     bios_param:&t;&t;aha1542_biosparam,      &bslash;&n;&t;&t;     can_queue:&t;&t;&t;AHA1542_MAILBOXES, &t;&bslash;&n;&t;&t;     this_id:&t;&t;&t;7, &t;&t;&t;&bslash;&n;&t;&t;     sg_tablesize:&t;&t;AHA1542_SCATTER, &t;&bslash;&n;&t;&t;     cmd_per_lun:&t;&t;AHA1542_CMDLUN, &t;&bslash;&n;&t;&t;     unchecked_isa_dma:&t;&t;1, &t;&t;&t;&bslash;&n;&t;&t;     use_clustering:&t;&t;ENABLE_CLUSTERING&t;&bslash;&n;}
macro_line|#endif
eof
