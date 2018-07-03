# Linalg

Very basic linear algebra library for use in embedded applications such as firmware for PIC or AVR micro-controllers. Supports
* Matrix addition (and subtraction)
* Matrix multiplication
* Matrix transpose
* Matrix inverse (only for 2x2 matrices)

The library allocates memory for a fixed number of matrices to limit memory usage on the micro-controller.

# Examples

The project contains simple tests to demonstrate the features of the library. A makefile is provided so you can build the project  directly from the console.

```
make
```

A series of tests will be run. You can modify these tests directly in the `tests.c` file.

## Authors

* **Emile Décosterd** - *Initial work* - [emiledecosterd](https://github.com/emiledecosterd)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the GNU General Public License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Toby Jaffey https://electronics.stackexchange.com/questions/7850/use-of-malloc-in-pic
