multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef DSPDIDS_H_
DECL|macro|DSPDIDS_H_
mdefine_line|#define DSPDIDS_H_
multiline_comment|/*---------------------------------------------------------------------------*/
DECL|macro|DSP_DID_INVALID
mdefine_line|#define DSP_DID_INVALID   0
DECL|macro|DSP_DID_DIVA
mdefine_line|#define DSP_DID_DIVA   1
DECL|macro|DSP_DID_DIVA_PRO
mdefine_line|#define DSP_DID_DIVA_PRO  2
DECL|macro|DSP_DID_DIVA_PRO_20
mdefine_line|#define DSP_DID_DIVA_PRO_20  3
DECL|macro|DSP_DID_DIVA_PRO_PCCARD
mdefine_line|#define DSP_DID_DIVA_PRO_PCCARD  4
DECL|macro|DSP_DID_DIVA_SERVER_BRI_1M
mdefine_line|#define DSP_DID_DIVA_SERVER_BRI_1M 5
DECL|macro|DSP_DID_DIVA_SERVER_BRI_2M
mdefine_line|#define DSP_DID_DIVA_SERVER_BRI_2M 6
DECL|macro|DSP_DID_DIVA_SERVER_PRI_2M_TX
mdefine_line|#define DSP_DID_DIVA_SERVER_PRI_2M_TX 7
DECL|macro|DSP_DID_DIVA_SERVER_PRI_2M_RX
mdefine_line|#define DSP_DID_DIVA_SERVER_PRI_2M_RX 8
DECL|macro|DSP_DID_DIVA_SERVER_PRI_30M
mdefine_line|#define DSP_DID_DIVA_SERVER_PRI_30M 9
DECL|macro|DSP_DID_TASK_HSCX
mdefine_line|#define DSP_DID_TASK_HSCX  100
DECL|macro|DSP_DID_TASK_HSCX_PRI_2M_TX
mdefine_line|#define DSP_DID_TASK_HSCX_PRI_2M_TX 101
DECL|macro|DSP_DID_TASK_HSCX_PRI_2M_RX
mdefine_line|#define DSP_DID_TASK_HSCX_PRI_2M_RX 102
DECL|macro|DSP_DID_TASK_V110KRNL
mdefine_line|#define DSP_DID_TASK_V110KRNL  200
DECL|macro|DSP_DID_OVERLAY_V1100
mdefine_line|#define DSP_DID_OVERLAY_V1100  201
DECL|macro|DSP_DID_OVERLAY_V1101
mdefine_line|#define DSP_DID_OVERLAY_V1101  202
DECL|macro|DSP_DID_OVERLAY_V1102
mdefine_line|#define DSP_DID_OVERLAY_V1102  203
DECL|macro|DSP_DID_OVERLAY_V1103
mdefine_line|#define DSP_DID_OVERLAY_V1103  204
DECL|macro|DSP_DID_OVERLAY_V1104
mdefine_line|#define DSP_DID_OVERLAY_V1104  205
DECL|macro|DSP_DID_OVERLAY_V1105
mdefine_line|#define DSP_DID_OVERLAY_V1105  206
DECL|macro|DSP_DID_OVERLAY_V1106
mdefine_line|#define DSP_DID_OVERLAY_V1106  207
DECL|macro|DSP_DID_OVERLAY_V1107
mdefine_line|#define DSP_DID_OVERLAY_V1107  208
DECL|macro|DSP_DID_OVERLAY_V1108
mdefine_line|#define DSP_DID_OVERLAY_V1108  209
DECL|macro|DSP_DID_OVERLAY_V1109
mdefine_line|#define DSP_DID_OVERLAY_V1109  210
DECL|macro|DSP_DID_TASK_V110_PRI_2M_TX
mdefine_line|#define DSP_DID_TASK_V110_PRI_2M_TX 220
DECL|macro|DSP_DID_TASK_V110_PRI_2M_RX
mdefine_line|#define DSP_DID_TASK_V110_PRI_2M_RX 221
DECL|macro|DSP_DID_TASK_MODEM
mdefine_line|#define DSP_DID_TASK_MODEM  300
DECL|macro|DSP_DID_TASK_FAX05
mdefine_line|#define DSP_DID_TASK_FAX05  400
DECL|macro|DSP_DID_TASK_VOICE
mdefine_line|#define DSP_DID_TASK_VOICE  500
DECL|macro|DSP_DID_TASK_TIKRNL81
mdefine_line|#define DSP_DID_TASK_TIKRNL81  600
DECL|macro|DSP_DID_OVERLAY_DIAL
mdefine_line|#define DSP_DID_OVERLAY_DIAL  601
DECL|macro|DSP_DID_OVERLAY_V22
mdefine_line|#define DSP_DID_OVERLAY_V22  602
DECL|macro|DSP_DID_OVERLAY_V32
mdefine_line|#define DSP_DID_OVERLAY_V32  603
DECL|macro|DSP_DID_OVERLAY_FSK
mdefine_line|#define DSP_DID_OVERLAY_FSK  604
DECL|macro|DSP_DID_OVERLAY_FAX
mdefine_line|#define DSP_DID_OVERLAY_FAX  605
DECL|macro|DSP_DID_OVERLAY_VXX
mdefine_line|#define DSP_DID_OVERLAY_VXX  606
DECL|macro|DSP_DID_OVERLAY_V8
mdefine_line|#define DSP_DID_OVERLAY_V8  607
DECL|macro|DSP_DID_OVERLAY_INFO
mdefine_line|#define DSP_DID_OVERLAY_INFO  608
DECL|macro|DSP_DID_OVERLAY_V34
mdefine_line|#define DSP_DID_OVERLAY_V34  609
DECL|macro|DSP_DID_OVERLAY_DFX
mdefine_line|#define DSP_DID_OVERLAY_DFX  610
DECL|macro|DSP_DID_PARTIAL_OVERLAY_DIAL
mdefine_line|#define DSP_DID_PARTIAL_OVERLAY_DIAL 611
DECL|macro|DSP_DID_PARTIAL_OVERLAY_FSK
mdefine_line|#define DSP_DID_PARTIAL_OVERLAY_FSK 612
DECL|macro|DSP_DID_PARTIAL_OVERLAY_FAX
mdefine_line|#define DSP_DID_PARTIAL_OVERLAY_FAX 613
DECL|macro|DSP_DID_TASK_TIKRNL05
mdefine_line|#define DSP_DID_TASK_TIKRNL05  700
multiline_comment|/*---------------------------------------------------------------------------*/
macro_line|#endif
multiline_comment|/*---------------------------------------------------------------------------*/
eof
