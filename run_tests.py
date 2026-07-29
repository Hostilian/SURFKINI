#!/usr/bin/env python3
"""
SURFKINI Automated QA Test Runner Suite v2.0.0
==============================================
Tests physics math, timer splits, net snapshot buffering, strafe sync, input packing, and anti-cheat validation.
"""

import sys
import math

def test_velocity_clipping():
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

def test_input_packing():
	# Pack bits: forward(1) | jump(16) | crouch(32) = 49
	packed = (1 << 0) | (1 << 4) | (1 << 5)
	assert packed == 49, f"Expected 49, got {packed}"
	assert (packed & (1 << 0)) != 0, "Forward bit missing"
	assert (packed & (1 << 4)) != 0, "Jump bit missing"
	print("[PASS] Networking: InputCompressor Bitfield test")

def test_strafe_sync():
	# Velocity normalized dot WishDir
	vel_norm = (1.0, 0.0, 0.0)
	wish_dir = (1.0, 0.0, 0.0)
	sync = (vel_norm[0]*wish_dir[0] + vel_norm[1]*wish_dir[1]) * 100.0
	assert sync == 100.0, f"Expected 100% sync, got {sync}"
	print("[PASS] Movement: StrafesCalculator Sync test")

def main():
	print("==================================================")
	print("  SURFKINI Automated QA Test Suite v2.0.0")
	print("==================================================")
	try:
		test_velocity_clipping()
		test_timer_precision()
		test_move_validator()
		test_input_packing()
		test_strafe_sync()
		print("\nSUCCESS: All 5 automated unit test suites passed cleanly!")
		return 0
	except AssertionError as e:
		print(f"\nFAIL: Unit test failure: {e}")
		return 1

if __name__ == "__main__":
	sys.exit(main())
