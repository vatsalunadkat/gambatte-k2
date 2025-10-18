# Gambatte-K2 Build System

Automated build scripts for cross-compiling gambatte-k2 for Kindle devices.

## Overview

This build system provides:
- ✅ Complete environment setup from scratch
- ✅ Full project builds
- ✅ Quick incremental builds for single-file changes
- ✅ Automated deployment to Kindle
- ✅ Release package creation

## Scripts

### 1. `setup-environment.sh` - One-Time Setup
**Run this ONCE after a fresh Ubuntu install or system reboot**

```bash
chmod +x setup-environment.sh
./setup-environment.sh
```

This script will:
- Install all required packages (build tools, GTK dev headers, etc.)
- Clone and build koxtoolchain (kindlehf) - takes ~30 minutes
- Install Kindle SDK
- Build FBInk library
- Build gambatte-libretro core
- Set up environment variables in `~/.bashrc`

**After running, restart your terminal or run:** `source ~/.bashrc`

---

### 2. `build-gambatte.sh` - Full Project Build
**Run this to build your project from scratch or after major changes**

```bash
chmod +x build-gambatte.sh
./build-gambatte.sh
```

This script will:
- Copy all dependencies (libretro.h, libfbink.a, etc.)
- Generate main_ui.h from main.ui
- Create necessary build files
- Compile all source files
- Link and strip the final binary

**Output:** `~/gambatte-k2/gambatte-k2-armhf`

---

### 3. `quick-build.py` - Fast Incremental Build
**Use this when you've only modified `gambatte-k2.c`**

```bash
chmod +x quick-build.py

# Just rebuild
./quick-build.py

# Rebuild and deploy to Kindle
./quick-build.py --deploy --kindle-ip 192.168.1.100
```

**Benefits:**
- Only recompiles changed file (~2-3 seconds)
- Skips unchanged dependencies
- Optional automatic deployment
- Perfect for rapid iteration

**Options:**
- `--project-dir PATH` - Specify project directory (default: ~/gambatte-k2)
- `--deploy` - Deploy to Kindle after building
- `--kindle-ip IP` - Kindle IP address for deployment

---

### 4. `deploy-to-kindle.py` - Deploy to Kindle
**Deploy your compiled binary to a Kindle device**

```bash
chmod +x deploy-to-kindle.py

# Deploy everything
./deploy-to-kindle.py 192.168.1.100

# Deploy binary only (skip core library)
./deploy-to-kindle.py 192.168.1.100 --binary-only
```

**Requirements:**
- Kindle must be connected via WiFi or USB networking
- SSH access enabled on Kindle
- You should have SSH keys set up (or will be prompted for password)

**What it does:**
- Tests SSH connection
- Creates target directory
- Copies binary (and optionally core library)
- Sets execute permissions
- Verifies deployment

---

### 5. `create-release.sh` - Create Public Release
**Package everything for public distribution**

```bash
chmod +x create-release.sh
./create-release.sh
```

**Prompts for:**
- Version number (or uses date if blank)

**Creates:**
- `gambatte-k2-vYYYYMMDD.zip` - Complete release package
- `gambatte-k2-vYYYYMMDD.zip.sha256` - Checksum file

**Package includes:**
- Binary (gambatte-k2-armhf)
- Core library (gambatte_libretro.so)
- Configuration files (config.xml, menu.json)
- Helper scripts (bluetooth.sh, shortcut)
- Documentation (README.md, INSTALL.txt)
- Empty state directory
- LICENSE (if present)

---

## Typical Workflows

### Initial Setup (First Time)
```bash
# 1. Set up build environment (one time only)
./setup-environment.sh
source ~/.bashrc

# 2. Clone your gambatte-k2 fork
cd ~
git clone https://github.com/YOUR_USERNAME/gambatte-k2.git

# 3. Build the project
cd ~/gambatte-k2
./build-gambatte.sh
```

### Daily Development
```bash
# Edit gambatte-k2.c with your changes
nano ~/gambatte-k2/gambatte-k2.c

# Quick rebuild and deploy
./quick-build.py --deploy --kindle-ip 192.168.1.100

# Test on Kindle immediately
```

### Creating a Release
```bash
# 1. Make sure everything is committed
git add -A
git commit -m "Release v1.0"
git push

# 2. Build fresh
./build-gambatte.sh

# 3. Create release package
./create-release.sh

# 4. Upload the ZIP to GitHub releases
```

### After System Reboot
```bash
# Environment variables are already set in ~/.bashrc
# Just start building:
cd ~/gambatte-k2
./quick-build.py
```

---

## Directory Structure

```
~
├── gambatte-k2/              # Your project
│   ├── gambatte-k2.c         # Modified source
│   ├── gambatte-k2-armhf     # Compiled binary
│   ├── setup-environment.sh  # Setup script
│   ├── build-gambatte.sh     # Full build script
│   ├── quick-build.py        # Fast rebuild script
│   ├── deploy-to-kindle.py   # Deploy script
│   └── create-release.sh     # Release packager
│
├── koxtoolchain/             # ARM toolchain
│   └── (automatically created)
│
├── kindle-sdk/               # Kindle SDK
│   └── (automatically created)
│
├── FBInk/                    # FBInk library
│   └── (automatically created)
│
├── gambatte-libretro/        # Emulator core
│   └── (automatically created)
│
└── x-tools/                  # Built toolchain
    └── arm-kindlehf-linux-gnueabihf/
```

---

## Troubleshooting

### "Toolchain not found" error
```bash
# Rebuild the toolchain
cd ~/koxtoolchain
./gen-tc.sh kindlehf
```

### "Binary not found" error
```bash
# Run a full build first
./build-gambatte.sh
```

### SSH connection fails
```bash
# Test connection manually
ssh root@192.168.1.100

# If password prompt, set up SSH keys:
ssh-keygen
ssh-copy-id root@192.168.1.100
```

### Build errors after Ubuntu update
```bash
# Reinstall packages
sudo apt-get update
sudo apt-get install --reinstall build-essential libgtk2.0-dev
```

---

## Environment Variables

These are automatically added to `~/.bashrc` by `setup-environment.sh`:

```bash
export PATH=~/x-tools/arm-kindlehf-linux-gnueabihf/bin:$PATH
export PKG_CONFIG_PATH=~/x-tools/arm-kindlehf-linux-gnueabihf/arm-kindlehf-linux-gnueabihf/sysroot/usr/lib/pkgconfig
export PKG_CONFIG_SYSROOT_DIR=~/x-tools/arm-kindlehf-linux-gnueabihf/arm-kindlehf-linux-gnueabihf/sysroot
```

---

## Performance

**Full Build:** ~20-30 seconds
**Quick Build:** ~2-3 seconds
**Deploy:** ~5-10 seconds (depending on network)

---

## Requirements

- Ubuntu 20.04 LTS or newer
- ~10 GB free disk space
- Internet connection (for initial setup)
- Python 3.6+
- Kindle with SSH access

---

## Credits

Build system follows the official [KindleModding.org](https://kindlemodding.org) guidelines.

---

## License

These build scripts are provided as-is for building gambatte-k2.
