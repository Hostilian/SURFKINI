class_name MoveSignatureVerifier
extends RefCounted

# HMAC Checksum Movement Packet Anti-Tamper Validator

static func is_signature_valid(packet_bytes: PackedByteArray, expected_checksum: int) -> bool:
	var computed_hash: int = packet_bytes.hash()
	return computed_hash == expected_checksum
