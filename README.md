# Chemistry Calculator: Technical Documentation

## 1. Overview

**Chemistry Calculator** is a command-line utility written in C designed to assist students, researchers, and chemists with fundamental chemical calculations and data retrieval. It features a comprehensive database of the first 118 elements of the periodic table and provides tools for calculating molar masses, converting between mass and moles, determining solution molarity, solving Ideal Gas Law equations, and performing temperature unit conversions.

This document outlines the installation, usage, supported features, and underlying algorithms implemented in `main.c`.

---

## 2. Compilation and Installation

The program requires a standard C compiler (e.g., `gcc`) and links against the math library (`libm`) for potential future expansions or specific mathematical operations, although the current implementation primarily uses standard arithmetic.

### Prerequisites
*   GCC or Clang compiler
*   Standard C Library (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `math.h`)

### Build Instructions
To compile the source code into an executable named `chemcalc`:

```bash
gcc -o chemcalc main.c -lm
```

*Note: The `-lm` flag is included to link the math library, ensuring compatibility with functions like `pow()` if used in extended versions.*

---

## 3. Usage

### Interactive Mode
The program runs in an interactive menu-driven mode. Upon execution, it presents a main menu from which users can select various operations.

```bash
./chemcalc
```

### Main Menu Options
1.  **Periodic Table**: Displays a partial list of elements (first 30) with atomic number, symbol, name, and atomic weight.
2.  **Element Search**: Searches for detailed information about a specific element by atomic number, symbol, or name.
3.  **Molar Mass Calculator**: Calculates the molar mass of a given chemical formula.
4.  **Mass/Moles Conversion**: Converts between mass (grams) and moles for a given substance.
5.  **Molarity Calculator**: Calculates the molarity (mol/L) of a solution.
6.  **Ideal Gas Law Calculator**: Solves for Pressure, Volume, Moles, or Temperature using $PV = nRT$.
7.  **Temperature Converter**: Converts between Celsius, Kelvin, and Fahrenheit.
8.  **Help**: Displays available commands.
0.  **Exit**: Terminates the program.

---

## 4. Feature Details

### 4.1. Element Database
The program contains a static array of `Element` structures storing data for elements 1 (Hydrogen) through 118 (Oganesson).
*   **Data Fields**: Atomic Number, Name, Symbol, Atomic Weight, Electron Configuration, State at STP, Melting Point (K), and Boiling Point (K).
*   **Source**: Data is sourced from reliable chemistry databases, including estimated values for synthetic radioactive elements.

### 4.2. Element Search
*   **Input**: Accepts atomic number (integer), element symbol (e.g., "Fe"), or element name (e.g., "Iron").
*   **Case Insensitivity**: Searches are case-insensitive for symbols and names.
*   **Output**: Displays full details of the found element, including physical properties and electron configuration.

### 4.3. Molar Mass Calculator
*   **Functionality**: Parses a chemical formula string and calculates the total molar mass in g/mol.
*   **Supported Syntax**:
    *   Element symbols (e.g., `H`, `He`).
    *   Subscripts (e.g., `H2O`).
    *   Parentheses for groups (e.g., `Ca(OH)2`, `Al2(SO4)3`).
*   **Algorithm**: Uses a recursive descent parser (`parseFormula`) to handle nested parentheses and multi-digit subscripts.
*   **Error Handling**: Detects unknown element symbols and invalid characters.

### 4.4. Mass/Moles Conversion
*   **Modes**:
    1.  **Mass to Moles**: Input mass (g) $\rightarrow$ Output moles (mol).
    2.  **Moles to Mass**: Input moles (mol) $\rightarrow$ Output mass (g).
*   **Process**: First calculates the molar mass of the specified compound, then applies the formula:
    $$ \text{Moles} = \frac{\text{Mass}}{\text{Molar Mass}} $$

### 4.5. Molarity Calculator
*   **Functionality**: Calculates the molarity ($M$) of a solution.
*   **Input Options**: Users can provide the solute amount as either **Mass (g)** or **Moles (mol)**.
*   **Formula**:
    $$ M = \frac{\text{Moles of Solute}}{\text{Volume of Solution (L)}} $$
*   **Validation**: Ensures volume is greater than zero.

