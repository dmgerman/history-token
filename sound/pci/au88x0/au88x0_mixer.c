multiline_comment|/*&n; * Vortex Mixer support.&n; *&n; * There is much more than just the AC97 mixer...&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;au88x0.h&quot;
DECL|function|snd_vortex_mixer
r_static
r_int
id|__devinit
id|snd_vortex_mixer
c_func
(paren
id|vortex_t
op_star
id|vortex
)paren
(brace
id|ac97_bus_t
op_star
id|pbus
suffix:semicolon
id|ac97_template_t
id|ac97
suffix:semicolon
r_int
id|err
suffix:semicolon
r_static
id|ac97_bus_ops_t
id|ops
op_assign
(brace
dot
id|write
op_assign
id|vortex_codec_write
comma
dot
id|read
op_assign
id|vortex_codec_read
comma
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ac97_bus
c_func
(paren
id|vortex-&gt;card
comma
l_int|0
comma
op_amp
id|ops
comma
l_int|NULL
comma
op_amp
id|pbus
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ac97
comma
l_int|0
comma
r_sizeof
(paren
id|ac97
)paren
)paren
suffix:semicolon
singleline_comment|// Intialize AC97 codec stuff.
id|ac97.private_data
op_assign
id|vortex
suffix:semicolon
id|ac97.scaps
op_assign
id|AC97_SCAP_NO_SPDIF
suffix:semicolon
id|err
op_assign
id|snd_ac97_mixer
c_func
(paren
id|pbus
comma
op_amp
id|ac97
comma
op_amp
id|vortex-&gt;codec
)paren
suffix:semicolon
id|vortex-&gt;isquad
op_assign
(paren
(paren
id|vortex-&gt;codec
op_eq
l_int|NULL
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|vortex-&gt;codec-&gt;ext_id
op_amp
l_int|0x80
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
