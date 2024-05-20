//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CDXLPhysicalInitPlanAnchor.cpp
//
//	@doc:
//		Implementation of DXL physical initplan anchor operator
//---------------------------------------------------------------------------


#include "naucrates/dxl/operators/CDXLPhysicalInitPlanAnchor.h"

#include "naucrates/dxl/operators/CDXLNode.h"
#include "naucrates/dxl/xml/CXMLSerializer.h"

using namespace gpos;
using namespace gpdxl;

//---------------------------------------------------------------------------
//	@function:
//		CDXLPhysicalInitPlanAnchor::CDXLPhysicalInitPlanAnchor
//
//	@doc:
//		Constructor
//
//---------------------------------------------------------------------------
CDXLPhysicalInitPlanAnchor::CDXLPhysicalInitPlanAnchor(CMemoryPool *mp)
	: CDXLPhysical(mp)
{
}

//---------------------------------------------------------------------------
//	@function:
//		CDXLPhysicalInitPlanAnchor::~CDXLPhysicalInitPlanAnchor
//
//	@doc:
//		Destructor
//
//---------------------------------------------------------------------------
CDXLPhysicalInitPlanAnchor::~CDXLPhysicalInitPlanAnchor() = default;

//---------------------------------------------------------------------------
//	@function:
//		CDXLPhysicalInitPlanAnchor::GetDXLOperator
//
//	@doc:
//		Operator type
//
//---------------------------------------------------------------------------
Edxlopid
CDXLPhysicalInitPlanAnchor::GetDXLOperator() const
{
	return EdxlopPhysicalInitPlanAnchor;
}


//---------------------------------------------------------------------------
//	@function:
//		CDXLPhysicalInitPlanAnchor::GetOpNameStr
//
//	@doc:
//		Operator name
//
//---------------------------------------------------------------------------
const CWStringConst *
CDXLPhysicalInitPlanAnchor::GetOpNameStr() const
{
	return CDXLTokens::GetDXLTokenStr(EdxltokenPhysicalInitPlanAnchor);
}

//---------------------------------------------------------------------------
//	@function:
//		CDXLPhysicalInitPlanAnchor::SerializeToDXL
//
//	@doc:
//		Serialize operator in DXL format
//
//---------------------------------------------------------------------------
void
CDXLPhysicalInitPlanAnchor::SerializeToDXL(CXMLSerializer *xml_serializer,
										   const CDXLNode *dxlnode) const
{
	const CWStringConst *element_name = GetOpNameStr();

	xml_serializer->OpenElement(
		CDXLTokens::GetDXLTokenStr(EdxltokenNamespacePrefix), element_name);

	// serialize properties
	dxlnode->SerializePropertiesToDXL(xml_serializer);

	// serialize children
	dxlnode->SerializeChildrenToDXL(xml_serializer);

	xml_serializer->CloseElement(
		CDXLTokens::GetDXLTokenStr(EdxltokenNamespacePrefix), element_name);
}

#ifdef GPOS_DEBUG
//---------------------------------------------------------------------------
//	@function:
//		CDXLPhysicalInitPlanAnchor::AssertValid
//
//	@doc:
//		Checks whether operator node is well-structured
//
//---------------------------------------------------------------------------
void
CDXLPhysicalInitPlanAnchor::AssertValid(const CDXLNode *dxlnode,
										BOOL validate_children) const
{
	const ULONG arity = dxlnode->Arity();
	GPOS_ASSERT(1 < arity);

	for (ULONG ul = 1; ul < arity; ul++)
	{
		CDXLNode *child_dxlnode = (*dxlnode)[ul];
		GPOS_ASSERT(EdxloptypePhysical ==
					child_dxlnode->GetOperator()->GetDXLOperatorType());

		if (validate_children)
		{
			child_dxlnode->GetOperator()->AssertValid(child_dxlnode,
													  validate_children);
		}
	}
}
#endif	// GPOS_DEBUG

// EOF
