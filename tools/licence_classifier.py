# Copyright 2026 SURFKINI Team. Open-Source Licensed.
"""
SURFKINI Open-Source Licence Classifier & Gate
===============================================
Classifies open-source software licences to enforce clean, legal, and safe code reuse.
"""

import re

COMPATIBLE_LICENCES = {
    "MIT": {"permissive": True, "attribution_required": True, "score_weight": 1.0},
    "Apache-2.0": {"permissive": True, "attribution_required": True, "score_weight": 0.95},
    "BSD-3-Clause": {"permissive": True, "attribution_required": True, "score_weight": 0.95},
    "BSD-2-Clause": {"permissive": True, "attribution_required": True, "score_weight": 0.95},
    "Unlicense": {"permissive": True, "attribution_required": False, "score_weight": 1.0},
    "Zlib": {"permissive": True, "attribution_required": False, "score_weight": 0.9}
}

RESTRICTIVE_LICENCES = {
    "GPL-3.0": "Copyleft (GPL) — Requires clean-room adaptation only.",
    "GPL-2.0": "Copyleft (GPL) — Requires clean-room adaptation only.",
    "AGPL-3.0": "Network Copyleft (AGPL) — Requires clean-room adaptation only.",
    "Proprietary": "Proprietary Commercial — Clean-room implementation required.",
    "Unknown": "Licence missing or unverified — Clean-room implementation required."
}

def classify_licence(licence_text_or_spdx):
    if not licence_text_or_spdx:
        return "Unknown", False, "No licence provided."

    text = licence_text_or_spdx.strip()
    
    for spdx, meta in COMPATIBLE_LICENCES.items():
        if spdx.lower() in text.lower():
            return spdx, True, f"Permissive open-source licence ({spdx}). Direct reuse allowed with attribution."

    if "mit licence" in text.lower() or "mit license" in text.lower():
        return "MIT", True, "MIT Licence detected. Direct reuse allowed with attribution."

    if "apache" in text.lower():
        return "Apache-2.0", True, "Apache 2.0 Licence detected. Direct reuse allowed with attribution."

    return "Unknown/Restricted", False, "Licence is unknown or copyleft. Clean-room conceptual adaptation only."
