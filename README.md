# connect4
Connect Four (also known as Connect 4, Four Up, Plot Four, Find Four, Captain's Mistress, Four in a Row, Drop Four)

# Connect 4 Board Representation

## Maximum Board Size

The maximum supported board size is **60 x 60**.

## Bitboards

### Player 1's Bitboard (`bp1`)

- **Purpose**: Stores Player 1's checkers.
- **Type**: `uint64_t bp1[60]`
- **Example Representation**:
    ```
    .........
    101011...
    010010...
    ```

### Player 2's Bitboard and Board Mask (`bp2m`)

- **Purpose**: Stores Player 2's checkers and the mask of the board.
- **Type**: `uint64_t bp2m[60]`
- **Example Representation**:
    ```
    .........
    101011...
    111011...
    ```
