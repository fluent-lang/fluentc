<div align="center">
    <img src="assets/logo.png" height="60" width="60">
    <h1>The Fluent Language Compiler</h1>
    Fluent is a modern and blazing-fast programming language.
</div>

---

## 👋 Welcome

Welcome to the official Fluent repository! Here, you will find the source code of the Fluent Language Compiler. Have fun!

---

## 🎆 Installation

To install Fluent, you can download the official Fluent installer from the **Releases** pages.
Once the installer shows that the installation was successful, you may need to restart your terminal for changes to take effect.

- **On Windows**: Just close and re-open the terminal (CMD, PowerShell, etc.)
- **On Linux/macOS**: Execute `source ~/.bashrc` or `source ~/.zshrc` depending on your shell

---

## 📚 Supported Operating Systems

Most of the Fluent features are supported on the following operating systems:

- **Windows 10+** (32, 64-bit & ARM)
- **Linux** (x86_64, ARM64)
- **macOS** (x86_64, ARM64)
- **Almost all BSD-based systems** (e.g. FreeBSD, OpenBSD, NetBSD)
- **Android** (ARM64)
- **iOS** (ARM64)
- **Raspberry Pi** (ARM64)

Requirements for compilation:
- **Windows**: LLVM, Clang, and Visual Studio Build Tools with C++ support installed.
- **Mac-O systems**: LLVM and Clang installed.
- **Other POSIX-compliant systems**: GCC (Commonly pre-installed) and LLVM (Clang is not required).

> **Note**: Even though Windows is supported natively, it is highly recommended to use WSL instead
> because it is much faster to set up and use.

---

## 📦 Contributions

Contributions are welcome! If you'd like to contribute to the Fluent language, please read the [CONTRIBUTING.md](CONTRIBUTING.md) file for more information.

---

## 🎲 Building from Source

To build Fluent from source into an executable, you need to execute either one of the **build scripts**:

- **On Windows**: `build.bat`
- **On Linux/macOS**: `build.sh`

After the build process is complete, you will find the executable in the `bin/` directory.

---

## 🔒 Security

Please refer to [SECURITY.md](SECURITY.md) for more information on how to report security vulnerabilities.

---

## 📝 License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for more information.

```
Copyright (C) 2025 Rodrigo R. & All Fluent Contributors
This program comes with ABSOLUTELY NO WARRANTY; for details type `fluent license`.
This is free software, and you are welcome to redistribute it under certain conditions;
type `fluent license --full` for details.
```