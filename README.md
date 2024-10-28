# Think Engine

**Think Engine** is a personal game engine learning repository structured with inspiration from Unreal Engine’s architecture and standards. This project serves as a sandbox for exploring graphics programming, Vulkan API, and the design patterns employed in high-performance engines. The aim is to gain hands-on experience with engine development concepts while building a modular and scalable framework.
![ThinkEngine](./Docs/ThinkEngineSplash.png)

## Current State

- **VS Code Integration**: Complete VS Code setup with CMake and custom tasks for configuring, building and debugging the project.
- **VK Guide Legacy Completion**: Finished implementation based on the legacy version of [Vulkan Guide](https://vkguide.dev/), with ongoing work to add extra chapters and extend functionality.

## TODO / What Needs to Be Done

- [ ] Complete the dynamic rendering version from [Vulkan Guide](https://vkguide.dev/).
- [ ] Refactor code structure: split into smaller classes, such as `Device`, `Renderer`, and `Vulkan`, for improved readability and modularity.
- [ ] Sh!t ton of other things.


## Third-Party Libraries

This repository includes the following third-party libraries for added functionality:

- **argparse** – Command-line argument parsing
- **fmt** – Fast formatting library for strings and output
- **glm** – Mathematics library for graphics programming
- **imgui** – Immediate Mode GUI for debug overlays and controls
- **sdl3** – Cross-platform input and window management
- **stbImage** – Image loading library for textures
- **tinyobjloader** – OBJ file loader for basic 3D model support
- **vulkan** – Vulkan API for graphics rendering
- **volk** – Vulkan meta loader
- **vma** – Vulkan Memory Allocator for optimized memory management
- **vkbootstrap** – Utility for build and environment setup


## Platforms

- **Linux**: Primary development and testing platform. All features are verified to work on Linux.
- **Windows**: Expected to work, though not fully tested. Minor adjustments may be needed for compatibility.


---
This project is a continuous work-in-progress, with a primary focus on learning and experimentation. Feedback, contributions, and suggestions are welcome!
