/******************************************************************************
 *
 * Copyright(c) 2016 - 2017 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 ******************************************************************************/

#include "halmac_pwr_seq_8822b.h"

#if HALMAC_8822B_SUPPORT

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_CARDEMU_TO_ACT[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0x0012, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), 0}, /*SWR OCP = SWR OCP = 010 1382.40*/
	{0x0012, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /*SWR OCP = 010 1382.40 */
	{0x0020, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK | HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /*0x20[0] = 1b'1 enable LDOA12 MACRO block for all interface*/
	{0x0001, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK | HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_DELAY, 1, HALMAC_PWRSEQ_DELAY_MS}, /*Delay 1ms*/
	{0x0000, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK | HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(5), 0}, /*0x00[5] = 1b'0 release analog Ips to digital ,1:isolation*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, (BIT(4) | BIT(3) | BIT(2)), 0}, /* disable SW LPS 0x04[10]=0 and WLSUS_EN 0x04[12:11]=0*/
	{0x0075, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /* Disable USB suspend */
	{0x0006, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, BIT(1), BIT(1)}, /* wait till 0x04[17] = 1    power ready*/
	{0x0075, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), 0}, /* Enable USB suspend */
	{0xFF1A, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0}, /*0xFF1A = 0 to release resume signals*/
	{0x0006, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /* release WLON reset  0x04[16]=1*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(7), 0}, /* disable HWPDN 0x04[15]=0*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, (BIT(4) | BIT(3)), 0}, /* disable WL suspend*/
	{0x10C3, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)},  /*Close IO wraper time out for FW read 0xEA problem*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /* polling until return 0*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, BIT(0), 0},
	{0x0020, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3), BIT(3)}, /*Enable XTAL_CLK*/
	{0x10A8, HALMAC_PWR_CUT_C_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0},/*NFC pad enabled*/
	{0x10A9, HALMAC_PWR_CUT_C_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xef},/*NFC pad enabled*/
	{0x10AA, HALMAC_PWR_CUT_C_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x0c},/*NFC pad enabled*/
	{0x0068, HALMAC_PWR_CUT_C_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(4), BIT(4)}, /*SDIO pad power down disabled*/
	{0x0029, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xF9}, /*PLL seting*/
	{0x0024, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(2), 0}, /*CH13與5G部分CH TX EVM的改善*/
	{0x0074, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(5), BIT(5)}, /*PCIE WAKE# enabled*/
	{0x00AF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(5), BIT(5)}, /*解BT 160M spur*/
	{0x010C, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /*提高DMA對USB的priorityr*/
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_ACT_TO_CARDEMU[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0x0003, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(2), 0}, /*0x02[10] = 0 Disable MCU Core*/
	{0x0093, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3), 0}, /*LPS option 0x93[3]=0 , SWR PFM*/
	{0x001F, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0}, /*0x1F[7:0] = 0 turn off RF*/
	{0x00EF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0}, /*0xEF[7:0] = 0 turn off RF*/
	{0xFF1A, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x30}, /*0xFF1A = 0x30 to block resume signals*/
	{0x0049, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), 0}, /*Enable rising edge triggering interrupt*/
	{0x0006, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /* release WLON reset  0x04[16]=1*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), 0}, /* Whole BB is reset */
	{0x10C3, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), 0},  /*Open IO wraper time out for FW read 0xEA problem*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), BIT(1)}, /*0x04[9] = 1 turn off MAC by HW state machine*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, BIT(1), 0}, /*wait till 0x04[9] = 0 polling until return 0 to disable*/
	{0x0020, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3), 0}, /* XTAL_CLK gated*/
	{0x0000, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK | HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(5), BIT(5)}, /*0x00[5] = 1b'1 analog Ips to digital ,1:isolation*/
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_CARDEMU_TO_SUS[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(4) | BIT(3), (BIT(4) | BIT(3))}, /*0x04[12:11] = 2b'11 enable WL suspend for PCIe*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK | HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3) | BIT(4), BIT(3)}, /*0x04[12:11] = 2b'01 enable WL suspend*/
	{0x0007, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x20}, /*0x07[7:0] = 0x20 SDIO SOP option to disable BG/MB/ACK/SWR*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3) | BIT(4), BIT(3) | BIT(4)}, /*0x04[12:11] = 2b'11 enable WL suspend for PCIe*/
	{0x0086, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /*Set SDIO suspend local register*/
	{0x0086, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_POLLING, BIT(1), 0}, /*wait power state to suspend*/
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_SUS_TO_CARDEMU[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0xFF0A, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0},
	{0xFF0B, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0},
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3) | BIT(7), 0}, /*clear suspend enable and power down enable*/
	{0x0086, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_WRITE, BIT(0), 0}, /*Set SDIO suspend local register*/
	{0x0086, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_POLLING, BIT(1), BIT(1)}, /*wait power state to suspend*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3) | BIT(4), 0}, /*0x04[12:11] = 2b'01enable WL suspend*/
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_CARDEMU_TO_CARDDIS[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(7), BIT(7)}, /*suspend enable and power down enable*/
	{0x0007, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK | HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x20}, /*0x07=0x20 , SOP option to disable BG/MB*/
	{0x0067, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(5), 0}, /*0x67[5]=0 , BIT_PAPE_WLBT_SEL*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK | HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3) | BIT(4), BIT(3)}, /*0x04[12:11] = 2b'01 enable WL suspend*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(2), BIT(2)}, /*0x04[10] = 1, enable SW LPS*/
	{0x004A, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), 0}, /*0x48[16] = 0 to disable GPIO9 as EXT WAKEUP*/
	{0x0067, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(5), 0 }, /* 0: BT PAPE control ; 1: WL BB LNAON control*/
	{0x0067, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(4), 0 }, /* 0: BT GPIO[11:10] control  ; 1: WL BB LNAON control*/
	{0x004F, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), 0 }, /* 0: BT Control*/
	{0x0067, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), 0 }, /* turn off BT_3DD_SYNC_B and BT_GPIO[18] */
	{0x0046, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(6), BIT(6) }, /* GPIO[6] : Output mode*/
	{0x0067, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(2), 0 }, /* turn off BT_GPIO[16] */
	{0x0046, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(7), BIT(7) }, /* GPIO[7] : Output mode*/
	{0x0062, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(4), BIT(4) }, /* GPIO[12] : Output mode */
	{0x0081, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(7)| BIT(6), 0}, /*0x80[15]clean fw init ready bit*/
	{0x0086, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /*Set SDIO suspend local register*/
	{0x0086, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_POLLING, BIT(1), 0}, /*wait power state to suspend*/
	{0x0090, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK | HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), 0}, /*0x90[1]=0 , disable 32k clock*/
	{0x0044, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_WRITE, 0xFF, 0}, /*0x90[1]=0 , disable 32k clock by indirect access*/
	{0x0040, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_WRITE, 0xFF, 0x90}, /*0x90[1]=0 , disable 32k clock by indirect access*/
	{0x0041, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_WRITE, 0xFF, 0x00}, /*0x90[1]=0 , disable 32k clock by indirect access*/
	{0x0042, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_WRITE, 0xFF, 0x04}, /*0x90[1]=0 , disable 32k clock by indirect access*/
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_CARDDIS_TO_CARDEMU[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0x0086, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_WRITE, BIT(0), 0}, /*Set SDIO suspend local register*/
	{0x0086, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_POLLING, BIT(1), BIT(1)}, /*wait power state to suspend*/
	{0x004A, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), 0}, /*0x48[16] = 0 to disable GPIO9 as EXT WAKEUP*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3) | BIT(4) | BIT(7), 0}, /*clear suspend enable and power down enable*/
	{0x0300, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0},
	{0x0301, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0}, /*PCIe DMA start*/
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_CARDEMU_TO_PDN[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0x0007, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK | HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x20}, /*0x07[7:0] = 0x20 SOP option to disable BG/MB/ACK/SWR*/
	{0x0006, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), 0}, /* 0x04[16] = 0*/
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(7), BIT(7)}, /* 0x04[15] = 1*/
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_PDN_TO_CARDEMU[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0x0005, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(7), 0},
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_ACT_TO_LPS[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0x0101, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(2), BIT(2)}, /*Enable 32k calibration and thermal meter*/
	{0x0199, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3), BIT(3)}, /*Register write data of 32K calibration*/
	{0x019B, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(7), BIT(7)}, /*Enable 32k calibration reg write*/
	{0x1138, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0) | BIT(1), BIT(0) | BIT(1)}, /*set RPWM IMR*/
	{0x0194, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /* enable 32K CLK*/
	{0x0093, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xDE}, /* PCIE LPS Option*/
	{0x0092, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x60}, /* PCIE LPS Option*/
	{0x0093, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x9B}, /* USB LPS Option*/
	{0x0092, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x60}, /* USB LPS Option*/
	{0x0093, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xA}, /* SDIO LPS Option*/
	{0x0092, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x60}, /* SDIO LPS Option*/
	{0x0090, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), BIT(1)}, /* enable reg use 32K CLK*/
	{0x0301, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xFF}, /*PCIe DMA stop*/
	{0x0522, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xFF}, /*Tx Pause*/
	{0x05F8, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, 0xFF, 0}, /*Should be zero if no packet is transmitting*/
	{0x05F9, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, 0xFF, 0}, /*Should be zero if no packet is transmitting*/
	{0x05FA, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, 0xFF, 0}, /*Should be zero if no packet is transmitting*/
	{0x05FB, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, 0xFF, 0}, /*Should be zero if no packet is transmitting*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), 0}, /*CCK and OFDM are disabled,and clock are gated*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_DELAY, 0, HALMAC_PWRSEQ_DELAY_US}, /*Delay 1us*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), 0}, /*Whole BB is reset*/
	{0x0100, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x3F}, /*Reset MAC TRX*/
	{0x0101, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), 0}, /*check if removed later*/
	{0x0553, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(5), BIT(5)}, /*Respond TxOK to scheduler*/
	{0x0008, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(4), BIT(4)}, /* switch TSF clock to 32K*/
	{0x0109, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, BIT(7), BIT(7)}, /*Polling 0x109[7]=0  TSF in 40M*/
	{0x0090, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /* enable WL_LPS_EN*/
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_ACT_TO_DEEP_LPS[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0x0101, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(2), BIT(2)}, /*Enable 32k calibration and thermal meter*/
	{0x0199, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(3), BIT(3)}, /*Register write data of 32K calibration*/
	{0x019B, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(7), BIT(7)},  /*Enable 32k calibration reg write*/
	{0x1138, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0) | BIT(1), BIT(0) | BIT(1)}, /*set RPWM IMR*/
	{0x0194, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /* enable 32K CLK*/
	{0x0093, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xDE}, /* PCIE LPS Option*/
	{0x0092, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x60}, /* PCIE LPS Option*/
	{0x0093, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x9B}, /* USB LPS Option*/
	{0x0092, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x60}, /* USB LPS Option*/
	{0x0093, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xA}, /* SDIO LPS Option*/
	{0x0092, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x60}, /* SDIO LPS Option*/
	{0x0090, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), BIT(1)}, /* enable reg use 32K CLK*/
	{0x0301, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xFF}, /*PCIe DMA stop*/
	{0x0522, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xFF}, /*Tx Pause*/
	{0x05F8, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, 0xFF, 0}, /*Should be zero if no packet is transmitting*/
	{0x05F9, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, 0xFF, 0}, /*Should be zero if no packet is transmitting*/
	{0x05FA, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, 0xFF, 0}, /*Should be zero if no packet is transmitting*/
	{0x05FB, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, 0xFF, 0}, /*Should be zero if no packet is transmitting*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), 0}, /*CCK and OFDM are disabled,and clock are gated*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_DELAY, 0, HALMAC_PWRSEQ_DELAY_US}, /*Delay 1us*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), 0}, /*Whole BB is reset*/
	{0x0100, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x3F}, /*Reset MAC TRX*/
	{0x0101, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), 0}, /*check if removed later*/
	{0x0553, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(5), BIT(5)}, /*Respond TxOK to scheduler*/
	{0x0008, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(4), BIT(4)}, /* switch TSF clock to 32K*/
	{0x0109, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, BIT(7), BIT(7)}, /*Polling 0x109[7]=1  TSF in 32K*/
	{0x0090, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(0), BIT(0)}, /* enable WL_LPS_EN*/
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

