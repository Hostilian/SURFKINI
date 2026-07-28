# DEEP RESEARCH & MATHEMATICAL PHYSICS PROOFS FOR SURFKINI
## Unreal Engine 5.4 | Clean-Room Source Physics & High-Density Agent Architecture

---

## 🔬 Section 1: Mathematical Proof of Air-Strafing Acceleration Loophole

### 1. Classical Vector Acceleration vs. Projection-Capped Acceleration
In standard physics engines, velocity is updated by adding acceleration $\vec{a} \cdot \Delta t$ directly to velocity $\vec{v}$, capped by a maximum speed $V_{\text{max}}$:

$$\|\vec{v}_{\text{new}}\| \le V_{\text{max}}$$

In Source/Quake air physics, instead of capping the magnitude $\|\vec{v}\|$, the engine caps the **scalar projection** of the current velocity onto the normalized wish-direction vector $\hat{u}$:

$$V_{\text{proj}} = \vec{v} \cdot \hat{u}$$

The maximum allowable speed addition along $\hat{u}$ is defined by:

$$A_{\text{add}} = \max\left(0,\, L_{\text{air}} - V_{\text{proj}}\right)$$

where $L_{\text{air}}$ is the airborne wish speed cap (traditionally 30 ups).

The acceleration step added to velocity is:

$$A_{\text{step}} = \min\left(A_{\text{add}},\, \beta_{\text{air}} \cdot L_{\text{air}} \cdot \Delta t\right)$$

$$\vec{v}_{\text{new}} = \vec{v} + A_{\text{step}} \cdot \hat{u}$$

---

### 2. The Perpendicular Loophole Proof
Consider a player moving with high horizontal velocity $\vec{v} = (v_x, v_y, 0)$.

If the player aligns their wish-direction vector $\hat{u}$ such that it remains **strictly perpendicular** to $\vec{v}$:

$$\vec{v} \cdot \hat{u} = 0 \implies V_{\text{proj}} = 0$$

Since $V_{\text{proj}} = 0$, the maximum allowable acceleration $A_{\text{add}}$ simplifies to:

$$A_{\text{add}} = \max\left(0,\, L_{\text{air}} - 0\right) = L_{\text{air}} = 30$$

Regardless of how high the magnitude $\|\vec{v}\|$ becomes (e.g. 3,000 u/s), because $V_{\text{proj}} = 0$, the engine permits adding the maximum step $A_{\text{step}} = \beta_{\text{air}} \cdot L_{\text{air}} \cdot \Delta t$ in direction $\hat{u}$ every single tick!

Using Pythagoras' theorem for the updated velocity vector:

$$\|\vec{v}_{\text{new}}\|^2 = \|\vec{v}\|^2 + A_{\text{step}}^2 > \|\vec{v}\|^2$$

By continuously rotating camera yaw while holding strafe keys (A or D), $\hat{u}$ continuously rotates to stay perpendicular to $\vec{v}$, resulting in unbounded horizontal speed accumulation along a smooth parabolic curve.

---

## 📐 Section 2: Seam-Snagging & Normal Smoothing Algorithm

### The Mesh Seam Problem
When sweeping a capsule collider across adjacent planar triangles $T_1$ and $T_2$ on a surf ramp, floating point inaccuracies or internal edge geometry can cause the physics query to return an anomalous facet normal $\vec{n}_{\text{seam}}$ pointing flat or into the player's path ($\vec{n}_{\text{seam}} \cdot \vec{v} \ll 0$). Applying standard velocity clipping to $\vec{n}_{\text{seam}}$ instantly zeroes the player's momentum.

### The Normal Smoothing Solver
If the angle between consecutive contact normals exceeds $\theta_{\text{threshold}} = 15^\circ$ within a single tick, and both normals represent non-walkable ramp surfaces ($0 < n_z < 0.707$), we project the impact normal onto the average surface plane:

$$\vec{n}_{\text{smoothed}} = \text{Normalize}\left(\vec{n}_{\text{prev}} + \vec{n}_{\text{curr}}\right)$$

This prevents edge snagging and guarantees unbroken momentum along ramp seams.

---

## ⚡ Section 3: Subtick Jump & Coyote Time Architecture

### Subtick Buffer (8 ms Window)
If a jump input (`SpaceBar`) is pressed 2 ms before the next 60Hz physics tick, standard input polling might miss the window or trigger a frame boundary drop. We store a decaying subtick timer $T_{\text{subtick}} = 0.008\text{s}$. If $T_{\text{subtick}} > 0$ when the character becomes grounded or enters coyote time, the jump triggers deterministically.

### Coyote Time (100 ms Grace Window)
When a character slides off the lower edge of a ramp, $T_{\text{coyote}} = 0.100\text{s}$ is granted, allowing air jumps within 100 ms of leaving physical contact with the ramp surface.
