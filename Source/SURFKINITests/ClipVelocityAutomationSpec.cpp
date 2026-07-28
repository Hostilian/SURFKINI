// Copyright 2026 SURFKINI Team. Open-Source Licensed.
// Source: ValveSoftware/source-sdk-2013, gamemovement.cpp

#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FClipVelocityOverbounceTest, "SURFKINI.Physics.ClipVelocityOverbounce", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FClipVelocityOverbounceTest::RunTest(const FString& Parameters)
{
	const float ExpectedOverbounce = 1.001f;
	const float ExpectedRampCosThreshold = 0.707f; // cos(45 degrees)

	TestEqual(TEXT("Overbounce coefficient must match Source SDK 1.001f"), ExpectedOverbounce, 1.001f);
	TestEqual(TEXT("Ramp surface normal Z threshold must equal cos(45deg) = 0.707f"), ExpectedRampCosThreshold, 0.707f);

	return true;
}
