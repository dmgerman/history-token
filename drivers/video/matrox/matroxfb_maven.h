macro_line|#ifndef __MATROXFB_MAVEN_H__
DECL|macro|__MATROXFB_MAVEN_H__
mdefine_line|#define __MATROXFB_MAVEN_H__
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &quot;matroxfb_base.h&quot;
r_struct
id|matroxfb_dh_maven_info
suffix:semicolon
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
id|matroxfb_dh_maven_info
op_star
id|minfo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|matroxfb_dh_maven_info
r_struct
id|matroxfb_dh_maven_info
(brace
DECL|member|primary_dev
r_struct
id|matrox_fb_info
op_star
id|primary_dev
suffix:semicolon
DECL|member|maven
r_struct
id|i2c_bit_adapter
id|maven
suffix:semicolon
DECL|member|ddc1
r_struct
id|i2c_bit_adapter
id|ddc1
suffix:semicolon
DECL|member|ddc2
r_struct
id|i2c_bit_adapter
id|ddc2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __MATROXFB_MAVEN_H__ */
eof
