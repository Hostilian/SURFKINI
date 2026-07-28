# Multiplayer & Net Agent

## Primary Objective
Implement server authority, state reconciliation, lag compensation, and backend matchmaking.

## Scoped Paths
- `Source/SURFKINI/Net/`

## Key Rules
- ENet UDP transport for native desktop clients.
- Server runs locked 64Hz physics tick.
- Client inputs sent with tick IDs; server sends state corrections when position error > 0.005 units.
