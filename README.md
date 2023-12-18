# Book Database Project
## Overview
Welcome to the Book Database project! This is a learning project aimed at creating a simple book database to keep track of the books you've read or are currently reading. The project is implemented in C++ and utilizes an SQLite database to store book information.

## Features
- SQLite Database: The project leverages the power of SQLite to efficiently store and manage book data.
- C++ Implementation: The core functionality is implemented in C++, allowing you to explore and understand the language better.
- Command Line Interface (CLI): The current version of the project operates through the command line interface, providing a foundational structure for managing books.

## Future Plans
The ultimate goal is to enhance the project by adding a graphical user interface (GUI) for a more user-friendly experience. However, before diving into learning GUI development, the focus is on achieving most of the initial functionality through the command line interface. Once the core features are solidified, we'll transition to building a GUI to make interacting with the book database even more accessible.

## Getting Started
### Prerequisites
Before running the project, ensure you have the following installed:
- C++ compiler
- SQLite library

### Installation
1. Clone the repository:
``` bash
git clone https://github.com/your-username/book-database-project.git
```
* Note: Database is in a completely different folder than project. Path used is HOME/Programming/Databases/book_database.db *

To run
- Can manually compile
``` bash
g++ main.cpp -o book_database -lsqlite3
```
- Or use an IDE. Projject was started and run through CLion.

## Usage
When running, there are on-screen instructions to interact with the book database. Use commands to add new books, and view the list of books. Other features will be added at a later time.

## Contributing
Contributions are welcome! If you have ideas for improvements or find any issues, feel free to open an issue or submit a pull request.

## License
This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.
