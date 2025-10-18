#!/bin/bash

# Debug run script for gambatte-k2
# This script helps run the emulator and capture all output

LOG_DIR="/mnt/us/extensions/gambatte-k2"
STDERR_LOG="$LOG_DIR/stderr.log"
STDOUT_LOG="$LOG_DIR/stdout.log"
COMBINED_LOG="$LOG_DIR/combined.log"
DEBUG_LOG="$LOG_DIR/gambatte-debug.log"

# Create log directory if it doesn't exist
mkdir -p "$LOG_DIR"

echo "=== Gambatte-K2 Debug Runner ==="
echo "Logs will be saved to: $LOG_DIR"
echo ""

# Clean old logs
echo "Cleaning old logs..."
rm -f "$STDERR_LOG" "$STDOUT_LOG" "$COMBINED_LOG" "$DEBUG_LOG"

# Check if binary exists
if [ ! -f "./gambatte-k2" ]; then
    echo "ERROR: gambatte-k2 binary not found in current directory"
    exit 1
fi

# Make sure it's executable
chmod +x ./gambatte-k2

echo "Starting gambatte-k2..."
echo "Press Ctrl+C to stop"
echo ""

# Run the emulator and capture all output
./gambatte-k2 2>"$STDERR_LOG" 1>"$STDOUT_LOG" &
PID=$!

echo "gambatte-k2 started with PID: $PID"
echo ""
echo "Monitoring logs (Ctrl+C to stop)..."
echo "-----------------------------------"

# Monitor the process
sleep 2

if ! kill -0 $PID 2>/dev/null; then
    echo ""
    echo "ERROR: Process died immediately!"
    echo ""
    echo "=== STDERR OUTPUT ==="
    cat "$STDERR_LOG"
    echo ""
    echo "=== STDOUT OUTPUT ==="
    cat "$STDOUT_LOG"
    echo ""
    if [ -f "$DEBUG_LOG" ]; then
        echo "=== DEBUG LOG ==="
        cat "$DEBUG_LOG"
    fi
    exit 1
fi

# Tail the logs
tail -f "$DEBUG_LOG" "$STDERR_LOG" 2>/dev/null &
TAIL_PID=$!

# Wait for the process
wait $PID
EXIT_CODE=$?

# Kill tail
kill $TAIL_PID 2>/dev/null

echo ""
echo "-----------------------------------"
echo "gambatte-k2 exited with code: $EXIT_CODE"
echo ""

# Combine logs
echo "=== COMBINED LOG ===" > "$COMBINED_LOG"
echo "" >> "$COMBINED_LOG"
echo "=== DEBUG LOG ===" >> "$COMBINED_LOG"
if [ -f "$DEBUG_LOG" ]; then
    cat "$DEBUG_LOG" >> "$COMBINED_LOG"
else
    echo "(No debug log found)" >> "$COMBINED_LOG"
fi
echo "" >> "$COMBINED_LOG"
echo "=== STDERR ===" >> "$COMBINED_LOG"
cat "$STDERR_LOG" >> "$COMBINED_LOG"
echo "" >> "$COMBINED_LOG"
echo "=== STDOUT ===" >> "$COMBINED_LOG"
cat "$STDOUT_LOG" >> "$COMBINED_LOG"

echo "All logs combined in: $COMBINED_LOG"
echo ""
echo "To view logs:"
echo "  Debug log:    cat $DEBUG_LOG"
echo "  STDERR:       cat $STDERR_LOG"
echo "  STDOUT:       cat $STDOUT_LOG"
echo "  Combined:     cat $COMBINED_LOG"
echo ""

# Show last 30 lines of debug log
if [ -f "$DEBUG_LOG" ]; then
    echo "=== Last 30 lines of debug log ==="
    tail -30 "$DEBUG_LOG"
else
    echo "No debug log was created - this is a bad sign!"
fi

# Check for common errors
echo ""
echo "=== Checking for common errors ==="
if grep -q "Segmentation fault" "$STDERR_LOG" 2>/dev/null; then
    echo "X SEGMENTATION FAULT detected"
fi
if grep -q "error while loading shared libraries" "$STDERR_LOG" 2>/dev/null; then
    echo "X Missing library detected:"
    grep "error while loading shared libraries" "$STDERR_LOG"
fi
if grep -q "FAILED" "$DEBUG_LOG" 2>/dev/null; then
    echo "!!!  FAILED operations detected:"
    grep "FAILED" "$DEBUG_LOG"
fi
if grep -q "ERROR" "$DEBUG_LOG" 2>/dev/null; then
    echo "!!!  ERRORS detected:"
    grep "ERROR" "$DEBUG_LOG"
fi

echo ""
echo "Done!"
