multiline_comment|/*  &n; * ioctl defines for ethernet driver&n; *&n; * Copyright (c) 2001 Axis Communications AB&n; * &n; * Author: Mikael Starvik &n; *&n; */
macro_line|#ifndef _CRIS_ETHERNET_H
DECL|macro|_CRIS_ETHERNET_H
mdefine_line|#define _CRIS_ETHERNET_H
DECL|macro|SET_ETH_SPEED_AUTO
mdefine_line|#define SET_ETH_SPEED_AUTO      SIOCDEVPRIVATE          /* Auto neg speed */
DECL|macro|SET_ETH_SPEED_10
mdefine_line|#define SET_ETH_SPEED_10        SIOCDEVPRIVATE+1        /* 10 Mbps */
DECL|macro|SET_ETH_SPEED_100
mdefine_line|#define SET_ETH_SPEED_100       SIOCDEVPRIVATE+2        /* 100 Mbps. */
DECL|macro|SET_ETH_DUPLEX_AUTO
mdefine_line|#define SET_ETH_DUPLEX_AUTO     SIOCDEVPRIVATE+3        /* Auto neg duplex */
DECL|macro|SET_ETH_DUPLEX_HALF
mdefine_line|#define SET_ETH_DUPLEX_HALF     SIOCDEVPRIVATE+4        /* Full duplex */
DECL|macro|SET_ETH_DUPLEX_FULL
mdefine_line|#define SET_ETH_DUPLEX_FULL     SIOCDEVPRIVATE+5        /* Half duplex */
macro_line|#endif /* _CRIS_ETHERNET_H */
eof
