macro_line|#ifndef _AV7110_H_
DECL|macro|_AV7110_H_
mdefine_line|#define _AV7110_H_
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#ifdef CONFIG_DEVFS_FS
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/dvb/video.h&gt;
macro_line|#include &lt;linux/dvb/audio.h&gt;
macro_line|#include &lt;linux/dvb/dmx.h&gt;
macro_line|#include &lt;linux/dvb/ca.h&gt;
macro_line|#include &lt;linux/dvb/osd.h&gt;
macro_line|#include &lt;linux/dvb/net.h&gt;
macro_line|#include &quot;dvbdev.h&quot;
macro_line|#include &quot;demux.h&quot;
macro_line|#include &quot;dvb_demux.h&quot;
macro_line|#include &quot;dmxdev.h&quot;
macro_line|#include &quot;dvb_filter.h&quot;
macro_line|#include &quot;dvb_net.h&quot;
macro_line|#include &quot;dvb_ringbuffer.h&quot;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;ves1820.h&quot;
macro_line|#include &quot;ves1x93.h&quot;
macro_line|#include &quot;stv0299.h&quot;
macro_line|#include &quot;tda8083.h&quot;
macro_line|#include &quot;sp8870.h&quot;
macro_line|#include &quot;stv0297.h&quot;
macro_line|#include &lt;media/saa7146_vv.h&gt;
DECL|macro|ANALOG_TUNER_VES1820
mdefine_line|#define ANALOG_TUNER_VES1820 1
DECL|macro|ANALOG_TUNER_STV0297
mdefine_line|#define ANALOG_TUNER_STV0297 2
DECL|macro|ANALOG_TUNER_VBI
mdefine_line|#define ANALOG_TUNER_VBI     0x100
r_extern
r_int
id|av7110_debug
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(level,args...) &bslash;&n;&t;    do { if ((av7110_debug &amp; level)) { printk(&quot;dvb-ttpci: %s(): &quot;, __FUNCTION__); printk(args); } } while (0)
DECL|macro|MAXFILT
mdefine_line|#define MAXFILT 32
DECL|enumerator|AV_PES_STREAM
DECL|enumerator|PS_STREAM
DECL|enumerator|TS_STREAM
DECL|enumerator|PES_STREAM
r_enum
(brace
id|AV_PES_STREAM
comma
id|PS_STREAM
comma
id|TS_STREAM
comma
id|PES_STREAM
)brace
suffix:semicolon
DECL|struct|av7110_p2t
r_struct
id|av7110_p2t
(brace
DECL|member|pes
id|u8
id|pes
(braket
id|TS_SIZE
)braket
suffix:semicolon
DECL|member|counter
id|u8
id|counter
suffix:semicolon
DECL|member|pos
r_int
r_int
id|pos
suffix:semicolon
DECL|member|frags
r_int
id|frags
suffix:semicolon
DECL|member|feed
r_struct
id|dvb_demux_feed
op_star
id|feed
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* video MPEG decoder events: */
multiline_comment|/* (code copied from dvb_frontend.c, should maybe be factored out...) */
DECL|macro|MAX_VIDEO_EVENT
mdefine_line|#define MAX_VIDEO_EVENT 8
DECL|struct|dvb_video_events
r_struct
id|dvb_video_events
(brace
DECL|member|events
r_struct
id|video_event
id|events
(braket
id|MAX_VIDEO_EVENT
)braket
suffix:semicolon
DECL|member|eventw
r_int
id|eventw
suffix:semicolon
DECL|member|eventr
r_int
id|eventr
suffix:semicolon
DECL|member|overflow
r_int
id|overflow
suffix:semicolon
DECL|member|wait_queue
id|wait_queue_head_t
id|wait_queue
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* place to store all the necessary device information */
DECL|struct|av7110
r_struct
id|av7110
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
DECL|member|v4l_dev
r_struct
id|video_device
op_star
id|v4l_dev
suffix:semicolon
DECL|member|vbi_dev
r_struct
id|video_device
op_star
id|vbi_dev
suffix:semicolon
DECL|member|dev
r_struct
id|saa7146_dev
op_star
id|dev
suffix:semicolon
DECL|member|i2c_adap
r_struct
id|i2c_adapter
id|i2c_adap
suffix:semicolon
DECL|member|card_name
r_char
op_star
id|card_name
suffix:semicolon
multiline_comment|/* support for analog module of dvb-c */
DECL|member|analog_tuner_flags
r_int
id|analog_tuner_flags
suffix:semicolon
DECL|member|current_input
r_int
id|current_input
suffix:semicolon
DECL|member|current_freq
id|u32
id|current_freq
suffix:semicolon
DECL|member|debi_tasklet
r_struct
id|tasklet_struct
id|debi_tasklet
suffix:semicolon
DECL|member|gpio_tasklet
r_struct
id|tasklet_struct
id|gpio_tasklet
suffix:semicolon
DECL|member|adac_type
r_int
id|adac_type
suffix:semicolon
multiline_comment|/* audio DAC type */
DECL|macro|DVB_ADAC_TI
mdefine_line|#define DVB_ADAC_TI       0
DECL|macro|DVB_ADAC_CRYSTAL
mdefine_line|#define DVB_ADAC_CRYSTAL  1
DECL|macro|DVB_ADAC_MSP
mdefine_line|#define DVB_ADAC_MSP      2
DECL|macro|DVB_ADAC_NONE
mdefine_line|#define DVB_ADAC_NONE    -1
multiline_comment|/* buffers */
DECL|member|iobuf
r_void
op_star
id|iobuf
suffix:semicolon
multiline_comment|/* memory for all buffers */
DECL|member|avout
r_struct
id|dvb_ringbuffer
id|avout
suffix:semicolon
multiline_comment|/* buffer for video or A/V mux */
DECL|macro|AVOUTLEN
mdefine_line|#define AVOUTLEN (128*1024)
DECL|member|aout
r_struct
id|dvb_ringbuffer
id|aout
suffix:semicolon
multiline_comment|/* buffer for audio */
DECL|macro|AOUTLEN
mdefine_line|#define AOUTLEN (64*1024)
DECL|member|bmpbuf
r_void
op_star
id|bmpbuf
suffix:semicolon
DECL|macro|BMPLEN
mdefine_line|#define BMPLEN (8*32768+1024)
multiline_comment|/* bitmap buffers and states */
DECL|member|bmpp
r_int
id|bmpp
suffix:semicolon
DECL|member|bmplen
r_int
id|bmplen
suffix:semicolon
DECL|member|bmp_state
r_volatile
r_int
id|bmp_state
suffix:semicolon
DECL|macro|BMP_NONE
mdefine_line|#define BMP_NONE     0
DECL|macro|BMP_LOADING
mdefine_line|#define BMP_LOADING  1
DECL|macro|BMP_LOADINGS
mdefine_line|#define BMP_LOADINGS 2
DECL|macro|BMP_LOADED
mdefine_line|#define BMP_LOADED   3
DECL|member|bmpq
id|wait_queue_head_t
id|bmpq
suffix:semicolon
multiline_comment|/* DEBI and polled command interface */
DECL|member|debilock
id|spinlock_t
id|debilock
suffix:semicolon
DECL|member|dcomlock
r_struct
id|semaphore
id|dcomlock
suffix:semicolon
DECL|member|debitype
r_volatile
r_int
id|debitype
suffix:semicolon
DECL|member|debilen
r_volatile
r_int
id|debilen
suffix:semicolon
multiline_comment|/* Recording and playback flags */
DECL|member|rec_mode
r_int
id|rec_mode
suffix:semicolon
DECL|member|playing
r_int
id|playing
suffix:semicolon
DECL|macro|RP_NONE
mdefine_line|#define RP_NONE  0
DECL|macro|RP_VIDEO
mdefine_line|#define RP_VIDEO 1
DECL|macro|RP_AUDIO
mdefine_line|#define RP_AUDIO 2
DECL|macro|RP_AV
mdefine_line|#define RP_AV    3
multiline_comment|/* OSD */
DECL|member|osdwin
r_int
id|osdwin
suffix:semicolon
multiline_comment|/* currently active window */
DECL|member|osdbpp
id|u16
id|osdbpp
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|osd_sema
r_struct
id|semaphore
id|osd_sema
suffix:semicolon
multiline_comment|/* CA */
DECL|member|ci_slot
id|ca_slot_info_t
id|ci_slot
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|vidmode
r_int
id|vidmode
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
multiline_comment|/* for budget mode demux1 */
DECL|member|dmxdev1
r_struct
id|dmxdev
id|dmxdev1
suffix:semicolon
DECL|member|demux1
r_struct
id|dvb_demux
id|demux1
suffix:semicolon
DECL|member|dvb_net1
r_struct
id|dvb_net
id|dvb_net1
suffix:semicolon
DECL|member|feedlock1
id|spinlock_t
id|feedlock1
suffix:semicolon
DECL|member|feeding1
r_int
id|feeding1
suffix:semicolon
DECL|member|tsf
id|u8
id|tsf
suffix:semicolon
DECL|member|ttbp
id|u32
id|ttbp
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
DECL|member|vpe_tasklet
r_struct
id|tasklet_struct
id|vpe_tasklet
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
DECL|member|video_blank
r_int
id|video_blank
suffix:semicolon
DECL|member|videostate
r_struct
id|video_status
id|videostate
suffix:semicolon
DECL|member|display_ar
r_int
id|display_ar
suffix:semicolon
DECL|member|trickmode
r_int
id|trickmode
suffix:semicolon
DECL|macro|TRICK_NONE
mdefine_line|#define TRICK_NONE   0
DECL|macro|TRICK_FAST
mdefine_line|#define TRICK_FAST   1
DECL|macro|TRICK_SLOW
mdefine_line|#define TRICK_SLOW   2
DECL|macro|TRICK_FREEZE
mdefine_line|#define TRICK_FREEZE 3
DECL|member|audiostate
r_struct
id|audio_status
id|audiostate
suffix:semicolon
DECL|member|handle2filter
r_struct
id|dvb_demux_filter
op_star
id|handle2filter
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|p2t_filter
r_struct
id|av7110_p2t
id|p2t_filter
(braket
id|MAXFILT
)braket
suffix:semicolon
DECL|member|p2t
r_struct
id|dvb_filter_pes2ts
id|p2t
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ipack
r_struct
id|ipack
id|ipack
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|kbuf
id|u8
op_star
id|kbuf
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|sinfo
r_int
id|sinfo
suffix:semicolon
DECL|member|feeding
r_int
id|feeding
suffix:semicolon
DECL|member|arm_errors
r_int
id|arm_errors
suffix:semicolon
DECL|member|registered
r_int
id|registered
suffix:semicolon
multiline_comment|/* AV711X */
DECL|member|arm_fw
id|u32
id|arm_fw
suffix:semicolon
DECL|member|arm_rtsl
id|u32
id|arm_rtsl
suffix:semicolon
DECL|member|arm_vid
id|u32
id|arm_vid
suffix:semicolon
DECL|member|arm_app
id|u32
id|arm_app
suffix:semicolon
DECL|member|avtype
id|u32
id|avtype
suffix:semicolon
DECL|member|arm_ready
r_int
id|arm_ready
suffix:semicolon
DECL|member|arm_thread
r_struct
id|task_struct
op_star
id|arm_thread
suffix:semicolon
DECL|member|arm_wait
id|wait_queue_head_t
id|arm_wait
suffix:semicolon
DECL|member|arm_loops
id|u16
id|arm_loops
suffix:semicolon
DECL|member|arm_rmmod
r_int
id|arm_rmmod
suffix:semicolon
DECL|member|debi_virt
r_void
op_star
id|debi_virt
suffix:semicolon
DECL|member|debi_bus
id|dma_addr_t
id|debi_bus
suffix:semicolon
DECL|member|pids
id|u16
id|pids
(braket
id|DMX_PES_OTHER
)braket
suffix:semicolon
DECL|member|ci_rbuffer
r_struct
id|dvb_ringbuffer
id|ci_rbuffer
suffix:semicolon
DECL|member|ci_wbuffer
r_struct
id|dvb_ringbuffer
id|ci_wbuffer
suffix:semicolon
DECL|member|mixer
r_struct
id|audio_mixer
id|mixer
suffix:semicolon
DECL|member|dvb_adapter
r_struct
id|dvb_adapter
op_star
id|dvb_adapter
suffix:semicolon
DECL|member|video_dev
r_struct
id|dvb_device
op_star
id|video_dev
suffix:semicolon
DECL|member|audio_dev
r_struct
id|dvb_device
op_star
id|audio_dev
suffix:semicolon
DECL|member|ca_dev
r_struct
id|dvb_device
op_star
id|ca_dev
suffix:semicolon
DECL|member|osd_dev
r_struct
id|dvb_device
op_star
id|osd_dev
suffix:semicolon
DECL|member|video_events
r_struct
id|dvb_video_events
id|video_events
suffix:semicolon
DECL|member|video_size
id|video_size_t
id|video_size
suffix:semicolon
DECL|member|ir_config
id|u32
id|ir_config
suffix:semicolon
multiline_comment|/* firmware stuff */
DECL|member|device_initialized
r_int
r_int
id|device_initialized
suffix:semicolon
DECL|member|bin_fw
r_int
r_char
op_star
id|bin_fw
suffix:semicolon
DECL|member|size_fw
r_int
r_int
id|size_fw
suffix:semicolon
DECL|member|bin_dpram
r_int
r_char
op_star
id|bin_dpram
suffix:semicolon
DECL|member|size_dpram
r_int
r_int
id|size_dpram
suffix:semicolon
DECL|member|bin_root
r_int
r_char
op_star
id|bin_root
suffix:semicolon
DECL|member|size_root
r_int
r_int
id|size_root
suffix:semicolon
DECL|member|fe
r_struct
id|dvb_frontend
op_star
id|fe
suffix:semicolon
DECL|member|fe_status
id|fe_status_t
id|fe_status
suffix:semicolon
DECL|member|fe_init
r_int
(paren
op_star
id|fe_init
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
suffix:semicolon
DECL|member|fe_read_status
r_int
(paren
op_star
id|fe_read_status
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|fe_status_t
op_star
id|status
)paren
suffix:semicolon
DECL|member|fe_diseqc_reset_overload
r_int
(paren
op_star
id|fe_diseqc_reset_overload
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
suffix:semicolon
DECL|member|fe_diseqc_send_master_cmd
r_int
(paren
op_star
id|fe_diseqc_send_master_cmd
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_diseqc_master_cmd
op_star
id|cmd
)paren
suffix:semicolon
DECL|member|fe_diseqc_send_burst
r_int
(paren
op_star
id|fe_diseqc_send_burst
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|fe_sec_mini_cmd_t
id|minicmd
)paren
suffix:semicolon
DECL|member|fe_set_tone
r_int
(paren
op_star
id|fe_set_tone
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|fe_sec_tone_mode_t
id|tone
)paren
suffix:semicolon
DECL|member|fe_set_voltage
r_int
(paren
op_star
id|fe_set_voltage
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|fe_sec_voltage_t
id|voltage
)paren
suffix:semicolon
DECL|member|fe_dishnetwork_send_legacy_command
r_int
(paren
op_star
id|fe_dishnetwork_send_legacy_command
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
r_int
id|cmd
)paren
suffix:semicolon
DECL|member|fe_set_frontend
r_int
(paren
op_star
id|fe_set_frontend
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_frontend_parameters
op_star
id|params
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|ChangePIDs
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u16
id|vpid
comma
id|u16
id|apid
comma
id|u16
id|ttpid
comma
id|u16
id|subpid
comma
id|u16
id|pcrpid
)paren
suffix:semicolon
r_extern
r_void
id|av7110_register_irc_handler
c_func
(paren
r_void
(paren
op_star
id|func
)paren
(paren
id|u32
)paren
)paren
suffix:semicolon
r_extern
r_void
id|av7110_unregister_irc_handler
c_func
(paren
r_void
(paren
op_star
id|func
)paren
(paren
id|u32
)paren
)paren
suffix:semicolon
r_extern
r_void
id|av7110_setup_irc_config
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|ir_config
)paren
suffix:semicolon
r_extern
r_int
id|av7110_ir_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|av7110_ir_exit
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* msp3400 i2c subaddresses */
DECL|macro|MSP_WR_DEM
mdefine_line|#define MSP_WR_DEM 0x10
DECL|macro|MSP_RD_DEM
mdefine_line|#define MSP_RD_DEM 0x11
DECL|macro|MSP_WR_DSP
mdefine_line|#define MSP_WR_DSP 0x12
DECL|macro|MSP_RD_DSP
mdefine_line|#define MSP_RD_DSP 0x13
r_extern
r_int
id|i2c_writereg
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u8
id|id
comma
id|u8
id|reg
comma
id|u8
id|val
)paren
suffix:semicolon
r_extern
id|u8
id|i2c_readreg
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u8
id|id
comma
id|u8
id|reg
)paren
suffix:semicolon
r_extern
r_int
id|msp_writereg
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u8
id|dev
comma
id|u16
id|reg
comma
id|u16
id|val
)paren
suffix:semicolon
r_extern
r_int
id|msp_readreg
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u8
id|dev
comma
id|u16
id|reg
comma
id|u16
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|av7110_init_analog_module
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
suffix:semicolon
r_extern
r_int
id|av7110_init_v4l
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
suffix:semicolon
r_extern
r_int
id|av7110_exit_v4l
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
suffix:semicolon
macro_line|#endif /* _AV7110_H_ */
eof
