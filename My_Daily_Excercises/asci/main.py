def read_file(filename):
    try:
        with open(filename,'r')as file:
            ascii_art=file.readlines()
            return ascii_art
    except FileNotFoundError as e:
        print(f"Error:The file can not open because :{e}")
def get_user_input():
    x=int(input("Enter the number of coordinates x:"))
    y=int(input("Enter the number of coordinates y:"))
    N=int(input("Enter the size of the square size:"))
    return x,y,N
def is_square_valid(x,y,N,ascii_art):
    if y+N>len(ascii_art) and x+N>len(ascii_art[y]):
        return False
    return True
def compute_statistics(x, y, N, ascii_art):
    char_count = {}
    total_chars = N * N

    for i in range(y, y + N):
        for j in range(x, x + N):
            char = ascii_art[i][j]
            if char in char_count:
                char_count[char] += 1
            else:
                char_count[char] = 1

    # Calculate percentages
    for char in char_count:
        char_count[char] = (char_count[char] / total_chars) * 100

    # Sort by percentage in descending order
    sorted_chars = sorted(char_count.items(), key=lambda item: item[1], reverse=True)

    return sorted_chars

def main():
    filename = "landscape.txt"
    ascii_art = read_file(filename)
    if ascii_art is None:
        return

    x, y, N = get_user_input()

    if not is_square_valid(x, y, N, ascii_art):
        print("ERROR!! The square to analyze is out of limits.")
        return

    statistics = compute_statistics(x, y, N, ascii_art)

    for char, percentage in statistics:
        print(f"{char}-> {percentage:.1f}%")

if __name__ == "__main__":
    main()