/*
 * Copyright (C) 2011 Sansar Choinyambuu
 * HSR Hochschule fuer Technik Rapperswil
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

#include "tcg_pts_attr_tpm_version_info.h"

#include <pa_tnc/pa_tnc_msg.h>
#include <bio/bio_writer.h>
#include <bio/bio_reader.h>
#include <debug.h>

typedef struct private_tcg_pts_attr_tpm_version_info_t private_tcg_pts_attr_tpm_version_info_t;

/**
 * TPM Version Information
 * see section 3.11 of PTS Protocol: Binding to TNC IF-M Specification
 *
 *					   1				   2				   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |		  TPM Version Information (Variable Lenght)				|
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * see TPM Structure Specification Part 2, section 21.6: TPM_CAP_VERSION_INFO
 */

#define PTS_TPM_VER_INFO_SIZE		4

/**
 * Private data of an tcg_pts_attr_tpm_version_info_t object.
 */
struct private_tcg_pts_attr_tpm_version_info_t {

	/**
	 * Public members of tcg_pts_attr_tpm_version_info_t
	 */
	tcg_pts_attr_tpm_version_info_t public;

	/**
	 * Attribute vendor ID
	 */
	pen_t vendor_id;

	/**
	 * Attribute type
	 */
	u_int32_t type;

	/**
	 * Attribute value
	 */
	chunk_t value;

	/**
	 * Noskip flag
	 */
	bool noskip_flag;
	
	/**
	 * TPM Version Information
	 */
	chunk_t tpm_version_info;
};

METHOD(pa_tnc_attr_t, get_vendor_id, pen_t,
	private_tcg_pts_attr_tpm_version_info_t *this)
{
	return this->vendor_id;
}

METHOD(pa_tnc_attr_t, get_type, u_int32_t,
	private_tcg_pts_attr_tpm_version_info_t *this)
{
	return this->type;
}

METHOD(pa_tnc_attr_t, get_value, chunk_t,
	private_tcg_pts_attr_tpm_version_info_t *this)
{
	return this->value;
}

METHOD(pa_tnc_attr_t, get_noskip_flag, bool,
	private_tcg_pts_attr_tpm_version_info_t *this)
{
	return this->noskip_flag;
}

METHOD(pa_tnc_attr_t, set_noskip_flag,void,
	private_tcg_pts_attr_tpm_version_info_t *this, bool noskip)
{
	this->noskip_flag = noskip;
}

METHOD(pa_tnc_attr_t, build, void,
	private_tcg_pts_attr_tpm_version_info_t *this)
{
	bio_writer_t *writer;

	writer = bio_writer_create(PTS_TPM_VER_INFO_SIZE);
	writer->write_data(writer, this->tpm_version_info);

	this->value = chunk_clone(writer->get_buf(writer));
	writer->destroy(writer);
}

METHOD(pa_tnc_attr_t, process, status_t,
	private_tcg_pts_attr_tpm_version_info_t *this, u_int32_t *offset)
{
	bio_reader_t *reader;
	
	if (this->value.len < PTS_TPM_VER_INFO_SIZE)
	{
		DBG1(DBG_TNC, "insufficient data for TPM Version Information");
		*offset = 0;
		return FAILED;
	}
	reader = bio_reader_create(this->value);
	reader->read_data  (reader, this->value.len, &this->tpm_version_info);
	this->tpm_version_info = chunk_clone(this->tpm_version_info);
	reader->destroy(reader);

	return SUCCESS;
}

METHOD(pa_tnc_attr_t, destroy, void,
	private_tcg_pts_attr_tpm_version_info_t *this)
{
	free(this->value.ptr);
	free(this->tpm_version_info.ptr);
	free(this);
}

METHOD(tcg_pts_attr_tpm_version_info_t, get_tpm_version_info, chunk_t,
	private_tcg_pts_attr_tpm_version_info_t *this)
{
	return this->tpm_version_info;
}

METHOD(tcg_pts_attr_tpm_version_info_t, set_tpm_version_info, void,
		private_tcg_pts_attr_tpm_version_info_t *this,
		chunk_t tpm_version_info)
{
	this->tpm_version_info = tpm_version_info;
}

/**
 * Described in header.
 */
pa_tnc_attr_t *tcg_pts_attr_tpm_version_info_create(chunk_t tpm_version_info)
{
	private_tcg_pts_attr_tpm_version_info_t *this;

	INIT(this,
		.public = {
			.pa_tnc_attribute = {
				.get_vendor_id = _get_vendor_id,
				.get_type = _get_type,
				.get_value = _get_value,
				.get_noskip_flag = _get_noskip_flag,
				.set_noskip_flag = _set_noskip_flag,
				.build = _build,
				.process = _process,
				.destroy = _destroy,
			},
			.get_tpm_version_info = _get_tpm_version_info,
			.set_tpm_version_info = _set_tpm_version_info,
		},
		.vendor_id = PEN_TCG,
		.type = TCG_PTS_TPM_VERSION_INFO,
		.tpm_version_info = tpm_version_info,
	);

	return &this->public.pa_tnc_attribute;
}


/**
 * Described in header.
 */
pa_tnc_attr_t *tcg_pts_attr_tpm_version_info_create_from_data(chunk_t data)
{
	private_tcg_pts_attr_tpm_version_info_t *this;

	INIT(this,
		.public = {
			.pa_tnc_attribute = {
				.get_vendor_id = _get_vendor_id,
				.get_type = _get_type,
				.get_value = _get_value,
				.get_noskip_flag = _get_noskip_flag,
				.set_noskip_flag = _set_noskip_flag,
				.build = _build,
				.process = _process,
				.destroy = _destroy,
			},
			.get_tpm_version_info = _get_tpm_version_info,
			.set_tpm_version_info = _set_tpm_version_info,
		},
		.vendor_id = PEN_TCG,
		.type = TCG_PTS_TPM_VERSION_INFO,
		.value = chunk_clone(data),
	);

	return &this->public.pa_tnc_attribute;
}