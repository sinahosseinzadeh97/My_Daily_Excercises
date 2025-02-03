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
midfield_players = []

for player in data:
    if player["position"] == "MF":  # Check if player is a midfielder
        minutes = int(player["minutes"])
        crosses = int(player["crosses"])
        assists = int(player["assists"])
        if minutes > 0:  # To avoid division by zero
            efficiency = (int(player["interceptions"]) + int(player["ball_recoveries"]) +
                          (assists / crosses if crosses > 0 else 0)) / minutes
            midfield_players.append((player["player"], player["team"], efficiency))

# Sort by efficiency (highest first)
midfield_players.sort(key=lambda x: x[2], reverse=True)

# Print the top 3 midfielders
print("\nName".ljust(30), "Team".ljust(20), "Midfield efficiency")
for name, team, efficiency in midfield_players[:3]:
    print(name.ljust(30), team.ljust(20), f"{efficiency:.3f}")
from collections import defaultdict

team_ages = defaultdict(list)

for player in data:
    age = 2022 - int(player["birth_year"])  # Compute player's age
    team_ages[player["team"]].append(age)  # Add age to the team list

# Compute average age for each team
team_avg_age = {team: sum(ages) / len(ages) for team, ages in team_ages.items()}

# Sort teams by average age (youngest first)
youngest_teams = sorted(team_avg_age.items(), key=lambda x: x[1])[:3]

print("\nThe three teams with the lowest average age are:")
for team, avg_age in youngest_teams:
    print(team.ljust(20), f"{avg_age:.2f} years")
from collections import defaultdict

team_efficiency = defaultdict(list)

# Store efficiencies by team
for name, team, efficiency in forward_players:
    team_efficiency[team].append(efficiency)

# Sum the efficiencies of the best 3 forwards from each team
team_total_efficiency = {team: sum(sorted(effs, reverse=True)[:3]) for team, effs in team_efficiency.items()}

# Find the most efficient team
most_efficient_team = max(team_total_efficiency, key=team_total_efficiency.get)

print("\nThe most efficient team is", most_efficient_team)

