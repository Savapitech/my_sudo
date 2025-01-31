CUSTOM_SUDO="./my_sudo"  # Path to your sudo clone
TEST_USER="test"         # Valid user
TEST_GROUP="wheel"       # Valid group
INVALID_USER="invalid"   # Non-existent user
INVALID_CMD="invalid"

run_test() {
    TEST_NAME="$1"
    CMD="$2"
    
    echo "[TEST] $TEST_NAME"
    OUTPUT_REF=$(sudo sudo $CMD)
    OUTPUT_CUSTOM=$(sudo $CUSTOM_SUDO $CMD)

    if [ "$OUTPUT_REF" == "$OUTPUT_CUSTOM" ]; then
        echo "✅ Success"
    else
        echo "❌ Failure"
        echo "  🔹 Reference : $OUTPUT_REF"
        echo "  🔹 My sudo   : $OUTPUT_CUSTOM"
    fi
    echo "--------------------------------------------"
}

run_test "-u (change user)" "-u $TEST_USER whoami"
run_test "-g (change group)" "-g $TEST_GROUP -- id -gn"
run_test "-u -g (change user & group)" "-u $TEST_USER -g $TEST_GROUP id"
run_test "Invalid user" "-u $INVALID_USER whoami"
run_test "Invalid group" "-g invalidgroup -- id -gn"
run_test "User not in sudoers" "-u root whoami"
run_test "Invalid command" "$INVALID_CMD"
run_test "Multiple -u flags" "-u $TEST_USER whoami"
run_test "Multiple -g flags" "-g $TEST_GROUP -g root id -gn"
run_test "Run command without privileges" "echo Test"
run_test "Execute as root (without -u)" "-- id -u"
