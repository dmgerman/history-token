multiline_comment|/*&n; * ciscode.h -- Definitions for bulk memory services&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * (C) 1999&t;&t;David A. Hinds&n; */
macro_line|#ifndef _LINUX_CISCODE_H
DECL|macro|_LINUX_CISCODE_H
mdefine_line|#define _LINUX_CISCODE_H
multiline_comment|/* Manufacturer and Product ID codes */
DECL|macro|MANFID_3COM
mdefine_line|#define MANFID_3COM&t;&t;&t;0x0101
DECL|macro|PRODID_3COM_3CXEM556
mdefine_line|#define PRODID_3COM_3CXEM556&t;&t;0x0035
DECL|macro|PRODID_3COM_3CCFEM556
mdefine_line|#define PRODID_3COM_3CCFEM556&t;&t;0x0556
DECL|macro|PRODID_3COM_3C562
mdefine_line|#define PRODID_3COM_3C562&t;&t;0x0562
DECL|macro|MANFID_ACCTON
mdefine_line|#define MANFID_ACCTON&t;&t;&t;0x01bf
DECL|macro|PRODID_ACCTON_EN2226
mdefine_line|#define PRODID_ACCTON_EN2226&t;&t;0x010a
DECL|macro|MANFID_ADAPTEC
mdefine_line|#define MANFID_ADAPTEC&t;&t;&t;0x012f
DECL|macro|PRODID_ADAPTEC_SCSI
mdefine_line|#define PRODID_ADAPTEC_SCSI&t;&t;0x0001
DECL|macro|MANFID_ATT
mdefine_line|#define MANFID_ATT&t;&t;&t;0xffff
DECL|macro|PRODID_ATT_KIT
mdefine_line|#define PRODID_ATT_KIT&t;&t;&t;0x0100
DECL|macro|MANFID_CONTEC
mdefine_line|#define MANFID_CONTEC&t;&t;&t;0xc001
DECL|macro|MANFID_FUJITSU
mdefine_line|#define MANFID_FUJITSU&t;&t;&t;0x0004
DECL|macro|PRODID_FUJITSU_MBH10302
mdefine_line|#define PRODID_FUJITSU_MBH10302&t;&t;0x0004
DECL|macro|PRODID_FUJITSU_MBH10304
mdefine_line|#define PRODID_FUJITSU_MBH10304&t;&t;0x1003
DECL|macro|PRODID_FUJITSU_LA501
mdefine_line|#define PRODID_FUJITSU_LA501&t;&t;0x2000
DECL|macro|MANFID_IBM
mdefine_line|#define MANFID_IBM&t;&t;&t;0x00a4
DECL|macro|PRODID_IBM_HOME_AND_AWAY
mdefine_line|#define PRODID_IBM_HOME_AND_AWAY&t;0x002e
DECL|macro|MANFID_INTEL
mdefine_line|#define MANFID_INTEL&t;&t;&t;0x0089
DECL|macro|PRODID_INTEL_DUAL_RS232
mdefine_line|#define PRODID_INTEL_DUAL_RS232&t;&t;0x0301
DECL|macro|PRODID_INTEL_2PLUS
mdefine_line|#define PRODID_INTEL_2PLUS&t;&t;0x8422
DECL|macro|MANFID_KME
mdefine_line|#define MANFID_KME&t;&t;&t;0x0032
DECL|macro|PRODID_KME_KXLC005_A
mdefine_line|#define PRODID_KME_KXLC005_A&t;&t;0x0704
DECL|macro|PRODID_KME_KXLC005_B
mdefine_line|#define PRODID_KME_KXLC005_B&t;&t;0x2904
DECL|macro|MANFID_LINKSYS
mdefine_line|#define MANFID_LINKSYS&t;&t;&t;0x0143
DECL|macro|PRODID_LINKSYS_PCMLM28
mdefine_line|#define PRODID_LINKSYS_PCMLM28&t;&t;0xc0ab
DECL|macro|PRODID_LINKSYS_3400
mdefine_line|#define PRODID_LINKSYS_3400&t;&t;0x3341
DECL|macro|MANFID_MEGAHERTZ
mdefine_line|#define MANFID_MEGAHERTZ&t;&t;0x0102
DECL|macro|PRODID_MEGAHERTZ_VARIOUS
mdefine_line|#define PRODID_MEGAHERTZ_VARIOUS&t;0x0000
DECL|macro|PRODID_MEGAHERTZ_EM3288
mdefine_line|#define PRODID_MEGAHERTZ_EM3288&t;&t;0x0006
DECL|macro|MANFID_MACNICA
mdefine_line|#define MANFID_MACNICA&t;&t;&t;0xc00b
DECL|macro|MANFID_MOTOROLA
mdefine_line|#define MANFID_MOTOROLA&t;&t;&t;0x0109
DECL|macro|PRODID_MOTOROLA_MARINER
mdefine_line|#define PRODID_MOTOROLA_MARINER&t;&t;0x0501
DECL|macro|MANFID_NATINST
mdefine_line|#define MANFID_NATINST&t;&t;&t;0x010b
DECL|macro|PRODID_NATINST_QUAD_RS232
mdefine_line|#define PRODID_NATINST_QUAD_RS232&t;0xd180
DECL|macro|MANFID_NEW_MEDIA
mdefine_line|#define MANFID_NEW_MEDIA&t;&t;0x0057
DECL|macro|MANFID_NOKIA
mdefine_line|#define MANFID_NOKIA&t;&t;&t;0x0124
DECL|macro|PRODID_NOKIA_CARDPHONE
mdefine_line|#define PRODID_NOKIA_CARDPHONE&t;&t;0x0900
DECL|macro|MANFID_OLICOM
mdefine_line|#define MANFID_OLICOM&t;&t;&t;0x0121
DECL|macro|PRODID_OLICOM_OC2231
mdefine_line|#define PRODID_OLICOM_OC2231&t;&t;0x3122
DECL|macro|PRODID_OLICOM_OC2232
mdefine_line|#define PRODID_OLICOM_OC2232&t;&t;0x3222
DECL|macro|MANFID_OMEGA
mdefine_line|#define MANFID_OMEGA&t;&t;&t;0x0137
DECL|macro|PRODID_OMEGA_QSP_100
mdefine_line|#define PRODID_OMEGA_QSP_100&t;&t;0x0025
DECL|macro|MANFID_OSITECH
mdefine_line|#define MANFID_OSITECH&t;&t;&t;0x0140
DECL|macro|PRODID_OSITECH_JACK_144
mdefine_line|#define PRODID_OSITECH_JACK_144&t;&t;0x0001
DECL|macro|PRODID_OSITECH_JACK_288
mdefine_line|#define PRODID_OSITECH_JACK_288&t;&t;0x0002
DECL|macro|PRODID_OSITECH_JACK_336
mdefine_line|#define PRODID_OSITECH_JACK_336&t;&t;0x0007
DECL|macro|PRODID_OSITECH_SEVEN
mdefine_line|#define PRODID_OSITECH_SEVEN&t;&t;0x0008
DECL|macro|MANFID_OXSEMI
mdefine_line|#define MANFID_OXSEMI&t;&t;&t;0x0279
DECL|macro|MANFID_PIONEER
mdefine_line|#define MANFID_PIONEER&t;&t;&t;0x000b
DECL|macro|MANFID_PSION
mdefine_line|#define MANFID_PSION&t;&t;&t;0x016c
DECL|macro|PRODID_PSION_NET100
mdefine_line|#define PRODID_PSION_NET100&t;&t;0x0023
DECL|macro|MANFID_QUATECH
mdefine_line|#define MANFID_QUATECH&t;&t;&t;0x0137
DECL|macro|PRODID_QUATECH_SPP100
mdefine_line|#define PRODID_QUATECH_SPP100&t;&t;0x0003
DECL|macro|PRODID_QUATECH_DUAL_RS232
mdefine_line|#define PRODID_QUATECH_DUAL_RS232&t;0x0012
DECL|macro|PRODID_QUATECH_DUAL_RS232_D1
mdefine_line|#define PRODID_QUATECH_DUAL_RS232_D1&t;0x0007
DECL|macro|PRODID_QUATECH_DUAL_RS232_D2
mdefine_line|#define PRODID_QUATECH_DUAL_RS232_D2&t;0x0052
DECL|macro|PRODID_QUATECH_QUAD_RS232
mdefine_line|#define PRODID_QUATECH_QUAD_RS232&t;0x001b
DECL|macro|PRODID_QUATECH_DUAL_RS422
mdefine_line|#define PRODID_QUATECH_DUAL_RS422&t;0x000e
DECL|macro|PRODID_QUATECH_QUAD_RS422
mdefine_line|#define PRODID_QUATECH_QUAD_RS422&t;0x0045
DECL|macro|MANFID_SMC
mdefine_line|#define MANFID_SMC&t;&t;&t;0x0108
DECL|macro|PRODID_SMC_ETHER
mdefine_line|#define PRODID_SMC_ETHER&t;&t;0x0105
DECL|macro|MANFID_SOCKET
mdefine_line|#define MANFID_SOCKET&t;&t;&t;0x0104
DECL|macro|PRODID_SOCKET_DUAL_RS232
mdefine_line|#define PRODID_SOCKET_DUAL_RS232&t;0x0006
DECL|macro|PRODID_SOCKET_EIO
mdefine_line|#define PRODID_SOCKET_EIO&t;&t;0x000a
DECL|macro|PRODID_SOCKET_LPE
mdefine_line|#define PRODID_SOCKET_LPE&t;&t;0x000d
DECL|macro|PRODID_SOCKET_LPE_CF
mdefine_line|#define PRODID_SOCKET_LPE_CF&t;&t;0x0075
DECL|macro|MANFID_SUNDISK
mdefine_line|#define MANFID_SUNDISK&t;&t;&t;0x0045
DECL|macro|MANFID_TDK
mdefine_line|#define MANFID_TDK&t;&t;&t;0x0105
DECL|macro|PRODID_TDK_CF010
mdefine_line|#define PRODID_TDK_CF010&t;&t;0x0900
DECL|macro|PRODID_TDK_GN3410
mdefine_line|#define PRODID_TDK_GN3410&t;&t;0x4815
DECL|macro|MANFID_TOSHIBA
mdefine_line|#define MANFID_TOSHIBA&t;&t;&t;0x0098
DECL|macro|MANFID_UNGERMANN
mdefine_line|#define MANFID_UNGERMANN 0x02c0
DECL|macro|MANFID_XIRCOM
mdefine_line|#define MANFID_XIRCOM&t;&t;&t;0x0105
macro_line|#endif /* _LINUX_CISCODE_H */
eof
