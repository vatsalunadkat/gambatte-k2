# Gambatte-K2 Build System - Quick Start Guide

## 📋 Prerequisites

- Ubuntu 20.04 LTS (fresh install or after reboot)
- Your gambatte-k2 fork cloned to `~/gambatte-k2`
- ~10 GB free disk space
- Kindle Gen 10 with SSH access

---

## 🚀 One-Time Setup (After Fresh Install)

### Step 1: Save All Scripts

Save these 6 scripts to your `~/gambatte-k2/` directory:

1. **setup-environment.sh** - Environment setup
2. **build-gambatte.sh** - Full build
3. **quick-build.py** - Fast incremental build
4. **deploy-to-kindle.py** - Deploy to Kindle
5. **create-release.sh** - Create release ZIP
6. **BUILD_SYSTEM_README.md** - Full documentation

Make them executable:
```bash
cd ~/gambatte-k2
chmod +x *.sh *.py
```

### Step 2: Run Initial Setup

```bash
cd ~/gambatte-k2
./setup-environment.sh
```

⏱️ **This takes ~30-40 minutes** (compiles toolchain)

☕ **Grab a coffee!** This downloads and compiles:
- ARM toolchain (koxtoolchain)
- Kindle SDK
- FBInk library
- gambatte-libretro core

### Step 3: Restart Terminal

```bash
# Close and reopen terminal, OR:
source ~/.bashrc
```

### Step 4: Initial Build

```bash
cd ~/gambatte-k2
./build-gambatte.sh
```

⏱️ **Takes ~20-30 seconds**

✅ **You're done with setup!** This only needs to be done once.

---

## 💻 Daily Development Workflow

### Scenario 1: Quick Code Change

You modified only `gambatte-k2.c`:

```bash
# Edit the file
nano ~/gambatte-k2/gambatte-k2.c

# Quick rebuild (2-3 seconds)
./quick-build.py

# Or rebuild AND deploy to Kindle
./quick-build.py --deploy --kindle-ip 192.168.1.100
```

### Scenario 2: Major Changes

Modified multiple files or added new dependencies:

```bash
# Full rebuild
./build-gambatte.sh
```

### Scenario 3: Deploy to Kindle

```bash
# Deploy binary to Kindle
./deploy-to-kindle.py 192.168.1.100

# Or just binary (skip core library)
./deploy-to-kindle.py 192.168.1.100 --binary-only
```

### Scenario 4: Create Public Release

```bash
# Create release ZIP
./create-release.sh

# Enter version when prompted (or press Enter for date-based)
# Output: gambatte-k2-vYYYYMMDD.zip
```

---

## 🔄 After System Reboot

**Good news:** Everything is already set up!

```bash
# Just build as normal
cd ~/gambatte-k2
./quick-build.py
```

The environment variables are in `~/.bashrc`, so they load automatically.

---

## 📁 Expected File Structure

After setup, you should have:

```
~/
├── gambatte-k2/               ← Your project
│   ├── gambatte-k2.c          ← Your modified source
│   ├── file_picker.c
│   ├── gray_shm.c
│   ├── main.ui
│   ├── setup-environment.sh    ← Build scripts (you added these)
│   ├── build-gambatte.sh
│   ├── quick-build.py
│   ├── deploy-to-kindle.py
│   ├── create-release.sh
│   ├── BUILD_SYSTEM_README.md
│   └── gambatte-k2-armhf      ← Compiled binary (after build)
│
├── koxtoolchain/              ← Auto-created by setup
├── kindle-sdk/
├── FBInk/
├── gambatte-libretro/
└── x-tools/                   ← Compiled toolchain
```

---

## 🎯 Common Commands Cheat Sheet

```bash
# First time setup (once ever)
./setup-environment.sh

# Full build
./build-gambatte.sh

# Quick rebuild (gambatte-k2.c only)
./quick-build.py

# Quick rebuild + deploy
./quick-build.py --deploy --kindle-ip 192.168.1.100

# Deploy to Kindle
./deploy-to-kindle.py 192.168.1.100

# Create release ZIP
./create-release.sh

# Clean build
cd ~/gambatte-k2
make clean
./build-gambatte.sh
```

---

## 🐛 Troubleshooting

### "Command not found: arm-kindlehf-linux-gnueabihf-gcc"

```bash
source ~/.bashrc
# or restart terminal
```

### "Binary not found"

```bash
./build-gambatte.sh  # Run full build first
```

### "Cannot connect to Kindle"

```bash
# Test SSH connection
ssh root@192.168.1.100

# Make sure:
# 1. Kindle is on WiFi
# 2. SSH is enabled
# 3. IP is correct
```

### Build fails with GTK errors

```bash
# Reinstall GTK dev headers
sudo apt-get install --reinstall libgtk2.0-dev
```

---

## ⚡ Performance

| Task | Time |
|------|------|
| Initial setup | 30-40 min (one time) |
| Full build | 20-30 sec |
| Quick build | 2-3 sec |
| Deploy to Kindle | 5-10 sec |
| Create release | 10-15 sec |

---

## 📚 Need More Help?

Read the full documentation:
```bash
cat BUILD_SYSTEM_README.md
```

---

## ✅ Verification

After setup, verify everything works:

```bash
# Check toolchain
arm-kindlehf-linux-gnueabihf-gcc --version

# Check environment
echo $PATH | grep arm-kindlehf

# Try a build
cd ~/gambatte-k2
./build-gambatte.sh

# Check binary
file gambatte-k2-armhf
# Should output: "ELF 32-bit LSB executable, ARM, EABI5..."
```

---

## 🎉 You're Ready!

Start making changes to `gambatte-k2.c` and use `./quick-build.py` for rapid iteration!

Happy coding! 🚀
