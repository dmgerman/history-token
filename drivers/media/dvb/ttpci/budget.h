macro_line|#ifndef __BUDGET_DVB__
DECL|macro|__BUDGET_DVB__
mdefine_line|#define __BUDGET_DVB__
macro_line|#include &lt;media/saa7146.h&gt;
macro_line|#include &quot;dvb_i2c.h&quot;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;dvbdev.h&quot;
macro_line|#include &quot;demux.h&quot;
macro_line|#include &quot;dvb_demux.h&quot;
macro_line|#include &quot;dmxdev.h&quot;
macro_line|#include &quot;dvb_filter.h&quot;
macro_line|#include &quot;dvb_net.h&quot;
r_extern
r_int
id|budget_debug
suffix:semicolon
DECL|struct|budget_info
r_struct
id|budget_info
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* place to store all the necessary device information */
DECL|struct|budget
r_struct
id|budget
(brace
multiline_comment|/* devices */
DECL|member|dvb_dev
r_struct
id|dvb_device
id|dvb_dev
suffix:semicolon
DECL|member|dvb_net
r_struct
id|dvb_net
id|dvb_net
suffix:semicolon
DECL|member|dev
r_struct
id|saa7146_dev
op_star
id|dev
suffix:semicolon
DECL|member|i2c_bus
r_struct
id|dvb_i2c_bus
op_star
id|i2c_bus
suffix:semicolon
DECL|member|card
r_struct
id|budget_info
op_star
id|card
suffix:semicolon
DECL|member|grabbing
r_int
r_char
op_star
id|grabbing
suffix:semicolon
DECL|member|pt
r_struct
id|saa7146_pgtable
id|pt
suffix:semicolon
DECL|member|fidb_tasklet
r_struct
id|tasklet_struct
id|fidb_tasklet
suffix:semicolon
DECL|member|vpe_tasklet
r_struct
id|tasklet_struct
id|vpe_tasklet
suffix:semicolon
DECL|member|dmxdev
r_struct
id|dmxdev
id|dmxdev
suffix:semicolon
DECL|member|demux
r_struct
id|dvb_demux
id|demux
suffix:semicolon
DECL|member|hw_frontend
r_struct
id|dmx_frontend
id|hw_frontend
suffix:semicolon
DECL|member|mem_frontend
r_struct
id|dmx_frontend
id|mem_frontend
suffix:semicolon
DECL|member|fe_synced
r_int
id|fe_synced
suffix:semicolon
DECL|member|pid_mutex
r_struct
id|semaphore
id|pid_mutex
suffix:semicolon
DECL|member|tsf
id|u8
id|tsf
suffix:semicolon
DECL|member|ttbp
id|u32
id|ttbp
suffix:semicolon
DECL|member|feeding
r_int
id|feeding
suffix:semicolon
DECL|member|dvb_adapter
r_struct
id|dvb_adapter
op_star
id|dvb_adapter
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAKE_BUDGET_INFO
mdefine_line|#define MAKE_BUDGET_INFO(x_var,x_name,x_type) &bslash;&n;static struct budget_info x_var ## _info = { &bslash;&n;&t;.name=x_name,&t;&bslash;&n;&t;.type=x_type };&t;&bslash;&n;static struct saa7146_pci_extension_data x_var = { &bslash;&n;&t;.ext_priv = &amp;x_var ## _info, &bslash;&n;&t;.ext = &amp;budget_extension };
DECL|macro|TS_WIDTH
mdefine_line|#define TS_WIDTH  (4*188)
DECL|macro|TS_HEIGHT
mdefine_line|#define TS_HEIGHT (1024/4)
DECL|macro|TS_BUFLEN
mdefine_line|#define TS_BUFLEN (TS_WIDTH*TS_HEIGHT)
DECL|macro|TS_MAX_PACKETS
mdefine_line|#define TS_MAX_PACKETS (TS_BUFLEN/TS_SIZE)
DECL|macro|BUDGET_TT
mdefine_line|#define BUDGET_TT&t;&t;   0
DECL|macro|BUDGET_TT_HW_DISEQC
mdefine_line|#define BUDGET_TT_HW_DISEQC&t;   1
DECL|macro|BUDGET_KNC1
mdefine_line|#define BUDGET_KNC1&t;&t;   2
DECL|macro|BUDGET_PATCH
mdefine_line|#define BUDGET_PATCH&t;&t;   3
r_extern
r_int
id|ttpci_budget_init
(paren
r_struct
id|budget
op_star
id|budget
comma
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_pci_extension_data
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|ttpci_budget_deinit
(paren
r_struct
id|budget
op_star
id|budget
)paren
suffix:semicolon
r_extern
r_void
id|ttpci_budget_irq10_handler
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
id|u32
op_star
id|isr
)paren
suffix:semicolon
macro_line|#endif
eof
