# Function to create an orphan process
create_orphan() {
    echo "Creating an orphan process..."
    # Fork a child process
    (
        # Child process sleeps longer than the parent
        sleep 10
        echo "Orphan process (PID $$) is now adopted by init/systemd"
    ) &
    # Parent process exits immediately
    echo "Parent process (PID $$) is exiting"
    exit 0
}

create_orphan
