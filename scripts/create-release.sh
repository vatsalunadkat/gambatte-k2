#!/bin/bash
# create-release.sh
# Create a release ZIP file for public distribution

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

PROJECT_DIR=~/gambatte-k2
RELEASE_DIR=/tmp/gambatte-k2-release

echo -e "${BLUE}=========================================${NC}"
echo -e "${BLUE}Creating Public Release${NC}"
echo -e "${BLUE}=========================================${NC}"
echo ""

# Get version from user or use date
read -p "Enter version (or press Enter for date-based): " VERSION
if [ -z "$VERSION" ]; then
    VERSION=$(date +%Y%m%d)
fi

RELEASE_NAME="gambatte-k2-v${VERSION}"
RELEASE_ZIP="${RELEASE_NAME}.zip"

echo "Release version: $VERSION"
echo "Output file: $RELEASE_ZIP"
echo ""

# Check if binary exists
if [ ! -f "$PROJECT_DIR/gambatte-k2-armhf" ]; then
    echo -e "${RED}Error: Binary not found!${NC}"
    echo "Run ./build-gambatte.sh first"
    exit 1
fi

# Create release directory structure
echo -e "${YELLOW}Step 1: Creating release directory...${NC}"
rm -rf "$RELEASE_DIR"
mkdir -p "$RELEASE_DIR/$RELEASE_NAME"

# Copy binary
echo -e "${YELLOW}Step 2: Copying binary...${NC}"
cp "$PROJECT_DIR/gambatte-k2-armhf" "$RELEASE_DIR/$RELEASE_NAME/"
echo "  ✓ Binary copied"

# Copy libretro core
echo -e "${YELLOW}Step 3: Copying gambatte-libretro core...${NC}"
if [ -f "$PROJECT_DIR/gambatte_libretro.so" ]; then
    cp "$PROJECT_DIR/gambatte_libretro.so" "$RELEASE_DIR/$RELEASE_NAME/"
    echo "  ✓ Core copied"
else
    echo -e "  ${YELLOW}⚠ Warning: gambatte_libretro.so not found${NC}"
fi

# Create state directory
mkdir -p "$RELEASE_DIR/$RELEASE_NAME/state"
echo "  ✓ State directory created"

# Create config files if they don't exist
echo -e "${YELLOW}Step 4: Creating configuration files...${NC}"

# config.xml
if [ ! -f "$PROJECT_DIR/config.xml" ]; then
    cat > "$RELEASE_DIR/$RELEASE_NAME/config.xml" << 'EOF'
<?xml version="1.0" encoding="UTF-8"?>
<config>
    <item>
        <key>emulator_path</key>
        <value>/mnt/us/extensions/gambatte-k2/gambatte-k2-armhf</value>
    </item>
    <item>
        <key>core_path</key>
        <value>/mnt/us/extensions/gambatte-k2/gambatte_libretro.so</value>
    </item>
</config>
EOF
else
    cp "$PROJECT_DIR/config.xml" "$RELEASE_DIR/$RELEASE_NAME/"
fi
echo "  ✓ config.xml"

# menu.json
if [ ! -f "$PROJECT_DIR/menu.json" ]; then
    cat > "$RELEASE_DIR/$RELEASE_NAME/menu.json" << 'EOF'
{
    "items": [
        {
            "name": "Gambatte-K2",
            "priority": 1,
            "action": "/mnt/us/extensions/gambatte-k2/gambatte-k2-armhf",
            "params": "",
            "exitmenu": false,
            "refresh": false,
            "if": "sh /mnt/us/extensions/gambatte-k2/check.sh"
        }
    ]
}
EOF
else
    cp "$PROJECT_DIR/menu.json" "$RELEASE_DIR/$RELEASE_NAME/"
fi
echo "  ✓ menu.json"

# bluetooth.sh
if [ ! -f "$PROJECT_DIR/bluetooth.sh" ]; then
    cat > "$RELEASE_DIR/$RELEASE_NAME/bluetooth.sh" << 'EOF'
#!/bin/sh
# Enable bluetooth for gamepad support
lipc-set-prop com.lab126.cmd wirelessEnable 1
EOF
    chmod +x "$RELEASE_DIR/$RELEASE_NAME/bluetooth.sh"
else
    cp "$PROJECT_DIR/bluetooth.sh" "$RELEASE_DIR/$RELEASE_NAME/"
fi
echo "  ✓ bluetooth.sh"

# shortcut script
cat > "$RELEASE_DIR/$RELEASE_NAME/shortcut_gambatte-k2.sh" << 'EOF'
#!/bin/sh
cd /mnt/us/extensions/gambatte-k2
./gambatte-k2-armhf
EOF
chmod +x "$RELEASE_DIR/$RELEASE_NAME/shortcut_gambatte-k2.sh"
echo "  ✓ shortcut_gambatte-k2.sh"

# Create README
echo -e "${YELLOW}Step 5: Creating README...${NC}"
cat > "$RELEASE_DIR/$RELEASE_NAME/README.md" << EOF
# Gambatte-K2 v${VERSION}

Game Boy / Game Boy Color emulator for Kindle e-ink devices.

## Installation

