# Modular C++ Systems Framework (Zombie Co-op Multiplayer Prototype)

A high-performance, system-driven gameplay prototype developed in Unreal Engine 5 C++. This project focuses on decoupled, component-based architecture designed for multiplayer scalability.

Key Engineering Highlights:

* Modular Weapon System: Implemented a base C++ weapon class supporting extensible fire logic, automated targeting via physics overlaps, and event-driven ammo management.

* Data-Driven Upgrade Manager: Developed a robust UUpgradeManager component that parses Data Tables to dynamically generate and apply gameplay modifiers (Movement, Combat, XP) at runtime.

* Component-Based Character: Utilized a clean "Manager-Component" pattern to separate concerns between input handling, attributes, and inventory systems.

* Event-Driven UI/UX: Leveraged Dynamic Multi-cast Delegates to drive UI updates, ensuring zero tight coupling between game logic and the HUD.

* <img width="2751" height="1602" alt="image" src="https://github.com/user-attachments/assets/a9f5d3ed-f791-414c-ae61-c6ee74db1f2c" />
