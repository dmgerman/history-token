multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef PC_H_INCLUDED  /* { */
DECL|macro|PC_H_INCLUDED
mdefine_line|#define PC_H_INCLUDED
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
mdefine_line|#define UREMOVE 0xfe /* without return code */
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
DECL|macro|N_XON
mdefine_line|#define N_XON           15      /* clear RNR state */
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
mdefine_line|#define ASSIGN_SIG  1    /* assign signaling task                    */
DECL|macro|UREMOVE_SIG
mdefine_line|#define UREMOVE_SIG 0xfe /* remove signaling task without return code*/
DECL|macro|REMOVE_SIG
mdefine_line|#define REMOVE_SIG  0xff /* remove signaling task                    */
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
DECL|macro|HW_CTRL
mdefine_line|#define HW_CTRL 16      /* B-Channel hardware IOCTL req/ind         */
DECL|macro|TEL_CTRL
mdefine_line|#define TEL_CTRL 16     /* Telephone control request/indication     */
DECL|macro|STATUS_REQ
mdefine_line|#define STATUS_REQ 17   /* Request D-State (returned in INFO_IND)   */
DECL|macro|FAC_REG_REQ
mdefine_line|#define FAC_REG_REQ 18  /* 1TR6 connection independent fac reg      */
DECL|macro|FAC_REG_ACK
mdefine_line|#define FAC_REG_ACK 19  /* 1TR6 fac registration acknowledge        */
DECL|macro|FAC_REG_REJ
mdefine_line|#define FAC_REG_REJ 20  /* 1TR6 fac registration reject             */
DECL|macro|CALL_COMPLETE
mdefine_line|#define CALL_COMPLETE 21/* send a CALL_PROC for incoming call       */
DECL|macro|SW_CTRL
mdefine_line|#define SW_CTRL 22      /* extended software features               */
DECL|macro|REGISTER_REQ
mdefine_line|#define REGISTER_REQ 23 /* Q.931 connection independent reg req     */
DECL|macro|REGISTER_IND
mdefine_line|#define REGISTER_IND 24 /* Q.931 connection independent reg ind     */
DECL|macro|FACILITY_REQ
mdefine_line|#define FACILITY_REQ 25 /* Q.931 connection independent fac req     */
DECL|macro|FACILITY_IND
mdefine_line|#define FACILITY_IND 26 /* Q.931 connection independent fac ind     */
DECL|macro|NCR_INFO_REQ
mdefine_line|#define NCR_INFO_REQ 27 /* INFO_REQ with NULL CR                    */
DECL|macro|GCR_MIM_REQ
mdefine_line|#define GCR_MIM_REQ 28  /* MANAGEMENT_INFO_REQ with global CR       */
DECL|macro|SIG_CTRL
mdefine_line|#define SIG_CTRL    29  /* Control for Signalling Hardware          */
DECL|macro|DSP_CTRL
mdefine_line|#define DSP_CTRL    30  /* Control for DSPs                         */
DECL|macro|LAW_REQ
mdefine_line|#define LAW_REQ      31 /* Law config request for (returns info_i)  */
DECL|macro|SPID_CTRL
mdefine_line|#define SPID_CTRL    32 /* Request/indication SPID related          */
DECL|macro|NCR_FACILITY
mdefine_line|#define NCR_FACILITY 33 /* Request/indication with NULL/DUMMY CR    */
DECL|macro|CALL_HOLD
mdefine_line|#define CALL_HOLD    34 /* Request/indication to hold a CALL        */
DECL|macro|CALL_RETRIEVE
mdefine_line|#define CALL_RETRIEVE 35 /* Request/indication to retrieve a CALL   */
DECL|macro|CALL_HOLD_ACK
mdefine_line|#define CALL_HOLD_ACK 36 /* OK of                hold a CALL        */
DECL|macro|CALL_RETRIEVE_ACK
mdefine_line|#define CALL_RETRIEVE_ACK 37 /* OK of             retrieve a CALL   */
DECL|macro|CALL_HOLD_REJ
mdefine_line|#define CALL_HOLD_REJ 38 /* Reject of            hold a CALL        */
DECL|macro|CALL_RETRIEVE_REJ
mdefine_line|#define CALL_RETRIEVE_REJ 39 /* Reject of         retrieve a call   */
DECL|macro|GCR_RESTART
mdefine_line|#define GCR_RESTART   40 /* Send/Receive Restart message            */
DECL|macro|S_SERVICE
mdefine_line|#define S_SERVICE     41 /* Send/Receive Supplementary Service      */
DECL|macro|S_SERVICE_REJ
mdefine_line|#define S_SERVICE_REJ 42 /* Reject Supplementary Service indication */
DECL|macro|S_SUPPORTED
mdefine_line|#define S_SUPPORTED   43 /* Req/Ind to get Supported Services       */
DECL|macro|STATUS_ENQ
mdefine_line|#define STATUS_ENQ    44 /* Req to send the D-ch request if !state0 */
DECL|macro|CALL_GUARD
mdefine_line|#define CALL_GUARD    45 /* Req/Ind to use the FLAGS_CALL_OUTCHECK  */
DECL|macro|CALL_GUARD_HP
mdefine_line|#define CALL_GUARD_HP 46 /* Call Guard function to reject a call    */
DECL|macro|CALL_GUARD_IF
mdefine_line|#define CALL_GUARD_IF 47 /* Call Guard function, inform the appl    */
DECL|macro|SSEXT_REQ
mdefine_line|#define SSEXT_REQ     48 /* Supplem.Serv./QSIG specific request     */
DECL|macro|SSEXT_IND
mdefine_line|#define SSEXT_IND     49 /* Supplem.Serv./QSIG specific indication  */
multiline_comment|/* reserved commands for the US protocols */
DECL|macro|INT_3PTY_NIND
mdefine_line|#define INT_3PTY_NIND 50 /* US       specific indication            */
DECL|macro|INT_CF_NIND
mdefine_line|#define INT_CF_NIND   51 /* US       specific indication            */
DECL|macro|INT_3PTY_DROP
mdefine_line|#define INT_3PTY_DROP 52 /* US       specific indication            */
DECL|macro|INT_MOVE_CONF
mdefine_line|#define INT_MOVE_CONF 53 /* US       specific indication            */
DECL|macro|INT_MOVE_RC
mdefine_line|#define INT_MOVE_RC   54 /* US       specific indication            */
DECL|macro|INT_MOVE_FLIPPED_CONF
mdefine_line|#define INT_MOVE_FLIPPED_CONF 55 /* US specific indication          */
DECL|macro|INT_X5NI_OK
mdefine_line|#define INT_X5NI_OK   56 /* internal transfer OK indication         */
DECL|macro|INT_XDMS_START
mdefine_line|#define INT_XDMS_START 57 /* internal transfer OK indication        */
DECL|macro|INT_XDMS_STOP
mdefine_line|#define INT_XDMS_STOP 58 /* internal transfer finish indication     */
DECL|macro|INT_XDMS_STOP2
mdefine_line|#define INT_XDMS_STOP2 59 /* internal transfer send FA              */
DECL|macro|INT_CUSTCONF_REJ
mdefine_line|#define INT_CUSTCONF_REJ 60 /* internal conference reject           */
DECL|macro|INT_CUSTXFER
mdefine_line|#define INT_CUSTXFER 61 /* internal transfer request                */
DECL|macro|INT_CUSTX_NIND
mdefine_line|#define INT_CUSTX_NIND 62 /* internal transfer ack                  */
DECL|macro|INT_CUSTXREJ_NIND
mdefine_line|#define INT_CUSTXREJ_NIND 63 /* internal transfer rej               */
DECL|macro|INT_X5NI_CF_XFER
mdefine_line|#define INT_X5NI_CF_XFER  64 /* internal transfer OK indication     */
DECL|macro|VSWITCH_REQ
mdefine_line|#define VSWITCH_REQ 65        /* communication between protocol and */
DECL|macro|VSWITCH_IND
mdefine_line|#define VSWITCH_IND 66        /* capifunctions for D-CH-switching   */
DECL|macro|MWI_POLL
mdefine_line|#define MWI_POLL 67     /* Message Waiting Status Request fkt */
DECL|macro|CALL_PEND_NOTIFY
mdefine_line|#define CALL_PEND_NOTIFY 68 /* notify capi to set new listen        */
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
DECL|macro|ISDN_GUARD_REJ
mdefine_line|#define ISDN_GUARD_REJ          0x09    /* ISDN-Guard SuppServ rej  */
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
DECL|macro|SMSG
mdefine_line|#define SMSG 0x00               /* segmented message                */
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
DECL|macro|FTY
mdefine_line|#define FTY 0x1c                /* Facility                         */
DECL|macro|DT
mdefine_line|#define DT  0x29                /* ETSI date/time                   */
DECL|macro|KEY
mdefine_line|#define KEY 0x2c                /* keypad information element       */
DECL|macro|UID
mdefine_line|#define UID 0x2d                /* User id information element      */
DECL|macro|DSP
mdefine_line|#define DSP 0x28                /* display                          */
DECL|macro|SIG
mdefine_line|#define SIG 0x34                /* signalling hardware control      */
DECL|macro|OAD
mdefine_line|#define OAD 0x6c                /* origination address              */
DECL|macro|OSA
mdefine_line|#define OSA 0x6d                /* origination sub-address          */
DECL|macro|CPN
mdefine_line|#define CPN 0x70                /* called party number              */
DECL|macro|DSA
mdefine_line|#define DSA 0x71                /* destination sub-address          */
DECL|macro|RDX
mdefine_line|#define RDX 0x73                /* redirecting number extended      */
DECL|macro|RDN
mdefine_line|#define RDN 0x74                /* redirecting number               */
DECL|macro|RIN
mdefine_line|#define RIN 0x76                /* redirection number               */
DECL|macro|RI
mdefine_line|#define RI  0x79                /* restart indicator                */
DECL|macro|MIE
mdefine_line|#define MIE 0x7a                /* management info element          */
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
multiline_comment|/* ESC information elements                                         */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|MSGTYPEIE
mdefine_line|#define MSGTYPEIE        0x7a   /* Messagetype info element         */
DECL|macro|CRIE
mdefine_line|#define CRIE             0x7b   /* INFO info element                */
DECL|macro|VSWITCHIE
mdefine_line|#define VSWITCHIE        0xed   /* VSwitch info element             */
DECL|macro|SSEXTIE
mdefine_line|#define SSEXTIE          0xee   /* Supplem. Service info element    */
DECL|macro|PROFILEIE
mdefine_line|#define PROFILEIE        0xef   /* Profile info element             */
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
multiline_comment|/* operation values used by ETSI supplementary services */
DECL|macro|THREE_PTY_BEGIN
mdefine_line|#define THREE_PTY_BEGIN           0x04
DECL|macro|THREE_PTY_END
mdefine_line|#define THREE_PTY_END             0x05
DECL|macro|ECT_EXECUTE
mdefine_line|#define ECT_EXECUTE               0x06
DECL|macro|ACTIVATION_DIVERSION
mdefine_line|#define ACTIVATION_DIVERSION      0x07
DECL|macro|DEACTIVATION_DIVERSION
mdefine_line|#define DEACTIVATION_DIVERSION    0x08
DECL|macro|CALL_DEFLECTION
mdefine_line|#define CALL_DEFLECTION           0x0D
DECL|macro|INTERROGATION_DIVERSION
mdefine_line|#define INTERROGATION_DIVERSION   0x0B
DECL|macro|INTERROGATION_SERV_USR_NR
mdefine_line|#define INTERROGATION_SERV_USR_NR 0x11
DECL|macro|ACTIVATION_MWI
mdefine_line|#define ACTIVATION_MWI            0x20
DECL|macro|DEACTIVATION_MWI
mdefine_line|#define DEACTIVATION_MWI          0x21
DECL|macro|MWI_INDICATION
mdefine_line|#define MWI_INDICATION            0x22
DECL|macro|MWI_RESPONSE
mdefine_line|#define MWI_RESPONSE              0x23
DECL|macro|CONF_BEGIN
mdefine_line|#define CONF_BEGIN                0x28
DECL|macro|CONF_ADD
mdefine_line|#define CONF_ADD                  0x29
DECL|macro|CONF_SPLIT
mdefine_line|#define CONF_SPLIT                0x2a
DECL|macro|CONF_DROP
mdefine_line|#define CONF_DROP                 0x2b
DECL|macro|CONF_ISOLATE
mdefine_line|#define CONF_ISOLATE              0x2c
DECL|macro|CONF_REATTACH
mdefine_line|#define CONF_REATTACH             0x2d
DECL|macro|CONF_PARTYDISC
mdefine_line|#define CONF_PARTYDISC            0x2e
DECL|macro|CCBS_INFO_RETAIN
mdefine_line|#define CCBS_INFO_RETAIN          0x2f
DECL|macro|CCBS_ERASECALLLINKAGEID
mdefine_line|#define CCBS_ERASECALLLINKAGEID   0x30
DECL|macro|CCBS_STOP_ALERTING
mdefine_line|#define CCBS_STOP_ALERTING        0x31
DECL|macro|CCBS_REQUEST
mdefine_line|#define CCBS_REQUEST              0x32
DECL|macro|CCBS_DEACTIVATE
mdefine_line|#define CCBS_DEACTIVATE           0x33
DECL|macro|CCBS_INTERROGATE
mdefine_line|#define CCBS_INTERROGATE          0x34
DECL|macro|GET_SUPPORTED_SERVICES
mdefine_line|#define GET_SUPPORTED_SERVICES    0xff
DECL|macro|DIVERSION_PROCEDURE_CFU
mdefine_line|#define DIVERSION_PROCEDURE_CFU     0x70
DECL|macro|DIVERSION_PROCEDURE_CFB
mdefine_line|#define DIVERSION_PROCEDURE_CFB     0x71
DECL|macro|DIVERSION_PROCEDURE_CFNR
mdefine_line|#define DIVERSION_PROCEDURE_CFNR    0x72
DECL|macro|DIVERSION_DEACTIVATION_CFU
mdefine_line|#define DIVERSION_DEACTIVATION_CFU  0x80
DECL|macro|DIVERSION_DEACTIVATION_CFB
mdefine_line|#define DIVERSION_DEACTIVATION_CFB  0x81
DECL|macro|DIVERSION_DEACTIVATION_CFNR
mdefine_line|#define DIVERSION_DEACTIVATION_CFNR 0x82
DECL|macro|DIVERSION_INTERROGATE_NUM
mdefine_line|#define DIVERSION_INTERROGATE_NUM   0x11
DECL|macro|DIVERSION_INTERROGATE_CFU
mdefine_line|#define DIVERSION_INTERROGATE_CFU   0x60
DECL|macro|DIVERSION_INTERROGATE_CFB
mdefine_line|#define DIVERSION_INTERROGATE_CFB   0x61
DECL|macro|DIVERSION_INTERROGATE_CFNR
mdefine_line|#define DIVERSION_INTERROGATE_CFNR  0x62
multiline_comment|/* Service Masks */
DECL|macro|SMASK_HOLD_RETRIEVE
mdefine_line|#define SMASK_HOLD_RETRIEVE        0x00000001
DECL|macro|SMASK_TERMINAL_PORTABILITY
mdefine_line|#define SMASK_TERMINAL_PORTABILITY 0x00000002
DECL|macro|SMASK_ECT
mdefine_line|#define SMASK_ECT                  0x00000004
DECL|macro|SMASK_3PTY
mdefine_line|#define SMASK_3PTY                 0x00000008
DECL|macro|SMASK_CALL_FORWARDING
mdefine_line|#define SMASK_CALL_FORWARDING      0x00000010
DECL|macro|SMASK_CALL_DEFLECTION
mdefine_line|#define SMASK_CALL_DEFLECTION      0x00000020
DECL|macro|SMASK_CCBS
mdefine_line|#define SMASK_CCBS                 0x00000080
DECL|macro|SMASK_MWI
mdefine_line|#define SMASK_MWI                  0x00000100
DECL|macro|SMASK_CCNR
mdefine_line|#define SMASK_CCNR                 0x00000200
DECL|macro|SMASK_CONF
mdefine_line|#define SMASK_CONF                 0x00000400
multiline_comment|/* ----------------------------------------------&n;    Types of transfers used to transfer the&n;    information in the &squot;struct RC-&gt;Reserved2[8]&squot;&n;    The information is transferred as 2 dwords&n;    (2 4Byte unsigned values)&n;    First of them is the transfer type.&n;    2^32-1 possible messages are possible in this way.&n;    The context of the second one had no meaning&n;   ---------------------------------------------- */
DECL|macro|DIVA_RC_TYPE_NONE
mdefine_line|#define DIVA_RC_TYPE_NONE              0x00000000
DECL|macro|DIVA_RC_TYPE_REMOVE_COMPLETE
mdefine_line|#define DIVA_RC_TYPE_REMOVE_COMPLETE   0x00000008
DECL|macro|DIVA_RC_TYPE_STREAM_PTR
mdefine_line|#define DIVA_RC_TYPE_STREAM_PTR        0x00000009
DECL|macro|DIVA_RC_TYPE_CMA_PTR
mdefine_line|#define DIVA_RC_TYPE_CMA_PTR           0x0000000a
DECL|macro|DIVA_RC_TYPE_OK_FC
mdefine_line|#define DIVA_RC_TYPE_OK_FC             0x0000000b
DECL|macro|DIVA_RC_TYPE_RX_DMA
mdefine_line|#define DIVA_RC_TYPE_RX_DMA            0x0000000c
multiline_comment|/* ------------------------------------------------------&n;      IO Control codes for IN BAND SIGNALING&n;   ------------------------------------------------------ */
DECL|macro|CTRL_L1_SET_SIG_ID
mdefine_line|#define CTRL_L1_SET_SIG_ID        5
DECL|macro|CTRL_L1_SET_DAD
mdefine_line|#define CTRL_L1_SET_DAD           6
DECL|macro|CTRL_L1_RESOURCES
mdefine_line|#define CTRL_L1_RESOURCES         7
multiline_comment|/* ------------------------------------------------------ */
multiline_comment|/* ------------------------------------------------------&n;      Layer 2 types&n;   ------------------------------------------------------ */
DECL|macro|X75T
mdefine_line|#define X75T            1       /* x.75 for ttx                     */
DECL|macro|TRF
mdefine_line|#define TRF             2       /* transparent with hdlc framing    */
DECL|macro|TRF_IN
mdefine_line|#define TRF_IN          3       /* transparent with hdlc fr. inc.   */
DECL|macro|SDLC
mdefine_line|#define SDLC            4       /* sdlc, sna layer-2                */
DECL|macro|X75
mdefine_line|#define X75             5       /* x.75 for btx                     */
DECL|macro|LAPD
mdefine_line|#define LAPD            6       /* lapd (Q.921)                     */
DECL|macro|X25_L2
mdefine_line|#define X25_L2          7       /* x.25 layer-2                     */
DECL|macro|V120_L2
mdefine_line|#define V120_L2         8       /* V.120 layer-2 protocol           */
DECL|macro|V42_IN
mdefine_line|#define V42_IN          9       /* V.42 layer-2 protocol, incomming */
DECL|macro|V42
mdefine_line|#define V42            10       /* V.42 layer-2 protocol            */
DECL|macro|MDM_ATP
mdefine_line|#define MDM_ATP        11       /* AT Parser built in the L2        */
DECL|macro|X75_V42BIS
mdefine_line|#define X75_V42BIS     12       /* x.75 with V.42bis                */
DECL|macro|RTPL2_IN
mdefine_line|#define RTPL2_IN       13       /* RTP layer-2 protocol, incomming  */
DECL|macro|RTPL2
mdefine_line|#define RTPL2          14       /* RTP layer-2 protocol             */
DECL|macro|V120_V42BIS
mdefine_line|#define V120_V42BIS    15       /* V.120 asynchronous mode supporting V.42bis compression */
DECL|macro|PIAFS_CRC
mdefine_line|#define PIAFS_CRC      29       /* PIAFS Layer 2 with CRC calculation at L2 */
multiline_comment|/* ------------------------------------------------------&n;   PIAFS DLC DEFINITIONS&n;   ------------------------------------------------------ */
DECL|macro|PIAFS_64K
mdefine_line|#define PIAFS_64K            0x01
DECL|macro|PIAFS_VARIABLE_SPEED
mdefine_line|#define PIAFS_VARIABLE_SPEED 0x02
DECL|macro|PIAFS_CHINESE_SPEED
mdefine_line|#define PIAFS_CHINESE_SPEED    0x04
DECL|macro|PIAFS_UDATA_ABILITY_ID
mdefine_line|#define PIAFS_UDATA_ABILITY_ID    0x80
DECL|macro|PIAFS_UDATA_ABILITY_DCDON
mdefine_line|#define PIAFS_UDATA_ABILITY_DCDON 0x01
DECL|macro|PIAFS_UDATA_ABILITY_DDI
mdefine_line|#define PIAFS_UDATA_ABILITY_DDI   0x80
multiline_comment|/*&n;DLC of PIAFS :&n;Byte | 8 7 6 5 4 3 2 1&n;-----+--------------------------------------------------------&n;   0 | 0 0 1 0 0 0 0 0  Data Link Configuration&n;   1 | X X X X X X X X  Length of IE (at least 15 Bytes)&n;   2 | 0 0 0 0 0 0 0 0  max. information field, LOW  byte (not used, fix 73 Bytes)&n;   3 | 0 0 0 0 0 0 0 0  max. information field, HIGH byte (not used, fix 73 Bytes)&n;   4 | 0 0 0 0 0 0 0 0  address A (not used)&n;   5 | 0 0 0 0 0 0 0 0  address B (not used)&n;   6 | 0 0 0 0 0 0 0 0  Mode (not used, fix 128)&n;   7 | 0 0 0 0 0 0 0 0  Window Size (not used, fix 127)&n;   8 | X X X X X X X X  XID Length, Low Byte (at least 7 Bytes)&n;   9 | X X X X X X X X  XID Length, High Byte&n;  10 | 0 0 0 0 0 C V S  PIAFS Protocol Speed configuration -&gt; Note(1)&n;     |                  S = 0 -&gt; Protocol Speed is 32K&n;     |                  S = 1 -&gt; Protocol Speed is 64K&n;     |                  V = 0 -&gt; Protocol Speed is fixed&n;     |                  V = 1 -&gt; Protocol Speed is variable&n;     |                  C = 0 -&gt; speed setting according to standard&n;     |                  C = 1 -&gt; speed setting for chinese implementation&n;  11 | 0 0 0 0 0 0 R T  P0 - V42bis Compression enable/disable, Low Byte&n;     |                  T = 0 -&gt; Transmit Direction enable&n;     |                  T = 1 -&gt; Transmit Direction disable&n;     |                  R = 0 -&gt; Receive  Direction enable&n;     |                  R = 1 -&gt; Receive  Direction disable&n;  13 | 0 0 0 0 0 0 0 0  P0 - V42bis Compression enable/disable, High Byte&n;  14 | X X X X X X X X  P1 - V42bis Dictionary Size, Low Byte&n;  15 | X X X X X X X X  P1 - V42bis Dictionary Size, High Byte&n;  16 | X X X X X X X X  P2 - V42bis String Length, Low Byte&n;  17 | X X X X X X X X  P2 - V42bis String Length, High Byte&n;  18 | X X X X X X X X  PIAFS extension length&n;  19 | 1 0 0 0 0 0 0 0  PIAFS extension Id (0x80) - UDATA abilities&n;  20 | U 0 0 0 0 0 0 D  UDATA abilities -&gt; Note (2)&n;     |                  up to now the following Bits are defined:&n;     |                  D - signal DCD ON&n;     |                  U - use extensive UDATA control communication&n;     |                      for DDI test application&n;+ Note (1): ----------+------+-----------------------------------------+&n;| PIAFS Protocol      | Bit  |                                         |&n;| Speed configuration |    S | Bit 1 - Protocol Speed                  |&n;|                     |      |         0 - 32K                         |&n;|                     |      |         1 - 64K (default)               |&n;|                     |    V | Bit 2 - Variable Protocol Speed         |&n;|                     |      |         0 - Speed is fix                |&n;|                     |      |         1 - Speed is variable (default) |&n;|                     |      |             OVERWRITES 32k Bit 1        |&n;|                     |    C | Bit 3   0 - Speed Settings according to |&n;|                     |      |             PIAFS specification         |&n;|                     |      |         1 - Speed setting for chinese   |&n;|                     |      |             PIAFS implementation        |&n;|                     |      | Explanation for chinese speed settings: |&n;|                     |      |         if Bit 3 is set the following   |&n;|                     |      |         rules apply:                    |&n;|                     |      |         Bit1=0 Bit2=0: 32k fix          |&n;|                     |      |         Bit1=1 Bit2=0: 64k fix          |&n;|                     |      |         Bit1=0 Bit2=1: PIAFS is trying  |&n;|                     |      |             to negotiate 32k is that is |&n;|                     |      |             not possible it tries to    |&n;|                     |      |             negotiate 64k               |&n;|                     |      |         Bit1=1 Bit2=1: PIAFS is trying  |&n;|                     |      |             to negotiate 64k is that is |&n;|                     |      |             not possible it tries to    |&n;|                     |      |             negotiate 32k               |&n;+ Note (2): ----------+------+-----------------------------------------+&n;| PIAFS               | Bit  | this byte defines the usage of UDATA    |&n;| Implementation      |      | control communication                   |&n;| UDATA usage         |    D | Bit 1 - DCD-ON signalling               |&n;|                     |      |         0 - no DCD-ON is signalled      |&n;|                     |      |             (default)                   |&n;|                     |      |         1 - DCD-ON will be signalled    |&n;|                     |    U | Bit 8 - DDI test application UDATA      |&n;|                     |      |         control communication           |&n;|                     |      |         0 - no UDATA control            |&n;|                     |      |             communication (default)     |&n;|                     |      |             sets as well the DCD-ON     |&n;|                     |      |             signalling                  |&n;|                     |      |         1 - UDATA control communication |&n;|                     |      |             ATTENTION: Do not use these |&n;|                     |      |                        setting if you   |&n;|                     |      |                        are not really   |&n;|                     |      |                        that you need it |&n;|                     |      |                        and you know     |&n;|                     |      |                        exactly what you |&n;|                     |      |                        are doing.       |&n;|                     |      |                        You can easily   |&n;|                     |      |                        disable any      |&n;|                     |      |                        data transfer.   |&n;+---------------------+------+-----------------------------------------+&n;*/
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* CAPI-like profile to indicate features on LAW_REQ                */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|GL_INTERNAL_CONTROLLER_SUPPORTED
mdefine_line|#define GL_INTERNAL_CONTROLLER_SUPPORTED     0x00000001L
DECL|macro|GL_EXTERNAL_EQUIPMENT_SUPPORTED
mdefine_line|#define GL_EXTERNAL_EQUIPMENT_SUPPORTED      0x00000002L
DECL|macro|GL_HANDSET_SUPPORTED
mdefine_line|#define GL_HANDSET_SUPPORTED                 0x00000004L
DECL|macro|GL_DTMF_SUPPORTED
mdefine_line|#define GL_DTMF_SUPPORTED                    0x00000008L
DECL|macro|GL_SUPPLEMENTARY_SERVICES_SUPPORTED
mdefine_line|#define GL_SUPPLEMENTARY_SERVICES_SUPPORTED  0x00000010L
DECL|macro|GL_CHANNEL_ALLOCATION_SUPPORTED
mdefine_line|#define GL_CHANNEL_ALLOCATION_SUPPORTED      0x00000020L
DECL|macro|GL_BCHANNEL_OPERATION_SUPPORTED
mdefine_line|#define GL_BCHANNEL_OPERATION_SUPPORTED      0x00000040L
DECL|macro|GL_LINE_INTERCONNECT_SUPPORTED
mdefine_line|#define GL_LINE_INTERCONNECT_SUPPORTED       0x00000080L
DECL|macro|B1_HDLC_SUPPORTED
mdefine_line|#define B1_HDLC_SUPPORTED                    0x00000001L
DECL|macro|B1_TRANSPARENT_SUPPORTED
mdefine_line|#define B1_TRANSPARENT_SUPPORTED             0x00000002L
DECL|macro|B1_V110_ASYNC_SUPPORTED
mdefine_line|#define B1_V110_ASYNC_SUPPORTED              0x00000004L
DECL|macro|B1_V110_SYNC_SUPPORTED
mdefine_line|#define B1_V110_SYNC_SUPPORTED               0x00000008L
DECL|macro|B1_T30_SUPPORTED
mdefine_line|#define B1_T30_SUPPORTED                     0x00000010L
DECL|macro|B1_HDLC_INVERTED_SUPPORTED
mdefine_line|#define B1_HDLC_INVERTED_SUPPORTED           0x00000020L
DECL|macro|B1_TRANSPARENT_R_SUPPORTED
mdefine_line|#define B1_TRANSPARENT_R_SUPPORTED           0x00000040L
DECL|macro|B1_MODEM_ALL_NEGOTIATE_SUPPORTED
mdefine_line|#define B1_MODEM_ALL_NEGOTIATE_SUPPORTED     0x00000080L
DECL|macro|B1_MODEM_ASYNC_SUPPORTED
mdefine_line|#define B1_MODEM_ASYNC_SUPPORTED             0x00000100L
DECL|macro|B1_MODEM_SYNC_HDLC_SUPPORTED
mdefine_line|#define B1_MODEM_SYNC_HDLC_SUPPORTED         0x00000200L
DECL|macro|B2_X75_SUPPORTED
mdefine_line|#define B2_X75_SUPPORTED                     0x00000001L
DECL|macro|B2_TRANSPARENT_SUPPORTED
mdefine_line|#define B2_TRANSPARENT_SUPPORTED             0x00000002L
DECL|macro|B2_SDLC_SUPPORTED
mdefine_line|#define B2_SDLC_SUPPORTED                    0x00000004L
DECL|macro|B2_LAPD_SUPPORTED
mdefine_line|#define B2_LAPD_SUPPORTED                    0x00000008L
DECL|macro|B2_T30_SUPPORTED
mdefine_line|#define B2_T30_SUPPORTED                     0x00000010L
DECL|macro|B2_PPP_SUPPORTED
mdefine_line|#define B2_PPP_SUPPORTED                     0x00000020L
DECL|macro|B2_TRANSPARENT_NO_CRC_SUPPORTED
mdefine_line|#define B2_TRANSPARENT_NO_CRC_SUPPORTED      0x00000040L
DECL|macro|B2_MODEM_EC_COMPRESSION_SUPPORTED
mdefine_line|#define B2_MODEM_EC_COMPRESSION_SUPPORTED    0x00000080L
DECL|macro|B2_X75_V42BIS_SUPPORTED
mdefine_line|#define B2_X75_V42BIS_SUPPORTED              0x00000100L
DECL|macro|B2_V120_ASYNC_SUPPORTED
mdefine_line|#define B2_V120_ASYNC_SUPPORTED              0x00000200L
DECL|macro|B2_V120_ASYNC_V42BIS_SUPPORTED
mdefine_line|#define B2_V120_ASYNC_V42BIS_SUPPORTED       0x00000400L
DECL|macro|B2_V120_BIT_TRANSPARENT_SUPPORTED
mdefine_line|#define B2_V120_BIT_TRANSPARENT_SUPPORTED    0x00000800L
DECL|macro|B2_LAPD_FREE_SAPI_SEL_SUPPORTED
mdefine_line|#define B2_LAPD_FREE_SAPI_SEL_SUPPORTED      0x00001000L
DECL|macro|B3_TRANSPARENT_SUPPORTED
mdefine_line|#define B3_TRANSPARENT_SUPPORTED             0x00000001L
DECL|macro|B3_T90NL_SUPPORTED
mdefine_line|#define B3_T90NL_SUPPORTED                   0x00000002L
DECL|macro|B3_ISO8208_SUPPORTED
mdefine_line|#define B3_ISO8208_SUPPORTED                 0x00000004L
DECL|macro|B3_X25_DCE_SUPPORTED
mdefine_line|#define B3_X25_DCE_SUPPORTED                 0x00000008L
DECL|macro|B3_T30_SUPPORTED
mdefine_line|#define B3_T30_SUPPORTED                     0x00000010L
DECL|macro|B3_T30_WITH_EXTENSIONS_SUPPORTED
mdefine_line|#define B3_T30_WITH_EXTENSIONS_SUPPORTED     0x00000020L
DECL|macro|B3_RESERVED_SUPPORTED
mdefine_line|#define B3_RESERVED_SUPPORTED                0x00000040L
DECL|macro|B3_MODEM_SUPPORTED
mdefine_line|#define B3_MODEM_SUPPORTED                   0x00000080L
DECL|macro|MANUFACTURER_FEATURE_SLAVE_CODEC
mdefine_line|#define MANUFACTURER_FEATURE_SLAVE_CODEC          0x00000001L
DECL|macro|MANUFACTURER_FEATURE_FAX_MORE_DOCUMENTS
mdefine_line|#define MANUFACTURER_FEATURE_FAX_MORE_DOCUMENTS   0x00000002L
DECL|macro|MANUFACTURER_FEATURE_HARDDTMF
mdefine_line|#define MANUFACTURER_FEATURE_HARDDTMF             0x00000004L
DECL|macro|MANUFACTURER_FEATURE_SOFTDTMF_SEND
mdefine_line|#define MANUFACTURER_FEATURE_SOFTDTMF_SEND        0x00000008L
DECL|macro|MANUFACTURER_FEATURE_DTMF_PARAMETERS
mdefine_line|#define MANUFACTURER_FEATURE_DTMF_PARAMETERS      0x00000010L
DECL|macro|MANUFACTURER_FEATURE_SOFTDTMF_RECEIVE
mdefine_line|#define MANUFACTURER_FEATURE_SOFTDTMF_RECEIVE     0x00000020L
DECL|macro|MANUFACTURER_FEATURE_FAX_SUB_SEP_PWD
mdefine_line|#define MANUFACTURER_FEATURE_FAX_SUB_SEP_PWD      0x00000040L
DECL|macro|MANUFACTURER_FEATURE_V18
mdefine_line|#define MANUFACTURER_FEATURE_V18                  0x00000080L
DECL|macro|MANUFACTURER_FEATURE_MIXER_CH_CH
mdefine_line|#define MANUFACTURER_FEATURE_MIXER_CH_CH          0x00000100L
DECL|macro|MANUFACTURER_FEATURE_MIXER_CH_PC
mdefine_line|#define MANUFACTURER_FEATURE_MIXER_CH_PC          0x00000200L
DECL|macro|MANUFACTURER_FEATURE_MIXER_PC_CH
mdefine_line|#define MANUFACTURER_FEATURE_MIXER_PC_CH          0x00000400L
DECL|macro|MANUFACTURER_FEATURE_MIXER_PC_PC
mdefine_line|#define MANUFACTURER_FEATURE_MIXER_PC_PC          0x00000800L
DECL|macro|MANUFACTURER_FEATURE_ECHO_CANCELLER
mdefine_line|#define MANUFACTURER_FEATURE_ECHO_CANCELLER       0x00001000L
DECL|macro|MANUFACTURER_FEATURE_RTP
mdefine_line|#define MANUFACTURER_FEATURE_RTP                  0x00002000L
DECL|macro|MANUFACTURER_FEATURE_T38
mdefine_line|#define MANUFACTURER_FEATURE_T38                  0x00004000L
DECL|macro|MANUFACTURER_FEATURE_TRANSP_DELIVERY_CONF
mdefine_line|#define MANUFACTURER_FEATURE_TRANSP_DELIVERY_CONF 0x00008000L
DECL|macro|MANUFACTURER_FEATURE_XONOFF_FLOW_CONTROL
mdefine_line|#define MANUFACTURER_FEATURE_XONOFF_FLOW_CONTROL  0x00010000L
DECL|macro|MANUFACTURER_FEATURE_OOB_CHANNEL
mdefine_line|#define MANUFACTURER_FEATURE_OOB_CHANNEL          0x00020000L
DECL|macro|MANUFACTURER_FEATURE_IN_BAND_CHANNEL
mdefine_line|#define MANUFACTURER_FEATURE_IN_BAND_CHANNEL      0x00040000L
DECL|macro|MANUFACTURER_FEATURE_IN_BAND_FEATURE
mdefine_line|#define MANUFACTURER_FEATURE_IN_BAND_FEATURE      0x00080000L
DECL|macro|MANUFACTURER_FEATURE_PIAFS
mdefine_line|#define MANUFACTURER_FEATURE_PIAFS                0x00100000L
DECL|macro|MANUFACTURER_FEATURE_DTMF_TONE
mdefine_line|#define MANUFACTURER_FEATURE_DTMF_TONE            0x00200000L
DECL|macro|MANUFACTURER_FEATURE_FAX_PAPER_FORMATS
mdefine_line|#define MANUFACTURER_FEATURE_FAX_PAPER_FORMATS    0x00400000L
DECL|macro|MANUFACTURER_FEATURE_OK_FC_LABEL
mdefine_line|#define MANUFACTURER_FEATURE_OK_FC_LABEL          0x00800000L
DECL|macro|MANUFACTURER_FEATURE_VOWN
mdefine_line|#define MANUFACTURER_FEATURE_VOWN                 0x01000000L
DECL|macro|MANUFACTURER_FEATURE_XCONNECT
mdefine_line|#define MANUFACTURER_FEATURE_XCONNECT             0x02000000L
DECL|macro|MANUFACTURER_FEATURE_DMACONNECT
mdefine_line|#define MANUFACTURER_FEATURE_DMACONNECT           0x04000000L
DECL|macro|MANUFACTURER_FEATURE_AUDIO_TAP
mdefine_line|#define MANUFACTURER_FEATURE_AUDIO_TAP            0x08000000L
DECL|macro|MANUFACTURER_FEATURE_FAX_NONSTANDARD
mdefine_line|#define MANUFACTURER_FEATURE_FAX_NONSTANDARD      0x10000000L
DECL|macro|RTP_PRIM_PAYLOAD_PCMU_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_PCMU_8000     0
DECL|macro|RTP_PRIM_PAYLOAD_1016_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_1016_8000     1
DECL|macro|RTP_PRIM_PAYLOAD_G726_32_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_G726_32_8000  2
DECL|macro|RTP_PRIM_PAYLOAD_GSM_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_GSM_8000      3
DECL|macro|RTP_PRIM_PAYLOAD_G723_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_G723_8000     4
DECL|macro|RTP_PRIM_PAYLOAD_DVI4_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_DVI4_8000     5
DECL|macro|RTP_PRIM_PAYLOAD_DVI4_16000
mdefine_line|#define RTP_PRIM_PAYLOAD_DVI4_16000    6
DECL|macro|RTP_PRIM_PAYLOAD_LPC_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_LPC_8000      7
DECL|macro|RTP_PRIM_PAYLOAD_PCMA_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_PCMA_8000     8
DECL|macro|RTP_PRIM_PAYLOAD_G722_16000
mdefine_line|#define RTP_PRIM_PAYLOAD_G722_16000    9
DECL|macro|RTP_PRIM_PAYLOAD_QCELP_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_QCELP_8000    12
DECL|macro|RTP_PRIM_PAYLOAD_G728_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_G728_8000     14
DECL|macro|RTP_PRIM_PAYLOAD_G729_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_G729_8000     18
DECL|macro|RTP_PRIM_PAYLOAD_GSM_HR_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_GSM_HR_8000   30
DECL|macro|RTP_PRIM_PAYLOAD_GSM_EFR_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_GSM_EFR_8000  31
DECL|macro|RTP_ADD_PAYLOAD_BASE
mdefine_line|#define RTP_ADD_PAYLOAD_BASE           32
DECL|macro|RTP_ADD_PAYLOAD_RED
mdefine_line|#define RTP_ADD_PAYLOAD_RED            32
DECL|macro|RTP_ADD_PAYLOAD_CN_8000
mdefine_line|#define RTP_ADD_PAYLOAD_CN_8000        33
DECL|macro|RTP_ADD_PAYLOAD_DTMF
mdefine_line|#define RTP_ADD_PAYLOAD_DTMF           34
DECL|macro|RTP_PRIM_PAYLOAD_PCMU_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_PCMU_8000_SUPPORTED     (1L &lt;&lt; RTP_PRIM_PAYLOAD_PCMU_8000)
DECL|macro|RTP_PRIM_PAYLOAD_1016_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_1016_8000_SUPPORTED     (1L &lt;&lt; RTP_PRIM_PAYLOAD_1016_8000)
DECL|macro|RTP_PRIM_PAYLOAD_G726_32_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_G726_32_8000_SUPPORTED  (1L &lt;&lt; RTP_PRIM_PAYLOAD_G726_32_8000)
DECL|macro|RTP_PRIM_PAYLOAD_GSM_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_GSM_8000_SUPPORTED      (1L &lt;&lt; RTP_PRIM_PAYLOAD_GSM_8000)
DECL|macro|RTP_PRIM_PAYLOAD_G723_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_G723_8000_SUPPORTED     (1L &lt;&lt; RTP_PRIM_PAYLOAD_G723_8000)
DECL|macro|RTP_PRIM_PAYLOAD_DVI4_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_DVI4_8000_SUPPORTED     (1L &lt;&lt; RTP_PRIM_PAYLOAD_DVI4_8000)
DECL|macro|RTP_PRIM_PAYLOAD_DVI4_16000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_DVI4_16000_SUPPORTED    (1L &lt;&lt; RTP_PRIM_PAYLOAD_DVI4_16000)
DECL|macro|RTP_PRIM_PAYLOAD_LPC_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_LPC_8000_SUPPORTED      (1L &lt;&lt; RTP_PRIM_PAYLOAD_LPC_8000)
DECL|macro|RTP_PRIM_PAYLOAD_PCMA_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_PCMA_8000_SUPPORTED     (1L &lt;&lt; RTP_PRIM_PAYLOAD_PCMA_8000)
DECL|macro|RTP_PRIM_PAYLOAD_G722_16000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_G722_16000_SUPPORTED    (1L &lt;&lt; RTP_PRIM_PAYLOAD_G722_16000)
DECL|macro|RTP_PRIM_PAYLOAD_QCELP_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_QCELP_8000_SUPPORTED    (1L &lt;&lt; RTP_PRIM_PAYLOAD_QCELP_8000)
DECL|macro|RTP_PRIM_PAYLOAD_G728_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_G728_8000_SUPPORTED     (1L &lt;&lt; RTP_PRIM_PAYLOAD_G728_8000)
DECL|macro|RTP_PRIM_PAYLOAD_G729_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_G729_8000_SUPPORTED     (1L &lt;&lt; RTP_PRIM_PAYLOAD_G729_8000)
DECL|macro|RTP_PRIM_PAYLOAD_GSM_HR_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_GSM_HR_8000_SUPPORTED   (1L &lt;&lt; RTP_PRIM_PAYLOAD_GSM_HR_8000)
DECL|macro|RTP_PRIM_PAYLOAD_GSM_EFR_8000_SUPPORTED
mdefine_line|#define RTP_PRIM_PAYLOAD_GSM_EFR_8000_SUPPORTED  (1L &lt;&lt; RTP_PRIM_PAYLOAD_GSM_EFR_8000)
DECL|macro|RTP_ADD_PAYLOAD_RED_SUPPORTED
mdefine_line|#define RTP_ADD_PAYLOAD_RED_SUPPORTED            (1L &lt;&lt; (RTP_ADD_PAYLOAD_RED - RTP_ADD_PAYLOAD_BASE))
DECL|macro|RTP_ADD_PAYLOAD_CN_8000_SUPPORTED
mdefine_line|#define RTP_ADD_PAYLOAD_CN_8000_SUPPORTED        (1L &lt;&lt; (RTP_ADD_PAYLOAD_CN_8000 - RTP_ADD_PAYLOAD_BASE))
DECL|macro|RTP_ADD_PAYLOAD_DTMF_SUPPORTED
mdefine_line|#define RTP_ADD_PAYLOAD_DTMF_SUPPORTED           (1L &lt;&lt; (RTP_ADD_PAYLOAD_DTMF - RTP_ADD_PAYLOAD_BASE))
multiline_comment|/* virtual switching definitions */
DECL|macro|VSJOIN
mdefine_line|#define VSJOIN         1
DECL|macro|VSTRANSPORT
mdefine_line|#define VSTRANSPORT    2
DECL|macro|VSGETPARAMS
mdefine_line|#define VSGETPARAMS    3
DECL|macro|VSCAD
mdefine_line|#define VSCAD          1
DECL|macro|VSRXCPNAME
mdefine_line|#define VSRXCPNAME     2
DECL|macro|VSCALLSTAT
mdefine_line|#define VSCALLSTAT     3
DECL|macro|VSINVOKEID
mdefine_line|#define VSINVOKEID    4
DECL|macro|VSCLMRKS
mdefine_line|#define VSCLMRKS       5
DECL|macro|VSTBCTIDENT
mdefine_line|#define VSTBCTIDENT    6
multiline_comment|/* -----------------------------------------------------------**&n;** The PROTOCOL_FEATURE_STRING in feature.h (included         **&n;** in prstart.sx and astart.sx) defines capabilities and      **&n;** features of the actual protocol code. It&squot;s used as a bit   **&n;** mask.                                                      **&n;** The following Bits are defined:                            **&n;** -----------------------------------------------------------*/
DECL|macro|PROTCAP_TELINDUS
mdefine_line|#define PROTCAP_TELINDUS  0x0001  /* Telindus Variant of protocol code   */
DECL|macro|PROTCAP_MAN_IF
mdefine_line|#define PROTCAP_MAN_IF    0x0002  /* Management interface implemented    */
DECL|macro|PROTCAP_V_42
mdefine_line|#define PROTCAP_V_42      0x0004  /* V42 implemented                     */
DECL|macro|PROTCAP_V90D
mdefine_line|#define PROTCAP_V90D      0x0008  /* V.90D (implies up to 384k DSP code) */
DECL|macro|PROTCAP_EXTD_FAX
mdefine_line|#define PROTCAP_EXTD_FAX  0x0010  /* Extended FAX (ECM, 2D, T6, Polling) */
DECL|macro|PROTCAP_EXTD_RXFC
mdefine_line|#define PROTCAP_EXTD_RXFC 0x0020  /* RxFC (Extd Flow Control), OOB Chnl  */
DECL|macro|PROTCAP_VOIP
mdefine_line|#define PROTCAP_VOIP      0x0040  /* VoIP (implies up to 512k DSP code)  */
DECL|macro|PROTCAP_CMA_ALLPR
mdefine_line|#define PROTCAP_CMA_ALLPR 0x0080  /* CMA support for all NL primitives   */
DECL|macro|PROTCAP_FREE8
mdefine_line|#define PROTCAP_FREE8     0x0100  /* not used                            */
DECL|macro|PROTCAP_FREE9
mdefine_line|#define PROTCAP_FREE9     0x0200  /* not used                            */
DECL|macro|PROTCAP_FREE10
mdefine_line|#define PROTCAP_FREE10    0x0400  /* not used                            */
DECL|macro|PROTCAP_FREE11
mdefine_line|#define PROTCAP_FREE11    0x0800  /* not used                            */
DECL|macro|PROTCAP_FREE12
mdefine_line|#define PROTCAP_FREE12    0x1000  /* not used                            */
DECL|macro|PROTCAP_FREE13
mdefine_line|#define PROTCAP_FREE13    0x2000  /* not used                            */
DECL|macro|PROTCAP_FREE14
mdefine_line|#define PROTCAP_FREE14    0x4000  /* not used                            */
DECL|macro|PROTCAP_EXTENSION
mdefine_line|#define PROTCAP_EXTENSION 0x8000  /* used for future extentions          */
macro_line|#else
macro_line|#endif /* PC_H_INCLUDED  } */
eof
