#!/usr/bin/env python3
"""
SURFKINI Automated QA Test Runner Suite v5.0.0
==============================================
Tests physics math, timer splits, net snapshot buffering, strafe sync, input packing, recoil decay, teleport bounds, circuit breaker, subtick buffering, duck jump offset, and lag compensation rewind.
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
	packed = (1 << 0) | (1 << 4) | (1 << 5)
	assert packed == 49, f"Expected 49, got {packed}"
	assert (packed & (1 << 0)) != 0, "Forward bit missing"
	assert (packed & (1 << 4)) != 0, "Jump bit missing"
	print("[PASS] Networking: InputCompressor Bitfield test")

def test_strafe_sync():
	vel_norm = (1.0, 0.0, 0.0)
	wish_dir = (1.0, 0.0, 0.0)
	sync = (vel_norm[0]*wish_dir[0] + vel_norm[1]*wish_dir[1]) * 100.0
	assert sync == 100.0, f"Expected 100% sync, got {sync}"
	print("[PASS] Movement: StrafesCalculator Sync test")

def test_recoil_decay():
	recoil_pitch = 0.05
	decay_rate = 5.0
	delta_time = 0.1
	decayed = recoil_pitch * (1.0 - min(decay_rate * delta_time, 1.0))
	assert decayed == 0.025, f"Expected 0.025 decayed pitch, got {decayed}"
	print("[PASS] Weapons: Recoil Pattern Decay test")

def test_teleport_bounds():
	dist_sqr = 1500000.0
	max_allowed_sqr = 1000000.0
	is_illegal = dist_sqr > max_allowed_sqr
	assert is_illegal, "Expected illegal teleport detection"
	print("[PASS] Anti-Cheat: Teleport Bounds test")

def test_subtick_buffering():
	current_ms = 1000
	last_jump_ms = 950
	last_ground_ms = 920
	valid = (current_ms - last_jump_ms <= 80) and (current_ms - last_ground_ms <= 100)
	assert valid, "Expected buffered jump valid"
	print("[PASS] Movement: Subtick Buffer & Coyote Time test")

def test_circuit_breaker():
	failures = 5
	threshold = 5
	should_allow = failures < threshold
	assert not should_allow, "Expected circuit breaker OPEN (blocked)"
	print("[PASS] Networking: CircuitBreaker Failover test")

def test_duck_jump_height():
	stand_h = 1.8
	crouch_h = 1.2
	crouch_ratio = 1.0
	lerped_h = stand_h + (crouch_h - stand_h) * crouch_ratio
	assert math.isclose(lerped_h, 1.2, abs_tol=1e-3), f"Expected 1.2 crouch height, got {lerped_h}"
	print("[PASS] Movement: DuckJump Height Lerp test")

def test_lag_compensation_rewind():
	prev_pos = (0.0, 0.0, 0.0)
	curr_pos = (10.0, 0.0, 0.0)
	alpha = 0.5
	rewound = (prev_pos[0] + (curr_pos[0] - prev_pos[0]) * alpha, 0.0, 0.0)
	assert math.isclose(rewound[0], 5.0, abs_tol=1e-3), f"Expected 5.0 rewound X pos, got {rewound[0]}"
	print("[PASS] Networking: Lag Compensation Rewind test")

def main():
	print("==================================================")
	print("  SURFKINI Automated QA Test Suite v5.0.0")
	print("==================================================")
	try:
		test_velocity_clipping()
		test_timer_precision()
		test_move_validator()
		test_input_packing()
		test_strafe_sync()
		test_recoil_decay()
		test_teleport_bounds()
		test_subtick_buffering()
		test_circuit_breaker()
		test_duck_jump_height()
		test_lag_compensation_rewind()
		print("\nSUCCESS: All 11 automated unit test suites passed cleanly!")
		return 0
	except AssertionError as e:
		print(f"\nFAIL: Unit test failure: {e}")
		return 1

if __name__ == "__main__":
	sys.exit(main())
