# Dual Tracking Module for AzerothCore

- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Credits](#credits)
- [License](#license)

---

## Description

`mod-dual-tracking` is an AzerothCore module that enables concurrent node tracking for dual-profession gatherers. It alters server-side tracking behavior in-memory, allowing players with both Mining and Herbalism to display both resource node types on the minimap radar simultaneously.

---

## Features

* **Simultaneous Node Tracking:** Displays both Mining nodes and Herbalism nodes on the minimap.
* **Profession Gated:** Dynamically verifies character skills. Players without both professions will retain default single-tracking behavior.
* **Update-Safe & Modular:** Operates without database edits, core code changes, or custom client patches.
* **Lightweight:** Uses in-memory spell mutations on boot and hooks directly into server aura handling.

---

## Requirements

* AzerothCore 3.3.5a (latest `master` branch)
* C++17 compatible compiler (MSVC 2019/2022, GCC, or Clang)
* CMake 3.16+

  ## Installation

1. Navigate to your AzerothCore `modules/` directory:
   cd azerothcore-wotlk/modules

2. Clone this repository:
   git clone https://github.com/b-wun/mod-dual-tracking.git

3. Re-run CMake to generate build files with the new module included.

4. Recompile your worldserver binary.

---

## Usage

* **Single Profession:** Casting **Find Herbs** or **Find Minerals** functions as normal, displaying only that specific node type.
* **Dual Profession:** When a character holding both Mining and Herbalism skills activates either **Find Herbs** or **Find Minerals**, the server automatically enables both tracking bitmasks, displaying both herb and ore locations on the minimap radar.

---

## Credits

* AzerothCore module framework.

---

## License

This module is released under the GNU AGPL v3 license, consistent with the base AzerothCore project.
