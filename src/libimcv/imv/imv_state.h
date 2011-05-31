/*
 * Copyright (C) 2011 Andreas Steffen, HSR Hochschule fuer Technik Rapperswil
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
 *
 * @defgroup imv_state_t imv_state
 * @{ @ingroup imv_state
 */

#ifndef IMV_STATE_H_
#define IMV_STATE_H_

#include <tnc/tncifimv.h>
#include <library.h>

typedef struct imv_state_t imv_state_t;

/**
 * Internal state of an IMV connection instance
 */
struct imv_state_t {

	/**
	 * Get the TNCS connection ID attached to the state
	 *
	 * @return				TNCS connection ID of the state
	 */
	 TNC_ConnectionID (*get_connection_id)(imv_state_t *this);

	/**
	 * Change the connection state
	 *
	 * @param new_state		new connection state
	 */
	void (*change_state)(imv_state_t *this, TNC_ConnectionState new_state);

	/**
	 * Get IMV action recommendation and evaluation result
	 *
	 * @param rec			IMV action recommendation
	 * @param eval			IMV evaluation result
	 *
	 */
	void (*get_recommendation)(imv_state_t *this,
							   TNC_IMV_Action_Recommendation *rec,
							   TNC_IMV_Evaluation_Result *eval);

	/**
	 * Set IMV action recommendation and evaluation result
	 *
	 * @param rec			IMV action recommendation
	 * @param eval			IMV evaluation result
	 *
	 */
	void (*set_recommendation)(imv_state_t *this,
							   TNC_IMV_Action_Recommendation rec,
							   TNC_IMV_Evaluation_Result eval);

	/**
	 * Destroys an imv_state_t object
	 */
	void (*destroy)(imv_state_t *this);
};

#endif /** IMV_STATE_H_ @}*/