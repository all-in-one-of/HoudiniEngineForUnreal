/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * Produced by:
 *      Mykola Konyk
 *      Side Effects Software Inc
 *      123 Front Street West, Suite 1401
 *      Toronto, Ontario
 *      Canada   M5J 2M2
 *      416-504-9876
 *
 */

#pragma once
#include "HoudiniAssetParameter.h"
#include "HoudiniAssetParameterRamp.generated.h"


class UHoudiniAssetParameterRamp;


UCLASS(BlueprintType)
class HOUDINIENGINERUNTIME_API UHoudiniAssetParameterRampCurveFloat : public UCurveFloat
{
	GENERATED_UCLASS_BODY()

public:

	/** Set parent ramp parameter. **/
	void SetParentRampParameter(UHoudiniAssetParameterRamp* InHoudiniAssetParameterRamp);

/** FCurveOwnerInterface methods. **/
public:

	virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;

protected:

	/** Parent ramp parameter. **/
	UHoudiniAssetParameterRamp* HoudiniAssetParameterRamp;
};


UCLASS(BlueprintType)
class HOUDINIENGINERUNTIME_API UHoudiniAssetParameterRampCurveColor : public UCurveLinearColor
{
	GENERATED_UCLASS_BODY()

public:

	/** Set parent ramp parameter. **/
	void SetParentRampParameter(UHoudiniAssetParameterRamp* InHoudiniAssetParameterRamp);

/** FCurveOwnerInterface methods. **/
public:

	virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;

protected:

	/** Parent ramp parameter. **/
	UHoudiniAssetParameterRamp* HoudiniAssetParameterRamp;
};


UCLASS()
class HOUDINIENGINERUNTIME_API UHoudiniAssetParameterRamp : public UHoudiniAssetParameterMultiparm
{
	GENERATED_UCLASS_BODY()

public:

	/** Destructor. **/
	virtual ~UHoudiniAssetParameterRamp();

public:

	/** Create instance of this class. **/
	static UHoudiniAssetParameterRamp* Create(UHoudiniAssetComponent* InHoudiniAssetComponent,
		UHoudiniAssetParameter* InParentParameter, HAPI_NodeId InNodeId, const HAPI_ParmInfo& ParmInfo);

public:

	/** Create this parameter from HAPI information. **/
	virtual bool CreateParameter(UHoudiniAssetComponent* InHoudiniAssetComponent,
		UHoudiniAssetParameter* InParentParameter, HAPI_NodeId InNodeId, const HAPI_ParmInfo& ParmInfo) override;

/** UObject methods. **/
public:

	virtual void Serialize(FArchive& Ar) override;
	static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);

#if WITH_EDITOR

	/** Create widget for this parameter and add it to a given category. **/
	virtual void CreateWidget(IDetailCategoryBuilder& DetailCategoryBuilder) override;

	/** Create package for curve object. **/
	UPackage* BakeCreateCurvePackage(FName& CurveName, bool bBake);

	/** Called when float ramp parameter changes via user interface. **/
	void OnCurveFloatChanged();

	/** Called when color ramp parameter changes via user interface. **/
	void OnCurveColorChanged();

#endif

protected:

	//! Curve that is being edited.
	UCurveBase* CurveObject;

	//! Set to true if this ramp is a float ramp. Otherwise is considered a color ramp.
	bool bIsFloatRamp;
};
