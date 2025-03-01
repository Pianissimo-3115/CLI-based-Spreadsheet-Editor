with open("spreadsheet_rules.txt", "w") as f:
    row = 1
    col = "A"
    next_col="A"
    while row <= 999:
        if next_col[-1] == 'Z':  # Column overflow (e.g., Z -> AA)
            if len(next_col) == 1:
                next_col = "AA"
            else:
                next_col = chr(ord(next_col[0]) + 1) + "A"
        else:
            next_col = chr(ord(col[-1]) + 1) if len(col) == 1 else col[:-1] + chr(ord(col[-1]) + 1)

        f.write(f"{col}{row}=MAX({next_col}{row+1}:ZZZ999)\n")
        
        # Update column (handle multi-letter column names)
        
        col = next_col
        row += 1
