#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 1000   // Maximum number of players
#define MAX_NAME 50        // Maximum length for player names
#define MAX_TEAM 50        // Maximum length for team names

// Structure to hold player information
typedef struct {
    char name[MAX_NAME];
    char position[3];  // FW, MF, DF, GK
    char team[MAX_TEAM];
    int birth_year;
    int minutes;
    int goals;
    int assists;
    int offsides;
    int crosses;
    int interceptions;
    int tackles_won;
    int pens_conceded;
    int ball_recoveries;
    int aerials_won;
    int aerials_lost;
} Player;

// Function to read the file and store player data
int read_file(const char *filename, Player players[]) {
    FILE *file = fopen(filename, "r"); // Open file for reading
    if (!file) {
        printf("Error opening file!\n");
        return 0;
    }

    char line[200];
    int count = 0; // Track number of players

    fgets(line, sizeof(line), file); // Skip header line

    // Read player data line by line
    while (fgets(line, sizeof(line), file) && count < MAX_PLAYERS) {
        // Extract values from CSV format
        sscanf(line, "%49[^,],%2[^,],%49[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
               players[count].name, players[count].position, players[count].team,
               &players[count].birth_year, &players[count].minutes, &players[count].goals,
               &players[count].assists, &players[count].offsides, &players[count].crosses,
               &players[count].interceptions, &players[count].tackles_won, &players[count].pens_conceded,
               &players[count].ball_recoveries, &players[count].aerials_won, &players[count].aerials_lost);

        count++;
    }

    fclose(file); // Close file
    return count; // Return number of players read
}

// Function to calculate forward efficiency
void forward_efficiency(Player players[], int count) {
    printf("\n%-30s %-20s %s\n", "Name", "Team", "Forward Efficiency");

    // Loop through all players
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].position, "FW") == 0) {  // Check if Forward
            if (players[i].minutes > 0) { // Avoid division by zero
                double efficiency = (players[i].goals / (double)players[i].minutes) +
                                    (players[i].assists / (double)players[i].minutes) -
                                    (players[i].offsides / (double)players[i].minutes);

                printf("%-30s %-20s %.3f\n", players[i].name, players[i].team, efficiency);
            }
        }
    }
}

// Function to calculate midfield efficiency
void midfield_efficiency(Player players[], int count) {
    printf("\n%-30s %-20s %s\n", "Name", "Team", "Midfield Efficiency");

    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].position, "MF") == 0) {  // Check if Midfielder
            if (players[i].minutes > 0) {
                double efficiency = (players[i].interceptions + players[i].ball_recoveries +
                                    (players[i].assists / (double)(players[i].crosses > 0 ? players[i].crosses : 1))) /
                                    players[i].minutes;

                printf("%-30s %-20s %.3f\n", players[i].name, players[i].team, efficiency);
            }
        }
    }
}

// Function to find the three youngest teams
void find_youngest_teams(Player players[], int count) {
    printf("\nThe three teams with the lowest average age are:\n");

    typedef struct {
        char team[MAX_TEAM];
        int total_age;
        int player_count;
    } TeamInfo;

    TeamInfo teams[MAX_PLAYERS]; // Store teams
    int team_count = 0;

    // Loop through players and calculate team average age
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < team_count; j++) {
            if (strcmp(players[i].team, teams[j].team) == 0) {
                teams[j].total_age += (2022 - players[i].birth_year);
                teams[j].player_count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(teams[team_count].team, players[i].team);
            teams[team_count].total_age = (2022 - players[i].birth_year);
            teams[team_count].player_count = 1;
            team_count++;
        }
    }

    // Sort teams by average age
    for (int i = 0; i < team_count - 1; i++) {
        for (int j = i + 1; j < team_count; j++) {
            double avg_age_i = (double)teams[i].total_age / teams[i].player_count;
            double avg_age_j = (double)teams[j].total_age / teams[j].player_count;
            if (avg_age_i > avg_age_j) {
                TeamInfo temp = teams[i];
                teams[i] = teams[j];
                teams[j] = temp;
            }
        }
    }

    // Print the three youngest teams
    for (int i = 0; i < 3 && i < team_count; i++) {
        printf("%-20s %.2f years\n", teams[i].team, (double)teams[i].total_age / teams[i].player_count);
    }
}

// Function to find the most efficient team
void find_most_efficient_team(Player players[], int count) {
    printf("\nThe most efficient team is:\n");

    typedef struct {
        char team[MAX_TEAM];
        double efficiency;
    } TeamEfficiency;

    TeamEfficiency teams[MAX_PLAYERS];
    int team_count = 0;

    // Loop through forwards and calculate team efficiency
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].position, "FW") == 0 && players[i].minutes > 0) {
            double efficiency = (players[i].goals / (double)players[i].minutes) +
                                (players[i].assists / (double)players[i].minutes) -
                                (players[i].offsides / (double)players[i].minutes);

            int found = 0;
            for (int j = 0; j < team_count; j++) {
                if (strcmp(players[i].team, teams[j].team) == 0) {
                    teams[j].efficiency += efficiency;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(teams[team_count].team, players[i].team);
                teams[team_count].efficiency = efficiency;
                team_count++;
            }
        }
    }

    // Find the team with the highest efficiency
    double max_efficiency = 0;
    char best_team[MAX_TEAM];

    for (int i = 0; i < team_count; i++) {
        if (teams[i].efficiency > max_efficiency) {
            max_efficiency = teams[i].efficiency;
            strcpy(best_team, teams[i].team);
        }
    }

    printf("%s\n", best_team);
}

// Main function
int main() {
    Player players[MAX_PLAYERS];
    int count = read_file("player_stats-small.csv", players);

    if (count > 0) {
        forward_efficiency(players, count);
        midfield_efficiency(players, count);
        find_youngest_teams(players, count);
        find_most_efficient_team(players, count);
    }

    return 0;
}
