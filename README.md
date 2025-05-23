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

## 📚 Supported architectures

Not all architectures are supported by the Fluent compiler.
The following architectures are supported:

| Operating System | Architecture | Supported               |
|------------------|--------------|-------------------------|
| Linux            | x86_64       | ✅                       |
| Linux            | x86          | ✅                       |
| Linux            | ARM          | ✅                       |
| Linux            | ARM64        | ✅                       |
| macOS            | x86_64       | Still implementing      |
| macOS            | ARM64        | Still implementing      |
| Windows          | x86_64       | Scheduled (after macOS) |
| Windows          | x86          | Scheduled (after macOS) |
| Windows          | ARM          | Scheduled (after macOS) |
| Windows          | ARM64        | Scheduled (after macOS) |

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