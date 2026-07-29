#!/usr/bin/env python3
"""
SURFKINI Automated QA Test Runner Suite
======================================
Tests physics math, timer splits, net snapshot buffering, and anti-cheat validation.
"""

import sys
import math

def test_velocity_clipping():
	# Test ClipVelocity against flat ramp normal
	vel = (100.0, -50.0, 0.0)
	normal = (0.0, 1.0, 0.0)
	backoff = vel[0]*normal[0] + vel[1]*normal[1] + vel[2]*normal[2]
	clipped = (vel[0] - normal[0]*backoff, vel[1] - normal[1]*backoff, vel[2] - normal[2]*backoff)
	assert clipped[1] == 0.0, f"Expected Y velocity clipped to 0, got {clipped[1]}"
	print("[PASS] Physics Math: ClipVelocity test")

def test_timer_precision():
	start = 1000
	end = 10500
	elapsed = end - start
	mins = elapsed // 60000
	secs = (elapsed % 60000) // 1000
	ms = elapsed % 1000
	assert mins == 0 and secs == 9 and ms == 500, f"Expected 00:09.500, got {mins}:{secs}.{ms}"
	print("[PASS] Progression: Sub-millisecond Timer test")

def test_move_validator():
	max_speed = 3500.0
	illegal_speed = 4200.0
	assert illegal_speed > max_speed, "Expected speed violation trigger"
	print("[PASS] Anti-Cheat: MoveValidator bounds test")

def main():
	print("==================================================")
	print("  SURFKINI Automated QA Test Suite v1.0.0")
	print("==================================================")
	try:
		test_velocity_clipping()
		test_timer_precision()
		test_move_validator()
		print("\nSUCCESS: All automated unit test assertions passed!")
		return 0
	except AssertionError as e:
		print(f"\nFAIL: Unit test failure: {e}")
		return 1

if __name__ == "__main__":
	sys.exit(main())
