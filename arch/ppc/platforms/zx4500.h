multiline_comment|/* * arch/ppc/platforms/zx4500.h&n; * &n; * Board setup routines for Znyx ZX4500 cPCI board.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * Copyright 2000, 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef&t;__PPC_PLATFORMS_ZX4500_H_
DECL|macro|__PPC_PLATFORMS_ZX4500_H_
mdefine_line|#define&t;__PPC_PLATFORMS_ZX4500_H_
multiline_comment|/*&n; * Define the addresses of CPLD registers in CLPD area.&n; */
DECL|macro|ZX4500_CPLD_BOARD_ID
mdefine_line|#define&t;ZX4500_CPLD_BOARD_ID&t;&t;0xff800001
DECL|macro|ZX4500_CPLD_REV
mdefine_line|#define&t;ZX4500_CPLD_REV&t;&t;&t;0xff800002
DECL|macro|ZX4500_CPLD_RESET
mdefine_line|#define&t;ZX4500_CPLD_RESET&t;&t;0xff800011
DECL|macro|ZX4500_CPLD_PHY1
mdefine_line|#define&t;ZX4500_CPLD_PHY1&t;&t;0xff800014
DECL|macro|ZX4500_CPLD_PHY2
mdefine_line|#define&t;ZX4500_CPLD_PHY2&t;&t;0xff800015
DECL|macro|ZX4500_CPLD_PHY3
mdefine_line|#define&t;ZX4500_CPLD_PHY3&t;&t;0xff800016
DECL|macro|ZX4500_CPLD_SYSCTL
mdefine_line|#define&t;ZX4500_CPLD_SYSCTL&t;&t;0xff800017
DECL|macro|ZX4500_CPLD_EXT_FLASH
mdefine_line|#define&t;ZX4500_CPLD_EXT_FLASH&t;&t;0xff800018
DECL|macro|ZX4500_CPLD_DUAL1
mdefine_line|#define&t;ZX4500_CPLD_DUAL1&t;&t;0xff800019
DECL|macro|ZX4500_CPLD_DUAL2
mdefine_line|#define&t;ZX4500_CPLD_DUAL2&t;&t;0xff80001A
DECL|macro|ZX4500_CPLD_STATUS
mdefine_line|#define&t;ZX4500_CPLD_STATUS&t;&t;0xff800030
DECL|macro|ZX4500_CPLD_STREAM
mdefine_line|#define&t;ZX4500_CPLD_STREAM&t;&t;0xff800032
DECL|macro|ZX4500_CPLD_PHY1_LED
mdefine_line|#define&t;ZX4500_CPLD_PHY1_LED&t;&t;0xff800034
DECL|macro|ZX4500_CPLD_PHY2_LED
mdefine_line|#define&t;ZX4500_CPLD_PHY2_LED&t;&t;0xff800035
DECL|macro|ZX4500_CPLD_PHY3_LED
mdefine_line|#define&t;ZX4500_CPLD_PHY3_LED&t;&t;0xff800036
DECL|macro|ZX4500_CPLD_PHY1_LNK
mdefine_line|#define&t;ZX4500_CPLD_PHY1_LNK&t;&t;0xff80003C
DECL|macro|ZX4500_CPLD_PHY2_LNK
mdefine_line|#define&t;ZX4500_CPLD_PHY2_LNK&t;&t;0xff80003D
DECL|macro|ZX4500_CPLD_PHY3_LNK
mdefine_line|#define&t;ZX4500_CPLD_PHY3_LNK&t;&t;0xff80003E
DECL|macro|ZX4500_CPLD_RESET_SOFT
mdefine_line|#define&t;ZX4500_CPLD_RESET_SOFT&t;&t;0x01&t;/* Soft Reset */
DECL|macro|ZX4500_CPLD_RESET_XBUS
mdefine_line|#define&t;ZX4500_CPLD_RESET_XBUS&t;&t;0x40&t;/* Reset entire board */
DECL|macro|ZX4500_CPLD_SYSCTL_PMC
mdefine_line|#define&t;ZX4500_CPLD_SYSCTL_PMC&t;&t;0x01&t;/* Enable INTA/B/C/D from PMC */
DECL|macro|ZX4500_CPLD_SYSCTL_BCM
mdefine_line|#define&t;ZX4500_CPLD_SYSCTL_BCM&t;&t;0x04&t;/* Enable INTA from BCM */
DECL|macro|ZX4500_CPLD_SYSCTL_SINTA
mdefine_line|#define&t;ZX4500_CPLD_SYSCTL_SINTA&t;0x08&t;/* Enable SINTA from 21554 */
DECL|macro|ZX4500_CPLD_SYSCTL_WD
mdefine_line|#define&t;ZX4500_CPLD_SYSCTL_WD&t;&t;0x20&t;/* Enable Watchdog Timer */
DECL|macro|ZX4500_CPLD_SYSCTL_PMC_TRI
mdefine_line|#define&t;ZX4500_CPLD_SYSCTL_PMC_TRI&t;0x80&t;/* Tri-state PMC EREADY */
DECL|macro|ZX4500_CPLD_DUAL2_LED_PULL
mdefine_line|#define&t;ZX4500_CPLD_DUAL2_LED_PULL&t;0x01&t;/* Pull LED */
DECL|macro|ZX4500_CPLD_DUAL2_LED_EXT_FAULT
mdefine_line|#define&t;ZX4500_CPLD_DUAL2_LED_EXT_FAULT&t;0x02&t;/* External Fault LED */
DECL|macro|ZX4500_CPLD_DUAL2_LED_INT_FAULT
mdefine_line|#define&t;ZX4500_CPLD_DUAL2_LED_INT_FAULT&t;0x04&t;/* Internal Fault LED */
DECL|macro|ZX4500_CPLD_DUAL2_LED_OK
mdefine_line|#define&t;ZX4500_CPLD_DUAL2_LED_OK&t;0x08&t;/* OK LED */
DECL|macro|ZX4500_CPLD_DUAL2_LED_CLK
mdefine_line|#define&t;ZX4500_CPLD_DUAL2_LED_CLK&t;0x10&t;/* CLK LED */
multiline_comment|/*&n; * Defines related to boot string stored in flash.&n; */
DECL|macro|ZX4500_BOOT_STRING_ADDR
mdefine_line|#define&t;ZX4500_BOOT_STRING_ADDR&t;&t;0xfff7f000
DECL|macro|ZX4500_BOOT_STRING_LEN
mdefine_line|#define&t;ZX4500_BOOT_STRING_LEN&t;&t;80
multiline_comment|/*&n; * Define the IDSEL that the PCI bus side of the 8240 is connected to.&n; * This IDSEL must not be selected from the 8240 processor side.&n; */
DECL|macro|ZX4500_HOST_BRIDGE_IDSEL
mdefine_line|#define&t;ZX4500_HOST_BRIDGE_IDSEL&t;20
r_void
id|zx4500_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;/* __PPC_PLATFORMS_ZX4500_H_ */
eof
