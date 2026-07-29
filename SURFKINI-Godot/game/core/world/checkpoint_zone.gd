class_name CheckpointZone
extends Area3D

enum ZoneType { START, STAGE, CHECKPOINT, FINISH }

signal zone_entered(player: Node, zone_type: ZoneType, zone_index: int)

@export var type: ZoneType = ZoneType.CHECKPOINT
@export var zone_index: int = 1

func _ready() -> void:
	body_entered.connect(_on_body_entered)

func _on_body_entered(body: Node) -> void:
	if body.is_in_group("players"):
		zone_entered.emit(body, type, zone_index)
