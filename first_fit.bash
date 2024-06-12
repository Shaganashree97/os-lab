#!/bin/bash

# Function to implement First Fit
implementFirstFit() {
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
        for ((j = 0; j < blocks; j++)); do
            if [[ ${blockSize[$j]} -ge ${processSize[$i]} && ${occupied[$j]} -eq 0 ]]; then
                allocation[$i]=$j
                occupied[$j]=1
                break
            fi
        done
    done

    # Print allocation result
    echo -e "\nProcess No.\tProcess Size\tBlock no."
    for ((i = 0; i < processes; i++)); do
        if [[ ${allocation[$i]} -ne -1 ]]; then
            echo -e "$((i + 1))\t\t${processSize[$i]}\t\t$((allocation[$i] + 1))"
        else
            echo -e "$((i + 1))\t\t${processSize[$i]}\t\tNot Allocated"
        fi
    done
}

# Main script
blockSize=(100 50 30 120 35)
processSize=(40 10 30 60)

implementFirstFit blockSize[@] processSize[@]
