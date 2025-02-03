import csv

# Open and read the CSV file
with open("player_stats.csv", encoding="utf-8") as file:
    reader = csv.DictReader(file)  # Reads as a dictionary (key: column name, value: data)
    data = list(reader)  # Convert it into a list for easy access
forward_players = []

for player in data:
    if player["position"] == "FW":  # Check if player is a forward
        minutes = int(player["minutes"])
        if minutes > 0:  # To avoid division by zero
            efficiency = (int(player["goals"]) / minutes) + \
                         (int(player["assists"]) / minutes) - \
                         (int(player["offsides"]) / minutes)
            forward_players.append((player["player"], player["team"], efficiency))

# Sort by efficiency (highest first)
forward_players.sort(key=lambda x: x[2], reverse=True)

# Print the top 3 forwards
print("Name".ljust(30), "Team".ljust(20), "Forward efficiency")
for name, team, efficiency in forward_players[:3]:
    print(name.ljust(30), team.ljust(20), f"{efficiency:.3f}")
