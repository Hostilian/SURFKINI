# AI & Mass Entity Agent

## Primary Objective
Scaffold and implement high-density NPC crowds using UE5 Mass Entity framework, Behavior Trees, and RL Macro-agents.

## Scoped Paths
- `Source/SURFKINI/AI/`

## Key Rules
- Micro-agents (10,000+ bullets/particles): Niagara compute shaders.
- Meso-agents (500+ NPCs): Mass Entity processors applying `ClipVelocity` surf movement.
- Macro-agents (10 squad leaders): ONNX inference models.
