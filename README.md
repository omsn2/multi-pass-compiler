# Multi-Pass Compiler

## Overview
The **Multi-Pass Compiler** is a project that implements a multi-pass compilation process. It includes separate components for the frontend, backend, and common utilities, demonstrating a structured approach to compiler development.

## Project Structure
```
├── backend/            # Backend logic for the compiler
├── frontend/           # Frontend logic (parsing, lexical analysis, etc.)
├── common/             # Shared modules/utilities
├── tests/              # Test cases for the compiler
├── Makefile            # Build configuration file
├── test.c++            # Sample C++ test file
├── multi_pass_compiler.exe # Compiled executable
└── .vscode/            # VS Code configuration files
```

## Features
- **Multi-Pass Compilation**: Implements a modular approach with separate phases.
- **Frontend and Backend**: Clearly separated components for parsing and code generation.
- **Testing Framework**: Includes test cases to verify the functionality of each compiler stage.

## Requirements
To build and run the project, you need the following:
- A C++ compiler (e.g., `g++` or `clang`)
- `make` utility for building the project
- Visual Studio Code (optional, for development)

## How to Build
1. Open a terminal and navigate to the project directory.
2. Run the following command to build the project using the Makefile:
   ```bash
   make
   ```

## How to Run
After building, you can run the compiler using the provided executable:
```bash
./multi_pass_compiler.exe
```

## How to Test
The `tests/` directory contains various test cases. To run the tests:
```bash
make test
```

## Development Environment
This project is configured for Visual Studio Code. To set up:
1. Open the project in VS Code.
2. Install the recommended extensions for C++ development.
3. Modify the `.vscode/settings.json` and `.vscode/launch.json` files as needed for your environment.

## Contributing
Contributions are welcome! Feel free to open issues or submit pull requests.

## License
This project is licensed under the [MIT License](LICENSE).

## Author
Developed by Omkar S N .
