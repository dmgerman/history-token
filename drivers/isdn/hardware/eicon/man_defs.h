multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    1.9&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/* Definitions for use with the Management Information Element      */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Management information element                                   */
multiline_comment|/* ----------------------------------------------------------       */
multiline_comment|/* Byte     Coding            Comment                               */
multiline_comment|/* ----------------------------------------------------------       */
multiline_comment|/*    0 | 0 1 1 1 1 1 1 1 | ESC                                     */
multiline_comment|/*    1 | 0 x x x x x x x | Length of information element (m-1)     */
multiline_comment|/*    2 | 1 0 0 0 0 0 0 0 | Management Information Id               */
multiline_comment|/*    3 | x x x x x x x x | Type                                    */
multiline_comment|/*    4 | x x x x x x x x | Attribute                               */
multiline_comment|/*    5 | x x x x x x x x | Status                                  */
multiline_comment|/*    6 | x x x x x x x x | Variable Value Length (m-n)             */
multiline_comment|/*    7 | x x x x x x x x | Path / Variable Name String Length (n-8)*/
multiline_comment|/* 8..n | x x x x x x x x | Path/Node Name String separated by &squot;&bslash;&squot;  */
multiline_comment|/* n..m | x x x x x x x x | Variable content                        */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Type Field                                                       */
multiline_comment|/*                                                                  */
multiline_comment|/* MAN_READ:      not used                                          */
multiline_comment|/* MAN_WRITE:     not used                                          */
multiline_comment|/* MAN_EVENT_ON:  not used                                          */
multiline_comment|/* MAN_EVENT_OFF: not used                                          */
multiline_comment|/* MAN_INFO_IND:  type of variable                                  */
multiline_comment|/* MAN_EVENT_IND: type of variable                                  */
multiline_comment|/* MAN_TRACE_IND  not used                                          */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|MI_DIR
mdefine_line|#define MI_DIR          0x01  /* Directory string (zero terminated) */
DECL|macro|MI_EXECUTE
mdefine_line|#define MI_EXECUTE      0x02  /* Executable function (has no value) */
DECL|macro|MI_ASCIIZ
mdefine_line|#define MI_ASCIIZ       0x03  /* Zero terminated string             */
DECL|macro|MI_ASCII
mdefine_line|#define MI_ASCII        0x04  /* String, first byte is length       */
DECL|macro|MI_NUMBER
mdefine_line|#define MI_NUMBER       0x05  /* Number string, first byte is length*/
DECL|macro|MI_TRACE
mdefine_line|#define MI_TRACE        0x06  /* Trace information, format see below*/
DECL|macro|MI_FIXED_LENGTH
mdefine_line|#define MI_FIXED_LENGTH 0x80  /* get length from MAN_INFO max_len   */
DECL|macro|MI_INT
mdefine_line|#define MI_INT          0x81  /* number to display as signed int    */
DECL|macro|MI_UINT
mdefine_line|#define MI_UINT         0x82  /* number to display as unsigned int  */
DECL|macro|MI_HINT
mdefine_line|#define MI_HINT         0x83  /* number to display in hex format    */
DECL|macro|MI_HSTR
mdefine_line|#define MI_HSTR         0x84  /* number to display as a hex string  */
DECL|macro|MI_BOOLEAN
mdefine_line|#define MI_BOOLEAN      0x85  /* number to display as boolean       */
DECL|macro|MI_IP_ADDRESS
mdefine_line|#define MI_IP_ADDRESS   0x86  /* number to display as IP address    */
DECL|macro|MI_BITFLD
mdefine_line|#define MI_BITFLD       0x87  /* number to display as bit field     */
DECL|macro|MI_SPID_STATE
mdefine_line|#define MI_SPID_STATE   0x88  /* state# of SPID initialisation      */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Attribute Field                                                  */
multiline_comment|/*                                                                  */
multiline_comment|/* MAN_READ:      not used                                          */
multiline_comment|/* MAN_WRITE:     not used                                          */
multiline_comment|/* MAN_EVENT_ON:  not used                                          */
multiline_comment|/* MAN_EVENT_OFF: not used                                          */
multiline_comment|/* MAN_INFO_IND:  set according to capabilities of that variable    */
multiline_comment|/* MAN_EVENT_IND: not used                                          */
multiline_comment|/* MAN_TRACE_IND  not used                                          */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|MI_WRITE
mdefine_line|#define MI_WRITE        0x01  /* Variable is writeable              */
DECL|macro|MI_EVENT
mdefine_line|#define MI_EVENT        0x02  /* Variable can indicate changes      */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Status Field                                                     */
multiline_comment|/*                                                                  */
multiline_comment|/* MAN_READ:      not used                                          */
multiline_comment|/* MAN_WRITE:     not used                                          */
multiline_comment|/* MAN_EVENT_ON:  not used                                          */
multiline_comment|/* MAN_EVENT_OFF: not used                                          */
multiline_comment|/* MAN_INFO_IND:  set according to the actual status                */
multiline_comment|/* MAN_EVENT_IND: set according to the actual statu                 */
multiline_comment|/* MAN_TRACE_IND  not used                                          */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|MI_LOCKED
mdefine_line|#define MI_LOCKED       0x01  /* write protected by another instance*/
DECL|macro|MI_EVENT_ON
mdefine_line|#define MI_EVENT_ON     0x02  /* Event logging switched on          */
DECL|macro|MI_PROTECTED
mdefine_line|#define MI_PROTECTED    0x04  /* write protected by this instance   */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Data Format used for MAN_TRACE_IND (no MI-element used)          */
multiline_comment|/*------------------------------------------------------------------*/
DECL|typedef|MI_XLOG_HDR
r_typedef
r_struct
id|mi_xlog_hdr_s
id|MI_XLOG_HDR
suffix:semicolon
DECL|struct|mi_xlog_hdr_s
r_struct
id|mi_xlog_hdr_s
(brace
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
multiline_comment|/* Timestamp in msec units                 */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* Size of data that follows               */
DECL|member|code
r_int
r_int
id|code
suffix:semicolon
multiline_comment|/* code of trace event                     */
)brace
suffix:semicolon
multiline_comment|/* unspecified data follows this header    */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Trace mask definitions for trace events except B channel and     */
multiline_comment|/* debug trace events                                               */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|TM_D_CHAN
mdefine_line|#define TM_D_CHAN   0x0001  /* D-Channel        (D-.) Code 3,4      */
DECL|macro|TM_L_LAYER
mdefine_line|#define TM_L_LAYER  0x0002  /* Low Layer        (LL)  Code 6,7      */
DECL|macro|TM_N_LAYER
mdefine_line|#define TM_N_LAYER  0x0004  /* Network Layer    (N)   Code 14,15    */
DECL|macro|TM_DL_ERR
mdefine_line|#define TM_DL_ERR   0x0008  /* Data Link Error  (MDL) Code 9        */
DECL|macro|TM_LAYER1
mdefine_line|#define TM_LAYER1   0x0010  /* Layer 1                Code 20       */
DECL|macro|TM_C_COMM
mdefine_line|#define TM_C_COMM   0x0020  /* Call Comment     (SIG) Code 5,21,22  */
DECL|macro|TM_M_DATA
mdefine_line|#define TM_M_DATA   0x0040  /* Modulation Data  (EYE) Code 23       */
DECL|macro|TM_STRING
mdefine_line|#define TM_STRING   0x0080  /* Sting data             Code 24       */
DECL|macro|TM_N_USED2
mdefine_line|#define TM_N_USED2  0x0100  /* not used                             */
DECL|macro|TM_N_USED3
mdefine_line|#define TM_N_USED3  0x0200  /* not used                             */
DECL|macro|TM_N_USED4
mdefine_line|#define TM_N_USED4  0x0400  /* not used                             */
DECL|macro|TM_N_USED5
mdefine_line|#define TM_N_USED5  0x0800  /* not used                             */
DECL|macro|TM_N_USED6
mdefine_line|#define TM_N_USED6  0x1000  /* not used                             */
DECL|macro|TM_N_USED7
mdefine_line|#define TM_N_USED7  0x2000  /* not used                             */
DECL|macro|TM_N_USED8
mdefine_line|#define TM_N_USED8  0x4000  /* not used                             */
DECL|macro|TM_REST
mdefine_line|#define TM_REST     0x8000  /* Codes 10,11,12,13,16,18,19,128,129   */
multiline_comment|/*------ End of file -----------------------------------------------*/
eof
