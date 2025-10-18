#!/bin/bash
# install-build-scripts.sh
# Install all build scripts to ~/gambatte-k2/

set -e

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}=========================================${NC}"
echo -e "${BLUE}Installing Gambatte-K2 Build Scripts${NC}"
echo -e "${BLUE}=========================================${NC}"
echo ""

# Determine project directory
PROJECT_DIR="${1:-~/gambatte-k2}"
PROJECT_DIR="${PROJECT_DIR/#\~/$HOME}"

# Create project directory if it doesn't exist
mkdir -p "$PROJECT_DIR"

echo "Installing scripts to: $PROJECT_DIR"
echo ""

# Create each script
echo -e "${YELLOW}Creating scripts...${NC}"

# Note: In practice, you would paste the actual script content here
# For now, I'll show you the structure

cat > "$PROJECT_DIR/setup-environment.sh" << 'SCRIPT_EOF'
# Paste the content of setup-environment.sh here
SCRIPT_EOF

cat > "$PROJECT_DIR/build-gambatte.sh" << 'SCRIPT_EOF'
# Paste the content of build-gambatte.sh here
SCRIPT_EOF

cat > "$PROJECT_DIR/quick-build.py" << 'SCRIPT_EOF'
# Paste the content of quick-build.py here
SCRIPT_EOF

cat > "$PROJECT_DIR/deploy-to-kindle.py" << 'SCRIPT_EOF'
# Paste the content of deploy-to-kindle.py here
SCRIPT_EOF

cat > "$PROJECT_DIR/create-release.sh" << 'SCRIPT_EOF'
# Paste the content of create-release.sh here
SCRIPT_EOF

cat > "$PROJECT_DIR/BUILD_SYSTEM_README.md" << 'SCRIPT_EOF'
# Paste the content of BUILD_SYSTEM_README.md here
SCRIPT_EOF

# Make scripts executable
chmod +x "$PROJECT_DIR"/*.sh
chmod +x "$PROJECT_DIR"/*.py

echo -e "${GREEN}✓ Scripts installed${NC}"
echo ""
echo "Installed files:"
ls -lh "$PROJECT_DIR"/*.sh "$PROJECT_DIR"/*.py "$PROJECT_DIR"/*.md 2>/dev/null | awk '{print "  " $9, "(" $5 ")"}'

echo ""
echo -e "${GREEN}=========================================${NC}"
echo -e "${GREEN}✓ Installation Complete!${NC}"
echo -e "${GREEN}=========================================${NC}"
echo ""
echo "Next steps:"
echo "  1. cd $PROJECT_DIR"
echo "  2. Read BUILD_SYSTEM_README.md"
echo "  3. Run ./setup-environment.sh (first time only)"
echo "  4. Run ./build-gambatte.sh"
echo ""