### 4.6. Ideal Gas Law Calculator
*   **Equation**: $PV = nRT$
*   **Constant**: Uses $R = 0.0821 \, \text{L·atm/(mol·K)}$.
*   **Variables**:
    *   $P$: Pressure (atm)
    *   $V$: Volume (L)
    *   $n$: Moles (mol)
    *   $T$: Temperature (K)
*   **Usage**: User selects which variable to solve for and provides the other three. The program validates that denominators are not zero.

### 4.7. Temperature Converter
*   **Conversions Supported**:
    *   Celsius ($^\circ$C) $\leftrightarrow$ Kelvin (K)
    *   Celsius ($^\circ$C) $\leftrightarrow$ Fahrenheit ($^\circ$F)
*   **Formulas**:
    *   $K = ^\circ C + 273.15$
    *   $^\circ F = (^{\circ}C \times \frac{9}{5}) + 32$

---

## 5. Algorithmic Details

### 5.1. Chemical Formula Parser
The `parseFormula` function implements a recursive parser to handle complex chemical formulas.
1.  **Iteration**: Iterates through the character array of the formula.
2.  **Element Detection**: Identifies uppercase letters as the start of an element symbol, followed by optional lowercase letters.
3.  **Subscript Handling**: Accumulates digits following an element or closing parenthesis to determine the count.
4.  **Parentheses Handling**: When an opening parenthesis `(` is encountered, the function calls itself recursively to calculate the mass of the group inside. Upon returning, it checks for a subscript immediately following the closing parenthesis `)` and multiplies the group's mass accordingly.

### 5.2. Data Structures
*   **`Element` Struct**: Holds all periodic table data.
*   **Global Array**: `elements[MAX_ELEMENTS]` stores the database, allowing $O(1)$ access by atomic number and $O(N)$ search by symbol/name (where $N=118$, making linear search efficient).

---

## 6. Error Handling and Validation

*   **Input Validation**:
    *   Checks for valid numeric inputs in calculators.
    *   Validates chemical formulas against the internal element database.
    *   Ensures physical constraints (e.g., volume > 0, temperature > 0 K where applicable).
*   **Unknown Elements**: If a symbol in a formula is not found in the database, the parser returns an error code (-1) and prints a specific error message identifying the unknown symbol.
*   **Invalid Menu Choices**: The main loop rejects invalid menu selections and prompts the user again.

---

## 7. Limitations

1.  **Formula Complexity**: The parser supports standard alphanumeric formulas with parentheses but does not support hydrates (e.g., `CuSO4.5H2O`) or charge states unless explicitly typed as part of the formula structure (which may cause errors if dots are not handled).
2.  **Precision**: Floating-point calculations use `double` precision, which is sufficient for most educational and general laboratory purposes but may have minor rounding differences compared to specialized high-precision software.
3.  **Ideal Gas Assumption**: The Ideal Gas Law calculator assumes ideal behavior and does not account for real gas deviations (Van der Waals corrections).
4.  **Static Data**: Element data is hardcoded. Updates to atomic weights or new discoveries require recompilation of the source code.

---

## 8. Example Sessions

### Calculating Molar Mass of Sulfuric Acid
```text
=== Chemistry Calculator ===
...
Enter your choice: 3
Enter chemical formula (e.g., H2O, C6H12O6, Ca(OH)2): H2SO4
The molar mass of H2SO4 is approximately: 98.0790 g/mol
```

### Solving for Pressure in Ideal Gas Law
```text
Enter your choice: 6
Enter the variable you want to solve for (P, V, n, or T): P
Enter the known values (enter 0 for the variable you are solving for):
Pressure (atm): 0
Volume (L): 22.4
Moles (mol): 1
Temperature (K): 273.15
Pressure (P) = 1.0000 atm
```

### Searching for Gold
```text
Enter your choice: 2
Enter atomic number, element symbol, or name: Au

=== Gold (Au) ===
Atomic Number      : 79
Atomic Weight      : 196.9666
Electron Config    : [Xe] 4f14 5d10 6s1
State (25°C, 1 atm): Solid
Melting Point (K)  : 1337.33
Boiling Point (K)  : 3129.00
```
