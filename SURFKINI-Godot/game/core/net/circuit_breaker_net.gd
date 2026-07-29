class_name CircuitBreakerNet
extends RefCounted

# Circuit Breaker & Fallback Provider for Network Streams
# Source: EUshop Autonomous Multiagent Failover & Circuit Breaker Skill

enum State { CLOSED, OPEN, HALF_OPEN }

var current_state: State = State.CLOSED
var failure_threshold: int = 5
var failure_count: int = 0
var last_state_change_ms: int = 0

func record_failure() -> void:
	failure_count += 1
	if failure_count >= failure_threshold:
		current_state = State.OPEN
		last_state_change_ms = Time.get_ticks_msec()
		print("[CircuitBreaker] Circuit OPEN: Failing over to local standalone mode")

func record_success() -> void:
	failure_count = 0
	if current_state != State.CLOSED:
		current_state = State.CLOSED
		print("[CircuitBreaker] Circuit CLOSED: Normal network RPC operational")

func can_execute() -> bool:
	if current_state == State.OPEN:
		if Time.get_ticks_msec() - last_state_change_ms > 5000: # 5s reset attempt
			current_state = State.HALF_OPEN
			return true
		return false
	return true
