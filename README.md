Not ready to be integrated to every project it's
# Linear Tile Procedural Generation Plugin (WIP)

This is a work-in-progress plugin for **Unreal Engine**, designed to be a lightweight and easy-to-use tool for prototyping tile-based procedural generation.

A lot of the projects I worked on during my studies involved simple procedural generation. I started developing this modular, *linear* tile-based system as a way to save time.  

With the release of the **PCG Framework** in Unreal Engine 5.2, this plugin has become a quick and lightweight way to prototype procedural generation **before** integrating PCG (even if I prefer using my own tools)

---

## Features

- Helps create **linear maps** with a clear start and end.
- Supports **branches**, but it is not meant to generate complex dungeons like *The Binding of Isaac* or *Lethal Company*.  
  It is designed as a “go forward” generation system.
- Fairly **modular**, allowing you to:
  - Create **biomes**
  - Add **elevation points**
  - Handle **corners** and path variations
  - Spawn **decor**, **traps**, and **objects**
- Control which **tile can spawn after the current one**.
- Optionally **trigger the generation of the rest of the dungeon later**, so you don’t have to generate everything at once if it’s not needed.

---

## To-Do

- Fix **overlapping tiles** that can occur when two branches merge  
  → This would make it possible to have less strictly linear layouts.
- Add **contextual spawning**, checking for a tile type instead of referencing specific tiles in the tile Blueprint  
  → This might make the plugin a bit heavier, but also more modular.
- Add the ability to **change Post Process Volume settings and game audio** when changing biome.
- And many more ideas to come…
