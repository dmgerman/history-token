multiline_comment|/*&n; * Exported symbols for audio driver.&n; */
macro_line|#include &lt;linux/module.h&gt;
DECL|variable|audio_syms_symbol
r_char
id|audio_syms_symbol
suffix:semicolon
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;sound_calls.h&quot;
DECL|variable|DMAbuf_start_dma
id|EXPORT_SYMBOL
c_func
(paren
id|DMAbuf_start_dma
)paren
suffix:semicolon
DECL|variable|DMAbuf_open_dma
id|EXPORT_SYMBOL
c_func
(paren
id|DMAbuf_open_dma
)paren
suffix:semicolon
DECL|variable|DMAbuf_close_dma
id|EXPORT_SYMBOL
c_func
(paren
id|DMAbuf_close_dma
)paren
suffix:semicolon
DECL|variable|DMAbuf_inputintr
id|EXPORT_SYMBOL
c_func
(paren
id|DMAbuf_inputintr
)paren
suffix:semicolon
DECL|variable|DMAbuf_outputintr
id|EXPORT_SYMBOL
c_func
(paren
id|DMAbuf_outputintr
)paren
suffix:semicolon
eof