HALMAC_WLAN_PWR_CFG HALMAC_RTL8822B_TRANS_LPS_TO_ACT[] = {
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value } */
	{0x0080, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_WRITE, BIT(7), BIT(7)}, /*SDIO RPWM*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_DELAY, 0, HALMAC_PWRSEQ_DELAY_MS}, /*Delay*/
	{0x0080, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_SDIO_MSK, HALMAC_PWR_BASEADDR_SDIO, HALMAC_PWR_CMD_WRITE, BIT(7), 0}, /*SDIO RPWM*/
	{0xFE58, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x84}, /*USB RPWM*/
	{0xFE58, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_USB_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x04}, /*USB RPWM*/
	{0x03D9, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x84}, /*PCIe RPWM*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_DELAY, 0, HALMAC_PWRSEQ_DELAY_MS}, /*Delay*/
	{0x03D9, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_PCI_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x04}, /*PCIe RPWM*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_DELAY, 0, HALMAC_PWRSEQ_DELAY_MS}, /*Delay*/
	{0x0008, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(4), 0}, /* switch TSF to 40M*/
	{0x0109, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_POLLING, BIT(7), 0}, /*Polling 0x109[7]=0  TSF in 40M*/
	{0x0101, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), BIT(1)},
	{0x0100, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xFF}, /*nable WMAC TRX*/
	{0x0002, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1) | BIT(0), BIT(1) | BIT(0)}, /*nable BB macro*/
	{0x0522, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0},
	{0x113C, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0x03}, /*clear RPWM INT*/
	{0x0124, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xFF}, /*clear FW INT*/
	{0x0125, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xFF}, /*clear FW INT*/
	{0x0126, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xFF}, /*clear FW INT*/
	{0x0127, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, 0xFF, 0xFF}, /*clear FW INT*/
	{0x0090, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(1), 0}, /* disable reg use 32K CLK*/
	{0x0101, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, HALMAC_PWR_BASEADDR_MAC, HALMAC_PWR_CMD_WRITE, BIT(2), 0}, /*disable 32k calibration and thermal meter*/
	{0xFFFF, HALMAC_PWR_CUT_ALL_MSK, HALMAC_PWR_FAB_ALL_MSK, HALMAC_PWR_INTF_ALL_MSK, 0, HALMAC_PWR_CMD_END, 0, 0},
};

