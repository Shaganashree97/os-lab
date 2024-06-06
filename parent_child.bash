echo "Parent process (PID $$) is running"

# Fork a child process
(
    echo "Child process (PID $$) is running"
    sleep 5
    echo "Child process (PID $$) is exiting"
) &
child_pid=$!

# Wait for the child process to complete
wait $child_pid
echo "Parent process detected that the child process has exited"
