//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CXformImplementInitPlanAnchor.h
//
//	@doc:
//		Transform logical to physical InitPlanAnchor
//---------------------------------------------------------------------------
#ifndef GPOPT_CXformImplementInitPlanAnchor_H
#define GPOPT_CXformImplementInitPlanAnchor_H

#include "gpos/base.h"

#include "gpopt/xforms/CXformImplementation.h"

namespace gpopt
{
using namespace gpos;

//---------------------------------------------------------------------------
//	@class:
//		CXformImplementInitPlanAnchor
//
//	@doc:
//		Transform logical to physical InitPlanAnchor
//
//---------------------------------------------------------------------------
class CXformImplementInitPlanAnchor : public CXformImplementation
{
private:
public:
	CXformImplementInitPlanAnchor(const CXformImplementInitPlanAnchor &) =
		delete;

	// ctor
	explicit CXformImplementInitPlanAnchor(CMemoryPool *);

	// dtor
	~CXformImplementInitPlanAnchor() override = default;

	// ident accessors
	EXformId
	Exfid() const override
	{
		return ExfImplementInitPlanAnchor;
	}

	// return a string for xform name
	const CHAR *
	SzId() const override
	{
		return "CXformImplementInitPlanAnchor";
	}

	// compute xform promise for a given expression handle
	EXformPromise
	Exfp(CExpressionHandle &  // exprhdl
	) const override
	{
		return CXform::ExfpHigh;
	}

	// actual transform
	void Transform(CXformContext *pxfctxt, CXformResult *pxfres,
				   CExpression *pexpr) const override;

};	// class CXformImplementInitPlanAnchor

}  // namespace gpopt


#endif	// !GPOPT_CXformImplementInitPlanAnchor_H

// EOF
