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
DECL|struct|msp_matrix
r_struct
id|msp_matrix
(brace
DECL|member|input
r_int
id|input
suffix:semicolon
DECL|member|output
r_int
id|output
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MSP_SET_DFPREG
mdefine_line|#define MSP_SET_DFPREG     _IOW(&squot;m&squot;,15,struct msp_dfpreg)
DECL|macro|MSP_GET_DFPREG
mdefine_line|#define MSP_GET_DFPREG     _IOW(&squot;m&squot;,16,struct msp_dfpreg)
multiline_comment|/* ioctl for MSP_SET_MATRIX will have to be registered */
DECL|macro|MSP_SET_MATRIX
mdefine_line|#define MSP_SET_MATRIX     _IOW(&squot;m&squot;,17,struct msp_matrix)
DECL|macro|SCART_MASK
mdefine_line|#define SCART_MASK    0
DECL|macro|SCART_IN1
mdefine_line|#define SCART_IN1     1
DECL|macro|SCART_IN2
mdefine_line|#define SCART_IN2     2
DECL|macro|SCART_IN1_DA
mdefine_line|#define SCART_IN1_DA  3
DECL|macro|SCART_IN2_DA
mdefine_line|#define SCART_IN2_DA  4
DECL|macro|SCART_IN3
mdefine_line|#define SCART_IN3     5
DECL|macro|SCART_IN4
mdefine_line|#define SCART_IN4     6
DECL|macro|SCART_MONO
mdefine_line|#define SCART_MONO    7
DECL|macro|SCART_MUTE
mdefine_line|#define SCART_MUTE    8
DECL|macro|SCART_DSP_IN
mdefine_line|#define SCART_DSP_IN  0
DECL|macro|SCART1_OUT
mdefine_line|#define SCART1_OUT    1
DECL|macro|SCART2_OUT
mdefine_line|#define SCART2_OUT    2
macro_line|#endif /* MSP3400_H */
eof
