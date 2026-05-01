#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> // Required for atoi function
#include <math.h>   // Required for pow function (if needed for future features)

#define MAX_ELEMENTS 118
#define MAX_FORMULA_LENGTH 100 // Increased formula length
#define R_IDEAL_GAS 0.0821 // Ideal gas constant in L*atm/(mol*K)

// Structure to hold element data
typedef struct {
    int atomicNumber;
    char name[30]; // Increased name buffer
    char symbol[4]; // Increased symbol buffer
    double atomicWeight;
    char electronConfig[50]; // Increased electron config buffer
    char state[40]; // Increased state buffer to accommodate longer strings like "Expected to be Gas/Liquid/Solid"
    double meltingPoint;   // Melting point (K)
    double boilingPoint;   // Boiling point (K)
} Element;

// Array to store element data (first 118 elements)
// Data sourced from various reliable chemistry databases.
Element elements[MAX_ELEMENTS] = {
    {1, "Hydrogen", "H", 1.008, "1s1", "Gas", 14.01, 20.28},
    {2, "Helium", "He", 4.0026, "1s2", "Gas", 0.95, 4.22},
    {3, "Lithium", "Li", 6.94, "[He] 2s1", "Solid", 453.65, 1615},
    {4, "Beryllium", "Be", 9.0122, "[He] 2s2", "Solid", 1560, 2742},
    {5, "Boron", "B", 10.81, "[He] 2s2 2p1", "Solid", 2349, 4200},
    {6, "Carbon", "C", 12.011, "[He] 2s2 2p2", "Solid", 3825, 4300},
    {7, "Nitrogen", "N", 14.007, "[He] 2s2 2p3", "Gas", 63.15, 77.36},
    {8, "Oxygen", "O", 15.999, "[He] 2s2 2p4", "Gas", 54.36, 90.20},
    {9, "Fluorine", "F", 18.998, "[He] 2s2 2p5", "Gas", 53.53, 85.03},
    {10, "Neon", "Ne", 20.180, "[He] 2s2 2p6", "Gas", 24.56, 27.07},
    {11, "Sodium", "Na", 22.990, "[Ne] 3s1", "Solid", 370.95, 1156},
    {12, "Magnesium", "Mg", 24.305, "[Ne] 3s2", "Solid", 923, 1363},
    {13, "Aluminum", "Al", 26.982, "[Ne] 3s2 3p1", "Solid", 933.47, 2792},
    {14, "Silicon", "Si", 28.085, "[Ne] 3s2 3p2", "Solid", 1687, 3505},
    {15, "Phosphorus", "P", 30.974, "[Ne] 3s2 3p3", "Solid", 317.3, 550}, // White phosphorus
    {16, "Sulfur", "S", 32.06, "[Ne] 3s2 3p4", "Solid", 388.36, 717.8},
    {17, "Chlorine", "Cl", 35.45, "[Ne] 3s2 3p5", "Gas", 171.65, 239.11},
    {18, "Argon", "Ar", 39.948, "[Ne] 3s2 3p6", "Gas", 83.81, 87.30},
    {19, "Potassium", "K", 39.098, "[Ar] 4s1", "Solid", 336.53, 1032},
    {20, "Calcium", "Ca", 40.078, "[Ar] 4s2", "Solid", 1115, 1757},
    {21, "Scandium", "Sc", 44.956, "[Ar] 3d1 4s2", "Solid", 1814, 3109},
    {22, "Titanium", "Ti", 47.867, "[Ar] 3d2 4s2", "Solid", 1941, 3560},
    {23, "Vanadium", "V", 50.942, "[Ar] 3d3 4s2", "Solid", 2183, 3680},
    {24, "Chromium", "Cr", 51.996, "[Ar] 3d5 4s1", "Solid", 2180, 2944},
    {25, "Manganese", "Mn", 54.938, "[Ar] 3d5 4s2", "Solid", 1519, 2334},
    {26, "Iron", "Fe", 55.845, "[Ar] 3d6 4s2", "Solid", 1811, 3134},
    {27, "Cobalt", "Co", 58.933, "[Ar] 3d7 4s2", "Solid", 1768, 3200},
    {28, "Nickel", "Ni", 58.693, "[Ar] 3d8 4s2", "Solid", 1728, 3003},
    {29, "Copper", "Cu", 63.546, "[Ar] 3d10 4s1", "Solid", 1358, 2835},
    {30, "Zinc", "Zn", 65.38, "[Ar] 3d10 4s2", "Solid", 692.68, 1180},
    {31, "Gallium", "Ga", 69.723, "[Ar] 3d10 4s2 4p1", "Solid", 302.91, 2673},
    {32, "Germanium", "Ge", 72.630, "[Ar] 3d10 4s2 4p2", "Solid", 1211.4, 3106},
    {33, "Arsenic", "As", 74.9216, "[Ar] 3d10 4s2 4p3", "Solid", 1090, 887}, // Sublimes
    {34, "Selenium", "Se", 78.971, "[Ar] 3d10 4s2 4p4", "Solid", 494, 958},
    {35, "Bromine", "Br", 79.904, "[Ar] 3d10 4s2 4p5", "Liquid", 265.8, 332.0},
    {36, "Krypton", "Kr", 83.798, "[Ar] 3d10 4s2 4p6", "Gas", 115.79, 120.85},
    {37, "Rubidium", "Rb", 85.468, "[Kr] 5s1", "Solid", 312.46, 961},
    {38, "Strontium", "Sr", 87.62, "[Kr] 5s2", "Solid", 1050, 1655},
    {39, "Yttrium", "Y", 88.9058, "[Kr] 4d1 5s2", "Solid", 1799, 3203},
    {40, "Zirconium", "Zr", 91.224, "[Kr] 4d2 5s2", "Solid", 2128, 4650},
    {41, "Niobium", "Nb", 92.9064, "[Kr] 4d4 5s1", "Solid", 2750, 5017},
    {42, "Molybdenum", "Mo", 95.95, "[Kr] 4d5 5s1", "Solid", 2896, 4912},
    {43, "Technetium", "Tc", 98.0, "[Kr] 4d5 5s2", "Solid", 2430, 4600}, // Radioactive
    {44, "Ruthenium", "Ru", 101.07, "[Kr] 4d7 5s1", "Solid", 2607, 4423},
    {45, "Rhodium", "Rh", 102.9055, "[Kr] 4d8 5s1", "Solid", 2237, 3968},
    {46, "Palladium", "Pd", 106.42, "[Kr] 4d10", "Solid", 1828, 3236},
    {47, "Silver", "Ag", 107.868, "[Kr] 4d10 5s1", "Solid", 1234.93, 2435},
    {48, "Cadmium", "Cd", 112.41, "[Kr] 4d10 5s2", "Solid", 594.22, 1040},
    {49, "Indium", "In", 114.818, "[Kr] 4d10 5s2 5p1", "Solid", 429.75, 2345},
    {50, "Tin", "Sn", 118.710, "[Kr] 4d10 5s2 5p2", "Solid", 505.08, 2875},
    {51, "Antimony", "Sb", 121.760, "[Kr] 4d10 5s2 5p3", "Solid", 903.78, 1860},
    {52, "Tellurium", "Te", 127.60, "[Kr] 4d10 5s2 5p4", "Solid", 722.66, 1261},
    {53, "Iodine", "I", 126.9045, "[Kr] 4d10 5s2 5p5", "Solid", 386.85, 457.4}, // Sublimes
    {54, "Xenon", "Xe", 131.293, "[Kr] 4d10 5s2 5p6", "Gas", 161.37, 165.05},
    {55, "Cesium", "Cs", 132.9055, "[Xe] 6s1", "Solid", 301.59, 944},
    {56, "Barium", "Ba", 137.327, "[Xe] 6s2", "Solid", 1000, 2170},
    {57, "Lanthanum", "La", 138.9055, "[Xe] 5d1 6s2", "Solid", 1193, 3737},
    {58, "Cerium", "Ce", 140.116, "[Xe] 4f1 5d1 6s2", "Solid", 1068, 3716},
    {59, "Praseodymium", "Pr", 140.9077, "[Xe] 4f3 6s2", "Solid", 1208, 3793},
    {60, "Neodymium", "Nd", 144.242, "[Xe] 4f4 6s2", "Solid", 1294, 3347},
    {61, "Promethium", "Pm", 145.0, "[Xe] 4f5 6s2", "Solid", 1315, 3273}, // Radioactive
    {62, "Samarium", "Sm", 150.36, "[Xe] 4f6 6s2", "Solid", 1345, 2067},
    {63, "Europium", "Eu", 151.964, "[Xe] 4f7 6s2", "Solid", 1049, 1802},
    {64, "Gadolinium", "Gd", 157.25, "[Xe] 4f7 5d1 6s2", "Solid", 1585, 3273},
    {65, "Terbium", "Tb", 158.9254, "[Xe] 4f9 6s2", "Solid", 1629, 3503},
    {66, "Dysprosium", "Dy", 162.500, "[Xe] 4f10 6s2", "Solid", 1680, 2840},
    {67, "Holmium", "Ho", 164.9303, "[Xe] 4f11 6s2", "Solid", 1734, 2873},
    {68, "Erbium", "Er", 167.259, "[Xe] 4f12 6s2", "Solid", 1802, 3141},
    {69, "Thulium", "Tm", 168.9342, "[Xe] 4f13 6s2", "Solid", 1818, 2223},
    {70, "Ytterbium", "Yb", 173.054, "[Xe] 4f14 6s2", "Solid", 1097, 1469},
    {71, "Lutetium", "Lu", 174.9668, "[Xe] 4f14 5d1 6s2", "Solid", 1925, 3675},
    {72, "Hafnium", "Hf", 178.49, "[Xe] 4f14 5d2 6s2", "Solid", 2506, 4876},
    {73, "Tantalum", "Ta", 180.9479, "[Xe] 4f14 5d3 6s2", "Solid", 3290, 5731},
    {74, "Tungsten", "W", 183.84, "[Xe] 4f14 5d4 6s2", "Solid", 3695, 6203},
    {75, "Rhenium", "Re", 186.207, "[Xe] 4f14 5d5 6s2", "Solid", 3459, 5869},
    {76, "Osmium", "Os", 190.23, "[Xe] 4f14 5d6 6s2", "Solid", 3306, 5285},
    {77, "Iridium", "Ir", 192.217, "[Xe] 4f14 5d7 6s2", "Solid", 2719, 4701},
    {78, "Platinum", "Pt", 195.084, "[Xe] 4f14 5d9 6s1", "Solid", 2041.4, 4098},
    {79, "Gold", "Au", 196.9666, "[Xe] 4f14 5d10 6s1", "Solid", 1337.33, 3129},
    {80, "Mercury", "Hg", 200.59, "[Xe] 4f14 5d10 6s2", "Liquid", 234.32, 629.88},
    {81, "Thallium", "Tl", 204.38, "[Xe] 4f14 5d10 6s2 6p1", "Solid", 577, 1746},
    {82, "Lead", "Pb", 207.2, "[Xe] 4f14 5d10 6s2 6p2", "Solid", 600.61, 2022},
    {83, "Bismuth", "Bi", 208.9804, "[Xe] 4f14 5d10 6s2 6p3", "Solid", 544.7, 1837},
    {84, "Polonium", "Po", 209.0, "[Xe] 4f14 5d10 6s2 6p4", "Solid", 527, 1235}, // Radioactive
    {85, "Astatine", "At", 210.0, "[Xe] 4f14 5d10 6s2 6p5", "Solid", 575, 610}, // Radioactive
    {86, "Radon", "Rn", 222.0, "[Xe] 4f14 5d10 6s2 6p6", "Gas", 202, 211.3}, // Radioactive
    {87, "Francium", "Fr", 223.0, "[Rn] 7s1", "Solid", 270, 677}, // Radioactive
    {88, "Radium", "Ra", 226.0, "[Rn] 7s2", "Solid", 973, 2010}, // Radioactive
    {89, "Actinium", "Ac", 227.0, "[Rn] 6d1 7s2", "Solid", 1323, 3473}, // Radioactive
    {90, "Thorium", "Th", 232.0377, "[Rn] 6d2 7s2", "Solid", 2023, 5061}, // Radioactive
    {91, "Protactinium", "Pa", 231.0359, "[Rn] 5f2 6d1 7s2", "Solid", 1845, 4300}, // Radioactive
    {92, "Uranium", "U", 238.0289, "[Rn] 5f3 6d1 7s2", "Solid", 1405.3, 4404}, // Radioactive
    {93, "Neptunium", "Np", 237.0, "[Rn] 5f4 6d1 7s2", "Solid", 912, 4273}, // Radioactive
    {94, "Plutonium", "Pu", 244.0, "[Rn] 5f6 7s2", "Solid", 912.5, 3503}, // Radioactive
    {95, "Americium", "Am", 243.0, "[Rn] 5f7 7s2", "Solid", 1449, 2880}, // Radioactive
    {96, "Curium", "Cm", 247.0, "[Rn] 5f7 6d1 7s2", "Solid", 1613, 3383}, // Radioactive
    {97, "Berkelium", "Bk", 247.0, "[Rn] 5f9 7s2", "Solid", 1259, 2900}, // Radioactive
    {98, "Californium", "Cf", 251.0, "[Rn] 5f10 7s2", "Solid", 1173, 1743}, // Radioactive
    {99, "Einsteinium", "Es", 252.0, "[Rn] 5f11 7s2", "Solid", 1133, 1260}, // Radioactive
    {100, "Fermium", "Fm", 257.0, "[Rn] 5f12 7s2", "Solid", 1800, 1800}, // Radioactive (estimated)
    {101, "Mendelevium", "Md", 258.0, "[Rn] 5f13 7s2", "Solid", 1100, 1100}, // Radioactive (estimated)
    {102, "Nobelium", "No", 259.0, "[Rn] 5f14 7s2", "Solid", 1100, 1100}, // Radioactive (estimated)
    {103, "Lawrencium", "Lr", 266.0, "[Rn] 5f14 7p1", "Solid", 1900, 1900}, // Radioactive (estimated)
    {104, "Rutherfordium", "Rf", 267.0, "[Rn] 5f14 6d2 7s2", "Solid", 2400, 5300}, // Radioactive (estimated)
    {105, "Dubnium", "Db", 268.0, "[Rn] 5f14 6d3 7s2", "Solid", 2400, 5000}, // Radioactive (estimated)
    {106, "Seaborgium", "Sg", 269.0, "[Rn] 5f14 6d4 7s2", "Solid", 2400, 4800}, // Radioactive (estimated)
    {107, "Bohrium", "Bh", 270.0, "[Rn] 5f14 6d5 7s2", "Solid", 2400, 4500}, // Radioactive (estimated)
    {108, "Hassium", "Hs", 269.0, "[Rn] 5f14 6d6 7s2", "Solid", 2400, 4300}, // Radioactive (estimated)
    {109, "Meitnerium", "Mt", 278.0, "[Rn] 5f14 6d7 7s2", "Expected to be Solid", 2400, 4000}, // Radioactive (estimated)
    {110, "Darmstadtium", "Ds", 281.0, "[Rn] 5f14 6d9 7s1", "Expected to be Solid", 2400, 3700}, // Radioactive (estimated)
    {111, "Roentgenium", "Rg", 282.0, "[Rn] 5f14 6d10 7s1", "Expected to be Solid", 2400, 3500}, // Radioactive (estimated)
    {112, "Copernicium", "Cn", 285.0, "[Rn] 5f14 6d10 7s2", "Expected to be Gas", 283, 357}, // Radioactive (estimated)
    {113, "Nihonium", "Nh", 286.0, "[Rn] 5f14 6d10 7s2 7p1", "Expected to be Solid", 700, 1400}, // Radioactive (estimated)
    {114, "Flerovium", "Fl", 289.0, "[Rn] 5f14 6d10 7s2 7p2", "Expected to be Solid", 340, 420}, // Radioactive (estimated)
    {115, "Moscovium", "Mc", 290.0, "[Rn] 5f14 6d10 7s2 7p3", "Expected to be Solid", 600, 900}, // Radioactive (estimated)
    {116, "Livermorium", "Lv", 293.0, "[Rn] 5f14 6d10 7s2 7p4", "Expected to be Solid", 700, 1100}, // Radioactive (estimated)
    {117, "Tennessine", "Ts", 294.0, "[Rn] 5f14 6d10 7s2 7p5", "Expected to be Solid", 723, 883}, // Radioactive (estimated)
    {118, "Oganesson", "Og", 294.0, "[Rn] 5f14 6d10 7s2 7p6", "Expected to be Gas/Liquid/Solid", 263, 263} // Radioactive (estimated)
};

