def read_flights(filename):
    flights = {}
    with open(filename, 'r') as file:
        for line in file:
            flight_id, model, rows, cols = line.strip().split()
            flights[flight_id] = {
                "model": model,
                "rows": int(rows),
                "cols": int(cols),
                "seats": {}
            }
    return flights

def read_bookings(filename):
    bookings = []
    with open(filename, 'r') as file:
        for line in file:
            bookings.append(line.strip().split())
    return bookings

def book_seats(flight, name, surname, num_seats):
    full_name = f"{name} {surname}"
    available_seats = []

    for row in range(1, flight["rows"] + 1):
        for col in range(1, flight["cols"] + 1):
            if len(available_seats) == num_seats:
                break
            if (row, col) not in flight["seats"]:
                available_seats.append((row, col))

    if len(available_seats) < num_seats:
        print(f"BOOK {name} {full_name} {num_seats} - FAIL")
        return False

    for seat in available_seats:
        flight["seats"][seat] = full_name
    return True

def cancel_bookings(flight, name, surname):
    full_name = f"{name} {surname}"
    seats_to_remove = []

    for seat, passenger in flight["seats"].items():
        if passenger == full_name:
            seats_to_remove.append(seat)

    if not seats_to_remove:
        print(f"CANCEL {full_name} - No seats found!")
        return False

    for seat in seats_to_remove:
        del flight["seats"][seat]

    return True

def process_bookings(flights, bookings):
    for booking in bookings:
        op_code = booking[0]
        flight_id = booking[1]
        name = booking[2]
        surname = booking[3]

        if flight_id not in flights:
            continue

        if op_code == "BOOK":
            num_seats = int(booking[4])
            book_seats(flights[flight_id], name, surname, num_seats)
        elif op_code == "CANCEL":
            cancel_bookings(flights[flight_id], name, surname)

def print_flight_bookings(flights):
    for flight_id, flight in flights.items():
        print(f"Flight {flight_id}:")
        for (row, col), passenger in sorted(flight["seats"].items()):
            print(f"{row} {col} {passenger}")

def main():
    flights = read_flights("flights.txt")
    bookings = read_bookings("bookings.txt")
    process_bookings(flights, bookings)
    print_flight_bookings(flights)

if __name__ == "__main__":
    main()
