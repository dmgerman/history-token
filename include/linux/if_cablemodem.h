macro_line|#ifndef _LINUX_CABLEMODEM_H_
DECL|macro|_LINUX_CABLEMODEM_H_
mdefine_line|#define _LINUX_CABLEMODEM_H_
multiline_comment|/*&n; *&t;&t;Author: Franco Venturi &lt;fventuri@mediaone.net&gt;&n; *&t;&t;Copyright 1998 Franco Venturi&n; *&n; *&t;&t;This program is free software; you can redistribute it&n; *&t;&t;and/or  modify it under  the terms of  the GNU General&n; *&t;&t;Public  License as  published  by  the  Free  Software&n; *&t;&t;Foundation;  either  version 2 of the License, or  (at&n; *&t;&t;your option) any later version.&n; */
multiline_comment|/* some useful defines for sb1000.c e cmconfig.c - fv */
DECL|macro|SIOCGCMSTATS
mdefine_line|#define SIOCGCMSTATS&t;&t;SIOCDEVPRIVATE+0&t;/* get cable modem stats */
DECL|macro|SIOCGCMFIRMWARE
mdefine_line|#define SIOCGCMFIRMWARE&t;&t;SIOCDEVPRIVATE+1&t;/* get cm firmware version */
DECL|macro|SIOCGCMFREQUENCY
mdefine_line|#define SIOCGCMFREQUENCY&t;SIOCDEVPRIVATE+2&t;/* get cable modem frequency */
DECL|macro|SIOCSCMFREQUENCY
mdefine_line|#define SIOCSCMFREQUENCY&t;SIOCDEVPRIVATE+3&t;/* set cable modem frequency */
DECL|macro|SIOCGCMPIDS
mdefine_line|#define SIOCGCMPIDS&t;&t;&t;SIOCDEVPRIVATE+4&t;/* get cable modem PIDs */
DECL|macro|SIOCSCMPIDS
mdefine_line|#define SIOCSCMPIDS&t;&t;&t;SIOCDEVPRIVATE+5&t;/* set cable modem PIDs */
macro_line|#endif
eof
