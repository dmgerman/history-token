multiline_comment|/*&n; * Flags for SCSI devices that need special treatment&n; */
DECL|macro|BLIST_NOLUN
mdefine_line|#define BLIST_NOLUN     &t;0x001&t;/* Only scan LUN 0 */
DECL|macro|BLIST_FORCELUN
mdefine_line|#define BLIST_FORCELUN  &t;0x002&t;/* Known to have LUNs, force scanning */
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
mdefine_line|#define BLIST_NOSTARTONADD      0x1000  /* do not do automatic start on add */
eof
