macro_line|#include &lt;dvbdev.h&gt;
macro_line|#include &lt;dmxdev.h&gt;
macro_line|#include &lt;dvb_demux.h&gt;
macro_line|#include &lt;dvb_net.h&gt;
macro_line|#include &lt;dvb_frontend.h&gt;
DECL|struct|videobuf_dvb
r_struct
id|videobuf_dvb
(brace
multiline_comment|/* filling that the job of the driver */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|frontend
r_struct
id|dvb_frontend
op_star
id|frontend
suffix:semicolon
DECL|member|dvbq
r_struct
id|videobuf_queue
id|dvbq
suffix:semicolon
multiline_comment|/* video-buf-dvb state info */
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|thread
r_struct
id|task_struct
op_star
id|thread
suffix:semicolon
DECL|member|nfeeds
r_int
id|nfeeds
suffix:semicolon
multiline_comment|/* videobuf_dvb_(un)register manges this */
DECL|member|adapter
r_struct
id|dvb_adapter
op_star
id|adapter
suffix:semicolon
DECL|member|demux
r_struct
id|dvb_demux
id|demux
suffix:semicolon
DECL|member|dmxdev
r_struct
id|dmxdev
id|dmxdev
suffix:semicolon
DECL|member|fe_hw
r_struct
id|dmx_frontend
id|fe_hw
suffix:semicolon
DECL|member|fe_mem
r_struct
id|dmx_frontend
id|fe_mem
suffix:semicolon
DECL|member|net
r_struct
id|dvb_net
id|net
suffix:semicolon
)brace
suffix:semicolon
r_int
id|videobuf_dvb_register
c_func
(paren
r_struct
id|videobuf_dvb
op_star
id|dvb
)paren
suffix:semicolon
r_void
id|videobuf_dvb_unregister
c_func
(paren
r_struct
id|videobuf_dvb
op_star
id|dvb
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
