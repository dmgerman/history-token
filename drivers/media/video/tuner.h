multiline_comment|/* &n;    tuner.h - definition for different tuners&n;&n;    Copyright (C) 1997 Markus Schroeder (schroedm@uni-duesseldorf.de)&n;    minor modifications by Ralph Metzler (rjkm@thp.uni-koeln.de)&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _TUNER_H
DECL|macro|_TUNER_H
mdefine_line|#define _TUNER_H
DECL|macro|TUNER_TEMIC_PAL
mdefine_line|#define TUNER_TEMIC_PAL     0        /* 4002 FH5_9483 */
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
mdefine_line|#define TUNER_TEMIC_NTSC    6        /* 4032 FY5_7004 */
DECL|macro|TUNER_TEMIC_PAL_I
mdefine_line|#define TUNER_TEMIC_PAL_I   7        /* 4062 FY5_9957 */
DECL|macro|TUNER_TEMIC_4036FY5_NTSC
mdefine_line|#define TUNER_TEMIC_4036FY5_NTSC 8   /* 4036 FY5      */
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
mdefine_line|#define TUNER_TEMIC_4006FH5_PAL&t;14   /* 4006 FH5      */
DECL|macro|TUNER_ALPS_TSHC6_NTSC
mdefine_line|#define TUNER_ALPS_TSHC6_NTSC &t;15
DECL|macro|TUNER_TEMIC_PAL_DK
mdefine_line|#define TUNER_TEMIC_PAL_DK&t;16   /* 4016 FY5      */
DECL|macro|TUNER_PHILIPS_NTSC_M
mdefine_line|#define TUNER_PHILIPS_NTSC_M&t;17
DECL|macro|TUNER_TEMIC_4066FY5_PAL_I
mdefine_line|#define TUNER_TEMIC_4066FY5_PAL_I       18
DECL|macro|TUNER_TEMIC_4006FN5_MULTI_PAL
mdefine_line|#define TUNER_TEMIC_4006FN5_MULTI_PAL   19  /* B/G, I and D/K autodetected */
DECL|macro|TUNER_TEMIC_4009FR5_PAL
mdefine_line|#define TUNER_TEMIC_4009FR5_PAL         20  /* incl. FM radio */
DECL|macro|TUNER_TEMIC_4039FR5_NTSC
mdefine_line|#define TUNER_TEMIC_4039FR5_NTSC        21  /* incl. FM radio */
DECL|macro|TUNER_TEMIC_4046FM5
mdefine_line|#define TUNER_TEMIC_4046FM5             22  /* you must actively select B/G, D/K, I, L, L` !  */
DECL|macro|TUNER_PHILIPS_PAL_DK
mdefine_line|#define TUNER_PHILIPS_PAL_DK&t;&t;23
DECL|macro|TUNER_PHILIPS_FQ1216ME
mdefine_line|#define TUNER_PHILIPS_FQ1216ME&t;&t;24  /* you must actively select B/G/D/K, I, L, L` */
DECL|macro|NOTUNER
mdefine_line|#define NOTUNER 0
DECL|macro|PAL
mdefine_line|#define PAL     1
DECL|macro|PAL_I
mdefine_line|#define PAL_I   2
DECL|macro|NTSC
mdefine_line|#define NTSC    3
DECL|macro|SECAM
mdefine_line|#define SECAM   4
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
DECL|macro|TUNER_SET_TYPE
mdefine_line|#define TUNER_SET_TYPE               _IOW(&squot;t&squot;,1,int)    /* set tuner type */
DECL|macro|TUNER_SET_TVFREQ
mdefine_line|#define TUNER_SET_TVFREQ             _IOW(&squot;t&squot;,2,int)    /* set tv freq */
DECL|macro|TUNER_SET_RADIOFREQ
mdefine_line|#define TUNER_SET_RADIOFREQ          _IOW(&squot;t&squot;,3,int)    /* set radio freq */
DECL|macro|TUNER_SET_MODE
mdefine_line|#define TUNER_SET_MODE               _IOW(&squot;t&squot;,4,int)    /* set tuner mode */
macro_line|#endif
eof
