class_name WeaponBase
extends Node3D

signal weapon_fired(weapon_name: String, ammo_remaining: int)
signal reloaded()

@export var weapon_name: String = "Kinetic Rifle"
@export var damage: float = 24.0
@export var fire_rate: float = 0.1
@export var max_ammo: int = 30
@export var is_hitscan: bool = true
@export var range_meters: float = 200.0

var current_ammo: int = 30
var _can_fire: bool = true
var _fire_timer: Timer

func _ready() -> void:
	current_ammo = max_ammo
	_fire_timer = Timer.new()
	_fire_timer.wait_time = fire_rate
	_fire_timer.one_shot = true
	_fire_timer.timeout.connect(func(): _can_fire = true)
	add_child(_fire_timer)

func fire(from_position: Vector3, direction: Vector3) -> bool:
	if not _can_fire or current_ammo <= 0:
		return false
		
	current_ammo -= 1
	_can_fire = false
	_fire_timer.start()
	weapon_fired.emit(weapon_name, current_ammo)
	return true

func reload() -> void:
	current_ammo = max_ammo
	reloaded.emit()
