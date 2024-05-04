//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CLogicalInitPlanAnchor.cpp
//
//	@doc:
//		Implementation of InitPlan anchor operator
//---------------------------------------------------------------------------

#include "gpopt/operators/CLogicalInitPlanAnchor.h"

#include "gpos/base.h"

#include "gpopt/base/COptCtxt.h"
#include "gpopt/operators/CExpression.h"
#include "gpopt/operators/CExpressionHandle.h"

using namespace gpopt;

//---------------------------------------------------------------------------
//	@function:
//		CLogicalInitPlanAnchor::CLogicalInitPlanAnchor
//
//	@doc:
//		Ctor - for pattern
//
//---------------------------------------------------------------------------
CLogicalInitPlanAnchor::CLogicalInitPlanAnchor(CMemoryPool *mp)
	: CLogical(mp), m_id(0)
{
	m_fPattern = true;
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalInitPlanAnchor::CLogicalInitPlanAnchor
//
//	@doc:
//		Ctor
//
//---------------------------------------------------------------------------
CLogicalInitPlanAnchor::CLogicalInitPlanAnchor(CMemoryPool *mp, ULONG id)
	: CLogical(mp), m_id(id)
{
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalInitPlanAnchor::DeriveOutputColumns
//
//	@doc:
//		Derive output columns
//
//---------------------------------------------------------------------------
CColRefSet *
CLogicalInitPlanAnchor::DeriveOutputColumns(CMemoryPool *,	// mp
											CExpressionHandle &exprhdl)
{
	CColRefSet *pcrs = exprhdl.DeriveOutputColumns(exprhdl.Arity() - 1);
	pcrs->AddRef();

	return pcrs;
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalInitPlanAnchor::PkcDeriveKeys
//
//	@doc:
//		Derive key collection
//
//---------------------------------------------------------------------------
CKeyCollection *
CLogicalInitPlanAnchor::DeriveKeyCollection(CMemoryPool *,	// mp
											CExpressionHandle &exprhdl) const
{
	return PkcDeriveKeysPassThru(exprhdl, 0 /* ulChild */);
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalInitPlanAnchor::DerivePartitionInfo
//
//	@doc:
//		Derive part consumer
//
//---------------------------------------------------------------------------
CPartInfo *
CLogicalInitPlanAnchor::DerivePartitionInfo(CMemoryPool *mp,
									   CExpressionHandle &exprhdl) const
{
	return PpartinfoDeriveCombine(mp, exprhdl);
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalInitPlanAnchor::DeriveMaxCard
//
//	@doc:
//		Derive max card
//
//---------------------------------------------------------------------------
CMaxCard
CLogicalInitPlanAnchor::DeriveMaxCard(CMemoryPool *,  // mp
									  CExpressionHandle &exprhdl) const
{
	// pass on max card of first child
	return exprhdl.DeriveMaxCard(0);
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalInitPlanAnchor::Matches
//
//	@doc:
//		Match function
//
//---------------------------------------------------------------------------
BOOL
CLogicalInitPlanAnchor::Matches(COperator *pop) const
{
	if (pop->Eopid() != Eopid())
	{
		return false;
	}

	CLogicalInitPlanAnchor *popInitPlanAnchor =
		CLogicalInitPlanAnchor::PopConvert(pop);

	return m_id == popInitPlanAnchor->Id();
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalInitPlanAnchor::HashValue
//
//	@doc:
//		Hash function
//
//---------------------------------------------------------------------------
ULONG
CLogicalInitPlanAnchor::HashValue() const
{
	return gpos::CombineHashes(COperator::HashValue(), m_id);
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalInitPlanAnchor::PxfsCandidates
//
//	@doc:
//		Get candidate xforms
//
//---------------------------------------------------------------------------
CXformSet *
CLogicalInitPlanAnchor::PxfsCandidates(CMemoryPool *mp) const
{
	CXformSet *xform_set = GPOS_NEW(mp) CXformSet(mp);
	(void) xform_set->ExchangeSet(CXform::ExfLeftJoin2RightJoin);
	return xform_set;
}

//---------------------------------------------------------------------------
//	@function:
//		CLogicalInitPlanAnchor::OsPrint
//
//	@doc:
//		debug print
//
//---------------------------------------------------------------------------
IOstream &
CLogicalInitPlanAnchor::OsPrint(IOstream &os) const
{
	os << SzId() << " (";
	os << m_id;
	os << ")";

	return os;
}

// EOF
