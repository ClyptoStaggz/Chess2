## Board Initialization Process

### 1. **Starting Location Initialization**

- Define the starting location where the first tile will be spawned.
- This is represented as a vector specifying the position in the game world.

### 2. **Offset Initialization**

- Determine the offset value for each piece.
- This offset value ensures that tiles are spaced correctly on the board.

### 3. **Rows and Columns Initialization**

- Specify the number of rows and columns the board will have.
- These values can either be the same or different, depending on the desired board dimensions.

### 4. **Naming Convention Initialization**

- Determine the naming convention for rows and columns.
- This could be alphabetical, numerical, or any other system that makes sense for the game.

### 5. **Offset Calculation for Vertical Tiles**

- Calculate and store the offset values for vertical placements of tiles.
- This ensures that tiles are positioned correctly vertically, building on top or beside as necessary.

### 6. **Board Dimension Verification**

- Verify the board dimensions to ensure they adhere to any specified maximum or minimum sizes.
- This step is crucial to prevent spawning errors or gameplay issues later on.

### 7. **Error Handling Setup**

- Set up error handling mechanisms for the spawning process.
- This can include logging, retries, or user feedback systems to ensure a smooth player experience.

### 8. **Initial Locations Mapping**

- Map the initial locations for each row based on the starting location and offset values.
- This mapping will be used during the spawning process to position tiles correctly on the board.