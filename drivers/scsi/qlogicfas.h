multiline_comment|/* to be used by qlogicfas and qlogic_cs */
macro_line|#ifndef __QLOGICFAS_H
DECL|macro|__QLOGICFAS_H
mdefine_line|#define __QLOGICFAS_H
DECL|struct|qlogicfas_priv
r_struct
id|qlogicfas_priv
(brace
DECL|member|qbase
r_int
id|qbase
suffix:semicolon
multiline_comment|/* Port */
DECL|member|qinitid
r_int
id|qinitid
suffix:semicolon
multiline_comment|/* initiator ID */
DECL|member|qabort
r_int
id|qabort
suffix:semicolon
multiline_comment|/* Flag to cause an abort */
DECL|member|qlirq
r_int
id|qlirq
suffix:semicolon
multiline_comment|/* IRQ being used */
DECL|member|qinfo
r_char
id|qinfo
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* description */
DECL|member|qlcmd
id|Scsi_Cmnd
op_star
id|qlcmd
suffix:semicolon
multiline_comment|/* current command being processed */
)brace
suffix:semicolon
DECL|typedef|qlogicfas_priv_t
r_typedef
r_struct
id|qlogicfas_priv
op_star
id|qlogicfas_priv_t
suffix:semicolon
macro_line|#endif&t;/* __QLOGICFAS_H */
eof
