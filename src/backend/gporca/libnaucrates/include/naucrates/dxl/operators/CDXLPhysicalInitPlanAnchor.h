//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CDXLPhysicalInitPlanAnchor.h
//
//	@doc:
//		Class for representing DXL physical initplan anchor operators
//---------------------------------------------------------------------------

#ifndef GPDXL_CDXLPhysicalInitPlanAnchor_H
#define GPDXL_CDXLPhysicalInitPlanAnchor_H

#include "gpos/base.h"

#include "naucrates/dxl/operators/CDXLPhysical.h"
#include "naucrates/dxl/operators/CDXLSpoolInfo.h"


namespace gpdxl
{
//---------------------------------------------------------------------------
//	@class:
//		CDXLPhysicalInitPlanAnchor
//
//	@doc:
//		Class for representing DXL physical initplan anchor operators
//
//---------------------------------------------------------------------------
class CDXLPhysicalInitPlanAnchor : public CDXLPhysical
{
private:
public:
	CDXLPhysicalInitPlanAnchor(CDXLPhysicalInitPlanAnchor &) = delete;

	// ctor
	CDXLPhysicalInitPlanAnchor(CMemoryPool *mp);

	// dtor
	~CDXLPhysicalInitPlanAnchor() override;

	// accessors
	Edxlopid GetDXLOperator() const override;
	const CWStringConst *GetOpNameStr() const override;

	// serialize operator in DXL format
	void SerializeToDXL(CXMLSerializer *xml_serializer,
						const CDXLNode *dxlnode) const override;

	// conversion function
	static CDXLPhysicalInitPlanAnchor *
	Cast(CDXLOperator *dxl_op)
	{
		GPOS_ASSERT(nullptr != dxl_op);
		GPOS_ASSERT(EdxlopPhysicalInitPlanAnchor == dxl_op->GetDXLOperator());

		return dynamic_cast<CDXLPhysicalInitPlanAnchor *>(dxl_op);
	}

#ifdef GPOS_DEBUG
	// checks whether the operator has valid structure, i.e. number and
	// types of child nodes
	void AssertValid(const CDXLNode *, BOOL validate_children) const override;
#endif	// GPOS_DEBUG
};
}  // namespace gpdxl
#endif	// !GPDXL_CDXLPhysicalInitPlanAnchor_H

// EOF
