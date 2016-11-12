/******************************************************************************
 *
 * Copyright(c) 2015 - 2016 Realtek Corporation. All rights reserved.
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
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 ******************************************************************************/
#define _RTW_SDIO_C_

#include <drv_types.h>		/* struct dvobj_priv and etc. */
#include <drv_types_sdio.h>	/* RTW_SDIO_ADDR_CMD52_GEN */

/*
 * Description:
 *	Use SDIO cmd52 or cmd53 to read/write data
 *
 * Parameters:
 *	d	pointer of device object(struct dvobj_priv)
 *	addr	SDIO address, 17 bits
 *	buf	buffer for I/O
 *	len	length
 *	write	0:read, 1:write
 *	cmd52	0:cmd52, 1:cmd53
 *
 * Return:
 *	_SUCCESS	I/O ok.
 *	_FAIL		I/O fail.
 */
static u8 sdio_io(struct dvobj_priv *d, u32 addr, void *buf, size_t len, u8 write, u8 cmd52)
{
	u32 addr_drv;	/* address with driver defined bit */
	int err;
	u8 stop_retry = _FALSE;	/* flag for stopping retry or not */


	if (rtw_is_surprise_removed(dvobj_get_primary_adapter(d))) {
		RTW_ERR("%s: bSurpriseRemoved, skip %s 0x%05x, %zu bytes\n",
		        __FUNCTION__, write?"write":"read", addr, len);
		return _FAIL;
	}

	addr_drv = addr;
	if (cmd52)
		addr_drv = RTW_SDIO_ADDR_CMD52_GEN(addr_drv);

	do {
		if (write)
			err = d->intf_ops->write(d, addr_drv, buf, len, 0);
		else
			err = d->intf_ops->read(d, addr_drv, buf, len, 0);
		if (!err) {
			if (ATOMIC_READ(&d->continual_io_error)) {
				RTW_INFO("%s: Retry %s OK! addr=0x%05x %zu bytes, retry=%u\n",
				         __FUNCTION__, write?"write":"read",
				         addr, len, ATOMIC_READ(&d->continual_io_error));
				RTW_INFO_DUMP("Data: ", buf, len);
				rtw_reset_continual_io_error(d);
			}
			break;
		}

		RTW_ERR("%s: %s FAIL! error(%d) addr=0x%05x len=%zu\n",
			__FUNCTION__, write?"write":"read", err, addr, len);
		stop_retry = rtw_inc_and_chk_continual_io_error(d);
		if ((_TRUE == stop_retry) || (err == -1)) {
			/* critical error, unrecoverable */
			RTW_ERR("%s: Fatal error! Set surprise remove flag ON! (retry=%u)\n",
				__FUNCTION__, ATOMIC_READ(&d->continual_io_error));
			rtw_set_surprise_removed(dvobj_get_primary_adapter(d));
			return _FAIL;
		}

		/* WLAN IOREG or SDIO Local */
		if ((addr & 0x10000) || !(addr & 0xE000)) {
			RTW_WARN("%s: Retry %s addr=0x%05x %zu bytes, retry=%u\n",
			         __FUNCTION__, write?"write":"read", addr, len, ATOMIC_READ(&d->continual_io_error));
			continue;
		}
		return _FAIL;
	} while (1);

	return _SUCCESS;
}

u8 rtw_sdio_read_cmd52(struct dvobj_priv *d, u32 addr, void *buf, size_t len)
{
	return sdio_io(d, addr, buf, len, 0, 1);
}

u8 rtw_sdio_read_cmd53(struct dvobj_priv *d, u32 addr, void *buf, size_t len)
{
	return sdio_io(d, addr, buf, len, 0, 0);
}

u8 rtw_sdio_write_cmd52(struct dvobj_priv *d, u32 addr, void *buf, size_t len)
{
	return sdio_io(d, addr, buf, len, 1, 1);
}

u8 rtw_sdio_write_cmd53(struct dvobj_priv *d, u32 addr, void *buf, size_t len)
{
	return sdio_io(d, addr, buf, len, 1, 0);
}

u8 rtw_sdio_f0_read(struct dvobj_priv *d, u32 addr, void *buf, size_t len)
{
	int err;
	u8 ret;


	ret = _SUCCESS;
	addr = RTW_SDIO_ADDR_F0_GEN(addr);

	err = d->intf_ops->read(d, addr, buf, len, 0);
	if (err) {
		RTW_INFO("%s: [ERROR] Read f0 register FAIL!\n", __FUNCTION__);
		ret = _FAIL;
	}


	return ret;
}
