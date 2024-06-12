#!/bin/bash

# Function to implement Best Fit
implementBestFit() {
    local blockSize=("${!1}")
    local processSize=("${!2}")
    local blocks=${#blockSize[@]}
    local processes=${#processSize[@]}
    local allocation=()
    local occupied=()

    # Initialize allocation and occupied arrays
    for ((i = 0; i < processes; i++)); do
        allocation[$i]=-1
    done

    for ((i = 0; i < blocks; i++)); do
        occupied[$i]=0
    done

    # Allocate blocks to processes
    for ((i = 0; i < processes; i++)); do
        local indexPlaced=-1
        for ((j = 0; j < blocks; j++)); do
            if [[ ${blockSize[$j]} -ge ${processSize[$i]} && ${occupied[$j]} -eq 0 ]]; then
                if [[ $indexPlaced -eq -1 || ${blockSize[$j]} -lt ${blockSize[$indexPlaced]} ]]; then
                    indexPlaced=$j
                fi
            fi
        done
        if [[ $indexPlaced -ne -1 ]]; then
            allocation[$i]=$indexPlaced
            occupied[$indexPlaced]=1
        fi
    done

    # Print allocation result
    echo -e "\nProcess No.\tProcess Size\tBlock no."
    for ((i = 0; i < processes; i++)); do
        echo -ne "$((i + 1))\t\t${processSize[$i]}\t\t"
        if [[ ${allocation[$i]} -ne -1 ]]; then
            echo -e "$((allocation[$i] + 1))"
        else
            echo -e "Not Allocated"
        fi
    done
}

# Main script
blockSize=(100 50 30 120 35)
processSize=(40 10 30 60)

implementBestFit blockSize[@] processSize[@]
