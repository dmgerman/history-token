multiline_comment|/*&n; *&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * Eicon File Revision :    1.2  &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY &n; * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  &n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef PC_H_INCLUDED
DECL|macro|PC_H_INCLUDED
mdefine_line|#define PC_H_INCLUDED
DECL|macro|byte
mdefine_line|#define byte unsigned char
DECL|macro|word
mdefine_line|#define word unsigned short
DECL|macro|dword
mdefine_line|#define dword unsigned long
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* buffer definition                                                */
multiline_comment|/*------------------------------------------------------------------*/
r_typedef
r_struct
(brace
DECL|member|length
id|word
id|length
suffix:semicolon
multiline_comment|/* length of data/parameter field           */
DECL|member|P
id|byte
id|P
(braket
l_int|270
)braket
suffix:semicolon
multiline_comment|/* data/parameter field                     */
DECL|typedef|PBUFFER
)brace
id|PBUFFER
suffix:semicolon
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* dual port ram structure                                          */
multiline_comment|/*------------------------------------------------------------------*/
DECL|struct|dual
r_struct
id|dual
(brace
DECL|member|Req
id|byte
id|Req
suffix:semicolon
multiline_comment|/* request register                         */
DECL|member|ReqId
id|byte
id|ReqId
suffix:semicolon
multiline_comment|/* request task/entity identification       */
DECL|member|Rc
id|byte
id|Rc
suffix:semicolon
multiline_comment|/* return code register                     */
DECL|member|RcId
id|byte
id|RcId
suffix:semicolon
multiline_comment|/* return code task/entity identification   */
DECL|member|Ind
id|byte
id|Ind
suffix:semicolon
multiline_comment|/* Indication register                      */
DECL|member|IndId
id|byte
id|IndId
suffix:semicolon
multiline_comment|/* Indication task/entity identification    */
DECL|member|IMask
id|byte
id|IMask
suffix:semicolon
multiline_comment|/* Interrupt Mask Flag                      */
DECL|member|RNR
id|byte
id|RNR
suffix:semicolon
multiline_comment|/* Receiver Not Ready (set by PC)           */
DECL|member|XLock
id|byte
id|XLock
suffix:semicolon
multiline_comment|/* XBuffer locked Flag                      */
DECL|member|Int
id|byte
id|Int
suffix:semicolon
multiline_comment|/* ISDN-S interrupt                         */
DECL|member|ReqCh
id|byte
id|ReqCh
suffix:semicolon
multiline_comment|/* Channel field for layer-3 Requests       */
DECL|member|RcCh
id|byte
id|RcCh
suffix:semicolon
multiline_comment|/* Channel field for layer-3 Returncodes    */
DECL|member|IndCh
id|byte
id|IndCh
suffix:semicolon
multiline_comment|/* Channel field for layer-3 Indications    */
DECL|member|MInd
id|byte
id|MInd
suffix:semicolon
multiline_comment|/* more data indication field               */
DECL|member|MLength
id|word
id|MLength
suffix:semicolon
multiline_comment|/* more data total packet length            */
DECL|member|ReadyInt
id|byte
id|ReadyInt
suffix:semicolon
multiline_comment|/* request field for ready interrupt        */
DECL|member|SWReg
id|byte
id|SWReg
suffix:semicolon
multiline_comment|/* Software register for special purposes   */
DECL|member|Reserved
id|byte
id|Reserved
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* reserved space                           */
DECL|member|InterfaceType
id|byte
id|InterfaceType
suffix:semicolon
multiline_comment|/* interface type 1=16K interface           */
DECL|member|Signature
id|word
id|Signature
suffix:semicolon
multiline_comment|/* ISDN-S adapter Signature (GD)            */
DECL|member|XBuffer
id|PBUFFER
id|XBuffer
suffix:semicolon
multiline_comment|/* Transmit Buffer                          */
DECL|member|RBuffer
id|PBUFFER
id|RBuffer
suffix:semicolon
multiline_comment|/* Receive Buffer                           */
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* SWReg Values (0 means no command)                                */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|SWREG_DIE_WITH_LEDON
mdefine_line|#define SWREG_DIE_WITH_LEDON  0x01
DECL|macro|SWREG_HALT_CPU
mdefine_line|#define SWREG_HALT_CPU        0x02 /* Push CPU into a while(1) loop */         
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Id Fields Coding                                                 */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|ID_MASK
mdefine_line|#define ID_MASK 0xe0    /* Mask for the ID field                    */
DECL|macro|GL_ERR_ID
mdefine_line|#define GL_ERR_ID 0x1f  /* ID for error reporting on global requests*/
DECL|macro|DSIG_ID
mdefine_line|#define DSIG_ID  0x00   /* ID for D-channel signaling               */
DECL|macro|NL_ID
mdefine_line|#define NL_ID    0x20   /* ID for network-layer access (B or D)     */
DECL|macro|BLLC_ID
mdefine_line|#define BLLC_ID  0x60   /* ID for B-channel link level access       */
DECL|macro|TASK_ID
mdefine_line|#define TASK_ID  0x80   /* ID for dynamic user tasks                */
DECL|macro|TIMER_ID
mdefine_line|#define TIMER_ID 0xa0   /* ID for timer task                        */
DECL|macro|TEL_ID
mdefine_line|#define TEL_ID   0xc0   /* ID for telephone support                 */
DECL|macro|MAN_ID
mdefine_line|#define MAN_ID   0xe0   /* ID for management                        */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* ASSIGN and REMOVE requests are the same for all entities         */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|ASSIGN
mdefine_line|#define ASSIGN  0x01
DECL|macro|UREMOVE
mdefine_line|#define UREMOVE  0xfe   /* without returncode */  
DECL|macro|REMOVE
mdefine_line|#define REMOVE  0xff
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Timer Interrupt Task Interface                                   */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|ASSIGN_TIM
mdefine_line|#define ASSIGN_TIM 0x01
DECL|macro|REMOVE_TIM
mdefine_line|#define REMOVE_TIM 0xff
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* dynamic user task interface                                      */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|ASSIGN_TSK
mdefine_line|#define ASSIGN_TSK 0x01
DECL|macro|REMOVE_TSK
mdefine_line|#define REMOVE_TSK 0xff
DECL|macro|LOAD
mdefine_line|#define LOAD 0xf0
DECL|macro|RELOCATE
mdefine_line|#define RELOCATE 0xf1
DECL|macro|START
mdefine_line|#define START 0xf2
DECL|macro|LOAD2
mdefine_line|#define LOAD2 0xf3
DECL|macro|RELOCATE2
mdefine_line|#define RELOCATE2 0xf4
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* dynamic user task messages                                       */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|TSK_B2
mdefine_line|#define TSK_B2          0x0000
DECL|macro|TSK_WAKEUP
mdefine_line|#define TSK_WAKEUP      0x2000
DECL|macro|TSK_TIMER
mdefine_line|#define TSK_TIMER       0x4000
DECL|macro|TSK_TSK
mdefine_line|#define TSK_TSK         0x6000
DECL|macro|TSK_PC
mdefine_line|#define TSK_PC          0xe000
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* LL management primitives                                         */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|ASSIGN_LL
mdefine_line|#define ASSIGN_LL 1     /* assign logical link                      */
DECL|macro|REMOVE_LL
mdefine_line|#define REMOVE_LL 0xff  /* remove logical link                      */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* LL service primitives                                            */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|LL_UDATA
mdefine_line|#define LL_UDATA 1      /* link unit data request/indication        */
DECL|macro|LL_ESTABLISH
mdefine_line|#define LL_ESTABLISH 2  /* link establish request/indication        */
DECL|macro|LL_RELEASE
mdefine_line|#define LL_RELEASE 3    /* link release request/indication          */
DECL|macro|LL_DATA
mdefine_line|#define LL_DATA 4       /* data request/indication                  */
DECL|macro|LL_LOCAL
mdefine_line|#define LL_LOCAL 5      /* switch to local operation (COM only)     */
DECL|macro|LL_DATA_PEND
mdefine_line|#define LL_DATA_PEND 5  /* data pending indication (SDLC SHM only)  */
DECL|macro|LL_REMOTE
mdefine_line|#define LL_REMOTE 6     /* switch to remote operation (COM only)    */
DECL|macro|LL_TEST
mdefine_line|#define LL_TEST 8       /* link test request                        */
DECL|macro|LL_MDATA
mdefine_line|#define LL_MDATA 9      /* more data request/indication             */
DECL|macro|LL_BUDATA
mdefine_line|#define LL_BUDATA 10    /* broadcast unit data request/indication   */
DECL|macro|LL_XID
mdefine_line|#define LL_XID 12       /* XID command request/indication           */
DECL|macro|LL_XID_R
mdefine_line|#define LL_XID_R 13     /* XID response request/indication          */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* NL service primitives                                            */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|N_MDATA
mdefine_line|#define N_MDATA         1       /* more data to come REQ/IND        */
DECL|macro|N_CONNECT
mdefine_line|#define N_CONNECT       2       /* OSI N-CONNECT REQ/IND            */
DECL|macro|N_CONNECT_ACK
mdefine_line|#define N_CONNECT_ACK   3       /* OSI N-CONNECT CON/RES            */
DECL|macro|N_DISC
mdefine_line|#define N_DISC          4       /* OSI N-DISC REQ/IND               */
DECL|macro|N_DISC_ACK
mdefine_line|#define N_DISC_ACK      5       /* OSI N-DISC CON/RES               */
DECL|macro|N_RESET
mdefine_line|#define N_RESET         6       /* OSI N-RESET REQ/IND              */
DECL|macro|N_RESET_ACK
mdefine_line|#define N_RESET_ACK     7       /* OSI N-RESET CON/RES              */
DECL|macro|N_DATA
mdefine_line|#define N_DATA          8       /* OSI N-DATA REQ/IND               */
DECL|macro|N_EDATA
mdefine_line|#define N_EDATA         9       /* OSI N-EXPEDITED DATA REQ/IND     */
DECL|macro|N_UDATA
mdefine_line|#define N_UDATA         10      /* OSI D-UNIT-DATA REQ/IND          */
DECL|macro|N_BDATA
mdefine_line|#define N_BDATA         11      /* BROADCAST-DATA REQ/IND           */
DECL|macro|N_DATA_ACK
mdefine_line|#define N_DATA_ACK      12      /* data ack ind for D-bit procedure */
DECL|macro|N_EDATA_ACK
mdefine_line|#define N_EDATA_ACK     13      /* data ack ind for INTERRUPT       */
DECL|macro|N_Q_BIT
mdefine_line|#define N_Q_BIT         0x10    /* Q-bit for req/ind                */
DECL|macro|N_M_BIT
mdefine_line|#define N_M_BIT         0x20    /* M-bit for req/ind                */
DECL|macro|N_D_BIT
mdefine_line|#define N_D_BIT         0x40    /* D-bit for req/ind                */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Signaling management primitives                                  */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|ASSIGN_SIG
mdefine_line|#define ASSIGN_SIG 1    /* assign signaling task                    */
DECL|macro|UREMOVE_SIG
mdefine_line|#define UREMOVE_SIG 0xfe /* remove signaling task without returncode */
DECL|macro|REMOVE_SIG
mdefine_line|#define REMOVE_SIG 0xff /* remove signaling task                    */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Signaling service primitives                                     */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|CALL_REQ
mdefine_line|#define CALL_REQ 1      /* call request                             */
DECL|macro|CALL_CON
mdefine_line|#define CALL_CON 1      /* call confirmation                        */
DECL|macro|CALL_IND
mdefine_line|#define CALL_IND 2      /* incoming call connected                  */
DECL|macro|LISTEN_REQ
mdefine_line|#define LISTEN_REQ 2    /* listen request                           */
DECL|macro|HANGUP
mdefine_line|#define HANGUP 3        /* hangup request/indication                */
DECL|macro|SUSPEND
mdefine_line|#define SUSPEND 4       /* call suspend request/confirm             */
DECL|macro|RESUME
mdefine_line|#define RESUME 5        /* call resume request/confirm              */
DECL|macro|SUSPEND_REJ
mdefine_line|#define SUSPEND_REJ 6   /* suspend rejected indication              */
DECL|macro|USER_DATA
mdefine_line|#define USER_DATA 8     /* user data for user to user signaling     */
DECL|macro|CONGESTION
mdefine_line|#define CONGESTION 9    /* network congestion indication            */
DECL|macro|INDICATE_REQ
mdefine_line|#define INDICATE_REQ 10 /* request to indicate an incoming call     */
DECL|macro|INDICATE_IND
mdefine_line|#define INDICATE_IND 10 /* indicates that there is an incoming call */
DECL|macro|CALL_RES
mdefine_line|#define CALL_RES 11     /* accept an incoming call                  */
DECL|macro|CALL_ALERT
mdefine_line|#define CALL_ALERT 12   /* send ALERT for incoming call             */
DECL|macro|INFO_REQ
mdefine_line|#define INFO_REQ 13     /* INFO request                             */
DECL|macro|INFO_IND
mdefine_line|#define INFO_IND 13     /* INFO indication                          */
DECL|macro|REJECT
mdefine_line|#define REJECT 14       /* reject an incoming call                  */
DECL|macro|RESOURCES
mdefine_line|#define RESOURCES 15    /* reserve B-Channel hardware resources     */
DECL|macro|TEL_CTRL
mdefine_line|#define TEL_CTRL 16     /* Telephone control request/indication     */
DECL|macro|STATUS_REQ
mdefine_line|#define STATUS_REQ 17   /* Request D-State (returned in INFO_IND)   */
DECL|macro|FAC_REG_REQ
mdefine_line|#define FAC_REG_REQ 18  /* connection idependent fac registration   */
DECL|macro|FAC_REG_ACK
mdefine_line|#define FAC_REG_ACK 19  /* fac registration acknowledge             */
DECL|macro|FAC_REG_REJ
mdefine_line|#define FAC_REG_REJ 20  /* fac registration reject                  */
DECL|macro|CALL_COMPLETE
mdefine_line|#define CALL_COMPLETE 21/* send a CALL_PROC for incoming call       */
DECL|macro|FACILITY_REQ
mdefine_line|#define FACILITY_REQ 22 /* send a Facility Message type             */
DECL|macro|FACILITY_IND
mdefine_line|#define FACILITY_IND 22 /* Facility Message type indication         */
DECL|macro|SIG_CTRL
mdefine_line|#define SIG_CTRL     29 /* Control for signalling hardware          */
DECL|macro|DSP_CTRL
mdefine_line|#define DSP_CTRL     30 /* Control for DSPs                         */
DECL|macro|LAW_REQ
mdefine_line|#define LAW_REQ      31 /* Law config request for (returns info_i)  */ 
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* management service primitives                                    */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|MAN_READ
mdefine_line|#define MAN_READ        2
DECL|macro|MAN_WRITE
mdefine_line|#define MAN_WRITE       3
DECL|macro|MAN_EXECUTE
mdefine_line|#define MAN_EXECUTE     4
DECL|macro|MAN_EVENT_ON
mdefine_line|#define MAN_EVENT_ON    5
DECL|macro|MAN_EVENT_OFF
mdefine_line|#define MAN_EVENT_OFF   6
DECL|macro|MAN_LOCK
mdefine_line|#define MAN_LOCK        7
DECL|macro|MAN_UNLOCK
mdefine_line|#define MAN_UNLOCK      8   
DECL|macro|MAN_INFO_IND
mdefine_line|#define MAN_INFO_IND    2
DECL|macro|MAN_EVENT_IND
mdefine_line|#define MAN_EVENT_IND   3
DECL|macro|MAN_TRACE_IND
mdefine_line|#define MAN_TRACE_IND   4  
DECL|macro|MAN_ESC
mdefine_line|#define MAN_ESC         0x80
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* return code coding                                               */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|UNKNOWN_COMMAND
mdefine_line|#define UNKNOWN_COMMAND         0x01    /* unknown command          */
DECL|macro|WRONG_COMMAND
mdefine_line|#define WRONG_COMMAND           0x02    /* wrong command            */
DECL|macro|WRONG_ID
mdefine_line|#define WRONG_ID                0x03    /* unknown task/entity id   */
DECL|macro|WRONG_CH
mdefine_line|#define WRONG_CH                0x04    /* wrong task/entity id     */
DECL|macro|UNKNOWN_IE
mdefine_line|#define UNKNOWN_IE              0x05    /* unknown information el.  */
DECL|macro|WRONG_IE
mdefine_line|#define WRONG_IE                0x06    /* wrong information el.    */
DECL|macro|OUT_OF_RESOURCES
mdefine_line|#define OUT_OF_RESOURCES        0x07    /* ISDN-S card out of res.  */
DECL|macro|ADAPTER_DEAD
mdefine_line|#define ADAPTER_DEAD            0x08    /* ISDN card CPU halted     */ 
DECL|macro|N_FLOW_CONTROL
mdefine_line|#define N_FLOW_CONTROL          0x10    /* Flow-Control, retry      */
DECL|macro|ASSIGN_RC
mdefine_line|#define ASSIGN_RC               0xe0    /* ASSIGN acknowledgement   */
DECL|macro|ASSIGN_OK
mdefine_line|#define ASSIGN_OK               0xef    /* ASSIGN OK                */
DECL|macro|OK_FC
mdefine_line|#define OK_FC                   0xfc    /* Flow-Control RC          */
DECL|macro|READY_INT
mdefine_line|#define READY_INT               0xfd    /* Ready interrupt          */
DECL|macro|TIMER_INT
mdefine_line|#define TIMER_INT               0xfe    /* timer interrupt          */
DECL|macro|OK
mdefine_line|#define OK                      0xff    /* command accepted         */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* information elements                                             */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|SHIFT
mdefine_line|#define SHIFT 0x90              /* codeset shift                    */
DECL|macro|MORE
mdefine_line|#define MORE 0xa0               /* more data                        */
DECL|macro|CL
mdefine_line|#define CL 0xb0                 /* congestion level                 */
multiline_comment|/* codeset 0                                                */
DECL|macro|BC
mdefine_line|#define BC  0x04                /* Bearer Capability                */
DECL|macro|CAU
mdefine_line|#define CAU 0x08                /* cause                            */
DECL|macro|CAD
mdefine_line|#define CAD 0x0c                /* Connected address                */
DECL|macro|CAI
mdefine_line|#define CAI 0x10                /* call identity                    */
DECL|macro|CHI
mdefine_line|#define CHI 0x18                /* channel identification           */
DECL|macro|LLI
mdefine_line|#define LLI 0x19                /* logical link id                  */
DECL|macro|CHA
mdefine_line|#define CHA 0x1a                /* charge advice                    */
DECL|macro|DT
mdefine_line|#define DT  0x29                /* ETSI date/time                   */
DECL|macro|KEY
mdefine_line|#define KEY 0x2c                /* keypad information element       */
DECL|macro|FTY
mdefine_line|#define FTY 0x1c                /* facility information element     */ 
DECL|macro|DSP
mdefine_line|#define DSP 0x28                /* display                          */
DECL|macro|OAD
mdefine_line|#define OAD 0x6c                /* origination address              */
DECL|macro|OSA
mdefine_line|#define OSA 0x6d                /* origination sub-address          */
DECL|macro|CPN
mdefine_line|#define CPN 0x70                /* called party number              */
DECL|macro|DSA
mdefine_line|#define DSA 0x71                /* destination sub-address          */
DECL|macro|RDX
mdefine_line|#define RDX 0x73                /* redirected number extended       */
DECL|macro|RDN
mdefine_line|#define RDN 0x74                /* redirected number                */  
DECL|macro|LLC
mdefine_line|#define LLC 0x7c                /* low layer compatibility          */
DECL|macro|HLC
mdefine_line|#define HLC 0x7d                /* high layer compatibility         */
DECL|macro|UUI
mdefine_line|#define UUI 0x7e                /* user user information            */
DECL|macro|ESC
mdefine_line|#define ESC 0x7f                /* escape extension                 */
DECL|macro|DLC
mdefine_line|#define DLC 0x20                /* data link layer configuration    */
DECL|macro|NLC
mdefine_line|#define NLC 0x21                /* network layer configuration      */
multiline_comment|/* codeset 6                                                */
DECL|macro|SIN
mdefine_line|#define SIN 0x01                /* service indicator                */
DECL|macro|CIF
mdefine_line|#define CIF 0x02                /* charging information             */
DECL|macro|DATE
mdefine_line|#define DATE 0x03               /* date                             */
DECL|macro|CPS
mdefine_line|#define CPS 0x07                /* called party status              */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* TEL_CTRL contents                                                */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|RING_ON
mdefine_line|#define RING_ON         0x01
DECL|macro|RING_OFF
mdefine_line|#define RING_OFF        0x02
DECL|macro|HANDS_FREE_ON
mdefine_line|#define HANDS_FREE_ON   0x03
DECL|macro|HANDS_FREE_OFF
mdefine_line|#define HANDS_FREE_OFF  0x04
DECL|macro|ON_HOOK
mdefine_line|#define ON_HOOK         0x80
DECL|macro|OFF_HOOK
mdefine_line|#define OFF_HOOK        0x90
macro_line|#endif
eof
