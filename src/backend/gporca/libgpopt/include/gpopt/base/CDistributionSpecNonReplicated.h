//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2023 VMware, Inc. or its affiliates.
//
//	@filename:
//		CDistributionSpecNonReplicated.h
//
//	@doc:
//		Description of a distribution that allows no duplicates;
//		Can be used only as a required property;
//---------------------------------------------------------------------------
#ifndef GPOPT_CDistributionSpecNonReplicated_H
#define GPOPT_CDistributionSpecNonReplicated_H

#include "gpos/base.h"

#include "gpopt/base/CDistributionSpec.h"
#include "gpopt/base/CDistributionSpecSingleton.h"

namespace gpopt
{
using namespace gpos;

//---------------------------------------------------------------------------
//	@class:
//		CDistributionSpecNonReplicated
//
//	@doc:
//		Class for representing distribution that allows no duplicates
//---------------------------------------------------------------------------
class CDistributionSpecNonReplicated : public CDistributionSpecSingleton
{
private:
public:
	//ctor
	CDistributionSpecNonReplicated()
	{
	}

	// accessor
	virtual EDistributionType
	Edt() const
	{
		return CDistributionSpec::EdtNonReplicated;
	}

	// does current distribution satisfy the given one
	virtual BOOL
	FSatisfies(const CDistributionSpec *pds GPOS_UNUSED) const
	{
		GPOS_ASSERT(!"Non-Replicated distribution cannot be derived");

		return false;
	}

	// return true if distribution spec can be derived
	virtual BOOL
	FDerivable() const
	{
		return false;
	}

	// print
	virtual IOstream &
	OsPrint(IOstream &os) const
	{
		return os << "NON-REPLICATED";
	}

	// return distribution partitioning type
	virtual EDistributionPartitioningType
	Edpt() const
	{
		return EdptUnknown;
	}

};	// class CDistributionSpecNonReplicated

}  // namespace gpopt

#endif	// !GPOPT_CDistributionSpecNonReplicated_H

// EOF
