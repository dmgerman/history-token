macro_line|#ifndef MSP3400_H
DECL|macro|MSP3400_H
mdefine_line|#define MSP3400_H
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|struct|msp_dfpreg
r_struct
id|msp_dfpreg
(brace
DECL|member|reg
r_int
id|reg
suffix:semicolon
DECL|member|value
r_int
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MSP_SET_DFPREG
mdefine_line|#define MSP_SET_DFPREG     _IOW(&squot;m&squot;,15,struct msp_dfpreg)
DECL|macro|MSP_GET_DFPREG
mdefine_line|#define MSP_GET_DFPREG     _IOW(&squot;m&squot;,16,struct msp_dfpreg)
macro_line|#endif /* MSP3400_H */
eof
