multiline_comment|/* $Id$&n; *&n; * apc - Driver definitions for power management functions&n; * of Aurora Personality Chip (APC) on SPARCstation-4/5 and &n; * derivatives&n; *&n; * Copyright (c) 2001 Eric Brower (ebrower@usa.net)&n; *&n; */
macro_line|#ifndef _SPARC_APC_H
DECL|macro|_SPARC_APC_H
mdefine_line|#define _SPARC_APC_H
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|APC_IOC
mdefine_line|#define APC_IOC&t;&squot;A&squot;
DECL|macro|APCIOCGFANCTL
mdefine_line|#define APCIOCGFANCTL _IOR(APC_IOC, 0x00, int)&t;/* Get fan speed&t;*/
DECL|macro|APCIOCSFANCTL
mdefine_line|#define APCIOCSFANCTL _IOW(APC_IOC, 0x01, int)&t;/* Set fan speed&t;*/
DECL|macro|APCIOCGCPWR
mdefine_line|#define APCIOCGCPWR   _IOR(APC_IOC, 0x02, int)&t;/* Get CPOWER state&t;*/
DECL|macro|APCIOCSCPWR
mdefine_line|#define APCIOCSCPWR   _IOW(APC_IOC, 0x03, int)&t;/* Set CPOWER state&t;*/
DECL|macro|APCIOCGBPORT
mdefine_line|#define APCIOCGBPORT   _IOR(APC_IOC, 0x04, int)&t;/* Get BPORT state &t;*/
DECL|macro|APCIOCSBPORT
mdefine_line|#define APCIOCSBPORT   _IOW(APC_IOC, 0x05, int)&t;/* Set BPORT state&t;*/
multiline_comment|/*&n; * Register offsets&n; */
DECL|macro|APC_IDLE_REG
mdefine_line|#define APC_IDLE_REG&t;0x00
DECL|macro|APC_FANCTL_REG
mdefine_line|#define APC_FANCTL_REG&t;0x20
DECL|macro|APC_CPOWER_REG
mdefine_line|#define APC_CPOWER_REG&t;0x24
DECL|macro|APC_BPORT_REG
mdefine_line|#define APC_BPORT_REG&t;0x30
DECL|macro|APC_REGMASK
mdefine_line|#define APC_REGMASK&t;&t;0x01
DECL|macro|APC_BPMASK
mdefine_line|#define APC_BPMASK&t;&t;0x03
multiline_comment|/*&n; * IDLE - CPU standby values (set to initiate standby)&n; */
DECL|macro|APC_IDLE_ON
mdefine_line|#define APC_IDLE_ON&t;&t;0x01
multiline_comment|/*&n; * FANCTL - Fan speed control state values&n; */
DECL|macro|APC_FANCTL_HI
mdefine_line|#define APC_FANCTL_HI&t;0x00&t;/* Fan speed high&t;*/
DECL|macro|APC_FANCTL_LO
mdefine_line|#define APC_FANCTL_LO&t;0x01&t;/* Fan speed low&t;*/
multiline_comment|/*&n; * CPWR - Convenience power outlet state values &n; */
DECL|macro|APC_CPOWER_ON
mdefine_line|#define APC_CPOWER_ON&t;0x00&t;/* Conv power on&t;*/
DECL|macro|APC_CPOWER_OFF
mdefine_line|#define APC_CPOWER_OFF&t;0x01&t;/* Conv power off&t;*/
multiline_comment|/*&n; * BPA/BPB - Read-Write &quot;Bit Ports&quot; state values (reset to 0 at power-on)&n; *&n; * WARNING: Internal usage of bit ports is platform dependent--&n; * don&squot;t modify BPORT settings unless you know what you are doing.&n; * &n; * On SS5 BPA seems to toggle onboard ethernet loopback... -E&n; */
DECL|macro|APC_BPORT_A
mdefine_line|#define APC_BPORT_A&t;&t;0x01&t;/* Bit Port A&t;&t;*/
DECL|macro|APC_BPORT_B
mdefine_line|#define APC_BPORT_B&t;&t;0x02&t;/* Bit Port B&t;&t;*/
macro_line|#endif /* !(_SPARC_APC_H) */
eof
