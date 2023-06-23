//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2023 VMware, Inc. or its affiliates.
//
//	@filename:
//		CXformPushJoinBelowUnionAll.h
//
//	@doc:
//		Push join below union all transform
//---------------------------------------------------------------------------
#ifndef GPOPT_CXformPushJoinBelowUnionAll_H
#define GPOPT_CXformPushJoinBelowUnionAll_H

#include "gpos/base.h"

#include "gpopt/xforms/CXformExploration.h"

namespace gpopt
{
using namespace gpos;

//---------------------------------------------------------------------------
//	@class:
//		CXformPushJoinBelowUnionAll
//
//	@doc:
//		Push join below union all transform
//
//---------------------------------------------------------------------------
class CXformPushJoinBelowUnionAll : public CXformExploration
{
private:
public:
	// ctor
	explicit CXformPushJoinBelowUnionAll(CExpression *pexprPattern)
		: CXformExploration(pexprPattern)
	{
	}

	// dtor
	virtual ~CXformPushJoinBelowUnionAll()
	{
	}

	// compute xform promise for a given expression handle
	virtual EXformPromise Exfp(CExpressionHandle &exprhdl) const;

	CColRefArray *CopyWithRemappedColumns(CColRefArray *colref_array_template,
										  CColRefArray *colref_array_from,
										  CColRefArray *colref_array_to,
										  CMemoryPool *mp) const;

	// actual transform
	void Transform(CXformContext *pxfctxt, CXformResult *pxfres,
				   CExpression *pexpr) const;

	// This xform matches a large expression pattern, of
	// three children, one is a multileaf, and two are trees
	// To prevent the search space from exploding, return true
	// for xform to be applied only once
	BOOL
	IsApplyOnce()
	{
		return true;
	};
};	// class CXformPushJoinBelowUnionAll

}  // namespace gpopt


#endif	// !GPOPT_CXformPushJoinBelowUnionAll_H

// EOF
