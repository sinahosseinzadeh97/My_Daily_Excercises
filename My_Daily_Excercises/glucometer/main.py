def read_file(filename):
    glu_info = {}
    with open(filename, 'r') as file:
        lines = file.readlines()
        for line in lines:
            ID, Hour, index, temp, bpm = line.strip().split()
            index = int(index)
            if ID not in glu_info:
                glu_info[ID] = []
            glu_info[ID].append((Hour, index, temp, bpm))
    return glu_info


def calculate_glu(glu_info):
    glucometer = {}

    # Count the number of exceeding readings for each patient
    for ID, info in glu_info.items():
        exceeding_readings = []
        for reading in info:
            hour, index, temp, bpm = reading
            if index > 200:
                exceeding_readings.append((hour, index))
        if exceeding_readings:
            glucometer[ID] = exceeding_readings

    # Sort patients by the number of exceeding readings in descending order
    sorted_patients = sorted(glucometer.items(), key=lambda x: len(x[1]), reverse=True)

    # Print the results
    for patient, readings in sorted_patients:
        for reading in readings:
            hour, index = reading
            print(f'{patient} {hour} {index}')


def main():
    # Define filepath
    filepath = 'glucometer.txt'
    glu_file = read_file(filepath)
    calculate_glu(glu_file)


if __name__ == '__main__':
    main()