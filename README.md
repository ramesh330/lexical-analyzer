# Lexical Analyzer in C

## 📌 Description

A **Lexical Analyzer** implemented in C that reads a C source file character by character, identifies and classifies different types of tokens, and detects common lexical errors.

The project demonstrates fundamental concepts of **Compiler Design, File Handling, Structures, Enumerations, Character Processing, Tokenization, and Error Handling** in C.

## 🚀 Features

- Recognizes **Keywords**
- Recognizes **Identifiers**
- Recognizes **Integer Constants**
- Recognizes **Floating-Point Constants**
- Recognizes **Character Constants**
- Recognizes **String Literals**
- Recognizes **Operators**
- Recognizes **Special Symbols**
- Recognizes **Preprocessor Directives**
- Handles **Single-line comments (`//`)**
- Handles **Multi-line comments (`/* */`)**
- Handles common **Escape Sequences**
- Maintains **Line Numbers**
- Detects and reports **Lexical Errors**
- Stores recognized tokens using a **Token Array**
- Protects against exceeding the maximum token limit

## ⚠️ Lexical Errors Detected

The analyzer can detect errors such as:

- Invalid characters
- Invalid number formats
- Multiple decimal points in a number
- Numbers followed by invalid identifiers
- Invalid character constants
- Unterminated string literals
- Unterminated multi-line comments

### Example

```c
float x = 10.20.30;
```

Output:

```text
10.20.30    INVALID
```

And:

```text
Lexical Error: Invalid number
```

## 🛠️ Technologies Used

- **Language:** C
- **Compiler:** GCC
- **Operating System:** Linux
- **Concepts:** Lexical Analysis, Tokenization, File Handling, Structures, Enums, Pointers

## 📂 Project Structure

```text
lexical-analyzer/
│
├── main.c       # Command-line argument validation and file handling
├── lexar.c      # Lexical analysis and tokenization logic
├── lexar.h      # Structures, enums, and function declarations
├── input.c      # Sample C source file for testing
├── .gitignore
└── README.md
```

## 🔧 Compilation

Compile the project using:

```bash
cc main.c lexar.c -o lexar
```

## ▶️ Execution

Run the lexical analyzer by passing a C source file:

```bash
./lexar input.c
```

## 📋 Sample Output

```text
LEXEME                         TOKEN TYPE
----------------------------------------------------------
#include <stdio.h>             PREPROCESSOR_DIRECTIVE
int                            KEYWORD
main                           IDENTIFIER
(                              SPECIAL_SYMBOL
)                              SPECIAL_SYMBOL
{                              SPECIAL_SYMBOL
count                          IDENTIFIER
=                              OPERATOR
10                             INTEGER_CONSTANT
;                              SPECIAL_SYMBOL
12.50                          FLOATING_CONSTANT
'A'                            CHARACTER_CONSTANT
"Hello World"                  STRING_LITERAL
++                             OPERATOR
}                              SPECIAL_SYMBOL
```

## 📊 Token Types

| Token Type | Example |
|---|---|
| KEYWORD | `int`, `return`, `if` |
| IDENTIFIER | `main`, `count` |
| INTEGER_CONSTANT | `100` |
| FLOATING_CONSTANT | `12.50` |
| CHARACTER_CONSTANT | `'A'`, `'\n'` |
| STRING_LITERAL | `"Hello World"` |
| OPERATOR | `+`, `==`, `++`, `&&` |
| SPECIAL_SYMBOL | `(`, `)`, `{`, `}`, `;` |
| PREPROCESSOR_DIRECTIVE | `#include<stdio.h>` |
| INVALID | `@`, `10.20.30` |

## 🧠 How It Works

```text
C Source File
      ↓
Read Character by Character
      ↓
Identify Lexeme
      ↓
Classify Token
      ↓
Validate Lexical Rules
      ↓
Store Token
      ↓
Display Token Table
```

## 🎯 Learning Objectives

This project was developed to understand:

- How a lexical analyzer works
- How source code is converted into tokens
- Token recognition techniques
- Character-by-character file processing
- Lexical error detection
- Structures and enumerations in C
- Command-line arguments
- File handling in C
- Basic compiler design concepts

## 🔮 Future Enhancements

- Add a symbol table
- Improve numeric constant validation
- Support more C operators
- Support additional escape sequences
- Generate tokens as an intermediate file
- Integrate the lexer with a syntax parser

## 👨‍💻 Author

**Ramesh Pandhare**

### ⭐ If you find this project useful, consider giving it a star!
