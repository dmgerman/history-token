macro_line|#ifndef __LINUX_MATROXFB_H__
DECL|macro|__LINUX_MATROXFB_H__
mdefine_line|#define __LINUX_MATROXFB_H__
macro_line|#include &lt;asm/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|struct|matroxioc_output_mode
r_struct
id|matroxioc_output_mode
(brace
DECL|member|output
id|__u32
id|output
suffix:semicolon
multiline_comment|/* which output */
DECL|macro|MATROXFB_OUTPUT_PRIMARY
mdefine_line|#define MATROXFB_OUTPUT_PRIMARY&t;&t;0x0000
DECL|macro|MATROXFB_OUTPUT_SECONDARY
mdefine_line|#define MATROXFB_OUTPUT_SECONDARY&t;0x0001
DECL|macro|MATROXFB_OUTPUT_DFP
mdefine_line|#define MATROXFB_OUTPUT_DFP&t;&t;0x0002
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
multiline_comment|/* which mode */
DECL|macro|MATROXFB_OUTPUT_MODE_PAL
mdefine_line|#define MATROXFB_OUTPUT_MODE_PAL&t;0x0001
DECL|macro|MATROXFB_OUTPUT_MODE_NTSC
mdefine_line|#define MATROXFB_OUTPUT_MODE_NTSC&t;0x0002
DECL|macro|MATROXFB_OUTPUT_MODE_MONITOR
mdefine_line|#define MATROXFB_OUTPUT_MODE_MONITOR&t;0x0080
)brace
suffix:semicolon
DECL|macro|MATROXFB_SET_OUTPUT_MODE
mdefine_line|#define MATROXFB_SET_OUTPUT_MODE&t;_IOW(&squot;n&squot;,0xFA,sizeof(struct matroxioc_output_mode))
DECL|macro|MATROXFB_GET_OUTPUT_MODE
mdefine_line|#define MATROXFB_GET_OUTPUT_MODE&t;_IOWR(&squot;n&squot;,0xFA,sizeof(struct matroxioc_output_mode))
multiline_comment|/* bitfield */
DECL|macro|MATROXFB_OUTPUT_CONN_PRIMARY
mdefine_line|#define MATROXFB_OUTPUT_CONN_PRIMARY&t;(1 &lt;&lt; MATROXFB_OUTPUT_PRIMARY)
DECL|macro|MATROXFB_OUTPUT_CONN_SECONDARY
mdefine_line|#define MATROXFB_OUTPUT_CONN_SECONDARY&t;(1 &lt;&lt; MATROXFB_OUTPUT_SECONDARY)
DECL|macro|MATROXFB_OUTPUT_CONN_DFP
mdefine_line|#define MATROXFB_OUTPUT_CONN_DFP&t;(1 &lt;&lt; MATROXFB_OUTPUT_DFP)
multiline_comment|/* connect these outputs to this framebuffer */
DECL|macro|MATROXFB_SET_OUTPUT_CONNECTION
mdefine_line|#define MATROXFB_SET_OUTPUT_CONNECTION&t;_IOW(&squot;n&squot;,0xF8,sizeof(__u32))
multiline_comment|/* which outputs are connected to this framebuffer */
DECL|macro|MATROXFB_GET_OUTPUT_CONNECTION
mdefine_line|#define MATROXFB_GET_OUTPUT_CONNECTION&t;_IOR(&squot;n&squot;,0xF8,sizeof(__u32))
multiline_comment|/* which outputs are available for this framebuffer */
DECL|macro|MATROXFB_GET_AVAILABLE_OUTPUTS
mdefine_line|#define MATROXFB_GET_AVAILABLE_OUTPUTS&t;_IOR(&squot;n&squot;,0xF9,sizeof(__u32))
multiline_comment|/* which outputs exist on this framebuffer */
DECL|macro|MATROXFB_GET_ALL_OUTPUTS
mdefine_line|#define MATROXFB_GET_ALL_OUTPUTS&t;_IOR(&squot;n&squot;,0xFB,sizeof(__u32))
macro_line|#endif
eof
