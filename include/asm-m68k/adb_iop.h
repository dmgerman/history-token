multiline_comment|/*&n; * ADB through the IOP&n; * Written by Joshua M. Thompson&n; */
multiline_comment|/* IOP number and channel number for ADB */
DECL|macro|ADB_IOP
mdefine_line|#define ADB_IOP&t;&t;IOP_NUM_ISM
DECL|macro|ADB_CHAN
mdefine_line|#define ADB_CHAN&t;2
multiline_comment|/* From the A/UX headers...maybe important, maybe not */
DECL|macro|ADB_IOP_LISTEN
mdefine_line|#define ADB_IOP_LISTEN&t;0x01
DECL|macro|ADB_IOP_TALK
mdefine_line|#define ADB_IOP_TALK&t;0x02
DECL|macro|ADB_IOP_EXISTS
mdefine_line|#define ADB_IOP_EXISTS&t;0x04
DECL|macro|ADB_IOP_FLUSH
mdefine_line|#define ADB_IOP_FLUSH&t;0x08
DECL|macro|ADB_IOP_RESET
mdefine_line|#define ADB_IOP_RESET&t;0x10
DECL|macro|ADB_IOP_INT
mdefine_line|#define ADB_IOP_INT&t;0x20
DECL|macro|ADB_IOP_POLL
mdefine_line|#define ADB_IOP_POLL&t;0x40
DECL|macro|ADB_IOP_UNINT
mdefine_line|#define ADB_IOP_UNINT&t;0x80
DECL|macro|AIF_RESET
mdefine_line|#define AIF_RESET&t;0x00
DECL|macro|AIF_FLUSH
mdefine_line|#define AIF_FLUSH&t;0x01
DECL|macro|AIF_LISTEN
mdefine_line|#define AIF_LISTEN&t;0x08
DECL|macro|AIF_TALK
mdefine_line|#define AIF_TALK&t;0x0C
multiline_comment|/* Flag bits in struct adb_iopmsg */
DECL|macro|ADB_IOP_EXPLICIT
mdefine_line|#define ADB_IOP_EXPLICIT&t;0x80&t;/* nonzero if explicit command */
DECL|macro|ADB_IOP_AUTOPOLL
mdefine_line|#define ADB_IOP_AUTOPOLL&t;0x40&t;/* auto/SRQ polling enabled    */
DECL|macro|ADB_IOP_SRQ
mdefine_line|#define ADB_IOP_SRQ&t;&t;0x04&t;/* SRQ detected                */
DECL|macro|ADB_IOP_TIMEOUT
mdefine_line|#define ADB_IOP_TIMEOUT&t;&t;0x02&t;/* nonzero if timeout          */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|adb_iopmsg
r_struct
id|adb_iopmsg
(brace
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
multiline_comment|/* ADB flags         */
DECL|member|count
id|__u8
id|count
suffix:semicolon
multiline_comment|/* no. of data bytes */
DECL|member|cmd
id|__u8
id|cmd
suffix:semicolon
multiline_comment|/* ADB command       */
DECL|member|data
id|__u8
id|data
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* ADB data          */
DECL|member|spare
id|__u8
id|spare
(braket
l_int|21
)braket
suffix:semicolon
multiline_comment|/* spare             */
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
eof
