def read_exams(filename):
    exams = {}
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if not line:
                continue
            id, date, exam_code, grade = line.split(',')
            if grade in ['A', 'R']:
                continue  # Skip absent or failed exams
            if id not in exams:
                exams[id] = {}
            exams[id][exam_code] = grade
    return exams

def read_cfu(filename):
    cfu_info = {}
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if not line:
                continue
            exam_code, cfu, mandatory = line.split(',')
            cfu_info[exam_code] = {
                'cfu': int(cfu),
                'mandatory': int(mandatory)
            }
    return cfu_info

def calculate_weighted_average(grades, cfu_info):
    total_cfu = 0
    total_weighted_grade = 0
    mandatory_cfu = 0

    for exam_code, grade in grades.items():
        if exam_code not in cfu_info:
            continue  # Skip if exam code is not in cfu.dat
        cfu = cfu_info[exam_code]['cfu']
        is_mandatory = cfu_info[exam_code]['mandatory']

        # Convert 30L to 33 for average calculation
        if grade == '30L':
            grade_value = 33
        else:
            grade_value = int(grade)

        total_cfu += cfu
        total_weighted_grade += grade_value * cfu
        if is_mandatory:
            mandatory_cfu += cfu

    if total_cfu == 0:
        return 0, 0, 0  # Avoid division by zero

    average = total_weighted_grade / total_cfu
    return total_cfu, mandatory_cfu, round(average, 2)

def main():
    exams_file = 'exams.log'
    cfu_file = 'cfu.dat'

    # Read and parse files
    exams = read_exams(exams_file)
    cfu_info = read_cfu(cfu_file)

    # Process each student
    for student_id, grades in exams.items():
        total_cfu, mandatory_cfu, average = calculate_weighted_average(grades, cfu_info)

        # Check eligibility
        if total_cfu >= 30 and mandatory_cfu >= 10:
            print(f"STUDENT {student_id}")
            print(f"Student with {total_cfu} total credits; {mandatory_cfu} mandatory credits; {average} average.")
            print()

if __name__ == '__main__':
    main()