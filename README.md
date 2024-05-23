# Description

CSS Processor is a simple engine designed to process and manipulate CSS sections. It reads CSS declarations and commands from standard input, parses them, and executes commands to query or modify the CSS, outputting the results to standard output. The project includes custom implementations for a linked list and a string class for efficient data handling.

## Features

- **CSS Parsing**: Reads and parses syntactically correct CSS.
- **Command Execution**: Executes various commands to query and manipulate CSS.
- **Custom Data Structures**: Uses custom linked list and string class for efficient block management.

```
  body {
  margin: 0;
  padding: 0;
}
h1, h2 {
  color: red;
}
????
?           // Number of CSS blocks
1,S,?       // Number of selectors in the first block
1,A,?       // Number of attributes in the first block
1,S,1       // First selector in the first block
1,A,margin  // Value of the 'margin' attribute in the first block
color,A,?   // Total number of 'color' attributes across all blocks
h1,S,?      // Total number of occurrences of the 'h1' selector
h1,E,color  // Value of the 'color' attribute for the 'h1' selector
1,D,*       // Delete the first block
```

## Commands
- `????` - Begin command section.
- `****` - Resume reading CSS.
- `?` - Print the number of CSS blocks.
- `i,S,?` - Print the number of selectors in the i-th block.
- `i,A,?` - Print the number of attributes in the i-th block.
- `i,S,j` - Print the j-th selector in the i-th block.
- `i,A,n` - Print the value of the attribute named n in the i-th block.
- `n,A,?`- Print the total number of occurrences of the attribute named n.
- `z,S,?` - Print the total number of occurrences of the selector z.
- `z,E,n` - Print the value of the attribute named n for the selector z.
- `i,D,*` - Delete the i-th block.
- `i,D,n` - Delete the attribute named n in the i-th block.

# Implementation Details

## CSS Parsing
- **Selectors**: Treated as values without semantic interpretation.
- **Attributes**: Parsed as key-value pairs. Duplicate attributes are resolved by retaining the last occurrence.
- **Blocks**: Stored in a custom doubly linked list for efficient operations.

## Data Structures
- **Custom Linked List** `(Block_List)`: Efficiently manages CSS blocks.
- **Custom String Class** `(String)`: Handles string operations required for parsing.
