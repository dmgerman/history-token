multiline_comment|/* $Id: envctrl.h,v 1.3 2000/11/03 00:37:40 davem Exp $&n; *&n; * envctrl.h: Definitions for access to the i2c environment&n; *            monitoring on Ultrasparc systems.&n; *&n; * Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)&n; * Copyright (C) 2000  Vinh Truong  (vinh.truong@eng.sun.com)&n; * VT - Add all ioctl commands and environment status definitions &n; * VT - Add application note &n; */
macro_line|#ifndef _SPARC64_ENVCTRL_H
DECL|macro|_SPARC64_ENVCTRL_H
mdefine_line|#define _SPARC64_ENVCTRL_H 1
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* Application note:&n; *&n; * The driver supports 4 operations: open(), close(), ioctl(), read()&n; * The device name is /dev/envctrl.&n; * Below is sample usage:&n; *&n; *&t;fd = open(&quot;/dev/envtrl&quot;, O_RDONLY);&n; *&t;if (ioctl(fd, ENVCTRL_READ_SHUTDOWN_TEMPERATURE, 0) &lt; 0)&n; *&t;&t;printf(&quot;error&bslash;n&quot;);&n; *&t;ret = read(fd, buf, 10);&n; *&t;close(fd);&n; *&n; * Notice in the case of cpu voltage and temperature, the default is&n; * cpu0.  If we need to know the info of cpu1, cpu2, cpu3, we need to&n; * pass in cpu number in ioctl() last parameter.  For example, to&n; * get the voltage of cpu2:&n; *&n; *&t;ioctlbuf[0] = 2;&n; *&t;if (ioctl(fd, ENVCTRL_READ_CPU_VOLTAGE, ioctlbuf) &lt; 0)&n; *&t;&t;printf(&quot;error&bslash;n&quot;);&n; *&t;ret = read(fd, buf, 10);&n; *&n; * All the return values are in ascii.  So check read return value&n; * and do appropriate conversions in your application.&n; */
multiline_comment|/* IOCTL commands */
multiline_comment|/* Note: these commands reflect possible monitor features.&n; * Some boards choose to support some of the features only.&n; */
DECL|macro|ENVCTRL_RD_CPU_TEMPERATURE
mdefine_line|#define ENVCTRL_RD_CPU_TEMPERATURE&t;_IOR(&squot;p&squot;, 0x40, int)
DECL|macro|ENVCTRL_RD_CPU_VOLTAGE
mdefine_line|#define ENVCTRL_RD_CPU_VOLTAGE&t;&t;_IOR(&squot;p&squot;, 0x41, int)
DECL|macro|ENVCTRL_RD_FAN_STATUS
mdefine_line|#define ENVCTRL_RD_FAN_STATUS&t;&t;_IOR(&squot;p&squot;, 0x42, int)
DECL|macro|ENVCTRL_RD_WARNING_TEMPERATURE
mdefine_line|#define ENVCTRL_RD_WARNING_TEMPERATURE&t;_IOR(&squot;p&squot;, 0x43, int)
DECL|macro|ENVCTRL_RD_SHUTDOWN_TEMPERATURE
mdefine_line|#define ENVCTRL_RD_SHUTDOWN_TEMPERATURE&t;_IOR(&squot;p&squot;, 0x44, int)
DECL|macro|ENVCTRL_RD_VOLTAGE_STATUS
mdefine_line|#define ENVCTRL_RD_VOLTAGE_STATUS&t;_IOR(&squot;p&squot;, 0x45, int)
DECL|macro|ENVCTRL_RD_SCSI_TEMPERATURE
mdefine_line|#define ENVCTRL_RD_SCSI_TEMPERATURE&t;_IOR(&squot;p&squot;, 0x46, int)
DECL|macro|ENVCTRL_RD_ETHERNET_TEMPERATURE
mdefine_line|#define ENVCTRL_RD_ETHERNET_TEMPERATURE&t;_IOR(&squot;p&squot;, 0x47, int)
DECL|macro|ENVCTRL_RD_MTHRBD_TEMPERATURE
mdefine_line|#define ENVCTRL_RD_MTHRBD_TEMPERATURE&t;_IOR(&squot;p&squot;, 0x48, int)
DECL|macro|ENVCTRL_RD_GLOBALADDRESS
mdefine_line|#define ENVCTRL_RD_GLOBALADDRESS&t;_IOR(&squot;p&squot;, 0x49, int)
multiline_comment|/* Read return values for a voltage status request. */
DECL|macro|ENVCTRL_VOLTAGE_POWERSUPPLY_GOOD
mdefine_line|#define ENVCTRL_VOLTAGE_POWERSUPPLY_GOOD&t;0x01
DECL|macro|ENVCTRL_VOLTAGE_BAD
mdefine_line|#define ENVCTRL_VOLTAGE_BAD&t;&t;&t;0x02
DECL|macro|ENVCTRL_POWERSUPPLY_BAD
mdefine_line|#define ENVCTRL_POWERSUPPLY_BAD&t;&t;&t;0x03
DECL|macro|ENVCTRL_VOLTAGE_POWERSUPPLY_BAD
mdefine_line|#define ENVCTRL_VOLTAGE_POWERSUPPLY_BAD&t;&t;0x04
multiline_comment|/* Read return values for a fan status request.&n; * A failure match means either the fan fails or&n; * the fan is not connected.  Some boards have optional&n; * connectors to connect extra fans.&n; *&n; * There are maximum 8 monitor fans.  Some are cpu fans&n; * some are system fans.  The mask below only indicates&n; * fan by order number.&n; * Below is a sample application:&n; *&n; *&t;if (ioctl(fd, ENVCTRL_READ_FAN_STATUS, 0) &lt; 0) {&n; *&t;&t;printf(&quot;ioctl fan failed&bslash;n&quot;);&n; *&t;}&n; *&t;if (read(fd, rslt, 1) &lt;= 0) {&n; *&t;&t;printf(&quot;error or fan not monitored&bslash;n&quot;);&n; *&t;} else {&n; *&t;&t;if (rslt[0] == ENVCTRL_ALL_FANS_GOOD) {&n; *&t;&t;&t;printf(&quot;all fans good&bslash;n&quot;);&n; *&t;} else if (rslt[0] == ENVCTRL_ALL_FANS_BAD) {&n; *&t;&t;printf(&quot;all fans bad&bslash;n&quot;);&n; *&t;} else {&n; *&t;&t;if (rslt[0] &amp; ENVCTRL_FAN0_FAILURE_MASK) {&n; *&t;&t;&t;printf(&quot;fan 0 failed or not connected&bslash;n&quot;);&n; *&t;}&n; *&t;......&n; */
DECL|macro|ENVCTRL_ALL_FANS_GOOD
mdefine_line|#define ENVCTRL_ALL_FANS_GOOD&t;&t;&t;0x00
DECL|macro|ENVCTRL_FAN0_FAILURE_MASK
mdefine_line|#define ENVCTRL_FAN0_FAILURE_MASK&t;&t;0x01
DECL|macro|ENVCTRL_FAN1_FAILURE_MASK
mdefine_line|#define ENVCTRL_FAN1_FAILURE_MASK&t;&t;0x02
DECL|macro|ENVCTRL_FAN2_FAILURE_MASK
mdefine_line|#define ENVCTRL_FAN2_FAILURE_MASK&t;&t;0x04
DECL|macro|ENVCTRL_FAN3_FAILURE_MASK
mdefine_line|#define ENVCTRL_FAN3_FAILURE_MASK&t;&t;0x08
DECL|macro|ENVCTRL_FAN4_FAILURE_MASK
mdefine_line|#define ENVCTRL_FAN4_FAILURE_MASK&t;&t;0x10
DECL|macro|ENVCTRL_FAN5_FAILURE_MASK
mdefine_line|#define ENVCTRL_FAN5_FAILURE_MASK&t;&t;0x20
DECL|macro|ENVCTRL_FAN6_FAILURE_MASK
mdefine_line|#define ENVCTRL_FAN6_FAILURE_MASK&t;&t;0x40
DECL|macro|ENVCTRL_FAN7_FAILURE_MASK
mdefine_line|#define ENVCTRL_FAN7_FAILURE_MASK&t;&t;0x80
DECL|macro|ENVCTRL_ALL_FANS_BAD
mdefine_line|#define ENVCTRL_ALL_FANS_BAD &t;&t;&t;0xFF
macro_line|#endif /* !(_SPARC64_ENVCTRL_H) */
eof
