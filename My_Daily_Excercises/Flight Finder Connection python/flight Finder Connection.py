def read_file(filename):
    information_flights = {}
    with open(filename, 'r') as file:
        for line in file:
            parts = line.strip().split(' ')
            flight_number = parts[0]
            departure_airpot = parts[1]
            arrival_airport = parts[2]
            departure_time = float(parts[3])
            arrival_time = float(parts[4])
            information_flights[flight_number] = [departure_airpot, arrival_airport, departure_time, arrival_time]
        return information_flights
def main():
    

if __name__ == '__main__':
    main()