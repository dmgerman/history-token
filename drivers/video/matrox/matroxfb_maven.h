macro_line|#ifndef __MATROXFB_MAVEN_H__
DECL|macro|__MATROXFB_MAVEN_H__
mdefine_line|#define __MATROXFB_MAVEN_H__
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &quot;matroxfb_base.h&quot;
DECL|struct|i2c_bit_adapter
r_struct
id|i2c_bit_adapter
(brace
DECL|member|adapter
r_struct
id|i2c_adapter
id|adapter
suffix:semicolon
DECL|member|initialized
r_int
id|initialized
suffix:semicolon
DECL|member|bac
r_struct
id|i2c_algo_bit_data
id|bac
suffix:semicolon
DECL|member|minfo
r_struct
id|matrox_fb_info
op_star
id|minfo
suffix:semicolon
r_struct
(brace
DECL|member|data
r_int
r_int
id|data
suffix:semicolon
DECL|member|clock
r_int
r_int
id|clock
suffix:semicolon
DECL|member|mask
)brace
id|mask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __MATROXFB_MAVEN_H__ */
eof
