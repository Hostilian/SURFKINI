class_name SurfTimer
extends Node

signal timer_started()
signal stage_completed(stage_num: int, split_time_ms: int)
signal timer_finished(total_time_ms: int, is_personal_best: bool)

var is_running: bool = false
var start_time_ms: int = 0
var elapsed_time_ms: int = 0
var personal_best_ms: int = 99999999
var current_stage: int = 1

func start_run() -> void:
	is_running = true
	start_time_ms = Time.get_ticks_msec()
	elapsed_time_ms = 0
	current_stage = 1
	timer_started.emit()

func update_timer() -> int:
	if is_running:
		elapsed_time_ms = Time.get_ticks_msec() - start_time_ms
	return elapsed_time_ms

func complete_stage(stage_num: int) -> void:
	if not is_running: return
	var split: int = update_timer()
	current_stage = stage_num + 1
	stage_completed.emit(stage_num, split)

func finish_run() -> int:
	if not is_running: return elapsed_time_ms
	is_running = false
	elapsed_time_ms = update_timer()
	
	var is_pb: bool = elapsed_time_ms < personal_best_ms
	if is_pb:
		personal_best_ms = elapsed_time_ms
		
	timer_finished.emit(elapsed_time_ms, is_pb)
	return elapsed_time_ms
