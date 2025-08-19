<div align="center">
  <picture>
    <source media="(prefers-color-scheme: light)" srcset="https://github.com/Interactive-Echoes/IEResources/raw/master/IE-Brand-Kit/IE-Logo-Alt-NoBg.png">
    <source media="(prefers-color-scheme: dark)" srcset="https://github.com/Interactive-Echoes/IEResources/raw/master/IE-Brand-Kit/IE-Logo-NoBg.png">
  <img alt="IELogo" width="128">
  </picture>
</div>

# IECore

**IECore** is a cross-platform library for Linux, Windows, and macOS that leverages ImGui as its user interface. It serves as the core framework for all Interactive Echoes (IE) applications, offering a plug-and-play setup with pre-configured entry points, making it simple to start developping C++ applications.  

> [!IMPORTANT] 
> For installation and integration instructions, please refer to the Wiki here: [IECore Wiki](https://github.com/Interactive-Echoes/IECore/wiki)

## Feature Highlight
- **Abstracted Renderer Class**: Provides a unified interface for different rendering backends.
- **Robust Logging**: Offers detailed logging capabilities for debugging and monitoring.
- **Utilities**: Provides various helpful tools and functions for application development.
- **ImGui Extension Logic**: Enhances ImGui with additional functionality and customizations.
> [!NOTE]
> Currently, only Vulkan is implemented as a rendering backend, but support for additional backends will be added in the future. 

## Third-Party Libraries Used
- [Dear ImGui](https://github.com/ocornut/imgui)
- [stb](https://github.com/nothings/stb)

## Contribution
Contributors are welcomed to this open-source project. Any feedback or assistance, whether in coding, packaging, documentation, design, or testing, is greatly appreciated. 

## License
This work is licensed under the [SPDX-License-Identifier: GPL-2.0-only](./LICENSE).
