/*
 * Copyright (C) 2012 Martin Willi
 * Copyright (C) 2012 revosec AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

/**
 * @defgroup eap_radius_accounting eap_radius_accounting
 * @{ @ingroup
 */

#ifndef EAP_RADIUS_ACCOUNTING_H_
#define EAP_RADIUS_ACCOUNTING_H_

#include <bus/listeners/listener.h>

typedef struct eap_radius_accounting_t eap_radius_accounting_t;

/**
 * RADIUS accounting for IKE/IPsec.
 */
struct eap_radius_accounting_t {

	/**
	 * Implements listener_t.
	 */
	listener_t listener;

	/**
	 * Destroy a eap_radius_accounting_t.
	 */
	void (*destroy)(eap_radius_accounting_t *this);
};

/**
 * Create a eap_radius_accounting instance.
 */
eap_radius_accounting_t *eap_radius_accounting_create();

#endif /** EAP_RADIUS_ACCOUNTING_H_ @}*/