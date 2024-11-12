# xtermc -- XTerm control via the command-line

`xtermc` is a simple C program
that allows to change the appearance of a running XTerm terminal.

This program currently allows you to change the title of the terminal,
as well as the text color, background color, and cursor color.

## Usage

Run the program with the following options:
```SH
xtermc [options]
```

### Options

- `-t` <string>: Set the title of the terminal.
- `-f` <color>: Set the foreground (text) color.
- `-b` <color>: Set the background color.
- `-c` <color>: Set the cursor color.

### Colors
Colors are specified either as strings (e.g., `black` or `red`)
or as RGB values in hex (e.g. `#000` or `#3124f7`),
with or without the initial `#` character.

## Examples

Set the title to the hostname:
```sh
xtermc -t "$(hostname)"
```
    
Set the text color to red:
```SH
xtermc -f red
```

Set the background color to blue:
```SH
xtermc -b 00f
```

Set the colors of the Solarized theme:
```sh
xterm -f #839496 -b #fdf6e3
```
    
## License
This code is licensed under the General Public License, version 3 or later.
See the LICENSE file for the license text.

