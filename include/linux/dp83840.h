multiline_comment|/*&n; * linux/dp83840.h: definitions for DP83840 MII-compatible transceivers&n; *&n; * Copyright (C) 1996, 1999 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef __LINUX_DP83840_H
DECL|macro|__LINUX_DP83840_H
mdefine_line|#define __LINUX_DP83840_H
macro_line|#include &lt;linux/mii.h&gt;
multiline_comment|/*&n; * Data sheets and programming docs for the DP83840 are available at&n; * from http://www.national.com/&n; *&n; * The DP83840 is capable of both 10 and 100Mbps ethernet, in both&n; * half and full duplex mode.  It also supports auto negotiation.&n; *&n; * But.... THIS THING IS A PAIN IN THE ASS TO PROGRAM!&n; * Debugging eeprom burnt code is more fun than programming this chip!&n; */
multiline_comment|/* First, the MII register numbers (actually DP83840 register numbers). */
DECL|macro|MII_CSCONFIG
mdefine_line|#define MII_CSCONFIG        0x17        /* CS configuration            */
multiline_comment|/* The Carrier Sense config register. */
DECL|macro|CSCONFIG_RESV1
mdefine_line|#define CSCONFIG_RESV1          0x0001  /* Unused...                   */
DECL|macro|CSCONFIG_LED4
mdefine_line|#define CSCONFIG_LED4           0x0002  /* Pin for full-dplx LED4      */
DECL|macro|CSCONFIG_LED1
mdefine_line|#define CSCONFIG_LED1           0x0004  /* Pin for conn-status LED1    */
DECL|macro|CSCONFIG_RESV2
mdefine_line|#define CSCONFIG_RESV2          0x0008  /* Unused...                   */
DECL|macro|CSCONFIG_TCVDISAB
mdefine_line|#define CSCONFIG_TCVDISAB       0x0010  /* Turns off the transceiver   */
DECL|macro|CSCONFIG_DFBYPASS
mdefine_line|#define CSCONFIG_DFBYPASS       0x0020  /* Bypass disconnect function  */
DECL|macro|CSCONFIG_GLFORCE
mdefine_line|#define CSCONFIG_GLFORCE        0x0040  /* Good link force for 100mbps */
DECL|macro|CSCONFIG_CLKTRISTATE
mdefine_line|#define CSCONFIG_CLKTRISTATE    0x0080  /* Tristate 25m clock          */
DECL|macro|CSCONFIG_RESV3
mdefine_line|#define CSCONFIG_RESV3          0x0700  /* Unused...                   */
DECL|macro|CSCONFIG_ENCODE
mdefine_line|#define CSCONFIG_ENCODE         0x0800  /* 1=MLT-3, 0=binary           */
DECL|macro|CSCONFIG_RENABLE
mdefine_line|#define CSCONFIG_RENABLE        0x1000  /* Repeater mode enable        */
DECL|macro|CSCONFIG_TCDISABLE
mdefine_line|#define CSCONFIG_TCDISABLE      0x2000  /* Disable timeout counter     */
DECL|macro|CSCONFIG_RESV4
mdefine_line|#define CSCONFIG_RESV4          0x4000  /* Unused...                   */
DECL|macro|CSCONFIG_NDISABLE
mdefine_line|#define CSCONFIG_NDISABLE       0x8000  /* Disable NRZI                */
macro_line|#endif /* __LINUX_DP83840_H */
eof
