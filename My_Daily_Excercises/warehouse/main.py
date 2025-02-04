def read_warehouse(filename):
    """ Reads the warehouse file and returns a dictionary with product data. """
    warehouse_info = {}
    with open(filename, 'r') as file:
        for line in file:
            product_code, unit_cost, quantity_available = line.strip().split(",")
            unit_cost = float(unit_cost)
            quantity_available = int(quantity_available)
            warehouse_info[product_code] = [unit_cost, quantity_available]
    return warehouse_info


def read_movements(filename):
    """ Reads the movements file and returns a list of movement commands. """
    movements_info = []
    with open(filename, "r") as file:
        for line in file:
            product_code, variation = line.strip().split(",")
            variation = int(variation)
            movements_info.append({
                "product_code": product_code,
                "variation": variation
            })
    return movements_info


def process_movements(warehouse_info, movements_info):
    """ Processes the movements and updates the warehouse inventory. """
    total_value = sum(unit_cost * quantity for unit_cost, quantity in warehouse_info.values())

    for movement in movements_info:
        product_code = movement["product_code"]
        variation = movement["variation"]

        if product_code not in warehouse_info:
            print(f"ERROR: product {product_code} not existent.")
            continue

        unit_cost, quantity_available = warehouse_info[product_code]

        # Check feasibility of the variation
        if variation < 0 and abs(variation) > quantity_available:
            print(f"ERROR: Required quantity of {product_code} not available!")
            continue
        if variation > 0 and (quantity_available + variation) > 10000:
            print(f"ERROR: Cannot increase quantity of {product_code} beyond 10,000!")
            continue

        # Update total value before modification
        previous_value = total_value

        # Apply the movement
        warehouse_info[product_code][1] += variation  # Update quantity
        total_value += unit_cost * variation

        # Print movement update message
        if variation > 0:
            print(f"Increasing the quantity of {product_code} by {variation}")
        else:
            print(f"Decreasing the quantity of {product_code} by {abs(variation)}")

        print(f"Previous total value: {previous_value:.2f}€")
        print(f"New total value: {total_value:.2f}€\n")


def write_updated_warehouse(filename, warehouse_info):
    """ Writes the updated warehouse inventory to a file. """
    with open(filename, 'w') as file:
        for product_code, (unit_cost, quantity_available) in warehouse_info.items():
            file.write(f"{product_code},{unit_cost},{quantity_available}\n")


def main():
    file_warehouse = "warehouse.txt"
    file_movements = "movements.txt"
    output_file = "warehouse2.txt"

    # Read warehouse and movement data
    warehouse = read_warehouse(file_warehouse)
    movements = read_movements(file_movements)

    # Process movements and update warehouse
    process_movements(warehouse, movements)

    # Save the updated warehouse to a file
    write_updated_warehouse(output_file, warehouse)


if __name__ == '__main__':
    main()
