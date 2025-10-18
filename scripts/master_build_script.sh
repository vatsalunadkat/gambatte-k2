#!/bin/bash
# build.sh - Master build script with all options
# One script to rule them all!

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

# Default values
ACTION=""
KINDLE_IP=""
PROJECT_DIR=~/gambatte-k2

show_help() {
    echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║  Gambatte-K2 Master Build Script     ║${NC}"
    echo -e "${BLUE}╚════════════════════════════════════════╝${NC}"
    echo ""
    echo "Usage: $0 [command] [options]"
    echo ""
    echo -e "${CYAN}Commands:${NC}"
    echo "  setup         - Initial environment setup (run once)"
    echo "  build         - Full project build"
    echo "  quick         - Quick rebuild (gambatte-k2.c only)"
    echo "  deploy        - Deploy to Kindle"
    echo "  release       - Create release ZIP"
    echo "  clean         - Clean build artifacts"
    echo "  status        - Show build system status"
    echo ""
    echo -e "${CYAN}Options:${NC}"
    echo "  --kindle-ip IP    Kindle IP address (for deploy)"
    echo "  --project-dir DIR Project directory (default: ~/gambatte-k2)"
    echo ""
    echo -e "${CYAN}Examples:${NC}"
    echo "  $0 setup                              # Initial setup"
    echo "  $0 build                              # Full build"
    echo "  $0 quick                              # Quick rebuild"
    echo "  $0 quick --kindle-ip 192.168.1.100    # Rebuild + deploy"
    echo "  $0 deploy --kindle-ip 192.168.1.100   # Deploy only"
    echo "  $0 release                            # Create release"
    echo "  $0 status                             # Check status"
    echo ""
}

show_status()