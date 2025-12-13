<h1 align="center">🚀 libcsp-works</h1>

<p align="center">
  <b>Rust • Python • Embedded experiments with CubeSat Space Protocol</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/language-C%20%7C%20Rust%20%7C%20Python-blue" />
  <img src="https://img.shields.io/badge/domain-Embedded%20%7C%20Space-orange" />
  <img src="https://img.shields.io/badge/status-Work%20in%20Progress-yellow" />
  <img src="https://img.shields.io/badge/license-MIT-green" />
</p>

---

## ✨ Overview

libcsp-works is a workspace and experimental playground for working with the CubeSat Space Protocol (CSP) across multiple ecosystems. The project focuses on integrating the C-based libcsp library with modern languages and environments such as Rust, Python, and embedded systems, while keeping the setup reproducible, automation-friendly, and suitable for real-world embedded and space applications.

---

## 🎯 Goals

- Create safe and ergonomic Rust bindings for libcsp
- Provide Python-accessible APIs for rapid prototyping and tooling
- Enable CSP usage on embedded targets (ARM, RISC-V, etc.)
- Collect experiments, tools, and example applications in a single workspace
- Support automation and reproducibility via Makefile helpers

---

## 📂 Project Structure

```
libcsp-works/
├── .github/
│   └── workflows/
├── rust-server/
├── embedded-client/
├── thirdparty/
├── .gitmodules
├── Makefile
└── README.md
```

---

## 🧰 Requirements

Git, C compiler (gcc or clang), Make, Rust & Cargo, Python 3, and optional embedded cross-compilation toolchains.

---

## ⚡ Quick Start

git clone https://github.com/dogusyuksel/libcsp-works.git
cd libcsp-works
git submodule update --init --recursive
make create-bindings
make build-server
make console

---

## 🦀 Rust Usage

```
cd rust-server
make build-docker
make create-bindings
make build-server
```

---

## 🐍 Embedded Usage

```
cd embedded-client
make build-docker
make all
```

---

## 🛰️ What is CSP?

CubeSat Space Protocol (CSP) is a lightweight networking protocol designed for resource-constrained systems such as CubeSats and embedded devices.

---

## 🛣️ Roadmap

Complete Rust API coverage, Python examples, embedded board demos, CSP simulations, and CI automation.

---

## 🤝 Contributing

Fork, create a branch, commit changes, and open a pull request.

---

## 📜 License

MIT License.
