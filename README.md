# CompreC

CompreC is a command-line utility written in C that allows you to work with zip archives. It provides various options for browsing, extracting, bruteforcing, and manipulating zip files.

## Installation

To use CompreC, make sure you have `make` installed on your system. Then, follow these steps:

1. Clone the repository:

   ```shell
   git clone https://github.com/Dourin/compreC.git
   ```

2. Navigate to the project directory:

   ```shell
   cd CompreC
   ```

3. Run the `make` command to compile the source code:

   ```shell
   make
   ```

4. Run the executable:

   ```shell
   ./programme.exe [options]
   ```

## Usage

CompreC supports the following command-line options:

- `-h, --help`: Display the help message.
- `-o, --open`: Open a zip file for browsing.
- `-b, --bruteforce`: Try to bruteforce the password for the zip file.
- `-d, --dictionary <filename>`: Try to bruteforce the password with a dictionary file.
- `-e, --extract <filename>`: Extract a specific file from the zip archive.
- `-i, --include <filename>`: Include a file in the zip archive.

Please note that some options require additional arguments or user input.

## Examples

Here are some examples of how to use CompreC:

1. Open a zip file for browsing:

   ```shell
   ./programme.exe -o
   ```

2. Try to bruteforce the password for the zip file:

   ```shell
   ./programme.exe -b
   ```

3. Try to bruteforce the password with a dictionary file:

   ```shell
   ./programme.exe -d dictionary.txt
   ```

4. Extract a specific file from the zip archive:

   ```shell
   ./programme.exe -e file.txt
   ```

5. Include a file in the zip archive:

   ```shell
   ./programme.exe -i file.txt
   ```

## Contributing

If you would like to contribute to CompreC, please follow the guidelines in the [CONTRIBUTING](CONTRIBUTING.md) file.

## License

CompreC is an open-source project released under a [ESGI](https://www.esgi.fr) school project.

## Disclaimer

This project is intended for educational and learning purposes only. Neither the team members nor the project are responsible for any misuse or illegal activities conducted with the code.

## Authors 
- [Dorin](https://gitlab.com/Muncidor) 
- [Ethan](https://gitlab.com/CobraBubulle)
- [Thibault](https://gitlab.com/thibaultleguern)
