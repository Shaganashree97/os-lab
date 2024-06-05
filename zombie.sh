# Function to create a child process
create_zombie() {
    echo "Creating a zombie process..."
    # Fork a child process
    ( 
        echo "Child process (PID $$) is running and will exit"
        # The child process exits immediately
        exit 0
    )
    # Parent process sleeps to allow the child to exit
    sleep 5
    echo "Check the process table to see the zombie process (use 'ps aux | grep Z')"
    # Keep the script running to see the zombie
    sleep 60
}

create_zombie