// Function prototypes
void displayMenu();
void displayPeriodicTable();
void searchElement();
double getAtomicWeight(const char* symbol); // Helper function to get atomic weight by symbol
double parseFormula(const char* formula, int* index); // Recursive function to parse formula
void molarMassCalculator();
void massMolesConverter(); // New function for mass/moles conversion
void molarityCalculator(); // New function for molarity calculation
void idealGasLawCalculator(); // New function for ideal gas law calculation
void temperatureConverter(); // New function for temperature conversion
void help();

// Displays the main menu
void displayMenu() {
    printf("\n=== Chemistry Calculator ===\n");
    printf("1. Periodic Table\n");
    printf("2. Element Search\n");
    printf("3. Molar Mass Calculator\n");
    printf("4. Mass/Moles Conversion\n");
    printf("5. Molarity Calculator\n"); // New menu option
    printf("6. Ideal Gas Law Calculator (PV=nRT)\n"); // New menu option
    printf("7. Temperature Converter\n");
    printf("8. Help\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

// Displays a simplified periodic table (showing first 30)
void displayPeriodicTable() {
    printf("\nAtomic# | Symbol | Name        | Atomic Weight\n");
    printf("---------------------------------------------\n");
    // Displaying a limited number of elements for brevity.
    // You can modify this loop to display more or paginate.
    for(int i = 0; i < 30; i++) { // Displaying first 30 elements as example
        printf("%-8d | %-6s | %-11s | %.4f\n",
              elements[i].atomicNumber,
              elements[i].symbol,
              elements[i].name,
              elements[i].atomicWeight);
    }
    printf("\nNote: Only a partial list is shown here. Use 'Element Search' for detailed information.\n");
}

// Searches for an element by atomic number, symbol, or name
void searchElement() {
    char input[30];
    int num = 0;
    Element foundElement;
    int found = 0;

    printf("Enter atomic number, element symbol, or name: ");
    scanf("%s", input);

    // Check if input is a number (atomic number)
    int isNumber = 1;
    for(int i = 0; i < strlen(input); i++) {
        if(!isdigit(input[i])) {
            isNumber = 0;
            break;
        }
    }

    if(isNumber) {
        num = atoi(input); // atoi is declared in stdlib.h
        if(num >= 1 && num <= MAX_ELEMENTS) {
            foundElement = elements[num-1];
            found = 1;
        }
    } else {
        // Check if input is a symbol or name
        for(int i = 0; i < MAX_ELEMENTS; i++) {
            // Case-insensitive comparison for symbol and name
            if(strcasecmp(input, elements[i].symbol) == 0 || strcasecmp(input, elements[i].name) == 0) {
                foundElement = elements[i];
                found = 1;
                break;
            }
        }
    }

    if(found) {
        printf("\n=== %s (%s) ===\n", foundElement.name, foundElement.symbol);
        printf("Atomic Number      : %d\n", foundElement.atomicNumber);
        printf("Atomic Weight      : %.4f\n", foundElement.atomicWeight);
        printf("Electron Config    : %s\n", foundElement.electronConfig);
        printf("State (25°C, 1 atm): %s\n", foundElement.state);
        printf("Melting Point (K)  : %.2f\n", foundElement.meltingPoint);
        printf("Boiling Point (K)  : %.2f\n", foundElement.boilingPoint);
    } else {
        printf("Element not found.\n");
    }
}

// Helper function to get atomic weight by element symbol
// Returns 0 if symbol is not found
double getAtomicWeight(const char* symbol) {
    for(int i = 0; i < MAX_ELEMENTS; i++) {
        if(strcasecmp(symbol, elements[i].symbol) == 0) {
            return elements[i].atomicWeight;
        }
    }
    return 0; // Symbol not found
}

// Recursive function to parse a chemical formula and calculate molar mass
// Handles basic element symbols, subscripts, and parentheses.
// Returns the molar mass of the parsed part of the formula.
// Updates the index to the position after the parsed part.
double parseFormula(const char* formula, int* index) {
    double currentMolarMass = 0.0;
    char currentSymbol[10];
    int symbolIndex = 0;
    int count = 0;
    int formulaLen = strlen(formula);

    while (*index < formulaLen) {
        char currentChar = formula[*index];

        if (isalpha(currentChar)) {
            // If we were processing a previous element, calculate its contribution
            if (symbolIndex > 0) {
                currentSymbol[symbolIndex] = '\0';
                double weight = getAtomicWeight(currentSymbol);
                if (weight > 0) {
                    currentMolarMass += weight * (count > 0 ? count : 1);
                } else {
                    printf("Error: Unknown element symbol '%s'.\n", currentSymbol);
                    return -1; // Indicate error
                }
                symbolIndex = 0;
                count = 0;
            }
            // Start processing new element symbol
            currentSymbol[symbolIndex++] = currentChar;
            (*index)++;
        } else if (isdigit(currentChar)) {
            // Process digit (subscript)
            count = count * 10 + (currentChar - '0');
            (*index)++;
        } else if (currentChar == '(') {
            // If we were processing a previous element, calculate its contribution
            if (symbolIndex > 0) {
                 currentSymbol[symbolIndex] = '\0';
                double weight = getAtomicWeight(currentSymbol);
                if (weight > 0) {
                    currentMolarMass += weight * (count > 0 ? count : 1);
                } else {
                    printf("Error: Unknown element symbol '%s'.\n", currentSymbol);
                    return -1; // Indicate error
                }
                symbolIndex = 0;
                count = 0;
            }

            (*index)++; // Move past '('
            // Recursively parse the content inside parentheses
            double groupMolarMass = parseFormula(formula, index);
            if (groupMolarMass == -1) return -1; // Propagate error

            // Check for subscript immediately after ')'
            int groupCount = 0;
            while (*index < formulaLen && isdigit(formula[*index])) {
                groupCount = groupCount * 10 + (formula[*index] - '0');
                (*index)++;
            }
            currentMolarMass += groupMolarMass * (groupCount > 0 ? groupCount : 1);

        } else if (currentChar == ')') {
            // End of a group, calculate contribution of the last element in the group
            if (symbolIndex > 0) {
                currentSymbol[symbolIndex] = '\0';
                double weight = getAtomicWeight(currentSymbol);
                if (weight > 0) {
                    currentMolarMass += weight * (count > 0 ? count : 1);
                } else {
                    printf("Error: Unknown element symbol '%s'.\n", currentSymbol);
                    return -1; // Indicate error
                }
            }
            (*index)++; // Move past ')'
            return currentMolarMass; // Return molar mass of this group
        } else {
            // Handle potential invalid characters
            printf("Error: Invalid character '%c' in formula.\n", currentChar);
            return -1; // Indicate error
        }
    }

    // After the loop, process the last element if any
    if (symbolIndex > 0) {
        currentSymbol[symbolIndex] = '\0';
        double weight = getAtomicWeight(currentSymbol);
        if (weight > 0) {
            currentMolarMass += weight * (count > 0 ? count : 1);
        } else {
            printf("Error: Unknown element symbol '%s'.\n", currentSymbol);
            return -1; // Indicate error
        }
    }

    return currentMolarMass;
}


// Calculates the molar mass of a chemical formula
void molarMassCalculator() {
    char formula[MAX_FORMULA_LENGTH];
    printf("Enter chemical formula (e.g., H2O, C6H12O6, Ca(OH)2): ");
    scanf("%s", formula);

    int index = 0;
    double molarMass = parseFormula(formula, &index);

    if (molarMass > 0) {
        printf("The molar mass of %s is approximately: %.4f g/mol\n", formula, molarMass);
    } else if (molarMass == 0) {
         printf("Could not calculate molar mass. Please check the formula.\n");
    }
    // Error message is printed within parseFormula if molarMass is -1
}

// Converts between mass and moles
void massMolesConverter() {
    int choice;
    char formula[MAX_FORMULA_LENGTH];
    double mass, moles, molarMass;

    printf("\n=== Mass/Moles Conversion ===\n");
    printf("1. Convert Mass to Moles\n");
    printf("2. Convert Moles to Mass\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter the chemical formula of the substance: ");
    scanf("%s", formula);

    int index = 0;
    molarMass = parseFormula(formula, &index);

    if (molarMass <= 0) {
        printf("Could not calculate molar mass. Please check the formula.\n");
        return;
    }

    switch(choice) {
        case 1:
            printf("Enter the mass of the substance (g): ");
            scanf("%lf", &mass);
            moles = mass / molarMass;
            printf("%.4f g of %s is approximately %.4f mol.\n", mass, formula, moles);
            break;
        case 2:
            printf("Enter the moles of the substance (mol): ");
            scanf("%lf", &moles);
            mass = moles * molarMass;
            printf("%.4f mol of %s is approximately %.4f g.\n", moles, formula, mass);
            break;
        default:
            printf("Invalid choice.\n");
    }
}

// Calculates molarity of a solution
void molarityCalculator() {
    char formula[MAX_FORMULA_LENGTH];
    double mass = 0.0, moles = 0.0, volume = 0.0, molarMass = 0.0;
    int input_type_choice;

    printf("\n=== Molarity Calculator ===\n");
    printf("Calculate molarity (mol/L).\n");
    printf("Do you have the mass or moles of the solute?\n");
    printf("1. Mass\n");
    printf("2. Moles\n");
    printf("Enter your choice: ");
    scanf("%d", &input_type_choice);

    printf("Enter the chemical formula of the solute: ");
    scanf("%s", formula);

    int index = 0;
    molarMass = parseFormula(formula, &index);

    if (molarMass <= 0) {
        printf("Could not calculate molar mass. Please check the formula.\n");
        return;
    }

    if (input_type_choice == 1) {
        printf("Enter the mass of the solute (g): ");
        scanf("%lf", &mass);
        moles = mass / molarMass;
    } else if (input_type_choice == 2) {
        printf("Enter the moles of the solute (mol): ");
        scanf("%lf", &moles);
    } else {
        printf("Invalid input type choice.\n");
        return;
    }

    printf("Enter the volume of the solution (L): ");
    scanf("%lf", &volume);

    if (volume <= 0) {
        printf("Volume must be greater than zero.\n");
        return;
    }

    double molarity = moles / volume;
    printf("The molarity of the solution is approximately: %.4f mol/L\n", molarity);
}

// Performs Ideal Gas Law calculations (PV=nRT)
void idealGasLawCalculator() {
    char solve_for;
    double P = 0.0, V = 0.0, n = 0.0, T = 0.0;

    printf("\n=== Ideal Gas Law Calculator (PV=nRT) ===\n");
    printf("Enter the variable you want to solve for (P, V, n, or T): ");
    scanf(" %c", &solve_for); // Note the space before %c to consume newline

    // Convert input to uppercase for easier comparison
    solve_for = toupper(solve_for);

    if (solve_for != 'P' && solve_for != 'V' && solve_for != 'N' && solve_for != 'T') {
        printf("Invalid variable to solve for. Please enter P, V, n, or T.\n");
        return;
    }

    printf("Enter the known values (enter 0 for the variable you are solving for):\n");

    if (solve_for != 'P') {
        printf("Pressure (atm): ");
        scanf("%lf", &P);
    }
    if (solve_for != 'V') {
        printf("Volume (L): ");
        scanf("%lf", &V);
    }
    if (solve_for != 'N') {
        printf("Moles (mol): ");
        scanf("%lf", &n);
    }
    if (solve_for != 'T') {
        printf("Temperature (K): ");
        scanf("%lf", &T);
    }

    // Perform calculation based on the variable to solve for
    switch (solve_for) {
        case 'P':
            if (V == 0 || n == 0 || T == 0) {
                 printf("Error: Cannot solve for Pressure with zero Volume, Moles, or Temperature.\n");
            } else {
                P = (n * R_IDEAL_GAS * T) / V;
                printf("Pressure (P) = %.4f atm\n", P);
            }
            break;
        case 'V':
             if (P == 0 || n == 0 || T == 0) {
                 printf("Error: Cannot solve for Volume with zero Pressure, Moles, or Temperature.\n");
            } else {
                V = (n * R_IDEAL_GAS * T) / P;
                printf("Volume (V) = %.4f L\n", V);
            }
            break;
        case 'N':
            if (P == 0 || V == 0 || T == 0) {
                 printf("Error: Cannot solve for Moles with zero Pressure, Volume, or Temperature.\n");
            } else {
                n = (P * V) / (R_IDEAL_GAS * T);
                printf("Moles (n) = %.4f mol\n", n);
            }
            break;
        case 'T':
             if (P == 0 || V == 0 || n == 0) {
                 printf("Error: Cannot solve for Temperature with zero Pressure, Volume, or Moles.\n");
            } else {
                T = (P * V) / (n * R_IDEAL_GAS);
                printf("Temperature (T) = %.2f K\n", T);
            }
            break;
        default:
            // This case should ideally not be reached due to the initial check
            printf("An unexpected error occurred.\n");
            break;
    }
}


// Converts between temperature units
void temperatureConverter() {
    int choice;
    double temp, convertedTemp;

    printf("\n=== Temperature Converter ===\n");
    printf("1. Celsius (°C) to Kelvin (K)\n");
    printf("2. Kelvin (K) to Celsius (°C)\n");
    printf("3. Celsius (°C) to Fahrenheit (°F)\n");
    printf("4. Fahrenheit (°F) to Celsius (°C)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter the temperature value: ");
    scanf("%lf", &temp);

    switch(choice) {
        case 1: // C to K
            convertedTemp = temp + 273.15;
            printf("%.2f °C is equal to %.2f K\n", temp, convertedTemp);
            break;
        case 2: // K to C
            convertedTemp = temp - 273.15;
            printf("%.2f K is equal to %.2f °C\n", temp, convertedTemp);
            break;
        case 3: // C to F
            convertedTemp = (temp * 9.0/5.0) + 32.0; // Use floating-point division
            printf("%.2f °C is equal to %.2f °F\n", temp, convertedTemp);
            break;
        case 4: // F to C
            convertedTemp = (temp - 32.0) * 5.0/9.0; // Use floating-point division
            printf("%.2f °F is equal to %.2f °C\n", temp, convertedTemp);
            break;
        default:
            printf("Invalid choice.\n");
    }
}


// Displays help information
void help() {
    printf("\nAvailable Commands:\n");
    printf("1 - View Periodic Table (partial)\n");
    printf("2 - Search for element details by atomic number, symbol, or name\n");
    printf("3 - Calculate the molar mass of a given chemical formula (supports parentheses)\n");
    printf("4 - Convert between mass and moles\n");
    printf("5 - Calculate the molarity of a solution\n");
    printf("6 - Perform Ideal Gas Law calculations (PV=nRT)\n");
    printf("7 - Perform temperature unit conversions\n");
    printf("8 - Display help information\n");
    printf("0 - Exit the program\n");
}

int main() {
    // No need for Windows-specific console settings for English output

    int choice;
    while(1) {
        displayMenu();
        scanf("%d", &choice);

        switch(choice) {
            case 1: displayPeriodicTable(); break;
            case 2: searchElement(); break;
            case 3: molarMassCalculator(); break;
            case 4: massMolesConverter(); break;
            case 5: molarityCalculator(); break; // Call new function
            case 6: idealGasLawCalculator(); break; // Call new function
            case 7: temperatureConverter(); break;
            case 8: help(); break;
            case 0: return 0;
            default: printf("Invalid choice. Please enter a number between 0 and 8.\n");
        }
    }

    return 0;
}