/* Card Enable Array */
PHALMAC_WLAN_PWR_CFG halmac_8822b_card_enable_flow[] = {
	HALMAC_RTL8822B_TRANS_CARDDIS_TO_CARDEMU,
	HALMAC_RTL8822B_TRANS_CARDEMU_TO_ACT,
	NULL
};

/* Card Disable Array */
PHALMAC_WLAN_PWR_CFG halmac_8822b_card_disable_flow[] = {
	HALMAC_RTL8822B_TRANS_ACT_TO_CARDEMU,
	HALMAC_RTL8822B_TRANS_CARDEMU_TO_CARDDIS,
	NULL
};

/* Suspend Array */
PHALMAC_WLAN_PWR_CFG halmac_8822b_suspend_flow[] = {
	HALMAC_RTL8822B_TRANS_ACT_TO_CARDEMU,
	HALMAC_RTL8822B_TRANS_CARDEMU_TO_SUS,
	NULL
};

/* Resume Array */
PHALMAC_WLAN_PWR_CFG halmac_8822b_resume_flow[] = {
	HALMAC_RTL8822B_TRANS_SUS_TO_CARDEMU,
	HALMAC_RTL8822B_TRANS_CARDEMU_TO_ACT,
	NULL
};

/* HWPDN Array - HW behavior */
PHALMAC_WLAN_PWR_CFG halmac_8822b_hwpdn_flow[] = {
	NULL
};

/* Enter LPS - FW behavior */
PHALMAC_WLAN_PWR_CFG halmac_8822b_enter_lps_flow[] = {
	HALMAC_RTL8822B_TRANS_ACT_TO_LPS,
	NULL
};

/* Enter Deep LPS - FW behavior */
PHALMAC_WLAN_PWR_CFG halmac_8822b_enter_deep_lps_flow[] = {
	HALMAC_RTL8822B_TRANS_ACT_TO_DEEP_LPS,
	NULL
};

/* Leave LPS -FW behavior */
PHALMAC_WLAN_PWR_CFG halmac_8822b_leave_lps_flow[] = {
	HALMAC_RTL8822B_TRANS_LPS_TO_ACT,
	NULL
};

#endif /* HALMAC_8822B_SUPPORT*/