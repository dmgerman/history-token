multiline_comment|/*&n; * $Id: bttv.h,v 1.10 2004/10/13 10:39:00 kraxel Exp $&n; *&n; *  bttv - Bt848 frame grabber driver&n; *&n; *  card ID&squot;s and external interfaces of the bttv driver&n; *  basically stuff needed by other drivers (i2c, lirc, ...)&n; *  and is supported not to change much over time.&n; *&n; *  Copyright (C) 1996,97 Ralph Metzler (rjkm@thp.uni-koeln.de)&n; *  (c) 1999,2000 Gerd Knorr &lt;kraxel@goldbach.in-berlin.de&gt;&n; *&n; */
macro_line|#ifndef _BTTV_H_
DECL|macro|_BTTV_H_
mdefine_line|#define _BTTV_H_
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
multiline_comment|/* ---------------------------------------------------------- */
multiline_comment|/* exported by bttv-cards.c                                   */
DECL|macro|BTTV_UNKNOWN
mdefine_line|#define BTTV_UNKNOWN       0x00
DECL|macro|BTTV_MIRO
mdefine_line|#define BTTV_MIRO          0x01
DECL|macro|BTTV_HAUPPAUGE
mdefine_line|#define BTTV_HAUPPAUGE     0x02
DECL|macro|BTTV_STB
mdefine_line|#define BTTV_STB           0x03
DECL|macro|BTTV_INTEL
mdefine_line|#define BTTV_INTEL         0x04
DECL|macro|BTTV_DIAMOND
mdefine_line|#define BTTV_DIAMOND       0x05
DECL|macro|BTTV_AVERMEDIA
mdefine_line|#define BTTV_AVERMEDIA     0x06
DECL|macro|BTTV_MATRIX_VISION
mdefine_line|#define BTTV_MATRIX_VISION 0x07
DECL|macro|BTTV_FLYVIDEO
mdefine_line|#define BTTV_FLYVIDEO      0x08
DECL|macro|BTTV_TURBOTV
mdefine_line|#define BTTV_TURBOTV       0x09
DECL|macro|BTTV_HAUPPAUGE878
mdefine_line|#define BTTV_HAUPPAUGE878  0x0a
DECL|macro|BTTV_MIROPRO
mdefine_line|#define BTTV_MIROPRO       0x0b
DECL|macro|BTTV_ADSTECH_TV
mdefine_line|#define BTTV_ADSTECH_TV    0x0c
DECL|macro|BTTV_AVERMEDIA98
mdefine_line|#define BTTV_AVERMEDIA98   0x0d
DECL|macro|BTTV_VHX
mdefine_line|#define BTTV_VHX           0x0e
DECL|macro|BTTV_ZOLTRIX
mdefine_line|#define BTTV_ZOLTRIX       0x0f
DECL|macro|BTTV_PIXVIEWPLAYTV
mdefine_line|#define BTTV_PIXVIEWPLAYTV 0x10
DECL|macro|BTTV_WINVIEW_601
mdefine_line|#define BTTV_WINVIEW_601   0x11
DECL|macro|BTTV_AVEC_INTERCAP
mdefine_line|#define BTTV_AVEC_INTERCAP 0x12
DECL|macro|BTTV_LIFE_FLYKIT
mdefine_line|#define BTTV_LIFE_FLYKIT   0x13
DECL|macro|BTTV_CEI_RAFFLES
mdefine_line|#define BTTV_CEI_RAFFLES   0x14
DECL|macro|BTTV_CONFERENCETV
mdefine_line|#define BTTV_CONFERENCETV  0x15
DECL|macro|BTTV_PHOEBE_TVMAS
mdefine_line|#define BTTV_PHOEBE_TVMAS  0x16
DECL|macro|BTTV_MODTEC_205
mdefine_line|#define BTTV_MODTEC_205    0x17
DECL|macro|BTTV_MAGICTVIEW061
mdefine_line|#define BTTV_MAGICTVIEW061 0x18
DECL|macro|BTTV_VOBIS_BOOSTAR
mdefine_line|#define BTTV_VOBIS_BOOSTAR 0x19
DECL|macro|BTTV_HAUPPAUG_WCAM
mdefine_line|#define BTTV_HAUPPAUG_WCAM 0x1a
DECL|macro|BTTV_MAXI
mdefine_line|#define BTTV_MAXI          0x1b
DECL|macro|BTTV_TERRATV
mdefine_line|#define BTTV_TERRATV       0x1c
DECL|macro|BTTV_PXC200
mdefine_line|#define BTTV_PXC200        0x1d
DECL|macro|BTTV_FLYVIDEO_98
mdefine_line|#define BTTV_FLYVIDEO_98   0x1e
DECL|macro|BTTV_IPROTV
mdefine_line|#define BTTV_IPROTV        0x1f
DECL|macro|BTTV_INTEL_C_S_PCI
mdefine_line|#define BTTV_INTEL_C_S_PCI 0x20
DECL|macro|BTTV_TERRATVALUE
mdefine_line|#define BTTV_TERRATVALUE   0x21
DECL|macro|BTTV_WINFAST2000
mdefine_line|#define BTTV_WINFAST2000   0x22
DECL|macro|BTTV_CHRONOS_VS2
mdefine_line|#define BTTV_CHRONOS_VS2   0x23
DECL|macro|BTTV_TYPHOON_TVIEW
mdefine_line|#define BTTV_TYPHOON_TVIEW 0x24
DECL|macro|BTTV_PXELVWPLTVPRO
mdefine_line|#define BTTV_PXELVWPLTVPRO 0x25
DECL|macro|BTTV_MAGICTVIEW063
mdefine_line|#define BTTV_MAGICTVIEW063 0x26
DECL|macro|BTTV_PINNACLE
mdefine_line|#define BTTV_PINNACLE      0x27
DECL|macro|BTTV_STB2
mdefine_line|#define BTTV_STB2          0x28
DECL|macro|BTTV_AVPHONE98
mdefine_line|#define BTTV_AVPHONE98     0x29
DECL|macro|BTTV_PV951
mdefine_line|#define BTTV_PV951         0x2a
DECL|macro|BTTV_ONAIR_TV
mdefine_line|#define BTTV_ONAIR_TV      0x2b
DECL|macro|BTTV_SIGMA_TVII_FM
mdefine_line|#define BTTV_SIGMA_TVII_FM 0x2c
DECL|macro|BTTV_MATRIX_VISION2
mdefine_line|#define BTTV_MATRIX_VISION2 0x2d
DECL|macro|BTTV_ZOLTRIX_GENIE
mdefine_line|#define BTTV_ZOLTRIX_GENIE 0x2e
DECL|macro|BTTV_TERRATVRADIO
mdefine_line|#define BTTV_TERRATVRADIO  0x2f
DECL|macro|BTTV_DYNALINK
mdefine_line|#define BTTV_DYNALINK      0x30
DECL|macro|BTTV_GVBCTV3PCI
mdefine_line|#define BTTV_GVBCTV3PCI    0x31
DECL|macro|BTTV_PXELVWPLTVPAK
mdefine_line|#define BTTV_PXELVWPLTVPAK 0x32
DECL|macro|BTTV_EAGLE
mdefine_line|#define BTTV_EAGLE         0x33
DECL|macro|BTTV_PINNACLEPRO
mdefine_line|#define BTTV_PINNACLEPRO   0x34
DECL|macro|BTTV_TVIEW_RDS_FM
mdefine_line|#define BTTV_TVIEW_RDS_FM  0x35
DECL|macro|BTTV_LIFETEC_9415
mdefine_line|#define BTTV_LIFETEC_9415  0x36
DECL|macro|BTTV_BESTBUY_EASYTV
mdefine_line|#define BTTV_BESTBUY_EASYTV 0x37
DECL|macro|BTTV_FLYVIDEO_98FM
mdefine_line|#define BTTV_FLYVIDEO_98FM 0x38
DECL|macro|BTTV_GMV1
mdefine_line|#define BTTV_GMV1          0x3d
DECL|macro|BTTV_BESTBUY_EASYTV2
mdefine_line|#define BTTV_BESTBUY_EASYTV2 0x3e
DECL|macro|BTTV_ATI_TVWONDER
mdefine_line|#define BTTV_ATI_TVWONDER  0x3f
DECL|macro|BTTV_ATI_TVWONDERVE
mdefine_line|#define BTTV_ATI_TVWONDERVE 0x40
DECL|macro|BTTV_FLYVIDEO2000
mdefine_line|#define BTTV_FLYVIDEO2000   0x41
DECL|macro|BTTV_TERRATVALUER
mdefine_line|#define BTTV_TERRATVALUER   0x42
DECL|macro|BTTV_GVBCTV4PCI
mdefine_line|#define BTTV_GVBCTV4PCI     0x43
DECL|macro|BTTV_VOODOOTV_FM
mdefine_line|#define BTTV_VOODOOTV_FM    0x44
DECL|macro|BTTV_AIMMS
mdefine_line|#define BTTV_AIMMS          0x45
DECL|macro|BTTV_PV_BT878P_PLUS
mdefine_line|#define BTTV_PV_BT878P_PLUS 0x46
DECL|macro|BTTV_FLYVIDEO98EZ
mdefine_line|#define BTTV_FLYVIDEO98EZ   0x47
DECL|macro|BTTV_PV_BT878P_9B
mdefine_line|#define BTTV_PV_BT878P_9B   0x48
DECL|macro|BTTV_SENSORAY311
mdefine_line|#define BTTV_SENSORAY311    0x49
DECL|macro|BTTV_RV605
mdefine_line|#define BTTV_RV605          0x4a
DECL|macro|BTTV_WINDVR
mdefine_line|#define BTTV_WINDVR         0x4c
DECL|macro|BTTV_GRANDTEC
mdefine_line|#define BTTV_GRANDTEC       0x4d
DECL|macro|BTTV_KWORLD
mdefine_line|#define BTTV_KWORLD         0x4e
DECL|macro|BTTV_HAUPPAUGEPVR
mdefine_line|#define BTTV_HAUPPAUGEPVR   0x50
DECL|macro|BTTV_GVBCTV5PCI
mdefine_line|#define BTTV_GVBCTV5PCI     0x51
DECL|macro|BTTV_OSPREY1x0
mdefine_line|#define BTTV_OSPREY1x0      0x52
DECL|macro|BTTV_OSPREY1x0_848
mdefine_line|#define BTTV_OSPREY1x0_848  0x53
DECL|macro|BTTV_OSPREY101_848
mdefine_line|#define BTTV_OSPREY101_848  0x54
DECL|macro|BTTV_OSPREY1x1
mdefine_line|#define BTTV_OSPREY1x1      0x55
DECL|macro|BTTV_OSPREY1x1_SVID
mdefine_line|#define BTTV_OSPREY1x1_SVID 0x56
DECL|macro|BTTV_OSPREY2xx
mdefine_line|#define BTTV_OSPREY2xx      0x57
DECL|macro|BTTV_OSPREY2x0_SVID
mdefine_line|#define BTTV_OSPREY2x0_SVID 0x58
DECL|macro|BTTV_OSPREY2x0
mdefine_line|#define BTTV_OSPREY2x0      0x59
DECL|macro|BTTV_OSPREY500
mdefine_line|#define BTTV_OSPREY500      0x5a
DECL|macro|BTTV_OSPREY540
mdefine_line|#define BTTV_OSPREY540      0x5b
DECL|macro|BTTV_OSPREY2000
mdefine_line|#define BTTV_OSPREY2000     0x5c
DECL|macro|BTTV_IDS_EAGLE
mdefine_line|#define BTTV_IDS_EAGLE      0x5d
DECL|macro|BTTV_PINNACLESAT
mdefine_line|#define BTTV_PINNACLESAT    0x5e
DECL|macro|BTTV_FORMAC_PROTV
mdefine_line|#define BTTV_FORMAC_PROTV   0x5f
DECL|macro|BTTV_EURESYS_PICOLO
mdefine_line|#define BTTV_EURESYS_PICOLO 0x61
DECL|macro|BTTV_PV150
mdefine_line|#define BTTV_PV150          0x62
DECL|macro|BTTV_AD_TVK503
mdefine_line|#define BTTV_AD_TVK503      0x63
DECL|macro|BTTV_IVC200
mdefine_line|#define BTTV_IVC200         0x66
DECL|macro|BTTV_XGUARD
mdefine_line|#define BTTV_XGUARD         0x67
DECL|macro|BTTV_NEBULA_DIGITV
mdefine_line|#define BTTV_NEBULA_DIGITV  0x68
DECL|macro|BTTV_PV143
mdefine_line|#define BTTV_PV143          0x69
DECL|macro|BTTV_IVC100
mdefine_line|#define BTTV_IVC100         0x6e
DECL|macro|BTTV_IVC120
mdefine_line|#define BTTV_IVC120         0x6f
DECL|macro|BTTV_PC_HDTV
mdefine_line|#define BTTV_PC_HDTV        0x70
DECL|macro|BTTV_TWINHAN_DST
mdefine_line|#define BTTV_TWINHAN_DST    0x71
DECL|macro|BTTV_WINFASTVC100
mdefine_line|#define BTTV_WINFASTVC100   0x72
DECL|macro|BTTV_SIMUS_GVC1100
mdefine_line|#define BTTV_SIMUS_GVC1100  0x74
DECL|macro|BTTV_NGSTV_PLUS
mdefine_line|#define BTTV_NGSTV_PLUS     0x75
DECL|macro|BTTV_LMLBT4
mdefine_line|#define BTTV_LMLBT4         0x76
DECL|macro|BTTV_PICOLO_TETRA_CHIP
mdefine_line|#define BTTV_PICOLO_TETRA_CHIP 0x79
DECL|macro|BTTV_AVDVBT_771
mdefine_line|#define BTTV_AVDVBT_771     0x7b
DECL|macro|BTTV_AVDVBT_761
mdefine_line|#define BTTV_AVDVBT_761     0x7c
DECL|macro|BTTV_MATRIX_VISIONSQ
mdefine_line|#define BTTV_MATRIX_VISIONSQ  0x7d
DECL|macro|BTTV_MATRIX_VISIONSLC
mdefine_line|#define BTTV_MATRIX_VISIONSLC 0x7e
DECL|macro|BTTV_APAC_VIEWCOMP
mdefine_line|#define BTTV_APAC_VIEWCOMP  0x7f
DECL|macro|BTTV_DVICO_DVBT_LITE
mdefine_line|#define BTTV_DVICO_DVBT_LITE  0x80
multiline_comment|/* i2c address list */
DECL|macro|I2C_TSA5522
mdefine_line|#define I2C_TSA5522        0xc2
DECL|macro|I2C_TDA7432
mdefine_line|#define I2C_TDA7432        0x8a
DECL|macro|I2C_BT832_ALT1
mdefine_line|#define I2C_BT832_ALT1&t;   0x88
DECL|macro|I2C_BT832_ALT2
mdefine_line|#define I2C_BT832_ALT2&t;   0x8a 
singleline_comment|// alternate setting
DECL|macro|I2C_TDA8425
mdefine_line|#define I2C_TDA8425        0x82
DECL|macro|I2C_TDA9840
mdefine_line|#define I2C_TDA9840        0x84
DECL|macro|I2C_TDA9850
mdefine_line|#define I2C_TDA9850        0xb6 /* also used by 9855,9873 */
DECL|macro|I2C_TDA9874
mdefine_line|#define I2C_TDA9874        0xb0 /* also used by 9875 */
DECL|macro|I2C_TDA9875
mdefine_line|#define I2C_TDA9875        0xb0
DECL|macro|I2C_HAUPEE
mdefine_line|#define I2C_HAUPEE         0xa0
DECL|macro|I2C_STBEE
mdefine_line|#define I2C_STBEE          0xae
DECL|macro|I2C_VHX
mdefine_line|#define I2C_VHX            0xc0
DECL|macro|I2C_MSP3400
mdefine_line|#define I2C_MSP3400        0x80
DECL|macro|I2C_MSP3400_ALT
mdefine_line|#define I2C_MSP3400_ALT    0x88
DECL|macro|I2C_TEA6300
mdefine_line|#define I2C_TEA6300        0x80
DECL|macro|I2C_DPL3518
mdefine_line|#define I2C_DPL3518&t;   0x84
DECL|macro|I2C_TDA9887
mdefine_line|#define I2C_TDA9887&t;   0x86
multiline_comment|/* more card-specific defines */
DECL|macro|PT2254_L_CHANNEL
mdefine_line|#define PT2254_L_CHANNEL 0x10
DECL|macro|PT2254_R_CHANNEL
mdefine_line|#define PT2254_R_CHANNEL 0x08
DECL|macro|PT2254_DBS_IN_2
mdefine_line|#define PT2254_DBS_IN_2 0x400
DECL|macro|PT2254_DBS_IN_10
mdefine_line|#define PT2254_DBS_IN_10 0x20000
DECL|macro|WINVIEW_PT2254_CLK
mdefine_line|#define WINVIEW_PT2254_CLK  0x40
DECL|macro|WINVIEW_PT2254_DATA
mdefine_line|#define WINVIEW_PT2254_DATA 0x20
DECL|macro|WINVIEW_PT2254_STROBE
mdefine_line|#define WINVIEW_PT2254_STROBE 0x80
multiline_comment|/* digital_mode */
DECL|macro|DIGITAL_MODE_VIDEO
mdefine_line|#define DIGITAL_MODE_VIDEO 1
DECL|macro|DIGITAL_MODE_CAMERA
mdefine_line|#define DIGITAL_MODE_CAMERA 2
DECL|struct|bttv_core
r_struct
id|bttv_core
(brace
multiline_comment|/* device structs */
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|i2c_adap
r_struct
id|i2c_adapter
id|i2c_adap
suffix:semicolon
DECL|member|subs
r_struct
id|list_head
id|subs
suffix:semicolon
multiline_comment|/* struct bttv_sub_device */
multiline_comment|/* device config */
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
multiline_comment|/* dev nr (for printk(&quot;bttv%d: ...&quot;);  */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* card type (pointer into tvcards[])  */
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* dev name */
)brace
suffix:semicolon
r_struct
id|bttv
suffix:semicolon
DECL|struct|tvcard
r_struct
id|tvcard
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|video_inputs
r_int
r_int
id|video_inputs
suffix:semicolon
DECL|member|audio_inputs
r_int
r_int
id|audio_inputs
suffix:semicolon
DECL|member|tuner
r_int
r_int
id|tuner
suffix:semicolon
DECL|member|svhs
r_int
r_int
id|svhs
suffix:semicolon
DECL|member|digital_mode
r_int
r_int
id|digital_mode
suffix:semicolon
singleline_comment|// DIGITAL_MODE_CAMERA or DIGITAL_MODE_VIDEO
DECL|member|gpiomask
id|u32
id|gpiomask
suffix:semicolon
DECL|member|muxsel
id|u32
id|muxsel
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|audiomux
id|u32
id|audiomux
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Tuner, Radio, external, internal, mute, stereo */
DECL|member|gpiomask2
id|u32
id|gpiomask2
suffix:semicolon
multiline_comment|/* GPIO MUX mask */
multiline_comment|/* i2c audio flags */
DECL|member|no_msp34xx
r_int
r_int
id|no_msp34xx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|no_tda9875
r_int
r_int
id|no_tda9875
suffix:colon
l_int|1
suffix:semicolon
DECL|member|no_tda7432
r_int
r_int
id|no_tda7432
suffix:colon
l_int|1
suffix:semicolon
DECL|member|needs_tvaudio
r_int
r_int
id|needs_tvaudio
suffix:colon
l_int|1
suffix:semicolon
DECL|member|msp34xx_alt
r_int
r_int
id|msp34xx_alt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag: video pci function is unused */
DECL|member|no_video
r_int
r_int
id|no_video
suffix:colon
l_int|1
suffix:semicolon
DECL|member|has_dvb
r_int
r_int
id|has_dvb
suffix:colon
l_int|1
suffix:semicolon
DECL|member|has_remote
r_int
r_int
id|has_remote
suffix:colon
l_int|1
suffix:semicolon
DECL|member|no_gpioirq
r_int
r_int
id|no_gpioirq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* other settings */
DECL|member|pll
r_int
r_int
id|pll
suffix:semicolon
DECL|macro|PLL_NONE
mdefine_line|#define PLL_NONE 0
DECL|macro|PLL_28
mdefine_line|#define PLL_28   1
DECL|macro|PLL_35
mdefine_line|#define PLL_35   2
DECL|member|tuner_type
r_int
r_int
id|tuner_type
suffix:semicolon
DECL|member|has_radio
r_int
r_int
id|has_radio
suffix:semicolon
DECL|member|audio_hook
r_void
(paren
op_star
id|audio_hook
)paren
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_struct
id|video_audio
op_star
id|v
comma
r_int
id|set
)paren
suffix:semicolon
DECL|member|muxsel_hook
r_void
(paren
op_star
id|muxsel_hook
)paren
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
r_int
id|input
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|tvcard
id|bttv_tvcards
(braket
)braket
suffix:semicolon
multiline_comment|/* identification / initialization of the card */
r_extern
r_void
id|bttv_idcard
c_func
(paren
r_struct
id|bttv
op_star
id|btv
)paren
suffix:semicolon
r_extern
r_void
id|bttv_init_card1
c_func
(paren
r_struct
id|bttv
op_star
id|btv
)paren
suffix:semicolon
r_extern
r_void
id|bttv_init_card2
c_func
(paren
r_struct
id|bttv
op_star
id|btv
)paren
suffix:semicolon
multiline_comment|/* card-specific funtions */
r_extern
r_void
id|tea5757_set_freq
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
r_int
id|freq
)paren
suffix:semicolon
r_extern
r_void
id|bttv_tda9880_setnorm
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
id|norm
)paren
suffix:semicolon
multiline_comment|/* extra tweaks for some chipsets */
r_extern
r_void
id|bttv_check_chipset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|bttv_handle_chipset
c_func
(paren
r_struct
id|bttv
op_star
id|btv
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------- */
multiline_comment|/* exported by bttv-if.c                                      */
multiline_comment|/* this obsolete -- please use the sysfs-based&n;   interface below for new code */
multiline_comment|/* returns card type + card ID (for bt878-based ones)&n;   for possible values see lines below beginning with #define BTTV_UNKNOWN&n;   returns negative value if error occurred&n;*/
r_extern
r_int
id|bttv_get_cardinfo
c_func
(paren
r_int
r_int
id|card
comma
r_int
op_star
id|type
comma
r_int
r_int
op_star
id|cardid
)paren
suffix:semicolon
r_extern
r_struct
id|pci_dev
op_star
id|bttv_get_pcidev
c_func
(paren
r_int
r_int
id|card
)paren
suffix:semicolon
multiline_comment|/* obsolete, use bttv_get_cardinfo instead */
r_extern
r_int
id|bttv_get_id
c_func
(paren
r_int
r_int
id|card
)paren
suffix:semicolon
multiline_comment|/* sets GPOE register (BT848_GPIO_OUT_EN) to new value:&n;   data | (current_GPOE_value &amp; ~mask)&n;   returns negative value if error occurred&n;*/
r_extern
r_int
id|bttv_gpio_enable
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|data
)paren
suffix:semicolon
multiline_comment|/* fills data with GPDATA register contents&n;   returns negative value if error occurred&n;*/
r_extern
r_int
id|bttv_read_gpio
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* sets GPDATA register to new value:&n;  (data &amp; mask) | (current_GPDATA_value &amp; ~mask)&n;  returns negative value if error occurred&n;*/
r_extern
r_int
id|bttv_write_gpio
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|data
)paren
suffix:semicolon
multiline_comment|/* returns pointer to task queue which can be used as parameter to&n;   interruptible_sleep_on&n;   in interrupt handler if BT848_INT_GPINT bit is set - this queue is activated&n;   (wake_up_interruptible) and following call to the function bttv_read_gpio&n;   should return new value of GPDATA,&n;   returns NULL value if error occurred or queue is not available&n;   WARNING: because there is no buffer for GPIO data, one MUST&n;   process data ASAP&n;*/
r_extern
id|wait_queue_head_t
op_star
id|bttv_get_gpio_queue
c_func
(paren
r_int
r_int
id|card
)paren
suffix:semicolon
multiline_comment|/* call i2c clients&n;*/
r_extern
r_void
id|bttv_i2c_call
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------- */
multiline_comment|/* sysfs/driver-moded based gpio access interface             */
DECL|struct|bttv_sub_device
r_struct
id|bttv_sub_device
(brace
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|core
r_struct
id|bttv_core
op_star
id|core
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_bttv_sub_dev
mdefine_line|#define to_bttv_sub_dev(x) container_of((x), struct bttv_sub_device, dev)
DECL|struct|bttv_sub_driver
r_struct
id|bttv_sub_driver
(brace
DECL|member|drv
r_struct
id|device_driver
id|drv
suffix:semicolon
DECL|member|wanted
r_char
id|wanted
(braket
id|BUS_ID_SIZE
)braket
suffix:semicolon
DECL|member|gpio_irq
r_void
(paren
op_star
id|gpio_irq
)paren
(paren
r_struct
id|bttv_sub_device
op_star
id|sub
)paren
suffix:semicolon
DECL|member|i2c_info
r_void
(paren
op_star
id|i2c_info
)paren
(paren
r_struct
id|bttv_sub_device
op_star
id|sub
comma
r_struct
id|i2c_client
op_star
id|client
comma
r_int
id|attach
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_bttv_sub_drv
mdefine_line|#define to_bttv_sub_drv(x) container_of((x), struct bttv_sub_driver, drv)
r_int
id|bttv_sub_register
c_func
(paren
r_struct
id|bttv_sub_driver
op_star
id|drv
comma
r_char
op_star
id|wanted
)paren
suffix:semicolon
r_int
id|bttv_sub_unregister
c_func
(paren
r_struct
id|bttv_sub_driver
op_star
id|drv
)paren
suffix:semicolon
multiline_comment|/* gpio access functions */
r_void
id|bttv_gpio_inout
c_func
(paren
r_struct
id|bttv_core
op_star
id|core
comma
id|u32
id|mask
comma
id|u32
id|outbits
)paren
suffix:semicolon
id|u32
id|bttv_gpio_read
c_func
(paren
r_struct
id|bttv_core
op_star
id|core
)paren
suffix:semicolon
r_void
id|bttv_gpio_write
c_func
(paren
r_struct
id|bttv_core
op_star
id|core
comma
id|u32
id|value
)paren
suffix:semicolon
r_void
id|bttv_gpio_bits
c_func
(paren
r_struct
id|bttv_core
op_star
id|core
comma
id|u32
id|mask
comma
id|u32
id|bits
)paren
suffix:semicolon
DECL|macro|gpio_inout
mdefine_line|#define gpio_inout(mask,bits)  bttv_gpio_inout(&amp;btv-&gt;c, mask, bits)
DECL|macro|gpio_read
mdefine_line|#define gpio_read()            bttv_gpio_read(&amp;btv-&gt;c)
DECL|macro|gpio_write
mdefine_line|#define gpio_write(value)      bttv_gpio_write(&amp;btv-&gt;c, value)
DECL|macro|gpio_bits
mdefine_line|#define gpio_bits(mask,bits)   bttv_gpio_bits(&amp;btv-&gt;c, mask, bits)
multiline_comment|/* ---------------------------------------------------------- */
multiline_comment|/* i2c                                                        */
r_extern
r_void
id|bttv_call_i2c_clients
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|bttv_I2CRead
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
r_char
id|addr
comma
r_char
op_star
id|probe_for
)paren
suffix:semicolon
r_extern
r_int
id|bttv_I2CWrite
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
r_char
id|addr
comma
r_int
r_char
id|b1
comma
r_int
r_char
id|b2
comma
r_int
id|both
)paren
suffix:semicolon
r_extern
r_void
id|bttv_readee
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
r_char
op_star
id|eedata
comma
r_int
id|addr
)paren
suffix:semicolon
macro_line|#endif /* _BTTV_H_ */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
