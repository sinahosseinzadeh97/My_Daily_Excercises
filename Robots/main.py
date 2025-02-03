# Step 1: Read the file and store robot paths
robot_paths = {}

with open("trajectories.txt", "r") as file:
    for line in file:
        parts = line.strip().split()  # Split line into parts
        name = parts[0]  # Robot name
        x, y = int(parts[1]), int(parts[2])  # Starting position
        moves = parts[3]  # Movement sequence

        # Track visited locations
        visited = set()
        visited.add((x, y))  # Mark the starting point

        # Step 2: Follow the moves
        for i in range(0, len(moves), 2):  # Moves come in pairs (+h, -v,)
            direction = moves[i]  # '+' or '-'
            axis = moves[i + 1]  # 'h' or 'v'

            # Change position based on movement
            if axis == 'h':
                x = x + 1 if direction == '+' else x - 1  # Move left/right
            elif axis == 'v':
                y = y + 1 if direction == '+' else y - 1  # Move up/down

            visited.add((x, y))  # Store the new location

        # Store the path of this robot
        robot_paths[name] = visited

# Step 3: Ask user for two robot names
robot1 = input("Enter the first robot's name: ")
robot2 = input("Enter the second robot's name: ")

# Check if robots exist
if robot1 in robot_paths and robot2 in robot_paths:
    # Find the common locations
    common_locations = robot_paths[robot1] & robot_paths[robot2]
    print(f"Number of locations visited by both robots: {len(common_locations)}")
else:
    print("One or both robots not found in the file.")
