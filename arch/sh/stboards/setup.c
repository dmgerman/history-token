multiline_comment|/*&n; * arch/sh/stboard/setup.c&n; *&n; * Copyright (C) 2001 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * STMicroelectronics ST40STB1 HARP and compatible support.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;harp.h&quot;
multiline_comment|/*&n; * Initialize the board&n; */
DECL|function|setup_harp
r_int
id|__init
id|setup_harp
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SH_STB1_HARP
r_int
r_int
id|ic8_version
comma
id|ic36_version
suffix:semicolon
id|ic8_version
op_assign
id|ctrl_inl
c_func
(paren
id|EPLD_REVID2
)paren
suffix:semicolon
id|ic36_version
op_assign
id|ctrl_inl
c_func
(paren
id|EPLD_REVID1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;STMicroelectronics STB1 HARP initialisaton&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EPLD versions: IC8: %d.%02d, IC36: %d.%02d&bslash;n&quot;
comma
(paren
id|ic8_version
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
comma
id|ic8_version
op_amp
l_int|0xf
comma
(paren
id|ic36_version
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
comma
id|ic36_version
op_amp
l_int|0xf
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_SH_STB1_OVERDRIVE)
r_int
r_int
id|version
suffix:semicolon
id|version
op_assign
id|ctrl_inl
c_func
(paren
id|EPLD_REVID
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;STMicroelectronics STB1 Overdrive initialisaton&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EPLD version: %d.%02d&bslash;n&quot;
comma
(paren
id|version
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
comma
id|version
op_amp
l_int|0xf
)paren
suffix:semicolon
macro_line|#else
macro_line|#error Undefined machine
macro_line|#endif
multiline_comment|/* Currently all STB1 chips have problems with the sleep instruction,&n;         * so disable it here.&n;         */
id|disable_hlt
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