1. Connect your Kindle via USB
2. Copy the entire \`$RELEASE_NAME\` folder to \`/mnt/us/extensions/gambatte-k2/\`
3. Safely eject your Kindle
4. Launch via KUAL or the shortcut

## Features

- Game Boy and Game Boy Color support
- GTK2 UI with touch controls
- Direct framebuffer rendering (FBInk mode)
- Audio support via Bluetooth
- Save states
- Optimized for ARM Cortex-A7 with NEON

## Requirements

- Jailbroken Kindle
- Firmware 5.16.3 or later (for armhf support)
- KUAL (Kindle Unified Application Launcher)

## Usage

### Via KUAL
Navigate to Gambatte-K2 in KUAL menu

### Via Shortcut
Copy \`shortcut_gambatte-k2.sh\` to \`/mnt/us/documents\` to create a library shortcut

### Via SSH
\`\`\`bash
ssh root@<kindle-ip>
cd /mnt/us/extensions/gambatte-k2
./gambatte-k2-armhf
\`\`\`

## Controls

Touch controls are displayed on screen. You can also use:
- Bluetooth gamepad (pair via bluetooth.sh)
- Keyboard (if connected via USB OTG)

## Save States

Save states are stored in the \`state/\` directory.

## ROMs

Place your .gb and .gbc ROM files in any directory on your Kindle.
Use the "Open" button in the UI to browse for ROMs.

## Troubleshooting

### App won't start
- Ensure binary has execute permissions: \`chmod +x gambatte-k2-armhf\`
- Check that gambatte_libretro.so is present

### No audio
- Run \`./bluetooth.sh\` to enable Bluetooth
- Pair your Bluetooth headphones/speaker

### Performance issues
- Try FBInk mode for better performance
- Ensure no other applications are running

## Build Info

- Version: ${VERSION}
- Built: $(date)
- Toolchain: koxtoolchain (kindlehf)
- Target: ARM Cortex-A7, NEON, hard float
- Optimizations: -O3

## Credits

- Gambatte core: libretro/gambatte-libretro
- FBInk: NiLuJe/FBInk
- Original port: Based on gambatte-k2

## License

See LICENSE file for details.
EOF
echo "  ✓ README.md created"

# Create LICENSE if not exists
if [ -f "$PROJECT_DIR/LICENSE" ]; then
    cp "$PROJECT_DIR/LICENSE" "$RELEASE_DIR/$RELEASE_NAME/"
    echo "  ✓ LICENSE copied"
fi

# Create installation instructions
echo -e "${YELLOW}Step 6: Creating INSTALL.txt...${NC}"
cat > "$RELEASE_DIR/$RELEASE_NAME/INSTALL.txt" << EOF
GAMBATTE-K2 INSTALLATION INSTRUCTIONS
======================================

Quick Start:
1. Connect Kindle via USB
2. Copy this entire folder to: /mnt/us/extensions/gambatte-k2/
3. Eject Kindle safely
4. Launch from KUAL menu

Directory Structure:
/mnt/us/extensions/gambatte-k2/
  ├── gambatte-k2-armhf          (main binary)
  ├── gambatte_libretro.so       (emulator core)
  ├── config.xml                 (configuration)
  ├── menu.json                  (KUAL menu)
  ├── bluetooth.sh               (bluetooth helper)
  ├── shortcut_gambatte-k2.sh    (launcher)
  ├── state/                     (save states directory)
  └── README.md                  (documentation)

First Run:
- Launch from KUAL
- Click "Open" to browse for ROM files
- Select a .gb or .gbc file
- Use on-screen touch controls

For detailed instructions, see README.md

Support: https://github.com/YOUR_USERNAME/gambatte-k2
EOF
echo "  ✓ INSTALL.txt created"

# Get file sizes
echo ""
echo -e "${YELLOW}Step 7: File information...${NC}"
cd "$RELEASE_DIR/$RELEASE_NAME"
echo "Binary size: $(ls -lh gambatte-k2-armhf | awk '{print $5}')"
if [ -f "gambatte_libretro.so" ]; then
    echo "Core size: $(ls -lh gambatte_libretro.so | awk '{print $5}')"
fi

# Create ZIP
echo ""
echo -e "${YELLOW}Step 8: Creating ZIP archive...${NC}"
cd "$RELEASE_DIR"
zip -r "$RELEASE_ZIP" "$RELEASE_NAME" > /dev/null 2>&1
echo "  ✓ ZIP created"

# Move to project directory
mv "$RELEASE_ZIP" "$PROJECT_DIR/"
ZIP_SIZE=$(ls -lh "$PROJECT_DIR/$RELEASE_ZIP" | awk '{print $5}')

# Calculate SHA256
echo ""
echo -e "${YELLOW}Step 9: Generating checksums...${NC}"
cd "$PROJECT_DIR"
sha256sum "$RELEASE_ZIP" > "${RELEASE_ZIP}.sha256"
echo "  ✓ SHA256: $(cat ${RELEASE_ZIP}.sha256 | awk '{print $1}')"

# Clean up
rm -rf "$RELEASE_DIR"

# Summary
echo ""
echo -e "${GREEN}=========================================${NC}"
echo -e "${GREEN}✓ Release Created Successfully!${NC}"
echo -e "${GREEN}=========================================${NC}"
echo ""
echo "Release file: $PROJECT_DIR/$RELEASE_ZIP"
echo "Size: $ZIP_SIZE"
echo "Checksum: ${RELEASE_ZIP}.sha256"
echo ""
echo "Contents:"
echo "  • gambatte-k2-armhf (optimized binary)"
echo "  • gambatte_libretro.so (emulator core)"
echo "  • Configuration files"
echo "  • Documentation (README.md, INSTALL.txt)"
echo "  • Installation scripts"
echo ""
echo "Ready for distribution!"