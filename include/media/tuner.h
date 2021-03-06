multiline_comment|/*&n;    tuner.h - definition for different tuners&n;&n;    Copyright (C) 1997 Markus Schroeder (schroedm@uni-duesseldorf.de)&n;    minor modifications by Ralph Metzler (rjkm@thp.uni-koeln.de)&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _TUNER_H
DECL|macro|_TUNER_H
mdefine_line|#define _TUNER_H
macro_line|#include &quot;id.h&quot;
DECL|macro|TUNER_TEMIC_PAL
mdefine_line|#define TUNER_TEMIC_PAL     0        /* 4002 FH5 (3X 7756, 9483) */
DECL|macro|TUNER_PHILIPS_PAL_I
mdefine_line|#define TUNER_PHILIPS_PAL_I 1
DECL|macro|TUNER_PHILIPS_NTSC
mdefine_line|#define TUNER_PHILIPS_NTSC  2
DECL|macro|TUNER_PHILIPS_SECAM
mdefine_line|#define TUNER_PHILIPS_SECAM 3&t;&t;/* you must actively select B/G, L, L` */
DECL|macro|TUNER_ABSENT
mdefine_line|#define TUNER_ABSENT        4
DECL|macro|TUNER_PHILIPS_PAL
mdefine_line|#define TUNER_PHILIPS_PAL   5
DECL|macro|TUNER_TEMIC_NTSC
mdefine_line|#define TUNER_TEMIC_NTSC    6        /* 4032 FY5 (3X 7004, 9498, 9789)  */
DECL|macro|TUNER_TEMIC_PAL_I
mdefine_line|#define TUNER_TEMIC_PAL_I   7        /* 4062 FY5 (3X 8501, 9957)        */
DECL|macro|TUNER_TEMIC_4036FY5_NTSC
mdefine_line|#define TUNER_TEMIC_4036FY5_NTSC 8   /* 4036 FY5 (3X 1223, 1981, 7686)  */
DECL|macro|TUNER_ALPS_TSBH1_NTSC
mdefine_line|#define TUNER_ALPS_TSBH1_NTSC &t; 9
DECL|macro|TUNER_ALPS_TSBE1_PAL
mdefine_line|#define TUNER_ALPS_TSBE1_PAL &t;10
DECL|macro|TUNER_ALPS_TSBB5_PAL_I
mdefine_line|#define TUNER_ALPS_TSBB5_PAL_I &t;11
DECL|macro|TUNER_ALPS_TSBE5_PAL
mdefine_line|#define TUNER_ALPS_TSBE5_PAL &t;12
DECL|macro|TUNER_ALPS_TSBC5_PAL
mdefine_line|#define TUNER_ALPS_TSBC5_PAL &t;13
DECL|macro|TUNER_TEMIC_4006FH5_PAL
mdefine_line|#define TUNER_TEMIC_4006FH5_PAL&t;14   /* 4006 FH5 (3X 9500, 9501, 7291)     */
DECL|macro|TUNER_ALPS_TSHC6_NTSC
mdefine_line|#define TUNER_ALPS_TSHC6_NTSC &t;15
DECL|macro|TUNER_TEMIC_PAL_DK
mdefine_line|#define TUNER_TEMIC_PAL_DK&t;16   /* 4016 FY5 (3X 1392, 1393)     */
DECL|macro|TUNER_PHILIPS_NTSC_M
mdefine_line|#define TUNER_PHILIPS_NTSC_M&t;17
DECL|macro|TUNER_TEMIC_4066FY5_PAL_I
mdefine_line|#define TUNER_TEMIC_4066FY5_PAL_I       18  /* 4066 FY5 (3X 7032, 7035) */
DECL|macro|TUNER_TEMIC_4006FN5_MULTI_PAL
mdefine_line|#define TUNER_TEMIC_4006FN5_MULTI_PAL   19  /* B/G, I and D/K autodetected (3X 7595, 7606, 7657)*/
DECL|macro|TUNER_TEMIC_4009FR5_PAL
mdefine_line|#define TUNER_TEMIC_4009FR5_PAL         20  /* incl. FM radio (3X 7607, 7488, 7711)*/
DECL|macro|TUNER_TEMIC_4039FR5_NTSC
mdefine_line|#define TUNER_TEMIC_4039FR5_NTSC        21  /* incl. FM radio (3X 7246, 7578, 7732)*/
DECL|macro|TUNER_TEMIC_4046FM5
mdefine_line|#define TUNER_TEMIC_4046FM5             22  /* you must actively select B/G, D/K, I, L, L` !  (3X 7804, 7806, 8103, 8104)*/
DECL|macro|TUNER_PHILIPS_PAL_DK
mdefine_line|#define TUNER_PHILIPS_PAL_DK&t;&t;23
DECL|macro|TUNER_PHILIPS_FQ1216ME
mdefine_line|#define TUNER_PHILIPS_FQ1216ME&t;&t;24  /* you must actively select B/G/D/K, I, L, L` */
DECL|macro|TUNER_LG_PAL_I_FM
mdefine_line|#define TUNER_LG_PAL_I_FM&t;25
DECL|macro|TUNER_LG_PAL_I
mdefine_line|#define TUNER_LG_PAL_I&t;&t;26
DECL|macro|TUNER_LG_NTSC_FM
mdefine_line|#define TUNER_LG_NTSC_FM&t;27
DECL|macro|TUNER_LG_PAL_FM
mdefine_line|#define TUNER_LG_PAL_FM&t;&t;28
DECL|macro|TUNER_LG_PAL
mdefine_line|#define TUNER_LG_PAL&t;&t;29
DECL|macro|TUNER_TEMIC_4009FN5_MULTI_PAL_FM
mdefine_line|#define TUNER_TEMIC_4009FN5_MULTI_PAL_FM&t;30  /* B/G, I and D/K autodetected (3X 8155, 8160, 8163)*/
DECL|macro|TUNER_SHARP_2U5JF5540_NTSC
mdefine_line|#define TUNER_SHARP_2U5JF5540_NTSC  31
DECL|macro|TUNER_Samsung_PAL_TCPM9091PD27
mdefine_line|#define TUNER_Samsung_PAL_TCPM9091PD27 32
DECL|macro|TUNER_MT2032
mdefine_line|#define TUNER_MT2032 33
DECL|macro|TUNER_TEMIC_4106FH5
mdefine_line|#define TUNER_TEMIC_4106FH5 &t;34&t;/* 4106 FH5 (3X 7808, 7865)*/
DECL|macro|TUNER_TEMIC_4012FY5
mdefine_line|#define TUNER_TEMIC_4012FY5&t;35&t;/* 4012 FY5 (3X 0971, 1099)*/
DECL|macro|TUNER_TEMIC_4136FY5
mdefine_line|#define TUNER_TEMIC_4136FY5&t;36&t;/* 4136 FY5 (3X 7708, 7746)*/
DECL|macro|TUNER_LG_PAL_NEW_TAPC
mdefine_line|#define TUNER_LG_PAL_NEW_TAPC   37
DECL|macro|TUNER_PHILIPS_FM1216ME_MK3
mdefine_line|#define TUNER_PHILIPS_FM1216ME_MK3  38
DECL|macro|TUNER_LG_NTSC_NEW_TAPC
mdefine_line|#define TUNER_LG_NTSC_NEW_TAPC   39
DECL|macro|TUNER_HITACHI_NTSC
mdefine_line|#define TUNER_HITACHI_NTSC       40
DECL|macro|TUNER_PHILIPS_PAL_MK
mdefine_line|#define TUNER_PHILIPS_PAL_MK     41
DECL|macro|TUNER_PHILIPS_ATSC
mdefine_line|#define TUNER_PHILIPS_ATSC       42
DECL|macro|TUNER_PHILIPS_FM1236_MK3
mdefine_line|#define TUNER_PHILIPS_FM1236_MK3 43
DECL|macro|TUNER_PHILIPS_4IN1
mdefine_line|#define TUNER_PHILIPS_4IN1       44&t;/* ATI TV Wonder Pro - Conexant */
multiline_comment|/* Microtune mergeged with Temic 12/31/1999 partially financed by Alps - these may be similar to Temic */
DECL|macro|TUNER_MICROTUNE_4049FM5
mdefine_line|#define TUNER_MICROTUNE_4049FM5  45
DECL|macro|TUNER_LG_NTSC_TAPE
mdefine_line|#define TUNER_LG_NTSC_TAPE       47
DECL|macro|TUNER_TNF_8831BGFF
mdefine_line|#define TUNER_TNF_8831BGFF       48
DECL|macro|TUNER_MICROTUNE_4042FI5
mdefine_line|#define TUNER_MICROTUNE_4042FI5  49&t;/* FusionHDTV 3 Gold - 4042 FI5 (3X 8147) */
DECL|macro|TUNER_TCL_2002N
mdefine_line|#define TUNER_TCL_2002N          50
DECL|macro|TUNER_PHILIPS_FM1256_IH3
mdefine_line|#define TUNER_PHILIPS_FM1256_IH3   51
DECL|macro|TUNER_THOMSON_DTT7610
mdefine_line|#define TUNER_THOMSON_DTT7610    52
DECL|macro|TUNER_PHILIPS_FQ1286
mdefine_line|#define TUNER_PHILIPS_FQ1286     53
DECL|macro|TUNER_PHILIPS_TDA8290
mdefine_line|#define TUNER_PHILIPS_TDA8290    54
DECL|macro|TUNER_LG_PAL_TAPE
mdefine_line|#define TUNER_LG_PAL_TAPE        55    /* Hauppauge PVR-150 PAL */
DECL|macro|TUNER_PHILIPS_FQ1216AME_MK4
mdefine_line|#define TUNER_PHILIPS_FQ1216AME_MK4 56 /* Hauppauge PVR-150 PAL */
DECL|macro|TUNER_PHILIPS_FQ1236A_MK4
mdefine_line|#define TUNER_PHILIPS_FQ1236A_MK4 57   /* Hauppauge PVR-500MCE NTSC */
DECL|macro|NOTUNER
mdefine_line|#define NOTUNER 0
DECL|macro|PAL
mdefine_line|#define PAL     1&t;/* PAL_BG */
DECL|macro|PAL_I
mdefine_line|#define PAL_I   2
DECL|macro|NTSC
mdefine_line|#define NTSC    3
DECL|macro|SECAM
mdefine_line|#define SECAM   4
DECL|macro|ATSC
mdefine_line|#define ATSC    5
DECL|macro|NoTuner
mdefine_line|#define NoTuner 0
DECL|macro|Philips
mdefine_line|#define Philips 1
DECL|macro|TEMIC
mdefine_line|#define TEMIC   2
DECL|macro|Sony
mdefine_line|#define Sony    3
DECL|macro|Alps
mdefine_line|#define Alps    4
DECL|macro|LGINNOTEK
mdefine_line|#define LGINNOTEK 5
DECL|macro|SHARP
mdefine_line|#define SHARP   6
DECL|macro|Samsung
mdefine_line|#define Samsung 7
DECL|macro|Microtune
mdefine_line|#define Microtune 8
DECL|macro|HITACHI
mdefine_line|#define HITACHI 9
DECL|macro|Panasonic
mdefine_line|#define Panasonic 10
DECL|macro|TCL
mdefine_line|#define TCL     11
DECL|macro|THOMSON
mdefine_line|#define THOMSON 12
DECL|macro|TUNER_SET_TYPE
mdefine_line|#define TUNER_SET_TYPE               _IOW(&squot;t&squot;,1,int)    /* set tuner type */
DECL|macro|TUNER_SET_TVFREQ
mdefine_line|#define TUNER_SET_TVFREQ             _IOW(&squot;t&squot;,2,int)    /* set tv freq */
DECL|macro|TDA9887_SET_CONFIG
mdefine_line|#define  TDA9887_SET_CONFIG          _IOW(&squot;t&squot;,5,int)
multiline_comment|/* tv card specific */
DECL|macro|TDA9887_PRESENT
macro_line|# define TDA9887_PRESENT             (1&lt;&lt;0)
DECL|macro|TDA9887_PORT1_INACTIVE
macro_line|# define TDA9887_PORT1_INACTIVE      (1&lt;&lt;1)
DECL|macro|TDA9887_PORT2_INACTIVE
macro_line|# define TDA9887_PORT2_INACTIVE      (1&lt;&lt;2)
DECL|macro|TDA9887_QSS
macro_line|# define TDA9887_QSS                 (1&lt;&lt;3)
DECL|macro|TDA9887_INTERCARRIER
macro_line|# define TDA9887_INTERCARRIER        (1&lt;&lt;4)
DECL|macro|TDA9887_PORT1_ACTIVE
macro_line|# define TDA9887_PORT1_ACTIVE        (1&lt;&lt;5)
DECL|macro|TDA9887_PORT2_ACTIVE
macro_line|# define TDA9887_PORT2_ACTIVE        (1&lt;&lt;6)
multiline_comment|/* config options */
DECL|macro|TDA9887_DEEMPHASIS_MASK
macro_line|# define TDA9887_DEEMPHASIS_MASK     (3&lt;&lt;16)
DECL|macro|TDA9887_DEEMPHASIS_NONE
macro_line|# define TDA9887_DEEMPHASIS_NONE     (1&lt;&lt;16)
DECL|macro|TDA9887_DEEMPHASIS_50
macro_line|# define TDA9887_DEEMPHASIS_50       (2&lt;&lt;16)
DECL|macro|TDA9887_DEEMPHASIS_75
macro_line|# define TDA9887_DEEMPHASIS_75       (3&lt;&lt;16)
DECL|macro|TDA9887_AUTOMUTE
macro_line|# define TDA9887_AUTOMUTE            (1&lt;&lt;18)
macro_line|#ifdef __KERNEL__
DECL|macro|I2C_ADDR_TDA8290
mdefine_line|#define I2C_ADDR_TDA8290        0x4b
DECL|macro|I2C_ADDR_TDA8275
mdefine_line|#define I2C_ADDR_TDA8275        0x61
DECL|struct|tuner
r_struct
id|tuner
(brace
multiline_comment|/* device */
DECL|member|i2c
r_struct
id|i2c_client
id|i2c
suffix:semicolon
multiline_comment|/* state + config */
DECL|member|initialized
r_int
r_int
id|initialized
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* chip type */
DECL|member|freq
r_int
r_int
id|freq
suffix:semicolon
multiline_comment|/* keep track of the current settings */
DECL|member|std
id|v4l2_std_id
id|std
suffix:semicolon
DECL|member|using_v4l2
r_int
id|using_v4l2
suffix:semicolon
DECL|member|mode
r_enum
id|v4l2_tuner_type
id|mode
suffix:semicolon
DECL|member|input
r_int
r_int
id|input
suffix:semicolon
multiline_comment|/* used by MT2032 */
DECL|member|xogc
r_int
r_int
id|xogc
suffix:semicolon
DECL|member|radio_if2
r_int
r_int
id|radio_if2
suffix:semicolon
multiline_comment|/* used by tda8290 */
DECL|member|i2c_easy_mode
r_int
r_char
id|i2c_easy_mode
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|i2c_set_freq
r_int
r_char
id|i2c_set_freq
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* function ptrs */
DECL|member|tv_freq
r_void
(paren
op_star
id|tv_freq
)paren
(paren
r_struct
id|i2c_client
op_star
id|c
comma
r_int
r_int
id|freq
)paren
suffix:semicolon
DECL|member|radio_freq
r_void
(paren
op_star
id|radio_freq
)paren
(paren
r_struct
id|i2c_client
op_star
id|c
comma
r_int
r_int
id|freq
)paren
suffix:semicolon
DECL|member|has_signal
r_int
(paren
op_star
id|has_signal
)paren
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
suffix:semicolon
DECL|member|is_stereo
r_int
(paren
op_star
id|is_stereo
)paren
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
r_int
id|tuner_debug
suffix:semicolon
r_extern
r_int
r_const
r_int
id|tuner_count
suffix:semicolon
r_extern
r_int
id|microtune_init
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
suffix:semicolon
r_extern
r_int
id|tda8290_init
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
suffix:semicolon
r_extern
r_int
id|default_tuner_init
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
suffix:semicolon
DECL|macro|tuner_warn
mdefine_line|#define tuner_warn(fmt, arg...) &bslash;&n;&t;dev_printk(KERN_WARNING , &amp;t-&gt;i2c.dev , fmt , ## arg)
DECL|macro|tuner_info
mdefine_line|#define tuner_info(fmt, arg...) &bslash;&n;&t;dev_printk(KERN_INFO , &amp;t-&gt;i2c.dev , fmt , ## arg)
DECL|macro|tuner_dbg
mdefine_line|#define tuner_dbg(fmt, arg...) &bslash;&n;&t;if (tuner_debug) dev_printk(KERN_DEBUG , &amp;t-&gt;i2c.dev , fmt , ## arg)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
