macro_line|#ifndef _SCSI_SCSI_DEVINFO_H
DECL|macro|_SCSI_SCSI_DEVINFO_H
mdefine_line|#define _SCSI_SCSI_DEVINFO_H
multiline_comment|/*&n; * Flags for SCSI devices that need special treatment&n; */
DECL|macro|BLIST_NOLUN
mdefine_line|#define BLIST_NOLUN     &t;0x001&t;/* Only scan LUN 0 */
DECL|macro|BLIST_FORCELUN
mdefine_line|#define BLIST_FORCELUN  &t;0x002&t;/* Known to have LUNs, force scanning,&n;&t;&t;&t;&t;&t;   deprecated: Use max_luns=N */
DECL|macro|BLIST_BORKEN
mdefine_line|#define BLIST_BORKEN    &t;0x004&t;/* Flag for broken handshaking */
DECL|macro|BLIST_KEY
mdefine_line|#define BLIST_KEY       &t;0x008&t;/* unlock by special command */
DECL|macro|BLIST_SINGLELUN
mdefine_line|#define BLIST_SINGLELUN &t;0x010&t;/* Do not use LUNs in parallel */
DECL|macro|BLIST_NOTQ
mdefine_line|#define BLIST_NOTQ&t;&t;0x020&t;/* Buggy Tagged Command Queuing */
DECL|macro|BLIST_SPARSELUN
mdefine_line|#define BLIST_SPARSELUN &t;0x040&t;/* Non consecutive LUN numbering */
DECL|macro|BLIST_MAX5LUN
mdefine_line|#define BLIST_MAX5LUN&t;&t;0x080&t;/* Avoid LUNS &gt;= 5 */
DECL|macro|BLIST_ISROM
mdefine_line|#define BLIST_ISROM     &t;0x100&t;/* Treat as (removable) CD-ROM */
DECL|macro|BLIST_LARGELUN
mdefine_line|#define BLIST_LARGELUN&t;&t;0x200&t;/* LUNs past 7 on a SCSI-2 device */
DECL|macro|BLIST_INQUIRY_36
mdefine_line|#define BLIST_INQUIRY_36&t;0x400&t;/* override additional length field */
DECL|macro|BLIST_INQUIRY_58
mdefine_line|#define BLIST_INQUIRY_58&t;0x800&t;/* ... for broken inquiry responses */
DECL|macro|BLIST_NOSTARTONADD
mdefine_line|#define BLIST_NOSTARTONADD&t;0x1000&t;/* do not do automatic start on add */
DECL|macro|BLIST_MS_SKIP_PAGE_08
mdefine_line|#define BLIST_MS_SKIP_PAGE_08&t;0x2000&t;/* do not send ms page 0x08 */
DECL|macro|BLIST_MS_SKIP_PAGE_3F
mdefine_line|#define BLIST_MS_SKIP_PAGE_3F&t;0x4000&t;/* do not send ms page 0x3f */
DECL|macro|BLIST_USE_10_BYTE_MS
mdefine_line|#define BLIST_USE_10_BYTE_MS&t;0x8000&t;/* use 10 byte ms before 6 byte ms */
DECL|macro|BLIST_MS_192_BYTES_FOR_3F
mdefine_line|#define BLIST_MS_192_BYTES_FOR_3F&t;0x10000&t;/*  192 byte ms page 0x3f request */
DECL|macro|BLIST_REPORTLUN2
mdefine_line|#define BLIST_REPORTLUN2&t;0x20000&t;/* try REPORT_LUNS even for SCSI-2 devs&n; &t;&t;&t;&t;&t;   (if HBA supports more than 8 LUNs) */
DECL|macro|BLIST_NOREPORTLUN
mdefine_line|#define BLIST_NOREPORTLUN&t;0x40000&t;/* don&squot;t try REPORT_LUNS scan (SCSI-3 devs) */
DECL|macro|BLIST_NOT_LOCKABLE
mdefine_line|#define BLIST_NOT_LOCKABLE&t;0x80000&t;/* don&squot;t use PREVENT-ALLOW commands */
DECL|macro|BLIST_NO_ULD_ATTACH
mdefine_line|#define BLIST_NO_ULD_ATTACH&t;0x100000 /* device is actually for RAID config */
macro_line|#endif
eof
