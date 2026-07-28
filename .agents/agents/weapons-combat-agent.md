# Weapons & Combat Agent

## Primary Objective
Implement weapons, hitscan traces, physics projectiles, damage logic, and lag compensation.

## Scoped Paths
- `Source/SURFKINI/Weapons/`

## Key Rules
- All weapons inherit from `AWeaponBase`.
- Server authoritative hit validation; client-side immediate tracer prediction.
- Support 100 HP + 100 Armor CS-style damage calculation.
