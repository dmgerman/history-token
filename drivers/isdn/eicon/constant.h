multiline_comment|/*&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * Eicon File Revision :    1.0  &n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Q.931 information elements maximum length                        */
multiline_comment|/* excluding the identifier, including the length field             */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|MAX_LEN_BC
mdefine_line|#define MAX_LEN_BC      13
DECL|macro|MAX_LEN_LLC
mdefine_line|#define MAX_LEN_LLC     19 /* ctr3 */
DECL|macro|MAX_LEN_HLC
mdefine_line|#define MAX_LEN_HLC     6  /* ctr3 */
DECL|macro|MAX_LEN_UUI
mdefine_line|#define MAX_LEN_UUI     200 /* Hicom USBS req */
DECL|macro|MAX_LEN_NUM
mdefine_line|#define MAX_LEN_NUM     24
DECL|macro|MAX_LEN_DSP
mdefine_line|#define MAX_LEN_DSP     83 /* ctr3 */
DECL|macro|MAX_LEN_NI
mdefine_line|#define MAX_LEN_NI      4
DECL|macro|MAX_LEN_PI
mdefine_line|#define MAX_LEN_PI      5
DECL|macro|MAX_LEN_SIN
mdefine_line|#define MAX_LEN_SIN     3
DECL|macro|MAX_LEN_CST
mdefine_line|#define MAX_LEN_CST     4
DECL|macro|MAX_LEN_SIG
mdefine_line|#define MAX_LEN_SIG     2
DECL|macro|MAX_LEN_SPID
mdefine_line|#define MAX_LEN_SPID    32
DECL|macro|MAX_LEN_EID
mdefine_line|#define MAX_LEN_EID     3
DECL|macro|MAX_LEN_CHI
mdefine_line|#define MAX_LEN_CHI     35  /* ctr3 */
DECL|macro|MAX_LEN_CAU
mdefine_line|#define MAX_LEN_CAU     33
DECL|macro|MAX_LEN_FTY
mdefine_line|#define MAX_LEN_FTY     130
DECL|macro|MAX_LEN_KEY
mdefine_line|#define MAX_LEN_KEY     83  /* ctr3 */
DECL|macro|MAX_LEN_RSI
mdefine_line|#define MAX_LEN_RSI     4
DECL|macro|MAX_LEN_CAI
mdefine_line|#define MAX_LEN_CAI     11
DECL|macro|MAX_NUM_SPID
mdefine_line|#define MAX_NUM_SPID    4
DECL|macro|MAX_LEN_USERID
mdefine_line|#define MAX_LEN_USERID  9
DECL|macro|MAX_LEN_APPLID
mdefine_line|#define MAX_LEN_APPLID  5
DECL|macro|MAX_LEN_NTTCIF
mdefine_line|#define MAX_LEN_NTTCIF  15
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* decision return values                                           */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|YES
mdefine_line|#define YES             1
DECL|macro|NO
mdefine_line|#define NO              0
multiline_comment|/*-------------------------------------------------------------------*/
multiline_comment|/* w element coding                                                  */
multiline_comment|/*-------------------------------------------------------------------*/
DECL|macro|NTTCIF
mdefine_line|#define NTTCIF          0x01
DECL|macro|BC
mdefine_line|#define BC              0x04
DECL|macro|CAU
mdefine_line|#define CAU             0x08
DECL|macro|CAD
mdefine_line|#define CAD             0x0c
DECL|macro|CAI
mdefine_line|#define CAI             0x10
DECL|macro|CST
mdefine_line|#define CST             0x14
DECL|macro|CHI
mdefine_line|#define CHI             0x18
DECL|macro|LLI
mdefine_line|#define LLI             0x19
DECL|macro|CHA
mdefine_line|#define CHA             0x1a
DECL|macro|FTY
mdefine_line|#define FTY             0x1c
DECL|macro|PI
mdefine_line|#define PI              0x1e
DECL|macro|NFAC
mdefine_line|#define NFAC            0x20
DECL|macro|TC
mdefine_line|#define TC              0x24
DECL|macro|ATT_EID
mdefine_line|#define ATT_EID         0x26
DECL|macro|NI
mdefine_line|#define NI              0x27
DECL|macro|DSP
mdefine_line|#define DSP             0x28
DECL|macro|DT
mdefine_line|#define DT              0x29
DECL|macro|KEY
mdefine_line|#define KEY             0x2c
DECL|macro|KP
mdefine_line|#define KP              0x2c
DECL|macro|UID
mdefine_line|#define UID             0x2d
DECL|macro|SIG
mdefine_line|#define SIG             0x34
DECL|macro|FI
mdefine_line|#define FI              0x39
DECL|macro|SPID
mdefine_line|#define SPID            0x3a
DECL|macro|EID
mdefine_line|#define EID             0x3b
DECL|macro|DSPF
mdefine_line|#define DSPF            0x3c
DECL|macro|ECAD
mdefine_line|#define ECAD            0x4c
DECL|macro|OAD
mdefine_line|#define OAD             0x6c
DECL|macro|OSA
mdefine_line|#define OSA             0x6d
DECL|macro|DAD
mdefine_line|#define DAD             0x70
DECL|macro|CPN
mdefine_line|#define CPN             0x70
DECL|macro|DSA
mdefine_line|#define DSA             0x71
DECL|macro|RDX
mdefine_line|#define RDX             0x73
DECL|macro|RAD
mdefine_line|#define RAD             0x74
DECL|macro|RDN
mdefine_line|#define RDN             0x74
DECL|macro|RSI
mdefine_line|#define RSI             0x79
DECL|macro|SCR
mdefine_line|#define SCR             0x7A   /* internal unscreened CPN          */
DECL|macro|MIE
mdefine_line|#define MIE             0x7a   /* internal management info element */
DECL|macro|LLC
mdefine_line|#define LLC             0x7c
DECL|macro|HLC
mdefine_line|#define HLC             0x7d
DECL|macro|UUI
mdefine_line|#define UUI             0x7e
DECL|macro|ESC
mdefine_line|#define ESC             0x7f
DECL|macro|SHIFT
mdefine_line|#define SHIFT           0x90
DECL|macro|MORE
mdefine_line|#define MORE            0xa0
DECL|macro|CL
mdefine_line|#define CL              0xb0
multiline_comment|/* information elements used on the spid interface */
DECL|macro|SPID_CMD
mdefine_line|#define SPID_CMD        0xc0
DECL|macro|SPID_LINK
mdefine_line|#define SPID_LINK       0x10
DECL|macro|SPID_DN
mdefine_line|#define SPID_DN         0x70
DECL|macro|SPID_BC
mdefine_line|#define SPID_BC         0x04
DECL|macro|SPID_SWITCH
mdefine_line|#define SPID_SWITCH     0x11
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* global configuration parameters, defined in exec.c               */
multiline_comment|/* these parameters are configured with program loading             */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|PROT_1TR6
mdefine_line|#define PROT_1TR6       0
DECL|macro|PROT_ETSI
mdefine_line|#define PROT_ETSI       1
DECL|macro|PROT_FRANC
mdefine_line|#define PROT_FRANC      2
DECL|macro|PROT_BELG
mdefine_line|#define PROT_BELG       3
DECL|macro|PROT_SWED
mdefine_line|#define PROT_SWED       4
DECL|macro|PROT_NI
mdefine_line|#define PROT_NI         5
DECL|macro|PROT_5ESS
mdefine_line|#define PROT_5ESS       6
DECL|macro|PROT_JAPAN
mdefine_line|#define PROT_JAPAN      7
DECL|macro|PROT_ATEL
mdefine_line|#define PROT_ATEL       8
DECL|macro|PROT_US
mdefine_line|#define PROT_US         9
DECL|macro|PROT_ITALY
mdefine_line|#define PROT_ITALY      10
DECL|macro|PROT_TWAN
mdefine_line|#define PROT_TWAN       11
DECL|macro|PROT_AUSTRAL
mdefine_line|#define PROT_AUSTRAL    12
DECL|macro|INIT_PROT_1TR6
mdefine_line|#define INIT_PROT_1TR6    0x80|PROT_1TR6
DECL|macro|INIT_PROT_ETSI
mdefine_line|#define INIT_PROT_ETSI    0x80|PROT_ETSI
DECL|macro|INIT_PROT_FRANC
mdefine_line|#define INIT_PROT_FRANC   0x80|PROT_FRANC
DECL|macro|INIT_PROT_BELG
mdefine_line|#define INIT_PROT_BELG    0x80|PROT_BELG
DECL|macro|INIT_PROT_SWED
mdefine_line|#define INIT_PROT_SWED    0x80|PROT_SWED
DECL|macro|INIT_PROT_NI
mdefine_line|#define INIT_PROT_NI      0x80|PROT_NI
DECL|macro|INIT_PROT_5ESS
mdefine_line|#define INIT_PROT_5ESS    0x80|PROT_5ESS
DECL|macro|INIT_PROT_JAPAN
mdefine_line|#define INIT_PROT_JAPAN   0x80|PROT_JAPAN
DECL|macro|INIT_PROT_ATEL
mdefine_line|#define INIT_PROT_ATEL    0x80|PROT_ATEL
DECL|macro|INIT_PROT_ITALY
mdefine_line|#define INIT_PROT_ITALY   0x80|PROT_ITALY
DECL|macro|INIT_PROT_TWAN
mdefine_line|#define INIT_PROT_TWAN    0x80|PROT_TWAN
DECL|macro|INIT_PROT_AUSTRAL
mdefine_line|#define INIT_PROT_AUSTRAL 0x80|PROT_AUSTRAL
multiline_comment|/* -----------------------------------------------------------**&n;** The PROTOCOL_FEATURE_STRING in feature.h (included         **&n;** in prstart.sx and astart.sx) defines capabilities and      **&n;** features of the actual protocol code. It&squot;s used as a bit   **&n;** mask.                                                      **&n;** The following Bits are defined:                            **&n;** -----------------------------------------------------------*/
DECL|macro|PROTCAP_TELINDUS
mdefine_line|#define PROTCAP_TELINDUS  0x0001  /* Telindus Variant of protocol code   */
DECL|macro|PROTCAP_MANIF
mdefine_line|#define PROTCAP_MANIF     0x0002  /* Management interface implemented    */
DECL|macro|PROTCAP_V_42
mdefine_line|#define PROTCAP_V_42      0x0004  /* V42 implemented                     */
DECL|macro|PROTCAP_V90D
mdefine_line|#define PROTCAP_V90D      0x0008  /* V.90D (implies up to 384k DSP code) */
DECL|macro|PROTCAP_EXTD_FAX
mdefine_line|#define PROTCAP_EXTD_FAX  0x0010  /* Extended FAX (ECM, 2D, T6, Polling) */
DECL|macro|PROTCAP_FREE4
mdefine_line|#define PROTCAP_FREE4     0x0020  /* not used                            */
DECL|macro|PROTCAP_FREE5
mdefine_line|#define PROTCAP_FREE5     0x0040  /* not used                            */
DECL|macro|PROTCAP_FREE6
mdefine_line|#define PROTCAP_FREE6     0x0080  /* not used                            */
DECL|macro|PROTCAP_FREE7
mdefine_line|#define PROTCAP_FREE7     0x0100  /* not used                            */
DECL|macro|PROTCAP_FREE8
mdefine_line|#define PROTCAP_FREE8     0x0200  /* not used                            */
DECL|macro|PROTCAP_FREE9
mdefine_line|#define PROTCAP_FREE9     0x0400  /* not used                            */
DECL|macro|PROTCAP_FREE10
mdefine_line|#define PROTCAP_FREE10    0x0800  /* not used                            */
DECL|macro|PROTCAP_FREE11
mdefine_line|#define PROTCAP_FREE11    0x1000  /* not used                            */
DECL|macro|PROTCAP_FREE12
mdefine_line|#define PROTCAP_FREE12    0x2000  /* not used                            */
DECL|macro|PROTCAP_FREE13
mdefine_line|#define PROTCAP_FREE13    0x4000  /* not used                            */
DECL|macro|PROTCAP_EXTENSION
mdefine_line|#define PROTCAP_EXTENSION 0x8000  /* used for future extentions          */
eof
